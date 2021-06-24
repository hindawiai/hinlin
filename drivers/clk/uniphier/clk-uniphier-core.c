<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "clk-uniphier.h"

अटल काष्ठा clk_hw *uniphier_clk_रेजिस्टर(काष्ठा device *dev,
					    काष्ठा regmap *regmap,
					स्थिर काष्ठा uniphier_clk_data *data)
अणु
	चयन (data->type) अणु
	हाल UNIPHIER_CLK_TYPE_CPUGEAR:
		वापस uniphier_clk_रेजिस्टर_cpugear(dev, regmap, data->name,
						     &data->data.cpugear);
	हाल UNIPHIER_CLK_TYPE_FIXED_FACTOR:
		वापस uniphier_clk_रेजिस्टर_fixed_factor(dev, data->name,
							  &data->data.factor);
	हाल UNIPHIER_CLK_TYPE_FIXED_RATE:
		वापस uniphier_clk_रेजिस्टर_fixed_rate(dev, data->name,
							&data->data.rate);
	हाल UNIPHIER_CLK_TYPE_GATE:
		वापस uniphier_clk_रेजिस्टर_gate(dev, regmap, data->name,
						  &data->data.gate);
	हाल UNIPHIER_CLK_TYPE_MUX:
		वापस uniphier_clk_रेजिस्टर_mux(dev, regmap, data->name,
						 &data->data.mux);
	शेष:
		dev_err(dev, "unsupported clock type\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक uniphier_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk_hw_onecell_data *hw_data;
	स्थिर काष्ठा uniphier_clk_data *p, *data;
	काष्ठा regmap *regmap;
	काष्ठा device_node *parent;
	पूर्णांक clk_num = 0;

	data = of_device_get_match_data(dev);
	अगर (WARN_ON(!data))
		वापस -EINVAL;

	parent = of_get_parent(dev->of_node); /* parent should be syscon node */
	regmap = syscon_node_to_regmap(parent);
	of_node_put(parent);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to get regmap (error %ld)\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	क्रम (p = data; p->name; p++)
		clk_num = max(clk_num, p->idx + 1);

	hw_data = devm_kzalloc(dev, काष्ठा_size(hw_data, hws, clk_num),
			GFP_KERNEL);
	अगर (!hw_data)
		वापस -ENOMEM;

	hw_data->num = clk_num;

	/* aव्योम वापसing शून्य क्रम unused idx */
	जबतक (--clk_num >= 0)
		hw_data->hws[clk_num] = ERR_PTR(-EINVAL);

	क्रम (p = data; p->name; p++) अणु
		काष्ठा clk_hw *hw;

		dev_dbg(dev, "register %s (index=%d)\n", p->name, p->idx);
		hw = uniphier_clk_रेजिस्टर(dev, regmap, p);
		अगर (WARN(IS_ERR(hw), "failed to register %s", p->name))
			जारी;

		अगर (p->idx >= 0)
			hw_data->hws[p->idx] = hw;
	पूर्ण

	वापस of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
				      hw_data);
पूर्ण

अटल पूर्णांक uniphier_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_clk_match[] = अणु
	/* System घड़ी */
	अणु
		.compatible = "socionext,uniphier-ld4-clock",
		.data = uniphier_ld4_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-clock",
		.data = uniphier_pro4_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sld8-clock",
		.data = uniphier_sld8_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-clock",
		.data = uniphier_pro5_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-clock",
		.data = uniphier_pxs2_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-clock",
		.data = uniphier_ld11_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-clock",
		.data = uniphier_ld20_sys_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-clock",
		.data = uniphier_pxs3_sys_clk_data,
	पूर्ण,
	/* Media I/O घड़ी, SD घड़ी */
	अणु
		.compatible = "socionext,uniphier-ld4-mio-clock",
		.data = uniphier_ld4_mio_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-mio-clock",
		.data = uniphier_ld4_mio_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sld8-mio-clock",
		.data = uniphier_ld4_mio_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-sd-clock",
		.data = uniphier_pro5_sd_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-sd-clock",
		.data = uniphier_pro5_sd_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-mio-clock",
		.data = uniphier_ld4_mio_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-sd-clock",
		.data = uniphier_pro5_sd_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-sd-clock",
		.data = uniphier_pro5_sd_clk_data,
	पूर्ण,
	/* Peripheral घड़ी */
	अणु
		.compatible = "socionext,uniphier-ld4-peri-clock",
		.data = uniphier_ld4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro4-peri-clock",
		.data = uniphier_pro4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-sld8-peri-clock",
		.data = uniphier_ld4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pro5-peri-clock",
		.data = uniphier_pro4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs2-peri-clock",
		.data = uniphier_pro4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld11-peri-clock",
		.data = uniphier_pro4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-ld20-peri-clock",
		.data = uniphier_pro4_peri_clk_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-pxs3-peri-clock",
		.data = uniphier_pro4_peri_clk_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver uniphier_clk_driver = अणु
	.probe = uniphier_clk_probe,
	.हटाओ = uniphier_clk_हटाओ,
	.driver = अणु
		.name = "uniphier-clk",
		.of_match_table = uniphier_clk_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(uniphier_clk_driver);
