<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rl6231.h - RL6231 class device shared support
 *
 * Copyright 2014 Realtek Semiconductor Corp.
 *
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#अगर_अघोषित __RL6231_H__
#घोषणा __RL6231_H__

#घोषणा RL6231_PLL_INP_MAX	50000000
#घोषणा RL6231_PLL_INP_MIN	256000
#घोषणा RL6231_PLL_N_MAX	0x1ff
#घोषणा RL6231_PLL_K_MAX	0x1f
#घोषणा RL6231_PLL_M_MAX	0xf

काष्ठा rl6231_pll_code अणु
	bool m_bp; /* Indicates bypass m code or not. */
	bool k_bp; /* Indicates bypass k code or not. */
	पूर्णांक m_code;
	पूर्णांक n_code;
	पूर्णांक k_code;
पूर्ण;

पूर्णांक rl6231_calc_dmic_clk(पूर्णांक rate);
पूर्णांक rl6231_pll_calc(स्थिर अचिन्हित पूर्णांक freq_in,
	स्थिर अचिन्हित पूर्णांक freq_out, काष्ठा rl6231_pll_code *pll_code);
पूर्णांक rl6231_get_clk_info(पूर्णांक sclk, पूर्णांक rate);
पूर्णांक rl6231_get_pre_भाग(काष्ठा regmap *map, अचिन्हित पूर्णांक reg, पूर्णांक sft);

#पूर्ण_अगर /* __RL6231_H__ */
