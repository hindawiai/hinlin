<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Emilio Lथकpez
 *
 * Emilio Lथकpez <emilio@elopez.com.ar>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

अटल DEFINE_SPINLOCK(mod1_lock);

#घोषणा SUN4I_MOD1_ENABLE	31
#घोषणा SUN4I_MOD1_MUX		16
#घोषणा SUN4I_MOD1_MUX_WIDTH	2
#घोषणा SUN4I_MOD1_MAX_PARENTS	4

अटल व्योम __init sun4i_mod1_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_mux *mux;
	काष्ठा clk_gate *gate;
	स्थिर अक्षर *parents[4];
	स्थिर अक्षर *clk_name = node->name;
	व्योम __iomem *reg;
	पूर्णांक i;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		जाओ err_unmap;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		जाओ err_मुक्त_mux;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	i = of_clk_parent_fill(node, parents, SUN4I_MOD1_MAX_PARENTS);

	gate->reg = reg;
	gate->bit_idx = SUN4I_MOD1_ENABLE;
	gate->lock = &mod1_lock;
	mux->reg = reg;
	mux->shअगरt = SUN4I_MOD1_MUX;
	mux->mask = BIT(SUN4I_MOD1_MUX_WIDTH) - 1;
	mux->lock = &mod1_lock;

	clk = clk_रेजिस्टर_composite(शून्य, clk_name, parents, i,
				     &mux->hw, &clk_mux_ops,
				     शून्य, शून्य,
				     &gate->hw, &clk_gate_ops, CLK_SET_RATE_PARENT);
	अगर (IS_ERR(clk))
		जाओ err_मुक्त_gate;

	of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस;

err_मुक्त_gate:
	kमुक्त(gate);
err_मुक्त_mux:
	kमुक्त(mux);
err_unmap:
	iounmap(reg);
पूर्ण
CLK_OF_DECLARE(sun4i_mod1, "allwinner,sun4i-a10-mod1-clk",
	       sun4i_mod1_clk_setup);
