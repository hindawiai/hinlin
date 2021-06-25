<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Toshiba Visconti Ethernet Support
 *
 * (C) Copyright 2020 TOSHIBA CORPORATION
 * (C) Copyright 2020 Toshiba Electronic Devices & Storage Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"
#समावेश "dwmac4.h"

#घोषणा REG_ETHER_CONTROL	0x52D4
#घोषणा ETHER_ETH_CONTROL_RESET BIT(17)

#घोषणा REG_ETHER_CLOCK_SEL	0x52D0
#घोषणा ETHER_CLK_SEL_TX_CLK_EN BIT(0)
#घोषणा ETHER_CLK_SEL_RX_CLK_EN BIT(1)
#घोषणा ETHER_CLK_SEL_RMII_CLK_EN BIT(2)
#घोषणा ETHER_CLK_SEL_RMII_CLK_RST BIT(3)
#घोषणा ETHER_CLK_SEL_DIV_SEL_2 BIT(4)
#घोषणा ETHER_CLK_SEL_DIV_SEL_20 BIT(0)
#घोषणा ETHER_CLK_SEL_FREQ_SEL_125M	(BIT(9) | BIT(8))
#घोषणा ETHER_CLK_SEL_FREQ_SEL_50M	BIT(9)
#घोषणा ETHER_CLK_SEL_FREQ_SEL_25M	BIT(8)
#घोषणा ETHER_CLK_SEL_FREQ_SEL_2P5M	BIT(0)
#घोषणा ETHER_CLK_SEL_TX_CLK_EXT_SEL_IN BIT(0)
#घोषणा ETHER_CLK_SEL_TX_CLK_EXT_SEL_TXC BIT(10)
#घोषणा ETHER_CLK_SEL_TX_CLK_EXT_SEL_DIV BIT(11)
#घोषणा ETHER_CLK_SEL_RX_CLK_EXT_SEL_IN  BIT(0)
#घोषणा ETHER_CLK_SEL_RX_CLK_EXT_SEL_RXC BIT(12)
#घोषणा ETHER_CLK_SEL_RX_CLK_EXT_SEL_DIV BIT(13)
#घोषणा ETHER_CLK_SEL_TX_CLK_O_TX_I	 BIT(0)
#घोषणा ETHER_CLK_SEL_TX_CLK_O_RMII_I	 BIT(14)
#घोषणा ETHER_CLK_SEL_TX_O_E_N_IN	 BIT(15)
#घोषणा ETHER_CLK_SEL_RMII_CLK_SEL_IN	 BIT(0)
#घोषणा ETHER_CLK_SEL_RMII_CLK_SEL_RX_C	 BIT(16)

#घोषणा ETHER_CLK_SEL_RX_TX_CLK_EN (ETHER_CLK_SEL_RX_CLK_EN | ETHER_CLK_SEL_TX_CLK_EN)

#घोषणा ETHER_CONFIG_INTF_MII 0
#घोषणा ETHER_CONFIG_INTF_RGMII BIT(0)
#घोषणा ETHER_CONFIG_INTF_RMII BIT(2)

काष्ठा visconti_eth अणु
	व्योम __iomem *reg;
	u32 phy_पूर्णांकf_sel;
	काष्ठा clk *phy_ref_clk;
	spinlock_t lock; /* lock to protect रेजिस्टर update */
पूर्ण;

अटल व्योम visconti_eth_fix_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा visconti_eth *dwmac = priv;
	अचिन्हित पूर्णांक val, clk_sel_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dwmac->lock, flags);

	/* adjust link */
	val = पढ़ोl(dwmac->reg + MAC_CTRL_REG);
	val &= ~(GMAC_CONFIG_PS | GMAC_CONFIG_FES);

	चयन (speed) अणु
	हाल SPEED_1000:
		अगर (dwmac->phy_पूर्णांकf_sel == ETHER_CONFIG_INTF_RGMII)
			clk_sel_val = ETHER_CLK_SEL_FREQ_SEL_125M;
		अवरोध;
	हाल SPEED_100:
		अगर (dwmac->phy_पूर्णांकf_sel == ETHER_CONFIG_INTF_RGMII)
			clk_sel_val = ETHER_CLK_SEL_FREQ_SEL_25M;
		अगर (dwmac->phy_पूर्णांकf_sel == ETHER_CONFIG_INTF_RMII)
			clk_sel_val = ETHER_CLK_SEL_DIV_SEL_2;
		val |= GMAC_CONFIG_PS | GMAC_CONFIG_FES;
		अवरोध;
	हाल SPEED_10:
		अगर (dwmac->phy_पूर्णांकf_sel == ETHER_CONFIG_INTF_RGMII)
			clk_sel_val = ETHER_CLK_SEL_FREQ_SEL_2P5M;
		अगर (dwmac->phy_पूर्णांकf_sel == ETHER_CONFIG_INTF_RMII)
			clk_sel_val = ETHER_CLK_SEL_DIV_SEL_20;
		val |= GMAC_CONFIG_PS;
		अवरोध;
	शेष:
		/* No bit control */
		अवरोध;
	पूर्ण

	ग_लिखोl(val, dwmac->reg + MAC_CTRL_REG);

	/* Stop पूर्णांकernal घड़ी */
	val = पढ़ोl(dwmac->reg + REG_ETHER_CLOCK_SEL);
	val &= ~(ETHER_CLK_SEL_RMII_CLK_EN | ETHER_CLK_SEL_RX_TX_CLK_EN);
	val |= ETHER_CLK_SEL_TX_O_E_N_IN;
	ग_लिखोl(val, dwmac->reg + REG_ETHER_CLOCK_SEL);

	चयन (dwmac->phy_पूर्णांकf_sel) अणु
	हाल ETHER_CONFIG_INTF_RGMII:
		val = clk_sel_val | ETHER_CLK_SEL_RX_CLK_EXT_SEL_RXC;
		अवरोध;
	हाल ETHER_CONFIG_INTF_RMII:
		val = clk_sel_val | ETHER_CLK_SEL_RX_CLK_EXT_SEL_DIV |
			ETHER_CLK_SEL_TX_CLK_EXT_SEL_TXC | ETHER_CLK_SEL_TX_O_E_N_IN |
			ETHER_CLK_SEL_RMII_CLK_SEL_RX_C;
		अवरोध;
	हाल ETHER_CONFIG_INTF_MII:
	शेष:
		val = clk_sel_val | ETHER_CLK_SEL_RX_CLK_EXT_SEL_RXC |
			ETHER_CLK_SEL_TX_CLK_EXT_SEL_DIV | ETHER_CLK_SEL_TX_O_E_N_IN |
			ETHER_CLK_SEL_RMII_CLK_EN;
		अवरोध;
	पूर्ण

	/* Start घड़ी */
	ग_लिखोl(val, dwmac->reg + REG_ETHER_CLOCK_SEL);
	val |= ETHER_CLK_SEL_RX_TX_CLK_EN;
	ग_लिखोl(val, dwmac->reg + REG_ETHER_CLOCK_SEL);

	val &= ~ETHER_CLK_SEL_TX_O_E_N_IN;
	ग_लिखोl(val, dwmac->reg + REG_ETHER_CLOCK_SEL);

	spin_unlock_irqrestore(&dwmac->lock, flags);
पूर्ण

अटल पूर्णांक visconti_eth_init_hw(काष्ठा platक्रमm_device *pdev, काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा visconti_eth *dwmac = plat_dat->bsp_priv;
	अचिन्हित पूर्णांक reg_val, clk_sel_val;

	चयन (plat_dat->phy_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		dwmac->phy_पूर्णांकf_sel = ETHER_CONFIG_INTF_RGMII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		dwmac->phy_पूर्णांकf_sel = ETHER_CONFIG_INTF_MII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		dwmac->phy_पूर्णांकf_sel = ETHER_CONFIG_INTF_RMII;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported phy-mode (%d)\n", plat_dat->phy_पूर्णांकerface);
		वापस -EOPNOTSUPP;
	पूर्ण

	reg_val = dwmac->phy_पूर्णांकf_sel;
	ग_लिखोl(reg_val, dwmac->reg + REG_ETHER_CONTROL);

	/* Enable TX/RX घड़ी */
	clk_sel_val = ETHER_CLK_SEL_FREQ_SEL_125M;
	ग_लिखोl(clk_sel_val, dwmac->reg + REG_ETHER_CLOCK_SEL);

	ग_लिखोl((clk_sel_val | ETHER_CLK_SEL_RMII_CLK_EN | ETHER_CLK_SEL_RX_TX_CLK_EN),
	       dwmac->reg + REG_ETHER_CLOCK_SEL);

	/* release पूर्णांकernal-reset */
	reg_val |= ETHER_ETH_CONTROL_RESET;
	ग_लिखोl(reg_val, dwmac->reg + REG_ETHER_CONTROL);

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_eth_घड़ी_probe(काष्ठा platक्रमm_device *pdev,
				    काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा visconti_eth *dwmac = plat_dat->bsp_priv;
	पूर्णांक err;

	dwmac->phy_ref_clk = devm_clk_get(&pdev->dev, "phy_ref_clk");
	अगर (IS_ERR(dwmac->phy_ref_clk)) अणु
		dev_err(&pdev->dev, "phy_ref_clk clock not found.\n");
		वापस PTR_ERR(dwmac->phy_ref_clk);
	पूर्ण

	err = clk_prepare_enable(dwmac->phy_ref_clk);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable phy_ref clock: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_eth_घड़ी_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा visconti_eth *dwmac = get_sपंचांगmac_bsp_priv(&pdev->dev);
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	clk_disable_unprepare(dwmac->phy_ref_clk);
	clk_disable_unprepare(priv->plat->sपंचांगmac_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_eth_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा visconti_eth *dwmac;
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
		जाओ हटाओ_config;
	पूर्ण

	spin_lock_init(&dwmac->lock);
	dwmac->reg = sपंचांगmac_res.addr;
	plat_dat->bsp_priv = dwmac;
	plat_dat->fix_mac_speed = visconti_eth_fix_mac_speed;

	ret = visconti_eth_घड़ी_probe(pdev, plat_dat);
	अगर (ret)
		जाओ हटाओ_config;

	visconti_eth_init_hw(pdev, plat_dat);

	plat_dat->dma_cfg->aal = 1;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ हटाओ;

	वापस ret;

हटाओ:
	visconti_eth_घड़ी_हटाओ(pdev);
हटाओ_config:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक visconti_eth_dwmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	err = sपंचांगmac_pltfr_हटाओ(pdev);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to remove platform: %d\n", err);

	err = visconti_eth_घड़ी_हटाओ(pdev);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to remove clock: %d\n", err);

	sपंचांगmac_हटाओ_config_dt(pdev, priv->plat);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id visconti_eth_dwmac_match[] = अणु
	अणु .compatible = "toshiba,visconti-dwmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, visconti_eth_dwmac_match);

अटल काष्ठा platक्रमm_driver visconti_eth_dwmac_driver = अणु
	.probe  = visconti_eth_dwmac_probe,
	.हटाओ = visconti_eth_dwmac_हटाओ,
	.driver = अणु
		.name           = "visconti-eth-dwmac",
		.of_match_table = visconti_eth_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(visconti_eth_dwmac_driver);

MODULE_AUTHOR("Toshiba");
MODULE_DESCRIPTION("Toshiba Visconti Ethernet DWMAC glue driver");
MODULE_AUTHOR("Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp");
MODULE_LICENSE("GPL v2");
