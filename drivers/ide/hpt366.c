<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999-2003		Andre Hedrick <andre@linux-ide.org>
 * Portions Copyright (C) 2001	        Sun Microप्रणालीs, Inc.
 * Portions Copyright (C) 2003		Red Hat Inc
 * Portions Copyright (C) 2007		Bartlomiej Zolnierkiewicz
 * Portions Copyright (C) 2005-2009	MontaVista Software, Inc.
 *
 * Thanks to HighPoपूर्णांक Technologies क्रम their assistance, and hardware.
 * Special Thanks to Jon Burchmore in SanDiego क्रम the deep pockets, his
 * करोnation of an ABit BP6 मुख्यboard, processor, and memory acellerated
 * development and support.
 *
 *
 * HighPoपूर्णांक has its own drivers (खोलो source except क्रम the RAID part)
 * available from http://www.highpoपूर्णांक-tech.com/USA_new/service_support.hपंचांग 
 * This may be useful to anyone wanting to work on this driver, however  करो not
 * trust  them too much since the code tends to become less and less meaningful
 * as the समय passes... :-/
 *
 * Note that final HPT370 support was करोne by क्रमce extraction of GPL.
 *
 * - add function क्रम getting/setting घातer status of drive
 * - the HPT370's state machine can get confused. reset it beक्रमe each dma 
 *   xfer to prevent that from happening.
 * - reset state engine whenever we get an error.
 * - check क्रम busmaster state at end of dma. 
 * - use new highpoपूर्णांक timings.
 * - detect bus speed using highpoपूर्णांक रेजिस्टर.
 * - use pll अगर we करोn't have a clock table. added a 66MHz table that's
 *   just 2x the 33MHz table.
 * - हटाओd turnaround. NOTE: we never want to चयन between pll and
 *   pci घड़ीs as the chip can glitch in those हालs. the highpoपूर्णांक
 *   approved workaround slows everything करोwn too much to be useful. in
 *   addition, we would have to serialize access to each chip.
 * 	Adrian Sun <a.sun@sun.com>
 *
 * add drive timings क्रम 66MHz PCI bus,
 * fix ATA Cable संकेत detection, fix incorrect /proc info
 * add /proc display क्रम per-drive PIO/DMA/UDMA mode and
 * per-channel ATA-33/66 Cable detect.
 * 	Duncan Laurie <व्योम@sun.com>
 *
 * fixup /proc output क्रम multiple controllers
 *	Tim Hockin <thockin@sun.com>
 *
 * On hpt366: 
 * Reset the hpt366 on error, reset on dma
 * Fix disabling Fast Interrupt hpt366.
 * 	Mike Waychison <crlf@sun.com>
 *
 * Added support क्रम 372N घड़ीing and घड़ी चयनing. The 372N needs
 * dअगरferent घड़ीs on पढ़ो/ग_लिखो. This requires overloading rw_disk and
 * other deeply crazy things. Thanks to <http://www.hoerstreich.de> क्रम
 * keeping me sane. 
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * - fix the घड़ी turnaround code: it was writing to the wrong ports when
 *   called क्रम the secondary channel, caching the current घड़ी mode per-
 *   channel caused the cached रेजिस्टर value to get out of sync with the
 *   actual one, the channels weren't serialized, the turnaround shouldn't
 *   be करोne on 66 MHz PCI bus
 * - disable UltraATA/100 क्रम HPT370 by शेष as the 33 MHz घड़ी being used
 *   करोes not allow क्रम this speed anyway
 * - aव्योम touching disabled channels (e.g. HPT371/N are single channel chips,
 *   their primary channel is kind of भव, it isn't tied to any pins)
 * - fix/हटाओ bad/unused timing tables and use one set of tables क्रम the whole
 *   HPT37x chip family; save space by पूर्णांकroducing the separate transfer mode
 *   table in which the mode lookup is करोne
 * - use f_CNT value saved by  the HighPoपूर्णांक BIOS as पढ़ोing it directly gives
 *   the wrong PCI frequency since DPLL has alपढ़ोy been calibrated by BIOS;
 *   पढ़ो it only from the function 0 of HPT374 chips
 * - fix the hotswap code:  it caused RESET- to glitch when tristating the bus,
 *   and क्रम HPT36x the obsolete HDIO_TRISTATE_HWIF handler was called instead
 * - pass to init_chipset() handlers a copy of the IDE PCI device काष्ठाure as
 *   they tamper with its fields
 * - pass  to the init_setup handlers a copy of the ide_pci_device_t काष्ठाure
 *   since they may tamper with its fields
 * - prefix the driver startup messages with the real chip name
 * - claim the extra 240 bytes of I/O space क्रम all chips
 * - optimize the UltraDMA filtering and the drive list lookup code
 * - use pci_get_slot() to get to the function 1 of HPT36x/374
 * - cache offset of the channel's misc. control रेजिस्टरs (MCRs) being used
 *   throughout the driver
 * - only touch the relevant MCR when detecting the cable type on HPT374's
 *   function 1
 * - नाम all the रेजिस्टर related variables consistently
 * - move all the पूर्णांकerrupt twiddling code from the speedproc handlers पूर्णांकo
 *   init_hwअगर_hpt366(), also grouping all the DMA related code together there
 * - merge HPT36x/HPT37x speedproc handlers, fix PIO timing रेजिस्टर mask and
 *   separate the UltraDMA and MWDMA masks there to aव्योम changing PIO timings
 *   when setting an UltraDMA mode
 * - fix hpt3xx_tune_drive() to set the PIO mode requested, not always select
 *   the best possible one
 * - clean up DMA समयout handling क्रम HPT370
 * - चयन to using the क्रमागतeration type to dअगरfer between the numerous chip
 *   variants, matching PCI device/revision ID with the chip type early, at the
 *   init_setup stage
 * - extend the hpt_info काष्ठाure to hold the DPLL and PCI घड़ी frequencies,
 *   stop duplicating it क्रम each channel by storing the poपूर्णांकer in the pci_dev
 *   काष्ठाure: first, at the init_setup stage, poपूर्णांक it to a अटल "template"
 *   with only the chip type and its specअगरic base DPLL frequency, the highest
 *   UltraDMA mode, and the chip settings table poपूर्णांकer filled,  then, at the
 *   init_chipset stage, allocate per-chip instance  and fill it with the rest
 *   of the necessary inक्रमmation
 * - get rid of the स्थिरant thresholds in the HPT37x PCI घड़ी detection code,
 *   चयन  to calculating  PCI घड़ी frequency based on the chip's base DPLL
 *   frequency
 * - चयन to using the  DPLL घड़ी and enable UltraATA/133 mode by शेष on
 *   anything  newer than HPT370/A (except HPT374 that is not capable of this
 *   mode according to the manual)
 * - fold PCI घड़ी detection and DPLL setup code पूर्णांकo init_chipset_hpt366(),
 *   also fixing the पूर्णांकerchanged 25/40 MHz PCI घड़ी हालs क्रम HPT36x chips;
 *   unअगरy HPT36x/37x timing setup code and the speedproc handlers by joining
 *   the रेजिस्टर setting lists पूर्णांकo the table indexed by the घड़ी selected
 * - set the correct hwअगर->ultra_mask क्रम each inभागidual chip
 * - add Ultra and MW DMA mode filtering क्रम the HPT37[24] based SATA cards
 * - stop resetting HPT370's state machine beक्रमe each DMA transfer as that has
 *   caused more harm than good
 *	Sergei Shtylyov, <sshtylyov@ru.mvista.com> or <source@mvista.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "hpt366"

/* various tuning parameters */
#अघोषित	HPT_RESET_STATE_ENGINE
#अघोषित	HPT_DELAY_INTERRUPT

अटल स्थिर अक्षर *bad_ata100_5[] = अणु
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

अटल स्थिर अक्षर *bad_ata66_4[] = अणु
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
	"MAXTOR STM3320620A",
	शून्य
पूर्ण;

अटल स्थिर अक्षर *bad_ata66_3[] = अणु
	"WDC AC310200R",
	शून्य
पूर्ण;

अटल स्थिर अक्षर *bad_ata33[] = अणु
	"Maxtor 92720U8", "Maxtor 92040U6", "Maxtor 91360U4", "Maxtor 91020U3", "Maxtor 90845U3", "Maxtor 90650U2",
	"Maxtor 91360D8", "Maxtor 91190D7", "Maxtor 91020D6", "Maxtor 90845D5", "Maxtor 90680D4", "Maxtor 90510D3", "Maxtor 90340D2",
	"Maxtor 91152D8", "Maxtor 91008D7", "Maxtor 90845D6", "Maxtor 90840D6", "Maxtor 90720D5", "Maxtor 90648D5", "Maxtor 90576D4",
	"Maxtor 90510D4",
	"Maxtor 90432D3", "Maxtor 90288D2", "Maxtor 90256D2",
	"Maxtor 91000D8", "Maxtor 90910D8", "Maxtor 90875D7", "Maxtor 90840D7", "Maxtor 90750D6", "Maxtor 90625D5", "Maxtor 90500D4",
	"Maxtor 91728D8", "Maxtor 91512D7", "Maxtor 91303D6", "Maxtor 91080D5", "Maxtor 90845D4", "Maxtor 90680D4", "Maxtor 90648D3", "Maxtor 90432D2",
	शून्य
पूर्ण;

अटल u8 xfer_speeds[] = अणु
	XFER_UDMA_6,
	XFER_UDMA_5,
	XFER_UDMA_4,
	XFER_UDMA_3,
	XFER_UDMA_2,
	XFER_UDMA_1,
	XFER_UDMA_0,

	XFER_MW_DMA_2,
	XFER_MW_DMA_1,
	XFER_MW_DMA_0,

	XFER_PIO_4,
	XFER_PIO_3,
	XFER_PIO_2,
	XFER_PIO_1,
	XFER_PIO_0
पूर्ण;

/* Key क्रम bus घड़ी timings
 * 36x   37x
 * bits  bits
 * 0:3	 0:3	data_high_समय. Inactive समय of DIOW_/DIOR_ क्रम PIO and MW DMA.
 *		cycles = value + 1
 * 4:7	 4:8	data_low_समय. Active समय of DIOW_/DIOR_ क्रम PIO and MW DMA.
 *		cycles = value + 1
 * 8:11  9:12	cmd_high_समय. Inactive समय of DIOW_/DIOR_ during task file
 *		रेजिस्टर access.
 * 12:15 13:17	cmd_low_समय. Active समय of DIOW_/DIOR_ during task file
 *		रेजिस्टर access.
 * 16:18 18:20	udma_cycle_समय. Clock cycles क्रम UDMA xfer.
 * -	 21	CLK frequency: 0=ATA घड़ी, 1=dual ATA घड़ी.
 * 19:21 22:24	pre_high_समय. Time to initialize the 1st cycle क्रम PIO and
 *		MW DMA xfer.
 * 22:24 25:27	cmd_pre_high_समय. Time to initialize the 1st PIO cycle क्रम
 *		task file रेजिस्टर access.
 * 28	 28	UDMA enable.
 * 29	 29	DMA  enable.
 * 30	 30	PIO MST enable. If set, the chip is in bus master mode during
 *		PIO xfer.
 * 31	 31	FIFO enable.
 */

अटल u32 क्रमty_base_hpt36x[] = अणु
	/* XFER_UDMA_6 */	0x900fd943,
	/* XFER_UDMA_5 */	0x900fd943,
	/* XFER_UDMA_4 */	0x900fd943,
	/* XFER_UDMA_3 */	0x900ad943,
	/* XFER_UDMA_2 */	0x900bd943,
	/* XFER_UDMA_1 */	0x9008d943,
	/* XFER_UDMA_0 */	0x9008d943,

	/* XFER_MW_DMA_2 */	0xa008d943,
	/* XFER_MW_DMA_1 */	0xa010d955,
	/* XFER_MW_DMA_0 */	0xa010d9fc,

	/* XFER_PIO_4 */	0xc008d963,
	/* XFER_PIO_3 */	0xc010d974,
	/* XFER_PIO_2 */	0xc010d997,
	/* XFER_PIO_1 */	0xc010d9c7,
	/* XFER_PIO_0 */	0xc018d9d9
पूर्ण;

अटल u32 thirty_three_base_hpt36x[] = अणु
	/* XFER_UDMA_6 */	0x90c9a731,
	/* XFER_UDMA_5 */	0x90c9a731,
	/* XFER_UDMA_4 */	0x90c9a731,
	/* XFER_UDMA_3 */	0x90cfa731,
	/* XFER_UDMA_2 */	0x90caa731,
	/* XFER_UDMA_1 */	0x90cba731,
	/* XFER_UDMA_0 */	0x90c8a731,

	/* XFER_MW_DMA_2 */	0xa0c8a731,
	/* XFER_MW_DMA_1 */	0xa0c8a732,	/* 0xa0c8a733 */
	/* XFER_MW_DMA_0 */	0xa0c8a797,

	/* XFER_PIO_4 */	0xc0c8a731,
	/* XFER_PIO_3 */	0xc0c8a742,
	/* XFER_PIO_2 */	0xc0d0a753,
	/* XFER_PIO_1 */	0xc0d0a7a3,	/* 0xc0d0a793 */
	/* XFER_PIO_0 */	0xc0d0a7aa	/* 0xc0d0a7a7 */
पूर्ण;

अटल u32 twenty_five_base_hpt36x[] = अणु
	/* XFER_UDMA_6 */	0x90c98521,
	/* XFER_UDMA_5 */	0x90c98521,
	/* XFER_UDMA_4 */	0x90c98521,
	/* XFER_UDMA_3 */	0x90cf8521,
	/* XFER_UDMA_2 */	0x90cf8521,
	/* XFER_UDMA_1 */	0x90cb8521,
	/* XFER_UDMA_0 */	0x90cb8521,

	/* XFER_MW_DMA_2 */	0xa0ca8521,
	/* XFER_MW_DMA_1 */	0xa0ca8532,
	/* XFER_MW_DMA_0 */	0xa0ca8575,

	/* XFER_PIO_4 */	0xc0ca8521,
	/* XFER_PIO_3 */	0xc0ca8532,
	/* XFER_PIO_2 */	0xc0ca8542,
	/* XFER_PIO_1 */	0xc0d08572,
	/* XFER_PIO_0 */	0xc0d08585
पूर्ण;

/*
 * The following are the new timing tables with PIO mode data/taskfile transfer
 * overघड़ीing fixed...
 */

/* This table is taken from the HPT370 data manual rev. 1.02 */
अटल u32 thirty_three_base_hpt37x[] = अणु
	/* XFER_UDMA_6 */	0x16455031,	/* 0x16655031 ?? */
	/* XFER_UDMA_5 */	0x16455031,
	/* XFER_UDMA_4 */	0x16455031,
	/* XFER_UDMA_3 */	0x166d5031,
	/* XFER_UDMA_2 */	0x16495031,
	/* XFER_UDMA_1 */	0x164d5033,
	/* XFER_UDMA_0 */	0x16515097,

	/* XFER_MW_DMA_2 */	0x26515031,
	/* XFER_MW_DMA_1 */	0x26515033,
	/* XFER_MW_DMA_0 */	0x26515097,

	/* XFER_PIO_4 */	0x06515021,
	/* XFER_PIO_3 */	0x06515022,
	/* XFER_PIO_2 */	0x06515033,
	/* XFER_PIO_1 */	0x06915065,
	/* XFER_PIO_0 */	0x06d1508a
पूर्ण;

अटल u32 fअगरty_base_hpt37x[] = अणु
	/* XFER_UDMA_6 */	0x1a861842,
	/* XFER_UDMA_5 */	0x1a861842,
	/* XFER_UDMA_4 */	0x1aae1842,
	/* XFER_UDMA_3 */	0x1a8e1842,
	/* XFER_UDMA_2 */	0x1a0e1842,
	/* XFER_UDMA_1 */	0x1a161854,
	/* XFER_UDMA_0 */	0x1a1a18ea,

	/* XFER_MW_DMA_2 */	0x2a821842,
	/* XFER_MW_DMA_1 */	0x2a821854,
	/* XFER_MW_DMA_0 */	0x2a8218ea,

	/* XFER_PIO_4 */	0x0a821842,
	/* XFER_PIO_3 */	0x0a821843,
	/* XFER_PIO_2 */	0x0a821855,
	/* XFER_PIO_1 */	0x0ac218a8,
	/* XFER_PIO_0 */	0x0b02190c
पूर्ण;

अटल u32 sixty_six_base_hpt37x[] = अणु
	/* XFER_UDMA_6 */	0x1c86fe62,
	/* XFER_UDMA_5 */	0x1caefe62,	/* 0x1c8afe62 */
	/* XFER_UDMA_4 */	0x1c8afe62,
	/* XFER_UDMA_3 */	0x1c8efe62,
	/* XFER_UDMA_2 */	0x1c92fe62,
	/* XFER_UDMA_1 */	0x1c9afe62,
	/* XFER_UDMA_0 */	0x1c82fe62,

	/* XFER_MW_DMA_2 */	0x2c82fe62,
	/* XFER_MW_DMA_1 */	0x2c82fe66,
	/* XFER_MW_DMA_0 */	0x2c82ff2e,

	/* XFER_PIO_4 */	0x0c82fe62,
	/* XFER_PIO_3 */	0x0c82fe84,
	/* XFER_PIO_2 */	0x0c82fea6,
	/* XFER_PIO_1 */	0x0d02ff26,
	/* XFER_PIO_0 */	0x0d42ff7f
पूर्ण;

#घोषणा HPT371_ALLOW_ATA133_6		1
#घोषणा HPT302_ALLOW_ATA133_6		1
#घोषणा HPT372_ALLOW_ATA133_6		1
#घोषणा HPT370_ALLOW_ATA100_5		0
#घोषणा HPT366_ALLOW_ATA66_4		1
#घोषणा HPT366_ALLOW_ATA66_3		1

/* Supported ATA घड़ी frequencies */
क्रमागत ata_घड़ी अणु
	ATA_CLOCK_25MHZ,
	ATA_CLOCK_33MHZ,
	ATA_CLOCK_40MHZ,
	ATA_CLOCK_50MHZ,
	ATA_CLOCK_66MHZ,
	NUM_ATA_CLOCKS
पूर्ण;

काष्ठा hpt_timings अणु
	u32 pio_mask;
	u32 dma_mask;
	u32 ultra_mask;
	u32 *घड़ी_प्रकारable[NUM_ATA_CLOCKS];
पूर्ण;

/*
 *	Hold all the HighPoपूर्णांक chip inक्रमmation in one place.
 */

काष्ठा hpt_info अणु
	अक्षर *chip_name;	/* Chip name */
	u8 chip_type;		/* Chip type */
	u8 udma_mask;		/* Allowed UltraDMA modes mask. */
	u8 dpll_clk;		/* DPLL घड़ी in MHz */
	u8 pci_clk;		/* PCI  घड़ी in MHz */
	काष्ठा hpt_timings *timings; /* Chipset timing data */
	u8 घड़ी;		/* ATA घड़ी selected */
पूर्ण;

/* Supported HighPoपूर्णांक chips */
क्रमागत अणु
	HPT36x,
	HPT370,
	HPT370A,
	HPT374,
	HPT372,
	HPT372A,
	HPT302,
	HPT371,
	HPT372N,
	HPT302N,
	HPT371N
पूर्ण;

अटल काष्ठा hpt_timings hpt36x_timings = अणु
	.pio_mask	= 0xc1f8ffff,
	.dma_mask	= 0x303800ff,
	.ultra_mask	= 0x30070000,
	.घड़ी_प्रकारable	= अणु
		[ATA_CLOCK_25MHZ] = twenty_five_base_hpt36x,
		[ATA_CLOCK_33MHZ] = thirty_three_base_hpt36x,
		[ATA_CLOCK_40MHZ] = क्रमty_base_hpt36x,
		[ATA_CLOCK_50MHZ] = शून्य,
		[ATA_CLOCK_66MHZ] = शून्य
	पूर्ण
पूर्ण;

अटल काष्ठा hpt_timings hpt37x_timings = अणु
	.pio_mask	= 0xcfc3ffff,
	.dma_mask	= 0x31c001ff,
	.ultra_mask	= 0x303c0000,
	.घड़ी_प्रकारable	= अणु
		[ATA_CLOCK_25MHZ] = शून्य,
		[ATA_CLOCK_33MHZ] = thirty_three_base_hpt37x,
		[ATA_CLOCK_40MHZ] = शून्य,
		[ATA_CLOCK_50MHZ] = fअगरty_base_hpt37x,
		[ATA_CLOCK_66MHZ] = sixty_six_base_hpt37x
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt36x = अणु
	.chip_name	= "HPT36x",
	.chip_type	= HPT36x,
	.udma_mask	= HPT366_ALLOW_ATA66_3 ? (HPT366_ALLOW_ATA66_4 ? ATA_UDMA4 : ATA_UDMA3) : ATA_UDMA2,
	.dpll_clk	= 0,	/* no DPLL */
	.timings	= &hpt36x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt370 = अणु
	.chip_name	= "HPT370",
	.chip_type	= HPT370,
	.udma_mask	= HPT370_ALLOW_ATA100_5 ? ATA_UDMA5 : ATA_UDMA4,
	.dpll_clk	= 48,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt370a = अणु
	.chip_name	= "HPT370A",
	.chip_type	= HPT370A,
	.udma_mask	= HPT370_ALLOW_ATA100_5 ? ATA_UDMA5 : ATA_UDMA4,
	.dpll_clk	= 48,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt374 = अणु
	.chip_name	= "HPT374",
	.chip_type	= HPT374,
	.udma_mask	= ATA_UDMA5,
	.dpll_clk	= 48,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt372 = अणु
	.chip_name	= "HPT372",
	.chip_type	= HPT372,
	.udma_mask	= HPT372_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 55,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt372a = अणु
	.chip_name	= "HPT372A",
	.chip_type	= HPT372A,
	.udma_mask	= HPT372_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 66,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt302 = अणु
	.chip_name	= "HPT302",
	.chip_type	= HPT302,
	.udma_mask	= HPT302_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 66,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt371 = अणु
	.chip_name	= "HPT371",
	.chip_type	= HPT371,
	.udma_mask	= HPT371_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 66,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt372n = अणु
	.chip_name	= "HPT372N",
	.chip_type	= HPT372N,
	.udma_mask	= HPT372_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 77,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt302n = अणु
	.chip_name	= "HPT302N",
	.chip_type	= HPT302N,
	.udma_mask	= HPT302_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 77,
	.timings	= &hpt37x_timings
पूर्ण;

अटल स्थिर काष्ठा hpt_info hpt371n = अणु
	.chip_name	= "HPT371N",
	.chip_type	= HPT371N,
	.udma_mask	= HPT371_ALLOW_ATA133_6 ? ATA_UDMA6 : ATA_UDMA5,
	.dpll_clk	= 77,
	.timings	= &hpt37x_timings
पूर्ण;

अटल bool check_in_drive_list(ide_drive_t *drive, स्थिर अक्षर **list)
अणु
	वापस match_string(list, -1, (अक्षर *)&drive->id[ATA_ID_PROD]) >= 0;
पूर्ण

अटल काष्ठा hpt_info *hpt3xx_get_info(काष्ठा device *dev)
अणु
	काष्ठा ide_host *host	= dev_get_drvdata(dev);
	काष्ठा hpt_info *info	= (काष्ठा hpt_info *)host->host_priv;

	वापस dev == host->dev[1] ? info + 1 : info;
पूर्ण

/*
 * The Marvell bridge chips used on the HighPoपूर्णांक SATA cards करो not seem
 * to support the UltraDMA modes 1, 2, and 3 as well as any MWDMA modes...
 */

अटल u8 hpt3xx_udma_filter(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा hpt_info *info	= hpt3xx_get_info(hwअगर->dev);
	u8 mask 		= hwअगर->ultra_mask;

	चयन (info->chip_type) अणु
	हाल HPT36x:
		अगर (!HPT366_ALLOW_ATA66_4 ||
		    check_in_drive_list(drive, bad_ata66_4))
			mask = ATA_UDMA3;

		अगर (!HPT366_ALLOW_ATA66_3 ||
		    check_in_drive_list(drive, bad_ata66_3))
			mask = ATA_UDMA2;
		अवरोध;
	हाल HPT370:
		अगर (!HPT370_ALLOW_ATA100_5 ||
		    check_in_drive_list(drive, bad_ata100_5))
			mask = ATA_UDMA4;
		अवरोध;
	हाल HPT370A:
		अगर (!HPT370_ALLOW_ATA100_5 ||
		    check_in_drive_list(drive, bad_ata100_5))
			वापस ATA_UDMA4;
		fallthrough;
	हाल HPT372 :
	हाल HPT372A:
	हाल HPT372N:
	हाल HPT374 :
		अगर (ata_id_is_sata(drive->id))
			mask &= ~0x0e;
		fallthrough;
	शेष:
		वापस mask;
	पूर्ण

	वापस check_in_drive_list(drive, bad_ata33) ? 0x00 : mask;
पूर्ण

अटल u8 hpt3xx_mdma_filter(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा hpt_info *info	= hpt3xx_get_info(hwअगर->dev);

	चयन (info->chip_type) अणु
	हाल HPT372 :
	हाल HPT372A:
	हाल HPT372N:
	हाल HPT374 :
		अगर (ata_id_is_sata(drive->id))
			वापस 0x00;
		fallthrough;
	शेष:
		वापस 0x07;
	पूर्ण
पूर्ण

अटल u32 get_speed_setting(u8 speed, काष्ठा hpt_info *info)
अणु
	पूर्णांक i;

	/*
	 * Lookup the transfer mode table to get the index पूर्णांकo
	 * the timing table.
	 *
	 * NOTE: For XFER_PIO_SLOW, PIO mode 0 timings will be used.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(xfer_speeds) - 1; i++)
		अगर (xfer_speeds[i] == speed)
			अवरोध;

	वापस info->timings->घड़ी_प्रकारable[info->घड़ी][i];
पूर्ण

अटल व्योम hpt3xx_set_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	काष्ठा hpt_info *info	= hpt3xx_get_info(hwअगर->dev);
	काष्ठा hpt_timings *t	= info->timings;
	u8  itr_addr		= 0x40 + (drive->dn * 4);
	u32 old_itr		= 0;
	स्थिर u8 speed		= drive->dma_mode;
	u32 new_itr		= get_speed_setting(speed, info);
	u32 itr_mask		= speed < XFER_MW_DMA_0 ? t->pio_mask :
				 (speed < XFER_UDMA_0   ? t->dma_mask :
							  t->ultra_mask);

	pci_पढ़ो_config_dword(dev, itr_addr, &old_itr);
	new_itr = (old_itr & ~itr_mask) | (new_itr & itr_mask);
	/*
	 * Disable on-chip PIO FIFO/buffer (and PIO MST mode as well)
	 * to aव्योम problems handling I/O errors later
	 */
	new_itr &= ~0xc0000000;

	pci_ग_लिखो_config_dword(dev, itr_addr, new_itr);
पूर्ण

अटल व्योम hpt3xx_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	hpt3xx_set_mode(hwअगर, drive);
पूर्ण

अटल व्योम hpt3xx_maskproc(ide_drive_t *drive, पूर्णांक mask)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev	*dev	= to_pci_dev(hwअगर->dev);
	काष्ठा hpt_info *info	= hpt3xx_get_info(hwअगर->dev);

	अगर ((drive->dev_flags & IDE_DFLAG_NIEN_QUIRK) == 0)
		वापस;

	अगर (info->chip_type >= HPT370) अणु
		u8 scr1 = 0;

		pci_पढ़ो_config_byte(dev, 0x5a, &scr1);
		अगर (((scr1 & 0x10) >> 4) != mask) अणु
			अगर (mask)
				scr1 |=  0x10;
			अन्यथा
				scr1 &= ~0x10;
			pci_ग_लिखो_config_byte(dev, 0x5a, scr1);
		पूर्ण
	पूर्ण अन्यथा अगर (mask)
		disable_irq(hwअगर->irq);
	अन्यथा
		enable_irq(hwअगर->irq);
पूर्ण

/*
 * This is specअगरic to the HPT366 UDMA chipset
 * by HighPoपूर्णांक|Triones Technologies, Inc.
 */
अटल व्योम hpt366_dma_lost_irq(ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(drive->hwअगर->dev);
	u8 mcr1 = 0, mcr3 = 0, scr1 = 0;

	pci_पढ़ो_config_byte(dev, 0x50, &mcr1);
	pci_पढ़ो_config_byte(dev, 0x52, &mcr3);
	pci_पढ़ो_config_byte(dev, 0x5a, &scr1);
	prपूर्णांकk("%s: (%s)  mcr1=0x%02x, mcr3=0x%02x, scr1=0x%02x\n",
		drive->name, __func__, mcr1, mcr3, scr1);
	अगर (scr1 & 0x10)
		pci_ग_लिखो_config_byte(dev, 0x5a, scr1 & ~0x10);
	ide_dma_lost_irq(drive);
पूर्ण

अटल व्योम hpt370_clear_engine(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	pci_ग_लिखो_config_byte(dev, hwअगर->select_data, 0x37);
	udelay(10);
पूर्ण

अटल व्योम hpt370_irq_समयout(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u16 bfअगरo		= 0;
	u8  dma_cmd;

	pci_पढ़ो_config_word(dev, hwअगर->select_data + 2, &bfअगरo);
	prपूर्णांकk(KERN_DEBUG "%s: %d bytes in FIFO\n", drive->name, bfअगरo & 0x1ff);

	/* get DMA command mode */
	dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
	/* stop DMA */
	outb(dma_cmd & ~ATA_DMA_START, hwअगर->dma_base + ATA_DMA_CMD);
	hpt370_clear_engine(drive);
पूर्ण

अटल व्योम hpt370_dma_start(ide_drive_t *drive)
अणु
#अगर_घोषित HPT_RESET_STATE_ENGINE
	hpt370_clear_engine(drive);
#पूर्ण_अगर
	ide_dma_start(drive);
पूर्ण

अटल पूर्णांक hpt370_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	u8  dma_stat		= inb(hwअगर->dma_base + ATA_DMA_STATUS);

	अगर (dma_stat & ATA_DMA_ACTIVE) अणु
		/* रुको a little */
		udelay(20);
		dma_stat = inb(hwअगर->dma_base + ATA_DMA_STATUS);
		अगर (dma_stat & ATA_DMA_ACTIVE)
			hpt370_irq_समयout(drive);
	पूर्ण
	वापस ide_dma_end(drive);
पूर्ण

/* वापसs 1 अगर DMA IRQ issued, 0 otherwise */
अटल पूर्णांक hpt374_dma_test_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u16 bfअगरo		= 0;
	u8  dma_stat;

	pci_पढ़ो_config_word(dev, hwअगर->select_data + 2, &bfअगरo);
	अगर (bfअगरo & 0x1FF) अणु
//		prपूर्णांकk("%s: %d bytes in FIFO\n", drive->name, bfअगरo);
		वापस 0;
	पूर्ण

	dma_stat = inb(hwअगर->dma_base + ATA_DMA_STATUS);
	/* वापस 1 अगर INTR निश्चितed */
	अगर (dma_stat & ATA_DMA_INTR)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hpt374_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 mcr	= 0, mcr_addr	= hwअगर->select_data;
	u8 bwsr = 0, mask	= hwअगर->channel ? 0x02 : 0x01;

	pci_पढ़ो_config_byte(dev, 0x6a, &bwsr);
	pci_पढ़ो_config_byte(dev, mcr_addr, &mcr);
	अगर (bwsr & mask)
		pci_ग_लिखो_config_byte(dev, mcr_addr, mcr | 0x30);
	वापस ide_dma_end(drive);
पूर्ण

/**
 *	hpt3xxn_set_घड़ी	-	perक्रमm घड़ी चयनing dance
 *	@hwअगर: hwअगर to चयन
 *	@mode: घड़ीing mode (0x21 क्रम ग_लिखो, 0x23 otherwise)
 *
 *	Switch the DPLL घड़ी on the HPT3xxN devices. This is a	right mess.
 */

अटल व्योम hpt3xxn_set_घड़ी(ide_hwअगर_t *hwअगर, u8 mode)
अणु
	अचिन्हित दीर्घ base = hwअगर->extra_base;
	u8 scr2 = inb(base + 0x6b);

	अगर ((scr2 & 0x7f) == mode)
		वापस;

	/* Tristate the bus */
	outb(0x80, base + 0x63);
	outb(0x80, base + 0x67);

	/* Switch घड़ी and reset channels */
	outb(mode, base + 0x6b);
	outb(0xc0, base + 0x69);

	/*
	 * Reset the state machines.
	 * NOTE: aव्योम accidentally enabling the disabled channels.
	 */
	outb(inb(base + 0x60) | 0x32, base + 0x60);
	outb(inb(base + 0x64) | 0x32, base + 0x64);

	/* Complete reset */
	outb(0x00, base + 0x69);

	/* Reconnect channels to bus */
	outb(0x00, base + 0x63);
	outb(0x00, base + 0x67);
पूर्ण

/**
 *	hpt3xxn_rw_disk		-	prepare क्रम I/O
 *	@drive: drive क्रम command
 *	@rq: block request काष्ठाure
 *
 *	This is called when a disk I/O is issued to HPT3xxN.
 *	We need it because of the घड़ी चयनing.
 */

अटल व्योम hpt3xxn_rw_disk(ide_drive_t *drive, काष्ठा request *rq)
अणु
	hpt3xxn_set_घड़ी(drive->hwअगर, rq_data_dir(rq) ? 0x21 : 0x23);
पूर्ण

/**
 *	hpt37x_calibrate_dpll	-	calibrate the DPLL
 *	@dev: PCI device
 *
 *	Perक्रमm a calibration cycle on the DPLL.
 *	Returns 1 अगर this succeeds
 */
अटल पूर्णांक hpt37x_calibrate_dpll(काष्ठा pci_dev *dev, u16 f_low, u16 f_high)
अणु
	u32 dpll = (f_high << 16) | f_low | 0x100;
	u8  scr2;
	पूर्णांक i;

	pci_ग_लिखो_config_dword(dev, 0x5c, dpll);

	/* Wait क्रम oscillator पढ़ोy */
	क्रम(i = 0; i < 0x5000; ++i) अणु
		udelay(50);
		pci_पढ़ो_config_byte(dev, 0x5b, &scr2);
		अगर (scr2 & 0x80)
			अवरोध;
	पूर्ण
	/* See अगर it stays पढ़ोy (we'll just bail out if it's not yet) */
	क्रम(i = 0; i < 0x1000; ++i) अणु
		pci_पढ़ो_config_byte(dev, 0x5b, &scr2);
		/* DPLL destabilized? */
		अगर(!(scr2 & 0x80))
			वापस 0;
	पूर्ण
	/* Turn off tuning, we have the DPLL set */
	pci_पढ़ो_config_dword (dev, 0x5c, &dpll);
	pci_ग_लिखो_config_dword(dev, 0x5c, (dpll & ~0x100));
	वापस 1;
पूर्ण

अटल व्योम hpt3xx_disable_fast_irq(काष्ठा pci_dev *dev, u8 mcr_addr)
अणु
	काष्ठा ide_host *host	= pci_get_drvdata(dev);
	काष्ठा hpt_info *info	= host->host_priv + (&dev->dev == host->dev[1]);
	u8  chip_type		= info->chip_type;
	u8  new_mcr, old_mcr	= 0;

	/*
	 * Disable the "fast interrupt" prediction.  Don't hold off
	 * on पूर्णांकerrupts. (== 0x01 despite what the करोcs say)
	 */
	pci_पढ़ो_config_byte(dev, mcr_addr + 1, &old_mcr);

	अगर (chip_type >= HPT374)
		new_mcr = old_mcr & ~0x07;
	अन्यथा अगर (chip_type >= HPT370) अणु
		new_mcr = old_mcr;
		new_mcr &= ~0x02;
#अगर_घोषित HPT_DELAY_INTERRUPT
		new_mcr &= ~0x01;
#अन्यथा
		new_mcr |=  0x01;
#पूर्ण_अगर
	पूर्ण अन्यथा					/* HPT366 and HPT368  */
		new_mcr = old_mcr & ~0x80;

	अगर (new_mcr != old_mcr)
		pci_ग_लिखो_config_byte(dev, mcr_addr + 1, new_mcr);
पूर्ण

अटल पूर्णांक init_chipset_hpt366(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ io_base	= pci_resource_start(dev, 4);
	काष्ठा hpt_info *info	= hpt3xx_get_info(&dev->dev);
	स्थिर अक्षर *name	= DRV_NAME;
	u8 pci_clk,  dpll_clk	= 0;	/* PCI and DPLL घड़ी in MHz */
	u8 chip_type;
	क्रमागत ata_घड़ी	घड़ी;

	chip_type = info->chip_type;

	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, (L1_CACHE_BYTES / 4));
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 0x78);
	pci_ग_लिखो_config_byte(dev, PCI_MIN_GNT, 0x08);
	pci_ग_लिखो_config_byte(dev, PCI_MAX_LAT, 0x08);

	/*
	 * First, try to estimate the PCI घड़ी frequency...
	 */
	अगर (chip_type >= HPT370) अणु
		u8  scr1  = 0;
		u16 f_cnt = 0;
		u32 temp  = 0;

		/* Interrupt क्रमce enable. */
		pci_पढ़ो_config_byte(dev, 0x5a, &scr1);
		अगर (scr1 & 0x10)
			pci_ग_लिखो_config_byte(dev, 0x5a, scr1 & ~0x10);

		/*
		 * HighPoपूर्णांक करोes this क्रम HPT372A.
		 * NOTE: This रेजिस्टर is only ग_लिखोable via I/O space.
		 */
		अगर (chip_type == HPT372A)
			outb(0x0e, io_base + 0x9c);

		/*
		 * Default to PCI घड़ी. Make sure MA15/16 are set to output
		 * to prevent drives having problems with 40-pin cables.
		 */
		pci_ग_लिखो_config_byte(dev, 0x5b, 0x23);

		/*
		 * We'll have to पढ़ो f_CNT value in order to determine
		 * the PCI घड़ी frequency according to the following ratio:
		 *
		 * f_CNT = Fpci * 192 / Fdpll
		 *
		 * First try पढ़ोing the रेजिस्टर in which the HighPoपूर्णांक BIOS
		 * saves f_CNT value beक्रमe  reprogramming the DPLL from its
		 * शेष setting (which dअगरfers क्रम the various chips).
		 *
		 * NOTE: This रेजिस्टर is only accessible via I/O space;
		 * HPT374 BIOS only saves it क्रम the function 0, so we have to
		 * always पढ़ो it from there -- no need to check the result of
		 * pci_get_slot() क्रम the function 0 as the whole device has
		 * been alपढ़ोy "pinned" (via function 1) in init_setup_hpt374()
		 */
		अगर (chip_type == HPT374 && (PCI_FUNC(dev->devfn) & 1)) अणु
			काष्ठा pci_dev	*dev1 = pci_get_slot(dev->bus,
							     dev->devfn - 1);
			अचिन्हित दीर्घ io_base = pci_resource_start(dev1, 4);

			temp =	inl(io_base + 0x90);
			pci_dev_put(dev1);
		पूर्ण अन्यथा
			temp =	inl(io_base + 0x90);

		/*
		 * In हाल the signature check fails, we'll have to
		 * resort to पढ़ोing the f_CNT रेजिस्टर itself in hopes
		 * that nobody has touched the DPLL yet...
		 */
		अगर ((temp & 0xFFFFF000) != 0xABCDE000) अणु
			पूर्णांक i;

			prपूर्णांकk(KERN_WARNING "%s %s: no clock data saved by "
				"BIOS\n", name, pci_name(dev));

			/* Calculate the average value of f_CNT. */
			क्रम (temp = i = 0; i < 128; i++) अणु
				pci_पढ़ो_config_word(dev, 0x78, &f_cnt);
				temp += f_cnt & 0x1ff;
				mdelay(1);
			पूर्ण
			f_cnt = temp / 128;
		पूर्ण अन्यथा
			f_cnt = temp & 0x1ff;

		dpll_clk = info->dpll_clk;
		pci_clk  = (f_cnt * dpll_clk) / 192;

		/* Clamp PCI घड़ी to bands. */
		अगर (pci_clk < 40)
			pci_clk = 33;
		अन्यथा अगर(pci_clk < 45)
			pci_clk = 40;
		अन्यथा अगर(pci_clk < 55)
			pci_clk = 50;
		अन्यथा
			pci_clk = 66;

		prपूर्णांकk(KERN_INFO "%s %s: DPLL base: %d MHz, f_CNT: %d, "
			"assuming %d MHz PCI\n", name, pci_name(dev),
			dpll_clk, f_cnt, pci_clk);
	पूर्ण अन्यथा अणु
		u32 itr1 = 0;

		pci_पढ़ो_config_dword(dev, 0x40, &itr1);

		/* Detect PCI घड़ी by looking at cmd_high_समय. */
		चयन ((itr1 >> 8) & 0x0f) अणु
			हाल 0x09:
				pci_clk = 40;
				अवरोध;
			हाल 0x05:
				pci_clk = 25;
				अवरोध;
			हाल 0x07:
			शेष:
				pci_clk = 33;
				अवरोध;
		पूर्ण
	पूर्ण

	/* Let's assume we'll use PCI घड़ी क्रम the ATA घड़ी... */
	चयन (pci_clk) अणु
		हाल 25:
			घड़ी = ATA_CLOCK_25MHZ;
			अवरोध;
		हाल 33:
		शेष:
			घड़ी = ATA_CLOCK_33MHZ;
			अवरोध;
		हाल 40:
			घड़ी = ATA_CLOCK_40MHZ;
			अवरोध;
		हाल 50:
			घड़ी = ATA_CLOCK_50MHZ;
			अवरोध;
		हाल 66:
			घड़ी = ATA_CLOCK_66MHZ;
			अवरोध;
	पूर्ण

	/*
	 * Only try the DPLL अगर we करोn't have a table क्रम the PCI घड़ी that
	 * we are running at क्रम HPT370/A, always use it  क्रम anything newer...
	 *
	 * NOTE: Using the पूर्णांकernal DPLL results in slow पढ़ोs on 33 MHz PCI.
	 * We also  करोn't like using  the DPLL because this causes glitches
	 * on PRST-/SRST- when the state engine माला_लो reset...
	 */
	अगर (chip_type >= HPT374 || info->timings->घड़ी_प्रकारable[घड़ी] == शून्य) अणु
		u16 f_low, delta = pci_clk < 50 ? 2 : 4;
		पूर्णांक adjust;

		 /*
		  * Select 66 MHz DPLL घड़ी only अगर UltraATA/133 mode is
		  * supported/enabled, use 50 MHz DPLL घड़ी otherwise...
		  */
		अगर (info->udma_mask == ATA_UDMA6) अणु
			dpll_clk = 66;
			घड़ी = ATA_CLOCK_66MHZ;
		पूर्ण अन्यथा अगर (dpll_clk) अणु	/* HPT36x chips करोn't have DPLL */
			dpll_clk = 50;
			घड़ी = ATA_CLOCK_50MHZ;
		पूर्ण

		अगर (info->timings->घड़ी_प्रकारable[घड़ी] == शून्य) अणु
			prपूर्णांकk(KERN_ERR "%s %s: unknown bus timing!\n",
				name, pci_name(dev));
			वापस -EIO;
		पूर्ण

		/* Select the DPLL घड़ी. */
		pci_ग_लिखो_config_byte(dev, 0x5b, 0x21);

		/*
		 * Adjust the DPLL based upon PCI घड़ी, enable it,
		 * and रुको क्रम stabilization...
		 */
		f_low = (pci_clk * 48) / dpll_clk;

		क्रम (adjust = 0; adjust < 8; adjust++) अणु
			अगर(hpt37x_calibrate_dpll(dev, f_low, f_low + delta))
				अवरोध;

			/*
			 * See अगर it'll settle at a fractionally dअगरferent घड़ी
			 */
			अगर (adjust & 1)
				f_low -= adjust >> 1;
			अन्यथा
				f_low += adjust >> 1;
		पूर्ण
		अगर (adjust == 8) अणु
			prपूर्णांकk(KERN_ERR "%s %s: DPLL did not stabilize!\n",
				name, pci_name(dev));
			वापस -EIO;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s %s: using %d MHz DPLL clock\n",
			name, pci_name(dev), dpll_clk);
	पूर्ण अन्यथा अणु
		/* Mark the fact that we're not using the DPLL. */
		dpll_clk = 0;

		prपूर्णांकk(KERN_INFO "%s %s: using %d MHz PCI clock\n",
			name, pci_name(dev), pci_clk);
	पूर्ण

	/* Store the घड़ी frequencies. */
	info->dpll_clk	= dpll_clk;
	info->pci_clk	= pci_clk;
	info->घड़ी	= घड़ी;

	अगर (chip_type >= HPT370) अणु
		u8  mcr1, mcr4;

		/*
		 * Reset the state engines.
		 * NOTE: Aव्योम accidentally enabling the disabled channels.
		 */
		pci_पढ़ो_config_byte (dev, 0x50, &mcr1);
		pci_पढ़ो_config_byte (dev, 0x54, &mcr4);
		pci_ग_लिखो_config_byte(dev, 0x50, (mcr1 | 0x32));
		pci_ग_लिखो_config_byte(dev, 0x54, (mcr4 | 0x32));
		udelay(100);
	पूर्ण

	/*
	 * On  HPT371N, अगर ATA घड़ी is 66 MHz we must set bit 2 in
	 * the MISC. रेजिस्टर to stretch the UltraDMA Tss timing.
	 * NOTE: This रेजिस्टर is only ग_लिखोable via I/O space.
	 */
	अगर (chip_type == HPT371N && घड़ी == ATA_CLOCK_66MHZ)
		outb(inb(io_base + 0x9c) | 0x04, io_base + 0x9c);

	hpt3xx_disable_fast_irq(dev, 0x50);
	hpt3xx_disable_fast_irq(dev, 0x54);

	वापस 0;
पूर्ण

अटल u8 hpt3xx_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev	*dev	= to_pci_dev(hwअगर->dev);
	काष्ठा hpt_info *info	= hpt3xx_get_info(hwअगर->dev);
	u8 chip_type		= info->chip_type;
	u8 scr1 = 0, ata66	= hwअगर->channel ? 0x01 : 0x02;

	/*
	 * The HPT37x uses the CBLID pins as outमाला_दो क्रम MA15/MA16
	 * address lines to access an बाह्यal EEPROM.  To पढ़ो valid
	 * cable detect state the pins must be enabled as inमाला_दो.
	 */
	अगर (chip_type == HPT374 && (PCI_FUNC(dev->devfn) & 1)) अणु
		/*
		 * HPT374 PCI function 1
		 * - set bit 15 of reg 0x52 to enable TCBLID as input
		 * - set bit 15 of reg 0x56 to enable FCBLID as input
		 */
		u8  mcr_addr = hwअगर->select_data + 2;
		u16 mcr;

		pci_पढ़ो_config_word(dev, mcr_addr, &mcr);
		pci_ग_लिखो_config_word(dev, mcr_addr, mcr | 0x8000);
		/* Debounce, then पढ़ो cable ID रेजिस्टर */
		udelay(10);
		pci_पढ़ो_config_byte(dev, 0x5a, &scr1);
		pci_ग_लिखो_config_word(dev, mcr_addr, mcr);
	पूर्ण अन्यथा अगर (chip_type >= HPT370) अणु
		/*
		 * HPT370/372 and 374 pcअगरn 0
		 * - clear bit 0 of reg 0x5b to enable P/SCBLID as inमाला_दो
		 */
		u8 scr2 = 0;

		pci_पढ़ो_config_byte(dev, 0x5b, &scr2);
		pci_ग_लिखो_config_byte(dev, 0x5b, scr2 & ~1);
		/* Debounce, then पढ़ो cable ID रेजिस्टर */
		udelay(10);
		pci_पढ़ो_config_byte(dev, 0x5a, &scr1);
		pci_ग_लिखो_config_byte(dev, 0x5b, scr2);
	पूर्ण अन्यथा
		pci_पढ़ो_config_byte(dev, 0x5a, &scr1);

	वापस (scr1 & ata66) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

अटल व्योम init_hwअगर_hpt366(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा hpt_info *info	= hpt3xx_get_info(hwअगर->dev);
	u8  chip_type		= info->chip_type;

	/* Cache the channel's MISC. control registers' offset */
	hwअगर->select_data	= hwअगर->channel ? 0x54 : 0x50;

	/*
	 * HPT3xxN chips have some complications:
	 *
	 * - on 33 MHz PCI we must घड़ी चयन
	 * - on 66 MHz PCI we must NOT use the PCI घड़ी
	 */
	अगर (chip_type >= HPT372N && info->dpll_clk && info->pci_clk < 66) अणु
		/*
		 * Clock is shared between the channels,
		 * so we'll have to serialize them... :-(
		 */
		hwअगर->host->host_flags |= IDE_HFLAG_SERIALIZE;
		hwअगर->rw_disk = &hpt3xxn_rw_disk;
	पूर्ण
पूर्ण

अटल पूर्णांक init_dma_hpt366(ide_hwअगर_t *hwअगर,
				     स्थिर काष्ठा ide_port_info *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ flags, base = ide_pci_dma_base(hwअगर, d);
	u8 dma_old, dma_new, masterdma = 0, slavedma = 0;

	अगर (base == 0)
		वापस -1;

	hwअगर->dma_base = base;

	अगर (ide_pci_check_simplex(hwअगर, d) < 0)
		वापस -1;

	अगर (ide_pci_set_master(dev, d->name) < 0)
		वापस -1;

	dma_old = inb(base + 2);

	local_irq_save(flags);

	dma_new = dma_old;
	pci_पढ़ो_config_byte(dev, hwअगर->channel ? 0x4b : 0x43, &masterdma);
	pci_पढ़ो_config_byte(dev, hwअगर->channel ? 0x4f : 0x47,  &slavedma);

	अगर (masterdma & 0x30)	dma_new |= 0x20;
	अगर ( slavedma & 0x30)	dma_new |= 0x40;
	अगर (dma_new != dma_old)
		outb(dma_new, base + 2);

	local_irq_restore(flags);

	prपूर्णांकk(KERN_INFO "    %s: BM-DMA at 0x%04lx-0x%04lx\n",
			 hwअगर->name, base, base + 7);

	hwअगर->extra_base = base + (hwअगर->channel ? 8 : 16);

	अगर (ide_allocate_dma_engine(hwअगर))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम hpt374_init(काष्ठा pci_dev *dev, काष्ठा pci_dev *dev2)
अणु
	अगर (dev2->irq != dev->irq) अणु
		/* FIXME: we need a core pci_set_पूर्णांकerrupt() */
		dev2->irq = dev->irq;
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: PCI config space interrupt "
			"fixed\n", pci_name(dev2));
	पूर्ण
पूर्ण

अटल व्योम hpt371_init(काष्ठा pci_dev *dev)
अणु
	u8 mcr1 = 0;

	/*
	 * HPT371 chips physically have only one channel, the secondary one,
	 * but the primary channel रेजिस्टरs करो exist!  Go figure...
	 * So,  we manually disable the non-existing channel here
	 * (अगर the BIOS hasn't करोne this alपढ़ोy).
	 */
	pci_पढ़ो_config_byte(dev, 0x50, &mcr1);
	अगर (mcr1 & 0x04)
		pci_ग_लिखो_config_byte(dev, 0x50, mcr1 & ~0x04);
पूर्ण

अटल पूर्णांक hpt36x_init(काष्ठा pci_dev *dev, काष्ठा pci_dev *dev2)
अणु
	u8 mcr1 = 0, pin1 = 0, pin2 = 0;

	/*
	 * Now we'll have to क्रमce both channels enabled अगर
	 * at least one of them has been enabled by BIOS...
	 */
	pci_पढ़ो_config_byte(dev, 0x50, &mcr1);
	अगर (mcr1 & 0x30)
		pci_ग_लिखो_config_byte(dev, 0x50, mcr1 | 0x30);

	pci_पढ़ो_config_byte(dev,  PCI_INTERRUPT_PIN, &pin1);
	pci_पढ़ो_config_byte(dev2, PCI_INTERRUPT_PIN, &pin2);

	अगर (pin1 != pin2 && dev->irq == dev2->irq) अणु
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: onboard version of chipset, "
			"pin1=%d pin2=%d\n", pci_name(dev), pin1, pin2);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा IDE_HFLAGS_HPT3XX \
	(IDE_HFLAG_NO_ATAPI_DMA | \
	 IDE_HFLAG_OFF_BOARD)

अटल स्थिर काष्ठा ide_port_ops hpt3xx_port_ops = अणु
	.set_pio_mode		= hpt3xx_set_pio_mode,
	.set_dma_mode		= hpt3xx_set_mode,
	.maskproc		= hpt3xx_maskproc,
	.mdma_filter		= hpt3xx_mdma_filter,
	.udma_filter		= hpt3xx_udma_filter,
	.cable_detect		= hpt3xx_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops hpt37x_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= hpt374_dma_end,
	.dma_test_irq		= hpt374_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops hpt370_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= hpt370_dma_start,
	.dma_end		= hpt370_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_clear		= hpt370_irq_समयout,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops hpt36x_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= ide_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= hpt366_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info hpt366_chipsets[] = अणु
	अणु	/* 0: HPT36x */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_hpt366,
		.init_hwअगर	= init_hwअगर_hpt366,
		.init_dma	= init_dma_hpt366,
		/*
		 * HPT36x chips have one channel per function and have
		 * both channel enable bits located dअगरferently and visible
		 * to both functions -- really stupid design decision... :-(
		 * Bit 4 is क्रम the primary channel, bit 5 क्रम the secondary.
		 */
		.enablebits	= अणुअणु0x50,0x10,0x10पूर्ण, अणु0x54,0x04,0x04पूर्णपूर्ण,
		.port_ops	= &hpt3xx_port_ops,
		.dma_ops	= &hpt36x_dma_ops,
		.host_flags	= IDE_HFLAGS_HPT3XX | IDE_HFLAG_SINGLE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
	पूर्ण,
	अणु	/* 1: HPT3xx */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_hpt366,
		.init_hwअगर	= init_hwअगर_hpt366,
		.init_dma	= init_dma_hpt366,
		.enablebits	= अणुअणु0x50,0x04,0x04पूर्ण, अणु0x54,0x04,0x04पूर्णपूर्ण,
		.port_ops	= &hpt3xx_port_ops,
		.dma_ops	= &hpt37x_dma_ops,
		.host_flags	= IDE_HFLAGS_HPT3XX,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
	पूर्ण
पूर्ण;

/**
 *	hpt366_init_one	-	called when an HPT366 is found
 *	@dev: the hpt366 device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */
अटल पूर्णांक hpt366_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा hpt_info *info = शून्य;
	काष्ठा hpt_info *dyn_info;
	काष्ठा pci_dev *dev2 = शून्य;
	काष्ठा ide_port_info d;
	u8 idx = id->driver_data;
	u8 rev = dev->revision;
	पूर्णांक ret;

	अगर ((idx == 0 || idx == 4) && (PCI_FUNC(dev->devfn) & 1))
		वापस -ENODEV;

	चयन (idx) अणु
	हाल 0:
		अगर (rev < 3)
			info = &hpt36x;
		अन्यथा अणु
			चयन (min_t(u8, rev, 6)) अणु
			हाल 3: info = &hpt370;  अवरोध;
			हाल 4: info = &hpt370a; अवरोध;
			हाल 5: info = &hpt372;  अवरोध;
			हाल 6: info = &hpt372n; अवरोध;
			पूर्ण
			idx++;
		पूर्ण
		अवरोध;
	हाल 1:
		info = (rev > 1) ? &hpt372n : &hpt372a;
		अवरोध;
	हाल 2:
		info = (rev > 1) ? &hpt302n : &hpt302;
		अवरोध;
	हाल 3:
		hpt371_init(dev);
		info = (rev > 1) ? &hpt371n : &hpt371;
		अवरोध;
	हाल 4:
		info = &hpt374;
		अवरोध;
	हाल 5:
		info = &hpt372n;
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO DRV_NAME ": %s chipset detected\n", info->chip_name);

	d = hpt366_chipsets[min_t(u8, idx, 1)];

	d.udma_mask = info->udma_mask;

	/* fixup ->dma_ops क्रम HPT370/HPT370A */
	अगर (info == &hpt370 || info == &hpt370a)
		d.dma_ops = &hpt370_dma_ops;

	अगर (info == &hpt36x || info == &hpt374)
		dev2 = pci_get_slot(dev->bus, dev->devfn + 1);

	dyn_info = kसुस्मृति(dev2 ? 2 : 1, माप(*dyn_info), GFP_KERNEL);
	अगर (dyn_info == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s %s: out of memory!\n",
			d.name, pci_name(dev));
		pci_dev_put(dev2);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Copy everything from a अटल "template" काष्ठाure
	 * to just allocated per-chip hpt_info काष्ठाure.
	 */
	स_नकल(dyn_info, info, माप(*dyn_info));

	अगर (dev2) अणु
		स_नकल(dyn_info + 1, info, माप(*dyn_info));

		अगर (info == &hpt374)
			hpt374_init(dev, dev2);
		अन्यथा अणु
			अगर (hpt36x_init(dev, dev2))
				d.host_flags &= ~IDE_HFLAG_NON_BOOTABLE;
		पूर्ण

		ret = ide_pci_init_two(dev, dev2, &d, dyn_info);
		अगर (ret < 0) अणु
			pci_dev_put(dev2);
			kमुक्त(dyn_info);
		पूर्ण
		वापस ret;
	पूर्ण

	ret = ide_pci_init_one(dev, &d, dyn_info);
	अगर (ret < 0)
		kमुक्त(dyn_info);

	वापस ret;
पूर्ण

अटल व्योम hpt366_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा ide_info *info = host->host_priv;
	काष्ठा pci_dev *dev2 = host->dev[1] ? to_pci_dev(host->dev[1]) : शून्य;

	ide_pci_हटाओ(dev);
	pci_dev_put(dev2);
	kमुक्त(info);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hpt366_pci_tbl[] = अणु
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT366),  0 पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372),  1 पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT302),  2 पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT371),  3 पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT374),  4 पूर्ण,
	अणु PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372N), 5 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, hpt366_pci_tbl);

अटल काष्ठा pci_driver hpt366_pci_driver = अणु
	.name		= "HPT366_IDE",
	.id_table	= hpt366_pci_tbl,
	.probe		= hpt366_init_one,
	.हटाओ		= hpt366_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init hpt366_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&hpt366_pci_driver);
पूर्ण

अटल व्योम __निकास hpt366_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hpt366_pci_driver);
पूर्ण

module_init(hpt366_ide_init);
module_निकास(hpt366_ide_निकास);

MODULE_AUTHOR("Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for Highpoint HPT366 IDE");
MODULE_LICENSE("GPL");
