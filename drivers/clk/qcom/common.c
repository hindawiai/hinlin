<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/of.h>

#समावेश "common.h"
#समावेश "clk-rcg.h"
#समावेश "clk-regmap.h"
#समावेश "reset.h"
#समावेश "gdsc.h"

काष्ठा qcom_cc अणु
	काष्ठा qcom_reset_controller reset;
	काष्ठा clk_regmap **rclks;
	माप_प्रकार num_rclks;
पूर्ण;

स्थिर
काष्ठा freq_tbl *qcom_find_freq(स्थिर काष्ठा freq_tbl *f, अचिन्हित दीर्घ rate)
अणु
	अगर (!f)
		वापस शून्य;

	अगर (!f->freq)
		वापस f;

	क्रम (; f->freq; f++)
		अगर (rate <= f->freq)
			वापस f;

	/* Default to our fastest rate */
	वापस f - 1;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_find_freq);

स्थिर काष्ठा freq_tbl *qcom_find_freq_न्यूनमान(स्थिर काष्ठा freq_tbl *f,
					    अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा freq_tbl *best = शून्य;

	क्रम ( ; f->freq; f++) अणु
		अगर (rate >= f->freq)
			best = f;
		अन्यथा
			अवरोध;
	पूर्ण

	वापस best;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_find_freq_न्यूनमान);

पूर्णांक qcom_find_src_index(काष्ठा clk_hw *hw, स्थिर काष्ठा parent_map *map, u8 src)
अणु
	पूर्णांक i, num_parents = clk_hw_get_num_parents(hw);

	क्रम (i = 0; i < num_parents; i++)
		अगर (src == map[i].src)
			वापस i;

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_find_src_index);

काष्ठा regmap *
qcom_cc_map(काष्ठा platक्रमm_device *pdev, स्थिर काष्ठा qcom_cc_desc *desc)
अणु
	व्योम __iomem *base;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस ERR_CAST(base);

	वापस devm_regmap_init_mmio(dev, base, desc->config);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_map);

व्योम
qcom_pll_set_fsm_mode(काष्ठा regmap *map, u32 reg, u8 bias_count, u8 lock_count)
अणु
	u32 val;
	u32 mask;

	/* De-निश्चित reset to FSM */
	regmap_update_bits(map, reg, PLL_VOTE_FSM_RESET, 0);

	/* Program bias count and lock count */
	val = bias_count << PLL_BIAS_COUNT_SHIFT |
		lock_count << PLL_LOCK_COUNT_SHIFT;
	mask = PLL_BIAS_COUNT_MASK << PLL_BIAS_COUNT_SHIFT;
	mask |= PLL_LOCK_COUNT_MASK << PLL_LOCK_COUNT_SHIFT;
	regmap_update_bits(map, reg, mask, val);

	/* Enable PLL FSM voting */
	regmap_update_bits(map, reg, PLL_VOTE_FSM_ENA, PLL_VOTE_FSM_ENA);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_pll_set_fsm_mode);

अटल व्योम qcom_cc_gdsc_unरेजिस्टर(व्योम *data)
अणु
	gdsc_unरेजिस्टर(data);
पूर्ण

/*
 * Backwards compatibility with old DTs. Register a pass-through factor 1/1
 * घड़ी to translate 'path' clk into 'name' clk and register the 'path'
 * clk as a fixed rate घड़ी अगर it isn't present.
 */
अटल पूर्णांक _qcom_cc_रेजिस्टर_board_clk(काष्ठा device *dev, स्थिर अक्षर *path,
				       स्थिर अक्षर *name, अचिन्हित दीर्घ rate,
				       bool add_factor)
अणु
	काष्ठा device_node *node = शून्य;
	काष्ठा device_node *घड़ीs_node;
	काष्ठा clk_fixed_factor *factor;
	काष्ठा clk_fixed_rate *fixed;
	काष्ठा clk_init_data init_data = अणु पूर्ण;
	पूर्णांक ret;

	घड़ीs_node = of_find_node_by_path("/clocks");
	अगर (घड़ीs_node) अणु
		node = of_get_child_by_name(घड़ीs_node, path);
		of_node_put(घड़ीs_node);
	पूर्ण

	अगर (!node) अणु
		fixed = devm_kzalloc(dev, माप(*fixed), GFP_KERNEL);
		अगर (!fixed)
			वापस -EINVAL;

		fixed->fixed_rate = rate;
		fixed->hw.init = &init_data;

		init_data.name = path;
		init_data.ops = &clk_fixed_rate_ops;

		ret = devm_clk_hw_रेजिस्टर(dev, &fixed->hw);
		अगर (ret)
			वापस ret;
	पूर्ण
	of_node_put(node);

	अगर (add_factor) अणु
		factor = devm_kzalloc(dev, माप(*factor), GFP_KERNEL);
		अगर (!factor)
			वापस -EINVAL;

		factor->mult = factor->भाग = 1;
		factor->hw.init = &init_data;

		init_data.name = name;
		init_data.parent_names = &path;
		init_data.num_parents = 1;
		init_data.flags = 0;
		init_data.ops = &clk_fixed_factor_ops;

		ret = devm_clk_hw_रेजिस्टर(dev, &factor->hw);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qcom_cc_रेजिस्टर_board_clk(काष्ठा device *dev, स्थिर अक्षर *path,
			       स्थिर अक्षर *name, अचिन्हित दीर्घ rate)
अणु
	bool add_factor = true;

	/*
	 * TODO: The RPM घड़ी driver currently करोes not support the xo घड़ी.
	 * When xo is added to the RPM घड़ी driver, we should change this
	 * function to skip registration of xo factor घड़ीs.
	 */

	वापस _qcom_cc_रेजिस्टर_board_clk(dev, path, name, rate, add_factor);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_रेजिस्टर_board_clk);

पूर्णांक qcom_cc_रेजिस्टर_sleep_clk(काष्ठा device *dev)
अणु
	वापस _qcom_cc_रेजिस्टर_board_clk(dev, "sleep_clk", "sleep_clk_src",
					   32768, true);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_रेजिस्टर_sleep_clk);

/* Drop 'protected-clocks' from the list of घड़ीs to रेजिस्टर */
अटल व्योम qcom_cc_drop_रक्षित(काष्ठा device *dev, काष्ठा qcom_cc *cc)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	u32 i;

	of_property_क्रम_each_u32(np, "protected-clocks", prop, p, i) अणु
		अगर (i >= cc->num_rclks)
			जारी;

		cc->rclks[i] = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा clk_hw *qcom_cc_clk_hw_get(काष्ठा of_phandle_args *clkspec,
					 व्योम *data)
अणु
	काष्ठा qcom_cc *cc = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= cc->num_rclks) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस cc->rclks[idx] ? &cc->rclks[idx]->hw : शून्य;
पूर्ण

पूर्णांक qcom_cc_really_probe(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा qcom_cc_desc *desc, काष्ठा regmap *regmap)
अणु
	पूर्णांक i, ret;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_reset_controller *reset;
	काष्ठा qcom_cc *cc;
	काष्ठा gdsc_desc *scd;
	माप_प्रकार num_clks = desc->num_clks;
	काष्ठा clk_regmap **rclks = desc->clks;
	माप_प्रकार num_clk_hws = desc->num_clk_hws;
	काष्ठा clk_hw **clk_hws = desc->clk_hws;

	cc = devm_kzalloc(dev, माप(*cc), GFP_KERNEL);
	अगर (!cc)
		वापस -ENOMEM;

	reset = &cc->reset;
	reset->rcdev.of_node = dev->of_node;
	reset->rcdev.ops = &qcom_reset_ops;
	reset->rcdev.owner = dev->driver->owner;
	reset->rcdev.nr_resets = desc->num_resets;
	reset->regmap = regmap;
	reset->reset_map = desc->resets;

	ret = devm_reset_controller_रेजिस्टर(dev, &reset->rcdev);
	अगर (ret)
		वापस ret;

	अगर (desc->gdscs && desc->num_gdscs) अणु
		scd = devm_kzalloc(dev, माप(*scd), GFP_KERNEL);
		अगर (!scd)
			वापस -ENOMEM;
		scd->dev = dev;
		scd->scs = desc->gdscs;
		scd->num = desc->num_gdscs;
		ret = gdsc_रेजिस्टर(scd, &reset->rcdev, regmap);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, qcom_cc_gdsc_unरेजिस्टर,
					       scd);
		अगर (ret)
			वापस ret;
	पूर्ण

	cc->rclks = rclks;
	cc->num_rclks = num_clks;

	qcom_cc_drop_रक्षित(dev, cc);

	क्रम (i = 0; i < num_clk_hws; i++) अणु
		ret = devm_clk_hw_रेजिस्टर(dev, clk_hws[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < num_clks; i++) अणु
		अगर (!rclks[i])
			जारी;

		ret = devm_clk_रेजिस्टर_regmap(dev, rclks[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, qcom_cc_clk_hw_get, cc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_really_probe);

पूर्णांक qcom_cc_probe(काष्ठा platक्रमm_device *pdev, स्थिर काष्ठा qcom_cc_desc *desc)
अणु
	काष्ठा regmap *regmap;

	regmap = qcom_cc_map(pdev, desc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस qcom_cc_really_probe(pdev, desc, regmap);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_probe);

पूर्णांक qcom_cc_probe_by_index(काष्ठा platक्रमm_device *pdev, पूर्णांक index,
			   स्थिर काष्ठा qcom_cc_desc *desc)
अणु
	काष्ठा regmap *regmap;
	काष्ठा resource *res;
	व्योम __iomem *base;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस -ENOMEM;

	regmap = devm_regmap_init_mmio(&pdev->dev, base, desc->config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस qcom_cc_really_probe(pdev, desc, regmap);
पूर्ण
EXPORT_SYMBOL_GPL(qcom_cc_probe_by_index);

MODULE_LICENSE("GPL v2");
