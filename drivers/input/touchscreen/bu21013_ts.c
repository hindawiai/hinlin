<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Naveen Kumar G <naveen.gaddipati@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा MAX_FINGERS	2
#घोषणा RESET_DELAY	30
#घोषणा PENUP_TIMEOUT	(10)
#घोषणा DELTA_MIN	16
#घोषणा MASK_BITS	0x03
#घोषणा SHIFT_8		8
#घोषणा SHIFT_2		2
#घोषणा LENGTH_OF_BUFFER	11
#घोषणा I2C_RETRY_COUNT	5

#घोषणा BU21013_SENSORS_BTN_0_7_REG	0x70
#घोषणा BU21013_SENSORS_BTN_8_15_REG	0x71
#घोषणा BU21013_SENSORS_BTN_16_23_REG	0x72
#घोषणा BU21013_X1_POS_MSB_REG		0x73
#घोषणा BU21013_X1_POS_LSB_REG		0x74
#घोषणा BU21013_Y1_POS_MSB_REG		0x75
#घोषणा BU21013_Y1_POS_LSB_REG		0x76
#घोषणा BU21013_X2_POS_MSB_REG		0x77
#घोषणा BU21013_X2_POS_LSB_REG		0x78
#घोषणा BU21013_Y2_POS_MSB_REG		0x79
#घोषणा BU21013_Y2_POS_LSB_REG		0x7A
#घोषणा BU21013_INT_CLR_REG		0xE8
#घोषणा BU21013_INT_MODE_REG		0xE9
#घोषणा BU21013_GAIN_REG		0xEA
#घोषणा BU21013_OFFSET_MODE_REG		0xEB
#घोषणा BU21013_XY_EDGE_REG		0xEC
#घोषणा BU21013_RESET_REG		0xED
#घोषणा BU21013_CALIB_REG		0xEE
#घोषणा BU21013_DONE_REG		0xEF
#घोषणा BU21013_SENSOR_0_7_REG		0xF0
#घोषणा BU21013_SENSOR_8_15_REG		0xF1
#घोषणा BU21013_SENSOR_16_23_REG	0xF2
#घोषणा BU21013_POS_MODE1_REG		0xF3
#घोषणा BU21013_POS_MODE2_REG		0xF4
#घोषणा BU21013_CLK_MODE_REG		0xF5
#घोषणा BU21013_IDLE_REG		0xFA
#घोषणा BU21013_FILTER_REG		0xFB
#घोषणा BU21013_TH_ON_REG		0xFC
#घोषणा BU21013_TH_OFF_REG		0xFD


#घोषणा BU21013_RESET_ENABLE		0x01

#घोषणा BU21013_SENSORS_EN_0_7		0x3F
#घोषणा BU21013_SENSORS_EN_8_15		0xFC
#घोषणा BU21013_SENSORS_EN_16_23	0x1F

#घोषणा BU21013_POS_MODE1_0		0x02
#घोषणा BU21013_POS_MODE1_1		0x04
#घोषणा BU21013_POS_MODE1_2		0x08

#घोषणा BU21013_POS_MODE2_ZERO		0x01
#घोषणा BU21013_POS_MODE2_AVG1		0x02
#घोषणा BU21013_POS_MODE2_AVG2		0x04
#घोषणा BU21013_POS_MODE2_EN_XY		0x08
#घोषणा BU21013_POS_MODE2_EN_RAW	0x10
#घोषणा BU21013_POS_MODE2_MULTI		0x80

#घोषणा BU21013_CLK_MODE_DIV		0x01
#घोषणा BU21013_CLK_MODE_EXT		0x02
#घोषणा BU21013_CLK_MODE_CALIB		0x80

#घोषणा BU21013_IDLET_0			0x01
#घोषणा BU21013_IDLET_1			0x02
#घोषणा BU21013_IDLET_2			0x04
#घोषणा BU21013_IDLET_3			0x08
#घोषणा BU21013_IDLE_INTERMIT_EN	0x10

#घोषणा BU21013_DELTA_0_6	0x7F
#घोषणा BU21013_FILTER_EN	0x80

#घोषणा BU21013_INT_MODE_LEVEL	0x00
#घोषणा BU21013_INT_MODE_EDGE	0x01

#घोषणा BU21013_GAIN_0		0x01
#घोषणा BU21013_GAIN_1		0x02
#घोषणा BU21013_GAIN_2		0x04

#घोषणा BU21013_OFFSET_MODE_DEFAULT	0x00
#घोषणा BU21013_OFFSET_MODE_MOVE	0x01
#घोषणा BU21013_OFFSET_MODE_DISABLE	0x02

#घोषणा BU21013_TH_ON_0		0x01
#घोषणा BU21013_TH_ON_1		0x02
#घोषणा BU21013_TH_ON_2		0x04
#घोषणा BU21013_TH_ON_3		0x08
#घोषणा BU21013_TH_ON_4		0x10
#घोषणा BU21013_TH_ON_5		0x20
#घोषणा BU21013_TH_ON_6		0x40
#घोषणा BU21013_TH_ON_7		0x80
#घोषणा BU21013_TH_ON_MAX	0xFF

#घोषणा BU21013_TH_OFF_0	0x01
#घोषणा BU21013_TH_OFF_1	0x02
#घोषणा BU21013_TH_OFF_2	0x04
#घोषणा BU21013_TH_OFF_3	0x08
#घोषणा BU21013_TH_OFF_4	0x10
#घोषणा BU21013_TH_OFF_5	0x20
#घोषणा BU21013_TH_OFF_6	0x40
#घोषणा BU21013_TH_OFF_7	0x80
#घोषणा BU21013_TH_OFF_MAX	0xFF

#घोषणा BU21013_X_EDGE_0	0x01
#घोषणा BU21013_X_EDGE_1	0x02
#घोषणा BU21013_X_EDGE_2	0x04
#घोषणा BU21013_X_EDGE_3	0x08
#घोषणा BU21013_Y_EDGE_0	0x10
#घोषणा BU21013_Y_EDGE_1	0x20
#घोषणा BU21013_Y_EDGE_2	0x40
#घोषणा BU21013_Y_EDGE_3	0x80

#घोषणा BU21013_DONE	0x01
#घोषणा BU21013_NUMBER_OF_X_SENSORS	(6)
#घोषणा BU21013_NUMBER_OF_Y_SENSORS	(11)

#घोषणा DRIVER_TP	"bu21013_tp"

/**
 * काष्ठा bu21013_ts - touch panel data काष्ठाure
 * @client: poपूर्णांकer to the i2c client
 * @in_dev: poपूर्णांकer to the input device काष्ठाure
 * @props: the device coordinate transक्रमmation properties
 * @regulator: poपूर्णांकer to the Regulator used क्रम touch screen
 * @cs_gpiod: chip select GPIO line
 * @पूर्णांक_gpiod: touch पूर्णांकerrupt GPIO line
 * @touch_x_max: maximum X coordinate reported by the device
 * @touch_y_max: maximum Y coordinate reported by the device
 * @x_flip: indicates that the driver should invert X coordinate beक्रमe
 *	reporting
 * @y_flip: indicates that the driver should invert Y coordinate beक्रमe
 *	reporting
 * @touch_stopped: touch stop flag
 *
 * Touch panel device data काष्ठाure
 */
काष्ठा bu21013_ts अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *in_dev;
	काष्ठा touchscreen_properties props;
	काष्ठा regulator *regulator;
	काष्ठा gpio_desc *cs_gpiod;
	काष्ठा gpio_desc *पूर्णांक_gpiod;
	u32 touch_x_max;
	u32 touch_y_max;
	bool x_flip;
	bool y_flip;
	bool touch_stopped;
पूर्ण;

अटल पूर्णांक bu21013_पढ़ो_block_data(काष्ठा bu21013_ts *ts, u8 *buf)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < I2C_RETRY_COUNT; i++) अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(ts->client,
						    BU21013_SENSORS_BTN_0_7_REG,
						    LENGTH_OF_BUFFER, buf);
		अगर (ret == LENGTH_OF_BUFFER)
			वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bu21013_करो_touch_report(काष्ठा bu21013_ts *ts)
अणु
	काष्ठा input_dev *input = ts->in_dev;
	काष्ठा input_mt_pos pos[MAX_FINGERS];
	पूर्णांक slots[MAX_FINGERS];
	u8 buf[LENGTH_OF_BUFFER];
	bool has_x_sensors, has_y_sensors;
	पूर्णांक finger_करोwn_count = 0;
	पूर्णांक i;

	अगर (bu21013_पढ़ो_block_data(ts, buf) < 0)
		वापस -EINVAL;

	has_x_sensors = hweight32(buf[0] & BU21013_SENSORS_EN_0_7);
	has_y_sensors = hweight32(((buf[1] & BU21013_SENSORS_EN_8_15) |
		((buf[2] & BU21013_SENSORS_EN_16_23) << SHIFT_8)) >> SHIFT_2);
	अगर (!has_x_sensors || !has_y_sensors)
		वापस 0;

	क्रम (i = 0; i < MAX_FINGERS; i++) अणु
		स्थिर u8 *data = &buf[4 * i + 3];
		अचिन्हित पूर्णांक x, y;

		x = data[0] << SHIFT_2 | (data[1] & MASK_BITS);
		y = data[2] << SHIFT_2 | (data[3] & MASK_BITS);
		अगर (x != 0 && y != 0)
			touchscreen_set_mt_pos(&pos[finger_करोwn_count++],
					       &ts->props, x, y);
	पूर्ण

	अगर (finger_करोwn_count == 2 &&
	    (असल(pos[0].x - pos[1].x) < DELTA_MIN ||
	     असल(pos[0].y - pos[1].y) < DELTA_MIN)) अणु
		वापस 0;
	पूर्ण

	input_mt_assign_slots(input, slots, pos, finger_करोwn_count, DELTA_MIN);
	क्रम (i = 0; i < finger_करोwn_count; i++) अणु
		input_mt_slot(input, slots[i]);
		input_mt_report_slot_state(input, MT_TOOL_FINGER, true);
		input_report_असल(input, ABS_MT_POSITION_X, pos[i].x);
		input_report_असल(input, ABS_MT_POSITION_Y, pos[i].y);
	पूर्ण

	input_mt_sync_frame(input);
	input_sync(input);

	वापस 0;
पूर्ण

अटल irqवापस_t bu21013_gpio_irq(पूर्णांक irq, व्योम *device_data)
अणु
	काष्ठा bu21013_ts *ts = device_data;
	पूर्णांक keep_polling;
	पूर्णांक error;

	करो अणु
		error = bu21013_करो_touch_report(ts);
		अगर (error) अणु
			dev_err(&ts->client->dev, "%s failed\n", __func__);
			अवरोध;
		पूर्ण

		अगर (unlikely(ts->touch_stopped))
			अवरोध;

		keep_polling = ts->पूर्णांक_gpiod ?
			gpiod_get_value(ts->पूर्णांक_gpiod) : false;
		अगर (keep_polling)
			usleep_range(2000, 2500);
	पूर्ण जबतक (keep_polling);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bu21013_init_chip(काष्ठा bu21013_ts *ts)
अणु
	काष्ठा i2c_client *client = ts->client;
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_RESET_REG,
					  BU21013_RESET_ENABLE);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_RESET reg write failed\n");
		वापस error;
	पूर्ण
	msleep(RESET_DELAY);

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_SENSOR_0_7_REG,
					  BU21013_SENSORS_EN_0_7);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_SENSOR_0_7 reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_SENSOR_8_15_REG,
					  BU21013_SENSORS_EN_8_15);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_SENSOR_8_15 reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_SENSOR_16_23_REG,
					  BU21013_SENSORS_EN_16_23);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_SENSOR_16_23 reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_POS_MODE1_REG,
					  BU21013_POS_MODE1_0 |
						BU21013_POS_MODE1_1);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_POS_MODE1 reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_POS_MODE2_REG,
					  BU21013_POS_MODE2_ZERO |
						BU21013_POS_MODE2_AVG1 |
						BU21013_POS_MODE2_AVG2 |
						BU21013_POS_MODE2_EN_RAW |
						BU21013_POS_MODE2_MULTI);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_POS_MODE2 reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_CLK_MODE_REG,
					  BU21013_CLK_MODE_DIV |
						BU21013_CLK_MODE_CALIB);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_CLK_MODE reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_IDLE_REG,
					  BU21013_IDLET_0 |
						BU21013_IDLE_INTERMIT_EN);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_IDLE reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_INT_MODE_REG,
					  BU21013_INT_MODE_LEVEL);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_INT_MODE reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_FILTER_REG,
					  BU21013_DELTA_0_6 |
						BU21013_FILTER_EN);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_FILTER reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_TH_ON_REG,
					  BU21013_TH_ON_5);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_TH_ON reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_TH_OFF_REG,
					  BU21013_TH_OFF_4 | BU21013_TH_OFF_3);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_TH_OFF reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_GAIN_REG,
					  BU21013_GAIN_0 | BU21013_GAIN_1);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_GAIN reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_OFFSET_MODE_REG,
					  BU21013_OFFSET_MODE_DEFAULT);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_OFFSET_MODE reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_XY_EDGE_REG,
					  BU21013_X_EDGE_0 |
						BU21013_X_EDGE_2 |
						BU21013_Y_EDGE_1 |
						BU21013_Y_EDGE_3);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_XY_EDGE reg write failed\n");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, BU21013_DONE_REG,
					  BU21013_DONE);
	अगर (error) अणु
		dev_err(&client->dev, "BU21013_REG_DONE reg write failed\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bu21013_घातer_off(व्योम *_ts)
अणु
	काष्ठा bu21013_ts *ts = _ts;

	regulator_disable(ts->regulator);
पूर्ण

अटल व्योम bu21013_disable_chip(व्योम *_ts)
अणु
	काष्ठा bu21013_ts *ts = _ts;

	gpiod_set_value(ts->cs_gpiod, 0);
पूर्ण

अटल पूर्णांक bu21013_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bu21013_ts *ts;
	काष्ठा input_dev *in_dev;
	काष्ठा input_असलinfo *info;
	u32 max_x = 0, max_y = 0;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "i2c smbus byte data not supported\n");
		वापस -EIO;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(&client->dev, "No IRQ set up\n");
		वापस -EINVAL;
	पूर्ण

	ts = devm_kzalloc(&client->dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	ts->client = client;

	ts->x_flip = device_property_पढ़ो_bool(&client->dev, "rohm,flip-x");
	ts->y_flip = device_property_पढ़ो_bool(&client->dev, "rohm,flip-y");

	in_dev = devm_input_allocate_device(&client->dev);
	अगर (!in_dev) अणु
		dev_err(&client->dev, "device memory alloc failed\n");
		वापस -ENOMEM;
	पूर्ण
	ts->in_dev = in_dev;
	input_set_drvdata(in_dev, ts);

	/* रेजिस्टर the device to input subप्रणाली */
	in_dev->name = DRIVER_TP;
	in_dev->id.bustype = BUS_I2C;

	device_property_पढ़ो_u32(&client->dev, "rohm,touch-max-x", &max_x);
	device_property_पढ़ो_u32(&client->dev, "rohm,touch-max-y", &max_y);

	input_set_असल_params(in_dev, ABS_MT_POSITION_X, 0, max_x, 0, 0);
	input_set_असल_params(in_dev, ABS_MT_POSITION_Y, 0, max_y, 0, 0);

	touchscreen_parse_properties(in_dev, true, &ts->props);

	/* Adjust क्रम the legacy "flip" properties, अगर present */
	अगर (!ts->props.invert_x &&
	    device_property_पढ़ो_bool(&client->dev, "rohm,flip-x")) अणु
		info = &in_dev->असलinfo[ABS_MT_POSITION_X];
		info->maximum -= info->minimum;
		info->minimum = 0;
	पूर्ण

	अगर (!ts->props.invert_y &&
	    device_property_पढ़ो_bool(&client->dev, "rohm,flip-y")) अणु
		info = &in_dev->असलinfo[ABS_MT_POSITION_Y];
		info->maximum -= info->minimum;
		info->minimum = 0;
	पूर्ण

	error = input_mt_init_slots(in_dev, MAX_FINGERS,
				    INPUT_MT_सूचीECT | INPUT_MT_TRACK |
					INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(&client->dev, "failed to initialize MT slots");
		वापस error;
	पूर्ण

	ts->regulator = devm_regulator_get(&client->dev, "avdd");
	अगर (IS_ERR(ts->regulator)) अणु
		dev_err(&client->dev, "regulator_get failed\n");
		वापस PTR_ERR(ts->regulator);
	पूर्ण

	error = regulator_enable(ts->regulator);
	अगर (error) अणु
		dev_err(&client->dev, "regulator enable failed\n");
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev, bu21013_घातer_off, ts);
	अगर (error) अणु
		dev_err(&client->dev, "failed to install power off handler\n");
		वापस error;
	पूर्ण

	/* Named "CS" on the chip, DT binding is "reset" */
	ts->cs_gpiod = devm_gpiod_get(&client->dev, "reset", GPIOD_OUT_HIGH);
	error = PTR_ERR_OR_ZERO(ts->cs_gpiod);
	अगर (error) अणु
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev, "failed to get CS GPIO\n");
		वापस error;
	पूर्ण
	gpiod_set_consumer_name(ts->cs_gpiod, "BU21013 CS");

	error = devm_add_action_or_reset(&client->dev,
					 bu21013_disable_chip, ts);
	अगर (error) अणु
		dev_err(&client->dev,
			"failed to install chip disable handler\n");
		वापस error;
	पूर्ण

	/* Named "INT" on the chip, DT binding is "touch" */
	ts->पूर्णांक_gpiod = devm_gpiod_get_optional(&client->dev,
						"touch", GPIOD_IN);
	error = PTR_ERR_OR_ZERO(ts->पूर्णांक_gpiod);
	अगर (error) अणु
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev, "failed to get INT GPIO\n");
		वापस error;
	पूर्ण

	अगर (ts->पूर्णांक_gpiod)
		gpiod_set_consumer_name(ts->पूर्णांक_gpiod, "BU21013 INT");

	/* configure the touch panel controller */
	error = bu21013_init_chip(ts);
	अगर (error) अणु
		dev_err(&client->dev, "error in bu21013 config\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, bu21013_gpio_irq,
					  IRQF_ONESHOT, DRIVER_TP, ts);
	अगर (error) अणु
		dev_err(&client->dev, "request irq %d failed\n",
			client->irq);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(in_dev);
	अगर (error) अणु
		dev_err(&client->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	i2c_set_clientdata(client, ts);

	वापस 0;
पूर्ण

अटल पूर्णांक bu21013_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bu21013_ts *ts = i2c_get_clientdata(client);

	/* Make sure IRQ will निकास quickly even अगर there is contact */
	ts->touch_stopped = true;
	/* The resources will be मुक्तd by devm */

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bu21013_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bu21013_ts *ts = i2c_get_clientdata(client);

	ts->touch_stopped = true;
	mb();
	disable_irq(client->irq);

	अगर (!device_may_wakeup(&client->dev))
		regulator_disable(ts->regulator);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bu21013_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bu21013_ts *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	अगर (!device_may_wakeup(&client->dev)) अणु
		error = regulator_enable(ts->regulator);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to re-enable regulator when resuming\n");
			वापस error;
		पूर्ण

		error = bu21013_init_chip(ts);
		अगर (error) अणु
			dev_err(&client->dev,
				"failed to reinitialize chip when resuming\n");
			वापस error;
		पूर्ण
	पूर्ण

	ts->touch_stopped = false;
	mb();
	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bu21013_dev_pm_ops, bu21013_suspend, bu21013_resume);

अटल स्थिर काष्ठा i2c_device_id bu21013_id[] = अणु
	अणु DRIVER_TP, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bu21013_id);

अटल काष्ठा i2c_driver bu21013_driver = अणु
	.driver	= अणु
		.name	=	DRIVER_TP,
		.pm	=	&bu21013_dev_pm_ops,
	पूर्ण,
	.probe		=	bu21013_probe,
	.हटाओ		=	bu21013_हटाओ,
	.id_table	=	bu21013_id,
पूर्ण;

module_i2c_driver(bu21013_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Naveen Kumar G <naveen.gaddipati@stericsson.com>");
MODULE_DESCRIPTION("bu21013 touch screen controller driver");
