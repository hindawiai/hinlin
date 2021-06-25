<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Altera Corporation. All rights reserved
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "clk.h"

#घोषणा streq(a, b) (म_भेद((a), (b)) == 0)

#घोषणा to_socfpga_gate_clk(p) container_of(p, काष्ठा socfpga_gate_clk, hw.hw)

/* SDMMC Group क्रम System Manager defines */
#घोषणा SYSMGR_SDMMCGRP_CTRL_OFFSET	0x28

अटल अचिन्हित दीर्घ socfpga_gate_clk_recalc_rate(काष्ठा clk_hw *hwclk,
	अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 भाग = 1, val;

	अगर (socfpgaclk->fixed_भाग)
		भाग = socfpgaclk->fixed_भाग;
	अन्यथा अगर (socfpgaclk->भाग_reg) अणु
		val = पढ़ोl(socfpgaclk->भाग_reg) >> socfpgaclk->shअगरt;
		val &= GENMASK(socfpgaclk->width - 1, 0);
		भाग = (1 << val);
	पूर्ण

	वापस parent_rate / भाग;
पूर्ण

अटल पूर्णांक socfpga_clk_prepare(काष्ठा clk_hw *hwclk)
अणु
	काष्ठा socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	पूर्णांक i;
	u32 hs_timing;
	u32 clk_phase[2];

	अगर (socfpgaclk->clk_phase[0] || socfpgaclk->clk_phase[1]) अणु
		क्रम (i = 0; i < ARRAY_SIZE(clk_phase); i++) अणु
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

		hs_timing = SYSMGR_SDMMC_CTRL_SET_AS10(clk_phase[0], clk_phase[1]);
		अगर (!IS_ERR(socfpgaclk->sys_mgr_base_addr))
			regmap_ग_लिखो(socfpgaclk->sys_mgr_base_addr,
				     SYSMGR_SDMMCGRP_CTRL_OFFSET, hs_timing);
		अन्यथा
			pr_err("%s: cannot set clk_phase because sys_mgr_base_addr is not available!\n",
					__func__);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा clk_ops gateclk_ops = अणु
	.prepare = socfpga_clk_prepare,
	.recalc_rate = socfpga_gate_clk_recalc_rate,
पूर्ण;

अटल व्योम __init __socfpga_gate_init(काष्ठा device_node *node,
	स्थिर काष्ठा clk_ops *ops)
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
	पूर्णांक rc;

	socfpga_clk = kzalloc(माप(*socfpga_clk), GFP_KERNEL);
	अगर (WARN_ON(!socfpga_clk))
		वापस;

	rc = of_property_पढ़ो_u32_array(node, "clk-gate", clk_gate, 2);
	अगर (rc)
		clk_gate[0] = 0;

	अगर (clk_gate[0]) अणु
		socfpga_clk->hw.reg = clk_mgr_a10_base_addr + clk_gate[0];
		socfpga_clk->hw.bit_idx = clk_gate[1];

		gateclk_ops.enable = clk_gate_ops.enable;
		gateclk_ops.disable = clk_gate_ops.disable;
	पूर्ण

	rc = of_property_पढ़ो_u32(node, "fixed-divider", &fixed_भाग);
	अगर (rc)
		socfpga_clk->fixed_भाग = 0;
	अन्यथा
		socfpga_clk->fixed_भाग = fixed_भाग;

	rc = of_property_पढ़ो_u32_array(node, "div-reg", भाग_reg, 3);
	अगर (!rc) अणु
		socfpga_clk->भाग_reg = clk_mgr_a10_base_addr + भाग_reg[0];
		socfpga_clk->shअगरt = भाग_reg[1];
		socfpga_clk->width = भाग_reg[2];
	पूर्ण अन्यथा अणु
		socfpga_clk->भाग_reg = शून्य;
	पूर्ण

	rc = of_property_पढ़ो_u32_array(node, "clk-phase", clk_phase, 2);
	अगर (!rc) अणु
		socfpga_clk->clk_phase[0] = clk_phase[0];
		socfpga_clk->clk_phase[1] = clk_phase[1];

		socfpga_clk->sys_mgr_base_addr =
			syscon_regmap_lookup_by_compatible("altr,sys-mgr");
		अगर (IS_ERR(socfpga_clk->sys_mgr_base_addr)) अणु
			pr_err("%s: failed to find altr,sys-mgr regmap!\n",
					__func__);
			kमुक्त(socfpga_clk);
			वापस;
		पूर्ण
	पूर्ण

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = ops;
	init.flags = 0;

	init.num_parents = of_clk_parent_fill(node, parent_name, SOCFPGA_MAX_PARENTS);
	init.parent_names = parent_name;
	socfpga_clk->hw.hw.init = &init;
	hw_clk = &socfpga_clk->hw.hw;

	अगर (clk_hw_रेजिस्टर(शून्य, hw_clk)) अणु
		kमुक्त(socfpga_clk);
		वापस;
	पूर्ण
	rc = of_clk_add_provider(node, of_clk_src_simple_get, hw_clk);
	अगर (WARN_ON(rc))
		वापस;
पूर्ण

व्योम __init socfpga_a10_gate_init(काष्ठा device_node *node)
अणु
	__socfpga_gate_init(node, &gateclk_ops);
पूर्ण
