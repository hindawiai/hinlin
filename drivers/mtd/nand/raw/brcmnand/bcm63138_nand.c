<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2015 Broadcom Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "brcmnand.h"

काष्ठा bcm63138_nand_soc अणु
	काष्ठा brcmnand_soc soc;
	व्योम __iomem *base;
पूर्ण;

#घोषणा BCM63138_न_अंकD_INT_STATUS		0x00
#घोषणा BCM63138_न_अंकD_INT_EN			0x04

क्रमागत अणु
	BCM63138_CTLRDY		= BIT(4),
पूर्ण;

अटल bool bcm63138_nand_पूर्णांकc_ack(काष्ठा brcmnand_soc *soc)
अणु
	काष्ठा bcm63138_nand_soc *priv =
			container_of(soc, काष्ठा bcm63138_nand_soc, soc);
	व्योम __iomem *mmio = priv->base + BCM63138_न_अंकD_INT_STATUS;
	u32 val = brcmnand_पढ़ोl(mmio);

	अगर (val & BCM63138_CTLRDY) अणु
		brcmnand_ग_लिखोl(val & ~BCM63138_CTLRDY, mmio);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम bcm63138_nand_पूर्णांकc_set(काष्ठा brcmnand_soc *soc, bool en)
अणु
	काष्ठा bcm63138_nand_soc *priv =
			container_of(soc, काष्ठा bcm63138_nand_soc, soc);
	व्योम __iomem *mmio = priv->base + BCM63138_न_अंकD_INT_EN;
	u32 val = brcmnand_पढ़ोl(mmio);

	अगर (en)
		val |= BCM63138_CTLRDY;
	अन्यथा
		val &= ~BCM63138_CTLRDY;

	brcmnand_ग_लिखोl(val, mmio);
पूर्ण

अटल पूर्णांक bcm63138_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm63138_nand_soc *priv;
	काष्ठा brcmnand_soc *soc;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	soc = &priv->soc;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nand-int-base");
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	soc->ctlrdy_ack = bcm63138_nand_पूर्णांकc_ack;
	soc->ctlrdy_set_enabled = bcm63138_nand_पूर्णांकc_set;

	वापस brcmnand_probe(pdev, soc);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm63138_nand_of_match[] = अणु
	अणु .compatible = "brcm,nand-bcm63138" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm63138_nand_of_match);

अटल काष्ठा platक्रमm_driver bcm63138_nand_driver = अणु
	.probe			= bcm63138_nand_probe,
	.हटाओ			= brcmnand_हटाओ,
	.driver = अणु
		.name		= "bcm63138_nand",
		.pm		= &brcmnand_pm_ops,
		.of_match_table	= bcm63138_nand_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(bcm63138_nand_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Norris");
MODULE_DESCRIPTION("NAND driver for BCM63138");
