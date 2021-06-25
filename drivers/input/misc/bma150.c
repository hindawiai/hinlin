<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Bosch Sensortec GmbH
 * Copyright (c) 2011 Unixphere
 *
 * This driver adds support क्रम Bosch Sensortec's digital acceleration
 * sensors BMA150 and SMB380.
 * The SMB380 is fully compatible with BMA150 and only dअगरfers in packaging.
 *
 * The datasheet क्रम the BMA150 chip can be found here:
 * http://www.bosch-sensortec.com/content/language1/करोwnloads/BST-BMA150-DS000-07.pdf
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/bma150.h>

#घोषणा ABSMAX_ACC_VAL		0x01FF
#घोषणा ABSMIN_ACC_VAL		-(ABSMAX_ACC_VAL)

/* Each axis is represented by a 2-byte data word */
#घोषणा BMA150_XYZ_DATA_SIZE	6

/* Input poll पूर्णांकerval in milliseconds */
#घोषणा BMA150_POLL_INTERVAL	10
#घोषणा BMA150_POLL_MAX		200
#घोषणा BMA150_POLL_MIN		0

#घोषणा BMA150_MODE_NORMAL	0
#घोषणा BMA150_MODE_SLEEP	2
#घोषणा BMA150_MODE_WAKE_UP	3

/* Data रेजिस्टर addresses */
#घोषणा BMA150_DATA_0_REG	0x00
#घोषणा BMA150_DATA_1_REG	0x01
#घोषणा BMA150_DATA_2_REG	0x02

/* Control रेजिस्टर addresses */
#घोषणा BMA150_CTRL_0_REG	0x0A
#घोषणा BMA150_CTRL_1_REG	0x0B
#घोषणा BMA150_CTRL_2_REG	0x14
#घोषणा BMA150_CTRL_3_REG	0x15

/* Configuration/Setting रेजिस्टर addresses */
#घोषणा BMA150_CFG_0_REG	0x0C
#घोषणा BMA150_CFG_1_REG	0x0D
#घोषणा BMA150_CFG_2_REG	0x0E
#घोषणा BMA150_CFG_3_REG	0x0F
#घोषणा BMA150_CFG_4_REG	0x10
#घोषणा BMA150_CFG_5_REG	0x11

#घोषणा BMA150_CHIP_ID		2
#घोषणा BMA150_CHIP_ID_REG	BMA150_DATA_0_REG

#घोषणा BMA150_ACC_X_LSB_REG	BMA150_DATA_2_REG

#घोषणा BMA150_SLEEP_POS	0
#घोषणा BMA150_SLEEP_MSK	0x01
#घोषणा BMA150_SLEEP_REG	BMA150_CTRL_0_REG

#घोषणा BMA150_BANDWIDTH_POS	0
#घोषणा BMA150_BANDWIDTH_MSK	0x07
#घोषणा BMA150_BANDWIDTH_REG	BMA150_CTRL_2_REG

#घोषणा BMA150_RANGE_POS	3
#घोषणा BMA150_RANGE_MSK	0x18
#घोषणा BMA150_RANGE_REG	BMA150_CTRL_2_REG

#घोषणा BMA150_WAKE_UP_POS	0
#घोषणा BMA150_WAKE_UP_MSK	0x01
#घोषणा BMA150_WAKE_UP_REG	BMA150_CTRL_3_REG

#घोषणा BMA150_SW_RES_POS	1
#घोषणा BMA150_SW_RES_MSK	0x02
#घोषणा BMA150_SW_RES_REG	BMA150_CTRL_0_REG

/* Any-motion पूर्णांकerrupt रेजिस्टर fields */
#घोषणा BMA150_ANY_MOTION_EN_POS	6
#घोषणा BMA150_ANY_MOTION_EN_MSK	0x40
#घोषणा BMA150_ANY_MOTION_EN_REG	BMA150_CTRL_1_REG

#घोषणा BMA150_ANY_MOTION_DUR_POS	6
#घोषणा BMA150_ANY_MOTION_DUR_MSK	0xC0
#घोषणा BMA150_ANY_MOTION_DUR_REG	BMA150_CFG_5_REG

#घोषणा BMA150_ANY_MOTION_THRES_REG	BMA150_CFG_4_REG

/* Advanced पूर्णांकerrupt रेजिस्टर fields */
#घोषणा BMA150_ADV_INT_EN_POS		6
#घोषणा BMA150_ADV_INT_EN_MSK		0x40
#घोषणा BMA150_ADV_INT_EN_REG		BMA150_CTRL_3_REG

/* High-G पूर्णांकerrupt रेजिस्टर fields */
#घोषणा BMA150_HIGH_G_EN_POS		1
#घोषणा BMA150_HIGH_G_EN_MSK		0x02
#घोषणा BMA150_HIGH_G_EN_REG		BMA150_CTRL_1_REG

#घोषणा BMA150_HIGH_G_HYST_POS		3
#घोषणा BMA150_HIGH_G_HYST_MSK		0x38
#घोषणा BMA150_HIGH_G_HYST_REG		BMA150_CFG_5_REG

#घोषणा BMA150_HIGH_G_DUR_REG		BMA150_CFG_3_REG
#घोषणा BMA150_HIGH_G_THRES_REG		BMA150_CFG_2_REG

/* Low-G पूर्णांकerrupt रेजिस्टर fields */
#घोषणा BMA150_LOW_G_EN_POS		0
#घोषणा BMA150_LOW_G_EN_MSK		0x01
#घोषणा BMA150_LOW_G_EN_REG		BMA150_CTRL_1_REG

#घोषणा BMA150_LOW_G_HYST_POS		0
#घोषणा BMA150_LOW_G_HYST_MSK		0x07
#घोषणा BMA150_LOW_G_HYST_REG		BMA150_CFG_5_REG

#घोषणा BMA150_LOW_G_DUR_REG		BMA150_CFG_1_REG
#घोषणा BMA150_LOW_G_THRES_REG		BMA150_CFG_0_REG

काष्ठा bma150_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	u8 mode;
पूर्ण;

/*
 * The settings क्रम the given range, bandwidth and पूर्णांकerrupt features
 * are stated and verअगरied by Bosch Sensortec where they are configured
 * to provide a generic sensitivity perक्रमmance.
 */
अटल स्थिर काष्ठा bma150_cfg शेष_cfg = अणु
	.any_motion_पूर्णांक = 1,
	.hg_पूर्णांक = 1,
	.lg_पूर्णांक = 1,
	.any_motion_dur = 0,
	.any_motion_thres = 0,
	.hg_hyst = 0,
	.hg_dur = 150,
	.hg_thres = 160,
	.lg_hyst = 0,
	.lg_dur = 150,
	.lg_thres = 20,
	.range = BMA150_RANGE_2G,
	.bandwidth = BMA150_BW_50HZ
पूर्ण;

अटल पूर्णांक bma150_ग_लिखो_byte(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	s32 ret;

	/* As per specअगरication, disable irq in between रेजिस्टर ग_लिखोs */
	अगर (client->irq)
		disable_irq_nosync(client->irq);

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

	अगर (client->irq)
		enable_irq(client->irq);

	वापस ret;
पूर्ण

अटल पूर्णांक bma150_set_reg_bits(काष्ठा i2c_client *client,
					पूर्णांक val, पूर्णांक shअगरt, u8 mask, u8 reg)
अणु
	पूर्णांक data;

	data = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (data < 0)
		वापस data;

	data = (data & ~mask) | ((val << shअगरt) & mask);
	वापस bma150_ग_लिखो_byte(client, reg, data);
पूर्ण

अटल पूर्णांक bma150_set_mode(काष्ठा bma150_data *bma150, u8 mode)
अणु
	पूर्णांक error;

	error = bma150_set_reg_bits(bma150->client, mode, BMA150_WAKE_UP_POS,
				BMA150_WAKE_UP_MSK, BMA150_WAKE_UP_REG);
	अगर (error)
		वापस error;

	error = bma150_set_reg_bits(bma150->client, mode, BMA150_SLEEP_POS,
				BMA150_SLEEP_MSK, BMA150_SLEEP_REG);
	अगर (error)
		वापस error;

	अगर (mode == BMA150_MODE_NORMAL)
		usleep_range(2000, 2100);

	bma150->mode = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक bma150_soft_reset(काष्ठा bma150_data *bma150)
अणु
	पूर्णांक error;

	error = bma150_set_reg_bits(bma150->client, 1, BMA150_SW_RES_POS,
				BMA150_SW_RES_MSK, BMA150_SW_RES_REG);
	अगर (error)
		वापस error;

	usleep_range(2000, 2100);
	वापस 0;
पूर्ण

अटल पूर्णांक bma150_set_range(काष्ठा bma150_data *bma150, u8 range)
अणु
	वापस bma150_set_reg_bits(bma150->client, range, BMA150_RANGE_POS,
				BMA150_RANGE_MSK, BMA150_RANGE_REG);
पूर्ण

अटल पूर्णांक bma150_set_bandwidth(काष्ठा bma150_data *bma150, u8 bw)
अणु
	वापस bma150_set_reg_bits(bma150->client, bw, BMA150_BANDWIDTH_POS,
				BMA150_BANDWIDTH_MSK, BMA150_BANDWIDTH_REG);
पूर्ण

अटल पूर्णांक bma150_set_low_g_पूर्णांकerrupt(काष्ठा bma150_data *bma150,
					u8 enable, u8 hyst, u8 dur, u8 thres)
अणु
	पूर्णांक error;

	error = bma150_set_reg_bits(bma150->client, hyst,
				BMA150_LOW_G_HYST_POS, BMA150_LOW_G_HYST_MSK,
				BMA150_LOW_G_HYST_REG);
	अगर (error)
		वापस error;

	error = bma150_ग_लिखो_byte(bma150->client, BMA150_LOW_G_DUR_REG, dur);
	अगर (error)
		वापस error;

	error = bma150_ग_लिखो_byte(bma150->client, BMA150_LOW_G_THRES_REG, thres);
	अगर (error)
		वापस error;

	वापस bma150_set_reg_bits(bma150->client, !!enable,
				BMA150_LOW_G_EN_POS, BMA150_LOW_G_EN_MSK,
				BMA150_LOW_G_EN_REG);
पूर्ण

अटल पूर्णांक bma150_set_high_g_पूर्णांकerrupt(काष्ठा bma150_data *bma150,
					u8 enable, u8 hyst, u8 dur, u8 thres)
अणु
	पूर्णांक error;

	error = bma150_set_reg_bits(bma150->client, hyst,
				BMA150_HIGH_G_HYST_POS, BMA150_HIGH_G_HYST_MSK,
				BMA150_HIGH_G_HYST_REG);
	अगर (error)
		वापस error;

	error = bma150_ग_लिखो_byte(bma150->client,
				BMA150_HIGH_G_DUR_REG, dur);
	अगर (error)
		वापस error;

	error = bma150_ग_लिखो_byte(bma150->client,
				BMA150_HIGH_G_THRES_REG, thres);
	अगर (error)
		वापस error;

	वापस bma150_set_reg_bits(bma150->client, !!enable,
				BMA150_HIGH_G_EN_POS, BMA150_HIGH_G_EN_MSK,
				BMA150_HIGH_G_EN_REG);
पूर्ण


अटल पूर्णांक bma150_set_any_motion_पूर्णांकerrupt(काष्ठा bma150_data *bma150,
						u8 enable, u8 dur, u8 thres)
अणु
	पूर्णांक error;

	error = bma150_set_reg_bits(bma150->client, dur,
				BMA150_ANY_MOTION_DUR_POS,
				BMA150_ANY_MOTION_DUR_MSK,
				BMA150_ANY_MOTION_DUR_REG);
	अगर (error)
		वापस error;

	error = bma150_ग_लिखो_byte(bma150->client,
				BMA150_ANY_MOTION_THRES_REG, thres);
	अगर (error)
		वापस error;

	error = bma150_set_reg_bits(bma150->client, !!enable,
				BMA150_ADV_INT_EN_POS, BMA150_ADV_INT_EN_MSK,
				BMA150_ADV_INT_EN_REG);
	अगर (error)
		वापस error;

	वापस bma150_set_reg_bits(bma150->client, !!enable,
				BMA150_ANY_MOTION_EN_POS,
				BMA150_ANY_MOTION_EN_MSK,
				BMA150_ANY_MOTION_EN_REG);
पूर्ण

अटल व्योम bma150_report_xyz(काष्ठा bma150_data *bma150)
अणु
	u8 data[BMA150_XYZ_DATA_SIZE];
	s16 x, y, z;
	s32 ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(bma150->client,
			BMA150_ACC_X_LSB_REG, BMA150_XYZ_DATA_SIZE, data);
	अगर (ret != BMA150_XYZ_DATA_SIZE)
		वापस;

	x = ((0xc0 & data[0]) >> 6) | (data[1] << 2);
	y = ((0xc0 & data[2]) >> 6) | (data[3] << 2);
	z = ((0xc0 & data[4]) >> 6) | (data[5] << 2);

	x = sign_extend32(x, 9);
	y = sign_extend32(y, 9);
	z = sign_extend32(z, 9);

	input_report_असल(bma150->input, ABS_X, x);
	input_report_असल(bma150->input, ABS_Y, y);
	input_report_असल(bma150->input, ABS_Z, z);
	input_sync(bma150->input);
पूर्ण

अटल irqवापस_t bma150_irq_thपढ़ो(पूर्णांक irq, व्योम *dev)
अणु
	bma150_report_xyz(dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bma150_poll(काष्ठा input_dev *input)
अणु
	काष्ठा bma150_data *bma150 = input_get_drvdata(input);

	bma150_report_xyz(bma150);
पूर्ण

अटल पूर्णांक bma150_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा bma150_data *bma150 = input_get_drvdata(input);
	पूर्णांक error;

	error = pm_runसमय_get_sync(&bma150->client->dev);
	अगर (error < 0 && error != -ENOSYS)
		वापस error;

	/*
	 * See अगर runसमय PM woke up the device. If runसमय PM
	 * is disabled we need to करो it ourselves.
	 */
	अगर (bma150->mode != BMA150_MODE_NORMAL) अणु
		error = bma150_set_mode(bma150, BMA150_MODE_NORMAL);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bma150_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा bma150_data *bma150 = input_get_drvdata(input);

	pm_runसमय_put_sync(&bma150->client->dev);

	अगर (bma150->mode != BMA150_MODE_SLEEP)
		bma150_set_mode(bma150, BMA150_MODE_SLEEP);
पूर्ण

अटल पूर्णांक bma150_initialize(काष्ठा bma150_data *bma150,
			     स्थिर काष्ठा bma150_cfg *cfg)
अणु
	पूर्णांक error;

	error = bma150_soft_reset(bma150);
	अगर (error)
		वापस error;

	error = bma150_set_bandwidth(bma150, cfg->bandwidth);
	अगर (error)
		वापस error;

	error = bma150_set_range(bma150, cfg->range);
	अगर (error)
		वापस error;

	अगर (bma150->client->irq) अणु
		error = bma150_set_any_motion_पूर्णांकerrupt(bma150,
					cfg->any_motion_पूर्णांक,
					cfg->any_motion_dur,
					cfg->any_motion_thres);
		अगर (error)
			वापस error;

		error = bma150_set_high_g_पूर्णांकerrupt(bma150,
					cfg->hg_पूर्णांक, cfg->hg_hyst,
					cfg->hg_dur, cfg->hg_thres);
		अगर (error)
			वापस error;

		error = bma150_set_low_g_पूर्णांकerrupt(bma150,
					cfg->lg_पूर्णांक, cfg->lg_hyst,
					cfg->lg_dur, cfg->lg_thres);
		अगर (error)
			वापस error;
	पूर्ण

	वापस bma150_set_mode(bma150, BMA150_MODE_SLEEP);
पूर्ण

अटल पूर्णांक bma150_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा bma150_platक्रमm_data *pdata =
			dev_get_platdata(&client->dev);
	स्थिर काष्ठा bma150_cfg *cfg;
	काष्ठा bma150_data *bma150;
	काष्ठा input_dev *idev;
	पूर्णांक chip_id;
	पूर्णांक error;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c_check_functionality error\n");
		वापस -EIO;
	पूर्ण

	chip_id = i2c_smbus_पढ़ो_byte_data(client, BMA150_CHIP_ID_REG);
	अगर (chip_id != BMA150_CHIP_ID) अणु
		dev_err(&client->dev, "BMA150 chip id error: %d\n", chip_id);
		वापस -EINVAL;
	पूर्ण

	bma150 = devm_kzalloc(&client->dev, माप(*bma150), GFP_KERNEL);
	अगर (!bma150)
		वापस -ENOMEM;

	bma150->client = client;

	अगर (pdata) अणु
		अगर (pdata->irq_gpio_cfg) अणु
			error = pdata->irq_gpio_cfg();
			अगर (error) अणु
				dev_err(&client->dev,
					"IRQ GPIO conf. error %d, error %d\n",
					client->irq, error);
				वापस error;
			पूर्ण
		पूर्ण
		cfg = &pdata->cfg;
	पूर्ण अन्यथा अणु
		cfg = &शेष_cfg;
	पूर्ण

	error = bma150_initialize(bma150, cfg);
	अगर (error)
		वापस error;

	idev = devm_input_allocate_device(&bma150->client->dev);
	अगर (!idev)
		वापस -ENOMEM;

	input_set_drvdata(idev, bma150);
	bma150->input = idev;

	idev->name = BMA150_DRIVER;
	idev->phys = BMA150_DRIVER "/input0";
	idev->id.bustype = BUS_I2C;

	idev->खोलो = bma150_खोलो;
	idev->बंद = bma150_बंद;

	input_set_असल_params(idev, ABS_X, ABSMIN_ACC_VAL, ABSMAX_ACC_VAL, 0, 0);
	input_set_असल_params(idev, ABS_Y, ABSMIN_ACC_VAL, ABSMAX_ACC_VAL, 0, 0);
	input_set_असल_params(idev, ABS_Z, ABSMIN_ACC_VAL, ABSMAX_ACC_VAL, 0, 0);

	अगर (client->irq <= 0) अणु
		error = input_setup_polling(idev, bma150_poll);
		अगर (error)
			वापस error;

		input_set_poll_पूर्णांकerval(idev, BMA150_POLL_INTERVAL);
		input_set_min_poll_पूर्णांकerval(idev, BMA150_POLL_MIN);
		input_set_max_poll_पूर्णांकerval(idev, BMA150_POLL_MAX);
	पूर्ण

	error = input_रेजिस्टर_device(idev);
	अगर (error)
		वापस error;

	अगर (client->irq > 0) अणु
		error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, bma150_irq_thपढ़ो,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					BMA150_DRIVER, bma150);
		अगर (error) अणु
			dev_err(&client->dev,
				"irq request failed %d, error %d\n",
				client->irq, error);
			वापस error;
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, bma150);

	pm_runसमय_enable(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bma150_हटाओ(काष्ठा i2c_client *client)
अणु
	pm_runसमय_disable(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bma150_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bma150_data *bma150 = i2c_get_clientdata(client);

	वापस bma150_set_mode(bma150, BMA150_MODE_SLEEP);
पूर्ण

अटल पूर्णांक __maybe_unused bma150_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bma150_data *bma150 = i2c_get_clientdata(client);

	वापस bma150_set_mode(bma150, BMA150_MODE_NORMAL);
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(bma150_pm, bma150_suspend, bma150_resume, शून्य);

अटल स्थिर काष्ठा i2c_device_id bma150_id[] = अणु
	अणु "bma150", 0 पूर्ण,
	अणु "smb380", 0 पूर्ण,
	अणु "bma023", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, bma150_id);

अटल काष्ठा i2c_driver bma150_driver = अणु
	.driver = अणु
		.name	= BMA150_DRIVER,
		.pm	= &bma150_pm,
	पूर्ण,
	.class		= I2C_CLASS_HWMON,
	.id_table	= bma150_id,
	.probe		= bma150_probe,
	.हटाओ		= bma150_हटाओ,
पूर्ण;

module_i2c_driver(bma150_driver);

MODULE_AUTHOR("Albert Zhang <xu.zhang@bosch-sensortec.com>");
MODULE_DESCRIPTION("BMA150 driver");
MODULE_LICENSE("GPL");
