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
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "clk.h"

#घोषणा SOCFPGA_L4_MP_CLK		"l4_mp_clk"
#घोषणा SOCFPGA_L4_SP_CLK		"l4_sp_clk"
#घोषणा SOCFPGA_न_अंकD_CLK		"nand_clk"
#घोषणा SOCFPGA_न_अंकD_X_CLK		"nand_x_clk"
#घोषणा SOCFPGA_MMC_CLK			"sdmmc_clk"
#घोषणा SOCFPGA_GPIO_DB_CLK_OFFSET	0xA8

#घोषणा to_socfpga_gate_clk(p) container_of(p, काष्ठा socfpga_gate_clk, hw.hw)

/* SDMMC Group क्रम System Manager defines */
#घोषणा SYSMGR_SDMMCGRP_CTRL_OFFSET    0x108

अटल u8 socfpga_clk_get_parent(काष्ठा clk_hw *hwclk)
अणु
	u32 l4_src;
	u32 perpll_src;
	स्थिर अक्षर *name = clk_hw_get_name(hwclk);

	अगर (streq(name, SOCFPGA_L4_MP_CLK)) अणु
		l4_src = पढ़ोl(clk_mgr_base_addr + CLKMGR_L4SRC);
		वापस l4_src &= 0x1;
	पूर्ण
	अगर (streq(name, SOCFPGA_L4_SP_CLK)) अणु
		l4_src = पढ़ोl(clk_mgr_base_addr + CLKMGR_L4SRC);
		वापस !!(l4_src & 2);
	पूर्ण

	perpll_src = पढ़ोl(clk_mgr_base_addr + CLKMGR_PERPLL_SRC);
	अगर (streq(name, SOCFPGA_MMC_CLK))
		वापस perpll_src &= 0x3;
	अगर (streq(name, SOCFPGA_न_अंकD_CLK) ||
	    streq(name, SOCFPGA_न_अंकD_X_CLK))
		वापस (perpll_src >> 2) & 3;

	/* QSPI घड़ी */
	वापस (perpll_src >> 4) & 3;

पूर्ण

अटल पूर्णांक socfpga_clk_set_parent(काष्ठा clk_hw *hwclk, u8 parent)
अणु
	u32 src_reg;
	स्थिर अक्षर *name = clk_hw_get_name(hwclk);

	अगर (streq(name, SOCFPGA_L4_MP_CLK)) अणु
		src_reg = पढ़ोl(clk_mgr_base_addr + CLKMGR_L4SRC);
		src_reg &= ~0x1;
		src_reg |= parent;
		ग_लिखोl(src_reg, clk_mgr_base_addr + CLKMGR_L4SRC);
	पूर्ण अन्यथा अगर (streq(name, SOCFPGA_L4_SP_CLK)) अणु
		src_reg = पढ़ोl(clk_mgr_base_addr + CLKMGR_L4SRC);
		src_reg &= ~0x2;
		src_reg |= (parent << 1);
		ग_लिखोl(src_reg, clk_mgr_base_addr + CLKMGR_L4SRC);
	पूर्ण अन्यथा अणु
		src_reg = पढ़ोl(clk_mgr_base_addr + CLKMGR_PERPLL_SRC);
		अगर (streq(name, SOCFPGA_MMC_CLK)) अणु
			src_reg &= ~0x3;
			src_reg |= parent;
		पूर्ण अन्यथा अगर (streq(name, SOCFPGA_न_अंकD_CLK) ||
			streq(name, SOCFPGA_न_अंकD_X_CLK)) अणु
			src_reg &= ~0xC;
			src_reg |= (parent << 2);
		पूर्ण अन्यथा अणु/* QSPI घड़ी */
			src_reg &= ~0x30;
			src_reg |= (parent << 4);
		पूर्ण
		ग_लिखोl(src_reg, clk_mgr_base_addr + CLKMGR_PERPLL_SRC);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ socfpga_clk_recalc_rate(काष्ठा clk_hw *hwclk,
	अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 भाग = 1, val;

	अगर (socfpgaclk->fixed_भाग)
		भाग = socfpgaclk->fixed_भाग;
	अन्यथा अगर (socfpgaclk->भाग_reg) अणु
		val = पढ़ोl(socfpgaclk->भाग_reg) >> socfpgaclk->shअगरt;
		val &= GENMASK(socfpgaclk->width - 1, 0);
		/* Check क्रम GPIO_DB_CLK by its offset */
		अगर ((uपूर्णांकptr_t) socfpgaclk->भाग_reg & SOCFPGA_GPIO_DB_CLK_OFFSET)
			भाग = val + 1;
		अन्यथा
			भाग = (1 << val);
	पूर्ण

	वापस parent_rate / भाग;
पूर्ण

अटल पूर्णांक socfpga_clk_prepare(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	काष्ठा regmap *sys_mgr_base_addr;
	पूर्णांक i;
	u32 hs_timing;
	u32 clk_phase[2];

	अगर (socfpgaclk->clk_phase[0] || socfpgaclk->clk_phase[1]) अणु
		sys_mgr_base_addr = syscon_regmap_lookup_by_compatible("altr,sys-mgr");
		अगर (IS_ERR(sys_mgr_base_addr)) अणु
			pr_err("%s: failed to find altr,sys-mgr regmap!\n", __func__);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < 2; i++) अणु
			चयन (socfpgaclk->clk_phase[i]) अणु
			हाल 0:
				clk_phase[i] = 0;
				अवरोध;
			हाल 45:
				clk_phase[i] = 1;
				अवरोध;
			हाल 90:
				clk_phase[i] = 2;
				अवरोध;
			हाल 135:
				clk_phase[i] = 3;
				अवरोध;
			हाल 180:
				clk_phase[i] = 4;
				अवरोध;
			हाल 225:
				clk_phase[i] = 5;
				अवरोध;
			हाल 270:
				clk_phase[i] = 6;
				अवरोध;
			हाल 315:
				clk_phase[i] = 7;
				अवरोध;
			शेष:
				clk_phase[i] = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		hs_timing = SYSMGR_SDMMC_CTRL_SET(clk_phase[0], clk_phase[1]);
		regmap_ग_लिखो(sys_mgr_base_addr, SYSMGR_SDMMCGRP_CTRL_OFFSET,
			hs_timing);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा clk_ops gateclk_ops = अणु
	.prepare = socfpga_clk_prepare,
	.recalc_rate = socfpga_clk_recalc_rate,
	.get_parent = socfpga_clk_get_parent,
	.set_parent = socfpga_clk_set_parent,
पूर्ण;

व्योम __init socfpga_gate_init(काष्ठा device_node *node)
अणु
	u32 clk_gate[2];
	u32 भाग_reg[3];
	u32 clk_phase[2];
	u32 fixed_भाग;
	काष्ठा clk_hw *hw_clk;
	काष्ठा socfpga_gate_clk *socfpga_clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name[SOCFPGA_MAX_PARENTS];
	काष्ठा clk_init_data init;
	काष्ठा clk_ops *ops;
	पूर्णांक rc;
	पूर्णांक err;

	socfpga_clk = kzalloc(माप(*socfpga_clk), GFP_KERNEL);
	अगर (WARN_ON(!socfpga_clk))
		वापस;

	ops = kmemdup(&gateclk_ops, माप(gateclk_ops), GFP_KERNEL);
	अगर (WARN_ON(!ops))
		वापस;

	rc = of_property_पढ़ो_u32_array(node, "clk-gate", clk_gate, 2);
	अगर (rc)
		clk_gate[0] = 0;

	अगर (clk_gate[0]) अणु
		socfpga_clk->hw.reg = clk_mgr_base_addr + clk_gate[0];
		socfpga_clk->hw.bit_idx = clk_gate[1];

		ops->enable = clk_gate_ops.enable;
		ops->disable = clk_gate_ops.disable;
	पूर्ण

	rc = of_property_पढ़ो_u32(node, "fixed-divider", &fixed_भाग);
	अगर (rc)
		socfpga_clk->fixed_भाग = 0;
	अन्यथा
		socfpga_clk->fixed_भाग = fixed_भाग;

	rc = of_property_पढ़ो_u32_array(node, "div-reg", भाग_reg, 3);
	अगर (!rc) अणु
		socfpga_clk->भाग_reg = clk_mgr_base_addr + भाग_reg[0];
		socfpga_clk->shअगरt = भाग_reg[1];
		socfpga_clk->width = भाग_reg[2];
	पूर्ण अन्यथा अणु
		socfpga_clk->भाग_reg = शून्य;
	पूर्ण

	rc = of_property_पढ़ो_u32_array(node, "clk-phase", clk_phase, 2);
	अगर (!rc) अणु
		socfpga_clk->clk_phase[0] = clk_phase[0];
		socfpga_clk->clk_phase[1] = clk_phase[1];
	पूर्ण

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = ops;
	init.flags = 0;

	init.num_parents = of_clk_parent_fill(node, parent_name, SOCFPGA_MAX_PARENTS);
	अगर (init.num_parents < 2) अणु
		ops->get_parent = शून्य;
		ops->set_parent = शून्य;
	पूर्ण

	init.parent_names = parent_name;
	socfpga_clk->hw.hw.init = &init;

	hw_clk = &socfpga_clk->hw.hw;

	err = clk_hw_रेजिस्टर(शून्य, hw_clk);
	अगर (err) अणु
		kमुक्त(socfpga_clk);
		वापस;
	पूर्ण
	rc = of_clk_add_provider(node, of_clk_src_simple_get, hw_clk);
	अगर (WARN_ON(rc))
		वापस;
पूर्ण
