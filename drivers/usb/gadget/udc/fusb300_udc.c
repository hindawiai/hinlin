<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fusb300 UDC (USB gadget)
 *
 * Copyright (C) 2010 Faraday Technology Corp.
 *
 * Author : Yuan-hsin Chen <yhchen@faraday-tech.com>
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश "fusb300_udc.h"

MODULE_DESCRIPTION("FUSB300  USB gadget driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yuan-Hsin Chen, Feng-Hsin Chiang <john453@faraday-tech.com>");
MODULE_ALIAS("platform:fusb300_udc");

#घोषणा DRIVER_VERSION	"20 October 2010"

अटल स्थिर अक्षर udc_name[] = "fusb300_udc";
अटल स्थिर अक्षर * स्थिर fusb300_ep_name[] = अणु
	"ep0", "ep1", "ep2", "ep3", "ep4", "ep5", "ep6", "ep7", "ep8", "ep9",
	"ep10", "ep11", "ep12", "ep13", "ep14", "ep15"
पूर्ण;

अटल व्योम करोne(काष्ठा fusb300_ep *ep, काष्ठा fusb300_request *req,
		 पूर्णांक status);

अटल व्योम fusb300_enable_bit(काष्ठा fusb300 *fusb300, u32 offset,
			       u32 value)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + offset);

	reg |= value;
	ioग_लिखो32(reg, fusb300->reg + offset);
पूर्ण

अटल व्योम fusb300_disable_bit(काष्ठा fusb300 *fusb300, u32 offset,
				u32 value)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + offset);

	reg &= ~value;
	ioग_लिखो32(reg, fusb300->reg + offset);
पूर्ण


अटल व्योम fusb300_ep_setting(काष्ठा fusb300_ep *ep,
			       काष्ठा fusb300_ep_info info)
अणु
	ep->epnum = info.epnum;
	ep->type = info.type;
पूर्ण

अटल पूर्णांक fusb300_ep_release(काष्ठा fusb300_ep *ep)
अणु
	अगर (!ep->epnum)
		वापस 0;
	ep->epnum = 0;
	ep->stall = 0;
	ep->wedged = 0;
	वापस 0;
पूर्ण

अटल व्योम fusb300_set_fअगरo_entry(काष्ठा fusb300 *fusb300,
				   u32 ep)
अणु
	u32 val = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(ep));

	val &= ~FUSB300_EPSET1_FIFOENTRY_MSK;
	val |= FUSB300_EPSET1_FIFOENTRY(FUSB300_FIFO_ENTRY_NUM);
	ioग_लिखो32(val, fusb300->reg + FUSB300_OFFSET_EPSET1(ep));
पूर्ण

अटल व्योम fusb300_set_start_entry(काष्ठा fusb300 *fusb300,
				    u8 ep)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(ep));
	u32 start_entry = fusb300->fअगरo_entry_num * FUSB300_FIFO_ENTRY_NUM;

	reg &= ~FUSB300_EPSET1_START_ENTRY_MSK	;
	reg |= FUSB300_EPSET1_START_ENTRY(start_entry);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(ep));
	अगर (fusb300->fअगरo_entry_num == FUSB300_MAX_FIFO_ENTRY) अणु
		fusb300->fअगरo_entry_num = 0;
		fusb300->addrofs = 0;
		pr_err("fifo entry is over the maximum number!\n");
	पूर्ण अन्यथा
		fusb300->fअगरo_entry_num++;
पूर्ण

/* set fusb300_set_start_entry first beक्रमe fusb300_set_epaddrofs */
अटल व्योम fusb300_set_epaddrofs(काष्ठा fusb300 *fusb300,
				  काष्ठा fusb300_ep_info info)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET2(info.epnum));

	reg &= ~FUSB300_EPSET2_ADDROFS_MSK;
	reg |= FUSB300_EPSET2_ADDROFS(fusb300->addrofs);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET2(info.epnum));
	fusb300->addrofs += (info.maxpacket + 7) / 8 * FUSB300_FIFO_ENTRY_NUM;
पूर्ण

अटल व्योम ep_fअगरo_setting(काष्ठा fusb300 *fusb300,
			    काष्ठा fusb300_ep_info info)
अणु
	fusb300_set_fअगरo_entry(fusb300, info.epnum);
	fusb300_set_start_entry(fusb300, info.epnum);
	fusb300_set_epaddrofs(fusb300, info);
पूर्ण

अटल व्योम fusb300_set_eptype(काष्ठा fusb300 *fusb300,
			       काष्ठा fusb300_ep_info info)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));

	reg &= ~FUSB300_EPSET1_TYPE_MSK;
	reg |= FUSB300_EPSET1_TYPE(info.type);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));
पूर्ण

अटल व्योम fusb300_set_epdir(काष्ठा fusb300 *fusb300,
			      काष्ठा fusb300_ep_info info)
अणु
	u32 reg;

	अगर (!info.dir_in)
		वापस;
	reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));
	reg &= ~FUSB300_EPSET1_सूची_MSK;
	reg |= FUSB300_EPSET1_सूचीIN;
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));
पूर्ण

अटल व्योम fusb300_set_ep_active(काष्ठा fusb300 *fusb300,
			  u8 ep)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(ep));

	reg |= FUSB300_EPSET1_ACTEN;
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(ep));
पूर्ण

अटल व्योम fusb300_set_epmps(काष्ठा fusb300 *fusb300,
			      काष्ठा fusb300_ep_info info)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET2(info.epnum));

	reg &= ~FUSB300_EPSET2_MPS_MSK;
	reg |= FUSB300_EPSET2_MPS(info.maxpacket);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET2(info.epnum));
पूर्ण

अटल व्योम fusb300_set_पूर्णांकerval(काष्ठा fusb300 *fusb300,
				 काष्ठा fusb300_ep_info info)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));

	reg &= ~FUSB300_EPSET1_INTERVAL(0x7);
	reg |= FUSB300_EPSET1_INTERVAL(info.पूर्णांकerval);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));
पूर्ण

अटल व्योम fusb300_set_bwnum(काष्ठा fusb300 *fusb300,
			      काष्ठा fusb300_ep_info info)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));

	reg &= ~FUSB300_EPSET1_BWNUM(0x3);
	reg |= FUSB300_EPSET1_BWNUM(info.bw_num);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(info.epnum));
पूर्ण

अटल व्योम set_ep_reg(काष्ठा fusb300 *fusb300,
		      काष्ठा fusb300_ep_info info)
अणु
	fusb300_set_eptype(fusb300, info);
	fusb300_set_epdir(fusb300, info);
	fusb300_set_epmps(fusb300, info);

	अगर (info.पूर्णांकerval)
		fusb300_set_पूर्णांकerval(fusb300, info);

	अगर (info.bw_num)
		fusb300_set_bwnum(fusb300, info);

	fusb300_set_ep_active(fusb300, info.epnum);
पूर्ण

अटल पूर्णांक config_ep(काष्ठा fusb300_ep *ep,
		     स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा fusb300 *fusb300 = ep->fusb300;
	काष्ठा fusb300_ep_info info;

	ep->ep.desc = desc;

	info.पूर्णांकerval = 0;
	info.addrofs = 0;
	info.bw_num = 0;

	info.type = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
	info.dir_in = (desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) ? 1 : 0;
	info.maxpacket = usb_endpoपूर्णांक_maxp(desc);
	info.epnum = desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK;

	अगर ((info.type == USB_ENDPOINT_XFER_INT) ||
	   (info.type == USB_ENDPOINT_XFER_ISOC)) अणु
		info.पूर्णांकerval = desc->bInterval;
		अगर (info.type == USB_ENDPOINT_XFER_ISOC)
			info.bw_num = usb_endpoपूर्णांक_maxp_mult(desc);
	पूर्ण

	ep_fअगरo_setting(fusb300, info);

	set_ep_reg(fusb300, info);

	fusb300_ep_setting(ep, info);

	fusb300->ep[info.epnum] = ep;

	वापस 0;
पूर्ण

अटल पूर्णांक fusb300_enable(काष्ठा usb_ep *_ep,
			  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा fusb300_ep *ep;

	ep = container_of(_ep, काष्ठा fusb300_ep, ep);

	अगर (ep->fusb300->reक्रमागत) अणु
		ep->fusb300->fअगरo_entry_num = 0;
		ep->fusb300->addrofs = 0;
		ep->fusb300->reक्रमागत = 0;
	पूर्ण

	वापस config_ep(ep, desc);
पूर्ण

अटल पूर्णांक fusb300_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा fusb300_ep *ep;
	काष्ठा fusb300_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा fusb300_ep, ep);

	BUG_ON(!ep);

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा fusb300_request, queue);
		spin_lock_irqsave(&ep->fusb300->lock, flags);
		करोne(ep, req, -ECONNRESET);
		spin_unlock_irqrestore(&ep->fusb300->lock, flags);
	पूर्ण

	वापस fusb300_ep_release(ep);
पूर्ण

अटल काष्ठा usb_request *fusb300_alloc_request(काष्ठा usb_ep *_ep,
						gfp_t gfp_flags)
अणु
	काष्ठा fusb300_request *req;

	req = kzalloc(माप(काष्ठा fusb300_request), gfp_flags);
	अगर (!req)
		वापस शून्य;
	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम fusb300_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा fusb300_request *req;

	req = container_of(_req, काष्ठा fusb300_request, req);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक enable_fअगरo_पूर्णांक(काष्ठा fusb300_ep *ep)
अणु
	काष्ठा fusb300 *fusb300 = ep->fusb300;

	अगर (ep->epnum) अणु
		fusb300_enable_bit(fusb300, FUSB300_OFFSET_IGER0,
			FUSB300_IGER0_EEPn_FIFO_INT(ep->epnum));
	पूर्ण अन्यथा अणु
		pr_err("can't enable_fifo_int ep0\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक disable_fअगरo_पूर्णांक(काष्ठा fusb300_ep *ep)
अणु
	काष्ठा fusb300 *fusb300 = ep->fusb300;

	अगर (ep->epnum) अणु
		fusb300_disable_bit(fusb300, FUSB300_OFFSET_IGER0,
			FUSB300_IGER0_EEPn_FIFO_INT(ep->epnum));
	पूर्ण अन्यथा अणु
		pr_err("can't disable_fifo_int ep0\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fusb300_set_cxlen(काष्ठा fusb300 *fusb300, u32 length)
अणु
	u32 reg;

	reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_CSR);
	reg &= ~FUSB300_CSR_LEN_MSK;
	reg |= FUSB300_CSR_LEN(length);
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_CSR);
पूर्ण

/* ग_लिखो data to cx fअगरo */
अटल व्योम fusb300_wrcxf(काष्ठा fusb300_ep *ep,
		   काष्ठा fusb300_request *req)
अणु
	पूर्णांक i = 0;
	u8 *पंचांगp;
	u32 data;
	काष्ठा fusb300 *fusb300 = ep->fusb300;
	u32 length = req->req.length - req->req.actual;

	पंचांगp = req->req.buf + req->req.actual;

	अगर (length > SS_CTL_MAX_PACKET_SIZE) अणु
		fusb300_set_cxlen(fusb300, SS_CTL_MAX_PACKET_SIZE);
		क्रम (i = (SS_CTL_MAX_PACKET_SIZE >> 2); i > 0; i--) अणु
			data = *पंचांगp | *(पंचांगp + 1) << 8 | *(पंचांगp + 2) << 16 |
				*(पंचांगp + 3) << 24;
			ioग_लिखो32(data, fusb300->reg + FUSB300_OFFSET_CXPORT);
			पंचांगp += 4;
		पूर्ण
		req->req.actual += SS_CTL_MAX_PACKET_SIZE;
	पूर्ण अन्यथा अणु /* length is less than max packet size */
		fusb300_set_cxlen(fusb300, length);
		क्रम (i = length >> 2; i > 0; i--) अणु
			data = *पंचांगp | *(पंचांगp + 1) << 8 | *(पंचांगp + 2) << 16 |
				*(पंचांगp + 3) << 24;
			prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
			ioग_लिखो32(data, fusb300->reg + FUSB300_OFFSET_CXPORT);
			पंचांगp = पंचांगp + 4;
		पूर्ण
		चयन (length % 4) अणु
		हाल 1:
			data = *पंचांगp;
			prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
			ioग_लिखो32(data, fusb300->reg + FUSB300_OFFSET_CXPORT);
			अवरोध;
		हाल 2:
			data = *पंचांगp | *(पंचांगp + 1) << 8;
			prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
			ioग_लिखो32(data, fusb300->reg + FUSB300_OFFSET_CXPORT);
			अवरोध;
		हाल 3:
			data = *पंचांगp | *(पंचांगp + 1) << 8 | *(पंचांगp + 2) << 16;
			prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
			ioग_लिखो32(data, fusb300->reg + FUSB300_OFFSET_CXPORT);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		req->req.actual += length;
	पूर्ण
पूर्ण

अटल व्योम fusb300_set_epnstall(काष्ठा fusb300 *fusb300, u8 ep)
अणु
	fusb300_enable_bit(fusb300, FUSB300_OFFSET_EPSET0(ep),
		FUSB300_EPSET0_STL);
पूर्ण

अटल व्योम fusb300_clear_epnstall(काष्ठा fusb300 *fusb300, u8 ep)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET0(ep));

	अगर (reg & FUSB300_EPSET0_STL) अणु
		prपूर्णांकk(KERN_DEBUG "EP%d stall... Clear!!\n", ep);
		reg |= FUSB300_EPSET0_STL_CLR;
		ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_EPSET0(ep));
	पूर्ण
पूर्ण

अटल व्योम ep0_queue(काष्ठा fusb300_ep *ep, काष्ठा fusb300_request *req)
अणु
	अगर (ep->fusb300->ep0_dir) अणु /* अगर IN */
		अगर (req->req.length) अणु
			fusb300_wrcxf(ep, req);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_DEBUG "%s : req->req.length = 0x%x\n",
				__func__, req->req.length);
		अगर ((req->req.length == req->req.actual) ||
		    (req->req.actual < ep->ep.maxpacket))
			करोne(ep, req, 0);
	पूर्ण अन्यथा अणु /* OUT */
		अगर (!req->req.length)
			करोne(ep, req, 0);
		अन्यथा
			fusb300_enable_bit(ep->fusb300, FUSB300_OFFSET_IGER1,
				FUSB300_IGER1_CX_OUT_INT);
	पूर्ण
पूर्ण

अटल पूर्णांक fusb300_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			 gfp_t gfp_flags)
अणु
	काष्ठा fusb300_ep *ep;
	काष्ठा fusb300_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक request  = 0;

	ep = container_of(_ep, काष्ठा fusb300_ep, ep);
	req = container_of(_req, काष्ठा fusb300_request, req);

	अगर (ep->fusb300->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	spin_lock_irqsave(&ep->fusb300->lock, flags);

	अगर (list_empty(&ep->queue))
		request = 1;

	list_add_tail(&req->queue, &ep->queue);

	req->req.actual = 0;
	req->req.status = -EINPROGRESS;

	अगर (ep->ep.desc == शून्य) /* ep0 */
		ep0_queue(ep, req);
	अन्यथा अगर (request && !ep->stall)
		enable_fअगरo_पूर्णांक(ep);

	spin_unlock_irqrestore(&ep->fusb300->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fusb300_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा fusb300_ep *ep;
	काष्ठा fusb300_request *req;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा fusb300_ep, ep);
	req = container_of(_req, काष्ठा fusb300_request, req);

	spin_lock_irqsave(&ep->fusb300->lock, flags);
	अगर (!list_empty(&ep->queue))
		करोne(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&ep->fusb300->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक fusb300_set_halt_and_wedge(काष्ठा usb_ep *_ep, पूर्णांक value, पूर्णांक wedge)
अणु
	काष्ठा fusb300_ep *ep;
	काष्ठा fusb300 *fusb300;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	ep = container_of(_ep, काष्ठा fusb300_ep, ep);

	fusb300 = ep->fusb300;

	spin_lock_irqsave(&ep->fusb300->lock, flags);

	अगर (!list_empty(&ep->queue)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (value) अणु
		fusb300_set_epnstall(fusb300, ep->epnum);
		ep->stall = 1;
		अगर (wedge)
			ep->wedged = 1;
	पूर्ण अन्यथा अणु
		fusb300_clear_epnstall(fusb300, ep->epnum);
		ep->stall = 0;
		ep->wedged = 0;
	पूर्ण

out:
	spin_unlock_irqrestore(&ep->fusb300->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक fusb300_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस fusb300_set_halt_and_wedge(_ep, value, 0);
पूर्ण

अटल पूर्णांक fusb300_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस fusb300_set_halt_and_wedge(_ep, 1, 1);
पूर्ण

अटल व्योम fusb300_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops fusb300_ep_ops = अणु
	.enable		= fusb300_enable,
	.disable	= fusb300_disable,

	.alloc_request	= fusb300_alloc_request,
	.मुक्त_request	= fusb300_मुक्त_request,

	.queue		= fusb300_queue,
	.dequeue	= fusb300_dequeue,

	.set_halt	= fusb300_set_halt,
	.fअगरo_flush	= fusb300_fअगरo_flush,
	.set_wedge	= fusb300_set_wedge,
पूर्ण;

/*****************************************************************************/
अटल व्योम fusb300_clear_पूर्णांक(काष्ठा fusb300 *fusb300, u32 offset,
		       u32 value)
अणु
	ioग_लिखो32(value, fusb300->reg + offset);
पूर्ण

अटल व्योम fusb300_reset(व्योम)
अणु
पूर्ण

अटल व्योम fusb300_set_cxstall(काष्ठा fusb300 *fusb300)
अणु
	fusb300_enable_bit(fusb300, FUSB300_OFFSET_CSR,
			   FUSB300_CSR_STL);
पूर्ण

अटल व्योम fusb300_set_cxकरोne(काष्ठा fusb300 *fusb300)
अणु
	fusb300_enable_bit(fusb300, FUSB300_OFFSET_CSR,
			   FUSB300_CSR_DONE);
पूर्ण

/* पढ़ो data from cx fअगरo */
अटल व्योम fusb300_rdcxf(काष्ठा fusb300 *fusb300,
		   u8 *buffer, u32 length)
अणु
	पूर्णांक i = 0;
	u8 *पंचांगp;
	u32 data;

	पंचांगp = buffer;

	क्रम (i = (length >> 2); i > 0; i--) अणु
		data = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_CXPORT);
		prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		*(पंचांगp + 2) = (data >> 16) & 0xFF;
		*(पंचांगp + 3) = (data >> 24) & 0xFF;
		पंचांगp = पंचांगp + 4;
	पूर्ण

	चयन (length % 4) अणु
	हाल 1:
		data = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_CXPORT);
		prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
		*पंचांगp = data & 0xFF;
		अवरोध;
	हाल 2:
		data = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_CXPORT);
		prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		अवरोध;
	हाल 3:
		data = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_CXPORT);
		prपूर्णांकk(KERN_DEBUG "    0x%x\n", data);
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		*(पंचांगp + 2) = (data >> 16) & 0xFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fusb300_rdfअगरo(काष्ठा fusb300_ep *ep,
			  काष्ठा fusb300_request *req,
			  u32 length)
अणु
	पूर्णांक i = 0;
	u8 *पंचांगp;
	u32 data, reg;
	काष्ठा fusb300 *fusb300 = ep->fusb300;

	पंचांगp = req->req.buf + req->req.actual;
	req->req.actual += length;

	अगर (req->req.actual > req->req.length)
		prपूर्णांकk(KERN_DEBUG "req->req.actual > req->req.length\n");

	क्रम (i = (length >> 2); i > 0; i--) अणु
		data = ioपढ़ो32(fusb300->reg +
			FUSB300_OFFSET_EPPORT(ep->epnum));
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		*(पंचांगp + 2) = (data >> 16) & 0xFF;
		*(पंचांगp + 3) = (data >> 24) & 0xFF;
		पंचांगp = पंचांगp + 4;
	पूर्ण

	चयन (length % 4) अणु
	हाल 1:
		data = ioपढ़ो32(fusb300->reg +
			FUSB300_OFFSET_EPPORT(ep->epnum));
		*पंचांगp = data & 0xFF;
		अवरोध;
	हाल 2:
		data = ioपढ़ो32(fusb300->reg +
			FUSB300_OFFSET_EPPORT(ep->epnum));
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		अवरोध;
	हाल 3:
		data = ioपढ़ो32(fusb300->reg +
			FUSB300_OFFSET_EPPORT(ep->epnum));
		*पंचांगp = data & 0xFF;
		*(पंचांगp + 1) = (data >> 8) & 0xFF;
		*(पंचांगp + 2) = (data >> 16) & 0xFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	करो अणु
		reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_IGR1);
		reg &= FUSB300_IGR1_SYNF0_EMPTY_INT;
		अगर (i)
			prपूर्णांकk(KERN_INFO "sync fifo is not empty!\n");
		i++;
	पूर्ण जबतक (!reg);
पूर्ण

अटल u8 fusb300_get_epnstall(काष्ठा fusb300 *fusb300, u8 ep)
अणु
	u8 value;
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPSET0(ep));

	value = reg & FUSB300_EPSET0_STL;

	वापस value;
पूर्ण

अटल u8 fusb300_get_cxstall(काष्ठा fusb300 *fusb300)
अणु
	u8 value;
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_CSR);

	value = (reg & FUSB300_CSR_STL) >> 1;

	वापस value;
पूर्ण

अटल व्योम request_error(काष्ठा fusb300 *fusb300)
अणु
	fusb300_set_cxstall(fusb300);
	prपूर्णांकk(KERN_DEBUG "request error!!\n");
पूर्ण

अटल व्योम get_status(काष्ठा fusb300 *fusb300, काष्ठा usb_ctrlrequest *ctrl)
__releases(fusb300->lock)
__acquires(fusb300->lock)
अणु
	u8 ep;
	u16 status = 0;
	u16 w_index = ctrl->wIndex;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		status = 1 << USB_DEVICE_SELF_POWERED;
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		status = 0;
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		ep = w_index & USB_ENDPOINT_NUMBER_MASK;
		अगर (ep) अणु
			अगर (fusb300_get_epnstall(fusb300, ep))
				status = 1 << USB_ENDPOINT_HALT;
		पूर्ण अन्यथा अणु
			अगर (fusb300_get_cxstall(fusb300))
				status = 0;
		पूर्ण
		अवरोध;

	शेष:
		request_error(fusb300);
		वापस;		/* निकास */
	पूर्ण

	fusb300->ep0_data = cpu_to_le16(status);
	fusb300->ep0_req->buf = &fusb300->ep0_data;
	fusb300->ep0_req->length = 2;

	spin_unlock(&fusb300->lock);
	fusb300_queue(fusb300->gadget.ep0, fusb300->ep0_req, GFP_KERNEL);
	spin_lock(&fusb300->lock);
पूर्ण

अटल व्योम set_feature(काष्ठा fusb300 *fusb300, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u8 ep;

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		fusb300_set_cxकरोne(fusb300);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		fusb300_set_cxकरोne(fusb300);
		अवरोध;
	हाल USB_RECIP_ENDPOINT: अणु
		u16 w_index = le16_to_cpu(ctrl->wIndex);

		ep = w_index & USB_ENDPOINT_NUMBER_MASK;
		अगर (ep)
			fusb300_set_epnstall(fusb300, ep);
		अन्यथा
			fusb300_set_cxstall(fusb300);
		fusb300_set_cxकरोne(fusb300);
		पूर्ण
		अवरोध;
	शेष:
		request_error(fusb300);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fusb300_clear_seqnum(काष्ठा fusb300 *fusb300, u8 ep)
अणु
	fusb300_enable_bit(fusb300, FUSB300_OFFSET_EPSET0(ep),
			    FUSB300_EPSET0_CLRSEQNUM);
पूर्ण

अटल व्योम clear_feature(काष्ठा fusb300 *fusb300, काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा fusb300_ep *ep =
		fusb300->ep[ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK];

	चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		fusb300_set_cxकरोne(fusb300);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		fusb300_set_cxकरोne(fusb300);
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		अगर (ctrl->wIndex & USB_ENDPOINT_NUMBER_MASK) अणु
			अगर (ep->wedged) अणु
				fusb300_set_cxकरोne(fusb300);
				अवरोध;
			पूर्ण
			अगर (ep->stall) अणु
				ep->stall = 0;
				fusb300_clear_seqnum(fusb300, ep->epnum);
				fusb300_clear_epnstall(fusb300, ep->epnum);
				अगर (!list_empty(&ep->queue))
					enable_fअगरo_पूर्णांक(ep);
			पूर्ण
		पूर्ण
		fusb300_set_cxकरोne(fusb300);
		अवरोध;
	शेष:
		request_error(fusb300);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fusb300_set_dev_addr(काष्ठा fusb300 *fusb300, u16 addr)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_DAR);

	reg &= ~FUSB300_DAR_DRVADDR_MSK;
	reg |= FUSB300_DAR_DRVADDR(addr);

	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_DAR);
पूर्ण

अटल व्योम set_address(काष्ठा fusb300 *fusb300, काष्ठा usb_ctrlrequest *ctrl)
अणु
	अगर (ctrl->wValue >= 0x0100)
		request_error(fusb300);
	अन्यथा अणु
		fusb300_set_dev_addr(fusb300, ctrl->wValue);
		fusb300_set_cxकरोne(fusb300);
	पूर्ण
पूर्ण

#घोषणा UVC_COPY_DESCRIPTORS(mem, src) \
	करो अणु \
		स्थिर काष्ठा usb_descriptor_header * स्थिर *__src; \
		क्रम (__src = src; *__src; ++__src) अणु \
			स_नकल(mem, *__src, (*__src)->bLength); \
			mem += (*__src)->bLength; \
		पूर्ण \
	पूर्ण जबतक (0)

अटल पूर्णांक setup_packet(काष्ठा fusb300 *fusb300, काष्ठा usb_ctrlrequest *ctrl)
अणु
	u8 *p = (u8 *)ctrl;
	u8 ret = 0;
	u8 i = 0;

	fusb300_rdcxf(fusb300, p, 8);
	fusb300->ep0_dir = ctrl->bRequestType & USB_सूची_IN;
	fusb300->ep0_length = ctrl->wLength;

	/* check request */
	अगर ((ctrl->bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (ctrl->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			get_status(fusb300, ctrl);
			अवरोध;
		हाल USB_REQ_CLEAR_FEATURE:
			clear_feature(fusb300, ctrl);
			अवरोध;
		हाल USB_REQ_SET_FEATURE:
			set_feature(fusb300, ctrl);
			अवरोध;
		हाल USB_REQ_SET_ADDRESS:
			set_address(fusb300, ctrl);
			अवरोध;
		हाल USB_REQ_SET_CONFIGURATION:
			fusb300_enable_bit(fusb300, FUSB300_OFFSET_DAR,
					   FUSB300_DAR_SETCONFG);
			/* clear sequence number */
			क्रम (i = 1; i <= FUSB300_MAX_NUM_EP; i++)
				fusb300_clear_seqnum(fusb300, i);
			fusb300->reक्रमागत = 1;
			ret = 1;
			अवरोध;
		शेष:
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		ret = 1;

	वापस ret;
पूर्ण

अटल व्योम करोne(काष्ठा fusb300_ep *ep, काष्ठा fusb300_request *req,
		 पूर्णांक status)
अणु
	list_del_init(&req->queue);

	/* करोn't modअगरy queue heads during completion callback */
	अगर (ep->fusb300->gadget.speed == USB_SPEED_UNKNOWN)
		req->req.status = -ESHUTDOWN;
	अन्यथा
		req->req.status = status;

	spin_unlock(&ep->fusb300->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&ep->fusb300->lock);

	अगर (ep->epnum) अणु
		disable_fअगरo_पूर्णांक(ep);
		अगर (!list_empty(&ep->queue))
			enable_fअगरo_पूर्णांक(ep);
	पूर्ण अन्यथा
		fusb300_set_cxकरोne(ep->fusb300);
पूर्ण

अटल व्योम fusb300_fill_idma_prdtbl(काष्ठा fusb300_ep *ep, dma_addr_t d,
		u32 len)
अणु
	u32 value;
	u32 reg;

	/* रुको SW owner */
	करो अणु
		reg = ioपढ़ो32(ep->fusb300->reg +
			FUSB300_OFFSET_EPPRD_W0(ep->epnum));
		reg &= FUSB300_EPPRD0_H;
	पूर्ण जबतक (reg);

	ioग_लिखो32(d, ep->fusb300->reg + FUSB300_OFFSET_EPPRD_W1(ep->epnum));

	value = FUSB300_EPPRD0_BTC(len) | FUSB300_EPPRD0_H |
		FUSB300_EPPRD0_F | FUSB300_EPPRD0_L | FUSB300_EPPRD0_I;
	ioग_लिखो32(value, ep->fusb300->reg + FUSB300_OFFSET_EPPRD_W0(ep->epnum));

	ioग_लिखो32(0x0, ep->fusb300->reg + FUSB300_OFFSET_EPPRD_W2(ep->epnum));

	fusb300_enable_bit(ep->fusb300, FUSB300_OFFSET_EPPRDRDY,
		FUSB300_EPPRDR_EP_PRD_RDY(ep->epnum));
पूर्ण

अटल व्योम fusb300_रुको_idma_finished(काष्ठा fusb300_ep *ep)
अणु
	u32 reg;

	करो अणु
		reg = ioपढ़ो32(ep->fusb300->reg + FUSB300_OFFSET_IGR1);
		अगर ((reg & FUSB300_IGR1_VBUS_CHG_INT) ||
		    (reg & FUSB300_IGR1_WARM_RST_INT) ||
		    (reg & FUSB300_IGR1_HOT_RST_INT) ||
		    (reg & FUSB300_IGR1_USBRST_INT)
		)
			जाओ IDMA_RESET;
		reg = ioपढ़ो32(ep->fusb300->reg + FUSB300_OFFSET_IGR0);
		reg &= FUSB300_IGR0_EPn_PRD_INT(ep->epnum);
	पूर्ण जबतक (!reg);

	fusb300_clear_पूर्णांक(ep->fusb300, FUSB300_OFFSET_IGR0,
		FUSB300_IGR0_EPn_PRD_INT(ep->epnum));
	वापस;

IDMA_RESET:
	reg = ioपढ़ो32(ep->fusb300->reg + FUSB300_OFFSET_IGER0);
	reg &= ~FUSB300_IGER0_EEPn_PRD_INT(ep->epnum);
	ioग_लिखो32(reg, ep->fusb300->reg + FUSB300_OFFSET_IGER0);
पूर्ण

अटल व्योम fusb300_set_idma(काष्ठा fusb300_ep *ep,
			काष्ठा fusb300_request *req)
अणु
	पूर्णांक ret;

	ret = usb_gadget_map_request(&ep->fusb300->gadget,
			&req->req, DMA_TO_DEVICE);
	अगर (ret)
		वापस;

	fusb300_enable_bit(ep->fusb300, FUSB300_OFFSET_IGER0,
		FUSB300_IGER0_EEPn_PRD_INT(ep->epnum));

	fusb300_fill_idma_prdtbl(ep, req->req.dma, req->req.length);
	/* check idma is करोne */
	fusb300_रुको_idma_finished(ep);

	usb_gadget_unmap_request(&ep->fusb300->gadget,
			&req->req, DMA_TO_DEVICE);
पूर्ण

अटल व्योम in_ep_fअगरo_handler(काष्ठा fusb300_ep *ep)
अणु
	काष्ठा fusb300_request *req = list_entry(ep->queue.next,
					काष्ठा fusb300_request, queue);

	अगर (req->req.length)
		fusb300_set_idma(ep, req);
	करोne(ep, req, 0);
पूर्ण

अटल व्योम out_ep_fअगरo_handler(काष्ठा fusb300_ep *ep)
अणु
	काष्ठा fusb300 *fusb300 = ep->fusb300;
	काष्ठा fusb300_request *req = list_entry(ep->queue.next,
						 काष्ठा fusb300_request, queue);
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_EPFFR(ep->epnum));
	u32 length = reg & FUSB300_FFR_BYCNT;

	fusb300_rdfअगरo(ep, req, length);

	/* finish out transfer */
	अगर ((req->req.length == req->req.actual) || (length < ep->ep.maxpacket))
		करोne(ep, req, 0);
पूर्ण

अटल व्योम check_device_mode(काष्ठा fusb300 *fusb300)
अणु
	u32 reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_GCR);

	चयन (reg & FUSB300_GCR_DEVEN_MSK) अणु
	हाल FUSB300_GCR_DEVEN_SS:
		fusb300->gadget.speed = USB_SPEED_SUPER;
		अवरोध;
	हाल FUSB300_GCR_DEVEN_HS:
		fusb300->gadget.speed = USB_SPEED_HIGH;
		अवरोध;
	हाल FUSB300_GCR_DEVEN_FS:
		fusb300->gadget.speed = USB_SPEED_FULL;
		अवरोध;
	शेष:
		fusb300->gadget.speed = USB_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
	prपूर्णांकk(KERN_INFO "dev_mode = %d\n", (reg & FUSB300_GCR_DEVEN_MSK));
पूर्ण


अटल व्योम fusb300_ep0out(काष्ठा fusb300 *fusb300)
अणु
	काष्ठा fusb300_ep *ep = fusb300->ep[0];
	u32 reg;

	अगर (!list_empty(&ep->queue)) अणु
		काष्ठा fusb300_request *req;

		req = list_first_entry(&ep->queue,
			काष्ठा fusb300_request, queue);
		अगर (req->req.length)
			fusb300_rdcxf(ep->fusb300, req->req.buf,
				req->req.length);
		करोne(ep, req, 0);
		reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_IGER1);
		reg &= ~FUSB300_IGER1_CX_OUT_INT;
		ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_IGER1);
	पूर्ण अन्यथा
		pr_err("%s : empty queue\n", __func__);
पूर्ण

अटल व्योम fusb300_ep0in(काष्ठा fusb300 *fusb300)
अणु
	काष्ठा fusb300_request *req;
	काष्ठा fusb300_ep *ep = fusb300->ep[0];

	अगर ((!list_empty(&ep->queue)) && (fusb300->ep0_dir)) अणु
		req = list_entry(ep->queue.next,
				काष्ठा fusb300_request, queue);
		अगर (req->req.length)
			fusb300_wrcxf(ep, req);
		अगर ((req->req.length - req->req.actual) < ep->ep.maxpacket)
			करोne(ep, req, 0);
	पूर्ण अन्यथा
		fusb300_set_cxकरोne(fusb300);
पूर्ण

अटल व्योम fusb300_grp2_handler(व्योम)
अणु
पूर्ण

अटल व्योम fusb300_grp3_handler(व्योम)
अणु
पूर्ण

अटल व्योम fusb300_grp4_handler(व्योम)
अणु
पूर्ण

अटल व्योम fusb300_grp5_handler(व्योम)
अणु
पूर्ण

अटल irqवापस_t fusb300_irq(पूर्णांक irq, व्योम *_fusb300)
अणु
	काष्ठा fusb300 *fusb300 = _fusb300;
	u32 पूर्णांक_grp1 = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_IGR1);
	u32 पूर्णांक_grp1_en = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_IGER1);
	u32 पूर्णांक_grp0 = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_IGR0);
	u32 पूर्णांक_grp0_en = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_IGER0);
	काष्ठा usb_ctrlrequest ctrl;
	u8 in;
	u32 reg;
	पूर्णांक i;

	spin_lock(&fusb300->lock);

	पूर्णांक_grp1 &= पूर्णांक_grp1_en;
	पूर्णांक_grp0 &= पूर्णांक_grp0_en;

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_WARM_RST_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_WARM_RST_INT);
		prपूर्णांकk(KERN_INFO"fusb300_warmreset\n");
		fusb300_reset();
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_HOT_RST_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_HOT_RST_INT);
		prपूर्णांकk(KERN_INFO"fusb300_hotreset\n");
		fusb300_reset();
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_USBRST_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_USBRST_INT);
		fusb300_reset();
	पूर्ण
	/* COMABT_INT has a highest priority */

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_CX_COMABT_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_CX_COMABT_INT);
		prपूर्णांकk(KERN_INFO"fusb300_ep0abt\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_VBUS_CHG_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_VBUS_CHG_INT);
		prपूर्णांकk(KERN_INFO"fusb300_vbus_change\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U3_EXIT_FAIL_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U3_EXIT_FAIL_INT);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U2_EXIT_FAIL_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U2_EXIT_FAIL_INT);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U1_EXIT_FAIL_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U1_EXIT_FAIL_INT);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U2_ENTRY_FAIL_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U2_ENTRY_FAIL_INT);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U1_ENTRY_FAIL_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U1_ENTRY_FAIL_INT);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U3_EXIT_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U3_EXIT_INT);
		prपूर्णांकk(KERN_INFO "FUSB300_IGR1_U3_EXIT_INT\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U2_EXIT_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U2_EXIT_INT);
		prपूर्णांकk(KERN_INFO "FUSB300_IGR1_U2_EXIT_INT\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U1_EXIT_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U1_EXIT_INT);
		prपूर्णांकk(KERN_INFO "FUSB300_IGR1_U1_EXIT_INT\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U3_ENTRY_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U3_ENTRY_INT);
		prपूर्णांकk(KERN_INFO "FUSB300_IGR1_U3_ENTRY_INT\n");
		fusb300_enable_bit(fusb300, FUSB300_OFFSET_SSCR1,
				   FUSB300_SSCR1_GO_U3_DONE);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U2_ENTRY_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U2_ENTRY_INT);
		prपूर्णांकk(KERN_INFO "FUSB300_IGR1_U2_ENTRY_INT\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_U1_ENTRY_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_U1_ENTRY_INT);
		prपूर्णांकk(KERN_INFO "FUSB300_IGR1_U1_ENTRY_INT\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_RESM_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_RESM_INT);
		prपूर्णांकk(KERN_INFO "fusb300_resume\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_SUSP_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_SUSP_INT);
		prपूर्णांकk(KERN_INFO "fusb300_suspend\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_HS_LPM_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_HS_LPM_INT);
		prपूर्णांकk(KERN_INFO "fusb300_HS_LPM_INT\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_DEV_MODE_CHG_INT) अणु
		fusb300_clear_पूर्णांक(fusb300, FUSB300_OFFSET_IGR1,
				  FUSB300_IGR1_DEV_MODE_CHG_INT);
		check_device_mode(fusb300);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_CX_COMFAIL_INT) अणु
		fusb300_set_cxstall(fusb300);
		prपूर्णांकk(KERN_INFO "fusb300_ep0fail\n");
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_CX_SETUP_INT) अणु
		prपूर्णांकk(KERN_INFO "fusb300_ep0setup\n");
		अगर (setup_packet(fusb300, &ctrl)) अणु
			spin_unlock(&fusb300->lock);
			अगर (fusb300->driver->setup(&fusb300->gadget, &ctrl) < 0)
				fusb300_set_cxstall(fusb300);
			spin_lock(&fusb300->lock);
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_CX_CMDEND_INT)
		prपूर्णांकk(KERN_INFO "fusb300_cmdend\n");


	अगर (पूर्णांक_grp1 & FUSB300_IGR1_CX_OUT_INT) अणु
		prपूर्णांकk(KERN_INFO "fusb300_cxout\n");
		fusb300_ep0out(fusb300);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_CX_IN_INT) अणु
		prपूर्णांकk(KERN_INFO "fusb300_cxin\n");
		fusb300_ep0in(fusb300);
	पूर्ण

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_INTGRP5)
		fusb300_grp5_handler();

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_INTGRP4)
		fusb300_grp4_handler();

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_INTGRP3)
		fusb300_grp3_handler();

	अगर (पूर्णांक_grp1 & FUSB300_IGR1_INTGRP2)
		fusb300_grp2_handler();

	अगर (पूर्णांक_grp0) अणु
		क्रम (i = 1; i < FUSB300_MAX_NUM_EP; i++) अणु
			अगर (पूर्णांक_grp0 & FUSB300_IGR0_EPn_FIFO_INT(i)) अणु
				reg = ioपढ़ो32(fusb300->reg +
					FUSB300_OFFSET_EPSET1(i));
				in = (reg & FUSB300_EPSET1_सूचीIN) ? 1 : 0;
				अगर (in)
					in_ep_fअगरo_handler(fusb300->ep[i]);
				अन्यथा
					out_ep_fअगरo_handler(fusb300->ep[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(&fusb300->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fusb300_set_u2_समयout(काष्ठा fusb300 *fusb300,
				   u32 समय)
अणु
	u32 reg;

	reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_TT);
	reg &= ~0xff;
	reg |= FUSB300_SSCR2_U2TIMEOUT(समय);

	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_TT);
पूर्ण

अटल व्योम fusb300_set_u1_समयout(काष्ठा fusb300 *fusb300,
				   u32 समय)
अणु
	u32 reg;

	reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_TT);
	reg &= ~(0xff << 8);
	reg |= FUSB300_SSCR2_U1TIMEOUT(समय);

	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_TT);
पूर्ण

अटल व्योम init_controller(काष्ठा fusb300 *fusb300)
अणु
	u32 reg;
	u32 mask = 0;
	u32 val = 0;

	/* split on */
	mask = val = FUSB300_AHBBCR_S0_SPLIT_ON | FUSB300_AHBBCR_S1_SPLIT_ON;
	reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_AHBCR);
	reg &= ~mask;
	reg |= val;
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_AHBCR);

	/* enable high-speed LPM */
	mask = val = FUSB300_HSCR_HS_LPM_PERMIT;
	reg = ioपढ़ो32(fusb300->reg + FUSB300_OFFSET_HSCR);
	reg &= ~mask;
	reg |= val;
	ioग_लिखो32(reg, fusb300->reg + FUSB300_OFFSET_HSCR);

	/*set u1 u2 timmer*/
	fusb300_set_u2_समयout(fusb300, 0xff);
	fusb300_set_u1_समयout(fusb300, 0xff);

	/* enable all grp1 पूर्णांकerrupt */
	ioग_लिखो32(0xcfffff9f, fusb300->reg + FUSB300_OFFSET_IGER1);
पूर्ण
/*------------------------------------------------------------------------*/
अटल पूर्णांक fusb300_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा fusb300 *fusb300 = to_fusb300(g);

	/* hook up the driver */
	driver->driver.bus = शून्य;
	fusb300->driver = driver;

	वापस 0;
पूर्ण

अटल पूर्णांक fusb300_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा fusb300 *fusb300 = to_fusb300(g);

	init_controller(fusb300);
	fusb300->driver = शून्य;

	वापस 0;
पूर्ण
/*--------------------------------------------------------------------------*/

अटल पूर्णांक fusb300_udc_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops fusb300_gadget_ops = अणु
	.pullup		= fusb300_udc_pullup,
	.udc_start	= fusb300_udc_start,
	.udc_stop	= fusb300_udc_stop,
पूर्ण;

अटल पूर्णांक fusb300_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fusb300 *fusb300 = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	usb_del_gadget_udc(&fusb300->gadget);
	iounmap(fusb300->reg);
	मुक्त_irq(platक्रमm_get_irq(pdev, 0), fusb300);

	fusb300_मुक्त_request(&fusb300->ep[0]->ep, fusb300->ep0_req);
	क्रम (i = 0; i < FUSB300_MAX_NUM_EP; i++)
		kमुक्त(fusb300->ep[i]);
	kमुक्त(fusb300);

	वापस 0;
पूर्ण

अटल पूर्णांक fusb300_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res, *ires, *ires1;
	व्योम __iomem *reg = शून्य;
	काष्ठा fusb300 *fusb300 = शून्य;
	काष्ठा fusb300_ep *_ep[FUSB300_MAX_NUM_EP];
	पूर्णांक ret = 0;
	पूर्णांक i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		pr_err("platform_get_resource error.\n");
		जाओ clean_up;
	पूर्ण

	ires = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!ires) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev,
			"platform_get_resource IORESOURCE_IRQ error.\n");
		जाओ clean_up;
	पूर्ण

	ires1 = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 1);
	अगर (!ires1) अणु
		ret = -ENODEV;
		dev_err(&pdev->dev,
			"platform_get_resource IORESOURCE_IRQ 1 error.\n");
		जाओ clean_up;
	पूर्ण

	reg = ioremap(res->start, resource_size(res));
	अगर (reg == शून्य) अणु
		ret = -ENOMEM;
		pr_err("ioremap error.\n");
		जाओ clean_up;
	पूर्ण

	/* initialize udc */
	fusb300 = kzalloc(माप(काष्ठा fusb300), GFP_KERNEL);
	अगर (fusb300 == शून्य) अणु
		ret = -ENOMEM;
		जाओ clean_up;
	पूर्ण

	क्रम (i = 0; i < FUSB300_MAX_NUM_EP; i++) अणु
		_ep[i] = kzalloc(माप(काष्ठा fusb300_ep), GFP_KERNEL);
		अगर (_ep[i] == शून्य) अणु
			ret = -ENOMEM;
			जाओ clean_up;
		पूर्ण
		fusb300->ep[i] = _ep[i];
	पूर्ण

	spin_lock_init(&fusb300->lock);

	platक्रमm_set_drvdata(pdev, fusb300);

	fusb300->gadget.ops = &fusb300_gadget_ops;

	fusb300->gadget.max_speed = USB_SPEED_HIGH;
	fusb300->gadget.name = udc_name;
	fusb300->reg = reg;

	ret = request_irq(ires->start, fusb300_irq, IRQF_SHARED,
			  udc_name, fusb300);
	अगर (ret < 0) अणु
		pr_err("request_irq error (%d)\n", ret);
		जाओ clean_up;
	पूर्ण

	ret = request_irq(ires1->start, fusb300_irq,
			IRQF_SHARED, udc_name, fusb300);
	अगर (ret < 0) अणु
		pr_err("request_irq1 error (%d)\n", ret);
		जाओ clean_up;
	पूर्ण

	INIT_LIST_HEAD(&fusb300->gadget.ep_list);

	क्रम (i = 0; i < FUSB300_MAX_NUM_EP ; i++) अणु
		काष्ठा fusb300_ep *ep = fusb300->ep[i];

		अगर (i != 0) अणु
			INIT_LIST_HEAD(&fusb300->ep[i]->ep.ep_list);
			list_add_tail(&fusb300->ep[i]->ep.ep_list,
				     &fusb300->gadget.ep_list);
		पूर्ण
		ep->fusb300 = fusb300;
		INIT_LIST_HEAD(&ep->queue);
		ep->ep.name = fusb300_ep_name[i];
		ep->ep.ops = &fusb300_ep_ops;
		usb_ep_set_maxpacket_limit(&ep->ep, HS_BULK_MAX_PACKET_SIZE);

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
	usb_ep_set_maxpacket_limit(&fusb300->ep[0]->ep, HS_CTL_MAX_PACKET_SIZE);
	fusb300->ep[0]->epnum = 0;
	fusb300->gadget.ep0 = &fusb300->ep[0]->ep;
	INIT_LIST_HEAD(&fusb300->gadget.ep0->ep_list);

	fusb300->ep0_req = fusb300_alloc_request(&fusb300->ep[0]->ep,
				GFP_KERNEL);
	अगर (fusb300->ep0_req == शून्य) अणु
		ret = -ENOMEM;
		जाओ clean_up3;
	पूर्ण

	init_controller(fusb300);
	ret = usb_add_gadget_udc(&pdev->dev, &fusb300->gadget);
	अगर (ret)
		जाओ err_add_udc;

	dev_info(&pdev->dev, "version %s\n", DRIVER_VERSION);

	वापस 0;

err_add_udc:
	fusb300_मुक्त_request(&fusb300->ep[0]->ep, fusb300->ep0_req);

clean_up3:
	मुक्त_irq(ires->start, fusb300);

clean_up:
	अगर (fusb300) अणु
		अगर (fusb300->ep0_req)
			fusb300_मुक्त_request(&fusb300->ep[0]->ep,
				fusb300->ep0_req);
		क्रम (i = 0; i < FUSB300_MAX_NUM_EP; i++)
			kमुक्त(fusb300->ep[i]);
		kमुक्त(fusb300);
	पूर्ण
	अगर (reg)
		iounmap(reg);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver fusb300_driver = अणु
	.हटाओ =	fusb300_हटाओ,
	.driver		= अणु
		.name =	udc_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(fusb300_driver, fusb300_probe);
