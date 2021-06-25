<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम MAXI MAX11801 - A Resistive touch screen controller with
 * i2c पूर्णांकerface
 *
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 * Author: Zhang Jiejing <jiejing.zhang@मुक्तscale.com>
 *
 * Based on mcs5000_ts.c
 */

/*
 * This driver aims to support the series of MAXI touch chips max11801
 * through max11803. The मुख्य dअगरference between these 4 chips can be
 * found in the table below:
 * -----------------------------------------------------
 * | CHIP     |  AUTO MODE SUPPORT(FIFO) | INTERFACE    |
 * |----------------------------------------------------|
 * | max11800 |  YES                     |   SPI        |
 * | max11801 |  YES                     |   I2C        |
 * | max11802 |  NO                      |   SPI        |
 * | max11803 |  NO                      |   I2C        |
 * ------------------------------------------------------
 *
 * Currently, this driver only supports max11801.
 *
 * Data Sheet:
 * http://www.maxim-ic.com/datasheet/index.mvp/id/5943
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>

/* Register Address define */
#घोषणा GENERNAL_STATUS_REG		0x00
#घोषणा GENERNAL_CONF_REG		0x01
#घोषणा MESURE_RES_CONF_REG		0x02
#घोषणा MESURE_AVER_CONF_REG		0x03
#घोषणा ADC_SAMPLE_TIME_CONF_REG	0x04
#घोषणा PANEL_SETUPTIME_CONF_REG	0x05
#घोषणा DELAY_CONVERSION_CONF_REG	0x06
#घोषणा TOUCH_DETECT_PULLUP_CONF_REG	0x07
#घोषणा AUTO_MODE_TIME_CONF_REG		0x08 /* only क्रम max11800/max11801 */
#घोषणा APERTURE_CONF_REG		0x09 /* only क्रम max11800/max11801 */
#घोषणा AUX_MESURE_CONF_REG		0x0a
#घोषणा OP_MODE_CONF_REG		0x0b

/* FIFO is found only in max11800 and max11801 */
#घोषणा FIFO_RD_CMD			(0x50 << 1)
#घोषणा MAX11801_FIFO_INT		(1 << 2)
#घोषणा MAX11801_FIFO_OVERFLOW		(1 << 3)

#घोषणा XY_बफ_मानE			4
#घोषणा XY_BUF_OFFSET			4

#घोषणा MAX11801_MAX_X			0xfff
#घोषणा MAX11801_MAX_Y			0xfff

#घोषणा MEASURE_TAG_OFFSET		2
#घोषणा MEASURE_TAG_MASK		(3 << MEASURE_TAG_OFFSET)
#घोषणा EVENT_TAG_OFFSET		0
#घोषणा EVENT_TAG_MASK			(3 << EVENT_TAG_OFFSET)
#घोषणा MEASURE_X_TAG			(0 << MEASURE_TAG_OFFSET)
#घोषणा MEASURE_Y_TAG			(1 << MEASURE_TAG_OFFSET)

/* These are the state of touch event state machine */
क्रमागत अणु
	EVENT_INIT,
	EVENT_MIDDLE,
	EVENT_RELEASE,
	EVENT_FIFO_END
पूर्ण;

काष्ठा max11801_data अणु
	काष्ठा i2c_client		*client;
	काष्ठा input_dev		*input_dev;
पूर्ण;

अटल u8 पढ़ो_रेजिस्टर(काष्ठा i2c_client *client, पूर्णांक addr)
अणु
	/* XXX: The chip ignores LSB of रेजिस्टर address */
	वापस i2c_smbus_पढ़ो_byte_data(client, addr << 1);
पूर्ण

अटल पूर्णांक max11801_ग_लिखो_reg(काष्ठा i2c_client *client, पूर्णांक addr, पूर्णांक data)
अणु
	/* XXX: The chip ignores LSB of रेजिस्टर address */
	वापस i2c_smbus_ग_लिखो_byte_data(client, addr << 1, data);
पूर्ण

अटल irqवापस_t max11801_ts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max11801_data *data = dev_id;
	काष्ठा i2c_client *client = data->client;
	पूर्णांक status, i, ret;
	u8 buf[XY_बफ_मानE];
	पूर्णांक x = -1;
	पूर्णांक y = -1;

	status = पढ़ो_रेजिस्टर(data->client, GENERNAL_STATUS_REG);

	अगर (status & (MAX11801_FIFO_INT | MAX11801_FIFO_OVERFLOW)) अणु
		status = पढ़ो_रेजिस्टर(data->client, GENERNAL_STATUS_REG);

		ret = i2c_smbus_पढ़ो_i2c_block_data(client, FIFO_RD_CMD,
						    XY_बफ_मानE, buf);

		/*
		 * We should get 4 bytes buffer that contains X,Y
		 * and event tag
		 */
		अगर (ret < XY_बफ_मानE)
			जाओ out;

		क्रम (i = 0; i < XY_बफ_मानE; i += XY_बफ_मानE / 2) अणु
			अगर ((buf[i + 1] & MEASURE_TAG_MASK) == MEASURE_X_TAG)
				x = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
			अन्यथा अगर ((buf[i + 1] & MEASURE_TAG_MASK) == MEASURE_Y_TAG)
				y = (buf[i] << XY_BUF_OFFSET) +
				    (buf[i + 1] >> XY_BUF_OFFSET);
		पूर्ण

		अगर ((buf[1] & EVENT_TAG_MASK) != (buf[3] & EVENT_TAG_MASK))
			जाओ out;

		चयन (buf[1] & EVENT_TAG_MASK) अणु
		हाल EVENT_INIT:
		हाल EVENT_MIDDLE:
			input_report_असल(data->input_dev, ABS_X, x);
			input_report_असल(data->input_dev, ABS_Y, y);
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 1);
			input_sync(data->input_dev);
			अवरोध;

		हाल EVENT_RELEASE:
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 0);
			input_sync(data->input_dev);
			अवरोध;

		हाल EVENT_FIFO_END:
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max11801_ts_phy_init(काष्ठा max11801_data *data)
अणु
	काष्ठा i2c_client *client = data->client;

	/* Average X,Y, take 16 samples, average eight media sample */
	max11801_ग_लिखो_reg(client, MESURE_AVER_CONF_REG, 0xff);
	/* X,Y panel setup समय set to 20us */
	max11801_ग_लिखो_reg(client, PANEL_SETUPTIME_CONF_REG, 0x11);
	/* Rough pullup समय (2uS), Fine pullup समय (10us)  */
	max11801_ग_लिखो_reg(client, TOUCH_DETECT_PULLUP_CONF_REG, 0x10);
	/* Auto mode init period = 5ms , scan period = 5ms*/
	max11801_ग_लिखो_reg(client, AUTO_MODE_TIME_CONF_REG, 0xaa);
	/* Aperture X,Y set to +- 4LSB */
	max11801_ग_लिखो_reg(client, APERTURE_CONF_REG, 0x33);
	/* Enable Power, enable Automode, enable Aperture, enable Average X,Y */
	max11801_ग_लिखो_reg(client, OP_MODE_CONF_REG, 0x36);
पूर्ण

अटल पूर्णांक max11801_ts_probe(काष्ठा i2c_client *client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max11801_data *data;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!data || !input_dev) अणु
		dev_err(&client->dev, "Failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	data->client = client;
	data->input_dev = input_dev;

	input_dev->name = "max11801_ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	input_set_असल_params(input_dev, ABS_X, 0, MAX11801_MAX_X, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, MAX11801_MAX_Y, 0, 0);

	max11801_ts_phy_init(data);

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					  max11801_ts_पूर्णांकerrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "max11801_ts", data);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(data->input_dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max11801_ts_id[] = अणु
	अणु"max11801", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max11801_ts_id);

अटल स्थिर काष्ठा of_device_id max11801_ts_dt_ids[] = अणु
	अणु .compatible = "maxim,max11801" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max11801_ts_dt_ids);

अटल काष्ठा i2c_driver max11801_ts_driver = अणु
	.driver = अणु
		.name	= "max11801_ts",
		.of_match_table = max11801_ts_dt_ids,
	पूर्ण,
	.id_table	= max11801_ts_id,
	.probe		= max11801_ts_probe,
पूर्ण;

module_i2c_driver(max11801_ts_driver);

MODULE_AUTHOR("Zhang Jiejing <jiejing.zhang@freescale.com>");
MODULE_DESCRIPTION("Touchscreen driver for MAXI MAX11801 controller");
MODULE_LICENSE("GPL");
