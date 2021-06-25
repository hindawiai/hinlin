<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2021 ROHM Semiconductors
 *
 * ROHM BD9576MUF and BD9573MUF PMIC driver
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rohm-bd957x.h>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

क्रमागत अणु
	BD957X_REGULATOR_CELL,
	BD957X_WDT_CELL,
पूर्ण;

/*
 * Due to the BD9576MUF nasty IRQ behaiour we करोn't always populate IRQs.
 * These will be added to regulator resources only अगर IRQ inक्रमmation क्रम the
 * PMIC is populated in device-tree.
 */
अटल स्थिर काष्ठा resource bd9576_regulator_irqs[] = अणु
	DEFINE_RES_IRQ_NAMED(BD9576_INT_THERM, "bd9576-temp"),
	DEFINE_RES_IRQ_NAMED(BD9576_INT_OVD, "bd9576-ovd"),
	DEFINE_RES_IRQ_NAMED(BD9576_INT_UVD, "bd9576-uvd"),
पूर्ण;

अटल काष्ठा mfd_cell bd9573_mfd_cells[] = अणु
	[BD957X_REGULATOR_CELL]	= अणु .name = "bd9573-regulator", पूर्ण,
	[BD957X_WDT_CELL]	= अणु .name = "bd9576-wdt", पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell bd9576_mfd_cells[] = अणु
	[BD957X_REGULATOR_CELL]	= अणु .name = "bd9576-regulator", पूर्ण,
	[BD957X_WDT_CELL]	= अणु .name = "bd9576-wdt", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range अस्थिर_ranges[] = अणु
	regmap_reg_range(BD957X_REG_SMRB_ASSERT, BD957X_REG_SMRB_ASSERT),
	regmap_reg_range(BD957X_REG_PMIC_INTERNAL_STAT,
			 BD957X_REG_PMIC_INTERNAL_STAT),
	regmap_reg_range(BD957X_REG_INT_THERM_STAT, BD957X_REG_INT_THERM_STAT),
	regmap_reg_range(BD957X_REG_INT_OVP_STAT, BD957X_REG_INT_SYS_STAT),
	regmap_reg_range(BD957X_REG_INT_MAIN_STAT, BD957X_REG_INT_MAIN_STAT),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table अस्थिर_regs = अणु
	.yes_ranges = &अस्थिर_ranges[0],
	.n_yes_ranges = ARRAY_SIZE(अस्थिर_ranges),
पूर्ण;

अटल काष्ठा regmap_config bd957x_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &अस्थिर_regs,
	.max_रेजिस्टर = BD957X_MAX_REGISTER,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा regmap_irq bd9576_irqs[] = अणु
	REGMAP_IRQ_REG(BD9576_INT_THERM, 0, BD957X_MASK_INT_MAIN_THERM),
	REGMAP_IRQ_REG(BD9576_INT_OVP, 0, BD957X_MASK_INT_MAIN_OVP),
	REGMAP_IRQ_REG(BD9576_INT_SCP, 0, BD957X_MASK_INT_MAIN_SCP),
	REGMAP_IRQ_REG(BD9576_INT_OCP, 0, BD957X_MASK_INT_MAIN_OCP),
	REGMAP_IRQ_REG(BD9576_INT_OVD, 0, BD957X_MASK_INT_MAIN_OVD),
	REGMAP_IRQ_REG(BD9576_INT_UVD, 0, BD957X_MASK_INT_MAIN_UVD),
	REGMAP_IRQ_REG(BD9576_INT_UVP, 0, BD957X_MASK_INT_MAIN_UVP),
	REGMAP_IRQ_REG(BD9576_INT_SYS, 0, BD957X_MASK_INT_MAIN_SYS),
पूर्ण;

अटल काष्ठा regmap_irq_chip bd9576_irq_chip = अणु
	.name = "bd9576_irq",
	.irqs = &bd9576_irqs[0],
	.num_irqs = ARRAY_SIZE(bd9576_irqs),
	.status_base = BD957X_REG_INT_MAIN_STAT,
	.mask_base = BD957X_REG_INT_MAIN_MASK,
	.ack_base = BD957X_REG_INT_MAIN_STAT,
	.init_ack_masked = true,
	.num_regs = 1,
	.irq_reg_stride = 1,
पूर्ण;

अटल पूर्णांक bd957x_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा regmap *regmap;
	काष्ठा mfd_cell *cells;
	पूर्णांक num_cells;
	अचिन्हित दीर्घ chip_type;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	bool usable_irqs;

	chip_type = (अचिन्हित दीर्घ)of_device_get_match_data(&i2c->dev);

	चयन (chip_type) अणु
	हाल ROHM_CHIP_TYPE_BD9576:
		cells = bd9576_mfd_cells;
		num_cells = ARRAY_SIZE(bd9576_mfd_cells);
		usable_irqs = !!i2c->irq;
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD9573:
		cells = bd9573_mfd_cells;
		num_cells = ARRAY_SIZE(bd9573_mfd_cells);
		/*
		 * BD9573 only supports fatal IRQs which we can not handle
		 * because SoC is going to lose the घातer.
		 */
		usable_irqs = false;
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unknown device type");
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init_i2c(i2c, &bd957x_regmap);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i2c->dev, "Failed to initialize Regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/*
	 * BD9576 behaves badly. It kepts IRQ line निश्चितed क्रम the whole
	 * duration of detected HW condition (like over temperature). So we
	 * करोn't require IRQ to be populated.
	 * If IRQ inक्रमmation is not given, then we mask all IRQs and करो not
	 * provide IRQ resources to regulator driver - which then just omits
	 * the notअगरiers.
	 */
	अगर (usable_irqs) अणु
		काष्ठा regmap_irq_chip_data *irq_data;
		काष्ठा mfd_cell *regulators;

		regulators = &bd9576_mfd_cells[BD957X_REGULATOR_CELL];
		regulators->resources = bd9576_regulator_irqs;
		regulators->num_resources = ARRAY_SIZE(bd9576_regulator_irqs);

		ret = devm_regmap_add_irq_chip(&i2c->dev, regmap, i2c->irq,
					       IRQF_ONESHOT, 0,
					       &bd9576_irq_chip, &irq_data);
		अगर (ret) अणु
			dev_err(&i2c->dev, "Failed to add IRQ chip\n");
			वापस ret;
		पूर्ण
		करोमुख्य = regmap_irq_get_करोमुख्य(irq_data);
	पूर्ण अन्यथा अणु
		ret = regmap_update_bits(regmap, BD957X_REG_INT_MAIN_MASK,
					 BD957X_MASK_INT_ALL,
					 BD957X_MASK_INT_ALL);
		अगर (ret)
			वापस ret;
		करोमुख्य = शून्य;
	पूर्ण

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_AUTO, cells,
				   num_cells, शून्य, 0, करोमुख्य);
	अगर (ret)
		dev_err(&i2c->dev, "Failed to create subdevices\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bd957x_of_match[] = अणु
	अणु .compatible = "rohm,bd9576", .data = (व्योम *)ROHM_CHIP_TYPE_BD9576, पूर्ण,
	अणु .compatible = "rohm,bd9573", .data = (व्योम *)ROHM_CHIP_TYPE_BD9573, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bd957x_of_match);

अटल काष्ठा i2c_driver bd957x_drv = अणु
	.driver = अणु
		.name = "rohm-bd957x",
		.of_match_table = bd957x_of_match,
	पूर्ण,
	.probe = &bd957x_i2c_probe,
पूर्ण;
module_i2c_driver(bd957x_drv);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("ROHM BD9576MUF and BD9573MUF Power Management IC driver");
MODULE_LICENSE("GPL");
