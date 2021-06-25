<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * New ATA layer SC1200 driver		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * TODO: Mode selection filtering
 * TODO: Needs custom DMA cleanup code
 *
 * Based very heavily on
 *
 * linux/drivers/ide/pci/sc1200.c		Version 0.91	28-Jan-2003
 *
 * Copyright (C) 2000-2002		Mark Lord <mlord@pobox.com>
 * May be copied or modअगरied under the terms of the GNU General Public License
 *
 * Development of this chipset driver was funded
 * by the nice folks at National Semiconductor.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_sc1200"
#घोषणा DRV_VERSION	"0.2.6"

#घोषणा SC1200_REV_A	0x00
#घोषणा SC1200_REV_B1	0x01
#घोषणा SC1200_REV_B3	0x02
#घोषणा SC1200_REV_C1	0x03
#घोषणा SC1200_REV_D1	0x04

/**
 *	sc1200_घड़ी	-	PCI घड़ी
 *
 *	Return the PCI bus घड़ीing क्रम the SC1200 chipset configuration
 *	in use. We वापस 0 क्रम 33MHz 1 क्रम 48MHz and 2 क्रम 66Mhz
 */

अटल पूर्णांक sc1200_घड़ी(व्योम)
अणु
	/* Magic रेजिस्टरs that give us the chipset data */
	u8 chip_id = inb(0x903C);
	u8 silicon_rev = inb(0x903D);
	u16 pci_घड़ी;

	अगर (chip_id == 0x04 && silicon_rev < SC1200_REV_B1)
		वापस 0;	/* 33 MHz mode */

	/* Clock generator configuration 0x901E its 8/9 are the PCI घड़ीing
	   0/3 is 33Mhz 1 is 48 2 is 66 */

	pci_घड़ी = inw(0x901E);
	pci_घड़ी >>= 8;
	pci_घड़ी &= 0x03;
	अगर (pci_घड़ी == 3)
		pci_घड़ी = 0;
	वापस pci_घड़ी;
पूर्ण

/**
 *	sc1200_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Set our PIO requirements. This is fairly simple on the SC1200
 */

अटल व्योम sc1200_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u32 pio_timings[4][5] = अणु
		/* क्रमmat0, 33Mhz */
		अणु 0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010 पूर्ण,
		/* क्रमmat1, 33Mhz */
		अणु 0xd1329172, 0x71212171, 0x30200080, 0x20102010, 0x00100010 पूर्ण,
		/* क्रमmat1, 48Mhz */
		अणु 0xfaa3f4f3, 0xc23232b2, 0x513101c1, 0x31213121, 0x10211021 पूर्ण,
		/* क्रमmat1, 66Mhz */
		अणु 0xfff4fff4, 0xf35353d3, 0x814102f1, 0x42314231, 0x11311131 पूर्ण
	पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 क्रमmat;
	अचिन्हित पूर्णांक reg = 0x40 + 0x10 * ap->port_no;
	पूर्णांक mode = adev->pio_mode - XFER_PIO_0;

	pci_पढ़ो_config_dword(pdev, reg + 4, &क्रमmat);
	क्रमmat >>= 31;
	क्रमmat += sc1200_घड़ी();
	pci_ग_लिखो_config_dword(pdev, reg + 8 * adev->devno,
				pio_timings[क्रमmat][mode]);
पूर्ण

/**
 *	sc1200_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	We cannot mix MWDMA and UDMA without reloading timings each चयन
 *	master to slave.
 */

अटल व्योम sc1200_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u32 udma_timing[3][3] = अणु
		अणु 0x00921250, 0x00911140, 0x00911030 पूर्ण,
		अणु 0x00932470, 0x00922260, 0x00922140 पूर्ण,
		अणु 0x009436A1, 0x00933481, 0x00923261 पूर्ण
	पूर्ण;

	अटल स्थिर u32 mwdma_timing[3][3] = अणु
		अणु 0x00077771, 0x00012121, 0x00002020 पूर्ण,
		अणु 0x000BBBB2, 0x00024241, 0x00013131 पूर्ण,
		अणु 0x000FFFF3, 0x00035352, 0x00015151 पूर्ण
	पूर्ण;

	पूर्णांक घड़ी = sc1200_घड़ी();
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक reg = 0x40 + 0x10 * ap->port_no;
	पूर्णांक mode = adev->dma_mode;
	u32 क्रमmat;

	अगर (mode >= XFER_UDMA_0)
		क्रमmat = udma_timing[घड़ी][mode - XFER_UDMA_0];
	अन्यथा
		क्रमmat = mwdma_timing[घड़ी][mode - XFER_MW_DMA_0];

	अगर (adev->devno == 0) अणु
		u32 timings;

		pci_पढ़ो_config_dword(pdev, reg + 4, &timings);
		timings &= 0x80000000UL;
		timings |= क्रमmat;
		pci_ग_लिखो_config_dword(pdev, reg + 4, timings);
	पूर्ण अन्यथा
		pci_ग_लिखो_config_dword(pdev, reg + 12, क्रमmat);
पूर्ण

/**
 *	sc1200_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary.  Specअगरically we have a problem that there is only
 *	one MWDMA/UDMA bit.
 */

अटल अचिन्हित पूर्णांक sc1200_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा ata_device *prev = ap->निजी_data;

	/* See अगर the DMA settings could be wrong */
	अगर (ata_dma_enabled(adev) && adev != prev && prev != शून्य) अणु
		/* Maybe, but करो the channels match MWDMA/UDMA ? */
		अगर ((ata_using_udma(adev) && !ata_using_udma(prev)) ||
		    (ata_using_udma(prev) && !ata_using_udma(adev)))
		    	/* Switch the mode bits */
		    	sc1200_set_dmamode(ap, adev);
	पूर्ण

	वापस ata_bmdma_qc_issue(qc);
पूर्ण

/**
 *	sc1200_qc_defer	-	implement serialization
 *	@qc: command
 *
 *	Serialize command issue on this controller.
 */

अटल पूर्णांक sc1200_qc_defer(काष्ठा ata_queued_cmd *qc)
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

अटल काष्ठा scsi_host_ढाँचा sc1200_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.sg_tablesize	= LIBATA_DUMB_MAX_PRD,
पूर्ण;

अटल काष्ठा ata_port_operations sc1200_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.qc_prep 	= ata_bmdma_dumb_qc_prep,
	.qc_issue	= sc1200_qc_issue,
	.qc_defer	= sc1200_qc_defer,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= sc1200_set_piomode,
	.set_dmamode	= sc1200_set_dmamode,
पूर्ण;

/**
 *	sc1200_init_one		-	Initialise an SC1200
 *	@dev: PCI device
 *	@id: Entry in match table
 *
 *	Just throw the needed data at the libata helper and it करोes all
 *	our work.
 */

अटल पूर्णांक sc1200_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.port_ops = &sc1200_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	वापस ata_pci_bmdma_init_one(dev, ppi, &sc1200_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id sc1200[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SCx200_IDE), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver sc1200_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= sc1200,
	.probe 		= sc1200_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(sc1200_pci_driver);

MODULE_AUTHOR("Alan Cox, Mark Lord");
MODULE_DESCRIPTION("low-level driver for the NS/AMD SC1200");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, sc1200);
MODULE_VERSION(DRV_VERSION);
