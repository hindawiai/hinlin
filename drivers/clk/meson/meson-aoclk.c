<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson-AXG Clock Controller Driver
 *
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * Copyright (c) 2018 Amlogic, inc.
 * Author: Qiufang Dai <qiufang.dai@amlogic.com>
 * Author: Yixun Lan <yixun.lan@amlogic.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>

#समावेश <linux/slab.h>
#समावेश "meson-aoclk.h"

अटल पूर्णांक meson_aoclk_करो_reset(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा meson_aoclk_reset_controller *rstc =
		container_of(rcdev, काष्ठा meson_aoclk_reset_controller, reset);

	वापस regmap_ग_लिखो(rstc->regmap, rstc->data->reset_reg,
			    BIT(rstc->data->reset[id]));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops meson_aoclk_reset_ops = अणु
	.reset = meson_aoclk_करो_reset,
पूर्ण;

पूर्णांक meson_aoclkc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा meson_aoclk_reset_controller *rstc;
	काष्ठा meson_aoclk_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret, clkid;

	data = (काष्ठा meson_aoclk_data *) of_device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	rstc = devm_kzalloc(dev, माप(*rstc), GFP_KERNEL);
	अगर (!rstc)
		वापस -ENOMEM;

	regmap = syscon_node_to_regmap(of_get_parent(dev->of_node));
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to get regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/* Reset Controller */
	rstc->data = data;
	rstc->regmap = regmap;
	rstc->reset.ops = &meson_aoclk_reset_ops;
	rstc->reset.nr_resets = data->num_reset;
	rstc->reset.of_node = dev->of_node;
	ret = devm_reset_controller_रेजिस्टर(dev, &rstc->reset);
	अगर (ret) अणु
		dev_err(dev, "failed to register reset controller\n");
		वापस ret;
	पूर्ण

	/* Populate regmap */
	क्रम (clkid = 0; clkid < data->num_clks; clkid++)
		data->clks[clkid]->map = regmap;

	/* Register all clks */
	क्रम (clkid = 0; clkid < data->hw_data->num; clkid++) अणु
		अगर (!data->hw_data->hws[clkid])
			जारी;

		ret = devm_clk_hw_रेजिस्टर(dev, data->hw_data->hws[clkid]);
		अगर (ret) अणु
			dev_err(dev, "Clock registration failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
		(व्योम *) data->hw_data);
पूर्ण
EXPORT_SYMBOL_GPL(meson_aoclkc_probe);
MODULE_LICENSE("GPL v2");
