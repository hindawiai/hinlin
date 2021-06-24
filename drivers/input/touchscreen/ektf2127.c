<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ELAN eKTF2127 i2c touchscreen controller
 *
 * For this driver the layout of the Chipone icn8318 i2c
 * touchscreencontroller is used.
 *
 * Author:
 * Michel Verlaan <michel.verl@gmail.com>
 * Siebren Vroegindeweij <siebren.vroegindeweij@hoपंचांगail.com>
 *
 * Original chipone_icn8318 driver:
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
#समावेश <linux/delay.h>

/* Packet header defines (first byte of data send / received) */
#घोषणा EKTF2127_NOISE			0x40
#घोषणा EKTF2127_RESPONSE		0x52
#घोषणा EKTF2127_REQUEST		0x53
#घोषणा EKTF2127_HELLO			0x55
#घोषणा EKTF2127_REPORT2		0x5a
#घोषणा EKTF2127_REPORT			0x5d
#घोषणा EKTF2127_CALIB_DONE		0x66

/* Register defines (second byte of data send / received) */
#घोषणा EKTF2127_ENV_NOISY		0x41
#घोषणा EKTF2127_HEIGHT			0x60
#घोषणा EKTF2127_WIDTH			0x63

/* 2 bytes header + 5 * 3 bytes coordinates + 3 bytes pressure info + footer */
#घोषणा EKTF2127_TOUCH_REPORT_SIZE	21
#घोषणा EKTF2127_MAX_TOUCHES		5

काष्ठा ektf2127_ts अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *घातer_gpios;
	काष्ठा touchscreen_properties prop;
पूर्ण;

अटल व्योम ektf2127_parse_coordinates(स्थिर u8 *buf, अचिन्हित पूर्णांक touch_count,
				       काष्ठा input_mt_pos *touches)
अणु
	पूर्णांक index = 0;
	पूर्णांक i;

	क्रम (i = 0; i < touch_count; i++) अणु
		index = 2 + i * 3;

		touches[i].x = (buf[index] & 0x0f);
		touches[i].x <<= 8;
		touches[i].x |= buf[index + 2];

		touches[i].y = (buf[index] & 0xf0);
		touches[i].y <<= 4;
		touches[i].y |= buf[index + 1];
	पूर्ण
पूर्ण

अटल व्योम ektf2127_report_event(काष्ठा ektf2127_ts *ts, स्थिर u8 *buf)
अणु
	काष्ठा input_mt_pos touches[EKTF2127_MAX_TOUCHES];
	पूर्णांक slots[EKTF2127_MAX_TOUCHES];
	अचिन्हित पूर्णांक touch_count, i;

	touch_count = buf[1] & 0x07;
	अगर (touch_count > EKTF2127_MAX_TOUCHES) अणु
		dev_err(&ts->client->dev,
			"Too many touches %d > %d\n",
			touch_count, EKTF2127_MAX_TOUCHES);
		touch_count = EKTF2127_MAX_TOUCHES;
	पूर्ण

	ektf2127_parse_coordinates(buf, touch_count, touches);
	input_mt_assign_slots(ts->input, slots, touches,
			      touch_count, 0);

	क्रम (i = 0; i < touch_count; i++) अणु
		input_mt_slot(ts->input, slots[i]);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, true);
		touchscreen_report_pos(ts->input, &ts->prop,
				       touches[i].x, touches[i].y, true);
	पूर्ण

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
पूर्ण

अटल व्योम ektf2127_report2_contact(काष्ठा ektf2127_ts *ts, पूर्णांक slot,
				     स्थिर u8 *buf, bool active)
अणु
	input_mt_slot(ts->input, slot);
	input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, active);

	अगर (active) अणु
		पूर्णांक x = (buf[0] & 0xf0) << 4 | buf[1];
		पूर्णांक y = (buf[0] & 0x0f) << 8 | buf[2];

		touchscreen_report_pos(ts->input, &ts->prop, x, y, true);
	पूर्ण
पूर्ण

अटल व्योम ektf2127_report2_event(काष्ठा ektf2127_ts *ts, स्थिर u8 *buf)
अणु
	ektf2127_report2_contact(ts, 0, &buf[1], !!(buf[7] & 2));
	ektf2127_report2_contact(ts, 1, &buf[4], !!(buf[7] & 4));

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
पूर्ण

अटल irqवापस_t ektf2127_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ektf2127_ts *ts = dev_id;
	काष्ठा device *dev = &ts->client->dev;
	अक्षर buf[EKTF2127_TOUCH_REPORT_SIZE];
	पूर्णांक ret;

	ret = i2c_master_recv(ts->client, buf, EKTF2127_TOUCH_REPORT_SIZE);
	अगर (ret != EKTF2127_TOUCH_REPORT_SIZE) अणु
		dev_err(dev, "Error reading touch data: %d\n", ret);
		जाओ out;
	पूर्ण

	चयन (buf[0]) अणु
	हाल EKTF2127_REPORT:
		ektf2127_report_event(ts, buf);
		अवरोध;

	हाल EKTF2127_REPORT2:
		ektf2127_report2_event(ts, buf);
		अवरोध;

	हाल EKTF2127_NOISE:
		अगर (buf[1] == EKTF2127_ENV_NOISY)
			dev_dbg(dev, "Environment is electrically noisy\n");
		अवरोध;

	हाल EKTF2127_HELLO:
	हाल EKTF2127_CALIB_DONE:
		अवरोध;

	शेष:
		dev_err(dev, "Unexpected packet header byte %#02x\n", buf[0]);
		अवरोध;
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ektf2127_start(काष्ठा input_dev *dev)
अणु
	काष्ठा ektf2127_ts *ts = input_get_drvdata(dev);

	enable_irq(ts->client->irq);
	gpiod_set_value_cansleep(ts->घातer_gpios, 1);

	वापस 0;
पूर्ण

अटल व्योम ektf2127_stop(काष्ठा input_dev *dev)
अणु
	काष्ठा ektf2127_ts *ts = input_get_drvdata(dev);

	disable_irq(ts->client->irq);
	gpiod_set_value_cansleep(ts->घातer_gpios, 0);
पूर्ण

अटल पूर्णांक __maybe_unused ektf2127_suspend(काष्ठा device *dev)
अणु
	काष्ठा ektf2127_ts *ts = i2c_get_clientdata(to_i2c_client(dev));

	mutex_lock(&ts->input->mutex);
	अगर (input_device_enabled(ts->input))
		ektf2127_stop(ts->input);
	mutex_unlock(&ts->input->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ektf2127_resume(काष्ठा device *dev)
अणु
	काष्ठा ektf2127_ts *ts = i2c_get_clientdata(to_i2c_client(dev));

	mutex_lock(&ts->input->mutex);
	अगर (input_device_enabled(ts->input))
		ektf2127_start(ts->input);
	mutex_unlock(&ts->input->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ektf2127_pm_ops, ektf2127_suspend,
			 ektf2127_resume);

अटल पूर्णांक ektf2127_query_dimension(काष्ठा i2c_client *client, bool width)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर अक्षर *what = width ? "width" : "height";
	u8 what_code = width ? EKTF2127_WIDTH : EKTF2127_HEIGHT;
	u8 buf[4];
	पूर्णांक ret;
	पूर्णांक error;

	/* Request dimension */
	buf[0] = EKTF2127_REQUEST;
	buf[1] = width ? EKTF2127_WIDTH : EKTF2127_HEIGHT;
	buf[2] = 0x00;
	buf[3] = 0x00;
	ret = i2c_master_send(client, buf, माप(buf));
	अगर (ret != माप(buf)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(dev, "Failed to request %s: %d\n", what, error);
		वापस error;
	पूर्ण

	msleep(20);

	/* Read response */
	ret = i2c_master_recv(client, buf, माप(buf));
	अगर (ret != माप(buf)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(dev, "Failed to receive %s data: %d\n", what, error);
		वापस error;
	पूर्ण

	अगर (buf[0] != EKTF2127_RESPONSE || buf[1] != what_code) अणु
		dev_err(dev, "Unexpected %s data: %#02x %#02x\n",
			what, buf[0], buf[1]);
		वापस -EIO;
	पूर्ण

	वापस (((buf[3] & 0xf0) << 4) | buf[2]) - 1;
पूर्ण

अटल पूर्णांक ektf2127_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ektf2127_ts *ts;
	काष्ठा input_dev *input;
	u8 buf[4];
	पूर्णांक max_x, max_y;
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(dev, "Error no irq specified\n");
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	/* This requests the gpio *and* turns on the touchscreen controller */
	ts->घातer_gpios = devm_gpiod_get(dev, "power", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts->घातer_gpios)) अणु
		error = PTR_ERR(ts->घातer_gpios);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Error getting power gpio: %d\n", error);
		वापस error;
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->खोलो = ektf2127_start;
	input->बंद = ektf2127_stop;

	ts->client = client;

	/* Read hello (ignore result, depends on initial घातer state) */
	msleep(20);
	i2c_master_recv(ts->client, buf, माप(buf));

	/* Read resolution from chip */
	max_x = ektf2127_query_dimension(client, true);
	अगर (max_x < 0)
		वापस max_x;

	max_y = ektf2127_query_dimension(client, false);
	अगर (max_y < 0)
		वापस max_y;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	touchscreen_parse_properties(input, true, &ts->prop);

	error = input_mt_init_slots(input, EKTF2127_MAX_TOUCHES,
				    INPUT_MT_सूचीECT |
					INPUT_MT_DROP_UNUSED |
					INPUT_MT_TRACK);
	अगर (error)
		वापस error;

	ts->input = input;
	input_set_drvdata(input, ts);

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, ektf2127_irq,
					  IRQF_ONESHOT, client->name, ts);
	अगर (error) अणु
		dev_err(dev, "Error requesting irq: %d\n", error);
		वापस error;
	पूर्ण

	/* Stop device till खोलोed */
	ektf2127_stop(ts->input);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, ts);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ektf2127_of_match[] = अणु
	अणु .compatible = "elan,ektf2127" पूर्ण,
	अणु .compatible = "elan,ektf2132" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ektf2127_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id ektf2127_i2c_id[] = अणु
	अणु "ektf2127", 0 पूर्ण,
	अणु "ektf2132", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ektf2127_i2c_id);

अटल काष्ठा i2c_driver ektf2127_driver = अणु
	.driver = अणु
		.name	= "elan_ektf2127",
		.pm	= &ektf2127_pm_ops,
		.of_match_table = of_match_ptr(ektf2127_of_match),
	पूर्ण,
	.probe = ektf2127_probe,
	.id_table = ektf2127_i2c_id,
पूर्ण;
module_i2c_driver(ektf2127_driver);

MODULE_DESCRIPTION("ELAN eKTF2127/eKTF2132 I2C Touchscreen Driver");
MODULE_AUTHOR("Michel Verlaan, Siebren Vroegindeweij");
MODULE_LICENSE("GPL");
