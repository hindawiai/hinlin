<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_radisys.c - Intel PATA/SATA controllers
 *
 *	(C) 2006 Red Hat <alan@lxorguk.ukuu.org.uk>
 *
 *    Some parts based on ata_piix.c by Jeff Garzik and others.
 *
 *    A PIIX relative, this device has a single ATA channel and no
 *    slave timings, SITRE or PPE. In that sense it is a बंद relative
 *    of the original PIIX. It करोes however support UDMA 33/66 per channel
 *    although no other modes/timings. Also lacking is 32bit I/O on the ATA
 *    port.
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

#घोषणा DRV_NAME	"pata_radisys"
#घोषणा DRV_VERSION	"0.4.4"

/**
 *	radisys_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: ATA port
 *	@adev: Device whose timings we are configuring
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम radisys_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio	= adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	u16 ideपंचांग_data;
	पूर्णांक control = 0;

	/*
	 *	See Intel Document 298600-004 क्रम the timing programing rules
	 *	क्रम PIIX/ICH. Note that the early PIIX करोes not have the slave
	 *	timing port at 0x44. The Radisys is a relative of the PIIX
	 *	but not the same so be careful.
	 */

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,	/* Check me */
			    अणु 0, 0 पूर्ण,
			    अणु 1, 1 पूर्ण,
			    अणु 2, 2 पूर्ण,
			    अणु 3, 3 पूर्ण, पूर्ण;

	अगर (pio > 0)
		control |= 1;	/* TIME1 enable */
	अगर (ata_pio_need_iordy(adev))
		control |= 2;	/* IE IORDY */

	pci_पढ़ो_config_word(dev, 0x40, &ideपंचांग_data);

	/* Enable IE and TIME as appropriate. Clear the other
	   drive timing bits */
	ideपंचांग_data &= 0xCCCC;
	ideपंचांग_data |= (control << (4 * adev->devno));
	ideपंचांग_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	pci_ग_लिखो_config_word(dev, 0x40, ideपंचांग_data);

	/* Track which port is configured */
	ap->निजी_data = adev;
पूर्ण

/**
 *	radisys_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set MWDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम radisys_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	u16 ideपंचांग_data;
	u8 udma_enable;

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 1 पूर्ण,
			    अणु 2, 2 पूर्ण,
			    अणु 3, 3 पूर्ण, पूर्ण;

	/*
	 * MWDMA is driven by the PIO timings. We must also enable
	 * IORDY unconditionally.
	 */

	pci_पढ़ो_config_word(dev, 0x40, &ideपंचांग_data);
	pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);

	अगर (adev->dma_mode < XFER_UDMA_0) अणु
		अचिन्हित पूर्णांक mwdma	= adev->dma_mode - XFER_MW_DMA_0;
		स्थिर अचिन्हित पूर्णांक needed_pio[3] = अणु
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		पूर्ण;
		पूर्णांक pio = needed_pio[mwdma] - XFER_PIO_0;
		पूर्णांक control = 3;	/* IORDY|TIME0 */

		/* If the drive MWDMA is faster than it can करो PIO then
		   we must क्रमce PIO0 क्रम PIO cycles. */

		अगर (adev->pio_mode < needed_pio[mwdma])
			control = 1;

		/* Mask out the relevant control and timing bits we will load. Also
		   clear the other drive TIME रेजिस्टर as a precaution */

		ideपंचांग_data &= 0xCCCC;
		ideपंचांग_data |= control << (4 * adev->devno);
		ideपंचांग_data |= (timings[pio][0] << 12) | (timings[pio][1] << 8);

		udma_enable &= ~(1 << adev->devno);
	पूर्ण अन्यथा अणु
		u8 udma_mode;

		/* UDMA66 on: UDMA 33 and 66 are चयनable via रेजिस्टर 0x4A */

		pci_पढ़ो_config_byte(dev, 0x4A, &udma_mode);

		अगर (adev->xfer_mode == XFER_UDMA_2)
			udma_mode &= ~(2 << (adev->devno * 4));
		अन्यथा /* UDMA 4 */
			udma_mode |= (2 << (adev->devno * 4));

		pci_ग_लिखो_config_byte(dev, 0x4A, udma_mode);

		udma_enable |= (1 << adev->devno);
	पूर्ण
	pci_ग_लिखो_config_word(dev, 0x40, ideपंचांग_data);
	pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);

	/* Track which port is configured */
	ap->निजी_data = adev;
पूर्ण

/**
 *	radisys_qc_issue	-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary. Our logic also clears TIME0/TIME1 क्रम the other device so
 *	that, even अगर we get this wrong, cycles to the other device will
 *	be made PIO0.
 */

अटल अचिन्हित पूर्णांक radisys_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	अगर (adev != ap->निजी_data) अणु
		/* UDMA timing is not shared */
		अगर (adev->dma_mode < XFER_UDMA_0) अणु
			अगर (adev->dma_mode)
				radisys_set_dmamode(ap, adev);
			अन्यथा अगर (adev->pio_mode)
				radisys_set_piomode(ap, adev);
		पूर्ण
	पूर्ण
	वापस ata_bmdma_qc_issue(qc);
पूर्ण


अटल काष्ठा scsi_host_ढाँचा radisys_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations radisys_pata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.qc_issue		= radisys_qc_issue,
	.cable_detect		= ata_cable_unknown,
	.set_piomode		= radisys_set_piomode,
	.set_dmamode		= radisys_set_dmamode,
पूर्ण;


/**
 *	radisys_init_one - Register PIIX ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in radisys_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.  We probe क्रम combined mode (sigh),
 *	and then hand over control to libata, क्रम it to करो the rest.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक radisys_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY,
		.udma_mask	= ATA_UDMA24_ONLY,
		.port_ops	= &radisys_pata_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &radisys_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id radisys_pci_tbl[] = अणु
	अणु PCI_VDEVICE(RADISYS, 0x8201), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver radisys_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= radisys_pci_tbl,
	.probe			= radisys_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(radisys_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for Radisys R82600 controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, radisys_pci_tbl);
MODULE_VERSION(DRV_VERSION);
