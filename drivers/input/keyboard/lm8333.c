<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LM8333 keypad driver
 * Copyright (C) 2012 Wolfram Sang, Pengutronix <kernel@pengutronix.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/input/lm8333.h>

#घोषणा LM8333_FIFO_READ		0x20
#घोषणा LM8333_DEBOUNCE			0x22
#घोषणा LM8333_READ_INT			0xD0
#घोषणा LM8333_ACTIVE			0xE4
#घोषणा LM8333_READ_ERROR		0xF0

#घोषणा LM8333_KEYPAD_IRQ		(1 << 0)
#घोषणा LM8333_ERROR_IRQ		(1 << 3)

#घोषणा LM8333_ERROR_KEYOVR		0x04
#घोषणा LM8333_ERROR_FIFOOVR		0x40

#घोषणा LM8333_FIFO_TRANSFER_SIZE	16

#घोषणा LM8333_NUM_ROWS		8
#घोषणा LM8333_NUM_COLS		16
#घोषणा LM8333_ROW_SHIFT	4

काष्ठा lm8333 अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	अचिन्हित लघु keycodes[LM8333_NUM_ROWS << LM8333_ROW_SHIFT];
पूर्ण;

/* The accessors try twice because the first access may be needed क्रम wakeup */
#घोषणा LM8333_READ_RETRIES 2

पूर्णांक lm8333_पढ़ो8(काष्ठा lm8333 *lm8333, u8 cmd)
अणु
	पूर्णांक retries = 0, ret;

	करो अणु
		ret = i2c_smbus_पढ़ो_byte_data(lm8333->client, cmd);
	पूर्ण जबतक (ret < 0 && retries++ < LM8333_READ_RETRIES);

	वापस ret;
पूर्ण

पूर्णांक lm8333_ग_लिखो8(काष्ठा lm8333 *lm8333, u8 cmd, u8 val)
अणु
	पूर्णांक retries = 0, ret;

	करो अणु
		ret = i2c_smbus_ग_लिखो_byte_data(lm8333->client, cmd, val);
	पूर्ण जबतक (ret < 0 && retries++ < LM8333_READ_RETRIES);

	वापस ret;
पूर्ण

पूर्णांक lm8333_पढ़ो_block(काष्ठा lm8333 *lm8333, u8 cmd, u8 len, u8 *buf)
अणु
	पूर्णांक retries = 0, ret;

	करो अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(lm8333->client,
						    cmd, len, buf);
	पूर्ण जबतक (ret < 0 && retries++ < LM8333_READ_RETRIES);

	वापस ret;
पूर्ण

अटल व्योम lm8333_key_handler(काष्ठा lm8333 *lm8333)
अणु
	काष्ठा input_dev *input = lm8333->input;
	u8 keys[LM8333_FIFO_TRANSFER_SIZE];
	u8 code, pressed;
	पूर्णांक i, ret;

	ret = lm8333_पढ़ो_block(lm8333, LM8333_FIFO_READ,
				LM8333_FIFO_TRANSFER_SIZE, keys);
	अगर (ret != LM8333_FIFO_TRANSFER_SIZE) अणु
		dev_err(&lm8333->client->dev,
			"Error %d while reading FIFO\n", ret);
		वापस;
	पूर्ण

	क्रम (i = 0; i < LM8333_FIFO_TRANSFER_SIZE && keys[i]; i++) अणु
		pressed = keys[i] & 0x80;
		code = keys[i] & 0x7f;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_report_key(input, lm8333->keycodes[code], pressed);
	पूर्ण

	input_sync(input);
पूर्ण

अटल irqवापस_t lm8333_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lm8333 *lm8333 = data;
	u8 status = lm8333_पढ़ो8(lm8333, LM8333_READ_INT);

	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & LM8333_ERROR_IRQ) अणु
		u8 err = lm8333_पढ़ो8(lm8333, LM8333_READ_ERROR);

		अगर (err & (LM8333_ERROR_KEYOVR | LM8333_ERROR_FIFOOVR)) अणु
			u8 dummy[LM8333_FIFO_TRANSFER_SIZE];

			lm8333_पढ़ो_block(lm8333, LM8333_FIFO_READ,
					LM8333_FIFO_TRANSFER_SIZE, dummy);
		पूर्ण
		dev_err(&lm8333->client->dev, "Got error %02x\n", err);
	पूर्ण

	अगर (status & LM8333_KEYPAD_IRQ)
		lm8333_key_handler(lm8333);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lm8333_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा lm8333_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	काष्ठा lm8333 *lm8333;
	काष्ठा input_dev *input;
	पूर्णांक err, active_समय;

	अगर (!pdata)
		वापस -EINVAL;

	active_समय = pdata->active_समय ?: 500;
	अगर (active_समय / 3 <= pdata->debounce_समय / 3) अणु
		dev_err(&client->dev, "Active time not big enough!\n");
		वापस -EINVAL;
	पूर्ण

	lm8333 = kzalloc(माप(*lm8333), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!lm8333 || !input) अणु
		err = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	lm8333->client = client;
	lm8333->input = input;

	input->name = client->name;
	input->dev.parent = &client->dev;
	input->id.bustype = BUS_I2C;

	input_set_capability(input, EV_MSC, MSC_SCAN);

	err = matrix_keypad_build_keymap(pdata->matrix_data, शून्य,
					 LM8333_NUM_ROWS, LM8333_NUM_COLS,
					 lm8333->keycodes, input);
	अगर (err)
		जाओ मुक्त_mem;

	अगर (pdata->debounce_समय) अणु
		err = lm8333_ग_लिखो8(lm8333, LM8333_DEBOUNCE,
				    pdata->debounce_समय / 3);
		अगर (err)
			dev_warn(&client->dev, "Unable to set debounce time\n");
	पूर्ण

	अगर (pdata->active_समय) अणु
		err = lm8333_ग_लिखो8(lm8333, LM8333_ACTIVE,
				    pdata->active_समय / 3);
		अगर (err)
			dev_warn(&client->dev, "Unable to set active time\n");
	पूर्ण

	err = request_thपढ़ोed_irq(client->irq, शून्य, lm8333_irq_thपढ़ो,
				   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				   "lm8333", lm8333);
	अगर (err)
		जाओ मुक्त_mem;

	err = input_रेजिस्टर_device(input);
	अगर (err)
		जाओ मुक्त_irq;

	i2c_set_clientdata(client, lm8333);
	वापस 0;

 मुक्त_irq:
	मुक्त_irq(client->irq, lm8333);
 मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(lm8333);
	वापस err;
पूर्ण

अटल पूर्णांक lm8333_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm8333 *lm8333 = i2c_get_clientdata(client);

	मुक्त_irq(client->irq, lm8333);
	input_unरेजिस्टर_device(lm8333->input);
	kमुक्त(lm8333);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm8333_id[] = अणु
	अणु "lm8333", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm8333_id);

अटल काष्ठा i2c_driver lm8333_driver = अणु
	.driver = अणु
		.name		= "lm8333",
	पूर्ण,
	.probe		= lm8333_probe,
	.हटाओ		= lm8333_हटाओ,
	.id_table	= lm8333_id,
पूर्ण;
module_i2c_driver(lm8333_driver);

MODULE_AUTHOR("Wolfram Sang <kernel@pengutronix.de>");
MODULE_DESCRIPTION("LM8333 keyboard driver");
MODULE_LICENSE("GPL v2");
