<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 * Author: Chao Xie <chao.xie@marvell.com>
 *	   Neil Zhang <zhangwm@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "mv_udc.h"

#घोषणा DRIVER_DESC		"Marvell PXA USB Device Controller driver"

#घोषणा ep_dir(ep)	(((ep)->ep_num == 0) ? \
				((ep)->udc->ep0_dir) : ((ep)->direction))

/* समयout value -- usec */
#घोषणा RESET_TIMEOUT		10000
#घोषणा FLUSH_TIMEOUT		10000
#घोषणा EPSTATUS_TIMEOUT	10000
#घोषणा PRIME_TIMEOUT		10000
#घोषणा READSAFE_TIMEOUT	1000

#घोषणा LOOPS_USEC_SHIFT	1
#घोषणा LOOPS_USEC		(1 << LOOPS_USEC_SHIFT)
#घोषणा LOOPS(समयout)		((समयout) >> LOOPS_USEC_SHIFT)

अटल DECLARE_COMPLETION(release_करोne);

अटल स्थिर अक्षर driver_name[] = "mv_udc";

अटल व्योम nuke(काष्ठा mv_ep *ep, पूर्णांक status);
अटल व्योम stop_activity(काष्ठा mv_udc *udc, काष्ठा usb_gadget_driver *driver);

/* क्रम endpoपूर्णांक 0 operations */
अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor mv_ep0_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	0,
	.bmAttributes =		USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize =	EP0_MAX_PKT_SIZE,
पूर्ण;

अटल व्योम ep0_reset(काष्ठा mv_udc *udc)
अणु
	काष्ठा mv_ep *ep;
	u32 epctrlx;
	पूर्णांक i = 0;

	/* ep0 in and out */
	क्रम (i = 0; i < 2; i++) अणु
		ep = &udc->eps[i];
		ep->udc = udc;

		/* ep0 dQH */
		ep->dqh = &udc->ep_dqh[i];

		/* configure ep0 endpoपूर्णांक capabilities in dQH */
		ep->dqh->max_packet_length =
			(EP0_MAX_PKT_SIZE << EP_QUEUE_HEAD_MAX_PKT_LEN_POS)
			| EP_QUEUE_HEAD_IOS;

		ep->dqh->next_dtd_ptr = EP_QUEUE_HEAD_NEXT_TERMINATE;

		epctrlx = पढ़ोl(&udc->op_regs->epctrlx[0]);
		अगर (i) अणु	/* TX */
			epctrlx |= EPCTRL_TX_ENABLE
				| (USB_ENDPOINT_XFER_CONTROL
					<< EPCTRL_TX_EP_TYPE_SHIFT);

		पूर्ण अन्यथा अणु	/* RX */
			epctrlx |= EPCTRL_RX_ENABLE
				| (USB_ENDPOINT_XFER_CONTROL
					<< EPCTRL_RX_EP_TYPE_SHIFT);
		पूर्ण

		ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[0]);
	पूर्ण
पूर्ण

/* protocol ep0 stall, will स्वतःmatically be cleared on new transaction */
अटल व्योम ep0_stall(काष्ठा mv_udc *udc)
अणु
	u32	epctrlx;

	/* set TX and RX to stall */
	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[0]);
	epctrlx |= EPCTRL_RX_EP_STALL | EPCTRL_TX_EP_STALL;
	ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[0]);

	/* update ep0 state */
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = EP_सूची_OUT;
पूर्ण

अटल पूर्णांक process_ep_req(काष्ठा mv_udc *udc, पूर्णांक index,
	काष्ठा mv_req *curr_req)
अणु
	काष्ठा mv_dtd	*curr_dtd;
	काष्ठा mv_dqh	*curr_dqh;
	पूर्णांक actual, reमुख्यing_length;
	पूर्णांक i, direction;
	पूर्णांक retval = 0;
	u32 errors;
	u32 bit_pos;

	curr_dqh = &udc->ep_dqh[index];
	direction = index % 2;

	curr_dtd = curr_req->head;
	actual = curr_req->req.length;

	क्रम (i = 0; i < curr_req->dtd_count; i++) अणु
		अगर (curr_dtd->size_ioc_sts & DTD_STATUS_ACTIVE) अणु
			dev_dbg(&udc->dev->dev, "%s, dTD not completed\n",
				udc->eps[index].name);
			वापस 1;
		पूर्ण

		errors = curr_dtd->size_ioc_sts & DTD_ERROR_MASK;
		अगर (!errors) अणु
			reमुख्यing_length =
				(curr_dtd->size_ioc_sts	& DTD_PACKET_SIZE)
					>> DTD_LENGTH_BIT_POS;
			actual -= reमुख्यing_length;

			अगर (reमुख्यing_length) अणु
				अगर (direction) अणु
					dev_dbg(&udc->dev->dev,
						"TX dTD remains data\n");
					retval = -EPROTO;
					अवरोध;
				पूर्ण अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_info(&udc->dev->dev,
				"complete_tr error: ep=%d %s: error = 0x%x\n",
				index >> 1, direction ? "SEND" : "RECV",
				errors);
			अगर (errors & DTD_STATUS_HALTED) अणु
				/* Clear the errors and Halt condition */
				curr_dqh->size_ioc_पूर्णांक_sts &= ~errors;
				retval = -EPIPE;
			पूर्ण अन्यथा अगर (errors & DTD_STATUS_DATA_BUFF_ERR) अणु
				retval = -EPROTO;
			पूर्ण अन्यथा अगर (errors & DTD_STATUS_TRANSACTION_ERR) अणु
				retval = -EILSEQ;
			पूर्ण
		पूर्ण
		अगर (i != curr_req->dtd_count - 1)
			curr_dtd = (काष्ठा mv_dtd *)curr_dtd->next_dtd_virt;
	पूर्ण
	अगर (retval)
		वापस retval;

	अगर (direction == EP_सूची_OUT)
		bit_pos = 1 << curr_req->ep->ep_num;
	अन्यथा
		bit_pos = 1 << (16 + curr_req->ep->ep_num);

	जबतक (curr_dqh->curr_dtd_ptr == curr_dtd->td_dma) अणु
		अगर (curr_dtd->dtd_next == EP_QUEUE_HEAD_NEXT_TERMINATE) अणु
			जबतक (पढ़ोl(&udc->op_regs->epstatus) & bit_pos)
				udelay(1);
			अवरोध;
		पूर्ण
		udelay(1);
	पूर्ण

	curr_req->req.actual = actual;

	वापस 0;
पूर्ण

/*
 * करोne() - retire a request; caller blocked irqs
 * @status : request status to be set, only works when
 * request is still in progress.
 */
अटल व्योम करोne(काष्ठा mv_ep *ep, काष्ठा mv_req *req, पूर्णांक status)
	__releases(&ep->udc->lock)
	__acquires(&ep->udc->lock)
अणु
	काष्ठा mv_udc *udc = शून्य;
	अचिन्हित अक्षर stopped = ep->stopped;
	काष्ठा mv_dtd *curr_td, *next_td;
	पूर्णांक j;

	udc = (काष्ठा mv_udc *)ep->udc;
	/* Removed the req from fsl_ep->queue */
	list_del_init(&req->queue);

	/* req.status should be set as -EINPROGRESS in ep_queue() */
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	/* Free dtd क्रम the request */
	next_td = req->head;
	क्रम (j = 0; j < req->dtd_count; j++) अणु
		curr_td = next_td;
		अगर (j != req->dtd_count - 1)
			next_td = curr_td->next_dtd_virt;
		dma_pool_मुक्त(udc->dtd_pool, curr_td, curr_td->td_dma);
	पूर्ण

	usb_gadget_unmap_request(&udc->gadget, &req->req, ep_dir(ep));

	अगर (status && (status != -ESHUTDOWN))
		dev_info(&udc->dev->dev, "complete %s req %p stat %d len %u/%u",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	ep->stopped = 1;

	spin_unlock(&ep->udc->lock);

	usb_gadget_giveback_request(&ep->ep, &req->req);

	spin_lock(&ep->udc->lock);
	ep->stopped = stopped;
पूर्ण

अटल पूर्णांक queue_dtd(काष्ठा mv_ep *ep, काष्ठा mv_req *req)
अणु
	काष्ठा mv_udc *udc;
	काष्ठा mv_dqh *dqh;
	u32 bit_pos, direction;
	u32 usbcmd, epstatus;
	अचिन्हित पूर्णांक loops;
	पूर्णांक retval = 0;

	udc = ep->udc;
	direction = ep_dir(ep);
	dqh = &(udc->ep_dqh[ep->ep_num * 2 + direction]);
	bit_pos = 1 << (((direction == EP_सूची_OUT) ? 0 : 16) + ep->ep_num);

	/* check अगर the pipe is empty */
	अगर (!(list_empty(&ep->queue))) अणु
		काष्ठा mv_req *lastreq;
		lastreq = list_entry(ep->queue.prev, काष्ठा mv_req, queue);
		lastreq->tail->dtd_next =
			req->head->td_dma & EP_QUEUE_HEAD_NEXT_POINTER_MASK;

		wmb();

		अगर (पढ़ोl(&udc->op_regs->epprime) & bit_pos)
			जाओ करोne;

		loops = LOOPS(READSAFE_TIMEOUT);
		जबतक (1) अणु
			/* start with setting the semaphores */
			usbcmd = पढ़ोl(&udc->op_regs->usbcmd);
			usbcmd |= USBCMD_ATDTW_TRIPWIRE_SET;
			ग_लिखोl(usbcmd, &udc->op_regs->usbcmd);

			/* पढ़ो the endpoपूर्णांक status */
			epstatus = पढ़ोl(&udc->op_regs->epstatus) & bit_pos;

			/*
			 * Reपढ़ो the ATDTW semaphore bit to check अगर it is
			 * cleared. When hardware see a hazard, it will clear
			 * the bit or अन्यथा we reमुख्य set to 1 and we can
			 * proceed with priming of endpoपूर्णांक अगर not alपढ़ोy
			 * primed.
			 */
			अगर (पढ़ोl(&udc->op_regs->usbcmd)
				& USBCMD_ATDTW_TRIPWIRE_SET)
				अवरोध;

			loops--;
			अगर (loops == 0) अणु
				dev_err(&udc->dev->dev,
					"Timeout for ATDTW_TRIPWIRE...\n");
				retval = -ETIME;
				जाओ करोne;
			पूर्ण
			udelay(LOOPS_USEC);
		पूर्ण

		/* Clear the semaphore */
		usbcmd = पढ़ोl(&udc->op_regs->usbcmd);
		usbcmd &= USBCMD_ATDTW_TRIPWIRE_CLEAR;
		ग_लिखोl(usbcmd, &udc->op_regs->usbcmd);

		अगर (epstatus)
			जाओ करोne;
	पूर्ण

	/* Write dQH next poपूर्णांकer and terminate bit to 0 */
	dqh->next_dtd_ptr = req->head->td_dma
				& EP_QUEUE_HEAD_NEXT_POINTER_MASK;

	/* clear active and halt bit, in हाल set from a previous error */
	dqh->size_ioc_पूर्णांक_sts &= ~(DTD_STATUS_ACTIVE | DTD_STATUS_HALTED);

	/* Ensure that updates to the QH will occur beक्रमe priming. */
	wmb();

	/* Prime the Endpoपूर्णांक */
	ग_लिखोl(bit_pos, &udc->op_regs->epprime);

करोne:
	वापस retval;
पूर्ण

अटल काष्ठा mv_dtd *build_dtd(काष्ठा mv_req *req, अचिन्हित *length,
		dma_addr_t *dma, पूर्णांक *is_last)
अणु
	काष्ठा mv_dtd *dtd;
	काष्ठा mv_udc *udc;
	काष्ठा mv_dqh *dqh;
	u32 temp, mult = 0;

	/* how big will this transfer be? */
	अगर (usb_endpoपूर्णांक_xfer_isoc(req->ep->ep.desc)) अणु
		dqh = req->ep->dqh;
		mult = (dqh->max_packet_length >> EP_QUEUE_HEAD_MULT_POS)
				& 0x3;
		*length = min(req->req.length - req->req.actual,
				(अचिन्हित)(mult * req->ep->ep.maxpacket));
	पूर्ण अन्यथा
		*length = min(req->req.length - req->req.actual,
				(अचिन्हित)EP_MAX_LENGTH_TRANSFER);

	udc = req->ep->udc;

	/*
	 * Be careful that no _GFP_HIGHMEM is set,
	 * or we can not use dma_to_virt
	 */
	dtd = dma_pool_alloc(udc->dtd_pool, GFP_ATOMIC, dma);
	अगर (dtd == शून्य)
		वापस dtd;

	dtd->td_dma = *dma;
	/* initialize buffer page poपूर्णांकers */
	temp = (u32)(req->req.dma + req->req.actual);
	dtd->buff_ptr0 = cpu_to_le32(temp);
	temp &= ~0xFFF;
	dtd->buff_ptr1 = cpu_to_le32(temp + 0x1000);
	dtd->buff_ptr2 = cpu_to_le32(temp + 0x2000);
	dtd->buff_ptr3 = cpu_to_le32(temp + 0x3000);
	dtd->buff_ptr4 = cpu_to_le32(temp + 0x4000);

	req->req.actual += *length;

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

	/* Fill in the transfer size; set active bit */
	temp = ((*length << DTD_LENGTH_BIT_POS) | DTD_STATUS_ACTIVE);

	/* Enable पूर्णांकerrupt क्रम the last dtd of a request */
	अगर (*is_last && !req->req.no_पूर्णांकerrupt)
		temp |= DTD_IOC;

	temp |= mult << 10;

	dtd->size_ioc_sts = temp;

	mb();

	वापस dtd;
पूर्ण

/* generate dTD linked list क्रम a request */
अटल पूर्णांक req_to_dtd(काष्ठा mv_req *req)
अणु
	अचिन्हित count;
	पूर्णांक is_last, is_first = 1;
	काष्ठा mv_dtd *dtd, *last_dtd = शून्य;
	dma_addr_t dma;

	करो अणु
		dtd = build_dtd(req, &count, &dma, &is_last);
		अगर (dtd == शून्य)
			वापस -ENOMEM;

		अगर (is_first) अणु
			is_first = 0;
			req->head = dtd;
		पूर्ण अन्यथा अणु
			last_dtd->dtd_next = dma;
			last_dtd->next_dtd_virt = dtd;
		पूर्ण
		last_dtd = dtd;
		req->dtd_count++;
	पूर्ण जबतक (!is_last);

	/* set terminate bit to 1 क्रम the last dTD */
	dtd->dtd_next = DTD_NEXT_TERMINATE;

	req->tail = dtd;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_ep_enable(काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा mv_udc *udc;
	काष्ठा mv_ep *ep;
	काष्ठा mv_dqh *dqh;
	u16 max = 0;
	u32 bit_pos, epctrlx, direction;
	स्थिर अचिन्हित अक्षर zlt = 1;
	अचिन्हित अक्षर ios, mult;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा mv_ep, ep);
	udc = ep->udc;

	अगर (!_ep || !desc
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	direction = ep_dir(ep);
	max = usb_endpoपूर्णांक_maxp(desc);

	/*
	 * disable HW zero length termination select
	 * driver handles zero length packet through req->req.zero
	 */
	bit_pos = 1 << ((direction == EP_सूची_OUT ? 0 : 16) + ep->ep_num);

	/* Check अगर the Endpoपूर्णांक is Primed */
	अगर ((पढ़ोl(&udc->op_regs->epprime) & bit_pos)
		|| (पढ़ोl(&udc->op_regs->epstatus) & bit_pos)) अणु
		dev_info(&udc->dev->dev,
			"ep=%d %s: Init ERROR: ENDPTPRIME=0x%x,"
			" ENDPTSTATUS=0x%x, bit_pos=0x%x\n",
			(अचिन्हित)ep->ep_num, direction ? "SEND" : "RECV",
			(अचिन्हित)पढ़ोl(&udc->op_regs->epprime),
			(अचिन्हित)पढ़ोl(&udc->op_regs->epstatus),
			(अचिन्हित)bit_pos);
		जाओ en_करोne;
	पूर्ण

	/* Set the max packet length, पूर्णांकerrupt on Setup and Mult fields */
	ios = 0;
	mult = 0;
	चयन (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) अणु
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		अवरोध;
	हाल USB_ENDPOINT_XFER_CONTROL:
		ios = 1;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		/* Calculate transactions needed क्रम high bandwidth iso */
		mult = usb_endpoपूर्णांक_maxp_mult(desc);
		/* 3 transactions at most */
		अगर (mult > 3)
			जाओ en_करोne;
		अवरोध;
	शेष:
		जाओ en_करोne;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);
	/* Get the endpoपूर्णांक queue head address */
	dqh = ep->dqh;
	dqh->max_packet_length = (max << EP_QUEUE_HEAD_MAX_PKT_LEN_POS)
		| (mult << EP_QUEUE_HEAD_MULT_POS)
		| (zlt ? EP_QUEUE_HEAD_ZLT_SEL : 0)
		| (ios ? EP_QUEUE_HEAD_IOS : 0);
	dqh->next_dtd_ptr = 1;
	dqh->size_ioc_पूर्णांक_sts = 0;

	ep->ep.maxpacket = max;
	ep->ep.desc = desc;
	ep->stopped = 0;

	/* Enable the endpoपूर्णांक क्रम Rx or Tx and set the endpoपूर्णांक type */
	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep->ep_num]);
	अगर (direction == EP_सूची_IN) अणु
		epctrlx &= ~EPCTRL_TX_ALL_MASK;
		epctrlx |= EPCTRL_TX_ENABLE | EPCTRL_TX_DATA_TOGGLE_RST
			| ((desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)
				<< EPCTRL_TX_EP_TYPE_SHIFT);
	पूर्ण अन्यथा अणु
		epctrlx &= ~EPCTRL_RX_ALL_MASK;
		epctrlx |= EPCTRL_RX_ENABLE | EPCTRL_RX_DATA_TOGGLE_RST
			| ((desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)
				<< EPCTRL_RX_EP_TYPE_SHIFT);
	पूर्ण
	ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep->ep_num]);

	/*
	 * Implement Guideline (GL# USB-7) The unused endpoपूर्णांक type must
	 * be programmed to bulk.
	 */
	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep->ep_num]);
	अगर ((epctrlx & EPCTRL_RX_ENABLE) == 0) अणु
		epctrlx |= (USB_ENDPOINT_XFER_BULK
				<< EPCTRL_RX_EP_TYPE_SHIFT);
		ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep->ep_num]);
	पूर्ण

	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep->ep_num]);
	अगर ((epctrlx & EPCTRL_TX_ENABLE) == 0) अणु
		epctrlx |= (USB_ENDPOINT_XFER_BULK
				<< EPCTRL_TX_EP_TYPE_SHIFT);
		ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep->ep_num]);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
en_करोne:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक  mv_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा mv_udc *udc;
	काष्ठा mv_ep *ep;
	काष्ठा mv_dqh *dqh;
	u32 epctrlx, direction;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा mv_ep, ep);
	अगर ((_ep == शून्य) || !ep->ep.desc)
		वापस -EINVAL;

	udc = ep->udc;

	/* Get the endpoपूर्णांक queue head address */
	dqh = ep->dqh;

	spin_lock_irqsave(&udc->lock, flags);

	direction = ep_dir(ep);

	/* Reset the max packet length and the पूर्णांकerrupt on Setup */
	dqh->max_packet_length = 0;

	/* Disable the endpoपूर्णांक क्रम Rx or Tx and reset the endpoपूर्णांक type */
	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep->ep_num]);
	epctrlx &= ~((direction == EP_सूची_IN)
			? (EPCTRL_TX_ENABLE | EPCTRL_TX_TYPE)
			: (EPCTRL_RX_ENABLE | EPCTRL_RX_TYPE));
	ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep->ep_num]);

	/* nuke all pending requests (करोes flush) */
	nuke(ep, -ESHUTDOWN);

	ep->ep.desc = शून्य;
	ep->stopped = 1;

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_request *
mv_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा mv_req *req = शून्य;

	req = kzalloc(माप *req, gfp_flags);
	अगर (!req)
		वापस शून्य;

	req->req.dma = DMA_ADDR_INVALID;
	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम mv_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा mv_req *req = शून्य;

	req = container_of(_req, काष्ठा mv_req, req);

	अगर (_req)
		kमुक्त(req);
पूर्ण

अटल व्योम mv_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा mv_udc *udc;
	u32 bit_pos, direction;
	काष्ठा mv_ep *ep;
	अचिन्हित पूर्णांक loops;

	अगर (!_ep)
		वापस;

	ep = container_of(_ep, काष्ठा mv_ep, ep);
	अगर (!ep->ep.desc)
		वापस;

	udc = ep->udc;
	direction = ep_dir(ep);

	अगर (ep->ep_num == 0)
		bit_pos = (1 << 16) | 1;
	अन्यथा अगर (direction == EP_सूची_OUT)
		bit_pos = 1 << ep->ep_num;
	अन्यथा
		bit_pos = 1 << (16 + ep->ep_num);

	loops = LOOPS(EPSTATUS_TIMEOUT);
	करो अणु
		अचिन्हित पूर्णांक पूर्णांकer_loops;

		अगर (loops == 0) अणु
			dev_err(&udc->dev->dev,
				"TIMEOUT for ENDPTSTATUS=0x%x, bit_pos=0x%x\n",
				(अचिन्हित)पढ़ोl(&udc->op_regs->epstatus),
				(अचिन्हित)bit_pos);
			वापस;
		पूर्ण
		/* Write 1 to the Flush रेजिस्टर */
		ग_लिखोl(bit_pos, &udc->op_regs->epflush);

		/* Wait until flushing completed */
		पूर्णांकer_loops = LOOPS(FLUSH_TIMEOUT);
		जबतक (पढ़ोl(&udc->op_regs->epflush)) अणु
			/*
			 * ENDPTFLUSH bit should be cleared to indicate this
			 * operation is complete
			 */
			अगर (पूर्णांकer_loops == 0) अणु
				dev_err(&udc->dev->dev,
					"TIMEOUT for ENDPTFLUSH=0x%x,"
					"bit_pos=0x%x\n",
					(अचिन्हित)पढ़ोl(&udc->op_regs->epflush),
					(अचिन्हित)bit_pos);
				वापस;
			पूर्ण
			पूर्णांकer_loops--;
			udelay(LOOPS_USEC);
		पूर्ण
		loops--;
	पूर्ण जबतक (पढ़ोl(&udc->op_regs->epstatus) & bit_pos);
पूर्ण

/* queues (submits) an I/O request to an endpoपूर्णांक */
अटल पूर्णांक
mv_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा mv_ep *ep = container_of(_ep, काष्ठा mv_ep, ep);
	काष्ठा mv_req *req = container_of(_req, काष्ठा mv_req, req);
	काष्ठा mv_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	/* catch various bogus parameters */
	अगर (!_req || !req->req.complete || !req->req.buf
			|| !list_empty(&req->queue)) अणु
		dev_err(&udc->dev->dev, "%s, bad params", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(!_ep || !ep->ep.desc)) अणु
		dev_err(&udc->dev->dev, "%s, bad ep", __func__);
		वापस -EINVAL;
	पूर्ण

	udc = ep->udc;
	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	req->ep = ep;

	/* map भव address to hardware */
	retval = usb_gadget_map_request(&udc->gadget, _req, ep_dir(ep));
	अगर (retval)
		वापस retval;

	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->dtd_count = 0;

	spin_lock_irqsave(&udc->lock, flags);

	/* build dtds and push them to device queue */
	अगर (!req_to_dtd(req)) अणु
		retval = queue_dtd(ep, req);
		अगर (retval) अणु
			spin_unlock_irqrestore(&udc->lock, flags);
			dev_err(&udc->dev->dev, "Failed to queue dtd\n");
			जाओ err_unmap_dma;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		dev_err(&udc->dev->dev, "Failed to dma_pool_alloc\n");
		retval = -ENOMEM;
		जाओ err_unmap_dma;
	पूर्ण

	/* Update ep0 state */
	अगर (ep->ep_num == 0)
		udc->ep0_state = DATA_STATE_XMIT;

	/* irq handler advances the queue */
	list_add_tail(&req->queue, &ep->queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;

err_unmap_dma:
	usb_gadget_unmap_request(&udc->gadget, _req, ep_dir(ep));

	वापस retval;
पूर्ण

अटल व्योम mv_prime_ep(काष्ठा mv_ep *ep, काष्ठा mv_req *req)
अणु
	काष्ठा mv_dqh *dqh = ep->dqh;
	u32 bit_pos;

	/* Write dQH next poपूर्णांकer and terminate bit to 0 */
	dqh->next_dtd_ptr = req->head->td_dma
		& EP_QUEUE_HEAD_NEXT_POINTER_MASK;

	/* clear active and halt bit, in हाल set from a previous error */
	dqh->size_ioc_पूर्णांक_sts &= ~(DTD_STATUS_ACTIVE | DTD_STATUS_HALTED);

	/* Ensure that updates to the QH will occure beक्रमe priming. */
	wmb();

	bit_pos = 1 << (((ep_dir(ep) == EP_सूची_OUT) ? 0 : 16) + ep->ep_num);

	/* Prime the Endpoपूर्णांक */
	ग_लिखोl(bit_pos, &ep->udc->op_regs->epprime);
पूर्ण

/* dequeues (cancels, unlinks) an I/O request from an endpoपूर्णांक */
अटल पूर्णांक mv_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा mv_ep *ep = container_of(_ep, काष्ठा mv_ep, ep);
	काष्ठा mv_req *req;
	काष्ठा mv_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक stopped, ret = 0;
	u32 epctrlx;

	अगर (!_ep || !_req)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->udc->lock, flags);
	stopped = ep->stopped;

	/* Stop the ep beक्रमe we deal with the queue */
	ep->stopped = 1;
	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep->ep_num]);
	अगर (ep_dir(ep) == EP_सूची_IN)
		epctrlx &= ~EPCTRL_TX_ENABLE;
	अन्यथा
		epctrlx &= ~EPCTRL_RX_ENABLE;
	ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep->ep_num]);

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
		mv_ep_fअगरo_flush(_ep);	/* flush current transfer */

		/* The request isn't the last request in this ep queue */
		अगर (req->queue.next != &ep->queue) अणु
			काष्ठा mv_req *next_req;

			next_req = list_entry(req->queue.next,
				काष्ठा mv_req, queue);

			/* Poपूर्णांक the QH to the first TD of next request */
			mv_prime_ep(ep, next_req);
		पूर्ण अन्यथा अणु
			काष्ठा mv_dqh *qh;

			qh = ep->dqh;
			qh->next_dtd_ptr = 1;
			qh->size_ioc_पूर्णांक_sts = 0;
		पूर्ण

		/* The request hasn't been processed, patch up the TD chain */
	पूर्ण अन्यथा अणु
		काष्ठा mv_req *prev_req;

		prev_req = list_entry(req->queue.prev, काष्ठा mv_req, queue);
		ग_लिखोl(पढ़ोl(&req->tail->dtd_next),
				&prev_req->tail->dtd_next);

	पूर्ण

	करोne(ep, req, -ECONNRESET);

	/* Enable EP */
out:
	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep->ep_num]);
	अगर (ep_dir(ep) == EP_सूची_IN)
		epctrlx |= EPCTRL_TX_ENABLE;
	अन्यथा
		epctrlx |= EPCTRL_RX_ENABLE;
	ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep->ep_num]);
	ep->stopped = stopped;

	spin_unlock_irqrestore(&ep->udc->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम ep_set_stall(काष्ठा mv_udc *udc, u8 ep_num, u8 direction, पूर्णांक stall)
अणु
	u32 epctrlx;

	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep_num]);

	अगर (stall) अणु
		अगर (direction == EP_सूची_IN)
			epctrlx |= EPCTRL_TX_EP_STALL;
		अन्यथा
			epctrlx |= EPCTRL_RX_EP_STALL;
	पूर्ण अन्यथा अणु
		अगर (direction == EP_सूची_IN) अणु
			epctrlx &= ~EPCTRL_TX_EP_STALL;
			epctrlx |= EPCTRL_TX_DATA_TOGGLE_RST;
		पूर्ण अन्यथा अणु
			epctrlx &= ~EPCTRL_RX_EP_STALL;
			epctrlx |= EPCTRL_RX_DATA_TOGGLE_RST;
		पूर्ण
	पूर्ण
	ग_लिखोl(epctrlx, &udc->op_regs->epctrlx[ep_num]);
पूर्ण

अटल पूर्णांक ep_is_stall(काष्ठा mv_udc *udc, u8 ep_num, u8 direction)
अणु
	u32 epctrlx;

	epctrlx = पढ़ोl(&udc->op_regs->epctrlx[ep_num]);

	अगर (direction == EP_सूची_OUT)
		वापस (epctrlx & EPCTRL_RX_EP_STALL) ? 1 : 0;
	अन्यथा
		वापस (epctrlx & EPCTRL_TX_EP_STALL) ? 1 : 0;
पूर्ण

अटल पूर्णांक mv_ep_set_halt_wedge(काष्ठा usb_ep *_ep, पूर्णांक halt, पूर्णांक wedge)
अणु
	काष्ठा mv_ep *ep;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक status = 0;
	काष्ठा mv_udc *udc;

	ep = container_of(_ep, काष्ठा mv_ep, ep);
	udc = ep->udc;
	अगर (!_ep || !ep->ep.desc) अणु
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
	अगर (halt && (ep_dir(ep) == EP_सूची_IN) && !list_empty(&ep->queue)) अणु
		status = -EAGAIN;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&ep->udc->lock, flags);
	ep_set_stall(udc, ep->ep_num, ep_dir(ep), halt);
	अगर (halt && wedge)
		ep->wedge = 1;
	अन्यथा अगर (!halt)
		ep->wedge = 0;
	spin_unlock_irqrestore(&ep->udc->lock, flags);

	अगर (ep->ep_num == 0) अणु
		udc->ep0_state = WAIT_FOR_SETUP;
		udc->ep0_dir = EP_सूची_OUT;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल पूर्णांक mv_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक halt)
अणु
	वापस mv_ep_set_halt_wedge(_ep, halt, 0);
पूर्ण

अटल पूर्णांक mv_ep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस mv_ep_set_halt_wedge(_ep, 1, 1);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops mv_ep_ops = अणु
	.enable		= mv_ep_enable,
	.disable	= mv_ep_disable,

	.alloc_request	= mv_alloc_request,
	.मुक्त_request	= mv_मुक्त_request,

	.queue		= mv_ep_queue,
	.dequeue	= mv_ep_dequeue,

	.set_wedge	= mv_ep_set_wedge,
	.set_halt	= mv_ep_set_halt,
	.fअगरo_flush	= mv_ep_fअगरo_flush,	/* flush fअगरo */
पूर्ण;

अटल पूर्णांक udc_घड़ी_enable(काष्ठा mv_udc *udc)
अणु
	वापस clk_prepare_enable(udc->clk);
पूर्ण

अटल व्योम udc_घड़ी_disable(काष्ठा mv_udc *udc)
अणु
	clk_disable_unprepare(udc->clk);
पूर्ण

अटल व्योम udc_stop(काष्ठा mv_udc *udc)
अणु
	u32 पंचांगp;

	/* Disable पूर्णांकerrupts */
	पंचांगp = पढ़ोl(&udc->op_regs->usbपूर्णांकr);
	पंचांगp &= ~(USBINTR_INT_EN | USBINTR_ERR_INT_EN |
		USBINTR_PORT_CHANGE_DETECT_EN | USBINTR_RESET_EN);
	ग_लिखोl(पंचांगp, &udc->op_regs->usbपूर्णांकr);

	udc->stopped = 1;

	/* Reset the Run the bit in the command रेजिस्टर to stop VUSB */
	पंचांगp = पढ़ोl(&udc->op_regs->usbcmd);
	पंचांगp &= ~USBCMD_RUN_STOP;
	ग_लिखोl(पंचांगp, &udc->op_regs->usbcmd);
पूर्ण

अटल व्योम udc_start(काष्ठा mv_udc *udc)
अणु
	u32 usbपूर्णांकr;

	usbपूर्णांकr = USBINTR_INT_EN | USBINTR_ERR_INT_EN
		| USBINTR_PORT_CHANGE_DETECT_EN
		| USBINTR_RESET_EN | USBINTR_DEVICE_SUSPEND;
	/* Enable पूर्णांकerrupts */
	ग_लिखोl(usbपूर्णांकr, &udc->op_regs->usbपूर्णांकr);

	udc->stopped = 0;

	/* Set the Run bit in the command रेजिस्टर */
	ग_लिखोl(USBCMD_RUN_STOP, &udc->op_regs->usbcmd);
पूर्ण

अटल पूर्णांक udc_reset(काष्ठा mv_udc *udc)
अणु
	अचिन्हित पूर्णांक loops;
	u32 पंचांगp, portsc;

	/* Stop the controller */
	पंचांगp = पढ़ोl(&udc->op_regs->usbcmd);
	पंचांगp &= ~USBCMD_RUN_STOP;
	ग_लिखोl(पंचांगp, &udc->op_regs->usbcmd);

	/* Reset the controller to get शेष values */
	ग_लिखोl(USBCMD_CTRL_RESET, &udc->op_regs->usbcmd);

	/* रुको क्रम reset to complete */
	loops = LOOPS(RESET_TIMEOUT);
	जबतक (पढ़ोl(&udc->op_regs->usbcmd) & USBCMD_CTRL_RESET) अणु
		अगर (loops == 0) अणु
			dev_err(&udc->dev->dev,
				"Wait for RESET completed TIMEOUT\n");
			वापस -ETIMEDOUT;
		पूर्ण
		loops--;
		udelay(LOOPS_USEC);
	पूर्ण

	/* set controller to device mode */
	पंचांगp = पढ़ोl(&udc->op_regs->usbmode);
	पंचांगp |= USBMODE_CTRL_MODE_DEVICE;

	/* turn setup lockout off, require setup tripwire in usbcmd */
	पंचांगp |= USBMODE_SETUP_LOCK_OFF;

	ग_लिखोl(पंचांगp, &udc->op_regs->usbmode);

	ग_लिखोl(0x0, &udc->op_regs->epsetupstat);

	/* Configure the Endpoपूर्णांक List Address */
	ग_लिखोl(udc->ep_dqh_dma & USB_EP_LIST_ADDRESS_MASK,
		&udc->op_regs->eplistaddr);

	portsc = पढ़ोl(&udc->op_regs->portsc[0]);
	अगर (पढ़ोl(&udc->cap_regs->hcsparams) & HCSPARAMS_PPC)
		portsc &= (~PORTSCX_W1C_BITS | ~PORTSCX_PORT_POWER);

	अगर (udc->क्रमce_fs)
		portsc |= PORTSCX_FORCE_FULL_SPEED_CONNECT;
	अन्यथा
		portsc &= (~PORTSCX_FORCE_FULL_SPEED_CONNECT);

	ग_लिखोl(portsc, &udc->op_regs->portsc[0]);

	पंचांगp = पढ़ोl(&udc->op_regs->epctrlx[0]);
	पंचांगp &= ~(EPCTRL_TX_EP_STALL | EPCTRL_RX_EP_STALL);
	ग_लिखोl(पंचांगp, &udc->op_regs->epctrlx[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_udc_enable_पूर्णांकernal(काष्ठा mv_udc *udc)
अणु
	पूर्णांक retval;

	अगर (udc->active)
		वापस 0;

	dev_dbg(&udc->dev->dev, "enable udc\n");
	retval = udc_घड़ी_enable(udc);
	अगर (retval)
		वापस retval;

	अगर (udc->pdata->phy_init) अणु
		retval = udc->pdata->phy_init(udc->phy_regs);
		अगर (retval) अणु
			dev_err(&udc->dev->dev,
				"init phy error %d\n", retval);
			udc_घड़ी_disable(udc);
			वापस retval;
		पूर्ण
	पूर्ण
	udc->active = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक mv_udc_enable(काष्ठा mv_udc *udc)
अणु
	अगर (udc->घड़ी_gating)
		वापस mv_udc_enable_पूर्णांकernal(udc);

	वापस 0;
पूर्ण

अटल व्योम mv_udc_disable_पूर्णांकernal(काष्ठा mv_udc *udc)
अणु
	अगर (udc->active) अणु
		dev_dbg(&udc->dev->dev, "disable udc\n");
		अगर (udc->pdata->phy_deinit)
			udc->pdata->phy_deinit(udc->phy_regs);
		udc_घड़ी_disable(udc);
		udc->active = 0;
	पूर्ण
पूर्ण

अटल व्योम mv_udc_disable(काष्ठा mv_udc *udc)
अणु
	अगर (udc->घड़ी_gating)
		mv_udc_disable_पूर्णांकernal(udc);
पूर्ण

अटल पूर्णांक mv_udc_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा mv_udc *udc;
	u16	retval;

	अगर (!gadget)
		वापस -ENODEV;

	udc = container_of(gadget, काष्ठा mv_udc, gadget);

	retval = पढ़ोl(&udc->op_regs->frindex) & USB_FRINDEX_MASKS;

	वापस retval;
पूर्ण

/* Tries to wake up the host connected to this gadget */
अटल पूर्णांक mv_udc_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा mv_udc *udc = container_of(gadget, काष्ठा mv_udc, gadget);
	u32 portsc;

	/* Remote wakeup feature not enabled by host */
	अगर (!udc->remote_wakeup)
		वापस -ENOTSUPP;

	portsc = पढ़ोl(&udc->op_regs->portsc);
	/* not suspended? */
	अगर (!(portsc & PORTSCX_PORT_SUSPEND))
		वापस 0;
	/* trigger क्रमce resume */
	portsc |= PORTSCX_PORT_FORCE_RESUME;
	ग_लिखोl(portsc, &udc->op_regs->portsc[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक mv_udc_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा mv_udc *udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	udc = container_of(gadget, काष्ठा mv_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);

	udc->vbus_active = (is_active != 0);

	dev_dbg(&udc->dev->dev, "%s: softconnect %d, vbus_active %d\n",
		__func__, udc->softconnect, udc->vbus_active);

	अगर (udc->driver && udc->softconnect && udc->vbus_active) अणु
		retval = mv_udc_enable(udc);
		अगर (retval == 0) अणु
			/* Clock is disabled, need re-init रेजिस्टरs */
			udc_reset(udc);
			ep0_reset(udc);
			udc_start(udc);
		पूर्ण
	पूर्ण अन्यथा अगर (udc->driver && udc->softconnect) अणु
		अगर (!udc->active)
			जाओ out;

		/* stop all the transfer in queue*/
		stop_activity(udc, udc->driver);
		udc_stop(udc);
		mv_udc_disable(udc);
	पूर्ण

out:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक mv_udc_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा mv_udc *udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = 0;

	udc = container_of(gadget, काष्ठा mv_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);

	udc->softconnect = (is_on != 0);

	dev_dbg(&udc->dev->dev, "%s: softconnect %d, vbus_active %d\n",
			__func__, udc->softconnect, udc->vbus_active);

	अगर (udc->driver && udc->softconnect && udc->vbus_active) अणु
		retval = mv_udc_enable(udc);
		अगर (retval == 0) अणु
			/* Clock is disabled, need re-init रेजिस्टरs */
			udc_reset(udc);
			ep0_reset(udc);
			udc_start(udc);
		पूर्ण
	पूर्ण अन्यथा अगर (udc->driver && udc->vbus_active) अणु
		/* stop all the transfer in queue*/
		stop_activity(udc, udc->driver);
		udc_stop(udc);
		mv_udc_disable(udc);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक mv_udc_start(काष्ठा usb_gadget *, काष्ठा usb_gadget_driver *);
अटल पूर्णांक mv_udc_stop(काष्ठा usb_gadget *);
/* device controller usb_gadget_ops काष्ठाure */
अटल स्थिर काष्ठा usb_gadget_ops mv_ops = अणु

	/* वापसs the current frame number */
	.get_frame	= mv_udc_get_frame,

	/* tries to wake up the host connected to this gadget */
	.wakeup		= mv_udc_wakeup,

	/* notअगरy controller that VBUS is घातered or not */
	.vbus_session	= mv_udc_vbus_session,

	/* D+ pullup, software-controlled connect/disconnect to USB host */
	.pullup		= mv_udc_pullup,
	.udc_start	= mv_udc_start,
	.udc_stop	= mv_udc_stop,
पूर्ण;

अटल पूर्णांक eps_init(काष्ठा mv_udc *udc)
अणु
	काष्ठा mv_ep	*ep;
	अक्षर name[14];
	पूर्णांक i;

	/* initialize ep0 */
	ep = &udc->eps[0];
	ep->udc = udc;
	म_नकलन(ep->name, "ep0", माप(ep->name));
	ep->ep.name = ep->name;
	ep->ep.ops = &mv_ep_ops;
	ep->wedge = 0;
	ep->stopped = 0;
	usb_ep_set_maxpacket_limit(&ep->ep, EP0_MAX_PKT_SIZE);
	ep->ep.caps.type_control = true;
	ep->ep.caps.dir_in = true;
	ep->ep.caps.dir_out = true;
	ep->ep_num = 0;
	ep->ep.desc = &mv_ep0_desc;
	INIT_LIST_HEAD(&ep->queue);

	ep->ep_type = USB_ENDPOINT_XFER_CONTROL;

	/* initialize other endpoपूर्णांकs */
	क्रम (i = 2; i < udc->max_eps * 2; i++) अणु
		ep = &udc->eps[i];
		अगर (i % 2) अणु
			snम_लिखो(name, माप(name), "ep%din", i / 2);
			ep->direction = EP_सूची_IN;
			ep->ep.caps.dir_in = true;
		पूर्ण अन्यथा अणु
			snम_लिखो(name, माप(name), "ep%dout", i / 2);
			ep->direction = EP_सूची_OUT;
			ep->ep.caps.dir_out = true;
		पूर्ण
		ep->udc = udc;
		म_नकलन(ep->name, name, माप(ep->name));
		ep->ep.name = ep->name;

		ep->ep.caps.type_iso = true;
		ep->ep.caps.type_bulk = true;
		ep->ep.caps.type_पूर्णांक = true;

		ep->ep.ops = &mv_ep_ops;
		ep->stopped = 0;
		usb_ep_set_maxpacket_limit(&ep->ep, (अचिन्हित लघु) ~0);
		ep->ep_num = i / 2;

		INIT_LIST_HEAD(&ep->queue);
		list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);

		ep->dqh = &udc->ep_dqh[i];
	पूर्ण

	वापस 0;
पूर्ण

/* delete all endpoपूर्णांक requests, called with spinlock held */
अटल व्योम nuke(काष्ठा mv_ep *ep, पूर्णांक status)
अणु
	/* called with spinlock held */
	ep->stopped = 1;

	/* endpoपूर्णांक fअगरo flush */
	mv_ep_fअगरo_flush(&ep->ep);

	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा mv_req *req = शून्य;
		req = list_entry(ep->queue.next, काष्ठा mv_req, queue);
		करोne(ep, req, status);
	पूर्ण
पूर्ण

अटल व्योम gadget_reset(काष्ठा mv_udc *udc, काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा mv_ep	*ep;

	nuke(&udc->eps[0], -ESHUTDOWN);

	list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list) अणु
		nuke(ep, -ESHUTDOWN);
	पूर्ण

	/* report reset; the driver is alपढ़ोy quiesced */
	अगर (driver) अणु
		spin_unlock(&udc->lock);
		usb_gadget_udc_reset(&udc->gadget, driver);
		spin_lock(&udc->lock);
	पूर्ण
पूर्ण
/* stop all USB activities */
अटल व्योम stop_activity(काष्ठा mv_udc *udc, काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा mv_ep	*ep;

	nuke(&udc->eps[0], -ESHUTDOWN);

	list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list) अणु
		nuke(ep, -ESHUTDOWN);
	पूर्ण

	/* report disconnect; the driver is alपढ़ोy quiesced */
	अगर (driver) अणु
		spin_unlock(&udc->lock);
		driver->disconnect(&udc->gadget);
		spin_lock(&udc->lock);
	पूर्ण
पूर्ण

अटल पूर्णांक mv_udc_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा mv_udc *udc;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	udc = container_of(gadget, काष्ठा mv_udc, gadget);

	अगर (udc->driver)
		वापस -EBUSY;

	spin_lock_irqsave(&udc->lock, flags);

	/* hook up the driver ... */
	driver->driver.bus = शून्य;
	udc->driver = driver;

	udc->usb_state = USB_STATE_ATTACHED;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = EP_सूची_OUT;

	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->transceiver) अणु
		retval = otg_set_peripheral(udc->transceiver->otg,
					&udc->gadget);
		अगर (retval) अणु
			dev_err(&udc->dev->dev,
				"unable to register peripheral to otg\n");
			udc->driver = शून्य;
			वापस retval;
		पूर्ण
	पूर्ण

	/* When boot with cable attached, there will be no vbus irq occurred */
	अगर (udc->qwork)
		queue_work(udc->qwork, &udc->vbus_work);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा mv_udc *udc;
	अचिन्हित दीर्घ flags;

	udc = container_of(gadget, काष्ठा mv_udc, gadget);

	spin_lock_irqsave(&udc->lock, flags);

	mv_udc_enable(udc);
	udc_stop(udc);

	/* stop all usb activities */
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	stop_activity(udc, शून्य);
	mv_udc_disable(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	/* unbind gadget driver */
	udc->driver = शून्य;

	वापस 0;
पूर्ण

अटल व्योम mv_set_ptc(काष्ठा mv_udc *udc, u32 mode)
अणु
	u32 portsc;

	portsc = पढ़ोl(&udc->op_regs->portsc[0]);
	portsc |= mode << 16;
	ग_लिखोl(portsc, &udc->op_regs->portsc[0]);
पूर्ण

अटल व्योम prime_status_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *_req)
अणु
	काष्ठा mv_ep *mvep = container_of(ep, काष्ठा mv_ep, ep);
	काष्ठा mv_req *req = container_of(_req, काष्ठा mv_req, req);
	काष्ठा mv_udc *udc;
	अचिन्हित दीर्घ flags;

	udc = mvep->udc;

	dev_info(&udc->dev->dev, "switch to test mode %d\n", req->test_mode);

	spin_lock_irqsave(&udc->lock, flags);
	अगर (req->test_mode) अणु
		mv_set_ptc(udc, req->test_mode);
		req->test_mode = 0;
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल पूर्णांक
udc_prime_status(काष्ठा mv_udc *udc, u8 direction, u16 status, bool empty)
अणु
	पूर्णांक retval = 0;
	काष्ठा mv_req *req;
	काष्ठा mv_ep *ep;

	ep = &udc->eps[0];
	udc->ep0_dir = direction;
	udc->ep0_state = WAIT_FOR_OUT_STATUS;

	req = udc->status_req;

	/* fill in the reqest काष्ठाure */
	अगर (empty == false) अणु
		*((u16 *) req->req.buf) = cpu_to_le16(status);
		req->req.length = 2;
	पूर्ण अन्यथा
		req->req.length = 0;

	req->ep = ep;
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	अगर (udc->test_mode) अणु
		req->req.complete = prime_status_complete;
		req->test_mode = udc->test_mode;
		udc->test_mode = 0;
	पूर्ण अन्यथा
		req->req.complete = शून्य;
	req->dtd_count = 0;

	अगर (req->req.dma == DMA_ADDR_INVALID) अणु
		req->req.dma = dma_map_single(ep->udc->gadget.dev.parent,
				req->req.buf, req->req.length,
				ep_dir(ep) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		req->mapped = 1;
	पूर्ण

	/* prime the data phase */
	अगर (!req_to_dtd(req)) अणु
		retval = queue_dtd(ep, req);
		अगर (retval) अणु
			dev_err(&udc->dev->dev,
				"Failed to queue dtd when prime status\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथाअणु	/* no mem */
		retval = -ENOMEM;
		dev_err(&udc->dev->dev,
			"Failed to dma_pool_alloc when prime status\n");
		जाओ out;
	पूर्ण

	list_add_tail(&req->queue, &ep->queue);

	वापस 0;
out:
	usb_gadget_unmap_request(&udc->gadget, &req->req, ep_dir(ep));

	वापस retval;
पूर्ण

अटल व्योम mv_udc_tesपंचांगode(काष्ठा mv_udc *udc, u16 index)
अणु
	अगर (index <= USB_TEST_FORCE_ENABLE) अणु
		udc->test_mode = index;
		अगर (udc_prime_status(udc, EP_सूची_IN, 0, true))
			ep0_stall(udc);
	पूर्ण अन्यथा
		dev_err(&udc->dev->dev,
			"This test mode(%d) is not supported\n", index);
पूर्ण

अटल व्योम ch9setaddress(काष्ठा mv_udc *udc, काष्ठा usb_ctrlrequest *setup)
अणु
	udc->dev_addr = (u8)setup->wValue;

	/* update usb state */
	udc->usb_state = USB_STATE_ADDRESS;

	अगर (udc_prime_status(udc, EP_सूची_IN, 0, true))
		ep0_stall(udc);
पूर्ण

अटल व्योम ch9माला_लोtatus(काष्ठा mv_udc *udc, u8 ep_num,
	काष्ठा usb_ctrlrequest *setup)
अणु
	u16 status = 0;
	पूर्णांक retval;

	अगर ((setup->bRequestType & (USB_सूची_IN | USB_TYPE_MASK))
		!= (USB_सूची_IN | USB_TYPE_STANDARD))
		वापस;

	अगर ((setup->bRequestType & USB_RECIP_MASK) == USB_RECIP_DEVICE) अणु
		status = 1 << USB_DEVICE_SELF_POWERED;
		status |= udc->remote_wakeup << USB_DEVICE_REMOTE_WAKEUP;
	पूर्ण अन्यथा अगर ((setup->bRequestType & USB_RECIP_MASK)
			== USB_RECIP_INTERFACE) अणु
		/* get पूर्णांकerface status */
		status = 0;
	पूर्ण अन्यथा अगर ((setup->bRequestType & USB_RECIP_MASK)
			== USB_RECIP_ENDPOINT) अणु
		u8 ep_num, direction;

		ep_num = setup->wIndex & USB_ENDPOINT_NUMBER_MASK;
		direction = (setup->wIndex & USB_ENDPOINT_सूची_MASK)
				? EP_सूची_IN : EP_सूची_OUT;
		status = ep_is_stall(udc, ep_num, direction)
				<< USB_ENDPOINT_HALT;
	पूर्ण

	retval = udc_prime_status(udc, EP_सूची_IN, status, false);
	अगर (retval)
		ep0_stall(udc);
	अन्यथा
		udc->ep0_state = DATA_STATE_XMIT;
पूर्ण

अटल व्योम ch9clearfeature(काष्ठा mv_udc *udc, काष्ठा usb_ctrlrequest *setup)
अणु
	u8 ep_num;
	u8 direction;
	काष्ठा mv_ep *ep;

	अगर ((setup->bRequestType & (USB_TYPE_MASK | USB_RECIP_MASK))
		== ((USB_TYPE_STANDARD | USB_RECIP_DEVICE))) अणु
		चयन (setup->wValue) अणु
		हाल USB_DEVICE_REMOTE_WAKEUP:
			udc->remote_wakeup = 0;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((setup->bRequestType & (USB_TYPE_MASK | USB_RECIP_MASK))
		== ((USB_TYPE_STANDARD | USB_RECIP_ENDPOINT))) अणु
		चयन (setup->wValue) अणु
		हाल USB_ENDPOINT_HALT:
			ep_num = setup->wIndex & USB_ENDPOINT_NUMBER_MASK;
			direction = (setup->wIndex & USB_ENDPOINT_सूची_MASK)
				? EP_सूची_IN : EP_सूची_OUT;
			अगर (setup->wValue != 0 || setup->wLength != 0
				|| ep_num > udc->max_eps)
				जाओ out;
			ep = &udc->eps[ep_num * 2 + direction];
			अगर (ep->wedge == 1)
				अवरोध;
			spin_unlock(&udc->lock);
			ep_set_stall(udc, ep_num, direction, 0);
			spin_lock(&udc->lock);
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		जाओ out;

	अगर (udc_prime_status(udc, EP_सूची_IN, 0, true))
		ep0_stall(udc);
out:
	वापस;
पूर्ण

अटल व्योम ch9setfeature(काष्ठा mv_udc *udc, काष्ठा usb_ctrlrequest *setup)
अणु
	u8 ep_num;
	u8 direction;

	अगर ((setup->bRequestType & (USB_TYPE_MASK | USB_RECIP_MASK))
		== ((USB_TYPE_STANDARD | USB_RECIP_DEVICE))) अणु
		चयन (setup->wValue) अणु
		हाल USB_DEVICE_REMOTE_WAKEUP:
			udc->remote_wakeup = 1;
			अवरोध;
		हाल USB_DEVICE_TEST_MODE:
			अगर (setup->wIndex & 0xFF
				||  udc->gadget.speed != USB_SPEED_HIGH)
				ep0_stall(udc);

			अगर (udc->usb_state != USB_STATE_CONFIGURED
				&& udc->usb_state != USB_STATE_ADDRESS
				&& udc->usb_state != USB_STATE_DEFAULT)
				ep0_stall(udc);

			mv_udc_tesपंचांगode(udc, (setup->wIndex >> 8));
			जाओ out;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर ((setup->bRequestType & (USB_TYPE_MASK | USB_RECIP_MASK))
		== ((USB_TYPE_STANDARD | USB_RECIP_ENDPOINT))) अणु
		चयन (setup->wValue) अणु
		हाल USB_ENDPOINT_HALT:
			ep_num = setup->wIndex & USB_ENDPOINT_NUMBER_MASK;
			direction = (setup->wIndex & USB_ENDPOINT_सूची_MASK)
				? EP_सूची_IN : EP_सूची_OUT;
			अगर (setup->wValue != 0 || setup->wLength != 0
				|| ep_num > udc->max_eps)
				जाओ out;
			spin_unlock(&udc->lock);
			ep_set_stall(udc, ep_num, direction, 1);
			spin_lock(&udc->lock);
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		जाओ out;

	अगर (udc_prime_status(udc, EP_सूची_IN, 0, true))
		ep0_stall(udc);
out:
	वापस;
पूर्ण

अटल व्योम handle_setup_packet(काष्ठा mv_udc *udc, u8 ep_num,
	काष्ठा usb_ctrlrequest *setup)
	__releases(&ep->udc->lock)
	__acquires(&ep->udc->lock)
अणु
	bool delegate = false;

	nuke(&udc->eps[ep_num * 2 + EP_सूची_OUT], -ESHUTDOWN);

	dev_dbg(&udc->dev->dev, "SETUP %02x.%02x v%04x i%04x l%04x\n",
			setup->bRequestType, setup->bRequest,
			setup->wValue, setup->wIndex, setup->wLength);
	/* We process some standard setup requests here */
	अगर ((setup->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (setup->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			ch9माला_लोtatus(udc, ep_num, setup);
			अवरोध;

		हाल USB_REQ_SET_ADDRESS:
			ch9setaddress(udc, setup);
			अवरोध;

		हाल USB_REQ_CLEAR_FEATURE:
			ch9clearfeature(udc, setup);
			अवरोध;

		हाल USB_REQ_SET_FEATURE:
			ch9setfeature(udc, setup);
			अवरोध;

		शेष:
			delegate = true;
		पूर्ण
	पूर्ण अन्यथा
		delegate = true;

	/* delegate USB standard requests to the gadget driver */
	अगर (delegate == true) अणु
		/* USB requests handled by gadget */
		अगर (setup->wLength) अणु
			/* DATA phase from gadget, STATUS phase from udc */
			udc->ep0_dir = (setup->bRequestType & USB_सूची_IN)
					?  EP_सूची_IN : EP_सूची_OUT;
			spin_unlock(&udc->lock);
			अगर (udc->driver->setup(&udc->gadget,
				&udc->local_setup_buff) < 0)
				ep0_stall(udc);
			spin_lock(&udc->lock);
			udc->ep0_state = (setup->bRequestType & USB_सूची_IN)
					?  DATA_STATE_XMIT : DATA_STATE_RECV;
		पूर्ण अन्यथा अणु
			/* no DATA phase, IN STATUS phase from gadget */
			udc->ep0_dir = EP_सूची_IN;
			spin_unlock(&udc->lock);
			अगर (udc->driver->setup(&udc->gadget,
				&udc->local_setup_buff) < 0)
				ep0_stall(udc);
			spin_lock(&udc->lock);
			udc->ep0_state = WAIT_FOR_OUT_STATUS;
		पूर्ण
	पूर्ण
पूर्ण

/* complete DATA or STATUS phase of ep0 prime status phase अगर needed */
अटल व्योम ep0_req_complete(काष्ठा mv_udc *udc,
	काष्ठा mv_ep *ep0, काष्ठा mv_req *req)
अणु
	u32 new_addr;

	अगर (udc->usb_state == USB_STATE_ADDRESS) अणु
		/* set the new address */
		new_addr = (u32)udc->dev_addr;
		ग_लिखोl(new_addr << USB_DEVICE_ADDRESS_BIT_SHIFT,
			&udc->op_regs->deviceaddr);
	पूर्ण

	करोne(ep0, req, 0);

	चयन (udc->ep0_state) अणु
	हाल DATA_STATE_XMIT:
		/* receive status phase */
		अगर (udc_prime_status(udc, EP_सूची_OUT, 0, true))
			ep0_stall(udc);
		अवरोध;
	हाल DATA_STATE_RECV:
		/* send status phase */
		अगर (udc_prime_status(udc, EP_सूची_IN, 0 , true))
			ep0_stall(udc);
		अवरोध;
	हाल WAIT_FOR_OUT_STATUS:
		udc->ep0_state = WAIT_FOR_SETUP;
		अवरोध;
	हाल WAIT_FOR_SETUP:
		dev_err(&udc->dev->dev, "unexpect ep0 packets\n");
		अवरोध;
	शेष:
		ep0_stall(udc);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम get_setup_data(काष्ठा mv_udc *udc, u8 ep_num, u8 *buffer_ptr)
अणु
	u32 temp;
	काष्ठा mv_dqh *dqh;

	dqh = &udc->ep_dqh[ep_num * 2 + EP_सूची_OUT];

	/* Clear bit in ENDPTSETUPSTAT */
	ग_लिखोl((1 << ep_num), &udc->op_regs->epsetupstat);

	/* जबतक a hazard exists when setup package arrives */
	करो अणु
		/* Set Setup Tripwire */
		temp = पढ़ोl(&udc->op_regs->usbcmd);
		ग_लिखोl(temp | USBCMD_SETUP_TRIPWIRE_SET, &udc->op_regs->usbcmd);

		/* Copy the setup packet to local buffer */
		स_नकल(buffer_ptr, (u8 *) dqh->setup_buffer, 8);
	पूर्ण जबतक (!(पढ़ोl(&udc->op_regs->usbcmd) & USBCMD_SETUP_TRIPWIRE_SET));

	/* Clear Setup Tripwire */
	temp = पढ़ोl(&udc->op_regs->usbcmd);
	ग_लिखोl(temp & ~USBCMD_SETUP_TRIPWIRE_SET, &udc->op_regs->usbcmd);
पूर्ण

अटल व्योम irq_process_tr_complete(काष्ठा mv_udc *udc)
अणु
	u32 पंचांगp, bit_pos;
	पूर्णांक i, ep_num = 0, direction = 0;
	काष्ठा mv_ep	*curr_ep;
	काष्ठा mv_req *curr_req, *temp_req;
	पूर्णांक status;

	/*
	 * We use separate loops क्रम ENDPTSETUPSTAT and ENDPTCOMPLETE
	 * because the setup packets are to be पढ़ो ASAP
	 */

	/* Process all Setup packet received पूर्णांकerrupts */
	पंचांगp = पढ़ोl(&udc->op_regs->epsetupstat);

	अगर (पंचांगp) अणु
		क्रम (i = 0; i < udc->max_eps; i++) अणु
			अगर (पंचांगp & (1 << i)) अणु
				get_setup_data(udc, i,
					(u8 *)(&udc->local_setup_buff));
				handle_setup_packet(udc, i,
					&udc->local_setup_buff);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Don't clear the endpoपूर्णांक setup status रेजिस्टर here.
	 * It is cleared as a setup packet is पढ़ो out of the buffer
	 */

	/* Process non-setup transaction complete पूर्णांकerrupts */
	पंचांगp = पढ़ोl(&udc->op_regs->epcomplete);

	अगर (!पंचांगp)
		वापस;

	ग_लिखोl(पंचांगp, &udc->op_regs->epcomplete);

	क्रम (i = 0; i < udc->max_eps * 2; i++) अणु
		ep_num = i >> 1;
		direction = i % 2;

		bit_pos = 1 << (ep_num + 16 * direction);

		अगर (!(bit_pos & पंचांगp))
			जारी;

		अगर (i == 1)
			curr_ep = &udc->eps[0];
		अन्यथा
			curr_ep = &udc->eps[i];
		/* process the req queue until an uncomplete request */
		list_क्रम_each_entry_safe(curr_req, temp_req,
			&curr_ep->queue, queue) अणु
			status = process_ep_req(udc, i, curr_req);
			अगर (status)
				अवरोध;

			/* ग_लिखो back status to req */
			curr_req->req.status = status;

			/* ep0 request completion */
			अगर (ep_num == 0) अणु
				ep0_req_complete(udc, curr_ep, curr_req);
				अवरोध;
			पूर्ण अन्यथा अणु
				करोne(curr_ep, curr_req, status);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम irq_process_reset(काष्ठा mv_udc *udc)
अणु
	u32 पंचांगp;
	अचिन्हित पूर्णांक loops;

	udc->ep0_dir = EP_सूची_OUT;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->remote_wakeup = 0;		/* शेष to 0 on reset */

	/* The address bits are past bit 25-31. Set the address */
	पंचांगp = पढ़ोl(&udc->op_regs->deviceaddr);
	पंचांगp &= ~(USB_DEVICE_ADDRESS_MASK);
	ग_लिखोl(पंचांगp, &udc->op_regs->deviceaddr);

	/* Clear all the setup token semaphores */
	पंचांगp = पढ़ोl(&udc->op_regs->epsetupstat);
	ग_लिखोl(पंचांगp, &udc->op_regs->epsetupstat);

	/* Clear all the endpoपूर्णांक complete status bits */
	पंचांगp = पढ़ोl(&udc->op_regs->epcomplete);
	ग_लिखोl(पंचांगp, &udc->op_regs->epcomplete);

	/* रुको until all endptprime bits cleared */
	loops = LOOPS(PRIME_TIMEOUT);
	जबतक (पढ़ोl(&udc->op_regs->epprime) & 0xFFFFFFFF) अणु
		अगर (loops == 0) अणु
			dev_err(&udc->dev->dev,
				"Timeout for ENDPTPRIME = 0x%x\n",
				पढ़ोl(&udc->op_regs->epprime));
			अवरोध;
		पूर्ण
		loops--;
		udelay(LOOPS_USEC);
	पूर्ण

	/* Write 1s to the Flush रेजिस्टर */
	ग_लिखोl((u32)~0, &udc->op_regs->epflush);

	अगर (पढ़ोl(&udc->op_regs->portsc[0]) & PORTSCX_PORT_RESET) अणु
		dev_info(&udc->dev->dev, "usb bus reset\n");
		udc->usb_state = USB_STATE_DEFAULT;
		/* reset all the queues, stop all USB activities */
		gadget_reset(udc, udc->driver);
	पूर्ण अन्यथा अणु
		dev_info(&udc->dev->dev, "USB reset portsc 0x%x\n",
			पढ़ोl(&udc->op_regs->portsc));

		/*
		 * re-initialize
		 * controller reset
		 */
		udc_reset(udc);

		/* reset all the queues, stop all USB activities */
		stop_activity(udc, udc->driver);

		/* reset ep0 dQH and endptctrl */
		ep0_reset(udc);

		/* enable पूर्णांकerrupt and set controller to run state */
		udc_start(udc);

		udc->usb_state = USB_STATE_ATTACHED;
	पूर्ण
पूर्ण

अटल व्योम handle_bus_resume(काष्ठा mv_udc *udc)
अणु
	udc->usb_state = udc->resume_state;
	udc->resume_state = 0;

	/* report resume to the driver */
	अगर (udc->driver) अणु
		अगर (udc->driver->resume) अणु
			spin_unlock(&udc->lock);
			udc->driver->resume(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम irq_process_suspend(काष्ठा mv_udc *udc)
अणु
	udc->resume_state = udc->usb_state;
	udc->usb_state = USB_STATE_SUSPENDED;

	अगर (udc->driver->suspend) अणु
		spin_unlock(&udc->lock);
		udc->driver->suspend(&udc->gadget);
		spin_lock(&udc->lock);
	पूर्ण
पूर्ण

अटल व्योम irq_process_port_change(काष्ठा mv_udc *udc)
अणु
	u32 portsc;

	portsc = पढ़ोl(&udc->op_regs->portsc[0]);
	अगर (!(portsc & PORTSCX_PORT_RESET)) अणु
		/* Get the speed */
		u32 speed = portsc & PORTSCX_PORT_SPEED_MASK;
		चयन (speed) अणु
		हाल PORTSCX_PORT_SPEED_HIGH:
			udc->gadget.speed = USB_SPEED_HIGH;
			अवरोध;
		हाल PORTSCX_PORT_SPEED_FULL:
			udc->gadget.speed = USB_SPEED_FULL;
			अवरोध;
		हाल PORTSCX_PORT_SPEED_LOW:
			udc->gadget.speed = USB_SPEED_LOW;
			अवरोध;
		शेष:
			udc->gadget.speed = USB_SPEED_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (portsc & PORTSCX_PORT_SUSPEND) अणु
		udc->resume_state = udc->usb_state;
		udc->usb_state = USB_STATE_SUSPENDED;
		अगर (udc->driver->suspend) अणु
			spin_unlock(&udc->lock);
			udc->driver->suspend(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण

	अगर (!(portsc & PORTSCX_PORT_SUSPEND)
		&& udc->usb_state == USB_STATE_SUSPENDED) अणु
		handle_bus_resume(udc);
	पूर्ण

	अगर (!udc->resume_state)
		udc->usb_state = USB_STATE_DEFAULT;
पूर्ण

अटल व्योम irq_process_error(काष्ठा mv_udc *udc)
अणु
	/* Increment the error count */
	udc->errors++;
पूर्ण

अटल irqवापस_t mv_udc_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mv_udc *udc = (काष्ठा mv_udc *)dev;
	u32 status, पूर्णांकr;

	/* Disable ISR when stopped bit is set */
	अगर (udc->stopped)
		वापस IRQ_NONE;

	spin_lock(&udc->lock);

	status = पढ़ोl(&udc->op_regs->usbsts);
	पूर्णांकr = पढ़ोl(&udc->op_regs->usbपूर्णांकr);
	status &= पूर्णांकr;

	अगर (status == 0) अणु
		spin_unlock(&udc->lock);
		वापस IRQ_NONE;
	पूर्ण

	/* Clear all the पूर्णांकerrupts occurred */
	ग_लिखोl(status, &udc->op_regs->usbsts);

	अगर (status & USBSTS_ERR)
		irq_process_error(udc);

	अगर (status & USBSTS_RESET)
		irq_process_reset(udc);

	अगर (status & USBSTS_PORT_CHANGE)
		irq_process_port_change(udc);

	अगर (status & USBSTS_INT)
		irq_process_tr_complete(udc);

	अगर (status & USBSTS_SUSPEND)
		irq_process_suspend(udc);

	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mv_udc_vbus_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा mv_udc *udc = (काष्ठा mv_udc *)dev;

	/* polling VBUS and init phy may cause too much समय*/
	अगर (udc->qwork)
		queue_work(udc->qwork, &udc->vbus_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mv_udc_vbus_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mv_udc *udc;
	अचिन्हित पूर्णांक vbus;

	udc = container_of(work, काष्ठा mv_udc, vbus_work);
	अगर (!udc->pdata->vbus)
		वापस;

	vbus = udc->pdata->vbus->poll();
	dev_info(&udc->dev->dev, "vbus is %d\n", vbus);

	अगर (vbus == VBUS_HIGH)
		mv_udc_vbus_session(&udc->gadget, 1);
	अन्यथा अगर (vbus == VBUS_LOW)
		mv_udc_vbus_session(&udc->gadget, 0);
पूर्ण

/* release device काष्ठाure */
अटल व्योम gadget_release(काष्ठा device *_dev)
अणु
	काष्ठा mv_udc *udc;

	udc = dev_get_drvdata(_dev);

	complete(udc->करोne);
पूर्ण

अटल पूर्णांक mv_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_udc *udc;

	udc = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);

	अगर (udc->qwork) अणु
		flush_workqueue(udc->qwork);
		destroy_workqueue(udc->qwork);
	पूर्ण

	/* मुक्त memory allocated in probe */
	dma_pool_destroy(udc->dtd_pool);

	अगर (udc->ep_dqh)
		dma_मुक्त_coherent(&pdev->dev, udc->ep_dqh_size,
			udc->ep_dqh, udc->ep_dqh_dma);

	mv_udc_disable(udc);

	/* मुक्त dev, रुको क्रम the release() finished */
	रुको_क्रम_completion(udc->करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा mv_udc *udc;
	पूर्णांक retval = 0;
	काष्ठा resource *r;
	माप_प्रकार size;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "missing platform_data\n");
		वापस -ENODEV;
	पूर्ण

	udc = devm_kzalloc(&pdev->dev, माप(*udc), GFP_KERNEL);
	अगर (udc == शून्य)
		वापस -ENOMEM;

	udc->करोne = &release_करोne;
	udc->pdata = dev_get_platdata(&pdev->dev);
	spin_lock_init(&udc->lock);

	udc->dev = pdev;

	अगर (pdata->mode == MV_USB_MODE_OTG) अणु
		udc->transceiver = devm_usb_get_phy(&pdev->dev,
					USB_PHY_TYPE_USB2);
		अगर (IS_ERR(udc->transceiver)) अणु
			retval = PTR_ERR(udc->transceiver);

			अगर (retval == -ENXIO)
				वापस retval;

			udc->transceiver = शून्य;
			वापस -EPROBE_DEFER;
		पूर्ण
	पूर्ण

	/* udc only have one sysclk. */
	udc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(udc->clk))
		वापस PTR_ERR(udc->clk);

	r = platक्रमm_get_resource_byname(udc->dev, IORESOURCE_MEM, "capregs");
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "no I/O memory resource defined\n");
		वापस -ENODEV;
	पूर्ण

	udc->cap_regs = (काष्ठा mv_cap_regs __iomem *)
		devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (udc->cap_regs == शून्य) अणु
		dev_err(&pdev->dev, "failed to map I/O memory\n");
		वापस -EBUSY;
	पूर्ण

	r = platक्रमm_get_resource_byname(udc->dev, IORESOURCE_MEM, "phyregs");
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "no phy I/O memory resource defined\n");
		वापस -ENODEV;
	पूर्ण

	udc->phy_regs = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (udc->phy_regs == शून्य) अणु
		dev_err(&pdev->dev, "failed to map phy I/O memory\n");
		वापस -EBUSY;
	पूर्ण

	/* we will acces controller रेजिस्टर, so enable the clk */
	retval = mv_udc_enable_पूर्णांकernal(udc);
	अगर (retval)
		वापस retval;

	udc->op_regs =
		(काष्ठा mv_op_regs __iomem *)((अचिन्हित दीर्घ)udc->cap_regs
		+ (पढ़ोl(&udc->cap_regs->caplength_hciversion)
			& CAPLENGTH_MASK));
	udc->max_eps = पढ़ोl(&udc->cap_regs->dccparams) & DCCPARAMS_DEN_MASK;

	/*
	 * some platक्रमm will use usb to करोwnload image, it may not disconnect
	 * usb gadget beक्रमe loading kernel. So first stop udc here.
	 */
	udc_stop(udc);
	ग_लिखोl(0xFFFFFFFF, &udc->op_regs->usbsts);

	size = udc->max_eps * माप(काष्ठा mv_dqh) *2;
	size = (size + DQH_ALIGNMENT - 1) & ~(DQH_ALIGNMENT - 1);
	udc->ep_dqh = dma_alloc_coherent(&pdev->dev, size,
					&udc->ep_dqh_dma, GFP_KERNEL);

	अगर (udc->ep_dqh == शून्य) अणु
		dev_err(&pdev->dev, "allocate dQH memory failed\n");
		retval = -ENOMEM;
		जाओ err_disable_घड़ी;
	पूर्ण
	udc->ep_dqh_size = size;

	/* create dTD dma_pool resource */
	udc->dtd_pool = dma_pool_create("mv_dtd",
			&pdev->dev,
			माप(काष्ठा mv_dtd),
			DTD_ALIGNMENT,
			DMA_BOUNDARY);

	अगर (!udc->dtd_pool) अणु
		retval = -ENOMEM;
		जाओ err_मुक्त_dma;
	पूर्ण

	size = udc->max_eps * माप(काष्ठा mv_ep) *2;
	udc->eps = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (udc->eps == शून्य) अणु
		retval = -ENOMEM;
		जाओ err_destroy_dma;
	पूर्ण

	/* initialize ep0 status request काष्ठाure */
	udc->status_req = devm_kzalloc(&pdev->dev, माप(काष्ठा mv_req),
					GFP_KERNEL);
	अगर (!udc->status_req) अणु
		retval = -ENOMEM;
		जाओ err_destroy_dma;
	पूर्ण
	INIT_LIST_HEAD(&udc->status_req->queue);

	/* allocate a small amount of memory to get valid address */
	udc->status_req->req.buf = kzalloc(8, GFP_KERNEL);
	udc->status_req->req.dma = DMA_ADDR_INVALID;

	udc->resume_state = USB_STATE_NOTATTACHED;
	udc->usb_state = USB_STATE_POWERED;
	udc->ep0_dir = EP_सूची_OUT;
	udc->remote_wakeup = 0;

	r = platक्रमm_get_resource(udc->dev, IORESOURCE_IRQ, 0);
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "no IRQ resource defined\n");
		retval = -ENODEV;
		जाओ err_destroy_dma;
	पूर्ण
	udc->irq = r->start;
	अगर (devm_request_irq(&pdev->dev, udc->irq, mv_udc_irq,
		IRQF_SHARED, driver_name, udc)) अणु
		dev_err(&pdev->dev, "Request irq %d for UDC failed\n",
			udc->irq);
		retval = -ENODEV;
		जाओ err_destroy_dma;
	पूर्ण

	/* initialize gadget काष्ठाure */
	udc->gadget.ops = &mv_ops;	/* usb_gadget_ops */
	udc->gadget.ep0 = &udc->eps[0].ep;	/* gadget ep0 */
	INIT_LIST_HEAD(&udc->gadget.ep_list);	/* ep_list */
	udc->gadget.speed = USB_SPEED_UNKNOWN;	/* speed */
	udc->gadget.max_speed = USB_SPEED_HIGH;	/* support dual speed */

	/* the "gadget" असलtracts/भवizes the controller */
	udc->gadget.name = driver_name;		/* gadget name */

	eps_init(udc);

	/* VBUS detect: we can disable/enable घड़ी on demand.*/
	अगर (udc->transceiver)
		udc->घड़ी_gating = 1;
	अन्यथा अगर (pdata->vbus) अणु
		udc->घड़ी_gating = 1;
		retval = devm_request_thपढ़ोed_irq(&pdev->dev,
				pdata->vbus->irq, शून्य,
				mv_udc_vbus_irq, IRQF_ONESHOT, "vbus", udc);
		अगर (retval) अणु
			dev_info(&pdev->dev,
				"Can not request irq for VBUS, "
				"disable clock gating\n");
			udc->घड़ी_gating = 0;
		पूर्ण

		udc->qwork = create_singlethपढ़ो_workqueue("mv_udc_queue");
		अगर (!udc->qwork) अणु
			dev_err(&pdev->dev, "cannot create workqueue\n");
			retval = -ENOMEM;
			जाओ err_destroy_dma;
		पूर्ण

		INIT_WORK(&udc->vbus_work, mv_udc_vbus_work);
	पूर्ण

	/*
	 * When घड़ी gating is supported, we can disable clk and phy.
	 * If not, it means that VBUS detection is not supported, we
	 * have to enable vbus active all the समय to let controller work.
	 */
	अगर (udc->घड़ी_gating)
		mv_udc_disable_पूर्णांकernal(udc);
	अन्यथा
		udc->vbus_active = 1;

	retval = usb_add_gadget_udc_release(&pdev->dev, &udc->gadget,
			gadget_release);
	अगर (retval)
		जाओ err_create_workqueue;

	platक्रमm_set_drvdata(pdev, udc);
	dev_info(&pdev->dev, "successful probe UDC device %s clock gating.\n",
		udc->घड़ी_gating ? "with" : "without");

	वापस 0;

err_create_workqueue:
	अगर (udc->qwork)
		destroy_workqueue(udc->qwork);
err_destroy_dma:
	dma_pool_destroy(udc->dtd_pool);
err_मुक्त_dma:
	dma_मुक्त_coherent(&pdev->dev, udc->ep_dqh_size,
			udc->ep_dqh, udc->ep_dqh_dma);
err_disable_घड़ी:
	mv_udc_disable_पूर्णांकernal(udc);

	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mv_udc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mv_udc *udc;

	udc = dev_get_drvdata(dev);

	/* अगर OTG is enabled, the following will be करोne in OTG driver*/
	अगर (udc->transceiver)
		वापस 0;

	अगर (udc->pdata->vbus && udc->pdata->vbus->poll)
		अगर (udc->pdata->vbus->poll() == VBUS_HIGH) अणु
			dev_info(&udc->dev->dev, "USB cable is connected!\n");
			वापस -EAGAIN;
		पूर्ण

	/*
	 * only cable is unplugged, udc can suspend.
	 * So करो not care about घड़ी_gating == 1.
	 */
	अगर (!udc->घड़ी_gating) अणु
		udc_stop(udc);

		spin_lock_irq(&udc->lock);
		/* stop all usb activities */
		stop_activity(udc, udc->driver);
		spin_unlock_irq(&udc->lock);

		mv_udc_disable_पूर्णांकernal(udc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv_udc_resume(काष्ठा device *dev)
अणु
	काष्ठा mv_udc *udc;
	पूर्णांक retval;

	udc = dev_get_drvdata(dev);

	/* अगर OTG is enabled, the following will be करोne in OTG driver*/
	अगर (udc->transceiver)
		वापस 0;

	अगर (!udc->घड़ी_gating) अणु
		retval = mv_udc_enable_पूर्णांकernal(udc);
		अगर (retval)
			वापस retval;

		अगर (udc->driver && udc->softconnect) अणु
			udc_reset(udc);
			ep0_reset(udc);
			udc_start(udc);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mv_udc_pm_ops = अणु
	.suspend	= mv_udc_suspend,
	.resume		= mv_udc_resume,
पूर्ण;
#पूर्ण_अगर

अटल व्योम mv_udc_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_udc *udc;
	u32 mode;

	udc = platक्रमm_get_drvdata(pdev);
	/* reset controller mode to IDLE */
	mv_udc_enable(udc);
	mode = पढ़ोl(&udc->op_regs->usbmode);
	mode &= ~3;
	ग_लिखोl(mode, &udc->op_regs->usbmode);
	mv_udc_disable(udc);
पूर्ण

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.probe		= mv_udc_probe,
	.हटाओ		= mv_udc_हटाओ,
	.shutकरोwn	= mv_udc_shutकरोwn,
	.driver		= अणु
		.name	= "mv-udc",
#अगर_घोषित CONFIG_PM
		.pm	= &mv_udc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(udc_driver);
MODULE_ALIAS("platform:mv-udc");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Chao Xie <chao.xie@marvell.com>");
MODULE_LICENSE("GPL");
