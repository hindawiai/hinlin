<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Synopsys DWC Ethernet Quality-of-Service v4.10a linux driver
 *
 * Copyright (C) 2016 Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"
#समावेश "dwmac4.h"

काष्ठा tegra_eqos अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;

	काष्ठा reset_control *rst;
	काष्ठा clk *clk_master;
	काष्ठा clk *clk_slave;
	काष्ठा clk *clk_tx;
	काष्ठा clk *clk_rx;

	काष्ठा gpio_desc *reset;
पूर्ण;

अटल पूर्णांक dwc_eth_dwmac_config_dt(काष्ठा platक्रमm_device *pdev,
				   काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा device *dev = &pdev->dev;
	u32 burst_map = 0;
	u32 bit_index = 0;
	u32 a_index = 0;

	अगर (!plat_dat->axi) अणु
		plat_dat->axi = kzalloc(माप(काष्ठा sपंचांगmac_axi), GFP_KERNEL);

		अगर (!plat_dat->axi)
			वापस -ENOMEM;
	पूर्ण

	plat_dat->axi->axi_lpi_en = device_property_पढ़ो_bool(dev,
							      "snps,en-lpi");
	अगर (device_property_पढ़ो_u32(dev, "snps,write-requests",
				     &plat_dat->axi->axi_wr_osr_lmt)) अणु
		/**
		 * Since the रेजिस्टर has a reset value of 1, अगर property
		 * is missing, शेष to 1.
		 */
		plat_dat->axi->axi_wr_osr_lmt = 1;
	पूर्ण अन्यथा अणु
		/**
		 * If property exists, to keep the behavior from dwc_eth_qos,
		 * subtract one after parsing.
		 */
		plat_dat->axi->axi_wr_osr_lmt--;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "snps,read-requests",
				     &plat_dat->axi->axi_rd_osr_lmt)) अणु
		/**
		 * Since the रेजिस्टर has a reset value of 1, अगर property
		 * is missing, शेष to 1.
		 */
		plat_dat->axi->axi_rd_osr_lmt = 1;
	पूर्ण अन्यथा अणु
		/**
		 * If property exists, to keep the behavior from dwc_eth_qos,
		 * subtract one after parsing.
		 */
		plat_dat->axi->axi_rd_osr_lmt--;
	पूर्ण
	device_property_पढ़ो_u32(dev, "snps,burst-map", &burst_map);

	/* converts burst-map biपंचांगask to burst array */
	क्रम (bit_index = 0; bit_index < 7; bit_index++) अणु
		अगर (burst_map & (1 << bit_index)) अणु
			चयन (bit_index) अणु
			हाल 0:
			plat_dat->axi->axi_blen[a_index] = 4; अवरोध;
			हाल 1:
			plat_dat->axi->axi_blen[a_index] = 8; अवरोध;
			हाल 2:
			plat_dat->axi->axi_blen[a_index] = 16; अवरोध;
			हाल 3:
			plat_dat->axi->axi_blen[a_index] = 32; अवरोध;
			हाल 4:
			plat_dat->axi->axi_blen[a_index] = 64; अवरोध;
			हाल 5:
			plat_dat->axi->axi_blen[a_index] = 128; अवरोध;
			हाल 6:
			plat_dat->axi->axi_blen[a_index] = 256; अवरोध;
			शेष:
			अवरोध;
			पूर्ण
			a_index++;
		पूर्ण
	पूर्ण

	/* dwc-qos needs GMAC4, AAL, TSO and PMT */
	plat_dat->has_gmac4 = 1;
	plat_dat->dma_cfg->aal = 1;
	plat_dat->tso_en = 1;
	plat_dat->pmt = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc_qos_probe(काष्ठा platक्रमm_device *pdev,
			 काष्ठा plat_sपंचांगmacenet_data *plat_dat,
			 काष्ठा sपंचांगmac_resources *sपंचांगmac_res)
अणु
	पूर्णांक err;

	plat_dat->sपंचांगmac_clk = devm_clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(plat_dat->sपंचांगmac_clk)) अणु
		dev_err(&pdev->dev, "apb_pclk clock not found.\n");
		वापस PTR_ERR(plat_dat->sपंचांगmac_clk);
	पूर्ण

	err = clk_prepare_enable(plat_dat->sपंचांगmac_clk);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable apb_pclk clock: %d\n",
			err);
		वापस err;
	पूर्ण

	plat_dat->pclk = devm_clk_get(&pdev->dev, "phy_ref_clk");
	अगर (IS_ERR(plat_dat->pclk)) अणु
		dev_err(&pdev->dev, "phy_ref_clk clock not found.\n");
		err = PTR_ERR(plat_dat->pclk);
		जाओ disable;
	पूर्ण

	err = clk_prepare_enable(plat_dat->pclk);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable phy_ref clock: %d\n",
			err);
		जाओ disable;
	पूर्ण

	वापस 0;

disable:
	clk_disable_unprepare(plat_dat->sपंचांगmac_clk);
	वापस err;
पूर्ण

अटल पूर्णांक dwc_qos_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	clk_disable_unprepare(priv->plat->pclk);
	clk_disable_unprepare(priv->plat->sपंचांगmac_clk);

	वापस 0;
पूर्ण

#घोषणा SDMEMCOMPPADCTRL 0x8800
#घोषणा  SDMEMCOMPPADCTRL_PAD_E_INPUT_OR_E_PWRD BIT(31)

#घोषणा AUTO_CAL_CONFIG 0x8804
#घोषणा  AUTO_CAL_CONFIG_START BIT(31)
#घोषणा  AUTO_CAL_CONFIG_ENABLE BIT(29)

#घोषणा AUTO_CAL_STATUS 0x880c
#घोषणा  AUTO_CAL_STATUS_ACTIVE BIT(31)

अटल व्योम tegra_eqos_fix_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा tegra_eqos *eqos = priv;
	अचिन्हित दीर्घ rate = 125000000;
	bool needs_calibration = false;
	u32 value;
	पूर्णांक err;

	चयन (speed) अणु
	हाल SPEED_1000:
		needs_calibration = true;
		rate = 125000000;
		अवरोध;

	हाल SPEED_100:
		needs_calibration = true;
		rate = 25000000;
		अवरोध;

	हाल SPEED_10:
		rate = 2500000;
		अवरोध;

	शेष:
		dev_err(eqos->dev, "invalid speed %u\n", speed);
		अवरोध;
	पूर्ण

	अगर (needs_calibration) अणु
		/* calibrate */
		value = पढ़ोl(eqos->regs + SDMEMCOMPPADCTRL);
		value |= SDMEMCOMPPADCTRL_PAD_E_INPUT_OR_E_PWRD;
		ग_लिखोl(value, eqos->regs + SDMEMCOMPPADCTRL);

		udelay(1);

		value = पढ़ोl(eqos->regs + AUTO_CAL_CONFIG);
		value |= AUTO_CAL_CONFIG_START | AUTO_CAL_CONFIG_ENABLE;
		ग_लिखोl(value, eqos->regs + AUTO_CAL_CONFIG);

		err = पढ़ोl_poll_समयout_atomic(eqos->regs + AUTO_CAL_STATUS,
						value,
						value & AUTO_CAL_STATUS_ACTIVE,
						1, 10);
		अगर (err < 0) अणु
			dev_err(eqos->dev, "calibration did not start\n");
			जाओ failed;
		पूर्ण

		err = पढ़ोl_poll_समयout_atomic(eqos->regs + AUTO_CAL_STATUS,
						value,
						(value & AUTO_CAL_STATUS_ACTIVE) == 0,
						20, 200);
		अगर (err < 0) अणु
			dev_err(eqos->dev, "calibration didn't finish\n");
			जाओ failed;
		पूर्ण

	failed:
		value = पढ़ोl(eqos->regs + SDMEMCOMPPADCTRL);
		value &= ~SDMEMCOMPPADCTRL_PAD_E_INPUT_OR_E_PWRD;
		ग_लिखोl(value, eqos->regs + SDMEMCOMPPADCTRL);
	पूर्ण अन्यथा अणु
		value = पढ़ोl(eqos->regs + AUTO_CAL_CONFIG);
		value &= ~AUTO_CAL_CONFIG_ENABLE;
		ग_लिखोl(value, eqos->regs + AUTO_CAL_CONFIG);
	पूर्ण

	err = clk_set_rate(eqos->clk_tx, rate);
	अगर (err < 0)
		dev_err(eqos->dev, "failed to set TX rate: %d\n", err);
पूर्ण

अटल पूर्णांक tegra_eqos_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा tegra_eqos *eqos = priv;
	अचिन्हित दीर्घ rate;
	u32 value;

	rate = clk_get_rate(eqos->clk_slave);

	value = (rate / 1000000) - 1;
	ग_लिखोl(value, eqos->regs + GMAC_1US_TIC_COUNTER);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_eqos_probe(काष्ठा platक्रमm_device *pdev,
			    काष्ठा plat_sपंचांगmacenet_data *data,
			    काष्ठा sपंचांगmac_resources *res)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra_eqos *eqos;
	पूर्णांक err;

	eqos = devm_kzalloc(&pdev->dev, माप(*eqos), GFP_KERNEL);
	अगर (!eqos)
		वापस -ENOMEM;

	eqos->dev = &pdev->dev;
	eqos->regs = res->addr;

	अगर (!is_of_node(dev->fwnode))
		जाओ bypass_clk_reset_gpio;

	eqos->clk_master = devm_clk_get(&pdev->dev, "master_bus");
	अगर (IS_ERR(eqos->clk_master)) अणु
		err = PTR_ERR(eqos->clk_master);
		जाओ error;
	पूर्ण

	err = clk_prepare_enable(eqos->clk_master);
	अगर (err < 0)
		जाओ error;

	eqos->clk_slave = devm_clk_get(&pdev->dev, "slave_bus");
	अगर (IS_ERR(eqos->clk_slave)) अणु
		err = PTR_ERR(eqos->clk_slave);
		जाओ disable_master;
	पूर्ण

	data->sपंचांगmac_clk = eqos->clk_slave;

	err = clk_prepare_enable(eqos->clk_slave);
	अगर (err < 0)
		जाओ disable_master;

	eqos->clk_rx = devm_clk_get(&pdev->dev, "rx");
	अगर (IS_ERR(eqos->clk_rx)) अणु
		err = PTR_ERR(eqos->clk_rx);
		जाओ disable_slave;
	पूर्ण

	err = clk_prepare_enable(eqos->clk_rx);
	अगर (err < 0)
		जाओ disable_slave;

	eqos->clk_tx = devm_clk_get(&pdev->dev, "tx");
	अगर (IS_ERR(eqos->clk_tx)) अणु
		err = PTR_ERR(eqos->clk_tx);
		जाओ disable_rx;
	पूर्ण

	err = clk_prepare_enable(eqos->clk_tx);
	अगर (err < 0)
		जाओ disable_rx;

	eqos->reset = devm_gpiod_get(&pdev->dev, "phy-reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(eqos->reset)) अणु
		err = PTR_ERR(eqos->reset);
		जाओ disable_tx;
	पूर्ण

	usleep_range(2000, 4000);
	gpiod_set_value(eqos->reset, 0);

	/* MDIO bus was alपढ़ोy reset just above */
	data->mdio_bus_data->needs_reset = false;

	eqos->rst = devm_reset_control_get(&pdev->dev, "eqos");
	अगर (IS_ERR(eqos->rst)) अणु
		err = PTR_ERR(eqos->rst);
		जाओ reset_phy;
	पूर्ण

	err = reset_control_निश्चित(eqos->rst);
	अगर (err < 0)
		जाओ reset_phy;

	usleep_range(2000, 4000);

	err = reset_control_deनिश्चित(eqos->rst);
	अगर (err < 0)
		जाओ reset_phy;

	usleep_range(2000, 4000);

bypass_clk_reset_gpio:
	data->fix_mac_speed = tegra_eqos_fix_speed;
	data->init = tegra_eqos_init;
	data->bsp_priv = eqos;

	err = tegra_eqos_init(pdev, eqos);
	अगर (err < 0)
		जाओ reset;

	वापस 0;
reset:
	reset_control_निश्चित(eqos->rst);
reset_phy:
	gpiod_set_value(eqos->reset, 1);
disable_tx:
	clk_disable_unprepare(eqos->clk_tx);
disable_rx:
	clk_disable_unprepare(eqos->clk_rx);
disable_slave:
	clk_disable_unprepare(eqos->clk_slave);
disable_master:
	clk_disable_unprepare(eqos->clk_master);
error:
	वापस err;
पूर्ण

अटल पूर्णांक tegra_eqos_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_eqos *eqos = get_sपंचांगmac_bsp_priv(&pdev->dev);

	reset_control_निश्चित(eqos->rst);
	gpiod_set_value(eqos->reset, 1);
	clk_disable_unprepare(eqos->clk_tx);
	clk_disable_unprepare(eqos->clk_rx);
	clk_disable_unprepare(eqos->clk_slave);
	clk_disable_unprepare(eqos->clk_master);

	वापस 0;
पूर्ण

काष्ठा dwc_eth_dwmac_data अणु
	पूर्णांक (*probe)(काष्ठा platक्रमm_device *pdev,
		     काष्ठा plat_sपंचांगmacenet_data *data,
		     काष्ठा sपंचांगmac_resources *res);
	पूर्णांक (*हटाओ)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

अटल स्थिर काष्ठा dwc_eth_dwmac_data dwc_qos_data = अणु
	.probe = dwc_qos_probe,
	.हटाओ = dwc_qos_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा dwc_eth_dwmac_data tegra_eqos_data = अणु
	.probe = tegra_eqos_probe,
	.हटाओ = tegra_eqos_हटाओ,
पूर्ण;

अटल पूर्णांक dwc_eth_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dwc_eth_dwmac_data *data;
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	पूर्णांक ret;

	data = device_get_match_data(&pdev->dev);

	स_रखो(&sपंचांगmac_res, 0, माप(काष्ठा sपंचांगmac_resources));

	/**
	 * Since sपंचांगmac_platक्रमm supports name IRQ only, basic platक्रमm
	 * resource initialization is करोne in the glue logic.
	 */
	sपंचांगmac_res.irq = platक्रमm_get_irq(pdev, 0);
	अगर (sपंचांगmac_res.irq < 0)
		वापस sपंचांगmac_res.irq;
	sपंचांगmac_res.wol_irq = sपंचांगmac_res.irq;

	sपंचांगmac_res.addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sपंचांगmac_res.addr))
		वापस PTR_ERR(sपंचांगmac_res.addr);

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	ret = data->probe(pdev, plat_dat, &sपंचांगmac_res);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to probe subdriver: %d\n",
				ret);

		जाओ हटाओ_config;
	पूर्ण

	ret = dwc_eth_dwmac_config_dt(pdev, plat_dat);
	अगर (ret)
		जाओ हटाओ;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ हटाओ;

	वापस ret;

हटाओ:
	data->हटाओ(pdev);
हटाओ_config:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc_eth_dwmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	स्थिर काष्ठा dwc_eth_dwmac_data *data;
	पूर्णांक err;

	data = device_get_match_data(&pdev->dev);

	err = sपंचांगmac_dvr_हटाओ(&pdev->dev);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to remove platform: %d\n", err);

	err = data->हटाओ(pdev);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to remove subdriver: %d\n", err);

	sपंचांगmac_हटाओ_config_dt(pdev, priv->plat);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id dwc_eth_dwmac_match[] = अणु
	अणु .compatible = "snps,dwc-qos-ethernet-4.10", .data = &dwc_qos_data पूर्ण,
	अणु .compatible = "nvidia,tegra186-eqos", .data = &tegra_eqos_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dwc_eth_dwmac_match);

अटल काष्ठा platक्रमm_driver dwc_eth_dwmac_driver = अणु
	.probe  = dwc_eth_dwmac_probe,
	.हटाओ = dwc_eth_dwmac_हटाओ,
	.driver = अणु
		.name           = "dwc-eth-dwmac",
		.pm             = &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = dwc_eth_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dwc_eth_dwmac_driver);

MODULE_AUTHOR("Joao Pinto <jpinto@synopsys.com>");
MODULE_DESCRIPTION("Synopsys DWC Ethernet Quality-of-Service v4.10a driver");
MODULE_LICENSE("GPL v2");
