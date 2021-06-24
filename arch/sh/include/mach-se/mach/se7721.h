<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 *
 * Hitachi UL SolutionEngine 7721 Support.
 */

#अगर_अघोषित __ASM_SH_SE7721_H
#घोषणा __ASM_SH_SE7721_H

#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/addrspace.h>

/* Box specअगरic addresses. */
#घोषणा SE_AREA0_WIDTH	2		/* Area0: 32bit */
#घोषणा PA_ROM		0xa0000000	/* EPROM */
#घोषणा PA_ROM_SIZE	0x00200000	/* EPROM size 2M byte */
#घोषणा PA_FROM		0xa1000000	/* Flash-ROM */
#घोषणा PA_FROM_SIZE	0x01000000	/* Flash-ROM size 16M byte */
#घोषणा PA_EXT1		0xa4000000
#घोषणा PA_EXT1_SIZE	0x04000000
#घोषणा PA_SDRAM	0xaC000000	/* SDRAM(Area3) 64MB */
#घोषणा PA_SDRAM_SIZE	0x04000000

#घोषणा PA_EXT4		0xb0000000
#घोषणा PA_EXT4_SIZE	0x04000000

#घोषणा PA_PERIPHERAL	0xB8000000

#घोषणा PA_PCIC		PA_PERIPHERAL
#घोषणा PA_MRSHPC	(PA_PERIPHERAL + 0x003fffe0)
#घोषणा PA_MRSHPC_MW1	(PA_PERIPHERAL + 0x00400000)
#घोषणा PA_MRSHPC_MW2	(PA_PERIPHERAL + 0x00500000)
#घोषणा PA_MRSHPC_IO	(PA_PERIPHERAL + 0x00600000)
#घोषणा MRSHPC_OPTION	(PA_MRSHPC + 6)
#घोषणा MRSHPC_CSR	(PA_MRSHPC + 8)
#घोषणा MRSHPC_ISR	(PA_MRSHPC + 10)
#घोषणा MRSHPC_ICR	(PA_MRSHPC + 12)
#घोषणा MRSHPC_CPWCR	(PA_MRSHPC + 14)
#घोषणा MRSHPC_MW0CR1	(PA_MRSHPC + 16)
#घोषणा MRSHPC_MW1CR1	(PA_MRSHPC + 18)
#घोषणा MRSHPC_IOWCR1	(PA_MRSHPC + 20)
#घोषणा MRSHPC_MW0CR2	(PA_MRSHPC + 22)
#घोषणा MRSHPC_MW1CR2	(PA_MRSHPC + 24)
#घोषणा MRSHPC_IOWCR2	(PA_MRSHPC + 26)
#घोषणा MRSHPC_CDCR	(PA_MRSHPC + 28)
#घोषणा MRSHPC_PCIC_INFO	(PA_MRSHPC + 30)

#घोषणा PA_LED		0xB6800000	/* 8bit LED */
#घोषणा PA_FPGA		0xB7000000	/* FPGA base address */

#घोषणा MRSHPC_IRQ0	evt2irq(0x340)

#घोषणा FPGA_ILSR1	(PA_FPGA + 0x02)
#घोषणा FPGA_ILSR2	(PA_FPGA + 0x03)
#घोषणा FPGA_ILSR3	(PA_FPGA + 0x04)
#घोषणा FPGA_ILSR4	(PA_FPGA + 0x05)
#घोषणा FPGA_ILSR5	(PA_FPGA + 0x06)
#घोषणा FPGA_ILSR6	(PA_FPGA + 0x07)
#घोषणा FPGA_ILSR7	(PA_FPGA + 0x08)
#घोषणा FPGA_ILSR8	(PA_FPGA + 0x09)

व्योम init_se7721_IRQ(व्योम);

#घोषणा __IO_PREFIX		se7721
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_SE7721_H */
