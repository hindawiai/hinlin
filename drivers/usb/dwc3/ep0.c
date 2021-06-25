<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ep0.c - DesignWare USB3 DRD Controller Endpoपूर्णांक 0 Handling
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/composite.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "gadget.h"
#समावेश "io.h"

अटल व्योम __dwc3_ep0_करो_control_status(काष्ठा dwc3 *dwc, काष्ठा dwc3_ep *dep);
अटल व्योम __dwc3_ep0_करो_control_data(काष्ठा dwc3 *dwc,
		काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req);

अटल व्योम dwc3_ep0_prepare_one_trb(काष्ठा dwc3_ep *dep,
		dma_addr_t buf_dma, u32 len, u32 type, bool chain)
अणु
	काष्ठा dwc3_trb			*trb;
	काष्ठा dwc3			*dwc;

	dwc = dep->dwc;
	trb = &dwc->ep0_trb[dep->trb_enqueue];

	अगर (chain)
		dep->trb_enqueue++;

	trb->bpl = lower_32_bits(buf_dma);
	trb->bph = upper_32_bits(buf_dma);
	trb->size = len;
	trb->ctrl = type;

	trb->ctrl |= (DWC3_TRB_CTRL_HWO
			| DWC3_TRB_CTRL_ISP_IMI);

	अगर (chain)
		trb->ctrl |= DWC3_TRB_CTRL_CHN;
	अन्यथा
		trb->ctrl |= (DWC3_TRB_CTRL_IOC
				| DWC3_TRB_CTRL_LST);

	trace_dwc3_prepare_trb(dep, trb);
पूर्ण

अटल पूर्णांक dwc3_ep0_start_trans(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params params;
	काष्ठा dwc3			*dwc;
	पूर्णांक				ret;

	अगर (dep->flags & DWC3_EP_TRANSFER_STARTED)
		वापस 0;

	dwc = dep->dwc;

	स_रखो(&params, 0, माप(params));
	params.param0 = upper_32_bits(dwc->ep0_trb_addr);
	params.param1 = lower_32_bits(dwc->ep0_trb_addr);

	ret = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_STARTTRANSFER, &params);
	अगर (ret < 0)
		वापस ret;

	dwc->ep0_next_event = DWC3_EP0_COMPLETE;

	वापस 0;
पूर्ण

अटल पूर्णांक __dwc3_gadget_ep0_queue(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;

	req->request.actual	= 0;
	req->request.status	= -EINPROGRESS;
	req->epnum		= dep->number;

	list_add_tail(&req->list, &dep->pending_list);

	/*
	 * Gadget driver might not be quick enough to queue a request
	 * beक्रमe we get a Transfer Not Ready event on this endpoपूर्णांक.
	 *
	 * In that हाल, we will set DWC3_EP_PENDING_REQUEST. When that
	 * flag is set, it's telling us that as soon as Gadget queues the
	 * required request, we should kick the transfer here because the
	 * IRQ we were रुकोing क्रम is दीर्घ gone.
	 */
	अगर (dep->flags & DWC3_EP_PENDING_REQUEST) अणु
		अचिन्हित पूर्णांक direction;

		direction = !!(dep->flags & DWC3_EP0_सूची_IN);

		अगर (dwc->ep0state != EP0_DATA_PHASE) अणु
			dev_WARN(dwc->dev, "Unexpected pending request\n");
			वापस 0;
		पूर्ण

		__dwc3_ep0_करो_control_data(dwc, dwc->eps[direction], req);

		dep->flags &= ~(DWC3_EP_PENDING_REQUEST |
				DWC3_EP0_सूची_IN);

		वापस 0;
	पूर्ण

	/*
	 * In हाल gadget driver asked us to delay the STATUS phase,
	 * handle it here.
	 */
	अगर (dwc->delayed_status) अणु
		अचिन्हित पूर्णांक direction;

		direction = !dwc->ep0_expect_in;
		dwc->delayed_status = false;
		usb_gadget_set_state(dwc->gadget, USB_STATE_CONFIGURED);

		अगर (dwc->ep0state == EP0_STATUS_PHASE)
			__dwc3_ep0_करो_control_status(dwc, dwc->eps[direction]);

		वापस 0;
	पूर्ण

	/*
	 * Unक्रमtunately we have uncovered a limitation wrt the Data Phase.
	 *
	 * Section 9.4 says we can रुको क्रम the XferNotReady(DATA) event to
	 * come beक्रमe issueing Start Transfer command, but अगर we करो, we will
	 * miss situations where the host starts another SETUP phase instead of
	 * the DATA phase.  Such हालs happen at least on TD.7.6 of the Link
	 * Layer Compliance Suite.
	 *
	 * The problem surfaces due to the fact that in हाल of back-to-back
	 * SETUP packets there will be no XferNotReady(DATA) generated and we
	 * will be stuck रुकोing क्रम XferNotReady(DATA) क्रमever.
	 *
	 * By looking at tables 9-13 and 9-14 of the Databook, we can see that
	 * it tells us to start Data Phase right away. It also mentions that अगर
	 * we receive a SETUP phase instead of the DATA phase, core will issue
	 * XferComplete क्रम the DATA phase, beक्रमe actually initiating it in
	 * the wire, with the TRB's status set to "SETUP_PENDING". Such status
	 * can only be used to prपूर्णांक some debugging logs, as the core expects
	 * us to go through to the STATUS phase and start a CONTROL_STATUS TRB,
	 * just so it completes right away, without transferring anything and,
	 * only then, we can go back to the SETUP phase.
	 *
	 * Because of this scenario, SNPS decided to change the programming
	 * model of control transfers and support on-demand transfers only क्रम
	 * the STATUS phase. To fix the issue we have now, we will always रुको
	 * क्रम gadget driver to queue the DATA phase's काष्ठा usb_request, then
	 * start it right away.
	 *
	 * If we're actually in a 2-stage transfer, we will रुको क्रम
	 * XferNotReady(STATUS).
	 */
	अगर (dwc->three_stage_setup) अणु
		अचिन्हित पूर्णांक direction;

		direction = dwc->ep0_expect_in;
		dwc->ep0state = EP0_DATA_PHASE;

		__dwc3_ep0_करो_control_data(dwc, dwc->eps[direction], req);

		dep->flags &= ~DWC3_EP0_सूची_IN;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dwc3_gadget_ep0_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *request,
		gfp_t gfp_flags)
अणु
	काष्ठा dwc3_request		*req = to_dwc3_request(request);
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;

	अचिन्हित दीर्घ			flags;

	पूर्णांक				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	अगर (!dep->endpoपूर्णांक.desc || !dwc->pullups_connected) अणु
		dev_err(dwc->dev, "%s: can't queue to disabled endpoint\n",
				dep->name);
		ret = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	/* we share one TRB क्रम ep0/1 */
	अगर (!list_empty(&dep->pending_list)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = __dwc3_gadget_ep0_queue(dep, req);

out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम dwc3_ep0_stall_and_restart(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_ep		*dep;

	/* reinitialize physical ep1 */
	dep = dwc->eps[1];
	dep->flags = DWC3_EP_ENABLED;

	/* stall is always issued on EP0 */
	dep = dwc->eps[0];
	__dwc3_gadget_ep_set_halt(dep, 1, false);
	dep->flags = DWC3_EP_ENABLED;
	dwc->delayed_status = false;

	अगर (!list_empty(&dep->pending_list)) अणु
		काष्ठा dwc3_request	*req;

		req = next_request(&dep->pending_list);
		dwc3_gadget_giveback(dep, req, -ECONNRESET);
	पूर्ण

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_start(dwc);
पूर्ण

पूर्णांक __dwc3_gadget_ep0_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;

	dwc3_ep0_stall_and_restart(dwc);

	वापस 0;
पूर्ण

पूर्णांक dwc3_gadget_ep0_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_ep0_set_halt(ep, value);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

व्योम dwc3_ep0_out_start(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_ep			*dep;
	पूर्णांक				ret;

	complete(&dwc->ep0_in_setup);

	dep = dwc->eps[0];
	dwc3_ep0_prepare_one_trb(dep, dwc->ep0_trb_addr, 8,
			DWC3_TRBCTL_CONTROL_SETUP, false);
	ret = dwc3_ep0_start_trans(dep);
	WARN_ON(ret < 0);
पूर्ण

अटल काष्ठा dwc3_ep *dwc3_wIndex_to_dep(काष्ठा dwc3 *dwc, __le16 wIndex_le)
अणु
	काष्ठा dwc3_ep		*dep;
	u32			windex = le16_to_cpu(wIndex_le);
	u32			epnum;

	epnum = (windex & USB_ENDPOINT_NUMBER_MASK) << 1;
	अगर ((windex & USB_ENDPOINT_सूची_MASK) == USB_सूची_IN)
		epnum |= 1;

	dep = dwc->eps[epnum];
	अगर (dep == शून्य)
		वापस शून्य;

	अगर (dep->flags & DWC3_EP_ENABLED)
		वापस dep;

	वापस शून्य;
पूर्ण

अटल व्योम dwc3_ep0_status_cmpl(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
पूर्ण
/*
 * ch 9.4.5
 */
अटल पूर्णांक dwc3_ep0_handle_status(काष्ठा dwc3 *dwc,
		काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा dwc3_ep		*dep;
	u32			recip;
	u32			value;
	u32			reg;
	u16			usb_status = 0;
	__le16			*response_pkt;

	/* We करोn't support PTM_STATUS */
	value = le16_to_cpu(ctrl->wValue);
	अगर (value != 0)
		वापस -EINVAL;

	recip = ctrl->bRequestType & USB_RECIP_MASK;
	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		/*
		 * LTM will be set once we know how to set this in HW.
		 */
		usb_status |= dwc->gadget->is_selfघातered;

		अगर ((dwc->speed == DWC3_DSTS_SUPERSPEED) ||
		    (dwc->speed == DWC3_DSTS_SUPERSPEED_PLUS)) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
			अगर (reg & DWC3_DCTL_INITU1ENA)
				usb_status |= 1 << USB_DEV_STAT_U1_ENABLED;
			अगर (reg & DWC3_DCTL_INITU2ENA)
				usb_status |= 1 << USB_DEV_STAT_U2_ENABLED;
		पूर्ण

		अवरोध;

	हाल USB_RECIP_INTERFACE:
		/*
		 * Function Remote Wake Capable	D0
		 * Function Remote Wakeup	D1
		 */
		अवरोध;

	हाल USB_RECIP_ENDPOINT:
		dep = dwc3_wIndex_to_dep(dwc, ctrl->wIndex);
		अगर (!dep)
			वापस -EINVAL;

		अगर (dep->flags & DWC3_EP_STALL)
			usb_status = 1 << USB_ENDPOINT_HALT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	response_pkt = (__le16 *) dwc->setup_buf;
	*response_pkt = cpu_to_le16(usb_status);

	dep = dwc->eps[0];
	dwc->ep0_usb_req.dep = dep;
	dwc->ep0_usb_req.request.length = माप(*response_pkt);
	dwc->ep0_usb_req.request.buf = dwc->setup_buf;
	dwc->ep0_usb_req.request.complete = dwc3_ep0_status_cmpl;

	वापस __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_req);
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_u1(काष्ठा dwc3 *dwc, क्रमागत usb_device_state state,
		पूर्णांक set)
अणु
	u32 reg;

	अगर (state != USB_STATE_CONFIGURED)
		वापस -EINVAL;
	अगर ((dwc->speed != DWC3_DSTS_SUPERSPEED) &&
			(dwc->speed != DWC3_DSTS_SUPERSPEED_PLUS))
		वापस -EINVAL;
	अगर (set && dwc->dis_u1_entry_quirk)
		वापस -EINVAL;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	अगर (set)
		reg |= DWC3_DCTL_INITU1ENA;
	अन्यथा
		reg &= ~DWC3_DCTL_INITU1ENA;
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_u2(काष्ठा dwc3 *dwc, क्रमागत usb_device_state state,
		पूर्णांक set)
अणु
	u32 reg;


	अगर (state != USB_STATE_CONFIGURED)
		वापस -EINVAL;
	अगर ((dwc->speed != DWC3_DSTS_SUPERSPEED) &&
			(dwc->speed != DWC3_DSTS_SUPERSPEED_PLUS))
		वापस -EINVAL;
	अगर (set && dwc->dis_u2_entry_quirk)
		वापस -EINVAL;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	अगर (set)
		reg |= DWC3_DCTL_INITU2ENA;
	अन्यथा
		reg &= ~DWC3_DCTL_INITU2ENA;
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_test(काष्ठा dwc3 *dwc, क्रमागत usb_device_state state,
		u32 wIndex, पूर्णांक set)
अणु
	अगर ((wIndex & 0xff) != 0)
		वापस -EINVAL;
	अगर (!set)
		वापस -EINVAL;

	चयन (wIndex >> 8) अणु
	हाल USB_TEST_J:
	हाल USB_TEST_K:
	हाल USB_TEST_SE0_NAK:
	हाल USB_TEST_PACKET:
	हाल USB_TEST_FORCE_ENABLE:
		dwc->test_mode_nr = wIndex >> 8;
		dwc->test_mode = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_device(काष्ठा dwc3 *dwc,
		काष्ठा usb_ctrlrequest *ctrl, पूर्णांक set)
अणु
	क्रमागत usb_device_state	state;
	u32			wValue;
	u32			wIndex;
	पूर्णांक			ret = 0;

	wValue = le16_to_cpu(ctrl->wValue);
	wIndex = le16_to_cpu(ctrl->wIndex);
	state = dwc->gadget->state;

	चयन (wValue) अणु
	हाल USB_DEVICE_REMOTE_WAKEUP:
		अवरोध;
	/*
	 * 9.4.1 says only only क्रम SS, in AddressState only क्रम
	 * शेष control pipe
	 */
	हाल USB_DEVICE_U1_ENABLE:
		ret = dwc3_ep0_handle_u1(dwc, state, set);
		अवरोध;
	हाल USB_DEVICE_U2_ENABLE:
		ret = dwc3_ep0_handle_u2(dwc, state, set);
		अवरोध;
	हाल USB_DEVICE_LTM_ENABLE:
		ret = -EINVAL;
		अवरोध;
	हाल USB_DEVICE_TEST_MODE:
		ret = dwc3_ep0_handle_test(dwc, state, wIndex, set);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_पूर्णांकf(काष्ठा dwc3 *dwc,
		काष्ठा usb_ctrlrequest *ctrl, पूर्णांक set)
अणु
	u32			wValue;
	पूर्णांक			ret = 0;

	wValue = le16_to_cpu(ctrl->wValue);

	चयन (wValue) अणु
	हाल USB_INTRF_FUNC_SUSPEND:
		/*
		 * REVISIT: Ideally we would enable some low घातer mode here,
		 * however it's unclear what we should be करोing here.
		 *
		 * For now, we're not करोing anything, just making sure we वापस
		 * 0 so USB Command Verअगरier tests pass without any errors.
		 */
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_endpoपूर्णांक(काष्ठा dwc3 *dwc,
		काष्ठा usb_ctrlrequest *ctrl, पूर्णांक set)
अणु
	काष्ठा dwc3_ep		*dep;
	u32			wValue;
	पूर्णांक			ret;

	wValue = le16_to_cpu(ctrl->wValue);

	चयन (wValue) अणु
	हाल USB_ENDPOINT_HALT:
		dep = dwc3_wIndex_to_dep(dwc, ctrl->wIndex);
		अगर (!dep)
			वापस -EINVAL;

		अगर (set == 0 && (dep->flags & DWC3_EP_WEDGE))
			अवरोध;

		ret = __dwc3_gadget_ep_set_halt(dep, set, true);
		अगर (ret)
			वापस -EINVAL;

		/* ClearFeature(Halt) may need delayed status */
		अगर (!set && (dep->flags & DWC3_EP_END_TRANSFER_PENDING))
			वापस USB_GADGET_DELAYED_STATUS;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep0_handle_feature(काष्ठा dwc3 *dwc,
		काष्ठा usb_ctrlrequest *ctrl, पूर्णांक set)
अणु
	u32			recip;
	पूर्णांक			ret;

	recip = ctrl->bRequestType & USB_RECIP_MASK;

	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		ret = dwc3_ep0_handle_device(dwc, ctrl, set);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		ret = dwc3_ep0_handle_पूर्णांकf(dwc, ctrl, set);
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ret = dwc3_ep0_handle_endpoपूर्णांक(dwc, ctrl, set);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_ep0_set_address(काष्ठा dwc3 *dwc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	क्रमागत usb_device_state state = dwc->gadget->state;
	u32 addr;
	u32 reg;

	addr = le16_to_cpu(ctrl->wValue);
	अगर (addr > 127) अणु
		dev_err(dwc->dev, "invalid device address %d\n", addr);
		वापस -EINVAL;
	पूर्ण

	अगर (state == USB_STATE_CONFIGURED) अणु
		dev_err(dwc->dev, "can't SetAddress() from Configured State\n");
		वापस -EINVAL;
	पूर्ण

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
	reg &= ~(DWC3_DCFG_DEVADDR_MASK);
	reg |= DWC3_DCFG_DEVADDR(addr);
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);

	अगर (addr)
		usb_gadget_set_state(dwc->gadget, USB_STATE_ADDRESS);
	अन्यथा
		usb_gadget_set_state(dwc->gadget, USB_STATE_DEFAULT);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep0_delegate_req(काष्ठा dwc3 *dwc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret;

	spin_unlock(&dwc->lock);
	ret = dwc->gadget_driver->setup(dwc->gadget, ctrl);
	spin_lock(&dwc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_ep0_set_config(काष्ठा dwc3 *dwc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	क्रमागत usb_device_state state = dwc->gadget->state;
	u32 cfg;
	पूर्णांक ret;
	u32 reg;

	cfg = le16_to_cpu(ctrl->wValue);

	चयन (state) अणु
	हाल USB_STATE_DEFAULT:
		वापस -EINVAL;

	हाल USB_STATE_ADDRESS:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		/* अगर the cfg matches and the cfg is non zero */
		अगर (cfg && (!ret || (ret == USB_GADGET_DELAYED_STATUS))) अणु

			/*
			 * only change state अगर set_config has alपढ़ोy
			 * been processed. If gadget driver वापसs
			 * USB_GADGET_DELAYED_STATUS, we will रुको
			 * to change the state on the next usb_ep_queue()
			 */
			अगर (ret == 0)
				usb_gadget_set_state(dwc->gadget,
						USB_STATE_CONFIGURED);

			/*
			 * Enable transition to U1/U2 state when
			 * nothing is pending from application.
			 */
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
			अगर (!dwc->dis_u1_entry_quirk)
				reg |= DWC3_DCTL_ACCEPTU1ENA;
			अगर (!dwc->dis_u2_entry_quirk)
				reg |= DWC3_DCTL_ACCEPTU2ENA;
			dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);
		पूर्ण
		अवरोध;

	हाल USB_STATE_CONFIGURED:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		अगर (!cfg && !ret)
			usb_gadget_set_state(dwc->gadget,
					USB_STATE_ADDRESS);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम dwc3_ep0_set_sel_cmpl(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा dwc3_ep	*dep = to_dwc3_ep(ep);
	काष्ठा dwc3	*dwc = dep->dwc;

	u32		param = 0;
	u32		reg;

	काष्ठा timing अणु
		u8	u1sel;
		u8	u1pel;
		__le16	u2sel;
		__le16	u2pel;
	पूर्ण __packed timing;

	पूर्णांक		ret;

	स_नकल(&timing, req->buf, माप(timing));

	dwc->u1sel = timing.u1sel;
	dwc->u1pel = timing.u1pel;
	dwc->u2sel = le16_to_cpu(timing.u2sel);
	dwc->u2pel = le16_to_cpu(timing.u2pel);

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	अगर (reg & DWC3_DCTL_INITU2ENA)
		param = dwc->u2pel;
	अगर (reg & DWC3_DCTL_INITU1ENA)
		param = dwc->u1pel;

	/*
	 * According to Synopsys Databook, अगर parameter is
	 * greater than 125, a value of zero should be
	 * programmed in the रेजिस्टर.
	 */
	अगर (param > 125)
		param = 0;

	/* now that we have the समय, issue DGCMD Set Sel */
	ret = dwc3_send_gadget_generic_command(dwc,
			DWC3_DGCMD_SET_PERIODIC_PAR, param);
	WARN_ON(ret < 0);
पूर्ण

अटल पूर्णांक dwc3_ep0_set_sel(काष्ठा dwc3 *dwc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा dwc3_ep	*dep;
	क्रमागत usb_device_state state = dwc->gadget->state;
	u16		wLength;

	अगर (state == USB_STATE_DEFAULT)
		वापस -EINVAL;

	wLength = le16_to_cpu(ctrl->wLength);

	अगर (wLength != 6) अणु
		dev_err(dwc->dev, "Set SEL should be 6 bytes, got %d\n",
				wLength);
		वापस -EINVAL;
	पूर्ण

	/*
	 * To handle Set SEL we need to receive 6 bytes from Host. So let's
	 * queue a usb_request क्रम 6 bytes.
	 *
	 * Remember, though, this controller can't handle non-wMaxPacketSize
	 * aligned transfers on the OUT direction, so we queue a request क्रम
	 * wMaxPacketSize instead.
	 */
	dep = dwc->eps[0];
	dwc->ep0_usb_req.dep = dep;
	dwc->ep0_usb_req.request.length = dep->endpoपूर्णांक.maxpacket;
	dwc->ep0_usb_req.request.buf = dwc->setup_buf;
	dwc->ep0_usb_req.request.complete = dwc3_ep0_set_sel_cmpl;

	वापस __dwc3_gadget_ep0_queue(dep, &dwc->ep0_usb_req);
पूर्ण

अटल पूर्णांक dwc3_ep0_set_isoch_delay(काष्ठा dwc3 *dwc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u16		wLength;
	u16		wValue;
	u16		wIndex;

	wValue = le16_to_cpu(ctrl->wValue);
	wLength = le16_to_cpu(ctrl->wLength);
	wIndex = le16_to_cpu(ctrl->wIndex);

	अगर (wIndex || wLength)
		वापस -EINVAL;

	dwc->gadget->isoch_delay = wValue;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_ep0_std_request(काष्ठा dwc3 *dwc, काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret;

	चयन (ctrl->bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		ret = dwc3_ep0_handle_status(dwc, ctrl);
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
		ret = dwc3_ep0_handle_feature(dwc, ctrl, 0);
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		ret = dwc3_ep0_handle_feature(dwc, ctrl, 1);
		अवरोध;
	हाल USB_REQ_SET_ADDRESS:
		ret = dwc3_ep0_set_address(dwc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_CONFIGURATION:
		ret = dwc3_ep0_set_config(dwc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_SEL:
		ret = dwc3_ep0_set_sel(dwc, ctrl);
		अवरोध;
	हाल USB_REQ_SET_ISOCH_DELAY:
		ret = dwc3_ep0_set_isoch_delay(dwc, ctrl);
		अवरोध;
	शेष:
		ret = dwc3_ep0_delegate_req(dwc, ctrl);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dwc3_ep0_inspect_setup(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा usb_ctrlrequest *ctrl = (व्योम *) dwc->ep0_trb;
	पूर्णांक ret = -EINVAL;
	u32 len;

	अगर (!dwc->gadget_driver)
		जाओ out;

	trace_dwc3_ctrl_req(ctrl);

	len = le16_to_cpu(ctrl->wLength);
	अगर (!len) अणु
		dwc->three_stage_setup = false;
		dwc->ep0_expect_in = false;
		dwc->ep0_next_event = DWC3_EP0_NRDY_STATUS;
	पूर्ण अन्यथा अणु
		dwc->three_stage_setup = true;
		dwc->ep0_expect_in = !!(ctrl->bRequestType & USB_सूची_IN);
		dwc->ep0_next_event = DWC3_EP0_NRDY_DATA;
	पूर्ण

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		ret = dwc3_ep0_std_request(dwc, ctrl);
	अन्यथा
		ret = dwc3_ep0_delegate_req(dwc, ctrl);

	अगर (ret == USB_GADGET_DELAYED_STATUS)
		dwc->delayed_status = true;

out:
	अगर (ret < 0)
		dwc3_ep0_stall_and_restart(dwc);
पूर्ण

अटल व्योम dwc3_ep0_complete_data(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3_request	*r;
	काष्ठा usb_request	*ur;
	काष्ठा dwc3_trb		*trb;
	काष्ठा dwc3_ep		*ep0;
	u32			transferred = 0;
	u32			status;
	u32			length;
	u8			epnum;

	epnum = event->endpoपूर्णांक_number;
	ep0 = dwc->eps[0];

	dwc->ep0_next_event = DWC3_EP0_NRDY_STATUS;
	trb = dwc->ep0_trb;
	trace_dwc3_complete_trb(ep0, trb);

	r = next_request(&ep0->pending_list);
	अगर (!r)
		वापस;

	status = DWC3_TRB_SIZE_TRBSTS(trb->size);
	अगर (status == DWC3_TRBSTS_SETUP_PENDING) अणु
		dwc->setup_packet_pending = true;
		अगर (r)
			dwc3_gadget_giveback(ep0, r, -ECONNRESET);

		वापस;
	पूर्ण

	ur = &r->request;

	length = trb->size & DWC3_TRB_SIZE_MASK;
	transferred = ur->length - length;
	ur->actual += transferred;

	अगर ((IS_ALIGNED(ur->length, ep0->endpoपूर्णांक.maxpacket) &&
	     ur->length && ur->zero) || dwc->ep0_bounced) अणु
		trb++;
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;
		trace_dwc3_complete_trb(ep0, trb);

		अगर (r->direction)
			dwc->eps[1]->trb_enqueue = 0;
		अन्यथा
			dwc->eps[0]->trb_enqueue = 0;

		dwc->ep0_bounced = false;
	पूर्ण

	अगर ((epnum & 1) && ur->actual < ur->length)
		dwc3_ep0_stall_and_restart(dwc);
	अन्यथा
		dwc3_gadget_giveback(ep0, r, 0);
पूर्ण

अटल व्योम dwc3_ep0_complete_status(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3_request	*r;
	काष्ठा dwc3_ep		*dep;
	काष्ठा dwc3_trb		*trb;
	u32			status;

	dep = dwc->eps[0];
	trb = dwc->ep0_trb;

	trace_dwc3_complete_trb(dep, trb);

	अगर (!list_empty(&dep->pending_list)) अणु
		r = next_request(&dep->pending_list);

		dwc3_gadget_giveback(dep, r, 0);
	पूर्ण

	अगर (dwc->test_mode) अणु
		पूर्णांक ret;

		ret = dwc3_gadget_set_test_mode(dwc, dwc->test_mode_nr);
		अगर (ret < 0) अणु
			dev_err(dwc->dev, "invalid test #%d\n",
					dwc->test_mode_nr);
			dwc3_ep0_stall_and_restart(dwc);
			वापस;
		पूर्ण
	पूर्ण

	status = DWC3_TRB_SIZE_TRBSTS(trb->size);
	अगर (status == DWC3_TRBSTS_SETUP_PENDING)
		dwc->setup_packet_pending = true;

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_start(dwc);
पूर्ण

अटल व्योम dwc3_ep0_xfer_complete(काष्ठा dwc3 *dwc,
			स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3_ep		*dep = dwc->eps[event->endpoपूर्णांक_number];

	dep->flags &= ~DWC3_EP_TRANSFER_STARTED;
	dep->resource_index = 0;
	dwc->setup_packet_pending = false;

	चयन (dwc->ep0state) अणु
	हाल EP0_SETUP_PHASE:
		dwc3_ep0_inspect_setup(dwc, event);
		अवरोध;

	हाल EP0_DATA_PHASE:
		dwc3_ep0_complete_data(dwc, event);
		अवरोध;

	हाल EP0_STATUS_PHASE:
		dwc3_ep0_complete_status(dwc, event);
		अवरोध;
	शेष:
		WARN(true, "UNKNOWN ep0state %d\n", dwc->ep0state);
	पूर्ण
पूर्ण

अटल व्योम __dwc3_ep0_करो_control_data(काष्ठा dwc3 *dwc,
		काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req)
अणु
	अचिन्हित पूर्णांक		trb_length = 0;
	पूर्णांक			ret;

	req->direction = !!dep->number;

	अगर (req->request.length == 0) अणु
		अगर (!req->direction)
			trb_length = dep->endpoपूर्णांक.maxpacket;

		dwc3_ep0_prepare_one_trb(dep, dwc->bounce_addr, trb_length,
				DWC3_TRBCTL_CONTROL_DATA, false);
		ret = dwc3_ep0_start_trans(dep);
	पूर्ण अन्यथा अगर (!IS_ALIGNED(req->request.length, dep->endpoपूर्णांक.maxpacket)
			&& (dep->number == 0)) अणु
		u32	maxpacket;
		u32	rem;

		ret = usb_gadget_map_request_by_dev(dwc->sysdev,
				&req->request, dep->number);
		अगर (ret)
			वापस;

		maxpacket = dep->endpoपूर्णांक.maxpacket;
		rem = req->request.length % maxpacket;
		dwc->ep0_bounced = true;

		/* prepare normal TRB */
		dwc3_ep0_prepare_one_trb(dep, req->request.dma,
					 req->request.length,
					 DWC3_TRBCTL_CONTROL_DATA,
					 true);

		req->trb = &dwc->ep0_trb[dep->trb_enqueue - 1];

		/* Now prepare one extra TRB to align transfer size */
		dwc3_ep0_prepare_one_trb(dep, dwc->bounce_addr,
					 maxpacket - rem,
					 DWC3_TRBCTL_CONTROL_DATA,
					 false);
		ret = dwc3_ep0_start_trans(dep);
	पूर्ण अन्यथा अगर (IS_ALIGNED(req->request.length, dep->endpoपूर्णांक.maxpacket) &&
		   req->request.length && req->request.zero) अणु

		ret = usb_gadget_map_request_by_dev(dwc->sysdev,
				&req->request, dep->number);
		अगर (ret)
			वापस;

		/* prepare normal TRB */
		dwc3_ep0_prepare_one_trb(dep, req->request.dma,
					 req->request.length,
					 DWC3_TRBCTL_CONTROL_DATA,
					 true);

		req->trb = &dwc->ep0_trb[dep->trb_enqueue - 1];

		अगर (!req->direction)
			trb_length = dep->endpoपूर्णांक.maxpacket;

		/* Now prepare one extra TRB to align transfer size */
		dwc3_ep0_prepare_one_trb(dep, dwc->bounce_addr,
					 trb_length, DWC3_TRBCTL_CONTROL_DATA,
					 false);
		ret = dwc3_ep0_start_trans(dep);
	पूर्ण अन्यथा अणु
		ret = usb_gadget_map_request_by_dev(dwc->sysdev,
				&req->request, dep->number);
		अगर (ret)
			वापस;

		dwc3_ep0_prepare_one_trb(dep, req->request.dma,
				req->request.length, DWC3_TRBCTL_CONTROL_DATA,
				false);

		req->trb = &dwc->ep0_trb[dep->trb_enqueue];

		ret = dwc3_ep0_start_trans(dep);
	पूर्ण

	WARN_ON(ret < 0);
पूर्ण

अटल पूर्णांक dwc3_ep0_start_control_status(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;
	u32			type;

	type = dwc->three_stage_setup ? DWC3_TRBCTL_CONTROL_STATUS3
		: DWC3_TRBCTL_CONTROL_STATUS2;

	dwc3_ep0_prepare_one_trb(dep, dwc->ep0_trb_addr, 0, type, false);
	वापस dwc3_ep0_start_trans(dep);
पूर्ण

अटल व्योम __dwc3_ep0_करो_control_status(काष्ठा dwc3 *dwc, काष्ठा dwc3_ep *dep)
अणु
	WARN_ON(dwc3_ep0_start_control_status(dep));
पूर्ण

अटल व्योम dwc3_ep0_करो_control_status(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3_ep		*dep = dwc->eps[event->endpoपूर्णांक_number];

	__dwc3_ep0_करो_control_status(dwc, dep);
पूर्ण

व्योम dwc3_ep0_send_delayed_status(काष्ठा dwc3 *dwc)
अणु
	अचिन्हित पूर्णांक direction = !dwc->ep0_expect_in;

	dwc->delayed_status = false;

	अगर (dwc->ep0state != EP0_STATUS_PHASE)
		वापस;

	__dwc3_ep0_करो_control_status(dwc, dwc->eps[direction]);
पूर्ण

अटल व्योम dwc3_ep0_end_control_data(काष्ठा dwc3 *dwc, काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params params;
	u32			cmd;
	पूर्णांक			ret;

	अगर (!dep->resource_index)
		वापस;

	cmd = DWC3_DEPCMD_ENDTRANSFER;
	cmd |= DWC3_DEPCMD_CMDIOC;
	cmd |= DWC3_DEPCMD_PARAM(dep->resource_index);
	स_रखो(&params, 0, माप(params));
	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	WARN_ON_ONCE(ret);
	dep->resource_index = 0;
पूर्ण

अटल व्योम dwc3_ep0_xfernotपढ़ोy(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	चयन (event->status) अणु
	हाल DEPEVT_STATUS_CONTROL_DATA:
		/*
		 * We alपढ़ोy have a DATA transfer in the controller's cache,
		 * अगर we receive a XferNotReady(DATA) we will ignore it, unless
		 * it's क्रम the wrong direction.
		 *
		 * In that हाल, we must issue END_TRANSFER command to the Data
		 * Phase we alपढ़ोy have started and issue SetStall on the
		 * control endpoपूर्णांक.
		 */
		अगर (dwc->ep0_expect_in != event->endpoपूर्णांक_number) अणु
			काष्ठा dwc3_ep	*dep = dwc->eps[dwc->ep0_expect_in];

			dev_err(dwc->dev, "unexpected direction for Data Phase\n");
			dwc3_ep0_end_control_data(dwc, dep);
			dwc3_ep0_stall_and_restart(dwc);
			वापस;
		पूर्ण

		अवरोध;

	हाल DEPEVT_STATUS_CONTROL_STATUS:
		अगर (dwc->ep0_next_event != DWC3_EP0_NRDY_STATUS)
			वापस;

		dwc->ep0state = EP0_STATUS_PHASE;

		अगर (dwc->delayed_status) अणु
			काष्ठा dwc3_ep *dep = dwc->eps[0];

			WARN_ON_ONCE(event->endpoपूर्णांक_number != 1);
			/*
			 * We should handle the delay STATUS phase here अगर the
			 * request क्रम handling delay STATUS has been queued
			 * पूर्णांकo the list.
			 */
			अगर (!list_empty(&dep->pending_list)) अणु
				dwc->delayed_status = false;
				usb_gadget_set_state(dwc->gadget,
						     USB_STATE_CONFIGURED);
				dwc3_ep0_करो_control_status(dwc, event);
			पूर्ण

			वापस;
		पूर्ण

		dwc3_ep0_करो_control_status(dwc, event);
	पूर्ण
पूर्ण

व्योम dwc3_ep0_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3_ep	*dep = dwc->eps[event->endpoपूर्णांक_number];
	u8		cmd;

	चयन (event->endpoपूर्णांक_event) अणु
	हाल DWC3_DEPEVT_XFERCOMPLETE:
		dwc3_ep0_xfer_complete(dwc, event);
		अवरोध;

	हाल DWC3_DEPEVT_XFERNOTREADY:
		dwc3_ep0_xfernotपढ़ोy(dwc, event);
		अवरोध;

	हाल DWC3_DEPEVT_XFERINPROGRESS:
	हाल DWC3_DEPEVT_RXTXFIFOEVT:
	हाल DWC3_DEPEVT_STREAMEVT:
		अवरोध;
	हाल DWC3_DEPEVT_EPCMDCMPLT:
		cmd = DEPEVT_PARAMETER_CMD(event->parameters);

		अगर (cmd == DWC3_DEPCMD_ENDTRANSFER) अणु
			dep->flags &= ~DWC3_EP_END_TRANSFER_PENDING;
			dep->flags &= ~DWC3_EP_TRANSFER_STARTED;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
