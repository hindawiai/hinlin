<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device driver क्रम MFD hi655x PMIC
 *
 * Copyright (c) 2016 Hisilicon.
 *
 * Authors:
 * Chen Feng <puck.chen@hisilicon.com>
 * Fei  Wang <w.f@huawei.com>
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/hi655x-pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा regmap_irq hi655x_irqs[] = अणु
	अणु .reg_offset = 0, .mask = OTMP_D1R_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = VSYS_2P5_R_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = VSYS_UV_D3R_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = VSYS_6P0_D200UR_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = PWRON_D4SR_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = PWRON_D20F_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = PWRON_D20R_INT_MASK पूर्ण,
	अणु .reg_offset = 0, .mask = RESERVE_INT_MASK पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip hi655x_irq_chip = अणु
	.name = "hi655x-pmic",
	.irqs = hi655x_irqs,
	.num_regs = 1,
	.num_irqs = ARRAY_SIZE(hi655x_irqs),
	.status_base = HI655X_IRQ_STAT_BASE,
	.ack_base = HI655X_IRQ_STAT_BASE,
	.mask_base = HI655X_IRQ_MASK_BASE,
पूर्ण;

अटल काष्ठा regmap_config hi655x_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = HI655X_STRIDE,
	.val_bits = 8,
	.max_रेजिस्टर = HI655X_BUS_ADDR(0x400) - HI655X_STRIDE,
पूर्ण;

अटल स्थिर काष्ठा resource pwrkey_resources[] = अणु
	अणु
		.name	= "down",
		.start	= PWRON_D20R_INT,
		.end	= PWRON_D20R_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण, अणु
		.name	= "up",
		.start	= PWRON_D20F_INT,
		.end	= PWRON_D20F_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण, अणु
		.name	= "hold 4s",
		.start	= PWRON_D4SR_INT,
		.end	= PWRON_D4SR_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell hi655x_pmic_devs[] = अणु
	अणु
		.name		= "hi65xx-powerkey",
		.num_resources	= ARRAY_SIZE(pwrkey_resources),
		.resources	= &pwrkey_resources[0],
	पूर्ण,
	अणु	.name		= "hi655x-regulator",	पूर्ण,
	अणु	.name		= "hi655x-clk",		पूर्ण,
पूर्ण;

अटल व्योम hi655x_local_irq_clear(काष्ठा regmap *map)
अणु
	पूर्णांक i;

	regmap_ग_लिखो(map, HI655X_ANA_IRQM_BASE, HI655X_IRQ_CLR);
	क्रम (i = 0; i < HI655X_IRQ_ARRAY; i++) अणु
		regmap_ग_लिखो(map, HI655X_IRQ_STAT_BASE + i * HI655X_STRIDE,
			     HI655X_IRQ_CLR);
	पूर्ण
पूर्ण

अटल पूर्णांक hi655x_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा hi655x_pmic *pmic;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	व्योम __iomem *base;

	pmic = devm_kzalloc(dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;
	pmic->dev = dev;

	pmic->res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, pmic->res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	pmic->regmap = devm_regmap_init_mmio_clk(dev, शून्य, base,
						 &hi655x_regmap_config);
	अगर (IS_ERR(pmic->regmap))
		वापस PTR_ERR(pmic->regmap);

	regmap_पढ़ो(pmic->regmap, HI655X_BUS_ADDR(HI655X_VER_REG), &pmic->ver);
	अगर ((pmic->ver < PMU_VER_START) || (pmic->ver > PMU_VER_END)) अणु
		dev_warn(dev, "PMU version %d unsupported\n", pmic->ver);
		वापस -EINVAL;
	पूर्ण

	hi655x_local_irq_clear(pmic->regmap);

	pmic->gpio = of_get_named_gpio(np, "pmic-gpios", 0);
	अगर (!gpio_is_valid(pmic->gpio)) अणु
		dev_err(dev, "Failed to get the pmic-gpios\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_gpio_request_one(dev, pmic->gpio, GPIOF_IN,
				    "hi655x_pmic_irq");
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request gpio %d  ret = %d\n",
			pmic->gpio, ret);
		वापस ret;
	पूर्ण

	ret = regmap_add_irq_chip(pmic->regmap, gpio_to_irq(pmic->gpio),
				  IRQF_TRIGGER_LOW | IRQF_NO_SUSPEND, 0,
				  &hi655x_irq_chip, &pmic->irq_data);
	अगर (ret) अणु
		dev_err(dev, "Failed to obtain 'hi655x_pmic_irq' %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmic);

	ret = mfd_add_devices(dev, PLATFORM_DEVID_AUTO, hi655x_pmic_devs,
			      ARRAY_SIZE(hi655x_pmic_devs), शून्य, 0,
			      regmap_irq_get_करोमुख्य(pmic->irq_data));
	अगर (ret) अणु
		dev_err(dev, "Failed to register device %d\n", ret);
		regmap_del_irq_chip(gpio_to_irq(pmic->gpio), pmic->irq_data);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hi655x_pmic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi655x_pmic *pmic = platक्रमm_get_drvdata(pdev);

	regmap_del_irq_chip(gpio_to_irq(pmic->gpio), pmic->irq_data);
	mfd_हटाओ_devices(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hi655x_pmic_match[] = अणु
	अणु .compatible = "hisilicon,hi655x-pmic", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi655x_pmic_match);

अटल काष्ठा platक्रमm_driver hi655x_pmic_driver = अणु
	.driver	= अणु
		.name =	"hi655x-pmic",
		.of_match_table = of_match_ptr(hi655x_pmic_match),
	पूर्ण,
	.probe  = hi655x_pmic_probe,
	.हटाओ = hi655x_pmic_हटाओ,
पूर्ण;
module_platक्रमm_driver(hi655x_pmic_driver);

MODULE_AUTHOR("Chen Feng <puck.chen@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon hi655x PMIC driver");
MODULE_LICENSE("GPL v2");
