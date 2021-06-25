<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ROHM BD9571MWV-M and BD9574MVF-M core driver
 *
 * Copyright (C) 2017 Marek Vasut <marek.vasut+renesas@gmail.com>
 * Copyright (C) 2020 Renesas Electronics Corporation
 *
 * Based on the TPS65086 driver
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>

#समावेश <linux/mfd/bd9571mwv.h>

अटल स्थिर काष्ठा mfd_cell bd9571mwv_cells[] = अणु
	अणु .name = "bd9571mwv-regulator", पूर्ण,
	अणु .name = "bd9571mwv-gpio", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9571mwv_पढ़ोable_yes_ranges[] = अणु
	regmap_reg_range(BD9571MWV_VENDOR_CODE, BD9571MWV_PRODUCT_REVISION),
	regmap_reg_range(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	regmap_reg_range(BD9571MWV_AVS_SET_MONI, BD9571MWV_AVS_DVFS_VID(3)),
	regmap_reg_range(BD9571MWV_VD18_VID, BD9571MWV_VD33_VID),
	regmap_reg_range(BD9571MWV_DVFS_VINIT, BD9571MWV_DVFS_VINIT),
	regmap_reg_range(BD9571MWV_DVFS_SETVMAX, BD9571MWV_DVFS_MONIVDAC),
	regmap_reg_range(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	regmap_reg_range(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INTMASK),
	regmap_reg_range(BD9571MWV_INT_INTREQ, BD9571MWV_INT_INTMASK),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9571mwv_पढ़ोable_table = अणु
	.yes_ranges	= bd9571mwv_पढ़ोable_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bd9571mwv_पढ़ोable_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9571mwv_writable_yes_ranges[] = अणु
	regmap_reg_range(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	regmap_reg_range(BD9571MWV_AVS_VD09_VID(0), BD9571MWV_AVS_VD09_VID(3)),
	regmap_reg_range(BD9571MWV_DVFS_SETVID, BD9571MWV_DVFS_SETVID),
	regmap_reg_range(BD9571MWV_GPIO_सूची, BD9571MWV_GPIO_OUT),
	regmap_reg_range(BD9571MWV_GPIO_INT_SET, BD9571MWV_GPIO_INTMASK),
	regmap_reg_range(BD9571MWV_INT_INTREQ, BD9571MWV_INT_INTMASK),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9571mwv_writable_table = अणु
	.yes_ranges	= bd9571mwv_writable_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bd9571mwv_writable_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9571mwv_अस्थिर_yes_ranges[] = अणु
	regmap_reg_range(BD9571MWV_DVFS_MONIVDAC, BD9571MWV_DVFS_MONIVDAC),
	regmap_reg_range(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	regmap_reg_range(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INT),
	regmap_reg_range(BD9571MWV_INT_INTREQ, BD9571MWV_INT_INTREQ),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9571mwv_अस्थिर_table = अणु
	.yes_ranges	= bd9571mwv_अस्थिर_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bd9571mwv_अस्थिर_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config bd9571mwv_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.cache_type	= REGCACHE_RBTREE,
	.rd_table	= &bd9571mwv_पढ़ोable_table,
	.wr_table	= &bd9571mwv_writable_table,
	.अस्थिर_table	= &bd9571mwv_अस्थिर_table,
	.max_रेजिस्टर	= 0xff,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq bd9571mwv_irqs[] = अणु
	REGMAP_IRQ_REG(BD9571MWV_IRQ_MD1, 0,
		       BD9571MWV_INT_INTREQ_MD1_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_MD2_E1, 0,
		       BD9571MWV_INT_INTREQ_MD2_E1_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_MD2_E2, 0,
		       BD9571MWV_INT_INTREQ_MD2_E2_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_PROT_ERR, 0,
		       BD9571MWV_INT_INTREQ_PROT_ERR_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_GP, 0,
		       BD9571MWV_INT_INTREQ_GP_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_128H_OF, 0,
		       BD9571MWV_INT_INTREQ_128H_OF_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_WDT_OF, 0,
		       BD9571MWV_INT_INTREQ_WDT_OF_INT),
	REGMAP_IRQ_REG(BD9571MWV_IRQ_BKUP_TRG, 0,
		       BD9571MWV_INT_INTREQ_BKUP_TRG_INT),
पूर्ण;

अटल काष्ठा regmap_irq_chip bd9571mwv_irq_chip = अणु
	.name		= "bd9571mwv",
	.status_base	= BD9571MWV_INT_INTREQ,
	.mask_base	= BD9571MWV_INT_INTMASK,
	.ack_base	= BD9571MWV_INT_INTREQ,
	.init_ack_masked = true,
	.num_regs	= 1,
	.irqs		= bd9571mwv_irqs,
	.num_irqs	= ARRAY_SIZE(bd9571mwv_irqs),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell bd9574mwf_cells[] = अणु
	अणु .name = "bd9574mwf-regulator", पूर्ण,
	अणु .name = "bd9574mwf-gpio", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9574mwf_पढ़ोable_yes_ranges[] = अणु
	regmap_reg_range(BD9571MWV_VENDOR_CODE, BD9571MWV_PRODUCT_REVISION),
	regmap_reg_range(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	regmap_reg_range(BD9571MWV_DVFS_VINIT, BD9571MWV_DVFS_SETVMAX),
	regmap_reg_range(BD9571MWV_DVFS_SETVID, BD9571MWV_DVFS_MONIVDAC),
	regmap_reg_range(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	regmap_reg_range(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INTMASK),
	regmap_reg_range(BD9571MWV_INT_INTREQ, BD9571MWV_INT_INTMASK),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9574mwf_पढ़ोable_table = अणु
	.yes_ranges	= bd9574mwf_पढ़ोable_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bd9574mwf_पढ़ोable_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9574mwf_writable_yes_ranges[] = अणु
	regmap_reg_range(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	regmap_reg_range(BD9571MWV_DVFS_SETVID, BD9571MWV_DVFS_SETVID),
	regmap_reg_range(BD9571MWV_GPIO_सूची, BD9571MWV_GPIO_OUT),
	regmap_reg_range(BD9571MWV_GPIO_INT_SET, BD9571MWV_GPIO_INTMASK),
	regmap_reg_range(BD9571MWV_INT_INTREQ, BD9571MWV_INT_INTMASK),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9574mwf_writable_table = अणु
	.yes_ranges	= bd9574mwf_writable_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bd9574mwf_writable_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range bd9574mwf_अस्थिर_yes_ranges[] = अणु
	regmap_reg_range(BD9571MWV_DVFS_MONIVDAC, BD9571MWV_DVFS_MONIVDAC),
	regmap_reg_range(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	regmap_reg_range(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INT),
	regmap_reg_range(BD9571MWV_INT_INTREQ, BD9571MWV_INT_INTREQ),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bd9574mwf_अस्थिर_table = अणु
	.yes_ranges	= bd9574mwf_अस्थिर_yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bd9574mwf_अस्थिर_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config bd9574mwf_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.cache_type	= REGCACHE_RBTREE,
	.rd_table	= &bd9574mwf_पढ़ोable_table,
	.wr_table	= &bd9574mwf_writable_table,
	.अस्थिर_table	= &bd9574mwf_अस्थिर_table,
	.max_रेजिस्टर	= 0xff,
पूर्ण;

अटल काष्ठा regmap_irq_chip bd9574mwf_irq_chip = अणु
	.name		= "bd9574mwf",
	.status_base	= BD9571MWV_INT_INTREQ,
	.mask_base	= BD9571MWV_INT_INTMASK,
	.ack_base	= BD9571MWV_INT_INTREQ,
	.init_ack_masked = true,
	.num_regs	= 1,
	.irqs		= bd9571mwv_irqs,
	.num_irqs	= ARRAY_SIZE(bd9571mwv_irqs),
पूर्ण;

अटल पूर्णांक bd957x_identअगरy(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, BD9571MWV_VENDOR_CODE, &value);
	अगर (ret) अणु
		dev_err(dev, "Failed to read vendor code register (ret=%i)\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (value != BD9571MWV_VENDOR_CODE_VAL) अणु
		dev_err(dev, "Invalid vendor code ID %02x (expected %02x)\n",
			value, BD9571MWV_VENDOR_CODE_VAL);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(regmap, BD9571MWV_PRODUCT_CODE, &value);
	अगर (ret) अणु
		dev_err(dev, "Failed to read product code register (ret=%i)\n",
			ret);
		वापस ret;
	पूर्ण
	ret = regmap_पढ़ो(regmap, BD9571MWV_PRODUCT_REVISION, &value);
	अगर (ret) अणु
		dev_err(dev, "Failed to read revision register (ret=%i)\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd9571mwv_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *ids)
अणु
	स्थिर काष्ठा regmap_config *regmap_config;
	स्थिर काष्ठा regmap_irq_chip *irq_chip;
	स्थिर काष्ठा mfd_cell *cells;
	काष्ठा device *dev = &client->dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक ret, num_cells, irq = client->irq;

	/* Read the PMIC product code */
	ret = i2c_smbus_पढ़ो_byte_data(client, BD9571MWV_PRODUCT_CODE);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read product code\n");
		वापस ret;
	पूर्ण

	चयन (ret) अणु
	हाल BD9571MWV_PRODUCT_CODE_BD9571MWV:
		regmap_config = &bd9571mwv_regmap_config;
		irq_chip = &bd9571mwv_irq_chip;
		cells = bd9571mwv_cells;
		num_cells = ARRAY_SIZE(bd9571mwv_cells);
		अवरोध;
	हाल BD9571MWV_PRODUCT_CODE_BD9574MWF:
		regmap_config = &bd9574mwf_regmap_config;
		irq_chip = &bd9574mwf_irq_chip;
		cells = bd9574mwf_cells;
		num_cells = ARRAY_SIZE(bd9574mwf_cells);
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported device 0x%x\n", ret);
		वापस -ENODEV;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to initialize register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = bd957x_identअगरy(dev, regmap);
	अगर (ret)
		वापस ret;

	ret = devm_regmap_add_irq_chip(dev, regmap, irq, IRQF_ONESHOT, 0,
				       irq_chip, &irq_data);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IRQ chip\n");
		वापस ret;
	पूर्ण

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_AUTO, cells, num_cells,
				    शून्य, 0, regmap_irq_get_करोमुख्य(irq_data));
पूर्ण

अटल स्थिर काष्ठा of_device_id bd9571mwv_of_match_table[] = अणु
	अणु .compatible = "rohm,bd9571mwv", पूर्ण,
	अणु .compatible = "rohm,bd9574mwf", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bd9571mwv_of_match_table);

अटल स्थिर काष्ठा i2c_device_id bd9571mwv_id_table[] = अणु
	अणु "bd9571mwv", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bd9571mwv_id_table);

अटल काष्ठा i2c_driver bd9571mwv_driver = अणु
	.driver		= अणु
		.name	= "bd9571mwv",
		.of_match_table = bd9571mwv_of_match_table,
	पूर्ण,
	.probe		= bd9571mwv_probe,
	.id_table       = bd9571mwv_id_table,
पूर्ण;
module_i2c_driver(bd9571mwv_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut+renesas@gmail.com>");
MODULE_DESCRIPTION("BD9571MWV PMIC Driver");
MODULE_LICENSE("GPL v2");
