<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम TWL4030/6030 Pulse Width Modulator used as LED driver
 *
 * Copyright (C) 2012 Texas Instruments
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * This driver is a complete reग_लिखो of the क्रमmer pwm-twl6030.c authorded by:
 * Hemanth V <hemanthv@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/slab.h>

/*
 * This driver handles the PWM driven LED terminals of TWL4030 and TWL6030.
 * To generate the संकेत on TWL4030:
 *  - LEDA uses PWMA
 *  - LEDB uses PWMB
 * TWL6030 has one LED pin with dedicated LEDPWM
 */

#घोषणा TWL4030_LED_MAX		0x7f
#घोषणा TWL6030_LED_MAX		0xff

/* Registers, bits and macro क्रम TWL4030 */
#घोषणा TWL4030_LEDEN_REG	0x00
#घोषणा TWL4030_PWMA_REG	0x01

#घोषणा TWL4030_LEDXON		(1 << 0)
#घोषणा TWL4030_LEDXPWM		(1 << 4)
#घोषणा TWL4030_LED_PINS	(TWL4030_LEDXON | TWL4030_LEDXPWM)
#घोषणा TWL4030_LED_TOGGLE(led, x)	((x) << (led))

/* Register, bits and macro क्रम TWL6030 */
#घोषणा TWL6030_LED_PWM_CTRL1	0xf4
#घोषणा TWL6030_LED_PWM_CTRL2	0xf5

#घोषणा TWL6040_LED_MODE_HW	0x00
#घोषणा TWL6040_LED_MODE_ON	0x01
#घोषणा TWL6040_LED_MODE_OFF	0x02
#घोषणा TWL6040_LED_MODE_MASK	0x03

काष्ठा twl_pwmled_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा mutex mutex;
पूर्ण;

अटल अंतरभूत काष्ठा twl_pwmled_chip *to_twl(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा twl_pwmled_chip, chip);
पूर्ण

अटल पूर्णांक twl4030_pwmled_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	पूर्णांक duty_cycle = DIV_ROUND_UP(duty_ns * TWL4030_LED_MAX, period_ns) + 1;
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
	अन्यथा अगर (duty_cycle > TWL4030_LED_MAX)
		duty_cycle = 1;

	base = pwm->hwpwm * 2 + TWL4030_PWMA_REG;

	pwm_config[1] = duty_cycle;

	ret = twl_i2c_ग_लिखो(TWL4030_MODULE_LED, pwm_config, base, 2);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to configure PWM\n", pwm->label);

	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_pwmled_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwmled_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_LED, &val, TWL4030_LEDEN_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read LEDEN\n", pwm->label);
		जाओ out;
	पूर्ण

	val |= TWL4030_LED_TOGGLE(pwm->hwpwm, TWL4030_LED_PINS);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, val, TWL4030_LEDEN_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to enable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl4030_pwmled_disable(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwmled_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_LED, &val, TWL4030_LEDEN_REG);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read LEDEN\n", pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL4030_LED_TOGGLE(pwm->hwpwm, TWL4030_LED_PINS);

	ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, val, TWL4030_LEDEN_REG);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
पूर्ण

अटल पूर्णांक twl6030_pwmled_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	पूर्णांक duty_cycle = (duty_ns * TWL6030_LED_MAX) / period_ns;
	u8 on_समय;
	पूर्णांक ret;

	on_समय = duty_cycle & 0xff;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, on_समय,
			       TWL6030_LED_PWM_CTRL1);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to configure PWM\n", pwm->label);

	वापस ret;
पूर्ण

अटल पूर्णांक twl6030_pwmled_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwmled_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID1, &val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read PWM_CTRL2\n",
			pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL6040_LED_MODE_MASK;
	val |= TWL6040_LED_MODE_ON;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to enable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl6030_pwmled_disable(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwmled_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID1, &val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read PWM_CTRL2\n",
			pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL6040_LED_MODE_MASK;
	val |= TWL6040_LED_MODE_OFF;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to disable PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
पूर्ण

अटल पूर्णांक twl6030_pwmled_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwmled_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID1, &val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read PWM_CTRL2\n",
			pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL6040_LED_MODE_MASK;
	val |= TWL6040_LED_MODE_OFF;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to request PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl6030_pwmled_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा twl_pwmled_chip *twl = to_twl(chip);
	पूर्णांक ret;
	u8 val;

	mutex_lock(&twl->mutex);
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID1, &val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s: Failed to read PWM_CTRL2\n",
			pwm->label);
		जाओ out;
	पूर्ण

	val &= ~TWL6040_LED_MODE_MASK;
	val |= TWL6040_LED_MODE_HW;

	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID1, val, TWL6030_LED_PWM_CTRL2);
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to free PWM\n", pwm->label);

out:
	mutex_unlock(&twl->mutex);
पूर्ण

अटल स्थिर काष्ठा pwm_ops twl4030_pwmled_ops = अणु
	.enable = twl4030_pwmled_enable,
	.disable = twl4030_pwmled_disable,
	.config = twl4030_pwmled_config,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा pwm_ops twl6030_pwmled_ops = अणु
	.enable = twl6030_pwmled_enable,
	.disable = twl6030_pwmled_disable,
	.config = twl6030_pwmled_config,
	.request = twl6030_pwmled_request,
	.मुक्त = twl6030_pwmled_मुक्त,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक twl_pwmled_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_pwmled_chip *twl;
	पूर्णांक ret;

	twl = devm_kzalloc(&pdev->dev, माप(*twl), GFP_KERNEL);
	अगर (!twl)
		वापस -ENOMEM;

	अगर (twl_class_is_4030()) अणु
		twl->chip.ops = &twl4030_pwmled_ops;
		twl->chip.npwm = 2;
	पूर्ण अन्यथा अणु
		twl->chip.ops = &twl6030_pwmled_ops;
		twl->chip.npwm = 1;
	पूर्ण

	twl->chip.dev = &pdev->dev;

	mutex_init(&twl->mutex);

	ret = pwmchip_add(&twl->chip);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, twl);

	वापस 0;
पूर्ण

अटल पूर्णांक twl_pwmled_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl_pwmled_chip *twl = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&twl->chip);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id twl_pwmled_of_match[] = अणु
	अणु .compatible = "ti,twl4030-pwmled" पूर्ण,
	अणु .compatible = "ti,twl6030-pwmled" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_pwmled_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver twl_pwmled_driver = अणु
	.driver = अणु
		.name = "twl-pwmled",
		.of_match_table = of_match_ptr(twl_pwmled_of_match),
	पूर्ण,
	.probe = twl_pwmled_probe,
	.हटाओ = twl_pwmled_हटाओ,
पूर्ण;
module_platक्रमm_driver(twl_pwmled_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("PWM driver for TWL4030 and TWL6030 LED outputs");
MODULE_ALIAS("platform:twl-pwmled");
MODULE_LICENSE("GPL");
