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

#घोषणा SUN4I_CODEC_GATE	31

अटल व्योम __init sun4i_codec_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = node->name, *parent_name;
	व्योम __iomem *reg;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	parent_name = of_clk_get_parent_name(node, 0);

	clk = clk_रेजिस्टर_gate(शून्य, clk_name, parent_name,
				CLK_SET_RATE_PARENT, reg,
				SUN4I_CODEC_GATE, 0, शून्य);

	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
पूर्ण
CLK_OF_DECLARE(sun4i_codec, "allwinner,sun4i-a10-codec-clk",
	       sun4i_codec_clk_setup);
