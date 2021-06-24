<शैली गुरु>
/*
 * pata_sil680.c 	- SIL680 PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *
 * based upon
 *
 * linux/drivers/ide/pci/siimage.c		Version 1.07	Nov 30, 2003
 *
 * Copyright (C) 2001-2002	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2003		Red Hat <alan@redhat.com>
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 *  Documentation खुलाly available.
 *
 *	If you have strange problems with nVidia chipset प्रणालीs please
 *	see the SI support करोcumentation and update your प्रणाली BIOS
 *	अगर necessary
 *
 * TODO
 *	If we know all our devices are LBA28 (or LBA28 sized)  we could use
 *	the command fअगरo mode.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_sil680"
#घोषणा DRV_VERSION "0.4.9"

#घोषणा SIL680_MMIO_BAR		5

/**
 *	sil680_selreg		-	वापस रेजिस्टर base
 *	@ap: ATA पूर्णांकerface
 *	@r: config offset
 *
 *	Turn a config रेजिस्टर offset पूर्णांकo the right address in PCI space
 *	to access the control रेजिस्टर in question.
 *
 *	Thankfully this is a configuration operation so isn't perक्रमmance
 *	criticial.
 */

अटल अचिन्हित दीर्घ sil680_selreg(काष्ठा ata_port *ap, पूर्णांक r)
अणु
	अचिन्हित दीर्घ base = 0xA0 + r;
	base += (ap->port_no << 4);
	वापस base;
पूर्ण

/**
 *	sil680_seldev		-	वापस रेजिस्टर base
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@r: config offset
 *
 *	Turn a config रेजिस्टर offset पूर्णांकo the right address in PCI space
 *	to access the control रेजिस्टर in question including accounting क्रम
 *	the unit shअगरt.
 */

अटल अचिन्हित दीर्घ sil680_seldev(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक r)
अणु
	अचिन्हित दीर्घ base = 0xA0 + r;
	base += (ap->port_no << 4);
	base |= adev->devno ? 2 : 0;
	वापस base;
पूर्ण


/**
 *	sil680_cable_detect	-	cable detection
 *	@ap: ATA port
 *
 *	Perक्रमm cable detection. The SIL680 stores this in PCI config
 *	space क्रम us.
 */

अटल पूर्णांक sil680_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ addr = sil680_selreg(ap, 0);
	u8 ata66;
	pci_पढ़ो_config_byte(pdev, addr, &ata66);
	अगर (ata66 & 1)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	sil680_set_piomode	-	set PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the SIL680 रेजिस्टरs क्रम PIO mode. Note that the task speed
 *	रेजिस्टरs are shared between the devices so we must pick the lowest
 *	mode क्रम command work.
 */

अटल व्योम sil680_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u16 speed_p[5] = अणु
		0x328A, 0x2283, 0x1104, 0x10C3, 0x10C1
	पूर्ण;
	अटल स्थिर u16 speed_t[5] = अणु
		0x328A, 0x2283, 0x1281, 0x10C3, 0x10C1
	पूर्ण;

	अचिन्हित दीर्घ tfaddr = sil680_selreg(ap, 0x02);
	अचिन्हित दीर्घ addr = sil680_seldev(ap, adev, 0x04);
	अचिन्हित दीर्घ addr_mask = 0x80 + 4 * ap->port_no;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक pio = adev->pio_mode - XFER_PIO_0;
	पूर्णांक lowest_pio = pio;
	पूर्णांक port_shअगरt = 4 * adev->devno;
	u16 reg;
	u8 mode;

	काष्ठा ata_device *pair = ata_dev_pair(adev);

	अगर (pair != शून्य && adev->pio_mode > pair->pio_mode)
		lowest_pio = pair->pio_mode - XFER_PIO_0;

	pci_ग_लिखो_config_word(pdev, addr, speed_p[pio]);
	pci_ग_लिखो_config_word(pdev, tfaddr, speed_t[lowest_pio]);

	pci_पढ़ो_config_word(pdev, tfaddr-2, &reg);
	pci_पढ़ो_config_byte(pdev, addr_mask, &mode);

	reg &= ~0x0200;			/* Clear IORDY */
	mode &= ~(3 << port_shअगरt);	/* Clear IORDY and DMA bits */

	अगर (ata_pio_need_iordy(adev)) अणु
		reg |= 0x0200;		/* Enable IORDY */
		mode |= 1 << port_shअगरt;
	पूर्ण
	pci_ग_लिखो_config_word(pdev, tfaddr-2, reg);
	pci_ग_लिखो_config_byte(pdev, addr_mask, mode);
पूर्ण

/**
 *	sil680_set_dmamode	-	set DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the MWDMA/UDMA modes क्रम the sil680 chipset.
 *
 *	The MWDMA mode values are pulled from a lookup table
 *	जबतक the chipset uses mode number क्रम UDMA.
 */

अटल व्योम sil680_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 ultra_table[2][7] = अणु
		अणु 0x0C, 0x07, 0x05, 0x04, 0x02, 0x01, 0xFF पूर्ण,	/* 100MHz */
		अणु 0x0F, 0x0B, 0x07, 0x05, 0x03, 0x02, 0x01 पूर्ण,	/* 133Mhz */
	पूर्ण;
	अटल स्थिर u16 dma_table[3] = अणु 0x2208, 0x10C2, 0x10C1 पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ ma = sil680_seldev(ap, adev, 0x08);
	अचिन्हित दीर्घ ua = sil680_seldev(ap, adev, 0x0C);
	अचिन्हित दीर्घ addr_mask = 0x80 + 4 * ap->port_no;
	पूर्णांक port_shअगरt = adev->devno * 4;
	u8 scsc, mode;
	u16 multi, ultra;

	pci_पढ़ो_config_byte(pdev, 0x8A, &scsc);
	pci_पढ़ो_config_byte(pdev, addr_mask, &mode);
	pci_पढ़ो_config_word(pdev, ma, &multi);
	pci_पढ़ो_config_word(pdev, ua, &ultra);

	/* Mask timing bits */
	ultra &= ~0x3F;
	mode &= ~(0x03 << port_shअगरt);

	/* Extract scsc */
	scsc = (scsc & 0x30) ? 1 : 0;

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		multi = 0x10C1;
		ultra |= ultra_table[scsc][adev->dma_mode - XFER_UDMA_0];
		mode |= (0x03 << port_shअगरt);
	पूर्ण अन्यथा अणु
		multi = dma_table[adev->dma_mode - XFER_MW_DMA_0];
		mode |= (0x02 << port_shअगरt);
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, addr_mask, mode);
	pci_ग_लिखो_config_word(pdev, ma, multi);
	pci_ग_लिखो_config_word(pdev, ua, ultra);
पूर्ण

/**
 *	sil680_sff_exec_command - issue ATA command to host controller
 *	@ap: port to which command is being issued
 *	@tf: ATA taskfile रेजिस्टर set
 *
 *	Issues ATA command, with proper synchronization with पूर्णांकerrupt
 *	handler / other thपढ़ोs. Use our MMIO space क्रम PCI posting to aव्योम
 *	a hideously slow cycle all the way to the device.
 *
 *	LOCKING:
 *	spin_lock_irqsave(host lock)
 */
अटल व्योम sil680_sff_exec_command(काष्ठा ata_port *ap,
				    स्थिर काष्ठा ata_taskfile *tf)
अणु
	DPRINTK("ata%u: cmd 0x%X\n", ap->prपूर्णांक_id, tf->command);
	ioग_लिखो8(tf->command, ap->ioaddr.command_addr);
	ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_CMD);
पूर्ण

अटल bool sil680_sff_irq_check(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ addr	= sil680_selreg(ap, 1);
	u8 val;

	pci_पढ़ो_config_byte(pdev, addr, &val);

	वापस val & 0x08;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sil680_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;


अटल काष्ठा ata_port_operations sil680_port_ops = अणु
	.inherits		= &ata_bmdma32_port_ops,
	.sff_exec_command	= sil680_sff_exec_command,
	.sff_irq_check		= sil680_sff_irq_check,
	.cable_detect		= sil680_cable_detect,
	.set_piomode		= sil680_set_piomode,
	.set_dmamode		= sil680_set_dmamode,
पूर्ण;

/**
 *	sil680_init_chip		-	chip setup
 *	@pdev: PCI device
 *	@try_mmio: Indicates to caller whether MMIO should be attempted
 *
 *	Perक्रमm all the chip setup which must be करोne both when the device
 *	is घातered up on boot and when we resume in हाल we resumed from RAM.
 *	Returns the final घड़ी settings.
 */

अटल u8 sil680_init_chip(काष्ठा pci_dev *pdev, पूर्णांक *try_mmio)
अणु
	u8 पंचांगpbyte	= 0;

	/* FIXME: द्विगुन check */
	pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE,
			      pdev->revision ? 1 : 255);

	pci_ग_लिखो_config_byte(pdev, 0x80, 0x00);
	pci_ग_लिखो_config_byte(pdev, 0x84, 0x00);

	pci_पढ़ो_config_byte(pdev, 0x8A, &पंचांगpbyte);

	dev_dbg(&pdev->dev, "sil680: BA5_EN = %d clock = %02X\n",
		पंचांगpbyte & 1, पंचांगpbyte & 0x30);

	*try_mmio = 0;
#अगर_घोषित CONFIG_PPC
	अगर (machine_is(cell))
		*try_mmio = (पंचांगpbyte & 1) || pci_resource_start(pdev, 5);
#पूर्ण_अगर

	चयन (पंचांगpbyte & 0x30) अणु
	हाल 0x00:
		/* 133 घड़ी attempt to क्रमce it on */
		pci_ग_लिखो_config_byte(pdev, 0x8A, पंचांगpbyte|0x10);
		अवरोध;
	हाल 0x30:
		/* अगर घड़ीing is disabled */
		/* 133 घड़ी attempt to क्रमce it on */
		pci_ग_लिखो_config_byte(pdev, 0x8A, पंचांगpbyte & ~0x20);
		अवरोध;
	हाल 0x10:
		/* 133 alपढ़ोy */
		अवरोध;
	हाल 0x20:
		/* BIOS set PCI x2 घड़ीing */
		अवरोध;
	पूर्ण

	pci_पढ़ो_config_byte(pdev,   0x8A, &पंचांगpbyte);
	dev_dbg(&pdev->dev, "sil680: BA5_EN = %d clock = %02X\n",
		पंचांगpbyte & 1, पंचांगpbyte & 0x30);

	pci_ग_लिखो_config_byte(pdev,  0xA1, 0x72);
	pci_ग_लिखो_config_word(pdev,  0xA2, 0x328A);
	pci_ग_लिखो_config_dword(pdev, 0xA4, 0x62DD62DD);
	pci_ग_लिखो_config_dword(pdev, 0xA8, 0x43924392);
	pci_ग_लिखो_config_dword(pdev, 0xAC, 0x40094009);
	pci_ग_लिखो_config_byte(pdev,  0xB1, 0x72);
	pci_ग_लिखो_config_word(pdev,  0xB2, 0x328A);
	pci_ग_लिखो_config_dword(pdev, 0xB4, 0x62DD62DD);
	pci_ग_लिखो_config_dword(pdev, 0xB8, 0x43924392);
	pci_ग_लिखो_config_dword(pdev, 0xBC, 0x40094009);

	चयन (पंचांगpbyte & 0x30) अणु
	हाल 0x00:
		prपूर्णांकk(KERN_INFO "sil680: 100MHz clock.\n");
		अवरोध;
	हाल 0x10:
		prपूर्णांकk(KERN_INFO "sil680: 133MHz clock.\n");
		अवरोध;
	हाल 0x20:
		prपूर्णांकk(KERN_INFO "sil680: Using PCI clock.\n");
		अवरोध;
	/* This last हाल is _NOT_ ok */
	हाल 0x30:
		prपूर्णांकk(KERN_ERR "sil680: Clock disabled ?\n");
	पूर्ण
	वापस पंचांगpbyte & 0x30;
पूर्ण

अटल पूर्णांक sil680_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &sil680_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_slow = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &sil680_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	काष्ठा ata_host *host;
	व्योम __iomem *mmio_base;
	पूर्णांक rc, try_mmio;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	चयन (sil680_init_chip(pdev, &try_mmio)) अणु
		हाल 0:
			ppi[0] = &info_slow;
			अवरोध;
		हाल 0x30:
			वापस -ENODEV;
	पूर्ण

	अगर (!try_mmio)
		जाओ use_ioports;

	/* Try to acquire MMIO resources and fallback to PIO अगर
	 * that fails
	 */
	rc = pcim_iomap_regions(pdev, 1 << SIL680_MMIO_BAR, DRV_NAME);
	अगर (rc)
		जाओ use_ioports;

	/* Allocate host and set it up */
	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 2);
	अगर (!host)
		वापस -ENOMEM;
	host->iomap = pcim_iomap_table(pdev);

	/* Setup DMA masks */
	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;
	pci_set_master(pdev);

	/* Get MMIO base and initialize port addresses */
	mmio_base = host->iomap[SIL680_MMIO_BAR];
	host->ports[0]->ioaddr.bmdma_addr = mmio_base + 0x00;
	host->ports[0]->ioaddr.cmd_addr = mmio_base + 0x80;
	host->ports[0]->ioaddr.ctl_addr = mmio_base + 0x8a;
	host->ports[0]->ioaddr.altstatus_addr = mmio_base + 0x8a;
	ata_sff_std_ports(&host->ports[0]->ioaddr);
	host->ports[1]->ioaddr.bmdma_addr = mmio_base + 0x08;
	host->ports[1]->ioaddr.cmd_addr = mmio_base + 0xc0;
	host->ports[1]->ioaddr.ctl_addr = mmio_base + 0xca;
	host->ports[1]->ioaddr.altstatus_addr = mmio_base + 0xca;
	ata_sff_std_ports(&host->ports[1]->ioaddr);

	/* Register & activate */
	वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &sil680_sht);

use_ioports:
	वापस ata_pci_bmdma_init_one(pdev, ppi, &sil680_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sil680_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक try_mmio, rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;
	sil680_init_chip(pdev, &try_mmio);
	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id sil680[] = अणु
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_680), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver sil680_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= sil680,
	.probe 		= sil680_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= sil680_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(sil680_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for SI680 PATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sil680);
MODULE_VERSION(DRV_VERSION);
