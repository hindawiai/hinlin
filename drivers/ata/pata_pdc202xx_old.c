<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_pdc202xx_old.c 	- Promise PDC202xx PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  Alan Cox <alan@lxorguk.ukuu.org.uk>
 *			  (C) 2007,2009,2010 Bartlomiej Zolnierkiewicz
 *
 * Based in part on linux/drivers/ide/pci/pdc202xx_old.c
 *
 * First cut with LBA48/ATAPI
 *
 * TODO:
 *	Channel पूर्णांकerlock/reset on both required ?
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_pdc202xx_old"
#घोषणा DRV_VERSION "0.4.3"

अटल पूर्णांक pdc2026x_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 cis;

	pci_पढ़ो_config_word(pdev, 0x50, &cis);
	अगर (cis & (1 << (10 + ap->port_no)))
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

अटल व्योम pdc202xx_exec_command(काष्ठा ata_port *ap,
				  स्थिर काष्ठा ata_taskfile *tf)
अणु
	DPRINTK("ata%u: cmd 0x%X\n", ap->prपूर्णांक_id, tf->command);

	ioग_लिखो8(tf->command, ap->ioaddr.command_addr);
	ndelay(400);
पूर्ण

अटल bool pdc202xx_irq_check(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ master	= pci_resource_start(pdev, 4);
	u8 sc1d			= inb(master + 0x1d);

	अगर (ap->port_no) अणु
		/*
		 * bit 7: error, bit 6: पूर्णांकerrupting,
		 * bit 5: FIFO full, bit 4: FIFO empty
		 */
		वापस sc1d & 0x40;
	पूर्ण अन्यथा	अणु
		/*
		 * bit 3: error, bit 2: पूर्णांकerrupting,
		 * bit 1: FIFO full, bit 0: FIFO empty
		 */
		वापस sc1d & 0x04;
	पूर्ण
पूर्ण

/**
 *	pdc202xx_configure_piomode	-	set chip PIO timing
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@pio: PIO mode
 *
 *	Called to करो the PIO mode setup. Our timing रेजिस्टरs are shared
 *	so a configure_dmamode call will unकरो any work we करो here and vice
 *	versa
 */

अटल व्योम pdc202xx_configure_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक pio)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = 0x60 + 8 * ap->port_no + 4 * adev->devno;
	अटल u16 pio_timing[5] = अणु
		0x0913, 0x050C , 0x0308, 0x0206, 0x0104
	पूर्ण;
	u8 r_ap, r_bp;

	pci_पढ़ो_config_byte(pdev, port, &r_ap);
	pci_पढ़ो_config_byte(pdev, port + 1, &r_bp);
	r_ap &= ~0x3F;	/* Preserve ERRDY_EN, SYNC_IN */
	r_bp &= ~0x1F;
	r_ap |= (pio_timing[pio] >> 8);
	r_bp |= (pio_timing[pio] & 0xFF);

	अगर (ata_pio_need_iordy(adev))
		r_ap |= 0x20;	/* IORDY enable */
	अगर (adev->class == ATA_DEV_ATA)
		r_ap |= 0x10;	/* FIFO enable */
	pci_ग_लिखो_config_byte(pdev, port, r_ap);
	pci_ग_लिखो_config_byte(pdev, port + 1, r_bp);
पूर्ण

/**
 *	pdc202xx_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup. Our timing रेजिस्टरs are shared
 *	but we want to set the PIO timing by शेष.
 */

अटल व्योम pdc202xx_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	pdc202xx_configure_piomode(ap, adev, adev->pio_mode - XFER_PIO_0);
पूर्ण

/**
 *	pdc202xx_set_dmamode	-	set DMA mode in chip
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Load DMA cycle बार पूर्णांकo the chip पढ़ोy क्रम a DMA transfer
 *	to occur.
 */

अटल व्योम pdc202xx_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = 0x60 + 8 * ap->port_no + 4 * adev->devno;
	अटल u8 udma_timing[6][2] = अणु
		अणु 0x60, 0x03 पूर्ण,	/* 33 Mhz Clock */
		अणु 0x40, 0x02 पूर्ण,
		अणु 0x20, 0x01 पूर्ण,
		अणु 0x40, 0x02 पूर्ण,	/* 66 Mhz Clock */
		अणु 0x20, 0x01 पूर्ण,
		अणु 0x20, 0x01 पूर्ण
	पूर्ण;
	अटल u8 mdma_timing[3][2] = अणु
		अणु 0xe0, 0x0f पूर्ण,
		अणु 0x60, 0x04 पूर्ण,
		अणु 0x60, 0x03 पूर्ण,
	पूर्ण;
	u8 r_bp, r_cp;

	pci_पढ़ो_config_byte(pdev, port + 1, &r_bp);
	pci_पढ़ो_config_byte(pdev, port + 2, &r_cp);

	r_bp &= ~0xE0;
	r_cp &= ~0x0F;

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		पूर्णांक speed = adev->dma_mode - XFER_UDMA_0;
		r_bp |= udma_timing[speed][0];
		r_cp |= udma_timing[speed][1];

	पूर्ण अन्यथा अणु
		पूर्णांक speed = adev->dma_mode - XFER_MW_DMA_0;
		r_bp |= mdma_timing[speed][0];
		r_cp |= mdma_timing[speed][1];
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, port + 1, r_bp);
	pci_ग_लिखो_config_byte(pdev, port + 2, r_cp);

पूर्ण

/**
 *	pdc2026x_bmdma_start		-	DMA engine begin
 *	@qc: ATA command
 *
 *	In UDMA3 or higher we have to घड़ी चयन क्रम the duration of the
 *	DMA transfer sequence.
 *
 *	Note: The host lock held by the libata layer protects
 *	us from two channels both trying to set DMA bits at once
 */

अटल व्योम pdc2026x_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा ata_taskfile *tf = &qc->tf;
	पूर्णांक sel66 = ap->port_no ? 0x08: 0x02;

	व्योम __iomem *master = ap->host->ports[0]->ioaddr.bmdma_addr;
	व्योम __iomem *घड़ी = master + 0x11;
	व्योम __iomem *atapi_reg = master + 0x20 + (4 * ap->port_no);

	u32 len;

	/* Check we keep host level locking here */
	अगर (adev->dma_mode > XFER_UDMA_2)
		ioग_लिखो8(ioपढ़ो8(घड़ी) | sel66, घड़ी);
	अन्यथा
		ioग_लिखो8(ioपढ़ो8(घड़ी) & ~sel66, घड़ी);

	/* The DMA घड़ीs may have been trashed by a reset. FIXME: make conditional
	   and move to qc_issue ? */
	pdc202xx_set_dmamode(ap, qc->dev);

	/* Cases the state machine will not complete correctly without help */
	अगर ((tf->flags & ATA_TFLAG_LBA48) ||  tf->protocol == ATAPI_PROT_DMA) अणु
		len = qc->nbytes / 2;

		अगर (tf->flags & ATA_TFLAG_WRITE)
			len |= 0x06000000;
		अन्यथा
			len |= 0x05000000;

		ioग_लिखो32(len, atapi_reg);
	पूर्ण

	/* Activate DMA */
	ata_bmdma_start(qc);
पूर्ण

/**
 *	pdc2026x_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	After a DMA completes we need to put the घड़ी back to 33MHz क्रम
 *	PIO timings.
 *
 *	Note: The host lock held by the libata layer protects
 *	us from two channels both trying to set DMA bits at once
 */

अटल व्योम pdc2026x_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा ata_taskfile *tf = &qc->tf;

	पूर्णांक sel66 = ap->port_no ? 0x08: 0x02;
	/* The घड़ी bits are in the same रेजिस्टर क्रम both channels */
	व्योम __iomem *master = ap->host->ports[0]->ioaddr.bmdma_addr;
	व्योम __iomem *घड़ी = master + 0x11;
	व्योम __iomem *atapi_reg = master + 0x20 + (4 * ap->port_no);

	/* Cases the state machine will not complete correctly */
	अगर (tf->protocol == ATAPI_PROT_DMA || (tf->flags & ATA_TFLAG_LBA48)) अणु
		ioग_लिखो32(0, atapi_reg);
		ioग_लिखो8(ioपढ़ो8(घड़ी) & ~sel66, घड़ी);
	पूर्ण
	/* Flip back to 33Mhz क्रम PIO */
	अगर (adev->dma_mode > XFER_UDMA_2)
		ioग_लिखो8(ioपढ़ो8(घड़ी) & ~sel66, घड़ी);
	ata_bmdma_stop(qc);
	pdc202xx_set_piomode(ap, adev);
पूर्ण

/**
 *	pdc2026x_dev_config	-	device setup hook
 *	@adev: newly found device
 *
 *	Perक्रमm chip specअगरic early setup. We need to lock the transfer
 *	sizes to 8bit to aव्योम making the state engine on the 2026x cards
 *	barf.
 */

अटल व्योम pdc2026x_dev_config(काष्ठा ata_device *adev)
अणु
	adev->max_sectors = 256;
पूर्ण

अटल पूर्णांक pdc2026x_port_start(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *bmdma = ap->ioaddr.bmdma_addr;
	अगर (bmdma) अणु
		/* Enable burst mode */
		u8 burst = ioपढ़ो8(bmdma + 0x1f);
		ioग_लिखो8(burst | 0x01, bmdma + 0x1f);
	पूर्ण
	वापस ata_bmdma_port_start(ap);
पूर्ण

/**
 *	pdc2026x_check_atapi_dma - Check whether ATAPI DMA can be supported क्रम this command
 *	@qc: Metadata associated with taskfile to check
 *
 *	Just say no - not supported on older Promise.
 *
 *	LOCKING:
 *	None (inherited from caller).
 *
 *	RETURNS: 0 when ATAPI DMA can be used
 *		 1 otherwise
 */

अटल पूर्णांक pdc2026x_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pdc202xx_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pdc2024x_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.cable_detect		= ata_cable_40wire,
	.set_piomode		= pdc202xx_set_piomode,
	.set_dmamode		= pdc202xx_set_dmamode,

	.sff_exec_command	= pdc202xx_exec_command,
	.sff_irq_check		= pdc202xx_irq_check,
पूर्ण;

अटल काष्ठा ata_port_operations pdc2026x_port_ops = अणु
	.inherits		= &pdc2024x_port_ops,

	.check_atapi_dma	= pdc2026x_check_atapi_dma,
	.bmdma_start		= pdc2026x_bmdma_start,
	.bmdma_stop		= pdc2026x_bmdma_stop,

	.cable_detect		= pdc2026x_cable_detect,
	.dev_config		= pdc2026x_dev_config,

	.port_start		= pdc2026x_port_start,

	.sff_exec_command	= pdc202xx_exec_command,
	.sff_irq_check		= pdc202xx_irq_check,
पूर्ण;

अटल पूर्णांक pdc202xx_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info[3] = अणु
		अणु
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.port_ops = &pdc2024x_port_ops
		पूर्ण,
		अणु
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.port_ops = &pdc2026x_port_ops
		पूर्ण,
		अणु
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &pdc2026x_port_ops
		पूर्ण

	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info[id->driver_data], शून्य पूर्ण;

	अगर (dev->device == PCI_DEVICE_ID_PROMISE_20265) अणु
		काष्ठा pci_dev *bridge = dev->bus->self;
		/* Don't grab anything behind a Promise I2O RAID */
		अगर (bridge && bridge->venकरोr == PCI_VENDOR_ID_INTEL) अणु
			अगर (bridge->device == PCI_DEVICE_ID_INTEL_I960)
				वापस -ENODEV;
			अगर (bridge->device == PCI_DEVICE_ID_INTEL_I960RM)
				वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस ata_pci_bmdma_init_one(dev, ppi, &pdc202xx_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pdc202xx[] = अणु
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20246), 0 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20262), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20263), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20265), 2 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20267), 2 पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver pdc202xx_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= pdc202xx,
	.probe 		= pdc202xx_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(pdc202xx_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Promise 2024x and 20262-20267");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pdc202xx);
MODULE_VERSION(DRV_VERSION);
