<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010-2011 Canonical Ltd <jeremy.kerr@canonical.com>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Gated घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>

/**
 * DOC: basic gatable घड़ी which can gate and ungate it's ouput
 *
 * Traits of this घड़ी:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional & control gating
 * rate - inherits rate from parent.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

अटल अंतरभूत u32 clk_gate_पढ़ोl(काष्ठा clk_gate *gate)
अणु
	अगर (gate->flags & CLK_GATE_BIG_ENDIAN)
		वापस ioपढ़ो32be(gate->reg);

	वापस पढ़ोl(gate->reg);
पूर्ण

अटल अंतरभूत व्योम clk_gate_ग_लिखोl(काष्ठा clk_gate *gate, u32 val)
अणु
	अगर (gate->flags & CLK_GATE_BIG_ENDIAN)
		ioग_लिखो32be(val, gate->reg);
	अन्यथा
		ग_लिखोl(val, gate->reg);
पूर्ण

/*
 * It works on following logic:
 *
 * For enabling घड़ी, enable = 1
 *	set2dis = 1	-> clear bit	-> set = 0
 *	set2dis = 0	-> set bit	-> set = 1
 *
 * For disabling घड़ी, enable = 0
 *	set2dis = 1	-> set bit	-> set = 1
 *	set2dis = 0	-> clear bit	-> set = 0
 *
 * So, result is always: enable xor set2dis.
 */
अटल व्योम clk_gate_endisable(काष्ठा clk_hw *hw, पूर्णांक enable)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	पूर्णांक set = gate->flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;
	अचिन्हित दीर्घ flags;
	u32 reg;

	set ^= enable;

	अगर (gate->lock)
		spin_lock_irqsave(gate->lock, flags);
	अन्यथा
		__acquire(gate->lock);

	अगर (gate->flags & CLK_GATE_HIWORD_MASK) अणु
		reg = BIT(gate->bit_idx + 16);
		अगर (set)
			reg |= BIT(gate->bit_idx);
	पूर्ण अन्यथा अणु
		reg = clk_gate_पढ़ोl(gate);

		अगर (set)
			reg |= BIT(gate->bit_idx);
		अन्यथा
			reg &= ~BIT(gate->bit_idx);
	पूर्ण

	clk_gate_ग_लिखोl(gate, reg);

	अगर (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);
	अन्यथा
		__release(gate->lock);
पूर्ण

अटल पूर्णांक clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	clk_gate_endisable(hw, 1);

	वापस 0;
पूर्ण

अटल व्योम clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	clk_gate_endisable(hw, 0);
पूर्ण

पूर्णांक clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	u32 reg;
	काष्ठा clk_gate *gate = to_clk_gate(hw);

	reg = clk_gate_पढ़ोl(gate);

	/* अगर a set bit disables this clk, flip it beक्रमe masking */
	अगर (gate->flags & CLK_GATE_SET_TO_DISABLE)
		reg ^= BIT(gate->bit_idx);

	reg &= BIT(gate->bit_idx);

	वापस reg ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_gate_is_enabled);

स्थिर काष्ठा clk_ops clk_gate_ops = अणु
	.enable = clk_gate_enable,
	.disable = clk_gate_disable,
	.is_enabled = clk_gate_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_gate_ops);

काष्ठा clk_hw *__clk_hw_रेजिस्टर_gate(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data,
		अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx,
		u8 clk_gate_flags, spinlock_t *lock)
अणु
	काष्ठा clk_gate *gate;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक ret = -EINVAL;

	अगर (clk_gate_flags & CLK_GATE_HIWORD_MASK) अणु
		अगर (bit_idx > 15) अणु
			pr_err("gate bit exceeds LOWORD field\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	/* allocate the gate */
	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_gate_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.parent_hws = parent_hw ? &parent_hw : शून्य;
	init.parent_data = parent_data;
	अगर (parent_name || parent_hw || parent_data)
		init.num_parents = 1;
	अन्यथा
		init.num_parents = 0;

	/* काष्ठा clk_gate assignments */
	gate->reg = reg;
	gate->bit_idx = bit_idx;
	gate->flags = clk_gate_flags;
	gate->lock = lock;
	gate->hw.init = &init;

	hw = &gate->hw;
	अगर (dev || !np)
		ret = clk_hw_रेजिस्टर(dev, hw);
	अन्यथा अगर (np)
		ret = of_clk_hw_रेजिस्टर(np, hw);
	अगर (ret) अणु
		kमुक्त(gate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;

पूर्ण
EXPORT_SYMBOL_GPL(__clk_hw_रेजिस्टर_gate);

काष्ठा clk *clk_रेजिस्टर_gate(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx,
		u8 clk_gate_flags, spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_gate(dev, name, parent_name, flags, reg,
				  bit_idx, clk_gate_flags, lock);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_gate);

व्योम clk_unरेजिस्टर_gate(काष्ठा clk *clk)
अणु
	काष्ठा clk_gate *gate;
	काष्ठा clk_hw *hw;

	hw = __clk_get_hw(clk);
	अगर (!hw)
		वापस;

	gate = to_clk_gate(hw);

	clk_unरेजिस्टर(clk);
	kमुक्त(gate);
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर_gate);

व्योम clk_hw_unरेजिस्टर_gate(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate;

	gate = to_clk_gate(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(gate);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर_gate);
