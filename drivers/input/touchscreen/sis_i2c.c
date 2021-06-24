<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Touch Screen driver क्रम SiS 9200 family I2C Touch panels
 *
 * Copyright (C) 2015 SiS, Inc.
 * Copyright (C) 2016 Nextfour Group
 */

#समावेश <linux/crc-itu-t.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा SIS_I2C_NAME		"sis_i2c_ts"

/*
 * The I2C packet क्रमmat:
 * le16		byte count
 * u8		Report ID
 * <contact data - variable length>
 * u8		Number of contacts
 * le16		Scan Time (optional)
 * le16		CRC
 *
 * One touch poपूर्णांक inक्रमmation consists of 6+ bytes, the order is:
 * u8		contact state
 * u8		finger id
 * le16		x axis
 * le16		y axis
 * u8		contact width (optional)
 * u8		contact height (optional)
 * u8		pressure (optional)
 *
 * Maximum amount of data transmitted in one shot is 64 bytes, अगर controller
 * needs to report more contacts than fit in one packet it will send true
 * number of contacts in first packet and 0 as number of contacts in second
 * packet.
 */

#घोषणा SIS_MAX_PACKET_SIZE		64

#घोषणा SIS_PKT_LEN_OFFSET		0
#घोषणा SIS_PKT_REPORT_OFFSET		2 /* Report ID/type */
#घोषणा SIS_PKT_CONTACT_OFFSET		3 /* First contact */

#घोषणा SIS_SCAN_TIME_LEN		2

/* Supported report types */
#घोषणा SIS_ALL_IN_ONE_PACKAGE		0x10
#घोषणा SIS_PKT_IS_TOUCH(x)		(((x) & 0x0f) == 0x01)
#घोषणा SIS_PKT_IS_HIDI2C(x)		(((x) & 0x0f) == 0x06)

/* Contact properties within report */
#घोषणा SIS_PKT_HAS_AREA(x)		((x) & BIT(4))
#घोषणा SIS_PKT_HAS_PRESSURE(x)		((x) & BIT(5))
#घोषणा SIS_PKT_HAS_SCANTIME(x)		((x) & BIT(6))

/* Contact size */
#घोषणा SIS_BASE_LEN_PER_CONTACT	6
#घोषणा SIS_AREA_LEN_PER_CONTACT	2
#घोषणा SIS_PRESSURE_LEN_PER_CONTACT	1

/* Offsets within contact data */
#घोषणा SIS_CONTACT_STATUS_OFFSET	0
#घोषणा SIS_CONTACT_ID_OFFSET		1 /* Contact ID */
#घोषणा SIS_CONTACT_X_OFFSET		2
#घोषणा SIS_CONTACT_Y_OFFSET		4
#घोषणा SIS_CONTACT_WIDTH_OFFSET	6
#घोषणा SIS_CONTACT_HEIGHT_OFFSET	7
#घोषणा SIS_CONTACT_PRESSURE_OFFSET(id)	(SIS_PKT_HAS_AREA(id) ? 8 : 6)

/* Inभागidual contact state */
#घोषणा SIS_STATUS_UP			0x0
#घोषणा SIS_STATUS_DOWN			0x3

/* Touchscreen parameters */
#घोषणा SIS_MAX_FINGERS			10
#घोषणा SIS_MAX_X			4095
#घोषणा SIS_MAX_Y			4095
#घोषणा SIS_MAX_PRESSURE		255

/* Resolution diagonal */
#घोषणा SIS_AREA_LENGTH_LONGER		5792
/*((SIS_MAX_X^2) + (SIS_MAX_Y^2))^0.5*/
#घोषणा SIS_AREA_LENGTH_SHORT		5792
#घोषणा SIS_AREA_UNIT			(5792 / 32)

काष्ठा sis_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;

	काष्ठा gpio_desc *attn_gpio;
	काष्ठा gpio_desc *reset_gpio;

	u8 packet[SIS_MAX_PACKET_SIZE];
पूर्ण;

अटल पूर्णांक sis_पढ़ो_packet(काष्ठा i2c_client *client, u8 *buf,
			   अचिन्हित पूर्णांक *num_contacts,
			   अचिन्हित पूर्णांक *contact_size)
अणु
	पूर्णांक count_idx;
	पूर्णांक ret;
	u16 len;
	u16 crc, pkg_crc;
	u8 report_id;

	ret = i2c_master_recv(client, buf, SIS_MAX_PACKET_SIZE);
	अगर (ret <= 0)
		वापस -EIO;

	len = get_unaligned_le16(&buf[SIS_PKT_LEN_OFFSET]);
	अगर (len > SIS_MAX_PACKET_SIZE) अणु
		dev_err(&client->dev,
			"%s: invalid packet length (%d vs %d)\n",
			__func__, len, SIS_MAX_PACKET_SIZE);
		वापस -E2BIG;
	पूर्ण

	अगर (len < 10)
		वापस -EINVAL;

	report_id = buf[SIS_PKT_REPORT_OFFSET];
	count_idx  = len - 1;
	*contact_size = SIS_BASE_LEN_PER_CONTACT;

	अगर (report_id != SIS_ALL_IN_ONE_PACKAGE) अणु
		अगर (SIS_PKT_IS_TOUCH(report_id)) अणु
			/*
			 * Calculate CRC ignoring packet length
			 * in the beginning and CRC transmitted
			 * at the end of the packet.
			 */
			crc = crc_itu_t(0, buf + 2, len - 2 - 2);
			pkg_crc = get_unaligned_le16(&buf[len - 2]);

			अगर (crc != pkg_crc) अणु
				dev_err(&client->dev,
					"%s: CRC Error (%d vs %d)\n",
					__func__, crc, pkg_crc);
				वापस -EINVAL;
			पूर्ण

			count_idx -= 2;

		पूर्ण अन्यथा अगर (!SIS_PKT_IS_HIDI2C(report_id)) अणु
			dev_err(&client->dev,
				"%s: invalid packet ID %#02x\n",
				__func__, report_id);
			वापस -EINVAL;
		पूर्ण

		अगर (SIS_PKT_HAS_SCANTIME(report_id))
			count_idx -= SIS_SCAN_TIME_LEN;

		अगर (SIS_PKT_HAS_AREA(report_id))
			*contact_size += SIS_AREA_LEN_PER_CONTACT;
		अगर (SIS_PKT_HAS_PRESSURE(report_id))
			*contact_size += SIS_PRESSURE_LEN_PER_CONTACT;
	पूर्ण

	*num_contacts = buf[count_idx];
	वापस 0;
पूर्ण

अटल पूर्णांक sis_ts_report_contact(काष्ठा sis_ts_data *ts, स्थिर u8 *data, u8 id)
अणु
	काष्ठा input_dev *input = ts->input;
	पूर्णांक slot;
	u8 status = data[SIS_CONTACT_STATUS_OFFSET];
	u8 pressure;
	u8 height, width;
	u16 x, y;

	अगर (status != SIS_STATUS_DOWN && status != SIS_STATUS_UP) अणु
		dev_err(&ts->client->dev, "Unexpected touch status: %#02x\n",
			data[SIS_CONTACT_STATUS_OFFSET]);
		वापस -EINVAL;
	पूर्ण

	slot = input_mt_get_slot_by_key(input, data[SIS_CONTACT_ID_OFFSET]);
	अगर (slot < 0)
		वापस -ENOENT;

	input_mt_slot(input, slot);
	input_mt_report_slot_state(input, MT_TOOL_FINGER,
				   status == SIS_STATUS_DOWN);

	अगर (status == SIS_STATUS_DOWN) अणु
		pressure = height = width = 1;
		अगर (id != SIS_ALL_IN_ONE_PACKAGE) अणु
			अगर (SIS_PKT_HAS_AREA(id)) अणु
				width = data[SIS_CONTACT_WIDTH_OFFSET];
				height = data[SIS_CONTACT_HEIGHT_OFFSET];
			पूर्ण

			अगर (SIS_PKT_HAS_PRESSURE(id))
				pressure =
					data[SIS_CONTACT_PRESSURE_OFFSET(id)];
		पूर्ण

		x = get_unaligned_le16(&data[SIS_CONTACT_X_OFFSET]);
		y = get_unaligned_le16(&data[SIS_CONTACT_Y_OFFSET]);

		input_report_असल(input, ABS_MT_TOUCH_MAJOR,
				 width * SIS_AREA_UNIT);
		input_report_असल(input, ABS_MT_TOUCH_MINOR,
				 height * SIS_AREA_UNIT);
		input_report_असल(input, ABS_MT_PRESSURE, pressure);
		input_report_असल(input, ABS_MT_POSITION_X, x);
		input_report_असल(input, ABS_MT_POSITION_Y, y);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sis_ts_handle_packet(काष्ठा sis_ts_data *ts)
अणु
	स्थिर u8 *contact;
	अचिन्हित पूर्णांक num_to_report = 0;
	अचिन्हित पूर्णांक num_contacts;
	अचिन्हित पूर्णांक num_reported;
	अचिन्हित पूर्णांक contact_size;
	पूर्णांक error;
	u8 report_id;

	करो अणु
		error = sis_पढ़ो_packet(ts->client, ts->packet,
					&num_contacts, &contact_size);
		अगर (error)
			अवरोध;

		अगर (num_to_report == 0) अणु
			num_to_report = num_contacts;
		पूर्ण अन्यथा अगर (num_contacts != 0) अणु
			dev_err(&ts->client->dev,
				"%s: nonzero (%d) point count in tail packet\n",
				__func__, num_contacts);
			अवरोध;
		पूर्ण

		report_id = ts->packet[SIS_PKT_REPORT_OFFSET];
		contact = &ts->packet[SIS_PKT_CONTACT_OFFSET];
		num_reported = 0;

		जबतक (num_to_report > 0) अणु
			error = sis_ts_report_contact(ts, contact, report_id);
			अगर (error)
				अवरोध;

			contact += contact_size;
			num_to_report--;
			num_reported++;

			अगर (report_id != SIS_ALL_IN_ONE_PACKAGE &&
			    num_reported >= 5) अणु
				/*
				 * The reमुख्यder of contacts is sent
				 * in the 2nd packet.
				 */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (num_to_report > 0);

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
पूर्ण

अटल irqवापस_t sis_ts_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sis_ts_data *ts = dev_id;

	करो अणु
		sis_ts_handle_packet(ts);
	पूर्ण जबतक (ts->attn_gpio && gpiod_get_value_cansleep(ts->attn_gpio));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sis_ts_reset(काष्ठा sis_ts_data *ts)
अणु
	अगर (ts->reset_gpio) अणु
		/* Get out of reset */
		usleep_range(1000, 2000);
		gpiod_set_value(ts->reset_gpio, 1);
		usleep_range(1000, 2000);
		gpiod_set_value(ts->reset_gpio, 0);
		msleep(100);
	पूर्ण
पूर्ण

अटल पूर्णांक sis_ts_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sis_ts_data *ts;
	काष्ठा input_dev *input;
	पूर्णांक error;

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;

	ts->attn_gpio = devm_gpiod_get_optional(&client->dev,
						"attn", GPIOD_IN);
	अगर (IS_ERR(ts->attn_gpio)) अणु
		error = PTR_ERR(ts->attn_gpio);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get attention GPIO: %d\n", error);
		वापस error;
	पूर्ण

	ts->reset_gpio = devm_gpiod_get_optional(&client->dev,
						 "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ts->reset_gpio)) अणु
		error = PTR_ERR(ts->reset_gpio);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"Failed to get reset GPIO: %d\n", error);
		वापस error;
	पूर्ण

	sis_ts_reset(ts);

	ts->input = input = devm_input_allocate_device(&client->dev);
	अगर (!input) अणु
		dev_err(&client->dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = "SiS Touchscreen";
	input->id.bustype = BUS_I2C;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0, SIS_MAX_X, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0, SIS_MAX_Y, 0, 0);
	input_set_असल_params(input, ABS_MT_PRESSURE, 0, SIS_MAX_PRESSURE, 0, 0);
	input_set_असल_params(input, ABS_MT_TOUCH_MAJOR,
			     0, SIS_AREA_LENGTH_LONGER, 0, 0);
	input_set_असल_params(input, ABS_MT_TOUCH_MINOR,
			     0, SIS_AREA_LENGTH_SHORT, 0, 0);

	error = input_mt_init_slots(input, SIS_MAX_FINGERS, INPUT_MT_सूचीECT);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to initialize MT slots: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, sis_ts_irq_handler,
					  IRQF_ONESHOT,
					  client->name, ts);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(ts->input);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sis_ts_dt_ids[] = अणु
	अणु .compatible = "sis,9200-ts" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sis_ts_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id sis_ts_id[] = अणु
	अणु SIS_I2C_NAME,	0 पूर्ण,
	अणु "9200-ts",	0 पूर्ण,
	अणु /* sentinel */  पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sis_ts_id);

अटल काष्ठा i2c_driver sis_ts_driver = अणु
	.driver = अणु
		.name	= SIS_I2C_NAME,
		.of_match_table = of_match_ptr(sis_ts_dt_ids),
	पूर्ण,
	.probe		= sis_ts_probe,
	.id_table	= sis_ts_id,
पूर्ण;
module_i2c_driver(sis_ts_driver);

MODULE_DESCRIPTION("SiS 9200 Family Touchscreen Driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Mika Penttilथअ <mika.penttila@nextfour.com>");
