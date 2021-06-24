<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip KSZ9477 series रेजिस्टर access through I2C
 *
 * Copyright (C) 2018-2019 Microchip Technology Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "ksz_common.h"

KSZ_REGMAP_TABLE(ksz9477, not_used, 16, 0, 0);

अटल पूर्णांक ksz9477_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा regmap_config rc;
	काष्ठा ksz_device *dev;
	पूर्णांक i, ret;

	dev = ksz_चयन_alloc(&i2c->dev, i2c);
	अगर (!dev)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(ksz9477_regmap_config); i++) अणु
		rc = ksz9477_regmap_config[i];
		rc.lock_arg = &dev->regmap_mutex;
		dev->regmap[i] = devm_regmap_init_i2c(i2c, &rc);
		अगर (IS_ERR(dev->regmap[i])) अणु
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&i2c->dev,
				"Failed to initialize regmap%i: %d\n",
				ksz9477_regmap_config[i].val_bits, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (i2c->dev.platक्रमm_data)
		dev->pdata = i2c->dev.platक्रमm_data;

	ret = ksz9477_चयन_रेजिस्टर(dev);

	/* Main DSA driver may not be started yet. */
	अगर (ret)
		वापस ret;

	i2c_set_clientdata(i2c, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9477_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा ksz_device *dev = i2c_get_clientdata(i2c);

	ksz_चयन_हटाओ(dev);

	वापस 0;
पूर्ण

अटल व्योम ksz9477_i2c_shutकरोwn(काष्ठा i2c_client *i2c)
अणु
	काष्ठा ksz_device *dev = i2c_get_clientdata(i2c);

	अगर (dev && dev->dev_ops->shutकरोwn)
		dev->dev_ops->shutकरोwn(dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ksz9477_i2c_id[] = अणु
	अणु "ksz9477-switch", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ksz9477_i2c_id);

अटल स्थिर काष्ठा of_device_id ksz9477_dt_ids[] = अणु
	अणु .compatible = "microchip,ksz9477" पूर्ण,
	अणु .compatible = "microchip,ksz9897" पूर्ण,
	अणु .compatible = "microchip,ksz9893" पूर्ण,
	अणु .compatible = "microchip,ksz9563" पूर्ण,
	अणु .compatible = "microchip,ksz9567" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ksz9477_dt_ids);

अटल काष्ठा i2c_driver ksz9477_i2c_driver = अणु
	.driver = अणु
		.name	= "ksz9477-switch",
		.of_match_table = of_match_ptr(ksz9477_dt_ids),
	पूर्ण,
	.probe	= ksz9477_i2c_probe,
	.हटाओ	= ksz9477_i2c_हटाओ,
	.shutकरोwn = ksz9477_i2c_shutकरोwn,
	.id_table = ksz9477_i2c_id,
पूर्ण;

module_i2c_driver(ksz9477_i2c_driver);

MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch I2C access Driver");
MODULE_LICENSE("GPL v2");
