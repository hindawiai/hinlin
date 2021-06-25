<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम PCA9685 16-channel 12-bit PWM LED controller
 *
 * Copyright (C) 2013 Steffen Trumtrar <s.trumtrar@pengutronix.de>
 * Copyright (C) 2015 Clemens Gruber <clemens.gruber@pqgruber.com>
 *
 * based on the pwm-twl-led.c driver
 */

#समावेश <linux/acpi.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/biपंचांगap.h>

/*
 * Because the PCA9685 has only one prescaler per chip, changing the period of
 * one channel affects the period of all 16 PWM outमाला_दो!
 * However, the ratio between each configured duty cycle and the chip-wide
 * period reमुख्यs स्थिरant, because the OFF समय is set in proportion to the
 * counter range.
 */

#घोषणा PCA9685_MODE1		0x00
#घोषणा PCA9685_MODE2		0x01
#घोषणा PCA9685_SUBADDR1	0x02
#घोषणा PCA9685_SUBADDR2	0x03
#घोषणा PCA9685_SUBADDR3	0x04
#घोषणा PCA9685_ALLCALLADDR	0x05
#घोषणा PCA9685_LEDX_ON_L	0x06
#घोषणा PCA9685_LEDX_ON_H	0x07
#घोषणा PCA9685_LEDX_OFF_L	0x08
#घोषणा PCA9685_LEDX_OFF_H	0x09

#घोषणा PCA9685_ALL_LED_ON_L	0xFA
#घोषणा PCA9685_ALL_LED_ON_H	0xFB
#घोषणा PCA9685_ALL_LED_OFF_L	0xFC
#घोषणा PCA9685_ALL_LED_OFF_H	0xFD
#घोषणा PCA9685_PRESCALE	0xFE

#घोषणा PCA9685_PRESCALE_MIN	0x03	/* => max. frequency of 1526 Hz */
#घोषणा PCA9685_PRESCALE_MAX	0xFF	/* => min. frequency of 24 Hz */

#घोषणा PCA9685_COUNTER_RANGE	4096
#घोषणा PCA9685_OSC_CLOCK_MHZ	25	/* Internal oscillator with 25 MHz */

#घोषणा PCA9685_NUMREGS		0xFF
#घोषणा PCA9685_MAXCHAN		0x10

#घोषणा LED_FULL		BIT(4)
#घोषणा MODE1_ALLCALL		BIT(0)
#घोषणा MODE1_SUB3		BIT(1)
#घोषणा MODE1_SUB2		BIT(2)
#घोषणा MODE1_SUB1		BIT(3)
#घोषणा MODE1_SLEEP		BIT(4)
#घोषणा MODE2_INVRT		BIT(4)
#घोषणा MODE2_OUTDRV		BIT(2)

#घोषणा LED_N_ON_H(N)	(PCA9685_LEDX_ON_H + (4 * (N)))
#घोषणा LED_N_ON_L(N)	(PCA9685_LEDX_ON_L + (4 * (N)))
#घोषणा LED_N_OFF_H(N)	(PCA9685_LEDX_OFF_H + (4 * (N)))
#घोषणा LED_N_OFF_L(N)	(PCA9685_LEDX_OFF_L + (4 * (N)))

#घोषणा REG_ON_H(C)	((C) >= PCA9685_MAXCHAN ? PCA9685_ALL_LED_ON_H : LED_N_ON_H((C)))
#घोषणा REG_ON_L(C)	((C) >= PCA9685_MAXCHAN ? PCA9685_ALL_LED_ON_L : LED_N_ON_L((C)))
#घोषणा REG_OFF_H(C)	((C) >= PCA9685_MAXCHAN ? PCA9685_ALL_LED_OFF_H : LED_N_OFF_H((C)))
#घोषणा REG_OFF_L(C)	((C) >= PCA9685_MAXCHAN ? PCA9685_ALL_LED_OFF_L : LED_N_OFF_L((C)))

काष्ठा pca9685 अणु
	काष्ठा pwm_chip chip;
	काष्ठा regmap *regmap;
#अगर IS_ENABLED(CONFIG_GPIOLIB)
	काष्ठा mutex lock;
	काष्ठा gpio_chip gpio;
	DECLARE_BITMAP(pwms_inuse, PCA9685_MAXCHAN + 1);
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा pca9685 *to_pca(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा pca9685, chip);
पूर्ण

/* Helper function to set the duty cycle ratio to duty/4096 (e.g. duty=2048 -> 50%) */
अटल व्योम pca9685_pwm_set_duty(काष्ठा pca9685 *pca, पूर्णांक channel, अचिन्हित पूर्णांक duty)
अणु
	अगर (duty == 0) अणु
		/* Set the full OFF bit, which has the highest precedence */
		regmap_ग_लिखो(pca->regmap, REG_OFF_H(channel), LED_FULL);
	पूर्ण अन्यथा अगर (duty >= PCA9685_COUNTER_RANGE) अणु
		/* Set the full ON bit and clear the full OFF bit */
		regmap_ग_लिखो(pca->regmap, REG_ON_H(channel), LED_FULL);
		regmap_ग_लिखो(pca->regmap, REG_OFF_H(channel), 0);
	पूर्ण अन्यथा अणु
		/* Set OFF समय (clears the full OFF bit) */
		regmap_ग_लिखो(pca->regmap, REG_OFF_L(channel), duty & 0xff);
		regmap_ग_लिखो(pca->regmap, REG_OFF_H(channel), (duty >> 8) & 0xf);
		/* Clear the full ON bit */
		regmap_ग_लिखो(pca->regmap, REG_ON_H(channel), 0);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक pca9685_pwm_get_duty(काष्ठा pca9685 *pca, पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक off_h = 0, val = 0;

	अगर (WARN_ON(channel >= PCA9685_MAXCHAN)) अणु
		/* HW करोes not support पढ़ोing state of "all LEDs" channel */
		वापस 0;
	पूर्ण

	regmap_पढ़ो(pca->regmap, LED_N_OFF_H(channel), &off_h);
	अगर (off_h & LED_FULL) अणु
		/* Full OFF bit is set */
		वापस 0;
	पूर्ण

	regmap_पढ़ो(pca->regmap, LED_N_ON_H(channel), &val);
	अगर (val & LED_FULL) अणु
		/* Full ON bit is set */
		वापस PCA9685_COUNTER_RANGE;
	पूर्ण

	अगर (regmap_पढ़ो(pca->regmap, LED_N_OFF_L(channel), &val)) अणु
		/* Reset val to 0 in हाल पढ़ोing LED_N_OFF_L failed */
		val = 0;
	पूर्ण
	वापस ((off_h & 0xf) << 8) | (val & 0xff);
पूर्ण

#अगर IS_ENABLED(CONFIG_GPIOLIB)
अटल bool pca9685_pwm_test_and_set_inuse(काष्ठा pca9685 *pca, पूर्णांक pwm_idx)
अणु
	bool is_inuse;

	mutex_lock(&pca->lock);
	अगर (pwm_idx >= PCA9685_MAXCHAN) अणु
		/*
		 * "All LEDs" channel:
		 * pretend alपढ़ोy in use अगर any of the PWMs are requested
		 */
		अगर (!biपंचांगap_empty(pca->pwms_inuse, PCA9685_MAXCHAN)) अणु
			is_inuse = true;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Regular channel:
		 * pretend alपढ़ोy in use अगर the "all LEDs" channel is requested
		 */
		अगर (test_bit(PCA9685_MAXCHAN, pca->pwms_inuse)) अणु
			is_inuse = true;
			जाओ out;
		पूर्ण
	पूर्ण
	is_inuse = test_and_set_bit(pwm_idx, pca->pwms_inuse);
out:
	mutex_unlock(&pca->lock);
	वापस is_inuse;
पूर्ण

अटल व्योम pca9685_pwm_clear_inuse(काष्ठा pca9685 *pca, पूर्णांक pwm_idx)
अणु
	mutex_lock(&pca->lock);
	clear_bit(pwm_idx, pca->pwms_inuse);
	mutex_unlock(&pca->lock);
पूर्ण

अटल पूर्णांक pca9685_pwm_gpio_request(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pca9685 *pca = gpiochip_get_data(gpio);

	अगर (pca9685_pwm_test_and_set_inuse(pca, offset))
		वापस -EBUSY;
	pm_runसमय_get_sync(pca->chip.dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pca9685_pwm_gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pca9685 *pca = gpiochip_get_data(gpio);

	वापस pca9685_pwm_get_duty(pca, offset) != 0;
पूर्ण

अटल व्योम pca9685_pwm_gpio_set(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset,
				 पूर्णांक value)
अणु
	काष्ठा pca9685 *pca = gpiochip_get_data(gpio);

	pca9685_pwm_set_duty(pca, offset, value ? PCA9685_COUNTER_RANGE : 0);
पूर्ण

अटल व्योम pca9685_pwm_gpio_मुक्त(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pca9685 *pca = gpiochip_get_data(gpio);

	pca9685_pwm_set_duty(pca, offset, 0);
	pm_runसमय_put(pca->chip.dev);
	pca9685_pwm_clear_inuse(pca, offset);
पूर्ण

अटल पूर्णांक pca9685_pwm_gpio_get_direction(काष्ठा gpio_chip *chip,
					  अचिन्हित पूर्णांक offset)
अणु
	/* Always out */
	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक pca9685_pwm_gpio_direction_input(काष्ठा gpio_chip *gpio,
					    अचिन्हित पूर्णांक offset)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pca9685_pwm_gpio_direction_output(काष्ठा gpio_chip *gpio,
					     अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	pca9685_pwm_gpio_set(gpio, offset, value);

	वापस 0;
पूर्ण

/*
 * The PCA9685 has a bit क्रम turning the PWM output full off or on. Some
 * boards like Intel Galileo actually uses these as normal GPIOs so we
 * expose a GPIO chip here which can exclusively take over the underlying
 * PWM channel.
 */
अटल पूर्णांक pca9685_pwm_gpio_probe(काष्ठा pca9685 *pca)
अणु
	काष्ठा device *dev = pca->chip.dev;

	mutex_init(&pca->lock);

	pca->gpio.label = dev_name(dev);
	pca->gpio.parent = dev;
	pca->gpio.request = pca9685_pwm_gpio_request;
	pca->gpio.मुक्त = pca9685_pwm_gpio_मुक्त;
	pca->gpio.get_direction = pca9685_pwm_gpio_get_direction;
	pca->gpio.direction_input = pca9685_pwm_gpio_direction_input;
	pca->gpio.direction_output = pca9685_pwm_gpio_direction_output;
	pca->gpio.get = pca9685_pwm_gpio_get;
	pca->gpio.set = pca9685_pwm_gpio_set;
	pca->gpio.base = -1;
	pca->gpio.ngpio = PCA9685_MAXCHAN;
	pca->gpio.can_sleep = true;

	वापस devm_gpiochip_add_data(dev, &pca->gpio, pca);
पूर्ण
#अन्यथा
अटल अंतरभूत bool pca9685_pwm_test_and_set_inuse(काष्ठा pca9685 *pca,
						  पूर्णांक pwm_idx)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम
pca9685_pwm_clear_inuse(काष्ठा pca9685 *pca, पूर्णांक pwm_idx)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pca9685_pwm_gpio_probe(काष्ठा pca9685 *pca)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम pca9685_set_sleep_mode(काष्ठा pca9685 *pca, bool enable)
अणु
	regmap_update_bits(pca->regmap, PCA9685_MODE1,
			   MODE1_SLEEP, enable ? MODE1_SLEEP : 0);
	अगर (!enable) अणु
		/* Wait 500us क्रम the oscillator to be back up */
		udelay(500);
	पूर्ण
पूर्ण

अटल पूर्णांक pca9685_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा pca9685 *pca = to_pca(chip);
	अचिन्हित दीर्घ दीर्घ duty, prescale;
	अचिन्हित पूर्णांक val = 0;

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	prescale = DIV_ROUND_CLOSEST_ULL(PCA9685_OSC_CLOCK_MHZ * state->period,
					 PCA9685_COUNTER_RANGE * 1000) - 1;
	अगर (prescale < PCA9685_PRESCALE_MIN || prescale > PCA9685_PRESCALE_MAX) अणु
		dev_err(chip->dev, "pwm not changed: period out of bounds!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!state->enabled) अणु
		pca9685_pwm_set_duty(pca, pwm->hwpwm, 0);
		वापस 0;
	पूर्ण

	regmap_पढ़ो(pca->regmap, PCA9685_PRESCALE, &val);
	अगर (prescale != val) अणु
		/*
		 * Putting the chip briefly पूर्णांकo SLEEP mode
		 * at this poपूर्णांक won't पूर्णांकerfere with the
		 * pm_runसमय framework, because the pm_runसमय
		 * state is guaranteed active here.
		 */
		/* Put chip पूर्णांकo sleep mode */
		pca9685_set_sleep_mode(pca, true);

		/* Change the chip-wide output frequency */
		regmap_ग_लिखो(pca->regmap, PCA9685_PRESCALE, prescale);

		/* Wake the chip up */
		pca9685_set_sleep_mode(pca, false);
	पूर्ण

	duty = PCA9685_COUNTER_RANGE * state->duty_cycle;
	duty = DIV_ROUND_UP_ULL(duty, state->period);
	pca9685_pwm_set_duty(pca, pwm->hwpwm, duty);
	वापस 0;
पूर्ण

अटल व्योम pca9685_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				  काष्ठा pwm_state *state)
अणु
	काष्ठा pca9685 *pca = to_pca(chip);
	अचिन्हित दीर्घ दीर्घ duty;
	अचिन्हित पूर्णांक val = 0;

	/* Calculate (chip-wide) period from prescale value */
	regmap_पढ़ो(pca->regmap, PCA9685_PRESCALE, &val);
	/*
	 * PCA9685_OSC_CLOCK_MHZ is 25, i.e. an पूर्णांकeger भागider of 1000.
	 * The following calculation is thereक्रमe only a multiplication
	 * and we are not losing precision.
	 */
	state->period = (PCA9685_COUNTER_RANGE * 1000 / PCA9685_OSC_CLOCK_MHZ) *
			(val + 1);

	/* The (per-channel) polarity is fixed */
	state->polarity = PWM_POLARITY_NORMAL;

	अगर (pwm->hwpwm >= PCA9685_MAXCHAN) अणु
		/*
		 * The "all LEDs" channel करोes not support HW पढ़ोout
		 * Return 0 and disabled क्रम backwards compatibility
		 */
		state->duty_cycle = 0;
		state->enabled = false;
		वापस;
	पूर्ण

	state->enabled = true;
	duty = pca9685_pwm_get_duty(pca, pwm->hwpwm);
	state->duty_cycle = DIV_ROUND_DOWN_ULL(duty * state->period, PCA9685_COUNTER_RANGE);
पूर्ण

अटल पूर्णांक pca9685_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pca9685 *pca = to_pca(chip);

	अगर (pca9685_pwm_test_and_set_inuse(pca, pwm->hwpwm))
		वापस -EBUSY;
	pm_runसमय_get_sync(chip->dev);

	वापस 0;
पूर्ण

अटल व्योम pca9685_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pca9685 *pca = to_pca(chip);

	pca9685_pwm_set_duty(pca, pwm->hwpwm, 0);
	pm_runसमय_put(chip->dev);
	pca9685_pwm_clear_inuse(pca, pwm->hwpwm);
पूर्ण

अटल स्थिर काष्ठा pwm_ops pca9685_pwm_ops = अणु
	.apply = pca9685_pwm_apply,
	.get_state = pca9685_pwm_get_state,
	.request = pca9685_pwm_request,
	.मुक्त = pca9685_pwm_मुक्त,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config pca9685_regmap_i2c_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = PCA9685_NUMREGS,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक pca9685_pwm_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pca9685 *pca;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	pca = devm_kzalloc(&client->dev, माप(*pca), GFP_KERNEL);
	अगर (!pca)
		वापस -ENOMEM;

	pca->regmap = devm_regmap_init_i2c(client, &pca9685_regmap_i2c_config);
	अगर (IS_ERR(pca->regmap)) अणु
		ret = PTR_ERR(pca->regmap);
		dev_err(&client->dev, "Failed to initialize register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, pca);

	regmap_पढ़ो(pca->regmap, PCA9685_MODE2, &reg);

	अगर (device_property_पढ़ो_bool(&client->dev, "invert"))
		reg |= MODE2_INVRT;
	अन्यथा
		reg &= ~MODE2_INVRT;

	अगर (device_property_पढ़ो_bool(&client->dev, "open-drain"))
		reg &= ~MODE2_OUTDRV;
	अन्यथा
		reg |= MODE2_OUTDRV;

	regmap_ग_लिखो(pca->regmap, PCA9685_MODE2, reg);

	/* Disable all LED ALLCALL and SUBx addresses to aव्योम bus collisions */
	regmap_पढ़ो(pca->regmap, PCA9685_MODE1, &reg);
	reg &= ~(MODE1_ALLCALL | MODE1_SUB1 | MODE1_SUB2 | MODE1_SUB3);
	regmap_ग_लिखो(pca->regmap, PCA9685_MODE1, reg);

	/* Reset OFF रेजिस्टरs to POR शेष */
	regmap_ग_लिखो(pca->regmap, PCA9685_ALL_LED_OFF_L, LED_FULL);
	regmap_ग_लिखो(pca->regmap, PCA9685_ALL_LED_OFF_H, LED_FULL);

	pca->chip.ops = &pca9685_pwm_ops;
	/* Add an extra channel क्रम ALL_LED */
	pca->chip.npwm = PCA9685_MAXCHAN + 1;

	pca->chip.dev = &client->dev;

	ret = pwmchip_add(&pca->chip);
	अगर (ret < 0)
		वापस ret;

	ret = pca9685_pwm_gpio_probe(pca);
	अगर (ret < 0) अणु
		pwmchip_हटाओ(&pca->chip);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&client->dev);

	अगर (pm_runसमय_enabled(&client->dev)) अणु
		/*
		 * Although the chip comes out of घातer-up in the sleep state,
		 * we क्रमce it to sleep in हाल it was woken up beक्रमe
		 */
		pca9685_set_sleep_mode(pca, true);
		pm_runसमय_set_suspended(&client->dev);
	पूर्ण अन्यथा अणु
		/* Wake the chip up अगर runसमय PM is disabled */
		pca9685_set_sleep_mode(pca, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pca9685_pwm_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pca9685 *pca = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&pca->chip);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_enabled(&client->dev)) अणु
		/* Put chip in sleep state अगर runसमय PM is disabled */
		pca9685_set_sleep_mode(pca, true);
	पूर्ण

	pm_runसमय_disable(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pca9685_pwm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pca9685 *pca = i2c_get_clientdata(client);

	pca9685_set_sleep_mode(pca, true);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pca9685_pwm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pca9685 *pca = i2c_get_clientdata(client);

	pca9685_set_sleep_mode(pca, false);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pca9685_id[] = अणु
	अणु "pca9685", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pca9685_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id pca9685_acpi_ids[] = अणु
	अणु "INT3492", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pca9685_acpi_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pca9685_dt_ids[] = अणु
	अणु .compatible = "nxp,pca9685-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pca9685_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops pca9685_pwm_pm = अणु
	SET_RUNTIME_PM_OPS(pca9685_pwm_runसमय_suspend,
			   pca9685_pwm_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver pca9685_i2c_driver = अणु
	.driver = अणु
		.name = "pca9685-pwm",
		.acpi_match_table = ACPI_PTR(pca9685_acpi_ids),
		.of_match_table = of_match_ptr(pca9685_dt_ids),
		.pm = &pca9685_pwm_pm,
	पूर्ण,
	.probe = pca9685_pwm_probe,
	.हटाओ = pca9685_pwm_हटाओ,
	.id_table = pca9685_id,
पूर्ण;

module_i2c_driver(pca9685_i2c_driver);

MODULE_AUTHOR("Steffen Trumtrar <s.trumtrar@pengutronix.de>");
MODULE_DESCRIPTION("PWM driver for PCA9685");
MODULE_LICENSE("GPL");
