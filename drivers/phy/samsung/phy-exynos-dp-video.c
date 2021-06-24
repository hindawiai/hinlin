<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung Exynos SoC series Display Port PHY driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

काष्ठा exynos_dp_video_phy_drvdata अणु
	u32 phy_ctrl_offset;
पूर्ण;

काष्ठा exynos_dp_video_phy अणु
	काष्ठा regmap *regs;
	स्थिर काष्ठा exynos_dp_video_phy_drvdata *drvdata;
पूर्ण;

अटल पूर्णांक exynos_dp_video_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा exynos_dp_video_phy *state = phy_get_drvdata(phy);

	/* Disable घातer isolation on DP-PHY */
	वापस regmap_update_bits(state->regs, state->drvdata->phy_ctrl_offset,
				  EXYNOS4_PHY_ENABLE, EXYNOS4_PHY_ENABLE);
पूर्ण

अटल पूर्णांक exynos_dp_video_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा exynos_dp_video_phy *state = phy_get_drvdata(phy);

	/* Enable घातer isolation on DP-PHY */
	वापस regmap_update_bits(state->regs, state->drvdata->phy_ctrl_offset,
				  EXYNOS4_PHY_ENABLE, 0);
पूर्ण

अटल स्थिर काष्ठा phy_ops exynos_dp_video_phy_ops = अणु
	.घातer_on	= exynos_dp_video_phy_घातer_on,
	.घातer_off	= exynos_dp_video_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा exynos_dp_video_phy_drvdata exynos5250_dp_video_phy = अणु
	.phy_ctrl_offset	= EXYNOS5_DPTX_PHY_CONTROL,
पूर्ण;

अटल स्थिर काष्ठा exynos_dp_video_phy_drvdata exynos5420_dp_video_phy = अणु
	.phy_ctrl_offset	= EXYNOS5420_DPTX_PHY_CONTROL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_dp_video_phy_of_match[] = अणु
	अणु
		.compatible = "samsung,exynos5250-dp-video-phy",
		.data = &exynos5250_dp_video_phy,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-dp-video-phy",
		.data = &exynos5420_dp_video_phy,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_dp_video_phy_of_match);

अटल पूर्णांक exynos_dp_video_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_dp_video_phy *state;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *phy;

	state = devm_kzalloc(dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->regs = syscon_regmap_lookup_by_phandle(dev->of_node,
						      "samsung,pmu-syscon");
	अगर (IS_ERR(state->regs)) अणु
		dev_err(dev, "Failed to lookup PMU regmap\n");
		वापस PTR_ERR(state->regs);
	पूर्ण

	state->drvdata = of_device_get_match_data(dev);

	phy = devm_phy_create(dev, शून्य, &exynos_dp_video_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create Display Port PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण
	phy_set_drvdata(phy, state);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_dp_video_phy_driver = अणु
	.probe	= exynos_dp_video_phy_probe,
	.driver = अणु
		.name	= "exynos-dp-video-phy",
		.of_match_table	= exynos_dp_video_phy_of_match,
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(exynos_dp_video_phy_driver);

MODULE_AUTHOR("Jingoo Han <jg1.han@samsung.com>");
MODULE_DESCRIPTION("Samsung Exynos SoC DP PHY driver");
MODULE_LICENSE("GPL v2");
