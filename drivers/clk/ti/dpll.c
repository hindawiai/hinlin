<शैली गुरु>
/*
 * OMAP DPLL घड़ी support
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>
#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX)
अटल स्थिर काष्ठा clk_ops dpll_m4xen_ck_ops = अणु
	.enable		= &omap3_noncore_dpll_enable,
	.disable	= &omap3_noncore_dpll_disable,
	.recalc_rate	= &omap4_dpll_regm4xen_recalc,
	.round_rate	= &omap4_dpll_regm4xen_round_rate,
	.set_rate	= &omap3_noncore_dpll_set_rate,
	.set_parent	= &omap3_noncore_dpll_set_parent,
	.set_rate_and_parent	= &omap3_noncore_dpll_set_rate_and_parent,
	.determine_rate	= &omap4_dpll_regm4xen_determine_rate,
	.get_parent	= &omap2_init_dpll_parent,
	.save_context	= &omap3_core_dpll_save_context,
	.restore_context = &omap3_core_dpll_restore_context,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा clk_ops dpll_m4xen_ck_ops = अणुपूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_OMAP3) || defined(CONFIG_ARCH_OMAP4) || \
	defined(CONFIG_SOC_OMAP5) || defined(CONFIG_SOC_DRA7XX) || \
	defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_AM43XX)
अटल स्थिर काष्ठा clk_ops dpll_core_ck_ops = अणु
	.recalc_rate	= &omap3_dpll_recalc,
	.get_parent	= &omap2_init_dpll_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_ops dpll_ck_ops = अणु
	.enable		= &omap3_noncore_dpll_enable,
	.disable	= &omap3_noncore_dpll_disable,
	.recalc_rate	= &omap3_dpll_recalc,
	.round_rate	= &omap2_dpll_round_rate,
	.set_rate	= &omap3_noncore_dpll_set_rate,
	.set_parent	= &omap3_noncore_dpll_set_parent,
	.set_rate_and_parent	= &omap3_noncore_dpll_set_rate_and_parent,
	.determine_rate	= &omap3_noncore_dpll_determine_rate,
	.get_parent	= &omap2_init_dpll_parent,
	.save_context	= &omap3_noncore_dpll_save_context,
	.restore_context = &omap3_noncore_dpll_restore_context,
पूर्ण;

अटल स्थिर काष्ठा clk_ops dpll_no_gate_ck_ops = अणु
	.recalc_rate	= &omap3_dpll_recalc,
	.get_parent	= &omap2_init_dpll_parent,
	.round_rate	= &omap2_dpll_round_rate,
	.set_rate	= &omap3_noncore_dpll_set_rate,
	.set_parent	= &omap3_noncore_dpll_set_parent,
	.set_rate_and_parent	= &omap3_noncore_dpll_set_rate_and_parent,
	.determine_rate	= &omap3_noncore_dpll_determine_rate,
	.save_context	= &omap3_noncore_dpll_save_context,
	.restore_context = &omap3_noncore_dpll_restore_context
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा clk_ops dpll_core_ck_ops = अणुपूर्ण;
अटल स्थिर काष्ठा clk_ops dpll_ck_ops = अणुपूर्ण;
अटल स्थिर काष्ठा clk_ops dpll_no_gate_ck_ops = अणुपूर्ण;
स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3_dpll = अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP2
अटल स्थिर काष्ठा clk_ops omap2_dpll_core_ck_ops = अणु
	.get_parent	= &omap2_init_dpll_parent,
	.recalc_rate	= &omap2_dpllcore_recalc,
	.round_rate	= &omap2_dpll_round_rate,
	.set_rate	= &omap2_reprogram_dpllcore,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा clk_ops omap2_dpll_core_ck_ops = अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल स्थिर काष्ठा clk_ops omap3_dpll_core_ck_ops = अणु
	.get_parent	= &omap2_init_dpll_parent,
	.recalc_rate	= &omap3_dpll_recalc,
	.round_rate	= &omap2_dpll_round_rate,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा clk_ops omap3_dpll_core_ck_ops = अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल स्थिर काष्ठा clk_ops omap3_dpll_ck_ops = अणु
	.enable		= &omap3_noncore_dpll_enable,
	.disable	= &omap3_noncore_dpll_disable,
	.get_parent	= &omap2_init_dpll_parent,
	.recalc_rate	= &omap3_dpll_recalc,
	.set_rate	= &omap3_noncore_dpll_set_rate,
	.set_parent	= &omap3_noncore_dpll_set_parent,
	.set_rate_and_parent	= &omap3_noncore_dpll_set_rate_and_parent,
	.determine_rate	= &omap3_noncore_dpll_determine_rate,
	.round_rate	= &omap2_dpll_round_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops omap3_dpll5_ck_ops = अणु
	.enable		= &omap3_noncore_dpll_enable,
	.disable	= &omap3_noncore_dpll_disable,
	.get_parent	= &omap2_init_dpll_parent,
	.recalc_rate	= &omap3_dpll_recalc,
	.set_rate	= &omap3_dpll5_set_rate,
	.set_parent	= &omap3_noncore_dpll_set_parent,
	.set_rate_and_parent	= &omap3_noncore_dpll_set_rate_and_parent,
	.determine_rate	= &omap3_noncore_dpll_determine_rate,
	.round_rate	= &omap2_dpll_round_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops omap3_dpll_per_ck_ops = अणु
	.enable		= &omap3_noncore_dpll_enable,
	.disable	= &omap3_noncore_dpll_disable,
	.get_parent	= &omap2_init_dpll_parent,
	.recalc_rate	= &omap3_dpll_recalc,
	.set_rate	= &omap3_dpll4_set_rate,
	.set_parent	= &omap3_noncore_dpll_set_parent,
	.set_rate_and_parent	= &omap3_dpll4_set_rate_and_parent,
	.determine_rate	= &omap3_noncore_dpll_determine_rate,
	.round_rate	= &omap2_dpll_round_rate,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा clk_ops dpll_x2_ck_ops = अणु
	.recalc_rate	= &omap3_clkoutx2_recalc,
पूर्ण;

/**
 * _रेजिस्टर_dpll - low level registration of a DPLL घड़ी
 * @user: poपूर्णांकer to the hardware घड़ी definition क्रम the घड़ी
 * @node: device node क्रम the घड़ी
 *
 * Finalizes DPLL registration process. In हाल a failure (clk-ref or
 * clk-bypass is missing), the घड़ी is added to retry list and
 * the initialization is retried on later stage.
 */
अटल व्योम __init _रेजिस्टर_dpll(व्योम *user,
				  काष्ठा device_node *node)
अणु
	काष्ठा clk_hw *hw = user;
	काष्ठा clk_hw_omap *clk_hw = to_clk_hw_omap(hw);
	काष्ठा dpll_data *dd = clk_hw->dpll_data;
	काष्ठा clk *clk;
	स्थिर काष्ठा clk_init_data *init = hw->init;

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_debug("clk-ref missing for %pOFn, retry later\n",
			 node);
		अगर (!ti_clk_retry_init(node, hw, _रेजिस्टर_dpll))
			वापस;

		जाओ cleanup;
	पूर्ण

	dd->clk_ref = __clk_get_hw(clk);

	clk = of_clk_get(node, 1);

	अगर (IS_ERR(clk)) अणु
		pr_debug("clk-bypass missing for %pOFn, retry later\n",
			 node);
		अगर (!ti_clk_retry_init(node, hw, _रेजिस्टर_dpll))
			वापस;

		जाओ cleanup;
	पूर्ण

	dd->clk_bypass = __clk_get_hw(clk);

	/* रेजिस्टर the घड़ी */
	clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &clk_hw->hw, node->name);

	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		kमुक्त(init->parent_names);
		kमुक्त(init);
		वापस;
	पूर्ण

cleanup:
	kमुक्त(clk_hw->dpll_data);
	kमुक्त(init->parent_names);
	kमुक्त(init);
	kमुक्त(clk_hw);
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX) || defined(CONFIG_SOC_AM33XX) || \
	defined(CONFIG_SOC_AM43XX)
/**
 * _रेजिस्टर_dpll_x2 - Registers a DPLLx2 घड़ी
 * @node: device node क्रम this घड़ी
 * @ops: clk_ops क्रम this घड़ी
 * @hw_ops: clk_hw_ops क्रम this घड़ी
 *
 * Initializes a DPLL x 2 घड़ी from device tree data.
 */
अटल व्योम _रेजिस्टर_dpll_x2(काष्ठा device_node *node,
			      स्थिर काष्ठा clk_ops *ops,
			      स्थिर काष्ठा clk_hw_omap_ops *hw_ops)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw_omap *clk_hw;
	स्थिर अक्षर *name = node->name;
	स्थिर अक्षर *parent_name;

	parent_name = of_clk_get_parent_name(node, 0);
	अगर (!parent_name) अणु
		pr_err("%pOFn must have parent\n", node);
		वापस;
	पूर्ण

	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	अगर (!clk_hw)
		वापस;

	clk_hw->ops = hw_ops;
	clk_hw->hw.init = &init;

	init.name = name;
	init.ops = ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX)
	अगर (hw_ops == &clkhwops_omap4_dpllmx) अणु
		पूर्णांक ret;

		/* Check अगर रेजिस्टर defined, अगर not, drop hw-ops */
		ret = of_property_count_elems_of_size(node, "reg", 1);
		अगर (ret <= 0) अणु
			clk_hw->ops = शून्य;
		पूर्ण अन्यथा अगर (ti_clk_get_reg_addr(node, 0, &clk_hw->clksel_reg)) अणु
			kमुक्त(clk_hw);
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* रेजिस्टर the घड़ी */
	clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &clk_hw->hw, name);

	अगर (IS_ERR(clk))
		kमुक्त(clk_hw);
	अन्यथा
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
पूर्ण
#पूर्ण_अगर

/**
 * of_ti_dpll_setup - Setup function क्रम OMAP DPLL घड़ीs
 * @node: device node containing the DPLL info
 * @ops: ops क्रम the DPLL
 * @ddt: DPLL data ढाँचा to use
 *
 * Initializes a DPLL घड़ी from device tree data.
 */
अटल व्योम __init of_ti_dpll_setup(काष्ठा device_node *node,
				    स्थिर काष्ठा clk_ops *ops,
				    स्थिर काष्ठा dpll_data *ddt)
अणु
	काष्ठा clk_hw_omap *clk_hw = शून्य;
	काष्ठा clk_init_data *init = शून्य;
	स्थिर अक्षर **parent_names = शून्य;
	काष्ठा dpll_data *dd = शून्य;
	u8 dpll_mode = 0;

	dd = kmemdup(ddt, माप(*dd), GFP_KERNEL);
	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	init = kzalloc(माप(*init), GFP_KERNEL);
	अगर (!dd || !clk_hw || !init)
		जाओ cleanup;

	clk_hw->dpll_data = dd;
	clk_hw->ops = &clkhwops_omap3_dpll;
	clk_hw->hw.init = init;

	init->name = node->name;
	init->ops = ops;

	init->num_parents = of_clk_get_parent_count(node);
	अगर (!init->num_parents) अणु
		pr_err("%pOFn must have parent(s)\n", node);
		जाओ cleanup;
	पूर्ण

	parent_names = kसुस्मृति(init->num_parents, माप(अक्षर *), GFP_KERNEL);
	अगर (!parent_names)
		जाओ cleanup;

	of_clk_parent_fill(node, parent_names, init->num_parents);

	init->parent_names = parent_names;

	अगर (ti_clk_get_reg_addr(node, 0, &dd->control_reg))
		जाओ cleanup;

	/*
	 * Special हाल क्रम OMAP2 DPLL, रेजिस्टर order is dअगरferent due to
	 * missing idlest_reg, also clkhwops is dअगरferent. Detected from
	 * missing idlest_mask.
	 */
	अगर (!dd->idlest_mask) अणु
		अगर (ti_clk_get_reg_addr(node, 1, &dd->mult_भाग1_reg))
			जाओ cleanup;
#अगर_घोषित CONFIG_ARCH_OMAP2
		clk_hw->ops = &clkhwops_omap2xxx_dpll;
		omap2xxx_clkt_dpllcore_init(&clk_hw->hw);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अगर (ti_clk_get_reg_addr(node, 1, &dd->idlest_reg))
			जाओ cleanup;

		अगर (ti_clk_get_reg_addr(node, 2, &dd->mult_भाग1_reg))
			जाओ cleanup;
	पूर्ण

	अगर (dd->स्वतःidle_mask) अणु
		अगर (ti_clk_get_reg_addr(node, 3, &dd->स्वतःidle_reg))
			जाओ cleanup;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "ti,low-power-stop"))
		dpll_mode |= 1 << DPLL_LOW_POWER_STOP;

	अगर (of_property_पढ़ो_bool(node, "ti,low-power-bypass"))
		dpll_mode |= 1 << DPLL_LOW_POWER_BYPASS;

	अगर (of_property_पढ़ो_bool(node, "ti,lock"))
		dpll_mode |= 1 << DPLL_LOCKED;

	अगर (dpll_mode)
		dd->modes = dpll_mode;

	_रेजिस्टर_dpll(&clk_hw->hw, node);
	वापस;

cleanup:
	kमुक्त(dd);
	kमुक्त(parent_names);
	kमुक्त(init);
	kमुक्त(clk_hw);
पूर्ण

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX)
अटल व्योम __init of_ti_omap4_dpll_x2_setup(काष्ठा device_node *node)
अणु
	_रेजिस्टर_dpll_x2(node, &dpll_x2_ck_ops, &clkhwops_omap4_dpllmx);
पूर्ण
CLK_OF_DECLARE(ti_omap4_dpll_x2_घड़ी, "ti,omap4-dpll-x2-clock",
	       of_ti_omap4_dpll_x2_setup);
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_AM43XX)
अटल व्योम __init of_ti_am3_dpll_x2_setup(काष्ठा device_node *node)
अणु
	_रेजिस्टर_dpll_x2(node, &dpll_x2_ck_ops, शून्य);
पूर्ण
CLK_OF_DECLARE(ti_am3_dpll_x2_घड़ी, "ti,am3-dpll-x2-clock",
	       of_ti_am3_dpll_x2_setup);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल व्योम __init of_ti_omap3_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.freqsel_mask = 0xf0,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	अगर ((of_machine_is_compatible("ti,omap3630") ||
	     of_machine_is_compatible("ti,omap36xx")) &&
	     of_node_name_eq(node, "dpll5_ck"))
		of_ti_dpll_setup(node, &omap3_dpll5_ck_ops, &dd);
	अन्यथा
		of_ti_dpll_setup(node, &omap3_dpll_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap3_dpll_घड़ी, "ti,omap3-dpll-clock",
	       of_ti_omap3_dpll_setup);

अटल व्योम __init of_ti_omap3_core_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0x7ff << 16,
		.भाग1_mask = 0x7f << 8,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.freqsel_mask = 0xf0,
	पूर्ण;

	of_ti_dpll_setup(node, &omap3_dpll_core_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap3_core_dpll_घड़ी, "ti,omap3-dpll-core-clock",
	       of_ti_omap3_core_dpll_setup);

अटल व्योम __init of_ti_omap3_per_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1 << 1,
		.enable_mask = 0x7 << 16,
		.स्वतःidle_mask = 0x7 << 3,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.freqsel_mask = 0xf00000,
		.modes = (1 << DPLL_LOW_POWER_STOP) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &omap3_dpll_per_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap3_per_dpll_घड़ी, "ti,omap3-dpll-per-clock",
	       of_ti_omap3_per_dpll_setup);

अटल व्योम __init of_ti_omap3_per_jtype_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1 << 1,
		.enable_mask = 0x7 << 16,
		.स्वतःidle_mask = 0x7 << 3,
		.mult_mask = 0xfff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 4095,
		.max_भागider = 128,
		.min_भागider = 1,
		.sdभाग_mask = 0xff << 24,
		.dco_mask = 0xe << 20,
		.flags = DPLL_J_TYPE,
		.modes = (1 << DPLL_LOW_POWER_STOP) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &omap3_dpll_per_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap3_per_jtype_dpll_घड़ी, "ti,omap3-dpll-per-j-type-clock",
	       of_ti_omap3_per_jtype_dpll_setup);
#पूर्ण_अगर

अटल व्योम __init of_ti_omap4_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap4_dpll_घड़ी, "ti,omap4-dpll-clock",
	       of_ti_omap4_dpll_setup);

अटल व्योम __init of_ti_omap5_mpu_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.dcc_mask = BIT(22),
		.dcc_rate = 1400000000, /* DCC beyond 1.4GHz */
		.min_भागider = 1,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(of_ti_omap5_mpu_dpll_घड़ी, "ti,omap5-mpu-dpll-clock",
	       of_ti_omap5_mpu_dpll_setup);

अटल व्योम __init of_ti_omap4_core_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_core_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap4_core_dpll_घड़ी, "ti,omap4-dpll-core-clock",
	       of_ti_omap4_core_dpll_setup);

#अगर defined(CONFIG_ARCH_OMAP4) || defined(CONFIG_SOC_OMAP5) || \
	defined(CONFIG_SOC_DRA7XX)
अटल व्योम __init of_ti_omap4_m4xen_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.m4xen_mask = 0x800,
		.lpmode_mask = 1 << 10,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_m4xen_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap4_m4xen_dpll_घड़ी, "ti,omap4-dpll-m4xen-clock",
	       of_ti_omap4_m4xen_dpll_setup);

अटल व्योम __init of_ti_omap4_jtype_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.स्वतःidle_mask = 0x7,
		.mult_mask = 0xfff << 8,
		.भाग1_mask = 0xff,
		.max_multiplier = 4095,
		.max_भागider = 256,
		.min_भागider = 1,
		.sdभाग_mask = 0xff << 24,
		.flags = DPLL_J_TYPE,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_m4xen_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap4_jtype_dpll_घड़ी, "ti,omap4-dpll-j-type-clock",
	       of_ti_omap4_jtype_dpll_setup);
#पूर्ण_अगर

अटल व्योम __init of_ti_am3_no_gate_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.max_rate = 1000000000,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_no_gate_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_am3_no_gate_dpll_घड़ी, "ti,am3-dpll-no-gate-clock",
	       of_ti_am3_no_gate_dpll_setup);

अटल व्योम __init of_ti_am3_jtype_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 4095,
		.max_भागider = 256,
		.min_भागider = 2,
		.flags = DPLL_J_TYPE,
		.max_rate = 2000000000,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_am3_jtype_dpll_घड़ी, "ti,am3-dpll-j-type-clock",
	       of_ti_am3_jtype_dpll_setup);

अटल व्योम __init of_ti_am3_no_gate_jtype_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.max_rate = 2000000000,
		.flags = DPLL_J_TYPE,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_no_gate_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_am3_no_gate_jtype_dpll_घड़ी,
	       "ti,am3-dpll-no-gate-j-type-clock",
	       of_ti_am3_no_gate_jtype_dpll_setup);

अटल व्योम __init of_ti_am3_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.max_rate = 1000000000,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_am3_dpll_घड़ी, "ti,am3-dpll-clock", of_ti_am3_dpll_setup);

अटल व्योम __init of_ti_am3_core_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.idlest_mask = 0x1,
		.enable_mask = 0x7,
		.mult_mask = 0x7ff << 8,
		.भाग1_mask = 0x7f,
		.max_multiplier = 2047,
		.max_भागider = 128,
		.min_भागider = 1,
		.max_rate = 1000000000,
		.modes = (1 << DPLL_LOW_POWER_BYPASS) | (1 << DPLL_LOCKED),
	पूर्ण;

	of_ti_dpll_setup(node, &dpll_core_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_am3_core_dpll_घड़ी, "ti,am3-dpll-core-clock",
	       of_ti_am3_core_dpll_setup);

अटल व्योम __init of_ti_omap2_core_dpll_setup(काष्ठा device_node *node)
अणु
	स्थिर काष्ठा dpll_data dd = अणु
		.enable_mask = 0x3,
		.mult_mask = 0x3ff << 12,
		.भाग1_mask = 0xf << 8,
		.max_भागider = 16,
		.min_भागider = 1,
	पूर्ण;

	of_ti_dpll_setup(node, &omap2_dpll_core_ck_ops, &dd);
पूर्ण
CLK_OF_DECLARE(ti_omap2_core_dpll_घड़ी, "ti,omap2-dpll-core-clock",
	       of_ti_omap2_core_dpll_setup);
