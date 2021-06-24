<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2013 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * based in parts on Nook zक्रमce driver
 *
 * Copyright (C) 2010 Barnes & Noble, Inc.
 * Author: Pieter Truter<ptruter@पूर्णांकrinsyc.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/platक्रमm_data/zक्रमce_ts.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of.h>

#घोषणा WAIT_TIMEOUT		msecs_to_jअगरfies(1000)

#घोषणा FRAME_START		0xee
#घोषणा FRAME_MAXSIZE		257

/* Offsets of the dअगरferent parts of the payload the controller sends */
#घोषणा PAYLOAD_HEADER		0
#घोषणा PAYLOAD_LENGTH		1
#घोषणा PAYLOAD_BODY		2

/* Response offsets */
#घोषणा RESPONSE_ID		0
#घोषणा RESPONSE_DATA		1

/* Commands */
#घोषणा COMMAND_DEACTIVATE	0x00
#घोषणा COMMAND_INITIALIZE	0x01
#घोषणा COMMAND_RESOLUTION	0x02
#घोषणा COMMAND_SETCONFIG	0x03
#घोषणा COMMAND_DATAREQUEST	0x04
#घोषणा COMMAND_SCANFREQ	0x08
#घोषणा COMMAND_STATUS		0X1e

/*
 * Responses the controller sends as a result of
 * command requests
 */
#घोषणा RESPONSE_DEACTIVATE	0x00
#घोषणा RESPONSE_INITIALIZE	0x01
#घोषणा RESPONSE_RESOLUTION	0x02
#घोषणा RESPONSE_SETCONFIG	0x03
#घोषणा RESPONSE_SCANFREQ	0x08
#घोषणा RESPONSE_STATUS		0X1e

/*
 * Notअगरications are sent by the touch controller without
 * being requested by the driver and include क्रम example
 * touch indications
 */
#घोषणा NOTIFICATION_TOUCH		0x04
#घोषणा NOTIFICATION_BOOTCOMPLETE	0x07
#घोषणा NOTIFICATION_OVERRUN		0x25
#घोषणा NOTIFICATION_PROXIMITY		0x26
#घोषणा NOTIFICATION_INVALID_COMMAND	0xfe

#घोषणा ZFORCE_REPORT_POINTS		2
#घोषणा ZFORCE_MAX_AREA			0xff

#घोषणा STATE_DOWN			0
#घोषणा STATE_MOVE			1
#घोषणा STATE_UP			2

#घोषणा SETCONFIG_DUALTOUCH		(1 << 0)

काष्ठा zक्रमce_poपूर्णांक अणु
	पूर्णांक coord_x;
	पूर्णांक coord_y;
	पूर्णांक state;
	पूर्णांक id;
	पूर्णांक area_major;
	पूर्णांक area_minor;
	पूर्णांक orientation;
	पूर्णांक pressure;
	पूर्णांक prblty;
पूर्ण;

/*
 * @client		the i2c_client
 * @input		the input device
 * @suspending		in the process of going to suspend (करोn't emit wakeup
 *			events क्रम commands executed to suspend the device)
 * @suspended		device suspended
 * @access_mutex	serialize i2c-access, to keep multipart पढ़ोs together
 * @command_करोne	completion to रुको क्रम the command result
 * @command_mutex	serialize commands sent to the ic
 * @command_रुकोing	the id of the command that is currently रुकोing
 *			क्रम a result
 * @command_result	वापसed result of the command
 */
काष्ठा zक्रमce_ts अणु
	काष्ठा i2c_client	*client;
	काष्ठा input_dev	*input;
	स्थिर काष्ठा zक्रमce_ts_platdata *pdata;
	अक्षर			phys[32];

	काष्ठा regulator	*reg_vdd;

	काष्ठा gpio_desc	*gpio_पूर्णांक;
	काष्ठा gpio_desc	*gpio_rst;

	bool			suspending;
	bool			suspended;
	bool			boot_complete;

	/* Firmware version inक्रमmation */
	u16			version_major;
	u16			version_minor;
	u16			version_build;
	u16			version_rev;

	काष्ठा mutex		access_mutex;

	काष्ठा completion	command_करोne;
	काष्ठा mutex		command_mutex;
	पूर्णांक			command_रुकोing;
	पूर्णांक			command_result;
पूर्ण;

अटल पूर्णांक zक्रमce_command(काष्ठा zक्रमce_ts *ts, u8 cmd)
अणु
	काष्ठा i2c_client *client = ts->client;
	अक्षर buf[3];
	पूर्णांक ret;

	dev_dbg(&client->dev, "%s: 0x%x\n", __func__, cmd);

	buf[0] = FRAME_START;
	buf[1] = 1; /* data size, command only */
	buf[2] = cmd;

	mutex_lock(&ts->access_mutex);
	ret = i2c_master_send(client, &buf[0], ARRAY_SIZE(buf));
	mutex_unlock(&ts->access_mutex);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "i2c send data request error: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम zक्रमce_reset_निश्चित(काष्ठा zक्रमce_ts *ts)
अणु
	gpiod_set_value_cansleep(ts->gpio_rst, 1);
पूर्ण

अटल व्योम zक्रमce_reset_deनिश्चित(काष्ठा zक्रमce_ts *ts)
अणु
	gpiod_set_value_cansleep(ts->gpio_rst, 0);
पूर्ण

अटल पूर्णांक zक्रमce_send_रुको(काष्ठा zक्रमce_ts *ts, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	ret = mutex_trylock(&ts->command_mutex);
	अगर (!ret) अणु
		dev_err(&client->dev, "already waiting for a command\n");
		वापस -EBUSY;
	पूर्ण

	dev_dbg(&client->dev, "sending %d bytes for command 0x%x\n",
		buf[1], buf[2]);

	ts->command_रुकोing = buf[2];

	mutex_lock(&ts->access_mutex);
	ret = i2c_master_send(client, buf, len);
	mutex_unlock(&ts->access_mutex);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "i2c send data request error: %d\n", ret);
		जाओ unlock;
	पूर्ण

	dev_dbg(&client->dev, "waiting for result for command 0x%x\n", buf[2]);

	अगर (रुको_क्रम_completion_समयout(&ts->command_करोne, WAIT_TIMEOUT) == 0) अणु
		ret = -ETIME;
		जाओ unlock;
	पूर्ण

	ret = ts->command_result;

unlock:
	mutex_unlock(&ts->command_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक zक्रमce_command_रुको(काष्ठा zक्रमce_ts *ts, u8 cmd)
अणु
	काष्ठा i2c_client *client = ts->client;
	अक्षर buf[3];
	पूर्णांक ret;

	dev_dbg(&client->dev, "%s: 0x%x\n", __func__, cmd);

	buf[0] = FRAME_START;
	buf[1] = 1; /* data size, command only */
	buf[2] = cmd;

	ret = zक्रमce_send_रुको(ts, &buf[0], ARRAY_SIZE(buf));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "i2c send data request error: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zक्रमce_resolution(काष्ठा zक्रमce_ts *ts, u16 x, u16 y)
अणु
	काष्ठा i2c_client *client = ts->client;
	अक्षर buf[7] = अणु FRAME_START, 5, COMMAND_RESOLUTION,
			(x & 0xff), ((x >> 8) & 0xff),
			(y & 0xff), ((y >> 8) & 0xff) पूर्ण;

	dev_dbg(&client->dev, "set resolution to (%d,%d)\n", x, y);

	वापस zक्रमce_send_रुको(ts, &buf[0], ARRAY_SIZE(buf));
पूर्ण

अटल पूर्णांक zक्रमce_scan_frequency(काष्ठा zक्रमce_ts *ts, u16 idle, u16 finger,
				 u16 stylus)
अणु
	काष्ठा i2c_client *client = ts->client;
	अक्षर buf[9] = अणु FRAME_START, 7, COMMAND_SCANFREQ,
			(idle & 0xff), ((idle >> 8) & 0xff),
			(finger & 0xff), ((finger >> 8) & 0xff),
			(stylus & 0xff), ((stylus >> 8) & 0xff) पूर्ण;

	dev_dbg(&client->dev,
		"set scan frequency to (idle: %d, finger: %d, stylus: %d)\n",
		idle, finger, stylus);

	वापस zक्रमce_send_रुको(ts, &buf[0], ARRAY_SIZE(buf));
पूर्ण

अटल पूर्णांक zक्रमce_setconfig(काष्ठा zक्रमce_ts *ts, अक्षर b1)
अणु
	काष्ठा i2c_client *client = ts->client;
	अक्षर buf[7] = अणु FRAME_START, 5, COMMAND_SETCONFIG,
			b1, 0, 0, 0 पूर्ण;

	dev_dbg(&client->dev, "set config to (%d)\n", b1);

	वापस zक्रमce_send_रुको(ts, &buf[0], ARRAY_SIZE(buf));
पूर्ण

अटल पूर्णांक zक्रमce_start(काष्ठा zक्रमce_ts *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर काष्ठा zक्रमce_ts_platdata *pdata = ts->pdata;
	पूर्णांक ret;

	dev_dbg(&client->dev, "starting device\n");

	ret = zक्रमce_command_रुको(ts, COMMAND_INITIALIZE);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to initialize, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zक्रमce_resolution(ts, pdata->x_max, pdata->y_max);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to set resolution, %d\n", ret);
		जाओ error;
	पूर्ण

	ret = zक्रमce_scan_frequency(ts, 10, 50, 50);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to set scan frequency, %d\n",
			ret);
		जाओ error;
	पूर्ण

	ret = zक्रमce_setconfig(ts, SETCONFIG_DUALTOUCH);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to set config\n");
		जाओ error;
	पूर्ण

	/* start sending touch events */
	ret = zक्रमce_command(ts, COMMAND_DATAREQUEST);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to request data\n");
		जाओ error;
	पूर्ण

	/*
	 * Per NN, initial cal. take max. of 200msec.
	 * Allow समय to complete this calibration
	 */
	msleep(200);

	वापस 0;

error:
	zक्रमce_command_रुको(ts, COMMAND_DEACTIVATE);
	वापस ret;
पूर्ण

अटल पूर्णांक zक्रमce_stop(काष्ठा zक्रमce_ts *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "stopping device\n");

	/* Deactivates touch sensing and माला_दो the device पूर्णांकo sleep. */
	ret = zक्रमce_command_रुको(ts, COMMAND_DEACTIVATE);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "could not deactivate device, %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zक्रमce_touch_event(काष्ठा zक्रमce_ts *ts, u8 *payload)
अणु
	काष्ठा i2c_client *client = ts->client;
	स्थिर काष्ठा zक्रमce_ts_platdata *pdata = ts->pdata;
	काष्ठा zक्रमce_poपूर्णांक poपूर्णांक;
	पूर्णांक count, i, num = 0;

	count = payload[0];
	अगर (count > ZFORCE_REPORT_POINTS) अणु
		dev_warn(&client->dev,
			 "too many coordinates %d, expected max %d\n",
			 count, ZFORCE_REPORT_POINTS);
		count = ZFORCE_REPORT_POINTS;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		poपूर्णांक.coord_x =
			payload[9 * i + 2] << 8 | payload[9 * i + 1];
		poपूर्णांक.coord_y =
			payload[9 * i + 4] << 8 | payload[9 * i + 3];

		अगर (poपूर्णांक.coord_x > pdata->x_max ||
		    poपूर्णांक.coord_y > pdata->y_max) अणु
			dev_warn(&client->dev, "coordinates (%d,%d) invalid\n",
				poपूर्णांक.coord_x, poपूर्णांक.coord_y);
			poपूर्णांक.coord_x = poपूर्णांक.coord_y = 0;
		पूर्ण

		poपूर्णांक.state = payload[9 * i + 5] & 0x0f;
		poपूर्णांक.id = (payload[9 * i + 5] & 0xf0) >> 4;

		/* determine touch major, minor and orientation */
		poपूर्णांक.area_major = max(payload[9 * i + 6],
					  payload[9 * i + 7]);
		poपूर्णांक.area_minor = min(payload[9 * i + 6],
					  payload[9 * i + 7]);
		poपूर्णांक.orientation = payload[9 * i + 6] > payload[9 * i + 7];

		poपूर्णांक.pressure = payload[9 * i + 8];
		poपूर्णांक.prblty = payload[9 * i + 9];

		dev_dbg(&client->dev,
			"point %d/%d: state %d, id %d, pressure %d, prblty %d, x %d, y %d, amajor %d, aminor %d, ori %d\n",
			i, count, poपूर्णांक.state, poपूर्णांक.id,
			poपूर्णांक.pressure, poपूर्णांक.prblty,
			poपूर्णांक.coord_x, poपूर्णांक.coord_y,
			poपूर्णांक.area_major, poपूर्णांक.area_minor,
			poपूर्णांक.orientation);

		/* the zक्रमce id starts with "1", so needs to be decreased */
		input_mt_slot(ts->input, poपूर्णांक.id - 1);

		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER,
						poपूर्णांक.state != STATE_UP);

		अगर (poपूर्णांक.state != STATE_UP) अणु
			input_report_असल(ts->input, ABS_MT_POSITION_X,
					 poपूर्णांक.coord_x);
			input_report_असल(ts->input, ABS_MT_POSITION_Y,
					 poपूर्णांक.coord_y);
			input_report_असल(ts->input, ABS_MT_TOUCH_MAJOR,
					 poपूर्णांक.area_major);
			input_report_असल(ts->input, ABS_MT_TOUCH_MINOR,
					 poपूर्णांक.area_minor);
			input_report_असल(ts->input, ABS_MT_ORIENTATION,
					 poपूर्णांक.orientation);
			num++;
		पूर्ण
	पूर्ण

	input_mt_sync_frame(ts->input);

	input_mt_report_finger_count(ts->input, num);

	input_sync(ts->input);

	वापस 0;
पूर्ण

अटल पूर्णांक zक्रमce_पढ़ो_packet(काष्ठा zक्रमce_ts *ts, u8 *buf)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	mutex_lock(&ts->access_mutex);

	/* पढ़ो 2 byte message header */
	ret = i2c_master_recv(client, buf, 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error reading header: %d\n", ret);
		जाओ unlock;
	पूर्ण

	अगर (buf[PAYLOAD_HEADER] != FRAME_START) अणु
		dev_err(&client->dev, "invalid frame start: %d\n", buf[0]);
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	अगर (buf[PAYLOAD_LENGTH] == 0) अणु
		dev_err(&client->dev, "invalid payload length: %d\n",
			buf[PAYLOAD_LENGTH]);
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	/* पढ़ो the message */
	ret = i2c_master_recv(client, &buf[PAYLOAD_BODY], buf[PAYLOAD_LENGTH]);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error reading payload: %d\n", ret);
		जाओ unlock;
	पूर्ण

	dev_dbg(&client->dev, "read %d bytes for response command 0x%x\n",
		buf[PAYLOAD_LENGTH], buf[PAYLOAD_BODY]);

unlock:
	mutex_unlock(&ts->access_mutex);
	वापस ret;
पूर्ण

अटल व्योम zक्रमce_complete(काष्ठा zक्रमce_ts *ts, पूर्णांक cmd, पूर्णांक result)
अणु
	काष्ठा i2c_client *client = ts->client;

	अगर (ts->command_रुकोing == cmd) अणु
		dev_dbg(&client->dev, "completing command 0x%x\n", cmd);
		ts->command_result = result;
		complete(&ts->command_करोne);
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "command %d not for us\n", cmd);
	पूर्ण
पूर्ण

अटल irqवापस_t zक्रमce_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zक्रमce_ts *ts = dev_id;
	काष्ठा i2c_client *client = ts->client;

	अगर (ts->suspended && device_may_wakeup(&client->dev))
		pm_wakeup_event(&client->dev, 500);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t zक्रमce_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा zक्रमce_ts *ts = dev_id;
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;
	u8 payload_buffer[FRAME_MAXSIZE];
	u8 *payload;

	/*
	 * When still suspended, वापस.
	 * Due to the level-पूर्णांकerrupt we will get re-triggered later.
	 */
	अगर (ts->suspended) अणु
		msleep(20);
		वापस IRQ_HANDLED;
	पूर्ण

	dev_dbg(&client->dev, "handling interrupt\n");

	/* Don't emit wakeup events from commands run by zक्रमce_suspend */
	अगर (!ts->suspending && device_may_wakeup(&client->dev))
		pm_stay_awake(&client->dev);

	/*
	 * Run at least once and निकास the loop अगर
	 * - the optional पूर्णांकerrupt GPIO isn't specअगरied
	 *   (there is only one packet पढ़ो per ISR invocation, then)
	 * or
	 * - the GPIO isn't active any more
	 *   (packet पढ़ो until the level GPIO indicates that there is
	 *    no IRQ any more)
	 */
	करो अणु
		ret = zक्रमce_पढ़ो_packet(ts, payload_buffer);
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"could not read packet, ret: %d\n", ret);
			अवरोध;
		पूर्ण

		payload =  &payload_buffer[PAYLOAD_BODY];

		चयन (payload[RESPONSE_ID]) अणु
		हाल NOTIFICATION_TOUCH:
			/*
			 * Always report touch-events received जबतक
			 * suspending, when being a wakeup source
			 */
			अगर (ts->suspending && device_may_wakeup(&client->dev))
				pm_wakeup_event(&client->dev, 500);
			zक्रमce_touch_event(ts, &payload[RESPONSE_DATA]);
			अवरोध;

		हाल NOTIFICATION_BOOTCOMPLETE:
			ts->boot_complete = payload[RESPONSE_DATA];
			zक्रमce_complete(ts, payload[RESPONSE_ID], 0);
			अवरोध;

		हाल RESPONSE_INITIALIZE:
		हाल RESPONSE_DEACTIVATE:
		हाल RESPONSE_SETCONFIG:
		हाल RESPONSE_RESOLUTION:
		हाल RESPONSE_SCANFREQ:
			zक्रमce_complete(ts, payload[RESPONSE_ID],
					payload[RESPONSE_DATA]);
			अवरोध;

		हाल RESPONSE_STATUS:
			/*
			 * Version Payload Results
			 * [2:major] [2:minor] [2:build] [2:rev]
			 */
			ts->version_major = (payload[RESPONSE_DATA + 1] << 8) |
						payload[RESPONSE_DATA];
			ts->version_minor = (payload[RESPONSE_DATA + 3] << 8) |
						payload[RESPONSE_DATA + 2];
			ts->version_build = (payload[RESPONSE_DATA + 5] << 8) |
						payload[RESPONSE_DATA + 4];
			ts->version_rev   = (payload[RESPONSE_DATA + 7] << 8) |
						payload[RESPONSE_DATA + 6];
			dev_dbg(&ts->client->dev,
				"Firmware Version %04x:%04x %04x:%04x\n",
				ts->version_major, ts->version_minor,
				ts->version_build, ts->version_rev);

			zक्रमce_complete(ts, payload[RESPONSE_ID], 0);
			अवरोध;

		हाल NOTIFICATION_INVALID_COMMAND:
			dev_err(&ts->client->dev, "invalid command: 0x%x\n",
				payload[RESPONSE_DATA]);
			अवरोध;

		शेष:
			dev_err(&ts->client->dev,
				"unrecognized response id: 0x%x\n",
				payload[RESPONSE_ID]);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (gpiod_get_value_cansleep(ts->gpio_पूर्णांक));

	अगर (!ts->suspending && device_may_wakeup(&client->dev))
		pm_relax(&client->dev);

	dev_dbg(&client->dev, "finished interrupt\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक zक्रमce_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा zक्रमce_ts *ts = input_get_drvdata(dev);

	वापस zक्रमce_start(ts);
पूर्ण

अटल व्योम zक्रमce_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा zक्रमce_ts *ts = input_get_drvdata(dev);
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक ret;

	ret = zक्रमce_stop(ts);
	अगर (ret)
		dev_warn(&client->dev, "stopping zforce failed\n");

	वापस;
पूर्ण

अटल पूर्णांक __maybe_unused zक्रमce_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा zक्रमce_ts *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;
	पूर्णांक ret = 0;

	mutex_lock(&input->mutex);
	ts->suspending = true;

	/*
	 * When configured as a wakeup source device should always wake
	 * the प्रणाली, thereक्रमe start device अगर necessary.
	 */
	अगर (device_may_wakeup(&client->dev)) अणु
		dev_dbg(&client->dev, "suspend while being a wakeup source\n");

		/* Need to start device, अगर not खोलो, to be a wakeup source. */
		अगर (!input_device_enabled(input)) अणु
			ret = zक्रमce_start(ts);
			अगर (ret)
				जाओ unlock;
		पूर्ण

		enable_irq_wake(client->irq);
	पूर्ण अन्यथा अगर (input_device_enabled(input)) अणु
		dev_dbg(&client->dev,
			"suspend without being a wakeup source\n");

		ret = zक्रमce_stop(ts);
		अगर (ret)
			जाओ unlock;

		disable_irq(client->irq);
	पूर्ण

	ts->suspended = true;

unlock:
	ts->suspending = false;
	mutex_unlock(&input->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused zक्रमce_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा zक्रमce_ts *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;
	पूर्णांक ret = 0;

	mutex_lock(&input->mutex);

	ts->suspended = false;

	अगर (device_may_wakeup(&client->dev)) अणु
		dev_dbg(&client->dev, "resume from being a wakeup source\n");

		disable_irq_wake(client->irq);

		/* need to stop device अगर it was not खोलो on suspend */
		अगर (!input_device_enabled(input)) अणु
			ret = zक्रमce_stop(ts);
			अगर (ret)
				जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अगर (input_device_enabled(input)) अणु
		dev_dbg(&client->dev, "resume without being a wakeup source\n");

		enable_irq(client->irq);

		ret = zक्रमce_start(ts);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

unlock:
	mutex_unlock(&input->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(zक्रमce_pm_ops, zक्रमce_suspend, zक्रमce_resume);

अटल व्योम zक्रमce_reset(व्योम *data)
अणु
	काष्ठा zक्रमce_ts *ts = data;

	zक्रमce_reset_निश्चित(ts);

	udelay(10);

	अगर (!IS_ERR(ts->reg_vdd))
		regulator_disable(ts->reg_vdd);
पूर्ण

अटल काष्ठा zक्रमce_ts_platdata *zक्रमce_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा zक्रमce_ts_platdata *pdata;
	काष्ठा device_node *np = dev->of_node;

	अगर (!np)
		वापस ERR_PTR(-ENOENT);

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(dev, "failed to allocate platform data\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "x-size", &pdata->x_max)) अणु
		dev_err(dev, "failed to get x-size property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "y-size", &pdata->y_max)) अणु
		dev_err(dev, "failed to get y-size property\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस pdata;
पूर्ण

अटल पूर्णांक zक्रमce_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा zक्रमce_ts_platdata *pdata = dev_get_platdata(&client->dev);
	काष्ठा zक्रमce_ts *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक ret;

	अगर (!pdata) अणु
		pdata = zक्रमce_parse_dt(&client->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(काष्ठा zक्रमce_ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->gpio_rst = devm_gpiod_get_optional(&client->dev, "reset",
					       GPIOD_OUT_HIGH);
	अगर (IS_ERR(ts->gpio_rst)) अणु
		ret = PTR_ERR(ts->gpio_rst);
		dev_err(&client->dev,
			"failed to request reset GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ts->gpio_rst) अणु
		ts->gpio_पूर्णांक = devm_gpiod_get_optional(&client->dev, "irq",
						       GPIOD_IN);
		अगर (IS_ERR(ts->gpio_पूर्णांक)) अणु
			ret = PTR_ERR(ts->gpio_पूर्णांक);
			dev_err(&client->dev,
				"failed to request interrupt GPIO: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Deprecated GPIO handling क्रम compatibility
		 * with legacy binding.
		 */

		/* INT GPIO */
		ts->gpio_पूर्णांक = devm_gpiod_get_index(&client->dev, शून्य, 0,
						    GPIOD_IN);
		अगर (IS_ERR(ts->gpio_पूर्णांक)) अणु
			ret = PTR_ERR(ts->gpio_पूर्णांक);
			dev_err(&client->dev,
				"failed to request interrupt GPIO: %d\n", ret);
			वापस ret;
		पूर्ण

		/* RST GPIO */
		ts->gpio_rst = devm_gpiod_get_index(&client->dev, शून्य, 1,
					    GPIOD_OUT_HIGH);
		अगर (IS_ERR(ts->gpio_rst)) अणु
			ret = PTR_ERR(ts->gpio_rst);
			dev_err(&client->dev,
				"failed to request reset GPIO: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ts->reg_vdd = devm_regulator_get_optional(&client->dev, "vdd");
	अगर (IS_ERR(ts->reg_vdd)) अणु
		ret = PTR_ERR(ts->reg_vdd);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(ts->reg_vdd);
		अगर (ret)
			वापस ret;

		/*
		 * according to datasheet add 100us grace समय after regular
		 * regulator enable delay.
		 */
		udelay(100);
	पूर्ण

	ret = devm_add_action(&client->dev, zक्रमce_reset, ts);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to register reset action, %d\n",
			ret);

		/* hereafter the regulator will be disabled by the action */
		अगर (!IS_ERR(ts->reg_vdd))
			regulator_disable(ts->reg_vdd);

		वापस ret;
	पूर्ण

	snम_लिखो(ts->phys, माप(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev) अणु
		dev_err(&client->dev, "could not allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&ts->access_mutex);
	mutex_init(&ts->command_mutex);

	ts->pdata = pdata;
	ts->client = client;
	ts->input = input_dev;

	input_dev->name = "Neonode zForce touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;

	input_dev->खोलो = zक्रमce_input_खोलो;
	input_dev->बंद = zक्रमce_input_बंद;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_SYN, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);

	/* For multi touch */
	input_set_असल_params(input_dev, ABS_MT_POSITION_X, 0,
			     pdata->x_max, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_POSITION_Y, 0,
			     pdata->y_max, 0, 0);

	input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
			     ZFORCE_MAX_AREA, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MINOR, 0,
			     ZFORCE_MAX_AREA, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);
	input_mt_init_slots(input_dev, ZFORCE_REPORT_POINTS, INPUT_MT_सूचीECT);

	input_set_drvdata(ts->input, ts);

	init_completion(&ts->command_करोne);

	/*
	 * The zक्रमce pulls the पूर्णांकerrupt low when it has data पढ़ोy.
	 * After it is triggered the isr thपढ़ो runs until all the available
	 * packets have been पढ़ो and the पूर्णांकerrupt is high again.
	 * Thereक्रमe we can trigger the पूर्णांकerrupt anyसमय it is low and करो
	 * not need to limit it to the पूर्णांकerrupt edge.
	 */
	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					zक्रमce_irq, zक्रमce_irq_thपढ़ो,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					input_dev->name, ts);
	अगर (ret) अणु
		dev_err(&client->dev, "irq %d request failed\n", client->irq);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, ts);

	/* let the controller boot */
	zक्रमce_reset_deनिश्चित(ts);

	ts->command_रुकोing = NOTIFICATION_BOOTCOMPLETE;
	अगर (रुको_क्रम_completion_समयout(&ts->command_करोne, WAIT_TIMEOUT) == 0)
		dev_warn(&client->dev, "bootcomplete timed out\n");

	/* need to start device to get version inक्रमmation */
	ret = zक्रमce_command_रुको(ts, COMMAND_INITIALIZE);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to initialize, %d\n", ret);
		वापस ret;
	पूर्ण

	/* this माला_लो the firmware version among other inक्रमmation */
	ret = zक्रमce_command_रुको(ts, COMMAND_STATUS);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "couldn't get status, %d\n", ret);
		zक्रमce_stop(ts);
		वापस ret;
	पूर्ण

	/* stop device and put it पूर्णांकo sleep until it is खोलोed */
	ret = zक्रमce_stop(ts);
	अगर (ret < 0)
		वापस ret;

	device_set_wakeup_capable(&client->dev, true);

	ret = input_रेजिस्टर_device(input_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "could not register input device, %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i2c_device_id zक्रमce_idtable[] = अणु
	अणु "zforce-ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, zक्रमce_idtable);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id zक्रमce_dt_idtable[] = अणु
	अणु .compatible = "neonode,zforce" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zक्रमce_dt_idtable);
#पूर्ण_अगर

अटल काष्ठा i2c_driver zक्रमce_driver = अणु
	.driver = अणु
		.name	= "zforce-ts",
		.pm	= &zक्रमce_pm_ops,
		.of_match_table	= of_match_ptr(zक्रमce_dt_idtable),
	पूर्ण,
	.probe		= zक्रमce_probe,
	.id_table	= zक्रमce_idtable,
पूर्ण;

module_i2c_driver(zक्रमce_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("zForce TouchScreen Driver");
MODULE_LICENSE("GPL");
