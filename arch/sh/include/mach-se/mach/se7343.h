<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_HITACHI_SE7343_H
#घोषणा __ASM_SH_HITACHI_SE7343_H

/*
 * include/यंत्र-sh/se/se7343.h
 *
 * Copyright (C) 2003 Takashi Kusuda <kusuda-takashi@hitachi-ul.co.jp>
 *
 * SH-Mobile SolutionEngine 7343 support
 */
#समावेश <linux/sh_पूर्णांकc.h>

/* Box specअगरic addresses.  */

/* Area 0 */
#घोषणा PA_ROM		0x00000000	/* EPROM */
#घोषणा PA_ROM_SIZE	0x00400000	/* EPROM size 4M byte(Actually 2MB) */
#घोषणा PA_FROM		0x00400000	/* Flash ROM */
#घोषणा PA_FROM_SIZE	0x00400000	/* Flash size 4M byte */
#घोषणा PA_SRAM		0x00800000	/* SRAM */
#घोषणा PA_FROM_SIZE	0x00400000	/* SRAM size 4M byte */
/* Area 1 */
#घोषणा PA_EXT1		0x04000000
#घोषणा PA_EXT1_SIZE	0x04000000
/* Area 2 */
#घोषणा PA_EXT2		0x08000000
#घोषणा PA_EXT2_SIZE	0x04000000
/* Area 3 */
#घोषणा PA_SDRAM	0x0c000000
#घोषणा PA_SDRAM_SIZE	0x04000000
/* Area 4 */
#घोषणा PA_PCIC		0x10000000	/* MR-SHPC-01 PCMCIA */
#घोषणा PA_MRSHPC       0xb03fffe0      /* MR-SHPC-01 PCMCIA controller */
#घोषणा PA_MRSHPC_MW1   0xb0400000      /* MR-SHPC-01 memory winकरोw base */
#घोषणा PA_MRSHPC_MW2   0xb0500000      /* MR-SHPC-01 attribute winकरोw base */
#घोषणा PA_MRSHPC_IO    0xb0600000      /* MR-SHPC-01 I/O winकरोw base */
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
#घोषणा PA_LED		0xb0C00000	/* LED */
#घोषणा LED_SHIFT       0
#घोषणा PA_DIPSW	0xb0900000	/* Dip चयन 31 */
/* Area 5 */
#घोषणा PA_EXT5		0x14000000
#घोषणा PA_EXT5_SIZE	0x04000000
/* Area 6 */
#घोषणा PA_LCD1		0xb8000000
#घोषणा PA_LCD2		0xb8800000

#घोषणा PORT_PACR	0xA4050100
#घोषणा PORT_PBCR	0xA4050102
#घोषणा PORT_PCCR	0xA4050104
#घोषणा PORT_PDCR	0xA4050106
#घोषणा PORT_PECR	0xA4050108
#घोषणा PORT_PFCR	0xA405010A
#घोषणा PORT_PGCR	0xA405010C
#घोषणा PORT_PHCR	0xA405010E
#घोषणा PORT_PJCR	0xA4050110
#घोषणा PORT_PKCR	0xA4050112
#घोषणा PORT_PLCR	0xA4050114
#घोषणा PORT_PMCR	0xA4050116
#घोषणा PORT_PNCR	0xA4050118
#घोषणा PORT_PQCR	0xA405011A
#घोषणा PORT_PRCR	0xA405011C
#घोषणा PORT_PSCR	0xA405011E
#घोषणा PORT_PTCR	0xA4050140
#घोषणा PORT_PUCR	0xA4050142
#घोषणा PORT_PVCR	0xA4050144
#घोषणा PORT_PWCR	0xA4050146
#घोषणा PORT_PYCR	0xA4050148
#घोषणा PORT_PZCR	0xA405014A

#घोषणा PORT_PSELA	0xA405014C
#घोषणा PORT_PSELB	0xA405014E
#घोषणा PORT_PSELC	0xA4050150
#घोषणा PORT_PSELD	0xA4050152
#घोषणा PORT_PSELE	0xA4050154

#घोषणा PORT_HIZCRA	0xA4050156
#घोषणा PORT_HIZCRB	0xA4050158
#घोषणा PORT_HIZCRC	0xA405015C

#घोषणा PORT_DRVCR	0xA4050180

#घोषणा PORT_PADR	0xA4050120
#घोषणा PORT_PBDR	0xA4050122
#घोषणा PORT_PCDR	0xA4050124
#घोषणा PORT_PDDR	0xA4050126
#घोषणा PORT_PEDR	0xA4050128
#घोषणा PORT_PFDR	0xA405012A
#घोषणा PORT_PGDR	0xA405012C
#घोषणा PORT_PHDR	0xA405012E
#घोषणा PORT_PJDR	0xA4050130
#घोषणा PORT_PKDR	0xA4050132
#घोषणा PORT_PLDR	0xA4050134
#घोषणा PORT_PMDR	0xA4050136
#घोषणा PORT_PNDR	0xA4050138
#घोषणा PORT_PQDR	0xA405013A
#घोषणा PORT_PRDR	0xA405013C
#घोषणा PORT_PTDR	0xA4050160
#घोषणा PORT_PUDR	0xA4050162
#घोषणा PORT_PVDR	0xA4050164
#घोषणा PORT_PWDR	0xA4050166
#घोषणा PORT_PYDR	0xA4050168

#घोषणा FPGA_IN		0xb1400000
#घोषणा FPGA_OUT	0xb1400002

#घोषणा IRQ0_IRQ        evt2irq(0x600)
#घोषणा IRQ1_IRQ        evt2irq(0x620)
#घोषणा IRQ4_IRQ        evt2irq(0x680)
#घोषणा IRQ5_IRQ        evt2irq(0x6a0)

#घोषणा SE7343_FPGA_IRQ_MRSHPC0	0
#घोषणा SE7343_FPGA_IRQ_MRSHPC1	1
#घोषणा SE7343_FPGA_IRQ_MRSHPC2	2
#घोषणा SE7343_FPGA_IRQ_MRSHPC3	3
#घोषणा SE7343_FPGA_IRQ_SMC	6	/* EXT_IRQ2 */
#घोषणा SE7343_FPGA_IRQ_USB	8
#घोषणा SE7343_FPGA_IRQ_UARTA	10
#घोषणा SE7343_FPGA_IRQ_UARTB	11

#घोषणा SE7343_FPGA_IRQ_NR	12

काष्ठा irq_करोमुख्य;

/* arch/sh/boards/se/7343/irq.c */
बाह्य काष्ठा irq_करोमुख्य *se7343_irq_करोमुख्य;

व्योम init_7343se_IRQ(व्योम);

#पूर्ण_अगर  /* __ASM_SH_HITACHI_SE7343_H */
