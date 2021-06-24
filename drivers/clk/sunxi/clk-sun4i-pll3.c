<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा SUN4I_A10_PLL3_GATE_BIT	31
#घोषणा SUN4I_A10_PLL3_DIV_WIDTH	7
#घोषणा SUN4I_A10_PLL3_DIV_SHIFT	0

अटल DEFINE_SPINLOCK(sun4i_a10_pll3_lock);

अटल व्योम __init sun4i_a10_pll3_setup(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *clk_name = node->name, *parent;
	काष्ठा clk_multiplier *mult;
	काष्ठा clk_gate *gate;
	काष्ठा resource res;
	व्योम __iomem *reg;
	काष्ठा clk *clk;
	पूर्णांक ret;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	parent = of_clk_get_parent_name(node, 0);

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%s: Could not map the clock registers\n", clk_name);
		वापस;
	पूर्ण

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		जाओ err_unmap;

	gate->reg = reg;
	gate->bit_idx = SUN4I_A10_PLL3_GATE_BIT;
	gate->lock = &sun4i_a10_pll3_lock;

	mult = kzalloc(माप(*mult), GFP_KERNEL);
	अगर (!mult)
		जाओ err_मुक्त_gate;

	mult->reg = reg;
	mult->shअगरt = SUN4I_A10_PLL3_DIV_SHIFT;
	mult->width = SUN4I_A10_PLL3_DIV_WIDTH;
	mult->lock = &sun4i_a10_pll3_lock;

	clk = clk_रेजिस्टर_composite(शून्य, clk_name,
				     &parent, 1,
				     शून्य, शून्य,
				     &mult->hw, &clk_multiplier_ops,
				     &gate->hw, &clk_gate_ops,
				     0);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: Couldn't register the clock\n", clk_name);
		जाओ err_मुक्त_mult;
	पूर्ण

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret) अणु
		pr_err("%s: Couldn't register DT provider\n",
		       clk_name);
		जाओ err_clk_unरेजिस्टर;
	पूर्ण

	वापस;

err_clk_unरेजिस्टर:
	clk_unरेजिस्टर_composite(clk);
err_मुक्त_mult:
	kमुक्त(mult);
err_मुक्त_gate:
	kमुक्त(gate);
err_unmap:
	iounmap(reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
पूर्ण

CLK_OF_DECLARE(sun4i_a10_pll3, "allwinner,sun4i-a10-pll3-clk",
	       sun4i_a10_pll3_setup);
