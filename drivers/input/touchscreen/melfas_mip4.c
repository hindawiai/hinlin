<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MELFAS MIP4 Touchscreen
 *
 * Copyright (C) 2016 MELFAS Inc.
 *
 * Author : Sangwon Jee <jeesw@melfas.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा MIP4_DEVICE_NAME	"mip4_ts"

/*****************************************************************
 * Protocol
 * Version : MIP 4.0 Rev 5.4
 *****************************************************************/

/* Address */
#घोषणा MIP4_R0_BOOT				0x00
#घोषणा MIP4_R1_BOOT_MODE			0x01
#घोषणा MIP4_R1_BOOT_BUF_ADDR			0x10
#घोषणा MIP4_R1_BOOT_STATUS			0x20
#घोषणा MIP4_R1_BOOT_CMD			0x30
#घोषणा MIP4_R1_BOOT_TARGET_ADDR		0x40
#घोषणा MIP4_R1_BOOT_SIZE			0x44

#घोषणा MIP4_R0_INFO				0x01
#घोषणा MIP4_R1_INFO_PRODUCT_NAME		0x00
#घोषणा MIP4_R1_INFO_RESOLUTION_X		0x10
#घोषणा MIP4_R1_INFO_RESOLUTION_Y		0x12
#घोषणा MIP4_R1_INFO_NODE_NUM_X			0x14
#घोषणा MIP4_R1_INFO_NODE_NUM_Y			0x15
#घोषणा MIP4_R1_INFO_KEY_NUM			0x16
#घोषणा MIP4_R1_INFO_PRESSURE_NUM		0x17
#घोषणा MIP4_R1_INFO_LENGTH_X			0x18
#घोषणा MIP4_R1_INFO_LENGTH_Y			0x1A
#घोषणा MIP4_R1_INFO_PPM_X			0x1C
#घोषणा MIP4_R1_INFO_PPM_Y			0x1D
#घोषणा MIP4_R1_INFO_VERSION_BOOT		0x20
#घोषणा MIP4_R1_INFO_VERSION_CORE		0x22
#घोषणा MIP4_R1_INFO_VERSION_APP		0x24
#घोषणा MIP4_R1_INFO_VERSION_PARAM		0x26
#घोषणा MIP4_R1_INFO_SECT_BOOT_START		0x30
#घोषणा MIP4_R1_INFO_SECT_BOOT_END		0x31
#घोषणा MIP4_R1_INFO_SECT_CORE_START		0x32
#घोषणा MIP4_R1_INFO_SECT_CORE_END		0x33
#घोषणा MIP4_R1_INFO_SECT_APP_START		0x34
#घोषणा MIP4_R1_INFO_SECT_APP_END		0x35
#घोषणा MIP4_R1_INFO_SECT_PARAM_START		0x36
#घोषणा MIP4_R1_INFO_SECT_PARAM_END		0x37
#घोषणा MIP4_R1_INFO_BUILD_DATE			0x40
#घोषणा MIP4_R1_INFO_BUILD_TIME			0x44
#घोषणा MIP4_R1_INFO_CHECKSUM_PRECALC		0x48
#घोषणा MIP4_R1_INFO_CHECKSUM_REALTIME		0x4A
#घोषणा MIP4_R1_INFO_PROTOCOL_NAME		0x50
#घोषणा MIP4_R1_INFO_PROTOCOL_VERSION		0x58
#घोषणा MIP4_R1_INFO_IC_ID			0x70
#घोषणा MIP4_R1_INFO_IC_NAME			0x71
#घोषणा MIP4_R1_INFO_IC_VENDOR_ID		0x75
#घोषणा MIP4_R1_INFO_IC_HW_CATEGORY		0x77
#घोषणा MIP4_R1_INFO_CONTACT_THD_SCR		0x78
#घोषणा MIP4_R1_INFO_CONTACT_THD_KEY		0x7A
#घोषणा MIP4_R1_INFO_PID				0x7C
#घोषणा MIP4_R1_INFO_VID				0x7E
#घोषणा MIP4_R1_INFO_SLAVE_ADDR			0x80

#घोषणा MIP4_R0_EVENT				0x02
#घोषणा MIP4_R1_EVENT_SUPPORTED_FUNC		0x00
#घोषणा MIP4_R1_EVENT_FORMAT			0x04
#घोषणा MIP4_R1_EVENT_SIZE			0x06
#घोषणा MIP4_R1_EVENT_PACKET_INFO		0x10
#घोषणा MIP4_R1_EVENT_PACKET_DATA		0x11

#घोषणा MIP4_R0_CTRL				0x06
#घोषणा MIP4_R1_CTRL_READY_STATUS		0x00
#घोषणा MIP4_R1_CTRL_EVENT_READY		0x01
#घोषणा MIP4_R1_CTRL_MODE			0x10
#घोषणा MIP4_R1_CTRL_EVENT_TRIGGER_TYPE		0x11
#घोषणा MIP4_R1_CTRL_RECALIBRATE		0x12
#घोषणा MIP4_R1_CTRL_POWER_STATE		0x13
#घोषणा MIP4_R1_CTRL_GESTURE_TYPE		0x14
#घोषणा MIP4_R1_CTRL_DISABLE_ESD_ALERT		0x18
#घोषणा MIP4_R1_CTRL_CHARGER_MODE		0x19
#घोषणा MIP4_R1_CTRL_HIGH_SENS_MODE		0x1A
#घोषणा MIP4_R1_CTRL_WINDOW_MODE		0x1B
#घोषणा MIP4_R1_CTRL_PALM_REJECTION		0x1C
#घोषणा MIP4_R1_CTRL_EDGE_CORRECTION		0x1D
#घोषणा MIP4_R1_CTRL_ENTER_GLOVE_MODE		0x1E
#घोषणा MIP4_R1_CTRL_I2C_ON_LPM			0x1F
#घोषणा MIP4_R1_CTRL_GESTURE_DEBUG		0x20
#घोषणा MIP4_R1_CTRL_PALM_EVENT			0x22
#घोषणा MIP4_R1_CTRL_PROXIMITY_SENSING		0x23

/* Value */
#घोषणा MIP4_BOOT_MODE_BOOT			0x01
#घोषणा MIP4_BOOT_MODE_APP			0x02

#घोषणा MIP4_BOOT_STATUS_BUSY			0x05
#घोषणा MIP4_BOOT_STATUS_ERROR			0x0E
#घोषणा MIP4_BOOT_STATUS_DONE			0xA0

#घोषणा MIP4_BOOT_CMD_MASS_ERASE		0x15
#घोषणा MIP4_BOOT_CMD_PROGRAM			0x54
#घोषणा MIP4_BOOT_CMD_ERASE			0x8F
#घोषणा MIP4_BOOT_CMD_WRITE			0xA5
#घोषणा MIP4_BOOT_CMD_READ			0xC2

#घोषणा MIP4_EVENT_INPUT_TYPE_KEY		0
#घोषणा MIP4_EVENT_INPUT_TYPE_SCREEN		1
#घोषणा MIP4_EVENT_INPUT_TYPE_PROXIMITY		2

#घोषणा I2C_RETRY_COUNT				3	/* 2~ */

#घोषणा MIP4_BUF_SIZE				128
#घोषणा MIP4_MAX_FINGERS			10
#घोषणा MIP4_MAX_KEYS				4

#घोषणा MIP4_TOUCH_MAJOR_MIN			0
#घोषणा MIP4_TOUCH_MAJOR_MAX			255
#घोषणा MIP4_TOUCH_MINOR_MIN			0
#घोषणा MIP4_TOUCH_MINOR_MAX			255
#घोषणा MIP4_PRESSURE_MIN			0
#घोषणा MIP4_PRESSURE_MAX			255

#घोषणा MIP4_FW_NAME			"melfas_mip4.fw"
#घोषणा MIP4_FW_UPDATE_DEBUG		0	/* 0 (शेष) or 1 */

काष्ठा mip4_fw_version अणु
	u16 boot;
	u16 core;
	u16 app;
	u16 param;
पूर्ण;

काष्ठा mip4_ts अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *gpio_ce;

	अक्षर phys[32];
	अक्षर product_name[16];
	u16 product_id;
	अक्षर ic_name[4];
	अक्षर fw_name[32];

	अचिन्हित पूर्णांक max_x;
	अचिन्हित पूर्णांक max_y;
	u8 node_x;
	u8 node_y;
	u8 node_key;
	अचिन्हित पूर्णांक ppm_x;
	अचिन्हित पूर्णांक ppm_y;

	काष्ठा mip4_fw_version fw_version;

	अचिन्हित पूर्णांक event_size;
	अचिन्हित पूर्णांक event_क्रमmat;

	अचिन्हित पूर्णांक key_num;
	अचिन्हित लघु key_code[MIP4_MAX_KEYS];

	bool wake_irq_enabled;

	u8 buf[MIP4_BUF_SIZE];
पूर्ण;

अटल पूर्णांक mip4_i2c_xfer(काष्ठा mip4_ts *ts,
			 अक्षर *ग_लिखो_buf, अचिन्हित पूर्णांक ग_लिखो_len,
			 अक्षर *पढ़ो_buf, अचिन्हित पूर्णांक पढ़ो_len)
अणु
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = ts->client->addr,
			.flags = 0,
			.buf = ग_लिखो_buf,
			.len = ग_लिखो_len,
		पूर्ण, अणु
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.buf = पढ़ो_buf,
			.len = पढ़ो_len,
		पूर्ण,
	पूर्ण;
	पूर्णांक retry = I2C_RETRY_COUNT;
	पूर्णांक res;
	पूर्णांक error;

	करो अणु
		res = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
		अगर (res == ARRAY_SIZE(msg))
			वापस 0;

		error = res < 0 ? res : -EIO;
		dev_err(&ts->client->dev,
			"%s - i2c_transfer failed: %d (%d)\n",
			__func__, error, res);
	पूर्ण जबतक (--retry);

	वापस error;
पूर्ण

अटल व्योम mip4_parse_fw_version(स्थिर u8 *buf, काष्ठा mip4_fw_version *v)
अणु
	v->boot  = get_unaligned_le16(buf + 0);
	v->core  = get_unaligned_le16(buf + 2);
	v->app   = get_unaligned_le16(buf + 4);
	v->param = get_unaligned_le16(buf + 6);
पूर्ण

/*
 * Read chip firmware version
 */
अटल पूर्णांक mip4_get_fw_version(काष्ठा mip4_ts *ts)
अणु
	u8 cmd[] = अणु MIP4_R0_INFO, MIP4_R1_INFO_VERSION_BOOT पूर्ण;
	u8 buf[माप(ts->fw_version)];
	पूर्णांक error;

	error = mip4_i2c_xfer(ts, cmd, माप(cmd), buf, माप(buf));
	अगर (error) अणु
		स_रखो(&ts->fw_version, 0xff, माप(ts->fw_version));
		वापस error;
	पूर्ण

	mip4_parse_fw_version(buf, &ts->fw_version);

	वापस 0;
पूर्ण

/*
 * Fetch device अक्षरacteristics
 */
अटल पूर्णांक mip4_query_device(काष्ठा mip4_ts *ts)
अणु
	जोड़ i2c_smbus_data dummy;
	पूर्णांक error;
	u8 cmd[2];
	u8 buf[14];

	/*
	 * Make sure there is something at this address as we करो not
	 * consider subsequent failures as fatal.
	 */
	अगर (i2c_smbus_xfer(ts->client->adapter, ts->client->addr,
			   0, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &dummy) < 0) अणु
		dev_err(&ts->client->dev, "nothing at this address\n");
		वापस -ENXIO;
	पूर्ण

	/* Product name */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_PRODUCT_NAME;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd),
			      ts->product_name, माप(ts->product_name));
	अगर (error)
		dev_warn(&ts->client->dev,
			 "Failed to retrieve product name: %d\n", error);
	अन्यथा
		dev_dbg(&ts->client->dev, "product name: %.*s\n",
			(पूर्णांक)माप(ts->product_name), ts->product_name);

	/* Product ID */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_PID;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd), buf, 2);
	अगर (error) अणु
		dev_warn(&ts->client->dev,
			 "Failed to retrieve product id: %d\n", error);
	पूर्ण अन्यथा अणु
		ts->product_id = get_unaligned_le16(&buf[0]);
		dev_dbg(&ts->client->dev, "product id: %04X\n", ts->product_id);
	पूर्ण

	/* Firmware name */
	snम_लिखो(ts->fw_name, माप(ts->fw_name),
		"melfas_mip4_%04X.fw", ts->product_id);
	dev_dbg(&ts->client->dev, "firmware name: %s\n", ts->fw_name);

	/* IC name */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_IC_NAME;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd),
			      ts->ic_name, माप(ts->ic_name));
	अगर (error)
		dev_warn(&ts->client->dev,
			 "Failed to retrieve IC name: %d\n", error);
	अन्यथा
		dev_dbg(&ts->client->dev, "IC name: %.*s\n",
			(पूर्णांक)माप(ts->ic_name), ts->ic_name);

	/* Firmware version */
	error = mip4_get_fw_version(ts);
	अगर (error)
		dev_warn(&ts->client->dev,
			"Failed to retrieve FW version: %d\n", error);
	अन्यथा
		dev_dbg(&ts->client->dev, "F/W Version: %04X %04X %04X %04X\n",
			 ts->fw_version.boot, ts->fw_version.core,
			 ts->fw_version.app, ts->fw_version.param);

	/* Resolution */
	cmd[0] = MIP4_R0_INFO;
	cmd[1] = MIP4_R1_INFO_RESOLUTION_X;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd), buf, 14);
	अगर (error) अणु
		dev_warn(&ts->client->dev,
			 "Failed to retrieve touchscreen parameters: %d\n",
			 error);
	पूर्ण अन्यथा अणु
		ts->max_x = get_unaligned_le16(&buf[0]);
		ts->max_y = get_unaligned_le16(&buf[2]);
		dev_dbg(&ts->client->dev, "max_x: %d, max_y: %d\n",
			ts->max_x, ts->max_y);

		ts->node_x = buf[4];
		ts->node_y = buf[5];
		ts->node_key = buf[6];
		dev_dbg(&ts->client->dev,
			"node_x: %d, node_y: %d, node_key: %d\n",
			ts->node_x, ts->node_y, ts->node_key);

		ts->ppm_x = buf[12];
		ts->ppm_y = buf[13];
		dev_dbg(&ts->client->dev, "ppm_x: %d, ppm_y: %d\n",
			ts->ppm_x, ts->ppm_y);

		/* Key ts */
		अगर (ts->node_key > 0)
			ts->key_num = ts->node_key;
	पूर्ण

	/* Protocol */
	cmd[0] = MIP4_R0_EVENT;
	cmd[1] = MIP4_R1_EVENT_SUPPORTED_FUNC;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd), buf, 7);
	अगर (error) अणु
		dev_warn(&ts->client->dev,
			"Failed to retrieve device type: %d\n", error);
		ts->event_क्रमmat = 0xff;
	पूर्ण अन्यथा अणु
		ts->event_क्रमmat = get_unaligned_le16(&buf[4]);
		ts->event_size = buf[6];
		dev_dbg(&ts->client->dev, "event_format: %d, event_size: %d\n",
			ts->event_क्रमmat, ts->event_size);

		अगर (ts->event_क्रमmat == 2 || ts->event_क्रमmat > 3)
			dev_warn(&ts->client->dev,
				 "Unknown event format %d\n", ts->event_क्रमmat);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mip4_घातer_on(काष्ठा mip4_ts *ts)
अणु
	अगर (ts->gpio_ce) अणु
		gpiod_set_value_cansleep(ts->gpio_ce, 1);

		/* Booting delay : 200~300ms */
		usleep_range(200 * 1000, 300 * 1000);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mip4_घातer_off(काष्ठा mip4_ts *ts)
अणु
	अगर (ts->gpio_ce)
		gpiod_set_value_cansleep(ts->gpio_ce, 0);
पूर्ण

/*
 * Clear touch input event status
 */
अटल व्योम mip4_clear_input(काष्ठा mip4_ts *ts)
अणु
	पूर्णांक i;

	/* Screen */
	क्रम (i = 0; i < MIP4_MAX_FINGERS; i++) अणु
		input_mt_slot(ts->input, i);
		input_mt_report_slot_inactive(ts->input);
	पूर्ण

	/* Keys */
	क्रम (i = 0; i < ts->key_num; i++)
		input_report_key(ts->input, ts->key_code[i], 0);

	input_sync(ts->input);
पूर्ण

अटल पूर्णांक mip4_enable(काष्ठा mip4_ts *ts)
अणु
	पूर्णांक error;

	error = mip4_घातer_on(ts);
	अगर (error)
		वापस error;

	enable_irq(ts->client->irq);

	वापस 0;
पूर्ण

अटल व्योम mip4_disable(काष्ठा mip4_ts *ts)
अणु
	disable_irq(ts->client->irq);

	mip4_घातer_off(ts);

	mip4_clear_input(ts);
पूर्ण

/*****************************************************************
 * Input handling
 *****************************************************************/

अटल व्योम mip4_report_keys(काष्ठा mip4_ts *ts, u8 *packet)
अणु
	u8 key;
	bool करोwn;

	चयन (ts->event_क्रमmat) अणु
	हाल 0:
	हाल 1:
		key = packet[0] & 0x0F;
		करोwn = packet[0] & 0x80;
		अवरोध;

	हाल 3:
	शेष:
		key = packet[0] & 0x0F;
		करोwn = packet[1] & 0x01;
		अवरोध;
	पूर्ण

	/* Report key event */
	अगर (key >= 1 && key <= ts->key_num) अणु
		अचिन्हित लघु keycode = ts->key_code[key - 1];

		dev_dbg(&ts->client->dev,
			"Key - ID: %d, keycode: %d, state: %d\n",
			key, keycode, करोwn);

		input_event(ts->input, EV_MSC, MSC_SCAN, keycode);
		input_report_key(ts->input, keycode, करोwn);

	पूर्ण अन्यथा अणु
		dev_err(&ts->client->dev, "Unknown key: %d\n", key);
	पूर्ण
पूर्ण

अटल व्योम mip4_report_touch(काष्ठा mip4_ts *ts, u8 *packet)
अणु
	पूर्णांक id;
	bool __always_unused hover;
	bool __always_unused palm;
	bool state;
	u16 x, y;
	u8 __always_unused pressure_stage = 0;
	u8 pressure;
	u8 __always_unused size;
	u8 touch_major;
	u8 touch_minor;

	चयन (ts->event_क्रमmat) अणु
	हाल 0:
	हाल 1:
		/* Touch only */
		state = packet[0] & BIT(7);
		hover = packet[0] & BIT(5);
		palm = packet[0] & BIT(4);
		id = (packet[0] & 0x0F) - 1;
		x = ((packet[1] & 0x0F) << 8) | packet[2];
		y = (((packet[1] >> 4) & 0x0F) << 8) |
			packet[3];
		pressure = packet[4];
		size = packet[5];
		अगर (ts->event_क्रमmat == 0) अणु
			touch_major = packet[5];
			touch_minor = packet[5];
		पूर्ण अन्यथा अणु
			touch_major = packet[6];
			touch_minor = packet[7];
		पूर्ण
		अवरोध;

	हाल 3:
	शेष:
		/* Touch + Force(Pressure) */
		id = (packet[0] & 0x0F) - 1;
		hover = packet[1] & BIT(2);
		palm = packet[1] & BIT(1);
		state = packet[1] & BIT(0);
		x = ((packet[2] & 0x0F) << 8) | packet[3];
		y = (((packet[2] >> 4) & 0x0F) << 8) |
			packet[4];
		size = packet[6];
		pressure_stage = (packet[7] & 0xF0) >> 4;
		pressure = ((packet[7] & 0x0F) << 8) |
			packet[8];
		touch_major = packet[9];
		touch_minor = packet[10];
		अवरोध;
	पूर्ण

	dev_dbg(&ts->client->dev,
		"Screen - Slot: %d State: %d X: %04d Y: %04d Z: %d\n",
		id, state, x, y, pressure);

	अगर (unlikely(id < 0 || id >= MIP4_MAX_FINGERS)) अणु
		dev_err(&ts->client->dev, "Screen - invalid slot ID: %d\n", id);
	पूर्ण अन्यथा अगर (state) अणु
		/* Press or Move event */
		input_mt_slot(ts->input, id);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, true);
		input_report_असल(ts->input, ABS_MT_POSITION_X, x);
		input_report_असल(ts->input, ABS_MT_POSITION_Y, y);
		input_report_असल(ts->input, ABS_MT_PRESSURE, pressure);
		input_report_असल(ts->input, ABS_MT_TOUCH_MAJOR, touch_major);
		input_report_असल(ts->input, ABS_MT_TOUCH_MINOR, touch_minor);
	पूर्ण अन्यथा अणु
		/* Release event */
		input_mt_slot(ts->input, id);
		input_mt_report_slot_inactive(ts->input);
	पूर्ण

	input_mt_sync_frame(ts->input);
पूर्ण

अटल पूर्णांक mip4_handle_packet(काष्ठा mip4_ts *ts, u8 *packet)
अणु
	u8 type;

	चयन (ts->event_क्रमmat) अणु
	हाल 0:
	हाल 1:
		type = (packet[0] & 0x40) >> 6;
		अवरोध;

	हाल 3:
		type = (packet[0] & 0xF0) >> 4;
		अवरोध;

	शेष:
		/* Should not happen unless we have corrupted firmware */
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&ts->client->dev, "Type: %d\n", type);

	/* Report input event */
	चयन (type) अणु
	हाल MIP4_EVENT_INPUT_TYPE_KEY:
		mip4_report_keys(ts, packet);
		अवरोध;

	हाल MIP4_EVENT_INPUT_TYPE_SCREEN:
		mip4_report_touch(ts, packet);
		अवरोध;

	शेष:
		dev_err(&ts->client->dev, "Unknown event type: %d\n", type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t mip4_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mip4_ts *ts = dev_id;
	काष्ठा i2c_client *client = ts->client;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;
	u8 cmd[2];
	u8 size;
	bool alert;

	/* Read packet info */
	cmd[0] = MIP4_R0_EVENT;
	cmd[1] = MIP4_R1_EVENT_PACKET_INFO;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd), ts->buf, 1);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to read packet info: %d\n", error);
		जाओ out;
	पूर्ण

	size = ts->buf[0] & 0x7F;
	alert = ts->buf[0] & BIT(7);
	dev_dbg(&client->dev, "packet size: %d, alert: %d\n", size, alert);

	/* Check size */
	अगर (!size) अणु
		dev_err(&client->dev, "Empty packet\n");
		जाओ out;
	पूर्ण

	/* Read packet data */
	cmd[0] = MIP4_R0_EVENT;
	cmd[1] = MIP4_R1_EVENT_PACKET_DATA;
	error = mip4_i2c_xfer(ts, cmd, माप(cmd), ts->buf, size);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to read packet data: %d\n", error);
		जाओ out;
	पूर्ण

	अगर (alert) अणु
		dev_dbg(&client->dev, "Alert: %d\n", ts->buf[0]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < size; i += ts->event_size) अणु
			error = mip4_handle_packet(ts, &ts->buf[i]);
			अगर (error)
				अवरोध;
		पूर्ण

		input_sync(ts->input);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mip4_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा mip4_ts *ts = input_get_drvdata(dev);

	वापस mip4_enable(ts);
पूर्ण

अटल व्योम mip4_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा mip4_ts *ts = input_get_drvdata(dev);

	mip4_disable(ts);
पूर्ण

/*****************************************************************
 * Firmware update
 *****************************************************************/

/* Firmware Info */
#घोषणा MIP4_BL_PAGE_SIZE		512	/* 512 */
#घोषणा MIP4_BL_PACKET_SIZE		512	/* 512, 256, 128, 64, ... */

/*
 * Firmware binary tail info
 */

काष्ठा mip4_bin_tail अणु
	u8 tail_mark[4];
	u8 chip_name[4];

	__le32 bin_start_addr;
	__le32 bin_length;

	__le16 ver_boot;
	__le16 ver_core;
	__le16 ver_app;
	__le16 ver_param;

	u8 boot_start;
	u8 boot_end;
	u8 core_start;
	u8 core_end;
	u8 app_start;
	u8 app_end;
	u8 param_start;
	u8 param_end;

	u8 checksum_type;
	u8 hw_category;

	__le16 param_id;
	__le32 param_length;
	__le32 build_date;
	__le32 build_समय;

	__le32 reserved1;
	__le32 reserved2;
	__le16 reserved3;
	__le16 tail_size;
	__le32 crc;
पूर्ण __packed;

#घोषणा MIP4_BIN_TAIL_MARK	"MBT\001"
#घोषणा MIP4_BIN_TAIL_SIZE	(माप(काष्ठा mip4_bin_tail))

/*
* Bootloader - Read status
*/
अटल पूर्णांक mip4_bl_पढ़ो_status(काष्ठा mip4_ts *ts)
अणु
	u8 cmd[] = अणु MIP4_R0_BOOT, MIP4_R1_BOOT_STATUS पूर्ण;
	u8 result;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = ts->client->addr,
			.flags = 0,
			.buf = cmd,
			.len = माप(cmd),
		पूर्ण, अणु
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.buf = &result,
			.len = माप(result),
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक error;
	पूर्णांक retry = 1000;

	करो अणु
		ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
		अगर (ret != ARRAY_SIZE(msg)) अणु
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to read bootloader status: %d\n",
				error);
			वापस error;
		पूर्ण

		चयन (result) अणु
		हाल MIP4_BOOT_STATUS_DONE:
			dev_dbg(&ts->client->dev, "%s - done\n", __func__);
			वापस 0;

		हाल MIP4_BOOT_STATUS_ERROR:
			dev_err(&ts->client->dev, "Bootloader failure\n");
			वापस -EIO;

		हाल MIP4_BOOT_STATUS_BUSY:
			dev_dbg(&ts->client->dev, "%s - Busy\n", __func__);
			error = -EBUSY;
			अवरोध;

		शेष:
			dev_err(&ts->client->dev,
				"Unexpected bootloader status: %#02x\n",
				result);
			error = -EINVAL;
			अवरोध;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण जबतक (--retry);

	वापस error;
पूर्ण

/*
* Bootloader - Change mode
*/
अटल पूर्णांक mip4_bl_change_mode(काष्ठा mip4_ts *ts, u8 mode)
अणु
	u8 mode_chg_cmd[] = अणु MIP4_R0_BOOT, MIP4_R1_BOOT_MODE, mode पूर्ण;
	u8 mode_पढ़ो_cmd[] = अणु MIP4_R0_BOOT, MIP4_R1_BOOT_MODE पूर्ण;
	u8 result;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = ts->client->addr,
			.flags = 0,
			.buf = mode_पढ़ो_cmd,
			.len = माप(mode_पढ़ो_cmd),
		पूर्ण, अणु
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.buf = &result,
			.len = माप(result),
		पूर्ण,
	पूर्ण;
	पूर्णांक retry = 10;
	पूर्णांक ret;
	पूर्णांक error;

	करो अणु
		/* Send mode change command */
		ret = i2c_master_send(ts->client,
				      mode_chg_cmd, माप(mode_chg_cmd));
		अगर (ret != माप(mode_chg_cmd)) अणु
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to send %d mode change: %d (%d)\n",
				mode, error, ret);
			वापस error;
		पूर्ण

		dev_dbg(&ts->client->dev,
			"Sent mode change request (mode: %d)\n", mode);

		/* Wait */
		msleep(1000);

		/* Verअगरy target mode */
		ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
		अगर (ret != ARRAY_SIZE(msg)) अणु
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to read device mode: %d\n", error);
			वापस error;
		पूर्ण

		dev_dbg(&ts->client->dev,
			"Current device mode: %d, want: %d\n", result, mode);

		अगर (result == mode)
			वापस 0;

	पूर्ण जबतक (--retry);

	वापस -EIO;
पूर्ण

/*
 * Bootloader - Start bootloader mode
 */
अटल पूर्णांक mip4_bl_enter(काष्ठा mip4_ts *ts)
अणु
	वापस mip4_bl_change_mode(ts, MIP4_BOOT_MODE_BOOT);
पूर्ण

/*
 * Bootloader - Exit bootloader mode
 */
अटल पूर्णांक mip4_bl_निकास(काष्ठा mip4_ts *ts)
अणु
	वापस mip4_bl_change_mode(ts, MIP4_BOOT_MODE_APP);
पूर्ण

अटल पूर्णांक mip4_bl_get_address(काष्ठा mip4_ts *ts, u16 *buf_addr)
अणु
	u8 cmd[] = अणु MIP4_R0_BOOT, MIP4_R1_BOOT_BUF_ADDR पूर्ण;
	u8 result[माप(u16)];
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = ts->client->addr,
			.flags = 0,
			.buf = cmd,
			.len = माप(cmd),
		पूर्ण, अणु
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.buf = result,
			.len = माप(result),
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक error;

	ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret != ARRAY_SIZE(msg)) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to retrieve bootloader buffer address: %d\n",
			error);
		वापस error;
	पूर्ण

	*buf_addr = get_unaligned_le16(result);
	dev_dbg(&ts->client->dev,
		"Bootloader buffer address %#04x\n", *buf_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक mip4_bl_program_page(काष्ठा mip4_ts *ts, पूर्णांक offset,
				स्थिर u8 *data, पूर्णांक length, u16 buf_addr)
अणु
	u8 cmd[6];
	u8 *data_buf;
	u16 buf_offset;
	पूर्णांक ret;
	पूर्णांक error;

	dev_dbg(&ts->client->dev, "Writing page @%#06x (%d)\n",
		offset, length);

	अगर (length > MIP4_BL_PAGE_SIZE || length % MIP4_BL_PACKET_SIZE) अणु
		dev_err(&ts->client->dev,
			"Invalid page length: %d\n", length);
		वापस -EINVAL;
	पूर्ण

	data_buf = kदो_स्मृति(2 + MIP4_BL_PACKET_SIZE, GFP_KERNEL);
	अगर (!data_buf)
		वापस -ENOMEM;

	/* Addr */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_TARGET_ADDR;
	put_unaligned_le32(offset, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	अगर (ret != 6) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send write page address: %d\n", error);
		जाओ out;
	पूर्ण

	/* Size */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_SIZE;
	put_unaligned_le32(length, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	अगर (ret != 6) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send write page size: %d\n", error);
		जाओ out;
	पूर्ण

	/* Data */
	क्रम (buf_offset = 0;
	     buf_offset < length;
	     buf_offset += MIP4_BL_PACKET_SIZE) अणु
		dev_dbg(&ts->client->dev,
			"writing chunk at %#04x (size %d)\n",
			buf_offset, MIP4_BL_PACKET_SIZE);
		put_unaligned_be16(buf_addr + buf_offset, data_buf);
		स_नकल(&data_buf[2], &data[buf_offset], MIP4_BL_PACKET_SIZE);
		ret = i2c_master_send(ts->client,
				      data_buf, 2 + MIP4_BL_PACKET_SIZE);
		अगर (ret != 2 + MIP4_BL_PACKET_SIZE) अणु
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to read chunk at %#04x (size %d): %d\n",
				buf_offset, MIP4_BL_PACKET_SIZE, error);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Command */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_CMD;
	cmd[2] = MIP4_BOOT_CMD_PROGRAM;
	ret = i2c_master_send(ts->client, cmd, 3);
	अगर (ret != 3) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send 'write' command: %d\n", error);
		जाओ out;
	पूर्ण

	/* Status */
	error = mip4_bl_पढ़ो_status(ts);

out:
	kमुक्त(data_buf);
	वापस error ? error : 0;
पूर्ण

अटल पूर्णांक mip4_bl_verअगरy_page(काष्ठा mip4_ts *ts, पूर्णांक offset,
			       स्थिर u8 *data, पूर्णांक length, पूर्णांक buf_addr)
अणु
	u8 cmd[8];
	u8 *पढ़ो_buf;
	पूर्णांक buf_offset;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = ts->client->addr,
			.flags = 0,
			.buf = cmd,
			.len = 2,
		पूर्ण, अणु
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.len = MIP4_BL_PACKET_SIZE,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक error;

	dev_dbg(&ts->client->dev, "Validating page @%#06x (%d)\n",
		offset, length);

	/* Addr */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_TARGET_ADDR;
	put_unaligned_le32(offset, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	अगर (ret != 6) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send read page address: %d\n", error);
		वापस error;
	पूर्ण

	/* Size */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_SIZE;
	put_unaligned_le32(length, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	अगर (ret != 6) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send read page size: %d\n", error);
		वापस error;
	पूर्ण

	/* Command */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_CMD;
	cmd[2] = MIP4_BOOT_CMD_READ;
	ret = i2c_master_send(ts->client, cmd, 3);
	अगर (ret != 3) अणु
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send 'read' command: %d\n", error);
		वापस error;
	पूर्ण

	/* Status */
	error = mip4_bl_पढ़ो_status(ts);
	अगर (error)
		वापस error;

	/* Read */
	msg[1].buf = पढ़ो_buf = kदो_स्मृति(MIP4_BL_PACKET_SIZE, GFP_KERNEL);
	अगर (!पढ़ो_buf)
		वापस -ENOMEM;

	क्रम (buf_offset = 0;
	     buf_offset < length;
	     buf_offset += MIP4_BL_PACKET_SIZE) अणु
		dev_dbg(&ts->client->dev,
			"reading chunk at %#04x (size %d)\n",
			buf_offset, MIP4_BL_PACKET_SIZE);
		put_unaligned_be16(buf_addr + buf_offset, cmd);
		ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
		अगर (ret != ARRAY_SIZE(msg)) अणु
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to read chunk at %#04x (size %d): %d\n",
				buf_offset, MIP4_BL_PACKET_SIZE, error);
			अवरोध;
		पूर्ण

		अगर (स_भेद(&data[buf_offset], पढ़ो_buf, MIP4_BL_PACKET_SIZE)) अणु
			dev_err(&ts->client->dev,
				"Failed to validate chunk at %#04x (size %d)\n",
				buf_offset, MIP4_BL_PACKET_SIZE);
#अगर MIP4_FW_UPDATE_DEBUG
			prपूर्णांक_hex_dump(KERN_DEBUG,
				       MIP4_DEVICE_NAME " F/W File: ",
				       DUMP_PREFIX_OFFSET, 16, 1,
				       data + offset, MIP4_BL_PACKET_SIZE,
				       false);
			prपूर्णांक_hex_dump(KERN_DEBUG,
				       MIP4_DEVICE_NAME " F/W Chip: ",
				       DUMP_PREFIX_OFFSET, 16, 1,
				       पढ़ो_buf, MIP4_BL_PAGE_SIZE, false);
#पूर्ण_अगर
			error = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(पढ़ो_buf);
	वापस error ? error : 0;
पूर्ण

/*
 * Flash chip firmware
 */
अटल पूर्णांक mip4_flash_fw(काष्ठा mip4_ts *ts,
			 स्थिर u8 *fw_data, u32 fw_size, u32 fw_offset)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक offset;
	u16 buf_addr;
	पूर्णांक error, error2;

	/* Enter bootloader mode */
	dev_dbg(&client->dev, "Entering bootloader mode\n");

	error = mip4_bl_enter(ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to enter bootloader mode: %d\n",
			error);
		वापस error;
	पूर्ण

	/* Read info */
	error = mip4_bl_get_address(ts, &buf_addr);
	अगर (error)
		जाओ निकास_bl;

	/* Program & Verअगरy */
	dev_dbg(&client->dev,
		"Program & Verify, page size: %d, packet size: %d\n",
		MIP4_BL_PAGE_SIZE, MIP4_BL_PACKET_SIZE);

	क्रम (offset = fw_offset;
	     offset < fw_offset + fw_size;
	     offset += MIP4_BL_PAGE_SIZE) अणु
		/* Program */
		error = mip4_bl_program_page(ts, offset, fw_data + offset,
					     MIP4_BL_PAGE_SIZE, buf_addr);
		अगर (error)
			अवरोध;

		/* Verअगरy */
		error = mip4_bl_verअगरy_page(ts, offset, fw_data + offset,
					    MIP4_BL_PAGE_SIZE, buf_addr);
		अगर (error)
			अवरोध;
	पूर्ण

निकास_bl:
	/* Exit bootloader mode */
	dev_dbg(&client->dev, "Exiting bootloader mode\n");

	error2 = mip4_bl_निकास(ts);
	अगर (error2) अणु
		dev_err(&client->dev,
			"Failed to exit bootloader mode: %d\n", error2);
		अगर (!error)
			error = error2;
	पूर्ण

	/* Reset chip */
	mip4_घातer_off(ts);
	mip4_घातer_on(ts);

	mip4_query_device(ts);

	/* Refresh device parameters */
	input_set_असल_params(ts->input, ABS_MT_POSITION_X, 0, ts->max_x, 0, 0);
	input_set_असल_params(ts->input, ABS_MT_POSITION_Y, 0, ts->max_y, 0, 0);
	input_set_असल_params(ts->input, ABS_X, 0, ts->max_x, 0, 0);
	input_set_असल_params(ts->input, ABS_Y, 0, ts->max_y, 0, 0);
	input_असल_set_res(ts->input, ABS_MT_POSITION_X, ts->ppm_x);
	input_असल_set_res(ts->input, ABS_MT_POSITION_Y, ts->ppm_y);
	input_असल_set_res(ts->input, ABS_X, ts->ppm_x);
	input_असल_set_res(ts->input, ABS_Y, ts->ppm_y);

	वापस error ? error : 0;
पूर्ण

अटल पूर्णांक mip4_parse_firmware(काष्ठा mip4_ts *ts, स्थिर काष्ठा firmware *fw,
			       u32 *fw_offset_start, u32 *fw_size,
			       स्थिर काष्ठा mip4_bin_tail **pfw_info)
अणु
	स्थिर काष्ठा mip4_bin_tail *fw_info;
	काष्ठा mip4_fw_version fw_version;
	u16 tail_size;

	अगर (fw->size < MIP4_BIN_TAIL_SIZE) अणु
		dev_err(&ts->client->dev,
			"Invalid firmware, size mismatch (tail %zd vs %zd)\n",
			MIP4_BIN_TAIL_SIZE, fw->size);
		वापस -EINVAL;
	पूर्ण

	fw_info = (स्थिर व्योम *)&fw->data[fw->size - MIP4_BIN_TAIL_SIZE];

#अगर MIP4_FW_UPDATE_DEBUG
	prपूर्णांक_hex_dump(KERN_ERR, MIP4_DEVICE_NAME " Bin Info: ",
		       DUMP_PREFIX_OFFSET, 16, 1, *fw_info, tail_size, false);
#पूर्ण_अगर

	tail_size = get_unaligned_le16(&fw_info->tail_size);
	अगर (tail_size != MIP4_BIN_TAIL_SIZE) अणु
		dev_err(&ts->client->dev,
			"wrong tail size: %d (expected %zd)\n",
			tail_size, MIP4_BIN_TAIL_SIZE);
		वापस -EINVAL;
	पूर्ण

	/* Check bin क्रमmat */
	अगर (स_भेद(fw_info->tail_mark, MIP4_BIN_TAIL_MARK,
		   माप(fw_info->tail_mark))) अणु
		dev_err(&ts->client->dev,
			"unable to locate tail marker (%*ph vs %*ph)\n",
			(पूर्णांक)माप(fw_info->tail_mark), fw_info->tail_mark,
			(पूर्णांक)माप(fw_info->tail_mark), MIP4_BIN_TAIL_MARK);
		वापस -EINVAL;
	पूर्ण

	*fw_offset_start = get_unaligned_le32(&fw_info->bin_start_addr);
	*fw_size = get_unaligned_le32(&fw_info->bin_length);

	dev_dbg(&ts->client->dev,
		"F/W Data offset: %#08x, size: %d\n",
		*fw_offset_start, *fw_size);

	अगर (*fw_size % MIP4_BL_PAGE_SIZE) अणु
		dev_err(&ts->client->dev,
			"encoded fw length %d is not multiple of pages (%d)\n",
			*fw_size, MIP4_BL_PAGE_SIZE);
		वापस -EINVAL;
	पूर्ण

	अगर (fw->size != *fw_offset_start + *fw_size) अणु
		dev_err(&ts->client->dev,
			"Wrong firmware size, expected %d bytes, got %zd\n",
			*fw_offset_start + *fw_size, fw->size);
		वापस -EINVAL;
	पूर्ण

	mip4_parse_fw_version((स्थिर u8 *)&fw_info->ver_boot, &fw_version);

	dev_dbg(&ts->client->dev,
		"F/W file version %04X %04X %04X %04X\n",
		fw_version.boot, fw_version.core,
		fw_version.app, fw_version.param);

	dev_dbg(&ts->client->dev, "F/W chip version: %04X %04X %04X %04X\n",
		 ts->fw_version.boot, ts->fw_version.core,
		 ts->fw_version.app, ts->fw_version.param);

	/* Check F/W type */
	अगर (fw_version.boot != 0xEEEE && fw_version.boot != 0xFFFF &&
	    fw_version.core == 0xEEEE &&
	    fw_version.app == 0xEEEE &&
	    fw_version.param == 0xEEEE) अणु
		dev_dbg(&ts->client->dev, "F/W type: Bootloader\n");
	पूर्ण अन्यथा अगर (fw_version.boot == 0xEEEE &&
		   fw_version.core != 0xEEEE && fw_version.core != 0xFFFF &&
		   fw_version.app != 0xEEEE && fw_version.app != 0xFFFF &&
		   fw_version.param != 0xEEEE && fw_version.param != 0xFFFF) अणु
		dev_dbg(&ts->client->dev, "F/W type: Main\n");
	पूर्ण अन्यथा अणु
		dev_err(&ts->client->dev, "Wrong firmware type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mip4_execute_fw_update(काष्ठा mip4_ts *ts, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा mip4_bin_tail *fw_info;
	u32 fw_start_offset;
	u32 fw_size;
	पूर्णांक retires = 3;
	पूर्णांक error;

	error = mip4_parse_firmware(ts, fw,
				    &fw_start_offset, &fw_size, &fw_info);
	अगर (error)
		वापस error;

	अगर (input_device_enabled(ts->input)) अणु
		disable_irq(ts->client->irq);
	पूर्ण अन्यथा अणु
		error = mip4_घातer_on(ts);
		अगर (error)
			वापस error;
	पूर्ण

	/* Update firmware */
	करो अणु
		error = mip4_flash_fw(ts, fw->data, fw_size, fw_start_offset);
		अगर (!error)
			अवरोध;
	पूर्ण जबतक (--retires);

	अगर (error)
		dev_err(&ts->client->dev,
			"Failed to flash firmware: %d\n", error);

	/* Enable IRQ */
	अगर (input_device_enabled(ts->input))
		enable_irq(ts->client->irq);
	अन्यथा
		mip4_घातer_off(ts);

	वापस error ? error : 0;
पूर्ण

अटल sमाप_प्रकार mip4_sysfs_fw_update(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	स्थिर काष्ठा firmware *fw;
	पूर्णांक error;

	error = request_firmware(&fw, ts->fw_name, dev);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"Failed to retrieve firmware %s: %d\n",
			ts->fw_name, error);
		वापस error;
	पूर्ण

	/*
	 * Take input mutex to prevent racing with itself and also with
	 * userspace खोलोing and closing the device and also suspend/resume
	 * transitions.
	 */
	mutex_lock(&ts->input->mutex);

	error = mip4_execute_fw_update(ts, fw);

	mutex_unlock(&ts->input->mutex);

	release_firmware(fw);

	अगर (error) अणु
		dev_err(&ts->client->dev,
			"Firmware update failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(update_fw, S_IWUSR, शून्य, mip4_sysfs_fw_update);

अटल sमाप_प्रकार mip4_sysfs_पढ़ो_fw_version(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	माप_प्रकार count;

	/* Take lock to prevent racing with firmware update */
	mutex_lock(&ts->input->mutex);

	count = snम_लिखो(buf, PAGE_SIZE, "%04X %04X %04X %04X\n",
			 ts->fw_version.boot, ts->fw_version.core,
			 ts->fw_version.app, ts->fw_version.param);

	mutex_unlock(&ts->input->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(fw_version, S_IRUGO, mip4_sysfs_पढ़ो_fw_version, शून्य);

अटल sमाप_प्रकार mip4_sysfs_पढ़ो_hw_version(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	माप_प्रकार count;

	/* Take lock to prevent racing with firmware update */
	mutex_lock(&ts->input->mutex);

	/*
	 * product_name shows the name or version of the hardware
	 * paired with current firmware in the chip.
	 */
	count = snम_लिखो(buf, PAGE_SIZE, "%.*s\n",
			 (पूर्णांक)माप(ts->product_name), ts->product_name);

	mutex_unlock(&ts->input->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(hw_version, S_IRUGO, mip4_sysfs_पढ़ो_hw_version, शून्य);

अटल sमाप_प्रकार mip4_sysfs_पढ़ो_product_id(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	माप_प्रकार count;

	mutex_lock(&ts->input->mutex);

	count = snम_लिखो(buf, PAGE_SIZE, "%04X\n", ts->product_id);

	mutex_unlock(&ts->input->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(product_id, S_IRUGO, mip4_sysfs_पढ़ो_product_id, शून्य);

अटल sमाप_प्रकार mip4_sysfs_पढ़ो_ic_name(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	माप_प्रकार count;

	mutex_lock(&ts->input->mutex);

	count = snम_लिखो(buf, PAGE_SIZE, "%.*s\n",
			 (पूर्णांक)माप(ts->ic_name), ts->ic_name);

	mutex_unlock(&ts->input->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(ic_name, S_IRUGO, mip4_sysfs_पढ़ो_ic_name, शून्य);

अटल काष्ठा attribute *mip4_attrs[] = अणु
	&dev_attr_fw_version.attr,
	&dev_attr_hw_version.attr,
	&dev_attr_product_id.attr,
	&dev_attr_ic_name.attr,
	&dev_attr_update_fw.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mip4_attr_group = अणु
	.attrs = mip4_attrs,
पूर्ण;

अटल पूर्णांक mip4_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mip4_ts *ts;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "Not supported I2C adapter\n");
		वापस -ENXIO;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&client->dev);
	अगर (!input)
		वापस -ENOMEM;

	ts->client = client;
	ts->input = input;

	snम_लिखो(ts->phys, माप(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	ts->gpio_ce = devm_gpiod_get_optional(&client->dev,
					      "ce", GPIOD_OUT_LOW);
	अगर (IS_ERR(ts->gpio_ce)) अणु
		error = PTR_ERR(ts->gpio_ce);
		अगर (error != EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get gpio: %d\n", error);
		वापस error;
	पूर्ण

	error = mip4_घातer_on(ts);
	अगर (error)
		वापस error;
	error = mip4_query_device(ts);
	mip4_घातer_off(ts);
	अगर (error)
		वापस error;

	input->name = "MELFAS MIP4 Touchscreen";
	input->phys = ts->phys;

	input->id.bustype = BUS_I2C;
	input->id.venकरोr = 0x13c5;
	input->id.product = ts->product_id;

	input->खोलो = mip4_input_खोलो;
	input->बंद = mip4_input_बंद;

	input_set_drvdata(input, ts);

	input->keycode = ts->key_code;
	input->keycodesize = माप(*ts->key_code);
	input->keycodemax = ts->key_num;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, ts->max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, ts->max_y, 0, 0);
	input_set_असल_params(input, ABS_MT_PRESSURE,
			     MIP4_PRESSURE_MIN, MIP4_PRESSURE_MAX, 0, 0);
	input_set_असल_params(input, ABS_MT_TOUCH_MAJOR,
			     MIP4_TOUCH_MAJOR_MIN, MIP4_TOUCH_MAJOR_MAX, 0, 0);
	input_set_असल_params(input, ABS_MT_TOUCH_MINOR,
			     MIP4_TOUCH_MINOR_MIN, MIP4_TOUCH_MINOR_MAX, 0, 0);
	input_असल_set_res(ts->input, ABS_MT_POSITION_X, ts->ppm_x);
	input_असल_set_res(ts->input, ABS_MT_POSITION_Y, ts->ppm_y);

	error = input_mt_init_slots(input, MIP4_MAX_FINGERS, INPUT_MT_सूचीECT);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, ts);

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, mip4_पूर्णांकerrupt,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  MIP4_DEVICE_NAME, ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to request interrupt %d: %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(&client->dev, &mip4_attr_group);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to create sysfs attribute group: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mip4_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;

	mutex_lock(&input->mutex);

	अगर (device_may_wakeup(dev))
		ts->wake_irq_enabled = enable_irq_wake(client->irq) == 0;
	अन्यथा अगर (input_device_enabled(input))
		mip4_disable(ts);

	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mip4_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mip4_ts *ts = i2c_get_clientdata(client);
	काष्ठा input_dev *input = ts->input;

	mutex_lock(&input->mutex);

	अगर (ts->wake_irq_enabled)
		disable_irq_wake(client->irq);
	अन्यथा अगर (input_device_enabled(input))
		mip4_enable(ts);

	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mip4_pm_ops, mip4_suspend, mip4_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mip4_of_match[] = अणु
	अणु .compatible = "melfas,"MIP4_DEVICE_NAME, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mip4_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id mip4_acpi_match[] = अणु
	अणु "MLFS0000", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mip4_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id mip4_i2c_ids[] = अणु
	अणु MIP4_DEVICE_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mip4_i2c_ids);

अटल काष्ठा i2c_driver mip4_driver = अणु
	.id_table = mip4_i2c_ids,
	.probe = mip4_probe,
	.driver = अणु
		.name = MIP4_DEVICE_NAME,
		.of_match_table = of_match_ptr(mip4_of_match),
		.acpi_match_table = ACPI_PTR(mip4_acpi_match),
		.pm = &mip4_pm_ops,
	पूर्ण,
पूर्ण;
module_i2c_driver(mip4_driver);

MODULE_DESCRIPTION("MELFAS MIP4 Touchscreen");
MODULE_AUTHOR("Sangwon Jee <jeesw@melfas.com>");
MODULE_LICENSE("GPL");
