<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  pata_sch.c - Intel SCH PATA controllers
 *
 *  Copyright (c) 2008 Alek Du <alek.du@पूर्णांकel.com>
 */

/*
 *  Supports:
 *    Intel SCH (AF82US15W, AF82US15L, AF82UL11L) chipsets -- see spec at:
 *    http://करोwnload.पूर्णांकel.com/design/chipsets/embedded/datashts/319537.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME	"pata_sch"
#घोषणा DRV_VERSION	"0.2"

/* see SCH datasheet page 351 */
क्रमागत अणु
	D0TIM	= 0x80,		/* Device 0 Timing Register */
	D1TIM	= 0x84,		/* Device 1 Timing Register */
	PM	= 0x07,		/* PIO Mode Bit Mask */
	MDM	= (0x03 << 8),	/* Multi-word DMA Mode Bit Mask */
	UDM	= (0x07 << 16), /* Ultra DMA Mode Bit Mask */
	PPE	= (1 << 30),	/* Prefetch/Post Enable */
	USD	= (1 << 31),	/* Use Synchronous DMA */
पूर्ण;

अटल पूर्णांक sch_init_one(काष्ठा pci_dev *pdev,
			 स्थिर काष्ठा pci_device_id *ent);
अटल व्योम sch_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev);
अटल व्योम sch_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev);

अटल स्थिर काष्ठा pci_device_id sch_pci_tbl[] = अणु
	/* Intel SCH PATA Controller */
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_SCH_IDE), 0 पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver sch_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= sch_pci_tbl,
	.probe			= sch_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा sch_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations sch_pata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= ata_cable_unknown,
	.set_piomode		= sch_set_piomode,
	.set_dmamode		= sch_set_dmamode,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info sch_port_info = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA5,
	.port_ops	= &sch_pata_ops,
पूर्ण;

MODULE_AUTHOR("Alek Du <alek.du@intel.com>");
MODULE_DESCRIPTION("SCSI low-level driver for Intel SCH PATA controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sch_pci_tbl);
MODULE_VERSION(DRV_VERSION);

/**
 *	sch_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: ATA device
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sch_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio	= adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक port	= adev->devno ? D1TIM : D0TIM;
	अचिन्हित पूर्णांक data;

	pci_पढ़ो_config_dword(dev, port, &data);
	/* see SCH datasheet page 351 */
	/* set PIO mode */
	data &= ~(PM | PPE);
	data |= pio;
	/* enable PPE क्रम block device */
	अगर (adev->class == ATA_DEV_ATA)
		data |= PPE;
	pci_ग_लिखो_config_dword(dev, port, data);
पूर्ण

/**
 *	sch_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: ATA device
 *
 *	Set MW/UDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम sch_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक dma_mode	= adev->dma_mode;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक port	= adev->devno ? D1TIM : D0TIM;
	अचिन्हित पूर्णांक data;

	pci_पढ़ो_config_dword(dev, port, &data);
	/* see SCH datasheet page 351 */
	अगर (dma_mode >= XFER_UDMA_0) अणु
		/* enable Synchronous DMA mode */
		data |= USD;
		data &= ~UDM;
		data |= (dma_mode - XFER_UDMA_0) << 16;
	पूर्ण अन्यथा अणु /* must be MWDMA mode, since we masked SWDMA alपढ़ोy */
		data &= ~(USD | MDM);
		data |= (dma_mode - XFER_MW_DMA_0) << 8;
	पूर्ण
	pci_ग_लिखो_config_dword(dev, port, data);
पूर्ण

/**
 *	sch_init_one - Register SCH ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in sch_pci_tbl matching with @pdev
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक sch_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &sch_port_info, शून्य पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &sch_sht, शून्य, 0);
पूर्ण

module_pci_driver(sch_pci_driver);
