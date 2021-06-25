<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_atiixp.c 	- ATI PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  (C) 2009-2010 Bartlomiej Zolnierkiewicz
 *
 * Based on
 *
 *  linux/drivers/ide/pci/atiixp.c	Version 0.01-bart2	Feb. 26, 2004
 *
 *  Copyright (C) 2003 ATI Inc. <hyu@ati.com>
 *  Copyright (C) 2004 Bartlomiej Zolnierkiewicz
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME "pata_atiixp"
#घोषणा DRV_VERSION "0.4.6"

क्रमागत अणु
	ATIIXP_IDE_PIO_TIMING	= 0x40,
	ATIIXP_IDE_MWDMA_TIMING	= 0x44,
	ATIIXP_IDE_PIO_CONTROL	= 0x48,
	ATIIXP_IDE_PIO_MODE	= 0x4a,
	ATIIXP_IDE_UDMA_CONTROL	= 0x54,
	ATIIXP_IDE_UDMA_MODE 	= 0x56
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id attixp_cable_override_dmi_table[] = अणु
	अणु
		/* Board has onboard PATA<->SATA converters */
		.ident = "MSI E350DM-E33",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "MSI"),
			DMI_MATCH(DMI_BOARD_NAME, "E350DM-E33(MS-7720)"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक atiixp_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 udma;

	अगर (dmi_check_प्रणाली(attixp_cable_override_dmi_table))
		वापस ATA_CBL_PATA40_SHORT;

	/* Hack from drivers/ide/pci. Really we want to know how to करो the
	   raw detection not play follow the bios mode guess */
	pci_पढ़ो_config_byte(pdev, ATIIXP_IDE_UDMA_MODE + ap->port_no, &udma);
	अगर ((udma & 0x07) >= 0x04 || (udma & 0x70) >= 0x40)
		वापस  ATA_CBL_PATA80;
	वापस ATA_CBL_PATA40;
पूर्ण

अटल DEFINE_SPINLOCK(atiixp_lock);

/**
 *	atiixp_prereset	-	perक्रमm reset handling
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Reset sequence checking enable bits to see which ports are
 *	active.
 */

अटल पूर्णांक atiixp_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits atiixp_enable_bits[] = अणु
		अणु 0x48, 1, 0x01, 0x00 पूर्ण,
		अणु 0x48, 1, 0x08, 0x00 पूर्ण
	पूर्ण;

	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &atiixp_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	atiixp_set_pio_timing	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@pio: Requested PIO
 *
 *	Called by both the pio and dma setup functions to set the controller
 *	timings क्रम PIO transfers. We must load both the mode number and
 *	timing values पूर्णांकo the controller.
 */

अटल व्योम atiixp_set_pio_timing(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक pio)
अणु
	अटल u8 pio_timings[5] = अणु 0x5D, 0x47, 0x34, 0x22, 0x20 पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक dn = 2 * ap->port_no + adev->devno;
	पूर्णांक timing_shअगरt = (16 * ap->port_no) + 8 * (adev->devno ^ 1);
	u32 pio_timing_data;
	u16 pio_mode_data;

	pci_पढ़ो_config_word(pdev, ATIIXP_IDE_PIO_MODE, &pio_mode_data);
	pio_mode_data &= ~(0x7 << (4 * dn));
	pio_mode_data |= pio << (4 * dn);
	pci_ग_लिखो_config_word(pdev, ATIIXP_IDE_PIO_MODE, pio_mode_data);

	pci_पढ़ो_config_dword(pdev, ATIIXP_IDE_PIO_TIMING, &pio_timing_data);
	pio_timing_data &= ~(0xFF << timing_shअगरt);
	pio_timing_data |= (pio_timings[pio] << timing_shअगरt);
	pci_ग_लिखो_config_dword(pdev, ATIIXP_IDE_PIO_TIMING, pio_timing_data);
पूर्ण

/**
 *	atiixp_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup. We use a shared helper क्रम this
 *	as the DMA setup must also adjust the PIO timing inक्रमmation.
 */

अटल व्योम atiixp_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&atiixp_lock, flags);
	atiixp_set_pio_timing(ap, adev, adev->pio_mode - XFER_PIO_0);
	spin_unlock_irqrestore(&atiixp_lock, flags);
पूर्ण

/**
 *	atiixp_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the DMA mode setup. We use timing tables क्रम most
 *	modes but must tune an appropriate PIO mode to match.
 */

अटल व्योम atiixp_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल u8 mwdma_timings[5] = अणु 0x77, 0x21, 0x20 पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक dma = adev->dma_mode;
	पूर्णांक dn = 2 * ap->port_no + adev->devno;
	पूर्णांक wanted_pio;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&atiixp_lock, flags);

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		u16 udma_mode_data;

		dma -= XFER_UDMA_0;

		pci_पढ़ो_config_word(pdev, ATIIXP_IDE_UDMA_MODE, &udma_mode_data);
		udma_mode_data &= ~(0x7 << (4 * dn));
		udma_mode_data |= dma << (4 * dn);
		pci_ग_लिखो_config_word(pdev, ATIIXP_IDE_UDMA_MODE, udma_mode_data);
	पूर्ण अन्यथा अणु
		पूर्णांक timing_shअगरt = (16 * ap->port_no) + 8 * (adev->devno ^ 1);
		u32 mwdma_timing_data;

		dma -= XFER_MW_DMA_0;

		pci_पढ़ो_config_dword(pdev, ATIIXP_IDE_MWDMA_TIMING,
				      &mwdma_timing_data);
		mwdma_timing_data &= ~(0xFF << timing_shअगरt);
		mwdma_timing_data |= (mwdma_timings[dma] << timing_shअगरt);
		pci_ग_लिखो_config_dword(pdev, ATIIXP_IDE_MWDMA_TIMING,
				       mwdma_timing_data);
	पूर्ण
	/*
	 *	We must now look at the PIO mode situation. We may need to
	 *	adjust the PIO mode to keep the timings acceptable
	 */
	अगर (adev->dma_mode >= XFER_MW_DMA_2)
		wanted_pio = 4;
	अन्यथा अगर (adev->dma_mode == XFER_MW_DMA_1)
		wanted_pio = 3;
	अन्यथा अगर (adev->dma_mode == XFER_MW_DMA_0)
		wanted_pio = 0;
	अन्यथा BUG();

	अगर (adev->pio_mode != wanted_pio)
		atiixp_set_pio_timing(ap, adev, wanted_pio);
	spin_unlock_irqrestore(&atiixp_lock, flags);
पूर्ण

/**
 *	atiixp_bmdma_start	-	DMA start callback
 *	@qc: Command in progress
 *
 *	When DMA begins we need to ensure that the UDMA control
 *	रेजिस्टर क्रम the channel is correctly set.
 *
 *	Note: The host lock held by the libata layer protects
 *	us from two channels both trying to set DMA bits at once
 */

अटल व्योम atiixp_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक dn = (2 * ap->port_no) + adev->devno;
	u16 पंचांगp16;

	pci_पढ़ो_config_word(pdev, ATIIXP_IDE_UDMA_CONTROL, &पंचांगp16);
	अगर (ata_using_udma(adev))
		पंचांगp16 |= (1 << dn);
	अन्यथा
		पंचांगp16 &= ~(1 << dn);
	pci_ग_लिखो_config_word(pdev, ATIIXP_IDE_UDMA_CONTROL, पंचांगp16);
	ata_bmdma_start(qc);
पूर्ण

/**
 *	atiixp_bmdma_stop	-	DMA stop callback
 *	@qc: Command in progress
 *
 *	DMA has completed. Clear the UDMA flag as the next operations will
 *	be PIO ones not UDMA data transfer.
 *
 *	Note: The host lock held by the libata layer protects
 *	us from two channels both trying to set DMA bits at once
 */

अटल व्योम atiixp_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक dn = (2 * ap->port_no) + qc->dev->devno;
	u16 पंचांगp16;

	pci_पढ़ो_config_word(pdev, ATIIXP_IDE_UDMA_CONTROL, &पंचांगp16);
	पंचांगp16 &= ~(1 << dn);
	pci_ग_लिखो_config_word(pdev, ATIIXP_IDE_UDMA_CONTROL, पंचांगp16);
	ata_bmdma_stop(qc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा atiixp_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.sg_tablesize		= LIBATA_DUMB_MAX_PRD,
पूर्ण;

अटल काष्ठा ata_port_operations atiixp_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.qc_prep 	= ata_bmdma_dumb_qc_prep,
	.bmdma_start 	= atiixp_bmdma_start,
	.bmdma_stop	= atiixp_bmdma_stop,

	.prereset	= atiixp_prereset,
	.cable_detect	= atiixp_cable_detect,
	.set_piomode	= atiixp_set_piomode,
	.set_dmamode	= atiixp_set_dmamode,
पूर्ण;

अटल पूर्णांक atiixp_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA12_ONLY,
		.udma_mask = ATA_UDMA5,
		.port_ops = &atiixp_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &info पूर्ण;

	/* SB600 करोesn't have secondary port wired */
	अगर (pdev->device == PCI_DEVICE_ID_ATI_IXP600_IDE)
		ppi[1] = &ata_dummy_port_info;

	वापस ata_pci_bmdma_init_one(pdev, ppi, &atiixp_sht, शून्य,
				      ATA_HOST_PARALLEL_SCAN);
पूर्ण

अटल स्थिर काष्ठा pci_device_id atiixp[] = अणु
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP200_IDE), पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP300_IDE), पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP400_IDE), पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP600_IDE), पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP700_IDE), पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_HUDSON2_IDE), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver atiixp_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= atiixp,
	.probe 		= atiixp_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.resume		= ata_pci_device_resume,
	.suspend	= ata_pci_device_suspend,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(atiixp_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for ATI IXP200/300/400");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, atiixp);
MODULE_VERSION(DRV_VERSION);
