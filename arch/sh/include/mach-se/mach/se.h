<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_HITACHI_SE_H
#घोषणा __ASM_SH_HITACHI_SE_H

/*
 * linux/include/यंत्र-sh/hitachi_se.h
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine support
 */
#समावेश <linux/sh_पूर्णांकc.h>

/* Box specअगरic addresses.  */

#घोषणा PA_ROM		0x00000000	/* EPROM */
#घोषणा PA_ROM_SIZE	0x00400000	/* EPROM size 4M byte */
#घोषणा PA_FROM		0x01000000	/* EPROM */
#घोषणा PA_FROM_SIZE	0x00400000	/* EPROM size 4M byte */
#घोषणा PA_EXT1		0x04000000
#घोषणा PA_EXT1_SIZE	0x04000000
#घोषणा PA_EXT2		0x08000000
#घोषणा PA_EXT2_SIZE	0x04000000
#घोषणा PA_SDRAM	0x0c000000
#घोषणा PA_SDRAM_SIZE	0x04000000

#घोषणा PA_EXT4		0x12000000
#घोषणा PA_EXT4_SIZE	0x02000000
#घोषणा PA_EXT5		0x14000000
#घोषणा PA_EXT5_SIZE	0x04000000
#घोषणा PA_PCIC		0x18000000	/* MR-SHPC-01 PCMCIA */

#घोषणा PA_83902	0xb0000000	/* DP83902A */
#घोषणा PA_83902_IF	0xb0040000	/* DP83902A remote io port */
#घोषणा PA_83902_RST	0xb0080000	/* DP83902A reset port */

#घोषणा PA_SUPERIO	0xb0400000	/* SMC37C935A super io chip */
#घोषणा PA_DIPSW0	0xb0800000	/* Dip चयन 5,6 */
#घोषणा PA_DIPSW1	0xb0800002	/* Dip चयन 7,8 */
#घोषणा PA_LED		0xb0c00000	/* LED */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7705)
#घोषणा PA_BCR		0xb0e00000
#अन्यथा
#घोषणा PA_BCR		0xb1400000	/* FPGA */
#पूर्ण_अगर

#घोषणा PA_MRSHPC	0xb83fffe0	/* MR-SHPC-01 PCMCIA controller */
#घोषणा PA_MRSHPC_MW1	0xb8400000	/* MR-SHPC-01 memory winकरोw base */
#घोषणा PA_MRSHPC_MW2	0xb8500000	/* MR-SHPC-01 attribute winकरोw base */
#घोषणा PA_MRSHPC_IO	0xb8600000	/* MR-SHPC-01 I/O winकरोw base */
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

#घोषणा BCR_ILCRA	(PA_BCR + 0)
#घोषणा BCR_ILCRB	(PA_BCR + 2)
#घोषणा BCR_ILCRC	(PA_BCR + 4)
#घोषणा BCR_ILCRD	(PA_BCR + 6)
#घोषणा BCR_ILCRE	(PA_BCR + 8)
#घोषणा BCR_ILCRF	(PA_BCR + 10)
#घोषणा BCR_ILCRG	(PA_BCR + 12)

#अगर defined(CONFIG_CPU_SUBTYPE_SH7709)
#घोषणा INTC_IRR0       0xa4000004UL
#घोषणा INTC_IRR1       0xa4000006UL
#घोषणा INTC_IRR2       0xa4000008UL

#घोषणा INTC_ICR0       0xfffffee0UL
#घोषणा INTC_ICR1       0xa4000010UL
#घोषणा INTC_ICR2       0xa4000012UL
#घोषणा INTC_INTER      0xa4000014UL

#घोषणा INTC_IPRC       0xa4000016UL
#घोषणा INTC_IPRD       0xa4000018UL
#घोषणा INTC_IPRE       0xa400001aUL

#घोषणा IRQ0_IRQ        evt2irq(0x600)
#घोषणा IRQ1_IRQ        evt2irq(0x620)
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_SUBTYPE_SH7705)
#घोषणा IRQ_STNIC	evt2irq(0x380)
#घोषणा IRQ_CFCARD	evt2irq(0x3c0)
#अन्यथा
#घोषणा IRQ_STNIC	evt2irq(0x340)
#घोषणा IRQ_CFCARD	evt2irq(0x2e0)
#पूर्ण_अगर

/* SH Ether support (SH7710/SH7712) */
/* Base address */
#घोषणा SH_ETH0_BASE 0xA7000000
#घोषणा SH_ETH1_BASE 0xA7000400
#घोषणा SH_TSU_BASE  0xA7000800
/* PHY ID */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7710)
# define PHY_ID 0x00
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7712)
# define PHY_ID 0x01
#पूर्ण_अगर
/* Ether IRQ */
#घोषणा SH_ETH0_IRQ	evt2irq(0xc00)
#घोषणा SH_ETH1_IRQ	evt2irq(0xc20)
#घोषणा SH_TSU_IRQ	evt2irq(0xc40)

व्योम init_se_IRQ(व्योम);

#घोषणा __IO_PREFIX	se
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_HITACHI_SE_H */
