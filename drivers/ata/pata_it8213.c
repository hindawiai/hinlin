<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_it8213.c - iTE Tech. Inc.  IT8213 PATA driver
 *
 *    The IT8213 is a very Intel ICH like device क्रम timing purposes, having
 *    a similar रेजिस्टर layout and the same split घड़ी arrangement. Cable
 *    detection is dअगरferent, and it करोes not have slave channels or all the
 *    clutter of later ICH/SATA setups.
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

#घोषणा DRV_NAME	"pata_it8213"
#घोषणा DRV_VERSION	"0.0.3"

/**
 *	it8213_pre_reset	-	probe begin
 *	@link: link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Filter out ports by the enable bits beक्रमe करोing the normal reset
 *	and probe.
 */

अटल पूर्णांक it8213_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits it8213_enable_bits[] = अणु
		अणु 0x41U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 0 */
	पूर्ण;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अगर (!pci_test_config_bits(pdev, &it8213_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	it8213_cable_detect	-	check क्रम 40/80 pin
 *	@ap: Port
 *
 *	Perक्रमm cable detection क्रम the 8213 ATA पूर्णांकerface. This is
 *	dअगरferent to the PIIX arrangement
 */

अटल पूर्णांक it8213_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 पंचांगp;
	pci_पढ़ो_config_byte(pdev, 0x42, &पंचांगp);
	अगर (पंचांगp & 2)	/* The initial करोcs are incorrect */
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	it8213_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device whose timings we are configuring
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम it8213_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio	= adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक master_port = ap->port_no ? 0x42 : 0x40;
	u16 master_data;
	पूर्णांक control = 0;

	/*
	 *	See Intel Document 298600-004 क्रम the timing programing rules
	 *	क्रम PIIX/ICH. The 8213 is a clone so very similar
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
	/* Bit 2 is set क्रम ATAPI on the IT8213 - reverse of ICH/PIIX */
	अगर (adev->class != ATA_DEV_ATA)
		control |= 4;	/* PPE */

	pci_पढ़ो_config_word(dev, master_port, &master_data);

	/* Set PPE, IE, and TIME as appropriate */
	अगर (adev->devno == 0) अणु
		master_data &= 0xCCF0;
		master_data |= control;
		master_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	पूर्ण अन्यथा अणु
		u8 slave_data;

		master_data &= 0xFF0F;
		master_data |= (control << 4);

		/* Slave timing in separate रेजिस्टर */
		pci_पढ़ो_config_byte(dev, 0x44, &slave_data);
		slave_data &= 0xF0;
		slave_data |= (timings[pio][0] << 2) | timings[pio][1];
		pci_ग_लिखो_config_byte(dev, 0x44, slave_data);
	पूर्ण

	master_data |= 0x4000;	/* Ensure SITRE is set */
	pci_ग_लिखो_config_word(dev, master_port, master_data);
पूर्ण

/**
 *	it8213_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set UDMA/MWDMA mode क्रम device, in host controller PCI config space.
 *	This device is basically an ICH alike.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम it8213_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	u16 master_data;
	u8 speed		= adev->dma_mode;
	पूर्णांक devid		= adev->devno;
	u8 udma_enable;

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	pci_पढ़ो_config_word(dev, 0x40, &master_data);
	pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);

	अगर (speed >= XFER_UDMA_0) अणु
		अचिन्हित पूर्णांक udma = adev->dma_mode - XFER_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		पूर्णांक u_घड़ी, u_speed;

		/* Clocks follow the PIIX style */
		u_speed = min(2 - (udma & 1), udma);
		अगर (udma > 4)
			u_घड़ी = 0x1000;	/* 100Mhz */
		अन्यथा अगर (udma > 2)
			u_घड़ी = 1;		/* 66Mhz */
		अन्यथा
			u_घड़ी = 0;		/* 33Mhz */

		udma_enable |= (1 << devid);

		/* Load the UDMA cycle समय */
		pci_पढ़ो_config_word(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_ग_लिखो_config_word(dev, 0x4A, udma_timing);

		/* Load the घड़ी selection */
		pci_पढ़ो_config_word(dev, 0x54, &ideconf);
		ideconf &= ~(0x1001 << devid);
		ideconf |= u_घड़ी << devid;
		pci_ग_लिखो_config_word(dev, 0x54, ideconf);
	पूर्ण अन्यथा अणु
		/*
		 * MWDMA is driven by the PIO timings. We must also enable
		 * IORDY unconditionally aदीर्घ with TIME1. PPE has alपढ़ोy
		 * been set when the PIO timing was set.
		 */
		अचिन्हित पूर्णांक mwdma	= adev->dma_mode - XFER_MW_DMA_0;
		अचिन्हित पूर्णांक control;
		u8 slave_data;
		अटल स्थिर अचिन्हित पूर्णांक needed_pio[3] = अणु
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		पूर्ण;
		पूर्णांक pio = needed_pio[mwdma] - XFER_PIO_0;

		control = 3;	/* IORDY|TIME1 */

		/* If the drive MWDMA is faster than it can करो PIO then
		   we must क्रमce PIO पूर्णांकo PIO0 */

		अगर (adev->pio_mode < needed_pio[mwdma])
			/* Enable DMA timing only */
			control |= 8;	/* PIO cycles in PIO0 */

		अगर (devid) अणु	/* Slave */
			master_data &= 0xFF4F;  /* Mask out IORDY|TIME1|DMAONLY */
			master_data |= control << 4;
			pci_पढ़ो_config_byte(dev, 0x44, &slave_data);
			slave_data &= 0xF0;
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
		pci_ग_लिखो_config_word(dev, 0x40, master_data);
	पूर्ण
	pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा it8213_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;


अटल काष्ठा ata_port_operations it8213_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= it8213_cable_detect,
	.set_piomode		= it8213_set_piomode,
	.set_dmamode		= it8213_set_dmamode,
	.prereset		= it8213_pre_reset,
पूर्ण;


/**
 *	it8213_init_one - Register 8213 ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in it8213_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक it8213_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &it8213_ops,
	पूर्ण;
	/* Current IT8213 stuff is single port */
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &ata_dummy_port_info पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &it8213_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id it8213_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8213), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver it8213_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= it8213_pci_tbl,
	.probe			= it8213_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(it8213_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for the ITE 8213");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, it8213_pci_tbl);
MODULE_VERSION(DRV_VERSION);
