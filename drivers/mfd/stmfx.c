<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम STMicroelectronics Multi-Function eXpander (STMFX) core
 *
 * Copyright (C) 2019 STMicroelectronics
 * Author(s): Amelie Delaunay <amelie.delaunay@st.com>.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/sपंचांगfx.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>

अटल bool sपंचांगfx_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STMFX_REG_SYS_CTRL:
	हाल STMFX_REG_IRQ_SRC_EN:
	हाल STMFX_REG_IRQ_PENDING:
	हाल STMFX_REG_IRQ_GPI_PENDING1:
	हाल STMFX_REG_IRQ_GPI_PENDING2:
	हाल STMFX_REG_IRQ_GPI_PENDING3:
	हाल STMFX_REG_GPIO_STATE1:
	हाल STMFX_REG_GPIO_STATE2:
	हाल STMFX_REG_GPIO_STATE3:
	हाल STMFX_REG_IRQ_GPI_SRC1:
	हाल STMFX_REG_IRQ_GPI_SRC2:
	हाल STMFX_REG_IRQ_GPI_SRC3:
	हाल STMFX_REG_GPO_SET1:
	हाल STMFX_REG_GPO_SET2:
	हाल STMFX_REG_GPO_SET3:
	हाल STMFX_REG_GPO_CLR1:
	हाल STMFX_REG_GPO_CLR2:
	हाल STMFX_REG_GPO_CLR3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool sपंचांगfx_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg >= STMFX_REG_SYS_CTRL);
पूर्ण

अटल स्थिर काष्ठा regmap_config sपंचांगfx_regmap_config = अणु
	.reg_bits	= 8,
	.reg_stride	= 1,
	.val_bits	= 8,
	.max_रेजिस्टर	= STMFX_REG_MAX,
	.अस्थिर_reg	= sपंचांगfx_reg_अस्थिर,
	.ग_लिखोable_reg	= sपंचांगfx_reg_ग_लिखोable,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा resource sपंचांगfx_pinctrl_resources[] = अणु
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_GPIO),
पूर्ण;

अटल स्थिर काष्ठा resource sपंचांगfx_idd_resources[] = अणु
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_IDD),
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_ERROR),
पूर्ण;

अटल स्थिर काष्ठा resource sपंचांगfx_ts_resources[] = अणु
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_TS_DET),
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_TS_NE),
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_TS_TH),
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_TS_FULL),
	DEFINE_RES_IRQ(STMFX_REG_IRQ_SRC_EN_TS_OVF),
पूर्ण;

अटल काष्ठा mfd_cell sपंचांगfx_cells[] = अणु
	अणु
		.of_compatible = "st,stmfx-0300-pinctrl",
		.name = "stmfx-pinctrl",
		.resources = sपंचांगfx_pinctrl_resources,
		.num_resources = ARRAY_SIZE(sपंचांगfx_pinctrl_resources),
	पूर्ण,
	अणु
		.of_compatible = "st,stmfx-0300-idd",
		.name = "stmfx-idd",
		.resources = sपंचांगfx_idd_resources,
		.num_resources = ARRAY_SIZE(sपंचांगfx_idd_resources),
	पूर्ण,
	अणु
		.of_compatible = "st,stmfx-0300-ts",
		.name = "stmfx-ts",
		.resources = sपंचांगfx_ts_resources,
		.num_resources = ARRAY_SIZE(sपंचांगfx_ts_resources),
	पूर्ण,
पूर्ण;

अटल u8 sपंचांगfx_func_to_mask(u32 func)
अणु
	u8 mask = 0;

	अगर (func & STMFX_FUNC_GPIO)
		mask |= STMFX_REG_SYS_CTRL_GPIO_EN;

	अगर ((func & STMFX_FUNC_ALTGPIO_LOW) || (func & STMFX_FUNC_ALTGPIO_HIGH))
		mask |= STMFX_REG_SYS_CTRL_ALTGPIO_EN;

	अगर (func & STMFX_FUNC_TS)
		mask |= STMFX_REG_SYS_CTRL_TS_EN;

	अगर (func & STMFX_FUNC_IDD)
		mask |= STMFX_REG_SYS_CTRL_IDD_EN;

	वापस mask;
पूर्ण

पूर्णांक sपंचांगfx_function_enable(काष्ठा sपंचांगfx *sपंचांगfx, u32 func)
अणु
	u32 sys_ctrl;
	u8 mask;
	पूर्णांक ret;

	ret = regmap_पढ़ो(sपंचांगfx->map, STMFX_REG_SYS_CTRL, &sys_ctrl);
	अगर (ret)
		वापस ret;

	/*
	 * IDD and TS have priority in STMFX FW, so अगर IDD and TS are enabled,
	 * ALTGPIO function is disabled by STMFX FW. If IDD or TS is enabled,
	 * the number of aGPIO available decreases. To aव्योम GPIO management
	 * disturbance, पात IDD or TS function enable in this हाल.
	 */
	अगर (((func & STMFX_FUNC_IDD) || (func & STMFX_FUNC_TS)) &&
	    (sys_ctrl & STMFX_REG_SYS_CTRL_ALTGPIO_EN)) अणु
		dev_err(sपंचांगfx->dev, "ALTGPIO function already enabled\n");
		वापस -EBUSY;
	पूर्ण

	/* If TS is enabled, aGPIO[3:0] cannot be used */
	अगर ((func & STMFX_FUNC_ALTGPIO_LOW) &&
	    (sys_ctrl & STMFX_REG_SYS_CTRL_TS_EN)) अणु
		dev_err(sपंचांगfx->dev, "TS in use, aGPIO[3:0] unavailable\n");
		वापस -EBUSY;
	पूर्ण

	/* If IDD is enabled, aGPIO[7:4] cannot be used */
	अगर ((func & STMFX_FUNC_ALTGPIO_HIGH) &&
	    (sys_ctrl & STMFX_REG_SYS_CTRL_IDD_EN)) अणु
		dev_err(sपंचांगfx->dev, "IDD in use, aGPIO[7:4] unavailable\n");
		वापस -EBUSY;
	पूर्ण

	mask = sपंचांगfx_func_to_mask(func);

	वापस regmap_update_bits(sपंचांगfx->map, STMFX_REG_SYS_CTRL, mask, mask);
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगfx_function_enable);

पूर्णांक sपंचांगfx_function_disable(काष्ठा sपंचांगfx *sपंचांगfx, u32 func)
अणु
	u8 mask = sपंचांगfx_func_to_mask(func);

	वापस regmap_update_bits(sपंचांगfx->map, STMFX_REG_SYS_CTRL, mask, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांगfx_function_disable);

अटल व्योम sपंचांगfx_irq_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = irq_data_get_irq_chip_data(data);

	mutex_lock(&sपंचांगfx->lock);
पूर्ण

अटल व्योम sपंचांगfx_irq_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = irq_data_get_irq_chip_data(data);

	regmap_ग_लिखो(sपंचांगfx->map, STMFX_REG_IRQ_SRC_EN, sपंचांगfx->irq_src);

	mutex_unlock(&sपंचांगfx->lock);
पूर्ण

अटल व्योम sपंचांगfx_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = irq_data_get_irq_chip_data(data);

	sपंचांगfx->irq_src &= ~BIT(data->hwirq % 8);
पूर्ण

अटल व्योम sपंचांगfx_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = irq_data_get_irq_chip_data(data);

	sपंचांगfx->irq_src |= BIT(data->hwirq % 8);
पूर्ण

अटल काष्ठा irq_chip sपंचांगfx_irq_chip = अणु
	.name			= "stmfx-core",
	.irq_bus_lock		= sपंचांगfx_irq_bus_lock,
	.irq_bus_sync_unlock	= sपंचांगfx_irq_bus_sync_unlock,
	.irq_mask		= sपंचांगfx_irq_mask,
	.irq_unmask		= sपंचांगfx_irq_unmask,
पूर्ण;

अटल irqवापस_t sपंचांगfx_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = data;
	अचिन्हित दीर्घ bits;
	u32 pending, ack;
	पूर्णांक n, ret;

	ret = regmap_पढ़ो(sपंचांगfx->map, STMFX_REG_IRQ_PENDING, &pending);
	अगर (ret)
		वापस IRQ_NONE;

	/*
	 * There is no ACK क्रम GPIO, MFX_REG_IRQ_PENDING_GPIO is a logical OR
	 * of MFX_REG_IRQ_GPI _PENDING1/_PENDING2/_PENDING3
	 */
	ack = pending & ~BIT(STMFX_REG_IRQ_SRC_EN_GPIO);
	अगर (ack) अणु
		ret = regmap_ग_लिखो(sपंचांगfx->map, STMFX_REG_IRQ_ACK, ack);
		अगर (ret)
			वापस IRQ_NONE;
	पूर्ण

	bits = pending;
	क्रम_each_set_bit(n, &bits, STMFX_REG_IRQ_SRC_MAX)
		handle_nested_irq(irq_find_mapping(sपंचांगfx->irq_करोमुख्य, n));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांगfx_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(virq, d->host_data);
	irq_set_chip_and_handler(virq, &sपंचांगfx_irq_chip, handle_simple_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल व्योम sपंचांगfx_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
	irq_set_chip_and_handler(virq, शून्य, शून्य);
	irq_set_chip_data(virq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sपंचांगfx_irq_ops = अणु
	.map	= sपंचांगfx_irq_map,
	.unmap	= sपंचांगfx_irq_unmap,
पूर्ण;

अटल व्योम sपंचांगfx_irq_निकास(काष्ठा i2c_client *client)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = i2c_get_clientdata(client);
	पूर्णांक hwirq;

	क्रम (hwirq = 0; hwirq < STMFX_REG_IRQ_SRC_MAX; hwirq++)
		irq_dispose_mapping(irq_find_mapping(sपंचांगfx->irq_करोमुख्य, hwirq));

	irq_करोमुख्य_हटाओ(sपंचांगfx->irq_करोमुख्य);
पूर्ण

अटल पूर्णांक sपंचांगfx_irq_init(काष्ठा i2c_client *client)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = i2c_get_clientdata(client);
	u32 irqoutpin = 0, irqtrigger;
	पूर्णांक ret;

	sपंचांगfx->irq_करोमुख्य = irq_करोमुख्य_add_simple(sपंचांगfx->dev->of_node,
						  STMFX_REG_IRQ_SRC_MAX, 0,
						  &sपंचांगfx_irq_ops, sपंचांगfx);
	अगर (!sपंचांगfx->irq_करोमुख्य) अणु
		dev_err(sपंचांगfx->dev, "Failed to create IRQ domain\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!of_property_पढ़ो_bool(sपंचांगfx->dev->of_node, "drive-open-drain"))
		irqoutpin |= STMFX_REG_IRQ_OUT_PIN_TYPE;

	irqtrigger = irq_get_trigger_type(client->irq);
	अगर ((irqtrigger & IRQ_TYPE_EDGE_RISING) ||
	    (irqtrigger & IRQ_TYPE_LEVEL_HIGH))
		irqoutpin |= STMFX_REG_IRQ_OUT_PIN_POL;

	ret = regmap_ग_लिखो(sपंचांगfx->map, STMFX_REG_IRQ_OUT_PIN, irqoutpin);
	अगर (ret)
		जाओ irq_निकास;

	ret = devm_request_thपढ़ोed_irq(sपंचांगfx->dev, client->irq,
					शून्य, sपंचांगfx_irq_handler,
					irqtrigger | IRQF_ONESHOT,
					"stmfx", sपंचांगfx);
	अगर (ret)
		जाओ irq_निकास;

	sपंचांगfx->irq = client->irq;

	वापस 0;

irq_निकास:
	sपंचांगfx_irq_निकास(client);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगfx_chip_reset(काष्ठा sपंचांगfx *sपंचांगfx)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(sपंचांगfx->map, STMFX_REG_SYS_CTRL,
			   STMFX_REG_SYS_CTRL_SWRST);
	अगर (ret)
		वापस ret;

	msleep(STMFX_BOOT_TIME_MS);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगfx_chip_init(काष्ठा i2c_client *client)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = i2c_get_clientdata(client);
	u32 id;
	u8 version[2];
	पूर्णांक ret;

	sपंचांगfx->vdd = devm_regulator_get_optional(&client->dev, "vdd");
	ret = PTR_ERR_OR_ZERO(sपंचांगfx->vdd);
	अगर (ret) अणु
		अगर (ret == -ENODEV)
			sपंचांगfx->vdd = शून्य;
		अन्यथा
			वापस dev_err_probe(&client->dev, ret, "Failed to get VDD regulator\n");
	पूर्ण

	अगर (sपंचांगfx->vdd) अणु
		ret = regulator_enable(sपंचांगfx->vdd);
		अगर (ret) अणु
			dev_err(&client->dev, "VDD enable failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regmap_पढ़ो(sपंचांगfx->map, STMFX_REG_CHIP_ID, &id);
	अगर (ret) अणु
		dev_err(&client->dev, "Error reading chip ID: %d\n", ret);
		जाओ err;
	पूर्ण

	/*
	 * Check that ID is the complement of the I2C address:
	 * STMFX I2C address follows the 7-bit क्रमmat (MSB), that's why
	 * client->addr is shअगरted.
	 *
	 * STMFX_I2C_ADDR|       STMFX         |        Linux
	 *   input pin   | I2C device address  | I2C device address
	 *---------------------------------------------------------
	 *       0       | b: 1000 010x h:0x84 |       0x42
	 *       1       | b: 1000 011x h:0x86 |       0x43
	 */
	अगर (FIELD_GET(STMFX_REG_CHIP_ID_MASK, ~id) != (client->addr << 1)) अणु
		dev_err(&client->dev, "Unknown chip ID: %#x\n", id);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = regmap_bulk_पढ़ो(sपंचांगfx->map, STMFX_REG_FW_VERSION_MSB,
			       version, ARRAY_SIZE(version));
	अगर (ret) अणु
		dev_err(&client->dev, "Error reading FW version: %d\n", ret);
		जाओ err;
	पूर्ण

	dev_info(&client->dev, "STMFX id: %#x, fw version: %x.%02x\n",
		 id, version[0], version[1]);

	ret = sपंचांगfx_chip_reset(sपंचांगfx);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to reset chip: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	अगर (sपंचांगfx->vdd)
		वापस regulator_disable(sपंचांगfx->vdd);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगfx_chip_निकास(काष्ठा i2c_client *client)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = i2c_get_clientdata(client);

	regmap_ग_लिखो(sपंचांगfx->map, STMFX_REG_IRQ_SRC_EN, 0);
	regmap_ग_लिखो(sपंचांगfx->map, STMFX_REG_SYS_CTRL, 0);

	अगर (sपंचांगfx->vdd)
		वापस regulator_disable(sपंचांगfx->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा sपंचांगfx *sपंचांगfx;
	पूर्णांक ret;

	sपंचांगfx = devm_kzalloc(dev, माप(*sपंचांगfx), GFP_KERNEL);
	अगर (!sपंचांगfx)
		वापस -ENOMEM;

	i2c_set_clientdata(client, sपंचांगfx);

	sपंचांगfx->dev = dev;

	sपंचांगfx->map = devm_regmap_init_i2c(client, &sपंचांगfx_regmap_config);
	अगर (IS_ERR(sपंचांगfx->map)) अणु
		ret = PTR_ERR(sपंचांगfx->map);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	mutex_init(&sपंचांगfx->lock);

	ret = sपंचांगfx_chip_init(client);
	अगर (ret) अणु
		अगर (ret == -ETIMEDOUT)
			वापस -EPROBE_DEFER;
		वापस ret;
	पूर्ण

	अगर (client->irq < 0) अणु
		dev_err(dev, "Failed to get IRQ: %d\n", client->irq);
		ret = client->irq;
		जाओ err_chip_निकास;
	पूर्ण

	ret = sपंचांगfx_irq_init(client);
	अगर (ret)
		जाओ err_chip_निकास;

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				   sपंचांगfx_cells, ARRAY_SIZE(sपंचांगfx_cells), शून्य,
				   0, sपंचांगfx->irq_करोमुख्य);
	अगर (ret)
		जाओ err_irq_निकास;

	वापस 0;

err_irq_निकास:
	sपंचांगfx_irq_निकास(client);
err_chip_निकास:
	sपंचांगfx_chip_निकास(client);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगfx_हटाओ(काष्ठा i2c_client *client)
अणु
	sपंचांगfx_irq_निकास(client);

	वापस sपंचांगfx_chip_निकास(client);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांगfx_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_raw_पढ़ो(sपंचांगfx->map, STMFX_REG_SYS_CTRL,
			      &sपंचांगfx->bkp_sysctrl, माप(sपंचांगfx->bkp_sysctrl));
	अगर (ret)
		वापस ret;

	ret = regmap_raw_पढ़ो(sपंचांगfx->map, STMFX_REG_IRQ_OUT_PIN,
			      &sपंचांगfx->bkp_irqoutpin,
			      माप(sपंचांगfx->bkp_irqoutpin));
	अगर (ret)
		वापस ret;

	disable_irq(sपंचांगfx->irq);

	अगर (sपंचांगfx->vdd)
		वापस regulator_disable(sपंचांगfx->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगfx_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांगfx *sपंचांगfx = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (sपंचांगfx->vdd) अणु
		ret = regulator_enable(sपंचांगfx->vdd);
		अगर (ret) अणु
			dev_err(sपंचांगfx->dev,
				"VDD enable failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Reset STMFX - supply has been stopped during suspend */
	ret = sपंचांगfx_chip_reset(sपंचांगfx);
	अगर (ret) अणु
		dev_err(sपंचांगfx->dev, "Failed to reset chip: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_raw_ग_लिखो(sपंचांगfx->map, STMFX_REG_SYS_CTRL,
			       &sपंचांगfx->bkp_sysctrl, माप(sपंचांगfx->bkp_sysctrl));
	अगर (ret)
		वापस ret;

	ret = regmap_raw_ग_लिखो(sपंचांगfx->map, STMFX_REG_IRQ_OUT_PIN,
			       &sपंचांगfx->bkp_irqoutpin,
			       माप(sपंचांगfx->bkp_irqoutpin));
	अगर (ret)
		वापस ret;

	ret = regmap_raw_ग_लिखो(sपंचांगfx->map, STMFX_REG_IRQ_SRC_EN,
			       &sपंचांगfx->irq_src, माप(sपंचांगfx->irq_src));
	अगर (ret)
		वापस ret;

	enable_irq(sपंचांगfx->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sपंचांगfx_dev_pm_ops, sपंचांगfx_suspend, sपंचांगfx_resume);

अटल स्थिर काष्ठा of_device_id sपंचांगfx_of_match[] = अणु
	अणु .compatible = "st,stmfx-0300", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगfx_of_match);

अटल काष्ठा i2c_driver sपंचांगfx_driver = अणु
	.driver = अणु
		.name = "stmfx-core",
		.of_match_table = sपंचांगfx_of_match,
		.pm = &sपंचांगfx_dev_pm_ops,
	पूर्ण,
	.probe = sपंचांगfx_probe,
	.हटाओ = sपंचांगfx_हटाओ,
पूर्ण;
module_i2c_driver(sपंचांगfx_driver);

MODULE_DESCRIPTION("STMFX core driver");
MODULE_AUTHOR("Amelie Delaunay <amelie.delaunay@st.com>");
MODULE_LICENSE("GPL v2");
