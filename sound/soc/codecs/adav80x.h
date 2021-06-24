<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * header file क्रम ADAV80X parts
 *
 * Copyright 2011 Analog Devices Inc.
 */

#अगर_अघोषित _ADAV80X_H
#घोषणा _ADAV80X_H

#समावेश <linux/regmap.h>

काष्ठा device;

बाह्य स्थिर काष्ठा regmap_config adav80x_regmap_config;
पूर्णांक adav80x_bus_probe(काष्ठा device *dev, काष्ठा regmap *regmap);

क्रमागत adav80x_pll_src अणु
	ADAV80X_PLL_SRC_XIN,
	ADAV80X_PLL_SRC_XTAL,
	ADAV80X_PLL_SRC_MCLKI,
पूर्ण;

क्रमागत adav80x_pll अणु
	ADAV80X_PLL1 = 0,
	ADAV80X_PLL2 = 1,
पूर्ण;

क्रमागत adav80x_clk_src अणु
	ADAV80X_CLK_XIN = 0,
	ADAV80X_CLK_MCLKI = 1,
	ADAV80X_CLK_PLL1 = 2,
	ADAV80X_CLK_PLL2 = 3,
	ADAV80X_CLK_XTAL = 6,

	ADAV80X_CLK_SYSCLK1 = 6,
	ADAV80X_CLK_SYSCLK2 = 7,
	ADAV80X_CLK_SYSCLK3 = 8,
पूर्ण;

#पूर्ण_अगर
