<शैली गुरु>
/*
 * Copyright (C) 2001-2002	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2003		Red Hat
 * Copyright (C) 2007-2008	MontaVista Software, Inc.
 * Copyright (C) 2007-2008	Bartlomiej Zolnierkiewicz
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 *  Documentation क्रम CMD680:
 *  http://gkernel.sourceक्रमge.net/specs/sii/sii-0680a-v1.31.pdf.bz2
 *
 *  Documentation क्रम SiI 3112:
 *  http://gkernel.sourceक्रमge.net/specs/sii/3112A_SiI-DS-0095-B2.pdf.bz2
 *
 *  Errata and other करोcumentation only available under NDA.
 *
 *
 *  FAQ Items:
 *	If you are using Marvell SATA-IDE adapters with Maxtor drives
 *	ensure the प्रणाली is set up क्रम ATA100/UDMA5, not UDMA6.
 *
 *	If you are using WD drives with SATA bridges you must set the
 *	drive to "Single". "Master" will hang.
 *
 *	If you have strange problems with nVidia chipset प्रणालीs please
 *	see the SI support करोcumentation and update your प्रणाली BIOS
 *	अगर necessary
 *
 *  The Dell DRAC4 has some पूर्णांकeresting features including effectively hot
 *  unplugging/replugging the भव CD पूर्णांकerface when the DRAC is reset.
 *  This often causes drivers/ide/siimage to panic but is ok with the rather
 *  smarter code in libata.
 *
 * TODO:
 * - VDMA support
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#घोषणा DRV_NAME "siimage"

/**
 *	pdev_is_sata		-	check अगर device is SATA
 *	@pdev:	PCI device to check
 *
 *	Returns true अगर this is a SATA controller
 */

अटल पूर्णांक pdev_is_sata(काष्ठा pci_dev *pdev)
अणु
#अगर_घोषित CONFIG_BLK_DEV_IDE_SATA
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_SII_3112:
	हाल PCI_DEVICE_ID_SII_1210SA:
		वापस 1;
	हाल PCI_DEVICE_ID_SII_680:
		वापस 0;
	पूर्ण
	BUG();
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 *	is_sata			-	check अगर hwअगर is SATA
 *	@hwअगर:	पूर्णांकerface to check
 *
 *	Returns true अगर this is a SATA controller
 */

अटल अंतरभूत पूर्णांक is_sata(ide_hwअगर_t *hwअगर)
अणु
	वापस pdev_is_sata(to_pci_dev(hwअगर->dev));
पूर्ण

/**
 *	siimage_selreg		-	वापस रेजिस्टर base
 *	@hwअगर: पूर्णांकerface
 *	@r: config offset
 *
 *	Turn a config रेजिस्टर offset पूर्णांकo the right address in either
 *	PCI space or MMIO space to access the control रेजिस्टर in question
 *	Thankfully this is a configuration operation, so isn't perक्रमmance
 *	critical.
 */

अटल अचिन्हित दीर्घ siimage_selreg(ide_hwअगर_t *hwअगर, पूर्णांक r)
अणु
	अचिन्हित दीर्घ base = (अचिन्हित दीर्घ)hwअगर->hwअगर_data;

	base += 0xA0 + r;
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		base += hwअगर->channel << 6;
	अन्यथा
		base += hwअगर->channel << 4;
	वापस base;
पूर्ण

/**
 *	siimage_seldev		-	वापस रेजिस्टर base
 *	@hwअगर: पूर्णांकerface
 *	@r: config offset
 *
 *	Turn a config रेजिस्टर offset पूर्णांकo the right address in either
 *	PCI space or MMIO space to access the control रेजिस्टर in question
 *	including accounting क्रम the unit shअगरt.
 */

अटल अंतरभूत अचिन्हित दीर्घ siimage_seldev(ide_drive_t *drive, पूर्णांक r)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	अचिन्हित दीर्घ base	= (अचिन्हित दीर्घ)hwअगर->hwअगर_data;
	u8 unit			= drive->dn & 1;

	base += 0xA0 + r;
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		base += hwअगर->channel << 6;
	अन्यथा
		base += hwअगर->channel << 4;
	base |= unit << unit;
	वापस base;
पूर्ण

अटल u8 sil_ioपढ़ो8(काष्ठा pci_dev *dev, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	u8 पंचांगp = 0;

	अगर (host->host_priv)
		पंचांगp = पढ़ोb((व्योम __iomem *)addr);
	अन्यथा
		pci_पढ़ो_config_byte(dev, addr, &पंचांगp);

	वापस पंचांगp;
पूर्ण

अटल u16 sil_ioपढ़ो16(काष्ठा pci_dev *dev, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	u16 पंचांगp = 0;

	अगर (host->host_priv)
		पंचांगp = पढ़ोw((व्योम __iomem *)addr);
	अन्यथा
		pci_पढ़ो_config_word(dev, addr, &पंचांगp);

	वापस पंचांगp;
पूर्ण

अटल व्योम sil_ioग_लिखो8(काष्ठा pci_dev *dev, u8 val, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);

	अगर (host->host_priv)
		ग_लिखोb(val, (व्योम __iomem *)addr);
	अन्यथा
		pci_ग_लिखो_config_byte(dev, addr, val);
पूर्ण

अटल व्योम sil_ioग_लिखो16(काष्ठा pci_dev *dev, u16 val, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);

	अगर (host->host_priv)
		ग_लिखोw(val, (व्योम __iomem *)addr);
	अन्यथा
		pci_ग_लिखो_config_word(dev, addr, val);
पूर्ण

अटल व्योम sil_ioग_लिखो32(काष्ठा pci_dev *dev, u32 val, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);

	अगर (host->host_priv)
		ग_लिखोl(val, (व्योम __iomem *)addr);
	अन्यथा
		pci_ग_लिखो_config_dword(dev, addr, val);
पूर्ण

/**
 *	sil_udma_filter		-	compute UDMA mask
 *	@drive: IDE device
 *
 *	Compute the available UDMA speeds क्रम the device on the पूर्णांकerface.
 *
 *	For the CMD680 this depends on the घड़ीing mode (scsc), क्रम the
 *	SI3112 SATA controller lअगरe is a bit simpler.
 */

अटल u8 sil_pata_udma_filter(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ base	= (अचिन्हित दीर्घ)hwअगर->hwअगर_data;
	u8 scsc, mask		= 0;

	base += (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 0x4A : 0x8A;

	scsc = sil_ioपढ़ो8(dev, base);

	चयन (scsc & 0x30) अणु
	हाल 0x10:	/* 133 */
		mask = ATA_UDMA6;
		अवरोध;
	हाल 0x20:	/* 2xPCI */
		mask = ATA_UDMA6;
		अवरोध;
	हाल 0x00:	/* 100 */
		mask = ATA_UDMA5;
		अवरोध;
	शेष: 	/* Disabled ? */
		BUG();
	पूर्ण

	वापस mask;
पूर्ण

अटल u8 sil_sata_udma_filter(ide_drive_t *drive)
अणु
	अक्षर *m = (अक्षर *)&drive->id[ATA_ID_PROD];

	वापस म_माला(m, "Maxtor") ? ATA_UDMA5 : ATA_UDMA6;
पूर्ण

/**
 *	sil_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Load the timing settings क्रम this device mode पूर्णांकo the
 *	controller.
 */

अटल व्योम sil_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल स्थिर u16 tf_speed[]   = अणु 0x328a, 0x2283, 0x1281, 0x10c3, 0x10c1 पूर्ण;
	अटल स्थिर u16 data_speed[] = अणु 0x328a, 0x2283, 0x1104, 0x10c3, 0x10c1 पूर्ण;

	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	ide_drive_t *pair	= ide_get_pair_dev(drive);
	u32 speedt		= 0;
	u16 speedp		= 0;
	अचिन्हित दीर्घ addr	= siimage_seldev(drive, 0x04);
	अचिन्हित दीर्घ tfaddr	= siimage_selreg(hwअगर,	0x02);
	अचिन्हित दीर्घ base	= (अचिन्हित दीर्घ)hwअगर->hwअगर_data;
	स्थिर u8 pio		= drive->pio_mode - XFER_PIO_0;
	u8 tf_pio		= pio;
	u8 mmio			= (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;
	u8 addr_mask		= hwअगर->channel ? (mmio ? 0xF4 : 0x84)
						: (mmio ? 0xB4 : 0x80);
	u8 mode			= 0;
	u8 unit			= drive->dn & 1;

	/* trim *taskfile* PIO to the slowest of the master/slave */
	अगर (pair) अणु
		u8 pair_pio = pair->pio_mode - XFER_PIO_0;

		अगर (pair_pio < tf_pio)
			tf_pio = pair_pio;
	पूर्ण

	/* cheat क्रम now and use the करोcs */
	speedp = data_speed[pio];
	speedt = tf_speed[tf_pio];

	sil_ioग_लिखो16(dev, speedp, addr);
	sil_ioग_लिखो16(dev, speedt, tfaddr);

	/* now set up IORDY */
	speedp = sil_ioपढ़ो16(dev, tfaddr - 2);
	speedp &= ~0x200;

	mode = sil_ioपढ़ो8(dev, base + addr_mask);
	mode &= ~(unit ? 0x30 : 0x03);

	अगर (ide_pio_need_iordy(drive, pio)) अणु
		speedp |= 0x200;
		mode |= unit ? 0x10 : 0x01;
	पूर्ण

	sil_ioग_लिखो16(dev, speedp, tfaddr - 2);
	sil_ioग_लिखो8(dev, mode, base + addr_mask);
पूर्ण

/**
 *	sil_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Tune the SiI chipset क्रम the desired DMA mode.
 */

अटल व्योम sil_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल स्थिर u8 ultra6[] = अणु 0x0F, 0x0B, 0x07, 0x05, 0x03, 0x02, 0x01 पूर्ण;
	अटल स्थिर u8 ultra5[] = अणु 0x0C, 0x07, 0x05, 0x04, 0x02, 0x01 पूर्ण;
	अटल स्थिर u16 dma[]	 = अणु 0x2208, 0x10C2, 0x10C1 पूर्ण;

	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ base	= (अचिन्हित दीर्घ)hwअगर->hwअगर_data;
	u16 ultra = 0, multi	= 0;
	u8 mode = 0, unit	= drive->dn & 1;
	u8 mmio			= (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;
	u8 scsc = 0, addr_mask	= hwअगर->channel ? (mmio ? 0xF4 : 0x84)
						: (mmio ? 0xB4 : 0x80);
	अचिन्हित दीर्घ ma	= siimage_seldev(drive, 0x08);
	अचिन्हित दीर्घ ua	= siimage_seldev(drive, 0x0C);
	स्थिर u8 speed		= drive->dma_mode;

	scsc  = sil_ioपढ़ो8 (dev, base + (mmio ? 0x4A : 0x8A));
	mode  = sil_ioपढ़ो8 (dev, base + addr_mask);
	multi = sil_ioपढ़ो16(dev, ma);
	ultra = sil_ioपढ़ो16(dev, ua);

	mode  &= ~(unit ? 0x30 : 0x03);
	ultra &= ~0x3F;
	scsc = ((scsc & 0x30) == 0x00) ? 0 : 1;

	scsc = is_sata(hwअगर) ? 1 : scsc;

	अगर (speed >= XFER_UDMA_0) अणु
		multi  = dma[2];
		ultra |= scsc ? ultra6[speed - XFER_UDMA_0] :
				ultra5[speed - XFER_UDMA_0];
		mode  |= unit ? 0x30 : 0x03;
	पूर्ण अन्यथा अणु
		multi = dma[speed - XFER_MW_DMA_0];
		mode |= unit ? 0x20 : 0x02;
	पूर्ण

	sil_ioग_लिखो8 (dev, mode, base + addr_mask);
	sil_ioग_लिखो16(dev, multi, ma);
	sil_ioग_लिखो16(dev, ultra, ua);
पूर्ण

अटल पूर्णांक sil_test_irq(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ addr	= siimage_selreg(hwअगर, 1);
	u8 val			= sil_ioपढ़ो8(dev, addr);

	/* Return 1 अगर INTRQ निश्चितed */
	वापस (val & 8) ? 1 : 0;
पूर्ण

/**
 *	siimage_mmio_dma_test_irq	-	check we caused an IRQ
 *	@drive: drive we are testing
 *
 *	Check अगर we caused an IDE DMA पूर्णांकerrupt. We may also have caused
 *	SATA status पूर्णांकerrupts, अगर so we clean them up and जारी.
 */

अटल पूर्णांक siimage_mmio_dma_test_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	व्योम __iomem *sata_error_addr
		= (व्योम __iomem *)hwअगर->sata_scr[SATA_ERROR_OFFSET];

	अगर (sata_error_addr) अणु
		अचिन्हित दीर्घ base	= (अचिन्हित दीर्घ)hwअगर->hwअगर_data;
		u32 ext_stat		= पढ़ोl((व्योम __iomem *)(base + 0x10));
		u8 watchकरोg		= 0;

		अगर (ext_stat & ((hwअगर->channel) ? 0x40 : 0x10)) अणु
			u32 sata_error = पढ़ोl(sata_error_addr);

			ग_लिखोl(sata_error, sata_error_addr);
			watchकरोg = (sata_error & 0x00680000) ? 1 : 0;
			prपूर्णांकk(KERN_WARNING "%s: sata_error = 0x%08x, "
				"watchdog = %d, %s\n",
				drive->name, sata_error, watchकरोg, __func__);
		पूर्ण अन्यथा
			watchकरोg = (ext_stat & 0x8000) ? 1 : 0;

		ext_stat >>= 16;
		अगर (!(ext_stat & 0x0404) && !watchकरोg)
			वापस 0;
	पूर्ण

	/* वापस 1 अगर INTR निश्चितed */
	अगर (पढ़ोb((व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_STATUS)) & 4)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक siimage_dma_test_irq(ide_drive_t *drive)
अणु
	अगर (drive->hwअगर->host_flags & IDE_HFLAG_MMIO)
		वापस siimage_mmio_dma_test_irq(drive);
	अन्यथा
		वापस ide_dma_test_irq(drive);
पूर्ण

/**
 *	sil_sata_reset_poll	-	रुको क्रम SATA reset
 *	@drive: drive we are resetting
 *
 *	Poll the SATA phy and see whether it has come back from the dead
 *	yet.
 */

अटल blk_status_t sil_sata_reset_poll(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	व्योम __iomem *sata_status_addr
		= (व्योम __iomem *)hwअगर->sata_scr[SATA_STATUS_OFFSET];

	अगर (sata_status_addr) अणु
		/* SATA Status is available only when in MMIO mode */
		u32 sata_stat = पढ़ोl(sata_status_addr);

		अगर ((sata_stat & 0x03) != 0x03) अणु
			prपूर्णांकk(KERN_WARNING "%s: reset phy dead, status=0x%08x\n",
					    hwअगर->name, sata_stat);
			वापस BLK_STS_IOERR;
		पूर्ण
	पूर्ण

	वापस BLK_STS_OK;
पूर्ण

/**
 *	sil_sata_pre_reset	-	reset hook
 *	@drive: IDE device being reset
 *
 *	For the SATA devices we need to handle recalibration/geometry
 *	dअगरferently
 */

अटल व्योम sil_sata_pre_reset(ide_drive_t *drive)
अणु
	अगर (drive->media == ide_disk) अणु
		drive->special_flags &=
			~(IDE_SFLAG_SET_GEOMETRY | IDE_SFLAG_RECALIBRATE);
	पूर्ण
पूर्ण

/**
 *	init_chipset_siimage	-	set up an SI device
 *	@dev: PCI device
 *
 *	Perक्रमm the initial PCI set up क्रम this device. Attempt to चयन
 *	to 133 MHz घड़ीing अगर the प्रणाली isn't alपढ़ोy set up to करो it.
 */

अटल पूर्णांक init_chipset_siimage(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	व्योम __iomem *ioaddr = host->host_priv;
	अचिन्हित दीर्घ base, scsc_addr;
	u8 rev = dev->revision, पंचांगp;

	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, rev ? 1 : 255);

	अगर (ioaddr)
		pci_set_master(dev);

	base = (अचिन्हित दीर्घ)ioaddr;

	अगर (ioaddr && pdev_is_sata(dev)) अणु
		u32 पंचांगp32, irq_mask;

		/* make sure IDE0/1 पूर्णांकerrupts are not masked */
		irq_mask = (1 << 22) | (1 << 23);
		पंचांगp32 = पढ़ोl(ioaddr + 0x48);
		अगर (पंचांगp32 & irq_mask) अणु
			पंचांगp32 &= ~irq_mask;
			ग_लिखोl(पंचांगp32, ioaddr + 0x48);
			पढ़ोl(ioaddr + 0x48); /* flush */
		पूर्ण
		ग_लिखोl(0, ioaddr + 0x148);
		ग_लिखोl(0, ioaddr + 0x1C8);
	पूर्ण

	sil_ioग_लिखो8(dev, 0, base ? (base + 0xB4) : 0x80);
	sil_ioग_लिखो8(dev, 0, base ? (base + 0xF4) : 0x84);

	scsc_addr = base ? (base + 0x4A) : 0x8A;
	पंचांगp = sil_ioपढ़ो8(dev, scsc_addr);

	चयन (पंचांगp & 0x30) अणु
	हाल 0x00:
		/* On 100 MHz घड़ीing, try and चयन to 133 MHz */
		sil_ioग_लिखो8(dev, पंचांगp | 0x10, scsc_addr);
		अवरोध;
	हाल 0x30:
		/* Clocking is disabled, attempt to क्रमce 133MHz घड़ीing. */
		sil_ioग_लिखो8(dev, पंचांगp & ~0x20, scsc_addr);
	हाल 0x10:
		/* On 133Mhz घड़ीing. */
		अवरोध;
	हाल 0x20:
		/* On PCIx2 घड़ीing. */
		अवरोध;
	पूर्ण

	पंचांगp = sil_ioपढ़ो8(dev, scsc_addr);

	sil_ioग_लिखो8 (dev,       0x72, base + 0xA1);
	sil_ioग_लिखो16(dev,     0x328A, base + 0xA2);
	sil_ioग_लिखो32(dev, 0x62DD62DD, base + 0xA4);
	sil_ioग_लिखो32(dev, 0x43924392, base + 0xA8);
	sil_ioग_लिखो32(dev, 0x40094009, base + 0xAC);
	sil_ioग_लिखो8 (dev,       0x72, base ? (base + 0xE1) : 0xB1);
	sil_ioग_लिखो16(dev,     0x328A, base ? (base + 0xE2) : 0xB2);
	sil_ioग_लिखो32(dev, 0x62DD62DD, base ? (base + 0xE4) : 0xB4);
	sil_ioग_लिखो32(dev, 0x43924392, base ? (base + 0xE8) : 0xB8);
	sil_ioग_लिखो32(dev, 0x40094009, base ? (base + 0xEC) : 0xBC);

	अगर (base && pdev_is_sata(dev)) अणु
		ग_लिखोl(0xFFFF0000, ioaddr + 0x108);
		ग_लिखोl(0xFFFF0000, ioaddr + 0x188);
		ग_लिखोl(0x00680000, ioaddr + 0x148);
		ग_लिखोl(0x00680000, ioaddr + 0x1C8);
	पूर्ण

	/* report the घड़ीing mode of the controller */
	अगर (!pdev_is_sata(dev)) अणु
		अटल स्थिर अक्षर *clk_str[] =
			अणु "== 100", "== 133", "== 2X PCI", "DISABLED!" पूर्ण;

		पंचांगp >>= 4;
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: BASE CLOCK %s\n",
			pci_name(dev), clk_str[पंचांगp & 3]);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	init_mmio_iops_siimage	-	set up the iops क्रम MMIO
 *	@hwअगर: पूर्णांकerface to set up
 *
 *	The basic setup here is fairly simple, we can use standard MMIO
 *	operations. However we करो have to set the taskfile रेजिस्टर offsets
 *	by hand as there isn't a standard defined layout क्रम them this समय.
 *
 *	The hardware supports buffered taskfiles and also some rather nice
 *	extended PRD tables. For better SI3112 support use the libata driver
 */

अटल व्योम init_mmio_iops_siimage(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	काष्ठा ide_host *host	= pci_get_drvdata(dev);
	व्योम *addr		= host->host_priv;
	u8 ch			= hwअगर->channel;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	अचिन्हित दीर्घ base;

	/*
	 *	Fill in the basic hwअगर bits
	 */
	hwअगर->host_flags |= IDE_HFLAG_MMIO;

	hwअगर->hwअगर_data	= addr;

	/*
	 *	Now set up the hw. We have to करो this ourselves as the
	 *	MMIO layout isn't the same as the standard port based I/O.
	 */
	स_रखो(io_ports, 0, माप(*io_ports));

	base = (अचिन्हित दीर्घ)addr;
	अगर (ch)
		base += 0xC0;
	अन्यथा
		base += 0x80;

	/*
	 *	The buffered task file करोesn't have status/control, so we
	 *	can't currently use it sanely since we want to use LBA48 mode.
	 */
	io_ports->data_addr	= base;
	io_ports->error_addr	= base + 1;
	io_ports->nsect_addr	= base + 2;
	io_ports->lbal_addr	= base + 3;
	io_ports->lbam_addr	= base + 4;
	io_ports->lbah_addr	= base + 5;
	io_ports->device_addr	= base + 6;
	io_ports->status_addr	= base + 7;
	io_ports->ctl_addr	= base + 10;

	अगर (pdev_is_sata(dev)) अणु
		base = (अचिन्हित दीर्घ)addr;
		अगर (ch)
			base += 0x80;
		hwअगर->sata_scr[SATA_STATUS_OFFSET]	= base + 0x104;
		hwअगर->sata_scr[SATA_ERROR_OFFSET]	= base + 0x108;
		hwअगर->sata_scr[SATA_CONTROL_OFFSET]	= base + 0x100;
	पूर्ण

	hwअगर->irq = dev->irq;

	hwअगर->dma_base = (अचिन्हित दीर्घ)addr + (ch ? 0x08 : 0x00);
पूर्ण

अटल पूर्णांक is_dev_seagate_sata(ide_drive_t *drive)
अणु
	स्थिर अक्षर *s	= (स्थिर अक्षर *)&drive->id[ATA_ID_PROD];
	अचिन्हित len	= strnlen(s, ATA_ID_PROD_LEN);

	अगर ((len > 4) && (!स_भेद(s, "ST", 2)))
		अगर ((!स_भेद(s + len - 2, "AS", 2)) ||
		    (!स_भेद(s + len - 3, "ASL", 3))) अणु
			prपूर्णांकk(KERN_INFO "%s: applying pessimistic Seagate "
					 "errata fix\n", drive->name);
			वापस 1;
		पूर्ण

	वापस 0;
पूर्ण

/**
 *	sil_quirkproc		-	post probe fixups
 *	@drive: drive
 *
 *	Called after drive probe we use this to decide whether the
 *	Seagate fixup must be applied. This used to be in init_iops but
 *	that can occur beक्रमe we know what drives are present.
 */

अटल व्योम sil_quirkproc(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	/* Try and rise the rqsize */
	अगर (!is_sata(hwअगर) || !is_dev_seagate_sata(drive))
		hwअगर->rqsize = 128;
पूर्ण

/**
 *	init_iops_siimage	-	set up iops
 *	@hwअगर: पूर्णांकerface to set up
 *
 *	Do the basic setup क्रम the SIIMAGE hardware पूर्णांकerface
 *	and then करो the MMIO setup अगर we can. This is the first
 *	look in we get क्रम setting up the hwअगर so that we
 *	can get the iops right beक्रमe using them.
 */

अटल व्योम init_iops_siimage(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा ide_host *host = dev_get_drvdata(hwअगर->dev);

	hwअगर->hwअगर_data = शून्य;

	/* Pessimal until we finish probing */
	hwअगर->rqsize = 15;

	अगर (host->host_priv)
		init_mmio_iops_siimage(hwअगर);
पूर्ण

/**
 *	sil_cable_detect	-	cable detection
 *	@hwअगर: पूर्णांकerface to check
 *
 *	Check क्रम the presence of an ATA66 capable cable on the पूर्णांकerface.
 */

अटल u8 sil_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ addr	= siimage_selreg(hwअगर, 0);
	u8 ata66		= sil_ioपढ़ो8(dev, addr);

	वापस (ata66 & 0x01) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops sil_pata_port_ops = अणु
	.set_pio_mode		= sil_set_pio_mode,
	.set_dma_mode		= sil_set_dma_mode,
	.quirkproc		= sil_quirkproc,
	.test_irq		= sil_test_irq,
	.udma_filter		= sil_pata_udma_filter,
	.cable_detect		= sil_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops sil_sata_port_ops = अणु
	.set_pio_mode		= sil_set_pio_mode,
	.set_dma_mode		= sil_set_dma_mode,
	.reset_poll		= sil_sata_reset_poll,
	.pre_reset		= sil_sata_pre_reset,
	.quirkproc		= sil_quirkproc,
	.test_irq		= sil_test_irq,
	.udma_filter		= sil_sata_udma_filter,
	.cable_detect		= sil_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops sil_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= ide_dma_end,
	.dma_test_irq		= siimage_dma_test_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

#घोषणा DECLARE_SII_DEV(p_ops)				\
	अणु						\
		.name		= DRV_NAME,		\
		.init_chipset	= init_chipset_siimage,	\
		.init_iops	= init_iops_siimage,	\
		.port_ops	= p_ops,		\
		.dma_ops	= &sil_dma_ops,		\
		.pio_mask	= ATA_PIO4,		\
		.mwdma_mask	= ATA_MWDMA2,		\
		.udma_mask	= ATA_UDMA6,		\
	पूर्ण

अटल स्थिर काष्ठा ide_port_info siimage_chipsets[] = अणु
	/* 0: SiI680 */  DECLARE_SII_DEV(&sil_pata_port_ops),
	/* 1: SiI3112 */ DECLARE_SII_DEV(&sil_sata_port_ops)
पूर्ण;

/**
 *	siimage_init_one	-	PCI layer discovery entry
 *	@dev: PCI device
 *	@id: ident table entry
 *
 *	Called by the PCI code when it finds an SiI680 or SiI3112 controller.
 *	We then use the IDE PCI generic helper to करो most of the work.
 */

अटल पूर्णांक siimage_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	व्योम __iomem *ioaddr = शून्य;
	resource_माप_प्रकार bar5 = pci_resource_start(dev, 5);
	अचिन्हित दीर्घ barsize = pci_resource_len(dev, 5);
	पूर्णांक rc;
	काष्ठा ide_port_info d;
	u8 idx = id->driver_data;
	u8 BA5_EN;

	d = siimage_chipsets[idx];

	अगर (idx) अणु
		अटल पूर्णांक first = 1;

		अगर (first) अणु
			prपूर्णांकk(KERN_INFO DRV_NAME ": For full SATA support you "
				"should use the libata sata_sil module.\n");
			first = 0;
		पूर्ण

		d.host_flags |= IDE_HFLAG_NO_ATAPI_DMA;
	पूर्ण

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	pci_पढ़ो_config_byte(dev, 0x8A, &BA5_EN);
	अगर ((BA5_EN & 0x01) || bar5) अणु
		/*
		* Drop back to PIO अगर we can't map the MMIO. Some प्रणालीs
		* seem to get terminally confused in the PCI spaces.
		*/
		अगर (!request_mem_region(bar5, barsize, d.name)) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME " %s: MMIO ports not "
				"available\n", pci_name(dev));
		पूर्ण अन्यथा अणु
			ioaddr = pci_ioremap_bar(dev, 5);
			अगर (ioaddr == शून्य)
				release_mem_region(bar5, barsize);
		पूर्ण
	पूर्ण

	rc = ide_pci_init_one(dev, &d, ioaddr);
	अगर (rc) अणु
		अगर (ioaddr) अणु
			iounmap(ioaddr);
			release_mem_region(bar5, barsize);
		पूर्ण
		pci_disable_device(dev);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम siimage_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	व्योम __iomem *ioaddr = host->host_priv;

	ide_pci_हटाओ(dev);

	अगर (ioaddr) अणु
		resource_माप_प्रकार bar5 = pci_resource_start(dev, 5);
		अचिन्हित दीर्घ barsize = pci_resource_len(dev, 5);

		iounmap(ioaddr);
		release_mem_region(bar5, barsize);
	पूर्ण

	pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id siimage_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_680),    0 पूर्ण,
#अगर_घोषित CONFIG_BLK_DEV_IDE_SATA
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_3112),   1 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_1210SA), 1 पूर्ण,
#पूर्ण_अगर
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, siimage_pci_tbl);

अटल काष्ठा pci_driver siimage_pci_driver = अणु
	.name		= "SiI_IDE",
	.id_table	= siimage_pci_tbl,
	.probe		= siimage_init_one,
	.हटाओ		= siimage_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init siimage_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&siimage_pci_driver);
पूर्ण

अटल व्योम __निकास siimage_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&siimage_pci_driver);
पूर्ण

module_init(siimage_ide_init);
module_निकास(siimage_ide_निकास);

MODULE_AUTHOR("Andre Hedrick, Alan Cox");
MODULE_DESCRIPTION("PCI driver module for SiI IDE");
MODULE_LICENSE("GPL");
