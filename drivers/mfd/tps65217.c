<शैली गुरु>
/*
 * tps65217.c
 *
 * TPS65217 chip family multi-function driver
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps65217.h>

अटल स्थिर काष्ठा resource अक्षरger_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(TPS65217_IRQ_AC, "AC"),
	DEFINE_RES_IRQ_NAMED(TPS65217_IRQ_USB, "USB"),
पूर्ण;

अटल स्थिर काष्ठा resource pb_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(TPS65217_IRQ_PB, "PB"),
पूर्ण;

अटल व्योम tps65217_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा tps65217 *tps = irq_data_get_irq_chip_data(data);

	mutex_lock(&tps->irq_lock);
पूर्ण

अटल व्योम tps65217_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा tps65217 *tps = irq_data_get_irq_chip_data(data);
	पूर्णांक ret;

	ret = tps65217_set_bits(tps, TPS65217_REG_INT, TPS65217_INT_MASK,
				tps->irq_mask, TPS65217_PROTECT_NONE);
	अगर (ret != 0)
		dev_err(tps->dev, "Failed to sync IRQ masks\n");

	mutex_unlock(&tps->irq_lock);
पूर्ण

अटल व्योम tps65217_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा tps65217 *tps = irq_data_get_irq_chip_data(data);
	u8 mask = BIT(data->hwirq) << TPS65217_INT_SHIFT;

	tps->irq_mask &= ~mask;
पूर्ण

अटल व्योम tps65217_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा tps65217 *tps = irq_data_get_irq_chip_data(data);
	u8 mask = BIT(data->hwirq) << TPS65217_INT_SHIFT;

	tps->irq_mask |= mask;
पूर्ण

अटल काष्ठा irq_chip tps65217_irq_chip = अणु
	.name			= "tps65217",
	.irq_bus_lock		= tps65217_irq_lock,
	.irq_bus_sync_unlock	= tps65217_irq_sync_unlock,
	.irq_enable		= tps65217_irq_enable,
	.irq_disable		= tps65217_irq_disable,
पूर्ण;

अटल काष्ठा mfd_cell tps65217s[] = अणु
	अणु
		.name = "tps65217-pmic",
		.of_compatible = "ti,tps65217-pmic",
	पूर्ण,
	अणु
		.name = "tps65217-bl",
		.of_compatible = "ti,tps65217-bl",
	पूर्ण,
	अणु
		.name = "tps65217-charger",
		.num_resources = ARRAY_SIZE(अक्षरger_resources),
		.resources = अक्षरger_resources,
		.of_compatible = "ti,tps65217-charger",
	पूर्ण,
	अणु
		.name = "tps65217-pwrbutton",
		.num_resources = ARRAY_SIZE(pb_resources),
		.resources = pb_resources,
		.of_compatible = "ti,tps65217-pwrbutton",
	पूर्ण,
पूर्ण;

अटल irqवापस_t tps65217_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tps65217 *tps = data;
	अचिन्हित पूर्णांक status;
	bool handled = false;
	पूर्णांक i;
	पूर्णांक ret;

	ret = tps65217_reg_पढ़ो(tps, TPS65217_REG_INT, &status);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "Failed to read IRQ status: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	क्रम (i = 0; i < TPS65217_NUM_IRQ; i++) अणु
		अगर (status & BIT(i)) अणु
			handle_nested_irq(irq_find_mapping(tps->irq_करोमुख्य, i));
			handled = true;
		पूर्ण
	पूर्ण

	अगर (handled)
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक tps65217_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			irq_hw_number_t hw)
अणु
	काष्ठा tps65217 *tps = h->host_data;

	irq_set_chip_data(virq, tps);
	irq_set_chip_and_handler(virq, &tps65217_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_parent(virq, tps->irq);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops tps65217_irq_करोमुख्य_ops = अणु
	.map = tps65217_irq_map,
पूर्ण;

अटल पूर्णांक tps65217_irq_init(काष्ठा tps65217 *tps, पूर्णांक irq)
अणु
	पूर्णांक ret;

	mutex_init(&tps->irq_lock);
	tps->irq = irq;

	/* Mask all पूर्णांकerrupt sources */
	tps->irq_mask = TPS65217_INT_MASK;
	tps65217_set_bits(tps, TPS65217_REG_INT, TPS65217_INT_MASK,
			  TPS65217_INT_MASK, TPS65217_PROTECT_NONE);

	tps->irq_करोमुख्य = irq_करोमुख्य_add_linear(tps->dev->of_node,
		TPS65217_NUM_IRQ, &tps65217_irq_करोमुख्य_ops, tps);
	अगर (!tps->irq_करोमुख्य) अणु
		dev_err(tps->dev, "Could not create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(tps->dev, irq, शून्य,
					tps65217_irq_thपढ़ो, IRQF_ONESHOT,
					"tps65217-irq", tps);
	अगर (ret) अणु
		dev_err(tps->dev, "Failed to request IRQ %d: %d\n",
			irq, ret);
		वापस ret;
	पूर्ण

	enable_irq_wake(irq);

	वापस 0;
पूर्ण

/**
 * tps65217_reg_पढ़ो: Read a single tps65217 रेजिस्टर.
 *
 * @tps: Device to पढ़ो from.
 * @reg: Register to पढ़ो.
 * @val: Contians the value
 */
पूर्णांक tps65217_reg_पढ़ो(काष्ठा tps65217 *tps, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक *val)
अणु
	वापस regmap_पढ़ो(tps->regmap, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(tps65217_reg_पढ़ो);

/**
 * tps65217_reg_ग_लिखो: Write a single tps65217 रेजिस्टर.
 *
 * @tps: Device to ग_लिखो to.
 * @reg: Register to ग_लिखो to.
 * @val: Value to ग_लिखो.
 * @level: Password रक्षित level
 */
पूर्णांक tps65217_reg_ग_लिखो(काष्ठा tps65217 *tps, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक xor_reg_val;

	चयन (level) अणु
	हाल TPS65217_PROTECT_NONE:
		वापस regmap_ग_लिखो(tps->regmap, reg, val);
	हाल TPS65217_PROTECT_L1:
		xor_reg_val = reg ^ TPS65217_PASSWORD_REGS_UNLOCK;
		ret = regmap_ग_लिखो(tps->regmap, TPS65217_REG_PASSWORD,
							xor_reg_val);
		अगर (ret < 0)
			वापस ret;

		वापस regmap_ग_लिखो(tps->regmap, reg, val);
	हाल TPS65217_PROTECT_L2:
		xor_reg_val = reg ^ TPS65217_PASSWORD_REGS_UNLOCK;
		ret = regmap_ग_लिखो(tps->regmap, TPS65217_REG_PASSWORD,
							xor_reg_val);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_ग_लिखो(tps->regmap, reg, val);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_ग_लिखो(tps->regmap, TPS65217_REG_PASSWORD,
							xor_reg_val);
		अगर (ret < 0)
			वापस ret;
		वापस regmap_ग_लिखो(tps->regmap, reg, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tps65217_reg_ग_लिखो);

/**
 * tps65217_update_bits: Modअगरy bits w.r.t mask, val and level.
 *
 * @tps: Device to ग_लिखो to.
 * @reg: Register to पढ़ो-ग_लिखो to.
 * @mask: Mask.
 * @val: Value to ग_लिखो.
 * @level: Password रक्षित level
 */
अटल पूर्णांक tps65217_update_bits(काष्ठा tps65217 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = tps65217_reg_पढ़ो(tps, reg, &data);
	अगर (ret) अणु
		dev_err(tps->dev, "Read from reg 0x%x failed\n", reg);
		वापस ret;
	पूर्ण

	data &= ~mask;
	data |= val & mask;

	ret = tps65217_reg_ग_लिखो(tps, reg, data, level);
	अगर (ret)
		dev_err(tps->dev, "Write for reg 0x%x failed\n", reg);

	वापस ret;
पूर्ण

पूर्णांक tps65217_set_bits(काष्ठा tps65217 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक level)
अणु
	वापस tps65217_update_bits(tps, reg, mask, val, level);
पूर्ण
EXPORT_SYMBOL_GPL(tps65217_set_bits);

पूर्णांक tps65217_clear_bits(काष्ठा tps65217 *tps, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक level)
अणु
	वापस tps65217_update_bits(tps, reg, mask, 0, level);
पूर्ण
EXPORT_SYMBOL_GPL(tps65217_clear_bits);

अटल bool tps65217_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TPS65217_REG_INT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tps65217_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = TPS65217_REG_MAX,
	.अस्थिर_reg = tps65217_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tps65217_of_match[] = अणु
	अणु .compatible = "ti,tps65217"पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65217_of_match);

अटल पूर्णांक tps65217_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा tps65217 *tps;
	अचिन्हित पूर्णांक version;
	bool status_off = false;
	पूर्णांक ret;

	status_off = of_property_पढ़ो_bool(client->dev.of_node,
					   "ti,pmic-shutdown-controller");

	tps = devm_kzalloc(&client->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;

	tps->regmap = devm_regmap_init_i2c(client, &tps65217_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		ret = PTR_ERR(tps->regmap);
		dev_err(tps->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (client->irq) अणु
		tps65217_irq_init(tps, client->irq);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		/* Don't tell children about IRQ resources which won't fire */
		क्रम (i = 0; i < ARRAY_SIZE(tps65217s); i++)
			tps65217s[i].num_resources = 0;
	पूर्ण

	ret = devm_mfd_add_devices(tps->dev, -1, tps65217s,
				   ARRAY_SIZE(tps65217s), शून्य, 0,
				   tps->irq_करोमुख्य);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "mfd_add_devices failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = tps65217_reg_पढ़ो(tps, TPS65217_REG_CHIPID, &version);
	अगर (ret < 0) अणु
		dev_err(tps->dev, "Failed to read revision register: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* Set the PMIC to shutकरोwn on PWR_EN toggle */
	अगर (status_off) अणु
		ret = tps65217_set_bits(tps, TPS65217_REG_STATUS,
				TPS65217_STATUS_OFF, TPS65217_STATUS_OFF,
				TPS65217_PROTECT_NONE);
		अगर (ret)
			dev_warn(tps->dev, "unable to set the status OFF\n");
	पूर्ण

	dev_info(tps->dev, "TPS65217 ID %#x version 1.%d\n",
			(version & TPS65217_CHIPID_CHIP_MASK) >> 4,
			version & TPS65217_CHIPID_REV_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक tps65217_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps65217 *tps = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक virq;
	पूर्णांक i;

	क्रम (i = 0; i < TPS65217_NUM_IRQ; i++) अणु
		virq = irq_find_mapping(tps->irq_करोमुख्य, i);
		अगर (virq)
			irq_dispose_mapping(virq);
	पूर्ण

	irq_करोमुख्य_हटाओ(tps->irq_करोमुख्य);
	tps->irq_करोमुख्य = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65217_id_table[] = अणु
	अणु"tps65217", TPS65217पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps65217_id_table);

अटल काष्ठा i2c_driver tps65217_driver = अणु
	.driver		= अणु
		.name	= "tps65217",
		.of_match_table = tps65217_of_match,
	पूर्ण,
	.id_table	= tps65217_id_table,
	.probe_new	= tps65217_probe,
	.हटाओ		= tps65217_हटाओ,
पूर्ण;

अटल पूर्णांक __init tps65217_init(व्योम)
अणु
	वापस i2c_add_driver(&tps65217_driver);
पूर्ण
subsys_initcall(tps65217_init);

अटल व्योम __निकास tps65217_निकास(व्योम)
अणु
	i2c_del_driver(&tps65217_driver);
पूर्ण
module_निकास(tps65217_निकास);

MODULE_AUTHOR("AnilKumar Ch <anilkumar@ti.com>");
MODULE_DESCRIPTION("TPS65217 chip family multi-function driver");
MODULE_LICENSE("GPL v2");
