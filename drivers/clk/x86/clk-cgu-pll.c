<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel Corporation.
 * Zhu YiXin <yixin.zhu@पूर्णांकel.com>
 * Rahul Tanwar <rahul.tanwar@पूर्णांकel.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>

#समावेश "clk-cgu.h"

#घोषणा to_lgm_clk_pll(_hw)	container_of(_hw, काष्ठा lgm_clk_pll, hw)
#घोषणा PLL_REF_DIV(x)		((x) + 0x08)

/*
 * Calculate क्रमmula:
 * rate = (prate * mult + (prate * frac) / frac_भाग) / भाग
 */
अटल अचिन्हित दीर्घ
lgm_pll_calc_rate(अचिन्हित दीर्घ prate, अचिन्हित पूर्णांक mult,
		  अचिन्हित पूर्णांक भाग, अचिन्हित पूर्णांक frac, अचिन्हित पूर्णांक frac_भाग)
अणु
	u64 crate, frate, rate64;

	rate64 = prate;
	crate = rate64 * mult;
	frate = rate64 * frac;
	करो_भाग(frate, frac_भाग);
	crate += frate;
	करो_भाग(crate, भाग);

	वापस crate;
पूर्ण

अटल अचिन्हित दीर्घ lgm_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ prate)
अणु
	काष्ठा lgm_clk_pll *pll = to_lgm_clk_pll(hw);
	अचिन्हित पूर्णांक भाग, mult, frac;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pll->lock, flags);
	mult = lgm_get_clk_val(pll->membase, PLL_REF_DIV(pll->reg), 0, 12);
	भाग = lgm_get_clk_val(pll->membase, PLL_REF_DIV(pll->reg), 18, 6);
	frac = lgm_get_clk_val(pll->membase, pll->reg, 2, 24);
	spin_unlock_irqrestore(&pll->lock, flags);

	अगर (pll->type == TYPE_LJPLL)
		भाग *= 4;

	वापस lgm_pll_calc_rate(prate, mult, भाग, frac, BIT(24));
पूर्ण

अटल पूर्णांक lgm_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_pll *pll = to_lgm_clk_pll(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&pll->lock, flags);
	ret = lgm_get_clk_val(pll->membase, pll->reg, 0, 1);
	spin_unlock_irqrestore(&pll->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक lgm_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_pll *pll = to_lgm_clk_pll(hw);
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	spin_lock_irqsave(&pll->lock, flags);
	lgm_set_clk_val(pll->membase, pll->reg, 0, 1, 1);
	ret = पढ़ोl_poll_समयout_atomic(pll->membase + pll->reg,
					val, (val & 0x1), 1, 100);
	spin_unlock_irqrestore(&pll->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम lgm_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_pll *pll = to_lgm_clk_pll(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pll->lock, flags);
	lgm_set_clk_val(pll->membase, pll->reg, 0, 1, 0);
	spin_unlock_irqrestore(&pll->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops lgm_pll_ops = अणु
	.recalc_rate = lgm_pll_recalc_rate,
	.is_enabled = lgm_pll_is_enabled,
	.enable = lgm_pll_enable,
	.disable = lgm_pll_disable,
पूर्ण;

अटल काष्ठा clk_hw *
lgm_clk_रेजिस्टर_pll(काष्ठा lgm_clk_provider *ctx,
		     स्थिर काष्ठा lgm_pll_clk_data *list)
अणु
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा lgm_clk_pll *pll;
	काष्ठा device *dev = ctx->dev;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	init.ops = &lgm_pll_ops;
	init.name = list->name;
	init.flags = list->flags;
	init.parent_data = list->parent_data;
	init.num_parents = list->num_parents;

	pll = devm_kzalloc(dev, माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	pll->membase = ctx->membase;
	pll->lock = ctx->lock;
	pll->reg = list->reg;
	pll->flags = list->flags;
	pll->type = list->type;
	pll->hw.init = &init;

	hw = &pll->hw;
	ret = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस hw;
पूर्ण

पूर्णांक lgm_clk_रेजिस्टर_plls(काष्ठा lgm_clk_provider *ctx,
			  स्थिर काष्ठा lgm_pll_clk_data *list,
			  अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *hw;
	पूर्णांक i;

	क्रम (i = 0; i < nr_clk; i++, list++) अणु
		hw = lgm_clk_रेजिस्टर_pll(ctx, list);
		अगर (IS_ERR(hw)) अणु
			dev_err(ctx->dev, "failed to register pll: %s\n",
				list->name);
			वापस PTR_ERR(hw);
		पूर्ण
		ctx->clk_data.hws[list->id] = hw;
	पूर्ण

	वापस 0;
पूर्ण
