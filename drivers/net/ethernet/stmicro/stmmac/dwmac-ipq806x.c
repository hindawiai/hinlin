<शैली गुरु>
/*
 * Qualcomm Atheros IPQ806x GMAC glue layer
 *
 * Copyright (C) 2015 The Linux Foundation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/of_net.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/sपंचांगmac.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/module.h>

#समावेश "stmmac_platform.h"

#घोषणा NSS_COMMON_CLK_GATE			0x8
#घोषणा NSS_COMMON_CLK_GATE_PTP_EN(x)		BIT(0x10 + x)
#घोषणा NSS_COMMON_CLK_GATE_RGMII_RX_EN(x)	BIT(0x9 + (x * 2))
#घोषणा NSS_COMMON_CLK_GATE_RGMII_TX_EN(x)	BIT(0x8 + (x * 2))
#घोषणा NSS_COMMON_CLK_GATE_GMII_RX_EN(x)	BIT(0x4 + x)
#घोषणा NSS_COMMON_CLK_GATE_GMII_TX_EN(x)	BIT(0x0 + x)

#घोषणा NSS_COMMON_CLK_DIV0			0xC
#घोषणा NSS_COMMON_CLK_DIV_OFFSET(x)		(x * 8)
#घोषणा NSS_COMMON_CLK_DIV_MASK			0x7f

#घोषणा NSS_COMMON_CLK_SRC_CTRL			0x14
#घोषणा NSS_COMMON_CLK_SRC_CTRL_OFFSET(x)	(x)
/* Mode is coded on 1 bit but is dअगरferent depending on the MAC ID:
 * MAC0: QSGMII=0 RGMII=1
 * MAC1: QSGMII=0 SGMII=0 RGMII=1
 * MAC2 & MAC3: QSGMII=0 SGMII=1
 */
#घोषणा NSS_COMMON_CLK_SRC_CTRL_RGMII(x)	1
#घोषणा NSS_COMMON_CLK_SRC_CTRL_SGMII(x)	((x >= 2) ? 1 : 0)

#घोषणा NSS_COMMON_GMAC_CTL(x)			(0x30 + (x * 4))
#घोषणा NSS_COMMON_GMAC_CTL_CSYS_REQ		BIT(19)
#घोषणा NSS_COMMON_GMAC_CTL_PHY_IFACE_SEL	BIT(16)
#घोषणा NSS_COMMON_GMAC_CTL_IFG_LIMIT_OFFSET	8
#घोषणा NSS_COMMON_GMAC_CTL_IFG_OFFSET		0

#घोषणा NSS_COMMON_CLK_DIV_RGMII_1000		1
#घोषणा NSS_COMMON_CLK_DIV_RGMII_100		9
#घोषणा NSS_COMMON_CLK_DIV_RGMII_10		99
#घोषणा NSS_COMMON_CLK_DIV_SGMII_1000		0
#घोषणा NSS_COMMON_CLK_DIV_SGMII_100		4
#घोषणा NSS_COMMON_CLK_DIV_SGMII_10		49

#घोषणा QSGMII_PCS_CAL_LCKDT_CTL		0x120
#घोषणा QSGMII_PCS_CAL_LCKDT_CTL_RST		BIT(19)

/* Only GMAC1/2/3 support SGMII and their CTL रेजिस्टर are not contiguous */
#घोषणा QSGMII_PHY_SGMII_CTL(x)			((x == 1) ? 0x134 : \
						 (0x13c + (4 * (x - 2))))
#घोषणा QSGMII_PHY_CDR_EN			BIT(0)
#घोषणा QSGMII_PHY_RX_FRONT_EN			BIT(1)
#घोषणा QSGMII_PHY_RX_SIGNAL_DETECT_EN		BIT(2)
#घोषणा QSGMII_PHY_TX_DRIVER_EN			BIT(3)
#घोषणा QSGMII_PHY_QSGMII_EN			BIT(7)
#घोषणा QSGMII_PHY_PHASE_LOOP_GAIN_OFFSET	12
#घोषणा QSGMII_PHY_RX_DC_BIAS_OFFSET		18
#घोषणा QSGMII_PHY_RX_INPUT_EQU_OFFSET		20
#घोषणा QSGMII_PHY_CDR_PI_SLEW_OFFSET		22
#घोषणा QSGMII_PHY_TX_DRV_AMP_OFFSET		28

काष्ठा ipq806x_gmac अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *nss_common;
	काष्ठा regmap *qsgmii_csr;
	uपूर्णांक32_t id;
	काष्ठा clk *core_clk;
	phy_पूर्णांकerface_t phy_mode;
पूर्ण;

अटल पूर्णांक get_clk_भाग_sgmii(काष्ठा ipq806x_gmac *gmac, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा device *dev = &gmac->pdev->dev;
	पूर्णांक भाग;

	चयन (speed) अणु
	हाल SPEED_1000:
		भाग = NSS_COMMON_CLK_DIV_SGMII_1000;
		अवरोध;

	हाल SPEED_100:
		भाग = NSS_COMMON_CLK_DIV_SGMII_100;
		अवरोध;

	हाल SPEED_10:
		भाग = NSS_COMMON_CLK_DIV_SGMII_10;
		अवरोध;

	शेष:
		dev_err(dev, "Speed %dMbps not supported in SGMII\n", speed);
		वापस -EINVAL;
	पूर्ण

	वापस भाग;
पूर्ण

अटल पूर्णांक get_clk_भाग_rgmii(काष्ठा ipq806x_gmac *gmac, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा device *dev = &gmac->pdev->dev;
	पूर्णांक भाग;

	चयन (speed) अणु
	हाल SPEED_1000:
		भाग = NSS_COMMON_CLK_DIV_RGMII_1000;
		अवरोध;

	हाल SPEED_100:
		भाग = NSS_COMMON_CLK_DIV_RGMII_100;
		अवरोध;

	हाल SPEED_10:
		भाग = NSS_COMMON_CLK_DIV_RGMII_10;
		अवरोध;

	शेष:
		dev_err(dev, "Speed %dMbps not supported in RGMII\n", speed);
		वापस -EINVAL;
	पूर्ण

	वापस भाग;
पूर्ण

अटल पूर्णांक ipq806x_gmac_set_speed(काष्ठा ipq806x_gmac *gmac, अचिन्हित पूर्णांक speed)
अणु
	uपूर्णांक32_t clk_bits, val;
	पूर्णांक भाग;

	चयन (gmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		भाग = get_clk_भाग_rgmii(gmac, speed);
		clk_bits = NSS_COMMON_CLK_GATE_RGMII_RX_EN(gmac->id) |
			   NSS_COMMON_CLK_GATE_RGMII_TX_EN(gmac->id);
		अवरोध;

	हाल PHY_INTERFACE_MODE_SGMII:
		भाग = get_clk_भाग_sgmii(gmac, speed);
		clk_bits = NSS_COMMON_CLK_GATE_GMII_RX_EN(gmac->id) |
			   NSS_COMMON_CLK_GATE_GMII_TX_EN(gmac->id);
		अवरोध;

	शेष:
		dev_err(&gmac->pdev->dev, "Unsupported PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		वापस -EINVAL;
	पूर्ण

	/* Disable the घड़ीs */
	regmap_पढ़ो(gmac->nss_common, NSS_COMMON_CLK_GATE, &val);
	val &= ~clk_bits;
	regmap_ग_लिखो(gmac->nss_common, NSS_COMMON_CLK_GATE, val);

	/* Set the भागider */
	regmap_पढ़ो(gmac->nss_common, NSS_COMMON_CLK_DIV0, &val);
	val &= ~(NSS_COMMON_CLK_DIV_MASK
		 << NSS_COMMON_CLK_DIV_OFFSET(gmac->id));
	val |= भाग << NSS_COMMON_CLK_DIV_OFFSET(gmac->id);
	regmap_ग_लिखो(gmac->nss_common, NSS_COMMON_CLK_DIV0, val);

	/* Enable the घड़ी back */
	regmap_पढ़ो(gmac->nss_common, NSS_COMMON_CLK_GATE, &val);
	val |= clk_bits;
	regmap_ग_लिखो(gmac->nss_common, NSS_COMMON_CLK_GATE, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ipq806x_gmac_of_parse(काष्ठा ipq806x_gmac *gmac)
अणु
	काष्ठा device *dev = &gmac->pdev->dev;
	पूर्णांक ret;

	ret = of_get_phy_mode(dev->of_node, &gmac->phy_mode);
	अगर (ret) अणु
		dev_err(dev, "missing phy mode property\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "qcom,id", &gmac->id) < 0) अणु
		dev_err(dev, "missing qcom id property\n");
		वापस -EINVAL;
	पूर्ण

	/* The GMACs are called 1 to 4 in the करोcumentation, but to simplअगरy the
	 * code and keep it consistent with the Linux convention, we'll number
	 * them from 0 to 3 here.
	 */
	अगर (gmac->id > 3) अणु
		dev_err(dev, "invalid gmac id\n");
		वापस -EINVAL;
	पूर्ण

	gmac->core_clk = devm_clk_get(dev, "stmmaceth");
	अगर (IS_ERR(gmac->core_clk)) अणु
		dev_err(dev, "missing stmmaceth clk property\n");
		वापस PTR_ERR(gmac->core_clk);
	पूर्ण
	clk_set_rate(gmac->core_clk, 266000000);

	/* Setup the रेजिस्टर map क्रम the nss common रेजिस्टरs */
	gmac->nss_common = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "qcom,nss-common");
	अगर (IS_ERR(gmac->nss_common)) अणु
		dev_err(dev, "missing nss-common node\n");
		वापस PTR_ERR(gmac->nss_common);
	पूर्ण

	/* Setup the रेजिस्टर map क्रम the qsgmii csr रेजिस्टरs */
	gmac->qsgmii_csr = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "qcom,qsgmii-csr");
	अगर (IS_ERR(gmac->qsgmii_csr))
		dev_err(dev, "missing qsgmii-csr node\n");

	वापस PTR_ERR_OR_ZERO(gmac->qsgmii_csr);
पूर्ण

अटल व्योम ipq806x_gmac_fix_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा ipq806x_gmac *gmac = priv;

	ipq806x_gmac_set_speed(gmac, speed);
पूर्ण

अटल पूर्णांक ipq806x_gmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ipq806x_gmac *gmac;
	पूर्णांक val;
	पूर्णांक err;

	val = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (val)
		वापस val;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	gmac = devm_kzalloc(dev, माप(*gmac), GFP_KERNEL);
	अगर (!gmac) अणु
		err = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	gmac->pdev = pdev;

	err = ipq806x_gmac_of_parse(gmac);
	अगर (err) अणु
		dev_err(dev, "device tree parsing error\n");
		जाओ err_हटाओ_config_dt;
	पूर्ण

	regmap_ग_लिखो(gmac->qsgmii_csr, QSGMII_PCS_CAL_LCKDT_CTL,
		     QSGMII_PCS_CAL_LCKDT_CTL_RST);

	/* Inter frame gap is set to 12 */
	val = 12 << NSS_COMMON_GMAC_CTL_IFG_OFFSET |
	      12 << NSS_COMMON_GMAC_CTL_IFG_LIMIT_OFFSET;
	/* We also initiate an AXI low घातer निकास request */
	val |= NSS_COMMON_GMAC_CTL_CSYS_REQ;
	चयन (gmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		val |= NSS_COMMON_GMAC_CTL_PHY_IFACE_SEL;
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		val &= ~NSS_COMMON_GMAC_CTL_PHY_IFACE_SEL;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		err = -EINVAL;
		जाओ err_हटाओ_config_dt;
	पूर्ण
	regmap_ग_लिखो(gmac->nss_common, NSS_COMMON_GMAC_CTL(gmac->id), val);

	/* Configure the घड़ी src according to the mode */
	regmap_पढ़ो(gmac->nss_common, NSS_COMMON_CLK_SRC_CTRL, &val);
	val &= ~(1 << NSS_COMMON_CLK_SRC_CTRL_OFFSET(gmac->id));
	चयन (gmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		val |= NSS_COMMON_CLK_SRC_CTRL_RGMII(gmac->id) <<
			NSS_COMMON_CLK_SRC_CTRL_OFFSET(gmac->id);
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		val |= NSS_COMMON_CLK_SRC_CTRL_SGMII(gmac->id) <<
			NSS_COMMON_CLK_SRC_CTRL_OFFSET(gmac->id);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported PHY mode: \"%s\"\n",
			phy_modes(gmac->phy_mode));
		err = -EINVAL;
		जाओ err_हटाओ_config_dt;
	पूर्ण
	regmap_ग_लिखो(gmac->nss_common, NSS_COMMON_CLK_SRC_CTRL, val);

	/* Enable PTP घड़ी */
	regmap_पढ़ो(gmac->nss_common, NSS_COMMON_CLK_GATE, &val);
	val |= NSS_COMMON_CLK_GATE_PTP_EN(gmac->id);
	चयन (gmac->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		val |= NSS_COMMON_CLK_GATE_RGMII_RX_EN(gmac->id) |
			NSS_COMMON_CLK_GATE_RGMII_TX_EN(gmac->id);
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		val |= NSS_COMMON_CLK_GATE_GMII_RX_EN(gmac->id) |
				NSS_COMMON_CLK_GATE_GMII_TX_EN(gmac->id);
		अवरोध;
	शेष:
		/* We करोn't get here; the चयन above will have errored out */
		unreachable();
	पूर्ण
	regmap_ग_लिखो(gmac->nss_common, NSS_COMMON_CLK_GATE, val);

	अगर (gmac->phy_mode == PHY_INTERFACE_MODE_SGMII) अणु
		regmap_ग_लिखो(gmac->qsgmii_csr, QSGMII_PHY_SGMII_CTL(gmac->id),
			     QSGMII_PHY_CDR_EN |
			     QSGMII_PHY_RX_FRONT_EN |
			     QSGMII_PHY_RX_SIGNAL_DETECT_EN |
			     QSGMII_PHY_TX_DRIVER_EN |
			     QSGMII_PHY_QSGMII_EN |
			     0x4ul << QSGMII_PHY_PHASE_LOOP_GAIN_OFFSET |
			     0x3ul << QSGMII_PHY_RX_DC_BIAS_OFFSET |
			     0x1ul << QSGMII_PHY_RX_INPUT_EQU_OFFSET |
			     0x2ul << QSGMII_PHY_CDR_PI_SLEW_OFFSET |
			     0xCul << QSGMII_PHY_TX_DRV_AMP_OFFSET);
	पूर्ण

	plat_dat->has_gmac = true;
	plat_dat->bsp_priv = gmac;
	plat_dat->fix_mac_speed = ipq806x_gmac_fix_mac_speed;
	plat_dat->multicast_filter_bins = 0;
	plat_dat->tx_fअगरo_size = 8192;
	plat_dat->rx_fअगरo_size = 8192;

	err = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (err)
		जाओ err_हटाओ_config_dt;

	वापस 0;

err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id ipq806x_gmac_dwmac_match[] = अणु
	अणु .compatible = "qcom,ipq806x-gmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ipq806x_gmac_dwmac_match);

अटल काष्ठा platक्रमm_driver ipq806x_gmac_dwmac_driver = अणु
	.probe = ipq806x_gmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name		= "ipq806x-gmac-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table	= ipq806x_gmac_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ipq806x_gmac_dwmac_driver);

MODULE_AUTHOR("Mathieu Olivari <mathieu@codeaurora.org>");
MODULE_DESCRIPTION("Qualcomm Atheros IPQ806x DWMAC specific glue layer");
MODULE_LICENSE("Dual BSD/GPL");
