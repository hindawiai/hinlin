<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम Goodix Touchscreens
 *
 *  Copyright (c) 2014 Red Hat Inc.
 *  Copyright (c) 2015 K. Merker <merker@debian.org>
 *
 *  This code is based on gt9xx.c authored by andrew@goodix.com:
 *
 *  2010 - 2012 Goodix Technology.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/dmi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा GOODIX_GPIO_INT_NAME		"irq"
#घोषणा GOODIX_GPIO_RST_NAME		"reset"

#घोषणा GOODIX_MAX_HEIGHT		4096
#घोषणा GOODIX_MAX_WIDTH		4096
#घोषणा GOODIX_INT_TRIGGER		1
#घोषणा GOODIX_CONTACT_SIZE		8
#घोषणा GOODIX_MAX_CONTACT_SIZE		9
#घोषणा GOODIX_MAX_CONTACTS		10
#घोषणा GOODIX_MAX_KEYS			7

#घोषणा GOODIX_CONFIG_MIN_LENGTH	186
#घोषणा GOODIX_CONFIG_911_LENGTH	186
#घोषणा GOODIX_CONFIG_967_LENGTH	228
#घोषणा GOODIX_CONFIG_GT9X_LENGTH	240
#घोषणा GOODIX_CONFIG_MAX_LENGTH	240

/* Register defines */
#घोषणा GOODIX_REG_COMMAND		0x8040
#घोषणा GOODIX_CMD_SCREEN_OFF		0x05

#घोषणा GOODIX_READ_COOR_ADDR		0x814E
#घोषणा GOODIX_GT1X_REG_CONFIG_DATA	0x8050
#घोषणा GOODIX_GT9X_REG_CONFIG_DATA	0x8047
#घोषणा GOODIX_REG_ID			0x8140

#घोषणा GOODIX_BUFFER_STATUS_READY	BIT(7)
#घोषणा GOODIX_HAVE_KEY			BIT(4)
#घोषणा GOODIX_BUFFER_STATUS_TIMEOUT	20

#घोषणा RESOLUTION_LOC		1
#घोषणा MAX_CONTACTS_LOC	5
#घोषणा TRIGGER_LOC		6

/* Our special handling क्रम GPIO accesses through ACPI is x86 specअगरic */
#अगर defined CONFIG_X86 && defined CONFIG_ACPI
#घोषणा ACPI_GPIO_SUPPORT
#पूर्ण_अगर

काष्ठा goodix_ts_data;

क्रमागत goodix_irq_pin_access_method अणु
	IRQ_PIN_ACCESS_NONE,
	IRQ_PIN_ACCESS_GPIO,
	IRQ_PIN_ACCESS_ACPI_GPIO,
	IRQ_PIN_ACCESS_ACPI_METHOD,
पूर्ण;

काष्ठा goodix_chip_data अणु
	u16 config_addr;
	पूर्णांक config_len;
	पूर्णांक (*check_config)(काष्ठा goodix_ts_data *ts, स्थिर u8 *cfg, पूर्णांक len);
	व्योम (*calc_config_checksum)(काष्ठा goodix_ts_data *ts);
पूर्ण;

काष्ठा goodix_chip_id अणु
	स्थिर अक्षर *id;
	स्थिर काष्ठा goodix_chip_data *data;
पूर्ण;

#घोषणा GOODIX_ID_MAX_LEN	4

काष्ठा goodix_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	स्थिर काष्ठा goodix_chip_data *chip;
	काष्ठा touchscreen_properties prop;
	अचिन्हित पूर्णांक max_touch_num;
	अचिन्हित पूर्णांक पूर्णांक_trigger_type;
	काष्ठा regulator *avdd28;
	काष्ठा regulator *vddio;
	काष्ठा gpio_desc *gpiod_पूर्णांक;
	काष्ठा gpio_desc *gpiod_rst;
	पूर्णांक gpio_count;
	पूर्णांक gpio_पूर्णांक_idx;
	अक्षर id[GOODIX_ID_MAX_LEN + 1];
	u16 version;
	स्थिर अक्षर *cfg_name;
	bool reset_controller_at_probe;
	bool load_cfg_from_disk;
	काष्ठा completion firmware_loading_complete;
	अचिन्हित दीर्घ irq_flags;
	क्रमागत goodix_irq_pin_access_method irq_pin_access_method;
	अचिन्हित पूर्णांक contact_size;
	u8 config[GOODIX_CONFIG_MAX_LENGTH];
	अचिन्हित लघु keymap[GOODIX_MAX_KEYS];
पूर्ण;

अटल पूर्णांक goodix_check_cfg_8(काष्ठा goodix_ts_data *ts,
			      स्थिर u8 *cfg, पूर्णांक len);
अटल पूर्णांक goodix_check_cfg_16(काष्ठा goodix_ts_data *ts,
			       स्थिर u8 *cfg, पूर्णांक len);
अटल व्योम goodix_calc_cfg_checksum_8(काष्ठा goodix_ts_data *ts);
अटल व्योम goodix_calc_cfg_checksum_16(काष्ठा goodix_ts_data *ts);

अटल स्थिर काष्ठा goodix_chip_data gt1x_chip_data = अणु
	.config_addr		= GOODIX_GT1X_REG_CONFIG_DATA,
	.config_len		= GOODIX_CONFIG_GT9X_LENGTH,
	.check_config		= goodix_check_cfg_16,
	.calc_config_checksum	= goodix_calc_cfg_checksum_16,
पूर्ण;

अटल स्थिर काष्ठा goodix_chip_data gt911_chip_data = अणु
	.config_addr		= GOODIX_GT9X_REG_CONFIG_DATA,
	.config_len		= GOODIX_CONFIG_911_LENGTH,
	.check_config		= goodix_check_cfg_8,
	.calc_config_checksum	= goodix_calc_cfg_checksum_8,
पूर्ण;

अटल स्थिर काष्ठा goodix_chip_data gt967_chip_data = अणु
	.config_addr		= GOODIX_GT9X_REG_CONFIG_DATA,
	.config_len		= GOODIX_CONFIG_967_LENGTH,
	.check_config		= goodix_check_cfg_8,
	.calc_config_checksum	= goodix_calc_cfg_checksum_8,
पूर्ण;

अटल स्थिर काष्ठा goodix_chip_data gt9x_chip_data = अणु
	.config_addr		= GOODIX_GT9X_REG_CONFIG_DATA,
	.config_len		= GOODIX_CONFIG_GT9X_LENGTH,
	.check_config		= goodix_check_cfg_8,
	.calc_config_checksum	= goodix_calc_cfg_checksum_8,
पूर्ण;

अटल स्थिर काष्ठा goodix_chip_id goodix_chip_ids[] = अणु
	अणु .id = "1151", .data = &gt1x_chip_data पूर्ण,
	अणु .id = "5663", .data = &gt1x_chip_data पूर्ण,
	अणु .id = "5688", .data = &gt1x_chip_data पूर्ण,
	अणु .id = "917S", .data = &gt1x_chip_data पूर्ण,
	अणु .id = "9286", .data = &gt1x_chip_data पूर्ण,

	अणु .id = "911", .data = &gt911_chip_data पूर्ण,
	अणु .id = "9271", .data = &gt911_chip_data पूर्ण,
	अणु .id = "9110", .data = &gt911_chip_data पूर्ण,
	अणु .id = "927", .data = &gt911_chip_data पूर्ण,
	अणु .id = "928", .data = &gt911_chip_data पूर्ण,

	अणु .id = "912", .data = &gt967_chip_data पूर्ण,
	अणु .id = "9147", .data = &gt967_chip_data पूर्ण,
	अणु .id = "967", .data = &gt967_chip_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ goodix_irq_flags[] = अणु
	IRQ_TYPE_EDGE_RISING,
	IRQ_TYPE_EDGE_FALLING,
	IRQ_TYPE_LEVEL_LOW,
	IRQ_TYPE_LEVEL_HIGH,
पूर्ण;

/*
 * Those tablets have their coordinates origin at the bottom right
 * of the tablet, as अगर rotated 180 degrees
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id rotated_screen[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		.ident = "Teclast X89",
		.matches = अणु
			/* tPAD is too generic, also match on bios date */
			DMI_MATCH(DMI_BOARD_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_BOARD_NAME, "tPAD"),
			DMI_MATCH(DMI_BIOS_DATE, "12/19/2014"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Teclast X98 Pro",
		.matches = अणु
			/*
			 * Only match BIOS date, because the manufacturers
			 * BIOS करोes not report the board name at all
			 * (someबार)...
			 */
			DMI_MATCH(DMI_BOARD_VENDOR, "TECLAST"),
			DMI_MATCH(DMI_BIOS_DATE, "10/28/2015"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "WinBook TW100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "WinBook"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TW100")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "WinBook TW700",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "WinBook"),
			DMI_MATCH(DMI_PRODUCT_NAME, "TW700")
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id nine_bytes_report[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		.ident = "Lenovo YogaBook",
		/* YB1-X91L/F and YB1-X90L/F */
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Lenovo YB1-X9")
		पूर्ण
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

/*
 * Those tablets have their x coordinate inverted
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id inverted_x_screen[] = अणु
#अगर defined(CONFIG_DMI) && defined(CONFIG_X86)
	अणु
		.ident = "Cube I15-TC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Cube"),
			DMI_MATCH(DMI_PRODUCT_NAME, "I15-TC")
		पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

/**
 * goodix_i2c_पढ़ो - पढ़ो data from a रेजिस्टर of the i2c slave device.
 *
 * @client: i2c device.
 * @reg: the रेजिस्टर to पढ़ो from.
 * @buf: raw ग_लिखो data buffer.
 * @len: length of the buffer to ग_लिखो
 */
अटल पूर्णांक goodix_i2c_पढ़ो(काष्ठा i2c_client *client,
			   u16 reg, u8 *buf, पूर्णांक len)
अणु
	काष्ठा i2c_msg msgs[2];
	__be16 wbuf = cpu_to_be16(reg);
	पूर्णांक ret;

	msgs[0].flags = 0;
	msgs[0].addr  = client->addr;
	msgs[0].len   = 2;
	msgs[0].buf   = (u8 *)&wbuf;

	msgs[1].flags = I2C_M_RD;
	msgs[1].addr  = client->addr;
	msgs[1].len   = len;
	msgs[1].buf   = buf;

	ret = i2c_transfer(client->adapter, msgs, 2);
	वापस ret < 0 ? ret : (ret != ARRAY_SIZE(msgs) ? -EIO : 0);
पूर्ण

/**
 * goodix_i2c_ग_लिखो - ग_लिखो data to a रेजिस्टर of the i2c slave device.
 *
 * @client: i2c device.
 * @reg: the रेजिस्टर to ग_लिखो to.
 * @buf: raw data buffer to ग_लिखो.
 * @len: length of the buffer to ग_लिखो
 */
अटल पूर्णांक goodix_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 reg, स्थिर u8 *buf,
			    अचिन्हित len)
अणु
	u8 *addr_buf;
	काष्ठा i2c_msg msg;
	पूर्णांक ret;

	addr_buf = kदो_स्मृति(len + 2, GFP_KERNEL);
	अगर (!addr_buf)
		वापस -ENOMEM;

	addr_buf[0] = reg >> 8;
	addr_buf[1] = reg & 0xFF;
	स_नकल(&addr_buf[2], buf, len);

	msg.flags = 0;
	msg.addr = client->addr;
	msg.buf = addr_buf;
	msg.len = len + 2;

	ret = i2c_transfer(client->adapter, &msg, 1);
	kमुक्त(addr_buf);
	वापस ret < 0 ? ret : (ret != 1 ? -EIO : 0);
पूर्ण

अटल पूर्णांक goodix_i2c_ग_लिखो_u8(काष्ठा i2c_client *client, u16 reg, u8 value)
अणु
	वापस goodix_i2c_ग_लिखो(client, reg, &value, माप(value));
पूर्ण

अटल स्थिर काष्ठा goodix_chip_data *goodix_get_chip_data(स्थिर अक्षर *id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; goodix_chip_ids[i].id; i++) अणु
		अगर (!म_भेद(goodix_chip_ids[i].id, id))
			वापस goodix_chip_ids[i].data;
	पूर्ण

	वापस &gt9x_chip_data;
पूर्ण

अटल पूर्णांक goodix_ts_पढ़ो_input_report(काष्ठा goodix_ts_data *ts, u8 *data)
अणु
	अचिन्हित दीर्घ max_समयout;
	पूर्णांक touch_num;
	पूर्णांक error;
	u16 addr = GOODIX_READ_COOR_ADDR;
	/*
	 * We are going to पढ़ो 1-byte header,
	 * ts->contact_size * max(1, touch_num) bytes of coordinates
	 * and 1-byte footer which contains the touch-key code.
	 */
	स्थिर पूर्णांक header_contact_keycode_size = 1 + ts->contact_size + 1;

	/*
	 * The 'buffer status' bit, which indicates that the data is valid, is
	 * not set as soon as the पूर्णांकerrupt is उठाओd, but slightly after.
	 * This takes around 10 ms to happen, so we poll क्रम 20 ms.
	 */
	max_समयout = jअगरfies + msecs_to_jअगरfies(GOODIX_BUFFER_STATUS_TIMEOUT);
	करो अणु
		error = goodix_i2c_पढ़ो(ts->client, addr, data,
					header_contact_keycode_size);
		अगर (error) अणु
			dev_err(&ts->client->dev, "I2C transfer error: %d\n",
					error);
			वापस error;
		पूर्ण

		अगर (data[0] & GOODIX_BUFFER_STATUS_READY) अणु
			touch_num = data[0] & 0x0f;
			अगर (touch_num > ts->max_touch_num)
				वापस -EPROTO;

			अगर (touch_num > 1) अणु
				addr += header_contact_keycode_size;
				data += header_contact_keycode_size;
				error = goodix_i2c_पढ़ो(ts->client,
						addr, data,
						ts->contact_size *
							(touch_num - 1));
				अगर (error)
					वापस error;
			पूर्ण

			वापस touch_num;
		पूर्ण

		usleep_range(1000, 2000); /* Poll every 1 - 2 ms */
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, max_समयout));

	/*
	 * The Goodix panel will send spurious पूर्णांकerrupts after a
	 * 'finger up' event, which will always cause a समयout.
	 */
	वापस -ENOMSG;
पूर्ण

अटल व्योम goodix_ts_report_touch_8b(काष्ठा goodix_ts_data *ts, u8 *coor_data)
अणु
	पूर्णांक id = coor_data[0] & 0x0F;
	पूर्णांक input_x = get_unaligned_le16(&coor_data[1]);
	पूर्णांक input_y = get_unaligned_le16(&coor_data[3]);
	पूर्णांक input_w = get_unaligned_le16(&coor_data[5]);

	input_mt_slot(ts->input_dev, id);
	input_mt_report_slot_state(ts->input_dev, MT_TOOL_FINGER, true);
	touchscreen_report_pos(ts->input_dev, &ts->prop,
			       input_x, input_y, true);
	input_report_असल(ts->input_dev, ABS_MT_TOUCH_MAJOR, input_w);
	input_report_असल(ts->input_dev, ABS_MT_WIDTH_MAJOR, input_w);
पूर्ण

अटल व्योम goodix_ts_report_touch_9b(काष्ठा goodix_ts_data *ts, u8 *coor_data)
अणु
	पूर्णांक id = coor_data[1] & 0x0F;
	पूर्णांक input_x = get_unaligned_le16(&coor_data[3]);
	पूर्णांक input_y = get_unaligned_le16(&coor_data[5]);
	पूर्णांक input_w = get_unaligned_le16(&coor_data[7]);

	input_mt_slot(ts->input_dev, id);
	input_mt_report_slot_state(ts->input_dev, MT_TOOL_FINGER, true);
	touchscreen_report_pos(ts->input_dev, &ts->prop,
			       input_x, input_y, true);
	input_report_असल(ts->input_dev, ABS_MT_TOUCH_MAJOR, input_w);
	input_report_असल(ts->input_dev, ABS_MT_WIDTH_MAJOR, input_w);
पूर्ण

अटल व्योम goodix_ts_report_key(काष्ठा goodix_ts_data *ts, u8 *data)
अणु
	पूर्णांक touch_num;
	u8 key_value;
	पूर्णांक i;

	अगर (data[0] & GOODIX_HAVE_KEY) अणु
		touch_num = data[0] & 0x0f;
		key_value = data[1 + ts->contact_size * touch_num];
		क्रम (i = 0; i < GOODIX_MAX_KEYS; i++)
			अगर (key_value & BIT(i))
				input_report_key(ts->input_dev,
						 ts->keymap[i], 1);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < GOODIX_MAX_KEYS; i++)
			input_report_key(ts->input_dev, ts->keymap[i], 0);
	पूर्ण
पूर्ण

/**
 * goodix_process_events - Process incoming events
 *
 * @ts: our goodix_ts_data poपूर्णांकer
 *
 * Called when the IRQ is triggered. Read the current device state, and push
 * the input events to the user space.
 */
अटल व्योम goodix_process_events(काष्ठा goodix_ts_data *ts)
अणु
	u8  poपूर्णांक_data[2 + GOODIX_MAX_CONTACT_SIZE * GOODIX_MAX_CONTACTS];
	पूर्णांक touch_num;
	पूर्णांक i;

	touch_num = goodix_ts_पढ़ो_input_report(ts, poपूर्णांक_data);
	अगर (touch_num < 0)
		वापस;

	goodix_ts_report_key(ts, poपूर्णांक_data);

	क्रम (i = 0; i < touch_num; i++)
		अगर (ts->contact_size == 9)
			goodix_ts_report_touch_9b(ts,
				&poपूर्णांक_data[1 + ts->contact_size * i]);
		अन्यथा
			goodix_ts_report_touch_8b(ts,
				&poपूर्णांक_data[1 + ts->contact_size * i]);

	input_mt_sync_frame(ts->input_dev);
	input_sync(ts->input_dev);
पूर्ण

/**
 * goodix_ts_irq_handler - The IRQ handler
 *
 * @irq: पूर्णांकerrupt number.
 * @dev_id: निजी data poपूर्णांकer.
 */
अटल irqवापस_t goodix_ts_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा goodix_ts_data *ts = dev_id;

	goodix_process_events(ts);

	अगर (goodix_i2c_ग_लिखो_u8(ts->client, GOODIX_READ_COOR_ADDR, 0) < 0)
		dev_err(&ts->client->dev, "I2C write end_cmd error\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम goodix_मुक्त_irq(काष्ठा goodix_ts_data *ts)
अणु
	devm_मुक्त_irq(&ts->client->dev, ts->client->irq, ts);
पूर्ण

अटल पूर्णांक goodix_request_irq(काष्ठा goodix_ts_data *ts)
अणु
	वापस devm_request_thपढ़ोed_irq(&ts->client->dev, ts->client->irq,
					 शून्य, goodix_ts_irq_handler,
					 ts->irq_flags, ts->client->name, ts);
पूर्ण

अटल पूर्णांक goodix_check_cfg_8(काष्ठा goodix_ts_data *ts, स्थिर u8 *cfg, पूर्णांक len)
अणु
	पूर्णांक i, raw_cfg_len = len - 2;
	u8 check_sum = 0;

	क्रम (i = 0; i < raw_cfg_len; i++)
		check_sum += cfg[i];
	check_sum = (~check_sum) + 1;
	अगर (check_sum != cfg[raw_cfg_len]) अणु
		dev_err(&ts->client->dev,
			"The checksum of the config fw is not correct");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg[raw_cfg_len + 1] != 1) अणु
		dev_err(&ts->client->dev,
			"Config fw must have Config_Fresh register set");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम goodix_calc_cfg_checksum_8(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक i, raw_cfg_len = ts->chip->config_len - 2;
	u8 check_sum = 0;

	क्रम (i = 0; i < raw_cfg_len; i++)
		check_sum += ts->config[i];
	check_sum = (~check_sum) + 1;

	ts->config[raw_cfg_len] = check_sum;
	ts->config[raw_cfg_len + 1] = 1; /* Set "config_fresh" bit */
पूर्ण

अटल पूर्णांक goodix_check_cfg_16(काष्ठा goodix_ts_data *ts, स्थिर u8 *cfg,
			       पूर्णांक len)
अणु
	पूर्णांक i, raw_cfg_len = len - 3;
	u16 check_sum = 0;

	क्रम (i = 0; i < raw_cfg_len; i += 2)
		check_sum += get_unaligned_be16(&cfg[i]);
	check_sum = (~check_sum) + 1;
	अगर (check_sum != get_unaligned_be16(&cfg[raw_cfg_len])) अणु
		dev_err(&ts->client->dev,
			"The checksum of the config fw is not correct");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg[raw_cfg_len + 2] != 1) अणु
		dev_err(&ts->client->dev,
			"Config fw must have Config_Fresh register set");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम goodix_calc_cfg_checksum_16(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक i, raw_cfg_len = ts->chip->config_len - 3;
	u16 check_sum = 0;

	क्रम (i = 0; i < raw_cfg_len; i += 2)
		check_sum += get_unaligned_be16(&ts->config[i]);
	check_sum = (~check_sum) + 1;

	put_unaligned_be16(check_sum, &ts->config[raw_cfg_len]);
	ts->config[raw_cfg_len + 2] = 1; /* Set "config_fresh" bit */
पूर्ण

/**
 * goodix_check_cfg - Checks अगर config fw is valid
 *
 * @ts: goodix_ts_data poपूर्णांकer
 * @cfg: firmware config data
 * @len: config data length
 */
अटल पूर्णांक goodix_check_cfg(काष्ठा goodix_ts_data *ts, स्थिर u8 *cfg, पूर्णांक len)
अणु
	अगर (len < GOODIX_CONFIG_MIN_LENGTH ||
	    len > GOODIX_CONFIG_MAX_LENGTH) अणु
		dev_err(&ts->client->dev,
			"The length of the config fw is not correct");
		वापस -EINVAL;
	पूर्ण

	वापस ts->chip->check_config(ts, cfg, len);
पूर्ण

/**
 * goodix_send_cfg - Write fw config to device
 *
 * @ts: goodix_ts_data poपूर्णांकer
 * @cfg: config firmware to ग_लिखो to device
 * @len: config data length
 */
अटल पूर्णांक goodix_send_cfg(काष्ठा goodix_ts_data *ts, स्थिर u8 *cfg, पूर्णांक len)
अणु
	पूर्णांक error;

	error = goodix_check_cfg(ts, cfg, len);
	अगर (error)
		वापस error;

	error = goodix_i2c_ग_लिखो(ts->client, ts->chip->config_addr, cfg, len);
	अगर (error) अणु
		dev_err(&ts->client->dev, "Failed to write config data: %d",
			error);
		वापस error;
	पूर्ण
	dev_dbg(&ts->client->dev, "Config sent successfully.");

	/* Let the firmware reconfigure itself, so sleep क्रम 10ms */
	usleep_range(10000, 11000);

	वापस 0;
पूर्ण

#अगर_घोषित ACPI_GPIO_SUPPORT
अटल पूर्णांक goodix_pin_acpi_direction_input(काष्ठा goodix_ts_data *ts)
अणु
	acpi_handle handle = ACPI_HANDLE(&ts->client->dev);
	acpi_status status;

	status = acpi_evaluate_object(handle, "INTI", शून्य, शून्य);
	वापस ACPI_SUCCESS(status) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक goodix_pin_acpi_output_method(काष्ठा goodix_ts_data *ts, पूर्णांक value)
अणु
	acpi_handle handle = ACPI_HANDLE(&ts->client->dev);
	acpi_status status;

	status = acpi_execute_simple_method(handle, "INTO", value);
	वापस ACPI_SUCCESS(status) ? 0 : -EIO;
पूर्ण
#अन्यथा
अटल पूर्णांक goodix_pin_acpi_direction_input(काष्ठा goodix_ts_data *ts)
अणु
	dev_err(&ts->client->dev,
		"%s called on device without ACPI support\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक goodix_pin_acpi_output_method(काष्ठा goodix_ts_data *ts, पूर्णांक value)
अणु
	dev_err(&ts->client->dev,
		"%s called on device without ACPI support\n", __func__);
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक goodix_irq_direction_output(काष्ठा goodix_ts_data *ts, पूर्णांक value)
अणु
	चयन (ts->irq_pin_access_method) अणु
	हाल IRQ_PIN_ACCESS_NONE:
		dev_err(&ts->client->dev,
			"%s called without an irq_pin_access_method set\n",
			__func__);
		वापस -EINVAL;
	हाल IRQ_PIN_ACCESS_GPIO:
		वापस gpiod_direction_output(ts->gpiod_पूर्णांक, value);
	हाल IRQ_PIN_ACCESS_ACPI_GPIO:
		/*
		 * The IRQ pin triggers on a falling edge, so its माला_लो marked
		 * as active-low, use output_raw to aव्योम the value inversion.
		 */
		वापस gpiod_direction_output_raw(ts->gpiod_पूर्णांक, value);
	हाल IRQ_PIN_ACCESS_ACPI_METHOD:
		वापस goodix_pin_acpi_output_method(ts, value);
	पूर्ण

	वापस -EINVAL; /* Never reached */
पूर्ण

अटल पूर्णांक goodix_irq_direction_input(काष्ठा goodix_ts_data *ts)
अणु
	चयन (ts->irq_pin_access_method) अणु
	हाल IRQ_PIN_ACCESS_NONE:
		dev_err(&ts->client->dev,
			"%s called without an irq_pin_access_method set\n",
			__func__);
		वापस -EINVAL;
	हाल IRQ_PIN_ACCESS_GPIO:
		वापस gpiod_direction_input(ts->gpiod_पूर्णांक);
	हाल IRQ_PIN_ACCESS_ACPI_GPIO:
		वापस gpiod_direction_input(ts->gpiod_पूर्णांक);
	हाल IRQ_PIN_ACCESS_ACPI_METHOD:
		वापस goodix_pin_acpi_direction_input(ts);
	पूर्ण

	वापस -EINVAL; /* Never reached */
पूर्ण

अटल पूर्णांक goodix_पूर्णांक_sync(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक error;

	error = goodix_irq_direction_output(ts, 0);
	अगर (error)
		वापस error;

	msleep(50);				/* T5: 50ms */

	error = goodix_irq_direction_input(ts);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

/**
 * goodix_reset - Reset device during घातer on
 *
 * @ts: goodix_ts_data poपूर्णांकer
 */
अटल पूर्णांक goodix_reset(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक error;

	/* begin select I2C slave addr */
	error = gpiod_direction_output(ts->gpiod_rst, 0);
	अगर (error)
		वापस error;

	msleep(20);				/* T2: > 10ms */

	/* HIGH: 0x28/0x29, LOW: 0xBA/0xBB */
	error = goodix_irq_direction_output(ts, ts->client->addr == 0x14);
	अगर (error)
		वापस error;

	usleep_range(100, 2000);		/* T3: > 100us */

	error = gpiod_direction_output(ts->gpiod_rst, 1);
	अगर (error)
		वापस error;

	usleep_range(6000, 10000);		/* T4: > 5ms */

	/* end select I2C slave addr */
	error = gpiod_direction_input(ts->gpiod_rst);
	अगर (error)
		वापस error;

	error = goodix_पूर्णांक_sync(ts);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

#अगर_घोषित ACPI_GPIO_SUPPORT
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>

अटल स्थिर काष्ठा x86_cpu_id baytrail_cpu_ids[] = अणु
	अणु X86_VENDOR_INTEL, 6, INTEL_FAM6_ATOM_SILVERMONT, X86_FEATURE_ANY, पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत bool is_byt(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id = x86_match_cpu(baytrail_cpu_ids);

	वापस !!id;
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params first_gpio = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params second_gpio = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_goodix_पूर्णांक_first_gpios[] = अणु
	अणु GOODIX_GPIO_INT_NAME "-gpios", &first_gpio, 1 पूर्ण,
	अणु GOODIX_GPIO_RST_NAME "-gpios", &second_gpio, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_goodix_पूर्णांक_last_gpios[] = अणु
	अणु GOODIX_GPIO_RST_NAME "-gpios", &first_gpio, 1 पूर्ण,
	अणु GOODIX_GPIO_INT_NAME "-gpios", &second_gpio, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_goodix_reset_only_gpios[] = अणु
	अणु GOODIX_GPIO_RST_NAME "-gpios", &first_gpio, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक goodix_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा goodix_ts_data *ts = data;
	काष्ठा device *dev = &ts->client->dev;
	काष्ठा acpi_resource_gpio *gpio;

	चयन (ares->type) अणु
	हाल ACPI_RESOURCE_TYPE_GPIO:
		gpio = &ares->data.gpio;
		अगर (gpio->connection_type == ACPI_RESOURCE_GPIO_TYPE_INT) अणु
			अगर (ts->gpio_पूर्णांक_idx == -1) अणु
				ts->gpio_पूर्णांक_idx = ts->gpio_count;
			पूर्ण अन्यथा अणु
				dev_err(dev, "More then one GpioInt resource, ignoring ACPI GPIO resources\n");
				ts->gpio_पूर्णांक_idx = -2;
			पूर्ण
		पूर्ण
		ts->gpio_count++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function माला_लो called in हाल we fail to get the irq GPIO directly
 * because the ACPI tables lack GPIO-name to APCI _CRS index mappings
 * (no _DSD UUID daffd814-6eba-4d8c-8a91-bc9bbf4aa301 data).
 * In that हाल we add our own mapping and then goodix_get_gpio_config()
 * retries to get the GPIOs based on the added mapping.
 */
अटल पूर्णांक goodix_add_acpi_gpio_mappings(काष्ठा goodix_ts_data *ts)
अणु
	स्थिर काष्ठा acpi_gpio_mapping *gpio_mapping = शून्य;
	काष्ठा device *dev = &ts->client->dev;
	LIST_HEAD(resources);
	पूर्णांक ret;

	ts->gpio_count = 0;
	ts->gpio_पूर्णांक_idx = -1;
	ret = acpi_dev_get_resources(ACPI_COMPANION(dev), &resources,
				     goodix_resource, ts);
	अगर (ret < 0) अणु
		dev_err(dev, "Error getting ACPI resources: %d\n", ret);
		वापस ret;
	पूर्ण

	acpi_dev_मुक्त_resource_list(&resources);

	अगर (ts->gpio_count == 2 && ts->gpio_पूर्णांक_idx == 0) अणु
		ts->irq_pin_access_method = IRQ_PIN_ACCESS_ACPI_GPIO;
		gpio_mapping = acpi_goodix_पूर्णांक_first_gpios;
	पूर्ण अन्यथा अगर (ts->gpio_count == 2 && ts->gpio_पूर्णांक_idx == 1) अणु
		ts->irq_pin_access_method = IRQ_PIN_ACCESS_ACPI_GPIO;
		gpio_mapping = acpi_goodix_पूर्णांक_last_gpios;
	पूर्ण अन्यथा अगर (ts->gpio_count == 1 && ts->gpio_पूर्णांक_idx == -1 &&
		   acpi_has_method(ACPI_HANDLE(dev), "INTI") &&
		   acpi_has_method(ACPI_HANDLE(dev), "INTO")) अणु
		dev_info(dev, "Using ACPI INTI and INTO methods for IRQ pin access\n");
		ts->irq_pin_access_method = IRQ_PIN_ACCESS_ACPI_METHOD;
		gpio_mapping = acpi_goodix_reset_only_gpios;
	पूर्ण अन्यथा अगर (is_byt() && ts->gpio_count == 2 && ts->gpio_पूर्णांक_idx == -1) अणु
		dev_info(dev, "No ACPI GpioInt resource, assuming that the GPIO order is reset, int\n");
		ts->irq_pin_access_method = IRQ_PIN_ACCESS_ACPI_GPIO;
		gpio_mapping = acpi_goodix_पूर्णांक_last_gpios;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Unexpected ACPI resources: gpio_count %d, gpio_int_idx %d\n",
			 ts->gpio_count, ts->gpio_पूर्णांक_idx);
		वापस -EINVAL;
	पूर्ण

	वापस devm_acpi_dev_add_driver_gpios(dev, gpio_mapping);
पूर्ण
#अन्यथा
अटल पूर्णांक goodix_add_acpi_gpio_mappings(काष्ठा goodix_ts_data *ts)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86 && CONFIG_ACPI */

/**
 * goodix_get_gpio_config - Get GPIO config from ACPI/DT
 *
 * @ts: goodix_ts_data poपूर्णांकer
 */
अटल पूर्णांक goodix_get_gpio_config(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक error;
	काष्ठा device *dev;
	काष्ठा gpio_desc *gpiod;
	bool added_acpi_mappings = false;

	अगर (!ts->client)
		वापस -EINVAL;
	dev = &ts->client->dev;

	ts->avdd28 = devm_regulator_get(dev, "AVDD28");
	अगर (IS_ERR(ts->avdd28)) अणु
		error = PTR_ERR(ts->avdd28);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev,
				"Failed to get AVDD28 regulator: %d\n", error);
		वापस error;
	पूर्ण

	ts->vddio = devm_regulator_get(dev, "VDDIO");
	अगर (IS_ERR(ts->vddio)) अणु
		error = PTR_ERR(ts->vddio);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev,
				"Failed to get VDDIO regulator: %d\n", error);
		वापस error;
	पूर्ण

retry_get_irq_gpio:
	/* Get the पूर्णांकerrupt GPIO pin number */
	gpiod = devm_gpiod_get_optional(dev, GOODIX_GPIO_INT_NAME, GPIOD_IN);
	अगर (IS_ERR(gpiod)) अणु
		error = PTR_ERR(gpiod);
		अगर (error != -EPROBE_DEFER)
			dev_dbg(dev, "Failed to get %s GPIO: %d\n",
				GOODIX_GPIO_INT_NAME, error);
		वापस error;
	पूर्ण
	अगर (!gpiod && has_acpi_companion(dev) && !added_acpi_mappings) अणु
		added_acpi_mappings = true;
		अगर (goodix_add_acpi_gpio_mappings(ts) == 0)
			जाओ retry_get_irq_gpio;
	पूर्ण

	ts->gpiod_पूर्णांक = gpiod;

	/* Get the reset line GPIO pin number */
	gpiod = devm_gpiod_get_optional(dev, GOODIX_GPIO_RST_NAME, GPIOD_IN);
	अगर (IS_ERR(gpiod)) अणु
		error = PTR_ERR(gpiod);
		अगर (error != -EPROBE_DEFER)
			dev_dbg(dev, "Failed to get %s GPIO: %d\n",
				GOODIX_GPIO_RST_NAME, error);
		वापस error;
	पूर्ण

	ts->gpiod_rst = gpiod;

	चयन (ts->irq_pin_access_method) अणु
	हाल IRQ_PIN_ACCESS_ACPI_GPIO:
		/*
		 * We end up here अगर goodix_add_acpi_gpio_mappings() has
		 * called devm_acpi_dev_add_driver_gpios() because the ACPI
		 * tables did not contain name to index mappings.
		 * Check that we successfully got both GPIOs after we've
		 * added our own acpi_gpio_mapping and अगर we did not get both
		 * GPIOs reset irq_pin_access_method to IRQ_PIN_ACCESS_NONE.
		 */
		अगर (!ts->gpiod_पूर्णांक || !ts->gpiod_rst)
			ts->irq_pin_access_method = IRQ_PIN_ACCESS_NONE;
		अवरोध;
	हाल IRQ_PIN_ACCESS_ACPI_METHOD:
		अगर (!ts->gpiod_rst)
			ts->irq_pin_access_method = IRQ_PIN_ACCESS_NONE;
		अवरोध;
	शेष:
		अगर (ts->gpiod_पूर्णांक && ts->gpiod_rst) अणु
			ts->reset_controller_at_probe = true;
			ts->load_cfg_from_disk = true;
			ts->irq_pin_access_method = IRQ_PIN_ACCESS_GPIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * goodix_पढ़ो_config - Read the embedded configuration of the panel
 *
 * @ts: our goodix_ts_data poपूर्णांकer
 *
 * Must be called during probe
 */
अटल व्योम goodix_पढ़ो_config(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक x_max, y_max;
	पूर्णांक error;

	error = goodix_i2c_पढ़ो(ts->client, ts->chip->config_addr,
				ts->config, ts->chip->config_len);
	अगर (error) अणु
		dev_warn(&ts->client->dev, "Error reading config: %d\n",
			 error);
		ts->पूर्णांक_trigger_type = GOODIX_INT_TRIGGER;
		ts->max_touch_num = GOODIX_MAX_CONTACTS;
		वापस;
	पूर्ण

	ts->पूर्णांक_trigger_type = ts->config[TRIGGER_LOC] & 0x03;
	ts->max_touch_num = ts->config[MAX_CONTACTS_LOC] & 0x0f;

	x_max = get_unaligned_le16(&ts->config[RESOLUTION_LOC]);
	y_max = get_unaligned_le16(&ts->config[RESOLUTION_LOC + 2]);
	अगर (x_max && y_max) अणु
		input_असल_set_max(ts->input_dev, ABS_MT_POSITION_X, x_max - 1);
		input_असल_set_max(ts->input_dev, ABS_MT_POSITION_Y, y_max - 1);
	पूर्ण

	ts->chip->calc_config_checksum(ts);
पूर्ण

/**
 * goodix_पढ़ो_version - Read goodix touchscreen version
 *
 * @ts: our goodix_ts_data poपूर्णांकer
 */
अटल पूर्णांक goodix_पढ़ो_version(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक error;
	u8 buf[6];
	अक्षर id_str[GOODIX_ID_MAX_LEN + 1];

	error = goodix_i2c_पढ़ो(ts->client, GOODIX_REG_ID, buf, माप(buf));
	अगर (error) अणु
		dev_err(&ts->client->dev, "read version failed: %d\n", error);
		वापस error;
	पूर्ण

	स_नकल(id_str, buf, GOODIX_ID_MAX_LEN);
	id_str[GOODIX_ID_MAX_LEN] = 0;
	strscpy(ts->id, id_str, GOODIX_ID_MAX_LEN + 1);

	ts->version = get_unaligned_le16(&buf[4]);

	dev_info(&ts->client->dev, "ID %s, version: %04x\n", ts->id,
		 ts->version);

	वापस 0;
पूर्ण

/**
 * goodix_i2c_test - I2C test function to check अगर the device answers.
 *
 * @client: the i2c client
 */
अटल पूर्णांक goodix_i2c_test(काष्ठा i2c_client *client)
अणु
	पूर्णांक retry = 0;
	पूर्णांक error;
	u8 test;

	जबतक (retry++ < 2) अणु
		error = goodix_i2c_पढ़ो(client, GOODIX_REG_ID,
					&test, 1);
		अगर (!error)
			वापस 0;

		dev_err(&client->dev, "i2c test failed attempt %d: %d\n",
			retry, error);
		msleep(20);
	पूर्ण

	वापस error;
पूर्ण

/**
 * goodix_configure_dev - Finish device initialization
 *
 * @ts: our goodix_ts_data poपूर्णांकer
 *
 * Must be called from probe to finish initialization of the device.
 * Contains the common initialization code क्रम both devices that
 * declare gpio pins and devices that करो not. It is either called
 * directly from probe or from request_firmware_रुको callback.
 */
अटल पूर्णांक goodix_configure_dev(काष्ठा goodix_ts_data *ts)
अणु
	पूर्णांक error;
	पूर्णांक i;

	ts->पूर्णांक_trigger_type = GOODIX_INT_TRIGGER;
	ts->max_touch_num = GOODIX_MAX_CONTACTS;

	ts->input_dev = devm_input_allocate_device(&ts->client->dev);
	अगर (!ts->input_dev) अणु
		dev_err(&ts->client->dev, "Failed to allocate input device.");
		वापस -ENOMEM;
	पूर्ण

	ts->input_dev->name = "Goodix Capacitive TouchScreen";
	ts->input_dev->phys = "input/ts";
	ts->input_dev->id.bustype = BUS_I2C;
	ts->input_dev->id.venकरोr = 0x0416;
	अगर (kstrtou16(ts->id, 10, &ts->input_dev->id.product))
		ts->input_dev->id.product = 0x1001;
	ts->input_dev->id.version = ts->version;

	ts->input_dev->keycode = ts->keymap;
	ts->input_dev->keycodesize = माप(ts->keymap[0]);
	ts->input_dev->keycodemax = GOODIX_MAX_KEYS;

	/* Capacitive Winकरोws/Home button on some devices */
	क्रम (i = 0; i < GOODIX_MAX_KEYS; ++i) अणु
		अगर (i == 0)
			ts->keymap[i] = KEY_LEFTMETA;
		अन्यथा
			ts->keymap[i] = KEY_F1 + (i - 1);

		input_set_capability(ts->input_dev, EV_KEY, ts->keymap[i]);
	पूर्ण

	input_set_capability(ts->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(ts->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_असल_params(ts->input_dev, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);

	/* Read configuration and apply touchscreen parameters */
	goodix_पढ़ो_config(ts);

	/* Try overriding touchscreen parameters via device properties */
	touchscreen_parse_properties(ts->input_dev, true, &ts->prop);

	अगर (!ts->prop.max_x || !ts->prop.max_y || !ts->max_touch_num) अणु
		dev_err(&ts->client->dev,
			"Invalid config (%d, %d, %d), using defaults\n",
			ts->prop.max_x, ts->prop.max_y, ts->max_touch_num);
		ts->prop.max_x = GOODIX_MAX_WIDTH - 1;
		ts->prop.max_y = GOODIX_MAX_HEIGHT - 1;
		ts->max_touch_num = GOODIX_MAX_CONTACTS;
		input_असल_set_max(ts->input_dev,
				  ABS_MT_POSITION_X, ts->prop.max_x);
		input_असल_set_max(ts->input_dev,
				  ABS_MT_POSITION_Y, ts->prop.max_y);
	पूर्ण

	अगर (dmi_check_प्रणाली(rotated_screen)) अणु
		ts->prop.invert_x = true;
		ts->prop.invert_y = true;
		dev_dbg(&ts->client->dev,
			"Applying '180 degrees rotated screen' quirk\n");
	पूर्ण

	अगर (dmi_check_प्रणाली(nine_bytes_report)) अणु
		ts->contact_size = 9;

		dev_dbg(&ts->client->dev,
			"Non-standard 9-bytes report format quirk\n");
	पूर्ण

	अगर (dmi_check_प्रणाली(inverted_x_screen)) अणु
		ts->prop.invert_x = true;
		dev_dbg(&ts->client->dev,
			"Applying 'inverted x screen' quirk\n");
	पूर्ण

	error = input_mt_init_slots(ts->input_dev, ts->max_touch_num,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"Failed to initialize MT slots: %d", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ts->input_dev);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"Failed to register input device: %d", error);
		वापस error;
	पूर्ण

	ts->irq_flags = goodix_irq_flags[ts->पूर्णांक_trigger_type] | IRQF_ONESHOT;
	error = goodix_request_irq(ts);
	अगर (error) अणु
		dev_err(&ts->client->dev, "request IRQ failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * goodix_config_cb - Callback to finish device init
 *
 * @cfg: firmware config
 * @ctx: our goodix_ts_data poपूर्णांकer
 *
 * request_firmware_रुको callback that finishes
 * initialization of the device.
 */
अटल व्योम goodix_config_cb(स्थिर काष्ठा firmware *cfg, व्योम *ctx)
अणु
	काष्ठा goodix_ts_data *ts = ctx;
	पूर्णांक error;

	अगर (cfg) अणु
		/* send device configuration to the firmware */
		error = goodix_send_cfg(ts, cfg->data, cfg->size);
		अगर (error)
			जाओ err_release_cfg;
	पूर्ण

	goodix_configure_dev(ts);

err_release_cfg:
	release_firmware(cfg);
	complete_all(&ts->firmware_loading_complete);
पूर्ण

अटल व्योम goodix_disable_regulators(व्योम *arg)
अणु
	काष्ठा goodix_ts_data *ts = arg;

	regulator_disable(ts->vddio);
	regulator_disable(ts->avdd28);
पूर्ण

अटल पूर्णांक goodix_ts_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा goodix_ts_data *ts;
	पूर्णांक error;

	dev_dbg(&client->dev, "I2C Address: 0x%02x\n", client->addr);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "I2C check functionality failed.\n");
		वापस -ENXIO;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;
	i2c_set_clientdata(client, ts);
	init_completion(&ts->firmware_loading_complete);
	ts->contact_size = GOODIX_CONTACT_SIZE;

	error = goodix_get_gpio_config(ts);
	अगर (error)
		वापस error;

	/* घातer up the controller */
	error = regulator_enable(ts->avdd28);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to enable AVDD28 regulator: %d\n",
			error);
		वापस error;
	पूर्ण

	error = regulator_enable(ts->vddio);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to enable VDDIO regulator: %d\n",
			error);
		regulator_disable(ts->avdd28);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev,
					 goodix_disable_regulators, ts);
	अगर (error)
		वापस error;

reset:
	अगर (ts->reset_controller_at_probe) अणु
		/* reset the controller */
		error = goodix_reset(ts);
		अगर (error) अणु
			dev_err(&client->dev, "Controller reset failed.\n");
			वापस error;
		पूर्ण
	पूर्ण

	error = goodix_i2c_test(client);
	अगर (error) अणु
		अगर (!ts->reset_controller_at_probe &&
		    ts->irq_pin_access_method != IRQ_PIN_ACCESS_NONE) अणु
			/* Retry after a controller reset */
			ts->reset_controller_at_probe = true;
			जाओ reset;
		पूर्ण
		dev_err(&client->dev, "I2C communication failure: %d\n", error);
		वापस error;
	पूर्ण

	error = goodix_पढ़ो_version(ts);
	अगर (error) अणु
		dev_err(&client->dev, "Read version failed.\n");
		वापस error;
	पूर्ण

	ts->chip = goodix_get_chip_data(ts->id);

	अगर (ts->load_cfg_from_disk) अणु
		/* update device config */
		ts->cfg_name = devm_kaप्र_लिखो(&client->dev, GFP_KERNEL,
					      "goodix_%s_cfg.bin", ts->id);
		अगर (!ts->cfg_name)
			वापस -ENOMEM;

		error = request_firmware_noरुको(THIS_MODULE, true, ts->cfg_name,
						&client->dev, GFP_KERNEL, ts,
						goodix_config_cb);
		अगर (error) अणु
			dev_err(&client->dev,
				"Failed to invoke firmware loader: %d\n",
				error);
			वापस error;
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अणु
		error = goodix_configure_dev(ts);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक goodix_ts_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा goodix_ts_data *ts = i2c_get_clientdata(client);

	अगर (ts->load_cfg_from_disk)
		रुको_क्रम_completion(&ts->firmware_loading_complete);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused goodix_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा goodix_ts_data *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	अगर (ts->load_cfg_from_disk)
		रुको_क्रम_completion(&ts->firmware_loading_complete);

	/* We need gpio pins to suspend/resume */
	अगर (ts->irq_pin_access_method == IRQ_PIN_ACCESS_NONE) अणु
		disable_irq(client->irq);
		वापस 0;
	पूर्ण

	/* Free IRQ as IRQ pin is used as output in the suspend sequence */
	goodix_मुक्त_irq(ts);

	/* Output LOW on the INT pin क्रम 5 ms */
	error = goodix_irq_direction_output(ts, 0);
	अगर (error) अणु
		goodix_request_irq(ts);
		वापस error;
	पूर्ण

	usleep_range(5000, 6000);

	error = goodix_i2c_ग_लिखो_u8(ts->client, GOODIX_REG_COMMAND,
				    GOODIX_CMD_SCREEN_OFF);
	अगर (error) अणु
		dev_err(&ts->client->dev, "Screen off command failed\n");
		goodix_irq_direction_input(ts);
		goodix_request_irq(ts);
		वापस -EAGAIN;
	पूर्ण

	/*
	 * The datasheet specअगरies that the पूर्णांकerval between sending screen-off
	 * command and wake-up should be दीर्घer than 58 ms. To aव्योम waking up
	 * sooner, delay 58ms here.
	 */
	msleep(58);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused goodix_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा goodix_ts_data *ts = i2c_get_clientdata(client);
	u8 config_ver;
	पूर्णांक error;

	अगर (ts->irq_pin_access_method == IRQ_PIN_ACCESS_NONE) अणु
		enable_irq(client->irq);
		वापस 0;
	पूर्ण

	/*
	 * Exit sleep mode by outputting HIGH level to INT pin
	 * क्रम 2ms~5ms.
	 */
	error = goodix_irq_direction_output(ts, 1);
	अगर (error)
		वापस error;

	usleep_range(2000, 5000);

	error = goodix_पूर्णांक_sync(ts);
	अगर (error)
		वापस error;

	error = goodix_i2c_पढ़ो(ts->client, ts->chip->config_addr,
				&config_ver, 1);
	अगर (error)
		dev_warn(dev, "Error reading config version: %d, resetting controller\n",
			 error);
	अन्यथा अगर (config_ver != ts->config[0])
		dev_info(dev, "Config version mismatch %d != %d, resetting controller\n",
			 config_ver, ts->config[0]);

	अगर (error != 0 || config_ver != ts->config[0]) अणु
		error = goodix_reset(ts);
		अगर (error) अणु
			dev_err(dev, "Controller reset failed.\n");
			वापस error;
		पूर्ण

		error = goodix_send_cfg(ts, ts->config, ts->chip->config_len);
		अगर (error)
			वापस error;
	पूर्ण

	error = goodix_request_irq(ts);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(goodix_pm_ops, goodix_suspend, goodix_resume);

अटल स्थिर काष्ठा i2c_device_id goodix_ts_id[] = अणु
	अणु "GDIX1001:00", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, goodix_ts_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id goodix_acpi_match[] = अणु
	अणु "GDIX1001", 0 पूर्ण,
	अणु "GDIX1002", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, goodix_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id goodix_of_match[] = अणु
	अणु .compatible = "goodix,gt1151" पूर्ण,
	अणु .compatible = "goodix,gt5663" पूर्ण,
	अणु .compatible = "goodix,gt5688" पूर्ण,
	अणु .compatible = "goodix,gt911" पूर्ण,
	अणु .compatible = "goodix,gt9110" पूर्ण,
	अणु .compatible = "goodix,gt912" पूर्ण,
	अणु .compatible = "goodix,gt9147" पूर्ण,
	अणु .compatible = "goodix,gt917s" पूर्ण,
	अणु .compatible = "goodix,gt927" पूर्ण,
	अणु .compatible = "goodix,gt9271" पूर्ण,
	अणु .compatible = "goodix,gt928" पूर्ण,
	अणु .compatible = "goodix,gt9286" पूर्ण,
	अणु .compatible = "goodix,gt967" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, goodix_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver goodix_ts_driver = अणु
	.probe = goodix_ts_probe,
	.हटाओ = goodix_ts_हटाओ,
	.id_table = goodix_ts_id,
	.driver = अणु
		.name = "Goodix-TS",
		.acpi_match_table = ACPI_PTR(goodix_acpi_match),
		.of_match_table = of_match_ptr(goodix_of_match),
		.pm = &goodix_pm_ops,
	पूर्ण,
पूर्ण;
module_i2c_driver(goodix_ts_driver);

MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_AUTHOR("Bastien Nocera <hadess@hadess.net>");
MODULE_DESCRIPTION("Goodix touchscreen driver");
MODULE_LICENSE("GPL v2");
