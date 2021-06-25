<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
//
// Copyright (C) 2018 ROHM Semiconductors
//
// ROHM BD71837MWV and BD71847MWV PMIC driver
//
// Datasheet क्रम BD71837MWV available from
// https://www.rohm.com/datasheet/BD71837MWV/bd71837mwv-e

#समावेश <linux/gpio_keys.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/rohm-bd718x7.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

अटल काष्ठा gpio_keys_button button = अणु
	.code = KEY_POWER,
	.gpio = -1,
	.type = EV_KEY,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data bd718xx_घातerkey_data = अणु
	.buttons = &button,
	.nbuttons = 1,
	.name = "bd718xx-pwrkey",
पूर्ण;

अटल काष्ठा mfd_cell bd71837_mfd_cells[] = अणु
	अणु
		.name = "gpio-keys",
		.platक्रमm_data = &bd718xx_घातerkey_data,
		.pdata_size = माप(bd718xx_घातerkey_data),
	पूर्ण,
	अणु .name = "bd71837-clk", पूर्ण,
	अणु .name = "bd71837-pmic", पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell bd71847_mfd_cells[] = अणु
	अणु
		.name = "gpio-keys",
		.platक्रमm_data = &bd718xx_घातerkey_data,
		.pdata_size = माप(bd718xx_घातerkey_data),
	पूर्ण,
	अणु .name = "bd71847-clk", पूर्ण,
	अणु .name = "bd71847-pmic", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bd718xx_irqs[] = अणु
	REGMAP_IRQ_REG(BD718XX_INT_SWRST, 0, BD718XX_INT_SWRST_MASK),
	REGMAP_IRQ_REG(BD718XX_INT_PWRBTN_S, 0, BD718XX_INT_PWRBTN_S_MASK),
	REGMAP_IRQ_REG(BD718XX_INT_PWRBTN_L, 0, BD718XX_INT_PWRBTN_L_MASK),
	REGMAP_IRQ_REG(BD718XX_INT_PWRBTN, 0, BD718XX_INT_PWRBTN_MASK),
	REGMAP_IRQ_REG(BD718XX_INT_WDOG, 0, BD718XX_INT_WDOG_MASK),
	REGMAP_IRQ_REG(BD718XX_INT_ON_REQ, 0, BD718XX_INT_ON_REQ_MASK),
	REGMAP_IRQ_REG(BD718XX_INT_STBY_REQ, 0, BD718XX_INT_STBY_REQ_MASK),
पूर्ण;

अटल काष्ठा regmap_irq_chip bd718xx_irq_chip = अणु
	.name = "bd718xx-irq",
	.irqs = bd718xx_irqs,
	.num_irqs = ARRAY_SIZE(bd718xx_irqs),
	.num_regs = 1,
	.irq_reg_stride = 1,
	.status_base = BD718XX_REG_IRQ,
	.mask_base = BD718XX_REG_MIRQ,
	.ack_base = BD718XX_REG_IRQ,
	.init_ack_masked = true,
	.mask_invert = false,
पूर्ण;

अटल स्थिर काष्ठा regmap_range pmic_status_range = अणु
	.range_min = BD718XX_REG_IRQ,
	.range_max = BD718XX_REG_POW_STATE,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table अस्थिर_regs = अणु
	.yes_ranges = &pmic_status_range,
	.n_yes_ranges = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bd718xx_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &अस्थिर_regs,
	.max_रेजिस्टर = BD718XX_MAX_REGISTER - 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक bd718xx_init_press_duration(काष्ठा regmap *regmap,
				       काष्ठा device *dev)
अणु
	u32 लघु_press_ms, दीर्घ_press_ms;
	u32 लघु_press_value, दीर्घ_press_value;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(dev->of_node, "rohm,short-press-ms",
				   &लघु_press_ms);
	अगर (!ret) अणु
		लघु_press_value = min(15u, (लघु_press_ms + 250) / 500);
		ret = regmap_update_bits(regmap, BD718XX_REG_PWRONCONFIG0,
					 BD718XX_PWRBTN_PRESS_DURATION_MASK,
					 लघु_press_value);
		अगर (ret) अणु
			dev_err(dev, "Failed to init pwron short press\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "rohm,long-press-ms",
				   &दीर्घ_press_ms);
	अगर (!ret) अणु
		दीर्घ_press_value = min(15u, (दीर्घ_press_ms + 500) / 1000);
		ret = regmap_update_bits(regmap, BD718XX_REG_PWRONCONFIG1,
					 BD718XX_PWRBTN_PRESS_DURATION_MASK,
					 दीर्घ_press_value);
		अगर (ret) अणु
			dev_err(dev, "Failed to init pwron long press\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd718xx_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक ret;
	अचिन्हित पूर्णांक chip_type;
	काष्ठा mfd_cell *mfd;
	पूर्णांक cells;

	अगर (!i2c->irq) अणु
		dev_err(&i2c->dev, "No IRQ configured\n");
		वापस -EINVAL;
	पूर्ण
	chip_type = (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)
		    of_device_get_match_data(&i2c->dev);
	चयन (chip_type) अणु
	हाल ROHM_CHIP_TYPE_BD71837:
		mfd = bd71837_mfd_cells;
		cells = ARRAY_SIZE(bd71837_mfd_cells);
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71847:
		mfd = bd71847_mfd_cells;
		cells = ARRAY_SIZE(bd71847_mfd_cells);
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unknown device type");
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init_i2c(i2c, &bd718xx_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i2c->dev, "regmap initialization failed\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = devm_regmap_add_irq_chip(&i2c->dev, regmap, i2c->irq,
				       IRQF_ONESHOT, 0, &bd718xx_irq_chip,
				       &irq_data);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to add irq_chip\n");
		वापस ret;
	पूर्ण

	ret = bd718xx_init_press_duration(regmap, &i2c->dev);
	अगर (ret)
		वापस ret;

	ret = regmap_irq_get_virq(irq_data, BD718XX_INT_PWRBTN_S);

	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to get the IRQ\n");
		वापस ret;
	पूर्ण

	button.irq = ret;

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO,
				   mfd, cells, शून्य, 0,
				   regmap_irq_get_करोमुख्य(irq_data));
	अगर (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bd718xx_of_match[] = अणु
	अणु
		.compatible = "rohm,bd71837",
		.data = (व्योम *)ROHM_CHIP_TYPE_BD71837,
	पूर्ण,
	अणु
		.compatible = "rohm,bd71847",
		.data = (व्योम *)ROHM_CHIP_TYPE_BD71847,
	पूर्ण,
	अणु
		.compatible = "rohm,bd71850",
		.data = (व्योम *)ROHM_CHIP_TYPE_BD71847,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bd718xx_of_match);

अटल काष्ठा i2c_driver bd718xx_i2c_driver = अणु
	.driver = अणु
		.name = "rohm-bd718x7",
		.of_match_table = bd718xx_of_match,
	पूर्ण,
	.probe = bd718xx_i2c_probe,
पूर्ण;

अटल पूर्णांक __init bd718xx_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&bd718xx_i2c_driver);
पूर्ण

/* Initialise early so consumer devices can complete प्रणाली boot */
subsys_initcall(bd718xx_i2c_init);

अटल व्योम __निकास bd718xx_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&bd718xx_i2c_driver);
पूर्ण
module_निकास(bd718xx_i2c_निकास);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD71837/BD71847 Power Management IC driver");
MODULE_LICENSE("GPL");
