<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2005-2009 MontaVista Software, Inc.
 * Copyright 2008,2012,2015      Freescale Semiconductor, Inc.
 *
 * Ported to 834x by Randy Vinson <rvinson@mvista.com> using code provided
 * by Hunter Wu.
 * Power Management support by Dave Liu <daveliu@मुक्तscale.com>,
 * Jerry Huang <Chang-Ming.Huang@मुक्तscale.com> and
 * Anton Vorontsov <avorontsov@ru.mvista.com>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/err.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ehci_def.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#समावेश "ehci.h"
#समावेश "ehci-fsl.h"

#घोषणा DRIVER_DESC "Freescale EHCI Host controller driver"
#घोषणा DRV_NAME "ehci-fsl"

अटल काष्ठा hc_driver __पढ़ो_mostly fsl_ehci_hc_driver;

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */

/*
 * fsl_ehci_drv_probe - initialize FSL-based HCDs
 * @pdev: USB Host Controller being probed
 *
 * Context: task context, might sleep
 *
 * Allocates basic resources क्रम this USB host controller.
 */
अटल पूर्णांक fsl_ehci_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata;
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक retval;
	u32 पंचांगp;

	pr_debug("initializing FSL-SOC USB Controller\n");

	/* Need platक्रमm data क्रम setup */
	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev,
			"No platform data for %s.\n", dev_name(&pdev->dev));
		वापस -ENODEV;
	पूर्ण

	/*
	 * This is a host mode driver, verअगरy that we're supposed to be
	 * in host mode.
	 */
	अगर (!((pdata->operating_mode == FSL_USB2_DR_HOST) ||
	      (pdata->operating_mode == FSL_USB2_MPH_HOST) ||
	      (pdata->operating_mode == FSL_USB2_DR_OTG))) अणु
		dev_err(&pdev->dev,
			"Non Host Mode configured for %s. Wrong driver linked.\n",
			dev_name(&pdev->dev));
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev,
			"Found HC with no IRQ. Check %s setup!\n",
			dev_name(&pdev->dev));
		वापस -ENODEV;
	पूर्ण
	irq = res->start;

	hcd = __usb_create_hcd(&fsl_ehci_hc_driver, pdev->dev.parent,
			       &pdev->dev, dev_name(&pdev->dev), शून्य);
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ err1;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ err2;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	pdata->regs = hcd->regs;

	अगर (pdata->घातer_budget)
		hcd->घातer_budget = pdata->घातer_budget;

	/*
	 * करो platक्रमm specअगरic init: check the घड़ी, grab/config pins, etc.
	 */
	अगर (pdata->init && pdata->init(pdev)) अणु
		retval = -ENODEV;
		जाओ err2;
	पूर्ण

	/* Enable USB controller, 83xx or 8536 */
	अगर (pdata->have_sysअगर_regs && pdata->controller_ver < FSL_USB_VER_1_6) अणु
		पंचांगp = ioपढ़ो32be(hcd->regs + FSL_SOC_USB_CTRL);
		पंचांगp &= ~CONTROL_REGISTER_W1C_MASK;
		पंचांगp |= 0x4;
		ioग_लिखो32be(पंचांगp, hcd->regs + FSL_SOC_USB_CTRL);
	पूर्ण

	/* Set USB_EN bit to select ULPI phy क्रम USB controller version 2.5 */
	अगर (pdata->controller_ver == FSL_USB_VER_2_5 &&
	    pdata->phy_mode == FSL_USB2_PHY_ULPI)
		ioग_लिखो32be(USB_CTRL_USB_EN, hcd->regs + FSL_SOC_USB_CTRL);

	/*
	 * Enable UTMI phy and program PTS field in UTMI mode beक्रमe निश्चितing
	 * controller reset क्रम USB Controller version 2.5
	 */
	अगर (pdata->has_fsl_erratum_a007792) अणु
		पंचांगp = ioपढ़ो32be(hcd->regs + FSL_SOC_USB_CTRL);
		पंचांगp &= ~CONTROL_REGISTER_W1C_MASK;
		पंचांगp |= CTRL_UTMI_PHY_EN;
		ioग_लिखो32be(पंचांगp, hcd->regs + FSL_SOC_USB_CTRL);

		ग_लिखोl(PORT_PTS_UTMI, hcd->regs + FSL_SOC_USB_PORTSC1);
	पूर्ण

	/* Don't need to set host mode here. It will be करोne by tdi_reset() */

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval != 0)
		जाओ err2;
	device_wakeup_enable(hcd->self.controller);

#अगर_घोषित CONFIG_USB_OTG
	अगर (pdata->operating_mode == FSL_USB2_DR_OTG) अणु
		काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);

		hcd->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
		dev_dbg(&pdev->dev, "hcd=0x%p  ehci=0x%p, phy=0x%p\n",
			hcd, ehci, hcd->usb_phy);

		अगर (!IS_ERR_OR_शून्य(hcd->usb_phy)) अणु
			retval = otg_set_host(hcd->usb_phy->otg,
					      &ehci_to_hcd(ehci)->self);
			अगर (retval) अणु
				usb_put_phy(hcd->usb_phy);
				जाओ err2;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "can't find phy\n");
			retval = -ENODEV;
			जाओ err2;
		पूर्ण

		hcd->skip_phy_initialization = 1;
	पूर्ण
#पूर्ण_अगर
	वापस retval;

      err2:
	usb_put_hcd(hcd);
      err1:
	dev_err(&pdev->dev, "init %s fail, %d\n", dev_name(&pdev->dev), retval);
	अगर (pdata->निकास)
		pdata->निकास(pdev);
	वापस retval;
पूर्ण

अटल bool usb_phy_clk_valid(काष्ठा usb_hcd *hcd)
अणु
	व्योम __iomem *non_ehci = hcd->regs;
	bool ret = true;

	अगर (!(ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL) & PHY_CLK_VALID))
		ret = false;

	वापस ret;
पूर्ण

अटल पूर्णांक ehci_fsl_setup_phy(काष्ठा usb_hcd *hcd,
			       क्रमागत fsl_usb2_phy_modes phy_mode,
			       अचिन्हित पूर्णांक port_offset)
अणु
	u32 portsc, पंचांगp;
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	व्योम __iomem *non_ehci = hcd->regs;
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(dev);

	अगर (pdata->controller_ver < 0) अणु
		dev_warn(hcd->self.controller, "Could not get controller version\n");
		वापस -ENODEV;
	पूर्ण

	portsc = ehci_पढ़ोl(ehci, &ehci->regs->port_status[port_offset]);
	portsc &= ~(PORT_PTS_MSK | PORT_PTS_PTW);

	चयन (phy_mode) अणु
	हाल FSL_USB2_PHY_ULPI:
		अगर (pdata->have_sysअगर_regs && pdata->controller_ver) अणु
			/* controller version 1.6 or above */
			/* turn off UTMI PHY first */
			पंचांगp = ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL);
			पंचांगp &= ~(CONTROL_REGISTER_W1C_MASK | UTMI_PHY_EN);
			ioग_लिखो32be(पंचांगp, non_ehci + FSL_SOC_USB_CTRL);

			/* then turn on ULPI and enable USB controller */
			पंचांगp = ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL);
			पंचांगp &= ~CONTROL_REGISTER_W1C_MASK;
			पंचांगp |= ULPI_PHY_CLK_SEL | USB_CTRL_USB_EN;
			ioग_लिखो32be(पंचांगp, non_ehci + FSL_SOC_USB_CTRL);
		पूर्ण
		portsc |= PORT_PTS_ULPI;
		अवरोध;
	हाल FSL_USB2_PHY_SERIAL:
		portsc |= PORT_PTS_SERIAL;
		अवरोध;
	हाल FSL_USB2_PHY_UTMI_WIDE:
		portsc |= PORT_PTS_PTW;
		fallthrough;
	हाल FSL_USB2_PHY_UTMI:
		/* Presence of this node "has_fsl_erratum_a006918"
		 * in device-tree is used to stop USB controller
		 * initialization in Linux
		 */
		अगर (pdata->has_fsl_erratum_a006918) अणु
			dev_warn(dev, "USB PHY clock invalid\n");
			वापस -EINVAL;
		पूर्ण
		fallthrough;
	हाल FSL_USB2_PHY_UTMI_DUAL:
		/* PHY_CLK_VALID bit is de-featured from all controller
		 * versions below 2.4 and is to be checked only क्रम
		 * पूर्णांकernal UTMI phy
		 */
		अगर (pdata->controller_ver > FSL_USB_VER_2_4 &&
		    pdata->have_sysअगर_regs && !usb_phy_clk_valid(hcd)) अणु
			dev_err(dev, "USB PHY clock invalid\n");
			वापस -EINVAL;
		पूर्ण

		अगर (pdata->have_sysअगर_regs && pdata->controller_ver) अणु
			/* controller version 1.6 or above */
			पंचांगp = ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL);
			पंचांगp &= ~CONTROL_REGISTER_W1C_MASK;
			पंचांगp |= UTMI_PHY_EN;
			ioग_लिखो32be(पंचांगp, non_ehci + FSL_SOC_USB_CTRL);

			mdelay(FSL_UTMI_PHY_DLY);  /* Delay क्रम UTMI PHY CLK to
						become stable - 10ms*/
		पूर्ण
		/* enable UTMI PHY */
		अगर (pdata->have_sysअगर_regs) अणु
			पंचांगp = ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL);
			पंचांगp &= ~CONTROL_REGISTER_W1C_MASK;
			पंचांगp |= CTRL_UTMI_PHY_EN;
			ioग_लिखो32be(पंचांगp, non_ehci + FSL_SOC_USB_CTRL);
		पूर्ण
		portsc |= PORT_PTS_UTMI;
		अवरोध;
	हाल FSL_USB2_PHY_NONE:
		अवरोध;
	पूर्ण

	अगर (pdata->have_sysअगर_regs &&
	    pdata->controller_ver > FSL_USB_VER_1_6 &&
	    !usb_phy_clk_valid(hcd)) अणु
		dev_warn(hcd->self.controller, "USB PHY clock invalid\n");
		वापस -EINVAL;
	पूर्ण

	ehci_ग_लिखोl(ehci, portsc, &ehci->regs->port_status[port_offset]);

	अगर (phy_mode != FSL_USB2_PHY_ULPI && pdata->have_sysअगर_regs) अणु
		पंचांगp = ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL);
		पंचांगp &= ~CONTROL_REGISTER_W1C_MASK;
		पंचांगp |= USB_CTRL_USB_EN;
		ioग_लिखो32be(पंचांगp, non_ehci + FSL_SOC_USB_CTRL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ehci_fsl_usb_setup(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा usb_hcd *hcd = ehci_to_hcd(ehci);
	काष्ठा fsl_usb2_platक्रमm_data *pdata;
	व्योम __iomem *non_ehci = hcd->regs;

	pdata = dev_get_platdata(hcd->self.controller);

	अगर (pdata->have_sysअगर_regs) अणु
		/*
		* Turn on cache snooping hardware, since some PowerPC platक्रमms
		* wholly rely on hardware to deal with cache coherent
		*/

		/* Setup Snooping क्रम all the 4GB space */
		/* SNOOP1 starts from 0x0, size 2G */
		ioग_लिखो32be(0x0 | SNOOP_SIZE_2GB,
			    non_ehci + FSL_SOC_USB_SNOOP1);
		/* SNOOP2 starts from 0x80000000, size 2G */
		ioग_लिखो32be(0x80000000 | SNOOP_SIZE_2GB,
			    non_ehci + FSL_SOC_USB_SNOOP2);
	पूर्ण

	/* Deal with USB erratum A-005275 */
	अगर (pdata->has_fsl_erratum_a005275 == 1)
		ehci->has_fsl_hs_errata = 1;

	अगर (pdata->has_fsl_erratum_a005697 == 1)
		ehci->has_fsl_susp_errata = 1;

	अगर ((pdata->operating_mode == FSL_USB2_DR_HOST) ||
			(pdata->operating_mode == FSL_USB2_DR_OTG))
		अगर (ehci_fsl_setup_phy(hcd, pdata->phy_mode, 0))
			वापस -EINVAL;

	अगर (pdata->operating_mode == FSL_USB2_MPH_HOST) अणु

		/* Deal with USB Erratum #14 on MPC834x Rev 1.0 & 1.1 chips */
		अगर (pdata->has_fsl_erratum_14 == 1)
			ehci->has_fsl_port_bug = 1;

		अगर (pdata->port_enables & FSL_USB2_PORT0_ENABLED)
			अगर (ehci_fsl_setup_phy(hcd, pdata->phy_mode, 0))
				वापस -EINVAL;

		अगर (pdata->port_enables & FSL_USB2_PORT1_ENABLED)
			अगर (ehci_fsl_setup_phy(hcd, pdata->phy_mode, 1))
				वापस -EINVAL;
	पूर्ण

	अगर (pdata->have_sysअगर_regs) अणु
#अगर_घोषित CONFIG_FSL_SOC_BOOKE
		ioग_लिखो32be(0x00000008, non_ehci + FSL_SOC_USB_PRICTRL);
		ioग_लिखो32be(0x00000080, non_ehci + FSL_SOC_USB_AGECNTTHRSH);
#अन्यथा
		ioग_लिखो32be(0x0000000c, non_ehci + FSL_SOC_USB_PRICTRL);
		ioग_लिखो32be(0x00000040, non_ehci + FSL_SOC_USB_AGECNTTHRSH);
#पूर्ण_अगर
		ioग_लिखो32be(0x00000001, non_ehci + FSL_SOC_USB_SICTRL);
	पूर्ण

	वापस 0;
पूर्ण

/* called after घातerup, by probe or प्रणाली-pm "wakeup" */
अटल पूर्णांक ehci_fsl_reinit(काष्ठा ehci_hcd *ehci)
अणु
	अगर (ehci_fsl_usb_setup(ehci))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* called during probe() after chip reset completes */
अटल पूर्णांक ehci_fsl_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	पूर्णांक retval;
	काष्ठा fsl_usb2_platक्रमm_data *pdata;
	काष्ठा device *dev;

	dev = hcd->self.controller;
	pdata = dev_get_platdata(hcd->self.controller);
	ehci->big_endian_desc = pdata->big_endian_desc;
	ehci->big_endian_mmio = pdata->big_endian_mmio;

	/* EHCI रेजिस्टरs start at offset 0x100 */
	ehci->caps = hcd->regs + 0x100;

#अगर_घोषित CONFIG_PPC_83xx
	/*
	 * Deal with MPC834X that need port घातer to be cycled after the घातer
	 * fault condition is हटाओd. Otherwise the state machine करोes not
	 * reflect PORTSC[CSC] correctly.
	 */
	ehci->need_oc_pp_cycle = 1;
#पूर्ण_अगर

	hcd->has_tt = 1;

	retval = ehci_setup(hcd);
	अगर (retval)
		वापस retval;

	अगर (of_device_is_compatible(dev->parent->of_node,
				    "fsl,mpc5121-usb2-dr")) अणु
		/*
		 * set SBUSCFG:AHBBRST so that control msgs करोn't
		 * fail when करोing heavy PATA ग_लिखोs.
		 */
		ehci_ग_लिखोl(ehci, SBUSCFG_INCR8,
			    hcd->regs + FSL_SOC_USB_SBUSCFG);
	पूर्ण

	retval = ehci_fsl_reinit(ehci);
	वापस retval;
पूर्ण

काष्ठा ehci_fsl अणु
	काष्ठा ehci_hcd	ehci;

#अगर_घोषित CONFIG_PM
	/* Saved USB PHY settings, need to restore after deep sleep. */
	u32 usb_ctrl;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PM

#अगर_घोषित CONFIG_PPC_MPC512x
अटल पूर्णांक ehci_fsl_mpc512x_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(dev);
	u32 पंचांगp;

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
	u32 mode = ehci_पढ़ोl(ehci, hcd->regs + FSL_SOC_USB_USBMODE);
	mode &= USBMODE_CM_MASK;
	पंचांगp = ehci_पढ़ोl(ehci, hcd->regs + 0x140);	/* usbcmd */

	dev_dbg(dev, "suspend=%d already_suspended=%d "
		"mode=%d  usbcmd %08x\n", pdata->suspended,
		pdata->alपढ़ोy_suspended, mode, पंचांगp);
#पूर्ण_अगर

	/*
	 * If the controller is alपढ़ोy suspended, then this must be a
	 * PM suspend.  Remember this fact, so that we will leave the
	 * controller suspended at PM resume समय.
	 */
	अगर (pdata->suspended) अणु
		dev_dbg(dev, "already suspended, leaving early\n");
		pdata->alपढ़ोy_suspended = 1;
		वापस 0;
	पूर्ण

	dev_dbg(dev, "suspending...\n");

	ehci->rh_state = EHCI_RH_SUSPENDED;
	dev->घातer.घातer_state = PMSG_SUSPEND;

	/* ignore non-host पूर्णांकerrupts */
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	/* stop the controller */
	पंचांगp = ehci_पढ़ोl(ehci, &ehci->regs->command);
	पंचांगp &= ~CMD_RUN;
	ehci_ग_लिखोl(ehci, पंचांगp, &ehci->regs->command);

	/* save EHCI रेजिस्टरs */
	pdata->pm_command = ehci_पढ़ोl(ehci, &ehci->regs->command);
	pdata->pm_command &= ~CMD_RUN;
	pdata->pm_status  = ehci_पढ़ोl(ehci, &ehci->regs->status);
	pdata->pm_पूर्णांकr_enable  = ehci_पढ़ोl(ehci, &ehci->regs->पूर्णांकr_enable);
	pdata->pm_frame_index  = ehci_पढ़ोl(ehci, &ehci->regs->frame_index);
	pdata->pm_segment  = ehci_पढ़ोl(ehci, &ehci->regs->segment);
	pdata->pm_frame_list  = ehci_पढ़ोl(ehci, &ehci->regs->frame_list);
	pdata->pm_async_next  = ehci_पढ़ोl(ehci, &ehci->regs->async_next);
	pdata->pm_configured_flag  =
		ehci_पढ़ोl(ehci, &ehci->regs->configured_flag);
	pdata->pm_portsc = ehci_पढ़ोl(ehci, &ehci->regs->port_status[0]);
	pdata->pm_usbgenctrl = ehci_पढ़ोl(ehci,
					  hcd->regs + FSL_SOC_USB_USBGENCTRL);

	/* clear the W1C bits */
	pdata->pm_portsc &= cpu_to_hc32(ehci, ~PORT_RWC_BITS);

	pdata->suspended = 1;

	/* clear PP to cut घातer to the port */
	पंचांगp = ehci_पढ़ोl(ehci, &ehci->regs->port_status[0]);
	पंचांगp &= ~PORT_POWER;
	ehci_ग_लिखोl(ehci, पंचांगp, &ehci->regs->port_status[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ehci_fsl_mpc512x_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(dev);
	u32 पंचांगp;

	dev_dbg(dev, "suspend=%d already_suspended=%d\n",
		pdata->suspended, pdata->alपढ़ोy_suspended);

	/*
	 * If the controller was alपढ़ोy suspended at suspend समय,
	 * then करोn't resume it now.
	 */
	अगर (pdata->alपढ़ोy_suspended) अणु
		dev_dbg(dev, "already suspended, leaving early\n");
		pdata->alपढ़ोy_suspended = 0;
		वापस 0;
	पूर्ण

	अगर (!pdata->suspended) अणु
		dev_dbg(dev, "not suspended, leaving early\n");
		वापस 0;
	पूर्ण

	pdata->suspended = 0;

	dev_dbg(dev, "resuming...\n");

	/* set host mode */
	पंचांगp = USBMODE_CM_HOST | (pdata->es ? USBMODE_ES : 0);
	ehci_ग_लिखोl(ehci, पंचांगp, hcd->regs + FSL_SOC_USB_USBMODE);

	ehci_ग_लिखोl(ehci, pdata->pm_usbgenctrl,
		    hcd->regs + FSL_SOC_USB_USBGENCTRL);
	ehci_ग_लिखोl(ehci, ISIPHYCTRL_PXE | ISIPHYCTRL_PHYE,
		    hcd->regs + FSL_SOC_USB_ISIPHYCTRL);

	ehci_ग_लिखोl(ehci, SBUSCFG_INCR8, hcd->regs + FSL_SOC_USB_SBUSCFG);

	/* restore EHCI रेजिस्टरs */
	ehci_ग_लिखोl(ehci, pdata->pm_command, &ehci->regs->command);
	ehci_ग_लिखोl(ehci, pdata->pm_पूर्णांकr_enable, &ehci->regs->पूर्णांकr_enable);
	ehci_ग_लिखोl(ehci, pdata->pm_frame_index, &ehci->regs->frame_index);
	ehci_ग_लिखोl(ehci, pdata->pm_segment, &ehci->regs->segment);
	ehci_ग_लिखोl(ehci, pdata->pm_frame_list, &ehci->regs->frame_list);
	ehci_ग_लिखोl(ehci, pdata->pm_async_next, &ehci->regs->async_next);
	ehci_ग_लिखोl(ehci, pdata->pm_configured_flag,
		    &ehci->regs->configured_flag);
	ehci_ग_लिखोl(ehci, pdata->pm_portsc, &ehci->regs->port_status[0]);

	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	ehci->rh_state = EHCI_RH_RUNNING;
	dev->घातer.घातer_state = PMSG_ON;

	पंचांगp = ehci_पढ़ोl(ehci, &ehci->regs->command);
	पंचांगp |= CMD_RUN;
	ehci_ग_लिखोl(ehci, पंचांगp, &ehci->regs->command);

	usb_hcd_resume_root_hub(hcd);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ehci_fsl_mpc512x_drv_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ehci_fsl_mpc512x_drv_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC512x */

अटल काष्ठा ehci_fsl *hcd_to_ehci_fsl(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);

	वापस container_of(ehci, काष्ठा ehci_fsl, ehci);
पूर्ण

अटल पूर्णांक ehci_fsl_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा ehci_fsl *ehci_fsl = hcd_to_ehci_fsl(hcd);
	व्योम __iomem *non_ehci = hcd->regs;

	अगर (of_device_is_compatible(dev->parent->of_node,
				    "fsl,mpc5121-usb2-dr")) अणु
		वापस ehci_fsl_mpc512x_drv_suspend(dev);
	पूर्ण

	ehci_prepare_ports_क्रम_controller_suspend(hcd_to_ehci(hcd),
			device_may_wakeup(dev));
	अगर (!fsl_deep_sleep())
		वापस 0;

	ehci_fsl->usb_ctrl = ioपढ़ो32be(non_ehci + FSL_SOC_USB_CTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक ehci_fsl_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा ehci_fsl *ehci_fsl = hcd_to_ehci_fsl(hcd);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	व्योम __iomem *non_ehci = hcd->regs;

	अगर (of_device_is_compatible(dev->parent->of_node,
				    "fsl,mpc5121-usb2-dr")) अणु
		वापस ehci_fsl_mpc512x_drv_resume(dev);
	पूर्ण

	ehci_prepare_ports_क्रम_controller_resume(ehci);
	अगर (!fsl_deep_sleep())
		वापस 0;

	usb_root_hub_lost_घातer(hcd->self.root_hub);

	/* Restore USB PHY settings and enable the controller. */
	ioग_लिखो32be(ehci_fsl->usb_ctrl, non_ehci + FSL_SOC_USB_CTRL);

	ehci_reset(ehci);
	ehci_fsl_reinit(ehci);

	वापस 0;
पूर्ण

अटल पूर्णांक ehci_fsl_drv_restore(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	usb_root_hub_lost_घातer(hcd->self.root_hub);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ehci_fsl_pm_ops = अणु
	.suspend = ehci_fsl_drv_suspend,
	.resume = ehci_fsl_drv_resume,
	.restore = ehci_fsl_drv_restore,
पूर्ण;

#घोषणा EHCI_FSL_PM_OPS		(&ehci_fsl_pm_ops)
#अन्यथा
#घोषणा EHCI_FSL_PM_OPS		शून्य
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_USB_OTG
अटल पूर्णांक ehci_start_port_reset(काष्ठा usb_hcd *hcd, अचिन्हित port)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	u32 status;

	अगर (!port)
		वापस -EINVAL;

	port--;

	/* start port reset beक्रमe HNP protocol समय out */
	status = पढ़ोl(&ehci->regs->port_status[port]);
	अगर (!(status & PORT_CONNECT))
		वापस -ENODEV;

	/* hub_wq will finish the reset later */
	अगर (ehci_is_TDI(ehci)) अणु
		ग_लिखोl(PORT_RESET |
		       (status & ~(PORT_CSC | PORT_PEC | PORT_OCC)),
		       &ehci->regs->port_status[port]);
	पूर्ण अन्यथा अणु
		ग_लिखोl(PORT_RESET, &ehci->regs->port_status[port]);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ehci_start_port_reset	शून्य
#पूर्ण_अगर /* CONFIG_USB_OTG */

अटल स्थिर काष्ठा ehci_driver_overrides ehci_fsl_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा ehci_fsl),
	.reset = ehci_fsl_setup,
पूर्ण;

/**
 * fsl_ehci_drv_हटाओ - shutकरोwn processing क्रम FSL-based HCDs
 * @pdev: USB Host Controller being हटाओd
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of usb_hcd_fsl_probe().
 */
अटल पूर्णांक fsl_ehci_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_usb2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	अगर (!IS_ERR_OR_शून्य(hcd->usb_phy)) अणु
		otg_set_host(hcd->usb_phy->otg, शून्य);
		usb_put_phy(hcd->usb_phy);
	पूर्ण

	usb_हटाओ_hcd(hcd);

	/*
	 * करो platक्रमm specअगरic un-initialization:
	 * release iomux pins, disable घड़ी, etc.
	 */
	अगर (pdata->निकास)
		pdata->निकास(pdev);
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ehci_fsl_driver = अणु
	.probe = fsl_ehci_drv_probe,
	.हटाओ = fsl_ehci_drv_हटाओ,
	.shutकरोwn = usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "fsl-ehci",
		.pm = EHCI_FSL_PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ehci_fsl_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info(DRV_NAME ": " DRIVER_DESC "\n");

	ehci_init_driver(&fsl_ehci_hc_driver, &ehci_fsl_overrides);

	fsl_ehci_hc_driver.product_desc =
			"Freescale On-Chip EHCI Host Controller";
	fsl_ehci_hc_driver.start_port_reset = ehci_start_port_reset;


	वापस platक्रमm_driver_रेजिस्टर(&ehci_fsl_driver);
पूर्ण
module_init(ehci_fsl_init);

अटल व्योम __निकास ehci_fsl_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_fsl_driver);
पूर्ण
module_निकास(ehci_fsl_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
