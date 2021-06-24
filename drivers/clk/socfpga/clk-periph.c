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

#समावेश "clk.h"

#घोषणा to_socfpga_periph_clk(p) container_of(p, काष्ठा socfpga_periph_clk, hw.hw)

अटल अचिन्हित दीर्घ clk_periclk_recalc_rate(काष्ठा clk_hw *hwclk,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_periph_clk *socfpgaclk = to_socfpga_periph_clk(hwclk);
	u32 भाग, val;

	अगर (socfpgaclk->fixed_भाग) अणु
		भाग = socfpgaclk->fixed_भाग;
	पूर्ण अन्यथा अणु
		अगर (socfpgaclk->भाग_reg) अणु
			val = पढ़ोl(socfpgaclk->भाग_reg) >> socfpgaclk->shअगरt;
			val &= GENMASK(socfpgaclk->width - 1, 0);
			parent_rate /= (val + 1);
		पूर्ण
		भाग = ((पढ़ोl(socfpgaclk->hw.reg) & 0x1ff) + 1);
	पूर्ण

	वापस parent_rate / भाग;
पूर्ण

अटल u8 clk_periclk_get_parent(काष्ठा clk_hw *hwclk)
अणु
	u32 clk_src;

	clk_src = पढ़ोl(clk_mgr_base_addr + CLKMGR_DBCTRL);
	वापस clk_src & 0x1;
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

	periph_clk->hw.reg = clk_mgr_base_addr + reg;

	rc = of_property_पढ़ो_u32_array(node, "div-reg", भाग_reg, 3);
	अगर (!rc) अणु
		periph_clk->भाग_reg = clk_mgr_base_addr + भाग_reg[0];
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

	init.num_parents = of_clk_parent_fill(node, parent_name,
					      SOCFPGA_MAX_PARENTS);
	init.parent_names = parent_name;

	periph_clk->hw.hw.init = &init;
	hw_clk = &periph_clk->hw.hw;

	अगर (clk_hw_रेजिस्टर(शून्य, hw_clk)) अणु
		kमुक्त(periph_clk);
		वापस;
	पूर्ण
	rc = of_clk_add_provider(node, of_clk_src_simple_get, hw_clk);
पूर्ण

व्योम __init socfpga_periph_init(काष्ठा device_node *node)
अणु
	__socfpga_periph_init(node, &periclk_ops);
पूर्ण
