<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *         Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश "mt7615.h"

पूर्णांक mt7622_wmac_init(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा device_node *np = dev->mt76.dev->of_node;

	अगर (!is_mt7622(&dev->mt76))
		वापस 0;

	dev->infracfg = syscon_regmap_lookup_by_phandle(np, "mediatek,infracfg");
	अगर (IS_ERR(dev->infracfg)) अणु
		dev_err(dev->mt76.dev, "Cannot find infracfg controller\n");
		वापस PTR_ERR(dev->infracfg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7622_wmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	व्योम __iomem *mem_base;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	mem_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mem_base))
		वापस PTR_ERR(mem_base);

	वापस mt7615_mmio_probe(&pdev->dev, mem_base, irq, mt7615e_reg_map);
पूर्ण

अटल पूर्णांक mt7622_wmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt7615_dev *dev = platक्रमm_get_drvdata(pdev);

	mt7615_unरेजिस्टर_device(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7622_wmac_of_match[] = अणु
	अणु .compatible = "mediatek,mt7622-wmac" पूर्ण,
	अणुपूर्ण,
पूर्ण;

काष्ठा platक्रमm_driver mt7622_wmac_driver = अणु
	.driver = अणु
		.name = "mt7622-wmac",
		.of_match_table = mt7622_wmac_of_match,
	पूर्ण,
	.probe = mt7622_wmac_probe,
	.हटाओ = mt7622_wmac_हटाओ,
पूर्ण;

MODULE_FIRMWARE(MT7622_FIRMWARE_N9);
MODULE_FIRMWARE(MT7622_ROM_PATCH);
