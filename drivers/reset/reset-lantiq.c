<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <blogic@phrozen.org>
 *  Copyright (C) 2013-2015 Lantiq Beteiligungs-GmbH & Co.KG
 *  Copyright (C) 2016 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 *  Copyright (C) 2017 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#घोषणा LANTIQ_RCU_RESET_TIMEOUT	10000

काष्ठा lantiq_rcu_reset_priv अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	u32 reset_offset;
	u32 status_offset;
पूर्ण;

अटल काष्ठा lantiq_rcu_reset_priv *to_lantiq_rcu_reset_priv(
	काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा lantiq_rcu_reset_priv, rcdev);
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_status(काष्ठा reset_controller_dev *rcdev,
				   अचिन्हित दीर्घ id)
अणु
	काष्ठा lantiq_rcu_reset_priv *priv = to_lantiq_rcu_reset_priv(rcdev);
	अचिन्हित पूर्णांक status = (id >> 8) & 0x1f;
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, priv->status_offset, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(status));
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_status_समयout(काष्ठा reset_controller_dev *rcdev,
					   अचिन्हित दीर्घ id, bool निश्चित)
अणु
	पूर्णांक ret;
	पूर्णांक retry = LANTIQ_RCU_RESET_TIMEOUT;

	करो अणु
		ret = lantiq_rcu_reset_status(rcdev, id);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == निश्चित)
			वापस 0;
		usleep_range(20, 40);
	पूर्ण जबतक (--retry);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_update(काष्ठा reset_controller_dev *rcdev,
				   अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा lantiq_rcu_reset_priv *priv = to_lantiq_rcu_reset_priv(rcdev);
	अचिन्हित पूर्णांक set = id & 0x1f;
	u32 val = निश्चित ? BIT(set) : 0;
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap, priv->reset_offset, BIT(set),
				 val);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to set reset bit %u\n", set);
		वापस ret;
	पूर्ण


	ret = lantiq_rcu_reset_status_समयout(rcdev, id, निश्चित);
	अगर (ret)
		dev_err(priv->dev, "Failed to %s bit %u\n",
			निश्चित ? "assert" : "deassert", set);

	वापस ret;
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	वापस lantiq_rcu_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस lantiq_rcu_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_reset(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;

	ret = lantiq_rcu_reset_निश्चित(rcdev, id);
	अगर (ret)
		वापस ret;

	वापस lantiq_rcu_reset_deनिश्चित(rcdev, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops lantiq_rcu_reset_ops = अणु
	.निश्चित = lantiq_rcu_reset_निश्चित,
	.deनिश्चित = lantiq_rcu_reset_deनिश्चित,
	.status = lantiq_rcu_reset_status,
	.reset	= lantiq_rcu_reset_reset,
पूर्ण;

अटल पूर्णांक lantiq_rcu_reset_of_parse(काष्ठा platक्रमm_device *pdev,
			       काष्ठा lantiq_rcu_reset_priv *priv)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर __be32 *offset;

	priv->regmap = syscon_node_to_regmap(dev->of_node->parent);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(&pdev->dev, "Failed to lookup RCU regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	offset = of_get_address(dev->of_node, 0, शून्य, शून्य);
	अगर (!offset) अणु
		dev_err(&pdev->dev, "Failed to get RCU reset offset\n");
		वापस -ENOENT;
	पूर्ण
	priv->reset_offset = __be32_to_cpu(*offset);

	offset = of_get_address(dev->of_node, 1, शून्य, शून्य);
	अगर (!offset) अणु
		dev_err(&pdev->dev, "Failed to get RCU status offset\n");
		वापस -ENOENT;
	पूर्ण
	priv->status_offset = __be32_to_cpu(*offset);

	वापस 0;
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_xlate(काष्ठा reset_controller_dev *rcdev,
				  स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अचिन्हित पूर्णांक status, set;

	set = reset_spec->args[0];
	status = reset_spec->args[1];

	अगर (set >= rcdev->nr_resets || status >= rcdev->nr_resets)
		वापस -EINVAL;

	वापस (status << 8) | set;
पूर्ण

अटल पूर्णांक lantiq_rcu_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lantiq_rcu_reset_priv *priv;
	पूर्णांक err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, priv);

	err = lantiq_rcu_reset_of_parse(pdev, priv);
	अगर (err)
		वापस err;

	priv->rcdev.ops = &lantiq_rcu_reset_ops;
	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.of_node = pdev->dev.of_node;
	priv->rcdev.nr_resets = 32;
	priv->rcdev.of_xlate = lantiq_rcu_reset_xlate;
	priv->rcdev.of_reset_n_cells = 2;

	वापस reset_controller_रेजिस्टर(&priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id lantiq_rcu_reset_dt_ids[] = अणु
	अणु .compatible = "lantiq,danube-reset", पूर्ण,
	अणु .compatible = "lantiq,xrx200-reset", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lantiq_rcu_reset_dt_ids);

अटल काष्ठा platक्रमm_driver lantiq_rcu_reset_driver = अणु
	.probe	= lantiq_rcu_reset_probe,
	.driver = अणु
		.name		= "lantiq-reset",
		.of_match_table	= lantiq_rcu_reset_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lantiq_rcu_reset_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Lantiq XWAY RCU Reset Controller Driver");
MODULE_LICENSE("GPL");
