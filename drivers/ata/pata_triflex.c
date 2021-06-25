<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_trअगरlex.c 	- Compaq PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * based upon
 *
 * trअगरlex.c
 *
 * IDE Chipset driver क्रम the Compaq TriFlex IDE controller.
 *
 * Known to work with the Compaq Workstation 5x00 series.
 *
 * Copyright (C) 2002 Hewlett-Packard Development Group, L.P.
 * Author: Torben Mathiasen <torben.mathiasen@hp.com>
 *
 * Loosely based on the piix & svwks drivers.
 *
 * Documentation:
 *	Not खुलाly available.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_triflex"
#घोषणा DRV_VERSION "0.2.8"

/**
 *	trअगरlex_prereset		-	probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Set up cable type and use generic probe init
 */

अटल पूर्णांक trअगरlex_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits trअगरlex_enable_bits[] = अणु
		अणु 0x80, 1, 0x01, 0x01 पूर्ण,
		अणु 0x80, 1, 0x02, 0x02 पूर्ण
	पूर्ण;

	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &trअगरlex_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण



/**
 *	trअगरlex_load_timing		-	timing configuration
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device on the bus
 *	@speed: speed to configure
 *
 *	The Trअगरlex has one set of timings per device per channel. This
 *	means we must करो some चयनing. As the PIO and DMA timings करोn't
 *	match we have to करो some reloading unlike PIIX devices where tuning
 *	tricks can aव्योम it.
 */

अटल व्योम trअगरlex_load_timing(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक speed)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 timing = 0;
	u32 trअगरlex_timing, old_trअगरlex_timing;
	पूर्णांक channel_offset = ap->port_no ? 0x74: 0x70;
	अचिन्हित पूर्णांक is_slave	= (adev->devno != 0);


	pci_पढ़ो_config_dword(pdev, channel_offset, &old_trअगरlex_timing);
	trअगरlex_timing = old_trअगरlex_timing;

	चयन(speed)
	अणु
		हाल XFER_MW_DMA_2:
			timing = 0x0103;अवरोध;
		हाल XFER_MW_DMA_1:
			timing = 0x0203;अवरोध;
		हाल XFER_MW_DMA_0:
			timing = 0x0808;अवरोध;
		हाल XFER_SW_DMA_2:
		हाल XFER_SW_DMA_1:
		हाल XFER_SW_DMA_0:
			timing = 0x0F0F;अवरोध;
		हाल XFER_PIO_4:
			timing = 0x0202;अवरोध;
		हाल XFER_PIO_3:
			timing = 0x0204;अवरोध;
		हाल XFER_PIO_2:
			timing = 0x0404;अवरोध;
		हाल XFER_PIO_1:
			timing = 0x0508;अवरोध;
		हाल XFER_PIO_0:
			timing = 0x0808;अवरोध;
		शेष:
			BUG();
	पूर्ण
	trअगरlex_timing &= ~ (0xFFFF << (16 * is_slave));
	trअगरlex_timing |= (timing << (16 * is_slave));

	अगर (trअगरlex_timing != old_trअगरlex_timing)
		pci_ग_लिखो_config_dword(pdev, channel_offset, trअगरlex_timing);
पूर्ण

/**
 *	trअगरlex_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Use the timing loader to set up the PIO mode. We have to करो this
 *	because DMA start/stop will only be called once DMA occurs. If there
 *	has been no DMA then the PIO timings are still needed.
 */
अटल व्योम trअगरlex_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	trअगरlex_load_timing(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	trअगरlex_bmdma_start	-	DMA start callback
 *	@qc: Command in progress
 *
 *	Usually drivers set the DMA timing at the poपूर्णांक the set_dmamode call
 *	is made. Trअगरlex however requires we load new timings on the
 *	transition or keep matching PIO/DMA pairs (ie MWDMA2/PIO4 etc).
 *	We load the DMA timings just beक्रमe starting DMA and then restore
 *	the PIO timing when the DMA is finished.
 */

अटल व्योम trअगरlex_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	trअगरlex_load_timing(qc->ap, qc->dev, qc->dev->dma_mode);
	ata_bmdma_start(qc);
पूर्ण

/**
 *	trअगरlex_bmdma_stop	-	DMA stop callback
 *	@qc: ATA command
 *
 *	We loaded new timings in dma_start, as a result we need to restore
 *	the PIO timings in dma_stop so that the next command issue माला_लो the
 *	right घड़ी values.
 */

अटल व्योम trअगरlex_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	ata_bmdma_stop(qc);
	trअगरlex_load_timing(qc->ap, qc->dev, qc->dev->pio_mode);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा trअगरlex_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations trअगरlex_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.bmdma_start 	= trअगरlex_bmdma_start,
	.bmdma_stop	= trअगरlex_bmdma_stop,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= trअगरlex_set_piomode,
	.prereset	= trअगरlex_prereset,
पूर्ण;

अटल पूर्णांक trअगरlex_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &trअगरlex_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	ata_prपूर्णांक_version_once(&dev->dev, DRV_VERSION);

	वापस ata_pci_bmdma_init_one(dev, ppi, &trअगरlex_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id trअगरlex[] = अणु
	अणु PCI_VDEVICE(COMPAQ, PCI_DEVICE_ID_COMPAQ_TRIFLEX_IDE), पूर्ण,

	अणु पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक trअगरlex_ata_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc = 0;

	rc = ata_host_suspend(host, mesg);
	अगर (rc)
		वापस rc;

	/*
	 * We must not disable or घातerकरोwn the device.
	 * APM bios refuses to suspend अगर IDE is not accessible.
	 */
	pci_save_state(pdev);

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल काष्ठा pci_driver trअगरlex_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= trअगरlex,
	.probe 		= trअगरlex_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= trअगरlex_ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(trअगरlex_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Compaq Triflex");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, trअगरlex);
MODULE_VERSION(DRV_VERSION);
