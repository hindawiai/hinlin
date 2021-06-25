<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम SMSC USB3503 USB 2.0 hub controller driver
 *
 * Copyright (c) 2012-2013 Dongjin Kim (tobetter@gmail.com)
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/usb3503.h>
#समावेश <linux/regmap.h>

#घोषणा USB3503_VIDL		0x00
#घोषणा USB3503_VIDM		0x01
#घोषणा USB3503_PIDL		0x02
#घोषणा USB3503_PIDM		0x03
#घोषणा USB3503_DIDL		0x04
#घोषणा USB3503_DIDM		0x05

#घोषणा USB3503_CFG1		0x06
#घोषणा USB3503_SELF_BUS_PWR	(1 << 7)

#घोषणा USB3503_CFG2		0x07
#घोषणा USB3503_CFG3		0x08
#घोषणा USB3503_NRD		0x09

#घोषणा USB3503_PDS		0x0a

#घोषणा USB3503_SP_ILOCK	0xe7
#घोषणा USB3503_SPILOCK_CONNECT	(1 << 1)
#घोषणा USB3503_SPILOCK_CONFIG	(1 << 0)

#घोषणा USB3503_CFGP		0xee
#घोषणा USB3503_CLKSUSP		(1 << 7)

#घोषणा USB3503_RESET		0xff

काष्ठा usb3503 अणु
	क्रमागत usb3503_mode	mode;
	काष्ठा regmap		*regmap;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	u8	port_off_mask;
	काष्ठा gpio_desc	*पूर्णांकn;
	काष्ठा gpio_desc 	*reset;
	काष्ठा gpio_desc 	*connect;
	bool	secondary_ref_clk;
पूर्ण;

अटल पूर्णांक usb3503_reset(काष्ठा usb3503 *hub, पूर्णांक state)
अणु
	अगर (!state && hub->connect)
		gpiod_set_value_cansleep(hub->connect, 0);

	अगर (hub->reset)
		gpiod_set_value_cansleep(hub->reset, !state);

	/* Wait T_HUBINIT == 4ms क्रम hub logic to stabilize */
	अगर (state)
		usleep_range(4000, 10000);

	वापस 0;
पूर्ण

अटल पूर्णांक usb3503_connect(काष्ठा usb3503 *hub)
अणु
	काष्ठा device *dev = hub->dev;
	पूर्णांक err;

	usb3503_reset(hub, 1);

	अगर (hub->regmap) अणु
		/* SP_ILOCK: set connect_n, config_n क्रम config */
		err = regmap_ग_लिखो(hub->regmap, USB3503_SP_ILOCK,
			   (USB3503_SPILOCK_CONNECT
				 | USB3503_SPILOCK_CONFIG));
		अगर (err < 0) अणु
			dev_err(dev, "SP_ILOCK failed (%d)\n", err);
			वापस err;
		पूर्ण

		/* PDS : Set the ports which are disabled in self-घातered mode. */
		अगर (hub->port_off_mask) अणु
			err = regmap_update_bits(hub->regmap, USB3503_PDS,
					hub->port_off_mask,
					hub->port_off_mask);
			अगर (err < 0) अणु
				dev_err(dev, "PDS failed (%d)\n", err);
				वापस err;
			पूर्ण
		पूर्ण

		/* CFG1 : Set SELF_BUS_PWR, this enables self-घातered operation. */
		err = regmap_update_bits(hub->regmap, USB3503_CFG1,
					 USB3503_SELF_BUS_PWR,
					 USB3503_SELF_BUS_PWR);
		अगर (err < 0) अणु
			dev_err(dev, "CFG1 failed (%d)\n", err);
			वापस err;
		पूर्ण

		/* SP_LOCK: clear connect_n, config_n क्रम hub connect */
		err = regmap_update_bits(hub->regmap, USB3503_SP_ILOCK,
					 (USB3503_SPILOCK_CONNECT
					  | USB3503_SPILOCK_CONFIG), 0);
		अगर (err < 0) अणु
			dev_err(dev, "SP_ILOCK failed (%d)\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (hub->connect)
		gpiod_set_value_cansleep(hub->connect, 1);

	hub->mode = USB3503_MODE_HUB;
	dev_info(dev, "switched to HUB mode\n");

	वापस 0;
पूर्ण

अटल पूर्णांक usb3503_चयन_mode(काष्ठा usb3503 *hub, क्रमागत usb3503_mode mode)
अणु
	काष्ठा device *dev = hub->dev;
	पूर्णांक err = 0;

	चयन (mode) अणु
	हाल USB3503_MODE_HUB:
		err = usb3503_connect(hub);
		अवरोध;

	हाल USB3503_MODE_STANDBY:
		usb3503_reset(hub, 0);
		dev_info(dev, "switched to STANDBY mode\n");
		अवरोध;

	शेष:
		dev_err(dev, "unknown mode is requested\n");
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा regmap_config usb3503_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = USB3503_RESET,
पूर्ण;

अटल पूर्णांक usb3503_probe(काष्ठा usb3503 *hub)
अणु
	काष्ठा device *dev = hub->dev;
	काष्ठा usb3503_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err;
	u32 mode = USB3503_MODE_HUB;
	स्थिर u32 *property;
	क्रमागत gpiod_flags flags;
	पूर्णांक len;

	अगर (pdata) अणु
		hub->port_off_mask	= pdata->port_off_mask;
		hub->mode		= pdata->initial_mode;
	पूर्ण अन्यथा अगर (np) अणु
		u32 rate = 0;
		hub->port_off_mask = 0;

		अगर (!of_property_पढ़ो_u32(np, "refclk-frequency", &rate)) अणु
			चयन (rate) अणु
			हाल 38400000:
			हाल 26000000:
			हाल 19200000:
			हाल 12000000:
				hub->secondary_ref_clk = 0;
				अवरोध;
			हाल 24000000:
			हाल 27000000:
			हाल 25000000:
			हाल 50000000:
				hub->secondary_ref_clk = 1;
				अवरोध;
			शेष:
				dev_err(dev,
					"unsupported reference clock rate (%d)\n",
					(पूर्णांक) rate);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		hub->clk = devm_clk_get_optional(dev, "refclk");
		अगर (IS_ERR(hub->clk)) अणु
			dev_err(dev, "unable to request refclk (%ld)\n",
					PTR_ERR(hub->clk));
			वापस PTR_ERR(hub->clk);
		पूर्ण

		अगर (rate != 0) अणु
			err = clk_set_rate(hub->clk, rate);
			अगर (err) अणु
				dev_err(dev,
					"unable to set reference clock rate to %d\n",
					(पूर्णांक)rate);
				वापस err;
			पूर्ण
		पूर्ण

		err = clk_prepare_enable(hub->clk);
		अगर (err) अणु
			dev_err(dev, "unable to enable reference clock\n");
			वापस err;
		पूर्ण

		property = of_get_property(np, "disabled-ports", &len);
		अगर (property && (len / माप(u32)) > 0) अणु
			पूर्णांक i;
			क्रम (i = 0; i < len / माप(u32); i++) अणु
				u32 port = be32_to_cpu(property[i]);
				अगर ((1 <= port) && (port <= 3))
					hub->port_off_mask |= (1 << port);
			पूर्ण
		पूर्ण

		of_property_पढ़ो_u32(np, "initial-mode", &mode);
		hub->mode = mode;
	पूर्ण

	अगर (hub->secondary_ref_clk)
		flags = GPIOD_OUT_LOW;
	अन्यथा
		flags = GPIOD_OUT_HIGH;
	hub->पूर्णांकn = devm_gpiod_get_optional(dev, "intn", flags);
	अगर (IS_ERR(hub->पूर्णांकn))
		वापस PTR_ERR(hub->पूर्णांकn);
	अगर (hub->पूर्णांकn)
		gpiod_set_consumer_name(hub->पूर्णांकn, "usb3503 intn");

	hub->connect = devm_gpiod_get_optional(dev, "connect", GPIOD_OUT_LOW);
	अगर (IS_ERR(hub->connect))
		वापस PTR_ERR(hub->connect);
	अगर (hub->connect)
		gpiod_set_consumer_name(hub->connect, "usb3503 connect");

	hub->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(hub->reset))
		वापस PTR_ERR(hub->reset);
	अगर (hub->reset) अणु
		/* Datasheet defines a hardware reset to be at least 100us */
		usleep_range(100, 10000);
		gpiod_set_consumer_name(hub->reset, "usb3503 reset");
	पूर्ण

	अगर (hub->port_off_mask && !hub->regmap)
		dev_err(dev, "Ports disabled with no control interface\n");

	usb3503_चयन_mode(hub, hub->mode);

	dev_info(dev, "%s: probed in %s mode\n", __func__,
			(hub->mode == USB3503_MODE_HUB) ? "hub" : "standby");

	वापस 0;
पूर्ण

अटल पूर्णांक usb3503_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा usb3503 *hub;
	पूर्णांक err;

	hub = devm_kzalloc(&i2c->dev, माप(काष्ठा usb3503), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, hub);
	hub->regmap = devm_regmap_init_i2c(i2c, &usb3503_regmap_config);
	अगर (IS_ERR(hub->regmap)) अणु
		err = PTR_ERR(hub->regmap);
		dev_err(&i2c->dev, "Failed to initialise regmap: %d\n", err);
		वापस err;
	पूर्ण
	hub->dev = &i2c->dev;

	वापस usb3503_probe(hub);
पूर्ण

अटल पूर्णांक usb3503_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा usb3503 *hub;

	hub = i2c_get_clientdata(i2c);
	clk_disable_unprepare(hub->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक usb3503_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb3503 *hub;

	hub = devm_kzalloc(&pdev->dev, माप(काष्ठा usb3503), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;
	hub->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, hub);

	वापस usb3503_probe(hub);
पूर्ण

अटल पूर्णांक usb3503_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb3503 *hub;

	hub = platक्रमm_get_drvdata(pdev);
	clk_disable_unprepare(hub->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused usb3503_suspend(काष्ठा usb3503 *hub)
अणु
	usb3503_चयन_mode(hub, USB3503_MODE_STANDBY);
	clk_disable_unprepare(hub->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused usb3503_resume(काष्ठा usb3503 *hub)
अणु
	clk_prepare_enable(hub->clk);
	usb3503_चयन_mode(hub, hub->mode);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused usb3503_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस usb3503_suspend(i2c_get_clientdata(client));
पूर्ण

अटल पूर्णांक __maybe_unused usb3503_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस usb3503_resume(i2c_get_clientdata(client));
पूर्ण

अटल पूर्णांक __maybe_unused usb3503_platक्रमm_suspend(काष्ठा device *dev)
अणु
	वापस usb3503_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक __maybe_unused usb3503_platक्रमm_resume(काष्ठा device *dev)
अणु
	वापस usb3503_resume(dev_get_drvdata(dev));
पूर्ण

अटल SIMPLE_DEV_PM_OPS(usb3503_i2c_pm_ops, usb3503_i2c_suspend,
		usb3503_i2c_resume);

अटल SIMPLE_DEV_PM_OPS(usb3503_platक्रमm_pm_ops, usb3503_platक्रमm_suspend,
		usb3503_platक्रमm_resume);

अटल स्थिर काष्ठा i2c_device_id usb3503_id[] = अणु
	अणु USB3503_I2C_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, usb3503_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id usb3503_of_match[] = अणु
	अणु .compatible = "smsc,usb3503", पूर्ण,
	अणु .compatible = "smsc,usb3503a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, usb3503_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver usb3503_i2c_driver = अणु
	.driver = अणु
		.name = USB3503_I2C_NAME,
		.pm = pm_ptr(&usb3503_i2c_pm_ops),
		.of_match_table = of_match_ptr(usb3503_of_match),
	पूर्ण,
	.probe		= usb3503_i2c_probe,
	.हटाओ		= usb3503_i2c_हटाओ,
	.id_table	= usb3503_id,
पूर्ण;

अटल काष्ठा platक्रमm_driver usb3503_platक्रमm_driver = अणु
	.driver = अणु
		.name = USB3503_I2C_NAME,
		.of_match_table = of_match_ptr(usb3503_of_match),
		.pm = pm_ptr(&usb3503_platक्रमm_pm_ops),
	पूर्ण,
	.probe		= usb3503_platक्रमm_probe,
	.हटाओ		= usb3503_platक्रमm_हटाओ,
पूर्ण;

अटल पूर्णांक __init usb3503_init(व्योम)
अणु
	पूर्णांक err;

	err = i2c_add_driver(&usb3503_i2c_driver);
	अगर (err) अणु
		pr_err("usb3503: Failed to register I2C driver: %d\n", err);
		वापस err;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&usb3503_platक्रमm_driver);
	अगर (err) अणु
		pr_err("usb3503: Failed to register platform driver: %d\n",
		       err);
		i2c_del_driver(&usb3503_i2c_driver);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
module_init(usb3503_init);

अटल व्योम __निकास usb3503_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&usb3503_platक्रमm_driver);
	i2c_del_driver(&usb3503_i2c_driver);
पूर्ण
module_निकास(usb3503_निकास);

MODULE_AUTHOR("Dongjin Kim <tobetter@gmail.com>");
MODULE_DESCRIPTION("USB3503 USB HUB driver");
MODULE_LICENSE("GPL");
