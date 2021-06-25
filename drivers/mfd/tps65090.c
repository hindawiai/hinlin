<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम TI TPS65090 PMIC family
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Venu Byravarasu <vbyravarasu@nvidia.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps65090.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/err.h>

#घोषणा NUM_INT_REG 2

#घोषणा TPS65090_INT1_MASK_VAC_STATUS_CHANGE		1
#घोषणा TPS65090_INT1_MASK_VSYS_STATUS_CHANGE		2
#घोषणा TPS65090_INT1_MASK_BAT_STATUS_CHANGE		3
#घोषणा TPS65090_INT1_MASK_CHARGING_STATUS_CHANGE	4
#घोषणा TPS65090_INT1_MASK_CHARGING_COMPLETE		5
#घोषणा TPS65090_INT1_MASK_OVERLOAD_DCDC1		6
#घोषणा TPS65090_INT1_MASK_OVERLOAD_DCDC2		7
#घोषणा TPS65090_INT2_MASK_OVERLOAD_DCDC3		0
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET1		1
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET2		2
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET3		3
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET4		4
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET5		5
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET6		6
#घोषणा TPS65090_INT2_MASK_OVERLOAD_FET7		7

अटल स्थिर काष्ठा resource अक्षरger_resources[] = अणु
	अणु
		.start  = TPS65090_IRQ_VAC_STATUS_CHANGE,
		.end    = TPS65090_IRQ_VAC_STATUS_CHANGE,
		.flags  = IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

क्रमागत tps65090_cells अणु
	PMIC = 0,
	CHARGER = 1,
पूर्ण;

अटल काष्ठा mfd_cell tps65090s[] = अणु
	[PMIC] = अणु
		.name = "tps65090-pmic",
	पूर्ण,
	[CHARGER] = अणु
		.name = "tps65090-charger",
		.num_resources = ARRAY_SIZE(अक्षरger_resources),
		.resources = &अक्षरger_resources[0],
		.of_compatible = "ti,tps65090-charger",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq tps65090_irqs[] = अणु
	/* INT1 IRQs*/
	[TPS65090_IRQ_VAC_STATUS_CHANGE] = अणु
		.mask = TPS65090_INT1_MASK_VAC_STATUS_CHANGE,
	पूर्ण,
	[TPS65090_IRQ_VSYS_STATUS_CHANGE] = अणु
		.mask = TPS65090_INT1_MASK_VSYS_STATUS_CHANGE,
	पूर्ण,
	[TPS65090_IRQ_BAT_STATUS_CHANGE] = अणु
		.mask = TPS65090_INT1_MASK_BAT_STATUS_CHANGE,
	पूर्ण,
	[TPS65090_IRQ_CHARGING_STATUS_CHANGE] = अणु
		.mask = TPS65090_INT1_MASK_CHARGING_STATUS_CHANGE,
	पूर्ण,
	[TPS65090_IRQ_CHARGING_COMPLETE] = अणु
		.mask = TPS65090_INT1_MASK_CHARGING_COMPLETE,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_DCDC1] = अणु
		.mask = TPS65090_INT1_MASK_OVERLOAD_DCDC1,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_DCDC2] = अणु
		.mask = TPS65090_INT1_MASK_OVERLOAD_DCDC2,
	पूर्ण,
	/* INT2 IRQs*/
	[TPS65090_IRQ_OVERLOAD_DCDC3] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_DCDC3,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET1] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET1,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET2] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET2,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET3] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET3,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET4] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET4,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET5] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET5,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET6] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET6,
	पूर्ण,
	[TPS65090_IRQ_OVERLOAD_FET7] = अणु
		.reg_offset = 1,
		.mask = TPS65090_INT2_MASK_OVERLOAD_FET7,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip tps65090_irq_chip = अणु
	.name = "tps65090",
	.irqs = tps65090_irqs,
	.num_irqs = ARRAY_SIZE(tps65090_irqs),
	.num_regs = NUM_INT_REG,
	.status_base = TPS65090_REG_INTR_STS,
	.mask_base = TPS65090_REG_INTR_MASK,
	.mask_invert = true,
पूर्ण;

अटल bool is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Nearly all रेजिस्टरs have status bits mixed in, except a few */
	चयन (reg) अणु
	हाल TPS65090_REG_INTR_MASK:
	हाल TPS65090_REG_INTR_MASK2:
	हाल TPS65090_REG_CG_CTRL0:
	हाल TPS65090_REG_CG_CTRL1:
	हाल TPS65090_REG_CG_CTRL2:
	हाल TPS65090_REG_CG_CTRL3:
	हाल TPS65090_REG_CG_CTRL4:
	हाल TPS65090_REG_CG_CTRL5:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config tps65090_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = TPS65090_MAX_REG,
	.num_reg_शेषs_raw = TPS65090_NUM_REGS,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = is_अस्थिर_reg,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tps65090_of_match[] = अणु
	अणु .compatible = "ti,tps65090",पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक tps65090_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps65090_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक irq_base = 0;
	काष्ठा tps65090 *tps65090;
	पूर्णांक ret;

	अगर (!pdata && !client->dev.of_node) अणु
		dev_err(&client->dev,
			"tps65090 requires platform data or of_node\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata)
		irq_base = pdata->irq_base;

	tps65090 = devm_kzalloc(&client->dev, माप(*tps65090), GFP_KERNEL);
	अगर (!tps65090)
		वापस -ENOMEM;

	tps65090->dev = &client->dev;
	i2c_set_clientdata(client, tps65090);

	tps65090->rmap = devm_regmap_init_i2c(client, &tps65090_regmap_config);
	अगर (IS_ERR(tps65090->rmap)) अणु
		ret = PTR_ERR(tps65090->rmap);
		dev_err(&client->dev, "regmap_init failed with err: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (client->irq) अणु
		ret = regmap_add_irq_chip(tps65090->rmap, client->irq,
					  IRQF_ONESHOT | IRQF_TRIGGER_LOW, irq_base,
					  &tps65090_irq_chip, &tps65090->irq_data);
		अगर (ret) अणु
			dev_err(&client->dev,
				"IRQ init failed with err: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Don't tell children they have an IRQ that'll never fire */
		tps65090s[CHARGER].num_resources = 0;
	पूर्ण

	ret = mfd_add_devices(tps65090->dev, -1, tps65090s,
			      ARRAY_SIZE(tps65090s), शून्य,
			      0, regmap_irq_get_करोमुख्य(tps65090->irq_data));
	अगर (ret) अणु
		dev_err(&client->dev, "add mfd devices failed with err: %d\n",
			ret);
		जाओ err_irq_निकास;
	पूर्ण

	वापस 0;

err_irq_निकास:
	अगर (client->irq)
		regmap_del_irq_chip(client->irq, tps65090->irq_data);
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id tps65090_id_table[] = अणु
	अणु "tps65090", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver tps65090_driver = अणु
	.driver	= अणु
		.name	= "tps65090",
		.suppress_bind_attrs = true,
		.of_match_table = of_match_ptr(tps65090_of_match),
	पूर्ण,
	.probe		= tps65090_i2c_probe,
	.id_table	= tps65090_id_table,
पूर्ण;

अटल पूर्णांक __init tps65090_init(व्योम)
अणु
	वापस i2c_add_driver(&tps65090_driver);
पूर्ण
subsys_initcall(tps65090_init);
