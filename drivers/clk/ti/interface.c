<शैली गुरु>
/*
 * OMAP पूर्णांकerface घड़ी support
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
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>
#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल स्थिर काष्ठा clk_ops ti_पूर्णांकerface_clk_ops = अणु
	.init		= &omap2_init_clk_clkdm,
	.enable		= &omap2_dflt_clk_enable,
	.disable	= &omap2_dflt_clk_disable,
	.is_enabled	= &omap2_dflt_clk_is_enabled,
पूर्ण;

अटल काष्ठा clk *_रेजिस्टर_पूर्णांकerface(काष्ठा device *dev, स्थिर अक्षर *name,
				       स्थिर अक्षर *parent_name,
				       काष्ठा clk_omap_reg *reg, u8 bit_idx,
				       स्थिर काष्ठा clk_hw_omap_ops *ops)
अणु
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw_omap *clk_hw;
	काष्ठा clk *clk;

	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	अगर (!clk_hw)
		वापस ERR_PTR(-ENOMEM);

	clk_hw->hw.init = &init;
	clk_hw->ops = ops;
	स_नकल(&clk_hw->enable_reg, reg, माप(*reg));
	clk_hw->enable_bit = bit_idx;

	init.name = name;
	init.ops = &ti_पूर्णांकerface_clk_ops;
	init.flags = 0;

	init.num_parents = 1;
	init.parent_names = &parent_name;

	clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &clk_hw->hw, name);

	अगर (IS_ERR(clk))
		kमुक्त(clk_hw);

	वापस clk;
पूर्ण

अटल व्योम __init _of_ti_पूर्णांकerface_clk_setup(काष्ठा device_node *node,
					      स्थिर काष्ठा clk_hw_omap_ops *ops)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_omap_reg reg;
	u8 enable_bit = 0;
	u32 val;

	अगर (ti_clk_get_reg_addr(node, 0, &reg))
		वापस;

	अगर (!of_property_पढ़ो_u32(node, "ti,bit-shift", &val))
		enable_bit = val;

	parent_name = of_clk_get_parent_name(node, 0);
	अगर (!parent_name) अणु
		pr_err("%pOFn must have a parent\n", node);
		वापस;
	पूर्ण

	clk = _रेजिस्टर_पूर्णांकerface(शून्य, node->name, parent_name, &reg,
				  enable_bit, ops);

	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
पूर्ण

अटल व्योम __init of_ti_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node, &clkhwops_iclk_रुको);
पूर्ण
CLK_OF_DECLARE(ti_पूर्णांकerface_clk, "ti,omap3-interface-clock",
	       of_ti_पूर्णांकerface_clk_setup);

अटल व्योम __init of_ti_no_रुको_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node, &clkhwops_iclk);
पूर्ण
CLK_OF_DECLARE(ti_no_रुको_पूर्णांकerface_clk, "ti,omap3-no-wait-interface-clock",
	       of_ti_no_रुको_पूर्णांकerface_clk_setup);

#अगर_घोषित CONFIG_ARCH_OMAP3
अटल व्योम __init of_ti_hsotgusb_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node,
				   &clkhwops_omap3430es2_iclk_hsotgusb_रुको);
पूर्ण
CLK_OF_DECLARE(ti_hsotgusb_पूर्णांकerface_clk, "ti,omap3-hsotgusb-interface-clock",
	       of_ti_hsotgusb_पूर्णांकerface_clk_setup);

अटल व्योम __init of_ti_dss_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node,
				   &clkhwops_omap3430es2_iclk_dss_usbhost_रुको);
पूर्ण
CLK_OF_DECLARE(ti_dss_पूर्णांकerface_clk, "ti,omap3-dss-interface-clock",
	       of_ti_dss_पूर्णांकerface_clk_setup);

अटल व्योम __init of_ti_ssi_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node, &clkhwops_omap3430es2_iclk_ssi_रुको);
पूर्ण
CLK_OF_DECLARE(ti_ssi_पूर्णांकerface_clk, "ti,omap3-ssi-interface-clock",
	       of_ti_ssi_पूर्णांकerface_clk_setup);

अटल व्योम __init of_ti_am35xx_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node, &clkhwops_am35xx_ipss_रुको);
पूर्ण
CLK_OF_DECLARE(ti_am35xx_पूर्णांकerface_clk, "ti,am35xx-interface-clock",
	       of_ti_am35xx_पूर्णांकerface_clk_setup);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
अटल व्योम __init of_ti_omap2430_पूर्णांकerface_clk_setup(काष्ठा device_node *node)
अणु
	_of_ti_पूर्णांकerface_clk_setup(node, &clkhwops_omap2430_i2chs_रुको);
पूर्ण
CLK_OF_DECLARE(ti_omap2430_पूर्णांकerface_clk, "ti,omap2430-interface-clock",
	       of_ti_omap2430_पूर्णांकerface_clk_setup);
#पूर्ण_अगर
