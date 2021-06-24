<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_ninja32.c 	- Ninja32 PATA क्रम new ATA layer
 *			  (C) 2007 Red Hat Inc
 *
 * Note: The controller like many controllers has shared timings क्रम
 * PIO and DMA. We thus flip to the DMA timings in dma_start and flip back
 * in the dma_stop function. Thus we actually करोn't need a set_dmamode
 * method as the PIO method is always called and will set the right PIO
 * timing parameters.
 *
 * The Ninja32 Cardbus is not a generic SFF controller. Instead it is
 * laid out as follows off BAR 0. This is based upon Mark Lord's delkin
 * driver and the extensive analysis करोne by the BSD developers, notably
 * ITOH Yasufumi.
 *
 *	Base + 0x00 IRQ Status
 *	Base + 0x01 IRQ control
 *	Base + 0x02 Chipset control
 *	Base + 0x03 Unknown
 *	Base + 0x04 VDMA and reset control + रुको bits
 *	Base + 0x08 BMIMBA
 *	Base + 0x0C DMA Length
 *	Base + 0x10 Taskfile
 *	Base + 0x18 BMDMA Status ?
 *	Base + 0x1C
 *	Base + 0x1D Bus master control
 *		bit 0 = enable
 *		bit 1 = 0 ग_लिखो/1 पढ़ो
 *		bit 2 = 1 sgtable
 *		bit 3 = go
 *		bit 4-6 रुको bits
 *		bit 7 = करोne
 *	Base + 0x1E AltStatus
 *	Base + 0x1F timing रेजिस्टर
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_ninja32"
#घोषणा DRV_VERSION "0.1.5"


/**
 *	ninja32_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup. Our timing रेजिस्टरs are shared
 *	but we want to set the PIO timing by शेष.
 */

अटल व्योम ninja32_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल u16 pio_timing[5] = अणु
		0xd6, 0x85, 0x44, 0x33, 0x13
	पूर्ण;
	ioग_लिखो8(pio_timing[adev->pio_mode - XFER_PIO_0],
		 ap->ioaddr.bmdma_addr + 0x1f);
	ap->निजी_data = adev;
पूर्ण


अटल व्योम ninja32_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	काष्ठा ata_device *adev = &ap->link.device[device];
	अगर (ap->निजी_data != adev) अणु
		ioग_लिखो8(0xd6, ap->ioaddr.bmdma_addr + 0x1f);
		ata_sff_dev_select(ap, device);
		ninja32_set_piomode(ap, adev);
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ninja32_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations ninja32_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.sff_dev_select = ninja32_dev_select,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= ninja32_set_piomode,
	.sff_data_xfer	= ata_sff_data_xfer32
पूर्ण;

अटल व्योम ninja32_program(व्योम __iomem *base)
अणु
	ioग_लिखो8(0x05, base + 0x01);	/* Enable पूर्णांकerrupt lines */
	ioग_लिखो8(0xBE, base + 0x02);	/* Burst, ?? setup */
	ioग_लिखो8(0x01, base + 0x03);	/* Unknown */
	ioग_लिखो8(0x20, base + 0x04);	/* WAIT0 */
	ioग_लिखो8(0x8f, base + 0x05);	/* Unknown */
	ioग_लिखो8(0xa4, base + 0x1c);	/* Unknown */
	ioग_लिखो8(0x83, base + 0x1d);	/* BMDMA control: WAIT0 */
पूर्ण

अटल पूर्णांक ninja32_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	व्योम __iomem *base;
	पूर्णांक rc;

	host = ata_host_alloc(&dev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;
	ap = host->ports[0];

	/* Set up the PCI device */
	rc = pcim_enable_device(dev);
	अगर (rc)
		वापस rc;
	rc = pcim_iomap_regions(dev, 1 << 0, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(dev);
	अगर (rc)
		वापस rc;

	host->iomap = pcim_iomap_table(dev);
	rc = dma_set_mask_and_coherent(&dev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;
	pci_set_master(dev);

	/* Set up the रेजिस्टर mappings. We use the I/O mapping as only the
	   older chips also have MMIO on BAR 1 */
	base = host->iomap[0];
	अगर (!base)
		वापस -ENOMEM;
	ap->ops = &ninja32_port_ops;
	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	ap->ioaddr.cmd_addr = base + 0x10;
	ap->ioaddr.ctl_addr = base + 0x1E;
	ap->ioaddr.altstatus_addr = base + 0x1E;
	ap->ioaddr.bmdma_addr = base;
	ata_sff_std_ports(&ap->ioaddr);
	ap->pflags |= ATA_PFLAG_PIO32 | ATA_PFLAG_PIO32CHANGE;

	ninja32_program(base);
	/* FIXME: Should we disable them at हटाओ ? */
	वापस ata_host_activate(host, dev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &ninja32_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ninja32_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;
	ninja32_program(host->iomap[0]);
	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id ninja32[] = अणु
	अणु 0x10FC, 0x0003, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0x1145, 0x8008, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0x1145, 0xf008, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0x1145, 0xf021, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0x1145, 0xf024, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0x1145, 0xf02C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ninja32_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= ninja32,
	.probe 		= ninja32_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ninja32_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(ninja32_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Ninja32 ATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ninja32);
MODULE_VERSION(DRV_VERSION);
