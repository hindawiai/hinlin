<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the PCM512x CODECs
 *
 * Author:	Mark Brown <broonie@kernel.org>
 *		Copyright 2014 Linaro Ltd
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>

#समावेश "pcm512x.h"

अटल पूर्णांक pcm512x_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_config config = pcm512x_regmap;

	/* msb needs to be set to enable स्वतः-increment of addresses */
	config.पढ़ो_flag_mask = 0x80;
	config.ग_लिखो_flag_mask = 0x80;

	regmap = devm_regmap_init_i2c(i2c, &config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस pcm512x_probe(&i2c->dev, regmap);
पूर्ण

अटल पूर्णांक pcm512x_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pcm512x_हटाओ(&i2c->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcm512x_i2c_id[] = अणु
	अणु "pcm5121", पूर्ण,
	अणु "pcm5122", पूर्ण,
	अणु "pcm5141", पूर्ण,
	अणु "pcm5142", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm512x_i2c_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id pcm512x_of_match[] = अणु
	अणु .compatible = "ti,pcm5121", पूर्ण,
	अणु .compatible = "ti,pcm5122", पूर्ण,
	अणु .compatible = "ti,pcm5141", पूर्ण,
	अणु .compatible = "ti,pcm5142", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm512x_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id pcm512x_acpi_match[] = अणु
	अणु "104C5121", 0 पूर्ण,
	अणु "104C5122", 0 पूर्ण,
	अणु "104C5141", 0 पूर्ण,
	अणु "104C5142", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pcm512x_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pcm512x_i2c_driver = अणु
	.probe 		= pcm512x_i2c_probe,
	.हटाओ 	= pcm512x_i2c_हटाओ,
	.id_table	= pcm512x_i2c_id,
	.driver		= अणु
		.name	= "pcm512x",
		.of_match_table = of_match_ptr(pcm512x_of_match),
		.acpi_match_table = ACPI_PTR(pcm512x_acpi_match),
		.pm     = &pcm512x_pm_ops,
	पूर्ण,
पूर्ण;

module_i2c_driver(pcm512x_i2c_driver);

MODULE_DESCRIPTION("ASoC PCM512x codec driver - I2C");
MODULE_AUTHOR("Mark Brown <broonie@kernel.org>");
MODULE_LICENSE("GPL v2");
