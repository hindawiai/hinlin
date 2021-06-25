<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ILITEK Touch IC driver क्रम 23XX, 25XX and Lego series
 *
 * Copyright (C) 2011 ILI Technology Corporation.
 * Copyright (C) 2020 Luca Hsu <luca_hsu@ilitek.com>
 * Copyright (C) 2021 Joe Hung <joe_hung@ilitek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/acpi.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <यंत्र/unaligned.h>


#घोषणा ILITEK_TS_NAME					"ilitek_ts"
#घोषणा BL_V1_8						0x108
#घोषणा BL_V1_7						0x107
#घोषणा BL_V1_6						0x106

#घोषणा ILITEK_TP_CMD_GET_TP_RES			0x20
#घोषणा ILITEK_TP_CMD_GET_SCRN_RES			0x21
#घोषणा ILITEK_TP_CMD_SET_IC_SLEEP			0x30
#घोषणा ILITEK_TP_CMD_SET_IC_WAKE			0x31
#घोषणा ILITEK_TP_CMD_GET_FW_VER			0x40
#घोषणा ILITEK_TP_CMD_GET_PRL_VER			0x42
#घोषणा ILITEK_TP_CMD_GET_MCU_VER			0x61
#घोषणा ILITEK_TP_CMD_GET_IC_MODE			0xC0

#घोषणा REPORT_COUNT_ADDRESS				61
#घोषणा ILITEK_SUPPORT_MAX_POINT			40

काष्ठा ilitek_protocol_info अणु
	u16 ver;
	u8 ver_major;
पूर्ण;

काष्ठा ilitek_ts_data अणु
	काष्ठा i2c_client		*client;
	काष्ठा gpio_desc		*reset_gpio;
	काष्ठा input_dev		*input_dev;
	काष्ठा touchscreen_properties	prop;

	स्थिर काष्ठा ilitek_protocol_map *ptl_cb_func;
	काष्ठा ilitek_protocol_info	ptl;

	अक्षर				product_id[30];
	u16				mcu_ver;
	u8				ic_mode;
	u8				firmware_ver[8];

	s32				reset_समय;
	s32				screen_max_x;
	s32				screen_max_y;
	s32				screen_min_x;
	s32				screen_min_y;
	s32				max_tp;
पूर्ण;

काष्ठा ilitek_protocol_map अणु
	u16 cmd;
	स्थिर अक्षर *name;
	पूर्णांक (*func)(काष्ठा ilitek_ts_data *ts, u16 cmd, u8 *inbuf, u8 *outbuf);
पूर्ण;

क्रमागत ilitek_cmds अणु
	/* common cmds */
	GET_PTL_VER = 0,
	GET_FW_VER,
	GET_SCRN_RES,
	GET_TP_RES,
	GET_IC_MODE,
	GET_MCU_VER,
	SET_IC_SLEEP,
	SET_IC_WAKE,

	/* ALWAYS keep at the end */
	MAX_CMD_CNT
पूर्ण;

/* ILITEK I2C R/W APIs */
अटल पूर्णांक ilitek_i2c_ग_लिखो_and_पढ़ो(काष्ठा ilitek_ts_data *ts,
				     u8 *cmd, पूर्णांक ग_लिखो_len, पूर्णांक delay,
				     u8 *data, पूर्णांक पढ़ो_len)
अणु
	पूर्णांक error;
	काष्ठा i2c_client *client = ts->client;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = ग_लिखो_len,
			.buf = cmd,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = पढ़ो_len,
			.buf = data,
		पूर्ण,
	पूर्ण;

	अगर (delay == 0 && ग_लिखो_len > 0 && पढ़ो_len > 0) अणु
		error = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
		अगर (error < 0)
			वापस error;
	पूर्ण अन्यथा अणु
		अगर (ग_लिखो_len > 0) अणु
			error = i2c_transfer(client->adapter, msgs, 1);
			अगर (error < 0)
				वापस error;
		पूर्ण
		अगर (delay > 0)
			mdelay(delay);

		अगर (पढ़ो_len > 0) अणु
			error = i2c_transfer(client->adapter, msgs + 1, 1);
			अगर (error < 0)
				वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* ILITEK ISR APIs */
अटल व्योम ilitek_touch_करोwn(काष्ठा ilitek_ts_data *ts, अचिन्हित पूर्णांक id,
			      अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	काष्ठा input_dev *input = ts->input_dev;

	input_mt_slot(input, id);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, true);

	touchscreen_report_pos(input, &ts->prop, x, y, true);
पूर्ण

अटल पूर्णांक ilitek_process_and_report_v6(काष्ठा ilitek_ts_data *ts)
अणु
	पूर्णांक error = 0;
	u8 buf[512];
	पूर्णांक packet_len = 5;
	पूर्णांक packet_max_poपूर्णांक = 10;
	पूर्णांक report_max_poपूर्णांक;
	पूर्णांक i, count;
	काष्ठा input_dev *input = ts->input_dev;
	काष्ठा device *dev = &ts->client->dev;
	अचिन्हित पूर्णांक x, y, status, id;

	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, शून्य, 0, 0, buf, 64);
	अगर (error) अणु
		dev_err(dev, "get touch info failed, err:%d\n", error);
		जाओ err_sync_frame;
	पूर्ण

	report_max_poपूर्णांक = buf[REPORT_COUNT_ADDRESS];
	अगर (report_max_poपूर्णांक > ts->max_tp) अणु
		dev_err(dev, "FW report max point:%d > panel info. max:%d\n",
			report_max_poपूर्णांक, ts->max_tp);
		error = -EINVAL;
		जाओ err_sync_frame;
	पूर्ण

	count = DIV_ROUND_UP(report_max_poपूर्णांक, packet_max_poपूर्णांक);
	क्रम (i = 1; i < count; i++) अणु
		error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, शून्य, 0, 0,
						  buf + i * 64, 64);
		अगर (error) अणु
			dev_err(dev, "get touch info. failed, cnt:%d, err:%d\n",
				count, error);
			जाओ err_sync_frame;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < report_max_poपूर्णांक; i++) अणु
		status = buf[i * packet_len + 1] & 0x40;
		अगर (!status)
			जारी;

		id = buf[i * packet_len + 1] & 0x3F;

		x = get_unaligned_le16(buf + i * packet_len + 2);
		y = get_unaligned_le16(buf + i * packet_len + 4);

		अगर (x > ts->screen_max_x || x < ts->screen_min_x ||
		    y > ts->screen_max_y || y < ts->screen_min_y) अणु
			dev_warn(dev, "invalid position, X[%d,%u,%d], Y[%d,%u,%d]\n",
				 ts->screen_min_x, x, ts->screen_max_x,
				 ts->screen_min_y, y, ts->screen_max_y);
			जारी;
		पूर्ण

		ilitek_touch_करोwn(ts, id, x, y);
	पूर्ण

err_sync_frame:
	input_mt_sync_frame(input);
	input_sync(input);
	वापस error;
पूर्ण

/* APIs of cmds क्रम ILITEK Touch IC */
अटल पूर्णांक api_protocol_set_cmd(काष्ठा ilitek_ts_data *ts,
				u16 idx, u8 *inbuf, u8 *outbuf)
अणु
	u16 cmd;
	पूर्णांक error;

	अगर (idx >= MAX_CMD_CNT)
		वापस -EINVAL;

	cmd = ts->ptl_cb_func[idx].cmd;
	error = ts->ptl_cb_func[idx].func(ts, cmd, inbuf, outbuf);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_get_ptl_ver(काष्ठा ilitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	पूर्णांक error;
	u8 buf[64];

	buf[0] = cmd;
	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 5, outbuf, 3);
	अगर (error)
		वापस error;

	ts->ptl.ver = get_unaligned_be16(outbuf);
	ts->ptl.ver_major = outbuf[0];

	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_get_mcu_ver(काष्ठा ilitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	पूर्णांक error;
	u8 buf[64];

	buf[0] = cmd;
	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 5, outbuf, 32);
	अगर (error)
		वापस error;

	ts->mcu_ver = get_unaligned_le16(outbuf);
	स_रखो(ts->product_id, 0, माप(ts->product_id));
	स_नकल(ts->product_id, outbuf + 6, 26);

	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_get_fw_ver(काष्ठा ilitek_ts_data *ts,
				   u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	पूर्णांक error;
	u8 buf[64];

	buf[0] = cmd;
	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 5, outbuf, 8);
	अगर (error)
		वापस error;

	स_नकल(ts->firmware_ver, outbuf, 8);

	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_get_scrn_res(काष्ठा ilitek_ts_data *ts,
				     u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	पूर्णांक error;
	u8 buf[64];

	buf[0] = cmd;
	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 5, outbuf, 8);
	अगर (error)
		वापस error;

	ts->screen_min_x = get_unaligned_le16(outbuf);
	ts->screen_min_y = get_unaligned_le16(outbuf + 2);
	ts->screen_max_x = get_unaligned_le16(outbuf + 4);
	ts->screen_max_y = get_unaligned_le16(outbuf + 6);

	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_get_tp_res(काष्ठा ilitek_ts_data *ts,
				   u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	पूर्णांक error;
	u8 buf[64];

	buf[0] = cmd;
	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 5, outbuf, 15);
	अगर (error)
		वापस error;

	ts->max_tp = outbuf[8];
	अगर (ts->max_tp > ILITEK_SUPPORT_MAX_POINT) अणु
		dev_err(&ts->client->dev, "Invalid MAX_TP:%d from FW\n",
			ts->max_tp);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_get_ic_mode(काष्ठा ilitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	पूर्णांक error;
	u8 buf[64];

	buf[0] = cmd;
	error = ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 5, outbuf, 2);
	अगर (error)
		वापस error;

	ts->ic_mode = outbuf[0];
	वापस 0;
पूर्ण

अटल पूर्णांक api_protocol_set_ic_sleep(काष्ठा ilitek_ts_data *ts,
				     u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	u8 buf[64];

	buf[0] = cmd;
	वापस ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 0, शून्य, 0);
पूर्ण

अटल पूर्णांक api_protocol_set_ic_wake(काष्ठा ilitek_ts_data *ts,
				    u16 cmd, u8 *inbuf, u8 *outbuf)
अणु
	u8 buf[64];

	buf[0] = cmd;
	वापस ilitek_i2c_ग_लिखो_and_पढ़ो(ts, buf, 1, 0, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा ilitek_protocol_map ptl_func_map[] = अणु
	/* common cmds */
	[GET_PTL_VER] = अणु
		ILITEK_TP_CMD_GET_PRL_VER, "GET_PTL_VER",
		api_protocol_get_ptl_ver
	पूर्ण,
	[GET_FW_VER] = अणु
		ILITEK_TP_CMD_GET_FW_VER, "GET_FW_VER",
		api_protocol_get_fw_ver
	पूर्ण,
	[GET_SCRN_RES] = अणु
		ILITEK_TP_CMD_GET_SCRN_RES, "GET_SCRN_RES",
		api_protocol_get_scrn_res
	पूर्ण,
	[GET_TP_RES] = अणु
		ILITEK_TP_CMD_GET_TP_RES, "GET_TP_RES",
		api_protocol_get_tp_res
	पूर्ण,
	[GET_IC_MODE] = अणु
		ILITEK_TP_CMD_GET_IC_MODE, "GET_IC_MODE",
			   api_protocol_get_ic_mode
	पूर्ण,
	[GET_MCU_VER] = अणु
		ILITEK_TP_CMD_GET_MCU_VER, "GET_MOD_VER",
			   api_protocol_get_mcu_ver
	पूर्ण,
	[SET_IC_SLEEP] = अणु
		ILITEK_TP_CMD_SET_IC_SLEEP, "SET_IC_SLEEP",
		api_protocol_set_ic_sleep
	पूर्ण,
	[SET_IC_WAKE] = अणु
		ILITEK_TP_CMD_SET_IC_WAKE, "SET_IC_WAKE",
		api_protocol_set_ic_wake
	पूर्ण,
पूर्ण;

/* Probe APIs */
अटल व्योम ilitek_reset(काष्ठा ilitek_ts_data *ts, पूर्णांक delay)
अणु
	अगर (ts->reset_gpio) अणु
		gpiod_set_value(ts->reset_gpio, 1);
		mdelay(10);
		gpiod_set_value(ts->reset_gpio, 0);
		mdelay(delay);
	पूर्ण
पूर्ण

अटल पूर्णांक ilitek_protocol_init(काष्ठा ilitek_ts_data *ts)
अणु
	पूर्णांक error;
	u8 outbuf[64];

	ts->ptl_cb_func = ptl_func_map;
	ts->reset_समय = 600;

	error = api_protocol_set_cmd(ts, GET_PTL_VER, शून्य, outbuf);
	अगर (error)
		वापस error;

	/* Protocol v3 is not support currently */
	अगर (ts->ptl.ver_major == 0x3 ||
	    ts->ptl.ver == BL_V1_6 ||
	    ts->ptl.ver == BL_V1_7)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ilitek_पढ़ो_tp_info(काष्ठा ilitek_ts_data *ts, bool boot)
अणु
	u8 outbuf[256];
	पूर्णांक error;

	error = api_protocol_set_cmd(ts, GET_PTL_VER, शून्य, outbuf);
	अगर (error)
		वापस error;

	error = api_protocol_set_cmd(ts, GET_MCU_VER, शून्य, outbuf);
	अगर (error)
		वापस error;

	error = api_protocol_set_cmd(ts, GET_FW_VER, शून्य, outbuf);
	अगर (error)
		वापस error;

	अगर (boot) अणु
		error = api_protocol_set_cmd(ts, GET_SCRN_RES, शून्य,
					     outbuf);
		अगर (error)
			वापस error;
	पूर्ण

	error = api_protocol_set_cmd(ts, GET_TP_RES, शून्य, outbuf);
	अगर (error)
		वापस error;

	error = api_protocol_set_cmd(ts, GET_IC_MODE, शून्य, outbuf);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक ilitek_input_dev_init(काष्ठा device *dev, काष्ठा ilitek_ts_data *ts)
अणु
	पूर्णांक error;
	काष्ठा input_dev *input;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	ts->input_dev = input;
	input->name = ILITEK_TS_NAME;
	input->id.bustype = BUS_I2C;

	__set_bit(INPUT_PROP_सूचीECT, input->propbit);

	input_set_असल_params(input, ABS_MT_POSITION_X,
			     ts->screen_min_x, ts->screen_max_x, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y,
			     ts->screen_min_y, ts->screen_max_y, 0, 0);

	touchscreen_parse_properties(input, true, &ts->prop);

	error = input_mt_init_slots(input, ts->max_tp,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(dev, "initialize MT slots failed, err:%d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "register input device failed, err:%d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t ilitek_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ilitek_ts_data *ts = dev_id;
	पूर्णांक error;

	error = ilitek_process_and_report_v6(ts);
	अगर (error < 0) अणु
		dev_err(&ts->client->dev, "[%s] err:%d\n", __func__, error);
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ilitek_ts_data *ts = i2c_get_clientdata(client);

	वापस scnम_लिखो(buf, PAGE_SIZE,
			 "fw version: [%02X%02X.%02X%02X.%02X%02X.%02X%02X]\n",
			 ts->firmware_ver[0], ts->firmware_ver[1],
			 ts->firmware_ver[2], ts->firmware_ver[3],
			 ts->firmware_ver[4], ts->firmware_ver[5],
			 ts->firmware_ver[6], ts->firmware_ver[7]);
पूर्ण
अटल DEVICE_ATTR_RO(firmware_version);

अटल sमाप_प्रकार product_id_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ilitek_ts_data *ts = i2c_get_clientdata(client);

	वापस scnम_लिखो(buf, PAGE_SIZE, "product id: [%04X], module: [%s]\n",
			 ts->mcu_ver, ts->product_id);
पूर्ण
अटल DEVICE_ATTR_RO(product_id);

अटल काष्ठा attribute *ilitek_sysfs_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_product_id.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ilitek_attrs_group = अणु
	.attrs = ilitek_sysfs_attrs,
पूर्ण;

अटल पूर्णांक ilitek_ts_i2c_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ilitek_ts_data *ts;
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "i2c check functionality failed\n");
		वापस -ENXIO;
	पूर्ण

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;
	i2c_set_clientdata(client, ts);

	ts->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);
		dev_err(dev, "request gpiod failed: %d", error);
		वापस error;
	पूर्ण

	ilitek_reset(ts, 1000);

	error = ilitek_protocol_init(ts);
	अगर (error) अणु
		dev_err(dev, "protocol init failed: %d", error);
		वापस error;
	पूर्ण

	error = ilitek_पढ़ो_tp_info(ts, true);
	अगर (error) अणु
		dev_err(dev, "read tp info failed: %d", error);
		वापस error;
	पूर्ण

	error = ilitek_input_dev_init(dev, ts);
	अगर (error) अणु
		dev_err(dev, "input dev init failed: %d", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, ts->client->irq,
					  शून्य, ilitek_i2c_isr, IRQF_ONESHOT,
					  "ilitek_touch_irq", ts);
	अगर (error) अणु
		dev_err(dev, "request threaded irq failed: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_device_add_group(dev, &ilitek_attrs_group);
	अगर (error) अणु
		dev_err(dev, "sysfs create group failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ilitek_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ilitek_ts_data *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	disable_irq(client->irq);

	अगर (!device_may_wakeup(dev)) अणु
		error = api_protocol_set_cmd(ts, SET_IC_SLEEP, शून्य, शून्य);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ilitek_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ilitek_ts_data *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	अगर (!device_may_wakeup(dev)) अणु
		error = api_protocol_set_cmd(ts, SET_IC_WAKE, शून्य, शून्य);
		अगर (error)
			वापस error;

		ilitek_reset(ts, ts->reset_समय);
	पूर्ण

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ilitek_pm_ops, ilitek_suspend, ilitek_resume);

अटल स्थिर काष्ठा i2c_device_id ilitek_ts_i2c_id[] = अणु
	अणु ILITEK_TS_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ilitek_ts_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ilitekts_acpi_id[] = अणु
	अणु "ILTK0001", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ilitekts_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ilitek_ts_i2c_match[] = अणु
	अणु.compatible = "ilitek,ili2130",पूर्ण,
	अणु.compatible = "ilitek,ili2131",पूर्ण,
	अणु.compatible = "ilitek,ili2132",पूर्ण,
	अणु.compatible = "ilitek,ili2316",पूर्ण,
	अणु.compatible = "ilitek,ili2322",पूर्ण,
	अणु.compatible = "ilitek,ili2323",पूर्ण,
	अणु.compatible = "ilitek,ili2326",पूर्ण,
	अणु.compatible = "ilitek,ili2520",पूर्ण,
	अणु.compatible = "ilitek,ili2521",पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ilitek_ts_i2c_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ilitek_ts_i2c_driver = अणु
	.driver = अणु
		.name = ILITEK_TS_NAME,
		.pm = &ilitek_pm_ops,
		.of_match_table = of_match_ptr(ilitek_ts_i2c_match),
		.acpi_match_table = ACPI_PTR(ilitekts_acpi_id),
	पूर्ण,
	.probe = ilitek_ts_i2c_probe,
	.id_table = ilitek_ts_i2c_id,
पूर्ण;
module_i2c_driver(ilitek_ts_i2c_driver);

MODULE_AUTHOR("ILITEK");
MODULE_DESCRIPTION("ILITEK I2C Touchscreen Driver");
MODULE_LICENSE("GPL");
