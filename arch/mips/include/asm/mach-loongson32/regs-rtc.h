<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2016 Yang Ling <gnaygnil@gmail.com>
 *
 * Loongson 1 RTC समयr Register Definitions.
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_REGS_RTC_H
#घोषणा __ASM_MACH_LOONGSON32_REGS_RTC_H

#घोषणा LS1X_RTC_REG(x) \
		((व्योम __iomem *)KSEG1ADDR(LS1X_RTC_BASE + (x)))

#घोषणा LS1X_RTC_CTRL	LS1X_RTC_REG(0x40)

#घोषणा RTC_EXTCLK_OK	(BIT(5) | BIT(8))
#घोषणा RTC_EXTCLK_EN	BIT(8)

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_REGS_RTC_H */
