<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BCM6328 USBH PHY Controller Driver
 *
 * Copyright (C) 2020 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 * Copyright (C) 2015 Simon Arlott
 *
 * Derived from bcm963xx_4.12L.06B_consumer/kernel/linux/arch/mips/bcm963xx/setup.c:
 * Copyright (C) 2002 Broadcom Corporation
 *
 * Derived from OpenWrt patches:
 * Copyright (C) 2013 Jonas Gorski <jonas.gorski@gmail.com>
 * Copyright (C) 2013 Florian Fainelli <f.fainelli@gmail.com>
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

/* USBH control रेजिस्टर offsets */
क्रमागत usbh_regs अणु
	USBH_BRT_CONTROL1 = 0,
	USBH_BRT_CONTROL2,
	USBH_BRT_STATUS1,
	USBH_BRT_STATUS2,
	USBH_UTMI_CONTROL1,
#घोषणा   USBH_UC1_DEV_MODE_SEL		BIT(0)
	USBH_TEST_PORT_CONTROL,
	USBH_PLL_CONTROL1,
#घोषणा   USBH_PLLC_REFCLKSEL_SHIFT	0
#घोषणा   USBH_PLLC_REFCLKSEL_MASK	(0x3 << USBH_PLLC_REFCLKSEL_SHIFT)
#घोषणा   USBH_PLLC_CLKSEL_SHIFT	2
#घोषणा   USBH_PLLC_CLKSEL_MASK		(0x3 << USBH_PLLC_CLKSEL_MASK)
#घोषणा   USBH_PLLC_XTAL_PWRDWNB	BIT(4)
#घोषणा   USBH_PLLC_PLL_PWRDWNB		BIT(5)
#घोषणा   USBH_PLLC_PLL_CALEN		BIT(6)
#घोषणा   USBH_PLLC_PHYPLL_BYP		BIT(7)
#घोषणा   USBH_PLLC_PLL_RESET		BIT(8)
#घोषणा   USBH_PLLC_PLL_IDDQ_PWRDN	BIT(9)
#घोषणा   USBH_PLLC_PLL_PWRDN_DELAY	BIT(10)
#घोषणा   USBH_6318_PLLC_PLL_SUSPEND_EN	BIT(27)
#घोषणा   USBH_6318_PLLC_PHYPLL_BYP	BIT(29)
#घोषणा   USBH_6318_PLLC_PLL_RESET	BIT(30)
#घोषणा   USBH_6318_PLLC_PLL_IDDQ_PWRDN	BIT(31)
	USBH_SWAP_CONTROL,
#घोषणा   USBH_SC_OHCI_DATA_SWAP	BIT(0)
#घोषणा   USBH_SC_OHCI_ENDIAN_SWAP	BIT(1)
#घोषणा   USBH_SC_OHCI_LOGICAL_ADDR_EN	BIT(2)
#घोषणा   USBH_SC_EHCI_DATA_SWAP	BIT(3)
#घोषणा   USBH_SC_EHCI_ENDIAN_SWAP	BIT(4)
#घोषणा   USBH_SC_EHCI_LOGICAL_ADDR_EN	BIT(5)
#घोषणा   USBH_SC_USB_DEVICE_SEL	BIT(6)
	USBH_GENERIC_CONTROL,
#घोषणा   USBH_GC_PLL_SUSPEND_EN	BIT(1)
	USBH_FRAME_ADJUST_VALUE,
	USBH_SETUP,
#घोषणा   USBH_S_IOC			BIT(4)
#घोषणा   USBH_S_IPP			BIT(5)
	USBH_MDIO,
	USBH_MDIO32,
	USBH_USB_SIM_CONTROL,
#घोषणा   USBH_USC_LADDR_SEL		BIT(5)

	__USBH_ENUM_SIZE
पूर्ण;

काष्ठा bcm63xx_usbh_phy_variant अणु
	/* Registers */
	दीर्घ regs[__USBH_ENUM_SIZE];

	/* PLLC bits to set/clear क्रम घातer on */
	u32 घातer_pllc_clr;
	u32 घातer_pllc_set;

	/* Setup bits to set/clear क्रम घातer on */
	u32 setup_clr;
	u32 setup_set;

	/* Swap Control bits to set */
	u32 swapctl_dev_set;

	/* Test Port Control value to set अगर non-zero */
	u32 tpc_val;

	/* USB Sim Control bits to set */
	u32 usc_set;

	/* UTMI Control 1 bits to set */
	u32 uपंचांगictl1_dev_set;
पूर्ण;

काष्ठा bcm63xx_usbh_phy अणु
	व्योम __iomem *base;
	काष्ठा clk *usbh_clk;
	काष्ठा clk *usb_ref_clk;
	काष्ठा reset_control *reset;
	स्थिर काष्ठा bcm63xx_usbh_phy_variant *variant;
	bool device_mode;
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_usbh_phy_variant usbh_bcm6318 = अणु
	.regs = अणु
		[USBH_BRT_CONTROL1] = -1,
		[USBH_BRT_CONTROL2] = -1,
		[USBH_BRT_STATUS1] = -1,
		[USBH_BRT_STATUS2] = -1,
		[USBH_UTMI_CONTROL1] = 0x2c,
		[USBH_TEST_PORT_CONTROL] = 0x1c,
		[USBH_PLL_CONTROL1] = 0x04,
		[USBH_SWAP_CONTROL] = 0x0c,
		[USBH_GENERIC_CONTROL] = -1,
		[USBH_FRAME_ADJUST_VALUE] = 0x08,
		[USBH_SETUP] = 0x00,
		[USBH_MDIO] = 0x14,
		[USBH_MDIO32] = 0x18,
		[USBH_USB_SIM_CONTROL] = 0x20,
	पूर्ण,
	.घातer_pllc_clr = USBH_6318_PLLC_PLL_IDDQ_PWRDN,
	.घातer_pllc_set = USBH_6318_PLLC_PLL_SUSPEND_EN,
	.setup_set = USBH_S_IOC,
	.swapctl_dev_set = USBH_SC_USB_DEVICE_SEL,
	.usc_set = USBH_USC_LADDR_SEL,
	.uपंचांगictl1_dev_set = USBH_UC1_DEV_MODE_SEL,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_usbh_phy_variant usbh_bcm6328 = अणु
	.regs = अणु
		[USBH_BRT_CONTROL1] = 0x00,
		[USBH_BRT_CONTROL2] = 0x04,
		[USBH_BRT_STATUS1] = 0x08,
		[USBH_BRT_STATUS2] = 0x0c,
		[USBH_UTMI_CONTROL1] = 0x10,
		[USBH_TEST_PORT_CONTROL] = 0x14,
		[USBH_PLL_CONTROL1] = 0x18,
		[USBH_SWAP_CONTROL] = 0x1c,
		[USBH_GENERIC_CONTROL] = 0x20,
		[USBH_FRAME_ADJUST_VALUE] = 0x24,
		[USBH_SETUP] = 0x28,
		[USBH_MDIO] = 0x2c,
		[USBH_MDIO32] = 0x30,
		[USBH_USB_SIM_CONTROL] = 0x34,
	पूर्ण,
	.setup_set = USBH_S_IOC,
	.swapctl_dev_set = USBH_SC_USB_DEVICE_SEL,
	.uपंचांगictl1_dev_set = USBH_UC1_DEV_MODE_SEL,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_usbh_phy_variant usbh_bcm6358 = अणु
	.regs = अणु
		[USBH_BRT_CONTROL1] = -1,
		[USBH_BRT_CONTROL2] = -1,
		[USBH_BRT_STATUS1] = -1,
		[USBH_BRT_STATUS2] = -1,
		[USBH_UTMI_CONTROL1] = -1,
		[USBH_TEST_PORT_CONTROL] = 0x24,
		[USBH_PLL_CONTROL1] = -1,
		[USBH_SWAP_CONTROL] = 0x00,
		[USBH_GENERIC_CONTROL] = -1,
		[USBH_FRAME_ADJUST_VALUE] = -1,
		[USBH_SETUP] = -1,
		[USBH_MDIO] = -1,
		[USBH_MDIO32] = -1,
		[USBH_USB_SIM_CONTROL] = -1,
	पूर्ण,
	/*
	 * The magic value comes क्रम the original venकरोr BSP
	 * and is needed क्रम USB to work. Datasheet करोes not
	 * help, so the magic value is used as-is.
	 */
	.tpc_val = 0x1c0020,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_usbh_phy_variant usbh_bcm6368 = अणु
	.regs = अणु
		[USBH_BRT_CONTROL1] = 0x00,
		[USBH_BRT_CONTROL2] = 0x04,
		[USBH_BRT_STATUS1] = 0x08,
		[USBH_BRT_STATUS2] = 0x0c,
		[USBH_UTMI_CONTROL1] = 0x10,
		[USBH_TEST_PORT_CONTROL] = 0x14,
		[USBH_PLL_CONTROL1] = 0x18,
		[USBH_SWAP_CONTROL] = 0x1c,
		[USBH_GENERIC_CONTROL] = -1,
		[USBH_FRAME_ADJUST_VALUE] = 0x24,
		[USBH_SETUP] = 0x28,
		[USBH_MDIO] = 0x2c,
		[USBH_MDIO32] = 0x30,
		[USBH_USB_SIM_CONTROL] = 0x34,
	पूर्ण,
	.घातer_pllc_clr = USBH_PLLC_PLL_IDDQ_PWRDN | USBH_PLLC_PLL_PWRDN_DELAY,
	.setup_set = USBH_S_IOC,
	.swapctl_dev_set = USBH_SC_USB_DEVICE_SEL,
	.uपंचांगictl1_dev_set = USBH_UC1_DEV_MODE_SEL,
पूर्ण;

अटल स्थिर काष्ठा bcm63xx_usbh_phy_variant usbh_bcm63268 = अणु
	.regs = अणु
		[USBH_BRT_CONTROL1] = 0x00,
		[USBH_BRT_CONTROL2] = 0x04,
		[USBH_BRT_STATUS1] = 0x08,
		[USBH_BRT_STATUS2] = 0x0c,
		[USBH_UTMI_CONTROL1] = 0x10,
		[USBH_TEST_PORT_CONTROL] = 0x14,
		[USBH_PLL_CONTROL1] = 0x18,
		[USBH_SWAP_CONTROL] = 0x1c,
		[USBH_GENERIC_CONTROL] = 0x20,
		[USBH_FRAME_ADJUST_VALUE] = 0x24,
		[USBH_SETUP] = 0x28,
		[USBH_MDIO] = 0x2c,
		[USBH_MDIO32] = 0x30,
		[USBH_USB_SIM_CONTROL] = 0x34,
	पूर्ण,
	.घातer_pllc_clr = USBH_PLLC_PLL_IDDQ_PWRDN | USBH_PLLC_PLL_PWRDN_DELAY,
	.setup_clr = USBH_S_IPP,
	.setup_set = USBH_S_IOC,
	.swapctl_dev_set = USBH_SC_USB_DEVICE_SEL,
	.uपंचांगictl1_dev_set = USBH_UC1_DEV_MODE_SEL,
पूर्ण;

अटल अंतरभूत bool usbh_has_reg(काष्ठा bcm63xx_usbh_phy *usbh, पूर्णांक reg)
अणु
	वापस (usbh->variant->regs[reg] >= 0);
पूर्ण

अटल अंतरभूत u32 usbh_पढ़ोl(काष्ठा bcm63xx_usbh_phy *usbh, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(usbh->base + usbh->variant->regs[reg]);
पूर्ण

अटल अंतरभूत व्योम usbh_ग_लिखोl(काष्ठा bcm63xx_usbh_phy *usbh, पूर्णांक reg,
			       u32 value)
अणु
	__raw_ग_लिखोl(value, usbh->base + usbh->variant->regs[reg]);
पूर्ण

अटल पूर्णांक bcm63xx_usbh_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा bcm63xx_usbh_phy *usbh = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(usbh->usbh_clk);
	अगर (ret) अणु
		dev_err(&phy->dev, "unable to enable usbh clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(usbh->usb_ref_clk);
	अगर (ret) अणु
		dev_err(&phy->dev, "unable to enable usb_ref clock: %d\n", ret);
		clk_disable_unprepare(usbh->usbh_clk);
		वापस ret;
	पूर्ण

	ret = reset_control_reset(usbh->reset);
	अगर (ret) अणु
		dev_err(&phy->dev, "unable to reset device: %d\n", ret);
		clk_disable_unprepare(usbh->usb_ref_clk);
		clk_disable_unprepare(usbh->usbh_clk);
		वापस ret;
	पूर्ण

	/* Configure to work in native CPU endian */
	अगर (usbh_has_reg(usbh, USBH_SWAP_CONTROL)) अणु
		u32 val = usbh_पढ़ोl(usbh, USBH_SWAP_CONTROL);

		val |= USBH_SC_EHCI_DATA_SWAP;
		val &= ~USBH_SC_EHCI_ENDIAN_SWAP;

		val |= USBH_SC_OHCI_DATA_SWAP;
		val &= ~USBH_SC_OHCI_ENDIAN_SWAP;

		अगर (usbh->device_mode && usbh->variant->swapctl_dev_set)
			val |= usbh->variant->swapctl_dev_set;

		usbh_ग_लिखोl(usbh, USBH_SWAP_CONTROL, val);
	पूर्ण

	अगर (usbh_has_reg(usbh, USBH_SETUP)) अणु
		u32 val = usbh_पढ़ोl(usbh, USBH_SETUP);

		val |= usbh->variant->setup_set;
		val &= ~usbh->variant->setup_clr;

		usbh_ग_लिखोl(usbh, USBH_SETUP, val);
	पूर्ण

	अगर (usbh_has_reg(usbh, USBH_USB_SIM_CONTROL)) अणु
		u32 val = usbh_पढ़ोl(usbh, USBH_USB_SIM_CONTROL);

		val |= usbh->variant->usc_set;

		usbh_ग_लिखोl(usbh, USBH_USB_SIM_CONTROL, val);
	पूर्ण

	अगर (usbh->variant->tpc_val &&
	    usbh_has_reg(usbh, USBH_TEST_PORT_CONTROL))
		usbh_ग_लिखोl(usbh, USBH_TEST_PORT_CONTROL,
			    usbh->variant->tpc_val);

	अगर (usbh->device_mode &&
	    usbh_has_reg(usbh, USBH_UTMI_CONTROL1) &&
	    usbh->variant->uपंचांगictl1_dev_set) अणु
		u32 val = usbh_पढ़ोl(usbh, USBH_UTMI_CONTROL1);

		val |= usbh->variant->uपंचांगictl1_dev_set;

		usbh_ग_लिखोl(usbh, USBH_UTMI_CONTROL1, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_usbh_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा bcm63xx_usbh_phy *usbh = phy_get_drvdata(phy);

	अगर (usbh_has_reg(usbh, USBH_PLL_CONTROL1)) अणु
		u32 val = usbh_पढ़ोl(usbh, USBH_PLL_CONTROL1);

		val |= usbh->variant->घातer_pllc_set;
		val &= ~usbh->variant->घातer_pllc_clr;

		usbh_ग_लिखोl(usbh, USBH_PLL_CONTROL1, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_usbh_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा bcm63xx_usbh_phy *usbh = phy_get_drvdata(phy);

	अगर (usbh_has_reg(usbh, USBH_PLL_CONTROL1)) अणु
		u32 val = usbh_पढ़ोl(usbh, USBH_PLL_CONTROL1);

		val &= ~usbh->variant->घातer_pllc_set;
		val |= usbh->variant->घातer_pllc_clr;

		usbh_ग_लिखोl(usbh, USBH_PLL_CONTROL1, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_usbh_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा bcm63xx_usbh_phy *usbh = phy_get_drvdata(phy);

	clk_disable_unprepare(usbh->usbh_clk);
	clk_disable_unprepare(usbh->usb_ref_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops bcm63xx_usbh_phy_ops = अणु
	.निकास = bcm63xx_usbh_phy_निकास,
	.init = bcm63xx_usbh_phy_init,
	.घातer_off = bcm63xx_usbh_phy_घातer_off,
	.घातer_on = bcm63xx_usbh_phy_घातer_on,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *bcm63xx_usbh_phy_xlate(काष्ठा device *dev,
					  काष्ठा of_phandle_args *args)
अणु
	काष्ठा bcm63xx_usbh_phy *usbh = dev_get_drvdata(dev);

	usbh->device_mode = !!args->args[0];

	वापस of_phy_simple_xlate(dev, args);
पूर्ण

अटल पूर्णांक __init bcm63xx_usbh_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm63xx_usbh_phy	*usbh;
	स्थिर काष्ठा bcm63xx_usbh_phy_variant *variant;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;

	usbh = devm_kzalloc(dev, माप(*usbh), GFP_KERNEL);
	अगर (!usbh)
		वापस -ENOMEM;

	variant = device_get_match_data(dev);
	अगर (!variant)
		वापस -EINVAL;
	usbh->variant = variant;

	usbh->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(usbh->base))
		वापस PTR_ERR(usbh->base);

	usbh->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(usbh->reset)) अणु
		अगर (PTR_ERR(usbh->reset) != -EPROBE_DEFER)
			dev_err(dev, "failed to get reset\n");
		वापस PTR_ERR(usbh->reset);
	पूर्ण

	usbh->usbh_clk = devm_clk_get_optional(dev, "usbh");
	अगर (IS_ERR(usbh->usbh_clk))
		वापस PTR_ERR(usbh->usbh_clk);

	usbh->usb_ref_clk = devm_clk_get_optional(dev, "usb_ref");
	अगर (IS_ERR(usbh->usb_ref_clk))
		वापस PTR_ERR(usbh->usb_ref_clk);

	phy = devm_phy_create(dev, शून्य, &bcm63xx_usbh_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	platक्रमm_set_drvdata(pdev, usbh);
	phy_set_drvdata(phy, usbh);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
						     bcm63xx_usbh_phy_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(dev, "failed to register PHY provider\n");
		वापस PTR_ERR(phy_provider);
	पूर्ण

	dev_dbg(dev, "Registered BCM63xx USB PHY driver\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm63xx_usbh_phy_ids[] __initस्थिर = अणु
	अणु .compatible = "brcm,bcm6318-usbh-phy", .data = &usbh_bcm6318 पूर्ण,
	अणु .compatible = "brcm,bcm6328-usbh-phy", .data = &usbh_bcm6328 पूर्ण,
	अणु .compatible = "brcm,bcm6358-usbh-phy", .data = &usbh_bcm6358 पूर्ण,
	अणु .compatible = "brcm,bcm6362-usbh-phy", .data = &usbh_bcm6368 पूर्ण,
	अणु .compatible = "brcm,bcm6368-usbh-phy", .data = &usbh_bcm6368 पूर्ण,
	अणु .compatible = "brcm,bcm63268-usbh-phy", .data = &usbh_bcm63268 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm63xx_usbh_phy_ids);

अटल काष्ठा platक्रमm_driver bcm63xx_usbh_phy_driver __refdata = अणु
	.driver	= अणु
		.name = "bcm63xx-usbh-phy",
		.of_match_table = bcm63xx_usbh_phy_ids,
	पूर्ण,
	.probe	= bcm63xx_usbh_phy_probe,
पूर्ण;
module_platक्रमm_driver(bcm63xx_usbh_phy_driver);

MODULE_DESCRIPTION("BCM63xx USBH PHY driver");
MODULE_AUTHOR("थlvaro Fernथँndez Rojas <noltari@gmail.com>");
MODULE_AUTHOR("Simon Arlott");
MODULE_LICENSE("GPL");
