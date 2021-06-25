<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD core driver क्रम the Richtek RT5033.
 *
 * RT5033 comprises multiple sub-devices switcing अक्षरger, fuel gauge,
 * flash LED, current source, LDO and BUCK regulators.
 *
 * Copyright (C) 2014 Samsung Electronics, Co., Ltd.
 * Author: Beomho Seo <beomho.seo@samsung.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rt5033.h>
#समावेश <linux/mfd/rt5033-निजी.h>

अटल स्थिर काष्ठा regmap_irq rt5033_irqs[] = अणु
	अणु .mask = RT5033_PMIC_IRQ_BUCKOCP, पूर्ण,
	अणु .mask = RT5033_PMIC_IRQ_BUCKLV, पूर्ण,
	अणु .mask = RT5033_PMIC_IRQ_SAFELDOLV, पूर्ण,
	अणु .mask = RT5033_PMIC_IRQ_LDOLV, पूर्ण,
	अणु .mask = RT5033_PMIC_IRQ_OT, पूर्ण,
	अणु .mask = RT5033_PMIC_IRQ_VDDA_UV, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip rt5033_irq_chip = अणु
	.name		= "rt5033",
	.status_base	= RT5033_REG_PMIC_IRQ_STAT,
	.mask_base	= RT5033_REG_PMIC_IRQ_CTRL,
	.mask_invert	= true,
	.num_regs	= 1,
	.irqs		= rt5033_irqs,
	.num_irqs	= ARRAY_SIZE(rt5033_irqs),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rt5033_devs[] = अणु
	अणु .name = "rt5033-regulator", पूर्ण,
	अणु
		.name = "rt5033-charger",
		.of_compatible = "richtek,rt5033-charger",
	पूर्ण, अणु
		.name = "rt5033-battery",
		.of_compatible = "richtek,rt5033-battery",
	पूर्ण, अणु
		.name = "rt5033-led",
		.of_compatible = "richtek,rt5033-led",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt5033_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= RT5033_REG_END,
पूर्ण;

अटल पूर्णांक rt5033_i2c_probe(काष्ठा i2c_client *i2c,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt5033_dev *rt5033;
	अचिन्हित पूर्णांक dev_id;
	पूर्णांक ret;

	rt5033 = devm_kzalloc(&i2c->dev, माप(*rt5033), GFP_KERNEL);
	अगर (!rt5033)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, rt5033);
	rt5033->dev = &i2c->dev;
	rt5033->irq = i2c->irq;
	rt5033->wakeup = true;

	rt5033->regmap = devm_regmap_init_i2c(i2c, &rt5033_regmap_config);
	अगर (IS_ERR(rt5033->regmap)) अणु
		dev_err(&i2c->dev, "Failed to allocate register map.\n");
		वापस PTR_ERR(rt5033->regmap);
	पूर्ण

	ret = regmap_पढ़ो(rt5033->regmap, RT5033_REG_DEVICE_ID, &dev_id);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Device not found\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(&i2c->dev, "Device found Device ID: %04x\n", dev_id);

	ret = regmap_add_irq_chip(rt5033->regmap, rt5033->irq,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			0, &rt5033_irq_chip, &rt5033->irq_data);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to request IRQ %d: %d\n",
							rt5033->irq, ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(rt5033->dev, -1, rt5033_devs,
				   ARRAY_SIZE(rt5033_devs), शून्य, 0,
				   regmap_irq_get_करोमुख्य(rt5033->irq_data));
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to add RT5033 child devices.\n");
		वापस ret;
	पूर्ण

	device_init_wakeup(rt5033->dev, rt5033->wakeup);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rt5033_i2c_id[] = अणु
	अणु "rt5033", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt5033_i2c_id);

अटल स्थिर काष्ठा of_device_id rt5033_dt_match[] = अणु
	अणु .compatible = "richtek,rt5033", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5033_dt_match);

अटल काष्ठा i2c_driver rt5033_driver = अणु
	.driver = अणु
		.name = "rt5033",
		.of_match_table = rt5033_dt_match,
	पूर्ण,
	.probe = rt5033_i2c_probe,
	.id_table = rt5033_i2c_id,
पूर्ण;
module_i2c_driver(rt5033_driver);

MODULE_DESCRIPTION("Richtek RT5033 multi-function core driver");
MODULE_AUTHOR("Beomho Seo <beomho.seo@samsung.com>");
MODULE_LICENSE("GPL");
