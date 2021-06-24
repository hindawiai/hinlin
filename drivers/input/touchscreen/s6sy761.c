<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Samsung S6SY761 Touchscreen device driver
//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
// Copyright (c) 2017 Andi Shyti <andi@etezian.org>

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>

/* commands */
#घोषणा S6SY761_SENSE_ON		0x10
#घोषणा S6SY761_SENSE_OFF		0x11
#घोषणा S6SY761_TOUCH_FUNCTION		0x30 /* R/W क्रम get/set */
#घोषणा S6SY761_FIRMWARE_INTEGRITY	0x21
#घोषणा S6SY761_PANEL_INFO		0x23
#घोषणा S6SY761_DEVICE_ID		0x52
#घोषणा S6SY761_BOOT_STATUS		0x55
#घोषणा S6SY761_READ_ONE_EVENT		0x60
#घोषणा S6SY761_READ_ALL_EVENT		0x61
#घोषणा S6SY761_CLEAR_EVENT_STACK	0x62
#घोषणा S6SY761_APPLICATION_MODE	0xe4

/* events */
#घोषणा S6SY761_EVENT_INFO		0x02
#घोषणा S6SY761_EVENT_VENDOR_INFO	0x07

/* info */
#घोषणा S6SY761_INFO_BOOT_COMPLETE	0x00

/* firmware status */
#घोषणा S6SY761_FW_OK			0x80

/*
 * the functionalities are put as a reference
 * as in the device I am using none of them
 * works thereक्रमe not used in this driver yet.
 */
/* touchscreen functionalities */
#घोषणा S6SY761_MASK_TOUCH		BIT(0)
#घोषणा S6SY761_MASK_HOVER		BIT(1)
#घोषणा S6SY761_MASK_COVER		BIT(2)
#घोषणा S6SY761_MASK_GLOVE		BIT(3)
#घोषणा S6SY761_MASK_STYLUS		BIT(4)
#घोषणा S6SY761_MASK_PALM		BIT(5)
#घोषणा S6SY761_MASK_WET		BIT(6)
#घोषणा S6SY761_MASK_PROXIMITY		BIT(7)

/* boot status (BS) */
#घोषणा S6SY761_BS_BOOT_LOADER		0x10
#घोषणा S6SY761_BS_APPLICATION		0x20

/* event id */
#घोषणा S6SY761_EVENT_ID_COORDINATE	0x00
#घोषणा S6SY761_EVENT_ID_STATUS		0x01

/* event रेजिस्टर masks */
#घोषणा S6SY761_MASK_TOUCH_STATE	0xc0 /* byte 0 */
#घोषणा S6SY761_MASK_TID		0x3c
#घोषणा S6SY761_MASK_EID		0x03
#घोषणा S6SY761_MASK_X			0xf0 /* byte 3 */
#घोषणा S6SY761_MASK_Y			0x0f
#घोषणा S6SY761_MASK_Z			0x3f /* byte 6 */
#घोषणा S6SY761_MASK_LEFT_EVENTS	0x3f /* byte 7 */
#घोषणा S6SY761_MASK_TOUCH_TYPE		0xc0 /* MSB in byte 6, LSB in byte 7 */

/* event touch state values */
#घोषणा S6SY761_TS_NONE			0x00
#घोषणा S6SY761_TS_PRESS		0x01
#घोषणा S6SY761_TS_MOVE			0x02
#घोषणा S6SY761_TS_RELEASE		0x03

/* application modes */
#घोषणा S6SY761_APP_NORMAL		0x0
#घोषणा S6SY761_APP_LOW_POWER		0x1
#घोषणा S6SY761_APP_TEST		0x2
#घोषणा S6SY761_APP_FLASH		0x3
#घोषणा S6SY761_APP_SLEEP		0x4

#घोषणा S6SY761_EVENT_SIZE		8
#घोषणा S6SY761_EVENT_COUNT		32
#घोषणा S6SY761_DEVID_SIZE		3
#घोषणा S6SY761_PANEL_ID_SIZE		11
#घोषणा S6SY761_TS_STATUS_SIZE		5
#घोषणा S6SY761_MAX_FINGERS		10

#घोषणा S6SY761_DEV_NAME	"s6sy761"

क्रमागत s6sy761_regulators अणु
	S6SY761_REGULATOR_VDD,
	S6SY761_REGULATOR_AVDD,
पूर्ण;

काष्ठा s6sy761_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regulator_bulk_data regulators[2];
	काष्ठा input_dev *input;
	काष्ठा touchscreen_properties prop;

	u8 data[S6SY761_EVENT_SIZE * S6SY761_EVENT_COUNT];

	u16 devid;
	u8 tx_channel;
पूर्ण;

/*
 * We can't simply use i2c_smbus_पढ़ो_i2c_block_data because we
 * need to पढ़ो more than 255 bytes
 */
अटल पूर्णांक s6sy761_पढ़ो_events(काष्ठा s6sy761_data *sdata, u16 n_events)
अणु
	u8 cmd = S6SY761_READ_ALL_EVENT;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr	= sdata->client->addr,
			.len	= 1,
			.buf	= &cmd,
		पूर्ण,
		अणु
			.addr	= sdata->client->addr,
			.flags	= I2C_M_RD,
			.len	= (n_events * S6SY761_EVENT_SIZE),
			.buf	= sdata->data + S6SY761_EVENT_SIZE,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(sdata->client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;

	वापस ret == ARRAY_SIZE(msgs) ? 0 : -EIO;
पूर्ण

अटल व्योम s6sy761_report_coordinates(काष्ठा s6sy761_data *sdata,
				       u8 *event, u8 tid)
अणु
	u8 major = event[4];
	u8 minor = event[5];
	u8 z = event[6] & S6SY761_MASK_Z;
	u16 x = (event[1] << 4) | ((event[3] & S6SY761_MASK_X) >> 4);
	u16 y = (event[2] << 4) | (event[3] & S6SY761_MASK_Y);

	input_mt_slot(sdata->input, tid);

	input_mt_report_slot_state(sdata->input, MT_TOOL_FINGER, true);
	input_report_असल(sdata->input, ABS_MT_POSITION_X, x);
	input_report_असल(sdata->input, ABS_MT_POSITION_Y, y);
	input_report_असल(sdata->input, ABS_MT_TOUCH_MAJOR, major);
	input_report_असल(sdata->input, ABS_MT_TOUCH_MINOR, minor);
	input_report_असल(sdata->input, ABS_MT_PRESSURE, z);

	input_sync(sdata->input);
पूर्ण

अटल व्योम s6sy761_report_release(काष्ठा s6sy761_data *sdata,
				   u8 *event, u8 tid)
अणु
	input_mt_slot(sdata->input, tid);
	input_mt_report_slot_state(sdata->input, MT_TOOL_FINGER, false);

	input_sync(sdata->input);
पूर्ण

अटल व्योम s6sy761_handle_coordinates(काष्ठा s6sy761_data *sdata, u8 *event)
अणु
	u8 tid;
	u8 touch_state;

	अगर (unlikely(!(event[0] & S6SY761_MASK_TID)))
		वापस;

	tid = ((event[0] & S6SY761_MASK_TID) >> 2) - 1;
	touch_state = (event[0] & S6SY761_MASK_TOUCH_STATE) >> 6;

	चयन (touch_state) अणु

	हाल S6SY761_TS_NONE:
		अवरोध;
	हाल S6SY761_TS_RELEASE:
		s6sy761_report_release(sdata, event, tid);
		अवरोध;
	हाल S6SY761_TS_PRESS:
	हाल S6SY761_TS_MOVE:
		s6sy761_report_coordinates(sdata, event, tid);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम s6sy761_handle_events(काष्ठा s6sy761_data *sdata, u8 n_events)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_events; i++) अणु
		u8 *event = &sdata->data[i * S6SY761_EVENT_SIZE];
		u8 event_id = event[0] & S6SY761_MASK_EID;

		अगर (!event[0])
			वापस;

		चयन (event_id) अणु

		हाल S6SY761_EVENT_ID_COORDINATE:
			s6sy761_handle_coordinates(sdata, event);
			अवरोध;

		हाल S6SY761_EVENT_ID_STATUS:
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t s6sy761_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा s6sy761_data *sdata = dev;
	पूर्णांक ret;
	u8 n_events;

	ret = i2c_smbus_पढ़ो_i2c_block_data(sdata->client,
					    S6SY761_READ_ONE_EVENT,
					    S6SY761_EVENT_SIZE,
					    sdata->data);
	अगर (ret < 0) अणु
		dev_err(&sdata->client->dev, "failed to read events\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!sdata->data[0])
		वापस IRQ_HANDLED;

	n_events = sdata->data[7] & S6SY761_MASK_LEFT_EVENTS;
	अगर (unlikely(n_events > S6SY761_EVENT_COUNT - 1))
		वापस IRQ_HANDLED;

	अगर (n_events) अणु
		ret = s6sy761_पढ़ो_events(sdata, n_events);
		अगर (ret < 0) अणु
			dev_err(&sdata->client->dev, "failed to read events\n");
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण

	s6sy761_handle_events(sdata, n_events +  1);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s6sy761_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा s6sy761_data *sdata = input_get_drvdata(dev);

	वापस i2c_smbus_ग_लिखो_byte(sdata->client, S6SY761_SENSE_ON);
पूर्ण

अटल व्योम s6sy761_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा s6sy761_data *sdata = input_get_drvdata(dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(sdata->client, S6SY761_SENSE_OFF);
	अगर (ret)
		dev_err(&sdata->client->dev, "failed to turn off sensing\n");
पूर्ण

अटल sमाप_प्रकार s6sy761_sysfs_devid(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा s6sy761_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", sdata->devid);
पूर्ण

अटल DEVICE_ATTR(devid, 0444, s6sy761_sysfs_devid, शून्य);

अटल काष्ठा attribute *s6sy761_sysfs_attrs[] = अणु
	&dev_attr_devid.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group s6sy761_attribute_group = अणु
	.attrs = s6sy761_sysfs_attrs
पूर्ण;

अटल पूर्णांक s6sy761_घातer_on(काष्ठा s6sy761_data *sdata)
अणु
	u8 buffer[S6SY761_EVENT_SIZE];
	u8 event;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(sdata->regulators),
				    sdata->regulators);
	अगर (ret)
		वापस ret;

	msleep(140);

	/* द्विगुन check whether the touch is functional */
	ret = i2c_smbus_पढ़ो_i2c_block_data(sdata->client,
					    S6SY761_READ_ONE_EVENT,
					    S6SY761_EVENT_SIZE,
					    buffer);
	अगर (ret < 0)
		वापस ret;

	event = (buffer[0] >> 2) & 0xf;

	अगर ((event != S6SY761_EVENT_INFO &&
	     event != S6SY761_EVENT_VENDOR_INFO) ||
	    buffer[1] != S6SY761_INFO_BOOT_COMPLETE) अणु
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(sdata->client, S6SY761_BOOT_STATUS);
	अगर (ret < 0)
		वापस ret;

	/* क्रम some reasons the device might be stuck in the bootloader */
	अगर (ret != S6SY761_BS_APPLICATION)
		वापस -ENODEV;

	/* enable touch functionality */
	ret = i2c_smbus_ग_लिखो_word_data(sdata->client,
					S6SY761_TOUCH_FUNCTION,
					S6SY761_MASK_TOUCH);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक s6sy761_hw_init(काष्ठा s6sy761_data *sdata,
			   अचिन्हित पूर्णांक *max_x, अचिन्हित पूर्णांक *max_y)
अणु
	u8 buffer[S6SY761_PANEL_ID_SIZE]; /* larger पढ़ो size */
	पूर्णांक ret;

	ret = s6sy761_घातer_on(sdata);
	अगर (ret)
		वापस ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(sdata->client,
					    S6SY761_DEVICE_ID,
					    S6SY761_DEVID_SIZE,
					    buffer);
	अगर (ret < 0)
		वापस ret;

	sdata->devid = get_unaligned_be16(buffer + 1);

	ret = i2c_smbus_पढ़ो_i2c_block_data(sdata->client,
					    S6SY761_PANEL_INFO,
					    S6SY761_PANEL_ID_SIZE,
					    buffer);
	अगर (ret < 0)
		वापस ret;

	*max_x = get_unaligned_be16(buffer);
	*max_y = get_unaligned_be16(buffer + 2);

	/* अगर no tx channels defined, at least keep one */
	sdata->tx_channel = max_t(u8, buffer[8], 1);

	ret = i2c_smbus_पढ़ो_byte_data(sdata->client,
				       S6SY761_FIRMWARE_INTEGRITY);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != S6SY761_FW_OK)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम s6sy761_घातer_off(व्योम *data)
अणु
	काष्ठा s6sy761_data *sdata = data;

	disable_irq(sdata->client->irq);
	regulator_bulk_disable(ARRAY_SIZE(sdata->regulators),
						sdata->regulators);
पूर्ण

अटल पूर्णांक s6sy761_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा s6sy761_data *sdata;
	अचिन्हित पूर्णांक max_x, max_y;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
						I2C_FUNC_SMBUS_BYTE_DATA |
						I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -ENODEV;

	sdata = devm_kzalloc(&client->dev, माप(*sdata), GFP_KERNEL);
	अगर (!sdata)
		वापस -ENOMEM;

	i2c_set_clientdata(client, sdata);
	sdata->client = client;

	sdata->regulators[S6SY761_REGULATOR_VDD].supply = "vdd";
	sdata->regulators[S6SY761_REGULATOR_AVDD].supply = "avdd";
	err = devm_regulator_bulk_get(&client->dev,
				      ARRAY_SIZE(sdata->regulators),
				      sdata->regulators);
	अगर (err)
		वापस err;

	err = devm_add_action_or_reset(&client->dev, s6sy761_घातer_off, sdata);
	अगर (err)
		वापस err;

	err = s6sy761_hw_init(sdata, &max_x, &max_y);
	अगर (err)
		वापस err;

	sdata->input = devm_input_allocate_device(&client->dev);
	अगर (!sdata->input)
		वापस -ENOMEM;

	sdata->input->name = S6SY761_DEV_NAME;
	sdata->input->id.bustype = BUS_I2C;
	sdata->input->खोलो = s6sy761_input_खोलो;
	sdata->input->बंद = s6sy761_input_बंद;

	input_set_असल_params(sdata->input, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_PRESSURE, 0, 255, 0, 0);

	touchscreen_parse_properties(sdata->input, true, &sdata->prop);

	अगर (!input_असल_get_max(sdata->input, ABS_X) ||
	    !input_असल_get_max(sdata->input, ABS_Y)) अणु
		dev_warn(&client->dev, "the axis have not been set\n");
	पूर्ण

	err = input_mt_init_slots(sdata->input, sdata->tx_channel,
				  INPUT_MT_सूचीECT);
	अगर (err)
		वापस err;

	input_set_drvdata(sdata->input, sdata);

	err = input_रेजिस्टर_device(sdata->input);
	अगर (err)
		वापस err;

	err = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					s6sy761_irq_handler,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"s6sy761_irq", sdata);
	अगर (err)
		वापस err;

	err = devm_device_add_group(&client->dev, &s6sy761_attribute_group);
	अगर (err)
		वापस err;

	pm_runसमय_enable(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक s6sy761_हटाओ(काष्ठा i2c_client *client)
अणु
	pm_runसमय_disable(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused s6sy761_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा s6sy761_data *sdata = dev_get_drvdata(dev);

	वापस i2c_smbus_ग_लिखो_byte_data(sdata->client,
				S6SY761_APPLICATION_MODE, S6SY761_APP_SLEEP);
पूर्ण

अटल पूर्णांक __maybe_unused s6sy761_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा s6sy761_data *sdata = dev_get_drvdata(dev);

	वापस i2c_smbus_ग_लिखो_byte_data(sdata->client,
				S6SY761_APPLICATION_MODE, S6SY761_APP_NORMAL);
पूर्ण

अटल पूर्णांक __maybe_unused s6sy761_suspend(काष्ठा device *dev)
अणु
	काष्ठा s6sy761_data *sdata = dev_get_drvdata(dev);

	s6sy761_घातer_off(sdata);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused s6sy761_resume(काष्ठा device *dev)
अणु
	काष्ठा s6sy761_data *sdata = dev_get_drvdata(dev);

	enable_irq(sdata->client->irq);

	वापस s6sy761_घातer_on(sdata);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops s6sy761_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(s6sy761_suspend, s6sy761_resume)
	SET_RUNTIME_PM_OPS(s6sy761_runसमय_suspend,
				s6sy761_runसमय_resume, शून्य)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id s6sy761_of_match[] = अणु
	अणु .compatible = "samsung,s6sy761", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s6sy761_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id s6sy761_id[] = अणु
	अणु "s6sy761", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s6sy761_id);

अटल काष्ठा i2c_driver s6sy761_driver = अणु
	.driver = अणु
		.name = S6SY761_DEV_NAME,
		.of_match_table = of_match_ptr(s6sy761_of_match),
		.pm = &s6sy761_pm_ops,
	पूर्ण,
	.probe = s6sy761_probe,
	.हटाओ = s6sy761_हटाओ,
	.id_table = s6sy761_id,
पूर्ण;

module_i2c_driver(s6sy761_driver);

MODULE_AUTHOR("Andi Shyti <andi.shyti@samsung.com>");
MODULE_DESCRIPTION("Samsung S6SY761 Touch Screen");
MODULE_LICENSE("GPL v2");
