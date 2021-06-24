<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * Allwinner A31 APB0 घड़ी driver
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * The APB0 clk has a configurable भागisor.
 *
 * We must use a clk_भाग_प्रकारable and not a regular घातer of 2
 * भागisor here, because the first 2 values भागide the घड़ी
 * by 2.
 */
अटल स्थिर काष्ठा clk_भाग_प्रकारable sun6i_a31_apb0_भागs[] = अणु
	अणु .val = 0, .भाग = 2, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 2, .भाग = 4, पूर्ण,
	अणु .val = 3, .भाग = 8, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक sun6i_a31_apb0_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *clk_parent;
	काष्ठा resource *r;
	व्योम __iomem *reg;
	काष्ठा clk *clk;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	clk_parent = of_clk_get_parent_name(np, 0);
	अगर (!clk_parent)
		वापस -EINVAL;

	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	clk = clk_रेजिस्टर_भागider_table(&pdev->dev, clk_name, clk_parent,
					 0, reg, 0, 2, 0, sun6i_a31_apb0_भागs,
					 शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	वापस of_clk_add_provider(np, of_clk_src_simple_get, clk);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_a31_apb0_clk_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-apb0-clk" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sun6i_a31_apb0_clk_driver = अणु
	.driver = अणु
		.name = "sun6i-a31-apb0-clk",
		.of_match_table = sun6i_a31_apb0_clk_dt_ids,
	पूर्ण,
	.probe = sun6i_a31_apb0_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sun6i_a31_apb0_clk_driver);
