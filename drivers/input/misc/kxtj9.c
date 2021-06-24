<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Kionix, Inc.
 * Written by Chris Hudson <chudson@kionix.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input/kxtj9.h>

#घोषणा NAME			"kxtj9"
#घोषणा G_MAX			8000
/* OUTPUT REGISTERS */
#घोषणा XOUT_L			0x06
#घोषणा WHO_AM_I		0x0F
/* CONTROL REGISTERS */
#घोषणा INT_REL			0x1A
#घोषणा CTRL_REG1		0x1B
#घोषणा INT_CTRL1		0x1E
#घोषणा DATA_CTRL		0x21
/* CONTROL REGISTER 1 BITS */
#घोषणा PC1_OFF			0x7F
#घोषणा PC1_ON			(1 << 7)
/* Data पढ़ोy funtion enable bit: set during probe अगर using irq mode */
#घोषणा DRDYE			(1 << 5)
/* DATA CONTROL REGISTER BITS */
#घोषणा ODR12_5F		0
#घोषणा ODR25F			1
#घोषणा ODR50F			2
#घोषणा ODR100F		3
#घोषणा ODR200F		4
#घोषणा ODR400F		5
#घोषणा ODR800F		6
/* INTERRUPT CONTROL REGISTER 1 BITS */
/* Set these during probe अगर using irq mode */
#घोषणा KXTJ9_IEL		(1 << 3)
#घोषणा KXTJ9_IEA		(1 << 4)
#घोषणा KXTJ9_IEN		(1 << 5)
/* INPUT_ABS CONSTANTS */
#घोषणा FUZZ			3
#घोषणा FLAT			3
/* RESUME STATE INDICES */
#घोषणा RES_DATA_CTRL		0
#घोषणा RES_CTRL_REG1		1
#घोषणा RES_INT_CTRL1		2
#घोषणा RESUME_ENTRIES		3

/*
 * The following table lists the maximum appropriate poll पूर्णांकerval क्रम each
 * available output data rate.
 */
अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक cutoff;
	u8 mask;
पूर्ण kxtj9_odr_table[] = अणु
	अणु 3,	ODR800F पूर्ण,
	अणु 5,	ODR400F पूर्ण,
	अणु 10,	ODR200F पूर्ण,
	अणु 20,	ODR100F पूर्ण,
	अणु 40,	ODR50F  पूर्ण,
	अणु 80,	ODR25F  पूर्ण,
	अणु 0,	ODR12_5Fपूर्ण,
पूर्ण;

काष्ठा kxtj9_data अणु
	काष्ठा i2c_client *client;
	काष्ठा kxtj9_platक्रमm_data pdata;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक last_poll_पूर्णांकerval;
	u8 shअगरt;
	u8 ctrl_reg1;
	u8 data_ctrl;
	u8 पूर्णांक_ctrl;
पूर्ण;

अटल पूर्णांक kxtj9_i2c_पढ़ो(काष्ठा kxtj9_data *tj9, u8 addr, u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = tj9->client->addr,
			.flags = tj9->client->flags,
			.len = 1,
			.buf = &addr,
		पूर्ण,
		अणु
			.addr = tj9->client->addr,
			.flags = tj9->client->flags | I2C_M_RD,
			.len = len,
			.buf = data,
		पूर्ण,
	पूर्ण;

	वापस i2c_transfer(tj9->client->adapter, msgs, 2);
पूर्ण

अटल व्योम kxtj9_report_acceleration_data(काष्ठा kxtj9_data *tj9)
अणु
	s16 acc_data[3]; /* Data bytes from hardware xL, xH, yL, yH, zL, zH */
	s16 x, y, z;
	पूर्णांक err;

	err = kxtj9_i2c_पढ़ो(tj9, XOUT_L, (u8 *)acc_data, 6);
	अगर (err < 0)
		dev_err(&tj9->client->dev, "accelerometer data read failed\n");

	x = le16_to_cpu(acc_data[tj9->pdata.axis_map_x]);
	y = le16_to_cpu(acc_data[tj9->pdata.axis_map_y]);
	z = le16_to_cpu(acc_data[tj9->pdata.axis_map_z]);

	x >>= tj9->shअगरt;
	y >>= tj9->shअगरt;
	z >>= tj9->shअगरt;

	input_report_असल(tj9->input_dev, ABS_X, tj9->pdata.negate_x ? -x : x);
	input_report_असल(tj9->input_dev, ABS_Y, tj9->pdata.negate_y ? -y : y);
	input_report_असल(tj9->input_dev, ABS_Z, tj9->pdata.negate_z ? -z : z);
	input_sync(tj9->input_dev);
पूर्ण

अटल irqवापस_t kxtj9_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा kxtj9_data *tj9 = dev;
	पूर्णांक err;

	/* data पढ़ोy is the only possible पूर्णांकerrupt type */
	kxtj9_report_acceleration_data(tj9);

	err = i2c_smbus_पढ़ो_byte_data(tj9->client, INT_REL);
	अगर (err < 0)
		dev_err(&tj9->client->dev,
			"error clearing interrupt status: %d\n", err);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक kxtj9_update_g_range(काष्ठा kxtj9_data *tj9, u8 new_g_range)
अणु
	चयन (new_g_range) अणु
	हाल KXTJ9_G_2G:
		tj9->shअगरt = 4;
		अवरोध;
	हाल KXTJ9_G_4G:
		tj9->shअगरt = 3;
		अवरोध;
	हाल KXTJ9_G_8G:
		tj9->shअगरt = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	tj9->ctrl_reg1 &= 0xe7;
	tj9->ctrl_reg1 |= new_g_range;

	वापस 0;
पूर्ण

अटल पूर्णांक kxtj9_update_odr(काष्ठा kxtj9_data *tj9, अचिन्हित पूर्णांक poll_पूर्णांकerval)
अणु
	पूर्णांक err;
	पूर्णांक i;

	/* Use the lowest ODR that can support the requested poll पूर्णांकerval */
	क्रम (i = 0; i < ARRAY_SIZE(kxtj9_odr_table); i++) अणु
		tj9->data_ctrl = kxtj9_odr_table[i].mask;
		अगर (poll_पूर्णांकerval < kxtj9_odr_table[i].cutoff)
			अवरोध;
	पूर्ण

	err = i2c_smbus_ग_लिखो_byte_data(tj9->client, CTRL_REG1, 0);
	अगर (err < 0)
		वापस err;

	err = i2c_smbus_ग_लिखो_byte_data(tj9->client, DATA_CTRL, tj9->data_ctrl);
	अगर (err < 0)
		वापस err;

	err = i2c_smbus_ग_लिखो_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक kxtj9_device_घातer_on(काष्ठा kxtj9_data *tj9)
अणु
	अगर (tj9->pdata.घातer_on)
		वापस tj9->pdata.घातer_on();

	वापस 0;
पूर्ण

अटल व्योम kxtj9_device_घातer_off(काष्ठा kxtj9_data *tj9)
अणु
	पूर्णांक err;

	tj9->ctrl_reg1 &= PC1_OFF;
	err = i2c_smbus_ग_लिखो_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	अगर (err < 0)
		dev_err(&tj9->client->dev, "soft power off failed\n");

	अगर (tj9->pdata.घातer_off)
		tj9->pdata.घातer_off();
पूर्ण

अटल पूर्णांक kxtj9_enable(काष्ठा kxtj9_data *tj9)
अणु
	पूर्णांक err;

	err = kxtj9_device_घातer_on(tj9);
	अगर (err < 0)
		वापस err;

	/* ensure that PC1 is cleared beक्रमe updating control रेजिस्टरs */
	err = i2c_smbus_ग_लिखो_byte_data(tj9->client, CTRL_REG1, 0);
	अगर (err < 0)
		वापस err;

	/* only ग_लिखो INT_CTRL_REG1 अगर in irq mode */
	अगर (tj9->client->irq) अणु
		err = i2c_smbus_ग_लिखो_byte_data(tj9->client,
						INT_CTRL1, tj9->पूर्णांक_ctrl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = kxtj9_update_g_range(tj9, tj9->pdata.g_range);
	अगर (err < 0)
		वापस err;

	/* turn on outमाला_दो */
	tj9->ctrl_reg1 |= PC1_ON;
	err = i2c_smbus_ग_लिखो_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	अगर (err < 0)
		वापस err;

	err = kxtj9_update_odr(tj9, tj9->last_poll_पूर्णांकerval);
	अगर (err < 0)
		वापस err;

	/* clear initial पूर्णांकerrupt अगर in irq mode */
	अगर (tj9->client->irq) अणु
		err = i2c_smbus_पढ़ो_byte_data(tj9->client, INT_REL);
		अगर (err < 0) अणु
			dev_err(&tj9->client->dev,
				"error clearing interrupt: %d\n", err);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	kxtj9_device_घातer_off(tj9);
	वापस err;
पूर्ण

अटल व्योम kxtj9_disable(काष्ठा kxtj9_data *tj9)
अणु
	kxtj9_device_घातer_off(tj9);
पूर्ण

अटल पूर्णांक kxtj9_input_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा kxtj9_data *tj9 = input_get_drvdata(input);

	वापस kxtj9_enable(tj9);
पूर्ण

अटल व्योम kxtj9_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा kxtj9_data *tj9 = input_get_drvdata(dev);

	kxtj9_disable(tj9);
पूर्ण

/*
 * When IRQ mode is selected, we need to provide an पूर्णांकerface to allow the user
 * to change the output data rate of the part.  For consistency, we are using
 * the set_poll method, which accepts a poll पूर्णांकerval in milliseconds, and then
 * calls update_odr() जबतक passing this value as an argument.  In IRQ mode, the
 * data outमाला_दो will not be पढ़ो AT the requested poll पूर्णांकerval, rather, the
 * lowest ODR that can support the requested पूर्णांकerval.  The client application
 * will be responsible क्रम retrieving data from the input node at the desired
 * पूर्णांकerval.
 */

/* Returns currently selected poll पूर्णांकerval (in ms) */
अटल sमाप_प्रकार kxtj9_get_poll(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा kxtj9_data *tj9 = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d\n", tj9->last_poll_पूर्णांकerval);
पूर्ण

/* Allow users to select a new poll पूर्णांकerval (in ms) */
अटल sमाप_प्रकार kxtj9_set_poll(काष्ठा device *dev, काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा kxtj9_data *tj9 = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = tj9->input_dev;
	अचिन्हित पूर्णांक पूर्णांकerval;
	पूर्णांक error;

	error = kstrtouपूर्णांक(buf, 10, &पूर्णांकerval);
	अगर (error < 0)
		वापस error;

	/* Lock the device to prevent races with खोलो/बंद (and itself) */
	mutex_lock(&input_dev->mutex);

	disable_irq(client->irq);

	/*
	 * Set current पूर्णांकerval to the greater of the minimum पूर्णांकerval or
	 * the requested पूर्णांकerval
	 */
	tj9->last_poll_पूर्णांकerval = max(पूर्णांकerval, tj9->pdata.min_पूर्णांकerval);

	kxtj9_update_odr(tj9, tj9->last_poll_पूर्णांकerval);

	enable_irq(client->irq);
	mutex_unlock(&input_dev->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(poll, S_IRUGO|S_IWUSR, kxtj9_get_poll, kxtj9_set_poll);

अटल काष्ठा attribute *kxtj9_attributes[] = अणु
	&dev_attr_poll.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group kxtj9_attribute_group = अणु
	.attrs = kxtj9_attributes
पूर्ण;

अटल व्योम kxtj9_poll(काष्ठा input_dev *input)
अणु
	काष्ठा kxtj9_data *tj9 = input_get_drvdata(input);
	अचिन्हित पूर्णांक poll_पूर्णांकerval = input_get_poll_पूर्णांकerval(input);

	kxtj9_report_acceleration_data(tj9);

	अगर (poll_पूर्णांकerval != tj9->last_poll_पूर्णांकerval) अणु
		kxtj9_update_odr(tj9, poll_पूर्णांकerval);
		tj9->last_poll_पूर्णांकerval = poll_पूर्णांकerval;
	पूर्ण
पूर्ण

अटल व्योम kxtj9_platक्रमm_निकास(व्योम *data)
अणु
	काष्ठा kxtj9_data *tj9 = data;

	अगर (tj9->pdata.निकास)
		tj9->pdata.निकास();
पूर्ण

अटल पूर्णांक kxtj9_verअगरy(काष्ठा kxtj9_data *tj9)
अणु
	पूर्णांक retval;

	retval = kxtj9_device_घातer_on(tj9);
	अगर (retval < 0)
		वापस retval;

	retval = i2c_smbus_पढ़ो_byte_data(tj9->client, WHO_AM_I);
	अगर (retval < 0) अणु
		dev_err(&tj9->client->dev, "read err int source\n");
		जाओ out;
	पूर्ण

	retval = (retval != 0x07 && retval != 0x08) ? -EIO : 0;

out:
	kxtj9_device_घातer_off(tj9);
	वापस retval;
पूर्ण

अटल पूर्णांक kxtj9_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा kxtj9_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	काष्ठा kxtj9_data *tj9;
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter,
				I2C_FUNC_I2C | I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev, "client is not i2c capable\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&client->dev, "platform data is NULL; exiting\n");
		वापस -EINVAL;
	पूर्ण

	tj9 = devm_kzalloc(&client->dev, माप(*tj9), GFP_KERNEL);
	अगर (!tj9) अणु
		dev_err(&client->dev,
			"failed to allocate memory for module data\n");
		वापस -ENOMEM;
	पूर्ण

	tj9->client = client;
	tj9->pdata = *pdata;

	अगर (pdata->init) अणु
		err = pdata->init();
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = devm_add_action_or_reset(&client->dev, kxtj9_platक्रमm_निकास, tj9);
	अगर (err)
		वापस err;

	err = kxtj9_verअगरy(tj9);
	अगर (err < 0) अणु
		dev_err(&client->dev, "device not recognized\n");
		वापस err;
	पूर्ण

	i2c_set_clientdata(client, tj9);

	tj9->ctrl_reg1 = tj9->pdata.res_12bit | tj9->pdata.g_range;
	tj9->last_poll_पूर्णांकerval = tj9->pdata.init_पूर्णांकerval;

	input_dev = devm_input_allocate_device(&client->dev);
	अगर (!input_dev) अणु
		dev_err(&client->dev, "input device allocate failed\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(input_dev, tj9);
	tj9->input_dev = input_dev;

	input_dev->name = "kxtj9_accel";
	input_dev->id.bustype = BUS_I2C;

	input_dev->खोलो = kxtj9_input_खोलो;
	input_dev->बंद = kxtj9_input_बंद;

	input_set_असल_params(input_dev, ABS_X, -G_MAX, G_MAX, FUZZ, FLAT);
	input_set_असल_params(input_dev, ABS_Y, -G_MAX, G_MAX, FUZZ, FLAT);
	input_set_असल_params(input_dev, ABS_Z, -G_MAX, G_MAX, FUZZ, FLAT);

	अगर (client->irq <= 0) अणु
		err = input_setup_polling(input_dev, kxtj9_poll);
		अगर (err)
			वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		dev_err(&client->dev,
			"unable to register input polled device %s: %d\n",
			input_dev->name, err);
		वापस err;
	पूर्ण

	अगर (client->irq) अणु
		/* If in irq mode, populate INT_CTRL_REG1 and enable DRDY. */
		tj9->पूर्णांक_ctrl |= KXTJ9_IEN | KXTJ9_IEA | KXTJ9_IEL;
		tj9->ctrl_reg1 |= DRDYE;

		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, kxtj9_isr,
						IRQF_TRIGGER_RISING |
							IRQF_ONESHOT,
						"kxtj9-irq", tj9);
		अगर (err) अणु
			dev_err(&client->dev, "request irq failed: %d\n", err);
			वापस err;
		पूर्ण

		err = devm_device_add_group(&client->dev,
					    &kxtj9_attribute_group);
		अगर (err) अणु
			dev_err(&client->dev, "sysfs create failed: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused kxtj9_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा kxtj9_data *tj9 = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = tj9->input_dev;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		kxtj9_disable(tj9);

	mutex_unlock(&input_dev->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused kxtj9_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा kxtj9_data *tj9 = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = tj9->input_dev;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		kxtj9_enable(tj9);

	mutex_unlock(&input_dev->mutex);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(kxtj9_pm_ops, kxtj9_suspend, kxtj9_resume);

अटल स्थिर काष्ठा i2c_device_id kxtj9_id[] = अणु
	अणु NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, kxtj9_id);

अटल काष्ठा i2c_driver kxtj9_driver = अणु
	.driver = अणु
		.name	= NAME,
		.pm	= &kxtj9_pm_ops,
	पूर्ण,
	.probe		= kxtj9_probe,
	.id_table	= kxtj9_id,
पूर्ण;

module_i2c_driver(kxtj9_driver);

MODULE_DESCRIPTION("KXTJ9 accelerometer driver");
MODULE_AUTHOR("Chris Hudson <chudson@kionix.com>");
MODULE_LICENSE("GPL");
