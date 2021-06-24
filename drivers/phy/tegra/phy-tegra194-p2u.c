<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * P2U (PIPE to UPHY) driver क्रम Tegra T194 SoC
 *
 * Copyright (C) 2019 NVIDIA Corporation.
 *
 * Author: Vidya Sagar <vidyas@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>

#घोषणा P2U_PERIODIC_EQ_CTRL_GEN3	0xc0
#घोषणा P2U_PERIODIC_EQ_CTRL_GEN3_PERIODIC_EQ_EN		BIT(0)
#घोषणा P2U_PERIODIC_EQ_CTRL_GEN3_INIT_PRESET_EQ_TRAIN_EN	BIT(1)
#घोषणा P2U_PERIODIC_EQ_CTRL_GEN4	0xc4
#घोषणा P2U_PERIODIC_EQ_CTRL_GEN4_INIT_PRESET_EQ_TRAIN_EN	BIT(1)

#घोषणा P2U_RX_DEBOUNCE_TIME				0xa4
#घोषणा P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_MASK	0xffff
#घोषणा P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_VAL		160

काष्ठा tegra_p2u अणु
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत व्योम p2u_ग_लिखोl(काष्ठा tegra_p2u *phy, स्थिर u32 value,
			      स्थिर u32 reg)
अणु
	ग_लिखोl_relaxed(value, phy->base + reg);
पूर्ण

अटल अंतरभूत u32 p2u_पढ़ोl(काष्ठा tegra_p2u *phy, स्थिर u32 reg)
अणु
	वापस पढ़ोl_relaxed(phy->base + reg);
पूर्ण

अटल पूर्णांक tegra_p2u_घातer_on(काष्ठा phy *x)
अणु
	काष्ठा tegra_p2u *phy = phy_get_drvdata(x);
	u32 val;

	val = p2u_पढ़ोl(phy, P2U_PERIODIC_EQ_CTRL_GEN3);
	val &= ~P2U_PERIODIC_EQ_CTRL_GEN3_PERIODIC_EQ_EN;
	val |= P2U_PERIODIC_EQ_CTRL_GEN3_INIT_PRESET_EQ_TRAIN_EN;
	p2u_ग_लिखोl(phy, val, P2U_PERIODIC_EQ_CTRL_GEN3);

	val = p2u_पढ़ोl(phy, P2U_PERIODIC_EQ_CTRL_GEN4);
	val |= P2U_PERIODIC_EQ_CTRL_GEN4_INIT_PRESET_EQ_TRAIN_EN;
	p2u_ग_लिखोl(phy, val, P2U_PERIODIC_EQ_CTRL_GEN4);

	val = p2u_पढ़ोl(phy, P2U_RX_DEBOUNCE_TIME);
	val &= ~P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_MASK;
	val |= P2U_RX_DEBOUNCE_TIME_DEBOUNCE_TIMER_VAL;
	p2u_ग_लिखोl(phy, val, P2U_RX_DEBOUNCE_TIME);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.घातer_on = tegra_p2u_घातer_on,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक tegra_p2u_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *generic_phy;
	काष्ठा tegra_p2u *phy;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->base = devm_platक्रमm_ioremap_resource_byname(pdev, "ctl");
	अगर (IS_ERR(phy->base))
		वापस PTR_ERR(phy->base);

	platक्रमm_set_drvdata(pdev, phy);

	generic_phy = devm_phy_create(dev, शून्य, &ops);
	अगर (IS_ERR(generic_phy))
		वापस PTR_ERR(generic_phy);

	phy_set_drvdata(generic_phy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_p2u_id_table[] = अणु
	अणु
		.compatible = "nvidia,tegra194-p2u",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_p2u_id_table);

अटल काष्ठा platक्रमm_driver tegra_p2u_driver = अणु
	.probe = tegra_p2u_probe,
	.driver = अणु
		.name = "tegra194-p2u",
		.of_match_table = tegra_p2u_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_p2u_driver);

MODULE_AUTHOR("Vidya Sagar <vidyas@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA Tegra194 PIPE2UPHY PHY driver");
MODULE_LICENSE("GPL v2");
