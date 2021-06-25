<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8350-i2c.c  --  Generic I2C driver क्रम Wolfson WM8350 PMIC
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood
 *         linux@wolfsonmicro.com
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल पूर्णांक wm8350_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8350 *wm8350;
	काष्ठा wm8350_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	पूर्णांक ret = 0;

	wm8350 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8350), GFP_KERNEL);
	अगर (wm8350 == शून्य)
		वापस -ENOMEM;

	wm8350->regmap = devm_regmap_init_i2c(i2c, &wm8350_regmap);
	अगर (IS_ERR(wm8350->regmap)) अणु
		ret = PTR_ERR(wm8350->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, wm8350);
	wm8350->dev = &i2c->dev;

	वापस wm8350_device_init(wm8350, i2c->irq, pdata);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8350_i2c_id[] = अणु
	अणु "wm8350", 0 पूर्ण,
	अणु "wm8351", 0 पूर्ण,
	अणु "wm8352", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver wm8350_i2c_driver = अणु
	.driver = अणु
		   .name = "wm8350",
		   .suppress_bind_attrs = true,
	पूर्ण,
	.probe = wm8350_i2c_probe,
	.id_table = wm8350_i2c_id,
पूर्ण;

अटल पूर्णांक __init wm8350_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&wm8350_i2c_driver);
पूर्ण
/* init early so consumer devices can complete प्रणाली boot */
subsys_initcall(wm8350_i2c_init);
