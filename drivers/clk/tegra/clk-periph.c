<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश "clk.h"

अटल u8 clk_periph_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *mux_ops = periph->mux_ops;
	काष्ठा clk_hw *mux_hw = &periph->mux.hw;

	__clk_hw_set_clk(mux_hw, hw);

	वापस mux_ops->get_parent(mux_hw);
पूर्ण

अटल पूर्णांक clk_periph_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *mux_ops = periph->mux_ops;
	काष्ठा clk_hw *mux_hw = &periph->mux.hw;

	__clk_hw_set_clk(mux_hw, hw);

	वापस mux_ops->set_parent(mux_hw, index);
पूर्ण

अटल अचिन्हित दीर्घ clk_periph_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *भाग_ops = periph->भाग_ops;
	काष्ठा clk_hw *भाग_hw = &periph->भागider.hw;

	__clk_hw_set_clk(भाग_hw, hw);

	वापस भाग_ops->recalc_rate(भाग_hw, parent_rate);
पूर्ण

अटल दीर्घ clk_periph_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *भाग_ops = periph->भाग_ops;
	काष्ठा clk_hw *भाग_hw = &periph->भागider.hw;

	__clk_hw_set_clk(भाग_hw, hw);

	वापस भाग_ops->round_rate(भाग_hw, rate, prate);
पूर्ण

अटल पूर्णांक clk_periph_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *भाग_ops = periph->भाग_ops;
	काष्ठा clk_hw *भाग_hw = &periph->भागider.hw;

	__clk_hw_set_clk(भाग_hw, hw);

	वापस भाग_ops->set_rate(भाग_hw, rate, parent_rate);
पूर्ण

अटल पूर्णांक clk_periph_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *gate_ops = periph->gate_ops;
	काष्ठा clk_hw *gate_hw = &periph->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस gate_ops->is_enabled(gate_hw);
पूर्ण

अटल पूर्णांक clk_periph_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *gate_ops = periph->gate_ops;
	काष्ठा clk_hw *gate_hw = &periph->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस gate_ops->enable(gate_hw);
पूर्ण

अटल व्योम clk_periph_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *gate_ops = periph->gate_ops;
	काष्ठा clk_hw *gate_hw = &periph->gate.hw;

	gate_ops->disable(gate_hw);
पूर्ण

अटल व्योम clk_periph_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph *periph = to_clk_periph(hw);
	स्थिर काष्ठा clk_ops *भाग_ops = periph->भाग_ops;
	काष्ठा clk_hw *भाग_hw = &periph->भागider.hw;
	पूर्णांक parent_id;

	parent_id = clk_hw_get_parent_index(hw);
	अगर (WARN_ON(parent_id < 0))
		वापस;

	अगर (!(periph->gate.flags & TEGRA_PERIPH_NO_DIV))
		भाग_ops->restore_context(भाग_hw);

	clk_periph_set_parent(hw, parent_id);
पूर्ण

स्थिर काष्ठा clk_ops tegra_clk_periph_ops = अणु
	.get_parent = clk_periph_get_parent,
	.set_parent = clk_periph_set_parent,
	.recalc_rate = clk_periph_recalc_rate,
	.round_rate = clk_periph_round_rate,
	.set_rate = clk_periph_set_rate,
	.is_enabled = clk_periph_is_enabled,
	.enable = clk_periph_enable,
	.disable = clk_periph_disable,
	.restore_context = clk_periph_restore_context,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_clk_periph_noभाग_ops = अणु
	.get_parent = clk_periph_get_parent,
	.set_parent = clk_periph_set_parent,
	.is_enabled = clk_periph_is_enabled,
	.enable = clk_periph_enable,
	.disable = clk_periph_disable,
	.restore_context = clk_periph_restore_context,
पूर्ण;

अटल स्थिर काष्ठा clk_ops tegra_clk_periph_no_gate_ops = अणु
	.get_parent = clk_periph_get_parent,
	.set_parent = clk_periph_set_parent,
	.recalc_rate = clk_periph_recalc_rate,
	.round_rate = clk_periph_round_rate,
	.set_rate = clk_periph_set_rate,
	.restore_context = clk_periph_restore_context,
पूर्ण;

अटल काष्ठा clk *_tegra_clk_रेजिस्टर_periph(स्थिर अक्षर *name,
			स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
			काष्ठा tegra_clk_periph *periph,
			व्योम __iomem *clk_base, u32 offset,
			अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	स्थिर काष्ठा tegra_clk_periph_regs *bank;
	bool भाग = !(periph->gate.flags & TEGRA_PERIPH_NO_DIV);

	अगर (periph->gate.flags & TEGRA_PERIPH_NO_DIV) अणु
		flags |= CLK_SET_RATE_PARENT;
		init.ops = &tegra_clk_periph_noभाग_ops;
	पूर्ण अन्यथा अगर (periph->gate.flags & TEGRA_PERIPH_NO_GATE)
		init.ops = &tegra_clk_periph_no_gate_ops;
	अन्यथा
		init.ops = &tegra_clk_periph_ops;

	init.name = name;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	bank = get_reg_bank(periph->gate.clk_num);
	अगर (!bank)
		वापस ERR_PTR(-EINVAL);

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	periph->hw.init = &init;
	periph->magic = TEGRA_CLK_PERIPH_MAGIC;
	periph->mux.reg = clk_base + offset;
	periph->भागider.reg = भाग ? (clk_base + offset) : शून्य;
	periph->gate.clk_base = clk_base;
	periph->gate.regs = bank;
	periph->gate.enable_refcnt = periph_clk_enb_refcnt;

	clk = clk_रेजिस्टर(शून्य, &periph->hw);
	अगर (IS_ERR(clk))
		वापस clk;

	periph->mux.hw.clk = clk;
	periph->भागider.hw.clk = भाग ? clk : शून्य;
	periph->gate.hw.clk = clk;

	वापस clk;
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_periph(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		काष्ठा tegra_clk_periph *periph, व्योम __iomem *clk_base,
		u32 offset, अचिन्हित दीर्घ flags)
अणु
	वापस _tegra_clk_रेजिस्टर_periph(name, parent_names, num_parents,
			periph, clk_base, offset, flags);
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_periph_noभाग(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		काष्ठा tegra_clk_periph *periph, व्योम __iomem *clk_base,
		u32 offset)
अणु
	periph->gate.flags |= TEGRA_PERIPH_NO_DIV;
	वापस _tegra_clk_रेजिस्टर_periph(name, parent_names, num_parents,
			periph, clk_base, offset, CLK_SET_RATE_PARENT);
पूर्ण

काष्ठा clk *tegra_clk_रेजिस्टर_periph_data(व्योम __iomem *clk_base,
					   काष्ठा tegra_periph_init_data *init)
अणु
	वापस _tegra_clk_रेजिस्टर_periph(init->name, init->p.parent_names,
					  init->num_parents, &init->periph,
					  clk_base, init->offset, init->flags);
पूर्ण
