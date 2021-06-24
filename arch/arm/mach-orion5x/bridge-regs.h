<शैली गुरु>
/*
 * Orion CPU Bridge Registers
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_BRIDGE_REGS_H
#घोषणा __ASM_ARCH_BRIDGE_REGS_H

#समावेश "orion5x.h"

#घोषणा CPU_CONF		(ORION5X_BRIDGE_VIRT_BASE + 0x100)

#घोषणा CPU_CTRL		(ORION5X_BRIDGE_VIRT_BASE + 0x104)

#घोषणा RSTOUTn_MASK		(ORION5X_BRIDGE_VIRT_BASE + 0x108)
#घोषणा RSTOUTn_MASK_PHYS	(ORION5X_BRIDGE_PHYS_BASE + 0x108)

#घोषणा CPU_SOFT_RESET		(ORION5X_BRIDGE_VIRT_BASE + 0x10c)

#घोषणा BRIDGE_CAUSE		(ORION5X_BRIDGE_VIRT_BASE + 0x110)

#घोषणा POWER_MNG_CTRL_REG	(ORION5X_BRIDGE_VIRT_BASE + 0x11C)

#घोषणा BRIDGE_INT_TIMER1_CLR	(~0x0004)

#घोषणा MAIN_IRQ_CAUSE		(ORION5X_BRIDGE_VIRT_BASE + 0x200)

#घोषणा MAIN_IRQ_MASK		(ORION5X_BRIDGE_VIRT_BASE + 0x204)

#घोषणा TIMER_VIRT_BASE		(ORION5X_BRIDGE_VIRT_BASE + 0x300)
#घोषणा TIMER_PHYS_BASE		(ORION5X_BRIDGE_PHYS_BASE + 0x300)
#पूर्ण_अगर
