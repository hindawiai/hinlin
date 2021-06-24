<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 *
 * Loongson 1 Clock Register Definitions.
 */

#अगर_अघोषित __ASM_MACH_LOONGSON32_REGS_CLK_H
#घोषणा __ASM_MACH_LOONGSON32_REGS_CLK_H

#घोषणा LS1X_CLK_REG(x) \
		((व्योम __iomem *)KSEG1ADDR(LS1X_CLK_BASE + (x)))

#घोषणा LS1X_CLK_PLL_FREQ		LS1X_CLK_REG(0x0)
#घोषणा LS1X_CLK_PLL_DIV		LS1X_CLK_REG(0x4)

#अगर defined(CONFIG_LOONGSON1_LS1B)
/* Clock PLL Divisor Register Bits */
#घोषणा DIV_DC_EN			BIT(31)
#घोषणा DIV_DC_RST			BIT(30)
#घोषणा DIV_CPU_EN			BIT(25)
#घोषणा DIV_CPU_RST			BIT(24)
#घोषणा DIV_DDR_EN			BIT(19)
#घोषणा DIV_DDR_RST			BIT(18)
#घोषणा RST_DC_EN			BIT(5)
#घोषणा RST_DC				BIT(4)
#घोषणा RST_DDR_EN			BIT(3)
#घोषणा RST_DDR				BIT(2)
#घोषणा RST_CPU_EN			BIT(1)
#घोषणा RST_CPU				BIT(0)

#घोषणा DIV_DC_SHIFT			26
#घोषणा DIV_CPU_SHIFT			20
#घोषणा DIV_DDR_SHIFT			14

#घोषणा DIV_DC_WIDTH			4
#घोषणा DIV_CPU_WIDTH			4
#घोषणा DIV_DDR_WIDTH			4

#घोषणा BYPASS_DC_SHIFT			12
#घोषणा BYPASS_DDR_SHIFT		10
#घोषणा BYPASS_CPU_SHIFT		8

#घोषणा BYPASS_DC_WIDTH			1
#घोषणा BYPASS_DDR_WIDTH		1
#घोषणा BYPASS_CPU_WIDTH		1

#या_अगर defined(CONFIG_LOONGSON1_LS1C)
/* PLL/SDRAM Frequency configuration रेजिस्टर Bits */
#घोषणा PLL_VALID			BIT(31)
#घोषणा FRAC_N				GENMASK(23, 16)
#घोषणा RST_TIME			GENMASK(3, 2)
#घोषणा SDRAM_DIV			GENMASK(1, 0)

/* CPU/CAMERA/DC Frequency configuration रेजिस्टर Bits */
#घोषणा DIV_DC_EN			BIT(31)
#घोषणा DIV_DC				GENMASK(30, 24)
#घोषणा DIV_CAM_EN			BIT(23)
#घोषणा DIV_CAM				GENMASK(22, 16)
#घोषणा DIV_CPU_EN			BIT(15)
#घोषणा DIV_CPU				GENMASK(14, 8)
#घोषणा DIV_DC_SEL_EN			BIT(5)
#घोषणा DIV_DC_SEL			BIT(4)
#घोषणा DIV_CAM_SEL_EN			BIT(3)
#घोषणा DIV_CAM_SEL			BIT(2)
#घोषणा DIV_CPU_SEL_EN			BIT(1)
#घोषणा DIV_CPU_SEL			BIT(0)

#घोषणा DIV_DC_SHIFT			24
#घोषणा DIV_CAM_SHIFT			16
#घोषणा DIV_CPU_SHIFT			8
#घोषणा DIV_DDR_SHIFT			0

#घोषणा DIV_DC_WIDTH			7
#घोषणा DIV_CAM_WIDTH			7
#घोषणा DIV_CPU_WIDTH			7
#घोषणा DIV_DDR_WIDTH			2

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_LOONGSON32_REGS_CLK_H */
