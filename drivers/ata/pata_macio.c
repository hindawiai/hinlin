<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Libata based driver क्रम Apple "macio" family of PATA controllers
 *
 * Copyright 2008/2009 Benjamin Herrenschmidt, IBM Corp
 *                     <benh@kernel.crashing.org>
 *
 * Some bits and pieces from drivers/ide/ppc/pmac.c
 *
 */

#अघोषित DEBUG
#अघोषित DEBUG_DMA

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/of.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>

#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/mediabay.h>

#अगर_घोषित DEBUG_DMA
#घोषणा dev_dbgdma(dev, क्रमmat, arg...)		\
	dev_prपूर्णांकk(KERN_DEBUG , dev , क्रमmat , ## arg)
#अन्यथा
#घोषणा dev_dbgdma(dev, क्रमmat, arg...)		\
	(अणु अगर (0) dev_prपूर्णांकk(KERN_DEBUG, dev, क्रमmat, ##arg); 0; पूर्ण)
#पूर्ण_अगर

#घोषणा DRV_NAME	"pata_macio"
#घोषणा DRV_VERSION	"0.9"

/* Models of macio ATA controller */
क्रमागत अणु
	controller_ohare,	/* OHare based */
	controller_heathrow,	/* Heathrow/Paddington */
	controller_kl_ata3,	/* KeyLargo ATA-3 */
	controller_kl_ata4,	/* KeyLargo ATA-4 */
	controller_un_ata6,	/* UniNorth2 ATA-6 */
	controller_k2_ata6,	/* K2 ATA-6 */
	controller_sh_ata6,	/* Shasta ATA-6 */
पूर्ण;

अटल स्थिर अक्षर* macio_ata_names[] = अणु
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
 * Note that PIO_MASK and MDMA_MASK seem to overlap, that's just
 * weird and I करोn't now why .. at this stage
 */
#घोषणा TR_133_PIOREG_PIO_MASK		0xff000fff
#घोषणा TR_133_PIOREG_MDMA_MASK		0x00fff800
#घोषणा TR_133_UDMAREG_UDMA_MASK	0x0003ffff
#घोषणा TR_133_UDMAREG_UDMA_EN		0x00000001

/* 100Mhz cell, found in Uninorth 2 and K2. It appears as a pci device
 * (106b/0033) on uninorth or K2 पूर्णांकernal PCI bus and it's घड़ी is
 * controlled like gem or fw. It appears to be an evolution of keylargo
 * ATA4 with a timing रेजिस्टर extended to 2x32bits रेजिस्टरs (one
 * क्रम PIO & MWDMA and one क्रम UDMA, and a similar DBDMA channel.
 * It has it's own local feature control रेजिस्टर as well.
 *
 * After scratching my mind over the timing values, at least क्रम PIO
 * and MDMA, I think I've figured the क्रमmat of the timing रेजिस्टर,
 * though I use pre-calculated tables क्रम UDMA as usual...
 */
#घोषणा TR_100_PIO_ADDRSETUP_MASK	0xff000000 /* Size of field unknown */
#घोषणा TR_100_PIO_ADDRSETUP_SHIFT	24
#घोषणा TR_100_MDMA_MASK		0x00fff000
#घोषणा TR_100_MDMA_RECOVERY_MASK	0x00fc0000
#घोषणा TR_100_MDMA_RECOVERY_SHIFT	18
#घोषणा TR_100_MDMA_ACCESS_MASK		0x0003f000
#घोषणा TR_100_MDMA_ACCESS_SHIFT	12
#घोषणा TR_100_PIO_MASK			0xff000fff
#घोषणा TR_100_PIO_RECOVERY_MASK	0x00000fc0
#घोषणा TR_100_PIO_RECOVERY_SHIFT	6
#घोषणा TR_100_PIO_ACCESS_MASK		0x0000003f
#घोषणा TR_100_PIO_ACCESS_SHIFT		0

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
#घोषणा TR_66_PIO_ADDRSETUP_MASK	0xe0000000 /* Address setup */
#घोषणा TR_66_PIO_ADDRSETUP_SHIFT	29
#घोषणा TR_66_UDMA_RDY2PAUS_MASK	0x1e000000 /* Ready 2 छोड़ो समय */
#घोषणा TR_66_UDMA_RDY2PAUS_SHIFT	25
#घोषणा TR_66_UDMA_WRDATASETUP_MASK	0x01e00000 /* Write data setup समय */
#घोषणा TR_66_UDMA_WRDATASETUP_SHIFT	21
#घोषणा TR_66_MDMA_MASK			0x000ffc00
#घोषणा TR_66_MDMA_RECOVERY_MASK	0x000f8000
#घोषणा TR_66_MDMA_RECOVERY_SHIFT	15
#घोषणा TR_66_MDMA_ACCESS_MASK		0x00007c00
#घोषणा TR_66_MDMA_ACCESS_SHIFT		10
#घोषणा TR_66_PIO_MASK			0xe00003ff
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
 * Interrupt रेजिस्टर definitions. Only present on newer cells
 * (Keylargo and later afaik) so we करोn't use it.
 */
#घोषणा IDE_INTR_DMA			0x80000000
#घोषणा IDE_INTR_DEVICE			0x40000000

/*
 * FCR Register on Kauai. Not sure what bit 0x4 is  ...
 */
#घोषणा KAUAI_FCR_UATA_MAGIC		0x00000004
#घोषणा KAUAI_FCR_UATA_RESET_N		0x00000002
#घोषणा KAUAI_FCR_UATA_ENABLE		0x00000001


/* Allow up to 256 DBDMA commands per xfer */
#घोषणा MAX_DCMDS		256

/* Don't let a DMA segment go all the way to 64K */
#घोषणा MAX_DBDMA_SEG		0xff00


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
#घोषणा IDE_WAKEUP_DELAY_MS	1000

काष्ठा pata_macio_timing;

काष्ठा pata_macio_priv अणु
	पूर्णांक				kind;
	पूर्णांक				aapl_bus_id;
	पूर्णांक				mediabay : 1;
	काष्ठा device_node		*node;
	काष्ठा macio_dev		*mdev;
	काष्ठा pci_dev			*pdev;
	काष्ठा device			*dev;
	पूर्णांक				irq;
	u32				treg[2][2];
	व्योम __iomem			*tfregs;
	व्योम __iomem			*kauai_fcr;
	काष्ठा dbdma_cmd *		dma_table_cpu;
	dma_addr_t			dma_table_dma;
	काष्ठा ata_host			*host;
	स्थिर काष्ठा pata_macio_timing	*timings;
पूर्ण;

/* Previous variants of this driver used to calculate timings
 * क्रम various variants of the chip and use tables क्रम others.
 *
 * Not only was this confusing, but in addition, it isn't clear
 * whether our calculation code was correct. It didn't entirely
 * match the darwin code and whatever करोcumentation I could find
 * on these cells
 *
 * I decided to entirely rely on a table instead क्रम this version
 * of the driver. Also, because I करोn't really care about derated
 * modes and really old HW other than making it work, I'm not going
 * to calculate / snoop timing values क्रम something अन्यथा than the
 * standard modes.
 */
काष्ठा pata_macio_timing अणु
	पूर्णांक	mode;
	u32	reg1;	/* Bits to set in first timing reg */
	u32	reg2;	/* Bits to set in second timing reg */
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing pata_macio_ohare_timings[] = अणु
	अणु XFER_PIO_0,		0x00000526,	0, पूर्ण,
	अणु XFER_PIO_1,		0x00000085,	0, पूर्ण,
	अणु XFER_PIO_2,		0x00000025,	0, पूर्ण,
	अणु XFER_PIO_3,		0x00000025,	0, पूर्ण,
	अणु XFER_PIO_4,		0x00000025,	0, पूर्ण,
	अणु XFER_MW_DMA_0,	0x00074000,	0, पूर्ण,
	अणु XFER_MW_DMA_1,	0x00221000,	0, पूर्ण,
	अणु XFER_MW_DMA_2,	0x00211000,	0, पूर्ण,
	अणु -1, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing pata_macio_heathrow_timings[] = अणु
	अणु XFER_PIO_0,		0x00000526,	0, पूर्ण,
	अणु XFER_PIO_1,		0x00000085,	0, पूर्ण,
	अणु XFER_PIO_2,		0x00000025,	0, पूर्ण,
	अणु XFER_PIO_3,		0x00000025,	0, पूर्ण,
	अणु XFER_PIO_4,		0x00000025,	0, पूर्ण,
	अणु XFER_MW_DMA_0,	0x00074000,	0, पूर्ण,
	अणु XFER_MW_DMA_1,	0x00221000,	0, पूर्ण,
	अणु XFER_MW_DMA_2,	0x00211000,	0, पूर्ण,
	अणु -1, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing pata_macio_kl33_timings[] = अणु
	अणु XFER_PIO_0,		0x00000526,	0, पूर्ण,
	अणु XFER_PIO_1,		0x00000085,	0, पूर्ण,
	अणु XFER_PIO_2,		0x00000025,	0, पूर्ण,
	अणु XFER_PIO_3,		0x00000025,	0, पूर्ण,
	अणु XFER_PIO_4,		0x00000025,	0, पूर्ण,
	अणु XFER_MW_DMA_0,	0x00084000,	0, पूर्ण,
	अणु XFER_MW_DMA_1,	0x00021800,	0, पूर्ण,
	अणु XFER_MW_DMA_2,	0x00011800,	0, पूर्ण,
	अणु -1, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing pata_macio_kl66_timings[] = अणु
	अणु XFER_PIO_0,		0x0000038c,	0, पूर्ण,
	अणु XFER_PIO_1,		0x0000020a,	0, पूर्ण,
	अणु XFER_PIO_2,		0x00000127,	0, पूर्ण,
	अणु XFER_PIO_3,		0x000000c6,	0, पूर्ण,
	अणु XFER_PIO_4,		0x00000065,	0, पूर्ण,
	अणु XFER_MW_DMA_0,	0x00084000,	0, पूर्ण,
	अणु XFER_MW_DMA_1,	0x00029800,	0, पूर्ण,
	अणु XFER_MW_DMA_2,	0x00019400,	0, पूर्ण,
	अणु XFER_UDMA_0,		0x19100000,	0, पूर्ण,
	अणु XFER_UDMA_1,		0x14d00000,	0, पूर्ण,
	अणु XFER_UDMA_2,		0x10900000,	0, पूर्ण,
	अणु XFER_UDMA_3,		0x0c700000,	0, पूर्ण,
	अणु XFER_UDMA_4,		0x0c500000,	0, पूर्ण,
	अणु -1, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing pata_macio_kauai_timings[] = अणु
	अणु XFER_PIO_0,		0x08000a92,	0, पूर्ण,
	अणु XFER_PIO_1,		0x0800060f,	0, पूर्ण,
	अणु XFER_PIO_2,		0x0800038b,	0, पूर्ण,
	अणु XFER_PIO_3,		0x05000249,	0, पूर्ण,
	अणु XFER_PIO_4,		0x04000148,	0, पूर्ण,
	अणु XFER_MW_DMA_0,	0x00618000,	0, पूर्ण,
	अणु XFER_MW_DMA_1,	0x00209000,	0, पूर्ण,
	अणु XFER_MW_DMA_2,	0x00148000,	0, पूर्ण,
	अणु XFER_UDMA_0,		         0,	0x000070c1, पूर्ण,
	अणु XFER_UDMA_1,		         0,	0x00005d81, पूर्ण,
	अणु XFER_UDMA_2,		         0,	0x00004a61, पूर्ण,
	अणु XFER_UDMA_3,		         0,	0x00003a51, पूर्ण,
	अणु XFER_UDMA_4,		         0,	0x00002a31, पूर्ण,
	अणु XFER_UDMA_5,		         0,	0x00002921, पूर्ण,
	अणु -1, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing pata_macio_shasta_timings[] = अणु
	अणु XFER_PIO_0,		0x0a000c97,	0, पूर्ण,
	अणु XFER_PIO_1,		0x07000712,	0, पूर्ण,
	अणु XFER_PIO_2,		0x040003cd,	0, पूर्ण,
	अणु XFER_PIO_3,		0x0500028b,	0, पूर्ण,
	अणु XFER_PIO_4,		0x0400010a,	0, पूर्ण,
	अणु XFER_MW_DMA_0,	0x00820800,	0, पूर्ण,
	अणु XFER_MW_DMA_1,	0x0028b000,	0, पूर्ण,
	अणु XFER_MW_DMA_2,	0x001ca000,	0, पूर्ण,
	अणु XFER_UDMA_0,		         0,	0x00035901, पूर्ण,
	अणु XFER_UDMA_1,		         0,	0x000348b1, पूर्ण,
	अणु XFER_UDMA_2,		         0,	0x00033881, पूर्ण,
	अणु XFER_UDMA_3,		         0,	0x00033861, पूर्ण,
	अणु XFER_UDMA_4,		         0,	0x00033841, पूर्ण,
	अणु XFER_UDMA_5,		         0,	0x00033031, पूर्ण,
	अणु XFER_UDMA_6,		         0,	0x00033021, पूर्ण,
	अणु -1, 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pata_macio_timing *pata_macio_find_timing(
					    काष्ठा pata_macio_priv *priv,
					    पूर्णांक mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; priv->timings[i].mode > 0; i++) अणु
		अगर (priv->timings[i].mode == mode)
			वापस &priv->timings[i];
	पूर्ण
	वापस शून्य;
पूर्ण


अटल व्योम pata_macio_apply_timings(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	व्योम __iomem *rbase = ap->ioaddr.cmd_addr;

	अगर (priv->kind == controller_sh_ata6 ||
	    priv->kind == controller_un_ata6 ||
	    priv->kind == controller_k2_ata6) अणु
		ग_लिखोl(priv->treg[device][0], rbase + IDE_KAUAI_PIO_CONFIG);
		ग_लिखोl(priv->treg[device][1], rbase + IDE_KAUAI_ULTRA_CONFIG);
	पूर्ण अन्यथा
		ग_लिखोl(priv->treg[device][0], rbase + IDE_TIMING_CONFIG);
पूर्ण

अटल व्योम pata_macio_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	ata_sff_dev_select(ap, device);

	/* Apply timings */
	pata_macio_apply_timings(ap, device);
पूर्ण

अटल व्योम pata_macio_set_timings(काष्ठा ata_port *ap,
				   काष्ठा ata_device *adev)
अणु
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	स्थिर काष्ठा pata_macio_timing *t;

	dev_dbg(priv->dev, "Set timings: DEV=%d,PIO=0x%x (%s),DMA=0x%x (%s)\n",
		adev->devno,
		adev->pio_mode,
		ata_mode_string(ata_xfer_mode2mask(adev->pio_mode)),
		adev->dma_mode,
		ata_mode_string(ata_xfer_mode2mask(adev->dma_mode)));

	/* First clear timings */
	priv->treg[adev->devno][0] = priv->treg[adev->devno][1] = 0;

	/* Now get the PIO timings */
	t = pata_macio_find_timing(priv, adev->pio_mode);
	अगर (t == शून्य) अणु
		dev_warn(priv->dev, "Invalid PIO timing requested: 0x%x\n",
			 adev->pio_mode);
		t = pata_macio_find_timing(priv, XFER_PIO_0);
	पूर्ण
	BUG_ON(t == शून्य);

	/* PIO timings only ever use the first treg */
	priv->treg[adev->devno][0] |= t->reg1;

	/* Now get DMA timings */
	t = pata_macio_find_timing(priv, adev->dma_mode);
	अगर (t == शून्य || (t->reg1 == 0 && t->reg2 == 0)) अणु
		dev_dbg(priv->dev, "DMA timing not set yet, using MW_DMA_0\n");
		t = pata_macio_find_timing(priv, XFER_MW_DMA_0);
	पूर्ण
	BUG_ON(t == शून्य);

	/* DMA timings can use both tregs */
	priv->treg[adev->devno][0] |= t->reg1;
	priv->treg[adev->devno][1] |= t->reg2;

	dev_dbg(priv->dev, " -> %08x %08x\n",
		priv->treg[adev->devno][0],
		priv->treg[adev->devno][1]);

	/* Apply to hardware */
	pata_macio_apply_timings(ap, adev->devno);
पूर्ण

/*
 * Blast some well known "safe" values to the timing रेजिस्टरs at init or
 * wakeup from sleep समय, beक्रमe we करो real calculation
 */
अटल व्योम pata_macio_शेष_timings(काष्ठा pata_macio_priv *priv)
अणु
	अचिन्हित पूर्णांक value, value2 = 0;

	चयन(priv->kind) अणु
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
	priv->treg[0][0] = priv->treg[1][0] = value;
	priv->treg[0][1] = priv->treg[1][1] = value2;
पूर्ण

अटल पूर्णांक pata_macio_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_macio_priv *priv = ap->निजी_data;

	/* Get cable type from device-tree */
	अगर (priv->kind == controller_kl_ata4 ||
	    priv->kind == controller_un_ata6 ||
	    priv->kind == controller_k2_ata6 ||
	    priv->kind == controller_sh_ata6) अणु
		स्थिर अक्षर* cable = of_get_property(priv->node, "cable-type",
						    शून्य);
		काष्ठा device_node *root = of_find_node_by_path("/");
		स्थिर अक्षर *model = of_get_property(root, "model", शून्य);

		of_node_put(root);

		अगर (cable && !म_भेदन(cable, "80-", 3)) अणु
			/* Some drives fail to detect 80c cable in PowerBook
			 * These machine use proprietary लघु IDE cable
			 * anyway
			 */
			अगर (!म_भेदन(model, "PowerBook", 9))
				वापस ATA_CBL_PATA40_SHORT;
			अन्यथा
				वापस ATA_CBL_PATA80;
		पूर्ण
	पूर्ण

	/* G5's seem to have incorrect cable type in device-tree.
	 * Let's assume they always have a 80 conductor cable, this seem to
	 * be always the हाल unless the user mucked around
	 */
	अगर (of_device_is_compatible(priv->node, "K2-UATA") ||
	    of_device_is_compatible(priv->node, "shasta-ata"))
		वापस ATA_CBL_PATA80;

	/* Anything अन्यथा is 40 connectors */
	वापस ATA_CBL_PATA40;
पूर्ण

अटल क्रमागत ata_completion_errors pata_macio_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	अचिन्हित पूर्णांक ग_लिखो = (qc->tf.flags & ATA_TFLAG_WRITE);
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	काष्ठा scatterlist *sg;
	काष्ठा dbdma_cmd *table;
	अचिन्हित पूर्णांक si, pi;

	dev_dbgdma(priv->dev, "%s: qc %p flags %lx, write %d dev %d\n",
		   __func__, qc, qc->flags, ग_लिखो, qc->dev->devno);

	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	table = (काष्ठा dbdma_cmd *) priv->dma_table_cpu;

	pi = 0;
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		u32 addr, sg_len, len;

		/* determine अगर physical DMA addr spans 64K boundary.
		 * Note h/w करोesn't support 64-bit, so we unconditionally
		 * truncate dma_addr_t to u32.
		 */
		addr = (u32) sg_dma_address(sg);
		sg_len = sg_dma_len(sg);

		जबतक (sg_len) अणु
			/* table overflow should never happen */
			BUG_ON (pi++ >= MAX_DCMDS);

			len = (sg_len < MAX_DBDMA_SEG) ? sg_len : MAX_DBDMA_SEG;
			table->command = cpu_to_le16(ग_लिखो ? OUTPUT_MORE: INPUT_MORE);
			table->req_count = cpu_to_le16(len);
			table->phy_addr = cpu_to_le32(addr);
			table->cmd_dep = 0;
			table->xfer_status = 0;
			table->res_count = 0;
			addr += len;
			sg_len -= len;
			++table;
		पूर्ण
	पूर्ण

	/* Should never happen according to Tejun */
	BUG_ON(!pi);

	/* Convert the last command to an input/output */
	table--;
	table->command = cpu_to_le16(ग_लिखो ? OUTPUT_LAST: INPUT_LAST);
	table++;

	/* Add the stop command to the end of the list */
	स_रखो(table, 0, माप(काष्ठा dbdma_cmd));
	table->command = cpu_to_le16(DBDMA_STOP);

	dev_dbgdma(priv->dev, "%s: %d DMA list entries\n", __func__, pi);

	वापस AC_ERR_OK;
पूर्ण


अटल व्योम pata_macio_मुक्तze(काष्ठा ata_port *ap)
अणु
	काष्ठा dbdma_regs __iomem *dma_regs = ap->ioaddr.bmdma_addr;

	अगर (dma_regs) अणु
		अचिन्हित पूर्णांक समयout = 1000000;

		/* Make sure DMA controller is stopped */
		ग_लिखोl((RUN|PAUSE|FLUSH|WAKE|DEAD) << 16, &dma_regs->control);
		जबतक (--समयout && (पढ़ोl(&dma_regs->status) & RUN))
			udelay(1);
	पूर्ण

	ata_sff_मुक्तze(ap);
पूर्ण


अटल व्योम pata_macio_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	काष्ठा dbdma_regs __iomem *dma_regs = ap->ioaddr.bmdma_addr;
	पूर्णांक dev = qc->dev->devno;

	dev_dbgdma(priv->dev, "%s: qc %p\n", __func__, qc);

	/* Make sure DMA commands updates are visible */
	ग_लिखोl(priv->dma_table_dma, &dma_regs->cmdptr);

	/* On KeyLargo 66Mhz cell, we need to add 60ns to wrDataSetup on
	 * UDMA पढ़ोs
	 */
	अगर (priv->kind == controller_kl_ata4 &&
	    (priv->treg[dev][0] & TR_66_UDMA_EN)) अणु
		व्योम __iomem *rbase = ap->ioaddr.cmd_addr;
		u32 reg = priv->treg[dev][0];

		अगर (!(qc->tf.flags & ATA_TFLAG_WRITE))
			reg += 0x00800000;
		ग_लिखोl(reg, rbase + IDE_TIMING_CONFIG);
	पूर्ण

	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

अटल व्योम pata_macio_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	काष्ठा dbdma_regs __iomem *dma_regs = ap->ioaddr.bmdma_addr;

	dev_dbgdma(priv->dev, "%s: qc %p\n", __func__, qc);

	ग_लिखोl((RUN << 16) | RUN, &dma_regs->control);
	/* Make sure it माला_लो to the controller right now */
	(व्योम)पढ़ोl(&dma_regs->control);
पूर्ण

अटल व्योम pata_macio_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	काष्ठा dbdma_regs __iomem *dma_regs = ap->ioaddr.bmdma_addr;
	अचिन्हित पूर्णांक समयout = 1000000;

	dev_dbgdma(priv->dev, "%s: qc %p\n", __func__, qc);

	/* Stop the DMA engine and रुको क्रम it to full halt */
	ग_लिखोl (((RUN|WAKE|DEAD) << 16), &dma_regs->control);
	जबतक (--समयout && (पढ़ोl(&dma_regs->status) & RUN))
		udelay(1);
पूर्ण

अटल u8 pata_macio_bmdma_status(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	काष्ठा dbdma_regs __iomem *dma_regs = ap->ioaddr.bmdma_addr;
	u32 dstat, rstat = ATA_DMA_INTR;
	अचिन्हित दीर्घ समयout = 0;

	dstat = पढ़ोl(&dma_regs->status);

	dev_dbgdma(priv->dev, "%s: dstat=%x\n", __func__, dstat);

	/* We have two things to deal with here:
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

	/* First check क्रम errors */
	अगर ((dstat & (RUN|DEAD)) != RUN)
		rstat |= ATA_DMA_ERR;

	/* If ACTIVE is cleared, the STOP command has been hit and
	 * the transfer is complete. If not, we have to flush the
	 * channel.
	 */
	अगर ((dstat & ACTIVE) == 0)
		वापस rstat;

	dev_dbgdma(priv->dev, "%s: DMA still active, flushing...\n", __func__);

	/* If dbdma didn't execute the STOP command yet, the
	 * active bit is still set. We consider that we aren't
	 * sharing पूर्णांकerrupts (which is hopefully the हाल with
	 * those controllers) and so we just try to flush the
	 * channel क्रम pending data in the fअगरo
	 */
	udelay(1);
	ग_लिखोl((FLUSH << 16) | FLUSH, &dma_regs->control);
	क्रम (;;) अणु
		udelay(1);
		dstat = पढ़ोl(&dma_regs->status);
		अगर ((dstat & FLUSH) == 0)
			अवरोध;
		अगर (++समयout > 1000) अणु
			dev_warn(priv->dev, "timeout flushing DMA\n");
			rstat |= ATA_DMA_ERR;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rstat;
पूर्ण

/* port_start is when we allocate the DMA command list */
अटल पूर्णांक pata_macio_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_macio_priv *priv = ap->निजी_data;

	अगर (ap->ioaddr.bmdma_addr == शून्य)
		वापस 0;

	/* Allocate space क्रम the DBDMA commands.
	 *
	 * The +2 is +1 क्रम the stop command and +1 to allow क्रम
	 * aligning the start address to a multiple of 16 bytes.
	 */
	priv->dma_table_cpu =
		dmam_alloc_coherent(priv->dev,
				    (MAX_DCMDS + 2) * माप(काष्ठा dbdma_cmd),
				    &priv->dma_table_dma, GFP_KERNEL);
	अगर (priv->dma_table_cpu == शून्य) अणु
		dev_err(priv->dev, "Unable to allocate DMA command list\n");
		ap->ioaddr.bmdma_addr = शून्य;
		ap->mwdma_mask = 0;
		ap->udma_mask = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pata_macio_irq_clear(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_macio_priv *priv = ap->निजी_data;

	/* Nothing to करो here */

	dev_dbgdma(priv->dev, "%s\n", __func__);
पूर्ण

अटल व्योम pata_macio_reset_hw(काष्ठा pata_macio_priv *priv, पूर्णांक resume)
अणु
	dev_dbg(priv->dev, "Enabling & resetting... \n");

	अगर (priv->mediabay)
		वापस;

	अगर (priv->kind == controller_ohare && !resume) अणु
		/* The code below is having trouble on some ohare machines
		 * (timing related ?). Until I can put my hand on one of these
		 * units, I keep the old way
		 */
		ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, priv->node, 0, 1);
	पूर्ण अन्यथा अणु
		पूर्णांक rc;

 		/* Reset and enable controller */
		rc = ppc_md.feature_call(PMAC_FTR_IDE_RESET,
					 priv->node, priv->aapl_bus_id, 1);
		ppc_md.feature_call(PMAC_FTR_IDE_ENABLE,
				    priv->node, priv->aapl_bus_id, 1);
		msleep(10);
		/* Only bother रुकोing अगर there's a reset control */
		अगर (rc == 0) अणु
			ppc_md.feature_call(PMAC_FTR_IDE_RESET,
					    priv->node, priv->aapl_bus_id, 0);
			msleep(IDE_WAKEUP_DELAY_MS);
		पूर्ण
	पूर्ण

	/* If resuming a PCI device, restore the config space here */
	अगर (priv->pdev && resume) अणु
		पूर्णांक rc;

		pci_restore_state(priv->pdev);
		rc = pcim_enable_device(priv->pdev);
		अगर (rc)
			dev_err(&priv->pdev->dev,
				"Failed to enable device after resume (%d)\n",
				rc);
		अन्यथा
			pci_set_master(priv->pdev);
	पूर्ण

	/* On Kauai, initialize the FCR. We करोn't perform a reset, doesn't really
	 * seem necessary and speeds up the boot process
	 */
	अगर (priv->kauai_fcr)
		ग_लिखोl(KAUAI_FCR_UATA_MAGIC |
		       KAUAI_FCR_UATA_RESET_N |
		       KAUAI_FCR_UATA_ENABLE, priv->kauai_fcr);
पूर्ण

/* Hook the standard slave config to fixup some HW related alignment
 * restrictions
 */
अटल पूर्णांक pata_macio_slave_config(काष्ठा scsi_device *sdev)
अणु
	काष्ठा ata_port *ap = ata_shost_to_port(sdev->host);
	काष्ठा pata_macio_priv *priv = ap->निजी_data;
	काष्ठा ata_device *dev;
	u16 cmd;
	पूर्णांक rc;

	/* First call original */
	rc = ata_scsi_slave_config(sdev);
	अगर (rc)
		वापस rc;

	/* This is lअगरted from sata_nv */
	dev = &ap->link.device[sdev->id];

	/* OHare has issues with non cache aligned DMA on some chipsets */
	अगर (priv->kind == controller_ohare) अणु
		blk_queue_update_dma_alignment(sdev->request_queue, 31);
		blk_queue_update_dma_pad(sdev->request_queue, 31);

		/* Tell the world about it */
		ata_dev_info(dev, "OHare alignment limits applied\n");
		वापस 0;
	पूर्ण

	/* We only have issues with ATAPI */
	अगर (dev->class != ATA_DEV_ATAPI)
		वापस 0;

	/* Shasta and K2 seem to have "issues" with पढ़ोs ... */
	अगर (priv->kind == controller_sh_ata6 || priv->kind == controller_k2_ata6) अणु
		/* Allright these are bad, apply restrictions */
		blk_queue_update_dma_alignment(sdev->request_queue, 15);
		blk_queue_update_dma_pad(sdev->request_queue, 15);

		/* We enable MWI and hack cache line size directly here, this
		 * is specअगरic to this chipset and not normal values, we happen
		 * to somewhat know what we are करोing here (which is basically
		 * to करो the same Apple करोes and pray they did not get it wrong :-)
		 */
		BUG_ON(!priv->pdev);
		pci_ग_लिखो_config_byte(priv->pdev, PCI_CACHE_LINE_SIZE, 0x08);
		pci_पढ़ो_config_word(priv->pdev, PCI_COMMAND, &cmd);
		pci_ग_लिखो_config_word(priv->pdev, PCI_COMMAND,
				      cmd | PCI_COMMAND_INVALIDATE);

		/* Tell the world about it */
		ata_dev_info(dev, "K2/Shasta alignment limits applied\n");
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pata_macio_करो_suspend(काष्ठा pata_macio_priv *priv, pm_message_t mesg)
अणु
	पूर्णांक rc;

	/* First, core libata suspend to करो most of the work */
	rc = ata_host_suspend(priv->host, mesg);
	अगर (rc)
		वापस rc;

	/* Restore to शेष timings */
	pata_macio_शेष_timings(priv);

	/* Mask पूर्णांकerrupt. Not strictly necessary but old driver did
	 * it and I'd rather not change that here */
	disable_irq(priv->irq);

	/* The media bay will handle itself just fine */
	अगर (priv->mediabay)
		वापस 0;

	/* Kauai has bus control FCRs directly here */
	अगर (priv->kauai_fcr) अणु
		u32 fcr = पढ़ोl(priv->kauai_fcr);
		fcr &= ~(KAUAI_FCR_UATA_RESET_N | KAUAI_FCR_UATA_ENABLE);
		ग_लिखोl(fcr, priv->kauai_fcr);
	पूर्ण

	/* For PCI, save state and disable DMA. No need to call
	 * pci_set_घातer_state(), the HW करोesn't करो D states that
	 * way, the platक्रमm code will take care of suspending the
	 * ASIC properly
	 */
	अगर (priv->pdev) अणु
		pci_save_state(priv->pdev);
		pci_disable_device(priv->pdev);
	पूर्ण

	/* Disable the bus on older machines and the cell on kauai */
	ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, priv->node,
			    priv->aapl_bus_id, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pata_macio_करो_resume(काष्ठा pata_macio_priv *priv)
अणु
	/* Reset and re-enable the HW */
	pata_macio_reset_hw(priv, 1);

	/* Sanitize drive timings */
	pata_macio_apply_timings(priv->host->ports[0], 0);

	/* We want our IRQ back ! */
	enable_irq(priv->irq);

	/* Let the libata core take it from there */
	ata_host_resume(priv->host);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा scsi_host_ढाँचा pata_macio_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= MAX_DCMDS,
	/* We may not need that strict one */
	.dma_boundary		= ATA_DMA_BOUNDARY,
	/* Not sure what the real max is but we know it's less than 64K, let's
	 * use 64K minus 256
	 */
	.max_segment_size	= MAX_DBDMA_SEG,
	.slave_configure	= pata_macio_slave_config,
पूर्ण;

अटल काष्ठा ata_port_operations pata_macio_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.मुक्तze			= pata_macio_मुक्तze,
	.set_piomode		= pata_macio_set_timings,
	.set_dmamode		= pata_macio_set_timings,
	.cable_detect		= pata_macio_cable_detect,
	.sff_dev_select		= pata_macio_dev_select,
	.qc_prep		= pata_macio_qc_prep,
	.bmdma_setup		= pata_macio_bmdma_setup,
	.bmdma_start		= pata_macio_bmdma_start,
	.bmdma_stop		= pata_macio_bmdma_stop,
	.bmdma_status		= pata_macio_bmdma_status,
	.port_start		= pata_macio_port_start,
	.sff_irq_clear		= pata_macio_irq_clear,
पूर्ण;

अटल व्योम pata_macio_invariants(काष्ठा pata_macio_priv *priv)
अणु
	स्थिर पूर्णांक *bidp;

	/* Identअगरy the type of controller */
	अगर (of_device_is_compatible(priv->node, "shasta-ata")) अणु
		priv->kind = controller_sh_ata6;
	        priv->timings = pata_macio_shasta_timings;
	पूर्ण अन्यथा अगर (of_device_is_compatible(priv->node, "kauai-ata")) अणु
		priv->kind = controller_un_ata6;
	        priv->timings = pata_macio_kauai_timings;
	पूर्ण अन्यथा अगर (of_device_is_compatible(priv->node, "K2-UATA")) अणु
		priv->kind = controller_k2_ata6;
	        priv->timings = pata_macio_kauai_timings;
	पूर्ण अन्यथा अगर (of_device_is_compatible(priv->node, "keylargo-ata")) अणु
		अगर (of_node_name_eq(priv->node, "ata-4")) अणु
			priv->kind = controller_kl_ata4;
			priv->timings = pata_macio_kl66_timings;
		पूर्ण अन्यथा अणु
			priv->kind = controller_kl_ata3;
			priv->timings = pata_macio_kl33_timings;
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(priv->node, "heathrow-ata")) अणु
		priv->kind = controller_heathrow;
		priv->timings = pata_macio_heathrow_timings;
	पूर्ण अन्यथा अणु
		priv->kind = controller_ohare;
		priv->timings = pata_macio_ohare_timings;
	पूर्ण

	/* XXX FIXME --- setup priv->mediabay here */

	/* Get Apple bus ID (क्रम घड़ी and ASIC control) */
	bidp = of_get_property(priv->node, "AAPL,bus-id", शून्य);
	priv->aapl_bus_id =  bidp ? *bidp : 0;

	/* Fixup missing Apple bus ID in हाल of media-bay */
	अगर (priv->mediabay && !bidp)
		priv->aapl_bus_id = 1;
पूर्ण

अटल व्योम pata_macio_setup_ios(काष्ठा ata_ioports *ioaddr,
				 व्योम __iomem * base, व्योम __iomem * dma)
अणु
	/* cmd_addr is the base of regs क्रम that port */
	ioaddr->cmd_addr	= base;

	/* taskfile रेजिस्टरs */
	ioaddr->data_addr	= base + (ATA_REG_DATA    << 4);
	ioaddr->error_addr	= base + (ATA_REG_ERR     << 4);
	ioaddr->feature_addr	= base + (ATA_REG_FEATURE << 4);
	ioaddr->nsect_addr	= base + (ATA_REG_NSECT   << 4);
	ioaddr->lbal_addr	= base + (ATA_REG_LBAL    << 4);
	ioaddr->lbam_addr	= base + (ATA_REG_LBAM    << 4);
	ioaddr->lbah_addr	= base + (ATA_REG_LBAH    << 4);
	ioaddr->device_addr	= base + (ATA_REG_DEVICE  << 4);
	ioaddr->status_addr	= base + (ATA_REG_STATUS  << 4);
	ioaddr->command_addr	= base + (ATA_REG_CMD     << 4);
	ioaddr->altstatus_addr	= base + 0x160;
	ioaddr->ctl_addr	= base + 0x160;
	ioaddr->bmdma_addr	= dma;
पूर्ण

अटल व्योम pmac_macio_calc_timing_masks(काष्ठा pata_macio_priv *priv,
					 काष्ठा ata_port_info *pinfo)
अणु
	पूर्णांक i = 0;

	pinfo->pio_mask		= 0;
	pinfo->mwdma_mask	= 0;
	pinfo->udma_mask	= 0;

	जबतक (priv->timings[i].mode > 0) अणु
		अचिन्हित पूर्णांक mask = 1U << (priv->timings[i].mode & 0x0f);
		चयन(priv->timings[i].mode & 0xf0) अणु
		हाल 0x00: /* PIO */
			pinfo->pio_mask |= (mask >> 8);
			अवरोध;
		हाल 0x20: /* MWDMA */
			pinfo->mwdma_mask |= mask;
			अवरोध;
		हाल 0x40: /* UDMA */
			pinfo->udma_mask |= mask;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	dev_dbg(priv->dev, "Supported masks: PIO=%lx, MWDMA=%lx, UDMA=%lx\n",
		pinfo->pio_mask, pinfo->mwdma_mask, pinfo->udma_mask);
पूर्ण

अटल पूर्णांक pata_macio_common_init(काष्ठा pata_macio_priv *priv,
				  resource_माप_प्रकार tfregs,
				  resource_माप_प्रकार dmaregs,
				  resource_माप_प्रकार fcregs,
				  अचिन्हित दीर्घ irq)
अणु
	काष्ठा ata_port_info		pinfo;
	स्थिर काष्ठा ata_port_info	*ppi[] = अणु &pinfo, शून्य पूर्ण;
	व्योम __iomem			*dma_regs = शून्य;

	/* Fill up निजीs with various invariants collected from the
	 * device-tree
	 */
	pata_macio_invariants(priv);

	/* Make sure we have sane initial timings in the cache */
	pata_macio_शेष_timings(priv);

	/* Allocate libata host क्रम 1 port */
	स_रखो(&pinfo, 0, माप(काष्ठा ata_port_info));
	pmac_macio_calc_timing_masks(priv, &pinfo);
	pinfo.flags		= ATA_FLAG_SLAVE_POSS;
	pinfo.port_ops		= &pata_macio_ops;
	pinfo.निजी_data	= priv;

	priv->host = ata_host_alloc_pinfo(priv->dev, ppi, 1);
	अगर (priv->host == शून्य) अणु
		dev_err(priv->dev, "Failed to allocate ATA port structure\n");
		वापस -ENOMEM;
	पूर्ण

	/* Setup the निजी data in host too */
	priv->host->निजी_data = priv;

	/* Map base रेजिस्टरs */
	priv->tfregs = devm_ioremap(priv->dev, tfregs, 0x100);
	अगर (priv->tfregs == शून्य) अणु
		dev_err(priv->dev, "Failed to map ATA ports\n");
		वापस -ENOMEM;
	पूर्ण
	priv->host->iomap = &priv->tfregs;

	/* Map DMA regs */
	अगर (dmaregs != 0) अणु
		dma_regs = devm_ioremap(priv->dev, dmaregs,
					माप(काष्ठा dbdma_regs));
		अगर (dma_regs == शून्य)
			dev_warn(priv->dev, "Failed to map ATA DMA registers\n");
	पूर्ण

	/* If chip has local feature control, map those regs too */
	अगर (fcregs != 0) अणु
		priv->kauai_fcr = devm_ioremap(priv->dev, fcregs, 4);
		अगर (priv->kauai_fcr == शून्य) अणु
			dev_err(priv->dev, "Failed to map ATA FCR register\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Setup port data काष्ठाure */
	pata_macio_setup_ios(&priv->host->ports[0]->ioaddr,
			     priv->tfregs, dma_regs);
	priv->host->ports[0]->निजी_data = priv;

	/* hard-reset the controller */
	pata_macio_reset_hw(priv, 0);
	pata_macio_apply_timings(priv->host->ports[0], 0);

	/* Enable bus master अगर necessary */
	अगर (priv->pdev && dma_regs)
		pci_set_master(priv->pdev);

	dev_info(priv->dev, "Activating pata-macio chipset %s, Apple bus ID %d\n",
		 macio_ata_names[priv->kind], priv->aapl_bus_id);

	/* Start it up */
	priv->irq = irq;
	वापस ata_host_activate(priv->host, irq, ata_bmdma_पूर्णांकerrupt, 0,
				 &pata_macio_sht);
पूर्ण

अटल पूर्णांक pata_macio_attach(काष्ठा macio_dev *mdev,
			     स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा pata_macio_priv	*priv;
	resource_माप_प्रकार		tfregs, dmaregs = 0;
	अचिन्हित दीर्घ		irq;
	पूर्णांक			rc;

	/* Check क्रम broken device-trees */
	अगर (macio_resource_count(mdev) == 0) अणु
		dev_err(&mdev->ofdev.dev,
			"No addresses for controller\n");
		वापस -ENXIO;
	पूर्ण

	/* Enable managed resources */
	macio_enable_devres(mdev);

	/* Allocate and init निजी data काष्ठाure */
	priv = devm_kzalloc(&mdev->ofdev.dev,
			    माप(काष्ठा pata_macio_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->node = of_node_get(mdev->ofdev.dev.of_node);
	priv->mdev = mdev;
	priv->dev = &mdev->ofdev.dev;

	/* Request memory resource क्रम taskfile रेजिस्टरs */
	अगर (macio_request_resource(mdev, 0, "pata-macio")) अणु
		dev_err(&mdev->ofdev.dev,
			"Cannot obtain taskfile resource\n");
		वापस -EBUSY;
	पूर्ण
	tfregs = macio_resource_start(mdev, 0);

	/* Request resources क्रम DMA रेजिस्टरs अगर any */
	अगर (macio_resource_count(mdev) >= 2) अणु
		अगर (macio_request_resource(mdev, 1, "pata-macio-dma"))
			dev_err(&mdev->ofdev.dev,
				"Cannot obtain DMA resource\n");
		अन्यथा
			dmaregs = macio_resource_start(mdev, 1);
	पूर्ण

	/*
	 * Fixup missing IRQ क्रम some old implementations with broken
	 * device-trees.
	 *
	 * This is a bit bogus, it should be fixed in the device-tree itself,
	 * via the existing macio fixups, based on the type of पूर्णांकerrupt
	 * controller in the machine. However, I have no test HW क्रम this हाल,
	 * and this trick works well enough on those old machines...
	 */
	अगर (macio_irq_count(mdev) == 0) अणु
		dev_warn(&mdev->ofdev.dev,
			 "No interrupts for controller, using 13\n");
		irq = irq_create_mapping(शून्य, 13);
	पूर्ण अन्यथा
		irq = macio_irq(mdev, 0);

	/* Prevvent media bay callbacks until fully रेजिस्टरed */
	lock_media_bay(priv->mdev->media_bay);

	/* Get रेजिस्टर addresses and call common initialization */
	rc = pata_macio_common_init(priv,
				    tfregs,		/* Taskfile regs */
				    dmaregs,		/* DBDMA regs */
				    0,			/* Feature control */
				    irq);
	unlock_media_bay(priv->mdev->media_bay);

	वापस rc;
पूर्ण

अटल पूर्णांक pata_macio_detach(काष्ठा macio_dev *mdev)
अणु
	काष्ठा ata_host *host = macio_get_drvdata(mdev);
	काष्ठा pata_macio_priv *priv = host->निजी_data;

	lock_media_bay(priv->mdev->media_bay);

	/* Make sure the mediabay callback करोesn't try to access
	 * dead stuff
	 */
	priv->host->निजी_data = शून्य;

	ata_host_detach(host);

	unlock_media_bay(priv->mdev->media_bay);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pata_macio_suspend(काष्ठा macio_dev *mdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = macio_get_drvdata(mdev);

	वापस pata_macio_करो_suspend(host->निजी_data, mesg);
पूर्ण

अटल पूर्णांक pata_macio_resume(काष्ठा macio_dev *mdev)
अणु
	काष्ठा ata_host *host = macio_get_drvdata(mdev);

	वापस pata_macio_करो_resume(host->निजी_data);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PMAC_MEDIABAY
अटल व्योम pata_macio_mb_event(काष्ठा macio_dev* mdev, पूर्णांक mb_state)
अणु
	काष्ठा ata_host *host = macio_get_drvdata(mdev);
	काष्ठा ata_port *ap;
	काष्ठा ata_eh_info *ehi;
	काष्ठा ata_device *dev;
	अचिन्हित दीर्घ flags;

	अगर (!host || !host->निजी_data)
		वापस;
	ap = host->ports[0];
	spin_lock_irqsave(ap->lock, flags);
	ehi = &ap->link.eh_info;
	अगर (mb_state == MB_CD) अणु
		ata_ehi_push_desc(ehi, "mediabay plug");
		ata_ehi_hotplugged(ehi);
		ata_port_मुक्तze(ap);
	पूर्ण अन्यथा अणु
		ata_ehi_push_desc(ehi, "mediabay unplug");
		ata_क्रम_each_dev(dev, &ap->link, ALL)
			dev->flags |= ATA_DFLAG_DETACH;
		ata_port_पात(ap);
	पूर्ण
	spin_unlock_irqrestore(ap->lock, flags);

पूर्ण
#पूर्ण_अगर /* CONFIG_PMAC_MEDIABAY */


अटल पूर्णांक pata_macio_pci_attach(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pata_macio_priv	*priv;
	काष्ठा device_node	*np;
	resource_माप_प्रकार		rbase;

	/* We cannot use a MacIO controller without its OF device node */
	np = pci_device_to_OF_node(pdev);
	अगर (np == शून्य) अणु
		dev_err(&pdev->dev,
			"Cannot find OF device node for controller\n");
		वापस -ENODEV;
	पूर्ण

	/* Check that it can be enabled */
	अगर (pcim_enable_device(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot enable controller PCI device\n");
		वापस -ENXIO;
	पूर्ण

	/* Allocate and init निजी data काष्ठाure */
	priv = devm_kzalloc(&pdev->dev,
			    माप(काष्ठा pata_macio_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->node = of_node_get(np);
	priv->pdev = pdev;
	priv->dev = &pdev->dev;

	/* Get MMIO regions */
	अगर (pci_request_regions(pdev, "pata-macio")) अणु
		dev_err(&pdev->dev,
			"Cannot obtain PCI resources\n");
		वापस -EBUSY;
	पूर्ण

	/* Get रेजिस्टर addresses and call common initialization */
	rbase = pci_resource_start(pdev, 0);
	अगर (pata_macio_common_init(priv,
				   rbase + 0x2000,	/* Taskfile regs */
				   rbase + 0x1000,	/* DBDMA regs */
				   rbase,		/* Feature control */
				   pdev->irq))
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल व्योम pata_macio_pci_detach(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);

	ata_host_detach(host);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pata_macio_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);

	वापस pata_macio_करो_suspend(host->निजी_data, mesg);
पूर्ण

अटल पूर्णांक pata_macio_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);

	वापस pata_macio_करो_resume(host->निजी_data);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा of_device_id pata_macio_match[] =
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
MODULE_DEVICE_TABLE(of, pata_macio_match);

अटल काष्ठा macio_driver pata_macio_driver =
अणु
	.driver = अणु
		.name 		= "pata-macio",
		.owner		= THIS_MODULE,
		.of_match_table	= pata_macio_match,
	पूर्ण,
	.probe		= pata_macio_attach,
	.हटाओ		= pata_macio_detach,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= pata_macio_suspend,
	.resume		= pata_macio_resume,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PMAC_MEDIABAY
	.mediabay_event	= pata_macio_mb_event,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pata_macio_pci_match[] = अणु
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_UNI_N_ATA),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_IPID_ATA100),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_K2_ATA100),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_SH_ATA),	0 पूर्ण,
	अणु PCI_VDEVICE(APPLE, PCI_DEVICE_ID_APPLE_IPID2_ATA),	0 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा pci_driver pata_macio_pci_driver = अणु
	.name		= "pata-pci-macio",
	.id_table	= pata_macio_pci_match,
	.probe		= pata_macio_pci_attach,
	.हटाओ		= pata_macio_pci_detach,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= pata_macio_pci_suspend,
	.resume		= pata_macio_pci_resume,
#पूर्ण_अगर
	.driver = अणु
		.owner		= THIS_MODULE,
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pata_macio_pci_match);


अटल पूर्णांक __init pata_macio_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!machine_is(घातermac))
		वापस -ENODEV;

	rc = pci_रेजिस्टर_driver(&pata_macio_pci_driver);
	अगर (rc)
		वापस rc;
	rc = macio_रेजिस्टर_driver(&pata_macio_driver);
	अगर (rc) अणु
		pci_unरेजिस्टर_driver(&pata_macio_pci_driver);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास pata_macio_निकास(व्योम)
अणु
	macio_unरेजिस्टर_driver(&pata_macio_driver);
	pci_unरेजिस्टर_driver(&pata_macio_pci_driver);
पूर्ण

module_init(pata_macio_init);
module_निकास(pata_macio_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt");
MODULE_DESCRIPTION("Apple MacIO PATA driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
