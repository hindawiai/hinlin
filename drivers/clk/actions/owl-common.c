<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// OWL common घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "owl-common.h"

अटल स्थिर काष्ठा regmap_config owl_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x00cc,
	.fast_io	= true,
पूर्ण;

अटल व्योम owl_clk_set_regmap(स्थिर काष्ठा owl_clk_desc *desc,
			 काष्ठा regmap *regmap)
अणु
	पूर्णांक i;
	काष्ठा owl_clk_common *clks;

	क्रम (i = 0; i < desc->num_clks; i++) अणु
		clks = desc->clks[i];
		अगर (!clks)
			जारी;

		clks->regmap = regmap;
	पूर्ण
पूर्ण

पूर्णांक owl_clk_regmap_init(काष्ठा platक्रमm_device *pdev,
			काष्ठा owl_clk_desc *desc)
अणु
	व्योम __iomem *base;
	काष्ठा regmap *regmap;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base, &owl_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		pr_err("failed to init regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	owl_clk_set_regmap(desc, regmap);
	desc->regmap = regmap;

	वापस 0;
पूर्ण

पूर्णांक owl_clk_probe(काष्ठा device *dev, काष्ठा clk_hw_onecell_data *hw_clks)
अणु
	पूर्णांक i, ret;
	काष्ठा clk_hw *hw;

	क्रम (i = 0; i < hw_clks->num; i++) अणु
		स्थिर अक्षर *name;

		hw = hw_clks->hws[i];
		अगर (IS_ERR_OR_शून्य(hw))
			जारी;

		name = hw->init->name;
		ret = devm_clk_hw_रेजिस्टर(dev, hw);
		अगर (ret) अणु
			dev_err(dev, "Couldn't register clock %d - %s\n",
				i, name);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, hw_clks);
	अगर (ret)
		dev_err(dev, "Failed to add clock provider\n");

	वापस ret;
पूर्ण
