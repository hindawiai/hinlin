<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Adaptrum Anarion DWMAC glue layer
 *
 * Copyright (C) 2017, Adaptrum, Inc.
 * (Written by Alexandru Gagniuc <alex.g at adaptrum.com> क्रम Adaptrum, Inc.)
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

#घोषणा GMAC_RESET_CONTROL_REG		0
#घोषणा GMAC_SW_CONFIG_REG		4
#घोषणा  GMAC_CONFIG_INTF_SEL_MASK	(0x7 << 0)
#घोषणा  GMAC_CONFIG_INTF_RGMII		(0x1 << 0)

काष्ठा anarion_gmac अणु
	uपूर्णांकptr_t ctl_block;
	uपूर्णांक32_t phy_पूर्णांकf_sel;
पूर्ण;

अटल uपूर्णांक32_t gmac_पढ़ो_reg(काष्ठा anarion_gmac *gmac, uपूर्णांक8_t reg)
अणु
	वापस पढ़ोl((व्योम *)(gmac->ctl_block + reg));
पूर्ण;

अटल व्योम gmac_ग_लिखो_reg(काष्ठा anarion_gmac *gmac, uपूर्णांक8_t reg, uपूर्णांक32_t val)
अणु
	ग_लिखोl(val, (व्योम *)(gmac->ctl_block + reg));
पूर्ण

अटल पूर्णांक anarion_gmac_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	uपूर्णांक32_t sw_config;
	काष्ठा anarion_gmac *gmac = priv;

	/* Reset logic, configure पूर्णांकerface mode, then release reset. SIMPLE! */
	gmac_ग_लिखो_reg(gmac, GMAC_RESET_CONTROL_REG, 1);

	sw_config = gmac_पढ़ो_reg(gmac, GMAC_SW_CONFIG_REG);
	sw_config &= ~GMAC_CONFIG_INTF_SEL_MASK;
	sw_config |= (gmac->phy_पूर्णांकf_sel & GMAC_CONFIG_INTF_SEL_MASK);
	gmac_ग_लिखो_reg(gmac, GMAC_SW_CONFIG_REG, sw_config);

	gmac_ग_लिखो_reg(gmac, GMAC_RESET_CONTROL_REG, 0);

	वापस 0;
पूर्ण

अटल व्योम anarion_gmac_निकास(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा anarion_gmac *gmac = priv;

	gmac_ग_लिखो_reg(gmac, GMAC_RESET_CONTROL_REG, 1);
पूर्ण

अटल काष्ठा anarion_gmac *anarion_config_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा anarion_gmac *gmac;
	phy_पूर्णांकerface_t phy_mode;
	व्योम __iomem *ctl_block;
	पूर्णांक err;

	ctl_block = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(ctl_block)) अणु
		dev_err(&pdev->dev, "Cannot get reset region (%ld)!\n",
			PTR_ERR(ctl_block));
		वापस ctl_block;
	पूर्ण

	gmac = devm_kzalloc(&pdev->dev, माप(*gmac), GFP_KERNEL);
	अगर (!gmac)
		वापस ERR_PTR(-ENOMEM);

	gmac->ctl_block = (uपूर्णांकptr_t)ctl_block;

	err = of_get_phy_mode(pdev->dev.of_node, &phy_mode);
	अगर (err)
		वापस ERR_PTR(err);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		fallthrough;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		gmac->phy_पूर्णांकf_sel = GMAC_CONFIG_INTF_RGMII;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported phy-mode (%d)\n",
			phy_mode);
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण

	वापस gmac;
पूर्ण

अटल पूर्णांक anarion_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा anarion_gmac *gmac;
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	gmac = anarion_config_dt(pdev);
	अगर (IS_ERR(gmac))
		वापस PTR_ERR(gmac);

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	plat_dat->init = anarion_gmac_init;
	plat_dat->निकास = anarion_gmac_निकास;
	anarion_gmac_init(pdev, gmac);
	plat_dat->bsp_priv = gmac;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret) अणु
		sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id anarion_dwmac_match[] = अणु
	अणु .compatible = "adaptrum,anarion-gmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, anarion_dwmac_match);

अटल काष्ठा platक्रमm_driver anarion_dwmac_driver = अणु
	.probe  = anarion_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "anarion-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = anarion_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(anarion_dwmac_driver);

MODULE_DESCRIPTION("Adaptrum Anarion DWMAC specific glue layer");
MODULE_AUTHOR("Alexandru Gagniuc <mr.nuke.me@gmail.com>");
MODULE_LICENSE("GPL v2");
