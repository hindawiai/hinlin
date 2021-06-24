<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011 bct electronic GmbH
 * Copyright 2013 Qtechnology/AS
 *
 * Author: Peter Meerwald <p.meerwald@bct-electronic.com>
 * Author: Ricarकरो Ribalda <ribalda@kernel.org>
 *
 * Based on leds-pca955x.c
 *
 * LED driver क्रम the PCA9633 I2C LED driver (7-bit slave address 0x62)
 * LED driver क्रम the PCA9634/5 I2C LED driver (7-bit slave address set by hw.)
 *
 * Note that hardware blinking violates the leds infraकाष्ठाure driver
 * पूर्णांकerface since the hardware only supports blinking all LEDs with the
 * same delay_on/delay_off rates.  That is, only the LEDs that are set to
 * blink will actually blink but all LEDs that are set to blink will blink
 * in identical fashion.  The delay_on/delay_off values of the last LED
 * that is set to blink will be used क्रम all of the blinking LEDs.
 * Hardware blinking is disabled by शेष but can be enabled by setting
 * the 'blink_type' member in the platform_data struct to 'PCA963X_HW_BLINK'
 * or by adding the 'nxp,hw-blink' property to the DTS.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/leds.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

/* LED select रेजिस्टरs determine the source that drives LED outमाला_दो */
#घोषणा PCA963X_LED_OFF		0x0	/* LED driver off */
#घोषणा PCA963X_LED_ON		0x1	/* LED driver on */
#घोषणा PCA963X_LED_PWM		0x2	/* Controlled through PWM */
#घोषणा PCA963X_LED_GRP_PWM	0x3	/* Controlled through PWM/GRPPWM */

#घोषणा PCA963X_MODE2_OUTDRV	0x04	/* Open-drain or totem pole */
#घोषणा PCA963X_MODE2_INVRT	0x10	/* Normal or inverted direction */
#घोषणा PCA963X_MODE2_DMBLNK	0x20	/* Enable blinking */

#घोषणा PCA963X_MODE1		0x00
#घोषणा PCA963X_MODE2		0x01
#घोषणा PCA963X_PWM_BASE	0x02

क्रमागत pca963x_type अणु
	pca9633,
	pca9634,
	pca9635,
पूर्ण;

काष्ठा pca963x_chipdef अणु
	u8			grppwm;
	u8			grpfreq;
	u8			leकरोut_base;
	पूर्णांक			n_leds;
	अचिन्हित पूर्णांक		scaling;
पूर्ण;

अटल काष्ठा pca963x_chipdef pca963x_chipdefs[] = अणु
	[pca9633] = अणु
		.grppwm		= 0x6,
		.grpfreq	= 0x7,
		.leकरोut_base	= 0x8,
		.n_leds		= 4,
	पूर्ण,
	[pca9634] = अणु
		.grppwm		= 0xa,
		.grpfreq	= 0xb,
		.leकरोut_base	= 0xc,
		.n_leds		= 8,
	पूर्ण,
	[pca9635] = अणु
		.grppwm		= 0x12,
		.grpfreq	= 0x13,
		.leकरोut_base	= 0x14,
		.n_leds		= 16,
	पूर्ण,
पूर्ण;

/* Total blink period in milliseconds */
#घोषणा PCA963X_BLINK_PERIOD_MIN	42
#घोषणा PCA963X_BLINK_PERIOD_MAX	10667

अटल स्थिर काष्ठा i2c_device_id pca963x_id[] = अणु
	अणु "pca9632", pca9633 पूर्ण,
	अणु "pca9633", pca9633 पूर्ण,
	अणु "pca9634", pca9634 पूर्ण,
	अणु "pca9635", pca9635 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pca963x_id);

काष्ठा pca963x;

काष्ठा pca963x_led अणु
	काष्ठा pca963x *chip;
	काष्ठा led_classdev led_cdev;
	पूर्णांक led_num; /* 0 .. 15 potentially */
	u8 gdc;
	u8 gfrq;
पूर्ण;

काष्ठा pca963x अणु
	काष्ठा pca963x_chipdef *chipdef;
	काष्ठा mutex mutex;
	काष्ठा i2c_client *client;
	अचिन्हित दीर्घ leds_on;
	काष्ठा pca963x_led leds[];
पूर्ण;

अटल पूर्णांक pca963x_brightness(काष्ठा pca963x_led *led,
			      क्रमागत led_brightness brightness)
अणु
	काष्ठा i2c_client *client = led->chip->client;
	काष्ठा pca963x_chipdef *chipdef = led->chip->chipdef;
	u8 leकरोut_addr, leकरोut, mask, val;
	पूर्णांक shअगरt;
	पूर्णांक ret;

	leकरोut_addr = chipdef->leकरोut_base + (led->led_num / 4);
	shअगरt = 2 * (led->led_num % 4);
	mask = 0x3 << shअगरt;
	leकरोut = i2c_smbus_पढ़ो_byte_data(client, leकरोut_addr);

	चयन (brightness) अणु
	हाल LED_FULL:
		val = (leकरोut & ~mask) | (PCA963X_LED_ON << shअगरt);
		ret = i2c_smbus_ग_लिखो_byte_data(client, leकरोut_addr, val);
		अवरोध;
	हाल LED_OFF:
		val = leकरोut & ~mask;
		ret = i2c_smbus_ग_लिखो_byte_data(client, leकरोut_addr, val);
		अवरोध;
	शेष:
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						PCA963X_PWM_BASE +
						led->led_num,
						brightness);
		अगर (ret < 0)
			वापस ret;

		val = (leकरोut & ~mask) | (PCA963X_LED_PWM << shअगरt);
		ret = i2c_smbus_ग_लिखो_byte_data(client, leकरोut_addr, val);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pca963x_blink(काष्ठा pca963x_led *led)
अणु
	काष्ठा i2c_client *client = led->chip->client;
	काष्ठा pca963x_chipdef *chipdef = led->chip->chipdef;
	u8 leकरोut_addr, leकरोut, mask, val, mode2;
	पूर्णांक shअगरt;

	leकरोut_addr = chipdef->leकरोut_base + (led->led_num / 4);
	shअगरt = 2 * (led->led_num % 4);
	mask = 0x3 << shअगरt;
	mode2 = i2c_smbus_पढ़ो_byte_data(client, PCA963X_MODE2);

	i2c_smbus_ग_लिखो_byte_data(client, chipdef->grppwm, led->gdc);

	i2c_smbus_ग_लिखो_byte_data(client, chipdef->grpfreq, led->gfrq);

	अगर (!(mode2 & PCA963X_MODE2_DMBLNK))
		i2c_smbus_ग_लिखो_byte_data(client, PCA963X_MODE2,
					  mode2 | PCA963X_MODE2_DMBLNK);

	mutex_lock(&led->chip->mutex);

	leकरोut = i2c_smbus_पढ़ो_byte_data(client, leकरोut_addr);
	अगर ((leकरोut & mask) != (PCA963X_LED_GRP_PWM << shअगरt)) अणु
		val = (leकरोut & ~mask) | (PCA963X_LED_GRP_PWM << shअगरt);
		i2c_smbus_ग_लिखो_byte_data(client, leकरोut_addr, val);
	पूर्ण

	mutex_unlock(&led->chip->mutex);
पूर्ण

अटल पूर्णांक pca963x_घातer_state(काष्ठा pca963x_led *led)
अणु
	काष्ठा i2c_client *client = led->chip->client;
	अचिन्हित दीर्घ *leds_on = &led->chip->leds_on;
	अचिन्हित दीर्घ cached_leds = *leds_on;

	अगर (led->led_cdev.brightness)
		set_bit(led->led_num, leds_on);
	अन्यथा
		clear_bit(led->led_num, leds_on);

	अगर (!(*leds_on) != !cached_leds)
		वापस i2c_smbus_ग_लिखो_byte_data(client, PCA963X_MODE1,
						 *leds_on ? 0 : BIT(4));

	वापस 0;
पूर्ण

अटल पूर्णांक pca963x_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा pca963x_led *led;
	पूर्णांक ret;

	led = container_of(led_cdev, काष्ठा pca963x_led, led_cdev);

	mutex_lock(&led->chip->mutex);

	ret = pca963x_brightness(led, value);
	अगर (ret < 0)
		जाओ unlock;
	ret = pca963x_घातer_state(led);

unlock:
	mutex_unlock(&led->chip->mutex);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक pca963x_period_scale(काष्ठा pca963x_led *led,
					 अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक scaling = led->chip->chipdef->scaling;

	वापस scaling ? DIV_ROUND_CLOSEST(val * scaling, 1000) : val;
पूर्ण

अटल पूर्णांक pca963x_blink_set(काष्ठा led_classdev *led_cdev,
			     अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	अचिन्हित दीर्घ समय_on, समय_off, period;
	काष्ठा pca963x_led *led;
	u8 gdc, gfrq;

	led = container_of(led_cdev, काष्ठा pca963x_led, led_cdev);

	समय_on = *delay_on;
	समय_off = *delay_off;

	/* If both zero, pick reasonable शेषs of 500ms each */
	अगर (!समय_on && !समय_off) अणु
		समय_on = 500;
		समय_off = 500;
	पूर्ण

	period = pca963x_period_scale(led, समय_on + समय_off);

	/* If period not supported by hardware, शेष to someting sane. */
	अगर ((period < PCA963X_BLINK_PERIOD_MIN) ||
	    (period > PCA963X_BLINK_PERIOD_MAX)) अणु
		समय_on = 500;
		समय_off = 500;
		period = pca963x_period_scale(led, 1000);
	पूर्ण

	/*
	 * From manual: duty cycle = (GDC / 256) ->
	 *	(समय_on / period) = (GDC / 256) ->
	 *		GDC = ((समय_on * 256) / period)
	 */
	gdc = (pca963x_period_scale(led, समय_on) * 256) / period;

	/*
	 * From manual: period = ((GFRQ + 1) / 24) in seconds.
	 * So, period (in ms) = (((GFRQ + 1) / 24) * 1000) ->
	 *		GFRQ = ((period * 24 / 1000) - 1)
	 */
	gfrq = (period * 24 / 1000) - 1;

	led->gdc = gdc;
	led->gfrq = gfrq;

	pca963x_blink(led);

	*delay_on = समय_on;
	*delay_off = समय_off;

	वापस 0;
पूर्ण

अटल पूर्णांक pca963x_रेजिस्टर_leds(काष्ठा i2c_client *client,
				 काष्ठा pca963x *chip)
अणु
	काष्ठा pca963x_chipdef *chipdef = chip->chipdef;
	काष्ठा pca963x_led *led = chip->leds;
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *child;
	bool hw_blink;
	s32 mode2;
	u32 reg;
	पूर्णांक ret;

	अगर (device_property_पढ़ो_u32(dev, "nxp,period-scale",
				     &chipdef->scaling))
		chipdef->scaling = 1000;

	hw_blink = device_property_पढ़ो_bool(dev, "nxp,hw-blink");

	mode2 = i2c_smbus_पढ़ो_byte_data(client, PCA963X_MODE2);
	अगर (mode2 < 0)
		वापस mode2;

	/* शेष to खोलो-drain unless totem pole (push-pull) is specअगरied */
	अगर (device_property_पढ़ो_bool(dev, "nxp,totem-pole"))
		mode2 |= PCA963X_MODE2_OUTDRV;
	अन्यथा
		mode2 &= ~PCA963X_MODE2_OUTDRV;

	/* शेष to non-inverted output, unless inverted is specअगरied */
	अगर (device_property_पढ़ो_bool(dev, "nxp,inverted-out"))
		mode2 |= PCA963X_MODE2_INVRT;
	अन्यथा
		mode2 &= ~PCA963X_MODE2_INVRT;

	ret = i2c_smbus_ग_लिखो_byte_data(client, PCA963X_MODE2, mode2);
	अगर (ret < 0)
		वापस ret;

	device_क्रम_each_child_node(dev, child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;
		अक्षर शेष_label[32];

		ret = fwnode_property_पढ़ो_u32(child, "reg", &reg);
		अगर (ret || reg >= chipdef->n_leds) अणु
			dev_err(dev, "Invalid 'reg' property for node %pfw\n",
				child);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		led->led_num = reg;
		led->chip = chip;
		led->led_cdev.brightness_set_blocking = pca963x_led_set;
		अगर (hw_blink)
			led->led_cdev.blink_set = pca963x_blink_set;

		init_data.fwnode = child;
		/* क्रम backwards compatibility */
		init_data.devicename = "pca963x";
		snम_लिखो(शेष_label, माप(शेष_label), "%d:%.2x:%u",
			 client->adapter->nr, client->addr, reg);
		init_data.शेष_label = शेष_label;

		ret = devm_led_classdev_रेजिस्टर_ext(dev, &led->led_cdev,
						     &init_data);
		अगर (ret) अणु
			dev_err(dev, "Failed to register LED for node %pfw\n",
				child);
			जाओ err;
		पूर्ण

		++led;
	पूर्ण

	वापस 0;
err:
	fwnode_handle_put(child);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pca963x_match[] = अणु
	अणु .compatible = "nxp,pca9632", पूर्ण,
	अणु .compatible = "nxp,pca9633", पूर्ण,
	अणु .compatible = "nxp,pca9634", पूर्ण,
	अणु .compatible = "nxp,pca9635", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pca963x_match);

अटल पूर्णांक pca963x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा pca963x_chipdef *chipdef;
	काष्ठा pca963x *chip;
	पूर्णांक i, count;

	chipdef = &pca963x_chipdefs[id->driver_data];

	count = device_get_child_node_count(dev);
	अगर (!count || count > chipdef->n_leds) अणु
		dev_err(dev, "Node %pfw must define between 1 and %d LEDs\n",
			dev_fwnode(dev), chipdef->n_leds);
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(dev, काष्ठा_size(chip, leds, count), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);

	mutex_init(&chip->mutex);
	chip->chipdef = chipdef;
	chip->client = client;

	/* Turn off LEDs by शेष*/
	क्रम (i = 0; i < chipdef->n_leds / 4; i++)
		i2c_smbus_ग_लिखो_byte_data(client, chipdef->leकरोut_base + i, 0x00);

	/* Disable LED all-call address, and घातer करोwn initially */
	i2c_smbus_ग_लिखो_byte_data(client, PCA963X_MODE1, BIT(4));

	वापस pca963x_रेजिस्टर_leds(client, chip);
पूर्ण

अटल काष्ठा i2c_driver pca963x_driver = अणु
	.driver = अणु
		.name	= "leds-pca963x",
		.of_match_table = of_pca963x_match,
	पूर्ण,
	.probe	= pca963x_probe,
	.id_table = pca963x_id,
पूर्ण;

module_i2c_driver(pca963x_driver);

MODULE_AUTHOR("Peter Meerwald <p.meerwald@bct-electronic.com>");
MODULE_DESCRIPTION("PCA963X LED driver");
MODULE_LICENSE("GPL v2");
