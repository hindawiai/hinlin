<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * phy-keystone - USB PHY, talking to dwc3 controller in Keystone.
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: WingMan Kwok <w-kwok2@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#समावेश "phy-generic.h"

/* USB PHY control रेजिस्टर offsets */
#घोषणा USB_PHY_CTL_UTMI		0x0000
#घोषणा USB_PHY_CTL_PIPE		0x0004
#घोषणा USB_PHY_CTL_PARAM_1		0x0008
#घोषणा USB_PHY_CTL_PARAM_2		0x000c
#घोषणा USB_PHY_CTL_CLOCK		0x0010
#घोषणा USB_PHY_CTL_PLL			0x0014

#घोषणा PHY_REF_SSP_EN			BIT(29)

काष्ठा keystone_usbphy अणु
	काष्ठा usb_phy_generic	usb_phy_gen;
	व्योम __iomem			*phy_ctrl;
पूर्ण;

अटल अंतरभूत u32 keystone_usbphy_पढ़ोl(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम keystone_usbphy_ग_लिखोl(व्योम __iomem *base,
					  u32 offset, u32 value)
अणु
	ग_लिखोl(value, base + offset);
पूर्ण

अटल पूर्णांक keystone_usbphy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा keystone_usbphy *k_phy = dev_get_drvdata(phy->dev);
	u32 val;

	val  = keystone_usbphy_पढ़ोl(k_phy->phy_ctrl, USB_PHY_CTL_CLOCK);
	keystone_usbphy_ग_लिखोl(k_phy->phy_ctrl, USB_PHY_CTL_CLOCK,
				val | PHY_REF_SSP_EN);
	वापस 0;
पूर्ण

अटल व्योम keystone_usbphy_shutकरोwn(काष्ठा usb_phy *phy)
अणु
	काष्ठा keystone_usbphy *k_phy = dev_get_drvdata(phy->dev);
	u32 val;

	val  = keystone_usbphy_पढ़ोl(k_phy->phy_ctrl, USB_PHY_CTL_CLOCK);
	keystone_usbphy_ग_लिखोl(k_phy->phy_ctrl, USB_PHY_CTL_CLOCK,
				val &= ~PHY_REF_SSP_EN);
पूर्ण

अटल पूर्णांक keystone_usbphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा keystone_usbphy	*k_phy;
	पूर्णांक ret;

	k_phy = devm_kzalloc(dev, माप(*k_phy), GFP_KERNEL);
	अगर (!k_phy)
		वापस -ENOMEM;

	k_phy->phy_ctrl = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(k_phy->phy_ctrl))
		वापस PTR_ERR(k_phy->phy_ctrl);

	ret = usb_phy_gen_create_phy(dev, &k_phy->usb_phy_gen);
	अगर (ret)
		वापस ret;

	k_phy->usb_phy_gen.phy.init = keystone_usbphy_init;
	k_phy->usb_phy_gen.phy.shutकरोwn = keystone_usbphy_shutकरोwn;

	platक्रमm_set_drvdata(pdev, k_phy);

	वापस usb_add_phy_dev(&k_phy->usb_phy_gen.phy);
पूर्ण

अटल पूर्णांक keystone_usbphy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा keystone_usbphy *k_phy = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&k_phy->usb_phy_gen.phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id keystone_usbphy_ids[] = अणु
	अणु .compatible = "ti,keystone-usbphy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, keystone_usbphy_ids);

अटल काष्ठा platक्रमm_driver keystone_usbphy_driver = अणु
	.probe          = keystone_usbphy_probe,
	.हटाओ         = keystone_usbphy_हटाओ,
	.driver         = अणु
		.name   = "keystone-usbphy",
		.of_match_table = keystone_usbphy_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(keystone_usbphy_driver);

MODULE_ALIAS("platform:keystone-usbphy");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("Keystone USB phy driver");
MODULE_LICENSE("GPL v2");
