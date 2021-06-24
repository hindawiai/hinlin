<शैली गुरु>
/*
 * TI Fixed Factor Clock
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
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

/**
 * of_ti_fixed_factor_clk_setup - Setup function क्रम TI fixed factor घड़ी
 * @node: device node क्रम this घड़ी
 *
 * Sets up a simple fixed factor घड़ी based on device tree info.
 */
अटल व्योम __init of_ti_fixed_factor_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	u32 भाग, mult;
	u32 flags = 0;

	अगर (of_property_पढ़ो_u32(node, "ti,clock-div", &भाग)) अणु
		pr_err("%pOFn must have a clock-div property\n", node);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "ti,clock-mult", &mult)) अणु
		pr_err("%pOFn must have a clock-mult property\n", node);
		वापस;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "ti,set-rate-parent"))
		flags |= CLK_SET_RATE_PARENT;

	parent_name = of_clk_get_parent_name(node, 0);

	clk = clk_रेजिस्टर_fixed_factor(शून्य, clk_name, parent_name, flags,
					mult, भाग);

	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		of_ti_clk_स्वतःidle_setup(node);
		ti_clk_add_alias(शून्य, clk, clk_name);
	पूर्ण
पूर्ण
CLK_OF_DECLARE(ti_fixed_factor_clk, "ti,fixed-factor-clock",
	       of_ti_fixed_factor_clk_setup);
