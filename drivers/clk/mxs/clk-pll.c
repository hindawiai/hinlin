<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "clk.h"

/**
 * काष्ठा clk_pll - mxs pll घड़ी
 * @hw: clk_hw क्रम the pll
 * @base: base address of the pll
 * @घातer: the shअगरt of घातer bit
 * @rate: the घड़ी rate of the pll
 *
 * The mxs pll is a fixed rate घड़ी with घातer and gate control,
 * and the shअगरt of gate bit is always 31.
 */
काष्ठा clk_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	u8 घातer;
	अचिन्हित दीर्घ rate;
पूर्ण;

#घोषणा to_clk_pll(_hw) container_of(_hw, काष्ठा clk_pll, hw)

अटल पूर्णांक clk_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	ग_लिखोl_relaxed(1 << pll->घातer, pll->base + SET);

	udelay(10);

	वापस 0;
पूर्ण

अटल व्योम clk_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	ग_लिखोl_relaxed(1 << pll->घातer, pll->base + CLR);
पूर्ण

अटल पूर्णांक clk_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	ग_लिखोl_relaxed(1 << 31, pll->base + CLR);

	वापस 0;
पूर्ण

अटल व्योम clk_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	ग_लिखोl_relaxed(1 << 31, pll->base + SET);
पूर्ण

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);

	वापस pll->rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.prepare = clk_pll_prepare,
	.unprepare = clk_pll_unprepare,
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
पूर्ण;

काष्ठा clk *mxs_clk_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			व्योम __iomem *base, u8 घातer, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk_pll *pll;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_pll_ops;
	init.flags = 0;
	init.parent_names = (parent_name ? &parent_name: शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	pll->base = base;
	pll->rate = rate;
	pll->घातer = घातer;
	pll->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &pll->hw);
	अगर (IS_ERR(clk))
		kमुक्त(pll);

	वापस clk;
पूर्ण
