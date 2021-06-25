<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Lucas Stach <l.stach@pengutronix.de>, Pengutronix
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश "clk.h"

काष्ठा clk_cpu अणु
	काष्ठा clk_hw	hw;
	काष्ठा clk	*भाग;
	काष्ठा clk	*mux;
	काष्ठा clk	*pll;
	काष्ठा clk	*step;
पूर्ण;

अटल अंतरभूत काष्ठा clk_cpu *to_clk_cpu(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clk_cpu, hw);
पूर्ण

अटल अचिन्हित दीर्घ clk_cpu_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_cpu *cpu = to_clk_cpu(hw);

	वापस clk_get_rate(cpu->भाग);
पूर्ण

अटल दीर्घ clk_cpu_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_cpu *cpu = to_clk_cpu(hw);

	वापस clk_round_rate(cpu->pll, rate);
पूर्ण

अटल पूर्णांक clk_cpu_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_cpu *cpu = to_clk_cpu(hw);
	पूर्णांक ret;

	/* चयन to PLL bypass घड़ी */
	ret = clk_set_parent(cpu->mux, cpu->step);
	अगर (ret)
		वापस ret;

	/* reprogram PLL */
	ret = clk_set_rate(cpu->pll, rate);
	अगर (ret) अणु
		clk_set_parent(cpu->mux, cpu->pll);
		वापस ret;
	पूर्ण
	/* चयन back to PLL घड़ी */
	clk_set_parent(cpu->mux, cpu->pll);

	/* Ensure the भागider is what we expect */
	clk_set_rate(cpu->भाग, rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_cpu_ops = अणु
	.recalc_rate	= clk_cpu_recalc_rate,
	.round_rate	= clk_cpu_round_rate,
	.set_rate	= clk_cpu_set_rate,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_cpu(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		काष्ठा clk *भाग, काष्ठा clk *mux, काष्ठा clk *pll,
		काष्ठा clk *step)
अणु
	काष्ठा clk_cpu *cpu;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	cpu = kzalloc(माप(*cpu), GFP_KERNEL);
	अगर (!cpu)
		वापस ERR_PTR(-ENOMEM);

	cpu->भाग = भाग;
	cpu->mux = mux;
	cpu->pll = pll;
	cpu->step = step;

	init.name = name;
	init.ops = &clk_cpu_ops;
	init.flags = CLK_IS_CRITICAL;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	cpu->hw.init = &init;
	hw = &cpu->hw;

	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(cpu);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(imx_clk_hw_cpu);
