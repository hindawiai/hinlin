<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __MESON_CLK_MPLL_H
#घोषणा __MESON_CLK_MPLL_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>

#समावेश "parm.h"

काष्ठा meson_clk_mpll_data अणु
	काष्ठा parm sdm;
	काष्ठा parm sdm_en;
	काष्ठा parm n2;
	काष्ठा parm ssen;
	काष्ठा parm misc;
	स्थिर काष्ठा reg_sequence *init_regs;
	अचिन्हित पूर्णांक init_count;
	spinlock_t *lock;
	u8 flags;
पूर्ण;

#घोषणा CLK_MESON_MPLL_ROUND_CLOSEST	BIT(0)
#घोषणा CLK_MESON_MPLL_SPREAD_SPECTRUM	BIT(1)

बाह्य स्थिर काष्ठा clk_ops meson_clk_mpll_ro_ops;
बाह्य स्थिर काष्ठा clk_ops meson_clk_mpll_ops;

#पूर्ण_अगर /* __MESON_CLK_MPLL_H */
