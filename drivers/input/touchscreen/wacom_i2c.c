<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Wacom Penabled Driver क्रम I2C
 *
 * Copyright (c) 2011 - 2013 Tatsunosuke Tobita, Wacom.
 * <tobita.tatsunosuke@wacom.co.jp>
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा WACOM_CMD_QUERY0	0x04
#घोषणा WACOM_CMD_QUERY1	0x00
#घोषणा WACOM_CMD_QUERY2	0x33
#घोषणा WACOM_CMD_QUERY3	0x02
#घोषणा WACOM_CMD_THROW0	0x05
#घोषणा WACOM_CMD_THROW1	0x00
#घोषणा WACOM_QUERY_SIZE	19

काष्ठा wacom_features अणु
	पूर्णांक x_max;
	पूर्णांक y_max;
	पूर्णांक pressure_max;
	अक्षर fw_version;
पूर्ण;

काष्ठा wacom_i2c अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	u8 data[WACOM_QUERY_SIZE];
	bool prox;
	पूर्णांक tool;
पूर्ण;

अटल पूर्णांक wacom_query_device(काष्ठा i2c_client *client,
			      काष्ठा wacom_features *features)
अणु
	पूर्णांक ret;
	u8 cmd1[] = अणु WACOM_CMD_QUERY0, WACOM_CMD_QUERY1,
			WACOM_CMD_QUERY2, WACOM_CMD_QUERY3 पूर्ण;
	u8 cmd2[] = अणु WACOM_CMD_THROW0, WACOM_CMD_THROW1 पूर्ण;
	u8 data[WACOM_QUERY_SIZE];
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = माप(cmd1),
			.buf = cmd1,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = माप(cmd2),
			.buf = cmd2,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = माप(data),
			.buf = data,
		पूर्ण,
	पूर्ण;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;

	features->x_max = get_unaligned_le16(&data[3]);
	features->y_max = get_unaligned_le16(&data[5]);
	features->pressure_max = get_unaligned_le16(&data[11]);
	features->fw_version = get_unaligned_le16(&data[13]);

	dev_dbg(&client->dev,
		"x_max:%d, y_max:%d, pressure:%d, fw:%d\n",
		features->x_max, features->y_max,
		features->pressure_max, features->fw_version);

	वापस 0;
पूर्ण

अटल irqवापस_t wacom_i2c_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा wacom_i2c *wac_i2c = dev_id;
	काष्ठा input_dev *input = wac_i2c->input;
	u8 *data = wac_i2c->data;
	अचिन्हित पूर्णांक x, y, pressure;
	अचिन्हित अक्षर tsw, f1, f2, ers;
	पूर्णांक error;

	error = i2c_master_recv(wac_i2c->client,
				wac_i2c->data, माप(wac_i2c->data));
	अगर (error < 0)
		जाओ out;

	tsw = data[3] & 0x01;
	ers = data[3] & 0x04;
	f1 = data[3] & 0x02;
	f2 = data[3] & 0x10;
	x = le16_to_cpup((__le16 *)&data[4]);
	y = le16_to_cpup((__le16 *)&data[6]);
	pressure = le16_to_cpup((__le16 *)&data[8]);

	अगर (!wac_i2c->prox)
		wac_i2c->tool = (data[3] & 0x0c) ?
			BTN_TOOL_RUBBER : BTN_TOOL_PEN;

	wac_i2c->prox = data[3] & 0x20;

	input_report_key(input, BTN_TOUCH, tsw || ers);
	input_report_key(input, wac_i2c->tool, wac_i2c->prox);
	input_report_key(input, BTN_STYLUS, f1);
	input_report_key(input, BTN_STYLUS2, f2);
	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);
	input_report_असल(input, ABS_PRESSURE, pressure);
	input_sync(input);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wacom_i2c_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wacom_i2c *wac_i2c = input_get_drvdata(dev);
	काष्ठा i2c_client *client = wac_i2c->client;

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल व्योम wacom_i2c_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wacom_i2c *wac_i2c = input_get_drvdata(dev);
	काष्ठा i2c_client *client = wac_i2c->client;

	disable_irq(client->irq);
पूर्ण

अटल पूर्णांक wacom_i2c_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा wacom_i2c *wac_i2c;
	काष्ठा input_dev *input;
	काष्ठा wacom_features features = अणु 0 पूर्ण;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "i2c_check_functionality error\n");
		वापस -EIO;
	पूर्ण

	error = wacom_query_device(client, &features);
	अगर (error)
		वापस error;

	wac_i2c = devm_kzalloc(dev, माप(*wac_i2c), GFP_KERNEL);
	अगर (!wac_i2c)
		वापस -ENOMEM;

	wac_i2c->client = client;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	wac_i2c->input = input;

	input->name = "Wacom I2C Digitizer";
	input->id.bustype = BUS_I2C;
	input->id.venकरोr = 0x56a;
	input->id.version = features.fw_version;
	input->खोलो = wacom_i2c_खोलो;
	input->बंद = wacom_i2c_बंद;

	input->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	__set_bit(BTN_TOOL_PEN, input->keybit);
	__set_bit(BTN_TOOL_RUBBER, input->keybit);
	__set_bit(BTN_STYLUS, input->keybit);
	__set_bit(BTN_STYLUS2, input->keybit);
	__set_bit(BTN_TOUCH, input->keybit);

	input_set_असल_params(input, ABS_X, 0, features.x_max, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, features.y_max, 0, 0);
	input_set_असल_params(input, ABS_PRESSURE,
			     0, features.pressure_max, 0, 0);

	input_set_drvdata(input, wac_i2c);

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, wacom_i2c_irq,
					  IRQF_ONESHOT, "wacom_i2c", wac_i2c);
	अगर (error) अणु
		dev_err(dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	/* Disable the IRQ, we'll enable it in wac_i2c_खोलो() */
	disable_irq(client->irq);

	error = input_रेजिस्टर_device(wac_i2c->input);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wacom_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	disable_irq(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wacom_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(wacom_i2c_pm, wacom_i2c_suspend, wacom_i2c_resume);

अटल स्थिर काष्ठा i2c_device_id wacom_i2c_id[] = अणु
	अणु "WAC_I2C_EMR", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wacom_i2c_id);

अटल काष्ठा i2c_driver wacom_i2c_driver = अणु
	.driver	= अणु
		.name	= "wacom_i2c",
		.pm	= &wacom_i2c_pm,
	पूर्ण,

	.probe		= wacom_i2c_probe,
	.id_table	= wacom_i2c_id,
पूर्ण;
module_i2c_driver(wacom_i2c_driver);

MODULE_AUTHOR("Tatsunosuke Tobita <tobita.tatsunosuke@wacom.co.jp>");
MODULE_DESCRIPTION("WACOM EMR I2C Driver");
MODULE_LICENSE("GPL");
