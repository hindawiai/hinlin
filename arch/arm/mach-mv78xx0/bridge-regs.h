<शैली गुरु>
/*
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_BRIDGE_REGS_H
#घोषणा __ASM_ARCH_BRIDGE_REGS_H

#समावेश "mv78xx0.h"

#घोषणा CPU_CONTROL		(BRIDGE_VIRT_BASE + 0x0104)
#घोषणा L2_WRITETHROUGH		0x00020000

#घोषणा RSTOUTn_MASK		(BRIDGE_VIRT_BASE + 0x0108)
#घोषणा RSTOUTn_MASK_PHYS	(BRIDGE_PHYS_BASE + 0x0108)
#घोषणा SOFT_RESET_OUT_EN	0x00000004

#घोषणा SYSTEM_SOFT_RESET	(BRIDGE_VIRT_BASE + 0x010c)
#घोषणा SOFT_RESET		0x00000001

#घोषणा BRIDGE_INT_TIMER1_CLR	(~0x0004)

#घोषणा IRQ_VIRT_BASE		(BRIDGE_VIRT_BASE + 0x0200)
#घोषणा IRQ_CAUSE_ERR_OFF	0x0000
#घोषणा IRQ_CAUSE_LOW_OFF	0x0004
#घोषणा IRQ_CAUSE_HIGH_OFF	0x0008
#घोषणा IRQ_MASK_ERR_OFF	0x000c
#घोषणा IRQ_MASK_LOW_OFF	0x0010
#घोषणा IRQ_MASK_HIGH_OFF	0x0014

#घोषणा TIMER_VIRT_BASE		(BRIDGE_VIRT_BASE + 0x0300)
#घोषणा TIMER_PHYS_BASE		(BRIDGE_PHYS_BASE + 0x0300)

#पूर्ण_अगर
