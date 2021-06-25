<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Touchkey driver क्रम MELFAS MCS5000/5080 controller
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/mcs.h>
#समावेश <linux/pm.h>

/* MCS5000 Touchkey */
#घोषणा MCS5000_TOUCHKEY_STATUS		0x04
#घोषणा MCS5000_TOUCHKEY_STATUS_PRESS	7
#घोषणा MCS5000_TOUCHKEY_FW		0x0a
#घोषणा MCS5000_TOUCHKEY_BASE_VAL	0x61

/* MCS5080 Touchkey */
#घोषणा MCS5080_TOUCHKEY_STATUS		0x00
#घोषणा MCS5080_TOUCHKEY_STATUS_PRESS	3
#घोषणा MCS5080_TOUCHKEY_FW		0x01
#घोषणा MCS5080_TOUCHKEY_BASE_VAL	0x1

क्रमागत mcs_touchkey_type अणु
	MCS5000_TOUCHKEY,
	MCS5080_TOUCHKEY,
पूर्ण;

काष्ठा mcs_touchkey_chip अणु
	अचिन्हित पूर्णांक status_reg;
	अचिन्हित पूर्णांक pressbit;
	अचिन्हित पूर्णांक press_invert;
	अचिन्हित पूर्णांक baseval;
पूर्ण;

काष्ठा mcs_touchkey_data अणु
	व्योम (*घातeron)(bool);

	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा mcs_touchkey_chip chip;
	अचिन्हित पूर्णांक key_code;
	अचिन्हित पूर्णांक key_val;
	अचिन्हित लघु keycodes[];
पूर्ण;

अटल irqवापस_t mcs_touchkey_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mcs_touchkey_data *data = dev_id;
	काष्ठा mcs_touchkey_chip *chip = &data->chip;
	काष्ठा i2c_client *client = data->client;
	काष्ठा input_dev *input = data->input_dev;
	अचिन्हित पूर्णांक key_val;
	अचिन्हित पूर्णांक pressed;
	पूर्णांक val;

	val = i2c_smbus_पढ़ो_byte_data(client, chip->status_reg);
	अगर (val < 0) अणु
		dev_err(&client->dev, "i2c read error [%d]\n", val);
		जाओ out;
	पूर्ण

	pressed = (val & (1 << chip->pressbit)) >> chip->pressbit;
	अगर (chip->press_invert)
		pressed ^= chip->press_invert;

	/* key_val is 0 when released, so we should use key_val of press. */
	अगर (pressed) अणु
		key_val = val & (0xff >> (8 - chip->pressbit));
		अगर (!key_val)
			जाओ out;
		key_val -= chip->baseval;
		data->key_code = data->keycodes[key_val];
		data->key_val = key_val;
	पूर्ण

	input_event(input, EV_MSC, MSC_SCAN, data->key_val);
	input_report_key(input, data->key_code, pressed);
	input_sync(input);

	dev_dbg(&client->dev, "key %d %d %s\n", data->key_val, data->key_code,
		pressed ? "pressed" : "released");

 out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mcs_touchkey_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा mcs_platक्रमm_data *pdata;
	काष्ठा mcs_touchkey_data *data;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक fw_reg;
	पूर्णांक fw_ver;
	पूर्णांक error;
	पूर्णांक i;

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata) अणु
		dev_err(&client->dev, "no platform data defined\n");
		वापस -EINVAL;
	पूर्ण

	data = kzalloc(काष्ठा_size(data, keycodes, pdata->key_maxval + 1),
		       GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!data || !input_dev) अणु
		dev_err(&client->dev, "Failed to allocate memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	data->client = client;
	data->input_dev = input_dev;

	अगर (id->driver_data == MCS5000_TOUCHKEY) अणु
		data->chip.status_reg = MCS5000_TOUCHKEY_STATUS;
		data->chip.pressbit = MCS5000_TOUCHKEY_STATUS_PRESS;
		data->chip.baseval = MCS5000_TOUCHKEY_BASE_VAL;
		fw_reg = MCS5000_TOUCHKEY_FW;
	पूर्ण अन्यथा अणु
		data->chip.status_reg = MCS5080_TOUCHKEY_STATUS;
		data->chip.pressbit = MCS5080_TOUCHKEY_STATUS_PRESS;
		data->chip.press_invert = 1;
		data->chip.baseval = MCS5080_TOUCHKEY_BASE_VAL;
		fw_reg = MCS5080_TOUCHKEY_FW;
	पूर्ण

	fw_ver = i2c_smbus_पढ़ो_byte_data(client, fw_reg);
	अगर (fw_ver < 0) अणु
		error = fw_ver;
		dev_err(&client->dev, "i2c read error[%d]\n", error);
		जाओ err_मुक्त_mem;
	पूर्ण
	dev_info(&client->dev, "Firmware version: %d\n", fw_ver);

	input_dev->name = "MELFAS MCS Touchkey";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	अगर (!pdata->no_स्वतःrepeat)
		input_dev->evbit[0] |= BIT_MASK(EV_REP);
	input_dev->keycode = data->keycodes;
	input_dev->keycodesize = माप(data->keycodes[0]);
	input_dev->keycodemax = pdata->key_maxval + 1;

	क्रम (i = 0; i < pdata->keymap_size; i++) अणु
		अचिन्हित पूर्णांक val = MCS_KEY_VAL(pdata->keymap[i]);
		अचिन्हित पूर्णांक code = MCS_KEY_CODE(pdata->keymap[i]);

		data->keycodes[val] = code;
		__set_bit(code, input_dev->keybit);
	पूर्ण

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, data);

	अगर (pdata->cfg_pin)
		pdata->cfg_pin();

	अगर (pdata->घातeron) अणु
		data->घातeron = pdata->घातeron;
		data->घातeron(true);
	पूर्ण

	error = request_thपढ़ोed_irq(client->irq, शून्य, mcs_touchkey_पूर्णांकerrupt,
				     IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				     client->dev.driver->name, data);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		जाओ err_मुक्त_irq;

	i2c_set_clientdata(client, data);
	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(client->irq, data);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(data);
	वापस error;
पूर्ण

अटल पूर्णांक mcs_touchkey_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mcs_touchkey_data *data = i2c_get_clientdata(client);

	मुक्त_irq(client->irq, data);
	अगर (data->घातeron)
		data->घातeron(false);
	input_unरेजिस्टर_device(data->input_dev);
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल व्योम mcs_touchkey_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा mcs_touchkey_data *data = i2c_get_clientdata(client);

	अगर (data->घातeron)
		data->घातeron(false);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mcs_touchkey_suspend(काष्ठा device *dev)
अणु
	काष्ठा mcs_touchkey_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	/* Disable the work */
	disable_irq(client->irq);

	/* Finally turn off the घातer */
	अगर (data->घातeron)
		data->घातeron(false);

	वापस 0;
पूर्ण

अटल पूर्णांक mcs_touchkey_resume(काष्ठा device *dev)
अणु
	काष्ठा mcs_touchkey_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	/* Enable the device first */
	अगर (data->घातeron)
		data->घातeron(true);

	/* Enable irq again */
	enable_irq(client->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mcs_touchkey_pm_ops,
			 mcs_touchkey_suspend, mcs_touchkey_resume);

अटल स्थिर काष्ठा i2c_device_id mcs_touchkey_id[] = अणु
	अणु "mcs5000_touchkey", MCS5000_TOUCHKEY पूर्ण,
	अणु "mcs5080_touchkey", MCS5080_TOUCHKEY पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcs_touchkey_id);

अटल काष्ठा i2c_driver mcs_touchkey_driver = अणु
	.driver = अणु
		.name	= "mcs_touchkey",
		.pm	= &mcs_touchkey_pm_ops,
	पूर्ण,
	.probe		= mcs_touchkey_probe,
	.हटाओ		= mcs_touchkey_हटाओ,
	.shutकरोwn       = mcs_touchkey_shutकरोwn,
	.id_table	= mcs_touchkey_id,
पूर्ण;

module_i2c_driver(mcs_touchkey_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_AUTHOR("HeungJun Kim <riverful.kim@samsung.com>");
MODULE_DESCRIPTION("Touchkey driver for MELFAS MCS5000/5080 controller");
MODULE_LICENSE("GPL");
