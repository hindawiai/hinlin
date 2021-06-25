<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

/* Peri Configuration रेजिस्टर क्रम mt2712 */
#घोषणा PERI_ETH_PHY_INTF_SEL	0x418
#घोषणा PHY_INTF_MII		0
#घोषणा PHY_INTF_RGMII		1
#घोषणा PHY_INTF_RMII		4
#घोषणा RMII_CLK_SRC_RXC	BIT(4)
#घोषणा RMII_CLK_SRC_INTERNAL	BIT(5)

#घोषणा PERI_ETH_DLY	0x428
#घोषणा ETH_DLY_GTXC_INV	BIT(6)
#घोषणा ETH_DLY_GTXC_ENABLE	BIT(5)
#घोषणा ETH_DLY_GTXC_STAGES	GENMASK(4, 0)
#घोषणा ETH_DLY_TXC_INV		BIT(20)
#घोषणा ETH_DLY_TXC_ENABLE	BIT(19)
#घोषणा ETH_DLY_TXC_STAGES	GENMASK(18, 14)
#घोषणा ETH_DLY_RXC_INV		BIT(13)
#घोषणा ETH_DLY_RXC_ENABLE	BIT(12)
#घोषणा ETH_DLY_RXC_STAGES	GENMASK(11, 7)

#घोषणा PERI_ETH_DLY_FINE	0x800
#घोषणा ETH_RMII_DLY_TX_INV	BIT(2)
#घोषणा ETH_FINE_DLY_GTXC	BIT(1)
#घोषणा ETH_FINE_DLY_RXC	BIT(0)

काष्ठा mac_delay_काष्ठा अणु
	u32 tx_delay;
	u32 rx_delay;
	bool tx_inv;
	bool rx_inv;
पूर्ण;

काष्ठा mediatek_dwmac_plat_data अणु
	स्थिर काष्ठा mediatek_dwmac_variant *variant;
	काष्ठा mac_delay_काष्ठा mac_delay;
	काष्ठा clk_bulk_data *clks;
	काष्ठा device_node *np;
	काष्ठा regmap *peri_regmap;
	काष्ठा device *dev;
	phy_पूर्णांकerface_t phy_mode;
	पूर्णांक num_clks_to_config;
	bool rmii_clk_from_mac;
	bool rmii_rxc;
पूर्ण;

काष्ठा mediatek_dwmac_variant अणु
	पूर्णांक (*dwmac_set_phy_पूर्णांकerface)(काष्ठा mediatek_dwmac_plat_data *plat);
	पूर्णांक (*dwmac_set_delay)(काष्ठा mediatek_dwmac_plat_data *plat);

	/* घड़ी ids to be requested */
	स्थिर अक्षर * स्थिर *clk_list;
	पूर्णांक num_clks;

	u32 dma_bit_mask;
	u32 rx_delay_max;
	u32 tx_delay_max;
पूर्ण;

/* list of घड़ीs required क्रम mac */
अटल स्थिर अक्षर * स्थिर mt2712_dwmac_clk_l[] = अणु
	"axi", "apb", "mac_main", "ptp_ref", "rmii_internal"
पूर्ण;

अटल पूर्णांक mt2712_set_पूर्णांकerface(काष्ठा mediatek_dwmac_plat_data *plat)
अणु
	पूर्णांक rmii_clk_from_mac = plat->rmii_clk_from_mac ? RMII_CLK_SRC_INTERNAL : 0;
	पूर्णांक rmii_rxc = plat->rmii_rxc ? RMII_CLK_SRC_RXC : 0;
	u32 पूर्णांकf_val = 0;

	/* The घड़ी labeled as "rmii_internal" in mt2712_dwmac_clk_l is needed
	 * only in RMII(when MAC provides the reference घड़ी), and useless क्रम
	 * RGMII/MII/RMII(when PHY provides the reference घड़ी).
	 * num_clks_to_config indicates the real number of घड़ीs should be
	 * configured, equals to (plat->variant->num_clks - 1) in शेष क्रम all the हाल,
	 * then +1 क्रम rmii_clk_from_mac हाल.
	 */
	plat->num_clks_to_config = plat->variant->num_clks - 1;

	/* select phy पूर्णांकerface in top control करोमुख्य */
	चयन (plat->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_MII:
		पूर्णांकf_val |= PHY_INTF_MII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		अगर (plat->rmii_clk_from_mac)
			plat->num_clks_to_config++;
		पूर्णांकf_val |= (PHY_INTF_RMII | rmii_rxc | rmii_clk_from_mac);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		पूर्णांकf_val |= PHY_INTF_RGMII;
		अवरोध;
	शेष:
		dev_err(plat->dev, "phy interface not supported\n");
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(plat->peri_regmap, PERI_ETH_PHY_INTF_SEL, पूर्णांकf_val);

	वापस 0;
पूर्ण

अटल व्योम mt2712_delay_ps2stage(काष्ठा mediatek_dwmac_plat_data *plat)
अणु
	काष्ठा mac_delay_काष्ठा *mac_delay = &plat->mac_delay;

	चयन (plat->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_RMII:
		/* 550ps per stage क्रम MII/RMII */
		mac_delay->tx_delay /= 550;
		mac_delay->rx_delay /= 550;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		/* 170ps per stage क्रम RGMII */
		mac_delay->tx_delay /= 170;
		mac_delay->rx_delay /= 170;
		अवरोध;
	शेष:
		dev_err(plat->dev, "phy interface not supported\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt2712_delay_stage2ps(काष्ठा mediatek_dwmac_plat_data *plat)
अणु
	काष्ठा mac_delay_काष्ठा *mac_delay = &plat->mac_delay;

	चयन (plat->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_RMII:
		/* 550ps per stage क्रम MII/RMII */
		mac_delay->tx_delay *= 550;
		mac_delay->rx_delay *= 550;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		/* 170ps per stage क्रम RGMII */
		mac_delay->tx_delay *= 170;
		mac_delay->rx_delay *= 170;
		अवरोध;
	शेष:
		dev_err(plat->dev, "phy interface not supported\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mt2712_set_delay(काष्ठा mediatek_dwmac_plat_data *plat)
अणु
	काष्ठा mac_delay_काष्ठा *mac_delay = &plat->mac_delay;
	u32 delay_val = 0, fine_val = 0;

	mt2712_delay_ps2stage(plat);

	चयन (plat->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_MII:
		delay_val |= FIELD_PREP(ETH_DLY_TXC_ENABLE, !!mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_TXC_STAGES, mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_TXC_INV, mac_delay->tx_inv);

		delay_val |= FIELD_PREP(ETH_DLY_RXC_ENABLE, !!mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_STAGES, mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_INV, mac_delay->rx_inv);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		अगर (plat->rmii_clk_from_mac) अणु
			/* हाल 1: mac provides the rmii reference घड़ी,
			 * and the घड़ी output to TXC pin.
			 * The egress timing can be adjusted by GTXC delay macro circuit.
			 * The ingress timing can be adjusted by TXC delay macro circuit.
			 */
			delay_val |= FIELD_PREP(ETH_DLY_TXC_ENABLE, !!mac_delay->rx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_TXC_STAGES, mac_delay->rx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_TXC_INV, mac_delay->rx_inv);

			delay_val |= FIELD_PREP(ETH_DLY_GTXC_ENABLE, !!mac_delay->tx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_GTXC_STAGES, mac_delay->tx_delay);
			delay_val |= FIELD_PREP(ETH_DLY_GTXC_INV, mac_delay->tx_inv);
		पूर्ण अन्यथा अणु
			/* हाल 2: the rmii reference घड़ी is from बाह्यal phy,
			 * and the property "rmii_rxc" indicates which pin(TXC/RXC)
			 * the reference clk is connected to. The reference घड़ी is a
			 * received संकेत, so rx_delay/rx_inv are used to indicate
			 * the reference घड़ी timing adjusपंचांगent
			 */
			अगर (plat->rmii_rxc) अणु
				/* the rmii reference घड़ी from outside is connected
				 * to RXC pin, the reference घड़ी will be adjusted
				 * by RXC delay macro circuit.
				 */
				delay_val |= FIELD_PREP(ETH_DLY_RXC_ENABLE, !!mac_delay->rx_delay);
				delay_val |= FIELD_PREP(ETH_DLY_RXC_STAGES, mac_delay->rx_delay);
				delay_val |= FIELD_PREP(ETH_DLY_RXC_INV, mac_delay->rx_inv);
			पूर्ण अन्यथा अणु
				/* the rmii reference घड़ी from outside is connected
				 * to TXC pin, the reference घड़ी will be adjusted
				 * by TXC delay macro circuit.
				 */
				delay_val |= FIELD_PREP(ETH_DLY_TXC_ENABLE, !!mac_delay->rx_delay);
				delay_val |= FIELD_PREP(ETH_DLY_TXC_STAGES, mac_delay->rx_delay);
				delay_val |= FIELD_PREP(ETH_DLY_TXC_INV, mac_delay->rx_inv);
			पूर्ण
			/* tx_inv will inverse the tx घड़ी inside mac relateive to
			 * reference घड़ी from बाह्यal phy,
			 * and this bit is located in the same रेजिस्टर with fine-tune
			 */
			अगर (mac_delay->tx_inv)
				fine_val = ETH_RMII_DLY_TX_INV;
		पूर्ण
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		fine_val = ETH_FINE_DLY_GTXC | ETH_FINE_DLY_RXC;

		delay_val |= FIELD_PREP(ETH_DLY_GTXC_ENABLE, !!mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_GTXC_STAGES, mac_delay->tx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_GTXC_INV, mac_delay->tx_inv);

		delay_val |= FIELD_PREP(ETH_DLY_RXC_ENABLE, !!mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_STAGES, mac_delay->rx_delay);
		delay_val |= FIELD_PREP(ETH_DLY_RXC_INV, mac_delay->rx_inv);
		अवरोध;
	शेष:
		dev_err(plat->dev, "phy interface not supported\n");
		वापस -EINVAL;
	पूर्ण
	regmap_ग_लिखो(plat->peri_regmap, PERI_ETH_DLY, delay_val);
	regmap_ग_लिखो(plat->peri_regmap, PERI_ETH_DLY_FINE, fine_val);

	mt2712_delay_stage2ps(plat);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mediatek_dwmac_variant mt2712_gmac_variant = अणु
		.dwmac_set_phy_पूर्णांकerface = mt2712_set_पूर्णांकerface,
		.dwmac_set_delay = mt2712_set_delay,
		.clk_list = mt2712_dwmac_clk_l,
		.num_clks = ARRAY_SIZE(mt2712_dwmac_clk_l),
		.dma_bit_mask = 33,
		.rx_delay_max = 17600,
		.tx_delay_max = 17600,
पूर्ण;

अटल पूर्णांक mediatek_dwmac_config_dt(काष्ठा mediatek_dwmac_plat_data *plat)
अणु
	काष्ठा mac_delay_काष्ठा *mac_delay = &plat->mac_delay;
	u32 tx_delay_ps, rx_delay_ps;
	पूर्णांक err;

	plat->peri_regmap = syscon_regmap_lookup_by_phandle(plat->np, "mediatek,pericfg");
	अगर (IS_ERR(plat->peri_regmap)) अणु
		dev_err(plat->dev, "Failed to get pericfg syscon\n");
		वापस PTR_ERR(plat->peri_regmap);
	पूर्ण

	err = of_get_phy_mode(plat->np, &plat->phy_mode);
	अगर (err) अणु
		dev_err(plat->dev, "not find phy-mode\n");
		वापस err;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(plat->np, "mediatek,tx-delay-ps", &tx_delay_ps)) अणु
		अगर (tx_delay_ps < plat->variant->tx_delay_max) अणु
			mac_delay->tx_delay = tx_delay_ps;
		पूर्ण अन्यथा अणु
			dev_err(plat->dev, "Invalid TX clock delay: %dps\n", tx_delay_ps);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(plat->np, "mediatek,rx-delay-ps", &rx_delay_ps)) अणु
		अगर (rx_delay_ps < plat->variant->rx_delay_max) अणु
			mac_delay->rx_delay = rx_delay_ps;
		पूर्ण अन्यथा अणु
			dev_err(plat->dev, "Invalid RX clock delay: %dps\n", rx_delay_ps);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mac_delay->tx_inv = of_property_पढ़ो_bool(plat->np, "mediatek,txc-inverse");
	mac_delay->rx_inv = of_property_पढ़ो_bool(plat->np, "mediatek,rxc-inverse");
	plat->rmii_rxc = of_property_पढ़ो_bool(plat->np, "mediatek,rmii-rxc");
	plat->rmii_clk_from_mac = of_property_पढ़ो_bool(plat->np, "mediatek,rmii-clk-from-mac");

	वापस 0;
पूर्ण

अटल पूर्णांक mediatek_dwmac_clk_init(काष्ठा mediatek_dwmac_plat_data *plat)
अणु
	स्थिर काष्ठा mediatek_dwmac_variant *variant = plat->variant;
	पूर्णांक i, num = variant->num_clks;

	plat->clks = devm_kसुस्मृति(plat->dev, num, माप(*plat->clks), GFP_KERNEL);
	अगर (!plat->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++)
		plat->clks[i].id = variant->clk_list[i];

	plat->num_clks_to_config = variant->num_clks;

	वापस devm_clk_bulk_get(plat->dev, num, plat->clks);
पूर्ण

अटल पूर्णांक mediatek_dwmac_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा mediatek_dwmac_plat_data *plat = priv;
	स्थिर काष्ठा mediatek_dwmac_variant *variant = plat->variant;
	पूर्णांक ret;

	ret = dma_set_mask_and_coherent(plat->dev, DMA_BIT_MASK(variant->dma_bit_mask));
	अगर (ret) अणु
		dev_err(plat->dev, "No suitable DMA available, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = variant->dwmac_set_phy_पूर्णांकerface(plat);
	अगर (ret) अणु
		dev_err(plat->dev, "failed to set phy interface, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = variant->dwmac_set_delay(plat);
	अगर (ret) अणु
		dev_err(plat->dev, "failed to set delay value, err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(plat->num_clks_to_config, plat->clks);
	अगर (ret) अणु
		dev_err(plat->dev, "failed to enable clks, err = %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम mediatek_dwmac_निकास(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा mediatek_dwmac_plat_data *plat = priv;

	clk_bulk_disable_unprepare(plat->num_clks_to_config, plat->clks);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
पूर्ण

अटल पूर्णांक mediatek_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mediatek_dwmac_plat_data *priv_plat;
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	पूर्णांक ret;

	priv_plat = devm_kzalloc(&pdev->dev, माप(*priv_plat), GFP_KERNEL);
	अगर (!priv_plat)
		वापस -ENOMEM;

	priv_plat->variant = of_device_get_match_data(&pdev->dev);
	अगर (!priv_plat->variant) अणु
		dev_err(&pdev->dev, "Missing dwmac-mediatek variant\n");
		वापस -EINVAL;
	पूर्ण

	priv_plat->dev = &pdev->dev;
	priv_plat->np = pdev->dev.of_node;

	ret = mediatek_dwmac_config_dt(priv_plat);
	अगर (ret)
		वापस ret;

	ret = mediatek_dwmac_clk_init(priv_plat);
	अगर (ret)
		वापस ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	plat_dat->पूर्णांकerface = priv_plat->phy_mode;
	plat_dat->has_gmac4 = 1;
	plat_dat->has_gmac = 0;
	plat_dat->pmt = 0;
	plat_dat->riwt_off = 1;
	plat_dat->maxmtu = ETH_DATA_LEN;
	plat_dat->bsp_priv = priv_plat;
	plat_dat->init = mediatek_dwmac_init;
	plat_dat->निकास = mediatek_dwmac_निकास;
	mediatek_dwmac_init(pdev, priv_plat);

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret) अणु
		sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mediatek_dwmac_match[] = अणु
	अणु .compatible = "mediatek,mt2712-gmac",
	  .data = &mt2712_gmac_variant पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, mediatek_dwmac_match);

अटल काष्ठा platक्रमm_driver mediatek_dwmac_driver = अणु
	.probe  = mediatek_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "dwmac-mediatek",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = mediatek_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mediatek_dwmac_driver);

MODULE_AUTHOR("Biao Huang <biao.huang@mediatek.com>");
MODULE_DESCRIPTION("MediaTek DWMAC specific glue layer");
MODULE_LICENSE("GPL v2");
