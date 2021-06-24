<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sfr.c - driver क्रम special function रेजिस्टरs
 *
 * Copyright (C) 2019 Bootlin.
 *
 */
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा SFR_SN0		0x4c
#घोषणा SFR_SN_SIZE	8

काष्ठा aपंचांगel_sfr_priv अणु
	काष्ठा regmap			*regmap;
पूर्ण;

अटल पूर्णांक aपंचांगel_sfr_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			  व्योम *buf, माप_प्रकार bytes)
अणु
	काष्ठा aपंचांगel_sfr_priv *priv = context;

	वापस regmap_bulk_पढ़ो(priv->regmap, SFR_SN0 + offset,
				buf, bytes / 4);
पूर्ण

अटल काष्ठा nvmem_config aपंचांगel_sfr_nvmem_config = अणु
	.name = "atmel-sfr",
	.पढ़ो_only = true,
	.word_size = 4,
	.stride = 4,
	.size = SFR_SN_SIZE,
	.reg_पढ़ो = aपंचांगel_sfr_पढ़ो,
पूर्ण;

अटल पूर्णांक aपंचांगel_sfr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा nvmem_device *nvmem;
	काष्ठा aपंचांगel_sfr_priv *priv;
	u8 sn[SFR_SN_SIZE];
	पूर्णांक ret;

	priv = devm_kदो_स्मृति(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "cannot get parent's regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	aपंचांगel_sfr_nvmem_config.dev = dev;
	aपंचांगel_sfr_nvmem_config.priv = priv;

	nvmem = devm_nvmem_रेजिस्टर(dev, &aपंचांगel_sfr_nvmem_config);
	अगर (IS_ERR(nvmem)) अणु
		dev_err(dev, "error registering nvmem config\n");
		वापस PTR_ERR(nvmem);
	पूर्ण

	ret = aपंचांगel_sfr_पढ़ो(priv, 0, sn, SFR_SN_SIZE);
	अगर (ret == 0)
		add_device_अक्रमomness(sn, SFR_SN_SIZE);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_sfr_dt_ids[] = अणु
	अणु
		.compatible = "atmel,sama5d2-sfr",
	पूर्ण, अणु
		.compatible = "atmel,sama5d4-sfr",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_sfr_dt_ids);

अटल काष्ठा platक्रमm_driver aपंचांगel_sfr_driver = अणु
	.probe = aपंचांगel_sfr_probe,
	.driver = अणु
		.name = "atmel-sfr",
		.of_match_table = aपंचांगel_sfr_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_sfr_driver);

MODULE_AUTHOR("Kamel Bouhara <kamel.bouhara@bootlin.com>");
MODULE_DESCRIPTION("Atmel SFR SN driver for SAMA5D2/4 SoC family");
MODULE_LICENSE("GPL v2");
