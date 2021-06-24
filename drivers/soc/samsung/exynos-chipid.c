<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *	      http://www.samsung.com/
 * Copyright (c) 2020 Krzysztof Kozlowski <krzk@kernel.org>
 *
 * Exynos - CHIP ID support
 * Author: Pankaj Dubey <pankaj.dubey@samsung.com>
 * Author: Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>
 * Author: Krzysztof Kozlowski <krzk@kernel.org>
 *
 * Samsung Exynos SoC Adaptive Supply Voltage and Chip ID support
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/samsung/exynos-chipid.h>
#समावेश <linux/sys_soc.h>

#समावेश "exynos-asv.h"

अटल स्थिर काष्ठा exynos_soc_id अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
पूर्ण soc_ids[] = अणु
	/* List ordered by SoC name */
	अणु "EXYNOS3250", 0xE3472000 पूर्ण,
	अणु "EXYNOS4210", 0x43200000 पूर्ण,	/* EVT0 revision */
	अणु "EXYNOS4210", 0x43210000 पूर्ण,
	अणु "EXYNOS4212", 0x43220000 पूर्ण,
	अणु "EXYNOS4412", 0xE4412000 पूर्ण,
	अणु "EXYNOS5250", 0x43520000 पूर्ण,
	अणु "EXYNOS5260", 0xE5260000 पूर्ण,
	अणु "EXYNOS5410", 0xE5410000 पूर्ण,
	अणु "EXYNOS5420", 0xE5420000 पूर्ण,
	अणु "EXYNOS5433", 0xE5433000 पूर्ण,
	अणु "EXYNOS5440", 0xE5440000 पूर्ण,
	अणु "EXYNOS5800", 0xE5422000 पूर्ण,
	अणु "EXYNOS7420", 0xE7420000 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *product_id_to_soc_id(अचिन्हित पूर्णांक product_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(soc_ids); i++)
		अगर ((product_id & EXYNOS_MASK) == soc_ids[i].id)
			वापस soc_ids[i].name;
	वापस शून्य;
पूर्ण

अटल पूर्णांक exynos_chipid_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;
	काष्ठा device_node *root;
	काष्ठा regmap *regmap;
	u32 product_id;
	u32 revision;
	पूर्णांक ret;

	regmap = device_node_to_regmap(pdev->dev.of_node);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = regmap_पढ़ो(regmap, EXYNOS_CHIPID_REG_PRO_ID, &product_id);
	अगर (ret < 0)
		वापस ret;

	revision = product_id & EXYNOS_REV_MASK;

	soc_dev_attr = devm_kzalloc(&pdev->dev, माप(*soc_dev_attr),
				    GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->family = "Samsung Exynos";

	root = of_find_node_by_path("/");
	of_property_पढ़ो_string(root, "model", &soc_dev_attr->machine);
	of_node_put(root);

	soc_dev_attr->revision = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
						"%x", revision);
	soc_dev_attr->soc_id = product_id_to_soc_id(product_id);
	अगर (!soc_dev_attr->soc_id) अणु
		pr_err("Unknown SoC\n");
		वापस -ENODEV;
	पूर्ण

	/* please note that the actual registration will be deferred */
	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev))
		वापस PTR_ERR(soc_dev);

	ret = exynos_asv_init(&pdev->dev, regmap);
	अगर (ret)
		जाओ err;

	platक्रमm_set_drvdata(pdev, soc_dev);

	dev_info(soc_device_to_device(soc_dev),
		 "Exynos: CPU[%s] PRO_ID[0x%x] REV[0x%x] Detected\n",
		 soc_dev_attr->soc_id, product_id, revision);

	वापस 0;

err:
	soc_device_unरेजिस्टर(soc_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_chipid_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा soc_device *soc_dev = platक्रमm_get_drvdata(pdev);

	soc_device_unरेजिस्टर(soc_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos_chipid_of_device_ids[] = अणु
	अणु .compatible = "samsung,exynos4210-chipid" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos_chipid_driver = अणु
	.driver = अणु
		.name = "exynos-chipid",
		.of_match_table = exynos_chipid_of_device_ids,
	पूर्ण,
	.probe	= exynos_chipid_probe,
	.हटाओ	= exynos_chipid_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(exynos_chipid_driver);
