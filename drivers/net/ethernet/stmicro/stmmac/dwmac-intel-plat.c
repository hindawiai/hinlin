<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Intel DWMAC platक्रमm driver
 *
 * Copyright(C) 2020 Intel Corporation
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "dwmac4.h"
#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

काष्ठा पूर्णांकel_dwmac अणु
	काष्ठा device *dev;
	काष्ठा clk *tx_clk;
	स्थिर काष्ठा पूर्णांकel_dwmac_data *data;
पूर्ण;

काष्ठा पूर्णांकel_dwmac_data अणु
	व्योम (*fix_mac_speed)(व्योम *priv, अचिन्हित पूर्णांक speed);
	अचिन्हित दीर्घ ptp_ref_clk_rate;
	अचिन्हित दीर्घ tx_clk_rate;
	bool tx_clk_en;
पूर्ण;

अटल व्योम kmb_eth_fix_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा पूर्णांकel_dwmac *dwmac = priv;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	rate = clk_get_rate(dwmac->tx_clk);

	चयन (speed) अणु
	हाल SPEED_1000:
		rate = 125000000;
		अवरोध;

	हाल SPEED_100:
		rate = 25000000;
		अवरोध;

	हाल SPEED_10:
		rate = 2500000;
		अवरोध;

	शेष:
		dev_err(dwmac->dev, "Invalid speed\n");
		अवरोध;
	पूर्ण

	ret = clk_set_rate(dwmac->tx_clk, rate);
	अगर (ret)
		dev_err(dwmac->dev, "Failed to configure tx clock rate\n");
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_dwmac_data kmb_data = अणु
	.fix_mac_speed = kmb_eth_fix_mac_speed,
	.ptp_ref_clk_rate = 200000000,
	.tx_clk_rate = 125000000,
	.tx_clk_en = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id पूर्णांकel_eth_plat_match[] = अणु
	अणु .compatible = "intel,keembay-dwmac", .data = &kmb_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, पूर्णांकel_eth_plat_match);

अटल पूर्णांक पूर्णांकel_eth_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा पूर्णांकel_dwmac *dwmac;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat)) अणु
		dev_err(&pdev->dev, "dt configuration failed\n");
		वापस PTR_ERR(plat_dat);
	पूर्ण

	dwmac = devm_kzalloc(&pdev->dev, माप(*dwmac), GFP_KERNEL);
	अगर (!dwmac) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->dev = &pdev->dev;
	dwmac->tx_clk = शून्य;

	match = of_match_device(पूर्णांकel_eth_plat_match, &pdev->dev);
	अगर (match && match->data) अणु
		dwmac->data = (स्थिर काष्ठा पूर्णांकel_dwmac_data *)match->data;

		अगर (dwmac->data->fix_mac_speed)
			plat_dat->fix_mac_speed = dwmac->data->fix_mac_speed;

		/* Enable TX घड़ी */
		अगर (dwmac->data->tx_clk_en) अणु
			dwmac->tx_clk = devm_clk_get(&pdev->dev, "tx_clk");
			अगर (IS_ERR(dwmac->tx_clk)) अणु
				ret = PTR_ERR(dwmac->tx_clk);
				जाओ err_हटाओ_config_dt;
			पूर्ण

			clk_prepare_enable(dwmac->tx_clk);

			/* Check and configure TX घड़ी rate */
			rate = clk_get_rate(dwmac->tx_clk);
			अगर (dwmac->data->tx_clk_rate &&
			    rate != dwmac->data->tx_clk_rate) अणु
				rate = dwmac->data->tx_clk_rate;
				ret = clk_set_rate(dwmac->tx_clk, rate);
				अगर (ret) अणु
					dev_err(&pdev->dev,
						"Failed to set tx_clk\n");
					जाओ err_हटाओ_config_dt;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Check and configure PTP ref घड़ी rate */
		rate = clk_get_rate(plat_dat->clk_ptp_ref);
		अगर (dwmac->data->ptp_ref_clk_rate &&
		    rate != dwmac->data->ptp_ref_clk_rate) अणु
			rate = dwmac->data->ptp_ref_clk_rate;
			ret = clk_set_rate(plat_dat->clk_ptp_ref, rate);
			अगर (ret) अणु
				dev_err(&pdev->dev,
					"Failed to set clk_ptp_ref\n");
				जाओ err_हटाओ_config_dt;
			पूर्ण
		पूर्ण
	पूर्ण

	plat_dat->bsp_priv = dwmac;
	plat_dat->eee_usecs_rate = plat_dat->clk_ptp_rate;

	अगर (plat_dat->eee_usecs_rate > 0) अणु
		u32 tx_lpi_usec;

		tx_lpi_usec = (plat_dat->eee_usecs_rate / 1000000) - 1;
		ग_लिखोl(tx_lpi_usec, sपंचांगmac_res.addr + GMAC_1US_TIC_COUNTER);
	पूर्ण

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret) अणु
		clk_disable_unprepare(dwmac->tx_clk);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	वापस 0;

err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_eth_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_dwmac *dwmac = get_sपंचांगmac_bsp_priv(&pdev->dev);
	पूर्णांक ret;

	ret = sपंचांगmac_pltfr_हटाओ(pdev);
	clk_disable_unprepare(dwmac->tx_clk);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_eth_plat_driver = अणु
	.probe  = पूर्णांकel_eth_plat_probe,
	.हटाओ = पूर्णांकel_eth_plat_हटाओ,
	.driver = अणु
		.name		= "intel-eth-plat",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = पूर्णांकel_eth_plat_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(पूर्णांकel_eth_plat_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel DWMAC platform driver");
