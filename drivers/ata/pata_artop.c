<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_artop.c - ARTOP ATA controller driver
 *
 *	(C) 2006 Red Hat
 *	(C) 2007,2011 Bartlomiej Zolnierkiewicz
 *
 *    Based in part on drivers/ide/pci/aec62xx.c
 *	Copyright (C) 1999-2002	Andre Hedrick <andre@linux-ide.org>
 *	865/865R fixes क्रम Macपूर्णांकosh card version from a patch to the old
 *		driver by Thibaut VARENE <varenet@parisc-linux.org>
 *	When setting the PCI latency we must set 0x80 or higher क्रम burst
 *		perक्रमmance Alessandro Zummo <alessandro.zummo@towertech.it>
 *
 *	TODO
 *	Investigate no_dsc on 850R
 *	Clock detect
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

#घोषणा DRV_NAME	"pata_artop"
#घोषणा DRV_VERSION	"0.4.6"

/*
 *	The ARTOP has 33 Mhz and "over clocked" timing tables. Until we
 *	get PCI bus speed functionality we leave this as 0. Its a variable
 *	क्रम when we get the functionality and also क्रम folks wanting to
 *	test stuff.
 */

अटल पूर्णांक घड़ी = 0;

/**
 *	artop62x0_pre_reset	-	probe begin
 *	@link: link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Nothing complicated needed here.
 */

अटल पूर्णांक artop62x0_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits artop_enable_bits[] = अणु
		अणु 0x4AU, 1U, 0x02UL, 0x02UL पूर्ण,	/* port 0 */
		अणु 0x4AU, 1U, 0x04UL, 0x04UL पूर्ण,	/* port 1 */
	पूर्ण;

	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	/* Odd numbered device ids are the units with enable bits. */
	अगर ((pdev->device & 1) &&
	    !pci_test_config_bits(pdev, &artop_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	artop6260_cable_detect	-	identअगरy cable type
 *	@ap: Port
 *
 *	Identअगरy the cable type क्रम the ARTOP पूर्णांकerface in question
 */

अटल पूर्णांक artop6260_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 पंचांगp;
	pci_पढ़ो_config_byte(pdev, 0x49, &पंचांगp);
	अगर (पंचांगp & (1 << ap->port_no))
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	artop6210_load_piomode - Load a set of PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device
 *	@pio: PIO mode
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. This
 *	is used both to set PIO timings in PIO mode and also to set the
 *	matching PIO घड़ीing क्रम UDMA, as well as the MWDMA timings.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम artop6210_load_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev, अचिन्हित पूर्णांक pio)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	पूर्णांक dn = adev->devno + 2 * ap->port_no;
	अटल स्थिर u16 timing[2][5] = अणु
		अणु 0x0000, 0x000A, 0x0008, 0x0303, 0x0301 पूर्ण,
		अणु 0x0700, 0x070A, 0x0708, 0x0403, 0x0401 पूर्ण

	पूर्ण;
	/* Load the PIO timing active/recovery bits */
	pci_ग_लिखो_config_word(pdev, 0x40 + 2 * dn, timing[घड़ी][pio]);
पूर्ण

/**
 *	artop6210_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. For
 *	ARTOP we must also clear the UDMA bits अगर we are not करोing UDMA. In
 *	the event UDMA is used the later call to set_dmamode will set the
 *	bits as required.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम artop6210_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	पूर्णांक dn = adev->devno + 2 * ap->port_no;
	u8 ultra;

	artop6210_load_piomode(ap, adev, adev->pio_mode - XFER_PIO_0);

	/* Clear the UDMA mode bits (set_dmamode will reकरो this अगर needed) */
	pci_पढ़ो_config_byte(pdev, 0x54, &ultra);
	ultra &= ~(3 << (2 * dn));
	pci_ग_लिखो_config_byte(pdev, 0x54, ultra);
पूर्ण

/**
 *	artop6260_load_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring
 *	@pio: PIO mode
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. The
 *	ARTOP6260 and relatives store the timing data dअगरferently.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम artop6260_load_piomode (काष्ठा ata_port *ap, काष्ठा ata_device *adev, अचिन्हित पूर्णांक pio)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	पूर्णांक dn = adev->devno + 2 * ap->port_no;
	अटल स्थिर u8 timing[2][5] = अणु
		अणु 0x00, 0x0A, 0x08, 0x33, 0x31 पूर्ण,
		अणु 0x70, 0x7A, 0x78, 0x43, 0x41 पूर्ण

	पूर्ण;
	/* Load the PIO timing active/recovery bits */
	pci_ग_लिखो_config_byte(pdev, 0x40 + dn, timing[घड़ी][pio]);
पूर्ण

/**
 *	artop6260_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring
 *
 *	Set PIO mode क्रम device, in host controller PCI config space. For
 *	ARTOP we must also clear the UDMA bits अगर we are not करोing UDMA. In
 *	the event UDMA is used the later call to set_dmamode will set the
 *	bits as required.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम artop6260_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u8 ultra;

	artop6260_load_piomode(ap, adev, adev->pio_mode - XFER_PIO_0);

	/* Clear the UDMA mode bits (set_dmamode will reकरो this अगर needed) */
	pci_पढ़ो_config_byte(pdev, 0x44 + ap->port_no, &ultra);
	ultra &= ~(7 << (4  * adev->devno));	/* One nibble per drive */
	pci_ग_लिखो_config_byte(pdev, 0x44 + ap->port_no, ultra);
पूर्ण

/**
 *	artop6210_set_dmamode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device whose timings we are configuring
 *
 *	Set DMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम artop6210_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio;
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	पूर्णांक dn = adev->devno + 2 * ap->port_no;
	u8 ultra;

	अगर (adev->dma_mode == XFER_MW_DMA_0)
		pio = 1;
	अन्यथा
		pio = 4;

	/* Load the PIO timing active/recovery bits */
	artop6210_load_piomode(ap, adev, pio);

	pci_पढ़ो_config_byte(pdev, 0x54, &ultra);
	ultra &= ~(3 << (2 * dn));

	/* Add ultra DMA bits अगर in UDMA mode */
	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		u8 mode = (adev->dma_mode - XFER_UDMA_0) + 1 - घड़ी;
		अगर (mode == 0)
			mode = 1;
		ultra |= (mode << (2 * dn));
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, 0x54, ultra);
पूर्ण

/**
 *	artop6260_set_dmamode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Device we are configuring
 *
 *	Set DMA mode क्रम device, in host controller PCI config space. The
 *	ARTOP6260 and relatives store the timing data dअगरferently.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम artop6260_set_dmamode (काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio;
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u8 ultra;

	अगर (adev->dma_mode == XFER_MW_DMA_0)
		pio = 1;
	अन्यथा
		pio = 4;

	/* Load the PIO timing active/recovery bits */
	artop6260_load_piomode(ap, adev, pio);

	/* Add ultra DMA bits अगर in UDMA mode */
	pci_पढ़ो_config_byte(pdev, 0x44 + ap->port_no, &ultra);
	ultra &= ~(7 << (4  * adev->devno));	/* One nibble per drive */
	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		u8 mode = adev->dma_mode - XFER_UDMA_0 + 1 - घड़ी;
		अगर (mode == 0)
			mode = 1;
		ultra |= (mode << (4 * adev->devno));
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, 0x44 + ap->port_no, ultra);
पूर्ण

/**
 *	artop6210_qc_defer	-	implement serialization
 *	@qc: command
 *
 *	Issue commands per host on this chip.
 */

अटल पूर्णांक artop6210_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_host *host = qc->ap->host;
	काष्ठा ata_port *alt = host->ports[1 ^ qc->ap->port_no];
	पूर्णांक rc;

	/* First apply the usual rules */
	rc = ata_std_qc_defer(qc);
	अगर (rc != 0)
		वापस rc;

	/* Now apply serialization rules. Only allow a command अगर the
	   other channel state machine is idle */
	अगर (alt && alt->qc_active)
		वापस	ATA_DEFER_PORT;
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा artop_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations artop6210_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= ata_cable_40wire,
	.set_piomode		= artop6210_set_piomode,
	.set_dmamode		= artop6210_set_dmamode,
	.prereset		= artop62x0_pre_reset,
	.qc_defer		= artop6210_qc_defer,
पूर्ण;

अटल काष्ठा ata_port_operations artop6260_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= artop6260_cable_detect,
	.set_piomode		= artop6260_set_piomode,
	.set_dmamode		= artop6260_set_dmamode,
	.prereset		= artop62x0_pre_reset,
पूर्ण;

अटल व्योम atp8xx_fixup(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->device == 0x0005)
		/* BIOS may have left us in UDMA, clear it beक्रमe libata probe */
		pci_ग_लिखो_config_byte(pdev, 0x54, 0);
	अन्यथा अगर (pdev->device == 0x0008 || pdev->device == 0x0009) अणु
		u8 reg;

		/* Mac प्रणालीs come up with some रेजिस्टरs not set as we
		   will need them */

		/* Clear reset & test bits */
		pci_पढ़ो_config_byte(pdev, 0x49, &reg);
		pci_ग_लिखो_config_byte(pdev, 0x49, reg & ~0x30);

		/* PCI latency must be > 0x80 क्रम burst mode, tweak it
		 * अगर required.
		 */
		pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &reg);
		अगर (reg <= 0x80)
			pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x90);

		/* Enable IRQ output and burst mode */
		pci_पढ़ो_config_byte(pdev, 0x4a, &reg);
		pci_ग_लिखो_config_byte(pdev, 0x4a, (reg & ~0x01) | 0x80);
	पूर्ण
पूर्ण

/**
 *	artop_init_one - Register ARTOP ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@id: PCI device ID
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक artop_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info_6210 = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA2,
		.port_ops	= &artop6210_ops,
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_626x = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA4,
		.port_ops	= &artop6260_ops,
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_628x = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5,
		.port_ops	= &artop6260_ops,
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_628x_fast = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA6,
		.port_ops	= &artop6260_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (id->driver_data == 0)	/* 6210 variant */
		ppi[0] = &info_6210;
	अन्यथा अगर (id->driver_data == 1)	/* 6260 */
		ppi[0] = &info_626x;
	अन्यथा अगर (id->driver_data == 2)	अणु /* 6280 or 6280 + fast */
		अचिन्हित दीर्घ io = pci_resource_start(pdev, 4);

		ppi[0] = &info_628x;
		अगर (inb(io) & 0x10)
			ppi[0] = &info_628x_fast;
	पूर्ण

	BUG_ON(ppi[0] == शून्य);

	atp8xx_fixup(pdev);

	वापस ata_pci_bmdma_init_one(pdev, ppi, &artop_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id artop_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ARTOP, 0x0005), 0 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, 0x0006), 1 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, 0x0007), 1 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, 0x0008), 2 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, 0x0009), 2 पूर्ण,

	अणु पूर्ण	/* terminate list */
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक atp8xx_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	atp8xx_fixup(pdev);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pci_driver artop_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= artop_pci_tbl,
	.probe			= artop_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= atp8xx_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(artop_pci_driver);

MODULE_AUTHOR("Alan Cox, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("SCSI low-level driver for ARTOP PATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, artop_pci_tbl);
MODULE_VERSION(DRV_VERSION);
