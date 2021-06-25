<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Altera Corporation. All rights reserved
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश "clk.h"

#घोषणा CLK_MGR_FREE_SHIFT		16
#घोषणा CLK_MGR_FREE_MASK		0x7

#घोषणा SOCFPGA_MPU_FREE_CLK		"mpu_free_clk"
#घोषणा SOCFPGA_NOC_FREE_CLK		"noc_free_clk"
#घोषणा SOCFPGA_SDMMC_FREE_CLK		"sdmmc_free_clk"
#घोषणा to_socfpga_periph_clk(p) container_of(p, काष्ठा socfpga_periph_clk, hw.hw)

अटल अचिन्हित दीर्घ clk_periclk_recalc_rate(काष्ठा clk_hw *hwclk,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_socfpga_periph_clk(hwclk);
	u32 भाग;

	अगर (socfpgaclk->fixed_भाग) अणु
		भाग = socfpgaclk->fixed_भाग;
	पूर्ण अन्यथा अगर (socfpgaclk->भाग_reg) अणु
		भाग = पढ़ोl(socfpgaclk->भाग_reg) >> socfpgaclk->shअगरt;
		भाग &= GENMASK(socfpgaclk->width - 1, 0);
		भाग += 1;
	पूर्ण अन्यथा अणु
		भाग = ((पढ़ोl(socfpgaclk->hw.reg) & 0x7ff) + 1);
	पूर्ण

	वापस parent_rate / भाग;
पूर्ण

अटल u8 clk_periclk_get_parent(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_socfpga_periph_clk(hwclk);
	u32 clk_src;
	स्थिर अक्षर *name = clk_hw_get_name(hwclk);

	clk_src = पढ़ोl(socfpgaclk->hw.reg);
	अगर (streq(name, SOCFPGA_MPU_FREE_CLK) ||
	    streq(name, SOCFPGA_NOC_FREE_CLK) ||
	    streq(name, SOCFPGA_SDMMC_FREE_CLK))
		वापस (clk_src >> CLK_MGR_FREE_SHIFT) &
			CLK_MGR_FREE_MASK;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops periclk_ops = अणु
	.recalc_rate = clk_periclk_recalc_rate,
	.get_parent = clk_periclk_get_parent,
पूर्ण;

अटल __init व्योम __socfpga_periph_init(काष्ठा device_node *node,
	स्थिर काष्ठा clk_ops *ops)
अणु
	u32 reg;
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_periph_clk *periph_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name[SOCFPGA_MAX_PARENTS];
	काष्ठा clk_init_data init;
	पूर्णांक rc;
	u32 fixed_भाग;
	u32 भाग_reg[3];

	of_property_पढ़ो_u32(node, "reg", &reg);

	periph_clk = kzalloc(माप(*periph_clk), GFP_KERNEL);
	अगर (WARN_ON(!periph_clk))
		वापस;

	periph_clk->hw.reg = clk_mgr_a10_base_addr + reg;

	rc = of_property_पढ़ो_u32_array(node, "div-reg", भाग_reg, 3);
	अगर (!rc) अणु
		periph_clk->भाग_reg = clk_mgr_a10_base_addr + भाग_reg[0];
		periph_clk->shअगरt = भाग_reg[1];
		periph_clk->width = भाग_reg[2];
	पूर्ण अन्यथा अणु
		periph_clk->भाग_reg = शून्य;
	पूर्ण

	rc = of_property_पढ़ो_u32(node, "fixed-divider", &fixed_भाग);
	अगर (rc)
		periph_clk->fixed_भाग = 0;
	अन्यथा
		periph_clk->fixed_भाग = fixed_भाग;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = ops;
	init.flags = 0;

	init.num_parents = of_clk_parent_fill(node, parent_name, SOCFPGA_MAX_PARENTS);
	init.parent_names = parent_name;

	periph_clk->hw.hw.init = &init;

	hw_clk = &periph_clk->hw.hw;

	अगर (clk_hw_रेजिस्टर(शून्य, hw_clk)) अणु
		kमुक्त(periph_clk);
		वापस;
	पूर्ण
	rc = of_clk_add_provider(node, of_clk_src_simple_get, hw_clk);
	अगर (rc < 0) अणु
		pr_err("Could not register clock provider for node:%s\n",
		       clk_name);
		जाओ err_clk;
	पूर्ण

	वापस;

err_clk:
	clk_hw_unरेजिस्टर(hw_clk);
पूर्ण

व्योम __init socfpga_a10_periph_init(काष्ठा device_node *node)
अणु
	__socfpga_periph_init(node, &periclk_ops);
पूर्ण
