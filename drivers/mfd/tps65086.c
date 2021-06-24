<शैली गुरु>
/*
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 *
 * Based on the TPS65912 driver
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>

#समावेश <linux/mfd/tps65086.h>

अटल स्थिर काष्ठा mfd_cell tps65086_cells[] = अणु
	अणु .name = "tps65086-regulator", पूर्ण,
	अणु .name = "tps65086-gpio", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range tps65086_yes_ranges[] = अणु
	regmap_reg_range(TPS65086_IRQ, TPS65086_IRQ),
	regmap_reg_range(TPS65086_PMICSTAT, TPS65086_SHUTDNSRC),
	regmap_reg_range(TPS65086_GPOCTRL, TPS65086_GPOCTRL),
	regmap_reg_range(TPS65086_PG_STATUS1, TPS65086_OC_STATUS),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tps65086_अस्थिर_table = अणु
	.yes_ranges = tps65086_yes_ranges,
	.n_yes_ranges = ARRAY_SIZE(tps65086_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config tps65086_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_table = &tps65086_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq tps65086_irqs[] = अणु
	REGMAP_IRQ_REG(TPS65086_IRQ_DIETEMP, 0, TPS65086_IRQ_DIETEMP_MASK),
	REGMAP_IRQ_REG(TPS65086_IRQ_SHUTDN, 0, TPS65086_IRQ_SHUTDN_MASK),
	REGMAP_IRQ_REG(TPS65086_IRQ_FAULT, 0, TPS65086_IRQ_FAULT_MASK),
पूर्ण;

अटल काष्ठा regmap_irq_chip tps65086_irq_chip = अणु
	.name = "tps65086",
	.status_base = TPS65086_IRQ,
	.mask_base = TPS65086_IRQ_MASK,
	.ack_base = TPS65086_IRQ,
	.init_ack_masked = true,
	.num_regs = 1,
	.irqs = tps65086_irqs,
	.num_irqs = ARRAY_SIZE(tps65086_irqs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id tps65086_of_match_table[] = अणु
	अणु .compatible = "ti,tps65086", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65086_of_match_table);

अटल पूर्णांक tps65086_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *ids)
अणु
	काष्ठा tps65086 *tps;
	अचिन्हित पूर्णांक version;
	पूर्णांक ret;

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;
	tps->irq = client->irq;

	tps->regmap = devm_regmap_init_i2c(client, &tps65086_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		dev_err(tps->dev, "Failed to initialize register map\n");
		वापस PTR_ERR(tps->regmap);
	पूर्ण

	ret = regmap_पढ़ो(tps->regmap, TPS65086_DEVICEID, &version);
	अगर (ret) अणु
		dev_err(tps->dev, "Failed to read revision register\n");
		वापस ret;
	पूर्ण

	dev_info(tps->dev, "Device: TPS65086%01lX, OTP: %c, Rev: %ld\n",
		 (version & TPS65086_DEVICEID_PART_MASK),
		 (अक्षर)((version & TPS65086_DEVICEID_OTP_MASK) >> 4) + 'A',
		 (version & TPS65086_DEVICEID_REV_MASK) >> 6);

	ret = regmap_add_irq_chip(tps->regmap, tps->irq, IRQF_ONESHOT, 0,
				  &tps65086_irq_chip, &tps->irq_data);
	अगर (ret) अणु
		dev_err(tps->dev, "Failed to register IRQ chip\n");
		वापस ret;
	पूर्ण

	ret = mfd_add_devices(tps->dev, PLATFORM_DEVID_AUTO, tps65086_cells,
			      ARRAY_SIZE(tps65086_cells), शून्य, 0,
			      regmap_irq_get_करोमुख्य(tps->irq_data));
	अगर (ret) अणु
		regmap_del_irq_chip(tps->irq, tps->irq_data);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65086_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps65086 *tps = i2c_get_clientdata(client);

	regmap_del_irq_chip(tps->irq, tps->irq_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65086_id_table[] = अणु
	अणु "tps65086", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps65086_id_table);

अटल काष्ठा i2c_driver tps65086_driver = अणु
	.driver		= अणु
		.name	= "tps65086",
		.of_match_table = tps65086_of_match_table,
	पूर्ण,
	.probe		= tps65086_probe,
	.हटाओ		= tps65086_हटाओ,
	.id_table       = tps65086_id_table,
पूर्ण;
module_i2c_driver(tps65086_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPS65086 PMIC Driver");
MODULE_LICENSE("GPL v2");
