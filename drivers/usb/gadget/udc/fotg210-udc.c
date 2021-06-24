<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FOTG210 UDC Driver supports Bulk transfer so far
 *
 * Copyright (C) 2013 Faraday Technology Corporation
 *
 * Author : Yuan-Hsin Chen <yhchen@faraday-tech.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश "fotg210.h"

#घोषणा	DRIVER_DESC	"FOTG210 USB Device Controller Driver"
#घोषणा	DRIVER_VERSION	"30-April-2013"

अटल स्थिर अक्षर udc_name[] = "fotg210_udc";
अटल स्थिर अक्षर * स्थिर fotg210_ep_name[] = अणु
	"ep0", "ep1", "ep2", "ep3", "ep4"पूर्ण;

अटल व्योम fotg210_disable_fअगरo_पूर्णांक(काष्ठा fotg210_ep *ep)
अणु
	u32 value = ioपढ़ो32(ep->fotg210->reg + FOTG210_DMISGR1);

	अगर (ep->dir_in)
		value |= DMISGR1_MF_IN_INT(ep->epnum - 1);
	अन्यथा
		value |= DMISGR1_MF_OUTSPK_INT(ep->epnum - 1);
	ioग_लिखो32(value, ep->fotg210->reg + FOTG210_DMISGR1);
पूर्ण

अटल व्योम fotg210_enable_fअगरo_पूर्णांक(काष्ठा fotg210_ep *ep)
अणु
	u32 value = ioपढ़ो32(ep->fotg210->reg + FOTG210_DMISGR1);

	अगर (ep->dir_in)
		value &= ~DMISGR1_MF_IN_INT(ep->epnum - 1);
	अन्यथा
		value &= ~DMISGR1_MF_OUTSPK_INT(ep->epnum - 1);
	ioग_लिखो32(value, ep->fotg210->reg + FOTG210_DMISGR1);
पूर्ण

अटल व्योम fotg210_set_cxकरोne(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_DCFESR);

	value |= DCFESR_CX_DONE;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DCFESR);
पूर्ण

अटल व्योम fotg210_करोne(काष्ठा fotg210_ep *ep, काष्ठा fotg210_request *req,
			पूर्णांक status)
अणु
	list_del_init(&req->queue);

	/* करोn't modअगरy queue heads during completion callback */
	अगर (ep->fotg210->gadget.speed == USB_SPEED_UNKNOWN)
		req->req.status = -ESHUTDOWN;
	अन्यथा
		req->req.status = status;

	spin_unlock(&ep->fotg210->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&ep->fotg210->lock);

	अगर (ep->epnum) अणु
		अगर (list_empty(&ep->queue))
			fotg210_disable_fअगरo_पूर्णांक(ep);
	पूर्ण अन्यथा अणु
		fotg210_set_cxकरोne(ep->fotg210);
	पूर्ण
पूर्ण

अटल व्योम fotg210_fअगरo_ep_mapping(काष्ठा fotg210_ep *ep, u32 epnum,
				u32 dir_in)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 val;

	/* Driver should map an ep to a fअगरo and then map the fअगरo
	 * to the ep. What a brain-damaged design!
	 */

	/* map a fअगरo to an ep */
	val = ioपढ़ो32(fotg210->reg + FOTG210_EPMAP);
	val &= ~EPMAP_FIFONOMSK(epnum, dir_in);
	val |= EPMAP_FIFONO(epnum, dir_in);
	ioग_लिखो32(val, fotg210->reg + FOTG210_EPMAP);

	/* map the ep to the fअगरo */
	val = ioपढ़ो32(fotg210->reg + FOTG210_FIFOMAP);
	val &= ~FIFOMAP_EPNOMSK(epnum);
	val |= FIFOMAP_EPNO(epnum);
	ioग_लिखो32(val, fotg210->reg + FOTG210_FIFOMAP);

	/* enable fअगरo */
	val = ioपढ़ो32(fotg210->reg + FOTG210_FIFOCF);
	val |= FIFOCF_FIFO_EN(epnum - 1);
	ioग_लिखो32(val, fotg210->reg + FOTG210_FIFOCF);
पूर्ण

अटल व्योम fotg210_set_fअगरo_dir(काष्ठा fotg210_ep *ep, u32 epnum, u32 dir_in)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 val;

	val = ioपढ़ो32(fotg210->reg + FOTG210_FIFOMAP);
	val |= (dir_in ? FIFOMAP_सूचीIN(epnum - 1) : FIFOMAP_सूचीOUT(epnum - 1));
	ioग_लिखो32(val, fotg210->reg + FOTG210_FIFOMAP);
पूर्ण

अटल व्योम fotg210_set_tfrtype(काष्ठा fotg210_ep *ep, u32 epnum, u32 type)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 val;

	val = ioपढ़ो32(fotg210->reg + FOTG210_FIFOCF);
	val |= FIFOCF_TYPE(type, epnum - 1);
	ioग_लिखो32(val, fotg210->reg + FOTG210_FIFOCF);
पूर्ण

अटल व्योम fotg210_set_mps(काष्ठा fotg210_ep *ep, u32 epnum, u32 mps,
				u32 dir_in)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 val;
	u32 offset = dir_in ? FOTG210_INEPMPSR(epnum) :
				FOTG210_OUTEPMPSR(epnum);

	val = ioपढ़ो32(fotg210->reg + offset);
	val |= INOUTEPMPSR_MPS(mps);
	ioग_लिखो32(val, fotg210->reg + offset);
पूर्ण

अटल पूर्णांक fotg210_config_ep(काष्ठा fotg210_ep *ep,
		     स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;

	fotg210_set_fअगरo_dir(ep, ep->epnum, ep->dir_in);
	fotg210_set_tfrtype(ep, ep->epnum, ep->type);
	fotg210_set_mps(ep, ep->epnum, ep->ep.maxpacket, ep->dir_in);
	fotg210_fअगरo_ep_mapping(ep, ep->epnum, ep->dir_in);

	fotg210->ep[ep->epnum] = ep;

	वापस 0;
पूर्ण

अटल पूर्णांक fotg210_ep_enable(काष्ठा usb_ep *_ep,
			  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा fotg210_ep *ep;

	ep = container_of(_ep, काष्ठा fotg210_ep, ep);

	ep->desc = desc;
	ep->epnum = usb_endpoपूर्णांक_num(desc);
	ep->type = usb_endpoपूर्णांक_type(desc);
	ep->dir_in = usb_endpoपूर्णांक_dir_in(desc);
	ep->ep.maxpacket = usb_endpoपूर्णांक_maxp(desc);

	वापस fotg210_config_ep(ep, desc);
पूर्ण

अटल व्योम fotg210_reset_tseq(काष्ठा fotg210_udc *fotg210, u8 epnum)
अणु
	काष्ठा fotg210_ep *ep = fotg210->ep[epnum];
	u32 value;
	व्योम __iomem *reg;

	reg = (ep->dir_in) ?
		fotg210->reg + FOTG210_INEPMPSR(epnum) :
		fotg210->reg + FOTG210_OUTEPMPSR(epnum);

	/* Note: Driver needs to set and clear INOUTEPMPSR_RESET_TSEQ
	 *	 bit. Controller wouldn't clear this bit. WTF!!!
	 */

	value = ioपढ़ो32(reg);
	value |= INOUTEPMPSR_RESET_TSEQ;
	ioग_लिखो32(value, reg);

	value = ioपढ़ो32(reg);
	value &= ~INOUTEPMPSR_RESET_TSEQ;
	ioग_लिखो32(value, reg);
पूर्ण

अटल पूर्णांक fotg210_ep_release(काष्ठा fotg210_ep *ep)
अणु
	अगर (!ep->epnum)
		वापस 0;
	ep->epnum = 0;
	ep->stall = 0;
	ep->wedged = 0;

	fotg210_reset_tseq(ep->fotg210, ep->epnum);

	वापस 0;
पूर्ण

अटल पूर्णांक fotg210_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा fotg210_ep *ep;
	काष्ठा fotg210_request *req;
	अचिन्हित दीर्घ flags;

	BUG_ON(!_ep);

	ep = container_of(_ep, काष्ठा fotg210_ep, ep);

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next,
			काष्ठा fotg210_request, queue);
		spin_lock_irqsave(&ep->fotg210->lock, flags);
		fotg210_करोne(ep, req, -ECONNRESET);
		spin_unlock_irqrestore(&ep->fotg210->lock, flags);
	पूर्ण

	वापस fotg210_ep_release(ep);
पूर्ण

अटल काष्ठा usb_request *fotg210_ep_alloc_request(काष्ठा usb_ep *_ep,
						gfp_t gfp_flags)
अणु
	काष्ठा fotg210_request *req;

	req = kzalloc(माप(काष्ठा fotg210_request), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम fotg210_ep_मुक्त_request(काष्ठा usb_ep *_ep,
					काष्ठा usb_request *_req)
अणु
	काष्ठा fotg210_request *req;

	req = container_of(_req, काष्ठा fotg210_request, req);
	kमुक्त(req);
पूर्ण

अटल व्योम fotg210_enable_dma(काष्ठा fotg210_ep *ep,
			      dma_addr_t d, u32 len)
अणु
	u32 value;
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;

	/* set transfer length and direction */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMACPSR1);
	value &= ~(DMACPSR1_DMA_LEN(0xFFFF) | DMACPSR1_DMA_TYPE(1));
	value |= DMACPSR1_DMA_LEN(len) | DMACPSR1_DMA_TYPE(ep->dir_in);
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMACPSR1);

	/* set device DMA target FIFO number */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMATFNR);
	अगर (ep->epnum)
		value |= DMATFNR_ACC_FN(ep->epnum - 1);
	अन्यथा
		value |= DMATFNR_ACC_CXF;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMATFNR);

	/* set DMA memory address */
	ioग_लिखो32(d, fotg210->reg + FOTG210_DMACPSR2);

	/* enable MDMA_EROR and MDMA_CMPLT पूर्णांकerrupt */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMISGR2);
	value &= ~(DMISGR2_MDMA_CMPLT | DMISGR2_MDMA_ERROR);
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMISGR2);

	/* start DMA */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMACPSR1);
	value |= DMACPSR1_DMA_START;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMACPSR1);
पूर्ण

अटल व्योम fotg210_disable_dma(काष्ठा fotg210_ep *ep)
अणु
	ioग_लिखो32(DMATFNR_DISDMA, ep->fotg210->reg + FOTG210_DMATFNR);
पूर्ण

अटल व्योम fotg210_रुको_dma_करोne(काष्ठा fotg210_ep *ep)
अणु
	u32 value;

	करो अणु
		value = ioपढ़ो32(ep->fotg210->reg + FOTG210_DISGR2);
		अगर ((value & DISGR2_USBRST_INT) ||
		    (value & DISGR2_DMA_ERROR))
			जाओ dma_reset;
	पूर्ण जबतक (!(value & DISGR2_DMA_CMPLT));

	value &= ~DISGR2_DMA_CMPLT;
	ioग_लिखो32(value, ep->fotg210->reg + FOTG210_DISGR2);
	वापस;

dma_reset:
	value = ioपढ़ो32(ep->fotg210->reg + FOTG210_DMACPSR1);
	value |= DMACPSR1_DMA_ABORT;
	ioग_लिखो32(value, ep->fotg210->reg + FOTG210_DMACPSR1);

	/* reset fअगरo */
	अगर (ep->epnum) अणु
		value = ioपढ़ो32(ep->fotg210->reg +
				FOTG210_FIBCR(ep->epnum - 1));
		value |= FIBCR_FFRST;
		ioग_लिखो32(value, ep->fotg210->reg +
				FOTG210_FIBCR(ep->epnum - 1));
	पूर्ण अन्यथा अणु
		value = ioपढ़ो32(ep->fotg210->reg + FOTG210_DCFESR);
		value |= DCFESR_CX_CLR;
		ioग_लिखो32(value, ep->fotg210->reg + FOTG210_DCFESR);
	पूर्ण
पूर्ण

अटल व्योम fotg210_start_dma(काष्ठा fotg210_ep *ep,
			काष्ठा fotg210_request *req)
अणु
	काष्ठा device *dev = &ep->fotg210->gadget.dev;
	dma_addr_t d;
	u8 *buffer;
	u32 length;

	अगर (ep->epnum) अणु
		अगर (ep->dir_in) अणु
			buffer = req->req.buf;
			length = req->req.length;
		पूर्ण अन्यथा अणु
			buffer = req->req.buf + req->req.actual;
			length = ioपढ़ो32(ep->fotg210->reg +
					FOTG210_FIBCR(ep->epnum - 1)) & FIBCR_BCFX;
			अगर (length > req->req.length - req->req.actual)
				length = req->req.length - req->req.actual;
		पूर्ण
	पूर्ण अन्यथा अणु
		buffer = req->req.buf + req->req.actual;
		अगर (req->req.length - req->req.actual > ep->ep.maxpacket)
			length = ep->ep.maxpacket;
		अन्यथा
			length = req->req.length - req->req.actual;
	पूर्ण

	d = dma_map_single(dev, buffer, length,
			ep->dir_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

	अगर (dma_mapping_error(dev, d)) अणु
		pr_err("dma_mapping_error\n");
		वापस;
	पूर्ण

	fotg210_enable_dma(ep, d, length);

	/* check अगर dma is करोne */
	fotg210_रुको_dma_करोne(ep);

	fotg210_disable_dma(ep);

	/* update actual transfer length */
	req->req.actual += length;

	dma_unmap_single(dev, d, length, DMA_TO_DEVICE);
पूर्ण

अटल व्योम fotg210_ep0_queue(काष्ठा fotg210_ep *ep,
				काष्ठा fotg210_request *req)
अणु
	अगर (!req->req.length) अणु
		fotg210_करोne(ep, req, 0);
		वापस;
	पूर्ण
	अगर (ep->dir_in) अणु /* अगर IN */
		fotg210_start_dma(ep, req);
		अगर (req->req.length == req->req.actual)
			fotg210_करोne(ep, req, 0);
	पूर्ण अन्यथा अणु /* OUT */
		u32 value = ioपढ़ो32(ep->fotg210->reg + FOTG210_DMISGR0);

		value &= ~DMISGR0_MCX_OUT_INT;
		ioग_लिखो32(value, ep->fotg210->reg + FOTG210_DMISGR0);
	पूर्ण
पूर्ण

अटल पूर्णांक fotg210_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
				gfp_t gfp_flags)
अणु
	काष्ठा fotg210_ep *ep;
	काष्ठा fotg210_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक request = 0;

	ep = container_of(_ep, काष्ठा fotg210_ep, ep);
	req = container_of(_req, काष्ठा fotg210_request, req);

	अगर (ep->fotg210->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&ep->fotg210->lock, flags);

	अगर (list_empty(&ep->queue))
		request = 1;

	list_add_tail(&req->queue, &ep->queue);

	req->req.actual = 0;
	req->req.status = -EINPROGRESS;

	अगर (!ep->epnum) /* ep0 */
		fotg210_ep0_queue(ep, req);
	अन्यथा अगर (request && !ep->stall)
		fotg210_enable_fअगरo_पूर्णांक(ep);

	spin_unlock_irqrestore(&ep->fotg210->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fotg210_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा fotg210_ep *ep;
	काष्ठा fotg210_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा fotg210_ep, ep);
	req = container_of(_req, काष्ठा fotg210_request, req);

	spin_lock_irqsave(&ep->fotg210->lock, flags);
	अगर (!list_empty(&ep->queue))
		fotg210_करोne(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&ep->fotg210->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम fotg210_set_epnstall(काष्ठा fotg210_ep *ep)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 value;
	व्योम __iomem *reg;

	/* check अगर IN FIFO is empty beक्रमe stall */
	अगर (ep->dir_in) अणु
		करो अणु
			value = ioपढ़ो32(fotg210->reg + FOTG210_DCFESR);
		पूर्ण जबतक (!(value & DCFESR_FIFO_EMPTY(ep->epnum - 1)));
	पूर्ण

	reg = (ep->dir_in) ?
		fotg210->reg + FOTG210_INEPMPSR(ep->epnum) :
		fotg210->reg + FOTG210_OUTEPMPSR(ep->epnum);
	value = ioपढ़ो32(reg);
	value |= INOUTEPMPSR_STL_EP;
	ioग_लिखो32(value, reg);
पूर्ण

अटल व्योम fotg210_clear_epnstall(काष्ठा fotg210_ep *ep)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 value;
	व्योम __iomem *reg;

	reg = (ep->dir_in) ?
		fotg210->reg + FOTG210_INEPMPSR(ep->epnum) :
		fotg210->reg + FOTG210_OUTEPMPSR(ep->epnum);
	value = ioपढ़ो32(reg);
	value &= ~INOUTEPMPSR_STL_EP;
	ioग_लिखो32(value, reg);
पूर्ण

अटल पूर्णांक fotg210_set_halt_and_wedge(काष्ठा usb_ep *_ep, पूर्णांक value, पूर्णांक wedge)
अणु
	काष्ठा fotg210_ep *ep;
	काष्ठा fotg210_udc *fotg210;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा fotg210_ep, ep);

	fotg210 = ep->fotg210;

	spin_lock_irqsave(&ep->fotg210->lock, flags);

	अगर (value) अणु
		fotg210_set_epnstall(ep);
		ep->stall = 1;
		अगर (wedge)
			ep->wedged = 1;
	पूर्ण अन्यथा अणु
		fotg210_reset_tseq(fotg210, ep->epnum);
		fotg210_clear_epnstall(ep);
		ep->stall = 0;
		ep->wedged = 0;
		अगर (!list_empty(&ep->queue))
			fotg210_enable_fअगरo_पूर्णांक(ep);
	पूर्ण

	spin_unlock_irqrestore(&ep->fotg210->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक fotg210_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस fotg210_set_halt_and_wedge(_ep, value, 0);
पूर्ण

अटल पूर्णांक fotg210_ep_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस fotg210_set_halt_and_wedge(_ep, 1, 1);
पूर्ण

अटल व्योम fotg210_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops fotg210_ep_ops = अणु
	.enable		= fotg210_ep_enable,
	.disable	= fotg210_ep_disable,

	.alloc_request	= fotg210_ep_alloc_request,
	.मुक्त_request	= fotg210_ep_मुक्त_request,

	.queue		= fotg210_ep_queue,
	.dequeue	= fotg210_ep_dequeue,

	.set_halt	= fotg210_ep_set_halt,
	.fअगरo_flush	= fotg210_ep_fअगरo_flush,
	.set_wedge	= fotg210_ep_set_wedge,
पूर्ण;

अटल व्योम fotg210_clear_tx0byte(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_TX0BYTE);

	value &= ~(TX0BYTE_EP1 | TX0BYTE_EP2 | TX0BYTE_EP3
		   | TX0BYTE_EP4);
	ioग_लिखो32(value, fotg210->reg + FOTG210_TX0BYTE);
पूर्ण

अटल व्योम fotg210_clear_rx0byte(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_RX0BYTE);

	value &= ~(RX0BYTE_EP1 | RX0BYTE_EP2 | RX0BYTE_EP3
		   | RX0BYTE_EP4);
	ioग_लिखो32(value, fotg210->reg + FOTG210_RX0BYTE);
पूर्ण

/* पढ़ो 8-byte setup packet only */
अटल व्योम fotg210_rdsetupp(काष्ठा fotg210_udc *fotg210,
		   u8 *buffer)
अणु
	पूर्णांक i = 0;
	u8 *पंचांगp = buffer;
	u32 data;
	u32 length = 8;

	ioग_लिखो32(DMATFNR_ACC_CXF, fotg210->reg + FOTG210_DMATFNR);

	क्रम (i = (length >> 2); i > 0; i--) अणु
		data = ioपढ़ो32(fotg210->reg + FOTG210_CXPORT);
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		*(पंचांगp + 2) = (data >> 16) & 0xFF;
		*(पंचांगp + 3) = (data >> 24) & 0xFF;
		पंचांगp = पंचांगp + 4;
	पूर्ण

	चयन (length % 4) अणु
	हाल 1:
		data = ioपढ़ो32(fotg210->reg + FOTG210_CXPORT);
		*पंचांगp = data & 0xFF;
		अवरोध;
	हाल 2:
		data = ioपढ़ो32(fotg210->reg + FOTG210_CXPORT);
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		अवरोध;
	हाल 3:
		data = ioपढ़ो32(fotg210->reg + FOTG210_CXPORT);
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		*(पंचांगp + 2) = (data >> 16) & 0xFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ioग_लिखो32(DMATFNR_DISDMA, fotg210->reg + FOTG210_DMATFNR);
पूर्ण

अटल व्योम fotg210_set_configuration(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_DAR);

	value |= DAR_AFT_CONF;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DAR);
पूर्ण

अटल व्योम fotg210_set_dev_addr(काष्ठा fotg210_udc *fotg210, u32 addr)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_DAR);

	value |= (addr & 0x7F);
	ioग_लिखो32(value, fotg210->reg + FOTG210_DAR);
पूर्ण

अटल व्योम fotg210_set_cxstall(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_DCFESR);

	value |= DCFESR_CX_STL;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DCFESR);
पूर्ण

अटल व्योम fotg210_request_error(काष्ठा fotg210_udc *fotg210)
अणु
	fotg210_set_cxstall(fotg210);
	pr_err("request error!!\n");
पूर्ण

अटल व्योम fotg210_set_address(काष्ठा fotg210_udc *fotg210,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	अगर (ctrl->wValue >= 0x0100) अणु
		fotg210_request_error(fotg210);
	पूर्ण अन्यथा अणु
		fotg210_set_dev_addr(fotg210, ctrl->wValue);
		fotg210_set_cxकरोne(fotg210);
	पूर्ण
पूर्ण

अटल व्योम fotg210_set_feature(काष्ठा fotg210_udc *fotg210,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		fotg210_set_cxकरोne(fotg210);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		fotg210_set_cxकरोne(fotg210);
		अवरोध;
	हाल USB_RECIP_ENDPOINT: अणु
		u8 epnum;
		epnum = le16_to_cpu(ctrl->wIndex) & USB_ENDPOINT_NUMBER_MASK;
		अगर (epnum)
			fotg210_set_epnstall(fotg210->ep[epnum]);
		अन्यथा
			fotg210_set_cxstall(fotg210);
		fotg210_set_cxकरोne(fotg210);
		पूर्ण
		अवरोध;
	शेष:
		fotg210_request_error(fotg210);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fotg210_clear_feature(काष्ठा fotg210_udc *fotg210,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा fotg210_ep *ep =
		fotg210->ep[ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK];

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		fotg210_set_cxकरोne(fotg210);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		fotg210_set_cxकरोne(fotg210);
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		अगर (ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK) अणु
			अगर (ep->wedged) अणु
				fotg210_set_cxकरोne(fotg210);
				अवरोध;
			पूर्ण
			अगर (ep->stall)
				fotg210_set_halt_and_wedge(&ep->ep, 0, 0);
		पूर्ण
		fotg210_set_cxकरोne(fotg210);
		अवरोध;
	शेष:
		fotg210_request_error(fotg210);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक fotg210_is_epnstall(काष्ठा fotg210_ep *ep)
अणु
	काष्ठा fotg210_udc *fotg210 = ep->fotg210;
	u32 value;
	व्योम __iomem *reg;

	reg = (ep->dir_in) ?
		fotg210->reg + FOTG210_INEPMPSR(ep->epnum) :
		fotg210->reg + FOTG210_OUTEPMPSR(ep->epnum);
	value = ioपढ़ो32(reg);
	वापस value & INOUTEPMPSR_STL_EP ? 1 : 0;
पूर्ण

अटल व्योम fotg210_get_status(काष्ठा fotg210_udc *fotg210,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	u8 epnum;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		fotg210->ep0_data = 1 << USB_DEVICE_SELF_POWERED;
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		fotg210->ep0_data = 0;
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		epnum = ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK;
		अगर (epnum)
			fotg210->ep0_data =
				fotg210_is_epnstall(fotg210->ep[epnum])
				<< USB_ENDPOINT_HALT;
		अन्यथा
			fotg210_request_error(fotg210);
		अवरोध;

	शेष:
		fotg210_request_error(fotg210);
		वापस;		/* निकास */
	पूर्ण

	fotg210->ep0_req->buf = &fotg210->ep0_data;
	fotg210->ep0_req->length = 2;

	spin_unlock(&fotg210->lock);
	fotg210_ep_queue(fotg210->gadget.ep0, fotg210->ep0_req, GFP_ATOMIC);
	spin_lock(&fotg210->lock);
पूर्ण

अटल पूर्णांक fotg210_setup_packet(काष्ठा fotg210_udc *fotg210,
				काष्ठा usb_ctrlrequest *ctrl)
अणु
	u8 *p = (u8 *)ctrl;
	u8 ret = 0;

	fotg210_rdsetupp(fotg210, p);

	fotg210->ep[0]->dir_in = ctrl->bRequestType & USB_सूची_IN;

	अगर (fotg210->gadget.speed == USB_SPEED_UNKNOWN) अणु
		u32 value = ioपढ़ो32(fotg210->reg + FOTG210_DMCR);
		fotg210->gadget.speed = value & DMCR_HS_EN ?
				USB_SPEED_HIGH : USB_SPEED_FULL;
	पूर्ण

	/* check request */
	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (ctrl->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			fotg210_get_status(fotg210, ctrl);
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE:
			fotg210_clear_feature(fotg210, ctrl);
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			fotg210_set_feature(fotg210, ctrl);
			अवरोध;
		हाल USB_REQ_SET_ADDRESS:
			fotg210_set_address(fotg210, ctrl);
			अवरोध;
		हाल USB_REQ_SET_CONFIGURATION:
			fotg210_set_configuration(fotg210);
			ret = 1;
			अवरोध;
		शेष:
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम fotg210_ep0out(काष्ठा fotg210_udc *fotg210)
अणु
	काष्ठा fotg210_ep *ep = fotg210->ep[0];

	अगर (!list_empty(&ep->queue) && !ep->dir_in) अणु
		काष्ठा fotg210_request *req;

		req = list_first_entry(&ep->queue,
			काष्ठा fotg210_request, queue);

		अगर (req->req.length)
			fotg210_start_dma(ep, req);

		अगर ((req->req.length - req->req.actual) < ep->ep.maxpacket)
			fotg210_करोne(ep, req, 0);
	पूर्ण अन्यथा अणु
		pr_err("%s : empty queue\n", __func__);
	पूर्ण
पूर्ण

अटल व्योम fotg210_ep0in(काष्ठा fotg210_udc *fotg210)
अणु
	काष्ठा fotg210_ep *ep = fotg210->ep[0];

	अगर ((!list_empty(&ep->queue)) && (ep->dir_in)) अणु
		काष्ठा fotg210_request *req;

		req = list_entry(ep->queue.next,
				काष्ठा fotg210_request, queue);

		अगर (req->req.length)
			fotg210_start_dma(ep, req);

		अगर (req->req.actual == req->req.length)
			fotg210_करोne(ep, req, 0);
	पूर्ण अन्यथा अणु
		fotg210_set_cxकरोne(fotg210);
	पूर्ण
पूर्ण

अटल व्योम fotg210_clear_comabt_पूर्णांक(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value = ioपढ़ो32(fotg210->reg + FOTG210_DISGR0);

	value &= ~DISGR0_CX_COMABT_INT;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DISGR0);
पूर्ण

अटल व्योम fotg210_in_fअगरo_handler(काष्ठा fotg210_ep *ep)
अणु
	काष्ठा fotg210_request *req = list_entry(ep->queue.next,
					काष्ठा fotg210_request, queue);

	अगर (req->req.length)
		fotg210_start_dma(ep, req);
	fotg210_करोne(ep, req, 0);
पूर्ण

अटल व्योम fotg210_out_fअगरo_handler(काष्ठा fotg210_ep *ep)
अणु
	काष्ठा fotg210_request *req = list_entry(ep->queue.next,
						 काष्ठा fotg210_request, queue);
	पूर्णांक disgr1 = ioपढ़ो32(ep->fotg210->reg + FOTG210_DISGR1);

	fotg210_start_dma(ep, req);

	/* Complete the request when it's full or a लघु packet arrived.
	 * Like other drivers, लघु_not_ok isn't handled.
	 */

	अगर (req->req.length == req->req.actual ||
	    (disgr1 & DISGR1_SPK_INT(ep->epnum - 1)))
		fotg210_करोne(ep, req, 0);
पूर्ण

अटल irqवापस_t fotg210_irq(पूर्णांक irq, व्योम *_fotg210)
अणु
	काष्ठा fotg210_udc *fotg210 = _fotg210;
	u32 पूर्णांक_grp = ioपढ़ो32(fotg210->reg + FOTG210_DIGR);
	u32 पूर्णांक_msk = ioपढ़ो32(fotg210->reg + FOTG210_DMIGR);

	पूर्णांक_grp &= ~पूर्णांक_msk;

	spin_lock(&fotg210->lock);

	अगर (पूर्णांक_grp & DIGR_INT_G2) अणु
		व्योम __iomem *reg = fotg210->reg + FOTG210_DISGR2;
		u32 पूर्णांक_grp2 = ioपढ़ो32(reg);
		u32 पूर्णांक_msk2 = ioपढ़ो32(fotg210->reg + FOTG210_DMISGR2);
		u32 value;

		पूर्णांक_grp2 &= ~पूर्णांक_msk2;

		अगर (पूर्णांक_grp2 & DISGR2_USBRST_INT) अणु
			usb_gadget_udc_reset(&fotg210->gadget,
					     fotg210->driver);
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_USBRST_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 udc reset\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_SUSP_INT) अणु
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_SUSP_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 udc suspend\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_RESM_INT) अणु
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_RESM_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 udc resume\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_ISO_SEQ_ERR_INT) अणु
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_ISO_SEQ_ERR_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 iso sequence error\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_ISO_SEQ_ABORT_INT) अणु
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_ISO_SEQ_ABORT_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 iso sequence abort\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_TX0BYTE_INT) अणु
			fotg210_clear_tx0byte(fotg210);
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_TX0BYTE_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 transferred 0 byte\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_RX0BYTE_INT) अणु
			fotg210_clear_rx0byte(fotg210);
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_RX0BYTE_INT;
			ioग_लिखो32(value, reg);
			pr_info("fotg210 received 0 byte\n");
		पूर्ण
		अगर (पूर्णांक_grp2 & DISGR2_DMA_ERROR) अणु
			value = ioपढ़ो32(reg);
			value &= ~DISGR2_DMA_ERROR;
			ioग_लिखो32(value, reg);
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_grp & DIGR_INT_G0) अणु
		व्योम __iomem *reg = fotg210->reg + FOTG210_DISGR0;
		u32 पूर्णांक_grp0 = ioपढ़ो32(reg);
		u32 पूर्णांक_msk0 = ioपढ़ो32(fotg210->reg + FOTG210_DMISGR0);
		काष्ठा usb_ctrlrequest ctrl;

		पूर्णांक_grp0 &= ~पूर्णांक_msk0;

		/* the highest priority in this source रेजिस्टर */
		अगर (पूर्णांक_grp0 & DISGR0_CX_COMABT_INT) अणु
			fotg210_clear_comabt_पूर्णांक(fotg210);
			pr_info("fotg210 CX command abort\n");
		पूर्ण

		अगर (पूर्णांक_grp0 & DISGR0_CX_SETUP_INT) अणु
			अगर (fotg210_setup_packet(fotg210, &ctrl)) अणु
				spin_unlock(&fotg210->lock);
				अगर (fotg210->driver->setup(&fotg210->gadget,
							   &ctrl) < 0)
					fotg210_set_cxstall(fotg210);
				spin_lock(&fotg210->lock);
			पूर्ण
		पूर्ण
		अगर (पूर्णांक_grp0 & DISGR0_CX_COMEND_INT)
			pr_info("fotg210 cmd end\n");

		अगर (पूर्णांक_grp0 & DISGR0_CX_IN_INT)
			fotg210_ep0in(fotg210);

		अगर (पूर्णांक_grp0 & DISGR0_CX_OUT_INT)
			fotg210_ep0out(fotg210);

		अगर (पूर्णांक_grp0 & DISGR0_CX_COMFAIL_INT) अणु
			fotg210_set_cxstall(fotg210);
			pr_info("fotg210 ep0 fail\n");
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_grp & DIGR_INT_G1) अणु
		व्योम __iomem *reg = fotg210->reg + FOTG210_DISGR1;
		u32 पूर्णांक_grp1 = ioपढ़ो32(reg);
		u32 पूर्णांक_msk1 = ioपढ़ो32(fotg210->reg + FOTG210_DMISGR1);
		पूर्णांक fअगरo;

		पूर्णांक_grp1 &= ~पूर्णांक_msk1;

		क्रम (fअगरo = 0; fअगरo < FOTG210_MAX_FIFO_NUM; fअगरo++) अणु
			अगर (पूर्णांक_grp1 & DISGR1_IN_INT(fअगरo))
				fotg210_in_fअगरo_handler(fotg210->ep[fअगरo + 1]);

			अगर ((पूर्णांक_grp1 & DISGR1_OUT_INT(fअगरo)) ||
			    (पूर्णांक_grp1 & DISGR1_SPK_INT(fअगरo)))
				fotg210_out_fअगरo_handler(fotg210->ep[fअगरo + 1]);
		पूर्ण
	पूर्ण

	spin_unlock(&fotg210->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fotg210_disable_unplug(काष्ठा fotg210_udc *fotg210)
अणु
	u32 reg = ioपढ़ो32(fotg210->reg + FOTG210_PHYTMSR);

	reg &= ~PHYTMSR_UNPLUG;
	ioग_लिखो32(reg, fotg210->reg + FOTG210_PHYTMSR);
पूर्ण

अटल पूर्णांक fotg210_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा fotg210_udc *fotg210 = gadget_to_fotg210(g);
	u32 value;

	/* hook up the driver */
	driver->driver.bus = शून्य;
	fotg210->driver = driver;

	/* enable device global पूर्णांकerrupt */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMCR);
	value |= DMCR_GLINT_EN;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMCR);

	वापस 0;
पूर्ण

अटल व्योम fotg210_init(काष्ठा fotg210_udc *fotg210)
अणु
	u32 value;

	/* disable global पूर्णांकerrupt and set पूर्णांक polarity to active high */
	ioग_लिखो32(GMIR_MHC_INT | GMIR_MOTG_INT | GMIR_INT_POLARITY,
		  fotg210->reg + FOTG210_GMIR);

	/* disable device global पूर्णांकerrupt */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMCR);
	value &= ~DMCR_GLINT_EN;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMCR);

	/* enable only grp2 irqs we handle */
	ioग_लिखो32(~(DISGR2_DMA_ERROR | DISGR2_RX0BYTE_INT | DISGR2_TX0BYTE_INT
		    | DISGR2_ISO_SEQ_ABORT_INT | DISGR2_ISO_SEQ_ERR_INT
		    | DISGR2_RESM_INT | DISGR2_SUSP_INT | DISGR2_USBRST_INT),
		  fotg210->reg + FOTG210_DMISGR2);

	/* disable all fअगरo पूर्णांकerrupt */
	ioग_लिखो32(~(u32)0, fotg210->reg + FOTG210_DMISGR1);

	/* disable cmd end */
	value = ioपढ़ो32(fotg210->reg + FOTG210_DMISGR0);
	value |= DMISGR0_MCX_COMEND;
	ioग_लिखो32(value, fotg210->reg + FOTG210_DMISGR0);
पूर्ण

अटल पूर्णांक fotg210_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा fotg210_udc *fotg210 = gadget_to_fotg210(g);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&fotg210->lock, flags);

	fotg210_init(fotg210);
	fotg210->driver = शून्य;

	spin_unlock_irqrestore(&fotg210->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops fotg210_gadget_ops = अणु
	.udc_start		= fotg210_udc_start,
	.udc_stop		= fotg210_udc_stop,
पूर्ण;

अटल पूर्णांक fotg210_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fotg210_udc *fotg210 = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	usb_del_gadget_udc(&fotg210->gadget);
	iounmap(fotg210->reg);
	मुक्त_irq(platक्रमm_get_irq(pdev, 0), fotg210);

	fotg210_ep_मुक्त_request(&fotg210->ep[0]->ep, fotg210->ep0_req);
	क्रम (i = 0; i < FOTG210_MAX_NUM_EP; i++)
		kमुक्त(fotg210->ep[i]);
	kमुक्त(fotg210);

	वापस 0;
पूर्ण

अटल पूर्णांक fotg210_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res, *ires;
	काष्ठा fotg210_udc *fotg210 = शून्य;
	काष्ठा fotg210_ep *_ep[FOTG210_MAX_NUM_EP];
	पूर्णांक ret = 0;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		pr_err("platform_get_resource error.\n");
		वापस -ENODEV;
	पूर्ण

	ires = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!ires) अणु
		pr_err("platform_get_resource IORESOURCE_IRQ error.\n");
		वापस -ENODEV;
	पूर्ण

	ret = -ENOMEM;

	/* initialize udc */
	fotg210 = kzalloc(माप(काष्ठा fotg210_udc), GFP_KERNEL);
	अगर (fotg210 == शून्य)
		जाओ err;

	क्रम (i = 0; i < FOTG210_MAX_NUM_EP; i++) अणु
		_ep[i] = kzalloc(माप(काष्ठा fotg210_ep), GFP_KERNEL);
		अगर (_ep[i] == शून्य)
			जाओ err_alloc;
		fotg210->ep[i] = _ep[i];
	पूर्ण

	fotg210->reg = ioremap(res->start, resource_size(res));
	अगर (fotg210->reg == शून्य) अणु
		pr_err("ioremap error.\n");
		जाओ err_alloc;
	पूर्ण

	spin_lock_init(&fotg210->lock);

	platक्रमm_set_drvdata(pdev, fotg210);

	fotg210->gadget.ops = &fotg210_gadget_ops;

	fotg210->gadget.max_speed = USB_SPEED_HIGH;
	fotg210->gadget.dev.parent = &pdev->dev;
	fotg210->gadget.dev.dma_mask = pdev->dev.dma_mask;
	fotg210->gadget.name = udc_name;

	INIT_LIST_HEAD(&fotg210->gadget.ep_list);

	क्रम (i = 0; i < FOTG210_MAX_NUM_EP; i++) अणु
		काष्ठा fotg210_ep *ep = fotg210->ep[i];

		अगर (i) अणु
			INIT_LIST_HEAD(&fotg210->ep[i]->ep.ep_list);
			list_add_tail(&fotg210->ep[i]->ep.ep_list,
				      &fotg210->gadget.ep_list);
		पूर्ण
		ep->fotg210 = fotg210;
		INIT_LIST_HEAD(&ep->queue);
		ep->ep.name = fotg210_ep_name[i];
		ep->ep.ops = &fotg210_ep_ops;
		usb_ep_set_maxpacket_limit(&ep->ep, (अचिन्हित लघु) ~0);

		अगर (i == 0) अणु
			ep->ep.caps.type_control = true;
		पूर्ण अन्यथा अणु
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_पूर्णांक = true;
		पूर्ण

		ep->ep.caps.dir_in = true;
		ep->ep.caps.dir_out = true;
	पूर्ण
	usb_ep_set_maxpacket_limit(&fotg210->ep[0]->ep, 0x40);
	fotg210->gadget.ep0 = &fotg210->ep[0]->ep;
	INIT_LIST_HEAD(&fotg210->gadget.ep0->ep_list);

	fotg210->ep0_req = fotg210_ep_alloc_request(&fotg210->ep[0]->ep,
				GFP_KERNEL);
	अगर (fotg210->ep0_req == शून्य)
		जाओ err_map;

	fotg210_init(fotg210);

	fotg210_disable_unplug(fotg210);

	ret = request_irq(ires->start, fotg210_irq, IRQF_SHARED,
			  udc_name, fotg210);
	अगर (ret < 0) अणु
		pr_err("request_irq error (%d)\n", ret);
		जाओ err_req;
	पूर्ण

	ret = usb_add_gadget_udc(&pdev->dev, &fotg210->gadget);
	अगर (ret)
		जाओ err_add_udc;

	dev_info(&pdev->dev, "version %s\n", DRIVER_VERSION);

	वापस 0;

err_add_udc:
	मुक्त_irq(ires->start, fotg210);

err_req:
	fotg210_ep_मुक्त_request(&fotg210->ep[0]->ep, fotg210->ep0_req);

err_map:
	iounmap(fotg210->reg);

err_alloc:
	क्रम (i = 0; i < FOTG210_MAX_NUM_EP; i++)
		kमुक्त(fotg210->ep[i]);
	kमुक्त(fotg210);

err:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver fotg210_driver = अणु
	.driver		= अणु
		.name =	udc_name,
	पूर्ण,
	.probe		= fotg210_udc_probe,
	.हटाओ		= fotg210_udc_हटाओ,
पूर्ण;

module_platक्रमm_driver(fotg210_driver);

MODULE_AUTHOR("Yuan-Hsin Chen, Feng-Hsin Chiang <john453@faraday-tech.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
