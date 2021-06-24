<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * host.c - ChipIdea USB host controller driver
 *
 * Copyright (c) 2012 Intel Corporation
 *
 * Author: Alexander Shishkin
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pinctrl/consumer.h>

#समावेश "../host/ehci.h"

#समावेश "ci.h"
#समावेश "bits.h"
#समावेश "host.h"

अटल काष्ठा hc_driver __पढ़ो_mostly ci_ehci_hc_driver;
अटल पूर्णांक (*orig_bus_suspend)(काष्ठा usb_hcd *hcd);

काष्ठा ehci_ci_priv अणु
	काष्ठा regulator *reg_vbus;
	bool enabled;
पूर्ण;

काष्ठा ci_hdrc_dma_aligned_buffer अणु
	व्योम *kदो_स्मृति_ptr;
	व्योम *old_xfer_buffer;
	u8 data[];
पूर्ण;

अटल पूर्णांक ehci_ci_portघातer(काष्ठा usb_hcd *hcd, पूर्णांक portnum, bool enable)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	काष्ठा ehci_ci_priv *priv = (काष्ठा ehci_ci_priv *)ehci->priv;
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	पूर्णांक port = HCS_N_PORTS(ehci->hcs_params);

	अगर (priv->reg_vbus && enable != priv->enabled) अणु
		अगर (port > 1) अणु
			dev_warn(dev,
				"Not support multi-port regulator control\n");
			वापस 0;
		पूर्ण
		अगर (enable)
			ret = regulator_enable(priv->reg_vbus);
		अन्यथा
			ret = regulator_disable(priv->reg_vbus);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to %s vbus regulator, ret=%d\n",
				enable ? "enable" : "disable", ret);
			वापस ret;
		पूर्ण
		priv->enabled = enable;
	पूर्ण

	अगर (enable && (ci->platdata->phy_mode == USBPHY_INTERFACE_MODE_HSIC)) अणु
		/*
		 * Marvell 28nm HSIC PHY requires क्रमcing the port to HS mode.
		 * As HSIC is always HS, this should be safe क्रम others.
		 */
		hw_port_test_set(ci, 5);
		hw_port_test_set(ci, 0);
	पूर्ण
	वापस 0;
पूर्ण;

अटल पूर्णांक ehci_ci_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	पूर्णांक ret;

	ret = ehci_setup(hcd);
	अगर (ret)
		वापस ret;

	ehci->need_io_watchकरोg = 0;

	अगर (ci->platdata->notअगरy_event) अणु
		ret = ci->platdata->notअगरy_event(ci,
				CI_HDRC_CONTROLLER_RESET_EVENT);
		अगर (ret)
			वापस ret;
	पूर्ण

	ci_platक्रमm_configure(ci);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ehci_driver_overrides ehci_ci_overrides = अणु
	.extra_priv_size = माप(काष्ठा ehci_ci_priv),
	.port_घातer	 = ehci_ci_portघातer,
	.reset		 = ehci_ci_reset,
पूर्ण;

अटल irqवापस_t host_irq(काष्ठा ci_hdrc *ci)
अणु
	वापस usb_hcd_irq(ci->irq, ci->hcd);
पूर्ण

अटल पूर्णांक host_start(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd *ehci;
	काष्ठा ehci_ci_priv *priv;
	पूर्णांक ret;

	अगर (usb_disabled())
		वापस -ENODEV;

	hcd = __usb_create_hcd(&ci_ehci_hc_driver, ci->dev->parent,
			       ci->dev, dev_name(ci->dev), शून्य);
	अगर (!hcd)
		वापस -ENOMEM;

	dev_set_drvdata(ci->dev, ci);
	hcd->rsrc_start = ci->hw_bank.phys;
	hcd->rsrc_len = ci->hw_bank.size;
	hcd->regs = ci->hw_bank.असल;
	hcd->has_tt = 1;

	hcd->घातer_budget = ci->platdata->घातer_budget;
	hcd->tpl_support = ci->platdata->tpl_support;
	अगर (ci->phy || ci->usb_phy) अणु
		hcd->skip_phy_initialization = 1;
		अगर (ci->usb_phy)
			hcd->usb_phy = ci->usb_phy;
	पूर्ण

	ehci = hcd_to_ehci(hcd);
	ehci->caps = ci->hw_bank.cap;
	ehci->has_hostpc = ci->hw_bank.lpm;
	ehci->has_tdi_phy_lpm = ci->hw_bank.lpm;
	ehci->imx28_ग_लिखो_fix = ci->imx28_ग_लिखो_fix;

	priv = (काष्ठा ehci_ci_priv *)ehci->priv;
	priv->reg_vbus = शून्य;

	अगर (ci->platdata->reg_vbus && !ci_otg_is_fsm_mode(ci)) अणु
		अगर (ci->platdata->flags & CI_HDRC_TURN_VBUS_EARLY_ON) अणु
			ret = regulator_enable(ci->platdata->reg_vbus);
			अगर (ret) अणु
				dev_err(ci->dev,
				"Failed to enable vbus regulator, ret=%d\n",
									ret);
				जाओ put_hcd;
			पूर्ण
		पूर्ण अन्यथा अणु
			priv->reg_vbus = ci->platdata->reg_vbus;
		पूर्ण
	पूर्ण

	अगर (ci->platdata->pins_host)
		pinctrl_select_state(ci->platdata->pctl,
				     ci->platdata->pins_host);

	ci->hcd = hcd;

	ret = usb_add_hcd(hcd, 0, 0);
	अगर (ret) अणु
		ci->hcd = शून्य;
		जाओ disable_reg;
	पूर्ण अन्यथा अणु
		काष्ठा usb_otg *otg = &ci->otg;

		अगर (ci_otg_is_fsm_mode(ci)) अणु
			otg->host = &hcd->self;
			hcd->self.otg_port = 1;
		पूर्ण

		अगर (ci->platdata->notअगरy_event &&
			(ci->platdata->flags & CI_HDRC_IMX_IS_HSIC))
			ci->platdata->notअगरy_event
				(ci, CI_HDRC_IMX_HSIC_ACTIVE_EVENT);
	पूर्ण

	वापस ret;

disable_reg:
	अगर (ci->platdata->reg_vbus && !ci_otg_is_fsm_mode(ci) &&
			(ci->platdata->flags & CI_HDRC_TURN_VBUS_EARLY_ON))
		regulator_disable(ci->platdata->reg_vbus);
put_hcd:
	usb_put_hcd(hcd);

	वापस ret;
पूर्ण

अटल व्योम host_stop(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा usb_hcd *hcd = ci->hcd;

	अगर (hcd) अणु
		अगर (ci->platdata->notअगरy_event)
			ci->platdata->notअगरy_event(ci,
				CI_HDRC_CONTROLLER_STOPPED_EVENT);
		usb_हटाओ_hcd(hcd);
		ci->role = CI_ROLE_END;
		synchronize_irq(ci->irq);
		usb_put_hcd(hcd);
		अगर (ci->platdata->reg_vbus && !ci_otg_is_fsm_mode(ci) &&
			(ci->platdata->flags & CI_HDRC_TURN_VBUS_EARLY_ON))
				regulator_disable(ci->platdata->reg_vbus);
	पूर्ण
	ci->hcd = शून्य;
	ci->otg.host = शून्य;

	अगर (ci->platdata->pins_host && ci->platdata->pins_शेष)
		pinctrl_select_state(ci->platdata->pctl,
				     ci->platdata->pins_शेष);
पूर्ण


व्योम ci_hdrc_host_destroy(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->role == CI_ROLE_HOST && ci->hcd)
		host_stop(ci);
पूर्ण

/* The below code is based on tegra ehci driver */
अटल पूर्णांक ci_ehci_hub_control(
	काष्ठा usb_hcd	*hcd,
	u16		typeReq,
	u16		wValue,
	u16		wIndex,
	अक्षर		*buf,
	u16		wLength
)
अणु
	काष्ठा ehci_hcd	*ehci = hcd_to_ehci(hcd);
	u32 __iomem	*status_reg;
	u32		temp;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		retval = 0;
	bool		करोne = false;
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);

	status_reg = &ehci->regs->port_status[(wIndex & 0xff) - 1];

	spin_lock_irqsave(&ehci->lock, flags);

	अगर (ci->platdata->hub_control) अणु
		retval = ci->platdata->hub_control(ci, typeReq, wValue, wIndex,
						   buf, wLength, &करोne, &flags);
		अगर (करोne)
			जाओ करोne;
	पूर्ण

	अगर (typeReq == SetPortFeature && wValue == USB_PORT_FEAT_SUSPEND) अणु
		temp = ehci_पढ़ोl(ehci, status_reg);
		अगर ((temp & PORT_PE) == 0 || (temp & PORT_RESET) != 0) अणु
			retval = -EPIPE;
			जाओ करोne;
		पूर्ण

		temp &= ~(PORT_RWC_BITS | PORT_WKCONN_E);
		temp |= PORT_WKDISC_E | PORT_WKOC_E;
		ehci_ग_लिखोl(ehci, temp | PORT_SUSPEND, status_reg);

		/*
		 * If a transaction is in progress, there may be a delay in
		 * suspending the port. Poll until the port is suspended.
		 */
		अगर (ehci_handshake(ehci, status_reg, PORT_SUSPEND,
			PORT_SUSPEND, 5000))
			ehci_err(ehci, "timeout waiting for SUSPEND\n");

		अगर (ci->platdata->flags & CI_HDRC_IMX_IS_HSIC) अणु
			अगर (ci->platdata->notअगरy_event)
				ci->platdata->notअगरy_event(ci,
					CI_HDRC_IMX_HSIC_SUSPEND_EVENT);

			temp = ehci_पढ़ोl(ehci, status_reg);
			temp &= ~(PORT_WKDISC_E | PORT_WKCONN_E);
			ehci_ग_लिखोl(ehci, temp, status_reg);
		पूर्ण

		set_bit((wIndex & 0xff) - 1, &ehci->suspended_ports);
		जाओ करोne;
	पूर्ण

	/*
	 * After resume has finished, it needs करो some post resume
	 * operation क्रम some SoCs.
	 */
	अन्यथा अगर (typeReq == ClearPortFeature &&
		wValue == USB_PORT_FEAT_C_SUSPEND) अणु
		/* Make sure the resume has finished, it should be finished */
		अगर (ehci_handshake(ehci, status_reg, PORT_RESUME, 0, 25000))
			ehci_err(ehci, "timeout waiting for resume\n");
	पूर्ण

	spin_unlock_irqrestore(&ehci->lock, flags);

	/* Handle the hub control events here */
	वापस ehci_hub_control(hcd, typeReq, wValue, wIndex, buf, wLength);
करोne:
	spin_unlock_irqrestore(&ehci->lock, flags);
	वापस retval;
पूर्ण
अटल पूर्णांक ci_ehci_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	पूर्णांक port;
	u32 पंचांगp;

	पूर्णांक ret = orig_bus_suspend(hcd);

	अगर (ret)
		वापस ret;

	port = HCS_N_PORTS(ehci->hcs_params);
	जबतक (port--) अणु
		u32 __iomem *reg = &ehci->regs->port_status[port];
		u32 portsc = ehci_पढ़ोl(ehci, reg);

		अगर (portsc & PORT_CONNECT) अणु
			/*
			 * For chipidea, the resume संकेत will be ended
			 * स्वतःmatically, so क्रम remote wakeup हाल, the
			 * usbcmd.rs may not be set beक्रमe the resume has
			 * ended अगर other resume paths consumes too much
			 * समय (~24ms), in that हाल, the SOF will not
			 * send out within 3ms after resume ends, then the
			 * high speed device will enter full speed mode.
			 */

			पंचांगp = ehci_पढ़ोl(ehci, &ehci->regs->command);
			पंचांगp |= CMD_RUN;
			ehci_ग_लिखोl(ehci, पंचांगp, &ehci->regs->command);
			/*
			 * It needs a लघु delay between set RS bit and PHCD.
			 */
			usleep_range(150, 200);
			/*
			 * Need to clear WKCN and WKOC क्रम imx HSIC,
			 * otherwise, there will be wakeup event.
			 */
			अगर (ci->platdata->flags & CI_HDRC_IMX_IS_HSIC) अणु
				पंचांगp = ehci_पढ़ोl(ehci, reg);
				पंचांगp &= ~(PORT_WKDISC_E | PORT_WKCONN_E);
				ehci_ग_लिखोl(ehci, पंचांगp, reg);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ci_hdrc_मुक्त_dma_aligned_buffer(काष्ठा urb *urb)
अणु
	काष्ठा ci_hdrc_dma_aligned_buffer *temp;
	माप_प्रकार length;

	अगर (!(urb->transfer_flags & URB_ALIGNED_TEMP_BUFFER))
		वापस;

	temp = container_of(urb->transfer_buffer,
			    काष्ठा ci_hdrc_dma_aligned_buffer, data);

	अगर (usb_urb_dir_in(urb)) अणु
		अगर (usb_pipeisoc(urb->pipe))
			length = urb->transfer_buffer_length;
		अन्यथा
			length = urb->actual_length;

		स_नकल(temp->old_xfer_buffer, temp->data, length);
	पूर्ण
	urb->transfer_buffer = temp->old_xfer_buffer;
	kमुक्त(temp->kदो_स्मृति_ptr);

	urb->transfer_flags &= ~URB_ALIGNED_TEMP_BUFFER;
पूर्ण

अटल पूर्णांक ci_hdrc_alloc_dma_aligned_buffer(काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा ci_hdrc_dma_aligned_buffer *temp, *kदो_स्मृति_ptr;
	स्थिर अचिन्हित पूर्णांक ci_hdrc_usb_dma_align = 32;
	माप_प्रकार kदो_स्मृति_size;

	अगर (urb->num_sgs || urb->sg || urb->transfer_buffer_length == 0 ||
	    !((uपूर्णांकptr_t)urb->transfer_buffer & (ci_hdrc_usb_dma_align - 1)))
		वापस 0;

	/* Allocate a buffer with enough padding क्रम alignment */
	kदो_स्मृति_size = urb->transfer_buffer_length +
		       माप(काष्ठा ci_hdrc_dma_aligned_buffer) +
		       ci_hdrc_usb_dma_align - 1;

	kदो_स्मृति_ptr = kदो_स्मृति(kदो_स्मृति_size, mem_flags);
	अगर (!kदो_स्मृति_ptr)
		वापस -ENOMEM;

	/* Position our काष्ठा dma_aligned_buffer such that data is aligned */
	temp = PTR_ALIGN(kदो_स्मृति_ptr + 1, ci_hdrc_usb_dma_align) - 1;
	temp->kदो_स्मृति_ptr = kदो_स्मृति_ptr;
	temp->old_xfer_buffer = urb->transfer_buffer;
	अगर (usb_urb_dir_out(urb))
		स_नकल(temp->data, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = temp->data;

	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	वापस 0;
पूर्ण

अटल पूर्णांक ci_hdrc_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				   gfp_t mem_flags)
अणु
	पूर्णांक ret;

	ret = ci_hdrc_alloc_dma_aligned_buffer(urb, mem_flags);
	अगर (ret)
		वापस ret;

	ret = usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);
	अगर (ret)
		ci_hdrc_मुक्त_dma_aligned_buffer(urb);

	वापस ret;
पूर्ण

अटल व्योम ci_hdrc_unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	usb_hcd_unmap_urb_क्रम_dma(hcd, urb);
	ci_hdrc_मुक्त_dma_aligned_buffer(urb);
पूर्ण

पूर्णांक ci_hdrc_host_init(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा ci_role_driver *rdrv;

	अगर (!hw_पढ़ो(ci, CAP_DCCPARAMS, DCCPARAMS_HC))
		वापस -ENXIO;

	rdrv = devm_kzalloc(ci->dev, माप(काष्ठा ci_role_driver), GFP_KERNEL);
	अगर (!rdrv)
		वापस -ENOMEM;

	rdrv->start	= host_start;
	rdrv->stop	= host_stop;
	rdrv->irq	= host_irq;
	rdrv->name	= "host";
	ci->roles[CI_ROLE_HOST] = rdrv;

	अगर (ci->platdata->flags & CI_HDRC_REQUIRES_ALIGNED_DMA) अणु
		ci_ehci_hc_driver.map_urb_क्रम_dma = ci_hdrc_map_urb_क्रम_dma;
		ci_ehci_hc_driver.unmap_urb_क्रम_dma = ci_hdrc_unmap_urb_क्रम_dma;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ci_hdrc_host_driver_init(व्योम)
अणु
	ehci_init_driver(&ci_ehci_hc_driver, &ehci_ci_overrides);
	orig_bus_suspend = ci_ehci_hc_driver.bus_suspend;
	ci_ehci_hc_driver.bus_suspend = ci_ehci_bus_suspend;
	ci_ehci_hc_driver.hub_control = ci_ehci_hub_control;
पूर्ण
