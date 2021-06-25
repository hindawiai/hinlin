<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * leds-lp3944.c - driver क्रम National Semiconductor LP3944 Funlight Chip
 *
 * Copyright (C) 2009 Antonio Ospite <ospite@studenti.unina.it>
 */

/*
 * I2C driver क्रम National Semiconductor LP3944 Funlight Chip
 * http://www.national.com/pf/LP/LP3944.hपंचांगl
 *
 * This helper chip can drive up to 8 leds, with two programmable DIM modes;
 * it could even be used as a gpio expander but this driver assumes it is used
 * as a led controller.
 *
 * The DIM modes are used to set _blink_ patterns क्रम leds, the pattern is
 * specअगरied supplying two parameters:
 *   - period: from 0s to 1.6s
 *   - duty cycle: percentage of the period the led is on, from 0 to 100
 *
 * LP3944 can be found on Motorola A910 smartphone, where it drives the rgb
 * leds, the camera flash light and the displays backlights.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/mutex.h>
#समावेश <linux/leds-lp3944.h>

/* Read Only Registers */
#घोषणा LP3944_REG_INPUT1     0x00 /* LEDs 0-7 InputRegister (Read Only) */
#घोषणा LP3944_REG_REGISTER1  0x01 /* None (Read Only) */

#घोषणा LP3944_REG_PSC0       0x02 /* Frequency Prescaler 0 (R/W) */
#घोषणा LP3944_REG_PWM0       0x03 /* PWM Register 0 (R/W) */
#घोषणा LP3944_REG_PSC1       0x04 /* Frequency Prescaler 1 (R/W) */
#घोषणा LP3944_REG_PWM1       0x05 /* PWM Register 1 (R/W) */
#घोषणा LP3944_REG_LS0        0x06 /* LEDs 0-3 Selector (R/W) */
#घोषणा LP3944_REG_LS1        0x07 /* LEDs 4-7 Selector (R/W) */

/* These रेजिस्टरs are not used to control leds in LP3944, they can store
 * arbitrary values which the chip will ignore.
 */
#घोषणा LP3944_REG_REGISTER8  0x08
#घोषणा LP3944_REG_REGISTER9  0x09

#घोषणा LP3944_DIM0 0
#घोषणा LP3944_DIM1 1

/* period in ms */
#घोषणा LP3944_PERIOD_MIN 0
#घोषणा LP3944_PERIOD_MAX 1600

/* duty cycle is a percentage */
#घोषणा LP3944_DUTY_CYCLE_MIN 0
#घोषणा LP3944_DUTY_CYCLE_MAX 100

#घोषणा ldev_to_led(c)       container_of(c, काष्ठा lp3944_led_data, ldev)

/* Saved data */
काष्ठा lp3944_led_data अणु
	u8 id;
	क्रमागत lp3944_type type;
	काष्ठा led_classdev ldev;
	काष्ठा i2c_client *client;
पूर्ण;

काष्ठा lp3944_data अणु
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा lp3944_led_data leds[LP3944_LEDS_MAX];
पूर्ण;

अटल पूर्णांक lp3944_reg_पढ़ो(काष्ठा i2c_client *client, u8 reg, u8 *value)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	*value = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक lp3944_reg_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

/**
 * Set the period क्रम DIM status
 *
 * @client: the i2c client
 * @dim: either LP3944_DIM0 or LP3944_DIM1
 * @period: period of a blink, that is a on/off cycle, expressed in ms.
 */
अटल पूर्णांक lp3944_dim_set_period(काष्ठा i2c_client *client, u8 dim, u16 period)
अणु
	u8 psc_reg;
	u8 psc_value;
	पूर्णांक err;

	अगर (dim == LP3944_DIM0)
		psc_reg = LP3944_REG_PSC0;
	अन्यथा अगर (dim == LP3944_DIM1)
		psc_reg = LP3944_REG_PSC1;
	अन्यथा
		वापस -EINVAL;

	/* Convert period to Prescaler value */
	अगर (period > LP3944_PERIOD_MAX)
		वापस -EINVAL;

	psc_value = (period * 255) / LP3944_PERIOD_MAX;

	err = lp3944_reg_ग_लिखो(client, psc_reg, psc_value);

	वापस err;
पूर्ण

/**
 * Set the duty cycle क्रम DIM status
 *
 * @client: the i2c client
 * @dim: either LP3944_DIM0 or LP3944_DIM1
 * @duty_cycle: percentage of a period during which a led is ON
 */
अटल पूर्णांक lp3944_dim_set_dutycycle(काष्ठा i2c_client *client, u8 dim,
				    u8 duty_cycle)
अणु
	u8 pwm_reg;
	u8 pwm_value;
	पूर्णांक err;

	अगर (dim == LP3944_DIM0)
		pwm_reg = LP3944_REG_PWM0;
	अन्यथा अगर (dim == LP3944_DIM1)
		pwm_reg = LP3944_REG_PWM1;
	अन्यथा
		वापस -EINVAL;

	/* Convert duty cycle to PWM value */
	अगर (duty_cycle > LP3944_DUTY_CYCLE_MAX)
		वापस -EINVAL;

	pwm_value = (duty_cycle * 255) / LP3944_DUTY_CYCLE_MAX;

	err = lp3944_reg_ग_लिखो(client, pwm_reg, pwm_value);

	वापस err;
पूर्ण

/**
 * Set the led status
 *
 * @led: a lp3944_led_data काष्ठाure
 * @status: one of LP3944_LED_STATUS_OFF
 *                 LP3944_LED_STATUS_ON
 *                 LP3944_LED_STATUS_DIM0
 *                 LP3944_LED_STATUS_DIM1
 */
अटल पूर्णांक lp3944_led_set(काष्ठा lp3944_led_data *led, u8 status)
अणु
	काष्ठा lp3944_data *data = i2c_get_clientdata(led->client);
	u8 id = led->id;
	u8 reg;
	u8 val = 0;
	पूर्णांक err;

	dev_dbg(&led->client->dev, "%s: %s, status before normalization:%d\n",
		__func__, led->ldev.name, status);

	चयन (id) अणु
	हाल LP3944_LED0:
	हाल LP3944_LED1:
	हाल LP3944_LED2:
	हाल LP3944_LED3:
		reg = LP3944_REG_LS0;
		अवरोध;
	हाल LP3944_LED4:
	हाल LP3944_LED5:
	हाल LP3944_LED6:
	हाल LP3944_LED7:
		id -= LP3944_LED4;
		reg = LP3944_REG_LS1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (status > LP3944_LED_STATUS_DIM1)
		वापस -EINVAL;

	/*
	 * Invert status only when it's < 2 (i.e. 0 or 1) which means it's
	 * controlling the on/off state directly.
	 * When, instead, status is >= 2 करोn't invert it because it would mean
	 * to mess with the hardware blinking mode.
	 */
	अगर (led->type == LP3944_LED_TYPE_LED_INVERTED && status < 2)
		status = 1 - status;

	mutex_lock(&data->lock);
	lp3944_reg_पढ़ो(led->client, reg, &val);

	val &= ~(LP3944_LED_STATUS_MASK << (id << 1));
	val |= (status << (id << 1));

	dev_dbg(&led->client->dev, "%s: %s, reg:%d id:%d status:%d val:%#x\n",
		__func__, led->ldev.name, reg, id, status, val);

	/* set led status */
	err = lp3944_reg_ग_लिखो(led->client, reg, val);
	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल पूर्णांक lp3944_led_set_blink(काष्ठा led_classdev *led_cdev,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा lp3944_led_data *led = ldev_to_led(led_cdev);
	u16 period;
	u8 duty_cycle;
	पूर्णांक err;

	/* units are in ms */
	अगर (*delay_on + *delay_off > LP3944_PERIOD_MAX)
		वापस -EINVAL;

	अगर (*delay_on == 0 && *delay_off == 0) अणु
		/* Special हाल: the leds subप्रणाली requires a शेष user
		 * मित्रly blink pattern क्रम the LED.  Let's blink the led
		 * slowly (1Hz).
		 */
		*delay_on = 500;
		*delay_off = 500;
	पूर्ण

	period = (*delay_on) + (*delay_off);

	/* duty_cycle is the percentage of period during which the led is ON */
	duty_cycle = 100 * (*delay_on) / period;

	/* invert duty cycle क्रम inverted leds, this has the same effect of
	 * swapping delay_on and delay_off
	 */
	अगर (led->type == LP3944_LED_TYPE_LED_INVERTED)
		duty_cycle = 100 - duty_cycle;

	/* NOTE: using always the first DIM mode, this means that all leds
	 * will have the same blinking pattern.
	 *
	 * We could find a way later to have two leds blinking in hardware
	 * with dअगरferent patterns at the same समय, falling back to software
	 * control क्रम the other ones.
	 */
	err = lp3944_dim_set_period(led->client, LP3944_DIM0, period);
	अगर (err)
		वापस err;

	err = lp3944_dim_set_dutycycle(led->client, LP3944_DIM0, duty_cycle);
	अगर (err)
		वापस err;

	dev_dbg(&led->client->dev, "%s: OK hardware accelerated blink!\n",
		__func__);

	lp3944_led_set(led, LP3944_LED_STATUS_DIM0);

	वापस 0;
पूर्ण

अटल पूर्णांक lp3944_led_set_brightness(काष्ठा led_classdev *led_cdev,
				      क्रमागत led_brightness brightness)
अणु
	काष्ठा lp3944_led_data *led = ldev_to_led(led_cdev);

	dev_dbg(&led->client->dev, "%s: %s, %d\n",
		__func__, led_cdev->name, brightness);

	वापस lp3944_led_set(led, !!brightness);
पूर्ण

अटल पूर्णांक lp3944_configure(काष्ठा i2c_client *client,
			    काष्ठा lp3944_data *data,
			    काष्ठा lp3944_platक्रमm_data *pdata)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < pdata->leds_size; i++) अणु
		काष्ठा lp3944_led *pled = &pdata->leds[i];
		काष्ठा lp3944_led_data *led = &data->leds[i];
		led->client = client;
		led->id = i;

		चयन (pled->type) अणु

		हाल LP3944_LED_TYPE_LED:
		हाल LP3944_LED_TYPE_LED_INVERTED:
			led->type = pled->type;
			led->ldev.name = pled->name;
			led->ldev.max_brightness = 1;
			led->ldev.brightness_set_blocking =
						lp3944_led_set_brightness;
			led->ldev.blink_set = lp3944_led_set_blink;
			led->ldev.flags = LED_CORE_SUSPENDRESUME;

			err = led_classdev_रेजिस्टर(&client->dev, &led->ldev);
			अगर (err < 0) अणु
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led->ldev.name);
				जाओ निकास;
			पूर्ण

			/* to expose the शेष value to userspace */
			led->ldev.brightness =
					(क्रमागत led_brightness) pled->status;

			/* Set the शेष led status */
			err = lp3944_led_set(led, pled->status);
			अगर (err < 0) अणु
				dev_err(&client->dev,
					"%s couldn't set STATUS %d\n",
					led->ldev.name, pled->status);
				जाओ निकास;
			पूर्ण
			अवरोध;

		हाल LP3944_LED_TYPE_NONE:
		शेष:
			अवरोध;

		पूर्ण
	पूर्ण
	वापस 0;

निकास:
	अगर (i > 0)
		क्रम (i = i - 1; i >= 0; i--)
			चयन (pdata->leds[i].type) अणु

			हाल LP3944_LED_TYPE_LED:
			हाल LP3944_LED_TYPE_LED_INVERTED:
				led_classdev_unरेजिस्टर(&data->leds[i].ldev);
				अवरोध;

			हाल LP3944_LED_TYPE_NONE:
			शेष:
				अवरोध;
			पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक lp3944_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp3944_platक्रमm_data *lp3944_pdata =
			dev_get_platdata(&client->dev);
	काष्ठा lp3944_data *data;
	पूर्णांक err;

	अगर (lp3944_pdata == शून्य) अणु
		dev_err(&client->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	/* Let's see whether this adapter can support what we need. */
	अगर (!i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "insufficient functionality!\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&client->dev, माप(काष्ठा lp3944_data),
			GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	i2c_set_clientdata(client, data);

	mutex_init(&data->lock);

	err = lp3944_configure(client, data, lp3944_pdata);
	अगर (err < 0)
		वापस err;

	dev_info(&client->dev, "lp3944 enabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक lp3944_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp3944_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा lp3944_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	क्रम (i = 0; i < pdata->leds_size; i++)
		चयन (data->leds[i].type) अणु
		हाल LP3944_LED_TYPE_LED:
		हाल LP3944_LED_TYPE_LED_INVERTED:
			led_classdev_unरेजिस्टर(&data->leds[i].ldev);
			अवरोध;

		हाल LP3944_LED_TYPE_NONE:
		शेष:
			अवरोध;
		पूर्ण

	वापस 0;
पूर्ण

/* lp3944 i2c driver काष्ठा */
अटल स्थिर काष्ठा i2c_device_id lp3944_id[] = अणु
	अणु"lp3944", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lp3944_id);

अटल काष्ठा i2c_driver lp3944_driver = अणु
	.driver   = अणु
		   .name = "lp3944",
	पूर्ण,
	.probe    = lp3944_probe,
	.हटाओ   = lp3944_हटाओ,
	.id_table = lp3944_id,
पूर्ण;

module_i2c_driver(lp3944_driver);

MODULE_AUTHOR("Antonio Ospite <ospite@studenti.unina.it>");
MODULE_DESCRIPTION("LP3944 Fun Light Chip");
MODULE_LICENSE("GPL");
