<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CZ.NIC's Turris Omnia LEDs driver
 *
 * 2020 by Marek Behथजn <kabel@kernel.org>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/led-class-multicolor.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश "leds.h"

#घोषणा OMNIA_BOARD_LEDS	12
#घोषणा OMNIA_LED_NUM_CHANNELS	3

#घोषणा CMD_LED_MODE		3
#घोषणा CMD_LED_MODE_LED(l)	((l) & 0x0f)
#घोषणा CMD_LED_MODE_USER	0x10

#घोषणा CMD_LED_STATE		4
#घोषणा CMD_LED_STATE_LED(l)	((l) & 0x0f)
#घोषणा CMD_LED_STATE_ON	0x10

#घोषणा CMD_LED_COLOR		5
#घोषणा CMD_LED_SET_BRIGHTNESS	7
#घोषणा CMD_LED_GET_BRIGHTNESS	8

काष्ठा omnia_led अणु
	काष्ठा led_classdev_mc mc_cdev;
	काष्ठा mc_subled subled_info[OMNIA_LED_NUM_CHANNELS];
	पूर्णांक reg;
पूर्ण;

#घोषणा to_omnia_led(l)		container_of(l, काष्ठा omnia_led, mc_cdev)

काष्ठा omnia_leds अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	काष्ठा omnia_led leds[];
पूर्ण;

अटल पूर्णांक omnia_led_brightness_set_blocking(काष्ठा led_classdev *cdev,
					     क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev_mc *mc_cdev = lcdev_to_mccdev(cdev);
	काष्ठा omnia_leds *leds = dev_get_drvdata(cdev->dev->parent);
	काष्ठा omnia_led *led = to_omnia_led(mc_cdev);
	u8 buf[5], state;
	पूर्णांक ret;

	mutex_lock(&leds->lock);

	led_mc_calc_color_components(&led->mc_cdev, brightness);

	buf[0] = CMD_LED_COLOR;
	buf[1] = led->reg;
	buf[2] = mc_cdev->subled_info[0].brightness;
	buf[3] = mc_cdev->subled_info[1].brightness;
	buf[4] = mc_cdev->subled_info[2].brightness;

	state = CMD_LED_STATE_LED(led->reg);
	अगर (buf[2] || buf[3] || buf[4])
		state |= CMD_LED_STATE_ON;

	ret = i2c_smbus_ग_लिखो_byte_data(leds->client, CMD_LED_STATE, state);
	अगर (ret >= 0 && (state & CMD_LED_STATE_ON))
		ret = i2c_master_send(leds->client, buf, 5);

	mutex_unlock(&leds->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक omnia_led_रेजिस्टर(काष्ठा i2c_client *client, काष्ठा omnia_led *led,
			      काष्ठा device_node *np)
अणु
	काष्ठा led_init_data init_data = अणुपूर्ण;
	काष्ठा device *dev = &client->dev;
	काष्ठा led_classdev *cdev;
	पूर्णांक ret, color;

	ret = of_property_पढ़ो_u32(np, "reg", &led->reg);
	अगर (ret || led->reg >= OMNIA_BOARD_LEDS) अणु
		dev_warn(dev,
			 "Node %pOF: must contain 'reg' property with values between 0 and %i\n",
			 np, OMNIA_BOARD_LEDS - 1);
		वापस 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "color", &color);
	अगर (ret || color != LED_COLOR_ID_RGB) अणु
		dev_warn(dev,
			 "Node %pOF: must contain 'color' property with value LED_COLOR_ID_RGB\n",
			 np);
		वापस 0;
	पूर्ण

	led->subled_info[0].color_index = LED_COLOR_ID_RED;
	led->subled_info[0].channel = 0;
	led->subled_info[1].color_index = LED_COLOR_ID_GREEN;
	led->subled_info[1].channel = 1;
	led->subled_info[2].color_index = LED_COLOR_ID_BLUE;
	led->subled_info[2].channel = 2;

	led->mc_cdev.subled_info = led->subled_info;
	led->mc_cdev.num_colors = OMNIA_LED_NUM_CHANNELS;

	init_data.fwnode = &np->fwnode;

	cdev = &led->mc_cdev.led_cdev;
	cdev->max_brightness = 255;
	cdev->brightness_set_blocking = omnia_led_brightness_set_blocking;

	/* put the LED पूर्णांकo software mode */
	ret = i2c_smbus_ग_लिखो_byte_data(client, CMD_LED_MODE,
					CMD_LED_MODE_LED(led->reg) |
					CMD_LED_MODE_USER);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot set LED %pOF to software mode: %i\n", np,
			ret);
		वापस ret;
	पूर्ण

	/* disable the LED */
	ret = i2c_smbus_ग_लिखो_byte_data(client, CMD_LED_STATE,
					CMD_LED_STATE_LED(led->reg));
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot set LED %pOF brightness: %i\n", np, ret);
		वापस ret;
	पूर्ण

	ret = devm_led_classdev_multicolor_रेजिस्टर_ext(dev, &led->mc_cdev,
							&init_data);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot register LED %pOF: %i\n", np, ret);
		वापस ret;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * On the front panel of the Turris Omnia router there is also a button which
 * can be used to control the पूर्णांकensity of all the LEDs at once, so that अगर they
 * are too bright, user can dim them.
 * The microcontroller cycles between 8 levels of this global brightness (from
 * 100% to 0%), but this setting can have any पूर्णांकeger value between 0 and 100.
 * It is thereक्रमe convenient to be able to change this setting from software.
 * We expose this setting via a sysfs attribute file called "brightness". This
 * file lives in the device directory of the LED controller, not an inभागidual
 * LED, so it should not confuse users.
 */
अटल sमाप_प्रकार brightness_show(काष्ठा device *dev, काष्ठा device_attribute *a,
			       अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा omnia_leds *leds = i2c_get_clientdata(client);
	पूर्णांक ret;

	mutex_lock(&leds->lock);
	ret = i2c_smbus_पढ़ो_byte_data(client, CMD_LED_GET_BRIGHTNESS);
	mutex_unlock(&leds->lock);

	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार brightness_store(काष्ठा device *dev, काष्ठा device_attribute *a,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा omnia_leds *leds = i2c_get_clientdata(client);
	अचिन्हित दीर्घ brightness;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &brightness))
		वापस -EINVAL;

	अगर (brightness > 100)
		वापस -EINVAL;

	mutex_lock(&leds->lock);
	ret = i2c_smbus_ग_लिखो_byte_data(client, CMD_LED_SET_BRIGHTNESS,
					(u8)brightness);
	mutex_unlock(&leds->lock);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(brightness);

अटल काष्ठा attribute *omnia_led_controller_attrs[] = अणु
	&dev_attr_brightness.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(omnia_led_controller);

अटल पूर्णांक omnia_leds_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev_of_node(dev), *child;
	काष्ठा omnia_leds *leds;
	काष्ठा omnia_led *led;
	पूर्णांक ret, count;

	count = of_get_available_child_count(np);
	अगर (!count) अणु
		dev_err(dev, "LEDs are not defined in device tree!\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (count > OMNIA_BOARD_LEDS) अणु
		dev_err(dev, "Too many LEDs defined in device tree!\n");
		वापस -EINVAL;
	पूर्ण

	leds = devm_kzalloc(dev, काष्ठा_size(leds, leds, count), GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	leds->client = client;
	i2c_set_clientdata(client, leds);

	mutex_init(&leds->lock);

	led = &leds->leds[0];
	क्रम_each_available_child_of_node(np, child) अणु
		ret = omnia_led_रेजिस्टर(client, led, child);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		led += ret;
	पूर्ण

	अगर (devm_device_add_groups(dev, omnia_led_controller_groups))
		dev_warn(dev, "Could not add attribute group!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक omnia_leds_हटाओ(काष्ठा i2c_client *client)
अणु
	u8 buf[5];

	/* put all LEDs पूर्णांकo शेष (HW triggered) mode */
	i2c_smbus_ग_लिखो_byte_data(client, CMD_LED_MODE,
				  CMD_LED_MODE_LED(OMNIA_BOARD_LEDS));

	/* set all LEDs color to [255, 255, 255] */
	buf[0] = CMD_LED_COLOR;
	buf[1] = OMNIA_BOARD_LEDS;
	buf[2] = 255;
	buf[3] = 255;
	buf[4] = 255;

	i2c_master_send(client, buf, 5);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_omnia_leds_match[] = अणु
	अणु .compatible = "cznic,turris-omnia-leds", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id omnia_id[] = अणु
	अणु "omnia", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver omnia_leds_driver = अणु
	.probe		= omnia_leds_probe,
	.हटाओ		= omnia_leds_हटाओ,
	.id_table	= omnia_id,
	.driver		= अणु
		.name	= "leds-turris-omnia",
		.of_match_table = of_omnia_leds_match,
	पूर्ण,
पूर्ण;

module_i2c_driver(omnia_leds_driver);

MODULE_AUTHOR("Marek Behun <kabel@kernel.org>");
MODULE_DESCRIPTION("CZ.NIC's Turris Omnia LEDs");
MODULE_LICENSE("GPL v2");
