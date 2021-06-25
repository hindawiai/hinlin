<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Gateworks I2C PLD GPIO expander
//
// Copyright (C) 2019 Linus Walleij <linus.walleij@linaro.org>
//
// Based on code and know-how from the OpenWrt driver:
// Copyright (C) 2009 Gateworks Corporation
// Authors: Chris Lang, Imre Kaloz

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

/**
 * काष्ठा gw_pld - State container क्रम Gateworks PLD
 * @chip: GPIO chip instance
 * @client: I2C client
 * @out: shaकरोw रेजिस्टर क्रम the output bute
 */
काष्ठा gw_pld अणु
	काष्ठा gpio_chip chip;
	काष्ठा i2c_client *client;
	u8 out;
पूर्ण;

/*
 * The Gateworks I2C PLD chip only expose one पढ़ो and one ग_लिखो रेजिस्टर.
 * Writing a "one" bit (to match the reset state) lets that pin be used as an
 * input. It is an खोलो-drain model.
 */
अटल पूर्णांक gw_pld_input8(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gw_pld *gw = gpiochip_get_data(gc);

	gw->out |= BIT(offset);
	वापस i2c_smbus_ग_लिखो_byte(gw->client, gw->out);
पूर्ण

अटल पूर्णांक gw_pld_get8(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	काष्ठा gw_pld *gw = gpiochip_get_data(gc);
	s32 val;

	val = i2c_smbus_पढ़ो_byte(gw->client);

	वापस (val < 0) ? 0 : !!(val & BIT(offset));
पूर्ण

अटल पूर्णांक gw_pld_output8(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gw_pld *gw = gpiochip_get_data(gc);

	अगर (value)
		gw->out |= BIT(offset);
	अन्यथा
		gw->out &= ~BIT(offset);

	वापस i2c_smbus_ग_लिखो_byte(gw->client, gw->out);
पूर्ण

अटल व्योम gw_pld_set8(काष्ठा gpio_chip *gc, अचिन्हित offset, पूर्णांक value)
अणु
	gw_pld_output8(gc, offset, value);
पूर्ण

अटल पूर्णांक gw_pld_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gw_pld *gw;
	पूर्णांक ret;

	gw = devm_kzalloc(dev, माप(*gw), GFP_KERNEL);
	अगर (!gw)
		वापस -ENOMEM;

	gw->chip.base = -1;
	gw->chip.can_sleep = true;
	gw->chip.parent = dev;
	gw->chip.of_node = np;
	gw->chip.owner = THIS_MODULE;
	gw->chip.label = dev_name(dev);
	gw->chip.ngpio = 8;
	gw->chip.direction_input = gw_pld_input8;
	gw->chip.get = gw_pld_get8;
	gw->chip.direction_output = gw_pld_output8;
	gw->chip.set = gw_pld_set8;
	gw->client = client;

	/*
	 * The Gateworks I2C PLD chip करोes not properly send the acknowledge
	 * bit at all बार, but we can still use the standard i2c_smbus
	 * functions by simply ignoring this bit.
	 */
	client->flags |= I2C_M_IGNORE_NAK;
	gw->out = 0xFF;

	i2c_set_clientdata(client, gw);

	ret = devm_gpiochip_add_data(dev, &gw->chip, gw);
	अगर (ret)
		वापस ret;

	dev_info(dev, "registered Gateworks PLD GPIO device\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id gw_pld_id[] = अणु
	अणु "gw-pld", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, gw_pld_id);

अटल स्थिर काष्ठा of_device_id gw_pld_dt_ids[] = अणु
	अणु .compatible = "gateworks,pld-gpio", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gw_pld_dt_ids);

अटल काष्ठा i2c_driver gw_pld_driver = अणु
	.driver = अणु
		.name = "gw_pld",
		.of_match_table = gw_pld_dt_ids,
	पूर्ण,
	.probe = gw_pld_probe,
	.id_table = gw_pld_id,
पूर्ण;
module_i2c_driver(gw_pld_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
