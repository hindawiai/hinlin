<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Jens Kuske <jenskuske@gmail.com>
 *
 * Based on clk-simple-gates.c, which is:
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

अटल DEFINE_SPINLOCK(gates_lock);

अटल व्योम __init sun8i_h3_bus_gates_init(काष्ठा device_node *node)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु "ahb1", "ahb2", "apb1", "apb2" पूर्ण;
	क्रमागत अणु AHB1, AHB2, APB1, APB2, PARENT_MAX पूर्ण clk_parent;
	स्थिर अक्षर *parents[PARENT_MAX];
	काष्ठा clk_onecell_data *clk_data;
	स्थिर अक्षर *clk_name;
	काष्ठा property *prop;
	काष्ठा resource res;
	व्योम __iomem *clk_reg;
	व्योम __iomem *reg;
	स्थिर __be32 *p;
	पूर्णांक number, i;
	u8 clk_bit;
	पूर्णांक index;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(names); i++) अणु
		पूर्णांक idx = of_property_match_string(node, "clock-names",
						   names[i]);
		अगर (idx < 0)
			वापस;

		parents[i] = of_clk_get_parent_name(node, idx);
	पूर्ण

	clk_data = kदो_स्मृति(माप(काष्ठा clk_onecell_data), GFP_KERNEL);
	अगर (!clk_data)
		जाओ err_unmap;

	number = of_property_count_u32_elems(node, "clock-indices");
	of_property_पढ़ो_u32_index(node, "clock-indices", number - 1, &number);

	clk_data->clks = kसुस्मृति(number + 1, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clk_data->clks)
		जाओ err_मुक्त_data;

	i = 0;
	of_property_क्रम_each_u32(node, "clock-indices", prop, p, index) अणु
		of_property_पढ़ो_string_index(node, "clock-output-names",
					      i, &clk_name);

		अगर (index == 17 || (index >= 29 && index <= 31))
			clk_parent = AHB2;
		अन्यथा अगर (index <= 63 || index >= 128)
			clk_parent = AHB1;
		अन्यथा अगर (index >= 64 && index <= 95)
			clk_parent = APB1;
		अन्यथा अगर (index >= 96 && index <= 127)
			clk_parent = APB2;
		अन्यथा अणु
			WARN_ON(true);
			जारी;
		पूर्ण

		clk_reg = reg + 4 * (index / 32);
		clk_bit = index % 32;

		clk_data->clks[index] = clk_रेजिस्टर_gate(शून्य, clk_name,
							  parents[clk_parent],
							  0, clk_reg, clk_bit,
							  0, &gates_lock);
		i++;

		अगर (IS_ERR(clk_data->clks[index])) अणु
			WARN_ON(true);
			जारी;
		पूर्ण
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

CLK_OF_DECLARE(sun8i_h3_bus_gates, "allwinner,sun8i-h3-bus-gates-clk",
	       sun8i_h3_bus_gates_init);
CLK_OF_DECLARE(sun8i_a83t_bus_gates, "allwinner,sun8i-a83t-bus-gates-clk",
	       sun8i_h3_bus_gates_init);
