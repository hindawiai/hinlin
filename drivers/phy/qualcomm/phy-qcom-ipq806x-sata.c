<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>

काष्ठा qcom_ipq806x_sata_phy अणु
	व्योम __iomem *mmio;
	काष्ठा clk *cfg_clk;
	काष्ठा device *dev;
पूर्ण;

#घोषणा __set(v, a, b)	(((v) << (b)) & GENMASK(a, b))

#घोषणा SATA_PHY_P0_PARAM0		0x200
#घोषणा SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN3(x)	__set(x, 17, 12)
#घोषणा SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN3_MASK	GENMASK(17, 12)
#घोषणा SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN2(x)	__set(x, 11, 6)
#घोषणा SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN2_MASK	GENMASK(11, 6)
#घोषणा SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN1(x)	__set(x, 5, 0)
#घोषणा SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN1_MASK	GENMASK(5, 0)

#घोषणा SATA_PHY_P0_PARAM1		0x204
#घोषणा SATA_PHY_P0_PARAM1_RESERVED_BITS31_21(x)	__set(x, 31, 21)
#घोषणा SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN3(x)	__set(x, 20, 14)
#घोषणा SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN3_MASK	GENMASK(20, 14)
#घोषणा SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN2(x)	__set(x, 13, 7)
#घोषणा SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN2_MASK	GENMASK(13, 7)
#घोषणा SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN1(x)	__set(x, 6, 0)
#घोषणा SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN1_MASK	GENMASK(6, 0)

#घोषणा SATA_PHY_P0_PARAM2		0x208
#घोषणा SATA_PHY_P0_PARAM2_RX_EQ(x)	__set(x, 20, 18)
#घोषणा SATA_PHY_P0_PARAM2_RX_EQ_MASK	GENMASK(20, 18)

#घोषणा SATA_PHY_P0_PARAM3		0x20C
#घोषणा SATA_PHY_SSC_EN			0x8
#घोषणा SATA_PHY_P0_PARAM4		0x210
#घोषणा SATA_PHY_REF_SSP_EN		0x2
#घोषणा SATA_PHY_RESET			0x1

अटल पूर्णांक qcom_ipq806x_sata_phy_init(काष्ठा phy *generic_phy)
अणु
	काष्ठा qcom_ipq806x_sata_phy *phy = phy_get_drvdata(generic_phy);
	u32 reg;

	/* Setting SSC_EN to 1 */
	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM3);
	reg = reg | SATA_PHY_SSC_EN;
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM3);

	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM0) &
			~(SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN3_MASK |
			  SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN2_MASK |
			  SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN1_MASK);
	reg |= SATA_PHY_P0_PARAM0_P0_TX_PREEMPH_GEN3(0xf);
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM0);

	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM1) &
			~(SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN3_MASK |
			  SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN2_MASK |
			  SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN1_MASK);
	reg |= SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN3(0x55) |
		SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN2(0x55) |
		SATA_PHY_P0_PARAM1_P0_TX_AMPLITUDE_GEN1(0x55);
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM1);

	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM2) &
		~SATA_PHY_P0_PARAM2_RX_EQ_MASK;
	reg |= SATA_PHY_P0_PARAM2_RX_EQ(0x3);
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM2);

	/* Setting PHY_RESET to 1 */
	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM4);
	reg = reg | SATA_PHY_RESET;
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM4);

	/* Setting REF_SSP_EN to 1 */
	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM4);
	reg = reg | SATA_PHY_REF_SSP_EN | SATA_PHY_RESET;
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM4);

	/* make sure all changes complete beक्रमe we let the PHY out of reset */
	mb();

	/* sleep क्रम max. 50us more to combine processor wakeups */
	usleep_range(20, 20 + 50);

	/* Clearing PHY_RESET to 0 */
	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM4);
	reg = reg & ~SATA_PHY_RESET;
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM4);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_ipq806x_sata_phy_निकास(काष्ठा phy *generic_phy)
अणु
	काष्ठा qcom_ipq806x_sata_phy *phy = phy_get_drvdata(generic_phy);
	u32 reg;

	/* Setting PHY_RESET to 1 */
	reg = पढ़ोl_relaxed(phy->mmio + SATA_PHY_P0_PARAM4);
	reg = reg | SATA_PHY_RESET;
	ग_लिखोl_relaxed(reg, phy->mmio + SATA_PHY_P0_PARAM4);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_ipq806x_sata_phy_ops = अणु
	.init		= qcom_ipq806x_sata_phy_init,
	.निकास		= qcom_ipq806x_sata_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक qcom_ipq806x_sata_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_ipq806x_sata_phy *phy;
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

	generic_phy = devm_phy_create(dev, शून्य, &qcom_ipq806x_sata_phy_ops);
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

अटल पूर्णांक qcom_ipq806x_sata_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_ipq806x_sata_phy *phy = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(phy->cfg_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_ipq806x_sata_phy_of_match[] = अणु
	अणु .compatible = "qcom,ipq806x-sata-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_ipq806x_sata_phy_of_match);

अटल काष्ठा platक्रमm_driver qcom_ipq806x_sata_phy_driver = अणु
	.probe	= qcom_ipq806x_sata_phy_probe,
	.हटाओ	= qcom_ipq806x_sata_phy_हटाओ,
	.driver = अणु
		.name	= "qcom-ipq806x-sata-phy",
		.of_match_table	= qcom_ipq806x_sata_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(qcom_ipq806x_sata_phy_driver);

MODULE_DESCRIPTION("QCOM IPQ806x SATA PHY driver");
MODULE_LICENSE("GPL v2");
