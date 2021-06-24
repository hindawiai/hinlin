<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* MCP23S08 SPI GPIO driver */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "pinctrl-mcp23s08.h"

#घोषणा MCP_MAX_DEV_PER_CS	8

/*
 * A given spi_device can represent up to eight mcp23sxx chips
 * sharing the same chipselect but using dअगरferent addresses
 * (e.g. chips #0 and #3 might be populated, but not #1 or #2).
 * Driver data holds all the per-chip data.
 */
काष्ठा mcp23s08_driver_data अणु
	अचिन्हित		ngpio;
	काष्ठा mcp23s08		*mcp[8];
	काष्ठा mcp23s08		chip[];
पूर्ण;

अटल पूर्णांक mcp23sxx_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा mcp23s08 *mcp = context;
	काष्ठा spi_device *spi = to_spi_device(mcp->dev);
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[2] = अणु अणु .tx_buf = &mcp->addr, .len = 1, पूर्ण,
				     अणु .tx_buf = data, .len = count, पूर्ण, पूर्ण;

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	वापस spi_sync(spi, &m);
पूर्ण

अटल पूर्णांक mcp23sxx_spi_gather_ग_लिखो(व्योम *context,
				स्थिर व्योम *reg, माप_प्रकार reg_size,
				स्थिर व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा mcp23s08 *mcp = context;
	काष्ठा spi_device *spi = to_spi_device(mcp->dev);
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[3] = अणु अणु .tx_buf = &mcp->addr, .len = 1, पूर्ण,
				     अणु .tx_buf = reg, .len = reg_size, पूर्ण,
				     अणु .tx_buf = val, .len = val_size, पूर्ण, पूर्ण;

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);
	spi_message_add_tail(&t[2], &m);

	वापस spi_sync(spi, &m);
पूर्ण

अटल पूर्णांक mcp23sxx_spi_पढ़ो(व्योम *context, स्थिर व्योम *reg, माप_प्रकार reg_size,
				व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा mcp23s08 *mcp = context;
	काष्ठा spi_device *spi = to_spi_device(mcp->dev);
	u8 tx[2];

	अगर (reg_size != 1)
		वापस -EINVAL;

	tx[0] = mcp->addr | 0x01;
	tx[1] = *((u8 *) reg);

	वापस spi_ग_लिखो_then_पढ़ो(spi, tx, माप(tx), val, val_size);
पूर्ण

अटल स्थिर काष्ठा regmap_bus mcp23sxx_spi_regmap = अणु
	.ग_लिखो = mcp23sxx_spi_ग_लिखो,
	.gather_ग_लिखो = mcp23sxx_spi_gather_ग_लिखो,
	.पढ़ो = mcp23sxx_spi_पढ़ो,
पूर्ण;

अटल पूर्णांक mcp23s08_spi_regmap_init(काष्ठा mcp23s08 *mcp, काष्ठा device *dev,
				    अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक type)
अणु
	स्थिर काष्ठा regmap_config *config;
	काष्ठा regmap_config *copy;
	स्थिर अक्षर *name;

	चयन (type) अणु
	हाल MCP_TYPE_S08:
		mcp->reg_shअगरt = 0;
		mcp->chip.ngpio = 8;
		mcp->chip.label = devm_kaप्र_लिखो(dev, GFP_KERNEL, "mcp23s08.%d", addr);

		config = &mcp23x08_regmap;
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%d", addr);
		अवरोध;

	हाल MCP_TYPE_S17:
		mcp->reg_shअगरt = 1;
		mcp->chip.ngpio = 16;
		mcp->chip.label = devm_kaप्र_लिखो(dev, GFP_KERNEL, "mcp23s17.%d", addr);

		config = &mcp23x17_regmap;
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%d", addr);
		अवरोध;

	हाल MCP_TYPE_S18:
		mcp->reg_shअगरt = 1;
		mcp->chip.ngpio = 16;
		mcp->chip.label = "mcp23s18";

		config = &mcp23x17_regmap;
		name = config->name;
		अवरोध;

	शेष:
		dev_err(dev, "invalid device type (%d)\n", type);
		वापस -EINVAL;
	पूर्ण

	copy = devm_kmemdup(dev, config, माप(*config), GFP_KERNEL);
	अगर (!copy)
		वापस -ENOMEM;

	copy->name = name;

	mcp->regmap = devm_regmap_init(dev, &mcp23sxx_spi_regmap, mcp, copy);
	अगर (IS_ERR(mcp->regmap))
		dev_err(dev, "regmap init failed for %s\n", mcp->chip.label);
	वापस PTR_ERR_OR_ZERO(mcp->regmap);
पूर्ण

अटल पूर्णांक mcp23s08_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा mcp23s08_driver_data *data;
	अचिन्हित दीर्घ spi_present_mask;
	स्थिर व्योम *match;
	अचिन्हित पूर्णांक addr;
	अचिन्हित पूर्णांक ngpio = 0;
	पूर्णांक chips;
	पूर्णांक type;
	पूर्णांक ret;
	u32 v;

	match = device_get_match_data(dev);
	अगर (match)
		type = (पूर्णांक)(uपूर्णांकptr_t)match;
	अन्यथा
		type = spi_get_device_id(spi)->driver_data;

	ret = device_property_पढ़ो_u32(dev, "microchip,spi-present-mask", &v);
	अगर (ret) अणु
		ret = device_property_पढ़ो_u32(dev, "mcp,spi-present-mask", &v);
		अगर (ret) अणु
			dev_err(dev, "missing spi-present-mask");
			वापस ret;
		पूर्ण
	पूर्ण
	spi_present_mask = v;

	अगर (!spi_present_mask || spi_present_mask >= BIT(MCP_MAX_DEV_PER_CS)) अणु
		dev_err(dev, "invalid spi-present-mask");
		वापस -ENODEV;
	पूर्ण

	chips = hweight_दीर्घ(spi_present_mask);

	data = devm_kzalloc(dev, काष्ठा_size(data, chip, chips), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spi_set_drvdata(spi, data);

	क्रम_each_set_bit(addr, &spi_present_mask, MCP_MAX_DEV_PER_CS) अणु
		data->mcp[addr] = &data->chip[--chips];
		data->mcp[addr]->irq = spi->irq;

		ret = mcp23s08_spi_regmap_init(data->mcp[addr], dev, addr, type);
		अगर (ret)
			वापस ret;

		data->mcp[addr]->pinctrl_desc.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
								    "mcp23xxx-pinctrl.%d",
								    addr);
		अगर (!data->mcp[addr]->pinctrl_desc.name)
			वापस -ENOMEM;

		ret = mcp23s08_probe_one(data->mcp[addr], dev, 0x40 | (addr << 1), type, -1);
		अगर (ret < 0)
			वापस ret;

		ngpio += data->mcp[addr]->chip.ngpio;
	पूर्ण
	data->ngpio = ngpio;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id mcp23s08_ids[] = अणु
	अणु "mcp23s08", MCP_TYPE_S08 पूर्ण,
	अणु "mcp23s17", MCP_TYPE_S17 पूर्ण,
	अणु "mcp23s18", MCP_TYPE_S18 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp23s08_ids);

अटल स्थिर काष्ठा of_device_id mcp23s08_spi_of_match[] = अणु
	अणु
		.compatible = "microchip,mcp23s08",
		.data = (व्योम *) MCP_TYPE_S08,
	पूर्ण,
	अणु
		.compatible = "microchip,mcp23s17",
		.data = (व्योम *) MCP_TYPE_S17,
	पूर्ण,
	अणु
		.compatible = "microchip,mcp23s18",
		.data = (व्योम *) MCP_TYPE_S18,
	पूर्ण,
/* NOTE: The use of the mcp prefix is deprecated and will be हटाओd. */
	अणु
		.compatible = "mcp,mcp23s08",
		.data = (व्योम *) MCP_TYPE_S08,
	पूर्ण,
	अणु
		.compatible = "mcp,mcp23s17",
		.data = (व्योम *) MCP_TYPE_S17,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp23s08_spi_of_match);

अटल काष्ठा spi_driver mcp23s08_driver = अणु
	.probe		= mcp23s08_probe,
	.id_table	= mcp23s08_ids,
	.driver = अणु
		.name	= "mcp23s08",
		.of_match_table = mcp23s08_spi_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mcp23s08_spi_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&mcp23s08_driver);
पूर्ण

/*
 * Register after SPI postcore initcall and beक्रमe
 * subsys initcalls that may rely on these GPIOs.
 */
subsys_initcall(mcp23s08_spi_init);

अटल व्योम mcp23s08_spi_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&mcp23s08_driver);
पूर्ण
module_निकास(mcp23s08_spi_निकास);

MODULE_LICENSE("GPL");
