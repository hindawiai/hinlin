<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2010, 2011 Fabien Marteau <fabien.marteau@armadeus.com>
 * Sponsored by ARMadeus Systems
 *
 * Driver क्रम Austria Microप्रणालीs joysticks AS5011
 *
 * TODO:
 *	- Power on the chip when खोलो() and घातer करोwn when बंद()
 *	- Manage घातer mode
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/input/as5011.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_DESC "Driver for Austria Microsystems AS5011 joystick"
#घोषणा MODULE_DEVICE_ALIAS "as5011"

MODULE_AUTHOR("Fabien Marteau <fabien.marteau@armadeus.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/* रेजिस्टरs */
#घोषणा AS5011_CTRL1		0x76
#घोषणा AS5011_CTRL2		0x75
#घोषणा AS5011_XP		0x43
#घोषणा AS5011_XN		0x44
#घोषणा AS5011_YP		0x53
#घोषणा AS5011_YN		0x54
#घोषणा AS5011_X_REG		0x41
#घोषणा AS5011_Y_REG		0x42
#घोषणा AS5011_X_RES_INT	0x51
#घोषणा AS5011_Y_RES_INT	0x52

/* CTRL1 bits */
#घोषणा AS5011_CTRL1_LP_PULSED		0x80
#घोषणा AS5011_CTRL1_LP_ACTIVE		0x40
#घोषणा AS5011_CTRL1_LP_CONTINUE	0x20
#घोषणा AS5011_CTRL1_INT_WUP_EN		0x10
#घोषणा AS5011_CTRL1_INT_ACT_EN		0x08
#घोषणा AS5011_CTRL1_EXT_CLK_EN		0x04
#घोषणा AS5011_CTRL1_SOFT_RST		0x02
#घोषणा AS5011_CTRL1_DATA_VALID		0x01

/* CTRL2 bits */
#घोषणा AS5011_CTRL2_EXT_SAMPLE_EN	0x08
#घोषणा AS5011_CTRL2_RC_BIAS_ON		0x04
#घोषणा AS5011_CTRL2_INV_SPINNING	0x02

#घोषणा AS5011_MAX_AXIS	80
#घोषणा AS5011_MIN_AXIS	(-80)
#घोषणा AS5011_FUZZ	8
#घोषणा AS5011_FLAT	40

काष्ठा as5011_device अणु
	काष्ठा input_dev *input_dev;
	काष्ठा i2c_client *i2c_client;
	अचिन्हित पूर्णांक button_gpio;
	अचिन्हित पूर्णांक button_irq;
	अचिन्हित पूर्णांक axis_irq;
पूर्ण;

अटल पूर्णांक as5011_i2c_ग_लिखो(काष्ठा i2c_client *client,
			    uपूर्णांक8_t aregaddr,
			    uपूर्णांक8_t avalue)
अणु
	uपूर्णांक8_t data[2] = अणु aregaddr, avalue पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.flags = I2C_M_IGNORE_NAK,
		.len = 2,
		.buf = (uपूर्णांक8_t *)data
	पूर्ण;
	पूर्णांक error;

	error = i2c_transfer(client->adapter, &msg, 1);
	वापस error < 0 ? error : 0;
पूर्ण

अटल पूर्णांक as5011_i2c_पढ़ो(काष्ठा i2c_client *client,
			   uपूर्णांक8_t aregaddr, चिन्हित अक्षर *value)
अणु
	uपूर्णांक8_t data[2] = अणु aregaddr पूर्ण;
	काष्ठा i2c_msg msg_set[2] = अणु
		अणु
			.addr = client->addr,
			.flags = I2C_M_REV_सूची_ADDR,
			.len = 1,
			.buf = (uपूर्णांक8_t *)data
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD | I2C_M_NOSTART,
			.len = 1,
			.buf = (uपूर्णांक8_t *)data
		पूर्ण
	पूर्ण;
	पूर्णांक error;

	error = i2c_transfer(client->adapter, msg_set, 2);
	अगर (error < 0)
		वापस error;

	*value = data[0] & 0x80 ? -1 * (1 + ~data[0]) : data[0];
	वापस 0;
पूर्ण

अटल irqवापस_t as5011_button_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा as5011_device *as5011 = dev_id;
	पूर्णांक val = gpio_get_value_cansleep(as5011->button_gpio);

	input_report_key(as5011->input_dev, BTN_JOYSTICK, !val);
	input_sync(as5011->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t as5011_axis_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा as5011_device *as5011 = dev_id;
	पूर्णांक error;
	चिन्हित अक्षर x, y;

	error = as5011_i2c_पढ़ो(as5011->i2c_client, AS5011_X_RES_INT, &x);
	अगर (error < 0)
		जाओ out;

	error = as5011_i2c_पढ़ो(as5011->i2c_client, AS5011_Y_RES_INT, &y);
	अगर (error < 0)
		जाओ out;

	input_report_असल(as5011->input_dev, ABS_X, x);
	input_report_असल(as5011->input_dev, ABS_Y, y);
	input_sync(as5011->input_dev);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक as5011_configure_chip(काष्ठा as5011_device *as5011,
				स्थिर काष्ठा as5011_platक्रमm_data *plat_dat)
अणु
	काष्ठा i2c_client *client = as5011->i2c_client;
	पूर्णांक error;
	चिन्हित अक्षर value;

	/* chip soft reset */
	error = as5011_i2c_ग_लिखो(client, AS5011_CTRL1,
				 AS5011_CTRL1_SOFT_RST);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Soft reset failed\n");
		वापस error;
	पूर्ण

	mdelay(10);

	error = as5011_i2c_ग_लिखो(client, AS5011_CTRL1,
				 AS5011_CTRL1_LP_PULSED |
				 AS5011_CTRL1_LP_ACTIVE |
				 AS5011_CTRL1_INT_ACT_EN);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Power config failed\n");
		वापस error;
	पूर्ण

	error = as5011_i2c_ग_लिखो(client, AS5011_CTRL2,
				 AS5011_CTRL2_INV_SPINNING);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Can't invert spinning\n");
		वापस error;
	पूर्ण

	/* ग_लिखो threshold */
	error = as5011_i2c_ग_लिखो(client, AS5011_XP, plat_dat->xp);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Can't write threshold\n");
		वापस error;
	पूर्ण

	error = as5011_i2c_ग_लिखो(client, AS5011_XN, plat_dat->xn);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Can't write threshold\n");
		वापस error;
	पूर्ण

	error = as5011_i2c_ग_लिखो(client, AS5011_YP, plat_dat->yp);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Can't write threshold\n");
		वापस error;
	पूर्ण

	error = as5011_i2c_ग_लिखो(client, AS5011_YN, plat_dat->yn);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Can't write threshold\n");
		वापस error;
	पूर्ण

	/* to मुक्त irq gpio in chip */
	error = as5011_i2c_पढ़ो(client, AS5011_X_RES_INT, &value);
	अगर (error < 0) अणु
		dev_err(&client->dev, "Can't read i2c X resolution value\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक as5011_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा as5011_platक्रमm_data *plat_data;
	काष्ठा as5011_device *as5011;
	काष्ठा input_dev *input_dev;
	पूर्णांक irq;
	पूर्णांक error;

	plat_data = dev_get_platdata(&client->dev);
	अगर (!plat_data)
		वापस -EINVAL;

	अगर (!plat_data->axis_irq) अणु
		dev_err(&client->dev, "No axis IRQ?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_NOSTART |
				     I2C_FUNC_PROTOCOL_MANGLING)) अणु
		dev_err(&client->dev,
			"need i2c bus that supports protocol mangling\n");
		वापस -ENODEV;
	पूर्ण

	as5011 = kदो_स्मृति(माप(काष्ठा as5011_device), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!as5011 || !input_dev) अणु
		dev_err(&client->dev,
			"Can't allocate memory for device structure\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	as5011->i2c_client = client;
	as5011->input_dev = input_dev;
	as5011->button_gpio = plat_data->button_gpio;
	as5011->axis_irq = plat_data->axis_irq;

	input_dev->name = "Austria Microsystem as5011 joystick";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	input_set_capability(input_dev, EV_KEY, BTN_JOYSTICK);

	input_set_असल_params(input_dev, ABS_X,
		AS5011_MIN_AXIS, AS5011_MAX_AXIS, AS5011_FUZZ, AS5011_FLAT);
	input_set_असल_params(as5011->input_dev, ABS_Y,
		AS5011_MIN_AXIS, AS5011_MAX_AXIS, AS5011_FUZZ, AS5011_FLAT);

	error = gpio_request(as5011->button_gpio, "AS5011 button");
	अगर (error < 0) अणु
		dev_err(&client->dev, "Failed to request button gpio\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	irq = gpio_to_irq(as5011->button_gpio);
	अगर (irq < 0) अणु
		dev_err(&client->dev,
			"Failed to get irq number for button gpio\n");
		error = irq;
		जाओ err_मुक्त_button_gpio;
	पूर्ण

	as5011->button_irq = irq;

	error = request_thपढ़ोed_irq(as5011->button_irq,
				     शून्य, as5011_button_पूर्णांकerrupt,
				     IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				     "as5011_button", as5011);
	अगर (error < 0) अणु
		dev_err(&client->dev,
			"Can't allocate button irq %d\n", as5011->button_irq);
		जाओ err_मुक्त_button_gpio;
	पूर्ण

	error = as5011_configure_chip(as5011, plat_data);
	अगर (error)
		जाओ err_मुक्त_button_irq;

	error = request_thपढ़ोed_irq(as5011->axis_irq, शून्य,
				     as5011_axis_पूर्णांकerrupt,
				     plat_data->axis_irqflags | IRQF_ONESHOT,
				     "as5011_joystick", as5011);
	अगर (error) अणु
		dev_err(&client->dev,
			"Can't allocate axis irq %d\n", plat_data->axis_irq);
		जाओ err_मुक्त_button_irq;
	पूर्ण

	error = input_रेजिस्टर_device(as5011->input_dev);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register input device\n");
		जाओ err_मुक्त_axis_irq;
	पूर्ण

	i2c_set_clientdata(client, as5011);

	वापस 0;

err_मुक्त_axis_irq:
	मुक्त_irq(as5011->axis_irq, as5011);
err_मुक्त_button_irq:
	मुक्त_irq(as5011->button_irq, as5011);
err_मुक्त_button_gpio:
	gpio_मुक्त(as5011->button_gpio);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(as5011);

	वापस error;
पूर्ण

अटल पूर्णांक as5011_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा as5011_device *as5011 = i2c_get_clientdata(client);

	मुक्त_irq(as5011->axis_irq, as5011);
	मुक्त_irq(as5011->button_irq, as5011);
	gpio_मुक्त(as5011->button_gpio);

	input_unरेजिस्टर_device(as5011->input_dev);
	kमुक्त(as5011);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id as5011_id[] = अणु
	अणु MODULE_DEVICE_ALIAS, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, as5011_id);

अटल काष्ठा i2c_driver as5011_driver = अणु
	.driver = अणु
		.name = "as5011",
	पूर्ण,
	.probe		= as5011_probe,
	.हटाओ		= as5011_हटाओ,
	.id_table	= as5011_id,
पूर्ण;

module_i2c_driver(as5011_driver);
