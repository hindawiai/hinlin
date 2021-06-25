<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * H8/300 भागide घड़ी driver
 *
 * Copyright 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

अटल DEFINE_SPINLOCK(clklock);

अटल व्योम __init h8300_भाग_clk_setup(काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक num_parents;
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	व्योम __iomem *भागcr = शून्य;
	पूर्णांक width;
	पूर्णांक offset;

	num_parents = of_clk_get_parent_count(node);
	अगर (!num_parents) अणु
		pr_err("%s: no parent found\n", clk_name);
		वापस;
	पूर्ण

	भागcr = of_iomap(node, 0);
	अगर (भागcr == शून्य) अणु
		pr_err("%s: failed to map divide register\n", clk_name);
		जाओ error;
	पूर्ण
	offset = (अचिन्हित दीर्घ)भागcr & 3;
	offset = (3 - offset) * 8;
	भागcr = (व्योम __iomem *)((अचिन्हित दीर्घ)भागcr & ~3);

	parent_name = of_clk_get_parent_name(node, 0);
	of_property_पढ़ो_u32(node, "renesas,width", &width);
	hw = clk_hw_रेजिस्टर_भागider(शून्य, clk_name, parent_name,
				   CLK_SET_RATE_GATE, भागcr, offset, width,
				   CLK_DIVIDER_POWER_OF_TWO, &clklock);
	अगर (!IS_ERR(hw)) अणु
		of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
		वापस;
	पूर्ण
	pr_err("%s: failed to register %s div clock (%ld)\n",
	       __func__, clk_name, PTR_ERR(hw));
error:
	अगर (भागcr)
		iounmap(भागcr);
पूर्ण

CLK_OF_DECLARE(h8300_भाग_clk, "renesas,h8300-div-clock", h8300_भाग_clk_setup);
