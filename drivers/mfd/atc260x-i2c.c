<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * I2C bus पूर्णांकerface क्रम ATC260x PMICs
 *
 * Copyright (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 * Copyright (C) 2020 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/mfd/atc260x/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

अटल पूर्णांक atc260x_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा atc260x *atc260x;
	काष्ठा regmap_config regmap_cfg;
	पूर्णांक ret;

	atc260x = devm_kzalloc(&client->dev, माप(*atc260x), GFP_KERNEL);
	अगर (!atc260x)
		वापस -ENOMEM;

	atc260x->dev = &client->dev;
	atc260x->irq = client->irq;

	ret = atc260x_match_device(atc260x, &regmap_cfg);
	अगर (ret)
		वापस ret;

	i2c_set_clientdata(client, atc260x);

	atc260x->regmap = devm_regmap_init_i2c(client, &regmap_cfg);
	अगर (IS_ERR(atc260x->regmap)) अणु
		ret = PTR_ERR(atc260x->regmap);
		dev_err(&client->dev, "failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस atc260x_device_probe(atc260x);
पूर्ण

अटल स्थिर काष्ठा of_device_id atc260x_i2c_of_match[] = अणु
	अणु .compatible = "actions,atc2603c", .data = (व्योम *)ATC2603C पूर्ण,
	अणु .compatible = "actions,atc2609a", .data = (व्योम *)ATC2609A पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, atc260x_i2c_of_match);

अटल काष्ठा i2c_driver atc260x_i2c_driver = अणु
	.driver = अणु
		.name = "atc260x",
		.of_match_table	= of_match_ptr(atc260x_i2c_of_match),
	पूर्ण,
	.probe = atc260x_i2c_probe,
पूर्ण;
module_i2c_driver(atc260x_i2c_driver);

MODULE_DESCRIPTION("ATC260x PMICs I2C bus interface");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_AUTHOR("Cristian Ciocaltea <cristian.ciocaltea@gmail.com>");
MODULE_LICENSE("GPL");
