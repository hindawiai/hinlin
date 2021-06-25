<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_netcell.c - Netcell PATA driver
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

#घोषणा DRV_NAME	"pata_netcell"
#घोषणा DRV_VERSION	"0.1.7"

/* No PIO or DMA methods needed क्रम this device */

अटल अचिन्हित पूर्णांक netcell_पढ़ो_id(काष्ठा ata_device *adev,
					काष्ठा ata_taskfile *tf, u16 *id)
अणु
	अचिन्हित पूर्णांक err_mask = ata_करो_dev_पढ़ो_id(adev, tf, id);
	/* Firmware क्रममाला_लो to mark words 85-87 valid */
	अगर (err_mask == 0)
		id[ATA_ID_CSF_DEFAULT] |= 0x4000;
	वापस err_mask;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा netcell_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations netcell_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_80wire,
	.पढ़ो_id	= netcell_पढ़ो_id,
पूर्ण;


/**
 *	netcell_init_one - Register Netcell ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in netcell_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक netcell_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		/* Actually we करोn't really care about these as the
		   firmware deals with it */
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5, /* UDMA 133 */
		.port_ops	= &netcell_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *port_info[] = अणु &info, शून्य पूर्ण;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* Any chip specअगरic setup/optimisation/messages here */
	ata_pci_bmdma_clear_simplex(pdev);

	/* And let the library code करो the work */
	वापस ata_pci_bmdma_init_one(pdev, port_info, &netcell_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id netcell_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NETCELL, PCI_DEVICE_ID_REVOLUTION), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver netcell_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= netcell_pci_tbl,
	.probe			= netcell_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(netcell_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for Netcell PATA RAID");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, netcell_pci_tbl);
MODULE_VERSION(DRV_VERSION);
