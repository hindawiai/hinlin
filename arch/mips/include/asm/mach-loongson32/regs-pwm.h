<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * Loongson 1 PWM Register Definitions.
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_REGS_PWM_H
#घोषणा __ASM_MACH_LOONGSON32_REGS_PWM_H

/* Loongson 1 PWM Timer Register Definitions */
#घोषणा PWM_CNT			0x0
#घोषणा PWM_HRC			0x4
#घोषणा PWM_LRC			0x8
#घोषणा PWM_CTRL		0xc

/* PWM Control Register Bits */
#घोषणा CNT_RST			BIT(7)
#घोषणा INT_SR			BIT(6)
#घोषणा INT_EN			BIT(5)
#घोषणा PWM_SINGLE		BIT(4)
#घोषणा PWM_OE			BIT(3)
#घोषणा CNT_EN			BIT(0)

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_REGS_PWM_H */
