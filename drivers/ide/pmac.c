<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम IDE पूर्णांकerfaces on PowerMacs.
 *
 * These IDE पूर्णांकerfaces are memory-mapped and have a DBDMA channel
 * क्रम करोing DMA.
 *
 *  Copyright (C) 1998-2003 Paul Mackerras & Ben. Herrenschmidt
 *  Copyright (C) 2007-2008 Bartlomiej Zolnierkiewicz
 *
 * Some code taken from drivers/ide/ide-dma.c:
 *
 *  Copyright (c) 1995-1998  Mark Lord
 *
 * TODO: - Use pre-calculated (kauai) timing tables all the समय and
 * get rid of the "rounded" tables used previously, so we have the
 * same table क्रमmat क्रम all controllers and can then just have one
 * big table
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/ide.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mediabay.h>

#घोषणा DRV_NAME "ide-pmac"

#अघोषित IDE_PMAC_DEBUG

#घोषणा DMA_WAIT_TIMEOUT	50

प्रकार काष्ठा pmac_ide_hwअगर अणु
	अचिन्हित दीर्घ			regbase;
	पूर्णांक				irq;
	पूर्णांक				kind;
	पूर्णांक				aapl_bus_id;
	अचिन्हित			broken_dma : 1;
	अचिन्हित			broken_dma_warn : 1;
	काष्ठा device_node*		node;
	काष्ठा macio_dev		*mdev;
	u32				timings[4];
	अस्थिर u32 __iomem *		*kauai_fcr;
	ide_hwअगर_t			*hwअगर;

	/* Those fields are duplicating what is in hwअगर. We currently
	 * can't use the hwअगर ones because of some assumptions that are
	 * beeing करोne by the generic code about the kind of dma controller
	 * and क्रमmat of the dma table. This will have to be fixed though.
	 */
	अस्थिर काष्ठा dbdma_regs __iomem *	dma_regs;
	काष्ठा dbdma_cmd*		dma_table_cpu;
पूर्ण pmac_ide_hwअगर_t;

क्रमागत अणु
	controller_ohare,	/* OHare based */
	controller_heathrow,	/* Heathrow/Paddington */
	controller_kl_ata3,	/* KeyLargo ATA-3 */
	controller_kl_ata4,	/* KeyLargo ATA-4 */
	controller_un_ata6,	/* UniNorth2 ATA-6 */
	controller_k2_ata6,	/* K2 ATA-6 */
	controller_sh_ata6,	/* Shasta ATA-6 */
पूर्ण;

अटल स्थिर अक्षर* model_name[] = अणु
	"OHare ATA",		/* OHare based */
	"Heathrow ATA",		/* Heathrow/Paddington */
	"KeyLargo ATA-3",	/* KeyLargo ATA-3 (MDMA only) */
	"KeyLargo ATA-4",	/* KeyLargo ATA-4 (UDMA/66) */
	"UniNorth ATA-6",	/* UniNorth2 ATA-6 (UDMA/100) */
	"K2 ATA-6",		/* K2 ATA-6 (UDMA/100) */
	"Shasta ATA-6",		/* Shasta ATA-6 (UDMA/133) */
पूर्ण;

/*
 * Extra रेजिस्टरs, both 32-bit little-endian
 */
#घोषणा IDE_TIMING_CONFIG	0x200
#घोषणा IDE_INTERRUPT		0x300

/* Kauai (U2) ATA has dअगरferent रेजिस्टर setup */
#घोषणा IDE_KAUAI_PIO_CONFIG	0x200
#घोषणा IDE_KAUAI_ULTRA_CONFIG	0x210
#घोषणा IDE_KAUAI_POLL_CONFIG	0x220

/*
 * Timing configuration रेजिस्टर definitions
 */

/* Number of IDE_SYSCLK_NS ticks, argument is in nanoseconds */
#घोषणा SYSCLK_TICKS(t)		(((t) + IDE_SYSCLK_NS - 1) / IDE_SYSCLK_NS)
#घोषणा SYSCLK_TICKS_66(t)	(((t) + IDE_SYSCLK_66_NS - 1) / IDE_SYSCLK_66_NS)
#घोषणा IDE_SYSCLK_NS		30	/* 33Mhz cell */
#घोषणा IDE_SYSCLK_66_NS	15	/* 66Mhz cell */

/* 133Mhz cell, found in shasta.
 * See comments about 100 Mhz Uninorth 2...
 * Note that PIO_MASK and MDMA_MASK seem to overlap
 */
#घोषणा TR_133_PIOREG_PIO_MASK		0xff000fff
#घोषणा TR_133_PIOREG_MDMA_MASK		0x00fff800
#घोषणा TR_133_UDMAREG_UDMA_MASK	0x0003ffff
#घोषणा TR_133_UDMAREG_UDMA_EN		0x00000001

/* 100Mhz cell, found in Uninorth 2. I करोn't have much infos about
 * this one yet, it appears as a pci device (106b/0033) on uninorth
 * पूर्णांकernal PCI bus and it's घड़ी is controlled like gem or fw. It
 * appears to be an evolution of keylargo ATA4 with a timing रेजिस्टर
 * extended to 2 32bits रेजिस्टरs and a similar DBDMA channel. Other
 * रेजिस्टरs seem to exist but I can't tell much about them.
 * 
 * So far, I'm using pre-calculated tables क्रम this extracted from
 * the values used by the MacOS X driver.
 * 
 * The "PIO" रेजिस्टर controls PIO and MDMA timings, the "ULTRA"
 * रेजिस्टर controls the UDMA timings. At least, it seems bit 0
 * of this one enables UDMA vs. MDMA, and bits 4..7 are the
 * cycle समय in units of 10ns. Bits 8..15 are used by I करोn't
 * know their meaning yet
 */
#घोषणा TR_100_PIOREG_PIO_MASK		0xff000fff
#घोषणा TR_100_PIOREG_MDMA_MASK		0x00fff000
#घोषणा TR_100_UDMAREG_UDMA_MASK	0x0000ffff
#घोषणा TR_100_UDMAREG_UDMA_EN		0x00000001


/* 66Mhz cell, found in KeyLargo. Can करो ultra mode 0 to 2 on
 * 40 connector cable and to 4 on 80 connector one.
 * Clock unit is 15ns (66Mhz)
 * 
 * 3 Values can be programmed:
 *  - Write data setup, which appears to match the cycle समय. They
 *    also call it DIOW setup.
 *  - Ready to छोड़ो समय (from spec)
 *  - Address setup. That one is weird. I करोn't see where exactly
 *    it fits in UDMA cycles, I got it's name from an obscure piece
 *    of commented out code in Darwin. They leave it to 0, we करो as
 *    well, despite a comment that would lead to think it has a
 *    min value of 45ns.
 * Apple also add 60ns to the ग_लिखो data setup (or cycle समय ?) on
 * पढ़ोs.
 */
#घोषणा TR_66_UDMA_MASK			0xfff00000
#घोषणा TR_66_UDMA_EN			0x00100000 /* Enable Ultra mode क्रम DMA */
#घोषणा TR_66_UDMA_ADDRSETUP_MASK	0xe0000000 /* Address setup */
#घोषणा TR_66_UDMA_ADDRSETUP_SHIFT	29
#घोषणा TR_66_UDMA_RDY2PAUS_MASK	0x1e000000 /* Ready 2 छोड़ो समय */
#घोषणा TR_66_UDMA_RDY2PAUS_SHIFT	25
#घोषणा TR_66_UDMA_WRDATASETUP_MASK	0x01e00000 /* Write data setup समय */
#घोषणा TR_66_UDMA_WRDATASETUP_SHIFT	21
#घोषणा TR_66_MDMA_MASK			0x000ffc00
#घोषणा TR_66_MDMA_RECOVERY_MASK	0x000f8000
#घोषणा TR_66_MDMA_RECOVERY_SHIFT	15
#घोषणा TR_66_MDMA_ACCESS_MASK		0x00007c00
#घोषणा TR_66_MDMA_ACCESS_SHIFT		10
#घोषणा TR_66_PIO_MASK			0x000003ff
#घोषणा TR_66_PIO_RECOVERY_MASK		0x000003e0
#घोषणा TR_66_PIO_RECOVERY_SHIFT	5
#घोषणा TR_66_PIO_ACCESS_MASK		0x0000001f
#घोषणा TR_66_PIO_ACCESS_SHIFT		0

/* 33Mhz cell, found in OHare, Heathrow (& Paddington) and KeyLargo
 * Can करो pio & mdma modes, घड़ी unit is 30ns (33Mhz)
 * 
 * The access समय and recovery समय can be programmed. Some older
 * Darwin code base limit OHare to 150ns cycle समय. I decided to करो
 * the same here क्रमe safety against broken old hardware ;)
 * The HalfTick bit, when set, adds half a घड़ी (15ns) to the access
 * समय and हटाओs one from recovery. It's not supported on KeyLargo
 * implementation afaik. The E bit appears to be set क्रम PIO mode 0 and
 * is used to reach दीर्घ timings used in this mode.
 */
#घोषणा TR_33_MDMA_MASK			0x003ff800
#घोषणा TR_33_MDMA_RECOVERY_MASK	0x001f0000
#घोषणा TR_33_MDMA_RECOVERY_SHIFT	16
#घोषणा TR_33_MDMA_ACCESS_MASK		0x0000f800
#घोषणा TR_33_MDMA_ACCESS_SHIFT		11
#घोषणा TR_33_MDMA_HALFTICK		0x00200000
#घोषणा TR_33_PIO_MASK			0x000007ff
#घोषणा TR_33_PIO_E			0x00000400
#घोषणा TR_33_PIO_RECOVERY_MASK		0x000003e0
#घोषणा TR_33_PIO_RECOVERY_SHIFT	5
#घोषणा TR_33_PIO_ACCESS_MASK		0x0000001f
#घोषणा TR_33_PIO_ACCESS_SHIFT		0

/*
 * Interrupt रेजिस्टर definitions
 */
#घोषणा IDE_INTR_DMA			0x80000000
#घोषणा IDE_INTR_DEVICE			0x40000000

/*
 * FCR Register on Kauai. Not sure what bit 0x4 is  ...
 */
#घोषणा KAUAI_FCR_UATA_MAGIC		0x00000004
#घोषणा KAUAI_FCR_UATA_RESET_N		0x00000002
#घोषणा KAUAI_FCR_UATA_ENABLE		0x00000001

/* Rounded Multiword DMA timings
 * 
 * I gave up finding a generic क्रमmula क्रम all controller
 * types and instead, built tables based on timing values
 * used by Apple in Darwin's implementation.
 */
काष्ठा mdma_timings_t अणु
	पूर्णांक	accessTime;
	पूर्णांक	recoveryTime;
	पूर्णांक	cycleTime;
पूर्ण;

काष्ठा mdma_timings_t mdma_timings_33[] =
अणु
    अणु 240, 240, 480 पूर्ण,
    अणु 180, 180, 360 पूर्ण,
    अणु 135, 135, 270 पूर्ण,
    अणु 120, 120, 240 पूर्ण,
    अणु 105, 105, 210 पूर्ण,
    अणु  90,  90, 180 पूर्ण,
    अणु  75,  75, 150 पूर्ण,
    अणु  75,  45, 120 पूर्ण,
    अणु   0,   0,   0 पूर्ण
पूर्ण;

काष्ठा mdma_timings_t mdma_timings_33k[] =
अणु
    अणु 240, 240, 480 पूर्ण,
    अणु 180, 180, 360 पूर्ण,
    अणु 150, 150, 300 पूर्ण,
    अणु 120, 120, 240 पूर्ण,
    अणु  90, 120, 210 पूर्ण,
    अणु  90,  90, 180 पूर्ण,
    अणु  90,  60, 150 पूर्ण,
    अणु  90,  30, 120 पूर्ण,
    अणु   0,   0,   0 पूर्ण
पूर्ण;

काष्ठा mdma_timings_t mdma_timings_66[] =
अणु
    अणु 240, 240, 480 पूर्ण,
    अणु 180, 180, 360 पूर्ण,
    अणु 135, 135, 270 पूर्ण,
    अणु 120, 120, 240 पूर्ण,
    अणु 105, 105, 210 पूर्ण,
    अणु  90,  90, 180 पूर्ण,
    अणु  90,  75, 165 पूर्ण,
    अणु  75,  45, 120 पूर्ण,
    अणु   0,   0,   0 पूर्ण
पूर्ण;

/* KeyLargo ATA-4 Ultra DMA timings (rounded) */
काष्ठा अणु
	पूर्णांक	addrSetup; /* ??? */
	पूर्णांक	rdy2छोड़ो;
	पूर्णांक	wrDataSetup;
पूर्ण kl66_udma_timings[] =
अणु
    अणु   0, 180,  120 पूर्ण,	/* Mode 0 */
    अणु   0, 150,  90 पूर्ण,	/*      1 */
    अणु   0, 120,  60 पूर्ण,	/*      2 */
    अणु   0, 90,   45 पूर्ण,	/*      3 */
    अणु   0, 90,   30 पूर्ण	/*      4 */
पूर्ण;

/* UniNorth 2 ATA/100 timings */
काष्ठा kauai_timing अणु
	पूर्णांक	cycle_समय;
	u32	timing_reg;
पूर्ण;

अटल काष्ठा kauai_timing	kauai_pio_timings[] =
अणु
	अणु 930	, 0x08000fff पूर्ण,
	अणु 600	, 0x08000a92 पूर्ण,
	अणु 383	, 0x0800060f पूर्ण,
	अणु 360	, 0x08000492 पूर्ण,
	अणु 330	, 0x0800048f पूर्ण,
	अणु 300	, 0x080003cf पूर्ण,
	अणु 270	, 0x080003cc पूर्ण,
	अणु 240	, 0x0800038b पूर्ण,
	अणु 239	, 0x0800030c पूर्ण,
	अणु 180	, 0x05000249 पूर्ण,
	अणु 120	, 0x04000148 पूर्ण,
	अणु 0	, 0 पूर्ण,
पूर्ण;

अटल काष्ठा kauai_timing	kauai_mdma_timings[] =
अणु
	अणु 1260	, 0x00fff000 पूर्ण,
	अणु 480	, 0x00618000 पूर्ण,
	अणु 360	, 0x00492000 पूर्ण,
	अणु 270	, 0x0038e000 पूर्ण,
	अणु 240	, 0x0030c000 पूर्ण,
	अणु 210	, 0x002cb000 पूर्ण,
	अणु 180	, 0x00249000 पूर्ण,
	अणु 150	, 0x00209000 पूर्ण,
	अणु 120	, 0x00148000 पूर्ण,
	अणु 0	, 0 पूर्ण,
पूर्ण;

अटल काष्ठा kauai_timing	kauai_udma_timings[] =
अणु
	अणु 120	, 0x000070c0 पूर्ण,
	अणु 90	, 0x00005d80 पूर्ण,
	अणु 60	, 0x00004a60 पूर्ण,
	अणु 45	, 0x00003a50 पूर्ण,
	अणु 30	, 0x00002a30 पूर्ण,
	अणु 20	, 0x00002921 पूर्ण,
	अणु 0	, 0 पूर्ण,
पूर्ण;

अटल काष्ठा kauai_timing	shasta_pio_timings[] =
अणु
	अणु 930	, 0x08000fff पूर्ण,
	अणु 600	, 0x0A000c97 पूर्ण,
	अणु 383	, 0x07000712 पूर्ण,
	अणु 360	, 0x040003cd पूर्ण,
	अणु 330	, 0x040003cd पूर्ण,
	अणु 300	, 0x040003cd पूर्ण,
	अणु 270	, 0x040003cd पूर्ण,
	अणु 240	, 0x040003cd पूर्ण,
	अणु 239	, 0x040003cd पूर्ण,
	अणु 180	, 0x0400028b पूर्ण,
	अणु 120	, 0x0400010a पूर्ण,
	अणु 0	, 0 पूर्ण,
पूर्ण;

अटल काष्ठा kauai_timing	shasta_mdma_timings[] =
अणु
	अणु 1260	, 0x00fff000 पूर्ण,
	अणु 480	, 0x00820800 पूर्ण,
	अणु 360	, 0x00820800 पूर्ण,
	अणु 270	, 0x00820800 पूर्ण,
	अणु 240	, 0x00820800 पूर्ण,
	अणु 210	, 0x00820800 पूर्ण,
	अणु 180	, 0x00820800 पूर्ण,
	अणु 150	, 0x0028b000 पूर्ण,
	अणु 120	, 0x001ca000 पूर्ण,
	अणु 0	, 0 पूर्ण,
पूर्ण;

अटल काष्ठा kauai_timing	shasta_udma133_timings[] =
अणु
	अणु 120   , 0x00035901, पूर्ण,
	अणु 90    , 0x000348b1, पूर्ण,
	अणु 60    , 0x00033881, पूर्ण,
	अणु 45    , 0x00033861, पूर्ण,
	अणु 30    , 0x00033841, पूर्ण,
	अणु 20    , 0x00033031, पूर्ण,
	अणु 15    , 0x00033021, पूर्ण,
	अणु 0	, 0 पूर्ण,
पूर्ण;


अटल अंतरभूत u32
kauai_lookup_timing(काष्ठा kauai_timing* table, पूर्णांक cycle_समय)
अणु
	पूर्णांक i;
	
	क्रम (i=0; table[i].cycle_समय; i++)
		अगर (cycle_समय > table[i+1].cycle_समय)
			वापस table[i].timing_reg;
	BUG();
	वापस 0;
पूर्ण

/* allow up to 256 DBDMA commands per xfer */
#घोषणा MAX_DCMDS		256

/* 
 * Wait 1s क्रम disk to answer on IDE bus after a hard reset
 * of the device (via GPIO/FCR).
 * 
 * Some devices seem to "pollute" the bus even after dropping
 * the BSY bit (typically some combo drives slave on the UDMA
 * bus) after a hard reset. Since we hard reset all drives on
 * KeyLargo ATA66, we have to keep that delay around. I may end
 * up not hard resetting anymore on these and keep the delay only
 * क्रम older पूर्णांकerfaces instead (we have to reset when coming
 * from MacOS...) --BenH. 
 */
#घोषणा IDE_WAKEUP_DELAY	(1*HZ)

अटल पूर्णांक pmac_ide_init_dma(ide_hwअगर_t *, स्थिर काष्ठा ide_port_info *);

#घोषणा PMAC_IDE_REG(x) \
	((व्योम __iomem *)((drive)->hwअगर->io_ports.data_addr + (x)))

/*
 * Apply the timings of the proper unit (master/slave) to the shared
 * timing रेजिस्टर when selecting that unit. This version is क्रम
 * ASICs with a single timing रेजिस्टर
 */
अटल व्योम pmac_ide_apply_timings(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);

	अगर (drive->dn & 1)
		ग_लिखोl(pmअगर->timings[1], PMAC_IDE_REG(IDE_TIMING_CONFIG));
	अन्यथा
		ग_लिखोl(pmअगर->timings[0], PMAC_IDE_REG(IDE_TIMING_CONFIG));
	(व्योम)पढ़ोl(PMAC_IDE_REG(IDE_TIMING_CONFIG));
पूर्ण

/*
 * Apply the timings of the proper unit (master/slave) to the shared
 * timing रेजिस्टर when selecting that unit. This version is क्रम
 * ASICs with a dual timing रेजिस्टर (Kauai)
 */
अटल व्योम pmac_ide_kauai_apply_timings(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);

	अगर (drive->dn & 1) अणु
		ग_लिखोl(pmअगर->timings[1], PMAC_IDE_REG(IDE_KAUAI_PIO_CONFIG));
		ग_लिखोl(pmअगर->timings[3], PMAC_IDE_REG(IDE_KAUAI_ULTRA_CONFIG));
	पूर्ण अन्यथा अणु
		ग_लिखोl(pmअगर->timings[0], PMAC_IDE_REG(IDE_KAUAI_PIO_CONFIG));
		ग_लिखोl(pmअगर->timings[2], PMAC_IDE_REG(IDE_KAUAI_ULTRA_CONFIG));
	पूर्ण
	(व्योम)पढ़ोl(PMAC_IDE_REG(IDE_KAUAI_PIO_CONFIG));
पूर्ण

/*
 * Force an update of controller timing values क्रम a given drive
 */
अटल व्योम
pmac_ide_करो_update_timings(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);

	अगर (pmअगर->kind == controller_sh_ata6 ||
	    pmअगर->kind == controller_un_ata6 ||
	    pmअगर->kind == controller_k2_ata6)
		pmac_ide_kauai_apply_timings(drive);
	अन्यथा
		pmac_ide_apply_timings(drive);
पूर्ण

अटल व्योम pmac_dev_select(ide_drive_t *drive)
अणु
	pmac_ide_apply_timings(drive);

	ग_लिखोb(drive->select | ATA_DEVICE_OBS,
	       (व्योम __iomem *)drive->hwअगर->io_ports.device_addr);
पूर्ण

अटल व्योम pmac_kauai_dev_select(ide_drive_t *drive)
अणु
	pmac_ide_kauai_apply_timings(drive);

	ग_लिखोb(drive->select | ATA_DEVICE_OBS,
	       (व्योम __iomem *)drive->hwअगर->io_ports.device_addr);
पूर्ण

अटल व्योम pmac_exec_command(ide_hwअगर_t *hwअगर, u8 cmd)
अणु
	ग_लिखोb(cmd, (व्योम __iomem *)hwअगर->io_ports.command_addr);
	(व्योम)पढ़ोl((व्योम __iomem *)(hwअगर->io_ports.data_addr
				     + IDE_TIMING_CONFIG));
पूर्ण

अटल व्योम pmac_ग_लिखो_devctl(ide_hwअगर_t *hwअगर, u8 ctl)
अणु
	ग_लिखोb(ctl, (व्योम __iomem *)hwअगर->io_ports.ctl_addr);
	(व्योम)पढ़ोl((व्योम __iomem *)(hwअगर->io_ports.data_addr
				     + IDE_TIMING_CONFIG));
पूर्ण

/*
 * Old tuning functions (called on hdparm -p), sets up drive PIO timings
 */
अटल व्योम pmac_ide_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	काष्ठा ide_timing *tim = ide_timing_find_mode(XFER_PIO_0 + pio);
	u32 *timings, t;
	अचिन्हित accessTicks, recTicks;
	अचिन्हित accessTime, recTime;
	अचिन्हित पूर्णांक cycle_समय;

	/* which drive is it ? */
	timings = &pmअगर->timings[drive->dn & 1];
	t = *timings;

	cycle_समय = ide_pio_cycle_समय(drive, pio);

	चयन (pmअगर->kind) अणु
	हाल controller_sh_ata6: अणु
		/* 133Mhz cell */
		u32 tr = kauai_lookup_timing(shasta_pio_timings, cycle_समय);
		t = (t & ~TR_133_PIOREG_PIO_MASK) | tr;
		अवरोध;
		पूर्ण
	हाल controller_un_ata6:
	हाल controller_k2_ata6: अणु
		/* 100Mhz cell */
		u32 tr = kauai_lookup_timing(kauai_pio_timings, cycle_समय);
		t = (t & ~TR_100_PIOREG_PIO_MASK) | tr;
		अवरोध;
		पूर्ण
	हाल controller_kl_ata4:
		/* 66Mhz cell */
		recTime = cycle_समय - tim->active - tim->setup;
		recTime = max(recTime, 150U);
		accessTime = tim->active;
		accessTime = max(accessTime, 150U);
		accessTicks = SYSCLK_TICKS_66(accessTime);
		accessTicks = min(accessTicks, 0x1fU);
		recTicks = SYSCLK_TICKS_66(recTime);
		recTicks = min(recTicks, 0x1fU);
		t = (t & ~TR_66_PIO_MASK) |
			(accessTicks << TR_66_PIO_ACCESS_SHIFT) |
			(recTicks << TR_66_PIO_RECOVERY_SHIFT);
		अवरोध;
	शेष: अणु
		/* 33Mhz cell */
		पूर्णांक ebit = 0;
		recTime = cycle_समय - tim->active - tim->setup;
		recTime = max(recTime, 150U);
		accessTime = tim->active;
		accessTime = max(accessTime, 150U);
		accessTicks = SYSCLK_TICKS(accessTime);
		accessTicks = min(accessTicks, 0x1fU);
		accessTicks = max(accessTicks, 4U);
		recTicks = SYSCLK_TICKS(recTime);
		recTicks = min(recTicks, 0x1fU);
		recTicks = max(recTicks, 5U) - 4;
		अगर (recTicks > 9) अणु
			recTicks--; /* guess, but it's only क्रम PIO0, so... */
			ebit = 1;
		पूर्ण
		t = (t & ~TR_33_PIO_MASK) |
				(accessTicks << TR_33_PIO_ACCESS_SHIFT) |
				(recTicks << TR_33_PIO_RECOVERY_SHIFT);
		अगर (ebit)
			t |= TR_33_PIO_E;
		अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित IDE_PMAC_DEBUG
	prपूर्णांकk(KERN_ERR "%s: Set PIO timing for mode %d, reg: 0x%08x\n",
		drive->name, pio,  *timings);
#पूर्ण_अगर	

	*timings = t;
	pmac_ide_करो_update_timings(drive);
पूर्ण

/*
 * Calculate KeyLargo ATA/66 UDMA timings
 */
अटल पूर्णांक
set_timings_udma_ata4(u32 *timings, u8 speed)
अणु
	अचिन्हित rdyToPauseTicks, wrDataSetupTicks, addrTicks;

	अगर (speed > XFER_UDMA_4)
		वापस 1;

	rdyToPauseTicks = SYSCLK_TICKS_66(kl66_udma_timings[speed & 0xf].rdy2छोड़ो);
	wrDataSetupTicks = SYSCLK_TICKS_66(kl66_udma_timings[speed & 0xf].wrDataSetup);
	addrTicks = SYSCLK_TICKS_66(kl66_udma_timings[speed & 0xf].addrSetup);

	*timings = ((*timings) & ~(TR_66_UDMA_MASK | TR_66_MDMA_MASK)) |
			(wrDataSetupTicks << TR_66_UDMA_WRDATASETUP_SHIFT) | 
			(rdyToPauseTicks << TR_66_UDMA_RDY2PAUS_SHIFT) |
			(addrTicks <<TR_66_UDMA_ADDRSETUP_SHIFT) |
			TR_66_UDMA_EN;
#अगर_घोषित IDE_PMAC_DEBUG
	prपूर्णांकk(KERN_ERR "ide_pmac: Set UDMA timing for mode %d, reg: 0x%08x\n",
		speed & 0xf,  *timings);
#पूर्ण_अगर	

	वापस 0;
पूर्ण

/*
 * Calculate Kauai ATA/100 UDMA timings
 */
अटल पूर्णांक
set_timings_udma_ata6(u32 *pio_timings, u32 *ultra_timings, u8 speed)
अणु
	काष्ठा ide_timing *t = ide_timing_find_mode(speed);
	u32 tr;

	अगर (speed > XFER_UDMA_5 || t == शून्य)
		वापस 1;
	tr = kauai_lookup_timing(kauai_udma_timings, (पूर्णांक)t->udma);
	*ultra_timings = ((*ultra_timings) & ~TR_100_UDMAREG_UDMA_MASK) | tr;
	*ultra_timings = (*ultra_timings) | TR_100_UDMAREG_UDMA_EN;

	वापस 0;
पूर्ण

/*
 * Calculate Shasta ATA/133 UDMA timings
 */
अटल पूर्णांक
set_timings_udma_shasta(u32 *pio_timings, u32 *ultra_timings, u8 speed)
अणु
	काष्ठा ide_timing *t = ide_timing_find_mode(speed);
	u32 tr;

	अगर (speed > XFER_UDMA_6 || t == शून्य)
		वापस 1;
	tr = kauai_lookup_timing(shasta_udma133_timings, (पूर्णांक)t->udma);
	*ultra_timings = ((*ultra_timings) & ~TR_133_UDMAREG_UDMA_MASK) | tr;
	*ultra_timings = (*ultra_timings) | TR_133_UDMAREG_UDMA_EN;

	वापस 0;
पूर्ण

/*
 * Calculate MDMA timings क्रम all cells
 */
अटल व्योम
set_timings_mdma(ide_drive_t *drive, पूर्णांक पूर्णांकf_type, u32 *timings, u32 *timings2,
		 	u8 speed)
अणु
	u16 *id = drive->id;
	पूर्णांक cycleTime, accessTime = 0, recTime = 0;
	अचिन्हित accessTicks, recTicks;
	काष्ठा mdma_timings_t* पंचांग = शून्य;
	पूर्णांक i;

	/* Get शेष cycle समय क्रम mode */
	चयन(speed & 0xf) अणु
		हाल 0: cycleTime = 480; अवरोध;
		हाल 1: cycleTime = 150; अवरोध;
		हाल 2: cycleTime = 120; अवरोध;
		शेष:
			BUG();
			अवरोध;
	पूर्ण

	/* Check अगर drive provides explicit DMA cycle समय */
	अगर ((id[ATA_ID_FIELD_VALID] & 2) && id[ATA_ID_EIDE_DMA_TIME])
		cycleTime = max_t(पूर्णांक, id[ATA_ID_EIDE_DMA_TIME], cycleTime);

	/* OHare limits according to some old Apple sources */	
	अगर ((पूर्णांकf_type == controller_ohare) && (cycleTime < 150))
		cycleTime = 150;
	/* Get the proper timing array क्रम this controller */
	चयन(पूर्णांकf_type) अणु
	        हाल controller_sh_ata6:
		हाल controller_un_ata6:
		हाल controller_k2_ata6:
			अवरोध;
		हाल controller_kl_ata4:
			पंचांग = mdma_timings_66;
			अवरोध;
		हाल controller_kl_ata3:
			पंचांग = mdma_timings_33k;
			अवरोध;
		शेष:
			पंचांग = mdma_timings_33;
			अवरोध;
	पूर्ण
	अगर (पंचांग != शून्य) अणु
		/* Lookup matching access & recovery बार */
		i = -1;
		क्रम (;;) अणु
			अगर (पंचांग[i+1].cycleTime < cycleTime)
				अवरोध;
			i++;
		पूर्ण
		cycleTime = पंचांग[i].cycleTime;
		accessTime = पंचांग[i].accessTime;
		recTime = पंचांग[i].recoveryTime;

#अगर_घोषित IDE_PMAC_DEBUG
		prपूर्णांकk(KERN_ERR "%s: MDMA, cycleTime: %d, accessTime: %d, recTime: %d\n",
			drive->name, cycleTime, accessTime, recTime);
#पूर्ण_अगर
	पूर्ण
	चयन(पूर्णांकf_type) अणु
	हाल controller_sh_ata6: अणु
		/* 133Mhz cell */
		u32 tr = kauai_lookup_timing(shasta_mdma_timings, cycleTime);
		*timings = ((*timings) & ~TR_133_PIOREG_MDMA_MASK) | tr;
		*timings2 = (*timings2) & ~TR_133_UDMAREG_UDMA_EN;
		पूर्ण
		अवरोध;
	हाल controller_un_ata6:
	हाल controller_k2_ata6: अणु
		/* 100Mhz cell */
		u32 tr = kauai_lookup_timing(kauai_mdma_timings, cycleTime);
		*timings = ((*timings) & ~TR_100_PIOREG_MDMA_MASK) | tr;
		*timings2 = (*timings2) & ~TR_100_UDMAREG_UDMA_EN;
		पूर्ण
		अवरोध;
	हाल controller_kl_ata4:
		/* 66Mhz cell */
		accessTicks = SYSCLK_TICKS_66(accessTime);
		accessTicks = min(accessTicks, 0x1fU);
		accessTicks = max(accessTicks, 0x1U);
		recTicks = SYSCLK_TICKS_66(recTime);
		recTicks = min(recTicks, 0x1fU);
		recTicks = max(recTicks, 0x3U);
		/* Clear out mdma bits and disable udma */
		*timings = ((*timings) & ~(TR_66_MDMA_MASK | TR_66_UDMA_MASK)) |
			(accessTicks << TR_66_MDMA_ACCESS_SHIFT) |
			(recTicks << TR_66_MDMA_RECOVERY_SHIFT);
		अवरोध;
	हाल controller_kl_ata3:
		/* 33Mhz cell on KeyLargo */
		accessTicks = SYSCLK_TICKS(accessTime);
		accessTicks = max(accessTicks, 1U);
		accessTicks = min(accessTicks, 0x1fU);
		accessTime = accessTicks * IDE_SYSCLK_NS;
		recTicks = SYSCLK_TICKS(recTime);
		recTicks = max(recTicks, 1U);
		recTicks = min(recTicks, 0x1fU);
		*timings = ((*timings) & ~TR_33_MDMA_MASK) |
				(accessTicks << TR_33_MDMA_ACCESS_SHIFT) |
				(recTicks << TR_33_MDMA_RECOVERY_SHIFT);
		अवरोध;
	शेष: अणु
		/* 33Mhz cell on others */
		पूर्णांक halfTick = 0;
		पूर्णांक origAccessTime = accessTime;
		पूर्णांक origRecTime = recTime;
		
		accessTicks = SYSCLK_TICKS(accessTime);
		accessTicks = max(accessTicks, 1U);
		accessTicks = min(accessTicks, 0x1fU);
		accessTime = accessTicks * IDE_SYSCLK_NS;
		recTicks = SYSCLK_TICKS(recTime);
		recTicks = max(recTicks, 2U) - 1;
		recTicks = min(recTicks, 0x1fU);
		recTime = (recTicks + 1) * IDE_SYSCLK_NS;
		अगर ((accessTicks > 1) &&
		    ((accessTime - IDE_SYSCLK_NS/2) >= origAccessTime) &&
		    ((recTime - IDE_SYSCLK_NS/2) >= origRecTime)) अणु
            		halfTick = 1;
			accessTicks--;
		पूर्ण
		*timings = ((*timings) & ~TR_33_MDMA_MASK) |
				(accessTicks << TR_33_MDMA_ACCESS_SHIFT) |
				(recTicks << TR_33_MDMA_RECOVERY_SHIFT);
		अगर (halfTick)
			*timings |= TR_33_MDMA_HALFTICK;
		पूर्ण
	पूर्ण
#अगर_घोषित IDE_PMAC_DEBUG
	prपूर्णांकk(KERN_ERR "%s: Set MDMA timing for mode %d, reg: 0x%08x\n",
		drive->name, speed & 0xf,  *timings);
#पूर्ण_अगर	
पूर्ण

अटल व्योम pmac_ide_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	पूर्णांक ret = 0;
	u32 *timings, *timings2, tl[2];
	u8 unit = drive->dn & 1;
	स्थिर u8 speed = drive->dma_mode;

	timings = &pmअगर->timings[unit];
	timings2 = &pmअगर->timings[unit+2];

	/* Copy timings to local image */
	tl[0] = *timings;
	tl[1] = *timings2;

	अगर (speed >= XFER_UDMA_0) अणु
		अगर (pmअगर->kind == controller_kl_ata4)
			ret = set_timings_udma_ata4(&tl[0], speed);
		अन्यथा अगर (pmअगर->kind == controller_un_ata6
			 || pmअगर->kind == controller_k2_ata6)
			ret = set_timings_udma_ata6(&tl[0], &tl[1], speed);
		अन्यथा अगर (pmअगर->kind == controller_sh_ata6)
			ret = set_timings_udma_shasta(&tl[0], &tl[1], speed);
		अन्यथा
			ret = -1;
	पूर्ण अन्यथा
		set_timings_mdma(drive, pmअगर->kind, &tl[0], &tl[1], speed);

	अगर (ret)
		वापस;

	/* Apply timings to controller */
	*timings = tl[0];
	*timings2 = tl[1];

	pmac_ide_करो_update_timings(drive);	
पूर्ण

/*
 * Blast some well known "safe" values to the timing रेजिस्टरs at init or
 * wakeup from sleep समय, beक्रमe we करो real calculation
 */
अटल व्योम
sanitize_timings(pmac_ide_hwअगर_t *pmअगर)
अणु
	अचिन्हित पूर्णांक value, value2 = 0;
	
	चयन(pmअगर->kind) अणु
		हाल controller_sh_ata6:
			value = 0x0a820c97;
			value2 = 0x00033031;
			अवरोध;
		हाल controller_un_ata6:
		हाल controller_k2_ata6:
			value = 0x08618a92;
			value2 = 0x00002921;
			अवरोध;
		हाल controller_kl_ata4:
			value = 0x0008438c;
			अवरोध;
		हाल controller_kl_ata3:
			value = 0x00084526;
			अवरोध;
		हाल controller_heathrow:
		हाल controller_ohare:
		शेष:
			value = 0x00074526;
			अवरोध;
	पूर्ण
	pmअगर->timings[0] = pmअगर->timings[1] = value;
	pmअगर->timings[2] = pmअगर->timings[3] = value2;
पूर्ण

अटल पूर्णांक on_media_bay(pmac_ide_hwअगर_t *pmअगर)
अणु
	वापस pmअगर->mdev && pmअगर->mdev->media_bay != शून्य;
पूर्ण

/* Suspend call back, should be called after the child devices
 * have actually been suspended
 */
अटल पूर्णांक pmac_ide_करो_suspend(pmac_ide_hwअगर_t *pmअगर)
अणु
	/* We clear the timings */
	pmअगर->timings[0] = 0;
	pmअगर->timings[1] = 0;
	
	disable_irq(pmअगर->irq);

	/* The media bay will handle itself just fine */
	अगर (on_media_bay(pmअगर))
		वापस 0;
	
	/* Kauai has bus control FCRs directly here */
	अगर (pmअगर->kauai_fcr) अणु
		u32 fcr = पढ़ोl(pmअगर->kauai_fcr);
		fcr &= ~(KAUAI_FCR_UATA_RESET_N | KAUAI_FCR_UATA_ENABLE);
		ग_लिखोl(fcr, pmअगर->kauai_fcr);
	पूर्ण

	/* Disable the bus on older machines and the cell on kauai */
	ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, pmअगर->node, pmअगर->aapl_bus_id,
			    0);

	वापस 0;
पूर्ण

/* Resume call back, should be called beक्रमe the child devices
 * are resumed
 */
अटल पूर्णांक pmac_ide_करो_resume(pmac_ide_hwअगर_t *pmअगर)
अणु
	/* Hard reset & re-enable controller (करो we really need to reset ? -BenH) */
	अगर (!on_media_bay(pmअगर)) अणु
		ppc_md.feature_call(PMAC_FTR_IDE_RESET, pmअगर->node, pmअगर->aapl_bus_id, 1);
		ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, pmअगर->node, pmअगर->aapl_bus_id, 1);
		msleep(10);
		ppc_md.feature_call(PMAC_FTR_IDE_RESET, pmअगर->node, pmअगर->aapl_bus_id, 0);

		/* Kauai has it dअगरferent */
		अगर (pmअगर->kauai_fcr) अणु
			u32 fcr = पढ़ोl(pmअगर->kauai_fcr);
			fcr |= KAUAI_FCR_UATA_RESET_N | KAUAI_FCR_UATA_ENABLE;
			ग_लिखोl(fcr, pmअगर->kauai_fcr);
		पूर्ण

		msleep(jअगरfies_to_msecs(IDE_WAKEUP_DELAY));
	पूर्ण

	/* Sanitize drive timings */
	sanitize_timings(pmअगर);

	enable_irq(pmअगर->irq);

	वापस 0;
पूर्ण

अटल u8 pmac_ide_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	काष्ठा device_node *np = pmअगर->node;
	स्थिर अक्षर *cable = of_get_property(np, "cable-type", शून्य);
	काष्ठा device_node *root = of_find_node_by_path("/");
	स्थिर अक्षर *model = of_get_property(root, "model", शून्य);

	of_node_put(root);
	/* Get cable type from device-tree. */
	अगर (cable && !म_भेदन(cable, "80-", 3)) अणु
		/* Some drives fail to detect 80c cable in PowerBook */
		/* These machine use proprietary लघु IDE cable anyway */
		अगर (!म_भेदन(model, "PowerBook", 9))
			वापस ATA_CBL_PATA40_SHORT;
		अन्यथा
			वापस ATA_CBL_PATA80;
	पूर्ण

	/*
	 * G5's seem to have incorrect cable type in device-tree.
	 * Let's assume they have a 80 conductor cable, this seem
	 * to be always the हाल unless the user mucked around.
	 */
	अगर (of_device_is_compatible(np, "K2-UATA") ||
	    of_device_is_compatible(np, "shasta-ata"))
		वापस ATA_CBL_PATA80;

	वापस ATA_CBL_PATA40;
पूर्ण

अटल व्योम pmac_ide_init_dev(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);

	अगर (on_media_bay(pmअगर)) अणु
		अगर (check_media_bay(pmअगर->mdev->media_bay) == MB_CD) अणु
			drive->dev_flags &= ~IDE_DFLAG_NOPROBE;
			वापस;
		पूर्ण
		drive->dev_flags |= IDE_DFLAG_NOPROBE;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ide_tp_ops pmac_tp_ops = अणु
	.exec_command		= pmac_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= pmac_ग_लिखो_devctl,

	.dev_select		= pmac_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_tp_ops pmac_ata6_tp_ops = अणु
	.exec_command		= pmac_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= pmac_ग_लिखो_devctl,

	.dev_select		= pmac_kauai_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops pmac_ide_ata4_port_ops = अणु
	.init_dev		= pmac_ide_init_dev,
	.set_pio_mode		= pmac_ide_set_pio_mode,
	.set_dma_mode		= pmac_ide_set_dma_mode,
	.cable_detect		= pmac_ide_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops pmac_ide_port_ops = अणु
	.init_dev		= pmac_ide_init_dev,
	.set_pio_mode		= pmac_ide_set_pio_mode,
	.set_dma_mode		= pmac_ide_set_dma_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops pmac_dma_ops;

अटल स्थिर काष्ठा ide_port_info pmac_port_info = अणु
	.name			= DRV_NAME,
	.init_dma		= pmac_ide_init_dma,
	.chipset		= ide_pmac,
	.tp_ops			= &pmac_tp_ops,
	.port_ops		= &pmac_ide_port_ops,
	.dma_ops		= &pmac_dma_ops,
	.host_flags		= IDE_HFLAG_SET_PIO_MODE_KEEP_DMA |
				  IDE_HFLAG_POST_SET_MODE |
				  IDE_HFLAG_MMIO |
				  IDE_HFLAG_UNMASK_IRQS,
	.pio_mask		= ATA_PIO4,
	.mwdma_mask		= ATA_MWDMA2,
पूर्ण;

/*
 * Setup, रेजिस्टर & probe an IDE channel driven by this driver, this is
 * called by one of the 2 probe functions (macio or PCI).
 */
अटल पूर्णांक pmac_ide_setup_device(pmac_ide_hwअगर_t *pmअगर, काष्ठा ide_hw *hw)
अणु
	काष्ठा device_node *np = pmअगर->node;
	स्थिर पूर्णांक *bidp;
	काष्ठा ide_host *host;
	काष्ठा ide_hw *hws[] = अणु hw पूर्ण;
	काष्ठा ide_port_info d = pmac_port_info;
	पूर्णांक rc;

	pmअगर->broken_dma = pmअगर->broken_dma_warn = 0;
	अगर (of_device_is_compatible(np, "shasta-ata")) अणु
		pmअगर->kind = controller_sh_ata6;
		d.tp_ops = &pmac_ata6_tp_ops;
		d.port_ops = &pmac_ide_ata4_port_ops;
		d.udma_mask = ATA_UDMA6;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "kauai-ata")) अणु
		pmअगर->kind = controller_un_ata6;
		d.tp_ops = &pmac_ata6_tp_ops;
		d.port_ops = &pmac_ide_ata4_port_ops;
		d.udma_mask = ATA_UDMA5;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "K2-UATA")) अणु
		pmअगर->kind = controller_k2_ata6;
		d.tp_ops = &pmac_ata6_tp_ops;
		d.port_ops = &pmac_ide_ata4_port_ops;
		d.udma_mask = ATA_UDMA5;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "keylargo-ata")) अणु
		अगर (of_node_name_eq(np, "ata-4")) अणु
			pmअगर->kind = controller_kl_ata4;
			d.port_ops = &pmac_ide_ata4_port_ops;
			d.udma_mask = ATA_UDMA4;
		पूर्ण अन्यथा
			pmअगर->kind = controller_kl_ata3;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "heathrow-ata")) अणु
		pmअगर->kind = controller_heathrow;
	पूर्ण अन्यथा अणु
		pmअगर->kind = controller_ohare;
		pmअगर->broken_dma = 1;
	पूर्ण

	bidp = of_get_property(np, "AAPL,bus-id", शून्य);
	pmअगर->aapl_bus_id =  bidp ? *bidp : 0;

	/* On Kauai-type controllers, we make sure the FCR is correct */
	अगर (pmअगर->kauai_fcr)
		ग_लिखोl(KAUAI_FCR_UATA_MAGIC |
		       KAUAI_FCR_UATA_RESET_N |
		       KAUAI_FCR_UATA_ENABLE, pmअगर->kauai_fcr);
	
	/* Make sure we have sane timings */
	sanitize_timings(pmअगर);

	/* If we are on a media bay, रुको क्रम it to settle and lock it */
	अगर (pmअगर->mdev)
		lock_media_bay(pmअगर->mdev->media_bay);

	host = ide_host_alloc(&d, hws, 1);
	अगर (host == शून्य) अणु
		rc = -ENOMEM;
		जाओ bail;
	पूर्ण
	pmअगर->hwअगर = host->ports[0];

	अगर (on_media_bay(pmअगर)) अणु
		/* Fixup bus ID क्रम media bay */
		अगर (!bidp)
			pmअगर->aapl_bus_id = 1;
	पूर्ण अन्यथा अगर (pmअगर->kind == controller_ohare) अणु
		/* The code below is having trouble on some ohare machines
		 * (timing related ?). Until I can put my hand on one of these
		 * units, I keep the old way
		 */
		ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, np, 0, 1);
	पूर्ण अन्यथा अणु
 		/* This is necessary to enable IDE when net-booting */
		ppc_md.feature_call(PMAC_FTR_IDE_RESET, np, pmअगर->aapl_bus_id, 1);
		ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, np, pmअगर->aapl_bus_id, 1);
		msleep(10);
		ppc_md.feature_call(PMAC_FTR_IDE_RESET, np, pmअगर->aapl_bus_id, 0);
		msleep(jअगरfies_to_msecs(IDE_WAKEUP_DELAY));
	पूर्ण

	prपूर्णांकk(KERN_INFO DRV_NAME ": Found Apple %s controller (%s), "
	       "bus ID %d%s, irq %d\n", model_name[pmअगर->kind],
	       pmअगर->mdev ? "macio" : "PCI", pmअगर->aapl_bus_id,
	       on_media_bay(pmअगर) ? " (mediabay)" : "", hw->irq);

	rc = ide_host_रेजिस्टर(host, &d, hws);
	अगर (rc)
		pmअगर->hwअगर = शून्य;

	अगर (pmअगर->mdev)
		unlock_media_bay(pmअगर->mdev->media_bay);

 bail:
	अगर (rc && host)
		ide_host_मुक्त(host);
	वापस rc;
पूर्ण

अटल व्योम pmac_ide_init_ports(काष्ठा ide_hw *hw, अचिन्हित दीर्घ base)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; ++i)
		hw->io_ports_array[i] = base + i * 0x10;

	hw->io_ports.ctl_addr = base + 0x160;
पूर्ण

/*
 * Attach to a macio probed पूर्णांकerface
 */
अटल पूर्णांक pmac_ide_macio_attach(काष्ठा macio_dev *mdev,
				 स्थिर काष्ठा of_device_id *match)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ regbase;
	pmac_ide_hwअगर_t *pmअगर;
	पूर्णांक irq, rc;
	काष्ठा ide_hw hw;

	pmअगर = kzalloc(माप(*pmअगर), GFP_KERNEL);
	अगर (pmअगर == शून्य)
		वापस -ENOMEM;

	अगर (macio_resource_count(mdev) == 0) अणु
		prपूर्णांकk(KERN_WARNING "ide-pmac: no address for %pOF\n",
				    mdev->ofdev.dev.of_node);
		rc = -ENXIO;
		जाओ out_मुक्त_pmअगर;
	पूर्ण

	/* Request memory resource क्रम IO ports */
	अगर (macio_request_resource(mdev, 0, "ide-pmac (ports)")) अणु
		prपूर्णांकk(KERN_ERR "ide-pmac: can't request MMIO resource for "
				"%pOF!\n", mdev->ofdev.dev.of_node);
		rc = -EBUSY;
		जाओ out_मुक्त_pmअगर;
	पूर्ण
			
	/* XXX This is bogus. Should be fixed in the registry by checking
	 * the kind of host पूर्णांकerrupt controller, a bit like gatwick
	 * fixes in irq.c. That works well enough क्रम the single हाल
	 * where that happens though...
	 */
	अगर (macio_irq_count(mdev) == 0) अणु
		prपूर्णांकk(KERN_WARNING "ide-pmac: no intrs for device %pOF, using "
				    "13\n", mdev->ofdev.dev.of_node);
		irq = irq_create_mapping(शून्य, 13);
	पूर्ण अन्यथा
		irq = macio_irq(mdev, 0);

	base = ioremap(macio_resource_start(mdev, 0), 0x400);
	regbase = (अचिन्हित दीर्घ) base;

	pmअगर->mdev = mdev;
	pmअगर->node = mdev->ofdev.dev.of_node;
	pmअगर->regbase = regbase;
	pmअगर->irq = irq;
	pmअगर->kauai_fcr = शून्य;

	अगर (macio_resource_count(mdev) >= 2) अणु
		अगर (macio_request_resource(mdev, 1, "ide-pmac (dma)"))
			prपूर्णांकk(KERN_WARNING "ide-pmac: can't request DMA "
					    "resource for %pOF!\n",
					    mdev->ofdev.dev.of_node);
		अन्यथा
			pmअगर->dma_regs = ioremap(macio_resource_start(mdev, 1), 0x1000);
	पूर्ण अन्यथा
		pmअगर->dma_regs = शून्य;

	dev_set_drvdata(&mdev->ofdev.dev, pmअगर);

	स_रखो(&hw, 0, माप(hw));
	pmac_ide_init_ports(&hw, pmअगर->regbase);
	hw.irq = irq;
	hw.dev = &mdev->bus->pdev->dev;
	hw.parent = &mdev->ofdev.dev;

	rc = pmac_ide_setup_device(pmअगर, &hw);
	अगर (rc != 0) अणु
		/* The पूर्णांकeface is released to the common IDE layer */
		dev_set_drvdata(&mdev->ofdev.dev, शून्य);
		iounmap(base);
		अगर (pmअगर->dma_regs) अणु
			iounmap(pmअगर->dma_regs);
			macio_release_resource(mdev, 1);
		पूर्ण
		macio_release_resource(mdev, 0);
		kमुक्त(pmअगर);
	पूर्ण

	वापस rc;

out_मुक्त_pmअगर:
	kमुक्त(pmअगर);
	वापस rc;
पूर्ण

अटल पूर्णांक
pmac_ide_macio_suspend(काष्ठा macio_dev *mdev, pm_message_t mesg)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(&mdev->ofdev.dev);
	पूर्णांक rc = 0;

	अगर (mesg.event != mdev->ofdev.dev.घातer.घातer_state.event
			&& (mesg.event & PM_EVENT_SLEEP)) अणु
		rc = pmac_ide_करो_suspend(pmअगर);
		अगर (rc == 0)
			mdev->ofdev.dev.घातer.घातer_state = mesg;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
pmac_ide_macio_resume(काष्ठा macio_dev *mdev)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(&mdev->ofdev.dev);
	पूर्णांक rc = 0;

	अगर (mdev->ofdev.dev.घातer.घातer_state.event != PM_EVENT_ON) अणु
		rc = pmac_ide_करो_resume(pmअगर);
		अगर (rc == 0)
			mdev->ofdev.dev.घातer.घातer_state = PMSG_ON;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Attach to a PCI probed पूर्णांकerface
 */
अटल पूर्णांक pmac_ide_pci_attach(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device_node *np;
	pmac_ide_hwअगर_t *pmअगर;
	व्योम __iomem *base;
	अचिन्हित दीर्घ rbase, rlen;
	पूर्णांक rc;
	काष्ठा ide_hw hw;

	np = pci_device_to_OF_node(pdev);
	अगर (np == शून्य) अणु
		prपूर्णांकk(KERN_ERR "ide-pmac: cannot find MacIO node for Kauai ATA interface\n");
		वापस -ENODEV;
	पूर्ण

	pmअगर = kzalloc(माप(*pmअगर), GFP_KERNEL);
	अगर (pmअगर == शून्य)
		वापस -ENOMEM;

	अगर (pci_enable_device(pdev)) अणु
		prपूर्णांकk(KERN_WARNING "ide-pmac: Can't enable PCI device for "
				    "%pOF\n", np);
		rc = -ENXIO;
		जाओ out_मुक्त_pmअगर;
	पूर्ण
	pci_set_master(pdev);
			
	अगर (pci_request_regions(pdev, "Kauai ATA")) अणु
		prपूर्णांकk(KERN_ERR "ide-pmac: Cannot obtain PCI resources for "
				"%pOF\n", np);
		rc = -ENXIO;
		जाओ out_मुक्त_pmअगर;
	पूर्ण

	pmअगर->mdev = शून्य;
	pmअगर->node = np;

	rbase = pci_resource_start(pdev, 0);
	rlen = pci_resource_len(pdev, 0);

	base = ioremap(rbase, rlen);
	pmअगर->regbase = (अचिन्हित दीर्घ) base + 0x2000;
	pmअगर->dma_regs = base + 0x1000;
	pmअगर->kauai_fcr = base;
	pmअगर->irq = pdev->irq;

	pci_set_drvdata(pdev, pmअगर);

	स_रखो(&hw, 0, माप(hw));
	pmac_ide_init_ports(&hw, pmअगर->regbase);
	hw.irq = pdev->irq;
	hw.dev = &pdev->dev;

	rc = pmac_ide_setup_device(pmअगर, &hw);
	अगर (rc != 0) अणु
		/* The पूर्णांकeface is released to the common IDE layer */
		iounmap(base);
		pci_release_regions(pdev);
		kमुक्त(pmअगर);
	पूर्ण

	वापस rc;

out_मुक्त_pmअगर:
	kमुक्त(pmअगर);
	वापस rc;
पूर्ण

अटल पूर्णांक
pmac_ide_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	pmac_ide_hwअगर_t *pmअगर = pci_get_drvdata(pdev);
	पूर्णांक rc = 0;

	अगर (mesg.event != pdev->dev.घातer.घातer_state.event
			&& (mesg.event & PM_EVENT_SLEEP)) अणु
		rc = pmac_ide_करो_suspend(pmअगर);
		अगर (rc == 0)
			pdev->dev.घातer.घातer_state = mesg;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
pmac_ide_pci_resume(काष्ठा pci_dev *pdev)
अणु
	pmac_ide_hwअगर_t *pmअगर = pci_get_drvdata(pdev);
	पूर्णांक rc = 0;

	अगर (pdev->dev.घातer.घातer_state.event != PM_EVENT_ON) अणु
		rc = pmac_ide_करो_resume(pmअगर);
		अगर (rc == 0)
			pdev->dev.घातer.घातer_state = PMSG_ON;
	पूर्ण

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PMAC_MEDIABAY
अटल व्योम pmac_ide_macio_mb_event(काष्ठा macio_dev* mdev, पूर्णांक mb_state)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(&mdev->ofdev.dev);

	चयन(mb_state) अणु
	हाल MB_CD:
		अगर (!pmअगर->hwअगर->present)
			ide_port_scan(pmअगर->hwअगर);
		अवरोध;
	शेष:
		अगर (pmअगर->hwअगर->present)
			ide_port_unरेजिस्टर_devices(pmअगर->hwअगर);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PMAC_MEDIABAY */


अटल काष्ठा of_device_id pmac_ide_macio_match[] = 
अणु
	अणु
	.name 		= "IDE",
	पूर्ण,
	अणु
	.name 		= "ATA",
	पूर्ण,
	अणु
	.type		= "ide",
	पूर्ण,
	अणु
	.type		= "ata",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा macio_driver pmac_ide_macio_driver = 
अणु
	.driver = अणु
		.name 		= "ide-pmac",
		.owner		= THIS_MODULE,
		.of_match_table	= pmac_ide_macio_match,
	पूर्ण,
	.probe		= pmac_ide_macio_attach,
	.suspend	= pmac_ide_macio_suspend,
	.resume		= pmac_ide_macio_resume,
#अगर_घोषित CONFIG_PMAC_MEDIABAY
	.mediabay_event	= pmac_ide_macio_mb_event,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pmac_ide_pci_match[] = अणु
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_UNI_N_ATA),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_IPID_ATA100),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_K2_ATA100),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_SH_ATA),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_IPID2_ATA),	0 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pci_driver pmac_ide_pci_driver = अणु
	.name		= "ide-pmac",
	.id_table	= pmac_ide_pci_match,
	.probe		= pmac_ide_pci_attach,
	.suspend	= pmac_ide_pci_suspend,
	.resume		= pmac_ide_pci_resume,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pmac_ide_pci_match);

पूर्णांक __init pmac_ide_probe(व्योम)
अणु
	पूर्णांक error;

	अगर (!machine_is(घातermac))
		वापस -ENODEV;

#अगर_घोषित CONFIG_BLK_DEV_IDE_PMAC_ATA100FIRST
	error = pci_रेजिस्टर_driver(&pmac_ide_pci_driver);
	अगर (error)
		जाओ out;
	error = macio_रेजिस्टर_driver(&pmac_ide_macio_driver);
	अगर (error) अणु
		pci_unरेजिस्टर_driver(&pmac_ide_pci_driver);
		जाओ out;
	पूर्ण
#अन्यथा
	error = macio_रेजिस्टर_driver(&pmac_ide_macio_driver);
	अगर (error)
		जाओ out;
	error = pci_रेजिस्टर_driver(&pmac_ide_pci_driver);
	अगर (error) अणु
		macio_unरेजिस्टर_driver(&pmac_ide_macio_driver);
		जाओ out;
	पूर्ण
#पूर्ण_अगर
out:
	वापस error;
पूर्ण

/*
 * pmac_ide_build_dmatable builds the DBDMA command list
 * क्रम a transfer and sets the DBDMA channel to poपूर्णांक to it.
 */
अटल पूर्णांक pmac_ide_build_dmatable(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	काष्ठा dbdma_cmd *table;
	अस्थिर काष्ठा dbdma_regs __iomem *dma = pmअगर->dma_regs;
	काष्ठा scatterlist *sg;
	पूर्णांक wr = !!(cmd->tf_flags & IDE_TFLAG_WRITE);
	पूर्णांक i = cmd->sg_nents, count = 0;

	/* DMA table is alपढ़ोy aligned */
	table = (काष्ठा dbdma_cmd *) pmअगर->dma_table_cpu;

	/* Make sure DMA controller is stopped (necessary ?) */
	ग_लिखोl((RUN|PAUSE|FLUSH|WAKE|DEAD) << 16, &dma->control);
	जबतक (पढ़ोl(&dma->status) & RUN)
		udelay(1);

	/* Build DBDMA commands list */
	sg = hwअगर->sg_table;
	जबतक (i && sg_dma_len(sg)) अणु
		u32 cur_addr;
		u32 cur_len;

		cur_addr = sg_dma_address(sg);
		cur_len = sg_dma_len(sg);

		अगर (pmअगर->broken_dma && cur_addr & (L1_CACHE_BYTES - 1)) अणु
			अगर (pmअगर->broken_dma_warn == 0) अणु
				prपूर्णांकk(KERN_WARNING "%s: DMA on non aligned address, "
				       "switching to PIO on Ohare chipset\n", drive->name);
				pmअगर->broken_dma_warn = 1;
			पूर्ण
			वापस 0;
		पूर्ण
		जबतक (cur_len) अणु
			अचिन्हित पूर्णांक tc = (cur_len < 0xfe00)? cur_len: 0xfe00;

			अगर (count++ >= MAX_DCMDS) अणु
				prपूर्णांकk(KERN_WARNING "%s: DMA table too small\n",
				       drive->name);
				वापस 0;
			पूर्ण
			table->command = cpu_to_le16(wr? OUTPUT_MORE: INPUT_MORE);
			table->req_count = cpu_to_le16(tc);
			table->phy_addr = cpu_to_le32(cur_addr);
			table->cmd_dep = 0;
			table->xfer_status = 0;
			table->res_count = 0;
			cur_addr += tc;
			cur_len -= tc;
			++table;
		पूर्ण
		sg = sg_next(sg);
		i--;
	पूर्ण

	/* convert the last command to an input/output last command */
	अगर (count) अणु
		table[-1].command = cpu_to_le16(wr? OUTPUT_LAST: INPUT_LAST);
		/* add the stop command to the end of the list */
		स_रखो(table, 0, माप(काष्ठा dbdma_cmd));
		table->command = cpu_to_le16(DBDMA_STOP);
		mb();
		ग_लिखोl(hwअगर->dmatable_dma, &dma->cmdptr);
		वापस 1;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: empty DMA table?\n", drive->name);

	वापस 0; /* revert to PIO क्रम this request */
पूर्ण

/*
 * Prepare a DMA transfer. We build the DMA table, adjust the timings क्रम
 * a पढ़ो on KeyLargo ATA/66 and mark us as रुकोing क्रम DMA completion
 */
अटल पूर्णांक pmac_ide_dma_setup(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	u8 unit = drive->dn & 1, ata4 = (pmअगर->kind == controller_kl_ata4);
	u8 ग_लिखो = !!(cmd->tf_flags & IDE_TFLAG_WRITE);

	अगर (pmac_ide_build_dmatable(drive, cmd) == 0)
		वापस 1;

	/* Apple adds 60ns to wrDataSetup on पढ़ोs */
	अगर (ata4 && (pmअगर->timings[unit] & TR_66_UDMA_EN)) अणु
		ग_लिखोl(pmअगर->timings[unit] + (ग_लिखो ? 0 : 0x00800000UL),
			PMAC_IDE_REG(IDE_TIMING_CONFIG));
		(व्योम)पढ़ोl(PMAC_IDE_REG(IDE_TIMING_CONFIG));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Kick the DMA controller पूर्णांकo lअगरe after the DMA command has been issued
 * to the drive.
 */
अटल व्योम
pmac_ide_dma_start(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	अस्थिर काष्ठा dbdma_regs __iomem *dma;

	dma = pmअगर->dma_regs;

	ग_लिखोl((RUN << 16) | RUN, &dma->control);
	/* Make sure it माला_लो to the controller right now */
	(व्योम)पढ़ोl(&dma->control);
पूर्ण

/*
 * After a DMA transfer, make sure the controller is stopped
 */
अटल पूर्णांक
pmac_ide_dma_end (ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	अस्थिर काष्ठा dbdma_regs __iomem *dma = pmअगर->dma_regs;
	u32 dstat;

	dstat = पढ़ोl(&dma->status);
	ग_लिखोl(((RUN|WAKE|DEAD) << 16), &dma->control);

	/* verअगरy good dma status. we करोn't check क्रम ACTIVE beeing 0. We should...
	 * in theory, but with ATAPI decices करोing buffer underruns, that would
	 * cause us to disable DMA, which isn't what we want
	 */
	वापस (dstat & (RUN|DEAD)) != RUN;
पूर्ण

/*
 * Check out that the पूर्णांकerrupt we got was क्रम us. We can't always know this
 * क्रम sure with those Apple पूर्णांकerfaces (well, we could on the recent ones but
 * that's not implemented yet), on the other hand, we don't have shared पूर्णांकerrupts
 * so it's not really a problem
 */
अटल पूर्णांक
pmac_ide_dma_test_irq (ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	अस्थिर काष्ठा dbdma_regs __iomem *dma = pmअगर->dma_regs;
	अचिन्हित दीर्घ status, समयout;

	/* We have to things to deal with here:
	 * 
	 * - The dbdma won't stop अगर the command was started
	 * but completed with an error without transferring all
	 * datas. This happens when bad blocks are met during
	 * a multi-block transfer.
	 * 
	 * - The dbdma fअगरo hasn't yet finished flushing to
	 * to प्रणाली memory when the disk पूर्णांकerrupt occurs.
	 * 
	 */

	/* If ACTIVE is cleared, the STOP command have passed and
	 * transfer is complete.
	 */
	status = पढ़ोl(&dma->status);
	अगर (!(status & ACTIVE))
		वापस 1;

	/* If dbdma didn't execute the STOP command yet, the
	 * active bit is still set. We consider that we aren't
	 * sharing पूर्णांकerrupts (which is hopefully the हाल with
	 * those controllers) and so we just try to flush the
	 * channel क्रम pending data in the fअगरo
	 */
	udelay(1);
	ग_लिखोl((FLUSH << 16) | FLUSH, &dma->control);
	समयout = 0;
	क्रम (;;) अणु
		udelay(1);
		status = पढ़ोl(&dma->status);
		अगर ((status & FLUSH) == 0)
			अवरोध;
		अगर (++समयout > 100) अणु
			prपूर्णांकk(KERN_WARNING "ide%d, ide_dma_test_irq timeout flushing channel\n",
			       hwअगर->index);
			अवरोध;
		पूर्ण
	पूर्ण	
	वापस 1;
पूर्ण

अटल व्योम pmac_ide_dma_host_set(ide_drive_t *drive, पूर्णांक on)
अणु
पूर्ण

अटल व्योम
pmac_ide_dma_lost_irq (ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	अस्थिर काष्ठा dbdma_regs __iomem *dma = pmअगर->dma_regs;
	अचिन्हित दीर्घ status = पढ़ोl(&dma->status);

	prपूर्णांकk(KERN_ERR "ide-pmac lost interrupt, dma status: %lx\n", status);
पूर्ण

अटल स्थिर काष्ठा ide_dma_ops pmac_dma_ops = अणु
	.dma_host_set		= pmac_ide_dma_host_set,
	.dma_setup		= pmac_ide_dma_setup,
	.dma_start		= pmac_ide_dma_start,
	.dma_end		= pmac_ide_dma_end,
	.dma_test_irq		= pmac_ide_dma_test_irq,
	.dma_lost_irq		= pmac_ide_dma_lost_irq,
पूर्ण;

/*
 * Allocate the data काष्ठाures needed क्रम using DMA with an पूर्णांकerface
 * and fill the proper list of functions poपूर्णांकers
 */
अटल पूर्णांक pmac_ide_init_dma(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	pmac_ide_hwअगर_t *pmअगर = dev_get_drvdata(hwअगर->gendev.parent);
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	/* We won't need pci_dev अगर we चयन to generic consistent
	 * DMA routines ...
	 */
	अगर (dev == शून्य || pmअगर->dma_regs == 0)
		वापस -ENODEV;
	/*
	 * Allocate space क्रम the DBDMA commands.
	 * The +2 is +1 क्रम the stop command and +1 to allow क्रम
	 * aligning the start address to a multiple of 16 bytes.
	 */
	pmअगर->dma_table_cpu = dma_alloc_coherent(&dev->dev,
		(MAX_DCMDS + 2) * माप(काष्ठा dbdma_cmd),
		&hwअगर->dmatable_dma, GFP_KERNEL);
	अगर (pmअगर->dma_table_cpu == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to allocate DMA command list\n",
		       hwअगर->name);
		वापस -ENOMEM;
	पूर्ण

	hwअगर->sg_max_nents = MAX_DCMDS;

	वापस 0;
पूर्ण

module_init(pmac_ide_probe);

MODULE_LICENSE("GPL");
