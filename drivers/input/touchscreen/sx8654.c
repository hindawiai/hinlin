<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Semtech SX8654 I2C touchscreen controller.
 *
 * Copyright (c) 2015 Armadeus Systems
 *	Sथऊbastien Szymanski <sebastien.szymanski@armadeus.com>
 *
 * Using code from:
 *  - sx865x.c
 *	Copyright (c) 2013 U-MoBo Srl
 *	Pierluigi Passaro <p.passaro@u-mobo.com>
 *  - sx8650.c
 *      Copyright (c) 2009 Wayne Roberts
 *  - tsc2007.c
 *      Copyright (c) 2008 Kwangwoo Lee
 *  - ads7846.c
 *      Copyright (c) 2005 David Brownell
 *      Copyright (c) 2006 Nokia Corporation
 *  - corgi_ts.c
 *      Copyright (C) 2004-2005 Riअक्षरd Purdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *      Copyright (C) 2002 MontaVista Software
 *      Copyright (C) 2004 Texas Instruments
 *      Copyright (C) 2005 Dirk Behme
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

/* रेजिस्टर addresses */
#घोषणा I2C_REG_TOUCH0			0x00
#घोषणा I2C_REG_TOUCH1			0x01
#घोषणा I2C_REG_CHANMASK		0x04
#घोषणा I2C_REG_IRQMASK			0x22
#घोषणा I2C_REG_IRQSRC			0x23
#घोषणा I2C_REG_SOFTRESET		0x3f

#घोषणा I2C_REG_SX8650_STAT		0x05
#घोषणा SX8650_STAT_CONVIRQ		BIT(7)

/* commands */
#घोषणा CMD_READ_REGISTER		0x40
#घोषणा CMD_PENTRG			0xe0

/* value क्रम I2C_REG_SOFTRESET */
#घोषणा SOFTRESET_VALUE			0xde

/* bits क्रम I2C_REG_IRQSRC */
#घोषणा IRQ_PENTOUCH_TOUCHCONVDONE	BIT(3)
#घोषणा IRQ_PENRELEASE			BIT(2)

/* bits क्रम RegTouch1 */
#घोषणा CONसूचीQ				0x20
#घोषणा RPDNT_100K			0x00
#घोषणा FILT_7SA			0x03

/* bits क्रम I2C_REG_CHANMASK */
#घोषणा CONV_X				BIT(7)
#घोषणा CONV_Y				BIT(6)

/* coordinates rate: higher nibble of CTRL0 रेजिस्टर */
#घोषणा RATE_MANUAL			0x00
#घोषणा RATE_5000CPS			0xf0

/* घातer delay: lower nibble of CTRL0 रेजिस्टर */
#घोषणा POWDLY_1_1MS			0x0b

/* क्रम sx8650, as we have no pen release IRQ there: समयout in ns following the
 * last PENIRQ after which we assume the pen is lअगरted.
 */
#घोषणा SX8650_PENIRQ_TIMEOUT		msecs_to_jअगरfies(10)

#घोषणा MAX_12BIT			((1 << 12) - 1)
#घोषणा MAX_I2C_READ_LEN		10 /* see datasheet section 5.1.5 */

/* channel definition */
#घोषणा CH_X				0x00
#घोषणा CH_Y				0x01

काष्ठा sx865x_data अणु
	u8 cmd_manual;
	u8 chan_mask;
	bool has_irq_penrelease;
	bool has_reg_irqmask;
	irq_handler_t irqh;
पूर्ण;

काष्ठा sx8654 अणु
	काष्ठा input_dev *input;
	काष्ठा i2c_client *client;
	काष्ठा gpio_desc *gpio_reset;

	spinlock_t lock;	/* क्रम input reporting from irq/समयr */
	काष्ठा समयr_list समयr;

	काष्ठा touchscreen_properties props;

	स्थिर काष्ठा sx865x_data *data;
पूर्ण;

अटल अंतरभूत व्योम sx865x_penrelease(काष्ठा sx8654 *ts)
अणु
	काष्ठा input_dev *input_dev = ts->input;

	input_report_key(input_dev, BTN_TOUCH, 0);
	input_sync(input_dev);
पूर्ण

अटल व्योम sx865x_penrelease_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा sx8654 *ts = from_समयr(ts, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ts->lock, flags);
	sx865x_penrelease(ts);
	spin_unlock_irqrestore(&ts->lock, flags);
	dev_dbg(&ts->client->dev, "penrelease by timer\n");
पूर्ण

अटल irqवापस_t sx8650_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा sx8654 *ts = handle;
	काष्ठा device *dev = &ts->client->dev;
	पूर्णांक len, i;
	अचिन्हित दीर्घ flags;
	u8 stat;
	u16 x, y;
	u16 ch;
	u16 chdata;
	__be16 data[MAX_I2C_READ_LEN / माप(__be16)];
	u8 nchan = hweight32(ts->data->chan_mask);
	u8 पढ़ोlen = nchan * माप(*data);

	stat = i2c_smbus_पढ़ो_byte_data(ts->client, CMD_READ_REGISTER
						    | I2C_REG_SX8650_STAT);

	अगर (!(stat & SX8650_STAT_CONVIRQ)) अणु
		dev_dbg(dev, "%s ignore stat [0x%02x]", __func__, stat);
		वापस IRQ_HANDLED;
	पूर्ण

	len = i2c_master_recv(ts->client, (u8 *)data, पढ़ोlen);
	अगर (len != पढ़ोlen) अणु
		dev_dbg(dev, "ignore short recv (%d)\n", len);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_lock_irqsave(&ts->lock, flags);

	x = 0;
	y = 0;
	क्रम (i = 0; i < nchan; i++) अणु
		chdata = be16_to_cpu(data[i]);

		अगर (unlikely(chdata == 0xFFFF)) अणु
			dev_dbg(dev, "invalid qualified data @ %d\n", i);
			जारी;
		पूर्ण अन्यथा अगर (unlikely(chdata & 0x8000)) अणु
			dev_warn(dev, "hibit @ %d [0x%04x]\n", i, chdata);
			जारी;
		पूर्ण

		ch = chdata >> 12;
		अगर (ch == CH_X)
			x = chdata & MAX_12BIT;
		अन्यथा अगर (ch == CH_Y)
			y = chdata & MAX_12BIT;
		अन्यथा
			dev_warn(dev, "unknown channel %d [0x%04x]\n", ch,
				 chdata);
	पूर्ण

	touchscreen_report_pos(ts->input, &ts->props, x, y, false);
	input_report_key(ts->input, BTN_TOUCH, 1);
	input_sync(ts->input);
	dev_dbg(dev, "point(%4d,%4d)\n", x, y);

	mod_समयr(&ts->समयr, jअगरfies + SX8650_PENIRQ_TIMEOUT);
	spin_unlock_irqrestore(&ts->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sx8654_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा sx8654 *sx8654 = handle;
	पूर्णांक irqsrc;
	u8 data[4];
	अचिन्हित पूर्णांक x, y;
	पूर्णांक retval;

	irqsrc = i2c_smbus_पढ़ो_byte_data(sx8654->client,
					  CMD_READ_REGISTER | I2C_REG_IRQSRC);
	dev_dbg(&sx8654->client->dev, "irqsrc = 0x%x", irqsrc);

	अगर (irqsrc < 0)
		जाओ out;

	अगर (irqsrc & IRQ_PENRELEASE) अणु
		dev_dbg(&sx8654->client->dev, "pen release interrupt");

		input_report_key(sx8654->input, BTN_TOUCH, 0);
		input_sync(sx8654->input);
	पूर्ण

	अगर (irqsrc & IRQ_PENTOUCH_TOUCHCONVDONE) अणु
		dev_dbg(&sx8654->client->dev, "pen touch interrupt");

		retval = i2c_master_recv(sx8654->client, data, माप(data));
		अगर (retval != माप(data))
			जाओ out;

		/* invalid data */
		अगर (unlikely(data[0] & 0x80 || data[2] & 0x80))
			जाओ out;

		x = ((data[0] & 0xf) << 8) | (data[1]);
		y = ((data[2] & 0xf) << 8) | (data[3]);

		touchscreen_report_pos(sx8654->input, &sx8654->props, x, y,
				       false);
		input_report_key(sx8654->input, BTN_TOUCH, 1);
		input_sync(sx8654->input);

		dev_dbg(&sx8654->client->dev, "point(%4d,%4d)\n", x, y);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sx8654_reset(काष्ठा sx8654 *ts)
अणु
	पूर्णांक err;

	अगर (ts->gpio_reset) अणु
		gpiod_set_value_cansleep(ts->gpio_reset, 1);
		udelay(2); /* Tpulse > 1तगs */
		gpiod_set_value_cansleep(ts->gpio_reset, 0);
	पूर्ण अन्यथा अणु
		dev_dbg(&ts->client->dev, "NRST unavailable, try softreset\n");
		err = i2c_smbus_ग_लिखो_byte_data(ts->client, I2C_REG_SOFTRESET,
						SOFTRESET_VALUE);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sx8654_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा sx8654 *sx8654 = input_get_drvdata(dev);
	काष्ठा i2c_client *client = sx8654->client;
	पूर्णांक error;

	/* enable pen trigger mode */
	error = i2c_smbus_ग_लिखो_byte_data(client, I2C_REG_TOUCH0,
					  RATE_5000CPS | POWDLY_1_1MS);
	अगर (error) अणु
		dev_err(&client->dev, "writing to I2C_REG_TOUCH0 failed");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte(client, CMD_PENTRG);
	अगर (error) अणु
		dev_err(&client->dev, "writing command CMD_PENTRG failed");
		वापस error;
	पूर्ण

	enable_irq(client->irq);

	वापस 0;
पूर्ण

अटल व्योम sx8654_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा sx8654 *sx8654 = input_get_drvdata(dev);
	काष्ठा i2c_client *client = sx8654->client;
	पूर्णांक error;

	disable_irq(client->irq);

	अगर (!sx8654->data->has_irq_penrelease)
		del_समयr_sync(&sx8654->समयr);

	/* enable manual mode mode */
	error = i2c_smbus_ग_लिखो_byte(client, sx8654->data->cmd_manual);
	अगर (error) अणु
		dev_err(&client->dev, "writing command CMD_MANUAL failed");
		वापस;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, I2C_REG_TOUCH0, RATE_MANUAL);
	अगर (error) अणु
		dev_err(&client->dev, "writing to I2C_REG_TOUCH0 failed");
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक sx8654_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sx8654 *sx8654;
	काष्ठा input_dev *input;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -ENXIO;

	sx8654 = devm_kzalloc(&client->dev, माप(*sx8654), GFP_KERNEL);
	अगर (!sx8654)
		वापस -ENOMEM;

	sx8654->gpio_reset = devm_gpiod_get_optional(&client->dev, "reset",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(sx8654->gpio_reset)) अणु
		error = PTR_ERR(sx8654->gpio_reset);
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev, "unable to get reset-gpio: %d\n",
				error);
		वापस error;
	पूर्ण
	dev_dbg(&client->dev, "got GPIO reset pin\n");

	sx8654->data = device_get_match_data(&client->dev);
	अगर (!sx8654->data)
		sx8654->data = (स्थिर काष्ठा sx865x_data *)id->driver_data;
	अगर (!sx8654->data) अणु
		dev_err(&client->dev, "invalid or missing device data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!sx8654->data->has_irq_penrelease) अणु
		dev_dbg(&client->dev, "use timer for penrelease\n");
		समयr_setup(&sx8654->समयr, sx865x_penrelease_समयr_handler, 0);
		spin_lock_init(&sx8654->lock);
	पूर्ण

	input = devm_input_allocate_device(&client->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "SX8654 I2C Touchscreen";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;
	input->खोलो = sx8654_खोलो;
	input->बंद = sx8654_बंद;

	__set_bit(INPUT_PROP_सूचीECT, input->propbit);
	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input, ABS_X, 0, MAX_12BIT, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, MAX_12BIT, 0, 0);

	touchscreen_parse_properties(input, false, &sx8654->props);

	sx8654->client = client;
	sx8654->input = input;

	input_set_drvdata(sx8654->input, sx8654);

	error = sx8654_reset(sx8654);
	अगर (error) अणु
		dev_err(&client->dev, "reset failed");
		वापस error;
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, I2C_REG_CHANMASK,
					  sx8654->data->chan_mask);
	अगर (error) अणु
		dev_err(&client->dev, "writing to I2C_REG_CHANMASK failed");
		वापस error;
	पूर्ण

	अगर (sx8654->data->has_reg_irqmask) अणु
		error = i2c_smbus_ग_लिखो_byte_data(client, I2C_REG_IRQMASK,
						  IRQ_PENTOUCH_TOUCHCONVDONE |
							IRQ_PENRELEASE);
		अगर (error) अणु
			dev_err(&client->dev, "writing I2C_REG_IRQMASK failed");
			वापस error;
		पूर्ण
	पूर्ण

	error = i2c_smbus_ग_लिखो_byte_data(client, I2C_REG_TOUCH1,
					  CONसूचीQ | RPDNT_100K | FILT_7SA);
	अगर (error) अणु
		dev_err(&client->dev, "writing to I2C_REG_TOUCH1 failed");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, sx8654->data->irqh,
					  IRQF_ONESHOT,
					  client->name, sx8654);
	अगर (error) अणु
		dev_err(&client->dev,
			"Failed to enable IRQ %d, error: %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	/* Disable the IRQ, we'll enable it in sx8654_खोलो() */
	disable_irq(client->irq);

	error = input_रेजिस्टर_device(sx8654->input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sx865x_data sx8650_data = अणु
	.cmd_manual		= 0xb0,
	.has_irq_penrelease	= false,
	.has_reg_irqmask	= false,
	.chan_mask		= (CONV_X | CONV_Y),
	.irqh			= sx8650_irq,
पूर्ण;

अटल स्थिर काष्ठा sx865x_data sx8654_data = अणु
	.cmd_manual		= 0xc0,
	.has_irq_penrelease	= true,
	.has_reg_irqmask	= true,
	.chan_mask		= (CONV_X | CONV_Y),
	.irqh			= sx8654_irq,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sx8654_of_match[] = अणु
	अणु
		.compatible = "semtech,sx8650",
		.data = &sx8650_data,
	पूर्ण, अणु
		.compatible = "semtech,sx8654",
		.data = &sx8654_data,
	पूर्ण, अणु
		.compatible = "semtech,sx8655",
		.data = &sx8654_data,
	पूर्ण, अणु
		.compatible = "semtech,sx8656",
		.data = &sx8654_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sx8654_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id sx8654_id_table[] = अणु
	अणु .name = "semtech_sx8650", .driver_data = (दीर्घ)&sx8650_data पूर्ण,
	अणु .name = "semtech_sx8654", .driver_data = (दीर्घ)&sx8654_data पूर्ण,
	अणु .name = "semtech_sx8655", .driver_data = (दीर्घ)&sx8654_data पूर्ण,
	अणु .name = "semtech_sx8656", .driver_data = (दीर्घ)&sx8654_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sx8654_id_table);

अटल काष्ठा i2c_driver sx8654_driver = अणु
	.driver = अणु
		.name = "sx8654",
		.of_match_table = of_match_ptr(sx8654_of_match),
	पूर्ण,
	.id_table = sx8654_id_table,
	.probe = sx8654_probe,
पूर्ण;
module_i2c_driver(sx8654_driver);

MODULE_AUTHOR("Sथऊbastien Szymanski <sebastien.szymanski@armadeus.com>");
MODULE_DESCRIPTION("Semtech SX8654 I2C Touchscreen Driver");
MODULE_LICENSE("GPL");
