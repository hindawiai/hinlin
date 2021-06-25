<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2008 Cavium Networks
 */
#अगर_अघोषित __OCTEON_IRQ_H__
#घोषणा __OCTEON_IRQ_H__

#घोषणा NR_IRQS OCTEON_IRQ_LAST
#घोषणा MIPS_CPU_IRQ_BASE OCTEON_IRQ_SW0

क्रमागत octeon_irq अणु
/* 1 - 8 represent the 8 MIPS standard पूर्णांकerrupt sources */
	OCTEON_IRQ_SW0 = 1,
	OCTEON_IRQ_SW1,
/* CIU0, CUI2, CIU4 are 3, 4, 5 */
	OCTEON_IRQ_5 = 6,
	OCTEON_IRQ_PERF,
	OCTEON_IRQ_TIMER,
/* sources in CIU_INTX_EN0 */
	OCTEON_IRQ_WORKQ0,
	OCTEON_IRQ_WDOG0 = OCTEON_IRQ_WORKQ0 + 64,
	OCTEON_IRQ_MBOX0 = OCTEON_IRQ_WDOG0 + 32,
	OCTEON_IRQ_MBOX1,
	OCTEON_IRQ_MBOX2,
	OCTEON_IRQ_MBOX3,
	OCTEON_IRQ_PCI_INT0,
	OCTEON_IRQ_PCI_INT1,
	OCTEON_IRQ_PCI_INT2,
	OCTEON_IRQ_PCI_INT3,
	OCTEON_IRQ_PCI_MSI0,
	OCTEON_IRQ_PCI_MSI1,
	OCTEON_IRQ_PCI_MSI2,
	OCTEON_IRQ_PCI_MSI3,

	OCTEON_IRQ_TWSI,
	OCTEON_IRQ_TWSI2,
	OCTEON_IRQ_RML,
	OCTEON_IRQ_TIMER0,
	OCTEON_IRQ_TIMER1,
	OCTEON_IRQ_TIMER2,
	OCTEON_IRQ_TIMER3,
#अगर_अघोषित CONFIG_PCI_MSI
	OCTEON_IRQ_LAST = 127
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
/* 256 - 511 represent the MSI पूर्णांकerrupts 0-255 */
#घोषणा OCTEON_IRQ_MSI_BIT0	(256)

#घोषणा OCTEON_IRQ_MSI_LAST	 (OCTEON_IRQ_MSI_BIT0 + 255)
#घोषणा OCTEON_IRQ_LAST		 (OCTEON_IRQ_MSI_LAST + 1)
#पूर्ण_अगर

#पूर्ण_अगर
