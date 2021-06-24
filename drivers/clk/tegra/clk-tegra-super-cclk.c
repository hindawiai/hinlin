<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on clk-super.c
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * Based on older tegra20-cpufreq driver by Colin Cross <ccross@google.com>
 * Copyright (C) 2010 Google, Inc.
 *
 * Author: Dmitry Osipenko <digetx@gmail.com>
 * Copyright (C) 2019 GRATE-DRIVER project
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "clk.h"

#घोषणा PLLP_INDEX		4
#घोषणा PLLX_INDEX		8

#घोषणा SUPER_CDIV_ENB		BIT(31)

अटल काष्ठा tegra_clk_super_mux *cclk_super;
अटल bool cclk_on_pllx;

अटल u8 cclk_super_get_parent(काष्ठा clk_hw *hw)
अणु
	वापस tegra_clk_super_ops.get_parent(hw);
पूर्ण

अटल पूर्णांक cclk_super_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	वापस tegra_clk_super_ops.set_parent(hw, index);
पूर्ण

अटल पूर्णांक cclk_super_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	वापस tegra_clk_super_ops.set_rate(hw, rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ cclk_super_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	अगर (cclk_super_get_parent(hw) == PLLX_INDEX)
		वापस parent_rate;

	वापस tegra_clk_super_ops.recalc_rate(hw, parent_rate);
पूर्ण

अटल पूर्णांक cclk_super_determine_rate(काष्ठा clk_hw *hw,
				     काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *pllp_hw = clk_hw_get_parent_by_index(hw, PLLP_INDEX);
	काष्ठा clk_hw *pllx_hw = clk_hw_get_parent_by_index(hw, PLLX_INDEX);
	काष्ठा tegra_clk_super_mux *super = to_clk_super_mux(hw);
	अचिन्हित दीर्घ pllp_rate;
	दीर्घ rate = req->rate;

	अगर (WARN_ON_ONCE(!pllp_hw || !pllx_hw))
		वापस -EINVAL;

	/*
	 * Switch parent to PLLP क्रम all CCLK rates that are suitable क्रम PLLP.
	 * PLLX will be disabled in this हाल, saving some घातer.
	 */
	pllp_rate = clk_hw_get_rate(pllp_hw);

	अगर (rate <= pllp_rate) अणु
		अगर (super->flags & TEGRA20_SUPER_CLK)
			rate = pllp_rate;
		अन्यथा
			rate = tegra_clk_super_ops.round_rate(hw, rate,
							      &pllp_rate);

		req->best_parent_rate = pllp_rate;
		req->best_parent_hw = pllp_hw;
		req->rate = rate;
	पूर्ण अन्यथा अणु
		rate = clk_hw_round_rate(pllx_hw, rate);
		req->best_parent_rate = rate;
		req->best_parent_hw = pllx_hw;
		req->rate = rate;
	पूर्ण

	अगर (WARN_ON_ONCE(rate <= 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_cclk_super_ops = अणु
	.get_parent = cclk_super_get_parent,
	.set_parent = cclk_super_set_parent,
	.set_rate = cclk_super_set_rate,
	.recalc_rate = cclk_super_recalc_rate,
	.determine_rate = cclk_super_determine_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_cclk_super_mux_ops = अणु
	.get_parent = cclk_super_get_parent,
	.set_parent = cclk_super_set_parent,
	.determine_rate = cclk_super_determine_rate,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_super_cclk(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 clk_super_flags,
		spinlock_t *lock)
अणु
	काष्ठा tegra_clk_super_mux *super;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	u32 val;

	अगर (WARN_ON(cclk_super))
		वापस ERR_PTR(-EBUSY);

	super = kzalloc(माप(*super), GFP_KERNEL);
	अगर (!super)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	super->reg = reg;
	super->lock = lock;
	super->width = 4;
	super->flags = clk_super_flags;
	super->hw.init = &init;

	अगर (super->flags & TEGRA20_SUPER_CLK) अणु
		init.ops = &tegra_cclk_super_mux_ops;
	पूर्ण अन्यथा अणु
		init.ops = &tegra_cclk_super_ops;

		super->frac_भाग.reg = reg + 4;
		super->frac_भाग.shअगरt = 16;
		super->frac_भाग.width = 8;
		super->frac_भाग.frac_width = 1;
		super->frac_भाग.lock = lock;
		super->भाग_ops = &tegra_clk_frac_भाग_ops;
	पूर्ण

	/*
	 * Tegra30+ has the following CPUG घड़ी topology:
	 *
	 *        +---+  +-------+  +-+            +-+                +-+
	 * PLLP+->+   +->+DIVIDER+->+0|  +-------->+0|  ------------->+0|
	 *        |   |  +-------+  | |  |  +---+  | |  |             | |
	 * PLLC+->+MUX|             | +->+  | S |  | +->+             | +->+CPU
	 *  ...   |   |             | |  |  | K |  | |  |  +-------+  | |
	 * PLLX+->+-->+------------>+1|  +->+ I +->+1|  +->+ DIV2  +->+1|
	 *        +---+             +++     | P |  +++     |SKIPPER|  +++
	 *                           ^      | P |   ^      +-------+   ^
	 *                           |      | E |   |                  |
	 *                PLLX_SEL+--+      | R |   |       OVERHEAT+--+
	 *                                  +---+   |
	 *                                          |
	 *                         SUPER_CDIV_ENB+--+
	 *
	 * Tegra20 is similar, but simpler. It करोesn't have the भागider and
	 * thermal DIV2 skipper.
	 *
	 * At least क्रम now we're not going to use clock-skipper, hence let's
	 * ensure that it is disabled.
	 */
	val = पढ़ोl_relaxed(reg + 4);
	val &= ~SUPER_CDIV_ENB;
	ग_लिखोl_relaxed(val, reg + 4);

	clk = clk_रेजिस्टर(शून्य, &super->hw);
	अगर (IS_ERR(clk))
		kमुक्त(super);
	अन्यथा
		cclk_super = super;

	वापस clk;
पूर्ण

पूर्णांक tegra_cclk_pre_pllx_rate_change(व्योम)
अणु
	अगर (IS_ERR_OR_शून्य(cclk_super))
		वापस -EINVAL;

	अगर (cclk_super_get_parent(&cclk_super->hw) == PLLX_INDEX)
		cclk_on_pllx = true;
	अन्यथा
		cclk_on_pllx = false;

	/*
	 * CPU needs to be temporarily re-parented away from PLLX अगर PLLX
	 * changes its rate. PLLP is a safe parent क्रम CPU on all Tegra SoCs.
	 */
	अगर (cclk_on_pllx)
		cclk_super_set_parent(&cclk_super->hw, PLLP_INDEX);

	वापस 0;
पूर्ण

व्योम tegra_cclk_post_pllx_rate_change(व्योम)
अणु
	अगर (cclk_on_pllx)
		cclk_super_set_parent(&cclk_super->hw, PLLX_INDEX);
पूर्ण
