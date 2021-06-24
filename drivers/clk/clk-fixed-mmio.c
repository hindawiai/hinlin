<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Memory Mapped IO Fixed घड़ी driver
 *
 * Copyright (C) 2018 Cadence Design Systems, Inc.
 *
 * Authors:
 *	Jan Kotas <jank@cadence.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

अटल काष्ठा clk_hw *fixed_mmio_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk_hw *clk;
	स्थिर अक्षर *clk_name = node->name;
	व्योम __iomem *base;
	u32 freq;
	पूर्णांक ret;

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("%pOFn: failed to map address\n", node);
		वापस ERR_PTR(-EIO);
	पूर्ण

	freq = पढ़ोl(base);
	iounmap(base);
	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	clk = clk_hw_रेजिस्टर_fixed_rate(शून्य, clk_name, शून्य, 0, freq);
	अगर (IS_ERR(clk)) अणु
		pr_err("%pOFn: failed to register fixed rate clock\n", node);
		वापस clk;
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, clk);
	अगर (ret) अणु
		pr_err("%pOFn: failed to add clock provider\n", node);
		clk_hw_unरेजिस्टर(clk);
		clk = ERR_PTR(ret);
	पूर्ण

	वापस clk;
पूर्ण

अटल व्योम __init of_fixed_mmio_clk_setup(काष्ठा device_node *node)
अणु
	fixed_mmio_clk_setup(node);
पूर्ण
CLK_OF_DECLARE(fixed_mmio_clk, "fixed-mmio-clock", of_fixed_mmio_clk_setup);

/*
 * This is not executed when of_fixed_mmio_clk_setup succeeded.
 */
अटल पूर्णांक of_fixed_mmio_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw *clk;

	clk = fixed_mmio_clk_setup(pdev->dev.of_node);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	platक्रमm_set_drvdata(pdev, clk);

	वापस 0;
पूर्ण

अटल पूर्णांक of_fixed_mmio_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw *clk = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);
	clk_hw_unरेजिस्टर_fixed_rate(clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_fixed_mmio_clk_ids[] = अणु
	अणु .compatible = "fixed-mmio-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fixed_mmio_clk_ids);

अटल काष्ठा platक्रमm_driver of_fixed_mmio_clk_driver = अणु
	.driver = अणु
		.name = "of_fixed_mmio_clk",
		.of_match_table = of_fixed_mmio_clk_ids,
	पूर्ण,
	.probe = of_fixed_mmio_clk_probe,
	.हटाओ = of_fixed_mmio_clk_हटाओ,
पूर्ण;
module_platक्रमm_driver(of_fixed_mmio_clk_driver);

MODULE_AUTHOR("Jan Kotas <jank@cadence.com>");
MODULE_DESCRIPTION("Memory Mapped IO Fixed clock driver");
MODULE_LICENSE("GPL v2");
