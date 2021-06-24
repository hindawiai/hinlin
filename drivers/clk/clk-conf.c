<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/prपूर्णांकk.h>

अटल पूर्णांक __set_clk_parents(काष्ठा device_node *node, bool clk_supplier)
अणु
	काष्ठा of_phandle_args clkspec;
	पूर्णांक index, rc, num_parents;
	काष्ठा clk *clk, *pclk;

	num_parents = of_count_phandle_with_args(node, "assigned-clock-parents",
						 "#clock-cells");
	अगर (num_parents == -EINVAL)
		pr_err("clk: invalid value of clock-parents property at %pOF\n",
		       node);

	क्रम (index = 0; index < num_parents; index++) अणु
		rc = of_parse_phandle_with_args(node, "assigned-clock-parents",
					"#clock-cells",	index, &clkspec);
		अगर (rc < 0) अणु
			/* skip empty (null) phandles */
			अगर (rc == -ENOENT)
				जारी;
			अन्यथा
				वापस rc;
		पूर्ण
		अगर (clkspec.np == node && !clk_supplier)
			वापस 0;
		pclk = of_clk_get_from_provider(&clkspec);
		अगर (IS_ERR(pclk)) अणु
			अगर (PTR_ERR(pclk) != -EPROBE_DEFER)
				pr_warn("clk: couldn't get parent clock %d for %pOF\n",
					index, node);
			वापस PTR_ERR(pclk);
		पूर्ण

		rc = of_parse_phandle_with_args(node, "assigned-clocks",
					"#clock-cells", index, &clkspec);
		अगर (rc < 0)
			जाओ err;
		अगर (clkspec.np == node && !clk_supplier) अणु
			rc = 0;
			जाओ err;
		पूर्ण
		clk = of_clk_get_from_provider(&clkspec);
		अगर (IS_ERR(clk)) अणु
			अगर (PTR_ERR(clk) != -EPROBE_DEFER)
				pr_warn("clk: couldn't get assigned clock %d for %pOF\n",
					index, node);
			rc = PTR_ERR(clk);
			जाओ err;
		पूर्ण

		rc = clk_set_parent(clk, pclk);
		अगर (rc < 0)
			pr_err("clk: failed to reparent %s to %s: %d\n",
			       __clk_get_name(clk), __clk_get_name(pclk), rc);
		clk_put(clk);
		clk_put(pclk);
	पूर्ण
	वापस 0;
err:
	clk_put(pclk);
	वापस rc;
पूर्ण

अटल पूर्णांक __set_clk_rates(काष्ठा device_node *node, bool clk_supplier)
अणु
	काष्ठा of_phandle_args clkspec;
	काष्ठा property	*prop;
	स्थिर __be32 *cur;
	पूर्णांक rc, index = 0;
	काष्ठा clk *clk;
	u32 rate;

	of_property_क्रम_each_u32(node, "assigned-clock-rates", prop, cur, rate) अणु
		अगर (rate) अणु
			rc = of_parse_phandle_with_args(node, "assigned-clocks",
					"#clock-cells",	index, &clkspec);
			अगर (rc < 0) अणु
				/* skip empty (null) phandles */
				अगर (rc == -ENOENT)
					जारी;
				अन्यथा
					वापस rc;
			पूर्ण
			अगर (clkspec.np == node && !clk_supplier)
				वापस 0;

			clk = of_clk_get_from_provider(&clkspec);
			अगर (IS_ERR(clk)) अणु
				अगर (PTR_ERR(clk) != -EPROBE_DEFER)
					pr_warn("clk: couldn't get clock %d for %pOF\n",
						index, node);
				वापस PTR_ERR(clk);
			पूर्ण

			rc = clk_set_rate(clk, rate);
			अगर (rc < 0)
				pr_err("clk: couldn't set %s clk rate to %u (%d), current rate: %lu\n",
				       __clk_get_name(clk), rate, rc,
				       clk_get_rate(clk));
			clk_put(clk);
		पूर्ण
		index++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * of_clk_set_शेषs() - parse and set asचिन्हित घड़ीs configuration
 * @node: device node to apply घड़ी settings क्रम
 * @clk_supplier: true अगर घड़ीs supplied by @node should also be considered
 *
 * This function parses 'assigned-{clocks/clock-parents/clock-rates}' properties
 * and sets any specअगरied घड़ी parents and rates. The @clk_supplier argument
 * should be set to true अगर @node may be also a घड़ी supplier of any घड़ी
 * listed in its 'assigned-clocks' or 'assigned-clock-parents' properties.
 * If @clk_supplier is false the function निकासs वापसing 0 as soon as it
 * determines the @node is also a supplier of any of the घड़ीs.
 */
पूर्णांक of_clk_set_शेषs(काष्ठा device_node *node, bool clk_supplier)
अणु
	पूर्णांक rc;

	अगर (!node)
		वापस 0;

	rc = __set_clk_parents(node, clk_supplier);
	अगर (rc < 0)
		वापस rc;

	वापस __set_clk_rates(node, clk_supplier);
पूर्ण
EXPORT_SYMBOL_GPL(of_clk_set_शेषs);
