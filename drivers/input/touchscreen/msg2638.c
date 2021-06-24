<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MStar msg2638 touchscreens
 *
 * Copyright (c) 2021 Vincent Knecht <vincent.knecht@mailoo.org>
 *
 * Checksum and IRQ handler based on mstar_drv_common.c and
 * mstar_drv_mutual_fw_control.c
 * Copyright (c) 2006-2012 MStar Semiconductor, Inc.
 *
 * Driver काष्ठाure based on zinitix.c by Michael Srba <Michael.Srba@seznam.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#घोषणा MODE_DATA_RAW			0x5A

#घोषणा MAX_SUPPORTED_FINGER_NUM	5

#घोषणा CHIP_ON_DELAY_MS		15
#घोषणा FIRMWARE_ON_DELAY_MS		50
#घोषणा RESET_DELAY_MIN_US		10000
#घोषणा RESET_DELAY_MAX_US		11000

काष्ठा packet अणु
	u8	xy_hi; /* higher bits of x and y coordinates */
	u8	x_low;
	u8	y_low;
	u8	pressure;
पूर्ण;

काष्ठा touch_event अणु
	u8	mode;
	काष्ठा	packet pkt[MAX_SUPPORTED_FINGER_NUM];
	u8	proximity;
	u8	checksum;
पूर्ण;

काष्ठा msg2638_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा touchscreen_properties prop;
	काष्ठा regulator_bulk_data supplies[2];
	काष्ठा gpio_desc *reset_gpiod;
पूर्ण;

अटल u8 msg2638_checksum(u8 *data, u32 length)
अणु
	s32 sum = 0;
	u32 i;

	क्रम (i = 0; i < length; i++)
		sum += data[i];

	वापस (u8)((-sum) & 0xFF);
पूर्ण

अटल irqवापस_t msg2638_ts_irq_handler(पूर्णांक irq, व्योम *msg2638_handler)
अणु
	काष्ठा msg2638_ts_data *msg2638 = msg2638_handler;
	काष्ठा i2c_client *client = msg2638->client;
	काष्ठा input_dev *input = msg2638->input_dev;
	काष्ठा touch_event touch_event;
	u32 len = माप(touch_event);
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= माप(touch_event),
			.buf	= (u8 *)&touch_event,
		पूर्ण,
	पूर्ण;
	काष्ठा packet *p;
	u16 x, y;
	पूर्णांक ret;
	पूर्णांक i;

	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret != ARRAY_SIZE(msg)) अणु
		dev_err(&client->dev,
			"Failed I2C transfer in irq handler: %d\n",
			ret < 0 ? ret : -EIO);
		जाओ out;
	पूर्ण

	अगर (touch_event.mode != MODE_DATA_RAW)
		जाओ out;

	अगर (msg2638_checksum((u8 *)&touch_event, len - 1) !=
						touch_event.checksum) अणु
		dev_err(&client->dev, "Failed checksum!\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < MAX_SUPPORTED_FINGER_NUM; i++) अणु
		p = &touch_event.pkt[i];

		/* Ignore non-pressed finger data */
		अगर (p->xy_hi == 0xFF && p->x_low == 0xFF && p->y_low == 0xFF)
			जारी;

		x = (((p->xy_hi & 0xF0) << 4) | p->x_low);
		y = (((p->xy_hi & 0x0F) << 8) | p->y_low);

		input_mt_slot(input, i);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		touchscreen_report_pos(input, &msg2638->prop, x, y, true);
	पूर्ण

	input_mt_sync_frame(msg2638->input_dev);
	input_sync(msg2638->input_dev);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम msg2638_reset(काष्ठा msg2638_ts_data *msg2638)
अणु
	gpiod_set_value_cansleep(msg2638->reset_gpiod, 1);
	usleep_range(RESET_DELAY_MIN_US, RESET_DELAY_MAX_US);
	gpiod_set_value_cansleep(msg2638->reset_gpiod, 0);
	msleep(FIRMWARE_ON_DELAY_MS);
पूर्ण

अटल पूर्णांक msg2638_start(काष्ठा msg2638_ts_data *msg2638)
अणु
	पूर्णांक error;

	error = regulator_bulk_enable(ARRAY_SIZE(msg2638->supplies),
				      msg2638->supplies);
	अगर (error) अणु
		dev_err(&msg2638->client->dev,
			"Failed to enable regulators: %d\n", error);
		वापस error;
	पूर्ण

	msleep(CHIP_ON_DELAY_MS);

	msg2638_reset(msg2638);

	enable_irq(msg2638->client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक msg2638_stop(काष्ठा msg2638_ts_data *msg2638)
अणु
	पूर्णांक error;

	disable_irq(msg2638->client->irq);

	error = regulator_bulk_disable(ARRAY_SIZE(msg2638->supplies),
				       msg2638->supplies);
	अगर (error) अणु
		dev_err(&msg2638->client->dev,
			"Failed to disable regulators: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msg2638_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा msg2638_ts_data *msg2638 = input_get_drvdata(dev);

	वापस msg2638_start(msg2638);
पूर्ण

अटल व्योम msg2638_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा msg2638_ts_data *msg2638 = input_get_drvdata(dev);

	msg2638_stop(msg2638);
पूर्ण

अटल पूर्णांक msg2638_init_input_dev(काष्ठा msg2638_ts_data *msg2638)
अणु
	काष्ठा device *dev = &msg2638->client->dev;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev) अणु
		dev_err(dev, "Failed to allocate input device.\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(input_dev, msg2638);
	msg2638->input_dev = input_dev;

	input_dev->name = "MStar TouchScreen";
	input_dev->phys = "input/ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->खोलो = msg2638_input_खोलो;
	input_dev->बंद = msg2638_input_बंद;

	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_Y);

	touchscreen_parse_properties(input_dev, true, &msg2638->prop);
	अगर (!msg2638->prop.max_x || !msg2638->prop.max_y) अणु
		dev_err(dev, "touchscreen-size-x and/or touchscreen-size-y not set in properties\n");
		वापस -EINVAL;
	पूर्ण

	error = input_mt_init_slots(input_dev, MAX_SUPPORTED_FINGER_NUM,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(dev, "Failed to initialize MT slots: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msg2638_ts_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा msg2638_ts_data *msg2638;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "Failed to assert adapter's support for plain I2C.\n");
		वापस -ENXIO;
	पूर्ण

	msg2638 = devm_kzalloc(dev, माप(*msg2638), GFP_KERNEL);
	अगर (!msg2638)
		वापस -ENOMEM;

	msg2638->client = client;
	i2c_set_clientdata(client, msg2638);

	msg2638->supplies[0].supply = "vdd";
	msg2638->supplies[1].supply = "vddio";
	error = devm_regulator_bulk_get(dev, ARRAY_SIZE(msg2638->supplies),
					msg2638->supplies);
	अगर (error) अणु
		dev_err(dev, "Failed to get regulators: %d\n", error);
		वापस error;
	पूर्ण

	msg2638->reset_gpiod = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(msg2638->reset_gpiod)) अणु
		error = PTR_ERR(msg2638->reset_gpiod);
		dev_err(dev, "Failed to request reset GPIO: %d\n", error);
		वापस error;
	पूर्ण

	error = msg2638_init_input_dev(msg2638);
	अगर (error) अणु
		dev_err(dev, "Failed to initialize input device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, msg2638_ts_irq_handler,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  client->name, msg2638);
	अगर (error) अणु
		dev_err(dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msg2638_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा msg2638_ts_data *msg2638 = i2c_get_clientdata(client);

	mutex_lock(&msg2638->input_dev->mutex);

	अगर (input_device_enabled(msg2638->input_dev))
		msg2638_stop(msg2638);

	mutex_unlock(&msg2638->input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused msg2638_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा msg2638_ts_data *msg2638 = i2c_get_clientdata(client);
	पूर्णांक ret = 0;

	mutex_lock(&msg2638->input_dev->mutex);

	अगर (input_device_enabled(msg2638->input_dev))
		ret = msg2638_start(msg2638);

	mutex_unlock(&msg2638->input_dev->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(msg2638_pm_ops, msg2638_suspend, msg2638_resume);

अटल स्थिर काष्ठा of_device_id msg2638_of_match[] = अणु
	अणु .compatible = "mstar,msg2638" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, msg2638_of_match);

अटल काष्ठा i2c_driver msg2638_ts_driver = अणु
	.probe_new = msg2638_ts_probe,
	.driver = अणु
		.name = "MStar-TS",
		.pm = &msg2638_pm_ops,
		.of_match_table = msg2638_of_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(msg2638_ts_driver);

MODULE_AUTHOR("Vincent Knecht <vincent.knecht@mailoo.org>");
MODULE_DESCRIPTION("MStar MSG2638 touchscreen driver");
MODULE_LICENSE("GPL v2");
