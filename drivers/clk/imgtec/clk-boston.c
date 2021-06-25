<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016-2017 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#घोषणा pr_fmt(fmt) "clk-boston: " fmt

#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <dt-bindings/घड़ी/boston-घड़ी.h>

#घोषणा BOSTON_PLAT_MMCMDIV		0x30
# define BOSTON_PLAT_MMCMDIV_CLK0DIV	(0xff << 0)
# define BOSTON_PLAT_MMCMDIV_INPUT	(0xff << 8)
# define BOSTON_PLAT_MMCMDIV_MUL	(0xff << 16)
# define BOSTON_PLAT_MMCMDIV_CLK1DIV	(0xff << 24)

#घोषणा BOSTON_CLK_COUNT 3

अटल u32 ext_field(u32 val, u32 mask)
अणु
	वापस (val & mask) >> (ffs(mask) - 1);
पूर्ण

अटल व्योम __init clk_boston_setup(काष्ठा device_node *np)
अणु
	अचिन्हित दीर्घ in_freq, cpu_freq, sys_freq;
	uपूर्णांक mmcmभाग, mul, cpu_भाग, sys_भाग;
	काष्ठा clk_hw_onecell_data *onecell;
	काष्ठा regmap *regmap;
	काष्ठा clk_hw *hw;
	पूर्णांक err;

	regmap = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(regmap)) अणु
		pr_err("failed to find regmap\n");
		वापस;
	पूर्ण

	err = regmap_पढ़ो(regmap, BOSTON_PLAT_MMCMDIV, &mmcmभाग);
	अगर (err) अणु
		pr_err("failed to read mmcm_div register: %d\n", err);
		वापस;
	पूर्ण

	in_freq = ext_field(mmcmभाग, BOSTON_PLAT_MMCMDIV_INPUT) * 1000000;
	mul = ext_field(mmcmभाग, BOSTON_PLAT_MMCMDIV_MUL);

	sys_भाग = ext_field(mmcmभाग, BOSTON_PLAT_MMCMDIV_CLK0DIV);
	sys_freq = mult_frac(in_freq, mul, sys_भाग);

	cpu_भाग = ext_field(mmcmभाग, BOSTON_PLAT_MMCMDIV_CLK1DIV);
	cpu_freq = mult_frac(in_freq, mul, cpu_भाग);

	onecell = kzalloc(काष्ठा_size(onecell, hws, BOSTON_CLK_COUNT),
			  GFP_KERNEL);
	अगर (!onecell)
		वापस;

	onecell->num = BOSTON_CLK_COUNT;

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "input", शून्य, 0, in_freq);
	अगर (IS_ERR(hw)) अणु
		pr_err("failed to register input clock: %ld\n", PTR_ERR(hw));
		जाओ fail_input;
	पूर्ण
	onecell->hws[BOSTON_CLK_INPUT] = hw;

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "sys", "input", 0, sys_freq);
	अगर (IS_ERR(hw)) अणु
		pr_err("failed to register sys clock: %ld\n", PTR_ERR(hw));
		जाओ fail_sys;
	पूर्ण
	onecell->hws[BOSTON_CLK_SYS] = hw;

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, "cpu", "input", 0, cpu_freq);
	अगर (IS_ERR(hw)) अणु
		pr_err("failed to register cpu clock: %ld\n", PTR_ERR(hw));
		जाओ fail_cpu;
	पूर्ण
	onecell->hws[BOSTON_CLK_CPU] = hw;

	err = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, onecell);
	अगर (err) अणु
		pr_err("failed to add DT provider: %d\n", err);
		जाओ fail_clk_add;
	पूर्ण

	वापस;

fail_clk_add:
	clk_hw_unरेजिस्टर_fixed_rate(onecell->hws[BOSTON_CLK_CPU]);
fail_cpu:
	clk_hw_unरेजिस्टर_fixed_rate(onecell->hws[BOSTON_CLK_SYS]);
fail_sys:
	clk_hw_unरेजिस्टर_fixed_rate(onecell->hws[BOSTON_CLK_INPUT]);
fail_input:
	kमुक्त(onecell);
पूर्ण

/*
 * Use CLK_OF_DECLARE so that this driver is probed early enough to provide the
 * CPU frequency क्रम use with the GIC or cop0 counters/समयrs.
 */
CLK_OF_DECLARE(clk_boston, "img,boston-clock", clk_boston_setup);
