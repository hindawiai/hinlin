<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Timers Module
 */

#अगर_अघोषित __ASM_MACH_REGS_TIMERS_H
#घोषणा __ASM_MACH_REGS_TIMERS_H

#समावेश "addr-map.h"

#घोषणा TIMERS1_VIRT_BASE	(APB_VIRT_BASE + 0x14000)
#घोषणा TIMERS2_VIRT_BASE	(APB_VIRT_BASE + 0x16000)

#घोषणा TMR_CCR		(0x0000)
#घोषणा TMR_TN_MM(n, m)	(0x0004 + ((n) << 3) + (((n) + (m)) << 2))
#घोषणा TMR_CR(n)	(0x0028 + ((n) << 2))
#घोषणा TMR_SR(n)	(0x0034 + ((n) << 2))
#घोषणा TMR_IER(n)	(0x0040 + ((n) << 2))
#घोषणा TMR_PLVR(n)	(0x004c + ((n) << 2))
#घोषणा TMR_PLCR(n)	(0x0058 + ((n) << 2))
#घोषणा TMR_WMER	(0x0064)
#घोषणा TMR_WMR		(0x0068)
#घोषणा TMR_WVR		(0x006c)
#घोषणा TMR_WSR		(0x0070)
#घोषणा TMR_ICR(n)	(0x0074 + ((n) << 2))
#घोषणा TMR_WICR	(0x0080)
#घोषणा TMR_CER		(0x0084)
#घोषणा TMR_CMR		(0x0088)
#घोषणा TMR_ILR(n)	(0x008c + ((n) << 2))
#घोषणा TMR_WCR		(0x0098)
#घोषणा TMR_WFAR	(0x009c)
#घोषणा TMR_WSAR	(0x00A0)
#घोषणा TMR_CVWR(n)	(0x00A4 + ((n) << 2))

#घोषणा TMR_CCR_CS_0(x)	(((x) & 0x3) << 0)
#घोषणा TMR_CCR_CS_1(x)	(((x) & 0x7) << 2)
#घोषणा TMR_CCR_CS_2(x)	(((x) & 0x3) << 5)

#पूर्ण_अगर /* __ASM_MACH_REGS_TIMERS_H */
