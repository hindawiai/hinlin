<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Pengutronix, Steffen Trumtrar <kernel@pengutronix.de>
 * Copyright (c) 2017 Pengutronix, Oleksij Rempel <kernel@pengutronix.de>
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#घोषणा IMX6Q_SNVS_HPLR		0x00
#घोषणा IMX6Q_SNVS_LPLR		0x34
#घोषणा IMX6Q_SNVS_LPGPR	0x68

#घोषणा IMX7D_SNVS_HPLR		0x00
#घोषणा IMX7D_SNVS_LPLR		0x34
#घोषणा IMX7D_SNVS_LPGPR	0x90

#घोषणा IMX_GPR_SL		BIT(5)
#घोषणा IMX_GPR_HL		BIT(5)

काष्ठा snvs_lpgpr_cfg अणु
	पूर्णांक offset;
	पूर्णांक offset_hplr;
	पूर्णांक offset_lplr;
	पूर्णांक size;
पूर्ण;

काष्ठा snvs_lpgpr_priv अणु
	काष्ठा device_d			*dev;
	काष्ठा regmap			*regmap;
	काष्ठा nvmem_config		cfg;
	स्थिर काष्ठा snvs_lpgpr_cfg	*dcfg;
पूर्ण;

अटल स्थिर काष्ठा snvs_lpgpr_cfg snvs_lpgpr_cfg_imx6q = अणु
	.offset		= IMX6Q_SNVS_LPGPR,
	.offset_hplr	= IMX6Q_SNVS_HPLR,
	.offset_lplr	= IMX6Q_SNVS_LPLR,
	.size		= 4,
पूर्ण;

अटल स्थिर काष्ठा snvs_lpgpr_cfg snvs_lpgpr_cfg_imx7d = अणु
	.offset		= IMX7D_SNVS_LPGPR,
	.offset_hplr	= IMX7D_SNVS_HPLR,
	.offset_lplr	= IMX7D_SNVS_LPLR,
	.size		= 16,
पूर्ण;

अटल पूर्णांक snvs_lpgpr_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *val,
			    माप_प्रकार bytes)
अणु
	काष्ठा snvs_lpgpr_priv *priv = context;
	स्थिर काष्ठा snvs_lpgpr_cfg *dcfg = priv->dcfg;
	अचिन्हित पूर्णांक lock_reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, dcfg->offset_hplr, &lock_reg);
	अगर (ret < 0)
		वापस ret;

	अगर (lock_reg & IMX_GPR_SL)
		वापस -EPERM;

	ret = regmap_पढ़ो(priv->regmap, dcfg->offset_lplr, &lock_reg);
	अगर (ret < 0)
		वापस ret;

	अगर (lock_reg & IMX_GPR_HL)
		वापस -EPERM;

	वापस regmap_bulk_ग_लिखो(priv->regmap, dcfg->offset + offset, val,
				bytes / 4);
पूर्ण

अटल पूर्णांक snvs_lpgpr_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *val,
			   माप_प्रकार bytes)
अणु
	काष्ठा snvs_lpgpr_priv *priv = context;
	स्थिर काष्ठा snvs_lpgpr_cfg *dcfg = priv->dcfg;

	वापस regmap_bulk_पढ़ो(priv->regmap, dcfg->offset + offset,
			       val, bytes / 4);
पूर्ण

अटल पूर्णांक snvs_lpgpr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *syscon_node;
	काष्ठा snvs_lpgpr_priv *priv;
	काष्ठा nvmem_config *cfg;
	काष्ठा nvmem_device *nvmem;
	स्थिर काष्ठा snvs_lpgpr_cfg *dcfg;

	अगर (!node)
		वापस -ENOENT;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dcfg = of_device_get_match_data(dev);
	अगर (!dcfg)
		वापस -EINVAL;

	syscon_node = of_get_parent(node);
	अगर (!syscon_node)
		वापस -ENODEV;

	priv->regmap = syscon_node_to_regmap(syscon_node);
	of_node_put(syscon_node);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->dcfg = dcfg;

	cfg = &priv->cfg;
	cfg->priv = priv;
	cfg->name = dev_name(dev);
	cfg->dev = dev;
	cfg->stride = 4;
	cfg->word_size = 4;
	cfg->size = dcfg->size;
	cfg->owner = THIS_MODULE;
	cfg->reg_पढ़ो  = snvs_lpgpr_पढ़ो;
	cfg->reg_ग_लिखो = snvs_lpgpr_ग_लिखो;

	nvmem = devm_nvmem_रेजिस्टर(dev, cfg);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id snvs_lpgpr_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-snvs-lpgpr", .data = &snvs_lpgpr_cfg_imx6q पूर्ण,
	अणु .compatible = "fsl,imx6ul-snvs-lpgpr",
	  .data = &snvs_lpgpr_cfg_imx6q पूर्ण,
	अणु .compatible = "fsl,imx7d-snvs-lpgpr",	.data = &snvs_lpgpr_cfg_imx7d पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, snvs_lpgpr_dt_ids);

अटल काष्ठा platक्रमm_driver snvs_lpgpr_driver = अणु
	.probe	= snvs_lpgpr_probe,
	.driver = अणु
		.name	= "snvs_lpgpr",
		.of_match_table = snvs_lpgpr_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snvs_lpgpr_driver);

MODULE_AUTHOR("Oleksij Rempel <o.rempel@pengutronix.de>");
MODULE_DESCRIPTION("Low Power General Purpose Register in i.MX6 and i.MX7 Secure Non-Volatile Storage");
MODULE_LICENSE("GPL v2");
