<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/device.h>

#समावेश "clk-mtk.h"
#समावेश "clk-gate.h"

काष्ठा clk_onecell_data *mtk_alloc_clk_data(अचिन्हित पूर्णांक clk_num)
अणु
	पूर्णांक i;
	काष्ठा clk_onecell_data *clk_data;

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस शून्य;

	clk_data->clks = kसुस्मृति(clk_num, माप(*clk_data->clks), GFP_KERNEL);
	अगर (!clk_data->clks)
		जाओ err_out;

	clk_data->clk_num = clk_num;

	क्रम (i = 0; i < clk_num; i++)
		clk_data->clks[i] = ERR_PTR(-ENOENT);

	वापस clk_data;
err_out:
	kमुक्त(clk_data);

	वापस शून्य;
पूर्ण

व्योम mtk_clk_रेजिस्टर_fixed_clks(स्थिर काष्ठा mtk_fixed_clk *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data)
अणु
	पूर्णांक i;
	काष्ठा clk *clk;

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा mtk_fixed_clk *rc = &clks[i];

		अगर (clk_data && !IS_ERR_OR_शून्य(clk_data->clks[rc->id]))
			जारी;

		clk = clk_रेजिस्टर_fixed_rate(शून्य, rc->name, rc->parent, 0,
					      rc->rate);

		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
					rc->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		अगर (clk_data)
			clk_data->clks[rc->id] = clk;
	पूर्ण
पूर्ण

व्योम mtk_clk_रेजिस्टर_factors(स्थिर काष्ठा mtk_fixed_factor *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data)
अणु
	पूर्णांक i;
	काष्ठा clk *clk;

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा mtk_fixed_factor *ff = &clks[i];

		अगर (clk_data && !IS_ERR_OR_शून्य(clk_data->clks[ff->id]))
			जारी;

		clk = clk_रेजिस्टर_fixed_factor(शून्य, ff->name, ff->parent_name,
				CLK_SET_RATE_PARENT, ff->mult, ff->भाग);

		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
					ff->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		अगर (clk_data)
			clk_data->clks[ff->id] = clk;
	पूर्ण
पूर्ण

पूर्णांक mtk_clk_रेजिस्टर_gates_with_dev(काष्ठा device_node *node,
		स्थिर काष्ठा mtk_gate *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data,
		काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;

	अगर (!clk_data)
		वापस -ENOMEM;

	regmap = syscon_node_to_regmap(node);
	अगर (IS_ERR(regmap)) अणु
		pr_err("Cannot find regmap for %pOF: %ld\n", node,
				PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा mtk_gate *gate = &clks[i];

		अगर (!IS_ERR_OR_शून्य(clk_data->clks[gate->id]))
			जारी;

		clk = mtk_clk_रेजिस्टर_gate(gate->name, gate->parent_name,
				regmap,
				gate->regs->set_ofs,
				gate->regs->clr_ofs,
				gate->regs->sta_ofs,
				gate->shअगरt, gate->ops, gate->flags, dev);

		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
					gate->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		clk_data->clks[gate->id] = clk;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mtk_clk_रेजिस्टर_gates(काष्ठा device_node *node,
		स्थिर काष्ठा mtk_gate *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data)
अणु
	वापस mtk_clk_रेजिस्टर_gates_with_dev(node,
		clks, num, clk_data, शून्य);
पूर्ण

काष्ठा clk *mtk_clk_रेजिस्टर_composite(स्थिर काष्ठा mtk_composite *mc,
		व्योम __iomem *base, spinlock_t *lock)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_भागider *भाग = शून्य;
	काष्ठा clk_hw *mux_hw = शून्य, *gate_hw = शून्य, *भाग_hw = शून्य;
	स्थिर काष्ठा clk_ops *mux_ops = शून्य, *gate_ops = शून्य, *भाग_ops = शून्य;
	स्थिर अक्षर * स्थिर *parent_names;
	स्थिर अक्षर *parent;
	पूर्णांक num_parents;
	पूर्णांक ret;

	अगर (mc->mux_shअगरt >= 0) अणु
		mux = kzalloc(माप(*mux), GFP_KERNEL);
		अगर (!mux)
			वापस ERR_PTR(-ENOMEM);

		mux->reg = base + mc->mux_reg;
		mux->mask = BIT(mc->mux_width) - 1;
		mux->shअगरt = mc->mux_shअगरt;
		mux->lock = lock;
		mux->flags = mc->mux_flags;
		mux_hw = &mux->hw;
		mux_ops = &clk_mux_ops;

		parent_names = mc->parent_names;
		num_parents = mc->num_parents;
	पूर्ण अन्यथा अणु
		parent = mc->parent;
		parent_names = &parent;
		num_parents = 1;
	पूर्ण

	अगर (mc->gate_shअगरt >= 0) अणु
		gate = kzalloc(माप(*gate), GFP_KERNEL);
		अगर (!gate) अणु
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

		gate->reg = base + mc->gate_reg;
		gate->bit_idx = mc->gate_shअगरt;
		gate->flags = CLK_GATE_SET_TO_DISABLE;
		gate->lock = lock;

		gate_hw = &gate->hw;
		gate_ops = &clk_gate_ops;
	पूर्ण

	अगर (mc->भागider_shअगरt >= 0) अणु
		भाग = kzalloc(माप(*भाग), GFP_KERNEL);
		अगर (!भाग) अणु
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

		भाग->reg = base + mc->भागider_reg;
		भाग->shअगरt = mc->भागider_shअगरt;
		भाग->width = mc->भागider_width;
		भाग->lock = lock;

		भाग_hw = &भाग->hw;
		भाग_ops = &clk_भागider_ops;
	पूर्ण

	clk = clk_रेजिस्टर_composite(शून्य, mc->name, parent_names, num_parents,
		mux_hw, mux_ops,
		भाग_hw, भाग_ops,
		gate_hw, gate_ops,
		mc->flags);

	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ err_out;
	पूर्ण

	वापस clk;
err_out:
	kमुक्त(भाग);
	kमुक्त(gate);
	kमुक्त(mux);

	वापस ERR_PTR(ret);
पूर्ण

व्योम mtk_clk_रेजिस्टर_composites(स्थिर काष्ठा mtk_composite *mcs,
		पूर्णांक num, व्योम __iomem *base, spinlock_t *lock,
		काष्ठा clk_onecell_data *clk_data)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा mtk_composite *mc = &mcs[i];

		अगर (clk_data && !IS_ERR_OR_शून्य(clk_data->clks[mc->id]))
			जारी;

		clk = mtk_clk_रेजिस्टर_composite(mc, base, lock);

		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
					mc->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		अगर (clk_data)
			clk_data->clks[mc->id] = clk;
	पूर्ण
पूर्ण

व्योम mtk_clk_रेजिस्टर_भागiders(स्थिर काष्ठा mtk_clk_भागider *mcds,
			पूर्णांक num, व्योम __iomem *base, spinlock_t *lock,
				काष्ठा clk_onecell_data *clk_data)
अणु
	काष्ठा clk *clk;
	पूर्णांक i;

	क्रम (i = 0; i <  num; i++) अणु
		स्थिर काष्ठा mtk_clk_भागider *mcd = &mcds[i];

		अगर (clk_data && !IS_ERR_OR_शून्य(clk_data->clks[mcd->id]))
			जारी;

		clk = clk_रेजिस्टर_भागider(शून्य, mcd->name, mcd->parent_name,
			mcd->flags, base +  mcd->भाग_reg, mcd->भाग_shअगरt,
			mcd->भाग_width, mcd->clk_भागider_flags, lock);

		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to register clk %s: %ld\n",
				mcd->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		अगर (clk_data)
			clk_data->clks[mcd->id] = clk;
	पूर्ण
पूर्ण
