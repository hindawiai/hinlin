<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Emilio Lथकpez
 * Emilio Lथकpez <emilio@elopez.com.ar>
 *
 * Copyright 2015 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/sun4i-a10-pll2.h>

#घोषणा SUN4I_PLL2_ENABLE		31

#घोषणा SUN4I_PLL2_PRE_DIV_SHIFT	0
#घोषणा SUN4I_PLL2_PRE_DIV_WIDTH	5
#घोषणा SUN4I_PLL2_PRE_DIV_MASK		GENMASK(SUN4I_PLL2_PRE_DIV_WIDTH - 1, 0)

#घोषणा SUN4I_PLL2_N_SHIFT		8
#घोषणा SUN4I_PLL2_N_WIDTH		7
#घोषणा SUN4I_PLL2_N_MASK		GENMASK(SUN4I_PLL2_N_WIDTH - 1, 0)

#घोषणा SUN4I_PLL2_POST_DIV_SHIFT	26
#घोषणा SUN4I_PLL2_POST_DIV_WIDTH	4
#घोषणा SUN4I_PLL2_POST_DIV_MASK	GENMASK(SUN4I_PLL2_POST_DIV_WIDTH - 1, 0)

#घोषणा SUN4I_PLL2_POST_DIV_VALUE	4

#घोषणा SUN4I_PLL2_OUTPUTS		4

अटल DEFINE_SPINLOCK(sun4i_a10_pll2_lock);

अटल व्योम __init sun4i_pll2_setup(काष्ठा device_node *node,
				    पूर्णांक post_भाग_offset)
अणु
	स्थिर अक्षर *clk_name = node->name, *parent;
	काष्ठा clk **clks, *base_clk, *preभाग_clk;
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा clk_multiplier *mult;
	काष्ठा clk_gate *gate;
	व्योम __iomem *reg;
	u32 val;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	clk_data = kzalloc(माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		जाओ err_unmap;

	clks = kसुस्मृति(SUN4I_PLL2_OUTPUTS, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clks)
		जाओ err_मुक्त_data;

	parent = of_clk_get_parent_name(node, 0);
	preभाग_clk = clk_रेजिस्टर_भागider(शून्य, "pll2-prediv",
					  parent, 0, reg,
					  SUN4I_PLL2_PRE_DIV_SHIFT,
					  SUN4I_PLL2_PRE_DIV_WIDTH,
					  CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
					  &sun4i_a10_pll2_lock);
	अगर (IS_ERR(preभाग_clk)) अणु
		pr_err("Couldn't register the prediv clock\n");
		जाओ err_मुक्त_array;
	पूर्ण

	/* Setup the gate part of the PLL2 */
	gate = kzalloc(माप(काष्ठा clk_gate), GFP_KERNEL);
	अगर (!gate)
		जाओ err_unरेजिस्टर_preभाग;

	gate->reg = reg;
	gate->bit_idx = SUN4I_PLL2_ENABLE;
	gate->lock = &sun4i_a10_pll2_lock;

	/* Setup the multiplier part of the PLL2 */
	mult = kzalloc(माप(काष्ठा clk_multiplier), GFP_KERNEL);
	अगर (!mult)
		जाओ err_मुक्त_gate;

	mult->reg = reg;
	mult->shअगरt = SUN4I_PLL2_N_SHIFT;
	mult->width = 7;
	mult->flags = CLK_MULTIPLIER_ZERO_BYPASS |
			CLK_MULTIPLIER_ROUND_CLOSEST;
	mult->lock = &sun4i_a10_pll2_lock;

	parent = __clk_get_name(preभाग_clk);
	base_clk = clk_रेजिस्टर_composite(शून्य, "pll2-base",
					  &parent, 1,
					  शून्य, शून्य,
					  &mult->hw, &clk_multiplier_ops,
					  &gate->hw, &clk_gate_ops,
					  CLK_SET_RATE_PARENT);
	अगर (IS_ERR(base_clk)) अणु
		pr_err("Couldn't register the base multiplier clock\n");
		जाओ err_मुक्त_multiplier;
	पूर्ण

	parent = __clk_get_name(base_clk);

	/*
	 * PLL2-1x
	 *
	 * This is supposed to have a post भागider, but we won't need
	 * to use it, we just need to initialise it to 4, and use a
	 * fixed भागider.
	 */
	val = पढ़ोl(reg);
	val &= ~(SUN4I_PLL2_POST_DIV_MASK << SUN4I_PLL2_POST_DIV_SHIFT);
	val |= (SUN4I_PLL2_POST_DIV_VALUE - post_भाग_offset) << SUN4I_PLL2_POST_DIV_SHIFT;
	ग_लिखोl(val, reg);

	of_property_पढ़ो_string_index(node, "clock-output-names",
				      SUN4I_A10_PLL2_1X, &clk_name);
	clks[SUN4I_A10_PLL2_1X] = clk_रेजिस्टर_fixed_factor(शून्य, clk_name,
							    parent,
							    CLK_SET_RATE_PARENT,
							    1,
							    SUN4I_PLL2_POST_DIV_VALUE);
	WARN_ON(IS_ERR(clks[SUN4I_A10_PLL2_1X]));

	/*
	 * PLL2-2x
	 *
	 * This घड़ी करोesn't use the post भागider, and really is just
	 * a fixed भागider from the PLL2 base घड़ी.
	 */
	of_property_पढ़ो_string_index(node, "clock-output-names",
				      SUN4I_A10_PLL2_2X, &clk_name);
	clks[SUN4I_A10_PLL2_2X] = clk_रेजिस्टर_fixed_factor(शून्य, clk_name,
							    parent,
							    CLK_SET_RATE_PARENT,
							    1, 2);
	WARN_ON(IS_ERR(clks[SUN4I_A10_PLL2_2X]));

	/* PLL2-4x */
	of_property_पढ़ो_string_index(node, "clock-output-names",
				      SUN4I_A10_PLL2_4X, &clk_name);
	clks[SUN4I_A10_PLL2_4X] = clk_रेजिस्टर_fixed_factor(शून्य, clk_name,
							    parent,
							    CLK_SET_RATE_PARENT,
							    1, 1);
	WARN_ON(IS_ERR(clks[SUN4I_A10_PLL2_4X]));

	/* PLL2-8x */
	of_property_पढ़ो_string_index(node, "clock-output-names",
				      SUN4I_A10_PLL2_8X, &clk_name);
	clks[SUN4I_A10_PLL2_8X] = clk_रेजिस्टर_fixed_factor(शून्य, clk_name,
							    parent,
							    CLK_SET_RATE_PARENT,
							    2, 1);
	WARN_ON(IS_ERR(clks[SUN4I_A10_PLL2_8X]));

	clk_data->clks = clks;
	clk_data->clk_num = SUN4I_PLL2_OUTPUTS;
	of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	वापस;

err_मुक्त_multiplier:
	kमुक्त(mult);
err_मुक्त_gate:
	kमुक्त(gate);
err_unरेजिस्टर_preभाग:
	clk_unरेजिस्टर_भागider(preभाग_clk);
err_मुक्त_array:
	kमुक्त(clks);
err_मुक्त_data:
	kमुक्त(clk_data);
err_unmap:
	iounmap(reg);
पूर्ण

अटल व्योम __init sun4i_a10_pll2_setup(काष्ठा device_node *node)
अणु
	sun4i_pll2_setup(node, 0);
पूर्ण

CLK_OF_DECLARE(sun4i_a10_pll2, "allwinner,sun4i-a10-pll2-clk",
	       sun4i_a10_pll2_setup);

अटल व्योम __init sun5i_a13_pll2_setup(काष्ठा device_node *node)
अणु
	sun4i_pll2_setup(node, 1);
पूर्ण

CLK_OF_DECLARE(sun5i_a13_pll2, "allwinner,sun5i-a13-pll2-clk",
	       sun5i_a13_pll2_setup);
