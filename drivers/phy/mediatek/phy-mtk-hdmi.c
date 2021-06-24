<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */

#समावेश "phy-mtk-hdmi.h"

अटल पूर्णांक mtk_hdmi_phy_घातer_on(काष्ठा phy *phy);
अटल पूर्णांक mtk_hdmi_phy_घातer_off(काष्ठा phy *phy);

अटल स्थिर काष्ठा phy_ops mtk_hdmi_phy_dev_ops = अणु
	.घातer_on = mtk_hdmi_phy_घातer_on,
	.घातer_off = mtk_hdmi_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

व्योम mtk_hdmi_phy_clear_bits(काष्ठा mtk_hdmi_phy *hdmi_phy, u32 offset,
			     u32 bits)
अणु
	व्योम __iomem *reg = hdmi_phy->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp &= ~bits;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

व्योम mtk_hdmi_phy_set_bits(काष्ठा mtk_hdmi_phy *hdmi_phy, u32 offset,
			   u32 bits)
अणु
	व्योम __iomem *reg = hdmi_phy->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp |= bits;
	ग_लिखोl(पंचांगp, reg);
पूर्ण

व्योम mtk_hdmi_phy_mask(काष्ठा mtk_hdmi_phy *hdmi_phy, u32 offset,
		       u32 val, u32 mask)
अणु
	व्योम __iomem *reg = hdmi_phy->regs + offset;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(reg);
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	ग_लिखोl(पंचांगp, reg);
पूर्ण

अंतरभूत काष्ठा mtk_hdmi_phy *to_mtk_hdmi_phy(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mtk_hdmi_phy, pll_hw);
पूर्ण

अटल पूर्णांक mtk_hdmi_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(hdmi_phy->pll);
	अगर (ret < 0)
		वापस ret;

	hdmi_phy->conf->hdmi_phy_enable_पंचांगds(hdmi_phy);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hdmi_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = phy_get_drvdata(phy);

	hdmi_phy->conf->hdmi_phy_disable_पंचांगds(hdmi_phy);
	clk_disable_unprepare(hdmi_phy->pll);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops *
mtk_hdmi_phy_dev_get_ops(स्थिर काष्ठा mtk_hdmi_phy *hdmi_phy)
अणु
	अगर (hdmi_phy && hdmi_phy->conf &&
	    hdmi_phy->conf->hdmi_phy_enable_पंचांगds &&
	    hdmi_phy->conf->hdmi_phy_disable_पंचांगds)
		वापस &mtk_hdmi_phy_dev_ops;

	अगर (hdmi_phy)
		dev_err(hdmi_phy->dev, "Failed to get dev ops of phy\n");
	वापस शून्य;
पूर्ण

अटल व्योम mtk_hdmi_phy_clk_get_data(काष्ठा mtk_hdmi_phy *hdmi_phy,
				      काष्ठा clk_init_data *clk_init)
अणु
	clk_init->flags = hdmi_phy->conf->flags;
	clk_init->ops = hdmi_phy->conf->hdmi_phy_clk_ops;
पूर्ण

अटल पूर्णांक mtk_hdmi_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_hdmi_phy *hdmi_phy;
	काष्ठा resource *mem;
	काष्ठा clk *ref_clk;
	स्थिर अक्षर *ref_clk_name;
	काष्ठा clk_init_data clk_init = अणु
		.num_parents = 1,
		.parent_names = (स्थिर अक्षर * स्थिर *)&ref_clk_name,
	पूर्ण;

	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;
	पूर्णांक ret;

	hdmi_phy = devm_kzalloc(dev, माप(*hdmi_phy), GFP_KERNEL);
	अगर (!hdmi_phy)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hdmi_phy->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(hdmi_phy->regs)) अणु
		ret = PTR_ERR(hdmi_phy->regs);
		dev_err(dev, "Failed to get memory resource: %d\n", ret);
		वापस ret;
	पूर्ण

	ref_clk = devm_clk_get(dev, "pll_ref");
	अगर (IS_ERR(ref_clk)) अणु
		ret = PTR_ERR(ref_clk);
		dev_err(&pdev->dev, "Failed to get PLL reference clock: %d\n",
			ret);
		वापस ret;
	पूर्ण
	ref_clk_name = __clk_get_name(ref_clk);

	ret = of_property_पढ़ो_string(dev->of_node, "clock-output-names",
				      &clk_init.name);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read clock-output-names: %d\n", ret);
		वापस ret;
	पूर्ण

	hdmi_phy->dev = dev;
	hdmi_phy->conf =
		(काष्ठा mtk_hdmi_phy_conf *)of_device_get_match_data(dev);
	mtk_hdmi_phy_clk_get_data(hdmi_phy, &clk_init);
	hdmi_phy->pll_hw.init = &clk_init;
	hdmi_phy->pll = devm_clk_रेजिस्टर(dev, &hdmi_phy->pll_hw);
	अगर (IS_ERR(hdmi_phy->pll)) अणु
		ret = PTR_ERR(hdmi_phy->pll);
		dev_err(dev, "Failed to register PLL: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "mediatek,ibias",
				   &hdmi_phy->ibias);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get ibias: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "mediatek,ibias_up",
				   &hdmi_phy->ibias_up);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get ibias up: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "Using default TX DRV impedance: 4.2k/36\n");
	hdmi_phy->drv_imp_clk = 0x30;
	hdmi_phy->drv_imp_d2 = 0x30;
	hdmi_phy->drv_imp_d1 = 0x30;
	hdmi_phy->drv_imp_d0 = 0x30;

	phy = devm_phy_create(dev, शून्य, mtk_hdmi_phy_dev_get_ops(hdmi_phy));
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "Failed to create HDMI PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण
	phy_set_drvdata(phy, hdmi_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(dev, "Failed to register HDMI PHY\n");
		वापस PTR_ERR(phy_provider);
	पूर्ण

	अगर (hdmi_phy->conf->pll_शेष_off)
		hdmi_phy->conf->hdmi_phy_disable_पंचांगds(hdmi_phy);

	वापस of_clk_add_provider(dev->of_node, of_clk_src_simple_get,
				   hdmi_phy->pll);
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_hdmi_phy_match[] = अणु
	अणु .compatible = "mediatek,mt2701-hdmi-phy",
	  .data = &mtk_hdmi_phy_2701_conf,
	पूर्ण,
	अणु .compatible = "mediatek,mt8173-hdmi-phy",
	  .data = &mtk_hdmi_phy_8173_conf,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_hdmi_phy_match);

अटल काष्ठा platक्रमm_driver mtk_hdmi_phy_driver = अणु
	.probe = mtk_hdmi_phy_probe,
	.driver = अणु
		.name = "mediatek-hdmi-phy",
		.of_match_table = mtk_hdmi_phy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_hdmi_phy_driver);

MODULE_DESCRIPTION("MediaTek HDMI PHY Driver");
MODULE_LICENSE("GPL v2");
