<शैली गुरु>
/*
 * Cobalt IRQ definitions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997 Cobalt Microserver
 * Copyright (C) 1997, 2003 Ralf Baechle
 * Copyright (C) 2001-2003 Liam Davies (ldavies@agile.tv)
 * Copyright (C) 2007 Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित _ASM_COBALT_IRQ_H
#घोषणा _ASM_COBALT_IRQ_H

/*
 * i8259 पूर्णांकerrupts used on Cobalt:
 *
 *	8  - RTC
 *	9  - PCI slot
 *	14 - IDE0
 *	15 - IDE1(no connector on board)
 */
#घोषणा I8259A_IRQ_BASE			0

#घोषणा PCISLOT_IRQ			(I8259A_IRQ_BASE + 9)

/*
 * CPU पूर्णांकerrupts used on Cobalt:
 *
 *	0 - Software पूर्णांकerrupt 0 (unused)
 *	1 - Software पूर्णांकerrupt 0 (unused)
 *	2 - cascade GT64111
 *	3 - ethernet or SCSI host controller
 *	4 - ethernet
 *	5 - 16550 UART
 *	6 - cascade i8259
 *	7 - CP0 counter
 */
#घोषणा MIPS_CPU_IRQ_BASE		16

#घोषणा GT641XX_CASCADE_IRQ		(MIPS_CPU_IRQ_BASE + 2)
#घोषणा RAQ2_SCSI_IRQ			(MIPS_CPU_IRQ_BASE + 3)
#घोषणा ETH0_IRQ			(MIPS_CPU_IRQ_BASE + 3)
#घोषणा QUBE1_ETH0_IRQ			(MIPS_CPU_IRQ_BASE + 4)
#घोषणा ETH1_IRQ			(MIPS_CPU_IRQ_BASE + 4)
#घोषणा SERIAL_IRQ			(MIPS_CPU_IRQ_BASE + 5)
#घोषणा SCSI_IRQ			(MIPS_CPU_IRQ_BASE + 5)
#घोषणा I8259_CASCADE_IRQ		(MIPS_CPU_IRQ_BASE + 6)

#घोषणा GT641XX_IRQ_BASE		24

#समावेश <यंत्र/irq_gt641xx.h>

#घोषणा NR_IRQS					(GT641XX_PCI_INT3_IRQ + 1)

#पूर्ण_अगर /* _ASM_COBALT_IRQ_H */
