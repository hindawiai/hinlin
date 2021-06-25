<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016, NVIDIA Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>

#समावेश <linux/usb.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/phy.h>

#समावेश "../host/ehci.h"

#समावेश "ci.h"

काष्ठा tegra_usb अणु
	काष्ठा ci_hdrc_platक्रमm_data data;
	काष्ठा platक्रमm_device *dev;

	स्थिर काष्ठा tegra_usb_soc_info *soc;
	काष्ठा usb_phy *phy;
	काष्ठा clk *clk;

	bool needs_द्विगुन_reset;
पूर्ण;

काष्ठा tegra_usb_soc_info अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक txfअगरothresh;
	क्रमागत usb_dr_mode dr_mode;
पूर्ण;

अटल स्थिर काष्ठा tegra_usb_soc_info tegra20_ehci_soc_info = अणु
	.flags = CI_HDRC_REQUIRES_ALIGNED_DMA |
		 CI_HDRC_OVERRIDE_PHY_CONTROL |
		 CI_HDRC_SUPPORTS_RUNTIME_PM,
	.dr_mode = USB_DR_MODE_HOST,
	.txfअगरothresh = 10,
पूर्ण;

अटल स्थिर काष्ठा tegra_usb_soc_info tegra30_ehci_soc_info = अणु
	.flags = CI_HDRC_REQUIRES_ALIGNED_DMA |
		 CI_HDRC_OVERRIDE_PHY_CONTROL |
		 CI_HDRC_SUPPORTS_RUNTIME_PM,
	.dr_mode = USB_DR_MODE_HOST,
	.txfअगरothresh = 16,
पूर्ण;

अटल स्थिर काष्ठा tegra_usb_soc_info tegra20_udc_soc_info = अणु
	.flags = CI_HDRC_REQUIRES_ALIGNED_DMA |
		 CI_HDRC_OVERRIDE_PHY_CONTROL |
		 CI_HDRC_SUPPORTS_RUNTIME_PM,
	.dr_mode = USB_DR_MODE_UNKNOWN,
	.txfअगरothresh = 10,
पूर्ण;

अटल स्थिर काष्ठा tegra_usb_soc_info tegra30_udc_soc_info = अणु
	.flags = CI_HDRC_REQUIRES_ALIGNED_DMA |
		 CI_HDRC_OVERRIDE_PHY_CONTROL |
		 CI_HDRC_SUPPORTS_RUNTIME_PM,
	.dr_mode = USB_DR_MODE_UNKNOWN,
	.txfअगरothresh = 16,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_usb_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra20-ehci",
		.data = &tegra20_ehci_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra30-ehci",
		.data = &tegra30_ehci_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra20-udc",
		.data = &tegra20_udc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra30-udc",
		.data = &tegra30_udc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra114-udc",
		.data = &tegra30_udc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra124-udc",
		.data = &tegra30_udc_soc_info,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_usb_of_match);

अटल पूर्णांक tegra_usb_reset_controller(काष्ठा device *dev)
अणु
	काष्ठा reset_control *rst, *rst_uपंचांगi;
	काष्ठा device_node *phy_np;
	पूर्णांक err;

	rst = devm_reset_control_get_shared(dev, "usb");
	अगर (IS_ERR(rst)) अणु
		dev_err(dev, "can't get ehci reset: %pe\n", rst);
		वापस PTR_ERR(rst);
	पूर्ण

	phy_np = of_parse_phandle(dev->of_node, "nvidia,phy", 0);
	अगर (!phy_np)
		वापस -ENOENT;

	/*
	 * The 1st USB controller contains some UTMI pad रेजिस्टरs that are
	 * global क्रम all the controllers on the chip. Those रेजिस्टरs are
	 * also cleared when reset is निश्चितed to the 1st controller.
	 */
	rst_uपंचांगi = of_reset_control_get_shared(phy_np, "utmi-pads");
	अगर (IS_ERR(rst_uपंचांगi)) अणु
		dev_warn(dev, "can't get utmi-pads reset from the PHY\n");
		dev_warn(dev, "continuing, but please update your DT\n");
	पूर्ण अन्यथा अणु
		/*
		 * PHY driver perक्रमms UTMI-pads reset in a हाल of a
		 * non-legacy DT.
		 */
		reset_control_put(rst_uपंचांगi);
	पूर्ण

	of_node_put(phy_np);

	/* reset control is shared, hence initialize it first */
	err = reset_control_deनिश्चित(rst);
	अगर (err)
		वापस err;

	err = reset_control_निश्चित(rst);
	अगर (err)
		वापस err;

	udelay(1);

	err = reset_control_deनिश्चित(rst);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_usb_notअगरy_event(काष्ठा ci_hdrc *ci, अचिन्हित पूर्णांक event)
अणु
	काष्ठा tegra_usb *usb = dev_get_drvdata(ci->dev->parent);
	काष्ठा ehci_hcd *ehci;

	चयन (event) अणु
	हाल CI_HDRC_CONTROLLER_RESET_EVENT:
		अगर (ci->hcd) अणु
			ehci = hcd_to_ehci(ci->hcd);
			ehci->has_tdi_phy_lpm = false;
			ehci_ग_लिखोl(ehci, usb->soc->txfअगरothresh << 16,
				    &ehci->regs->txfill_tuning);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_usb_पूर्णांकernal_port_reset(काष्ठा ehci_hcd *ehci,
					 u32 __iomem *portsc_reg,
					 अचिन्हित दीर्घ *flags)
अणु
	u32 saved_usbपूर्णांकr, temp;
	अचिन्हित पूर्णांक i, tries;
	पूर्णांक retval = 0;

	saved_usbपूर्णांकr = ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);
	/* disable USB पूर्णांकerrupt */
	ehci_ग_लिखोl(ehci, 0, &ehci->regs->पूर्णांकr_enable);
	spin_unlock_irqrestore(&ehci->lock, *flags);

	/*
	 * Here we have to करो Port Reset at most twice क्रम
	 * Port Enable bit to be set.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		temp = ehci_पढ़ोl(ehci, portsc_reg);
		temp |= PORT_RESET;
		ehci_ग_लिखोl(ehci, temp, portsc_reg);
		fsleep(10000);
		temp &= ~PORT_RESET;
		ehci_ग_लिखोl(ehci, temp, portsc_reg);
		fsleep(1000);
		tries = 100;
		करो अणु
			fsleep(1000);
			/*
			 * Up to this poपूर्णांक, Port Enable bit is
			 * expected to be set after 2 ms रुकोing.
			 * USB1 usually takes extra 45 ms, क्रम safety,
			 * we take 100 ms as समयout.
			 */
			temp = ehci_पढ़ोl(ehci, portsc_reg);
		पूर्ण जबतक (!(temp & PORT_PE) && tries--);
		अगर (temp & PORT_PE)
			अवरोध;
	पूर्ण
	अगर (i == 2)
		retval = -ETIMEDOUT;

	/*
	 * Clear Connect Status Change bit अगर it's set.
	 * We can't clear PORT_PEC. It will also cause PORT_PE to be cleared.
	 */
	अगर (temp & PORT_CSC)
		ehci_ग_लिखोl(ehci, PORT_CSC, portsc_reg);

	/*
	 * Write to clear any पूर्णांकerrupt status bits that might be set
	 * during port reset.
	 */
	temp = ehci_पढ़ोl(ehci, &ehci->regs->status);
	ehci_ग_लिखोl(ehci, temp, &ehci->regs->status);

	/* restore original पूर्णांकerrupt-enable bits */
	spin_lock_irqsave(&ehci->lock, *flags);
	ehci_ग_लिखोl(ehci, saved_usbपूर्णांकr, &ehci->regs->पूर्णांकr_enable);

	वापस retval;
पूर्ण

अटल पूर्णांक tegra_ehci_hub_control(काष्ठा ci_hdrc *ci, u16 typeReq, u16 wValue,
				  u16 wIndex, अक्षर *buf, u16 wLength,
				  bool *करोne, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा tegra_usb *usb = dev_get_drvdata(ci->dev->parent);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(ci->hcd);
	u32 __iomem *status_reg;
	पूर्णांक retval = 0;

	status_reg = &ehci->regs->port_status[(wIndex & 0xff) - 1];

	चयन (typeReq) अणु
	हाल SetPortFeature:
		अगर (wValue != USB_PORT_FEAT_RESET || !usb->needs_द्विगुन_reset)
			अवरोध;

		/* क्रम USB1 port we need to issue Port Reset twice पूर्णांकernally */
		retval = tegra_usb_पूर्णांकernal_port_reset(ehci, status_reg, flags);
		*करोne  = true;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम tegra_usb_enter_lpm(काष्ठा ci_hdrc *ci, bool enable)
अणु
	/*
	 * Touching any रेजिस्टर which beदीर्घs to AHB घड़ी करोमुख्य will
	 * hang CPU अगर USB controller is put पूर्णांकo low घातer mode because
	 * AHB USB घड़ी is gated on Tegra in the LPM.
	 *
	 * Tegra PHY has a separate रेजिस्टर क्रम checking the घड़ी status
	 * and usb_phy_set_suspend() takes care of gating/ungating the घड़ीs
	 * and restoring the PHY state on Tegra. Hence DEVLC/PORTSC रेजिस्टरs
	 * shouldn't be touched directly by the CI driver.
	 */
	usb_phy_set_suspend(ci->usb_phy, enable);
पूर्ण

अटल पूर्णांक tegra_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा tegra_usb_soc_info *soc;
	काष्ठा tegra_usb *usb;
	पूर्णांक err;

	usb = devm_kzalloc(&pdev->dev, माप(*usb), GFP_KERNEL);
	अगर (!usb)
		वापस -ENOMEM;

	soc = of_device_get_match_data(&pdev->dev);
	अगर (!soc) अणु
		dev_err(&pdev->dev, "failed to match OF data\n");
		वापस -EINVAL;
	पूर्ण

	usb->phy = devm_usb_get_phy_by_phandle(&pdev->dev, "nvidia,phy", 0);
	अगर (IS_ERR(usb->phy))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(usb->phy),
				     "failed to get PHY\n");

	usb->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(usb->clk)) अणु
		err = PTR_ERR(usb->clk);
		dev_err(&pdev->dev, "failed to get clock: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(usb->clk);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to enable clock: %d\n", err);
		वापस err;
	पूर्ण

	अगर (device_property_present(&pdev->dev, "nvidia,needs-double-reset"))
		usb->needs_द्विगुन_reset = true;

	err = tegra_usb_reset_controller(&pdev->dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to reset controller: %d\n", err);
		जाओ fail_घातer_off;
	पूर्ण

	/*
	 * USB controller रेजिस्टरs shouldn't be touched beक्रमe PHY is
	 * initialized, otherwise CPU will hang because घड़ीs are gated.
	 * PHY driver controls gating of पूर्णांकernal USB घड़ीs on Tegra.
	 */
	err = usb_phy_init(usb->phy);
	अगर (err)
		जाओ fail_घातer_off;

	platक्रमm_set_drvdata(pdev, usb);

	/* setup and रेजिस्टर ChipIdea HDRC device */
	usb->soc = soc;
	usb->data.name = "tegra-usb";
	usb->data.flags = soc->flags;
	usb->data.usb_phy = usb->phy;
	usb->data.dr_mode = soc->dr_mode;
	usb->data.capoffset = DEF_CAPOFFSET;
	usb->data.enter_lpm = tegra_usb_enter_lpm;
	usb->data.hub_control = tegra_ehci_hub_control;
	usb->data.notअगरy_event = tegra_usb_notअगरy_event;

	/* Tegra PHY driver currently करोesn't support LPM क्रम ULPI */
	अगर (of_usb_get_phy_mode(pdev->dev.of_node) == USBPHY_INTERFACE_MODE_ULPI)
		usb->data.flags &= ~CI_HDRC_SUPPORTS_RUNTIME_PM;

	usb->dev = ci_hdrc_add_device(&pdev->dev, pdev->resource,
				      pdev->num_resources, &usb->data);
	अगर (IS_ERR(usb->dev)) अणु
		err = PTR_ERR(usb->dev);
		dev_err(&pdev->dev, "failed to add HDRC device: %d\n", err);
		जाओ phy_shutकरोwn;
	पूर्ण

	वापस 0;

phy_shutकरोwn:
	usb_phy_shutकरोwn(usb->phy);
fail_घातer_off:
	clk_disable_unprepare(usb->clk);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_usb *usb = platक्रमm_get_drvdata(pdev);

	ci_hdrc_हटाओ_device(usb->dev);
	usb_phy_shutकरोwn(usb->phy);
	clk_disable_unprepare(usb->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_usb_driver = अणु
	.driver = अणु
		.name = "tegra-usb",
		.of_match_table = tegra_usb_of_match,
	पूर्ण,
	.probe = tegra_usb_probe,
	.हटाओ = tegra_usb_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_usb_driver);

MODULE_DESCRIPTION("NVIDIA Tegra USB driver");
MODULE_AUTHOR("Thierry Reding <treding@nvidia.com>");
MODULE_LICENSE("GPL v2");
