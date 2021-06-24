<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>
#समावेश <linux/clk.h>

#समावेश "mv_u3d.h"

#घोषणा DRIVER_DESC		"Marvell PXA USB3.0 Device Controller driver"

अटल स्थिर अक्षर driver_name[] = "mv_u3d";

अटल व्योम mv_u3d_nuke(काष्ठा mv_u3d_ep *ep, पूर्णांक status);
अटल व्योम mv_u3d_stop_activity(काष्ठा mv_u3d *u3d,
			काष्ठा usb_gadget_driver *driver);

/* क्रम endpoपूर्णांक 0 operations */
अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor mv_u3d_ep0_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	0,
	.bmAttributes =		USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize =	MV_U3D_EP0_MAX_PKT_SIZE,
पूर्ण;

अटल व्योम mv_u3d_ep0_reset(काष्ठा mv_u3d *u3d)
अणु
	काष्ठा mv_u3d_ep *ep;
	u32 epxcr;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		ep = &u3d->eps[i];
		ep->u3d = u3d;

		/* ep0 ep context, ep0 in and out share the same ep context */
		ep->ep_context = &u3d->ep_context[1];
	पूर्ण

	/* reset ep state machine */
	/* reset ep0 out */
	epxcr = ioपढ़ो32(&u3d->vuc_regs->epcr[0].epxoutcr0);
	epxcr |= MV_U3D_EPXCR_EP_INIT;
	ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[0].epxoutcr0);
	udelay(5);
	epxcr &= ~MV_U3D_EPXCR_EP_INIT;
	ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[0].epxoutcr0);

	epxcr = ((MV_U3D_EP0_MAX_PKT_SIZE
		<< MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		| MV_U3D_EPXCR_EP_TYPE_CONTROL);
	ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[0].epxoutcr1);

	/* reset ep0 in */
	epxcr = ioपढ़ो32(&u3d->vuc_regs->epcr[0].epxincr0);
	epxcr |= MV_U3D_EPXCR_EP_INIT;
	ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[0].epxincr0);
	udelay(5);
	epxcr &= ~MV_U3D_EPXCR_EP_INIT;
	ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[0].epxincr0);

	epxcr = ((MV_U3D_EP0_MAX_PKT_SIZE
		<< MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT)
		| (1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		| MV_U3D_EPXCR_EP_TYPE_CONTROL);
	ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[0].epxincr1);
पूर्ण

अटल व्योम mv_u3d_ep0_stall(काष्ठा mv_u3d *u3d)
अणु
	u32 पंचांगp;
	dev_dbg(u3d->dev, "%s\n", __func__);

	/* set TX and RX to stall */
	पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[0].epxoutcr0);
	पंचांगp |= MV_U3D_EPXCR_EP_HALT;
	ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[0].epxoutcr0);

	पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[0].epxincr0);
	पंचांगp |= MV_U3D_EPXCR_EP_HALT;
	ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[0].epxincr0);

	/* update ep0 state */
	u3d->ep0_state = MV_U3D_WAIT_FOR_SETUP;
	u3d->ep0_dir = MV_U3D_EP_सूची_OUT;
पूर्ण

अटल पूर्णांक mv_u3d_process_ep_req(काष्ठा mv_u3d *u3d, पूर्णांक index,
	काष्ठा mv_u3d_req *curr_req)
अणु
	काष्ठा mv_u3d_trb	*curr_trb;
	पूर्णांक actual, reमुख्यing_length = 0;
	पूर्णांक direction, ep_num;
	पूर्णांक retval = 0;
	u32 पंचांगp, status, length;

	direction = index % 2;
	ep_num = index / 2;

	actual = curr_req->req.length;

	जबतक (!list_empty(&curr_req->trb_list)) अणु
		curr_trb = list_entry(curr_req->trb_list.next,
					काष्ठा mv_u3d_trb, trb_list);
		अगर (!curr_trb->trb_hw->ctrl.own) अणु
			dev_err(u3d->dev, "%s, TRB own error!\n",
				u3d->eps[index].name);
			वापस 1;
		पूर्ण

		curr_trb->trb_hw->ctrl.own = 0;
		अगर (direction == MV_U3D_EP_सूची_OUT)
			पंचांगp = ioपढ़ो32(&u3d->vuc_regs->rxst[ep_num].statuslo);
		अन्यथा
			पंचांगp = ioपढ़ो32(&u3d->vuc_regs->txst[ep_num].statuslo);

		status = पंचांगp >> MV_U3D_XFERSTATUS_COMPLETE_SHIFT;
		length = पंचांगp & MV_U3D_XFERSTATUS_TRB_LENGTH_MASK;

		अगर (status == MV_U3D_COMPLETE_SUCCESS ||
			(status == MV_U3D_COMPLETE_SHORT_PACKET &&
			direction == MV_U3D_EP_सूची_OUT)) अणु
			reमुख्यing_length += length;
			actual -= reमुख्यing_length;
		पूर्ण अन्यथा अणु
			dev_err(u3d->dev,
				"complete_tr error: ep=%d %s: error = 0x%x\n",
				index >> 1, direction ? "SEND" : "RECV",
				status);
			retval = -EPROTO;
		पूर्ण

		list_del_init(&curr_trb->trb_list);
	पूर्ण
	अगर (retval)
		वापस retval;

	curr_req->req.actual = actual;
	वापस 0;
पूर्ण

/*
 * mv_u3d_करोne() - retire a request; caller blocked irqs
 * @status : request status to be set, only works when
 * request is still in progress.
 */
अटल
व्योम mv_u3d_करोne(काष्ठा mv_u3d_ep *ep, काष्ठा mv_u3d_req *req, पूर्णांक status)
	__releases(&ep->udc->lock)
	__acquires(&ep->udc->lock)
अणु
	काष्ठा mv_u3d *u3d = (काष्ठा mv_u3d *)ep->u3d;

	dev_dbg(u3d->dev, "mv_u3d_done: remove req->queue\n");
	/* Removed the req from ep queue */
	list_del_init(&req->queue);

	/* req.status should be set as -EINPROGRESS in ep_queue() */
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	/* Free trb क्रम the request */
	अगर (!req->chain)
		dma_pool_मुक्त(u3d->trb_pool,
			req->trb_head->trb_hw, req->trb_head->trb_dma);
	अन्यथा अणु
		dma_unmap_single(ep->u3d->gadget.dev.parent,
			(dma_addr_t)req->trb_head->trb_dma,
			req->trb_count * माप(काष्ठा mv_u3d_trb_hw),
			DMA_BIसूचीECTIONAL);
		kमुक्त(req->trb_head->trb_hw);
	पूर्ण
	kमुक्त(req->trb_head);

	usb_gadget_unmap_request(&u3d->gadget, &req->req, mv_u3d_ep_dir(ep));

	अगर (status && (status != -ESHUTDOWN)) अणु
		dev_dbg(u3d->dev, "complete %s req %p stat %d len %u/%u",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);
	पूर्ण

	spin_unlock(&ep->u3d->lock);

	usb_gadget_giveback_request(&ep->ep, &req->req);

	spin_lock(&ep->u3d->lock);
पूर्ण

अटल पूर्णांक mv_u3d_queue_trb(काष्ठा mv_u3d_ep *ep, काष्ठा mv_u3d_req *req)
अणु
	u32 पंचांगp, direction;
	काष्ठा mv_u3d *u3d;
	काष्ठा mv_u3d_ep_context *ep_context;
	पूर्णांक retval = 0;

	u3d = ep->u3d;
	direction = mv_u3d_ep_dir(ep);

	/* ep0 in and out share the same ep context slot 1*/
	अगर (ep->ep_num == 0)
		ep_context = &(u3d->ep_context[1]);
	अन्यथा
		ep_context = &(u3d->ep_context[ep->ep_num * 2 + direction]);

	/* check अगर the pipe is empty or not */
	अगर (!list_empty(&ep->queue)) अणु
		dev_err(u3d->dev, "add trb to non-empty queue!\n");
		retval = -ENOMEM;
		WARN_ON(1);
	पूर्ण अन्यथा अणु
		ep_context->rsvd0 = cpu_to_le32(1);
		ep_context->rsvd1 = 0;

		/* Configure the trb address and set the DCS bit.
		 * Both DCS bit and own bit in trb should be set.
		 */
		ep_context->trb_addr_lo =
			cpu_to_le32(req->trb_head->trb_dma | DCS_ENABLE);
		ep_context->trb_addr_hi = 0;

		/* Ensure that updates to the EP Context will
		 * occure beक्रमe Ring Bell.
		 */
		wmb();

		/* ring bell the ep */
		अगर (ep->ep_num == 0)
			पंचांगp = 0x1;
		अन्यथा
			पंचांगp = ep->ep_num * 2
				+ ((direction == MV_U3D_EP_सूची_OUT) ? 0 : 1);

		ioग_लिखो32(पंचांगp, &u3d->op_regs->करोorbell);
	पूर्ण
	वापस retval;
पूर्ण

अटल काष्ठा mv_u3d_trb *mv_u3d_build_trb_one(काष्ठा mv_u3d_req *req,
				अचिन्हित *length, dma_addr_t *dma)
अणु
	u32 temp;
	अचिन्हित पूर्णांक direction;
	काष्ठा mv_u3d_trb *trb;
	काष्ठा mv_u3d_trb_hw *trb_hw;
	काष्ठा mv_u3d *u3d;

	/* how big will this transfer be? */
	*length = req->req.length - req->req.actual;
	BUG_ON(*length > (अचिन्हित)MV_U3D_EP_MAX_LENGTH_TRANSFER);

	u3d = req->ep->u3d;

	trb = kzalloc(माप(*trb), GFP_ATOMIC);
	अगर (!trb)
		वापस शून्य;

	/*
	 * Be careful that no _GFP_HIGHMEM is set,
	 * or we can not use dma_to_virt
	 * cannot use GFP_KERNEL in spin lock
	 */
	trb_hw = dma_pool_alloc(u3d->trb_pool, GFP_ATOMIC, dma);
	अगर (!trb_hw) अणु
		kमुक्त(trb);
		dev_err(u3d->dev,
			"%s, dma_pool_alloc fail\n", __func__);
		वापस शून्य;
	पूर्ण
	trb->trb_dma = *dma;
	trb->trb_hw = trb_hw;

	/* initialize buffer page poपूर्णांकers */
	temp = (u32)(req->req.dma + req->req.actual);

	trb_hw->buf_addr_lo = cpu_to_le32(temp);
	trb_hw->buf_addr_hi = 0;
	trb_hw->trb_len = cpu_to_le32(*length);
	trb_hw->ctrl.own = 1;

	अगर (req->ep->ep_num == 0)
		trb_hw->ctrl.type = TYPE_DATA;
	अन्यथा
		trb_hw->ctrl.type = TYPE_NORMAL;

	req->req.actual += *length;

	direction = mv_u3d_ep_dir(req->ep);
	अगर (direction == MV_U3D_EP_सूची_IN)
		trb_hw->ctrl.dir = 1;
	अन्यथा
		trb_hw->ctrl.dir = 0;

	/* Enable पूर्णांकerrupt क्रम the last trb of a request */
	अगर (!req->req.no_पूर्णांकerrupt)
		trb_hw->ctrl.ioc = 1;

	trb_hw->ctrl.chain = 0;

	wmb();
	वापस trb;
पूर्ण

अटल पूर्णांक mv_u3d_build_trb_chain(काष्ठा mv_u3d_req *req, अचिन्हित *length,
		काष्ठा mv_u3d_trb *trb, पूर्णांक *is_last)
अणु
	u32 temp;
	अचिन्हित पूर्णांक direction;
	काष्ठा mv_u3d *u3d;

	/* how big will this transfer be? */
	*length = min(req->req.length - req->req.actual,
			(अचिन्हित)MV_U3D_EP_MAX_LENGTH_TRANSFER);

	u3d = req->ep->u3d;

	trb->trb_dma = 0;

	/* initialize buffer page poपूर्णांकers */
	temp = (u32)(req->req.dma + req->req.actual);

	trb->trb_hw->buf_addr_lo = cpu_to_le32(temp);
	trb->trb_hw->buf_addr_hi = 0;
	trb->trb_hw->trb_len = cpu_to_le32(*length);
	trb->trb_hw->ctrl.own = 1;

	अगर (req->ep->ep_num == 0)
		trb->trb_hw->ctrl.type = TYPE_DATA;
	अन्यथा
		trb->trb_hw->ctrl.type = TYPE_NORMAL;

	req->req.actual += *length;

	direction = mv_u3d_ep_dir(req->ep);
	अगर (direction == MV_U3D_EP_सूची_IN)
		trb->trb_hw->ctrl.dir = 1;
	अन्यथा
		trb->trb_hw->ctrl.dir = 0;

	/* zlp is needed अगर req->req.zero is set */
	अगर (req->req.zero) अणु
		अगर (*length == 0 || (*length % req->ep->ep.maxpacket) != 0)
			*is_last = 1;
		अन्यथा
			*is_last = 0;
	पूर्ण अन्यथा अगर (req->req.length == req->req.actual)
		*is_last = 1;
	अन्यथा
		*is_last = 0;

	/* Enable पूर्णांकerrupt क्रम the last trb of a request */
	अगर (*is_last && !req->req.no_पूर्णांकerrupt)
		trb->trb_hw->ctrl.ioc = 1;

	अगर (*is_last)
		trb->trb_hw->ctrl.chain = 0;
	अन्यथा अणु
		trb->trb_hw->ctrl.chain = 1;
		dev_dbg(u3d->dev, "chain trb\n");
	पूर्ण

	wmb();

	वापस 0;
पूर्ण

/* generate TRB linked list क्रम a request
 * usb controller only supports continous trb chain,
 * that trb काष्ठाure physical address should be continous.
 */
अटल पूर्णांक mv_u3d_req_to_trb(काष्ठा mv_u3d_req *req)
अणु
	अचिन्हित count;
	पूर्णांक is_last;
	काष्ठा mv_u3d_trb *trb;
	काष्ठा mv_u3d_trb_hw *trb_hw;
	काष्ठा mv_u3d *u3d;
	dma_addr_t dma;
	अचिन्हित length;
	अचिन्हित trb_num;

	u3d = req->ep->u3d;

	INIT_LIST_HEAD(&req->trb_list);

	length = req->req.length - req->req.actual;
	/* normally the request transfer length is less than 16KB.
	 * we use buil_trb_one() to optimize it.
	 */
	अगर (length <= (अचिन्हित)MV_U3D_EP_MAX_LENGTH_TRANSFER) अणु
		trb = mv_u3d_build_trb_one(req, &count, &dma);
		list_add_tail(&trb->trb_list, &req->trb_list);
		req->trb_head = trb;
		req->trb_count = 1;
		req->chain = 0;
	पूर्ण अन्यथा अणु
		trb_num = length / MV_U3D_EP_MAX_LENGTH_TRANSFER;
		अगर (length % MV_U3D_EP_MAX_LENGTH_TRANSFER)
			trb_num++;

		trb = kसुस्मृति(trb_num, माप(*trb), GFP_ATOMIC);
		अगर (!trb)
			वापस -ENOMEM;

		trb_hw = kसुस्मृति(trb_num, माप(*trb_hw), GFP_ATOMIC);
		अगर (!trb_hw) अणु
			kमुक्त(trb);
			वापस -ENOMEM;
		पूर्ण

		करो अणु
			trb->trb_hw = trb_hw;
			अगर (mv_u3d_build_trb_chain(req, &count,
						trb, &is_last)) अणु
				dev_err(u3d->dev,
					"%s, mv_u3d_build_trb_chain fail\n",
					__func__);
				वापस -EIO;
			पूर्ण

			list_add_tail(&trb->trb_list, &req->trb_list);
			req->trb_count++;
			trb++;
			trb_hw++;
		पूर्ण जबतक (!is_last);

		req->trb_head = list_entry(req->trb_list.next,
					काष्ठा mv_u3d_trb, trb_list);
		req->trb_head->trb_dma = dma_map_single(u3d->gadget.dev.parent,
					req->trb_head->trb_hw,
					trb_num * माप(*trb_hw),
					DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(u3d->gadget.dev.parent,
					req->trb_head->trb_dma)) अणु
			kमुक्त(req->trb_head->trb_hw);
			kमुक्त(req->trb_head);
			वापस -EFAULT;
		पूर्ण

		req->chain = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mv_u3d_start_queue(काष्ठा mv_u3d_ep *ep)
अणु
	काष्ठा mv_u3d *u3d = ep->u3d;
	काष्ठा mv_u3d_req *req;
	पूर्णांक ret;

	अगर (!list_empty(&ep->req_list) && !ep->processing)
		req = list_entry(ep->req_list.next, काष्ठा mv_u3d_req, list);
	अन्यथा
		वापस 0;

	ep->processing = 1;

	/* set up dma mapping */
	ret = usb_gadget_map_request(&u3d->gadget, &req->req,
					mv_u3d_ep_dir(ep));
	अगर (ret)
		जाओ अवरोध_processing;

	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->trb_count = 0;

	/* build trbs */
	ret = mv_u3d_req_to_trb(req);
	अगर (ret) अणु
		dev_err(u3d->dev, "%s, mv_u3d_req_to_trb fail\n", __func__);
		जाओ अवरोध_processing;
	पूर्ण

	/* and push them to device queue */
	ret = mv_u3d_queue_trb(ep, req);
	अगर (ret)
		जाओ अवरोध_processing;

	/* irq handler advances the queue */
	list_add_tail(&req->queue, &ep->queue);

	वापस 0;

अवरोध_processing:
	ep->processing = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक mv_u3d_ep_enable(काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा mv_u3d *u3d;
	काष्ठा mv_u3d_ep *ep;
	u16 max = 0;
	अचिन्हित maxburst = 0;
	u32 epxcr, direction;

	अगर (!_ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;

	ep = container_of(_ep, काष्ठा mv_u3d_ep, ep);
	u3d = ep->u3d;

	अगर (!u3d->driver || u3d->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	direction = mv_u3d_ep_dir(ep);
	max = le16_to_cpu(desc->wMaxPacketSize);

	अगर (!_ep->maxburst)
		_ep->maxburst = 1;
	maxburst = _ep->maxburst;

	/* Set the max burst size */
	चयन (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (maxburst > 16) अणु
			dev_dbg(u3d->dev,
				"max burst should not be greater "
				"than 16 on bulk ep\n");
			maxburst = 1;
			_ep->maxburst = maxburst;
		पूर्ण
		dev_dbg(u3d->dev,
			"maxburst: %d on bulk %s\n", maxburst, ep->name);
		अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:
		/* control transfer only supports maxburst as one */
		maxburst = 1;
		_ep->maxburst = maxburst;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (maxburst != 1) अणु
			dev_dbg(u3d->dev,
				"max burst should be 1 on int ep "
				"if transfer size is not 1024\n");
			maxburst = 1;
			_ep->maxburst = maxburst;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (maxburst != 1) अणु
			dev_dbg(u3d->dev,
				"max burst should be 1 on isoc ep "
				"if transfer size is not 1024\n");
			maxburst = 1;
			_ep->maxburst = maxburst;
		पूर्ण
		अवरोध;
	शेष:
		जाओ en_करोne;
	पूर्ण

	ep->ep.maxpacket = max;
	ep->ep.desc = desc;
	ep->enabled = 1;

	/* Enable the endpoपूर्णांक क्रम Rx or Tx and set the endpoपूर्णांक type */
	अगर (direction == MV_U3D_EP_सूची_OUT) अणु
		epxcr = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
		epxcr |= MV_U3D_EPXCR_EP_INIT;
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
		udelay(5);
		epxcr &= ~MV_U3D_EPXCR_EP_INIT;
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);

		epxcr = ((max << MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT)
		      | ((maxburst - 1) << MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT)
		      | (1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		      | (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK));
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr1);
	पूर्ण अन्यथा अणु
		epxcr = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
		epxcr |= MV_U3D_EPXCR_EP_INIT;
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
		udelay(5);
		epxcr &= ~MV_U3D_EPXCR_EP_INIT;
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxincr0);

		epxcr = ((max << MV_U3D_EPXCR_MAX_PACKET_SIZE_SHIFT)
		      | ((maxburst - 1) << MV_U3D_EPXCR_MAX_BURST_SIZE_SHIFT)
		      | (1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		      | (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK));
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxincr1);
	पूर्ण

	वापस 0;
en_करोne:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक  mv_u3d_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा mv_u3d *u3d;
	काष्ठा mv_u3d_ep *ep;
	u32 epxcr, direction;
	अचिन्हित दीर्घ flags;

	अगर (!_ep)
		वापस -EINVAL;

	ep = container_of(_ep, काष्ठा mv_u3d_ep, ep);
	अगर (!ep->ep.desc)
		वापस -EINVAL;

	u3d = ep->u3d;

	direction = mv_u3d_ep_dir(ep);

	/* nuke all pending requests (करोes flush) */
	spin_lock_irqsave(&u3d->lock, flags);
	mv_u3d_nuke(ep, -ESHUTDOWN);
	spin_unlock_irqrestore(&u3d->lock, flags);

	/* Disable the endpoपूर्णांक क्रम Rx or Tx and reset the endpoपूर्णांक type */
	अगर (direction == MV_U3D_EP_सूची_OUT) अणु
		epxcr = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxoutcr1);
		epxcr &= ~((1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		      | USB_ENDPOINT_XFERTYPE_MASK);
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr1);
	पूर्ण अन्यथा अणु
		epxcr = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxincr1);
		epxcr &= ~((1 << MV_U3D_EPXCR_EP_ENABLE_SHIFT)
		      | USB_ENDPOINT_XFERTYPE_MASK);
		ioग_लिखो32(epxcr, &u3d->vuc_regs->epcr[ep->ep_num].epxincr1);
	पूर्ण

	ep->enabled = 0;

	ep->ep.desc = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा usb_request *
mv_u3d_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा mv_u3d_req *req = शून्य;

	req = kzalloc(माप *req, gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम mv_u3d_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा mv_u3d_req *req = container_of(_req, काष्ठा mv_u3d_req, req);

	kमुक्त(req);
पूर्ण

अटल व्योम mv_u3d_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा mv_u3d *u3d;
	u32 direction;
	काष्ठा mv_u3d_ep *ep = container_of(_ep, काष्ठा mv_u3d_ep, ep);
	अचिन्हित पूर्णांक loops;
	u32 पंचांगp;

	/* अगर endpoपूर्णांक is not enabled, cannot flush endpoपूर्णांक */
	अगर (!ep->enabled)
		वापस;

	u3d = ep->u3d;
	direction = mv_u3d_ep_dir(ep);

	/* ep0 need clear bit after flushing fअगरo. */
	अगर (!ep->ep_num) अणु
		अगर (direction == MV_U3D_EP_सूची_OUT) अणु
			पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[0].epxoutcr0);
			पंचांगp |= MV_U3D_EPXCR_EP_FLUSH;
			ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[0].epxoutcr0);
			udelay(10);
			पंचांगp &= ~MV_U3D_EPXCR_EP_FLUSH;
			ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[0].epxoutcr0);
		पूर्ण अन्यथा अणु
			पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[0].epxincr0);
			पंचांगp |= MV_U3D_EPXCR_EP_FLUSH;
			ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[0].epxincr0);
			udelay(10);
			पंचांगp &= ~MV_U3D_EPXCR_EP_FLUSH;
			ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[0].epxincr0);
		पूर्ण
		वापस;
	पूर्ण

	अगर (direction == MV_U3D_EP_सूची_OUT) अणु
		पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
		पंचांगp |= MV_U3D_EPXCR_EP_FLUSH;
		ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);

		/* Wait until flushing completed */
		loops = LOOPS(MV_U3D_FLUSH_TIMEOUT);
		जबतक (ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0) &
			MV_U3D_EPXCR_EP_FLUSH) अणु
			/*
			 * EP_FLUSH bit should be cleared to indicate this
			 * operation is complete
			 */
			अगर (loops == 0) अणु
				dev_dbg(u3d->dev,
				    "EP FLUSH TIMEOUT for ep%d%s\n", ep->ep_num,
				    direction ? "in" : "out");
				वापस;
			पूर्ण
			loops--;
			udelay(LOOPS_USEC);
		पूर्ण
	पूर्ण अन्यथा अणु	/* EP_सूची_IN */
		पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
		पंचांगp |= MV_U3D_EPXCR_EP_FLUSH;
		ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[ep->ep_num].epxincr0);

		/* Wait until flushing completed */
		loops = LOOPS(MV_U3D_FLUSH_TIMEOUT);
		जबतक (ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxincr0) &
			MV_U3D_EPXCR_EP_FLUSH) अणु
			/*
			* EP_FLUSH bit should be cleared to indicate this
			* operation is complete
			*/
			अगर (loops == 0) अणु
				dev_dbg(u3d->dev,
				    "EP FLUSH TIMEOUT for ep%d%s\n", ep->ep_num,
				    direction ? "in" : "out");
				वापस;
			पूर्ण
			loops--;
			udelay(LOOPS_USEC);
		पूर्ण
	पूर्ण
पूर्ण

/* queues (submits) an I/O request to an endpoपूर्णांक */
अटल पूर्णांक
mv_u3d_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा mv_u3d_ep *ep;
	काष्ठा mv_u3d_req *req;
	काष्ठा mv_u3d *u3d;
	अचिन्हित दीर्घ flags;
	पूर्णांक is_first_req = 0;

	अगर (unlikely(!_ep || !_req))
		वापस -EINVAL;

	ep = container_of(_ep, काष्ठा mv_u3d_ep, ep);
	u3d = ep->u3d;

	req = container_of(_req, काष्ठा mv_u3d_req, req);

	अगर (!ep->ep_num
		&& u3d->ep0_state == MV_U3D_STATUS_STAGE
		&& !_req->length) अणु
		dev_dbg(u3d->dev, "ep0 status stage\n");
		u3d->ep0_state = MV_U3D_WAIT_FOR_SETUP;
		वापस 0;
	पूर्ण

	dev_dbg(u3d->dev, "%s: %s, req: 0x%p\n",
			__func__, _ep->name, req);

	/* catch various bogus parameters */
	अगर (!req->req.complete || !req->req.buf
			|| !list_empty(&req->queue)) अणु
		dev_err(u3d->dev,
			"%s, bad params, _req: 0x%p,"
			"req->req.complete: 0x%p, req->req.buf: 0x%p,"
			"list_empty: 0x%x\n",
			__func__, _req,
			req->req.complete, req->req.buf,
			list_empty(&req->queue));
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(!ep->ep.desc)) अणु
		dev_err(u3d->dev, "%s, bad ep\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (ep->ep.desc->bmAttributes == USB_ENDPOINT_XFER_ISOC) अणु
		अगर (req->req.length > ep->ep.maxpacket)
			वापस -EMSGSIZE;
	पूर्ण

	अगर (!u3d->driver || u3d->gadget.speed == USB_SPEED_UNKNOWN) अणु
		dev_err(u3d->dev,
			"bad params of driver/speed\n");
		वापस -ESHUTDOWN;
	पूर्ण

	req->ep = ep;

	/* Software list handles usb request. */
	spin_lock_irqsave(&ep->req_lock, flags);
	is_first_req = list_empty(&ep->req_list);
	list_add_tail(&req->list, &ep->req_list);
	spin_unlock_irqrestore(&ep->req_lock, flags);
	अगर (!is_first_req) अणु
		dev_dbg(u3d->dev, "list is not empty\n");
		वापस 0;
	पूर्ण

	dev_dbg(u3d->dev, "call mv_u3d_start_queue from usb_ep_queue\n");
	spin_lock_irqsave(&u3d->lock, flags);
	mv_u3d_start_queue(ep);
	spin_unlock_irqrestore(&u3d->lock, flags);
	वापस 0;
पूर्ण

/* dequeues (cancels, unlinks) an I/O request from an endpoपूर्णांक */
अटल पूर्णांक mv_u3d_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा mv_u3d_ep *ep;
	काष्ठा mv_u3d_req *req;
	काष्ठा mv_u3d *u3d;
	काष्ठा mv_u3d_ep_context *ep_context;
	काष्ठा mv_u3d_req *next_req;

	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!_ep || !_req)
		वापस -EINVAL;

	ep = container_of(_ep, काष्ठा mv_u3d_ep, ep);
	u3d = ep->u3d;

	spin_lock_irqsave(&ep->u3d->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* The request is in progress, or completed but not dequeued */
	अगर (ep->queue.next == &req->queue) अणु
		_req->status = -ECONNRESET;
		mv_u3d_ep_fअगरo_flush(_ep);

		/* The request isn't the last request in this ep queue */
		अगर (req->queue.next != &ep->queue) अणु
			dev_dbg(u3d->dev,
				"it is the last request in this ep queue\n");
			ep_context = ep->ep_context;
			next_req = list_entry(req->queue.next,
					काष्ठा mv_u3d_req, queue);

			/* Poपूर्णांक first TRB of next request to the EP context. */
			ioग_लिखो32((अचिन्हित दीर्घ) next_req->trb_head,
					&ep_context->trb_addr_lo);
		पूर्ण अन्यथा अणु
			काष्ठा mv_u3d_ep_context *ep_context;
			ep_context = ep->ep_context;
			ep_context->trb_addr_lo = 0;
			ep_context->trb_addr_hi = 0;
		पूर्ण

	पूर्ण अन्यथा
		WARN_ON(1);

	mv_u3d_करोne(ep, req, -ECONNRESET);

	/* हटाओ the req from the ep req list */
	अगर (!list_empty(&ep->req_list)) अणु
		काष्ठा mv_u3d_req *curr_req;
		curr_req = list_entry(ep->req_list.next,
					काष्ठा mv_u3d_req, list);
		अगर (curr_req == req) अणु
			list_del_init(&req->list);
			ep->processing = 0;
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&ep->u3d->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम
mv_u3d_ep_set_stall(काष्ठा mv_u3d *u3d, u8 ep_num, u8 direction, पूर्णांक stall)
अणु
	u32 पंचांगp;
	काष्ठा mv_u3d_ep *ep = u3d->eps;

	dev_dbg(u3d->dev, "%s\n", __func__);
	अगर (direction == MV_U3D_EP_सूची_OUT) अणु
		पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
		अगर (stall)
			पंचांगp |= MV_U3D_EPXCR_EP_HALT;
		अन्यथा
			पंचांगp &= ~MV_U3D_EPXCR_EP_HALT;
		ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[ep->ep_num].epxoutcr0);
	पूर्ण अन्यथा अणु
		पंचांगp = ioपढ़ो32(&u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
		अगर (stall)
			पंचांगp |= MV_U3D_EPXCR_EP_HALT;
		अन्यथा
			पंचांगp &= ~MV_U3D_EPXCR_EP_HALT;
		ioग_लिखो32(पंचांगp, &u3d->vuc_regs->epcr[ep->ep_num].epxincr0);
	पूर्ण
पूर्ण

अटल पूर्णांक mv_u3d_ep_set_halt_wedge(काष्ठा usb_ep *_ep, पूर्णांक halt, पूर्णांक wedge)
अणु
	काष्ठा mv_u3d_ep *ep;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक status = 0;
	काष्ठा mv_u3d *u3d;

	ep = container_of(_ep, काष्ठा mv_u3d_ep, ep);
	u3d = ep->u3d;
	अगर (!ep->ep.desc) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (ep->ep.desc->bmAttributes == USB_ENDPOINT_XFER_ISOC) अणु
		status = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/*
	 * Attempt to halt IN ep will fail अगर any transfer requests
	 * are still queue
	 */
	अगर (halt && (mv_u3d_ep_dir(ep) == MV_U3D_EP_सूची_IN)
			&& !list_empty(&ep->queue)) अणु
		status = -EAGAIN;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&ep->u3d->lock, flags);
	mv_u3d_ep_set_stall(u3d, ep->ep_num, mv_u3d_ep_dir(ep), halt);
	अगर (halt && wedge)
		ep->wedge = 1;
	अन्यथा अगर (!halt)
		ep->wedge = 0;
	spin_unlock_irqrestore(&ep->u3d->lock, flags);

	अगर (ep->ep_num == 0)
		u3d->ep0_dir = MV_U3D_EP_सूची_OUT;
out:
	वापस status;
पूर्ण

अटल पूर्णांक mv_u3d_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक halt)
अणु
	वापस mv_u3d_ep_set_halt_wedge(_ep, halt, 0);
पूर्ण

अटल पूर्णांक mv_u3d_ep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस mv_u3d_ep_set_halt_wedge(_ep, 1, 1);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops mv_u3d_ep_ops = अणु
	.enable		= mv_u3d_ep_enable,
	.disable	= mv_u3d_ep_disable,

	.alloc_request	= mv_u3d_alloc_request,
	.मुक्त_request	= mv_u3d_मुक्त_request,

	.queue		= mv_u3d_ep_queue,
	.dequeue	= mv_u3d_ep_dequeue,

	.set_wedge	= mv_u3d_ep_set_wedge,
	.set_halt	= mv_u3d_ep_set_halt,
	.fअगरo_flush	= mv_u3d_ep_fअगरo_flush,
पूर्ण;

अटल व्योम mv_u3d_controller_stop(काष्ठा mv_u3d *u3d)
अणु
	u32 पंचांगp;

	अगर (!u3d->घड़ी_gating && u3d->vbus_valid_detect)
		ioग_लिखो32(MV_U3D_INTR_ENABLE_VBUS_VALID,
				&u3d->vuc_regs->पूर्णांकrenable);
	अन्यथा
		ioग_लिखो32(0, &u3d->vuc_regs->पूर्णांकrenable);
	ioग_लिखो32(~0x0, &u3d->vuc_regs->endcomplete);
	ioग_लिखो32(~0x0, &u3d->vuc_regs->trbunderrun);
	ioग_लिखो32(~0x0, &u3d->vuc_regs->trbcomplete);
	ioग_लिखो32(~0x0, &u3d->vuc_regs->linkchange);
	ioग_लिखो32(0x1, &u3d->vuc_regs->setuplock);

	/* Reset the RUN bit in the command रेजिस्टर to stop USB */
	पंचांगp = ioपढ़ो32(&u3d->op_regs->usbcmd);
	पंचांगp &= ~MV_U3D_CMD_RUN_STOP;
	ioग_लिखो32(पंचांगp, &u3d->op_regs->usbcmd);
	dev_dbg(u3d->dev, "after u3d_stop, USBCMD 0x%x\n",
		ioपढ़ो32(&u3d->op_regs->usbcmd));
पूर्ण

अटल व्योम mv_u3d_controller_start(काष्ठा mv_u3d *u3d)
अणु
	u32 usbपूर्णांकr;
	u32 temp;

	/* enable link LTSSM state machine */
	temp = ioपढ़ो32(&u3d->vuc_regs->ltssm);
	temp |= MV_U3D_LTSSM_PHY_INIT_DONE;
	ioग_लिखो32(temp, &u3d->vuc_regs->ltssm);

	/* Enable पूर्णांकerrupts */
	usbपूर्णांकr = MV_U3D_INTR_ENABLE_LINK_CHG | MV_U3D_INTR_ENABLE_TXDESC_ERR |
		MV_U3D_INTR_ENABLE_RXDESC_ERR | MV_U3D_INTR_ENABLE_TX_COMPLETE |
		MV_U3D_INTR_ENABLE_RX_COMPLETE | MV_U3D_INTR_ENABLE_SETUP |
		(u3d->vbus_valid_detect ? MV_U3D_INTR_ENABLE_VBUS_VALID : 0);
	ioग_लिखो32(usbपूर्णांकr, &u3d->vuc_regs->पूर्णांकrenable);

	/* Enable ctrl ep */
	ioग_लिखो32(0x1, &u3d->vuc_regs->ctrlepenable);

	/* Set the Run bit in the command रेजिस्टर */
	ioग_लिखो32(MV_U3D_CMD_RUN_STOP, &u3d->op_regs->usbcmd);
	dev_dbg(u3d->dev, "after u3d_start, USBCMD 0x%x\n",
		ioपढ़ो32(&u3d->op_regs->usbcmd));
पूर्ण

अटल पूर्णांक mv_u3d_controller_reset(काष्ठा mv_u3d *u3d)
अणु
	अचिन्हित पूर्णांक loops;
	u32 पंचांगp;

	/* Stop the controller */
	पंचांगp = ioपढ़ो32(&u3d->op_regs->usbcmd);
	पंचांगp &= ~MV_U3D_CMD_RUN_STOP;
	ioग_लिखो32(पंचांगp, &u3d->op_regs->usbcmd);

	/* Reset the controller to get शेष values */
	ioग_लिखो32(MV_U3D_CMD_CTRL_RESET, &u3d->op_regs->usbcmd);

	/* रुको क्रम reset to complete */
	loops = LOOPS(MV_U3D_RESET_TIMEOUT);
	जबतक (ioपढ़ो32(&u3d->op_regs->usbcmd) & MV_U3D_CMD_CTRL_RESET) अणु
		अगर (loops == 0) अणु
			dev_err(u3d->dev,
				"Wait for RESET completed TIMEOUT\n");
			वापस -ETIMEDOUT;
		पूर्ण
		loops--;
		udelay(LOOPS_USEC);
	पूर्ण

	/* Configure the Endpoपूर्णांक Context Address */
	ioग_लिखो32(u3d->ep_context_dma, &u3d->op_regs->dcbaapl);
	ioग_लिखो32(0, &u3d->op_regs->dcbaaph);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_u3d_enable(काष्ठा mv_u3d *u3d)
अणु
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(u3d->dev);
	पूर्णांक retval;

	अगर (u3d->active)
		वापस 0;

	अगर (!u3d->घड़ी_gating) अणु
		u3d->active = 1;
		वापस 0;
	पूर्ण

	dev_dbg(u3d->dev, "enable u3d\n");
	clk_enable(u3d->clk);
	अगर (pdata->phy_init) अणु
		retval = pdata->phy_init(u3d->phy_regs);
		अगर (retval) अणु
			dev_err(u3d->dev,
				"init phy error %d\n", retval);
			clk_disable(u3d->clk);
			वापस retval;
		पूर्ण
	पूर्ण
	u3d->active = 1;

	वापस 0;
पूर्ण

अटल व्योम mv_u3d_disable(काष्ठा mv_u3d *u3d)
अणु
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(u3d->dev);
	अगर (u3d->घड़ी_gating && u3d->active) अणु
		dev_dbg(u3d->dev, "disable u3d\n");
		अगर (pdata->phy_deinit)
			pdata->phy_deinit(u3d->phy_regs);
		clk_disable(u3d->clk);
		u3d->active = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mv_u3d_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा mv_u3d *u3d;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	u3d = container_of(gadget, काष्ठा mv_u3d, gadget);

	spin_lock_irqsave(&u3d->lock, flags);

	u3d->vbus_active = (is_active != 0);
	dev_dbg(u3d->dev, "%s: softconnect %d, vbus_active %d\n",
		__func__, u3d->softconnect, u3d->vbus_active);
	/*
	 * 1. बाह्यal VBUS detect: we can disable/enable घड़ी on demand.
	 * 2. UDC VBUS detect: we have to enable घड़ी all the समय.
	 * 3. No VBUS detect: we have to enable घड़ी all the समय.
	 */
	अगर (u3d->driver && u3d->softconnect && u3d->vbus_active) अणु
		retval = mv_u3d_enable(u3d);
		अगर (retval == 0) अणु
			/*
			 * after घड़ी is disabled, we lost all the रेजिस्टर
			 *  context. We have to re-init रेजिस्टरs
			 */
			mv_u3d_controller_reset(u3d);
			mv_u3d_ep0_reset(u3d);
			mv_u3d_controller_start(u3d);
		पूर्ण
	पूर्ण अन्यथा अगर (u3d->driver && u3d->softconnect) अणु
		अगर (!u3d->active)
			जाओ out;

		/* stop all the transfer in queue*/
		mv_u3d_stop_activity(u3d, u3d->driver);
		mv_u3d_controller_stop(u3d);
		mv_u3d_disable(u3d);
	पूर्ण

out:
	spin_unlock_irqrestore(&u3d->lock, flags);
	वापस retval;
पूर्ण

/* स्थिरrain controller's VBUS घातer usage
 * This call is used by gadget drivers during SET_CONFIGURATION calls,
 * reporting how much घातer the device may consume.  For example, this
 * could affect how quickly batteries are reअक्षरged.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक mv_u3d_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु
	काष्ठा mv_u3d *u3d = container_of(gadget, काष्ठा mv_u3d, gadget);

	u3d->घातer = mA;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_u3d_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा mv_u3d *u3d = container_of(gadget, काष्ठा mv_u3d, gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	spin_lock_irqsave(&u3d->lock, flags);

	dev_dbg(u3d->dev, "%s: softconnect %d, vbus_active %d\n",
		__func__, u3d->softconnect, u3d->vbus_active);
	u3d->softconnect = (is_on != 0);
	अगर (u3d->driver && u3d->softconnect && u3d->vbus_active) अणु
		retval = mv_u3d_enable(u3d);
		अगर (retval == 0) अणु
			/*
			 * after घड़ी is disabled, we lost all the रेजिस्टर
			 *  context. We have to re-init रेजिस्टरs
			 */
			mv_u3d_controller_reset(u3d);
			mv_u3d_ep0_reset(u3d);
			mv_u3d_controller_start(u3d);
		पूर्ण
	पूर्ण अन्यथा अगर (u3d->driver && u3d->vbus_active) अणु
		/* stop all the transfer in queue*/
		mv_u3d_stop_activity(u3d, u3d->driver);
		mv_u3d_controller_stop(u3d);
		mv_u3d_disable(u3d);
	पूर्ण

	spin_unlock_irqrestore(&u3d->lock, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक mv_u3d_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा mv_u3d *u3d = container_of(g, काष्ठा mv_u3d, gadget);
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(u3d->dev);
	अचिन्हित दीर्घ flags;

	अगर (u3d->driver)
		वापस -EBUSY;

	spin_lock_irqsave(&u3d->lock, flags);

	अगर (!u3d->घड़ी_gating) अणु
		clk_enable(u3d->clk);
		अगर (pdata->phy_init)
			pdata->phy_init(u3d->phy_regs);
	पूर्ण

	/* hook up the driver ... */
	driver->driver.bus = शून्य;
	u3d->driver = driver;

	u3d->ep0_dir = USB_सूची_OUT;

	spin_unlock_irqrestore(&u3d->lock, flags);

	u3d->vbus_valid_detect = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_u3d_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा mv_u3d *u3d = container_of(g, काष्ठा mv_u3d, gadget);
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(u3d->dev);
	अचिन्हित दीर्घ flags;

	u3d->vbus_valid_detect = 0;
	spin_lock_irqsave(&u3d->lock, flags);

	/* enable घड़ी to access controller रेजिस्टर */
	clk_enable(u3d->clk);
	अगर (pdata->phy_init)
		pdata->phy_init(u3d->phy_regs);

	mv_u3d_controller_stop(u3d);
	/* stop all usb activities */
	u3d->gadget.speed = USB_SPEED_UNKNOWN;
	mv_u3d_stop_activity(u3d, शून्य);
	mv_u3d_disable(u3d);

	अगर (pdata->phy_deinit)
		pdata->phy_deinit(u3d->phy_regs);
	clk_disable(u3d->clk);

	spin_unlock_irqrestore(&u3d->lock, flags);

	u3d->driver = शून्य;

	वापस 0;
पूर्ण

/* device controller usb_gadget_ops काष्ठाure */
अटल स्थिर काष्ठा usb_gadget_ops mv_u3d_ops = अणु
	/* notअगरy controller that VBUS is घातered or not */
	.vbus_session	= mv_u3d_vbus_session,

	/* स्थिरrain controller's VBUS घातer usage */
	.vbus_draw	= mv_u3d_vbus_draw,

	.pullup		= mv_u3d_pullup,
	.udc_start	= mv_u3d_start,
	.udc_stop	= mv_u3d_stop,
पूर्ण;

अटल पूर्णांक mv_u3d_eps_init(काष्ठा mv_u3d *u3d)
अणु
	काष्ठा mv_u3d_ep	*ep;
	अक्षर name[14];
	पूर्णांक i;

	/* initialize ep0, ep0 in/out use eps[1] */
	ep = &u3d->eps[1];
	ep->u3d = u3d;
	म_नकलन(ep->name, "ep0", माप(ep->name));
	ep->ep.name = ep->name;
	ep->ep.ops = &mv_u3d_ep_ops;
	ep->wedge = 0;
	usb_ep_set_maxpacket_limit(&ep->ep, MV_U3D_EP0_MAX_PKT_SIZE);
	ep->ep.caps.type_control = true;
	ep->ep.caps.dir_in = true;
	ep->ep.caps.dir_out = true;
	ep->ep_num = 0;
	ep->ep.desc = &mv_u3d_ep0_desc;
	INIT_LIST_HEAD(&ep->queue);
	INIT_LIST_HEAD(&ep->req_list);
	ep->ep_type = USB_ENDPOINT_XFER_CONTROL;

	/* add ep0 ep_context */
	ep->ep_context = &u3d->ep_context[1];

	/* initialize other endpoपूर्णांकs */
	क्रम (i = 2; i < u3d->max_eps * 2; i++) अणु
		ep = &u3d->eps[i];
		अगर (i & 1) अणु
			snम_लिखो(name, माप(name), "ep%din", i >> 1);
			ep->direction = MV_U3D_EP_सूची_IN;
			ep->ep.caps.dir_in = true;
		पूर्ण अन्यथा अणु
			snम_लिखो(name, माप(name), "ep%dout", i >> 1);
			ep->direction = MV_U3D_EP_सूची_OUT;
			ep->ep.caps.dir_out = true;
		पूर्ण
		ep->u3d = u3d;
		म_नकलन(ep->name, name, माप(ep->name));
		ep->ep.name = ep->name;

		ep->ep.caps.type_iso = true;
		ep->ep.caps.type_bulk = true;
		ep->ep.caps.type_पूर्णांक = true;

		ep->ep.ops = &mv_u3d_ep_ops;
		usb_ep_set_maxpacket_limit(&ep->ep, (अचिन्हित लघु) ~0);
		ep->ep_num = i / 2;

		INIT_LIST_HEAD(&ep->queue);
		list_add_tail(&ep->ep.ep_list, &u3d->gadget.ep_list);

		INIT_LIST_HEAD(&ep->req_list);
		spin_lock_init(&ep->req_lock);
		ep->ep_context = &u3d->ep_context[i];
	पूर्ण

	वापस 0;
पूर्ण

/* delete all endpoपूर्णांक requests, called with spinlock held */
अटल व्योम mv_u3d_nuke(काष्ठा mv_u3d_ep *ep, पूर्णांक status)
अणु
	/* endpoपूर्णांक fअगरo flush */
	mv_u3d_ep_fअगरo_flush(&ep->ep);

	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा mv_u3d_req *req = शून्य;
		req = list_entry(ep->queue.next, काष्ठा mv_u3d_req, queue);
		mv_u3d_करोne(ep, req, status);
	पूर्ण
पूर्ण

/* stop all USB activities */
अटल
व्योम mv_u3d_stop_activity(काष्ठा mv_u3d *u3d, काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा mv_u3d_ep	*ep;

	mv_u3d_nuke(&u3d->eps[1], -ESHUTDOWN);

	list_क्रम_each_entry(ep, &u3d->gadget.ep_list, ep.ep_list) अणु
		mv_u3d_nuke(ep, -ESHUTDOWN);
	पूर्ण

	/* report disconnect; the driver is alपढ़ोy quiesced */
	अगर (driver) अणु
		spin_unlock(&u3d->lock);
		driver->disconnect(&u3d->gadget);
		spin_lock(&u3d->lock);
	पूर्ण
पूर्ण

अटल व्योम mv_u3d_irq_process_error(काष्ठा mv_u3d *u3d)
अणु
	/* Increment the error count */
	u3d->errors++;
	dev_err(u3d->dev, "%s\n", __func__);
पूर्ण

अटल व्योम mv_u3d_irq_process_link_change(काष्ठा mv_u3d *u3d)
अणु
	u32 linkchange;

	linkchange = ioपढ़ो32(&u3d->vuc_regs->linkchange);
	ioग_लिखो32(linkchange, &u3d->vuc_regs->linkchange);

	dev_dbg(u3d->dev, "linkchange: 0x%x\n", linkchange);

	अगर (linkchange & MV_U3D_LINK_CHANGE_LINK_UP) अणु
		dev_dbg(u3d->dev, "link up: ltssm state: 0x%x\n",
			ioपढ़ो32(&u3d->vuc_regs->ltssmstate));

		u3d->usb_state = USB_STATE_DEFAULT;
		u3d->ep0_dir = MV_U3D_EP_सूची_OUT;
		u3d->ep0_state = MV_U3D_WAIT_FOR_SETUP;

		/* set speed */
		u3d->gadget.speed = USB_SPEED_SUPER;
	पूर्ण

	अगर (linkchange & MV_U3D_LINK_CHANGE_SUSPEND) अणु
		dev_dbg(u3d->dev, "link suspend\n");
		u3d->resume_state = u3d->usb_state;
		u3d->usb_state = USB_STATE_SUSPENDED;
	पूर्ण

	अगर (linkchange & MV_U3D_LINK_CHANGE_RESUME) अणु
		dev_dbg(u3d->dev, "link resume\n");
		u3d->usb_state = u3d->resume_state;
		u3d->resume_state = 0;
	पूर्ण

	अगर (linkchange & MV_U3D_LINK_CHANGE_WRESET) अणु
		dev_dbg(u3d->dev, "warm reset\n");
		u3d->usb_state = USB_STATE_POWERED;
	पूर्ण

	अगर (linkchange & MV_U3D_LINK_CHANGE_HRESET) अणु
		dev_dbg(u3d->dev, "hot reset\n");
		u3d->usb_state = USB_STATE_DEFAULT;
	पूर्ण

	अगर (linkchange & MV_U3D_LINK_CHANGE_INACT)
		dev_dbg(u3d->dev, "inactive\n");

	अगर (linkchange & MV_U3D_LINK_CHANGE_DISABLE_AFTER_U0)
		dev_dbg(u3d->dev, "ss.disabled\n");

	अगर (linkchange & MV_U3D_LINK_CHANGE_VBUS_INVALID) अणु
		dev_dbg(u3d->dev, "vbus invalid\n");
		u3d->usb_state = USB_STATE_ATTACHED;
		u3d->vbus_valid_detect = 1;
		/* अगर बाह्यal vbus detect is not supported,
		 * we handle it here.
		 */
		अगर (!u3d->vbus) अणु
			spin_unlock(&u3d->lock);
			mv_u3d_vbus_session(&u3d->gadget, 0);
			spin_lock(&u3d->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mv_u3d_ch9setaddress(काष्ठा mv_u3d *u3d,
				काष्ठा usb_ctrlrequest *setup)
अणु
	u32 पंचांगp;

	अगर (u3d->usb_state != USB_STATE_DEFAULT) अणु
		dev_err(u3d->dev,
			"%s, cannot setaddr in this state (%d)\n",
			__func__, u3d->usb_state);
		जाओ err;
	पूर्ण

	u3d->dev_addr = (u8)setup->wValue;

	dev_dbg(u3d->dev, "%s: 0x%x\n", __func__, u3d->dev_addr);

	अगर (u3d->dev_addr > 127) अणु
		dev_err(u3d->dev,
			"%s, u3d address is wrong (out of range)\n", __func__);
		u3d->dev_addr = 0;
		जाओ err;
	पूर्ण

	/* update usb state */
	u3d->usb_state = USB_STATE_ADDRESS;

	/* set the new address */
	पंचांगp = ioपढ़ो32(&u3d->vuc_regs->devaddrtiebrkr);
	पंचांगp &= ~0x7F;
	पंचांगp |= (u32)u3d->dev_addr;
	ioग_लिखो32(पंचांगp, &u3d->vuc_regs->devaddrtiebrkr);

	वापस;
err:
	mv_u3d_ep0_stall(u3d);
पूर्ण

अटल पूर्णांक mv_u3d_is_set_configuration(काष्ठा usb_ctrlrequest *setup)
अणु
	अगर ((setup->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		अगर (setup->bRequest == USB_REQ_SET_CONFIGURATION)
			वापस 1;

	वापस 0;
पूर्ण

अटल व्योम mv_u3d_handle_setup_packet(काष्ठा mv_u3d *u3d, u8 ep_num,
	काष्ठा usb_ctrlrequest *setup)
	__releases(&u3c->lock)
	__acquires(&u3c->lock)
अणु
	bool delegate = false;

	mv_u3d_nuke(&u3d->eps[ep_num * 2 + MV_U3D_EP_सूची_IN], -ESHUTDOWN);

	dev_dbg(u3d->dev, "SETUP %02x.%02x v%04x i%04x l%04x\n",
			setup->bRequestType, setup->bRequest,
			setup->wValue, setup->wIndex, setup->wLength);

	/* We process some stardard setup requests here */
	अगर ((setup->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (setup->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			delegate = true;
			अवरोध;

		हाल USB_REQ_SET_ADDRESS:
			mv_u3d_ch9setaddress(u3d, setup);
			अवरोध;

		हाल USB_REQ_CLEAR_FEATURE:
			delegate = true;
			अवरोध;

		हाल USB_REQ_SET_FEATURE:
			delegate = true;
			अवरोध;

		शेष:
			delegate = true;
		पूर्ण
	पूर्ण अन्यथा
		delegate = true;

	/* delegate USB standard requests to the gadget driver */
	अगर (delegate) अणु
		/* USB requests handled by gadget */
		अगर (setup->wLength) अणु
			/* DATA phase from gadget, STATUS phase from u3d */
			u3d->ep0_dir = (setup->bRequestType & USB_सूची_IN)
					? MV_U3D_EP_सूची_IN : MV_U3D_EP_सूची_OUT;
			spin_unlock(&u3d->lock);
			अगर (u3d->driver->setup(&u3d->gadget,
				&u3d->local_setup_buff) < 0) अणु
				dev_err(u3d->dev, "setup error!\n");
				mv_u3d_ep0_stall(u3d);
			पूर्ण
			spin_lock(&u3d->lock);
		पूर्ण अन्यथा अणु
			/* no DATA phase, STATUS phase from gadget */
			u3d->ep0_dir = MV_U3D_EP_सूची_IN;
			u3d->ep0_state = MV_U3D_STATUS_STAGE;
			spin_unlock(&u3d->lock);
			अगर (u3d->driver->setup(&u3d->gadget,
				&u3d->local_setup_buff) < 0)
				mv_u3d_ep0_stall(u3d);
			spin_lock(&u3d->lock);
		पूर्ण

		अगर (mv_u3d_is_set_configuration(setup)) अणु
			dev_dbg(u3d->dev, "u3d configured\n");
			u3d->usb_state = USB_STATE_CONFIGURED;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mv_u3d_get_setup_data(काष्ठा mv_u3d *u3d, u8 ep_num, u8 *buffer_ptr)
अणु
	काष्ठा mv_u3d_ep_context *epcontext;

	epcontext = &u3d->ep_context[ep_num * 2 + MV_U3D_EP_सूची_IN];

	/* Copy the setup packet to local buffer */
	स_नकल(buffer_ptr, (u8 *) &epcontext->setup_buffer, 8);
पूर्ण

अटल व्योम mv_u3d_irq_process_setup(काष्ठा mv_u3d *u3d)
अणु
	u32 पंचांगp, i;
	/* Process all Setup packet received पूर्णांकerrupts */
	पंचांगp = ioपढ़ो32(&u3d->vuc_regs->setuplock);
	अगर (पंचांगp) अणु
		क्रम (i = 0; i < u3d->max_eps; i++) अणु
			अगर (पंचांगp & (1 << i)) अणु
				mv_u3d_get_setup_data(u3d, i,
					(u8 *)(&u3d->local_setup_buff));
				mv_u3d_handle_setup_packet(u3d, i,
					&u3d->local_setup_buff);
			पूर्ण
		पूर्ण
	पूर्ण

	ioग_लिखो32(पंचांगp, &u3d->vuc_regs->setuplock);
पूर्ण

अटल व्योम mv_u3d_irq_process_tr_complete(काष्ठा mv_u3d *u3d)
अणु
	u32 पंचांगp, bit_pos;
	पूर्णांक i, ep_num = 0, direction = 0;
	काष्ठा mv_u3d_ep	*curr_ep;
	काष्ठा mv_u3d_req *curr_req, *temp_req;
	पूर्णांक status;

	पंचांगp = ioपढ़ो32(&u3d->vuc_regs->endcomplete);

	dev_dbg(u3d->dev, "tr_complete: ep: 0x%x\n", पंचांगp);
	अगर (!पंचांगp)
		वापस;
	ioग_लिखो32(पंचांगp, &u3d->vuc_regs->endcomplete);

	क्रम (i = 0; i < u3d->max_eps * 2; i++) अणु
		ep_num = i >> 1;
		direction = i % 2;

		bit_pos = 1 << (ep_num + 16 * direction);

		अगर (!(bit_pos & पंचांगp))
			जारी;

		अगर (i == 0)
			curr_ep = &u3d->eps[1];
		अन्यथा
			curr_ep = &u3d->eps[i];

		/* हटाओ req out of ep request list after completion */
		dev_dbg(u3d->dev, "tr comp: check req_list\n");
		spin_lock(&curr_ep->req_lock);
		अगर (!list_empty(&curr_ep->req_list)) अणु
			काष्ठा mv_u3d_req *req;
			req = list_entry(curr_ep->req_list.next,
						काष्ठा mv_u3d_req, list);
			list_del_init(&req->list);
			curr_ep->processing = 0;
		पूर्ण
		spin_unlock(&curr_ep->req_lock);

		/* process the req queue until an uncomplete request */
		list_क्रम_each_entry_safe(curr_req, temp_req,
			&curr_ep->queue, queue) अणु
			status = mv_u3d_process_ep_req(u3d, i, curr_req);
			अगर (status)
				अवरोध;
			/* ग_लिखो back status to req */
			curr_req->req.status = status;

			/* ep0 request completion */
			अगर (ep_num == 0) अणु
				mv_u3d_करोne(curr_ep, curr_req, 0);
				अवरोध;
			पूर्ण अन्यथा अणु
				mv_u3d_करोne(curr_ep, curr_req, status);
			पूर्ण
		पूर्ण

		dev_dbg(u3d->dev, "call mv_u3d_start_queue from ep complete\n");
		mv_u3d_start_queue(curr_ep);
	पूर्ण
पूर्ण

अटल irqवापस_t mv_u3d_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mv_u3d *u3d = (काष्ठा mv_u3d *)dev;
	u32 status, पूर्णांकr;
	u32 bridgesetting;
	u32 trbunderrun;

	spin_lock(&u3d->lock);

	status = ioपढ़ो32(&u3d->vuc_regs->पूर्णांकrcause);
	पूर्णांकr = ioपढ़ो32(&u3d->vuc_regs->पूर्णांकrenable);
	status &= पूर्णांकr;

	अगर (status == 0) अणु
		spin_unlock(&u3d->lock);
		dev_err(u3d->dev, "irq error!\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & MV_U3D_USBINT_VBUS_VALID) अणु
		bridgesetting = ioपढ़ो32(&u3d->vuc_regs->bridgesetting);
		अगर (bridgesetting & MV_U3D_BRIDGE_SETTING_VBUS_VALID) अणु
			/* ग_लिखो vbus valid bit of bridge setting to clear */
			bridgesetting = MV_U3D_BRIDGE_SETTING_VBUS_VALID;
			ioग_लिखो32(bridgesetting, &u3d->vuc_regs->bridgesetting);
			dev_dbg(u3d->dev, "vbus valid\n");

			u3d->usb_state = USB_STATE_POWERED;
			u3d->vbus_valid_detect = 0;
			/* अगर बाह्यal vbus detect is not supported,
			 * we handle it here.
			 */
			अगर (!u3d->vbus) अणु
				spin_unlock(&u3d->lock);
				mv_u3d_vbus_session(&u3d->gadget, 1);
				spin_lock(&u3d->lock);
			पूर्ण
		पूर्ण अन्यथा
			dev_err(u3d->dev, "vbus bit is not set\n");
	पूर्ण

	/* RX data is alपढ़ोy in the 16KB FIFO.*/
	अगर (status & MV_U3D_USBINT_UNDER_RUN) अणु
		trbunderrun = ioपढ़ो32(&u3d->vuc_regs->trbunderrun);
		dev_err(u3d->dev, "under run, ep%d\n", trbunderrun);
		ioग_लिखो32(trbunderrun, &u3d->vuc_regs->trbunderrun);
		mv_u3d_irq_process_error(u3d);
	पूर्ण

	अगर (status & (MV_U3D_USBINT_RXDESC_ERR | MV_U3D_USBINT_TXDESC_ERR)) अणु
		/* ग_लिखो one to clear */
		ioग_लिखो32(status & (MV_U3D_USBINT_RXDESC_ERR
			| MV_U3D_USBINT_TXDESC_ERR),
			&u3d->vuc_regs->पूर्णांकrcause);
		dev_err(u3d->dev, "desc err 0x%x\n", status);
		mv_u3d_irq_process_error(u3d);
	पूर्ण

	अगर (status & MV_U3D_USBINT_LINK_CHG)
		mv_u3d_irq_process_link_change(u3d);

	अगर (status & MV_U3D_USBINT_TX_COMPLETE)
		mv_u3d_irq_process_tr_complete(u3d);

	अगर (status & MV_U3D_USBINT_RX_COMPLETE)
		mv_u3d_irq_process_tr_complete(u3d);

	अगर (status & MV_U3D_USBINT_SETUP)
		mv_u3d_irq_process_setup(u3d);

	spin_unlock(&u3d->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mv_u3d_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mv_u3d *u3d = platक्रमm_get_drvdata(dev);

	BUG_ON(u3d == शून्य);

	usb_del_gadget_udc(&u3d->gadget);

	/* मुक्त memory allocated in probe */
	dma_pool_destroy(u3d->trb_pool);

	अगर (u3d->ep_context)
		dma_मुक्त_coherent(&dev->dev, u3d->ep_context_size,
			u3d->ep_context, u3d->ep_context_dma);

	kमुक्त(u3d->eps);

	अगर (u3d->irq)
		मुक्त_irq(u3d->irq, u3d);

	अगर (u3d->cap_regs)
		iounmap(u3d->cap_regs);
	u3d->cap_regs = शून्य;

	kमुक्त(u3d->status_req);

	clk_put(u3d->clk);

	kमुक्त(u3d);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_u3d_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mv_u3d *u3d = शून्य;
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);
	पूर्णांक retval = 0;
	काष्ठा resource *r;
	माप_प्रकार size;

	अगर (!dev_get_platdata(&dev->dev)) अणु
		dev_err(&dev->dev, "missing platform_data\n");
		retval = -ENODEV;
		जाओ err_pdata;
	पूर्ण

	u3d = kzalloc(माप(*u3d), GFP_KERNEL);
	अगर (!u3d) अणु
		retval = -ENOMEM;
		जाओ err_alloc_निजी;
	पूर्ण

	spin_lock_init(&u3d->lock);

	platक्रमm_set_drvdata(dev, u3d);

	u3d->dev = &dev->dev;
	u3d->vbus = pdata->vbus;

	u3d->clk = clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(u3d->clk)) अणु
		retval = PTR_ERR(u3d->clk);
		जाओ err_get_clk;
	पूर्ण

	r = platक्रमm_get_resource_byname(dev, IORESOURCE_MEM, "capregs");
	अगर (!r) अणु
		dev_err(&dev->dev, "no I/O memory resource defined\n");
		retval = -ENODEV;
		जाओ err_get_cap_regs;
	पूर्ण

	u3d->cap_regs = (काष्ठा mv_u3d_cap_regs __iomem *)
		ioremap(r->start, resource_size(r));
	अगर (!u3d->cap_regs) अणु
		dev_err(&dev->dev, "failed to map I/O memory\n");
		retval = -EBUSY;
		जाओ err_map_cap_regs;
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->dev, "cap_regs address: 0x%lx/0x%lx\n",
			(अचिन्हित दीर्घ) r->start,
			(अचिन्हित दीर्घ) u3d->cap_regs);
	पूर्ण

	/* we will access controller रेजिस्टर, so enable the u3d controller */
	retval = clk_enable(u3d->clk);
	अगर (retval) अणु
		dev_err(&dev->dev, "clk_enable error %d\n", retval);
		जाओ err_u3d_enable;
	पूर्ण

	अगर (pdata->phy_init) अणु
		retval = pdata->phy_init(u3d->phy_regs);
		अगर (retval) अणु
			dev_err(&dev->dev, "init phy error %d\n", retval);
			clk_disable(u3d->clk);
			जाओ err_phy_init;
		पूर्ण
	पूर्ण

	u3d->op_regs = (काष्ठा mv_u3d_op_regs __iomem *)(u3d->cap_regs
		+ MV_U3D_USB3_OP_REGS_OFFSET);

	u3d->vuc_regs = (काष्ठा mv_u3d_vuc_regs __iomem *)(u3d->cap_regs
		+ ioपढ़ो32(&u3d->cap_regs->vuoff));

	u3d->max_eps = 16;

	/*
	 * some platक्रमm will use usb to करोwnload image, it may not disconnect
	 * usb gadget beक्रमe loading kernel. So first stop u3d here.
	 */
	mv_u3d_controller_stop(u3d);
	ioग_लिखो32(0xFFFFFFFF, &u3d->vuc_regs->पूर्णांकrcause);

	अगर (pdata->phy_deinit)
		pdata->phy_deinit(u3d->phy_regs);
	clk_disable(u3d->clk);

	size = u3d->max_eps * माप(काष्ठा mv_u3d_ep_context) * 2;
	size = (size + MV_U3D_EP_CONTEXT_ALIGNMENT - 1)
		& ~(MV_U3D_EP_CONTEXT_ALIGNMENT - 1);
	u3d->ep_context = dma_alloc_coherent(&dev->dev, size,
					&u3d->ep_context_dma, GFP_KERNEL);
	अगर (!u3d->ep_context) अणु
		dev_err(&dev->dev, "allocate ep context memory failed\n");
		retval = -ENOMEM;
		जाओ err_alloc_ep_context;
	पूर्ण
	u3d->ep_context_size = size;

	/* create TRB dma_pool resource */
	u3d->trb_pool = dma_pool_create("u3d_trb",
			&dev->dev,
			माप(काष्ठा mv_u3d_trb_hw),
			MV_U3D_TRB_ALIGNMENT,
			MV_U3D_DMA_BOUNDARY);

	अगर (!u3d->trb_pool) अणु
		retval = -ENOMEM;
		जाओ err_alloc_trb_pool;
	पूर्ण

	size = u3d->max_eps * माप(काष्ठा mv_u3d_ep) * 2;
	u3d->eps = kzalloc(size, GFP_KERNEL);
	अगर (!u3d->eps) अणु
		retval = -ENOMEM;
		जाओ err_alloc_eps;
	पूर्ण

	/* initialize ep0 status request काष्ठाure */
	u3d->status_req = kzalloc(माप(काष्ठा mv_u3d_req) + 8, GFP_KERNEL);
	अगर (!u3d->status_req) अणु
		retval = -ENOMEM;
		जाओ err_alloc_status_req;
	पूर्ण
	INIT_LIST_HEAD(&u3d->status_req->queue);

	/* allocate a small amount of memory to get valid address */
	u3d->status_req->req.buf = (अक्षर *)u3d->status_req
					+ माप(काष्ठा mv_u3d_req);
	u3d->status_req->req.dma = virt_to_phys(u3d->status_req->req.buf);

	u3d->resume_state = USB_STATE_NOTATTACHED;
	u3d->usb_state = USB_STATE_ATTACHED;
	u3d->ep0_dir = MV_U3D_EP_सूची_OUT;
	u3d->remote_wakeup = 0;

	r = platक्रमm_get_resource(dev, IORESOURCE_IRQ, 0);
	अगर (!r) अणु
		dev_err(&dev->dev, "no IRQ resource defined\n");
		retval = -ENODEV;
		जाओ err_get_irq;
	पूर्ण
	u3d->irq = r->start;
	अगर (request_irq(u3d->irq, mv_u3d_irq,
		IRQF_SHARED, driver_name, u3d)) अणु
		u3d->irq = 0;
		dev_err(&dev->dev, "Request irq %d for u3d failed\n",
			u3d->irq);
		retval = -ENODEV;
		जाओ err_request_irq;
	पूर्ण

	/* initialize gadget काष्ठाure */
	u3d->gadget.ops = &mv_u3d_ops;	/* usb_gadget_ops */
	u3d->gadget.ep0 = &u3d->eps[1].ep;	/* gadget ep0 */
	INIT_LIST_HEAD(&u3d->gadget.ep_list);	/* ep_list */
	u3d->gadget.speed = USB_SPEED_UNKNOWN;	/* speed */

	/* the "gadget" असलtracts/भवizes the controller */
	u3d->gadget.name = driver_name;		/* gadget name */

	mv_u3d_eps_init(u3d);

	/* बाह्यal vbus detection */
	अगर (u3d->vbus) अणु
		u3d->घड़ी_gating = 1;
		dev_err(&dev->dev, "external vbus detection\n");
	पूर्ण

	अगर (!u3d->घड़ी_gating)
		u3d->vbus_active = 1;

	/* enable usb3 controller vbus detection */
	u3d->vbus_valid_detect = 1;

	retval = usb_add_gadget_udc(&dev->dev, &u3d->gadget);
	अगर (retval)
		जाओ err_unरेजिस्टर;

	dev_dbg(&dev->dev, "successful probe usb3 device %s clock gating.\n",
		u3d->घड़ी_gating ? "with" : "without");

	वापस 0;

err_unरेजिस्टर:
	मुक्त_irq(u3d->irq, u3d);
err_request_irq:
err_get_irq:
	kमुक्त(u3d->status_req);
err_alloc_status_req:
	kमुक्त(u3d->eps);
err_alloc_eps:
	dma_pool_destroy(u3d->trb_pool);
err_alloc_trb_pool:
	dma_मुक्त_coherent(&dev->dev, u3d->ep_context_size,
		u3d->ep_context, u3d->ep_context_dma);
err_alloc_ep_context:
err_phy_init:
err_u3d_enable:
	iounmap(u3d->cap_regs);
err_map_cap_regs:
err_get_cap_regs:
	clk_put(u3d->clk);
err_get_clk:
	kमुक्त(u3d);
err_alloc_निजी:
err_pdata:
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mv_u3d_suspend(काष्ठा device *dev)
अणु
	काष्ठा mv_u3d *u3d = dev_get_drvdata(dev);

	/*
	 * only cable is unplugged, usb can suspend.
	 * So करो not care about घड़ी_gating == 1, it is handled by
	 * vbus session.
	 */
	अगर (!u3d->घड़ी_gating) अणु
		mv_u3d_controller_stop(u3d);

		spin_lock_irq(&u3d->lock);
		/* stop all usb activities */
		mv_u3d_stop_activity(u3d, u3d->driver);
		spin_unlock_irq(&u3d->lock);

		mv_u3d_disable(u3d);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv_u3d_resume(काष्ठा device *dev)
अणु
	काष्ठा mv_u3d *u3d = dev_get_drvdata(dev);
	पूर्णांक retval;

	अगर (!u3d->घड़ी_gating) अणु
		retval = mv_u3d_enable(u3d);
		अगर (retval)
			वापस retval;

		अगर (u3d->driver && u3d->softconnect) अणु
			mv_u3d_controller_reset(u3d);
			mv_u3d_ep0_reset(u3d);
			mv_u3d_controller_start(u3d);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(mv_u3d_pm_ops, mv_u3d_suspend, mv_u3d_resume);

अटल व्योम mv_u3d_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mv_u3d *u3d = platक्रमm_get_drvdata(dev);
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32(&u3d->op_regs->usbcmd);
	पंचांगp &= ~MV_U3D_CMD_RUN_STOP;
	ioग_लिखो32(पंचांगp, &u3d->op_regs->usbcmd);
पूर्ण

अटल काष्ठा platक्रमm_driver mv_u3d_driver = अणु
	.probe		= mv_u3d_probe,
	.हटाओ		= mv_u3d_हटाओ,
	.shutकरोwn	= mv_u3d_shutकरोwn,
	.driver		= अणु
		.name	= "mv-u3d",
		.pm	= &mv_u3d_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mv_u3d_driver);
MODULE_ALIAS("platform:mv-u3d");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Yu Xu <yuxu@marvell.com>");
MODULE_LICENSE("GPL");
