<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  RZ1000/1001 driver based upon
 *
 *  linux/drivers/ide/pci/rz1000.c	Version 0.06	January 12, 2003
 *  Copyright (C) 1995-1998  Linus Torvalds & author (see below)
 *  Principal Author:  mlord@pobox.com (Mark Lord)
 *
 *  See linux/MAINTAINERS क्रम address of current मुख्यtainer.
 *
 *  This file provides support क्रम disabling the buggy पढ़ो-ahead
 *  mode of the RZ1000 IDE chipset, commonly used on Intel motherboards.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_rz1000"
#घोषणा DRV_VERSION	"0.2.4"


/**
 *	rz1000_set_mode		-	mode setting function
 *	@link: ATA link
 *	@unused: वापसed device on set_mode failure
 *
 *	Use a non standard set_mode function. We करोn't want to be tuned. We
 *	would prefer to be BIOS generic but क्रम the fact our hardware is
 *	whacked out.
 */

अटल पूर्णांक rz1000_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **unused)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		/* We करोn't really care */
		dev->pio_mode = XFER_PIO_0;
		dev->xfer_mode = XFER_PIO_0;
		dev->xfer_shअगरt = ATA_SHIFT_PIO;
		dev->flags |= ATA_DFLAG_PIO;
		ata_dev_info(dev, "configured for PIO\n");
	पूर्ण
	वापस 0;
पूर्ण


अटल काष्ठा scsi_host_ढाँचा rz1000_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations rz1000_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_mode	= rz1000_set_mode,
पूर्ण;

अटल पूर्णांक rz1000_fअगरo_disable(काष्ठा pci_dev *pdev)
अणु
	u16 reg;
	/* Be exceptionally paranoid as we must be sure to apply the fix */
	अगर (pci_पढ़ो_config_word(pdev, 0x40, &reg) != 0)
		वापस -1;
	reg &= 0xDFFF;
	अगर (pci_ग_लिखो_config_word(pdev, 0x40, reg) != 0)
		वापस -1;
	prपूर्णांकk(KERN_INFO DRV_NAME ": disabled chipset readahead.\n");
	वापस 0;
पूर्ण

/**
 *	rz1000_init_one - Register RZ1000 ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in rz1000_pci_tbl matching with @pdev
 *
 *	Configure an RZ1000 पूर्णांकerface. This करोesn't require much special
 *	handling except that we *MUST* समाप्त the chipset पढ़ोahead or the
 *	user may experience data corruption.
 */

अटल पूर्णांक rz1000_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &rz1000_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	अगर (rz1000_fअगरo_disable(pdev) == 0)
		वापस ata_pci_sff_init_one(pdev, ppi, &rz1000_sht, शून्य, 0);

	prपूर्णांकk(KERN_ERR DRV_NAME ": failed to disable read-ahead on chipset..\n");
	/* Not safe to use so skip */
	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rz1000_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	/* If this fails on resume (which is a "can't happen" हाल), we
	   must stop as any progress risks data loss */
	अगर (rz1000_fअगरo_disable(pdev))
		panic("rz1000 fifo");

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id pata_rz1000[] = अणु
	अणु PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_RZ1000), पूर्ण,
	अणु PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_RZ1001), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver rz1000_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= pata_rz1000,
	.probe 		= rz1000_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= rz1000_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(rz1000_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for RZ1000 PCI ATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pata_rz1000);
MODULE_VERSION(DRV_VERSION);
