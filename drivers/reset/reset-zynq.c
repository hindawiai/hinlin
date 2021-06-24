<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, National Instruments Corp.
 *
 * Xilinx Zynq Reset controller driver
 *
 * Author: Moritz Fischer <moritz.fischer@ettus.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

काष्ठा zynq_reset_data अणु
	काष्ठा regmap *slcr;
	काष्ठा reset_controller_dev rcdev;
	u32 offset;
पूर्ण;

#घोषणा to_zynq_reset_data(p)		\
	container_of((p), काष्ठा zynq_reset_data, rcdev)

अटल पूर्णांक zynq_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा zynq_reset_data *priv = to_zynq_reset_data(rcdev);

	पूर्णांक bank = id / BITS_PER_LONG;
	पूर्णांक offset = id % BITS_PER_LONG;

	pr_debug("%s: %s reset bank %u offset %u\n", KBUILD_MODNAME, __func__,
		 bank, offset);

	वापस regmap_update_bits(priv->slcr,
				  priv->offset + (bank * 4),
				  BIT(offset),
				  BIT(offset));
पूर्ण

अटल पूर्णांक zynq_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा zynq_reset_data *priv = to_zynq_reset_data(rcdev);

	पूर्णांक bank = id / BITS_PER_LONG;
	पूर्णांक offset = id % BITS_PER_LONG;

	pr_debug("%s: %s reset bank %u offset %u\n", KBUILD_MODNAME, __func__,
		 bank, offset);

	वापस regmap_update_bits(priv->slcr,
				  priv->offset + (bank * 4),
				  BIT(offset),
				  ~BIT(offset));
पूर्ण

अटल पूर्णांक zynq_reset_status(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा zynq_reset_data *priv = to_zynq_reset_data(rcdev);

	पूर्णांक bank = id / BITS_PER_LONG;
	पूर्णांक offset = id % BITS_PER_LONG;
	पूर्णांक ret;
	u32 reg;

	pr_debug("%s: %s reset bank %u offset %u\n", KBUILD_MODNAME, __func__,
		 bank, offset);

	ret = regmap_पढ़ो(priv->slcr, priv->offset + (bank * 4), &reg);
	अगर (ret)
		वापस ret;

	वापस !!(reg & BIT(offset));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops zynq_reset_ops = अणु
	.निश्चित		= zynq_reset_निश्चित,
	.deनिश्चित	= zynq_reset_deनिश्चित,
	.status		= zynq_reset_status,
पूर्ण;

अटल पूर्णांक zynq_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा zynq_reset_data *priv;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->slcr = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						     "syscon");
	अगर (IS_ERR(priv->slcr)) अणु
		dev_err(&pdev->dev, "unable to get zynq-slcr regmap");
		वापस PTR_ERR(priv->slcr);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "missing IO resource\n");
		वापस -ENODEV;
	पूर्ण

	priv->offset = res->start;

	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.nr_resets = resource_size(res) / 4 * BITS_PER_LONG;
	priv->rcdev.ops = &zynq_reset_ops;
	priv->rcdev.of_node = pdev->dev.of_node;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id zynq_reset_dt_ids[] = अणु
	अणु .compatible = "xlnx,zynq-reset", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver zynq_reset_driver = अणु
	.probe	= zynq_reset_probe,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= zynq_reset_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(zynq_reset_driver);
