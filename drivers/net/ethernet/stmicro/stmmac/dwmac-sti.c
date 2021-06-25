<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dwmac-sti.c - STMicroelectronics DWMAC Specअगरic Glue layer
 *
 * Copyright (C) 2003-2014 STMicroelectronics (R&D) Limited
 * Author: Srinivas Kandagatla <srinivas.kandagatla@st.com>
 * Contributors: Giuseppe Cavallaro <peppe.cavallaro@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/phy.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>

#समावेश "stmmac_platform.h"

#घोषणा DWMAC_125MHZ	125000000
#घोषणा DWMAC_50MHZ	50000000
#घोषणा DWMAC_25MHZ	25000000
#घोषणा DWMAC_2_5MHZ	2500000

#घोषणा IS_PHY_IF_MODE_RGMII(अगरace)	(अगरace == PHY_INTERFACE_MODE_RGMII || \
			अगरace == PHY_INTERFACE_MODE_RGMII_ID || \
			अगरace == PHY_INTERFACE_MODE_RGMII_RXID || \
			अगरace == PHY_INTERFACE_MODE_RGMII_TXID)

#घोषणा IS_PHY_IF_MODE_GBIT(अगरace)	(IS_PHY_IF_MODE_RGMII(अगरace) || \
					 अगरace == PHY_INTERFACE_MODE_GMII)

/* STiH4xx रेजिस्टर definitions (STiH415/STiH416/STiH407/STiH410 families)
 *
 * Below table summarizes the घड़ी requirement and घड़ी sources क्रम
 * supported phy पूर्णांकerface modes with link speeds.
 * ________________________________________________
 *|  PHY_MODE	| 1000 Mbit Link | 100 Mbit Link   |
 * ------------------------------------------------
 *|	MII	|	n/a	 |	25Mhz	   |
 *|		|		 |	txclk	   |
 * ------------------------------------------------
 *|	GMII	|     125Mhz	 |	25Mhz	   |
 *|		|  clk-125/txclk |	txclk	   |
 * ------------------------------------------------
 *|	RGMII	|     125Mhz	 |	25Mhz	   |
 *|		|  clk-125/txclk |	clkgen     |
 *|		|    clkgen	 |		   |
 * ------------------------------------------------
 *|	RMII	|	n/a	 |	25Mhz	   |
 *|		|		 |clkgen/phyclk-in |
 * ------------------------------------------------
 *
 *	  Register Configuration
 *-------------------------------
 * src	 |BIT(8)| BIT(7)| BIT(6)|
 *-------------------------------
 * txclk |   0	|  n/a	|   1	|
 *-------------------------------
 * ck_125|   0	|  n/a	|   0	|
 *-------------------------------
 * phyclk|   1	|   0	|  n/a	|
 *-------------------------------
 * clkgen|   1	|   1	|  n/a	|
 *-------------------------------
 */

#घोषणा STIH4XX_RETIME_SRC_MASK			GENMASK(8, 6)
#घोषणा STIH4XX_ETH_SEL_TX_RETIME_CLK		BIT(8)
#घोषणा STIH4XX_ETH_SEL_INTERNAL_NOTEXT_PHYCLK	BIT(7)
#घोषणा STIH4XX_ETH_SEL_TXCLK_NOT_CLK125	BIT(6)

/* STiD127 रेजिस्टर definitions
 *-----------------------
 * src	 |BIT(6)| BIT(7)|
 *-----------------------
 * MII   |  1	|   n/a	|
 *-----------------------
 * RMII  |  n/a	|   1	|
 * clkgen|	|	|
 *-----------------------
 * RMII  |  n/a	|   0	|
 * phyclk|	|	|
 *-----------------------
 * RGMII |  1	|  n/a	|
 * clkgen|	|	|
 *-----------------------
 */

#घोषणा STID127_RETIME_SRC_MASK			GENMASK(7, 6)
#घोषणा STID127_ETH_SEL_INTERNAL_NOTEXT_PHYCLK	BIT(7)
#घोषणा STID127_ETH_SEL_INTERNAL_NOTEXT_TXCLK	BIT(6)

#घोषणा ENMII_MASK	GENMASK(5, 5)
#घोषणा ENMII		BIT(5)
#घोषणा EN_MASK		GENMASK(1, 1)
#घोषणा EN		BIT(1)

/*
 * 3 bits [4:2]
 *	000-GMII/MII
 *	001-RGMII
 *	010-SGMII
 *	100-RMII
 */
#घोषणा MII_PHY_SEL_MASK	GENMASK(4, 2)
#घोषणा ETH_PHY_SEL_RMII	BIT(4)
#घोषणा ETH_PHY_SEL_SGMII	BIT(3)
#घोषणा ETH_PHY_SEL_RGMII	BIT(2)
#घोषणा ETH_PHY_SEL_GMII	0x0
#घोषणा ETH_PHY_SEL_MII		0x0

काष्ठा sti_dwmac अणु
	phy_पूर्णांकerface_t पूर्णांकerface;	/* MII पूर्णांकerface */
	bool ext_phyclk;	/* Clock from बाह्यal PHY */
	u32 tx_reसमय_src;	/* TXCLK Retiming*/
	काष्ठा clk *clk;	/* PHY घड़ी */
	u32 ctrl_reg;		/* GMAC glue-logic control रेजिस्टर */
	पूर्णांक clk_sel_reg;	/* GMAC ext clk selection रेजिस्टर */
	काष्ठा regmap *regmap;
	bool gmac_en;
	u32 speed;
	व्योम (*fix_reसमय_src)(व्योम *priv, अचिन्हित पूर्णांक speed);
पूर्ण;

काष्ठा sti_dwmac_of_data अणु
	व्योम (*fix_reसमय_src)(व्योम *priv, अचिन्हित पूर्णांक speed);
पूर्ण;

अटल u32 phy_पूर्णांकf_sels[] = अणु
	[PHY_INTERFACE_MODE_MII] = ETH_PHY_SEL_MII,
	[PHY_INTERFACE_MODE_GMII] = ETH_PHY_SEL_GMII,
	[PHY_INTERFACE_MODE_RGMII] = ETH_PHY_SEL_RGMII,
	[PHY_INTERFACE_MODE_RGMII_ID] = ETH_PHY_SEL_RGMII,
	[PHY_INTERFACE_MODE_SGMII] = ETH_PHY_SEL_SGMII,
	[PHY_INTERFACE_MODE_RMII] = ETH_PHY_SEL_RMII,
पूर्ण;

क्रमागत अणु
	TX_RETIME_SRC_NA = 0,
	TX_RETIME_SRC_TXCLK = 1,
	TX_RETIME_SRC_CLK_125,
	TX_RETIME_SRC_PHYCLK,
	TX_RETIME_SRC_CLKGEN,
पूर्ण;

अटल u32 stih4xx_tx_reसमय_val[] = अणु
	[TX_RETIME_SRC_TXCLK] = STIH4XX_ETH_SEL_TXCLK_NOT_CLK125,
	[TX_RETIME_SRC_CLK_125] = 0x0,
	[TX_RETIME_SRC_PHYCLK] = STIH4XX_ETH_SEL_TX_RETIME_CLK,
	[TX_RETIME_SRC_CLKGEN] = STIH4XX_ETH_SEL_TX_RETIME_CLK
				 | STIH4XX_ETH_SEL_INTERNAL_NOTEXT_PHYCLK,
पूर्ण;

अटल व्योम stih4xx_fix_reसमय_src(व्योम *priv, u32 spd)
अणु
	काष्ठा sti_dwmac *dwmac = priv;
	u32 src = dwmac->tx_reसमय_src;
	u32 reg = dwmac->ctrl_reg;
	u32 freq = 0;

	अगर (dwmac->पूर्णांकerface == PHY_INTERFACE_MODE_MII) अणु
		src = TX_RETIME_SRC_TXCLK;
	पूर्ण अन्यथा अगर (dwmac->पूर्णांकerface == PHY_INTERFACE_MODE_RMII) अणु
		अगर (dwmac->ext_phyclk) अणु
			src = TX_RETIME_SRC_PHYCLK;
		पूर्ण अन्यथा अणु
			src = TX_RETIME_SRC_CLKGEN;
			freq = DWMAC_50MHZ;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_PHY_IF_MODE_RGMII(dwmac->पूर्णांकerface)) अणु
		/* On GiGa clk source can be either ext or from clkgen */
		अगर (spd == SPEED_1000) अणु
			freq = DWMAC_125MHZ;
		पूर्ण अन्यथा अणु
			/* Switch to clkgen क्रम these speeds */
			src = TX_RETIME_SRC_CLKGEN;
			अगर (spd == SPEED_100)
				freq = DWMAC_25MHZ;
			अन्यथा अगर (spd == SPEED_10)
				freq = DWMAC_2_5MHZ;
		पूर्ण
	पूर्ण

	अगर (src == TX_RETIME_SRC_CLKGEN && freq)
		clk_set_rate(dwmac->clk, freq);

	regmap_update_bits(dwmac->regmap, reg, STIH4XX_RETIME_SRC_MASK,
			   stih4xx_tx_reसमय_val[src]);
पूर्ण

अटल व्योम stid127_fix_reसमय_src(व्योम *priv, u32 spd)
अणु
	काष्ठा sti_dwmac *dwmac = priv;
	u32 reg = dwmac->ctrl_reg;
	u32 freq = 0;
	u32 val = 0;

	अगर (dwmac->पूर्णांकerface == PHY_INTERFACE_MODE_MII) अणु
		val = STID127_ETH_SEL_INTERNAL_NOTEXT_TXCLK;
	पूर्ण अन्यथा अगर (dwmac->पूर्णांकerface == PHY_INTERFACE_MODE_RMII) अणु
		अगर (!dwmac->ext_phyclk) अणु
			val = STID127_ETH_SEL_INTERNAL_NOTEXT_PHYCLK;
			freq = DWMAC_50MHZ;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_PHY_IF_MODE_RGMII(dwmac->पूर्णांकerface)) अणु
		val = STID127_ETH_SEL_INTERNAL_NOTEXT_TXCLK;
		अगर (spd == SPEED_1000)
			freq = DWMAC_125MHZ;
		अन्यथा अगर (spd == SPEED_100)
			freq = DWMAC_25MHZ;
		अन्यथा अगर (spd == SPEED_10)
			freq = DWMAC_2_5MHZ;
	पूर्ण

	अगर (freq)
		clk_set_rate(dwmac->clk, freq);

	regmap_update_bits(dwmac->regmap, reg, STID127_RETIME_SRC_MASK, val);
पूर्ण

अटल पूर्णांक sti_dwmac_set_mode(काष्ठा sti_dwmac *dwmac)
अणु
	काष्ठा regmap *regmap = dwmac->regmap;
	पूर्णांक अगरace = dwmac->पूर्णांकerface;
	u32 reg = dwmac->ctrl_reg;
	u32 val;

	अगर (dwmac->gmac_en)
		regmap_update_bits(regmap, reg, EN_MASK, EN);

	regmap_update_bits(regmap, reg, MII_PHY_SEL_MASK, phy_पूर्णांकf_sels[अगरace]);

	val = (अगरace == PHY_INTERFACE_MODE_REVMII) ? 0 : ENMII;
	regmap_update_bits(regmap, reg, ENMII_MASK, val);

	dwmac->fix_reसमय_src(dwmac, dwmac->speed);

	वापस 0;
पूर्ण

अटल पूर्णांक sti_dwmac_parse_data(काष्ठा sti_dwmac *dwmac,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *regmap;
	पूर्णांक err;

	/* clk selection from extra syscfg रेजिस्टर */
	dwmac->clk_sel_reg = -ENXIO;
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "sti-clkconf");
	अगर (res)
		dwmac->clk_sel_reg = res->start;

	regmap = syscon_regmap_lookup_by_phandle(np, "st,syscon");
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	err = of_property_पढ़ो_u32_index(np, "st,syscon", 1, &dwmac->ctrl_reg);
	अगर (err) अणु
		dev_err(dev, "Can't get sysconfig ctrl offset (%d)\n", err);
		वापस err;
	पूर्ण

	err = of_get_phy_mode(np, &dwmac->पूर्णांकerface);
	अगर (err && err != -ENODEV) अणु
		dev_err(dev, "Can't get phy-mode\n");
		वापस err;
	पूर्ण

	dwmac->regmap = regmap;
	dwmac->gmac_en = of_property_पढ़ो_bool(np, "st,gmac_en");
	dwmac->ext_phyclk = of_property_पढ़ो_bool(np, "st,ext-phyclk");
	dwmac->tx_reसमय_src = TX_RETIME_SRC_NA;
	dwmac->speed = SPEED_100;

	अगर (IS_PHY_IF_MODE_GBIT(dwmac->पूर्णांकerface)) अणु
		स्थिर अक्षर *rs;

		dwmac->tx_reसमय_src = TX_RETIME_SRC_CLKGEN;

		err = of_property_पढ़ो_string(np, "st,tx-retime-src", &rs);
		अगर (err < 0) अणु
			dev_warn(dev, "Use internal clock source\n");
		पूर्ण अन्यथा अणु
			अगर (!strहालcmp(rs, "clk_125"))
				dwmac->tx_reसमय_src = TX_RETIME_SRC_CLK_125;
			अन्यथा अगर (!strहालcmp(rs, "txclk"))
				dwmac->tx_reसमय_src = TX_RETIME_SRC_TXCLK;
		पूर्ण
		dwmac->speed = SPEED_1000;
	पूर्ण

	dwmac->clk = devm_clk_get(dev, "sti-ethclk");
	अगर (IS_ERR(dwmac->clk)) अणु
		dev_warn(dev, "No phy clock provided...\n");
		dwmac->clk = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sti_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	स्थिर काष्ठा sti_dwmac_of_data *data;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा sti_dwmac *dwmac;
	पूर्णांक ret;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "No OF match data provided\n");
		वापस -EINVAL;
	पूर्ण

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

	ret = sti_dwmac_parse_data(dwmac, pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to parse OF data\n");
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->fix_reसमय_src = data->fix_reसमय_src;

	plat_dat->bsp_priv = dwmac;
	plat_dat->fix_mac_speed = data->fix_reसमय_src;

	ret = clk_prepare_enable(dwmac->clk);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = sti_dwmac_set_mode(dwmac);
	अगर (ret)
		जाओ disable_clk;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ disable_clk;

	वापस 0;

disable_clk:
	clk_disable_unprepare(dwmac->clk);
err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक sti_dwmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sti_dwmac *dwmac = get_sपंचांगmac_bsp_priv(&pdev->dev);
	पूर्णांक ret = sपंचांगmac_dvr_हटाओ(&pdev->dev);

	clk_disable_unprepare(dwmac->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sti_dwmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा sti_dwmac *dwmac = get_sपंचांगmac_bsp_priv(dev);
	पूर्णांक ret = sपंचांगmac_suspend(dev);

	clk_disable_unprepare(dwmac->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sti_dwmac_resume(काष्ठा device *dev)
अणु
	काष्ठा sti_dwmac *dwmac = get_sपंचांगmac_bsp_priv(dev);

	clk_prepare_enable(dwmac->clk);
	sti_dwmac_set_mode(dwmac);

	वापस sपंचांगmac_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(sti_dwmac_pm_ops, sti_dwmac_suspend,
					   sti_dwmac_resume);

अटल स्थिर काष्ठा sti_dwmac_of_data stih4xx_dwmac_data = अणु
	.fix_reसमय_src = stih4xx_fix_reसमय_src,
पूर्ण;

अटल स्थिर काष्ठा sti_dwmac_of_data stid127_dwmac_data = अणु
	.fix_reसमय_src = stid127_fix_reसमय_src,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sti_dwmac_match[] = अणु
	अणु .compatible = "st,stih415-dwmac", .data = &stih4xx_dwmac_dataपूर्ण,
	अणु .compatible = "st,stih416-dwmac", .data = &stih4xx_dwmac_dataपूर्ण,
	अणु .compatible = "st,stid127-dwmac", .data = &stid127_dwmac_dataपूर्ण,
	अणु .compatible = "st,stih407-dwmac", .data = &stih4xx_dwmac_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sti_dwmac_match);

अटल काष्ठा platक्रमm_driver sti_dwmac_driver = अणु
	.probe  = sti_dwmac_probe,
	.हटाओ = sti_dwmac_हटाओ,
	.driver = अणु
		.name           = "sti-dwmac",
		.pm		= &sti_dwmac_pm_ops,
		.of_match_table = sti_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sti_dwmac_driver);

MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@st.com>");
MODULE_DESCRIPTION("STMicroelectronics DWMAC Specific Glue layer");
MODULE_LICENSE("GPL");
