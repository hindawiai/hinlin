<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -------------------------------------------------------------------------
 * Copyright (C) 2014-2015, Intel Corporation
 *
 * Derived from:
 *  gslX68X.c
 *  Copyright (C) 2010-2015, Shanghai Sileadinc Co.Ltd
 *
 * -------------------------------------------------------------------------
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/irq.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा SILEAD_TS_NAME		"silead_ts"

#घोषणा SILEAD_REG_RESET	0xE0
#घोषणा SILEAD_REG_DATA		0x80
#घोषणा SILEAD_REG_TOUCH_NR	0x80
#घोषणा SILEAD_REG_POWER	0xBC
#घोषणा SILEAD_REG_CLOCK	0xE4
#घोषणा SILEAD_REG_STATUS	0xB0
#घोषणा SILEAD_REG_ID		0xFC
#घोषणा SILEAD_REG_MEM_CHECK	0xB0

#घोषणा SILEAD_STATUS_OK	0x5A5A5A5A
#घोषणा SILEAD_TS_DATA_LEN	44
#घोषणा SILEAD_CLOCK		0x04

#घोषणा SILEAD_CMD_RESET	0x88
#घोषणा SILEAD_CMD_START	0x00

#घोषणा SILEAD_POINT_DATA_LEN	0x04
#घोषणा SILEAD_POINT_Y_OFF      0x00
#घोषणा SILEAD_POINT_Y_MSB_OFF	0x01
#घोषणा SILEAD_POINT_X_OFF	0x02
#घोषणा SILEAD_POINT_X_MSB_OFF	0x03
#घोषणा SILEAD_EXTRA_DATA_MASK	0xF0

#घोषणा SILEAD_CMD_SLEEP_MIN	10000
#घोषणा SILEAD_CMD_SLEEP_MAX	20000
#घोषणा SILEAD_POWER_SLEEP	20
#घोषणा SILEAD_STARTUP_SLEEP	30

#घोषणा SILEAD_MAX_FINGERS	10

क्रमागत silead_ts_घातer अणु
	SILEAD_POWER_ON  = 1,
	SILEAD_POWER_OFF = 0
पूर्ण;

काष्ठा silead_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा gpio_desc *gpio_घातer;
	काष्ठा input_dev *input;
	काष्ठा regulator_bulk_data regulators[2];
	अक्षर fw_name[64];
	काष्ठा touchscreen_properties prop;
	u32 max_fingers;
	u32 chip_id;
	काष्ठा input_mt_pos pos[SILEAD_MAX_FINGERS];
	पूर्णांक slots[SILEAD_MAX_FINGERS];
	पूर्णांक id[SILEAD_MAX_FINGERS];
पूर्ण;

काष्ठा silead_fw_data अणु
	u32 offset;
	u32 val;
पूर्ण;

अटल पूर्णांक silead_ts_request_input_dev(काष्ठा silead_ts_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक error;

	data->input = devm_input_allocate_device(dev);
	अगर (!data->input) अणु
		dev_err(dev,
			"Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_असल_params(data->input, ABS_MT_POSITION_X, 0, 4095, 0, 0);
	input_set_असल_params(data->input, ABS_MT_POSITION_Y, 0, 4095, 0, 0);
	touchscreen_parse_properties(data->input, true, &data->prop);

	input_mt_init_slots(data->input, data->max_fingers,
			    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED |
			    INPUT_MT_TRACK);

	अगर (device_property_पढ़ो_bool(dev, "silead,home-button"))
		input_set_capability(data->input, EV_KEY, KEY_LEFTMETA);

	data->input->name = SILEAD_TS_NAME;
	data->input->phys = "input/ts";
	data->input->id.bustype = BUS_I2C;

	error = input_रेजिस्टर_device(data->input);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम silead_ts_set_घातer(काष्ठा i2c_client *client,
				क्रमागत silead_ts_घातer state)
अणु
	काष्ठा silead_ts_data *data = i2c_get_clientdata(client);

	अगर (data->gpio_घातer) अणु
		gpiod_set_value_cansleep(data->gpio_घातer, state);
		msleep(SILEAD_POWER_SLEEP);
	पूर्ण
पूर्ण

अटल व्योम silead_ts_पढ़ो_data(काष्ठा i2c_client *client)
अणु
	काष्ठा silead_ts_data *data = i2c_get_clientdata(client);
	काष्ठा input_dev *input = data->input;
	काष्ठा device *dev = &client->dev;
	u8 *bufp, buf[SILEAD_TS_DATA_LEN];
	पूर्णांक touch_nr, softbutton, error, i;
	bool softbutton_pressed = false;

	error = i2c_smbus_पढ़ो_i2c_block_data(client, SILEAD_REG_DATA,
					      SILEAD_TS_DATA_LEN, buf);
	अगर (error < 0) अणु
		dev_err(dev, "Data read error %d\n", error);
		वापस;
	पूर्ण

	अगर (buf[0] > data->max_fingers) अणु
		dev_warn(dev, "More touches reported then supported %d > %d\n",
			 buf[0], data->max_fingers);
		buf[0] = data->max_fingers;
	पूर्ण

	touch_nr = 0;
	bufp = buf + SILEAD_POINT_DATA_LEN;
	क्रम (i = 0; i < buf[0]; i++, bufp += SILEAD_POINT_DATA_LEN) अणु
		softbutton = (bufp[SILEAD_POINT_Y_MSB_OFF] &
			      SILEAD_EXTRA_DATA_MASK) >> 4;

		अगर (softbutton) अणु
			/*
			 * For now only respond to softbutton == 0x01, some
			 * tablets *without* a capacative button send 0x04
			 * when crossing the edges of the screen.
			 */
			अगर (softbutton == 0x01)
				softbutton_pressed = true;

			जारी;
		पूर्ण

		/*
		 * Bits 4-7 are the touch id, note not all models have
		 * hardware touch ids so aपंचांग we करोn't use these.
		 */
		data->id[touch_nr] = (bufp[SILEAD_POINT_X_MSB_OFF] &
				      SILEAD_EXTRA_DATA_MASK) >> 4;
		touchscreen_set_mt_pos(&data->pos[touch_nr], &data->prop,
			get_unaligned_le16(&bufp[SILEAD_POINT_X_OFF]) & 0xfff,
			get_unaligned_le16(&bufp[SILEAD_POINT_Y_OFF]) & 0xfff);
		touch_nr++;
	पूर्ण

	input_mt_assign_slots(input, data->slots, data->pos, touch_nr, 0);

	क्रम (i = 0; i < touch_nr; i++) अणु
		input_mt_slot(input, data->slots[i]);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X, data->pos[i].x);
		input_report_असल(input, ABS_MT_POSITION_Y, data->pos[i].y);

		dev_dbg(dev, "x=%d y=%d hw_id=%d sw_id=%d\n", data->pos[i].x,
			data->pos[i].y, data->id[i], data->slots[i]);
	पूर्ण

	input_mt_sync_frame(input);
	input_report_key(input, KEY_LEFTMETA, softbutton_pressed);
	input_sync(input);
पूर्ण

अटल पूर्णांक silead_ts_init(काष्ठा i2c_client *client)
अणु
	काष्ठा silead_ts_data *data = i2c_get_clientdata(client);
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_RESET,
					  SILEAD_CMD_RESET);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_TOUCH_NR,
					data->max_fingers);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_CLOCK,
					  SILEAD_CLOCK);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_RESET,
					  SILEAD_CMD_START);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	वापस 0;

i2c_ग_लिखो_err:
	dev_err(&client->dev, "Registers clear error %d\n", error);
	वापस error;
पूर्ण

अटल पूर्णांक silead_ts_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_RESET,
					  SILEAD_CMD_RESET);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_CLOCK,
					  SILEAD_CLOCK);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_POWER,
					  SILEAD_CMD_START);
	अगर (error)
		जाओ i2c_ग_लिखो_err;
	usleep_range(SILEAD_CMD_SLEEP_MIN, SILEAD_CMD_SLEEP_MAX);

	वापस 0;

i2c_ग_लिखो_err:
	dev_err(&client->dev, "Chip reset error %d\n", error);
	वापस error;
पूर्ण

अटल पूर्णांक silead_ts_startup(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(client, SILEAD_REG_RESET, 0x00);
	अगर (error) अणु
		dev_err(&client->dev, "Startup error %d\n", error);
		वापस error;
	पूर्ण

	msleep(SILEAD_STARTUP_SLEEP);

	वापस 0;
पूर्ण

अटल पूर्णांक silead_ts_load_fw(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा silead_ts_data *data = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक fw_size, i;
	स्थिर काष्ठा firmware *fw;
	काष्ठा silead_fw_data *fw_data;
	पूर्णांक error;

	dev_dbg(dev, "Firmware file name: %s", data->fw_name);

	error = firmware_request_platक्रमm(&fw, data->fw_name, dev);
	अगर (error) अणु
		dev_err(dev, "Firmware request error %d\n", error);
		वापस error;
	पूर्ण

	fw_size = fw->size / माप(*fw_data);
	fw_data = (काष्ठा silead_fw_data *)fw->data;

	क्रम (i = 0; i < fw_size; i++) अणु
		error = i2c_smbus_ग_लिखो_i2c_block_data(client,
						       fw_data[i].offset,
						       4,
						       (u8 *)&fw_data[i].val);
		अगर (error) अणु
			dev_err(dev, "Firmware load error %d\n", error);
			अवरोध;
		पूर्ण
	पूर्ण

	release_firmware(fw);
	वापस error ?: 0;
पूर्ण

अटल u32 silead_ts_get_status(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;
	__le32 status;

	error = i2c_smbus_पढ़ो_i2c_block_data(client, SILEAD_REG_STATUS,
					      माप(status), (u8 *)&status);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Status read error %d\n", error);
		वापस error;
	पूर्ण

	वापस le32_to_cpu(status);
पूर्ण

अटल पूर्णांक silead_ts_get_id(काष्ठा i2c_client *client)
अणु
	काष्ठा silead_ts_data *data = i2c_get_clientdata(client);
	__le32 chip_id;
	पूर्णांक error;

	error = i2c_smbus_पढ़ो_i2c_block_data(client, SILEAD_REG_ID,
					      माप(chip_id), (u8 *)&chip_id);
	अगर (error < 0)
		वापस error;

	data->chip_id = le32_to_cpu(chip_id);
	dev_info(&client->dev, "Silead chip ID: 0x%8X", data->chip_id);

	वापस 0;
पूर्ण

अटल पूर्णांक silead_ts_setup(काष्ठा i2c_client *client)
अणु
	पूर्णांक error;
	u32 status;

	/*
	 * Some buggy BIOS-es bring up the chip in a stuck state where it
	 * blocks the I2C bus. The following steps are necessary to
	 * unstuck the chip / bus:
	 * 1. Turn off the Silead chip.
	 * 2. Try to करो an I2C transfer with the chip, this will fail in
	 *    response to which the I2C-bus-driver will call:
	 *    i2c_recover_bus() which will unstuck the I2C-bus. Note the
	 *    unstuck-ing of the I2C bus only works अगर we first drop the
	 *    chip off the bus by turning it off.
	 * 3. Turn the chip back on.
	 *
	 * On the x86/ACPI प्रणालीs were this problem is seen, step 1. and
	 * 3. require making ACPI calls and dealing with ACPI Power
	 * Resources. The workaround below runसमय-suspends the chip to
	 * turn it off, leaving it up to the ACPI subप्रणाली to deal with
	 * this.
	 */

	अगर (device_property_पढ़ो_bool(&client->dev,
				      "silead,stuck-controller-bug")) अणु
		pm_runसमय_set_active(&client->dev);
		pm_runसमय_enable(&client->dev);
		pm_runसमय_allow(&client->dev);

		pm_runसमय_suspend(&client->dev);

		dev_warn(&client->dev, FW_BUG "Stuck I2C bus: please ignore the next 'controller timed out' error\n");
		silead_ts_get_id(client);

		/* The क्रमbid will also resume the device */
		pm_runसमय_क्रमbid(&client->dev);
		pm_runसमय_disable(&client->dev);
	पूर्ण

	silead_ts_set_घातer(client, SILEAD_POWER_OFF);
	silead_ts_set_घातer(client, SILEAD_POWER_ON);

	error = silead_ts_get_id(client);
	अगर (error) अणु
		dev_err(&client->dev, "Chip ID read error %d\n", error);
		वापस error;
	पूर्ण

	error = silead_ts_init(client);
	अगर (error)
		वापस error;

	error = silead_ts_reset(client);
	अगर (error)
		वापस error;

	error = silead_ts_load_fw(client);
	अगर (error)
		वापस error;

	error = silead_ts_startup(client);
	अगर (error)
		वापस error;

	status = silead_ts_get_status(client);
	अगर (status != SILEAD_STATUS_OK) अणु
		dev_err(&client->dev,
			"Initialization error, status: 0x%X\n", status);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t silead_ts_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा silead_ts_data *data = id;
	काष्ठा i2c_client *client = data->client;

	silead_ts_पढ़ो_data(client);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम silead_ts_पढ़ो_props(काष्ठा i2c_client *client)
अणु
	काष्ठा silead_ts_data *data = i2c_get_clientdata(client);
	काष्ठा device *dev = &client->dev;
	स्थिर अक्षर *str;
	पूर्णांक error;

	error = device_property_पढ़ो_u32(dev, "silead,max-fingers",
					 &data->max_fingers);
	अगर (error) अणु
		dev_dbg(dev, "Max fingers read error %d\n", error);
		data->max_fingers = 5; /* Most devices handle up-to 5 fingers */
	पूर्ण

	error = device_property_पढ़ो_string(dev, "firmware-name", &str);
	अगर (!error)
		snम_लिखो(data->fw_name, माप(data->fw_name),
			 "silead/%s", str);
	अन्यथा
		dev_dbg(dev, "Firmware file name read error. Using default.");
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक silead_ts_set_शेष_fw_name(काष्ठा silead_ts_data *data,
					 स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा acpi_device_id *acpi_id;
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक i;

	अगर (ACPI_HANDLE(dev)) अणु
		acpi_id = acpi_match_device(dev->driver->acpi_match_table, dev);
		अगर (!acpi_id)
			वापस -ENODEV;

		snम_लिखो(data->fw_name, माप(data->fw_name),
			 "silead/%s.fw", acpi_id->id);

		क्रम (i = 0; i < म_माप(data->fw_name); i++)
			data->fw_name[i] = छोटे(data->fw_name[i]);
	पूर्ण अन्यथा अणु
		snम_लिखो(data->fw_name, माप(data->fw_name),
			 "silead/%s.fw", id->name);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक silead_ts_set_शेष_fw_name(काष्ठा silead_ts_data *data,
					 स्थिर काष्ठा i2c_device_id *id)
अणु
	snम_लिखो(data->fw_name, माप(data->fw_name),
		 "silead/%s.fw", id->name);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम silead_disable_regulator(व्योम *arg)
अणु
	काष्ठा silead_ts_data *data = arg;

	regulator_bulk_disable(ARRAY_SIZE(data->regulators), data->regulators);
पूर्ण

अटल पूर्णांक silead_ts_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा silead_ts_data *data;
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK |
				     I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)) अणु
		dev_err(dev, "I2C functionality check failed\n");
		वापस -ENXIO;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;

	error = silead_ts_set_शेष_fw_name(data, id);
	अगर (error)
		वापस error;

	silead_ts_पढ़ो_props(client);

	/* We must have the IRQ provided by DT or ACPI subप्रणाली */
	अगर (client->irq <= 0)
		वापस -ENODEV;

	data->regulators[0].supply = "vddio";
	data->regulators[1].supply = "avdd";
	error = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->regulators),
					data->regulators);
	अगर (error)
		वापस error;

	/*
	 * Enable regulators at probe and disable them at हटाओ, we need
	 * to keep the chip घातered otherwise it क्रममाला_लो its firmware.
	 */
	error = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (error)
		वापस error;

	error = devm_add_action_or_reset(dev, silead_disable_regulator, data);
	अगर (error)
		वापस error;

	/* Power GPIO pin */
	data->gpio_घातer = devm_gpiod_get_optional(dev, "power", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpio_घातer)) अणु
		अगर (PTR_ERR(data->gpio_घातer) != -EPROBE_DEFER)
			dev_err(dev, "Shutdown GPIO request failed\n");
		वापस PTR_ERR(data->gpio_घातer);
	पूर्ण

	error = silead_ts_setup(client);
	अगर (error)
		वापस error;

	error = silead_ts_request_input_dev(data);
	अगर (error)
		वापस error;

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, silead_ts_thपढ़ोed_irq_handler,
					  IRQF_ONESHOT, client->name, data);
	अगर (error) अणु
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "IRQ request failed %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused silead_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	disable_irq(client->irq);
	silead_ts_set_घातer(client, SILEAD_POWER_OFF);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused silead_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	bool second_try = false;
	पूर्णांक error, status;

	silead_ts_set_घातer(client, SILEAD_POWER_ON);

 retry:
	error = silead_ts_reset(client);
	अगर (error)
		वापस error;

	अगर (second_try) अणु
		error = silead_ts_load_fw(client);
		अगर (error)
			वापस error;
	पूर्ण

	error = silead_ts_startup(client);
	अगर (error)
		वापस error;

	status = silead_ts_get_status(client);
	अगर (status != SILEAD_STATUS_OK) अणु
		अगर (!second_try) अणु
			second_try = true;
			dev_dbg(dev, "Reloading firmware after unsuccessful resume\n");
			जाओ retry;
		पूर्ण
		dev_err(dev, "Resume error, status: 0x%02x\n", status);
		वापस -ENODEV;
	पूर्ण

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(silead_ts_pm, silead_ts_suspend, silead_ts_resume);

अटल स्थिर काष्ठा i2c_device_id silead_ts_id[] = अणु
	अणु "gsl1680", 0 पूर्ण,
	अणु "gsl1688", 0 पूर्ण,
	अणु "gsl3670", 0 पूर्ण,
	अणु "gsl3675", 0 पूर्ण,
	अणु "gsl3692", 0 पूर्ण,
	अणु "mssl1680", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, silead_ts_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id silead_ts_acpi_match[] = अणु
	अणु "GSL1680", 0 पूर्ण,
	अणु "GSL1688", 0 पूर्ण,
	अणु "GSL3670", 0 पूर्ण,
	अणु "GSL3675", 0 पूर्ण,
	अणु "GSL3692", 0 पूर्ण,
	अणु "MSSL1680", 0 पूर्ण,
	अणु "MSSL0001", 0 पूर्ण,
	अणु "MSSL0002", 0 पूर्ण,
	अणु "MSSL0017", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, silead_ts_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id silead_ts_of_match[] = अणु
	अणु .compatible = "silead,gsl1680" पूर्ण,
	अणु .compatible = "silead,gsl1688" पूर्ण,
	अणु .compatible = "silead,gsl3670" पूर्ण,
	अणु .compatible = "silead,gsl3675" पूर्ण,
	अणु .compatible = "silead,gsl3692" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, silead_ts_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver silead_ts_driver = अणु
	.probe = silead_ts_probe,
	.id_table = silead_ts_id,
	.driver = अणु
		.name = SILEAD_TS_NAME,
		.acpi_match_table = ACPI_PTR(silead_ts_acpi_match),
		.of_match_table = of_match_ptr(silead_ts_of_match),
		.pm = &silead_ts_pm,
	पूर्ण,
पूर्ण;
module_i2c_driver(silead_ts_driver);

MODULE_AUTHOR("Robert Dolca <robert.dolca@intel.com>");
MODULE_DESCRIPTION("Silead I2C touchscreen driver");
MODULE_LICENSE("GPL");
