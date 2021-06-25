<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Pengutronix, Juergen Borleis <kernel@pengutronix.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>

#समावेश "lan9303.h"

काष्ठा lan9303_i2c अणु
	काष्ठा i2c_client *device;
	काष्ठा lan9303 chip;
पूर्ण;

अटल स्थिर काष्ठा regmap_config lan9303_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 1,
	.can_multi_ग_लिखो = true,
	.max_रेजिस्टर = 0x0ff, /* address bits 0..1 are not used */
	.reg_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,

	.अस्थिर_table = &lan9303_रेजिस्टर_set,
	.wr_table = &lan9303_रेजिस्टर_set,
	.rd_table = &lan9303_रेजिस्टर_set,

	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक lan9303_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lan9303_i2c *sw_dev;
	पूर्णांक ret;

	sw_dev = devm_kzalloc(&client->dev, माप(काष्ठा lan9303_i2c),
			      GFP_KERNEL);
	अगर (!sw_dev)
		वापस -ENOMEM;

	sw_dev->chip.regmap = devm_regmap_init_i2c(client,
						   &lan9303_i2c_regmap_config);
	अगर (IS_ERR(sw_dev->chip.regmap)) अणु
		ret = PTR_ERR(sw_dev->chip.regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* link क्रमward and backward */
	sw_dev->device = client;
	i2c_set_clientdata(client, sw_dev);
	sw_dev->chip.dev = &client->dev;

	sw_dev->chip.ops = &lan9303_indirect_phy_ops;

	ret = lan9303_probe(&sw_dev->chip, client->dev.of_node);
	अगर (ret != 0)
		वापस ret;

	dev_info(&client->dev, "LAN9303 I2C driver loaded successfully\n");

	वापस 0;
पूर्ण

अटल पूर्णांक lan9303_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lan9303_i2c *sw_dev;

	sw_dev = i2c_get_clientdata(client);
	अगर (!sw_dev)
		वापस -ENODEV;

	वापस lan9303_हटाओ(&sw_dev->chip);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा i2c_device_id lan9303_i2c_id[] = अणु
	अणु "lan9303", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lan9303_i2c_id);

अटल स्थिर काष्ठा of_device_id lan9303_i2c_of_match[] = अणु
	अणु .compatible = "smsc,lan9303-i2c", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lan9303_i2c_of_match);

अटल काष्ठा i2c_driver lan9303_i2c_driver = अणु
	.driver = अणु
		.name = "LAN9303_I2C",
		.of_match_table = of_match_ptr(lan9303_i2c_of_match),
	पूर्ण,
	.probe = lan9303_i2c_probe,
	.हटाओ = lan9303_i2c_हटाओ,
	.id_table = lan9303_i2c_id,
पूर्ण;
module_i2c_driver(lan9303_i2c_driver);

MODULE_AUTHOR("Juergen Borleis <kernel@pengutronix.de>");
MODULE_DESCRIPTION("Driver for SMSC/Microchip LAN9303 three port ethernet switch in I2C managed mode");
MODULE_LICENSE("GPL v2");
