<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

अटल DEFINE_SPINLOCK(gates_lock);

अटल व्योम __init sunxi_simple_gates_setup(काष्ठा device_node *node,
					    स्थिर पूर्णांक रक्षित[],
					    पूर्णांक nरक्षित)
अणु
	काष्ठा clk_onecell_data *clk_data;
	स्थिर अक्षर *clk_parent, *clk_name;
	काष्ठा property *prop;
	काष्ठा resource res;
	व्योम __iomem *clk_reg;
	व्योम __iomem *reg;
	स्थिर __be32 *p;
	पूर्णांक number, i = 0, j;
	u8 clk_bit;
	u32 index;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	clk_parent = of_clk_get_parent_name(node, 0);

	clk_data = kदो_स्मृति(माप(काष्ठा clk_onecell_data), GFP_KERNEL);
	अगर (!clk_data)
		जाओ err_unmap;

	number = of_property_count_u32_elems(node, "clock-indices");
	of_property_पढ़ो_u32_index(node, "clock-indices", number - 1, &number);

	clk_data->clks = kसुस्मृति(number + 1, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clk_data->clks)
		जाओ err_मुक्त_data;

	of_property_क्रम_each_u32(node, "clock-indices", prop, p, index) अणु
		of_property_पढ़ो_string_index(node, "clock-output-names",
					      i, &clk_name);

		clk_reg = reg + 4 * (index / 32);
		clk_bit = index % 32;

		clk_data->clks[index] = clk_रेजिस्टर_gate(शून्य, clk_name,
							  clk_parent, 0,
							  clk_reg,
							  clk_bit,
							  0, &gates_lock);
		i++;

		अगर (IS_ERR(clk_data->clks[index])) अणु
			WARN_ON(true);
			जारी;
		पूर्ण

		क्रम (j = 0; j < nरक्षित; j++)
			अगर (रक्षित[j] == index)
				clk_prepare_enable(clk_data->clks[index]);

	पूर्ण

	clk_data->clk_num = number + 1;
	of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	वापस;

err_मुक्त_data:
	kमुक्त(clk_data);
err_unmap:
	iounmap(reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
पूर्ण

अटल व्योम __init sunxi_simple_gates_init(काष्ठा device_node *node)
अणु
	sunxi_simple_gates_setup(node, शून्य, 0);
पूर्ण

CLK_OF_DECLARE(sun4i_a10_gates, "allwinner,sun4i-a10-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun4i_a10_apb0, "allwinner,sun4i-a10-apb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun4i_a10_apb1, "allwinner,sun4i-a10-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun4i_a10_axi, "allwinner,sun4i-a10-axi-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun5i_a10s_apb0, "allwinner,sun5i-a10s-apb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun5i_a10s_apb1, "allwinner,sun5i-a10s-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun5i_a13_apb0, "allwinner,sun5i-a13-apb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun5i_a13_apb1, "allwinner,sun5i-a13-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun6i_a31_ahb1, "allwinner,sun6i-a31-ahb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun6i_a31_apb1, "allwinner,sun6i-a31-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun6i_a31_apb2, "allwinner,sun6i-a31-apb2-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun7i_a20_apb0, "allwinner,sun7i-a20-apb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun7i_a20_apb1, "allwinner,sun7i-a20-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun8i_a23_ahb1, "allwinner,sun8i-a23-ahb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun8i_a23_apb1, "allwinner,sun8i-a23-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun8i_a23_apb2, "allwinner,sun8i-a23-apb2-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun8i_a33_ahb1, "allwinner,sun8i-a33-ahb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun8i_a83t_apb0, "allwinner,sun8i-a83t-apb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun9i_a80_ahb0, "allwinner,sun9i-a80-ahb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun9i_a80_ahb1, "allwinner,sun9i-a80-ahb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun9i_a80_ahb2, "allwinner,sun9i-a80-ahb2-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun9i_a80_apb0, "allwinner,sun9i-a80-apb0-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun9i_a80_apb1, "allwinner,sun9i-a80-apb1-gates-clk",
	       sunxi_simple_gates_init);
CLK_OF_DECLARE(sun9i_a80_apbs, "allwinner,sun9i-a80-apbs-gates-clk",
	       sunxi_simple_gates_init);

अटल स्थिर पूर्णांक sun4i_a10_ahb_critical_घड़ीs[] __initस्थिर = अणु
	14,	/* ahb_sdram */
पूर्ण;

अटल व्योम __init sun4i_a10_ahb_init(काष्ठा device_node *node)
अणु
	sunxi_simple_gates_setup(node, sun4i_a10_ahb_critical_घड़ीs,
				 ARRAY_SIZE(sun4i_a10_ahb_critical_घड़ीs));
पूर्ण
CLK_OF_DECLARE(sun4i_a10_ahb, "allwinner,sun4i-a10-ahb-gates-clk",
	       sun4i_a10_ahb_init);
CLK_OF_DECLARE(sun5i_a10s_ahb, "allwinner,sun5i-a10s-ahb-gates-clk",
	       sun4i_a10_ahb_init);
CLK_OF_DECLARE(sun5i_a13_ahb, "allwinner,sun5i-a13-ahb-gates-clk",
	       sun4i_a10_ahb_init);
CLK_OF_DECLARE(sun7i_a20_ahb, "allwinner,sun7i-a20-ahb-gates-clk",
	       sun4i_a10_ahb_init);

अटल स्थिर पूर्णांक sun4i_a10_dram_critical_घड़ीs[] __initस्थिर = अणु
	15,	/* dram_output */
पूर्ण;

अटल व्योम __init sun4i_a10_dram_init(काष्ठा device_node *node)
अणु
	sunxi_simple_gates_setup(node, sun4i_a10_dram_critical_घड़ीs,
				 ARRAY_SIZE(sun4i_a10_dram_critical_घड़ीs));
पूर्ण
CLK_OF_DECLARE(sun4i_a10_dram, "allwinner,sun4i-a10-dram-gates-clk",
	       sun4i_a10_dram_init);
