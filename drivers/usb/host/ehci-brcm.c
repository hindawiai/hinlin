<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020, Broadcom */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/iopoll.h>

#समावेश "ehci.h"

#घोषणा hcd_to_ehci_priv(h) ((काष्ठा brcm_priv *)hcd_to_ehci(h)->priv)

काष्ठा brcm_priv अणु
	काष्ठा clk *clk;
पूर्ण;

/*
 * ehci_brcm_रुको_क्रम_sof
 * Wait क्रम start of next microframe, then रुको extra delay microseconds
 */
अटल अंतरभूत व्योम ehci_brcm_रुको_क्रम_sof(काष्ठा ehci_hcd *ehci, u32 delay)
अणु
	u32 frame_idx = ehci_पढ़ोl(ehci, &ehci->regs->frame_index);
	u32 val;
	पूर्णांक res;

	/* Wait क्रम next microframe (every 125 usecs) */
	res = पढ़ोl_relaxed_poll_समयout(&ehci->regs->frame_index, val,
					 val != frame_idx, 1, 130);
	अगर (res)
		ehci_err(ehci, "Error waiting for SOF\n");
	udelay(delay);
पूर्ण

/*
 * ehci_brcm_hub_control
 * The EHCI controller has a bug where it can violate the SOF
 * पूर्णांकerval between the first two SOF's transmitted after resume
 * अगर the resume occurs near the end of the microframe. This causees
 * the controller to detect babble on the suspended port and
 * will eventually cause the controller to reset the port.
 * The fix is to Intercept the echi-hcd request to complete RESUME and
 * align it to the start of the next microframe.
 * See SWLINUX-1909 क्रम more details
 */
अटल पूर्णांक ehci_brcm_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength)
अणु
	काष्ठा ehci_hcd	*ehci = hcd_to_ehci(hcd);
	पूर्णांक		ports = HCS_N_PORTS(ehci->hcs_params);
	u32 __iomem	*status_reg;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval, irq_disabled = 0;

	status_reg = &ehci->regs->port_status[(wIndex & 0xff) - 1];

	/*
	 * RESUME is cleared when GetPortStatus() is called 20ms after start
	 * of RESUME
	 */
	अगर ((typeReq == GetPortStatus) &&
	    (wIndex && wIndex <= ports) &&
	    ehci->reset_करोne[wIndex-1] &&
	    समय_after_eq(jअगरfies, ehci->reset_करोne[wIndex-1]) &&
	    (ehci_पढ़ोl(ehci, status_reg) & PORT_RESUME)) अणु

		/*
		 * to make sure we are not पूर्णांकerrupted until RESUME bit
		 * is cleared, disable पूर्णांकerrupts on current CPU
		 */
		ehci_dbg(ehci, "SOF alignment workaround\n");
		irq_disabled = 1;
		local_irq_save(flags);
		ehci_brcm_रुको_क्रम_sof(ehci, 5);
	पूर्ण
	retval = ehci_hub_control(hcd, typeReq, wValue, wIndex, buf, wLength);
	अगर (irq_disabled)
		local_irq_restore(flags);
	वापस retval;
पूर्ण

अटल पूर्णांक ehci_brcm_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	पूर्णांक len;

	ehci->big_endian_mmio = 1;

	ehci->caps = (व्योम __iomem *)hcd->regs;
	len = HC_LENGTH(ehci, ehci_पढ़ोl(ehci, &ehci->caps->hc_capbase));
	ehci->regs = (व्योम __iomem *)(hcd->regs + len);

	/* This fixes the lockup during reboot due to prior पूर्णांकerrupts */
	ehci_ग_लिखोl(ehci, CMD_RESET, &ehci->regs->command);
	mdelay(10);

	/*
	 * SWLINUX-1705: Aव्योम OUT packet underflows during high memory
	 *   bus usage
	 * port_status[0x0f] = Broadcom-proprietary USB_EHCI_INSNREG00 @ 0x90
	 */
	ehci_ग_लिखोl(ehci, 0x00800040, &ehci->regs->port_status[0x10]);
	ehci_ग_लिखोl(ehci, 0x00000001, &ehci->regs->port_status[0x12]);

	वापस ehci_setup(hcd);
पूर्ण

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_brcm_hc_driver;

अटल स्थिर काष्ठा ehci_driver_overrides brcm_overrides __initस्थिर = अणु
	.reset = ehci_brcm_reset,
	.extra_priv_size = माप(काष्ठा brcm_priv),
पूर्ण;

अटल पूर्णांक ehci_brcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res_mem;
	काष्ठा brcm_priv *priv;
	काष्ठा usb_hcd *hcd;
	पूर्णांक irq;
	पूर्णांक err;

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (err)
		वापस err;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq ? irq : -EINVAL;

	/* Hook the hub control routine to work around a bug */
	ehci_brcm_hc_driver.hub_control = ehci_brcm_hub_control;

	/* initialize hcd */
	hcd = usb_create_hcd(&ehci_brcm_hc_driver, dev, dev_name(dev));
	अगर (!hcd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hcd);
	priv = hcd_to_ehci_priv(hcd);

	priv->clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		err = PTR_ERR(priv->clk);
		जाओ err_hcd;
	पूर्ण

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		जाओ err_hcd;

	hcd->regs = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res_mem);
	अगर (IS_ERR(hcd->regs)) अणु
		err = PTR_ERR(hcd->regs);
		जाओ err_clk;
	पूर्ण
	hcd->rsrc_start = res_mem->start;
	hcd->rsrc_len = resource_size(res_mem);
	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (err)
		जाओ err_clk;

	device_wakeup_enable(hcd->self.controller);
	device_enable_async_suspend(hcd->self.controller);

	वापस 0;

err_clk:
	clk_disable_unprepare(priv->clk);
err_hcd:
	usb_put_hcd(hcd);

	वापस err;
पूर्ण

अटल पूर्णांक ehci_brcm_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा brcm_priv *priv = hcd_to_ehci_priv(hcd);

	usb_हटाओ_hcd(hcd);
	clk_disable_unprepare(priv->clk);
	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_brcm_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा brcm_priv *priv = hcd_to_ehci_priv(hcd);
	bool करो_wakeup = device_may_wakeup(dev);

	ret = ehci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;
	clk_disable_unprepare(priv->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_brcm_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	काष्ठा brcm_priv *priv = hcd_to_ehci_priv(hcd);
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;
	/*
	 * SWLINUX-1705: Aव्योम OUT packet underflows during high memory
	 *   bus usage
	 * port_status[0x0f] = Broadcom-proprietary USB_EHCI_INSNREG00
	 * @ 0x90
	 */
	ehci_ग_लिखोl(ehci, 0x00800040, &ehci->regs->port_status[0x10]);
	ehci_ग_लिखोl(ehci, 0x00000001, &ehci->regs->port_status[0x12]);

	ehci_resume(hcd, false);

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ehci_brcm_pm_ops, ehci_brcm_suspend,
		ehci_brcm_resume);

अटल स्थिर काष्ठा of_device_id brcm_ehci_of_match[] = अणु
	अणु .compatible = "brcm,ehci-brcm-v2", पूर्ण,
	अणु .compatible = "brcm,bcm7445-ehci", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ehci_brcm_driver = अणु
	.probe		= ehci_brcm_probe,
	.हटाओ		= ehci_brcm_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "ehci-brcm",
		.pm	= &ehci_brcm_pm_ops,
		.of_match_table = brcm_ehci_of_match,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ehci_brcm_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	ehci_init_driver(&ehci_brcm_hc_driver, &brcm_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ehci_brcm_driver);
पूर्ण
module_init(ehci_brcm_init);

अटल व्योम __निकास ehci_brcm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_brcm_driver);
पूर्ण
module_निकास(ehci_brcm_निकास);

MODULE_ALIAS("platform:ehci-brcm");
MODULE_DESCRIPTION("EHCI Broadcom STB driver");
MODULE_AUTHOR("Al Cooper");
MODULE_LICENSE("GPL");
