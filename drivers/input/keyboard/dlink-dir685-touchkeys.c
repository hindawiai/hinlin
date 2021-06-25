<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * D-Link सूची-685 router I2C-based Touchkeys input driver
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * This is a one-off touchkey controller based on the Cypress Semiconductor
 * CY8C214 MCU with some firmware in its पूर्णांकernal 8KB flash. The circuit
 * board inside the router is named E119921
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>

काष्ठा dir685_touchkeys अणु
	काष्ठा device		*dev;
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input;
	अचिन्हित दीर्घ		cur_key;
	u16			codes[7];
पूर्ण;

अटल irqवापस_t dir685_tk_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा dir685_touchkeys *tk = data;
	स्थिर पूर्णांक num_bits = min_t(पूर्णांक, ARRAY_SIZE(tk->codes), 16);
	अचिन्हित दीर्घ changed;
	u8 buf[6];
	अचिन्हित दीर्घ key;
	पूर्णांक i;
	पूर्णांक err;

	स_रखो(buf, 0, माप(buf));
	err = i2c_master_recv(tk->client, buf, माप(buf));
	अगर (err != माप(buf)) अणु
		dev_err(tk->dev, "short read %d\n", err);
		वापस IRQ_HANDLED;
	पूर्ण

	dev_dbg(tk->dev, "IN: %*ph\n", (पूर्णांक)माप(buf), buf);
	key = be16_to_cpup((__be16 *) &buf[4]);

	/* Figure out अगर any bits went high or low since last message */
	changed = tk->cur_key ^ key;
	क्रम_each_set_bit(i, &changed, num_bits) अणु
		dev_dbg(tk->dev, "key %d is %s\n", i,
			test_bit(i, &key) ? "down" : "up");
		input_report_key(tk->input, tk->codes[i], test_bit(i, &key));
	पूर्ण

	/* Store currently करोwn keys */
	tk->cur_key = key;
	input_sync(tk->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dir685_tk_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा dir685_touchkeys *tk;
	काष्ठा device *dev = &client->dev;
	u8 bl_data[] = अणु 0xa7, 0x40 पूर्ण;
	पूर्णांक err;
	पूर्णांक i;

	tk = devm_kzalloc(&client->dev, माप(*tk), GFP_KERNEL);
	अगर (!tk)
		वापस -ENOMEM;

	tk->input = devm_input_allocate_device(dev);
	अगर (!tk->input)
		वापस -ENOMEM;

	tk->client = client;
	tk->dev = dev;

	tk->input->keycodesize = माप(u16);
	tk->input->keycodemax = ARRAY_SIZE(tk->codes);
	tk->input->keycode = tk->codes;
	tk->codes[0] = KEY_UP;
	tk->codes[1] = KEY_DOWN;
	tk->codes[2] = KEY_LEFT;
	tk->codes[3] = KEY_RIGHT;
	tk->codes[4] = KEY_ENTER;
	tk->codes[5] = KEY_WPS_BUTTON;
	/*
	 * This key appears in the venकरोr driver, but I have
	 * not been able to activate it.
	 */
	tk->codes[6] = KEY_RESERVED;

	__set_bit(EV_KEY, tk->input->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(tk->codes); i++)
		__set_bit(tk->codes[i], tk->input->keybit);
	__clear_bit(KEY_RESERVED, tk->input->keybit);

	tk->input->name = "D-Link DIR-685 touchkeys";
	tk->input->id.bustype = BUS_I2C;

	err = input_रेजिस्टर_device(tk->input);
	अगर (err)
		वापस err;

	/* Set the brightness to max level */
	err = i2c_master_send(client, bl_data, माप(bl_data));
	अगर (err != माप(bl_data))
		dev_warn(tk->dev, "error setting brightness level\n");

	अगर (!client->irq) अणु
		dev_err(dev, "no IRQ on the I2C device\n");
		वापस -ENODEV;
	पूर्ण
	err = devm_request_thपढ़ोed_irq(dev, client->irq,
					शून्य, dir685_tk_irq_thपढ़ो,
					IRQF_ONESHOT,
					"dir685-tk", tk);
	अगर (err) अणु
		dev_err(dev, "can't request IRQ\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dir685_tk_id[] = अणु
	अणु "dir685tk", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dir685_tk_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dir685_tk_of_match[] = अणु
	अणु .compatible = "dlink,dir685-touchkeys" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dir685_tk_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver dir685_tk_i2c_driver = अणु
	.driver = अणु
		.name	= "dlink-dir685-touchkeys",
		.of_match_table = of_match_ptr(dir685_tk_of_match),
	पूर्ण,
	.probe		= dir685_tk_probe,
	.id_table	= dir685_tk_id,
पूर्ण;
module_i2c_driver(dir685_tk_i2c_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("D-Link DIR-685 touchkeys driver");
MODULE_LICENSE("GPL");
