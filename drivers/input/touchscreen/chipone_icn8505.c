<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम ChipOne icn8505 i2c touchscreen controller
 *
 * Copyright (c) 2015-2018 Red Hat Inc.
 *
 * Red Hat authors:
 * Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/acpi.h>
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/module.h>

/* Normal operation mode defines */
#घोषणा ICN8505_REG_ADDR_WIDTH		16

#घोषणा ICN8505_REG_POWER		0x0004
#घोषणा ICN8505_REG_TOUCHDATA		0x1000
#घोषणा ICN8505_REG_CONFIGDATA		0x8000

/* ICN8505_REG_POWER commands */
#घोषणा ICN8505_POWER_ACTIVE		0x00
#घोषणा ICN8505_POWER_MONITOR		0x01
#घोषणा ICN8505_POWER_HIBERNATE		0x02
/*
 * The Android driver uses these to turn on/off the अक्षरger filter, but the
 * filter is way too aggressive making e.g. onscreen keyboards unusable.
 */
#घोषणा ICN8505_POWER_ENA_CHARGER_MODE	0x55
#घोषणा ICN8505_POWER_DIS_CHARGER_MODE	0x66

#घोषणा ICN8505_MAX_TOUCHES		10

/* Programming mode defines */
#घोषणा ICN8505_PROG_I2C_ADDR		0x30
#घोषणा ICN8505_PROG_REG_ADDR_WIDTH	24

#घोषणा MAX_FW_UPLOAD_TRIES		3

काष्ठा icn8505_touch अणु
	u8 slot;
	u8 x[2];
	u8 y[2];
	u8 pressure;	/* Seems more like finger width then pressure really */
	u8 event;
/* The dअगरference between 2 and 3 is unclear */
#घोषणा ICN8505_EVENT_NO_DATA	1 /* No finger seen yet since wakeup */
#घोषणा ICN8505_EVENT_UPDATE1	2 /* New or updated coordinates */
#घोषणा ICN8505_EVENT_UPDATE2	3 /* New or updated coordinates */
#घोषणा ICN8505_EVENT_END	4 /* Finger lअगरted */
पूर्ण __packed;

काष्ठा icn8505_touch_data अणु
	u8 softbutton;
	u8 touch_count;
	काष्ठा icn8505_touch touches[ICN8505_MAX_TOUCHES];
पूर्ण __packed;

काष्ठा icn8505_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	काष्ठा gpio_desc *wake_gpio;
	काष्ठा touchscreen_properties prop;
	अक्षर firmware_name[32];
पूर्ण;

अटल पूर्णांक icn8505_पढ़ो_xfer(काष्ठा i2c_client *client, u16 i2c_addr,
			     पूर्णांक reg_addr, पूर्णांक reg_addr_width,
			     व्योम *data, पूर्णांक len, bool silent)
अणु
	u8 buf[3];
	पूर्णांक i, ret;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = i2c_addr,
			.buf = buf,
			.len = reg_addr_width / 8,
		पूर्ण,
		अणु
			.addr = i2c_addr,
			.flags = I2C_M_RD,
			.buf = data,
			.len = len,
		पूर्ण
	पूर्ण;

	क्रम (i = 0; i < (reg_addr_width / 8); i++)
		buf[i] = (reg_addr >> (reg_addr_width - (i + 1) * 8)) & 0xff;

	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret != ARRAY_SIZE(msg)) अणु
		अगर (ret >= 0)
			ret = -EIO;
		अगर (!silent)
			dev_err(&client->dev,
				"Error reading addr %#x reg %#x: %d\n",
				i2c_addr, reg_addr, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icn8505_ग_लिखो_xfer(काष्ठा i2c_client *client, u16 i2c_addr,
			      पूर्णांक reg_addr, पूर्णांक reg_addr_width,
			      स्थिर व्योम *data, पूर्णांक len, bool silent)
अणु
	u8 buf[3 + 32]; /* 3 bytes क्रम 24 bit reg-addr + 32 bytes max len */
	पूर्णांक i, ret;
	काष्ठा i2c_msg msg = अणु
		.addr = i2c_addr,
		.buf = buf,
		.len = reg_addr_width / 8 + len,
	पूर्ण;

	अगर (WARN_ON(len > 32))
		वापस -EINVAL;

	क्रम (i = 0; i < (reg_addr_width / 8); i++)
		buf[i] = (reg_addr >> (reg_addr_width - (i + 1) * 8)) & 0xff;

	स_नकल(buf + reg_addr_width / 8, data, len);

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		अगर (ret >= 0)
			ret = -EIO;
		अगर (!silent)
			dev_err(&client->dev,
				"Error writing addr %#x reg %#x: %d\n",
				i2c_addr, reg_addr, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icn8505_पढ़ो_data(काष्ठा icn8505_data *icn8505, पूर्णांक reg,
			     व्योम *buf, पूर्णांक len)
अणु
	वापस icn8505_पढ़ो_xfer(icn8505->client, icn8505->client->addr, reg,
				 ICN8505_REG_ADDR_WIDTH, buf, len, false);
पूर्ण

अटल पूर्णांक icn8505_पढ़ो_reg_silent(काष्ठा icn8505_data *icn8505, पूर्णांक reg)
अणु
	u8 buf;
	पूर्णांक error;

	error = icn8505_पढ़ो_xfer(icn8505->client, icn8505->client->addr, reg,
				  ICN8505_REG_ADDR_WIDTH, &buf, 1, true);
	अगर (error)
		वापस error;

	वापस buf;
पूर्ण

अटल पूर्णांक icn8505_ग_लिखो_reg(काष्ठा icn8505_data *icn8505, पूर्णांक reg, u8 val)
अणु
	वापस icn8505_ग_लिखो_xfer(icn8505->client, icn8505->client->addr, reg,
				  ICN8505_REG_ADDR_WIDTH, &val, 1, false);
पूर्ण

अटल पूर्णांक icn8505_पढ़ो_prog_data(काष्ठा icn8505_data *icn8505, पूर्णांक reg,
				  व्योम *buf, पूर्णांक len)
अणु
	वापस icn8505_पढ़ो_xfer(icn8505->client, ICN8505_PROG_I2C_ADDR, reg,
				 ICN8505_PROG_REG_ADDR_WIDTH, buf, len, false);
पूर्ण

अटल पूर्णांक icn8505_ग_लिखो_prog_data(काष्ठा icn8505_data *icn8505, पूर्णांक reg,
				   स्थिर व्योम *buf, पूर्णांक len)
अणु
	वापस icn8505_ग_लिखो_xfer(icn8505->client, ICN8505_PROG_I2C_ADDR, reg,
				  ICN8505_PROG_REG_ADDR_WIDTH, buf, len, false);
पूर्ण

अटल पूर्णांक icn8505_ग_लिखो_prog_reg(काष्ठा icn8505_data *icn8505, पूर्णांक reg, u8 val)
अणु
	वापस icn8505_ग_लिखो_xfer(icn8505->client, ICN8505_PROG_I2C_ADDR, reg,
				  ICN8505_PROG_REG_ADDR_WIDTH, &val, 1, false);
पूर्ण

/*
 * Note this function uses a number of magic रेजिस्टर addresses and values,
 * there are deliberately no defines क्रम these because the algorithm is taken
 * from the icn85xx Android driver and I करो not want to make up possibly wrong
 * names क्रम the addresses and/or values.
 */
अटल पूर्णांक icn8505_try_fw_upload(काष्ठा icn8505_data *icn8505,
				 स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &icn8505->client->dev;
	माप_प्रकार offset, count;
	पूर्णांक error;
	u8 buf[4];
	u32 crc;

	/* Put the controller in programming mode */
	error = icn8505_ग_लिखो_prog_reg(icn8505, 0xcc3355, 0x5a);
	अगर (error)
		वापस error;

	usleep_range(2000, 5000);

	error = icn8505_ग_लिखो_prog_reg(icn8505, 0x040400, 0x01);
	अगर (error)
		वापस error;

	usleep_range(2000, 5000);

	error = icn8505_पढ़ो_prog_data(icn8505, 0x040002, buf, 1);
	अगर (error)
		वापस error;

	अगर (buf[0] != 0x85) अणु
		dev_err(dev, "Failed to enter programming mode\n");
		वापस -ENODEV;
	पूर्ण

	usleep_range(1000, 5000);

	/* Enable CRC mode */
	error = icn8505_ग_लिखो_prog_reg(icn8505, 0x40028, 1);
	अगर (error)
		वापस error;

	/* Send the firmware to SRAM */
	क्रम (offset = 0; offset < fw->size; offset += count) अणु
		count = min_t(माप_प्रकार, fw->size - offset, 32);
		error = icn8505_ग_लिखो_prog_data(icn8505, offset,
					      fw->data + offset, count);
		अगर (error)
			वापस error;
	पूर्ण

	/* Disable CRC mode */
	error = icn8505_ग_लिखो_prog_reg(icn8505, 0x40028, 0);
	अगर (error)
		वापस error;

	/* Get and check length and CRC */
	error = icn8505_पढ़ो_prog_data(icn8505, 0x40034, buf, 2);
	अगर (error)
		वापस error;

	अगर (get_unaligned_le16(buf) != fw->size) अणु
		dev_warn(dev, "Length mismatch after uploading fw\n");
		वापस -EIO;
	पूर्ण

	error = icn8505_पढ़ो_prog_data(icn8505, 0x4002c, buf, 4);
	अगर (error)
		वापस error;

	crc = crc32_be(0, fw->data, fw->size);
	अगर (get_unaligned_le32(buf) != crc) अणु
		dev_warn(dev, "CRC mismatch after uploading fw\n");
		वापस -EIO;
	पूर्ण

	/* Boot controller from SRAM */
	error = icn8505_ग_लिखो_prog_reg(icn8505, 0x40400, 0x03);
	अगर (error)
		वापस error;

	usleep_range(2000, 5000);
	वापस 0;
पूर्ण

अटल पूर्णांक icn8505_upload_fw(काष्ठा icn8505_data *icn8505)
अणु
	काष्ठा device *dev = &icn8505->client->dev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक i, error;

	/*
	 * Always load the firmware, even अगर we करोn't need it at boot, we
	 * we may need it at resume. Having loaded it once will make the
	 * firmware class code cache it at suspend/resume.
	 */
	error = firmware_request_platक्रमm(&fw, icn8505->firmware_name, dev);
	अगर (error) अणु
		dev_err(dev, "Firmware request error %d\n", error);
		वापस error;
	पूर्ण

	/* Check अगर the controller is not alपढ़ोy up and running */
	अगर (icn8505_पढ़ो_reg_silent(icn8505, 0x000a) == 0x85)
		जाओ success;

	क्रम (i = 1; i <= MAX_FW_UPLOAD_TRIES; i++) अणु
		error = icn8505_try_fw_upload(icn8505, fw);
		अगर (!error)
			जाओ success;

		dev_err(dev, "Failed to upload firmware: %d (attempt %d/%d)\n",
			error, i, MAX_FW_UPLOAD_TRIES);
		usleep_range(2000, 5000);
	पूर्ण

success:
	release_firmware(fw);
	वापस error;
पूर्ण

अटल bool icn8505_touch_active(u8 event)
अणु
	वापस event == ICN8505_EVENT_UPDATE1 ||
	       event == ICN8505_EVENT_UPDATE2;
पूर्ण

अटल irqवापस_t icn8505_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा icn8505_data *icn8505 = dev_id;
	काष्ठा device *dev = &icn8505->client->dev;
	काष्ठा icn8505_touch_data touch_data;
	पूर्णांक i, error;

	error = icn8505_पढ़ो_data(icn8505, ICN8505_REG_TOUCHDATA,
				  &touch_data, माप(touch_data));
	अगर (error) अणु
		dev_err(dev, "Error reading touch data: %d\n", error);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (touch_data.touch_count > ICN8505_MAX_TOUCHES) अणु
		dev_warn(dev, "Too many touches %d > %d\n",
			 touch_data.touch_count, ICN8505_MAX_TOUCHES);
		touch_data.touch_count = ICN8505_MAX_TOUCHES;
	पूर्ण

	क्रम (i = 0; i < touch_data.touch_count; i++) अणु
		काष्ठा icn8505_touch *touch = &touch_data.touches[i];
		bool act = icn8505_touch_active(touch->event);

		input_mt_slot(icn8505->input, touch->slot);
		input_mt_report_slot_state(icn8505->input, MT_TOOL_FINGER, act);
		अगर (!act)
			जारी;

		touchscreen_report_pos(icn8505->input, &icn8505->prop,
				       get_unaligned_le16(touch->x),
				       get_unaligned_le16(touch->y),
				       true);
	पूर्ण

	input_mt_sync_frame(icn8505->input);
	input_report_key(icn8505->input, KEY_LEFTMETA,
			 touch_data.softbutton == 1);
	input_sync(icn8505->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक icn8505_probe_acpi(काष्ठा icn8505_data *icn8505, काष्ठा device *dev)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	स्थिर अक्षर *subsys = "unknown";
	काष्ठा acpi_device *adev;
	जोड़ acpi_object *obj;
	acpi_status status;

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस -ENODEV;

	status = acpi_evaluate_object(adev->handle, "_SUB", शून्य, &buffer);
	अगर (ACPI_SUCCESS(status)) अणु
		obj = buffer.poपूर्णांकer;
		अगर (obj->type == ACPI_TYPE_STRING)
			subsys = obj->string.poपूर्णांकer;
		अन्यथा
			dev_warn(dev, "Warning ACPI _SUB did not return a string\n");
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Warning ACPI _SUB failed: %#x\n", status);
		buffer.poपूर्णांकer = शून्य;
	पूर्ण

	snम_लिखो(icn8505->firmware_name, माप(icn8505->firmware_name),
		 "chipone/icn8505-%s.fw", subsys);

	kमुक्त(buffer.poपूर्णांकer);
	वापस 0;
पूर्ण

अटल पूर्णांक icn8505_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा icn8505_data *icn8505;
	काष्ठा input_dev *input;
	__le16 resolution[2];
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(dev, "No irq specified\n");
		वापस -EINVAL;
	पूर्ण

	icn8505 = devm_kzalloc(dev, माप(*icn8505), GFP_KERNEL);
	अगर (!icn8505)
		वापस -ENOMEM;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = client->name;
	input->id.bustype = BUS_I2C;

	input_set_capability(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input, EV_ABS, ABS_MT_POSITION_Y);
	input_set_capability(input, EV_KEY, KEY_LEFTMETA);

	icn8505->client = client;
	icn8505->input = input;
	input_set_drvdata(input, icn8505);

	error = icn8505_probe_acpi(icn8505, dev);
	अगर (error)
		वापस error;

	error = icn8505_upload_fw(icn8505);
	अगर (error)
		वापस error;

	error = icn8505_पढ़ो_data(icn8505, ICN8505_REG_CONFIGDATA,
				resolution, माप(resolution));
	अगर (error) अणु
		dev_err(dev, "Error reading resolution: %d\n", error);
		वापस error;
	पूर्ण

	input_set_असल_params(input, ABS_MT_POSITION_X, 0,
			     le16_to_cpu(resolution[0]) - 1, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0,
			     le16_to_cpu(resolution[1]) - 1, 0, 0);

	touchscreen_parse_properties(input, true, &icn8505->prop);
	अगर (!input_असल_get_max(input, ABS_MT_POSITION_X) ||
	    !input_असल_get_max(input, ABS_MT_POSITION_Y)) अणु
		dev_err(dev, "Error touchscreen-size-x and/or -y missing\n");
		वापस -EINVAL;
	पूर्ण

	error = input_mt_init_slots(input, ICN8505_MAX_TOUCHES,
				  INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य, icn8505_irq,
					IRQF_ONESHOT, client->name, icn8505);
	अगर (error) अणु
		dev_err(dev, "Error requesting irq: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, icn8505);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused icn8505_suspend(काष्ठा device *dev)
अणु
	काष्ठा icn8505_data *icn8505 = i2c_get_clientdata(to_i2c_client(dev));

	disable_irq(icn8505->client->irq);

	icn8505_ग_लिखो_reg(icn8505, ICN8505_REG_POWER, ICN8505_POWER_HIBERNATE);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused icn8505_resume(काष्ठा device *dev)
अणु
	काष्ठा icn8505_data *icn8505 = i2c_get_clientdata(to_i2c_client(dev));
	पूर्णांक error;

	error = icn8505_upload_fw(icn8505);
	अगर (error)
		वापस error;

	enable_irq(icn8505->client->irq);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(icn8505_pm_ops, icn8505_suspend, icn8505_resume);

अटल स्थिर काष्ठा acpi_device_id icn8505_acpi_match[] = अणु
	अणु "CHPN0001" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, icn8505_acpi_match);

अटल काष्ठा i2c_driver icn8505_driver = अणु
	.driver = अणु
		.name	= "chipone_icn8505",
		.pm	= &icn8505_pm_ops,
		.acpi_match_table = icn8505_acpi_match,
	पूर्ण,
	.probe_new = icn8505_probe,
पूर्ण;

module_i2c_driver(icn8505_driver);

MODULE_DESCRIPTION("ChipOne icn8505 I2C Touchscreen Driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
