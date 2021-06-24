<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Core driver क्रम WM8400.
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/wm8400-निजी.h>
#समावेश <linux/mfd/wm8400-audपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल bool wm8400_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8400_INTERRUPT_STATUS_1:
	हाल WM8400_INTERRUPT_LEVELS:
	हाल WM8400_SHUTDOWN_REASON:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8400_रेजिस्टर_codec(काष्ठा wm8400 *wm8400)
अणु
	स्थिर काष्ठा mfd_cell cell = अणु
		.name = "wm8400-codec",
		.platक्रमm_data = wm8400,
		.pdata_size = माप(*wm8400),
	पूर्ण;

	वापस devm_mfd_add_devices(wm8400->dev, -1, &cell, 1, शून्य, 0, शून्य);
पूर्ण

/*
 * wm8400_init - Generic initialisation
 *
 * The WM8400 can be configured as either an I2C or SPI device.  Probe
 * functions क्रम each bus set up the accessors then call पूर्णांकo this to
 * set up the device itself.
 */
अटल पूर्णांक wm8400_init(काष्ठा wm8400 *wm8400,
		       काष्ठा wm8400_platक्रमm_data *pdata)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	dev_set_drvdata(wm8400->dev, wm8400);

	/* Check that this is actually a WM8400 */
	ret = regmap_पढ़ो(wm8400->regmap, WM8400_RESET_ID, &reg);
	अगर (ret != 0) अणु
		dev_err(wm8400->dev, "Chip ID register read failed\n");
		वापस -EIO;
	पूर्ण
	अगर (reg != 0x6172) अणु
		dev_err(wm8400->dev, "Device is not a WM8400, ID is %x\n",
			reg);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(wm8400->regmap, WM8400_ID, &reg);
	अगर (ret != 0) अणु
		dev_err(wm8400->dev, "ID register read failed: %d\n", ret);
		वापस ret;
	पूर्ण
	reg = (reg & WM8400_CHIP_REV_MASK) >> WM8400_CHIP_REV_SHIFT;
	dev_info(wm8400->dev, "WM8400 revision %x\n", reg);

	ret = wm8400_रेजिस्टर_codec(wm8400);
	अगर (ret != 0) अणु
		dev_err(wm8400->dev, "Failed to register codec\n");
		वापस ret;
	पूर्ण

	अगर (pdata && pdata->platक्रमm_init) अणु
		ret = pdata->platक्रमm_init(wm8400->dev);
		अगर (ret != 0) अणु
			dev_err(wm8400->dev, "Platform init failed: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा
		dev_warn(wm8400->dev, "No platform initialisation supplied\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config wm8400_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = WM8400_REGISTER_COUNT - 1,

	.अस्थिर_reg = wm8400_अस्थिर,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/**
 * wm8400_reset_codec_reg_cache - Reset cached codec रेजिस्टरs to
 * their शेष values.
 *
 * @wm8400: poपूर्णांकer to local driver data काष्ठाure
 */
व्योम wm8400_reset_codec_reg_cache(काष्ठा wm8400 *wm8400)
अणु
	regmap_reinit_cache(wm8400->regmap, &wm8400_regmap_config);
पूर्ण
EXPORT_SYMBOL_GPL(wm8400_reset_codec_reg_cache);

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8400_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8400 *wm8400;

	wm8400 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8400), GFP_KERNEL);
	अगर (!wm8400)
		वापस -ENOMEM;

	wm8400->regmap = devm_regmap_init_i2c(i2c, &wm8400_regmap_config);
	अगर (IS_ERR(wm8400->regmap))
		वापस PTR_ERR(wm8400->regmap);

	wm8400->dev = &i2c->dev;
	i2c_set_clientdata(i2c, wm8400);

	वापस wm8400_init(wm8400, dev_get_platdata(&i2c->dev));
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8400_i2c_id[] = अणु
       अणु "wm8400", 0 पूर्ण,
       अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver wm8400_i2c_driver = अणु
	.driver = अणु
		.name = "WM8400",
	पूर्ण,
	.probe    = wm8400_i2c_probe,
	.id_table = wm8400_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8400_driver_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8400_i2c_driver);
	अगर (ret != 0)
		pr_err("Failed to register I2C driver: %d\n", ret);
#पूर्ण_अगर

	वापस ret;
पूर्ण
subsys_initcall(wm8400_driver_init);
