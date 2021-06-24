<शैली गुरु>
/*
 * OMAP APLL घड़ी support
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * J Keerthy <j-keerthy@ti.com>
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
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/log2.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>
#समावेश <linux/delay.h>

#समावेश "clock.h"

#घोषणा APLL_FORCE_LOCK 0x1
#घोषणा APLL_AUTO_IDLE	0x2
#घोषणा MAX_APLL_WAIT_TRIES		1000000

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल पूर्णांक dra7_apll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	पूर्णांक r = 0, i = 0;
	काष्ठा dpll_data *ad;
	स्थिर अक्षर *clk_name;
	u8 state = 1;
	u32 v;

	ad = clk->dpll_data;
	अगर (!ad)
		वापस -EINVAL;

	clk_name = clk_hw_get_name(&clk->hw);

	state <<= __ffs(ad->idlest_mask);

	/* Check is alपढ़ोy locked */
	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->idlest_reg);

	अगर ((v & ad->idlest_mask) == state)
		वापस r;

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->control_reg);
	v &= ~ad->enable_mask;
	v |= APLL_FORCE_LOCK << __ffs(ad->enable_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &ad->control_reg);

	state <<= __ffs(ad->idlest_mask);

	जबतक (1) अणु
		v = ti_clk_ll_ops->clk_पढ़ोl(&ad->idlest_reg);
		अगर ((v & ad->idlest_mask) == state)
			अवरोध;
		अगर (i > MAX_APLL_WAIT_TRIES)
			अवरोध;
		i++;
		udelay(1);
	पूर्ण

	अगर (i == MAX_APLL_WAIT_TRIES) अणु
		pr_warn("clock: %s failed transition to '%s'\n",
			clk_name, (state) ? "locked" : "bypassed");
		r = -EBUSY;
	पूर्ण अन्यथा
		pr_debug("clock: %s transition to '%s' in %d loops\n",
			 clk_name, (state) ? "locked" : "bypassed", i);

	वापस r;
पूर्ण

अटल व्योम dra7_apll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *ad;
	u8 state = 1;
	u32 v;

	ad = clk->dpll_data;

	state <<= __ffs(ad->idlest_mask);

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->control_reg);
	v &= ~ad->enable_mask;
	v |= APLL_AUTO_IDLE << __ffs(ad->enable_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &ad->control_reg);
पूर्ण

अटल पूर्णांक dra7_apll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *ad;
	u32 v;

	ad = clk->dpll_data;

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->control_reg);
	v &= ad->enable_mask;

	v >>= __ffs(ad->enable_mask);

	वापस v == APLL_AUTO_IDLE ? 0 : 1;
पूर्ण

अटल u8 dra7_init_apll_parent(काष्ठा clk_hw *hw)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops apll_ck_ops = अणु
	.enable		= &dra7_apll_enable,
	.disable	= &dra7_apll_disable,
	.is_enabled	= &dra7_apll_is_enabled,
	.get_parent	= &dra7_init_apll_parent,
पूर्ण;

अटल व्योम __init omap_clk_रेजिस्टर_apll(व्योम *user,
					  काष्ठा device_node *node)
अणु
	काष्ठा clk_hw *hw = user;
	काष्ठा clk_hw_omap *clk_hw = to_clk_hw_omap(hw);
	काष्ठा dpll_data *ad = clk_hw->dpll_data;
	काष्ठा clk *clk;
	स्थिर काष्ठा clk_init_data *init = clk_hw->hw.init;

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_debug("clk-ref for %pOFn not ready, retry\n",
			 node);
		अगर (!ti_clk_retry_init(node, hw, omap_clk_रेजिस्टर_apll))
			वापस;

		जाओ cleanup;
	पूर्ण

	ad->clk_ref = __clk_get_hw(clk);

	clk = of_clk_get(node, 1);
	अगर (IS_ERR(clk)) अणु
		pr_debug("clk-bypass for %pOFn not ready, retry\n",
			 node);
		अगर (!ti_clk_retry_init(node, hw, omap_clk_रेजिस्टर_apll))
			वापस;

		जाओ cleanup;
	पूर्ण

	ad->clk_bypass = __clk_get_hw(clk);

	clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &clk_hw->hw, node->name);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		kमुक्त(init->parent_names);
		kमुक्त(init);
		वापस;
	पूर्ण

cleanup:
	kमुक्त(clk_hw->dpll_data);
	kमुक्त(init->parent_names);
	kमुक्त(init);
	kमुक्त(clk_hw);
पूर्ण

अटल व्योम __init of_dra7_apll_setup(काष्ठा device_node *node)
अणु
	काष्ठा dpll_data *ad = शून्य;
	काष्ठा clk_hw_omap *clk_hw = शून्य;
	काष्ठा clk_init_data *init = शून्य;
	स्थिर अक्षर **parent_names = शून्य;
	पूर्णांक ret;

	ad = kzalloc(माप(*ad), GFP_KERNEL);
	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	init = kzalloc(माप(*init), GFP_KERNEL);
	अगर (!ad || !clk_hw || !init)
		जाओ cleanup;

	clk_hw->dpll_data = ad;
	clk_hw->hw.init = init;

	init->name = node->name;
	init->ops = &apll_ck_ops;

	init->num_parents = of_clk_get_parent_count(node);
	अगर (init->num_parents < 1) अणु
		pr_err("dra7 apll %pOFn must have parent(s)\n", node);
		जाओ cleanup;
	पूर्ण

	parent_names = kसुस्मृति(init->num_parents, माप(अक्षर *), GFP_KERNEL);
	अगर (!parent_names)
		जाओ cleanup;

	of_clk_parent_fill(node, parent_names, init->num_parents);

	init->parent_names = parent_names;

	ret = ti_clk_get_reg_addr(node, 0, &ad->control_reg);
	ret |= ti_clk_get_reg_addr(node, 1, &ad->idlest_reg);

	अगर (ret)
		जाओ cleanup;

	ad->idlest_mask = 0x1;
	ad->enable_mask = 0x3;

	omap_clk_रेजिस्टर_apll(&clk_hw->hw, node);
	वापस;

cleanup:
	kमुक्त(parent_names);
	kमुक्त(ad);
	kमुक्त(clk_hw);
	kमुक्त(init);
पूर्ण
CLK_OF_DECLARE(dra7_apll_घड़ी, "ti,dra7-apll-clock", of_dra7_apll_setup);

#घोषणा OMAP2_EN_APLL_LOCKED	0x3
#घोषणा OMAP2_EN_APLL_STOPPED	0x0

अटल पूर्णांक omap2_apll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *ad = clk->dpll_data;
	u32 v;

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->control_reg);
	v &= ad->enable_mask;

	v >>= __ffs(ad->enable_mask);

	वापस v == OMAP2_EN_APLL_LOCKED ? 1 : 0;
पूर्ण

अटल अचिन्हित दीर्घ omap2_apll_recalc(काष्ठा clk_hw *hw,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);

	अगर (omap2_apll_is_enabled(hw))
		वापस clk->fixed_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक omap2_apll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *ad = clk->dpll_data;
	u32 v;
	पूर्णांक i = 0;

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->control_reg);
	v &= ~ad->enable_mask;
	v |= OMAP2_EN_APLL_LOCKED << __ffs(ad->enable_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &ad->control_reg);

	जबतक (1) अणु
		v = ti_clk_ll_ops->clk_पढ़ोl(&ad->idlest_reg);
		अगर (v & ad->idlest_mask)
			अवरोध;
		अगर (i > MAX_APLL_WAIT_TRIES)
			अवरोध;
		i++;
		udelay(1);
	पूर्ण

	अगर (i == MAX_APLL_WAIT_TRIES) अणु
		pr_warn("%s failed to transition to locked\n",
			clk_hw_get_name(&clk->hw));
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap2_apll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	काष्ठा dpll_data *ad = clk->dpll_data;
	u32 v;

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->control_reg);
	v &= ~ad->enable_mask;
	v |= OMAP2_EN_APLL_STOPPED << __ffs(ad->enable_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &ad->control_reg);
पूर्ण

अटल स्थिर काष्ठा clk_ops omap2_apll_ops = अणु
	.enable		= &omap2_apll_enable,
	.disable	= &omap2_apll_disable,
	.is_enabled	= &omap2_apll_is_enabled,
	.recalc_rate	= &omap2_apll_recalc,
पूर्ण;

अटल व्योम omap2_apll_set_स्वतःidle(काष्ठा clk_hw_omap *clk, u32 val)
अणु
	काष्ठा dpll_data *ad = clk->dpll_data;
	u32 v;

	v = ti_clk_ll_ops->clk_पढ़ोl(&ad->स्वतःidle_reg);
	v &= ~ad->स्वतःidle_mask;
	v |= val << __ffs(ad->स्वतःidle_mask);
	ti_clk_ll_ops->clk_ग_लिखोl(v, &ad->control_reg);
पूर्ण

#घोषणा OMAP2_APLL_AUTOIDLE_LOW_POWER_STOP	0x3
#घोषणा OMAP2_APLL_AUTOIDLE_DISABLE		0x0

अटल व्योम omap2_apll_allow_idle(काष्ठा clk_hw_omap *clk)
अणु
	omap2_apll_set_स्वतःidle(clk, OMAP2_APLL_AUTOIDLE_LOW_POWER_STOP);
पूर्ण

अटल व्योम omap2_apll_deny_idle(काष्ठा clk_hw_omap *clk)
अणु
	omap2_apll_set_स्वतःidle(clk, OMAP2_APLL_AUTOIDLE_DISABLE);
पूर्ण

अटल स्थिर काष्ठा clk_hw_omap_ops omap2_apll_hwops = अणु
	.allow_idle	= &omap2_apll_allow_idle,
	.deny_idle	= &omap2_apll_deny_idle,
पूर्ण;

अटल व्योम __init of_omap2_apll_setup(काष्ठा device_node *node)
अणु
	काष्ठा dpll_data *ad = शून्य;
	काष्ठा clk_hw_omap *clk_hw = शून्य;
	काष्ठा clk_init_data *init = शून्य;
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name;
	u32 val;
	पूर्णांक ret;

	ad = kzalloc(माप(*ad), GFP_KERNEL);
	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	init = kzalloc(माप(*init), GFP_KERNEL);

	अगर (!ad || !clk_hw || !init)
		जाओ cleanup;

	clk_hw->dpll_data = ad;
	clk_hw->hw.init = init;
	init->ops = &omap2_apll_ops;
	init->name = node->name;
	clk_hw->ops = &omap2_apll_hwops;

	init->num_parents = of_clk_get_parent_count(node);
	अगर (init->num_parents != 1) अणु
		pr_err("%pOFn must have one parent\n", node);
		जाओ cleanup;
	पूर्ण

	parent_name = of_clk_get_parent_name(node, 0);
	init->parent_names = &parent_name;

	अगर (of_property_पढ़ो_u32(node, "ti,clock-frequency", &val)) अणु
		pr_err("%pOFn missing clock-frequency\n", node);
		जाओ cleanup;
	पूर्ण
	clk_hw->fixed_rate = val;

	अगर (of_property_पढ़ो_u32(node, "ti,bit-shift", &val)) अणु
		pr_err("%pOFn missing bit-shift\n", node);
		जाओ cleanup;
	पूर्ण

	clk_hw->enable_bit = val;
	ad->enable_mask = 0x3 << val;
	ad->स्वतःidle_mask = 0x3 << val;

	अगर (of_property_पढ़ो_u32(node, "ti,idlest-shift", &val)) अणु
		pr_err("%pOFn missing idlest-shift\n", node);
		जाओ cleanup;
	पूर्ण

	ad->idlest_mask = 1 << val;

	ret = ti_clk_get_reg_addr(node, 0, &ad->control_reg);
	ret |= ti_clk_get_reg_addr(node, 1, &ad->स्वतःidle_reg);
	ret |= ti_clk_get_reg_addr(node, 2, &ad->idlest_reg);

	अगर (ret)
		जाओ cleanup;

	clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &clk_hw->hw, node->name);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		kमुक्त(init);
		वापस;
	पूर्ण
cleanup:
	kमुक्त(ad);
	kमुक्त(clk_hw);
	kमुक्त(init);
पूर्ण
CLK_OF_DECLARE(omap2_apll_घड़ी, "ti,omap2-apll-clock",
	       of_omap2_apll_setup);
