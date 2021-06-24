<शैली गुरु>
/*
 *  pata_piccolo.c - Toshiba Piccolo PATA/SATA controller driver.
 *
 *  This is basically an update to ata_generic.c to add Toshiba Piccolo support
 *  then split out to keep ata_generic "clean".
 *
 *  Copyright 2005 Red Hat Inc, all rights reserved.
 *
 *  Elements from ide/pci/generic.c
 *	    Copyright (C) 2001-2002	Andre Hedrick <andre@linux-ide.org>
 *	    Portions (C) Copyright 2002  Red Hat Inc <alan@redhat.com>
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 *
 *  The timing data tables/programming info are courtesy of the NetBSD driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_piccolo"
#घोषणा DRV_VERSION "0.0.1"



अटल व्योम tosh_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u16 pio[6] = अणु	/* For reg 0x50 low word & E088 */
		0x0566, 0x0433, 0x0311, 0x0201, 0x0200, 0x0100
	पूर्ण;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 conf;
	pci_पढ़ो_config_word(pdev, 0x50, &conf);
	conf &= 0xE088;
	conf |= pio[adev->pio_mode - XFER_PIO_0];
	pci_ग_लिखो_config_word(pdev, 0x50, conf);
पूर्ण

अटल व्योम tosh_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 conf;
	pci_पढ़ो_config_dword(pdev, 0x5C, &conf);
	conf &= 0x78FFE088;	/* Keep the other bits */
	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		पूर्णांक udma = adev->dma_mode - XFER_UDMA_0;
		conf |= 0x80000000;
		conf |= (udma + 2) << 28;
		conf |= (2 - udma) * 0x111;	/* spपढ़ो पूर्णांकo three nibbles */
	पूर्ण अन्यथा अणु
		अटल स्थिर u32 mwdma[4] = अणु
			0x0655, 0x0200, 0x0200, 0x0100
		पूर्ण;
		conf |= mwdma[adev->dma_mode - XFER_MW_DMA_0];
	पूर्ण
	pci_ग_लिखो_config_dword(pdev, 0x5C, conf);
पूर्ण


अटल काष्ठा scsi_host_ढाँचा tosh_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations tosh_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_unknown,
	.set_piomode	= tosh_set_piomode,
	.set_dmamode	= tosh_set_dmamode
पूर्ण;

/**
 *	ata_tosh_init_one		-	attach generic IDE
 *	@dev: PCI device found
 *	@id: match entry
 *
 *	Called each समय a matching IDE पूर्णांकerface is found. We check अगर the
 *	पूर्णांकerface is one we wish to claim and अगर so we perक्रमm any chip
 *	specअगरic hacks then let the ATA layer करो the heavy lअगरting.
 */

अटल पूर्णांक ata_tosh_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO5,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.port_ops = &tosh_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &ata_dummy_port_info पूर्ण;
	/* Just one port क्रम the moment */
	वापस ata_pci_bmdma_init_one(dev, ppi, &tosh_sht, शून्य, 0);
पूर्ण

अटल काष्ठा pci_device_id ata_tosh[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_1), पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_2),  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_3),  पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOLO_5),  पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ata_tosh_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= ata_tosh,
	.probe 		= ata_tosh_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(ata_tosh_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("Low level driver for Toshiba Piccolo ATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ata_tosh);
MODULE_VERSION(DRV_VERSION);
