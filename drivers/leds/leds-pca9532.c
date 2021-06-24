<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pca9532.c - 16-bit Led dimmer
 *
 * Copyright (C) 2011 Jan Weitzel
 * Copyright (C) 2008 Riku Voipio
 *
 * Datasheet: http://www.nxp.com/करोcuments/data_sheet/PCA9532.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <linux/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/leds-pca9532.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/* m =  num_leds*/
#घोषणा PCA9532_REG_INPUT(i)	((i) >> 3)
#घोषणा PCA9532_REG_OFFSET(m)	((m) >> 4)
#घोषणा PCA9532_REG_PSC(m, i)	(PCA9532_REG_OFFSET(m) + 0x1 + (i) * 2)
#घोषणा PCA9532_REG_PWM(m, i)	(PCA9532_REG_OFFSET(m) + 0x2 + (i) * 2)
#घोषणा LED_REG(m, led)		(PCA9532_REG_OFFSET(m) + 0x5 + (led >> 2))
#घोषणा LED_NUM(led)		(led & 0x3)
#घोषणा LED_SHIFT(led)		(LED_NUM(led) * 2)
#घोषणा LED_MASK(led)		(0x3 << LED_SHIFT(led))

#घोषणा ldev_to_led(c)       container_of(c, काष्ठा pca9532_led, ldev)

काष्ठा pca9532_chip_info अणु
	u8	num_leds;
पूर्ण;

काष्ठा pca9532_data अणु
	काष्ठा i2c_client *client;
	काष्ठा pca9532_led leds[16];
	काष्ठा mutex update_lock;
	काष्ठा input_dev *idev;
	काष्ठा work_काष्ठा work;
#अगर_घोषित CONFIG_LEDS_PCA9532_GPIO
	काष्ठा gpio_chip gpio;
#पूर्ण_अगर
	स्थिर काष्ठा pca9532_chip_info *chip_info;
	u8 pwm[2];
	u8 psc[2];
पूर्ण;

अटल पूर्णांक pca9532_probe(काष्ठा i2c_client *client,
	स्थिर काष्ठा i2c_device_id *id);
अटल पूर्णांक pca9532_हटाओ(काष्ठा i2c_client *client);

क्रमागत अणु
	pca9530,
	pca9531,
	pca9532,
	pca9533,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pca9532_id[] = अणु
	अणु "pca9530", pca9530 पूर्ण,
	अणु "pca9531", pca9531 पूर्ण,
	अणु "pca9532", pca9532 पूर्ण,
	अणु "pca9533", pca9533 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pca9532_id);

अटल स्थिर काष्ठा pca9532_chip_info pca9532_chip_info_tbl[] = अणु
	[pca9530] = अणु
		.num_leds = 2,
	पूर्ण,
	[pca9531] = अणु
		.num_leds = 8,
	पूर्ण,
	[pca9532] = अणु
		.num_leds = 16,
	पूर्ण,
	[pca9533] = अणु
		.num_leds = 4,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_pca9532_leds_match[] = अणु
	अणु .compatible = "nxp,pca9530", .data = (व्योम *)pca9530 पूर्ण,
	अणु .compatible = "nxp,pca9531", .data = (व्योम *)pca9531 पूर्ण,
	अणु .compatible = "nxp,pca9532", .data = (व्योम *)pca9532 पूर्ण,
	अणु .compatible = "nxp,pca9533", .data = (व्योम *)pca9533 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_pca9532_leds_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pca9532_driver = अणु
	.driver = अणु
		.name = "leds-pca953x",
		.of_match_table = of_match_ptr(of_pca9532_leds_match),
	पूर्ण,
	.probe = pca9532_probe,
	.हटाओ = pca9532_हटाओ,
	.id_table = pca9532_id,
पूर्ण;

/* We have two pwm/blinkers, but 16 possible leds to drive. Additionally,
 * the clever Thecus people are using one pwm to drive the beeper. So,
 * as a compromise we average one pwm to the values requested by all
 * leds that are not ON/OFF.
 * */
अटल पूर्णांक pca9532_calcpwm(काष्ठा i2c_client *client, पूर्णांक pwm, पूर्णांक blink,
	क्रमागत led_brightness value)
अणु
	पूर्णांक a = 0, b = 0, i = 0;
	काष्ठा pca9532_data *data = i2c_get_clientdata(client);
	क्रम (i = 0; i < data->chip_info->num_leds; i++) अणु
		अगर (data->leds[i].type == PCA9532_TYPE_LED &&
			data->leds[i].state == PCA9532_PWM0+pwm) अणु
				a++;
				b += data->leds[i].ldev.brightness;
		पूर्ण
	पूर्ण
	अगर (a == 0) अणु
		dev_err(&client->dev,
		"fear of division by zero %d/%d, wanted %d\n",
			b, a, value);
		वापस -EINVAL;
	पूर्ण
	b = b/a;
	अगर (b > 0xFF)
		वापस -EINVAL;
	data->pwm[pwm] = b;
	data->psc[pwm] = blink;
	वापस 0;
पूर्ण

अटल पूर्णांक pca9532_setpwm(काष्ठा i2c_client *client, पूर्णांक pwm)
अणु
	काष्ठा pca9532_data *data = i2c_get_clientdata(client);
	u8 maxleds = data->chip_info->num_leds;

	mutex_lock(&data->update_lock);
	i2c_smbus_ग_लिखो_byte_data(client, PCA9532_REG_PWM(maxleds, pwm),
		data->pwm[pwm]);
	i2c_smbus_ग_लिखो_byte_data(client, PCA9532_REG_PSC(maxleds, pwm),
		data->psc[pwm]);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

/* Set LED routing */
अटल व्योम pca9532_setled(काष्ठा pca9532_led *led)
अणु
	काष्ठा i2c_client *client = led->client;
	काष्ठा pca9532_data *data = i2c_get_clientdata(client);
	u8 maxleds = data->chip_info->num_leds;
	अक्षर reg;

	mutex_lock(&data->update_lock);
	reg = i2c_smbus_पढ़ो_byte_data(client, LED_REG(maxleds, led->id));
	/* zero led bits */
	reg = reg & ~LED_MASK(led->id);
	/* set the new value */
	reg = reg | (led->state << LED_SHIFT(led->id));
	i2c_smbus_ग_लिखो_byte_data(client, LED_REG(maxleds, led->id), reg);
	mutex_unlock(&data->update_lock);
पूर्ण

अटल पूर्णांक pca9532_set_brightness(काष्ठा led_classdev *led_cdev,
	क्रमागत led_brightness value)
अणु
	पूर्णांक err = 0;
	काष्ठा pca9532_led *led = ldev_to_led(led_cdev);

	अगर (value == LED_OFF)
		led->state = PCA9532_OFF;
	अन्यथा अगर (value == LED_FULL)
		led->state = PCA9532_ON;
	अन्यथा अणु
		led->state = PCA9532_PWM0; /* Thecus: hardcode one pwm */
		err = pca9532_calcpwm(led->client, 0, 0, value);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (led->state == PCA9532_PWM0)
		pca9532_setpwm(led->client, 0);
	pca9532_setled(led);
	वापस err;
पूर्ण

अटल पूर्णांक pca9532_set_blink(काष्ठा led_classdev *led_cdev,
	अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा pca9532_led *led = ldev_to_led(led_cdev);
	काष्ठा i2c_client *client = led->client;
	पूर्णांक psc;
	पूर्णांक err = 0;

	अगर (*delay_on == 0 && *delay_off == 0) अणु
		/* led subप्रणाली ask us क्रम a blink rate */
		*delay_on = 1000;
		*delay_off = 1000;
	पूर्ण
	अगर (*delay_on != *delay_off || *delay_on > 1690 || *delay_on < 6)
		वापस -EINVAL;

	/* Thecus specअगरic: only use PSC/PWM 0 */
	psc = (*delay_on * 152-1)/1000;
	err = pca9532_calcpwm(client, 0, psc, led_cdev->brightness);
	अगर (err)
		वापस err;
	अगर (led->state == PCA9532_PWM0)
		pca9532_setpwm(led->client, 0);
	pca9532_setled(led);

	वापस 0;
पूर्ण

अटल पूर्णांक pca9532_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
	अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा pca9532_data *data = input_get_drvdata(dev);

	अगर (!(type == EV_SND && (code == SND_BELL || code == SND_TONE)))
		वापस -1;

	/* XXX: allow dअगरferent kind of beeps with psc/pwm modअगरications */
	अगर (value > 1 && value < 32767)
		data->pwm[1] = 127;
	अन्यथा
		data->pwm[1] = 0;

	schedule_work(&data->work);

	वापस 0;
पूर्ण

अटल व्योम pca9532_input_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pca9532_data *data =
		container_of(work, काष्ठा pca9532_data, work);
	u8 maxleds = data->chip_info->num_leds;

	mutex_lock(&data->update_lock);
	i2c_smbus_ग_लिखो_byte_data(data->client, PCA9532_REG_PWM(maxleds, 1),
		data->pwm[1]);
	mutex_unlock(&data->update_lock);
पूर्ण

अटल क्रमागत pca9532_state pca9532_getled(काष्ठा pca9532_led *led)
अणु
	काष्ठा i2c_client *client = led->client;
	काष्ठा pca9532_data *data = i2c_get_clientdata(client);
	u8 maxleds = data->chip_info->num_leds;
	अक्षर reg;
	क्रमागत pca9532_state ret;

	mutex_lock(&data->update_lock);
	reg = i2c_smbus_पढ़ो_byte_data(client, LED_REG(maxleds, led->id));
	ret = (reg & LED_MASK(led->id)) >> LED_SHIFT(led->id);
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_LEDS_PCA9532_GPIO
अटल पूर्णांक pca9532_gpio_request_pin(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pca9532_data *data = gpiochip_get_data(gc);
	काष्ठा pca9532_led *led = &data->leds[offset];

	अगर (led->type == PCA9532_TYPE_GPIO)
		वापस 0;

	वापस -EBUSY;
पूर्ण

अटल व्योम pca9532_gpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा pca9532_data *data = gpiochip_get_data(gc);
	काष्ठा pca9532_led *led = &data->leds[offset];

	अगर (val)
		led->state = PCA9532_ON;
	अन्यथा
		led->state = PCA9532_OFF;

	pca9532_setled(led);
पूर्ण

अटल पूर्णांक pca9532_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा pca9532_data *data = gpiochip_get_data(gc);
	अचिन्हित अक्षर reg;

	reg = i2c_smbus_पढ़ो_byte_data(data->client, PCA9532_REG_INPUT(offset));

	वापस !!(reg & (1 << (offset % 8)));
पूर्ण

अटल पूर्णांक pca9532_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	/* To use as input ensure pin is not driven */
	pca9532_gpio_set_value(gc, offset, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pca9532_gpio_direction_output(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक val)
अणु
	pca9532_gpio_set_value(gc, offset, val);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_LEDS_PCA9532_GPIO */

अटल पूर्णांक pca9532_destroy_devices(काष्ठा pca9532_data *data, पूर्णांक n_devs)
अणु
	पूर्णांक i = n_devs;

	अगर (!data)
		वापस -EINVAL;

	जबतक (--i >= 0) अणु
		चयन (data->leds[i].type) अणु
		हाल PCA9532_TYPE_NONE:
		हाल PCA9532_TYPE_GPIO:
			अवरोध;
		हाल PCA9532_TYPE_LED:
			led_classdev_unरेजिस्टर(&data->leds[i].ldev);
			अवरोध;
		हाल PCA9532_TYPE_N2100_BEEP:
			अगर (data->idev != शून्य) अणु
				cancel_work_sync(&data->work);
				data->idev = शून्य;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_LEDS_PCA9532_GPIO
	अगर (data->gpio.parent)
		gpiochip_हटाओ(&data->gpio);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक pca9532_configure(काष्ठा i2c_client *client,
	काष्ठा pca9532_data *data, काष्ठा pca9532_platक्रमm_data *pdata)
अणु
	पूर्णांक i, err = 0;
	पूर्णांक gpios = 0;
	u8 maxleds = data->chip_info->num_leds;

	क्रम (i = 0; i < 2; i++)	अणु
		data->pwm[i] = pdata->pwm[i];
		data->psc[i] = pdata->psc[i];
		i2c_smbus_ग_लिखो_byte_data(client, PCA9532_REG_PWM(maxleds, i),
			data->pwm[i]);
		i2c_smbus_ग_लिखो_byte_data(client, PCA9532_REG_PSC(maxleds, i),
			data->psc[i]);
	पूर्ण

	क्रम (i = 0; i < data->chip_info->num_leds; i++) अणु
		काष्ठा pca9532_led *led = &data->leds[i];
		काष्ठा pca9532_led *pled = &pdata->leds[i];
		led->client = client;
		led->id = i;
		led->type = pled->type;
		चयन (led->type) अणु
		हाल PCA9532_TYPE_NONE:
			अवरोध;
		हाल PCA9532_TYPE_GPIO:
			gpios++;
			अवरोध;
		हाल PCA9532_TYPE_LED:
			अगर (pled->state == PCA9532_KEEP)
				led->state = pca9532_getled(led);
			अन्यथा
				led->state = pled->state;
			led->name = pled->name;
			led->ldev.name = led->name;
			led->ldev.शेष_trigger = pled->शेष_trigger;
			led->ldev.brightness = LED_OFF;
			led->ldev.brightness_set_blocking =
						pca9532_set_brightness;
			led->ldev.blink_set = pca9532_set_blink;
			err = led_classdev_रेजिस्टर(&client->dev, &led->ldev);
			अगर (err < 0) अणु
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led->name);
				जाओ निकास;
			पूर्ण
			pca9532_setled(led);
			अवरोध;
		हाल PCA9532_TYPE_N2100_BEEP:
			BUG_ON(data->idev);
			led->state = PCA9532_PWM1;
			pca9532_setled(led);
			data->idev = devm_input_allocate_device(&client->dev);
			अगर (data->idev == शून्य) अणु
				err = -ENOMEM;
				जाओ निकास;
			पूर्ण
			data->idev->name = pled->name;
			data->idev->phys = "i2c/pca9532";
			data->idev->id.bustype = BUS_HOST;
			data->idev->id.venकरोr = 0x001f;
			data->idev->id.product = 0x0001;
			data->idev->id.version = 0x0100;
			data->idev->evbit[0] = BIT_MASK(EV_SND);
			data->idev->sndbit[0] = BIT_MASK(SND_BELL) |
						BIT_MASK(SND_TONE);
			data->idev->event = pca9532_event;
			input_set_drvdata(data->idev, data);
			INIT_WORK(&data->work, pca9532_input_work);
			err = input_रेजिस्टर_device(data->idev);
			अगर (err) अणु
				cancel_work_sync(&data->work);
				data->idev = शून्य;
				जाओ निकास;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_LEDS_PCA9532_GPIO
	अगर (gpios) अणु
		data->gpio.label = "gpio-pca9532";
		data->gpio.direction_input = pca9532_gpio_direction_input;
		data->gpio.direction_output = pca9532_gpio_direction_output;
		data->gpio.set = pca9532_gpio_set_value;
		data->gpio.get = pca9532_gpio_get_value;
		data->gpio.request = pca9532_gpio_request_pin;
		data->gpio.can_sleep = 1;
		data->gpio.base = pdata->gpio_base;
		data->gpio.ngpio = data->chip_info->num_leds;
		data->gpio.parent = &client->dev;
		data->gpio.owner = THIS_MODULE;

		err = gpiochip_add_data(&data->gpio, data);
		अगर (err) अणु
			/* Use data->gpio.dev as a flag क्रम मुक्तing gpiochip */
			data->gpio.parent = शून्य;
			dev_warn(&client->dev, "could not add gpiochip\n");
		पूर्ण अन्यथा अणु
			dev_info(&client->dev, "gpios %i...%i\n",
				data->gpio.base, data->gpio.base +
				data->gpio.ngpio - 1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;

निकास:
	pca9532_destroy_devices(data, i);
	वापस err;
पूर्ण

अटल काष्ठा pca9532_platक्रमm_data *
pca9532_of_populate_pdata(काष्ठा device *dev, काष्ठा device_node *np)
अणु
	काष्ठा pca9532_platक्रमm_data *pdata;
	काष्ठा device_node *child;
	पूर्णांक devid, maxleds;
	पूर्णांक i = 0;
	स्थिर अक्षर *state;

	devid = (पूर्णांक)(uपूर्णांकptr_t)of_device_get_match_data(dev);
	maxleds = pca9532_chip_info_tbl[devid].num_leds;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->gpio_base = -1;

	of_property_पढ़ो_u8_array(np, "nxp,pwm", &pdata->pwm[0],
				  ARRAY_SIZE(pdata->pwm));
	of_property_पढ़ो_u8_array(np, "nxp,psc", &pdata->psc[0],
				  ARRAY_SIZE(pdata->psc));

	क्रम_each_available_child_of_node(np, child) अणु
		अगर (of_property_पढ़ो_string(child, "label",
					    &pdata->leds[i].name))
			pdata->leds[i].name = child->name;
		of_property_पढ़ो_u32(child, "type", &pdata->leds[i].type);
		of_property_पढ़ो_string(child, "linux,default-trigger",
					&pdata->leds[i].शेष_trigger);
		अगर (!of_property_पढ़ो_string(child, "default-state", &state)) अणु
			अगर (!म_भेद(state, "on"))
				pdata->leds[i].state = PCA9532_ON;
			अन्यथा अगर (!म_भेद(state, "keep"))
				pdata->leds[i].state = PCA9532_KEEP;
		पूर्ण
		अगर (++i >= maxleds) अणु
			of_node_put(child);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pdata;
पूर्ण

अटल पूर्णांक pca9532_probe(काष्ठा i2c_client *client,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक devid;
	काष्ठा pca9532_data *data = i2c_get_clientdata(client);
	काष्ठा pca9532_platक्रमm_data *pca9532_pdata =
			dev_get_platdata(&client->dev);
	काष्ठा device_node *np = dev_of_node(&client->dev);

	अगर (!pca9532_pdata) अणु
		अगर (np) अणु
			pca9532_pdata =
				pca9532_of_populate_pdata(&client->dev, np);
			अगर (IS_ERR(pca9532_pdata))
				वापस PTR_ERR(pca9532_pdata);
		पूर्ण अन्यथा अणु
			dev_err(&client->dev, "no platform data\n");
			वापस -EINVAL;
		पूर्ण
		devid = (पूर्णांक)(uपूर्णांकptr_t)of_device_get_match_data(&client->dev);
	पूर्ण अन्यथा अणु
		devid = id->driver_data;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->chip_info = &pca9532_chip_info_tbl[devid];

	dev_info(&client->dev, "setting platform data\n");
	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	वापस pca9532_configure(client, data, pca9532_pdata);
पूर्ण

अटल पूर्णांक pca9532_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pca9532_data *data = i2c_get_clientdata(client);

	वापस pca9532_destroy_devices(data, data->chip_info->num_leds);
पूर्ण

module_i2c_driver(pca9532_driver);

MODULE_AUTHOR("Riku Voipio");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PCA 9532 LED dimmer");
