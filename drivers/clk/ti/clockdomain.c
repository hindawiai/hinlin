<शैली गुरु>
/*
 * OMAP घड़ीकरोमुख्य support
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

/**
 * omap2_clkops_enable_clkdm - increment usecount on clkdm of @hw
 * @hw: काष्ठा clk_hw * of the घड़ी being enabled
 *
 * Increment the usecount of the घड़ीकरोमुख्य of the घड़ी poपूर्णांकed to
 * by @hw; अगर the usecount is 1, the घड़ीकरोमुख्य will be "enabled."
 * Only needed क्रम घड़ीs that करोn't use omap2_dflt_clk_enable() as
 * their enable function poपूर्णांकer.  Passes aदीर्घ the वापस value of
 * clkdm_clk_enable(), -EINVAL अगर @hw is not associated with a
 * घड़ीकरोमुख्य, or 0 अगर घड़ी framework-based घड़ीकरोमुख्य control is
 * not implemented.
 */
पूर्णांक omap2_clkops_enable_clkdm(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk;
	पूर्णांक ret = 0;

	clk = to_clk_hw_omap(hw);

	अगर (unlikely(!clk->clkdm)) अणु
		pr_err("%s: %s: no clkdm set ?!\n", __func__,
		       clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	अगर (ti_clk_get_features()->flags & TI_CLK_DISABLE_CLKDM_CONTROL) अणु
		pr_err("%s: %s: clkfw-based clockdomain control disabled ?!\n",
		       __func__, clk_hw_get_name(hw));
		वापस 0;
	पूर्ण

	ret = ti_clk_ll_ops->clkdm_clk_enable(clk->clkdm, hw->clk);
	WARN(ret, "%s: could not enable %s's clockdomain %s: %d\n",
	     __func__, clk_hw_get_name(hw), clk->clkdm_name, ret);

	वापस ret;
पूर्ण

/**
 * omap2_clkops_disable_clkdm - decrement usecount on clkdm of @hw
 * @hw: काष्ठा clk_hw * of the घड़ी being disabled
 *
 * Decrement the usecount of the घड़ीकरोमुख्य of the घड़ी poपूर्णांकed to
 * by @hw; अगर the usecount is 0, the घड़ीकरोमुख्य will be "disabled."
 * Only needed क्रम घड़ीs that करोn't use omap2_dflt_clk_disable() as their
 * disable function poपूर्णांकer.  No वापस value.
 */
व्योम omap2_clkops_disable_clkdm(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk;

	clk = to_clk_hw_omap(hw);

	अगर (unlikely(!clk->clkdm)) अणु
		pr_err("%s: %s: no clkdm set ?!\n", __func__,
		       clk_hw_get_name(hw));
		वापस;
	पूर्ण

	अगर (ti_clk_get_features()->flags & TI_CLK_DISABLE_CLKDM_CONTROL) अणु
		pr_err("%s: %s: clkfw-based clockdomain control disabled ?!\n",
		       __func__, clk_hw_get_name(hw));
		वापस;
	पूर्ण

	ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
पूर्ण

/**
 * omap2_init_clk_clkdm - look up a घड़ीकरोमुख्य name, store poपूर्णांकer in clk
 * @hw: Poपूर्णांकer to clk_hw_omap used to obtain OMAP घड़ी काष्ठा ptr to use
 *
 * Convert a घड़ीकरोमुख्य name stored in a काष्ठा clk 'clk' पूर्णांकo a
 * घड़ीकरोमुख्य poपूर्णांकer, and save it पूर्णांकo the काष्ठा clk.  Intended to be
 * called during clk_रेजिस्टर(). Returns 0 on success, -EERROR otherwise.
 */
पूर्णांक omap2_init_clk_clkdm(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा घड़ीकरोमुख्य *clkdm;
	स्थिर अक्षर *clk_name;

	अगर (!clk->clkdm_name)
		वापस 0;

	clk_name = __clk_get_name(hw->clk);

	clkdm = ti_clk_ll_ops->clkdm_lookup(clk->clkdm_name);
	अगर (clkdm) अणु
		pr_debug("clock: associated clk %s to clkdm %s\n",
			 clk_name, clk->clkdm_name);
		clk->clkdm = clkdm;
	पूर्ण अन्यथा अणु
		pr_debug("clock: could not associate clk %s to clkdm %s\n",
			 clk_name, clk->clkdm_name);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init of_ti_घड़ीकरोमुख्य_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_hw *clk_hw;
	स्थिर अक्षर *clkdm_name = node->name;
	पूर्णांक i;
	अचिन्हित पूर्णांक num_clks;

	num_clks = of_clk_get_parent_count(node);

	क्रम (i = 0; i < num_clks; i++) अणु
		clk = of_clk_get(node, i);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: Failed get %pOF' clock nr %d (%ld)\n",
			       __func__, node, i, PTR_ERR(clk));
			जारी;
		पूर्ण
		clk_hw = __clk_get_hw(clk);
		अगर (!omap2_clk_is_hw_omap(clk_hw)) अणु
			pr_warn("can't setup clkdm for basic clk %s\n",
				__clk_get_name(clk));
			clk_put(clk);
			जारी;
		पूर्ण
		to_clk_hw_omap(clk_hw)->clkdm_name = clkdm_name;
		omap2_init_clk_clkdm(clk_hw);
		clk_put(clk);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_clkdm_match_table[] __initस्थिर = अणु
	अणु .compatible = "ti,clockdomain" पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 * ti_dt_घड़ीकरोमुख्यs_setup - setup device tree घड़ीकरोमुख्यs
 *
 * Initializes घड़ीकरोमुख्य nodes क्रम a SoC. This parses through all the
 * nodes with compatible = "ti,clockdomain", and add the घड़ीकरोमुख्य
 * info क्रम all the घड़ीs listed under these. This function shall be
 * called after rest of the DT घड़ी init has completed and all
 * घड़ी nodes have been रेजिस्टरed.
 */
व्योम __init ti_dt_घड़ीकरोमुख्यs_setup(व्योम)
अणु
	काष्ठा device_node *np;
	क्रम_each_matching_node(np, ti_clkdm_match_table) अणु
		of_ti_घड़ीकरोमुख्य_setup(np);
	पूर्ण
पूर्ण
