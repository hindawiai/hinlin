<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_RENESAS_RTS7751R2D_H
#घोषणा __ASM_SH_RENESAS_RTS7751R2D_H

/*
 * linux/include/यंत्र-sh/renesas_rts7751r2d.h
 *
 * Copyright (C) 2000  Atom Create Engineering Co., Ltd.
 *
 * Renesas Technology Sales RTS7751R2D support
 */

/* Board specअगरic addresses.  */

#घोषणा PA_BCR		0xa4000000	/* FPGA */
#घोषणा PA_IRLMON	0xa4000002	/* Interrupt Status control */
#घोषणा PA_CFCTL	0xa4000004	/* CF Timing control */
#घोषणा PA_CFPOW	0xa4000006	/* CF Power control */
#घोषणा PA_DISPCTL	0xa4000008	/* Display Timing control */
#घोषणा PA_SDMPOW	0xa400000a	/* SD Power control */
#घोषणा PA_RTCCE	0xa400000c	/* RTC(9701) Enable control */
#घोषणा PA_PCICD	0xa400000e	/* PCI Extension detect control */
#घोषणा PA_VOYAGERRTS	0xa4000020	/* VOYAGER Reset control */

#घोषणा PA_R2D1_AXRST		0xa4000022	/* AX_LAN Reset control */
#घोषणा PA_R2D1_CFRST		0xa4000024	/* CF Reset control */
#घोषणा PA_R2D1_ADMRTS		0xa4000026	/* SD Reset control */
#घोषणा PA_R2D1_EXTRST		0xa4000028	/* Extension Reset control */
#घोषणा PA_R2D1_CFCDINTCLR	0xa400002a	/* CF Insert Interrupt clear */

#घोषणा PA_R2DPLUS_CFRST	0xa4000022	/* CF Reset control */
#घोषणा PA_R2DPLUS_ADMRTS	0xa4000024	/* SD Reset control */
#घोषणा PA_R2DPLUS_EXTRST	0xa4000026	/* Extension Reset control */
#घोषणा PA_R2DPLUS_CFCDINTCLR	0xa4000028	/* CF Insert Interrupt clear */
#घोषणा PA_R2DPLUS_KEYCTLCLR	0xa400002a	/* Key Interrupt clear */

#घोषणा PA_POWOFF	0xa4000030	/* Board Power OFF control */
#घोषणा PA_VERREG	0xa4000032	/* FPGA Version Register */
#घोषणा PA_INPORT	0xa4000034	/* KEY Input Port control */
#घोषणा PA_OUTPORT	0xa4000036	/* LED control */
#घोषणा PA_BVERREG	0xa4000038	/* Board Revision Register */

#घोषणा PA_AX88796L	0xaa000400	/* AX88796L Area */
#घोषणा PA_VOYAGER	0xab000000	/* VOYAGER GX Area */
#घोषणा PA_IDE_OFFSET	0x1f0		/* CF IDE Offset */
#घोषणा AX88796L_IO_BASE	0x1000	/* AX88796L IO Base Address */

#घोषणा IRLCNTR1	(PA_BCR + 0)	/* Interrupt Control Register1 */

#घोषणा R2D_FPGA_IRQ_BASE	100

#घोषणा IRQ_VOYAGER		(R2D_FPGA_IRQ_BASE + 0)
#घोषणा IRQ_EXT			(R2D_FPGA_IRQ_BASE + 1)
#घोषणा IRQ_TP			(R2D_FPGA_IRQ_BASE + 2)
#घोषणा IRQ_RTC_T		(R2D_FPGA_IRQ_BASE + 3)
#घोषणा IRQ_RTC_A		(R2D_FPGA_IRQ_BASE + 4)
#घोषणा IRQ_SDCARD		(R2D_FPGA_IRQ_BASE + 5)
#घोषणा IRQ_CF_CD		(R2D_FPGA_IRQ_BASE + 6)
#घोषणा IRQ_CF_IDE		(R2D_FPGA_IRQ_BASE + 7)
#घोषणा IRQ_AX88796		(R2D_FPGA_IRQ_BASE + 8)
#घोषणा IRQ_KEY			(R2D_FPGA_IRQ_BASE + 9)
#घोषणा IRQ_PCI_INTA		(R2D_FPGA_IRQ_BASE + 10)
#घोषणा IRQ_PCI_INTB		(R2D_FPGA_IRQ_BASE + 11)
#घोषणा IRQ_PCI_INTC		(R2D_FPGA_IRQ_BASE + 12)
#घोषणा IRQ_PCI_INTD		(R2D_FPGA_IRQ_BASE + 13)

/* arch/sh/boards/renesas/rts7751r2d/irq.c */
व्योम init_rts7751r2d_IRQ(व्योम);
पूर्णांक rts7751r2d_irq_demux(पूर्णांक);

#पूर्ण_अगर  /* __ASM_SH_RENESAS_RTS7751R2D */
