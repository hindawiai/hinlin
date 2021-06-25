<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Flora Fu, MediaTek
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mt6323/core.h>
#समावेश <linux/mfd/mt6358/core.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/mfd/mt6323/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6358/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6397/रेजिस्टरs.h>

#घोषणा MT6323_RTC_BASE		0x8000
#घोषणा MT6323_RTC_SIZE		0x40

#घोषणा MT6358_RTC_BASE		0x0588
#घोषणा MT6358_RTC_SIZE		0x3c

#घोषणा MT6397_RTC_BASE		0xe000
#घोषणा MT6397_RTC_SIZE		0x3e

#घोषणा MT6323_PWRC_BASE	0x8000
#घोषणा MT6323_PWRC_SIZE	0x40

अटल स्थिर काष्ठा resource mt6323_rtc_resources[] = अणु
	DEFINE_RES_MEM(MT6323_RTC_BASE, MT6323_RTC_SIZE),
	DEFINE_RES_IRQ(MT6323_IRQ_STATUS_RTC),
पूर्ण;

अटल स्थिर काष्ठा resource mt6358_rtc_resources[] = अणु
	DEFINE_RES_MEM(MT6358_RTC_BASE, MT6358_RTC_SIZE),
	DEFINE_RES_IRQ(MT6358_IRQ_RTC),
पूर्ण;

अटल स्थिर काष्ठा resource mt6397_rtc_resources[] = अणु
	DEFINE_RES_MEM(MT6397_RTC_BASE, MT6397_RTC_SIZE),
	DEFINE_RES_IRQ(MT6397_IRQ_RTC),
पूर्ण;

अटल स्थिर काष्ठा resource mt6323_keys_resources[] = अणु
	DEFINE_RES_IRQ(MT6323_IRQ_STATUS_PWRKEY),
	DEFINE_RES_IRQ(MT6323_IRQ_STATUS_FCHRKEY),
पूर्ण;

अटल स्थिर काष्ठा resource mt6397_keys_resources[] = अणु
	DEFINE_RES_IRQ(MT6397_IRQ_PWRKEY),
	DEFINE_RES_IRQ(MT6397_IRQ_HOMEKEY),
पूर्ण;

अटल स्थिर काष्ठा resource mt6323_pwrc_resources[] = अणु
	DEFINE_RES_MEM(MT6323_PWRC_BASE, MT6323_PWRC_SIZE),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell mt6323_devs[] = अणु
	अणु
		.name = "mt6323-rtc",
		.num_resources = ARRAY_SIZE(mt6323_rtc_resources),
		.resources = mt6323_rtc_resources,
		.of_compatible = "mediatek,mt6323-rtc",
	पूर्ण, अणु
		.name = "mt6323-regulator",
		.of_compatible = "mediatek,mt6323-regulator"
	पूर्ण, अणु
		.name = "mt6323-led",
		.of_compatible = "mediatek,mt6323-led"
	पूर्ण, अणु
		.name = "mtk-pmic-keys",
		.num_resources = ARRAY_SIZE(mt6323_keys_resources),
		.resources = mt6323_keys_resources,
		.of_compatible = "mediatek,mt6323-keys"
	पूर्ण, अणु
		.name = "mt6323-pwrc",
		.num_resources = ARRAY_SIZE(mt6323_pwrc_resources),
		.resources = mt6323_pwrc_resources,
		.of_compatible = "mediatek,mt6323-pwrc"
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell mt6358_devs[] = अणु
	अणु
		.name = "mt6358-regulator",
		.of_compatible = "mediatek,mt6358-regulator"
	पूर्ण, अणु
		.name = "mt6358-rtc",
		.num_resources = ARRAY_SIZE(mt6358_rtc_resources),
		.resources = mt6358_rtc_resources,
		.of_compatible = "mediatek,mt6358-rtc",
	पूर्ण, अणु
		.name = "mt6358-sound",
		.of_compatible = "mediatek,mt6358-sound"
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell mt6397_devs[] = अणु
	अणु
		.name = "mt6397-rtc",
		.num_resources = ARRAY_SIZE(mt6397_rtc_resources),
		.resources = mt6397_rtc_resources,
		.of_compatible = "mediatek,mt6397-rtc",
	पूर्ण, अणु
		.name = "mt6397-regulator",
		.of_compatible = "mediatek,mt6397-regulator",
	पूर्ण, अणु
		.name = "mt6397-codec",
		.of_compatible = "mediatek,mt6397-codec",
	पूर्ण, अणु
		.name = "mt6397-clk",
		.of_compatible = "mediatek,mt6397-clk",
	पूर्ण, अणु
		.name = "mt6397-pinctrl",
		.of_compatible = "mediatek,mt6397-pinctrl",
	पूर्ण, अणु
		.name = "mtk-pmic-keys",
		.num_resources = ARRAY_SIZE(mt6397_keys_resources),
		.resources = mt6397_keys_resources,
		.of_compatible = "mediatek,mt6397-keys"
	पूर्ण
पूर्ण;

काष्ठा chip_data अणु
	u32 cid_addr;
	u32 cid_shअगरt;
	स्थिर काष्ठा mfd_cell *cells;
	पूर्णांक cell_size;
	पूर्णांक (*irq_init)(काष्ठा mt6397_chip *chip);
पूर्ण;

अटल स्थिर काष्ठा chip_data mt6323_core = अणु
	.cid_addr = MT6323_CID,
	.cid_shअगरt = 0,
	.cells = mt6323_devs,
	.cell_size = ARRAY_SIZE(mt6323_devs),
	.irq_init = mt6397_irq_init,
पूर्ण;

अटल स्थिर काष्ठा chip_data mt6358_core = अणु
	.cid_addr = MT6358_SWCID,
	.cid_shअगरt = 8,
	.cells = mt6358_devs,
	.cell_size = ARRAY_SIZE(mt6358_devs),
	.irq_init = mt6358_irq_init,
पूर्ण;

अटल स्थिर काष्ठा chip_data mt6397_core = अणु
	.cid_addr = MT6397_CID,
	.cid_shअगरt = 0,
	.cells = mt6397_devs,
	.cell_size = ARRAY_SIZE(mt6397_devs),
	.irq_init = mt6397_irq_init,
पूर्ण;

अटल पूर्णांक mt6397_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक id = 0;
	काष्ठा mt6397_chip *pmic;
	स्थिर काष्ठा chip_data *pmic_core;

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	pmic->dev = &pdev->dev;

	/*
	 * mt6397 MFD is child device of soc pmic wrapper.
	 * Regmap is set from its parent.
	 */
	pmic->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!pmic->regmap)
		वापस -ENODEV;

	pmic_core = of_device_get_match_data(&pdev->dev);
	अगर (!pmic_core)
		वापस -ENODEV;

	ret = regmap_पढ़ो(pmic->regmap, pmic_core->cid_addr, &id);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to read chip id: %d\n", ret);
		वापस ret;
	पूर्ण

	pmic->chip_id = (id >> pmic_core->cid_shअगरt) & 0xff;

	platक्रमm_set_drvdata(pdev, pmic);

	pmic->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pmic->irq <= 0)
		वापस pmic->irq;

	ret = pmic_core->irq_init(pmic);
	अगर (ret)
		वापस ret;

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   pmic_core->cells, pmic_core->cell_size,
				   शून्य, 0, pmic->irq_करोमुख्य);
	अगर (ret) अणु
		irq_करोमुख्य_हटाओ(pmic->irq_करोमुख्य);
		dev_err(&pdev->dev, "failed to add child devices: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt6397_of_match[] = अणु
	अणु
		.compatible = "mediatek,mt6323",
		.data = &mt6323_core,
	पूर्ण, अणु
		.compatible = "mediatek,mt6358",
		.data = &mt6358_core,
	पूर्ण, अणु
		.compatible = "mediatek,mt6397",
		.data = &mt6397_core,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6397_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id mt6397_id[] = अणु
	अणु "mt6397", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mt6397_id);

अटल काष्ठा platक्रमm_driver mt6397_driver = अणु
	.probe = mt6397_probe,
	.driver = अणु
		.name = "mt6397",
		.of_match_table = mt6397_of_match,
	पूर्ण,
	.id_table = mt6397_id,
पूर्ण;

module_platक्रमm_driver(mt6397_driver);

MODULE_AUTHOR("Flora Fu, MediaTek");
MODULE_DESCRIPTION("Driver for MediaTek MT6397 PMIC");
MODULE_LICENSE("GPL");
