<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ChipOne icn8318 i2c touchscreen controller
 *
 * Copyright (c) 2015 Red Hat Inc.
 *
 * Red Hat authors:
 * Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#घोषणा ICN8318_REG_POWER		4
#घोषणा ICN8318_REG_TOUCHDATA		16

#घोषणा ICN8318_POWER_ACTIVE		0
#घोषणा ICN8318_POWER_MONITOR		1
#घोषणा ICN8318_POWER_HIBERNATE		2

#घोषणा ICN8318_MAX_TOUCHES		5

काष्ठा icn8318_touch अणु
	__u8 slot;
	__be16 x;
	__be16 y;
	__u8 pressure;	/* Seems more like finger width then pressure really */
	__u8 event;
/* The dअगरference between 2 and 3 is unclear */
#घोषणा ICN8318_EVENT_NO_DATA	1 /* No finger seen yet since wakeup */
#घोषणा ICN8318_EVENT_UPDATE1	2 /* New or updated coordinates */
#घोषणा ICN8318_EVENT_UPDATE2	3 /* New or updated coordinates */
#घोषणा ICN8318_EVENT_END	4 /* Finger lअगरted */
पूर्ण __packed;

काष्ठा icn8318_touch_data अणु
	__u8 softbutton;
	__u8 touch_count;
	काष्ठा icn8318_touch touches[ICN8318_MAX_TOUCHES];
पूर्ण __packed;

काष्ठा icn8318_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *wake_gpio;
	काष्ठा touchscreen_properties prop;
पूर्ण;

अटल पूर्णांक icn8318_पढ़ो_touch_data(काष्ठा i2c_client *client,
				   काष्ठा icn8318_touch_data *touch_data)
अणु
	u8 reg = ICN8318_REG_TOUCHDATA;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = client->addr,
			.len = 1,
			.buf = &reg
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = माप(काष्ठा icn8318_touch_data),
			.buf = (u8 *)touch_data
		पूर्ण
	पूर्ण;

	वापस i2c_transfer(client->adapter, msg, 2);
पूर्ण

अटल अंतरभूत bool icn8318_touch_active(u8 event)
अणु
	वापस (event == ICN8318_EVENT_UPDATE1) ||
	       (event == ICN8318_EVENT_UPDATE2);
पूर्ण

अटल irqवापस_t icn8318_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा icn8318_data *data = dev_id;
	काष्ठा device *dev = &data->client->dev;
	काष्ठा icn8318_touch_data touch_data;
	पूर्णांक i, ret;

	ret = icn8318_पढ़ो_touch_data(data->client, &touch_data);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading touch data: %d\n", ret);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (touch_data.softbutton) अणु
		/*
		 * Other data is invalid when a softbutton is pressed.
		 * This needs some extra devicetree bindings to map the icn8318
		 * softbutton codes to evdev codes. Currently no known devices
		 * use this.
		 */
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (touch_data.touch_count > ICN8318_MAX_TOUCHES) अणु
		dev_warn(dev, "Too much touches %d > %d\n",
			 touch_data.touch_count, ICN8318_MAX_TOUCHES);
		touch_data.touch_count = ICN8318_MAX_TOUCHES;
	पूर्ण

	क्रम (i = 0; i < touch_data.touch_count; i++) अणु
		काष्ठा icn8318_touch *touch = &touch_data.touches[i];
		bool act = icn8318_touch_active(touch->event);

		input_mt_slot(data->input, touch->slot);
		input_mt_report_slot_state(data->input, MT_TOOL_FINGER, act);
		अगर (!act)
			जारी;

		touchscreen_report_pos(data->input, &data->prop,
				       be16_to_cpu(touch->x),
				       be16_to_cpu(touch->y), true);
	पूर्ण

	input_mt_sync_frame(data->input);
	input_sync(data->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक icn8318_start(काष्ठा input_dev *dev)
अणु
	काष्ठा icn8318_data *data = input_get_drvdata(dev);

	enable_irq(data->client->irq);
	gpiod_set_value_cansleep(data->wake_gpio, 1);

	वापस 0;
पूर्ण

अटल व्योम icn8318_stop(काष्ठा input_dev *dev)
अणु
	काष्ठा icn8318_data *data = input_get_drvdata(dev);

	disable_irq(data->client->irq);
	i2c_smbus_ग_लिखो_byte_data(data->client, ICN8318_REG_POWER,
				  ICN8318_POWER_HIBERNATE);
	gpiod_set_value_cansleep(data->wake_gpio, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक icn8318_suspend(काष्ठा device *dev)
अणु
	काष्ठा icn8318_data *data = i2c_get_clientdata(to_i2c_client(dev));

	mutex_lock(&data->input->mutex);
	अगर (input_device_enabled(data->input))
		icn8318_stop(data->input);
	mutex_unlock(&data->input->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक icn8318_resume(काष्ठा device *dev)
अणु
	काष्ठा icn8318_data *data = i2c_get_clientdata(to_i2c_client(dev));

	mutex_lock(&data->input->mutex);
	अगर (input_device_enabled(data->input))
		icn8318_start(data->input);
	mutex_unlock(&data->input->mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(icn8318_pm_ops, icn8318_suspend, icn8318_resume);

अटल पूर्णांक icn8318_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा icn8318_data *data;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(dev, "Error no irq specified\n");
		वापस -EINVAL;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->wake_gpio = devm_gpiod_get(dev, "wake", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->wake_gpio)) अणु
		error = PTR_ERR(data->wake_gpio);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Error getting wake gpio: %d\n", error);
		वापस error;
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->खोलो = icn8318_start;
	input->बंद = icn8318_stop;
	input->dev.parent = dev;

	input_set_capability(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input, EV_ABS, ABS_MT_POSITION_Y);

	touchscreen_parse_properties(input, true, &data->prop);
	अगर (!input_असल_get_max(input, ABS_MT_POSITION_X) ||
	    !input_असल_get_max(input, ABS_MT_POSITION_Y)) अणु
		dev_err(dev, "Error touchscreen-size-x and/or -y missing\n");
		वापस -EINVAL;
	पूर्ण

	error = input_mt_init_slots(input, ICN8318_MAX_TOUCHES,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error)
		वापस error;

	data->client = client;
	data->input = input;
	input_set_drvdata(input, data);

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, icn8318_irq,
					  IRQF_ONESHOT, client->name, data);
	अगर (error) अणु
		dev_err(dev, "Error requesting irq: %d\n", error);
		वापस error;
	पूर्ण

	/* Stop device till खोलोed */
	icn8318_stop(data->input);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id icn8318_of_match[] = अणु
	अणु .compatible = "chipone,icn8318" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, icn8318_of_match);

/* This is useless क्रम OF-enabled devices, but it is needed by I2C subप्रणाली */
अटल स्थिर काष्ठा i2c_device_id icn8318_i2c_id[] = अणु
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, icn8318_i2c_id);

अटल काष्ठा i2c_driver icn8318_driver = अणु
	.driver = अणु
		.name	= "chipone_icn8318",
		.pm	= &icn8318_pm_ops,
		.of_match_table = icn8318_of_match,
	पूर्ण,
	.probe = icn8318_probe,
	.id_table = icn8318_i2c_id,
पूर्ण;

module_i2c_driver(icn8318_driver);

MODULE_DESCRIPTION("ChipOne icn8318 I2C Touchscreen Driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
