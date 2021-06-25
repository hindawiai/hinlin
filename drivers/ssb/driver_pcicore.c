<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Broadcom PCI-core driver
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/ssb/ssb_embedded.h>

अटल u32 ssb_pcie_पढ़ो(काष्ठा ssb_pcicore *pc, u32 address);
अटल व्योम ssb_pcie_ग_लिखो(काष्ठा ssb_pcicore *pc, u32 address, u32 data);
अटल u16 ssb_pcie_mdio_पढ़ो(काष्ठा ssb_pcicore *pc, u8 device, u8 address);
अटल व्योम ssb_pcie_mdio_ग_लिखो(काष्ठा ssb_pcicore *pc, u8 device,
				u8 address, u16 data);

अटल अंतरभूत
u32 pcicore_पढ़ो32(काष्ठा ssb_pcicore *pc, u16 offset)
अणु
	वापस ssb_पढ़ो32(pc->dev, offset);
पूर्ण

अटल अंतरभूत
व्योम pcicore_ग_लिखो32(काष्ठा ssb_pcicore *pc, u16 offset, u32 value)
अणु
	ssb_ग_लिखो32(pc->dev, offset, value);
पूर्ण

अटल अंतरभूत
u16 pcicore_पढ़ो16(काष्ठा ssb_pcicore *pc, u16 offset)
अणु
	वापस ssb_पढ़ो16(pc->dev, offset);
पूर्ण

अटल अंतरभूत
व्योम pcicore_ग_लिखो16(काष्ठा ssb_pcicore *pc, u16 offset, u16 value)
अणु
	ssb_ग_लिखो16(pc->dev, offset, value);
पूर्ण

/**************************************************
 * Code क्रम hosपंचांगode operation.
 **************************************************/

#अगर_घोषित CONFIG_SSB_PCICORE_HOSTMODE

#समावेश <यंत्र/paccess.h>
/* Probe a 32bit value on the bus and catch bus exceptions.
 * Returns nonzero on a bus exception.
 * This is MIPS specअगरic */
#घोषणा mips_busprobe32(val, addr)	get_dbe((val), ((u32 *)(addr)))

/* Assume one-hot slot wiring */
#घोषणा SSB_PCI_SLOT_MAX	16

/* Global lock is OK, as we won't have more than one extpci anyway. */
अटल DEFINE_SPINLOCK(cfgspace_lock);
/* Core to access the बाह्यal PCI config space. Can only have one. */
अटल काष्ठा ssb_pcicore *extpci_core;


अटल u32 get_cfgspace_addr(काष्ठा ssb_pcicore *pc,
			     अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक dev,
			     अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक off)
अणु
	u32 addr = 0;
	u32 पंचांगp;

	/* We करो only have one cardbus device behind the bridge. */
	अगर (pc->cardbusmode && (dev > 1))
		जाओ out;

	अगर (bus == 0) अणु
		/* Type 0 transaction */
		अगर (unlikely(dev >= SSB_PCI_SLOT_MAX))
			जाओ out;
		/* Slide the winकरोw */
		पंचांगp = SSB_PCICORE_SBTOPCI_CFG0;
		पंचांगp |= ((1 << (dev + 16)) & SSB_PCICORE_SBTOPCI1_MASK);
		pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI1, पंचांगp);
		/* Calculate the address */
		addr = SSB_PCI_CFG;
		addr |= ((1 << (dev + 16)) & ~SSB_PCICORE_SBTOPCI1_MASK);
		addr |= (func << 8);
		addr |= (off & ~3);
	पूर्ण अन्यथा अणु
		/* Type 1 transaction */
		pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI1,
				SSB_PCICORE_SBTOPCI_CFG1);
		/* Calculate the address */
		addr = SSB_PCI_CFG;
		addr |= (bus << 16);
		addr |= (dev << 11);
		addr |= (func << 8);
		addr |= (off & ~3);
	पूर्ण
out:
	वापस addr;
पूर्ण

अटल पूर्णांक ssb_extpci_पढ़ो_config(काष्ठा ssb_pcicore *pc,
				  अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक dev,
				  अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक off,
				  व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक err = -EINVAL;
	u32 addr, val;
	व्योम __iomem *mmio;

	WARN_ON(!pc->hosपंचांगode);
	अगर (unlikely(len != 1 && len != 2 && len != 4))
		जाओ out;
	addr = get_cfgspace_addr(pc, bus, dev, func, off);
	अगर (unlikely(!addr))
		जाओ out;
	err = -ENOMEM;
	mmio = ioremap(addr, len);
	अगर (!mmio)
		जाओ out;

	अगर (mips_busprobe32(val, mmio)) अणु
		val = 0xffffffff;
		जाओ unmap;
	पूर्ण

	val = पढ़ोl(mmio);
	val >>= (8 * (off & 3));

	चयन (len) अणु
	हाल 1:
		*((u8 *)buf) = (u8)val;
		अवरोध;
	हाल 2:
		*((u16 *)buf) = (u16)val;
		अवरोध;
	हाल 4:
		*((u32 *)buf) = (u32)val;
		अवरोध;
	पूर्ण
	err = 0;
unmap:
	iounmap(mmio);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ssb_extpci_ग_लिखो_config(काष्ठा ssb_pcicore *pc,
				   अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक dev,
				   अचिन्हित पूर्णांक func, अचिन्हित पूर्णांक off,
				   स्थिर व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक err = -EINVAL;
	u32 addr, val = 0;
	व्योम __iomem *mmio;

	WARN_ON(!pc->hosपंचांगode);
	अगर (unlikely(len != 1 && len != 2 && len != 4))
		जाओ out;
	addr = get_cfgspace_addr(pc, bus, dev, func, off);
	अगर (unlikely(!addr))
		जाओ out;
	err = -ENOMEM;
	mmio = ioremap(addr, len);
	अगर (!mmio)
		जाओ out;

	अगर (mips_busprobe32(val, mmio)) अणु
		val = 0xffffffff;
		जाओ unmap;
	पूर्ण

	चयन (len) अणु
	हाल 1:
		val = पढ़ोl(mmio);
		val &= ~(0xFF << (8 * (off & 3)));
		val |= *((स्थिर u8 *)buf) << (8 * (off & 3));
		अवरोध;
	हाल 2:
		val = पढ़ोl(mmio);
		val &= ~(0xFFFF << (8 * (off & 3)));
		val |= *((स्थिर u16 *)buf) << (8 * (off & 3));
		अवरोध;
	हाल 4:
		val = *((स्थिर u32 *)buf);
		अवरोध;
	पूर्ण
	ग_लिखोl(val, mmio);

	err = 0;
unmap:
	iounmap(mmio);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ssb_pcicore_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&cfgspace_lock, flags);
	err = ssb_extpci_पढ़ो_config(extpci_core, bus->number, PCI_SLOT(devfn),
				     PCI_FUNC(devfn), reg, val, size);
	spin_unlock_irqrestore(&cfgspace_lock, flags);

	वापस err ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ssb_pcicore_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&cfgspace_lock, flags);
	err = ssb_extpci_ग_लिखो_config(extpci_core, bus->number, PCI_SLOT(devfn),
				      PCI_FUNC(devfn), reg, &val, size);
	spin_unlock_irqrestore(&cfgspace_lock, flags);

	वापस err ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops ssb_pcicore_pciops = अणु
	.पढ़ो	= ssb_pcicore_पढ़ो_config,
	.ग_लिखो	= ssb_pcicore_ग_लिखो_config,
पूर्ण;

अटल काष्ठा resource ssb_pcicore_mem_resource = अणु
	.name	= "SSB PCIcore external memory",
	.start	= SSB_PCI_DMA,
	.end	= SSB_PCI_DMA + SSB_PCI_DMA_SZ - 1,
	.flags	= IORESOURCE_MEM | IORESOURCE_PCI_FIXED,
पूर्ण;

अटल काष्ठा resource ssb_pcicore_io_resource = अणु
	.name	= "SSB PCIcore external I/O",
	.start	= 0x100,
	.end	= 0x7FF,
	.flags	= IORESOURCE_IO | IORESOURCE_PCI_FIXED,
पूर्ण;

अटल काष्ठा pci_controller ssb_pcicore_controller = अणु
	.pci_ops	= &ssb_pcicore_pciops,
	.io_resource	= &ssb_pcicore_io_resource,
	.mem_resource	= &ssb_pcicore_mem_resource,
पूर्ण;

/* This function is called when करोing a pci_enable_device().
 * We must first check अगर the device is a device on the PCI-core bridge. */
पूर्णांक ssb_pcicore_plat_dev_init(काष्ठा pci_dev *d)
अणु
	अगर (d->bus->ops != &ssb_pcicore_pciops) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस -ENODEV;
	पूर्ण

	dev_info(&d->dev, "PCI: Fixing up device %s\n", pci_name(d));

	/* Fix up पूर्णांकerrupt lines */
	d->irq = ssb_mips_irq(extpci_core->dev) + 2;
	pci_ग_लिखो_config_byte(d, PCI_INTERRUPT_LINE, d->irq);

	वापस 0;
पूर्ण

/* Early PCI fixup क्रम a device on the PCI-core bridge. */
अटल व्योम ssb_pcicore_fixup_pcibridge(काष्ठा pci_dev *dev)
अणु
	u8 lat;

	अगर (dev->bus->ops != &ssb_pcicore_pciops) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस;
	पूर्ण
	अगर (dev->bus->number != 0 || PCI_SLOT(dev->devfn) != 0)
		वापस;

	dev_info(&dev->dev, "PCI: Fixing up bridge %s\n", pci_name(dev));

	/* Enable PCI bridge bus mastering and memory space */
	pci_set_master(dev);
	अगर (pcibios_enable_device(dev, ~0) < 0) अणु
		dev_err(&dev->dev, "PCI: SSB bridge enable failed\n");
		वापस;
	पूर्ण

	/* Enable PCI bridge BAR1 prefetch and burst */
	pci_ग_लिखो_config_dword(dev, SSB_BAR1_CONTROL, 3);

	/* Make sure our latency is high enough to handle the devices behind us */
	lat = 168;
	dev_info(&dev->dev,
		 "PCI: Fixing latency timer of device %s to %u\n",
		 pci_name(dev), lat);
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, lat);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_ANY_ID, PCI_ANY_ID, ssb_pcicore_fixup_pcibridge);

/* PCI device IRQ mapping. */
पूर्णांक ssb_pcicore_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (dev->bus->ops != &ssb_pcicore_pciops) अणु
		/* This is not a device on the PCI-core bridge. */
		वापस -ENODEV;
	पूर्ण
	वापस ssb_mips_irq(extpci_core->dev) + 2;
पूर्ण

अटल व्योम ssb_pcicore_init_hosपंचांगode(काष्ठा ssb_pcicore *pc)
अणु
	u32 val;

	अगर (WARN_ON(extpci_core))
		वापस;
	extpci_core = pc;

	dev_dbg(pc->dev->dev, "PCIcore in host mode found\n");
	/* Reset devices on the बाह्यal PCI bus */
	val = SSB_PCICORE_CTL_RST_OE;
	val |= SSB_PCICORE_CTL_CLK_OE;
	pcicore_ग_लिखो32(pc, SSB_PCICORE_CTL, val);
	val |= SSB_PCICORE_CTL_CLK; /* Clock on */
	pcicore_ग_लिखो32(pc, SSB_PCICORE_CTL, val);
	udelay(150); /* Assertion समय demanded by the PCI standard */
	val |= SSB_PCICORE_CTL_RST; /* Deनिश्चित RST# */
	pcicore_ग_लिखो32(pc, SSB_PCICORE_CTL, val);
	val = SSB_PCICORE_ARBCTL_INTERN;
	pcicore_ग_लिखो32(pc, SSB_PCICORE_ARBCTL, val);
	udelay(1); /* Assertion समय demanded by the PCI standard */

	अगर (pc->dev->bus->has_cardbus_slot) अणु
		dev_dbg(pc->dev->dev, "CardBus slot detected\n");
		pc->cardbusmode = 1;
		/* GPIO 1 resets the bridge */
		ssb_gpio_out(pc->dev->bus, 1, 1);
		ssb_gpio_outen(pc->dev->bus, 1, 1);
		pcicore_ग_लिखो16(pc, SSB_PCICORE_SPROM(0),
				pcicore_पढ़ो16(pc, SSB_PCICORE_SPROM(0))
				| 0x0400);
	पूर्ण

	/* 64MB I/O winकरोw */
	pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI0,
			SSB_PCICORE_SBTOPCI_IO);
	/* 64MB config space */
	pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI1,
			SSB_PCICORE_SBTOPCI_CFG0);
	/* 1GB memory winकरोw */
	pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI2,
			SSB_PCICORE_SBTOPCI_MEM | SSB_PCI_DMA);

	/*
	 * Accessing PCI config without a proper delay after devices reset (not
	 * GPIO reset) was causing reboots on WRT300N v1.0 (BCM4704).
	 * Tested delay 850 us lowered reboot chance to 50-80%, 1000 us fixed it
	 * completely. Flushing all ग_लिखोs was also tested but with no luck.
	 * The same problem was reported क्रम WRT350N v1 (BCM4705), so we just
	 * sleep here unconditionally.
	 */
	usleep_range(1000, 2000);

	/* Enable PCI bridge BAR0 prefetch and burst */
	val = PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
	ssb_extpci_ग_लिखो_config(pc, 0, 0, 0, PCI_COMMAND, &val, 2);
	/* Clear error conditions */
	val = 0;
	ssb_extpci_ग_लिखो_config(pc, 0, 0, 0, PCI_STATUS, &val, 2);

	/* Enable PCI पूर्णांकerrupts */
	pcicore_ग_लिखो32(pc, SSB_PCICORE_IMASK,
			SSB_PCICORE_IMASK_INTA);

	/* Ok, पढ़ोy to run, रेजिस्टर it to the प्रणाली.
	 * The following needs change, अगर we want to port hosपंचांगode
	 * to non-MIPS platक्रमm. */
	ssb_pcicore_controller.io_map_base = (अचिन्हित दीर्घ)ioremap(SSB_PCI_MEM, 0x04000000);
	set_io_port_base(ssb_pcicore_controller.io_map_base);
	/* Give some समय to the PCI controller to configure itself with the new
	 * values. Not रुकोing at this poपूर्णांक causes crashes of the machine. */
	mdelay(10);
	रेजिस्टर_pci_controller(&ssb_pcicore_controller);
पूर्ण

अटल पूर्णांक pcicore_is_in_hosपंचांगode(काष्ठा ssb_pcicore *pc)
अणु
	काष्ठा ssb_bus *bus = pc->dev->bus;
	u16 chipid_top;
	u32 पंचांगp;

	chipid_top = (bus->chip_id & 0xFF00);
	अगर (chipid_top != 0x4700 &&
	    chipid_top != 0x5300)
		वापस 0;

	अगर (bus->sprom.boardflags_lo & SSB_PCICORE_BFL_NOPCI)
		वापस 0;

	/* The 200-pin BCM4712 package करोes not bond out PCI. Even when
	 * PCI is bonded out, some boards may leave the pins भग्नing. */
	अगर (bus->chip_id == 0x4712) अणु
		अगर (bus->chip_package == SSB_CHIPPACK_BCM4712S)
			वापस 0;
		अगर (bus->chip_package == SSB_CHIPPACK_BCM4712M)
			वापस 0;
	पूर्ण
	अगर (bus->chip_id == 0x5350)
		वापस 0;

	वापस !mips_busprobe32(पंचांगp, (bus->mmio + (pc->dev->core_index * SSB_CORE_SIZE)));
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCICORE_HOSTMODE */

/**************************************************
 * Workarounds.
 **************************************************/

अटल व्योम ssb_pcicore_fix_sprom_core_index(काष्ठा ssb_pcicore *pc)
अणु
	u16 पंचांगp = pcicore_पढ़ो16(pc, SSB_PCICORE_SPROM(0));
	अगर (((पंचांगp & 0xF000) >> 12) != pc->dev->core_index) अणु
		पंचांगp &= ~0xF000;
		पंचांगp |= (pc->dev->core_index << 12);
		pcicore_ग_लिखो16(pc, SSB_PCICORE_SPROM(0), पंचांगp);
	पूर्ण
पूर्ण

अटल u8 ssb_pcicore_polarity_workaround(काष्ठा ssb_pcicore *pc)
अणु
	वापस (ssb_pcie_पढ़ो(pc, 0x204) & 0x10) ? 0xC0 : 0x80;
पूर्ण

अटल व्योम ssb_pcicore_serdes_workaround(काष्ठा ssb_pcicore *pc)
अणु
	स्थिर u8 serdes_pll_device = 0x1D;
	स्थिर u8 serdes_rx_device = 0x1F;
	u16 पंचांगp;

	ssb_pcie_mdio_ग_लिखो(pc, serdes_rx_device, 1 /* Control */,
			    ssb_pcicore_polarity_workaround(pc));
	पंचांगp = ssb_pcie_mdio_पढ़ो(pc, serdes_pll_device, 1 /* Control */);
	अगर (पंचांगp & 0x4000)
		ssb_pcie_mdio_ग_लिखो(pc, serdes_pll_device, 1, पंचांगp & ~0x4000);
पूर्ण

अटल व्योम ssb_pcicore_pci_setup_workarounds(काष्ठा ssb_pcicore *pc)
अणु
	काष्ठा ssb_device *pdev = pc->dev;
	काष्ठा ssb_bus *bus = pdev->bus;
	u32 पंचांगp;

	पंचांगp = pcicore_पढ़ो32(pc, SSB_PCICORE_SBTOPCI2);
	पंचांगp |= SSB_PCICORE_SBTOPCI_PREF;
	पंचांगp |= SSB_PCICORE_SBTOPCI_BURST;
	pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI2, पंचांगp);

	अगर (pdev->id.revision < 5) अणु
		पंचांगp = ssb_पढ़ो32(pdev, SSB_IMCFGLO);
		पंचांगp &= ~SSB_IMCFGLO_SERTO;
		पंचांगp |= 2;
		पंचांगp &= ~SSB_IMCFGLO_REQTO;
		पंचांगp |= 3 << SSB_IMCFGLO_REQTO_SHIFT;
		ssb_ग_लिखो32(pdev, SSB_IMCFGLO, पंचांगp);
		ssb_commit_settings(bus);
	पूर्ण अन्यथा अगर (pdev->id.revision >= 11) अणु
		पंचांगp = pcicore_पढ़ो32(pc, SSB_PCICORE_SBTOPCI2);
		पंचांगp |= SSB_PCICORE_SBTOPCI_MRM;
		pcicore_ग_लिखो32(pc, SSB_PCICORE_SBTOPCI2, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम ssb_pcicore_pcie_setup_workarounds(काष्ठा ssb_pcicore *pc)
अणु
	u32 पंचांगp;
	u8 rev = pc->dev->id.revision;

	अगर (rev == 0 || rev == 1) अणु
		/* TLP Workaround रेजिस्टर. */
		पंचांगp = ssb_pcie_पढ़ो(pc, 0x4);
		पंचांगp |= 0x8;
		ssb_pcie_ग_लिखो(pc, 0x4, पंचांगp);
	पूर्ण
	अगर (rev == 1) अणु
		/* DLLP Link Control रेजिस्टर. */
		पंचांगp = ssb_pcie_पढ़ो(pc, 0x100);
		पंचांगp |= 0x40;
		ssb_pcie_ग_लिखो(pc, 0x100, पंचांगp);
	पूर्ण

	अगर (rev == 0) अणु
		स्थिर u8 serdes_rx_device = 0x1F;

		ssb_pcie_mdio_ग_लिखो(pc, serdes_rx_device,
					2 /* Timer */, 0x8128);
		ssb_pcie_mdio_ग_लिखो(pc, serdes_rx_device,
					6 /* CDR */, 0x0100);
		ssb_pcie_mdio_ग_लिखो(pc, serdes_rx_device,
					7 /* CDR BW */, 0x1466);
	पूर्ण अन्यथा अगर (rev == 3 || rev == 4 || rev == 5) अणु
		/* TODO: DLLP Power Management Threshold */
		ssb_pcicore_serdes_workaround(pc);
		/* TODO: ASPM */
	पूर्ण अन्यथा अगर (rev == 7) अणु
		/* TODO: No PLL करोwn */
	पूर्ण

	अगर (rev >= 6) अणु
		/* Miscellaneous Configuration Fixup */
		पंचांगp = pcicore_पढ़ो16(pc, SSB_PCICORE_SPROM(5));
		अगर (!(पंचांगp & 0x8000))
			pcicore_ग_लिखो16(pc, SSB_PCICORE_SPROM(5),
					पंचांगp | 0x8000);
	पूर्ण
पूर्ण

/**************************************************
 * Generic and Clienपंचांगode operation code.
 **************************************************/

अटल व्योम ssb_pcicore_init_clienपंचांगode(काष्ठा ssb_pcicore *pc)
अणु
	काष्ठा ssb_device *pdev = pc->dev;
	काष्ठा ssb_bus *bus = pdev->bus;

	अगर (bus->bustype == SSB_BUSTYPE_PCI)
		ssb_pcicore_fix_sprom_core_index(pc);

	/* Disable PCI पूर्णांकerrupts. */
	ssb_ग_लिखो32(pdev, SSB_INTVEC, 0);

	/* Additional PCIe always once-executed workarounds */
	अगर (pc->dev->id.coreid == SSB_DEV_PCIE) अणु
		ssb_pcicore_serdes_workaround(pc);
		/* TODO: ASPM */
		/* TODO: Clock Request Update */
	पूर्ण
पूर्ण

व्योम ssb_pcicore_init(काष्ठा ssb_pcicore *pc)
अणु
	काष्ठा ssb_device *dev = pc->dev;

	अगर (!dev)
		वापस;
	अगर (!ssb_device_is_enabled(dev))
		ssb_device_enable(dev, 0);

#अगर_घोषित CONFIG_SSB_PCICORE_HOSTMODE
	pc->hosपंचांगode = pcicore_is_in_hosपंचांगode(pc);
	अगर (pc->hosपंचांगode)
		ssb_pcicore_init_hosपंचांगode(pc);
#पूर्ण_अगर /* CONFIG_SSB_PCICORE_HOSTMODE */
	अगर (!pc->hosपंचांगode)
		ssb_pcicore_init_clienपंचांगode(pc);
पूर्ण

अटल u32 ssb_pcie_पढ़ो(काष्ठा ssb_pcicore *pc, u32 address)
अणु
	pcicore_ग_लिखो32(pc, 0x130, address);
	वापस pcicore_पढ़ो32(pc, 0x134);
पूर्ण

अटल व्योम ssb_pcie_ग_लिखो(काष्ठा ssb_pcicore *pc, u32 address, u32 data)
अणु
	pcicore_ग_लिखो32(pc, 0x130, address);
	pcicore_ग_लिखो32(pc, 0x134, data);
पूर्ण

अटल व्योम ssb_pcie_mdio_set_phy(काष्ठा ssb_pcicore *pc, u8 phy)
अणु
	स्थिर u16 mdio_control = 0x128;
	स्थिर u16 mdio_data = 0x12C;
	u32 v;
	पूर्णांक i;

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 28); /* Write Transaction */
	v |= (1 << 17); /* Turnaround */
	v |= (0x1F << 18);
	v |= (phy << 4);
	pcicore_ग_लिखो32(pc, mdio_data, v);

	udelay(10);
	क्रम (i = 0; i < 200; i++) अणु
		v = pcicore_पढ़ो32(pc, mdio_control);
		अगर (v & 0x100 /* Trans complete */)
			अवरोध;
		msleep(1);
	पूर्ण
पूर्ण

अटल u16 ssb_pcie_mdio_पढ़ो(काष्ठा ssb_pcicore *pc, u8 device, u8 address)
अणु
	स्थिर u16 mdio_control = 0x128;
	स्थिर u16 mdio_data = 0x12C;
	पूर्णांक max_retries = 10;
	u16 ret = 0;
	u32 v;
	पूर्णांक i;

	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_ग_लिखो32(pc, mdio_control, v);

	अगर (pc->dev->id.revision >= 10) अणु
		max_retries = 200;
		ssb_pcie_mdio_set_phy(pc, device);
	पूर्ण

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 29); /* Read Transaction */
	v |= (1 << 17); /* Turnaround */
	अगर (pc->dev->id.revision < 10)
		v |= (u32)device << 22;
	v |= (u32)address << 18;
	pcicore_ग_लिखो32(pc, mdio_data, v);
	/* Wait क्रम the device to complete the transaction */
	udelay(10);
	क्रम (i = 0; i < max_retries; i++) अणु
		v = pcicore_पढ़ो32(pc, mdio_control);
		अगर (v & 0x100 /* Trans complete */) अणु
			udelay(10);
			ret = pcicore_पढ़ो32(pc, mdio_data);
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण
	pcicore_ग_लिखो32(pc, mdio_control, 0);
	वापस ret;
पूर्ण

अटल व्योम ssb_pcie_mdio_ग_लिखो(काष्ठा ssb_pcicore *pc, u8 device,
				u8 address, u16 data)
अणु
	स्थिर u16 mdio_control = 0x128;
	स्थिर u16 mdio_data = 0x12C;
	पूर्णांक max_retries = 10;
	u32 v;
	पूर्णांक i;

	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_ग_लिखो32(pc, mdio_control, v);

	अगर (pc->dev->id.revision >= 10) अणु
		max_retries = 200;
		ssb_pcie_mdio_set_phy(pc, device);
	पूर्ण

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 28); /* Write Transaction */
	v |= (1 << 17); /* Turnaround */
	अगर (pc->dev->id.revision < 10)
		v |= (u32)device << 22;
	v |= (u32)address << 18;
	v |= data;
	pcicore_ग_लिखो32(pc, mdio_data, v);
	/* Wait क्रम the device to complete the transaction */
	udelay(10);
	क्रम (i = 0; i < max_retries; i++) अणु
		v = pcicore_पढ़ो32(pc, mdio_control);
		अगर (v & 0x100 /* Trans complete */)
			अवरोध;
		msleep(1);
	पूर्ण
	pcicore_ग_लिखो32(pc, mdio_control, 0);
पूर्ण

पूर्णांक ssb_pcicore_dev_irqvecs_enable(काष्ठा ssb_pcicore *pc,
				   काष्ठा ssb_device *dev)
अणु
	काष्ठा ssb_device *pdev = pc->dev;
	काष्ठा ssb_bus *bus;
	पूर्णांक err = 0;
	u32 पंचांगp;

	अगर (dev->bus->bustype != SSB_BUSTYPE_PCI) अणु
		/* This SSB device is not on a PCI host-bus. So the IRQs are
		 * not routed through the PCI core.
		 * So we must not enable routing through the PCI core. */
		जाओ out;
	पूर्ण

	अगर (!pdev)
		जाओ out;
	bus = pdev->bus;

	might_sleep_अगर(pdev->id.coreid != SSB_DEV_PCI);

	/* Enable पूर्णांकerrupts क्रम this device. */
	अगर ((pdev->id.revision >= 6) || (pdev->id.coreid == SSB_DEV_PCIE)) अणु
		u32 coremask;

		/* Calculate the "coremask" क्रम the device. */
		coremask = (1 << dev->core_index);

		WARN_ON(bus->bustype != SSB_BUSTYPE_PCI);
		err = pci_पढ़ो_config_dword(bus->host_pci, SSB_PCI_IRQMASK, &पंचांगp);
		अगर (err)
			जाओ out;
		पंचांगp |= coremask << 8;
		err = pci_ग_लिखो_config_dword(bus->host_pci, SSB_PCI_IRQMASK, पंचांगp);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		u32 पूर्णांकvec;

		पूर्णांकvec = ssb_पढ़ो32(pdev, SSB_INTVEC);
		पंचांगp = ssb_पढ़ो32(dev, SSB_TPSFLAG);
		पंचांगp &= SSB_TPSFLAG_BPFLAG;
		पूर्णांकvec |= (1 << पंचांगp);
		ssb_ग_लिखो32(pdev, SSB_INTVEC, पूर्णांकvec);
	पूर्ण

	/* Setup PCIcore operation. */
	अगर (pc->setup_करोne)
		जाओ out;
	अगर (pdev->id.coreid == SSB_DEV_PCI) अणु
		ssb_pcicore_pci_setup_workarounds(pc);
	पूर्ण अन्यथा अणु
		WARN_ON(pdev->id.coreid != SSB_DEV_PCIE);
		ssb_pcicore_pcie_setup_workarounds(pc);
	पूर्ण
	pc->setup_करोne = 1;
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(ssb_pcicore_dev_irqvecs_enable);
