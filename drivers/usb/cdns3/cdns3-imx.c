<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * cdns3-imx.c - NXP i.MX specअगरic Glue layer क्रम Cadence USB Controller
 *
 * Copyright (C) 2019 NXP
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "core.h"

#घोषणा USB3_CORE_CTRL1    0x00
#घोषणा USB3_CORE_CTRL2    0x04
#घोषणा USB3_INT_REG       0x08
#घोषणा USB3_CORE_STATUS   0x0c
#घोषणा XHCI_DEBUG_LINK_ST 0x10
#घोषणा XHCI_DEBUG_BUS     0x14
#घोषणा USB3_SSPHY_CTRL1   0x40
#घोषणा USB3_SSPHY_CTRL2   0x44
#घोषणा USB3_SSPHY_STATUS  0x4c
#घोषणा USB2_PHY_CTRL1     0x50
#घोषणा USB2_PHY_CTRL2     0x54
#घोषणा USB2_PHY_STATUS    0x5c

/* Register bits definition */

/* USB3_CORE_CTRL1 */
#घोषणा SW_RESET_MASK	GENMASK(31, 26)
#घोषणा PWR_SW_RESET	BIT(31)
#घोषणा APB_SW_RESET	BIT(30)
#घोषणा AXI_SW_RESET	BIT(29)
#घोषणा RW_SW_RESET	BIT(28)
#घोषणा PHY_SW_RESET	BIT(27)
#घोषणा PHYAHB_SW_RESET	BIT(26)
#घोषणा ALL_SW_RESET	(PWR_SW_RESET | APB_SW_RESET | AXI_SW_RESET | \
		RW_SW_RESET | PHY_SW_RESET | PHYAHB_SW_RESET)
#घोषणा OC_DISABLE	BIT(9)
#घोषणा MDCTRL_CLK_SEL	BIT(7)
#घोषणा MODE_STRAP_MASK	(0x7)
#घोषणा DEV_MODE	(1 << 2)
#घोषणा HOST_MODE	(1 << 1)
#घोषणा OTG_MODE	(1 << 0)

/* USB3_INT_REG */
#घोषणा CLK_125_REQ	BIT(29)
#घोषणा LPM_CLK_REQ	BIT(28)
#घोषणा DEVU3_WAEKUP_EN	BIT(14)
#घोषणा OTG_WAKEUP_EN	BIT(12)
#घोषणा DEV_INT_EN	(3 << 8) /* DEV INT b9:8 */
#घोषणा HOST_INT1_EN	(1 << 0) /* HOST INT b7:0 */

/* USB3_CORE_STATUS */
#घोषणा MDCTRL_CLK_STATUS	BIT(15)
#घोषणा DEV_POWER_ON_READY	BIT(13)
#घोषणा HOST_POWER_ON_READY	BIT(12)

/* USB3_SSPHY_STATUS */
#घोषणा CLK_VALID_MASK		(0x3f << 26)
#घोषणा CLK_VALID_COMPARE_BITS	(0xf << 28)
#घोषणा PHY_REFCLK_REQ		(1 << 0)

/* OTG रेजिस्टरs definition */
#घोषणा OTGSTS		0x4
/* OTGSTS */
#घोषणा OTG_NRDY	BIT(11)

/* xHCI रेजिस्टरs definition  */
#घोषणा XECP_PM_PMCSR		0x8018
#घोषणा XECP_AUX_CTRL_REG1	0x8120

/* Register bits definition */
/* XECP_AUX_CTRL_REG1 */
#घोषणा CFG_RXDET_P3_EN		BIT(15)

/* XECP_PM_PMCSR */
#घोषणा PS_MASK			GENMASK(1, 0)
#घोषणा PS_D0			0
#घोषणा PS_D1			1

काष्ठा cdns_imx अणु
	काष्ठा device *dev;
	व्योम __iomem *noncore;
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
	काष्ठा platक्रमm_device *cdns3_pdev;
पूर्ण;

अटल अंतरभूत u32 cdns_imx_पढ़ोl(काष्ठा cdns_imx *data, u32 offset)
अणु
	वापस पढ़ोl(data->noncore + offset);
पूर्ण

अटल अंतरभूत व्योम cdns_imx_ग_लिखोl(काष्ठा cdns_imx *data, u32 offset, u32 value)
अणु
	ग_लिखोl(value, data->noncore + offset);
पूर्ण

अटल स्थिर काष्ठा clk_bulk_data imx_cdns3_core_clks[] = अणु
	अणु .id = "usb3_lpm_clk" पूर्ण,
	अणु .id = "usb3_bus_clk" पूर्ण,
	अणु .id = "usb3_aclk" पूर्ण,
	अणु .id = "usb3_ipg_clk" पूर्ण,
	अणु .id = "usb3_core_pclk" पूर्ण,
पूर्ण;

अटल पूर्णांक cdns_imx_noncore_init(काष्ठा cdns_imx *data)
अणु
	u32 value;
	पूर्णांक ret;
	काष्ठा device *dev = data->dev;

	cdns_imx_ग_लिखोl(data, USB3_SSPHY_STATUS, CLK_VALID_MASK);
	udelay(1);
	ret = पढ़ोl_poll_समयout(data->noncore + USB3_SSPHY_STATUS, value,
		(value & CLK_VALID_COMPARE_BITS) == CLK_VALID_COMPARE_BITS,
		10, 100000);
	अगर (ret) अणु
		dev_err(dev, "wait clkvld timeout\n");
		वापस ret;
	पूर्ण

	value = cdns_imx_पढ़ोl(data, USB3_CORE_CTRL1);
	value |= ALL_SW_RESET;
	cdns_imx_ग_लिखोl(data, USB3_CORE_CTRL1, value);
	udelay(1);

	value = cdns_imx_पढ़ोl(data, USB3_CORE_CTRL1);
	value = (value & ~MODE_STRAP_MASK) | OTG_MODE | OC_DISABLE;
	cdns_imx_ग_लिखोl(data, USB3_CORE_CTRL1, value);

	value = cdns_imx_पढ़ोl(data, USB3_INT_REG);
	value |= HOST_INT1_EN | DEV_INT_EN;
	cdns_imx_ग_लिखोl(data, USB3_INT_REG, value);

	value = cdns_imx_पढ़ोl(data, USB3_CORE_CTRL1);
	value &= ~ALL_SW_RESET;
	cdns_imx_ग_लिखोl(data, USB3_CORE_CTRL1, value);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns_imx_platक्रमm_suspend(काष्ठा device *dev,
	bool suspend, bool wakeup);
अटल काष्ठा cdns3_platक्रमm_data cdns_imx_pdata = अणु
	.platक्रमm_suspend = cdns_imx_platक्रमm_suspend,
	.quirks		  = CDNS3_DEFAULT_PM_RUNTIME_ALLOW,
पूर्ण;

अटल स्थिर काष्ठा of_dev_auxdata cdns_imx_auxdata[] = अणु
	अणु
		.compatible = "cdns,usb3",
		.platक्रमm_data = &cdns_imx_pdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक cdns_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा cdns_imx *data;
	पूर्णांक ret;

	अगर (!node)
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);
	data->dev = dev;
	data->noncore = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->noncore)) अणु
		dev_err(dev, "can't map IOMEM resource\n");
		वापस PTR_ERR(data->noncore);
	पूर्ण

	data->num_clks = ARRAY_SIZE(imx_cdns3_core_clks);
	data->clks = devm_kmemdup(dev, imx_cdns3_core_clks,
				माप(imx_cdns3_core_clks), GFP_KERNEL);
	अगर (!data->clks)
		वापस -ENOMEM;

	ret = devm_clk_bulk_get(dev, data->num_clks, data->clks);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(data->num_clks, data->clks);
	अगर (ret)
		वापस ret;

	ret = cdns_imx_noncore_init(data);
	अगर (ret)
		जाओ err;

	ret = of_platक्रमm_populate(node, शून्य, cdns_imx_auxdata, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to create children: %d\n", ret);
		जाओ err;
	पूर्ण

	device_set_wakeup_capable(dev, true);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस ret;
err:
	clk_bulk_disable_unprepare(data->num_clks, data->clks);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cdns_imx *data = dev_get_drvdata(dev);

	pm_runसमय_get_sync(dev);
	of_platक्रमm_depopulate(dev);
	clk_bulk_disable_unprepare(data->num_clks, data->clks);
	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम cdns3_set_wakeup(काष्ठा cdns_imx *data, bool enable)
अणु
	u32 value;

	value = cdns_imx_पढ़ोl(data, USB3_INT_REG);
	अगर (enable)
		value |= OTG_WAKEUP_EN | DEVU3_WAEKUP_EN;
	अन्यथा
		value &= ~(OTG_WAKEUP_EN | DEVU3_WAEKUP_EN);

	cdns_imx_ग_लिखोl(data, USB3_INT_REG, value);
पूर्ण

अटल पूर्णांक cdns_imx_platक्रमm_suspend(काष्ठा device *dev,
		bool suspend, bool wakeup)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);
	काष्ठा device *parent = dev->parent;
	काष्ठा cdns_imx *data = dev_get_drvdata(parent);
	व्योम __iomem *otg_regs = (व्योम __iomem *)(cdns->otg_regs);
	व्योम __iomem *xhci_regs = cdns->xhci_regs;
	u32 value;
	पूर्णांक ret = 0;

	अगर (cdns->role != USB_ROLE_HOST)
		वापस 0;

	अगर (suspend) अणु
		/* SW request low घातer when all usb ports allow to it ??? */
		value = पढ़ोl(xhci_regs + XECP_PM_PMCSR);
		value &= ~PS_MASK;
		value |= PS_D1;
		ग_लिखोl(value, xhci_regs + XECP_PM_PMCSR);

		/* mdctrl_clk_sel */
		value = cdns_imx_पढ़ोl(data, USB3_CORE_CTRL1);
		value |= MDCTRL_CLK_SEL;
		cdns_imx_ग_लिखोl(data, USB3_CORE_CTRL1, value);

		/* रुको क्रम mdctrl_clk_status */
		value = cdns_imx_पढ़ोl(data, USB3_CORE_STATUS);
		ret = पढ़ोl_poll_समयout(data->noncore + USB3_CORE_STATUS, value,
			(value & MDCTRL_CLK_STATUS) == MDCTRL_CLK_STATUS,
			10, 100000);
		अगर (ret)
			dev_warn(parent, "wait mdctrl_clk_status timeout\n");

		/* रुको lpm_clk_req to be 0 */
		value = cdns_imx_पढ़ोl(data, USB3_INT_REG);
		ret = पढ़ोl_poll_समयout(data->noncore + USB3_INT_REG, value,
			(value & LPM_CLK_REQ) != LPM_CLK_REQ,
			10, 100000);
		अगर (ret)
			dev_warn(parent, "wait lpm_clk_req timeout\n");

		/* रुको phy_refclk_req to be 0 */
		value = cdns_imx_पढ़ोl(data, USB3_SSPHY_STATUS);
		ret = पढ़ोl_poll_समयout(data->noncore + USB3_SSPHY_STATUS, value,
			(value & PHY_REFCLK_REQ) != PHY_REFCLK_REQ,
			10, 100000);
		अगर (ret)
			dev_warn(parent, "wait phy_refclk_req timeout\n");

		cdns3_set_wakeup(data, wakeup);
	पूर्ण अन्यथा अणु
		cdns3_set_wakeup(data, false);

		/* SW request D0 */
		value = पढ़ोl(xhci_regs + XECP_PM_PMCSR);
		value &= ~PS_MASK;
		value |= PS_D0;
		ग_लिखोl(value, xhci_regs + XECP_PM_PMCSR);

		/* clr CFG_RXDET_P3_EN */
		value = पढ़ोl(xhci_regs + XECP_AUX_CTRL_REG1);
		value &= ~CFG_RXDET_P3_EN;
		ग_लिखोl(value, xhci_regs + XECP_AUX_CTRL_REG1);

		/* clear mdctrl_clk_sel */
		value = cdns_imx_पढ़ोl(data, USB3_CORE_CTRL1);
		value &= ~MDCTRL_CLK_SEL;
		cdns_imx_ग_लिखोl(data, USB3_CORE_CTRL1, value);

		/* रुको CLK_125_REQ to be 1 */
		value = cdns_imx_पढ़ोl(data, USB3_INT_REG);
		ret = पढ़ोl_poll_समयout(data->noncore + USB3_INT_REG, value,
			(value & CLK_125_REQ) == CLK_125_REQ,
			10, 100000);
		अगर (ret)
			dev_warn(parent, "wait CLK_125_REQ timeout\n");

		/* रुको क्रम mdctrl_clk_status is cleared */
		value = cdns_imx_पढ़ोl(data, USB3_CORE_STATUS);
		ret = पढ़ोl_poll_समयout(data->noncore + USB3_CORE_STATUS, value,
			(value & MDCTRL_CLK_STATUS) != MDCTRL_CLK_STATUS,
			10, 100000);
		अगर (ret)
			dev_warn(parent, "wait mdctrl_clk_status cleared timeout\n");

		/* Wait until OTG_NRDY is 0 */
		value = पढ़ोl(otg_regs + OTGSTS);
		ret = पढ़ोl_poll_समयout(otg_regs + OTGSTS, value,
			(value & OTG_NRDY) != OTG_NRDY,
			10, 100000);
		अगर (ret)
			dev_warn(parent, "wait OTG ready timeout\n");
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक cdns_imx_resume(काष्ठा device *dev)
अणु
	काष्ठा cdns_imx *data = dev_get_drvdata(dev);

	वापस clk_bulk_prepare_enable(data->num_clks, data->clks);
पूर्ण

अटल पूर्णांक cdns_imx_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns_imx *data = dev_get_drvdata(dev);

	clk_bulk_disable_unprepare(data->num_clks, data->clks);

	वापस 0;
पूर्ण


/* Indicate अगर the controller was घातer lost beक्रमe */
अटल अंतरभूत bool cdns_imx_is_घातer_lost(काष्ठा cdns_imx *data)
अणु
	u32 value;

	value = cdns_imx_पढ़ोl(data, USB3_CORE_CTRL1);
	अगर ((value & SW_RESET_MASK) == ALL_SW_RESET)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक __maybe_unused cdns_imx_प्रणाली_resume(काष्ठा device *dev)
अणु
	काष्ठा cdns_imx *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = cdns_imx_resume(dev);
	अगर (ret)
		वापस ret;

	अगर (cdns_imx_is_घातer_lost(data)) अणु
		dev_dbg(dev, "resume from power lost\n");
		ret = cdns_imx_noncore_init(data);
		अगर (ret)
			cdns_imx_suspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

#अन्यथा
अटल पूर्णांक cdns_imx_platक्रमm_suspend(काष्ठा device *dev,
	bool suspend, bool wakeup)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops cdns_imx_pm_ops = अणु
	SET_RUNTIME_PM_OPS(cdns_imx_suspend, cdns_imx_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(cdns_imx_suspend, cdns_imx_प्रणाली_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_imx_of_match[] = अणु
	अणु .compatible = "fsl,imx8qm-usb3", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_imx_of_match);

अटल काष्ठा platक्रमm_driver cdns_imx_driver = अणु
	.probe		= cdns_imx_probe,
	.हटाओ		= cdns_imx_हटाओ,
	.driver		= अणु
		.name	= "cdns3-imx",
		.of_match_table	= cdns_imx_of_match,
		.pm	= &cdns_imx_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cdns_imx_driver);

MODULE_ALIAS("platform:cdns3-imx");
MODULE_AUTHOR("Peter Chen <peter.chen@nxp.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Cadence USB3 i.MX Glue Layer");
