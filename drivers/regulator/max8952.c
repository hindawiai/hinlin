<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max8952.c - Voltage and current regulation क्रम the Maxim 8952
 *
 * Copyright (C) 2010 Samsung Electronics
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/max8952.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/* Registers */
क्रमागत अणु
	MAX8952_REG_MODE0,
	MAX8952_REG_MODE1,
	MAX8952_REG_MODE2,
	MAX8952_REG_MODE3,
	MAX8952_REG_CONTROL,
	MAX8952_REG_SYNC,
	MAX8952_REG_RAMP,
	MAX8952_REG_CHIP_ID1,
	MAX8952_REG_CHIP_ID2,
पूर्ण;

काष्ठा max8952_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा max8952_platक्रमm_data *pdata;
	काष्ठा gpio_desc *vid0_gpiod;
	काष्ठा gpio_desc *vid1_gpiod;
	bool vid0;
	bool vid1;
पूर्ण;

अटल पूर्णांक max8952_पढ़ो_reg(काष्ठा max8952_data *max8952, u8 reg)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(max8952->client, reg);

	अगर (ret > 0)
		ret &= 0xff;

	वापस ret;
पूर्ण

अटल पूर्णांक max8952_ग_लिखो_reg(काष्ठा max8952_data *max8952,
		u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(max8952->client, reg, value);
पूर्ण

अटल पूर्णांक max8952_list_voltage(काष्ठा regulator_dev *rdev,
		अचिन्हित पूर्णांक selector)
अणु
	काष्ठा max8952_data *max8952 = rdev_get_drvdata(rdev);

	अगर (rdev_get_id(rdev) != 0)
		वापस -EINVAL;

	वापस (max8952->pdata->dvs_mode[selector] * 10 + 770) * 1000;
पूर्ण

अटल पूर्णांक max8952_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8952_data *max8952 = rdev_get_drvdata(rdev);
	u8 vid = 0;

	अगर (max8952->vid0)
		vid += 1;
	अगर (max8952->vid1)
		vid += 2;

	वापस vid;
पूर्ण

अटल पूर्णांक max8952_set_voltage_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित selector)
अणु
	काष्ठा max8952_data *max8952 = rdev_get_drvdata(rdev);

	अगर (!max8952->vid0_gpiod || !max8952->vid1_gpiod) अणु
		/* DVS not supported */
		वापस -EPERM;
	पूर्ण

	max8952->vid0 = selector & 0x1;
	max8952->vid1 = (selector >> 1) & 0x1;
	gpiod_set_value(max8952->vid0_gpiod, max8952->vid0);
	gpiod_set_value(max8952->vid1_gpiod, max8952->vid1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8952_ops = अणु
	.list_voltage		= max8952_list_voltage,
	.get_voltage_sel	= max8952_get_voltage_sel,
	.set_voltage_sel	= max8952_set_voltage_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc regulator = अणु
	.name		= "MAX8952_VOUT",
	.id		= 0,
	.n_voltages	= MAX8952_NUM_DVS_MODE,
	.ops		= &max8952_ops,
	.type		= REGULATOR_VOLTAGE,
	.owner		= THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max8952_dt_match[] = अणु
	अणु .compatible = "maxim,max8952" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max8952_dt_match);

अटल काष्ठा max8952_platक्रमm_data *max8952_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा max8952_platक्रमm_data *pd;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;
	पूर्णांक i;

	pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस शून्य;

	अगर (of_property_पढ़ो_u32(np, "max8952,default-mode", &pd->शेष_mode))
		dev_warn(dev, "Default mode not specified, assuming 0\n");

	ret = of_property_पढ़ो_u32_array(np, "max8952,dvs-mode-microvolt",
					pd->dvs_mode, ARRAY_SIZE(pd->dvs_mode));
	अगर (ret) अणु
		dev_err(dev, "max8952,dvs-mode-microvolt property not specified");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pd->dvs_mode); ++i) अणु
		अगर (pd->dvs_mode[i] < 770000 || pd->dvs_mode[i] > 1400000) अणु
			dev_err(dev, "DVS voltage %d out of range\n", i);
			वापस शून्य;
		पूर्ण
		pd->dvs_mode[i] = (pd->dvs_mode[i] - 770000) / 10000;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "max8952,sync-freq", &pd->sync_freq))
		dev_warn(dev, "max8952,sync-freq property not specified, defaulting to 26MHz\n");

	अगर (of_property_पढ़ो_u32(np, "max8952,ramp-speed", &pd->ramp_speed))
		dev_warn(dev, "max8952,ramp-speed property not specified, defaulting to 32mV/us\n");

	pd->reg_data = of_get_regulator_init_data(dev, np, &regulator);
	अगर (!pd->reg_data) अणु
		dev_err(dev, "Failed to parse regulator init data\n");
		वापस शून्य;
	पूर्ण

	वापस pd;
पूर्ण
#अन्यथा
अटल काष्ठा max8952_platक्रमm_data *max8952_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक max8952_pmic_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा max8952_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा max8952_data *max8952;
	काष्ठा regulator_dev *rdev;
	काष्ठा gpio_desc *gpiod;
	क्रमागत gpiod_flags gflags;

	पूर्णांक ret = 0;

	अगर (client->dev.of_node)
		pdata = max8952_parse_dt(&client->dev);

	अगर (!pdata) अणु
		dev_err(&client->dev, "Require the platform data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		वापस -EIO;

	max8952 = devm_kzalloc(&client->dev, माप(काष्ठा max8952_data),
			       GFP_KERNEL);
	अगर (!max8952)
		वापस -ENOMEM;

	max8952->client = client;
	max8952->pdata = pdata;

	config.dev = &client->dev;
	config.init_data = pdata->reg_data;
	config.driver_data = max8952;
	config.of_node = client->dev.of_node;

	अगर (pdata->reg_data->स्थिरraपूर्णांकs.boot_on)
		gflags = GPIOD_OUT_HIGH;
	अन्यथा
		gflags = GPIOD_OUT_LOW;
	gflags |= GPIOD_FLAGS_BIT_NONEXCLUSIVE;
	/*
	 * Do not use devm* here: the regulator core takes over the
	 * lअगरecycle management of the GPIO descriptor.
	 */
	gpiod = gpiod_get_optional(&client->dev,
				   "max8952,en",
				   gflags);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);
	अगर (gpiod)
		config.ena_gpiod = gpiod;

	rdev = devm_regulator_रेजिस्टर(&client->dev, &regulator, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(&client->dev, "regulator init failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	max8952->vid0 = pdata->शेष_mode & 0x1;
	max8952->vid1 = (pdata->शेष_mode >> 1) & 0x1;

	/* Fetch vid0 and vid1 GPIOs अगर available */
	gflags = max8952->vid0 ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	max8952->vid0_gpiod = devm_gpiod_get_index_optional(&client->dev,
							    "max8952,vid",
							    0, gflags);
	अगर (IS_ERR(max8952->vid0_gpiod))
		वापस PTR_ERR(max8952->vid0_gpiod);
	gflags = max8952->vid1 ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	max8952->vid1_gpiod = devm_gpiod_get_index_optional(&client->dev,
							    "max8952,vid",
							    1, gflags);
	अगर (IS_ERR(max8952->vid1_gpiod))
		वापस PTR_ERR(max8952->vid1_gpiod);

	/* If either VID GPIO is missing just disable this */
	अगर (!max8952->vid0_gpiod || !max8952->vid1_gpiod) अणु
		dev_warn(&client->dev, "VID0/1 gpio invalid: "
			 "DVS not available.\n");
		max8952->vid0 = 0;
		max8952->vid1 = 0;
		/* Make sure अगर we have any descriptors they get set to low */
		अगर (max8952->vid0_gpiod)
			gpiod_set_value(max8952->vid0_gpiod, 0);
		अगर (max8952->vid1_gpiod)
			gpiod_set_value(max8952->vid1_gpiod, 0);

		/* Disable Pullकरोwn of EN only */
		max8952_ग_लिखो_reg(max8952, MAX8952_REG_CONTROL, 0x60);

		dev_err(&client->dev, "DVS modes disabled because VID0 and VID1"
				" do not have proper controls.\n");
	पूर्ण अन्यथा अणु
		/*
		 * Disable Pullकरोwn on EN, VID0, VID1 to reduce
		 * leakage current of MAX8952 assuming that MAX8952
		 * is turned on (EN==1). Note that without having VID0/1
		 * properly connected, turning pullकरोwn off can be
		 * problematic. Thus, turn this off only when they are
		 * controllable by GPIO.
		 */
		max8952_ग_लिखो_reg(max8952, MAX8952_REG_CONTROL, 0x0);
	पूर्ण

	max8952_ग_लिखो_reg(max8952, MAX8952_REG_MODE0,
			(max8952_पढ़ो_reg(max8952,
					  MAX8952_REG_MODE0) & 0xC0) |
			(pdata->dvs_mode[0] & 0x3F));
	max8952_ग_लिखो_reg(max8952, MAX8952_REG_MODE1,
			(max8952_पढ़ो_reg(max8952,
					  MAX8952_REG_MODE1) & 0xC0) |
			(pdata->dvs_mode[1] & 0x3F));
	max8952_ग_लिखो_reg(max8952, MAX8952_REG_MODE2,
			(max8952_पढ़ो_reg(max8952,
					  MAX8952_REG_MODE2) & 0xC0) |
			(pdata->dvs_mode[2] & 0x3F));
	max8952_ग_लिखो_reg(max8952, MAX8952_REG_MODE3,
			(max8952_पढ़ो_reg(max8952,
					  MAX8952_REG_MODE3) & 0xC0) |
			(pdata->dvs_mode[3] & 0x3F));

	max8952_ग_लिखो_reg(max8952, MAX8952_REG_SYNC,
			(max8952_पढ़ो_reg(max8952, MAX8952_REG_SYNC) & 0x3F) |
			((pdata->sync_freq & 0x3) << 6));
	max8952_ग_लिखो_reg(max8952, MAX8952_REG_RAMP,
			(max8952_पढ़ो_reg(max8952, MAX8952_REG_RAMP) & 0x1F) |
			((pdata->ramp_speed & 0x7) << 5));

	i2c_set_clientdata(client, max8952);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8952_ids[] = अणु
	अणु "max8952", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max8952_ids);

अटल काष्ठा i2c_driver max8952_pmic_driver = अणु
	.probe		= max8952_pmic_probe,
	.driver		= अणु
		.name	= "max8952",
		.of_match_table = of_match_ptr(max8952_dt_match),
	पूर्ण,
	.id_table	= max8952_ids,
पूर्ण;

अटल पूर्णांक __init max8952_pmic_init(व्योम)
अणु
	वापस i2c_add_driver(&max8952_pmic_driver);
पूर्ण
subsys_initcall(max8952_pmic_init);

अटल व्योम __निकास max8952_pmic_निकास(व्योम)
अणु
	i2c_del_driver(&max8952_pmic_driver);
पूर्ण
module_निकास(max8952_pmic_निकास);

MODULE_DESCRIPTION("MAXIM 8952 voltage regulator driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_LICENSE("GPL");
