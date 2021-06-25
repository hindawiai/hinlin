<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Author: Pi-Cheng Chen <pi-cheng.chen@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/slab.h>

#समावेश "clk-mtk.h"
#समावेश "clk-cpumux.h"

अटल अंतरभूत काष्ठा mtk_clk_cpumux *to_mtk_clk_cpumux(काष्ठा clk_hw *_hw)
अणु
	वापस container_of(_hw, काष्ठा mtk_clk_cpumux, hw);
पूर्ण

अटल u8 clk_cpumux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_clk_cpumux *mux = to_mtk_clk_cpumux(hw);
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(mux->regmap, mux->reg, &val);

	val >>= mux->shअगरt;
	val &= mux->mask;

	वापस val;
पूर्ण

अटल पूर्णांक clk_cpumux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा mtk_clk_cpumux *mux = to_mtk_clk_cpumux(hw);
	u32 mask, val;

	val = index << mux->shअगरt;
	mask = mux->mask << mux->shअगरt;

	वापस regmap_update_bits(mux->regmap, mux->reg, mask, val);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_cpumux_ops = अणु
	.get_parent = clk_cpumux_get_parent,
	.set_parent = clk_cpumux_set_parent,
पूर्ण;

अटल काष्ठा clk *
mtk_clk_रेजिस्टर_cpumux(स्थिर काष्ठा mtk_composite *mux,
			काष्ठा regmap *regmap)
अणु
	काष्ठा mtk_clk_cpumux *cpumux;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	cpumux = kzalloc(माप(*cpumux), GFP_KERNEL);
	अगर (!cpumux)
		वापस ERR_PTR(-ENOMEM);

	init.name = mux->name;
	init.ops = &clk_cpumux_ops;
	init.parent_names = mux->parent_names;
	init.num_parents = mux->num_parents;
	init.flags = mux->flags;

	cpumux->reg = mux->mux_reg;
	cpumux->shअगरt = mux->mux_shअगरt;
	cpumux->mask = BIT(mux->mux_width) - 1;
	cpumux->regmap = regmap;
	cpumux->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &cpumux->hw);
	अगर (IS_ERR(clk))
		kमुक्त(cpumux);

	वापस clk;
पूर्ण

पूर्णांक mtk_clk_रेजिस्टर_cpumuxes(काष्ठा device_node *node,
			      स्थिर काष्ठा mtk_composite *clks, पूर्णांक num,
			      काष्ठा clk_onecell_data *clk_data)
अणु
	पूर्णांक i;
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;

	regmap = syscon_node_to_regmap(node);
	अगर (IS_ERR(regmap)) अणु
		pr_err("Cannot find regmap for %pOF: %ld\n", node,
		       PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा mtk_composite *mux = &clks[i];

		clk = mtk_clk_रेजिस्टर_cpumux(mux, regmap);
		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
			       mux->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		clk_data->clks[mux->id] = clk;
	पूर्ण

	वापस 0;
पूर्ण
