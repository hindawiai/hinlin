<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright 2011-2012 Calxeda, Inc.
 *  Copyright (C) 2012-2013 Altera Corporation <www.altera.com>
 *
 * Based from clk-highbank.c
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "clk.h"

/* Clock bypass bits */
#घोषणा MAINPLL_BYPASS		(1<<0)
#घोषणा SDRAMPLL_BYPASS		(1<<1)
#घोषणा SDRAMPLL_SRC_BYPASS	(1<<2)
#घोषणा PERPLL_BYPASS		(1<<3)
#घोषणा PERPLL_SRC_BYPASS	(1<<4)

#घोषणा SOCFPGA_PLL_BG_PWRDWN		0
#घोषणा SOCFPGA_PLL_EXT_ENA		1
#घोषणा SOCFPGA_PLL_PWR_DOWN		2
#घोषणा SOCFPGA_PLL_DIVF_MASK		0x0000FFF8
#घोषणा SOCFPGA_PLL_DIVF_SHIFT		3
#घोषणा SOCFPGA_PLL_DIVQ_MASK		0x003F0000
#घोषणा SOCFPGA_PLL_DIVQ_SHIFT		16

#घोषणा CLK_MGR_PLL_CLK_SRC_SHIFT	22
#घोषणा CLK_MGR_PLL_CLK_SRC_MASK	0x3

#घोषणा to_socfpga_clk(p) container_of(p, काष्ठा socfpga_pll, hw.hw)

व्योम __iomem *clk_mgr_base_addr;

अटल अचिन्हित दीर्घ clk_pll_recalc_rate(काष्ठा clk_hw *hwclk,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);
	अचिन्हित दीर्घ भागf, भागq, reg;
	अचिन्हित दीर्घ दीर्घ vco_freq;
	अचिन्हित दीर्घ bypass;

	reg = पढ़ोl(socfpgaclk->hw.reg);
	bypass = पढ़ोl(clk_mgr_base_addr + CLKMGR_BYPASS);
	अगर (bypass & MAINPLL_BYPASS)
		वापस parent_rate;

	भागf = (reg & SOCFPGA_PLL_DIVF_MASK) >> SOCFPGA_PLL_DIVF_SHIFT;
	भागq = (reg & SOCFPGA_PLL_DIVQ_MASK) >> SOCFPGA_PLL_DIVQ_SHIFT;
	vco_freq = (अचिन्हित दीर्घ दीर्घ)parent_rate * (भागf + 1);
	करो_भाग(vco_freq, (1 + भागq));
	वापस (अचिन्हित दीर्घ)vco_freq;
पूर्ण

अटल u8 clk_pll_get_parent(काष्ठा clk_hw *hwclk)
अणु
	u32 pll_src;
	काष्ठा socfpga_pll *socfpgaclk = to_socfpga_clk(hwclk);

	pll_src = पढ़ोl(socfpgaclk->hw.reg);
	वापस (pll_src >> CLK_MGR_PLL_CLK_SRC_SHIFT) &
			CLK_MGR_PLL_CLK_SRC_MASK;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.recalc_rate = clk_pll_recalc_rate,
	.get_parent = clk_pll_get_parent,
पूर्ण;

अटल __init काष्ठा clk_hw *__socfpga_pll_init(काष्ठा device_node *node,
	स्थिर काष्ठा clk_ops *ops)
अणु
	u32 reg;
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_pll *pll_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name[SOCFPGA_MAX_PARENTS];
	काष्ठा clk_init_data init;
	काष्ठा device_node *clkmgr_np;
	पूर्णांक rc;
	पूर्णांक err;

	of_property_पढ़ो_u32(node, "reg", &reg);

	pll_clk = kzalloc(माप(*pll_clk), GFP_KERNEL);
	अगर (WARN_ON(!pll_clk))
		वापस शून्य;

	clkmgr_np = of_find_compatible_node(शून्य, शून्य, "altr,clk-mgr");
	clk_mgr_base_addr = of_iomap(clkmgr_np, 0);
	of_node_put(clkmgr_np);
	BUG_ON(!clk_mgr_base_addr);
	pll_clk->hw.reg = clk_mgr_base_addr + reg;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = ops;
	init.flags = 0;

	init.num_parents = of_clk_parent_fill(node, parent_name, SOCFPGA_MAX_PARENTS);
	init.parent_names = parent_name;
	pll_clk->hw.hw.init = &init;

	pll_clk->hw.bit_idx = SOCFPGA_PLL_EXT_ENA;

	hw_clk = &pll_clk->hw.hw;

	err = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (err) अणु
		kमुक्त(pll_clk);
		वापस ERR_PTR(err);
	पूर्ण
	rc = of_clk_add_provider(node, of_clk_src_simple_get, hw_clk);
	वापस hw_clk;
पूर्ण

व्योम __init socfpga_pll_init(काष्ठा device_node *node)
अणु
	__socfpga_pll_init(node, &clk_pll_ops);
पूर्ण
