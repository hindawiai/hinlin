<शैली गुरु>
/*
 *	pata_hpt3x3		-	HPT3x3 driver
 *	(c) Copyright 2005-2006 Red Hat
 *
 *	Was pata_hpt34x but the naming was confusing as it supported the
 *	343 and 363 so it has been नामd.
 *
 *	Based on:
 *	linux/drivers/ide/pci/hpt34x.c		Version 0.40	Sept 10, 2002
 *	Copyright (C) 1998-2000	Andre Hedrick <andre@linux-ide.org>
 *
 *	May be copied or modअगरied under the terms of the GNU General Public
 *	License
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_hpt3x3"
#घोषणा DRV_VERSION	"0.6.1"

/**
 *	hpt3x3_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Set our PIO requirements. This is fairly simple on the HPT3x3 as
 *	all we have to करो is clear the MWDMA and UDMA bits then load the
 *	mode number.
 */

अटल व्योम hpt3x3_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 r1, r2;
	पूर्णांक dn = 2 * ap->port_no + adev->devno;

	pci_पढ़ो_config_dword(pdev, 0x44, &r1);
	pci_पढ़ो_config_dword(pdev, 0x48, &r2);
	/* Load the PIO timing number */
	r1 &= ~(7 << (3 * dn));
	r1 |= (adev->pio_mode - XFER_PIO_0) << (3 * dn);
	r2 &= ~(0x11 << dn);	/* Clear MWDMA and UDMA bits */

	pci_ग_लिखो_config_dword(pdev, 0x44, r1);
	pci_ग_लिखो_config_dword(pdev, 0x48, r2);
पूर्ण

#अगर defined(CONFIG_PATA_HPT3X3_DMA)
/**
 *	hpt3x3_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	Set up the channel क्रम MWDMA or UDMA modes. Much the same as with
 *	PIO, load the mode number and then set MWDMA or UDMA flag.
 *
 *	0x44 : bit 0-2 master mode, 3-5 slave mode, etc
 *	0x48 : bit 4/0 DMA/UDMA bit 5/1 क्रम slave etc
 */

अटल व्योम hpt3x3_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 r1, r2;
	पूर्णांक dn = 2 * ap->port_no + adev->devno;
	पूर्णांक mode_num = adev->dma_mode & 0x0F;

	pci_पढ़ो_config_dword(pdev, 0x44, &r1);
	pci_पढ़ो_config_dword(pdev, 0x48, &r2);
	/* Load the timing number */
	r1 &= ~(7 << (3 * dn));
	r1 |= (mode_num << (3 * dn));
	r2 &= ~(0x11 << dn);	/* Clear MWDMA and UDMA bits */

	अगर (adev->dma_mode >= XFER_UDMA_0)
		r2 |= (0x01 << dn);	/* Ultra mode */
	अन्यथा
		r2 |= (0x10 << dn);	/* MWDMA */

	pci_ग_लिखो_config_dword(pdev, 0x44, r1);
	pci_ग_लिखो_config_dword(pdev, 0x48, r2);
पूर्ण

/**
 *	hpt3x3_मुक्तze		-	DMA workaround
 *	@ap: port to मुक्तze
 *
 *	When मुक्तzing an HPT3x3 we must stop any pending DMA beक्रमe
 *	writing to the control रेजिस्टर or the chip will hang
 */

अटल व्योम hpt3x3_मुक्तze(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *mmio = ap->ioaddr.bmdma_addr;

	ioग_लिखो8(ioपढ़ो8(mmio + ATA_DMA_CMD) & ~ ATA_DMA_START,
			mmio + ATA_DMA_CMD);
	ata_sff_dma_छोड़ो(ap);
	ata_sff_मुक्तze(ap);
पूर्ण

/**
 *	hpt3x3_bmdma_setup	-	DMA workaround
 *	@qc: Queued command
 *
 *	When issuing BMDMA we must clean up the error/active bits in
 *	software on this device
 */

अटल व्योम hpt3x3_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	u8 r = ioपढ़ो8(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
	r |= ATA_DMA_INTR | ATA_DMA_ERR;
	ioग_लिखो8(r, ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
	वापस ata_bmdma_setup(qc);
पूर्ण

/**
 *	hpt3x3_atapi_dma	-	ATAPI DMA check
 *	@qc: Queued command
 *
 *	Just say no - we करोn't करो ATAPI DMA
 */

अटल पूर्णांक hpt3x3_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस 1;
पूर्ण

#पूर्ण_अगर /* CONFIG_PATA_HPT3X3_DMA */

अटल काष्ठा scsi_host_ढाँचा hpt3x3_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations hpt3x3_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= hpt3x3_set_piomode,
#अगर defined(CONFIG_PATA_HPT3X3_DMA)
	.set_dmamode	= hpt3x3_set_dmamode,
	.bmdma_setup	= hpt3x3_bmdma_setup,
	.check_atapi_dma= hpt3x3_atapi_dma,
	.मुक्तze		= hpt3x3_मुक्तze,
#पूर्ण_अगर

पूर्ण;

/**
 *	hpt3x3_init_chipset	-	chip setup
 *	@dev: PCI device
 *
 *	Perक्रमm the setup required at boot and on resume.
 */

अटल व्योम hpt3x3_init_chipset(काष्ठा pci_dev *dev)
अणु
	u16 cmd;
	/* Initialize the board */
	pci_ग_लिखो_config_word(dev, 0x80, 0x00);
	/* Check अगर it is a 343 or a 363. 363 has COMMAND_MEMORY set */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	अगर (cmd & PCI_COMMAND_MEMORY)
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0xF0);
	अन्यथा
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x20);
पूर्ण

/**
 *	hpt3x3_init_one		-	Initialise an HPT343/363
 *	@pdev: PCI device
 *	@id: Entry in match table
 *
 *	Perक्रमm basic initialisation. We set the device up so we access all
 *	ports via BAR4. This is necessary to work around errata.
 */

अटल पूर्णांक hpt3x3_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
#अगर defined(CONFIG_PATA_HPT3X3_DMA)
		/* Further debug needed */
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
#पूर्ण_अगर
		.port_ops = &hpt3x3_port_ops
	पूर्ण;
	/* Register offsets of taskfiles in BAR4 area */
	अटल स्थिर u8 offset_cmd[2] = अणु 0x20, 0x28 पूर्ण;
	अटल स्थिर u8 offset_ctl[2] = अणु 0x36, 0x3E पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	काष्ठा ata_host *host;
	पूर्णांक i, rc;
	व्योम __iomem *base;

	hpt3x3_init_chipset(pdev);

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 2);
	अगर (!host)
		वापस -ENOMEM;
	/* acquire resources and fill host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* Everything is relative to BAR4 अगर we set up this way */
	rc = pcim_iomap_regions(pdev, 1 << 4, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);
	rc = dma_set_mask_and_coherent(&pdev->dev, ATA_DMA_MASK);
	अगर (rc)
		वापस rc;

	base = host->iomap[4];	/* Bus mastering base */

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];
		काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

		ioaddr->cmd_addr = base + offset_cmd[i];
		ioaddr->altstatus_addr =
		ioaddr->ctl_addr = base + offset_ctl[i];
		ioaddr->scr_addr = शून्य;
		ata_sff_std_ports(ioaddr);
		ioaddr->bmdma_addr = base + 8 * i;

		ata_port_pbar_desc(ap, 4, -1, "ioport");
		ata_port_pbar_desc(ap, 4, offset_cmd[i], "cmd");
	पूर्ण
	pci_set_master(pdev);
	वापस ata_host_activate(host, pdev->irq, ata_bmdma_पूर्णांकerrupt,
				 IRQF_SHARED, &hpt3x3_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hpt3x3_reinit_one(काष्ठा pci_dev *dev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(dev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(dev);
	अगर (rc)
		वापस rc;

	hpt3x3_init_chipset(dev);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id hpt3x3[] = अणु
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT343), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver hpt3x3_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= hpt3x3,
	.probe 		= hpt3x3_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= hpt3x3_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(hpt3x3_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the Highpoint HPT343/363");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, hpt3x3);
MODULE_VERSION(DRV_VERSION);
