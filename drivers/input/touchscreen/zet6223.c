<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016, Jelle van der Waa <jelle@vdwaa.nl>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा ZET6223_MAX_FINGERS		16
#घोषणा ZET6223_MAX_PKT_SIZE		(3 + 4 * ZET6223_MAX_FINGERS)

#घोषणा ZET6223_CMD_INFO		0xB2
#घोषणा ZET6223_CMD_INFO_LENGTH		17
#घोषणा ZET6223_VALID_PACKET		0x3c

#घोषणा ZET6223_POWER_ON_DELAY_MSEC	30

काष्ठा zet6223_ts अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा regulator *vcc;
	काष्ठा regulator *vio;
	काष्ठा touchscreen_properties prop;
	काष्ठा regulator_bulk_data supplies[2];
	u16 max_x;
	u16 max_y;
	u8 fingernum;
पूर्ण;

अटल पूर्णांक zet6223_start(काष्ठा input_dev *dev)
अणु
	काष्ठा zet6223_ts *ts = input_get_drvdata(dev);

	enable_irq(ts->client->irq);

	वापस 0;
पूर्ण

अटल व्योम zet6223_stop(काष्ठा input_dev *dev)
अणु
	काष्ठा zet6223_ts *ts = input_get_drvdata(dev);

	disable_irq(ts->client->irq);
पूर्ण

अटल irqवापस_t zet6223_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zet6223_ts *ts = dev_id;
	u16 finger_bits;

	/*
	 * First 3 bytes are an identअगरier, two bytes of finger data.
	 * X, Y data per finger is 4 bytes.
	 */
	u8 bufsize = 3 + 4 * ts->fingernum;
	u8 buf[ZET6223_MAX_PKT_SIZE];
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक error;

	ret = i2c_master_recv(ts->client, buf, bufsize);
	अगर (ret != bufsize) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err_ratelimited(&ts->client->dev,
				    "Error reading input data: %d\n", error);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (buf[0] != ZET6223_VALID_PACKET)
		वापस IRQ_HANDLED;

	finger_bits = get_unaligned_be16(buf + 1);
	क्रम (i = 0; i < ts->fingernum; i++) अणु
		अगर (!(finger_bits & BIT(15 - i)))
			जारी;

		input_mt_slot(ts->input, i);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, true);
		input_event(ts->input, EV_ABS, ABS_MT_POSITION_X,
				((buf[i + 3] >> 4) << 8) + buf[i + 4]);
		input_event(ts->input, EV_ABS, ABS_MT_POSITION_Y,
				((buf[i + 3] & 0xF) << 8) + buf[i + 5]);
	पूर्ण

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम zet6223_घातer_off(व्योम *_ts)
अणु
	काष्ठा zet6223_ts *ts = _ts;

	regulator_bulk_disable(ARRAY_SIZE(ts->supplies), ts->supplies);
पूर्ण

अटल पूर्णांक zet6223_घातer_on(काष्ठा zet6223_ts *ts)
अणु
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक error;

	ts->supplies[0].supply = "vio";
	ts->supplies[1].supply = "vcc";

	error = devm_regulator_bulk_get(dev, ARRAY_SIZE(ts->supplies),
					ts->supplies);
	अगर (error)
		वापस error;

	error = regulator_bulk_enable(ARRAY_SIZE(ts->supplies), ts->supplies);
	अगर (error)
		वापस error;

	msleep(ZET6223_POWER_ON_DELAY_MSEC);

	error = devm_add_action_or_reset(dev, zet6223_घातer_off, ts);
	अगर (error) अणु
		dev_err(dev, "failed to install poweroff action: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zet6223_query_device(काष्ठा zet6223_ts *ts)
अणु
	u8 buf[ZET6223_CMD_INFO_LENGTH];
	u8 cmd = ZET6223_CMD_INFO;
	पूर्णांक ret;
	पूर्णांक error;

	ret = i2c_master_send(ts->client, &cmd, माप(cmd));
	अगर (ret != माप(cmd)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"touchpanel info cmd failed: %d\n", error);
		वापस error;
	पूर्ण

	ret = i2c_master_recv(ts->client, buf, माप(buf));
	अगर (ret != माप(buf)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"failed to retrieve touchpanel info: %d\n", error);
		वापस error;
	पूर्ण

	ts->fingernum = buf[15] & 0x7F;
	अगर (ts->fingernum > ZET6223_MAX_FINGERS) अणु
		dev_warn(&ts->client->dev,
			 "touchpanel reports %d fingers, limiting to %d\n",
			 ts->fingernum, ZET6223_MAX_FINGERS);
		ts->fingernum = ZET6223_MAX_FINGERS;
	पूर्ण

	ts->max_x = get_unaligned_le16(&buf[8]);
	ts->max_y = get_unaligned_le16(&buf[10]);

	वापस 0;
पूर्ण

अटल पूर्णांक zet6223_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा zet6223_ts *ts;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(dev, "no irq specified\n");
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;

	error = zet6223_घातer_on(ts);
	अगर (error)
		वापस error;

	error = zet6223_query_device(ts);
	अगर (error)
		वापस error;

	ts->input = input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input_set_drvdata(input, ts);

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->खोलो = zet6223_start;
	input->बंद = zet6223_stop;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, ts->max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, ts->max_y, 0, 0);

	touchscreen_parse_properties(input, true, &ts->prop);

	error = input_mt_init_slots(input, ts->fingernum,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, zet6223_irq,
					  IRQF_ONESHOT, client->name, ts);
	अगर (error) अणु
		dev_err(dev, "failed to request irq %d: %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	zet6223_stop(input);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zet6223_of_match[] = अणु
	अणु .compatible = "zeitec,zet6223" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zet6223_of_match);

अटल स्थिर काष्ठा i2c_device_id zet6223_id[] = अणु
	अणु "zet6223", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, zet6223_id);

अटल काष्ठा i2c_driver zet6223_driver = अणु
	.driver = अणु
		.name = "zet6223",
		.of_match_table = zet6223_of_match,
	पूर्ण,
	.probe = zet6223_probe,
	.id_table = zet6223_id
पूर्ण;
module_i2c_driver(zet6223_driver);

MODULE_AUTHOR("Jelle van der Waa <jelle@vdwaa.nl>");
MODULE_DESCRIPTION("ZEITEC zet622x I2C touchscreen driver");
MODULE_LICENSE("GPL");
