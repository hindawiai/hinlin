<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell EBU SoC common घड़ी handling
 *
 * Copyright (C) 2012 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Andrew Lunn <andrew@lunn.ch>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/syscore_ops.h>

#समावेश "common.h"

/*
 * Core Clocks
 */

#घोषणा SSCG_CONF_MODE(reg)	(((reg) >> 16) & 0x3)
#घोषणा SSCG_SPREAD_DOWN	0x0
#घोषणा SSCG_SPREAD_UP		0x1
#घोषणा SSCG_SPREAD_CENTRAL	0x2
#घोषणा SSCG_CONF_LOW(reg)	(((reg) >> 8) & 0xFF)
#घोषणा SSCG_CONF_HIGH(reg)	((reg) & 0xFF)

अटल काष्ठा clk_onecell_data clk_data;

/*
 * This function can be used by the Kirkwood, the Armada 370, the
 * Armada XP and the Armada 375 SoC. The name of the function was
 * chosen following the dt convention: using the first known SoC
 * compatible with it.
 */
u32 kirkwood_fix_sscg_deviation(u32 प्रणाली_clk)
अणु
	काष्ठा device_node *sscg_np = शून्य;
	व्योम __iomem *sscg_map;
	u32 sscg_reg;
	s32 low_bound, high_bound;
	u64 freq_swing_half;

	sscg_np = of_find_node_by_name(शून्य, "sscg");
	अगर (sscg_np == शून्य) अणु
		pr_err("cannot get SSCG register node\n");
		वापस प्रणाली_clk;
	पूर्ण

	sscg_map = of_iomap(sscg_np, 0);
	अगर (sscg_map == शून्य) अणु
		pr_err("cannot map SSCG register\n");
		जाओ out;
	पूर्ण

	sscg_reg = पढ़ोl(sscg_map);
	high_bound = SSCG_CONF_HIGH(sscg_reg);
	low_bound = SSCG_CONF_LOW(sscg_reg);

	अगर ((high_bound - low_bound) <= 0)
		जाओ out;
	/*
	 * From Marvell engineer we got the following क्रमmula (when
	 * this code was written, the datasheet was erroneous)
	 * Spपढ़ो percentage = 1/96 * (H - L) / H
	 * H = SSCG_High_Boundary
	 * L = SSCG_Low_Boundary
	 *
	 * As the deviation is half of spपढ़ो then it lead to the
	 * following क्रमmula in the code.
	 *
	 * To aव्योम an overflow and not lose any signअगरicant digit in
	 * the same समय we have to use a 64 bit पूर्णांकeger.
	 */

	freq_swing_half = (((u64)high_bound - (u64)low_bound)
			* (u64)प्रणाली_clk);
	करो_भाग(freq_swing_half, (2 * 96 * high_bound));

	चयन (SSCG_CONF_MODE(sscg_reg)) अणु
	हाल SSCG_SPREAD_DOWN:
		प्रणाली_clk -= freq_swing_half;
		अवरोध;
	हाल SSCG_SPREAD_UP:
		प्रणाली_clk += freq_swing_half;
		अवरोध;
	हाल SSCG_SPREAD_CENTRAL:
	शेष:
		अवरोध;
	पूर्ण

	iounmap(sscg_map);

out:
	of_node_put(sscg_np);

	वापस प्रणाली_clk;
पूर्ण

व्योम __init mvebu_coreclk_setup(काष्ठा device_node *np,
				स्थिर काष्ठा coreclk_soc_desc *desc)
अणु
	स्थिर अक्षर *tclk_name = "tclk";
	स्थिर अक्षर *cpuclk_name = "cpuclk";
	व्योम __iomem *base;
	अचिन्हित दीर्घ rate;
	पूर्णांक n;

	base = of_iomap(np, 0);
	अगर (WARN_ON(!base))
		वापस;

	/* Allocate काष्ठा क्रम TCLK, cpu clk, and core ratio घड़ीs */
	clk_data.clk_num = 2 + desc->num_ratios;

	/* One more घड़ी क्रम the optional refclk */
	अगर (desc->get_refclk_freq)
		clk_data.clk_num += 1;

	clk_data.clks = kसुस्मृति(clk_data.clk_num, माप(*clk_data.clks),
				GFP_KERNEL);
	अगर (WARN_ON(!clk_data.clks)) अणु
		iounmap(base);
		वापस;
	पूर्ण

	/* Register TCLK */
	of_property_पढ़ो_string_index(np, "clock-output-names", 0,
				      &tclk_name);
	rate = desc->get_tclk_freq(base);
	clk_data.clks[0] = clk_रेजिस्टर_fixed_rate(शून्य, tclk_name, शून्य, 0,
						   rate);
	WARN_ON(IS_ERR(clk_data.clks[0]));

	/* Register CPU घड़ी */
	of_property_पढ़ो_string_index(np, "clock-output-names", 1,
				      &cpuclk_name);
	rate = desc->get_cpu_freq(base);

	अगर (desc->is_sscg_enabled && desc->fix_sscg_deviation
		&& desc->is_sscg_enabled(base))
		rate = desc->fix_sscg_deviation(rate);

	clk_data.clks[1] = clk_रेजिस्टर_fixed_rate(शून्य, cpuclk_name, शून्य, 0,
						   rate);
	WARN_ON(IS_ERR(clk_data.clks[1]));

	/* Register fixed-factor घड़ीs derived from CPU घड़ी */
	क्रम (n = 0; n < desc->num_ratios; n++) अणु
		स्थिर अक्षर *rclk_name = desc->ratios[n].name;
		पूर्णांक mult, भाग;

		of_property_पढ़ो_string_index(np, "clock-output-names",
					      2+n, &rclk_name);
		desc->get_clk_ratio(base, desc->ratios[n].id, &mult, &भाग);
		clk_data.clks[2+n] = clk_रेजिस्टर_fixed_factor(शून्य, rclk_name,
				       cpuclk_name, 0, mult, भाग);
		WARN_ON(IS_ERR(clk_data.clks[2+n]));
	पूर्ण

	/* Register optional refclk */
	अगर (desc->get_refclk_freq) अणु
		स्थिर अक्षर *name = "refclk";
		of_property_पढ़ो_string_index(np, "clock-output-names",
					      2 + desc->num_ratios, &name);
		rate = desc->get_refclk_freq(base);
		clk_data.clks[2 + desc->num_ratios] =
			clk_रेजिस्टर_fixed_rate(शून्य, name, शून्य, 0, rate);
		WARN_ON(IS_ERR(clk_data.clks[2 + desc->num_ratios]));
	पूर्ण

	/* SAR रेजिस्टर isn't needed anymore */
	iounmap(base);

	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);
पूर्ण

/*
 * Clock Gating Control
 */

DEFINE_SPINLOCK(ctrl_gating_lock);

काष्ठा clk_gating_ctrl अणु
	spinlock_t *lock;
	काष्ठा clk **gates;
	पूर्णांक num_gates;
	व्योम __iomem *base;
	u32 saved_reg;
पूर्ण;

अटल काष्ठा clk_gating_ctrl *ctrl;

अटल काष्ठा clk *clk_gating_get_src(
	काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	पूर्णांक n;

	अगर (clkspec->args_count < 1)
		वापस ERR_PTR(-EINVAL);

	क्रम (n = 0; n < ctrl->num_gates; n++) अणु
		काष्ठा clk_gate *gate =
			to_clk_gate(__clk_get_hw(ctrl->gates[n]));
		अगर (clkspec->args[0] == gate->bit_idx)
			वापस ctrl->gates[n];
	पूर्ण
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक mvebu_clk_gating_suspend(व्योम)
अणु
	ctrl->saved_reg = पढ़ोl(ctrl->base);
	वापस 0;
पूर्ण

अटल व्योम mvebu_clk_gating_resume(व्योम)
अणु
	ग_लिखोl(ctrl->saved_reg, ctrl->base);
पूर्ण

अटल काष्ठा syscore_ops clk_gate_syscore_ops = अणु
	.suspend = mvebu_clk_gating_suspend,
	.resume = mvebu_clk_gating_resume,
पूर्ण;

व्योम __init mvebu_clk_gating_setup(काष्ठा device_node *np,
				   स्थिर काष्ठा clk_gating_soc_desc *desc)
अणु
	काष्ठा clk *clk;
	व्योम __iomem *base;
	स्थिर अक्षर *शेष_parent = शून्य;
	पूर्णांक n;

	अगर (ctrl) अणु
		pr_err("mvebu-clk-gating: cannot instantiate more than one gateable clock device\n");
		वापस;
	पूर्ण

	base = of_iomap(np, 0);
	अगर (WARN_ON(!base))
		वापस;

	clk = of_clk_get(np, 0);
	अगर (!IS_ERR(clk)) अणु
		शेष_parent = __clk_get_name(clk);
		clk_put(clk);
	पूर्ण

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (WARN_ON(!ctrl))
		जाओ ctrl_out;

	/* lock must alपढ़ोy be initialized */
	ctrl->lock = &ctrl_gating_lock;

	ctrl->base = base;

	/* Count, allocate, and रेजिस्टर घड़ी gates */
	क्रम (n = 0; desc[n].name;)
		n++;

	ctrl->num_gates = n;
	ctrl->gates = kसुस्मृति(ctrl->num_gates, माप(*ctrl->gates),
			      GFP_KERNEL);
	अगर (WARN_ON(!ctrl->gates))
		जाओ gates_out;

	क्रम (n = 0; n < ctrl->num_gates; n++) अणु
		स्थिर अक्षर *parent =
			(desc[n].parent) ? desc[n].parent : शेष_parent;
		ctrl->gates[n] = clk_रेजिस्टर_gate(शून्य, desc[n].name, parent,
					desc[n].flags, base, desc[n].bit_idx,
					0, ctrl->lock);
		WARN_ON(IS_ERR(ctrl->gates[n]));
	पूर्ण

	of_clk_add_provider(np, clk_gating_get_src, ctrl);

	रेजिस्टर_syscore_ops(&clk_gate_syscore_ops);

	वापस;
gates_out:
	kमुक्त(ctrl);
ctrl_out:
	iounmap(base);
पूर्ण
