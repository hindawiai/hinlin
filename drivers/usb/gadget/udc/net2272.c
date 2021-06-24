<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम PLX NET2272 USB device controller
 *
 * Copyright (C) 2005-2006 PLX Technology, Inc.
 * Copyright (C) 2006-2011 Analog Devices, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "net2272.h"

#घोषणा DRIVER_DESC "PLX NET2272 USB Peripheral Controller"

अटल स्थिर अक्षर driver_name[] = "net2272";
अटल स्थिर अक्षर driver_vers[] = "2006 October 17/mainline";
अटल स्थिर अक्षर driver_desc[] = DRIVER_DESC;

अटल स्थिर अक्षर ep0name[] = "ep0";
अटल स्थिर अक्षर * स्थिर ep_name[] = अणु
	ep0name,
	"ep-a", "ep-b", "ep-c",
पूर्ण;

#अगर_घोषित CONFIG_USB_NET2272_DMA
/*
 * use_dma: the NET2272 can use an बाह्यal DMA controller.
 * Note that since there is no generic DMA api, some functions,
 * notably request_dma, start_dma, and cancel_dma will need to be
 * modअगरied क्रम your platक्रमm's particular dma controller.
 *
 * If use_dma is disabled, pio will be used instead.
 */
अटल bool use_dma = false;
module_param(use_dma, bool, 0644);

/*
 * dma_ep: selects the endpoपूर्णांक क्रम use with dma (1=ep-a, 2=ep-b)
 * The NET2272 can only use dma क्रम a single endpoपूर्णांक at a समय.
 * At some poपूर्णांक this could be modअगरied to allow either endpoपूर्णांक
 * to take control of dma as it becomes available.
 *
 * Note that DMA should not be used on OUT endpoपूर्णांकs unless it can
 * be guaranteed that no लघु packets will arrive on an IN endpoपूर्णांक
 * जबतक the DMA operation is pending.  Otherwise the OUT DMA will
 * terminate prematurely (See NET2272 Errata 630-0213-0101)
 */
अटल uलघु dma_ep = 1;
module_param(dma_ep, uलघु, 0644);

/*
 * dma_mode: net2272 dma mode setting (see LOCCTL1 definiton):
 *	mode 0 == Slow DREQ mode
 *	mode 1 == Fast DREQ mode
 *	mode 2 == Burst mode
 */
अटल uलघु dma_mode = 2;
module_param(dma_mode, uलघु, 0644);
#अन्यथा
#घोषणा use_dma 0
#घोषणा dma_ep 1
#घोषणा dma_mode 2
#पूर्ण_अगर

/*
 * fअगरo_mode: net2272 buffer configuration:
 *      mode 0 == ep-अणुa,b,cपूर्ण 512db each
 *      mode 1 == ep-a 1k, ep-अणुb,cपूर्ण 512db
 *      mode 2 == ep-a 1k, ep-b 1k, ep-c 512db
 *      mode 3 == ep-a 1k, ep-b disabled, ep-c 512db
 */
अटल uलघु fअगरo_mode = 0;
module_param(fअगरo_mode, uलघु, 0644);

/*
 * enable_suspend: When enabled, the driver will respond to
 * USB suspend requests by घातering करोwn the NET2272.  Otherwise,
 * USB suspend requests will be ignored.  This is acceptible क्रम
 * self-घातered devices.  For bus घातered devices set this to 1.
 */
अटल uलघु enable_suspend = 0;
module_param(enable_suspend, uलघु, 0644);

अटल व्योम निश्चित_out_naking(काष्ठा net2272_ep *ep, स्थिर अक्षर *where)
अणु
	u8 पंचांगp;

#अगर_अघोषित DEBUG
	वापस;
#पूर्ण_अगर

	पंचांगp = net2272_ep_पढ़ो(ep, EP_STAT0);
	अगर ((पंचांगp & (1 << NAK_OUT_PACKETS)) == 0) अणु
		dev_dbg(ep->dev->dev, "%s %s %02x !NAK\n",
			ep->ep.name, where, पंचांगp);
		net2272_ep_ग_लिखो(ep, EP_RSPSET, 1 << ALT_NAK_OUT_PACKETS);
	पूर्ण
पूर्ण
#घोषणा ASSERT_OUT_NAKING(ep) निश्चित_out_naking(ep, __func__)

अटल व्योम stop_out_naking(काष्ठा net2272_ep *ep)
अणु
	u8 पंचांगp = net2272_ep_पढ़ो(ep, EP_STAT0);

	अगर ((पंचांगp & (1 << NAK_OUT_PACKETS)) != 0)
		net2272_ep_ग_लिखो(ep, EP_RSPCLR, 1 << ALT_NAK_OUT_PACKETS);
पूर्ण

#घोषणा PIPEसूची(bAddress) (usb_pipein(bAddress) ? "in" : "out")

अटल अक्षर *type_string(u8 bmAttributes)
अणु
	चयन ((bmAttributes) & USB_ENDPOINT_XFERTYPE_MASK) अणु
	हाल USB_ENDPOINT_XFER_BULK: वापस "bulk";
	हाल USB_ENDPOINT_XFER_ISOC: वापस "iso";
	हाल USB_ENDPOINT_XFER_INT:  वापस "intr";
	शेष:                     वापस "control";
	पूर्ण
पूर्ण

अटल अक्षर *buf_state_string(अचिन्हित state)
अणु
	चयन (state) अणु
	हाल BUFF_FREE:  वापस "free";
	हाल BUFF_VALID: वापस "valid";
	हाल BUFF_LCL:   वापस "local";
	हाल BUFF_USB:   वापस "usb";
	शेष:         वापस "unknown";
	पूर्ण
पूर्ण

अटल अक्षर *dma_mode_string(व्योम)
अणु
	अगर (!use_dma)
		वापस "PIO";
	चयन (dma_mode) अणु
	हाल 0:  वापस "SLOW DREQ";
	हाल 1:  वापस "FAST DREQ";
	हाल 2:  वापस "BURST";
	शेष: वापस "invalid";
	पूर्ण
पूर्ण

अटल व्योम net2272_dequeue_all(काष्ठा net2272_ep *);
अटल पूर्णांक net2272_kick_dma(काष्ठा net2272_ep *, काष्ठा net2272_request *);
अटल पूर्णांक net2272_fअगरo_status(काष्ठा usb_ep *);

अटल स्थिर काष्ठा usb_ep_ops net2272_ep_ops;

/*---------------------------------------------------------------------------*/

अटल पूर्णांक
net2272_enable(काष्ठा usb_ep *_ep, स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा net2272 *dev;
	काष्ठा net2272_ep *ep;
	u32 max;
	u8 पंचांगp;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || !desc || ep->desc || _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;
	dev = ep->dev;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	max = usb_endpoपूर्णांक_maxp(desc);

	spin_lock_irqsave(&dev->lock, flags);
	_ep->maxpacket = max;
	ep->desc = desc;

	/* net2272_ep_reset() has alपढ़ोy been called */
	ep->stopped = 0;
	ep->wedged = 0;

	/* set speed-dependent max packet */
	net2272_ep_ग_लिखो(ep, EP_MAXPKT0, max & 0xff);
	net2272_ep_ग_लिखो(ep, EP_MAXPKT1, (max & 0xff00) >> 8);

	/* set type, direction, address; reset fअगरo counters */
	net2272_ep_ग_लिखो(ep, EP_STAT1, 1 << BUFFER_FLUSH);
	पंचांगp = usb_endpoपूर्णांक_type(desc);
	अगर (usb_endpoपूर्णांक_xfer_bulk(desc)) अणु
		/* catch some particularly blatant driver bugs */
		अगर ((dev->gadget.speed == USB_SPEED_HIGH && max != 512) ||
		    (dev->gadget.speed == USB_SPEED_FULL && max > 64)) अणु
			spin_unlock_irqrestore(&dev->lock, flags);
			वापस -दुस्फल;
		पूर्ण
	पूर्ण
	ep->is_iso = usb_endpoपूर्णांक_xfer_isoc(desc) ? 1 : 0;
	पंचांगp <<= ENDPOINT_TYPE;
	पंचांगp |= ((desc->bEndpoपूर्णांकAddress & 0x0f) << ENDPOINT_NUMBER);
	पंचांगp |= usb_endpoपूर्णांक_dir_in(desc) << ENDPOINT_सूचीECTION;
	पंचांगp |= (1 << ENDPOINT_ENABLE);

	/* क्रम OUT transfers, block the rx fअगरo until a पढ़ो is posted */
	ep->is_in = usb_endpoपूर्णांक_dir_in(desc);
	अगर (!ep->is_in)
		net2272_ep_ग_लिखो(ep, EP_RSPSET, 1 << ALT_NAK_OUT_PACKETS);

	net2272_ep_ग_लिखो(ep, EP_CFG, पंचांगp);

	/* enable irqs */
	पंचांगp = (1 << ep->num) | net2272_पढ़ो(dev, IRQENB0);
	net2272_ग_लिखो(dev, IRQENB0, पंचांगp);

	पंचांगp = (1 << DATA_PACKET_RECEIVED_INTERRUPT_ENABLE)
		| (1 << DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE)
		| net2272_ep_पढ़ो(ep, EP_IRQENB);
	net2272_ep_ग_लिखो(ep, EP_IRQENB, पंचांगp);

	पंचांगp = desc->bEndpoपूर्णांकAddress;
	dev_dbg(dev->dev, "enabled %s (ep%d%s-%s) max %04x cfg %02x\n",
		_ep->name, पंचांगp & 0x0f, PIPEसूची(पंचांगp),
		type_string(desc->bmAttributes), max,
		net2272_ep_पढ़ो(ep, EP_CFG));

	spin_unlock_irqrestore(&dev->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम net2272_ep_reset(काष्ठा net2272_ep *ep)
अणु
	u8 पंचांगp;

	ep->desc = शून्य;
	INIT_LIST_HEAD(&ep->queue);

	usb_ep_set_maxpacket_limit(&ep->ep, ~0);
	ep->ep.ops = &net2272_ep_ops;

	/* disable irqs, endpoपूर्णांक */
	net2272_ep_ग_लिखो(ep, EP_IRQENB, 0);

	/* init to our chosen शेषs, notably so that we NAK OUT
	 * packets until the driver queues a पढ़ो.
	 */
	पंचांगp = (1 << NAK_OUT_PACKETS_MODE) | (1 << ALT_NAK_OUT_PACKETS);
	net2272_ep_ग_लिखो(ep, EP_RSPSET, पंचांगp);

	पंचांगp = (1 << INTERRUPT_MODE) | (1 << HIDE_STATUS_PHASE);
	अगर (ep->num != 0)
		पंचांगp |= (1 << ENDPOINT_TOGGLE) | (1 << ENDPOINT_HALT);

	net2272_ep_ग_लिखो(ep, EP_RSPCLR, पंचांगp);

	/* scrub most status bits, and flush any fअगरo state */
	net2272_ep_ग_लिखो(ep, EP_STAT0,
			  (1 << DATA_IN_TOKEN_INTERRUPT)
			| (1 << DATA_OUT_TOKEN_INTERRUPT)
			| (1 << DATA_PACKET_TRANSMITTED_INTERRUPT)
			| (1 << DATA_PACKET_RECEIVED_INTERRUPT)
			| (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT));

	net2272_ep_ग_लिखो(ep, EP_STAT1,
			    (1 << TIMEOUT)
			  | (1 << USB_OUT_ACK_SENT)
			  | (1 << USB_OUT_NAK_SENT)
			  | (1 << USB_IN_ACK_RCVD)
			  | (1 << USB_IN_NAK_SENT)
			  | (1 << USB_STALL_SENT)
			  | (1 << LOCAL_OUT_ZLP)
			  | (1 << BUFFER_FLUSH));

	/* fअगरo size is handled seperately */
पूर्ण

अटल पूर्णांक net2272_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा net2272_ep *ep;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || !ep->desc || _ep->name == ep0name)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->dev->lock, flags);
	net2272_dequeue_all(ep);
	net2272_ep_reset(ep);

	dev_vdbg(ep->dev->dev, "disabled %s\n", _ep->name);

	spin_unlock_irqrestore(&ep->dev->lock, flags);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल काष्ठा usb_request *
net2272_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा net2272_request *req;

	अगर (!_ep)
		वापस शून्य;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम
net2272_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा net2272_request *req;

	अगर (!_ep || !_req)
		वापस;

	req = container_of(_req, काष्ठा net2272_request, req);
	WARN_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

अटल व्योम
net2272_करोne(काष्ठा net2272_ep *ep, काष्ठा net2272_request *req, पूर्णांक status)
अणु
	काष्ठा net2272 *dev;
	अचिन्हित stopped = ep->stopped;

	अगर (ep->num == 0) अणु
		अगर (ep->dev->protocol_stall) अणु
			ep->stopped = 1;
			set_halt(ep);
		पूर्ण
		allow_status(ep);
	पूर्ण

	list_del_init(&req->queue);

	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	dev = ep->dev;
	अगर (use_dma && ep->dma)
		usb_gadget_unmap_request(&dev->gadget, &req->req,
				ep->is_in);

	अगर (status && status != -ESHUTDOWN)
		dev_vdbg(dev->dev, "complete %s req %p stat %d len %u/%u buf %p\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length, req->req.buf);

	/* करोn't modअगरy queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&dev->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&dev->lock);
	ep->stopped = stopped;
पूर्ण

अटल पूर्णांक
net2272_ग_लिखो_packet(काष्ठा net2272_ep *ep, u8 *buf,
	काष्ठा net2272_request *req, अचिन्हित max)
अणु
	u16 __iomem *ep_data = net2272_reg_addr(ep->dev, EP_DATA);
	u16 *bufp;
	अचिन्हित length, count;
	u8 पंचांगp;

	length = min(req->req.length - req->req.actual, max);
	req->req.actual += length;

	dev_vdbg(ep->dev->dev, "write packet %s req %p max %u len %u avail %u\n",
		ep->ep.name, req, max, length,
		(net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8) | net2272_ep_पढ़ो(ep, EP_AVAIL0));

	count = length;
	bufp = (u16 *)buf;

	जबतक (likely(count >= 2)) अणु
		/* no byte-swap required; chip endian set during init */
		ग_लिखोw(*bufp++, ep_data);
		count -= 2;
	पूर्ण
	buf = (u8 *)bufp;

	/* ग_लिखो final byte by placing the NET2272 पूर्णांकo 8-bit mode */
	अगर (unlikely(count)) अणु
		पंचांगp = net2272_पढ़ो(ep->dev, LOCCTL);
		net2272_ग_लिखो(ep->dev, LOCCTL, पंचांगp & ~(1 << DATA_WIDTH));
		ग_लिखोb(*buf, ep_data);
		net2272_ग_लिखो(ep->dev, LOCCTL, पंचांगp);
	पूर्ण
	वापस length;
पूर्ण

/* वापसs: 0: still running, 1: completed, negative: त्रुटि_सं */
अटल पूर्णांक
net2272_ग_लिखो_fअगरo(काष्ठा net2272_ep *ep, काष्ठा net2272_request *req)
अणु
	u8 *buf;
	अचिन्हित count, max;
	पूर्णांक status;

	dev_vdbg(ep->dev->dev, "write_fifo %s actual %d len %d\n",
		ep->ep.name, req->req.actual, req->req.length);

	/*
	 * Keep loading the endpoपूर्णांक until the final packet is loaded,
	 * or the endpoपूर्णांक buffer is full.
	 */
 top:
	/*
	 * Clear पूर्णांकerrupt status
	 *  - Packet Transmitted पूर्णांकerrupt will become set again when the
	 *    host successfully takes another packet
	 */
	net2272_ep_ग_लिखो(ep, EP_STAT0, (1 << DATA_PACKET_TRANSMITTED_INTERRUPT));
	जबतक (!(net2272_ep_पढ़ो(ep, EP_STAT0) & (1 << BUFFER_FULL))) अणु
		buf = req->req.buf + req->req.actual;
		prefetch(buf);

		/* क्रमce pagesel */
		net2272_ep_पढ़ो(ep, EP_STAT0);

		max = (net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8) |
			(net2272_ep_पढ़ो(ep, EP_AVAIL0));

		अगर (max < ep->ep.maxpacket)
			max = (net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8)
				| (net2272_ep_पढ़ो(ep, EP_AVAIL0));

		count = net2272_ग_लिखो_packet(ep, buf, req, max);
		/* see अगर we are करोne */
		अगर (req->req.length == req->req.actual) अणु
			/* validate लघु or zlp packet */
			अगर (count < ep->ep.maxpacket)
				set_fअगरo_bytecount(ep, 0);
			net2272_करोne(ep, req, 0);

			अगर (!list_empty(&ep->queue)) अणु
				req = list_entry(ep->queue.next,
						काष्ठा net2272_request,
						queue);
				status = net2272_kick_dma(ep, req);

				अगर (status < 0)
					अगर ((net2272_ep_पढ़ो(ep, EP_STAT0)
							& (1 << BUFFER_EMPTY)))
						जाओ top;
			पूर्ण
			वापस 1;
		पूर्ण
		net2272_ep_ग_लिखो(ep, EP_STAT0, (1 << DATA_PACKET_TRANSMITTED_INTERRUPT));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
net2272_out_flush(काष्ठा net2272_ep *ep)
अणु
	ASSERT_OUT_NAKING(ep);

	net2272_ep_ग_लिखो(ep, EP_STAT0, (1 << DATA_OUT_TOKEN_INTERRUPT)
			| (1 << DATA_PACKET_RECEIVED_INTERRUPT));
	net2272_ep_ग_लिखो(ep, EP_STAT1, 1 << BUFFER_FLUSH);
पूर्ण

अटल पूर्णांक
net2272_पढ़ो_packet(काष्ठा net2272_ep *ep, u8 *buf,
	काष्ठा net2272_request *req, अचिन्हित avail)
अणु
	u16 __iomem *ep_data = net2272_reg_addr(ep->dev, EP_DATA);
	अचिन्हित is_लघु;
	u16 *bufp;

	req->req.actual += avail;

	dev_vdbg(ep->dev->dev, "read packet %s req %p len %u avail %u\n",
		ep->ep.name, req, avail,
		(net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8) | net2272_ep_पढ़ो(ep, EP_AVAIL0));

	is_लघु = (avail < ep->ep.maxpacket);

	अगर (unlikely(avail == 0)) अणु
		/* हटाओ any zlp from the buffer */
		(व्योम)पढ़ोw(ep_data);
		वापस is_लघु;
	पूर्ण

	/* Ensure we get the final byte */
	अगर (unlikely(avail % 2))
		avail++;
	bufp = (u16 *)buf;

	करो अणु
		*bufp++ = पढ़ोw(ep_data);
		avail -= 2;
	पूर्ण जबतक (avail);

	/*
	 * To aव्योम false endpoपूर्णांक available race condition must पढ़ो
	 * ep stat0 twice in the हाल of a लघु transfer
	 */
	अगर (net2272_ep_पढ़ो(ep, EP_STAT0) & (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT))
		net2272_ep_पढ़ो(ep, EP_STAT0);

	वापस is_लघु;
पूर्ण

अटल पूर्णांक
net2272_पढ़ो_fअगरo(काष्ठा net2272_ep *ep, काष्ठा net2272_request *req)
अणु
	u8 *buf;
	अचिन्हित is_लघु;
	पूर्णांक count;
	पूर्णांक पंचांगp;
	पूर्णांक cleanup = 0;

	dev_vdbg(ep->dev->dev, "read_fifo %s actual %d len %d\n",
		ep->ep.name, req->req.actual, req->req.length);

 top:
	करो अणु
		buf = req->req.buf + req->req.actual;
		prefetchw(buf);

		count = (net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8)
			| net2272_ep_पढ़ो(ep, EP_AVAIL0);

		net2272_ep_ग_लिखो(ep, EP_STAT0,
			(1 << SHORT_PACKET_TRANSFERRED_INTERRUPT) |
			(1 << DATA_PACKET_RECEIVED_INTERRUPT));

		पंचांगp = req->req.length - req->req.actual;

		अगर (count > पंचांगp) अणु
			अगर ((पंचांगp % ep->ep.maxpacket) != 0) अणु
				dev_err(ep->dev->dev,
					"%s out fifo %d bytes, expected %d\n",
					ep->ep.name, count, पंचांगp);
				cleanup = 1;
			पूर्ण
			count = (पंचांगp > 0) ? पंचांगp : 0;
		पूर्ण

		is_लघु = net2272_पढ़ो_packet(ep, buf, req, count);

		/* completion */
		अगर (unlikely(cleanup || is_लघु ||
				req->req.actual == req->req.length)) अणु

			अगर (cleanup) अणु
				net2272_out_flush(ep);
				net2272_करोne(ep, req, -EOVERFLOW);
			पूर्ण अन्यथा
				net2272_करोne(ep, req, 0);

			/* re-initialize endpoपूर्णांक transfer रेजिस्टरs
			 * otherwise they may result in erroneous pre-validation
			 * क्रम subsequent control पढ़ोs
			 */
			अगर (unlikely(ep->num == 0)) अणु
				net2272_ep_ग_लिखो(ep, EP_TRANSFER2, 0);
				net2272_ep_ग_लिखो(ep, EP_TRANSFER1, 0);
				net2272_ep_ग_लिखो(ep, EP_TRANSFER0, 0);
			पूर्ण

			अगर (!list_empty(&ep->queue)) अणु
				पूर्णांक status;

				req = list_entry(ep->queue.next,
					काष्ठा net2272_request, queue);
				status = net2272_kick_dma(ep, req);
				अगर ((status < 0) &&
				    !(net2272_ep_पढ़ो(ep, EP_STAT0) & (1 << BUFFER_EMPTY)))
					जाओ top;
			पूर्ण
			वापस 1;
		पूर्ण
	पूर्ण जबतक (!(net2272_ep_पढ़ो(ep, EP_STAT0) & (1 << BUFFER_EMPTY)));

	वापस 0;
पूर्ण

अटल व्योम
net2272_pio_advance(काष्ठा net2272_ep *ep)
अणु
	काष्ठा net2272_request *req;

	अगर (unlikely(list_empty(&ep->queue)))
		वापस;

	req = list_entry(ep->queue.next, काष्ठा net2272_request, queue);
	(ep->is_in ? net2272_ग_लिखो_fअगरo : net2272_पढ़ो_fअगरo)(ep, req);
पूर्ण

/* वापसs 0 on success, अन्यथा negative त्रुटि_सं */
अटल पूर्णांक
net2272_request_dma(काष्ठा net2272 *dev, अचिन्हित ep, u32 buf,
	अचिन्हित len, अचिन्हित dir)
अणु
	dev_vdbg(dev->dev, "request_dma ep %d buf %08x len %d dir %d\n",
		ep, buf, len, dir);

	/* The NET2272 only supports a single dma channel */
	अगर (dev->dma_busy)
		वापस -EBUSY;
	/*
	 * EP_TRANSFER (used to determine the number of bytes received
	 * in an OUT transfer) is 24 bits wide; करोn't ask क्रम more than that.
	 */
	अगर ((dir == 1) && (len > 0x1000000))
		वापस -EINVAL;

	dev->dma_busy = 1;

	/* initialize platक्रमm's dma */
#अगर_घोषित CONFIG_USB_PCI
	/* NET2272 addr, buffer addr, length, etc. */
	चयन (dev->dev_id) अणु
	हाल PCI_DEVICE_ID_RDK1:
		/* Setup PLX 9054 DMA mode */
		ग_लिखोl((1 << LOCAL_BUS_WIDTH) |
			(1 << TA_READY_INPUT_ENABLE) |
			(0 << LOCAL_BURST_ENABLE) |
			(1 << DONE_INTERRUPT_ENABLE) |
			(1 << LOCAL_ADDRESSING_MODE) |
			(1 << DEMAND_MODE) |
			(1 << DMA_EOT_ENABLE) |
			(1 << FAST_SLOW_TERMINATE_MODE_SELECT) |
			(1 << DMA_CHANNEL_INTERRUPT_SELECT),
			dev->rdk1.plx9054_base_addr + DMAMODE0);

		ग_लिखोl(0x100000, dev->rdk1.plx9054_base_addr + DMALADR0);
		ग_लिखोl(buf, dev->rdk1.plx9054_base_addr + DMAPADR0);
		ग_लिखोl(len, dev->rdk1.plx9054_base_addr + DMASIZ0);
		ग_लिखोl((dir << सूचीECTION_OF_TRANSFER) |
			(1 << INTERRUPT_AFTER_TERMINAL_COUNT),
			dev->rdk1.plx9054_base_addr + DMADPR0);
		ग_लिखोl((1 << LOCAL_DMA_CHANNEL_0_INTERRUPT_ENABLE) |
			पढ़ोl(dev->rdk1.plx9054_base_addr + INTCSR),
			dev->rdk1.plx9054_base_addr + INTCSR);

		अवरोध;
	पूर्ण
#पूर्ण_अगर

	net2272_ग_लिखो(dev, DMAREQ,
		(0 << DMA_BUFFER_VALID) |
		(1 << DMA_REQUEST_ENABLE) |
		(1 << DMA_CONTROL_DACK) |
		(dev->dma_eot_polarity << EOT_POLARITY) |
		(dev->dma_dack_polarity << DACK_POLARITY) |
		(dev->dma_dreq_polarity << DREQ_POLARITY) |
		((ep >> 1) << DMA_ENDPOINT_SELECT));

	(व्योम) net2272_पढ़ो(dev, SCRATCH);

	वापस 0;
पूर्ण

अटल व्योम
net2272_start_dma(काष्ठा net2272 *dev)
अणु
	/* start platक्रमm's dma controller */
#अगर_घोषित CONFIG_USB_PCI
	चयन (dev->dev_id) अणु
	हाल PCI_DEVICE_ID_RDK1:
		ग_लिखोb((1 << CHANNEL_ENABLE) | (1 << CHANNEL_START),
			dev->rdk1.plx9054_base_addr + DMACSR0);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* वापसs 0 on success, अन्यथा negative त्रुटि_सं */
अटल पूर्णांक
net2272_kick_dma(काष्ठा net2272_ep *ep, काष्ठा net2272_request *req)
अणु
	अचिन्हित size;
	u8 पंचांगp;

	अगर (!use_dma || (ep->num < 1) || (ep->num > 2) || !ep->dma)
		वापस -EINVAL;

	/* करोn't use dma क्रम odd-length transfers
	 * otherwise, we'd need to deal with the last byte with pio
	 */
	अगर (req->req.length & 1)
		वापस -EINVAL;

	dev_vdbg(ep->dev->dev, "kick_dma %s req %p dma %08llx\n",
		ep->ep.name, req, (अचिन्हित दीर्घ दीर्घ) req->req.dma);

	net2272_ep_ग_लिखो(ep, EP_RSPSET, 1 << ALT_NAK_OUT_PACKETS);

	/* The NET2272 can only use DMA on one endpoपूर्णांक at a समय */
	अगर (ep->dev->dma_busy)
		वापस -EBUSY;

	/* Make sure we only DMA an even number of bytes (we'll use
	 * pio to complete the transfer)
	 */
	size = req->req.length;
	size &= ~1;

	/* device-to-host transfer */
	अगर (ep->is_in) अणु
		/* initialize platक्रमm's dma controller */
		अगर (net2272_request_dma(ep->dev, ep->num, req->req.dma, size, 0))
			/* unable to obtain DMA channel; वापस error and use pio mode */
			वापस -EBUSY;
		req->req.actual += size;

	/* host-to-device transfer */
	पूर्ण अन्यथा अणु
		पंचांगp = net2272_ep_पढ़ो(ep, EP_STAT0);

		/* initialize platक्रमm's dma controller */
		अगर (net2272_request_dma(ep->dev, ep->num, req->req.dma, size, 1))
			/* unable to obtain DMA channel; वापस error and use pio mode */
			वापस -EBUSY;

		अगर (!(पंचांगp & (1 << BUFFER_EMPTY)))
			ep->not_empty = 1;
		अन्यथा
			ep->not_empty = 0;


		/* allow the endpoपूर्णांक's buffer to fill */
		net2272_ep_ग_लिखो(ep, EP_RSPCLR, 1 << ALT_NAK_OUT_PACKETS);

		/* this transfer completed and data's alपढ़ोy in the fअगरo
		 * वापस error so pio माला_लो used.
		 */
		अगर (पंचांगp & (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT)) अणु

			/* deनिश्चित dreq */
			net2272_ग_लिखो(ep->dev, DMAREQ,
				(0 << DMA_BUFFER_VALID) |
				(0 << DMA_REQUEST_ENABLE) |
				(1 << DMA_CONTROL_DACK) |
				(ep->dev->dma_eot_polarity << EOT_POLARITY) |
				(ep->dev->dma_dack_polarity << DACK_POLARITY) |
				(ep->dev->dma_dreq_polarity << DREQ_POLARITY) |
				((ep->num >> 1) << DMA_ENDPOINT_SELECT));

			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Don't use per-packet पूर्णांकerrupts: use dma पूर्णांकerrupts only */
	net2272_ep_ग_लिखो(ep, EP_IRQENB, 0);

	net2272_start_dma(ep->dev);

	वापस 0;
पूर्ण

अटल व्योम net2272_cancel_dma(काष्ठा net2272 *dev)
अणु
#अगर_घोषित CONFIG_USB_PCI
	चयन (dev->dev_id) अणु
	हाल PCI_DEVICE_ID_RDK1:
		ग_लिखोb(0, dev->rdk1.plx9054_base_addr + DMACSR0);
		ग_लिखोb(1 << CHANNEL_ABORT, dev->rdk1.plx9054_base_addr + DMACSR0);
		जबतक (!(पढ़ोb(dev->rdk1.plx9054_base_addr + DMACSR0) &
		         (1 << CHANNEL_DONE)))
			जारी;	/* रुको क्रम dma to stabalize */

		/* dma पात generates an पूर्णांकerrupt */
		ग_लिखोb(1 << CHANNEL_CLEAR_INTERRUPT,
			dev->rdk1.plx9054_base_addr + DMACSR0);
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	dev->dma_busy = 0;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल पूर्णांक
net2272_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा net2272_request *req;
	काष्ठा net2272_ep *ep;
	काष्ठा net2272 *dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = -1;
	u8 s;

	req = container_of(_req, काष्ठा net2272_request, req);
	अगर (!_req || !_req->complete || !_req->buf
			|| !list_empty(&req->queue))
		वापस -EINVAL;
	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0))
		वापस -EINVAL;
	dev = ep->dev;
	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	/* set up dma mapping in हाल the caller didn't */
	अगर (use_dma && ep->dma) अणु
		status = usb_gadget_map_request(&dev->gadget, _req,
				ep->is_in);
		अगर (status)
			वापस status;
	पूर्ण

	dev_vdbg(dev->dev, "%s queue req %p, len %d buf %p dma %08llx %s\n",
		_ep->name, _req, _req->length, _req->buf,
		(अचिन्हित दीर्घ दीर्घ) _req->dma, _req->zero ? "zero" : "!zero");

	spin_lock_irqsave(&dev->lock, flags);

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	/* kickstart this i/o queue? */
	अगर (list_empty(&ep->queue) && !ep->stopped) अणु
		/* maybe there's no control data, just status ack */
		अगर (ep->num == 0 && _req->length == 0) अणु
			net2272_करोne(ep, req, 0);
			dev_vdbg(dev->dev, "%s status ack\n", ep->ep.name);
			जाओ करोne;
		पूर्ण

		/* Return zlp, करोn't let it block subsequent packets */
		s = net2272_ep_पढ़ो(ep, EP_STAT0);
		अगर (s & (1 << BUFFER_EMPTY)) अणु
			/* Buffer is empty check क्रम a blocking zlp, handle it */
			अगर ((s & (1 << NAK_OUT_PACKETS)) &&
			    net2272_ep_पढ़ो(ep, EP_STAT1) & (1 << LOCAL_OUT_ZLP)) अणु
				dev_dbg(dev->dev, "WARNING: returning ZLP short packet termination!\n");
				/*
				 * Request is going to terminate with a लघु packet ...
				 * hope the client is पढ़ोy क्रम it!
				 */
				status = net2272_पढ़ो_fअगरo(ep, req);
				/* clear लघु packet naking */
				net2272_ep_ग_लिखो(ep, EP_STAT0, (1 << NAK_OUT_PACKETS));
				जाओ करोne;
			पूर्ण
		पूर्ण

		/* try dma first */
		status = net2272_kick_dma(ep, req);

		अगर (status < 0) अणु
			/* dma failed (most likely in use by another endpoपूर्णांक)
			 * fallback to pio
			 */
			status = 0;

			अगर (ep->is_in)
				status = net2272_ग_लिखो_fअगरo(ep, req);
			अन्यथा अणु
				s = net2272_ep_पढ़ो(ep, EP_STAT0);
				अगर ((s & (1 << BUFFER_EMPTY)) == 0)
					status = net2272_पढ़ो_fअगरo(ep, req);
			पूर्ण

			अगर (unlikely(status != 0)) अणु
				अगर (status > 0)
					status = 0;
				req = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (likely(req))
		list_add_tail(&req->queue, &ep->queue);

	अगर (likely(!list_empty(&ep->queue)))
		net2272_ep_ग_लिखो(ep, EP_RSPCLR, 1 << ALT_NAK_OUT_PACKETS);
 करोne:
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/* dequeue ALL requests */
अटल व्योम
net2272_dequeue_all(काष्ठा net2272_ep *ep)
अणु
	काष्ठा net2272_request *req;

	/* called with spinlock held */
	ep->stopped = 1;

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next,
				काष्ठा net2272_request,
				queue);
		net2272_करोne(ep, req, -ESHUTDOWN);
	पूर्ण
पूर्ण

/* dequeue JUST ONE request */
अटल पूर्णांक
net2272_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा net2272_ep *ep;
	काष्ठा net2272_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक stopped;

	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0) || !_req)
		वापस -EINVAL;

	spin_lock_irqsave(&ep->dev->lock, flags);
	stopped = ep->stopped;
	ep->stopped = 1;

	/* make sure it's still queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		ep->stopped = stopped;
		spin_unlock_irqrestore(&ep->dev->lock, flags);
		वापस -EINVAL;
	पूर्ण

	/* queue head may be partially complete */
	अगर (ep->queue.next == &req->queue) अणु
		dev_dbg(ep->dev->dev, "unlink (%s) pio\n", _ep->name);
		net2272_करोne(ep, req, -ECONNRESET);
	पूर्ण
	req = शून्य;
	ep->stopped = stopped;

	spin_unlock_irqrestore(&ep->dev->lock, flags);
	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल पूर्णांक
net2272_set_halt_and_wedge(काष्ठा usb_ep *_ep, पूर्णांक value, पूर्णांक wedged)
अणु
	काष्ठा net2272_ep *ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0))
		वापस -EINVAL;
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;
	अगर (ep->desc /* not ep0 */ && usb_endpoपूर्णांक_xfer_isoc(ep->desc))
		वापस -EINVAL;

	spin_lock_irqsave(&ep->dev->lock, flags);
	अगर (!list_empty(&ep->queue))
		ret = -EAGAIN;
	अन्यथा अगर (ep->is_in && value && net2272_fअगरo_status(_ep) != 0)
		ret = -EAGAIN;
	अन्यथा अणु
		dev_vdbg(ep->dev->dev, "%s %s %s\n", _ep->name,
			value ? "set" : "clear",
			wedged ? "wedge" : "halt");
		/* set/clear */
		अगर (value) अणु
			अगर (ep->num == 0)
				ep->dev->protocol_stall = 1;
			अन्यथा
				set_halt(ep);
			अगर (wedged)
				ep->wedged = 1;
		पूर्ण अन्यथा अणु
			clear_halt(ep);
			ep->wedged = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ep->dev->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक
net2272_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	वापस net2272_set_halt_and_wedge(_ep, value, 0);
पूर्ण

अटल पूर्णांक
net2272_set_wedge(काष्ठा usb_ep *_ep)
अणु
	अगर (!_ep || _ep->name == ep0name)
		वापस -EINVAL;
	वापस net2272_set_halt_and_wedge(_ep, 1, 1);
पूर्ण

अटल पूर्णांक
net2272_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा net2272_ep *ep;
	u16 avail;

	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0))
		वापस -ENODEV;
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	avail = net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8;
	avail |= net2272_ep_पढ़ो(ep, EP_AVAIL0);
	अगर (avail > ep->fअगरo_size)
		वापस -EOVERFLOW;
	अगर (ep->is_in)
		avail = ep->fअगरo_size - avail;
	वापस avail;
पूर्ण

अटल व्योम
net2272_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा net2272_ep *ep;

	ep = container_of(_ep, काष्ठा net2272_ep, ep);
	अगर (!_ep || (!ep->desc && ep->num != 0))
		वापस;
	अगर (!ep->dev->driver || ep->dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस;

	net2272_ep_ग_लिखो(ep, EP_STAT1, 1 << BUFFER_FLUSH);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops net2272_ep_ops = अणु
	.enable        = net2272_enable,
	.disable       = net2272_disable,

	.alloc_request = net2272_alloc_request,
	.मुक्त_request  = net2272_मुक्त_request,

	.queue         = net2272_queue,
	.dequeue       = net2272_dequeue,

	.set_halt      = net2272_set_halt,
	.set_wedge     = net2272_set_wedge,
	.fअगरo_status   = net2272_fअगरo_status,
	.fअगरo_flush    = net2272_fअगरo_flush,
पूर्ण;

/*---------------------------------------------------------------------------*/

अटल पूर्णांक
net2272_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा net2272 *dev;
	अचिन्हित दीर्घ flags;
	u16 ret;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा net2272, gadget);
	spin_lock_irqsave(&dev->lock, flags);

	ret = net2272_पढ़ो(dev, FRAME1) << 8;
	ret |= net2272_पढ़ो(dev, FRAME0);

	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक
net2272_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा net2272 *dev;
	u8 पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (!_gadget)
		वापस 0;
	dev = container_of(_gadget, काष्ठा net2272, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	पंचांगp = net2272_पढ़ो(dev, USBCTL0);
	अगर (पंचांगp & (1 << IO_WAKEUP_ENABLE))
		net2272_ग_लिखो(dev, USBCTL1, (1 << GENERATE_RESUME));

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
net2272_set_selfघातered(काष्ठा usb_gadget *_gadget, पूर्णांक value)
अणु
	अगर (!_gadget)
		वापस -ENODEV;

	_gadget->is_selfघातered = (value != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
net2272_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_on)
अणु
	काष्ठा net2272 *dev;
	u8 पंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा net2272, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	पंचांगp = net2272_पढ़ो(dev, USBCTL0);
	dev->softconnect = (is_on != 0);
	अगर (is_on)
		पंचांगp |= (1 << USB_DETECT_ENABLE);
	अन्यथा
		पंचांगp &= ~(1 << USB_DETECT_ENABLE);
	net2272_ग_लिखो(dev, USBCTL0, पंचांगp);
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक net2272_start(काष्ठा usb_gadget *_gadget,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक net2272_stop(काष्ठा usb_gadget *_gadget);

अटल स्थिर काष्ठा usb_gadget_ops net2272_ops = अणु
	.get_frame	= net2272_get_frame,
	.wakeup		= net2272_wakeup,
	.set_selfघातered = net2272_set_selfघातered,
	.pullup		= net2272_pullup,
	.udc_start	= net2272_start,
	.udc_stop	= net2272_stop,
पूर्ण;

/*---------------------------------------------------------------------------*/

अटल sमाप_प्रकार
रेजिस्टरs_show(काष्ठा device *_dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net2272 *dev;
	अक्षर *next;
	अचिन्हित size, t;
	अचिन्हित दीर्घ flags;
	u8 t1, t2;
	पूर्णांक i;
	स्थिर अक्षर *s;

	dev = dev_get_drvdata(_dev);
	next = buf;
	size = PAGE_SIZE;
	spin_lock_irqsave(&dev->lock, flags);

	/* Main Control Registers */
	t = scnम_लिखो(next, size, "%s version %s,"
		"chiprev %02x, locctl %02x\n"
		"irqenb0 %02x irqenb1 %02x "
		"irqstat0 %02x irqstat1 %02x\n",
		driver_name, driver_vers, dev->chiprev,
		net2272_पढ़ो(dev, LOCCTL),
		net2272_पढ़ो(dev, IRQENB0),
		net2272_पढ़ो(dev, IRQENB1),
		net2272_पढ़ो(dev, IRQSTAT0),
		net2272_पढ़ो(dev, IRQSTAT1));
	size -= t;
	next += t;

	/* DMA */
	t1 = net2272_पढ़ो(dev, DMAREQ);
	t = scnम_लिखो(next, size, "\ndmareq %02x: %s %s%s%s%s\n",
		t1, ep_name[(t1 & 0x01) + 1],
		t1 & (1 << DMA_CONTROL_DACK) ? "dack " : "",
		t1 & (1 << DMA_REQUEST_ENABLE) ? "reqenb " : "",
		t1 & (1 << DMA_REQUEST) ? "req " : "",
		t1 & (1 << DMA_BUFFER_VALID) ? "valid " : "");
	size -= t;
	next += t;

	/* USB Control Registers */
	t1 = net2272_पढ़ो(dev, USBCTL1);
	अगर (t1 & (1 << VBUS_PIN)) अणु
		अगर (t1 & (1 << USB_HIGH_SPEED))
			s = "high speed";
		अन्यथा अगर (dev->gadget.speed == USB_SPEED_UNKNOWN)
			s = "powered";
		अन्यथा
			s = "full speed";
	पूर्ण अन्यथा
		s = "not attached";
	t = scnम_लिखो(next, size,
		"usbctl0 %02x usbctl1 %02x addr 0x%02x (%s)\n",
		net2272_पढ़ो(dev, USBCTL0), t1,
		net2272_पढ़ो(dev, OURADDR), s);
	size -= t;
	next += t;

	/* Endpoपूर्णांक Registers */
	क्रम (i = 0; i < 4; ++i) अणु
		काष्ठा net2272_ep *ep;

		ep = &dev->ep[i];
		अगर (i && !ep->desc)
			जारी;

		t1 = net2272_ep_पढ़ो(ep, EP_CFG);
		t2 = net2272_ep_पढ़ो(ep, EP_RSPSET);
		t = scnम_लिखो(next, size,
			"\n%s\tcfg %02x rsp (%02x) %s%s%s%s%s%s%s%s"
			"irqenb %02x\n",
			ep->ep.name, t1, t2,
			(t2 & (1 << ALT_NAK_OUT_PACKETS)) ? "NAK " : "",
			(t2 & (1 << HIDE_STATUS_PHASE)) ? "hide " : "",
			(t2 & (1 << AUTOVALIDATE)) ? "auto " : "",
			(t2 & (1 << INTERRUPT_MODE)) ? "interrupt " : "",
			(t2 & (1 << CONTROL_STATUS_PHASE_HANDSHAKE)) ? "status " : "",
			(t2 & (1 << NAK_OUT_PACKETS_MODE)) ? "NAKmode " : "",
			(t2 & (1 << ENDPOINT_TOGGLE)) ? "DATA1 " : "DATA0 ",
			(t2 & (1 << ENDPOINT_HALT)) ? "HALT " : "",
			net2272_ep_पढ़ो(ep, EP_IRQENB));
		size -= t;
		next += t;

		t = scnम_लिखो(next, size,
			"\tstat0 %02x stat1 %02x avail %04x "
			"(ep%d%s-%s)%s\n",
			net2272_ep_पढ़ो(ep, EP_STAT0),
			net2272_ep_पढ़ो(ep, EP_STAT1),
			(net2272_ep_पढ़ो(ep, EP_AVAIL1) << 8) | net2272_ep_पढ़ो(ep, EP_AVAIL0),
			t1 & 0x0f,
			ep->is_in ? "in" : "out",
			type_string(t1 >> 5),
			ep->stopped ? "*" : "");
		size -= t;
		next += t;

		t = scnम_लिखो(next, size,
			"\tep_transfer %06x\n",
			((net2272_ep_पढ़ो(ep, EP_TRANSFER2) & 0xff) << 16) |
			((net2272_ep_पढ़ो(ep, EP_TRANSFER1) & 0xff) << 8) |
			((net2272_ep_पढ़ो(ep, EP_TRANSFER0) & 0xff)));
		size -= t;
		next += t;

		t1 = net2272_ep_पढ़ो(ep, EP_BUFF_STATES) & 0x03;
		t2 = (net2272_ep_पढ़ो(ep, EP_BUFF_STATES) >> 2) & 0x03;
		t = scnम_लिखो(next, size,
			"\tbuf-a %s buf-b %s\n",
			buf_state_string(t1),
			buf_state_string(t2));
		size -= t;
		next += t;
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस PAGE_SIZE - size;
पूर्ण
अटल DEVICE_ATTR_RO(रेजिस्टरs);

/*---------------------------------------------------------------------------*/

अटल व्योम
net2272_set_fअगरo_mode(काष्ठा net2272 *dev, पूर्णांक mode)
अणु
	u8 पंचांगp;

	पंचांगp = net2272_पढ़ो(dev, LOCCTL) & 0x3f;
	पंचांगp |= (mode << 6);
	net2272_ग_लिखो(dev, LOCCTL, पंचांगp);

	INIT_LIST_HEAD(&dev->gadget.ep_list);

	/* always ep-a, ep-c ... maybe not ep-b */
	list_add_tail(&dev->ep[1].ep.ep_list, &dev->gadget.ep_list);

	चयन (mode) अणु
	हाल 0:
		list_add_tail(&dev->ep[2].ep.ep_list, &dev->gadget.ep_list);
		dev->ep[1].fअगरo_size = dev->ep[2].fअगरo_size = 512;
		अवरोध;
	हाल 1:
		list_add_tail(&dev->ep[2].ep.ep_list, &dev->gadget.ep_list);
		dev->ep[1].fअगरo_size = 1024;
		dev->ep[2].fअगरo_size = 512;
		अवरोध;
	हाल 2:
		list_add_tail(&dev->ep[2].ep.ep_list, &dev->gadget.ep_list);
		dev->ep[1].fअगरo_size = dev->ep[2].fअगरo_size = 1024;
		अवरोध;
	हाल 3:
		dev->ep[1].fअगरo_size = 1024;
		अवरोध;
	पूर्ण

	/* ep-c is always 2 512 byte buffers */
	list_add_tail(&dev->ep[3].ep.ep_list, &dev->gadget.ep_list);
	dev->ep[3].fअगरo_size = 512;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल व्योम
net2272_usb_reset(काष्ठा net2272 *dev)
अणु
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	net2272_cancel_dma(dev);

	net2272_ग_लिखो(dev, IRQENB0, 0);
	net2272_ग_लिखो(dev, IRQENB1, 0);

	/* clear irq state */
	net2272_ग_लिखो(dev, IRQSTAT0, 0xff);
	net2272_ग_लिखो(dev, IRQSTAT1, ~(1 << SUSPEND_REQUEST_INTERRUPT));

	net2272_ग_लिखो(dev, DMAREQ,
		(0 << DMA_BUFFER_VALID) |
		(0 << DMA_REQUEST_ENABLE) |
		(1 << DMA_CONTROL_DACK) |
		(dev->dma_eot_polarity << EOT_POLARITY) |
		(dev->dma_dack_polarity << DACK_POLARITY) |
		(dev->dma_dreq_polarity << DREQ_POLARITY) |
		((dma_ep >> 1) << DMA_ENDPOINT_SELECT));

	net2272_cancel_dma(dev);
	net2272_set_fअगरo_mode(dev, (fअगरo_mode <= 3) ? fअगरo_mode : 0);

	/* Set the NET2272 ep fअगरo data width to 16-bit mode and क्रम correct byte swapping
	 * note that the higher level gadget drivers are expected to convert data to little endian.
	 * Enable byte swap क्रम your local bus/cpu अगर needed by setting BYTE_SWAP in LOCCTL here
	 */
	net2272_ग_लिखो(dev, LOCCTL, net2272_पढ़ो(dev, LOCCTL) | (1 << DATA_WIDTH));
	net2272_ग_लिखो(dev, LOCCTL1, (dma_mode << DMA_MODE));
पूर्ण

अटल व्योम
net2272_usb_reinit(काष्ठा net2272 *dev)
अणु
	पूर्णांक i;

	/* basic endpoपूर्णांक init */
	क्रम (i = 0; i < 4; ++i) अणु
		काष्ठा net2272_ep *ep = &dev->ep[i];

		ep->ep.name = ep_name[i];
		ep->dev = dev;
		ep->num = i;
		ep->not_empty = 0;

		अगर (use_dma && ep->num == dma_ep)
			ep->dma = 1;

		अगर (i > 0 && i <= 3)
			ep->fअगरo_size = 512;
		अन्यथा
			ep->fअगरo_size = 64;
		net2272_ep_reset(ep);

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
	usb_ep_set_maxpacket_limit(&dev->ep[0].ep, 64);

	dev->gadget.ep0 = &dev->ep[0].ep;
	dev->ep[0].stopped = 0;
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);
पूर्ण

अटल व्योम
net2272_ep0_start(काष्ठा net2272 *dev)
अणु
	काष्ठा net2272_ep *ep0 = &dev->ep[0];

	net2272_ep_ग_लिखो(ep0, EP_RSPSET,
		(1 << NAK_OUT_PACKETS_MODE) |
		(1 << ALT_NAK_OUT_PACKETS));
	net2272_ep_ग_लिखो(ep0, EP_RSPCLR,
		(1 << HIDE_STATUS_PHASE) |
		(1 << CONTROL_STATUS_PHASE_HANDSHAKE));
	net2272_ग_लिखो(dev, USBCTL0,
		(dev->softconnect << USB_DETECT_ENABLE) |
		(1 << USB_ROOT_PORT_WAKEUP_ENABLE) |
		(1 << IO_WAKEUP_ENABLE));
	net2272_ग_लिखो(dev, IRQENB0,
		(1 << SETUP_PACKET_INTERRUPT_ENABLE) |
		(1 << ENDPOINT_0_INTERRUPT_ENABLE) |
		(1 << DMA_DONE_INTERRUPT_ENABLE));
	net2272_ग_लिखो(dev, IRQENB1,
		(1 << VBUS_INTERRUPT_ENABLE) |
		(1 << ROOT_PORT_RESET_INTERRUPT_ENABLE) |
		(1 << SUSPEND_REQUEST_CHANGE_INTERRUPT_ENABLE));
पूर्ण

/* when a driver is successfully रेजिस्टरed, it will receive
 * control requests including set_configuration(), which enables
 * non-control requests.  then usb traffic follows until a
 * disconnect is reported.  then a host may connect again, or
 * the driver might get unbound.
 */
अटल पूर्णांक net2272_start(काष्ठा usb_gadget *_gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा net2272 *dev;
	अचिन्हित i;

	अगर (!driver || !driver->setup ||
	    driver->max_speed != USB_SPEED_HIGH)
		वापस -EINVAL;

	dev = container_of(_gadget, काष्ठा net2272, gadget);

	क्रम (i = 0; i < 4; ++i)
		dev->ep[i].irqs = 0;
	/* hook up the driver ... */
	dev->softconnect = 1;
	driver->driver.bus = शून्य;
	dev->driver = driver;

	/* ... then enable host detection and ep0; and we're पढ़ोy
	 * क्रम set_configuration as well as eventual disconnect.
	 */
	net2272_ep0_start(dev);

	वापस 0;
पूर्ण

अटल व्योम
stop_activity(काष्ठा net2272 *dev, काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक i;

	/* करोn't disconnect if it's not connected */
	अगर (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;

	/* stop hardware; prevent new request submissions;
	 * and समाप्त any outstanding requests.
	 */
	net2272_usb_reset(dev);
	क्रम (i = 0; i < 4; ++i)
		net2272_dequeue_all(&dev->ep[i]);

	/* report disconnect; the driver is alपढ़ोy quiesced */
	अगर (driver) अणु
		spin_unlock(&dev->lock);
		driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);
	पूर्ण

	net2272_usb_reinit(dev);
पूर्ण

अटल पूर्णांक net2272_stop(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा net2272 *dev;
	अचिन्हित दीर्घ flags;

	dev = container_of(_gadget, काष्ठा net2272, gadget);

	spin_lock_irqsave(&dev->lock, flags);
	stop_activity(dev, शून्य);
	spin_unlock_irqrestore(&dev->lock, flags);

	dev->driver = शून्य;

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/
/* handle ep-a/ep-b dma completions */
अटल व्योम
net2272_handle_dma(काष्ठा net2272_ep *ep)
अणु
	काष्ठा net2272_request *req;
	अचिन्हित len;
	पूर्णांक status;

	अगर (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next,
				काष्ठा net2272_request, queue);
	अन्यथा
		req = शून्य;

	dev_vdbg(ep->dev->dev, "handle_dma %s req %p\n", ep->ep.name, req);

	/* Ensure DREQ is de-निश्चितed */
	net2272_ग_लिखो(ep->dev, DMAREQ,
		(0 << DMA_BUFFER_VALID)
	      | (0 << DMA_REQUEST_ENABLE)
	      | (1 << DMA_CONTROL_DACK)
	      | (ep->dev->dma_eot_polarity << EOT_POLARITY)
	      | (ep->dev->dma_dack_polarity << DACK_POLARITY)
	      | (ep->dev->dma_dreq_polarity << DREQ_POLARITY)
	      | (ep->dma << DMA_ENDPOINT_SELECT));

	ep->dev->dma_busy = 0;

	net2272_ep_ग_लिखो(ep, EP_IRQENB,
		  (1 << DATA_PACKET_RECEIVED_INTERRUPT_ENABLE)
		| (1 << DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE)
		| net2272_ep_पढ़ो(ep, EP_IRQENB));

	/* device-to-host transfer completed */
	अगर (ep->is_in) अणु
		/* validate a लघु packet or zlp अगर necessary */
		अगर ((req->req.length % ep->ep.maxpacket != 0) ||
				req->req.zero)
			set_fअगरo_bytecount(ep, 0);

		net2272_करोne(ep, req, 0);
		अगर (!list_empty(&ep->queue)) अणु
			req = list_entry(ep->queue.next,
					काष्ठा net2272_request, queue);
			status = net2272_kick_dma(ep, req);
			अगर (status < 0)
				net2272_pio_advance(ep);
		पूर्ण

	/* host-to-device transfer completed */
	पूर्ण अन्यथा अणु
		/* terminated with a लघु packet? */
		अगर (net2272_पढ़ो(ep->dev, IRQSTAT0) &
				(1 << DMA_DONE_INTERRUPT)) अणु
			/* पात प्रणाली dma */
			net2272_cancel_dma(ep->dev);
		पूर्ण

		/* EP_TRANSFER will contain the number of bytes
		 * actually received.
		 * NOTE: There is no overflow detection on EP_TRANSFER:
		 * We can't deal with transfers larger than 2^24 bytes!
		 */
		len = (net2272_ep_पढ़ो(ep, EP_TRANSFER2) << 16)
			| (net2272_ep_पढ़ो(ep, EP_TRANSFER1) << 8)
			| (net2272_ep_पढ़ो(ep, EP_TRANSFER0));

		अगर (ep->not_empty)
			len += 4;

		req->req.actual += len;

		/* get any reमुख्यing data */
		net2272_pio_advance(ep);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------------*/

अटल व्योम
net2272_handle_ep(काष्ठा net2272_ep *ep)
अणु
	काष्ठा net2272_request *req;
	u8 stat0, stat1;

	अगर (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next,
			काष्ठा net2272_request, queue);
	अन्यथा
		req = शून्य;

	/* ack all, and handle what we care about */
	stat0 = net2272_ep_पढ़ो(ep, EP_STAT0);
	stat1 = net2272_ep_पढ़ो(ep, EP_STAT1);
	ep->irqs++;

	dev_vdbg(ep->dev->dev, "%s ack ep_stat0 %02x, ep_stat1 %02x, req %p\n",
		ep->ep.name, stat0, stat1, req ? &req->req : शून्य);

	net2272_ep_ग_लिखो(ep, EP_STAT0, stat0 &
		~((1 << NAK_OUT_PACKETS)
		| (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT)));
	net2272_ep_ग_लिखो(ep, EP_STAT1, stat1);

	/* data packet(s) received (in the fअगरo, OUT)
	 * direction must be validated, otherwise control पढ़ो status phase
	 * could be पूर्णांकerpreted as a valid packet
	 */
	अगर (!ep->is_in && (stat0 & (1 << DATA_PACKET_RECEIVED_INTERRUPT)))
		net2272_pio_advance(ep);
	/* data packet(s) transmitted (IN) */
	अन्यथा अगर (stat0 & (1 << DATA_PACKET_TRANSMITTED_INTERRUPT))
		net2272_pio_advance(ep);
पूर्ण

अटल काष्ठा net2272_ep *
net2272_get_ep_by_addr(काष्ठा net2272 *dev, u16 wIndex)
अणु
	काष्ठा net2272_ep *ep;

	अगर ((wIndex & USB_ENDPOINT_NUMBER_MASK) == 0)
		वापस &dev->ep[0];

	list_क्रम_each_entry(ep, &dev->gadget.ep_list, ep.ep_list) अणु
		u8 bEndpoपूर्णांकAddress;

		अगर (!ep->desc)
			जारी;
		bEndpoपूर्णांकAddress = ep->desc->bEndpoपूर्णांकAddress;
		अगर ((wIndex ^ bEndpoपूर्णांकAddress) & USB_सूची_IN)
			जारी;
		अगर ((wIndex & 0x0f) == (bEndpoपूर्णांकAddress & 0x0f))
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * USB Test Packet:
 * JKJKJKJK * 9
 * JJKKJJKK * 8
 * JJJJKKKK * 8
 * JJJJJJJKKKKKKK * 8
 * JJJJJJJK * 8
 * अणुJKKKKKKK * 10पूर्ण, JK
 */
अटल स्थिर u8 net2272_test_packet[] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
	0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD,
	0xFC, 0x7E, 0xBF, 0xDF, 0xEF, 0xF7, 0xFD, 0x7E
पूर्ण;

अटल व्योम
net2272_set_test_mode(काष्ठा net2272 *dev, पूर्णांक mode)
अणु
	पूर्णांक i;

	/* Disable all net2272 पूर्णांकerrupts:
	 * Nothing but a घातer cycle should stop the test.
	 */
	net2272_ग_लिखो(dev, IRQENB0, 0x00);
	net2272_ग_लिखो(dev, IRQENB1, 0x00);

	/* Force tranceiver to high-speed */
	net2272_ग_लिखो(dev, XCVRDIAG, 1 << FORCE_HIGH_SPEED);

	net2272_ग_लिखो(dev, PAGESEL, 0);
	net2272_ग_लिखो(dev, EP_STAT0, 1 << DATA_PACKET_TRANSMITTED_INTERRUPT);
	net2272_ग_लिखो(dev, EP_RSPCLR,
			  (1 << CONTROL_STATUS_PHASE_HANDSHAKE)
			| (1 << HIDE_STATUS_PHASE));
	net2272_ग_लिखो(dev, EP_CFG, 1 << ENDPOINT_सूचीECTION);
	net2272_ग_लिखो(dev, EP_STAT1, 1 << BUFFER_FLUSH);

	/* रुको क्रम status phase to complete */
	जबतक (!(net2272_पढ़ो(dev, EP_STAT0) &
				(1 << DATA_PACKET_TRANSMITTED_INTERRUPT)))
		;

	/* Enable test mode */
	net2272_ग_लिखो(dev, USBTEST, mode);

	/* load test packet */
	अगर (mode == USB_TEST_PACKET) अणु
		/* चयन to 8 bit mode */
		net2272_ग_लिखो(dev, LOCCTL, net2272_पढ़ो(dev, LOCCTL) &
				~(1 << DATA_WIDTH));

		क्रम (i = 0; i < माप(net2272_test_packet); ++i)
			net2272_ग_लिखो(dev, EP_DATA, net2272_test_packet[i]);

		/* Validate test packet */
		net2272_ग_लिखो(dev, EP_TRANSFER0, 0);
	पूर्ण
पूर्ण

अटल व्योम
net2272_handle_stat0_irqs(काष्ठा net2272 *dev, u8 stat)
अणु
	काष्ठा net2272_ep *ep;
	u8 num, scratch;

	/* starting a control request? */
	अगर (unlikely(stat & (1 << SETUP_PACKET_INTERRUPT))) अणु
		जोड़ अणु
			u8 raw[8];
			काष्ठा usb_ctrlrequest	r;
		पूर्ण u;
		पूर्णांक पंचांगp = 0;
		काष्ठा net2272_request *req;

		अगर (dev->gadget.speed == USB_SPEED_UNKNOWN) अणु
			अगर (net2272_पढ़ो(dev, USBCTL1) & (1 << USB_HIGH_SPEED))
				dev->gadget.speed = USB_SPEED_HIGH;
			अन्यथा
				dev->gadget.speed = USB_SPEED_FULL;
			dev_dbg(dev->dev, "%s\n",
				usb_speed_string(dev->gadget.speed));
		पूर्ण

		ep = &dev->ep[0];
		ep->irqs++;

		/* make sure any leftover पूर्णांकerrupt state is cleared */
		stat &= ~(1 << ENDPOINT_0_INTERRUPT);
		जबतक (!list_empty(&ep->queue)) अणु
			req = list_entry(ep->queue.next,
				काष्ठा net2272_request, queue);
			net2272_करोne(ep, req,
				(req->req.actual == req->req.length) ? 0 : -EPROTO);
		पूर्ण
		ep->stopped = 0;
		dev->protocol_stall = 0;
		net2272_ep_ग_लिखो(ep, EP_STAT0,
			    (1 << DATA_IN_TOKEN_INTERRUPT)
			  | (1 << DATA_OUT_TOKEN_INTERRUPT)
			  | (1 << DATA_PACKET_TRANSMITTED_INTERRUPT)
			  | (1 << DATA_PACKET_RECEIVED_INTERRUPT)
			  | (1 << SHORT_PACKET_TRANSFERRED_INTERRUPT));
		net2272_ep_ग_लिखो(ep, EP_STAT1,
			    (1 << TIMEOUT)
			  | (1 << USB_OUT_ACK_SENT)
			  | (1 << USB_OUT_NAK_SENT)
			  | (1 << USB_IN_ACK_RCVD)
			  | (1 << USB_IN_NAK_SENT)
			  | (1 << USB_STALL_SENT)
			  | (1 << LOCAL_OUT_ZLP));

		/*
		 * Ensure Control Read pre-validation setting is beyond maximum size
		 *  - Control Writes can leave non-zero values in EP_TRANSFER. If
		 *    an EP0 transfer following the Control Write is a Control Read,
		 *    the NET2272 sees the non-zero EP_TRANSFER as an unexpected
		 *    pre-validation count.
		 *  - Setting EP_TRANSFER beyond the maximum EP0 transfer size ensures
		 *    the pre-validation count cannot cause an unexpected validatation
		 */
		net2272_ग_लिखो(dev, PAGESEL, 0);
		net2272_ग_लिखो(dev, EP_TRANSFER2, 0xff);
		net2272_ग_लिखो(dev, EP_TRANSFER1, 0xff);
		net2272_ग_लिखो(dev, EP_TRANSFER0, 0xff);

		u.raw[0] = net2272_पढ़ो(dev, SETUP0);
		u.raw[1] = net2272_पढ़ो(dev, SETUP1);
		u.raw[2] = net2272_पढ़ो(dev, SETUP2);
		u.raw[3] = net2272_पढ़ो(dev, SETUP3);
		u.raw[4] = net2272_पढ़ो(dev, SETUP4);
		u.raw[5] = net2272_पढ़ो(dev, SETUP5);
		u.raw[6] = net2272_पढ़ो(dev, SETUP6);
		u.raw[7] = net2272_पढ़ो(dev, SETUP7);
		/*
		 * If you have a big endian cpu make sure le16_to_cpus
		 * perक्रमms the proper byte swapping here...
		 */
		le16_to_cpus(&u.r.wValue);
		le16_to_cpus(&u.r.wIndex);
		le16_to_cpus(&u.r.wLength);

		/* ack the irq */
		net2272_ग_लिखो(dev, IRQSTAT0, 1 << SETUP_PACKET_INTERRUPT);
		stat ^= (1 << SETUP_PACKET_INTERRUPT);

		/* watch control traffic at the token level, and क्रमce
		 * synchronization beक्रमe letting the status phase happen.
		 */
		ep->is_in = (u.r.bRequestType & USB_सूची_IN) != 0;
		अगर (ep->is_in) अणु
			scratch = (1 << DATA_PACKET_TRANSMITTED_INTERRUPT_ENABLE)
				| (1 << DATA_OUT_TOKEN_INTERRUPT_ENABLE)
				| (1 << DATA_IN_TOKEN_INTERRUPT_ENABLE);
			stop_out_naking(ep);
		पूर्ण अन्यथा
			scratch = (1 << DATA_PACKET_RECEIVED_INTERRUPT_ENABLE)
				| (1 << DATA_OUT_TOKEN_INTERRUPT_ENABLE)
				| (1 << DATA_IN_TOKEN_INTERRUPT_ENABLE);
		net2272_ep_ग_लिखो(ep, EP_IRQENB, scratch);

		अगर ((u.r.bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
			जाओ delegate;
		चयन (u.r.bRequest) अणु
		हाल USB_REQ_GET_STATUS: अणु
			काष्ठा net2272_ep *e;
			u16 status = 0;

			चयन (u.r.bRequestType & USB_RECIP_MASK) अणु
			हाल USB_RECIP_ENDPOINT:
				e = net2272_get_ep_by_addr(dev, u.r.wIndex);
				अगर (!e || u.r.wLength > 2)
					जाओ करो_stall;
				अगर (net2272_ep_पढ़ो(e, EP_RSPSET) & (1 << ENDPOINT_HALT))
					status = cpu_to_le16(1);
				अन्यथा
					status = cpu_to_le16(0);

				/* करोn't bother with a request object! */
				net2272_ep_ग_लिखो(&dev->ep[0], EP_IRQENB, 0);
				ग_लिखोw(status, net2272_reg_addr(dev, EP_DATA));
				set_fअगरo_bytecount(&dev->ep[0], 0);
				allow_status(ep);
				dev_vdbg(dev->dev, "%s stat %02x\n",
					ep->ep.name, status);
				जाओ next_endpoपूर्णांकs;
			हाल USB_RECIP_DEVICE:
				अगर (u.r.wLength > 2)
					जाओ करो_stall;
				अगर (dev->gadget.is_selfघातered)
					status = (1 << USB_DEVICE_SELF_POWERED);

				/* करोn't bother with a request object! */
				net2272_ep_ग_लिखो(&dev->ep[0], EP_IRQENB, 0);
				ग_लिखोw(status, net2272_reg_addr(dev, EP_DATA));
				set_fअगरo_bytecount(&dev->ep[0], 0);
				allow_status(ep);
				dev_vdbg(dev->dev, "device stat %02x\n", status);
				जाओ next_endpoपूर्णांकs;
			हाल USB_RECIP_INTERFACE:
				अगर (u.r.wLength > 2)
					जाओ करो_stall;

				/* करोn't bother with a request object! */
				net2272_ep_ग_लिखो(&dev->ep[0], EP_IRQENB, 0);
				ग_लिखोw(status, net2272_reg_addr(dev, EP_DATA));
				set_fअगरo_bytecount(&dev->ep[0], 0);
				allow_status(ep);
				dev_vdbg(dev->dev, "interface status %02x\n", status);
				जाओ next_endpoपूर्णांकs;
			पूर्ण

			अवरोध;
		पूर्ण
		हाल USB_REQ_CLEAR_FEATURE: अणु
			काष्ठा net2272_ep *e;

			अगर (u.r.bRequestType != USB_RECIP_ENDPOINT)
				जाओ delegate;
			अगर (u.r.wValue != USB_ENDPOINT_HALT ||
			    u.r.wLength != 0)
				जाओ करो_stall;
			e = net2272_get_ep_by_addr(dev, u.r.wIndex);
			अगर (!e)
				जाओ करो_stall;
			अगर (e->wedged) अणु
				dev_vdbg(dev->dev, "%s wedged, halt not cleared\n",
					ep->ep.name);
			पूर्ण अन्यथा अणु
				dev_vdbg(dev->dev, "%s clear halt\n", ep->ep.name);
				clear_halt(e);
			पूर्ण
			allow_status(ep);
			जाओ next_endpoपूर्णांकs;
		पूर्ण
		हाल USB_REQ_SET_FEATURE: अणु
			काष्ठा net2272_ep *e;

			अगर (u.r.bRequestType == USB_RECIP_DEVICE) अणु
				अगर (u.r.wIndex != NORMAL_OPERATION)
					net2272_set_test_mode(dev, (u.r.wIndex >> 8));
				allow_status(ep);
				dev_vdbg(dev->dev, "test mode: %d\n", u.r.wIndex);
				जाओ next_endpoपूर्णांकs;
			पूर्ण अन्यथा अगर (u.r.bRequestType != USB_RECIP_ENDPOINT)
				जाओ delegate;
			अगर (u.r.wValue != USB_ENDPOINT_HALT ||
			    u.r.wLength != 0)
				जाओ करो_stall;
			e = net2272_get_ep_by_addr(dev, u.r.wIndex);
			अगर (!e)
				जाओ करो_stall;
			set_halt(e);
			allow_status(ep);
			dev_vdbg(dev->dev, "%s set halt\n", ep->ep.name);
			जाओ next_endpoपूर्णांकs;
		पूर्ण
		हाल USB_REQ_SET_ADDRESS: अणु
			net2272_ग_लिखो(dev, OURADDR, u.r.wValue & 0xff);
			allow_status(ep);
			अवरोध;
		पूर्ण
		शेष:
 delegate:
			dev_vdbg(dev->dev, "setup %02x.%02x v%04x i%04x "
				"ep_cfg %08x\n",
				u.r.bRequestType, u.r.bRequest,
				u.r.wValue, u.r.wIndex,
				net2272_ep_पढ़ो(ep, EP_CFG));
			spin_unlock(&dev->lock);
			पंचांगp = dev->driver->setup(&dev->gadget, &u.r);
			spin_lock(&dev->lock);
		पूर्ण

		/* stall ep0 on error */
		अगर (पंचांगp < 0) अणु
 करो_stall:
			dev_vdbg(dev->dev, "req %02x.%02x protocol STALL; stat %d\n",
				u.r.bRequestType, u.r.bRequest, पंचांगp);
			dev->protocol_stall = 1;
		पूर्ण
	/* endpoपूर्णांक dma irq? */
	पूर्ण अन्यथा अगर (stat & (1 << DMA_DONE_INTERRUPT)) अणु
		net2272_cancel_dma(dev);
		net2272_ग_लिखो(dev, IRQSTAT0, 1 << DMA_DONE_INTERRUPT);
		stat &= ~(1 << DMA_DONE_INTERRUPT);
		num = (net2272_पढ़ो(dev, DMAREQ) & (1 << DMA_ENDPOINT_SELECT))
			? 2 : 1;

		ep = &dev->ep[num];
		net2272_handle_dma(ep);
	पूर्ण

 next_endpoपूर्णांकs:
	/* endpoपूर्णांक data irq? */
	scratch = stat & 0x0f;
	stat &= ~0x0f;
	क्रम (num = 0; scratch; num++) अणु
		u8 t;

		/* करोes this endpoपूर्णांक's FIFO and queue need tending? */
		t = 1 << num;
		अगर ((scratch & t) == 0)
			जारी;
		scratch ^= t;

		ep = &dev->ep[num];
		net2272_handle_ep(ep);
	पूर्ण

	/* some पूर्णांकerrupts we can just ignore */
	stat &= ~(1 << SOF_INTERRUPT);

	अगर (stat)
		dev_dbg(dev->dev, "unhandled irqstat0 %02x\n", stat);
पूर्ण

अटल व्योम
net2272_handle_stat1_irqs(काष्ठा net2272 *dev, u8 stat)
अणु
	u8 पंचांगp, mask;

	/* after disconnect there's nothing अन्यथा to करो! */
	पंचांगp = (1 << VBUS_INTERRUPT) | (1 << ROOT_PORT_RESET_INTERRUPT);
	mask = (1 << USB_HIGH_SPEED) | (1 << USB_FULL_SPEED);

	अगर (stat & पंचांगp) अणु
		bool	reset = false;
		bool	disconnect = false;

		/*
		 * Ignore disconnects and resets अगर the speed hasn't been set.
		 * VBUS can bounce and there's always an initial reset.
		 */
		net2272_ग_लिखो(dev, IRQSTAT1, पंचांगp);
		अगर (dev->gadget.speed != USB_SPEED_UNKNOWN) अणु
			अगर ((stat & (1 << VBUS_INTERRUPT)) &&
					(net2272_पढ़ो(dev, USBCTL1) &
						(1 << VBUS_PIN)) == 0) अणु
				disconnect = true;
				dev_dbg(dev->dev, "disconnect %s\n",
					dev->driver->driver.name);
			पूर्ण अन्यथा अगर ((stat & (1 << ROOT_PORT_RESET_INTERRUPT)) &&
					(net2272_पढ़ो(dev, USBCTL1) & mask)
						== 0) अणु
				reset = true;
				dev_dbg(dev->dev, "reset %s\n",
					dev->driver->driver.name);
			पूर्ण

			अगर (disconnect || reset) अणु
				stop_activity(dev, dev->driver);
				net2272_ep0_start(dev);
				spin_unlock(&dev->lock);
				अगर (reset)
					usb_gadget_udc_reset
						(&dev->gadget, dev->driver);
				अन्यथा
					(dev->driver->disconnect)
						(&dev->gadget);
				spin_lock(&dev->lock);
				वापस;
			पूर्ण
		पूर्ण
		stat &= ~पंचांगp;

		अगर (!stat)
			वापस;
	पूर्ण

	पंचांगp = (1 << SUSPEND_REQUEST_CHANGE_INTERRUPT);
	अगर (stat & पंचांगp) अणु
		net2272_ग_लिखो(dev, IRQSTAT1, पंचांगp);
		अगर (stat & (1 << SUSPEND_REQUEST_INTERRUPT)) अणु
			अगर (dev->driver->suspend)
				dev->driver->suspend(&dev->gadget);
			अगर (!enable_suspend) अणु
				stat &= ~(1 << SUSPEND_REQUEST_INTERRUPT);
				dev_dbg(dev->dev, "Suspend disabled, ignoring\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (dev->driver->resume)
				dev->driver->resume(&dev->gadget);
		पूर्ण
		stat &= ~पंचांगp;
	पूर्ण

	/* clear any other status/irqs */
	अगर (stat)
		net2272_ग_लिखो(dev, IRQSTAT1, stat);

	/* some status we can just ignore */
	stat &= ~((1 << CONTROL_STATUS_INTERRUPT)
			| (1 << SUSPEND_REQUEST_INTERRUPT)
			| (1 << RESUME_INTERRUPT));
	अगर (!stat)
		वापस;
	अन्यथा
		dev_dbg(dev->dev, "unhandled irqstat1 %02x\n", stat);
पूर्ण

अटल irqवापस_t net2272_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा net2272 *dev = _dev;
#अगर defined(PLX_PCI_RDK) || defined(PLX_PCI_RDK2)
	u32 पूर्णांकcsr;
#पूर्ण_अगर
#अगर defined(PLX_PCI_RDK)
	u8 dmareq;
#पूर्ण_अगर
	spin_lock(&dev->lock);
#अगर defined(PLX_PCI_RDK)
	पूर्णांकcsr = पढ़ोl(dev->rdk1.plx9054_base_addr + INTCSR);

	अगर ((पूर्णांकcsr & LOCAL_INTERRUPT_TEST) == LOCAL_INTERRUPT_TEST) अणु
		ग_लिखोl(पूर्णांकcsr & ~(1 << PCI_INTERRUPT_ENABLE),
				dev->rdk1.plx9054_base_addr + INTCSR);
		net2272_handle_stat1_irqs(dev, net2272_पढ़ो(dev, IRQSTAT1));
		net2272_handle_stat0_irqs(dev, net2272_पढ़ो(dev, IRQSTAT0));
		पूर्णांकcsr = पढ़ोl(dev->rdk1.plx9054_base_addr + INTCSR);
		ग_लिखोl(पूर्णांकcsr | (1 << PCI_INTERRUPT_ENABLE),
			dev->rdk1.plx9054_base_addr + INTCSR);
	पूर्ण
	अगर ((पूर्णांकcsr & DMA_CHANNEL_0_TEST) == DMA_CHANNEL_0_TEST) अणु
		ग_लिखोb((1 << CHANNEL_CLEAR_INTERRUPT | (0 << CHANNEL_ENABLE)),
				dev->rdk1.plx9054_base_addr + DMACSR0);

		dmareq = net2272_पढ़ो(dev, DMAREQ);
		अगर (dmareq & 0x01)
			net2272_handle_dma(&dev->ep[2]);
		अन्यथा
			net2272_handle_dma(&dev->ep[1]);
	पूर्ण
#पूर्ण_अगर
#अगर defined(PLX_PCI_RDK2)
	/* see अगर PCI पूर्णांक क्रम us by checking irqstat */
	पूर्णांकcsr = पढ़ोl(dev->rdk2.fpga_base_addr + RDK2_IRQSTAT);
	अगर (!(पूर्णांकcsr & (1 << NET2272_PCI_IRQ))) अणु
		spin_unlock(&dev->lock);
		वापस IRQ_NONE;
	पूर्ण
	/* check dma पूर्णांकerrupts */
#पूर्ण_अगर
	/* Platक्रमm/devcice पूर्णांकerrupt handler */
#अगर !defined(PLX_PCI_RDK)
	net2272_handle_stat1_irqs(dev, net2272_पढ़ो(dev, IRQSTAT1));
	net2272_handle_stat0_irqs(dev, net2272_पढ़ो(dev, IRQSTAT0));
#पूर्ण_अगर
	spin_unlock(&dev->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक net2272_present(काष्ठा net2272 *dev)
अणु
	/*
	 * Quick test to see अगर CPU can communicate properly with the NET2272.
	 * Verअगरies connection using ग_लिखोs and पढ़ोs to ग_लिखो/पढ़ो and
	 * पढ़ो-only रेजिस्टरs.
	 *
	 * This routine is strongly recommended especially during early bring-up
	 * of new hardware, however क्रम designs that करो not apply Power On System
	 * Tests (POST) it may discarded (or perhaps minimized).
	 */
	अचिन्हित पूर्णांक ii;
	u8 val, refval;

	/* Verअगरy NET2272 ग_लिखो/पढ़ो SCRATCH रेजिस्टर can ग_लिखो and पढ़ो */
	refval = net2272_पढ़ो(dev, SCRATCH);
	क्रम (ii = 0; ii < 0x100; ii += 7) अणु
		net2272_ग_लिखो(dev, SCRATCH, ii);
		val = net2272_पढ़ो(dev, SCRATCH);
		अगर (val != ii) अणु
			dev_dbg(dev->dev,
				"%s: write/read SCRATCH register test failed: "
				"wrote:0x%2.2x, read:0x%2.2x\n",
				__func__, ii, val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* To be nice, we ग_लिखो the original SCRATCH value back: */
	net2272_ग_लिखो(dev, SCRATCH, refval);

	/* Verअगरy NET2272 CHIPREV रेजिस्टर is पढ़ो-only: */
	refval = net2272_पढ़ो(dev, CHIPREV_2272);
	क्रम (ii = 0; ii < 0x100; ii += 7) अणु
		net2272_ग_लिखो(dev, CHIPREV_2272, ii);
		val = net2272_पढ़ो(dev, CHIPREV_2272);
		अगर (val != refval) अणु
			dev_dbg(dev->dev,
				"%s: write/read CHIPREV register test failed: "
				"wrote 0x%2.2x, read:0x%2.2x expected:0x%2.2x\n",
				__func__, ii, val, refval);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Verअगरy NET2272's "NET2270 legacy revision" रेजिस्टर
	 *  - NET2272 has two revision रेजिस्टरs. The NET2270 legacy revision
	 *    रेजिस्टर should पढ़ो the same value, regardless of the NET2272
	 *    silicon revision.  The legacy रेजिस्टर applies to NET2270
	 *    firmware being applied to the NET2272.
	 */
	val = net2272_पढ़ो(dev, CHIPREV_LEGACY);
	अगर (val != NET2270_LEGACY_REV) अणु
		/*
		 * Unexpected legacy revision value
		 * - Perhaps the chip is a NET2270?
		 */
		dev_dbg(dev->dev,
			"%s: WARNING: UNEXPECTED NET2272 LEGACY REGISTER VALUE:\n"
			" - CHIPREV_LEGACY: expected 0x%2.2x, got:0x%2.2x. (Not NET2272?)\n",
			__func__, NET2270_LEGACY_REV, val);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Verअगरy NET2272 silicon revision
	 *  - This revision रेजिस्टर is appropriate क्रम the silicon version
	 *    of the NET2272
	 */
	val = net2272_पढ़ो(dev, CHIPREV_2272);
	चयन (val) अणु
	हाल CHIPREV_NET2272_R1:
		/*
		 * NET2272 Rev 1 has DMA related errata:
		 *  - Newer silicon (Rev 1A or better) required
		 */
		dev_dbg(dev->dev,
			"%s: Rev 1 detected: newer silicon recommended for DMA support\n",
			__func__);
		अवरोध;
	हाल CHIPREV_NET2272_R1A:
		अवरोध;
	शेष:
		/* NET2272 silicon version *may* not work with this firmware */
		dev_dbg(dev->dev,
			"%s: unexpected silicon revision register value: "
			" CHIPREV_2272: 0x%2.2x\n",
			__func__, val);
		/*
		 * Return Success, even though the chip rev is not an expected value
		 *  - Older, pre-built firmware can attempt to operate on newer silicon
		 *  - Often, new silicon is perfectly compatible
		 */
	पूर्ण

	/* Success: NET2272 checks out OK */
	वापस 0;
पूर्ण

अटल व्योम
net2272_gadget_release(काष्ठा device *_dev)
अणु
	काष्ठा net2272 *dev = container_of(_dev, काष्ठा net2272, gadget.dev);

	kमुक्त(dev);
पूर्ण

/*---------------------------------------------------------------------------*/

अटल व्योम
net2272_हटाओ(काष्ठा net2272 *dev)
अणु
	अगर (dev->added)
		usb_del_gadget(&dev->gadget);
	मुक्त_irq(dev->irq, dev);
	iounmap(dev->base_addr);
	device_हटाओ_file(dev->dev, &dev_attr_रेजिस्टरs);

	dev_info(dev->dev, "unbind\n");
पूर्ण

अटल काष्ठा net2272 *net2272_probe_init(काष्ठा device *dev, अचिन्हित पूर्णांक irq)
अणु
	काष्ठा net2272 *ret;

	अगर (!irq) अणु
		dev_dbg(dev, "No IRQ!\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* alloc, and start init */
	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&ret->lock);
	ret->irq = irq;
	ret->dev = dev;
	ret->gadget.ops = &net2272_ops;
	ret->gadget.max_speed = USB_SPEED_HIGH;

	/* the "gadget" असलtracts/भवizes the controller */
	ret->gadget.name = driver_name;
	usb_initialize_gadget(dev, &ret->gadget, net2272_gadget_release);

	वापस ret;
पूर्ण

अटल पूर्णांक
net2272_probe_fin(काष्ठा net2272 *dev, अचिन्हित पूर्णांक irqflags)
अणु
	पूर्णांक ret;

	/* See अगर there... */
	अगर (net2272_present(dev)) अणु
		dev_warn(dev->dev, "2272 not found!\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	net2272_usb_reset(dev);
	net2272_usb_reinit(dev);

	ret = request_irq(dev->irq, net2272_irq, irqflags, driver_name, dev);
	अगर (ret) अणु
		dev_err(dev->dev, "request interrupt %i failed\n", dev->irq);
		जाओ err;
	पूर्ण

	dev->chiprev = net2272_पढ़ो(dev, CHIPREV_2272);

	/* करोne */
	dev_info(dev->dev, "%s\n", driver_desc);
	dev_info(dev->dev, "irq %i, mem %p, chip rev %04x, dma %s\n",
		dev->irq, dev->base_addr, dev->chiprev,
		dma_mode_string());
	dev_info(dev->dev, "version: %s\n", driver_vers);

	ret = device_create_file(dev->dev, &dev_attr_रेजिस्टरs);
	अगर (ret)
		जाओ err_irq;

	ret = usb_add_gadget(&dev->gadget);
	अगर (ret)
		जाओ err_add_udc;
	dev->added = 1;

	वापस 0;

err_add_udc:
	device_हटाओ_file(dev->dev, &dev_attr_रेजिस्टरs);
 err_irq:
	मुक्त_irq(dev->irq, dev);
 err:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_USB_PCI

/*
 * wrap this driver around the specअगरied device, but
 * करोn't respond over USB until a gadget driver binds to us
 */

अटल पूर्णांक
net2272_rdk1_probe(काष्ठा pci_dev *pdev, काष्ठा net2272 *dev)
अणु
	अचिन्हित दीर्घ resource, len, पंचांगp;
	व्योम __iomem *mem_mapped_addr[4];
	पूर्णांक ret, i;

	/*
	 * BAR 0 holds PLX 9054 config रेजिस्टरs
	 * BAR 1 is i/o memory; unused here
	 * BAR 2 holds EPLD config रेजिस्टरs
	 * BAR 3 holds NET2272 रेजिस्टरs
	 */

	/* Find and map all address spaces */
	क्रम (i = 0; i < 4; ++i) अणु
		अगर (i == 1)
			जारी;	/* BAR1 unused */

		resource = pci_resource_start(pdev, i);
		len = pci_resource_len(pdev, i);

		अगर (!request_mem_region(resource, len, driver_name)) अणु
			dev_dbg(dev->dev, "controller already in use\n");
			ret = -EBUSY;
			जाओ err;
		पूर्ण

		mem_mapped_addr[i] = ioremap(resource, len);
		अगर (mem_mapped_addr[i] == शून्य) अणु
			release_mem_region(resource, len);
			dev_dbg(dev->dev, "can't map memory\n");
			ret = -EFAULT;
			जाओ err;
		पूर्ण
	पूर्ण

	dev->rdk1.plx9054_base_addr = mem_mapped_addr[0];
	dev->rdk1.epld_base_addr = mem_mapped_addr[2];
	dev->base_addr = mem_mapped_addr[3];

	/* Set PLX 9054 bus width (16 bits) */
	पंचांगp = पढ़ोl(dev->rdk1.plx9054_base_addr + LBRD1);
	ग_लिखोl((पंचांगp & ~(3 << MEMORY_SPACE_LOCAL_BUS_WIDTH)) | W16_BIT,
			dev->rdk1.plx9054_base_addr + LBRD1);

	/* Enable PLX 9054 Interrupts */
	ग_लिखोl(पढ़ोl(dev->rdk1.plx9054_base_addr + INTCSR) |
			(1 << PCI_INTERRUPT_ENABLE) |
			(1 << LOCAL_INTERRUPT_INPUT_ENABLE),
			dev->rdk1.plx9054_base_addr + INTCSR);

	ग_लिखोb((1 << CHANNEL_CLEAR_INTERRUPT | (0 << CHANNEL_ENABLE)),
			dev->rdk1.plx9054_base_addr + DMACSR0);

	/* reset */
	ग_लिखोb((1 << EPLD_DMA_ENABLE) |
		(1 << DMA_CTL_DACK) |
		(1 << DMA_TIMEOUT_ENABLE) |
		(1 << USER) |
		(0 << MPX_MODE) |
		(1 << BUSWIDTH) |
		(1 << NET2272_RESET),
		dev->base_addr + EPLD_IO_CONTROL_REGISTER);

	mb();
	ग_लिखोb(पढ़ोb(dev->base_addr + EPLD_IO_CONTROL_REGISTER) &
		~(1 << NET2272_RESET),
		dev->base_addr + EPLD_IO_CONTROL_REGISTER);
	udelay(200);

	वापस 0;

 err:
	जबतक (--i >= 0) अणु
		अगर (i == 1)
			जारी;	/* BAR1 unused */
		iounmap(mem_mapped_addr[i]);
		release_mem_region(pci_resource_start(pdev, i),
			pci_resource_len(pdev, i));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
net2272_rdk2_probe(काष्ठा pci_dev *pdev, काष्ठा net2272 *dev)
अणु
	अचिन्हित दीर्घ resource, len;
	व्योम __iomem *mem_mapped_addr[2];
	पूर्णांक ret, i;

	/*
	 * BAR 0 holds FGPA config रेजिस्टरs
	 * BAR 1 holds NET2272 रेजिस्टरs
	 */

	/* Find and map all address spaces, bar2-3 unused in rdk 2 */
	क्रम (i = 0; i < 2; ++i) अणु
		resource = pci_resource_start(pdev, i);
		len = pci_resource_len(pdev, i);

		अगर (!request_mem_region(resource, len, driver_name)) अणु
			dev_dbg(dev->dev, "controller already in use\n");
			ret = -EBUSY;
			जाओ err;
		पूर्ण

		mem_mapped_addr[i] = ioremap(resource, len);
		अगर (mem_mapped_addr[i] == शून्य) अणु
			release_mem_region(resource, len);
			dev_dbg(dev->dev, "can't map memory\n");
			ret = -EFAULT;
			जाओ err;
		पूर्ण
	पूर्ण

	dev->rdk2.fpga_base_addr = mem_mapped_addr[0];
	dev->base_addr = mem_mapped_addr[1];

	mb();
	/* Set 2272 bus width (16 bits) and reset */
	ग_लिखोl((1 << CHIP_RESET), dev->rdk2.fpga_base_addr + RDK2_LOCCTLRDK);
	udelay(200);
	ग_लिखोl((1 << BUS_WIDTH), dev->rdk2.fpga_base_addr + RDK2_LOCCTLRDK);
	/* Prपूर्णांक fpga version number */
	dev_info(dev->dev, "RDK2 FPGA version %08x\n",
		पढ़ोl(dev->rdk2.fpga_base_addr + RDK2_FPGAREV));
	/* Enable FPGA Interrupts */
	ग_लिखोl((1 << NET2272_PCI_IRQ), dev->rdk2.fpga_base_addr + RDK2_IRQENB);

	वापस 0;

 err:
	जबतक (--i >= 0) अणु
		iounmap(mem_mapped_addr[i]);
		release_mem_region(pci_resource_start(pdev, i),
			pci_resource_len(pdev, i));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
net2272_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net2272 *dev;
	पूर्णांक ret;

	dev = net2272_probe_init(&pdev->dev, pdev->irq);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);
	dev->dev_id = pdev->device;

	अगर (pci_enable_device(pdev) < 0) अणु
		ret = -ENODEV;
		जाओ err_put;
	पूर्ण

	pci_set_master(pdev);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_RDK1: ret = net2272_rdk1_probe(pdev, dev); अवरोध;
	हाल PCI_DEVICE_ID_RDK2: ret = net2272_rdk2_probe(pdev, dev); अवरोध;
	शेष: BUG();
	पूर्ण
	अगर (ret)
		जाओ err_pci;

	ret = net2272_probe_fin(dev, 0);
	अगर (ret)
		जाओ err_pci;

	pci_set_drvdata(pdev, dev);

	वापस 0;

 err_pci:
	pci_disable_device(pdev);
 err_put:
	usb_put_gadget(&dev->gadget);

	वापस ret;
पूर्ण

अटल व्योम
net2272_rdk1_हटाओ(काष्ठा pci_dev *pdev, काष्ठा net2272 *dev)
अणु
	पूर्णांक i;

	/* disable PLX 9054 पूर्णांकerrupts */
	ग_लिखोl(पढ़ोl(dev->rdk1.plx9054_base_addr + INTCSR) &
		~(1 << PCI_INTERRUPT_ENABLE),
		dev->rdk1.plx9054_base_addr + INTCSR);

	/* clean up resources allocated during probe() */
	iounmap(dev->rdk1.plx9054_base_addr);
	iounmap(dev->rdk1.epld_base_addr);

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (i == 1)
			जारी;	/* BAR1 unused */
		release_mem_region(pci_resource_start(pdev, i),
			pci_resource_len(pdev, i));
	पूर्ण
पूर्ण

अटल व्योम
net2272_rdk2_हटाओ(काष्ठा pci_dev *pdev, काष्ठा net2272 *dev)
अणु
	पूर्णांक i;

	/* disable fpga पूर्णांकerrupts
	ग_लिखोl(पढ़ोl(dev->rdk1.plx9054_base_addr + INTCSR) &
			~(1 << PCI_INTERRUPT_ENABLE),
			dev->rdk1.plx9054_base_addr + INTCSR);
	*/

	/* clean up resources allocated during probe() */
	iounmap(dev->rdk2.fpga_base_addr);

	क्रम (i = 0; i < 2; ++i)
		release_mem_region(pci_resource_start(pdev, i),
			pci_resource_len(pdev, i));
पूर्ण

अटल व्योम
net2272_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net2272 *dev = pci_get_drvdata(pdev);

	net2272_हटाओ(dev);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_RDK1: net2272_rdk1_हटाओ(pdev, dev); अवरोध;
	हाल PCI_DEVICE_ID_RDK2: net2272_rdk2_हटाओ(pdev, dev); अवरोध;
	शेष: BUG();
	पूर्ण

	pci_disable_device(pdev);

	usb_put_gadget(&dev->gadget);
पूर्ण

/* Table of matching PCI IDs */
अटल काष्ठा pci_device_id pci_ids[] = अणु
	अणु	/* RDK 1 card */
		.class       = ((PCI_CLASS_BRIDGE_OTHER << 8) | 0xfe),
		.class_mask  = 0,
		.venकरोr      = PCI_VENDOR_ID_PLX,
		.device      = PCI_DEVICE_ID_RDK1,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
	पूर्ण,
	अणु	/* RDK 2 card */
		.class       = ((PCI_CLASS_BRIDGE_OTHER << 8) | 0xfe),
		.class_mask  = 0,
		.venकरोr      = PCI_VENDOR_ID_PLX,
		.device      = PCI_DEVICE_ID_RDK2,
		.subvenकरोr   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

अटल काष्ठा pci_driver net2272_pci_driver = अणु
	.name     = driver_name,
	.id_table = pci_ids,

	.probe    = net2272_pci_probe,
	.हटाओ   = net2272_pci_हटाओ,
पूर्ण;

अटल पूर्णांक net2272_pci_रेजिस्टर(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&net2272_pci_driver);
पूर्ण

अटल व्योम net2272_pci_unरेजिस्टर(व्योम)
अणु
	pci_unरेजिस्टर_driver(&net2272_pci_driver);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक net2272_pci_रेजिस्टर(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम net2272_pci_unरेजिस्टर(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*---------------------------------------------------------------------------*/

अटल पूर्णांक
net2272_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net2272 *dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक irqflags;
	resource_माप_प्रकार base, len;
	काष्ठा resource *iomem, *iomem_bus, *irq_res;

	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	iomem_bus = platक्रमm_get_resource(pdev, IORESOURCE_BUS, 0);
	अगर (!irq_res || !iomem) अणु
		dev_err(&pdev->dev, "must provide irq/base addr");
		वापस -EINVAL;
	पूर्ण

	dev = net2272_probe_init(&pdev->dev, irq_res->start);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	irqflags = 0;
	अगर (irq_res->flags & IORESOURCE_IRQ_HIGHEDGE)
		irqflags |= IRQF_TRIGGER_RISING;
	अगर (irq_res->flags & IORESOURCE_IRQ_LOWEDGE)
		irqflags |= IRQF_TRIGGER_FALLING;
	अगर (irq_res->flags & IORESOURCE_IRQ_HIGHLEVEL)
		irqflags |= IRQF_TRIGGER_HIGH;
	अगर (irq_res->flags & IORESOURCE_IRQ_LOWLEVEL)
		irqflags |= IRQF_TRIGGER_LOW;

	base = iomem->start;
	len = resource_size(iomem);
	अगर (iomem_bus)
		dev->base_shअगरt = iomem_bus->start;

	अगर (!request_mem_region(base, len, driver_name)) अणु
		dev_dbg(dev->dev, "get request memory region!\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण
	dev->base_addr = ioremap(base, len);
	अगर (!dev->base_addr) अणु
		dev_dbg(dev->dev, "can't map memory\n");
		ret = -EFAULT;
		जाओ err_req;
	पूर्ण

	ret = net2272_probe_fin(dev, IRQF_TRIGGER_LOW);
	अगर (ret)
		जाओ err_io;

	platक्रमm_set_drvdata(pdev, dev);
	dev_info(&pdev->dev, "running in 16-bit, %sbyte swap local bus mode\n",
		(net2272_पढ़ो(dev, LOCCTL) & (1 << BYTE_SWAP)) ? "" : "no ");

	वापस 0;

 err_io:
	iounmap(dev->base_addr);
 err_req:
	release_mem_region(base, len);
 err:
	usb_put_gadget(&dev->gadget);

	वापस ret;
पूर्ण

अटल पूर्णांक
net2272_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net2272 *dev = platक्रमm_get_drvdata(pdev);

	net2272_हटाओ(dev);

	release_mem_region(pdev->resource[0].start,
		resource_size(&pdev->resource[0]));

	usb_put_gadget(&dev->gadget);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver net2272_plat_driver = अणु
	.probe   = net2272_plat_probe,
	.हटाओ  = net2272_plat_हटाओ,
	.driver  = अणु
		.name  = driver_name,
	पूर्ण,
	/* FIXME .suspend, .resume */
पूर्ण;
MODULE_ALIAS("platform:net2272");

अटल पूर्णांक __init net2272_init(व्योम)
अणु
	पूर्णांक ret;

	ret = net2272_pci_रेजिस्टर();
	अगर (ret)
		वापस ret;
	ret = platक्रमm_driver_रेजिस्टर(&net2272_plat_driver);
	अगर (ret)
		जाओ err_pci;
	वापस ret;

err_pci:
	net2272_pci_unरेजिस्टर();
	वापस ret;
पूर्ण
module_init(net2272_init);

अटल व्योम __निकास net2272_cleanup(व्योम)
अणु
	net2272_pci_unरेजिस्टर();
	platक्रमm_driver_unरेजिस्टर(&net2272_plat_driver);
पूर्ण
module_निकास(net2272_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("PLX Technology, Inc.");
MODULE_LICENSE("GPL");
