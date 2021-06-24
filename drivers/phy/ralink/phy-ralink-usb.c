<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 John Crispin <john@phrozen.org>
 *
 * Based on code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#घोषणा RT_SYSC_REG_SYSCFG1		0x014
#घोषणा RT_SYSC_REG_CLKCFG1		0x030
#घोषणा RT_SYSC_REG_USB_PHY_CFG		0x05c

#घोषणा OFS_U2_PHY_AC0			0x800
#घोषणा OFS_U2_PHY_AC1			0x804
#घोषणा OFS_U2_PHY_AC2			0x808
#घोषणा OFS_U2_PHY_ACR0			0x810
#घोषणा OFS_U2_PHY_ACR1			0x814
#घोषणा OFS_U2_PHY_ACR2			0x818
#घोषणा OFS_U2_PHY_ACR3			0x81C
#घोषणा OFS_U2_PHY_ACR4			0x820
#घोषणा OFS_U2_PHY_AMON0		0x824
#घोषणा OFS_U2_PHY_DCR0			0x860
#घोषणा OFS_U2_PHY_DCR1			0x864
#घोषणा OFS_U2_PHY_DTM0			0x868
#घोषणा OFS_U2_PHY_DTM1			0x86C

#घोषणा RT_RSTCTRL_UDEV			BIT(25)
#घोषणा RT_RSTCTRL_UHST			BIT(22)
#घोषणा RT_SYSCFG1_USB0_HOST_MODE	BIT(10)

#घोषणा MT7620_CLKCFG1_UPHY0_CLK_EN	BIT(25)
#घोषणा MT7620_CLKCFG1_UPHY1_CLK_EN	BIT(22)
#घोषणा RT_CLKCFG1_UPHY1_CLK_EN		BIT(20)
#घोषणा RT_CLKCFG1_UPHY0_CLK_EN		BIT(18)

#घोषणा USB_PHY_UTMI_8B60M		BIT(1)
#घोषणा UDEV_WAKEUP			BIT(0)

काष्ठा ralink_usb_phy अणु
	काष्ठा reset_control	*rstdev;
	काष्ठा reset_control	*rsthost;
	u32			clk;
	काष्ठा phy		*phy;
	व्योम __iomem		*base;
	काष्ठा regmap		*sysctl;
पूर्ण;

अटल व्योम u2_phy_w32(काष्ठा ralink_usb_phy *phy, u32 val, u32 reg)
अणु
	ग_लिखोl(val, phy->base + reg);
पूर्ण

अटल u32 u2_phy_r32(काष्ठा ralink_usb_phy *phy, u32 reg)
अणु
	वापस पढ़ोl(phy->base + reg);
पूर्ण

अटल व्योम ralink_usb_phy_init(काष्ठा ralink_usb_phy *phy)
अणु
	u2_phy_r32(phy, OFS_U2_PHY_AC2);
	u2_phy_r32(phy, OFS_U2_PHY_ACR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);

	u2_phy_w32(phy, 0x00ffff02, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x00555502, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x00aaaa02, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x00000402, OFS_U2_PHY_DCR0);
	u2_phy_r32(phy, OFS_U2_PHY_DCR0);
	u2_phy_w32(phy, 0x0048086a, OFS_U2_PHY_AC0);
	u2_phy_w32(phy, 0x4400001c, OFS_U2_PHY_AC1);
	u2_phy_w32(phy, 0xc0200000, OFS_U2_PHY_ACR3);
	u2_phy_w32(phy, 0x02000000, OFS_U2_PHY_DTM0);
पूर्ण

अटल पूर्णांक ralink_usb_phy_घातer_on(काष्ठा phy *_phy)
अणु
	काष्ठा ralink_usb_phy *phy = phy_get_drvdata(_phy);
	u32 t;

	/* enable the phy */
	regmap_update_bits(phy->sysctl, RT_SYSC_REG_CLKCFG1,
			   phy->clk, phy->clk);

	/* setup host mode */
	regmap_update_bits(phy->sysctl, RT_SYSC_REG_SYSCFG1,
			   RT_SYSCFG1_USB0_HOST_MODE,
			   RT_SYSCFG1_USB0_HOST_MODE);

	/* deनिश्चित the reset lines */
	reset_control_deनिश्चित(phy->rsthost);
	reset_control_deनिश्चित(phy->rstdev);

	/*
	 * The SDK kernel had a delay of 100ms. however on device
	 * testing showed that 10ms is enough
	 */
	mdelay(10);

	अगर (phy->base)
		ralink_usb_phy_init(phy);

	/* prपूर्णांक some status info */
	regmap_पढ़ो(phy->sysctl, RT_SYSC_REG_USB_PHY_CFG, &t);
	dev_info(&phy->phy->dev, "remote usb device wakeup %s\n",
		(t & UDEV_WAKEUP) ? ("enabled") : ("disabled"));
	अगर (t & USB_PHY_UTMI_8B60M)
		dev_info(&phy->phy->dev, "UTMI 8bit 60MHz\n");
	अन्यथा
		dev_info(&phy->phy->dev, "UTMI 16bit 30MHz\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ralink_usb_phy_घातer_off(काष्ठा phy *_phy)
अणु
	काष्ठा ralink_usb_phy *phy = phy_get_drvdata(_phy);

	/* disable the phy */
	regmap_update_bits(phy->sysctl, RT_SYSC_REG_CLKCFG1,
			   phy->clk, 0);

	/* निश्चित the reset lines */
	reset_control_निश्चित(phy->rstdev);
	reset_control_निश्चित(phy->rsthost);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ralink_usb_phy_ops = अणु
	.घातer_on	= ralink_usb_phy_घातer_on,
	.घातer_off	= ralink_usb_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ralink_usb_phy_of_match[] = अणु
	अणु
		.compatible = "ralink,rt3352-usbphy",
		.data = (व्योम *)(uपूर्णांकptr_t)(RT_CLKCFG1_UPHY1_CLK_EN |
					    RT_CLKCFG1_UPHY0_CLK_EN)
	पूर्ण,
	अणु
		.compatible = "mediatek,mt7620-usbphy",
		.data = (व्योम *)(uपूर्णांकptr_t)(MT7620_CLKCFG1_UPHY1_CLK_EN |
					    MT7620_CLKCFG1_UPHY0_CLK_EN)
	पूर्ण,
	अणु
		.compatible = "mediatek,mt7628-usbphy",
		.data = (व्योम *)(uपूर्णांकptr_t)(MT7620_CLKCFG1_UPHY1_CLK_EN |
					    MT7620_CLKCFG1_UPHY0_CLK_EN) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ralink_usb_phy_of_match);

अटल पूर्णांक ralink_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा ralink_usb_phy *phy;

	match = of_match_device(ralink_usb_phy_of_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->clk = (uपूर्णांकptr_t)match->data;
	phy->base = शून्य;

	phy->sysctl = syscon_regmap_lookup_by_phandle(dev->of_node, "ralink,sysctl");
	अगर (IS_ERR(phy->sysctl)) अणु
		dev_err(dev, "failed to get sysctl registers\n");
		वापस PTR_ERR(phy->sysctl);
	पूर्ण

	/* The MT7628 and MT7688 require extra setup of PHY रेजिस्टरs. */
	अगर (of_device_is_compatible(dev->of_node, "mediatek,mt7628-usbphy")) अणु
		phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(phy->base)) अणु
			dev_err(dev, "failed to remap register memory\n");
			वापस PTR_ERR(phy->base);
		पूर्ण
	पूर्ण

	phy->rsthost = devm_reset_control_get(&pdev->dev, "host");
	अगर (IS_ERR(phy->rsthost)) अणु
		dev_err(dev, "host reset is missing\n");
		वापस PTR_ERR(phy->rsthost);
	पूर्ण

	phy->rstdev = devm_reset_control_get(&pdev->dev, "device");
	अगर (IS_ERR(phy->rstdev)) अणु
		dev_err(dev, "device reset is missing\n");
		वापस PTR_ERR(phy->rstdev);
	पूर्ण

	phy->phy = devm_phy_create(dev, शून्य, &ralink_usb_phy_ops);
	अगर (IS_ERR(phy->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy->phy);
	पूर्ण
	phy_set_drvdata(phy->phy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver ralink_usb_phy_driver = अणु
	.probe	= ralink_usb_phy_probe,
	.driver = अणु
		.of_match_table	= ralink_usb_phy_of_match,
		.name  = "ralink-usb-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(ralink_usb_phy_driver);

MODULE_DESCRIPTION("Ralink USB phy driver");
MODULE_AUTHOR("John Crispin <john@phrozen.org>");
MODULE_LICENSE("GPL v2");
