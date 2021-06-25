<शैली गुरु>
/*
 * I2C access driver क्रम TI TPS65912x PMICs
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 *
 * Based on the TPS65218 driver and the previous TPS65912 driver by
 * Margarita Olaya Cabrera <magi@slimlogic.co.uk>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/tps65912.h>

अटल स्थिर काष्ठा of_device_id tps65912_i2c_of_match_table[] = अणु
	अणु .compatible = "ti,tps65912", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65912_i2c_of_match_table);

अटल पूर्णांक tps65912_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *ids)
अणु
	काष्ठा tps65912 *tps;

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;
	tps->irq = client->irq;

	tps->regmap = devm_regmap_init_i2c(client, &tps65912_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		dev_err(tps->dev, "Failed to initialize register map\n");
		वापस PTR_ERR(tps->regmap);
	पूर्ण

	वापस tps65912_device_init(tps);
पूर्ण

अटल पूर्णांक tps65912_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps65912 *tps = i2c_get_clientdata(client);

	वापस tps65912_device_निकास(tps);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65912_i2c_id_table[] = अणु
	अणु "tps65912", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps65912_i2c_id_table);

अटल काष्ठा i2c_driver tps65912_i2c_driver = अणु
	.driver		= अणु
		.name	= "tps65912",
		.of_match_table = tps65912_i2c_of_match_table,
	पूर्ण,
	.probe		= tps65912_i2c_probe,
	.हटाओ		= tps65912_i2c_हटाओ,
	.id_table       = tps65912_i2c_id_table,
पूर्ण;
module_i2c_driver(tps65912_i2c_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPS65912x I2C Interface Driver");
MODULE_LICENSE("GPL v2");
