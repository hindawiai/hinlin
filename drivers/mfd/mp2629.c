<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MP2629 parent driver क्रम ADC and battery अक्षरger
 *
 * Copyright 2020 Monolithic Power Systems, Inc
 *
 * Author: Saravanan Sekar <sravanhome@gmail.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mp2629.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल स्थिर काष्ठा mfd_cell mp2629_cell[] = अणु
	अणु
		.name = "mp2629_adc",
		.of_compatible = "mps,mp2629_adc",
	पूर्ण,
	अणु
		.name = "mp2629_charger",
		.of_compatible = "mps,mp2629_charger",
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config mp2629_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x17,
पूर्ण;

अटल पूर्णांक mp2629_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mp2629_data *ddata;
	पूर्णांक ret;

	ddata = devm_kzalloc(&client->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->dev = &client->dev;
	i2c_set_clientdata(client, ddata);

	ddata->regmap = devm_regmap_init_i2c(client, &mp2629_regmap_config);
	अगर (IS_ERR(ddata->regmap)) अणु
		dev_err(ddata->dev, "Failed to allocate regmap\n");
		वापस PTR_ERR(ddata->regmap);
	पूर्ण

	ret = devm_mfd_add_devices(ddata->dev, PLATFORM_DEVID_AUTO, mp2629_cell,
				   ARRAY_SIZE(mp2629_cell), शून्य, 0, शून्य);
	अगर (ret)
		dev_err(ddata->dev, "Failed to register sub-devices %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mp2629_of_match[] = अणु
	अणु .compatible = "mps,mp2629"पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mp2629_of_match);

अटल काष्ठा i2c_driver mp2629_driver = अणु
	.driver = अणु
		.name = "mp2629",
		.of_match_table = mp2629_of_match,
	पूर्ण,
	.probe_new	= mp2629_probe,
पूर्ण;
module_i2c_driver(mp2629_driver);

MODULE_AUTHOR("Saravanan Sekar <sravanhome@gmail.com>");
MODULE_DESCRIPTION("MP2629 Battery charger parent driver");
MODULE_LICENSE("GPL");
