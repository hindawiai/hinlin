<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8804-i2c.c  --  WM8804 S/PDIF transceiver driver - I2C
 *
 * Copyright 2015 Cirrus Logic Inc
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>

#समावेश "wm8804.h"

अटल पूर्णांक wm8804_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &wm8804_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस wm8804_probe(&i2c->dev, regmap);
पूर्ण

अटल पूर्णांक wm8804_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	wm8804_हटाओ(&i2c->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8804_i2c_id[] = अणु
	अणु "wm8804", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8804_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id wm8804_of_match[] = अणु
	अणु .compatible = "wlf,wm8804", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8804_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id wm8804_acpi_match[] = अणु
	अणु "1AEC8804", 0 पूर्ण, /* Wolfson PCI ID + part ID */
	अणु "10138804", 0 पूर्ण, /* Cirrus Logic PCI ID + part ID */
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, wm8804_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver wm8804_i2c_driver = अणु
	.driver = अणु
		.name = "wm8804",
		.pm = &wm8804_pm,
		.of_match_table = of_match_ptr(wm8804_of_match),
		.acpi_match_table = ACPI_PTR(wm8804_acpi_match),
	पूर्ण,
	.probe = wm8804_i2c_probe,
	.हटाओ = wm8804_i2c_हटाओ,
	.id_table = wm8804_i2c_id
पूर्ण;

module_i2c_driver(wm8804_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8804 driver - I2C");
MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
