<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C bus पूर्णांकerface to Cirrus Logic Madera codecs
 *
 * Copyright (C) 2015-2018 Cirrus Logic
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/madera/core.h>

#समावेश "madera.h"

अटल पूर्णांक madera_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा madera *madera;
	स्थिर काष्ठा regmap_config *regmap_16bit_config = शून्य;
	स्थिर काष्ठा regmap_config *regmap_32bit_config = शून्य;
	स्थिर व्योम *of_data;
	अचिन्हित दीर्घ type;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	of_data = of_device_get_match_data(&i2c->dev);
	अगर (of_data)
		type = (अचिन्हित दीर्घ)of_data;
	अन्यथा
		type = id->driver_data;

	चयन (type) अणु
	हाल CS47L15:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L15)) अणु
			regmap_16bit_config = &cs47l15_16bit_i2c_regmap;
			regmap_32bit_config = &cs47l15_32bit_i2c_regmap;
		पूर्ण
		अवरोध;
	हाल CS47L35:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L35)) अणु
			regmap_16bit_config = &cs47l35_16bit_i2c_regmap;
			regmap_32bit_config = &cs47l35_32bit_i2c_regmap;
		पूर्ण
		अवरोध;
	हाल CS47L85:
	हाल WM1840:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L85)) अणु
			regmap_16bit_config = &cs47l85_16bit_i2c_regmap;
			regmap_32bit_config = &cs47l85_32bit_i2c_regmap;
		पूर्ण
		अवरोध;
	हाल CS47L90:
	हाल CS47L91:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L90)) अणु
			regmap_16bit_config = &cs47l90_16bit_i2c_regmap;
			regmap_32bit_config = &cs47l90_32bit_i2c_regmap;
		पूर्ण
		अवरोध;
	हाल CS42L92:
	हाल CS47L92:
	हाल CS47L93:
		अगर (IS_ENABLED(CONFIG_MFD_CS47L92)) अणु
			regmap_16bit_config = &cs47l92_16bit_i2c_regmap;
			regmap_32bit_config = &cs47l92_32bit_i2c_regmap;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&i2c->dev,
			"Unknown Madera I2C device type %ld\n", type);
		वापस -EINVAL;
	पूर्ण

	name = madera_name_from_type(type);

	अगर (!regmap_16bit_config) अणु
		/* it's polite to say which codec isn't built पूर्णांकo the kernel */
		dev_err(&i2c->dev,
			"Kernel does not include support for %s\n", name);
		वापस -EINVAL;
	पूर्ण

	madera = devm_kzalloc(&i2c->dev, माप(*madera), GFP_KERNEL);
	अगर (!madera)
		वापस -ENOMEM;

	madera->regmap = devm_regmap_init_i2c(i2c, regmap_16bit_config);
	अगर (IS_ERR(madera->regmap)) अणु
		ret = PTR_ERR(madera->regmap);
		dev_err(&i2c->dev,
			"Failed to allocate 16-bit register map: %d\n",	ret);
		वापस ret;
	पूर्ण

	madera->regmap_32bit = devm_regmap_init_i2c(i2c, regmap_32bit_config);
	अगर (IS_ERR(madera->regmap_32bit)) अणु
		ret = PTR_ERR(madera->regmap_32bit);
		dev_err(&i2c->dev,
			"Failed to allocate 32-bit register map: %d\n", ret);
		वापस ret;
	पूर्ण

	madera->type = type;
	madera->type_name = name;
	madera->dev = &i2c->dev;
	madera->irq = i2c->irq;

	वापस madera_dev_init(madera);
पूर्ण

अटल पूर्णांक madera_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा madera *madera = dev_get_drvdata(&i2c->dev);

	madera_dev_निकास(madera);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id madera_i2c_id[] = अणु
	अणु "cs47l15", CS47L15 पूर्ण,
	अणु "cs47l35", CS47L35 पूर्ण,
	अणु "cs47l85", CS47L85 पूर्ण,
	अणु "cs47l90", CS47L90 पूर्ण,
	अणु "cs47l91", CS47L91 पूर्ण,
	अणु "cs42l92", CS42L92 पूर्ण,
	अणु "cs47l92", CS47L92 पूर्ण,
	अणु "cs47l93", CS47L93 पूर्ण,
	अणु "wm1840", WM1840 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, madera_i2c_id);

अटल काष्ठा i2c_driver madera_i2c_driver = अणु
	.driver = अणु
		.name	= "madera",
		.pm	= &madera_pm_ops,
		.of_match_table	= of_match_ptr(madera_of_match),
	पूर्ण,
	.probe		= madera_i2c_probe,
	.हटाओ		= madera_i2c_हटाओ,
	.id_table	= madera_i2c_id,
पूर्ण;

module_i2c_driver(madera_i2c_driver);

MODULE_DESCRIPTION("Madera I2C bus interface");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
