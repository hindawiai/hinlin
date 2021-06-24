<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 * Author: Andrew-CT Chen <andrew-ct.chen@mediatek.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पन.स>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा mtk_efuse_priv अणु
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक mtk_reg_पढ़ो(व्योम *context,
			अचिन्हित पूर्णांक reg, व्योम *_val, माप_प्रकार bytes)
अणु
	काष्ठा mtk_efuse_priv *priv = context;
	u32 *val = _val;
	पूर्णांक i = 0, words = bytes / 4;

	जबतक (words--)
		*val++ = पढ़ोl(priv->base + reg + (i++ * 4));

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config econfig = अणुपूर्ण;
	काष्ठा mtk_efuse_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	econfig.stride = 4;
	econfig.word_size = 4;
	econfig.reg_पढ़ो = mtk_reg_पढ़ो;
	econfig.size = resource_size(res);
	econfig.priv = priv;
	econfig.dev = dev;
	nvmem = devm_nvmem_रेजिस्टर(dev, &econfig);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_efuse_of_match[] = अणु
	अणु .compatible = "mediatek,mt8173-efuse",पूर्ण,
	अणु .compatible = "mediatek,efuse",पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_efuse_of_match);

अटल काष्ठा platक्रमm_driver mtk_efuse_driver = अणु
	.probe = mtk_efuse_probe,
	.driver = अणु
		.name = "mediatek,efuse",
		.of_match_table = mtk_efuse_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mtk_efuse_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&mtk_efuse_driver);
	अगर (ret) अणु
		pr_err("Failed to register efuse driver\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास mtk_efuse_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&mtk_efuse_driver);
पूर्ण

subsys_initcall(mtk_efuse_init);
module_निकास(mtk_efuse_निकास);

MODULE_AUTHOR("Andrew-CT Chen <andrew-ct.chen@mediatek.com>");
MODULE_DESCRIPTION("Mediatek EFUSE driver");
MODULE_LICENSE("GPL v2");
