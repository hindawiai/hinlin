<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007-2008 Extreme Engineering Solutions, Inc.
 *
 * Author: Nate Case <nहाल@xes-inc.com>
 *
 * LED driver क्रम various PCA955x I2C LED drivers
 *
 * Supported devices:
 *
 *	Device		Description		7-bit slave address
 *	------		-----------		-------------------
 *	PCA9550		2-bit driver		0x60 .. 0x61
 *	PCA9551		8-bit driver		0x60 .. 0x67
 *	PCA9552		16-bit driver		0x60 .. 0x67
 *	PCA9553/01	4-bit driver		0x62
 *	PCA9553/02	4-bit driver		0x63
 *
 * Philips PCA955x LED driver chips follow a रेजिस्टर map as shown below:
 *
 *	Control Register		Description
 *	----------------		-----------
 *	0x0				Input रेजिस्टर 0
 *					..
 *	NUM_INPUT_REGS - 1		Last Input रेजिस्टर X
 *
 *	NUM_INPUT_REGS			Frequency prescaler 0
 *	NUM_INPUT_REGS + 1		PWM रेजिस्टर 0
 *	NUM_INPUT_REGS + 2		Frequency prescaler 1
 *	NUM_INPUT_REGS + 3		PWM रेजिस्टर 1
 *
 *	NUM_INPUT_REGS + 4		LED selector 0
 *	NUM_INPUT_REGS + 4
 *	    + NUM_LED_REGS - 1		Last LED selector
 *
 *  where NUM_INPUT_REGS and NUM_LED_REGS vary depending on how many
 *  bits the chip supports.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <dt-bindings/leds/leds-pca955x.h>

/* LED select रेजिस्टरs determine the source that drives LED outमाला_दो */
#घोषणा PCA955X_LS_LED_ON	0x0	/* Output LOW */
#घोषणा PCA955X_LS_LED_OFF	0x1	/* Output HI-Z */
#घोषणा PCA955X_LS_BLINK0	0x2	/* Blink at PWM0 rate */
#घोषणा PCA955X_LS_BLINK1	0x3	/* Blink at PWM1 rate */

#घोषणा PCA955X_GPIO_INPUT	LED_OFF
#घोषणा PCA955X_GPIO_HIGH	LED_OFF
#घोषणा PCA955X_GPIO_LOW	LED_FULL

क्रमागत pca955x_type अणु
	pca9550,
	pca9551,
	pca9552,
	ibm_pca9552,
	pca9553,
पूर्ण;

काष्ठा pca955x_chipdef अणु
	पूर्णांक			bits;
	u8			slv_addr;	/* 7-bit slave address mask */
	पूर्णांक			slv_addr_shअगरt;	/* Number of bits to ignore */
पूर्ण;

अटल काष्ठा pca955x_chipdef pca955x_chipdefs[] = अणु
	[pca9550] = अणु
		.bits		= 2,
		.slv_addr	= /* 110000x */ 0x60,
		.slv_addr_shअगरt	= 1,
	पूर्ण,
	[pca9551] = अणु
		.bits		= 8,
		.slv_addr	= /* 1100xxx */ 0x60,
		.slv_addr_shअगरt	= 3,
	पूर्ण,
	[pca9552] = अणु
		.bits		= 16,
		.slv_addr	= /* 1100xxx */ 0x60,
		.slv_addr_shअगरt	= 3,
	पूर्ण,
	[ibm_pca9552] = अणु
		.bits		= 16,
		.slv_addr	= /* 0110xxx */ 0x30,
		.slv_addr_shअगरt	= 3,
	पूर्ण,
	[pca9553] = अणु
		.bits		= 4,
		.slv_addr	= /* 110001x */ 0x62,
		.slv_addr_shअगरt	= 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pca955x_id[] = अणु
	अणु "pca9550", pca9550 पूर्ण,
	अणु "pca9551", pca9551 पूर्ण,
	अणु "pca9552", pca9552 पूर्ण,
	अणु "ibm-pca9552", ibm_pca9552 पूर्ण,
	अणु "pca9553", pca9553 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pca955x_id);

काष्ठा pca955x अणु
	काष्ठा mutex lock;
	काष्ठा pca955x_led *leds;
	काष्ठा pca955x_chipdef	*chipdef;
	काष्ठा i2c_client	*client;
#अगर_घोषित CONFIG_LEDS_PCA955X_GPIO
	काष्ठा gpio_chip gpio;
#पूर्ण_अगर
पूर्ण;

काष्ठा pca955x_led अणु
	काष्ठा pca955x	*pca955x;
	काष्ठा led_classdev	led_cdev;
	पूर्णांक			led_num;	/* 0 .. 15 potentially */
	अक्षर			name[32];
	u32			type;
	स्थिर अक्षर		*शेष_trigger;
पूर्ण;

काष्ठा pca955x_platक्रमm_data अणु
	काष्ठा pca955x_led	*leds;
	पूर्णांक			num_leds;
पूर्ण;

/* 8 bits per input रेजिस्टर */
अटल अंतरभूत पूर्णांक pca95xx_num_input_regs(पूर्णांक bits)
अणु
	वापस (bits + 7) / 8;
पूर्ण

/* 4 bits per LED selector रेजिस्टर */
अटल अंतरभूत पूर्णांक pca95xx_num_led_regs(पूर्णांक bits)
अणु
	वापस (bits + 3)  / 4;
पूर्ण

/*
 * Return an LED selector रेजिस्टर value based on an existing one, with
 * the appropriate 2-bit state value set क्रम the given LED number (0-3).
 */
अटल अंतरभूत u8 pca955x_ledsel(u8 oldval, पूर्णांक led_num, पूर्णांक state)
अणु
	वापस (oldval & (~(0x3 << (led_num << 1)))) |
		((state & 0x3) << (led_num << 1));
पूर्ण

/*
 * Write to frequency prescaler रेजिस्टर, used to program the
 * period of the PWM output.  period = (PSCx + 1) / 38
 */
अटल पूर्णांक pca955x_ग_लिखो_psc(काष्ठा i2c_client *client, पूर्णांक n, u8 val)
अणु
	काष्ठा pca955x *pca955x = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client,
		pca95xx_num_input_regs(pca955x->chipdef->bits) + 2*n,
		val);
	अगर (ret < 0)
		dev_err(&client->dev, "%s: reg 0x%x, val 0x%x, err %d\n",
			__func__, n, val, ret);
	वापस ret;
पूर्ण

/*
 * Write to PWM रेजिस्टर, which determines the duty cycle of the
 * output.  LED is OFF when the count is less than the value of this
 * रेजिस्टर, and ON when it is greater.  If PWMx == 0, LED is always OFF.
 *
 * Duty cycle is (256 - PWMx) / 256
 */
अटल पूर्णांक pca955x_ग_लिखो_pwm(काष्ठा i2c_client *client, पूर्णांक n, u8 val)
अणु
	काष्ठा pca955x *pca955x = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client,
		pca95xx_num_input_regs(pca955x->chipdef->bits) + 1 + 2*n,
		val);
	अगर (ret < 0)
		dev_err(&client->dev, "%s: reg 0x%x, val 0x%x, err %d\n",
			__func__, n, val, ret);
	वापस ret;
पूर्ण

/*
 * Write to LED selector रेजिस्टर, which determines the source that
 * drives the LED output.
 */
अटल पूर्णांक pca955x_ग_लिखो_ls(काष्ठा i2c_client *client, पूर्णांक n, u8 val)
अणु
	काष्ठा pca955x *pca955x = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client,
		pca95xx_num_input_regs(pca955x->chipdef->bits) + 4 + n,
		val);
	अगर (ret < 0)
		dev_err(&client->dev, "%s: reg 0x%x, val 0x%x, err %d\n",
			__func__, n, val, ret);
	वापस ret;
पूर्ण

/*
 * Read the LED selector रेजिस्टर, which determines the source that
 * drives the LED output.
 */
अटल पूर्णांक pca955x_पढ़ो_ls(काष्ठा i2c_client *client, पूर्णांक n, u8 *val)
अणु
	काष्ठा pca955x *pca955x = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client,
		pca95xx_num_input_regs(pca955x->chipdef->bits) + 4 + n);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: reg 0x%x, err %d\n",
			__func__, n, ret);
		वापस ret;
	पूर्ण
	*val = (u8)ret;
	वापस 0;
पूर्ण

अटल पूर्णांक pca955x_led_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	काष्ठा pca955x_led *pca955x_led;
	काष्ठा pca955x *pca955x;
	u8 ls;
	पूर्णांक chip_ls;	/* which LSx to use (0-3 potentially) */
	पूर्णांक ls_led;	/* which set of bits within LSx to use (0-3) */
	पूर्णांक ret;

	pca955x_led = container_of(led_cdev, काष्ठा pca955x_led, led_cdev);
	pca955x = pca955x_led->pca955x;

	chip_ls = pca955x_led->led_num / 4;
	ls_led = pca955x_led->led_num % 4;

	mutex_lock(&pca955x->lock);

	ret = pca955x_पढ़ो_ls(pca955x->client, chip_ls, &ls);
	अगर (ret)
		जाओ out;

	चयन (value) अणु
	हाल LED_FULL:
		ls = pca955x_ledsel(ls, ls_led, PCA955X_LS_LED_ON);
		अवरोध;
	हाल LED_OFF:
		ls = pca955x_ledsel(ls, ls_led, PCA955X_LS_LED_OFF);
		अवरोध;
	हाल LED_HALF:
		ls = pca955x_ledsel(ls, ls_led, PCA955X_LS_BLINK0);
		अवरोध;
	शेष:
		/*
		 * Use PWM1 क्रम all other values.  This has the unwanted
		 * side effect of making all LEDs on the chip share the
		 * same brightness level अगर set to a value other than
		 * OFF, HALF, or FULL.  But, this is probably better than
		 * just turning off क्रम all other values.
		 */
		ret = pca955x_ग_लिखो_pwm(pca955x->client, 1, 255 - value);
		अगर (ret)
			जाओ out;
		ls = pca955x_ledsel(ls, ls_led, PCA955X_LS_BLINK1);
		अवरोध;
	पूर्ण

	ret = pca955x_ग_लिखो_ls(pca955x->client, chip_ls, ls);

out:
	mutex_unlock(&pca955x->lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_LEDS_PCA955X_GPIO
/*
 * Read the INPUT रेजिस्टर, which contains the state of LEDs.
 */
अटल पूर्णांक pca955x_पढ़ो_input(काष्ठा i2c_client *client, पूर्णांक n, u8 *val)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, n);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: reg 0x%x, err %d\n",
			__func__, n, ret);
		वापस ret;
	पूर्ण
	*val = (u8)ret;
	वापस 0;

पूर्ण

अटल पूर्णांक pca955x_gpio_request_pin(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pca955x *pca955x = gpiochip_get_data(gc);
	काष्ठा pca955x_led *led = &pca955x->leds[offset];

	अगर (led->type == PCA955X_TYPE_GPIO)
		वापस 0;

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक pca955x_set_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			     पूर्णांक val)
अणु
	काष्ठा pca955x *pca955x = gpiochip_get_data(gc);
	काष्ठा pca955x_led *led = &pca955x->leds[offset];

	अगर (val)
		वापस pca955x_led_set(&led->led_cdev, PCA955X_GPIO_HIGH);

	वापस pca955x_led_set(&led->led_cdev, PCA955X_GPIO_LOW);
पूर्ण

अटल व्योम pca955x_gpio_set_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
				   पूर्णांक val)
अणु
	pca955x_set_value(gc, offset, val);
पूर्ण

अटल पूर्णांक pca955x_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pca955x *pca955x = gpiochip_get_data(gc);
	काष्ठा pca955x_led *led = &pca955x->leds[offset];
	u8 reg = 0;

	/* There is nothing we can करो about errors */
	pca955x_पढ़ो_input(pca955x->client, led->led_num / 8, &reg);

	वापस !!(reg & (1 << (led->led_num % 8)));
पूर्ण

अटल पूर्णांक pca955x_gpio_direction_input(काष्ठा gpio_chip *gc,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pca955x *pca955x = gpiochip_get_data(gc);
	काष्ठा pca955x_led *led = &pca955x->leds[offset];

	/* To use as input ensure pin is not driven. */
	वापस pca955x_led_set(&led->led_cdev, PCA955X_GPIO_INPUT);
पूर्ण

अटल पूर्णांक pca955x_gpio_direction_output(काष्ठा gpio_chip *gc,
					 अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	वापस pca955x_set_value(gc, offset, val);
पूर्ण
#पूर्ण_अगर /* CONFIG_LEDS_PCA955X_GPIO */

अटल काष्ठा pca955x_platक्रमm_data *
pca955x_get_pdata(काष्ठा i2c_client *client, काष्ठा pca955x_chipdef *chip)
अणु
	काष्ठा pca955x_platक्रमm_data *pdata;
	काष्ठा fwnode_handle *child;
	पूर्णांक count;

	count = device_get_child_node_count(&client->dev);
	अगर (!count || count > chip->bits)
		वापस ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->leds = devm_kसुस्मृति(&client->dev,
				   chip->bits, माप(काष्ठा pca955x_led),
				   GFP_KERNEL);
	अगर (!pdata->leds)
		वापस ERR_PTR(-ENOMEM);

	device_क्रम_each_child_node(&client->dev, child) अणु
		स्थिर अक्षर *name;
		u32 reg;
		पूर्णांक res;

		res = fwnode_property_पढ़ो_u32(child, "reg", &reg);
		अगर ((res != 0) || (reg >= chip->bits))
			जारी;

		res = fwnode_property_पढ़ो_string(child, "label", &name);
		अगर ((res != 0) && is_of_node(child))
			name = to_of_node(child)->name;

		snम_लिखो(pdata->leds[reg].name, माप(pdata->leds[reg].name),
			 "%s", name);

		pdata->leds[reg].type = PCA955X_TYPE_LED;
		fwnode_property_पढ़ो_u32(child, "type", &pdata->leds[reg].type);
		fwnode_property_पढ़ो_string(child, "linux,default-trigger",
					&pdata->leds[reg].शेष_trigger);
	पूर्ण

	pdata->num_leds = chip->bits;

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pca955x_match[] = अणु
	अणु .compatible = "nxp,pca9550", .data = (व्योम *)pca9550 पूर्ण,
	अणु .compatible = "nxp,pca9551", .data = (व्योम *)pca9551 पूर्ण,
	अणु .compatible = "nxp,pca9552", .data = (व्योम *)pca9552 पूर्ण,
	अणु .compatible = "ibm,pca9552", .data = (व्योम *)ibm_pca9552 पूर्ण,
	अणु .compatible = "nxp,pca9553", .data = (व्योम *)pca9553 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pca955x_match);

अटल पूर्णांक pca955x_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pca955x *pca955x;
	काष्ठा pca955x_led *pca955x_led;
	काष्ठा pca955x_chipdef *chip;
	काष्ठा i2c_adapter *adapter;
	पूर्णांक i, err;
	काष्ठा pca955x_platक्रमm_data *pdata;
	पूर्णांक ngpios = 0;

	chip = &pca955x_chipdefs[id->driver_data];
	adapter = client->adapter;
	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata) अणु
		pdata =	pca955x_get_pdata(client, chip);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	/* Make sure the slave address / chip type combo given is possible */
	अगर ((client->addr & ~((1 << chip->slv_addr_shअगरt) - 1)) !=
	    chip->slv_addr) अणु
		dev_err(&client->dev, "invalid slave address %02x\n",
				client->addr);
		वापस -ENODEV;
	पूर्ण

	dev_info(&client->dev, "leds-pca955x: Using %s %d-bit LED driver at "
			"slave address 0x%02x\n",
			client->name, chip->bits, client->addr);

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	अगर (pdata->num_leds != chip->bits) अणु
		dev_err(&client->dev,
			"board info claims %d LEDs on a %d-bit chip\n",
			pdata->num_leds, chip->bits);
		वापस -ENODEV;
	पूर्ण

	pca955x = devm_kzalloc(&client->dev, माप(*pca955x), GFP_KERNEL);
	अगर (!pca955x)
		वापस -ENOMEM;

	pca955x->leds = devm_kसुस्मृति(&client->dev,
			chip->bits, माप(*pca955x_led), GFP_KERNEL);
	अगर (!pca955x->leds)
		वापस -ENOMEM;

	i2c_set_clientdata(client, pca955x);

	mutex_init(&pca955x->lock);
	pca955x->client = client;
	pca955x->chipdef = chip;

	क्रम (i = 0; i < chip->bits; i++) अणु
		pca955x_led = &pca955x->leds[i];
		pca955x_led->led_num = i;
		pca955x_led->pca955x = pca955x;
		pca955x_led->type = pdata->leds[i].type;

		चयन (pca955x_led->type) अणु
		हाल PCA955X_TYPE_NONE:
			अवरोध;
		हाल PCA955X_TYPE_GPIO:
			ngpios++;
			अवरोध;
		हाल PCA955X_TYPE_LED:
			/*
			 * Platक्रमm data can specअगरy LED names and
			 * शेष triggers
			 */
			अगर (pdata->leds[i].name[0] == '\0')
				snम_लिखो(pdata->leds[i].name,
					माप(pdata->leds[i].name), "%d", i);

			snम_लिखो(pca955x_led->name,
				माप(pca955x_led->name), "pca955x:%s",
				pdata->leds[i].name);

			अगर (pdata->leds[i].शेष_trigger)
				pca955x_led->led_cdev.शेष_trigger =
					pdata->leds[i].शेष_trigger;

			pca955x_led->led_cdev.name = pca955x_led->name;
			pca955x_led->led_cdev.brightness_set_blocking =
				pca955x_led_set;

			err = devm_led_classdev_रेजिस्टर(&client->dev,
							&pca955x_led->led_cdev);
			अगर (err)
				वापस err;

			/* Turn off LED */
			err = pca955x_led_set(&pca955x_led->led_cdev, LED_OFF);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	/* PWM0 is used क्रम half brightness or 50% duty cycle */
	err = pca955x_ग_लिखो_pwm(client, 0, 255 - LED_HALF);
	अगर (err)
		वापस err;

	/* PWM1 is used क्रम variable brightness, शेष to OFF */
	err = pca955x_ग_लिखो_pwm(client, 1, 0);
	अगर (err)
		वापस err;

	/* Set to fast frequency so we करो not see flashing */
	err = pca955x_ग_लिखो_psc(client, 0, 0);
	अगर (err)
		वापस err;
	err = pca955x_ग_लिखो_psc(client, 1, 0);
	अगर (err)
		वापस err;

#अगर_घोषित CONFIG_LEDS_PCA955X_GPIO
	अगर (ngpios) अणु
		pca955x->gpio.label = "gpio-pca955x";
		pca955x->gpio.direction_input = pca955x_gpio_direction_input;
		pca955x->gpio.direction_output = pca955x_gpio_direction_output;
		pca955x->gpio.set = pca955x_gpio_set_value;
		pca955x->gpio.get = pca955x_gpio_get_value;
		pca955x->gpio.request = pca955x_gpio_request_pin;
		pca955x->gpio.can_sleep = 1;
		pca955x->gpio.base = -1;
		pca955x->gpio.ngpio = ngpios;
		pca955x->gpio.parent = &client->dev;
		pca955x->gpio.owner = THIS_MODULE;

		err = devm_gpiochip_add_data(&client->dev, &pca955x->gpio,
					     pca955x);
		अगर (err) अणु
			/* Use data->gpio.dev as a flag क्रम मुक्तing gpiochip */
			pca955x->gpio.parent = शून्य;
			dev_warn(&client->dev, "could not add gpiochip\n");
			वापस err;
		पूर्ण
		dev_info(&client->dev, "gpios %i...%i\n",
			 pca955x->gpio.base, pca955x->gpio.base +
			 pca955x->gpio.ngpio - 1);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver pca955x_driver = अणु
	.driver = अणु
		.name	= "leds-pca955x",
		.of_match_table = of_pca955x_match,
	पूर्ण,
	.probe	= pca955x_probe,
	.id_table = pca955x_id,
पूर्ण;

module_i2c_driver(pca955x_driver);

MODULE_AUTHOR("Nate Case <ncase@xes-inc.com>");
MODULE_DESCRIPTION("PCA955x LED driver");
MODULE_LICENSE("GPL v2");
