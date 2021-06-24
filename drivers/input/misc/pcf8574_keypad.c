<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम a keypad w/16 buttons connected to a PCF8574 I2C I/O expander
 *
 * Copyright 2005-2008 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#घोषणा DRV_NAME "pcf8574_keypad"

अटल स्थिर अचिन्हित अक्षर pcf8574_kp_btncode[] = अणु
	[0] = KEY_RESERVED,
	[1] = KEY_ENTER,
	[2] = KEY_BACKSLASH,
	[3] = KEY_0,
	[4] = KEY_RIGHTBRACE,
	[5] = KEY_C,
	[6] = KEY_9,
	[7] = KEY_8,
	[8] = KEY_7,
	[9] = KEY_B,
	[10] = KEY_6,
	[11] = KEY_5,
	[12] = KEY_4,
	[13] = KEY_A,
	[14] = KEY_3,
	[15] = KEY_2,
	[16] = KEY_1
पूर्ण;

काष्ठा kp_data अणु
	अचिन्हित लघु btncode[ARRAY_SIZE(pcf8574_kp_btncode)];
	काष्ठा input_dev *idev;
	काष्ठा i2c_client *client;
	अक्षर name[64];
	अक्षर phys[32];
	अचिन्हित अक्षर laststate;
पूर्ण;

अटल लघु पढ़ो_state(काष्ठा kp_data *lp)
अणु
	अचिन्हित अक्षर x, y, a, b;

	i2c_smbus_ग_लिखो_byte(lp->client, 240);
	x = 0xF & (~(i2c_smbus_पढ़ो_byte(lp->client) >> 4));

	i2c_smbus_ग_लिखो_byte(lp->client, 15);
	y = 0xF & (~i2c_smbus_पढ़ो_byte(lp->client));

	क्रम (a = 0; x > 0; a++)
		x = x >> 1;
	क्रम (b = 0; y > 0; b++)
		y = y >> 1;

	वापस ((a - 1) * 4) + b;
पूर्ण

अटल irqवापस_t pcf8574_kp_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा kp_data *lp = dev_id;
	अचिन्हित अक्षर nextstate = पढ़ो_state(lp);

	अगर (lp->laststate != nextstate) अणु
		पूर्णांक key_करोwn = nextstate < ARRAY_SIZE(lp->btncode);
		अचिन्हित लघु keycode = key_करोwn ?
			lp->btncode[nextstate] : lp->btncode[lp->laststate];

		input_report_key(lp->idev, keycode, key_करोwn);
		input_sync(lp->idev);

		lp->laststate = nextstate;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcf8574_kp_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक i, ret;
	काष्ठा input_dev *idev;
	काष्ठा kp_data *lp;

	अगर (i2c_smbus_ग_लिखो_byte(client, 240) < 0) अणु
		dev_err(&client->dev, "probe: write fail\n");
		वापस -ENODEV;
	पूर्ण

	lp = kzalloc(माप(*lp), GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;

	idev = input_allocate_device();
	अगर (!idev) अणु
		dev_err(&client->dev, "Can't allocate input device\n");
		ret = -ENOMEM;
		जाओ fail_allocate;
	पूर्ण

	lp->idev = idev;
	lp->client = client;

	idev->evbit[0] = BIT_MASK(EV_KEY);
	idev->keycode = lp->btncode;
	idev->keycodesize = माप(lp->btncode[0]);
	idev->keycodemax = ARRAY_SIZE(lp->btncode);

	क्रम (i = 0; i < ARRAY_SIZE(pcf8574_kp_btncode); i++) अणु
		अगर (lp->btncode[i] <= KEY_MAX) अणु
			lp->btncode[i] = pcf8574_kp_btncode[i];
			__set_bit(lp->btncode[i], idev->keybit);
		पूर्ण
	पूर्ण
	__clear_bit(KEY_RESERVED, idev->keybit);

	प्र_लिखो(lp->name, DRV_NAME);
	प्र_लिखो(lp->phys, "kp_data/input0");

	idev->name = lp->name;
	idev->phys = lp->phys;
	idev->id.bustype = BUS_I2C;
	idev->id.venकरोr = 0x0001;
	idev->id.product = 0x0001;
	idev->id.version = 0x0100;

	lp->laststate = पढ़ो_state(lp);

	ret = request_thपढ़ोed_irq(client->irq, शून्य, pcf8574_kp_irq_handler,
				   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				   DRV_NAME, lp);
	अगर (ret) अणु
		dev_err(&client->dev, "IRQ %d is not free\n", client->irq);
		जाओ fail_मुक्त_device;
	पूर्ण

	ret = input_रेजिस्टर_device(idev);
	अगर (ret) अणु
		dev_err(&client->dev, "input_register_device() failed\n");
		जाओ fail_मुक्त_irq;
	पूर्ण

	i2c_set_clientdata(client, lp);
	वापस 0;

 fail_मुक्त_irq:
	मुक्त_irq(client->irq, lp);
 fail_मुक्त_device:
	input_मुक्त_device(idev);
 fail_allocate:
	kमुक्त(lp);

	वापस ret;
पूर्ण

अटल पूर्णांक pcf8574_kp_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा kp_data *lp = i2c_get_clientdata(client);

	मुक्त_irq(client->irq, lp);

	input_unरेजिस्टर_device(lp->idev);
	kमुक्त(lp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pcf8574_kp_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8574_kp_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	disable_irq(client->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pcf8574_kp_pm_ops = अणु
	.suspend	= pcf8574_kp_suspend,
	.resume		= pcf8574_kp_resume,
पूर्ण;

#अन्यथा
# define pcf8574_kp_resume  शून्य
# define pcf8574_kp_suspend शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id pcf8574_kp_id[] = अणु
	अणु DRV_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf8574_kp_id);

अटल काष्ठा i2c_driver pcf8574_kp_driver = अणु
	.driver = अणु
		.name  = DRV_NAME,
#अगर_घोषित CONFIG_PM
		.pm = &pcf8574_kp_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe    = pcf8574_kp_probe,
	.हटाओ   = pcf8574_kp_हटाओ,
	.id_table = pcf8574_kp_id,
पूर्ण;

module_i2c_driver(pcf8574_kp_driver);

MODULE_AUTHOR("Michael Hennerich");
MODULE_DESCRIPTION("Keypad input driver for 16 keys connected to PCF8574");
MODULE_LICENSE("GPL");
