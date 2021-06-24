<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 *
 * Allwinner A80 CPUS घड़ी driver
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

अटल DEFINE_SPINLOCK(sun9i_a80_cpus_lock);

/**
 * sun9i_a80_cpus_clk_setup() - Setup function क्रम a80 cpus composite clk
 */

#घोषणा SUN9I_CPUS_MAX_PARENTS		4
#घोषणा SUN9I_CPUS_MUX_PARENT_PLL4	3
#घोषणा SUN9I_CPUS_MUX_SHIFT		16
#घोषणा SUN9I_CPUS_MUX_MASK		GENMASK(17, 16)
#घोषणा SUN9I_CPUS_MUX_GET_PARENT(reg)	((reg & SUN9I_CPUS_MUX_MASK) >> \
						SUN9I_CPUS_MUX_SHIFT)

#घोषणा SUN9I_CPUS_DIV_SHIFT		4
#घोषणा SUN9I_CPUS_DIV_MASK		GENMASK(5, 4)
#घोषणा SUN9I_CPUS_DIV_GET(reg)		((reg & SUN9I_CPUS_DIV_MASK) >> \
						SUN9I_CPUS_DIV_SHIFT)
#घोषणा SUN9I_CPUS_DIV_SET(reg, भाग)	((reg & ~SUN9I_CPUS_DIV_MASK) | \
						(भाग << SUN9I_CPUS_DIV_SHIFT))
#घोषणा SUN9I_CPUS_PLL4_DIV_SHIFT	8
#घोषणा SUN9I_CPUS_PLL4_DIV_MASK	GENMASK(12, 8)
#घोषणा SUN9I_CPUS_PLL4_DIV_GET(reg)	((reg & SUN9I_CPUS_PLL4_DIV_MASK) >> \
						SUN9I_CPUS_PLL4_DIV_SHIFT)
#घोषणा SUN9I_CPUS_PLL4_DIV_SET(reg, भाग) ((reg & ~SUN9I_CPUS_PLL4_DIV_MASK) | \
						(भाग << SUN9I_CPUS_PLL4_DIV_SHIFT))

काष्ठा sun9i_a80_cpus_clk अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
पूर्ण;

#घोषणा to_sun9i_a80_cpus_clk(_hw) container_of(_hw, काष्ठा sun9i_a80_cpus_clk, hw)

अटल अचिन्हित दीर्घ sun9i_a80_cpus_clk_recalc_rate(काष्ठा clk_hw *hw,
						    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun9i_a80_cpus_clk *cpus = to_sun9i_a80_cpus_clk(hw);
	अचिन्हित दीर्घ rate;
	u32 reg;

	/* Fetch the रेजिस्टर value */
	reg = पढ़ोl(cpus->reg);

	/* apply pre-भागider first अगर parent is pll4 */
	अगर (SUN9I_CPUS_MUX_GET_PARENT(reg) == SUN9I_CPUS_MUX_PARENT_PLL4)
		parent_rate /= SUN9I_CPUS_PLL4_DIV_GET(reg) + 1;

	/* clk भागider */
	rate = parent_rate / (SUN9I_CPUS_DIV_GET(reg) + 1);

	वापस rate;
पूर्ण

अटल दीर्घ sun9i_a80_cpus_clk_round(अचिन्हित दीर्घ rate, u8 *भागp, u8 *pre_भागp,
				     u8 parent, अचिन्हित दीर्घ parent_rate)
अणु
	u8 भाग, pre_भाग = 1;

	/*
	 * घड़ी can only भागide, so we will never be able to achieve
	 * frequencies higher than the parent frequency
	 */
	अगर (parent_rate && rate > parent_rate)
		rate = parent_rate;

	भाग = DIV_ROUND_UP(parent_rate, rate);

	/* calculate pre-भागider अगर parent is pll4 */
	अगर (parent == SUN9I_CPUS_MUX_PARENT_PLL4 && भाग > 4) अणु
		/* pre-भागider is 1 ~ 32 */
		अगर (भाग < 32) अणु
			pre_भाग = भाग;
			भाग = 1;
		पूर्ण अन्यथा अगर (भाग < 64) अणु
			pre_भाग = DIV_ROUND_UP(भाग, 2);
			भाग = 2;
		पूर्ण अन्यथा अगर (भाग < 96) अणु
			pre_भाग = DIV_ROUND_UP(भाग, 3);
			भाग = 3;
		पूर्ण अन्यथा अणु
			pre_भाग = DIV_ROUND_UP(भाग, 4);
			भाग = 4;
		पूर्ण
	पूर्ण

	/* we were asked to pass back भागider values */
	अगर (भागp) अणु
		*भागp = भाग - 1;
		*pre_भागp = pre_भाग - 1;
	पूर्ण

	वापस parent_rate / pre_भाग / भाग;
पूर्ण

अटल पूर्णांक sun9i_a80_cpus_clk_determine_rate(काष्ठा clk_hw *clk,
					     काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *parent, *best_parent = शून्य;
	पूर्णांक i, num_parents;
	अचिन्हित दीर्घ parent_rate, best = 0, child_rate, best_child_rate = 0;
	अचिन्हित दीर्घ rate = req->rate;

	/* find the parent that can help provide the fastest rate <= rate */
	num_parents = clk_hw_get_num_parents(clk);
	क्रम (i = 0; i < num_parents; i++) अणु
		parent = clk_hw_get_parent_by_index(clk, i);
		अगर (!parent)
			जारी;
		अगर (clk_hw_get_flags(clk) & CLK_SET_RATE_PARENT)
			parent_rate = clk_hw_round_rate(parent, rate);
		अन्यथा
			parent_rate = clk_hw_get_rate(parent);

		child_rate = sun9i_a80_cpus_clk_round(rate, शून्य, शून्य, i,
						      parent_rate);

		अगर (child_rate <= rate && child_rate > best_child_rate) अणु
			best_parent = parent;
			best = parent_rate;
			best_child_rate = child_rate;
		पूर्ण
	पूर्ण

	अगर (!best_parent)
		वापस -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best;
	req->rate = best_child_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक sun9i_a80_cpus_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun9i_a80_cpus_clk *cpus = to_sun9i_a80_cpus_clk(hw);
	अचिन्हित दीर्घ flags;
	u8 भाग, pre_भाग, parent;
	u32 reg;

	spin_lock_irqsave(&sun9i_a80_cpus_lock, flags);

	reg = पढ़ोl(cpus->reg);

	/* need to know which parent is used to apply pre-भागider */
	parent = SUN9I_CPUS_MUX_GET_PARENT(reg);
	sun9i_a80_cpus_clk_round(rate, &भाग, &pre_भाग, parent, parent_rate);

	reg = SUN9I_CPUS_DIV_SET(reg, भाग);
	reg = SUN9I_CPUS_PLL4_DIV_SET(reg, pre_भाग);
	ग_लिखोl(reg, cpus->reg);

	spin_unlock_irqrestore(&sun9i_a80_cpus_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sun9i_a80_cpus_clk_ops = अणु
	.determine_rate	= sun9i_a80_cpus_clk_determine_rate,
	.recalc_rate	= sun9i_a80_cpus_clk_recalc_rate,
	.set_rate	= sun9i_a80_cpus_clk_set_rate,
पूर्ण;

अटल व्योम sun9i_a80_cpus_setup(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parents[SUN9I_CPUS_MAX_PARENTS];
	काष्ठा resource res;
	काष्ठा sun9i_a80_cpus_clk *cpus;
	काष्ठा clk_mux *mux;
	काष्ठा clk *clk;
	पूर्णांक ret;

	cpus = kzalloc(माप(*cpus), GFP_KERNEL);
	अगर (!cpus)
		वापस;

	cpus->reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(cpus->reg))
		जाओ err_मुक्त_cpus;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	/* we have a mux, we will have >1 parents */
	ret = of_clk_parent_fill(node, parents, SUN9I_CPUS_MAX_PARENTS);

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		जाओ err_unmap;

	/* set up घड़ी properties */
	mux->reg = cpus->reg;
	mux->shअगरt = SUN9I_CPUS_MUX_SHIFT;
	/* un-shअगरted mask is what mux_clk expects */
	mux->mask = SUN9I_CPUS_MUX_MASK >> SUN9I_CPUS_MUX_SHIFT;
	mux->lock = &sun9i_a80_cpus_lock;

	clk = clk_रेजिस्टर_composite(शून्य, clk_name, parents, ret,
				     &mux->hw, &clk_mux_ops,
				     &cpus->hw, &sun9i_a80_cpus_clk_ops,
				     शून्य, शून्य, 0);
	अगर (IS_ERR(clk))
		जाओ err_मुक्त_mux;

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret)
		जाओ err_unरेजिस्टर;

	वापस;

err_unरेजिस्टर:
	clk_unरेजिस्टर(clk);
err_मुक्त_mux:
	kमुक्त(mux);
err_unmap:
	iounmap(cpus->reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
err_मुक्त_cpus:
	kमुक्त(cpus);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_cpus, "allwinner,sun9i-a80-cpus-clk",
	       sun9i_a80_cpus_setup);
