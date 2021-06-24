<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम SMSC USB4604 USB HSIC 4-port 2.0 hub controller driver
 * Based on usb3503 driver
 *
 * Copyright (c) 2012-2013 Dongjin Kim (tobetter@gmail.com)
 * Copyright (c) 2016 Linaro Ltd.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>

क्रमागत usb4604_mode अणु
	USB4604_MODE_UNKNOWN,
	USB4604_MODE_HUB,
	USB4604_MODE_STANDBY,
पूर्ण;

काष्ठा usb4604 अणु
	क्रमागत usb4604_mode	mode;
	काष्ठा device		*dev;
	काष्ठा gpio_desc	*gpio_reset;
पूर्ण;

अटल व्योम usb4604_reset(काष्ठा usb4604 *hub, पूर्णांक state)
अणु
	gpiod_set_value_cansleep(hub->gpio_reset, state);

	/* Wait क्रम i2c logic to come up */
	अगर (state)
		msleep(250);
पूर्ण

अटल पूर्णांक usb4604_connect(काष्ठा usb4604 *hub)
अणु
	काष्ठा device *dev = hub->dev;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक err;
	u8 connect_cmd[] = अणु 0xaa, 0x55, 0x00 पूर्ण;

	usb4604_reset(hub, 1);

	err = i2c_master_send(client, connect_cmd, ARRAY_SIZE(connect_cmd));
	अगर (err < 0) अणु
		usb4604_reset(hub, 0);
		वापस err;
	पूर्ण

	hub->mode = USB4604_MODE_HUB;
	dev_dbg(dev, "switched to HUB mode\n");

	वापस 0;
पूर्ण

अटल पूर्णांक usb4604_चयन_mode(काष्ठा usb4604 *hub, क्रमागत usb4604_mode mode)
अणु
	काष्ठा device *dev = hub->dev;
	पूर्णांक err = 0;

	चयन (mode) अणु
	हाल USB4604_MODE_HUB:
		err = usb4604_connect(hub);
		अवरोध;

	हाल USB4604_MODE_STANDBY:
		usb4604_reset(hub, 0);
		dev_dbg(dev, "switched to STANDBY mode\n");
		अवरोध;

	शेष:
		dev_err(dev, "unknown mode is requested\n");
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक usb4604_probe(काष्ठा usb4604 *hub)
अणु
	काष्ठा device *dev = hub->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_desc *gpio;
	u32 mode = USB4604_MODE_HUB;

	gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);
	hub->gpio_reset = gpio;

	अगर (of_property_पढ़ो_u32(np, "initial-mode", &hub->mode))
		hub->mode = mode;

	वापस usb4604_चयन_mode(hub, hub->mode);
पूर्ण

अटल पूर्णांक usb4604_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा usb4604 *hub;

	hub = devm_kzalloc(&i2c->dev, माप(*hub), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, hub);
	hub->dev = &i2c->dev;

	वापस usb4604_probe(hub);
पूर्ण

अटल पूर्णांक __maybe_unused usb4604_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा usb4604 *hub = i2c_get_clientdata(client);

	usb4604_चयन_mode(hub, USB4604_MODE_STANDBY);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused usb4604_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा usb4604 *hub = i2c_get_clientdata(client);

	usb4604_चयन_mode(hub, hub->mode);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(usb4604_i2c_pm_ops, usb4604_i2c_suspend,
		usb4604_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id usb4604_id[] = अणु
	अणु "usb4604", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, usb4604_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id usb4604_of_match[] = अणु
	अणु .compatible = "smsc,usb4604" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usb4604_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver usb4604_i2c_driver = अणु
	.driver = अणु
		.name = "usb4604",
		.pm = pm_ptr(&usb4604_i2c_pm_ops),
		.of_match_table = of_match_ptr(usb4604_of_match),
	पूर्ण,
	.probe		= usb4604_i2c_probe,
	.id_table	= usb4604_id,
पूर्ण;
module_i2c_driver(usb4604_i2c_driver);

MODULE_DESCRIPTION("USB4604 USB HUB driver");
MODULE_LICENSE("GPL v2");
