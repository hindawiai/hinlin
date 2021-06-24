<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Libata driver क्रम the highpoपूर्णांक 37x and 30x UDMA66 ATA controllers.
 *
 * This driver is heavily based upon:
 *
 * linux/drivers/ide/pci/hpt366.c		Version 0.36	April 25, 2003
 *
 * Copyright (C) 1999-2003		Andre Hedrick <andre@linux-ide.org>
 * Portions Copyright (C) 2001	        Sun Microप्रणालीs, Inc.
 * Portions Copyright (C) 2003		Red Hat Inc
 * Portions Copyright (C) 2005-2010	MontaVista Software, Inc.
 *
 * TODO
 *	Look पूर्णांकo engine reset on समयout errors. Should not be	required.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_hpt37x"
#घोषणा DRV_VERSION	"0.6.23"

काष्ठा hpt_घड़ी अणु
	u8	xfer_speed;
	u32	timing;
पूर्ण;

काष्ठा hpt_chip अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक base;
	काष्ठा hpt_घड़ी स्थिर *घड़ीs[4];
पूर्ण;

/* key क्रम bus घड़ी timings
 * bit
 * 0:3    data_high_समय. Inactive समय of DIOW_/DIOR_ क्रम PIO and MW DMA.
 *        cycles = value + 1
 * 4:8    data_low_समय. Active समय of DIOW_/DIOR_ क्रम PIO and MW DMA.
 *        cycles = value + 1
 * 9:12   cmd_high_समय. Inactive समय of DIOW_/DIOR_ during task file
 *        रेजिस्टर access.
 * 13:17  cmd_low_समय. Active समय of DIOW_/DIOR_ during task file
 *        रेजिस्टर access.
 * 18:20  udma_cycle_समय. Clock cycles क्रम UDMA xfer.
 * 21     CLK frequency क्रम UDMA: 0=ATA घड़ी, 1=dual ATA घड़ी.
 * 22:24  pre_high_समय. Time to initialize 1st cycle क्रम PIO and MW DMA xfer.
 * 25:27  cmd_pre_high_समय. Time to initialize 1st PIO cycle क्रम task file
 *        रेजिस्टर access.
 * 28     UDMA enable.
 * 29     DMA  enable.
 * 30     PIO_MST enable. If set, the chip is in bus master mode during
 *        PIO xfer.
 * 31     FIFO enable. Only क्रम PIO.
 */

अटल काष्ठा hpt_घड़ी hpt37x_timings_33[] = अणु
	अणु XFER_UDMA_6,		0x12446231 पूर्ण,	/* 0x12646231 ?? */
	अणु XFER_UDMA_5,		0x12446231 पूर्ण,
	अणु XFER_UDMA_4,		0x12446231 पूर्ण,
	अणु XFER_UDMA_3,		0x126c6231 पूर्ण,
	अणु XFER_UDMA_2,		0x12486231 पूर्ण,
	अणु XFER_UDMA_1,		0x124c6233 पूर्ण,
	अणु XFER_UDMA_0,		0x12506297 पूर्ण,

	अणु XFER_MW_DMA_2,	0x22406c31 पूर्ण,
	अणु XFER_MW_DMA_1,	0x22406c33 पूर्ण,
	अणु XFER_MW_DMA_0,	0x22406c97 पूर्ण,

	अणु XFER_PIO_4,		0x06414e31 पूर्ण,
	अणु XFER_PIO_3,		0x06414e42 पूर्ण,
	अणु XFER_PIO_2,		0x06414e53 पूर्ण,
	अणु XFER_PIO_1,		0x06814e93 पूर्ण,
	अणु XFER_PIO_0,		0x06814ea7 पूर्ण
पूर्ण;

अटल काष्ठा hpt_घड़ी hpt37x_timings_50[] = अणु
	अणु XFER_UDMA_6,		0x12848242 पूर्ण,
	अणु XFER_UDMA_5,		0x12848242 पूर्ण,
	अणु XFER_UDMA_4,		0x12ac8242 पूर्ण,
	अणु XFER_UDMA_3,		0x128c8242 पूर्ण,
	अणु XFER_UDMA_2,		0x120c8242 पूर्ण,
	अणु XFER_UDMA_1,		0x12148254 पूर्ण,
	अणु XFER_UDMA_0,		0x121882ea पूर्ण,

	अणु XFER_MW_DMA_2,	0x22808242 पूर्ण,
	अणु XFER_MW_DMA_1,	0x22808254 पूर्ण,
	अणु XFER_MW_DMA_0,	0x228082ea पूर्ण,

	अणु XFER_PIO_4,		0x0a81f442 पूर्ण,
	अणु XFER_PIO_3,		0x0a81f443 पूर्ण,
	अणु XFER_PIO_2,		0x0a81f454 पूर्ण,
	अणु XFER_PIO_1,		0x0ac1f465 पूर्ण,
	अणु XFER_PIO_0,		0x0ac1f48a पूर्ण
पूर्ण;

अटल काष्ठा hpt_घड़ी hpt37x_timings_66[] = अणु
	अणु XFER_UDMA_6,		0x1c869c62 पूर्ण,
	अणु XFER_UDMA_5,		0x1cae9c62 पूर्ण,	/* 0x1c8a9c62 */
	अणु XFER_UDMA_4,		0x1c8a9c62 पूर्ण,
	अणु XFER_UDMA_3,		0x1c8e9c62 पूर्ण,
	अणु XFER_UDMA_2,		0x1c929c62 पूर्ण,
	अणु XFER_UDMA_1,		0x1c9a9c62 पूर्ण,
	अणु XFER_UDMA_0,		0x1c829c62 पूर्ण,

	अणु XFER_MW_DMA_2,	0x2c829c62 पूर्ण,
	अणु XFER_MW_DMA_1,	0x2c829c66 पूर्ण,
	अणु XFER_MW_DMA_0,	0x2c829d2e पूर्ण,

	अणु XFER_PIO_4,		0x0c829c62 पूर्ण,
	अणु XFER_PIO_3,		0x0c829c84 पूर्ण,
	अणु XFER_PIO_2,		0x0c829ca6 पूर्ण,
	अणु XFER_PIO_1,		0x0d029d26 पूर्ण,
	अणु XFER_PIO_0,		0x0d029d5e पूर्ण
पूर्ण;


अटल स्थिर काष्ठा hpt_chip hpt370 = अणु
	"HPT370",
	48,
	अणु
		hpt37x_timings_33,
		शून्य,
		शून्य,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_chip hpt370a = अणु
	"HPT370A",
	48,
	अणु
		hpt37x_timings_33,
		शून्य,
		hpt37x_timings_50,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_chip hpt372 = अणु
	"HPT372",
	55,
	अणु
		hpt37x_timings_33,
		शून्य,
		hpt37x_timings_50,
		hpt37x_timings_66
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_chip hpt302 = अणु
	"HPT302",
	66,
	अणु
		hpt37x_timings_33,
		शून्य,
		hpt37x_timings_50,
		hpt37x_timings_66
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_chip hpt371 = अणु
	"HPT371",
	66,
	अणु
		hpt37x_timings_33,
		शून्य,
		hpt37x_timings_50,
		hpt37x_timings_66
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_chip hpt372a = अणु
	"HPT372A",
	66,
	अणु
		hpt37x_timings_33,
		शून्य,
		hpt37x_timings_50,
		hpt37x_timings_66
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_chip hpt374 = अणु
	"HPT374",
	48,
	अणु
		hpt37x_timings_33,
		शून्य,
		शून्य,
		शून्य
	पूर्ण
पूर्ण;

/**
 *	hpt37x_find_mode	-	reset the hpt37x bus
 *	@ap: ATA port
 *	@speed: transfer mode
 *
 *	Return the 32bit रेजिस्टर programming inक्रमmation क्रम this channel
 *	that matches the speed provided.
 */

अटल u32 hpt37x_find_mode(काष्ठा ata_port *ap, पूर्णांक speed)
अणु
	काष्ठा hpt_घड़ी *घड़ीs = ap->host->निजी_data;

	जबतक (घड़ीs->xfer_speed) अणु
		अगर (घड़ीs->xfer_speed == speed)
			वापस घड़ीs->timing;
		घड़ीs++;
	पूर्ण
	BUG();
	वापस 0xffffffffU;	/* silence compiler warning */
पूर्ण

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

अटल स्थिर अक्षर * स्थिर bad_ata100_5[] = अणु
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

/**
 *	hpt370_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	Block UDMA on devices that cause trouble with this controller.
 */

अटल अचिन्हित दीर्घ hpt370_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अगर (adev->class == ATA_DEV_ATA) अणु
		अगर (hpt_dma_blacklisted(adev, "UDMA", bad_ata33))
			mask &= ~ATA_MASK_UDMA;
		अगर (hpt_dma_blacklisted(adev, "UDMA100", bad_ata100_5))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	पूर्ण
	वापस mask;
पूर्ण

/**
 *	hpt370a_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	Block UDMA on devices that cause trouble with this controller.
 */

अटल अचिन्हित दीर्घ hpt370a_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अगर (adev->class == ATA_DEV_ATA) अणु
		अगर (hpt_dma_blacklisted(adev, "UDMA100", bad_ata100_5))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	पूर्ण
	वापस mask;
पूर्ण

/**
 *	hpt372_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	The Marvell bridge chips used on the HighPoपूर्णांक SATA cards करो not seem
 *	to support the UltraDMA modes 1, 2, and 3 as well as any MWDMA modes...
 */
अटल अचिन्हित दीर्घ hpt372_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अगर (ata_id_is_sata(adev->id))
		mask &= ~((0xE << ATA_SHIFT_UDMA) | ATA_MASK_MWDMA);

	वापस mask;
पूर्ण

/**
 *	hpt37x_cable_detect	-	Detect the cable type
 *	@ap: ATA port to detect on
 *
 *	Return the cable type attached to this port
 */

अटल पूर्णांक hpt37x_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 scr2, ata66;

	pci_पढ़ो_config_byte(pdev, 0x5B, &scr2);
	pci_ग_लिखो_config_byte(pdev, 0x5B, scr2 & ~0x01);

	udelay(10); /* debounce */

	/* Cable रेजिस्टर now active */
	pci_पढ़ो_config_byte(pdev, 0x5A, &ata66);
	/* Restore state */
	pci_ग_लिखो_config_byte(pdev, 0x5B, scr2);

	अगर (ata66 & (2 >> ap->port_no))
		वापस ATA_CBL_PATA40;
	अन्यथा
		वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	hpt374_fn1_cable_detect	-	Detect the cable type
 *	@ap: ATA port to detect on
 *
 *	Return the cable type attached to this port
 */

अटल पूर्णांक hpt374_fn1_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित पूर्णांक mcrbase = 0x50 + 4 * ap->port_no;
	u16 mcr3;
	u8 ata66;

	/* Do the extra channel work */
	pci_पढ़ो_config_word(pdev, mcrbase + 2, &mcr3);
	/* Set bit 15 of 0x52 to enable TCBLID as input */
	pci_ग_लिखो_config_word(pdev, mcrbase + 2, mcr3 | 0x8000);
	pci_पढ़ो_config_byte(pdev, 0x5A, &ata66);
	/* Reset TCBLID/FCBLID to output */
	pci_ग_लिखो_config_word(pdev, mcrbase + 2, mcr3);

	अगर (ata66 & (2 >> ap->port_no))
		वापस ATA_CBL_PATA40;
	अन्यथा
		वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	hpt37x_pre_reset	-	reset the hpt37x bus
 *	@link: ATA link to reset
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm the initial reset handling क्रम the HPT37x.
 */

अटल पूर्णांक hpt37x_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर काष्ठा pci_bits hpt37x_enable_bits[] = अणु
		अणु 0x50, 1, 0x04, 0x04 पूर्ण,
		अणु 0x54, 1, 0x04, 0x04 पूर्ण
	पूर्ण;

	अगर (!pci_test_config_bits(pdev, &hpt37x_enable_bits[ap->port_no]))
		वापस -ENOENT;

	/* Reset the state machine */
	pci_ग_लिखो_config_byte(pdev, 0x50 + 4 * ap->port_no, 0x37);
	udelay(100);

	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल व्योम hpt370_set_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev,
			    u8 mode)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 addr1, addr2;
	u32 reg, timing, mask;
	u8 fast;

	addr1 = 0x40 + 4 * (adev->devno + 2 * ap->port_no);
	addr2 = 0x51 + 4 * ap->port_no;

	/* Fast पूर्णांकerrupt prediction disable, hold off पूर्णांकerrupt disable */
	pci_पढ़ो_config_byte(pdev, addr2, &fast);
	fast &= ~0x02;
	fast |= 0x01;
	pci_ग_लिखो_config_byte(pdev, addr2, fast);

	/* Determine timing mask and find matching mode entry */
	अगर (mode < XFER_MW_DMA_0)
		mask = 0xcfc3ffff;
	अन्यथा अगर (mode < XFER_UDMA_0)
		mask = 0x31c001ff;
	अन्यथा
		mask = 0x303c0000;

	timing = hpt37x_find_mode(ap, mode);

	pci_पढ़ो_config_dword(pdev, addr1, &reg);
	reg = (reg & ~mask) | (timing & mask);
	pci_ग_लिखो_config_dword(pdev, addr1, reg);
पूर्ण
/**
 *	hpt370_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Perक्रमm PIO mode setup.
 */

अटल व्योम hpt370_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt370_set_mode(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	hpt370_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	Set up the channel क्रम MWDMA or UDMA modes.
 */

अटल व्योम hpt370_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt370_set_mode(ap, adev, adev->dma_mode);
पूर्ण

/**
 *	hpt370_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Work around the HPT370 DMA engine.
 */

अटल व्योम hpt370_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	व्योम __iomem *bmdma = ap->ioaddr.bmdma_addr;
	u8 dma_stat = ioपढ़ो8(bmdma + ATA_DMA_STATUS);
	u8 dma_cmd;

	अगर (dma_stat & ATA_DMA_ACTIVE) अणु
		udelay(20);
		dma_stat = ioपढ़ो8(bmdma + ATA_DMA_STATUS);
	पूर्ण
	अगर (dma_stat & ATA_DMA_ACTIVE) अणु
		/* Clear the engine */
		pci_ग_लिखो_config_byte(pdev, 0x50 + 4 * ap->port_no, 0x37);
		udelay(10);
		/* Stop DMA */
		dma_cmd = ioपढ़ो8(bmdma + ATA_DMA_CMD);
		ioग_लिखो8(dma_cmd & ~ATA_DMA_START, bmdma + ATA_DMA_CMD);
		/* Clear Error */
		dma_stat = ioपढ़ो8(bmdma + ATA_DMA_STATUS);
		ioग_लिखो8(dma_stat | ATA_DMA_INTR | ATA_DMA_ERR,
			 bmdma + ATA_DMA_STATUS);
		/* Clear the engine */
		pci_ग_लिखो_config_byte(pdev, 0x50 + 4 * ap->port_no, 0x37);
		udelay(10);
	पूर्ण
	ata_bmdma_stop(qc);
पूर्ण

अटल व्योम hpt372_set_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev,
			    u8 mode)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 addr1, addr2;
	u32 reg, timing, mask;
	u8 fast;

	addr1 = 0x40 + 4 * (adev->devno + 2 * ap->port_no);
	addr2 = 0x51 + 4 * ap->port_no;

	/* Fast पूर्णांकerrupt prediction disable, hold off पूर्णांकerrupt disable */
	pci_पढ़ो_config_byte(pdev, addr2, &fast);
	fast &= ~0x07;
	pci_ग_लिखो_config_byte(pdev, addr2, fast);

	/* Determine timing mask and find matching mode entry */
	अगर (mode < XFER_MW_DMA_0)
		mask = 0xcfc3ffff;
	अन्यथा अगर (mode < XFER_UDMA_0)
		mask = 0x31c001ff;
	अन्यथा
		mask = 0x303c0000;

	timing = hpt37x_find_mode(ap, mode);

	pci_पढ़ो_config_dword(pdev, addr1, &reg);
	reg = (reg & ~mask) | (timing & mask);
	pci_ग_लिखो_config_dword(pdev, addr1, reg);
पूर्ण

/**
 *	hpt372_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Perक्रमm PIO mode setup.
 */

अटल व्योम hpt372_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt372_set_mode(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	hpt372_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	Set up the channel क्रम MWDMA or UDMA modes.
 */

अटल व्योम hpt372_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt372_set_mode(ap, adev, adev->dma_mode);
पूर्ण

/**
 *	hpt37x_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Clean up after the HPT372 and later DMA engine
 */

अटल व्योम hpt37x_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक mscreg = 0x50 + 4 * ap->port_no;
	u8 bwsr_stat, msc_stat;

	pci_पढ़ो_config_byte(pdev, 0x6A, &bwsr_stat);
	pci_पढ़ो_config_byte(pdev, mscreg, &msc_stat);
	अगर (bwsr_stat & (1 << ap->port_no))
		pci_ग_लिखो_config_byte(pdev, mscreg, msc_stat | 0x30);
	ata_bmdma_stop(qc);
पूर्ण


अटल काष्ठा scsi_host_ढाँचा hpt37x_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

/*
 *	Configuration क्रम HPT370
 */

अटल काष्ठा ata_port_operations hpt370_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.bmdma_stop	= hpt370_bmdma_stop,

	.mode_filter	= hpt370_filter,
	.cable_detect	= hpt37x_cable_detect,
	.set_piomode	= hpt370_set_piomode,
	.set_dmamode	= hpt370_set_dmamode,
	.prereset	= hpt37x_pre_reset,
पूर्ण;

/*
 *	Configuration क्रम HPT370A. Close to 370 but less filters
 */

अटल काष्ठा ata_port_operations hpt370a_port_ops = अणु
	.inherits	= &hpt370_port_ops,
	.mode_filter	= hpt370a_filter,
पूर्ण;

/*
 *	Configuration क्रम HPT371 and HPT302. Slightly dअगरferent PIO and DMA
 *	mode setting functionality.
 */

अटल काष्ठा ata_port_operations hpt302_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.bmdma_stop	= hpt37x_bmdma_stop,

	.cable_detect	= hpt37x_cable_detect,
	.set_piomode	= hpt372_set_piomode,
	.set_dmamode	= hpt372_set_dmamode,
	.prereset	= hpt37x_pre_reset,
पूर्ण;

/*
 *	Configuration क्रम HPT372. Mode setting works like 371 and 302
 *	but we have a mode filter.
 */

अटल काष्ठा ata_port_operations hpt372_port_ops = अणु
	.inherits	= &hpt302_port_ops,
	.mode_filter	= hpt372_filter,
पूर्ण;

/*
 *	Configuration क्रम HPT374. Mode setting and filtering works like 372
 *	but we have a dअगरferent cable detection procedure क्रम function 1.
 */

अटल काष्ठा ata_port_operations hpt374_fn1_port_ops = अणु
	.inherits	= &hpt372_port_ops,
	.cable_detect	= hpt374_fn1_cable_detect,
पूर्ण;

/**
 *	hpt37x_घड़ी_slot	-	Turn timing to PC घड़ी entry
 *	@freq: Reported frequency timing
 *	@base: Base timing
 *
 *	Turn the timing data पूर्णांकoa घड़ी slot (0 क्रम 33, 1 क्रम 40, 2 क्रम 50
 *	and 3 क्रम 66Mhz)
 */

अटल पूर्णांक hpt37x_घड़ी_slot(अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित पूर्णांक f = (base * freq) / 192;	/* Mhz */
	अगर (f < 40)
		वापस 0;	/* 33Mhz slot */
	अगर (f < 45)
		वापस 1;	/* 40Mhz slot */
	अगर (f < 55)
		वापस 2;	/* 50Mhz slot */
	वापस 3;		/* 60Mhz slot */
पूर्ण

/**
 *	hpt37x_calibrate_dpll		-	Calibrate the DPLL loop
 *	@dev: PCI device
 *
 *	Perक्रमm a calibration cycle on the HPT37x DPLL. Returns 1 अगर this
 *	succeeds
 */

अटल पूर्णांक hpt37x_calibrate_dpll(काष्ठा pci_dev *dev)
अणु
	u8 reg5b;
	u32 reg5c;
	पूर्णांक tries;

	क्रम (tries = 0; tries < 0x5000; tries++) अणु
		udelay(50);
		pci_पढ़ो_config_byte(dev, 0x5b, &reg5b);
		अगर (reg5b & 0x80) अणु
			/* See अगर it stays set */
			क्रम (tries = 0; tries < 0x1000; tries++) अणु
				pci_पढ़ो_config_byte(dev, 0x5b, &reg5b);
				/* Failed ? */
				अगर ((reg5b & 0x80) == 0)
					वापस 0;
			पूर्ण
			/* Turn off tuning, we have the DPLL set */
			pci_पढ़ो_config_dword(dev, 0x5c, &reg5c);
			pci_ग_लिखो_config_dword(dev, 0x5c, reg5c & ~0x100);
			वापस 1;
		पूर्ण
	पूर्ण
	/* Never went stable */
	वापस 0;
पूर्ण

अटल u32 hpt374_पढ़ो_freq(काष्ठा pci_dev *pdev)
अणु
	u32 freq;
	अचिन्हित दीर्घ io_base = pci_resource_start(pdev, 4);

	अगर (PCI_FUNC(pdev->devfn) & 1) अणु
		काष्ठा pci_dev *pdev_0;

		pdev_0 = pci_get_slot(pdev->bus, pdev->devfn - 1);
		/* Someone hot plugged the controller on us ? */
		अगर (pdev_0 == शून्य)
			वापस 0;
		io_base = pci_resource_start(pdev_0, 4);
		freq = inl(io_base + 0x90);
		pci_dev_put(pdev_0);
	पूर्ण अन्यथा
		freq = inl(io_base + 0x90);
	वापस freq;
पूर्ण

/**
 *	hpt37x_init_one		-	Initialise an HPT37X/302
 *	@dev: PCI device
 *	@id: Entry in match table
 *
 *	Initialise an HPT37x device. There are some पूर्णांकeresting complications
 *	here. Firstly the chip may report 366 and be one of several variants.
 *	Secondly all the timings depend on the घड़ी क्रम the chip which we must
 *	detect and look up
 *
 *	This is the known chip mappings. It may be missing a couple of later
 *	releases.
 *
 *	Chip version		PCI		Rev	Notes
 *	HPT366			4 (HPT366)	0	Other driver
 *	HPT366			4 (HPT366)	1	Other driver
 *	HPT368			4 (HPT366)	2	Other driver
 *	HPT370			4 (HPT366)	3	UDMA100
 *	HPT370A			4 (HPT366)	4	UDMA100
 *	HPT372			4 (HPT366)	5	UDMA133 (1)
 *	HPT372N			4 (HPT366)	6	Other driver
 *	HPT372A			5 (HPT372)	1	UDMA133 (1)
 *	HPT372N			5 (HPT372)	2	Other driver
 *	HPT302			6 (HPT302)	1	UDMA133
 *	HPT302N			6 (HPT302)	2	Other driver
 *	HPT371			7 (HPT371)	*	UDMA133
 *	HPT374			8 (HPT374)	*	UDMA133 4 channel
 *	HPT372N			9 (HPT372N)	*	Other driver
 *
 *	(1) UDMA133 support depends on the bus घड़ी
 */

अटल पूर्णांक hpt37x_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	/* HPT370 - UDMA100 */
	अटल स्थिर काष्ठा ata_port_info info_hpt370 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &hpt370_port_ops
	पूर्ण;
	/* HPT370A - UDMA100 */
	अटल स्थिर काष्ठा ata_port_info info_hpt370a = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &hpt370a_port_ops
	पूर्ण;
	/* HPT370 - UDMA66 */
	अटल स्थिर काष्ठा ata_port_info info_hpt370_33 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &hpt370_port_ops
	पूर्ण;
	/* HPT370A - UDMA66 */
	अटल स्थिर काष्ठा ata_port_info info_hpt370a_33 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &hpt370a_port_ops
	पूर्ण;
	/* HPT372 - UDMA133 */
	अटल स्थिर काष्ठा ata_port_info info_hpt372 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &hpt372_port_ops
	पूर्ण;
	/* HPT371, 302 - UDMA133 */
	अटल स्थिर काष्ठा ata_port_info info_hpt302 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &hpt302_port_ops
	पूर्ण;
	/* HPT374 - UDMA100, function 1 uses dअगरferent cable_detect method */
	अटल स्थिर काष्ठा ata_port_info info_hpt374_fn0 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &hpt372_port_ops
	पूर्ण;
	अटल स्थिर काष्ठा ata_port_info info_hpt374_fn1 = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &hpt374_fn1_port_ops
	पूर्ण;

	अटल स्थिर पूर्णांक MHz[4] = अणु 33, 40, 50, 66 पूर्ण;
	व्योम *निजी_data = शून्य;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	u8 rev = dev->revision;
	u8 irqmask;
	u8 mcr1;
	u32 freq;
	पूर्णांक prefer_dpll = 1;

	अचिन्हित दीर्घ iobase = pci_resource_start(dev, 4);

	स्थिर काष्ठा hpt_chip *chip_table;
	पूर्णांक घड़ी_slot;
	पूर्णांक rc;

	rc = pcim_enable_device(dev);
	अगर (rc)
		वापस rc;

	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_TTI_HPT366:
		/* May be a later chip in disguise. Check */
		/* Older chips are in the HPT366 driver. Ignore them */
		अगर (rev < 3)
			वापस -ENODEV;
		/* N series chips have their own driver. Ignore */
		अगर (rev == 6)
			वापस -ENODEV;

		चयन (rev) अणु
		हाल 3:
			ppi[0] = &info_hpt370;
			chip_table = &hpt370;
			prefer_dpll = 0;
			अवरोध;
		हाल 4:
			ppi[0] = &info_hpt370a;
			chip_table = &hpt370a;
			prefer_dpll = 0;
			अवरोध;
		हाल 5:
			ppi[0] = &info_hpt372;
			chip_table = &hpt372;
			अवरोध;
		शेष:
			pr_err("Unknown HPT366 subtype, please report (%d)\n",
			       rev);
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	हाल PCI_DEVICE_ID_TTI_HPT372:
		/* 372N अगर rev >= 2 */
		अगर (rev >= 2)
			वापस -ENODEV;
		ppi[0] = &info_hpt372;
		chip_table = &hpt372a;
		अवरोध;
	हाल PCI_DEVICE_ID_TTI_HPT302:
		/* 302N अगर rev > 1 */
		अगर (rev > 1)
			वापस -ENODEV;
		ppi[0] = &info_hpt302;
		/* Check this */
		chip_table = &hpt302;
		अवरोध;
	हाल PCI_DEVICE_ID_TTI_HPT371:
		अगर (rev > 1)
			वापस -ENODEV;
		ppi[0] = &info_hpt302;
		chip_table = &hpt371;
		/*
		 * Single channel device, master is not present but the BIOS
		 * (or us क्रम non x86) must mark it असलent
		 */
		pci_पढ़ो_config_byte(dev, 0x50, &mcr1);
		mcr1 &= ~0x04;
		pci_ग_लिखो_config_byte(dev, 0x50, mcr1);
		अवरोध;
	हाल PCI_DEVICE_ID_TTI_HPT374:
		chip_table = &hpt374;
		अगर (!(PCI_FUNC(dev->devfn) & 1))
			*ppi = &info_hpt374_fn0;
		अन्यथा
			*ppi = &info_hpt374_fn1;
		अवरोध;
	शेष:
		pr_err("PCI table is bogus, please report (%d)\n", dev->device);
		वापस -ENODEV;
	पूर्ण
	/* Ok so this is a chip we support */

	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, (L1_CACHE_BYTES / 4));
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x78);
	pci_ग_लिखो_config_byte(dev, PCI_MIN_GNT, 0x08);
	pci_ग_लिखो_config_byte(dev, PCI_MAX_LAT, 0x08);

	pci_पढ़ो_config_byte(dev, 0x5A, &irqmask);
	irqmask &= ~0x10;
	pci_ग_लिखो_config_byte(dev, 0x5a, irqmask);

	/*
	 * शेष to pci घड़ी. make sure MA15/16 are set to output
	 * to prevent drives having problems with 40-pin cables. Needed
	 * क्रम some drives such as IBM-DTLA which will not enter पढ़ोy
	 * state on reset when PDIAG is a input.
	 */

	pci_ग_लिखो_config_byte(dev, 0x5b, 0x23);

	/*
	 * HighPoपूर्णांक करोes this क्रम HPT372A.
	 * NOTE: This रेजिस्टर is only ग_लिखोable via I/O space.
	 */
	अगर (chip_table == &hpt372a)
		outb(0x0e, iobase + 0x9c);

	/*
	 * Some devices करो not let this value be accessed via PCI space
	 * according to the old driver. In addition we must use the value
	 * from FN 0 on the HPT374.
	 */

	अगर (chip_table == &hpt374) अणु
		freq = hpt374_पढ़ो_freq(dev);
		अगर (freq == 0)
			वापस -ENODEV;
	पूर्ण अन्यथा
		freq = inl(iobase + 0x90);

	अगर ((freq >> 12) != 0xABCDE) अणु
		पूर्णांक i;
		u8 sr;
		u32 total = 0;

		pr_warn("BIOS has not set timing clocks\n");

		/* This is the process the HPT371 BIOS is reported to use */
		क्रम (i = 0; i < 128; i++) अणु
			pci_पढ़ो_config_byte(dev, 0x78, &sr);
			total += sr & 0x1FF;
			udelay(15);
		पूर्ण
		freq = total / 128;
	पूर्ण
	freq &= 0x1FF;

	/*
	 *	Turn the frequency check पूर्णांकo a band and then find a timing
	 *	table to match it.
	 */

	घड़ी_slot = hpt37x_घड़ी_slot(freq, chip_table->base);
	अगर (chip_table->घड़ीs[घड़ी_slot] == शून्य || prefer_dpll) अणु
		/*
		 *	We need to try PLL mode instead
		 *
		 *	For non UDMA133 capable devices we should
		 *	use a 50MHz DPLL by choice
		 */
		अचिन्हित पूर्णांक f_low, f_high;
		पूर्णांक dpll, adjust;

		/* Compute DPLL */
		dpll = (ppi[0]->udma_mask & 0xC0) ? 3 : 2;

		f_low = (MHz[घड़ी_slot] * 48) / MHz[dpll];
		f_high = f_low + 2;
		अगर (घड़ी_slot > 1)
			f_high += 2;

		/* Select the DPLL घड़ी. */
		pci_ग_लिखो_config_byte(dev, 0x5b, 0x21);
		pci_ग_लिखो_config_dword(dev, 0x5C,
				       (f_high << 16) | f_low | 0x100);

		क्रम (adjust = 0; adjust < 8; adjust++) अणु
			अगर (hpt37x_calibrate_dpll(dev))
				अवरोध;
			/*
			 * See अगर it'll settle at a fractionally
			 * dअगरferent घड़ी
			 */
			अगर (adjust & 1)
				f_low -= adjust >> 1;
			अन्यथा
				f_high += adjust >> 1;
			pci_ग_लिखो_config_dword(dev, 0x5C,
					       (f_high << 16) | f_low | 0x100);
		पूर्ण
		अगर (adjust == 8) अणु
			pr_err("DPLL did not stabilize!\n");
			वापस -ENODEV;
		पूर्ण
		अगर (dpll == 3)
			निजी_data = (व्योम *)hpt37x_timings_66;
		अन्यथा
			निजी_data = (व्योम *)hpt37x_timings_50;

		pr_info("bus clock %dMHz, using %dMHz DPLL\n",
			MHz[घड़ी_slot], MHz[dpll]);
	पूर्ण अन्यथा अणु
		निजी_data = (व्योम *)chip_table->घड़ीs[घड़ी_slot];
		/*
		 *	Perक्रमm a final fixup. Note that we will have used the
		 *	DPLL on the HPT372 which means we करोn't have to worry
		 *	about lack of UDMA133 support on lower घड़ीs
		 */

		अगर (घड़ी_slot < 2 && ppi[0] == &info_hpt370)
			ppi[0] = &info_hpt370_33;
		अगर (घड़ी_slot < 2 && ppi[0] == &info_hpt370a)
			ppi[0] = &info_hpt370a_33;

		pr_info("%s using %dMHz bus clock\n",
			chip_table->name, MHz[घड़ी_slot]);
	पूर्ण

	/* Now kick off ATA set up */
	वापस ata_pci_bmdma_init_one(dev, ppi, &hpt37x_sht, निजी_data, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hpt37x[] = अणु
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT366), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT371), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT374), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT302), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver hpt37x_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= hpt37x,
	.probe		= hpt37x_init_one,
	.हटाओ		= ata_pci_हटाओ_one
पूर्ण;

module_pci_driver(hpt37x_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the Highpoint HPT37x/30x");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, hpt37x);
MODULE_VERSION(DRV_VERSION);
