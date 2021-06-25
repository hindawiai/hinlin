<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010-2011 Canonical Ltd <jeremy.kerr@canonical.com>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Gated घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश "clk.h"

/**
 * DOC: basic gateable घड़ी which can gate and ungate its output
 *
 * Traits of this घड़ी:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional & control gating
 * rate - inherits rate from parent.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

काष्ठा clk_gate2 अणु
	काष्ठा clk_hw hw;
	व्योम __iomem	*reg;
	u8		bit_idx;
	u8		cgr_val;
	u8		cgr_mask;
	u8		flags;
	spinlock_t	*lock;
	अचिन्हित पूर्णांक	*share_count;
पूर्ण;

#घोषणा to_clk_gate2(_hw) container_of(_hw, काष्ठा clk_gate2, hw)

अटल व्योम clk_gate2_करो_shared_clks(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा clk_gate2 *gate = to_clk_gate2(hw);
	u32 reg;

	reg = पढ़ोl(gate->reg);
	reg &= ~(gate->cgr_mask << gate->bit_idx);
	अगर (enable)
		reg |= (gate->cgr_val & gate->cgr_mask) << gate->bit_idx;
	ग_लिखोl(reg, gate->reg);
पूर्ण

अटल पूर्णांक clk_gate2_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate2 *gate = to_clk_gate2(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(gate->lock, flags);

	अगर (gate->share_count && (*gate->share_count)++ > 0)
		जाओ out;

	clk_gate2_करो_shared_clks(hw, true);
out:
	spin_unlock_irqrestore(gate->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_gate2_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate2 *gate = to_clk_gate2(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(gate->lock, flags);

	अगर (gate->share_count) अणु
		अगर (WARN_ON(*gate->share_count == 0))
			जाओ out;
		अन्यथा अगर (--(*gate->share_count) > 0)
			जाओ out;
	पूर्ण

	clk_gate2_करो_shared_clks(hw, false);
out:
	spin_unlock_irqrestore(gate->lock, flags);
पूर्ण

अटल पूर्णांक clk_gate2_reg_is_enabled(व्योम __iomem *reg, u8 bit_idx,
					u8 cgr_val, u8 cgr_mask)
अणु
	u32 val = पढ़ोl(reg);

	अगर (((val >> bit_idx) & cgr_mask) == cgr_val)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक clk_gate2_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate2 *gate = to_clk_gate2(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(gate->lock, flags);

	ret = clk_gate2_reg_is_enabled(gate->reg, gate->bit_idx,
					gate->cgr_val, gate->cgr_mask);

	spin_unlock_irqrestore(gate->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम clk_gate2_disable_unused(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate2 *gate = to_clk_gate2(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(gate->lock, flags);

	अगर (!gate->share_count || *gate->share_count == 0)
		clk_gate2_करो_shared_clks(hw, false);

	spin_unlock_irqrestore(gate->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gate2_ops = अणु
	.enable = clk_gate2_enable,
	.disable = clk_gate2_disable,
	.disable_unused = clk_gate2_disable_unused,
	.is_enabled = clk_gate2_is_enabled,
पूर्ण;

काष्ठा clk_hw *clk_hw_रेजिस्टर_gate2(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx, u8 cgr_val, u8 cgr_mask,
		u8 clk_gate2_flags, spinlock_t *lock,
		अचिन्हित पूर्णांक *share_count)
अणु
	काष्ठा clk_gate2 *gate;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	gate = kzalloc(माप(काष्ठा clk_gate2), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	/* काष्ठा clk_gate2 assignments */
	gate->reg = reg;
	gate->bit_idx = bit_idx;
	gate->cgr_val = cgr_val;
	gate->cgr_mask = cgr_mask;
	gate->flags = clk_gate2_flags;
	gate->lock = lock;
	gate->share_count = share_count;

	init.name = name;
	init.ops = &clk_gate2_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	gate->hw.init = &init;
	hw = &gate->hw;

	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(gate);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_रेजिस्टर_gate2);
