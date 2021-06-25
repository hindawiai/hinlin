<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_REGS_RTC_H
#घोषणा __ASM_MACH_REGS_RTC_H

#समावेश <mach/hardware.h>

/*
 * Real Time Clock
 */

#घोषणा RCNR		__REG(0x40900000)  /* RTC Count Register */
#घोषणा RTAR		__REG(0x40900004)  /* RTC Alarm Register */
#घोषणा RTSR		__REG(0x40900008)  /* RTC Status Register */
#घोषणा RTTR		__REG(0x4090000C)  /* RTC Timer Trim Register */
#घोषणा PIAR		__REG(0x40900038)  /* Periodic Interrupt Alarm Register */

#घोषणा RTSR_PICE	(1 << 15)	/* Periodic पूर्णांकerrupt count enable */
#घोषणा RTSR_PIALE	(1 << 14)	/* Periodic पूर्णांकerrupt Alarm enable */
#घोषणा RTSR_HZE	(1 << 3)	/* HZ पूर्णांकerrupt enable */
#घोषणा RTSR_ALE	(1 << 2)	/* RTC alarm पूर्णांकerrupt enable */
#घोषणा RTSR_HZ		(1 << 1)	/* HZ rising-edge detected */
#घोषणा RTSR_AL		(1 << 0)	/* RTC alarm detected */

#पूर्ण_अगर /* __ASM_MACH_REGS_RTC_H */
