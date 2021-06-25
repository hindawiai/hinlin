<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SE7722_H
#घोषणा __ASM_SH_SE7722_H

/*
 * linux/include/यंत्र-sh/se7722.h
 *
 * Copyright (C) 2007  Nobuhiro Iwamatsu
 *
 * Hitachi UL SolutionEngine 7722 Support.
 */
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/addrspace.h>

/* Box specअगरic addresses.  */
#घोषणा SE_AREA0_WIDTH	4		/* Area0: 32bit */
#घोषणा PA_ROM		0xa0000000	/* EPROM */
#घोषणा PA_ROM_SIZE	0x00200000	/* EPROM size 2M byte */
#घोषणा PA_FROM		0xa1000000	/* Flash-ROM */
#घोषणा PA_FROM_SIZE	0x01000000	/* Flash-ROM size 16M byte */
#घोषणा PA_EXT1		0xa4000000
#घोषणा PA_EXT1_SIZE	0x04000000
#घोषणा PA_SDRAM	0xaC000000	/* DDR-SDRAM(Area3) 64MB */
#घोषणा PA_SDRAM_SIZE	0x04000000

#घोषणा PA_EXT4		0xb0000000
#घोषणा PA_EXT4_SIZE	0x04000000

#घोषणा PA_PERIPHERAL	0xB0000000

#घोषणा PA_PCIC         PA_PERIPHERAL		/* MR-SHPC-01 PCMCIA */
#घोषणा PA_MRSHPC       (PA_PERIPHERAL + 0x003fffe0)    /* MR-SHPC-01 PCMCIA controller */
#घोषणा PA_MRSHPC_MW1   (PA_PERIPHERAL + 0x00400000)    /* MR-SHPC-01 memory winकरोw base */
#घोषणा PA_MRSHPC_MW2   (PA_PERIPHERAL + 0x00500000)    /* MR-SHPC-01 attribute winकरोw base */
#घोषणा PA_MRSHPC_IO    (PA_PERIPHERAL + 0x00600000)    /* MR-SHPC-01 I/O winकरोw base */
#घोषणा MRSHPC_OPTION   (PA_MRSHPC + 6)
#घोषणा MRSHPC_CSR      (PA_MRSHPC + 8)
#घोषणा MRSHPC_ISR      (PA_MRSHPC + 10)
#घोषणा MRSHPC_ICR      (PA_MRSHPC + 12)
#घोषणा MRSHPC_CPWCR    (PA_MRSHPC + 14)
#घोषणा MRSHPC_MW0CR1   (PA_MRSHPC + 16)
#घोषणा MRSHPC_MW1CR1   (PA_MRSHPC + 18)
#घोषणा MRSHPC_IOWCR1   (PA_MRSHPC + 20)
#घोषणा MRSHPC_MW0CR2   (PA_MRSHPC + 22)
#घोषणा MRSHPC_MW1CR2   (PA_MRSHPC + 24)
#घोषणा MRSHPC_IOWCR2   (PA_MRSHPC + 26)
#घोषणा MRSHPC_CDCR     (PA_MRSHPC + 28)
#घोषणा MRSHPC_PCIC_INFO (PA_MRSHPC + 30)

#घोषणा PA_LED		(PA_PERIPHERAL + 0x00800000)	/* 8bit LED */
#घोषणा PA_FPGA		(PA_PERIPHERAL + 0x01800000)	/* FPGA base address */

#घोषणा PA_LAN		(PA_AREA6_IO + 0)		/* SMC LAN91C111 */
/* GPIO */
#घोषणा FPGA_IN         0xb1840000UL
#घोषणा FPGA_OUT        0xb1840004UL

#घोषणा PORT_PECR       0xA4050108UL
#घोषणा PORT_PJCR       0xA4050110UL
#घोषणा PORT_PSELD      0xA4050154UL
#घोषणा PORT_PSELB      0xA4050150UL

#घोषणा PORT_PSELC      0xA4050152UL
#घोषणा PORT_PKCR       0xA4050112UL
#घोषणा PORT_PHCR       0xA405010EUL
#घोषणा PORT_PLCR       0xA4050114UL
#घोषणा PORT_PMCR       0xA4050116UL
#घोषणा PORT_PRCR       0xA405011CUL
#घोषणा PORT_PXCR       0xA4050148UL
#घोषणा PORT_PSELA      0xA405014EUL
#घोषणा PORT_PYCR       0xA405014AUL
#घोषणा PORT_PZCR       0xA405014CUL
#घोषणा PORT_HIZCRA     0xA4050158UL
#घोषणा PORT_HIZCRC     0xA405015CUL

/* IRQ */
#घोषणा IRQ0_IRQ        evt2irq(0x600)
#घोषणा IRQ1_IRQ        evt2irq(0x620)

#घोषणा SE7722_FPGA_IRQ_USB	0 /* IRQ0 */
#घोषणा SE7722_FPGA_IRQ_SMC	1 /* IRQ0 */
#घोषणा SE7722_FPGA_IRQ_MRSHPC0	2 /* IRQ1 */
#घोषणा SE7722_FPGA_IRQ_MRSHPC1	3 /* IRQ1 */
#घोषणा SE7722_FPGA_IRQ_MRSHPC2	4 /* IRQ1 */
#घोषणा SE7722_FPGA_IRQ_MRSHPC3	5 /* IRQ1 */
#घोषणा SE7722_FPGA_IRQ_NR	6

काष्ठा irq_करोमुख्य;

/* arch/sh/boards/se/7722/irq.c */
बाह्य काष्ठा irq_करोमुख्य *se7722_irq_करोमुख्य;

व्योम init_se7722_IRQ(व्योम);

#घोषणा __IO_PREFIX		se7722
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_SE7722_H */
