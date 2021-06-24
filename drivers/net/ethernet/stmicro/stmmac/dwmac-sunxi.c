<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dwmac-sunxi.c - Allwinner sunxi DWMAC specअगरic glue layer
 *
 * Copyright (C) 2013 Chen-Yu Tsai
 *
 * Chen-Yu Tsai  <wens@csie.org>
 */

#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "stmmac_platform.h"

काष्ठा sunxi_priv_data अणु
	phy_पूर्णांकerface_t पूर्णांकerface;
	पूर्णांक clk_enabled;
	काष्ठा clk *tx_clk;
	काष्ठा regulator *regulator;
पूर्ण;

#घोषणा SUN7I_GMAC_GMII_RGMII_RATE	125000000
#घोषणा SUN7I_GMAC_MII_RATE		25000000

अटल पूर्णांक sun7i_gmac_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा sunxi_priv_data *gmac = priv;
	पूर्णांक ret = 0;

	अगर (gmac->regulator) अणु
		ret = regulator_enable(gmac->regulator);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set GMAC पूर्णांकerface port mode
	 *
	 * The GMAC TX घड़ी lines are configured by setting the घड़ी
	 * rate, which then uses the स्वतः-reparenting feature of the
	 * घड़ी driver, and enabling/disabling the घड़ी.
	 */
	अगर (phy_पूर्णांकerface_mode_is_rgmii(gmac->पूर्णांकerface)) अणु
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_GMII_RGMII_RATE);
		clk_prepare_enable(gmac->tx_clk);
		gmac->clk_enabled = 1;
	पूर्ण अन्यथा अणु
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_MII_RATE);
		ret = clk_prepare(gmac->tx_clk);
		अगर (ret && gmac->regulator)
			regulator_disable(gmac->regulator);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sun7i_gmac_निकास(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा sunxi_priv_data *gmac = priv;

	अगर (gmac->clk_enabled) अणु
		clk_disable(gmac->tx_clk);
		gmac->clk_enabled = 0;
	पूर्ण
	clk_unprepare(gmac->tx_clk);

	अगर (gmac->regulator)
		regulator_disable(gmac->regulator);
पूर्ण

अटल व्योम sun7i_fix_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा sunxi_priv_data *gmac = priv;

	/* only GMII mode requires us to reconfigure the घड़ी lines */
	अगर (gmac->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
		वापस;

	अगर (gmac->clk_enabled) अणु
		clk_disable(gmac->tx_clk);
		gmac->clk_enabled = 0;
	पूर्ण
	clk_unprepare(gmac->tx_clk);

	अगर (speed == 1000) अणु
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_GMII_RGMII_RATE);
		clk_prepare_enable(gmac->tx_clk);
		gmac->clk_enabled = 1;
	पूर्ण अन्यथा अणु
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_MII_RATE);
		clk_prepare(gmac->tx_clk);
	पूर्ण
पूर्ण

अटल पूर्णांक sun7i_gmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा sunxi_priv_data *gmac;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	gmac = devm_kzalloc(dev, माप(*gmac), GFP_KERNEL);
	अगर (!gmac) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	ret = of_get_phy_mode(dev->of_node, &gmac->पूर्णांकerface);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(dev, "Can't get phy-mode\n");
		जाओ err_हटाओ_config_dt;
	पूर्ण

	gmac->tx_clk = devm_clk_get(dev, "allwinner_gmac_tx");
	अगर (IS_ERR(gmac->tx_clk)) अणु
		dev_err(dev, "could not get tx clock\n");
		ret = PTR_ERR(gmac->tx_clk);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	/* Optional regulator क्रम PHY */
	gmac->regulator = devm_regulator_get_optional(dev, "phy");
	अगर (IS_ERR(gmac->regulator)) अणु
		अगर (PTR_ERR(gmac->regulator) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_हटाओ_config_dt;
		पूर्ण
		dev_info(dev, "no regulator found\n");
		gmac->regulator = शून्य;
	पूर्ण

	/* platक्रमm data specअगरying hardware features and callbacks.
	 * hardware features were copied from Allwinner drivers. */
	plat_dat->tx_coe = 1;
	plat_dat->has_gmac = true;
	plat_dat->bsp_priv = gmac;
	plat_dat->init = sun7i_gmac_init;
	plat_dat->निकास = sun7i_gmac_निकास;
	plat_dat->fix_mac_speed = sun7i_fix_speed;
	plat_dat->tx_fअगरo_size = 4096;
	plat_dat->rx_fअगरo_size = 16384;

	ret = sun7i_gmac_init(pdev, plat_dat->bsp_priv);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_gmac_निकास;

	वापस 0;

err_gmac_निकास:
	sun7i_gmac_निकास(pdev, plat_dat->bsp_priv);
err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun7i_dwmac_match[] = अणु
	अणु .compatible = "allwinner,sun7i-a20-gmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun7i_dwmac_match);

अटल काष्ठा platक्रमm_driver sun7i_dwmac_driver = अणु
	.probe  = sun7i_gmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "sun7i-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = sun7i_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun7i_dwmac_driver);

MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_DESCRIPTION("Allwinner sunxi DWMAC specific glue layer");
MODULE_LICENSE("GPL");
