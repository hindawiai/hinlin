<शैली गुरु>
/*
 * Copyright (C) 2016 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Author: Keerthy <j-keerthy@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lp873x.h>

अटल स्थिर काष्ठा regmap_config lp873x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LP873X_REG_MAX,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lp873x_cells[] = अणु
	अणु .name = "lp873x-regulator", पूर्ण,
	अणु .name = "lp873x-gpio", पूर्ण,
पूर्ण;

अटल पूर्णांक lp873x_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *ids)
अणु
	काष्ठा lp873x *lp873;
	पूर्णांक ret;
	अचिन्हित पूर्णांक otpid;

	lp873 = devm_kzalloc(&client->dev, माप(*lp873), GFP_KERNEL);
	अगर (!lp873)
		वापस -ENOMEM;

	lp873->dev = &client->dev;

	lp873->regmap = devm_regmap_init_i2c(client, &lp873x_regmap_config);
	अगर (IS_ERR(lp873->regmap)) अणु
		ret = PTR_ERR(lp873->regmap);
		dev_err(lp873->dev,
			"Failed to initialize register map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(lp873->regmap, LP873X_REG_OTP_REV, &otpid);
	अगर (ret) अणु
		dev_err(lp873->dev, "Failed to read OTP ID\n");
		वापस ret;
	पूर्ण

	lp873->rev = otpid & LP873X_OTP_REV_OTP_ID;

	i2c_set_clientdata(client, lp873);

	ret = mfd_add_devices(lp873->dev, PLATFORM_DEVID_AUTO, lp873x_cells,
			      ARRAY_SIZE(lp873x_cells), शून्य, 0, शून्य);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_lp873x_match_table[] = अणु
	अणु .compatible = "ti,lp8733", पूर्ण,
	अणु .compatible = "ti,lp8732", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_lp873x_match_table);

अटल स्थिर काष्ठा i2c_device_id lp873x_id_table[] = अणु
	अणु "lp873x", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp873x_id_table);

अटल काष्ठा i2c_driver lp873x_driver = अणु
	.driver	= अणु
		.name	= "lp873x",
		.of_match_table = of_lp873x_match_table,
	पूर्ण,
	.probe		= lp873x_probe,
	.id_table	= lp873x_id_table,
पूर्ण;
module_i2c_driver(lp873x_driver);

MODULE_AUTHOR("J Keerthy <j-keerthy@ti.com>");
MODULE_DESCRIPTION("LP873X chip family Multi-Function Device driver");
MODULE_LICENSE("GPL v2");
