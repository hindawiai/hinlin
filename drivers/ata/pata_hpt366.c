<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Libata driver क्रम the highpoपूर्णांक 366 and 368 UDMA66 ATA controllers.
 *
 * This driver is heavily based upon:
 *
 * linux/drivers/ide/pci/hpt366.c		Version 0.36	April 25, 2003
 *
 * Copyright (C) 1999-2003		Andre Hedrick <andre@linux-ide.org>
 * Portions Copyright (C) 2001	        Sun Microप्रणालीs, Inc.
 * Portions Copyright (C) 2003		Red Hat Inc
 *
 *
 * TODO
 *	Look पूर्णांकo engine reset on समयout errors. Should not be required.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_hpt366"
#घोषणा DRV_VERSION	"0.6.11"

काष्ठा hpt_घड़ी अणु
	u8	xfer_mode;
	u32	timing;
पूर्ण;

/* key क्रम bus घड़ी timings
 * bit
 * 0:3    data_high_समय. Inactive समय of DIOW_/DIOR_ क्रम PIO and MW DMA.
 *        cycles = value + 1
 * 4:7    data_low_समय. Active समय of DIOW_/DIOR_ क्रम PIO and MW DMA.
 *        cycles = value + 1
 * 8:11   cmd_high_समय. Inactive समय of DIOW_/DIOR_ during task file
 *        रेजिस्टर access.
 * 12:15  cmd_low_समय. Active समय of DIOW_/DIOR_ during task file
 *        रेजिस्टर access.
 * 16:18  udma_cycle_समय. Clock cycles क्रम UDMA xfer?
 * 19:21  pre_high_समय. Time to initialize 1st cycle क्रम PIO and MW DMA xfer.
 * 22:24  cmd_pre_high_समय. Time to initialize 1st PIO cycle क्रम task file
 *        रेजिस्टर access.
 * 28     UDMA enable.
 * 29     DMA  enable.
 * 30     PIO_MST enable. If set, the chip is in bus master mode during
 *        PIO xfer.
 * 31     FIFO enable.
 */

अटल स्थिर काष्ठा hpt_घड़ी hpt366_40[] = अणु
	अणु	XFER_UDMA_4,	0x900fd943	पूर्ण,
	अणु	XFER_UDMA_3,	0x900ad943	पूर्ण,
	अणु	XFER_UDMA_2,	0x900bd943	पूर्ण,
	अणु	XFER_UDMA_1,	0x9008d943	पूर्ण,
	अणु	XFER_UDMA_0,	0x9008d943	पूर्ण,

	अणु	XFER_MW_DMA_2,	0xa008d943	पूर्ण,
	अणु	XFER_MW_DMA_1,	0xa010d955	पूर्ण,
	अणु	XFER_MW_DMA_0,	0xa010d9fc	पूर्ण,

	अणु	XFER_PIO_4,	0xc008d963	पूर्ण,
	अणु	XFER_PIO_3,	0xc010d974	पूर्ण,
	अणु	XFER_PIO_2,	0xc010d997	पूर्ण,
	अणु	XFER_PIO_1,	0xc010d9c7	पूर्ण,
	अणु	XFER_PIO_0,	0xc018d9d9	पूर्ण,
	अणु	0,		0x0120d9d9	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_घड़ी hpt366_33[] = अणु
	अणु	XFER_UDMA_4,	0x90c9a731	पूर्ण,
	अणु	XFER_UDMA_3,	0x90cfa731	पूर्ण,
	अणु	XFER_UDMA_2,	0x90caa731	पूर्ण,
	अणु	XFER_UDMA_1,	0x90cba731	पूर्ण,
	अणु	XFER_UDMA_0,	0x90c8a731	पूर्ण,

	अणु	XFER_MW_DMA_2,	0xa0c8a731	पूर्ण,
	अणु	XFER_MW_DMA_1,	0xa0c8a732	पूर्ण,	/* 0xa0c8a733 */
	अणु	XFER_MW_DMA_0,	0xa0c8a797	पूर्ण,

	अणु	XFER_PIO_4,	0xc0c8a731	पूर्ण,
	अणु	XFER_PIO_3,	0xc0c8a742	पूर्ण,
	अणु	XFER_PIO_2,	0xc0d0a753	पूर्ण,
	अणु	XFER_PIO_1,	0xc0d0a7a3	पूर्ण,	/* 0xc0d0a793 */
	अणु	XFER_PIO_0,	0xc0d0a7aa	पूर्ण,	/* 0xc0d0a7a7 */
	अणु	0,		0x0120a7a7	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_घड़ी hpt366_25[] = अणु
	अणु	XFER_UDMA_4,	0x90c98521	पूर्ण,
	अणु	XFER_UDMA_3,	0x90cf8521	पूर्ण,
	अणु	XFER_UDMA_2,	0x90cf8521	पूर्ण,
	अणु	XFER_UDMA_1,	0x90cb8521	पूर्ण,
	अणु	XFER_UDMA_0,	0x90cb8521	पूर्ण,

	अणु	XFER_MW_DMA_2,	0xa0ca8521	पूर्ण,
	अणु	XFER_MW_DMA_1,	0xa0ca8532	पूर्ण,
	अणु	XFER_MW_DMA_0,	0xa0ca8575	पूर्ण,

	अणु	XFER_PIO_4,	0xc0ca8521	पूर्ण,
	अणु	XFER_PIO_3,	0xc0ca8532	पूर्ण,
	अणु	XFER_PIO_2,	0xc0ca8542	पूर्ण,
	अणु	XFER_PIO_1,	0xc0d08572	पूर्ण,
	अणु	XFER_PIO_0,	0xc0d08585	पूर्ण,
	अणु	0,		0x01208585	पूर्ण
पूर्ण;

/**
 *	hpt36x_find_mode	-	find the hpt36x timing
 *	@ap: ATA port
 *	@speed: transfer mode
 *
 *	Return the 32bit रेजिस्टर programming inक्रमmation क्रम this channel
 *	that matches the speed provided.
 */

अटल u32 hpt36x_find_mode(काष्ठा ata_port *ap, पूर्णांक speed)
अणु
	काष्ठा hpt_घड़ी *घड़ीs = ap->host->निजी_data;

	जबतक (घड़ीs->xfer_mode) अणु
		अगर (घड़ीs->xfer_mode == speed)
			वापस घड़ीs->timing;
		घड़ीs++;
	पूर्ण
	BUG();
	वापस 0xffffffffU;	/* silence compiler warning */
पूर्ण

अटल स्थिर अक्षर * स्थिर bad_ata33[] = अणु
	"Maxtor 92720U8", "Maxtor 92040U6", "Maxtor 91360U4", "Maxtor 91020U3",
	"Maxtor 90845U3", "Maxtor 90650U2",
	"Maxtor 91360D8", "Maxtor 91190D7", "Maxtor 91020D6", "Maxtor 90845D5",
	"Maxtor 90680D4", "Maxtor 90510D3", "Maxtor 90340D2",
	"Maxtor 91152D8", "Maxtor 91008D7", "Maxtor 90845D6", "Maxtor 90840D6",
	"Maxtor 90720D5", "Maxtor 90648D5", "Maxtor 90576D4",
	"Maxtor 90510D4",
	"Maxtor 90432D3", "Maxtor 90288D2", "Maxtor 90256D2",
	"Maxtor 91000D8", "Maxtor 90910D8", "Maxtor 90875D7", "Maxtor 90840D7",
	"Maxtor 90750D6", "Maxtor 90625D5", "Maxtor 90500D4",
	"Maxtor 91728D8", "Maxtor 91512D7", "Maxtor 91303D6", "Maxtor 91080D5",
	"Maxtor 90845D4", "Maxtor 90680D4", "Maxtor 90648D3", "Maxtor 90432D2",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर bad_ata66_4[] = अणु
	"IBM-DTLA-307075",
	"IBM-DTLA-307060",
	"IBM-DTLA-307045",
	"IBM-DTLA-307030",
	"IBM-DTLA-307020",
	"IBM-DTLA-307015",
	"IBM-DTLA-305040",
	"IBM-DTLA-305030",
	"IBM-DTLA-305020",
	"IC35L010AVER07-0",
	"IC35L020AVER07-0",
	"IC35L030AVER07-0",
	"IC35L040AVER07-0",
	"IC35L060AVER07-0",
	"WDC AC310200R",
	शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर bad_ata66_3[] = अणु
	"WDC AC310200R",
	शून्य
पूर्ण;

अटल पूर्णांक hpt_dma_blacklisted(स्थिर काष्ठा ata_device *dev, अक्षर *modestr,
			       स्थिर अक्षर * स्थिर list[])
अणु
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];
	पूर्णांक i;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, माप(model_num));

	i = match_string(list, -1, model_num);
	अगर (i >= 0) अणु
		pr_warn("%s is not supported for %s\n", modestr, list[i]);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	hpt366_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: Current mask to manipulate and pass back
 *
 *	Block UDMA on devices that cause trouble with this controller.
 */

अटल अचिन्हित दीर्घ hpt366_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अगर (adev->class == ATA_DEV_ATA) अणु
		अगर (hpt_dma_blacklisted(adev, "UDMA",  bad_ata33))
			mask &= ~ATA_MASK_UDMA;
		अगर (hpt_dma_blacklisted(adev, "UDMA3", bad_ata66_3))
			mask &= ~(0xF8 << ATA_SHIFT_UDMA);
		अगर (hpt_dma_blacklisted(adev, "UDMA4", bad_ata66_4))
			mask &= ~(0xF0 << ATA_SHIFT_UDMA);
	पूर्ण अन्यथा अगर (adev->class == ATA_DEV_ATAPI)
		mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);

	वापस mask;
पूर्ण

अटल पूर्णांक hpt36x_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	/*
	 * Each channel of pata_hpt366 occupies separate PCI function
	 * as the primary channel and bit1 indicates the cable type.
	 */
	pci_पढ़ो_config_byte(pdev, 0x5A, &ata66);
	अगर (ata66 & 2)
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

अटल व्योम hpt366_set_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev,
			    u8 mode)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 addr = 0x40 + 4 * adev->devno;
	u32 mask, reg, t;

	/* determine timing mask and find matching घड़ी entry */
	अगर (mode < XFER_MW_DMA_0)
		mask = 0xc1f8ffff;
	अन्यथा अगर (mode < XFER_UDMA_0)
		mask = 0x303800ff;
	अन्यथा
		mask = 0x30070000;

	t = hpt36x_find_mode(ap, mode);

	/*
	 * Combine new mode bits with old config bits and disable
	 * on-chip PIO FIFO/buffer (and PIO MST mode as well) to aव्योम
	 * problems handling I/O errors later.
	 */
	pci_पढ़ो_config_dword(pdev, addr, &reg);
	reg = ((reg & ~mask) | (t & mask)) & ~0xc0000000;
	pci_ग_लिखो_config_dword(pdev, addr, reg);
पूर्ण

/**
 *	hpt366_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Perक्रमm PIO mode setup.
 */

अटल व्योम hpt366_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt366_set_mode(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	hpt366_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	Set up the channel क्रम MWDMA or UDMA modes. Much the same as with
 *	PIO, load the mode number and then set MWDMA or UDMA flag.
 */

अटल व्योम hpt366_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt366_set_mode(ap, adev, adev->dma_mode);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा hpt36x_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

/*
 *	Configuration क्रम HPT366/68
 */

अटल काष्ठा ata_port_operations hpt366_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= hpt36x_cable_detect,
	.mode_filter	= hpt366_filter,
	.set_piomode	= hpt366_set_piomode,
	.set_dmamode	= hpt366_set_dmamode,
पूर्ण;

/**
 *	hpt36x_init_chipset	-	common chip setup
 *	@dev: PCI device
 *
 *	Perक्रमm the chip setup work that must be करोne at both init and
 *	resume समय
 */

अटल व्योम hpt36x_init_chipset(काष्ठा pci_dev *dev)
अणु
	u8 drive_fast;

	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, (L1_CACHE_BYTES / 4));
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x78);
	pci_ग_लिखो_config_byte(dev, PCI_MIN_GNT, 0x08);
	pci_ग_लिखो_config_byte(dev, PCI_MAX_LAT, 0x08);

	pci_पढ़ो_config_byte(dev, 0x51, &drive_fast);
	अगर (drive_fast & 0x80)
		pci_ग_लिखो_config_byte(dev, 0x51, drive_fast & ~0x80);
पूर्ण

/**
 *	hpt36x_init_one		-	Initialise an HPT366/368
 *	@dev: PCI device
 *	@id: Entry in match table
 *
 *	Initialise an HPT36x device. There are some पूर्णांकeresting complications
 *	here. Firstly the chip may report 366 and be one of several variants.
 *	Secondly all the timings depend on the घड़ी क्रम the chip which we must
 *	detect and look up
 *
 *	This is the known chip mappings. It may be missing a couple of later
 *	releases.
 *
 *	Chip version		PCI		Rev	Notes
 *	HPT366			4 (HPT366)	0	UDMA66
 *	HPT366			4 (HPT366)	1	UDMA66
 *	HPT368			4 (HPT366)	2	UDMA66
 *	HPT37x/30x		4 (HPT366)	3+	Other driver
 *
 */

अटल पूर्णांक hpt36x_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info_hpt366 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &hpt366_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info_hpt366, शून्य पूर्ण;

	स्थिर व्योम *hpriv = शून्य;
	u32 reg1;
	पूर्णांक rc;

	rc = pcim_enable_device(dev);
	अगर (rc)
		वापस rc;

	/* May be a later chip in disguise. Check */
	/* Newer chips are not in the HPT36x driver. Ignore them */
	अगर (dev->revision > 2)
		वापस -ENODEV;

	hpt36x_init_chipset(dev);

	pci_पढ़ो_config_dword(dev, 0x40,  &reg1);

	/* PCI घड़ीing determines the ATA timing values to use */
	/* info_hpt366 is safe against re-entry so we can scribble on it */
	चयन ((reg1 & 0xf00) >> 8) अणु
	हाल 9:
		hpriv = &hpt366_40;
		अवरोध;
	हाल 5:
		hpriv = &hpt366_25;
		अवरोध;
	शेष:
		hpriv = &hpt366_33;
		अवरोध;
	पूर्ण
	/* Now kick off ATA set up */
	वापस ata_pci_bmdma_init_one(dev, ppi, &hpt36x_sht, (व्योम *)hpriv, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hpt36x_reinit_one(काष्ठा pci_dev *dev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(dev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(dev);
	अगर (rc)
		वापस rc;
	hpt36x_init_chipset(dev);
	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id hpt36x[] = अणु
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT366), पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver hpt36x_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= hpt36x,
	.probe		= hpt36x_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= hpt36x_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(hpt36x_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the Highpoint HPT366/368");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, hpt36x);
MODULE_VERSION(DRV_VERSION);
