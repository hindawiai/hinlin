<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Rohm BU21029 touchscreen controller driver
 *
 * Copyright (C) 2015-2018 Bosch Sicherheitsप्रणालीe GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/समयr.h>

/*
 * HW_ID1 Register (PAGE=0, ADDR=0x0E, Reset value=0x02, Read only)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |                                 HW_IDH                                |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * HW_ID2 Register (PAGE=0, ADDR=0x0F, Reset value=0x29, Read only)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |                                 HW_IDL                                |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * HW_IDH: high 8bits of IC's ID
 * HW_IDL: low  8bits of IC's ID
 */
#घोषणा BU21029_HWID_REG	(0x0E << 3)
#घोषणा SUPPORTED_HWID		0x0229

/*
 * CFR0 Register (PAGE=0, ADDR=0x00, Reset value=0x20)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   0    |   0    |  CALIB |  INTRM |   0    |   0    |   0    |   0    |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * CALIB: 0 = not to use calibration result (*)
 *        1 = use calibration result
 * INTRM: 0 = INT output depend on "pen down" (*)
 *        1 = INT output always "0"
 */
#घोषणा BU21029_CFR0_REG	(0x00 << 3)
#घोषणा CFR0_VALUE		0x00

/*
 * CFR1 Register (PAGE=0, ADDR=0x01, Reset value=0xA6)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |  MAV   |         AVE[2:0]         |   0    |         SMPL[2:0]        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * MAV:  0 = median average filter off
 *       1 = median average filter on (*)
 * AVE:  AVE+1 = number of average samples क्रम MAV,
 *               अगर AVE>SMPL, then AVE=SMPL (=3)
 * SMPL: SMPL+1 = number of conversion samples क्रम MAV (=7)
 */
#घोषणा BU21029_CFR1_REG	(0x01 << 3)
#घोषणा CFR1_VALUE		0xA6

/*
 * CFR2 Register (PAGE=0, ADDR=0x02, Reset value=0x04)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |          INTVL_TIME[3:0]          |          TIME_ST_ADC[3:0]         |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * INTVL_TIME: रुकोing समय between completion of conversion
 *             and start of next conversion, only usable in
 *             स्वतःscan mode (=20.480ms)
 * TIME_ST_ADC: रुकोing समय between application of voltage
 *              to panel and start of A/D conversion (=100us)
 */
#घोषणा BU21029_CFR2_REG	(0x02 << 3)
#घोषणा CFR2_VALUE		0xC9

/*
 * CFR3 Register (PAGE=0, ADDR=0x0B, Reset value=0x72)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |  RM8   | STRETCH|  PU90K |  DUAL  |           PIDAC_OFS[3:0]          |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * RM8: 0 = coordinate resolution is 12bit (*)
 *      1 = coordinate resolution is 8bit
 * STRETCH: 0 = SCL_STRETCH function off
 *          1 = SCL_STRETCH function on (*)
 * PU90K: 0 = पूर्णांकernal pull-up resistance क्रम touch detection is ~50kohms (*)
 *        1 = पूर्णांकernal pull-up resistance क्रम touch detection is ~90kohms
 * DUAL: 0 = dual touch detection off (*)
 *       1 = dual touch detection on
 * PIDAC_OFS: dual touch detection circuit adjusपंचांगent, it is not necessary
 *            to change this from initial value
 */
#घोषणा BU21029_CFR3_REG	(0x0B << 3)
#घोषणा CFR3_VALUE		0x42

/*
 * LDO Register (PAGE=0, ADDR=0x0C, Reset value=0x00)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   0    |         PVDD[2:0]        |   0    |         AVDD[2:0]        |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * PVDD: output voltage of panel output regulator (=2.000V)
 * AVDD: output voltage of analog circuit regulator (=2.000V)
 */
#घोषणा BU21029_LDO_REG		(0x0C << 3)
#घोषणा LDO_VALUE		0x77

/*
 * Serial Interface Command Byte 1 (CID=1)
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   D7   |   D6   |   D5   |   D4   |   D3   |   D2   |   D1   |   D0   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * |   1    |                 CF                |  CMSK  |  PDM   |  STP   |
 * +--------+--------+--------+--------+--------+--------+--------+--------+
 * CF: conversion function, see table 3 in datasheet p6 (=0000, स्वतःmatic scan)
 * CMSK: 0 = executes convert function (*)
 *       1 = पढ़ोs the convert result
 * PDM: 0 = घातer करोwn after convert function stops (*)
 *      1 = keep घातer on after convert function stops
 * STP: 1 = पात current conversion and घातer करोwn, set to "0" स्वतःmatically
 */
#घोषणा BU21029_AUTOSCAN	0x80

/*
 * The समयout value needs to be larger than INTVL_TIME + tConv4 (sample and
 * conversion समय), where tConv4 is calculated by क्रमmula:
 * tPON + tDLY1 + (tTIME_ST_ADC + (tADC * tSMPL) * 2 + tDLY2) * 3
 * see figure 8 in datasheet p15 क्रम details of each field.
 */
#घोषणा PEN_UP_TIMEOUT_MS	50

#घोषणा STOP_DELAY_MIN_US	50
#घोषणा STOP_DELAY_MAX_US	1000
#घोषणा START_DELAY_MS		2
#घोषणा BUF_LEN			8
#घोषणा SCALE_12BIT		(1 << 12)
#घोषणा MAX_12BIT		((1 << 12) - 1)
#घोषणा DRIVER_NAME		"bu21029"

काष्ठा bu21029_ts_data अणु
	काष्ठा i2c_client		*client;
	काष्ठा input_dev		*in_dev;
	काष्ठा समयr_list		समयr;
	काष्ठा regulator		*vdd;
	काष्ठा gpio_desc		*reset_gpios;
	u32				x_plate_ohms;
	काष्ठा touchscreen_properties	prop;
पूर्ण;

अटल व्योम bu21029_touch_report(काष्ठा bu21029_ts_data *bu21029, स्थिर u8 *buf)
अणु
	u16 x, y, z1, z2;
	u32 rz;
	s32 max_pressure = input_असल_get_max(bu21029->in_dev, ABS_PRESSURE);

	/*
	 * compose upper 8 and lower 4 bits पूर्णांकo a 12bit value:
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |            ByteH              |            ByteL              |
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |b07|b06|b05|b04|b03|b02|b01|b00|b07|b06|b05|b04|b03|b02|b01|b00|
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 * |v11|v10|v09|v08|v07|v06|v05|v04|v03|v02|v01|v00| 0 | 0 | 0 | 0 |
	 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	 */
	x  = (buf[0] << 4) | (buf[1] >> 4);
	y  = (buf[2] << 4) | (buf[3] >> 4);
	z1 = (buf[4] << 4) | (buf[5] >> 4);
	z2 = (buf[6] << 4) | (buf[7] >> 4);

	अगर (z1 && z2) अणु
		/*
		 * calculate Rz (pressure resistance value) by equation:
		 * Rz = Rx * (x/Q) * ((z2/z1) - 1), where
		 * Rx is x-plate resistance,
		 * Q  is the touch screen resolution (8bit = 256, 12bit = 4096)
		 * x, z1, z2 are the measured positions.
		 */
		rz  = z2 - z1;
		rz *= x;
		rz *= bu21029->x_plate_ohms;
		rz /= z1;
		rz  = DIV_ROUND_CLOSEST(rz, SCALE_12BIT);
		अगर (rz <= max_pressure) अणु
			touchscreen_report_pos(bu21029->in_dev, &bu21029->prop,
					       x, y, false);
			input_report_असल(bu21029->in_dev, ABS_PRESSURE,
					 max_pressure - rz);
			input_report_key(bu21029->in_dev, BTN_TOUCH, 1);
			input_sync(bu21029->in_dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bu21029_touch_release(काष्ठा समयr_list *t)
अणु
	काष्ठा bu21029_ts_data *bu21029 = from_समयr(bu21029, t, समयr);

	input_report_असल(bu21029->in_dev, ABS_PRESSURE, 0);
	input_report_key(bu21029->in_dev, BTN_TOUCH, 0);
	input_sync(bu21029->in_dev);
पूर्ण

अटल irqवापस_t bu21029_touch_soft_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bu21029_ts_data *bu21029 = data;
	u8 buf[BUF_LEN];
	पूर्णांक error;

	/*
	 * Read touch data and deनिश्चित पूर्णांकerrupt (will निश्चित again after
	 * INTVL_TIME + tConv4 क्रम continuous touch)
	 */
	error = i2c_smbus_पढ़ो_i2c_block_data(bu21029->client, BU21029_AUTOSCAN,
					      माप(buf), buf);
	अगर (error < 0)
		जाओ out;

	bu21029_touch_report(bu21029, buf);

	/* reset समयr क्रम pen up detection */
	mod_समयr(&bu21029->समयr,
		  jअगरfies + msecs_to_jअगरfies(PEN_UP_TIMEOUT_MS));

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bu21029_put_chip_in_reset(काष्ठा bu21029_ts_data *bu21029)
अणु
	अगर (bu21029->reset_gpios) अणु
		gpiod_set_value_cansleep(bu21029->reset_gpios, 1);
		usleep_range(STOP_DELAY_MIN_US, STOP_DELAY_MAX_US);
	पूर्ण
पूर्ण

अटल पूर्णांक bu21029_start_chip(काष्ठा input_dev *dev)
अणु
	काष्ठा bu21029_ts_data *bu21029 = input_get_drvdata(dev);
	काष्ठा i2c_client *i2c = bu21029->client;
	काष्ठा अणु
		u8 reg;
		u8 value;
	पूर्ण init_table[] = अणु
		अणुBU21029_CFR0_REG, CFR0_VALUEपूर्ण,
		अणुBU21029_CFR1_REG, CFR1_VALUEपूर्ण,
		अणुBU21029_CFR2_REG, CFR2_VALUEपूर्ण,
		अणुBU21029_CFR3_REG, CFR3_VALUEपूर्ण,
		अणुBU21029_LDO_REG,  LDO_VALUEपूर्ण
	पूर्ण;
	पूर्णांक error, i;
	__be16 hwid;

	error = regulator_enable(bu21029->vdd);
	अगर (error) अणु
		dev_err(&i2c->dev, "failed to power up chip: %d", error);
		वापस error;
	पूर्ण

	/* take chip out of reset */
	अगर (bu21029->reset_gpios) अणु
		gpiod_set_value_cansleep(bu21029->reset_gpios, 0);
		msleep(START_DELAY_MS);
	पूर्ण

	error = i2c_smbus_पढ़ो_i2c_block_data(i2c, BU21029_HWID_REG,
					      माप(hwid), (u8 *)&hwid);
	अगर (error < 0) अणु
		dev_err(&i2c->dev, "failed to read HW ID\n");
		जाओ err_out;
	पूर्ण

	अगर (be16_to_cpu(hwid) != SUPPORTED_HWID) अणु
		dev_err(&i2c->dev,
			"unsupported HW ID 0x%x\n", be16_to_cpu(hwid));
		error = -ENODEV;
		जाओ err_out;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(init_table); ++i) अणु
		error = i2c_smbus_ग_लिखो_byte_data(i2c,
						  init_table[i].reg,
						  init_table[i].value);
		अगर (error < 0) अणु
			dev_err(&i2c->dev,
				"failed to write %#02x to register %#02x: %d\n",
				init_table[i].value, init_table[i].reg,
				error);
			जाओ err_out;
		पूर्ण
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte(i2c, BU21029_AUTOSCAN);
	अगर (error < 0) अणु
		dev_err(&i2c->dev, "failed to start autoscan\n");
		जाओ err_out;
	पूर्ण

	enable_irq(bu21029->client->irq);
	वापस 0;

err_out:
	bu21029_put_chip_in_reset(bu21029);
	regulator_disable(bu21029->vdd);
	वापस error;
पूर्ण

अटल व्योम bu21029_stop_chip(काष्ठा input_dev *dev)
अणु
	काष्ठा bu21029_ts_data *bu21029 = input_get_drvdata(dev);

	disable_irq(bu21029->client->irq);
	del_समयr_sync(&bu21029->समयr);

	bu21029_put_chip_in_reset(bu21029);
	regulator_disable(bu21029->vdd);
पूर्ण

अटल पूर्णांक bu21029_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bu21029_ts_data *bu21029;
	काष्ठा input_dev *in_dev;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		dev_err(&client->dev,
			"i2c functionality support is not sufficient\n");
		वापस -EIO;
	पूर्ण

	bu21029 = devm_kzalloc(&client->dev, माप(*bu21029), GFP_KERNEL);
	अगर (!bu21029)
		वापस -ENOMEM;

	error = device_property_पढ़ो_u32(&client->dev, "rohm,x-plate-ohms",
					 &bu21029->x_plate_ohms);
	अगर (error) अणु
		dev_err(&client->dev,
			"invalid 'x-plate-ohms' supplied: %d\n", error);
		वापस error;
	पूर्ण

	bu21029->vdd = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(bu21029->vdd)) अणु
		error = PTR_ERR(bu21029->vdd);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to acquire 'vdd' supply: %d\n", error);
		वापस error;
	पूर्ण

	bu21029->reset_gpios = devm_gpiod_get_optional(&client->dev,
						       "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(bu21029->reset_gpios)) अणु
		error = PTR_ERR(bu21029->reset_gpios);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev,
				"failed to acquire 'reset' gpio: %d\n", error);
		वापस error;
	पूर्ण

	in_dev = devm_input_allocate_device(&client->dev);
	अगर (!in_dev) अणु
		dev_err(&client->dev, "unable to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	bu21029->client = client;
	bu21029->in_dev = in_dev;
	समयr_setup(&bu21029->समयr, bu21029_touch_release, 0);

	in_dev->name		= DRIVER_NAME;
	in_dev->id.bustype	= BUS_I2C;
	in_dev->खोलो		= bu21029_start_chip;
	in_dev->बंद		= bu21029_stop_chip;

	input_set_capability(in_dev, EV_KEY, BTN_TOUCH);
	input_set_असल_params(in_dev, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(in_dev, ABS_Y, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(in_dev, ABS_PRESSURE, 0, MAX_12BIT, 0, 0);
	touchscreen_parse_properties(in_dev, false, &bu21029->prop);

	input_set_drvdata(in_dev, bu21029);

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, bu21029_touch_soft_irq,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  DRIVER_NAME, bu21029);
	अगर (error) अणु
		dev_err(&client->dev,
			"unable to request touch irq: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(in_dev);
	अगर (error) अणु
		dev_err(&client->dev,
			"unable to register input device: %d\n", error);
		वापस error;
	पूर्ण

	i2c_set_clientdata(client, bu21029);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bu21029_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा bu21029_ts_data *bu21029 = i2c_get_clientdata(i2c);

	अगर (!device_may_wakeup(dev)) अणु
		mutex_lock(&bu21029->in_dev->mutex);
		अगर (input_device_enabled(bu21029->in_dev))
			bu21029_stop_chip(bu21029->in_dev);
		mutex_unlock(&bu21029->in_dev->mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bu21029_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा bu21029_ts_data *bu21029 = i2c_get_clientdata(i2c);

	अगर (!device_may_wakeup(dev)) अणु
		mutex_lock(&bu21029->in_dev->mutex);
		अगर (input_device_enabled(bu21029->in_dev))
			bu21029_start_chip(bu21029->in_dev);
		mutex_unlock(&bu21029->in_dev->mutex);
	पूर्ण

	वापस 0;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(bu21029_pm_ops, bu21029_suspend, bu21029_resume);

अटल स्थिर काष्ठा i2c_device_id bu21029_ids[] = अणु
	अणु DRIVER_NAME, 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bu21029_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bu21029_of_ids[] = अणु
	अणु .compatible = "rohm,bu21029" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bu21029_of_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver bu21029_driver = अणु
	.driver	= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= of_match_ptr(bu21029_of_ids),
		.pm		= &bu21029_pm_ops,
	पूर्ण,
	.id_table	= bu21029_ids,
	.probe		= bu21029_probe,
पूर्ण;
module_i2c_driver(bu21029_driver);

MODULE_AUTHOR("Zhu Yi <yi.zhu5@cn.bosch.com>");
MODULE_DESCRIPTION("Rohm BU21029 touchscreen controller driver");
MODULE_LICENSE("GPL v2");
