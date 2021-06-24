<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Bus scanning
 *
 * Copyright (C) 2005-2007 Michael Buesch <m@bues.ch>
 * Copyright (C) 2005 Martin Langer <martin-langer@gmx.de>
 * Copyright (C) 2005 Stefano Brivio <st3@riseup.net>
 * Copyright (C) 2005 Danny van Dyk <kugelfang@gentoo.org>
 * Copyright (C) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>
 * Copyright (C) 2006 Broadcom Corporation.
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_regs.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>


स्थिर अक्षर *ssb_core_name(u16 coreid)
अणु
	चयन (coreid) अणु
	हाल SSB_DEV_CHIPCOMMON:
		वापस "ChipCommon";
	हाल SSB_DEV_ILINE20:
		वापस "ILine 20";
	हाल SSB_DEV_SDRAM:
		वापस "SDRAM";
	हाल SSB_DEV_PCI:
		वापस "PCI";
	हाल SSB_DEV_MIPS:
		वापस "MIPS";
	हाल SSB_DEV_ETHERNET:
		वापस "Fast Ethernet";
	हाल SSB_DEV_V90:
		वापस "V90";
	हाल SSB_DEV_USB11_HOSTDEV:
		वापस "USB 1.1 Hostdev";
	हाल SSB_DEV_ADSL:
		वापस "ADSL";
	हाल SSB_DEV_ILINE100:
		वापस "ILine 100";
	हाल SSB_DEV_IPSEC:
		वापस "IPSEC";
	हाल SSB_DEV_PCMCIA:
		वापस "PCMCIA";
	हाल SSB_DEV_INTERNAL_MEM:
		वापस "Internal Memory";
	हाल SSB_DEV_MEMC_SDRAM:
		वापस "MEMC SDRAM";
	हाल SSB_DEV_EXTIF:
		वापस "EXTIF";
	हाल SSB_DEV_80211:
		वापस "IEEE 802.11";
	हाल SSB_DEV_MIPS_3302:
		वापस "MIPS 3302";
	हाल SSB_DEV_USB11_HOST:
		वापस "USB 1.1 Host";
	हाल SSB_DEV_USB11_DEV:
		वापस "USB 1.1 Device";
	हाल SSB_DEV_USB20_HOST:
		वापस "USB 2.0 Host";
	हाल SSB_DEV_USB20_DEV:
		वापस "USB 2.0 Device";
	हाल SSB_DEV_SDIO_HOST:
		वापस "SDIO Host";
	हाल SSB_DEV_ROBOSWITCH:
		वापस "Roboswitch";
	हाल SSB_DEV_PARA_ATA:
		वापस "PATA";
	हाल SSB_DEV_SATA_XORDMA:
		वापस "SATA XOR-DMA";
	हाल SSB_DEV_ETHERNET_GBIT:
		वापस "GBit Ethernet";
	हाल SSB_DEV_PCIE:
		वापस "PCI-E";
	हाल SSB_DEV_MIMO_PHY:
		वापस "MIMO PHY";
	हाल SSB_DEV_SRAM_CTRLR:
		वापस "SRAM Controller";
	हाल SSB_DEV_MINI_MACPHY:
		वापस "Mini MACPHY";
	हाल SSB_DEV_ARM_1176:
		वापस "ARM 1176";
	हाल SSB_DEV_ARM_7TDMI:
		वापस "ARM 7TDMI";
	हाल SSB_DEV_ARM_CM3:
		वापस "ARM Cortex M3";
	पूर्ण
	वापस "UNKNOWN";
पूर्ण

अटल u16 pcidev_to_chipid(काष्ठा pci_dev *pci_dev)
अणु
	u16 chipid_fallback = 0;

	चयन (pci_dev->device) अणु
	हाल 0x4301:
		chipid_fallback = 0x4301;
		अवरोध;
	हाल 0x4305 ... 0x4307:
		chipid_fallback = 0x4307;
		अवरोध;
	हाल 0x4403:
		chipid_fallback = 0x4402;
		अवरोध;
	हाल 0x4610 ... 0x4615:
		chipid_fallback = 0x4610;
		अवरोध;
	हाल 0x4710 ... 0x4715:
		chipid_fallback = 0x4710;
		अवरोध;
	हाल 0x4320 ... 0x4325:
		chipid_fallback = 0x4309;
		अवरोध;
	हाल PCI_DEVICE_ID_BCM4401:
	हाल PCI_DEVICE_ID_BCM4401B0:
	हाल PCI_DEVICE_ID_BCM4401B1:
		chipid_fallback = 0x4401;
		अवरोध;
	शेष:
		dev_err(&pci_dev->dev, "PCI-ID not in fallback list\n");
	पूर्ण

	वापस chipid_fallback;
पूर्ण

अटल u8 chipid_to_nrcores(u16 chipid)
अणु
	चयन (chipid) अणु
	हाल 0x5365:
		वापस 7;
	हाल 0x4306:
		वापस 6;
	हाल 0x4310:
		वापस 8;
	हाल 0x4307:
	हाल 0x4301:
		वापस 5;
	हाल 0x4401:
	हाल 0x4402:
		वापस 3;
	हाल 0x4710:
	हाल 0x4610:
	हाल 0x4704:
		वापस 9;
	शेष:
		pr_err("CHIPID not in nrcores fallback list\n");
	पूर्ण

	वापस 1;
पूर्ण

अटल u32 scan_पढ़ो32(काष्ठा ssb_bus *bus, u8 current_coreidx,
		       u16 offset)
अणु
	u32 lo, hi;

	चयन (bus->bustype) अणु
	हाल SSB_BUSTYPE_SSB:
		offset += current_coreidx * SSB_CORE_SIZE;
		अवरोध;
	हाल SSB_BUSTYPE_PCI:
		अवरोध;
	हाल SSB_BUSTYPE_PCMCIA:
		अगर (offset >= 0x800) अणु
			ssb_pcmcia_चयन_segment(bus, 1);
			offset -= 0x800;
		पूर्ण अन्यथा
			ssb_pcmcia_चयन_segment(bus, 0);
		lo = पढ़ोw(bus->mmio + offset);
		hi = पढ़ोw(bus->mmio + offset + 2);
		वापस lo | (hi << 16);
	हाल SSB_BUSTYPE_SDIO:
		offset += current_coreidx * SSB_CORE_SIZE;
		वापस ssb_sdio_scan_पढ़ो32(bus, offset);
	पूर्ण
	वापस पढ़ोl(bus->mmio + offset);
पूर्ण

अटल पूर्णांक scan_चयनcore(काष्ठा ssb_bus *bus, u8 coreidx)
अणु
	चयन (bus->bustype) अणु
	हाल SSB_BUSTYPE_SSB:
		अवरोध;
	हाल SSB_BUSTYPE_PCI:
		वापस ssb_pci_चयन_coreidx(bus, coreidx);
	हाल SSB_BUSTYPE_PCMCIA:
		वापस ssb_pcmcia_चयन_coreidx(bus, coreidx);
	हाल SSB_BUSTYPE_SDIO:
		वापस ssb_sdio_scan_चयन_coreidx(bus, coreidx);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ssb_iounmap(काष्ठा ssb_bus *bus)
अणु
	चयन (bus->bustype) अणु
	हाल SSB_BUSTYPE_SSB:
	हाल SSB_BUSTYPE_PCMCIA:
		iounmap(bus->mmio);
		अवरोध;
	हाल SSB_BUSTYPE_PCI:
#अगर_घोषित CONFIG_SSB_PCIHOST
		pci_iounmap(bus->host_pci, bus->mmio);
#अन्यथा
		WARN_ON(1); /* Can't reach this code. */
#पूर्ण_अगर
		अवरोध;
	हाल SSB_BUSTYPE_SDIO:
		अवरोध;
	पूर्ण
	bus->mmio = शून्य;
	bus->mapped_device = शून्य;
पूर्ण

अटल व्योम __iomem *ssb_ioremap(काष्ठा ssb_bus *bus,
				 अचिन्हित दीर्घ baseaddr)
अणु
	व्योम __iomem *mmio = शून्य;

	चयन (bus->bustype) अणु
	हाल SSB_BUSTYPE_SSB:
		/* Only map the first core क्रम now. */
		fallthrough;
	हाल SSB_BUSTYPE_PCMCIA:
		mmio = ioremap(baseaddr, SSB_CORE_SIZE);
		अवरोध;
	हाल SSB_BUSTYPE_PCI:
#अगर_घोषित CONFIG_SSB_PCIHOST
		mmio = pci_iomap(bus->host_pci, 0, ~0UL);
#अन्यथा
		WARN_ON(1); /* Can't reach this code. */
#पूर्ण_अगर
		अवरोध;
	हाल SSB_BUSTYPE_SDIO:
		/* Nothing to ioremap in the SDIO हाल, just fake it */
		mmio = (व्योम __iomem *)baseaddr;
		अवरोध;
	पूर्ण

	वापस mmio;
पूर्ण

अटल पूर्णांक we_support_multiple_80211_cores(काष्ठा ssb_bus *bus)
अणु
	/* More than one 802.11 core is only supported by special chips.
	 * There are chips with two 802.11 cores, but with dangling
	 * pins on the second core. Be careful and reject them here.
	 */

#अगर_घोषित CONFIG_SSB_PCIHOST
	अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
		अगर (bus->host_pci->venकरोr == PCI_VENDOR_ID_BROADCOM &&
		    ((bus->host_pci->device == 0x4313) ||
		     (bus->host_pci->device == 0x431A) ||
		     (bus->host_pci->device == 0x4321) ||
		     (bus->host_pci->device == 0x4324)))
			वापस 1;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */
	वापस 0;
पूर्ण

पूर्णांक ssb_bus_scan(काष्ठा ssb_bus *bus,
		 अचिन्हित दीर्घ baseaddr)
अणु
	पूर्णांक err = -ENOMEM;
	व्योम __iomem *mmio;
	u32 idhi, cc, rev, पंचांगp;
	पूर्णांक dev_i, i;
	काष्ठा ssb_device *dev;
	पूर्णांक nr_80211_cores = 0;

	mmio = ssb_ioremap(bus, baseaddr);
	अगर (!mmio)
		जाओ out;
	bus->mmio = mmio;

	err = scan_चयनcore(bus, 0); /* Switch to first core */
	अगर (err)
		जाओ err_unmap;

	idhi = scan_पढ़ो32(bus, 0, SSB_IDHIGH);
	cc = (idhi & SSB_IDHIGH_CC) >> SSB_IDHIGH_CC_SHIFT;
	rev = (idhi & SSB_IDHIGH_RCLO);
	rev |= (idhi & SSB_IDHIGH_RCHI) >> SSB_IDHIGH_RCHI_SHIFT;

	bus->nr_devices = 0;
	अगर (cc == SSB_DEV_CHIPCOMMON) अणु
		पंचांगp = scan_पढ़ो32(bus, 0, SSB_CHIPCO_CHIPID);

		bus->chip_id = (पंचांगp & SSB_CHIPCO_IDMASK);
		bus->chip_rev = (पंचांगp & SSB_CHIPCO_REVMASK) >>
				SSB_CHIPCO_REVSHIFT;
		bus->chip_package = (पंचांगp & SSB_CHIPCO_PACKMASK) >>
				    SSB_CHIPCO_PACKSHIFT;
		अगर (rev >= 4) अणु
			bus->nr_devices = (पंचांगp & SSB_CHIPCO_NRCORESMASK) >>
					  SSB_CHIPCO_NRCORESSHIFT;
		पूर्ण
		पंचांगp = scan_पढ़ो32(bus, 0, SSB_CHIPCO_CAP);
		bus->chipco.capabilities = पंचांगp;
	पूर्ण अन्यथा अणु
		अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
			bus->chip_id = pcidev_to_chipid(bus->host_pci);
			bus->chip_rev = bus->host_pci->revision;
			bus->chip_package = 0;
		पूर्ण अन्यथा अणु
			bus->chip_id = 0x4710;
			bus->chip_rev = 0;
			bus->chip_package = 0;
		पूर्ण
	पूर्ण
	pr_info("Found chip with id 0x%04X, rev 0x%02X and package 0x%02X\n",
		bus->chip_id, bus->chip_rev, bus->chip_package);
	अगर (!bus->nr_devices)
		bus->nr_devices = chipid_to_nrcores(bus->chip_id);
	अगर (bus->nr_devices > ARRAY_SIZE(bus->devices)) अणु
		pr_err("More than %d ssb cores found (%d)\n",
		       SSB_MAX_NR_CORES, bus->nr_devices);
		जाओ err_unmap;
	पूर्ण
	अगर (bus->bustype == SSB_BUSTYPE_SSB) अणु
		/* Now that we know the number of cores,
		 * remap the whole IO space क्रम all cores.
		 */
		err = -ENOMEM;
		iounmap(mmio);
		mmio = ioremap(baseaddr, SSB_CORE_SIZE * bus->nr_devices);
		अगर (!mmio)
			जाओ out;
		bus->mmio = mmio;
	पूर्ण

	/* Fetch basic inक्रमmation about each core/device */
	क्रम (i = 0, dev_i = 0; i < bus->nr_devices; i++) अणु
		err = scan_चयनcore(bus, i);
		अगर (err)
			जाओ err_unmap;
		dev = &(bus->devices[dev_i]);

		idhi = scan_पढ़ो32(bus, i, SSB_IDHIGH);
		dev->id.coreid = (idhi & SSB_IDHIGH_CC) >> SSB_IDHIGH_CC_SHIFT;
		dev->id.revision = (idhi & SSB_IDHIGH_RCLO);
		dev->id.revision |= (idhi & SSB_IDHIGH_RCHI) >> SSB_IDHIGH_RCHI_SHIFT;
		dev->id.venकरोr = (idhi & SSB_IDHIGH_VC) >> SSB_IDHIGH_VC_SHIFT;
		dev->core_index = i;
		dev->bus = bus;
		dev->ops = bus->ops;

		pr_debug("Core %d found: %s (cc 0x%03X, rev 0x%02X, vendor 0x%04X)\n",
			 i, ssb_core_name(dev->id.coreid),
			 dev->id.coreid, dev->id.revision, dev->id.venकरोr);

		चयन (dev->id.coreid) अणु
		हाल SSB_DEV_80211:
			nr_80211_cores++;
			अगर (nr_80211_cores > 1) अणु
				अगर (!we_support_multiple_80211_cores(bus)) अणु
					pr_debug("Ignoring additional 802.11 core\n");
					जारी;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल SSB_DEV_EXTIF:
#अगर_घोषित CONFIG_SSB_DRIVER_EXTIF
			अगर (bus->extअगर.dev) अणु
				pr_warn("WARNING: Multiple EXTIFs found\n");
				अवरोध;
			पूर्ण
			bus->extअगर.dev = dev;
#पूर्ण_अगर /* CONFIG_SSB_DRIVER_EXTIF */
			अवरोध;
		हाल SSB_DEV_CHIPCOMMON:
			अगर (bus->chipco.dev) अणु
				pr_warn("WARNING: Multiple ChipCommon found\n");
				अवरोध;
			पूर्ण
			bus->chipco.dev = dev;
			अवरोध;
		हाल SSB_DEV_MIPS:
		हाल SSB_DEV_MIPS_3302:
#अगर_घोषित CONFIG_SSB_DRIVER_MIPS
			अगर (bus->mipscore.dev) अणु
				pr_warn("WARNING: Multiple MIPS cores found\n");
				अवरोध;
			पूर्ण
			bus->mipscore.dev = dev;
#पूर्ण_अगर /* CONFIG_SSB_DRIVER_MIPS */
			अवरोध;
		हाल SSB_DEV_PCI:
		हाल SSB_DEV_PCIE:
#अगर_घोषित CONFIG_SSB_DRIVER_PCICORE
			अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
				/* Ignore PCI cores on PCI-E cards.
				 * Ignore PCI-E cores on PCI cards.
				 */
				अगर (dev->id.coreid == SSB_DEV_PCI) अणु
					अगर (pci_is_pcie(bus->host_pci))
						जारी;
				पूर्ण अन्यथा अणु
					अगर (!pci_is_pcie(bus->host_pci))
						जारी;
				पूर्ण
			पूर्ण
			अगर (bus->pcicore.dev) अणु
				pr_warn("WARNING: Multiple PCI(E) cores found\n");
				अवरोध;
			पूर्ण
			bus->pcicore.dev = dev;
#पूर्ण_अगर /* CONFIG_SSB_DRIVER_PCICORE */
			अवरोध;
		हाल SSB_DEV_ETHERNET:
			अगर (bus->bustype == SSB_BUSTYPE_PCI) अणु
				अगर (bus->host_pci->venकरोr == PCI_VENDOR_ID_BROADCOM &&
				    (bus->host_pci->device & 0xFF00) == 0x4300) अणु
					/* This is a dangling ethernet core on a
					 * wireless device. Ignore it.
					 */
					जारी;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		dev_i++;
	पूर्ण
	bus->nr_devices = dev_i;

	err = 0;
out:
	वापस err;
err_unmap:
	ssb_iounmap(bus);
	जाओ out;
पूर्ण
