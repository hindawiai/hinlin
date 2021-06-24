<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Interrupt Control Unit
 */

#अगर_अघोषित __ASM_MACH_ICU_H
#घोषणा __ASM_MACH_ICU_H

#समावेश "addr-map.h"

#घोषणा ICU_VIRT_BASE	(AXI_VIRT_BASE + 0x82000)
#घोषणा ICU_REG(x)	(ICU_VIRT_BASE + (x))

#घोषणा ICU2_VIRT_BASE	(AXI_VIRT_BASE + 0x84000)
#घोषणा ICU2_REG(x)	(ICU2_VIRT_BASE + (x))

#घोषणा ICU_INT_CONF(n)		ICU_REG((n) << 2)
#घोषणा ICU_INT_CONF_MASK	(0xf)

/************ PXA168/PXA910 (MMP) *********************/
#घोषणा ICU_INT_CONF_AP_INT	(1 << 6)
#घोषणा ICU_INT_CONF_CP_INT	(1 << 5)
#घोषणा ICU_INT_CONF_IRQ	(1 << 4)

#घोषणा ICU_AP_FIQ_SEL_INT_NUM	ICU_REG(0x108)	/* AP FIQ Selected Interrupt */
#घोषणा ICU_AP_IRQ_SEL_INT_NUM	ICU_REG(0x10C)	/* AP IRQ Selected Interrupt */
#घोषणा ICU_AP_GBL_IRQ_MSK	ICU_REG(0x114)	/* AP Global Interrupt Mask */
#घोषणा ICU_INT_STATUS_0	ICU_REG(0x128)	/* Interrupt Stuats 0 */
#घोषणा ICU_INT_STATUS_1	ICU_REG(0x12C)	/* Interrupt Status 1 */

/************************** MMP2 ***********************/

/*
 * IRQ0/FIQ0 is routed to SP IRQ/FIQ.
 * IRQ1 is routed to PJ4 IRQ, and IRQ2 is routes to PJ4 FIQ.
 */
#घोषणा ICU_INT_ROUTE_SP_IRQ		(1 << 4)
#घोषणा ICU_INT_ROUTE_PJ4_IRQ		(1 << 5)
#घोषणा ICU_INT_ROUTE_PJ4_FIQ		(1 << 6)

#घोषणा MMP2_ICU_PJ4_IRQ_STATUS0	ICU_REG(0x138)
#घोषणा MMP2_ICU_PJ4_IRQ_STATUS1	ICU_REG(0x13c)
#घोषणा MMP2_ICU_PJ4_FIQ_STATUS0	ICU_REG(0x140)
#घोषणा MMP2_ICU_PJ4_FIQ_STATUS1	ICU_REG(0x144)

#घोषणा MMP2_ICU_INT4_STATUS		ICU_REG(0x150)
#घोषणा MMP2_ICU_INT5_STATUS		ICU_REG(0x154)
#घोषणा MMP2_ICU_INT17_STATUS		ICU_REG(0x158)
#घोषणा MMP2_ICU_INT35_STATUS		ICU_REG(0x15c)
#घोषणा MMP2_ICU_INT51_STATUS		ICU_REG(0x160)

#घोषणा MMP2_ICU_INT4_MASK		ICU_REG(0x168)
#घोषणा MMP2_ICU_INT5_MASK		ICU_REG(0x16C)
#घोषणा MMP2_ICU_INT17_MASK		ICU_REG(0x170)
#घोषणा MMP2_ICU_INT35_MASK		ICU_REG(0x174)
#घोषणा MMP2_ICU_INT51_MASK		ICU_REG(0x178)

#घोषणा MMP2_ICU_SP_IRQ_SEL		ICU_REG(0x100)
#घोषणा MMP2_ICU_PJ4_IRQ_SEL		ICU_REG(0x104)
#घोषणा MMP2_ICU_PJ4_FIQ_SEL		ICU_REG(0x108)

#घोषणा MMP2_ICU_INVERT			ICU_REG(0x164)

#घोषणा MMP2_ICU_INV_PMIC		(1 << 0)
#घोषणा MMP2_ICU_INV_PERF		(1 << 1)
#घोषणा MMP2_ICU_INV_COMMTX		(1 << 2)
#घोषणा MMP2_ICU_INV_COMMRX		(1 << 3)

#पूर्ण_अगर /* __ASM_MACH_ICU_H */
