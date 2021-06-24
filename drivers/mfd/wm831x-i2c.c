<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm831x-i2c.c  --  I2C access क्रम Wolfson WM831x PMICs
 *
 * Copyright 2009,2010 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>

अटल पूर्णांक wm831x_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm831x_pdata *pdata = dev_get_platdata(&i2c->dev);
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा wm831x *wm831x;
	क्रमागत wm831x_parent type;
	पूर्णांक ret;

	अगर (i2c->dev.of_node) अणु
		of_id = of_match_device(wm831x_of_match, &i2c->dev);
		अगर (!of_id) अणु
			dev_err(&i2c->dev, "Failed to match device\n");
			वापस -ENODEV;
		पूर्ण
		type = (क्रमागत wm831x_parent)of_id->data;
	पूर्ण अन्यथा अणु
		type = (क्रमागत wm831x_parent)id->driver_data;
	पूर्ण

	wm831x = devm_kzalloc(&i2c->dev, माप(काष्ठा wm831x), GFP_KERNEL);
	अगर (wm831x == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm831x);
	wm831x->dev = &i2c->dev;
	wm831x->type = type;

	wm831x->regmap = devm_regmap_init_i2c(i2c, &wm831x_regmap_config);
	अगर (IS_ERR(wm831x->regmap)) अणु
		ret = PTR_ERR(wm831x->regmap);
		dev_err(wm831x->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (pdata)
		स_नकल(&wm831x->pdata, pdata, माप(*pdata));

	वापस wm831x_device_init(wm831x, i2c->irq);
पूर्ण

अटल पूर्णांक wm831x_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev);

	वापस wm831x_device_suspend(wm831x);
पूर्ण

अटल पूर्णांक wm831x_i2c_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(dev);

	wm831x_device_shutकरोwn(wm831x);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm831x_i2c_id[] = अणु
	अणु "wm8310", WM8310 पूर्ण,
	अणु "wm8311", WM8311 पूर्ण,
	अणु "wm8312", WM8312 पूर्ण,
	अणु "wm8320", WM8320 पूर्ण,
	अणु "wm8321", WM8321 पूर्ण,
	अणु "wm8325", WM8325 पूर्ण,
	अणु "wm8326", WM8326 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops wm831x_pm_ops = अणु
	.suspend = wm831x_i2c_suspend,
	.घातeroff = wm831x_i2c_घातeroff,
पूर्ण;

अटल काष्ठा i2c_driver wm831x_i2c_driver = अणु
	.driver = अणु
		.name = "wm831x",
		.pm = &wm831x_pm_ops,
		.of_match_table = of_match_ptr(wm831x_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = wm831x_i2c_probe,
	.id_table = wm831x_i2c_id,
पूर्ण;

अटल पूर्णांक __init wm831x_i2c_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&wm831x_i2c_driver);
	अगर (ret != 0)
		pr_err("Failed to register wm831x I2C driver: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(wm831x_i2c_init);
