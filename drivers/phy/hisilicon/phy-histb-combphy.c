<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * COMBPHY driver क्रम HiSilicon STB SoCs
 *
 * Copyright (C) 2016-2017 HiSilicon Co., Ltd. http://www.hisilicon.com
 *
 * Authors: Jianguo Sun <sunjianguo1@huawei.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <dt-bindings/phy/phy.h>

#घोषणा COMBPHY_MODE_PCIE		0
#घोषणा COMBPHY_MODE_USB3		1
#घोषणा COMBPHY_MODE_SATA		2

#घोषणा COMBPHY_CFG_REG			0x0
#घोषणा COMBPHY_BYPASS_CODEC		BIT(31)
#घोषणा COMBPHY_TEST_WRITE		BIT(24)
#घोषणा COMBPHY_TEST_DATA_SHIFT		20
#घोषणा COMBPHY_TEST_DATA_MASK		GENMASK(23, 20)
#घोषणा COMBPHY_TEST_ADDR_SHIFT		12
#घोषणा COMBPHY_TEST_ADDR_MASK		GENMASK(16, 12)
#घोषणा COMBPHY_CLKREF_OUT_OEN		BIT(0)

काष्ठा histb_combphy_mode अणु
	पूर्णांक fixed;
	पूर्णांक select;
	u32 reg;
	u32 shअगरt;
	u32 mask;
पूर्ण;

काष्ठा histb_combphy_priv अणु
	व्योम __iomem *mmio;
	काष्ठा regmap *syscon;
	काष्ठा reset_control *por_rst;
	काष्ठा clk *ref_clk;
	काष्ठा phy *phy;
	काष्ठा histb_combphy_mode mode;
पूर्ण;

अटल व्योम nano_रेजिस्टर_ग_लिखो(काष्ठा histb_combphy_priv *priv,
				u32 addr, u32 data)
अणु
	व्योम __iomem *reg = priv->mmio + COMBPHY_CFG_REG;
	u32 val;

	/* Set up address and data क्रम the ग_लिखो */
	val = पढ़ोl(reg);
	val &= ~COMBPHY_TEST_ADDR_MASK;
	val |= addr << COMBPHY_TEST_ADDR_SHIFT;
	val &= ~COMBPHY_TEST_DATA_MASK;
	val |= data << COMBPHY_TEST_DATA_SHIFT;
	ग_लिखोl(val, reg);

	/* Flip strobe control to trigger the ग_लिखो */
	val &= ~COMBPHY_TEST_WRITE;
	ग_लिखोl(val, reg);
	val |= COMBPHY_TEST_WRITE;
	ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक is_mode_fixed(काष्ठा histb_combphy_mode *mode)
अणु
	वापस (mode->fixed != PHY_NONE) ? true : false;
पूर्ण

अटल पूर्णांक histb_combphy_set_mode(काष्ठा histb_combphy_priv *priv)
अणु
	काष्ठा histb_combphy_mode *mode = &priv->mode;
	काष्ठा regmap *syscon = priv->syscon;
	u32 hw_sel;

	अगर (is_mode_fixed(mode))
		वापस 0;

	चयन (mode->select) अणु
	हाल PHY_TYPE_SATA:
		hw_sel = COMBPHY_MODE_SATA;
		अवरोध;
	हाल PHY_TYPE_PCIE:
		hw_sel = COMBPHY_MODE_PCIE;
		अवरोध;
	हाल PHY_TYPE_USB3:
		hw_sel = COMBPHY_MODE_USB3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(syscon, mode->reg, mode->mask,
				  hw_sel << mode->shअगरt);
पूर्ण

अटल पूर्णांक histb_combphy_init(काष्ठा phy *phy)
अणु
	काष्ठा histb_combphy_priv *priv = phy_get_drvdata(phy);
	u32 val;
	पूर्णांक ret;

	ret = histb_combphy_set_mode(priv);
	अगर (ret)
		वापस ret;

	/* Clear bypass bit to enable encoding/decoding */
	val = पढ़ोl(priv->mmio + COMBPHY_CFG_REG);
	val &= ~COMBPHY_BYPASS_CODEC;
	ग_लिखोl(val, priv->mmio + COMBPHY_CFG_REG);

	ret = clk_prepare_enable(priv->ref_clk);
	अगर (ret)
		वापस ret;

	reset_control_deनिश्चित(priv->por_rst);

	/* Enable EP घड़ी */
	val = पढ़ोl(priv->mmio + COMBPHY_CFG_REG);
	val |= COMBPHY_CLKREF_OUT_OEN;
	ग_लिखोl(val, priv->mmio + COMBPHY_CFG_REG);

	/* Need to रुको क्रम EP घड़ी stable */
	mdelay(5);

	/* Configure nano phy रेजिस्टरs as suggested by venकरोr */
	nano_रेजिस्टर_ग_लिखो(priv, 0x1, 0x8);
	nano_रेजिस्टर_ग_लिखो(priv, 0xc, 0x9);
	nano_रेजिस्टर_ग_लिखो(priv, 0x1a, 0x4);

	वापस 0;
पूर्ण

अटल पूर्णांक histb_combphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा histb_combphy_priv *priv = phy_get_drvdata(phy);
	u32 val;

	/* Disable EP घड़ी */
	val = पढ़ोl(priv->mmio + COMBPHY_CFG_REG);
	val &= ~COMBPHY_CLKREF_OUT_OEN;
	ग_लिखोl(val, priv->mmio + COMBPHY_CFG_REG);

	reset_control_निश्चित(priv->por_rst);
	clk_disable_unprepare(priv->ref_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops histb_combphy_ops = अणु
	.init = histb_combphy_init,
	.निकास = histb_combphy_निकास,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *histb_combphy_xlate(काष्ठा device *dev,
				       काष्ठा of_phandle_args *args)
अणु
	काष्ठा histb_combphy_priv *priv = dev_get_drvdata(dev);
	काष्ठा histb_combphy_mode *mode = &priv->mode;

	अगर (args->args_count < 1) अणु
		dev_err(dev, "invalid number of arguments\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mode->select = args->args[0];

	अगर (mode->select < PHY_TYPE_SATA || mode->select > PHY_TYPE_USB3) अणु
		dev_err(dev, "invalid phy mode select argument\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (is_mode_fixed(mode) && mode->select != mode->fixed) अणु
		dev_err(dev, "mode select %d mismatch fixed phy mode %d\n",
			mode->select, mode->fixed);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस priv->phy;
पूर्ण

अटल पूर्णांक histb_combphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा histb_combphy_priv *priv;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा histb_combphy_mode *mode;
	u32 vals[3];
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->mmio)) अणु
		ret = PTR_ERR(priv->mmio);
		वापस ret;
	पूर्ण

	priv->syscon = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(priv->syscon)) अणु
		dev_err(dev, "failed to find peri_ctrl syscon regmap\n");
		वापस PTR_ERR(priv->syscon);
	पूर्ण

	mode = &priv->mode;
	mode->fixed = PHY_NONE;

	ret = of_property_पढ़ो_u32(np, "hisilicon,fixed-mode", &mode->fixed);
	अगर (ret == 0)
		dev_dbg(dev, "found fixed phy mode %d\n", mode->fixed);

	ret = of_property_पढ़ो_u32_array(np, "hisilicon,mode-select-bits",
					 vals, ARRAY_SIZE(vals));
	अगर (ret == 0) अणु
		अगर (is_mode_fixed(mode)) अणु
			dev_err(dev, "found select bits for fixed mode phy\n");
			वापस -EINVAL;
		पूर्ण

		mode->reg = vals[0];
		mode->shअगरt = vals[1];
		mode->mask = vals[2];
		dev_dbg(dev, "found mode select bits\n");
	पूर्ण अन्यथा अणु
		अगर (!is_mode_fixed(mode)) अणु
			dev_err(dev, "no valid select bits found for non-fixed phy\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	priv->ref_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->ref_clk)) अणु
		dev_err(dev, "failed to find ref clock\n");
		वापस PTR_ERR(priv->ref_clk);
	पूर्ण

	priv->por_rst = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(priv->por_rst)) अणु
		dev_err(dev, "failed to get poweron reset\n");
		वापस PTR_ERR(priv->por_rst);
	पूर्ण

	priv->phy = devm_phy_create(dev, शून्य, &histb_combphy_ops);
	अगर (IS_ERR(priv->phy)) अणु
		dev_err(dev, "failed to create combphy\n");
		वापस PTR_ERR(priv->phy);
	पूर्ण

	dev_set_drvdata(dev, priv);
	phy_set_drvdata(priv->phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, histb_combphy_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id histb_combphy_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3798cv200-combphy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, histb_combphy_of_match);

अटल काष्ठा platक्रमm_driver histb_combphy_driver = अणु
	.probe	= histb_combphy_probe,
	.driver = अणु
		.name = "combphy",
		.of_match_table = histb_combphy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(histb_combphy_driver);

MODULE_DESCRIPTION("HiSilicon STB COMBPHY driver");
MODULE_LICENSE("GPL v2");
