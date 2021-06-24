<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS DRD Driver - gadget side.
 *
 * Copyright (C) 2018 Cadence Design Systems.
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Pawel Jez <pjez@cadence.com>,
 *          Pawel Laszczak <pawell@cadence.com>
 *          Peter Chen <peter.chen@nxp.com>
 */

#समावेश <linux/usb/composite.h>
#समावेश <linux/iopoll.h>

#समावेश "cdns3-gadget.h"
#समावेश "cdns3-trace.h"

अटल काष्ठा usb_endpoपूर्णांक_descriptor cdns3_gadget_ep0_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bmAttributes =	USB_ENDPOINT_XFER_CONTROL,
पूर्ण;

/**
 * cdns3_ep0_run_transfer - Do transfer on शेष endpoपूर्णांक hardware
 * @priv_dev: extended gadget object
 * @dma_addr: physical address where data is/will be stored
 * @length: data length
 * @erdy: set it to 1 when ERDY packet should be sent -
 *        निकास from flow control state
 * @zlp: add zero length packet
 */
अटल व्योम cdns3_ep0_run_transfer(काष्ठा cdns3_device *priv_dev,
				   dma_addr_t dma_addr,
				   अचिन्हित पूर्णांक length, पूर्णांक erdy, पूर्णांक zlp)
अणु
	काष्ठा cdns3_usb_regs __iomem *regs = priv_dev->regs;
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = priv_dev->eps[0];

	priv_ep->trb_pool[0].buffer = cpu_to_le32(TRB_BUFFER(dma_addr));
	priv_ep->trb_pool[0].length = cpu_to_le32(TRB_LEN(length));

	अगर (zlp) अणु
		priv_ep->trb_pool[0].control = cpu_to_le32(TRB_CYCLE | TRB_TYPE(TRB_NORMAL));
		priv_ep->trb_pool[1].buffer = cpu_to_le32(TRB_BUFFER(dma_addr));
		priv_ep->trb_pool[1].length = cpu_to_le32(TRB_LEN(0));
		priv_ep->trb_pool[1].control = cpu_to_le32(TRB_CYCLE | TRB_IOC |
		    TRB_TYPE(TRB_NORMAL));
	पूर्ण अन्यथा अणु
		priv_ep->trb_pool[0].control = cpu_to_le32(TRB_CYCLE | TRB_IOC |
		    TRB_TYPE(TRB_NORMAL));
		priv_ep->trb_pool[1].control = 0;
	पूर्ण

	trace_cdns3_prepare_trb(priv_ep, priv_ep->trb_pool);

	cdns3_select_ep(priv_dev, priv_dev->ep0_data_dir);

	ग_लिखोl(EP_STS_TRBERR, &regs->ep_sts);
	ग_लिखोl(EP_TRADDR_TRADDR(priv_ep->trb_pool_dma), &regs->ep_traddr);
	trace_cdns3_करोorbell_ep0(priv_dev->ep0_data_dir ? "ep0in" : "ep0out",
				 पढ़ोl(&regs->ep_traddr));

	/* TRB should be prepared beक्रमe starting transfer. */
	ग_लिखोl(EP_CMD_DRDY, &regs->ep_cmd);

	/* Resume controller beक्रमe arming transfer. */
	__cdns3_gadget_wakeup(priv_dev);

	अगर (erdy)
		ग_लिखोl(EP_CMD_ERDY, &priv_dev->regs->ep_cmd);
पूर्ण

/**
 * cdns3_ep0_delegate_req - Returns status of handling setup packet
 * Setup is handled by gadget driver
 * @priv_dev: extended gadget object
 * @ctrl_req: poपूर्णांकer to received setup packet
 *
 * Returns zero on success or negative value on failure
 */
अटल पूर्णांक cdns3_ep0_delegate_req(काष्ठा cdns3_device *priv_dev,
				  काष्ठा usb_ctrlrequest *ctrl_req)
अणु
	पूर्णांक ret;

	spin_unlock(&priv_dev->lock);
	priv_dev->setup_pending = 1;
	ret = priv_dev->gadget_driver->setup(&priv_dev->gadget, ctrl_req);
	priv_dev->setup_pending = 0;
	spin_lock(&priv_dev->lock);
	वापस ret;
पूर्ण

अटल व्योम cdns3_prepare_setup_packet(काष्ठा cdns3_device *priv_dev)
अणु
	priv_dev->ep0_data_dir = 0;
	priv_dev->ep0_stage = CDNS3_SETUP_STAGE;
	cdns3_ep0_run_transfer(priv_dev, priv_dev->setup_dma,
			       माप(काष्ठा usb_ctrlrequest), 0, 0);
पूर्ण

अटल व्योम cdns3_ep0_complete_setup(काष्ठा cdns3_device *priv_dev,
				     u8 send_stall, u8 send_erdy)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = priv_dev->eps[0];
	काष्ठा usb_request *request;

	request = cdns3_next_request(&priv_ep->pending_req_list);
	अगर (request)
		list_del_init(&request->list);

	अगर (send_stall) अणु
		trace_cdns3_halt(priv_ep, send_stall, 0);
		/* set_stall on ep0 */
		cdns3_select_ep(priv_dev, 0x00);
		ग_लिखोl(EP_CMD_SSTALL, &priv_dev->regs->ep_cmd);
	पूर्ण अन्यथा अणु
		cdns3_prepare_setup_packet(priv_dev);
	पूर्ण

	priv_dev->ep0_stage = CDNS3_SETUP_STAGE;
	ग_लिखोl((send_erdy ? EP_CMD_ERDY : 0) | EP_CMD_REQ_CMPL,
	       &priv_dev->regs->ep_cmd);
पूर्ण

/**
 * cdns3_req_ep0_set_configuration - Handling of SET_CONFIG standard USB request
 * @priv_dev: extended gadget object
 * @ctrl_req: poपूर्णांकer to received setup packet
 *
 * Returns 0 अगर success, USB_GADGET_DELAYED_STATUS on deferred status stage,
 * error code on error
 */
अटल पूर्णांक cdns3_req_ep0_set_configuration(काष्ठा cdns3_device *priv_dev,
					   काष्ठा usb_ctrlrequest *ctrl_req)
अणु
	क्रमागत usb_device_state device_state = priv_dev->gadget.state;
	u32 config = le16_to_cpu(ctrl_req->wValue);
	पूर्णांक result = 0;

	चयन (device_state) अणु
	हाल USB_STATE_ADDRESS:
		result = cdns3_ep0_delegate_req(priv_dev, ctrl_req);

		अगर (result || !config)
			जाओ reset_config;

		अवरोध;
	हाल USB_STATE_CONFIGURED:
		result = cdns3_ep0_delegate_req(priv_dev, ctrl_req);
		अगर (!config && !result)
			जाओ reset_config;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;

reset_config:
	अगर (result != USB_GADGET_DELAYED_STATUS)
		cdns3_hw_reset_eps_config(priv_dev);

	usb_gadget_set_state(&priv_dev->gadget,
			     USB_STATE_ADDRESS);

	वापस result;
पूर्ण

/**
 * cdns3_req_ep0_set_address - Handling of SET_ADDRESS standard USB request
 * @priv_dev: extended gadget object
 * @ctrl_req: poपूर्णांकer to received setup packet
 *
 * Returns 0 अगर success, error code on error
 */
अटल पूर्णांक cdns3_req_ep0_set_address(काष्ठा cdns3_device *priv_dev,
				     काष्ठा usb_ctrlrequest *ctrl_req)
अणु
	क्रमागत usb_device_state device_state = priv_dev->gadget.state;
	u32 reg;
	u32 addr;

	addr = le16_to_cpu(ctrl_req->wValue);

	अगर (addr > USB_DEVICE_MAX_ADDRESS) अणु
		dev_err(priv_dev->dev,
			"Device address (%d) cannot be greater than %d\n",
			addr, USB_DEVICE_MAX_ADDRESS);
		वापस -EINVAL;
	पूर्ण

	अगर (device_state == USB_STATE_CONFIGURED) अणु
		dev_err(priv_dev->dev,
			"can't set_address from configured state\n");
		वापस -EINVAL;
	पूर्ण

	reg = पढ़ोl(&priv_dev->regs->usb_cmd);

	ग_लिखोl(reg | USB_CMD_FADDR(addr) | USB_CMD_SET_ADDR,
	       &priv_dev->regs->usb_cmd);

	usb_gadget_set_state(&priv_dev->gadget,
			     (addr ? USB_STATE_ADDRESS : USB_STATE_DEFAULT));

	वापस 0;
पूर्ण

/**
 * cdns3_req_ep0_get_status - Handling of GET_STATUS standard USB request
 * @priv_dev: extended gadget object
 * @ctrl: poपूर्णांकer to received setup packet
 *
 * Returns 0 अगर success, error code on error
 */
अटल पूर्णांक cdns3_req_ep0_get_status(काष्ठा cdns3_device *priv_dev,
				    काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	__le16 *response_pkt;
	u16 usb_status = 0;
	u32 recip;
	u8 index;

	recip = ctrl->bRequestType & USB_RECIP_MASK;

	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		/* self घातered */
		अगर (priv_dev->is_selfघातered)
			usb_status = BIT(USB_DEVICE_SELF_POWERED);

		अगर (priv_dev->wake_up_flag)
			usb_status |= BIT(USB_DEVICE_REMOTE_WAKEUP);

		अगर (priv_dev->gadget.speed != USB_SPEED_SUPER)
			अवरोध;

		अगर (priv_dev->u1_allowed)
			usb_status |= BIT(USB_DEV_STAT_U1_ENABLED);

		अगर (priv_dev->u2_allowed)
			usb_status |= BIT(USB_DEV_STAT_U2_ENABLED);

		अवरोध;
	हाल USB_RECIP_INTERFACE:
		वापस cdns3_ep0_delegate_req(priv_dev, ctrl);
	हाल USB_RECIP_ENDPOINT:
		index = cdns3_ep_addr_to_index(le16_to_cpu(ctrl->wIndex));
		priv_ep = priv_dev->eps[index];

		/* check अगर endpoपूर्णांक is stalled or stall is pending */
		cdns3_select_ep(priv_dev, le16_to_cpu(ctrl->wIndex));
		अगर (EP_STS_STALL(पढ़ोl(&priv_dev->regs->ep_sts)) ||
		    (priv_ep->flags & EP_STALL_PENDING))
			usb_status =  BIT(USB_ENDPOINT_HALT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	response_pkt = (__le16 *)priv_dev->setup_buf;
	*response_pkt = cpu_to_le16(usb_status);

	cdns3_ep0_run_transfer(priv_dev, priv_dev->setup_dma,
			       माप(*response_pkt), 1, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_ep0_feature_handle_device(काष्ठा cdns3_device *priv_dev,
					   काष्ठा usb_ctrlrequest *ctrl,
					   पूर्णांक set)
अणु
	क्रमागत usb_device_state state;
	क्रमागत usb_device_speed speed;
	पूर्णांक ret = 0;
	u32 wValue;
	u16 पंचांगode;

	wValue = le16_to_cpu(ctrl->wValue);
	state = priv_dev->gadget.state;
	speed = priv_dev->gadget.speed;

	चयन (wValue) अणु
	हाल USB_DEVICE_REMOTE_WAKEUP:
		priv_dev->wake_up_flag = !!set;
		अवरोध;
	हाल USB_DEVICE_U1_ENABLE:
		अगर (state != USB_STATE_CONFIGURED || speed != USB_SPEED_SUPER)
			वापस -EINVAL;

		priv_dev->u1_allowed = !!set;
		अवरोध;
	हाल USB_DEVICE_U2_ENABLE:
		अगर (state != USB_STATE_CONFIGURED || speed != USB_SPEED_SUPER)
			वापस -EINVAL;

		priv_dev->u2_allowed = !!set;
		अवरोध;
	हाल USB_DEVICE_LTM_ENABLE:
		ret = -EINVAL;
		अवरोध;
	हाल USB_DEVICE_TEST_MODE:
		अगर (state != USB_STATE_CONFIGURED || speed > USB_SPEED_HIGH)
			वापस -EINVAL;

		पंचांगode = le16_to_cpu(ctrl->wIndex);

		अगर (!set || (पंचांगode & 0xff) != 0)
			वापस -EINVAL;

		पंचांगode >>= 8;
		चयन (पंचांगode) अणु
		हाल USB_TEST_J:
		हाल USB_TEST_K:
		हाल USB_TEST_SE0_NAK:
		हाल USB_TEST_PACKET:
			cdns3_set_रेजिस्टर_bit(&priv_dev->regs->usb_cmd,
					       USB_CMD_STMODE |
					       USB_STS_TMODE_SEL(पंचांगode - 1));
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_ep0_feature_handle_पूर्णांकf(काष्ठा cdns3_device *priv_dev,
					 काष्ठा usb_ctrlrequest *ctrl,
					 पूर्णांक set)
अणु
	u32 wValue;
	पूर्णांक ret = 0;

	wValue = le16_to_cpu(ctrl->wValue);

	चयन (wValue) अणु
	हाल USB_INTRF_FUNC_SUSPEND:
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_ep0_feature_handle_endpoपूर्णांक(काष्ठा cdns3_device *priv_dev,
					     काष्ठा usb_ctrlrequest *ctrl,
					     पूर्णांक set)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	पूर्णांक ret = 0;
	u8 index;

	अगर (le16_to_cpu(ctrl->wValue) != USB_ENDPOINT_HALT)
		वापस -EINVAL;

	अगर (!(le16_to_cpu(ctrl->wIndex) & ~USB_सूची_IN))
		वापस 0;

	index = cdns3_ep_addr_to_index(le16_to_cpu(ctrl->wIndex));
	priv_ep = priv_dev->eps[index];

	cdns3_select_ep(priv_dev, le16_to_cpu(ctrl->wIndex));

	अगर (set)
		__cdns3_gadget_ep_set_halt(priv_ep);
	अन्यथा अगर (!(priv_ep->flags & EP_WEDGE))
		ret = __cdns3_gadget_ep_clear_halt(priv_ep);

	cdns3_select_ep(priv_dev, 0x00);

	वापस ret;
पूर्ण

/**
 * cdns3_req_ep0_handle_feature -
 * Handling of GET/SET_FEATURE standard USB request
 *
 * @priv_dev: extended gadget object
 * @ctrl: poपूर्णांकer to received setup packet
 * @set: must be set to 1 क्रम SET_FEATURE request
 *
 * Returns 0 अगर success, error code on error
 */
अटल पूर्णांक cdns3_req_ep0_handle_feature(काष्ठा cdns3_device *priv_dev,
					काष्ठा usb_ctrlrequest *ctrl,
					पूर्णांक set)
अणु
	पूर्णांक ret = 0;
	u32 recip;

	recip = ctrl->bRequestType & USB_RECIP_MASK;

	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		ret = cdns3_ep0_feature_handle_device(priv_dev, ctrl, set);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		ret = cdns3_ep0_feature_handle_पूर्णांकf(priv_dev, ctrl, set);
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ret = cdns3_ep0_feature_handle_endpoपूर्णांक(priv_dev, ctrl, set);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * cdns3_req_ep0_set_sel - Handling of SET_SEL standard USB request
 * @priv_dev: extended gadget object
 * @ctrl_req: poपूर्णांकer to received setup packet
 *
 * Returns 0 अगर success, error code on error
 */
अटल पूर्णांक cdns3_req_ep0_set_sel(काष्ठा cdns3_device *priv_dev,
				 काष्ठा usb_ctrlrequest *ctrl_req)
अणु
	अगर (priv_dev->gadget.state < USB_STATE_ADDRESS)
		वापस -EINVAL;

	अगर (le16_to_cpu(ctrl_req->wLength) != 6) अणु
		dev_err(priv_dev->dev, "Set SEL should be 6 bytes, got %d\n",
			ctrl_req->wLength);
		वापस -EINVAL;
	पूर्ण

	cdns3_ep0_run_transfer(priv_dev, priv_dev->setup_dma, 6, 1, 0);
	वापस 0;
पूर्ण

/**
 * cdns3_req_ep0_set_isoch_delay -
 * Handling of GET_ISOCH_DELAY standard USB request
 * @priv_dev: extended gadget object
 * @ctrl_req: poपूर्णांकer to received setup packet
 *
 * Returns 0 अगर success, error code on error
 */
अटल पूर्णांक cdns3_req_ep0_set_isoch_delay(काष्ठा cdns3_device *priv_dev,
					 काष्ठा usb_ctrlrequest *ctrl_req)
अणु
	अगर (ctrl_req->wIndex || ctrl_req->wLength)
		वापस -EINVAL;

	priv_dev->isoch_delay = le16_to_cpu(ctrl_req->wValue);

	वापस 0;
पूर्ण

/**
 * cdns3_ep0_standard_request - Handling standard USB requests
 * @priv_dev: extended gadget object
 * @ctrl_req: poपूर्णांकer to received setup packet
 *
 * Returns 0 अगर success, error code on error
 */
अटल पूर्णांक cdns3_ep0_standard_request(काष्ठा cdns3_device *priv_dev,
				      काष्ठा usb_ctrlrequest *ctrl_req)
अणु
	पूर्णांक ret;

	चयन (ctrl_req->bRequest) अणु
	हाल USB_REQ_SET_ADDRESS:
		ret = cdns3_req_ep0_set_address(priv_dev, ctrl_req);
		अवरोध;
	हाल USB_REQ_SET_CONFIGURATION:
		ret = cdns3_req_ep0_set_configuration(priv_dev, ctrl_req);
		अवरोध;
	हाल USB_REQ_GET_STATUS:
		ret = cdns3_req_ep0_get_status(priv_dev, ctrl_req);
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
		ret = cdns3_req_ep0_handle_feature(priv_dev, ctrl_req, 0);
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		ret = cdns3_req_ep0_handle_feature(priv_dev, ctrl_req, 1);
		अवरोध;
	हाल USB_REQ_SET_SEL:
		ret = cdns3_req_ep0_set_sel(priv_dev, ctrl_req);
		अवरोध;
	हाल USB_REQ_SET_ISOCH_DELAY:
		ret = cdns3_req_ep0_set_isoch_delay(priv_dev, ctrl_req);
		अवरोध;
	शेष:
		ret = cdns3_ep0_delegate_req(priv_dev, ctrl_req);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __pending_setup_status_handler(काष्ठा cdns3_device *priv_dev)
अणु
	काष्ठा usb_request *request = priv_dev->pending_status_request;

	अगर (priv_dev->status_completion_no_call && request &&
	    request->complete) अणु
		request->complete(&priv_dev->eps[0]->endpoपूर्णांक, request);
		priv_dev->status_completion_no_call = 0;
	पूर्ण
पूर्ण

व्योम cdns3_pending_setup_status_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cdns3_device *priv_dev = container_of(work, काष्ठा cdns3_device,
			pending_status_wq);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv_dev->lock, flags);
	__pending_setup_status_handler(priv_dev);
	spin_unlock_irqrestore(&priv_dev->lock, flags);
पूर्ण

/**
 * cdns3_ep0_setup_phase - Handling setup USB requests
 * @priv_dev: extended gadget object
 */
अटल व्योम cdns3_ep0_setup_phase(काष्ठा cdns3_device *priv_dev)
अणु
	काष्ठा usb_ctrlrequest *ctrl = priv_dev->setup_buf;
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = priv_dev->eps[0];
	पूर्णांक result;

	priv_dev->ep0_data_dir = ctrl->bRequestType & USB_सूची_IN;

	trace_cdns3_ctrl_req(ctrl);

	अगर (!list_empty(&priv_ep->pending_req_list)) अणु
		काष्ठा usb_request *request;

		request = cdns3_next_request(&priv_ep->pending_req_list);
		priv_ep->dir = priv_dev->ep0_data_dir;
		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request),
				      -ECONNRESET);
	पूर्ण

	अगर (le16_to_cpu(ctrl->wLength))
		priv_dev->ep0_stage = CDNS3_DATA_STAGE;
	अन्यथा
		priv_dev->ep0_stage = CDNS3_STATUS_STAGE;

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		result = cdns3_ep0_standard_request(priv_dev, ctrl);
	अन्यथा
		result = cdns3_ep0_delegate_req(priv_dev, ctrl);

	अगर (result == USB_GADGET_DELAYED_STATUS)
		वापस;

	अगर (result < 0)
		cdns3_ep0_complete_setup(priv_dev, 1, 1);
	अन्यथा अगर (priv_dev->ep0_stage == CDNS3_STATUS_STAGE)
		cdns3_ep0_complete_setup(priv_dev, 0, 1);
पूर्ण

अटल व्योम cdns3_transfer_completed(काष्ठा cdns3_device *priv_dev)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = priv_dev->eps[0];

	अगर (!list_empty(&priv_ep->pending_req_list)) अणु
		काष्ठा usb_request *request;

		trace_cdns3_complete_trb(priv_ep, priv_ep->trb_pool);
		request = cdns3_next_request(&priv_ep->pending_req_list);

		request->actual =
			TRB_LEN(le32_to_cpu(priv_ep->trb_pool->length));

		priv_ep->dir = priv_dev->ep0_data_dir;
		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request), 0);
	पूर्ण

	cdns3_ep0_complete_setup(priv_dev, 0, 0);
पूर्ण

/**
 * cdns3_check_new_setup - Check अगर controller receive new SETUP packet.
 * @priv_dev: extended gadget object
 *
 * The SETUP packet can be kept in on-chip memory or in प्रणाली memory.
 */
अटल bool cdns3_check_new_setup(काष्ठा cdns3_device *priv_dev)
अणु
	u32 ep_sts_reg;

	cdns3_select_ep(priv_dev, USB_सूची_OUT);
	ep_sts_reg = पढ़ोl(&priv_dev->regs->ep_sts);

	वापस !!(ep_sts_reg & (EP_STS_SETUP | EP_STS_STPWAIT));
पूर्ण

/**
 * cdns3_check_ep0_पूर्णांकerrupt_proceed - Processes पूर्णांकerrupt related to endpoपूर्णांक 0
 * @priv_dev: extended gadget object
 * @dir: USB_सूची_IN क्रम IN direction, USB_सूची_OUT क्रम OUT direction
 */
व्योम cdns3_check_ep0_पूर्णांकerrupt_proceed(काष्ठा cdns3_device *priv_dev, पूर्णांक dir)
अणु
	u32 ep_sts_reg;

	cdns3_select_ep(priv_dev, dir);

	ep_sts_reg = पढ़ोl(&priv_dev->regs->ep_sts);
	ग_लिखोl(ep_sts_reg, &priv_dev->regs->ep_sts);

	trace_cdns3_ep0_irq(priv_dev, ep_sts_reg);

	__pending_setup_status_handler(priv_dev);

	अगर (ep_sts_reg & EP_STS_SETUP)
		priv_dev->रुको_क्रम_setup = 1;

	अगर (priv_dev->रुको_क्रम_setup && ep_sts_reg & EP_STS_IOC) अणु
		priv_dev->रुको_क्रम_setup = 0;
		cdns3_ep0_setup_phase(priv_dev);
	पूर्ण अन्यथा अगर ((ep_sts_reg & EP_STS_IOC) || (ep_sts_reg & EP_STS_ISP)) अणु
		priv_dev->ep0_data_dir = dir;
		cdns3_transfer_completed(priv_dev);
	पूर्ण

	अगर (ep_sts_reg & EP_STS_DESCMIS) अणु
		अगर (dir == 0 && !priv_dev->setup_pending)
			cdns3_prepare_setup_packet(priv_dev);
	पूर्ण
पूर्ण

/**
 * cdns3_gadget_ep0_enable
 * @ep: poपूर्णांकer to endpoपूर्णांक zero object
 * @desc: poपूर्णांकer to usb endpoपूर्णांक descriptor
 *
 * Function shouldn't be called by gadget driver,
 * endpoपूर्णांक 0 is allways active
 */
अटल पूर्णांक cdns3_gadget_ep0_enable(काष्ठा usb_ep *ep,
				   स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * cdns3_gadget_ep0_disable
 * @ep: poपूर्णांकer to endpoपूर्णांक zero object
 *
 * Function shouldn't be called by gadget driver,
 * endpoपूर्णांक 0 is allways active
 */
अटल पूर्णांक cdns3_gadget_ep0_disable(काष्ठा usb_ep *ep)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * cdns3_gadget_ep0_set_halt
 * @ep: poपूर्णांकer to endpoपूर्णांक zero object
 * @value: 1 क्रम set stall, 0 क्रम clear stall
 *
 * Returns 0
 */
अटल पूर्णांक cdns3_gadget_ep0_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	/* TODO */
	वापस 0;
पूर्ण

/**
 * cdns3_gadget_ep0_queue Transfer data on endpoपूर्णांक zero
 * @ep: poपूर्णांकer to endpoपूर्णांक zero object
 * @request: poपूर्णांकer to request object
 * @gfp_flags: gfp flags
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
अटल पूर्णांक cdns3_gadget_ep0_queue(काष्ठा usb_ep *ep,
				  काष्ठा usb_request *request,
				  gfp_t gfp_flags)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = ep_to_cdns3_ep(ep);
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u8 zlp = 0;
	पूर्णांक i;

	spin_lock_irqsave(&priv_dev->lock, flags);
	trace_cdns3_ep0_queue(priv_dev, request);

	/* cancel the request अगर controller receive new SETUP packet. */
	अगर (cdns3_check_new_setup(priv_dev)) अणु
		spin_unlock_irqrestore(&priv_dev->lock, flags);
		वापस -ECONNRESET;
	पूर्ण

	/* send STATUS stage. Should be called only क्रम SET_CONFIGURATION */
	अगर (priv_dev->ep0_stage == CDNS3_STATUS_STAGE) अणु
		u32 val;

		cdns3_select_ep(priv_dev, 0x00);

		/*
		 * Configure all non-control EPs which are not enabled by class driver
		 */
		क्रम (i = 0; i < CDNS3_ENDPOINTS_MAX_COUNT; i++) अणु
			priv_ep = priv_dev->eps[i];
			अगर (priv_ep && priv_ep->flags & EP_CLAIMED &&
			    !(priv_ep->flags & EP_ENABLED))
				cdns3_ep_config(priv_ep, 0);
		पूर्ण

		cdns3_set_hw_configuration(priv_dev);
		cdns3_ep0_complete_setup(priv_dev, 0, 1);
		/* रुको until configuration set */
		ret = पढ़ोl_poll_समयout_atomic(&priv_dev->regs->usb_sts, val,
					  val & USB_STS_CFGSTS_MASK, 1, 100);
		अगर (ret == -ETIMEDOUT)
			dev_warn(priv_dev->dev, "timeout for waiting configuration set\n");

		request->actual = 0;
		priv_dev->status_completion_no_call = true;
		priv_dev->pending_status_request = request;
		spin_unlock_irqrestore(&priv_dev->lock, flags);

		/*
		 * Since there is no completion पूर्णांकerrupt क्रम status stage,
		 * it needs to call ->completion in software after
		 * ep0_queue is back.
		 */
		queue_work(प्रणाली_मुक्तzable_wq, &priv_dev->pending_status_wq);
		वापस ret;
	पूर्ण

	अगर (!list_empty(&priv_ep->pending_req_list)) अणु
		dev_err(priv_dev->dev,
			"can't handle multiple requests for ep0\n");
		spin_unlock_irqrestore(&priv_dev->lock, flags);
		वापस -EBUSY;
	पूर्ण

	ret = usb_gadget_map_request_by_dev(priv_dev->sysdev, request,
					    priv_dev->ep0_data_dir);
	अगर (ret) अणु
		spin_unlock_irqrestore(&priv_dev->lock, flags);
		dev_err(priv_dev->dev, "failed to map request\n");
		वापस -EINVAL;
	पूर्ण

	request->status = -EINPROGRESS;
	list_add_tail(&request->list, &priv_ep->pending_req_list);

	अगर (request->zero && request->length &&
	    (request->length % ep->maxpacket == 0))
		zlp = 1;

	cdns3_ep0_run_transfer(priv_dev, request->dma, request->length, 1, zlp);

	spin_unlock_irqrestore(&priv_dev->lock, flags);

	वापस ret;
पूर्ण

/**
 * cdns3_gadget_ep_set_wedge Set wedge on selected endpoपूर्णांक
 * @ep: endpoपूर्णांक object
 *
 * Returns 0
 */
पूर्णांक cdns3_gadget_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = ep_to_cdns3_ep(ep);
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;

	dev_dbg(priv_dev->dev, "Wedge for %s\n", ep->name);
	cdns3_gadget_ep_set_halt(ep, 1);
	priv_ep->flags |= EP_WEDGE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops cdns3_gadget_ep0_ops = अणु
	.enable = cdns3_gadget_ep0_enable,
	.disable = cdns3_gadget_ep0_disable,
	.alloc_request = cdns3_gadget_ep_alloc_request,
	.मुक्त_request = cdns3_gadget_ep_मुक्त_request,
	.queue = cdns3_gadget_ep0_queue,
	.dequeue = cdns3_gadget_ep_dequeue,
	.set_halt = cdns3_gadget_ep0_set_halt,
	.set_wedge = cdns3_gadget_ep_set_wedge,
पूर्ण;

/**
 * cdns3_ep0_config - Configures शेष endpoपूर्णांक
 * @priv_dev: extended gadget object
 *
 * Functions sets parameters: maximal packet size and enables पूर्णांकerrupts
 */
व्योम cdns3_ep0_config(काष्ठा cdns3_device *priv_dev)
अणु
	काष्ठा cdns3_usb_regs __iomem *regs;
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	u32 max_packet_size = 64;
	u32 ep_cfg;

	regs = priv_dev->regs;

	अगर (priv_dev->gadget.speed == USB_SPEED_SUPER)
		max_packet_size = 512;

	priv_ep = priv_dev->eps[0];

	अगर (!list_empty(&priv_ep->pending_req_list)) अणु
		काष्ठा usb_request *request;

		request = cdns3_next_request(&priv_ep->pending_req_list);
		list_del_init(&request->list);
	पूर्ण

	priv_dev->u1_allowed = 0;
	priv_dev->u2_allowed = 0;

	priv_dev->gadget.ep0->maxpacket = max_packet_size;
	cdns3_gadget_ep0_desc.wMaxPacketSize = cpu_to_le16(max_packet_size);

	/* init ep out */
	cdns3_select_ep(priv_dev, USB_सूची_OUT);

	अगर (priv_dev->dev_ver >= DEV_VER_V3) अणु
		cdns3_set_रेजिस्टर_bit(&priv_dev->regs->dtrans,
				       BIT(0) | BIT(16));
		cdns3_set_रेजिस्टर_bit(&priv_dev->regs->tdl_from_trb,
				       BIT(0) | BIT(16));
	पूर्ण

	ep_cfg = EP_CFG_ENABLE | EP_CFG_MAXPKTSIZE(max_packet_size);

	अगर (!(priv_ep->flags & EP_CONFIGURED))
		ग_लिखोl(ep_cfg, &regs->ep_cfg);

	ग_लिखोl(EP_STS_EN_SETUPEN | EP_STS_EN_DESCMISEN | EP_STS_EN_TRBERREN,
	       &regs->ep_sts_en);

	/* init ep in */
	cdns3_select_ep(priv_dev, USB_सूची_IN);

	अगर (!(priv_ep->flags & EP_CONFIGURED))
		ग_लिखोl(ep_cfg, &regs->ep_cfg);

	priv_ep->flags |= EP_CONFIGURED;

	ग_लिखोl(EP_STS_EN_SETUPEN | EP_STS_EN_TRBERREN, &regs->ep_sts_en);

	cdns3_set_रेजिस्टर_bit(&regs->usb_conf, USB_CONF_U1DS | USB_CONF_U2DS);
पूर्ण

/**
 * cdns3_init_ep0 Initializes software endpoपूर्णांक 0 of gadget
 * @priv_dev: extended gadget object
 * @priv_ep: extended endpoपूर्णांक object
 *
 * Returns 0 on success अन्यथा error code.
 */
पूर्णांक cdns3_init_ep0(काष्ठा cdns3_device *priv_dev,
		   काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	प्र_लिखो(priv_ep->name, "ep0");

	/* fill linux fields */
	priv_ep->endpoपूर्णांक.ops = &cdns3_gadget_ep0_ops;
	priv_ep->endpoपूर्णांक.maxburst = 1;
	usb_ep_set_maxpacket_limit(&priv_ep->endpoपूर्णांक,
				   CDNS3_EP0_MAX_PACKET_LIMIT);
	priv_ep->endpoपूर्णांक.address = 0;
	priv_ep->endpoपूर्णांक.caps.type_control = 1;
	priv_ep->endpoपूर्णांक.caps.dir_in = 1;
	priv_ep->endpoपूर्णांक.caps.dir_out = 1;
	priv_ep->endpoपूर्णांक.name = priv_ep->name;
	priv_ep->endpoपूर्णांक.desc = &cdns3_gadget_ep0_desc;
	priv_dev->gadget.ep0 = &priv_ep->endpoपूर्णांक;
	priv_ep->type = USB_ENDPOINT_XFER_CONTROL;

	वापस cdns3_allocate_trb_pool(priv_ep);
पूर्ण
