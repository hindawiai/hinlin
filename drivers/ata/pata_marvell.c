<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	Marvell PATA driver.
 *
 *	For the moment we drive the PATA port in legacy mode. That
 *	isn't making full use of the device functionality but it is
 *	easy to get working.
 *
 *	(c) 2006 Red Hat
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/ata.h>

#घोषणा DRV_NAME	"pata_marvell"
#घोषणा DRV_VERSION	"0.1.6"

/**
 *	marvell_pata_active	-	check अगर PATA is active
 *	@pdev: PCI device
 *
 *	Returns 1 अगर the PATA port may be active. We know how to check this
 *	क्रम the 6145 but not the other devices
 */

अटल पूर्णांक marvell_pata_active(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	u32 devices;
	व्योम __iomem *barp;

	/* We करोn't yet know how to करो this क्रम other devices */
	अगर (pdev->device != 0x6145)
		वापस 1;

	barp = pci_iomap(pdev, 5, 0x10);
	अगर (barp == शून्य)
		वापस -ENOMEM;

	prपूर्णांकk("BAR5:");
	क्रम(i = 0; i <= 0x0F; i++)
		prपूर्णांकk("%02X:%02X ", i, ioपढ़ो8(barp + i));
	prपूर्णांकk("\n");

	devices = ioपढ़ो32(barp + 0x0C);
	pci_iounmap(pdev, barp);

	अगर (devices & 0x10)
		वापस 1;
	वापस 0;
पूर्ण

/**
 *	marvell_pre_reset	-	probe begin
 *	@link: link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm the PATA port setup we need.
 */

अटल पूर्णांक marvell_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (pdev->device == 0x6145 && ap->port_no == 0 &&
		!marvell_pata_active(pdev))	/* PATA enable ? */
			वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल पूर्णांक marvell_cable_detect(काष्ठा ata_port *ap)
अणु
	/* Cable type */
	चयन(ap->port_no)
	अणु
	हाल 0:
		अगर (ioपढ़ो8(ap->ioaddr.bmdma_addr + 1) & 1)
			वापस ATA_CBL_PATA40;
		वापस ATA_CBL_PATA80;
	हाल 1: /* Legacy SATA port */
		वापस ATA_CBL_SATA;
	पूर्ण

	BUG();
	वापस 0;	/* Our BUG macro needs the right markup */
पूर्ण

/* No PIO or DMA methods needed क्रम this device */

अटल काष्ठा scsi_host_ढाँचा marvell_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations marvell_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= marvell_cable_detect,
	.prereset		= marvell_pre_reset,
पूर्ण;


/**
 *	marvell_init_one - Register Marvell ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@id: PCI device ID
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक marvell_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,

		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5,

		.port_ops	= &marvell_ops,
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_sata = अणु
		/* Slave possible as its magically mapped not real */
		.flags		= ATA_FLAG_SLAVE_POSS,

		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA6,

		.port_ops	= &marvell_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &info_sata पूर्ण;

	अगर (pdev->device == 0x6101)
		ppi[1] = &ata_dummy_port_info;

#अगर IS_ENABLED(CONFIG_SATA_AHCI)
	अगर (!marvell_pata_active(pdev)) अणु
		prपूर्णांकk(KERN_INFO DRV_NAME ": PATA port not active, deferring to AHCI driver.\n");
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर
	वापस ata_pci_bmdma_init_one(pdev, ppi, &marvell_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id marvell_pci_tbl[] = अणु
	अणु PCI_DEVICE(0x11AB, 0x6101), पूर्ण,
	अणु PCI_DEVICE(0x11AB, 0x6121), पूर्ण,
	अणु PCI_DEVICE(0x11AB, 0x6123), पूर्ण,
	अणु PCI_DEVICE(0x11AB, 0x6145), पूर्ण,
	अणु PCI_DEVICE(0x1B4B, 0x91A0), पूर्ण,
	अणु PCI_DEVICE(0x1B4B, 0x91A4), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver marvell_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= marvell_pci_tbl,
	.probe			= marvell_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(marvell_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for Marvell ATA in legacy mode");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, marvell_pci_tbl);
MODULE_VERSION(DRV_VERSION);
