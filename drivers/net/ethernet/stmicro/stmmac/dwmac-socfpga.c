<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright Altera Corporation (C) 2014. All rights reserved.
 *
 * Aकरोpted from dwmac-sti.c
 */

#समावेश <linux/mfd/altera-sysmgr.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

#समावेश "altr_tse_pcs.h"

#घोषणा SGMII_ADAPTER_CTRL_REG                          0x00
#घोषणा SGMII_ADAPTER_DISABLE                           0x0001

#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII 0x0
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RGMII 0x1
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RMII 0x2
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_WIDTH 2
#घोषणा SYSMGR_EMACGRP_CTRL_PHYSEL_MASK 0x00000003
#घोषणा SYSMGR_EMACGRP_CTRL_PTP_REF_CLK_MASK 0x00000010
#घोषणा SYSMGR_GEN10_EMACGRP_CTRL_PTP_REF_CLK_MASK 0x00000100

#घोषणा SYSMGR_FPGAGRP_MODULE_REG  0x00000028
#घोषणा SYSMGR_FPGAGRP_MODULE_EMAC 0x00000004
#घोषणा SYSMGR_FPGAINTF_EMAC_REG	0x00000070
#घोषणा SYSMGR_FPGAINTF_EMAC_BIT	0x1

#घोषणा EMAC_SPLITTER_CTRL_REG			0x0
#घोषणा EMAC_SPLITTER_CTRL_SPEED_MASK		0x3
#घोषणा EMAC_SPLITTER_CTRL_SPEED_10		0x2
#घोषणा EMAC_SPLITTER_CTRL_SPEED_100		0x3
#घोषणा EMAC_SPLITTER_CTRL_SPEED_1000		0x0

काष्ठा socfpga_dwmac;
काष्ठा socfpga_dwmac_ops अणु
	पूर्णांक (*set_phy_mode)(काष्ठा socfpga_dwmac *dwmac_priv);
पूर्ण;

काष्ठा socfpga_dwmac अणु
	u32	reg_offset;
	u32	reg_shअगरt;
	काष्ठा	device *dev;
	काष्ठा regmap *sys_mgr_base_addr;
	काष्ठा reset_control *sपंचांगmac_rst;
	काष्ठा reset_control *sपंचांगmac_ocp_rst;
	व्योम __iomem *splitter_base;
	bool f2h_ptp_ref_clk;
	काष्ठा tse_pcs pcs;
	स्थिर काष्ठा socfpga_dwmac_ops *ops;
पूर्ण;

अटल व्योम socfpga_dwmac_fix_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा socfpga_dwmac *dwmac = (काष्ठा socfpga_dwmac *)priv;
	व्योम __iomem *splitter_base = dwmac->splitter_base;
	व्योम __iomem *tse_pcs_base = dwmac->pcs.tse_pcs_base;
	व्योम __iomem *sgmii_adapter_base = dwmac->pcs.sgmii_adapter_base;
	काष्ठा device *dev = dwmac->dev;
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा phy_device *phy_dev = ndev->phydev;
	u32 val;

	अगर ((tse_pcs_base) && (sgmii_adapter_base))
		ग_लिखोw(SGMII_ADAPTER_DISABLE,
		       sgmii_adapter_base + SGMII_ADAPTER_CTRL_REG);

	अगर (splitter_base) अणु
		val = पढ़ोl(splitter_base + EMAC_SPLITTER_CTRL_REG);
		val &= ~EMAC_SPLITTER_CTRL_SPEED_MASK;

		चयन (speed) अणु
		हाल 1000:
			val |= EMAC_SPLITTER_CTRL_SPEED_1000;
			अवरोध;
		हाल 100:
			val |= EMAC_SPLITTER_CTRL_SPEED_100;
			अवरोध;
		हाल 10:
			val |= EMAC_SPLITTER_CTRL_SPEED_10;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		ग_लिखोl(val, splitter_base + EMAC_SPLITTER_CTRL_REG);
	पूर्ण

	अगर (tse_pcs_base && sgmii_adapter_base)
		tse_pcs_fix_mac_speed(&dwmac->pcs, phy_dev, speed);
पूर्ण

अटल पूर्णांक socfpga_dwmac_parse_data(काष्ठा socfpga_dwmac *dwmac, काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *sys_mgr_base_addr;
	u32 reg_offset, reg_shअगरt;
	पूर्णांक ret, index;
	काष्ठा device_node *np_splitter = शून्य;
	काष्ठा device_node *np_sgmii_adapter = शून्य;
	काष्ठा resource res_splitter;
	काष्ठा resource res_tse_pcs;
	काष्ठा resource res_sgmii_adapter;

	sys_mgr_base_addr =
		altr_sysmgr_regmap_lookup_by_phandle(np, "altr,sysmgr-syscon");
	अगर (IS_ERR(sys_mgr_base_addr)) अणु
		dev_info(dev, "No sysmgr-syscon node found\n");
		वापस PTR_ERR(sys_mgr_base_addr);
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "altr,sysmgr-syscon", 1, &reg_offset);
	अगर (ret) अणु
		dev_info(dev, "Could not read reg_offset from sysmgr-syscon!\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "altr,sysmgr-syscon", 2, &reg_shअगरt);
	अगर (ret) अणु
		dev_info(dev, "Could not read reg_shift from sysmgr-syscon!\n");
		वापस -EINVAL;
	पूर्ण

	dwmac->f2h_ptp_ref_clk = of_property_पढ़ो_bool(np, "altr,f2h_ptp_ref_clk");

	np_splitter = of_parse_phandle(np, "altr,emac-splitter", 0);
	अगर (np_splitter) अणु
		ret = of_address_to_resource(np_splitter, 0, &res_splitter);
		of_node_put(np_splitter);
		अगर (ret) अणु
			dev_info(dev, "Missing emac splitter address\n");
			वापस -EINVAL;
		पूर्ण

		dwmac->splitter_base = devm_ioremap_resource(dev, &res_splitter);
		अगर (IS_ERR(dwmac->splitter_base)) अणु
			dev_info(dev, "Failed to mapping emac splitter\n");
			वापस PTR_ERR(dwmac->splitter_base);
		पूर्ण
	पूर्ण

	np_sgmii_adapter = of_parse_phandle(np,
					    "altr,gmii-to-sgmii-converter", 0);
	अगर (np_sgmii_adapter) अणु
		index = of_property_match_string(np_sgmii_adapter, "reg-names",
						 "hps_emac_interface_splitter_avalon_slave");

		अगर (index >= 0) अणु
			अगर (of_address_to_resource(np_sgmii_adapter, index,
						   &res_splitter)) अणु
				dev_err(dev,
					"%s: ERROR: missing emac splitter address\n",
					__func__);
				ret = -EINVAL;
				जाओ err_node_put;
			पूर्ण

			dwmac->splitter_base =
			    devm_ioremap_resource(dev, &res_splitter);

			अगर (IS_ERR(dwmac->splitter_base)) अणु
				ret = PTR_ERR(dwmac->splitter_base);
				जाओ err_node_put;
			पूर्ण
		पूर्ण

		index = of_property_match_string(np_sgmii_adapter, "reg-names",
						 "gmii_to_sgmii_adapter_avalon_slave");

		अगर (index >= 0) अणु
			अगर (of_address_to_resource(np_sgmii_adapter, index,
						   &res_sgmii_adapter)) अणु
				dev_err(dev,
					"%s: ERROR: failed mapping adapter\n",
					__func__);
				ret = -EINVAL;
				जाओ err_node_put;
			पूर्ण

			dwmac->pcs.sgmii_adapter_base =
			    devm_ioremap_resource(dev, &res_sgmii_adapter);

			अगर (IS_ERR(dwmac->pcs.sgmii_adapter_base)) अणु
				ret = PTR_ERR(dwmac->pcs.sgmii_adapter_base);
				जाओ err_node_put;
			पूर्ण
		पूर्ण

		index = of_property_match_string(np_sgmii_adapter, "reg-names",
						 "eth_tse_control_port");

		अगर (index >= 0) अणु
			अगर (of_address_to_resource(np_sgmii_adapter, index,
						   &res_tse_pcs)) अणु
				dev_err(dev,
					"%s: ERROR: failed mapping tse control port\n",
					__func__);
				ret = -EINVAL;
				जाओ err_node_put;
			पूर्ण

			dwmac->pcs.tse_pcs_base =
			    devm_ioremap_resource(dev, &res_tse_pcs);

			अगर (IS_ERR(dwmac->pcs.tse_pcs_base)) अणु
				ret = PTR_ERR(dwmac->pcs.tse_pcs_base);
				जाओ err_node_put;
			पूर्ण
		पूर्ण
	पूर्ण
	dwmac->reg_offset = reg_offset;
	dwmac->reg_shअगरt = reg_shअगरt;
	dwmac->sys_mgr_base_addr = sys_mgr_base_addr;
	dwmac->dev = dev;
	of_node_put(np_sgmii_adapter);

	वापस 0;

err_node_put:
	of_node_put(np_sgmii_adapter);
	वापस ret;
पूर्ण

अटल पूर्णांक socfpga_get_plat_phymode(काष्ठा socfpga_dwmac *dwmac)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dwmac->dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	वापस priv->plat->पूर्णांकerface;
पूर्ण

अटल पूर्णांक socfpga_set_phy_mode_common(पूर्णांक phymode, u32 *val)
अणु
	चयन (phymode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		*val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RGMII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_GMII:
	हाल PHY_INTERFACE_MODE_SGMII:
		*val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		*val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RMII;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_gen5_set_phy_mode(काष्ठा socfpga_dwmac *dwmac)
अणु
	काष्ठा regmap *sys_mgr_base_addr = dwmac->sys_mgr_base_addr;
	पूर्णांक phymode = socfpga_get_plat_phymode(dwmac);
	u32 reg_offset = dwmac->reg_offset;
	u32 reg_shअगरt = dwmac->reg_shअगरt;
	u32 ctrl, val, module;

	अगर (socfpga_set_phy_mode_common(phymode, &val)) अणु
		dev_err(dwmac->dev, "bad phy mode %d\n", phymode);
		वापस -EINVAL;
	पूर्ण

	/* Overग_लिखो val to GMII अगर splitter core is enabled. The phymode here
	 * is the actual phy mode on phy hardware, but phy पूर्णांकerface from
	 * EMAC core is GMII.
	 */
	अगर (dwmac->splitter_base)
		val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII;

	/* Assert reset to the enet controller beक्रमe changing the phy mode */
	reset_control_निश्चित(dwmac->sपंचांगmac_ocp_rst);
	reset_control_निश्चित(dwmac->sपंचांगmac_rst);

	regmap_पढ़ो(sys_mgr_base_addr, reg_offset, &ctrl);
	ctrl &= ~(SYSMGR_EMACGRP_CTRL_PHYSEL_MASK << reg_shअगरt);
	ctrl |= val << reg_shअगरt;

	अगर (dwmac->f2h_ptp_ref_clk ||
	    phymode == PHY_INTERFACE_MODE_MII ||
	    phymode == PHY_INTERFACE_MODE_GMII ||
	    phymode == PHY_INTERFACE_MODE_SGMII) अणु
		regmap_पढ़ो(sys_mgr_base_addr, SYSMGR_FPGAGRP_MODULE_REG,
			    &module);
		module |= (SYSMGR_FPGAGRP_MODULE_EMAC << (reg_shअगरt / 2));
		regmap_ग_लिखो(sys_mgr_base_addr, SYSMGR_FPGAGRP_MODULE_REG,
			     module);
	पूर्ण

	अगर (dwmac->f2h_ptp_ref_clk)
		ctrl |= SYSMGR_EMACGRP_CTRL_PTP_REF_CLK_MASK << (reg_shअगरt / 2);
	अन्यथा
		ctrl &= ~(SYSMGR_EMACGRP_CTRL_PTP_REF_CLK_MASK <<
			  (reg_shअगरt / 2));

	regmap_ग_लिखो(sys_mgr_base_addr, reg_offset, ctrl);

	/* Deनिश्चित reset क्रम the phy configuration to be sampled by
	 * the enet controller, and operation to start in requested mode
	 */
	reset_control_deनिश्चित(dwmac->sपंचांगmac_ocp_rst);
	reset_control_deनिश्चित(dwmac->sपंचांगmac_rst);
	अगर (phymode == PHY_INTERFACE_MODE_SGMII) अणु
		अगर (tse_pcs_init(dwmac->pcs.tse_pcs_base, &dwmac->pcs) != 0) अणु
			dev_err(dwmac->dev, "Unable to initialize TSE PCS");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_gen10_set_phy_mode(काष्ठा socfpga_dwmac *dwmac)
अणु
	काष्ठा regmap *sys_mgr_base_addr = dwmac->sys_mgr_base_addr;
	पूर्णांक phymode = socfpga_get_plat_phymode(dwmac);
	u32 reg_offset = dwmac->reg_offset;
	u32 reg_shअगरt = dwmac->reg_shअगरt;
	u32 ctrl, val, module;

	अगर (socfpga_set_phy_mode_common(phymode, &val))
		वापस -EINVAL;

	/* Overग_लिखो val to GMII अगर splitter core is enabled. The phymode here
	 * is the actual phy mode on phy hardware, but phy पूर्णांकerface from
	 * EMAC core is GMII.
	 */
	अगर (dwmac->splitter_base)
		val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII;

	/* Assert reset to the enet controller beक्रमe changing the phy mode */
	reset_control_निश्चित(dwmac->sपंचांगmac_ocp_rst);
	reset_control_निश्चित(dwmac->sपंचांगmac_rst);

	regmap_पढ़ो(sys_mgr_base_addr, reg_offset, &ctrl);
	ctrl &= ~(SYSMGR_EMACGRP_CTRL_PHYSEL_MASK);
	ctrl |= val;

	अगर (dwmac->f2h_ptp_ref_clk ||
	    phymode == PHY_INTERFACE_MODE_MII ||
	    phymode == PHY_INTERFACE_MODE_GMII ||
	    phymode == PHY_INTERFACE_MODE_SGMII) अणु
		ctrl |= SYSMGR_GEN10_EMACGRP_CTRL_PTP_REF_CLK_MASK;
		regmap_पढ़ो(sys_mgr_base_addr, SYSMGR_FPGAINTF_EMAC_REG,
			    &module);
		module |= (SYSMGR_FPGAINTF_EMAC_BIT << reg_shअगरt);
		regmap_ग_लिखो(sys_mgr_base_addr, SYSMGR_FPGAINTF_EMAC_REG,
			     module);
	पूर्ण अन्यथा अणु
		ctrl &= ~SYSMGR_GEN10_EMACGRP_CTRL_PTP_REF_CLK_MASK;
	पूर्ण

	regmap_ग_लिखो(sys_mgr_base_addr, reg_offset, ctrl);

	/* Deनिश्चित reset क्रम the phy configuration to be sampled by
	 * the enet controller, and operation to start in requested mode
	 */
	reset_control_deनिश्चित(dwmac->sपंचांगmac_ocp_rst);
	reset_control_deनिश्चित(dwmac->sपंचांगmac_rst);
	अगर (phymode == PHY_INTERFACE_MODE_SGMII) अणु
		अगर (tse_pcs_init(dwmac->pcs.tse_pcs_base, &dwmac->pcs) != 0) अणु
			dev_err(dwmac->dev, "Unable to initialize TSE PCS");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक socfpga_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा device		*dev = &pdev->dev;
	पूर्णांक			ret;
	काष्ठा socfpga_dwmac	*dwmac;
	काष्ठा net_device	*ndev;
	काष्ठा sपंचांगmac_priv	*stpriv;
	स्थिर काष्ठा socfpga_dwmac_ops *ops;

	ops = device_get_match_data(&pdev->dev);
	अगर (!ops) अणु
		dev_err(&pdev->dev, "no of match data provided\n");
		वापस -EINVAL;
	पूर्ण

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	dwmac = devm_kzalloc(dev, माप(*dwmac), GFP_KERNEL);
	अगर (!dwmac) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->sपंचांगmac_ocp_rst = devm_reset_control_get_optional(dev, "stmmaceth-ocp");
	अगर (IS_ERR(dwmac->sपंचांगmac_ocp_rst)) अणु
		ret = PTR_ERR(dwmac->sपंचांगmac_ocp_rst);
		dev_err(dev, "error getting reset control of ocp %d\n", ret);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	reset_control_deनिश्चित(dwmac->sपंचांगmac_ocp_rst);

	ret = socfpga_dwmac_parse_data(dwmac, dev);
	अगर (ret) अणु
		dev_err(dev, "Unable to parse OF data\n");
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->ops = ops;
	plat_dat->bsp_priv = dwmac;
	plat_dat->fix_mac_speed = socfpga_dwmac_fix_mac_speed;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	ndev = platक्रमm_get_drvdata(pdev);
	stpriv = netdev_priv(ndev);

	/* The socfpga driver needs to control the sपंचांगmac reset to set the phy
	 * mode. Create a copy of the core reset handle so it can be used by
	 * the driver later.
	 */
	dwmac->sपंचांगmac_rst = stpriv->plat->sपंचांगmac_rst;

	ret = ops->set_phy_mode(dwmac);
	अगर (ret)
		जाओ err_dvr_हटाओ;

	वापस 0;

err_dvr_हटाओ:
	sपंचांगmac_dvr_हटाओ(&pdev->dev);
err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक socfpga_dwmac_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा socfpga_dwmac *dwmac_priv = get_sपंचांगmac_bsp_priv(dev);

	dwmac_priv->ops->set_phy_mode(priv->plat->bsp_priv);

	/* Beक्रमe the enet controller is suspended, the phy is suspended.
	 * This causes the phy घड़ी to be gated. The enet controller is
	 * resumed beक्रमe the phy, so the घड़ी is still gated "off" when
	 * the enet controller is resumed. This code makes sure the phy
	 * is "resumed" beक्रमe reinitializing the enet controller since
	 * the enet controller depends on an active phy घड़ी to complete
	 * a DMA reset. A DMA reset will "time out" अगर executed
	 * with no phy घड़ी input on the Synopsys enet controller.
	 * Verअगरied through Synopsys Case #8000711656.
	 *
	 * Note that the phy घड़ी is also gated when the phy is isolated.
	 * Phy "suspend" and "isolate" controls are located in phy basic
	 * control रेजिस्टर 0, and can be modअगरied by the phy driver
	 * framework.
	 */
	अगर (ndev->phydev)
		phy_resume(ndev->phydev);

	वापस sपंचांगmac_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(socfpga_dwmac_pm_ops, sपंचांगmac_suspend,
					       socfpga_dwmac_resume);

अटल स्थिर काष्ठा socfpga_dwmac_ops socfpga_gen5_ops = अणु
	.set_phy_mode = socfpga_gen5_set_phy_mode,
पूर्ण;

अटल स्थिर काष्ठा socfpga_dwmac_ops socfpga_gen10_ops = अणु
	.set_phy_mode = socfpga_gen10_set_phy_mode,
पूर्ण;

अटल स्थिर काष्ठा of_device_id socfpga_dwmac_match[] = अणु
	अणु .compatible = "altr,socfpga-stmmac", .data = &socfpga_gen5_ops पूर्ण,
	अणु .compatible = "altr,socfpga-stmmac-a10-s10", .data = &socfpga_gen10_ops पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, socfpga_dwmac_match);

अटल काष्ठा platक्रमm_driver socfpga_dwmac_driver = अणु
	.probe  = socfpga_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "socfpga-dwmac",
		.pm		= &socfpga_dwmac_pm_ops,
		.of_match_table = socfpga_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(socfpga_dwmac_driver);

MODULE_LICENSE("GPL v2");
