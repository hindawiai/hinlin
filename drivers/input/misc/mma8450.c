<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Freescale's 3-Axis Accelerometer MMA8450
 *
 *  Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/of_device.h>

#घोषणा MMA8450_DRV_NAME	"mma8450"

#घोषणा MODE_CHANGE_DELAY_MS	100
#घोषणा POLL_INTERVAL		100
#घोषणा POLL_INTERVAL_MAX	500

/* रेजिस्टर definitions */
#घोषणा MMA8450_STATUS		0x00
#घोषणा MMA8450_STATUS_ZXYDR	0x08

#घोषणा MMA8450_OUT_X8		0x01
#घोषणा MMA8450_OUT_Y8		0x02
#घोषणा MMA8450_OUT_Z8		0x03

#घोषणा MMA8450_OUT_X_LSB	0x05
#घोषणा MMA8450_OUT_X_MSB	0x06
#घोषणा MMA8450_OUT_Y_LSB	0x07
#घोषणा MMA8450_OUT_Y_MSB	0x08
#घोषणा MMA8450_OUT_Z_LSB	0x09
#घोषणा MMA8450_OUT_Z_MSB	0x0a

#घोषणा MMA8450_XYZ_DATA_CFG	0x16

#घोषणा MMA8450_CTRL_REG1	0x38
#घोषणा MMA8450_CTRL_REG2	0x39

अटल पूर्णांक mma8450_पढ़ो(काष्ठा i2c_client *c, अचिन्हित पूर्णांक off)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(c, off);
	अगर (ret < 0)
		dev_err(&c->dev,
			"failed to read register 0x%02x, error %d\n",
			off, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mma8450_ग_लिखो(काष्ठा i2c_client *c, अचिन्हित पूर्णांक off, u8 v)
अणु
	पूर्णांक error;

	error = i2c_smbus_ग_लिखो_byte_data(c, off, v);
	अगर (error < 0) अणु
		dev_err(&c->dev,
			"failed to write to register 0x%02x, error %d\n",
			off, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mma8450_पढ़ो_block(काष्ठा i2c_client *c, अचिन्हित पूर्णांक off,
			      u8 *buf, माप_प्रकार size)
अणु
	पूर्णांक err;

	err = i2c_smbus_पढ़ो_i2c_block_data(c, off, size, buf);
	अगर (err < 0) अणु
		dev_err(&c->dev,
			"failed to read block data at 0x%02x, error %d\n",
			MMA8450_OUT_X_LSB, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mma8450_poll(काष्ठा input_dev *input)
अणु
	काष्ठा i2c_client *c = input_get_drvdata(input);
	पूर्णांक x, y, z;
	पूर्णांक ret;
	u8 buf[6];

	ret = mma8450_पढ़ो(c, MMA8450_STATUS);
	अगर (ret < 0)
		वापस;

	अगर (!(ret & MMA8450_STATUS_ZXYDR))
		वापस;

	ret = mma8450_पढ़ो_block(c, MMA8450_OUT_X_LSB, buf, माप(buf));
	अगर (ret < 0)
		वापस;

	x = ((पूर्णांक)(s8)buf[1] << 4) | (buf[0] & 0xf);
	y = ((पूर्णांक)(s8)buf[3] << 4) | (buf[2] & 0xf);
	z = ((पूर्णांक)(s8)buf[5] << 4) | (buf[4] & 0xf);

	input_report_असल(input, ABS_X, x);
	input_report_असल(input, ABS_Y, y);
	input_report_असल(input, ABS_Z, z);
	input_sync(input);
पूर्ण

/* Initialize the MMA8450 chip */
अटल पूर्णांक mma8450_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा i2c_client *c = input_get_drvdata(input);
	पूर्णांक err;

	/* enable all events from X/Y/Z, no FIFO */
	err = mma8450_ग_लिखो(c, MMA8450_XYZ_DATA_CFG, 0x07);
	अगर (err)
		वापस err;

	/*
	 * Sleep mode poll rate - 50Hz
	 * System output data rate - 400Hz
	 * Full scale selection - Active, +/- 2G
	 */
	err = mma8450_ग_लिखो(c, MMA8450_CTRL_REG1, 0x01);
	अगर (err)
		वापस err;

	msleep(MODE_CHANGE_DELAY_MS);
	वापस 0;
पूर्ण

अटल व्योम mma8450_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा i2c_client *c = input_get_drvdata(input);

	mma8450_ग_लिखो(c, MMA8450_CTRL_REG1, 0x00);
	mma8450_ग_लिखो(c, MMA8450_CTRL_REG2, 0x01);
पूर्ण

/*
 * I2C init/probing/निकास functions
 */
अटल पूर्णांक mma8450_probe(काष्ठा i2c_client *c,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा input_dev *input;
	पूर्णांक err;

	input = devm_input_allocate_device(&c->dev);
	अगर (!input)
		वापस -ENOMEM;

	input_set_drvdata(input, c);

	input->name = MMA8450_DRV_NAME;
	input->id.bustype = BUS_I2C;

	input->खोलो = mma8450_खोलो;
	input->बंद = mma8450_बंद;

	input_set_असल_params(input, ABS_X, -2048, 2047, 32, 32);
	input_set_असल_params(input, ABS_Y, -2048, 2047, 32, 32);
	input_set_असल_params(input, ABS_Z, -2048, 2047, 32, 32);

	err = input_setup_polling(input, mma8450_poll);
	अगर (err) अणु
		dev_err(&c->dev, "failed to set up polling\n");
		वापस err;
	पूर्ण

	input_set_poll_पूर्णांकerval(input, POLL_INTERVAL);
	input_set_max_poll_पूर्णांकerval(input, POLL_INTERVAL_MAX);

	err = input_रेजिस्टर_device(input);
	अगर (err) अणु
		dev_err(&c->dev, "failed to register input device\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mma8450_id[] = अणु
	अणु MMA8450_DRV_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mma8450_id);

अटल स्थिर काष्ठा of_device_id mma8450_dt_ids[] = अणु
	अणु .compatible = "fsl,mma8450", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mma8450_dt_ids);

अटल काष्ठा i2c_driver mma8450_driver = अणु
	.driver = अणु
		.name	= MMA8450_DRV_NAME,
		.of_match_table = mma8450_dt_ids,
	पूर्ण,
	.probe		= mma8450_probe,
	.id_table	= mma8450_id,
पूर्ण;

module_i2c_driver(mma8450_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("MMA8450 3-Axis Accelerometer Driver");
MODULE_LICENSE("GPL");
