<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// STMicroelectronics FTS Touchscreen device driver
//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
// Copyright (c) 2017 Andi Shyti <andi@etezian.org>

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>

/* I2C commands */
#घोषणा STMFTS_READ_INFO			0x80
#घोषणा STMFTS_READ_STATUS			0x84
#घोषणा STMFTS_READ_ONE_EVENT			0x85
#घोषणा STMFTS_READ_ALL_EVENT			0x86
#घोषणा STMFTS_LATEST_EVENT			0x87
#घोषणा STMFTS_SLEEP_IN				0x90
#घोषणा STMFTS_SLEEP_OUT			0x91
#घोषणा STMFTS_MS_MT_SENSE_OFF			0x92
#घोषणा STMFTS_MS_MT_SENSE_ON			0x93
#घोषणा STMFTS_SS_HOVER_SENSE_OFF		0x94
#घोषणा STMFTS_SS_HOVER_SENSE_ON		0x95
#घोषणा STMFTS_MS_KEY_SENSE_OFF			0x9a
#घोषणा STMFTS_MS_KEY_SENSE_ON			0x9b
#घोषणा STMFTS_SYSTEM_RESET			0xa0
#घोषणा STMFTS_CLEAR_EVENT_STACK		0xa1
#घोषणा STMFTS_FULL_FORCE_CALIBRATION		0xa2
#घोषणा STMFTS_MS_CX_TUNING			0xa3
#घोषणा STMFTS_SS_CX_TUNING			0xa4

/* events */
#घोषणा STMFTS_EV_NO_EVENT			0x00
#घोषणा STMFTS_EV_MULTI_TOUCH_DETECTED		0x02
#घोषणा STMFTS_EV_MULTI_TOUCH_ENTER		0x03
#घोषणा STMFTS_EV_MULTI_TOUCH_LEAVE		0x04
#घोषणा STMFTS_EV_MULTI_TOUCH_MOTION		0x05
#घोषणा STMFTS_EV_HOVER_ENTER			0x07
#घोषणा STMFTS_EV_HOVER_LEAVE			0x08
#घोषणा STMFTS_EV_HOVER_MOTION			0x09
#घोषणा STMFTS_EV_KEY_STATUS			0x0e
#घोषणा STMFTS_EV_ERROR				0x0f
#घोषणा STMFTS_EV_CONTROLLER_READY		0x10
#घोषणा STMFTS_EV_SLEEP_OUT_CONTROLLER_READY	0x11
#घोषणा STMFTS_EV_STATUS			0x16
#घोषणा STMFTS_EV_DEBUG				0xdb

/* multi touch related event masks */
#घोषणा STMFTS_MASK_EVENT_ID			0x0f
#घोषणा STMFTS_MASK_TOUCH_ID			0xf0
#घोषणा STMFTS_MASK_LEFT_EVENT			0x0f
#घोषणा STMFTS_MASK_X_MSB			0x0f
#घोषणा STMFTS_MASK_Y_LSB			0xf0

/* key related event masks */
#घोषणा STMFTS_MASK_KEY_NO_TOUCH		0x00
#घोषणा STMFTS_MASK_KEY_MENU			0x01
#घोषणा STMFTS_MASK_KEY_BACK			0x02

#घोषणा STMFTS_EVENT_SIZE	8
#घोषणा STMFTS_STACK_DEPTH	32
#घोषणा STMFTS_DATA_MAX_SIZE	(STMFTS_EVENT_SIZE * STMFTS_STACK_DEPTH)
#घोषणा STMFTS_MAX_FINGERS	10
#घोषणा STMFTS_DEV_NAME		"stmfts"

क्रमागत sपंचांगfts_regulators अणु
	STMFTS_REGULATOR_VDD,
	STMFTS_REGULATOR_AVDD,
पूर्ण;

काष्ठा sपंचांगfts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा led_classdev led_cdev;
	काष्ठा mutex mutex;

	काष्ठा touchscreen_properties prop;

	काष्ठा regulator_bulk_data regulators[2];

	/*
	 * Presence of ledvdd will be used also to check
	 * whether the LED is supported.
	 */
	काष्ठा regulator *ledvdd;

	u16 chip_id;
	u8 chip_ver;
	u16 fw_ver;
	u8 config_id;
	u8 config_ver;

	u8 data[STMFTS_DATA_MAX_SIZE];

	काष्ठा completion cmd_करोne;

	bool use_key;
	bool led_status;
	bool hover_enabled;
	bool running;
पूर्ण;

अटल पूर्णांक sपंचांगfts_brightness_set(काष्ठा led_classdev *led_cdev,
					क्रमागत led_brightness value)
अणु
	काष्ठा sपंचांगfts_data *sdata = container_of(led_cdev,
					काष्ठा sपंचांगfts_data, led_cdev);
	पूर्णांक err;

	अगर (value != sdata->led_status && sdata->ledvdd) अणु
		अगर (!value) अणु
			regulator_disable(sdata->ledvdd);
		पूर्ण अन्यथा अणु
			err = regulator_enable(sdata->ledvdd);
			अगर (err) अणु
				dev_warn(&sdata->client->dev,
					 "failed to disable ledvdd regulator: %d\n",
					 err);
				वापस err;
			पूर्ण
		पूर्ण
		sdata->led_status = value;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत led_brightness sपंचांगfts_brightness_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा sपंचांगfts_data *sdata = container_of(led_cdev,
						काष्ठा sपंचांगfts_data, led_cdev);

	वापस !!regulator_is_enabled(sdata->ledvdd);
पूर्ण

/*
 * We can't simply use i2c_smbus_पढ़ो_i2c_block_data because we
 * need to पढ़ो more than 255 bytes (
 */
अटल पूर्णांक sपंचांगfts_पढ़ो_events(काष्ठा sपंचांगfts_data *sdata)
अणु
	u8 cmd = STMFTS_READ_ALL_EVENT;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr	= sdata->client->addr,
			.len	= 1,
			.buf	= &cmd,
		पूर्ण,
		अणु
			.addr	= sdata->client->addr,
			.flags	= I2C_M_RD,
			.len	= STMFTS_DATA_MAX_SIZE,
			.buf	= sdata->data,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(sdata->client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;

	वापस ret == ARRAY_SIZE(msgs) ? 0 : -EIO;
पूर्ण

अटल व्योम sपंचांगfts_report_contact_event(काष्ठा sपंचांगfts_data *sdata,
					स्थिर u8 event[])
अणु
	u8 slot_id = (event[0] & STMFTS_MASK_TOUCH_ID) >> 4;
	u16 x = event[1] | ((event[2] & STMFTS_MASK_X_MSB) << 8);
	u16 y = (event[2] >> 4) | (event[3] << 4);
	u8 maj = event[4];
	u8 min = event[5];
	u8 orientation = event[6];
	u8 area = event[7];

	input_mt_slot(sdata->input, slot_id);

	input_mt_report_slot_state(sdata->input, MT_TOOL_FINGER, true);
	input_report_असल(sdata->input, ABS_MT_POSITION_X, x);
	input_report_असल(sdata->input, ABS_MT_POSITION_Y, y);
	input_report_असल(sdata->input, ABS_MT_TOUCH_MAJOR, maj);
	input_report_असल(sdata->input, ABS_MT_TOUCH_MINOR, min);
	input_report_असल(sdata->input, ABS_MT_PRESSURE, area);
	input_report_असल(sdata->input, ABS_MT_ORIENTATION, orientation);

	input_sync(sdata->input);
पूर्ण

अटल व्योम sपंचांगfts_report_contact_release(काष्ठा sपंचांगfts_data *sdata,
					  स्थिर u8 event[])
अणु
	u8 slot_id = (event[0] & STMFTS_MASK_TOUCH_ID) >> 4;

	input_mt_slot(sdata->input, slot_id);
	input_mt_report_slot_inactive(sdata->input);

	input_sync(sdata->input);
पूर्ण

अटल व्योम sपंचांगfts_report_hover_event(काष्ठा sपंचांगfts_data *sdata,
				      स्थिर u8 event[])
अणु
	u16 x = (event[2] << 4) | (event[4] >> 4);
	u16 y = (event[3] << 4) | (event[4] & STMFTS_MASK_Y_LSB);
	u8 z = event[5];

	input_report_असल(sdata->input, ABS_X, x);
	input_report_असल(sdata->input, ABS_Y, y);
	input_report_असल(sdata->input, ABS_DISTANCE, z);

	input_sync(sdata->input);
पूर्ण

अटल व्योम sपंचांगfts_report_key_event(काष्ठा sपंचांगfts_data *sdata, स्थिर u8 event[])
अणु
	चयन (event[2]) अणु
	हाल 0:
		input_report_key(sdata->input, KEY_BACK, 0);
		input_report_key(sdata->input, KEY_MENU, 0);
		अवरोध;

	हाल STMFTS_MASK_KEY_BACK:
		input_report_key(sdata->input, KEY_BACK, 1);
		अवरोध;

	हाल STMFTS_MASK_KEY_MENU:
		input_report_key(sdata->input, KEY_MENU, 1);
		अवरोध;

	शेष:
		dev_warn(&sdata->client->dev,
			 "unknown key event: %#02x\n", event[2]);
		अवरोध;
	पूर्ण

	input_sync(sdata->input);
पूर्ण

अटल व्योम sपंचांगfts_parse_events(काष्ठा sपंचांगfts_data *sdata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < STMFTS_STACK_DEPTH; i++) अणु
		u8 *event = &sdata->data[i * STMFTS_EVENT_SIZE];

		चयन (event[0]) अणु

		हाल STMFTS_EV_CONTROLLER_READY:
		हाल STMFTS_EV_SLEEP_OUT_CONTROLLER_READY:
		हाल STMFTS_EV_STATUS:
			complete(&sdata->cmd_करोne);
			fallthrough;

		हाल STMFTS_EV_NO_EVENT:
		हाल STMFTS_EV_DEBUG:
			वापस;
		पूर्ण

		चयन (event[0] & STMFTS_MASK_EVENT_ID) अणु

		हाल STMFTS_EV_MULTI_TOUCH_ENTER:
		हाल STMFTS_EV_MULTI_TOUCH_MOTION:
			sपंचांगfts_report_contact_event(sdata, event);
			अवरोध;

		हाल STMFTS_EV_MULTI_TOUCH_LEAVE:
			sपंचांगfts_report_contact_release(sdata, event);
			अवरोध;

		हाल STMFTS_EV_HOVER_ENTER:
		हाल STMFTS_EV_HOVER_LEAVE:
		हाल STMFTS_EV_HOVER_MOTION:
			sपंचांगfts_report_hover_event(sdata, event);
			अवरोध;

		हाल STMFTS_EV_KEY_STATUS:
			sपंचांगfts_report_key_event(sdata, event);
			अवरोध;

		हाल STMFTS_EV_ERROR:
			dev_warn(&sdata->client->dev,
					"error code: 0x%x%x%x%x%x%x",
					event[6], event[5], event[4],
					event[3], event[2], event[1]);
			अवरोध;

		शेष:
			dev_err(&sdata->client->dev,
				"unknown event %#02x\n", event[0]);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t sपंचांगfts_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev;
	पूर्णांक err;

	mutex_lock(&sdata->mutex);

	err = sपंचांगfts_पढ़ो_events(sdata);
	अगर (unlikely(err))
		dev_err(&sdata->client->dev,
			"failed to read events: %d\n", err);
	अन्यथा
		sपंचांगfts_parse_events(sdata);

	mutex_unlock(&sdata->mutex);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांगfts_command(काष्ठा sपंचांगfts_data *sdata, स्थिर u8 cmd)
अणु
	पूर्णांक err;

	reinit_completion(&sdata->cmd_करोne);

	err = i2c_smbus_ग_लिखो_byte(sdata->client, cmd);
	अगर (err)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&sdata->cmd_करोne,
					 msecs_to_jअगरfies(1000)))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfts_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = input_get_drvdata(dev);
	पूर्णांक err;

	err = pm_runसमय_get_sync(&sdata->client->dev);
	अगर (err < 0)
		वापस err;

	err = i2c_smbus_ग_लिखो_byte(sdata->client, STMFTS_MS_MT_SENSE_ON);
	अगर (err)
		वापस err;

	mutex_lock(&sdata->mutex);
	sdata->running = true;

	अगर (sdata->hover_enabled) अणु
		err = i2c_smbus_ग_लिखो_byte(sdata->client,
					   STMFTS_SS_HOVER_SENSE_ON);
		अगर (err)
			dev_warn(&sdata->client->dev,
				 "failed to enable hover\n");
	पूर्ण
	mutex_unlock(&sdata->mutex);

	अगर (sdata->use_key) अणु
		err = i2c_smbus_ग_लिखो_byte(sdata->client,
					   STMFTS_MS_KEY_SENSE_ON);
		अगर (err)
			/* I can still use only the touch screen */
			dev_warn(&sdata->client->dev,
				 "failed to enable touchkey\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांगfts_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = input_get_drvdata(dev);
	पूर्णांक err;

	err = i2c_smbus_ग_लिखो_byte(sdata->client, STMFTS_MS_MT_SENSE_OFF);
	अगर (err)
		dev_warn(&sdata->client->dev,
			 "failed to disable touchscreen: %d\n", err);

	mutex_lock(&sdata->mutex);

	sdata->running = false;

	अगर (sdata->hover_enabled) अणु
		err = i2c_smbus_ग_लिखो_byte(sdata->client,
					   STMFTS_SS_HOVER_SENSE_OFF);
		अगर (err)
			dev_warn(&sdata->client->dev,
				 "failed to disable hover: %d\n", err);
	पूर्ण
	mutex_unlock(&sdata->mutex);

	अगर (sdata->use_key) अणु
		err = i2c_smbus_ग_लिखो_byte(sdata->client,
					   STMFTS_MS_KEY_SENSE_OFF);
		अगर (err)
			dev_warn(&sdata->client->dev,
				 "failed to disable touchkey: %d\n", err);
	पूर्ण

	pm_runसमय_put_sync(&sdata->client->dev);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_chip_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", sdata->chip_id);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_chip_version(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", sdata->chip_ver);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_fw_ver(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", sdata->fw_ver);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_config_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%#x\n", sdata->config_id);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_config_version(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", sdata->config_ver);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_पढ़ो_status(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);
	u8 status[4];
	पूर्णांक err;

	err = i2c_smbus_पढ़ो_i2c_block_data(sdata->client, STMFTS_READ_STATUS,
					    माप(status), status);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%#02x\n", status[0]);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_hover_enable_पढ़ो(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", sdata->hover_enabled);
पूर्ण

अटल sमाप_प्रकार sपंचांगfts_sysfs_hover_enable_ग_लिखो(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक err = 0;

	अगर (kम_से_अदीर्घ(buf, 0, &value))
		वापस -EINVAL;

	mutex_lock(&sdata->mutex);

	अगर (value && sdata->hover_enabled)
		जाओ out;

	अगर (sdata->running)
		err = i2c_smbus_ग_लिखो_byte(sdata->client,
					   value ? STMFTS_SS_HOVER_SENSE_ON :
						   STMFTS_SS_HOVER_SENSE_OFF);

	अगर (!err)
		sdata->hover_enabled = !!value;

out:
	mutex_unlock(&sdata->mutex);

	वापस len;
पूर्ण

अटल DEVICE_ATTR(chip_id, 0444, sपंचांगfts_sysfs_chip_id, शून्य);
अटल DEVICE_ATTR(chip_version, 0444, sपंचांगfts_sysfs_chip_version, शून्य);
अटल DEVICE_ATTR(fw_ver, 0444, sपंचांगfts_sysfs_fw_ver, शून्य);
अटल DEVICE_ATTR(config_id, 0444, sपंचांगfts_sysfs_config_id, शून्य);
अटल DEVICE_ATTR(config_version, 0444, sपंचांगfts_sysfs_config_version, शून्य);
अटल DEVICE_ATTR(status, 0444, sपंचांगfts_sysfs_पढ़ो_status, शून्य);
अटल DEVICE_ATTR(hover_enable, 0644, sपंचांगfts_sysfs_hover_enable_पढ़ो,
					sपंचांगfts_sysfs_hover_enable_ग_लिखो);

अटल काष्ठा attribute *sपंचांगfts_sysfs_attrs[] = अणु
	&dev_attr_chip_id.attr,
	&dev_attr_chip_version.attr,
	&dev_attr_fw_ver.attr,
	&dev_attr_config_id.attr,
	&dev_attr_config_version.attr,
	&dev_attr_status.attr,
	&dev_attr_hover_enable.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group sपंचांगfts_attribute_group = अणु
	.attrs = sपंचांगfts_sysfs_attrs
पूर्ण;

अटल पूर्णांक sपंचांगfts_घातer_on(काष्ठा sपंचांगfts_data *sdata)
अणु
	पूर्णांक err;
	u8 reg[8];

	err = regulator_bulk_enable(ARRAY_SIZE(sdata->regulators),
				    sdata->regulators);
	अगर (err)
		वापस err;

	/*
	 * The datasheet करोes not specअगरy the घातer on समय, but considering
	 * that the reset समय is < 10ms, I sleep 20ms to be sure
	 */
	msleep(20);

	err = i2c_smbus_पढ़ो_i2c_block_data(sdata->client, STMFTS_READ_INFO,
					    माप(reg), reg);
	अगर (err < 0)
		वापस err;
	अगर (err != माप(reg))
		वापस -EIO;

	sdata->chip_id = be16_to_cpup((__be16 *)&reg[6]);
	sdata->chip_ver = reg[0];
	sdata->fw_ver = be16_to_cpup((__be16 *)&reg[2]);
	sdata->config_id = reg[4];
	sdata->config_ver = reg[5];

	enable_irq(sdata->client->irq);

	msleep(50);

	err = sपंचांगfts_command(sdata, STMFTS_SYSTEM_RESET);
	अगर (err)
		वापस err;

	err = sपंचांगfts_command(sdata, STMFTS_SLEEP_OUT);
	अगर (err)
		वापस err;

	/* optional tuning */
	err = sपंचांगfts_command(sdata, STMFTS_MS_CX_TUNING);
	अगर (err)
		dev_warn(&sdata->client->dev,
			 "failed to perform mutual auto tune: %d\n", err);

	/* optional tuning */
	err = sपंचांगfts_command(sdata, STMFTS_SS_CX_TUNING);
	अगर (err)
		dev_warn(&sdata->client->dev,
			 "failed to perform self auto tune: %d\n", err);

	err = sपंचांगfts_command(sdata, STMFTS_FULL_FORCE_CALIBRATION);
	अगर (err)
		वापस err;

	/*
	 * At this poपूर्णांक no one is using the touchscreen
	 * and I करोn't really care about the वापस value
	 */
	(व्योम) i2c_smbus_ग_लिखो_byte(sdata->client, STMFTS_SLEEP_IN);

	वापस 0;
पूर्ण

अटल व्योम sपंचांगfts_घातer_off(व्योम *data)
अणु
	काष्ठा sपंचांगfts_data *sdata = data;

	disable_irq(sdata->client->irq);
	regulator_bulk_disable(ARRAY_SIZE(sdata->regulators),
						sdata->regulators);
पूर्ण

/* This function is व्योम because I करोn't want to prevent using the touch key
 * only because the LEDs करोn't get रेजिस्टरed
 */
अटल पूर्णांक sपंचांगfts_enable_led(काष्ठा sपंचांगfts_data *sdata)
अणु
	पूर्णांक err;

	/* get the regulator क्रम घातering the leds on */
	sdata->ledvdd = devm_regulator_get(&sdata->client->dev, "ledvdd");
	अगर (IS_ERR(sdata->ledvdd))
		वापस PTR_ERR(sdata->ledvdd);

	sdata->led_cdev.name = STMFTS_DEV_NAME;
	sdata->led_cdev.max_brightness = LED_ON;
	sdata->led_cdev.brightness = LED_OFF;
	sdata->led_cdev.brightness_set_blocking = sपंचांगfts_brightness_set;
	sdata->led_cdev.brightness_get = sपंचांगfts_brightness_get;

	err = devm_led_classdev_रेजिस्टर(&sdata->client->dev, &sdata->led_cdev);
	अगर (err) अणु
		devm_regulator_put(sdata->ledvdd);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfts_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा sपंचांगfts_data *sdata;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
						I2C_FUNC_SMBUS_BYTE_DATA |
						I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -ENODEV;

	sdata = devm_kzalloc(&client->dev, माप(*sdata), GFP_KERNEL);
	अगर (!sdata)
		वापस -ENOMEM;

	i2c_set_clientdata(client, sdata);

	sdata->client = client;
	mutex_init(&sdata->mutex);
	init_completion(&sdata->cmd_करोne);

	sdata->regulators[STMFTS_REGULATOR_VDD].supply = "vdd";
	sdata->regulators[STMFTS_REGULATOR_AVDD].supply = "avdd";
	err = devm_regulator_bulk_get(&client->dev,
				      ARRAY_SIZE(sdata->regulators),
				      sdata->regulators);
	अगर (err)
		वापस err;

	sdata->input = devm_input_allocate_device(&client->dev);
	अगर (!sdata->input)
		वापस -ENOMEM;

	sdata->input->name = STMFTS_DEV_NAME;
	sdata->input->id.bustype = BUS_I2C;
	sdata->input->खोलो = sपंचांगfts_input_खोलो;
	sdata->input->बंद = sपंचांगfts_input_बंद;

	input_set_capability(sdata->input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(sdata->input, EV_ABS, ABS_MT_POSITION_Y);
	touchscreen_parse_properties(sdata->input, true, &sdata->prop);

	input_set_असल_params(sdata->input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_ORIENTATION, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_MT_PRESSURE, 0, 255, 0, 0);
	input_set_असल_params(sdata->input, ABS_DISTANCE, 0, 255, 0, 0);

	sdata->use_key = device_property_पढ़ो_bool(&client->dev,
						   "touch-key-connected");
	अगर (sdata->use_key) अणु
		input_set_capability(sdata->input, EV_KEY, KEY_MENU);
		input_set_capability(sdata->input, EV_KEY, KEY_BACK);
	पूर्ण

	err = input_mt_init_slots(sdata->input,
				  STMFTS_MAX_FINGERS, INPUT_MT_सूचीECT);
	अगर (err)
		वापस err;

	input_set_drvdata(sdata->input, sdata);

	/*
	 * sपंचांगfts_घातer_on expects पूर्णांकerrupt to be disabled, but
	 * at this poपूर्णांक the device is still off and I करो not trust
	 * the status of the irq line that can generate some spurious
	 * पूर्णांकerrupts. To be on the safe side it's better to not enable
	 * the पूर्णांकerrupts during their request.
	 */
	err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, sपंचांगfts_irq_handler,
					IRQF_ONESHOT | IRQF_NO_AUTOEN,
					"stmfts_irq", sdata);
	अगर (err)
		वापस err;

	dev_dbg(&client->dev, "initializing ST-Microelectronics FTS...\n");

	err = sपंचांगfts_घातer_on(sdata);
	अगर (err)
		वापस err;

	err = devm_add_action_or_reset(&client->dev, sपंचांगfts_घातer_off, sdata);
	अगर (err)
		वापस err;

	err = input_रेजिस्टर_device(sdata->input);
	अगर (err)
		वापस err;

	अगर (sdata->use_key) अणु
		err = sपंचांगfts_enable_led(sdata);
		अगर (err) अणु
			/*
			 * Even अगर the LEDs have failed to be initialized and
			 * used in the driver, I can still use the device even
			 * without LEDs. The ledvdd regulator poपूर्णांकer will be
			 * used as a flag.
			 */
			dev_warn(&client->dev, "unable to use touchkey leds\n");
			sdata->ledvdd = शून्य;
		पूर्ण
	पूर्ण

	err = devm_device_add_group(&client->dev, &sपंचांगfts_attribute_group);
	अगर (err)
		वापस err;

	pm_runसमय_enable(&client->dev);
	device_enable_async_suspend(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfts_हटाओ(काष्ठा i2c_client *client)
अणु
	pm_runसमय_disable(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगfts_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(sdata->client, STMFTS_SLEEP_IN);
	अगर (ret)
		dev_warn(dev, "failed to suspend device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगfts_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(sdata->client, STMFTS_SLEEP_OUT);
	अगर (ret)
		dev_err(dev, "failed to resume device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगfts_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	sपंचांगfts_घातer_off(sdata);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगfts_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfts_data *sdata = dev_get_drvdata(dev);

	वापस sपंचांगfts_घातer_on(sdata);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांगfts_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांगfts_suspend, sपंचांगfts_resume)
	SET_RUNTIME_PM_OPS(sपंचांगfts_runसमय_suspend, sपंचांगfts_runसमय_resume, शून्य)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sपंचांगfts_of_match[] = अणु
	अणु .compatible = "st,stmfts", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगfts_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id sपंचांगfts_id[] = अणु
	अणु "stmfts", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sपंचांगfts_id);

अटल काष्ठा i2c_driver sपंचांगfts_driver = अणु
	.driver = अणु
		.name = STMFTS_DEV_NAME,
		.of_match_table = of_match_ptr(sपंचांगfts_of_match),
		.pm = &sपंचांगfts_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe = sपंचांगfts_probe,
	.हटाओ = sपंचांगfts_हटाओ,
	.id_table = sपंचांगfts_id,
पूर्ण;

module_i2c_driver(sपंचांगfts_driver);

MODULE_AUTHOR("Andi Shyti <andi.shyti@samsung.com>");
MODULE_DESCRIPTION("STMicroelectronics FTS Touch Screen");
MODULE_LICENSE("GPL v2");
