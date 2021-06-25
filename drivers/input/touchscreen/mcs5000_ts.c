<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mcs5000_ts.c - Touchscreen driver क्रम MELFAS MCS-5000 controller
 *
 * Copyright (C) 2009 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * Based on wm97xx-core.c
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_data/mcs.h>
#समावेश <linux/slab.h>

/* Registers */
#घोषणा MCS5000_TS_STATUS		0x00
#घोषणा STATUS_OFFSET			0
#घोषणा STATUS_NO			(0 << STATUS_OFFSET)
#घोषणा STATUS_INIT			(1 << STATUS_OFFSET)
#घोषणा STATUS_SENSING			(2 << STATUS_OFFSET)
#घोषणा STATUS_COORD			(3 << STATUS_OFFSET)
#घोषणा STATUS_GESTURE			(4 << STATUS_OFFSET)
#घोषणा ERROR_OFFSET			4
#घोषणा ERROR_NO			(0 << ERROR_OFFSET)
#घोषणा ERROR_POWER_ON_RESET		(1 << ERROR_OFFSET)
#घोषणा ERROR_INT_RESET			(2 << ERROR_OFFSET)
#घोषणा ERROR_EXT_RESET			(3 << ERROR_OFFSET)
#घोषणा ERROR_INVALID_REG_ADDRESS	(8 << ERROR_OFFSET)
#घोषणा ERROR_INVALID_REG_VALUE		(9 << ERROR_OFFSET)

#घोषणा MCS5000_TS_OP_MODE		0x01
#घोषणा RESET_OFFSET			0
#घोषणा RESET_NO			(0 << RESET_OFFSET)
#घोषणा RESET_EXT_SOFT			(1 << RESET_OFFSET)
#घोषणा OP_MODE_OFFSET			1
#घोषणा OP_MODE_SLEEP			(0 << OP_MODE_OFFSET)
#घोषणा OP_MODE_ACTIVE			(1 << OP_MODE_OFFSET)
#घोषणा GESTURE_OFFSET			4
#घोषणा GESTURE_DISABLE			(0 << GESTURE_OFFSET)
#घोषणा GESTURE_ENABLE			(1 << GESTURE_OFFSET)
#घोषणा PROXIMITY_OFFSET		5
#घोषणा PROXIMITY_DISABLE		(0 << PROXIMITY_OFFSET)
#घोषणा PROXIMITY_ENABLE		(1 << PROXIMITY_OFFSET)
#घोषणा SCAN_MODE_OFFSET		6
#घोषणा SCAN_MODE_INTERRUPT		(0 << SCAN_MODE_OFFSET)
#घोषणा SCAN_MODE_POLLING		(1 << SCAN_MODE_OFFSET)
#घोषणा REPORT_RATE_OFFSET		7
#घोषणा REPORT_RATE_40			(0 << REPORT_RATE_OFFSET)
#घोषणा REPORT_RATE_80			(1 << REPORT_RATE_OFFSET)

#घोषणा MCS5000_TS_SENS_CTL		0x02
#घोषणा MCS5000_TS_FILTER_CTL		0x03
#घोषणा PRI_FILTER_OFFSET		0
#घोषणा SEC_FILTER_OFFSET		4

#घोषणा MCS5000_TS_X_SIZE_UPPER		0x08
#घोषणा MCS5000_TS_X_SIZE_LOWER		0x09
#घोषणा MCS5000_TS_Y_SIZE_UPPER		0x0A
#घोषणा MCS5000_TS_Y_SIZE_LOWER		0x0B

#घोषणा MCS5000_TS_INPUT_INFO		0x10
#घोषणा INPUT_TYPE_OFFSET		0
#घोषणा INPUT_TYPE_NONTOUCH		(0 << INPUT_TYPE_OFFSET)
#घोषणा INPUT_TYPE_SINGLE		(1 << INPUT_TYPE_OFFSET)
#घोषणा INPUT_TYPE_DUAL			(2 << INPUT_TYPE_OFFSET)
#घोषणा INPUT_TYPE_PALM			(3 << INPUT_TYPE_OFFSET)
#घोषणा INPUT_TYPE_PROXIMITY		(7 << INPUT_TYPE_OFFSET)
#घोषणा GESTURE_CODE_OFFSET		3
#घोषणा GESTURE_CODE_NO			(0 << GESTURE_CODE_OFFSET)

#घोषणा MCS5000_TS_X_POS_UPPER		0x11
#घोषणा MCS5000_TS_X_POS_LOWER		0x12
#घोषणा MCS5000_TS_Y_POS_UPPER		0x13
#घोषणा MCS5000_TS_Y_POS_LOWER		0x14
#घोषणा MCS5000_TS_Z_POS		0x15
#घोषणा MCS5000_TS_WIDTH		0x16
#घोषणा MCS5000_TS_GESTURE_VAL		0x17
#घोषणा MCS5000_TS_MODULE_REV		0x20
#घोषणा MCS5000_TS_FIRMWARE_VER		0x21

/* Touchscreen असलolute values */
#घोषणा MCS5000_MAX_XC			0x3ff
#घोषणा MCS5000_MAX_YC			0x3ff

क्रमागत mcs5000_ts_पढ़ो_offset अणु
	READ_INPUT_INFO,
	READ_X_POS_UPPER,
	READ_X_POS_LOWER,
	READ_Y_POS_UPPER,
	READ_Y_POS_LOWER,
	READ_BLOCK_SIZE,
पूर्ण;

/* Each client has this additional data */
काष्ठा mcs5000_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	स्थिर काष्ठा mcs_platक्रमm_data *platक्रमm_data;
पूर्ण;

अटल irqवापस_t mcs5000_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mcs5000_ts_data *data = dev_id;
	काष्ठा i2c_client *client = data->client;
	u8 buffer[READ_BLOCK_SIZE];
	पूर्णांक err;
	पूर्णांक x;
	पूर्णांक y;

	err = i2c_smbus_पढ़ो_i2c_block_data(client, MCS5000_TS_INPUT_INFO,
			READ_BLOCK_SIZE, buffer);
	अगर (err < 0) अणु
		dev_err(&client->dev, "%s, err[%d]\n", __func__, err);
		जाओ out;
	पूर्ण

	चयन (buffer[READ_INPUT_INFO]) अणु
	हाल INPUT_TYPE_NONTOUCH:
		input_report_key(data->input_dev, BTN_TOUCH, 0);
		input_sync(data->input_dev);
		अवरोध;

	हाल INPUT_TYPE_SINGLE:
		x = (buffer[READ_X_POS_UPPER] << 8) | buffer[READ_X_POS_LOWER];
		y = (buffer[READ_Y_POS_UPPER] << 8) | buffer[READ_Y_POS_LOWER];

		input_report_key(data->input_dev, BTN_TOUCH, 1);
		input_report_असल(data->input_dev, ABS_X, x);
		input_report_असल(data->input_dev, ABS_Y, y);
		input_sync(data->input_dev);
		अवरोध;

	हाल INPUT_TYPE_DUAL:
		/* TODO */
		अवरोध;

	हाल INPUT_TYPE_PALM:
		/* TODO */
		अवरोध;

	हाल INPUT_TYPE_PROXIMITY:
		/* TODO */
		अवरोध;

	शेष:
		dev_err(&client->dev, "Unknown ts input type %d\n",
				buffer[READ_INPUT_INFO]);
		अवरोध;
	पूर्ण

 out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mcs5000_ts_phys_init(काष्ठा mcs5000_ts_data *data,
				 स्थिर काष्ठा mcs_platक्रमm_data *platक्रमm_data)
अणु
	काष्ठा i2c_client *client = data->client;

	/* Touch reset & sleep mode */
	i2c_smbus_ग_लिखो_byte_data(client, MCS5000_TS_OP_MODE,
			RESET_EXT_SOFT | OP_MODE_SLEEP);

	/* Touch size */
	i2c_smbus_ग_लिखो_byte_data(client, MCS5000_TS_X_SIZE_UPPER,
			platक्रमm_data->x_size >> 8);
	i2c_smbus_ग_लिखो_byte_data(client, MCS5000_TS_X_SIZE_LOWER,
			platक्रमm_data->x_size & 0xff);
	i2c_smbus_ग_लिखो_byte_data(client, MCS5000_TS_Y_SIZE_UPPER,
			platक्रमm_data->y_size >> 8);
	i2c_smbus_ग_लिखो_byte_data(client, MCS5000_TS_Y_SIZE_LOWER,
			platक्रमm_data->y_size & 0xff);

	/* Touch active mode & 80 report rate */
	i2c_smbus_ग_लिखो_byte_data(data->client, MCS5000_TS_OP_MODE,
			OP_MODE_ACTIVE | REPORT_RATE_80);
पूर्ण

अटल पूर्णांक mcs5000_ts_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा mcs_platक्रमm_data *pdata;
	काष्ठा mcs5000_ts_data *data;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata)
		वापस -EINVAL;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		dev_err(&client->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	data->client = client;

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev) अणु
		dev_err(&client->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name = "MELFAS MCS-5000 Touchscreen";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	input_set_असल_params(input_dev, ABS_X, 0, MCS5000_MAX_XC, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MCS5000_MAX_YC, 0, 0);

	data->input_dev = input_dev;

	अगर (pdata->cfg_pin)
		pdata->cfg_pin();

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, mcs5000_ts_पूर्णांकerrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "mcs5000_ts", data);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(data->input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register input device\n");
		वापस error;
	पूर्ण

	mcs5000_ts_phys_init(data, pdata);
	i2c_set_clientdata(client, data);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mcs5000_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	/* Touch sleep mode */
	i2c_smbus_ग_लिखो_byte_data(client, MCS5000_TS_OP_MODE, OP_MODE_SLEEP);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mcs5000_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mcs5000_ts_data *data = i2c_get_clientdata(client);
	स्थिर काष्ठा mcs_platक्रमm_data *pdata = dev_get_platdata(dev);

	mcs5000_ts_phys_init(data, pdata);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mcs5000_ts_pm, mcs5000_ts_suspend, mcs5000_ts_resume);

अटल स्थिर काष्ठा i2c_device_id mcs5000_ts_id[] = अणु
	अणु "mcs5000_ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcs5000_ts_id);

अटल काष्ठा i2c_driver mcs5000_ts_driver = अणु
	.probe		= mcs5000_ts_probe,
	.driver = अणु
		.name = "mcs5000_ts",
		.pm   = &mcs5000_ts_pm,
	पूर्ण,
	.id_table	= mcs5000_ts_id,
पूर्ण;

module_i2c_driver(mcs5000_ts_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_DESCRIPTION("Touchscreen driver for MELFAS MCS-5000 controller");
MODULE_LICENSE("GPL");
