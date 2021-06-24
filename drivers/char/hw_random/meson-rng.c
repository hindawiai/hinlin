<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2016 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2014 Amlogic, Inc.
 */
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>

#घोषणा RNG_DATA 0x00

काष्ठा meson_rng_data अणु
	व्योम __iomem *base;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा hwrng rng;
	काष्ठा clk *core_clk;
पूर्ण;

अटल पूर्णांक meson_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा meson_rng_data *data =
			container_of(rng, काष्ठा meson_rng_data, rng);

	*(u32 *)buf = पढ़ोl_relaxed(data->base + RNG_DATA);

	वापस माप(u32);
पूर्ण

अटल व्योम meson_rng_clk_disable(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक meson_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_rng_data *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->pdev = pdev;

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->core_clk = devm_clk_get(dev, "core");
	अगर (IS_ERR(data->core_clk))
		data->core_clk = शून्य;

	अगर (data->core_clk) अणु
		ret = clk_prepare_enable(data->core_clk);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, meson_rng_clk_disable,
					       data->core_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	data->rng.name = pdev->name;
	data->rng.पढ़ो = meson_rng_पढ़ो;

	platक्रमm_set_drvdata(pdev, data);

	वापस devm_hwrng_रेजिस्टर(dev, &data->rng);
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_rng_of_match[] = अणु
	अणु .compatible = "amlogic,meson-rng", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_rng_of_match);

अटल काष्ठा platक्रमm_driver meson_rng_driver = अणु
	.probe	= meson_rng_probe,
	.driver	= अणु
		.name = "meson-rng",
		.of_match_table = meson_rng_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_rng_driver);

MODULE_DESCRIPTION("Meson H/W Random Number Generator driver");
MODULE_AUTHOR("Lawrence Mok <lawrence.mok@amlogic.com>");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("Dual BSD/GPL");
