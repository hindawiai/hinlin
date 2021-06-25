<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max7359_keypad.c - MAX7359 Key Switch Controller Driver
 *
 * Copyright (C) 2009 Samsung Electronics
 * Kim Kyuwon <q1.kim@samsung.com>
 *
 * Based on pxa27x_keypad.c
 *
 * Datasheet: http://www.maxim-ic.com/quick_view2.cfm/qv_pk/5456
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>

#घोषणा MAX7359_MAX_KEY_ROWS	8
#घोषणा MAX7359_MAX_KEY_COLS	8
#घोषणा MAX7359_MAX_KEY_NUM	(MAX7359_MAX_KEY_ROWS * MAX7359_MAX_KEY_COLS)
#घोषणा MAX7359_ROW_SHIFT	3

/*
 * MAX7359 रेजिस्टरs
 */
#घोषणा MAX7359_REG_KEYFIFO	0x00
#घोषणा MAX7359_REG_CONFIG	0x01
#घोषणा MAX7359_REG_DEBOUNCE	0x02
#घोषणा MAX7359_REG_INTERRUPT	0x03
#घोषणा MAX7359_REG_PORTS	0x04
#घोषणा MAX7359_REG_KEYREP	0x05
#घोषणा MAX7359_REG_SLEEP	0x06

/*
 * Configuration रेजिस्टर bits
 */
#घोषणा MAX7359_CFG_SLEEP	(1 << 7)
#घोषणा MAX7359_CFG_INTERRUPT	(1 << 5)
#घोषणा MAX7359_CFG_KEY_RELEASE	(1 << 3)
#घोषणा MAX7359_CFG_WAKEUP	(1 << 1)
#घोषणा MAX7359_CFG_TIMEOUT	(1 << 0)

/*
 * Autosleep रेजिस्टर values (ms)
 */
#घोषणा MAX7359_AUTOSLEEP_8192	0x01
#घोषणा MAX7359_AUTOSLEEP_4096	0x02
#घोषणा MAX7359_AUTOSLEEP_2048	0x03
#घोषणा MAX7359_AUTOSLEEP_1024	0x04
#घोषणा MAX7359_AUTOSLEEP_512	0x05
#घोषणा MAX7359_AUTOSLEEP_256	0x06

काष्ठा max7359_keypad अणु
	/* matrix key code map */
	अचिन्हित लघु keycodes[MAX7359_MAX_KEY_NUM];

	काष्ठा input_dev *input_dev;
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक max7359_ग_लिखो_reg(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

	अगर (ret < 0)
		dev_err(&client->dev, "%s: reg 0x%x, val 0x%x, err %d\n",
			__func__, reg, val, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक max7359_पढ़ो_reg(काष्ठा i2c_client *client, पूर्णांक reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, reg);

	अगर (ret < 0)
		dev_err(&client->dev, "%s: reg 0x%x, err %d\n",
			__func__, reg, ret);
	वापस ret;
पूर्ण

/* runs in an IRQ thपढ़ो -- can (and will!) sleep */
अटल irqवापस_t max7359_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max7359_keypad *keypad = dev_id;
	काष्ठा input_dev *input_dev = keypad->input_dev;
	पूर्णांक val, row, col, release, code;

	val = max7359_पढ़ो_reg(keypad->client, MAX7359_REG_KEYFIFO);
	row = val & 0x7;
	col = (val >> 3) & 0x7;
	release = val & 0x40;

	code = MATRIX_SCAN_CODE(row, col, MAX7359_ROW_SHIFT);

	dev_dbg(&keypad->client->dev,
		"key[%d:%d] %s\n", row, col, release ? "release" : "press");

	input_event(input_dev, EV_MSC, MSC_SCAN, code);
	input_report_key(input_dev, keypad->keycodes[code], !release);
	input_sync(input_dev);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Let MAX7359 fall पूर्णांकo a deep sleep:
 * If no keys are pressed, enter sleep mode क्रम 8192 ms. And अगर any
 * key is pressed, the MAX7359 वापसs to normal operating mode.
 */
अटल अंतरभूत व्योम max7359_fall_deepsleep(काष्ठा i2c_client *client)
अणु
	max7359_ग_लिखो_reg(client, MAX7359_REG_SLEEP, MAX7359_AUTOSLEEP_8192);
पूर्ण

/*
 * Let MAX7359 take a catnap:
 * Autosleep just क्रम 256 ms.
 */
अटल अंतरभूत व्योम max7359_take_catnap(काष्ठा i2c_client *client)
अणु
	max7359_ग_लिखो_reg(client, MAX7359_REG_SLEEP, MAX7359_AUTOSLEEP_256);
पूर्ण

अटल पूर्णांक max7359_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा max7359_keypad *keypad = input_get_drvdata(dev);

	max7359_take_catnap(keypad->client);

	वापस 0;
पूर्ण

अटल व्योम max7359_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा max7359_keypad *keypad = input_get_drvdata(dev);

	max7359_fall_deepsleep(keypad->client);
पूर्ण

अटल व्योम max7359_initialize(काष्ठा i2c_client *client)
अणु
	max7359_ग_लिखो_reg(client, MAX7359_REG_CONFIG,
		MAX7359_CFG_KEY_RELEASE | /* Key release enable */
		MAX7359_CFG_WAKEUP); /* Key press wakeup enable */

	/* Full key-scan functionality */
	max7359_ग_लिखो_reg(client, MAX7359_REG_DEBOUNCE, 0x1F);

	/* nINT निश्चितs every debounce cycles */
	max7359_ग_लिखो_reg(client, MAX7359_REG_INTERRUPT, 0x01);

	max7359_fall_deepsleep(client);
पूर्ण

अटल पूर्णांक max7359_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा matrix_keymap_data *keymap_data =
			dev_get_platdata(&client->dev);
	काष्ठा max7359_keypad *keypad;
	काष्ठा input_dev *input_dev;
	पूर्णांक ret;
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(&client->dev, "The irq number should not be zero\n");
		वापस -EINVAL;
	पूर्ण

	/* Detect MAX7359: The initial Keys FIFO value is '0x3F' */
	ret = max7359_पढ़ो_reg(client, MAX7359_REG_KEYFIFO);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to detect device\n");
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&client->dev, "keys FIFO is 0x%02x\n", ret);

	keypad = devm_kzalloc(&client->dev, माप(काष्ठा max7359_keypad),
			      GFP_KERNEL);
	अगर (!keypad) अणु
		dev_err(&client->dev, "failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev) अणु
		dev_err(&client->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	keypad->client = client;
	keypad->input_dev = input_dev;

	input_dev->name = client->name;
	input_dev->id.bustype = BUS_I2C;
	input_dev->खोलो = max7359_खोलो;
	input_dev->बंद = max7359_बंद;
	input_dev->dev.parent = &client->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->keycodesize = माप(keypad->keycodes[0]);
	input_dev->keycodemax = ARRAY_SIZE(keypad->keycodes);
	input_dev->keycode = keypad->keycodes;

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	input_set_drvdata(input_dev, keypad);

	error = matrix_keypad_build_keymap(keymap_data, शून्य,
					   MAX7359_MAX_KEY_ROWS,
					   MAX7359_MAX_KEY_COLS,
					   keypad->keycodes,
					   input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "failed to build keymap\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					  max7359_पूर्णांकerrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  client->name, keypad);
	अगर (error) अणु
		dev_err(&client->dev, "failed to register interrupt\n");
		वापस error;
	पूर्ण

	/* Register the input device */
	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	/* Initialize MAX7359 */
	max7359_initialize(client);

	device_init_wakeup(&client->dev, 1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max7359_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	max7359_fall_deepsleep(client);

	अगर (device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक max7359_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (device_may_wakeup(&client->dev))
		disable_irq_wake(client->irq);

	/* Restore the शेष setting */
	max7359_take_catnap(client);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(max7359_pm, max7359_suspend, max7359_resume);

अटल स्थिर काष्ठा i2c_device_id max7359_ids[] = अणु
	अणु "max7359", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max7359_ids);

अटल काष्ठा i2c_driver max7359_i2c_driver = अणु
	.driver = अणु
		.name = "max7359",
		.pm   = &max7359_pm,
	पूर्ण,
	.probe		= max7359_probe,
	.id_table	= max7359_ids,
पूर्ण;

module_i2c_driver(max7359_i2c_driver);

MODULE_AUTHOR("Kim Kyuwon <q1.kim@samsung.com>");
MODULE_DESCRIPTION("MAX7359 Key Switch Controller Driver");
MODULE_LICENSE("GPL v2");
