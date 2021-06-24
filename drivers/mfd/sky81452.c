<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sky81452.c	SKY81452 MFD driver
 *
 * Copyright 2014 Skyworks Solutions Inc.
 * Author : Gyungoh Yoo <jack.yoo@skyworksinc.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/sky81452.h>

अटल स्थिर काष्ठा regmap_config sky81452_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक sky81452_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा sky81452_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा mfd_cell cells[2];
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	अगर (!pdata) अणु
		pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &sky81452_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to initialize.err=%ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	i2c_set_clientdata(client, regmap);

	स_रखो(cells, 0, माप(cells));
	cells[0].name = "sky81452-backlight";
	cells[0].of_compatible = "skyworks,sky81452-backlight";
	cells[1].name = "sky81452-regulator";
	cells[1].platक्रमm_data = pdata->regulator_init_data;
	cells[1].pdata_size = माप(*pdata->regulator_init_data);

	ret = devm_mfd_add_devices(dev, -1, cells, ARRAY_SIZE(cells),
				   शून्य, 0, शून्य);
	अगर (ret)
		dev_err(dev, "failed to add child devices. err=%d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sky81452_ids[] = अणु
	अणु "sky81452" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sky81452_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sky81452_of_match[] = अणु
	अणु .compatible = "skyworks,sky81452", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sky81452_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver sky81452_driver = अणु
	.driver = अणु
		.name = "sky81452",
		.of_match_table = of_match_ptr(sky81452_of_match),
	पूर्ण,
	.probe = sky81452_probe,
	.id_table = sky81452_ids,
पूर्ण;

module_i2c_driver(sky81452_driver);

MODULE_DESCRIPTION("Skyworks SKY81452 MFD driver");
MODULE_AUTHOR("Gyungoh Yoo <jack.yoo@skyworksinc.com>");
MODULE_LICENSE("GPL v2");
