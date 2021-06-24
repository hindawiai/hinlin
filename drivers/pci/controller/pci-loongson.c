<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Loongson PCI Host Controller Driver
 *
 * Copyright (C) 2020 Jiaxun Yang <jiaxun.yang@flygoat.com>
 */

#समावेश <linux/of_device.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>

#समावेश "../pci.h"

/* Device IDs */
#घोषणा DEV_PCIE_PORT_0	0x7a09
#घोषणा DEV_PCIE_PORT_1	0x7a19
#घोषणा DEV_PCIE_PORT_2	0x7a29

#घोषणा DEV_LS2K_APB	0x7a02
#घोषणा DEV_LS7A_CONF	0x7a10
#घोषणा DEV_LS7A_LPC	0x7a0c

#घोषणा FLAG_CFG0	BIT(0)
#घोषणा FLAG_CFG1	BIT(1)
#घोषणा FLAG_DEV_FIX	BIT(2)

काष्ठा loongson_pci अणु
	व्योम __iomem *cfg0_base;
	व्योम __iomem *cfg1_base;
	काष्ठा platक्रमm_device *pdev;
	u32 flags;
पूर्ण;

/* Fixup wrong class code in PCIe bridges */
अटल व्योम bridge_class_quirk(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_LOONGSON,
			DEV_PCIE_PORT_0, bridge_class_quirk);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_LOONGSON,
			DEV_PCIE_PORT_1, bridge_class_quirk);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_LOONGSON,
			DEV_PCIE_PORT_2, bridge_class_quirk);

अटल व्योम प्रणाली_bus_quirk(काष्ठा pci_dev *pdev)
अणु
	/*
	 * The address space consumed by these devices is outside the
	 * resources of the host bridge.
	 */
	pdev->mmio_always_on = 1;
	pdev->non_compliant_bars = 1;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_LOONGSON,
			DEV_LS2K_APB, प्रणाली_bus_quirk);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_LOONGSON,
			DEV_LS7A_CONF, प्रणाली_bus_quirk);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_LOONGSON,
			DEV_LS7A_LPC, प्रणाली_bus_quirk);

अटल व्योम loongson_mrrs_quirk(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा pci_dev *bridge;
	अटल स्थिर काष्ठा pci_device_id bridge_devids[] = अणु
		अणु PCI_VDEVICE(LOONGSON, DEV_PCIE_PORT_0) पूर्ण,
		अणु PCI_VDEVICE(LOONGSON, DEV_PCIE_PORT_1) पूर्ण,
		अणु PCI_VDEVICE(LOONGSON, DEV_PCIE_PORT_2) पूर्ण,
		अणु 0, पूर्ण,
	पूर्ण;

	/* look क्रम the matching bridge */
	जबतक (!pci_is_root_bus(bus)) अणु
		bridge = bus->self;
		bus = bus->parent;
		/*
		 * Some Loongson PCIe ports have a h/w limitation of
		 * 256 bytes maximum पढ़ो request size. They can't handle
		 * anything larger than this. So क्रमce this limit on
		 * any devices attached under these ports.
		 */
		अगर (pci_match_id(bridge_devids, bridge)) अणु
			अगर (pcie_get_पढ़ोrq(dev) > 256) अणु
				pci_info(dev, "limiting MRRS to 256\n");
				pcie_set_पढ़ोrq(dev, 256);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_ANY_ID, PCI_ANY_ID, loongson_mrrs_quirk);

अटल व्योम __iomem *cfg1_map(काष्ठा loongson_pci *priv, पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	अचिन्हित दीर्घ addroff = 0x0;

	अगर (bus != 0)
		addroff |= BIT(28); /* Type 1 Access */
	addroff |= (where & 0xff) | ((where & 0xf00) << 16);
	addroff |= (bus << 16) | (devfn << 8);
	वापस priv->cfg1_base + addroff;
पूर्ण

अटल व्योम __iomem *cfg0_map(काष्ठा loongson_pci *priv, पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	अचिन्हित दीर्घ addroff = 0x0;

	अगर (bus != 0)
		addroff |= BIT(24); /* Type 1 Access */
	addroff |= (bus << 16) | (devfn << 8) | where;
	वापस priv->cfg0_base + addroff;
पूर्ण

अटल व्योम __iomem *pci_loongson_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where)
अणु
	अचिन्हित अक्षर busnum = bus->number;
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(bus);
	काष्ठा loongson_pci *priv =  pci_host_bridge_priv(bridge);

	/*
	 * Do not पढ़ो more than one device on the bus other than
	 * the host bus. For our hardware the root bus is always bus 0.
	 */
	अगर (priv->flags & FLAG_DEV_FIX && busnum != 0 &&
		PCI_SLOT(devfn) > 0)
		वापस शून्य;

	/* CFG0 can only access standard space */
	अगर (where < PCI_CFG_SPACE_SIZE && priv->cfg0_base)
		वापस cfg0_map(priv, busnum, devfn, where);

	/* CFG1 can access extended space */
	अगर (where < PCI_CFG_SPACE_EXP_SIZE && priv->cfg1_base)
		वापस cfg1_map(priv, busnum, devfn, where);

	वापस शून्य;
पूर्ण

अटल पूर्णांक loongson_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;
	u8 val;

	irq = of_irq_parse_and_map_pci(dev, slot, pin);
	अगर (irq > 0)
		वापस irq;

	/* Care i8259 legacy प्रणालीs */
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &val);
	/* i8259 only have 15 IRQs */
	अगर (val > 15)
		वापस 0;

	वापस val;
पूर्ण

/* H/w only accept 32-bit PCI operations */
अटल काष्ठा pci_ops loongson_pci_ops = अणु
	.map_bus = pci_loongson_map_bus,
	.पढ़ो	= pci_generic_config_पढ़ो32,
	.ग_लिखो	= pci_generic_config_ग_लिखो32,
पूर्ण;

अटल स्थिर काष्ठा of_device_id loongson_pci_of_match[] = अणु
	अणु .compatible = "loongson,ls2k-pci",
		.data = (व्योम *)(FLAG_CFG0 | FLAG_CFG1 | FLAG_DEV_FIX), पूर्ण,
	अणु .compatible = "loongson,ls7a-pci",
		.data = (व्योम *)(FLAG_CFG0 | FLAG_CFG1 | FLAG_DEV_FIX), पूर्ण,
	अणु .compatible = "loongson,rs780e-pci",
		.data = (व्योम *)(FLAG_CFG0), पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक loongson_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा loongson_pci *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा resource *regs;

	अगर (!node)
		वापस -ENODEV;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*priv));
	अगर (!bridge)
		वापस -ENODEV;

	priv = pci_host_bridge_priv(bridge);
	priv->pdev = pdev;
	priv->flags = (अचिन्हित दीर्घ)of_device_get_match_data(dev);

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(dev, "missing mem resources for cfg0\n");
		वापस -EINVAL;
	पूर्ण

	priv->cfg0_base = devm_pci_remap_cfg_resource(dev, regs);
	अगर (IS_ERR(priv->cfg0_base))
		वापस PTR_ERR(priv->cfg0_base);

	/* CFG1 is optional */
	अगर (priv->flags & FLAG_CFG1) अणु
		regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (!regs)
			dev_info(dev, "missing mem resource for cfg1\n");
		अन्यथा अणु
			priv->cfg1_base = devm_pci_remap_cfg_resource(dev, regs);
			अगर (IS_ERR(priv->cfg1_base))
				priv->cfg1_base = शून्य;
		पूर्ण
	पूर्ण

	bridge->sysdata = priv;
	bridge->ops = &loongson_pci_ops;
	bridge->map_irq = loongson_map_irq;

	वापस pci_host_probe(bridge);
पूर्ण

अटल काष्ठा platक्रमm_driver loongson_pci_driver = अणु
	.driver = अणु
		.name = "loongson-pci",
		.of_match_table = loongson_pci_of_match,
	पूर्ण,
	.probe = loongson_pci_probe,
पूर्ण;
builtin_platक्रमm_driver(loongson_pci_driver);
