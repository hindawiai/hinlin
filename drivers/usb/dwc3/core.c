<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * core.c - DesignWare USB3 DRD Controller Core file
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/version.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/reset.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/otg.h>

#समावेश "core.h"
#समावेश "gadget.h"
#समावेश "io.h"

#समावेश "debug.h"

#घोषणा DWC3_DEFAULT_AUTOSUSPEND_DELAY	5000 /* ms */

/**
 * dwc3_get_dr_mode - Validates and sets dr_mode
 * @dwc: poपूर्णांकer to our context काष्ठाure
 */
अटल पूर्णांक dwc3_get_dr_mode(काष्ठा dwc3 *dwc)
अणु
	क्रमागत usb_dr_mode mode;
	काष्ठा device *dev = dwc->dev;
	अचिन्हित पूर्णांक hw_mode;

	अगर (dwc->dr_mode == USB_DR_MODE_UNKNOWN)
		dwc->dr_mode = USB_DR_MODE_OTG;

	mode = dwc->dr_mode;
	hw_mode = DWC3_GHWPARAMS0_MODE(dwc->hwparams.hwparams0);

	चयन (hw_mode) अणु
	हाल DWC3_GHWPARAMS0_MODE_GADGET:
		अगर (IS_ENABLED(CONFIG_USB_DWC3_HOST)) अणु
			dev_err(dev,
				"Controller does not support host mode.\n");
			वापस -EINVAL;
		पूर्ण
		mode = USB_DR_MODE_PERIPHERAL;
		अवरोध;
	हाल DWC3_GHWPARAMS0_MODE_HOST:
		अगर (IS_ENABLED(CONFIG_USB_DWC3_GADGET)) अणु
			dev_err(dev,
				"Controller does not support device mode.\n");
			वापस -EINVAL;
		पूर्ण
		mode = USB_DR_MODE_HOST;
		अवरोध;
	शेष:
		अगर (IS_ENABLED(CONFIG_USB_DWC3_HOST))
			mode = USB_DR_MODE_HOST;
		अन्यथा अगर (IS_ENABLED(CONFIG_USB_DWC3_GADGET))
			mode = USB_DR_MODE_PERIPHERAL;

		/*
		 * DWC_usb31 and DWC_usb3 v3.30a and higher करो not support OTG
		 * mode. If the controller supports DRD but the dr_mode is not
		 * specअगरied or set to OTG, then set the mode to peripheral.
		 */
		अगर (mode == USB_DR_MODE_OTG &&
		    (!IS_ENABLED(CONFIG_USB_ROLE_SWITCH) ||
		     !device_property_पढ़ो_bool(dwc->dev, "usb-role-switch")) &&
		    !DWC3_VER_IS_PRIOR(DWC3, 330A))
			mode = USB_DR_MODE_PERIPHERAL;
	पूर्ण

	अगर (mode != dwc->dr_mode) अणु
		dev_warn(dev,
			 "Configuration mismatch. dr_mode forced to %s\n",
			 mode == USB_DR_MODE_HOST ? "host" : "gadget");

		dwc->dr_mode = mode;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dwc3_set_prtcap(काष्ठा dwc3 *dwc, u32 mode)
अणु
	u32 reg;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GCTL);
	reg &= ~(DWC3_GCTL_PRTCAPसूची(DWC3_GCTL_PRTCAP_OTG));
	reg |= DWC3_GCTL_PRTCAPसूची(mode);
	dwc3_ग_लिखोl(dwc->regs, DWC3_GCTL, reg);

	dwc->current_dr_role = mode;
पूर्ण

अटल पूर्णांक dwc3_core_soft_reset(काष्ठा dwc3 *dwc);

अटल व्योम __dwc3_set_mode(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dwc3 *dwc = work_to_dwc(work);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	u32 reg;

	mutex_lock(&dwc->mutex);

	pm_runसमय_get_sync(dwc->dev);

	अगर (dwc->current_dr_role == DWC3_GCTL_PRTCAP_OTG)
		dwc3_otg_update(dwc, 0);

	अगर (!dwc->desired_dr_role)
		जाओ out;

	अगर (dwc->desired_dr_role == dwc->current_dr_role)
		जाओ out;

	अगर (dwc->desired_dr_role == DWC3_GCTL_PRTCAP_OTG && dwc->edev)
		जाओ out;

	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_HOST:
		dwc3_host_निकास(dwc);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_gadget_निकास(dwc);
		dwc3_event_buffers_cleanup(dwc);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		dwc3_otg_निकास(dwc);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc->desired_otg_role = DWC3_OTG_ROLE_IDLE;
		spin_unlock_irqrestore(&dwc->lock, flags);
		dwc3_otg_update(dwc, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* For DRD host or device mode only */
	अगर (dwc->desired_dr_role != DWC3_GCTL_PRTCAP_OTG) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GCTL);
		reg |= DWC3_GCTL_CORESOFTRESET;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GCTL, reg);

		/*
		 * Wait क्रम पूर्णांकernal घड़ीs to synchronized. DWC_usb31 and
		 * DWC_usb32 may need at least 50ms (less क्रम DWC_usb3). To
		 * keep it consistent across dअगरferent IPs, let's रुको up to
		 * 100ms beक्रमe clearing GCTL.CORESOFTRESET.
		 */
		msleep(100);

		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GCTL);
		reg &= ~DWC3_GCTL_CORESOFTRESET;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GCTL, reg);
	पूर्ण

	spin_lock_irqsave(&dwc->lock, flags);

	dwc3_set_prtcap(dwc, dwc->desired_dr_role);

	spin_unlock_irqrestore(&dwc->lock, flags);

	चयन (dwc->desired_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_HOST:
		ret = dwc3_host_init(dwc);
		अगर (ret) अणु
			dev_err(dwc->dev, "failed to initialize host\n");
		पूर्ण अन्यथा अणु
			अगर (dwc->usb2_phy)
				otg_set_vbus(dwc->usb2_phy->otg, true);
			phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_HOST);
			phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_HOST);
			अगर (dwc->dis_split_quirk) अणु
				reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUCTL3);
				reg |= DWC3_GUCTL3_SPLITDISABLE;
				dwc3_ग_लिखोl(dwc->regs, DWC3_GUCTL3, reg);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_core_soft_reset(dwc);

		dwc3_event_buffers_setup(dwc);

		अगर (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, false);
		phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_DEVICE);
		phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_DEVICE);

		ret = dwc3_gadget_init(dwc);
		अगर (ret)
			dev_err(dwc->dev, "failed to initialize peripheral\n");
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		dwc3_otg_init(dwc);
		dwc3_otg_update(dwc, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	pm_runसमय_mark_last_busy(dwc->dev);
	pm_runसमय_put_स्वतःsuspend(dwc->dev);
	mutex_unlock(&dwc->mutex);
पूर्ण

व्योम dwc3_set_mode(काष्ठा dwc3 *dwc, u32 mode)
अणु
	अचिन्हित दीर्घ flags;

	अगर (dwc->dr_mode != USB_DR_MODE_OTG)
		वापस;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->desired_dr_role = mode;
	spin_unlock_irqrestore(&dwc->lock, flags);

	queue_work(प्रणाली_मुक्तzable_wq, &dwc->drd_work);
पूर्ण

u32 dwc3_core_fअगरo_space(काष्ठा dwc3_ep *dep, u8 type)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;
	u32			reg;

	dwc3_ग_लिखोl(dwc->regs, DWC3_GDBGFIFOSPACE,
			DWC3_GDBGFIFOSPACE_NUM(dep->number) |
			DWC3_GDBGFIFOSPACE_TYPE(type));

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GDBGFIFOSPACE);

	वापस DWC3_GDBGFIFOSPACE_SPACE_AVAILABLE(reg);
पूर्ण

/**
 * dwc3_core_soft_reset - Issues core soft reset and PHY reset
 * @dwc: poपूर्णांकer to our context काष्ठाure
 */
अटल पूर्णांक dwc3_core_soft_reset(काष्ठा dwc3 *dwc)
अणु
	u32		reg;
	पूर्णांक		retries = 1000;
	पूर्णांक		ret;

	usb_phy_init(dwc->usb2_phy);
	usb_phy_init(dwc->usb3_phy);
	ret = phy_init(dwc->usb2_generic_phy);
	अगर (ret < 0)
		वापस ret;

	ret = phy_init(dwc->usb3_generic_phy);
	अगर (ret < 0) अणु
		phy_निकास(dwc->usb2_generic_phy);
		वापस ret;
	पूर्ण

	/*
	 * We're resetting only the device side because, if we're in host mode,
	 * XHCI driver will reset the host block. If dwc3 was configured क्रम
	 * host-only mode, then we can वापस early.
	 */
	अगर (dwc->current_dr_role == DWC3_GCTL_PRTCAP_HOST)
		वापस 0;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	reg |= DWC3_DCTL_CSFTRST;
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);

	/*
	 * For DWC_usb31 controller 1.90a and later, the DCTL.CSFRST bit
	 * is cleared only after all the घड़ीs are synchronized. This can
	 * take a little more than 50ms. Set the polling rate at 20ms
	 * क्रम 10 बार instead.
	 */
	अगर (DWC3_VER_IS_WITHIN(DWC31, 190A, ANY) || DWC3_IP_IS(DWC32))
		retries = 10;

	करो अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
		अगर (!(reg & DWC3_DCTL_CSFTRST))
			जाओ करोne;

		अगर (DWC3_VER_IS_WITHIN(DWC31, 190A, ANY) || DWC3_IP_IS(DWC32))
			msleep(20);
		अन्यथा
			udelay(1);
	पूर्ण जबतक (--retries);

	phy_निकास(dwc->usb3_generic_phy);
	phy_निकास(dwc->usb2_generic_phy);

	वापस -ETIMEDOUT;

करोne:
	/*
	 * For DWC_usb31 controller 1.80a and prior, once DCTL.CSFRST bit
	 * is cleared, we must रुको at least 50ms beक्रमe accessing the PHY
	 * करोमुख्य (synchronization delay).
	 */
	अगर (DWC3_VER_IS_WITHIN(DWC31, ANY, 180A))
		msleep(50);

	वापस 0;
पूर्ण

/*
 * dwc3_frame_length_adjusपंचांगent - Adjusts frame length अगर required
 * @dwc3: Poपूर्णांकer to our controller context काष्ठाure
 */
अटल व्योम dwc3_frame_length_adjusपंचांगent(काष्ठा dwc3 *dwc)
अणु
	u32 reg;
	u32 dft;

	अगर (DWC3_VER_IS_PRIOR(DWC3, 250A))
		वापस;

	अगर (dwc->fladj == 0)
		वापस;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GFLADJ);
	dft = reg & DWC3_GFLADJ_30MHZ_MASK;
	अगर (dft != dwc->fladj) अणु
		reg &= ~DWC3_GFLADJ_30MHZ_MASK;
		reg |= DWC3_GFLADJ_30MHZ_SDBND_SEL | dwc->fladj;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GFLADJ, reg);
	पूर्ण
पूर्ण

/**
 * dwc3_मुक्त_one_event_buffer - Frees one event buffer
 * @dwc: Poपूर्णांकer to our controller context काष्ठाure
 * @evt: Poपूर्णांकer to event buffer to be मुक्तd
 */
अटल व्योम dwc3_मुक्त_one_event_buffer(काष्ठा dwc3 *dwc,
		काष्ठा dwc3_event_buffer *evt)
अणु
	dma_मुक्त_coherent(dwc->sysdev, evt->length, evt->buf, evt->dma);
पूर्ण

/**
 * dwc3_alloc_one_event_buffer - Allocates one event buffer काष्ठाure
 * @dwc: Poपूर्णांकer to our controller context काष्ठाure
 * @length: size of the event buffer
 *
 * Returns a poपूर्णांकer to the allocated event buffer काष्ठाure on success
 * otherwise ERR_PTR(त्रुटि_सं).
 */
अटल काष्ठा dwc3_event_buffer *dwc3_alloc_one_event_buffer(काष्ठा dwc3 *dwc,
		अचिन्हित length)
अणु
	काष्ठा dwc3_event_buffer	*evt;

	evt = devm_kzalloc(dwc->dev, माप(*evt), GFP_KERNEL);
	अगर (!evt)
		वापस ERR_PTR(-ENOMEM);

	evt->dwc	= dwc;
	evt->length	= length;
	evt->cache	= devm_kzalloc(dwc->dev, length, GFP_KERNEL);
	अगर (!evt->cache)
		वापस ERR_PTR(-ENOMEM);

	evt->buf	= dma_alloc_coherent(dwc->sysdev, length,
			&evt->dma, GFP_KERNEL);
	अगर (!evt->buf)
		वापस ERR_PTR(-ENOMEM);

	वापस evt;
पूर्ण

/**
 * dwc3_मुक्त_event_buffers - मुक्तs all allocated event buffers
 * @dwc: Poपूर्णांकer to our controller context काष्ठाure
 */
अटल व्योम dwc3_मुक्त_event_buffers(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_event_buffer	*evt;

	evt = dwc->ev_buf;
	अगर (evt)
		dwc3_मुक्त_one_event_buffer(dwc, evt);
पूर्ण

/**
 * dwc3_alloc_event_buffers - Allocates @num event buffers of size @length
 * @dwc: poपूर्णांकer to our controller context काष्ठाure
 * @length: size of event buffer
 *
 * Returns 0 on success otherwise negative त्रुटि_सं. In the error हाल, dwc
 * may contain some buffers allocated but not all which were requested.
 */
अटल पूर्णांक dwc3_alloc_event_buffers(काष्ठा dwc3 *dwc, अचिन्हित length)
अणु
	काष्ठा dwc3_event_buffer *evt;

	evt = dwc3_alloc_one_event_buffer(dwc, length);
	अगर (IS_ERR(evt)) अणु
		dev_err(dwc->dev, "can't allocate event buffer\n");
		वापस PTR_ERR(evt);
	पूर्ण
	dwc->ev_buf = evt;

	वापस 0;
पूर्ण

/**
 * dwc3_event_buffers_setup - setup our allocated event buffers
 * @dwc: poपूर्णांकer to our controller context काष्ठाure
 *
 * Returns 0 on success otherwise negative त्रुटि_सं.
 */
पूर्णांक dwc3_event_buffers_setup(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_event_buffer	*evt;

	evt = dwc->ev_buf;
	evt->lpos = 0;
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTADRLO(0),
			lower_32_bits(evt->dma));
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTADRHI(0),
			upper_32_bits(evt->dma));
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTSIZ(0),
			DWC3_GEVNTSIZ_SIZE(evt->length));
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTCOUNT(0), 0);

	वापस 0;
पूर्ण

व्योम dwc3_event_buffers_cleanup(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_event_buffer	*evt;

	evt = dwc->ev_buf;

	evt->lpos = 0;

	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTADRLO(0), 0);
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTADRHI(0), 0);
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTSIZ(0), DWC3_GEVNTSIZ_INTMASK
			| DWC3_GEVNTSIZ_SIZE(0));
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTCOUNT(0), 0);
पूर्ण

अटल पूर्णांक dwc3_alloc_scratch_buffers(काष्ठा dwc3 *dwc)
अणु
	अगर (!dwc->has_hibernation)
		वापस 0;

	अगर (!dwc->nr_scratch)
		वापस 0;

	dwc->scratchbuf = kदो_स्मृति_array(dwc->nr_scratch,
			DWC3_SCRATCHBUF_SIZE, GFP_KERNEL);
	अगर (!dwc->scratchbuf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_setup_scratch_buffers(काष्ठा dwc3 *dwc)
अणु
	dma_addr_t scratch_addr;
	u32 param;
	पूर्णांक ret;

	अगर (!dwc->has_hibernation)
		वापस 0;

	अगर (!dwc->nr_scratch)
		वापस 0;

	 /* should never fall here */
	अगर (!WARN_ON(dwc->scratchbuf))
		वापस 0;

	scratch_addr = dma_map_single(dwc->sysdev, dwc->scratchbuf,
			dwc->nr_scratch * DWC3_SCRATCHBUF_SIZE,
			DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dwc->sysdev, scratch_addr)) अणु
		dev_err(dwc->sysdev, "failed to map scratch buffer\n");
		ret = -EFAULT;
		जाओ err0;
	पूर्ण

	dwc->scratch_addr = scratch_addr;

	param = lower_32_bits(scratch_addr);

	ret = dwc3_send_gadget_generic_command(dwc,
			DWC3_DGCMD_SET_SCRATCHPAD_ADDR_LO, param);
	अगर (ret < 0)
		जाओ err1;

	param = upper_32_bits(scratch_addr);

	ret = dwc3_send_gadget_generic_command(dwc,
			DWC3_DGCMD_SET_SCRATCHPAD_ADDR_HI, param);
	अगर (ret < 0)
		जाओ err1;

	वापस 0;

err1:
	dma_unmap_single(dwc->sysdev, dwc->scratch_addr, dwc->nr_scratch *
			DWC3_SCRATCHBUF_SIZE, DMA_BIसूचीECTIONAL);

err0:
	वापस ret;
पूर्ण

अटल व्योम dwc3_मुक्त_scratch_buffers(काष्ठा dwc3 *dwc)
अणु
	अगर (!dwc->has_hibernation)
		वापस;

	अगर (!dwc->nr_scratch)
		वापस;

	 /* should never fall here */
	अगर (!WARN_ON(dwc->scratchbuf))
		वापस;

	dma_unmap_single(dwc->sysdev, dwc->scratch_addr, dwc->nr_scratch *
			DWC3_SCRATCHBUF_SIZE, DMA_BIसूचीECTIONAL);
	kमुक्त(dwc->scratchbuf);
पूर्ण

अटल व्योम dwc3_core_num_eps(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_hwparams	*parms = &dwc->hwparams;

	dwc->num_eps = DWC3_NUM_EPS(parms);
पूर्ण

अटल व्योम dwc3_cache_hwparams(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_hwparams	*parms = &dwc->hwparams;

	parms->hwparams0 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS0);
	parms->hwparams1 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS1);
	parms->hwparams2 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS2);
	parms->hwparams3 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS3);
	parms->hwparams4 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS4);
	parms->hwparams5 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS5);
	parms->hwparams6 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS6);
	parms->hwparams7 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS7);
	parms->hwparams8 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS8);

	अगर (DWC3_IP_IS(DWC32))
		parms->hwparams9 = dwc3_पढ़ोl(dwc->regs, DWC3_GHWPARAMS9);
पूर्ण

अटल पूर्णांक dwc3_core_ulpi_init(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक पूर्णांकf;
	पूर्णांक ret = 0;

	पूर्णांकf = DWC3_GHWPARAMS3_HSPHY_IFC(dwc->hwparams.hwparams3);

	अगर (पूर्णांकf == DWC3_GHWPARAMS3_HSPHY_IFC_ULPI ||
	    (पूर्णांकf == DWC3_GHWPARAMS3_HSPHY_IFC_UTMI_ULPI &&
	     dwc->hsphy_पूर्णांकerface &&
	     !म_भेदन(dwc->hsphy_पूर्णांकerface, "ulpi", 4)))
		ret = dwc3_ulpi_init(dwc);

	वापस ret;
पूर्ण

/**
 * dwc3_phy_setup - Configure USB PHY Interface of DWC3 Core
 * @dwc: Poपूर्णांकer to our controller context काष्ठाure
 *
 * Returns 0 on success. The USB PHY पूर्णांकerfaces are configured but not
 * initialized. The PHY पूर्णांकerfaces and the PHYs get initialized together with
 * the core in dwc3_core_init.
 */
अटल पूर्णांक dwc3_phy_setup(काष्ठा dwc3 *dwc)
अणु
	अचिन्हित पूर्णांक hw_mode;
	u32 reg;

	hw_mode = DWC3_GHWPARAMS0_MODE(dwc->hwparams.hwparams0);

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB3PIPECTL(0));

	/*
	 * Make sure UX_EXIT_PX is cleared as that causes issues with some
	 * PHYs. Also, this bit is not supposed to be used in normal operation.
	 */
	reg &= ~DWC3_GUSB3PIPECTL_UX_EXIT_PX;

	/*
	 * Above 1.94a, it is recommended to set DWC3_GUSB3PIPECTL_SUSPHY
	 * to '0' during coreConsultant configuration. So शेष value
	 * will be '0' when the core is reset. Application needs to set it
	 * to '1' after the core initialization is completed.
	 */
	अगर (!DWC3_VER_IS_WITHIN(DWC3, ANY, 194A))
		reg |= DWC3_GUSB3PIPECTL_SUSPHY;

	/*
	 * For DRD controllers, GUSB3PIPECTL.SUSPENDENABLE must be cleared after
	 * घातer-on reset, and it can be set after core initialization, which is
	 * after device soft-reset during initialization.
	 */
	अगर (hw_mode == DWC3_GHWPARAMS0_MODE_DRD)
		reg &= ~DWC3_GUSB3PIPECTL_SUSPHY;

	अगर (dwc->u2ss_inp3_quirk)
		reg |= DWC3_GUSB3PIPECTL_U2SSINP3OK;

	अगर (dwc->dis_rxdet_inp3_quirk)
		reg |= DWC3_GUSB3PIPECTL_DISRXDETINP3;

	अगर (dwc->req_p1p2p3_quirk)
		reg |= DWC3_GUSB3PIPECTL_REQP1P2P3;

	अगर (dwc->del_p1p2p3_quirk)
		reg |= DWC3_GUSB3PIPECTL_DEP1P2P3_EN;

	अगर (dwc->del_phy_घातer_chg_quirk)
		reg |= DWC3_GUSB3PIPECTL_DEPOCHANGE;

	अगर (dwc->lfps_filter_quirk)
		reg |= DWC3_GUSB3PIPECTL_LFPSFILT;

	अगर (dwc->rx_detect_poll_quirk)
		reg |= DWC3_GUSB3PIPECTL_RX_DETOPOLL;

	अगर (dwc->tx_de_emphasis_quirk)
		reg |= DWC3_GUSB3PIPECTL_TX_DEEPH(dwc->tx_de_emphasis);

	अगर (dwc->dis_u3_susphy_quirk)
		reg &= ~DWC3_GUSB3PIPECTL_SUSPHY;

	अगर (dwc->dis_del_phy_घातer_chg_quirk)
		reg &= ~DWC3_GUSB3PIPECTL_DEPOCHANGE;

	dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB3PIPECTL(0), reg);

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));

	/* Select the HS PHY पूर्णांकerface */
	चयन (DWC3_GHWPARAMS3_HSPHY_IFC(dwc->hwparams.hwparams3)) अणु
	हाल DWC3_GHWPARAMS3_HSPHY_IFC_UTMI_ULPI:
		अगर (dwc->hsphy_पूर्णांकerface &&
				!म_भेदन(dwc->hsphy_पूर्णांकerface, "utmi", 4)) अणु
			reg &= ~DWC3_GUSB2PHYCFG_ULPI_UTMI;
			अवरोध;
		पूर्ण अन्यथा अगर (dwc->hsphy_पूर्णांकerface &&
				!म_भेदन(dwc->hsphy_पूर्णांकerface, "ulpi", 4)) अणु
			reg |= DWC3_GUSB2PHYCFG_ULPI_UTMI;
			dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
		पूर्ण अन्यथा अणु
			/* Relying on शेष value. */
			अगर (!(reg & DWC3_GUSB2PHYCFG_ULPI_UTMI))
				अवरोध;
		पूर्ण
		fallthrough;
	हाल DWC3_GHWPARAMS3_HSPHY_IFC_ULPI:
	शेष:
		अवरोध;
	पूर्ण

	चयन (dwc->hsphy_mode) अणु
	हाल USBPHY_INTERFACE_MODE_UTMI:
		reg &= ~(DWC3_GUSB2PHYCFG_PHYIF_MASK |
		       DWC3_GUSB2PHYCFG_USBTRDTIM_MASK);
		reg |= DWC3_GUSB2PHYCFG_PHYIF(UTMI_PHYIF_8_BIT) |
		       DWC3_GUSB2PHYCFG_USBTRDTIM(USBTRDTIM_UTMI_8_BIT);
		अवरोध;
	हाल USBPHY_INTERFACE_MODE_UTMIW:
		reg &= ~(DWC3_GUSB2PHYCFG_PHYIF_MASK |
		       DWC3_GUSB2PHYCFG_USBTRDTIM_MASK);
		reg |= DWC3_GUSB2PHYCFG_PHYIF(UTMI_PHYIF_16_BIT) |
		       DWC3_GUSB2PHYCFG_USBTRDTIM(USBTRDTIM_UTMI_16_BIT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Above 1.94a, it is recommended to set DWC3_GUSB2PHYCFG_SUSPHY to
	 * '0' during coreConsultant configuration. So शेष value will
	 * be '0' when the core is reset. Application needs to set it to
	 * '1' after the core initialization is completed.
	 */
	अगर (!DWC3_VER_IS_WITHIN(DWC3, ANY, 194A))
		reg |= DWC3_GUSB2PHYCFG_SUSPHY;

	/*
	 * For DRD controllers, GUSB2PHYCFG.SUSPHY must be cleared after
	 * घातer-on reset, and it can be set after core initialization, which is
	 * after device soft-reset during initialization.
	 */
	अगर (hw_mode == DWC3_GHWPARAMS0_MODE_DRD)
		reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

	अगर (dwc->dis_u2_susphy_quirk)
		reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

	अगर (dwc->dis_enblslpm_quirk)
		reg &= ~DWC3_GUSB2PHYCFG_ENBLSLPM;
	अन्यथा
		reg |= DWC3_GUSB2PHYCFG_ENBLSLPM;

	अगर (dwc->dis_u2_मुक्तclk_exists_quirk)
		reg &= ~DWC3_GUSB2PHYCFG_U2_FREECLK_EXISTS;

	dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);

	वापस 0;
पूर्ण

अटल व्योम dwc3_core_निकास(काष्ठा dwc3 *dwc)
अणु
	dwc3_event_buffers_cleanup(dwc);

	usb_phy_shutकरोwn(dwc->usb2_phy);
	usb_phy_shutकरोwn(dwc->usb3_phy);
	phy_निकास(dwc->usb2_generic_phy);
	phy_निकास(dwc->usb3_generic_phy);

	usb_phy_set_suspend(dwc->usb2_phy, 1);
	usb_phy_set_suspend(dwc->usb3_phy, 1);
	phy_घातer_off(dwc->usb2_generic_phy);
	phy_घातer_off(dwc->usb3_generic_phy);
	clk_bulk_disable_unprepare(dwc->num_clks, dwc->clks);
	reset_control_निश्चित(dwc->reset);
पूर्ण

अटल bool dwc3_core_is_valid(काष्ठा dwc3 *dwc)
अणु
	u32 reg;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GSNPSID);
	dwc->ip = DWC3_GSNPS_ID(reg);

	/* This should पढ़ो as U3 followed by revision number */
	अगर (DWC3_IP_IS(DWC3)) अणु
		dwc->revision = reg;
	पूर्ण अन्यथा अगर (DWC3_IP_IS(DWC31) || DWC3_IP_IS(DWC32)) अणु
		dwc->revision = dwc3_पढ़ोl(dwc->regs, DWC3_VER_NUMBER);
		dwc->version_type = dwc3_पढ़ोl(dwc->regs, DWC3_VER_TYPE);
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम dwc3_core_setup_global_control(काष्ठा dwc3 *dwc)
अणु
	u32 hwparams4 = dwc->hwparams.hwparams4;
	u32 reg;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GCTL);
	reg &= ~DWC3_GCTL_SCALEDOWN_MASK;

	चयन (DWC3_GHWPARAMS1_EN_PWROPT(dwc->hwparams.hwparams1)) अणु
	हाल DWC3_GHWPARAMS1_EN_PWROPT_CLK:
		/**
		 * WORKAROUND: DWC3 revisions between 2.10a and 2.50a have an
		 * issue which would cause xHCI compliance tests to fail.
		 *
		 * Because of that we cannot enable घड़ी gating on such
		 * configurations.
		 *
		 * Refers to:
		 *
		 * STAR#9000588375: Clock Gating, SOF Issues when ref_clk-Based
		 * SOF/ITP Mode Used
		 */
		अगर ((dwc->dr_mode == USB_DR_MODE_HOST ||
				dwc->dr_mode == USB_DR_MODE_OTG) &&
				DWC3_VER_IS_WITHIN(DWC3, 210A, 250A))
			reg |= DWC3_GCTL_DSBLCLKGTNG | DWC3_GCTL_SOFITPSYNC;
		अन्यथा
			reg &= ~DWC3_GCTL_DSBLCLKGTNG;
		अवरोध;
	हाल DWC3_GHWPARAMS1_EN_PWROPT_HIB:
		/* enable hibernation here */
		dwc->nr_scratch = DWC3_GHWPARAMS4_HIBER_SCRATCHBUFS(hwparams4);

		/*
		 * REVISIT Enabling this bit so that host-mode hibernation
		 * will work. Device-mode hibernation is not yet implemented.
		 */
		reg |= DWC3_GCTL_GBLHIBERNATIONEN;
		अवरोध;
	शेष:
		/* nothing */
		अवरोध;
	पूर्ण

	/* check अगर current dwc3 is on simulation board */
	अगर (dwc->hwparams.hwparams6 & DWC3_GHWPARAMS6_EN_FPGA) अणु
		dev_info(dwc->dev, "Running with FPGA optimizations\n");
		dwc->is_fpga = true;
	पूर्ण

	WARN_ONCE(dwc->disable_scramble_quirk && !dwc->is_fpga,
			"disable_scramble cannot be used on non-FPGA builds\n");

	अगर (dwc->disable_scramble_quirk && dwc->is_fpga)
		reg |= DWC3_GCTL_DISSCRAMBLE;
	अन्यथा
		reg &= ~DWC3_GCTL_DISSCRAMBLE;

	अगर (dwc->u2निकास_lfps_quirk)
		reg |= DWC3_GCTL_U2EXIT_LFPS;

	/*
	 * WORKAROUND: DWC3 revisions <1.90a have a bug
	 * where the device can fail to connect at SuperSpeed
	 * and falls back to high-speed mode which causes
	 * the device to enter a Connect/Disconnect loop
	 */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 190A))
		reg |= DWC3_GCTL_U2RSTECN;

	dwc3_ग_लिखोl(dwc->regs, DWC3_GCTL, reg);
पूर्ण

अटल पूर्णांक dwc3_core_get_phy(काष्ठा dwc3 *dwc);
अटल पूर्णांक dwc3_core_ulpi_init(काष्ठा dwc3 *dwc);

/* set global incr burst type configuration रेजिस्टरs */
अटल व्योम dwc3_set_incr_burst_type(काष्ठा dwc3 *dwc)
अणु
	काष्ठा device *dev = dwc->dev;
	/* incrx_mode : क्रम INCR burst type. */
	bool incrx_mode;
	/* incrx_size : क्रम size of INCRX burst. */
	u32 incrx_size;
	u32 *vals;
	u32 cfg;
	पूर्णांक ntype;
	पूर्णांक ret;
	पूर्णांक i;

	cfg = dwc3_पढ़ोl(dwc->regs, DWC3_GSBUSCFG0);

	/*
	 * Handle property "snps,incr-burst-type-adjustment".
	 * Get the number of value from this property:
	 * result <= 0, means this property is not supported.
	 * result = 1, means INCRx burst mode supported.
	 * result > 1, means undefined length burst mode supported.
	 */
	ntype = device_property_count_u32(dev, "snps,incr-burst-type-adjustment");
	अगर (ntype <= 0)
		वापस;

	vals = kसुस्मृति(ntype, माप(u32), GFP_KERNEL);
	अगर (!vals) अणु
		dev_err(dev, "Error to get memory\n");
		वापस;
	पूर्ण

	/* Get INCR burst type, and parse it */
	ret = device_property_पढ़ो_u32_array(dev,
			"snps,incr-burst-type-adjustment", vals, ntype);
	अगर (ret) अणु
		kमुक्त(vals);
		dev_err(dev, "Error to get property\n");
		वापस;
	पूर्ण

	incrx_size = *vals;

	अगर (ntype > 1) अणु
		/* INCRX (undefined length) burst mode */
		incrx_mode = INCRX_UNDEF_LENGTH_BURST_MODE;
		क्रम (i = 1; i < ntype; i++) अणु
			अगर (vals[i] > incrx_size)
				incrx_size = vals[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		/* INCRX burst mode */
		incrx_mode = INCRX_BURST_MODE;
	पूर्ण

	kमुक्त(vals);

	/* Enable Undefined Length INCR Burst and Enable INCRx Burst */
	cfg &= ~DWC3_GSBUSCFG0_INCRBRST_MASK;
	अगर (incrx_mode)
		cfg |= DWC3_GSBUSCFG0_INCRBRSTENA;
	चयन (incrx_size) अणु
	हाल 256:
		cfg |= DWC3_GSBUSCFG0_INCR256BRSTENA;
		अवरोध;
	हाल 128:
		cfg |= DWC3_GSBUSCFG0_INCR128BRSTENA;
		अवरोध;
	हाल 64:
		cfg |= DWC3_GSBUSCFG0_INCR64BRSTENA;
		अवरोध;
	हाल 32:
		cfg |= DWC3_GSBUSCFG0_INCR32BRSTENA;
		अवरोध;
	हाल 16:
		cfg |= DWC3_GSBUSCFG0_INCR16BRSTENA;
		अवरोध;
	हाल 8:
		cfg |= DWC3_GSBUSCFG0_INCR8BRSTENA;
		अवरोध;
	हाल 4:
		cfg |= DWC3_GSBUSCFG0_INCR4BRSTENA;
		अवरोध;
	हाल 1:
		अवरोध;
	शेष:
		dev_err(dev, "Invalid property\n");
		अवरोध;
	पूर्ण

	dwc3_ग_लिखोl(dwc->regs, DWC3_GSBUSCFG0, cfg);
पूर्ण

/**
 * dwc3_core_init - Low-level initialization of DWC3 Core
 * @dwc: Poपूर्णांकer to our controller context काष्ठाure
 *
 * Returns 0 on success otherwise negative त्रुटि_सं.
 */
अटल पूर्णांक dwc3_core_init(काष्ठा dwc3 *dwc)
अणु
	अचिन्हित पूर्णांक		hw_mode;
	u32			reg;
	पूर्णांक			ret;

	hw_mode = DWC3_GHWPARAMS0_MODE(dwc->hwparams.hwparams0);

	/*
	 * Write Linux Version Code to our GUID रेजिस्टर so it's easy to figure
	 * out which kernel version a bug was found.
	 */
	dwc3_ग_लिखोl(dwc->regs, DWC3_GUID, LINUX_VERSION_CODE);

	ret = dwc3_phy_setup(dwc);
	अगर (ret)
		जाओ err0;

	अगर (!dwc->ulpi_पढ़ोy) अणु
		ret = dwc3_core_ulpi_init(dwc);
		अगर (ret)
			जाओ err0;
		dwc->ulpi_पढ़ोy = true;
	पूर्ण

	अगर (!dwc->phys_पढ़ोy) अणु
		ret = dwc3_core_get_phy(dwc);
		अगर (ret)
			जाओ err0a;
		dwc->phys_पढ़ोy = true;
	पूर्ण

	ret = dwc3_core_soft_reset(dwc);
	अगर (ret)
		जाओ err0a;

	अगर (hw_mode == DWC3_GHWPARAMS0_MODE_DRD &&
	    !DWC3_VER_IS_WITHIN(DWC3, ANY, 194A)) अणु
		अगर (!dwc->dis_u3_susphy_quirk) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB3PIPECTL(0));
			reg |= DWC3_GUSB3PIPECTL_SUSPHY;
			dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB3PIPECTL(0), reg);
		पूर्ण

		अगर (!dwc->dis_u2_susphy_quirk) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
			reg |= DWC3_GUSB2PHYCFG_SUSPHY;
			dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
		पूर्ण
	पूर्ण

	dwc3_core_setup_global_control(dwc);
	dwc3_core_num_eps(dwc);

	ret = dwc3_setup_scratch_buffers(dwc);
	अगर (ret)
		जाओ err1;

	/* Adjust Frame Length */
	dwc3_frame_length_adjusपंचांगent(dwc);

	dwc3_set_incr_burst_type(dwc);

	usb_phy_set_suspend(dwc->usb2_phy, 0);
	usb_phy_set_suspend(dwc->usb3_phy, 0);
	ret = phy_घातer_on(dwc->usb2_generic_phy);
	अगर (ret < 0)
		जाओ err2;

	ret = phy_घातer_on(dwc->usb3_generic_phy);
	अगर (ret < 0)
		जाओ err3;

	ret = dwc3_event_buffers_setup(dwc);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to setup event buffers\n");
		जाओ err4;
	पूर्ण

	/*
	 * ENDXFER polling is available on version 3.10a and later of
	 * the DWC_usb3 controller. It is NOT available in the
	 * DWC_usb31 controller.
	 */
	अगर (DWC3_VER_IS_WITHIN(DWC3, 310A, ANY)) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUCTL2);
		reg |= DWC3_GUCTL2_RST_ACTBITLATER;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GUCTL2, reg);
	पूर्ण

	अगर (!DWC3_VER_IS_PRIOR(DWC3, 250A)) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUCTL1);

		/*
		 * Enable hardware control of sending remote wakeup
		 * in HS when the device is in the L1 state.
		 */
		अगर (!DWC3_VER_IS_PRIOR(DWC3, 290A))
			reg |= DWC3_GUCTL1_DEV_L1_EXIT_BY_HW;

		अगर (dwc->dis_tx_ipgap_linecheck_quirk)
			reg |= DWC3_GUCTL1_TX_IPGAP_LINECHECK_DIS;

		अगर (dwc->parkmode_disable_ss_quirk)
			reg |= DWC3_GUCTL1_PARKMODE_DISABLE_SS;

		dwc3_ग_लिखोl(dwc->regs, DWC3_GUCTL1, reg);
	पूर्ण

	अगर (dwc->dr_mode == USB_DR_MODE_HOST ||
	    dwc->dr_mode == USB_DR_MODE_OTG) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUCTL);

		/*
		 * Enable Auto retry Feature to make the controller operating in
		 * Host mode on seeing transaction errors(CRC errors or पूर्णांकernal
		 * overrun scenerios) on IN transfers to reply to the device
		 * with a non-terminating retry ACK (i.e, an ACK transcation
		 * packet with Retry=1 & Nump != 0)
		 */
		reg |= DWC3_GUCTL_HSTINAUTORETRY;

		dwc3_ग_लिखोl(dwc->regs, DWC3_GUCTL, reg);
	पूर्ण

	/*
	 * Must config both number of packets and max burst settings to enable
	 * RX and/or TX threshold.
	 */
	अगर (!DWC3_IP_IS(DWC3) && dwc->dr_mode == USB_DR_MODE_HOST) अणु
		u8 rx_thr_num = dwc->rx_thr_num_pkt_prd;
		u8 rx_maxburst = dwc->rx_max_burst_prd;
		u8 tx_thr_num = dwc->tx_thr_num_pkt_prd;
		u8 tx_maxburst = dwc->tx_max_burst_prd;

		अगर (rx_thr_num && rx_maxburst) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_GRXTHRCFG);
			reg |= DWC31_RXTHRNUMPKTSEL_PRD;

			reg &= ~DWC31_RXTHRNUMPKT_PRD(~0);
			reg |= DWC31_RXTHRNUMPKT_PRD(rx_thr_num);

			reg &= ~DWC31_MAXRXBURSTSIZE_PRD(~0);
			reg |= DWC31_MAXRXBURSTSIZE_PRD(rx_maxburst);

			dwc3_ग_लिखोl(dwc->regs, DWC3_GRXTHRCFG, reg);
		पूर्ण

		अगर (tx_thr_num && tx_maxburst) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_GTXTHRCFG);
			reg |= DWC31_TXTHRNUMPKTSEL_PRD;

			reg &= ~DWC31_TXTHRNUMPKT_PRD(~0);
			reg |= DWC31_TXTHRNUMPKT_PRD(tx_thr_num);

			reg &= ~DWC31_MAXTXBURSTSIZE_PRD(~0);
			reg |= DWC31_MAXTXBURSTSIZE_PRD(tx_maxburst);

			dwc3_ग_लिखोl(dwc->regs, DWC3_GTXTHRCFG, reg);
		पूर्ण
	पूर्ण

	वापस 0;

err4:
	phy_घातer_off(dwc->usb3_generic_phy);

err3:
	phy_घातer_off(dwc->usb2_generic_phy);

err2:
	usb_phy_set_suspend(dwc->usb2_phy, 1);
	usb_phy_set_suspend(dwc->usb3_phy, 1);

err1:
	usb_phy_shutकरोwn(dwc->usb2_phy);
	usb_phy_shutकरोwn(dwc->usb3_phy);
	phy_निकास(dwc->usb2_generic_phy);
	phy_निकास(dwc->usb3_generic_phy);

err0a:
	dwc3_ulpi_निकास(dwc);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_core_get_phy(काष्ठा dwc3 *dwc)
अणु
	काष्ठा device		*dev = dwc->dev;
	काष्ठा device_node	*node = dev->of_node;
	पूर्णांक ret;

	अगर (node) अणु
		dwc->usb2_phy = devm_usb_get_phy_by_phandle(dev, "usb-phy", 0);
		dwc->usb3_phy = devm_usb_get_phy_by_phandle(dev, "usb-phy", 1);
	पूर्ण अन्यथा अणु
		dwc->usb2_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
		dwc->usb3_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB3);
	पूर्ण

	अगर (IS_ERR(dwc->usb2_phy)) अणु
		ret = PTR_ERR(dwc->usb2_phy);
		अगर (ret == -ENXIO || ret == -ENODEV) अणु
			dwc->usb2_phy = शून्य;
		पूर्ण अन्यथा अणु
			वापस dev_err_probe(dev, ret, "no usb2 phy configured\n");
		पूर्ण
	पूर्ण

	अगर (IS_ERR(dwc->usb3_phy)) अणु
		ret = PTR_ERR(dwc->usb3_phy);
		अगर (ret == -ENXIO || ret == -ENODEV) अणु
			dwc->usb3_phy = शून्य;
		पूर्ण अन्यथा अणु
			वापस dev_err_probe(dev, ret, "no usb3 phy configured\n");
		पूर्ण
	पूर्ण

	dwc->usb2_generic_phy = devm_phy_get(dev, "usb2-phy");
	अगर (IS_ERR(dwc->usb2_generic_phy)) अणु
		ret = PTR_ERR(dwc->usb2_generic_phy);
		अगर (ret == -ENOSYS || ret == -ENODEV) अणु
			dwc->usb2_generic_phy = शून्य;
		पूर्ण अन्यथा अणु
			वापस dev_err_probe(dev, ret, "no usb2 phy configured\n");
		पूर्ण
	पूर्ण

	dwc->usb3_generic_phy = devm_phy_get(dev, "usb3-phy");
	अगर (IS_ERR(dwc->usb3_generic_phy)) अणु
		ret = PTR_ERR(dwc->usb3_generic_phy);
		अगर (ret == -ENOSYS || ret == -ENODEV) अणु
			dwc->usb3_generic_phy = शून्य;
		पूर्ण अन्यथा अणु
			वापस dev_err_probe(dev, ret, "no usb3 phy configured\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_core_init_mode(काष्ठा dwc3 *dwc)
अणु
	काष्ठा device *dev = dwc->dev;
	पूर्णांक ret;

	चयन (dwc->dr_mode) अणु
	हाल USB_DR_MODE_PERIPHERAL:
		dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_DEVICE);

		अगर (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, false);
		phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_DEVICE);
		phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_DEVICE);

		ret = dwc3_gadget_init(dwc);
		अगर (ret)
			वापस dev_err_probe(dev, ret, "failed to initialize gadget\n");
		अवरोध;
	हाल USB_DR_MODE_HOST:
		dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_HOST);

		अगर (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, true);
		phy_set_mode(dwc->usb2_generic_phy, PHY_MODE_USB_HOST);
		phy_set_mode(dwc->usb3_generic_phy, PHY_MODE_USB_HOST);

		ret = dwc3_host_init(dwc);
		अगर (ret)
			वापस dev_err_probe(dev, ret, "failed to initialize host\n");
		अवरोध;
	हाल USB_DR_MODE_OTG:
		INIT_WORK(&dwc->drd_work, __dwc3_set_mode);
		ret = dwc3_drd_init(dwc);
		अगर (ret)
			वापस dev_err_probe(dev, ret, "failed to initialize dual-role\n");
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported mode of operation %d\n", dwc->dr_mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc3_core_निकास_mode(काष्ठा dwc3 *dwc)
अणु
	चयन (dwc->dr_mode) अणु
	हाल USB_DR_MODE_PERIPHERAL:
		dwc3_gadget_निकास(dwc);
		अवरोध;
	हाल USB_DR_MODE_HOST:
		dwc3_host_निकास(dwc);
		अवरोध;
	हाल USB_DR_MODE_OTG:
		dwc3_drd_निकास(dwc);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	/* de-निश्चित DRVVBUS क्रम HOST and OTG mode */
	dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_DEVICE);
पूर्ण

अटल व्योम dwc3_get_properties(काष्ठा dwc3 *dwc)
अणु
	काष्ठा device		*dev = dwc->dev;
	u8			lpm_nyet_threshold;
	u8			tx_de_emphasis;
	u8			hird_threshold;
	u8			rx_thr_num_pkt_prd;
	u8			rx_max_burst_prd;
	u8			tx_thr_num_pkt_prd;
	u8			tx_max_burst_prd;
	स्थिर अक्षर		*usb_psy_name;
	पूर्णांक			ret;

	/* शेष to highest possible threshold */
	lpm_nyet_threshold = 0xf;

	/* शेष to -3.5dB de-emphasis */
	tx_de_emphasis = 1;

	/*
	 * शेष to निश्चित uपंचांगi_sleep_n and use maximum allowed HIRD
	 * threshold value of 0b1100
	 */
	hird_threshold = 12;

	dwc->maximum_speed = usb_get_maximum_speed(dev);
	dwc->max_ssp_rate = usb_get_maximum_ssp_rate(dev);
	dwc->dr_mode = usb_get_dr_mode(dev);
	dwc->hsphy_mode = of_usb_get_phy_mode(dev->of_node);

	dwc->sysdev_is_parent = device_property_पढ़ो_bool(dev,
				"linux,sysdev_is_parent");
	अगर (dwc->sysdev_is_parent)
		dwc->sysdev = dwc->dev->parent;
	अन्यथा
		dwc->sysdev = dwc->dev;

	ret = device_property_पढ़ो_string(dev, "usb-psy-name", &usb_psy_name);
	अगर (ret >= 0) अणु
		dwc->usb_psy = घातer_supply_get_by_name(usb_psy_name);
		अगर (!dwc->usb_psy)
			dev_err(dev, "couldn't get usb power supply\n");
	पूर्ण

	dwc->has_lpm_erratum = device_property_पढ़ो_bool(dev,
				"snps,has-lpm-erratum");
	device_property_पढ़ो_u8(dev, "snps,lpm-nyet-threshold",
				&lpm_nyet_threshold);
	dwc->is_uपंचांगi_l1_suspend = device_property_पढ़ो_bool(dev,
				"snps,is-utmi-l1-suspend");
	device_property_पढ़ो_u8(dev, "snps,hird-threshold",
				&hird_threshold);
	dwc->dis_start_transfer_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-start-transfer-quirk");
	dwc->usb3_lpm_capable = device_property_पढ़ो_bool(dev,
				"snps,usb3_lpm_capable");
	dwc->usb2_lpm_disable = device_property_पढ़ो_bool(dev,
				"snps,usb2-lpm-disable");
	dwc->usb2_gadget_lpm_disable = device_property_पढ़ो_bool(dev,
				"snps,usb2-gadget-lpm-disable");
	device_property_पढ़ो_u8(dev, "snps,rx-thr-num-pkt-prd",
				&rx_thr_num_pkt_prd);
	device_property_पढ़ो_u8(dev, "snps,rx-max-burst-prd",
				&rx_max_burst_prd);
	device_property_पढ़ो_u8(dev, "snps,tx-thr-num-pkt-prd",
				&tx_thr_num_pkt_prd);
	device_property_पढ़ो_u8(dev, "snps,tx-max-burst-prd",
				&tx_max_burst_prd);

	dwc->disable_scramble_quirk = device_property_पढ़ो_bool(dev,
				"snps,disable_scramble_quirk");
	dwc->u2निकास_lfps_quirk = device_property_पढ़ो_bool(dev,
				"snps,u2exit_lfps_quirk");
	dwc->u2ss_inp3_quirk = device_property_पढ़ो_bool(dev,
				"snps,u2ss_inp3_quirk");
	dwc->req_p1p2p3_quirk = device_property_पढ़ो_bool(dev,
				"snps,req_p1p2p3_quirk");
	dwc->del_p1p2p3_quirk = device_property_पढ़ो_bool(dev,
				"snps,del_p1p2p3_quirk");
	dwc->del_phy_घातer_chg_quirk = device_property_पढ़ो_bool(dev,
				"snps,del_phy_power_chg_quirk");
	dwc->lfps_filter_quirk = device_property_पढ़ो_bool(dev,
				"snps,lfps_filter_quirk");
	dwc->rx_detect_poll_quirk = device_property_पढ़ो_bool(dev,
				"snps,rx_detect_poll_quirk");
	dwc->dis_u3_susphy_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis_u3_susphy_quirk");
	dwc->dis_u2_susphy_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis_u2_susphy_quirk");
	dwc->dis_enblslpm_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis_enblslpm_quirk");
	dwc->dis_u1_entry_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-u1-entry-quirk");
	dwc->dis_u2_entry_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-u2-entry-quirk");
	dwc->dis_rxdet_inp3_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis_rxdet_inp3_quirk");
	dwc->dis_u2_मुक्तclk_exists_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-u2-freeclk-exists-quirk");
	dwc->dis_del_phy_घातer_chg_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-del-phy-power-chg-quirk");
	dwc->dis_tx_ipgap_linecheck_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-tx-ipgap-linecheck-quirk");
	dwc->parkmode_disable_ss_quirk = device_property_पढ़ो_bool(dev,
				"snps,parkmode-disable-ss-quirk");

	dwc->tx_de_emphasis_quirk = device_property_पढ़ो_bool(dev,
				"snps,tx_de_emphasis_quirk");
	device_property_पढ़ो_u8(dev, "snps,tx_de_emphasis",
				&tx_de_emphasis);
	device_property_पढ़ो_string(dev, "snps,hsphy_interface",
				    &dwc->hsphy_पूर्णांकerface);
	device_property_पढ़ो_u32(dev, "snps,quirk-frame-length-adjustment",
				 &dwc->fladj);

	dwc->dis_metastability_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis_metastability_quirk");

	dwc->dis_split_quirk = device_property_पढ़ो_bool(dev,
				"snps,dis-split-quirk");

	dwc->lpm_nyet_threshold = lpm_nyet_threshold;
	dwc->tx_de_emphasis = tx_de_emphasis;

	dwc->hird_threshold = hird_threshold;

	dwc->rx_thr_num_pkt_prd = rx_thr_num_pkt_prd;
	dwc->rx_max_burst_prd = rx_max_burst_prd;

	dwc->tx_thr_num_pkt_prd = tx_thr_num_pkt_prd;
	dwc->tx_max_burst_prd = tx_max_burst_prd;

	dwc->imod_पूर्णांकerval = 0;
पूर्ण

/* check whether the core supports IMOD */
bool dwc3_has_imod(काष्ठा dwc3 *dwc)
अणु
	वापस DWC3_VER_IS_WITHIN(DWC3, 300A, ANY) ||
		DWC3_VER_IS_WITHIN(DWC31, 120A, ANY) ||
		DWC3_IP_IS(DWC32);
पूर्ण

अटल व्योम dwc3_check_params(काष्ठा dwc3 *dwc)
अणु
	काष्ठा device *dev = dwc->dev;
	अचिन्हित पूर्णांक hwparam_gen =
		DWC3_GHWPARAMS3_SSPHY_IFC(dwc->hwparams.hwparams3);

	/* Check क्रम proper value of imod_पूर्णांकerval */
	अगर (dwc->imod_पूर्णांकerval && !dwc3_has_imod(dwc)) अणु
		dev_warn(dwc->dev, "Interrupt moderation not supported\n");
		dwc->imod_पूर्णांकerval = 0;
	पूर्ण

	/*
	 * Workaround क्रम STAR 9000961433 which affects only version
	 * 3.00a of the DWC_usb3 core. This prevents the controller
	 * पूर्णांकerrupt from being masked जबतक handling events. IMOD
	 * allows us to work around this issue. Enable it क्रम the
	 * affected version.
	 */
	अगर (!dwc->imod_पूर्णांकerval &&
	    DWC3_VER_IS(DWC3, 300A))
		dwc->imod_पूर्णांकerval = 1;

	/* Check the maximum_speed parameter */
	चयन (dwc->maximum_speed) अणु
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
		अवरोध;
	हाल USB_SPEED_SUPER:
		अगर (hwparam_gen == DWC3_GHWPARAMS3_SSPHY_IFC_DIS)
			dev_warn(dev, "UDC doesn't support Gen 1\n");
		अवरोध;
	हाल USB_SPEED_SUPER_PLUS:
		अगर ((DWC3_IP_IS(DWC32) &&
		     hwparam_gen == DWC3_GHWPARAMS3_SSPHY_IFC_DIS) ||
		    (!DWC3_IP_IS(DWC32) &&
		     hwparam_gen != DWC3_GHWPARAMS3_SSPHY_IFC_GEN2))
			dev_warn(dev, "UDC doesn't support SSP\n");
		अवरोध;
	शेष:
		dev_err(dev, "invalid maximum_speed parameter %d\n",
			dwc->maximum_speed);
		fallthrough;
	हाल USB_SPEED_UNKNOWN:
		चयन (hwparam_gen) अणु
		हाल DWC3_GHWPARAMS3_SSPHY_IFC_GEN2:
			dwc->maximum_speed = USB_SPEED_SUPER_PLUS;
			अवरोध;
		हाल DWC3_GHWPARAMS3_SSPHY_IFC_GEN1:
			अगर (DWC3_IP_IS(DWC32))
				dwc->maximum_speed = USB_SPEED_SUPER_PLUS;
			अन्यथा
				dwc->maximum_speed = USB_SPEED_SUPER;
			अवरोध;
		हाल DWC3_GHWPARAMS3_SSPHY_IFC_DIS:
			dwc->maximum_speed = USB_SPEED_HIGH;
			अवरोध;
		शेष:
			dwc->maximum_speed = USB_SPEED_SUPER;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * Currently the controller करोes not have visibility पूर्णांकo the HW
	 * parameter to determine the maximum number of lanes the HW supports.
	 * If the number of lanes is not specअगरied in the device property, then
	 * set the शेष to support dual-lane क्रम DWC_usb32 and single-lane
	 * क्रम DWC_usb31 क्रम super-speed-plus.
	 */
	अगर (dwc->maximum_speed == USB_SPEED_SUPER_PLUS) अणु
		चयन (dwc->max_ssp_rate) अणु
		हाल USB_SSP_GEN_2x1:
			अगर (hwparam_gen == DWC3_GHWPARAMS3_SSPHY_IFC_GEN1)
				dev_warn(dev, "UDC only supports Gen 1\n");
			अवरोध;
		हाल USB_SSP_GEN_1x2:
		हाल USB_SSP_GEN_2x2:
			अगर (DWC3_IP_IS(DWC31))
				dev_warn(dev, "UDC only supports single lane\n");
			अवरोध;
		हाल USB_SSP_GEN_UNKNOWN:
		शेष:
			चयन (hwparam_gen) अणु
			हाल DWC3_GHWPARAMS3_SSPHY_IFC_GEN2:
				अगर (DWC3_IP_IS(DWC32))
					dwc->max_ssp_rate = USB_SSP_GEN_2x2;
				अन्यथा
					dwc->max_ssp_rate = USB_SSP_GEN_2x1;
				अवरोध;
			हाल DWC3_GHWPARAMS3_SSPHY_IFC_GEN1:
				अगर (DWC3_IP_IS(DWC32))
					dwc->max_ssp_rate = USB_SSP_GEN_1x2;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा resource		*res, dwc_res;
	काष्ठा dwc3		*dwc;

	पूर्णांक			ret;

	व्योम __iomem		*regs;

	dwc = devm_kzalloc(dev, माप(*dwc), GFP_KERNEL);
	अगर (!dwc)
		वापस -ENOMEM;

	dwc->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "missing memory resource\n");
		वापस -ENODEV;
	पूर्ण

	dwc->xhci_resources[0].start = res->start;
	dwc->xhci_resources[0].end = dwc->xhci_resources[0].start +
					DWC3_XHCI_REGS_END;
	dwc->xhci_resources[0].flags = res->flags;
	dwc->xhci_resources[0].name = res->name;

	/*
	 * Request memory region but exclude xHCI regs,
	 * since it will be requested by the xhci-plat driver.
	 */
	dwc_res = *res;
	dwc_res.start += DWC3_GLOBALS_REGS_START;

	regs = devm_ioremap_resource(dev, &dwc_res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	dwc->regs	= regs;
	dwc->regs_size	= resource_size(&dwc_res);

	dwc3_get_properties(dwc);

	dwc->reset = devm_reset_control_array_get_optional_shared(dev);
	अगर (IS_ERR(dwc->reset))
		वापस PTR_ERR(dwc->reset);

	अगर (dev->of_node) अणु
		ret = devm_clk_bulk_get_all(dev, &dwc->clks);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		/*
		 * Clocks are optional, but new DT platक्रमms should support all
		 * घड़ीs as required by the DT-binding.
		 */
		अगर (ret < 0)
			dwc->num_clks = 0;
		अन्यथा
			dwc->num_clks = ret;

	पूर्ण

	ret = reset_control_deनिश्चित(dwc->reset);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(dwc->num_clks, dwc->clks);
	अगर (ret)
		जाओ निश्चित_reset;

	अगर (!dwc3_core_is_valid(dwc)) अणु
		dev_err(dwc->dev, "this is not a DesignWare USB3 DRD Core\n");
		ret = -ENODEV;
		जाओ disable_clks;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dwc);
	dwc3_cache_hwparams(dwc);

	spin_lock_init(&dwc->lock);
	mutex_init(&dwc->mutex);

	pm_runसमय_set_active(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, DWC3_DEFAULT_AUTOSUSPEND_DELAY);
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err1;

	pm_runसमय_क्रमbid(dev);

	ret = dwc3_alloc_event_buffers(dwc, DWC3_EVENT_BUFFERS_SIZE);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to allocate event buffers\n");
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण

	ret = dwc3_get_dr_mode(dwc);
	अगर (ret)
		जाओ err3;

	ret = dwc3_alloc_scratch_buffers(dwc);
	अगर (ret)
		जाओ err3;

	ret = dwc3_core_init(dwc);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "failed to initialize core\n");
		जाओ err4;
	पूर्ण

	dwc3_check_params(dwc);

	ret = dwc3_core_init_mode(dwc);
	अगर (ret)
		जाओ err5;

	dwc3_debugfs_init(dwc);
	pm_runसमय_put(dev);

	वापस 0;

err5:
	dwc3_event_buffers_cleanup(dwc);

	usb_phy_shutकरोwn(dwc->usb2_phy);
	usb_phy_shutकरोwn(dwc->usb3_phy);
	phy_निकास(dwc->usb2_generic_phy);
	phy_निकास(dwc->usb3_generic_phy);

	usb_phy_set_suspend(dwc->usb2_phy, 1);
	usb_phy_set_suspend(dwc->usb3_phy, 1);
	phy_घातer_off(dwc->usb2_generic_phy);
	phy_घातer_off(dwc->usb3_generic_phy);

	dwc3_ulpi_निकास(dwc);

err4:
	dwc3_मुक्त_scratch_buffers(dwc);

err3:
	dwc3_मुक्त_event_buffers(dwc);

err2:
	pm_runसमय_allow(&pdev->dev);

err1:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

disable_clks:
	clk_bulk_disable_unprepare(dwc->num_clks, dwc->clks);
निश्चित_reset:
	reset_control_निश्चित(dwc->reset);

	अगर (dwc->usb_psy)
		घातer_supply_put(dwc->usb_psy);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3	*dwc = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);

	dwc3_core_निकास_mode(dwc);
	dwc3_debugfs_निकास(dwc);

	dwc3_core_निकास(dwc);
	dwc3_ulpi_निकास(dwc);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	dwc3_मुक्त_event_buffers(dwc);
	dwc3_मुक्त_scratch_buffers(dwc);

	अगर (dwc->usb_psy)
		घातer_supply_put(dwc->usb_psy);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dwc3_core_init_क्रम_resume(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(dwc->reset);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(dwc->num_clks, dwc->clks);
	अगर (ret)
		जाओ निश्चित_reset;

	ret = dwc3_core_init(dwc);
	अगर (ret)
		जाओ disable_clks;

	वापस 0;

disable_clks:
	clk_bulk_disable_unprepare(dwc->num_clks, dwc->clks);
निश्चित_reset:
	reset_control_निश्चित(dwc->reset);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_suspend_common(काष्ठा dwc3 *dwc, pm_message_t msg)
अणु
	अचिन्हित दीर्घ	flags;
	u32 reg;

	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		अगर (pm_runसमय_suspended(dwc->dev))
			अवरोध;
		spin_lock_irqsave(&dwc->lock, flags);
		dwc3_gadget_suspend(dwc);
		spin_unlock_irqrestore(&dwc->lock, flags);
		synchronize_irq(dwc->irq_gadget);
		dwc3_core_निकास(dwc);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_HOST:
		अगर (!PMSG_IS_AUTO(msg)) अणु
			dwc3_core_निकास(dwc);
			अवरोध;
		पूर्ण

		/* Let controller to suspend HSPHY beक्रमe PHY driver suspends */
		अगर (dwc->dis_u2_susphy_quirk ||
		    dwc->dis_enblslpm_quirk) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
			reg |=  DWC3_GUSB2PHYCFG_ENBLSLPM |
				DWC3_GUSB2PHYCFG_SUSPHY;
			dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);

			/* Give some समय क्रम USB2 PHY to suspend */
			usleep_range(5000, 6000);
		पूर्ण

		phy_pm_runसमय_put_sync(dwc->usb2_generic_phy);
		phy_pm_runसमय_put_sync(dwc->usb3_generic_phy);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		/* करो nothing during runसमय_suspend */
		अगर (PMSG_IS_AUTO(msg))
			अवरोध;

		अगर (dwc->current_otg_role == DWC3_OTG_ROLE_DEVICE) अणु
			spin_lock_irqsave(&dwc->lock, flags);
			dwc3_gadget_suspend(dwc);
			spin_unlock_irqrestore(&dwc->lock, flags);
			synchronize_irq(dwc->irq_gadget);
		पूर्ण

		dwc3_otg_निकास(dwc);
		dwc3_core_निकास(dwc);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_resume_common(काष्ठा dwc3 *dwc, pm_message_t msg)
अणु
	अचिन्हित दीर्घ	flags;
	पूर्णांक		ret;
	u32		reg;

	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		ret = dwc3_core_init_क्रम_resume(dwc);
		अगर (ret)
			वापस ret;

		dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_DEVICE);
		spin_lock_irqsave(&dwc->lock, flags);
		dwc3_gadget_resume(dwc);
		spin_unlock_irqrestore(&dwc->lock, flags);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_HOST:
		अगर (!PMSG_IS_AUTO(msg)) अणु
			ret = dwc3_core_init_क्रम_resume(dwc);
			अगर (ret)
				वापस ret;
			dwc3_set_prtcap(dwc, DWC3_GCTL_PRTCAP_HOST);
			अवरोध;
		पूर्ण
		/* Restore GUSB2PHYCFG bits that were modअगरied in suspend */
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
		अगर (dwc->dis_u2_susphy_quirk)
			reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;

		अगर (dwc->dis_enblslpm_quirk)
			reg &= ~DWC3_GUSB2PHYCFG_ENBLSLPM;

		dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);

		phy_pm_runसमय_get_sync(dwc->usb2_generic_phy);
		phy_pm_runसमय_get_sync(dwc->usb3_generic_phy);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_OTG:
		/* nothing to करो on runसमय_resume */
		अगर (PMSG_IS_AUTO(msg))
			अवरोध;

		ret = dwc3_core_init_क्रम_resume(dwc);
		अगर (ret)
			वापस ret;

		dwc3_set_prtcap(dwc, dwc->current_dr_role);

		dwc3_otg_init(dwc);
		अगर (dwc->current_otg_role == DWC3_OTG_ROLE_HOST) अणु
			dwc3_otg_host_init(dwc);
		पूर्ण अन्यथा अगर (dwc->current_otg_role == DWC3_OTG_ROLE_DEVICE) अणु
			spin_lock_irqsave(&dwc->lock, flags);
			dwc3_gadget_resume(dwc);
			spin_unlock_irqrestore(&dwc->lock, flags);
		पूर्ण

		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_runसमय_checks(काष्ठा dwc3 *dwc)
अणु
	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		अगर (dwc->connected)
			वापस -EBUSY;
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_HOST:
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3     *dwc = dev_get_drvdata(dev);
	पूर्णांक		ret;

	अगर (dwc3_runसमय_checks(dwc))
		वापस -EBUSY;

	ret = dwc3_suspend_common(dwc, PMSG_AUTO_SUSPEND);
	अगर (ret)
		वापस ret;

	device_init_wakeup(dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3     *dwc = dev_get_drvdata(dev);
	पूर्णांक		ret;

	device_init_wakeup(dev, false);

	ret = dwc3_resume_common(dwc, PMSG_AUTO_RESUME);
	अगर (ret)
		वापस ret;

	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		dwc3_gadget_process_pending_events(dwc);
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_HOST:
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा dwc3     *dwc = dev_get_drvdata(dev);

	चयन (dwc->current_dr_role) अणु
	हाल DWC3_GCTL_PRTCAP_DEVICE:
		अगर (dwc3_runसमय_checks(dwc))
			वापस -EBUSY;
		अवरोध;
	हाल DWC3_GCTL_PRTCAP_HOST:
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_स्वतःsuspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwc3_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3	*dwc = dev_get_drvdata(dev);
	पूर्णांक		ret;

	ret = dwc3_suspend_common(dwc, PMSG_SUSPEND);
	अगर (ret)
		वापस ret;

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3	*dwc = dev_get_drvdata(dev);
	पूर्णांक		ret;

	pinctrl_pm_select_शेष_state(dev);

	ret = dwc3_resume_common(dwc, PMSG_RESUME);
	अगर (ret)
		वापस ret;

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल व्योम dwc3_complete(काष्ठा device *dev)
अणु
	काष्ठा dwc3	*dwc = dev_get_drvdata(dev);
	u32		reg;

	अगर (dwc->current_dr_role == DWC3_GCTL_PRTCAP_HOST &&
			dwc->dis_split_quirk) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUCTL3);
		reg |= DWC3_GUCTL3_SPLITDISABLE;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GUCTL3, reg);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा dwc3_complete शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops dwc3_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_suspend, dwc3_resume)
	.complete = dwc3_complete,
	SET_RUNTIME_PM_OPS(dwc3_runसमय_suspend, dwc3_runसमय_resume,
			dwc3_runसमय_idle)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_dwc3_match[] = अणु
	अणु
		.compatible = "snps,dwc3"
	पूर्ण,
	अणु
		.compatible = "synopsys,dwc3"
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_dwc3_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI

#घोषणा ACPI_ID_INTEL_BSW	"808622B7"

अटल स्थिर काष्ठा acpi_device_id dwc3_acpi_match[] = अणु
	अणु ACPI_ID_INTEL_BSW, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dwc3_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver dwc3_driver = अणु
	.probe		= dwc3_probe,
	.हटाओ		= dwc3_हटाओ,
	.driver		= अणु
		.name	= "dwc3",
		.of_match_table	= of_match_ptr(of_dwc3_match),
		.acpi_match_table = ACPI_PTR(dwc3_acpi_match),
		.pm	= &dwc3_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_driver);

MODULE_ALIAS("platform:dwc3");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 DRD Controller Driver");
