<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Spपढ़ोtrum घड़ी infraकाष्ठाure
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>

#समावेश "common.h"

अटल स्थिर काष्ठा regmap_config sprdclk_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xffff,
	.fast_io	= true,
पूर्ण;

अटल व्योम sprd_clk_set_regmap(स्थिर काष्ठा sprd_clk_desc *desc,
			 काष्ठा regmap *regmap)
अणु
	पूर्णांक i;
	काष्ठा sprd_clk_common *cclk;

	क्रम (i = 0; i < desc->num_clk_clks; i++) अणु
		cclk = desc->clk_clks[i];
		अगर (!cclk)
			जारी;

		cclk->regmap = regmap;
	पूर्ण
पूर्ण

पूर्णांक sprd_clk_regmap_init(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा sprd_clk_desc *desc)
अणु
	व्योम __iomem *base;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा regmap *regmap;

	अगर (of_find_property(node, "sprd,syscon", शून्य)) अणु
		regmap = syscon_regmap_lookup_by_phandle(node, "sprd,syscon");
		अगर (IS_ERR(regmap)) अणु
			pr_err("%s: failed to get syscon regmap\n", __func__);
			वापस PTR_ERR(regmap);
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(of_get_parent(dev->of_node),
			   "syscon")) अणु
		regmap = device_node_to_regmap(of_get_parent(dev->of_node));
		अगर (IS_ERR(regmap)) अणु
			dev_err(dev, "failed to get regmap from its parent.\n");
			वापस PTR_ERR(regmap);
		पूर्ण
	पूर्ण अन्यथा अणु
		base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(base))
			वापस PTR_ERR(base);

		regmap = devm_regmap_init_mmio(&pdev->dev, base,
					       &sprdclk_regmap_config);
		अगर (IS_ERR(regmap)) अणु
			pr_err("failed to init regmap\n");
			वापस PTR_ERR(regmap);
		पूर्ण
	पूर्ण

	sprd_clk_set_regmap(desc, regmap);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_clk_regmap_init);

पूर्णांक sprd_clk_probe(काष्ठा device *dev, काष्ठा clk_hw_onecell_data *clkhw)
अणु
	पूर्णांक i, ret;
	काष्ठा clk_hw *hw;

	क्रम (i = 0; i < clkhw->num; i++) अणु
		स्थिर अक्षर *name;

		hw = clkhw->hws[i];
		अगर (!hw)
			जारी;

		name = hw->init->name;
		ret = devm_clk_hw_रेजिस्टर(dev, hw);
		अगर (ret) अणु
			dev_err(dev, "Couldn't register clock %d - %s\n",
				i, name);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, clkhw);
	अगर (ret)
		dev_err(dev, "Failed to add clock provider\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sprd_clk_probe);

MODULE_LICENSE("GPL v2");
