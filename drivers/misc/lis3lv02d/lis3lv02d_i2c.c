<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/hwmon/lis3lv02d_i2c.c
 *
 * Implements I2C पूर्णांकerface क्रम lis3lv02d (STMicroelectronics) accelerometer.
 * Driver is based on corresponding SPI driver written by Daniel Mack
 * (lis3lv02d_spi.c (C) 2009 Daniel Mack <daniel@caiaq.de> ).
 *
 * Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>

#समावेश "lis3lv02d.h"

#घोषणा DRV_NAME	"lis3lv02d_i2c"

अटल स्थिर अक्षर reg_vdd[]    = "Vdd";
अटल स्थिर अक्षर reg_vdd_io[] = "Vdd_IO";

अटल पूर्णांक lis3_reg_ctrl(काष्ठा lis3lv02d *lis3, bool state)
अणु
	पूर्णांक ret;
	अगर (state == LIS3_REG_OFF) अणु
		ret = regulator_bulk_disable(ARRAY_SIZE(lis3->regulators),
					lis3->regulators);
	पूर्ण अन्यथा अणु
		ret = regulator_bulk_enable(ARRAY_SIZE(lis3->regulators),
					lis3->regulators);
		/* Chip needs समय to wakeup. Not mentioned in datasheet */
		usleep_range(10000, 20000);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत s32 lis3_i2c_ग_लिखो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, u8 value)
अणु
	काष्ठा i2c_client *c = lis3->bus_priv;
	वापस i2c_smbus_ग_लिखो_byte_data(c, reg, value);
पूर्ण

अटल अंतरभूत s32 lis3_i2c_पढ़ो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, u8 *v)
अणु
	काष्ठा i2c_client *c = lis3->bus_priv;
	*v = i2c_smbus_पढ़ो_byte_data(c, reg);
	वापस 0;
पूर्ण

अटल अंतरभूत s32 lis3_i2c_blockपढ़ो(काष्ठा lis3lv02d *lis3, पूर्णांक reg, पूर्णांक len,
				u8 *v)
अणु
	काष्ठा i2c_client *c = lis3->bus_priv;
	reg |= (1 << 7); /* 7th bit enables address स्वतः incrementation */
	वापस i2c_smbus_पढ़ो_i2c_block_data(c, reg, len, v);
पूर्ण

अटल पूर्णांक lis3_i2c_init(काष्ठा lis3lv02d *lis3)
अणु
	u8 reg;
	पूर्णांक ret;

	lis3_reg_ctrl(lis3, LIS3_REG_ON);

	lis3->पढ़ो(lis3, WHO_AM_I, &reg);
	अगर (reg != lis3->whoami)
		prपूर्णांकk(KERN_ERR "lis3: power on failure\n");

	/* घातer up the device */
	ret = lis3->पढ़ो(lis3, CTRL_REG1, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (lis3->whoami == WAI_3DLH)
		reg |= CTRL1_PM0 | CTRL1_Xen | CTRL1_Yen | CTRL1_Zen;
	अन्यथा
		reg |= CTRL1_PD0 | CTRL1_Xen | CTRL1_Yen | CTRL1_Zen;

	वापस lis3->ग_लिखो(lis3, CTRL_REG1, reg);
पूर्ण

/* Default axis mapping but it can be overwritten by platक्रमm data */
अटल जोड़ axis_conversion lis3lv02d_axis_map =
	अणु .as_array = अणु LIS3_DEV_X, LIS3_DEV_Y, LIS3_DEV_Z पूर्ण पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lis3lv02d_i2c_dt_ids[] = अणु
	अणु .compatible = "st,lis3lv02d" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lis3lv02d_i2c_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक lis3lv02d_i2c_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा lis3lv02d_platक्रमm_data *pdata = client->dev.platक्रमm_data;

#अगर_घोषित CONFIG_OF
	अगर (of_match_device(lis3lv02d_i2c_dt_ids, &client->dev)) अणु
		lis3_dev.of_node = client->dev.of_node;
		ret = lis3lv02d_init_dt(&lis3_dev);
		अगर (ret)
			वापस ret;
		pdata = lis3_dev.pdata;
	पूर्ण
#पूर्ण_अगर

	अगर (pdata) अणु
		अगर ((pdata->driver_features & LIS3_USE_BLOCK_READ) &&
			(i2c_check_functionality(client->adapter,
						I2C_FUNC_SMBUS_I2C_BLOCK)))
			lis3_dev.blkपढ़ो  = lis3_i2c_blockपढ़ो;

		अगर (pdata->axis_x)
			lis3lv02d_axis_map.x = pdata->axis_x;

		अगर (pdata->axis_y)
			lis3lv02d_axis_map.y = pdata->axis_y;

		अगर (pdata->axis_z)
			lis3lv02d_axis_map.z = pdata->axis_z;

		अगर (pdata->setup_resources)
			ret = pdata->setup_resources();

		अगर (ret)
			जाओ fail;
	पूर्ण

	lis3_dev.regulators[0].supply = reg_vdd;
	lis3_dev.regulators[1].supply = reg_vdd_io;
	ret = regulator_bulk_get(&client->dev,
				 ARRAY_SIZE(lis3_dev.regulators),
				 lis3_dev.regulators);
	अगर (ret < 0)
		जाओ fail;

	lis3_dev.pdata	  = pdata;
	lis3_dev.bus_priv = client;
	lis3_dev.init	  = lis3_i2c_init;
	lis3_dev.पढ़ो	  = lis3_i2c_पढ़ो;
	lis3_dev.ग_लिखो	  = lis3_i2c_ग_लिखो;
	lis3_dev.irq	  = client->irq;
	lis3_dev.ac	  = lis3lv02d_axis_map;
	lis3_dev.pm_dev	  = &client->dev;

	i2c_set_clientdata(client, &lis3_dev);

	/* Provide घातer over the init call */
	lis3_reg_ctrl(&lis3_dev, LIS3_REG_ON);

	ret = lis3lv02d_init_device(&lis3_dev);

	lis3_reg_ctrl(&lis3_dev, LIS3_REG_OFF);

	अगर (ret)
		जाओ fail2;
	वापस 0;

fail2:
	regulator_bulk_मुक्त(ARRAY_SIZE(lis3_dev.regulators),
				lis3_dev.regulators);
fail:
	अगर (pdata && pdata->release_resources)
		pdata->release_resources();
	वापस ret;
पूर्ण

अटल पूर्णांक lis3lv02d_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lis3lv02d *lis3 = i2c_get_clientdata(client);
	काष्ठा lis3lv02d_platक्रमm_data *pdata = client->dev.platक्रमm_data;

	अगर (pdata && pdata->release_resources)
		pdata->release_resources();

	lis3lv02d_joystick_disable(lis3);
	lis3lv02d_हटाओ_fs(&lis3_dev);

	regulator_bulk_मुक्त(ARRAY_SIZE(lis3->regulators),
			    lis3_dev.regulators);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक lis3lv02d_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा lis3lv02d *lis3 = i2c_get_clientdata(client);

	अगर (!lis3->pdata || !lis3->pdata->wakeup_flags)
		lis3lv02d_घातeroff(lis3);
	वापस 0;
पूर्ण

अटल पूर्णांक lis3lv02d_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा lis3lv02d *lis3 = i2c_get_clientdata(client);

	/*
	 * pm_runसमय करोcumentation says that devices should always
	 * be घातered on at resume. Pm_runसमय turns them off after प्रणाली
	 * wide resume is complete.
	 */
	अगर (!lis3->pdata || !lis3->pdata->wakeup_flags ||
		pm_runसमय_suspended(dev))
		lis3lv02d_घातeron(lis3);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lis3_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा lis3lv02d *lis3 = i2c_get_clientdata(client);

	lis3lv02d_घातeroff(lis3);
	वापस 0;
पूर्ण

अटल पूर्णांक lis3_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा lis3lv02d *lis3 = i2c_get_clientdata(client);

	lis3lv02d_घातeron(lis3);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा i2c_device_id lis3lv02d_id[] = अणु
	अणु"lis3lv02d", LIS3LV02Dपूर्ण,
	अणु"lis331dlh", LIS331DLHपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lis3lv02d_id);

अटल स्थिर काष्ठा dev_pm_ops lis3_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(lis3lv02d_i2c_suspend,
				lis3lv02d_i2c_resume)
	SET_RUNTIME_PM_OPS(lis3_i2c_runसमय_suspend,
			   lis3_i2c_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा i2c_driver lis3lv02d_i2c_driver = अणु
	.driver	 = अणु
		.name   = DRV_NAME,
		.pm     = &lis3_pm_ops,
		.of_match_table = of_match_ptr(lis3lv02d_i2c_dt_ids),
	पूर्ण,
	.probe	= lis3lv02d_i2c_probe,
	.हटाओ	= lis3lv02d_i2c_हटाओ,
	.id_table = lis3lv02d_id,
पूर्ण;

module_i2c_driver(lis3lv02d_i2c_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("lis3lv02d I2C interface");
MODULE_LICENSE("GPL");
