<शैली गुरु>
/*
 * OMAP gate घड़ी support
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

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल पूर्णांक omap36xx_gate_clk_enable_with_hsभाग_restore(काष्ठा clk_hw *clk);

अटल स्थिर काष्ठा clk_ops omap_gate_clkdm_clk_ops = अणु
	.init		= &omap2_init_clk_clkdm,
	.enable		= &omap2_clkops_enable_clkdm,
	.disable	= &omap2_clkops_disable_clkdm,
	.restore_context = clk_gate_restore_context,
पूर्ण;

स्थिर काष्ठा clk_ops omap_gate_clk_ops = अणु
	.init		= &omap2_init_clk_clkdm,
	.enable		= &omap2_dflt_clk_enable,
	.disable	= &omap2_dflt_clk_disable,
	.is_enabled	= &omap2_dflt_clk_is_enabled,
	.restore_context = clk_gate_restore_context,
पूर्ण;

अटल स्थिर काष्ठा clk_ops omap_gate_clk_hsभाग_restore_ops = अणु
	.init		= &omap2_init_clk_clkdm,
	.enable		= &omap36xx_gate_clk_enable_with_hsभाग_restore,
	.disable	= &omap2_dflt_clk_disable,
	.is_enabled	= &omap2_dflt_clk_is_enabled,
	.restore_context = clk_gate_restore_context,
पूर्ण;

/**
 * omap36xx_gate_clk_enable_with_hsभाग_restore - enable घड़ीs suffering
 *         from HSDivider PWRDN problem Implements Errata ID: i556.
 * @hw: DPLL output काष्ठा clk_hw
 *
 * 3630 only: dpll3_m3_ck, dpll4_m2_ck, dpll4_m3_ck, dpll4_m4_ck,
 * dpll4_m5_ck & dpll4_m6_ck भागiders माला_लो loaded with reset
 * valueafter their respective PWRDN bits are set.  Any dummy ग_लिखो
 * (Any other value dअगरferent from the Read value) to the
 * corresponding CM_CLKSEL रेजिस्टर will refresh the भागiders.
 */
अटल पूर्णांक omap36xx_gate_clk_enable_with_hsभाग_restore(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_omap_भागider *parent;
	काष्ठा clk_hw *parent_hw;
	u32 dummy_v, orig_v;
	पूर्णांक ret;

	/* Clear PWRDN bit of HSDIVIDER */
	ret = omap2_dflt_clk_enable(hw);

	/* Parent is the x2 node, get parent of parent क्रम the m2 भाग */
	parent_hw = clk_hw_get_parent(clk_hw_get_parent(hw));
	parent = to_clk_omap_भागider(parent_hw);

	/* Restore the भागiders */
	अगर (!ret) अणु
		orig_v = ti_clk_ll_ops->clk_पढ़ोl(&parent->reg);
		dummy_v = orig_v;

		/* Write any other value dअगरferent from the Read value */
		dummy_v ^= (1 << parent->shअगरt);
		ti_clk_ll_ops->clk_ग_लिखोl(dummy_v, &parent->reg);

		/* Write the original भागider */
		ti_clk_ll_ops->clk_ग_लिखोl(orig_v, &parent->reg);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा clk *_रेजिस्टर_gate(काष्ठा device *dev, स्थिर अक्षर *name,
				  स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
				  काष्ठा clk_omap_reg *reg, u8 bit_idx,
				  u8 clk_gate_flags, स्थिर काष्ठा clk_ops *ops,
				  स्थिर काष्ठा clk_hw_omap_ops *hw_ops)
अणु
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw_omap *clk_hw;
	काष्ठा clk *clk;

	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	अगर (!clk_hw)
		वापस ERR_PTR(-ENOMEM);

	clk_hw->hw.init = &init;

	init.name = name;
	init.ops = ops;

	स_नकल(&clk_hw->enable_reg, reg, माप(*reg));
	clk_hw->enable_bit = bit_idx;
	clk_hw->ops = hw_ops;

	clk_hw->flags = clk_gate_flags;

	init.parent_names = &parent_name;
	init.num_parents = 1;

	init.flags = flags;

	clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &clk_hw->hw, name);

	अगर (IS_ERR(clk))
		kमुक्त(clk_hw);

	वापस clk;
पूर्ण

अटल व्योम __init _of_ti_gate_clk_setup(काष्ठा device_node *node,
					 स्थिर काष्ठा clk_ops *ops,
					 स्थिर काष्ठा clk_hw_omap_ops *hw_ops)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_omap_reg reg;
	u8 enable_bit = 0;
	u32 val;
	u32 flags = 0;
	u8 clk_gate_flags = 0;

	अगर (ops != &omap_gate_clkdm_clk_ops) अणु
		अगर (ti_clk_get_reg_addr(node, 0, &reg))
			वापस;

		अगर (!of_property_पढ़ो_u32(node, "ti,bit-shift", &val))
			enable_bit = val;
	पूर्ण

	अगर (of_clk_get_parent_count(node) != 1) अणु
		pr_err("%pOFn must have 1 parent\n", node);
		वापस;
	पूर्ण

	parent_name = of_clk_get_parent_name(node, 0);

	अगर (of_property_पढ़ो_bool(node, "ti,set-rate-parent"))
		flags |= CLK_SET_RATE_PARENT;

	अगर (of_property_पढ़ो_bool(node, "ti,set-bit-to-disable"))
		clk_gate_flags |= INVERT_ENABLE;

	clk = _रेजिस्टर_gate(शून्य, node->name, parent_name, flags, &reg,
			     enable_bit, clk_gate_flags, ops, hw_ops);

	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
पूर्ण

अटल व्योम __init
_of_ti_composite_gate_clk_setup(काष्ठा device_node *node,
				स्थिर काष्ठा clk_hw_omap_ops *hw_ops)
अणु
	काष्ठा clk_hw_omap *gate;
	u32 val = 0;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस;

	अगर (ti_clk_get_reg_addr(node, 0, &gate->enable_reg))
		जाओ cleanup;

	of_property_पढ़ो_u32(node, "ti,bit-shift", &val);

	gate->enable_bit = val;
	gate->ops = hw_ops;

	अगर (!ti_clk_add_component(node, &gate->hw, CLK_COMPONENT_TYPE_GATE))
		वापस;

cleanup:
	kमुक्त(gate);
पूर्ण

अटल व्योम __init
of_ti_composite_no_रुको_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_composite_gate_clk_setup(node, शून्य);
पूर्ण
CLK_OF_DECLARE(ti_composite_no_रुको_gate_clk, "ti,composite-no-wait-gate-clock",
	       of_ti_composite_no_रुको_gate_clk_setup);

#अगर defined(CONFIG_ARCH_OMAP2) || defined(CONFIG_ARCH_OMAP3)
अटल व्योम __init of_ti_composite_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_composite_gate_clk_setup(node, &clkhwops_iclk_रुको);
पूर्ण
CLK_OF_DECLARE(ti_composite_पूर्णांकerface_clk, "ti,composite-interface-clock",
	       of_ti_composite_पूर्णांकerface_clk_setup);
#पूर्ण_अगर

अटल व्योम __init of_ti_composite_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_composite_gate_clk_setup(node, &clkhwops_रुको);
पूर्ण
CLK_OF_DECLARE(ti_composite_gate_clk, "ti,composite-gate-clock",
	       of_ti_composite_gate_clk_setup);


अटल व्योम __init of_ti_clkdm_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_gate_clk_setup(node, &omap_gate_clkdm_clk_ops, शून्य);
पूर्ण
CLK_OF_DECLARE(ti_clkdm_gate_clk, "ti,clkdm-gate-clock",
	       of_ti_clkdm_gate_clk_setup);

अटल व्योम __init of_ti_hsभाग_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_gate_clk_setup(node, &omap_gate_clk_hsभाग_restore_ops,
			      &clkhwops_रुको);
पूर्ण
CLK_OF_DECLARE(ti_hsभाग_gate_clk, "ti,hsdiv-gate-clock",
	       of_ti_hsभाग_gate_clk_setup);

अटल व्योम __init of_ti_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_gate_clk_setup(node, &omap_gate_clk_ops, शून्य);
पूर्ण
CLK_OF_DECLARE(ti_gate_clk, "ti,gate-clock", of_ti_gate_clk_setup);

अटल व्योम __init of_ti_रुको_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_gate_clk_setup(node, &omap_gate_clk_ops, &clkhwops_रुको);
पूर्ण
CLK_OF_DECLARE(ti_रुको_gate_clk, "ti,wait-gate-clock",
	       of_ti_रुको_gate_clk_setup);

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल व्योम __init of_ti_am35xx_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_gate_clk_setup(node, &omap_gate_clk_ops,
			      &clkhwops_am35xx_ipss_module_रुको);
पूर्ण
CLK_OF_DECLARE(ti_am35xx_gate_clk, "ti,am35xx-gate-clock",
	       of_ti_am35xx_gate_clk_setup);

अटल व्योम __init of_ti_dss_gate_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_gate_clk_setup(node, &omap_gate_clk_ops,
			      &clkhwops_omap3430es2_dss_usbhost_रुको);
पूर्ण
CLK_OF_DECLARE(ti_dss_gate_clk, "ti,dss-gate-clock",
	       of_ti_dss_gate_clk_setup);
#पूर्ण_अगर
