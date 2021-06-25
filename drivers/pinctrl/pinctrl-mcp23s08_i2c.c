<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* MCP23S08 I2C GPIO driver */

#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "pinctrl-mcp23s08.h"

अटल पूर्णांक mcp230xx_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	अचिन्हित पूर्णांक type = id->driver_data;
	काष्ठा mcp23s08 *mcp;
	पूर्णांक ret;

	mcp = devm_kzalloc(dev, माप(*mcp), GFP_KERNEL);
	अगर (!mcp)
		वापस -ENOMEM;

	चयन (type) अणु
	हाल MCP_TYPE_008:
		mcp->regmap = devm_regmap_init_i2c(client, &mcp23x08_regmap);
		mcp->reg_shअगरt = 0;
		mcp->chip.ngpio = 8;
		mcp->chip.label = "mcp23008";
		अवरोध;

	हाल MCP_TYPE_017:
		mcp->regmap = devm_regmap_init_i2c(client, &mcp23x17_regmap);
		mcp->reg_shअगरt = 1;
		mcp->chip.ngpio = 16;
		mcp->chip.label = "mcp23017";
		अवरोध;

	हाल MCP_TYPE_018:
		mcp->regmap = devm_regmap_init_i2c(client, &mcp23x17_regmap);
		mcp->reg_shअगरt = 1;
		mcp->chip.ngpio = 16;
		mcp->chip.label = "mcp23018";
		अवरोध;

	शेष:
		dev_err(dev, "invalid device type (%d)\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(mcp->regmap))
		वापस PTR_ERR(mcp->regmap);

	mcp->irq = client->irq;
	mcp->pinctrl_desc.name = "mcp23xxx-pinctrl";

	ret = mcp23s08_probe_one(mcp, dev, client->addr, type, -1);
	अगर (ret)
		वापस ret;

	i2c_set_clientdata(client, mcp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mcp230xx_id[] = अणु
	अणु "mcp23008", MCP_TYPE_008 पूर्ण,
	अणु "mcp23017", MCP_TYPE_017 पूर्ण,
	अणु "mcp23018", MCP_TYPE_018 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp230xx_id);

अटल स्थिर काष्ठा of_device_id mcp23s08_i2c_of_match[] = अणु
	अणु
		.compatible = "microchip,mcp23008",
		.data = (व्योम *) MCP_TYPE_008,
	पूर्ण,
	अणु
		.compatible = "microchip,mcp23017",
		.data = (व्योम *) MCP_TYPE_017,
	पूर्ण,
	अणु
		.compatible = "microchip,mcp23018",
		.data = (व्योम *) MCP_TYPE_018,
	पूर्ण,
/* NOTE: The use of the mcp prefix is deprecated and will be हटाओd. */
	अणु
		.compatible = "mcp,mcp23008",
		.data = (व्योम *) MCP_TYPE_008,
	पूर्ण,
	अणु
		.compatible = "mcp,mcp23017",
		.data = (व्योम *) MCP_TYPE_017,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp23s08_i2c_of_match);

अटल काष्ठा i2c_driver mcp230xx_driver = अणु
	.driver = अणु
		.name	= "mcp230xx",
		.of_match_table = mcp23s08_i2c_of_match,
	पूर्ण,
	.probe		= mcp230xx_probe,
	.id_table	= mcp230xx_id,
पूर्ण;

अटल पूर्णांक __init mcp23s08_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&mcp230xx_driver);
पूर्ण

/*
 * Register after IतऑC postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs.
 */
subsys_initcall(mcp23s08_i2c_init);

अटल व्योम mcp23s08_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&mcp230xx_driver);
पूर्ण
module_निकास(mcp23s08_i2c_निकास);

MODULE_LICENSE("GPL");
