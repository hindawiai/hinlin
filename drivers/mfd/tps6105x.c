<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम TPS61050/61052 boost converters, used क्रम जबतक LED
 * driving, audio घातer amplअगरication, white LED flash, and generic
 * boost conversion. Additionally it provides a 1-bit GPIO pin (out or in)
 * and a flash synchronization pin to synchronize flash events when used as
 * flashgun.
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps6105x.h>

अटल काष्ठा regmap_config tps6105x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TPS6105X_REG_3,
पूर्ण;

अटल पूर्णांक tps6105x_startup(काष्ठा tps6105x *tps6105x)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	ret = regmap_पढ़ो(tps6105x->regmap, TPS6105X_REG_0, &regval);
	अगर (ret)
		वापस ret;
	चयन (regval >> TPS6105X_REG0_MODE_SHIFT) अणु
	हाल TPS6105X_REG0_MODE_SHUTDOWN:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in SHUTDOWN mode\n");
		अवरोध;
	हाल TPS6105X_REG0_MODE_TORCH:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in TORCH mode\n");
		अवरोध;
	हाल TPS6105X_REG0_MODE_TORCH_FLASH:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in FLASH mode\n");
		अवरोध;
	हाल TPS6105X_REG0_MODE_VOLTAGE:
		dev_info(&tps6105x->client->dev,
			 "TPS6105x found in VOLTAGE mode\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * MFD cells - we always have a GPIO cell and we have one cell
 * which is selected operation mode.
 */
अटल काष्ठा mfd_cell tps6105x_gpio_cell = अणु
	.name = "tps6105x-gpio",
पूर्ण;

अटल काष्ठा mfd_cell tps6105x_leds_cell = अणु
	.name = "tps6105x-leds",
पूर्ण;

अटल काष्ठा mfd_cell tps6105x_flash_cell = अणु
	.name = "tps6105x-flash",
पूर्ण;

अटल काष्ठा mfd_cell tps6105x_regulator_cell = अणु
	.name = "tps6105x-regulator",
पूर्ण;

अटल पूर्णांक tps6105x_add_device(काष्ठा tps6105x *tps6105x,
			       काष्ठा mfd_cell *cell)
अणु
	cell->platक्रमm_data = tps6105x;
	cell->pdata_size = माप(*tps6105x);

	वापस mfd_add_devices(&tps6105x->client->dev,
			       PLATFORM_DEVID_AUTO, cell, 1, शून्य, 0, शून्य);
पूर्ण

अटल काष्ठा tps6105x_platक्रमm_data *tps6105x_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा tps6105x_platक्रमm_data *pdata;
	काष्ठा device_node *child;

	अगर (!np)
		वापस ERR_PTR(-EINVAL);
	अगर (of_get_available_child_count(np) > 1) अणु
		dev_err(dev, "cannot support multiple operational modes");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);
	pdata->mode = TPS6105X_MODE_SHUTDOWN;
	क्रम_each_available_child_of_node(np, child) अणु
		अगर (child->name && !of_node_cmp(child->name, "regulator"))
			pdata->mode = TPS6105X_MODE_VOLTAGE;
		अन्यथा अगर (child->name && !of_node_cmp(child->name, "led"))
			pdata->mode = TPS6105X_MODE_TORCH;
	पूर्ण

	वापस pdata;
पूर्ण

अटल पूर्णांक tps6105x_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps6105x			*tps6105x;
	काष्ठा tps6105x_platक्रमm_data	*pdata;
	पूर्णांक ret;

	pdata = dev_get_platdata(&client->dev);
	अगर (!pdata)
		pdata = tps6105x_parse_dt(&client->dev);
	अगर (IS_ERR(pdata)) अणु
		dev_err(&client->dev, "No platform data or DT found");
		वापस PTR_ERR(pdata);
	पूर्ण

	tps6105x = devm_kदो_स्मृति(&client->dev, माप(*tps6105x), GFP_KERNEL);
	अगर (!tps6105x)
		वापस -ENOMEM;

	tps6105x->regmap = devm_regmap_init_i2c(client, &tps6105x_regmap_config);
	अगर (IS_ERR(tps6105x->regmap))
		वापस PTR_ERR(tps6105x->regmap);

	i2c_set_clientdata(client, tps6105x);
	tps6105x->client = client;
	tps6105x->pdata = pdata;

	ret = tps6105x_startup(tps6105x);
	अगर (ret) अणु
		dev_err(&client->dev, "chip initialization failed\n");
		वापस ret;
	पूर्ण

	ret = tps6105x_add_device(tps6105x, &tps6105x_gpio_cell);
	अगर (ret)
		वापस ret;

	चयन (pdata->mode) अणु
	हाल TPS6105X_MODE_SHUTDOWN:
		dev_info(&client->dev,
			 "present, not used for anything, only GPIO\n");
		अवरोध;
	हाल TPS6105X_MODE_TORCH:
		ret = tps6105x_add_device(tps6105x, &tps6105x_leds_cell);
		अवरोध;
	हाल TPS6105X_MODE_TORCH_FLASH:
		ret = tps6105x_add_device(tps6105x, &tps6105x_flash_cell);
		अवरोध;
	हाल TPS6105X_MODE_VOLTAGE:
		ret = tps6105x_add_device(tps6105x, &tps6105x_regulator_cell);
		अवरोध;
	शेष:
		dev_warn(&client->dev, "invalid mode: %d\n", pdata->mode);
		अवरोध;
	पूर्ण

	अगर (ret)
		mfd_हटाओ_devices(&client->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tps6105x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps6105x *tps6105x = i2c_get_clientdata(client);

	mfd_हटाओ_devices(&client->dev);

	/* Put chip in shutकरोwn mode */
	regmap_update_bits(tps6105x->regmap, TPS6105X_REG_0,
		TPS6105X_REG0_MODE_MASK,
		TPS6105X_MODE_SHUTDOWN << TPS6105X_REG0_MODE_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps6105x_id[] = अणु
	अणु "tps61050", 0 पूर्ण,
	अणु "tps61052", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps6105x_id);

अटल स्थिर काष्ठा of_device_id tps6105x_of_match[] = अणु
	अणु .compatible = "ti,tps61050" पूर्ण,
	अणु .compatible = "ti,tps61052" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps6105x_of_match);

अटल काष्ठा i2c_driver tps6105x_driver = अणु
	.driver = अणु
		.name	= "tps6105x",
		.of_match_table = tps6105x_of_match,
	पूर्ण,
	.probe		= tps6105x_probe,
	.हटाओ		= tps6105x_हटाओ,
	.id_table	= tps6105x_id,
पूर्ण;

अटल पूर्णांक __init tps6105x_init(व्योम)
अणु
	वापस i2c_add_driver(&tps6105x_driver);
पूर्ण
subsys_initcall(tps6105x_init);

अटल व्योम __निकास tps6105x_निकास(व्योम)
अणु
	i2c_del_driver(&tps6105x_driver);
पूर्ण
module_निकास(tps6105x_निकास);

MODULE_AUTHOR("Linus Walleij");
MODULE_DESCRIPTION("TPS6105x White LED Boost Converter Driver");
MODULE_LICENSE("GPL v2");
