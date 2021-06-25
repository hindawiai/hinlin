<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMARM_SMP_TWD_H
#घोषणा __ASMARM_SMP_TWD_H

#घोषणा TWD_TIMER_LOAD			0x00
#घोषणा TWD_TIMER_COUNTER		0x04
#घोषणा TWD_TIMER_CONTROL		0x08
#घोषणा TWD_TIMER_INTSTAT		0x0C

#घोषणा TWD_WDOG_LOAD			0x20
#घोषणा TWD_WDOG_COUNTER		0x24
#घोषणा TWD_WDOG_CONTROL		0x28
#घोषणा TWD_WDOG_INTSTAT		0x2C
#घोषणा TWD_WDOG_RESETSTAT		0x30
#घोषणा TWD_WDOG_DISABLE		0x34

#घोषणा TWD_TIMER_CONTROL_ENABLE	(1 << 0)
#घोषणा TWD_TIMER_CONTROL_ONESHOT	(0 << 1)
#घोषणा TWD_TIMER_CONTROL_PERIODIC	(1 << 1)
#घोषणा TWD_TIMER_CONTROL_IT_ENABLE	(1 << 2)

#पूर्ण_अगर
