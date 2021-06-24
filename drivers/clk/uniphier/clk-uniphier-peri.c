<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश "clk-uniphier.h"

#घोषणा UNIPHIER_PERI_CLK_UART(idx, ch)					\
	UNIPHIER_CLK_GATE("uart" #ch, (idx), "uart", 0x24, 19 + (ch))

#घोषणा UNIPHIER_PERI_CLK_I2C_COMMON					\
	UNIPHIER_CLK_GATE("i2c-common", -1, "i2c", 0x20, 1)

#घोषणा UNIPHIER_PERI_CLK_I2C(idx, ch)					\
	UNIPHIER_CLK_GATE("i2c" #ch, (idx), "i2c-common", 0x24, 5 + (ch))

#घोषणा UNIPHIER_PERI_CLK_FI2C(idx, ch)					\
	UNIPHIER_CLK_GATE("i2c" #ch, (idx), "i2c", 0x24, 24 + (ch))

#घोषणा UNIPHIER_PERI_CLK_SCSSI(idx, ch)				\
	UNIPHIER_CLK_GATE("scssi" #ch, (idx), "spi", 0x20, 17 + (ch))

#घोषणा UNIPHIER_PERI_CLK_MCSSI(idx)					\
	UNIPHIER_CLK_GATE("mcssi", (idx), "spi", 0x24, 14)

स्थिर काष्ठा uniphier_clk_data uniphier_ld4_peri_clk_data[] = अणु
	UNIPHIER_PERI_CLK_UART(0, 0),
	UNIPHIER_PERI_CLK_UART(1, 1),
	UNIPHIER_PERI_CLK_UART(2, 2),
	UNIPHIER_PERI_CLK_UART(3, 3),
	UNIPHIER_PERI_CLK_I2C_COMMON,
	UNIPHIER_PERI_CLK_I2C(4, 0),
	UNIPHIER_PERI_CLK_I2C(5, 1),
	UNIPHIER_PERI_CLK_I2C(6, 2),
	UNIPHIER_PERI_CLK_I2C(7, 3),
	UNIPHIER_PERI_CLK_I2C(8, 4),
	UNIPHIER_PERI_CLK_SCSSI(11, 0),
	अणु /* sentinel */ पूर्ण
पूर्ण;

स्थिर काष्ठा uniphier_clk_data uniphier_pro4_peri_clk_data[] = अणु
	UNIPHIER_PERI_CLK_UART(0, 0),
	UNIPHIER_PERI_CLK_UART(1, 1),
	UNIPHIER_PERI_CLK_UART(2, 2),
	UNIPHIER_PERI_CLK_UART(3, 3),
	UNIPHIER_PERI_CLK_FI2C(4, 0),
	UNIPHIER_PERI_CLK_FI2C(5, 1),
	UNIPHIER_PERI_CLK_FI2C(6, 2),
	UNIPHIER_PERI_CLK_FI2C(7, 3),
	UNIPHIER_PERI_CLK_FI2C(8, 4),
	UNIPHIER_PERI_CLK_FI2C(9, 5),
	UNIPHIER_PERI_CLK_FI2C(10, 6),
	UNIPHIER_PERI_CLK_SCSSI(11, 0),
	UNIPHIER_PERI_CLK_SCSSI(12, 1),
	UNIPHIER_PERI_CLK_SCSSI(13, 2),
	UNIPHIER_PERI_CLK_SCSSI(14, 3),
	UNIPHIER_PERI_CLK_MCSSI(15),
	अणु /* sentinel */ पूर्ण
पूर्ण;
