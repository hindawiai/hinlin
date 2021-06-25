<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom Limited
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "spi-bcm-qspi.h"

#घोषणा INTR_BASE_BIT_SHIFT			0x02
#घोषणा INTR_COUNT				0x07

काष्ठा bcm_iproc_पूर्णांकc अणु
	काष्ठा bcm_qspi_soc_पूर्णांकc soc_पूर्णांकc;
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *पूर्णांक_reg;
	व्योम __iomem *पूर्णांक_status_reg;
	spinlock_t soघड़ी;
	bool big_endian;
पूर्ण;

अटल u32 bcm_iproc_qspi_get_l2_पूर्णांक_status(काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc)
अणु
	काष्ठा bcm_iproc_पूर्णांकc *priv =
			container_of(soc_पूर्णांकc, काष्ठा bcm_iproc_पूर्णांकc, soc_पूर्णांकc);
	व्योम __iomem *mmio = priv->पूर्णांक_status_reg;
	पूर्णांक i;
	u32 val = 0, sts = 0;

	क्रम (i = 0; i < INTR_COUNT; i++) अणु
		अगर (bcm_qspi_पढ़ोl(priv->big_endian, mmio + (i * 4)))
			val |= 1UL << i;
	पूर्ण

	अगर (val & INTR_MSPI_DONE_MASK)
		sts |= MSPI_DONE;

	अगर (val & BSPI_LR_INTERRUPTS_ALL)
		sts |= BSPI_DONE;

	अगर (val & BSPI_LR_INTERRUPTS_ERROR)
		sts |= BSPI_ERR;

	वापस sts;
पूर्ण

अटल व्योम bcm_iproc_qspi_पूर्णांक_ack(काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc, पूर्णांक type)
अणु
	काष्ठा bcm_iproc_पूर्णांकc *priv =
			container_of(soc_पूर्णांकc, काष्ठा bcm_iproc_पूर्णांकc, soc_पूर्णांकc);
	व्योम __iomem *mmio = priv->पूर्णांक_status_reg;
	u32 mask = get_qspi_mask(type);
	पूर्णांक i;

	क्रम (i = 0; i < INTR_COUNT; i++) अणु
		अगर (mask & (1UL << i))
			bcm_qspi_ग_लिखोl(priv->big_endian, 1, mmio + (i * 4));
	पूर्ण
पूर्ण

अटल व्योम bcm_iproc_qspi_पूर्णांक_set(काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc, पूर्णांक type,
				   bool en)
अणु
	काष्ठा bcm_iproc_पूर्णांकc *priv =
			container_of(soc_पूर्णांकc, काष्ठा bcm_iproc_पूर्णांकc, soc_पूर्णांकc);
	व्योम __iomem *mmio = priv->पूर्णांक_reg;
	u32 mask = get_qspi_mask(type);
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->soघड़ी, flags);

	val = bcm_qspi_पढ़ोl(priv->big_endian, mmio);

	अगर (en)
		val = val | (mask << INTR_BASE_BIT_SHIFT);
	अन्यथा
		val = val & ~(mask << INTR_BASE_BIT_SHIFT);

	bcm_qspi_ग_लिखोl(priv->big_endian, val, mmio);

	spin_unlock_irqrestore(&priv->soघड़ी, flags);
पूर्ण

अटल पूर्णांक bcm_iproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm_iproc_पूर्णांकc *priv;
	काष्ठा bcm_qspi_soc_पूर्णांकc *soc_पूर्णांकc;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	soc_पूर्णांकc = &priv->soc_पूर्णांकc;
	priv->pdev = pdev;

	spin_lock_init(&priv->soघड़ी);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "intr_regs");
	priv->पूर्णांक_reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->पूर्णांक_reg))
		वापस PTR_ERR(priv->पूर्णांक_reg);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "intr_status_reg");
	priv->पूर्णांक_status_reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->पूर्णांक_status_reg))
		वापस PTR_ERR(priv->पूर्णांक_status_reg);

	priv->big_endian = of_device_is_big_endian(dev->of_node);

	bcm_iproc_qspi_पूर्णांक_ack(soc_पूर्णांकc, MSPI_BSPI_DONE);
	bcm_iproc_qspi_पूर्णांक_set(soc_पूर्णांकc, MSPI_BSPI_DONE, false);

	soc_पूर्णांकc->bcm_qspi_पूर्णांक_ack = bcm_iproc_qspi_पूर्णांक_ack;
	soc_पूर्णांकc->bcm_qspi_पूर्णांक_set = bcm_iproc_qspi_पूर्णांक_set;
	soc_पूर्णांकc->bcm_qspi_get_पूर्णांक_status = bcm_iproc_qspi_get_l2_पूर्णांक_status;

	वापस bcm_qspi_probe(pdev, soc_पूर्णांकc);
पूर्ण

अटल पूर्णांक bcm_iproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm_qspi_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_iproc_of_match[] = अणु
	अणु .compatible = "brcm,spi-nsp-qspi" पूर्ण,
	अणु .compatible = "brcm,spi-ns2-qspi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_iproc_of_match);

अटल काष्ठा platक्रमm_driver bcm_iproc_driver = अणु
	.probe			= bcm_iproc_probe,
	.हटाओ			= bcm_iproc_हटाओ,
	.driver = अणु
		.name		= "bcm_iproc",
		.pm		= &bcm_qspi_pm_ops,
		.of_match_table = bcm_iproc_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(bcm_iproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kamal Dasu");
MODULE_DESCRIPTION("SPI flash driver for Broadcom iProc SoCs");
