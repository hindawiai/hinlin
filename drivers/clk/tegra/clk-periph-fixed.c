<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>

#समावेश "clk.h"

अटल अंतरभूत काष्ठा tegra_clk_periph_fixed *
to_tegra_clk_periph_fixed(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा tegra_clk_periph_fixed, hw);
पूर्ण

अटल पूर्णांक tegra_clk_periph_fixed_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph_fixed *fixed = to_tegra_clk_periph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32), value;

	value = पढ़ोl(fixed->base + fixed->regs->enb_reg);
	अगर (value & mask) अणु
		value = पढ़ोl(fixed->base + fixed->regs->rst_reg);
		अगर ((value & mask) == 0)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_clk_periph_fixed_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph_fixed *fixed = to_tegra_clk_periph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32);

	ग_लिखोl(mask, fixed->base + fixed->regs->enb_set_reg);

	वापस 0;
पूर्ण

अटल व्योम tegra_clk_periph_fixed_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_periph_fixed *fixed = to_tegra_clk_periph_fixed(hw);
	u32 mask = 1 << (fixed->num % 32);

	ग_लिखोl(mask, fixed->base + fixed->regs->enb_clr_reg);
पूर्ण

अटल अचिन्हित दीर्घ
tegra_clk_periph_fixed_recalc_rate(काष्ठा clk_hw *hw,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_periph_fixed *fixed = to_tegra_clk_periph_fixed(hw);
	अचिन्हित दीर्घ दीर्घ rate;

	rate = (अचिन्हित दीर्घ दीर्घ)parent_rate * fixed->mul;
	करो_भाग(rate, fixed->भाग);

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_periph_fixed_ops = अणु
	.is_enabled = tegra_clk_periph_fixed_is_enabled,
	.enable = tegra_clk_periph_fixed_enable,
	.disable = tegra_clk_periph_fixed_disable,
	.recalc_rate = tegra_clk_periph_fixed_recalc_rate,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_periph_fixed(स्थिर अक्षर *name,
					    स्थिर अक्षर *parent,
					    अचिन्हित दीर्घ flags,
					    व्योम __iomem *base,
					    अचिन्हित पूर्णांक mul,
					    अचिन्हित पूर्णांक भाग,
					    अचिन्हित पूर्णांक num)
अणु
	स्थिर काष्ठा tegra_clk_periph_regs *regs;
	काष्ठा tegra_clk_periph_fixed *fixed;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	regs = get_reg_bank(num);
	अगर (!regs)
		वापस ERR_PTR(-EINVAL);

	fixed = kzalloc(माप(*fixed), GFP_KERNEL);
	अगर (!fixed)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags;
	init.parent_names = parent ? &parent : शून्य;
	init.num_parents = parent ? 1 : 0;
	init.ops = &tegra_clk_periph_fixed_ops;

	fixed->base = base;
	fixed->regs = regs;
	fixed->mul = mul;
	fixed->भाग = भाग;
	fixed->num = num;

	fixed->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &fixed->hw);
	अगर (IS_ERR(clk))
		kमुक्त(fixed);

	वापस clk;
पूर्ण
