<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Christian Mauderer <oss@c-mauderer.de>

/*
 * The driver supports controllers with a very simple SPI protocol:
 * - one LED is controlled by a single byte on MOSI
 * - the value of the byte gives the brightness between two values (lowest to
 *   highest)
 * - no वापस value is necessary (no MISO संकेत)
 *
 * The value क्रम minimum and maximum brightness depends on the device
 * (compatible string).
 *
 * Supported devices:
 * - "ubnt,acb-spi-led": Microcontroller (SONiX 8F26E611LA) based device used
 *   क्रम example in Ubiquiti airCube ISP. Reverse engineered protocol क्रम this
 *   controller:
 *   * Higher two bits set a mode. Lower six bits are a parameter.
 *   * Mode: 00 -> set brightness between 0x00 (min) and 0x3F (max)
 *   * Mode: 01 -> pulsing pattern (min -> max -> min) with an पूर्णांकerval. From
 *     some tests, the period is about (50ms + 102ms * parameter). There is a
 *     slightly dअगरferent pattern starting from 0x10 (दीर्घer gap between the
 *     pulses) but the समय still follows that calculation.
 *   * Mode: 10 -> same as 01 but with only a ramp from min to max. Again a
 *     slight jump in the pattern at 0x10.
 *   * Mode: 11 -> blinking (off -> 25% -> off -> 25% -> ...) with a period of
 *     (105ms * parameter)
 *   NOTE: This driver currently only supports mode 00.
 */

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/mutex.h>
#समावेश <uapi/linux/uleds.h>

काष्ठा spi_byte_chipdef अणु
	/* SPI byte that will be send to चयन the LED off */
	u8	off_value;
	/* SPI byte that will be send to चयन the LED to maximum brightness */
	u8	max_value;
पूर्ण;

काष्ठा spi_byte_led अणु
	काष्ठा led_classdev		ldev;
	काष्ठा spi_device		*spi;
	अक्षर				name[LED_MAX_NAME_SIZE];
	काष्ठा mutex			mutex;
	स्थिर काष्ठा spi_byte_chipdef	*cdef;
पूर्ण;

अटल स्थिर काष्ठा spi_byte_chipdef ubnt_acb_spi_led_cdef = अणु
	.off_value = 0x0,
	.max_value = 0x3F,
पूर्ण;

अटल स्थिर काष्ठा of_device_id spi_byte_dt_ids[] = अणु
	अणु .compatible = "ubnt,acb-spi-led", .data = &ubnt_acb_spi_led_cdef पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, spi_byte_dt_ids);

अटल पूर्णांक spi_byte_brightness_set_blocking(काष्ठा led_classdev *dev,
					    क्रमागत led_brightness brightness)
अणु
	काष्ठा spi_byte_led *led = container_of(dev, काष्ठा spi_byte_led, ldev);
	u8 value;
	पूर्णांक ret;

	value = (u8) brightness + led->cdef->off_value;

	mutex_lock(&led->mutex);
	ret = spi_ग_लिखो(led->spi, &value, माप(value));
	mutex_unlock(&led->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक spi_byte_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device_node *child;
	काष्ठा device *dev = &spi->dev;
	काष्ठा spi_byte_led *led;
	स्थिर अक्षर *name = "leds-spi-byte::";
	स्थिर अक्षर *state;
	पूर्णांक ret;

	अगर (of_get_available_child_count(dev_of_node(dev)) != 1) अणु
		dev_err(dev, "Device must have exactly one LED sub-node.");
		वापस -EINVAL;
	पूर्ण
	child = of_get_next_available_child(dev_of_node(dev), शून्य);

	led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	of_property_पढ़ो_string(child, "label", &name);
	strlcpy(led->name, name, माप(led->name));
	led->spi = spi;
	mutex_init(&led->mutex);
	led->cdef = device_get_match_data(dev);
	led->ldev.name = led->name;
	led->ldev.brightness = LED_OFF;
	led->ldev.max_brightness = led->cdef->max_value - led->cdef->off_value;
	led->ldev.brightness_set_blocking = spi_byte_brightness_set_blocking;

	state = of_get_property(child, "default-state", शून्य);
	अगर (state) अणु
		अगर (!म_भेद(state, "on")) अणु
			led->ldev.brightness = led->ldev.max_brightness;
		पूर्ण अन्यथा अगर (म_भेद(state, "off")) अणु
			/* all other हालs except "off" */
			dev_err(dev, "default-state can only be 'on' or 'off'");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	spi_byte_brightness_set_blocking(&led->ldev,
					 led->ldev.brightness);

	ret = devm_led_classdev_रेजिस्टर(&spi->dev, &led->ldev);
	अगर (ret) अणु
		mutex_destroy(&led->mutex);
		वापस ret;
	पूर्ण
	spi_set_drvdata(spi, led);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_byte_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_byte_led	*led = spi_get_drvdata(spi);

	mutex_destroy(&led->mutex);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver spi_byte_driver = अणु
	.probe		= spi_byte_probe,
	.हटाओ		= spi_byte_हटाओ,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= spi_byte_dt_ids,
	पूर्ण,
पूर्ण;

module_spi_driver(spi_byte_driver);

MODULE_AUTHOR("Christian Mauderer <oss@c-mauderer.de>");
MODULE_DESCRIPTION("single byte SPI LED driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:leds-spi-byte");
