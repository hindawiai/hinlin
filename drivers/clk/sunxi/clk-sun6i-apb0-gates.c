<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 *
 * Allwinner A31 APB0 घड़ी gates driver
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SUN6I_APB0_GATES_MAX_SIZE	32

काष्ठा gates_data अणु
	DECLARE_BITMAP(mask, SUN6I_APB0_GATES_MAX_SIZE);
पूर्ण;

अटल स्थिर काष्ठा gates_data sun6i_a31_apb0_gates __initस्थिर = अणु
	.mask = अणु0x7Fपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gates_data sun8i_a23_apb0_gates __initस्थिर = अणु
	.mask = अणु0x5Dपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun6i_a31_apb0_gates_clk_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-apb0-gates-clk", .data = &sun6i_a31_apb0_gates पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-apb0-gates-clk", .data = &sun8i_a23_apb0_gates पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक sun6i_a31_apb0_gates_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clk_onecell_data *clk_data;
	स्थिर काष्ठा gates_data *data;
	स्थिर अक्षर *clk_parent;
	स्थिर अक्षर *clk_name;
	काष्ठा resource *r;
	व्योम __iomem *reg;
	पूर्णांक ngates;
	पूर्णांक i;
	पूर्णांक j = 0;

	अगर (!np)
		वापस -ENODEV;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data)
		वापस -ENODEV;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	clk_parent = of_clk_get_parent_name(np, 0);
	अगर (!clk_parent)
		वापस -EINVAL;

	clk_data = devm_kzalloc(&pdev->dev, माप(काष्ठा clk_onecell_data),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	/* Worst-हाल size approximation and memory allocation */
	ngates = find_last_bit(data->mask, SUN6I_APB0_GATES_MAX_SIZE);
	clk_data->clks = devm_kसुस्मृति(&pdev->dev, (ngates + 1),
				      माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clk_data->clks)
		वापस -ENOMEM;

	क्रम_each_set_bit(i, data->mask, SUN6I_APB0_GATES_MAX_SIZE) अणु
		of_property_पढ़ो_string_index(np, "clock-output-names",
					      j, &clk_name);

		clk_data->clks[i] = clk_रेजिस्टर_gate(&pdev->dev, clk_name,
						      clk_parent, 0, reg, i,
						      0, शून्य);
		WARN_ON(IS_ERR(clk_data->clks[i]));

		j++;
	पूर्ण

	clk_data->clk_num = ngates + 1;

	वापस of_clk_add_provider(np, of_clk_src_onecell_get, clk_data);
पूर्ण

अटल काष्ठा platक्रमm_driver sun6i_a31_apb0_gates_clk_driver = अणु
	.driver = अणु
		.name = "sun6i-a31-apb0-gates-clk",
		.of_match_table = sun6i_a31_apb0_gates_clk_dt_ids,
	पूर्ण,
	.probe = sun6i_a31_apb0_gates_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(sun6i_a31_apb0_gates_clk_driver);
