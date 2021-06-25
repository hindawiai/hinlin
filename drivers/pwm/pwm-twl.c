<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम TWL4030/6030 Generic Pulse Width Modulator
 *
 * Copyright (C) 2012 Texas Instruments
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/slab.h>

/*
 * This driver handles the PWMs of TWL4030 and TWL6030.
 * The TRM names क्रम the PWMs on TWL4030 are: PWM0, PWM1
 * TWL6030 also have two PWMs named in the TRM as PWM1, PWM2
 */

#घोषणा TWL_PWM_MAX		0x7f

/* Registers, bits and macro क्रम TWL4030 */
#घोषणा TWL4030_GPBR1_REG	0x0c
#घोषणा TWL4030_PMBR1_REG	0x0d

/* GPBR1 रेजिस्टर bits */
#घोषणा TWL4030_PWMXCLK_ENABLE	(1 << 0)
#घोषणा TWL4030_PWMX_ENABLE	(1 << 2)
#घोषणा TWL4030_PWMX_BITS	(TWL4030_PWMX_ENABLE | TWL4030_PWMXCLK_ENABLE)
#घोषणा TWL4030_PWM_TOGGLE(pwm, x)	((x) << (pwm))

/* PMBR1 रेजिस्टर bits */
#घोषणा TWL4030_GPIO6_PWM0_MUTE_MASK		(0x03 << 2)
#घोषणा TWL4030_GPIO6_PWM0_MUTE_PWM0		(0x01 << 2)
#घोषणा TWL4030_GPIO7_VIBRASYNC_PWM1_MASK	(0x03 << 4)
#घोषणा TWL4030_GPIO7_VIBRASYNC_PWM1_PWM1	(0x03 << 4)

/* Register, bits and macro क्रम TWL6030 */
#घोषणा TWL6030_TOGGLE3_REG	0x92

#घोषणा TWL6030_PWMXR		(1 << 0)
#घोषणा TWL6030_PWMXS		(1 << 1)
#घोषणा TWL6030_PWMXEN		(1 << 2)
#घोषणा TWL6030_PWM_TOGGLE(pwm, x)	((x) << (pwm * 3))

काष्ठा twl_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा mutex mutex;
	u8 twl6030_toggle3;
	u8 twl4030_pwm_mux;
पूर्ण;

अटल अंतरभूत काष्ठा twl_pwm_chip *to_twl(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा twl_pwm_chip, chip);
पूर्ण

अटल पूर्णांक twl_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	पूर्णांक duty_cycle = DIV_ROUND_UP(duty_ns * TWL_PWM_MAX, period_ns) + 1;
	u8 pwm_config[2] = अणु 1, 0 पूर्ण;
	पूर्णांक base, ret;

	/*
	 * To configure the duty period:
	 * On-cycle is set to 1 (the minimum allowed value)
	 * The off समय of 0 is not configurable, so the mapping is:
	 * 0 -> off cycle = 2,
	 * 1 -> off cycle = 2,
	 * 2 -> off cycle = 3,
	 * 126 - > off cycle 127,
	 * 127 - > off cycle 1
	 * When on cycle == off cycle the PWM will be always on
	 */
	अगर (duty_cycle == 1)
		duty_cycle = 2;
	अन्यथा अगर (duty_cycle > TWL_PWM_MAX)
		duty_cycle = 1;

	base = pwm->hwpwm * 3;

	pwm_config[1] = duty_cycle;

	ret = twl_i2c_ग_लिखो(TWL_MODULE_PWM, pwm_config, base, 2);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to configure PWM\n", pwm->label);

	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwm_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &val, TWL4030_GPBR1_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read GPBR1\n", pwm->label);
		जाओ out;
	पूर्ण

	val |= TWL4030_PWM_TOGGLE(pwm->hwpwm, TWL4030_PWMXCLK_ENABLE);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, val, TWL4030_GPBR1_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to enable PWM\n", pwm->label);

	val |= TWL4030_PWM_TOGGLE(pwm->hwpwm, TWL4030_PWMX_ENABLE);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, val, TWL4030_GPBR1_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to enable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl4030_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwm_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &val, TWL4030_GPBR1_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read GPBR1\n", pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL4030_PWM_TOGGLE(pwm->hwpwm, TWL4030_PWMX_ENABLE);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, val, TWL4030_GPBR1_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

	val &= ~TWL4030_PWM_TOGGLE(pwm->hwpwm, TWL4030_PWMXCLK_ENABLE);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, val, TWL4030_GPBR1_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
पूर्ण

अटल पूर्णांक twl4030_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwm_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val, mask, bits;

	अगर (pwm->hwpwm == 1) अणु
		mask = TWL4030_GPIO7_VIBRASYNC_PWM1_MASK;
		bits = TWL4030_GPIO7_VIBRASYNC_PWM1_PWM1;
	पूर्ण अन्यथा अणु
		mask = TWL4030_GPIO6_PWM0_MUTE_MASK;
		bits = TWL4030_GPIO6_PWM0_MUTE_PWM0;
	पूर्ण

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &val, TWL4030_PMBR1_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read PMBR1\n", pwm->label);
		जाओ out;
	पूर्ण

	/* Save the current MUX configuration क्रम the PWM */
	twl->twl4030_pwm_mux &= ~mask;
	twl->twl4030_pwm_mux |= (val & mask);

	/* Select PWM functionality */
	val &= ~mask;
	val |= bits;

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, val, TWL4030_PMBR1_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to request PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl4030_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwm_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val, mask;

	अगर (pwm->hwpwm == 1)
		mask = TWL4030_GPIO7_VIBRASYNC_PWM1_MASK;
	अन्यथा
		mask = TWL4030_GPIO6_PWM0_MUTE_MASK;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &val, TWL4030_PMBR1_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read PMBR1\n", pwm->label);
		जाओ out;
	पूर्ण

	/* Restore the MUX configuration क्रम the PWM */
	val &= ~mask;
	val |= (twl->twl4030_pwm_mux & mask);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, val, TWL4030_PMBR1_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to free PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
पूर्ण

अटल पूर्णांक twl6030_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwm_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	val = twl->twl6030_toggle3;
	val |= TWL6030_PWM_TOGGLE(pwm->hwpwm, TWL6030_PWMXS | TWL6030_PWMXEN);
	val &= ~TWL6030_PWM_TOGGLE(pwm->hwpwm, TWL6030_PWMXR);

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_TOGGLE3_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to enable PWM\n", pwm->label);
		जाओ out;
	पूर्ण

	twl->twl6030_toggle3 = val;
out:
	mutex_unlock(&twl->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl6030_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwm_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	val = twl->twl6030_toggle3;
	val |= TWL6030_PWM_TOGGLE(pwm->hwpwm, TWL6030_PWMXR);
	val &= ~TWL6030_PWM_TOGGLE(pwm->hwpwm, TWL6030_PWMXS | TWL6030_PWMXEN);

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_TOGGLE3_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);
		जाओ out;
	पूर्ण

	val |= TWL6030_PWM_TOGGLE(pwm->hwpwm, TWL6030_PWMXEN);

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_TOGGLE3_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL6030_PWM_TOGGLE(pwm->hwpwm, TWL6030_PWMXEN);

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_TOGGLE3_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);
		जाओ out;
	पूर्ण

	twl->twl6030_toggle3 = val;
out:
	mutex_unlock(&twl->mutex);
पूर्ण

अटल स्थिर काष्ठा pwm_ops twl4030_pwm_ops = अणु
	.config = twl_pwm_config,
	.enable = twl4030_pwm_enable,
	.disable = twl4030_pwm_disable,
	.request = twl4030_pwm_request,
	.मुक्त = twl4030_pwm_मुक्त,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा pwm_ops twl6030_pwm_ops = अणु
	.config = twl_pwm_config,
	.enable = twl6030_pwm_enable,
	.disable = twl6030_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक twl_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_pwm_chip *twl;
	पूर्णांक ret;

	twl = devm_kzalloc(&pdev->dev, माप(*twl), GFP_KERNEL);
	अगर (!twl)
		वापस -ENOMEM;

	अगर (twl_class_is_4030())
		twl->chip.ops = &twl4030_pwm_ops;
	अन्यथा
		twl->chip.ops = &twl6030_pwm_ops;

	twl->chip.dev = &pdev->dev;
	twl->chip.npwm = 2;

	mutex_init(&twl->mutex);

	ret = pwmchip_add(&twl->chip);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, twl);

	वापस 0;
पूर्ण

अटल पूर्णांक twl_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_pwm_chip *twl = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&twl->chip);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id twl_pwm_of_match[] = अणु
	अणु .compatible = "ti,twl4030-pwm" पूर्ण,
	अणु .compatible = "ti,twl6030-pwm" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_pwm_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver twl_pwm_driver = अणु
	.driver = अणु
		.name = "twl-pwm",
		.of_match_table = of_match_ptr(twl_pwm_of_match),
	पूर्ण,
	.probe = twl_pwm_probe,
	.हटाओ = twl_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(twl_pwm_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("PWM driver for TWL4030 and TWL6030");
MODULE_ALIAS("platform:twl-pwm");
MODULE_LICENSE("GPL");
