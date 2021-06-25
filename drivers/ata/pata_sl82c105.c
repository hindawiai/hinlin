<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_sl82c105.c 	- SL82C105 PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  (C) 2011 Bartlomiej Zolnierkiewicz
 *
 * Based in part on linux/drivers/ide/pci/sl82c105.c
 * 		SL82C105/Winbond 553 IDE driver
 *
 * and in part on the करोcumentation and errata sheet
 *
 *
 * Note: The controller like many controllers has shared timings क्रम
 * PIO and DMA. We thus flip to the DMA timings in dma_start and flip back
 * in the dma_stop function. Thus we actually करोn't need a set_dmamode
 * method as the PIO method is always called and will set the right PIO
 * timing parameters.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_sl82c105"
#घोषणा DRV_VERSION "0.3.3"

क्रमागत अणु
	/*
	 * SL82C105 PCI config रेजिस्टर 0x40 bits.
	 */
	CTRL_IDE_IRQB	=	(1 << 30),
	CTRL_IDE_IRQA   =	(1 << 28),
	CTRL_LEGIRQ     =	(1 << 11),
	CTRL_P1F16      =	(1 << 5),
	CTRL_P1EN       =	(1 << 4),
	CTRL_P0F16      =	(1 << 1),
	CTRL_P0EN       =	(1 << 0)
पूर्ण;

/**
 *	sl82c105_pre_reset		-	probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Set up cable type and use generic probe init
 */

अटल पूर्णांक sl82c105_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits sl82c105_enable_bits[] = अणु
		अणु 0x40, 1, 0x01, 0x01 पूर्ण,
		अणु 0x40, 1, 0x10, 0x10 पूर्ण
	पूर्ण;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (ap->port_no && !pci_test_config_bits(pdev, &sl82c105_enable_bits[ap->port_no]))
		वापस -ENOENT;
	वापस ata_sff_prereset(link, deadline);
पूर्ण


/**
 *	sl82c105_configure_piomode	-	set chip PIO timing
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@pio: PIO mode
 *
 *	Called to करो the PIO mode setup. Our timing रेजिस्टरs are shared
 *	so a configure_dmamode call will unकरो any work we करो here and vice
 *	versa
 */

अटल व्योम sl82c105_configure_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक pio)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल u16 pio_timing[5] = अणु
		0x50D, 0x407, 0x304, 0x242, 0x240
	पूर्ण;
	u16 dummy;
	पूर्णांक timing = 0x44 + (8 * ap->port_no) + (4 * adev->devno);

	pci_ग_लिखो_config_word(pdev, timing, pio_timing[pio]);
	/* Can we lose this oddity of the old driver */
	pci_पढ़ो_config_word(pdev, timing, &dummy);
पूर्ण

/**
 *	sl82c105_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup. Our timing रेजिस्टरs are shared
 *	but we want to set the PIO timing by शेष.
 */

अटल व्योम sl82c105_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	sl82c105_configure_piomode(ap, adev, adev->pio_mode - XFER_PIO_0);
पूर्ण

/**
 *	sl82c105_configure_dmamode	-	set DMA mode in chip
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Load DMA cycle बार पूर्णांकo the chip पढ़ोy क्रम a DMA transfer
 *	to occur.
 */

अटल व्योम sl82c105_configure_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल u16 dma_timing[3] = अणु
		0x707, 0x201, 0x200
	पूर्ण;
	u16 dummy;
	पूर्णांक timing = 0x44 + (8 * ap->port_no) + (4 * adev->devno);
	पूर्णांक dma = adev->dma_mode - XFER_MW_DMA_0;

	pci_ग_लिखो_config_word(pdev, timing, dma_timing[dma]);
	/* Can we lose this oddity of the old driver */
	pci_पढ़ो_config_word(pdev, timing, &dummy);
पूर्ण

/**
 *	sl82c105_reset_engine	-	Reset the DMA engine
 *	@ap: ATA पूर्णांकerface
 *
 *	The sl82c105 has some serious problems with the DMA engine
 *	when transfers करोn't run as expected or ATAPI is used. The
 *	recommended fix is to reset the engine each use using a chip
 *	test रेजिस्टर.
 */

अटल व्योम sl82c105_reset_engine(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 val;

	pci_पढ़ो_config_word(pdev, 0x7E, &val);
	pci_ग_लिखो_config_word(pdev, 0x7E, val | 4);
	pci_ग_लिखो_config_word(pdev, 0x7E, val & ~4);
पूर्ण

/**
 *	sl82c105_bmdma_start		-	DMA engine begin
 *	@qc: ATA command
 *
 *	Reset the DMA engine each use as recommended by the errata
 *	करोcument.
 *
 *	FIXME: अगर we चयन घड़ी at BMDMA start/end we might get better
 *	PIO perक्रमmance on DMA capable devices.
 */

अटल व्योम sl82c105_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	udelay(100);
	sl82c105_reset_engine(ap);
	udelay(100);

	/* Set the घड़ीs क्रम DMA */
	sl82c105_configure_dmamode(ap, qc->dev);
	/* Activate DMA */
	ata_bmdma_start(qc);
पूर्ण

/**
 *	sl82c105_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Reset the DMA engine each use as recommended by the errata
 *	करोcument.
 *
 *	This function is also called to turn off DMA when a समयout occurs
 *	during DMA operation. In both हालs we need to reset the engine,
 *	so no actual eng_समयout handler is required.
 *
 *	We assume bmdma_stop is always called अगर bmdma_start as called. If
 *	not then we may need to wrap qc_issue.
 */

अटल व्योम sl82c105_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;

	ata_bmdma_stop(qc);
	sl82c105_reset_engine(ap);
	udelay(100);

	/* This will reकरो the initial setup of the DMA device to matching
	   PIO timings */
	sl82c105_set_piomode(ap, qc->dev);
पूर्ण

/**
 *	sl82c105_qc_defer	-	implement serialization
 *	@qc: command
 *
 *	We must issue one command per host not per channel because
 *	of the reset bug.
 *
 *	Q: is the scsi host lock sufficient ?
 */

अटल पूर्णांक sl82c105_qc_defer(काष्ठा ata_queued_cmd *qc)
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

अटल bool sl82c105_sff_irq_check(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u32 val, mask		= ap->port_no ? CTRL_IDE_IRQB : CTRL_IDE_IRQA;

	pci_पढ़ो_config_dword(pdev, 0x40, &val);

	वापस val & mask;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sl82c105_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations sl82c105_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.qc_defer	= sl82c105_qc_defer,
	.bmdma_start 	= sl82c105_bmdma_start,
	.bmdma_stop	= sl82c105_bmdma_stop,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= sl82c105_set_piomode,
	.prereset	= sl82c105_pre_reset,
	.sff_irq_check	= sl82c105_sff_irq_check,
पूर्ण;

/**
 *	sl82c105_bridge_revision	-	find bridge version
 *	@pdev: PCI device क्रम the ATA function
 *
 *	Locates the PCI bridge associated with the ATA function and
 *	providing it is a Winbond 553 reports the revision. If it cannot
 *	find a revision or the right device it वापसs -1
 */

अटल पूर्णांक sl82c105_bridge_revision(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *bridge;

	/*
	 * The bridge should be part of the same device, but function 0.
	 */
	bridge = pci_get_slot(pdev->bus,
			       PCI_DEVFN(PCI_SLOT(pdev->devfn), 0));
	अगर (!bridge)
		वापस -1;

	/*
	 * Make sure it is a Winbond 553 and is an ISA bridge.
	 */
	अगर (bridge->venकरोr != PCI_VENDOR_ID_WINBOND ||
	    bridge->device != PCI_DEVICE_ID_WINBOND_83C553 ||
	    bridge->class >> 8 != PCI_CLASS_BRIDGE_ISA) अणु
	    	pci_dev_put(bridge);
		वापस -1;
	पूर्ण
	/*
	 * We need to find function 0's revision, not function 1
	 */
	pci_dev_put(bridge);
	वापस bridge->revision;
पूर्ण

अटल व्योम sl82c105_fixup(काष्ठा pci_dev *pdev)
अणु
	u32 val;

	pci_पढ़ो_config_dword(pdev, 0x40, &val);
	val |= CTRL_P0EN | CTRL_P0F16 | CTRL_P1F16;
	pci_ग_लिखो_config_dword(pdev, 0x40, val);
पूर्ण

अटल पूर्णांक sl82c105_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info_dma = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &sl82c105_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_early = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &sl82c105_port_ops
	पूर्ण;
	/* क्रम now use only the first port */
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info_early,
					       शून्य पूर्ण;
	पूर्णांक rev;
	पूर्णांक rc;

	rc = pcim_enable_device(dev);
	अगर (rc)
		वापस rc;

	rev = sl82c105_bridge_revision(dev);

	अगर (rev == -1)
		dev_warn(&dev->dev,
			 "pata_sl82c105: Unable to find bridge, disabling DMA\n");
	अन्यथा अगर (rev <= 5)
		dev_warn(&dev->dev,
			 "pata_sl82c105: Early bridge revision, no DMA available\n");
	अन्यथा
		ppi[0] = &info_dma;

	sl82c105_fixup(dev);

	वापस ata_pci_bmdma_init_one(dev, ppi, &sl82c105_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sl82c105_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	sl82c105_fixup(pdev);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id sl82c105[] = अणु
	अणु PCI_VDEVICE(WINBOND, PCI_DEVICE_ID_WINBOND_82C105), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver sl82c105_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= sl82c105,
	.probe 		= sl82c105_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= sl82c105_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(sl82c105_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Sl82c105");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sl82c105);
MODULE_VERSION(DRV_VERSION);
