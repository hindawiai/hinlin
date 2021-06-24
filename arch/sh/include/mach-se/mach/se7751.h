<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_HITACHI_7751SE_H
#घोषणा __ASM_SH_HITACHI_7751SE_H

/*
 * linux/include/यंत्र-sh/hitachi_7751se.h
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * Hitachi SolutionEngine support

 * Modअगरied क्रम 7751 Solution Engine by
 * Ian da Silva and Jeremy Siegel, 2001.
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

#घोषणा PA_DIPSW0	0xb9000000	/* Dip चयन 5,6 */
#घोषणा PA_DIPSW1	0xb9000002	/* Dip चयन 7,8 */
#घोषणा PA_LED		0xba000000	/* LED */
#घोषणा	PA_BCR		0xbb000000	/* FPGA on the MS7751SE01 */

#घोषणा PA_MRSHPC	0xb83fffe0	/* MR-SHPC-01 PCMCIA controller */
#घोषणा PA_MRSHPC_MW1	0xb8400000	/* MR-SHPC-01 memory winकरोw base */
#घोषणा PA_MRSHPC_MW2	0xb8500000	/* MR-SHPC-01 attribute winकरोw base */
#घोषणा PA_MRSHPC_IO	0xb8600000	/* MR-SHPC-01 I/O winकरोw base */
#घोषणा MRSHPC_MODE     (PA_MRSHPC + 4)
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

#घोषणा IRQ_79C973	evt2irq(0x3a0)

व्योम init_7751se_IRQ(व्योम);

#घोषणा __IO_PREFIX	sh7751se
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_HITACHI_7751SE_H */
