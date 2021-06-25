<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-xilinx.c - Xilinx DWC3 controller specअगरic glue driver
 *
 * Authors: Manish Narani <manish.narani@xilinx.com>
 *          Anurag Kumar Vulisha <anurag.kumar.vulisha@xilinx.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware/xlnx-zynqmp.h>
#समावेश <linux/पन.स>

#समावेश <linux/phy/phy.h>

/* USB phy reset mask रेजिस्टर */
#घोषणा XLNX_USB_PHY_RST_EN			0x001C
#घोषणा XLNX_PHY_RST_MASK			0x1

/* Xilinx USB 3.0 IP Register */
#घोषणा XLNX_USB_TRAFFIC_ROUTE_CONFIG		0x005C
#घोषणा XLNX_USB_TRAFFIC_ROUTE_FPD		0x1

/* Versal USB Reset ID */
#घोषणा VERSAL_USB_RESET_ID			0xC104036

#घोषणा XLNX_USB_FPD_PIPE_CLK			0x7c
#घोषणा PIPE_CLK_DESELECT			1
#घोषणा PIPE_CLK_SELECT				0
#घोषणा XLNX_USB_FPD_POWER_PRSNT		0x80
#घोषणा FPD_POWER_PRSNT_OPTION			BIT(0)

काष्ठा dwc3_xlnx अणु
	पूर्णांक				num_घड़ीs;
	काष्ठा clk_bulk_data		*clks;
	काष्ठा device			*dev;
	व्योम __iomem			*regs;
	पूर्णांक				(*pltfm_init)(काष्ठा dwc3_xlnx *data);
पूर्ण;

अटल व्योम dwc3_xlnx_mask_phy_rst(काष्ठा dwc3_xlnx *priv_data, bool mask)
अणु
	u32 reg;

	/*
	 * Enable or disable ULPI PHY reset from USB Controller.
	 * This करोes not actually reset the phy, but just controls
	 * whether USB controller can or cannot reset ULPI PHY.
	 */
	reg = पढ़ोl(priv_data->regs + XLNX_USB_PHY_RST_EN);

	अगर (mask)
		reg &= ~XLNX_PHY_RST_MASK;
	अन्यथा
		reg |= XLNX_PHY_RST_MASK;

	ग_लिखोl(reg, priv_data->regs + XLNX_USB_PHY_RST_EN);
पूर्ण

अटल पूर्णांक dwc3_xlnx_init_versal(काष्ठा dwc3_xlnx *priv_data)
अणु
	काष्ठा device		*dev = priv_data->dev;
	पूर्णांक			ret;

	dwc3_xlnx_mask_phy_rst(priv_data, false);

	/* Assert and De-निश्चित reset */
	ret = zynqmp_pm_reset_निश्चित(VERSAL_USB_RESET_ID,
				     PM_RESET_ACTION_ASSERT);
	अगर (ret < 0) अणु
		dev_err_probe(dev, ret, "failed to assert Reset\n");
		वापस ret;
	पूर्ण

	ret = zynqmp_pm_reset_निश्चित(VERSAL_USB_RESET_ID,
				     PM_RESET_ACTION_RELEASE);
	अगर (ret < 0) अणु
		dev_err_probe(dev, ret, "failed to De-assert Reset\n");
		वापस ret;
	पूर्ण

	dwc3_xlnx_mask_phy_rst(priv_data, true);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_xlnx_init_zynqmp(काष्ठा dwc3_xlnx *priv_data)
अणु
	काष्ठा device		*dev = priv_data->dev;
	काष्ठा reset_control	*crst, *hibrst, *apbrst;
	काष्ठा phy		*usb3_phy;
	पूर्णांक			ret;
	u32			reg;

	usb3_phy = devm_phy_get(dev, "usb3-phy");
	अगर (PTR_ERR(usb3_phy) == -EPROBE_DEFER) अणु
		ret = -EPROBE_DEFER;
		जाओ err;
	पूर्ण अन्यथा अगर (IS_ERR(usb3_phy)) अणु
		usb3_phy = शून्य;
	पूर्ण

	crst = devm_reset_control_get_exclusive(dev, "usb_crst");
	अगर (IS_ERR(crst)) अणु
		ret = PTR_ERR(crst);
		dev_err_probe(dev, ret,
			      "failed to get core reset signal\n");
		जाओ err;
	पूर्ण

	hibrst = devm_reset_control_get_exclusive(dev, "usb_hibrst");
	अगर (IS_ERR(hibrst)) अणु
		ret = PTR_ERR(hibrst);
		dev_err_probe(dev, ret,
			      "failed to get hibernation reset signal\n");
		जाओ err;
	पूर्ण

	apbrst = devm_reset_control_get_exclusive(dev, "usb_apbrst");
	अगर (IS_ERR(apbrst)) अणु
		ret = PTR_ERR(apbrst);
		dev_err_probe(dev, ret,
			      "failed to get APB reset signal\n");
		जाओ err;
	पूर्ण

	ret = reset_control_निश्चित(crst);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to assert core reset\n");
		जाओ err;
	पूर्ण

	ret = reset_control_निश्चित(hibrst);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to assert hibernation reset\n");
		जाओ err;
	पूर्ण

	ret = reset_control_निश्चित(apbrst);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to assert APB reset\n");
		जाओ err;
	पूर्ण

	ret = phy_init(usb3_phy);
	अगर (ret < 0) अणु
		phy_निकास(usb3_phy);
		जाओ err;
	पूर्ण

	ret = reset_control_deनिश्चित(apbrst);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to release APB reset\n");
		जाओ err;
	पूर्ण

	/* Set PIPE Power Present संकेत in FPD Power Present Register*/
	ग_लिखोl(FPD_POWER_PRSNT_OPTION, priv_data->regs + XLNX_USB_FPD_POWER_PRSNT);

	/* Set the PIPE Clock Select bit in FPD PIPE Clock रेजिस्टर */
	ग_लिखोl(PIPE_CLK_SELECT, priv_data->regs + XLNX_USB_FPD_PIPE_CLK);

	ret = reset_control_deनिश्चित(crst);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to release core reset\n");
		जाओ err;
	पूर्ण

	ret = reset_control_deनिश्चित(hibrst);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to release hibernation reset\n");
		जाओ err;
	पूर्ण

	ret = phy_घातer_on(usb3_phy);
	अगर (ret < 0) अणु
		phy_निकास(usb3_phy);
		जाओ err;
	पूर्ण

	/*
	 * This routes the USB DMA traffic to go through FPD path instead
	 * of reaching DDR directly. This traffic routing is needed to
	 * make SMMU and CCI work with USB DMA.
	 */
	अगर (of_dma_is_coherent(dev->of_node) || device_iommu_mapped(dev)) अणु
		reg = पढ़ोl(priv_data->regs + XLNX_USB_TRAFFIC_ROUTE_CONFIG);
		reg |= XLNX_USB_TRAFFIC_ROUTE_FPD;
		ग_लिखोl(reg, priv_data->regs + XLNX_USB_TRAFFIC_ROUTE_CONFIG);
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id dwc3_xlnx_of_match[] = अणु
	अणु
		.compatible = "xlnx,zynqmp-dwc3",
		.data = &dwc3_xlnx_init_zynqmp,
	पूर्ण,
	अणु
		.compatible = "xlnx,versal-dwc3",
		.data = &dwc3_xlnx_init_versal,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dwc3_xlnx_of_match);

अटल पूर्णांक dwc3_xlnx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_xlnx		*priv_data;
	काष्ठा device			*dev = &pdev->dev;
	काष्ठा device_node		*np = dev->of_node;
	स्थिर काष्ठा of_device_id	*match;
	व्योम __iomem			*regs;
	पूर्णांक				ret;

	priv_data = devm_kzalloc(dev, माप(*priv_data), GFP_KERNEL);
	अगर (!priv_data)
		वापस -ENOMEM;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		dev_err_probe(dev, ret, "failed to map registers\n");
		वापस ret;
	पूर्ण

	match = of_match_node(dwc3_xlnx_of_match, pdev->dev.of_node);

	priv_data->pltfm_init = match->data;
	priv_data->regs = regs;
	priv_data->dev = dev;

	platक्रमm_set_drvdata(pdev, priv_data);

	ret = devm_clk_bulk_get_all(priv_data->dev, &priv_data->clks);
	अगर (ret < 0)
		वापस ret;

	priv_data->num_घड़ीs = ret;

	ret = clk_bulk_prepare_enable(priv_data->num_घड़ीs, priv_data->clks);
	अगर (ret)
		वापस ret;

	ret = priv_data->pltfm_init(priv_data);
	अगर (ret)
		जाओ err_clk_put;

	ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
	अगर (ret)
		जाओ err_clk_put;

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_suspend_ignore_children(dev, false);
	pm_runसमय_get_sync(dev);

	वापस 0;

err_clk_put:
	clk_bulk_disable_unprepare(priv_data->num_घड़ीs, priv_data->clks);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_xlnx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_xlnx	*priv_data = platक्रमm_get_drvdata(pdev);
	काष्ठा device		*dev = &pdev->dev;

	of_platक्रमm_depopulate(dev);

	clk_bulk_disable_unprepare(priv_data->num_घड़ीs, priv_data->clks);
	priv_data->num_घड़ीs = 0;

	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_set_suspended(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_xlnx_suspend_common(काष्ठा device *dev)
अणु
	काष्ठा dwc3_xlnx *priv_data = dev_get_drvdata(dev);

	clk_bulk_disable(priv_data->num_घड़ीs, priv_data->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_xlnx_resume_common(काष्ठा device *dev)
अणु
	काष्ठा dwc3_xlnx *priv_data = dev_get_drvdata(dev);

	वापस clk_bulk_enable(priv_data->num_घड़ीs, priv_data->clks);
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_xlnx_runसमय_idle(काष्ठा device *dev)
अणु
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(dwc3_xlnx_dev_pm_ops, dwc3_xlnx_suspend_common,
			    dwc3_xlnx_resume_common, dwc3_xlnx_runसमय_idle);

अटल काष्ठा platक्रमm_driver dwc3_xlnx_driver = अणु
	.probe		= dwc3_xlnx_probe,
	.हटाओ		= dwc3_xlnx_हटाओ,
	.driver		= अणु
		.name		= "dwc3-xilinx",
		.of_match_table	= dwc3_xlnx_of_match,
		.pm		= &dwc3_xlnx_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_xlnx_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Xilinx DWC3 controller specific glue driver");
MODULE_AUTHOR("Manish Narani <manish.narani@xilinx.com>");
MODULE_AUTHOR("Anurag Kumar Vulisha <anurag.kumar.vulisha@xilinx.com>");
