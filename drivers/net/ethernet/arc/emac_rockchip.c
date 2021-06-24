<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * emac-rockchip.c - Rockchip EMAC specअगरic glue layer
 *
 * Copyright (C) 2014 Roमुख्य Perier <roमुख्य.perier@gmail.com>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "emac.h"

#घोषणा DRV_NAME        "rockchip_emac"

काष्ठा emac_rockchip_soc_data अणु
	अचिन्हित पूर्णांक grf_offset;
	अचिन्हित पूर्णांक grf_mode_offset;
	अचिन्हित पूर्णांक grf_speed_offset;
	bool need_भाग_macclk;
पूर्ण;

काष्ठा rockchip_priv_data अणु
	काष्ठा arc_emac_priv emac;
	काष्ठा regmap *grf;
	स्थिर काष्ठा emac_rockchip_soc_data *soc_data;
	काष्ठा regulator *regulator;
	काष्ठा clk *refclk;
	काष्ठा clk *macclk;
पूर्ण;

अटल व्योम emac_rockchip_set_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा rockchip_priv_data *emac = priv;
	u32 speed_offset = emac->soc_data->grf_speed_offset;
	u32 data;
	पूर्णांक err = 0;

	चयन (speed) अणु
	हाल 10:
		data = (1 << (speed_offset + 16)) | (0 << speed_offset);
		अवरोध;
	हाल 100:
		data = (1 << (speed_offset + 16)) | (1 << speed_offset);
		अवरोध;
	शेष:
		pr_err("speed %u not supported\n", speed);
		वापस;
	पूर्ण

	err = regmap_ग_लिखो(emac->grf, emac->soc_data->grf_offset, data);
	अगर (err)
		pr_err("unable to apply speed %u to grf (%d)\n", speed, err);
पूर्ण

अटल स्थिर काष्ठा emac_rockchip_soc_data emac_rk3036_emac_data = अणु
	.grf_offset = 0x140,   .grf_mode_offset = 8,
	.grf_speed_offset = 9, .need_भाग_macclk = 1,
पूर्ण;

अटल स्थिर काष्ठा emac_rockchip_soc_data emac_rk3066_emac_data = अणु
	.grf_offset = 0x154,   .grf_mode_offset = 0,
	.grf_speed_offset = 1, .need_भाग_macclk = 0,
पूर्ण;

अटल स्थिर काष्ठा emac_rockchip_soc_data emac_rk3188_emac_data = अणु
	.grf_offset = 0x0a4,   .grf_mode_offset = 0,
	.grf_speed_offset = 1, .need_भाग_macclk = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id emac_rockchip_dt_ids[] = अणु
	अणु
		.compatible = "rockchip,rk3036-emac",
		.data = &emac_rk3036_emac_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3066-emac",
		.data = &emac_rk3066_emac_data,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3188-emac",
		.data = &emac_rk3188_emac_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, emac_rockchip_dt_ids);

अटल पूर्णांक emac_rockchip_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *ndev;
	काष्ठा rockchip_priv_data *priv;
	स्थिर काष्ठा of_device_id *match;
	phy_पूर्णांकerface_t पूर्णांकerface;
	u32 data;
	पूर्णांक err;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	ndev = alloc_etherdev(माप(काष्ठा rockchip_priv_data));
	अगर (!ndev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);

	priv = netdev_priv(ndev);
	priv->emac.drv_name = DRV_NAME;
	priv->emac.set_mac_speed = emac_rockchip_set_mac_speed;

	err = of_get_phy_mode(dev->of_node, &पूर्णांकerface);
	अगर (err)
		जाओ out_netdev;

	/* RK3036/RK3066/RK3188 SoCs only support RMII */
	अगर (पूर्णांकerface != PHY_INTERFACE_MODE_RMII) अणु
		dev_err(dev, "unsupported phy interface mode %d\n", पूर्णांकerface);
		err = -ENOTSUPP;
		जाओ out_netdev;
	पूर्ण

	priv->grf = syscon_regmap_lookup_by_phandle(dev->of_node,
						    "rockchip,grf");
	अगर (IS_ERR(priv->grf)) अणु
		dev_err(dev, "failed to retrieve global register file (%ld)\n",
			PTR_ERR(priv->grf));
		err = PTR_ERR(priv->grf);
		जाओ out_netdev;
	पूर्ण

	match = of_match_node(emac_rockchip_dt_ids, dev->of_node);
	priv->soc_data = match->data;

	priv->emac.clk = devm_clk_get(dev, "hclk");
	अगर (IS_ERR(priv->emac.clk)) अणु
		dev_err(dev, "failed to retrieve host clock (%ld)\n",
			PTR_ERR(priv->emac.clk));
		err = PTR_ERR(priv->emac.clk);
		जाओ out_netdev;
	पूर्ण

	priv->refclk = devm_clk_get(dev, "macref");
	अगर (IS_ERR(priv->refclk)) अणु
		dev_err(dev, "failed to retrieve reference clock (%ld)\n",
			PTR_ERR(priv->refclk));
		err = PTR_ERR(priv->refclk);
		जाओ out_netdev;
	पूर्ण

	err = clk_prepare_enable(priv->refclk);
	अगर (err) अणु
		dev_err(dev, "failed to enable reference clock (%d)\n", err);
		जाओ out_netdev;
	पूर्ण

	/* Optional regulator क्रम PHY */
	priv->regulator = devm_regulator_get_optional(dev, "phy");
	अगर (IS_ERR(priv->regulator)) अणु
		अगर (PTR_ERR(priv->regulator) == -EPROBE_DEFER) अणु
			err = -EPROBE_DEFER;
			जाओ out_clk_disable;
		पूर्ण
		dev_err(dev, "no regulator found\n");
		priv->regulator = शून्य;
	पूर्ण

	अगर (priv->regulator) अणु
		err = regulator_enable(priv->regulator);
		अगर (err) अणु
			dev_err(dev, "failed to enable phy-supply (%d)\n", err);
			जाओ out_clk_disable;
		पूर्ण
	पूर्ण

	/* Set speed 100M */
	data = (1 << (priv->soc_data->grf_speed_offset + 16)) |
	       (1 << priv->soc_data->grf_speed_offset);
	/* Set RMII mode */
	data |= (1 << (priv->soc_data->grf_mode_offset + 16)) |
		(0 << priv->soc_data->grf_mode_offset);

	err = regmap_ग_लिखो(priv->grf, priv->soc_data->grf_offset, data);
	अगर (err) अणु
		dev_err(dev, "unable to apply initial settings to grf (%d)\n",
			err);
		जाओ out_regulator_disable;
	पूर्ण

	/* RMII पूर्णांकerface needs always a rate of 50MHz */
	err = clk_set_rate(priv->refclk, 50000000);
	अगर (err) अणु
		dev_err(dev,
			"failed to change reference clock rate (%d)\n", err);
		जाओ out_regulator_disable;
	पूर्ण

	अगर (priv->soc_data->need_भाग_macclk) अणु
		priv->macclk = devm_clk_get(dev, "macclk");
		अगर (IS_ERR(priv->macclk)) अणु
			dev_err(dev, "failed to retrieve mac clock (%ld)\n",
				PTR_ERR(priv->macclk));
			err = PTR_ERR(priv->macclk);
			जाओ out_regulator_disable;
		पूर्ण

		err = clk_prepare_enable(priv->macclk);
		अगर (err) अणु
			dev_err(dev, "failed to enable mac clock (%d)\n", err);
			जाओ out_regulator_disable;
		पूर्ण

		/* RMII TX/RX needs always a rate of 25MHz */
		err = clk_set_rate(priv->macclk, 25000000);
		अगर (err) अणु
			dev_err(dev,
				"failed to change mac clock rate (%d)\n", err);
			जाओ out_clk_disable_macclk;
		पूर्ण
	पूर्ण

	err = arc_emac_probe(ndev, पूर्णांकerface);
	अगर (err) अणु
		dev_err(dev, "failed to probe arc emac (%d)\n", err);
		जाओ out_clk_disable_macclk;
	पूर्ण

	वापस 0;

out_clk_disable_macclk:
	अगर (priv->soc_data->need_भाग_macclk)
		clk_disable_unprepare(priv->macclk);
out_regulator_disable:
	अगर (priv->regulator)
		regulator_disable(priv->regulator);
out_clk_disable:
	clk_disable_unprepare(priv->refclk);
out_netdev:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक emac_rockchip_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा rockchip_priv_data *priv = netdev_priv(ndev);
	पूर्णांक err;

	err = arc_emac_हटाओ(ndev);

	clk_disable_unprepare(priv->refclk);

	अगर (priv->regulator)
		regulator_disable(priv->regulator);

	अगर (priv->soc_data->need_भाग_macclk)
		clk_disable_unprepare(priv->macclk);

	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver emac_rockchip_driver = अणु
	.probe = emac_rockchip_probe,
	.हटाओ = emac_rockchip_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table  = emac_rockchip_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(emac_rockchip_driver);

MODULE_AUTHOR("Romain Perier <romain.perier@gmail.com>");
MODULE_DESCRIPTION("Rockchip EMAC platform driver");
MODULE_LICENSE("GPL");
