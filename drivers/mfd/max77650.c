<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 BayLibre SAS
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
//
// Core MFD driver क्रम MAXIM 77650/77651 अक्षरger/घातer-supply.
// Programming manual: https://pdfserv.maximपूर्णांकegrated.com/en/an/AN6428.pdf

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max77650.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#घोषणा MAX77650_INT_GPI_F_MSK		BIT(0)
#घोषणा MAX77650_INT_GPI_R_MSK		BIT(1)
#घोषणा MAX77650_INT_GPI_MSK \
			(MAX77650_INT_GPI_F_MSK | MAX77650_INT_GPI_R_MSK)
#घोषणा MAX77650_INT_nEN_F_MSK		BIT(2)
#घोषणा MAX77650_INT_nEN_R_MSK		BIT(3)
#घोषणा MAX77650_INT_TJAL1_R_MSK	BIT(4)
#घोषणा MAX77650_INT_TJAL2_R_MSK	BIT(5)
#घोषणा MAX77650_INT_DOD_R_MSK		BIT(6)

#घोषणा MAX77650_INT_THM_MSK		BIT(0)
#घोषणा MAX77650_INT_CHG_MSK		BIT(1)
#घोषणा MAX77650_INT_CHGIN_MSK		BIT(2)
#घोषणा MAX77650_INT_TJ_REG_MSK		BIT(3)
#घोषणा MAX77650_INT_CHGIN_CTRL_MSK	BIT(4)
#घोषणा MAX77650_INT_SYS_CTRL_MSK	BIT(5)
#घोषणा MAX77650_INT_SYS_CNFG_MSK	BIT(6)

#घोषणा MAX77650_INT_GLBL_OFFSET	0
#घोषणा MAX77650_INT_CHG_OFFSET		1

#घोषणा MAX77650_SBIA_LPM_MASK		BIT(5)
#घोषणा MAX77650_SBIA_LPM_DISABLED	0x00

क्रमागत अणु
	MAX77650_INT_GPI,
	MAX77650_INT_nEN_F,
	MAX77650_INT_nEN_R,
	MAX77650_INT_TJAL1_R,
	MAX77650_INT_TJAL2_R,
	MAX77650_INT_DOD_R,
	MAX77650_INT_THM,
	MAX77650_INT_CHG,
	MAX77650_INT_CHGIN,
	MAX77650_INT_TJ_REG,
	MAX77650_INT_CHGIN_CTRL,
	MAX77650_INT_SYS_CTRL,
	MAX77650_INT_SYS_CNFG,
पूर्ण;

अटल स्थिर काष्ठा resource max77650_अक्षरger_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MAX77650_INT_CHG, "CHG"),
	DEFINE_RES_IRQ_NAMED(MAX77650_INT_CHGIN, "CHGIN"),
पूर्ण;

अटल स्थिर काष्ठा resource max77650_gpio_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MAX77650_INT_GPI, "GPI"),
पूर्ण;

अटल स्थिर काष्ठा resource max77650_onkey_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(MAX77650_INT_nEN_F, "nEN_F"),
	DEFINE_RES_IRQ_NAMED(MAX77650_INT_nEN_R, "nEN_R"),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell max77650_cells[] = अणु
	अणु
		.name		= "max77650-regulator",
		.of_compatible	= "maxim,max77650-regulator",
	पूर्ण, अणु
		.name		= "max77650-charger",
		.of_compatible	= "maxim,max77650-charger",
		.resources	= max77650_अक्षरger_resources,
		.num_resources	= ARRAY_SIZE(max77650_अक्षरger_resources),
	पूर्ण, अणु
		.name		= "max77650-gpio",
		.of_compatible	= "maxim,max77650-gpio",
		.resources	= max77650_gpio_resources,
		.num_resources	= ARRAY_SIZE(max77650_gpio_resources),
	पूर्ण, अणु
		.name		= "max77650-led",
		.of_compatible	= "maxim,max77650-led",
	पूर्ण, अणु
		.name		= "max77650-onkey",
		.of_compatible	= "maxim,max77650-onkey",
		.resources	= max77650_onkey_resources,
		.num_resources	= ARRAY_SIZE(max77650_onkey_resources),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77650_irqs[] = अणु
	[MAX77650_INT_GPI] = अणु
		.reg_offset = MAX77650_INT_GLBL_OFFSET,
		.mask = MAX77650_INT_GPI_MSK,
		.type = अणु
			.type_falling_val = MAX77650_INT_GPI_F_MSK,
			.type_rising_val = MAX77650_INT_GPI_R_MSK,
			.types_supported = IRQ_TYPE_EDGE_BOTH,
		पूर्ण,
	पूर्ण,
	REGMAP_IRQ_REG(MAX77650_INT_nEN_F,
		       MAX77650_INT_GLBL_OFFSET, MAX77650_INT_nEN_F_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_nEN_R,
		       MAX77650_INT_GLBL_OFFSET, MAX77650_INT_nEN_R_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_TJAL1_R,
		       MAX77650_INT_GLBL_OFFSET, MAX77650_INT_TJAL1_R_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_TJAL2_R,
		       MAX77650_INT_GLBL_OFFSET, MAX77650_INT_TJAL2_R_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_DOD_R,
		       MAX77650_INT_GLBL_OFFSET, MAX77650_INT_DOD_R_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_THM,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_THM_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_CHG,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_CHG_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_CHGIN,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_CHGIN_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_TJ_REG,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_TJ_REG_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_CHGIN_CTRL,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_CHGIN_CTRL_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_SYS_CTRL,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_SYS_CTRL_MSK),
	REGMAP_IRQ_REG(MAX77650_INT_SYS_CNFG,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_SYS_CNFG_MSK),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77650_irq_chip = अणु
	.name			= "max77650-irq",
	.irqs			= max77650_irqs,
	.num_irqs		= ARRAY_SIZE(max77650_irqs),
	.num_regs		= 2,
	.status_base		= MAX77650_REG_INT_GLBL,
	.mask_base		= MAX77650_REG_INTM_GLBL,
	.type_in_mask		= true,
	.type_invert		= true,
	.init_ack_masked	= true,
	.clear_on_unmask	= true,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77650_regmap_config = अणु
	.name		= "max77650",
	.reg_bits	= 8,
	.val_bits	= 8,
पूर्ण;

अटल पूर्णांक max77650_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regmap_irq_chip_data *irq_data;
	काष्ठा device *dev = &i2c->dev;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक val;
	पूर्णांक rv, id;

	map = devm_regmap_init_i2c(i2c, &max77650_regmap_config);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "Unable to initialise I2C Regmap\n");
		वापस PTR_ERR(map);
	पूर्ण

	rv = regmap_पढ़ो(map, MAX77650_REG_CID, &val);
	अगर (rv) अणु
		dev_err(dev, "Unable to read Chip ID\n");
		वापस rv;
	पूर्ण

	id = MAX77650_CID_BITS(val);
	चयन (id) अणु
	हाल MAX77650_CID_77650A:
	हाल MAX77650_CID_77650C:
	हाल MAX77650_CID_77651A:
	हाल MAX77650_CID_77651B:
		अवरोध;
	शेष:
		dev_err(dev, "Chip not supported - ID: 0x%02x\n", id);
		वापस -ENODEV;
	पूर्ण

	/*
	 * This IC has a low-घातer mode which reduces the quiescent current
	 * consumption to ~5.6uA but is only suitable क्रम प्रणालीs consuming
	 * less than ~2mA. Since this is not likely the हाल even on
	 * linux-based wearables - keep the chip in normal घातer mode.
	 */
	rv = regmap_update_bits(map,
				MAX77650_REG_CNFG_GLBL,
				MAX77650_SBIA_LPM_MASK,
				MAX77650_SBIA_LPM_DISABLED);
	अगर (rv) अणु
		dev_err(dev, "Unable to change the power mode\n");
		वापस rv;
	पूर्ण

	rv = devm_regmap_add_irq_chip(dev, map, i2c->irq,
				      IRQF_ONESHOT | IRQF_SHARED, 0,
				      &max77650_irq_chip, &irq_data);
	अगर (rv) अणु
		dev_err(dev, "Unable to add Regmap IRQ chip\n");
		वापस rv;
	पूर्ण

	करोमुख्य = regmap_irq_get_करोमुख्य(irq_data);

	वापस devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				    max77650_cells, ARRAY_SIZE(max77650_cells),
				    शून्य, 0, करोमुख्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id max77650_of_match[] = अणु
	अणु .compatible = "maxim,max77650" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max77650_of_match);

अटल काष्ठा i2c_driver max77650_i2c_driver = अणु
	.driver = अणु
		.name = "max77650",
		.of_match_table = max77650_of_match,
	पूर्ण,
	.probe_new = max77650_i2c_probe,
पूर्ण;
module_i2c_driver(max77650_i2c_driver);

MODULE_DESCRIPTION("MAXIM 77650/77651 multi-function core driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL v2");
