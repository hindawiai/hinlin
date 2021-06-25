<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * omap_udc.c -- क्रम OMAP full speed udc; most chips support OTG.
 *
 * Copyright (C) 2004 Texas Instruments, Inc.
 * Copyright (C) 2004-2005 David Brownell
 *
 * OMAP2 & DMA support by Kyungmin Park <kyungmin.park@samsung.com>
 */

#अघोषित	DEBUG
#अघोषित	VERBOSE

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/omap-dma.h>

#समावेश <mach/usb.h>

#समावेश "omap_udc.h"

#अघोषित	USB_TRACE

/* bulk DMA seems to be behaving क्रम both IN and OUT */
#घोषणा	USE_DMA

/* ISO too */
#घोषणा	USE_ISO

#घोषणा	DRIVER_DESC	"OMAP UDC driver"
#घोषणा	DRIVER_VERSION	"4 October 2004"

#घोषणा OMAP_DMA_USB_W2FC_TX0		29
#घोषणा OMAP_DMA_USB_W2FC_RX0		26

/*
 * The OMAP UDC needs _very_ early endpoपूर्णांक setup:  beक्रमe enabling the
 * D+ pullup to allow क्रमागतeration.  That's too early क्रम the gadget
 * framework to use from usb_endpoपूर्णांक_enable(), which happens after
 * क्रमागतeration as part of activating an पूर्णांकerface.  (But अगर we add an
 * optional new "UDC not yet running" state to the gadget driver model,
 * even just during driver binding, the endpoपूर्णांक स्वतःconfig logic is the
 * natural spot to manufacture new endpoपूर्णांकs.)
 *
 * So instead of using endpoपूर्णांक enable calls to control the hardware setup,
 * this driver defines a "fifo mode" parameter.  It's used during driver
 * initialization to choose among a set of pre-defined endpoपूर्णांक configs.
 * See omap_udc_setup() क्रम available modes, or to add others.  That code
 * lives in an init section, so use this driver as a module अगर you need
 * to change the fअगरo mode after the kernel boots.
 *
 * Gadget drivers normally ignore endpoपूर्णांकs they करोn't care about, and
 * won't include them in configuration descriptors.  That means only
 * misbehaving hosts would even notice they exist.
 */
#अगर_घोषित	USE_ISO
अटल अचिन्हित fअगरo_mode = 3;
#अन्यथा
अटल अचिन्हित fअगरo_mode;
#पूर्ण_अगर

/* "modprobe omap_udc fifo_mode=42", or अन्यथा as a kernel
 * boot parameter "omap_udc:fifo_mode=42"
 */
module_param(fअगरo_mode, uपूर्णांक, 0);
MODULE_PARM_DESC(fअगरo_mode, "endpoint configuration");

#अगर_घोषित	USE_DMA
अटल bool use_dma = 1;

/* "modprobe omap_udc use_dma=y", or अन्यथा as a kernel
 * boot parameter "omap_udc:use_dma=y"
 */
module_param(use_dma, bool, 0);
MODULE_PARM_DESC(use_dma, "enable/disable DMA");
#अन्यथा	/* !USE_DMA */

/* save a bit of code */
#घोषणा	use_dma		0
#पूर्ण_अगर	/* !USE_DMA */


अटल स्थिर अक्षर driver_name[] = "omap_udc";
अटल स्थिर अक्षर driver_desc[] = DRIVER_DESC;

/*-------------------------------------------------------------------------*/

/* there's a notion of "current endpoint" क्रम modअगरying endpoपूर्णांक
 * state, and PIO access to its FIFO.
 */

अटल व्योम use_ep(काष्ठा omap_ep *ep, u16 select)
अणु
	u16	num = ep->bEndpoपूर्णांकAddress & 0x0f;

	अगर (ep->bEndpoपूर्णांकAddress & USB_सूची_IN)
		num |= UDC_EP_सूची;
	omap_ग_लिखोw(num | select, UDC_EP_NUM);
	/* when select, MUST deselect later !! */
पूर्ण

अटल अंतरभूत व्योम deselect_ep(व्योम)
अणु
	u16 w;

	w = omap_पढ़ोw(UDC_EP_NUM);
	w &= ~UDC_EP_SEL;
	omap_ग_लिखोw(w, UDC_EP_NUM);
	/* 6 रुको states beक्रमe TX will happen */
पूर्ण

अटल व्योम dma_channel_claim(काष्ठा omap_ep *ep, अचिन्हित preferred);

/*-------------------------------------------------------------------------*/

अटल पूर्णांक omap_ep_enable(काष्ठा usb_ep *_ep,
		स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा omap_ep	*ep = container_of(_ep, काष्ठा omap_ep, ep);
	काष्ठा omap_udc	*udc;
	अचिन्हित दीर्घ	flags;
	u16		maxp;

	/* catch various bogus parameters */
	अगर (!_ep || !desc
			|| desc->bDescriptorType != USB_DT_ENDPOINT
			|| ep->bEndpoपूर्णांकAddress != desc->bEndpoपूर्णांकAddress
			|| ep->maxpacket < usb_endpoपूर्णांक_maxp(desc)) अणु
		DBG("%s, bad ep or descriptor\n", __func__);
		वापस -EINVAL;
	पूर्ण
	maxp = usb_endpoपूर्णांक_maxp(desc);
	अगर ((desc->bmAttributes == USB_ENDPOINT_XFER_BULK
				&& maxp != ep->maxpacket)
			|| usb_endpoपूर्णांक_maxp(desc) > ep->maxpacket
			|| !desc->wMaxPacketSize) अणु
		DBG("%s, bad %s maxpacket\n", __func__, _ep->name);
		वापस -दुस्फल;
	पूर्ण

#अगर_घोषित	USE_ISO
	अगर ((desc->bmAttributes == USB_ENDPOINT_XFER_ISOC
				&& desc->bInterval != 1)) अणु
		/* hardware wants period = 1; USB allows 2^(Interval-1) */
		DBG("%s, unsupported ISO period %dms\n", _ep->name,
				1 << (desc->bInterval - 1));
		वापस -गलत_तर्क;
	पूर्ण
#अन्यथा
	अगर (desc->bmAttributes == USB_ENDPOINT_XFER_ISOC) अणु
		DBG("%s, ISO nyet\n", _ep->name);
		वापस -गलत_तर्क;
	पूर्ण
#पूर्ण_अगर

	/* xfer types must match, except that पूर्णांकerrupt ~= bulk */
	अगर (ep->bmAttributes != desc->bmAttributes
			&& ep->bmAttributes != USB_ENDPOINT_XFER_BULK
			&& desc->bmAttributes != USB_ENDPOINT_XFER_INT) अणु
		DBG("%s, %s type mismatch\n", __func__, _ep->name);
		वापस -EINVAL;
	पूर्ण

	udc = ep->udc;
	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		DBG("%s, bogus device state\n", __func__);
		वापस -ESHUTDOWN;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	ep->ep.desc = desc;
	ep->irqs = 0;
	ep->stopped = 0;
	ep->ep.maxpacket = maxp;

	/* set endpoपूर्णांक to initial state */
	ep->dma_channel = 0;
	ep->has_dma = 0;
	ep->lch = -1;
	use_ep(ep, UDC_EP_SEL);
	omap_ग_लिखोw(udc->clr_halt, UDC_CTRL);
	ep->ackरुको = 0;
	deselect_ep();

	अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC)
		list_add(&ep->iso, &udc->iso);

	/* maybe assign a DMA channel to this endpoपूर्णांक */
	अगर (use_dma && desc->bmAttributes == USB_ENDPOINT_XFER_BULK)
		/* FIXME ISO can dma, but prefers first channel */
		dma_channel_claim(ep, 0);

	/* PIO OUT may RX packets */
	अगर (desc->bmAttributes != USB_ENDPOINT_XFER_ISOC
			&& !ep->has_dma
			&& !(ep->bEndpoपूर्णांकAddress & USB_सूची_IN)) अणु
		omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
		ep->ackरुको = 1 + ep->द्विगुन_buf;
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	VDBG("%s enabled\n", _ep->name);
	वापस 0;
पूर्ण

अटल व्योम nuke(काष्ठा omap_ep *, पूर्णांक status);

अटल पूर्णांक omap_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा omap_ep	*ep = container_of(_ep, काष्ठा omap_ep, ep);
	अचिन्हित दीर्घ	flags;

	अगर (!_ep || !ep->ep.desc) अणु
		DBG("%s, %s not enabled\n", __func__,
			_ep ? ep->ep.name : शून्य);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&ep->udc->lock, flags);
	ep->ep.desc = शून्य;
	nuke(ep, -ESHUTDOWN);
	ep->ep.maxpacket = ep->maxpacket;
	ep->has_dma = 0;
	omap_ग_लिखोw(UDC_SET_HALT, UDC_CTRL);
	list_del_init(&ep->iso);
	del_समयr(&ep->समयr);

	spin_unlock_irqrestore(&ep->udc->lock, flags);

	VDBG("%s disabled\n", _ep->name);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_request *
omap_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags)
अणु
	काष्ठा omap_req	*req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम
omap_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *_req)
अणु
	काष्ठा omap_req	*req = container_of(_req, काष्ठा omap_req, req);

	kमुक्त(req);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम
करोne(काष्ठा omap_ep *ep, काष्ठा omap_req *req, पूर्णांक status)
अणु
	काष्ठा omap_udc		*udc = ep->udc;
	अचिन्हित		stopped = ep->stopped;

	list_del_init(&req->queue);

	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	अगर (use_dma && ep->has_dma)
		usb_gadget_unmap_request(&udc->gadget, &req->req,
				(ep->bEndpoपूर्णांकAddress & USB_सूची_IN));

#अगर_अघोषित	USB_TRACE
	अगर (status && status != -ESHUTDOWN)
#पूर्ण_अगर
		VDBG("complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* करोn't modअगरy queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&ep->udc->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&ep->udc->lock);
	ep->stopped = stopped;
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा UDC_FIFO_FULL		(UDC_NON_ISO_FIFO_FULL | UDC_ISO_FIFO_FULL)
#घोषणा UDC_FIFO_UNWRITABLE	(UDC_EP_HALTED | UDC_FIFO_FULL)

#घोषणा FIFO_EMPTY	(UDC_NON_ISO_FIFO_EMPTY | UDC_ISO_FIFO_EMPTY)
#घोषणा FIFO_UNREADABLE (UDC_EP_HALTED | FIFO_EMPTY)

अटल अंतरभूत पूर्णांक
ग_लिखो_packet(u8 *buf, काष्ठा omap_req *req, अचिन्हित max)
अणु
	अचिन्हित	len;
	u16		*wp;

	len = min(req->req.length - req->req.actual, max);
	req->req.actual += len;

	max = len;
	अगर (likely((((पूर्णांक)buf) & 1) == 0)) अणु
		wp = (u16 *)buf;
		जबतक (max >= 2) अणु
			omap_ग_लिखोw(*wp++, UDC_DATA);
			max -= 2;
		पूर्ण
		buf = (u8 *)wp;
	पूर्ण
	जबतक (max--)
		omap_ग_लिखोb(*buf++, UDC_DATA);
	वापस len;
पूर्ण

/* FIXME change r/w fअगरo calling convention */


/* वापस:  0 = still running, 1 = completed, negative = त्रुटि_सं */
अटल पूर्णांक ग_लिखो_fअगरo(काष्ठा omap_ep *ep, काष्ठा omap_req *req)
अणु
	u8		*buf;
	अचिन्हित	count;
	पूर्णांक		is_last;
	u16		ep_stat;

	buf = req->req.buf + req->req.actual;
	prefetch(buf);

	/* PIO-IN isn't द्विगुन buffered except क्रम iso */
	ep_stat = omap_पढ़ोw(UDC_STAT_FLG);
	अगर (ep_stat & UDC_FIFO_UNWRITABLE)
		वापस 0;

	count = ep->ep.maxpacket;
	count = ग_लिखो_packet(buf, req, count);
	omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
	ep->ackरुको = 1;

	/* last packet is often लघु (someबार a zlp) */
	अगर (count != ep->ep.maxpacket)
		is_last = 1;
	अन्यथा अगर (req->req.length == req->req.actual
			&& !req->req.zero)
		is_last = 1;
	अन्यथा
		is_last = 0;

	/* NOTE:  requests complete when all IN data is in a
	 * FIFO (or someबार later, अगर a zlp was needed).
	 * Use usb_ep_fअगरo_status() where needed.
	 */
	अगर (is_last)
		करोne(ep, req, 0);
	वापस is_last;
पूर्ण

अटल अंतरभूत पूर्णांक
पढ़ो_packet(u8 *buf, काष्ठा omap_req *req, अचिन्हित avail)
अणु
	अचिन्हित	len;
	u16		*wp;

	len = min(req->req.length - req->req.actual, avail);
	req->req.actual += len;
	avail = len;

	अगर (likely((((पूर्णांक)buf) & 1) == 0)) अणु
		wp = (u16 *)buf;
		जबतक (avail >= 2) अणु
			*wp++ = omap_पढ़ोw(UDC_DATA);
			avail -= 2;
		पूर्ण
		buf = (u8 *)wp;
	पूर्ण
	जबतक (avail--)
		*buf++ = omap_पढ़ोb(UDC_DATA);
	वापस len;
पूर्ण

/* वापस:  0 = still running, 1 = queue empty, negative = त्रुटि_सं */
अटल पूर्णांक पढ़ो_fअगरo(काष्ठा omap_ep *ep, काष्ठा omap_req *req)
अणु
	u8		*buf;
	अचिन्हित	count, avail;
	पूर्णांक		is_last;

	buf = req->req.buf + req->req.actual;
	prefetchw(buf);

	क्रम (;;) अणु
		u16	ep_stat = omap_पढ़ोw(UDC_STAT_FLG);

		is_last = 0;
		अगर (ep_stat & FIFO_EMPTY) अणु
			अगर (!ep->द्विगुन_buf)
				अवरोध;
			ep->fnf = 1;
		पूर्ण
		अगर (ep_stat & UDC_EP_HALTED)
			अवरोध;

		अगर (ep_stat & UDC_FIFO_FULL)
			avail = ep->ep.maxpacket;
		अन्यथा  अणु
			avail = omap_पढ़ोw(UDC_RXFSTAT);
			ep->fnf = ep->द्विगुन_buf;
		पूर्ण
		count = पढ़ो_packet(buf, req, avail);

		/* partial packet पढ़ोs may not be errors */
		अगर (count < ep->ep.maxpacket) अणु
			is_last = 1;
			/* overflowed this request?  flush extra data */
			अगर (count != avail) अणु
				req->req.status = -EOVERFLOW;
				avail -= count;
				जबतक (avail--)
					omap_पढ़ोw(UDC_DATA);
			पूर्ण
		पूर्ण अन्यथा अगर (req->req.length == req->req.actual)
			is_last = 1;
		अन्यथा
			is_last = 0;

		अगर (!ep->bEndpoपूर्णांकAddress)
			अवरोध;
		अगर (is_last)
			करोne(ep, req, 0);
		अवरोध;
	पूर्ण
	वापस is_last;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल u16 dma_src_len(काष्ठा omap_ep *ep, dma_addr_t start)
अणु
	dma_addr_t	end;

	/* IN-DMA needs this on fault/cancel paths, so 15xx misreports
	 * the last transfer's bytecount by more than a FIFO's worth.
	 */
	अगर (cpu_is_omap15xx())
		वापस 0;

	end = omap_get_dma_src_pos(ep->lch);
	अगर (end == ep->dma_counter)
		वापस 0;

	end |= start & (0xffff << 16);
	अगर (end < start)
		end += 0x10000;
	वापस end - start;
पूर्ण

अटल u16 dma_dest_len(काष्ठा omap_ep *ep, dma_addr_t start)
अणु
	dma_addr_t	end;

	end = omap_get_dma_dst_pos(ep->lch);
	अगर (end == ep->dma_counter)
		वापस 0;

	end |= start & (0xffff << 16);
	अगर (cpu_is_omap15xx())
		end++;
	अगर (end < start)
		end += 0x10000;
	वापस end - start;
पूर्ण


/* Each USB transfer request using DMA maps to one or more DMA transfers.
 * When DMA completion isn't request completion, the UDC जारीs with
 * the next DMA transfer क्रम that USB transfer.
 */

अटल व्योम next_in_dma(काष्ठा omap_ep *ep, काष्ठा omap_req *req)
अणु
	u16		txdma_ctrl, w;
	अचिन्हित	length = req->req.length - req->req.actual;
	स्थिर पूर्णांक	sync_mode = cpu_is_omap15xx()
				? OMAP_DMA_SYNC_FRAME
				: OMAP_DMA_SYNC_ELEMENT;
	पूर्णांक		dma_trigger = 0;

	/* measure length in either bytes or packets */
	अगर ((cpu_is_omap16xx() && length <= UDC_TXN_TSC)
			|| (cpu_is_omap15xx() && length < ep->maxpacket)) अणु
		txdma_ctrl = UDC_TXN_EOT | length;
		omap_set_dma_transfer_params(ep->lch, OMAP_DMA_DATA_TYPE_S8,
				length, 1, sync_mode, dma_trigger, 0);
	पूर्ण अन्यथा अणु
		length = min(length / ep->maxpacket,
				(अचिन्हित) UDC_TXN_TSC + 1);
		txdma_ctrl = length;
		omap_set_dma_transfer_params(ep->lch, OMAP_DMA_DATA_TYPE_S16,
				ep->ep.maxpacket >> 1, length, sync_mode,
				dma_trigger, 0);
		length *= ep->maxpacket;
	पूर्ण
	omap_set_dma_src_params(ep->lch, OMAP_DMA_PORT_EMIFF,
		OMAP_DMA_AMODE_POST_INC, req->req.dma + req->req.actual,
		0, 0);

	omap_start_dma(ep->lch);
	ep->dma_counter = omap_get_dma_src_pos(ep->lch);
	w = omap_पढ़ोw(UDC_DMA_IRQ_EN);
	w |= UDC_TX_DONE_IE(ep->dma_channel);
	omap_ग_लिखोw(w, UDC_DMA_IRQ_EN);
	omap_ग_लिखोw(UDC_TXN_START | txdma_ctrl, UDC_TXDMA(ep->dma_channel));
	req->dma_bytes = length;
पूर्ण

अटल व्योम finish_in_dma(काष्ठा omap_ep *ep, काष्ठा omap_req *req, पूर्णांक status)
अणु
	u16 w;

	अगर (status == 0) अणु
		req->req.actual += req->dma_bytes;

		/* वापस अगर this request needs to send data or zlp */
		अगर (req->req.actual < req->req.length)
			वापस;
		अगर (req->req.zero
				&& req->dma_bytes != 0
				&& (req->req.actual % ep->maxpacket) == 0)
			वापस;
	पूर्ण अन्यथा
		req->req.actual += dma_src_len(ep, req->req.dma
							+ req->req.actual);

	/* tx completion */
	omap_stop_dma(ep->lch);
	w = omap_पढ़ोw(UDC_DMA_IRQ_EN);
	w &= ~UDC_TX_DONE_IE(ep->dma_channel);
	omap_ग_लिखोw(w, UDC_DMA_IRQ_EN);
	करोne(ep, req, status);
पूर्ण

अटल व्योम next_out_dma(काष्ठा omap_ep *ep, काष्ठा omap_req *req)
अणु
	अचिन्हित packets = req->req.length - req->req.actual;
	पूर्णांक dma_trigger = 0;
	u16 w;

	/* set up this DMA transfer, enable the fअगरo, start */
	packets /= ep->ep.maxpacket;
	packets = min(packets, (अचिन्हित)UDC_RXN_TC + 1);
	req->dma_bytes = packets * ep->ep.maxpacket;
	omap_set_dma_transfer_params(ep->lch, OMAP_DMA_DATA_TYPE_S16,
			ep->ep.maxpacket >> 1, packets,
			OMAP_DMA_SYNC_ELEMENT,
			dma_trigger, 0);
	omap_set_dma_dest_params(ep->lch, OMAP_DMA_PORT_EMIFF,
		OMAP_DMA_AMODE_POST_INC, req->req.dma + req->req.actual,
		0, 0);
	ep->dma_counter = omap_get_dma_dst_pos(ep->lch);

	omap_ग_लिखोw(UDC_RXN_STOP | (packets - 1), UDC_RXDMA(ep->dma_channel));
	w = omap_पढ़ोw(UDC_DMA_IRQ_EN);
	w |= UDC_RX_EOT_IE(ep->dma_channel);
	omap_ग_लिखोw(w, UDC_DMA_IRQ_EN);
	omap_ग_लिखोw(ep->bEndpoपूर्णांकAddress & 0xf, UDC_EP_NUM);
	omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);

	omap_start_dma(ep->lch);
पूर्ण

अटल व्योम
finish_out_dma(काष्ठा omap_ep *ep, काष्ठा omap_req *req, पूर्णांक status, पूर्णांक one)
अणु
	u16	count, w;

	अगर (status == 0)
		ep->dma_counter = (u16) (req->req.dma + req->req.actual);
	count = dma_dest_len(ep, req->req.dma + req->req.actual);
	count += req->req.actual;
	अगर (one)
		count--;
	अगर (count <= req->req.length)
		req->req.actual = count;

	अगर (count != req->dma_bytes || status)
		omap_stop_dma(ep->lch);

	/* अगर this wasn't लघु, request may need another transfer */
	अन्यथा अगर (req->req.actual < req->req.length)
		वापस;

	/* rx completion */
	w = omap_पढ़ोw(UDC_DMA_IRQ_EN);
	w &= ~UDC_RX_EOT_IE(ep->dma_channel);
	omap_ग_लिखोw(w, UDC_DMA_IRQ_EN);
	करोne(ep, req, status);
पूर्ण

अटल व्योम dma_irq(काष्ठा omap_udc *udc, u16 irq_src)
अणु
	u16		dman_stat = omap_पढ़ोw(UDC_DMAN_STAT);
	काष्ठा omap_ep	*ep;
	काष्ठा omap_req	*req;

	/* IN dma: tx to host */
	अगर (irq_src & UDC_TXN_DONE) अणु
		ep = &udc->ep[16 + UDC_DMA_TX_SRC(dman_stat)];
		ep->irqs++;
		/* can see TXN_DONE after dma पात */
		अगर (!list_empty(&ep->queue)) अणु
			req = container_of(ep->queue.next,
						काष्ठा omap_req, queue);
			finish_in_dma(ep, req, 0);
		पूर्ण
		omap_ग_लिखोw(UDC_TXN_DONE, UDC_IRQ_SRC);

		अगर (!list_empty(&ep->queue)) अणु
			req = container_of(ep->queue.next,
					काष्ठा omap_req, queue);
			next_in_dma(ep, req);
		पूर्ण
	पूर्ण

	/* OUT dma: rx from host */
	अगर (irq_src & UDC_RXN_EOT) अणु
		ep = &udc->ep[UDC_DMA_RX_SRC(dman_stat)];
		ep->irqs++;
		/* can see RXN_EOT after dma पात */
		अगर (!list_empty(&ep->queue)) अणु
			req = container_of(ep->queue.next,
					काष्ठा omap_req, queue);
			finish_out_dma(ep, req, 0, dman_stat & UDC_DMA_RX_SB);
		पूर्ण
		omap_ग_लिखोw(UDC_RXN_EOT, UDC_IRQ_SRC);

		अगर (!list_empty(&ep->queue)) अणु
			req = container_of(ep->queue.next,
					काष्ठा omap_req, queue);
			next_out_dma(ep, req);
		पूर्ण
	पूर्ण

	अगर (irq_src & UDC_RXN_CNT) अणु
		ep = &udc->ep[UDC_DMA_RX_SRC(dman_stat)];
		ep->irqs++;
		/* omap15xx करोes this unasked... */
		VDBG("%s, RX_CNT irq?\n", ep->ep.name);
		omap_ग_लिखोw(UDC_RXN_CNT, UDC_IRQ_SRC);
	पूर्ण
पूर्ण

अटल व्योम dma_error(पूर्णांक lch, u16 ch_status, व्योम *data)
अणु
	काष्ठा omap_ep	*ep = data;

	/* अगर ch_status & OMAP_DMA_DROP_IRQ ... */
	/* अगर ch_status & OMAP1_DMA_TOUT_IRQ ... */
	ERR("%s dma error, lch %d status %02x\n", ep->ep.name, lch, ch_status);

	/* complete current transfer ... */
पूर्ण

अटल व्योम dma_channel_claim(काष्ठा omap_ep *ep, अचिन्हित channel)
अणु
	u16	reg;
	पूर्णांक	status, restart, is_in;
	पूर्णांक	dma_channel;

	is_in = ep->bEndpoपूर्णांकAddress & USB_सूची_IN;
	अगर (is_in)
		reg = omap_पढ़ोw(UDC_TXDMA_CFG);
	अन्यथा
		reg = omap_पढ़ोw(UDC_RXDMA_CFG);
	reg |= UDC_DMA_REQ;		/* "pulse" activated */

	ep->dma_channel = 0;
	ep->lch = -1;
	अगर (channel == 0 || channel > 3) अणु
		अगर ((reg & 0x0f00) == 0)
			channel = 3;
		अन्यथा अगर ((reg & 0x00f0) == 0)
			channel = 2;
		अन्यथा अगर ((reg & 0x000f) == 0)	/* preferred क्रम ISO */
			channel = 1;
		अन्यथा अणु
			status = -EMLINK;
			जाओ just_restart;
		पूर्ण
	पूर्ण
	reg |= (0x0f & ep->bEndpoपूर्णांकAddress) << (4 * (channel - 1));
	ep->dma_channel = channel;

	अगर (is_in) अणु
		dma_channel = OMAP_DMA_USB_W2FC_TX0 - 1 + channel;
		status = omap_request_dma(dma_channel,
			ep->ep.name, dma_error, ep, &ep->lch);
		अगर (status == 0) अणु
			omap_ग_लिखोw(reg, UDC_TXDMA_CFG);
			/* EMIFF or SDRC */
			omap_set_dma_src_burst_mode(ep->lch,
						OMAP_DMA_DATA_BURST_4);
			omap_set_dma_src_data_pack(ep->lch, 1);
			/* TIPB */
			omap_set_dma_dest_params(ep->lch,
				OMAP_DMA_PORT_TIPB,
				OMAP_DMA_AMODE_CONSTANT,
				UDC_DATA_DMA,
				0, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		dma_channel = OMAP_DMA_USB_W2FC_RX0 - 1 + channel;
		status = omap_request_dma(dma_channel,
			ep->ep.name, dma_error, ep, &ep->lch);
		अगर (status == 0) अणु
			omap_ग_लिखोw(reg, UDC_RXDMA_CFG);
			/* TIPB */
			omap_set_dma_src_params(ep->lch,
				OMAP_DMA_PORT_TIPB,
				OMAP_DMA_AMODE_CONSTANT,
				UDC_DATA_DMA,
				0, 0);
			/* EMIFF or SDRC */
			omap_set_dma_dest_burst_mode(ep->lch,
						OMAP_DMA_DATA_BURST_4);
			omap_set_dma_dest_data_pack(ep->lch, 1);
		पूर्ण
	पूर्ण
	अगर (status)
		ep->dma_channel = 0;
	अन्यथा अणु
		ep->has_dma = 1;
		omap_disable_dma_irq(ep->lch, OMAP_DMA_BLOCK_IRQ);

		/* channel type P: hw synch (fअगरo) */
		अगर (!cpu_is_omap15xx())
			omap_set_dma_channel_mode(ep->lch, OMAP_DMA_LCH_P);
	पूर्ण

just_restart:
	/* restart any queue, even अगर the claim failed  */
	restart = !ep->stopped && !list_empty(&ep->queue);

	अगर (status)
		DBG("%s no dma channel: %d%s\n", ep->ep.name, status,
			restart ? " (restart)" : "");
	अन्यथा
		DBG("%s claimed %cxdma%d lch %d%s\n", ep->ep.name,
			is_in ? 't' : 'r',
			ep->dma_channel - 1, ep->lch,
			restart ? " (restart)" : "");

	अगर (restart) अणु
		काष्ठा omap_req	*req;
		req = container_of(ep->queue.next, काष्ठा omap_req, queue);
		अगर (ep->has_dma)
			(is_in ? next_in_dma : next_out_dma)(ep, req);
		अन्यथा अणु
			use_ep(ep, UDC_EP_SEL);
			(is_in ? ग_लिखो_fअगरo : पढ़ो_fअगरo)(ep, req);
			deselect_ep();
			अगर (!is_in) अणु
				omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
				ep->ackरुको = 1 + ep->द्विगुन_buf;
			पूर्ण
			/* IN: 6 रुको states beक्रमe it'll tx */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dma_channel_release(काष्ठा omap_ep *ep)
अणु
	पूर्णांक		shअगरt = 4 * (ep->dma_channel - 1);
	u16		mask = 0x0f << shअगरt;
	काष्ठा omap_req	*req;
	पूर्णांक		active;

	/* पात any active usb transfer request */
	अगर (!list_empty(&ep->queue))
		req = container_of(ep->queue.next, काष्ठा omap_req, queue);
	अन्यथा
		req = शून्य;

	active = omap_get_dma_active_status(ep->lch);

	DBG("%s release %s %cxdma%d %p\n", ep->ep.name,
			active ? "active" : "idle",
			(ep->bEndpoपूर्णांकAddress & USB_सूची_IN) ? 't' : 'r',
			ep->dma_channel - 1, req);

	/* NOTE: re-setting RX_REQ/TX_REQ because of a chip bug (beक्रमe
	 * OMAP 1710 ES2.0) where पढ़ोing the DMA_CFG can clear them.
	 */

	/* रुको till current packet DMA finishes, and fअगरo empties */
	अगर (ep->bEndpoपूर्णांकAddress & USB_सूची_IN) अणु
		omap_ग_लिखोw((omap_पढ़ोw(UDC_TXDMA_CFG) & ~mask) | UDC_DMA_REQ,
					UDC_TXDMA_CFG);

		अगर (req) अणु
			finish_in_dma(ep, req, -ECONNRESET);

			/* clear FIFO; hosts probably won't empty it */
			use_ep(ep, UDC_EP_SEL);
			omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
			deselect_ep();
		पूर्ण
		जबतक (omap_पढ़ोw(UDC_TXDMA_CFG) & mask)
			udelay(10);
	पूर्ण अन्यथा अणु
		omap_ग_लिखोw((omap_पढ़ोw(UDC_RXDMA_CFG) & ~mask) | UDC_DMA_REQ,
					UDC_RXDMA_CFG);

		/* dma empties the fअगरo */
		जबतक (omap_पढ़ोw(UDC_RXDMA_CFG) & mask)
			udelay(10);
		अगर (req)
			finish_out_dma(ep, req, -ECONNRESET, 0);
	पूर्ण
	omap_मुक्त_dma(ep->lch);
	ep->dma_channel = 0;
	ep->lch = -1;
	/* has_dma still set, till endpoपूर्णांक is fully quiesced */
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक
omap_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा omap_ep	*ep = container_of(_ep, काष्ठा omap_ep, ep);
	काष्ठा omap_req	*req = container_of(_req, काष्ठा omap_req, req);
	काष्ठा omap_udc	*udc;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		is_iso = 0;

	/* catch various bogus parameters */
	अगर (!_req || !req->req.complete || !req->req.buf
			|| !list_empty(&req->queue)) अणु
		DBG("%s, bad params\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (!_ep || (!ep->ep.desc && ep->bEndpoपूर्णांकAddress)) अणु
		DBG("%s, bad ep\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC) अणु
		अगर (req->req.length > ep->ep.maxpacket)
			वापस -EMSGSIZE;
		is_iso = 1;
	पूर्ण

	/* this isn't bogus, but OMAP DMA isn't the only hardware to
	 * have a hard समय with partial packet पढ़ोs...  reject it.
	 */
	अगर (use_dma
			&& ep->has_dma
			&& ep->bEndpoपूर्णांकAddress != 0
			&& (ep->bEndpoपूर्णांकAddress & USB_सूची_IN) == 0
			&& (req->req.length % ep->ep.maxpacket) != 0) अणु
		DBG("%s, no partial packet OUT reads\n", __func__);
		वापस -EMSGSIZE;
	पूर्ण

	udc = ep->udc;
	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	अगर (use_dma && ep->has_dma)
		usb_gadget_map_request(&udc->gadget, &req->req,
				(ep->bEndpoपूर्णांकAddress & USB_सूची_IN));

	VDBG("%s queue req %p, len %d buf %p\n",
		ep->ep.name, _req, _req->length, _req->buf);

	spin_lock_irqsave(&udc->lock, flags);

	req->req.status = -EINPROGRESS;
	req->req.actual = 0;

	/* maybe kickstart non-iso i/o queues */
	अगर (is_iso) अणु
		u16 w;

		w = omap_पढ़ोw(UDC_IRQ_EN);
		w |= UDC_SOF_IE;
		omap_ग_लिखोw(w, UDC_IRQ_EN);
	पूर्ण अन्यथा अगर (list_empty(&ep->queue) && !ep->stopped && !ep->ackरुको) अणु
		पूर्णांक	is_in;

		अगर (ep->bEndpoपूर्णांकAddress == 0) अणु
			अगर (!udc->ep0_pending || !list_empty(&ep->queue)) अणु
				spin_unlock_irqrestore(&udc->lock, flags);
				वापस -EL2HLT;
			पूर्ण

			/* empty DATA stage? */
			is_in = udc->ep0_in;
			अगर (!req->req.length) अणु

				/* chip became CONFIGURED or ADDRESSED
				 * earlier; drivers may alपढ़ोy have queued
				 * requests to non-control endpoपूर्णांकs
				 */
				अगर (udc->ep0_set_config) अणु
					u16	irq_en = omap_पढ़ोw(UDC_IRQ_EN);

					irq_en |= UDC_DS_CHG_IE | UDC_EP0_IE;
					अगर (!udc->ep0_reset_config)
						irq_en |= UDC_EPN_RX_IE
							| UDC_EPN_TX_IE;
					omap_ग_लिखोw(irq_en, UDC_IRQ_EN);
				पूर्ण

				/* STATUS क्रम zero length DATA stages is
				 * always an IN ... even क्रम IN transfers,
				 * a weird हाल which seem to stall OMAP.
				 */
				omap_ग_लिखोw(UDC_EP_SEL | UDC_EP_सूची,
						UDC_EP_NUM);
				omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
				omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
				omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);

				/* cleanup */
				udc->ep0_pending = 0;
				करोne(ep, req, 0);
				req = शून्य;

			/* non-empty DATA stage */
			पूर्ण अन्यथा अगर (is_in) अणु
				omap_ग_लिखोw(UDC_EP_SEL | UDC_EP_सूची,
						UDC_EP_NUM);
			पूर्ण अन्यथा अणु
				अगर (udc->ep0_setup)
					जाओ irq_रुको;
				omap_ग_लिखोw(UDC_EP_SEL, UDC_EP_NUM);
			पूर्ण
		पूर्ण अन्यथा अणु
			is_in = ep->bEndpoपूर्णांकAddress & USB_सूची_IN;
			अगर (!ep->has_dma)
				use_ep(ep, UDC_EP_SEL);
			/* अगर ISO: SOF IRQs must be enabled/disabled! */
		पूर्ण

		अगर (ep->has_dma)
			(is_in ? next_in_dma : next_out_dma)(ep, req);
		अन्यथा अगर (req) अणु
			अगर ((is_in ? ग_लिखो_fअगरo : पढ़ो_fअगरo)(ep, req) == 1)
				req = शून्य;
			deselect_ep();
			अगर (!is_in) अणु
				omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
				ep->ackरुको = 1 + ep->द्विगुन_buf;
			पूर्ण
			/* IN: 6 रुको states beक्रमe it'll tx */
		पूर्ण
	पूर्ण

irq_रुको:
	/* irq handler advances the queue */
	अगर (req != शून्य)
		list_add_tail(&req->queue, &ep->queue);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा omap_ep	*ep = container_of(_ep, काष्ठा omap_ep, ep);
	काष्ठा omap_req	*req;
	अचिन्हित दीर्घ	flags;

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

	अगर (use_dma && ep->dma_channel && ep->queue.next == &req->queue) अणु
		पूर्णांक channel = ep->dma_channel;

		/* releasing the channel cancels the request,
		 * reclaiming the channel restarts the queue
		 */
		dma_channel_release(ep);
		dma_channel_claim(ep, channel);
	पूर्ण अन्यथा
		करोne(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&ep->udc->lock, flags);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक omap_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा omap_ep	*ep = container_of(_ep, काष्ठा omap_ep, ep);
	अचिन्हित दीर्घ	flags;
	पूर्णांक		status = -EOPNOTSUPP;

	spin_lock_irqsave(&ep->udc->lock, flags);

	/* just use protocol stalls क्रम ep0; real halts are annoying */
	अगर (ep->bEndpoपूर्णांकAddress == 0) अणु
		अगर (!ep->udc->ep0_pending)
			status = -EINVAL;
		अन्यथा अगर (value) अणु
			अगर (ep->udc->ep0_set_config) अणु
				WARNING("error changing config?\n");
				omap_ग_लिखोw(UDC_CLR_CFG, UDC_SYSCON2);
			पूर्ण
			omap_ग_लिखोw(UDC_STALL_CMD, UDC_SYSCON2);
			ep->udc->ep0_pending = 0;
			status = 0;
		पूर्ण अन्यथा /* NOP */
			status = 0;

	/* otherwise, all active non-ISO endpoपूर्णांकs can halt */
	पूर्ण अन्यथा अगर (ep->bmAttributes != USB_ENDPOINT_XFER_ISOC && ep->ep.desc) अणु

		/* IN endpoपूर्णांकs must alपढ़ोy be idle */
		अगर ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN)
				&& !list_empty(&ep->queue)) अणु
			status = -EAGAIN;
			जाओ करोne;
		पूर्ण

		अगर (value) अणु
			पूर्णांक	channel;

			अगर (use_dma && ep->dma_channel
					&& !list_empty(&ep->queue)) अणु
				channel = ep->dma_channel;
				dma_channel_release(ep);
			पूर्ण अन्यथा
				channel = 0;

			use_ep(ep, UDC_EP_SEL);
			अगर (omap_पढ़ोw(UDC_STAT_FLG) & UDC_NON_ISO_FIFO_EMPTY) अणु
				omap_ग_लिखोw(UDC_SET_HALT, UDC_CTRL);
				status = 0;
			पूर्ण अन्यथा
				status = -EAGAIN;
			deselect_ep();

			अगर (channel)
				dma_channel_claim(ep, channel);
		पूर्ण अन्यथा अणु
			use_ep(ep, 0);
			omap_ग_लिखोw(ep->udc->clr_halt, UDC_CTRL);
			ep->ackरुको = 0;
			अगर (!(ep->bEndpoपूर्णांकAddress & USB_सूची_IN)) अणु
				omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
				ep->ackरुको = 1 + ep->द्विगुन_buf;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	VDBG("%s %s halt stat %d\n", ep->ep.name,
		value ? "set" : "clear", status);

	spin_unlock_irqrestore(&ep->udc->lock, flags);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops omap_ep_ops = अणु
	.enable		= omap_ep_enable,
	.disable	= omap_ep_disable,

	.alloc_request	= omap_alloc_request,
	.मुक्त_request	= omap_मुक्त_request,

	.queue		= omap_ep_queue,
	.dequeue	= omap_ep_dequeue,

	.set_halt	= omap_ep_set_halt,
	/* fअगरo_status ... report bytes in fअगरo */
	/* fअगरo_flush ... flush fअगरo */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक omap_get_frame(काष्ठा usb_gadget *gadget)
अणु
	u16	sof = omap_पढ़ोw(UDC_SOF);
	वापस (sof & UDC_TS_OK) ? (sof & UDC_TS) : -EL2NSYNC;
पूर्ण

अटल पूर्णांक omap_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा omap_udc	*udc;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		retval = -EHOSTUNREACH;

	udc = container_of(gadget, काष्ठा omap_udc, gadget);

	spin_lock_irqsave(&udc->lock, flags);
	अगर (udc->devstat & UDC_SUS) अणु
		/* NOTE:  OTG spec erratum says that OTG devices may
		 * issue wakeups without host enable.
		 */
		अगर (udc->devstat & (UDC_B_HNP_ENABLE|UDC_R_WK_OK)) अणु
			DBG("remote wakeup...\n");
			omap_ग_लिखोw(UDC_RMT_WKP, UDC_SYSCON2);
			retval = 0;
		पूर्ण

	/* NOTE:  non-OTG प्रणालीs may use SRP TOO... */
	पूर्ण अन्यथा अगर (!(udc->devstat & UDC_ATT)) अणु
		अगर (!IS_ERR_OR_शून्य(udc->transceiver))
			retval = otg_start_srp(udc->transceiver->otg);
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक
omap_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_selfघातered)
अणु
	काष्ठा omap_udc	*udc;
	अचिन्हित दीर्घ	flags;
	u16		syscon1;

	gadget->is_selfघातered = (is_selfघातered != 0);
	udc = container_of(gadget, काष्ठा omap_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);
	syscon1 = omap_पढ़ोw(UDC_SYSCON1);
	अगर (is_selfघातered)
		syscon1 |= UDC_SELF_PWR;
	अन्यथा
		syscon1 &= ~UDC_SELF_PWR;
	omap_ग_लिखोw(syscon1, UDC_SYSCON1);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक can_pullup(काष्ठा omap_udc *udc)
अणु
	वापस udc->driver && udc->softconnect && udc->vbus_active;
पूर्ण

अटल व्योम pullup_enable(काष्ठा omap_udc *udc)
अणु
	u16 w;

	w = omap_पढ़ोw(UDC_SYSCON1);
	w |= UDC_PULLUP_EN;
	omap_ग_लिखोw(w, UDC_SYSCON1);
	अगर (!gadget_is_otg(&udc->gadget) && !cpu_is_omap15xx()) अणु
		u32 l;

		l = omap_पढ़ोl(OTG_CTRL);
		l |= OTG_BSESSVLD;
		omap_ग_लिखोl(l, OTG_CTRL);
	पूर्ण
	omap_ग_लिखोw(UDC_DS_CHG_IE, UDC_IRQ_EN);
पूर्ण

अटल व्योम pullup_disable(काष्ठा omap_udc *udc)
अणु
	u16 w;

	अगर (!gadget_is_otg(&udc->gadget) && !cpu_is_omap15xx()) अणु
		u32 l;

		l = omap_पढ़ोl(OTG_CTRL);
		l &= ~OTG_BSESSVLD;
		omap_ग_लिखोl(l, OTG_CTRL);
	पूर्ण
	omap_ग_लिखोw(UDC_DS_CHG_IE, UDC_IRQ_EN);
	w = omap_पढ़ोw(UDC_SYSCON1);
	w &= ~UDC_PULLUP_EN;
	omap_ग_लिखोw(w, UDC_SYSCON1);
पूर्ण

अटल काष्ठा omap_udc *udc;

अटल व्योम omap_udc_enable_घड़ी(पूर्णांक enable)
अणु
	अगर (udc == शून्य || udc->dc_clk == शून्य || udc->hhc_clk == शून्य)
		वापस;

	अगर (enable) अणु
		clk_enable(udc->dc_clk);
		clk_enable(udc->hhc_clk);
		udelay(100);
	पूर्ण अन्यथा अणु
		clk_disable(udc->hhc_clk);
		clk_disable(udc->dc_clk);
	पूर्ण
पूर्ण

/*
 * Called by whatever detects VBUS sessions:  बाह्यal transceiver
 * driver, or maybe GPIO0 VBUS IRQ.  May request 48 MHz घड़ी.
 */
अटल पूर्णांक omap_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा omap_udc	*udc;
	अचिन्हित दीर्घ	flags;
	u32 l;

	udc = container_of(gadget, काष्ठा omap_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);
	VDBG("VBUS %s\n", is_active ? "on" : "off");
	udc->vbus_active = (is_active != 0);
	अगर (cpu_is_omap15xx()) अणु
		/* "software" detect, ignored अगर !VBUS_MODE_1510 */
		l = omap_पढ़ोl(FUNC_MUX_CTRL_0);
		अगर (is_active)
			l |= VBUS_CTRL_1510;
		अन्यथा
			l &= ~VBUS_CTRL_1510;
		omap_ग_लिखोl(l, FUNC_MUX_CTRL_0);
	पूर्ण
	अगर (udc->dc_clk != शून्य && is_active) अणु
		अगर (!udc->clk_requested) अणु
			omap_udc_enable_घड़ी(1);
			udc->clk_requested = 1;
		पूर्ण
	पूर्ण
	अगर (can_pullup(udc))
		pullup_enable(udc);
	अन्यथा
		pullup_disable(udc);
	अगर (udc->dc_clk != शून्य && !is_active) अणु
		अगर (udc->clk_requested) अणु
			omap_udc_enable_घड़ी(0);
			udc->clk_requested = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु
	काष्ठा omap_udc	*udc;

	udc = container_of(gadget, काष्ठा omap_udc, gadget);
	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		वापस usb_phy_set_घातer(udc->transceiver, mA);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक omap_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा omap_udc	*udc;
	अचिन्हित दीर्घ	flags;

	udc = container_of(gadget, काष्ठा omap_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);
	udc->softconnect = (is_on != 0);
	अगर (can_pullup(udc))
		pullup_enable(udc);
	अन्यथा
		pullup_disable(udc);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक omap_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops omap_gadget_ops = अणु
	.get_frame		= omap_get_frame,
	.wakeup			= omap_wakeup,
	.set_selfघातered	= omap_set_selfघातered,
	.vbus_session		= omap_vbus_session,
	.vbus_draw		= omap_vbus_draw,
	.pullup			= omap_pullup,
	.udc_start		= omap_udc_start,
	.udc_stop		= omap_udc_stop,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* dequeue ALL requests; caller holds udc->lock */
अटल व्योम nuke(काष्ठा omap_ep *ep, पूर्णांक status)
अणु
	काष्ठा omap_req	*req;

	ep->stopped = 1;

	अगर (use_dma && ep->dma_channel)
		dma_channel_release(ep);

	use_ep(ep, 0);
	omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
	अगर (ep->bEndpoपूर्णांकAddress && ep->bmAttributes != USB_ENDPOINT_XFER_ISOC)
		omap_ग_लिखोw(UDC_SET_HALT, UDC_CTRL);

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा omap_req, queue);
		करोne(ep, req, status);
	पूर्ण
पूर्ण

/* caller holds udc->lock */
अटल व्योम udc_quiesce(काष्ठा omap_udc *udc)
अणु
	काष्ठा omap_ep	*ep;

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	nuke(&udc->ep[0], -ESHUTDOWN);
	list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list)
		nuke(ep, -ESHUTDOWN);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम update_otg(काष्ठा omap_udc *udc)
अणु
	u16	devstat;

	अगर (!gadget_is_otg(&udc->gadget))
		वापस;

	अगर (omap_पढ़ोl(OTG_CTRL) & OTG_ID)
		devstat = omap_पढ़ोw(UDC_DEVSTAT);
	अन्यथा
		devstat = 0;

	udc->gadget.b_hnp_enable = !!(devstat & UDC_B_HNP_ENABLE);
	udc->gadget.a_hnp_support = !!(devstat & UDC_A_HNP_SUPPORT);
	udc->gadget.a_alt_hnp_support = !!(devstat & UDC_A_ALT_HNP_SUPPORT);

	/* Enable HNP early, aव्योमing races on suspend irq path.
	 * ASSUMES OTG state machine B_BUS_REQ input is true.
	 */
	अगर (udc->gadget.b_hnp_enable) अणु
		u32 l;

		l = omap_पढ़ोl(OTG_CTRL);
		l |= OTG_B_HNPEN | OTG_B_BUSREQ;
		l &= ~OTG_PULLUP;
		omap_ग_लिखोl(l, OTG_CTRL);
	पूर्ण
पूर्ण

अटल व्योम ep0_irq(काष्ठा omap_udc *udc, u16 irq_src)
अणु
	काष्ठा omap_ep	*ep0 = &udc->ep[0];
	काष्ठा omap_req	*req = शून्य;

	ep0->irqs++;

	/* Clear any pending requests and then scrub any rx/tx state
	 * beक्रमe starting to handle the SETUP request.
	 */
	अगर (irq_src & UDC_SETUP) अणु
		u16	ack = irq_src & (UDC_EP0_TX|UDC_EP0_RX);

		nuke(ep0, 0);
		अगर (ack) अणु
			omap_ग_लिखोw(ack, UDC_IRQ_SRC);
			irq_src = UDC_SETUP;
		पूर्ण
	पूर्ण

	/* IN/OUT packets mean we're in the DATA or STATUS stage.
	 * This driver uses only uses protocol stalls (ep0 never halts),
	 * and अगर we got this far the gadget driver alपढ़ोy had a
	 * chance to stall.  Tries to be क्रमgiving of host oddities.
	 *
	 * NOTE:  the last chance gadget drivers have to stall control
	 * requests is during their request completion callback.
	 */
	अगर (!list_empty(&ep0->queue))
		req = container_of(ep0->queue.next, काष्ठा omap_req, queue);

	/* IN == TX to host */
	अगर (irq_src & UDC_EP0_TX) अणु
		पूर्णांक	stat;

		omap_ग_लिखोw(UDC_EP0_TX, UDC_IRQ_SRC);
		omap_ग_लिखोw(UDC_EP_SEL|UDC_EP_सूची, UDC_EP_NUM);
		stat = omap_पढ़ोw(UDC_STAT_FLG);
		अगर (stat & UDC_ACK) अणु
			अगर (udc->ep0_in) अणु
				/* ग_लिखो next IN packet from response,
				 * or set up the status stage.
				 */
				अगर (req)
					stat = ग_लिखो_fअगरo(ep0, req);
				omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
				अगर (!req && udc->ep0_pending) अणु
					omap_ग_लिखोw(UDC_EP_SEL, UDC_EP_NUM);
					omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
					omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
					omap_ग_लिखोw(0, UDC_EP_NUM);
					udc->ep0_pending = 0;
				पूर्ण /* अन्यथा:  6 रुको states beक्रमe it'll tx */
			पूर्ण अन्यथा अणु
				/* ack status stage of OUT transfer */
				omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
				अगर (req)
					करोne(ep0, req, 0);
			पूर्ण
			req = शून्य;
		पूर्ण अन्यथा अगर (stat & UDC_STALL) अणु
			omap_ग_लिखोw(UDC_CLR_HALT, UDC_CTRL);
			omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
		पूर्ण अन्यथा अणु
			omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
		पूर्ण
	पूर्ण

	/* OUT == RX from host */
	अगर (irq_src & UDC_EP0_RX) अणु
		पूर्णांक	stat;

		omap_ग_लिखोw(UDC_EP0_RX, UDC_IRQ_SRC);
		omap_ग_लिखोw(UDC_EP_SEL, UDC_EP_NUM);
		stat = omap_पढ़ोw(UDC_STAT_FLG);
		अगर (stat & UDC_ACK) अणु
			अगर (!udc->ep0_in) अणु
				stat = 0;
				/* पढ़ो next OUT packet of request, maybe
				 * reactiviting the fअगरo; stall on errors.
				 */
				stat = पढ़ो_fअगरo(ep0, req);
				अगर (!req || stat < 0) अणु
					omap_ग_लिखोw(UDC_STALL_CMD, UDC_SYSCON2);
					udc->ep0_pending = 0;
					stat = 0;
				पूर्ण अन्यथा अगर (stat == 0)
					omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
				omap_ग_लिखोw(0, UDC_EP_NUM);

				/* activate status stage */
				अगर (stat == 1) अणु
					करोne(ep0, req, 0);
					/* that may have STALLed ep0... */
					omap_ग_लिखोw(UDC_EP_SEL | UDC_EP_सूची,
							UDC_EP_NUM);
					omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
					omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
					omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
					udc->ep0_pending = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* ack status stage of IN transfer */
				omap_ग_लिखोw(0, UDC_EP_NUM);
				अगर (req)
					करोne(ep0, req, 0);
			पूर्ण
		पूर्ण अन्यथा अगर (stat & UDC_STALL) अणु
			omap_ग_लिखोw(UDC_CLR_HALT, UDC_CTRL);
			omap_ग_लिखोw(0, UDC_EP_NUM);
		पूर्ण अन्यथा अणु
			omap_ग_लिखोw(0, UDC_EP_NUM);
		पूर्ण
	पूर्ण

	/* SETUP starts all control transfers */
	अगर (irq_src & UDC_SETUP) अणु
		जोड़ u अणु
			u16			word[4];
			काष्ठा usb_ctrlrequest	r;
		पूर्ण u;
		पूर्णांक			status = -EINVAL;
		काष्ठा omap_ep		*ep;

		/* पढ़ो the (latest) SETUP message */
		करो अणु
			omap_ग_लिखोw(UDC_SETUP_SEL, UDC_EP_NUM);
			/* two bytes at a समय */
			u.word[0] = omap_पढ़ोw(UDC_DATA);
			u.word[1] = omap_पढ़ोw(UDC_DATA);
			u.word[2] = omap_पढ़ोw(UDC_DATA);
			u.word[3] = omap_पढ़ोw(UDC_DATA);
			omap_ग_लिखोw(0, UDC_EP_NUM);
		पूर्ण जबतक (omap_पढ़ोw(UDC_IRQ_SRC) & UDC_SETUP);

#घोषणा	w_value		le16_to_cpu(u.r.wValue)
#घोषणा	w_index		le16_to_cpu(u.r.wIndex)
#घोषणा	w_length	le16_to_cpu(u.r.wLength)

		/* Delegate almost all control requests to the gadget driver,
		 * except क्रम a handful of ch9 status/feature requests that
		 * hardware करोesn't स्वतःdecode _and_ the gadget API hides.
		 */
		udc->ep0_in = (u.r.bRequestType & USB_सूची_IN) != 0;
		udc->ep0_set_config = 0;
		udc->ep0_pending = 1;
		ep0->stopped = 0;
		ep0->ackरुको = 0;
		चयन (u.r.bRequest) अणु
		हाल USB_REQ_SET_CONFIGURATION:
			/* udc needs to know when ep != 0 is valid */
			अगर (u.r.bRequestType != USB_RECIP_DEVICE)
				जाओ delegate;
			अगर (w_length != 0)
				जाओ करो_stall;
			udc->ep0_set_config = 1;
			udc->ep0_reset_config = (w_value == 0);
			VDBG("set config %d\n", w_value);

			/* update udc NOW since gadget driver may start
			 * queueing requests immediately; clear config
			 * later अगर it fails the request.
			 */
			अगर (udc->ep0_reset_config)
				omap_ग_लिखोw(UDC_CLR_CFG, UDC_SYSCON2);
			अन्यथा
				omap_ग_लिखोw(UDC_DEV_CFG, UDC_SYSCON2);
			update_otg(udc);
			जाओ delegate;
		हाल USB_REQ_CLEAR_FEATURE:
			/* clear endpoपूर्णांक halt */
			अगर (u.r.bRequestType != USB_RECIP_ENDPOINT)
				जाओ delegate;
			अगर (w_value != USB_ENDPOINT_HALT
					|| w_length != 0)
				जाओ करो_stall;
			ep = &udc->ep[w_index & 0xf];
			अगर (ep != ep0) अणु
				अगर (w_index & USB_सूची_IN)
					ep += 16;
				अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC
						|| !ep->ep.desc)
					जाओ करो_stall;
				use_ep(ep, 0);
				omap_ग_लिखोw(udc->clr_halt, UDC_CTRL);
				ep->ackरुको = 0;
				अगर (!(ep->bEndpoपूर्णांकAddress & USB_सूची_IN)) अणु
					omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
					ep->ackरुको = 1 + ep->द्विगुन_buf;
				पूर्ण
				/* NOTE:  assumes the host behaves sanely,
				 * only clearing real halts.  Else we may
				 * need to समाप्त pending transfers and then
				 * restart the queue... very messy क्रम DMA!
				 */
			पूर्ण
			VDBG("%s halt cleared by host\n", ep->name);
			जाओ ep0out_status_stage;
		हाल USB_REQ_SET_FEATURE:
			/* set endpoपूर्णांक halt */
			अगर (u.r.bRequestType != USB_RECIP_ENDPOINT)
				जाओ delegate;
			अगर (w_value != USB_ENDPOINT_HALT
					|| w_length != 0)
				जाओ करो_stall;
			ep = &udc->ep[w_index & 0xf];
			अगर (w_index & USB_सूची_IN)
				ep += 16;
			अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC
					|| ep == ep0 || !ep->ep.desc)
				जाओ करो_stall;
			अगर (use_dma && ep->has_dma) अणु
				/* this has rude side-effects (पातs) and
				 * can't really work अगर DMA-IN is active
				 */
				DBG("%s host set_halt, NYET\n", ep->name);
				जाओ करो_stall;
			पूर्ण
			use_ep(ep, 0);
			/* can't halt if fifo isn't empty... */
			omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
			omap_ग_लिखोw(UDC_SET_HALT, UDC_CTRL);
			VDBG("%s halted by host\n", ep->name);
ep0out_status_stage:
			status = 0;
			omap_ग_लिखोw(UDC_EP_SEL|UDC_EP_सूची, UDC_EP_NUM);
			omap_ग_लिखोw(UDC_CLR_EP, UDC_CTRL);
			omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
			omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
			udc->ep0_pending = 0;
			अवरोध;
		हाल USB_REQ_GET_STATUS:
			/* USB_ENDPOINT_HALT status? */
			अगर (u.r.bRequestType != (USB_सूची_IN|USB_RECIP_ENDPOINT))
				जाओ पूर्णांकf_status;

			/* ep0 never stalls */
			अगर (!(w_index & 0xf))
				जाओ zero_status;

			/* only active endpoपूर्णांकs count */
			ep = &udc->ep[w_index & 0xf];
			अगर (w_index & USB_सूची_IN)
				ep += 16;
			अगर (!ep->ep.desc)
				जाओ करो_stall;

			/* iso never stalls */
			अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC)
				जाओ zero_status;

			/* FIXME करोn't assume non-halted endpoपूर्णांकs!! */
			ERR("%s status, can't report\n", ep->ep.name);
			जाओ करो_stall;

पूर्णांकf_status:
			/* वापस पूर्णांकerface status.  अगर we were pedantic,
			 * we'd detect non-existent पूर्णांकerfaces, and stall.
			 */
			अगर (u.r.bRequestType
					!= (USB_सूची_IN|USB_RECIP_INTERFACE))
				जाओ delegate;

zero_status:
			/* वापस two zero bytes */
			omap_ग_लिखोw(UDC_EP_SEL|UDC_EP_सूची, UDC_EP_NUM);
			omap_ग_लिखोw(0, UDC_DATA);
			omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
			omap_ग_लिखोw(UDC_EP_सूची, UDC_EP_NUM);
			status = 0;
			VDBG("GET_STATUS, interface %d\n", w_index);
			/* next, status stage */
			अवरोध;
		शेष:
delegate:
			/* activate the ep0out fअगरo right away */
			अगर (!udc->ep0_in && w_length) अणु
				omap_ग_लिखोw(0, UDC_EP_NUM);
				omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
			पूर्ण

			/* gadget drivers see class/venकरोr specअगरic requests,
			 * अणुSET,GETपूर्ण_अणुINTERFACE,DESCRIPTOR,CONFIGURATIONपूर्ण,
			 * and more
			 */
			VDBG("SETUP %02x.%02x v%04x i%04x l%04x\n",
				u.r.bRequestType, u.r.bRequest,
				w_value, w_index, w_length);

#अघोषित	w_value
#अघोषित	w_index
#अघोषित	w_length

			/* The gadget driver may वापस an error here,
			 * causing an immediate protocol stall.
			 *
			 * Else it must issue a response, either queueing a
			 * response buffer क्रम the DATA stage, or halting ep0
			 * (causing a protocol stall, not a real halt).  A
			 * zero length buffer means no DATA stage.
			 *
			 * It's fine to issue that response after the setup()
			 * call वापसs, and this IRQ was handled.
			 */
			udc->ep0_setup = 1;
			spin_unlock(&udc->lock);
			status = udc->driver->setup(&udc->gadget, &u.r);
			spin_lock(&udc->lock);
			udc->ep0_setup = 0;
		पूर्ण

		अगर (status < 0) अणु
करो_stall:
			VDBG("req %02x.%02x protocol STALL; stat %d\n",
					u.r.bRequestType, u.r.bRequest, status);
			अगर (udc->ep0_set_config) अणु
				अगर (udc->ep0_reset_config)
					WARNING("error resetting config?\n");
				अन्यथा
					omap_ग_लिखोw(UDC_CLR_CFG, UDC_SYSCON2);
			पूर्ण
			omap_ग_लिखोw(UDC_STALL_CMD, UDC_SYSCON2);
			udc->ep0_pending = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

#घोषणा OTG_FLAGS (UDC_B_HNP_ENABLE|UDC_A_HNP_SUPPORT|UDC_A_ALT_HNP_SUPPORT)

अटल व्योम devstate_irq(काष्ठा omap_udc *udc, u16 irq_src)
अणु
	u16	devstat, change;

	devstat = omap_पढ़ोw(UDC_DEVSTAT);
	change = devstat ^ udc->devstat;
	udc->devstat = devstat;

	अगर (change & (UDC_USB_RESET|UDC_ATT)) अणु
		udc_quiesce(udc);

		अगर (change & UDC_ATT) अणु
			/* driver क्रम any बाह्यal transceiver will
			 * have called omap_vbus_session() alपढ़ोy
			 */
			अगर (devstat & UDC_ATT) अणु
				udc->gadget.speed = USB_SPEED_FULL;
				VDBG("connect\n");
				अगर (IS_ERR_OR_शून्य(udc->transceiver))
					pullup_enable(udc);
				/* अगर (driver->connect) call it */
			पूर्ण अन्यथा अगर (udc->gadget.speed != USB_SPEED_UNKNOWN) अणु
				udc->gadget.speed = USB_SPEED_UNKNOWN;
				अगर (IS_ERR_OR_शून्य(udc->transceiver))
					pullup_disable(udc);
				DBG("disconnect, gadget %s\n",
					udc->driver->driver.name);
				अगर (udc->driver->disconnect) अणु
					spin_unlock(&udc->lock);
					udc->driver->disconnect(&udc->gadget);
					spin_lock(&udc->lock);
				पूर्ण
			पूर्ण
			change &= ~UDC_ATT;
		पूर्ण

		अगर (change & UDC_USB_RESET) अणु
			अगर (devstat & UDC_USB_RESET) अणु
				VDBG("RESET=1\n");
			पूर्ण अन्यथा अणु
				udc->gadget.speed = USB_SPEED_FULL;
				INFO("USB reset done, gadget %s\n",
					udc->driver->driver.name);
				/* ep0 traffic is legal from now on */
				omap_ग_लिखोw(UDC_DS_CHG_IE | UDC_EP0_IE,
						UDC_IRQ_EN);
			पूर्ण
			change &= ~UDC_USB_RESET;
		पूर्ण
	पूर्ण
	अगर (change & UDC_SUS) अणु
		अगर (udc->gadget.speed != USB_SPEED_UNKNOWN) अणु
			/* FIXME tell isp1301 to suspend/resume (?) */
			अगर (devstat & UDC_SUS) अणु
				VDBG("suspend\n");
				update_otg(udc);
				/* HNP could be under way alपढ़ोy */
				अगर (udc->gadget.speed == USB_SPEED_FULL
						&& udc->driver->suspend) अणु
					spin_unlock(&udc->lock);
					udc->driver->suspend(&udc->gadget);
					spin_lock(&udc->lock);
				पूर्ण
				अगर (!IS_ERR_OR_शून्य(udc->transceiver))
					usb_phy_set_suspend(
							udc->transceiver, 1);
			पूर्ण अन्यथा अणु
				VDBG("resume\n");
				अगर (!IS_ERR_OR_शून्य(udc->transceiver))
					usb_phy_set_suspend(
							udc->transceiver, 0);
				अगर (udc->gadget.speed == USB_SPEED_FULL
						&& udc->driver->resume) अणु
					spin_unlock(&udc->lock);
					udc->driver->resume(&udc->gadget);
					spin_lock(&udc->lock);
				पूर्ण
			पूर्ण
		पूर्ण
		change &= ~UDC_SUS;
	पूर्ण
	अगर (!cpu_is_omap15xx() && (change & OTG_FLAGS)) अणु
		update_otg(udc);
		change &= ~OTG_FLAGS;
	पूर्ण

	change &= ~(UDC_CFG|UDC_DEF|UDC_ADD);
	अगर (change)
		VDBG("devstat %03x, ignore change %03x\n",
			devstat,  change);

	omap_ग_लिखोw(UDC_DS_CHG, UDC_IRQ_SRC);
पूर्ण

अटल irqवापस_t omap_udc_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा omap_udc	*udc = _udc;
	u16		irq_src;
	irqवापस_t	status = IRQ_NONE;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&udc->lock, flags);
	irq_src = omap_पढ़ोw(UDC_IRQ_SRC);

	/* Device state change (usb ch9 stuff) */
	अगर (irq_src & UDC_DS_CHG) अणु
		devstate_irq(_udc, irq_src);
		status = IRQ_HANDLED;
		irq_src &= ~UDC_DS_CHG;
	पूर्ण

	/* EP0 control transfers */
	अगर (irq_src & (UDC_EP0_RX|UDC_SETUP|UDC_EP0_TX)) अणु
		ep0_irq(_udc, irq_src);
		status = IRQ_HANDLED;
		irq_src &= ~(UDC_EP0_RX|UDC_SETUP|UDC_EP0_TX);
	पूर्ण

	/* DMA transfer completion */
	अगर (use_dma && (irq_src & (UDC_TXN_DONE|UDC_RXN_CNT|UDC_RXN_EOT))) अणु
		dma_irq(_udc, irq_src);
		status = IRQ_HANDLED;
		irq_src &= ~(UDC_TXN_DONE|UDC_RXN_CNT|UDC_RXN_EOT);
	पूर्ण

	irq_src &= ~(UDC_IRQ_SOF | UDC_EPN_TX|UDC_EPN_RX);
	अगर (irq_src)
		DBG("udc_irq, unhandled %03x\n", irq_src);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस status;
पूर्ण

/* workaround क्रम seemingly-lost IRQs क्रम RX ACKs... */
#घोषणा PIO_OUT_TIMEOUT	(jअगरfies + HZ/3)
#घोषणा HALF_FULL(f)	(!((f)&(UDC_NON_ISO_FIFO_FULL|UDC_NON_ISO_FIFO_EMPTY)))

अटल व्योम pio_out_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा omap_ep	*ep = from_समयr(ep, t, समयr);
	अचिन्हित दीर्घ	flags;
	u16		stat_flg;

	spin_lock_irqsave(&ep->udc->lock, flags);
	अगर (!list_empty(&ep->queue) && ep->ackरुको) अणु
		use_ep(ep, UDC_EP_SEL);
		stat_flg = omap_पढ़ोw(UDC_STAT_FLG);

		अगर ((stat_flg & UDC_ACK) && (!(stat_flg & UDC_FIFO_EN)
				|| (ep->द्विगुन_buf && HALF_FULL(stat_flg)))) अणु
			काष्ठा omap_req	*req;

			VDBG("%s: lose, %04x\n", ep->ep.name, stat_flg);
			req = container_of(ep->queue.next,
					काष्ठा omap_req, queue);
			(व्योम) पढ़ो_fअगरo(ep, req);
			omap_ग_लिखोw(ep->bEndpoपूर्णांकAddress, UDC_EP_NUM);
			omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
			ep->ackरुको = 1 + ep->द्विगुन_buf;
		पूर्ण अन्यथा
			deselect_ep();
	पूर्ण
	mod_समयr(&ep->समयr, PIO_OUT_TIMEOUT);
	spin_unlock_irqrestore(&ep->udc->lock, flags);
पूर्ण

अटल irqवापस_t omap_udc_pio_irq(पूर्णांक irq, व्योम *_dev)
अणु
	u16		epn_stat, irq_src;
	irqवापस_t	status = IRQ_NONE;
	काष्ठा omap_ep	*ep;
	पूर्णांक		epnum;
	काष्ठा omap_udc	*udc = _dev;
	काष्ठा omap_req	*req;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&udc->lock, flags);
	epn_stat = omap_पढ़ोw(UDC_EPN_STAT);
	irq_src = omap_पढ़ोw(UDC_IRQ_SRC);

	/* handle OUT first, to aव्योम some wasteful NAKs */
	अगर (irq_src & UDC_EPN_RX) अणु
		epnum = (epn_stat >> 8) & 0x0f;
		omap_ग_लिखोw(UDC_EPN_RX, UDC_IRQ_SRC);
		status = IRQ_HANDLED;
		ep = &udc->ep[epnum];
		ep->irqs++;

		omap_ग_लिखोw(epnum | UDC_EP_SEL, UDC_EP_NUM);
		ep->fnf = 0;
		अगर (omap_पढ़ोw(UDC_STAT_FLG) & UDC_ACK) अणु
			ep->ackरुको--;
			अगर (!list_empty(&ep->queue)) अणु
				पूर्णांक stat;
				req = container_of(ep->queue.next,
						काष्ठा omap_req, queue);
				stat = पढ़ो_fअगरo(ep, req);
				अगर (!ep->द्विगुन_buf)
					ep->fnf = 1;
			पूर्ण
		पूर्ण
		/* min 6 घड़ी delay beक्रमe clearing EP_SEL ... */
		epn_stat = omap_पढ़ोw(UDC_EPN_STAT);
		epn_stat = omap_पढ़ोw(UDC_EPN_STAT);
		omap_ग_लिखोw(epnum, UDC_EP_NUM);

		/* enabling fअगरo _after_ clearing ACK, contrary to करोcs,
		 * reduces lossage; समयr still needed though (sigh).
		 */
		अगर (ep->fnf) अणु
			omap_ग_लिखोw(UDC_SET_FIFO_EN, UDC_CTRL);
			ep->ackरुको = 1 + ep->द्विगुन_buf;
		पूर्ण
		mod_समयr(&ep->समयr, PIO_OUT_TIMEOUT);
	पूर्ण

	/* then IN transfers */
	अन्यथा अगर (irq_src & UDC_EPN_TX) अणु
		epnum = epn_stat & 0x0f;
		omap_ग_लिखोw(UDC_EPN_TX, UDC_IRQ_SRC);
		status = IRQ_HANDLED;
		ep = &udc->ep[16 + epnum];
		ep->irqs++;

		omap_ग_लिखोw(epnum | UDC_EP_सूची | UDC_EP_SEL, UDC_EP_NUM);
		अगर (omap_पढ़ोw(UDC_STAT_FLG) & UDC_ACK) अणु
			ep->ackरुको = 0;
			अगर (!list_empty(&ep->queue)) अणु
				req = container_of(ep->queue.next,
						काष्ठा omap_req, queue);
				(व्योम) ग_लिखो_fअगरo(ep, req);
			पूर्ण
		पूर्ण
		/* min 6 घड़ी delay beक्रमe clearing EP_SEL ... */
		epn_stat = omap_पढ़ोw(UDC_EPN_STAT);
		epn_stat = omap_पढ़ोw(UDC_EPN_STAT);
		omap_ग_लिखोw(epnum | UDC_EP_सूची, UDC_EP_NUM);
		/* then 6 घड़ीs beक्रमe it'd tx */
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस status;
पूर्ण

#अगर_घोषित	USE_ISO
अटल irqवापस_t omap_udc_iso_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा omap_udc	*udc = _dev;
	काष्ठा omap_ep	*ep;
	पूर्णांक		pending = 0;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&udc->lock, flags);

	/* handle all non-DMA ISO transfers */
	list_क्रम_each_entry(ep, &udc->iso, iso) अणु
		u16		stat;
		काष्ठा omap_req	*req;

		अगर (ep->has_dma || list_empty(&ep->queue))
			जारी;
		req = list_entry(ep->queue.next, काष्ठा omap_req, queue);

		use_ep(ep, UDC_EP_SEL);
		stat = omap_पढ़ोw(UDC_STAT_FLG);

		/* NOTE: like the other controller drivers, this isn't
		 * currently reporting lost or damaged frames.
		 */
		अगर (ep->bEndpoपूर्णांकAddress & USB_सूची_IN) अणु
			अगर (stat & UDC_MISS_IN)
				/* करोne(ep, req, -EPROTO) */;
			अन्यथा
				ग_लिखो_fअगरo(ep, req);
		पूर्ण अन्यथा अणु
			पूर्णांक	status = 0;

			अगर (stat & UDC_NO_RXPACKET)
				status = -EREMOTEIO;
			अन्यथा अगर (stat & UDC_ISO_ERR)
				status = -EILSEQ;
			अन्यथा अगर (stat & UDC_DATA_FLUSH)
				status = -ENOSR;

			अगर (status)
				/* करोne(ep, req, status) */;
			अन्यथा
				पढ़ो_fअगरo(ep, req);
		पूर्ण
		deselect_ep();
		/* 6 रुको states beक्रमe next EP */

		ep->irqs++;
		अगर (!list_empty(&ep->queue))
			pending = 1;
	पूर्ण
	अगर (!pending) अणु
		u16 w;

		w = omap_पढ़ोw(UDC_IRQ_EN);
		w &= ~UDC_SOF_IE;
		omap_ग_लिखोw(w, UDC_IRQ_EN);
	पूर्ण
	omap_ग_लिखोw(UDC_IRQ_SOF, UDC_IRQ_SRC);

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक machine_without_vbus_sense(व्योम)
अणु
	वापस machine_is_omap_innovator()
		|| machine_is_omap_osk()
		|| machine_is_omap_palmte()
		|| machine_is_sx1()
		/* No known omap7xx boards with vbus sense */
		|| cpu_is_omap7xx();
पूर्ण

अटल पूर्णांक omap_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक		status;
	काष्ठा omap_ep	*ep;
	अचिन्हित दीर्घ	flags;


	spin_lock_irqsave(&udc->lock, flags);
	/* reset state */
	list_क्रम_each_entry(ep, &udc->gadget.ep_list, ep.ep_list) अणु
		ep->irqs = 0;
		अगर (ep->bmAttributes == USB_ENDPOINT_XFER_ISOC)
			जारी;
		use_ep(ep, 0);
		omap_ग_लिखोw(UDC_SET_HALT, UDC_CTRL);
	पूर्ण
	udc->ep0_pending = 0;
	udc->ep[0].irqs = 0;
	udc->softconnect = 1;

	/* hook up the driver */
	driver->driver.bus = शून्य;
	udc->driver = driver;
	spin_unlock_irqrestore(&udc->lock, flags);

	अगर (udc->dc_clk != शून्य)
		omap_udc_enable_घड़ी(1);

	omap_ग_लिखोw(UDC_IRQ_SRC_MASK, UDC_IRQ_SRC);

	/* connect to bus through transceiver */
	अगर (!IS_ERR_OR_शून्य(udc->transceiver)) अणु
		status = otg_set_peripheral(udc->transceiver->otg,
						&udc->gadget);
		अगर (status < 0) अणु
			ERR("can't bind to transceiver\n");
			udc->driver = शून्य;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		status = 0;
		अगर (can_pullup(udc))
			pullup_enable(udc);
		अन्यथा
			pullup_disable(udc);
	पूर्ण

	/* boards that करोn't have VBUS sensing can't स्वतःgate 48MHz;
	 * can't enter deep sleep जबतक a gadget driver is active.
	 */
	अगर (machine_without_vbus_sense())
		omap_vbus_session(&udc->gadget, 1);

करोne:
	अगर (udc->dc_clk != शून्य)
		omap_udc_enable_घड़ी(0);

	वापस status;
पूर्ण

अटल पूर्णांक omap_udc_stop(काष्ठा usb_gadget *g)
अणु
	अचिन्हित दीर्घ	flags;

	अगर (udc->dc_clk != शून्य)
		omap_udc_enable_घड़ी(1);

	अगर (machine_without_vbus_sense())
		omap_vbus_session(&udc->gadget, 0);

	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		(व्योम) otg_set_peripheral(udc->transceiver->otg, शून्य);
	अन्यथा
		pullup_disable(udc);

	spin_lock_irqsave(&udc->lock, flags);
	udc_quiesce(udc);
	spin_unlock_irqrestore(&udc->lock, flags);

	udc->driver = शून्य;

	अगर (udc->dc_clk != शून्य)
		omap_udc_enable_घड़ी(0);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

#समावेश <linux/seq_file.h>

अटल स्थिर अक्षर proc_filename[] = "driver/udc";

#घोषणा FOURBITS "%s%s%s%s"
#घोषणा EIGHTBITS "%s%s%s%s%s%s%s%s"

अटल व्योम proc_ep_show(काष्ठा seq_file *s, काष्ठा omap_ep *ep)
अणु
	u16		stat_flg;
	काष्ठा omap_req	*req;
	अक्षर		buf[20];

	use_ep(ep, 0);

	अगर (use_dma && ep->has_dma)
		snम_लिखो(buf, माप buf, "(%cxdma%d lch%d) ",
			(ep->bEndpoपूर्णांकAddress & USB_सूची_IN) ? 't' : 'r',
			ep->dma_channel - 1, ep->lch);
	अन्यथा
		buf[0] = 0;

	stat_flg = omap_पढ़ोw(UDC_STAT_FLG);
	seq_म_लिखो(s,
		"\n%s %s%s%sirqs %ld stat %04x " EIGHTBITS FOURBITS "%s\n",
		ep->name, buf,
		ep->द्विगुन_buf ? "dbuf " : "",
		(अणु अक्षर *s;
		चयन (ep->ackरुको) अणु
		हाल 0:
			s = "";
			अवरोध;
		हाल 1:
			s = "(ackw) ";
			अवरोध;
		हाल 2:
			s = "(ackw2) ";
			अवरोध;
		शेष:
			s = "(?) ";
			अवरोध;
		पूर्ण s; पूर्ण),
		ep->irqs, stat_flg,
		(stat_flg & UDC_NO_RXPACKET) ? "no_rxpacket " : "",
		(stat_flg & UDC_MISS_IN) ? "miss_in " : "",
		(stat_flg & UDC_DATA_FLUSH) ? "data_flush " : "",
		(stat_flg & UDC_ISO_ERR) ? "iso_err " : "",
		(stat_flg & UDC_ISO_FIFO_EMPTY) ? "iso_fifo_empty " : "",
		(stat_flg & UDC_ISO_FIFO_FULL) ? "iso_fifo_full " : "",
		(stat_flg & UDC_EP_HALTED) ? "HALT " : "",
		(stat_flg & UDC_STALL) ? "STALL " : "",
		(stat_flg & UDC_NAK) ? "NAK " : "",
		(stat_flg & UDC_ACK) ? "ACK " : "",
		(stat_flg & UDC_FIFO_EN) ? "fifo_en " : "",
		(stat_flg & UDC_NON_ISO_FIFO_EMPTY) ? "fifo_empty " : "",
		(stat_flg & UDC_NON_ISO_FIFO_FULL) ? "fifo_full " : "");

	अगर (list_empty(&ep->queue))
		seq_म_लिखो(s, "\t(queue empty)\n");
	अन्यथा
		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			अचिन्हित	length = req->req.actual;

			अगर (use_dma && buf[0]) अणु
				length += ((ep->bEndpoपूर्णांकAddress & USB_सूची_IN)
						? dma_src_len : dma_dest_len)
					(ep, req->req.dma + length);
				buf[0] = 0;
			पूर्ण
			seq_म_लिखो(s, "\treq %p len %d/%d buf %p\n",
					&req->req, length,
					req->req.length, req->req.buf);
		पूर्ण
पूर्ण

अटल अक्षर *trx_mode(अचिन्हित m, पूर्णांक enabled)
अणु
	चयन (m) अणु
	हाल 0:
		वापस enabled ? "*6wire" : "unused";
	हाल 1:
		वापस "4wire";
	हाल 2:
		वापस "3wire";
	हाल 3:
		वापस "6wire";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक proc_otg_show(काष्ठा seq_file *s)
अणु
	u32		पंचांगp;
	u32		trans = 0;
	अक्षर		*ctrl_name = "(UNKNOWN)";

	पंचांगp = omap_पढ़ोl(OTG_REV);
	ctrl_name = "tranceiver_ctrl";
	trans = omap_पढ़ोw(USB_TRANSCEIVER_CTRL);
	seq_म_लिखो(s, "\nOTG rev %d.%d, %s %05x\n",
		पंचांगp >> 4, पंचांगp & 0xf, ctrl_name, trans);
	पंचांगp = omap_पढ़ोw(OTG_SYSCON_1);
	seq_म_लिखो(s, "otg_syscon1 %08x usb2 %s, usb1 %s, usb0 %s,"
			FOURBITS "\n", पंचांगp,
		trx_mode(USB2_TRX_MODE(पंचांगp), trans & CONF_USB2_UNI_R),
		trx_mode(USB1_TRX_MODE(पंचांगp), trans & CONF_USB1_UNI_R),
		(USB0_TRX_MODE(पंचांगp) == 0 && !cpu_is_omap1710())
			? "internal"
			: trx_mode(USB0_TRX_MODE(पंचांगp), 1),
		(पंचांगp & OTG_IDLE_EN) ? " !otg" : "",
		(पंचांगp & HST_IDLE_EN) ? " !host" : "",
		(पंचांगp & DEV_IDLE_EN) ? " !dev" : "",
		(पंचांगp & OTG_RESET_DONE) ? " reset_done" : " reset_active");
	पंचांगp = omap_पढ़ोl(OTG_SYSCON_2);
	seq_म_लिखो(s, "otg_syscon2 %08x%s" EIGHTBITS
			" b_ase_brst=%d hmc=%d\n", पंचांगp,
		(पंचांगp & OTG_EN) ? " otg_en" : "",
		(पंचांगp & USBX_SYNCHRO) ? " synchro" : "",
		/* much more SRP stuff */
		(पंचांगp & SRP_DATA) ? " srp_data" : "",
		(पंचांगp & SRP_VBUS) ? " srp_vbus" : "",
		(पंचांगp & OTG_PADEN) ? " otg_paden" : "",
		(पंचांगp & HMC_PADEN) ? " hmc_paden" : "",
		(पंचांगp & UHOST_EN) ? " uhost_en" : "",
		(पंचांगp & HMC_TLLSPEED) ? " tllspeed" : "",
		(पंचांगp & HMC_TLLATTACH) ? " tllattach" : "",
		B_ASE_BRST(पंचांगp),
		OTG_HMC(पंचांगp));
	पंचांगp = omap_पढ़ोl(OTG_CTRL);
	seq_म_लिखो(s, "otg_ctrl    %06x" EIGHTBITS EIGHTBITS "%s\n", पंचांगp,
		(पंचांगp & OTG_ASESSVLD) ? " asess" : "",
		(पंचांगp & OTG_BSESSEND) ? " bsess_end" : "",
		(पंचांगp & OTG_BSESSVLD) ? " bsess" : "",
		(पंचांगp & OTG_VBUSVLD) ? " vbus" : "",
		(पंचांगp & OTG_ID) ? " id" : "",
		(पंचांगp & OTG_DRIVER_SEL) ? " DEVICE" : " HOST",
		(पंचांगp & OTG_A_SETB_HNPEN) ? " a_setb_hnpen" : "",
		(पंचांगp & OTG_A_BUSREQ) ? " a_bus" : "",
		(पंचांगp & OTG_B_HNPEN) ? " b_hnpen" : "",
		(पंचांगp & OTG_B_BUSREQ) ? " b_bus" : "",
		(पंचांगp & OTG_BUSDROP) ? " busdrop" : "",
		(पंचांगp & OTG_PULLDOWN) ? " down" : "",
		(पंचांगp & OTG_PULLUP) ? " up" : "",
		(पंचांगp & OTG_DRV_VBUS) ? " drv" : "",
		(पंचांगp & OTG_PD_VBUS) ? " pd_vb" : "",
		(पंचांगp & OTG_PU_VBUS) ? " pu_vb" : "",
		(पंचांगp & OTG_PU_ID) ? " pu_id" : ""
		);
	पंचांगp = omap_पढ़ोw(OTG_IRQ_EN);
	seq_म_लिखो(s, "otg_irq_en  %04x" "\n", पंचांगp);
	पंचांगp = omap_पढ़ोw(OTG_IRQ_SRC);
	seq_म_लिखो(s, "otg_irq_src %04x" "\n", पंचांगp);
	पंचांगp = omap_पढ़ोw(OTG_OUTCTRL);
	seq_म_लिखो(s, "otg_outctrl %04x" "\n", पंचांगp);
	पंचांगp = omap_पढ़ोw(OTG_TEST);
	seq_म_लिखो(s, "otg_test    %04x" "\n", पंचांगp);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_udc_show(काष्ठा seq_file *s, व्योम *_)
अणु
	u32		पंचांगp;
	काष्ठा omap_ep	*ep;
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&udc->lock, flags);

	seq_म_लिखो(s, "%s, version: " DRIVER_VERSION
#अगर_घोषित	USE_ISO
		" (iso)"
#पूर्ण_अगर
		"%s\n",
		driver_desc,
		use_dma ?  " (dma)" : "");

	पंचांगp = omap_पढ़ोw(UDC_REV) & 0xff;
	seq_म_लिखो(s,
		"UDC rev %d.%d, fifo mode %d, gadget %s\n"
		"hmc %d, transceiver %s\n",
		पंचांगp >> 4, पंचांगp & 0xf,
		fअगरo_mode,
		udc->driver ? udc->driver->driver.name : "(none)",
		HMC,
		udc->transceiver
			? udc->transceiver->label
			: (cpu_is_omap1710()
				? "external" : "(none)"));
	seq_म_लिखो(s, "ULPD control %04x req %04x status %04x\n",
		omap_पढ़ोw(ULPD_CLOCK_CTRL),
		omap_पढ़ोw(ULPD_SOFT_REQ),
		omap_पढ़ोw(ULPD_STATUS_REQ));

	/* OTG controller रेजिस्टरs */
	अगर (!cpu_is_omap15xx())
		proc_otg_show(s);

	पंचांगp = omap_पढ़ोw(UDC_SYSCON1);
	seq_म_लिखो(s, "\nsyscon1     %04x" EIGHTBITS "\n", पंचांगp,
		(पंचांगp & UDC_CFG_LOCK) ? " cfg_lock" : "",
		(पंचांगp & UDC_DATA_ENDIAN) ? " data_endian" : "",
		(पंचांगp & UDC_DMA_ENDIAN) ? " dma_endian" : "",
		(पंचांगp & UDC_NAK_EN) ? " nak" : "",
		(पंचांगp & UDC_AUTODECODE_DIS) ? " autodecode_dis" : "",
		(पंचांगp & UDC_SELF_PWR) ? " self_pwr" : "",
		(पंचांगp & UDC_SOFF_DIS) ? " soff_dis" : "",
		(पंचांगp & UDC_PULLUP_EN) ? " PULLUP" : "");
	/* syscon2 is ग_लिखो-only */

	/* UDC controller रेजिस्टरs */
	अगर (!(पंचांगp & UDC_PULLUP_EN)) अणु
		seq_म_लिखो(s, "(suspended)\n");
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस 0;
	पूर्ण

	पंचांगp = omap_पढ़ोw(UDC_DEVSTAT);
	seq_म_लिखो(s, "devstat     %04x" EIGHTBITS "%s%s\n", पंचांगp,
		(पंचांगp & UDC_B_HNP_ENABLE) ? " b_hnp" : "",
		(पंचांगp & UDC_A_HNP_SUPPORT) ? " a_hnp" : "",
		(पंचांगp & UDC_A_ALT_HNP_SUPPORT) ? " a_alt_hnp" : "",
		(पंचांगp & UDC_R_WK_OK) ? " r_wk_ok" : "",
		(पंचांगp & UDC_USB_RESET) ? " usb_reset" : "",
		(पंचांगp & UDC_SUS) ? " SUS" : "",
		(पंचांगp & UDC_CFG) ? " CFG" : "",
		(पंचांगp & UDC_ADD) ? " ADD" : "",
		(पंचांगp & UDC_DEF) ? " DEF" : "",
		(पंचांगp & UDC_ATT) ? " ATT" : "");
	seq_म_लिखो(s, "sof         %04x\n", omap_पढ़ोw(UDC_SOF));
	पंचांगp = omap_पढ़ोw(UDC_IRQ_EN);
	seq_म_लिखो(s, "irq_en      %04x" FOURBITS "%s\n", पंचांगp,
		(पंचांगp & UDC_SOF_IE) ? " sof" : "",
		(पंचांगp & UDC_EPN_RX_IE) ? " epn_rx" : "",
		(पंचांगp & UDC_EPN_TX_IE) ? " epn_tx" : "",
		(पंचांगp & UDC_DS_CHG_IE) ? " ds_chg" : "",
		(पंचांगp & UDC_EP0_IE) ? " ep0" : "");
	पंचांगp = omap_पढ़ोw(UDC_IRQ_SRC);
	seq_म_लिखो(s, "irq_src     %04x" EIGHTBITS "%s%s\n", पंचांगp,
		(पंचांगp & UDC_TXN_DONE) ? " txn_done" : "",
		(पंचांगp & UDC_RXN_CNT) ? " rxn_cnt" : "",
		(पंचांगp & UDC_RXN_EOT) ? " rxn_eot" : "",
		(पंचांगp & UDC_IRQ_SOF) ? " sof" : "",
		(पंचांगp & UDC_EPN_RX) ? " epn_rx" : "",
		(पंचांगp & UDC_EPN_TX) ? " epn_tx" : "",
		(पंचांगp & UDC_DS_CHG) ? " ds_chg" : "",
		(पंचांगp & UDC_SETUP) ? " setup" : "",
		(पंचांगp & UDC_EP0_RX) ? " ep0out" : "",
		(पंचांगp & UDC_EP0_TX) ? " ep0in" : "");
	अगर (use_dma) अणु
		अचिन्हित i;

		पंचांगp = omap_पढ़ोw(UDC_DMA_IRQ_EN);
		seq_म_लिखो(s, "dma_irq_en  %04x%s" EIGHTBITS "\n", पंचांगp,
			(पंचांगp & UDC_TX_DONE_IE(3)) ? " tx2_done" : "",
			(पंचांगp & UDC_RX_CNT_IE(3)) ? " rx2_cnt" : "",
			(पंचांगp & UDC_RX_EOT_IE(3)) ? " rx2_eot" : "",

			(पंचांगp & UDC_TX_DONE_IE(2)) ? " tx1_done" : "",
			(पंचांगp & UDC_RX_CNT_IE(2)) ? " rx1_cnt" : "",
			(पंचांगp & UDC_RX_EOT_IE(2)) ? " rx1_eot" : "",

			(पंचांगp & UDC_TX_DONE_IE(1)) ? " tx0_done" : "",
			(पंचांगp & UDC_RX_CNT_IE(1)) ? " rx0_cnt" : "",
			(पंचांगp & UDC_RX_EOT_IE(1)) ? " rx0_eot" : "");

		पंचांगp = omap_पढ़ोw(UDC_RXDMA_CFG);
		seq_म_लिखो(s, "rxdma_cfg   %04x\n", पंचांगp);
		अगर (पंचांगp) अणु
			क्रम (i = 0; i < 3; i++) अणु
				अगर ((पंचांगp & (0x0f << (i * 4))) == 0)
					जारी;
				seq_म_लिखो(s, "rxdma[%d]    %04x\n", i,
						omap_पढ़ोw(UDC_RXDMA(i + 1)));
			पूर्ण
		पूर्ण
		पंचांगp = omap_पढ़ोw(UDC_TXDMA_CFG);
		seq_म_लिखो(s, "txdma_cfg   %04x\n", पंचांगp);
		अगर (पंचांगp) अणु
			क्रम (i = 0; i < 3; i++) अणु
				अगर (!(पंचांगp & (0x0f << (i * 4))))
					जारी;
				seq_म_लिखो(s, "txdma[%d]    %04x\n", i,
						omap_पढ़ोw(UDC_TXDMA(i + 1)));
			पूर्ण
		पूर्ण
	पूर्ण

	पंचांगp = omap_पढ़ोw(UDC_DEVSTAT);
	अगर (पंचांगp & UDC_ATT) अणु
		proc_ep_show(s, &udc->ep[0]);
		अगर (पंचांगp & UDC_ADD) अणु
			list_क्रम_each_entry(ep, &udc->gadget.ep_list,
					ep.ep_list) अणु
				अगर (ep->ep.desc)
					proc_ep_show(s, ep);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम create_proc_file(व्योम)
अणु
	proc_create_single(proc_filename, 0, शून्य, proc_udc_show);
पूर्ण

अटल व्योम हटाओ_proc_file(व्योम)
अणु
	हटाओ_proc_entry(proc_filename, शून्य);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम create_proc_file(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम हटाओ_proc_file(व्योम) अणुपूर्ण

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* Beक्रमe this controller can क्रमागतerate, we need to pick an endpoपूर्णांक
 * configuration, or "fifo_mode"  That involves allocating 2KB of packet
 * buffer space among the endpoपूर्णांकs we'll be operating.
 *
 * NOTE: as of OMAP 1710 ES2.0, writing a new endpoपूर्णांक config when
 * UDC_SYSCON_1.CFG_LOCK is set can now work.  We won't use that
 * capability yet though.
 */
अटल अचिन्हित
omap_ep_setup(अक्षर *name, u8 addr, u8 type,
		अचिन्हित buf, अचिन्हित maxp, पूर्णांक dbuf)
अणु
	काष्ठा omap_ep	*ep;
	u16		epn_rxtx = 0;

	/* OUT endpoपूर्णांकs first, then IN */
	ep = &udc->ep[addr & 0xf];
	अगर (addr & USB_सूची_IN)
		ep += 16;

	/* in हाल of ep init table bugs */
	BUG_ON(ep->name[0]);

	/* chip setup ... bit values are same क्रम IN, OUT */
	अगर (type == USB_ENDPOINT_XFER_ISOC) अणु
		चयन (maxp) अणु
		हाल 8:
			epn_rxtx = 0 << 12;
			अवरोध;
		हाल 16:
			epn_rxtx = 1 << 12;
			अवरोध;
		हाल 32:
			epn_rxtx = 2 << 12;
			अवरोध;
		हाल 64:
			epn_rxtx = 3 << 12;
			अवरोध;
		हाल 128:
			epn_rxtx = 4 << 12;
			अवरोध;
		हाल 256:
			epn_rxtx = 5 << 12;
			अवरोध;
		हाल 512:
			epn_rxtx = 6 << 12;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		epn_rxtx |= UDC_EPN_RX_ISO;
		dbuf = 1;
	पूर्ण अन्यथा अणु
		/* द्विगुन-buffering "not supported" on 15xx,
		 * and ignored क्रम PIO-IN on newer chips
		 * (क्रम more reliable behavior)
		 */
		अगर (!use_dma || cpu_is_omap15xx())
			dbuf = 0;

		चयन (maxp) अणु
		हाल 8:
			epn_rxtx = 0 << 12;
			अवरोध;
		हाल 16:
			epn_rxtx = 1 << 12;
			अवरोध;
		हाल 32:
			epn_rxtx = 2 << 12;
			अवरोध;
		हाल 64:
			epn_rxtx = 3 << 12;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अगर (dbuf && addr)
			epn_rxtx |= UDC_EPN_RX_DB;
		समयr_setup(&ep->समयr, pio_out_समयr, 0);
	पूर्ण
	अगर (addr)
		epn_rxtx |= UDC_EPN_RX_VALID;
	BUG_ON(buf & 0x07);
	epn_rxtx |= buf >> 3;

	DBG("%s addr %02x rxtx %04x maxp %d%s buf %d\n",
		name, addr, epn_rxtx, maxp, dbuf ? "x2" : "", buf);

	अगर (addr & USB_सूची_IN)
		omap_ग_लिखोw(epn_rxtx, UDC_EP_TX(addr & 0xf));
	अन्यथा
		omap_ग_लिखोw(epn_rxtx, UDC_EP_RX(addr));

	/* next endpoपूर्णांक's buffer starts after this one's */
	buf += maxp;
	अगर (dbuf)
		buf += maxp;
	BUG_ON(buf > 2048);

	/* set up driver data काष्ठाures */
	BUG_ON(म_माप(name) >= माप ep->name);
	strlcpy(ep->name, name, माप ep->name);
	INIT_LIST_HEAD(&ep->queue);
	INIT_LIST_HEAD(&ep->iso);
	ep->bEndpoपूर्णांकAddress = addr;
	ep->bmAttributes = type;
	ep->द्विगुन_buf = dbuf;
	ep->udc = udc;

	चयन (type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		ep->ep.caps.type_control = true;
		ep->ep.caps.dir_in = true;
		ep->ep.caps.dir_out = true;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		ep->ep.caps.type_iso = true;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		ep->ep.caps.type_bulk = true;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		ep->ep.caps.type_पूर्णांक = true;
		अवरोध;
	पूर्ण

	अगर (addr & USB_सूची_IN)
		ep->ep.caps.dir_in = true;
	अन्यथा
		ep->ep.caps.dir_out = true;

	ep->ep.name = ep->name;
	ep->ep.ops = &omap_ep_ops;
	ep->maxpacket = maxp;
	usb_ep_set_maxpacket_limit(&ep->ep, ep->maxpacket);
	list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);

	वापस buf;
पूर्ण

अटल व्योम omap_udc_release(काष्ठा device *dev)
अणु
	pullup_disable(udc);
	अगर (!IS_ERR_OR_शून्य(udc->transceiver)) अणु
		usb_put_phy(udc->transceiver);
		udc->transceiver = शून्य;
	पूर्ण
	omap_ग_लिखोw(0, UDC_SYSCON1);
	हटाओ_proc_file();
	अगर (udc->dc_clk) अणु
		अगर (udc->clk_requested)
			omap_udc_enable_घड़ी(0);
		clk_put(udc->hhc_clk);
		clk_put(udc->dc_clk);
	पूर्ण
	अगर (udc->करोne)
		complete(udc->करोne);
	kमुक्त(udc);
पूर्ण

अटल पूर्णांक
omap_udc_setup(काष्ठा platक्रमm_device *odev, काष्ठा usb_phy *xceiv)
अणु
	अचिन्हित	पंचांगp, buf;

	/* abolish any previous hardware state */
	omap_ग_लिखोw(0, UDC_SYSCON1);
	omap_ग_लिखोw(0, UDC_IRQ_EN);
	omap_ग_लिखोw(UDC_IRQ_SRC_MASK, UDC_IRQ_SRC);
	omap_ग_लिखोw(0, UDC_DMA_IRQ_EN);
	omap_ग_लिखोw(0, UDC_RXDMA_CFG);
	omap_ग_लिखोw(0, UDC_TXDMA_CFG);

	/* UDC_PULLUP_EN gates the chip घड़ी */
	/* OTG_SYSCON_1 |= DEV_IDLE_EN; */

	udc = kzalloc(माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	spin_lock_init(&udc->lock);

	udc->gadget.ops = &omap_gadget_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	INIT_LIST_HEAD(&udc->gadget.ep_list);
	INIT_LIST_HEAD(&udc->iso);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.max_speed = USB_SPEED_FULL;
	udc->gadget.name = driver_name;
	udc->gadget.quirk_ep_out_aligned_size = 1;
	udc->transceiver = xceiv;

	/* ep0 is special; put it right after the SETUP buffer */
	buf = omap_ep_setup("ep0", 0, USB_ENDPOINT_XFER_CONTROL,
			8 /* after SETUP */, 64 /* maxpacket */, 0);
	list_del_init(&udc->ep[0].ep.ep_list);

	/* initially disable all non-ep0 endpoपूर्णांकs */
	क्रम (पंचांगp = 1; पंचांगp < 15; पंचांगp++) अणु
		omap_ग_लिखोw(0, UDC_EP_RX(पंचांगp));
		omap_ग_लिखोw(0, UDC_EP_TX(पंचांगp));
	पूर्ण

#घोषणा OMAP_BULK_EP(name, addr) \
	buf = omap_ep_setup(name "-bulk", addr, \
			USB_ENDPOINT_XFER_BULK, buf, 64, 1);
#घोषणा OMAP_INT_EP(name, addr, maxp) \
	buf = omap_ep_setup(name "-int", addr, \
			USB_ENDPOINT_XFER_INT, buf, maxp, 0);
#घोषणा OMAP_ISO_EP(name, addr, maxp) \
	buf = omap_ep_setup(name "-iso", addr, \
			USB_ENDPOINT_XFER_ISOC, buf, maxp, 1);

	चयन (fअगरo_mode) अणु
	हाल 0:
		OMAP_BULK_EP("ep1in",  USB_सूची_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_सूची_OUT | 2);
		OMAP_INT_EP("ep3in",   USB_सूची_IN  | 3, 16);
		अवरोध;
	हाल 1:
		OMAP_BULK_EP("ep1in",  USB_सूची_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_सूची_OUT | 2);
		OMAP_INT_EP("ep9in",   USB_सूची_IN  | 9, 16);

		OMAP_BULK_EP("ep3in",  USB_सूची_IN  | 3);
		OMAP_BULK_EP("ep4out", USB_सूची_OUT | 4);
		OMAP_INT_EP("ep10in",  USB_सूची_IN  | 10, 16);

		OMAP_BULK_EP("ep5in",  USB_सूची_IN  | 5);
		OMAP_BULK_EP("ep5out", USB_सूची_OUT | 5);
		OMAP_INT_EP("ep11in",  USB_सूची_IN  | 11, 16);

		OMAP_BULK_EP("ep6in",  USB_सूची_IN  | 6);
		OMAP_BULK_EP("ep6out", USB_सूची_OUT | 6);
		OMAP_INT_EP("ep12in",  USB_सूची_IN  | 12, 16);

		OMAP_BULK_EP("ep7in",  USB_सूची_IN  | 7);
		OMAP_BULK_EP("ep7out", USB_सूची_OUT | 7);
		OMAP_INT_EP("ep13in",  USB_सूची_IN  | 13, 16);
		OMAP_INT_EP("ep13out", USB_सूची_OUT | 13, 16);

		OMAP_BULK_EP("ep8in",  USB_सूची_IN  | 8);
		OMAP_BULK_EP("ep8out", USB_सूची_OUT | 8);
		OMAP_INT_EP("ep14in",  USB_सूची_IN  | 14, 16);
		OMAP_INT_EP("ep14out", USB_सूची_OUT | 14, 16);

		OMAP_BULK_EP("ep15in",  USB_सूची_IN  | 15);
		OMAP_BULK_EP("ep15out", USB_सूची_OUT | 15);

		अवरोध;

#अगर_घोषित	USE_ISO
	हाल 2:			/* mixed iso/bulk */
		OMAP_ISO_EP("ep1in",   USB_सूची_IN  | 1, 256);
		OMAP_ISO_EP("ep2out",  USB_सूची_OUT | 2, 256);
		OMAP_ISO_EP("ep3in",   USB_सूची_IN  | 3, 128);
		OMAP_ISO_EP("ep4out",  USB_सूची_OUT | 4, 128);

		OMAP_INT_EP("ep5in",   USB_सूची_IN  | 5, 16);

		OMAP_BULK_EP("ep6in",  USB_सूची_IN  | 6);
		OMAP_BULK_EP("ep7out", USB_सूची_OUT | 7);
		OMAP_INT_EP("ep8in",   USB_सूची_IN  | 8, 16);
		अवरोध;
	हाल 3:			/* mixed bulk/iso */
		OMAP_BULK_EP("ep1in",  USB_सूची_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_सूची_OUT | 2);
		OMAP_INT_EP("ep3in",   USB_सूची_IN  | 3, 16);

		OMAP_BULK_EP("ep4in",  USB_सूची_IN  | 4);
		OMAP_BULK_EP("ep5out", USB_सूची_OUT | 5);
		OMAP_INT_EP("ep6in",   USB_सूची_IN  | 6, 16);

		OMAP_ISO_EP("ep7in",   USB_सूची_IN  | 7, 256);
		OMAP_ISO_EP("ep8out",  USB_सूची_OUT | 8, 256);
		OMAP_INT_EP("ep9in",   USB_सूची_IN  | 9, 16);
		अवरोध;
#पूर्ण_अगर

	/* add more modes as needed */

	शेष:
		ERR("unsupported fifo_mode #%d\n", fअगरo_mode);
		वापस -ENODEV;
	पूर्ण
	omap_ग_लिखोw(UDC_CFG_LOCK|UDC_SELF_PWR, UDC_SYSCON1);
	INFO("fifo mode %d, %d bytes not used\n", fअगरo_mode, 2048 - buf);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक			status = -ENODEV;
	पूर्णांक			hmc;
	काष्ठा usb_phy		*xceiv = शून्य;
	स्थिर अक्षर		*type = शून्य;
	काष्ठा omap_usb_config	*config = dev_get_platdata(&pdev->dev);
	काष्ठा clk		*dc_clk = शून्य;
	काष्ठा clk		*hhc_clk = शून्य;

	अगर (cpu_is_omap7xx())
		use_dma = 0;

	/* NOTE:  "knows" the order of the resources! */
	अगर (!request_mem_region(pdev->resource[0].start,
			resource_size(&pdev->resource[0]),
			driver_name)) अणु
		DBG("request_mem_region failed\n");
		वापस -EBUSY;
	पूर्ण

	अगर (cpu_is_omap16xx()) अणु
		dc_clk = clk_get(&pdev->dev, "usb_dc_ck");
		hhc_clk = clk_get(&pdev->dev, "usb_hhc_ck");
		BUG_ON(IS_ERR(dc_clk) || IS_ERR(hhc_clk));
		/* can't use omap_udc_enable_घड़ी yet */
		clk_enable(dc_clk);
		clk_enable(hhc_clk);
		udelay(100);
	पूर्ण

	अगर (cpu_is_omap7xx()) अणु
		dc_clk = clk_get(&pdev->dev, "usb_dc_ck");
		hhc_clk = clk_get(&pdev->dev, "l3_ocpi_ck");
		BUG_ON(IS_ERR(dc_clk) || IS_ERR(hhc_clk));
		/* can't use omap_udc_enable_घड़ी yet */
		clk_enable(dc_clk);
		clk_enable(hhc_clk);
		udelay(100);
	पूर्ण

	INFO("OMAP UDC rev %d.%d%s\n",
		omap_पढ़ोw(UDC_REV) >> 4, omap_पढ़ोw(UDC_REV) & 0xf,
		config->otg ? ", Mini-AB" : "");

	/* use the mode given to us by board init code */
	अगर (cpu_is_omap15xx()) अणु
		hmc = HMC_1510;
		type = "(unknown)";

		अगर (machine_without_vbus_sense()) अणु
			/* just set up software VBUS detect, and then
			 * later rig it so we always report VBUS.
			 * FIXME without really sensing VBUS, we can't
			 * know when to turn PULLUP_EN on/off; and that
			 * means we always "need" the 48MHz घड़ी.
			 */
			u32 पंचांगp = omap_पढ़ोl(FUNC_MUX_CTRL_0);
			पंचांगp &= ~VBUS_CTRL_1510;
			omap_ग_लिखोl(पंचांगp, FUNC_MUX_CTRL_0);
			पंचांगp |= VBUS_MODE_1510;
			पंचांगp &= ~VBUS_CTRL_1510;
			omap_ग_लिखोl(पंचांगp, FUNC_MUX_CTRL_0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The transceiver may package some GPIO logic or handle
		 * loopback and/or transceiverless setup; अगर we find one,
		 * use it.  Except क्रम OTG, we करोn't _need_ to talk to one;
		 * but not having one probably means no VBUS detection.
		 */
		xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
		अगर (!IS_ERR_OR_शून्य(xceiv))
			type = xceiv->label;
		अन्यथा अगर (config->otg) अणु
			DBG("OTG requires external transceiver!\n");
			जाओ cleanup0;
		पूर्ण

		hmc = HMC_1610;

		चयन (hmc) अणु
		हाल 0:			/* POWERUP DEFAULT == 0 */
		हाल 4:
		हाल 12:
		हाल 20:
			अगर (!cpu_is_omap1710()) अणु
				type = "integrated";
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 3:
		हाल 11:
		हाल 16:
		हाल 19:
		हाल 25:
			अगर (IS_ERR_OR_शून्य(xceiv)) अणु
				DBG("external transceiver not registered!\n");
				type = "unknown";
			पूर्ण
			अवरोध;
		हाल 21:			/* पूर्णांकernal loopback */
			type = "loopback";
			अवरोध;
		हाल 14:			/* transceiverless */
			अगर (cpu_is_omap1710())
				जाओ bad_on_1710;
			fallthrough;
		हाल 13:
		हाल 15:
			type = "no";
			अवरोध;

		शेष:
bad_on_1710:
			ERR("unrecognized UDC HMC mode %d\n", hmc);
			जाओ cleanup0;
		पूर्ण
	पूर्ण

	INFO("hmc mode %d, %s transceiver\n", hmc, type);

	/* a "gadget" असलtracts/भवizes the controller */
	status = omap_udc_setup(pdev, xceiv);
	अगर (status)
		जाओ cleanup0;

	xceiv = शून्य;
	/* "udc" is now valid */
	pullup_disable(udc);
#अगर	IS_ENABLED(CONFIG_USB_OHCI_HCD)
	udc->gadget.is_otg = (config->otg != 0);
#पूर्ण_अगर

	/* starting with omap1710 es2.0, clear toggle is a separate bit */
	अगर (omap_पढ़ोw(UDC_REV) >= 0x61)
		udc->clr_halt = UDC_RESET_EP | UDC_CLRDATA_TOGGLE;
	अन्यथा
		udc->clr_halt = UDC_RESET_EP;

	/* USB general purpose IRQ:  ep0, state changes, dma, etc */
	status = devm_request_irq(&pdev->dev, pdev->resource[1].start,
				  omap_udc_irq, 0, driver_name, udc);
	अगर (status != 0) अणु
		ERR("can't get irq %d, err %d\n",
			(पूर्णांक) pdev->resource[1].start, status);
		जाओ cleanup1;
	पूर्ण

	/* USB "non-iso" IRQ (PIO क्रम all but ep0) */
	status = devm_request_irq(&pdev->dev, pdev->resource[2].start,
				  omap_udc_pio_irq, 0, "omap_udc pio", udc);
	अगर (status != 0) अणु
		ERR("can't get irq %d, err %d\n",
			(पूर्णांक) pdev->resource[2].start, status);
		जाओ cleanup1;
	पूर्ण
#अगर_घोषित	USE_ISO
	status = devm_request_irq(&pdev->dev, pdev->resource[3].start,
				  omap_udc_iso_irq, 0, "omap_udc iso", udc);
	अगर (status != 0) अणु
		ERR("can't get irq %d, err %d\n",
			(पूर्णांक) pdev->resource[3].start, status);
		जाओ cleanup1;
	पूर्ण
#पूर्ण_अगर
	अगर (cpu_is_omap16xx() || cpu_is_omap7xx()) अणु
		udc->dc_clk = dc_clk;
		udc->hhc_clk = hhc_clk;
		clk_disable(hhc_clk);
		clk_disable(dc_clk);
	पूर्ण

	create_proc_file();
	वापस usb_add_gadget_udc_release(&pdev->dev, &udc->gadget,
					  omap_udc_release);

cleanup1:
	kमुक्त(udc);
	udc = शून्य;

cleanup0:
	अगर (!IS_ERR_OR_शून्य(xceiv))
		usb_put_phy(xceiv);

	अगर (cpu_is_omap16xx() || cpu_is_omap7xx()) अणु
		clk_disable(hhc_clk);
		clk_disable(dc_clk);
		clk_put(hhc_clk);
		clk_put(dc_clk);
	पूर्ण

	release_mem_region(pdev->resource[0].start,
			   resource_size(&pdev->resource[0]));

	वापस status;
पूर्ण

अटल पूर्णांक omap_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);

	udc->करोne = &करोne;

	usb_del_gadget_udc(&udc->gadget);

	रुको_क्रम_completion(&करोne);

	release_mem_region(pdev->resource[0].start,
			   resource_size(&pdev->resource[0]));

	वापस 0;
पूर्ण

/* suspend/resume/wakeup from sysfs (echo > घातer/state) or when the
 * प्रणाली is क्रमced पूर्णांकo deep sleep
 *
 * REVISIT we should probably reject suspend requests when there's a host
 * session active, rather than disconnecting, at least on boards that can
 * report VBUS irqs (UDC_DEVSTAT.UDC_ATT).  And in any हाल, we need to
 * make host resumes and VBUS detection trigger OMAP wakeup events; that
 * may involve talking to an बाह्यal transceiver (e.g. isp1301).
 */

अटल पूर्णांक omap_udc_suspend(काष्ठा platक्रमm_device *dev, pm_message_t message)
अणु
	u32	devstat;

	devstat = omap_पढ़ोw(UDC_DEVSTAT);

	/* we're requesting 48 MHz घड़ी अगर the pullup is enabled
	 * (== we're attached to the host) and we're not suspended,
	 * which would prevent entry to deep sleep...
	 */
	अगर ((devstat & UDC_ATT) != 0 && (devstat & UDC_SUS) == 0) अणु
		WARNING("session active; suspend requires disconnect\n");
		omap_pullup(&udc->gadget, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_udc_resume(काष्ठा platक्रमm_device *dev)
अणु
	DBG("resume + wakeup/SRP\n");
	omap_pullup(&udc->gadget, 1);

	/* maybe the host would क्रमागतerate us अगर we nudged it */
	msleep(100);
	वापस omap_wakeup(&udc->gadget);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.probe		= omap_udc_probe,
	.हटाओ		= omap_udc_हटाओ,
	.suspend	= omap_udc_suspend,
	.resume		= omap_udc_resume,
	.driver		= अणु
		.name	= driver_name,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(udc_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap_udc");
