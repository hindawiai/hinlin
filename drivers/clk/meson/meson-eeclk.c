<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "meson-eeclk.h"

पूर्णांक meson_eeclkc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_eeclkc_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *map;
	पूर्णांक ret, i;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	/* Get the hhi प्रणाली controller node */
	map = syscon_node_to_regmap(of_get_parent(dev->of_node));
	अगर (IS_ERR(map)) अणु
		dev_err(dev,
			"failed to get HHI regmap\n");
		वापस PTR_ERR(map);
	पूर्ण

	अगर (data->init_count)
		regmap_multi_reg_ग_लिखो(map, data->init_regs, data->init_count);

	/* Populate regmap क्रम the regmap backed घड़ीs */
	क्रम (i = 0; i < data->regmap_clk_num; i++)
		data->regmap_clks[i]->map = map;

	क्रम (i = 0; i < data->hw_onecell_data->num; i++) अणु
		/* array might be sparse */
		अगर (!data->hw_onecell_data->hws[i])
			जारी;

		ret = devm_clk_hw_रेजिस्टर(dev, data->hw_onecell_data->hws[i]);
		अगर (ret) अणु
			dev_err(dev, "Clock registration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   data->hw_onecell_data);
पूर्ण
EXPORT_SYMBOL_GPL(meson_eeclkc_probe);
MODULE_LICENSE("GPL v2");
