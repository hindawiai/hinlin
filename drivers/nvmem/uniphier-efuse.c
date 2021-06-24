<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * UniPhier eFuse driver
 *
 * Copyright (C) 2017 Socionext Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा uniphier_efuse_priv अणु
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक uniphier_reg_पढ़ो(व्योम *context,
			     अचिन्हित पूर्णांक reg, व्योम *_val, माप_प्रकार bytes)
अणु
	काष्ठा uniphier_efuse_priv *priv = context;
	u8 *val = _val;
	पूर्णांक offs;

	क्रम (offs = 0; offs < bytes; offs += माप(u8))
		*val++ = पढ़ोb(priv->base + reg + offs);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config econfig = अणुपूर्ण;
	काष्ठा uniphier_efuse_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	econfig.stride = 1;
	econfig.word_size = 1;
	econfig.पढ़ो_only = true;
	econfig.reg_पढ़ो = uniphier_reg_पढ़ो;
	econfig.size = resource_size(res);
	econfig.priv = priv;
	econfig.dev = dev;
	nvmem = devm_nvmem_रेजिस्टर(dev, &econfig);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_efuse_of_match[] = अणु
	अणु .compatible = "socionext,uniphier-efuse",पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_efuse_of_match);

अटल काष्ठा platक्रमm_driver uniphier_efuse_driver = अणु
	.probe = uniphier_efuse_probe,
	.driver = अणु
		.name = "uniphier-efuse",
		.of_match_table = uniphier_efuse_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_efuse_driver);

MODULE_AUTHOR("Keiji Hayashibara <hayashibara.keiji@socionext.com>");
MODULE_DESCRIPTION("UniPhier eFuse driver");
MODULE_LICENSE("GPL v2");
