<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम EETI eGalax Multiple Touch Controller
 *
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 *
 * based on max11801_ts.c
 */

/* EETI eGalax serial touch screen controller is a I2C based multiple
 * touch screen controller, it supports 5 poपूर्णांक multiple touch. */

/* TODO:
  - स्वतः idle mode support
*/

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/of_gpपन.स>

/*
 * Mouse Mode: some panel may configure the controller to mouse mode,
 * which can only report one poपूर्णांक at a given समय.
 * This driver will ignore events in this mode.
 */
#घोषणा REPORT_MODE_MOUSE		0x1
/*
 * Venकरोr Mode: this mode is used to transfer some venकरोr specअगरic
 * messages.
 * This driver will ignore events in this mode.
 */
#घोषणा REPORT_MODE_VENDOR		0x3
/* Multiple Touch Mode */
#घोषणा REPORT_MODE_MTTOUCH		0x4

#घोषणा MAX_SUPPORT_POINTS		5

#घोषणा EVENT_VALID_OFFSET	7
#घोषणा EVENT_VALID_MASK	(0x1 << EVENT_VALID_OFFSET)
#घोषणा EVENT_ID_OFFSET		2
#घोषणा EVENT_ID_MASK		(0xf << EVENT_ID_OFFSET)
#घोषणा EVENT_IN_RANGE		(0x1 << 1)
#घोषणा EVENT_DOWN_UP		(0X1 << 0)

#घोषणा MAX_I2C_DATA_LEN	10

#घोषणा EGALAX_MAX_X	32760
#घोषणा EGALAX_MAX_Y	32760
#घोषणा EGALAX_MAX_TRIES 100

काष्ठा egalax_ts अणु
	काष्ठा i2c_client		*client;
	काष्ठा input_dev		*input_dev;
पूर्ण;

अटल irqवापस_t egalax_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा egalax_ts *ts = dev_id;
	काष्ठा input_dev *input_dev = ts->input_dev;
	काष्ठा i2c_client *client = ts->client;
	u8 buf[MAX_I2C_DATA_LEN];
	पूर्णांक id, ret, x, y, z;
	पूर्णांक tries = 0;
	bool करोwn, valid;
	u8 state;

	करो अणु
		ret = i2c_master_recv(client, buf, MAX_I2C_DATA_LEN);
	पूर्ण जबतक (ret == -EAGAIN && tries++ < EGALAX_MAX_TRIES);

	अगर (ret < 0)
		वापस IRQ_HANDLED;

	अगर (buf[0] != REPORT_MODE_MTTOUCH) अणु
		/* ignore mouse events and venकरोr events */
		वापस IRQ_HANDLED;
	पूर्ण

	state = buf[1];
	x = (buf[3] << 8) | buf[2];
	y = (buf[5] << 8) | buf[4];
	z = (buf[7] << 8) | buf[6];

	valid = state & EVENT_VALID_MASK;
	id = (state & EVENT_ID_MASK) >> EVENT_ID_OFFSET;
	करोwn = state & EVENT_DOWN_UP;

	अगर (!valid || id > MAX_SUPPORT_POINTS) अणु
		dev_dbg(&client->dev, "point invalid\n");
		वापस IRQ_HANDLED;
	पूर्ण

	input_mt_slot(input_dev, id);
	input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, करोwn);

	dev_dbg(&client->dev, "%s id:%d x:%d y:%d z:%d",
		करोwn ? "down" : "up", id, x, y, z);

	अगर (करोwn) अणु
		input_report_असल(input_dev, ABS_MT_POSITION_X, x);
		input_report_असल(input_dev, ABS_MT_POSITION_Y, y);
		input_report_असल(input_dev, ABS_MT_PRESSURE, z);
	पूर्ण

	input_mt_report_poपूर्णांकer_emulation(input_dev, true);
	input_sync(input_dev);

	वापस IRQ_HANDLED;
पूर्ण

/* wake up controller by an falling edge of पूर्णांकerrupt gpio.  */
अटल पूर्णांक egalax_wake_up_device(काष्ठा i2c_client *client)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	पूर्णांक gpio;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	gpio = of_get_named_gpio(np, "wakeup-gpios", 0);
	अगर (!gpio_is_valid(gpio))
		वापस -ENODEV;

	ret = gpio_request(gpio, "egalax_irq");
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"request gpio failed, cannot wake up controller: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* wake up controller via an falling edge on IRQ gpio. */
	gpio_direction_output(gpio, 0);
	gpio_set_value(gpio, 1);

	/* controller should be waken up, वापस irq.  */
	gpio_direction_input(gpio);
	gpio_मुक्त(gpio);

	वापस 0;
पूर्ण

अटल पूर्णांक egalax_firmware_version(काष्ठा i2c_client *client)
अणु
	अटल स्थिर u8 cmd[MAX_I2C_DATA_LEN] = अणु 0x03, 0x03, 0xa, 0x01, 0x41 पूर्ण;
	पूर्णांक ret;

	ret = i2c_master_send(client, cmd, MAX_I2C_DATA_LEN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक egalax_ts_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा egalax_ts *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	ts = devm_kzalloc(&client->dev, माप(काष्ठा egalax_ts), GFP_KERNEL);
	अगर (!ts) अणु
		dev_err(&client->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev) अणु
		dev_err(&client->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	ts->client = client;
	ts->input_dev = input_dev;

	/* controller may be in sleep, wake it up. */
	error = egalax_wake_up_device(client);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to wake up the controller\n");
		वापस error;
	पूर्ण

	error = egalax_firmware_version(client);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Failed to read firmware version\n");
		वापस error;
	पूर्ण

	input_dev->name = "EETI eGalax Touch Screen";
	input_dev->id.bustype = BUS_I2C;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);

	input_set_असल_params(input_dev, ABS_X, 0, EGALAX_MAX_X, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, EGALAX_MAX_Y, 0, 0);
	input_set_असल_params(input_dev,
			     ABS_MT_POSITION_X, 0, EGALAX_MAX_X, 0, 0);
	input_set_असल_params(input_dev,
			     ABS_MT_POSITION_Y, 0, EGALAX_MAX_Y, 0, 0);
	input_mt_init_slots(input_dev, MAX_SUPPORT_POINTS, 0);

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					  egalax_ts_पूर्णांकerrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "egalax_ts", ts);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ts->input_dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id egalax_ts_id[] = अणु
	अणु "egalax_ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, egalax_ts_id);

अटल पूर्णांक __maybe_unused egalax_ts_suspend(काष्ठा device *dev)
अणु
	अटल स्थिर u8 suspend_cmd[MAX_I2C_DATA_LEN] = अणु
		0x3, 0x6, 0xa, 0x3, 0x36, 0x3f, 0x2, 0, 0, 0
	पूर्ण;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (device_may_wakeup(dev))
		वापस enable_irq_wake(client->irq);

	ret = i2c_master_send(client, suspend_cmd, MAX_I2C_DATA_LEN);
	वापस ret > 0 ? 0 : ret;
पूर्ण

अटल पूर्णांक __maybe_unused egalax_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (device_may_wakeup(dev))
		वापस disable_irq_wake(client->irq);

	वापस egalax_wake_up_device(client);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(egalax_ts_pm_ops, egalax_ts_suspend, egalax_ts_resume);

अटल स्थिर काष्ठा of_device_id egalax_ts_dt_ids[] = अणु
	अणु .compatible = "eeti,egalax_ts" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, egalax_ts_dt_ids);

अटल काष्ठा i2c_driver egalax_ts_driver = अणु
	.driver = अणु
		.name	= "egalax_ts",
		.pm	= &egalax_ts_pm_ops,
		.of_match_table	= egalax_ts_dt_ids,
	पूर्ण,
	.id_table	= egalax_ts_id,
	.probe		= egalax_ts_probe,
पूर्ण;

module_i2c_driver(egalax_ts_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Touchscreen driver for EETI eGalax touch controller");
MODULE_LICENSE("GPL");
