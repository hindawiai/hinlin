<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम cypress touch screen controller
 *
 * Copyright (c) 2009 Aava Mobile
 *
 * Some cleanups by Alan Cox <alan@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input/cy8cपंचांगg110_pdata.h>

#घोषणा CY8CTMG110_DRIVER_NAME      "cy8ctmg110"

/* Touch coordinates */
#घोषणा CY8CTMG110_X_MIN		0
#घोषणा CY8CTMG110_Y_MIN		0
#घोषणा CY8CTMG110_X_MAX		759
#घोषणा CY8CTMG110_Y_MAX		465


/* cy8cपंचांगg110 रेजिस्टर definitions */
#घोषणा CY8CTMG110_TOUCH_WAKEUP_TIME	0
#घोषणा CY8CTMG110_TOUCH_SLEEP_TIME	2
#घोषणा CY8CTMG110_TOUCH_X1		3
#घोषणा CY8CTMG110_TOUCH_Y1		5
#घोषणा CY8CTMG110_TOUCH_X2		7
#घोषणा CY8CTMG110_TOUCH_Y2		9
#घोषणा CY8CTMG110_FINGERS		11
#घोषणा CY8CTMG110_GESTURE		12
#घोषणा CY8CTMG110_REG_MAX		13


/*
 * The touch driver काष्ठाure.
 */
काष्ठा cy8cपंचांगg110 अणु
	काष्ठा input_dev *input;
	अक्षर phys[32];
	काष्ठा i2c_client *client;
	पूर्णांक reset_pin;
	पूर्णांक irq_pin;
पूर्ण;

/*
 * cy8cपंचांगg110_घातer is the routine that is called when touch hardware
 * will घातered off or on.
 */
अटल व्योम cy8cपंचांगg110_घातer(काष्ठा cy8cपंचांगg110 *ts, bool घातeron)
अणु
	अगर (ts->reset_pin)
		gpio_direction_output(ts->reset_pin, 1 - घातeron);
पूर्ण

अटल पूर्णांक cy8cपंचांगg110_ग_लिखो_regs(काष्ठा cy8cपंचांगg110 *tsc, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर len, अचिन्हित अक्षर *value)
अणु
	काष्ठा i2c_client *client = tsc->client;
	पूर्णांक ret;
	अचिन्हित अक्षर i2c_data[6];

	BUG_ON(len > 5);

	i2c_data[0] = reg;
	स_नकल(i2c_data + 1, value, len);

	ret = i2c_master_send(client, i2c_data, len + 1);
	अगर (ret != len + 1) अणु
		dev_err(&client->dev, "i2c write data cmd failed\n");
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cy8cपंचांगg110_पढ़ो_regs(काष्ठा cy8cपंचांगg110 *tsc,
		अचिन्हित अक्षर *data, अचिन्हित अक्षर len, अचिन्हित अक्षर cmd)
अणु
	काष्ठा i2c_client *client = tsc->client;
	पूर्णांक ret;
	काष्ठा i2c_msg msg[2] = अणु
		/* first ग_लिखो slave position to i2c devices */
		अणु
			.addr = client->addr,
			.len = 1,
			.buf = &cmd
		पूर्ण,
		/* Second पढ़ो data from position */
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = data
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cy8cपंचांगg110_touch_pos(काष्ठा cy8cपंचांगg110 *tsc)
अणु
	काष्ठा input_dev *input = tsc->input;
	अचिन्हित अक्षर reg_p[CY8CTMG110_REG_MAX];
	पूर्णांक x, y;

	स_रखो(reg_p, 0, CY8CTMG110_REG_MAX);

	/* Reading coordinates */
	अगर (cy8cपंचांगg110_पढ़ो_regs(tsc, reg_p, 9, CY8CTMG110_TOUCH_X1) != 0)
		वापस -EIO;

	y = reg_p[2] << 8 | reg_p[3];
	x = reg_p[0] << 8 | reg_p[1];

	/* Number of touch */
	अगर (reg_p[8] == 0) अणु
		input_report_key(input, BTN_TOUCH, 0);
	पूर्ण अन्यथा  अणु
		input_report_key(input, BTN_TOUCH, 1);
		input_report_असल(input, ABS_X, x);
		input_report_असल(input, ABS_Y, y);
	पूर्ण

	input_sync(input);

	वापस 0;
पूर्ण

अटल पूर्णांक cy8cपंचांगg110_set_sleepmode(काष्ठा cy8cपंचांगg110 *ts, bool sleep)
अणु
	अचिन्हित अक्षर reg_p[3];

	अगर (sleep) अणु
		reg_p[0] = 0x00;
		reg_p[1] = 0xff;
		reg_p[2] = 5;
	पूर्ण अन्यथा अणु
		reg_p[0] = 0x10;
		reg_p[1] = 0xff;
		reg_p[2] = 0;
	पूर्ण

	वापस cy8cपंचांगg110_ग_लिखो_regs(ts, CY8CTMG110_TOUCH_WAKEUP_TIME, 3, reg_p);
पूर्ण

अटल irqवापस_t cy8cपंचांगg110_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cy8cपंचांगg110 *tsc = dev_id;

	cy8cपंचांगg110_touch_pos(tsc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cy8cपंचांगg110_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा cy8cपंचांगg110_pdata *pdata = dev_get_platdata(&client->dev);
	काष्ठा cy8cपंचांगg110 *ts;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	/* No pdata no way क्रमward */
	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "no pdata\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -EIO;

	ts = kzalloc(माप(काष्ठा cy8cपंचांगg110), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!ts || !input_dev) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	ts->client = client;
	ts->input = input_dev;
	ts->reset_pin = pdata->reset_pin;
	ts->irq_pin = pdata->irq_pin;

	snम_लिखो(ts->phys, माप(ts->phys),
		 "%s/input0", dev_name(&client->dev));

	input_dev->name = CY8CTMG110_DRIVER_NAME " Touchscreen";
	input_dev->phys = ts->phys;
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_असल_params(input_dev, ABS_X,
			CY8CTMG110_X_MIN, CY8CTMG110_X_MAX, 4, 0);
	input_set_असल_params(input_dev, ABS_Y,
			CY8CTMG110_Y_MIN, CY8CTMG110_Y_MAX, 4, 0);

	अगर (ts->reset_pin) अणु
		err = gpio_request(ts->reset_pin, शून्य);
		अगर (err) अणु
			dev_err(&client->dev,
				"Unable to request GPIO pin %d.\n",
				ts->reset_pin);
			जाओ err_मुक्त_mem;
		पूर्ण
	पूर्ण

	cy8cपंचांगg110_घातer(ts, true);
	cy8cपंचांगg110_set_sleepmode(ts, false);

	err = gpio_request(ts->irq_pin, "touch_irq_key");
	अगर (err < 0) अणु
		dev_err(&client->dev,
			"Failed to request GPIO %d, error %d\n",
			ts->irq_pin, err);
		जाओ err_shutoff_device;
	पूर्ण

	err = gpio_direction_input(ts->irq_pin);
	अगर (err < 0) अणु
		dev_err(&client->dev,
			"Failed to configure input direction for GPIO %d, error %d\n",
			ts->irq_pin, err);
		जाओ err_मुक्त_irq_gpio;
	पूर्ण

	client->irq = gpio_to_irq(ts->irq_pin);
	अगर (client->irq < 0) अणु
		err = client->irq;
		dev_err(&client->dev,
			"Unable to get irq number for GPIO %d, error %d\n",
			ts->irq_pin, err);
		जाओ err_मुक्त_irq_gpio;
	पूर्ण

	err = request_thपढ़ोed_irq(client->irq, शून्य, cy8cपंचांगg110_irq_thपढ़ो,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				   "touch_reset_key", ts);
	अगर (err < 0) अणु
		dev_err(&client->dev,
			"irq %d busy? error %d\n", client->irq, err);
		जाओ err_मुक्त_irq_gpio;
	पूर्ण

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ err_मुक्त_irq;

	i2c_set_clientdata(client, ts);
	device_init_wakeup(&client->dev, 1);
	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(client->irq, ts);
err_मुक्त_irq_gpio:
	gpio_मुक्त(ts->irq_pin);
err_shutoff_device:
	cy8cपंचांगg110_set_sleepmode(ts, true);
	cy8cपंचांगg110_घातer(ts, false);
	अगर (ts->reset_pin)
		gpio_मुक्त(ts->reset_pin);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(ts);
	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused cy8cपंचांगg110_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cy8cपंचांगg110 *ts = i2c_get_clientdata(client);

	अगर (device_may_wakeup(&client->dev))
		enable_irq_wake(client->irq);
	अन्यथा अणु
		cy8cपंचांगg110_set_sleepmode(ts, true);
		cy8cपंचांगg110_घातer(ts, false);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cy8cपंचांगg110_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cy8cपंचांगg110 *ts = i2c_get_clientdata(client);

	अगर (device_may_wakeup(&client->dev))
		disable_irq_wake(client->irq);
	अन्यथा अणु
		cy8cपंचांगg110_घातer(ts, true);
		cy8cपंचांगg110_set_sleepmode(ts, false);
	पूर्ण
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cy8cपंचांगg110_pm, cy8cपंचांगg110_suspend, cy8cपंचांगg110_resume);

अटल पूर्णांक cy8cपंचांगg110_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cy8cपंचांगg110 *ts = i2c_get_clientdata(client);

	cy8cपंचांगg110_set_sleepmode(ts, true);
	cy8cपंचांगg110_घातer(ts, false);

	मुक्त_irq(client->irq, ts);
	input_unरेजिस्टर_device(ts->input);
	gpio_मुक्त(ts->irq_pin);
	अगर (ts->reset_pin)
		gpio_मुक्त(ts->reset_pin);
	kमुक्त(ts);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cy8cपंचांगg110_idtable[] = अणु
	अणु CY8CTMG110_DRIVER_NAME, 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cy8cपंचांगg110_idtable);

अटल काष्ठा i2c_driver cy8cपंचांगg110_driver = अणु
	.driver		= अणु
		.name	= CY8CTMG110_DRIVER_NAME,
		.pm	= &cy8cपंचांगg110_pm,
	पूर्ण,
	.id_table	= cy8cपंचांगg110_idtable,
	.probe		= cy8cपंचांगg110_probe,
	.हटाओ		= cy8cपंचांगg110_हटाओ,
पूर्ण;

module_i2c_driver(cy8cपंचांगg110_driver);

MODULE_AUTHOR("Samuli Konttila <samuli.konttila@aavamobile.com>");
MODULE_DESCRIPTION("cy8ctmg110 TouchScreen Driver");
MODULE_LICENSE("GPL v2");
