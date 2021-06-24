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

काष्ठा iproc_nand_soc अणु
	काष्ठा brcmnand_soc soc;

	व्योम __iomem *idm_base;
	व्योम __iomem *ext_base;
	spinlock_t idm_lock;
पूर्ण;

#घोषणा IPROC_न_अंकD_CTLR_READY_OFFSET       0x10
#घोषणा IPROC_न_अंकD_CTLR_READY              BIT(0)

#घोषणा IPROC_न_अंकD_IO_CTRL_OFFSET          0x00
#घोषणा IPROC_न_अंकD_APB_LE_MODE             BIT(24)
#घोषणा IPROC_न_अंकD_INT_CTRL_READ_ENABLE    BIT(6)

अटल bool iproc_nand_पूर्णांकc_ack(काष्ठा brcmnand_soc *soc)
अणु
	काष्ठा iproc_nand_soc *priv =
			container_of(soc, काष्ठा iproc_nand_soc, soc);
	व्योम __iomem *mmio = priv->ext_base + IPROC_न_अंकD_CTLR_READY_OFFSET;
	u32 val = brcmnand_पढ़ोl(mmio);

	अगर (val & IPROC_न_अंकD_CTLR_READY) अणु
		brcmnand_ग_लिखोl(IPROC_न_अंकD_CTLR_READY, mmio);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम iproc_nand_पूर्णांकc_set(काष्ठा brcmnand_soc *soc, bool en)
अणु
	काष्ठा iproc_nand_soc *priv =
			container_of(soc, काष्ठा iproc_nand_soc, soc);
	व्योम __iomem *mmio = priv->idm_base + IPROC_न_अंकD_IO_CTRL_OFFSET;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->idm_lock, flags);

	val = brcmnand_पढ़ोl(mmio);

	अगर (en)
		val |= IPROC_न_अंकD_INT_CTRL_READ_ENABLE;
	अन्यथा
		val &= ~IPROC_न_अंकD_INT_CTRL_READ_ENABLE;

	brcmnand_ग_लिखोl(val, mmio);

	spin_unlock_irqrestore(&priv->idm_lock, flags);
पूर्ण

अटल व्योम iproc_nand_apb_access(काष्ठा brcmnand_soc *soc, bool prepare,
				  bool is_param)
अणु
	काष्ठा iproc_nand_soc *priv =
			container_of(soc, काष्ठा iproc_nand_soc, soc);
	व्योम __iomem *mmio = priv->idm_base + IPROC_न_अंकD_IO_CTRL_OFFSET;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->idm_lock, flags);

	val = brcmnand_पढ़ोl(mmio);

	/*
	 * In the हाल of BE or when dealing with न_अंकD data, alway configure
	 * the APB bus to LE mode beक्रमe accessing the FIFO and back to BE mode
	 * after the access is करोne
	 */
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN) || !is_param) अणु
		अगर (prepare)
			val |= IPROC_न_अंकD_APB_LE_MODE;
		अन्यथा
			val &= ~IPROC_न_अंकD_APB_LE_MODE;
	पूर्ण अन्यथा अणु /* when in LE accessing the parameter page, keep APB in BE */
		val &= ~IPROC_न_अंकD_APB_LE_MODE;
	पूर्ण

	brcmnand_ग_लिखोl(val, mmio);

	spin_unlock_irqrestore(&priv->idm_lock, flags);
पूर्ण

अटल पूर्णांक iproc_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iproc_nand_soc *priv;
	काष्ठा brcmnand_soc *soc;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	soc = &priv->soc;

	spin_lock_init(&priv->idm_lock);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "iproc-idm");
	priv->idm_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->idm_base))
		वापस PTR_ERR(priv->idm_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "iproc-ext");
	priv->ext_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->ext_base))
		वापस PTR_ERR(priv->ext_base);

	soc->ctlrdy_ack = iproc_nand_पूर्णांकc_ack;
	soc->ctlrdy_set_enabled = iproc_nand_पूर्णांकc_set;
	soc->prepare_data_bus = iproc_nand_apb_access;

	वापस brcmnand_probe(pdev, soc);
पूर्ण

अटल स्थिर काष्ठा of_device_id iproc_nand_of_match[] = अणु
	अणु .compatible = "brcm,nand-iproc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, iproc_nand_of_match);

अटल काष्ठा platक्रमm_driver iproc_nand_driver = अणु
	.probe			= iproc_nand_probe,
	.हटाओ			= brcmnand_हटाओ,
	.driver = अणु
		.name		= "iproc_nand",
		.pm		= &brcmnand_pm_ops,
		.of_match_table	= iproc_nand_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(iproc_nand_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Norris");
MODULE_AUTHOR("Ray Jui");
MODULE_DESCRIPTION("NAND driver for Broadcom IPROC-based SoCs");
