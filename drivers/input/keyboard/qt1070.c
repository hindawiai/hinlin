<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Aपंचांगel AT42QT1070 QTouch Sensor Controller
 *
 *  Copyright (C) 2011 Aपंचांगel
 *
 *  Authors: Bo Shen <voice.shen@aपंचांगel.com>
 *
 *  Base on AT42QT2160 driver by:
 *  Raphael Derosso Pereira <raphaelpereira@gmail.com>
 *  Copyright (C) 2009
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>

/* Address क्रम each रेजिस्टर */
#घोषणा CHIP_ID            0x00
#घोषणा QT1070_CHIP_ID     0x2E

#घोषणा FW_VERSION         0x01
#घोषणा QT1070_FW_VERSION  0x15

#घोषणा DET_STATUS         0x02

#घोषणा KEY_STATUS         0x03

/* Calibrate */
#घोषणा CALIBRATE_CMD      0x38
#घोषणा QT1070_CAL_TIME    200

/* Reset */
#घोषणा RESET              0x39
#घोषणा QT1070_RESET_TIME  255

/* AT42QT1070 support up to 7 keys */
अटल स्थिर अचिन्हित लघु qt1070_key2code[] = अणु
	KEY_0, KEY_1, KEY_2, KEY_3,
	KEY_4, KEY_5, KEY_6,
पूर्ण;

काष्ठा qt1070_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	अचिन्हित पूर्णांक irq;
	अचिन्हित लघु keycodes[ARRAY_SIZE(qt1070_key2code)];
	u8 last_keys;
पूर्ण;

अटल पूर्णांक qt1070_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0)
		dev_err(&client->dev,
			"can not read register, returned %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक qt1070_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, data);
	अगर (ret < 0)
		dev_err(&client->dev,
			"can not write register, returned %d\n", ret);

	वापस ret;
पूर्ण

अटल bool qt1070_identअगरy(काष्ठा i2c_client *client)
अणु
	पूर्णांक id, ver;

	/* Read Chip ID */
	id = qt1070_पढ़ो(client, CHIP_ID);
	अगर (id != QT1070_CHIP_ID) अणु
		dev_err(&client->dev, "ID %d not supported\n", id);
		वापस false;
	पूर्ण

	/* Read firmware version */
	ver = qt1070_पढ़ो(client, FW_VERSION);
	अगर (ver < 0) अणु
		dev_err(&client->dev, "could not read the firmware version\n");
		वापस false;
	पूर्ण

	dev_info(&client->dev, "AT42QT1070 firmware version %x\n", ver);

	वापस true;
पूर्ण

अटल irqवापस_t qt1070_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qt1070_data *data = dev_id;
	काष्ठा i2c_client *client = data->client;
	काष्ठा input_dev *input = data->input;
	पूर्णांक i;
	u8 new_keys, keyval, mask = 0x01;

	/* Read the detected status रेजिस्टर, thus clearing पूर्णांकerrupt */
	qt1070_पढ़ो(client, DET_STATUS);

	/* Read which key changed */
	new_keys = qt1070_पढ़ो(client, KEY_STATUS);

	क्रम (i = 0; i < ARRAY_SIZE(qt1070_key2code); i++) अणु
		keyval = new_keys & mask;
		अगर ((data->last_keys & mask) != keyval)
			input_report_key(input, data->keycodes[i], keyval);
		mask <<= 1;
	पूर्ण
	input_sync(input);

	data->last_keys = new_keys;
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qt1070_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा qt1070_data *data;
	काष्ठा input_dev *input;
	पूर्णांक i;
	पूर्णांक err;

	err = i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE);
	अगर (!err) अणु
		dev_err(&client->dev, "%s adapter not supported\n",
			dev_driver_string(&client->adapter->dev));
		वापस -ENODEV;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "please assign the irq to this device\n");
		वापस -EINVAL;
	पूर्ण

	/* Identअगरy the qt1070 chip */
	अगर (!qt1070_identअगरy(client))
		वापस -ENODEV;

	data = kzalloc(माप(काष्ठा qt1070_data), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!data || !input) अणु
		dev_err(&client->dev, "insufficient memory\n");
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	data->client = client;
	data->input = input;
	data->irq = client->irq;

	input->name = "AT42QT1070 QTouch Sensor";
	input->dev.parent = &client->dev;
	input->id.bustype = BUS_I2C;

	/* Add the keycode */
	input->keycode = data->keycodes;
	input->keycodesize = माप(data->keycodes[0]);
	input->keycodemax = ARRAY_SIZE(qt1070_key2code);

	__set_bit(EV_KEY, input->evbit);

	क्रम (i = 0; i < ARRAY_SIZE(qt1070_key2code); i++) अणु
		data->keycodes[i] = qt1070_key2code[i];
		__set_bit(qt1070_key2code[i], input->keybit);
	पूर्ण

	/* Calibrate device */
	qt1070_ग_लिखो(client, CALIBRATE_CMD, 1);
	msleep(QT1070_CAL_TIME);

	/* Soft reset */
	qt1070_ग_लिखो(client, RESET, 1);
	msleep(QT1070_RESET_TIME);

	err = request_thपढ़ोed_irq(client->irq, शून्य, qt1070_पूर्णांकerrupt,
				   IRQF_TRIGGER_NONE | IRQF_ONESHOT,
				   client->dev.driver->name, data);
	अगर (err) अणु
		dev_err(&client->dev, "fail to request irq\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	/* Register the input device */
	err = input_रेजिस्टर_device(data->input);
	अगर (err) अणु
		dev_err(&client->dev, "Failed to register input device\n");
		जाओ err_मुक्त_irq;
	पूर्ण

	i2c_set_clientdata(client, data);

	/* Read to clear the chang line */
	qt1070_पढ़ो(client, DET_STATUS);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(client->irq, data);
err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक qt1070_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा qt1070_data *data = i2c_get_clientdata(client);

	/* Release IRQ */
	मुक्त_irq(client->irq, data);

	input_unरेजिस्टर_device(data->input);
	kमुक्त(data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qt1070_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा qt1070_data *data = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(data->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक qt1070_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा qt1070_data *data = i2c_get_clientdata(client);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(data->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(qt1070_pm_ops, qt1070_suspend, qt1070_resume);

अटल स्थिर काष्ठा i2c_device_id qt1070_id[] = अणु
	अणु "qt1070", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, qt1070_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id qt1070_of_match[] = अणु
	अणु .compatible = "qt1070", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qt1070_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver qt1070_driver = अणु
	.driver	= अणु
		.name	= "qt1070",
		.of_match_table = of_match_ptr(qt1070_of_match),
		.pm	= &qt1070_pm_ops,
	पूर्ण,
	.id_table	= qt1070_id,
	.probe		= qt1070_probe,
	.हटाओ		= qt1070_हटाओ,
पूर्ण;

module_i2c_driver(qt1070_driver);

MODULE_AUTHOR("Bo Shen <voice.shen@atmel.com>");
MODULE_DESCRIPTION("Driver for AT42QT1070 QTouch sensor");
MODULE_LICENSE("GPL");
