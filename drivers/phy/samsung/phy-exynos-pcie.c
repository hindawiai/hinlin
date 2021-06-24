<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung Exynos SoC series PCIe PHY driver
 *
 * Phy provider क्रम PCIe controller on Exynos SoC series
 *
 * Copyright (C) 2017-2020 Samsung Electronics Co., Ltd.
 * Jaehoon Chung <jh80.chung@samsung.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>

#घोषणा PCIE_PHY_OFFSET(x)		((x) * 0x4)

/* Sysreg FSYS रेजिस्टर offsets and bits क्रम Exynos5433 */
#घोषणा PCIE_EXYNOS5433_PHY_MAC_RESET		0x0208
#घोषणा PCIE_MAC_RESET_MASK			0xFF
#घोषणा PCIE_MAC_RESET				BIT(4)
#घोषणा PCIE_EXYNOS5433_PHY_L1SUB_CM_CON	0x1010
#घोषणा PCIE_REFCLK_GATING_EN			BIT(0)
#घोषणा PCIE_EXYNOS5433_PHY_COMMON_RESET	0x1020
#घोषणा PCIE_PHY_RESET				BIT(0)
#घोषणा PCIE_EXYNOS5433_PHY_GLOBAL_RESET	0x1040
#घोषणा PCIE_GLOBAL_RESET			BIT(0)
#घोषणा PCIE_REFCLK				BIT(1)
#घोषणा PCIE_REFCLK_MASK			0x16
#घोषणा PCIE_APP_REQ_EXIT_L1_MODE		BIT(5)

/* PMU PCIE PHY isolation control */
#घोषणा EXYNOS5433_PMU_PCIE_PHY_OFFSET		0x730

/* For Exynos pcie phy */
काष्ठा exynos_pcie_phy अणु
	व्योम __iomem *base;
	काष्ठा regmap *pmureg;
	काष्ठा regmap *fsysreg;
पूर्ण;

अटल व्योम exynos_pcie_phy_ग_लिखोl(व्योम __iomem *base, u32 val, u32 offset)
अणु
	ग_लिखोl(val, base + offset);
पूर्ण

/* Exynos5433 specअगरic functions */
अटल पूर्णांक exynos5433_pcie_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा exynos_pcie_phy *ep = phy_get_drvdata(phy);

	regmap_update_bits(ep->fsysreg,	PCIE_EXYNOS5433_PHY_COMMON_RESET,
			   PCIE_PHY_RESET, 1);
	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_MAC_RESET,
			   PCIE_MAC_RESET, 0);

	/* PHY refclk 24MHz */
	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_GLOBAL_RESET,
			   PCIE_REFCLK_MASK, PCIE_REFCLK);
	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_GLOBAL_RESET,
			   PCIE_GLOBAL_RESET, 0);


	exynos_pcie_phy_ग_लिखोl(ep->base, 0x11, PCIE_PHY_OFFSET(0x3));

	/* band gap reference on */
	exynos_pcie_phy_ग_लिखोl(ep->base, 0, PCIE_PHY_OFFSET(0x20));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0, PCIE_PHY_OFFSET(0x4b));

	/* jitter tuning */
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x34, PCIE_PHY_OFFSET(0x4));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x02, PCIE_PHY_OFFSET(0x7));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x41, PCIE_PHY_OFFSET(0x21));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x7F, PCIE_PHY_OFFSET(0x14));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0xC0, PCIE_PHY_OFFSET(0x15));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x61, PCIE_PHY_OFFSET(0x36));

	/* D0 uninit.. */
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x44, PCIE_PHY_OFFSET(0x3D));

	/* 24MHz */
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x94, PCIE_PHY_OFFSET(0x8));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0xA7, PCIE_PHY_OFFSET(0x9));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x93, PCIE_PHY_OFFSET(0xA));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x6B, PCIE_PHY_OFFSET(0xC));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0xA5, PCIE_PHY_OFFSET(0xF));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x34, PCIE_PHY_OFFSET(0x16));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0xA3, PCIE_PHY_OFFSET(0x17));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0xA7, PCIE_PHY_OFFSET(0x1A));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x71, PCIE_PHY_OFFSET(0x23));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x4C, PCIE_PHY_OFFSET(0x24));

	exynos_pcie_phy_ग_लिखोl(ep->base, 0x0E, PCIE_PHY_OFFSET(0x26));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x14, PCIE_PHY_OFFSET(0x7));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x48, PCIE_PHY_OFFSET(0x43));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x44, PCIE_PHY_OFFSET(0x44));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x03, PCIE_PHY_OFFSET(0x45));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0xA7, PCIE_PHY_OFFSET(0x48));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x13, PCIE_PHY_OFFSET(0x54));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0x04, PCIE_PHY_OFFSET(0x31));
	exynos_pcie_phy_ग_लिखोl(ep->base, 0, PCIE_PHY_OFFSET(0x32));

	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_COMMON_RESET,
			   PCIE_PHY_RESET, 0);
	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_MAC_RESET,
			   PCIE_MAC_RESET_MASK, PCIE_MAC_RESET);
	वापस 0;
पूर्ण

अटल पूर्णांक exynos5433_pcie_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा exynos_pcie_phy *ep = phy_get_drvdata(phy);

	regmap_update_bits(ep->pmureg, EXYNOS5433_PMU_PCIE_PHY_OFFSET,
			   BIT(0), 1);
	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_GLOBAL_RESET,
			   PCIE_APP_REQ_EXIT_L1_MODE, 0);
	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_L1SUB_CM_CON,
			   PCIE_REFCLK_GATING_EN, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक exynos5433_pcie_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा exynos_pcie_phy *ep = phy_get_drvdata(phy);

	regmap_update_bits(ep->fsysreg, PCIE_EXYNOS5433_PHY_L1SUB_CM_CON,
			   PCIE_REFCLK_GATING_EN, PCIE_REFCLK_GATING_EN);
	regmap_update_bits(ep->pmureg, EXYNOS5433_PMU_PCIE_PHY_OFFSET,
			   BIT(0), 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops exynos5433_phy_ops = अणु
	.init		= exynos5433_pcie_phy_init,
	.घातer_on	= exynos5433_pcie_phy_घातer_on,
	.घातer_off	= exynos5433_pcie_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_pcie_phy_match[] = अणु
	अणु
		.compatible = "samsung,exynos5433-pcie-phy",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक exynos_pcie_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा exynos_pcie_phy *exynos_phy;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;

	exynos_phy = devm_kzalloc(dev, माप(*exynos_phy), GFP_KERNEL);
	अगर (!exynos_phy)
		वापस -ENOMEM;

	exynos_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(exynos_phy->base))
		वापस PTR_ERR(exynos_phy->base);

	exynos_phy->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
							"samsung,pmu-syscon");
	अगर (IS_ERR(exynos_phy->pmureg)) अणु
		dev_err(&pdev->dev, "PMU regmap lookup failed.\n");
		वापस PTR_ERR(exynos_phy->pmureg);
	पूर्ण

	exynos_phy->fsysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
							 "samsung,fsys-sysreg");
	अगर (IS_ERR(exynos_phy->fsysreg)) अणु
		dev_err(&pdev->dev, "FSYS sysreg regmap lookup failed.\n");
		वापस PTR_ERR(exynos_phy->fsysreg);
	पूर्ण

	generic_phy = devm_phy_create(dev, dev->of_node, &exynos5433_phy_ops);
	अगर (IS_ERR(generic_phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(generic_phy);
	पूर्ण

	phy_set_drvdata(generic_phy, exynos_phy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_pcie_phy_driver = अणु
	.probe	= exynos_pcie_phy_probe,
	.driver = अणु
		.of_match_table	= exynos_pcie_phy_match,
		.name		= "exynos_pcie_phy",
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;
builtin_platक्रमm_driver(exynos_pcie_phy_driver);
