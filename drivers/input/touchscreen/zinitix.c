<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

/* Register Map */

#घोषणा BT541_SWRESET_CMD			0x0000
#घोषणा BT541_WAKEUP_CMD			0x0001

#घोषणा BT541_IDLE_CMD				0x0004
#घोषणा BT541_SLEEP_CMD				0x0005

#घोषणा BT541_CLEAR_INT_STATUS_CMD		0x0003
#घोषणा BT541_CALIBRATE_CMD			0x0006
#घोषणा BT541_SAVE_STATUS_CMD			0x0007
#घोषणा BT541_SAVE_CALIBRATION_CMD		0x0008
#घोषणा BT541_RECALL_FACTORY_CMD		0x000f

#घोषणा BT541_THRESHOLD				0x0020

#घोषणा BT541_LARGE_PALM_REJECT_AREA_TH		0x003F

#घोषणा BT541_DEBUG_REG				0x0115 /* 0~7 */

#घोषणा BT541_TOUCH_MODE			0x0010
#घोषणा BT541_CHIP_REVISION			0x0011
#घोषणा BT541_FIRMWARE_VERSION			0x0012

#घोषणा ZINITIX_USB_DETECT			0x116

#घोषणा BT541_MINOR_FW_VERSION			0x0121

#घोषणा BT541_VENDOR_ID				0x001C
#घोषणा BT541_HW_ID				0x0014

#घोषणा BT541_DATA_VERSION_REG			0x0013
#घोषणा BT541_SUPPORTED_FINGER_NUM		0x0015
#घोषणा BT541_EEPROM_INFO			0x0018
#घोषणा BT541_INITIAL_TOUCH_MODE		0x0019

#घोषणा BT541_TOTAL_NUMBER_OF_X			0x0060
#घोषणा BT541_TOTAL_NUMBER_OF_Y			0x0061

#घोषणा BT541_DELAY_RAW_FOR_HOST		0x007f

#घोषणा BT541_BUTTON_SUPPORTED_NUM		0x00B0
#घोषणा BT541_BUTTON_SENSITIVITY		0x00B2
#घोषणा BT541_DUMMY_BUTTON_SENSITIVITY		0X00C8

#घोषणा BT541_X_RESOLUTION			0x00C0
#घोषणा BT541_Y_RESOLUTION			0x00C1

#घोषणा BT541_POINT_STATUS_REG			0x0080
#घोषणा BT541_ICON_STATUS_REG			0x00AA

#घोषणा BT541_POINT_COORD_REG			(BT541_POINT_STATUS_REG + 2)

#घोषणा BT541_AFE_FREQUENCY			0x0100
#घोषणा BT541_DND_N_COUNT			0x0122
#घोषणा BT541_DND_U_COUNT			0x0135

#घोषणा BT541_RAWDATA_REG			0x0200

#घोषणा BT541_EEPROM_INFO_REG			0x0018

#घोषणा BT541_INT_ENABLE_FLAG			0x00f0
#घोषणा BT541_PERIODICAL_INTERRUPT_INTERVAL	0x00f1

#घोषणा BT541_BTN_WIDTH				0x016d

#घोषणा BT541_CHECKSUM_RESULT			0x012c

#घोषणा BT541_INIT_FLASH			0x01d0
#घोषणा BT541_WRITE_FLASH			0x01d1
#घोषणा BT541_READ_FLASH			0x01d2

#घोषणा ZINITIX_INTERNAL_FLAG_02		0x011e
#घोषणा ZINITIX_INTERNAL_FLAG_03		0x011f

#घोषणा ZINITIX_I2C_CHECKSUM_WCNT		0x016a
#घोषणा ZINITIX_I2C_CHECKSUM_RESULT		0x016c

/* Interrupt & status रेजिस्टर flags */

#घोषणा BIT_PT_CNT_CHANGE			BIT(0)
#घोषणा BIT_DOWN				BIT(1)
#घोषणा BIT_MOVE				BIT(2)
#घोषणा BIT_UP					BIT(3)
#घोषणा BIT_PALM				BIT(4)
#घोषणा BIT_PALM_REJECT				BIT(5)
#घोषणा BIT_RESERVED_0				BIT(6)
#घोषणा BIT_RESERVED_1				BIT(7)
#घोषणा BIT_WEIGHT_CHANGE			BIT(8)
#घोषणा BIT_PT_NO_CHANGE			BIT(9)
#घोषणा BIT_REJECT				BIT(10)
#घोषणा BIT_PT_EXIST				BIT(11)
#घोषणा BIT_RESERVED_2				BIT(12)
#घोषणा BIT_ERROR				BIT(13)
#घोषणा BIT_DEBUG				BIT(14)
#घोषणा BIT_ICON_EVENT				BIT(15)

#घोषणा SUB_BIT_EXIST				BIT(0)
#घोषणा SUB_BIT_DOWN				BIT(1)
#घोषणा SUB_BIT_MOVE				BIT(2)
#घोषणा SUB_BIT_UP				BIT(3)
#घोषणा SUB_BIT_UPDATE				BIT(4)
#घोषणा SUB_BIT_WAIT				BIT(5)

#घोषणा DEFAULT_TOUCH_POINT_MODE		2
#घोषणा MAX_SUPPORTED_FINGER_NUM		5

#घोषणा CHIP_ON_DELAY				15 // ms
#घोषणा FIRMWARE_ON_DELAY			40 // ms

काष्ठा poपूर्णांक_coord अणु
	__le16	x;
	__le16	y;
	u8	width;
	u8	sub_status;
	// currently unused, but needed as padding:
	u8	minor_width;
	u8	angle;
पूर्ण;

काष्ठा touch_event अणु
	__le16	status;
	u8	finger_cnt;
	u8	समय_stamp;
	काष्ठा poपूर्णांक_coord poपूर्णांक_coord[MAX_SUPPORTED_FINGER_NUM];
पूर्ण;

काष्ठा bt541_ts_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	काष्ठा touchscreen_properties prop;
	काष्ठा regulator_bulk_data supplies[2];
	u32 zinitix_mode;
पूर्ण;

अटल पूर्णांक zinitix_पढ़ो_data(काष्ठा i2c_client *client,
			     u16 reg, व्योम *values, माप_प्रकार length)
अणु
	__le16 reg_le = cpu_to_le16(reg);
	पूर्णांक ret;

	/* A single i2c_transfer() transaction करोes not work here. */
	ret = i2c_master_send(client, (u8 *)&reg_le, माप(reg_le));
	अगर (ret != माप(reg_le))
		वापस ret < 0 ? ret : -EIO;

	ret = i2c_master_recv(client, (u8 *)values, length);
	अगर (ret != length)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_ग_लिखो_u16(काष्ठा i2c_client *client, u16 reg, u16 value)
अणु
	__le16 packet[2] = अणुcpu_to_le16(reg), cpu_to_le16(value)पूर्ण;
	पूर्णांक ret;

	ret = i2c_master_send(client, (u8 *)packet, माप(packet));
	अगर (ret != माप(packet))
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_ग_लिखो_cmd(काष्ठा i2c_client *client, u16 reg)
अणु
	__le16 reg_le = cpu_to_le16(reg);
	पूर्णांक ret;

	ret = i2c_master_send(client, (u8 *)&reg_le, माप(reg_le));
	अगर (ret != माप(reg_le))
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_init_touch(काष्ठा bt541_ts_data *bt541)
अणु
	काष्ठा i2c_client *client = bt541->client;
	पूर्णांक i;
	पूर्णांक error;

	error = zinitix_ग_लिखो_cmd(client, BT541_SWRESET_CMD);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to write reset command\n");
		वापस error;
	पूर्ण

	error = zinitix_ग_लिखो_u16(client, BT541_INT_ENABLE_FLAG, 0x0);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to reset interrupt enable flag\n");
		वापस error;
	पूर्ण

	/* initialize */
	error = zinitix_ग_लिखो_u16(client, BT541_X_RESOLUTION,
				  bt541->prop.max_x);
	अगर (error)
		वापस error;

	error = zinitix_ग_लिखो_u16(client, BT541_Y_RESOLUTION,
				  bt541->prop.max_y);
	अगर (error)
		वापस error;

	error = zinitix_ग_लिखो_u16(client, BT541_SUPPORTED_FINGER_NUM,
				  MAX_SUPPORTED_FINGER_NUM);
	अगर (error)
		वापस error;

	error = zinitix_ग_लिखो_u16(client, BT541_INITIAL_TOUCH_MODE,
				  bt541->zinitix_mode);
	अगर (error)
		वापस error;

	error = zinitix_ग_लिखो_u16(client, BT541_TOUCH_MODE,
				  bt541->zinitix_mode);
	अगर (error)
		वापस error;

	error = zinitix_ग_लिखो_u16(client, BT541_INT_ENABLE_FLAG,
				  BIT_PT_CNT_CHANGE | BIT_DOWN | BIT_MOVE |
					BIT_UP);
	अगर (error)
		वापस error;

	/* clear queue */
	क्रम (i = 0; i < 10; i++) अणु
		zinitix_ग_लिखो_cmd(client, BT541_CLEAR_INT_STATUS_CMD);
		udelay(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_init_regulators(काष्ठा bt541_ts_data *bt541)
अणु
	काष्ठा i2c_client *client = bt541->client;
	पूर्णांक error;

	bt541->supplies[0].supply = "vdd";
	bt541->supplies[1].supply = "vddo";
	error = devm_regulator_bulk_get(&client->dev,
					ARRAY_SIZE(bt541->supplies),
					bt541->supplies);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Failed to get regulators: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_send_घातer_on_sequence(काष्ठा bt541_ts_data *bt541)
अणु
	पूर्णांक error;
	काष्ठा i2c_client *client = bt541->client;

	error = zinitix_ग_लिखो_u16(client, 0xc000, 0x0001);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to send power sequence(vendor cmd enable)\n");
		वापस error;
	पूर्ण
	udelay(10);

	error = zinitix_ग_लिखो_cmd(client, 0xc004);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to send power sequence (intn clear)\n");
		वापस error;
	पूर्ण
	udelay(10);

	error = zinitix_ग_लिखो_u16(client, 0xc002, 0x0001);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to send power sequence (nvm init)\n");
		वापस error;
	पूर्ण
	mdelay(2);

	error = zinitix_ग_लिखो_u16(client, 0xc001, 0x0001);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to send power sequence (program start)\n");
		वापस error;
	पूर्ण
	msleep(FIRMWARE_ON_DELAY);

	वापस 0;
पूर्ण

अटल व्योम zinitix_report_finger(काष्ठा bt541_ts_data *bt541, पूर्णांक slot,
				  स्थिर काष्ठा poपूर्णांक_coord *p)
अणु
	input_mt_slot(bt541->input_dev, slot);
	input_mt_report_slot_state(bt541->input_dev, MT_TOOL_FINGER, true);
	touchscreen_report_pos(bt541->input_dev, &bt541->prop,
			       le16_to_cpu(p->x), le16_to_cpu(p->y), true);
	input_report_असल(bt541->input_dev, ABS_MT_TOUCH_MAJOR, p->width);
पूर्ण

अटल irqवापस_t zinitix_ts_irq_handler(पूर्णांक irq, व्योम *bt541_handler)
अणु
	काष्ठा bt541_ts_data *bt541 = bt541_handler;
	काष्ठा i2c_client *client = bt541->client;
	काष्ठा touch_event touch_event;
	पूर्णांक error;
	पूर्णांक i;

	स_रखो(&touch_event, 0, माप(काष्ठा touch_event));

	error = zinitix_पढ़ो_data(bt541->client, BT541_POINT_STATUS_REG,
				  &touch_event, माप(काष्ठा touch_event));
	अगर (error) अणु
		dev_err(&client->dev, "Failed to read in touchpoint struct\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < MAX_SUPPORTED_FINGER_NUM; i++)
		अगर (touch_event.poपूर्णांक_coord[i].sub_status & SUB_BIT_EXIST)
			zinitix_report_finger(bt541, i,
					      &touch_event.poपूर्णांक_coord[i]);

	input_mt_sync_frame(bt541->input_dev);
	input_sync(bt541->input_dev);

out:
	zinitix_ग_लिखो_cmd(bt541->client, BT541_CLEAR_INT_STATUS_CMD);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक zinitix_start(काष्ठा bt541_ts_data *bt541)
अणु
	पूर्णांक error;

	error = regulator_bulk_enable(ARRAY_SIZE(bt541->supplies),
				      bt541->supplies);
	अगर (error) अणु
		dev_err(&bt541->client->dev,
			"Failed to enable regulators: %d\n", error);
		वापस error;
	पूर्ण

	msleep(CHIP_ON_DELAY);

	error = zinitix_send_घातer_on_sequence(bt541);
	अगर (error) अणु
		dev_err(&bt541->client->dev,
			"Error while sending power-on sequence: %d\n", error);
		वापस error;
	पूर्ण

	error = zinitix_init_touch(bt541);
	अगर (error) अणु
		dev_err(&bt541->client->dev,
			"Error while configuring touch IC\n");
		वापस error;
	पूर्ण

	enable_irq(bt541->client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_stop(काष्ठा bt541_ts_data *bt541)
अणु
	पूर्णांक error;

	disable_irq(bt541->client->irq);

	error = regulator_bulk_disable(ARRAY_SIZE(bt541->supplies),
				       bt541->supplies);
	अगर (error) अणु
		dev_err(&bt541->client->dev,
			"Failed to disable regulators: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा bt541_ts_data *bt541 = input_get_drvdata(dev);

	वापस zinitix_start(bt541);
पूर्ण

अटल व्योम zinitix_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा bt541_ts_data *bt541 = input_get_drvdata(dev);

	zinitix_stop(bt541);
पूर्ण

अटल पूर्णांक zinitix_init_input_dev(काष्ठा bt541_ts_data *bt541)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	input_dev = devm_input_allocate_device(&bt541->client->dev);
	अगर (!input_dev) अणु
		dev_err(&bt541->client->dev,
			"Failed to allocate input device.");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(input_dev, bt541);
	bt541->input_dev = input_dev;

	input_dev->name = "Zinitix Capacitive TouchScreen";
	input_dev->phys = "input/ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->खोलो = zinitix_input_खोलो;
	input_dev->बंद = zinitix_input_बंद;

	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_असल_params(input_dev, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);

	touchscreen_parse_properties(input_dev, true, &bt541->prop);
	अगर (!bt541->prop.max_x || !bt541->prop.max_y) अणु
		dev_err(&bt541->client->dev,
			"Touchscreen-size-x and/or touchscreen-size-y not set in dts\n");
		वापस -EINVAL;
	पूर्ण

	error = input_mt_init_slots(input_dev, MAX_SUPPORTED_FINGER_NUM,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(&bt541->client->dev,
			"Failed to initialize MT slots: %d", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&bt541->client->dev,
			"Failed to register input device: %d", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zinitix_ts_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा bt541_ts_data *bt541;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev,
			"Failed to assert adapter's support for plain I2C.\n");
		वापस -ENXIO;
	पूर्ण

	bt541 = devm_kzalloc(&client->dev, माप(*bt541), GFP_KERNEL);
	अगर (!bt541)
		वापस -ENOMEM;

	bt541->client = client;
	i2c_set_clientdata(client, bt541);

	error = zinitix_init_regulators(bt541);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to initialize regulators: %d\n", error);
		वापस error;
	पूर्ण

	error = zinitix_init_input_dev(bt541);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to initialize input device: %d\n", error);
		वापस error;
	पूर्ण

	error = device_property_पढ़ो_u32(&client->dev, "zinitix,mode",
					 &bt541->zinitix_mode);
	अगर (error < 0) अणु
		/* fall back to mode 2 */
		bt541->zinitix_mode = DEFAULT_TOUCH_POINT_MODE;
	पूर्ण

	अगर (bt541->zinitix_mode != 2) अणु
		/*
		 * If there are devices that करोn't support mode 2, support
		 * क्रम other modes (0, 1) will be needed.
		 */
		dev_err(&client->dev,
			"Malformed zinitix,mode property, must be 2 (supplied: %d)\n",
			bt541->zinitix_mode);
		वापस -EINVAL;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, zinitix_ts_irq_handler,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  client->name, bt541);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused zinitix_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bt541_ts_data *bt541 = i2c_get_clientdata(client);

	mutex_lock(&bt541->input_dev->mutex);

	अगर (input_device_enabled(bt541->input_dev))
		zinitix_stop(bt541);

	mutex_unlock(&bt541->input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused zinitix_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bt541_ts_data *bt541 = i2c_get_clientdata(client);
	पूर्णांक ret = 0;

	mutex_lock(&bt541->input_dev->mutex);

	अगर (input_device_enabled(bt541->input_dev))
		ret = zinitix_start(bt541);

	mutex_unlock(&bt541->input_dev->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(zinitix_pm_ops, zinitix_suspend, zinitix_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id zinitix_of_match[] = अणु
	अणु .compatible = "zinitix,bt541" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zinitix_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver zinitix_ts_driver = अणु
	.probe_new = zinitix_ts_probe,
	.driver = अणु
		.name = "Zinitix-TS",
		.pm = &zinitix_pm_ops,
		.of_match_table = of_match_ptr(zinitix_of_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(zinitix_ts_driver);

MODULE_AUTHOR("Michael Srba <Michael.Srba@seznam.cz>");
MODULE_DESCRIPTION("Zinitix touchscreen driver");
MODULE_LICENSE("GPL v2");
