<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015 Simon Arlott
 *
 * Derived from bcm63138_nand.c:
 * Copyright तऊ 2015 Broadcom Corporation
 *
 * Derived from bcm963xx_4.12L.06B_consumer/shared/खोलोsource/include/bcm963xx/63268_map_part.h:
 * Copyright 2000-2010 Broadcom Corporation
 *
 * Derived from bcm963xx_4.12L.06B_consumer/shared/खोलोsource/flash/nandflash.c:
 * Copyright 2000-2010 Broadcom Corporation
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

काष्ठा bcm6368_nand_soc अणु
	काष्ठा brcmnand_soc soc;
	व्योम __iomem *base;
पूर्ण;

#घोषणा BCM6368_न_अंकD_INT		0x00
#घोषणा  BCM6368_न_अंकD_STATUS_SHIFT	0
#घोषणा  BCM6368_न_अंकD_STATUS_MASK	(0xfff << BCM6368_न_अंकD_STATUS_SHIFT)
#घोषणा  BCM6368_न_अंकD_ENABLE_SHIFT	16
#घोषणा  BCM6368_न_अंकD_ENABLE_MASK	(0xffff << BCM6368_न_अंकD_ENABLE_SHIFT)
#घोषणा BCM6368_न_अंकD_BASE_ADDR0	0x04
#घोषणा BCM6368_न_अंकD_BASE_ADDR1	0x0c

क्रमागत अणु
	BCM6368_NP_READ		= BIT(0),
	BCM6368_BLOCK_ERASE	= BIT(1),
	BCM6368_COPY_BACK	= BIT(2),
	BCM6368_PAGE_PGM	= BIT(3),
	BCM6368_CTRL_READY	= BIT(4),
	BCM6368_DEV_RBPIN	= BIT(5),
	BCM6368_ECC_ERR_UNC	= BIT(6),
	BCM6368_ECC_ERR_CORR	= BIT(7),
पूर्ण;

अटल bool bcm6368_nand_पूर्णांकc_ack(काष्ठा brcmnand_soc *soc)
अणु
	काष्ठा bcm6368_nand_soc *priv =
			container_of(soc, काष्ठा bcm6368_nand_soc, soc);
	व्योम __iomem *mmio = priv->base + BCM6368_न_अंकD_INT;
	u32 val = brcmnand_पढ़ोl(mmio);

	अगर (val & (BCM6368_CTRL_READY << BCM6368_न_अंकD_STATUS_SHIFT)) अणु
		/* Ack पूर्णांकerrupt */
		val &= ~BCM6368_न_अंकD_STATUS_MASK;
		val |= BCM6368_CTRL_READY << BCM6368_न_अंकD_STATUS_SHIFT;
		brcmnand_ग_लिखोl(val, mmio);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम bcm6368_nand_पूर्णांकc_set(काष्ठा brcmnand_soc *soc, bool en)
अणु
	काष्ठा bcm6368_nand_soc *priv =
			container_of(soc, काष्ठा bcm6368_nand_soc, soc);
	व्योम __iomem *mmio = priv->base + BCM6368_न_अंकD_INT;
	u32 val = brcmnand_पढ़ोl(mmio);

	/* Don't ack any पूर्णांकerrupts */
	val &= ~BCM6368_न_अंकD_STATUS_MASK;

	अगर (en)
		val |= BCM6368_CTRL_READY << BCM6368_न_अंकD_ENABLE_SHIFT;
	अन्यथा
		val &= ~(BCM6368_CTRL_READY << BCM6368_न_अंकD_ENABLE_SHIFT);

	brcmnand_ग_लिखोl(val, mmio);
पूर्ण

अटल पूर्णांक bcm6368_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm6368_nand_soc *priv;
	काष्ठा brcmnand_soc *soc;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	soc = &priv->soc;

	res = platक्रमm_get_resource_byname(pdev,
		IORESOURCE_MEM, "nand-int-base");
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	soc->ctlrdy_ack = bcm6368_nand_पूर्णांकc_ack;
	soc->ctlrdy_set_enabled = bcm6368_nand_पूर्णांकc_set;

	/* Disable and ack all पूर्णांकerrupts  */
	brcmnand_ग_लिखोl(0, priv->base + BCM6368_न_अंकD_INT);
	brcmnand_ग_लिखोl(BCM6368_न_अंकD_STATUS_MASK,
			priv->base + BCM6368_न_अंकD_INT);

	वापस brcmnand_probe(pdev, soc);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6368_nand_of_match[] = अणु
	अणु .compatible = "brcm,nand-bcm6368" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm6368_nand_of_match);

अटल काष्ठा platक्रमm_driver bcm6368_nand_driver = अणु
	.probe			= bcm6368_nand_probe,
	.हटाओ			= brcmnand_हटाओ,
	.driver = अणु
		.name		= "bcm6368_nand",
		.pm		= &brcmnand_pm_ops,
		.of_match_table	= bcm6368_nand_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(bcm6368_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Simon Arlott");
MODULE_DESCRIPTION("NAND driver for BCM6368");
