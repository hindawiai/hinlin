<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा brcm_nvram अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक brcm_nvram_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *val,
			   माप_प्रकार bytes)
अणु
	काष्ठा brcm_nvram *priv = context;
	u8 *dst = val;

	जबतक (bytes--)
		*dst++ = पढ़ोb(priv->base + offset++);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_nvram_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvmem_config config = अणु
		.name = "brcm-nvram",
		.reg_पढ़ो = brcm_nvram_पढ़ो,
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा brcm_nvram *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	config.dev = dev;
	config.priv = priv;
	config.size = resource_size(res);

	वापस PTR_ERR_OR_ZERO(devm_nvmem_रेजिस्टर(dev, &config));
पूर्ण

अटल स्थिर काष्ठा of_device_id brcm_nvram_of_match_table[] = अणु
	अणु .compatible = "brcm,nvram", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver brcm_nvram_driver = अणु
	.probe = brcm_nvram_probe,
	.driver = अणु
		.name = "brcm_nvram",
		.of_match_table = brcm_nvram_of_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init brcm_nvram_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&brcm_nvram_driver);
पूर्ण

subsys_initcall_sync(brcm_nvram_init);

MODULE_AUTHOR("Rafaध Miधecki");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(of, brcm_nvram_of_match_table);
