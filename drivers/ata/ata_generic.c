<शैली गुरु>
/*
 *  ata_generic.c - Generic PATA/SATA controller driver.
 *  Copyright 2005 Red Hat Inc, all rights reserved.
 *
 *  Elements from ide/pci/generic.c
 *	    Copyright (C) 2001-2002	Andre Hedrick <andre@linux-ide.org>
 *	    Portions (C) Copyright 2002  Red Hat Inc <alan@redhat.com>
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 *  Driver क्रम PCI IDE पूर्णांकerfaces implementing the standard bus mastering
 *  पूर्णांकerface functionality. This assumes the BIOS did the drive set up and
 *  tuning क्रम us. By शेष we करो not grab all IDE class devices as they
 *  may have other drivers or need fixups to aव्योम problems. Instead we keep
 *  a शेष list of stuff without करोcumentation/driver that appears to
 *  work.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "ata_generic"
#घोषणा DRV_VERSION "0.2.15"

/*
 *	A generic parallel ATA driver using libata
 */

क्रमागत अणु
	ATA_GEN_CLASS_MATCH		= (1 << 0),
	ATA_GEN_FORCE_DMA		= (1 << 1),
	ATA_GEN_INTEL_IDER		= (1 << 2),
पूर्ण;

/**
 *	generic_set_mode	-	mode setting
 *	@link: link to set up
 *	@unused: वापसed device on error
 *
 *	Use a non standard set_mode function. We करोn't want to be tuned.
 *	The BIOS configured everything. Our job is not to fiddle. We
 *	पढ़ो the dma enabled bits from the PCI configuration of the device
 *	and respect them.
 */

अटल पूर्णांक generic_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **unused)
अणु
	काष्ठा ata_port *ap = link->ap;
	स्थिर काष्ठा pci_device_id *id = ap->host->निजी_data;
	पूर्णांक dma_enabled = 0;
	काष्ठा ata_device *dev;

	अगर (id->driver_data & ATA_GEN_FORCE_DMA) अणु
		dma_enabled = 0xff;
	पूर्ण अन्यथा अगर (ap->ioaddr.bmdma_addr) अणु
		/* Bits 5 and 6 indicate अगर DMA is active on master/slave */
		dma_enabled = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
	पूर्ण

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		/* We करोn't really care */
		dev->pio_mode = XFER_PIO_0;
		dev->dma_mode = XFER_MW_DMA_0;
		/* We करो need the right mode inक्रमmation क्रम DMA or PIO
		   and this comes from the current configuration flags */
		अगर (dma_enabled & (1 << (5 + dev->devno))) अणु
			अचिन्हित पूर्णांक xfer_mask = ata_id_xfermask(dev->id);
			स्थिर अक्षर *name;

			अगर (xfer_mask & (ATA_MASK_MWDMA | ATA_MASK_UDMA))
				name = ata_mode_string(xfer_mask);
			अन्यथा अणु
				/* SWDMA perhaps? */
				name = "DMA";
				xfer_mask |= ata_xfer_mode2mask(XFER_MW_DMA_0);
			पूर्ण

			ata_dev_info(dev, "configured for %s\n", name);

			dev->xfer_mode = ata_xfer_mask2mode(xfer_mask);
			dev->xfer_shअगरt = ata_xfer_mode2shअगरt(dev->xfer_mode);
			dev->flags &= ~ATA_DFLAG_PIO;
		पूर्ण अन्यथा अणु
			ata_dev_info(dev, "configured for PIO\n");
			dev->xfer_mode = XFER_PIO_0;
			dev->xfer_shअगरt = ATA_SHIFT_PIO;
			dev->flags |= ATA_DFLAG_PIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा generic_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations generic_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_unknown,
	.set_mode	= generic_set_mode,
पूर्ण;

अटल पूर्णांक all_generic_ide;		/* Set to claim all devices */

/**
 *	is_पूर्णांकel_ider		-	identअगरy पूर्णांकel IDE-R devices
 *	@dev: PCI device
 *
 *	Distinguish Intel IDE-R controller devices from other Intel IDE
 *	devices. IDE-R devices have no timing रेजिस्टरs and are in
 *	most respects भव. They should be driven by the ata_generic
 *	driver.
 *
 *	IDE-R devices have PCI offset 0xF8.L as zero, later Intel ATA has
 *	it non zero. All Intel ATA has 0x40 writable (timing), but it is
 *	not writable on IDE-R devices (this is guaranteed).
 */

अटल पूर्णांक is_पूर्णांकel_ider(काष्ठा pci_dev *dev)
अणु
	/* For Intel IDE the value at 0xF8 is only zero on IDE-R
	   पूर्णांकerfaces */
	u32 r;
	u16 t;

	/* Check the manufacturing ID, it will be zero क्रम IDE-R */
	pci_पढ़ो_config_dword(dev, 0xF8, &r);
	/* Not IDE-R: punt so that ata_(old)piix माला_लो it */
	अगर (r != 0)
		वापस 0;
	/* 0xF8 will also be zero on some early Intel IDE devices
	   but they will have a sane timing रेजिस्टर */
	pci_पढ़ो_config_word(dev, 0x40, &t);
	अगर (t != 0)
		वापस 0;
	/* Finally check अगर the timing रेजिस्टर is writable so that
	   we eliminate any early devices hot-करोcked in a करोcking
	   station */
	pci_ग_लिखो_config_word(dev, 0x40, 1);
	pci_पढ़ो_config_word(dev, 0x40, &t);
	अगर (t) अणु
		pci_ग_लिखो_config_word(dev, 0x40, 0);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	ata_generic_init_one		-	attach generic IDE
 *	@dev: PCI device found
 *	@id: match entry
 *
 *	Called each समय a matching IDE पूर्णांकerface is found. We check अगर the
 *	पूर्णांकerface is one we wish to claim and अगर so we perक्रमm any chip
 *	specअगरic hacks then let the ATA layer करो the heavy lअगरting.
 */

अटल पूर्णांक ata_generic_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	u16 command;
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &generic_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	/* Don't use the generic entry unless inकाष्ठाed to करो so */
	अगर ((id->driver_data & ATA_GEN_CLASS_MATCH) && all_generic_ide == 0)
		वापस -ENODEV;

	अगर ((id->driver_data & ATA_GEN_INTEL_IDER) && !all_generic_ide)
		अगर (!is_पूर्णांकel_ider(dev))
			वापस -ENODEV;

	/* Devices that need care */
	अगर (dev->venकरोr == PCI_VENDOR_ID_UMC &&
	    dev->device == PCI_DEVICE_ID_UMC_UM8886A &&
	    (!(PCI_FUNC(dev->devfn) & 1)))
		वापस -ENODEV;

	अगर (dev->venकरोr == PCI_VENDOR_ID_OPTI &&
	    dev->device == PCI_DEVICE_ID_OPTI_82C558 &&
	    (!(PCI_FUNC(dev->devfn) & 1)))
		वापस -ENODEV;

	/* Don't re-enable devices in generic mode or we will अवरोध some
	   motherboards with disabled and unused IDE controllers */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &command);
	अगर (!(command & PCI_COMMAND_IO))
		वापस -ENODEV;

	अगर (dev->venकरोr == PCI_VENDOR_ID_AL)
		ata_pci_bmdma_clear_simplex(dev);

	अगर (dev->venकरोr == PCI_VENDOR_ID_ATI) अणु
		पूर्णांक rc = pcim_enable_device(dev);
		अगर (rc < 0)
			वापस rc;
		pcim_pin_device(dev);
	पूर्ण
	वापस ata_pci_bmdma_init_one(dev, ppi, &generic_sht, (व्योम *)id, 0);
पूर्ण

अटल काष्ठा pci_device_id ata_generic[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_PCTECH, PCI_DEVICE_ID_PCTECH_SAMURAI_IDE), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HOLTEK, PCI_DEVICE_ID_HOLTEK_6565), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_UMC,    PCI_DEVICE_ID_UMC_UM8673F), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_UMC,    PCI_DEVICE_ID_UMC_UM8886A), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_UMC,    PCI_DEVICE_ID_UMC_UM8886BF), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HINT,   PCI_DEVICE_ID_HINT_VXPROII_IDE), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA,    PCI_DEVICE_ID_VIA_82C561), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_OPTI,   PCI_DEVICE_ID_OPTI_82C558), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CENATEK,PCI_DEVICE_ID_CENATEK_IDE),
	  .driver_data = ATA_GEN_FORCE_DMA पूर्ण,
#अगर !defined(CONFIG_PATA_TOSHIBA) && !defined(CONFIG_PATA_TOSHIBA_MODULE)
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_1), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_2),  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_3),  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_5),  पूर्ण,
#पूर्ण_अगर
	/* Intel, IDE class device */
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_IDE << 8, 0xFFFFFF00UL,
	  .driver_data = ATA_GEN_INTEL_IDER पूर्ण,
	/* Must come last. If you add entries adjust this table appropriately */
	अणु PCI_DEVICE_CLASS(PCI_CLASS_STORAGE_IDE << 8, 0xFFFFFF00UL),
	  .driver_data = ATA_GEN_CLASS_MATCH पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ata_generic_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= ata_generic,
	.probe 		= ata_generic_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(ata_generic_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for generic ATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ata_generic);
MODULE_VERSION(DRV_VERSION);

module_param(all_generic_ide, पूर्णांक, 0);
