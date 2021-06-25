<शैली गुरु>
/*
 * isl6271a-regulator.c
 *
 * Support क्रम Intersil ISL6271A voltage regulator
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#घोषणा	ISL6271A_VOLTAGE_MIN	850000
#घोषणा	ISL6271A_VOLTAGE_MAX	1600000
#घोषणा	ISL6271A_VOLTAGE_STEP	50000

/* PMIC details */
काष्ठा isl_pmic अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		mtx;
पूर्ण;

अटल पूर्णांक isl6271a_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा isl_pmic *pmic = rdev_get_drvdata(dev);
	पूर्णांक idx;

	mutex_lock(&pmic->mtx);

	idx = i2c_smbus_पढ़ो_byte(pmic->client);
	अगर (idx < 0)
		dev_err(&pmic->client->dev, "Error getting voltage\n");

	mutex_unlock(&pmic->mtx);
	वापस idx;
पूर्ण

अटल पूर्णांक isl6271a_set_voltage_sel(काष्ठा regulator_dev *dev,
				    अचिन्हित selector)
अणु
	काष्ठा isl_pmic *pmic = rdev_get_drvdata(dev);
	पूर्णांक err;

	mutex_lock(&pmic->mtx);

	err = i2c_smbus_ग_लिखो_byte(pmic->client, selector);
	अगर (err < 0)
		dev_err(&pmic->client->dev, "Error setting voltage\n");

	mutex_unlock(&pmic->mtx);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा regulator_ops isl_core_ops = अणु
	.get_voltage_sel = isl6271a_get_voltage_sel,
	.set_voltage_sel = isl6271a_set_voltage_sel,
	.list_voltage	= regulator_list_voltage_linear,
	.map_voltage	= regulator_map_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops isl_fixed_ops = अणु
	.list_voltage	= regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc isl_rd[] = अणु
	अणु
		.name		= "Core Buck",
		.id		= 0,
		.n_voltages	= 16,
		.ops		= &isl_core_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
		.min_uV		= ISL6271A_VOLTAGE_MIN,
		.uV_step	= ISL6271A_VOLTAGE_STEP,
	पूर्ण, अणु
		.name		= "LDO1",
		.id		= 1,
		.n_voltages	= 1,
		.ops		= &isl_fixed_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
		.min_uV		= 1100000,
	पूर्ण, अणु
		.name		= "LDO2",
		.id		= 2,
		.n_voltages	= 1,
		.ops		= &isl_fixed_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
		.min_uV		= 1300000,
	पूर्ण,
पूर्ण;

अटल पूर्णांक isl6271a_probe(काष्ठा i2c_client *i2c,
				     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_init_data *init_data	= dev_get_platdata(&i2c->dev);
	काष्ठा isl_pmic *pmic;
	पूर्णांक i;

	अगर (!i2c_check_functionality(i2c->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	pmic = devm_kzalloc(&i2c->dev, माप(काष्ठा isl_pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	pmic->client = i2c;

	mutex_init(&pmic->mtx);

	क्रम (i = 0; i < 3; i++) अणु
		config.dev = &i2c->dev;
		अगर (i == 0)
			config.init_data = init_data;
		अन्यथा
			config.init_data = शून्य;
		config.driver_data = pmic;

		rdev = devm_regulator_रेजिस्टर(&i2c->dev, &isl_rd[i], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&i2c->dev, "failed to register %s\n", id->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	i2c_set_clientdata(i2c, pmic);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id isl6271a_id[] = अणु
	अणु.name = "isl6271a", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, isl6271a_id);

अटल काष्ठा i2c_driver isl6271a_i2c_driver = अणु
	.driver = अणु
		.name = "isl6271a",
	पूर्ण,
	.probe = isl6271a_probe,
	.id_table = isl6271a_id,
पूर्ण;

अटल पूर्णांक __init isl6271a_init(व्योम)
अणु
	वापस i2c_add_driver(&isl6271a_i2c_driver);
पूर्ण

अटल व्योम __निकास isl6271a_cleanup(व्योम)
अणु
	i2c_del_driver(&isl6271a_i2c_driver);
पूर्ण

subsys_initcall(isl6271a_init);
module_निकास(isl6271a_cleanup);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("Intersil ISL6271A voltage regulator driver");
MODULE_LICENSE("GPL v2");
