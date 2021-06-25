<शैली गुरु>
// SPDX-License-Identअगरier:	GPL-2.0
/*
 * Copyright (C) 2017, Intel Corporation
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "stratix10-clk.h"
#समावेश "clk.h"

#घोषणा SOCFPGA_CS_PDBG_CLK	"cs_pdbg_clk"
#घोषणा to_socfpga_gate_clk(p) container_of(p, काष्ठा socfpga_gate_clk, hw.hw)

अटल अचिन्हित दीर्घ socfpga_gate_clk_recalc_rate(काष्ठा clk_hw *hwclk,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 भाग = 1, val;

	अगर (socfpgaclk->fixed_भाग) अणु
		भाग = socfpgaclk->fixed_भाग;
	पूर्ण अन्यथा अगर (socfpgaclk->भाग_reg) अणु
		val = पढ़ोl(socfpgaclk->भाग_reg) >> socfpgaclk->shअगरt;
		val &= GENMASK(socfpgaclk->width - 1, 0);
		भाग = (1 << val);
	पूर्ण
	वापस parent_rate / भाग;
पूर्ण

अटल अचिन्हित दीर्घ socfpga_dbg_clk_recalc_rate(काष्ठा clk_hw *hwclk,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 भाग, val;

	val = पढ़ोl(socfpgaclk->भाग_reg) >> socfpgaclk->shअगरt;
	val &= GENMASK(socfpgaclk->width - 1, 0);
	भाग = (1 << val);
	भाग = भाग ? 4 : 1;

	वापस parent_rate / भाग;
पूर्ण

अटल u8 socfpga_gate_get_parent(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 mask;
	u8 parent = 0;

	अगर (socfpgaclk->bypass_reg) अणु
		mask = (0x1 << socfpgaclk->bypass_shअगरt);
		parent = ((पढ़ोl(socfpgaclk->bypass_reg) & mask) >>
			  socfpgaclk->bypass_shअगरt);
	पूर्ण
	वापस parent;
पूर्ण

अटल काष्ठा clk_ops gateclk_ops = अणु
	.recalc_rate = socfpga_gate_clk_recalc_rate,
	.get_parent = socfpga_gate_get_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_ops dbgclk_ops = अणु
	.recalc_rate = socfpga_dbg_clk_recalc_rate,
	.get_parent = socfpga_gate_get_parent,
पूर्ण;

काष्ठा clk_hw *s10_रेजिस्टर_gate(स्थिर काष्ठा stratix10_gate_घड़ी *clks, व्योम __iomem *regbase)
अणु
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_gate_clk *socfpga_clk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name = clks->parent_name;
	पूर्णांक ret;

	socfpga_clk = kzalloc(माप(*socfpga_clk), GFP_KERNEL);
	अगर (!socfpga_clk)
		वापस शून्य;

	socfpga_clk->hw.reg = regbase + clks->gate_reg;
	socfpga_clk->hw.bit_idx = clks->gate_idx;

	gateclk_ops.enable = clk_gate_ops.enable;
	gateclk_ops.disable = clk_gate_ops.disable;

	socfpga_clk->fixed_भाग = clks->fixed_भाग;

	अगर (clks->भाग_reg)
		socfpga_clk->भाग_reg = regbase + clks->भाग_reg;
	अन्यथा
		socfpga_clk->भाग_reg = शून्य;

	socfpga_clk->width = clks->भाग_width;
	socfpga_clk->shअगरt = clks->भाग_offset;

	अगर (clks->bypass_reg)
		socfpga_clk->bypass_reg = regbase + clks->bypass_reg;
	अन्यथा
		socfpga_clk->bypass_reg = शून्य;
	socfpga_clk->bypass_shअगरt = clks->bypass_shअगरt;

	अगर (streq(clks->name, "cs_pdbg_clk"))
		init.ops = &dbgclk_ops;
	अन्यथा
		init.ops = &gateclk_ops;

	init.name = clks->name;
	init.flags = clks->flags;

	init.num_parents = clks->num_parents;
	init.parent_names = parent_name ? &parent_name : शून्य;
	अगर (init.parent_names == शून्य)
		init.parent_data = clks->parent_data;
	socfpga_clk->hw.hw.init = &init;

	hw_clk = &socfpga_clk->hw.hw;

	ret = clk_hw_रेजिस्टर(शून्य, &socfpga_clk->hw.hw);
	अगर (ret) अणु
		kमुक्त(socfpga_clk);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस hw_clk;
पूर्ण
