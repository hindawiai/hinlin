<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence CDNSP DRD Driver.
 *
 * Copyright (C) 2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 */

#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/list.h>

#समावेश "cdnsp-gadget.h"
#समावेश "cdnsp-trace.h"

अटल व्योम cdnsp_ep0_stall(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_request *preq;
	काष्ठा cdnsp_ep *pep;

	pep = &pdev->eps[0];
	preq = next_request(&pep->pending_list);

	अगर (pdev->three_stage_setup) अणु
		cdnsp_halt_endpoपूर्णांक(pdev, pep, true);

		अगर (preq)
			cdnsp_gadget_giveback(pep, preq, -ECONNRESET);
	पूर्ण अन्यथा अणु
		pep->ep_state |= EP0_HALTED_STATUS;

		अगर (preq)
			list_del(&preq->list);

		cdnsp_status_stage(pdev);
	पूर्ण
पूर्ण

अटल पूर्णांक cdnsp_ep0_delegate_req(काष्ठा cdnsp_device *pdev,
				  काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret;

	spin_unlock(&pdev->lock);
	ret = pdev->gadget_driver->setup(&pdev->gadget, ctrl);
	spin_lock(&pdev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_ep0_set_config(काष्ठा cdnsp_device *pdev,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	क्रमागत usb_device_state state = pdev->gadget.state;
	u32 cfg;
	पूर्णांक ret;

	cfg = le16_to_cpu(ctrl->wValue);

	चयन (state) अणु
	हाल USB_STATE_ADDRESS:
		trace_cdnsp_ep0_set_config("from Address state");
		अवरोध;
	हाल USB_STATE_CONFIGURED:
		trace_cdnsp_ep0_set_config("from Configured state");
		अवरोध;
	शेष:
		dev_err(pdev->dev, "Set Configuration - bad device state\n");
		वापस -EINVAL;
	पूर्ण

	ret = cdnsp_ep0_delegate_req(pdev, ctrl);
	अगर (ret)
		वापस ret;

	अगर (!cfg)
		usb_gadget_set_state(&pdev->gadget, USB_STATE_ADDRESS);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_ep0_set_address(काष्ठा cdnsp_device *pdev,
				 काष्ठा usb_ctrlrequest *ctrl)
अणु
	क्रमागत usb_device_state state = pdev->gadget.state;
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	अचिन्हित पूर्णांक slot_state;
	पूर्णांक ret;
	u32 addr;

	addr = le16_to_cpu(ctrl->wValue);

	अगर (addr > 127) अणु
		dev_err(pdev->dev, "Invalid device address %d\n", addr);
		वापस -EINVAL;
	पूर्ण

	slot_ctx = cdnsp_get_slot_ctx(&pdev->out_ctx);

	अगर (state == USB_STATE_CONFIGURED) अणु
		dev_err(pdev->dev, "Can't Set Address from Configured State\n");
		वापस -EINVAL;
	पूर्ण

	pdev->device_address = le16_to_cpu(ctrl->wValue);

	slot_ctx = cdnsp_get_slot_ctx(&pdev->out_ctx);
	slot_state = GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state));
	अगर (slot_state == SLOT_STATE_ADDRESSED)
		cdnsp_reset_device(pdev);

	/*set device address*/
	ret = cdnsp_setup_device(pdev, SETUP_CONTEXT_ADDRESS);
	अगर (ret)
		वापस ret;

	अगर (addr)
		usb_gadget_set_state(&pdev->gadget, USB_STATE_ADDRESS);
	अन्यथा
		usb_gadget_set_state(&pdev->gadget, USB_STATE_DEFAULT);

	वापस 0;
पूर्ण

पूर्णांक cdnsp_status_stage(काष्ठा cdnsp_device *pdev)
अणु
	pdev->ep0_stage = CDNSP_STATUS_STAGE;
	pdev->ep0_preq.request.length = 0;

	वापस cdnsp_ep_enqueue(pdev->ep0_preq.pep, &pdev->ep0_preq);
पूर्ण

अटल पूर्णांक cdnsp_w_index_to_ep_index(u16 wIndex)
अणु
	अगर (!(wIndex & USB_ENDPOINT_NUMBER_MASK))
		वापस 0;

	वापस ((wIndex & USB_ENDPOINT_NUMBER_MASK) * 2) +
		(wIndex & USB_ENDPOINT_सूची_MASK ? 1 : 0) - 1;
पूर्ण

अटल पूर्णांक cdnsp_ep0_handle_status(काष्ठा cdnsp_device *pdev,
				   काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा cdnsp_ep *pep;
	__le16 *response;
	पूर्णांक ep_sts = 0;
	u16 status = 0;
	u32 recipient;

	recipient = ctrl->bRequestType & USB_RECIP_MASK;

	चयन (recipient) अणु
	हाल USB_RECIP_DEVICE:
		status = pdev->gadget.is_selfघातered;
		status |= pdev->may_wakeup << USB_DEVICE_REMOTE_WAKEUP;

		अगर (pdev->gadget.speed >= USB_SPEED_SUPER) अणु
			status |= pdev->u1_allowed << USB_DEV_STAT_U1_ENABLED;
			status |= pdev->u2_allowed << USB_DEV_STAT_U2_ENABLED;
		पूर्ण
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		/*
		 * Function Remote Wake Capable	D0
		 * Function Remote Wakeup	D1
		 */
		वापस cdnsp_ep0_delegate_req(pdev, ctrl);
	हाल USB_RECIP_ENDPOINT:
		ep_sts = cdnsp_w_index_to_ep_index(le16_to_cpu(ctrl->wIndex));
		pep = &pdev->eps[ep_sts];
		ep_sts = GET_EP_CTX_STATE(pep->out_ctx);

		/* check अगर endpoपूर्णांक is stalled */
		अगर (ep_sts == EP_STATE_HALTED)
			status =  BIT(USB_ENDPOINT_HALT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	response = (__le16 *)pdev->setup_buf;
	*response = cpu_to_le16(status);

	pdev->ep0_preq.request.length = माप(*response);
	pdev->ep0_preq.request.buf = pdev->setup_buf;

	वापस cdnsp_ep_enqueue(pdev->ep0_preq.pep, &pdev->ep0_preq);
पूर्ण

अटल व्योम cdnsp_enter_test_mode(काष्ठा cdnsp_device *pdev)
अणु
	u32 temp;

	temp = पढ़ोl(&pdev->active_port->regs->portpmsc) & ~GENMASK(31, 28);
	temp |= PORT_TEST_MODE(pdev->test_mode);
	ग_लिखोl(temp, &pdev->active_port->regs->portpmsc);
पूर्ण

अटल पूर्णांक cdnsp_ep0_handle_feature_device(काष्ठा cdnsp_device *pdev,
					   काष्ठा usb_ctrlrequest *ctrl,
					   पूर्णांक set)
अणु
	क्रमागत usb_device_state state;
	क्रमागत usb_device_speed speed;
	u16 पंचांगode;

	state = pdev->gadget.state;
	speed = pdev->gadget.speed;

	चयन (le16_to_cpu(ctrl->wValue)) अणु
	हाल USB_DEVICE_REMOTE_WAKEUP:
		pdev->may_wakeup = !!set;
		trace_cdnsp_may_wakeup(set);
		अवरोध;
	हाल USB_DEVICE_U1_ENABLE:
		अगर (state != USB_STATE_CONFIGURED || speed < USB_SPEED_SUPER)
			वापस -EINVAL;

		pdev->u1_allowed = !!set;
		trace_cdnsp_u1(set);
		अवरोध;
	हाल USB_DEVICE_U2_ENABLE:
		अगर (state != USB_STATE_CONFIGURED || speed < USB_SPEED_SUPER)
			वापस -EINVAL;

		pdev->u2_allowed = !!set;
		trace_cdnsp_u2(set);
		अवरोध;
	हाल USB_DEVICE_LTM_ENABLE:
		वापस -EINVAL;
	हाल USB_DEVICE_TEST_MODE:
		अगर (state != USB_STATE_CONFIGURED || speed > USB_SPEED_HIGH)
			वापस -EINVAL;

		पंचांगode = le16_to_cpu(ctrl->wIndex);

		अगर (!set || (पंचांगode & 0xff) != 0)
			वापस -EINVAL;

		पंचांगode = पंचांगode >> 8;

		अगर (पंचांगode > USB_TEST_FORCE_ENABLE || पंचांगode < USB_TEST_J)
			वापस -EINVAL;

		pdev->test_mode = पंचांगode;

		/*
		 * Test mode must be set beक्रमe Status Stage but controller
		 * will start testing sequence after Status Stage.
		 */
		cdnsp_enter_test_mode(pdev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_ep0_handle_feature_पूर्णांकf(काष्ठा cdnsp_device *pdev,
					 काष्ठा usb_ctrlrequest *ctrl,
					 पूर्णांक set)
अणु
	u16 wValue, wIndex;
	पूर्णांक ret;

	wValue = le16_to_cpu(ctrl->wValue);
	wIndex = le16_to_cpu(ctrl->wIndex);

	चयन (wValue) अणु
	हाल USB_INTRF_FUNC_SUSPEND:
		ret = cdnsp_ep0_delegate_req(pdev, ctrl);
		अगर (ret)
			वापस ret;

		/*
		 * Remote wakeup is enabled when any function within a device
		 * is enabled क्रम function remote wakeup.
		 */
		अगर (wIndex & USB_INTRF_FUNC_SUSPEND_RW)
			pdev->may_wakeup++;
		अन्यथा
			अगर (pdev->may_wakeup > 0)
				pdev->may_wakeup--;

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_ep0_handle_feature_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
					     काष्ठा usb_ctrlrequest *ctrl,
					     पूर्णांक set)
अणु
	काष्ठा cdnsp_ep *pep;
	u16 wValue;

	wValue = le16_to_cpu(ctrl->wValue);
	pep = &pdev->eps[cdnsp_w_index_to_ep_index(le16_to_cpu(ctrl->wIndex))];

	चयन (wValue) अणु
	हाल USB_ENDPOINT_HALT:
		अगर (!set && (pep->ep_state & EP_WEDGE)) अणु
			/* Resets Sequence Number */
			cdnsp_halt_endpoपूर्णांक(pdev, pep, 0);
			cdnsp_halt_endpoपूर्णांक(pdev, pep, 1);
			अवरोध;
		पूर्ण

		वापस cdnsp_halt_endpoपूर्णांक(pdev, pep, set);
	शेष:
		dev_warn(pdev->dev, "WARN Incorrect wValue %04x\n", wValue);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_ep0_handle_feature(काष्ठा cdnsp_device *pdev,
				    काष्ठा usb_ctrlrequest *ctrl,
				    पूर्णांक set)
अणु
	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		वापस cdnsp_ep0_handle_feature_device(pdev, ctrl, set);
	हाल USB_RECIP_INTERFACE:
		वापस cdnsp_ep0_handle_feature_पूर्णांकf(pdev, ctrl, set);
	हाल USB_RECIP_ENDPOINT:
		वापस cdnsp_ep0_handle_feature_endpoपूर्णांक(pdev, ctrl, set);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक cdnsp_ep0_set_sel(काष्ठा cdnsp_device *pdev,
			     काष्ठा usb_ctrlrequest *ctrl)
अणु
	क्रमागत usb_device_state state = pdev->gadget.state;
	u16 wLength;

	अगर (state == USB_STATE_DEFAULT)
		वापस -EINVAL;

	wLength = le16_to_cpu(ctrl->wLength);

	अगर (wLength != 6) अणु
		dev_err(pdev->dev, "Set SEL should be 6 bytes, got %d\n",
			wLength);
		वापस -EINVAL;
	पूर्ण

	/*
	 * To handle Set SEL we need to receive 6 bytes from Host. So let's
	 * queue a usb_request क्रम 6 bytes.
	 */
	pdev->ep0_preq.request.length = 6;
	pdev->ep0_preq.request.buf = pdev->setup_buf;

	वापस cdnsp_ep_enqueue(pdev->ep0_preq.pep, &pdev->ep0_preq);
पूर्ण

अटल पूर्णांक cdnsp_ep0_set_isoch_delay(काष्ठा cdnsp_device *pdev,
				     काष्ठा usb_ctrlrequest *ctrl)
अणु
	अगर (le16_to_cpu(ctrl->wIndex) || le16_to_cpu(ctrl->wLength))
		वापस -EINVAL;

	pdev->gadget.isoch_delay = le16_to_cpu(ctrl->wValue);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_ep0_std_request(काष्ठा cdnsp_device *pdev,
				 काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret;

	चयन (ctrl->bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		ret = cdnsp_ep0_handle_status(pdev, ctrl);
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
		ret = cdnsp_ep0_handle_feature(pdev, ctrl, 0);
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		ret = cdnsp_ep0_handle_feature(pdev, ctrl, 1);
		अवरोध;
	हाल USB_REQ_SET_ADDRESS:
		ret = cdnsp_ep0_set_address(pdev, ctrl);
		अवरोध;
	हाल USB_REQ_SET_CONFIGURATION:
		ret = cdnsp_ep0_set_config(pdev, ctrl);
		अवरोध;
	हाल USB_REQ_SET_SEL:
		ret = cdnsp_ep0_set_sel(pdev, ctrl);
		अवरोध;
	हाल USB_REQ_SET_ISOCH_DELAY:
		ret = cdnsp_ep0_set_isoch_delay(pdev, ctrl);
		अवरोध;
	हाल USB_REQ_SET_INTERFACE:
		/*
		 * Add request पूर्णांकo pending list to block sending status stage
		 * by libcomposite.
		 */
		list_add_tail(&pdev->ep0_preq.list,
			      &pdev->ep0_preq.pep->pending_list);

		ret = cdnsp_ep0_delegate_req(pdev, ctrl);
		अगर (ret == -EBUSY)
			ret = 0;

		list_del(&pdev->ep0_preq.list);
		अवरोध;
	शेष:
		ret = cdnsp_ep0_delegate_req(pdev, ctrl);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

व्योम cdnsp_setup_analyze(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा usb_ctrlrequest *ctrl = &pdev->setup;
	पूर्णांक ret = 0;
	u16 len;

	trace_cdnsp_ctrl_req(ctrl);

	अगर (!pdev->gadget_driver)
		जाओ out;

	अगर (pdev->gadget.state == USB_STATE_NOTATTACHED) अणु
		dev_err(pdev->dev, "ERR: Setup detected in unattached state\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Restore the ep0 to Stopped/Running state. */
	अगर (pdev->eps[0].ep_state & EP_HALTED) अणु
		trace_cdnsp_ep0_halted("Restore to normal state");
		cdnsp_halt_endpoपूर्णांक(pdev, &pdev->eps[0], 0);
	पूर्ण

	/*
	 * Finishing previous SETUP transfer by removing request from
	 * list and inक्रमming upper layer
	 */
	अगर (!list_empty(&pdev->eps[0].pending_list)) अणु
		काष्ठा cdnsp_request	*req;

		trace_cdnsp_ep0_request("Remove previous");
		req = next_request(&pdev->eps[0].pending_list);
		cdnsp_ep_dequeue(&pdev->eps[0], req);
	पूर्ण

	len = le16_to_cpu(ctrl->wLength);
	अगर (!len) अणु
		pdev->three_stage_setup = false;
		pdev->ep0_expect_in = false;
	पूर्ण अन्यथा अणु
		pdev->three_stage_setup = true;
		pdev->ep0_expect_in = !!(ctrl->bRequestType & USB_सूची_IN);
	पूर्ण

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		ret = cdnsp_ep0_std_request(pdev, ctrl);
	अन्यथा
		ret = cdnsp_ep0_delegate_req(pdev, ctrl);

	अगर (!len)
		pdev->ep0_stage = CDNSP_STATUS_STAGE;

	अगर (ret == USB_GADGET_DELAYED_STATUS) अणु
		trace_cdnsp_ep0_status_stage("delayed");
		वापस;
	पूर्ण
out:
	अगर (ret < 0)
		cdnsp_ep0_stall(pdev);
	अन्यथा अगर (pdev->ep0_stage == CDNSP_STATUS_STAGE)
		cdnsp_status_stage(pdev);
पूर्ण
