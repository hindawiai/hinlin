<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Altera Corporation. All rights reserved
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "clk.h"

/* Clock Manager offsets */
#घोषणा CLK_MGR_PLL_CLK_SRC_SHIFT	8
#घोषणा CLK_MGR_PLL_CLK_SRC_MASK	0x3

/* Clock bypass bits */
#घोषणा SOCFPGA_PLL_BG_PWRDWN		0
#घोषणा SOCFPGA_PLL_PWR_DOWN		1
#घोषणा SOCFPGA_PLL_EXT_ENA		2
#घोषणा SOCFPGA_PLL_DIVF_MASK		0x00001FFF
#घोषणा SOCFPGA_PLL_DIVF_SHIFT	0
#घोषणा SOCFPGA_PLL_DIVQ_MASK		0x003F0000
#घोषणा SOCFPGA_PLL_DIVQ_SHIFT	16
#घोषणा SOCFGPA_MAX_PARENTS	5

#घोषणा SOCFPGA_MAIN_PLL_CLK		"main_pll"
#घोषणा SOCFPGA_PERIP_PLL_CLK		"periph_pll"

#घोषणा to_socfpga_clk(p) container_of(p, काष्ठा socfpga_pll, hw.hw)

व्योम __iomem *clk_mgr_a10_base_addr;

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	अचिन्हित दीर्घ भागf, भागq, reg;
	अचिन्हित दीर्घ दीर्घ vco_freq;

	/* पढ़ो VCO1 reg क्रम numerator and denominator */
	reg = पढ़ोl(socfpgaclk->hw.reg + 0x4);
	भागf = (reg & SOCFPGA_PLL_DIVF_MASK) >> SOCFPGA_PLL_DIVF_SHIFT;
	भागq = (reg & SOCFPGA_PLL_DIVQ_MASK) >> SOCFPGA_PLL_DIVQ_SHIFT;
	vco_freq = (अचिन्हित दीर्घ दीर्घ)parent_rate * (भागf + 1);
	करो_भाग(vco_freq, (1 + भागq));
	वापस (अचिन्हित दीर्घ)vco_freq;
पूर्ण

अटल u8 clk_pll_get_parent(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	u32 pll_src;

	pll_src = पढ़ोl(socfpgaclk->hw.reg);

	वापस (pll_src >> CLK_MGR_PLL_CLK_SRC_SHIFT) &
		CLK_MGR_PLL_CLK_SRC_MASK;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.recalc_rate = clk_pll_recalc_rate,
	.get_parent = clk_pll_get_parent,
पूर्ण;

अटल काष्ठा clk_hw * __init __socfpga_pll_init(काष्ठा device_node *node,
	स्थिर काष्ठा clk_ops *ops)
अणु
	u32 reg;
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_pll *pll_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name[SOCFGPA_MAX_PARENTS];
	काष्ठा clk_init_data init;
	काष्ठा device_node *clkmgr_np;
	पूर्णांक i = 0;

	of_property_पढ़ो_u32(node, "reg", &reg);

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (WARN_ON(!pll_clk))
		वापस शून्य;

	clkmgr_np = of_find_compatible_node(शून्य, शून्य, "altr,clk-mgr");
	clk_mgr_a10_base_addr = of_iomap(clkmgr_np, 0);
	of_node_put(clkmgr_np);
	BUG_ON(!clk_mgr_a10_base_addr);
	pll_clk->hw.reg = clk_mgr_a10_base_addr + reg;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = ops;
	init.flags = 0;

	जबतक (i < SOCFGPA_MAX_PARENTS && (parent_name[i] =
			of_clk_get_parent_name(node, i)) != शून्य)
		i++;
	init.num_parents = i;
	init.parent_names = parent_name;
	pll_clk->hw.hw.init = &init;

	pll_clk->hw.bit_idx = SOCFPGA_PLL_EXT_ENA;
	hw_clk = &pll_clk->hw.hw;

	अगर (clk_hw_रेजिस्टर(शून्य, hw_clk)) अणु
		kमुक्त(pll_clk);
		वापस शून्य;
	पूर्ण
	of_clk_add_provider(node, of_clk_src_simple_get, hw_clk);
	वापस hw_clk;
पूर्ण

व्योम __init socfpga_a10_pll_init(काष्ठा device_node *node)
अणु
	__socfpga_pll_init(node, &clk_pll_ops);
पूर्ण
