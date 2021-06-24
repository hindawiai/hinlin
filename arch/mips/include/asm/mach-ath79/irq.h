<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2008-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 */
#अगर_अघोषित __ASM_MACH_ATH79_IRQ_H
#घोषणा __ASM_MACH_ATH79_IRQ_H

#घोषणा MIPS_CPU_IRQ_BASE	0
#घोषणा NR_IRQS			51

#घोषणा ATH79_CPU_IRQ(_x)	(MIPS_CPU_IRQ_BASE + (_x))

#घोषणा ATH79_MISC_IRQ_BASE	8
#घोषणा ATH79_MISC_IRQ_COUNT	32
#घोषणा ATH79_MISC_IRQ(_x)	(ATH79_MISC_IRQ_BASE + (_x))

#घोषणा ATH79_PCI_IRQ_BASE	(ATH79_MISC_IRQ_BASE + ATH79_MISC_IRQ_COUNT)
#घोषणा ATH79_PCI_IRQ_COUNT	6
#घोषणा ATH79_PCI_IRQ(_x)	(ATH79_PCI_IRQ_BASE + (_x))

#घोषणा ATH79_IP2_IRQ_BASE	(ATH79_PCI_IRQ_BASE + ATH79_PCI_IRQ_COUNT)
#घोषणा ATH79_IP2_IRQ_COUNT	2
#घोषणा ATH79_IP2_IRQ(_x)	(ATH79_IP2_IRQ_BASE + (_x))

#घोषणा ATH79_IP3_IRQ_BASE	(ATH79_IP2_IRQ_BASE + ATH79_IP2_IRQ_COUNT)
#घोषणा ATH79_IP3_IRQ_COUNT     3
#घोषणा ATH79_IP3_IRQ(_x)       (ATH79_IP3_IRQ_BASE + (_x))

#समावेश <यंत्र/mach-generic/irq.h>

#पूर्ण_अगर /* __ASM_MACH_ATH79_IRQ_H */
