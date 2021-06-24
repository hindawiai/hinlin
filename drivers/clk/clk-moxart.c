<शैली गुरु>
/*
 * MOXA ART SoCs घड़ी driver.
 *
 * Copyright (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/clkdev.h>

अटल व्योम __init moxart_of_pll_clk_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base;
	काष्ठा clk_hw *hw;
	काष्ठा clk *ref_clk;
	अचिन्हित पूर्णांक mul;
	स्थिर अक्षर *name = node->name;
	स्थिर अक्षर *parent_name;

	of_property_पढ़ो_string(node, "clock-output-names", &name);
	parent_name = of_clk_get_parent_name(node, 0);

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("%pOF: of_iomap failed\n", node);
		वापस;
	पूर्ण

	mul = पढ़ोl(base + 0x30) >> 3 & 0x3f;
	iounmap(base);

	ref_clk = of_clk_get(node, 0);
	अगर (IS_ERR(ref_clk)) अणु
		pr_err("%pOF: of_clk_get failed\n", node);
		वापस;
	पूर्ण

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, name, parent_name, 0, mul, 1);
	अगर (IS_ERR(hw)) अणु
		pr_err("%pOF: failed to register clock\n", node);
		वापस;
	पूर्ण

	clk_hw_रेजिस्टर_clkdev(hw, शून्य, name);
	of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(moxart_pll_घड़ी, "moxa,moxart-pll-clock",
	       moxart_of_pll_clk_init);

अटल व्योम __init moxart_of_apb_clk_init(काष्ठा device_node *node)
अणु
	व्योम __iomem *base;
	काष्ठा clk_hw *hw;
	काष्ठा clk *pll_clk;
	अचिन्हित पूर्णांक भाग, val;
	अचिन्हित पूर्णांक भाग_idx[] = अणु 2, 3, 4, 6, 8पूर्ण;
	स्थिर अक्षर *name = node->name;
	स्थिर अक्षर *parent_name;

	of_property_पढ़ो_string(node, "clock-output-names", &name);
	parent_name = of_clk_get_parent_name(node, 0);

	base = of_iomap(node, 0);
	अगर (!base) अणु
		pr_err("%pOF: of_iomap failed\n", node);
		वापस;
	पूर्ण

	val = पढ़ोl(base + 0xc) >> 4 & 0x7;
	iounmap(base);

	अगर (val > 4)
		val = 0;
	भाग = भाग_idx[val] * 2;

	pll_clk = of_clk_get(node, 0);
	अगर (IS_ERR(pll_clk)) अणु
		pr_err("%pOF: of_clk_get failed\n", node);
		वापस;
	पूर्ण

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, name, parent_name, 0, 1, भाग);
	अगर (IS_ERR(hw)) अणु
		pr_err("%pOF: failed to register clock\n", node);
		वापस;
	पूर्ण

	clk_hw_रेजिस्टर_clkdev(hw, शून्य, name);
	of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
पूर्ण
CLK_OF_DECLARE(moxart_apb_घड़ी, "moxa,moxart-apb-clock",
	       moxart_of_apb_clk_init);
