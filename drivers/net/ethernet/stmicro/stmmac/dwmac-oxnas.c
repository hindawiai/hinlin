<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Oxक्रमd Semiconductor OXNAS DWMAC glue layer
 *
 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2014 Daniel Golle <daniel@makrotopia.org>
 * Copyright (C) 2013 Ma Haijun <mahaijuns@gmail.com>
 * Copyright (C) 2012 John Crispin <blogic@खोलोwrt.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"

/* System Control regmap offsets */
#घोषणा OXNAS_DWMAC_CTRL_REGOFFSET	0x78
#घोषणा OXNAS_DWMAC_DELAY_REGOFFSET	0x100

/* Control Register */
#घोषणा DWMAC_CKEN_RX_IN        14
#घोषणा DWMAC_CKEN_RXN_OUT      13
#घोषणा DWMAC_CKEN_RX_OUT       12
#घोषणा DWMAC_CKEN_TX_IN        10
#घोषणा DWMAC_CKEN_TXN_OUT      9
#घोषणा DWMAC_CKEN_TX_OUT       8
#घोषणा DWMAC_RX_SOURCE         7
#घोषणा DWMAC_TX_SOURCE         6
#घोषणा DWMAC_LOW_TX_SOURCE     4
#घोषणा DWMAC_AUTO_TX_SOURCE    3
#घोषणा DWMAC_RGMII             2
#घोषणा DWMAC_SIMPLE_MUX        1
#घोषणा DWMAC_CKEN_GTX          0

/* Delay रेजिस्टर */
#घोषणा DWMAC_TX_VARDELAY_SHIFT		0
#घोषणा DWMAC_TXN_VARDELAY_SHIFT	8
#घोषणा DWMAC_RX_VARDELAY_SHIFT		16
#घोषणा DWMAC_RXN_VARDELAY_SHIFT	24
#घोषणा DWMAC_TX_VARDELAY(d)		((d) << DWMAC_TX_VARDELAY_SHIFT)
#घोषणा DWMAC_TXN_VARDELAY(d)		((d) << DWMAC_TXN_VARDELAY_SHIFT)
#घोषणा DWMAC_RX_VARDELAY(d)		((d) << DWMAC_RX_VARDELAY_SHIFT)
#घोषणा DWMAC_RXN_VARDELAY(d)		((d) << DWMAC_RXN_VARDELAY_SHIFT)

काष्ठा oxnas_dwmac अणु
	काष्ठा device	*dev;
	काष्ठा clk	*clk;
	काष्ठा regmap	*regmap;
पूर्ण;

अटल पूर्णांक oxnas_dwmac_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा oxnas_dwmac *dwmac = priv;
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	/* Reset HW here beक्रमe changing the glue configuration */
	ret = device_reset(dwmac->dev);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(dwmac->clk);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(dwmac->regmap, OXNAS_DWMAC_CTRL_REGOFFSET, &value);
	अगर (ret < 0) अणु
		clk_disable_unprepare(dwmac->clk);
		वापस ret;
	पूर्ण

	/* Enable GMII_GTXCLK to follow GMII_REFCLK, required क्रम gigabit PHY */
	value |= BIT(DWMAC_CKEN_GTX)		|
		 /* Use simple mux क्रम 25/125 Mhz घड़ी चयनing */
		 BIT(DWMAC_SIMPLE_MUX)		|
		 /* set स्वतः चयन tx घड़ी source */
		 BIT(DWMAC_AUTO_TX_SOURCE)	|
		 /* enable tx & rx vardelay */
		 BIT(DWMAC_CKEN_TX_OUT)		|
		 BIT(DWMAC_CKEN_TXN_OUT)	|
		 BIT(DWMAC_CKEN_TX_IN)		|
		 BIT(DWMAC_CKEN_RX_OUT)		|
		 BIT(DWMAC_CKEN_RXN_OUT)	|
		 BIT(DWMAC_CKEN_RX_IN);
	regmap_ग_लिखो(dwmac->regmap, OXNAS_DWMAC_CTRL_REGOFFSET, value);

	/* set tx & rx vardelay */
	value = DWMAC_TX_VARDELAY(4)	|
		DWMAC_TXN_VARDELAY(2)	|
		DWMAC_RX_VARDELAY(10)	|
		DWMAC_RXN_VARDELAY(8);
	regmap_ग_लिखो(dwmac->regmap, OXNAS_DWMAC_DELAY_REGOFFSET, value);

	वापस 0;
पूर्ण

अटल व्योम oxnas_dwmac_निकास(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा oxnas_dwmac *dwmac = priv;

	clk_disable_unprepare(dwmac->clk);
पूर्ण

अटल पूर्णांक oxnas_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा oxnas_dwmac *dwmac;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	dwmac = devm_kzalloc(&pdev->dev, माप(*dwmac), GFP_KERNEL);
	अगर (!dwmac) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->dev = &pdev->dev;
	plat_dat->bsp_priv = dwmac;
	plat_dat->init = oxnas_dwmac_init;
	plat_dat->निकास = oxnas_dwmac_निकास;

	dwmac->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"oxsemi,sys-ctrl");
	अगर (IS_ERR(dwmac->regmap)) अणु
		dev_err(&pdev->dev, "failed to have sysctrl regmap\n");
		ret = PTR_ERR(dwmac->regmap);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->clk = devm_clk_get(&pdev->dev, "gmac");
	अगर (IS_ERR(dwmac->clk)) अणु
		ret = PTR_ERR(dwmac->clk);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	ret = oxnas_dwmac_init(pdev, plat_dat->bsp_priv);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_dwmac_निकास;


	वापस 0;

err_dwmac_निकास:
	oxnas_dwmac_निकास(pdev, plat_dat->bsp_priv);
err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id oxnas_dwmac_match[] = अणु
	अणु .compatible = "oxsemi,ox820-dwmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, oxnas_dwmac_match);

अटल काष्ठा platक्रमm_driver oxnas_dwmac_driver = अणु
	.probe  = oxnas_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "oxnas-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = oxnas_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(oxnas_dwmac_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Oxford Semiconductor OXNAS DWMAC glue layer");
MODULE_LICENSE("GPL v2");
