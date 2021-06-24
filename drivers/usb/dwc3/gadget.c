<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * gadget.c - DesignWare USB3 DRD Controller Gadget Framework Link
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
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

#समावेश "debug.h"
#समावेश "core.h"
#समावेश "gadget.h"
#समावेश "io.h"

#घोषणा DWC3_ALIGN_FRAME(d, n)	(((d)->frame_number + ((d)->पूर्णांकerval * (n))) \
					& ~((d)->पूर्णांकerval - 1))

/**
 * dwc3_gadget_set_test_mode - enables usb2 test modes
 * @dwc: poपूर्णांकer to our context काष्ठाure
 * @mode: the mode to set (J, K SE0 NAK, Force Enable)
 *
 * Caller should take care of locking. This function will वापस 0 on
 * success or -EINVAL अगर wrong Test Selector is passed.
 */
पूर्णांक dwc3_gadget_set_test_mode(काष्ठा dwc3 *dwc, पूर्णांक mode)
अणु
	u32		reg;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_TSTCTRL_MASK;

	चयन (mode) अणु
	हाल USB_TEST_J:
	हाल USB_TEST_K:
	हाल USB_TEST_SE0_NAK:
	हाल USB_TEST_PACKET:
	हाल USB_TEST_FORCE_ENABLE:
		reg |= mode << 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);

	वापस 0;
पूर्ण

/**
 * dwc3_gadget_get_link_state - माला_लो current state of usb link
 * @dwc: poपूर्णांकer to our context काष्ठाure
 *
 * Caller should take care of locking. This function will
 * वापस the link state on success (>= 0) or -ETIMEDOUT.
 */
पूर्णांक dwc3_gadget_get_link_state(काष्ठा dwc3 *dwc)
अणु
	u32		reg;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);

	वापस DWC3_DSTS_USBLNKST(reg);
पूर्ण

/**
 * dwc3_gadget_set_link_state - sets usb link to a particular state
 * @dwc: poपूर्णांकer to our context काष्ठाure
 * @state: the state to put link पूर्णांकo
 *
 * Caller should take care of locking. This function will
 * वापस 0 on success or -ETIMEDOUT.
 */
पूर्णांक dwc3_gadget_set_link_state(काष्ठा dwc3 *dwc, क्रमागत dwc3_link_state state)
अणु
	पूर्णांक		retries = 10000;
	u32		reg;

	/*
	 * Wait until device controller is पढ़ोy. Only applies to 1.94a and
	 * later RTL.
	 */
	अगर (!DWC3_VER_IS_PRIOR(DWC3, 194A)) अणु
		जबतक (--retries) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);
			अगर (reg & DWC3_DSTS_DCNRD)
				udelay(5);
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (retries <= 0)
			वापस -ETIMEDOUT;
	पूर्ण

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_ULSTCHNGREQ_MASK;

	/* set no action beक्रमe sending new link state change */
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);

	/* set requested state */
	reg |= DWC3_DCTL_ULSTCHNGREQ(state);
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);

	/*
	 * The following code is racy when called from dwc3_gadget_wakeup,
	 * and is not needed, at least on newer versions
	 */
	अगर (!DWC3_VER_IS_PRIOR(DWC3, 194A))
		वापस 0;

	/* रुको क्रम a change in DSTS */
	retries = 10000;
	जबतक (--retries) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);

		अगर (DWC3_DSTS_USBLNKST(reg) == state)
			वापस 0;

		udelay(5);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/**
 * dwc3_ep_inc_trb - increment a trb index.
 * @index: Poपूर्णांकer to the TRB index to increment.
 *
 * The index should never poपूर्णांक to the link TRB. After incrementing,
 * अगर it is poपूर्णांक to the link TRB, wrap around to the beginning. The
 * link TRB is always at the last TRB entry.
 */
अटल व्योम dwc3_ep_inc_trb(u8 *index)
अणु
	(*index)++;
	अगर (*index == (DWC3_TRB_NUM - 1))
		*index = 0;
पूर्ण

/**
 * dwc3_ep_inc_enq - increment endpoपूर्णांक's enqueue poपूर्णांकer
 * @dep: The endpoपूर्णांक whose enqueue poपूर्णांकer we're incrementing
 */
अटल व्योम dwc3_ep_inc_enq(काष्ठा dwc3_ep *dep)
अणु
	dwc3_ep_inc_trb(&dep->trb_enqueue);
पूर्ण

/**
 * dwc3_ep_inc_deq - increment endpoपूर्णांक's dequeue poपूर्णांकer
 * @dep: The endpoपूर्णांक whose enqueue poपूर्णांकer we're incrementing
 */
अटल व्योम dwc3_ep_inc_deq(काष्ठा dwc3_ep *dep)
अणु
	dwc3_ep_inc_trb(&dep->trb_dequeue);
पूर्ण

अटल व्योम dwc3_gadget_del_and_unmap_request(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req, पूर्णांक status)
अणु
	काष्ठा dwc3			*dwc = dep->dwc;

	list_del(&req->list);
	req->reमुख्यing = 0;
	req->needs_extra_trb = false;

	अगर (req->request.status == -EINPROGRESS)
		req->request.status = status;

	अगर (req->trb)
		usb_gadget_unmap_request_by_dev(dwc->sysdev,
				&req->request, req->direction);

	req->trb = शून्य;
	trace_dwc3_gadget_giveback(req);

	अगर (dep->number > 1)
		pm_runसमय_put(dwc->dev);
पूर्ण

/**
 * dwc3_gadget_giveback - call काष्ठा usb_request's ->complete callback
 * @dep: The endpoपूर्णांक to whom the request beदीर्घs to
 * @req: The request we're giving back
 * @status: completion code क्रम the request
 *
 * Must be called with controller's lock held and पूर्णांकerrupts disabled. This
 * function will unmap @req and call its ->complete() callback to notअगरy upper
 * layers that it has completed.
 */
व्योम dwc3_gadget_giveback(काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req,
		पूर्णांक status)
अणु
	काष्ठा dwc3			*dwc = dep->dwc;

	dwc3_gadget_del_and_unmap_request(dep, req, status);
	req->status = DWC3_REQUEST_STATUS_COMPLETED;

	spin_unlock(&dwc->lock);
	usb_gadget_giveback_request(&dep->endpoपूर्णांक, &req->request);
	spin_lock(&dwc->lock);
पूर्ण

/**
 * dwc3_send_gadget_generic_command - issue a generic command क्रम the controller
 * @dwc: poपूर्णांकer to the controller context
 * @cmd: the command to be issued
 * @param: command parameter
 *
 * Caller should take care of locking. Issue @cmd with a given @param to @dwc
 * and रुको क्रम its completion.
 */
पूर्णांक dwc3_send_gadget_generic_command(काष्ठा dwc3 *dwc, अचिन्हित पूर्णांक cmd,
		u32 param)
अणु
	u32		समयout = 500;
	पूर्णांक		status = 0;
	पूर्णांक		ret = 0;
	u32		reg;

	dwc3_ग_लिखोl(dwc->regs, DWC3_DGCMDPAR, param);
	dwc3_ग_लिखोl(dwc->regs, DWC3_DGCMD, cmd | DWC3_DGCMD_CMDACT);

	करो अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DGCMD);
		अगर (!(reg & DWC3_DGCMD_CMDACT)) अणु
			status = DWC3_DGCMD_STATUS(reg);
			अगर (status)
				ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (--समयout);

	अगर (!समयout) अणु
		ret = -ETIMEDOUT;
		status = -ETIMEDOUT;
	पूर्ण

	trace_dwc3_gadget_generic_cmd(cmd, param, status);

	वापस ret;
पूर्ण

अटल पूर्णांक __dwc3_gadget_wakeup(काष्ठा dwc3 *dwc);

/**
 * dwc3_send_gadget_ep_cmd - issue an endpoपूर्णांक command
 * @dep: the endpoपूर्णांक to which the command is going to be issued
 * @cmd: the command to be issued
 * @params: parameters to the command
 *
 * Caller should handle locking. This function will issue @cmd with given
 * @params to @dep and रुको क्रम its completion.
 */
पूर्णांक dwc3_send_gadget_ep_cmd(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक cmd,
		काष्ठा dwc3_gadget_ep_cmd_params *params)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc = dep->endpoपूर्णांक.desc;
	काष्ठा dwc3		*dwc = dep->dwc;
	u32			समयout = 5000;
	u32			saved_config = 0;
	u32			reg;

	पूर्णांक			cmd_status = 0;
	पूर्णांक			ret = -EINVAL;

	/*
	 * When operating in USB 2.0 speeds (HS/FS), अगर GUSB2PHYCFG.ENBLSLPM or
	 * GUSB2PHYCFG.SUSPHY is set, it must be cleared beक्रमe issuing an
	 * endpoपूर्णांक command.
	 *
	 * Save and clear both GUSB2PHYCFG.ENBLSLPM and GUSB2PHYCFG.SUSPHY
	 * settings. Restore them after the command is completed.
	 *
	 * DWC_usb3 3.30a and DWC_usb31 1.90a programming guide section 3.2.2
	 */
	अगर (dwc->gadget->speed <= USB_SPEED_HIGH) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
		अगर (unlikely(reg & DWC3_GUSB2PHYCFG_SUSPHY)) अणु
			saved_config |= DWC3_GUSB2PHYCFG_SUSPHY;
			reg &= ~DWC3_GUSB2PHYCFG_SUSPHY;
		पूर्ण

		अगर (reg & DWC3_GUSB2PHYCFG_ENBLSLPM) अणु
			saved_config |= DWC3_GUSB2PHYCFG_ENBLSLPM;
			reg &= ~DWC3_GUSB2PHYCFG_ENBLSLPM;
		पूर्ण

		अगर (saved_config)
			dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
	पूर्ण

	अगर (DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_STARTTRANSFER) अणु
		पूर्णांक link_state;

		link_state = dwc3_gadget_get_link_state(dwc);
		अगर (link_state == DWC3_LINK_STATE_U1 ||
		    link_state == DWC3_LINK_STATE_U2 ||
		    link_state == DWC3_LINK_STATE_U3) अणु
			ret = __dwc3_gadget_wakeup(dwc);
			dev_WARN_ONCE(dwc->dev, ret, "wakeup failed --> %d\n",
					ret);
		पूर्ण
	पूर्ण

	dwc3_ग_लिखोl(dep->regs, DWC3_DEPCMDPAR0, params->param0);
	dwc3_ग_लिखोl(dep->regs, DWC3_DEPCMDPAR1, params->param1);
	dwc3_ग_लिखोl(dep->regs, DWC3_DEPCMDPAR2, params->param2);

	/*
	 * Synopsys Databook 2.60a states in section 6.3.2.5.6 of that अगर we're
	 * not relying on XferNotReady, we can make use of a special "No
	 * Response Update Transfer" command where we should clear both CmdAct
	 * and CmdIOC bits.
	 *
	 * With this, we करोn't need to रुको क्रम command completion and can
	 * straight away issue further commands to the endpoपूर्णांक.
	 *
	 * NOTICE: We're making an assumption that control endpoपूर्णांकs will never
	 * make use of Update Transfer command. This is a safe assumption
	 * because we can never have more than one request at a समय with
	 * Control Endpoपूर्णांकs. If anybody changes that assumption, this chunk
	 * needs to be updated accordingly.
	 */
	अगर (DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_UPDATETRANSFER &&
			!usb_endpoपूर्णांक_xfer_isoc(desc))
		cmd &= ~(DWC3_DEPCMD_CMDIOC | DWC3_DEPCMD_CMDACT);
	अन्यथा
		cmd |= DWC3_DEPCMD_CMDACT;

	dwc3_ग_लिखोl(dep->regs, DWC3_DEPCMD, cmd);
	करो अणु
		reg = dwc3_पढ़ोl(dep->regs, DWC3_DEPCMD);
		अगर (!(reg & DWC3_DEPCMD_CMDACT)) अणु
			cmd_status = DWC3_DEPCMD_STATUS(reg);

			चयन (cmd_status) अणु
			हाल 0:
				ret = 0;
				अवरोध;
			हाल DEPEVT_TRANSFER_NO_RESOURCE:
				dev_WARN(dwc->dev, "No resource for %s\n",
					 dep->name);
				ret = -EINVAL;
				अवरोध;
			हाल DEPEVT_TRANSFER_BUS_EXPIRY:
				/*
				 * SW issues START TRANSFER command to
				 * isochronous ep with future frame पूर्णांकerval. If
				 * future पूर्णांकerval समय has alपढ़ोy passed when
				 * core receives the command, it will respond
				 * with an error status of 'Bus Expiry'.
				 *
				 * Instead of always वापसing -EINVAL, let's
				 * give a hपूर्णांक to the gadget driver that this is
				 * the हाल by वापसing -EAGAIN.
				 */
				ret = -EAGAIN;
				अवरोध;
			शेष:
				dev_WARN(dwc->dev, "UNKNOWN cmd status\n");
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण जबतक (--समयout);

	अगर (समयout == 0) अणु
		ret = -ETIMEDOUT;
		cmd_status = -ETIMEDOUT;
	पूर्ण

	trace_dwc3_gadget_ep_cmd(dep, cmd, params, cmd_status);

	अगर (DWC3_DEPCMD_CMD(cmd) == DWC3_DEPCMD_STARTTRANSFER) अणु
		अगर (ret == 0)
			dep->flags |= DWC3_EP_TRANSFER_STARTED;

		अगर (ret != -ETIMEDOUT)
			dwc3_gadget_ep_get_transfer_index(dep);
	पूर्ण

	अगर (saved_config) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_GUSB2PHYCFG(0));
		reg |= saved_config;
		dwc3_ग_लिखोl(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_send_clear_stall_ep_cmd(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3 *dwc = dep->dwc;
	काष्ठा dwc3_gadget_ep_cmd_params params;
	u32 cmd = DWC3_DEPCMD_CLEARSTALL;

	/*
	 * As of core revision 2.60a the recommended programming model
	 * is to set the ClearPendIN bit when issuing a Clear Stall EP
	 * command क्रम IN endpoपूर्णांकs. This is to prevent an issue where
	 * some (non-compliant) hosts may not send ACK TPs क्रम pending
	 * IN transfers due to a mishandled error condition. Synopsys
	 * STAR 9000614252.
	 */
	अगर (dep->direction &&
	    !DWC3_VER_IS_PRIOR(DWC3, 260A) &&
	    (dwc->gadget->speed >= USB_SPEED_SUPER))
		cmd |= DWC3_DEPCMD_CLEARPENDIN;

	स_रखो(&params, 0, माप(params));

	वापस dwc3_send_gadget_ep_cmd(dep, cmd, &params);
पूर्ण

अटल dma_addr_t dwc3_trb_dma_offset(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_trb *trb)
अणु
	u32		offset = (अक्षर *) trb - (अक्षर *) dep->trb_pool;

	वापस dep->trb_pool_dma + offset;
पूर्ण

अटल पूर्णांक dwc3_alloc_trb_pool(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;

	अगर (dep->trb_pool)
		वापस 0;

	dep->trb_pool = dma_alloc_coherent(dwc->sysdev,
			माप(काष्ठा dwc3_trb) * DWC3_TRB_NUM,
			&dep->trb_pool_dma, GFP_KERNEL);
	अगर (!dep->trb_pool) अणु
		dev_err(dep->dwc->dev, "failed to allocate trb pool for %s\n",
				dep->name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc3_मुक्त_trb_pool(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;

	dma_मुक्त_coherent(dwc->sysdev, माप(काष्ठा dwc3_trb) * DWC3_TRB_NUM,
			dep->trb_pool, dep->trb_pool_dma);

	dep->trb_pool = शून्य;
	dep->trb_pool_dma = 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_set_xfer_resource(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params params;

	स_रखो(&params, 0x00, माप(params));

	params.param0 = DWC3_DEPXFERCFG_NUM_XFER_RES(1);

	वापस dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETTRANSFRESOURCE,
			&params);
पूर्ण

/**
 * dwc3_gadget_start_config - configure ep resources
 * @dep: endpoपूर्णांक that is being enabled
 *
 * Issue a %DWC3_DEPCMD_DEPSTARTCFG command to @dep. After the command's
 * completion, it will set Transfer Resource क्रम all available endpoपूर्णांकs.
 *
 * The assignment of transfer resources cannot perfectly follow the data book
 * due to the fact that the controller driver करोes not have all knowledge of the
 * configuration in advance. It is given this inक्रमmation piecemeal by the
 * composite gadget framework after every SET_CONFIGURATION and
 * SET_INTERFACE. Trying to follow the databook programming model in this
 * scenario can cause errors. For two reasons:
 *
 * 1) The databook says to करो %DWC3_DEPCMD_DEPSTARTCFG क्रम every
 * %USB_REQ_SET_CONFIGURATION and %USB_REQ_SET_INTERFACE (8.1.5). This is
 * incorrect in the scenario of multiple पूर्णांकerfaces.
 *
 * 2) The databook करोes not mention करोing more %DWC3_DEPCMD_DEPXFERCFG क्रम new
 * endpoपूर्णांक on alt setting (8.1.6).
 *
 * The following simplअगरied method is used instead:
 *
 * All hardware endpoपूर्णांकs can be asचिन्हित a transfer resource and this setting
 * will stay persistent until either a core reset or hibernation. So whenever we
 * करो a %DWC3_DEPCMD_DEPSTARTCFG(0) we can go ahead and करो
 * %DWC3_DEPCMD_DEPXFERCFG क्रम every hardware endpoपूर्णांक as well. We are
 * guaranteed that there are as many transfer resources as endpoपूर्णांकs.
 *
 * This function is called क्रम each endpoपूर्णांक when it is being enabled but is
 * triggered only when called क्रम EP0-out, which always happens first, and which
 * should only happen in one of the above conditions.
 */
अटल पूर्णांक dwc3_gadget_start_config(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params params;
	काष्ठा dwc3		*dwc;
	u32			cmd;
	पूर्णांक			i;
	पूर्णांक			ret;

	अगर (dep->number)
		वापस 0;

	स_रखो(&params, 0x00, माप(params));
	cmd = DWC3_DEPCMD_DEPSTARTCFG;
	dwc = dep->dwc;

	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < DWC3_ENDPOINTS_NUM; i++) अणु
		काष्ठा dwc3_ep *dep = dwc->eps[i];

		अगर (!dep)
			जारी;

		ret = dwc3_gadget_set_xfer_resource(dep);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_set_ep_config(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक action)
अणु
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	काष्ठा dwc3_gadget_ep_cmd_params params;
	काष्ठा dwc3 *dwc = dep->dwc;

	comp_desc = dep->endpoपूर्णांक.comp_desc;
	desc = dep->endpoपूर्णांक.desc;

	स_रखो(&params, 0x00, माप(params));

	params.param0 = DWC3_DEPCFG_EP_TYPE(usb_endpoपूर्णांक_type(desc))
		| DWC3_DEPCFG_MAX_PACKET_SIZE(usb_endpoपूर्णांक_maxp(desc));

	/* Burst size is only needed in SuperSpeed mode */
	अगर (dwc->gadget->speed >= USB_SPEED_SUPER) अणु
		u32 burst = dep->endpoपूर्णांक.maxburst;

		params.param0 |= DWC3_DEPCFG_BURST_SIZE(burst - 1);
	पूर्ण

	params.param0 |= action;
	अगर (action == DWC3_DEPCFG_ACTION_RESTORE)
		params.param2 |= dep->saved_state;

	अगर (usb_endpoपूर्णांक_xfer_control(desc))
		params.param1 = DWC3_DEPCFG_XFER_COMPLETE_EN;

	अगर (dep->number <= 1 || usb_endpoपूर्णांक_xfer_isoc(desc))
		params.param1 |= DWC3_DEPCFG_XFER_NOT_READY_EN;

	अगर (usb_ss_max_streams(comp_desc) && usb_endpoपूर्णांक_xfer_bulk(desc)) अणु
		params.param1 |= DWC3_DEPCFG_STREAM_CAPABLE
			| DWC3_DEPCFG_XFER_COMPLETE_EN
			| DWC3_DEPCFG_STREAM_EVENT_EN;
		dep->stream_capable = true;
	पूर्ण

	अगर (!usb_endpoपूर्णांक_xfer_control(desc))
		params.param1 |= DWC3_DEPCFG_XFER_IN_PROGRESS_EN;

	/*
	 * We are करोing 1:1 mapping क्रम endpoपूर्णांकs, meaning
	 * Physical Endpoपूर्णांकs 2 maps to Logical Endpoपूर्णांक 2 and
	 * so on. We consider the direction bit as part of the physical
	 * endpoपूर्णांक number. So USB endpoपूर्णांक 0x81 is 0x03.
	 */
	params.param1 |= DWC3_DEPCFG_EP_NUMBER(dep->number);

	/*
	 * We must use the lower 16 TX FIFOs even though
	 * HW might have more
	 */
	अगर (dep->direction)
		params.param0 |= DWC3_DEPCFG_FIFO_NUMBER(dep->number >> 1);

	अगर (desc->bInterval) अणु
		u8 bInterval_m1;

		/*
		 * Valid range क्रम DEPCFG.bInterval_m1 is from 0 to 13.
		 *
		 * NOTE: The programming guide incorrectly stated bInterval_m1
		 * must be set to 0 when operating in fullspeed. Internally the
		 * controller करोes not have this limitation. See DWC_usb3x
		 * programming guide section 3.2.2.1.
		 */
		bInterval_m1 = min_t(u8, desc->bInterval - 1, 13);

		अगर (usb_endpoपूर्णांक_type(desc) == USB_ENDPOINT_XFER_INT &&
		    dwc->gadget->speed == USB_SPEED_FULL)
			dep->पूर्णांकerval = desc->bInterval;
		अन्यथा
			dep->पूर्णांकerval = 1 << (desc->bInterval - 1);

		params.param1 |= DWC3_DEPCFG_BINTERVAL_M1(bInterval_m1);
	पूर्ण

	वापस dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETEPCONFIG, &params);
पूर्ण

अटल व्योम dwc3_stop_active_transfer(काष्ठा dwc3_ep *dep, bool क्रमce,
		bool पूर्णांकerrupt);

/**
 * __dwc3_gadget_ep_enable - initializes a hw endpoपूर्णांक
 * @dep: endpoपूर्णांक to be initialized
 * @action: one of INIT, MODIFY or RESTORE
 *
 * Caller should take care of locking. Execute all necessary commands to
 * initialize a HW endpoपूर्णांक so it can be used by a gadget driver.
 */
अटल पूर्णांक __dwc3_gadget_ep_enable(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक action)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc = dep->endpoपूर्णांक.desc;
	काष्ठा dwc3		*dwc = dep->dwc;

	u32			reg;
	पूर्णांक			ret;

	अगर (!(dep->flags & DWC3_EP_ENABLED)) अणु
		ret = dwc3_gadget_start_config(dep);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = dwc3_gadget_set_ep_config(dep, action);
	अगर (ret)
		वापस ret;

	अगर (!(dep->flags & DWC3_EP_ENABLED)) अणु
		काष्ठा dwc3_trb	*trb_st_hw;
		काष्ठा dwc3_trb	*trb_link;

		dep->type = usb_endpoपूर्णांक_type(desc);
		dep->flags |= DWC3_EP_ENABLED;

		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DALEPENA);
		reg |= DWC3_DALEPENA_EP(dep->number);
		dwc3_ग_लिखोl(dwc->regs, DWC3_DALEPENA, reg);

		अगर (usb_endpoपूर्णांक_xfer_control(desc))
			जाओ out;

		/* Initialize the TRB ring */
		dep->trb_dequeue = 0;
		dep->trb_enqueue = 0;
		स_रखो(dep->trb_pool, 0,
		       माप(काष्ठा dwc3_trb) * DWC3_TRB_NUM);

		/* Link TRB. The HWO bit is never reset */
		trb_st_hw = &dep->trb_pool[0];

		trb_link = &dep->trb_pool[DWC3_TRB_NUM - 1];
		trb_link->bpl = lower_32_bits(dwc3_trb_dma_offset(dep, trb_st_hw));
		trb_link->bph = upper_32_bits(dwc3_trb_dma_offset(dep, trb_st_hw));
		trb_link->ctrl |= DWC3_TRBCTL_LINK_TRB;
		trb_link->ctrl |= DWC3_TRB_CTRL_HWO;
	पूर्ण

	/*
	 * Issue StartTransfer here with no-op TRB so we can always rely on No
	 * Response Update Transfer command.
	 */
	अगर (usb_endpoपूर्णांक_xfer_bulk(desc) ||
			usb_endpoपूर्णांक_xfer_पूर्णांक(desc)) अणु
		काष्ठा dwc3_gadget_ep_cmd_params params;
		काष्ठा dwc3_trb	*trb;
		dma_addr_t trb_dma;
		u32 cmd;

		स_रखो(&params, 0, माप(params));
		trb = &dep->trb_pool[0];
		trb_dma = dwc3_trb_dma_offset(dep, trb);

		params.param0 = upper_32_bits(trb_dma);
		params.param1 = lower_32_bits(trb_dma);

		cmd = DWC3_DEPCMD_STARTTRANSFER;

		ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
		अगर (ret < 0)
			वापस ret;

		अगर (dep->stream_capable) अणु
			/*
			 * For streams, at start, there maybe a race where the
			 * host primes the endpoपूर्णांक beक्रमe the function driver
			 * queues a request to initiate a stream. In that हाल,
			 * the controller will not see the prime to generate the
			 * ERDY and start stream. To workaround this, issue a
			 * no-op TRB as normal, but end it immediately. As a
			 * result, when the function driver queues the request,
			 * the next START_TRANSFER command will cause the
			 * controller to generate an ERDY to initiate the
			 * stream.
			 */
			dwc3_stop_active_transfer(dep, true, true);

			/*
			 * All stream eps will reinitiate stream on NoStream
			 * rejection until we can determine that the host can
			 * prime after the first transfer.
			 *
			 * However, अगर the controller is capable of
			 * TXF_FLUSH_BYPASS, then IN direction endpoपूर्णांकs will
			 * स्वतःmatically restart the stream without the driver
			 * initiation.
			 */
			अगर (!dep->direction ||
			    !(dwc->hwparams.hwparams9 &
			      DWC3_GHWPARAMS9_DEV_TXF_FLUSH_BYPASS))
				dep->flags |= DWC3_EP_FORCE_RESTART_STREAM;
		पूर्ण
	पूर्ण

out:
	trace_dwc3_gadget_ep_enable(dep);

	वापस 0;
पूर्ण

अटल व्योम dwc3_हटाओ_requests(काष्ठा dwc3 *dwc, काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_request		*req;

	dwc3_stop_active_transfer(dep, true, false);

	/* - giveback all requests to gadget driver */
	जबतक (!list_empty(&dep->started_list)) अणु
		req = next_request(&dep->started_list);

		dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
	पूर्ण

	जबतक (!list_empty(&dep->pending_list)) अणु
		req = next_request(&dep->pending_list);

		dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
	पूर्ण

	जबतक (!list_empty(&dep->cancelled_list)) अणु
		req = next_request(&dep->cancelled_list);

		dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
	पूर्ण
पूर्ण

/**
 * __dwc3_gadget_ep_disable - disables a hw endpoपूर्णांक
 * @dep: the endpoपूर्णांक to disable
 *
 * This function unकरोes what __dwc3_gadget_ep_enable did and also हटाओs
 * requests which are currently being processed by the hardware and those which
 * are not yet scheduled.
 *
 * Caller should take care of locking.
 */
अटल पूर्णांक __dwc3_gadget_ep_disable(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;
	u32			reg;

	trace_dwc3_gadget_ep_disable(dep);

	/* make sure HW endpoपूर्णांक isn't stalled */
	अगर (dep->flags & DWC3_EP_STALL)
		__dwc3_gadget_ep_set_halt(dep, 0, false);

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DALEPENA);
	reg &= ~DWC3_DALEPENA_EP(dep->number);
	dwc3_ग_लिखोl(dwc->regs, DWC3_DALEPENA, reg);

	/* Clear out the ep descriptors क्रम non-ep0 */
	अगर (dep->number > 1) अणु
		dep->endpoपूर्णांक.comp_desc = शून्य;
		dep->endpoपूर्णांक.desc = शून्य;
	पूर्ण

	dwc3_हटाओ_requests(dwc, dep);

	dep->stream_capable = false;
	dep->type = 0;
	dep->flags = 0;

	वापस 0;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक dwc3_gadget_ep0_enable(काष्ठा usb_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep0_disable(काष्ठा usb_ep *ep)
अणु
	वापस -EINVAL;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक dwc3_gadget_ep_enable(काष्ठा usb_ep *ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा dwc3_ep			*dep;
	काष्ठा dwc3			*dwc;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				ret;

	अगर (!ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT) अणु
		pr_debug("dwc3: invalid parameters\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->wMaxPacketSize) अणु
		pr_debug("dwc3: missing wMaxPacketSize\n");
		वापस -EINVAL;
	पूर्ण

	dep = to_dwc3_ep(ep);
	dwc = dep->dwc;

	अगर (dev_WARN_ONCE(dwc->dev, dep->flags & DWC3_EP_ENABLED,
					"%s is already enabled\n",
					dep->name))
		वापस 0;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_INIT);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा dwc3_ep			*dep;
	काष्ठा dwc3			*dwc;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				ret;

	अगर (!ep) अणु
		pr_debug("dwc3: invalid parameters\n");
		वापस -EINVAL;
	पूर्ण

	dep = to_dwc3_ep(ep);
	dwc = dep->dwc;

	अगर (dev_WARN_ONCE(dwc->dev, !(dep->flags & DWC3_EP_ENABLED),
					"%s is already disabled\n",
					dep->name))
		वापस 0;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_ep_disable(dep);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा usb_request *dwc3_gadget_ep_alloc_request(काष्ठा usb_ep *ep,
		gfp_t gfp_flags)
अणु
	काष्ठा dwc3_request		*req;
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	req->direction	= dep->direction;
	req->epnum	= dep->number;
	req->dep	= dep;
	req->status	= DWC3_REQUEST_STATUS_UNKNOWN;

	trace_dwc3_alloc_request(req);

	वापस &req->request;
पूर्ण

अटल व्योम dwc3_gadget_ep_मुक्त_request(काष्ठा usb_ep *ep,
		काष्ठा usb_request *request)
अणु
	काष्ठा dwc3_request		*req = to_dwc3_request(request);

	trace_dwc3_मुक्त_request(req);
	kमुक्त(req);
पूर्ण

/**
 * dwc3_ep_prev_trb - वापसs the previous TRB in the ring
 * @dep: The endpoपूर्णांक with the TRB ring
 * @index: The index of the current TRB in the ring
 *
 * Returns the TRB prior to the one poपूर्णांकed to by the index. If the
 * index is 0, we will wrap backwards, skip the link TRB, and वापस
 * the one just beक्रमe that.
 */
अटल काष्ठा dwc3_trb *dwc3_ep_prev_trb(काष्ठा dwc3_ep *dep, u8 index)
अणु
	u8 पंचांगp = index;

	अगर (!पंचांगp)
		पंचांगp = DWC3_TRB_NUM - 1;

	वापस &dep->trb_pool[पंचांगp - 1];
पूर्ण

अटल u32 dwc3_calc_trbs_left(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_trb		*पंचांगp;
	u8			trbs_left;

	/*
	 * If enqueue & dequeue are equal than it is either full or empty.
	 *
	 * One way to know क्रम sure is अगर the TRB right beक्रमe us has HWO bit
	 * set or not. If it has, then we're definitely full and can't fit any
	 * more transfers in our ring.
	 */
	अगर (dep->trb_enqueue == dep->trb_dequeue) अणु
		पंचांगp = dwc3_ep_prev_trb(dep, dep->trb_enqueue);
		अगर (पंचांगp->ctrl & DWC3_TRB_CTRL_HWO)
			वापस 0;

		वापस DWC3_TRB_NUM - 1;
	पूर्ण

	trbs_left = dep->trb_dequeue - dep->trb_enqueue;
	trbs_left &= (DWC3_TRB_NUM - 1);

	अगर (dep->trb_dequeue < dep->trb_enqueue)
		trbs_left--;

	वापस trbs_left;
पूर्ण

अटल व्योम __dwc3_prepare_one_trb(काष्ठा dwc3_ep *dep, काष्ठा dwc3_trb *trb,
		dma_addr_t dma, अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक chain,
		अचिन्हित पूर्णांक node, अचिन्हित पूर्णांक stream_id,
		अचिन्हित पूर्णांक लघु_not_ok, अचिन्हित पूर्णांक no_पूर्णांकerrupt,
		अचिन्हित पूर्णांक is_last, bool must_पूर्णांकerrupt)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;
	काष्ठा usb_gadget	*gadget = dwc->gadget;
	क्रमागत usb_device_speed	speed = gadget->speed;

	trb->size = DWC3_TRB_SIZE_LENGTH(length);
	trb->bpl = lower_32_bits(dma);
	trb->bph = upper_32_bits(dma);

	चयन (usb_endpoपूर्णांक_type(dep->endpoपूर्णांक.desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		trb->ctrl = DWC3_TRBCTL_CONTROL_SETUP;
		अवरोध;

	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (!node) अणु
			trb->ctrl = DWC3_TRBCTL_ISOCHRONOUS_FIRST;

			/*
			 * USB Specअगरication 2.0 Section 5.9.2 states that: "If
			 * there is only a single transaction in the microframe,
			 * only a DATA0 data packet PID is used.  If there are
			 * two transactions per microframe, DATA1 is used क्रम
			 * the first transaction data packet and DATA0 is used
			 * क्रम the second transaction data packet.  If there are
			 * three transactions per microframe, DATA2 is used क्रम
			 * the first transaction data packet, DATA1 is used क्रम
			 * the second, and DATA0 is used क्रम the third."
			 *
			 * IOW, we should satisfy the following हालs:
			 *
			 * 1) length <= maxpacket
			 *	- DATA0
			 *
			 * 2) maxpacket < length <= (2 * maxpacket)
			 *	- DATA1, DATA0
			 *
			 * 3) (2 * maxpacket) < length <= (3 * maxpacket)
			 *	- DATA2, DATA1, DATA0
			 */
			अगर (speed == USB_SPEED_HIGH) अणु
				काष्ठा usb_ep *ep = &dep->endpoपूर्णांक;
				अचिन्हित पूर्णांक mult = 2;
				अचिन्हित पूर्णांक maxp = usb_endpoपूर्णांक_maxp(ep->desc);

				अगर (length <= (2 * maxp))
					mult--;

				अगर (length <= maxp)
					mult--;

				trb->size |= DWC3_TRB_SIZE_PCM1(mult);
			पूर्ण
		पूर्ण अन्यथा अणु
			trb->ctrl = DWC3_TRBCTL_ISOCHRONOUS;
		पूर्ण

		/* always enable Interrupt on Missed ISOC */
		trb->ctrl |= DWC3_TRB_CTRL_ISP_IMI;
		अवरोध;

	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		trb->ctrl = DWC3_TRBCTL_NORMAL;
		अवरोध;
	शेष:
		/*
		 * This is only possible with faulty memory because we
		 * checked it alपढ़ोy :)
		 */
		dev_WARN(dwc->dev, "Unknown endpoint type %d\n",
				usb_endpoपूर्णांक_type(dep->endpoपूर्णांक.desc));
	पूर्ण

	/*
	 * Enable Continue on Short Packet
	 * when endpoपूर्णांक is not a stream capable
	 */
	अगर (usb_endpoपूर्णांक_dir_out(dep->endpoपूर्णांक.desc)) अणु
		अगर (!dep->stream_capable)
			trb->ctrl |= DWC3_TRB_CTRL_CSP;

		अगर (लघु_not_ok)
			trb->ctrl |= DWC3_TRB_CTRL_ISP_IMI;
	पूर्ण

	अगर ((!no_पूर्णांकerrupt && !chain) || must_पूर्णांकerrupt)
		trb->ctrl |= DWC3_TRB_CTRL_IOC;

	अगर (chain)
		trb->ctrl |= DWC3_TRB_CTRL_CHN;
	अन्यथा अगर (dep->stream_capable && is_last)
		trb->ctrl |= DWC3_TRB_CTRL_LST;

	अगर (usb_endpoपूर्णांक_xfer_bulk(dep->endpoपूर्णांक.desc) && dep->stream_capable)
		trb->ctrl |= DWC3_TRB_CTRL_SID_SOFN(stream_id);

	trb->ctrl |= DWC3_TRB_CTRL_HWO;

	dwc3_ep_inc_enq(dep);

	trace_dwc3_prepare_trb(dep, trb);
पूर्ण

/**
 * dwc3_prepare_one_trb - setup one TRB from one request
 * @dep: endpoपूर्णांक क्रम which this request is prepared
 * @req: dwc3_request poपूर्णांकer
 * @trb_length: buffer size of the TRB
 * @chain: should this TRB be chained to the next?
 * @node: only क्रम isochronous endpoपूर्णांकs. First TRB needs dअगरferent type.
 * @use_bounce_buffer: set to use bounce buffer
 * @must_पूर्णांकerrupt: set to पूर्णांकerrupt on TRB completion
 */
अटल व्योम dwc3_prepare_one_trb(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req, अचिन्हित पूर्णांक trb_length,
		अचिन्हित पूर्णांक chain, अचिन्हित पूर्णांक node, bool use_bounce_buffer,
		bool must_पूर्णांकerrupt)
अणु
	काष्ठा dwc3_trb		*trb;
	dma_addr_t		dma;
	अचिन्हित पूर्णांक		stream_id = req->request.stream_id;
	अचिन्हित पूर्णांक		लघु_not_ok = req->request.लघु_not_ok;
	अचिन्हित पूर्णांक		no_पूर्णांकerrupt = req->request.no_पूर्णांकerrupt;
	अचिन्हित पूर्णांक		is_last = req->request.is_last;

	अगर (use_bounce_buffer)
		dma = dep->dwc->bounce_addr;
	अन्यथा अगर (req->request.num_sgs > 0)
		dma = sg_dma_address(req->start_sg);
	अन्यथा
		dma = req->request.dma;

	trb = &dep->trb_pool[dep->trb_enqueue];

	अगर (!req->trb) अणु
		dwc3_gadget_move_started_request(req);
		req->trb = trb;
		req->trb_dma = dwc3_trb_dma_offset(dep, trb);
	पूर्ण

	req->num_trbs++;

	__dwc3_prepare_one_trb(dep, trb, dma, trb_length, chain, node,
			stream_id, लघु_not_ok, no_पूर्णांकerrupt, is_last,
			must_पूर्णांकerrupt);
पूर्ण

अटल bool dwc3_needs_extra_trb(काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req)
अणु
	अचिन्हित पूर्णांक maxp = usb_endpoपूर्णांक_maxp(dep->endpoपूर्णांक.desc);
	अचिन्हित पूर्णांक rem = req->request.length % maxp;

	अगर ((req->request.length && req->request.zero && !rem &&
			!usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc)) ||
			(!req->direction && rem))
		वापस true;

	वापस false;
पूर्ण

/**
 * dwc3_prepare_last_sg - prepare TRBs क्रम the last SG entry
 * @dep: The endpoपूर्णांक that the request beदीर्घs to
 * @req: The request to prepare
 * @entry_length: The last SG entry size
 * @node: Indicates whether this is not the first entry (क्रम isoc only)
 *
 * Return the number of TRBs prepared.
 */
अटल पूर्णांक dwc3_prepare_last_sg(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req, अचिन्हित पूर्णांक entry_length,
		अचिन्हित पूर्णांक node)
अणु
	अचिन्हित पूर्णांक maxp = usb_endpoपूर्णांक_maxp(dep->endpoपूर्णांक.desc);
	अचिन्हित पूर्णांक rem = req->request.length % maxp;
	अचिन्हित पूर्णांक num_trbs = 1;

	अगर (dwc3_needs_extra_trb(dep, req))
		num_trbs++;

	अगर (dwc3_calc_trbs_left(dep) < num_trbs)
		वापस 0;

	req->needs_extra_trb = num_trbs > 1;

	/* Prepare a normal TRB */
	अगर (req->direction || req->request.length)
		dwc3_prepare_one_trb(dep, req, entry_length,
				req->needs_extra_trb, node, false, false);

	/* Prepare extra TRBs क्रम ZLP and MPS OUT transfer alignment */
	अगर ((!req->direction && !req->request.length) || req->needs_extra_trb)
		dwc3_prepare_one_trb(dep, req,
				req->direction ? 0 : maxp - rem,
				false, 1, true, false);

	वापस num_trbs;
पूर्ण

अटल पूर्णांक dwc3_prepare_trbs_sg(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req)
अणु
	काष्ठा scatterlist *sg = req->start_sg;
	काष्ठा scatterlist *s;
	पूर्णांक		i;
	अचिन्हित पूर्णांक length = req->request.length;
	अचिन्हित पूर्णांक reमुख्यing = req->request.num_mapped_sgs
		- req->num_queued_sgs;
	अचिन्हित पूर्णांक num_trbs = req->num_trbs;
	bool needs_extra_trb = dwc3_needs_extra_trb(dep, req);

	/*
	 * If we resume preparing the request, then get the reमुख्यing length of
	 * the request and resume where we left off.
	 */
	क्रम_each_sg(req->request.sg, s, req->num_queued_sgs, i)
		length -= sg_dma_len(s);

	क्रम_each_sg(sg, s, reमुख्यing, i) अणु
		अचिन्हित पूर्णांक num_trbs_left = dwc3_calc_trbs_left(dep);
		अचिन्हित पूर्णांक trb_length;
		bool must_पूर्णांकerrupt = false;
		bool last_sg = false;

		trb_length = min_t(अचिन्हित पूर्णांक, length, sg_dma_len(s));

		length -= trb_length;

		/*
		 * IOMMU driver is coalescing the list of sgs which shares a
		 * page boundary पूर्णांकo one and giving it to USB driver. With
		 * this the number of sgs mapped is not equal to the number of
		 * sgs passed. So mark the chain bit to false अगर it isthe last
		 * mapped sg.
		 */
		अगर ((i == reमुख्यing - 1) || !length)
			last_sg = true;

		अगर (!num_trbs_left)
			अवरोध;

		अगर (last_sg) अणु
			अगर (!dwc3_prepare_last_sg(dep, req, trb_length, i))
				अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * Look ahead to check अगर we have enough TRBs क्रम the
			 * next SG entry. If not, set पूर्णांकerrupt on this TRB to
			 * resume preparing the next SG entry when more TRBs are
			 * मुक्त.
			 */
			अगर (num_trbs_left == 1 || (needs_extra_trb &&
					num_trbs_left <= 2 &&
					sg_dma_len(sg_next(s)) >= length))
				must_पूर्णांकerrupt = true;

			dwc3_prepare_one_trb(dep, req, trb_length, 1, i, false,
					must_पूर्णांकerrupt);
		पूर्ण

		/*
		 * There can be a situation where all sgs in sglist are not
		 * queued because of insufficient trb number. To handle this
		 * हाल, update start_sg to next sg to be queued, so that
		 * we have मुक्त trbs we can जारी queuing from where we
		 * previously stopped
		 */
		अगर (!last_sg)
			req->start_sg = sg_next(s);

		req->num_queued_sgs++;
		req->num_pending_sgs--;

		/*
		 * The number of pending SG entries may not correspond to the
		 * number of mapped SG entries. If all the data are queued, then
		 * करोn't include unused SG entries.
		 */
		अगर (length == 0) अणु
			req->num_pending_sgs = 0;
			अवरोध;
		पूर्ण

		अगर (must_पूर्णांकerrupt)
			अवरोध;
	पूर्ण

	वापस req->num_trbs - num_trbs;
पूर्ण

अटल पूर्णांक dwc3_prepare_trbs_linear(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req)
अणु
	वापस dwc3_prepare_last_sg(dep, req, req->request.length, 0);
पूर्ण

/*
 * dwc3_prepare_trbs - setup TRBs from requests
 * @dep: endpoपूर्णांक क्रम which requests are being prepared
 *
 * The function goes through the requests list and sets up TRBs क्रम the
 * transfers. The function वापसs once there are no more TRBs available or
 * it runs out of requests.
 *
 * Returns the number of TRBs prepared or negative त्रुटि_सं.
 */
अटल पूर्णांक dwc3_prepare_trbs(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_request	*req, *n;
	पूर्णांक			ret = 0;

	BUILD_BUG_ON_NOT_POWER_OF_2(DWC3_TRB_NUM);

	/*
	 * We can get in a situation where there's a request in the started list
	 * but there weren't enough TRBs to fully kick it in the first समय
	 * around, so it has been रुकोing क्रम more TRBs to be मुक्तd up.
	 *
	 * In that हाल, we should check अगर we have a request with pending_sgs
	 * in the started list and prepare TRBs क्रम that request first,
	 * otherwise we will prepare TRBs completely out of order and that will
	 * अवरोध things.
	 */
	list_क्रम_each_entry(req, &dep->started_list, list) अणु
		अगर (req->num_pending_sgs > 0) अणु
			ret = dwc3_prepare_trbs_sg(dep, req);
			अगर (!ret || req->num_pending_sgs)
				वापस ret;
		पूर्ण

		अगर (!dwc3_calc_trbs_left(dep))
			वापस ret;

		/*
		 * Don't prepare beyond a transfer. In DWC_usb32, its transfer
		 * burst capability may try to पढ़ो and use TRBs beyond the
		 * active transfer instead of stopping.
		 */
		अगर (dep->stream_capable && req->request.is_last)
			वापस ret;
	पूर्ण

	list_क्रम_each_entry_safe(req, n, &dep->pending_list, list) अणु
		काष्ठा dwc3	*dwc = dep->dwc;

		ret = usb_gadget_map_request_by_dev(dwc->sysdev, &req->request,
						    dep->direction);
		अगर (ret)
			वापस ret;

		req->sg			= req->request.sg;
		req->start_sg		= req->sg;
		req->num_queued_sgs	= 0;
		req->num_pending_sgs	= req->request.num_mapped_sgs;

		अगर (req->num_pending_sgs > 0) अणु
			ret = dwc3_prepare_trbs_sg(dep, req);
			अगर (req->num_pending_sgs)
				वापस ret;
		पूर्ण अन्यथा अणु
			ret = dwc3_prepare_trbs_linear(dep, req);
		पूर्ण

		अगर (!ret || !dwc3_calc_trbs_left(dep))
			वापस ret;

		/*
		 * Don't prepare beyond a transfer. In DWC_usb32, its transfer
		 * burst capability may try to पढ़ो and use TRBs beyond the
		 * active transfer instead of stopping.
		 */
		अगर (dep->stream_capable && req->request.is_last)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dwc3_gadget_ep_cleanup_cancelled_requests(काष्ठा dwc3_ep *dep);

अटल पूर्णांक __dwc3_gadget_kick_transfer(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params params;
	काष्ठा dwc3_request		*req;
	पूर्णांक				starting;
	पूर्णांक				ret;
	u32				cmd;

	/*
	 * Note that it's normal to have no new TRBs prepared (i.e. ret == 0).
	 * This happens when we need to stop and restart a transfer such as in
	 * the हाल of reinitiating a stream or retrying an isoc transfer.
	 */
	ret = dwc3_prepare_trbs(dep);
	अगर (ret < 0)
		वापस ret;

	starting = !(dep->flags & DWC3_EP_TRANSFER_STARTED);

	/*
	 * If there's no new TRB prepared and we don't need to restart a
	 * transfer, there's no need to update the transfer.
	 */
	अगर (!ret && !starting)
		वापस ret;

	req = next_request(&dep->started_list);
	अगर (!req) अणु
		dep->flags |= DWC3_EP_PENDING_REQUEST;
		वापस 0;
	पूर्ण

	स_रखो(&params, 0, माप(params));

	अगर (starting) अणु
		params.param0 = upper_32_bits(req->trb_dma);
		params.param1 = lower_32_bits(req->trb_dma);
		cmd = DWC3_DEPCMD_STARTTRANSFER;

		अगर (dep->stream_capable)
			cmd |= DWC3_DEPCMD_PARAM(req->request.stream_id);

		अगर (usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc))
			cmd |= DWC3_DEPCMD_PARAM(dep->frame_number);
	पूर्ण अन्यथा अणु
		cmd = DWC3_DEPCMD_UPDATETRANSFER |
			DWC3_DEPCMD_PARAM(dep->resource_index);
	पूर्ण

	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	अगर (ret < 0) अणु
		काष्ठा dwc3_request *पंचांगp;

		अगर (ret == -EAGAIN)
			वापस ret;

		dwc3_stop_active_transfer(dep, true, true);

		list_क्रम_each_entry_safe(req, पंचांगp, &dep->started_list, list)
			dwc3_gadget_move_cancelled_request(req, DWC3_REQUEST_STATUS_DEQUEUED);

		/* If ep isn't started, then there's no end transfer pending */
		अगर (!(dep->flags & DWC3_EP_END_TRANSFER_PENDING))
			dwc3_gadget_ep_cleanup_cancelled_requests(dep);

		वापस ret;
	पूर्ण

	अगर (dep->stream_capable && req->request.is_last)
		dep->flags |= DWC3_EP_WAIT_TRANSFER_COMPLETE;

	वापस 0;
पूर्ण

अटल पूर्णांक __dwc3_gadget_get_frame(काष्ठा dwc3 *dwc)
अणु
	u32			reg;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);
	वापस DWC3_DSTS_SOFFN(reg);
पूर्ण

/**
 * dwc3_gadget_start_isoc_quirk - workaround invalid frame number
 * @dep: isoc endpoपूर्णांक
 *
 * This function tests क्रम the correct combination of BIT[15:14] from the 16-bit
 * microframe number reported by the XferNotReady event क्रम the future frame
 * number to start the isoc transfer.
 *
 * In DWC_usb31 version 1.70a-ea06 and prior, क्रम highspeed and fullspeed
 * isochronous IN, BIT[15:14] of the 16-bit microframe number reported by the
 * XferNotReady event are invalid. The driver uses this number to schedule the
 * isochronous transfer and passes it to the START TRANSFER command. Because
 * this number is invalid, the command may fail. If BIT[15:14] matches the
 * पूर्णांकernal 16-bit microframe, the START TRANSFER command will pass and the
 * transfer will start at the scheduled समय, अगर it is off by 1, the command
 * will still pass, but the transfer will start 2 seconds in the future. For all
 * other conditions, the START TRANSFER command will fail with bus-expiry.
 *
 * In order to workaround this issue, we can test क्रम the correct combination of
 * BIT[15:14] by sending START TRANSFER commands with dअगरferent values of
 * BIT[15:14]: 'b00, 'b01, 'b10, and 'b11. Each combination is 2^14 uframe apart
 * (or 2 seconds). 4 seconds पूर्णांकo the future will result in a bus-expiry status.
 * As the result, within the 4 possible combinations क्रम BIT[15:14], there will
 * be 2 successful and 2 failure START COMMAND status. One of the 2 successful
 * command status will result in a 2-second delay start. The smaller BIT[15:14]
 * value is the correct combination.
 *
 * Since there are only 4 outcomes and the results are ordered, we can simply
 * test 2 START TRANSFER commands with BIT[15:14] combinations 'b00 and 'b01 to
 * deduce the smaller successful combination.
 *
 * Let test0 = test status क्रम combination 'b00 and test1 = test status for 'b01
 * of BIT[15:14]. The correct combination is as follow:
 *
 * अगर test0 fails and test1 passes, BIT[15:14] is 'b01
 * अगर test0 fails and test1 fails, BIT[15:14] is 'b10
 * अगर test0 passes and test1 fails, BIT[15:14] is 'b11
 * अगर test0 passes and test1 passes, BIT[15:14] is 'b00
 *
 * Synopsys STAR 9001202023: Wrong microframe number क्रम isochronous IN
 * endpoपूर्णांकs.
 */
अटल पूर्णांक dwc3_gadget_start_isoc_quirk(काष्ठा dwc3_ep *dep)
अणु
	पूर्णांक cmd_status = 0;
	bool test0;
	bool test1;

	जबतक (dep->combo_num < 2) अणु
		काष्ठा dwc3_gadget_ep_cmd_params params;
		u32 test_frame_number;
		u32 cmd;

		/*
		 * Check अगर we can start isoc transfer on the next पूर्णांकerval or
		 * 4 uframes in the future with BIT[15:14] as dep->combo_num
		 */
		test_frame_number = dep->frame_number & DWC3_FRNUMBER_MASK;
		test_frame_number |= dep->combo_num << 14;
		test_frame_number += max_t(u32, 4, dep->पूर्णांकerval);

		params.param0 = upper_32_bits(dep->dwc->bounce_addr);
		params.param1 = lower_32_bits(dep->dwc->bounce_addr);

		cmd = DWC3_DEPCMD_STARTTRANSFER;
		cmd |= DWC3_DEPCMD_PARAM(test_frame_number);
		cmd_status = dwc3_send_gadget_ep_cmd(dep, cmd, &params);

		/* Reकरो अगर some other failure beside bus-expiry is received */
		अगर (cmd_status && cmd_status != -EAGAIN) अणु
			dep->start_cmd_status = 0;
			dep->combo_num = 0;
			वापस 0;
		पूर्ण

		/* Store the first test status */
		अगर (dep->combo_num == 0)
			dep->start_cmd_status = cmd_status;

		dep->combo_num++;

		/*
		 * End the transfer अगर the START_TRANSFER command is successful
		 * to रुको क्रम the next XferNotReady to test the command again
		 */
		अगर (cmd_status == 0) अणु
			dwc3_stop_active_transfer(dep, true, true);
			वापस 0;
		पूर्ण
	पूर्ण

	/* test0 and test1 are both completed at this poपूर्णांक */
	test0 = (dep->start_cmd_status == 0);
	test1 = (cmd_status == 0);

	अगर (!test0 && test1)
		dep->combo_num = 1;
	अन्यथा अगर (!test0 && !test1)
		dep->combo_num = 2;
	अन्यथा अगर (test0 && !test1)
		dep->combo_num = 3;
	अन्यथा अगर (test0 && test1)
		dep->combo_num = 0;

	dep->frame_number &= DWC3_FRNUMBER_MASK;
	dep->frame_number |= dep->combo_num << 14;
	dep->frame_number += max_t(u32, 4, dep->पूर्णांकerval);

	/* Reinitialize test variables */
	dep->start_cmd_status = 0;
	dep->combo_num = 0;

	वापस __dwc3_gadget_kick_transfer(dep);
पूर्ण

अटल पूर्णांक __dwc3_gadget_start_isoc(काष्ठा dwc3_ep *dep)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc = dep->endpoपूर्णांक.desc;
	काष्ठा dwc3 *dwc = dep->dwc;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (list_empty(&dep->pending_list) &&
	    list_empty(&dep->started_list)) अणु
		dep->flags |= DWC3_EP_PENDING_REQUEST;
		वापस -EAGAIN;
	पूर्ण

	अगर (!dwc->dis_start_transfer_quirk &&
	    (DWC3_VER_IS_PRIOR(DWC31, 170A) ||
	     DWC3_VER_TYPE_IS_WITHIN(DWC31, 170A, EA01, EA06))) अणु
		अगर (dwc->gadget->speed <= USB_SPEED_HIGH && dep->direction)
			वापस dwc3_gadget_start_isoc_quirk(dep);
	पूर्ण

	अगर (desc->bInterval <= 14 &&
	    dwc->gadget->speed >= USB_SPEED_HIGH) अणु
		u32 frame = __dwc3_gadget_get_frame(dwc);
		bool rollover = frame <
				(dep->frame_number & DWC3_FRNUMBER_MASK);

		/*
		 * frame_number is set from XferNotReady and may be alपढ़ोy
		 * out of date. DSTS only provides the lower 14 bit of the
		 * current frame number. So add the upper two bits of
		 * frame_number and handle a possible rollover.
		 * This will provide the correct frame_number unless more than
		 * rollover has happened since XferNotReady.
		 */

		dep->frame_number = (dep->frame_number & ~DWC3_FRNUMBER_MASK) |
				     frame;
		अगर (rollover)
			dep->frame_number += BIT(14);
	पूर्ण

	क्रम (i = 0; i < DWC3_ISOC_MAX_RETRIES; i++) अणु
		dep->frame_number = DWC3_ALIGN_FRAME(dep, i + 1);

		ret = __dwc3_gadget_kick_transfer(dep);
		अगर (ret != -EAGAIN)
			अवरोध;
	पूर्ण

	/*
	 * After a number of unsuccessful start attempts due to bus-expiry
	 * status, issue END_TRANSFER command and retry on the next XferNotReady
	 * event.
	 */
	अगर (ret == -EAGAIN) अणु
		काष्ठा dwc3_gadget_ep_cmd_params params;
		u32 cmd;

		cmd = DWC3_DEPCMD_ENDTRANSFER |
			DWC3_DEPCMD_CMDIOC |
			DWC3_DEPCMD_PARAM(dep->resource_index);

		dep->resource_index = 0;
		स_रखो(&params, 0, माप(params));

		ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
		अगर (!ret)
			dep->flags |= DWC3_EP_END_TRANSFER_PENDING;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __dwc3_gadget_ep_queue(काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;

	अगर (!dep->endpoपूर्णांक.desc || !dwc->pullups_connected || !dwc->connected) अणु
		dev_err(dwc->dev, "%s: can't queue to disabled endpoint\n",
				dep->name);
		वापस -ESHUTDOWN;
	पूर्ण

	अगर (WARN(req->dep != dep, "request %pK belongs to '%s'\n",
				&req->request, req->dep->name))
		वापस -EINVAL;

	अगर (WARN(req->status < DWC3_REQUEST_STATUS_COMPLETED,
				"%s: request %pK already in flight\n",
				dep->name, &req->request))
		वापस -EINVAL;

	pm_runसमय_get(dwc->dev);

	req->request.actual	= 0;
	req->request.status	= -EINPROGRESS;

	trace_dwc3_ep_queue(req);

	list_add_tail(&req->list, &dep->pending_list);
	req->status = DWC3_REQUEST_STATUS_QUEUED;

	अगर (dep->flags & DWC3_EP_WAIT_TRANSFER_COMPLETE)
		वापस 0;

	/*
	 * Start the transfer only after the END_TRANSFER is completed
	 * and endpoपूर्णांक STALL is cleared.
	 */
	अगर ((dep->flags & DWC3_EP_END_TRANSFER_PENDING) ||
	    (dep->flags & DWC3_EP_WEDGE) ||
	    (dep->flags & DWC3_EP_STALL)) अणु
		dep->flags |= DWC3_EP_DELAY_START;
		वापस 0;
	पूर्ण

	/*
	 * NOTICE: Isochronous endpoपूर्णांकs should NEVER be prestarted. We must
	 * रुको क्रम a XferNotReady event so we will know what's the current
	 * (micro-)frame number.
	 *
	 * Without this trick, we are very, very likely gonna get Bus Expiry
	 * errors which will क्रमce us issue EndTransfer command.
	 */
	अगर (usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc)) अणु
		अगर (!(dep->flags & DWC3_EP_PENDING_REQUEST) &&
				!(dep->flags & DWC3_EP_TRANSFER_STARTED))
			वापस 0;

		अगर ((dep->flags & DWC3_EP_PENDING_REQUEST)) अणु
			अगर (!(dep->flags & DWC3_EP_TRANSFER_STARTED))
				वापस __dwc3_gadget_start_isoc(dep);
		पूर्ण
	पूर्ण

	__dwc3_gadget_kick_transfer(dep);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *request,
	gfp_t gfp_flags)
अणु
	काष्ठा dwc3_request		*req = to_dwc3_request(request);
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;

	अचिन्हित दीर्घ			flags;

	पूर्णांक				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_ep_queue(dep, req);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम dwc3_gadget_ep_skip_trbs(काष्ठा dwc3_ep *dep, काष्ठा dwc3_request *req)
अणु
	पूर्णांक i;

	/* If req->trb is not set, then the request has not started */
	अगर (!req->trb)
		वापस;

	/*
	 * If request was alपढ़ोy started, this means we had to
	 * stop the transfer. With that we also need to ignore
	 * all TRBs used by the request, however TRBs can only
	 * be modअगरied after completion of END_TRANSFER
	 * command. So what we करो here is that we रुको क्रम
	 * END_TRANSFER completion and only after that, we jump
	 * over TRBs by clearing HWO and incrementing dequeue
	 * poपूर्णांकer.
	 */
	क्रम (i = 0; i < req->num_trbs; i++) अणु
		काष्ठा dwc3_trb *trb;

		trb = &dep->trb_pool[dep->trb_dequeue];
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;
		dwc3_ep_inc_deq(dep);
	पूर्ण

	req->num_trbs = 0;
पूर्ण

अटल व्योम dwc3_gadget_ep_cleanup_cancelled_requests(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_request		*req;
	काष्ठा dwc3_request		*पंचांगp;
	काष्ठा dwc3			*dwc = dep->dwc;

	list_क्रम_each_entry_safe(req, पंचांगp, &dep->cancelled_list, list) अणु
		dwc3_gadget_ep_skip_trbs(dep, req);
		चयन (req->status) अणु
		हाल DWC3_REQUEST_STATUS_DISCONNECTED:
			dwc3_gadget_giveback(dep, req, -ESHUTDOWN);
			अवरोध;
		हाल DWC3_REQUEST_STATUS_DEQUEUED:
			dwc3_gadget_giveback(dep, req, -ECONNRESET);
			अवरोध;
		हाल DWC3_REQUEST_STATUS_STALLED:
			dwc3_gadget_giveback(dep, req, -EPIPE);
			अवरोध;
		शेष:
			dev_err(dwc->dev, "request cancelled with wrong reason:%d\n", req->status);
			dwc3_gadget_giveback(dep, req, -ECONNRESET);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_dequeue(काष्ठा usb_ep *ep,
		काष्ठा usb_request *request)
अणु
	काष्ठा dwc3_request		*req = to_dwc3_request(request);
	काष्ठा dwc3_request		*r = शून्य;

	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;

	अचिन्हित दीर्घ			flags;
	पूर्णांक				ret = 0;

	trace_dwc3_ep_dequeue(req);

	spin_lock_irqsave(&dwc->lock, flags);

	list_क्रम_each_entry(r, &dep->cancelled_list, list) अणु
		अगर (r == req)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(r, &dep->pending_list, list) अणु
		अगर (r == req) अणु
			dwc3_gadget_giveback(dep, req, -ECONNRESET);
			जाओ out;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(r, &dep->started_list, list) अणु
		अगर (r == req) अणु
			काष्ठा dwc3_request *t;

			/* रुको until it is processed */
			dwc3_stop_active_transfer(dep, true, true);

			/*
			 * Remove any started request अगर the transfer is
			 * cancelled.
			 */
			list_क्रम_each_entry_safe(r, t, &dep->started_list, list)
				dwc3_gadget_move_cancelled_request(r,
						DWC3_REQUEST_STATUS_DEQUEUED);

			dep->flags &= ~DWC3_EP_WAIT_TRANSFER_COMPLETE;

			जाओ out;
		पूर्ण
	पूर्ण

	dev_err(dwc->dev, "request %pK was not queued to %s\n",
		request, ep->name);
	ret = -EINVAL;
out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

पूर्णांक __dwc3_gadget_ep_set_halt(काष्ठा dwc3_ep *dep, पूर्णांक value, पूर्णांक protocol)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params	params;
	काष्ठा dwc3				*dwc = dep->dwc;
	काष्ठा dwc3_request			*req;
	काष्ठा dwc3_request			*पंचांगp;
	पूर्णांक					ret;

	अगर (usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc)) अणु
		dev_err(dwc->dev, "%s is of Isochronous type\n", dep->name);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&params, 0x00, माप(params));

	अगर (value) अणु
		काष्ठा dwc3_trb *trb;

		अचिन्हित पूर्णांक transfer_in_flight;
		अचिन्हित पूर्णांक started;

		अगर (dep->number > 1)
			trb = dwc3_ep_prev_trb(dep, dep->trb_enqueue);
		अन्यथा
			trb = &dwc->ep0_trb[dep->trb_enqueue];

		transfer_in_flight = trb->ctrl & DWC3_TRB_CTRL_HWO;
		started = !list_empty(&dep->started_list);

		अगर (!protocol && ((dep->direction && transfer_in_flight) ||
				(!dep->direction && started))) अणु
			वापस -EAGAIN;
		पूर्ण

		ret = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETSTALL,
				&params);
		अगर (ret)
			dev_err(dwc->dev, "failed to set STALL on %s\n",
					dep->name);
		अन्यथा
			dep->flags |= DWC3_EP_STALL;
	पूर्ण अन्यथा अणु
		/*
		 * Don't issue CLEAR_STALL command to control endpoपूर्णांकs. The
		 * controller स्वतःmatically clears the STALL when it receives
		 * the SETUP token.
		 */
		अगर (dep->number <= 1) अणु
			dep->flags &= ~(DWC3_EP_STALL | DWC3_EP_WEDGE);
			वापस 0;
		पूर्ण

		dwc3_stop_active_transfer(dep, true, true);

		list_क्रम_each_entry_safe(req, पंचांगp, &dep->started_list, list)
			dwc3_gadget_move_cancelled_request(req, DWC3_REQUEST_STATUS_STALLED);

		अगर (dep->flags & DWC3_EP_END_TRANSFER_PENDING) अणु
			dep->flags |= DWC3_EP_PENDING_CLEAR_STALL;
			वापस 0;
		पूर्ण

		dwc3_gadget_ep_cleanup_cancelled_requests(dep);

		ret = dwc3_send_clear_stall_ep_cmd(dep);
		अगर (ret) अणु
			dev_err(dwc->dev, "failed to clear STALL on %s\n",
					dep->name);
			वापस ret;
		पूर्ण

		dep->flags &= ~(DWC3_EP_STALL | DWC3_EP_WEDGE);

		अगर ((dep->flags & DWC3_EP_DELAY_START) &&
		    !usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc))
			__dwc3_gadget_kick_transfer(dep);

		dep->flags &= ~DWC3_EP_DELAY_START;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;

	अचिन्हित दीर्घ			flags;

	पूर्णांक				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_ep_set_halt(dep, value, false);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा dwc3_ep			*dep = to_dwc3_ep(ep);
	काष्ठा dwc3			*dwc = dep->dwc;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	dep->flags |= DWC3_EP_WEDGE;

	अगर (dep->number == 0 || dep->number == 1)
		ret = __dwc3_gadget_ep0_set_halt(ep, 1);
	अन्यथा
		ret = __dwc3_gadget_ep_set_halt(dep, 1, false);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

/* -------------------------------------------------------------------------- */

अटल काष्ठा usb_endpoपूर्णांक_descriptor dwc3_gadget_ep0_desc = अणु
	.bLength	= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bmAttributes	= USB_ENDPOINT_XFER_CONTROL,
पूर्ण;

अटल स्थिर काष्ठा usb_ep_ops dwc3_gadget_ep0_ops = अणु
	.enable		= dwc3_gadget_ep0_enable,
	.disable	= dwc3_gadget_ep0_disable,
	.alloc_request	= dwc3_gadget_ep_alloc_request,
	.मुक्त_request	= dwc3_gadget_ep_मुक्त_request,
	.queue		= dwc3_gadget_ep0_queue,
	.dequeue	= dwc3_gadget_ep_dequeue,
	.set_halt	= dwc3_gadget_ep0_set_halt,
	.set_wedge	= dwc3_gadget_ep_set_wedge,
पूर्ण;

अटल स्थिर काष्ठा usb_ep_ops dwc3_gadget_ep_ops = अणु
	.enable		= dwc3_gadget_ep_enable,
	.disable	= dwc3_gadget_ep_disable,
	.alloc_request	= dwc3_gadget_ep_alloc_request,
	.मुक्त_request	= dwc3_gadget_ep_मुक्त_request,
	.queue		= dwc3_gadget_ep_queue,
	.dequeue	= dwc3_gadget_ep_dequeue,
	.set_halt	= dwc3_gadget_ep_set_halt,
	.set_wedge	= dwc3_gadget_ep_set_wedge,
पूर्ण;

/* -------------------------------------------------------------------------- */

अटल पूर्णांक dwc3_gadget_get_frame(काष्ठा usb_gadget *g)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);

	वापस __dwc3_gadget_get_frame(dwc);
पूर्ण

अटल पूर्णांक __dwc3_gadget_wakeup(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक			retries;

	पूर्णांक			ret;
	u32			reg;

	u8			link_state;

	/*
	 * According to the Databook Remote wakeup request should
	 * be issued only when the device is in early suspend state.
	 *
	 * We can check that via USB Link State bits in DSTS रेजिस्टर.
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);

	link_state = DWC3_DSTS_USBLNKST(reg);

	चयन (link_state) अणु
	हाल DWC3_LINK_STATE_RESET:
	हाल DWC3_LINK_STATE_RX_DET:	/* in HS, means Early Suspend */
	हाल DWC3_LINK_STATE_U3:	/* in HS, means SUSPEND */
	हाल DWC3_LINK_STATE_U2:	/* in HS, means Sleep (L1) */
	हाल DWC3_LINK_STATE_U1:
	हाल DWC3_LINK_STATE_RESUME:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = dwc3_gadget_set_link_state(dwc, DWC3_LINK_STATE_RECOV);
	अगर (ret < 0) अणु
		dev_err(dwc->dev, "failed to put link in Recovery\n");
		वापस ret;
	पूर्ण

	/* Recent versions करो this स्वतःmatically */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 194A)) अणु
		/* ग_लिखो zeroes to Link Change Request */
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
		reg &= ~DWC3_DCTL_ULSTCHNGREQ_MASK;
		dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);
	पूर्ण

	/* poll until Link State changes to ON */
	retries = 20000;

	जबतक (retries--) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);

		/* in HS, means ON */
		अगर (DWC3_DSTS_USBLNKST(reg) == DWC3_LINK_STATE_U0)
			अवरोध;
	पूर्ण

	अगर (DWC3_DSTS_USBLNKST(reg) != DWC3_LINK_STATE_U0) अणु
		dev_err(dwc->dev, "failed to send remote wakeup\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_wakeup(काष्ठा usb_gadget *g)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;
	पूर्णांक			ret;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_wakeup(dwc);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_gadget_set_selfघातered(काष्ठा usb_gadget *g,
		पूर्णांक is_selfघातered)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	g->is_selfघातered = !!is_selfघातered;
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम dwc3_stop_active_transfers(काष्ठा dwc3 *dwc)
अणु
	u32 epnum;

	क्रम (epnum = 2; epnum < dwc->num_eps; epnum++) अणु
		काष्ठा dwc3_ep *dep;

		dep = dwc->eps[epnum];
		अगर (!dep)
			जारी;

		dwc3_हटाओ_requests(dwc, dep);
	पूर्ण
पूर्ण

अटल व्योम __dwc3_gadget_set_ssp_rate(काष्ठा dwc3 *dwc)
अणु
	क्रमागत usb_ssp_rate	ssp_rate = dwc->gadget_ssp_rate;
	u32			reg;

	अगर (ssp_rate == USB_SSP_GEN_UNKNOWN)
		ssp_rate = dwc->max_ssp_rate;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
	reg &= ~DWC3_DCFG_SPEED_MASK;
	reg &= ~DWC3_DCFG_NUMLANES(~0);

	अगर (ssp_rate == USB_SSP_GEN_1x2)
		reg |= DWC3_DCFG_SUPERSPEED;
	अन्यथा अगर (dwc->max_ssp_rate != USB_SSP_GEN_1x2)
		reg |= DWC3_DCFG_SUPERSPEED_PLUS;

	अगर (ssp_rate != USB_SSP_GEN_2x1 &&
	    dwc->max_ssp_rate != USB_SSP_GEN_2x1)
		reg |= DWC3_DCFG_NUMLANES(1);

	dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);
पूर्ण

अटल व्योम __dwc3_gadget_set_speed(काष्ठा dwc3 *dwc)
अणु
	क्रमागत usb_device_speed	speed;
	u32			reg;

	speed = dwc->gadget_max_speed;
	अगर (speed == USB_SPEED_UNKNOWN || speed > dwc->maximum_speed)
		speed = dwc->maximum_speed;

	अगर (speed == USB_SPEED_SUPER_PLUS &&
	    DWC3_IP_IS(DWC32)) अणु
		__dwc3_gadget_set_ssp_rate(dwc);
		वापस;
	पूर्ण

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
	reg &= ~(DWC3_DCFG_SPEED_MASK);

	/*
	 * WORKAROUND: DWC3 revision < 2.20a have an issue
	 * which would cause metastability state on Run/Stop
	 * bit अगर we try to क्रमce the IP to USB2-only mode.
	 *
	 * Because of that, we cannot configure the IP to any
	 * speed other than the SuperSpeed
	 *
	 * Refers to:
	 *
	 * STAR#9000525659: Clock Doमुख्य Crossing on DCTL in
	 * USB 2.0 Mode
	 */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 220A) &&
	    !dwc->dis_metastability_quirk) अणु
		reg |= DWC3_DCFG_SUPERSPEED;
	पूर्ण अन्यथा अणु
		चयन (speed) अणु
		हाल USB_SPEED_FULL:
			reg |= DWC3_DCFG_FULLSPEED;
			अवरोध;
		हाल USB_SPEED_HIGH:
			reg |= DWC3_DCFG_HIGHSPEED;
			अवरोध;
		हाल USB_SPEED_SUPER:
			reg |= DWC3_DCFG_SUPERSPEED;
			अवरोध;
		हाल USB_SPEED_SUPER_PLUS:
			अगर (DWC3_IP_IS(DWC3))
				reg |= DWC3_DCFG_SUPERSPEED;
			अन्यथा
				reg |= DWC3_DCFG_SUPERSPEED_PLUS;
			अवरोध;
		शेष:
			dev_err(dwc->dev, "invalid speed (%d)\n", speed);

			अगर (DWC3_IP_IS(DWC3))
				reg |= DWC3_DCFG_SUPERSPEED;
			अन्यथा
				reg |= DWC3_DCFG_SUPERSPEED_PLUS;
		पूर्ण
	पूर्ण

	अगर (DWC3_IP_IS(DWC32) &&
	    speed > USB_SPEED_UNKNOWN &&
	    speed < USB_SPEED_SUPER_PLUS)
		reg &= ~DWC3_DCFG_NUMLANES(~0);

	dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);
पूर्ण

अटल पूर्णांक dwc3_gadget_run_stop(काष्ठा dwc3 *dwc, पूर्णांक is_on, पूर्णांक suspend)
अणु
	u32			reg;
	u32			समयout = 500;

	अगर (pm_runसमय_suspended(dwc->dev))
		वापस 0;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	अगर (is_on) अणु
		अगर (DWC3_VER_IS_WITHIN(DWC3, ANY, 187A)) अणु
			reg &= ~DWC3_DCTL_TRGTULST_MASK;
			reg |= DWC3_DCTL_TRGTULST_RX_DET;
		पूर्ण

		अगर (!DWC3_VER_IS_PRIOR(DWC3, 194A))
			reg &= ~DWC3_DCTL_KEEP_CONNECT;
		reg |= DWC3_DCTL_RUN_STOP;

		अगर (dwc->has_hibernation)
			reg |= DWC3_DCTL_KEEP_CONNECT;

		__dwc3_gadget_set_speed(dwc);
		dwc->pullups_connected = true;
	पूर्ण अन्यथा अणु
		reg &= ~DWC3_DCTL_RUN_STOP;

		अगर (dwc->has_hibernation && !suspend)
			reg &= ~DWC3_DCTL_KEEP_CONNECT;

		dwc->pullups_connected = false;
	पूर्ण

	dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);

	करो अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);
		reg &= DWC3_DSTS_DEVCTRLHLT;
	पूर्ण जबतक (--समयout && !(!is_on ^ !reg));

	अगर (!समयout)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम dwc3_gadget_disable_irq(काष्ठा dwc3 *dwc);
अटल व्योम __dwc3_gadget_stop(काष्ठा dwc3 *dwc);
अटल पूर्णांक __dwc3_gadget_start(काष्ठा dwc3 *dwc);

अटल पूर्णांक dwc3_gadget_pullup(काष्ठा usb_gadget *g, पूर्णांक is_on)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;
	पूर्णांक			ret;

	is_on = !!is_on;

	/*
	 * Per databook, when we want to stop the gadget, अगर a control transfer
	 * is still in process, complete it and get the core पूर्णांकo setup phase.
	 */
	अगर (!is_on && dwc->ep0state != EP0_SETUP_PHASE) अणु
		reinit_completion(&dwc->ep0_in_setup);

		ret = रुको_क्रम_completion_समयout(&dwc->ep0_in_setup,
				msecs_to_jअगरfies(DWC3_PULL_UP_TIMEOUT));
		अगर (ret == 0) अणु
			dev_err(dwc->dev, "timed out waiting for SETUP phase\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/*
	 * Check the वापस value क्रम successful resume, or error.  For a
	 * successful resume, the DWC3 runसमय PM resume routine will handle
	 * the run stop sequence, so aव्योम duplicate operations here.
	 */
	ret = pm_runसमय_get_sync(dwc->dev);
	अगर (!ret || ret < 0) अणु
		pm_runसमय_put(dwc->dev);
		वापस 0;
	पूर्ण

	/*
	 * Synchronize and disable any further event handling जबतक controller
	 * is being enabled/disabled.
	 */
	disable_irq(dwc->irq_gadget);

	spin_lock_irqsave(&dwc->lock, flags);

	अगर (!is_on) अणु
		u32 count;

		dwc->connected = false;
		/*
		 * In the Synopsis DesignWare Cores USB3 Databook Rev. 3.30a
		 * Section 4.1.8 Table 4-7, it states that क्रम a device-initiated
		 * disconnect, the SW needs to ensure that it sends "a DEPENDXFER
		 * command क्रम any active transfers" beक्रमe clearing the RunStop
		 * bit.
		 */
		dwc3_stop_active_transfers(dwc);
		__dwc3_gadget_stop(dwc);

		/*
		 * In the Synopsis DesignWare Cores USB3 Databook Rev. 3.30a
		 * Section 1.3.4, it mentions that क्रम the DEVCTRLHLT bit, the
		 * "software needs to acknowledge the events that are generated
		 * (by writing to GEVNTCOUNTn) जबतक it is रुकोing क्रम this bit
		 * to be set to '1'."
		 */
		count = dwc3_पढ़ोl(dwc->regs, DWC3_GEVNTCOUNT(0));
		count &= DWC3_GEVNTCOUNT_MASK;
		अगर (count > 0) अणु
			dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTCOUNT(0), count);
			dwc->ev_buf->lpos = (dwc->ev_buf->lpos + count) %
						dwc->ev_buf->length;
		पूर्ण
	पूर्ण अन्यथा अणु
		__dwc3_gadget_start(dwc);
	पूर्ण

	ret = dwc3_gadget_run_stop(dwc, is_on, false);
	spin_unlock_irqrestore(&dwc->lock, flags);
	enable_irq(dwc->irq_gadget);

	pm_runसमय_put(dwc->dev);

	वापस ret;
पूर्ण

अटल व्योम dwc3_gadget_enable_irq(काष्ठा dwc3 *dwc)
अणु
	u32			reg;

	/* Enable all but Start and End of Frame IRQs */
	reg = (DWC3_DEVTEN_EVNTOVERFLOWEN |
			DWC3_DEVTEN_CMDCMPLTEN |
			DWC3_DEVTEN_ERRTICERREN |
			DWC3_DEVTEN_WKUPEVTEN |
			DWC3_DEVTEN_CONNECTDONEEN |
			DWC3_DEVTEN_USBRSTEN |
			DWC3_DEVTEN_DISCONNEVTEN);

	अगर (DWC3_VER_IS_PRIOR(DWC3, 250A))
		reg |= DWC3_DEVTEN_ULSTCNGEN;

	/* On 2.30a and above this bit enables U3/L2-L1 Suspend Events */
	अगर (!DWC3_VER_IS_PRIOR(DWC3, 230A))
		reg |= DWC3_DEVTEN_U3L2L1SUSPEN;

	dwc3_ग_लिखोl(dwc->regs, DWC3_DEVTEN, reg);
पूर्ण

अटल व्योम dwc3_gadget_disable_irq(काष्ठा dwc3 *dwc)
अणु
	/* mask all पूर्णांकerrupts */
	dwc3_ग_लिखोl(dwc->regs, DWC3_DEVTEN, 0x00);
पूर्ण

अटल irqवापस_t dwc3_पूर्णांकerrupt(पूर्णांक irq, व्योम *_dwc);
अटल irqवापस_t dwc3_thपढ़ो_पूर्णांकerrupt(पूर्णांक irq, व्योम *_dwc);

/**
 * dwc3_gadget_setup_nump - calculate and initialize NUMP field of %DWC3_DCFG
 * @dwc: poपूर्णांकer to our context काष्ठाure
 *
 * The following looks like complex but it's actually very simple. In order to
 * calculate the number of packets we can burst at once on OUT transfers, we're
 * gonna use RxFIFO size.
 *
 * To calculate RxFIFO size we need two numbers:
 * MDWIDTH = size, in bits, of the पूर्णांकernal memory bus
 * RAM2_DEPTH = depth, in MDWIDTH, of पूर्णांकernal RAM2 (where RxFIFO sits)
 *
 * Given these two numbers, the क्रमmula is simple:
 *
 * RxFIFO Size = (RAM2_DEPTH * MDWIDTH / 8) - 24 - 16;
 *
 * 24 bytes is क्रम 3x SETUP packets
 * 16 bytes is a घड़ी करोमुख्य crossing tolerance
 *
 * Given RxFIFO Size, NUMP = RxFIFOSize / 1024;
 */
अटल व्योम dwc3_gadget_setup_nump(काष्ठा dwc3 *dwc)
अणु
	u32 ram2_depth;
	u32 mdwidth;
	u32 nump;
	u32 reg;

	ram2_depth = DWC3_GHWPARAMS7_RAM2_DEPTH(dwc->hwparams.hwparams7);
	mdwidth = dwc3_mdwidth(dwc);

	nump = ((ram2_depth * mdwidth / 8) - 24 - 16) / 1024;
	nump = min_t(u32, nump, 16);

	/* update NumP */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
	reg &= ~DWC3_DCFG_NUMP_MASK;
	reg |= nump << DWC3_DCFG_NUMP_SHIFT;
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);
पूर्ण

अटल पूर्णांक __dwc3_gadget_start(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_ep		*dep;
	पूर्णांक			ret = 0;
	u32			reg;

	/*
	 * Use IMOD अगर enabled via dwc->imod_पूर्णांकerval. Otherwise, अगर
	 * the core supports IMOD, disable it.
	 */
	अगर (dwc->imod_पूर्णांकerval) अणु
		dwc3_ग_लिखोl(dwc->regs, DWC3_DEV_IMOD(0), dwc->imod_पूर्णांकerval);
		dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTCOUNT(0), DWC3_GEVNTCOUNT_EHB);
	पूर्ण अन्यथा अगर (dwc3_has_imod(dwc)) अणु
		dwc3_ग_लिखोl(dwc->regs, DWC3_DEV_IMOD(0), 0);
	पूर्ण

	/*
	 * We are telling dwc3 that we want to use DCFG.NUMP as ACK TP's NUMP
	 * field instead of letting dwc3 itself calculate that स्वतःmatically.
	 *
	 * This way, we maximize the chances that we'll be able to get several
	 * bursts of data without going through any sort of endpoपूर्णांक throttling.
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GRXTHRCFG);
	अगर (DWC3_IP_IS(DWC3))
		reg &= ~DWC3_GRXTHRCFG_PKTCNTSEL;
	अन्यथा
		reg &= ~DWC31_GRXTHRCFG_PKTCNTSEL;

	dwc3_ग_लिखोl(dwc->regs, DWC3_GRXTHRCFG, reg);

	dwc3_gadget_setup_nump(dwc);

	/*
	 * Currently the controller handles single stream only. So, Ignore
	 * Packet Pending bit क्रम stream selection and करोn't search क्रम another
	 * stream अगर the host sends Data Packet with PP=0 (क्रम OUT direction) or
	 * ACK with NumP=0 and PP=0 (क्रम IN direction). This slightly improves
	 * the stream perक्रमmance.
	 */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
	reg |= DWC3_DCFG_IGNSTRMPP;
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);

	/* Start with SuperSpeed Default */
	dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);

	dep = dwc->eps[0];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_INIT);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		जाओ err0;
	पूर्ण

	dep = dwc->eps[1];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_INIT);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		जाओ err1;
	पूर्ण

	/* begin to receive SETUP packets */
	dwc->ep0state = EP0_SETUP_PHASE;
	dwc->link_state = DWC3_LINK_STATE_SS_DIS;
	dwc3_ep0_out_start(dwc);

	dwc3_gadget_enable_irq(dwc);

	वापस 0;

err1:
	__dwc3_gadget_ep_disable(dwc->eps[0]);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_gadget_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;
	पूर्णांक			ret;
	पूर्णांक			irq;

	irq = dwc->irq_gadget;
	ret = request_thपढ़ोed_irq(irq, dwc3_पूर्णांकerrupt, dwc3_thपढ़ो_पूर्णांकerrupt,
			IRQF_SHARED, "dwc3", dwc->ev_buf);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to request irq #%d --> %d\n",
				irq, ret);
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->gadget_driver	= driver;
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम __dwc3_gadget_stop(काष्ठा dwc3 *dwc)
अणु
	dwc3_gadget_disable_irq(dwc);
	__dwc3_gadget_ep_disable(dwc->eps[0]);
	__dwc3_gadget_ep_disable(dwc->eps[1]);
पूर्ण

अटल पूर्णांक dwc3_gadget_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->gadget_driver	= शून्य;
	spin_unlock_irqrestore(&dwc->lock, flags);

	मुक्त_irq(dwc->irq_gadget, dwc->ev_buf);

	वापस 0;
पूर्ण

अटल व्योम dwc3_gadget_config_params(काष्ठा usb_gadget *g,
				      काष्ठा usb_dcd_config_params *params)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);

	params->besl_baseline = USB_DEFAULT_BESL_UNSPECIFIED;
	params->besl_deep = USB_DEFAULT_BESL_UNSPECIFIED;

	/* Recommended BESL */
	अगर (!dwc->dis_enblslpm_quirk) अणु
		/*
		 * If the recommended BESL baseline is 0 or अगर the BESL deep is
		 * less than 2, Microsoft's Winकरोws 10 host usb stack will issue
		 * a usb reset immediately after it receives the extended BOS
		 * descriptor and the क्रमागतeration will fail. To मुख्यtain
		 * compatibility with the Winकरोws' usb stack, let's set the
		 * recommended BESL baseline to 1 and clamp the BESL deep to be
		 * within 2 to 15.
		 */
		params->besl_baseline = 1;
		अगर (dwc->is_uपंचांगi_l1_suspend)
			params->besl_deep =
				clamp_t(u8, dwc->hird_threshold, 2, 15);
	पूर्ण

	/* U1 Device निकास Latency */
	अगर (dwc->dis_u1_entry_quirk)
		params->bU1devExitLat = 0;
	अन्यथा
		params->bU1devExitLat = DWC3_DEFAULT_U1_DEV_EXIT_LAT;

	/* U2 Device निकास Latency */
	अगर (dwc->dis_u2_entry_quirk)
		params->bU2DevExitLat = 0;
	अन्यथा
		params->bU2DevExitLat =
				cpu_to_le16(DWC3_DEFAULT_U2_DEV_EXIT_LAT);
पूर्ण

अटल व्योम dwc3_gadget_set_speed(काष्ठा usb_gadget *g,
				  क्रमागत usb_device_speed speed)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->gadget_max_speed = speed;
	spin_unlock_irqrestore(&dwc->lock, flags);
पूर्ण

अटल व्योम dwc3_gadget_set_ssp_rate(काष्ठा usb_gadget *g,
				     क्रमागत usb_ssp_rate rate)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc->gadget_max_speed = USB_SPEED_SUPER_PLUS;
	dwc->gadget_ssp_rate = rate;
	spin_unlock_irqrestore(&dwc->lock, flags);
पूर्ण

अटल पूर्णांक dwc3_gadget_vbus_draw(काष्ठा usb_gadget *g, अचिन्हित पूर्णांक mA)
अणु
	काष्ठा dwc3		*dwc = gadget_to_dwc(g);
	जोड़ घातer_supply_propval	val = अणु0पूर्ण;
	पूर्णांक				ret;

	अगर (dwc->usb2_phy)
		वापस usb_phy_set_घातer(dwc->usb2_phy, mA);

	अगर (!dwc->usb_psy)
		वापस -EOPNOTSUPP;

	val.पूर्णांकval = 1000 * mA;
	ret = घातer_supply_set_property(dwc->usb_psy, POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT, &val);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops dwc3_gadget_ops = अणु
	.get_frame		= dwc3_gadget_get_frame,
	.wakeup			= dwc3_gadget_wakeup,
	.set_selfघातered	= dwc3_gadget_set_selfघातered,
	.pullup			= dwc3_gadget_pullup,
	.udc_start		= dwc3_gadget_start,
	.udc_stop		= dwc3_gadget_stop,
	.udc_set_speed		= dwc3_gadget_set_speed,
	.udc_set_ssp_rate	= dwc3_gadget_set_ssp_rate,
	.get_config_params	= dwc3_gadget_config_params,
	.vbus_draw		= dwc3_gadget_vbus_draw,
पूर्ण;

/* -------------------------------------------------------------------------- */

अटल पूर्णांक dwc3_gadget_init_control_endpoपूर्णांक(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3 *dwc = dep->dwc;

	usb_ep_set_maxpacket_limit(&dep->endpoपूर्णांक, 512);
	dep->endpoपूर्णांक.maxburst = 1;
	dep->endpoपूर्णांक.ops = &dwc3_gadget_ep0_ops;
	अगर (!dep->direction)
		dwc->gadget->ep0 = &dep->endpoपूर्णांक;

	dep->endpoपूर्णांक.caps.type_control = true;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_init_in_endpoपूर्णांक(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3 *dwc = dep->dwc;
	u32 mdwidth;
	पूर्णांक size;

	mdwidth = dwc3_mdwidth(dwc);

	/* MDWIDTH is represented in bits, we need it in bytes */
	mdwidth /= 8;

	size = dwc3_पढ़ोl(dwc->regs, DWC3_GTXFIFOSIZ(dep->number >> 1));
	अगर (DWC3_IP_IS(DWC3))
		size = DWC3_GTXFIFOSIZ_TXFDEP(size);
	अन्यथा
		size = DWC31_GTXFIFOSIZ_TXFDEP(size);

	/* FIFO Depth is in MDWDITH bytes. Multiply */
	size *= mdwidth;

	/*
	 * To meet perक्रमmance requirement, a minimum TxFIFO size of 3x
	 * MaxPacketSize is recommended क्रम endpoपूर्णांकs that support burst and a
	 * minimum TxFIFO size of 2x MaxPacketSize क्रम endpoपूर्णांकs that करोn't
	 * support burst. Use those numbers and we can calculate the max packet
	 * limit as below.
	 */
	अगर (dwc->maximum_speed >= USB_SPEED_SUPER)
		size /= 3;
	अन्यथा
		size /= 2;

	usb_ep_set_maxpacket_limit(&dep->endpoपूर्णांक, size);

	dep->endpoपूर्णांक.max_streams = 16;
	dep->endpoपूर्णांक.ops = &dwc3_gadget_ep_ops;
	list_add_tail(&dep->endpoपूर्णांक.ep_list,
			&dwc->gadget->ep_list);
	dep->endpoपूर्णांक.caps.type_iso = true;
	dep->endpoपूर्णांक.caps.type_bulk = true;
	dep->endpoपूर्णांक.caps.type_पूर्णांक = true;

	वापस dwc3_alloc_trb_pool(dep);
पूर्ण

अटल पूर्णांक dwc3_gadget_init_out_endpoपूर्णांक(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3 *dwc = dep->dwc;
	u32 mdwidth;
	पूर्णांक size;

	mdwidth = dwc3_mdwidth(dwc);

	/* MDWIDTH is represented in bits, convert to bytes */
	mdwidth /= 8;

	/* All OUT endpoपूर्णांकs share a single RxFIFO space */
	size = dwc3_पढ़ोl(dwc->regs, DWC3_GRXFIFOSIZ(0));
	अगर (DWC3_IP_IS(DWC3))
		size = DWC3_GRXFIFOSIZ_RXFDEP(size);
	अन्यथा
		size = DWC31_GRXFIFOSIZ_RXFDEP(size);

	/* FIFO depth is in MDWDITH bytes */
	size *= mdwidth;

	/*
	 * To meet perक्रमmance requirement, a minimum recommended RxFIFO size
	 * is defined as follow:
	 * RxFIFO size >= (3 x MaxPacketSize) +
	 * (3 x 8 bytes setup packets size) + (16 bytes घड़ी crossing margin)
	 *
	 * Then calculate the max packet limit as below.
	 */
	size -= (3 * 8) + 16;
	अगर (size < 0)
		size = 0;
	अन्यथा
		size /= 3;

	usb_ep_set_maxpacket_limit(&dep->endpoपूर्णांक, size);
	dep->endpoपूर्णांक.max_streams = 16;
	dep->endpoपूर्णांक.ops = &dwc3_gadget_ep_ops;
	list_add_tail(&dep->endpoपूर्णांक.ep_list,
			&dwc->gadget->ep_list);
	dep->endpoपूर्णांक.caps.type_iso = true;
	dep->endpoपूर्णांक.caps.type_bulk = true;
	dep->endpoपूर्णांक.caps.type_पूर्णांक = true;

	वापस dwc3_alloc_trb_pool(dep);
पूर्ण

अटल पूर्णांक dwc3_gadget_init_endpoपूर्णांक(काष्ठा dwc3 *dwc, u8 epnum)
अणु
	काष्ठा dwc3_ep			*dep;
	bool				direction = epnum & 1;
	पूर्णांक				ret;
	u8				num = epnum >> 1;

	dep = kzalloc(माप(*dep), GFP_KERNEL);
	अगर (!dep)
		वापस -ENOMEM;

	dep->dwc = dwc;
	dep->number = epnum;
	dep->direction = direction;
	dep->regs = dwc->regs + DWC3_DEP_BASE(epnum);
	dwc->eps[epnum] = dep;
	dep->combo_num = 0;
	dep->start_cmd_status = 0;

	snम_लिखो(dep->name, माप(dep->name), "ep%u%s", num,
			direction ? "in" : "out");

	dep->endpoपूर्णांक.name = dep->name;

	अगर (!(dep->number > 1)) अणु
		dep->endpoपूर्णांक.desc = &dwc3_gadget_ep0_desc;
		dep->endpoपूर्णांक.comp_desc = शून्य;
	पूर्ण

	अगर (num == 0)
		ret = dwc3_gadget_init_control_endpoपूर्णांक(dep);
	अन्यथा अगर (direction)
		ret = dwc3_gadget_init_in_endpoपूर्णांक(dep);
	अन्यथा
		ret = dwc3_gadget_init_out_endpoपूर्णांक(dep);

	अगर (ret)
		वापस ret;

	dep->endpoपूर्णांक.caps.dir_in = direction;
	dep->endpoपूर्णांक.caps.dir_out = !direction;

	INIT_LIST_HEAD(&dep->pending_list);
	INIT_LIST_HEAD(&dep->started_list);
	INIT_LIST_HEAD(&dep->cancelled_list);

	dwc3_debugfs_create_endpoपूर्णांक_dir(dep);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_init_endpoपूर्णांकs(काष्ठा dwc3 *dwc, u8 total)
अणु
	u8				epnum;

	INIT_LIST_HEAD(&dwc->gadget->ep_list);

	क्रम (epnum = 0; epnum < total; epnum++) अणु
		पूर्णांक			ret;

		ret = dwc3_gadget_init_endpoपूर्णांक(dwc, epnum);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc3_gadget_मुक्त_endpoपूर्णांकs(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_ep			*dep;
	u8				epnum;

	क्रम (epnum = 0; epnum < DWC3_ENDPOINTS_NUM; epnum++) अणु
		dep = dwc->eps[epnum];
		अगर (!dep)
			जारी;
		/*
		 * Physical endpoपूर्णांकs 0 and 1 are special; they क्रमm the
		 * bi-directional USB endpoपूर्णांक 0.
		 *
		 * For those two physical endpoपूर्णांकs, we करोn't allocate a TRB
		 * pool nor करो we add them the endpoपूर्णांकs list. Due to that, we
		 * shouldn't करो these two operations otherwise we would end up
		 * with all sorts of bugs when removing dwc3.ko.
		 */
		अगर (epnum != 0 && epnum != 1) अणु
			dwc3_मुक्त_trb_pool(dep);
			list_del(&dep->endpoपूर्णांक.ep_list);
		पूर्ण

		debugfs_हटाओ_recursive(debugfs_lookup(dep->name, dwc->root));
		kमुक्त(dep);
	पूर्ण
पूर्ण

/* -------------------------------------------------------------------------- */

अटल पूर्णांक dwc3_gadget_ep_reclaim_completed_trb(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req, काष्ठा dwc3_trb *trb,
		स्थिर काष्ठा dwc3_event_depevt *event, पूर्णांक status, पूर्णांक chain)
अणु
	अचिन्हित पूर्णांक		count;

	dwc3_ep_inc_deq(dep);

	trace_dwc3_complete_trb(dep, trb);
	req->num_trbs--;

	/*
	 * If we're in the middle of series of chained TRBs and we
	 * receive a लघु transfer aदीर्घ the way, DWC3 will skip
	 * through all TRBs including the last TRB in the chain (the
	 * where CHN bit is zero. DWC3 will also aव्योम clearing HWO
	 * bit and SW has to करो it manually.
	 *
	 * We're going to करो that here to aव्योम problems of HW trying
	 * to use bogus TRBs क्रम transfers.
	 */
	अगर (chain && (trb->ctrl & DWC3_TRB_CTRL_HWO))
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;

	/*
	 * For isochronous transfers, the first TRB in a service पूर्णांकerval must
	 * have the Isoc-First type. Track and report its पूर्णांकerval frame number.
	 */
	अगर (usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc) &&
	    (trb->ctrl & DWC3_TRBCTL_ISOCHRONOUS_FIRST)) अणु
		अचिन्हित पूर्णांक frame_number;

		frame_number = DWC3_TRB_CTRL_GET_SID_SOFN(trb->ctrl);
		frame_number &= ~(dep->पूर्णांकerval - 1);
		req->request.frame_number = frame_number;
	पूर्ण

	/*
	 * We use bounce buffer क्रम requests that needs extra TRB or OUT ZLP. If
	 * this TRB poपूर्णांकs to the bounce buffer address, it's a MPS alignment
	 * TRB. Don't add it to req->reमुख्यing calculation.
	 */
	अगर (trb->bpl == lower_32_bits(dep->dwc->bounce_addr) &&
	    trb->bph == upper_32_bits(dep->dwc->bounce_addr)) अणु
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;
		वापस 1;
	पूर्ण

	count = trb->size & DWC3_TRB_SIZE_MASK;
	req->reमुख्यing += count;

	अगर ((trb->ctrl & DWC3_TRB_CTRL_HWO) && status != -ESHUTDOWN)
		वापस 1;

	अगर (event->status & DEPEVT_STATUS_SHORT && !chain)
		वापस 1;

	अगर ((trb->ctrl & DWC3_TRB_CTRL_IOC) ||
	    (trb->ctrl & DWC3_TRB_CTRL_LST))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_reclaim_trb_sg(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req, स्थिर काष्ठा dwc3_event_depevt *event,
		पूर्णांक status)
अणु
	काष्ठा dwc3_trb *trb = &dep->trb_pool[dep->trb_dequeue];
	काष्ठा scatterlist *sg = req->sg;
	काष्ठा scatterlist *s;
	अचिन्हित पूर्णांक num_queued = req->num_queued_sgs;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम_each_sg(sg, s, num_queued, i) अणु
		trb = &dep->trb_pool[dep->trb_dequeue];

		req->sg = sg_next(s);
		req->num_queued_sgs--;

		ret = dwc3_gadget_ep_reclaim_completed_trb(dep, req,
				trb, event, status, true);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_reclaim_trb_linear(काष्ठा dwc3_ep *dep,
		काष्ठा dwc3_request *req, स्थिर काष्ठा dwc3_event_depevt *event,
		पूर्णांक status)
अणु
	काष्ठा dwc3_trb *trb = &dep->trb_pool[dep->trb_dequeue];

	वापस dwc3_gadget_ep_reclaim_completed_trb(dep, req, trb,
			event, status, false);
पूर्ण

अटल bool dwc3_gadget_ep_request_completed(काष्ठा dwc3_request *req)
अणु
	वापस req->num_pending_sgs == 0 && req->num_queued_sgs == 0;
पूर्ण

अटल पूर्णांक dwc3_gadget_ep_cleanup_completed_request(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event,
		काष्ठा dwc3_request *req, पूर्णांक status)
अणु
	पूर्णांक ret;

	अगर (req->request.num_mapped_sgs)
		ret = dwc3_gadget_ep_reclaim_trb_sg(dep, req, event,
				status);
	अन्यथा
		ret = dwc3_gadget_ep_reclaim_trb_linear(dep, req, event,
				status);

	req->request.actual = req->request.length - req->reमुख्यing;

	अगर (!dwc3_gadget_ep_request_completed(req))
		जाओ out;

	अगर (req->needs_extra_trb) अणु
		ret = dwc3_gadget_ep_reclaim_trb_linear(dep, req, event,
				status);
		req->needs_extra_trb = false;
	पूर्ण

	dwc3_gadget_giveback(dep, req, status);

out:
	वापस ret;
पूर्ण

अटल व्योम dwc3_gadget_ep_cleanup_completed_requests(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event, पूर्णांक status)
अणु
	काष्ठा dwc3_request	*req;
	काष्ठा dwc3_request	*पंचांगp;

	list_क्रम_each_entry_safe(req, पंचांगp, &dep->started_list, list) अणु
		पूर्णांक ret;

		ret = dwc3_gadget_ep_cleanup_completed_request(dep, event,
				req, status);
		अगर (ret)
			अवरोध;
	पूर्ण
पूर्ण

अटल bool dwc3_gadget_ep_should_जारी(काष्ठा dwc3_ep *dep)
अणु
	काष्ठा dwc3_request	*req;
	काष्ठा dwc3		*dwc = dep->dwc;

	अगर (!dep->endpoपूर्णांक.desc || !dwc->pullups_connected ||
	    !dwc->connected)
		वापस false;

	अगर (!list_empty(&dep->pending_list))
		वापस true;

	/*
	 * We only need to check the first entry of the started list. We can
	 * assume the completed requests are हटाओd from the started list.
	 */
	req = next_request(&dep->started_list);
	अगर (!req)
		वापस false;

	वापस !dwc3_gadget_ep_request_completed(req);
पूर्ण

अटल व्योम dwc3_gadget_endpoपूर्णांक_frame_from_event(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	dep->frame_number = event->parameters;
पूर्ण

अटल bool dwc3_gadget_endpoपूर्णांक_trbs_complete(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event, पूर्णांक status)
अणु
	काष्ठा dwc3		*dwc = dep->dwc;
	bool			no_started_trb = true;

	dwc3_gadget_ep_cleanup_completed_requests(dep, event, status);

	अगर (dep->flags & DWC3_EP_END_TRANSFER_PENDING)
		जाओ out;

	अगर (usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc) &&
		list_empty(&dep->started_list) &&
		(list_empty(&dep->pending_list) || status == -EXDEV))
		dwc3_stop_active_transfer(dep, true, true);
	अन्यथा अगर (dwc3_gadget_ep_should_जारी(dep))
		अगर (__dwc3_gadget_kick_transfer(dep) == 0)
			no_started_trb = false;

out:
	/*
	 * WORKAROUND: This is the 2nd half of U1/U2 -> U0 workaround.
	 * See dwc3_gadget_linksts_change_पूर्णांकerrupt() क्रम 1st half.
	 */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 183A)) अणु
		u32		reg;
		पूर्णांक		i;

		क्रम (i = 0; i < DWC3_ENDPOINTS_NUM; i++) अणु
			dep = dwc->eps[i];

			अगर (!(dep->flags & DWC3_EP_ENABLED))
				जारी;

			अगर (!list_empty(&dep->started_list))
				वापस no_started_trb;
		पूर्ण

		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
		reg |= dwc->u1u2;
		dwc3_ग_लिखोl(dwc->regs, DWC3_DCTL, reg);

		dwc->u1u2 = 0;
	पूर्ण

	वापस no_started_trb;
पूर्ण

अटल व्योम dwc3_gadget_endpoपूर्णांक_transfer_in_progress(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	पूर्णांक status = 0;

	अगर (usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc))
		dwc3_gadget_endpoपूर्णांक_frame_from_event(dep, event);

	अगर (event->status & DEPEVT_STATUS_BUSERR)
		status = -ECONNRESET;

	अगर (event->status & DEPEVT_STATUS_MISSED_ISOC)
		status = -EXDEV;

	dwc3_gadget_endpoपूर्णांक_trbs_complete(dep, event, status);
पूर्ण

अटल व्योम dwc3_gadget_endpoपूर्णांक_transfer_complete(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	पूर्णांक status = 0;

	dep->flags &= ~DWC3_EP_TRANSFER_STARTED;

	अगर (event->status & DEPEVT_STATUS_BUSERR)
		status = -ECONNRESET;

	अगर (dwc3_gadget_endpoपूर्णांक_trbs_complete(dep, event, status))
		dep->flags &= ~DWC3_EP_WAIT_TRANSFER_COMPLETE;
पूर्ण

अटल व्योम dwc3_gadget_endpoपूर्णांक_transfer_not_पढ़ोy(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	dwc3_gadget_endpoपूर्णांक_frame_from_event(dep, event);

	/*
	 * The XferNotReady event is generated only once beक्रमe the endpoपूर्णांक
	 * starts. It will be generated again when END_TRANSFER command is
	 * issued. For some controller versions, the XferNotReady event may be
	 * generated जबतक the END_TRANSFER command is still in process. Ignore
	 * it and रुको क्रम the next XferNotReady event after the command is
	 * completed.
	 */
	अगर (dep->flags & DWC3_EP_END_TRANSFER_PENDING)
		वापस;

	(व्योम) __dwc3_gadget_start_isoc(dep);
पूर्ण

अटल व्योम dwc3_gadget_endpoपूर्णांक_command_complete(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	u8 cmd = DEPEVT_PARAMETER_CMD(event->parameters);

	अगर (cmd != DWC3_DEPCMD_ENDTRANSFER)
		वापस;

	dep->flags &= ~DWC3_EP_END_TRANSFER_PENDING;
	dep->flags &= ~DWC3_EP_TRANSFER_STARTED;
	dwc3_gadget_ep_cleanup_cancelled_requests(dep);

	अगर (dep->flags & DWC3_EP_PENDING_CLEAR_STALL) अणु
		काष्ठा dwc3 *dwc = dep->dwc;

		dep->flags &= ~DWC3_EP_PENDING_CLEAR_STALL;
		अगर (dwc3_send_clear_stall_ep_cmd(dep)) अणु
			काष्ठा usb_ep *ep0 = &dwc->eps[0]->endpoपूर्णांक;

			dev_err(dwc->dev, "failed to clear STALL on %s\n", dep->name);
			अगर (dwc->delayed_status)
				__dwc3_gadget_ep0_set_halt(ep0, 1);
			वापस;
		पूर्ण

		dep->flags &= ~(DWC3_EP_STALL | DWC3_EP_WEDGE);
		अगर (dwc->delayed_status)
			dwc3_ep0_send_delayed_status(dwc);
	पूर्ण

	अगर ((dep->flags & DWC3_EP_DELAY_START) &&
	    !usb_endpoपूर्णांक_xfer_isoc(dep->endpoपूर्णांक.desc))
		__dwc3_gadget_kick_transfer(dep);

	dep->flags &= ~DWC3_EP_DELAY_START;
पूर्ण

अटल व्योम dwc3_gadget_endpoपूर्णांक_stream_event(काष्ठा dwc3_ep *dep,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3 *dwc = dep->dwc;

	अगर (event->status == DEPEVT_STREAMEVT_FOUND) अणु
		dep->flags |= DWC3_EP_FIRST_STREAM_PRIMED;
		जाओ out;
	पूर्ण

	/* Note: NoStream rejection event param value is 0 and not 0xFFFF */
	चयन (event->parameters) अणु
	हाल DEPEVT_STREAM_PRIME:
		/*
		 * If the host can properly transition the endpoपूर्णांक state from
		 * idle to prime after a NoStream rejection, there's no need to
		 * क्रमce restarting the endpoपूर्णांक to reinitiate the stream. To
		 * simplअगरy the check, assume the host follows the USB spec अगर
		 * it primed the endpoपूर्णांक more than once.
		 */
		अगर (dep->flags & DWC3_EP_FORCE_RESTART_STREAM) अणु
			अगर (dep->flags & DWC3_EP_FIRST_STREAM_PRIMED)
				dep->flags &= ~DWC3_EP_FORCE_RESTART_STREAM;
			अन्यथा
				dep->flags |= DWC3_EP_FIRST_STREAM_PRIMED;
		पूर्ण

		अवरोध;
	हाल DEPEVT_STREAM_NOSTREAM:
		अगर ((dep->flags & DWC3_EP_IGNORE_NEXT_NOSTREAM) ||
		    !(dep->flags & DWC3_EP_FORCE_RESTART_STREAM) ||
		    !(dep->flags & DWC3_EP_WAIT_TRANSFER_COMPLETE))
			अवरोध;

		/*
		 * If the host rejects a stream due to no active stream, by the
		 * USB and xHCI spec, the endpoपूर्णांक will be put back to idle
		 * state. When the host is पढ़ोy (buffer added/updated), it will
		 * prime the endpoपूर्णांक to inक्रमm the usb device controller. This
		 * triggers the device controller to issue ERDY to restart the
		 * stream. However, some hosts करोn't follow this and keep the
		 * endpoपूर्णांक in the idle state. No prime will come despite host
		 * streams are updated, and the device controller will not be
		 * triggered to generate ERDY to move the next stream data. To
		 * workaround this and मुख्यtain compatibility with various
		 * hosts, क्रमce to reinitate the stream until the host is पढ़ोy
		 * instead of रुकोing क्रम the host to prime the endpoपूर्णांक.
		 */
		अगर (DWC3_VER_IS_WITHIN(DWC32, 100A, ANY)) अणु
			अचिन्हित पूर्णांक cmd = DWC3_DGCMD_SET_ENDPOINT_PRIME;

			dwc3_send_gadget_generic_command(dwc, cmd, dep->number);
		पूर्ण अन्यथा अणु
			dep->flags |= DWC3_EP_DELAY_START;
			dwc3_stop_active_transfer(dep, true, true);
			वापस;
		पूर्ण
		अवरोध;
	पूर्ण

out:
	dep->flags &= ~DWC3_EP_IGNORE_NEXT_NOSTREAM;
पूर्ण

अटल व्योम dwc3_endpoपूर्णांक_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_depevt *event)
अणु
	काष्ठा dwc3_ep		*dep;
	u8			epnum = event->endpoपूर्णांक_number;

	dep = dwc->eps[epnum];

	अगर (!(dep->flags & DWC3_EP_ENABLED)) अणु
		अगर (!(dep->flags & DWC3_EP_TRANSFER_STARTED))
			वापस;

		/* Handle only EPCMDCMPLT when EP disabled */
		अगर (event->endpoपूर्णांक_event != DWC3_DEPEVT_EPCMDCMPLT)
			वापस;
	पूर्ण

	अगर (epnum == 0 || epnum == 1) अणु
		dwc3_ep0_पूर्णांकerrupt(dwc, event);
		वापस;
	पूर्ण

	चयन (event->endpoपूर्णांक_event) अणु
	हाल DWC3_DEPEVT_XFERINPROGRESS:
		dwc3_gadget_endpoपूर्णांक_transfer_in_progress(dep, event);
		अवरोध;
	हाल DWC3_DEPEVT_XFERNOTREADY:
		dwc3_gadget_endpoपूर्णांक_transfer_not_पढ़ोy(dep, event);
		अवरोध;
	हाल DWC3_DEPEVT_EPCMDCMPLT:
		dwc3_gadget_endpoपूर्णांक_command_complete(dep, event);
		अवरोध;
	हाल DWC3_DEPEVT_XFERCOMPLETE:
		dwc3_gadget_endpoपूर्णांक_transfer_complete(dep, event);
		अवरोध;
	हाल DWC3_DEPEVT_STREAMEVT:
		dwc3_gadget_endpoपूर्णांक_stream_event(dep, event);
		अवरोध;
	हाल DWC3_DEPEVT_RXTXFIFOEVT:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dwc3_disconnect_gadget(काष्ठा dwc3 *dwc)
अणु
	अगर (dwc->gadget_driver && dwc->gadget_driver->disconnect) अणु
		spin_unlock(&dwc->lock);
		dwc->gadget_driver->disconnect(dwc->gadget);
		spin_lock(&dwc->lock);
	पूर्ण
पूर्ण

अटल व्योम dwc3_suspend_gadget(काष्ठा dwc3 *dwc)
अणु
	अगर (dwc->gadget_driver && dwc->gadget_driver->suspend) अणु
		spin_unlock(&dwc->lock);
		dwc->gadget_driver->suspend(dwc->gadget);
		spin_lock(&dwc->lock);
	पूर्ण
पूर्ण

अटल व्योम dwc3_resume_gadget(काष्ठा dwc3 *dwc)
अणु
	अगर (dwc->gadget_driver && dwc->gadget_driver->resume) अणु
		spin_unlock(&dwc->lock);
		dwc->gadget_driver->resume(dwc->gadget);
		spin_lock(&dwc->lock);
	पूर्ण
पूर्ण

अटल व्योम dwc3_reset_gadget(काष्ठा dwc3 *dwc)
अणु
	अगर (!dwc->gadget_driver)
		वापस;

	अगर (dwc->gadget->speed != USB_SPEED_UNKNOWN) अणु
		spin_unlock(&dwc->lock);
		usb_gadget_udc_reset(dwc->gadget, dwc->gadget_driver);
		spin_lock(&dwc->lock);
	पूर्ण
पूर्ण

अटल व्योम dwc3_stop_active_transfer(काष्ठा dwc3_ep *dep, bool क्रमce,
	bool पूर्णांकerrupt)
अणु
	काष्ठा dwc3_gadget_ep_cmd_params params;
	u32 cmd;
	पूर्णांक ret;

	अगर (!(dep->flags & DWC3_EP_TRANSFER_STARTED) ||
	    (dep->flags & DWC3_EP_END_TRANSFER_PENDING))
		वापस;

	/*
	 * NOTICE: We are violating what the Databook says about the
	 * EndTransfer command. Ideally we would _always_ रुको क्रम the
	 * EndTransfer Command Completion IRQ, but that's causing too
	 * much trouble synchronizing between us and gadget driver.
	 *
	 * We have discussed this with the IP Provider and it was
	 * suggested to giveback all requests here.
	 *
	 * Note also that a similar handling was tested by Synopsys
	 * (thanks a lot Paul) and nothing bad has come out of it.
	 * In लघु, what we're करोing is issuing EndTransfer with
	 * CMDIOC bit set and delay kicking transfer until the
	 * EndTransfer command had completed.
	 *
	 * As of IP version 3.10a of the DWC_usb3 IP, the controller
	 * supports a mode to work around the above limitation. The
	 * software can poll the CMDACT bit in the DEPCMD रेजिस्टर
	 * after issuing a EndTransfer command. This mode is enabled
	 * by writing GUCTL2[14]. This polling is alपढ़ोy करोne in the
	 * dwc3_send_gadget_ep_cmd() function so अगर the mode is
	 * enabled, the EndTransfer command will have completed upon
	 * वापसing from this function.
	 *
	 * This mode is NOT available on the DWC_usb31 IP.
	 */

	cmd = DWC3_DEPCMD_ENDTRANSFER;
	cmd |= क्रमce ? DWC3_DEPCMD_HIPRI_FORCERM : 0;
	cmd |= पूर्णांकerrupt ? DWC3_DEPCMD_CMDIOC : 0;
	cmd |= DWC3_DEPCMD_PARAM(dep->resource_index);
	स_रखो(&params, 0, माप(params));
	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	WARN_ON_ONCE(ret);
	dep->resource_index = 0;

	/*
	 * The END_TRANSFER command will cause the controller to generate a
	 * NoStream Event, and it's not due to the host DP NoStream rejection.
	 * Ignore the next NoStream event.
	 */
	अगर (dep->stream_capable)
		dep->flags |= DWC3_EP_IGNORE_NEXT_NOSTREAM;

	अगर (!पूर्णांकerrupt)
		dep->flags &= ~DWC3_EP_TRANSFER_STARTED;
	अन्यथा
		dep->flags |= DWC3_EP_END_TRANSFER_PENDING;
पूर्ण

अटल व्योम dwc3_clear_stall_all_ep(काष्ठा dwc3 *dwc)
अणु
	u32 epnum;

	क्रम (epnum = 1; epnum < DWC3_ENDPOINTS_NUM; epnum++) अणु
		काष्ठा dwc3_ep *dep;
		पूर्णांक ret;

		dep = dwc->eps[epnum];
		अगर (!dep)
			जारी;

		अगर (!(dep->flags & DWC3_EP_STALL))
			जारी;

		dep->flags &= ~DWC3_EP_STALL;

		ret = dwc3_send_clear_stall_ep_cmd(dep);
		WARN_ON_ONCE(ret);
	पूर्ण
पूर्ण

अटल व्योम dwc3_gadget_disconnect_पूर्णांकerrupt(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक			reg;

	dwc3_gadget_set_link_state(dwc, DWC3_LINK_STATE_RX_DET);

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_INITU1ENA;
	reg &= ~DWC3_DCTL_INITU2ENA;
	dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);

	dwc3_disconnect_gadget(dwc);

	dwc->gadget->speed = USB_SPEED_UNKNOWN;
	dwc->setup_packet_pending = false;
	usb_gadget_set_state(dwc->gadget, USB_STATE_NOTATTACHED);

	dwc->connected = false;
पूर्ण

अटल व्योम dwc3_gadget_reset_पूर्णांकerrupt(काष्ठा dwc3 *dwc)
अणु
	u32			reg;

	/*
	 * Ideally, dwc3_reset_gadget() would trigger the function
	 * drivers to stop any active transfers through ep disable.
	 * However, क्रम functions which defer ep disable, such as mass
	 * storage, we will need to rely on the call to stop active
	 * transfers here, and aव्योम allowing of request queuing.
	 */
	dwc->connected = false;

	/*
	 * WORKAROUND: DWC3 revisions <1.88a have an issue which
	 * would cause a missing Disconnect Event अगर there's a
	 * pending Setup Packet in the FIFO.
	 *
	 * There's no suggested workaround on the official Bug
	 * report, which states that "unless the driver/application
	 * is करोing any special handling of a disconnect event,
	 * there is no functional issue".
	 *
	 * Unक्रमtunately, it turns out that we _करो_ some special
	 * handling of a disconnect event, namely complete all
	 * pending transfers, notअगरy gadget driver of the
	 * disconnection, and so on.
	 *
	 * Our suggested workaround is to follow the Disconnect
	 * Event steps here, instead, based on a setup_packet_pending
	 * flag. Such flag माला_लो set whenever we have a SETUP_PENDING
	 * status क्रम EP0 TRBs and माला_लो cleared on XferComplete क्रम the
	 * same endpoपूर्णांक.
	 *
	 * Refers to:
	 *
	 * STAR#9000466709: RTL: Device : Disconnect event not
	 * generated अगर setup packet pending in FIFO
	 */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 188A)) अणु
		अगर (dwc->setup_packet_pending)
			dwc3_gadget_disconnect_पूर्णांकerrupt(dwc);
	पूर्ण

	dwc3_reset_gadget(dwc);
	/*
	 * In the Synopsis DesignWare Cores USB3 Databook Rev. 3.30a
	 * Section 4.1.2 Table 4-2, it states that during a USB reset, the SW
	 * needs to ensure that it sends "a DEPENDXFER command क्रम any active
	 * transfers."
	 */
	dwc3_stop_active_transfers(dwc);
	dwc->connected = true;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_TSTCTRL_MASK;
	dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);
	dwc->test_mode = false;
	dwc3_clear_stall_all_ep(dwc);

	/* Reset device address to zero */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
	reg &= ~(DWC3_DCFG_DEVADDR_MASK);
	dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);
पूर्ण

अटल व्योम dwc3_gadget_connकरोne_पूर्णांकerrupt(काष्ठा dwc3 *dwc)
अणु
	काष्ठा dwc3_ep		*dep;
	पूर्णांक			ret;
	u32			reg;
	u8			lanes = 1;
	u8			speed;

	reg = dwc3_पढ़ोl(dwc->regs, DWC3_DSTS);
	speed = reg & DWC3_DSTS_CONNECTSPD;
	dwc->speed = speed;

	अगर (DWC3_IP_IS(DWC32))
		lanes = DWC3_DSTS_CONNLANES(reg) + 1;

	dwc->gadget->ssp_rate = USB_SSP_GEN_UNKNOWN;

	/*
	 * RAMClkSel is reset to 0 after USB reset, so it must be reprogrammed
	 * each समय on Connect Done.
	 *
	 * Currently we always use the reset value. If any platक्रमm
	 * wants to set this to a dअगरferent value, we need to add a
	 * setting and update GCTL.RAMCLKSEL here.
	 */

	चयन (speed) अणु
	हाल DWC3_DSTS_SUPERSPEED_PLUS:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);
		dwc->gadget->ep0->maxpacket = 512;
		dwc->gadget->speed = USB_SPEED_SUPER_PLUS;

		अगर (lanes > 1)
			dwc->gadget->ssp_rate = USB_SSP_GEN_2x2;
		अन्यथा
			dwc->gadget->ssp_rate = USB_SSP_GEN_2x1;
		अवरोध;
	हाल DWC3_DSTS_SUPERSPEED:
		/*
		 * WORKAROUND: DWC3 revisions <1.90a have an issue which
		 * would cause a missing USB3 Reset event.
		 *
		 * In such situations, we should क्रमce a USB3 Reset
		 * event by calling our dwc3_gadget_reset_पूर्णांकerrupt()
		 * routine.
		 *
		 * Refers to:
		 *
		 * STAR#9000483510: RTL: SS : USB3 reset event may
		 * not be generated always when the link enters poll
		 */
		अगर (DWC3_VER_IS_PRIOR(DWC3, 190A))
			dwc3_gadget_reset_पूर्णांकerrupt(dwc);

		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(512);
		dwc->gadget->ep0->maxpacket = 512;
		dwc->gadget->speed = USB_SPEED_SUPER;

		अगर (lanes > 1) अणु
			dwc->gadget->speed = USB_SPEED_SUPER_PLUS;
			dwc->gadget->ssp_rate = USB_SSP_GEN_1x2;
		पूर्ण
		अवरोध;
	हाल DWC3_DSTS_HIGHSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		dwc->gadget->ep0->maxpacket = 64;
		dwc->gadget->speed = USB_SPEED_HIGH;
		अवरोध;
	हाल DWC3_DSTS_FULLSPEED:
		dwc3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(64);
		dwc->gadget->ep0->maxpacket = 64;
		dwc->gadget->speed = USB_SPEED_FULL;
		अवरोध;
	पूर्ण

	dwc->eps[1]->endpoपूर्णांक.maxpacket = dwc->gadget->ep0->maxpacket;

	/* Enable USB2 LPM Capability */

	अगर (!DWC3_VER_IS_WITHIN(DWC3, ANY, 194A) &&
	    !dwc->usb2_gadget_lpm_disable &&
	    (speed != DWC3_DSTS_SUPERSPEED) &&
	    (speed != DWC3_DSTS_SUPERSPEED_PLUS)) अणु
		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
		reg |= DWC3_DCFG_LPM_CAP;
		dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);

		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
		reg &= ~(DWC3_DCTL_HIRD_THRES_MASK | DWC3_DCTL_L1_HIBER_EN);

		reg |= DWC3_DCTL_HIRD_THRES(dwc->hird_threshold |
					    (dwc->is_uपंचांगi_l1_suspend << 4));

		/*
		 * When dwc3 revisions >= 2.40a, LPM Erratum is enabled and
		 * DCFG.LPMCap is set, core responses with an ACK and the
		 * BESL value in the LPM token is less than or equal to LPM
		 * NYET threshold.
		 */
		WARN_ONCE(DWC3_VER_IS_PRIOR(DWC3, 240A) && dwc->has_lpm_erratum,
				"LPM Erratum not available on dwc3 revisions < 2.40a\n");

		अगर (dwc->has_lpm_erratum && !DWC3_VER_IS_PRIOR(DWC3, 240A))
			reg |= DWC3_DCTL_NYET_THRES(dwc->lpm_nyet_threshold);

		dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);
	पूर्ण अन्यथा अणु
		अगर (dwc->usb2_gadget_lpm_disable) अणु
			reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCFG);
			reg &= ~DWC3_DCFG_LPM_CAP;
			dwc3_ग_लिखोl(dwc->regs, DWC3_DCFG, reg);
		पूर्ण

		reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
		reg &= ~DWC3_DCTL_HIRD_THRES_MASK;
		dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);
	पूर्ण

	dep = dwc->eps[0];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_MODIFY);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		वापस;
	पूर्ण

	dep = dwc->eps[1];
	ret = __dwc3_gadget_ep_enable(dep, DWC3_DEPCFG_ACTION_MODIFY);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to enable %s\n", dep->name);
		वापस;
	पूर्ण

	/*
	 * Configure PHY via GUSB3PIPECTLn अगर required.
	 *
	 * Update GTXFIFOSIZn
	 *
	 * In both हालs reset values should be sufficient.
	 */
पूर्ण

अटल व्योम dwc3_gadget_wakeup_पूर्णांकerrupt(काष्ठा dwc3 *dwc)
अणु
	/*
	 * TODO take core out of low घातer mode when that's
	 * implemented.
	 */

	अगर (dwc->gadget_driver && dwc->gadget_driver->resume) अणु
		spin_unlock(&dwc->lock);
		dwc->gadget_driver->resume(dwc->gadget);
		spin_lock(&dwc->lock);
	पूर्ण
पूर्ण

अटल व्योम dwc3_gadget_linksts_change_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
		अचिन्हित पूर्णांक evtinfo)
अणु
	क्रमागत dwc3_link_state	next = evtinfo & DWC3_LINK_STATE_MASK;
	अचिन्हित पूर्णांक		pwropt;

	/*
	 * WORKAROUND: DWC3 < 2.50a have an issue when configured without
	 * Hibernation mode enabled which would show up when device detects
	 * host-initiated U3 निकास.
	 *
	 * In that हाल, device will generate a Link State Change Interrupt
	 * from U3 to RESUME which is only necessary अगर Hibernation is
	 * configured in.
	 *
	 * There are no functional changes due to such spurious event and we
	 * just need to ignore it.
	 *
	 * Refers to:
	 *
	 * STAR#9000570034 RTL: SS Resume event generated in non-Hibernation
	 * operational mode
	 */
	pwropt = DWC3_GHWPARAMS1_EN_PWROPT(dwc->hwparams.hwparams1);
	अगर (DWC3_VER_IS_PRIOR(DWC3, 250A) &&
			(pwropt != DWC3_GHWPARAMS1_EN_PWROPT_HIB)) अणु
		अगर ((dwc->link_state == DWC3_LINK_STATE_U3) &&
				(next == DWC3_LINK_STATE_RESUME)) अणु
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * WORKAROUND: DWC3 Revisions <1.83a have an issue which, depending
	 * on the link partner, the USB session might करो multiple entry/निकास
	 * of low घातer states beक्रमe a transfer takes place.
	 *
	 * Due to this problem, we might experience lower throughput. The
	 * suggested workaround is to disable DCTL[12:9] bits अगर we're
	 * transitioning from U1/U2 to U0 and enable those bits again
	 * after a transfer completes and there are no pending transfers
	 * on any of the enabled endpoपूर्णांकs.
	 *
	 * This is the first half of that workaround.
	 *
	 * Refers to:
	 *
	 * STAR#9000446952: RTL: Device SS : अगर U1/U2 ->U0 takes >128us
	 * core send LGO_Ux entering U0
	 */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 183A)) अणु
		अगर (next == DWC3_LINK_STATE_U0) अणु
			u32	u1u2;
			u32	reg;

			चयन (dwc->link_state) अणु
			हाल DWC3_LINK_STATE_U1:
			हाल DWC3_LINK_STATE_U2:
				reg = dwc3_पढ़ोl(dwc->regs, DWC3_DCTL);
				u1u2 = reg & (DWC3_DCTL_INITU2ENA
						| DWC3_DCTL_ACCEPTU2ENA
						| DWC3_DCTL_INITU1ENA
						| DWC3_DCTL_ACCEPTU1ENA);

				अगर (!dwc->u1u2)
					dwc->u1u2 = reg & u1u2;

				reg &= ~u1u2;

				dwc3_gadget_dctl_ग_लिखो_safe(dwc, reg);
				अवरोध;
			शेष:
				/* करो nothing */
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (next) अणु
	हाल DWC3_LINK_STATE_U1:
		अगर (dwc->speed == USB_SPEED_SUPER)
			dwc3_suspend_gadget(dwc);
		अवरोध;
	हाल DWC3_LINK_STATE_U2:
	हाल DWC3_LINK_STATE_U3:
		dwc3_suspend_gadget(dwc);
		अवरोध;
	हाल DWC3_LINK_STATE_RESUME:
		dwc3_resume_gadget(dwc);
		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	dwc->link_state = next;
पूर्ण

अटल व्योम dwc3_gadget_suspend_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
					  अचिन्हित पूर्णांक evtinfo)
अणु
	क्रमागत dwc3_link_state next = evtinfo & DWC3_LINK_STATE_MASK;

	अगर (dwc->link_state != next && next == DWC3_LINK_STATE_U3)
		dwc3_suspend_gadget(dwc);

	dwc->link_state = next;
पूर्ण

अटल व्योम dwc3_gadget_hibernation_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
		अचिन्हित पूर्णांक evtinfo)
अणु
	अचिन्हित पूर्णांक is_ss = evtinfo & BIT(4);

	/*
	 * WORKAROUND: DWC3 revison 2.20a with hibernation support
	 * have a known issue which can cause USB CV TD.9.23 to fail
	 * अक्रमomly.
	 *
	 * Because of this issue, core could generate bogus hibernation
	 * events which SW needs to ignore.
	 *
	 * Refers to:
	 *
	 * STAR#9000546576: Device Mode Hibernation: Issue in USB 2.0
	 * Device Fallback from SuperSpeed
	 */
	अगर (is_ss ^ (dwc->speed == USB_SPEED_SUPER))
		वापस;

	/* enter hibernation here */
पूर्ण

अटल व्योम dwc3_gadget_पूर्णांकerrupt(काष्ठा dwc3 *dwc,
		स्थिर काष्ठा dwc3_event_devt *event)
अणु
	चयन (event->type) अणु
	हाल DWC3_DEVICE_EVENT_DISCONNECT:
		dwc3_gadget_disconnect_पूर्णांकerrupt(dwc);
		अवरोध;
	हाल DWC3_DEVICE_EVENT_RESET:
		dwc3_gadget_reset_पूर्णांकerrupt(dwc);
		अवरोध;
	हाल DWC3_DEVICE_EVENT_CONNECT_DONE:
		dwc3_gadget_connकरोne_पूर्णांकerrupt(dwc);
		अवरोध;
	हाल DWC3_DEVICE_EVENT_WAKEUP:
		dwc3_gadget_wakeup_पूर्णांकerrupt(dwc);
		अवरोध;
	हाल DWC3_DEVICE_EVENT_HIBER_REQ:
		अगर (dev_WARN_ONCE(dwc->dev, !dwc->has_hibernation,
					"unexpected hibernation event\n"))
			अवरोध;

		dwc3_gadget_hibernation_पूर्णांकerrupt(dwc, event->event_info);
		अवरोध;
	हाल DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
		dwc3_gadget_linksts_change_पूर्णांकerrupt(dwc, event->event_info);
		अवरोध;
	हाल DWC3_DEVICE_EVENT_SUSPEND:
		/* It changed to be suspend event क्रम version 2.30a and above */
		अगर (!DWC3_VER_IS_PRIOR(DWC3, 230A)) अणु
			/*
			 * Ignore suspend event until the gadget enters पूर्णांकo
			 * USB_STATE_CONFIGURED state.
			 */
			अगर (dwc->gadget->state >= USB_STATE_CONFIGURED)
				dwc3_gadget_suspend_पूर्णांकerrupt(dwc,
						event->event_info);
		पूर्ण
		अवरोध;
	हाल DWC3_DEVICE_EVENT_SOF:
	हाल DWC3_DEVICE_EVENT_ERRATIC_ERROR:
	हाल DWC3_DEVICE_EVENT_CMD_CMPL:
	हाल DWC3_DEVICE_EVENT_OVERFLOW:
		अवरोध;
	शेष:
		dev_WARN(dwc->dev, "UNKNOWN IRQ %d\n", event->type);
	पूर्ण
पूर्ण

अटल व्योम dwc3_process_event_entry(काष्ठा dwc3 *dwc,
		स्थिर जोड़ dwc3_event *event)
अणु
	trace_dwc3_event(event->raw, dwc);

	अगर (!event->type.is_devspec)
		dwc3_endpoपूर्णांक_पूर्णांकerrupt(dwc, &event->depevt);
	अन्यथा अगर (event->type.type == DWC3_EVENT_TYPE_DEV)
		dwc3_gadget_पूर्णांकerrupt(dwc, &event->devt);
	अन्यथा
		dev_err(dwc->dev, "UNKNOWN IRQ type %d\n", event->raw);
पूर्ण

अटल irqवापस_t dwc3_process_event_buf(काष्ठा dwc3_event_buffer *evt)
अणु
	काष्ठा dwc3 *dwc = evt->dwc;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक left;
	u32 reg;

	left = evt->count;

	अगर (!(evt->flags & DWC3_EVENT_PENDING))
		वापस IRQ_NONE;

	जबतक (left > 0) अणु
		जोड़ dwc3_event event;

		event.raw = *(u32 *) (evt->cache + evt->lpos);

		dwc3_process_event_entry(dwc, &event);

		/*
		 * FIXME we wrap around correctly to the next entry as
		 * almost all entries are 4 bytes in size. There is one
		 * entry which has 12 bytes which is a regular entry
		 * followed by 8 bytes data. ATM I करोn't know how
		 * things are organized अगर we get next to the a
		 * boundary so I worry about that once we try to handle
		 * that.
		 */
		evt->lpos = (evt->lpos + 4) % evt->length;
		left -= 4;
	पूर्ण

	evt->count = 0;
	evt->flags &= ~DWC3_EVENT_PENDING;
	ret = IRQ_HANDLED;

	/* Unmask पूर्णांकerrupt */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GEVNTSIZ(0));
	reg &= ~DWC3_GEVNTSIZ_INTMASK;
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTSIZ(0), reg);

	अगर (dwc->imod_पूर्णांकerval) अणु
		dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTCOUNT(0), DWC3_GEVNTCOUNT_EHB);
		dwc3_ग_लिखोl(dwc->regs, DWC3_DEV_IMOD(0), dwc->imod_पूर्णांकerval);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t dwc3_thपढ़ो_पूर्णांकerrupt(पूर्णांक irq, व्योम *_evt)
अणु
	काष्ठा dwc3_event_buffer *evt = _evt;
	काष्ठा dwc3 *dwc = evt->dwc;
	अचिन्हित दीर्घ flags;
	irqवापस_t ret = IRQ_NONE;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = dwc3_process_event_buf(evt);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस ret;
पूर्ण

अटल irqवापस_t dwc3_check_event_buf(काष्ठा dwc3_event_buffer *evt)
अणु
	काष्ठा dwc3 *dwc = evt->dwc;
	u32 amount;
	u32 count;
	u32 reg;

	अगर (pm_runसमय_suspended(dwc->dev)) अणु
		pm_runसमय_get(dwc->dev);
		disable_irq_nosync(dwc->irq_gadget);
		dwc->pending_events = true;
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * With PCIe legacy पूर्णांकerrupt, test shows that top-half irq handler can
	 * be called again after HW पूर्णांकerrupt deनिश्चितion. Check अगर bottom-half
	 * irq event handler completes beक्रमe caching new event to prevent
	 * losing events.
	 */
	अगर (evt->flags & DWC3_EVENT_PENDING)
		वापस IRQ_HANDLED;

	count = dwc3_पढ़ोl(dwc->regs, DWC3_GEVNTCOUNT(0));
	count &= DWC3_GEVNTCOUNT_MASK;
	अगर (!count)
		वापस IRQ_NONE;

	evt->count = count;
	evt->flags |= DWC3_EVENT_PENDING;

	/* Mask पूर्णांकerrupt */
	reg = dwc3_पढ़ोl(dwc->regs, DWC3_GEVNTSIZ(0));
	reg |= DWC3_GEVNTSIZ_INTMASK;
	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTSIZ(0), reg);

	amount = min(count, evt->length - evt->lpos);
	स_नकल(evt->cache + evt->lpos, evt->buf + evt->lpos, amount);

	अगर (amount < count)
		स_नकल(evt->cache, evt->buf, count - amount);

	dwc3_ग_लिखोl(dwc->regs, DWC3_GEVNTCOUNT(0), count);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t dwc3_पूर्णांकerrupt(पूर्णांक irq, व्योम *_evt)
अणु
	काष्ठा dwc3_event_buffer	*evt = _evt;

	वापस dwc3_check_event_buf(evt);
पूर्ण

अटल पूर्णांक dwc3_gadget_get_irq(काष्ठा dwc3 *dwc)
अणु
	काष्ठा platक्रमm_device *dwc3_pdev = to_platक्रमm_device(dwc->dev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq_byname_optional(dwc3_pdev, "peripheral");
	अगर (irq > 0)
		जाओ out;

	अगर (irq == -EPROBE_DEFER)
		जाओ out;

	irq = platक्रमm_get_irq_byname_optional(dwc3_pdev, "dwc_usb3");
	अगर (irq > 0)
		जाओ out;

	अगर (irq == -EPROBE_DEFER)
		जाओ out;

	irq = platक्रमm_get_irq(dwc3_pdev, 0);
	अगर (irq > 0)
		जाओ out;

	अगर (!irq)
		irq = -EINVAL;

out:
	वापस irq;
पूर्ण

अटल व्योम dwc_gadget_release(काष्ठा device *dev)
अणु
	काष्ठा usb_gadget *gadget = container_of(dev, काष्ठा usb_gadget, dev);

	kमुक्त(gadget);
पूर्ण

/**
 * dwc3_gadget_init - initializes gadget related रेजिस्टरs
 * @dwc: poपूर्णांकer to our controller context काष्ठाure
 *
 * Returns 0 on success otherwise negative त्रुटि_सं.
 */
पूर्णांक dwc3_gadget_init(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक ret;
	पूर्णांक irq;
	काष्ठा device *dev;

	irq = dwc3_gadget_get_irq(dwc);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err0;
	पूर्ण

	dwc->irq_gadget = irq;

	dwc->ep0_trb = dma_alloc_coherent(dwc->sysdev,
					  माप(*dwc->ep0_trb) * 2,
					  &dwc->ep0_trb_addr, GFP_KERNEL);
	अगर (!dwc->ep0_trb) अणु
		dev_err(dwc->dev, "failed to allocate ep0 trb\n");
		ret = -ENOMEM;
		जाओ err0;
	पूर्ण

	dwc->setup_buf = kzalloc(DWC3_EP0_SETUP_SIZE, GFP_KERNEL);
	अगर (!dwc->setup_buf) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	dwc->bounce = dma_alloc_coherent(dwc->sysdev, DWC3_BOUNCE_SIZE,
			&dwc->bounce_addr, GFP_KERNEL);
	अगर (!dwc->bounce) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण

	init_completion(&dwc->ep0_in_setup);
	dwc->gadget = kzalloc(माप(काष्ठा usb_gadget), GFP_KERNEL);
	अगर (!dwc->gadget) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण


	usb_initialize_gadget(dwc->dev, dwc->gadget, dwc_gadget_release);
	dev				= &dwc->gadget->dev;
	dev->platक्रमm_data		= dwc;
	dwc->gadget->ops		= &dwc3_gadget_ops;
	dwc->gadget->speed		= USB_SPEED_UNKNOWN;
	dwc->gadget->ssp_rate		= USB_SSP_GEN_UNKNOWN;
	dwc->gadget->sg_supported	= true;
	dwc->gadget->name		= "dwc3-gadget";
	dwc->gadget->lpm_capable	= !dwc->usb2_gadget_lpm_disable;

	/*
	 * FIXME We might be setting max_speed to <SUPER, however versions
	 * <2.20a of dwc3 have an issue with metastability (करोcumented
	 * अन्यथाwhere in this driver) which tells us we can't set max speed to
	 * anything lower than SUPER.
	 *
	 * Because gadget.max_speed is only used by composite.c and function
	 * drivers (i.e. it won't go into dwc3's रेजिस्टरs) we are allowing this
	 * to happen so we aव्योम sending SuperSpeed Capability descriptor
	 * together with our BOS descriptor as that could confuse host पूर्णांकo
	 * thinking we can handle super speed.
	 *
	 * Note that, in fact, we won't even support GetBOS requests when speed
	 * is less than super speed because we करोn't have means, yet, to tell
	 * composite.c that we are USB 2.0 + LPM ECN.
	 */
	अगर (DWC3_VER_IS_PRIOR(DWC3, 220A) &&
	    !dwc->dis_metastability_quirk)
		dev_info(dwc->dev, "changing max_speed on rev %08x\n",
				dwc->revision);

	dwc->gadget->max_speed		= dwc->maximum_speed;
	dwc->gadget->max_ssp_rate	= dwc->max_ssp_rate;

	/*
	 * REVISIT: Here we should clear all pending IRQs to be
	 * sure we're starting from a well known location.
	 */

	ret = dwc3_gadget_init_endpoपूर्णांकs(dwc, dwc->num_eps);
	अगर (ret)
		जाओ err4;

	ret = usb_add_gadget(dwc->gadget);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to add gadget\n");
		जाओ err5;
	पूर्ण

	अगर (DWC3_IP_IS(DWC32) && dwc->maximum_speed == USB_SPEED_SUPER_PLUS)
		dwc3_gadget_set_ssp_rate(dwc->gadget, dwc->max_ssp_rate);
	अन्यथा
		dwc3_gadget_set_speed(dwc->gadget, dwc->maximum_speed);

	वापस 0;

err5:
	dwc3_gadget_मुक्त_endpoपूर्णांकs(dwc);
err4:
	usb_put_gadget(dwc->gadget);
	dwc->gadget = शून्य;
err3:
	dma_मुक्त_coherent(dwc->sysdev, DWC3_BOUNCE_SIZE, dwc->bounce,
			dwc->bounce_addr);

err2:
	kमुक्त(dwc->setup_buf);

err1:
	dma_मुक्त_coherent(dwc->sysdev, माप(*dwc->ep0_trb) * 2,
			dwc->ep0_trb, dwc->ep0_trb_addr);

err0:
	वापस ret;
पूर्ण

/* -------------------------------------------------------------------------- */

व्योम dwc3_gadget_निकास(काष्ठा dwc3 *dwc)
अणु
	अगर (!dwc->gadget)
		वापस;

	usb_del_gadget(dwc->gadget);
	dwc3_gadget_मुक्त_endpoपूर्णांकs(dwc);
	usb_put_gadget(dwc->gadget);
	dma_मुक्त_coherent(dwc->sysdev, DWC3_BOUNCE_SIZE, dwc->bounce,
			  dwc->bounce_addr);
	kमुक्त(dwc->setup_buf);
	dma_मुक्त_coherent(dwc->sysdev, माप(*dwc->ep0_trb) * 2,
			  dwc->ep0_trb, dwc->ep0_trb_addr);
पूर्ण

पूर्णांक dwc3_gadget_suspend(काष्ठा dwc3 *dwc)
अणु
	अगर (!dwc->gadget_driver)
		वापस 0;

	dwc3_gadget_run_stop(dwc, false, false);
	dwc3_disconnect_gadget(dwc);
	__dwc3_gadget_stop(dwc);

	वापस 0;
पूर्ण

पूर्णांक dwc3_gadget_resume(काष्ठा dwc3 *dwc)
अणु
	पूर्णांक			ret;

	अगर (!dwc->gadget_driver)
		वापस 0;

	ret = __dwc3_gadget_start(dwc);
	अगर (ret < 0)
		जाओ err0;

	ret = dwc3_gadget_run_stop(dwc, true, false);
	अगर (ret < 0)
		जाओ err1;

	वापस 0;

err1:
	__dwc3_gadget_stop(dwc);

err0:
	वापस ret;
पूर्ण

व्योम dwc3_gadget_process_pending_events(काष्ठा dwc3 *dwc)
अणु
	अगर (dwc->pending_events) अणु
		dwc3_पूर्णांकerrupt(dwc->irq_gadget, dwc->ev_buf);
		dwc->pending_events = false;
		enable_irq(dwc->irq_gadget);
	पूर्ण
पूर्ण
