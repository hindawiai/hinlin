<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/slab.h>

#समावेश "ccu_common.h"
#समावेश "ccu_gate.h"
#समावेश "ccu_reset.h"

अटल DEFINE_SPINLOCK(ccu_lock);

व्योम ccu_helper_रुको_क्रम_lock(काष्ठा ccu_common *common, u32 lock)
अणु
	व्योम __iomem *addr;
	u32 reg;

	अगर (!lock)
		वापस;

	अगर (common->features & CCU_FEATURE_LOCK_REG)
		addr = common->base + common->lock_reg;
	अन्यथा
		addr = common->base + common->reg;

	WARN_ON(पढ़ोl_relaxed_poll_समयout(addr, reg, reg & lock, 100, 70000));
पूर्ण

/*
 * This घड़ी notअगरier is called when the frequency of a PLL घड़ी is
 * changed. In common PLL designs, changes to the भागiders take effect
 * almost immediately, जबतक changes to the multipliers (implemented
 * as भागiders in the feedback loop) take a few cycles to work पूर्णांकo
 * the feedback loop क्रम the PLL to stablize.
 *
 * Someबार when the PLL घड़ी rate is changed, the decrease in the
 * भागider is too much क्रम the decrease in the multiplier to catch up.
 * The PLL घड़ी rate will spike, and in some हालs, might lock up
 * completely.
 *
 * This notअगरier callback will gate and then ungate the घड़ी,
 * effectively resetting it, so it proceeds to work. Care must be
 * taken to reparent consumers to other temporary घड़ीs during the
 * rate change, and that this notअगरier callback must be the first
 * to be रेजिस्टरed.
 */
अटल पूर्णांक ccu_pll_notअगरier_cb(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा ccu_pll_nb *pll = to_ccu_pll_nb(nb);
	पूर्णांक ret = 0;

	अगर (event != POST_RATE_CHANGE)
		जाओ out;

	ccu_gate_helper_disable(pll->common, pll->enable);

	ret = ccu_gate_helper_enable(pll->common, pll->enable);
	अगर (ret)
		जाओ out;

	ccu_helper_रुको_क्रम_lock(pll->common, pll->lock);

out:
	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

पूर्णांक ccu_pll_notअगरier_रेजिस्टर(काष्ठा ccu_pll_nb *pll_nb)
अणु
	pll_nb->clk_nb.notअगरier_call = ccu_pll_notअगरier_cb;

	वापस clk_notअगरier_रेजिस्टर(pll_nb->common->hw.clk,
				     &pll_nb->clk_nb);
पूर्ण

पूर्णांक sunxi_ccu_probe(काष्ठा device_node *node, व्योम __iomem *reg,
		    स्थिर काष्ठा sunxi_ccu_desc *desc)
अणु
	काष्ठा ccu_reset *reset;
	पूर्णांक i, ret;

	क्रम (i = 0; i < desc->num_ccu_clks; i++) अणु
		काष्ठा ccu_common *cclk = desc->ccu_clks[i];

		अगर (!cclk)
			जारी;

		cclk->base = reg;
		cclk->lock = &ccu_lock;
	पूर्ण

	क्रम (i = 0; i < desc->hw_clks->num ; i++) अणु
		काष्ठा clk_hw *hw = desc->hw_clks->hws[i];
		स्थिर अक्षर *name;

		अगर (!hw)
			जारी;

		name = hw->init->name;
		ret = of_clk_hw_रेजिस्टर(node, hw);
		अगर (ret) अणु
			pr_err("Couldn't register clock %d - %s\n", i, name);
			जाओ err_clk_unreg;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get,
				     desc->hw_clks);
	अगर (ret)
		जाओ err_clk_unreg;

	reset = kzalloc(माप(*reset), GFP_KERNEL);
	अगर (!reset) अणु
		ret = -ENOMEM;
		जाओ err_alloc_reset;
	पूर्ण

	reset->rcdev.of_node = node;
	reset->rcdev.ops = &ccu_reset_ops;
	reset->rcdev.owner = THIS_MODULE;
	reset->rcdev.nr_resets = desc->num_resets;
	reset->base = reg;
	reset->lock = &ccu_lock;
	reset->reset_map = desc->resets;

	ret = reset_controller_रेजिस्टर(&reset->rcdev);
	अगर (ret)
		जाओ err_of_clk_unreg;

	वापस 0;

err_of_clk_unreg:
	kमुक्त(reset);
err_alloc_reset:
	of_clk_del_provider(node);
err_clk_unreg:
	जबतक (--i >= 0) अणु
		काष्ठा clk_hw *hw = desc->hw_clks->hws[i];

		अगर (!hw)
			जारी;
		clk_hw_unरेजिस्टर(hw);
	पूर्ण
	वापस ret;
पूर्ण
