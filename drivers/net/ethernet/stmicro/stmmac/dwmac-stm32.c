<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dwmac-sपंचांग32.c - DWMAC Specअगरic Glue layer क्रम STM32 MCU
 *
 * Copyright (C) STMicroelectronics SA 2017
 * Author:  Alexandre Torgue <alexandre.torgue@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"

#घोषणा SYSCFG_MCU_ETH_MASK		BIT(23)
#घोषणा SYSCFG_MP1_ETH_MASK		GENMASK(23, 16)
#घोषणा SYSCFG_PMCCLRR_OFFSET		0x40

#घोषणा SYSCFG_PMCR_ETH_CLK_SEL		BIT(16)
#घोषणा SYSCFG_PMCR_ETH_REF_CLK_SEL	BIT(17)

/* CLOCK feed to PHY*/
#घोषणा ETH_CK_F_25M	25000000
#घोषणा ETH_CK_F_50M	50000000
#घोषणा ETH_CK_F_125M	125000000

/*  Ethernet PHY पूर्णांकerface selection in रेजिस्टर SYSCFG Configuration
 *------------------------------------------
 * src	 |BIT(23)| BIT(22)| BIT(21)|BIT(20)|
 *------------------------------------------
 * MII   |   0	 |   0	  |   0    |   1   |
 *------------------------------------------
 * GMII  |   0	 |   0	  |   0    |   0   |
 *------------------------------------------
 * RGMII |   0	 |   0	  |   1	   |  n/a  |
 *------------------------------------------
 * RMII  |   1	 |   0	  |   0	   |  n/a  |
 *------------------------------------------
 */
#घोषणा SYSCFG_PMCR_ETH_SEL_MII		BIT(20)
#घोषणा SYSCFG_PMCR_ETH_SEL_RGMII	BIT(21)
#घोषणा SYSCFG_PMCR_ETH_SEL_RMII	BIT(23)
#घोषणा SYSCFG_PMCR_ETH_SEL_GMII	0
#घोषणा SYSCFG_MCU_ETH_SEL_MII		0
#घोषणा SYSCFG_MCU_ETH_SEL_RMII		1

/* STM32MP1 रेजिस्टर definitions
 *
 * Below table summarizes the घड़ी requirement and घड़ी sources क्रम
 * supported phy पूर्णांकerface modes.
 * __________________________________________________________________________
 *|PHY_MODE | Normal | PHY wo crystal|   PHY wo crystal   |No 125Mhz from PHY|
 *|         |        |      25MHz    |        50MHz       |                  |
 * ---------------------------------------------------------------------------
 *|  MII    |	 -   |     eth-ck    |	      n/a	  |	  n/a        |
 *|         |        | st,ext-phyclk |                    |		     |
 * ---------------------------------------------------------------------------
 *|  GMII   |	 -   |     eth-ck    |	      n/a	  |	  n/a        |
 *|         |        | st,ext-phyclk |                    |		     |
 * ---------------------------------------------------------------------------
 *| RGMII   |	 -   |     eth-ck    |	      n/a	  |      eth-ck      |
 *|         |        | st,ext-phyclk |                    | st,eth-clk-sel or|
 *|         |        |               |                    | st,ext-phyclk    |
 * ---------------------------------------------------------------------------
 *| RMII    |	 -   |     eth-ck    |	    eth-ck        |	  n/a        |
 *|         |        | st,ext-phyclk | st,eth-ref-clk-sel |		     |
 *|         |        |               | or st,ext-phyclk   |		     |
 * ---------------------------------------------------------------------------
 *
 */

काष्ठा sपंचांग32_dwmac अणु
	काष्ठा clk *clk_tx;
	काष्ठा clk *clk_rx;
	काष्ठा clk *clk_eth_ck;
	काष्ठा clk *clk_ethstp;
	काष्ठा clk *syscfg_clk;
	पूर्णांक ext_phyclk;
	पूर्णांक enable_eth_ck;
	पूर्णांक eth_clk_sel_reg;
	पूर्णांक eth_ref_clk_sel_reg;
	पूर्णांक irq_pwr_wakeup;
	u32 mode_reg;		 /* MAC glue-logic mode रेजिस्टर */
	काष्ठा regmap *regmap;
	u32 speed;
	स्थिर काष्ठा sपंचांग32_ops *ops;
	काष्ठा device *dev;
पूर्ण;

काष्ठा sपंचांग32_ops अणु
	पूर्णांक (*set_mode)(काष्ठा plat_sपंचांगmacenet_data *plat_dat);
	पूर्णांक (*clk_prepare)(काष्ठा sपंचांग32_dwmac *dwmac, bool prepare);
	पूर्णांक (*suspend)(काष्ठा sपंचांग32_dwmac *dwmac);
	व्योम (*resume)(काष्ठा sपंचांग32_dwmac *dwmac);
	पूर्णांक (*parse_data)(काष्ठा sपंचांग32_dwmac *dwmac,
			  काष्ठा device *dev);
	u32 syscfg_eth_mask;
पूर्ण;

अटल पूर्णांक sपंचांग32_dwmac_init(काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा sपंचांग32_dwmac *dwmac = plat_dat->bsp_priv;
	पूर्णांक ret;

	अगर (dwmac->ops->set_mode) अणु
		ret = dwmac->ops->set_mode(plat_dat);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dwmac->clk_tx);
	अगर (ret)
		वापस ret;

	अगर (!dwmac->dev->घातer.is_suspended) अणु
		ret = clk_prepare_enable(dwmac->clk_rx);
		अगर (ret) अणु
			clk_disable_unprepare(dwmac->clk_tx);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dwmac->ops->clk_prepare) अणु
		ret = dwmac->ops->clk_prepare(dwmac, true);
		अगर (ret) अणु
			clk_disable_unprepare(dwmac->clk_rx);
			clk_disable_unprepare(dwmac->clk_tx);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32mp1_clk_prepare(काष्ठा sपंचांग32_dwmac *dwmac, bool prepare)
अणु
	पूर्णांक ret = 0;

	अगर (prepare) अणु
		ret = clk_prepare_enable(dwmac->syscfg_clk);
		अगर (ret)
			वापस ret;
		अगर (dwmac->enable_eth_ck) अणु
			ret = clk_prepare_enable(dwmac->clk_eth_ck);
			अगर (ret) अणु
				clk_disable_unprepare(dwmac->syscfg_clk);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(dwmac->syscfg_clk);
		अगर (dwmac->enable_eth_ck)
			clk_disable_unprepare(dwmac->clk_eth_ck);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32mp1_set_mode(काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा sपंचांग32_dwmac *dwmac = plat_dat->bsp_priv;
	u32 reg = dwmac->mode_reg, clk_rate;
	पूर्णांक val;

	clk_rate = clk_get_rate(dwmac->clk_eth_ck);
	dwmac->enable_eth_ck = false;
	चयन (plat_dat->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		अगर (clk_rate == ETH_CK_F_25M && dwmac->ext_phyclk)
			dwmac->enable_eth_ck = true;
		val = SYSCFG_PMCR_ETH_SEL_MII;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_MII\n");
		अवरोध;
	हाल PHY_INTERFACE_MODE_GMII:
		val = SYSCFG_PMCR_ETH_SEL_GMII;
		अगर (clk_rate == ETH_CK_F_25M &&
		    (dwmac->eth_clk_sel_reg || dwmac->ext_phyclk)) अणु
			dwmac->enable_eth_ck = true;
			val |= SYSCFG_PMCR_ETH_CLK_SEL;
		पूर्ण
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_GMII\n");
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		val = SYSCFG_PMCR_ETH_SEL_RMII;
		अगर ((clk_rate == ETH_CK_F_25M || clk_rate == ETH_CK_F_50M) &&
		    (dwmac->eth_ref_clk_sel_reg || dwmac->ext_phyclk)) अणु
			dwmac->enable_eth_ck = true;
			val |= SYSCFG_PMCR_ETH_REF_CLK_SEL;
		पूर्ण
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_RMII\n");
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		val = SYSCFG_PMCR_ETH_SEL_RGMII;
		अगर ((clk_rate == ETH_CK_F_25M || clk_rate == ETH_CK_F_125M) &&
		    (dwmac->eth_clk_sel_reg || dwmac->ext_phyclk)) अणु
			dwmac->enable_eth_ck = true;
			val |= SYSCFG_PMCR_ETH_CLK_SEL;
		पूर्ण
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_RGMII\n");
		अवरोध;
	शेष:
		pr_debug("SYSCFG init :  Do not manage %d interface\n",
			 plat_dat->पूर्णांकerface);
		/* Do not manage others पूर्णांकerfaces */
		वापस -EINVAL;
	पूर्ण

	/* Need to update PMCCLRR (clear रेजिस्टर) */
	regmap_ग_लिखो(dwmac->regmap, reg + SYSCFG_PMCCLRR_OFFSET,
		     dwmac->ops->syscfg_eth_mask);

	/* Update PMCSETR (set रेजिस्टर) */
	वापस regmap_update_bits(dwmac->regmap, reg,
				 dwmac->ops->syscfg_eth_mask, val);
पूर्ण

अटल पूर्णांक sपंचांग32mcu_set_mode(काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा sपंचांग32_dwmac *dwmac = plat_dat->bsp_priv;
	u32 reg = dwmac->mode_reg;
	पूर्णांक val;

	चयन (plat_dat->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		val = SYSCFG_MCU_ETH_SEL_MII;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_MII\n");
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		val = SYSCFG_MCU_ETH_SEL_RMII;
		pr_debug("SYSCFG init : PHY_INTERFACE_MODE_RMII\n");
		अवरोध;
	शेष:
		pr_debug("SYSCFG init :  Do not manage %d interface\n",
			 plat_dat->पूर्णांकerface);
		/* Do not manage others पूर्णांकerfaces */
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(dwmac->regmap, reg,
				 dwmac->ops->syscfg_eth_mask, val << 23);
पूर्ण

अटल व्योम sपंचांग32_dwmac_clk_disable(काष्ठा sपंचांग32_dwmac *dwmac)
अणु
	clk_disable_unprepare(dwmac->clk_tx);
	clk_disable_unprepare(dwmac->clk_rx);

	अगर (dwmac->ops->clk_prepare)
		dwmac->ops->clk_prepare(dwmac, false);
पूर्ण

अटल पूर्णांक sपंचांग32_dwmac_parse_data(काष्ठा sपंचांग32_dwmac *dwmac,
				  काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err;

	/*  Get TX/RX घड़ीs */
	dwmac->clk_tx = devm_clk_get(dev, "mac-clk-tx");
	अगर (IS_ERR(dwmac->clk_tx)) अणु
		dev_err(dev, "No ETH Tx clock provided...\n");
		वापस PTR_ERR(dwmac->clk_tx);
	पूर्ण

	dwmac->clk_rx = devm_clk_get(dev, "mac-clk-rx");
	अगर (IS_ERR(dwmac->clk_rx)) अणु
		dev_err(dev, "No ETH Rx clock provided...\n");
		वापस PTR_ERR(dwmac->clk_rx);
	पूर्ण

	अगर (dwmac->ops->parse_data) अणु
		err = dwmac->ops->parse_data(dwmac, dev);
		अगर (err)
			वापस err;
	पूर्ण

	/* Get mode रेजिस्टर */
	dwmac->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscon");
	अगर (IS_ERR(dwmac->regmap))
		वापस PTR_ERR(dwmac->regmap);

	err = of_property_पढ़ो_u32_index(np, "st,syscon", 1, &dwmac->mode_reg);
	अगर (err)
		dev_err(dev, "Can't get sysconfig mode offset (%d)\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32mp1_parse_data(काष्ठा sपंचांग32_dwmac *dwmac,
			       काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err = 0;

	/* Ethernet PHY have no crystal */
	dwmac->ext_phyclk = of_property_पढ़ो_bool(np, "st,ext-phyclk");

	/* Gigabit Ethernet 125MHz घड़ी selection. */
	dwmac->eth_clk_sel_reg = of_property_पढ़ो_bool(np, "st,eth-clk-sel");

	/* Ethernet 50Mhz RMII घड़ी selection */
	dwmac->eth_ref_clk_sel_reg =
		of_property_पढ़ो_bool(np, "st,eth-ref-clk-sel");

	/*  Get ETH_CLK घड़ीs */
	dwmac->clk_eth_ck = devm_clk_get(dev, "eth-ck");
	अगर (IS_ERR(dwmac->clk_eth_ck)) अणु
		dev_info(dev, "No phy clock provided...\n");
		dwmac->clk_eth_ck = शून्य;
	पूर्ण

	/*  Clock used क्रम low घातer mode */
	dwmac->clk_ethstp = devm_clk_get(dev, "ethstp");
	अगर (IS_ERR(dwmac->clk_ethstp)) अणु
		dev_err(dev,
			"No ETH peripheral clock provided for CStop mode ...\n");
		वापस PTR_ERR(dwmac->clk_ethstp);
	पूर्ण

	/*  Optional Clock क्रम sysconfig */
	dwmac->syscfg_clk = devm_clk_get(dev, "syscfg-clk");
	अगर (IS_ERR(dwmac->syscfg_clk))
		dwmac->syscfg_clk = शून्य;

	/* Get IRQ inक्रमmation early to have an ability to ask क्रम deferred
	 * probe अगर needed beक्रमe we went too far with resource allocation.
	 */
	dwmac->irq_pwr_wakeup = platक्रमm_get_irq_byname_optional(pdev,
							"stm32_pwr_wakeup");
	अगर (dwmac->irq_pwr_wakeup == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (!dwmac->clk_eth_ck && dwmac->irq_pwr_wakeup >= 0) अणु
		err = device_init_wakeup(&pdev->dev, true);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to init wake up irq\n");
			वापस err;
		पूर्ण
		err = dev_pm_set_dedicated_wake_irq(&pdev->dev,
						    dwmac->irq_pwr_wakeup);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to set wake up irq\n");
			device_init_wakeup(&pdev->dev, false);
		पूर्ण
		device_set_wakeup_enable(&pdev->dev, false);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक sपंचांग32_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा sपंचांग32_dwmac *dwmac;
	स्थिर काष्ठा sपंचांग32_ops *data;
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

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "no of match data provided\n");
		ret = -EINVAL;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->ops = data;
	dwmac->dev = &pdev->dev;

	ret = sपंचांग32_dwmac_parse_data(dwmac, &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to parse OF data\n");
		जाओ err_हटाओ_config_dt;
	पूर्ण

	plat_dat->bsp_priv = dwmac;

	ret = sपंचांग32_dwmac_init(plat_dat);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_clk_disable;

	वापस 0;

err_clk_disable:
	sपंचांग32_dwmac_clk_disable(dwmac);
err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dwmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	पूर्णांक ret = sपंचांगmac_dvr_हटाओ(&pdev->dev);
	काष्ठा sपंचांग32_dwmac *dwmac = priv->plat->bsp_priv;

	sपंचांग32_dwmac_clk_disable(priv->plat->bsp_priv);

	अगर (dwmac->irq_pwr_wakeup >= 0) अणु
		dev_pm_clear_wake_irq(&pdev->dev);
		device_init_wakeup(&pdev->dev, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32mp1_suspend(काष्ठा sपंचांग32_dwmac *dwmac)
अणु
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(dwmac->clk_ethstp);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(dwmac->clk_tx);
	clk_disable_unprepare(dwmac->syscfg_clk);
	अगर (dwmac->enable_eth_ck)
		clk_disable_unprepare(dwmac->clk_eth_ck);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32mp1_resume(काष्ठा sपंचांग32_dwmac *dwmac)
अणु
	clk_disable_unprepare(dwmac->clk_ethstp);
पूर्ण

अटल पूर्णांक sपंचांग32mcu_suspend(काष्ठा sपंचांग32_dwmac *dwmac)
अणु
	clk_disable_unprepare(dwmac->clk_tx);
	clk_disable_unprepare(dwmac->clk_rx);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_dwmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा sपंचांग32_dwmac *dwmac = priv->plat->bsp_priv;

	पूर्णांक ret;

	ret = sपंचांगmac_suspend(dev);

	अगर (dwmac->ops->suspend)
		ret = dwmac->ops->suspend(dwmac);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dwmac_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा sपंचांग32_dwmac *dwmac = priv->plat->bsp_priv;
	पूर्णांक ret;

	अगर (dwmac->ops->resume)
		dwmac->ops->resume(dwmac);

	ret = sपंचांग32_dwmac_init(priv->plat);
	अगर (ret)
		वापस ret;

	ret = sपंचांगmac_resume(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_dwmac_pm_ops,
	sपंचांग32_dwmac_suspend, sपंचांग32_dwmac_resume);

अटल काष्ठा sपंचांग32_ops sपंचांग32mcu_dwmac_data = अणु
	.set_mode = sपंचांग32mcu_set_mode,
	.suspend = sपंचांग32mcu_suspend,
	.syscfg_eth_mask = SYSCFG_MCU_ETH_MASK
पूर्ण;

अटल काष्ठा sपंचांग32_ops sपंचांग32mp1_dwmac_data = अणु
	.set_mode = sपंचांग32mp1_set_mode,
	.clk_prepare = sपंचांग32mp1_clk_prepare,
	.suspend = sपंचांग32mp1_suspend,
	.resume = sपंचांग32mp1_resume,
	.parse_data = sपंचांग32mp1_parse_data,
	.syscfg_eth_mask = SYSCFG_MP1_ETH_MASK
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dwmac_match[] = अणु
	अणु .compatible = "st,stm32-dwmac", .data = &sपंचांग32mcu_dwmac_dataपूर्ण,
	अणु .compatible = "st,stm32mp1-dwmac", .data = &sपंचांग32mp1_dwmac_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dwmac_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_dwmac_driver = अणु
	.probe  = sपंचांग32_dwmac_probe,
	.हटाओ = sपंचांग32_dwmac_हटाओ,
	.driver = अणु
		.name           = "stm32-dwmac",
		.pm		= &sपंचांग32_dwmac_pm_ops,
		.of_match_table = sपंचांग32_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_dwmac_driver);

MODULE_AUTHOR("Alexandre Torgue <alexandre.torgue@gmail.com>");
MODULE_AUTHOR("Christophe Roullier <christophe.roullier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 DWMAC Specific Glue layer");
MODULE_LICENSE("GPL v2");
