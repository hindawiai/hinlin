<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * driver/usb/gadget/fsl_qe_udc.c
 *
 * Copyright (c) 2006-2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * 	Xie Xiaobo <X.Xie@मुक्तscale.com>
 * 	Li Yang <leoli@मुक्तscale.com>
 * 	Based on bareboard code from Shlomi Gridish.
 *
 * Description:
 * Freescle QE/CPM USB Pheripheral Controller Driver
 * The controller can be found on MPC8360, MPC8272, and etc.
 * MPC8360 Rev 1.1 may need QE mircocode update
 */

#अघोषित USB_TRACE

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <यंत्र/cpm.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/reg.h>
#समावेश "fsl_qe_udc.h"

#घोषणा DRIVER_DESC     "Freescale QE/CPM USB Device Controller driver"
#घोषणा DRIVER_AUTHOR   "Xie XiaoBo"
#घोषणा DRIVER_VERSION  "1.0"

#घोषणा DMA_ADDR_INVALID        (~(dma_addr_t)0)

अटल स्थिर अक्षर driver_name[] = "fsl_qe_udc";
अटल स्थिर अक्षर driver_desc[] = DRIVER_DESC;

/*ep name is important in gadget, it should obey the convention of ep_match()*/
अटल स्थिर अक्षर *स्थिर ep_name[] = अणु
	"ep0-control", /* everyone has ep0 */
	/* 3 configurable endpoपूर्णांकs */
	"ep1",
	"ep2",
	"ep3",
पूर्ण;

अटल स्थिर काष्ठा usb_endpoपूर्णांक_descriptor qe_ep0_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	0,
	.bmAttributes =		USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize =	USB_MAX_CTRL_PAYLOAD,
पूर्ण;

/********************************************************************
 *      Internal Used Function Start
********************************************************************/
/*-----------------------------------------------------------------
 * करोne() - retire a request; caller blocked irqs
 *--------------------------------------------------------------*/
अटल व्योम करोne(काष्ठा qe_ep *ep, काष्ठा qe_req *req, पूर्णांक status)
अणु
	काष्ठा qe_udc *udc = ep->udc;
	अचिन्हित अक्षर stopped = ep->stopped;

	/* the req->queue poपूर्णांकer is used by ep_queue() func, in which
	 * the request will be added पूर्णांकo a udc_ep->queue 'd tail
	 * so here the req will be dropped from the ep->queue
	 */
	list_del_init(&req->queue);

	/* req.status should be set as -EINPROGRESS in ep_queue() */
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	अगर (req->mapped) अणु
		dma_unmap_single(udc->gadget.dev.parent,
			req->req.dma, req->req.length,
			ep_is_in(ep)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		req->req.dma = DMA_ADDR_INVALID;
		req->mapped = 0;
	पूर्ण अन्यथा
		dma_sync_single_क्रम_cpu(udc->gadget.dev.parent,
			req->req.dma, req->req.length,
			ep_is_in(ep)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);

	अगर (status && (status != -ESHUTDOWN))
		dev_vdbg(udc->dev, "complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* करोn't modअगरy queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&udc->lock);

	usb_gadget_giveback_request(&ep->ep, &req->req);

	spin_lock(&udc->lock);

	ep->stopped = stopped;
पूर्ण

/*-----------------------------------------------------------------
 * nuke(): delete all requests related to this ep
 *--------------------------------------------------------------*/
अटल व्योम nuke(काष्ठा qe_ep *ep, पूर्णांक status)
अणु
	/* Whether this eq has request linked */
	जबतक (!list_empty(&ep->queue)) अणु
		काष्ठा qe_req *req = शून्य;
		req = list_entry(ep->queue.next, काष्ठा qe_req, queue);

		करोne(ep, req, status);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------*
 * USB and Endpoपूर्णांक manipulate process, include parameter and रेजिस्टर       *
 *---------------------------------------------------------------------------*/
/* @value: 1--set stall 0--clean stall */
अटल पूर्णांक qe_eprx_stall_change(काष्ठा qe_ep *ep, पूर्णांक value)
अणु
	u16 tem_usep;
	u8 epnum = ep->epnum;
	काष्ठा qe_udc *udc = ep->udc;

	tem_usep = in_be16(&udc->usb_regs->usb_usep[epnum]);
	tem_usep = tem_usep & ~USB_RHS_MASK;
	अगर (value == 1)
		tem_usep |= USB_RHS_STALL;
	अन्यथा अगर (ep->dir == USB_सूची_IN)
		tem_usep |= USB_RHS_IGNORE_OUT;

	out_be16(&udc->usb_regs->usb_usep[epnum], tem_usep);
	वापस 0;
पूर्ण

अटल पूर्णांक qe_eptx_stall_change(काष्ठा qe_ep *ep, पूर्णांक value)
अणु
	u16 tem_usep;
	u8 epnum = ep->epnum;
	काष्ठा qe_udc *udc = ep->udc;

	tem_usep = in_be16(&udc->usb_regs->usb_usep[epnum]);
	tem_usep = tem_usep & ~USB_THS_MASK;
	अगर (value == 1)
		tem_usep |= USB_THS_STALL;
	अन्यथा अगर (ep->dir == USB_सूची_OUT)
		tem_usep |= USB_THS_IGNORE_IN;

	out_be16(&udc->usb_regs->usb_usep[epnum], tem_usep);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep0_stall(काष्ठा qe_udc *udc)
अणु
	qe_eptx_stall_change(&udc->eps[0], 1);
	qe_eprx_stall_change(&udc->eps[0], 1);
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक qe_eprx_nack(काष्ठा qe_ep *ep)
अणु
	u8 epnum = ep->epnum;
	काष्ठा qe_udc *udc = ep->udc;

	अगर (ep->state == EP_STATE_IDLE) अणु
		/* Set the ep's nack */
		clrsetbits_be16(&udc->usb_regs->usb_usep[epnum],
				USB_RHS_MASK, USB_RHS_NACK);

		/* Mask Rx and Busy पूर्णांकerrupts */
		clrbits16(&udc->usb_regs->usb_usbmr,
				(USB_E_RXB_MASK | USB_E_BSY_MASK));

		ep->state = EP_STATE_NACK;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qe_eprx_normal(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_udc *udc = ep->udc;

	अगर (ep->state == EP_STATE_NACK) अणु
		clrsetbits_be16(&udc->usb_regs->usb_usep[ep->epnum],
				USB_RTHS_MASK, USB_THS_IGNORE_IN);

		/* Unmask RX पूर्णांकerrupts */
		out_be16(&udc->usb_regs->usb_usber,
				USB_E_BSY_MASK | USB_E_RXB_MASK);
		setbits16(&udc->usb_regs->usb_usbmr,
				(USB_E_RXB_MASK | USB_E_BSY_MASK));

		ep->state = EP_STATE_IDLE;
		ep->has_data = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_cmd_stoptx(काष्ठा qe_ep *ep)
अणु
	अगर (ep->udc->soc_type == PORT_CPM)
		cpm_command(CPM_USB_STOP_TX | (ep->epnum << CPM_USB_EP_SHIFT),
				CPM_USB_STOP_TX_OPCODE);
	अन्यथा
		qe_issue_cmd(QE_USB_STOP_TX, QE_CR_SUBBLOCK_USB,
				ep->epnum, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_cmd_restarttx(काष्ठा qe_ep *ep)
अणु
	अगर (ep->udc->soc_type == PORT_CPM)
		cpm_command(CPM_USB_RESTART_TX | (ep->epnum <<
				CPM_USB_EP_SHIFT), CPM_USB_RESTART_TX_OPCODE);
	अन्यथा
		qe_issue_cmd(QE_USB_RESTART_TX, QE_CR_SUBBLOCK_USB,
				ep->epnum, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_flushtxfअगरo(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_udc *udc = ep->udc;
	पूर्णांक i;

	i = (पूर्णांक)ep->epnum;

	qe_ep_cmd_stoptx(ep);
	out_8(&udc->usb_regs->usb_uscom,
		USB_CMD_FLUSH_FIFO | (USB_CMD_EP_MASK & (ep->epnum)));
	out_be16(&udc->ep_param[i]->tbptr, in_be16(&udc->ep_param[i]->tbase));
	out_be32(&udc->ep_param[i]->tstate, 0);
	out_be16(&udc->ep_param[i]->tbcnt, 0);

	ep->c_txbd = ep->txbase;
	ep->n_txbd = ep->txbase;
	qe_ep_cmd_restarttx(ep);
	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_filltxfअगरo(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_udc *udc = ep->udc;

	out_8(&udc->usb_regs->usb_uscom,
			USB_CMD_STR_FIFO | (USB_CMD_EP_MASK & (ep->epnum)));
	वापस 0;
पूर्ण

अटल पूर्णांक qe_epbds_reset(काष्ठा qe_udc *udc, पूर्णांक pipe_num)
अणु
	काष्ठा qe_ep *ep;
	u32 bdring_len;
	काष्ठा qe_bd __iomem *bd;
	पूर्णांक i;

	ep = &udc->eps[pipe_num];

	अगर (ep->dir == USB_सूची_OUT)
		bdring_len = USB_BDRING_LEN_RX;
	अन्यथा
		bdring_len = USB_BDRING_LEN;

	bd = ep->rxbase;
	क्रम (i = 0; i < (bdring_len - 1); i++) अणु
		out_be32((u32 __iomem *)bd, R_E | R_I);
		bd++;
	पूर्ण
	out_be32((u32 __iomem *)bd, R_E | R_I | R_W);

	bd = ep->txbase;
	क्रम (i = 0; i < USB_BDRING_LEN_TX - 1; i++) अणु
		out_be32(&bd->buf, 0);
		out_be32((u32 __iomem *)bd, 0);
		bd++;
	पूर्ण
	out_be32((u32 __iomem *)bd, T_W);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_reset(काष्ठा qe_udc *udc, पूर्णांक pipe_num)
अणु
	काष्ठा qe_ep *ep;
	u16 पंचांगpusep;

	ep = &udc->eps[pipe_num];
	पंचांगpusep = in_be16(&udc->usb_regs->usb_usep[pipe_num]);
	पंचांगpusep &= ~USB_RTHS_MASK;

	चयन (ep->dir) अणु
	हाल USB_सूची_BOTH:
		qe_ep_flushtxfअगरo(ep);
		अवरोध;
	हाल USB_सूची_OUT:
		पंचांगpusep |= USB_THS_IGNORE_IN;
		अवरोध;
	हाल USB_सूची_IN:
		qe_ep_flushtxfअगरo(ep);
		पंचांगpusep |= USB_RHS_IGNORE_OUT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	out_be16(&udc->usb_regs->usb_usep[pipe_num], पंचांगpusep);

	qe_epbds_reset(udc, pipe_num);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_toggledata01(काष्ठा qe_ep *ep)
अणु
	ep->data01 ^= 0x1;
	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_bd_init(काष्ठा qe_udc *udc, अचिन्हित अक्षर pipe_num)
अणु
	काष्ठा qe_ep *ep = &udc->eps[pipe_num];
	अचिन्हित दीर्घ पंचांगp_addr = 0;
	काष्ठा usb_ep_para __iomem *epparam;
	पूर्णांक i;
	काष्ठा qe_bd __iomem *bd;
	पूर्णांक bdring_len;

	अगर (ep->dir == USB_सूची_OUT)
		bdring_len = USB_BDRING_LEN_RX;
	अन्यथा
		bdring_len = USB_BDRING_LEN;

	epparam = udc->ep_param[pipe_num];
	/* alloc multi-ram क्रम BD rings and set the ep parameters */
	पंचांगp_addr = cpm_muram_alloc(माप(काष्ठा qe_bd) * (bdring_len +
				USB_BDRING_LEN_TX), QE_ALIGNMENT_OF_BD);
	अगर (IS_ERR_VALUE(पंचांगp_addr))
		वापस -ENOMEM;

	out_be16(&epparam->rbase, (u16)पंचांगp_addr);
	out_be16(&epparam->tbase, (u16)(पंचांगp_addr +
				(माप(काष्ठा qe_bd) * bdring_len)));

	out_be16(&epparam->rbptr, in_be16(&epparam->rbase));
	out_be16(&epparam->tbptr, in_be16(&epparam->tbase));

	ep->rxbase = cpm_muram_addr(पंचांगp_addr);
	ep->txbase = cpm_muram_addr(पंचांगp_addr + (माप(काष्ठा qe_bd)
				* bdring_len));
	ep->n_rxbd = ep->rxbase;
	ep->e_rxbd = ep->rxbase;
	ep->n_txbd = ep->txbase;
	ep->c_txbd = ep->txbase;
	ep->data01 = 0; /* data0 */

	/* Init TX and RX bds */
	bd = ep->rxbase;
	क्रम (i = 0; i < bdring_len - 1; i++) अणु
		out_be32(&bd->buf, 0);
		out_be32((u32 __iomem *)bd, 0);
		bd++;
	पूर्ण
	out_be32(&bd->buf, 0);
	out_be32((u32 __iomem *)bd, R_W);

	bd = ep->txbase;
	क्रम (i = 0; i < USB_BDRING_LEN_TX - 1; i++) अणु
		out_be32(&bd->buf, 0);
		out_be32((u32 __iomem *)bd, 0);
		bd++;
	पूर्ण
	out_be32(&bd->buf, 0);
	out_be32((u32 __iomem *)bd, T_W);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_rxbd_update(काष्ठा qe_ep *ep)
अणु
	अचिन्हित पूर्णांक size;
	पूर्णांक i;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा qe_bd __iomem *bd;
	अचिन्हित पूर्णांक bdring_len;

	अगर (ep->rxbase == शून्य)
		वापस -EINVAL;

	bd = ep->rxbase;

	ep->rxframe = kदो_स्मृति(माप(*ep->rxframe), GFP_ATOMIC);
	अगर (!ep->rxframe)
		वापस -ENOMEM;

	qe_frame_init(ep->rxframe);

	अगर (ep->dir == USB_सूची_OUT)
		bdring_len = USB_BDRING_LEN_RX;
	अन्यथा
		bdring_len = USB_BDRING_LEN;

	size = (ep->ep.maxpacket + USB_CRC_SIZE + 2) * (bdring_len + 1);
	ep->rxbuffer = kzalloc(size, GFP_ATOMIC);
	अगर (!ep->rxbuffer) अणु
		kमुक्त(ep->rxframe);
		वापस -ENOMEM;
	पूर्ण

	ep->rxbuf_d = virt_to_phys((व्योम *)ep->rxbuffer);
	अगर (ep->rxbuf_d == DMA_ADDR_INVALID) अणु
		ep->rxbuf_d = dma_map_single(ep->udc->gadget.dev.parent,
					ep->rxbuffer,
					size,
					DMA_FROM_DEVICE);
		ep->rxbufmap = 1;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_device(ep->udc->gadget.dev.parent,
					ep->rxbuf_d, size,
					DMA_FROM_DEVICE);
		ep->rxbufmap = 0;
	पूर्ण

	size = ep->ep.maxpacket + USB_CRC_SIZE + 2;
	पंचांगp = ep->rxbuf_d;
	पंचांगp = (u32)(((पंचांगp >> 2) << 2) + 4);

	क्रम (i = 0; i < bdring_len - 1; i++) अणु
		out_be32(&bd->buf, पंचांगp);
		out_be32((u32 __iomem *)bd, (R_E | R_I));
		पंचांगp = पंचांगp + size;
		bd++;
	पूर्ण
	out_be32(&bd->buf, पंचांगp);
	out_be32((u32 __iomem *)bd, (R_E | R_I | R_W));

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_रेजिस्टर_init(काष्ठा qe_udc *udc, अचिन्हित अक्षर pipe_num)
अणु
	काष्ठा qe_ep *ep = &udc->eps[pipe_num];
	काष्ठा usb_ep_para __iomem *epparam;
	u16 usep, logepnum;
	u16 पंचांगp;
	u8 rtfcr = 0;

	epparam = udc->ep_param[pipe_num];

	usep = 0;
	logepnum = (ep->ep.desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK);
	usep |= (logepnum << USB_EPNUM_SHIFT);

	चयन (ep->ep.desc->bmAttributes & 0x03) अणु
	हाल USB_ENDPOINT_XFER_BULK:
		usep |= USB_TRANS_BULK;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		usep |=  USB_TRANS_ISO;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		usep |= USB_TRANS_INT;
		अवरोध;
	शेष:
		usep |= USB_TRANS_CTR;
		अवरोध;
	पूर्ण

	चयन (ep->dir) अणु
	हाल USB_सूची_OUT:
		usep |= USB_THS_IGNORE_IN;
		अवरोध;
	हाल USB_सूची_IN:
		usep |= USB_RHS_IGNORE_OUT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	out_be16(&udc->usb_regs->usb_usep[pipe_num], usep);

	rtfcr = 0x30;
	out_8(&epparam->rbmr, rtfcr);
	out_8(&epparam->tbmr, rtfcr);

	पंचांगp = (u16)(ep->ep.maxpacket + USB_CRC_SIZE);
	/* MRBLR must be भागisble by 4 */
	पंचांगp = (u16)(((पंचांगp >> 2) << 2) + 4);
	out_be16(&epparam->mrblr, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_init(काष्ठा qe_udc *udc,
		      अचिन्हित अक्षर pipe_num,
		      स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा qe_ep *ep = &udc->eps[pipe_num];
	अचिन्हित दीर्घ flags;
	पूर्णांक reval = 0;
	u16 max = 0;

	max = usb_endpoपूर्णांक_maxp(desc);

	/* check the max package size validate क्रम this endpoपूर्णांक */
	/* Refer to USB2.0 spec table 9-13,
	*/
	अगर (pipe_num != 0) अणु
		चयन (desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) अणु
		हाल USB_ENDPOINT_XFER_BULK:
			अगर (म_माला(ep->ep.name, "-iso")
					|| म_माला(ep->ep.name, "-int"))
				जाओ en_करोne;
			चयन (udc->gadget.speed) अणु
			हाल USB_SPEED_HIGH:
			अगर ((max == 128) || (max == 256) || (max == 512))
				अवरोध;
			शेष:
				चयन (max) अणु
				हाल 4:
				हाल 8:
				हाल 16:
				हाल 32:
				हाल 64:
					अवरोध;
				शेष:
				हाल USB_SPEED_LOW:
					जाओ en_करोne;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल USB_ENDPOINT_XFER_INT:
			अगर (म_माला(ep->ep.name, "-iso"))	/* bulk is ok */
				जाओ en_करोne;
			चयन (udc->gadget.speed) अणु
			हाल USB_SPEED_HIGH:
				अगर (max <= 1024)
					अवरोध;
			हाल USB_SPEED_FULL:
				अगर (max <= 64)
					अवरोध;
			शेष:
				अगर (max <= 8)
					अवरोध;
				जाओ en_करोne;
			पूर्ण
			अवरोध;
		हाल USB_ENDPOINT_XFER_ISOC:
			अगर (म_माला(ep->ep.name, "-bulk")
				|| म_माला(ep->ep.name, "-int"))
				जाओ en_करोne;
			चयन (udc->gadget.speed) अणु
			हाल USB_SPEED_HIGH:
				अगर (max <= 1024)
					अवरोध;
			हाल USB_SPEED_FULL:
				अगर (max <= 1023)
					अवरोध;
			शेष:
				जाओ en_करोne;
			पूर्ण
			अवरोध;
		हाल USB_ENDPOINT_XFER_CONTROL:
			अगर (म_माला(ep->ep.name, "-iso")
				|| म_माला(ep->ep.name, "-int"))
				जाओ en_करोne;
			चयन (udc->gadget.speed) अणु
			हाल USB_SPEED_HIGH:
			हाल USB_SPEED_FULL:
				चयन (max) अणु
				हाल 1:
				हाल 2:
				हाल 4:
				हाल 8:
				हाल 16:
				हाल 32:
				हाल 64:
					अवरोध;
				शेष:
					जाओ en_करोne;
				पूर्ण
			हाल USB_SPEED_LOW:
				चयन (max) अणु
				हाल 1:
				हाल 2:
				हाल 4:
				हाल 8:
					अवरोध;
				शेष:
					जाओ en_करोne;
				पूर्ण
			शेष:
				जाओ en_करोne;
			पूर्ण
			अवरोध;

		शेष:
			जाओ en_करोne;
		पूर्ण
	पूर्ण /* अगर ep0*/

	spin_lock_irqsave(&udc->lock, flags);

	/* initialize ep काष्ठाure */
	ep->ep.maxpacket = max;
	ep->पंचांग = (u8)(desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK);
	ep->ep.desc = desc;
	ep->stopped = 0;
	ep->init = 1;

	अगर (pipe_num == 0) अणु
		ep->dir = USB_सूची_BOTH;
		udc->ep0_dir = USB_सूची_OUT;
		udc->ep0_state = WAIT_FOR_SETUP;
	पूर्ण अन्यथा	अणु
		चयन (desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) अणु
		हाल USB_सूची_OUT:
			ep->dir = USB_सूची_OUT;
			अवरोध;
		हाल USB_सूची_IN:
			ep->dir = USB_सूची_IN;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* hardware special operation */
	qe_ep_bd_init(udc, pipe_num);
	अगर ((ep->पंचांग == USBP_TM_CTL) || (ep->dir == USB_सूची_OUT)) अणु
		reval = qe_ep_rxbd_update(ep);
		अगर (reval)
			जाओ en_करोne1;
	पूर्ण

	अगर ((ep->पंचांग == USBP_TM_CTL) || (ep->dir == USB_सूची_IN)) अणु
		ep->txframe = kदो_स्मृति(माप(*ep->txframe), GFP_ATOMIC);
		अगर (!ep->txframe)
			जाओ en_करोne2;
		qe_frame_init(ep->txframe);
	पूर्ण

	qe_ep_रेजिस्टर_init(udc, pipe_num);

	/* Now HW will be NAKing transfers to that EP,
	 * until a buffer is queued to it. */
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
en_करोne2:
	kमुक्त(ep->rxbuffer);
	kमुक्त(ep->rxframe);
en_करोne1:
	spin_unlock_irqrestore(&udc->lock, flags);
en_करोne:
	dev_err(udc->dev, "failed to initialize %s\n", ep->ep.name);
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम qe_usb_enable(काष्ठा qe_udc *udc)
अणु
	setbits8(&udc->usb_regs->usb_usmod, USB_MODE_EN);
पूर्ण

अटल अंतरभूत व्योम qe_usb_disable(काष्ठा qe_udc *udc)
अणु
	clrbits8(&udc->usb_regs->usb_usmod, USB_MODE_EN);
पूर्ण

/*----------------------------------------------------------------------------*
 *		USB and EP basic manipulate function end		      *
 *----------------------------------------------------------------------------*/


/******************************************************************************
		UDC transmit and receive process
 ******************************************************************************/
अटल व्योम recycle_one_rxbd(काष्ठा qe_ep *ep)
अणु
	u32 bdstatus;

	bdstatus = in_be32((u32 __iomem *)ep->e_rxbd);
	bdstatus = R_I | R_E | (bdstatus & R_W);
	out_be32((u32 __iomem *)ep->e_rxbd, bdstatus);

	अगर (bdstatus & R_W)
		ep->e_rxbd = ep->rxbase;
	अन्यथा
		ep->e_rxbd++;
पूर्ण

अटल व्योम recycle_rxbds(काष्ठा qe_ep *ep, अचिन्हित अक्षर stopatnext)
अणु
	u32 bdstatus;
	काष्ठा qe_bd __iomem *bd, *nextbd;
	अचिन्हित अक्षर stop = 0;

	nextbd = ep->n_rxbd;
	bd = ep->e_rxbd;
	bdstatus = in_be32((u32 __iomem *)bd);

	जबतक (!(bdstatus & R_E) && !(bdstatus & BD_LENGTH_MASK) && !stop) अणु
		bdstatus = R_E | R_I | (bdstatus & R_W);
		out_be32((u32 __iomem *)bd, bdstatus);

		अगर (bdstatus & R_W)
			bd = ep->rxbase;
		अन्यथा
			bd++;

		bdstatus = in_be32((u32 __iomem *)bd);
		अगर (stopatnext && (bd == nextbd))
			stop = 1;
	पूर्ण

	ep->e_rxbd = bd;
पूर्ण

अटल व्योम ep_recycle_rxbds(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_bd __iomem *bd = ep->n_rxbd;
	u32 bdstatus;
	u8 epnum = ep->epnum;
	काष्ठा qe_udc *udc = ep->udc;

	bdstatus = in_be32((u32 __iomem *)bd);
	अगर (!(bdstatus & R_E) && !(bdstatus & BD_LENGTH_MASK)) अणु
		bd = ep->rxbase +
				((in_be16(&udc->ep_param[epnum]->rbptr) -
				  in_be16(&udc->ep_param[epnum]->rbase))
				 >> 3);
		bdstatus = in_be32((u32 __iomem *)bd);

		अगर (bdstatus & R_W)
			bd = ep->rxbase;
		अन्यथा
			bd++;

		ep->e_rxbd = bd;
		recycle_rxbds(ep, 0);
		ep->e_rxbd = ep->n_rxbd;
	पूर्ण अन्यथा
		recycle_rxbds(ep, 1);

	अगर (in_be16(&udc->usb_regs->usb_usber) & USB_E_BSY_MASK)
		out_be16(&udc->usb_regs->usb_usber, USB_E_BSY_MASK);

	अगर (ep->has_data <= 0 && (!list_empty(&ep->queue)))
		qe_eprx_normal(ep);

	ep->localnack = 0;
पूर्ण

अटल व्योम setup_received_handle(काष्ठा qe_udc *udc,
					काष्ठा usb_ctrlrequest *setup);
अटल पूर्णांक qe_ep_rxframe_handle(काष्ठा qe_ep *ep);
अटल व्योम ep0_req_complete(काष्ठा qe_udc *udc, काष्ठा qe_req *req);
/* when BD PID is setup, handle the packet */
अटल पूर्णांक ep0_setup_handle(काष्ठा qe_udc *udc)
अणु
	काष्ठा qe_ep *ep = &udc->eps[0];
	काष्ठा qe_frame *pframe;
	अचिन्हित पूर्णांक fsize;
	u8 *cp;

	pframe = ep->rxframe;
	अगर ((frame_get_info(pframe) & PID_SETUP)
			&& (udc->ep0_state == WAIT_FOR_SETUP)) अणु
		fsize = frame_get_length(pframe);
		अगर (unlikely(fsize != 8))
			वापस -EINVAL;
		cp = (u8 *)&udc->local_setup_buff;
		स_नकल(cp, pframe->data, fsize);
		ep->data01 = 1;

		/* handle the usb command base on the usb_ctrlrequest */
		setup_received_handle(udc, &udc->local_setup_buff);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qe_ep0_rx(काष्ठा qe_udc *udc)
अणु
	काष्ठा qe_ep *ep = &udc->eps[0];
	काष्ठा qe_frame *pframe;
	काष्ठा qe_bd __iomem *bd;
	u32 bdstatus, length;
	u32 vaddr;

	pframe = ep->rxframe;

	अगर (ep->dir == USB_सूची_IN) अणु
		dev_err(udc->dev, "ep0 not a control endpoint\n");
		वापस -EINVAL;
	पूर्ण

	bd = ep->n_rxbd;
	bdstatus = in_be32((u32 __iomem *)bd);
	length = bdstatus & BD_LENGTH_MASK;

	जबतक (!(bdstatus & R_E) && length) अणु
		अगर ((bdstatus & R_F) && (bdstatus & R_L)
			&& !(bdstatus & R_ERROR)) अणु
			अगर (length == USB_CRC_SIZE) अणु
				udc->ep0_state = WAIT_FOR_SETUP;
				dev_vdbg(udc->dev,
					"receive a ZLP in status phase\n");
			पूर्ण अन्यथा अणु
				qe_frame_clean(pframe);
				vaddr = (u32)phys_to_virt(in_be32(&bd->buf));
				frame_set_data(pframe, (u8 *)vaddr);
				frame_set_length(pframe,
						(length - USB_CRC_SIZE));
				frame_set_status(pframe, FRAME_OK);
				चयन (bdstatus & R_PID) अणु
				हाल R_PID_SETUP:
					frame_set_info(pframe, PID_SETUP);
					अवरोध;
				हाल R_PID_DATA1:
					frame_set_info(pframe, PID_DATA1);
					अवरोध;
				शेष:
					frame_set_info(pframe, PID_DATA0);
					अवरोध;
				पूर्ण

				अगर ((bdstatus & R_PID) == R_PID_SETUP)
					ep0_setup_handle(udc);
				अन्यथा
					qe_ep_rxframe_handle(ep);
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(udc->dev, "The receive frame with error!\n");
		पूर्ण

		/* note: करोn't clear the rxbd's buffer address */
		recycle_one_rxbd(ep);

		/* Get next BD */
		अगर (bdstatus & R_W)
			bd = ep->rxbase;
		अन्यथा
			bd++;

		bdstatus = in_be32((u32 __iomem *)bd);
		length = bdstatus & BD_LENGTH_MASK;

	पूर्ण

	ep->n_rxbd = bd;

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_rxframe_handle(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_frame *pframe;
	u8 framepid = 0;
	अचिन्हित पूर्णांक fsize;
	u8 *cp;
	काष्ठा qe_req *req;

	pframe = ep->rxframe;

	अगर (frame_get_info(pframe) & PID_DATA1)
		framepid = 0x1;

	अगर (framepid != ep->data01) अणु
		dev_err(ep->udc->dev, "the data01 error!\n");
		वापस -EIO;
	पूर्ण

	fsize = frame_get_length(pframe);
	अगर (list_empty(&ep->queue)) अणु
		dev_err(ep->udc->dev, "the %s have no requeue!\n", ep->name);
	पूर्ण अन्यथा अणु
		req = list_entry(ep->queue.next, काष्ठा qe_req, queue);

		cp = (u8 *)(req->req.buf) + req->req.actual;
		अगर (cp) अणु
			स_नकल(cp, pframe->data, fsize);
			req->req.actual += fsize;
			अगर ((fsize < ep->ep.maxpacket) ||
					(req->req.actual >= req->req.length)) अणु
				अगर (ep->epnum == 0)
					ep0_req_complete(ep->udc, req);
				अन्यथा
					करोne(ep, req, 0);
				अगर (list_empty(&ep->queue) && ep->epnum != 0)
					qe_eprx_nack(ep);
			पूर्ण
		पूर्ण
	पूर्ण

	qe_ep_toggledata01(ep);

	वापस 0;
पूर्ण

अटल व्योम ep_rx_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qe_udc *udc = from_tasklet(udc, t, rx_tasklet);
	काष्ठा qe_ep *ep;
	काष्ठा qe_frame *pframe;
	काष्ठा qe_bd __iomem *bd;
	अचिन्हित दीर्घ flags;
	u32 bdstatus, length;
	u32 vaddr, i;

	spin_lock_irqsave(&udc->lock, flags);

	क्रम (i = 1; i < USB_MAX_ENDPOINTS; i++) अणु
		ep = &udc->eps[i];

		अगर (ep->dir == USB_सूची_IN || ep->enable_tasklet == 0) अणु
			dev_dbg(udc->dev,
				"This is a transmit ep or disable tasklet!\n");
			जारी;
		पूर्ण

		pframe = ep->rxframe;
		bd = ep->n_rxbd;
		bdstatus = in_be32((u32 __iomem *)bd);
		length = bdstatus & BD_LENGTH_MASK;

		जबतक (!(bdstatus & R_E) && length) अणु
			अगर (list_empty(&ep->queue)) अणु
				qe_eprx_nack(ep);
				dev_dbg(udc->dev,
					"The rxep have noreq %d\n",
					ep->has_data);
				अवरोध;
			पूर्ण

			अगर ((bdstatus & R_F) && (bdstatus & R_L)
				&& !(bdstatus & R_ERROR)) अणु
				qe_frame_clean(pframe);
				vaddr = (u32)phys_to_virt(in_be32(&bd->buf));
				frame_set_data(pframe, (u8 *)vaddr);
				frame_set_length(pframe,
						(length - USB_CRC_SIZE));
				frame_set_status(pframe, FRAME_OK);
				चयन (bdstatus & R_PID) अणु
				हाल R_PID_DATA1:
					frame_set_info(pframe, PID_DATA1);
					अवरोध;
				हाल R_PID_SETUP:
					frame_set_info(pframe, PID_SETUP);
					अवरोध;
				शेष:
					frame_set_info(pframe, PID_DATA0);
					अवरोध;
				पूर्ण
				/* handle the rx frame */
				qe_ep_rxframe_handle(ep);
			पूर्ण अन्यथा अणु
				dev_err(udc->dev,
					"error in received frame\n");
			पूर्ण
			/* note: करोn't clear the rxbd's buffer address */
			/*clear the length */
			out_be32((u32 __iomem *)bd, bdstatus & BD_STATUS_MASK);
			ep->has_data--;
			अगर (!(ep->localnack))
				recycle_one_rxbd(ep);

			/* Get next BD */
			अगर (bdstatus & R_W)
				bd = ep->rxbase;
			अन्यथा
				bd++;

			bdstatus = in_be32((u32 __iomem *)bd);
			length = bdstatus & BD_LENGTH_MASK;
		पूर्ण

		ep->n_rxbd = bd;

		अगर (ep->localnack)
			ep_recycle_rxbds(ep);

		ep->enable_tasklet = 0;
	पूर्ण /* क्रम i=1 */

	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल पूर्णांक qe_ep_rx(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_udc *udc;
	काष्ठा qe_frame *pframe;
	काष्ठा qe_bd __iomem *bd;
	u16 swoffs, ucoffs, emptybds;

	udc = ep->udc;
	pframe = ep->rxframe;

	अगर (ep->dir == USB_सूची_IN) अणु
		dev_err(udc->dev, "transmit ep in rx function\n");
		वापस -EINVAL;
	पूर्ण

	bd = ep->n_rxbd;

	swoffs = (u16)(bd - ep->rxbase);
	ucoffs = (u16)((in_be16(&udc->ep_param[ep->epnum]->rbptr) -
			in_be16(&udc->ep_param[ep->epnum]->rbase)) >> 3);
	अगर (swoffs < ucoffs)
		emptybds = USB_BDRING_LEN_RX - ucoffs + swoffs;
	अन्यथा
		emptybds = swoffs - ucoffs;

	अगर (emptybds < MIN_EMPTY_BDS) अणु
		qe_eprx_nack(ep);
		ep->localnack = 1;
		dev_vdbg(udc->dev, "%d empty bds, send NACK\n", emptybds);
	पूर्ण
	ep->has_data = USB_BDRING_LEN_RX - emptybds;

	अगर (list_empty(&ep->queue)) अणु
		qe_eprx_nack(ep);
		dev_vdbg(udc->dev, "The rxep have no req queued with %d BDs\n",
				ep->has_data);
		वापस 0;
	पूर्ण

	tasklet_schedule(&udc->rx_tasklet);
	ep->enable_tasklet = 1;

	वापस 0;
पूर्ण

/* send data from a frame, no matter what tx_req */
अटल पूर्णांक qe_ep_tx(काष्ठा qe_ep *ep, काष्ठा qe_frame *frame)
अणु
	काष्ठा qe_udc *udc = ep->udc;
	काष्ठा qe_bd __iomem *bd;
	u16 saveusbmr;
	u32 bdstatus, pidmask;
	u32 paddr;

	अगर (ep->dir == USB_सूची_OUT) अणु
		dev_err(udc->dev, "receive ep passed to tx function\n");
		वापस -EINVAL;
	पूर्ण

	/* Disable the Tx पूर्णांकerrupt */
	saveusbmr = in_be16(&udc->usb_regs->usb_usbmr);
	out_be16(&udc->usb_regs->usb_usbmr,
			saveusbmr & ~(USB_E_TXB_MASK | USB_E_TXE_MASK));

	bd = ep->n_txbd;
	bdstatus = in_be32((u32 __iomem *)bd);

	अगर (!(bdstatus & (T_R | BD_LENGTH_MASK))) अणु
		अगर (frame_get_length(frame) == 0) अणु
			frame_set_data(frame, udc->nullbuf);
			frame_set_length(frame, 2);
			frame->info |= (ZLP | NO_CRC);
			dev_vdbg(udc->dev, "the frame size = 0\n");
		पूर्ण
		paddr = virt_to_phys((व्योम *)frame->data);
		out_be32(&bd->buf, paddr);
		bdstatus = (bdstatus&T_W);
		अगर (!(frame_get_info(frame) & NO_CRC))
			bdstatus |= T_R | T_I | T_L | T_TC
					| frame_get_length(frame);
		अन्यथा
			bdstatus |= T_R | T_I | T_L | frame_get_length(frame);

		/* अगर the packet is a ZLP in status phase */
		अगर ((ep->epnum == 0) && (udc->ep0_state == DATA_STATE_NEED_ZLP))
			ep->data01 = 0x1;

		अगर (ep->data01) अणु
			pidmask = T_PID_DATA1;
			frame->info |= PID_DATA1;
		पूर्ण अन्यथा अणु
			pidmask = T_PID_DATA0;
			frame->info |= PID_DATA0;
		पूर्ण
		bdstatus |= T_CNF;
		bdstatus |= pidmask;
		out_be32((u32 __iomem *)bd, bdstatus);
		qe_ep_filltxfअगरo(ep);

		/* enable the TX पूर्णांकerrupt */
		out_be16(&udc->usb_regs->usb_usbmr, saveusbmr);

		qe_ep_toggledata01(ep);
		अगर (bdstatus & T_W)
			ep->n_txbd = ep->txbase;
		अन्यथा
			ep->n_txbd++;

		वापस 0;
	पूर्ण अन्यथा अणु
		out_be16(&udc->usb_regs->usb_usbmr, saveusbmr);
		dev_vdbg(udc->dev, "The tx bd is not ready!\n");
		वापस -EBUSY;
	पूर्ण
पूर्ण

/* when a bd was transmitted, the function can
 * handle the tx_req, not include ep0           */
अटल पूर्णांक txcomplete(काष्ठा qe_ep *ep, अचिन्हित अक्षर restart)
अणु
	अगर (ep->tx_req != शून्य) अणु
		काष्ठा qe_req *req = ep->tx_req;
		अचिन्हित zlp = 0, last_len = 0;

		last_len = min_t(अचिन्हित, req->req.length - ep->sent,
				ep->ep.maxpacket);

		अगर (!restart) अणु
			पूर्णांक asent = ep->last;
			ep->sent += asent;
			ep->last -= asent;
		पूर्ण अन्यथा अणु
			ep->last = 0;
		पूर्ण

		/* zlp needed when req->re.zero is set */
		अगर (req->req.zero) अणु
			अगर (last_len == 0 ||
				(req->req.length % ep->ep.maxpacket) != 0)
				zlp = 0;
			अन्यथा
				zlp = 1;
		पूर्ण अन्यथा
			zlp = 0;

		/* a request alपढ़ोy were transmitted completely */
		अगर (((ep->tx_req->req.length - ep->sent) <= 0) && !zlp) अणु
			करोne(ep, ep->tx_req, 0);
			ep->tx_req = शून्य;
			ep->last = 0;
			ep->sent = 0;
		पूर्ण
	पूर्ण

	/* we should gain a new tx_req fot this endpoपूर्णांक */
	अगर (ep->tx_req == शून्य) अणु
		अगर (!list_empty(&ep->queue)) अणु
			ep->tx_req = list_entry(ep->queue.next,	काष्ठा qe_req,
							queue);
			ep->last = 0;
			ep->sent = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* give a frame and a tx_req, send some data */
अटल पूर्णांक qe_usb_senddata(काष्ठा qe_ep *ep, काष्ठा qe_frame *frame)
अणु
	अचिन्हित पूर्णांक size;
	u8 *buf;

	qe_frame_clean(frame);
	size = min_t(u32, (ep->tx_req->req.length - ep->sent),
				ep->ep.maxpacket);
	buf = (u8 *)ep->tx_req->req.buf + ep->sent;
	अगर (buf && size) अणु
		ep->last = size;
		ep->tx_req->req.actual += size;
		frame_set_data(frame, buf);
		frame_set_length(frame, size);
		frame_set_status(frame, FRAME_OK);
		frame_set_info(frame, 0);
		वापस qe_ep_tx(ep, frame);
	पूर्ण
	वापस -EIO;
पूर्ण

/* give a frame काष्ठा,send a ZLP */
अटल पूर्णांक sendnulldata(काष्ठा qe_ep *ep, काष्ठा qe_frame *frame, uपूर्णांक inक्रम)
अणु
	काष्ठा qe_udc *udc = ep->udc;

	अगर (frame == शून्य)
		वापस -ENODEV;

	qe_frame_clean(frame);
	frame_set_data(frame, (u8 *)udc->nullbuf);
	frame_set_length(frame, 2);
	frame_set_status(frame, FRAME_OK);
	frame_set_info(frame, (ZLP | NO_CRC | inक्रम));

	वापस qe_ep_tx(ep, frame);
पूर्ण

अटल पूर्णांक frame_create_tx(काष्ठा qe_ep *ep, काष्ठा qe_frame *frame)
अणु
	काष्ठा qe_req *req = ep->tx_req;
	पूर्णांक reval;

	अगर (req == शून्य)
		वापस -ENODEV;

	अगर ((req->req.length - ep->sent) > 0)
		reval = qe_usb_senddata(ep, frame);
	अन्यथा
		reval = sendnulldata(ep, frame, 0);

	वापस reval;
पूर्ण

/* अगर direction is सूची_IN, the status is Device->Host
 * अगर direction is सूची_OUT, the status transaction is Device<-Host
 * in status phase, udc create a request and gain status */
अटल पूर्णांक ep0_prime_status(काष्ठा qe_udc *udc, पूर्णांक direction)
अणु

	काष्ठा qe_ep *ep = &udc->eps[0];

	अगर (direction == USB_सूची_IN) अणु
		udc->ep0_state = DATA_STATE_NEED_ZLP;
		udc->ep0_dir = USB_सूची_IN;
		sendnulldata(ep, ep->txframe, SETUP_STATUS | NO_REQ);
	पूर्ण अन्यथा अणु
		udc->ep0_dir = USB_सूची_OUT;
		udc->ep0_state = WAIT_FOR_OUT_STATUS;
	पूर्ण

	वापस 0;
पूर्ण

/* a request complete in ep0, whether gadget request or udc request */
अटल व्योम ep0_req_complete(काष्ठा qe_udc *udc, काष्ठा qe_req *req)
अणु
	काष्ठा qe_ep *ep = &udc->eps[0];
	/* because usb and ep's status alपढ़ोy been set in ch9setaddress() */

	चयन (udc->ep0_state) अणु
	हाल DATA_STATE_XMIT:
		करोne(ep, req, 0);
		/* receive status phase */
		अगर (ep0_prime_status(udc, USB_सूची_OUT))
			qe_ep0_stall(udc);
		अवरोध;

	हाल DATA_STATE_NEED_ZLP:
		करोne(ep, req, 0);
		udc->ep0_state = WAIT_FOR_SETUP;
		अवरोध;

	हाल DATA_STATE_RECV:
		करोne(ep, req, 0);
		/* send status phase */
		अगर (ep0_prime_status(udc, USB_सूची_IN))
			qe_ep0_stall(udc);
		अवरोध;

	हाल WAIT_FOR_OUT_STATUS:
		करोne(ep, req, 0);
		udc->ep0_state = WAIT_FOR_SETUP;
		अवरोध;

	हाल WAIT_FOR_SETUP:
		dev_vdbg(udc->dev, "Unexpected interrupt\n");
		अवरोध;

	शेष:
		qe_ep0_stall(udc);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ep0_txcomplete(काष्ठा qe_ep *ep, अचिन्हित अक्षर restart)
अणु
	काष्ठा qe_req *tx_req = शून्य;
	काष्ठा qe_frame *frame = ep->txframe;

	अगर ((frame_get_info(frame) & (ZLP | NO_REQ)) == (ZLP | NO_REQ)) अणु
		अगर (!restart)
			ep->udc->ep0_state = WAIT_FOR_SETUP;
		अन्यथा
			sendnulldata(ep, ep->txframe, SETUP_STATUS | NO_REQ);
		वापस 0;
	पूर्ण

	tx_req = ep->tx_req;
	अगर (tx_req != शून्य) अणु
		अगर (!restart) अणु
			पूर्णांक asent = ep->last;
			ep->sent += asent;
			ep->last -= asent;
		पूर्ण अन्यथा अणु
			ep->last = 0;
		पूर्ण

		/* a request alपढ़ोy were transmitted completely */
		अगर ((ep->tx_req->req.length - ep->sent) <= 0) अणु
			ep->tx_req->req.actual = (अचिन्हित पूर्णांक)ep->sent;
			ep0_req_complete(ep->udc, ep->tx_req);
			ep->tx_req = शून्य;
			ep->last = 0;
			ep->sent = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_vdbg(ep->udc->dev, "the ep0_controller have no req\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ep0_txframe_handle(काष्ठा qe_ep *ep)
अणु
	/* अगर have error, transmit again */
	अगर (frame_get_status(ep->txframe) & FRAME_ERROR) अणु
		qe_ep_flushtxfअगरo(ep);
		dev_vdbg(ep->udc->dev, "The EP0 transmit data have error!\n");
		अगर (frame_get_info(ep->txframe) & PID_DATA0)
			ep->data01 = 0;
		अन्यथा
			ep->data01 = 1;

		ep0_txcomplete(ep, 1);
	पूर्ण अन्यथा
		ep0_txcomplete(ep, 0);

	frame_create_tx(ep, ep->txframe);
	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep0_txconf(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_bd __iomem *bd;
	काष्ठा qe_frame *pframe;
	u32 bdstatus;

	bd = ep->c_txbd;
	bdstatus = in_be32((u32 __iomem *)bd);
	जबतक (!(bdstatus & T_R) && (bdstatus & ~T_W)) अणु
		pframe = ep->txframe;

		/* clear and recycle the BD */
		out_be32((u32 __iomem *)bd, bdstatus & T_W);
		out_be32(&bd->buf, 0);
		अगर (bdstatus & T_W)
			ep->c_txbd = ep->txbase;
		अन्यथा
			ep->c_txbd++;

		अगर (ep->c_txbd == ep->n_txbd) अणु
			अगर (bdstatus & DEVICE_T_ERROR) अणु
				frame_set_status(pframe, FRAME_ERROR);
				अगर (bdstatus & T_TO)
					pframe->status |= TX_ER_TIMEOUT;
				अगर (bdstatus & T_UN)
					pframe->status |= TX_ER_UNDERUN;
			पूर्ण
			ep0_txframe_handle(ep);
		पूर्ण

		bd = ep->c_txbd;
		bdstatus = in_be32((u32 __iomem *)bd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ep_txframe_handle(काष्ठा qe_ep *ep)
अणु
	अगर (frame_get_status(ep->txframe) & FRAME_ERROR) अणु
		qe_ep_flushtxfअगरo(ep);
		dev_vdbg(ep->udc->dev, "The EP0 transmit data have error!\n");
		अगर (frame_get_info(ep->txframe) & PID_DATA0)
			ep->data01 = 0;
		अन्यथा
			ep->data01 = 1;

		txcomplete(ep, 1);
	पूर्ण अन्यथा
		txcomplete(ep, 0);

	frame_create_tx(ep, ep->txframe); /* send the data */
	वापस 0;
पूर्ण

/* confirm the alपढ़ोy trainsmited bd */
अटल पूर्णांक qe_ep_txconf(काष्ठा qe_ep *ep)
अणु
	काष्ठा qe_bd __iomem *bd;
	काष्ठा qe_frame *pframe = शून्य;
	u32 bdstatus;
	अचिन्हित अक्षर अवरोधonrxपूर्णांकerrupt = 0;

	bd = ep->c_txbd;
	bdstatus = in_be32((u32 __iomem *)bd);
	जबतक (!(bdstatus & T_R) && (bdstatus & ~T_W)) अणु
		pframe = ep->txframe;
		अगर (bdstatus & DEVICE_T_ERROR) अणु
			frame_set_status(pframe, FRAME_ERROR);
			अगर (bdstatus & T_TO)
				pframe->status |= TX_ER_TIMEOUT;
			अगर (bdstatus & T_UN)
				pframe->status |= TX_ER_UNDERUN;
		पूर्ण

		/* clear and recycle the BD */
		out_be32((u32 __iomem *)bd, bdstatus & T_W);
		out_be32(&bd->buf, 0);
		अगर (bdstatus & T_W)
			ep->c_txbd = ep->txbase;
		अन्यथा
			ep->c_txbd++;

		/* handle the tx frame */
		ep_txframe_handle(ep);
		bd = ep->c_txbd;
		bdstatus = in_be32((u32 __iomem *)bd);
	पूर्ण
	अगर (अवरोधonrxपूर्णांकerrupt)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

/* Add a request in queue, and try to transmit a packet */
अटल पूर्णांक ep_req_send(काष्ठा qe_ep *ep, काष्ठा qe_req *req)
अणु
	पूर्णांक reval = 0;

	अगर (ep->tx_req == शून्य) अणु
		ep->sent = 0;
		ep->last = 0;
		txcomplete(ep, 0); /* can gain a new tx_req */
		reval = frame_create_tx(ep, ep->txframe);
	पूर्ण
	वापस reval;
पूर्ण

/* Maybe this is a good ideal */
अटल पूर्णांक ep_req_rx(काष्ठा qe_ep *ep, काष्ठा qe_req *req)
अणु
	काष्ठा qe_udc *udc = ep->udc;
	काष्ठा qe_frame *pframe = शून्य;
	काष्ठा qe_bd __iomem *bd;
	u32 bdstatus, length;
	u32 vaddr, fsize;
	u8 *cp;
	u8 finish_req = 0;
	u8 framepid;

	अगर (list_empty(&ep->queue)) अणु
		dev_vdbg(udc->dev, "the req already finish!\n");
		वापस 0;
	पूर्ण
	pframe = ep->rxframe;

	bd = ep->n_rxbd;
	bdstatus = in_be32((u32 __iomem *)bd);
	length = bdstatus & BD_LENGTH_MASK;

	जबतक (!(bdstatus & R_E) && length) अणु
		अगर (finish_req)
			अवरोध;
		अगर ((bdstatus & R_F) && (bdstatus & R_L)
					&& !(bdstatus & R_ERROR)) अणु
			qe_frame_clean(pframe);
			vaddr = (u32)phys_to_virt(in_be32(&bd->buf));
			frame_set_data(pframe, (u8 *)vaddr);
			frame_set_length(pframe, (length - USB_CRC_SIZE));
			frame_set_status(pframe, FRAME_OK);
			चयन (bdstatus & R_PID) अणु
			हाल R_PID_DATA1:
				frame_set_info(pframe, PID_DATA1); अवरोध;
			शेष:
				frame_set_info(pframe, PID_DATA0); अवरोध;
			पूर्ण
			/* handle the rx frame */

			अगर (frame_get_info(pframe) & PID_DATA1)
				framepid = 0x1;
			अन्यथा
				framepid = 0;

			अगर (framepid != ep->data01) अणु
				dev_vdbg(udc->dev, "the data01 error!\n");
			पूर्ण अन्यथा अणु
				fsize = frame_get_length(pframe);

				cp = (u8 *)(req->req.buf) + req->req.actual;
				अगर (cp) अणु
					स_नकल(cp, pframe->data, fsize);
					req->req.actual += fsize;
					अगर ((fsize < ep->ep.maxpacket)
						|| (req->req.actual >=
							req->req.length)) अणु
						finish_req = 1;
						करोne(ep, req, 0);
						अगर (list_empty(&ep->queue))
							qe_eprx_nack(ep);
					पूर्ण
				पूर्ण
				qe_ep_toggledata01(ep);
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(udc->dev, "The receive frame with error!\n");
		पूर्ण

		/* note: करोn't clear the rxbd's buffer address *
		 * only Clear the length */
		out_be32((u32 __iomem *)bd, (bdstatus & BD_STATUS_MASK));
		ep->has_data--;

		/* Get next BD */
		अगर (bdstatus & R_W)
			bd = ep->rxbase;
		अन्यथा
			bd++;

		bdstatus = in_be32((u32 __iomem *)bd);
		length = bdstatus & BD_LENGTH_MASK;
	पूर्ण

	ep->n_rxbd = bd;
	ep_recycle_rxbds(ep);

	वापस 0;
पूर्ण

/* only add the request in queue */
अटल पूर्णांक ep_req_receive(काष्ठा qe_ep *ep, काष्ठा qe_req *req)
अणु
	अगर (ep->state == EP_STATE_NACK) अणु
		अगर (ep->has_data <= 0) अणु
			/* Enable rx and unmask rx पूर्णांकerrupt */
			qe_eprx_normal(ep);
		पूर्ण अन्यथा अणु
			/* Copy the exist BD data */
			ep_req_rx(ep, req);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/********************************************************************
	Internal Used Function End
********************************************************************/

/*-----------------------------------------------------------------------
	Endpoपूर्णांक Management Functions For Gadget
 -----------------------------------------------------------------------*/
अटल पूर्णांक qe_ep_enable(काष्ठा usb_ep *_ep,
			 स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा qe_udc *udc;
	काष्ठा qe_ep *ep;
	पूर्णांक retval = 0;
	अचिन्हित अक्षर epnum;

	ep = container_of(_ep, काष्ठा qe_ep, ep);

	/* catch various bogus parameters */
	अगर (!_ep || !desc || _ep->name == ep_name[0] ||
			(desc->bDescriptorType != USB_DT_ENDPOINT))
		वापस -EINVAL;

	udc = ep->udc;
	अगर (!udc->driver || (udc->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;

	epnum = (u8)desc->bEndpoपूर्णांकAddress & 0xF;

	retval = qe_ep_init(udc, epnum, desc);
	अगर (retval != 0) अणु
		cpm_muram_मुक्त(cpm_muram_offset(ep->rxbase));
		dev_dbg(udc->dev, "enable ep%d failed\n", ep->epnum);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(udc->dev, "enable ep%d successful\n", ep->epnum);
	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा qe_udc *udc;
	काष्ठा qe_ep *ep;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक size;

	ep = container_of(_ep, काष्ठा qe_ep, ep);
	udc = ep->udc;

	अगर (!_ep || !ep->ep.desc) अणु
		dev_dbg(udc->dev, "%s not enabled\n", _ep ? ep->ep.name : शून्य);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);
	/* Nuke all pending requests (करोes flush) */
	nuke(ep, -ESHUTDOWN);
	ep->ep.desc = शून्य;
	ep->stopped = 1;
	ep->tx_req = शून्य;
	qe_ep_reset(udc, ep->epnum);
	spin_unlock_irqrestore(&udc->lock, flags);

	cpm_muram_मुक्त(cpm_muram_offset(ep->rxbase));

	अगर (ep->dir == USB_सूची_OUT)
		size = (ep->ep.maxpacket + USB_CRC_SIZE + 2) *
				(USB_BDRING_LEN_RX + 1);
	अन्यथा
		size = (ep->ep.maxpacket + USB_CRC_SIZE + 2) *
				(USB_BDRING_LEN + 1);

	अगर (ep->dir != USB_सूची_IN) अणु
		kमुक्त(ep->rxframe);
		अगर (ep->rxbufmap) अणु
			dma_unmap_single(udc->gadget.dev.parent,
					ep->rxbuf_d, size,
					DMA_FROM_DEVICE);
			ep->rxbuf_d = DMA_ADDR_INVALID;
		पूर्ण अन्यथा अणु
			dma_sync_single_क्रम_cpu(
					udc->gadget.dev.parent,
					ep->rxbuf_d, size,
					DMA_FROM_DEVICE);
		पूर्ण
		kमुक्त(ep->rxbuffer);
	पूर्ण

	अगर (ep->dir != USB_सूची_OUT)
		kमुक्त(ep->txframe);

	dev_dbg(udc->dev, "disabled %s OK\n", _ep->name);
	वापस 0;
पूर्ण

अटल काष्ठा usb_request *qe_alloc_request(काष्ठा usb_ep *_ep,	gfp_t gfp_flags)
अणु
	काष्ठा qe_req *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	req->req.dma = DMA_ADDR_INVALID;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम qe_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा qe_req *req;

	req = container_of(_req, काष्ठा qe_req, req);

	अगर (_req)
		kमुक्त(req);
पूर्ण

अटल पूर्णांक __qe_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा qe_ep *ep = container_of(_ep, काष्ठा qe_ep, ep);
	काष्ठा qe_req *req = container_of(_req, काष्ठा qe_req, req);
	काष्ठा qe_udc *udc;
	पूर्णांक reval;

	udc = ep->udc;
	/* catch various bogus parameters */
	अगर (!_req || !req->req.complete || !req->req.buf
			|| !list_empty(&req->queue)) अणु
		dev_dbg(udc->dev, "bad params\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!_ep || (!ep->ep.desc && ep_index(ep))) अणु
		dev_dbg(udc->dev, "bad ep\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	req->ep = ep;

	/* map भव address to hardware */
	अगर (req->req.dma == DMA_ADDR_INVALID) अणु
		req->req.dma = dma_map_single(ep->udc->gadget.dev.parent,
					req->req.buf,
					req->req.length,
					ep_is_in(ep)
					? DMA_TO_DEVICE :
					DMA_FROM_DEVICE);
		req->mapped = 1;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_device(ep->udc->gadget.dev.parent,
					req->req.dma, req->req.length,
					ep_is_in(ep)
					? DMA_TO_DEVICE :
					DMA_FROM_DEVICE);
		req->mapped = 0;
	पूर्ण

	req->req.status = -EINPROGRESS;
	req->req.actual = 0;

	list_add_tail(&req->queue, &ep->queue);
	dev_vdbg(udc->dev, "gadget have request in %s! %d\n",
			ep->name, req->req.length);

	/* push the request to device */
	अगर (ep_is_in(ep))
		reval = ep_req_send(ep, req);

	/* EP0 */
	अगर (ep_index(ep) == 0 && req->req.length > 0) अणु
		अगर (ep_is_in(ep))
			udc->ep0_state = DATA_STATE_XMIT;
		अन्यथा
			udc->ep0_state = DATA_STATE_RECV;
	पूर्ण

	अगर (ep->dir == USB_सूची_OUT)
		reval = ep_req_receive(ep, req);

	वापस 0;
पूर्ण

/* queues (submits) an I/O request to an endpoपूर्णांक */
अटल पूर्णांक qe_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
		       gfp_t gfp_flags)
अणु
	काष्ठा qe_ep *ep = container_of(_ep, काष्ठा qe_ep, ep);
	काष्ठा qe_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&udc->lock, flags);
	ret = __qe_ep_queue(_ep, _req);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस ret;
पूर्ण

/* dequeues (cancels, unlinks) an I/O request from an endpoपूर्णांक */
अटल पूर्णांक qe_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा qe_ep *ep = container_of(_ep, काष्ठा qe_ep, ep);
	काष्ठा qe_req *req;
	अचिन्हित दीर्घ flags;

	अगर (!_ep || !_req)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->udc->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण

	अगर (&req->req != _req) अणु
		spin_unlock_irqrestore(&ep->udc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	करोne(ep, req, -ECONNRESET);

	spin_unlock_irqrestore(&ep->udc->lock, flags);
	वापस 0;
पूर्ण

/*-----------------------------------------------------------------
 * modअगरy the endpoपूर्णांक halt feature
 * @ep: the non-isochronous endpoपूर्णांक being stalled
 * @value: 1--set halt  0--clear halt
 * Returns zero, or a negative error code.
*----------------------------------------------------------------*/
अटल पूर्णांक qe_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा qe_ep *ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = -EOPNOTSUPP;
	काष्ठा qe_udc *udc;

	ep = container_of(_ep, काष्ठा qe_ep, ep);
	अगर (!_ep || !ep->ep.desc) अणु
		status = -EINVAL;
		जाओ out;
	पूर्ण

	udc = ep->udc;
	/* Attempt to halt IN ep will fail अगर any transfer requests
	 * are still queue */
	अगर (value && ep_is_in(ep) && !list_empty(&ep->queue)) अणु
		status = -EAGAIN;
		जाओ out;
	पूर्ण

	status = 0;
	spin_lock_irqsave(&ep->udc->lock, flags);
	qe_eptx_stall_change(ep, value);
	qe_eprx_stall_change(ep, value);
	spin_unlock_irqrestore(&ep->udc->lock, flags);

	अगर (ep->epnum == 0) अणु
		udc->ep0_state = WAIT_FOR_SETUP;
		udc->ep0_dir = 0;
	पूर्ण

	/* set data toggle to DATA0 on clear halt */
	अगर (value == 0)
		ep->data01 = 0;
out:
	dev_vdbg(udc->dev, "%s %s halt stat %d\n", ep->ep.name,
			value ?  "set" : "clear", status);

	वापस status;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops qe_ep_ops = अणु
	.enable = qe_ep_enable,
	.disable = qe_ep_disable,

	.alloc_request = qe_alloc_request,
	.मुक्त_request = qe_मुक्त_request,

	.queue = qe_ep_queue,
	.dequeue = qe_ep_dequeue,

	.set_halt = qe_ep_set_halt,
पूर्ण;

/*------------------------------------------------------------------------
	Gadget Driver Layer Operations
 ------------------------------------------------------------------------*/

/* Get the current frame number */
अटल पूर्णांक qe_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा qe_udc *udc = container_of(gadget, काष्ठा qe_udc, gadget);
	u16 पंचांगp;

	पंचांगp = in_be16(&udc->usb_param->frame_n);
	अगर (पंचांगp & 0x8000)
		वापस पंचांगp & 0x07ff;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fsl_qe_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक fsl_qe_stop(काष्ठा usb_gadget *gadget);

/* defined in usb_gadget.h */
अटल स्थिर काष्ठा usb_gadget_ops qe_gadget_ops = अणु
	.get_frame = qe_get_frame,
	.udc_start = fsl_qe_start,
	.udc_stop = fsl_qe_stop,
पूर्ण;

/*-------------------------------------------------------------------------
	USB ep0 Setup process in BUS Enumeration
 -------------------------------------------------------------------------*/
अटल पूर्णांक udc_reset_ep_queue(काष्ठा qe_udc *udc, u8 pipe)
अणु
	काष्ठा qe_ep *ep = &udc->eps[pipe];

	nuke(ep, -ECONNRESET);
	ep->tx_req = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक reset_queues(काष्ठा qe_udc *udc)
अणु
	u8 pipe;

	क्रम (pipe = 0; pipe < USB_MAX_ENDPOINTS; pipe++)
		udc_reset_ep_queue(udc, pipe);

	/* report disconnect; the driver is alपढ़ोy quiesced */
	spin_unlock(&udc->lock);
	usb_gadget_udc_reset(&udc->gadget, udc->driver);
	spin_lock(&udc->lock);

	वापस 0;
पूर्ण

अटल व्योम ch9setaddress(काष्ठा qe_udc *udc, u16 value, u16 index,
			u16 length)
अणु
	/* Save the new address to device काष्ठा */
	udc->device_address = (u8) value;
	/* Update usb state */
	udc->usb_state = USB_STATE_ADDRESS;

	/* Status phase , send a ZLP */
	अगर (ep0_prime_status(udc, USB_सूची_IN))
		qe_ep0_stall(udc);
पूर्ण

अटल व्योम ownercomplete(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा qe_req *req = container_of(_req, काष्ठा qe_req, req);

	req->req.buf = शून्य;
	kमुक्त(req);
पूर्ण

अटल व्योम ch9माला_लोtatus(काष्ठा qe_udc *udc, u8 request_type, u16 value,
			u16 index, u16 length)
अणु
	u16 usb_status = 0;
	काष्ठा qe_req *req;
	काष्ठा qe_ep *ep;
	पूर्णांक status = 0;

	ep = &udc->eps[0];
	अगर ((request_type & USB_RECIP_MASK) == USB_RECIP_DEVICE) अणु
		/* Get device status */
		usb_status = 1 << USB_DEVICE_SELF_POWERED;
	पूर्ण अन्यथा अगर ((request_type & USB_RECIP_MASK) == USB_RECIP_INTERFACE) अणु
		/* Get पूर्णांकerface status */
		/* We करोn't have पूर्णांकerface inक्रमmation in udc driver */
		usb_status = 0;
	पूर्ण अन्यथा अगर ((request_type & USB_RECIP_MASK) == USB_RECIP_ENDPOINT) अणु
		/* Get endpoपूर्णांक status */
		पूर्णांक pipe = index & USB_ENDPOINT_NUMBER_MASK;
		काष्ठा qe_ep *target_ep = &udc->eps[pipe];
		u16 usep;

		/* stall अगर endpoपूर्णांक करोesn't exist */
		अगर (!target_ep->ep.desc)
			जाओ stall;

		usep = in_be16(&udc->usb_regs->usb_usep[pipe]);
		अगर (index & USB_सूची_IN) अणु
			अगर (target_ep->dir != USB_सूची_IN)
				जाओ stall;
			अगर ((usep & USB_THS_MASK) == USB_THS_STALL)
				usb_status = 1 << USB_ENDPOINT_HALT;
		पूर्ण अन्यथा अणु
			अगर (target_ep->dir != USB_सूची_OUT)
				जाओ stall;
			अगर ((usep & USB_RHS_MASK) == USB_RHS_STALL)
				usb_status = 1 << USB_ENDPOINT_HALT;
		पूर्ण
	पूर्ण

	req = container_of(qe_alloc_request(&ep->ep, GFP_KERNEL),
					काष्ठा qe_req, req);
	req->req.length = 2;
	req->req.buf = udc->statusbuf;
	*(u16 *)req->req.buf = cpu_to_le16(usb_status);
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	req->req.complete = ownercomplete;

	udc->ep0_dir = USB_सूची_IN;

	/* data phase */
	status = __qe_ep_queue(&ep->ep, &req->req);

	अगर (status == 0)
		वापस;
stall:
	dev_err(udc->dev, "Can't respond to getstatus request \n");
	qe_ep0_stall(udc);
पूर्ण

/* only handle the setup request, suppose the device in normal status */
अटल व्योम setup_received_handle(काष्ठा qe_udc *udc,
				काष्ठा usb_ctrlrequest *setup)
अणु
	/* Fix Endian (udc->local_setup_buff is cpu Endian now)*/
	u16 wValue = le16_to_cpu(setup->wValue);
	u16 wIndex = le16_to_cpu(setup->wIndex);
	u16 wLength = le16_to_cpu(setup->wLength);

	/* clear the previous request in the ep0 */
	udc_reset_ep_queue(udc, 0);

	अगर (setup->bRequestType & USB_सूची_IN)
		udc->ep0_dir = USB_सूची_IN;
	अन्यथा
		udc->ep0_dir = USB_सूची_OUT;

	चयन (setup->bRequest) अणु
	हाल USB_REQ_GET_STATUS:
		/* Data+Status phase क्रमm udc */
		अगर ((setup->bRequestType & (USB_सूची_IN | USB_TYPE_MASK))
					!= (USB_सूची_IN | USB_TYPE_STANDARD))
			अवरोध;
		ch9माला_लोtatus(udc, setup->bRequestType, wValue, wIndex,
					wLength);
		वापस;

	हाल USB_REQ_SET_ADDRESS:
		/* Status phase from udc */
		अगर (setup->bRequestType != (USB_सूची_OUT | USB_TYPE_STANDARD |
						USB_RECIP_DEVICE))
			अवरोध;
		ch9setaddress(udc, wValue, wIndex, wLength);
		वापस;

	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		/* Requests with no data phase, status phase from udc */
		अगर ((setup->bRequestType & USB_TYPE_MASK)
					!= USB_TYPE_STANDARD)
			अवरोध;

		अगर ((setup->bRequestType & USB_RECIP_MASK)
				== USB_RECIP_ENDPOINT) अणु
			पूर्णांक pipe = wIndex & USB_ENDPOINT_NUMBER_MASK;
			काष्ठा qe_ep *ep;

			अगर (wValue != 0 || wLength != 0
				|| pipe >= USB_MAX_ENDPOINTS)
				अवरोध;
			ep = &udc->eps[pipe];

			spin_unlock(&udc->lock);
			qe_ep_set_halt(&ep->ep,
					(setup->bRequest == USB_REQ_SET_FEATURE)
						? 1 : 0);
			spin_lock(&udc->lock);
		पूर्ण

		ep0_prime_status(udc, USB_सूची_IN);

		वापस;

	शेष:
		अवरोध;
	पूर्ण

	अगर (wLength) अणु
		/* Data phase from gadget, status phase from udc */
		अगर (setup->bRequestType & USB_सूची_IN) अणु
			udc->ep0_state = DATA_STATE_XMIT;
			udc->ep0_dir = USB_सूची_IN;
		पूर्ण अन्यथा अणु
			udc->ep0_state = DATA_STATE_RECV;
			udc->ep0_dir = USB_सूची_OUT;
		पूर्ण
		spin_unlock(&udc->lock);
		अगर (udc->driver->setup(&udc->gadget,
					&udc->local_setup_buff) < 0)
			qe_ep0_stall(udc);
		spin_lock(&udc->lock);
	पूर्ण अन्यथा अणु
		/* No data phase, IN status from gadget */
		udc->ep0_dir = USB_सूची_IN;
		spin_unlock(&udc->lock);
		अगर (udc->driver->setup(&udc->gadget,
					&udc->local_setup_buff) < 0)
			qe_ep0_stall(udc);
		spin_lock(&udc->lock);
		udc->ep0_state = DATA_STATE_NEED_ZLP;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------
	USB Interrupt handlers
 -------------------------------------------------------------------------*/
अटल व्योम suspend_irq(काष्ठा qe_udc *udc)
अणु
	udc->resume_state = udc->usb_state;
	udc->usb_state = USB_STATE_SUSPENDED;

	/* report suspend to the driver ,serial.c not support this*/
	अगर (udc->driver->suspend)
		udc->driver->suspend(&udc->gadget);
पूर्ण

अटल व्योम resume_irq(काष्ठा qe_udc *udc)
अणु
	udc->usb_state = udc->resume_state;
	udc->resume_state = 0;

	/* report resume to the driver , serial.c not support this*/
	अगर (udc->driver->resume)
		udc->driver->resume(&udc->gadget);
पूर्ण

अटल व्योम idle_irq(काष्ठा qe_udc *udc)
अणु
	u8 usbs;

	usbs = in_8(&udc->usb_regs->usb_usbs);
	अगर (usbs & USB_IDLE_STATUS_MASK) अणु
		अगर ((udc->usb_state) != USB_STATE_SUSPENDED)
			suspend_irq(udc);
	पूर्ण अन्यथा अणु
		अगर (udc->usb_state == USB_STATE_SUSPENDED)
			resume_irq(udc);
	पूर्ण
पूर्ण

अटल पूर्णांक reset_irq(काष्ठा qe_udc *udc)
अणु
	अचिन्हित अक्षर i;

	अगर (udc->usb_state == USB_STATE_DEFAULT)
		वापस 0;

	qe_usb_disable(udc);
	out_8(&udc->usb_regs->usb_usadr, 0);

	क्रम (i = 0; i < USB_MAX_ENDPOINTS; i++) अणु
		अगर (udc->eps[i].init)
			qe_ep_reset(udc, i);
	पूर्ण

	reset_queues(udc);
	udc->usb_state = USB_STATE_DEFAULT;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = USB_सूची_OUT;
	qe_usb_enable(udc);
	वापस 0;
पूर्ण

अटल पूर्णांक bsy_irq(काष्ठा qe_udc *udc)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक txe_irq(काष्ठा qe_udc *udc)
अणु
	वापस 0;
पूर्ण

/* ep0 tx पूर्णांकerrupt also in here */
अटल पूर्णांक tx_irq(काष्ठा qe_udc *udc)
अणु
	काष्ठा qe_ep *ep;
	काष्ठा qe_bd __iomem *bd;
	पूर्णांक i, res = 0;

	अगर ((udc->usb_state == USB_STATE_ADDRESS)
		&& (in_8(&udc->usb_regs->usb_usadr) == 0))
		out_8(&udc->usb_regs->usb_usadr, udc->device_address);

	क्रम (i = (USB_MAX_ENDPOINTS-1); ((i >= 0) && (res == 0)); i--) अणु
		ep = &udc->eps[i];
		अगर (ep && ep->init && (ep->dir != USB_सूची_OUT)) अणु
			bd = ep->c_txbd;
			अगर (!(in_be32((u32 __iomem *)bd) & T_R)
						&& (in_be32(&bd->buf))) अणु
				/* confirm the transmitted bd */
				अगर (ep->epnum == 0)
					res = qe_ep0_txconf(ep);
				अन्यथा
					res = qe_ep_txconf(ep);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण


/* setup packect's rx is handle in the function too */
अटल व्योम rx_irq(काष्ठा qe_udc *udc)
अणु
	काष्ठा qe_ep *ep;
	काष्ठा qe_bd __iomem *bd;
	पूर्णांक i;

	क्रम (i = 0; i < USB_MAX_ENDPOINTS; i++) अणु
		ep = &udc->eps[i];
		अगर (ep && ep->init && (ep->dir != USB_सूची_IN)) अणु
			bd = ep->n_rxbd;
			अगर (!(in_be32((u32 __iomem *)bd) & R_E)
						&& (in_be32(&bd->buf))) अणु
				अगर (ep->epnum == 0) अणु
					qe_ep0_rx(udc);
				पूर्ण अन्यथा अणु
					/*non-setup package receive*/
					qe_ep_rx(ep);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t qe_udc_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा qe_udc *udc = (काष्ठा qe_udc *)_udc;
	u16 irq_src;
	irqवापस_t status = IRQ_NONE;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);

	irq_src = in_be16(&udc->usb_regs->usb_usber) &
		in_be16(&udc->usb_regs->usb_usbmr);
	/* Clear notअगरication bits */
	out_be16(&udc->usb_regs->usb_usber, irq_src);
	/* USB Interrupt */
	अगर (irq_src & USB_E_IDLE_MASK) अणु
		idle_irq(udc);
		irq_src &= ~USB_E_IDLE_MASK;
		status = IRQ_HANDLED;
	पूर्ण

	अगर (irq_src & USB_E_TXB_MASK) अणु
		tx_irq(udc);
		irq_src &= ~USB_E_TXB_MASK;
		status = IRQ_HANDLED;
	पूर्ण

	अगर (irq_src & USB_E_RXB_MASK) अणु
		rx_irq(udc);
		irq_src &= ~USB_E_RXB_MASK;
		status = IRQ_HANDLED;
	पूर्ण

	अगर (irq_src & USB_E_RESET_MASK) अणु
		reset_irq(udc);
		irq_src &= ~USB_E_RESET_MASK;
		status = IRQ_HANDLED;
	पूर्ण

	अगर (irq_src & USB_E_BSY_MASK) अणु
		bsy_irq(udc);
		irq_src &= ~USB_E_BSY_MASK;
		status = IRQ_HANDLED;
	पूर्ण

	अगर (irq_src & USB_E_TXE_MASK) अणु
		txe_irq(udc);
		irq_src &= ~USB_E_TXE_MASK;
		status = IRQ_HANDLED;
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस status;
पूर्ण

/*-------------------------------------------------------------------------
	Gadget driver probe and unरेजिस्टर.
 --------------------------------------------------------------------------*/
अटल पूर्णांक fsl_qe_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा qe_udc *udc;
	अचिन्हित दीर्घ flags;

	udc = container_of(gadget, काष्ठा qe_udc, gadget);
	/* lock is needed but whether should use this lock or another */
	spin_lock_irqsave(&udc->lock, flags);

	driver->driver.bus = शून्य;
	/* hook up the driver */
	udc->driver = driver;
	udc->gadget.speed = driver->max_speed;

	/* Enable IRQ reg and Set usbcmd reg EN bit */
	qe_usb_enable(udc);

	out_be16(&udc->usb_regs->usb_usber, 0xffff);
	out_be16(&udc->usb_regs->usb_usbmr, USB_E_DEFAULT_DEVICE);
	udc->usb_state = USB_STATE_ATTACHED;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = USB_सूची_OUT;
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_qe_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा qe_udc *udc;
	काष्ठा qe_ep *loop_ep;
	अचिन्हित दीर्घ flags;

	udc = container_of(gadget, काष्ठा qe_udc, gadget);
	/* stop usb controller, disable पूर्णांकr */
	qe_usb_disable(udc);

	/* in fact, no needed */
	udc->usb_state = USB_STATE_ATTACHED;
	udc->ep0_state = WAIT_FOR_SETUP;
	udc->ep0_dir = 0;

	/* stand operation */
	spin_lock_irqsave(&udc->lock, flags);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	nuke(&udc->eps[0], -ESHUTDOWN);
	list_क्रम_each_entry(loop_ep, &udc->gadget.ep_list, ep.ep_list)
		nuke(loop_ep, -ESHUTDOWN);
	spin_unlock_irqrestore(&udc->lock, flags);

	udc->driver = शून्य;

	वापस 0;
पूर्ण

/* udc काष्ठाure's alloc and setup, include ep-param alloc */
अटल काष्ठा qe_udc *qe_udc_config(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा qe_udc *udc;
	काष्ठा device_node *np = ofdev->dev.of_node;
	अचिन्हित दीर्घ पंचांगp_addr = 0;
	काष्ठा usb_device_para __iomem *usbpram;
	अचिन्हित पूर्णांक i;
	u64 size;
	u32 offset;

	udc = kzalloc(माप(*udc), GFP_KERNEL);
	अगर (!udc)
		जाओ cleanup;

	udc->dev = &ofdev->dev;

	/* get शेष address of usb parameter in MURAM from device tree */
	offset = *of_get_address(np, 1, &size, शून्य);
	udc->usb_param = cpm_muram_addr(offset);
	स_रखो_io(udc->usb_param, 0, size);

	usbpram = udc->usb_param;
	out_be16(&usbpram->frame_n, 0);
	out_be32(&usbpram->rstate, 0);

	पंचांगp_addr = cpm_muram_alloc((USB_MAX_ENDPOINTS *
					माप(काष्ठा usb_ep_para)),
					   USB_EP_PARA_ALIGNMENT);
	अगर (IS_ERR_VALUE(पंचांगp_addr))
		जाओ cleanup;

	क्रम (i = 0; i < USB_MAX_ENDPOINTS; i++) अणु
		out_be16(&usbpram->epptr[i], (u16)पंचांगp_addr);
		udc->ep_param[i] = cpm_muram_addr(पंचांगp_addr);
		पंचांगp_addr += 32;
	पूर्ण

	स_रखो_io(udc->ep_param[0], 0,
			USB_MAX_ENDPOINTS * माप(काष्ठा usb_ep_para));

	udc->resume_state = USB_STATE_NOTATTACHED;
	udc->usb_state = USB_STATE_POWERED;
	udc->ep0_dir = 0;

	spin_lock_init(&udc->lock);
	वापस udc;

cleanup:
	kमुक्त(udc);
	वापस शून्य;
पूर्ण

/* USB Controller रेजिस्टर init */
अटल पूर्णांक qe_udc_reg_init(काष्ठा qe_udc *udc)
अणु
	काष्ठा usb_ctlr __iomem *qe_usbregs;
	qe_usbregs = udc->usb_regs;

	/* Spec says that we must enable the USB controller to change mode. */
	out_8(&qe_usbregs->usb_usmod, 0x01);
	/* Mode changed, now disable it, since muram isn't initialized yet. */
	out_8(&qe_usbregs->usb_usmod, 0x00);

	/* Initialize the rest. */
	out_be16(&qe_usbregs->usb_usbmr, 0);
	out_8(&qe_usbregs->usb_uscom, 0);
	out_be16(&qe_usbregs->usb_usber, USBER_ALL_CLEAR);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_ep_config(काष्ठा qe_udc *udc, अचिन्हित अक्षर pipe_num)
अणु
	काष्ठा qe_ep *ep = &udc->eps[pipe_num];

	ep->udc = udc;
	म_नकल(ep->name, ep_name[pipe_num]);
	ep->ep.name = ep_name[pipe_num];

	अगर (pipe_num == 0) अणु
		ep->ep.caps.type_control = true;
	पूर्ण अन्यथा अणु
		ep->ep.caps.type_iso = true;
		ep->ep.caps.type_bulk = true;
		ep->ep.caps.type_पूर्णांक = true;
	पूर्ण

	ep->ep.caps.dir_in = true;
	ep->ep.caps.dir_out = true;

	ep->ep.ops = &qe_ep_ops;
	ep->stopped = 1;
	usb_ep_set_maxpacket_limit(&ep->ep, (अचिन्हित लघु) ~0);
	ep->ep.desc = शून्य;
	ep->dir = 0xff;
	ep->epnum = (u8)pipe_num;
	ep->sent = 0;
	ep->last = 0;
	ep->init = 0;
	ep->rxframe = शून्य;
	ep->txframe = शून्य;
	ep->tx_req = शून्य;
	ep->state = EP_STATE_IDLE;
	ep->has_data = 0;

	/* the queue lists any req क्रम this ep */
	INIT_LIST_HEAD(&ep->queue);

	/* gagdet.ep_list used क्रम ep_स्वतःconfig so no ep0*/
	अगर (pipe_num != 0)
		list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);

	ep->gadget = &udc->gadget;

	वापस 0;
पूर्ण

/*-----------------------------------------------------------------------
 *	UDC device Driver operation functions				*
 *----------------------------------------------------------------------*/
अटल व्योम qe_udc_release(काष्ठा device *dev)
अणु
	काष्ठा qe_udc *udc = container_of(dev, काष्ठा qe_udc, gadget.dev);
	पूर्णांक i;

	complete(udc->करोne);
	cpm_muram_मुक्त(cpm_muram_offset(udc->ep_param[0]));
	क्रम (i = 0; i < USB_MAX_ENDPOINTS; i++)
		udc->ep_param[i] = शून्य;

	kमुक्त(udc);
पूर्ण

/* Driver probe functions */
अटल स्थिर काष्ठा of_device_id qe_udc_match[];
अटल पूर्णांक qe_udc_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा qe_udc *udc;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा qe_ep *ep;
	अचिन्हित पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	स्थिर व्योम *prop;

	match = of_match_device(qe_udc_match, &ofdev->dev);
	अगर (!match)
		वापस -EINVAL;

	prop = of_get_property(np, "mode", शून्य);
	अगर (!prop || म_भेद(prop, "peripheral"))
		वापस -ENODEV;

	/* Initialize the udc काष्ठाure including QH member and other member */
	udc = qe_udc_config(ofdev);
	अगर (!udc) अणु
		dev_err(&ofdev->dev, "failed to initialize\n");
		वापस -ENOMEM;
	पूर्ण

	udc->soc_type = (अचिन्हित दीर्घ)match->data;
	udc->usb_regs = of_iomap(np, 0);
	अगर (!udc->usb_regs) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	/* initialize usb hw reg except क्रम regs क्रम EP,
	 * leave usbपूर्णांकr reg untouched*/
	qe_udc_reg_init(udc);

	/* here comes the stand operations क्रम probe
	 * set the qe_udc->gadget.xxx */
	udc->gadget.ops = &qe_gadget_ops;

	/* gadget.ep0 is a poपूर्णांकer */
	udc->gadget.ep0 = &udc->eps[0].ep;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	/* modअगरy in रेजिस्टर gadget process */
	udc->gadget.speed = USB_SPEED_UNKNOWN;

	/* name: Identअगरies the controller hardware type. */
	udc->gadget.name = driver_name;
	udc->gadget.dev.parent = &ofdev->dev;

	/* initialize qe_ep काष्ठा */
	क्रम (i = 0; i < USB_MAX_ENDPOINTS ; i++) अणु
		/* because the ep type isn't decide here so
		 * qe_ep_init() should be called in ep_enable() */

		/* setup the qe_ep काष्ठा and link ep.ep.list
		 * पूर्णांकo gadget.ep_list */
		qe_ep_config(udc, (अचिन्हित अक्षर)i);
	पूर्ण

	/* ep0 initialization in here */
	ret = qe_ep_init(udc, 0, &qe_ep0_desc);
	अगर (ret)
		जाओ err2;

	/* create a buf क्रम ZLP send, need to reमुख्य zeroed */
	udc->nullbuf = devm_kzalloc(&ofdev->dev, 256, GFP_KERNEL);
	अगर (udc->nullbuf == शून्य) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण

	/* buffer क्रम data of get_status request */
	udc->statusbuf = devm_kzalloc(&ofdev->dev, 2, GFP_KERNEL);
	अगर (udc->statusbuf == शून्य) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण

	udc->nullp = virt_to_phys((व्योम *)udc->nullbuf);
	अगर (udc->nullp == DMA_ADDR_INVALID) अणु
		udc->nullp = dma_map_single(
					udc->gadget.dev.parent,
					udc->nullbuf,
					256,
					DMA_TO_DEVICE);
		udc->nullmap = 1;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_device(udc->gadget.dev.parent,
					udc->nullp, 256,
					DMA_TO_DEVICE);
	पूर्ण

	tasklet_setup(&udc->rx_tasklet, ep_rx_tasklet);
	/* request irq and disable DR  */
	udc->usb_irq = irq_of_parse_and_map(np, 0);
	अगर (!udc->usb_irq) अणु
		ret = -EINVAL;
		जाओ err_noirq;
	पूर्ण

	ret = request_irq(udc->usb_irq, qe_udc_irq, 0,
				driver_name, udc);
	अगर (ret) अणु
		dev_err(udc->dev, "cannot request irq %d err %d\n",
				udc->usb_irq, ret);
		जाओ err4;
	पूर्ण

	ret = usb_add_gadget_udc_release(&ofdev->dev, &udc->gadget,
			qe_udc_release);
	अगर (ret)
		जाओ err5;

	platक्रमm_set_drvdata(ofdev, udc);
	dev_info(udc->dev,
			"%s USB controller initialized as device\n",
			(udc->soc_type == PORT_QE) ? "QE" : "CPM");
	वापस 0;

err5:
	मुक्त_irq(udc->usb_irq, udc);
err4:
	irq_dispose_mapping(udc->usb_irq);
err_noirq:
	अगर (udc->nullmap) अणु
		dma_unmap_single(udc->gadget.dev.parent,
			udc->nullp, 256,
				DMA_TO_DEVICE);
			udc->nullp = DMA_ADDR_INVALID;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_cpu(udc->gadget.dev.parent,
			udc->nullp, 256,
				DMA_TO_DEVICE);
	पूर्ण
err3:
	ep = &udc->eps[0];
	cpm_muram_मुक्त(cpm_muram_offset(ep->rxbase));
	kमुक्त(ep->rxframe);
	kमुक्त(ep->rxbuffer);
	kमुक्त(ep->txframe);
err2:
	iounmap(udc->usb_regs);
err1:
	kमुक्त(udc);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक qe_udc_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक qe_udc_resume(काष्ठा platक्रमm_device *dev)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक qe_udc_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा qe_udc *udc = platक्रमm_get_drvdata(ofdev);
	काष्ठा qe_ep *ep;
	अचिन्हित पूर्णांक size;
	DECLARE_COMPLETION_ONSTACK(करोne);

	usb_del_gadget_udc(&udc->gadget);

	udc->करोne = &करोne;
	tasklet_disable(&udc->rx_tasklet);

	अगर (udc->nullmap) अणु
		dma_unmap_single(udc->gadget.dev.parent,
			udc->nullp, 256,
				DMA_TO_DEVICE);
			udc->nullp = DMA_ADDR_INVALID;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_cpu(udc->gadget.dev.parent,
			udc->nullp, 256,
				DMA_TO_DEVICE);
	पूर्ण

	ep = &udc->eps[0];
	cpm_muram_मुक्त(cpm_muram_offset(ep->rxbase));
	size = (ep->ep.maxpacket + USB_CRC_SIZE + 2) * (USB_BDRING_LEN + 1);

	kमुक्त(ep->rxframe);
	अगर (ep->rxbufmap) अणु
		dma_unmap_single(udc->gadget.dev.parent,
				ep->rxbuf_d, size,
				DMA_FROM_DEVICE);
		ep->rxbuf_d = DMA_ADDR_INVALID;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_cpu(udc->gadget.dev.parent,
				ep->rxbuf_d, size,
				DMA_FROM_DEVICE);
	पूर्ण

	kमुक्त(ep->rxbuffer);
	kमुक्त(ep->txframe);

	मुक्त_irq(udc->usb_irq, udc);
	irq_dispose_mapping(udc->usb_irq);

	tasklet_समाप्त(&udc->rx_tasklet);

	iounmap(udc->usb_regs);

	/* रुको क्रम release() of gadget.dev to मुक्त udc */
	रुको_क्रम_completion(&करोne);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
अटल स्थिर काष्ठा of_device_id qe_udc_match[] = अणु
	अणु
		.compatible = "fsl,mpc8323-qe-usb",
		.data = (व्योम *)PORT_QE,
	पूर्ण,
	अणु
		.compatible = "fsl,mpc8360-qe-usb",
		.data = (व्योम *)PORT_QE,
	पूर्ण,
	अणु
		.compatible = "fsl,mpc8272-cpm-usb",
		.data = (व्योम *)PORT_CPM,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, qe_udc_match);

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.driver = अणु
		.name = driver_name,
		.of_match_table = qe_udc_match,
	पूर्ण,
	.probe          = qe_udc_probe,
	.हटाओ         = qe_udc_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend        = qe_udc_suspend,
	.resume         = qe_udc_resume,
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(udc_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
