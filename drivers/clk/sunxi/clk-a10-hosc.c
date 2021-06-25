<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Emilio Lथकpez
 *
 * Emilio Lथकpez <emilio@elopez.com.ar>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#घोषणा SUNXI_OSC24M_GATE	0

अटल DEFINE_SPINLOCK(hosc_lock);

अटल व्योम __init sun4i_osc_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_fixed_rate *fixed;
	काष्ठा clk_gate *gate;
	स्थिर अक्षर *clk_name = node->name;
	u32 rate;

	अगर (of_property_पढ़ो_u32(node, "clock-frequency", &rate))
		वापस;

	/* allocate fixed-rate and gate घड़ी काष्ठाs */
	fixed = kzalloc(माप(काष्ठा clk_fixed_rate), GFP_KERNEL);
	अगर (!fixed)
		वापस;
	gate = kzalloc(माप(काष्ठा clk_gate), GFP_KERNEL);
	अगर (!gate)
		जाओ err_मुक्त_fixed;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	/* set up gate and fixed rate properties */
	gate->reg = of_iomap(node, 0);
	gate->bit_idx = SUNXI_OSC24M_GATE;
	gate->lock = &hosc_lock;
	fixed->fixed_rate = rate;

	clk = clk_रेजिस्टर_composite(शून्य, clk_name,
			शून्य, 0,
			शून्य, शून्य,
			&fixed->hw, &clk_fixed_rate_ops,
			&gate->hw, &clk_gate_ops, 0);

	अगर (IS_ERR(clk))
		जाओ err_मुक्त_gate;

	of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस;

err_मुक्त_gate:
	kमुक्त(gate);
err_मुक्त_fixed:
	kमुक्त(fixed);
पूर्ण
CLK_OF_DECLARE(sun4i_osc, "allwinner,sun4i-a10-osc-clk", sun4i_osc_clk_setup);
