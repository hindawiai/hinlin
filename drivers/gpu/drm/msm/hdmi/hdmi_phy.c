<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/of_device.h>

#समावेश "hdmi.h"

अटल पूर्णांक msm_hdmi_phy_resource_init(काष्ठा hdmi_phy *phy)
अणु
	काष्ठा hdmi_phy_cfg *cfg = phy->cfg;
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक i, ret;

	phy->regs = devm_kसुस्मृति(dev, cfg->num_regs, माप(phy->regs[0]),
				 GFP_KERNEL);
	अगर (!phy->regs)
		वापस -ENOMEM;

	phy->clks = devm_kसुस्मृति(dev, cfg->num_clks, माप(phy->clks[0]),
				 GFP_KERNEL);
	अगर (!phy->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < cfg->num_regs; i++) अणु
		काष्ठा regulator *reg;

		reg = devm_regulator_get(dev, cfg->reg_names[i]);
		अगर (IS_ERR(reg)) अणु
			ret = PTR_ERR(reg);
			अगर (ret != -EPROBE_DEFER) अणु
				DRM_DEV_ERROR(dev,
					      "failed to get phy regulator: %s (%d)\n",
					      cfg->reg_names[i], ret);
			पूर्ण

			वापस ret;
		पूर्ण

		phy->regs[i] = reg;
	पूर्ण

	क्रम (i = 0; i < cfg->num_clks; i++) अणु
		काष्ठा clk *clk;

		clk = msm_clk_get(phy->pdev, cfg->clk_names[i]);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			DRM_DEV_ERROR(dev, "failed to get phy clock: %s (%d)\n",
				cfg->clk_names[i], ret);
			वापस ret;
		पूर्ण

		phy->clks[i] = clk;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक msm_hdmi_phy_resource_enable(काष्ठा hdmi_phy *phy)
अणु
	काष्ठा hdmi_phy_cfg *cfg = phy->cfg;
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक i, ret = 0;

	pm_runसमय_get_sync(dev);

	क्रम (i = 0; i < cfg->num_regs; i++) अणु
		ret = regulator_enable(phy->regs[i]);
		अगर (ret)
			DRM_DEV_ERROR(dev, "failed to enable regulator: %s (%d)\n",
				cfg->reg_names[i], ret);
	पूर्ण

	क्रम (i = 0; i < cfg->num_clks; i++) अणु
		ret = clk_prepare_enable(phy->clks[i]);
		अगर (ret)
			DRM_DEV_ERROR(dev, "failed to enable clock: %s (%d)\n",
				cfg->clk_names[i], ret);
	पूर्ण

	वापस ret;
पूर्ण

व्योम msm_hdmi_phy_resource_disable(काष्ठा hdmi_phy *phy)
अणु
	काष्ठा hdmi_phy_cfg *cfg = phy->cfg;
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक i;

	क्रम (i = cfg->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(phy->clks[i]);

	क्रम (i = cfg->num_regs - 1; i >= 0; i--)
		regulator_disable(phy->regs[i]);

	pm_runसमय_put_sync(dev);
पूर्ण

व्योम msm_hdmi_phy_घातerup(काष्ठा hdmi_phy *phy, अचिन्हित दीर्घ पूर्णांक pixघड़ी)
अणु
	अगर (!phy || !phy->cfg->घातerup)
		वापस;

	phy->cfg->घातerup(phy, pixघड़ी);
पूर्ण

व्योम msm_hdmi_phy_घातerकरोwn(काष्ठा hdmi_phy *phy)
अणु
	अगर (!phy || !phy->cfg->घातerकरोwn)
		वापस;

	phy->cfg->घातerकरोwn(phy);
पूर्ण

अटल पूर्णांक msm_hdmi_phy_pll_init(काष्ठा platक्रमm_device *pdev,
			     क्रमागत hdmi_phy_type type)
अणु
	पूर्णांक ret;

	चयन (type) अणु
	हाल MSM_HDMI_PHY_8960:
		ret = msm_hdmi_pll_8960_init(pdev);
		अवरोध;
	हाल MSM_HDMI_PHY_8996:
		ret = msm_hdmi_pll_8996_init(pdev);
		अवरोध;
	/*
	 * we करोn't have PLL support for these, don't report an error क्रम now
	 */
	हाल MSM_HDMI_PHY_8x60:
	हाल MSM_HDMI_PHY_8x74:
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msm_hdmi_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdmi_phy *phy;
	पूर्णांक ret;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENODEV;

	phy->cfg = (काष्ठा hdmi_phy_cfg *)of_device_get_match_data(dev);
	अगर (!phy->cfg)
		वापस -ENODEV;

	phy->mmio = msm_ioremap(pdev, "hdmi_phy", "HDMI_PHY");
	अगर (IS_ERR(phy->mmio)) अणु
		DRM_DEV_ERROR(dev, "%s: failed to map phy base\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	phy->pdev = pdev;

	ret = msm_hdmi_phy_resource_init(phy);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&pdev->dev);

	ret = msm_hdmi_phy_resource_enable(phy);
	अगर (ret)
		वापस ret;

	ret = msm_hdmi_phy_pll_init(pdev, phy->cfg->type);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "couldn't init PLL\n");
		msm_hdmi_phy_resource_disable(phy);
		वापस ret;
	पूर्ण

	msm_hdmi_phy_resource_disable(phy);

	platक्रमm_set_drvdata(pdev, phy);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_hdmi_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id msm_hdmi_phy_dt_match[] = अणु
	अणु .compatible = "qcom,hdmi-phy-8660",
	  .data = &msm_hdmi_phy_8x60_cfg पूर्ण,
	अणु .compatible = "qcom,hdmi-phy-8960",
	  .data = &msm_hdmi_phy_8960_cfg पूर्ण,
	अणु .compatible = "qcom,hdmi-phy-8974",
	  .data = &msm_hdmi_phy_8x74_cfg पूर्ण,
	अणु .compatible = "qcom,hdmi-phy-8084",
	  .data = &msm_hdmi_phy_8x74_cfg पूर्ण,
	अणु .compatible = "qcom,hdmi-phy-8996",
	  .data = &msm_hdmi_phy_8996_cfg पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver msm_hdmi_phy_platक्रमm_driver = अणु
	.probe      = msm_hdmi_phy_probe,
	.हटाओ     = msm_hdmi_phy_हटाओ,
	.driver     = अणु
		.name   = "msm_hdmi_phy",
		.of_match_table = msm_hdmi_phy_dt_match,
	पूर्ण,
पूर्ण;

व्योम __init msm_hdmi_phy_driver_रेजिस्टर(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&msm_hdmi_phy_platक्रमm_driver);
पूर्ण

व्योम __निकास msm_hdmi_phy_driver_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&msm_hdmi_phy_platक्रमm_driver);
पूर्ण
