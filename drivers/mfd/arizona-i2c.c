<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Arizona-i2c.c  --  Arizona I2C bus पूर्णांकerface
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/mfd/arizona/core.h>

#समावेश "arizona.h"

अटल पूर्णांक arizona_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर व्योम *match_data;
	काष्ठा arizona *arizona;
	स्थिर काष्ठा regmap_config *regmap_config = शून्य;
	अचिन्हित दीर्घ type = 0;
	पूर्णांक ret;

	match_data = device_get_match_data(&i2c->dev);
	अगर (match_data)
		type = (अचिन्हित दीर्घ)match_data;
	अन्यथा अगर (id)
		type = id->driver_data;

	चयन (type) अणु
	हाल WM5102:
		अगर (IS_ENABLED(CONFIG_MFD_WM5102))
			regmap_config = &wm5102_i2c_regmap;
		अवरोध;
	हाल WM5110:
	हाल WM8280:
		अगर (IS_ENABLED(CONFIG_MFD_WM5110))
			regmap_config = &wm5110_i2c_regmap;
		अवरोध;
	हाल WM8997:
		अगर (IS_ENABLED(CONFIG_MFD_WM8997))
			regmap_config = &wm8997_i2c_regmap;
		अवरोध;
	हाल WM8998:
	हाल WM1814:
		अगर (IS_ENABLED(CONFIG_MFD_WM8998))
			regmap_config = &wm8998_i2c_regmap;
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unknown device type %ld\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (!regmap_config) अणु
		dev_err(&i2c->dev,
			"No kernel support for device type %ld\n", type);
		वापस -EINVAL;
	पूर्ण

	arizona = devm_kzalloc(&i2c->dev, माप(*arizona), GFP_KERNEL);
	अगर (arizona == शून्य)
		वापस -ENOMEM;

	arizona->regmap = devm_regmap_init_i2c(i2c, regmap_config);
	अगर (IS_ERR(arizona->regmap)) अणु
		ret = PTR_ERR(arizona->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	arizona->type = type;
	arizona->dev = &i2c->dev;
	arizona->irq = i2c->irq;

	वापस arizona_dev_init(arizona);
पूर्ण

अटल पूर्णांक arizona_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(&i2c->dev);

	arizona_dev_निकास(arizona);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id arizona_i2c_id[] = अणु
	अणु "wm5102", WM5102 पूर्ण,
	अणु "wm5110", WM5110 पूर्ण,
	अणु "wm8280", WM8280 पूर्ण,
	अणु "wm8997", WM8997 पूर्ण,
	अणु "wm8998", WM8998 पूर्ण,
	अणु "wm1814", WM1814 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, arizona_i2c_id);

अटल काष्ठा i2c_driver arizona_i2c_driver = अणु
	.driver = अणु
		.name	= "arizona",
		.pm	= &arizona_pm_ops,
		.of_match_table	= of_match_ptr(arizona_of_match),
	पूर्ण,
	.probe		= arizona_i2c_probe,
	.हटाओ		= arizona_i2c_हटाओ,
	.id_table	= arizona_i2c_id,
पूर्ण;

module_i2c_driver(arizona_i2c_driver);

MODULE_SOFTDEP("pre: arizona_ldo1");
MODULE_DESCRIPTION("Arizona I2C bus interface");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
