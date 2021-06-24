<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Broadcom Gigabit Ethernet core driver
 *
 * Copyright 2008, Broadcom Corporation
 * Copyright 2008, Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_driver_gige.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/slab.h>


/*
MODULE_DESCRIPTION("SSB Broadcom Gigabit Ethernet driver");
MODULE_AUTHOR("Michael Buesch");
MODULE_LICENSE("GPL");
*/

अटल स्थिर काष्ठा ssb_device_id ssb_gige_tbl[] = अणु
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_ETHERNET_GBIT, SSB_ANY_REV),
	अणुपूर्ण,
पूर्ण;
/* MODULE_DEVICE_TABLE(ssb, ssb_gige_tbl); */


अटल अंतरभूत u8 gige_पढ़ो8(काष्ठा ssb_gige *dev, u16 offset)
अणु
	वापस ssb_पढ़ो8(dev->dev, offset);
पूर्ण

अटल अंतरभूत u16 gige_पढ़ो16(काष्ठा ssb_gige *dev, u16 offset)
अणु
	वापस ssb_पढ़ो16(dev->dev, offset);
पूर्ण

अटल अंतरभूत u32 gige_पढ़ो32(काष्ठा ssb_gige *dev, u16 offset)
अणु
	वापस ssb_पढ़ो32(dev->dev, offset);
पूर्ण

अटल अंतरभूत व्योम gige_ग_लिखो8(काष्ठा ssb_gige *dev,
			       u16 offset, u8 value)
अणु
	ssb_ग_लिखो8(dev->dev, offset, value);
पूर्ण

अटल अंतरभूत व्योम gige_ग_लिखो16(काष्ठा ssb_gige *dev,
				u16 offset, u16 value)
अणु
	ssb_ग_लिखो16(dev->dev, offset, value);
पूर्ण

अटल अंतरभूत व्योम gige_ग_लिखो32(काष्ठा ssb_gige *dev,
				u16 offset, u32 value)
अणु
	ssb_ग_लिखो32(dev->dev, offset, value);
पूर्ण

अटल अंतरभूत
u8 gige_pcicfg_पढ़ो8(काष्ठा ssb_gige *dev, अचिन्हित पूर्णांक offset)
अणु
	BUG_ON(offset >= 256);
	वापस gige_पढ़ो8(dev, SSB_GIGE_PCICFG + offset);
पूर्ण

अटल अंतरभूत
u16 gige_pcicfg_पढ़ो16(काष्ठा ssb_gige *dev, अचिन्हित पूर्णांक offset)
अणु
	BUG_ON(offset >= 256);
	वापस gige_पढ़ो16(dev, SSB_GIGE_PCICFG + offset);
पूर्ण

अटल अंतरभूत
u32 gige_pcicfg_पढ़ो32(काष्ठा ssb_gige *dev, अचिन्हित पूर्णांक offset)
अणु
	BUG_ON(offset >= 256);
	वापस gige_पढ़ो32(dev, SSB_GIGE_PCICFG + offset);
पूर्ण

अटल अंतरभूत
व्योम gige_pcicfg_ग_लिखो8(काष्ठा ssb_gige *dev,
			अचिन्हित पूर्णांक offset, u8 value)
अणु
	BUG_ON(offset >= 256);
	gige_ग_लिखो8(dev, SSB_GIGE_PCICFG + offset, value);
पूर्ण

अटल अंतरभूत
व्योम gige_pcicfg_ग_लिखो16(काष्ठा ssb_gige *dev,
			 अचिन्हित पूर्णांक offset, u16 value)
अणु
	BUG_ON(offset >= 256);
	gige_ग_लिखो16(dev, SSB_GIGE_PCICFG + offset, value);
पूर्ण

अटल अंतरभूत
व्योम gige_pcicfg_ग_लिखो32(काष्ठा ssb_gige *dev,
			 अचिन्हित पूर्णांक offset, u32 value)
अणु
	BUG_ON(offset >= 256);
	gige_ग_लिखो32(dev, SSB_GIGE_PCICFG + offset, value);
पूर्ण

अटल पूर्णांक ssb_gige_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	काष्ठा ssb_gige *dev = container_of(bus->ops, काष्ठा ssb_gige, pci_ops);
	अचिन्हित दीर्घ flags;

	अगर ((PCI_SLOT(devfn) > 0) || (PCI_FUNC(devfn) > 0))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर (reg >= 256)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	spin_lock_irqsave(&dev->lock, flags);
	चयन (size) अणु
	हाल 1:
		*val = gige_pcicfg_पढ़ो8(dev, reg);
		अवरोध;
	हाल 2:
		*val = gige_pcicfg_पढ़ो16(dev, reg);
		अवरोध;
	हाल 4:
		*val = gige_pcicfg_पढ़ो32(dev, reg);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ssb_gige_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	काष्ठा ssb_gige *dev = container_of(bus->ops, काष्ठा ssb_gige, pci_ops);
	अचिन्हित दीर्घ flags;

	अगर ((PCI_SLOT(devfn) > 0) || (PCI_FUNC(devfn) > 0))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर (reg >= 256)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	spin_lock_irqsave(&dev->lock, flags);
	चयन (size) अणु
	हाल 1:
		gige_pcicfg_ग_लिखो8(dev, reg, val);
		अवरोध;
	हाल 2:
		gige_pcicfg_ग_लिखो16(dev, reg, val);
		अवरोध;
	हाल 4:
		gige_pcicfg_ग_लिखो32(dev, reg, val);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ssb_gige_probe(काष्ठा ssb_device *sdev,
			  स्थिर काष्ठा ssb_device_id *id)
अणु
	काष्ठा ssb_gige *dev;
	u32 base, पंचांगslow, पंचांगshigh;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->dev = sdev;

	spin_lock_init(&dev->lock);
	dev->pci_controller.pci_ops = &dev->pci_ops;
	dev->pci_controller.io_resource = &dev->io_resource;
	dev->pci_controller.mem_resource = &dev->mem_resource;
	dev->pci_controller.io_map_base = 0x800;
	dev->pci_ops.पढ़ो = ssb_gige_pci_पढ़ो_config;
	dev->pci_ops.ग_लिखो = ssb_gige_pci_ग_लिखो_config;

	dev->io_resource.name = SSB_GIGE_IO_RES_NAME;
	dev->io_resource.start = 0x800;
	dev->io_resource.end = 0x8FF;
	dev->io_resource.flags = IORESOURCE_IO | IORESOURCE_PCI_FIXED;

	अगर (!ssb_device_is_enabled(sdev))
		ssb_device_enable(sdev, 0);

	/* Setup BAR0. This is a 64k MMIO region. */
	base = ssb_admatch_base(ssb_पढ़ो32(sdev, SSB_ADMATCH1));
	gige_pcicfg_ग_लिखो32(dev, PCI_BASE_ADDRESS_0, base);
	gige_pcicfg_ग_लिखो32(dev, PCI_BASE_ADDRESS_1, 0);

	dev->mem_resource.name = SSB_GIGE_MEM_RES_NAME;
	dev->mem_resource.start = base;
	dev->mem_resource.end = base + 0x10000 - 1;
	dev->mem_resource.flags = IORESOURCE_MEM | IORESOURCE_PCI_FIXED;

	/* Enable the memory region. */
	gige_pcicfg_ग_लिखो16(dev, PCI_COMMAND,
			    gige_pcicfg_पढ़ो16(dev, PCI_COMMAND)
			    | PCI_COMMAND_MEMORY);

	/* Write flushing is controlled by the Flush Status Control रेजिस्टर.
	 * We want to flush every रेजिस्टर ग_लिखो with a समयout and we want
	 * to disable the IRQ mask जबतक flushing to aव्योम concurrency.
	 * Note that स्वतःmatic ग_लिखो flushing करोes _not_ work from
	 * an IRQ handler. The driver must flush manually by पढ़ोing a रेजिस्टर.
	 */
	gige_ग_लिखो32(dev, SSB_GIGE_SHIM_FLUSHSTAT, 0x00000068);

	/* Check अगर we have an RGMII or GMII PHY-bus.
	 * On RGMII करो not bypass the DLLs */
	पंचांगslow = ssb_पढ़ो32(sdev, SSB_TMSLOW);
	पंचांगshigh = ssb_पढ़ो32(sdev, SSB_TMSHIGH);
	अगर (पंचांगshigh & SSB_GIGE_TMSHIGH_RGMII) अणु
		पंचांगslow &= ~SSB_GIGE_TMSLOW_TXBYPASS;
		पंचांगslow &= ~SSB_GIGE_TMSLOW_RXBYPASS;
		dev->has_rgmii = 1;
	पूर्ण अन्यथा अणु
		पंचांगslow |= SSB_GIGE_TMSLOW_TXBYPASS;
		पंचांगslow |= SSB_GIGE_TMSLOW_RXBYPASS;
		dev->has_rgmii = 0;
	पूर्ण
	पंचांगslow |= SSB_GIGE_TMSLOW_DLLEN;
	ssb_ग_लिखो32(sdev, SSB_TMSLOW, पंचांगslow);

	ssb_set_drvdata(sdev, dev);
	रेजिस्टर_pci_controller(&dev->pci_controller);

	वापस 0;
पूर्ण

bool pdev_is_ssb_gige_core(काष्ठा pci_dev *pdev)
अणु
	अगर (!pdev->resource[0].name)
		वापस false;
	वापस (म_भेद(pdev->resource[0].name, SSB_GIGE_MEM_RES_NAME) == 0);
पूर्ण
EXPORT_SYMBOL(pdev_is_ssb_gige_core);

पूर्णांक ssb_gige_pcibios_plat_dev_init(काष्ठा ssb_device *sdev,
				   काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = ssb_get_drvdata(sdev);
	काष्ठा resource *res;

	अगर (pdev->bus->ops != &dev->pci_ops) अणु
		/* The PCI device is not on this SSB GigE bridge device. */
		वापस -ENODEV;
	पूर्ण

	/* Fixup the PCI resources. */
	res = &(pdev->resource[0]);
	res->flags = IORESOURCE_MEM | IORESOURCE_PCI_FIXED;
	res->name = dev->mem_resource.name;
	res->start = dev->mem_resource.start;
	res->end = dev->mem_resource.end;

	/* Fixup पूर्णांकerrupt lines. */
	pdev->irq = ssb_mips_irq(sdev) + 2;
	pci_ग_लिखो_config_byte(pdev, PCI_INTERRUPT_LINE, pdev->irq);

	वापस 0;
पूर्ण

पूर्णांक ssb_gige_map_irq(काष्ठा ssb_device *sdev,
		     स्थिर काष्ठा pci_dev *pdev)
अणु
	काष्ठा ssb_gige *dev = ssb_get_drvdata(sdev);

	अगर (pdev->bus->ops != &dev->pci_ops) अणु
		/* The PCI device is not on this SSB GigE bridge device. */
		वापस -ENODEV;
	पूर्ण

	वापस ssb_mips_irq(sdev) + 2;
पूर्ण

अटल काष्ठा ssb_driver ssb_gige_driver = अणु
	.name		= "BCM-GigE",
	.id_table	= ssb_gige_tbl,
	.probe		= ssb_gige_probe,
पूर्ण;

पूर्णांक ssb_gige_init(व्योम)
अणु
	वापस ssb_driver_रेजिस्टर(&ssb_gige_driver);
पूर्ण
