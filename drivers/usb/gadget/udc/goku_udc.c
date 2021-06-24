<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Toshiba TC86C001 ("Goku-S") USB Device Controller driver
 *
 * Copyright (C) 2000-2002 Lineo
 *      by Stuart Lynne, Tom Rushworth, and Bruce Balden
 * Copyright (C) 2002 Toshiba Corporation
 * Copyright (C) 2003 MontaVista Software (source@mvista.com)
 */

/*
 * This device has ep0 and three semi-configurable bulk/पूर्णांकerrupt endpoपूर्णांकs.
 *
 *  - Endpoपूर्णांक numbering is fixed: epअणु1,2,3पूर्ण-bulk
 *  - Gadget drivers can choose ep maxpacket (8/16/32/64)
 *  - Gadget drivers can choose direction (IN, OUT)
 *  - DMA works with ep1 (OUT transfers) and ep2 (IN transfers).
 */

// #घोषणा	VERBOSE		/* extra debug messages (success too) */
// #घोषणा	USB_TRACE	/* packet-level success messages */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/prefetch.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>


#समावेश "goku_udc.h"

#घोषणा	DRIVER_DESC		"TC86C001 USB Device Controller"
#घोषणा	DRIVER_VERSION		"30-Oct 2003"

अटल स्थिर अक्षर driver_name [] = "goku_udc";
अटल स्थिर अक्षर driver_desc [] = DRIVER_DESC;

MODULE_AUTHOR("source@mvista.com");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");


/*
 * IN dma behaves ok under testing, though the IN-dma पात paths करोn't
 * seem to behave quite as expected.  Used by शेष.
 *
 * OUT dma करोcuments design problems handling the common "short packet"
 * transfer termination policy; it couldn't be enabled by शेष, even
 * अगर the OUT-dma पात problems had a resolution.
 */
अटल अचिन्हित use_dma = 1;

#अगर 0
//#समावेश <linux/moduleparam.h>
/* "modprobe goku_udc use_dma=1" etc
 *	0 to disable dma
 *	1 to use IN dma only (normal operation)
 *	2 to use IN and OUT dma
 */
module_param(use_dma, uपूर्णांक, S_IRUGO);
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल व्योम nuke(काष्ठा goku_ep *, पूर्णांक status);

अटल अंतरभूत व्योम
command(काष्ठा goku_udc_regs __iomem *regs, पूर्णांक command, अचिन्हित epnum)
अणु
	ग_लिखोl(COMMAND_EP(epnum) | command, &regs->Command);
	udelay(300);
पूर्ण

अटल पूर्णांक
goku_ep_enable(काष्ठा usb_ep *_ep, स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा goku_udc	*dev;
	काष्ठा goku_ep	*ep;
	u32		mode;
	u16		max;
	अचिन्हित दीर्घ	flags;

	ep = container_of(_ep, काष्ठा goku_ep, ep);
	अगर (!_ep || !desc
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;
	dev = ep->dev;
	अगर (ep == &dev->ep[0])
		वापस -EINVAL;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;
	अगर (ep->num != usb_endpoपूर्णांक_num(desc))
		वापस -EINVAL;

	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((पढ़ोl(ep->reg_status) & EPxSTATUS_EP_MASK)
			!= EPxSTATUS_EP_INVALID)
		वापस -EBUSY;

	/* enabling the no-toggle पूर्णांकerrupt mode would need an api hook */
	mode = 0;
	max = get_unaligned_le16(&desc->wMaxPacketSize);
	चयन (max) अणु
	हाल 64:
		mode++;
		fallthrough;
	हाल 32:
		mode++;
		fallthrough;
	हाल 16:
		mode++;
		fallthrough;
	हाल 8:
		mode <<= 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	mode |= 2 << 1;		/* bulk, or पूर्णांकr-with-toggle */

	/* ep1/ep2 dma direction is chosen early; it works in the other
	 * direction, with pio.  be cautious with out-dma.
	 */
	ep->is_in = usb_endpoपूर्णांक_dir_in(desc);
	अगर (ep->is_in) अणु
		mode |= 1;
		ep->dma = (use_dma != 0) && (ep->num == UDC_MSTRD_ENDPOINT);
	पूर्ण अन्यथा अणु
		ep->dma = (use_dma == 2) && (ep->num == UDC_MSTWR_ENDPOINT);
		अगर (ep->dma)
			DBG(dev, "%s out-dma hides short packets\n",
				ep->ep.name);
	पूर्ण

	spin_lock_irqsave(&ep->dev->lock, flags);

	/* ep1 and ep2 can करो द्विगुन buffering and/or dma */
	अगर (ep->num < 3) अणु
		काष्ठा goku_udc_regs __iomem	*regs = ep->dev->regs;
		u32				पंचांगp;

		/* द्विगुन buffer except (क्रम now) with pio in */
		पंचांगp = ((ep->dma || !ep->is_in)
				? 0x10	/* द्विगुन buffered */
				: 0x11	/* single buffer */
			) << ep->num;
		पंचांगp |= पढ़ोl(&regs->EPxSingle);
		ग_लिखोl(पंचांगp, &regs->EPxSingle);

		पंचांगp = (ep->dma ? 0x10/*dma*/ : 0x11/*pio*/) << ep->num;
		पंचांगp |= पढ़ोl(&regs->EPxBCS);
		ग_लिखोl(पंचांगp, &regs->EPxBCS);
	पूर्ण
	ग_लिखोl(mode, ep->reg_mode);
	command(ep->dev->regs, COMMAND_RESET, ep->num);
	ep->ep.maxpacket = max;
	ep->stopped = 0;
	ep->ep.desc = desc;
	spin_unlock_irqrestore(&ep->dev->lock, flags);

	DBG(dev, "enable %s %s %s maxpacket %u\n", ep->ep.name,
		ep->is_in ? "IN" : "OUT",
		ep->dma ? "dma" : "pio",
		max);

	वापस 0;
पूर्ण

अटल व्योम ep_reset(काष्ठा goku_udc_regs __iomem *regs, काष्ठा goku_ep *ep)
अणु
	काष्ठा goku_udc		*dev = ep->dev;

	अगर (regs) अणु
		command(regs, COMMAND_INVALID, ep->num);
		अगर (ep->num) अणु
			अगर (ep->num == UDC_MSTWR_ENDPOINT)
				dev->पूर्णांक_enable &= ~(INT_MSTWREND
							|INT_MSTWRTMOUT);
			अन्यथा अगर (ep->num == UDC_MSTRD_ENDPOINT)
				dev->पूर्णांक_enable &= ~INT_MSTRDEND;
			dev->पूर्णांक_enable &= ~INT_EPxDATASET (ep->num);
		पूर्ण अन्यथा
			dev->पूर्णांक_enable &= ~INT_EP0;
		ग_लिखोl(dev->पूर्णांक_enable, &regs->पूर्णांक_enable);
		पढ़ोl(&regs->पूर्णांक_enable);
		अगर (ep->num < 3) अणु
			काष्ठा goku_udc_regs __iomem	*r = ep->dev->regs;
			u32				पंचांगp;

			पंचांगp = पढ़ोl(&r->EPxSingle);
			पंचांगp &= ~(0x11 << ep->num);
			ग_लिखोl(पंचांगp, &r->EPxSingle);

			पंचांगp = पढ़ोl(&r->EPxBCS);
			पंचांगp &= ~(0x11 << ep->num);
			ग_लिखोl(पंचांगp, &r->EPxBCS);
		पूर्ण
		/* reset dma in हाल we're still using it */
		अगर (ep->dma) अणु
			u32	master;

			master = पढ़ोl(&regs->dma_master) & MST_RW_BITS;
			अगर (ep->num == UDC_MSTWR_ENDPOINT) अणु
				master &= ~MST_W_BITS;
				master |= MST_WR_RESET;
			पूर्ण अन्यथा अणु
				master &= ~MST_R_BITS;
				master |= MST_RD_RESET;
			पूर्ण
			ग_लिखोl(master, &regs->dma_master);
		पूर्ण
	पूर्ण

	usb_ep_set_maxpacket_limit(&ep->ep, MAX_FIFO_SIZE);
	ep->ep.desc = शून्य;
	ep->stopped = 1;
	ep->irqs = 0;
	ep->dma = 0;
पूर्ण

अटल पूर्णांक goku_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा goku_ep	*ep;
	काष्ठा goku_udc	*dev;
	अचिन्हित दीर्घ	flags;

	ep = container_of(_ep, काष्ठा goku_ep, ep);
	अगर (!_ep || !ep->ep.desc)
		वापस -ENODEV;
	dev = ep->dev;
	अगर (dev->ep0state == EP0_SUSPEND)
		वापस -EBUSY;

	VDBG(dev, "disable %s\n", _ep->name);

	spin_lock_irqsave(&dev->lock, flags);
	nuke(ep, -ESHUTDOWN);
	ep_reset(dev->regs, ep);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_request *
goku_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा goku_request	*req;

	अगर (!_ep)
		वापस शून्य;
	req = kzalloc(माप *req, gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);
	वापस &req->req;
पूर्ण

अटल व्योम
goku_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा goku_request	*req;

	अगर (!_ep || !_req)
		वापस;

	req = container_of(_req, काष्ठा goku_request, req);
	WARN_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम
करोne(काष्ठा goku_ep *ep, काष्ठा goku_request *req, पूर्णांक status)
अणु
	काष्ठा goku_udc		*dev;
	अचिन्हित		stopped = ep->stopped;

	list_del_init(&req->queue);

	अगर (likely(req->req.status == -EINPROGRESS))
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	dev = ep->dev;

	अगर (ep->dma)
		usb_gadget_unmap_request(&dev->gadget, &req->req, ep->is_in);

#अगर_अघोषित USB_TRACE
	अगर (status && status != -ESHUTDOWN)
#पूर्ण_अगर
		VDBG(dev, "complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* करोn't modअगरy queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&dev->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&dev->lock);
	ep->stopped = stopped;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक
ग_लिखो_packet(u32 __iomem *fअगरo, u8 *buf, काष्ठा goku_request *req, अचिन्हित max)
अणु
	अचिन्हित	length, count;

	length = min(req->req.length - req->req.actual, max);
	req->req.actual += length;

	count = length;
	जबतक (likely(count--))
		ग_लिखोl(*buf++, fअगरo);
	वापस length;
पूर्ण

// वापस:  0 = still running, 1 = completed, negative = त्रुटि_सं
अटल पूर्णांक ग_लिखो_fअगरo(काष्ठा goku_ep *ep, काष्ठा goku_request *req)
अणु
	काष्ठा goku_udc	*dev = ep->dev;
	u32		पंचांगp;
	u8		*buf;
	अचिन्हित	count;
	पूर्णांक		is_last;

	पंचांगp = पढ़ोl(&dev->regs->DataSet);
	buf = req->req.buf + req->req.actual;
	prefetch(buf);

	dev = ep->dev;
	अगर (unlikely(ep->num == 0 && dev->ep0state != EP0_IN))
		वापस -EL2HLT;

	/* NOTE:  just single-buffered PIO-IN क्रम now.  */
	अगर (unlikely((पंचांगp & DATASET_A(ep->num)) != 0))
		वापस 0;

	/* clear our "packet available" irq */
	अगर (ep->num != 0)
		ग_लिखोl(~INT_EPxDATASET(ep->num), &dev->regs->पूर्णांक_status);

	count = ग_लिखो_packet(ep->reg_fअगरo, buf, req, ep->ep.maxpacket);

	/* last packet often लघु (someबार a zlp, especially on ep0) */
	अगर (unlikely(count != ep->ep.maxpacket)) अणु
		ग_लिखोl(~(1<<ep->num), &dev->regs->EOP);
		अगर (ep->num == 0) अणु
			dev->ep[0].stopped = 1;
			dev->ep0state = EP0_STATUS;
		पूर्ण
		is_last = 1;
	पूर्ण अन्यथा अणु
		अगर (likely(req->req.length != req->req.actual)
				|| req->req.zero)
			is_last = 0;
		अन्यथा
			is_last = 1;
	पूर्ण
#अगर 0		/* prपूर्णांकk seemed to trash is_last...*/
//#अगर_घोषित USB_TRACE
	VDBG(dev, "wrote %s %u bytes%s IN %u left %p\n",
		ep->ep.name, count, is_last ? "/last" : "",
		req->req.length - req->req.actual, req);
#पूर्ण_अगर

	/* requests complete when all IN data is in the FIFO,
	 * or someबार later, अगर a zlp was needed.
	 */
	अगर (is_last) अणु
		करोne(ep, req, 0);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_fअगरo(काष्ठा goku_ep *ep, काष्ठा goku_request *req)
अणु
	काष्ठा goku_udc_regs __iomem	*regs;
	u32				size, set;
	u8				*buf;
	अचिन्हित			bufferspace, is_लघु, dbuff;

	regs = ep->dev->regs;
top:
	buf = req->req.buf + req->req.actual;
	prefetchw(buf);

	अगर (unlikely(ep->num == 0 && ep->dev->ep0state != EP0_OUT))
		वापस -EL2HLT;

	dbuff = (ep->num == 1 || ep->num == 2);
	करो अणु
		/* ack dataset irq matching the status we'll handle */
		अगर (ep->num != 0)
			ग_लिखोl(~INT_EPxDATASET(ep->num), &regs->पूर्णांक_status);

		set = पढ़ोl(&regs->DataSet) & DATASET_AB(ep->num);
		size = पढ़ोl(&regs->EPxSizeLA[ep->num]);
		bufferspace = req->req.length - req->req.actual;

		/* usually करो nothing without an OUT packet */
		अगर (likely(ep->num != 0 || bufferspace != 0)) अणु
			अगर (unlikely(set == 0))
				अवरोध;
			/* use ep1/ep2 द्विगुन-buffering क्रम OUT */
			अगर (!(size & PACKET_ACTIVE))
				size = पढ़ोl(&regs->EPxSizeLB[ep->num]);
			अगर (!(size & PACKET_ACTIVE))	/* "can't happen" */
				अवरोध;
			size &= DATASIZE;	/* EPxSizeH == 0 */

		/* ep0out no-out-data हाल क्रम set_config, etc */
		पूर्ण अन्यथा
			size = 0;

		/* पढ़ो all bytes from this packet */
		req->req.actual += size;
		is_लघु = (size < ep->ep.maxpacket);
#अगर_घोषित USB_TRACE
		VDBG(ep->dev, "read %s %u bytes%s OUT req %p %u/%u\n",
			ep->ep.name, size, is_लघु ? "/S" : "",
			req, req->req.actual, req->req.length);
#पूर्ण_अगर
		जबतक (likely(size-- != 0)) अणु
			u8	byte = (u8) पढ़ोl(ep->reg_fअगरo);

			अगर (unlikely(bufferspace == 0)) अणु
				/* this happens when the driver's buffer
				 * is smaller than what the host sent.
				 * discard the extra data in this packet.
				 */
				अगर (req->req.status != -EOVERFLOW)
					DBG(ep->dev, "%s overflow %u\n",
						ep->ep.name, size);
				req->req.status = -EOVERFLOW;
			पूर्ण अन्यथा अणु
				*buf++ = byte;
				bufferspace--;
			पूर्ण
		पूर्ण

		/* completion */
		अगर (unlikely(is_लघु || req->req.actual == req->req.length)) अणु
			अगर (unlikely(ep->num == 0)) अणु
				/* non-control endpoपूर्णांकs now usable? */
				अगर (ep->dev->req_config)
					ग_लिखोl(ep->dev->configured
							? USBSTATE_CONFIGURED
							: 0,
						&regs->UsbState);
				/* ep0out status stage */
				ग_लिखोl(~(1<<0), &regs->EOP);
				ep->stopped = 1;
				ep->dev->ep0state = EP0_STATUS;
			पूर्ण
			करोne(ep, req, 0);

			/* empty the second buffer asap */
			अगर (dbuff && !list_empty(&ep->queue)) अणु
				req = list_entry(ep->queue.next,
						काष्ठा goku_request, queue);
				जाओ top;
			पूर्ण
			वापस 1;
		पूर्ण
	पूर्ण जबतक (dbuff);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
pio_irq_enable(काष्ठा goku_udc *dev,
		काष्ठा goku_udc_regs __iomem *regs, पूर्णांक epnum)
अणु
	dev->पूर्णांक_enable |= INT_EPxDATASET (epnum);
	ग_लिखोl(dev->पूर्णांक_enable, &regs->पूर्णांक_enable);
	/* ग_लिखो may still be posted */
पूर्ण

अटल अंतरभूत व्योम
pio_irq_disable(काष्ठा goku_udc *dev,
		काष्ठा goku_udc_regs __iomem *regs, पूर्णांक epnum)
अणु
	dev->पूर्णांक_enable &= ~INT_EPxDATASET (epnum);
	ग_लिखोl(dev->पूर्णांक_enable, &regs->पूर्णांक_enable);
	/* ग_लिखो may still be posted */
पूर्ण

अटल अंतरभूत व्योम
pio_advance(काष्ठा goku_ep *ep)
अणु
	काष्ठा goku_request	*req;

	अगर (unlikely(list_empty (&ep->queue)))
		वापस;
	req = list_entry(ep->queue.next, काष्ठा goku_request, queue);
	(ep->is_in ? ग_लिखो_fअगरo : पढ़ो_fअगरo)(ep, req);
पूर्ण


/*-------------------------------------------------------------------------*/

// वापस:  0 = q running, 1 = q stopped, negative = त्रुटि_सं
अटल पूर्णांक start_dma(काष्ठा goku_ep *ep, काष्ठा goku_request *req)
अणु
	काष्ठा goku_udc_regs __iomem	*regs = ep->dev->regs;
	u32				master;
	u32				start = req->req.dma;
	u32				end = start + req->req.length - 1;

	master = पढ़ोl(&regs->dma_master) & MST_RW_BITS;

	/* re-init the bits affecting IN dma; careful with zlps */
	अगर (likely(ep->is_in)) अणु
		अगर (unlikely(master & MST_RD_ENA)) अणु
			DBG (ep->dev, "start, IN active dma %03x!!\n",
				master);
//			वापस -EL2HLT;
		पूर्ण
		ग_लिखोl(end, &regs->in_dma_end);
		ग_लिखोl(start, &regs->in_dma_start);

		master &= ~MST_R_BITS;
		अगर (unlikely(req->req.length == 0))
			master = MST_RD_ENA | MST_RD_EOPB;
		अन्यथा अगर ((req->req.length % ep->ep.maxpacket) != 0
					|| req->req.zero)
			master = MST_RD_ENA | MST_EOPB_ENA;
		अन्यथा
			master = MST_RD_ENA | MST_EOPB_DIS;

		ep->dev->पूर्णांक_enable |= INT_MSTRDEND;

	/* Goku DMA-OUT merges लघु packets, which plays poorly with
	 * protocols where लघु packets mark the transfer boundaries.
	 * The chip supports a nonstandard policy with INT_MSTWRTMOUT,
	 * ending transfers after 3 SOFs; we करोn't turn it on.
	 */
	पूर्ण अन्यथा अणु
		अगर (unlikely(master & MST_WR_ENA)) अणु
			DBG (ep->dev, "start, OUT active dma %03x!!\n",
				master);
//			वापस -EL2HLT;
		पूर्ण
		ग_लिखोl(end, &regs->out_dma_end);
		ग_लिखोl(start, &regs->out_dma_start);

		master &= ~MST_W_BITS;
		master |= MST_WR_ENA | MST_TIMEOUT_DIS;

		ep->dev->पूर्णांक_enable |= INT_MSTWREND|INT_MSTWRTMOUT;
	पूर्ण

	ग_लिखोl(master, &regs->dma_master);
	ग_लिखोl(ep->dev->पूर्णांक_enable, &regs->पूर्णांक_enable);
	वापस 0;
पूर्ण

अटल व्योम dma_advance(काष्ठा goku_udc *dev, काष्ठा goku_ep *ep)
अणु
	काष्ठा goku_request		*req;
	काष्ठा goku_udc_regs __iomem	*regs = ep->dev->regs;
	u32				master;

	master = पढ़ोl(&regs->dma_master);

	अगर (unlikely(list_empty(&ep->queue))) अणु
stop:
		अगर (ep->is_in)
			dev->पूर्णांक_enable &= ~INT_MSTRDEND;
		अन्यथा
			dev->पूर्णांक_enable &= ~(INT_MSTWREND|INT_MSTWRTMOUT);
		ग_लिखोl(dev->पूर्णांक_enable, &regs->पूर्णांक_enable);
		वापस;
	पूर्ण
	req = list_entry(ep->queue.next, काष्ठा goku_request, queue);

	/* normal hw dma completion (not पात) */
	अगर (likely(ep->is_in)) अणु
		अगर (unlikely(master & MST_RD_ENA))
			वापस;
		req->req.actual = पढ़ोl(&regs->in_dma_current);
	पूर्ण अन्यथा अणु
		अगर (unlikely(master & MST_WR_ENA))
			वापस;

		/* hardware merges लघु packets, and also hides packet
		 * overruns.  a partial packet MAY be in the fअगरo here.
		 */
		req->req.actual = पढ़ोl(&regs->out_dma_current);
	पूर्ण
	req->req.actual -= req->req.dma;
	req->req.actual++;

#अगर_घोषित USB_TRACE
	VDBG(dev, "done %s %s dma, %u/%u bytes, req %p\n",
		ep->ep.name, ep->is_in ? "IN" : "OUT",
		req->req.actual, req->req.length, req);
#पूर्ण_अगर
	करोne(ep, req, 0);
	अगर (list_empty(&ep->queue))
		जाओ stop;
	req = list_entry(ep->queue.next, काष्ठा goku_request, queue);
	(व्योम) start_dma(ep, req);
पूर्ण

अटल व्योम पात_dma(काष्ठा goku_ep *ep, पूर्णांक status)
अणु
	काष्ठा goku_udc_regs __iomem	*regs = ep->dev->regs;
	काष्ठा goku_request		*req;
	u32				curr, master;

	/* NAK future host requests, hoping the implicit delay lets the
	 * dma engine finish पढ़ोing (or writing) its latest packet and
	 * empty the dma buffer (up to 16 bytes).
	 *
	 * This aव्योमs needing to clean up a partial packet in the fअगरo;
	 * we can't करो that क्रम IN without side effects to HALT and TOGGLE.
	 */
	command(regs, COMMAND_FIFO_DISABLE, ep->num);
	req = list_entry(ep->queue.next, काष्ठा goku_request, queue);
	master = पढ़ोl(&regs->dma_master) & MST_RW_BITS;

	/* FIXME using these resets isn't usably करोcumented. this may
	 * not work unless it's followed by disabling the endpoपूर्णांक.
	 *
	 * FIXME the OUT reset path करोesn't even behave consistently.
	 */
	अगर (ep->is_in) अणु
		अगर (unlikely((पढ़ोl(&regs->dma_master) & MST_RD_ENA) == 0))
			जाओ finished;
		curr = पढ़ोl(&regs->in_dma_current);

		ग_लिखोl(curr, &regs->in_dma_end);
		ग_लिखोl(curr, &regs->in_dma_start);

		master &= ~MST_R_BITS;
		master |= MST_RD_RESET;
		ग_लिखोl(master, &regs->dma_master);

		अगर (पढ़ोl(&regs->dma_master) & MST_RD_ENA)
			DBG(ep->dev, "IN dma active after reset!\n");

	पूर्ण अन्यथा अणु
		अगर (unlikely((पढ़ोl(&regs->dma_master) & MST_WR_ENA) == 0))
			जाओ finished;
		curr = पढ़ोl(&regs->out_dma_current);

		ग_लिखोl(curr, &regs->out_dma_end);
		ग_लिखोl(curr, &regs->out_dma_start);

		master &= ~MST_W_BITS;
		master |= MST_WR_RESET;
		ग_लिखोl(master, &regs->dma_master);

		अगर (पढ़ोl(&regs->dma_master) & MST_WR_ENA)
			DBG(ep->dev, "OUT dma active after reset!\n");
	पूर्ण
	req->req.actual = (curr - req->req.dma) + 1;
	req->req.status = status;

	VDBG(ep->dev, "%s %s %s %d/%d\n", __func__, ep->ep.name,
		ep->is_in ? "IN" : "OUT",
		req->req.actual, req->req.length);

	command(regs, COMMAND_FIFO_ENABLE, ep->num);

	वापस;

finished:
	/* dma alपढ़ोy completed; no पात needed */
	command(regs, COMMAND_FIFO_ENABLE, ep->num);
	req->req.actual = req->req.length;
	req->req.status = 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
goku_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा goku_request	*req;
	काष्ठा goku_ep		*ep;
	काष्ठा goku_udc		*dev;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			status;

	/* always require a cpu-view buffer so pio works */
	req = container_of(_req, काष्ठा goku_request, req);
	अगर (unlikely(!_req || !_req->complete
			|| !_req->buf || !list_empty(&req->queue)))
		वापस -EINVAL;
	ep = container_of(_ep, काष्ठा goku_ep, ep);
	अगर (unlikely(!_ep || (!ep->ep.desc && ep->num != 0)))
		वापस -EINVAL;
	dev = ep->dev;
	अगर (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN))
		वापस -ESHUTDOWN;

	/* can't touch रेजिस्टरs when suspended */
	अगर (dev->ep0state == EP0_SUSPEND)
		वापस -EBUSY;

	/* set up dma mapping in हाल the caller didn't */
	अगर (ep->dma) अणु
		status = usb_gadget_map_request(&dev->gadget, &req->req,
				ep->is_in);
		अगर (status)
			वापस status;
	पूर्ण

#अगर_घोषित USB_TRACE
	VDBG(dev, "%s queue req %p, len %u buf %p\n",
			_ep->name, _req, _req->length, _req->buf);
#पूर्ण_अगर

	spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	/* क्रम ep0 IN without premature status, zlp is required and
	 * writing EOP starts the status stage (OUT).
	 */
	अगर (unlikely(ep->num == 0 && ep->is_in))
		_req->zero = 1;

	/* kickstart this i/o queue? */
	status = 0;
	अगर (list_empty(&ep->queue) && likely(!ep->stopped)) अणु
		/* dma:  करोne after dma completion IRQ (or error)
		 * pio:  करोne after last fअगरo operation
		 */
		अगर (ep->dma)
			status = start_dma(ep, req);
		अन्यथा
			status = (ep->is_in ? ग_लिखो_fअगरo : पढ़ो_fअगरo)(ep, req);

		अगर (unlikely(status != 0)) अणु
			अगर (status > 0)
				status = 0;
			req = शून्य;
		पूर्ण

	पूर्ण /* अन्यथा pio or dma irq handler advances the queue. */

	अगर (likely(req != शून्य))
		list_add_tail(&req->queue, &ep->queue);

	अगर (likely(!list_empty(&ep->queue))
			&& likely(ep->num != 0)
			&& !ep->dma
			&& !(dev->पूर्णांक_enable & INT_EPxDATASET (ep->num)))
		pio_irq_enable(dev, dev->regs, ep->num);

	spin_unlock_irqrestore(&dev->lock, flags);

	/* pci ग_लिखोs may still be posted */
	वापस status;
पूर्ण

/* dequeue ALL requests */
अटल व्योम nuke(काष्ठा goku_ep *ep, पूर्णांक status)
अणु
	काष्ठा goku_request	*req;

	ep->stopped = 1;
	अगर (list_empty(&ep->queue))
		वापस;
	अगर (ep->dma)
		पात_dma(ep, status);
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा goku_request, queue);
		करोne(ep, req, status);
	पूर्ण
पूर्ण

/* dequeue JUST ONE request */
अटल पूर्णांक goku_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा goku_request	*req;
	काष्ठा goku_ep		*ep;
	काष्ठा goku_udc		*dev;
	अचिन्हित दीर्घ		flags;

	ep = container_of(_ep, काष्ठा goku_ep, ep);
	अगर (!_ep || !_req || (!ep->ep.desc && ep->num != 0))
		वापस -EINVAL;
	dev = ep->dev;
	अगर (!dev->driver)
		वापस -ESHUTDOWN;

	/* we can't touch (dma) रेजिस्टरs when suspended */
	अगर (dev->ep0state == EP0_SUSPEND)
		वापस -EBUSY;

	VDBG(dev, "%s %s %s %s %p\n", __func__, _ep->name,
		ep->is_in ? "IN" : "OUT",
		ep->dma ? "dma" : "pio",
		_req);

	spin_lock_irqsave(&dev->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry (req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		spin_unlock_irqrestore (&dev->lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (ep->dma && ep->queue.next == &req->queue && !ep->stopped) अणु
		पात_dma(ep, -ECONNRESET);
		करोne(ep, req, -ECONNRESET);
		dma_advance(dev, ep);
	पूर्ण अन्यथा अगर (!list_empty(&req->queue))
		करोne(ep, req, -ECONNRESET);
	अन्यथा
		req = शून्य;
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस req ? 0 : -EOPNOTSUPP;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम goku_clear_halt(काष्ठा goku_ep *ep)
अणु
	// निश्चित (ep->num !=0)
	VDBG(ep->dev, "%s clear halt\n", ep->ep.name);
	command(ep->dev->regs, COMMAND_SETDATA0, ep->num);
	command(ep->dev->regs, COMMAND_STALL_CLEAR, ep->num);
	अगर (ep->stopped) अणु
		ep->stopped = 0;
		अगर (ep->dma) अणु
			काष्ठा goku_request	*req;

			अगर (list_empty(&ep->queue))
				वापस;
			req = list_entry(ep->queue.next, काष्ठा goku_request,
						queue);
			(व्योम) start_dma(ep, req);
		पूर्ण अन्यथा
			pio_advance(ep);
	पूर्ण
पूर्ण

अटल पूर्णांक goku_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा goku_ep	*ep;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		retval = 0;

	अगर (!_ep)
		वापस -ENODEV;
	ep = container_of (_ep, काष्ठा goku_ep, ep);

	अगर (ep->num == 0) अणु
		अगर (value) अणु
			ep->dev->ep0state = EP0_STALL;
			ep->dev->ep[0].stopped = 1;
		पूर्ण अन्यथा
			वापस -EINVAL;

	/* करोn't change EPxSTATUS_EP_INVALID to READY */
	पूर्ण अन्यथा अगर (!ep->ep.desc) अणु
		DBG(ep->dev, "%s %s inactive?\n", __func__, ep->ep.name);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&ep->dev->lock, flags);
	अगर (!list_empty(&ep->queue))
		retval = -EAGAIN;
	अन्यथा अगर (ep->is_in && value
			/* data in (either) packet buffer? */
			&& (पढ़ोl(&ep->dev->regs->DataSet)
					& DATASET_AB(ep->num)))
		retval = -EAGAIN;
	अन्यथा अगर (!value)
		goku_clear_halt(ep);
	अन्यथा अणु
		ep->stopped = 1;
		VDBG(ep->dev, "%s set halt\n", ep->ep.name);
		command(ep->dev->regs, COMMAND_STALL, ep->num);
		पढ़ोl(ep->reg_status);
	पूर्ण
	spin_unlock_irqrestore(&ep->dev->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक goku_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा goku_ep			*ep;
	काष्ठा goku_udc_regs __iomem	*regs;
	u32				size;

	अगर (!_ep)
		वापस -ENODEV;
	ep = container_of(_ep, काष्ठा goku_ep, ep);

	/* size is only reported sanely क्रम OUT */
	अगर (ep->is_in)
		वापस -EOPNOTSUPP;

	/* ignores 16-byte dma buffer; SizeH == 0 */
	regs = ep->dev->regs;
	size = पढ़ोl(&regs->EPxSizeLA[ep->num]) & DATASIZE;
	size += पढ़ोl(&regs->EPxSizeLB[ep->num]) & DATASIZE;
	VDBG(ep->dev, "%s %s %u\n", __func__, ep->ep.name, size);
	वापस size;
पूर्ण

अटल व्योम goku_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा goku_ep			*ep;
	काष्ठा goku_udc_regs __iomem	*regs;
	u32				size;

	अगर (!_ep)
		वापस;
	ep = container_of(_ep, काष्ठा goku_ep, ep);
	VDBG(ep->dev, "%s %s\n", __func__, ep->ep.name);

	/* करोn't change EPxSTATUS_EP_INVALID to READY */
	अगर (!ep->ep.desc && ep->num != 0) अणु
		DBG(ep->dev, "%s %s inactive?\n", __func__, ep->ep.name);
		वापस;
	पूर्ण

	regs = ep->dev->regs;
	size = पढ़ोl(&regs->EPxSizeLA[ep->num]);
	size &= DATASIZE;

	/* Non-desirable behavior:  FIFO_CLEAR also clears the
	 * endpoपूर्णांक halt feature.  For OUT, we _could_ just पढ़ो
	 * the bytes out (PIO, अगर !ep->dma); क्रम in, no choice.
	 */
	अगर (size)
		command(regs, COMMAND_FIFO_CLEAR, ep->num);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops goku_ep_ops = अणु
	.enable		= goku_ep_enable,
	.disable	= goku_ep_disable,

	.alloc_request	= goku_alloc_request,
	.मुक्त_request	= goku_मुक्त_request,

	.queue		= goku_queue,
	.dequeue	= goku_dequeue,

	.set_halt	= goku_set_halt,
	.fअगरo_status	= goku_fअगरo_status,
	.fअगरo_flush	= goku_fअगरo_flush,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक goku_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा usb_ep *goku_match_ep(काष्ठा usb_gadget *g,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		काष्ठा usb_ss_ep_comp_descriptor *ep_comp)
अणु
	काष्ठा goku_udc	*dev = to_goku_udc(g);
	काष्ठा usb_ep *ep;

	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_INT:
		/* single buffering is enough */
		ep = &dev->ep[3].ep;
		अगर (usb_gadget_ep_match_desc(g, ep, desc, ep_comp))
			वापस ep;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (usb_endpoपूर्णांक_dir_in(desc)) अणु
			/* DMA may be available */
			ep = &dev->ep[2].ep;
			अगर (usb_gadget_ep_match_desc(g, ep, desc, ep_comp))
				वापस ep;
		पूर्ण
		अवरोध;
	शेष:
		/* nothing */ ;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक goku_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक goku_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops goku_ops = अणु
	.get_frame	= goku_get_frame,
	.udc_start	= goku_udc_start,
	.udc_stop	= goku_udc_stop,
	.match_ep	= goku_match_ep,
	// no remote wakeup
	// not selfघातered
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल अंतरभूत स्थिर अक्षर *dmastr(व्योम)
अणु
	अगर (use_dma == 0)
		वापस "(dma disabled)";
	अन्यथा अगर (use_dma == 2)
		वापस "(dma IN and OUT)";
	अन्यथा
		वापस "(dma IN)";
पूर्ण

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

अटल स्थिर अक्षर proc_node_name [] = "driver/udc";

#घोषणा FOURBITS "%s%s%s%s"
#घोषणा EIGHTBITS FOURBITS FOURBITS

अटल व्योम dump_पूर्णांकmask(काष्ठा seq_file *m, स्थिर अक्षर *label, u32 mask)
अणु
	/* पूर्णांक_status is the same क्रमmat ... */
	seq_म_लिखो(m, "%s %05X =" FOURBITS EIGHTBITS EIGHTBITS "\n",
		   label, mask,
		   (mask & INT_PWRDETECT) ? " power" : "",
		   (mask & INT_SYSERROR) ? " sys" : "",
		   (mask & INT_MSTRDEND) ? " in-dma" : "",
		   (mask & INT_MSTWRTMOUT) ? " wrtmo" : "",

		   (mask & INT_MSTWREND) ? " out-dma" : "",
		   (mask & INT_MSTWRSET) ? " wrset" : "",
		   (mask & INT_ERR) ? " err" : "",
		   (mask & INT_SOF) ? " sof" : "",

		   (mask & INT_EP3NAK) ? " ep3nak" : "",
		   (mask & INT_EP2NAK) ? " ep2nak" : "",
		   (mask & INT_EP1NAK) ? " ep1nak" : "",
		   (mask & INT_EP3DATASET) ? " ep3" : "",

		   (mask & INT_EP2DATASET) ? " ep2" : "",
		   (mask & INT_EP1DATASET) ? " ep1" : "",
		   (mask & INT_STATUSNAK) ? " ep0snak" : "",
		   (mask & INT_STATUS) ? " ep0status" : "",

		   (mask & INT_SETUP) ? " setup" : "",
		   (mask & INT_ENDPOINT0) ? " ep0" : "",
		   (mask & INT_USBRESET) ? " reset" : "",
		   (mask & INT_SUSPEND) ? " suspend" : "");
पूर्ण

अटल स्थिर अक्षर *udc_ep_state(क्रमागत ep0state state)
अणु
	चयन (state) अणु
	हाल EP0_DISCONNECT:
		वापस "ep0_disconnect";
	हाल EP0_IDLE:
		वापस "ep0_idle";
	हाल EP0_IN:
		वापस "ep0_in";
	हाल EP0_OUT:
		वापस "ep0_out";
	हाल EP0_STATUS:
		वापस "ep0_status";
	हाल EP0_STALL:
		वापस "ep0_stall";
	हाल EP0_SUSPEND:
		वापस "ep0_suspend";
	पूर्ण

	वापस "ep0_?";
पूर्ण

अटल स्थिर अक्षर *udc_ep_status(u32 status)
अणु
	चयन (status & EPxSTATUS_EP_MASK) अणु
	हाल EPxSTATUS_EP_READY:
		वापस "ready";
	हाल EPxSTATUS_EP_DATAIN:
		वापस "packet";
	हाल EPxSTATUS_EP_FULL:
		वापस "full";
	हाल EPxSTATUS_EP_TX_ERR:	/* host will retry */
		वापस "tx_err";
	हाल EPxSTATUS_EP_RX_ERR:
		वापस "rx_err";
	हाल EPxSTATUS_EP_BUSY:		/* ep0 only */
		वापस "busy";
	हाल EPxSTATUS_EP_STALL:
		वापस "stall";
	हाल EPxSTATUS_EP_INVALID:	/* these "can't happen" */
		वापस "invalid";
	पूर्ण

	वापस "?";
पूर्ण

अटल पूर्णांक udc_proc_पढ़ो(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा goku_udc			*dev = m->निजी;
	काष्ठा goku_udc_regs __iomem	*regs = dev->regs;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				i, is_usb_connected;
	u32				पंचांगp;

	local_irq_save(flags);

	/* basic device status */
	पंचांगp = पढ़ोl(&regs->घातer_detect);
	is_usb_connected = पंचांगp & PW_DETECT;
	seq_म_लिखो(m,
		   "%s - %s\n"
		   "%s version: %s %s\n"
		   "Gadget driver: %s\n"
		   "Host %s, %s\n"
		   "\n",
		   pci_name(dev->pdev), driver_desc,
		   driver_name, DRIVER_VERSION, dmastr(),
		   dev->driver ? dev->driver->driver.name : "(none)",
		   is_usb_connected
			   ? ((पंचांगp & PW_PULLUP) ? "full speed" : "powered")
			   : "disconnected",
		   udc_ep_state(dev->ep0state));

	dump_पूर्णांकmask(m, "int_status", पढ़ोl(&regs->पूर्णांक_status));
	dump_पूर्णांकmask(m, "int_enable", पढ़ोl(&regs->पूर्णांक_enable));

	अगर (!is_usb_connected || !dev->driver || (पंचांगp & PW_PULLUP) == 0)
		जाओ करोne;

	/* रेजिस्टरs क्रम (active) device and ep0 */
	seq_म_लिखो(m, "\nirqs %lu\ndataset %02x single.bcs %02x.%02x state %x addr %u\n",
		   dev->irqs, पढ़ोl(&regs->DataSet),
		   पढ़ोl(&regs->EPxSingle), पढ़ोl(&regs->EPxBCS),
		   पढ़ोl(&regs->UsbState),
		   पढ़ोl(&regs->address));
	अगर (seq_has_overflowed(m))
		जाओ करोne;

	पंचांगp = पढ़ोl(&regs->dma_master);
	seq_म_लिखो(m, "dma %03X =" EIGHTBITS "%s %s\n",
		   पंचांगp,
		   (पंचांगp & MST_EOPB_DIS) ? " eopb-" : "",
		   (पंचांगp & MST_EOPB_ENA) ? " eopb+" : "",
		   (पंचांगp & MST_TIMEOUT_DIS) ? " tmo-" : "",
		   (पंचांगp & MST_TIMEOUT_ENA) ? " tmo+" : "",

		   (पंचांगp & MST_RD_EOPB) ? " eopb" : "",
		   (पंचांगp & MST_RD_RESET) ? " in_reset" : "",
		   (पंचांगp & MST_WR_RESET) ? " out_reset" : "",
		   (पंचांगp & MST_RD_ENA) ? " IN" : "",

		   (पंचांगp & MST_WR_ENA) ? " OUT" : "",
		   (पंचांगp & MST_CONNECTION) ? "ep1in/ep2out" : "ep1out/ep2in");
	अगर (seq_has_overflowed(m))
		जाओ करोne;

	/* dump endpoपूर्णांक queues */
	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा goku_ep		*ep = &dev->ep [i];
		काष्ठा goku_request	*req;

		अगर (i && !ep->ep.desc)
			जारी;

		पंचांगp = पढ़ोl(ep->reg_status);
		seq_म_लिखो(m, "%s %s max %u %s, irqs %lu, status %02x (%s) " FOURBITS "\n",
			   ep->ep.name,
			   ep->is_in ? "in" : "out",
			   ep->ep.maxpacket,
			   ep->dma ? "dma" : "pio",
			   ep->irqs,
			   पंचांगp, udc_ep_status(पंचांगp),
			   (पंचांगp & EPxSTATUS_TOGGLE) ? "data1" : "data0",
			   (पंचांगp & EPxSTATUS_SUSPEND) ? " suspend" : "",
			   (पंचांगp & EPxSTATUS_FIFO_DISABLE) ? " disable" : "",
			   (पंचांगp & EPxSTATUS_STAGE_ERROR) ? " ep0stat" : "");
		अगर (seq_has_overflowed(m))
			जाओ करोne;

		अगर (list_empty(&ep->queue)) अणु
			seq_माला_दो(m, "\t(nothing queued)\n");
			अगर (seq_has_overflowed(m))
				जाओ करोne;
			जारी;
		पूर्ण
		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			अगर (ep->dma && req->queue.prev == &ep->queue) अणु
				अगर (i == UDC_MSTRD_ENDPOINT)
					पंचांगp = पढ़ोl(&regs->in_dma_current);
				अन्यथा
					पंचांगp = पढ़ोl(&regs->out_dma_current);
				पंचांगp -= req->req.dma;
				पंचांगp++;
			पूर्ण अन्यथा
				पंचांगp = req->req.actual;

			seq_म_लिखो(m, "\treq %p len %u/%u buf %p\n",
				   &req->req, पंचांगp, req->req.length,
				   req->req.buf);
			अगर (seq_has_overflowed(m))
				जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	local_irq_restore(flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_USB_GADGET_DEBUG_खाताS */

/*-------------------------------------------------------------------------*/

अटल व्योम udc_reinit (काष्ठा goku_udc *dev)
अणु
	अटल अक्षर *names [] = अणु "ep0", "ep1-bulk", "ep2-bulk", "ep3-bulk" पूर्ण;

	अचिन्हित i;

	INIT_LIST_HEAD (&dev->gadget.ep_list);
	dev->gadget.ep0 = &dev->ep [0].ep;
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->ep0state = EP0_DISCONNECT;
	dev->irqs = 0;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा goku_ep	*ep = &dev->ep[i];

		ep->num = i;
		ep->ep.name = names[i];
		ep->reg_fअगरo = &dev->regs->ep_fअगरo [i];
		ep->reg_status = &dev->regs->ep_status [i];
		ep->reg_mode = &dev->regs->ep_mode[i];

		ep->ep.ops = &goku_ep_ops;
		list_add_tail (&ep->ep.ep_list, &dev->gadget.ep_list);
		ep->dev = dev;
		INIT_LIST_HEAD (&ep->queue);

		ep_reset(शून्य, ep);

		अगर (i == 0)
			ep->ep.caps.type_control = true;
		अन्यथा
			ep->ep.caps.type_bulk = true;

		ep->ep.caps.dir_in = true;
		ep->ep.caps.dir_out = true;
	पूर्ण

	dev->ep[0].reg_mode = शून्य;
	usb_ep_set_maxpacket_limit(&dev->ep[0].ep, MAX_EP0_SIZE);
	list_del_init (&dev->ep[0].ep.ep_list);
पूर्ण

अटल व्योम udc_reset(काष्ठा goku_udc *dev)
अणु
	काष्ठा goku_udc_regs __iomem	*regs = dev->regs;

	ग_लिखोl(0, &regs->घातer_detect);
	ग_लिखोl(0, &regs->पूर्णांक_enable);
	पढ़ोl(&regs->पूर्णांक_enable);
	dev->पूर्णांक_enable = 0;

	/* deनिश्चित reset, leave USB D+ at hi-Z (no pullup)
	 * करोn't let INT_PWRDETECT sequence begin
	 */
	udelay(250);
	ग_लिखोl(PW_RESETB, &regs->घातer_detect);
	पढ़ोl(&regs->पूर्णांक_enable);
पूर्ण

अटल व्योम ep0_start(काष्ठा goku_udc *dev)
अणु
	काष्ठा goku_udc_regs __iomem	*regs = dev->regs;
	अचिन्हित			i;

	VDBG(dev, "%s\n", __func__);

	udc_reset(dev);
	udc_reinit (dev);
	//ग_लिखोl(MST_EOPB_ENA | MST_TIMEOUT_ENA, &regs->dma_master);

	/* hw handles set_address, set_feature, get_status; maybe more */
	ग_लिखोl(   G_REQMODE_SET_INTF | G_REQMODE_GET_INTF
		| G_REQMODE_SET_CONF | G_REQMODE_GET_CONF
		| G_REQMODE_GET_DESC
		| G_REQMODE_CLEAR_FEAT
		, &regs->reqmode);

	क्रम (i = 0; i < 4; i++)
		dev->ep[i].irqs = 0;

	/* can't modअगरy descriptors after writing UsbReady */
	क्रम (i = 0; i < DESC_LEN; i++)
		ग_लिखोl(0, &regs->descriptors[i]);
	ग_लिखोl(0, &regs->UsbReady);

	/* expect ep0 requests when the host drops reset */
	ग_लिखोl(PW_RESETB | PW_PULLUP, &regs->घातer_detect);
	dev->पूर्णांक_enable = INT_DEVWIDE | INT_EP0;
	ग_लिखोl(dev->पूर्णांक_enable, &dev->regs->पूर्णांक_enable);
	पढ़ोl(&regs->पूर्णांक_enable);
	dev->gadget.speed = USB_SPEED_FULL;
	dev->ep0state = EP0_IDLE;
पूर्ण

अटल व्योम udc_enable(काष्ठा goku_udc *dev)
अणु
	/* start क्रमागतeration now, or after घातer detect irq */
	अगर (पढ़ोl(&dev->regs->घातer_detect) & PW_DETECT)
		ep0_start(dev);
	अन्यथा अणु
		DBG(dev, "%s\n", __func__);
		dev->पूर्णांक_enable = INT_PWRDETECT;
		ग_लिखोl(dev->पूर्णांक_enable, &dev->regs->पूर्णांक_enable);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

/* keeping it simple:
 * - one bus driver, initted first;
 * - one function driver, initted second
 */

/* when a driver is successfully रेजिस्टरed, it will receive
 * control requests including set_configuration(), which enables
 * non-control requests.  then usb traffic follows until a
 * disconnect is reported.  then a host may connect again, or
 * the driver might get unbound.
 */
अटल पूर्णांक goku_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा goku_udc	*dev = to_goku_udc(g);

	/* hook up the driver */
	driver->driver.bus = शून्य;
	dev->driver = driver;

	/*
	 * then enable host detection and ep0; and we're पढ़ोy
	 * क्रम set_configuration as well as eventual disconnect.
	 */
	udc_enable(dev);

	वापस 0;
पूर्ण

अटल व्योम stop_activity(काष्ठा goku_udc *dev)
अणु
	अचिन्हित	i;

	DBG (dev, "%s\n", __func__);

	/* disconnect gadget driver after quiesceing hw and the driver */
	udc_reset (dev);
	क्रम (i = 0; i < 4; i++)
		nuke(&dev->ep [i], -ESHUTDOWN);

	अगर (dev->driver)
		udc_enable(dev);
पूर्ण

अटल पूर्णांक goku_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा goku_udc	*dev = to_goku_udc(g);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&dev->lock, flags);
	dev->driver = शून्य;
	stop_activity(dev);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम ep0_setup(काष्ठा goku_udc *dev)
अणु
	काष्ठा goku_udc_regs __iomem	*regs = dev->regs;
	काष्ठा usb_ctrlrequest		ctrl;
	पूर्णांक				पंचांगp;

	/* पढ़ो SETUP packet and enter DATA stage */
	ctrl.bRequestType = पढ़ोl(&regs->bRequestType);
	ctrl.bRequest = पढ़ोl(&regs->bRequest);
	ctrl.wValue  = cpu_to_le16((पढ़ोl(&regs->wValueH)  << 8)
					| पढ़ोl(&regs->wValueL));
	ctrl.wIndex  = cpu_to_le16((पढ़ोl(&regs->wIndexH)  << 8)
					| पढ़ोl(&regs->wIndexL));
	ctrl.wLength = cpu_to_le16((पढ़ोl(&regs->wLengthH) << 8)
					| पढ़ोl(&regs->wLengthL));
	ग_लिखोl(0, &regs->SetupRecv);

	nuke(&dev->ep[0], 0);
	dev->ep[0].stopped = 0;
	अगर (likely(ctrl.bRequestType & USB_सूची_IN)) अणु
		dev->ep[0].is_in = 1;
		dev->ep0state = EP0_IN;
		/* detect early status stages */
		ग_लिखोl(ICONTROL_STATUSNAK, &dev->regs->IntControl);
	पूर्ण अन्यथा अणु
		dev->ep[0].is_in = 0;
		dev->ep0state = EP0_OUT;

		/* NOTE:  CLEAR_FEATURE is करोne in software so that we can
		 * synchronize transfer restarts after bulk IN stalls.  data
		 * won't even enter the fअगरo until the halt is cleared.
		 */
		चयन (ctrl.bRequest) अणु
		हाल USB_REQ_CLEAR_FEATURE:
			चयन (ctrl.bRequestType) अणु
			हाल USB_RECIP_ENDPOINT:
				पंचांगp = le16_to_cpu(ctrl.wIndex) & 0x0f;
				/* active endpoपूर्णांक */
				अगर (पंचांगp > 3 ||
				    (!dev->ep[पंचांगp].ep.desc && पंचांगp != 0))
					जाओ stall;
				अगर (ctrl.wIndex & cpu_to_le16(
						USB_सूची_IN)) अणु
					अगर (!dev->ep[पंचांगp].is_in)
						जाओ stall;
				पूर्ण अन्यथा अणु
					अगर (dev->ep[पंचांगp].is_in)
						जाओ stall;
				पूर्ण
				अगर (ctrl.wValue != cpu_to_le16(
						USB_ENDPOINT_HALT))
					जाओ stall;
				अगर (पंचांगp)
					goku_clear_halt(&dev->ep[पंचांगp]);
succeed:
				/* start ep0out status stage */
				ग_लिखोl(~(1<<0), &regs->EOP);
				dev->ep[0].stopped = 1;
				dev->ep0state = EP0_STATUS;
				वापस;
			हाल USB_RECIP_DEVICE:
				/* device remote wakeup: always clear */
				अगर (ctrl.wValue != cpu_to_le16(1))
					जाओ stall;
				VDBG(dev, "clear dev remote wakeup\n");
				जाओ succeed;
			हाल USB_RECIP_INTERFACE:
				जाओ stall;
			शेष:		/* pass to gadget driver */
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

#अगर_घोषित USB_TRACE
	VDBG(dev, "SETUP %02x.%02x v%04x i%04x l%04x\n",
		ctrl.bRequestType, ctrl.bRequest,
		le16_to_cpu(ctrl.wValue), le16_to_cpu(ctrl.wIndex),
		le16_to_cpu(ctrl.wLength));
#पूर्ण_अगर

	/* hw wants to know when we're configured (or not) */
	dev->req_config = (ctrl.bRequest == USB_REQ_SET_CONFIGURATION
				&& ctrl.bRequestType == USB_RECIP_DEVICE);
	अगर (unlikely(dev->req_config))
		dev->configured = (ctrl.wValue != cpu_to_le16(0));

	/* delegate everything to the gadget driver.
	 * it may respond after this irq handler वापसs.
	 */
	spin_unlock (&dev->lock);
	पंचांगp = dev->driver->setup(&dev->gadget, &ctrl);
	spin_lock (&dev->lock);
	अगर (unlikely(पंचांगp < 0)) अणु
stall:
#अगर_घोषित USB_TRACE
		VDBG(dev, "req %02x.%02x protocol STALL; err %d\n",
				ctrl.bRequestType, ctrl.bRequest, पंचांगp);
#पूर्ण_अगर
		command(regs, COMMAND_STALL, 0);
		dev->ep[0].stopped = 1;
		dev->ep0state = EP0_STALL;
	पूर्ण

	/* expect at least one data or status stage irq */
पूर्ण

#घोषणा ACK(irqbit) अणु \
		stat &= ~irqbit; \
		ग_लिखोl(~irqbit, &regs->पूर्णांक_status); \
		handled = 1; \
		पूर्ण

अटल irqवापस_t goku_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा goku_udc			*dev = _dev;
	काष्ठा goku_udc_regs __iomem	*regs = dev->regs;
	काष्ठा goku_ep			*ep;
	u32				stat, handled = 0;
	अचिन्हित			i, rescans = 5;

	spin_lock(&dev->lock);

rescan:
	stat = पढ़ोl(&regs->पूर्णांक_status) & dev->पूर्णांक_enable;
        अगर (!stat)
		जाओ करोne;
	dev->irqs++;

	/* device-wide irqs */
	अगर (unlikely(stat & INT_DEVWIDE)) अणु
		अगर (stat & INT_SYSERROR) अणु
			ERROR(dev, "system error\n");
			stop_activity(dev);
			stat = 0;
			handled = 1;
			// FIXME have a neater way to prevent re-क्रमागतeration
			dev->driver = शून्य;
			जाओ करोne;
		पूर्ण
		अगर (stat & INT_PWRDETECT) अणु
			ग_लिखोl(~stat, &regs->पूर्णांक_status);
			अगर (पढ़ोl(&dev->regs->घातer_detect) & PW_DETECT) अणु
				VDBG(dev, "connect\n");
				ep0_start(dev);
			पूर्ण अन्यथा अणु
				DBG(dev, "disconnect\n");
				अगर (dev->gadget.speed == USB_SPEED_FULL)
					stop_activity(dev);
				dev->ep0state = EP0_DISCONNECT;
				dev->पूर्णांक_enable = INT_DEVWIDE;
				ग_लिखोl(dev->पूर्णांक_enable, &dev->regs->पूर्णांक_enable);
			पूर्ण
			stat = 0;
			handled = 1;
			जाओ करोne;
		पूर्ण
		अगर (stat & INT_SUSPEND) अणु
			ACK(INT_SUSPEND);
			अगर (पढ़ोl(&regs->ep_status[0]) & EPxSTATUS_SUSPEND) अणु
				चयन (dev->ep0state) अणु
				हाल EP0_DISCONNECT:
				हाल EP0_SUSPEND:
					जाओ pm_next;
				शेष:
					अवरोध;
				पूर्ण
				DBG(dev, "USB suspend\n");
				dev->ep0state = EP0_SUSPEND;
				अगर (dev->gadget.speed != USB_SPEED_UNKNOWN
						&& dev->driver
						&& dev->driver->suspend) अणु
					spin_unlock(&dev->lock);
					dev->driver->suspend(&dev->gadget);
					spin_lock(&dev->lock);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (dev->ep0state != EP0_SUSPEND) अणु
					DBG(dev, "bogus USB resume %d\n",
						dev->ep0state);
					जाओ pm_next;
				पूर्ण
				DBG(dev, "USB resume\n");
				dev->ep0state = EP0_IDLE;
				अगर (dev->gadget.speed != USB_SPEED_UNKNOWN
						&& dev->driver
						&& dev->driver->resume) अणु
					spin_unlock(&dev->lock);
					dev->driver->resume(&dev->gadget);
					spin_lock(&dev->lock);
				पूर्ण
			पूर्ण
		पूर्ण
pm_next:
		अगर (stat & INT_USBRESET) अणु		/* hub reset करोne */
			ACK(INT_USBRESET);
			INFO(dev, "USB reset done, gadget %s\n",
				dev->driver->driver.name);
		पूर्ण
		// and INT_ERR on some endpoपूर्णांक's crc/bitstuff/... problem
	पूर्ण

	/* progress ep0 setup, data, or status stages.
	 * no transition अणुEP0_STATUS, EP0_STALLपूर्ण --> EP0_IDLE; saves irqs
	 */
	अगर (stat & INT_SETUP) अणु
		ACK(INT_SETUP);
		dev->ep[0].irqs++;
		ep0_setup(dev);
	पूर्ण
        अगर (stat & INT_STATUSNAK) अणु
		ACK(INT_STATUSNAK|INT_ENDPOINT0);
		अगर (dev->ep0state == EP0_IN) अणु
			ep = &dev->ep[0];
			ep->irqs++;
			nuke(ep, 0);
			ग_लिखोl(~(1<<0), &regs->EOP);
			dev->ep0state = EP0_STATUS;
		पूर्ण
	पूर्ण
        अगर (stat & INT_ENDPOINT0) अणु
		ACK(INT_ENDPOINT0);
		ep = &dev->ep[0];
		ep->irqs++;
		pio_advance(ep);
        पूर्ण

	/* dma completion */
        अगर (stat & INT_MSTRDEND) अणु	/* IN */
		ACK(INT_MSTRDEND);
		ep = &dev->ep[UDC_MSTRD_ENDPOINT];
		ep->irqs++;
		dma_advance(dev, ep);
        पूर्ण
        अगर (stat & INT_MSTWREND) अणु	/* OUT */
		ACK(INT_MSTWREND);
		ep = &dev->ep[UDC_MSTWR_ENDPOINT];
		ep->irqs++;
		dma_advance(dev, ep);
        पूर्ण
        अगर (stat & INT_MSTWRTMOUT) अणु	/* OUT */
		ACK(INT_MSTWRTMOUT);
		ep = &dev->ep[UDC_MSTWR_ENDPOINT];
		ep->irqs++;
		ERROR(dev, "%s write timeout ?\n", ep->ep.name);
		// reset dma? then dma_advance()
        पूर्ण

	/* pio */
	क्रम (i = 1; i < 4; i++) अणु
		u32		पंचांगp = INT_EPxDATASET(i);

		अगर (!(stat & पंचांगp))
			जारी;
		ep = &dev->ep[i];
		pio_advance(ep);
		अगर (list_empty (&ep->queue))
			pio_irq_disable(dev, regs, i);
		stat &= ~पंचांगp;
		handled = 1;
		ep->irqs++;
	पूर्ण

	अगर (rescans--)
		जाओ rescan;

करोne:
	(व्योम)पढ़ोl(&regs->पूर्णांक_enable);
	spin_unlock(&dev->lock);
	अगर (stat)
		DBG(dev, "unhandled irq status: %05x (%05x, %05x)\n", stat,
				पढ़ोl(&regs->पूर्णांक_status), dev->पूर्णांक_enable);
	वापस IRQ_RETVAL(handled);
पूर्ण

#अघोषित ACK

/*-------------------------------------------------------------------------*/

अटल व्योम gadget_release(काष्ठा device *_dev)
अणु
	काष्ठा goku_udc	*dev = dev_get_drvdata(_dev);

	kमुक्त(dev);
पूर्ण

/* tear करोwn the binding between this driver and the pci device */

अटल व्योम goku_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा goku_udc		*dev = pci_get_drvdata(pdev);

	DBG(dev, "%s\n", __func__);

	usb_del_gadget_udc(&dev->gadget);

	BUG_ON(dev->driver);

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	हटाओ_proc_entry(proc_node_name, शून्य);
#पूर्ण_अगर
	अगर (dev->regs)
		udc_reset(dev);
	अगर (dev->got_irq)
		मुक्त_irq(pdev->irq, dev);
	अगर (dev->regs)
		iounmap(dev->regs);
	अगर (dev->got_region)
		release_mem_region(pci_resource_start (pdev, 0),
				pci_resource_len (pdev, 0));
	अगर (dev->enabled)
		pci_disable_device(pdev);

	dev->regs = शून्य;

	INFO(dev, "unbind\n");
पूर्ण

/* wrap this driver around the specअगरied pci device, but
 * करोn't respond over USB until a gadget driver binds to us.
 */

अटल पूर्णांक goku_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा goku_udc		*dev = शून्य;
	अचिन्हित दीर्घ		resource, len;
	व्योम __iomem		*base = शून्य;
	पूर्णांक			retval;

	अगर (!pdev->irq) अणु
		prपूर्णांकk(KERN_ERR "Check PCI %s IRQ setup!\n", pci_name(pdev));
		retval = -ENODEV;
		जाओ err;
	पूर्ण

	/* alloc, and start init */
	dev = kzalloc (माप *dev, GFP_KERNEL);
	अगर (!dev) अणु
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	pci_set_drvdata(pdev, dev);
	spin_lock_init(&dev->lock);
	dev->pdev = pdev;
	dev->gadget.ops = &goku_ops;
	dev->gadget.max_speed = USB_SPEED_FULL;

	/* the "gadget" असलtracts/भवizes the controller */
	dev->gadget.name = driver_name;

	/* now all the pci goodies ... */
	retval = pci_enable_device(pdev);
	अगर (retval < 0) अणु
		DBG(dev, "can't enable, %d\n", retval);
		जाओ err;
	पूर्ण
	dev->enabled = 1;

	resource = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);
	अगर (!request_mem_region(resource, len, driver_name)) अणु
		DBG(dev, "controller already in use\n");
		retval = -EBUSY;
		जाओ err;
	पूर्ण
	dev->got_region = 1;

	base = ioremap(resource, len);
	अगर (base == शून्य) अणु
		DBG(dev, "can't map memory\n");
		retval = -EFAULT;
		जाओ err;
	पूर्ण
	dev->regs = (काष्ठा goku_udc_regs __iomem *) base;

	INFO(dev, "%s\n", driver_desc);
	INFO(dev, "version: " DRIVER_VERSION " %s\n", dmastr());
	INFO(dev, "irq %d, pci mem %p\n", pdev->irq, base);

	/* init to known state, then setup irqs */
	udc_reset(dev);
	udc_reinit (dev);
	अगर (request_irq(pdev->irq, goku_irq, IRQF_SHARED,
			driver_name, dev) != 0) अणु
		DBG(dev, "request interrupt %d failed\n", pdev->irq);
		retval = -EBUSY;
		जाओ err;
	पूर्ण
	dev->got_irq = 1;
	अगर (use_dma)
		pci_set_master(pdev);


#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	proc_create_single_data(proc_node_name, 0, शून्य, udc_proc_पढ़ो, dev);
#पूर्ण_अगर

	retval = usb_add_gadget_udc_release(&pdev->dev, &dev->gadget,
			gadget_release);
	अगर (retval)
		जाओ err;

	वापस 0;

err:
	अगर (dev)
		goku_हटाओ (pdev);
	/* gadget_release is not रेजिस्टरed yet, kमुक्त explicitly */
	kमुक्त(dev);
	वापस retval;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु अणु
	.class =	PCI_CLASS_SERIAL_USB_DEVICE,
	.class_mask =	~0,
	.venकरोr =	0x102f,		/* Toshiba */
	.device =	0x0107,		/* this UDC */
	.subvenकरोr =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,

पूर्ण, अणु /* end: all zeroes */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (pci, pci_ids);

अटल काष्ठा pci_driver goku_pci_driver = अणु
	.name =		driver_name,
	.id_table =	pci_ids,

	.probe =	goku_probe,
	.हटाओ =	goku_हटाओ,

	/* FIXME add घातer management support */
पूर्ण;

module_pci_driver(goku_pci_driver);
