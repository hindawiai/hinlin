<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BCM63xx Power Doमुख्य Controller Driver
 *
 * Copyright (C) 2020 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 */

#समावेश <dt-bindings/soc/bcm6318-pm.h>
#समावेश <dt-bindings/soc/bcm6328-pm.h>
#समावेश <dt-bindings/soc/bcm6362-pm.h>
#समावेश <dt-bindings/soc/bcm63268-pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

काष्ठा bcm63xx_घातer_dev अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा bcm63xx_घातer *घातer;
	uपूर्णांक32_t mask;
पूर्ण;

काष्ठा bcm63xx_घातer अणु
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा bcm63xx_घातer_dev *dev;
	काष्ठा genpd_onecell_data genpd_data;
	काष्ठा generic_pm_करोमुख्य **genpd;
पूर्ण;

काष्ठा bcm63xx_घातer_data अणु
	स्थिर अक्षर * स्थिर name;
	uपूर्णांक8_t bit;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल पूर्णांक bcm63xx_घातer_get_state(काष्ठा bcm63xx_घातer_dev *pmd, bool *is_on)
अणु
	काष्ठा bcm63xx_घातer *घातer = pmd->घातer;

	अगर (!pmd->mask) अणु
		*is_on = false;
		वापस -EINVAL;
	पूर्ण

	*is_on = !(__raw_पढ़ोl(घातer->base) & pmd->mask);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_घातer_set_state(काष्ठा bcm63xx_घातer_dev *pmd, bool on)
अणु
	काष्ठा bcm63xx_घातer *घातer = pmd->घातer;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t val;

	अगर (!pmd->mask)
		वापस -EINVAL;

	spin_lock_irqsave(&घातer->lock, flags);
	val = __raw_पढ़ोl(घातer->base);
	अगर (on)
		val &= ~pmd->mask;
	अन्यथा
		val |= pmd->mask;
	__raw_ग_लिखोl(val, घातer->base);
	spin_unlock_irqrestore(&घातer->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा bcm63xx_घातer_dev *pmd = container_of(genpd,
		काष्ठा bcm63xx_घातer_dev, genpd);

	वापस bcm63xx_घातer_set_state(pmd, true);
पूर्ण

अटल पूर्णांक bcm63xx_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा bcm63xx_घातer_dev *pmd = container_of(genpd,
		काष्ठा bcm63xx_घातer_dev, genpd);

	वापस bcm63xx_घातer_set_state(pmd, false);
पूर्ण

अटल पूर्णांक bcm63xx_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	स्थिर काष्ठा bcm63xx_घातer_data *entry, *table;
	काष्ठा bcm63xx_घातer *घातer;
	अचिन्हित पूर्णांक nकरोm;
	uपूर्णांक8_t max_bit = 0;
	पूर्णांक ret;

	घातer = devm_kzalloc(dev, माप(*घातer), GFP_KERNEL);
	अगर (!घातer)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	घातer->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(घातer->base))
		वापस PTR_ERR(घातer->base);

	table = of_device_get_match_data(dev);
	अगर (!table)
		वापस -EINVAL;

	घातer->genpd_data.num_करोमुख्यs = 0;
	nकरोm = 0;
	क्रम (entry = table; entry->name; entry++) अणु
		max_bit = max(max_bit, entry->bit);
		nकरोm++;
	पूर्ण

	अगर (!nकरोm)
		वापस -ENODEV;

	घातer->genpd_data.num_करोमुख्यs = max_bit + 1;

	घातer->dev = devm_kसुस्मृति(dev, घातer->genpd_data.num_करोमुख्यs,
				  माप(काष्ठा bcm63xx_घातer_dev),
				  GFP_KERNEL);
	अगर (!घातer->dev)
		वापस -ENOMEM;

	घातer->genpd = devm_kसुस्मृति(dev, घातer->genpd_data.num_करोमुख्यs,
				    माप(काष्ठा generic_pm_करोमुख्य *),
				    GFP_KERNEL);
	अगर (!घातer->genpd)
		वापस -ENOMEM;

	घातer->genpd_data.करोमुख्यs = घातer->genpd;

	nकरोm = 0;
	क्रम (entry = table; entry->name; entry++) अणु
		काष्ठा bcm63xx_घातer_dev *pmd = &घातer->dev[nकरोm];
		bool is_on;

		pmd->घातer = घातer;
		pmd->mask = BIT(entry->bit);
		pmd->genpd.name = entry->name;
		pmd->genpd.flags = entry->flags;

		ret = bcm63xx_घातer_get_state(pmd, &is_on);
		अगर (ret)
			dev_warn(dev, "unable to get current state for %s\n",
				 pmd->genpd.name);

		pmd->genpd.घातer_on = bcm63xx_घातer_on;
		pmd->genpd.घातer_off = bcm63xx_घातer_off;

		pm_genpd_init(&pmd->genpd, शून्य, !is_on);
		घातer->genpd[entry->bit] = &pmd->genpd;

		nकरोm++;
	पूर्ण

	spin_lock_init(&घातer->lock);

	ret = of_genpd_add_provider_onecell(np, &घातer->genpd_data);
	अगर (ret) अणु
		dev_err(dev, "failed to register genpd driver: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "registered %u power domains\n", nकरोm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bcm63xx_घातer_data bcm6318_घातer_करोमुख्यs[] = अणु
	अणु
		.name = "pcie",
		.bit = BCM6318_POWER_DOMAIN_PCIE,
	पूर्ण, अणु
		.name = "usb",
		.bit = BCM6318_POWER_DOMAIN_USB,
	पूर्ण, अणु
		.name = "ephy0",
		.bit = BCM6318_POWER_DOMAIN_EPHY0,
	पूर्ण, अणु
		.name = "ephy1",
		.bit = BCM6318_POWER_DOMAIN_EPHY1,
	पूर्ण, अणु
		.name = "ephy2",
		.bit = BCM6318_POWER_DOMAIN_EPHY2,
	पूर्ण, अणु
		.name = "ephy3",
		.bit = BCM6318_POWER_DOMAIN_EPHY3,
	पूर्ण, अणु
		.name = "ldo2p5",
		.bit = BCM6318_POWER_DOMAIN_LDO2P5,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "ldo2p9",
		.bit = BCM6318_POWER_DOMAIN_LDO2P9,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "sw1p0",
		.bit = BCM6318_POWER_DOMAIN_SW1P0,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "pad",
		.bit = BCM6318_POWER_DOMAIN_PAD,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_घातer_data bcm6328_घातer_करोमुख्यs[] = अणु
	अणु
		.name = "adsl2-mips",
		.bit = BCM6328_POWER_DOMAIN_ADSL2_MIPS,
	पूर्ण, अणु
		.name = "adsl2-phy",
		.bit = BCM6328_POWER_DOMAIN_ADSL2_PHY,
	पूर्ण, अणु
		.name = "adsl2-afe",
		.bit = BCM6328_POWER_DOMAIN_ADSL2_AFE,
	पूर्ण, अणु
		.name = "sar",
		.bit = BCM6328_POWER_DOMAIN_SAR,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM6328_POWER_DOMAIN_PCM,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM6328_POWER_DOMAIN_USBD,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM6328_POWER_DOMAIN_USBH,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM6328_POWER_DOMAIN_PCIE,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM6328_POWER_DOMAIN_ROBOSW,
	पूर्ण, अणु
		.name = "ephy",
		.bit = BCM6328_POWER_DOMAIN_EPHY,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_घातer_data bcm6362_घातer_करोमुख्यs[] = अणु
	अणु
		.name = "sar",
		.bit = BCM6362_POWER_DOMAIN_SAR,
	पूर्ण, अणु
		.name = "ipsec",
		.bit = BCM6362_POWER_DOMAIN_IPSEC,
	पूर्ण, अणु
		.name = "mips",
		.bit = BCM6362_POWER_DOMAIN_MIPS,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "dect",
		.bit = BCM6362_POWER_DOMAIN_DECT,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM6362_POWER_DOMAIN_USBH,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM6362_POWER_DOMAIN_USBD,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM6362_POWER_DOMAIN_ROBOSW,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM6362_POWER_DOMAIN_PCM,
	पूर्ण, अणु
		.name = "periph",
		.bit = BCM6362_POWER_DOMAIN_PERIPH,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "adsl-phy",
		.bit = BCM6362_POWER_DOMAIN_ADSL_PHY,
	पूर्ण, अणु
		.name = "gmii-pads",
		.bit = BCM6362_POWER_DOMAIN_GMII_PADS,
	पूर्ण, अणु
		.name = "fap",
		.bit = BCM6362_POWER_DOMAIN_FAP,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM6362_POWER_DOMAIN_PCIE,
	पूर्ण, अणु
		.name = "wlan-pads",
		.bit = BCM6362_POWER_DOMAIN_WLAN_PADS,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_घातer_data bcm63268_घातer_करोमुख्यs[] = अणु
	अणु
		.name = "sar",
		.bit = BCM63268_POWER_DOMAIN_SAR,
	पूर्ण, अणु
		.name = "ipsec",
		.bit = BCM63268_POWER_DOMAIN_IPSEC,
	पूर्ण, अणु
		.name = "mips",
		.bit = BCM63268_POWER_DOMAIN_MIPS,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "dect",
		.bit = BCM63268_POWER_DOMAIN_DECT,
	पूर्ण, अणु
		.name = "usbh",
		.bit = BCM63268_POWER_DOMAIN_USBH,
	पूर्ण, अणु
		.name = "usbd",
		.bit = BCM63268_POWER_DOMAIN_USBD,
	पूर्ण, अणु
		.name = "robosw",
		.bit = BCM63268_POWER_DOMAIN_ROBOSW,
	पूर्ण, अणु
		.name = "pcm",
		.bit = BCM63268_POWER_DOMAIN_PCM,
	पूर्ण, अणु
		.name = "periph",
		.bit = BCM63268_POWER_DOMAIN_PERIPH,
		.flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण, अणु
		.name = "vdsl-phy",
		.bit = BCM63268_POWER_DOMAIN_VDSL_PHY,
	पूर्ण, अणु
		.name = "vdsl-mips",
		.bit = BCM63268_POWER_DOMAIN_VDSL_MIPS,
	पूर्ण, अणु
		.name = "fap",
		.bit = BCM63268_POWER_DOMAIN_FAP,
	पूर्ण, अणु
		.name = "pcie",
		.bit = BCM63268_POWER_DOMAIN_PCIE,
	पूर्ण, अणु
		.name = "wlan-pads",
		.bit = BCM63268_POWER_DOMAIN_WLAN_PADS,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm63xx_घातer_of_match[] = अणु
	अणु
		.compatible = "brcm,bcm6318-power-controller",
		.data = &bcm6318_घातer_करोमुख्यs,
	पूर्ण, अणु
		.compatible = "brcm,bcm6328-power-controller",
		.data = &bcm6328_घातer_करोमुख्यs,
	पूर्ण, अणु
		.compatible = "brcm,bcm6362-power-controller",
		.data = &bcm6362_घातer_करोमुख्यs,
	पूर्ण, अणु
		.compatible = "brcm,bcm63268-power-controller",
		.data = &bcm63268_घातer_करोमुख्यs,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm63xx_घातer_driver = अणु
	.driver = अणु
		.name = "bcm63xx-power-controller",
		.of_match_table = bcm63xx_घातer_of_match,
	पूर्ण,
	.probe  = bcm63xx_घातer_probe,
पूर्ण;
builtin_platक्रमm_driver(bcm63xx_घातer_driver);
