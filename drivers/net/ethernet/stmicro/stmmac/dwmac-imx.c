<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwmac-imx.c - DWMAC Specअगरic Glue layer क्रम NXP imx8
 *
 * Copyright 2020 NXP
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
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

#घोषणा GPR_ENET_QOS_INTF_MODE_MASK	GENMASK(21, 16)
#घोषणा GPR_ENET_QOS_INTF_SEL_MII	(0x0 << 16)
#घोषणा GPR_ENET_QOS_INTF_SEL_RMII	(0x4 << 16)
#घोषणा GPR_ENET_QOS_INTF_SEL_RGMII	(0x1 << 16)
#घोषणा GPR_ENET_QOS_CLK_GEN_EN		(0x1 << 19)
#घोषणा GPR_ENET_QOS_CLK_TX_CLK_SEL	(0x1 << 20)
#घोषणा GPR_ENET_QOS_RGMII_EN		(0x1 << 21)

काष्ठा imx_dwmac_ops अणु
	u32 addr_width;
	bool mac_rgmii_txclk_स्वतः_adj;

	पूर्णांक (*set_पूर्णांकf_mode)(काष्ठा plat_sपंचांगmacenet_data *plat_dat);
पूर्ण;

काष्ठा imx_priv_data अणु
	काष्ठा device *dev;
	काष्ठा clk *clk_tx;
	काष्ठा clk *clk_mem;
	काष्ठा regmap *पूर्णांकf_regmap;
	u32 पूर्णांकf_reg_off;
	bool rmii_refclk_ext;

	स्थिर काष्ठा imx_dwmac_ops *ops;
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
पूर्ण;

अटल पूर्णांक imx8mp_set_पूर्णांकf_mode(काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	काष्ठा imx_priv_data *dwmac = plat_dat->bsp_priv;
	पूर्णांक val;

	चयन (plat_dat->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		val = GPR_ENET_QOS_INTF_SEL_MII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		val = GPR_ENET_QOS_INTF_SEL_RMII;
		val |= (dwmac->rmii_refclk_ext ? 0 : GPR_ENET_QOS_CLK_TX_CLK_SEL);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		val = GPR_ENET_QOS_INTF_SEL_RGMII |
		      GPR_ENET_QOS_RGMII_EN;
		अवरोध;
	शेष:
		pr_debug("imx dwmac doesn't support %d interface\n",
			 plat_dat->पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	val |= GPR_ENET_QOS_CLK_GEN_EN;
	वापस regmap_update_bits(dwmac->पूर्णांकf_regmap, dwmac->पूर्णांकf_reg_off,
				  GPR_ENET_QOS_INTF_MODE_MASK, val);
पूर्ण;

अटल पूर्णांक
imx8dxl_set_पूर्णांकf_mode(काष्ठा plat_sपंचांगmacenet_data *plat_dat)
अणु
	पूर्णांक ret = 0;

	/* TBD: depends on imx8dxl scu पूर्णांकerfaces to be upstreamed */
	वापस ret;
पूर्ण

अटल पूर्णांक imx_dwmac_clks_config(व्योम *priv, bool enabled)
अणु
	काष्ठा imx_priv_data *dwmac = priv;
	पूर्णांक ret = 0;

	अगर (enabled) अणु
		ret = clk_prepare_enable(dwmac->clk_mem);
		अगर (ret) अणु
			dev_err(dwmac->dev, "mem clock enable failed\n");
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(dwmac->clk_tx);
		अगर (ret) अणु
			dev_err(dwmac->dev, "tx clock enable failed\n");
			clk_disable_unprepare(dwmac->clk_mem);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(dwmac->clk_tx);
		clk_disable_unprepare(dwmac->clk_mem);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx_dwmac_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा imx_priv_data *dwmac = priv;
	पूर्णांक ret;

	plat_dat = dwmac->plat_dat;

	अगर (dwmac->ops->set_पूर्णांकf_mode) अणु
		ret = dwmac->ops->set_पूर्णांकf_mode(plat_dat);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_dwmac_निकास(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	/* nothing to करो now */
पूर्ण

अटल व्योम imx_dwmac_fix_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा imx_priv_data *dwmac = priv;
	अचिन्हित दीर्घ rate;
	पूर्णांक err;

	plat_dat = dwmac->plat_dat;

	अगर (dwmac->ops->mac_rgmii_txclk_स्वतः_adj ||
	    (plat_dat->पूर्णांकerface == PHY_INTERFACE_MODE_RMII) ||
	    (plat_dat->पूर्णांकerface == PHY_INTERFACE_MODE_MII))
		वापस;

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
		dev_err(dwmac->dev, "invalid speed %u\n", speed);
		वापस;
	पूर्ण

	err = clk_set_rate(dwmac->clk_tx, rate);
	अगर (err < 0)
		dev_err(dwmac->dev, "failed to set tx rate %lu\n", rate);
पूर्ण

अटल पूर्णांक
imx_dwmac_parse_dt(काष्ठा imx_priv_data *dwmac, काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err = 0;

	अगर (of_get_property(np, "snps,rmii_refclk_ext", शून्य))
		dwmac->rmii_refclk_ext = true;

	dwmac->clk_tx = devm_clk_get(dev, "tx");
	अगर (IS_ERR(dwmac->clk_tx)) अणु
		dev_err(dev, "failed to get tx clock\n");
		वापस PTR_ERR(dwmac->clk_tx);
	पूर्ण

	dwmac->clk_mem = शून्य;
	अगर (of_machine_is_compatible("fsl,imx8dxl")) अणु
		dwmac->clk_mem = devm_clk_get(dev, "mem");
		अगर (IS_ERR(dwmac->clk_mem)) अणु
			dev_err(dev, "failed to get mem clock\n");
			वापस PTR_ERR(dwmac->clk_mem);
		पूर्ण
	पूर्ण

	अगर (of_machine_is_compatible("fsl,imx8mp")) अणु
		/* Binding करोc describes the propety:
		   is required by i.MX8MP.
		   is optinoal क्रम i.MX8DXL.
		 */
		dwmac->पूर्णांकf_regmap = syscon_regmap_lookup_by_phandle(np, "intf_mode");
		अगर (IS_ERR(dwmac->पूर्णांकf_regmap))
			वापस PTR_ERR(dwmac->पूर्णांकf_regmap);

		err = of_property_पढ़ो_u32_index(np, "intf_mode", 1, &dwmac->पूर्णांकf_reg_off);
		अगर (err) अणु
			dev_err(dev, "Can't get intf mode reg offset (%d)\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक imx_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा imx_priv_data *dwmac;
	स्थिर काष्ठा imx_dwmac_ops *data;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	dwmac = devm_kzalloc(&pdev->dev, माप(*dwmac), GFP_KERNEL);
	अगर (!dwmac)
		वापस -ENOMEM;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		ret = -EINVAL;
		जाओ err_match_data;
	पूर्ण

	dwmac->ops = data;
	dwmac->dev = &pdev->dev;

	ret = imx_dwmac_parse_dt(dwmac, &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to parse OF data\n");
		जाओ err_parse_dt;
	पूर्ण

	plat_dat->addr64 = dwmac->ops->addr_width;
	plat_dat->init = imx_dwmac_init;
	plat_dat->निकास = imx_dwmac_निकास;
	plat_dat->clks_config = imx_dwmac_clks_config;
	plat_dat->fix_mac_speed = imx_dwmac_fix_speed;
	plat_dat->bsp_priv = dwmac;
	dwmac->plat_dat = plat_dat;

	ret = imx_dwmac_clks_config(dwmac, true);
	अगर (ret)
		जाओ err_clks_config;

	ret = imx_dwmac_init(pdev, dwmac);
	अगर (ret)
		जाओ err_dwmac_init;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_drv_probe;

	वापस 0;

err_drv_probe:
	imx_dwmac_निकास(pdev, plat_dat->bsp_priv);
err_dwmac_init:
	imx_dwmac_clks_config(dwmac, false);
err_clks_config:
err_parse_dt:
err_match_data:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);
	वापस ret;
पूर्ण

अटल काष्ठा imx_dwmac_ops imx8mp_dwmac_data = अणु
	.addr_width = 34,
	.mac_rgmii_txclk_स्वतः_adj = false,
	.set_पूर्णांकf_mode = imx8mp_set_पूर्णांकf_mode,
पूर्ण;

अटल काष्ठा imx_dwmac_ops imx8dxl_dwmac_data = अणु
	.addr_width = 32,
	.mac_rgmii_txclk_स्वतः_adj = true,
	.set_पूर्णांकf_mode = imx8dxl_set_पूर्णांकf_mode,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_dwmac_match[] = अणु
	अणु .compatible = "nxp,imx8mp-dwmac-eqos", .data = &imx8mp_dwmac_data पूर्ण,
	अणु .compatible = "nxp,imx8dxl-dwmac-eqos", .data = &imx8dxl_dwmac_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_dwmac_match);

अटल काष्ठा platक्रमm_driver imx_dwmac_driver = अणु
	.probe  = imx_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "imx-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = imx_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_dwmac_driver);

MODULE_AUTHOR("NXP");
MODULE_DESCRIPTION("NXP imx8 DWMAC Specific Glue layer");
MODULE_LICENSE("GPL v2");
