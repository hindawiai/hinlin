<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Author: Keerthy <j-keerthy@ti.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lp87565.h>

अटल स्थिर काष्ठा regmap_config lp87565_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LP87565_REG_MAX,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lp87565_cells[] = अणु
	अणु .name = "lp87565-q1-regulator", पूर्ण,
	अणु .name = "lp87565-q1-gpio", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_lp87565_match_table[] = अणु
	अणु .compatible = "ti,lp87565", पूर्ण,
	अणु
		.compatible = "ti,lp87524-q1",
		.data = (व्योम *)LP87565_DEVICE_TYPE_LP87524_Q1,
	पूर्ण,
	अणु
		.compatible = "ti,lp87565-q1",
		.data = (व्योम *)LP87565_DEVICE_TYPE_LP87565_Q1,
	पूर्ण,
	अणु
		.compatible = "ti,lp87561-q1",
		.data = (व्योम *)LP87565_DEVICE_TYPE_LP87561_Q1,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lp87565_match_table);

अटल पूर्णांक lp87565_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *ids)
अणु
	काष्ठा lp87565 *lp87565;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक ret;
	अचिन्हित पूर्णांक otpid;

	lp87565 = devm_kzalloc(&client->dev, माप(*lp87565), GFP_KERNEL);
	अगर (!lp87565)
		वापस -ENOMEM;

	lp87565->dev = &client->dev;

	lp87565->regmap = devm_regmap_init_i2c(client, &lp87565_regmap_config);
	अगर (IS_ERR(lp87565->regmap)) अणु
		ret = PTR_ERR(lp87565->regmap);
		dev_err(lp87565->dev,
			"Failed to initialize register map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(lp87565->regmap, LP87565_REG_OTP_REV, &otpid);
	अगर (ret) अणु
		dev_err(lp87565->dev, "Failed to read OTP ID\n");
		वापस ret;
	पूर्ण

	lp87565->rev = otpid & LP87565_OTP_REV_OTP_ID;

	of_id = of_match_device(of_lp87565_match_table, &client->dev);
	अगर (of_id)
		lp87565->dev_type = (क्रमागत lp87565_device_type)of_id->data;

	i2c_set_clientdata(client, lp87565);

	वापस devm_mfd_add_devices(lp87565->dev, PLATFORM_DEVID_AUTO,
				    lp87565_cells, ARRAY_SIZE(lp87565_cells),
				    शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp87565_id_table[] = अणु
	अणु "lp87565-q1", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp87565_id_table);

अटल काष्ठा i2c_driver lp87565_driver = अणु
	.driver	= अणु
		.name	= "lp87565",
		.of_match_table = of_lp87565_match_table,
	पूर्ण,
	.probe = lp87565_probe,
	.id_table = lp87565_id_table,
पूर्ण;
module_i2c_driver(lp87565_driver);

MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("lp87565 chip family Multi-Function Device driver");
MODULE_LICENSE("GPL v2");
