<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_efar.c - EFAR PIIX clone controller driver
 *
 *	(C) 2005 Red Hat
 *	(C) 2009-2010 Bartlomiej Zolnierkiewicz
 *
 *    Some parts based on ata_piix.c by Jeff Garzik and others.
 *
 *    The EFAR is a PIIX4 clone with UDMA66 support. Unlike the later
 *    Intel ICH controllers the EFAR widened the UDMA mode रेजिस्टर bits
 *    and करोesn't require the funky घड़ी selection.
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

#घोषणा DRV_NAME	"pata_efar"
#घोषणा DRV_VERSION	"0.4.5"

/**
 *	efar_pre_reset	-	Enable bits
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm cable detection क्रम the EFAR ATA पूर्णांकerface. This is
 *	dअगरferent to the PIIX arrangement
 */

अटल पूर्णांक efar_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits efar_enable_bits[] = अणु
		अणु 0x41U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 0 */
		अणु 0x43U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 1 */
	पूर्ण;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &efar_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	efar_cable_detect	-	check क्रम 40/80 pin
 *	@ap: Port
 *
 *	Perक्रमm cable detection क्रम the EFAR ATA पूर्णांकerface. This is
 *	dअगरferent to the PIIX arrangement
 */

अटल पूर्णांक efar_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 पंचांगp;

	pci_पढ़ो_config_byte(pdev, 0x47, &पंचांगp);
	अगर (पंचांगp & (2 >> ap->port_no))
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

अटल DEFINE_SPINLOCK(efar_lock);

/**
 *	efar_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम efar_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio	= adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक master_port = ap->port_no ? 0x42 : 0x40;
	अचिन्हित दीर्घ flags;
	u16 master_data;
	u8 udma_enable;
	पूर्णांक control = 0;

	/*
	 *	See Intel Document 298600-004 क्रम the timing programing rules
	 *	क्रम PIIX/ICH. The EFAR is a clone so very similar
	 */

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	अगर (pio > 1)
		control |= 1;	/* TIME */
	अगर (ata_pio_need_iordy(adev))	/* PIO 3/4 require IORDY */
		control |= 2;	/* IE */
	/* Intel specअगरies that the prefetch/posting is क्रम disk only */
	अगर (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE */

	spin_lock_irqsave(&efar_lock, flags);

	pci_पढ़ो_config_word(dev, master_port, &master_data);

	/* Set PPE, IE, and TIME as appropriate */
	अगर (adev->devno == 0) अणु
		master_data &= 0xCCF0;
		master_data |= control;
		master_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	पूर्ण अन्यथा अणु
		पूर्णांक shअगरt = 4 * ap->port_no;
		u8 slave_data;

		master_data &= 0xFF0F;
		master_data |= (control << 4);

		/* Slave timing in separate रेजिस्टर */
		pci_पढ़ो_config_byte(dev, 0x44, &slave_data);
		slave_data &= ap->port_no ? 0x0F : 0xF0;
		slave_data |= ((timings[pio][0] << 2) | timings[pio][1]) << shअगरt;
		pci_ग_लिखो_config_byte(dev, 0x44, slave_data);
	पूर्ण

	master_data |= 0x4000;	/* Ensure SITRE is set */
	pci_ग_लिखो_config_word(dev, master_port, master_data);

	pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);
	udma_enable &= ~(1 << (2 * ap->port_no + adev->devno));
	pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);
	spin_unlock_irqrestore(&efar_lock, flags);
पूर्ण

/**
 *	efar_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम efar_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	u8 master_port		= ap->port_no ? 0x42 : 0x40;
	u16 master_data;
	u8 speed		= adev->dma_mode;
	पूर्णांक devid		= adev->devno + 2 * ap->port_no;
	अचिन्हित दीर्घ flags;
	u8 udma_enable;

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	spin_lock_irqsave(&efar_lock, flags);

	pci_पढ़ो_config_word(dev, master_port, &master_data);
	pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);

	अगर (speed >= XFER_UDMA_0) अणु
		अचिन्हित पूर्णांक udma	= adev->dma_mode - XFER_UDMA_0;
		u16 udma_timing;

		udma_enable |= (1 << devid);

		/* Load the UDMA mode number */
		pci_पढ़ो_config_word(dev, 0x4A, &udma_timing);
		udma_timing &= ~(7 << (4 * devid));
		udma_timing |= udma << (4 * devid);
		pci_ग_लिखो_config_word(dev, 0x4A, udma_timing);
	पूर्ण अन्यथा अणु
		/*
		 * MWDMA is driven by the PIO timings. We must also enable
		 * IORDY unconditionally aदीर्घ with TIME1. PPE has alपढ़ोy
		 * been set when the PIO timing was set.
		 */
		अचिन्हित पूर्णांक mwdma	= adev->dma_mode - XFER_MW_DMA_0;
		अचिन्हित पूर्णांक control;
		u8 slave_data;
		स्थिर अचिन्हित पूर्णांक needed_pio[3] = अणु
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		पूर्ण;
		पूर्णांक pio = needed_pio[mwdma] - XFER_PIO_0;

		control = 3;	/* IORDY|TIME1 */

		/* If the drive MWDMA is faster than it can करो PIO then
		   we must क्रमce PIO पूर्णांकo PIO0 */

		अगर (adev->pio_mode < needed_pio[mwdma])
			/* Enable DMA timing only */
			control |= 8;	/* PIO cycles in PIO0 */

		अगर (adev->devno) अणु	/* Slave */
			master_data &= 0xFF4F;  /* Mask out IORDY|TIME1|DMAONLY */
			master_data |= control << 4;
			pci_पढ़ो_config_byte(dev, 0x44, &slave_data);
			slave_data &= ap->port_no ? 0x0F : 0xF0;
			/* Load the matching timing */
			slave_data |= ((timings[pio][0] << 2) | timings[pio][1]) << (ap->port_no ? 4 : 0);
			pci_ग_लिखो_config_byte(dev, 0x44, slave_data);
		पूर्ण अन्यथा अणु 	/* Master */
			master_data &= 0xCCF4;	/* Mask out IORDY|TIME1|DMAONLY
						   and master timing bits */
			master_data |= control;
			master_data |=
				(timings[pio][0] << 12) |
				(timings[pio][1] << 8);
		पूर्ण
		udma_enable &= ~(1 << devid);
		pci_ग_लिखो_config_word(dev, master_port, master_data);
	पूर्ण
	pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);
	spin_unlock_irqrestore(&efar_lock, flags);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा efar_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations efar_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= efar_cable_detect,
	.set_piomode		= efar_set_piomode,
	.set_dmamode		= efar_set_dmamode,
	.prereset		= efar_pre_reset,
पूर्ण;


/**
 *	efar_init_one - Register EFAR ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in efar_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक efar_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY,
		.udma_mask 	= ATA_UDMA4,
		.port_ops	= &efar_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &info पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &efar_sht, शून्य,
				      ATA_HOST_PARALLEL_SCAN);
पूर्ण

अटल स्थिर काष्ठा pci_device_id efar_pci_tbl[] = अणु
	अणु PCI_VDEVICE(EFAR, 0x9130), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver efar_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= efar_pci_tbl,
	.probe			= efar_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(efar_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for EFAR PIIX clones");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, efar_pci_tbl);
MODULE_VERSION(DRV_VERSION);
