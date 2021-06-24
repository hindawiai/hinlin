<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata-cs5530.c 	- CS5530 PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *
 * based upon cs5530.c by Mark Lord.
 *
 * Loosely based on the piix & svwks drivers.
 *
 * Documentation:
 *	Available from AMD web site.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME	"pata_cs5530"
#घोषणा DRV_VERSION	"0.7.4"

अटल व्योम __iomem *cs5530_port_base(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ bmdma = (अचिन्हित दीर्घ)ap->ioaddr.bmdma_addr;

	वापस (व्योम __iomem *)((bmdma & ~0x0F) + 0x20 + 0x10 * ap->port_no);
पूर्ण

/**
 *	cs5530_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Set our PIO requirements. This is fairly simple on the CS5530
 *	chips.
 */

अटल व्योम cs5530_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर अचिन्हित पूर्णांक cs5530_pio_timings[2][5] = अणु
		अणु0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010पूर्ण,
		अणु0xd1329172, 0x71212171, 0x30200080, 0x20102010, 0x00100010पूर्ण
	पूर्ण;
	व्योम __iomem *base = cs5530_port_base(ap);
	u32 tuning;
	पूर्णांक क्रमmat;

	/* Find out which table to use */
	tuning = ioपढ़ो32(base + 0x04);
	क्रमmat = (tuning & 0x80000000UL) ? 1 : 0;

	/* Now load the right timing रेजिस्टर */
	अगर (adev->devno)
		base += 0x08;

	ioग_लिखो32(cs5530_pio_timings[क्रमmat][adev->pio_mode - XFER_PIO_0], base);
पूर्ण

/**
 *	cs5530_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	We cannot mix MWDMA and UDMA without reloading timings each चयन
 *	master to slave. We track the last DMA setup in order to minimise
 *	reloads.
 */

अटल व्योम cs5530_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	व्योम __iomem *base = cs5530_port_base(ap);
	u32 tuning, timing = 0;
	u8 reg;

	/* Find out which table to use */
	tuning = ioपढ़ो32(base + 0x04);

	चयन(adev->dma_mode) अणु
		हाल XFER_UDMA_0:
			timing  = 0x00921250;अवरोध;
		हाल XFER_UDMA_1:
			timing  = 0x00911140;अवरोध;
		हाल XFER_UDMA_2:
			timing  = 0x00911030;अवरोध;
		हाल XFER_MW_DMA_0:
			timing  = 0x00077771;अवरोध;
		हाल XFER_MW_DMA_1:
			timing  = 0x00012121;अवरोध;
		हाल XFER_MW_DMA_2:
			timing  = 0x00002020;अवरोध;
		शेष:
			BUG();
	पूर्ण
	/* Merge in the PIO क्रमmat bit */
	timing |= (tuning & 0x80000000UL);
	अगर (adev->devno == 0) /* Master */
		ioग_लिखो32(timing, base + 0x04);
	अन्यथा अणु
		अगर (timing & 0x00100000)
			tuning |= 0x00100000;	/* UDMA क्रम both */
		अन्यथा
			tuning &= ~0x00100000;	/* MWDMA क्रम both */
		ioग_लिखो32(tuning, base + 0x04);
		ioग_लिखो32(timing, base + 0x0C);
	पूर्ण

	/* Set the DMA capable bit in the BMDMA area */
	reg = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
	reg |= (1 << (5 + adev->devno));
	ioग_लिखो8(reg, ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);

	/* Remember the last DMA setup we did */

	ap->निजी_data = adev;
पूर्ण

/**
 *	cs5530_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary.  Specअगरically we have a problem that there is only
 *	one MWDMA/UDMA bit.
 */

अटल अचिन्हित पूर्णांक cs5530_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा ata_device *prev = ap->निजी_data;

	/* See अगर the DMA settings could be wrong */
	अगर (ata_dma_enabled(adev) && adev != prev && prev != शून्य) अणु
		/* Maybe, but करो the channels match MWDMA/UDMA ? */
		अगर ((ata_using_udma(adev) && !ata_using_udma(prev)) ||
		    (ata_using_udma(prev) && !ata_using_udma(adev)))
		    	/* Switch the mode bits */
		    	cs5530_set_dmamode(ap, adev);
	पूर्ण

	वापस ata_bmdma_qc_issue(qc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cs5530_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.sg_tablesize	= LIBATA_DUMB_MAX_PRD,
पूर्ण;

अटल काष्ठा ata_port_operations cs5530_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.qc_prep 	= ata_bmdma_dumb_qc_prep,
	.qc_issue	= cs5530_qc_issue,

	.cable_detect	= ata_cable_40wire,
	.set_piomode	= cs5530_set_piomode,
	.set_dmamode	= cs5530_set_dmamode,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id palmax_dmi_table[] = अणु
	अणु
		.ident = "Palmax PD1100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Cyrix"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Caddis"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक cs5530_is_palmax(व्योम)
अणु
	अगर (dmi_check_प्रणाली(palmax_dmi_table)) अणु
		prपूर्णांकk(KERN_INFO "Palmax PD1100: Disabling DMA on docking port.\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


/**
 *	cs5530_init_chip	-	Chipset init
 *
 *	Perक्रमm the chip initialisation work that is shared between both
 *	setup and resume paths
 */

अटल पूर्णांक cs5530_init_chip(व्योम)
अणु
	काष्ठा pci_dev *master_0 = शून्य, *cs5530_0 = शून्य, *dev = शून्य;

	जबतक ((dev = pci_get_device(PCI_VENDOR_ID_CYRIX, PCI_ANY_ID, dev)) != शून्य) अणु
		चयन (dev->device) अणु
			हाल PCI_DEVICE_ID_CYRIX_PCI_MASTER:
				master_0 = pci_dev_get(dev);
				अवरोध;
			हाल PCI_DEVICE_ID_CYRIX_5530_LEGACY:
				cs5530_0 = pci_dev_get(dev);
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!master_0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": unable to locate PCI MASTER function\n");
		जाओ fail_put;
	पूर्ण
	अगर (!cs5530_0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": unable to locate CS5530 LEGACY function\n");
		जाओ fail_put;
	पूर्ण

	pci_set_master(cs5530_0);
	pci_try_set_mwi(cs5530_0);

	/*
	 * Set PCI CacheLineSize to 16-bytes:
	 * --> Write 0x04 पूर्णांकo 8-bit PCI CACHELINESIZE reg of function 0 of the cs5530
	 *
	 * Note: This value is स्थिरant because the 5530 is only a Geode companion
	 */

	pci_ग_लिखो_config_byte(cs5530_0, PCI_CACHE_LINE_SIZE, 0x04);

	/*
	 * Disable trapping of UDMA रेजिस्टर accesses (Win98 hack):
	 * --> Write 0x5006 पूर्णांकo 16-bit reg at offset 0xd0 of function 0 of the cs5530
	 */

	pci_ग_लिखो_config_word(cs5530_0, 0xd0, 0x5006);

	/*
	 * Bit-1 at 0x40 enables MemoryWriteAndInvalidate on पूर्णांकernal X-bus:
	 * The other settings are what is necessary to get the रेजिस्टर
	 * पूर्णांकo a sane state क्रम IDE DMA operation.
	 */

	pci_ग_लिखो_config_byte(master_0, 0x40, 0x1e);

	/*
	 * Set max PCI burst size (16-bytes seems to work best):
	 *	   16bytes: set bit-1 at 0x41 (reg value of 0x16)
	 *	all others: clear bit-1 at 0x41, and करो:
	 *	  128bytes: OR 0x00 at 0x41
	 *	  256bytes: OR 0x04 at 0x41
	 *	  512bytes: OR 0x08 at 0x41
	 *	 1024bytes: OR 0x0c at 0x41
	 */

	pci_ग_लिखो_config_byte(master_0, 0x41, 0x14);

	/*
	 * These settings are necessary to get the chip
	 * पूर्णांकo a sane state क्रम IDE DMA operation.
	 */

	pci_ग_लिखो_config_byte(master_0, 0x42, 0x00);
	pci_ग_लिखो_config_byte(master_0, 0x43, 0xc1);

	pci_dev_put(master_0);
	pci_dev_put(cs5530_0);
	वापस 0;
fail_put:
	pci_dev_put(master_0);
	pci_dev_put(cs5530_0);
	वापस -ENODEV;
पूर्ण

/**
 *	cs5530_init_one		-	Initialise a CS5530
 *	@pdev: PCI device
 *	@id: Entry in match table
 *
 *	Install a driver क्रम the newly found CS5530 companion chip. Most of
 *	this is just housekeeping. We have to set the chip up correctly and
 *	turn off various bits of emulation magic.
 */

अटल पूर्णांक cs5530_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.port_ops = &cs5530_port_ops
	पूर्ण;
	/* The करोcking connector करोesn't करो UDMA, and it seems not MWDMA */
	अटल स्थिर काष्ठा ata_port_info info_palmax_secondary = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &cs5530_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	पूर्णांक rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* Chip initialisation */
	अगर (cs5530_init_chip())
		वापस -ENODEV;

	अगर (cs5530_is_palmax())
		ppi[1] = &info_palmax_secondary;

	/* Now kick off ATA set up */
	वापस ata_pci_bmdma_init_one(pdev, ppi, &cs5530_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cs5530_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	/* If we fail on resume we are करोomed */
	अगर (cs5530_init_chip())
		वापस -EIO;

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा pci_device_id cs5530[] = अणु
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5530_IDE), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cs5530_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= cs5530,
	.probe 		= cs5530_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= cs5530_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cs5530_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the Cyrix/NS/AMD 5530");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cs5530);
MODULE_VERSION(DRV_VERSION);
