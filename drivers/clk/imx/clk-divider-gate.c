<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018 NXP.
 *   Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश "clk.h"

काष्ठा clk_भागider_gate अणु
	काष्ठा clk_भागider भागider;
	u32 cached_val;
पूर्ण;

अटल अंतरभूत काष्ठा clk_भागider_gate *to_clk_भागider_gate(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);

	वापस container_of(भाग, काष्ठा clk_भागider_gate, भागider);
पूर्ण

अटल अचिन्हित दीर्घ clk_भागider_gate_recalc_rate_ro(काष्ठा clk_hw *hw,
						     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(भाग->reg) >> भाग->shअगरt;
	val &= clk_भाग_mask(भाग->width);
	अगर (!val)
		वापस 0;

	वापस भागider_recalc_rate(hw, parent_rate, val, भाग->table,
				   भाग->flags, भाग->width);
पूर्ण

अटल अचिन्हित दीर्घ clk_भागider_gate_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider_gate *भाग_gate = to_clk_भागider_gate(hw);
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(भाग->lock, flags);

	अगर (!clk_hw_is_enabled(hw)) अणु
		val = भाग_gate->cached_val;
	पूर्ण अन्यथा अणु
		val = पढ़ोl(भाग->reg) >> भाग->shअगरt;
		val &= clk_भाग_mask(भाग->width);
	पूर्ण

	spin_unlock_irqrestore(भाग->lock, flags);

	अगर (!val)
		वापस 0;

	वापस भागider_recalc_rate(hw, parent_rate, val, भाग->table,
				   भाग->flags, भाग->width);
पूर्ण

अटल दीर्घ clk_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate)
अणु
	वापस clk_भागider_ops.round_rate(hw, rate, prate);
पूर्ण

अटल पूर्णांक clk_भागider_gate_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider_gate *भाग_gate = to_clk_भागider_gate(hw);
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक value;
	u32 val;

	value = भागider_get_val(rate, parent_rate, भाग->table,
				भाग->width, भाग->flags);
	अगर (value < 0)
		वापस value;

	spin_lock_irqsave(भाग->lock, flags);

	अगर (clk_hw_is_enabled(hw)) अणु
		val = पढ़ोl(भाग->reg);
		val &= ~(clk_भाग_mask(भाग->width) << भाग->shअगरt);
		val |= (u32)value << भाग->shअगरt;
		ग_लिखोl(val, भाग->reg);
	पूर्ण अन्यथा अणु
		भाग_gate->cached_val = value;
	पूर्ण

	spin_unlock_irqrestore(भाग->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_भागider_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider_gate *भाग_gate = to_clk_भागider_gate(hw);
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!भाग_gate->cached_val) अणु
		pr_err("%s: no valid preset rate\n", clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(भाग->lock, flags);
	/* restore भाग val */
	val = पढ़ोl(भाग->reg);
	val |= भाग_gate->cached_val << भाग->shअगरt;
	ग_लिखोl(val, भाग->reg);

	spin_unlock_irqrestore(भाग->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम clk_भागider_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider_gate *भाग_gate = to_clk_भागider_gate(hw);
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(भाग->lock, flags);

	/* store the current भाग val */
	val = पढ़ोl(भाग->reg) >> भाग->shअगरt;
	val &= clk_भाग_mask(भाग->width);
	भाग_gate->cached_val = val;
	ग_लिखोl(0, भाग->reg);

	spin_unlock_irqrestore(भाग->lock, flags);
पूर्ण

अटल पूर्णांक clk_भागider_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	u32 val;

	val = पढ़ोl(भाग->reg) >> भाग->shअगरt;
	val &= clk_भाग_mask(भाग->width);

	वापस val ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_भागider_gate_ro_ops = अणु
	.recalc_rate = clk_भागider_gate_recalc_rate_ro,
	.round_rate = clk_भागider_round_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_भागider_gate_ops = अणु
	.recalc_rate = clk_भागider_gate_recalc_rate,
	.round_rate = clk_भागider_round_rate,
	.set_rate = clk_भागider_gate_set_rate,
	.enable = clk_भागider_enable,
	.disable = clk_भागider_disable,
	.is_enabled = clk_भागider_is_enabled,
पूर्ण;

/*
 * NOTE: In order to reuse the most code from the common भागider,
 * we also design our भागider following the way that provids an extra
 * clk_भागider_flags, however it's fixed to CLK_DIVIDER_ONE_BASED by
 * शेष as our HW is. Besides that it supports only CLK_DIVIDER_READ_ONLY
 * flag which can be specअगरied by user flexibly.
 */
काष्ठा clk_hw *imx_clk_hw_भागider_gate(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				    अचिन्हित दीर्घ flags, व्योम __iomem *reg,
				    u8 shअगरt, u8 width, u8 clk_भागider_flags,
				    स्थिर काष्ठा clk_भाग_प्रकारable *table,
				    spinlock_t *lock)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_भागider_gate *भाग_gate;
	काष्ठा clk_hw *hw;
	u32 val;
	पूर्णांक ret;

	भाग_gate  = kzalloc(माप(*भाग_gate), GFP_KERNEL);
	अगर (!भाग_gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	अगर (clk_भागider_flags & CLK_DIVIDER_READ_ONLY)
		init.ops = &clk_भागider_gate_ro_ops;
	अन्यथा
		init.ops = &clk_भागider_gate_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	भाग_gate->भागider.reg = reg;
	भाग_gate->भागider.shअगरt = shअगरt;
	भाग_gate->भागider.width = width;
	भाग_gate->भागider.lock = lock;
	भाग_gate->भागider.table = table;
	भाग_gate->भागider.hw.init = &init;
	भाग_gate->भागider.flags = CLK_DIVIDER_ONE_BASED | clk_भागider_flags;
	/* cache gate status */
	val = पढ़ोl(reg) >> shअगरt;
	val &= clk_भाग_mask(width);
	भाग_gate->cached_val = val;

	hw = &भाग_gate->भागider.hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(भाग_gate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
