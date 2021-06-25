<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Chen-Yu Tsai
 * Author: Chen-Yu Tsai <wens@csie.org>
 *
 * Allwinner A23 APB0 घड़ी driver
 *
 * Based on clk-sun6i-apb0.c
 * Allwinner A31 APB0 घड़ी driver
 *
 * Copyright (C) 2014 Free Electrons
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

अटल काष्ठा clk *sun8i_a23_apb0_रेजिस्टर(काष्ठा device_node *node,
					   व्योम __iomem *reg)
अणु
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *clk_parent;
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk_parent = of_clk_get_parent_name(node, 0);
	अगर (!clk_parent)
		वापस ERR_PTR(-EINVAL);

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	/* The A23 APB0 घड़ी is a standard 2 bit wide भागider घड़ी */
	clk = clk_रेजिस्टर_भागider(शून्य, clk_name, clk_parent, 0, reg,
				   0, 2, 0, शून्य);
	अगर (IS_ERR(clk))
		वापस clk;

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret)
		जाओ err_unरेजिस्टर;

	वापस clk;

err_unरेजिस्टर:
	clk_unरेजिस्टर_भागider(clk);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम sun8i_a23_apb0_setup(काष्ठा device_node *node)
अणु
	व्योम __iomem *reg;
	काष्ठा resource res;
	काष्ठा clk *clk;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		/*
		 * This happens with clk nodes instantiated through mfd,
		 * as those करो not have their resources asचिन्हित in the
		 * device tree. Do not prपूर्णांक an error in this हाल.
		 */
		अगर (PTR_ERR(reg) != -EINVAL)
			pr_err("Could not get registers for a23-apb0-clk\n");

		वापस;
	पूर्ण

	clk = sun8i_a23_apb0_रेजिस्टर(node, reg);
	अगर (IS_ERR(clk))
		जाओ err_unmap;

	वापस;

err_unmap:
	iounmap(reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
पूर्ण
CLK_OF_DECLARE_DRIVER(sun8i_a23_apb0, "allwinner,sun8i-a23-apb0-clk",
		      sun8i_a23_apb0_setup);

अटल पूर्णांक sun8i_a23_apb0_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *r;
	व्योम __iomem *reg;
	काष्ठा clk *clk;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	clk = sun8i_a23_apb0_रेजिस्टर(np, reg);
	वापस PTR_ERR_OR_ZERO(clk);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun8i_a23_apb0_clk_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun8i-a23-apb0-clk" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun8i_a23_apb0_clk_driver = अणु
	.driver = अणु
		.name = "sun8i-a23-apb0-clk",
		.of_match_table = sun8i_a23_apb0_clk_dt_ids,
	पूर्ण,
	.probe = sun8i_a23_apb0_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sun8i_a23_apb0_clk_driver);
