<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>

/* PHY रेजिस्टरs */
#घोषणा UNIPHY_PLL_REFCLK_CFG		0x000
#घोषणा UNIPHY_PLL_PWRGEN_CFG		0x014
#घोषणा UNIPHY_PLL_GLB_CFG		0x020
#घोषणा UNIPHY_PLL_SDM_CFG0		0x038
#घोषणा UNIPHY_PLL_SDM_CFG1		0x03C
#घोषणा UNIPHY_PLL_SDM_CFG2		0x040
#घोषणा UNIPHY_PLL_SDM_CFG3		0x044
#घोषणा UNIPHY_PLL_SDM_CFG4		0x048
#घोषणा UNIPHY_PLL_SSC_CFG0		0x04C
#घोषणा UNIPHY_PLL_SSC_CFG1		0x050
#घोषणा UNIPHY_PLL_SSC_CFG2		0x054
#घोषणा UNIPHY_PLL_SSC_CFG3		0x058
#घोषणा UNIPHY_PLL_LKDET_CFG0		0x05C
#घोषणा UNIPHY_PLL_LKDET_CFG1		0x060
#घोषणा UNIPHY_PLL_LKDET_CFG2		0x064
#घोषणा UNIPHY_PLL_CAL_CFG0		0x06C
#घोषणा UNIPHY_PLL_CAL_CFG8		0x08C
#घोषणा UNIPHY_PLL_CAL_CFG9		0x090
#घोषणा UNIPHY_PLL_CAL_CFG10		0x094
#घोषणा UNIPHY_PLL_CAL_CFG11		0x098
#घोषणा UNIPHY_PLL_STATUS		0x0C0

#घोषणा SATA_PHY_SER_CTRL		0x100
#घोषणा SATA_PHY_TX_DRIV_CTRL0		0x104
#घोषणा SATA_PHY_TX_DRIV_CTRL1		0x108
#घोषणा SATA_PHY_TX_IMCAL0		0x11C
#घोषणा SATA_PHY_TX_IMCAL2		0x124
#घोषणा SATA_PHY_RX_IMCAL0		0x128
#घोषणा SATA_PHY_EQUAL			0x13C
#घोषणा SATA_PHY_OOB_TERM		0x144
#घोषणा SATA_PHY_CDR_CTRL0		0x148
#घोषणा SATA_PHY_CDR_CTRL1		0x14C
#घोषणा SATA_PHY_CDR_CTRL2		0x150
#घोषणा SATA_PHY_CDR_CTRL3		0x154
#घोषणा SATA_PHY_PI_CTRL0		0x168
#घोषणा SATA_PHY_POW_DWN_CTRL0		0x180
#घोषणा SATA_PHY_POW_DWN_CTRL1		0x184
#घोषणा SATA_PHY_TX_DATA_CTRL		0x188
#घोषणा SATA_PHY_ALIGNP			0x1A4
#घोषणा SATA_PHY_TX_IMCAL_STAT		0x1E4
#घोषणा SATA_PHY_RX_IMCAL_STAT		0x1E8

#घोषणा UNIPHY_PLL_LOCK		BIT(0)
#घोषणा SATA_PHY_TX_CAL		BIT(0)
#घोषणा SATA_PHY_RX_CAL		BIT(0)

/* शेष समयout set to 1 sec */
#घोषणा TIMEOUT_MS		10000
#घोषणा DELAY_INTERVAL_US	100

काष्ठा qcom_apq8064_sata_phy अणु
	व्योम __iomem *mmio;
	काष्ठा clk *cfg_clk;
	काष्ठा device *dev;
पूर्ण;

/* Helper function to करो poll and समयout */
अटल पूर्णांक poll_समयout(व्योम __iomem *addr, u32 mask)
अणु
	u32 val;

	वापस पढ़ोl_relaxed_poll_समयout(addr, val, (val & mask),
					DELAY_INTERVAL_US, TIMEOUT_MS * 1000);
पूर्ण

अटल पूर्णांक qcom_apq8064_sata_phy_init(काष्ठा phy *generic_phy)
अणु
	काष्ठा qcom_apq8064_sata_phy *phy = phy_get_drvdata(generic_phy);
	व्योम __iomem *base = phy->mmio;
	पूर्णांक ret = 0;

	/* SATA phy initialization */
	ग_लिखोl_relaxed(0x01, base + SATA_PHY_SER_CTRL);
	ग_लिखोl_relaxed(0xB1, base + SATA_PHY_POW_DWN_CTRL0);
	/* Make sure the घातer करोwn happens beक्रमe घातer up */
	mb();
	usleep_range(10, 60);

	ग_लिखोl_relaxed(0x01, base + SATA_PHY_POW_DWN_CTRL0);
	ग_लिखोl_relaxed(0x3E, base + SATA_PHY_POW_DWN_CTRL1);
	ग_लिखोl_relaxed(0x01, base + SATA_PHY_RX_IMCAL0);
	ग_लिखोl_relaxed(0x01, base + SATA_PHY_TX_IMCAL0);
	ग_लिखोl_relaxed(0x02, base + SATA_PHY_TX_IMCAL2);

	/* Write UNIPHYPLL रेजिस्टरs to configure PLL */
	ग_लिखोl_relaxed(0x04, base + UNIPHY_PLL_REFCLK_CFG);
	ग_लिखोl_relaxed(0x00, base + UNIPHY_PLL_PWRGEN_CFG);

	ग_लिखोl_relaxed(0x0A, base + UNIPHY_PLL_CAL_CFG0);
	ग_लिखोl_relaxed(0xF3, base + UNIPHY_PLL_CAL_CFG8);
	ग_लिखोl_relaxed(0x01, base + UNIPHY_PLL_CAL_CFG9);
	ग_लिखोl_relaxed(0xED, base + UNIPHY_PLL_CAL_CFG10);
	ग_लिखोl_relaxed(0x02, base + UNIPHY_PLL_CAL_CFG11);

	ग_लिखोl_relaxed(0x36, base + UNIPHY_PLL_SDM_CFG0);
	ग_लिखोl_relaxed(0x0D, base + UNIPHY_PLL_SDM_CFG1);
	ग_लिखोl_relaxed(0xA3, base + UNIPHY_PLL_SDM_CFG2);
	ग_लिखोl_relaxed(0xF0, base + UNIPHY_PLL_SDM_CFG3);
	ग_लिखोl_relaxed(0x00, base + UNIPHY_PLL_SDM_CFG4);

	ग_लिखोl_relaxed(0x19, base + UNIPHY_PLL_SSC_CFG0);
	ग_लिखोl_relaxed(0xE1, base + UNIPHY_PLL_SSC_CFG1);
	ग_लिखोl_relaxed(0x00, base + UNIPHY_PLL_SSC_CFG2);
	ग_लिखोl_relaxed(0x11, base + UNIPHY_PLL_SSC_CFG3);

	ग_लिखोl_relaxed(0x04, base + UNIPHY_PLL_LKDET_CFG0);
	ग_लिखोl_relaxed(0xFF, base + UNIPHY_PLL_LKDET_CFG1);

	ग_लिखोl_relaxed(0x02, base + UNIPHY_PLL_GLB_CFG);
	/* make sure global config LDO घातer करोwn happens beक्रमe घातer up */
	mb();

	ग_लिखोl_relaxed(0x03, base + UNIPHY_PLL_GLB_CFG);
	ग_लिखोl_relaxed(0x05, base + UNIPHY_PLL_LKDET_CFG2);

	/* PLL Lock रुको */
	ret = poll_समयout(base + UNIPHY_PLL_STATUS, UNIPHY_PLL_LOCK);
	अगर (ret) अणु
		dev_err(phy->dev, "poll timeout UNIPHY_PLL_STATUS\n");
		वापस ret;
	पूर्ण

	/* TX Calibration */
	ret = poll_समयout(base + SATA_PHY_TX_IMCAL_STAT, SATA_PHY_TX_CAL);
	अगर (ret) अणु
		dev_err(phy->dev, "poll timeout SATA_PHY_TX_IMCAL_STAT\n");
		वापस ret;
	पूर्ण

	/* RX Calibration */
	ret = poll_समयout(base + SATA_PHY_RX_IMCAL_STAT, SATA_PHY_RX_CAL);
	अगर (ret) अणु
		dev_err(phy->dev, "poll timeout SATA_PHY_RX_IMCAL_STAT\n");
		वापस ret;
	पूर्ण

	/* SATA phy calibrated succesfully, घातer up to functional mode */
	ग_लिखोl_relaxed(0x3E, base + SATA_PHY_POW_DWN_CTRL1);
	ग_लिखोl_relaxed(0x01, base + SATA_PHY_RX_IMCAL0);
	ग_लिखोl_relaxed(0x01, base + SATA_PHY_TX_IMCAL0);

	ग_लिखोl_relaxed(0x00, base + SATA_PHY_POW_DWN_CTRL1);
	ग_लिखोl_relaxed(0x59, base + SATA_PHY_CDR_CTRL0);
	ग_लिखोl_relaxed(0x04, base + SATA_PHY_CDR_CTRL1);
	ग_लिखोl_relaxed(0x00, base + SATA_PHY_CDR_CTRL2);
	ग_लिखोl_relaxed(0x00, base + SATA_PHY_PI_CTRL0);
	ग_लिखोl_relaxed(0x00, base + SATA_PHY_CDR_CTRL3);
	ग_लिखोl_relaxed(0x01, base + SATA_PHY_POW_DWN_CTRL0);

	ग_लिखोl_relaxed(0x11, base + SATA_PHY_TX_DATA_CTRL);
	ग_लिखोl_relaxed(0x43, base + SATA_PHY_ALIGNP);
	ग_लिखोl_relaxed(0x04, base + SATA_PHY_OOB_TERM);

	ग_लिखोl_relaxed(0x01, base + SATA_PHY_EQUAL);
	ग_लिखोl_relaxed(0x09, base + SATA_PHY_TX_DRIV_CTRL0);
	ग_लिखोl_relaxed(0x09, base + SATA_PHY_TX_DRIV_CTRL1);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_apq8064_sata_phy_निकास(काष्ठा phy *generic_phy)
अणु
	काष्ठा qcom_apq8064_sata_phy *phy = phy_get_drvdata(generic_phy);
	व्योम __iomem *base = phy->mmio;

	/* Power करोwn PHY */
	ग_लिखोl_relaxed(0xF8, base + SATA_PHY_POW_DWN_CTRL0);
	ग_लिखोl_relaxed(0xFE, base + SATA_PHY_POW_DWN_CTRL1);

	/* Power करोwn PLL block */
	ग_लिखोl_relaxed(0x00, base + UNIPHY_PLL_GLB_CFG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_apq8064_sata_phy_ops = अणु
	.init		= qcom_apq8064_sata_phy_init,
	.निकास		= qcom_apq8064_sata_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक qcom_apq8064_sata_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_apq8064_sata_phy *phy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *generic_phy;
	पूर्णांक ret;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->mmio))
		वापस PTR_ERR(phy->mmio);

	generic_phy = devm_phy_create(dev, शून्य, &qcom_apq8064_sata_phy_ops);
	अगर (IS_ERR(generic_phy)) अणु
		dev_err(dev, "%s: failed to create phy\n", __func__);
		वापस PTR_ERR(generic_phy);
	पूर्ण

	phy->dev = dev;
	phy_set_drvdata(generic_phy, phy);
	platक्रमm_set_drvdata(pdev, phy);

	phy->cfg_clk = devm_clk_get(dev, "cfg");
	अगर (IS_ERR(phy->cfg_clk)) अणु
		dev_err(dev, "Failed to get sata cfg clock\n");
		वापस PTR_ERR(phy->cfg_clk);
	पूर्ण

	ret = clk_prepare_enable(phy->cfg_clk);
	अगर (ret)
		वापस ret;

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		clk_disable_unprepare(phy->cfg_clk);
		dev_err(dev, "%s: failed to register phy\n", __func__);
		वापस PTR_ERR(phy_provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_apq8064_sata_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_apq8064_sata_phy *phy = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(phy->cfg_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_apq8064_sata_phy_of_match[] = अणु
	अणु .compatible = "qcom,apq8064-sata-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_apq8064_sata_phy_of_match);

अटल काष्ठा platक्रमm_driver qcom_apq8064_sata_phy_driver = अणु
	.probe	= qcom_apq8064_sata_phy_probe,
	.हटाओ	= qcom_apq8064_sata_phy_हटाओ,
	.driver = अणु
		.name	= "qcom-apq8064-sata-phy",
		.of_match_table	= qcom_apq8064_sata_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(qcom_apq8064_sata_phy_driver);

MODULE_DESCRIPTION("QCOM apq8064 SATA PHY driver");
MODULE_LICENSE("GPL v2");
