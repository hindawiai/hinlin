<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>

#समावेश "clk.h"

#घोषणा pll_out_enb(p) (BIT(p->enb_bit_idx))
#घोषणा pll_out_rst(p) (BIT(p->rst_bit_idx))

अटल पूर्णांक clk_pll_out_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll_out *pll_out = to_clk_pll_out(hw);
	u32 val = पढ़ोl_relaxed(pll_out->reg);
	पूर्णांक state;

	state = (val & pll_out_enb(pll_out)) ? 1 : 0;
	अगर (!(val & (pll_out_rst(pll_out))))
		state = 0;
	वापस state;
पूर्ण

अटल पूर्णांक clk_pll_out_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll_out *pll_out = to_clk_pll_out(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	अगर (pll_out->lock)
		spin_lock_irqsave(pll_out->lock, flags);

	val = पढ़ोl_relaxed(pll_out->reg);

	val |= (pll_out_enb(pll_out) | pll_out_rst(pll_out));

	ग_लिखोl_relaxed(val, pll_out->reg);
	udelay(2);

	अगर (pll_out->lock)
		spin_unlock_irqrestore(pll_out->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_pll_out_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_pll_out *pll_out = to_clk_pll_out(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	अगर (pll_out->lock)
		spin_lock_irqsave(pll_out->lock, flags);

	val = पढ़ोl_relaxed(pll_out->reg);

	val &= ~(pll_out_enb(pll_out) | pll_out_rst(pll_out));

	ग_लिखोl_relaxed(val, pll_out->reg);
	udelay(2);

	अगर (pll_out->lock)
		spin_unlock_irqrestore(pll_out->lock, flags);
पूर्ण

अटल व्योम tegra_clk_pll_out_restore_context(काष्ठा clk_hw *hw)
अणु
	अगर (!__clk_get_enable_count(hw->clk))
		clk_pll_out_disable(hw);
	अन्यथा
		clk_pll_out_enable(hw);
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_pll_out_ops = अणु
	.is_enabled = clk_pll_out_is_enabled,
	.enable = clk_pll_out_enable,
	.disable = clk_pll_out_disable,
	.restore_context = tegra_clk_pll_out_restore_context,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_pll_out(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *reg, u8 enb_bit_idx,
		u8 rst_bit_idx, अचिन्हित दीर्घ flags, u8 pll_out_flags,
		spinlock_t *lock)
अणु
	काष्ठा tegra_clk_pll_out *pll_out;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	pll_out = kzalloc(माप(*pll_out), GFP_KERNEL);
	अगर (!pll_out)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &tegra_clk_pll_out_ops;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);
	init.flags = flags;

	pll_out->reg = reg;
	pll_out->enb_bit_idx = enb_bit_idx;
	pll_out->rst_bit_idx = rst_bit_idx;
	pll_out->flags = pll_out_flags;
	pll_out->lock = lock;

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	pll_out->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &pll_out->hw);
	अगर (IS_ERR(clk))
		kमुक्त(pll_out);

	वापस clk;
पूर्ण
