<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs42l56.c -- CS42L51 ALSA SoC I2C audio driver
 *
 * Copyright 2014 CirrusLogic, Inc.
 *
 * Author: Brian Austin <brian.austin@cirrus.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश "cs42l51.h"

अटल काष्ठा i2c_device_id cs42l51_i2c_id[] = अणु
	अणु"cs42l51", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs42l51_i2c_id);

अटल पूर्णांक cs42l51_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap_config config;

	config = cs42l51_regmap;

	वापस cs42l51_probe(&i2c->dev, devm_regmap_init_i2c(i2c, &config));
पूर्ण

अटल पूर्णांक cs42l51_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस cs42l51_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cs42l51_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cs42l51_suspend, cs42l51_resume)
पूर्ण;

अटल काष्ठा i2c_driver cs42l51_i2c_driver = अणु
	.driver = अणु
		.name = "cs42l51",
		.of_match_table = cs42l51_of_match,
		.pm = &cs42l51_pm_ops,
	पूर्ण,
	.probe = cs42l51_i2c_probe,
	.हटाओ = cs42l51_i2c_हटाओ,
	.id_table = cs42l51_i2c_id,
पूर्ण;

module_i2c_driver(cs42l51_i2c_driver);

MODULE_DESCRIPTION("ASoC CS42L51 I2C Driver");
MODULE_AUTHOR("Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>");
MODULE_LICENSE("GPL");
