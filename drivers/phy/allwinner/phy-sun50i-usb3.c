<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Allwinner sun50i(H6) USB 3.0 phy driver
 *
 * Copyright (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on phy-sun9i-usb.c, which is:
 *
 * Copyright (C) 2014-2015 Chen-Yu Tsai <wens@csie.org>
 *
 * Based on code from Allwinner BSP, which is:
 *
 * Copyright (c) 2010-2015 Allwinner Technology Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

/* Interface Status and Control Registers */
#घोषणा SUNXI_ISCR			0x00
#घोषणा SUNXI_PIPE_CLOCK_CONTROL	0x14
#घोषणा SUNXI_PHY_TUNE_LOW		0x18
#घोषणा SUNXI_PHY_TUNE_HIGH		0x1c
#घोषणा SUNXI_PHY_EXTERNAL_CONTROL	0x20

/* USB2.0 Interface Status and Control Register */
#घोषणा SUNXI_ISCR_FORCE_VBUS		(3 << 12)

/* PIPE Clock Control Register */
#घोषणा SUNXI_PCC_PIPE_CLK_OPEN		(1 << 6)

/* PHY External Control Register */
#घोषणा SUNXI_PEC_EXTERN_VBUS		(3 << 1)
#घोषणा SUNXI_PEC_SSC_EN		(1 << 24)
#घोषणा SUNXI_PEC_REF_SSP_EN		(1 << 26)

/* PHY Tune High Register */
#घोषणा SUNXI_TX_DEEMPH_3P5DB(n)	((n) << 19)
#घोषणा SUNXI_TX_DEEMPH_3P5DB_MASK	GENMASK(24, 19)
#घोषणा SUNXI_TX_DEEMPH_6DB(n)		((n) << 13)
#घोषणा SUNXI_TX_DEEMPH_6GB_MASK	GENMASK(18, 13)
#घोषणा SUNXI_TX_SWING_FULL(n)		((n) << 6)
#घोषणा SUNXI_TX_SWING_FULL_MASK	GENMASK(12, 6)
#घोषणा SUNXI_LOS_BIAS(n)		((n) << 3)
#घोषणा SUNXI_LOS_BIAS_MASK		GENMASK(5, 3)
#घोषणा SUNXI_TXVBOOSTLVL(n)		((n) << 0)
#घोषणा SUNXI_TXVBOOSTLVL_MASK		GENMASK(2, 0)

काष्ठा sun50i_usb3_phy अणु
	काष्ठा phy *phy;
	व्योम __iomem *regs;
	काष्ठा reset_control *reset;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम sun50i_usb3_phy_खोलो(काष्ठा sun50i_usb3_phy *phy)
अणु
	u32 val;

	val = पढ़ोl(phy->regs + SUNXI_PHY_EXTERNAL_CONTROL);
	val |= SUNXI_PEC_EXTERN_VBUS;
	val |= SUNXI_PEC_SSC_EN | SUNXI_PEC_REF_SSP_EN;
	ग_लिखोl(val, phy->regs + SUNXI_PHY_EXTERNAL_CONTROL);

	val = पढ़ोl(phy->regs + SUNXI_PIPE_CLOCK_CONTROL);
	val |= SUNXI_PCC_PIPE_CLK_OPEN;
	ग_लिखोl(val, phy->regs + SUNXI_PIPE_CLOCK_CONTROL);

	val = पढ़ोl(phy->regs + SUNXI_ISCR);
	val |= SUNXI_ISCR_FORCE_VBUS;
	ग_लिखोl(val, phy->regs + SUNXI_ISCR);

	/*
	 * All the magic numbers written to the PHY_TUNE_अणुLOW_HIGHपूर्ण
	 * रेजिस्टरs are directly taken from the BSP USB3 driver from
	 * Allwiner.
	 */
	ग_लिखोl(0x0047fc87, phy->regs + SUNXI_PHY_TUNE_LOW);

	val = पढ़ोl(phy->regs + SUNXI_PHY_TUNE_HIGH);
	val &= ~(SUNXI_TXVBOOSTLVL_MASK | SUNXI_LOS_BIAS_MASK |
		 SUNXI_TX_SWING_FULL_MASK | SUNXI_TX_DEEMPH_6GB_MASK |
		 SUNXI_TX_DEEMPH_3P5DB_MASK);
	val |= SUNXI_TXVBOOSTLVL(0x7);
	val |= SUNXI_LOS_BIAS(0x7);
	val |= SUNXI_TX_SWING_FULL(0x55);
	val |= SUNXI_TX_DEEMPH_6DB(0x20);
	val |= SUNXI_TX_DEEMPH_3P5DB(0x15);
	ग_लिखोl(val, phy->regs + SUNXI_PHY_TUNE_HIGH);
पूर्ण

अटल पूर्णांक sun50i_usb3_phy_init(काष्ठा phy *_phy)
अणु
	काष्ठा sun50i_usb3_phy *phy = phy_get_drvdata(_phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_deनिश्चित(phy->reset);
	अगर (ret) अणु
		clk_disable_unprepare(phy->clk);
		वापस ret;
	पूर्ण

	sun50i_usb3_phy_खोलो(phy);
	वापस 0;
पूर्ण

अटल पूर्णांक sun50i_usb3_phy_निकास(काष्ठा phy *_phy)
अणु
	काष्ठा sun50i_usb3_phy *phy = phy_get_drvdata(_phy);

	reset_control_निश्चित(phy->reset);
	clk_disable_unprepare(phy->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops sun50i_usb3_phy_ops = अणु
	.init		= sun50i_usb3_phy_init,
	.निकास		= sun50i_usb3_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक sun50i_usb3_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun50i_usb3_phy *phy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(phy->clk)) अणु
		अगर (PTR_ERR(phy->clk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get phy clock\n");
		वापस PTR_ERR(phy->clk);
	पूर्ण

	phy->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(phy->reset)) अणु
		dev_err(dev, "failed to get reset control\n");
		वापस PTR_ERR(phy->reset);
	पूर्ण

	phy->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->regs))
		वापस PTR_ERR(phy->regs);

	phy->phy = devm_phy_create(dev, शून्य, &sun50i_usb3_phy_ops);
	अगर (IS_ERR(phy->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy->phy);
	पूर्ण

	phy_set_drvdata(phy->phy, phy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun50i_usb3_phy_of_match[] = अणु
	अणु .compatible = "allwinner,sun50i-h6-usb3-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun50i_usb3_phy_of_match);

अटल काष्ठा platक्रमm_driver sun50i_usb3_phy_driver = अणु
	.probe	= sun50i_usb3_phy_probe,
	.driver = अणु
		.of_match_table	= sun50i_usb3_phy_of_match,
		.name  = "sun50i-usb3-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sun50i_usb3_phy_driver);

MODULE_DESCRIPTION("Allwinner H6 USB 3.0 phy driver");
MODULE_AUTHOR("Icenowy Zheng <icenowy@aosc.io>");
MODULE_LICENSE("GPL");
