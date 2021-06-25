<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom Northstar USB 2.0 PHY Driver
 *
 * Copyright (C) 2016 Rafaध Miधecki <zajec5@gmail.com>
 */

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा bcm_ns_usb2 अणु
	काष्ठा device *dev;
	काष्ठा clk *ref_clk;
	काष्ठा phy *phy;
	व्योम __iomem *dmu;
पूर्ण;

अटल पूर्णांक bcm_ns_usb2_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा bcm_ns_usb2 *usb2 = phy_get_drvdata(phy);
	काष्ठा device *dev = usb2->dev;
	व्योम __iomem *dmu = usb2->dmu;
	u32 ref_clk_rate, usb2ctl, usb_pll_nभाग, usb_pll_pभाग;
	पूर्णांक err = 0;

	err = clk_prepare_enable(usb2->ref_clk);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to prepare ref clock: %d\n", err);
		जाओ err_out;
	पूर्ण

	ref_clk_rate = clk_get_rate(usb2->ref_clk);
	अगर (!ref_clk_rate) अणु
		dev_err(dev, "Failed to get ref clock rate\n");
		err = -EINVAL;
		जाओ err_clk_off;
	पूर्ण

	usb2ctl = पढ़ोl(dmu + BCMA_DMU_CRU_USB2_CONTROL);

	अगर (usb2ctl & BCMA_DMU_CRU_USB2_CONTROL_USB_PLL_PDIV_MASK) अणु
		usb_pll_pभाग = usb2ctl;
		usb_pll_pभाग &= BCMA_DMU_CRU_USB2_CONTROL_USB_PLL_PDIV_MASK;
		usb_pll_pभाग >>= BCMA_DMU_CRU_USB2_CONTROL_USB_PLL_PDIV_SHIFT;
	पूर्ण अन्यथा अणु
		usb_pll_pभाग = 1 << 3;
	पूर्ण

	/* Calculate nभाग based on a solid 1920 MHz that is क्रम USB2 PHY */
	usb_pll_nभाग = (1920000000 * usb_pll_pभाग) / ref_clk_rate;

	/* Unlock DMU PLL settings with some magic value */
	ग_लिखोl(0x0000ea68, dmu + BCMA_DMU_CRU_CLKSET_KEY);

	/* Write USB 2.0 PLL control setting */
	usb2ctl &= ~BCMA_DMU_CRU_USB2_CONTROL_USB_PLL_NDIV_MASK;
	usb2ctl |= usb_pll_nभाग << BCMA_DMU_CRU_USB2_CONTROL_USB_PLL_NDIV_SHIFT;
	ग_लिखोl(usb2ctl, dmu + BCMA_DMU_CRU_USB2_CONTROL);

	/* Lock DMU PLL settings */
	ग_लिखोl(0x00000000, dmu + BCMA_DMU_CRU_CLKSET_KEY);

err_clk_off:
	clk_disable_unprepare(usb2->ref_clk);
err_out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= bcm_ns_usb2_phy_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक bcm_ns_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm_ns_usb2 *usb2;
	काष्ठा phy_provider *phy_provider;

	usb2 = devm_kzalloc(&pdev->dev, माप(*usb2), GFP_KERNEL);
	अगर (!usb2)
		वापस -ENOMEM;
	usb2->dev = dev;

	usb2->dmu = devm_platक्रमm_ioremap_resource_byname(pdev, "dmu");
	अगर (IS_ERR(usb2->dmu)) अणु
		dev_err(dev, "Failed to map DMU regs\n");
		वापस PTR_ERR(usb2->dmu);
	पूर्ण

	usb2->ref_clk = devm_clk_get(dev, "phy-ref-clk");
	अगर (IS_ERR(usb2->ref_clk)) अणु
		dev_err(dev, "Clock not defined\n");
		वापस PTR_ERR(usb2->ref_clk);
	पूर्ण

	usb2->phy = devm_phy_create(dev, शून्य, &ops);
	अगर (IS_ERR(usb2->phy))
		वापस PTR_ERR(usb2->phy);

	phy_set_drvdata(usb2->phy, usb2);
	platक्रमm_set_drvdata(pdev, usb2);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_ns_usb2_id_table[] = अणु
	अणु .compatible = "brcm,ns-usb2-phy", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_ns_usb2_id_table);

अटल काष्ठा platक्रमm_driver bcm_ns_usb2_driver = अणु
	.probe		= bcm_ns_usb2_probe,
	.driver = अणु
		.name = "bcm_ns_usb2",
		.of_match_table = bcm_ns_usb2_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(bcm_ns_usb2_driver);

MODULE_LICENSE("GPL v2");
