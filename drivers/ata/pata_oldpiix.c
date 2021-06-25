<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_oldpiix.c - Intel PATA/SATA controllers
 *
 *	(C) 2005 Red Hat
 *
 *    Some parts based on ata_piix.c by Jeff Garzik and others.
 *
 *    Early PIIX dअगरfers signअगरicantly from the later PIIX as it lacks
 *    SITRE and the slave timing रेजिस्टरs. This means that you have to
 *    set timing per channel, or be clever. Libata tells us whenever it
 *    करोes drive selection and we use this to reload the timings.
 *
 *    Because of these behaviour dअगरferences PIIX माला_लो its own driver module.
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

#घोषणा DRV_NAME	"pata_oldpiix"
#घोषणा DRV_VERSION	"0.5.5"

/**
 *	oldpiix_pre_reset		-	probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Set up cable type and use generic probe init
 */

अटल पूर्णांक oldpiix_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर काष्ठा pci_bits oldpiix_enable_bits[] = अणु
		अणु 0x41U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 0 */
		अणु 0x43U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 1 */
	पूर्ण;

	अगर (!pci_test_config_bits(pdev, &oldpiix_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	oldpiix_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device whose timings we are configuring
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम oldpiix_set_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio	= adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक ideपंचांग_port= ap->port_no ? 0x42 : 0x40;
	u16 ideपंचांग_data;
	पूर्णांक control = 0;

	/*
	 *	See Intel Document 298600-004 क्रम the timing programing rules
	 *	क्रम PIIX/ICH. Note that the early PIIX करोes not have the slave
	 *	timing port at 0x44.
	 */

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	अगर (pio > 1)
		control |= 1;	/* TIME */
	अगर (ata_pio_need_iordy(adev))
		control |= 2;	/* IE */

	/* Intel specअगरies that the prefetch/posting is क्रम disk only */
	अगर (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE */

	pci_पढ़ो_config_word(dev, ideपंचांग_port, &ideपंचांग_data);

	/*
	 * Set PPE, IE and TIME as appropriate.
	 * Clear the other drive's timing bits.
	 */
	अगर (adev->devno == 0) अणु
		ideपंचांग_data &= 0xCCE0;
		ideपंचांग_data |= control;
	पूर्ण अन्यथा अणु
		ideपंचांग_data &= 0xCC0E;
		ideपंचांग_data |= (control << 4);
	पूर्ण
	ideपंचांग_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	pci_ग_लिखो_config_word(dev, ideपंचांग_port, ideपंचांग_data);

	/* Track which port is configured */
	ap->निजी_data = adev;
पूर्ण

/**
 *	oldpiix_set_dmamode - Initialize host controller PATA DMA timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device to program
 *
 *	Set MWDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम oldpiix_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	u8 ideपंचांग_port		= ap->port_no ? 0x42 : 0x40;
	u16 ideपंचांग_data;

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	/*
	 * MWDMA is driven by the PIO timings. We must also enable
	 * IORDY unconditionally aदीर्घ with TIME1. PPE has alपढ़ोy
	 * been set when the PIO timing was set.
	 */

	अचिन्हित पूर्णांक mwdma	= adev->dma_mode - XFER_MW_DMA_0;
	अचिन्हित पूर्णांक control;
	स्थिर अचिन्हित पूर्णांक needed_pio[3] = अणु
		XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
	पूर्ण;
	पूर्णांक pio = needed_pio[mwdma] - XFER_PIO_0;

	pci_पढ़ो_config_word(dev, ideपंचांग_port, &ideपंचांग_data);

	control = 3;	/* IORDY|TIME0 */
	/* Intel specअगरies that the PPE functionality is क्रम disk only */
	अगर (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE enable */

	/* If the drive MWDMA is faster than it can करो PIO then
	   we must क्रमce PIO पूर्णांकo PIO0 */

	अगर (adev->pio_mode < needed_pio[mwdma])
		/* Enable DMA timing only */
		control |= 8;	/* PIO cycles in PIO0 */

	/* Mask out the relevant control and timing bits we will load. Also
	   clear the other drive TIME रेजिस्टर as a precaution */
	अगर (adev->devno == 0) अणु
		ideपंचांग_data &= 0xCCE0;
		ideपंचांग_data |= control;
	पूर्ण अन्यथा अणु
		ideपंचांग_data &= 0xCC0E;
		ideपंचांग_data |= (control << 4);
	पूर्ण
	ideपंचांग_data |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	pci_ग_लिखो_config_word(dev, ideपंचांग_port, ideपंचांग_data);

	/* Track which port is configured */
	ap->निजी_data = adev;
पूर्ण

/**
 *	oldpiix_qc_issue	-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary. Our logic also clears TIME0/TIME1 क्रम the other device so
 *	that, even अगर we get this wrong, cycles to the other device will
 *	be made PIO0.
 */

अटल अचिन्हित पूर्णांक oldpiix_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	अगर (adev != ap->निजी_data) अणु
		oldpiix_set_piomode(ap, adev);
		अगर (ata_dma_enabled(adev))
			oldpiix_set_dmamode(ap, adev);
	पूर्ण
	वापस ata_bmdma_qc_issue(qc);
पूर्ण


अटल काष्ठा scsi_host_ढाँचा oldpiix_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations oldpiix_pata_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.qc_issue		= oldpiix_qc_issue,
	.cable_detect		= ata_cable_40wire,
	.set_piomode		= oldpiix_set_piomode,
	.set_dmamode		= oldpiix_set_dmamode,
	.prereset		= oldpiix_pre_reset,
पूर्ण;


/**
 *	oldpiix_init_one - Register PIIX ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in oldpiix_pci_tbl matching with @pdev
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

अटल पूर्णांक oldpiix_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONLY,
		.port_ops	= &oldpiix_pata_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &oldpiix_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id oldpiix_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x1230), पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver oldpiix_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= oldpiix_pci_tbl,
	.probe			= oldpiix_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(oldpiix_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for early PIIX series controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, oldpiix_pci_tbl);
MODULE_VERSION(DRV_VERSION);
