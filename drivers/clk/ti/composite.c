<शैली गुरु>
/*
 * TI composite घड़ी support
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
#समावेश <linux/list.h>

#समावेश "clock.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

अटल अचिन्हित दीर्घ ti_composite_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	वापस ti_clk_भागider_ops.recalc_rate(hw, parent_rate);
पूर्ण

अटल दीर्घ ti_composite_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *prate)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ti_composite_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops ti_composite_भागider_ops = अणु
	.recalc_rate	= &ti_composite_recalc_rate,
	.round_rate	= &ti_composite_round_rate,
	.set_rate	= &ti_composite_set_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_ops ti_composite_gate_ops = अणु
	.enable		= &omap2_dflt_clk_enable,
	.disable	= &omap2_dflt_clk_disable,
	.is_enabled	= &omap2_dflt_clk_is_enabled,
पूर्ण;

काष्ठा component_clk अणु
	पूर्णांक num_parents;
	स्थिर अक्षर **parent_names;
	काष्ठा device_node *node;
	पूर्णांक type;
	काष्ठा clk_hw *hw;
	काष्ठा list_head link;
पूर्ण;

अटल स्थिर अक्षर * स्थिर component_clk_types[] __initस्थिर = अणु
	"gate", "divider", "mux"
पूर्ण;

अटल LIST_HEAD(component_clks);

अटल काष्ठा device_node *_get_component_node(काष्ठा device_node *node, पूर्णांक i)
अणु
	पूर्णांक rc;
	काष्ठा of_phandle_args clkspec;

	rc = of_parse_phandle_with_args(node, "clocks", "#clock-cells", i,
					&clkspec);
	अगर (rc)
		वापस शून्य;

	वापस clkspec.np;
पूर्ण

अटल काष्ठा component_clk *_lookup_component(काष्ठा device_node *node)
अणु
	काष्ठा component_clk *comp;

	list_क्रम_each_entry(comp, &component_clks, link) अणु
		अगर (comp->node == node)
			वापस comp;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा clk_hw_omap_comp अणु
	काष्ठा clk_hw hw;
	काष्ठा device_node *comp_nodes[CLK_COMPONENT_TYPE_MAX];
	काष्ठा component_clk *comp_clks[CLK_COMPONENT_TYPE_MAX];
पूर्ण;

अटल अंतरभूत काष्ठा clk_hw *_get_hw(काष्ठा clk_hw_omap_comp *clk, पूर्णांक idx)
अणु
	अगर (!clk)
		वापस शून्य;

	अगर (!clk->comp_clks[idx])
		वापस शून्य;

	वापस clk->comp_clks[idx]->hw;
पूर्ण

#घोषणा to_clk_hw_comp(_hw) container_of(_hw, काष्ठा clk_hw_omap_comp, hw)

अटल व्योम __init _रेजिस्टर_composite(व्योम *user,
				       काष्ठा device_node *node)
अणु
	काष्ठा clk_hw *hw = user;
	काष्ठा clk *clk;
	काष्ठा clk_hw_omap_comp *cclk = to_clk_hw_comp(hw);
	काष्ठा component_clk *comp;
	पूर्णांक num_parents = 0;
	स्थिर अक्षर **parent_names = शून्य;
	पूर्णांक i;
	पूर्णांक ret;

	/* Check क्रम presence of each component घड़ी */
	क्रम (i = 0; i < CLK_COMPONENT_TYPE_MAX; i++) अणु
		अगर (!cclk->comp_nodes[i])
			जारी;

		comp = _lookup_component(cclk->comp_nodes[i]);
		अगर (!comp) अणु
			pr_debug("component %s not ready for %pOFn, retry\n",
				 cclk->comp_nodes[i]->name, node);
			अगर (!ti_clk_retry_init(node, hw,
					       _रेजिस्टर_composite))
				वापस;

			जाओ cleanup;
		पूर्ण
		अगर (cclk->comp_clks[comp->type] != शून्य) अणु
			pr_err("duplicate component types for %pOFn (%s)!\n",
			       node, component_clk_types[comp->type]);
			जाओ cleanup;
		पूर्ण

		cclk->comp_clks[comp->type] = comp;

		/* Mark this node as found */
		cclk->comp_nodes[i] = शून्य;
	पूर्ण

	/* All components exists, proceed with registration */
	क्रम (i = CLK_COMPONENT_TYPE_MAX - 1; i >= 0; i--) अणु
		comp = cclk->comp_clks[i];
		अगर (!comp)
			जारी;
		अगर (comp->num_parents) अणु
			num_parents = comp->num_parents;
			parent_names = comp->parent_names;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!num_parents) अणु
		pr_err("%s: no parents found for %pOFn!\n", __func__, node);
		जाओ cleanup;
	पूर्ण

	clk = clk_रेजिस्टर_composite(शून्य, node->name,
				     parent_names, num_parents,
				     _get_hw(cclk, CLK_COMPONENT_TYPE_MUX),
				     &ti_clk_mux_ops,
				     _get_hw(cclk, CLK_COMPONENT_TYPE_DIVIDER),
				     &ti_composite_भागider_ops,
				     _get_hw(cclk, CLK_COMPONENT_TYPE_GATE),
				     &ti_composite_gate_ops, 0);

	अगर (!IS_ERR(clk)) अणु
		ret = ti_clk_add_alias(शून्य, clk, node->name);
		अगर (ret) अणु
			clk_unरेजिस्टर(clk);
			जाओ cleanup;
		पूर्ण
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
	पूर्ण

cleanup:
	/* Free component घड़ी list entries */
	क्रम (i = 0; i < CLK_COMPONENT_TYPE_MAX; i++) अणु
		अगर (!cclk->comp_clks[i])
			जारी;
		list_del(&cclk->comp_clks[i]->link);
		kमुक्त(cclk->comp_clks[i]->parent_names);
		kमुक्त(cclk->comp_clks[i]);
	पूर्ण

	kमुक्त(cclk);
पूर्ण

अटल व्योम __init of_ti_composite_clk_setup(काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक num_clks;
	पूर्णांक i;
	काष्ठा clk_hw_omap_comp *cclk;

	/* Number of component घड़ीs to be put inside this घड़ी */
	num_clks = of_clk_get_parent_count(node);

	अगर (!num_clks) अणु
		pr_err("composite clk %pOFn must have component(s)\n", node);
		वापस;
	पूर्ण

	cclk = kzalloc(माप(*cclk), GFP_KERNEL);
	अगर (!cclk)
		वापस;

	/* Get device node poपूर्णांकers क्रम each component घड़ी */
	क्रम (i = 0; i < num_clks; i++)
		cclk->comp_nodes[i] = _get_component_node(node, i);

	_रेजिस्टर_composite(&cclk->hw, node);
पूर्ण
CLK_OF_DECLARE(ti_composite_घड़ी, "ti,composite-clock",
	       of_ti_composite_clk_setup);

/**
 * ti_clk_add_component - add a component घड़ी to the pool
 * @node: device node of the component घड़ी
 * @hw: hardware घड़ी definition क्रम the component घड़ी
 * @type: type of the component घड़ी
 *
 * Adds a component घड़ी to the list of available components, so that
 * it can be रेजिस्टरed by a composite घड़ी.
 */
पूर्णांक __init ti_clk_add_component(काष्ठा device_node *node, काष्ठा clk_hw *hw,
				पूर्णांक type)
अणु
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर **parent_names;
	काष्ठा component_clk *clk;

	num_parents = of_clk_get_parent_count(node);

	अगर (!num_parents) अणु
		pr_err("component-clock %pOFn must have parent(s)\n", node);
		वापस -EINVAL;
	पूर्ण

	parent_names = kzalloc((माप(अक्षर *) * num_parents), GFP_KERNEL);
	अगर (!parent_names)
		वापस -ENOMEM;

	of_clk_parent_fill(node, parent_names, num_parents);

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk) अणु
		kमुक्त(parent_names);
		वापस -ENOMEM;
	पूर्ण

	clk->num_parents = num_parents;
	clk->parent_names = parent_names;
	clk->hw = hw;
	clk->node = node;
	clk->type = type;
	list_add(&clk->link, &component_clks);

	वापस 0;
पूर्ण
