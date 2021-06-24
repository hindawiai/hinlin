<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Layerscape FlexSPI घड़ी driver
 *
 * Copyright 2020 Michael Walle <michael@walle.cc>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर काष्ठा clk_भाग_प्रकारable ls1028a_flexspi_भागs[] = अणु
	अणु .val = 0, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 2, .भाग = 3, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु .val = 4, .भाग = 5, पूर्ण,
	अणु .val = 5, .भाग = 6, पूर्ण,
	अणु .val = 6, .भाग = 7, पूर्ण,
	अणु .val = 7, .भाग = 8, पूर्ण,
	अणु .val = 11, .भाग = 12, पूर्ण,
	अणु .val = 15, .भाग = 16, पूर्ण,
	अणु .val = 16, .भाग = 20, पूर्ण,
	अणु .val = 17, .भाग = 24, पूर्ण,
	अणु .val = 18, .भाग = 28, पूर्ण,
	अणु .val = 19, .भाग = 32, पूर्ण,
	अणु .val = 20, .भाग = 80, पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable lx2160a_flexspi_भागs[] = अणु
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 3, .भाग = 4, पूर्ण,
	अणु .val = 5, .भाग = 6, पूर्ण,
	अणु .val = 7, .भाग = 8, पूर्ण,
	अणु .val = 11, .भाग = 12, पूर्ण,
	अणु .val = 15, .भाग = 16, पूर्ण,
	अणु .val = 16, .भाग = 20, पूर्ण,
	अणु .val = 17, .भाग = 24, पूर्ण,
	अणु .val = 18, .भाग = 28, पूर्ण,
	अणु .val = 19, .भाग = 32, पूर्ण,
	अणु .val = 20, .भाग = 80, पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक fsl_flexspi_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर *clk_name = np->name;
	स्थिर अक्षर *clk_parent;
	काष्ठा resource *res;
	व्योम __iomem *reg;
	काष्ठा clk_hw *hw;
	स्थिर काष्ठा clk_भाग_प्रकारable *भागs;

	भागs = device_get_match_data(dev);
	अगर (!भागs)
		वापस -ENOENT;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOENT;

	/*
	 * Can't use devm_ioremap_resource() or devm_of_iomap() because the
	 * resource might alपढ़ोy be taken by the parent device.
	 */
	reg = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!reg)
		वापस -ENOMEM;

	clk_parent = of_clk_get_parent_name(np, 0);
	अगर (!clk_parent)
		वापस -EINVAL;

	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	hw = devm_clk_hw_रेजिस्टर_भागider_table(dev, clk_name, clk_parent, 0,
						reg, 0, 5, 0, भागs, शून्य);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_flexspi_clk_dt_ids[] = अणु
	अणु .compatible = "fsl,ls1028a-flexspi-clk", .data = &ls1028a_flexspi_भागs पूर्ण,
	अणु .compatible = "fsl,lx2160a-flexspi-clk", .data = &lx2160a_flexspi_भागs पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_flexspi_clk_dt_ids);

अटल काष्ठा platक्रमm_driver fsl_flexspi_clk_driver = अणु
	.driver = अणु
		.name = "fsl-flexspi-clk",
		.of_match_table = fsl_flexspi_clk_dt_ids,
	पूर्ण,
	.probe = fsl_flexspi_clk_probe,
पूर्ण;
module_platक्रमm_driver(fsl_flexspi_clk_driver);

MODULE_DESCRIPTION("FlexSPI clock driver for Layerscape SoCs");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
