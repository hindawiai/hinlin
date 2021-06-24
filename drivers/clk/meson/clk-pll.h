<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __MESON_CLK_PLL_H
#घोषणा __MESON_CLK_PLL_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश "parm.h"

काष्ठा pll_params_table अणु
	अचिन्हित पूर्णांक	m;
	अचिन्हित पूर्णांक	n;
पूर्ण;

काष्ठा pll_mult_range अणु
	अचिन्हित पूर्णांक	min;
	अचिन्हित पूर्णांक	max;
पूर्ण;

#घोषणा PLL_PARAMS(_m, _n)						\
	अणु								\
		.m		= (_m),					\
		.n		= (_n),					\
	पूर्ण

#घोषणा CLK_MESON_PLL_ROUND_CLOSEST	BIT(0)

काष्ठा meson_clk_pll_data अणु
	काष्ठा parm en;
	काष्ठा parm m;
	काष्ठा parm n;
	काष्ठा parm frac;
	काष्ठा parm l;
	काष्ठा parm rst;
	स्थिर काष्ठा reg_sequence *init_regs;
	अचिन्हित पूर्णांक init_count;
	स्थिर काष्ठा pll_params_table *table;
	स्थिर काष्ठा pll_mult_range *range;
	u8 flags;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops meson_clk_pll_ro_ops;
बाह्य स्थिर काष्ठा clk_ops meson_clk_pll_ops;
बाह्य स्थिर काष्ठा clk_ops meson_clk_pcie_pll_ops;

#पूर्ण_अगर /* __MESON_CLK_PLL_H */
