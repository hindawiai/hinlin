<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_HD64461
#घोषणा __ASM_SH_HD64461
/*
 *	Copyright (C) 2007 Kristoffer Ericson <Kristoffer.Ericson@gmail.com>
 *	Copyright (C) 2004 Paul Mundt
 *	Copyright (C) 2000 YAEGASHI Takeshi
 *
 *		Hitachi HD64461 companion chip support
 *	(please note manual reference 0x10000000 = 0xb0000000)
 */

/* Constants क्रम PCMCIA mappings */
#घोषणा	HD64461_PCC_WINDOW	0x01000000

/* Area 6 - Slot 0 - memory and/or IO card */
#घोषणा HD64461_IOBASE		0xb0000000
#घोषणा HD64461_IO_OFFSET(x)	(HD64461_IOBASE + (x))
#घोषणा	HD64461_PCC0_BASE	HD64461_IO_OFFSET(0x8000000)
#घोषणा	HD64461_PCC0_ATTR	(HD64461_PCC0_BASE)				/* 0xb80000000 */
#घोषणा	HD64461_PCC0_COMM	(HD64461_PCC0_BASE+HD64461_PCC_WINDOW)		/* 0xb90000000 */
#घोषणा	HD64461_PCC0_IO		(HD64461_PCC0_BASE+2*HD64461_PCC_WINDOW)	/* 0xba0000000 */

/* Area 5 - Slot 1 - memory card only */
#घोषणा	HD64461_PCC1_BASE	HD64461_IO_OFFSET(0x4000000)
#घोषणा	HD64461_PCC1_ATTR	(HD64461_PCC1_BASE)				/* 0xb4000000 */
#घोषणा	HD64461_PCC1_COMM	(HD64461_PCC1_BASE+HD64461_PCC_WINDOW)		/* 0xb5000000 */

/* Standby Control Register क्रम HD64461 */
#घोषणा	HD64461_STBCR			HD64461_IO_OFFSET(0x00000000)
#घोषणा	HD64461_STBCR_CKIO_STBY		0x2000
#घोषणा	HD64461_STBCR_SAFECKE_IST	0x1000
#घोषणा	HD64461_STBCR_SLCKE_IST		0x0800
#घोषणा	HD64461_STBCR_SAFECKE_OST	0x0400
#घोषणा	HD64461_STBCR_SLCKE_OST		0x0200
#घोषणा	HD64461_STBCR_SMIAST		0x0100
#घोषणा	HD64461_STBCR_SLCDST		0x0080
#घोषणा	HD64461_STBCR_SPC0ST		0x0040
#घोषणा	HD64461_STBCR_SPC1ST		0x0020
#घोषणा	HD64461_STBCR_SAFEST		0x0010
#घोषणा	HD64461_STBCR_STM0ST		0x0008
#घोषणा	HD64461_STBCR_STM1ST		0x0004
#घोषणा	HD64461_STBCR_SIRST		0x0002
#घोषणा	HD64461_STBCR_SURTST		0x0001

/* System Configuration Register */
#घोषणा	HD64461_SYSCR		HD64461_IO_OFFSET(0x02)

/* CPU Data Bus Control Register */
#घोषणा	HD64461_SCPUCR		HD64461_IO_OFFSET(0x04)

/* Base Address Register */
#घोषणा	HD64461_LCDCBAR		HD64461_IO_OFFSET(0x1000)

/* Line increment address */
#घोषणा	HD64461_LCDCLOR		HD64461_IO_OFFSET(0x1002)

/* Controls LCD controller */
#घोषणा	HD64461_LCDCCR		HD64461_IO_OFFSET(0x1004)

/* LCCDR control bits */
#घोषणा	HD64461_LCDCCR_STBACK	0x0400	/* Standby Back */
#घोषणा	HD64461_LCDCCR_STREQ	0x0100	/* Standby Request */
#घोषणा	HD64461_LCDCCR_MOFF	0x0080	/* Memory Off */
#घोषणा	HD64461_LCDCCR_REFSEL	0x0040	/* Refresh Select */
#घोषणा	HD64461_LCDCCR_EPON	0x0020	/* End Power On */
#घोषणा	HD64461_LCDCCR_SPON	0x0010	/* Start Power On */

/* Controls LCD (1) */
#घोषणा	HD64461_LDR1		HD64461_IO_OFFSET(0x1010)
#घोषणा	HD64461_LDR1_DON	0x01	/* Display On */
#घोषणा	HD64461_LDR1_DINV	0x80	/* Display Invert */

/* Controls LCD (2) */
#घोषणा	HD64461_LDR2		HD64461_IO_OFFSET(0x1012)
#घोषणा	HD64461_LDHNCR		HD64461_IO_OFFSET(0x1014)	/* Number of horizontal अक्षरacters */
#घोषणा	HD64461_LDHNSR		HD64461_IO_OFFSET(0x1016)	/* Specअगरy output start position + width of CL1 */
#घोषणा	HD64461_LDVNTR		HD64461_IO_OFFSET(0x1018)	/* Specअगरy total vertical lines */
#घोषणा	HD64461_LDVNDR		HD64461_IO_OFFSET(0x101a)	/* specअगरy number of display vertical lines */
#घोषणा	HD64461_LDVSPR		HD64461_IO_OFFSET(0x101c)	/* specअगरy vertical synchronization pos and AC nr */

/* Controls LCD (3) */
#घोषणा	HD64461_LDR3		HD64461_IO_OFFSET(0x101e)

/* Palette Registers */
#घोषणा	HD64461_CPTWAR		HD64461_IO_OFFSET(0x1030)	/* Color Palette Write Address Register */
#घोषणा	HD64461_CPTWDR		HD64461_IO_OFFSET(0x1032)	/* Color Palette Write Data Register */
#घोषणा	HD64461_CPTRAR		HD64461_IO_OFFSET(0x1034)	/* Color Palette Read Address Register */
#घोषणा	HD64461_CPTRDR		HD64461_IO_OFFSET(0x1036)	/* Color Palette Read Data Register */

#घोषणा	HD64461_GRDOR		HD64461_IO_OFFSET(0x1040)	/* Display Resolution Offset Register */
#घोषणा	HD64461_GRSCR		HD64461_IO_OFFSET(0x1042)	/* Solid Color Register */
#घोषणा	HD64461_GRCFGR		HD64461_IO_OFFSET(0x1044)	/* Accelerator Configuration Register */

#घोषणा	HD64461_GRCFGR_ACCSTATUS	0x10	/* Accelerator Status */
#घोषणा	HD64461_GRCFGR_ACCRESET		0x08	/* Accelerator Reset */
#घोषणा	HD64461_GRCFGR_ACCSTART_BITBLT	0x06	/* Accelerator Start BITBLT */
#घोषणा	HD64461_GRCFGR_ACCSTART_LINE	0x04	/* Accelerator Start Line Drawing */
#घोषणा	HD64461_GRCFGR_COLORDEPTH16	0x01	/* Sets Colordepth 16 क्रम Accelerator */
#घोषणा	HD64461_GRCFGR_COLORDEPTH8	0x01	/* Sets Colordepth 8 क्रम Accelerator */

/* Line Drawing Registers */
#घोषणा	HD64461_LNSARH		HD64461_IO_OFFSET(0x1046)	/* Line Start Address Register (H) */
#घोषणा	HD64461_LNSARL		HD64461_IO_OFFSET(0x1048)	/* Line Start Address Register (L) */
#घोषणा	HD64461_LNAXLR		HD64461_IO_OFFSET(0x104a)	/* Axis Pixel Length Register */
#घोषणा	HD64461_LNDGR		HD64461_IO_OFFSET(0x104c)	/* Diagonal Register */
#घोषणा	HD64461_LNAXR		HD64461_IO_OFFSET(0x104e)	/* Axial Register */
#घोषणा	HD64461_LNERTR		HD64461_IO_OFFSET(0x1050)	/* Start Error Term Register */
#घोषणा	HD64461_LNMDR		HD64461_IO_OFFSET(0x1052)	/* Line Mode Register */

/* BitBLT Registers */
#घोषणा	HD64461_BBTSSARH	HD64461_IO_OFFSET(0x1054)	/* Source Start Address Register (H) */
#घोषणा	HD64461_BBTSSARL	HD64461_IO_OFFSET(0x1056)	/* Source Start Address Register (L) */
#घोषणा	HD64461_BBTDSARH	HD64461_IO_OFFSET(0x1058)	/* Destination Start Address Register (H) */
#घोषणा	HD64461_BBTDSARL	HD64461_IO_OFFSET(0x105a)	/* Destination Start Address Register (L) */
#घोषणा	HD64461_BBTDWR		HD64461_IO_OFFSET(0x105c)	/* Destination Block Width Register */
#घोषणा	HD64461_BBTDHR		HD64461_IO_OFFSET(0x105e)	/* Destination Block Height Register */
#घोषणा	HD64461_BBTPARH		HD64461_IO_OFFSET(0x1060)	/* Pattern Start Address Register (H) */
#घोषणा	HD64461_BBTPARL		HD64461_IO_OFFSET(0x1062)	/* Pattern Start Address Register (L) */
#घोषणा	HD64461_BBTMARH		HD64461_IO_OFFSET(0x1064)	/* Mask Start Address Register (H) */
#घोषणा	HD64461_BBTMARL		HD64461_IO_OFFSET(0x1066)	/* Mask Start Address Register (L) */
#घोषणा	HD64461_BBTROPR		HD64461_IO_OFFSET(0x1068)	/* ROP Register */
#घोषणा	HD64461_BBTMDR		HD64461_IO_OFFSET(0x106a)	/* BitBLT Mode Register */

/* PC Card Controller Registers */
/* Maps to Physical Area 6 */
#घोषणा	HD64461_PCC0ISR		HD64461_IO_OFFSET(0x2000)	/* socket 0 पूर्णांकerface status */
#घोषणा	HD64461_PCC0GCR		HD64461_IO_OFFSET(0x2002)	/* socket 0 general control */
#घोषणा	HD64461_PCC0CSCR	HD64461_IO_OFFSET(0x2004)	/* socket 0 card status change */
#घोषणा	HD64461_PCC0CSCIER	HD64461_IO_OFFSET(0x2006)	/* socket 0 card status change पूर्णांकerrupt enable */
#घोषणा	HD64461_PCC0SCR		HD64461_IO_OFFSET(0x2008)	/* socket 0 software control */
/* Maps to Physical Area 5 */
#घोषणा	HD64461_PCC1ISR		HD64461_IO_OFFSET(0x2010)	/* socket 1 पूर्णांकerface status */
#घोषणा	HD64461_PCC1GCR		HD64461_IO_OFFSET(0x2012)	/* socket 1 general control */
#घोषणा	HD64461_PCC1CSCR	HD64461_IO_OFFSET(0x2014)	/* socket 1 card status change */
#घोषणा	HD64461_PCC1CSCIER	HD64461_IO_OFFSET(0x2016)	/* socket 1 card status change पूर्णांकerrupt enable */
#घोषणा	HD64461_PCC1SCR		HD64461_IO_OFFSET(0x2018)	/* socket 1 software control */

/* PCC Interface Status Register */
#घोषणा	HD64461_PCCISR_READY		0x80	/* card पढ़ोy */
#घोषणा	HD64461_PCCISR_MWP		0x40	/* card ग_लिखो-रक्षित */
#घोषणा	HD64461_PCCISR_VS2		0x20	/* voltage select pin 2 */
#घोषणा	HD64461_PCCISR_VS1		0x10	/* voltage select pin 1 */
#घोषणा	HD64461_PCCISR_CD2		0x08	/* card detect 2 */
#घोषणा	HD64461_PCCISR_CD1		0x04	/* card detect 1 */
#घोषणा	HD64461_PCCISR_BVD2		0x02	/* battery 1 */
#घोषणा	HD64461_PCCISR_BVD1		0x01	/* battery 1 */

#घोषणा	HD64461_PCCISR_PCD_MASK		0x0c	/* card detect */
#घोषणा	HD64461_PCCISR_BVD_MASK		0x03	/* battery voltage */
#घोषणा	HD64461_PCCISR_BVD_BATGOOD	0x03	/* battery good */
#घोषणा	HD64461_PCCISR_BVD_BATWARN	0x01	/* battery low warning */
#घोषणा	HD64461_PCCISR_BVD_BATDEAD1	0x02	/* battery dead */
#घोषणा	HD64461_PCCISR_BVD_BATDEAD2	0x00	/* battery dead */

/* PCC General Control Register */
#घोषणा	HD64461_PCCGCR_DRVE		0x80	/* output drive */
#घोषणा	HD64461_PCCGCR_PCCR		0x40	/* PC card reset */
#घोषणा	HD64461_PCCGCR_PCCT		0x20	/* PC card type, 1=IO&mem, 0=mem */
#घोषणा	HD64461_PCCGCR_VCC0		0x10	/* voltage control pin VCC0SEL0 */
#घोषणा	HD64461_PCCGCR_PMMOD		0x08	/* memory mode */
#घोषणा	HD64461_PCCGCR_PA25		0x04	/* pin A25 */
#घोषणा	HD64461_PCCGCR_PA24		0x02	/* pin A24 */
#घोषणा	HD64461_PCCGCR_REG		0x01	/* pin PCC0REG# */

/* PCC Card Status Change Register */
#घोषणा	HD64461_PCCCSCR_SCDI		0x80	/* sw card detect पूर्णांकr */
#घोषणा	HD64461_PCCCSCR_SRV1		0x40	/* reserved */
#घोषणा	HD64461_PCCCSCR_IREQ		0x20	/* IREQ पूर्णांकr req */
#घोषणा	HD64461_PCCCSCR_SC		0x10	/* STSCHG (status change) pin */
#घोषणा	HD64461_PCCCSCR_CDC		0x08	/* CD (card detect) change */
#घोषणा	HD64461_PCCCSCR_RC		0x04	/* READY change */
#घोषणा	HD64461_PCCCSCR_BW		0x02	/* battery warning change */
#घोषणा	HD64461_PCCCSCR_BD		0x01	/* battery dead change */

/* PCC Card Status Change Interrupt Enable Register */
#घोषणा	HD64461_PCCCSCIER_CRE		0x80	/* change reset enable */
#घोषणा	HD64461_PCCCSCIER_IREQE_MASK	0x60	/* IREQ enable */
#घोषणा	HD64461_PCCCSCIER_IREQE_DISABLED 0x00	/* IREQ disabled */
#घोषणा	HD64461_PCCCSCIER_IREQE_LEVEL	0x20	/* IREQ level-triggered */
#घोषणा	HD64461_PCCCSCIER_IREQE_FALLING	0x40	/* IREQ falling-edge-trig */
#घोषणा	HD64461_PCCCSCIER_IREQE_RISING	0x60	/* IREQ rising-edge-trig */

#घोषणा	HD64461_PCCCSCIER_SCE		0x10	/* status change enable */
#घोषणा	HD64461_PCCCSCIER_CDE		0x08	/* card detect change enable */
#घोषणा	HD64461_PCCCSCIER_RE		0x04	/* पढ़ोy change enable */
#घोषणा	HD64461_PCCCSCIER_BWE		0x02	/* battery warn change enable */
#घोषणा	HD64461_PCCCSCIER_BDE		0x01	/* battery dead change enable*/

/* PCC Software Control Register */
#घोषणा	HD64461_PCCSCR_VCC1		0x02	/* voltage control pin 1 */
#घोषणा	HD64461_PCCSCR_SWP		0x01	/* ग_लिखो protect */

/* PCC0 Output Pins Control Register */
#घोषणा	HD64461_P0OCR		HD64461_IO_OFFSET(0x202a)

/* PCC1 Output Pins Control Register */
#घोषणा	HD64461_P1OCR		HD64461_IO_OFFSET(0x202c)

/* PC Card General Control Register */
#घोषणा	HD64461_PGCR		HD64461_IO_OFFSET(0x202e)

/* Port Control Registers */
#घोषणा	HD64461_GPACR		HD64461_IO_OFFSET(0x4000)	/* Port A - Handles IRDA/TIMER */
#घोषणा	HD64461_GPBCR		HD64461_IO_OFFSET(0x4002)	/* Port B - Handles UART */
#घोषणा	HD64461_GPCCR		HD64461_IO_OFFSET(0x4004)	/* Port C - Handles PCMCIA 1 */
#घोषणा	HD64461_GPDCR		HD64461_IO_OFFSET(0x4006)	/* Port D - Handles PCMCIA 1 */

/* Port Control Data Registers */
#घोषणा	HD64461_GPADR		HD64461_IO_OFFSET(0x4010)	/* A */
#घोषणा	HD64461_GPBDR		HD64461_IO_OFFSET(0x4012)	/* B */
#घोषणा	HD64461_GPCDR		HD64461_IO_OFFSET(0x4014)	/* C */
#घोषणा	HD64461_GPDDR		HD64461_IO_OFFSET(0x4016)	/* D */

/* Interrupt Control Registers */
#घोषणा	HD64461_GPAICR		HD64461_IO_OFFSET(0x4020)	/* A */
#घोषणा	HD64461_GPBICR		HD64461_IO_OFFSET(0x4022)	/* B */
#घोषणा	HD64461_GPCICR		HD64461_IO_OFFSET(0x4024)	/* C */
#घोषणा	HD64461_GPDICR		HD64461_IO_OFFSET(0x4026)	/* D */

/* Interrupt Status Registers */
#घोषणा	HD64461_GPAISR		HD64461_IO_OFFSET(0x4040)	/* A */
#घोषणा	HD64461_GPBISR		HD64461_IO_OFFSET(0x4042)	/* B */
#घोषणा	HD64461_GPCISR		HD64461_IO_OFFSET(0x4044)	/* C */
#घोषणा	HD64461_GPDISR		HD64461_IO_OFFSET(0x4046)	/* D */

/* Interrupt Request Register & Interrupt Mask Register */
#घोषणा	HD64461_NIRR		HD64461_IO_OFFSET(0x5000)
#घोषणा	HD64461_NIMR		HD64461_IO_OFFSET(0x5002)

#घोषणा	HD64461_IRQBASE		OFFCHIP_IRQ_BASE
#घोषणा	OFFCHIP_IRQ_BASE	64
#घोषणा	HD64461_IRQ_NUM		16

#घोषणा	HD64461_IRQ_UART	(HD64461_IRQBASE+5)
#घोषणा	HD64461_IRQ_IRDA	(HD64461_IRQBASE+6)
#घोषणा	HD64461_IRQ_TMU1	(HD64461_IRQBASE+9)
#घोषणा	HD64461_IRQ_TMU0	(HD64461_IRQBASE+10)
#घोषणा	HD64461_IRQ_GPIO	(HD64461_IRQBASE+11)
#घोषणा	HD64461_IRQ_AFE		(HD64461_IRQBASE+12)
#घोषणा	HD64461_IRQ_PCC1	(HD64461_IRQBASE+13)
#घोषणा	HD64461_IRQ_PCC0	(HD64461_IRQBASE+14)

#घोषणा __IO_PREFIX	hd64461
#समावेश <यंत्र/io_generic.h>

/* arch/sh/cchips/hd6446x/hd64461/setup.c */
व्योम hd64461_रेजिस्टर_irq_demux(पूर्णांक irq,
				पूर्णांक (*demux) (पूर्णांक irq, व्योम *dev), व्योम *dev);
व्योम hd64461_unरेजिस्टर_irq_demux(पूर्णांक irq);

#पूर्ण_अगर
