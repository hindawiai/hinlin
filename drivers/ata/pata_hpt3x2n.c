<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Libata driver क्रम the HighPoपूर्णांक 371N, 372N, and 302N UDMA66 ATA controllers.
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
 *
 * TODO
 *	Work out best PLL policy
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_hpt3x2n"
#घोषणा DRV_VERSION	"0.3.15"

क्रमागत अणु
	HPT_PCI_FAST	=	(1 << 31),
	PCI66		=	(1 << 1),
	USE_DPLL	=	(1 << 0)
पूर्ण;

काष्ठा hpt_घड़ी अणु
	u8	xfer_speed;
	u32	timing;
पूर्ण;

काष्ठा hpt_chip अणु
	स्थिर अक्षर *name;
	काष्ठा hpt_घड़ी *घड़ीs[3];
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

/* 66MHz DPLL घड़ीs */

अटल काष्ठा hpt_घड़ी hpt3x2n_घड़ीs[] = अणु
	अणु	XFER_UDMA_7,	0x1c869c62	पूर्ण,
	अणु	XFER_UDMA_6,	0x1c869c62	पूर्ण,
	अणु	XFER_UDMA_5,	0x1c8a9c62	पूर्ण,
	अणु	XFER_UDMA_4,	0x1c8a9c62	पूर्ण,
	अणु	XFER_UDMA_3,	0x1c8e9c62	पूर्ण,
	अणु	XFER_UDMA_2,	0x1c929c62	पूर्ण,
	अणु	XFER_UDMA_1,	0x1c9a9c62	पूर्ण,
	अणु	XFER_UDMA_0,	0x1c829c62	पूर्ण,

	अणु	XFER_MW_DMA_2,	0x2c829c62	पूर्ण,
	अणु	XFER_MW_DMA_1,	0x2c829c66	पूर्ण,
	अणु	XFER_MW_DMA_0,	0x2c829d2e	पूर्ण,

	अणु	XFER_PIO_4,	0x0c829c62	पूर्ण,
	अणु	XFER_PIO_3,	0x0c829c84	पूर्ण,
	अणु	XFER_PIO_2,	0x0c829ca6	पूर्ण,
	अणु	XFER_PIO_1,	0x0d029d26	पूर्ण,
	अणु	XFER_PIO_0,	0x0d029d5e	पूर्ण,
पूर्ण;

/**
 *	hpt3x2n_find_mode	-	reset the hpt3x2n bus
 *	@ap: ATA port
 *	@speed: transfer mode
 *
 *	Return the 32bit रेजिस्टर programming inक्रमmation क्रम this channel
 *	that matches the speed provided. For the moment the घड़ीs table
 *	is hard coded but easy to change. This will be needed अगर we use
 *	dअगरferent DPLLs
 */

अटल u32 hpt3x2n_find_mode(काष्ठा ata_port *ap, पूर्णांक speed)
अणु
	काष्ठा hpt_घड़ी *घड़ीs = hpt3x2n_घड़ीs;

	जबतक (घड़ीs->xfer_speed) अणु
		अगर (घड़ीs->xfer_speed == speed)
			वापस घड़ीs->timing;
		घड़ीs++;
	पूर्ण
	BUG();
	वापस 0xffffffffU;	/* silence compiler warning */
पूर्ण

/**
 *	hpt372n_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	The Marvell bridge chips used on the HighPoपूर्णांक SATA cards करो not seem
 *	to support the UltraDMA modes 1, 2, and 3 as well as any MWDMA modes...
 */
अटल अचिन्हित दीर्घ hpt372n_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अगर (ata_id_is_sata(adev->id))
		mask &= ~((0xE << ATA_SHIFT_UDMA) | ATA_MASK_MWDMA);

	वापस mask;
पूर्ण

/**
 *	hpt3x2n_cable_detect	-	Detect the cable type
 *	@ap: ATA port to detect on
 *
 *	Return the cable type attached to this port
 */

अटल पूर्णांक hpt3x2n_cable_detect(काष्ठा ata_port *ap)
अणु
	u8 scr2, ata66;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

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
 *	hpt3x2n_pre_reset	-	reset the hpt3x2n bus
 *	@link: ATA link to reset
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm the initial reset handling क्रम the 3x2n series controllers.
 *	Reset the hardware and state machine,
 */

अटल पूर्णांक hpt3x2n_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	/* Reset the state machine */
	pci_ग_लिखो_config_byte(pdev, 0x50 + 4 * ap->port_no, 0x37);
	udelay(100);

	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल व्योम hpt3x2n_set_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev,
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

	timing = hpt3x2n_find_mode(ap, mode);

	pci_पढ़ो_config_dword(pdev, addr1, &reg);
	reg = (reg & ~mask) | (timing & mask);
	pci_ग_लिखो_config_dword(pdev, addr1, reg);
पूर्ण

/**
 *	hpt3x2n_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Perक्रमm PIO mode setup.
 */

अटल व्योम hpt3x2n_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt3x2n_set_mode(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	hpt3x2n_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 *	Set up the channel क्रम MWDMA or UDMA modes.
 */

अटल व्योम hpt3x2n_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	hpt3x2n_set_mode(ap, adev, adev->dma_mode);
पूर्ण

/**
 *	hpt3x2n_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Clean up after the HPT3x2n and later DMA engine
 */

अटल व्योम hpt3x2n_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक mscreg = 0x50 + 2 * ap->port_no;
	u8 bwsr_stat, msc_stat;

	pci_पढ़ो_config_byte(pdev, 0x6A, &bwsr_stat);
	pci_पढ़ो_config_byte(pdev, mscreg, &msc_stat);
	अगर (bwsr_stat & (1 << ap->port_no))
		pci_ग_लिखो_config_byte(pdev, mscreg, msc_stat | 0x30);
	ata_bmdma_stop(qc);
पूर्ण

/**
 *	hpt3x2n_set_घड़ी	-	घड़ी control
 *	@ap: ATA port
 *	@source: 0x21 or 0x23 क्रम PLL or PCI sourced घड़ी
 *
 *	Switch the ATA bus घड़ी between the PLL and PCI घड़ी sources
 *	जबतक correctly isolating the bus and resetting पूर्णांकernal logic
 *
 *	We must use the DPLL क्रम
 *	-	writing
 *	-	second channel UDMA7 (SATA ports) or higher
 *	-	66MHz PCI
 *
 *	or we will underघड़ी the device and get reduced perक्रमmance.
 */

अटल व्योम hpt3x2n_set_घड़ी(काष्ठा ata_port *ap, पूर्णांक source)
अणु
	व्योम __iomem *bmdma = ap->ioaddr.bmdma_addr - ap->port_no * 8;

	/* Tristate the bus */
	ioग_लिखो8(0x80, bmdma+0x73);
	ioग_लिखो8(0x80, bmdma+0x77);

	/* Switch घड़ी and reset channels */
	ioग_लिखो8(source, bmdma+0x7B);
	ioग_लिखो8(0xC0, bmdma+0x79);

	/* Reset state machines, aव्योम enabling the disabled channels */
	ioग_लिखो8(ioपढ़ो8(bmdma+0x70) | 0x32, bmdma+0x70);
	ioग_लिखो8(ioपढ़ो8(bmdma+0x74) | 0x32, bmdma+0x74);

	/* Complete reset */
	ioग_लिखो8(0x00, bmdma+0x79);

	/* Reconnect channels to bus */
	ioग_लिखो8(0x00, bmdma+0x73);
	ioग_लिखो8(0x00, bmdma+0x77);
पूर्ण

अटल पूर्णांक hpt3x2n_use_dpll(काष्ठा ata_port *ap, पूर्णांक writing)
अणु
	दीर्घ flags = (दीर्घ)ap->host->निजी_data;

	/* See अगर we should use the DPLL */
	अगर (writing)
		वापस USE_DPLL;	/* Needed क्रम ग_लिखो */
	अगर (flags & PCI66)
		वापस USE_DPLL;	/* Needed at 66Mhz */
	वापस 0;
पूर्ण

अटल पूर्णांक hpt3x2n_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_port *alt = ap->host->ports[ap->port_no ^ 1];
	पूर्णांक rc, flags = (दीर्घ)ap->host->निजी_data;
	पूर्णांक dpll = hpt3x2n_use_dpll(ap, qc->tf.flags & ATA_TFLAG_WRITE);

	/* First apply the usual rules */
	rc = ata_std_qc_defer(qc);
	अगर (rc != 0)
		वापस rc;

	अगर ((flags & USE_DPLL) != dpll && alt->qc_active)
		वापस ATA_DEFER_PORT;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक hpt3x2n_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	पूर्णांक flags = (दीर्घ)ap->host->निजी_data;
	पूर्णांक dpll = hpt3x2n_use_dpll(ap, qc->tf.flags & ATA_TFLAG_WRITE);

	अगर ((flags & USE_DPLL) != dpll) अणु
		flags &= ~USE_DPLL;
		flags |= dpll;
		ap->host->निजी_data = (व्योम *)(दीर्घ)flags;

		hpt3x2n_set_घड़ी(ap, dpll ? 0x21 : 0x23);
	पूर्ण
	वापस ata_bmdma_qc_issue(qc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा hpt3x2n_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

/*
 *	Configuration क्रम HPT302N/371N.
 */

अटल काष्ठा ata_port_operations hpt3xxn_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,

	.bmdma_stop	= hpt3x2n_bmdma_stop,

	.qc_defer	= hpt3x2n_qc_defer,
	.qc_issue	= hpt3x2n_qc_issue,

	.cable_detect	= hpt3x2n_cable_detect,
	.set_piomode	= hpt3x2n_set_piomode,
	.set_dmamode	= hpt3x2n_set_dmamode,
	.prereset	= hpt3x2n_pre_reset,
पूर्ण;

/*
 *	Configuration क्रम HPT372N. Same as 302N/371N but we have a mode filter.
 */

अटल काष्ठा ata_port_operations hpt372n_port_ops = अणु
	.inherits	= &hpt3xxn_port_ops,
	.mode_filter	= &hpt372n_filter,
पूर्ण;

/**
 *	hpt3xn_calibrate_dpll		-	Calibrate the DPLL loop
 *	@dev: PCI device
 *
 *	Perक्रमm a calibration cycle on the HPT3xN DPLL. Returns 1 अगर this
 *	succeeds
 */

अटल पूर्णांक hpt3xn_calibrate_dpll(काष्ठा pci_dev *dev)
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

अटल पूर्णांक hpt3x2n_pci_घड़ी(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ freq;
	u32 fcnt;
	अचिन्हित दीर्घ iobase = pci_resource_start(pdev, 4);

	fcnt = inl(iobase + 0x90);	/* Not PCI पढ़ोable क्रम some chips */
	अगर ((fcnt >> 12) != 0xABCDE) अणु
		पूर्णांक i;
		u16 sr;
		u32 total = 0;

		pr_warn("BIOS clock data not set\n");

		/* This is the process the HPT371 BIOS is reported to use */
		क्रम (i = 0; i < 128; i++) अणु
			pci_पढ़ो_config_word(pdev, 0x78, &sr);
			total += sr & 0x1FF;
			udelay(15);
		पूर्ण
		fcnt = total / 128;
	पूर्ण
	fcnt &= 0x1FF;

	freq = (fcnt * 77) / 192;

	/* Clamp to bands */
	अगर (freq < 40)
		वापस 33;
	अगर (freq < 45)
		वापस 40;
	अगर (freq < 55)
		वापस 50;
	वापस 66;
पूर्ण

/**
 *	hpt3x2n_init_one		-	Initialise an HPT37X/302
 *	@dev: PCI device
 *	@id: Entry in match table
 *
 *	Initialise an HPT3x2n device. There are some पूर्णांकeresting complications
 *	here. Firstly the chip may report 366 and be one of several variants.
 *	Secondly all the timings depend on the घड़ी क्रम the chip which we must
 *	detect and look up
 *
 *	This is the known chip mappings. It may be missing a couple of later
 *	releases.
 *
 *	Chip version		PCI		Rev	Notes
 *	HPT372			4 (HPT366)	5	Other driver
 *	HPT372N			4 (HPT366)	6	UDMA133
 *	HPT372			5 (HPT372)	1	Other driver
 *	HPT372N			5 (HPT372)	2	UDMA133
 *	HPT302			6 (HPT302)	*	Other driver
 *	HPT302N			6 (HPT302)	> 1	UDMA133
 *	HPT371			7 (HPT371)	*	Other driver
 *	HPT371N			7 (HPT371)	> 1	UDMA133
 *	HPT374			8 (HPT374)	*	Other driver
 *	HPT372N			9 (HPT372N)	*	UDMA133
 *
 *	(1) UDMA133 support depends on the bus घड़ी
 */

अटल पूर्णांक hpt3x2n_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	/* HPT372N - UDMA133 */
	अटल स्थिर काष्ठा ata_port_info info_hpt372n = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &hpt372n_port_ops
	पूर्ण;
	/* HPT302N and HPT371N - UDMA133 */
	अटल स्थिर काष्ठा ata_port_info info_hpt3xxn = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.port_ops = &hpt3xxn_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info_hpt3xxn, शून्य पूर्ण;
	u8 rev = dev->revision;
	u8 irqmask;
	अचिन्हित पूर्णांक pci_mhz;
	अचिन्हित पूर्णांक f_low, f_high;
	पूर्णांक adjust;
	अचिन्हित दीर्घ iobase = pci_resource_start(dev, 4);
	व्योम *hpriv = (व्योम *)USE_DPLL;
	पूर्णांक rc;

	rc = pcim_enable_device(dev);
	अगर (rc)
		वापस rc;

	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_TTI_HPT366:
		/* 372N अगर rev >= 6 */
		अगर (rev < 6)
			वापस -ENODEV;
		जाओ hpt372n;
	हाल PCI_DEVICE_ID_TTI_HPT371:
		/* 371N अगर rev >= 2 */
		अगर (rev < 2)
			वापस -ENODEV;
		अवरोध;
	हाल PCI_DEVICE_ID_TTI_HPT372:
		/* 372N अगर rev >= 2 */
		अगर (rev < 2)
			वापस -ENODEV;
		जाओ hpt372n;
	हाल PCI_DEVICE_ID_TTI_HPT302:
		/* 302N अगर rev >= 2 */
		अगर (rev < 2)
			वापस -ENODEV;
		अवरोध;
	हाल PCI_DEVICE_ID_TTI_HPT372N:
hpt372n:
		ppi[0] = &info_hpt372n;
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
	 * HPT371 chips physically have only one channel, the secondary one,
	 * but the primary channel रेजिस्टरs करो exist!  Go figure...
	 * So,  we manually disable the non-existing channel here
	 * (अगर the BIOS hasn't करोne this alपढ़ोy).
	 */
	अगर (dev->device == PCI_DEVICE_ID_TTI_HPT371) अणु
		u8 mcr1;
		pci_पढ़ो_config_byte(dev, 0x50, &mcr1);
		mcr1 &= ~0x04;
		pci_ग_लिखो_config_byte(dev, 0x50, mcr1);
	पूर्ण

	/*
	 * Tune the PLL. HPT recommend using 75 क्रम SATA, 66 क्रम UDMA133 or
	 * 50 क्रम UDMA100. Right now we always use 66
	 */

	pci_mhz = hpt3x2n_pci_घड़ी(dev);

	f_low = (pci_mhz * 48) / 66;	/* PCI Mhz क्रम 66Mhz DPLL */
	f_high = f_low + 2;		/* Tolerance */

	pci_ग_लिखो_config_dword(dev, 0x5C, (f_high << 16) | f_low | 0x100);
	/* PLL घड़ी */
	pci_ग_लिखो_config_byte(dev, 0x5B, 0x21);

	/* Unlike the 37x we करोn't try jiggling the frequency */
	क्रम (adjust = 0; adjust < 8; adjust++) अणु
		अगर (hpt3xn_calibrate_dpll(dev))
			अवरोध;
		pci_ग_लिखो_config_dword(dev, 0x5C, (f_high << 16) | f_low);
	पूर्ण
	अगर (adjust == 8) अणु
		pr_err("DPLL did not stabilize!\n");
		वापस -ENODEV;
	पूर्ण

	pr_info("bus clock %dMHz, using 66MHz DPLL\n", pci_mhz);

	/*
	 * Set our निजी data up. We only need a few flags
	 * so we use it directly.
	 */
	अगर (pci_mhz > 60)
		hpriv = (व्योम *)(PCI66 | USE_DPLL);

	/*
	 * On  HPT371N, अगर ATA घड़ी is 66 MHz we must set bit 2 in
	 * the MISC. रेजिस्टर to stretch the UltraDMA Tss timing.
	 * NOTE: This रेजिस्टर is only ग_लिखोable via I/O space.
	 */
	अगर (dev->device == PCI_DEVICE_ID_TTI_HPT371)
		outb(inb(iobase + 0x9c) | 0x04, iobase + 0x9c);

	/* Now kick off ATA set up */
	वापस ata_pci_bmdma_init_one(dev, ppi, &hpt3x2n_sht, hpriv, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hpt3x2n[] = अणु
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT366), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT371), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT302), पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372N), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver hpt3x2n_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= hpt3x2n,
	.probe		= hpt3x2n_init_one,
	.हटाओ		= ata_pci_हटाओ_one
पूर्ण;

module_pci_driver(hpt3x2n_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the Highpoint HPT3xxN");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, hpt3x2n);
MODULE_VERSION(DRV_VERSION);
