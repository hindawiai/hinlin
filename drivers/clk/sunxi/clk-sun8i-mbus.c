<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_address.h>

#घोषणा SUN8I_MBUS_ENABLE	31
#घोषणा SUN8I_MBUS_MUX_SHIFT	24
#घोषणा SUN8I_MBUS_MUX_MASK	0x3
#घोषणा SUN8I_MBUS_DIV_SHIFT	0
#घोषणा SUN8I_MBUS_DIV_WIDTH	3
#घोषणा SUN8I_MBUS_MAX_PARENTS	4

अटल DEFINE_SPINLOCK(sun8i_a23_mbus_lock);

अटल व्योम __init sun8i_a23_mbus_setup(काष्ठा device_node *node)
अणु
	पूर्णांक num_parents = of_clk_get_parent_count(node);
	स्थिर अक्षर **parents;
	स्थिर अक्षर *clk_name = node->name;
	काष्ठा resource res;
	काष्ठा clk_भागider *भाग;
	काष्ठा clk_gate *gate;
	काष्ठा clk_mux *mux;
	काष्ठा clk *clk;
	व्योम __iomem *reg;
	पूर्णांक err;

	parents = kसुस्मृति(num_parents, माप(*parents), GFP_KERNEL);
	अगर (!parents)
		वापस;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("Could not get registers for sun8i-mbus-clk\n");
		जाओ err_मुक्त_parents;
	पूर्ण

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		जाओ err_unmap;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		जाओ err_मुक्त_भाग;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		जाओ err_मुक्त_mux;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	of_clk_parent_fill(node, parents, num_parents);

	gate->reg = reg;
	gate->bit_idx = SUN8I_MBUS_ENABLE;
	gate->lock = &sun8i_a23_mbus_lock;

	भाग->reg = reg;
	भाग->shअगरt = SUN8I_MBUS_DIV_SHIFT;
	भाग->width = SUN8I_MBUS_DIV_WIDTH;
	भाग->lock = &sun8i_a23_mbus_lock;

	mux->reg = reg;
	mux->shअगरt = SUN8I_MBUS_MUX_SHIFT;
	mux->mask = SUN8I_MBUS_MUX_MASK;
	mux->lock = &sun8i_a23_mbus_lock;

	/* The MBUS घड़ीs needs to be always enabled */
	clk = clk_रेजिस्टर_composite(शून्य, clk_name, parents, num_parents,
				     &mux->hw, &clk_mux_ops,
				     &भाग->hw, &clk_भागider_ops,
				     &gate->hw, &clk_gate_ops,
				     CLK_IS_CRITICAL);
	अगर (IS_ERR(clk))
		जाओ err_मुक्त_gate;

	err = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (err)
		जाओ err_unरेजिस्टर_clk;

	kमुक्त(parents); /* parents is deep copied */

	वापस;

err_unरेजिस्टर_clk:
	/* TODO: The composite घड़ी stuff will leak a bit here. */
	clk_unरेजिस्टर(clk);
err_मुक्त_gate:
	kमुक्त(gate);
err_मुक्त_mux:
	kमुक्त(mux);
err_मुक्त_भाग:
	kमुक्त(भाग);
err_unmap:
	iounmap(reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
err_मुक्त_parents:
	kमुक्त(parents);
पूर्ण
CLK_OF_DECLARE(sun8i_a23_mbus, "allwinner,sun8i-a23-mbus-clk", sun8i_a23_mbus_setup);
