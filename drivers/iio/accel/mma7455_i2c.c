<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO accel I2C driver क्रम Freescale MMA7455L 3-axis 10-bit accelerometer
 * Copyright 2015 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "mma7455.h"

अटल पूर्णांक mma7455_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;

	regmap = devm_regmap_init_i2c(i2c, &mma7455_core_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	अगर (id)
		name = id->name;

	वापस mma7455_core_probe(&i2c->dev, regmap, name);
पूर्ण

अटल पूर्णांक mma7455_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस mma7455_core_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mma7455_i2c_ids[] = अणु
	अणु "mma7455", 0 पूर्ण,
	अणु "mma7456", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mma7455_i2c_ids);

अटल स्थिर काष्ठा of_device_id mma7455_of_match[] = अणु
	अणु .compatible = "fsl,mma7455" पूर्ण,
	अणु .compatible = "fsl,mma7456" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mma7455_of_match);

अटल काष्ठा i2c_driver mma7455_i2c_driver = अणु
	.probe = mma7455_i2c_probe,
	.हटाओ = mma7455_i2c_हटाओ,
	.id_table = mma7455_i2c_ids,
	.driver = अणु
		.name	= "mma7455-i2c",
		.of_match_table = mma7455_of_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(mma7455_i2c_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("Freescale MMA7455L I2C accelerometer driver");
MODULE_LICENSE("GPL v2");
