<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  pci-rcar-gen2: पूर्णांकernal PCI bus support
 *
 * Copyright (C) 2013 Renesas Solutions Corp.
 * Copyright (C) 2013 Cogent Embedded, Inc.
 *
 * Author: Valentine Barshak <valentine.barshak@cogentembedded.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#समावेश "../pci.h"

/* AHB-PCI Bridge PCI communication रेजिस्टरs */
#घोषणा RCAR_AHBPCI_PCICOM_OFFSET	0x800

#घोषणा RCAR_PCIAHB_WIN1_CTR_REG	(RCAR_AHBPCI_PCICOM_OFFSET + 0x00)
#घोषणा RCAR_PCIAHB_WIN2_CTR_REG	(RCAR_AHBPCI_PCICOM_OFFSET + 0x04)
#घोषणा RCAR_PCIAHB_PREFETCH0		0x0
#घोषणा RCAR_PCIAHB_PREFETCH4		0x1
#घोषणा RCAR_PCIAHB_PREFETCH8		0x2
#घोषणा RCAR_PCIAHB_PREFETCH16		0x3

#घोषणा RCAR_AHBPCI_WIN1_CTR_REG	(RCAR_AHBPCI_PCICOM_OFFSET + 0x10)
#घोषणा RCAR_AHBPCI_WIN2_CTR_REG	(RCAR_AHBPCI_PCICOM_OFFSET + 0x14)
#घोषणा RCAR_AHBPCI_WIN_CTR_MEM		(3 << 1)
#घोषणा RCAR_AHBPCI_WIN_CTR_CFG		(5 << 1)
#घोषणा RCAR_AHBPCI_WIN1_HOST		(1 << 30)
#घोषणा RCAR_AHBPCI_WIN1_DEVICE		(1 << 31)

#घोषणा RCAR_PCI_INT_ENABLE_REG		(RCAR_AHBPCI_PCICOM_OFFSET + 0x20)
#घोषणा RCAR_PCI_INT_STATUS_REG		(RCAR_AHBPCI_PCICOM_OFFSET + 0x24)
#घोषणा RCAR_PCI_INT_SIGTABORT		(1 << 0)
#घोषणा RCAR_PCI_INT_SIGRETABORT	(1 << 1)
#घोषणा RCAR_PCI_INT_REMABORT		(1 << 2)
#घोषणा RCAR_PCI_INT_PERR		(1 << 3)
#घोषणा RCAR_PCI_INT_SIGSERR		(1 << 4)
#घोषणा RCAR_PCI_INT_RESERR		(1 << 5)
#घोषणा RCAR_PCI_INT_WIN1ERR		(1 << 12)
#घोषणा RCAR_PCI_INT_WIN2ERR		(1 << 13)
#घोषणा RCAR_PCI_INT_A			(1 << 16)
#घोषणा RCAR_PCI_INT_B			(1 << 17)
#घोषणा RCAR_PCI_INT_PME		(1 << 19)
#घोषणा RCAR_PCI_INT_ALLERRORS (RCAR_PCI_INT_SIGTABORT		| \
				RCAR_PCI_INT_SIGRETABORT	| \
				RCAR_PCI_INT_REMABORT		| \
				RCAR_PCI_INT_PERR		| \
				RCAR_PCI_INT_SIGSERR		| \
				RCAR_PCI_INT_RESERR		| \
				RCAR_PCI_INT_WIN1ERR		| \
				RCAR_PCI_INT_WIN2ERR)

#घोषणा RCAR_AHB_BUS_CTR_REG		(RCAR_AHBPCI_PCICOM_OFFSET + 0x30)
#घोषणा RCAR_AHB_BUS_MMODE_HTRANS	(1 << 0)
#घोषणा RCAR_AHB_BUS_MMODE_BYTE_BURST	(1 << 1)
#घोषणा RCAR_AHB_BUS_MMODE_WR_INCR	(1 << 2)
#घोषणा RCAR_AHB_BUS_MMODE_HBUS_REQ	(1 << 7)
#घोषणा RCAR_AHB_BUS_SMODE_READYCTR	(1 << 17)
#घोषणा RCAR_AHB_BUS_MODE		(RCAR_AHB_BUS_MMODE_HTRANS |	\
					RCAR_AHB_BUS_MMODE_BYTE_BURST |	\
					RCAR_AHB_BUS_MMODE_WR_INCR |	\
					RCAR_AHB_BUS_MMODE_HBUS_REQ |	\
					RCAR_AHB_BUS_SMODE_READYCTR)

#घोषणा RCAR_USBCTR_REG			(RCAR_AHBPCI_PCICOM_OFFSET + 0x34)
#घोषणा RCAR_USBCTR_USBH_RST		(1 << 0)
#घोषणा RCAR_USBCTR_PCICLK_MASK		(1 << 1)
#घोषणा RCAR_USBCTR_PLL_RST		(1 << 2)
#घोषणा RCAR_USBCTR_सूचीPD		(1 << 8)
#घोषणा RCAR_USBCTR_PCIAHB_WIN2_EN	(1 << 9)
#घोषणा RCAR_USBCTR_PCIAHB_WIN1_256M	(0 << 10)
#घोषणा RCAR_USBCTR_PCIAHB_WIN1_512M	(1 << 10)
#घोषणा RCAR_USBCTR_PCIAHB_WIN1_1G	(2 << 10)
#घोषणा RCAR_USBCTR_PCIAHB_WIN1_2G	(3 << 10)
#घोषणा RCAR_USBCTR_PCIAHB_WIN1_MASK	(3 << 10)

#घोषणा RCAR_PCI_ARBITER_CTR_REG	(RCAR_AHBPCI_PCICOM_OFFSET + 0x40)
#घोषणा RCAR_PCI_ARBITER_PCIREQ0	(1 << 0)
#घोषणा RCAR_PCI_ARBITER_PCIREQ1	(1 << 1)
#घोषणा RCAR_PCI_ARBITER_PCIBP_MODE	(1 << 12)

#घोषणा RCAR_PCI_UNIT_REV_REG		(RCAR_AHBPCI_PCICOM_OFFSET + 0x48)

काष्ठा rcar_pci_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *reg;
	काष्ठा resource mem_res;
	काष्ठा resource *cfg_res;
	पूर्णांक irq;
पूर्ण;

/* PCI configuration space operations */
अटल व्योम __iomem *rcar_pci_cfg_base(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				       पूर्णांक where)
अणु
	काष्ठा rcar_pci_priv *priv = bus->sysdata;
	पूर्णांक slot, val;

	अगर (!pci_is_root_bus(bus) || PCI_FUNC(devfn))
		वापस शून्य;

	/* Only one EHCI/OHCI device built-in */
	slot = PCI_SLOT(devfn);
	अगर (slot > 2)
		वापस शून्य;

	/* bridge logic only has रेजिस्टरs to 0x40 */
	अगर (slot == 0x0 && where >= 0x40)
		वापस शून्य;

	val = slot ? RCAR_AHBPCI_WIN1_DEVICE | RCAR_AHBPCI_WIN_CTR_CFG :
		     RCAR_AHBPCI_WIN1_HOST | RCAR_AHBPCI_WIN_CTR_CFG;

	ioग_लिखो32(val, priv->reg + RCAR_AHBPCI_WIN1_CTR_REG);
	वापस priv->reg + (slot >> 1) * 0x100 + where;
पूर्ण

#अगर_घोषित CONFIG_PCI_DEBUG
/* अगर debug enabled, then attach an error handler irq to the bridge */

अटल irqवापस_t rcar_pci_err_irq(पूर्णांक irq, व्योम *pw)
अणु
	काष्ठा rcar_pci_priv *priv = pw;
	काष्ठा device *dev = priv->dev;
	u32 status = ioपढ़ो32(priv->reg + RCAR_PCI_INT_STATUS_REG);

	अगर (status & RCAR_PCI_INT_ALLERRORS) अणु
		dev_err(dev, "error irq: status %08x\n", status);

		/* clear the error(s) */
		ioग_लिखो32(status & RCAR_PCI_INT_ALLERRORS,
			  priv->reg + RCAR_PCI_INT_STATUS_REG);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम rcar_pci_setup_errirq(काष्ठा rcar_pci_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret;
	u32 val;

	ret = devm_request_irq(dev, priv->irq, rcar_pci_err_irq,
			       IRQF_SHARED, "error irq", priv);
	अगर (ret) अणु
		dev_err(dev, "cannot claim IRQ for error handling\n");
		वापस;
	पूर्ण

	val = ioपढ़ो32(priv->reg + RCAR_PCI_INT_ENABLE_REG);
	val |= RCAR_PCI_INT_ALLERRORS;
	ioग_लिखो32(val, priv->reg + RCAR_PCI_INT_ENABLE_REG);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rcar_pci_setup_errirq(काष्ठा rcar_pci_priv *priv) अणु पूर्ण
#पूर्ण_अगर

/* PCI host controller setup */
अटल व्योम rcar_pci_setup(काष्ठा rcar_pci_priv *priv)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(priv);
	काष्ठा device *dev = priv->dev;
	व्योम __iomem *reg = priv->reg;
	काष्ठा resource_entry *entry;
	अचिन्हित दीर्घ winकरोw_size;
	अचिन्हित दीर्घ winकरोw_addr;
	अचिन्हित दीर्घ winकरोw_pci;
	u32 val;

	entry = resource_list_first_type(&bridge->dma_ranges, IORESOURCE_MEM);
	अगर (!entry) अणु
		winकरोw_addr = 0x40000000;
		winकरोw_pci = 0x40000000;
		winकरोw_size = SZ_1G;
	पूर्ण अन्यथा अणु
		winकरोw_addr = entry->res->start;
		winकरोw_pci = entry->res->start - entry->offset;
		winकरोw_size = resource_size(entry->res);
	पूर्ण

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	val = ioपढ़ो32(reg + RCAR_PCI_UNIT_REV_REG);
	dev_info(dev, "PCI: revision %x\n", val);

	/* Disable Direct Power Down State and निश्चित reset */
	val = ioपढ़ो32(reg + RCAR_USBCTR_REG) & ~RCAR_USBCTR_सूचीPD;
	val |= RCAR_USBCTR_USBH_RST | RCAR_USBCTR_PLL_RST;
	ioग_लिखो32(val, reg + RCAR_USBCTR_REG);
	udelay(4);

	/* De-निश्चित reset and reset PCIAHB winकरोw1 size */
	val &= ~(RCAR_USBCTR_PCIAHB_WIN1_MASK | RCAR_USBCTR_PCICLK_MASK |
		 RCAR_USBCTR_USBH_RST | RCAR_USBCTR_PLL_RST);

	/* Setup PCIAHB winकरोw1 size */
	चयन (winकरोw_size) अणु
	हाल SZ_2G:
		val |= RCAR_USBCTR_PCIAHB_WIN1_2G;
		अवरोध;
	हाल SZ_1G:
		val |= RCAR_USBCTR_PCIAHB_WIN1_1G;
		अवरोध;
	हाल SZ_512M:
		val |= RCAR_USBCTR_PCIAHB_WIN1_512M;
		अवरोध;
	शेष:
		pr_warn("unknown window size %ld - defaulting to 256M\n",
			winकरोw_size);
		winकरोw_size = SZ_256M;
		fallthrough;
	हाल SZ_256M:
		val |= RCAR_USBCTR_PCIAHB_WIN1_256M;
		अवरोध;
	पूर्ण
	ioग_लिखो32(val, reg + RCAR_USBCTR_REG);

	/* Configure AHB master and slave modes */
	ioग_लिखो32(RCAR_AHB_BUS_MODE, reg + RCAR_AHB_BUS_CTR_REG);

	/* Configure PCI arbiter */
	val = ioपढ़ो32(reg + RCAR_PCI_ARBITER_CTR_REG);
	val |= RCAR_PCI_ARBITER_PCIREQ0 | RCAR_PCI_ARBITER_PCIREQ1 |
	       RCAR_PCI_ARBITER_PCIBP_MODE;
	ioग_लिखो32(val, reg + RCAR_PCI_ARBITER_CTR_REG);

	/* PCI-AHB mapping */
	ioग_लिखो32(winकरोw_addr | RCAR_PCIAHB_PREFETCH16,
		  reg + RCAR_PCIAHB_WIN1_CTR_REG);

	/* AHB-PCI mapping: OHCI/EHCI रेजिस्टरs */
	val = priv->mem_res.start | RCAR_AHBPCI_WIN_CTR_MEM;
	ioग_लिखो32(val, reg + RCAR_AHBPCI_WIN2_CTR_REG);

	/* Enable AHB-PCI bridge PCI configuration access */
	ioग_लिखो32(RCAR_AHBPCI_WIN1_HOST | RCAR_AHBPCI_WIN_CTR_CFG,
		  reg + RCAR_AHBPCI_WIN1_CTR_REG);
	/* Set PCI-AHB Winकरोw1 address */
	ioग_लिखो32(winकरोw_pci | PCI_BASE_ADDRESS_MEM_PREFETCH,
		  reg + PCI_BASE_ADDRESS_1);
	/* Set AHB-PCI bridge PCI communication area address */
	val = priv->cfg_res->start + RCAR_AHBPCI_PCICOM_OFFSET;
	ioग_लिखो32(val, reg + PCI_BASE_ADDRESS_0);

	val = ioपढ़ो32(reg + PCI_COMMAND);
	val |= PCI_COMMAND_SERR | PCI_COMMAND_PARITY |
	       PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
	ioग_लिखो32(val, reg + PCI_COMMAND);

	/* Enable PCI पूर्णांकerrupts */
	ioग_लिखो32(RCAR_PCI_INT_A | RCAR_PCI_INT_B | RCAR_PCI_INT_PME,
		  reg + RCAR_PCI_INT_ENABLE_REG);

	rcar_pci_setup_errirq(priv);
पूर्ण

अटल काष्ठा pci_ops rcar_pci_ops = अणु
	.map_bus = rcar_pci_cfg_base,
	.पढ़ो	= pci_generic_config_पढ़ो,
	.ग_लिखो	= pci_generic_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक rcar_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *cfg_res, *mem_res;
	काष्ठा rcar_pci_priv *priv;
	काष्ठा pci_host_bridge *bridge;
	व्योम __iomem *reg;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*priv));
	अगर (!bridge)
		वापस -ENOMEM;

	priv = pci_host_bridge_priv(bridge);
	bridge->sysdata = priv;

	cfg_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(dev, cfg_res);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!mem_res || !mem_res->start)
		वापस -ENODEV;

	अगर (mem_res->start & 0xFFFF)
		वापस -EINVAL;

	priv->mem_res = *mem_res;
	priv->cfg_res = cfg_res;

	priv->irq = platक्रमm_get_irq(pdev, 0);
	priv->reg = reg;
	priv->dev = dev;

	अगर (priv->irq < 0) अणु
		dev_err(dev, "no valid irq found\n");
		वापस priv->irq;
	पूर्ण

	bridge->ops = &rcar_pci_ops;

	pci_add_flags(PCI_REASSIGN_ALL_BUS);

	rcar_pci_setup(priv);

	वापस pci_host_probe(bridge);
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_pci_of_match[] = अणु
	अणु .compatible = "renesas,pci-r8a7790", पूर्ण,
	अणु .compatible = "renesas,pci-r8a7791", पूर्ण,
	अणु .compatible = "renesas,pci-r8a7794", पूर्ण,
	अणु .compatible = "renesas,pci-rcar-gen2", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_pci_driver = अणु
	.driver = अणु
		.name = "pci-rcar-gen2",
		.suppress_bind_attrs = true,
		.of_match_table = rcar_pci_of_match,
	पूर्ण,
	.probe = rcar_pci_probe,
पूर्ण;
builtin_platक्रमm_driver(rcar_pci_driver);
