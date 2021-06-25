<शैली गुरु>
/*
 * mmp gate घड़ी operation source file
 *
 * Copyright (C) 2014 Marvell
 * Chao Xie <chao.xie@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#समावेश "clk.h"

/*
 * Some घड़ीs will have mutiple bits to enable the घड़ीs, and
 * the bits to disable the घड़ी is not same as enabling bits.
 */

#घोषणा to_clk_mmp_gate(hw)	container_of(hw, काष्ठा mmp_clk_gate, hw)

अटल पूर्णांक mmp_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_gate *gate = to_clk_mmp_gate(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ rate;
	u32 पंचांगp;

	अगर (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	पंचांगp = पढ़ोl(gate->reg);
	पंचांगp &= ~gate->mask;
	पंचांगp |= gate->val_enable;
	ग_लिखोl(पंचांगp, gate->reg);

	अगर (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);

	अगर (gate->flags & MMP_CLK_GATE_NEED_DELAY) अणु
		rate = clk_hw_get_rate(hw);
		/* Need delay 2 cycles. */
		udelay(2000000/rate);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mmp_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_gate *gate = to_clk_mmp_gate(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 पंचांगp;

	अगर (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	पंचांगp = पढ़ोl(gate->reg);
	पंचांगp &= ~gate->mask;
	पंचांगp |= gate->val_disable;
	ग_लिखोl(पंचांगp, gate->reg);

	अगर (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);
पूर्ण

अटल पूर्णांक mmp_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा mmp_clk_gate *gate = to_clk_mmp_gate(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 पंचांगp;

	अगर (gate->lock)
		spin_lock_irqsave(gate->lock, flags);

	पंचांगp = पढ़ोl(gate->reg);

	अगर (gate->lock)
		spin_unlock_irqrestore(gate->lock, flags);

	वापस (पंचांगp & gate->mask) == gate->val_enable;
पूर्ण

स्थिर काष्ठा clk_ops mmp_clk_gate_ops = अणु
	.enable = mmp_clk_gate_enable,
	.disable = mmp_clk_gate_disable,
	.is_enabled = mmp_clk_gate_is_enabled,
पूर्ण;

काष्ठा clk *mmp_clk_रेजिस्टर_gate(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u32 mask, u32 val_enable, u32 val_disable,
		अचिन्हित पूर्णांक gate_flags, spinlock_t *lock)
अणु
	काष्ठा mmp_clk_gate *gate;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	/* allocate the gate */
	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &mmp_clk_gate_ops;
	init.flags = flags;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	/* काष्ठा clk_gate assignments */
	gate->reg = reg;
	gate->mask = mask;
	gate->val_enable = val_enable;
	gate->val_disable = val_disable;
	gate->flags = gate_flags;
	gate->lock = lock;
	gate->hw.init = &init;

	clk = clk_रेजिस्टर(dev, &gate->hw);

	अगर (IS_ERR(clk))
		kमुक्त(gate);

	वापस clk;
पूर्ण
