<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB Peripheral Controller driver क्रम Aeroflex Gaisler GRUSBDC.
 *
 * 2013 (c) Aeroflex Gaisler AB
 *
 * This driver supports GRUSBDC USB Device Controller cores available in the
 * GRLIB VHDL IP core library.
 *
 * Full करोcumentation of the GRUSBDC core can be found here:
 * https://www.gaisler.com/products/grlib/grip.pdf
 *
 * Contributors:
 * - Andreas Larsson <andreas@gaisler.com>
 * - Marko Isomaki
 */

/*
 * A GRUSBDC core can have up to 16 IN endpoपूर्णांकs and 16 OUT endpoपूर्णांकs each
 * inभागidually configurable to any of the four USB transfer types. This driver
 * only supports cores in DMA mode.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "gr_udc.h"

#घोषणा	DRIVER_NAME	"gr_udc"
#घोषणा	DRIVER_DESC	"Aeroflex Gaisler GRUSBDC USB Peripheral Controller"

अटल स्थिर अक्षर driver_name[] = DRIVER_NAME;

#घोषणा gr_पढ़ो32(x) (ioपढ़ो32be((x)))
#घोषणा gr_ग_लिखो32(x, v) (ioग_लिखो32be((v), (x)))

/* USB speed and corresponding string calculated from status रेजिस्टर value */
#घोषणा GR_SPEED(status) \
	((status & GR_STATUS_SP) ? USB_SPEED_FULL : USB_SPEED_HIGH)
#घोषणा GR_SPEED_STR(status) usb_speed_string(GR_SPEED(status))

/* Size of hardware buffer calculated from epctrl रेजिस्टर value */
#घोषणा GR_BUFFER_SIZE(epctrl)					      \
	((((epctrl) & GR_EPCTRL_BUFSZ_MASK) >> GR_EPCTRL_BUFSZ_POS) * \
	 GR_EPCTRL_BUFSZ_SCALER)

/* ---------------------------------------------------------------------- */
/* Debug prपूर्णांकout functionality */

अटल स्थिर अक्षर * स्थिर gr_modestring[] = अणु"control", "iso", "bulk", "int"पूर्ण;

अटल स्थिर अक्षर *gr_ep0state_string(क्रमागत gr_ep0state state)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[GR_EP0_DISCONNECT] = "disconnect",
		[GR_EP0_SETUP] = "setup",
		[GR_EP0_IDATA] = "idata",
		[GR_EP0_ODATA] = "odata",
		[GR_EP0_ISTATUS] = "istatus",
		[GR_EP0_OSTATUS] = "ostatus",
		[GR_EP0_STALL] = "stall",
		[GR_EP0_SUSPEND] = "suspend",
	पूर्ण;

	अगर (state < 0 || state >= ARRAY_SIZE(names))
		वापस "UNKNOWN";

	वापस names[state];
पूर्ण

#अगर_घोषित VERBOSE_DEBUG

अटल व्योम gr_dbgprपूर्णांक_request(स्थिर अक्षर *str, काष्ठा gr_ep *ep,
				काष्ठा gr_request *req)
अणु
	पूर्णांक buflen = ep->is_in ? req->req.length : req->req.actual;
	पूर्णांक rowlen = 32;
	पूर्णांक plen = min(rowlen, buflen);

	dev_dbg(ep->dev->dev, "%s: 0x%p, %d bytes data%s:\n", str, req, buflen,
		(buflen > plen ? " (truncated)" : ""));
	prपूर्णांक_hex_dump_debug("   ", DUMP_PREFIX_NONE,
			     rowlen, 4, req->req.buf, plen, false);
पूर्ण

अटल व्योम gr_dbgprपूर्णांक_devreq(काष्ठा gr_udc *dev, u8 type, u8 request,
			       u16 value, u16 index, u16 length)
अणु
	dev_vdbg(dev->dev, "REQ: %02x.%02x v%04x i%04x l%04x\n",
		 type, request, value, index, length);
पूर्ण
#अन्यथा /* !VERBOSE_DEBUG */

अटल व्योम gr_dbgprपूर्णांक_request(स्थिर अक्षर *str, काष्ठा gr_ep *ep,
				काष्ठा gr_request *req) अणुपूर्ण

अटल व्योम gr_dbgprपूर्णांक_devreq(काष्ठा gr_udc *dev, u8 type, u8 request,
			       u16 value, u16 index, u16 length) अणुपूर्ण

#पूर्ण_अगर /* VERBOSE_DEBUG */

/* ---------------------------------------------------------------------- */
/* Debugfs functionality */

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS

अटल व्योम gr_seq_ep_show(काष्ठा seq_file *seq, काष्ठा gr_ep *ep)
अणु
	u32 epctrl = gr_पढ़ो32(&ep->regs->epctrl);
	u32 epstat = gr_पढ़ो32(&ep->regs->epstat);
	पूर्णांक mode = (epctrl & GR_EPCTRL_TT_MASK) >> GR_EPCTRL_TT_POS;
	काष्ठा gr_request *req;

	seq_म_लिखो(seq, "%s:\n", ep->ep.name);
	seq_म_लिखो(seq, "  mode = %s\n", gr_modestring[mode]);
	seq_म_लिखो(seq, "  halted: %d\n", !!(epctrl & GR_EPCTRL_EH));
	seq_म_लिखो(seq, "  disabled: %d\n", !!(epctrl & GR_EPCTRL_ED));
	seq_म_लिखो(seq, "  valid: %d\n", !!(epctrl & GR_EPCTRL_EV));
	seq_म_लिखो(seq, "  dma_start = %d\n", ep->dma_start);
	seq_म_लिखो(seq, "  stopped = %d\n", ep->stopped);
	seq_म_लिखो(seq, "  wedged = %d\n", ep->wedged);
	seq_म_लिखो(seq, "  callback = %d\n", ep->callback);
	seq_म_लिखो(seq, "  maxpacket = %d\n", ep->ep.maxpacket);
	seq_म_लिखो(seq, "  maxpacket_limit = %d\n", ep->ep.maxpacket_limit);
	seq_म_लिखो(seq, "  bytes_per_buffer = %d\n", ep->bytes_per_buffer);
	अगर (mode == 1 || mode == 3)
		seq_म_लिखो(seq, "  nt = %d\n",
			   (epctrl & GR_EPCTRL_NT_MASK) >> GR_EPCTRL_NT_POS);

	seq_म_लिखो(seq, "  Buffer 0: %s %s%d\n",
		   epstat & GR_EPSTAT_B0 ? "valid" : "invalid",
		   epstat & GR_EPSTAT_BS ? " " : "selected ",
		   (epstat & GR_EPSTAT_B0CNT_MASK) >> GR_EPSTAT_B0CNT_POS);
	seq_म_लिखो(seq, "  Buffer 1: %s %s%d\n",
		   epstat & GR_EPSTAT_B1 ? "valid" : "invalid",
		   epstat & GR_EPSTAT_BS ? "selected " : " ",
		   (epstat & GR_EPSTAT_B1CNT_MASK) >> GR_EPSTAT_B1CNT_POS);

	अगर (list_empty(&ep->queue)) अणु
		seq_माला_दो(seq, "  Queue: empty\n\n");
		वापस;
	पूर्ण

	seq_माला_दो(seq, "  Queue:\n");
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		काष्ठा gr_dma_desc *desc;
		काष्ठा gr_dma_desc *next;

		seq_म_लिखो(seq, "    0x%p: 0x%p %d %d\n", req,
			   &req->req.buf, req->req.actual, req->req.length);

		next = req->first_desc;
		करो अणु
			desc = next;
			next = desc->next_desc;
			seq_म_लिखो(seq, "    %c 0x%p (0x%08x): 0x%05x 0x%08x\n",
				   desc == req->curr_desc ? 'c' : ' ',
				   desc, desc->paddr, desc->ctrl, desc->data);
		पूर्ण जबतक (desc != req->last_desc);
	पूर्ण
	seq_माला_दो(seq, "\n");
पूर्ण

अटल पूर्णांक gr_dfs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा gr_udc *dev = seq->निजी;
	u32 control = gr_पढ़ो32(&dev->regs->control);
	u32 status = gr_पढ़ो32(&dev->regs->status);
	काष्ठा gr_ep *ep;

	seq_म_लिखो(seq, "usb state = %s\n",
		   usb_state_string(dev->gadget.state));
	seq_म_लिखो(seq, "address = %d\n",
		   (control & GR_CONTROL_UA_MASK) >> GR_CONTROL_UA_POS);
	seq_म_लिखो(seq, "speed = %s\n", GR_SPEED_STR(status));
	seq_म_लिखो(seq, "ep0state = %s\n", gr_ep0state_string(dev->ep0state));
	seq_म_लिखो(seq, "irq_enabled = %d\n", dev->irq_enabled);
	seq_म_लिखो(seq, "remote_wakeup = %d\n", dev->remote_wakeup);
	seq_म_लिखो(seq, "test_mode = %d\n", dev->test_mode);
	seq_माला_दो(seq, "\n");

	list_क्रम_each_entry(ep, &dev->ep_list, ep_list)
		gr_seq_ep_show(seq, ep);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(gr_dfs);

अटल व्योम gr_dfs_create(काष्ठा gr_udc *dev)
अणु
	स्थिर अक्षर *name = "gr_udc_state";

	dev->dfs_root = debugfs_create_dir(dev_name(dev->dev), usb_debug_root);
	debugfs_create_file(name, 0444, dev->dfs_root, dev, &gr_dfs_fops);
पूर्ण

अटल व्योम gr_dfs_delete(काष्ठा gr_udc *dev)
अणु
	debugfs_हटाओ_recursive(dev->dfs_root);
पूर्ण

#अन्यथा /* !CONFIG_USB_GADGET_DEBUG_FS */

अटल व्योम gr_dfs_create(काष्ठा gr_udc *dev) अणुपूर्ण
अटल व्योम gr_dfs_delete(काष्ठा gr_udc *dev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_USB_GADGET_DEBUG_FS */

/* ---------------------------------------------------------------------- */
/* DMA and request handling */

/* Allocates a new काष्ठा gr_dma_desc, sets paddr and zeroes the rest */
अटल काष्ठा gr_dma_desc *gr_alloc_dma_desc(काष्ठा gr_ep *ep, gfp_t gfp_flags)
अणु
	dma_addr_t paddr;
	काष्ठा gr_dma_desc *dma_desc;

	dma_desc = dma_pool_zalloc(ep->dev->desc_pool, gfp_flags, &paddr);
	अगर (!dma_desc) अणु
		dev_err(ep->dev->dev, "Could not allocate from DMA pool\n");
		वापस शून्य;
	पूर्ण

	dma_desc->paddr = paddr;

	वापस dma_desc;
पूर्ण

अटल अंतरभूत व्योम gr_मुक्त_dma_desc(काष्ठा gr_udc *dev,
				    काष्ठा gr_dma_desc *desc)
अणु
	dma_pool_मुक्त(dev->desc_pool, desc, (dma_addr_t)desc->paddr);
पूर्ण

/* Frees the chain of काष्ठा gr_dma_desc क्रम the given request */
अटल व्योम gr_मुक्त_dma_desc_chain(काष्ठा gr_udc *dev, काष्ठा gr_request *req)
अणु
	काष्ठा gr_dma_desc *desc;
	काष्ठा gr_dma_desc *next;

	next = req->first_desc;
	अगर (!next)
		वापस;

	करो अणु
		desc = next;
		next = desc->next_desc;
		gr_मुक्त_dma_desc(dev, desc);
	पूर्ण जबतक (desc != req->last_desc);

	req->first_desc = शून्य;
	req->curr_desc = शून्य;
	req->last_desc = शून्य;
पूर्ण

अटल व्योम gr_ep0_setup(काष्ठा gr_udc *dev, काष्ठा gr_request *req);

/*
 * Frees allocated resources and calls the appropriate completion function/setup
 * package handler क्रम a finished request.
 *
 * Must be called with dev->lock held and irqs disabled.
 */
अटल व्योम gr_finish_request(काष्ठा gr_ep *ep, काष्ठा gr_request *req,
			      पूर्णांक status)
	__releases(&dev->lock)
	__acquires(&dev->lock)
अणु
	काष्ठा gr_udc *dev;

	list_del_init(&req->queue);

	अगर (likely(req->req.status == -EINPROGRESS))
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	dev = ep->dev;
	usb_gadget_unmap_request(&dev->gadget, &req->req, ep->is_in);
	gr_मुक्त_dma_desc_chain(dev, req);

	अगर (ep->is_in) अणु /* For OUT, req->req.actual माला_लो updated bit by bit */
		req->req.actual = req->req.length;
	पूर्ण अन्यथा अगर (req->oddlen && req->req.actual > req->evenlen) अणु
		/*
		 * Copy to user buffer in this हाल where length was not evenly
		 * भागisible by ep->ep.maxpacket and the last descriptor was
		 * actually used.
		 */
		अक्षर *buftail = ((अक्षर *)req->req.buf + req->evenlen);

		स_नकल(buftail, ep->tailbuf, req->oddlen);

		अगर (req->req.actual > req->req.length) अणु
			/* We got more data than was requested */
			dev_dbg(ep->dev->dev, "Overflow for ep %s\n",
				ep->ep.name);
			gr_dbgprपूर्णांक_request("OVFL", ep, req);
			req->req.status = -EOVERFLOW;
		पूर्ण
	पूर्ण

	अगर (!status) अणु
		अगर (ep->is_in)
			gr_dbgprपूर्णांक_request("SENT", ep, req);
		अन्यथा
			gr_dbgprपूर्णांक_request("RECV", ep, req);
	पूर्ण

	/* Prevent changes to ep->queue during callback */
	ep->callback = 1;
	अगर (req == dev->ep0reqo && !status) अणु
		अगर (req->setup)
			gr_ep0_setup(dev, req);
		अन्यथा
			dev_err(dev->dev,
				"Unexpected non setup packet on ep0in\n");
	पूर्ण अन्यथा अगर (req->req.complete) अणु
		spin_unlock(&dev->lock);

		usb_gadget_giveback_request(&ep->ep, &req->req);

		spin_lock(&dev->lock);
	पूर्ण
	ep->callback = 0;
पूर्ण

अटल काष्ठा usb_request *gr_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा gr_request *req;

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

/*
 * Starts DMA क्रम endpoपूर्णांक ep अगर there are requests in the queue.
 *
 * Must be called with dev->lock held and with !ep->stopped.
 */
अटल व्योम gr_start_dma(काष्ठा gr_ep *ep)
अणु
	काष्ठा gr_request *req;
	u32 dmactrl;

	अगर (list_empty(&ep->queue)) अणु
		ep->dma_start = 0;
		वापस;
	पूर्ण

	req = list_first_entry(&ep->queue, काष्ठा gr_request, queue);

	/* A descriptor should alपढ़ोy have been allocated */
	BUG_ON(!req->curr_desc);

	/*
	 * The DMA controller can not handle smaller OUT buffers than
	 * ep->ep.maxpacket. It could lead to buffer overruns अगर an unexpectedly
	 * दीर्घ packet are received. Thereक्रमe an पूर्णांकernal bounce buffer माला_लो
	 * used when such a request माला_लो enabled.
	 */
	अगर (!ep->is_in && req->oddlen)
		req->last_desc->data = ep->tailbuf_paddr;

	wmb(); /* Make sure all is settled beक्रमe handing it over to DMA */

	/* Set the descriptor poपूर्णांकer in the hardware */
	gr_ग_लिखो32(&ep->regs->dmaaddr, req->curr_desc->paddr);

	/* Announce available descriptors */
	dmactrl = gr_पढ़ो32(&ep->regs->dmactrl);
	gr_ग_लिखो32(&ep->regs->dmactrl, dmactrl | GR_DMACTRL_DA);

	ep->dma_start = 1;
पूर्ण

/*
 * Finishes the first request in the ep's queue and, अगर available, starts the
 * next request in queue.
 *
 * Must be called with dev->lock held, irqs disabled and with !ep->stopped.
 */
अटल व्योम gr_dma_advance(काष्ठा gr_ep *ep, पूर्णांक status)
अणु
	काष्ठा gr_request *req;

	req = list_first_entry(&ep->queue, काष्ठा gr_request, queue);
	gr_finish_request(ep, req, status);
	gr_start_dma(ep); /* Regardless of ep->dma_start */
पूर्ण

/*
 * Abort DMA क्रम an endpoपूर्णांक. Sets the पात DMA bit which causes an ongoing DMA
 * transfer to be canceled and clears GR_DMACTRL_DA.
 *
 * Must be called with dev->lock held.
 */
अटल व्योम gr_पात_dma(काष्ठा gr_ep *ep)
अणु
	u32 dmactrl;

	dmactrl = gr_पढ़ो32(&ep->regs->dmactrl);
	gr_ग_लिखो32(&ep->regs->dmactrl, dmactrl | GR_DMACTRL_AD);
पूर्ण

/*
 * Allocates and sets up a काष्ठा gr_dma_desc and putting it on the descriptor
 * chain.
 *
 * Size is not used क्रम OUT endpoपूर्णांकs. Hardware can not be inकाष्ठाed to handle
 * smaller buffer than MAXPL in the OUT direction.
 */
अटल पूर्णांक gr_add_dma_desc(काष्ठा gr_ep *ep, काष्ठा gr_request *req,
			   dma_addr_t data, अचिन्हित size, gfp_t gfp_flags)
अणु
	काष्ठा gr_dma_desc *desc;

	desc = gr_alloc_dma_desc(ep, gfp_flags);
	अगर (!desc)
		वापस -ENOMEM;

	desc->data = data;
	अगर (ep->is_in)
		desc->ctrl =
			(GR_DESC_IN_CTRL_LEN_MASK & size) | GR_DESC_IN_CTRL_EN;
	अन्यथा
		desc->ctrl = GR_DESC_OUT_CTRL_IE;

	अगर (!req->first_desc) अणु
		req->first_desc = desc;
		req->curr_desc = desc;
	पूर्ण अन्यथा अणु
		req->last_desc->next_desc = desc;
		req->last_desc->next = desc->paddr;
		req->last_desc->ctrl |= GR_DESC_OUT_CTRL_NX;
	पूर्ण
	req->last_desc = desc;

	वापस 0;
पूर्ण

/*
 * Sets up a chain of काष्ठा gr_dma_descriptors poपूर्णांकing to buffers that
 * together covers req->req.length bytes of the buffer at DMA address
 * req->req.dma क्रम the OUT direction.
 *
 * The first descriptor in the chain is enabled, the rest disabled. The
 * पूर्णांकerrupt handler will later enable them one by one when needed so we can
 * find out when the transfer is finished. For OUT endpoपूर्णांकs, all descriptors
 * thereक्रमe generate पूर्णांकerrutps.
 */
अटल पूर्णांक gr_setup_out_desc_list(काष्ठा gr_ep *ep, काष्ठा gr_request *req,
				  gfp_t gfp_flags)
अणु
	u16 bytes_left; /* Bytes left to provide descriptors क्रम */
	u16 bytes_used; /* Bytes accommodated क्रम */
	पूर्णांक ret = 0;

	req->first_desc = शून्य; /* Signals that no allocation is करोne yet */
	bytes_left = req->req.length;
	bytes_used = 0;
	जबतक (bytes_left > 0) अणु
		dma_addr_t start = req->req.dma + bytes_used;
		u16 size = min(bytes_left, ep->bytes_per_buffer);

		अगर (size < ep->bytes_per_buffer) अणु
			/* Prepare using bounce buffer */
			req->evenlen = req->req.length - bytes_left;
			req->oddlen = size;
		पूर्ण

		ret = gr_add_dma_desc(ep, req, start, size, gfp_flags);
		अगर (ret)
			जाओ alloc_err;

		bytes_left -= size;
		bytes_used += size;
	पूर्ण

	req->first_desc->ctrl |= GR_DESC_OUT_CTRL_EN;

	वापस 0;

alloc_err:
	gr_मुक्त_dma_desc_chain(ep->dev, req);

	वापस ret;
पूर्ण

/*
 * Sets up a chain of काष्ठा gr_dma_descriptors poपूर्णांकing to buffers that
 * together covers req->req.length bytes of the buffer at DMA address
 * req->req.dma क्रम the IN direction.
 *
 * When more data is provided than the maximum payload size, the hardware splits
 * this up पूर्णांकo several payloads स्वतःmatically. Moreover, ep->bytes_per_buffer
 * is always set to a multiple of the maximum payload (restricted to the valid
 * number of maximum payloads during high bandwidth isochronous or पूर्णांकerrupt
 * transfers)
 *
 * All descriptors are enabled from the beginning and we only generate an
 * पूर्णांकerrupt क्रम the last one indicating that the entire request has been pushed
 * to hardware.
 */
अटल पूर्णांक gr_setup_in_desc_list(काष्ठा gr_ep *ep, काष्ठा gr_request *req,
				 gfp_t gfp_flags)
अणु
	u16 bytes_left; /* Bytes left in req to provide descriptors क्रम */
	u16 bytes_used; /* Bytes in req accommodated क्रम */
	पूर्णांक ret = 0;

	req->first_desc = शून्य; /* Signals that no allocation is करोne yet */
	bytes_left = req->req.length;
	bytes_used = 0;
	करो अणु /* Allow क्रम zero length packets */
		dma_addr_t start = req->req.dma + bytes_used;
		u16 size = min(bytes_left, ep->bytes_per_buffer);

		ret = gr_add_dma_desc(ep, req, start, size, gfp_flags);
		अगर (ret)
			जाओ alloc_err;

		bytes_left -= size;
		bytes_used += size;
	पूर्ण जबतक (bytes_left > 0);

	/*
	 * Send an extra zero length packet to indicate that no more data is
	 * available when req->req.zero is set and the data length is even
	 * multiples of ep->ep.maxpacket.
	 */
	अगर (req->req.zero && (req->req.length % ep->ep.maxpacket == 0)) अणु
		ret = gr_add_dma_desc(ep, req, 0, 0, gfp_flags);
		अगर (ret)
			जाओ alloc_err;
	पूर्ण

	/*
	 * For IN packets we only want to know when the last packet has been
	 * transmitted (not just put पूर्णांकo पूर्णांकernal buffers).
	 */
	req->last_desc->ctrl |= GR_DESC_IN_CTRL_PI;

	वापस 0;

alloc_err:
	gr_मुक्त_dma_desc_chain(ep->dev, req);

	वापस ret;
पूर्ण

/* Must be called with dev->lock held */
अटल पूर्णांक gr_queue(काष्ठा gr_ep *ep, काष्ठा gr_request *req, gfp_t gfp_flags)
अणु
	काष्ठा gr_udc *dev = ep->dev;
	पूर्णांक ret;

	अगर (unlikely(!ep->ep.desc && ep->num != 0)) अणु
		dev_err(dev->dev, "No ep descriptor for %s\n", ep->ep.name);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(!req->req.buf || !list_empty(&req->queue))) अणु
		dev_err(dev->dev,
			"Invalid request for %s: buf=%p list_empty=%d\n",
			ep->ep.name, req->req.buf, list_empty(&req->queue));
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)) अणु
		dev_err(dev->dev, "-ESHUTDOWN");
		वापस -ESHUTDOWN;
	पूर्ण

	/* Can't touch रेजिस्टरs when suspended */
	अगर (dev->ep0state == GR_EP0_SUSPEND) अणु
		dev_err(dev->dev, "-EBUSY");
		वापस -EBUSY;
	पूर्ण

	/* Set up DMA mapping in हाल the caller didn't */
	ret = usb_gadget_map_request(&dev->gadget, &req->req, ep->is_in);
	अगर (ret) अणु
		dev_err(dev->dev, "usb_gadget_map_request");
		वापस ret;
	पूर्ण

	अगर (ep->is_in)
		ret = gr_setup_in_desc_list(ep, req, gfp_flags);
	अन्यथा
		ret = gr_setup_out_desc_list(ep, req, gfp_flags);
	अगर (ret)
		वापस ret;

	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	list_add_tail(&req->queue, &ep->queue);

	/* Start DMA अगर not started, otherwise पूर्णांकerrupt handler handles it */
	अगर (!ep->dma_start && likely(!ep->stopped))
		gr_start_dma(ep);

	वापस 0;
पूर्ण

/*
 * Queue a request from within the driver.
 *
 * Must be called with dev->lock held.
 */
अटल अंतरभूत पूर्णांक gr_queue_पूर्णांक(काष्ठा gr_ep *ep, काष्ठा gr_request *req,
			       gfp_t gfp_flags)
अणु
	अगर (ep->is_in)
		gr_dbgprपूर्णांक_request("RESP", ep, req);

	वापस gr_queue(ep, req, gfp_flags);
पूर्ण

/* ---------------------------------------------------------------------- */
/* General helper functions */

/*
 * Dequeue ALL requests.
 *
 * Must be called with dev->lock held and irqs disabled.
 */
अटल व्योम gr_ep_nuke(काष्ठा gr_ep *ep)
अणु
	काष्ठा gr_request *req;

	ep->stopped = 1;
	ep->dma_start = 0;
	gr_पात_dma(ep);

	जबतक (!list_empty(&ep->queue)) अणु
		req = list_first_entry(&ep->queue, काष्ठा gr_request, queue);
		gr_finish_request(ep, req, -ESHUTDOWN);
	पूर्ण
पूर्ण

/*
 * Reset the hardware state of this endpoपूर्णांक.
 *
 * Must be called with dev->lock held.
 */
अटल व्योम gr_ep_reset(काष्ठा gr_ep *ep)
अणु
	gr_ग_लिखो32(&ep->regs->epctrl, 0);
	gr_ग_लिखो32(&ep->regs->dmactrl, 0);

	ep->ep.maxpacket = MAX_CTRL_PL_SIZE;
	ep->ep.desc = शून्य;
	ep->stopped = 1;
	ep->dma_start = 0;
पूर्ण

/*
 * Generate STALL on ep0in/out.
 *
 * Must be called with dev->lock held.
 */
अटल व्योम gr_control_stall(काष्ठा gr_udc *dev)
अणु
	u32 epctrl;

	epctrl = gr_पढ़ो32(&dev->epo[0].regs->epctrl);
	gr_ग_लिखो32(&dev->epo[0].regs->epctrl, epctrl | GR_EPCTRL_CS);
	epctrl = gr_पढ़ो32(&dev->epi[0].regs->epctrl);
	gr_ग_लिखो32(&dev->epi[0].regs->epctrl, epctrl | GR_EPCTRL_CS);

	dev->ep0state = GR_EP0_STALL;
पूर्ण

/*
 * Halts, halts and wedges, or clears halt क्रम an endpoपूर्णांक.
 *
 * Must be called with dev->lock held.
 */
अटल पूर्णांक gr_ep_halt_wedge(काष्ठा gr_ep *ep, पूर्णांक halt, पूर्णांक wedge, पूर्णांक fromhost)
अणु
	u32 epctrl;
	पूर्णांक retval = 0;

	अगर (ep->num && !ep->ep.desc)
		वापस -EINVAL;

	अगर (ep->num && ep->ep.desc->bmAttributes == USB_ENDPOINT_XFER_ISOC)
		वापस -EOPNOTSUPP;

	/* Never actually halt ep0, and thereक्रमe never clear halt क्रम ep0 */
	अगर (!ep->num) अणु
		अगर (halt && !fromhost) अणु
			/* ep0 halt from gadget - generate protocol stall */
			gr_control_stall(ep->dev);
			dev_dbg(ep->dev->dev, "EP: stall ep0\n");
			वापस 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	dev_dbg(ep->dev->dev, "EP: %s halt %s\n",
		(halt ? (wedge ? "wedge" : "set") : "clear"), ep->ep.name);

	epctrl = gr_पढ़ो32(&ep->regs->epctrl);
	अगर (halt) अणु
		/* Set HALT */
		gr_ग_लिखो32(&ep->regs->epctrl, epctrl | GR_EPCTRL_EH);
		ep->stopped = 1;
		अगर (wedge)
			ep->wedged = 1;
	पूर्ण अन्यथा अणु
		gr_ग_लिखो32(&ep->regs->epctrl, epctrl & ~GR_EPCTRL_EH);
		ep->stopped = 0;
		ep->wedged = 0;

		/* Things might have been queued up in the meanसमय */
		अगर (!ep->dma_start)
			gr_start_dma(ep);
	पूर्ण

	वापस retval;
पूर्ण

/* Must be called with dev->lock held */
अटल अंतरभूत व्योम gr_set_ep0state(काष्ठा gr_udc *dev, क्रमागत gr_ep0state value)
अणु
	अगर (dev->ep0state != value)
		dev_vdbg(dev->dev, "STATE:  ep0state=%s\n",
			 gr_ep0state_string(value));
	dev->ep0state = value;
पूर्ण

/*
 * Should only be called when endpoपूर्णांकs can not generate पूर्णांकerrupts.
 *
 * Must be called with dev->lock held.
 */
अटल व्योम gr_disable_पूर्णांकerrupts_and_pullup(काष्ठा gr_udc *dev)
अणु
	gr_ग_लिखो32(&dev->regs->control, 0);
	wmb(); /* Make sure that we करो not deny one of our पूर्णांकerrupts */
	dev->irq_enabled = 0;
पूर्ण

/*
 * Stop all device activity and disable data line pullup.
 *
 * Must be called with dev->lock held and irqs disabled.
 */
अटल व्योम gr_stop_activity(काष्ठा gr_udc *dev)
अणु
	काष्ठा gr_ep *ep;

	list_क्रम_each_entry(ep, &dev->ep_list, ep_list)
		gr_ep_nuke(ep);

	gr_disable_पूर्णांकerrupts_and_pullup(dev);

	gr_set_ep0state(dev, GR_EP0_DISCONNECT);
	usb_gadget_set_state(&dev->gadget, USB_STATE_NOTATTACHED);
पूर्ण

/* ---------------------------------------------------------------------- */
/* ep0 setup packet handling */

अटल व्योम gr_ep0_tesपंचांगode_complete(काष्ठा usb_ep *_ep,
				     काष्ठा usb_request *_req)
अणु
	काष्ठा gr_ep *ep;
	काष्ठा gr_udc *dev;
	u32 control;

	ep = container_of(_ep, काष्ठा gr_ep, ep);
	dev = ep->dev;

	spin_lock(&dev->lock);

	control = gr_पढ़ो32(&dev->regs->control);
	control |= GR_CONTROL_TM | (dev->test_mode << GR_CONTROL_TS_POS);
	gr_ग_लिखो32(&dev->regs->control, control);

	spin_unlock(&dev->lock);
पूर्ण

अटल व्योम gr_ep0_dummy_complete(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	/* Nothing needs to be करोne here */
पूर्ण

/*
 * Queue a response on ep0in.
 *
 * Must be called with dev->lock held.
 */
अटल पूर्णांक gr_ep0_respond(काष्ठा gr_udc *dev, u8 *buf, पूर्णांक length,
			  व्योम (*complete)(काष्ठा usb_ep *ep,
					   काष्ठा usb_request *req))
अणु
	u8 *reqbuf = dev->ep0reqi->req.buf;
	पूर्णांक status;
	पूर्णांक i;

	क्रम (i = 0; i < length; i++)
		reqbuf[i] = buf[i];
	dev->ep0reqi->req.length = length;
	dev->ep0reqi->req.complete = complete;

	status = gr_queue_पूर्णांक(&dev->epi[0], dev->ep0reqi, GFP_ATOMIC);
	अगर (status < 0)
		dev_err(dev->dev,
			"Could not queue ep0in setup response: %d\n", status);

	वापस status;
पूर्ण

/*
 * Queue a 2 byte response on ep0in.
 *
 * Must be called with dev->lock held.
 */
अटल अंतरभूत पूर्णांक gr_ep0_respond_u16(काष्ठा gr_udc *dev, u16 response)
अणु
	__le16 le_response = cpu_to_le16(response);

	वापस gr_ep0_respond(dev, (u8 *)&le_response, 2,
			      gr_ep0_dummy_complete);
पूर्ण

/*
 * Queue a ZLP response on ep0in.
 *
 * Must be called with dev->lock held.
 */
अटल अंतरभूत पूर्णांक gr_ep0_respond_empty(काष्ठा gr_udc *dev)
अणु
	वापस gr_ep0_respond(dev, शून्य, 0, gr_ep0_dummy_complete);
पूर्ण

/*
 * This is run when a SET_ADDRESS request is received. First ग_लिखोs
 * the new address to the control रेजिस्टर which is updated पूर्णांकernally
 * when the next IN packet is ACKED.
 *
 * Must be called with dev->lock held.
 */
अटल व्योम gr_set_address(काष्ठा gr_udc *dev, u8 address)
अणु
	u32 control;

	control = gr_पढ़ो32(&dev->regs->control) & ~GR_CONTROL_UA_MASK;
	control |= (address << GR_CONTROL_UA_POS) & GR_CONTROL_UA_MASK;
	control |= GR_CONTROL_SU;
	gr_ग_लिखो32(&dev->regs->control, control);
पूर्ण

/*
 * Returns negative क्रम STALL, 0 क्रम successful handling and positive क्रम
 * delegation.
 *
 * Must be called with dev->lock held.
 */
अटल पूर्णांक gr_device_request(काष्ठा gr_udc *dev, u8 type, u8 request,
			     u16 value, u16 index)
अणु
	u16 response;
	u8 test;

	चयन (request) अणु
	हाल USB_REQ_SET_ADDRESS:
		dev_dbg(dev->dev, "STATUS: address %d\n", value & 0xff);
		gr_set_address(dev, value & 0xff);
		अगर (value)
			usb_gadget_set_state(&dev->gadget, USB_STATE_ADDRESS);
		अन्यथा
			usb_gadget_set_state(&dev->gadget, USB_STATE_DEFAULT);
		वापस gr_ep0_respond_empty(dev);

	हाल USB_REQ_GET_STATUS:
		/* Self घातered | remote wakeup */
		response = 0x0001 | (dev->remote_wakeup ? 0x0002 : 0);
		वापस gr_ep0_respond_u16(dev, response);

	हाल USB_REQ_SET_FEATURE:
		चयन (value) अणु
		हाल USB_DEVICE_REMOTE_WAKEUP:
			/* Allow remote wakeup */
			dev->remote_wakeup = 1;
			वापस gr_ep0_respond_empty(dev);

		हाल USB_DEVICE_TEST_MODE:
			/* The hardware करोes not support USB_TEST_FORCE_ENABLE */
			test = index >> 8;
			अगर (test >= USB_TEST_J && test <= USB_TEST_PACKET) अणु
				dev->test_mode = test;
				वापस gr_ep0_respond(dev, शून्य, 0,
						      gr_ep0_tesपंचांगode_complete);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल USB_REQ_CLEAR_FEATURE:
		चयन (value) अणु
		हाल USB_DEVICE_REMOTE_WAKEUP:
			/* Disallow remote wakeup */
			dev->remote_wakeup = 0;
			वापस gr_ep0_respond_empty(dev);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 1; /* Delegate the rest */
पूर्ण

/*
 * Returns negative क्रम STALL, 0 क्रम successful handling and positive क्रम
 * delegation.
 *
 * Must be called with dev->lock held.
 */
अटल पूर्णांक gr_पूर्णांकerface_request(काष्ठा gr_udc *dev, u8 type, u8 request,
				u16 value, u16 index)
अणु
	अगर (dev->gadget.state != USB_STATE_CONFIGURED)
		वापस -1;

	/*
	 * Should वापस STALL क्रम invalid पूर्णांकerfaces, but udc driver करोes not
	 * know anything about that. However, many gadget drivers करो not handle
	 * GET_STATUS so we need to take care of that.
	 */

	चयन (request) अणु
	हाल USB_REQ_GET_STATUS:
		वापस gr_ep0_respond_u16(dev, 0x0000);

	हाल USB_REQ_SET_FEATURE:
	हाल USB_REQ_CLEAR_FEATURE:
		/*
		 * No possible valid standard requests. Still let gadget drivers
		 * have a go at it.
		 */
		अवरोध;
	पूर्ण

	वापस 1; /* Delegate the rest */
पूर्ण

/*
 * Returns negative क्रम STALL, 0 क्रम successful handling and positive क्रम
 * delegation.
 *
 * Must be called with dev->lock held.
 */
अटल पूर्णांक gr_endpoपूर्णांक_request(काष्ठा gr_udc *dev, u8 type, u8 request,
			       u16 value, u16 index)
अणु
	काष्ठा gr_ep *ep;
	पूर्णांक status;
	पूर्णांक halted;
	u8 epnum = index & USB_ENDPOINT_NUMBER_MASK;
	u8 is_in = index & USB_ENDPOINT_सूची_MASK;

	अगर ((is_in && epnum >= dev->nepi) || (!is_in && epnum >= dev->nepo))
		वापस -1;

	अगर (dev->gadget.state != USB_STATE_CONFIGURED && epnum != 0)
		वापस -1;

	ep = (is_in ? &dev->epi[epnum] : &dev->epo[epnum]);

	चयन (request) अणु
	हाल USB_REQ_GET_STATUS:
		halted = gr_पढ़ो32(&ep->regs->epctrl) & GR_EPCTRL_EH;
		वापस gr_ep0_respond_u16(dev, halted ? 0x0001 : 0);

	हाल USB_REQ_SET_FEATURE:
		चयन (value) अणु
		हाल USB_ENDPOINT_HALT:
			status = gr_ep_halt_wedge(ep, 1, 0, 1);
			अगर (status >= 0)
				status = gr_ep0_respond_empty(dev);
			वापस status;
		पूर्ण
		अवरोध;

	हाल USB_REQ_CLEAR_FEATURE:
		चयन (value) अणु
		हाल USB_ENDPOINT_HALT:
			अगर (ep->wedged)
				वापस -1;
			status = gr_ep_halt_wedge(ep, 0, 0, 1);
			अगर (status >= 0)
				status = gr_ep0_respond_empty(dev);
			वापस status;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 1; /* Delegate the rest */
पूर्ण

/* Must be called with dev->lock held */
अटल व्योम gr_ep0out_requeue(काष्ठा gr_udc *dev)
अणु
	पूर्णांक ret = gr_queue_पूर्णांक(&dev->epo[0], dev->ep0reqo, GFP_ATOMIC);

	अगर (ret)
		dev_err(dev->dev, "Could not queue ep0out setup request: %d\n",
			ret);
पूर्ण

/*
 * The मुख्य function dealing with setup requests on ep0.
 *
 * Must be called with dev->lock held and irqs disabled
 */
अटल व्योम gr_ep0_setup(काष्ठा gr_udc *dev, काष्ठा gr_request *req)
	__releases(&dev->lock)
	__acquires(&dev->lock)
अणु
	जोड़ अणु
		काष्ठा usb_ctrlrequest ctrl;
		u8 raw[8];
		u32 word[2];
	पूर्ण u;
	u8 type;
	u8 request;
	u16 value;
	u16 index;
	u16 length;
	पूर्णांक i;
	पूर्णांक status;

	/* Restore from ep0 halt */
	अगर (dev->ep0state == GR_EP0_STALL) अणु
		gr_set_ep0state(dev, GR_EP0_SETUP);
		अगर (!req->req.actual)
			जाओ out;
	पूर्ण

	अगर (dev->ep0state == GR_EP0_ISTATUS) अणु
		gr_set_ep0state(dev, GR_EP0_SETUP);
		अगर (req->req.actual > 0)
			dev_dbg(dev->dev,
				"Unexpected setup packet at state %s\n",
				gr_ep0state_string(GR_EP0_ISTATUS));
		अन्यथा
			जाओ out; /* Got expected ZLP */
	पूर्ण अन्यथा अगर (dev->ep0state != GR_EP0_SETUP) अणु
		dev_info(dev->dev,
			 "Unexpected ep0out request at state %s - stalling\n",
			 gr_ep0state_string(dev->ep0state));
		gr_control_stall(dev);
		gr_set_ep0state(dev, GR_EP0_SETUP);
		जाओ out;
	पूर्ण अन्यथा अगर (!req->req.actual) अणु
		dev_dbg(dev->dev, "Unexpected ZLP at state %s\n",
			gr_ep0state_string(dev->ep0state));
		जाओ out;
	पूर्ण

	/* Handle SETUP packet */
	क्रम (i = 0; i < req->req.actual; i++)
		u.raw[i] = ((u8 *)req->req.buf)[i];

	type = u.ctrl.bRequestType;
	request = u.ctrl.bRequest;
	value = le16_to_cpu(u.ctrl.wValue);
	index = le16_to_cpu(u.ctrl.wIndex);
	length = le16_to_cpu(u.ctrl.wLength);

	gr_dbgprपूर्णांक_devreq(dev, type, request, value, index, length);

	/* Check क्रम data stage */
	अगर (length) अणु
		अगर (type & USB_सूची_IN)
			gr_set_ep0state(dev, GR_EP0_IDATA);
		अन्यथा
			gr_set_ep0state(dev, GR_EP0_ODATA);
	पूर्ण

	status = 1; /* Positive status flags delegation */
	अगर ((type & USB_TYPE_MASK) == USB_TYPE_STANDARD) अणु
		चयन (type & USB_RECIP_MASK) अणु
		हाल USB_RECIP_DEVICE:
			status = gr_device_request(dev, type, request,
						   value, index);
			अवरोध;
		हाल USB_RECIP_ENDPOINT:
			status =  gr_endpoपूर्णांक_request(dev, type, request,
						      value, index);
			अवरोध;
		हाल USB_RECIP_INTERFACE:
			status = gr_पूर्णांकerface_request(dev, type, request,
						      value, index);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status > 0) अणु
		spin_unlock(&dev->lock);

		dev_vdbg(dev->dev, "DELEGATE\n");
		status = dev->driver->setup(&dev->gadget, &u.ctrl);

		spin_lock(&dev->lock);
	पूर्ण

	/* Generate STALL on both ep0out and ep0in अगर requested */
	अगर (unlikely(status < 0)) अणु
		dev_vdbg(dev->dev, "STALL\n");
		gr_control_stall(dev);
	पूर्ण

	अगर ((type & USB_TYPE_MASK) == USB_TYPE_STANDARD &&
	    request == USB_REQ_SET_CONFIGURATION) अणु
		अगर (!value) अणु
			dev_dbg(dev->dev, "STATUS: deconfigured\n");
			usb_gadget_set_state(&dev->gadget, USB_STATE_ADDRESS);
		पूर्ण अन्यथा अगर (status >= 0) अणु
			/* Not configured unless gadget OK:s it */
			dev_dbg(dev->dev, "STATUS: configured: %d\n", value);
			usb_gadget_set_state(&dev->gadget,
					     USB_STATE_CONFIGURED);
		पूर्ण
	पूर्ण

	/* Get पढ़ोy क्रम next stage */
	अगर (dev->ep0state == GR_EP0_ODATA)
		gr_set_ep0state(dev, GR_EP0_OSTATUS);
	अन्यथा अगर (dev->ep0state == GR_EP0_IDATA)
		gr_set_ep0state(dev, GR_EP0_ISTATUS);
	अन्यथा
		gr_set_ep0state(dev, GR_EP0_SETUP);

out:
	gr_ep0out_requeue(dev);
पूर्ण

/* ---------------------------------------------------------------------- */
/* VBUS and USB reset handling */

/* Must be called with dev->lock held and irqs disabled  */
अटल व्योम gr_vbus_connected(काष्ठा gr_udc *dev, u32 status)
अणु
	u32 control;

	dev->gadget.speed = GR_SPEED(status);
	usb_gadget_set_state(&dev->gadget, USB_STATE_POWERED);

	/* Turn on full पूर्णांकerrupts and pullup */
	control = (GR_CONTROL_SI | GR_CONTROL_UI | GR_CONTROL_VI |
		   GR_CONTROL_SP | GR_CONTROL_EP);
	gr_ग_लिखो32(&dev->regs->control, control);
पूर्ण

/* Must be called with dev->lock held */
अटल व्योम gr_enable_vbus_detect(काष्ठा gr_udc *dev)
अणु
	u32 status;

	dev->irq_enabled = 1;
	wmb(); /* Make sure we करो not ignore an पूर्णांकerrupt */
	gr_ग_लिखो32(&dev->regs->control, GR_CONTROL_VI);

	/* Take care of the हाल we are alपढ़ोy plugged in at this poपूर्णांक */
	status = gr_पढ़ो32(&dev->regs->status);
	अगर (status & GR_STATUS_VB)
		gr_vbus_connected(dev, status);
पूर्ण

/* Must be called with dev->lock held and irqs disabled */
अटल व्योम gr_vbus_disconnected(काष्ठा gr_udc *dev)
अणु
	gr_stop_activity(dev);

	/* Report disconnect */
	अगर (dev->driver && dev->driver->disconnect) अणु
		spin_unlock(&dev->lock);

		dev->driver->disconnect(&dev->gadget);

		spin_lock(&dev->lock);
	पूर्ण

	gr_enable_vbus_detect(dev);
पूर्ण

/* Must be called with dev->lock held and irqs disabled */
अटल व्योम gr_udc_usbreset(काष्ठा gr_udc *dev, u32 status)
अणु
	gr_set_address(dev, 0);
	gr_set_ep0state(dev, GR_EP0_SETUP);
	usb_gadget_set_state(&dev->gadget, USB_STATE_DEFAULT);
	dev->gadget.speed = GR_SPEED(status);

	gr_ep_nuke(&dev->epo[0]);
	gr_ep_nuke(&dev->epi[0]);
	dev->epo[0].stopped = 0;
	dev->epi[0].stopped = 0;
	gr_ep0out_requeue(dev);
पूर्ण

/* ---------------------------------------------------------------------- */
/* Irq handling */

/*
 * Handles पूर्णांकerrupts from in endpoपूर्णांकs. Returns whether something was handled.
 *
 * Must be called with dev->lock held, irqs disabled and with !ep->stopped.
 */
अटल पूर्णांक gr_handle_in_ep(काष्ठा gr_ep *ep)
अणु
	काष्ठा gr_request *req;

	req = list_first_entry(&ep->queue, काष्ठा gr_request, queue);
	अगर (!req->last_desc)
		वापस 0;

	अगर (READ_ONCE(req->last_desc->ctrl) & GR_DESC_IN_CTRL_EN)
		वापस 0; /* Not put in hardware buffers yet */

	अगर (gr_पढ़ो32(&ep->regs->epstat) & (GR_EPSTAT_B1 | GR_EPSTAT_B0))
		वापस 0; /* Not transmitted yet, still in hardware buffers */

	/* Write complete */
	gr_dma_advance(ep, 0);

	वापस 1;
पूर्ण

/*
 * Handles पूर्णांकerrupts from out endpoपूर्णांकs. Returns whether something was handled.
 *
 * Must be called with dev->lock held, irqs disabled and with !ep->stopped.
 */
अटल पूर्णांक gr_handle_out_ep(काष्ठा gr_ep *ep)
अणु
	u32 ep_dmactrl;
	u32 ctrl;
	u16 len;
	काष्ठा gr_request *req;
	काष्ठा gr_udc *dev = ep->dev;

	req = list_first_entry(&ep->queue, काष्ठा gr_request, queue);
	अगर (!req->curr_desc)
		वापस 0;

	ctrl = READ_ONCE(req->curr_desc->ctrl);
	अगर (ctrl & GR_DESC_OUT_CTRL_EN)
		वापस 0; /* Not received yet */

	/* Read complete */
	len = ctrl & GR_DESC_OUT_CTRL_LEN_MASK;
	req->req.actual += len;
	अगर (ctrl & GR_DESC_OUT_CTRL_SE)
		req->setup = 1;

	अगर (len < ep->ep.maxpacket || req->req.actual >= req->req.length) अणु
		/* Short packet or >= expected size - we are करोne */

		अगर ((ep == &dev->epo[0]) && (dev->ep0state == GR_EP0_OSTATUS)) अणु
			/*
			 * Send a status stage ZLP to ack the DATA stage in the
			 * OUT direction. This needs to be करोne beक्रमe
			 * gr_dma_advance as that can lead to a call to
			 * ep0_setup that can change dev->ep0state.
			 */
			gr_ep0_respond_empty(dev);
			gr_set_ep0state(dev, GR_EP0_SETUP);
		पूर्ण

		gr_dma_advance(ep, 0);
	पूर्ण अन्यथा अणु
		/* Not करोne yet. Enable the next descriptor to receive more. */
		req->curr_desc = req->curr_desc->next_desc;
		req->curr_desc->ctrl |= GR_DESC_OUT_CTRL_EN;

		ep_dmactrl = gr_पढ़ो32(&ep->regs->dmactrl);
		gr_ग_लिखो32(&ep->regs->dmactrl, ep_dmactrl | GR_DMACTRL_DA);
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Handle state changes. Returns whether something was handled.
 *
 * Must be called with dev->lock held and irqs disabled.
 */
अटल पूर्णांक gr_handle_state_changes(काष्ठा gr_udc *dev)
अणु
	u32 status = gr_पढ़ो32(&dev->regs->status);
	पूर्णांक handled = 0;
	पूर्णांक घातstate = !(dev->gadget.state == USB_STATE_NOTATTACHED ||
			 dev->gadget.state == USB_STATE_ATTACHED);

	/* VBUS valid detected */
	अगर (!घातstate && (status & GR_STATUS_VB)) अणु
		dev_dbg(dev->dev, "STATUS: vbus valid detected\n");
		gr_vbus_connected(dev, status);
		handled = 1;
	पूर्ण

	/* Disconnect */
	अगर (घातstate && !(status & GR_STATUS_VB)) अणु
		dev_dbg(dev->dev, "STATUS: vbus invalid detected\n");
		gr_vbus_disconnected(dev);
		handled = 1;
	पूर्ण

	/* USB reset detected */
	अगर (status & GR_STATUS_UR) अणु
		dev_dbg(dev->dev, "STATUS: USB reset - speed is %s\n",
			GR_SPEED_STR(status));
		gr_ग_लिखो32(&dev->regs->status, GR_STATUS_UR);
		gr_udc_usbreset(dev, status);
		handled = 1;
	पूर्ण

	/* Speed change */
	अगर (dev->gadget.speed != GR_SPEED(status)) अणु
		dev_dbg(dev->dev, "STATUS: USB Speed change to %s\n",
			GR_SPEED_STR(status));
		dev->gadget.speed = GR_SPEED(status);
		handled = 1;
	पूर्ण

	/* Going पूर्णांकo suspend */
	अगर ((dev->ep0state != GR_EP0_SUSPEND) && !(status & GR_STATUS_SU)) अणु
		dev_dbg(dev->dev, "STATUS: USB suspend\n");
		gr_set_ep0state(dev, GR_EP0_SUSPEND);
		dev->suspended_from = dev->gadget.state;
		usb_gadget_set_state(&dev->gadget, USB_STATE_SUSPENDED);

		अगर ((dev->gadget.speed != USB_SPEED_UNKNOWN) &&
		    dev->driver && dev->driver->suspend) अणु
			spin_unlock(&dev->lock);

			dev->driver->suspend(&dev->gadget);

			spin_lock(&dev->lock);
		पूर्ण
		handled = 1;
	पूर्ण

	/* Coming out of suspend */
	अगर ((dev->ep0state == GR_EP0_SUSPEND) && (status & GR_STATUS_SU)) अणु
		dev_dbg(dev->dev, "STATUS: USB resume\n");
		अगर (dev->suspended_from == USB_STATE_POWERED)
			gr_set_ep0state(dev, GR_EP0_DISCONNECT);
		अन्यथा
			gr_set_ep0state(dev, GR_EP0_SETUP);
		usb_gadget_set_state(&dev->gadget, dev->suspended_from);

		अगर ((dev->gadget.speed != USB_SPEED_UNKNOWN) &&
		    dev->driver && dev->driver->resume) अणु
			spin_unlock(&dev->lock);

			dev->driver->resume(&dev->gadget);

			spin_lock(&dev->lock);
		पूर्ण
		handled = 1;
	पूर्ण

	वापस handled;
पूर्ण

/* Non-पूर्णांकerrupt context irq handler */
अटल irqवापस_t gr_irq_handler(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा gr_udc *dev = _dev;
	काष्ठा gr_ep *ep;
	पूर्णांक handled = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	अगर (!dev->irq_enabled)
		जाओ out;

	/*
	 * Check IN ep पूर्णांकerrupts. We check these beक्रमe the OUT eps because
	 * some gadमाला_लो reuse the request that might alपढ़ोy be currently
	 * outstanding and needs to be completed (मुख्यly setup requests).
	 */
	क्रम (i = 0; i < dev->nepi; i++) अणु
		ep = &dev->epi[i];
		अगर (!ep->stopped && !ep->callback && !list_empty(&ep->queue))
			handled = gr_handle_in_ep(ep) || handled;
	पूर्ण

	/* Check OUT ep पूर्णांकerrupts */
	क्रम (i = 0; i < dev->nepo; i++) अणु
		ep = &dev->epo[i];
		अगर (!ep->stopped && !ep->callback && !list_empty(&ep->queue))
			handled = gr_handle_out_ep(ep) || handled;
	पूर्ण

	/* Check status पूर्णांकerrupts */
	handled = gr_handle_state_changes(dev) || handled;

	/*
	 * Check AMBA DMA errors. Only check अगर we didn't find anything अन्यथा to
	 * handle because this shouldn't happen अगर we did everything right.
	 */
	अगर (!handled) अणु
		list_क्रम_each_entry(ep, &dev->ep_list, ep_list) अणु
			अगर (gr_पढ़ो32(&ep->regs->dmactrl) & GR_DMACTRL_AE) अणु
				dev_err(dev->dev,
					"AMBA Error occurred for %s\n",
					ep->ep.name);
				handled = 1;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/* Interrupt context irq handler */
अटल irqवापस_t gr_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा gr_udc *dev = _dev;

	अगर (!dev->irq_enabled)
		वापस IRQ_NONE;

	वापस IRQ_WAKE_THREAD;
पूर्ण

/* ---------------------------------------------------------------------- */
/* USB ep ops */

/* Enable endpoपूर्णांक. Not क्रम ep0in and ep0out that are handled separately. */
अटल पूर्णांक gr_ep_enable(काष्ठा usb_ep *_ep,
			स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा gr_udc *dev;
	काष्ठा gr_ep *ep;
	u8 mode;
	u8 nt;
	u16 max;
	u16 buffer_size = 0;
	u32 epctrl;

	ep = container_of(_ep, काष्ठा gr_ep, ep);
	अगर (!_ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT)
		वापस -EINVAL;

	dev = ep->dev;

	/* 'ep0' IN and OUT are reserved */
	अगर (ep == &dev->epo[0] || ep == &dev->epi[0])
		वापस -EINVAL;

	अगर (!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)
		वापस -ESHUTDOWN;

	/* Make sure we are clear क्रम enabling */
	epctrl = gr_पढ़ो32(&ep->regs->epctrl);
	अगर (epctrl & GR_EPCTRL_EV)
		वापस -EBUSY;

	/* Check that directions match */
	अगर (!ep->is_in != !usb_endpoपूर्णांक_dir_in(desc))
		वापस -EINVAL;

	/* Check ep num */
	अगर ((!ep->is_in && ep->num >= dev->nepo) ||
	    (ep->is_in && ep->num >= dev->nepi))
		वापस -EINVAL;

	अगर (usb_endpoपूर्णांक_xfer_control(desc)) अणु
		mode = 0;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
		mode = 1;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_bulk(desc)) अणु
		mode = 2;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc)) अणु
		mode = 3;
	पूर्ण अन्यथा अणु
		dev_err(dev->dev, "Unknown transfer type for %s\n",
			ep->ep.name);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Bits 10-0 set the max payload. 12-11 set the number of
	 * additional transactions.
	 */
	max = usb_endpoपूर्णांक_maxp(desc);
	nt = usb_endpoपूर्णांक_maxp_mult(desc) - 1;
	buffer_size = GR_BUFFER_SIZE(epctrl);
	अगर (nt && (mode == 0 || mode == 2)) अणु
		dev_err(dev->dev,
			"%s mode: multiple trans./microframe not valid\n",
			(mode == 2 ? "Bulk" : "Control"));
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (nt == 0x3) अणु
		dev_err(dev->dev,
			"Invalid value 0x3 for additional trans./microframe\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((nt + 1) * max > buffer_size) अणु
		dev_err(dev->dev, "Hw buffer size %d < max payload %d * %d\n",
			buffer_size, (nt + 1), max);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (max == 0) अणु
		dev_err(dev->dev, "Max payload cannot be set to 0\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (max > ep->ep.maxpacket_limit) अणु
		dev_err(dev->dev, "Requested max payload %d > limit %d\n",
			max, ep->ep.maxpacket_limit);
		वापस -EINVAL;
	पूर्ण

	spin_lock(&ep->dev->lock);

	अगर (!ep->stopped) अणु
		spin_unlock(&ep->dev->lock);
		वापस -EBUSY;
	पूर्ण

	ep->stopped = 0;
	ep->wedged = 0;
	ep->ep.desc = desc;
	ep->ep.maxpacket = max;
	ep->dma_start = 0;


	अगर (nt) अणु
		/*
		 * Maximum possible size of all payloads in one microframe
		 * regardless of direction when using high-bandwidth mode.
		 */
		ep->bytes_per_buffer = (nt + 1) * max;
	पूर्ण अन्यथा अगर (ep->is_in) अणु
		/*
		 * The biggest multiple of maximum packet size that fits पूर्णांकo
		 * the buffer. The hardware will split up पूर्णांकo many packets in
		 * the IN direction.
		 */
		ep->bytes_per_buffer = (buffer_size / max) * max;
	पूर्ण अन्यथा अणु
		/*
		 * Only single packets will be placed the buffers in the OUT
		 * direction.
		 */
		ep->bytes_per_buffer = max;
	पूर्ण

	epctrl = (max << GR_EPCTRL_MAXPL_POS)
		| (nt << GR_EPCTRL_NT_POS)
		| (mode << GR_EPCTRL_TT_POS)
		| GR_EPCTRL_EV;
	अगर (ep->is_in)
		epctrl |= GR_EPCTRL_PI;
	gr_ग_लिखो32(&ep->regs->epctrl, epctrl);

	gr_ग_लिखो32(&ep->regs->dmactrl, GR_DMACTRL_IE | GR_DMACTRL_AI);

	spin_unlock(&ep->dev->lock);

	dev_dbg(ep->dev->dev, "EP: %s enabled - %s with %d bytes/buffer\n",
		ep->ep.name, gr_modestring[mode], ep->bytes_per_buffer);
	वापस 0;
पूर्ण

/* Disable endpoपूर्णांक. Not क्रम ep0in and ep0out that are handled separately. */
अटल पूर्णांक gr_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा gr_ep *ep;
	काष्ठा gr_udc *dev;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा gr_ep, ep);
	अगर (!_ep || !ep->ep.desc)
		वापस -ENODEV;

	dev = ep->dev;

	/* 'ep0' IN and OUT are reserved */
	अगर (ep == &dev->epo[0] || ep == &dev->epi[0])
		वापस -EINVAL;

	अगर (dev->ep0state == GR_EP0_SUSPEND)
		वापस -EBUSY;

	dev_dbg(ep->dev->dev, "EP: disable %s\n", ep->ep.name);

	spin_lock_irqsave(&dev->lock, flags);

	gr_ep_nuke(ep);
	gr_ep_reset(ep);
	ep->ep.desc = शून्य;

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

/*
 * Frees a request, but not any DMA buffers associated with it
 * (gr_finish_request should alपढ़ोy have taken care of that).
 */
अटल व्योम gr_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा gr_request *req;

	अगर (!_ep || !_req)
		वापस;
	req = container_of(_req, काष्ठा gr_request, req);

	/* Leads to memory leak */
	WARN(!list_empty(&req->queue),
	     "request not dequeued properly before freeing\n");

	kमुक्त(req);
पूर्ण

/* Queue a request from the gadget */
अटल पूर्णांक gr_queue_ext(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags)
अणु
	काष्ठा gr_ep *ep;
	काष्ठा gr_request *req;
	काष्ठा gr_udc *dev;
	पूर्णांक ret;

	अगर (unlikely(!_ep || !_req))
		वापस -EINVAL;

	ep = container_of(_ep, काष्ठा gr_ep, ep);
	req = container_of(_req, काष्ठा gr_request, req);
	dev = ep->dev;

	spin_lock(&ep->dev->lock);

	/*
	 * The ep0 poपूर्णांकer in the gadget काष्ठा is used both क्रम ep0in and
	 * ep0out. In a data stage in the out direction ep0out needs to be used
	 * instead of the शेष ep0in. Completion functions might use
	 * driver_data, so that needs to be copied as well.
	 */
	अगर ((ep == &dev->epi[0]) && (dev->ep0state == GR_EP0_ODATA)) अणु
		ep = &dev->epo[0];
		ep->ep.driver_data = dev->epi[0].ep.driver_data;
	पूर्ण

	अगर (ep->is_in)
		gr_dbgprपूर्णांक_request("EXTERN", ep, req);

	ret = gr_queue(ep, req, GFP_ATOMIC);

	spin_unlock(&ep->dev->lock);

	वापस ret;
पूर्ण

/* Dequeue JUST ONE request */
अटल पूर्णांक gr_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा gr_request *req;
	काष्ठा gr_ep *ep;
	काष्ठा gr_udc *dev;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	ep = container_of(_ep, काष्ठा gr_ep, ep);
	अगर (!_ep || !_req || (!ep->ep.desc && ep->num != 0))
		वापस -EINVAL;
	dev = ep->dev;
	अगर (!dev->driver)
		वापस -ESHUTDOWN;

	/* We can't touch (DMA) रेजिस्टरs when suspended */
	अगर (dev->ep0state == GR_EP0_SUSPEND)
		वापस -EBUSY;

	spin_lock_irqsave(&dev->lock, flags);

	/* Make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (list_first_entry(&ep->queue, काष्ठा gr_request, queue) == req) अणु
		/* This request is currently being processed */
		gr_पात_dma(ep);
		अगर (ep->stopped)
			gr_finish_request(ep, req, -ECONNRESET);
		अन्यथा
			gr_dma_advance(ep, -ECONNRESET);
	पूर्ण अन्यथा अगर (!list_empty(&req->queue)) अणु
		/* Not being processed - gr_finish_request dequeues it */
		gr_finish_request(ep, req, -ECONNRESET);
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
	पूर्ण

out:
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस ret;
पूर्ण

/* Helper क्रम gr_set_halt and gr_set_wedge */
अटल पूर्णांक gr_set_halt_wedge(काष्ठा usb_ep *_ep, पूर्णांक halt, पूर्णांक wedge)
अणु
	पूर्णांक ret;
	काष्ठा gr_ep *ep;

	अगर (!_ep)
		वापस -ENODEV;
	ep = container_of(_ep, काष्ठा gr_ep, ep);

	spin_lock(&ep->dev->lock);

	/* Halting an IN endpoपूर्णांक should fail अगर queue is not empty */
	अगर (halt && ep->is_in && !list_empty(&ep->queue)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = gr_ep_halt_wedge(ep, halt, wedge, 0);

out:
	spin_unlock(&ep->dev->lock);

	वापस ret;
पूर्ण

/* Halt endpoपूर्णांक */
अटल पूर्णांक gr_set_halt(काष्ठा usb_ep *_ep, पूर्णांक halt)
अणु
	वापस gr_set_halt_wedge(_ep, halt, 0);
पूर्ण

/* Halt and wedge endpoपूर्णांक */
अटल पूर्णांक gr_set_wedge(काष्ठा usb_ep *_ep)
अणु
	वापस gr_set_halt_wedge(_ep, 1, 1);
पूर्ण

/*
 * Return the total number of bytes currently stored in the पूर्णांकernal buffers of
 * the endpoपूर्णांक.
 */
अटल पूर्णांक gr_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा gr_ep *ep;
	u32 epstat;
	u32 bytes = 0;

	अगर (!_ep)
		वापस -ENODEV;
	ep = container_of(_ep, काष्ठा gr_ep, ep);

	epstat = gr_पढ़ो32(&ep->regs->epstat);

	अगर (epstat & GR_EPSTAT_B0)
		bytes += (epstat & GR_EPSTAT_B0CNT_MASK) >> GR_EPSTAT_B0CNT_POS;
	अगर (epstat & GR_EPSTAT_B1)
		bytes += (epstat & GR_EPSTAT_B1CNT_MASK) >> GR_EPSTAT_B1CNT_POS;

	वापस bytes;
पूर्ण


/* Empty data from पूर्णांकernal buffers of an endpoपूर्णांक. */
अटल व्योम gr_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा gr_ep *ep;
	u32 epctrl;

	अगर (!_ep)
		वापस;
	ep = container_of(_ep, काष्ठा gr_ep, ep);
	dev_vdbg(ep->dev->dev, "EP: flush fifo %s\n", ep->ep.name);

	spin_lock(&ep->dev->lock);

	epctrl = gr_पढ़ो32(&ep->regs->epctrl);
	epctrl |= GR_EPCTRL_CB;
	gr_ग_लिखो32(&ep->regs->epctrl, epctrl);

	spin_unlock(&ep->dev->lock);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops gr_ep_ops = अणु
	.enable		= gr_ep_enable,
	.disable	= gr_ep_disable,

	.alloc_request	= gr_alloc_request,
	.मुक्त_request	= gr_मुक्त_request,

	.queue		= gr_queue_ext,
	.dequeue	= gr_dequeue,

	.set_halt	= gr_set_halt,
	.set_wedge	= gr_set_wedge,
	.fअगरo_status	= gr_fअगरo_status,
	.fअगरo_flush	= gr_fअगरo_flush,
पूर्ण;

/* ---------------------------------------------------------------------- */
/* USB Gadget ops */

अटल पूर्णांक gr_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा gr_udc *dev;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा gr_udc, gadget);
	वापस gr_पढ़ो32(&dev->regs->status) & GR_STATUS_FN_MASK;
पूर्ण

अटल पूर्णांक gr_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा gr_udc *dev;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा gr_udc, gadget);

	/* Remote wakeup feature not enabled by host*/
	अगर (!dev->remote_wakeup)
		वापस -EINVAL;

	spin_lock(&dev->lock);

	gr_ग_लिखो32(&dev->regs->control,
		   gr_पढ़ो32(&dev->regs->control) | GR_CONTROL_RW);

	spin_unlock(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gr_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_on)
अणु
	काष्ठा gr_udc *dev;
	u32 control;

	अगर (!_gadget)
		वापस -ENODEV;
	dev = container_of(_gadget, काष्ठा gr_udc, gadget);

	spin_lock(&dev->lock);

	control = gr_पढ़ो32(&dev->regs->control);
	अगर (is_on)
		control |= GR_CONTROL_EP;
	अन्यथा
		control &= ~GR_CONTROL_EP;
	gr_ग_लिखो32(&dev->regs->control, control);

	spin_unlock(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gr_udc_start(काष्ठा usb_gadget *gadget,
			काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा gr_udc *dev = to_gr_udc(gadget);

	spin_lock(&dev->lock);

	/* Hook up the driver */
	driver->driver.bus = शून्य;
	dev->driver = driver;

	/* Get पढ़ोy क्रम host detection */
	gr_enable_vbus_detect(dev);

	spin_unlock(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gr_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा gr_udc *dev = to_gr_udc(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	dev->driver = शून्य;
	gr_stop_activity(dev);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops gr_ops = अणु
	.get_frame	= gr_get_frame,
	.wakeup         = gr_wakeup,
	.pullup         = gr_pullup,
	.udc_start	= gr_udc_start,
	.udc_stop	= gr_udc_stop,
	/* Other operations not supported */
पूर्ण;

/* ---------------------------------------------------------------------- */
/* Module probe, removal and of-matching */

अटल स्थिर अक्षर * स्थिर onames[] = अणु
	"ep0out", "ep1out", "ep2out", "ep3out", "ep4out", "ep5out",
	"ep6out", "ep7out", "ep8out", "ep9out", "ep10out", "ep11out",
	"ep12out", "ep13out", "ep14out", "ep15out"
पूर्ण;

अटल स्थिर अक्षर * स्थिर inames[] = अणु
	"ep0in", "ep1in", "ep2in", "ep3in", "ep4in", "ep5in",
	"ep6in", "ep7in", "ep8in", "ep9in", "ep10in", "ep11in",
	"ep12in", "ep13in", "ep14in", "ep15in"
पूर्ण;

/* Must be called with dev->lock held */
अटल पूर्णांक gr_ep_init(काष्ठा gr_udc *dev, पूर्णांक num, पूर्णांक is_in, u32 maxplimit)
अणु
	काष्ठा gr_ep *ep;
	काष्ठा gr_request *req;
	काष्ठा usb_request *_req;
	व्योम *buf;

	अगर (is_in) अणु
		ep = &dev->epi[num];
		ep->ep.name = inames[num];
		ep->regs = &dev->regs->epi[num];
	पूर्ण अन्यथा अणु
		ep = &dev->epo[num];
		ep->ep.name = onames[num];
		ep->regs = &dev->regs->epo[num];
	पूर्ण

	gr_ep_reset(ep);
	ep->num = num;
	ep->is_in = is_in;
	ep->dev = dev;
	ep->ep.ops = &gr_ep_ops;
	INIT_LIST_HEAD(&ep->queue);

	अगर (num == 0) अणु
		_req = gr_alloc_request(&ep->ep, GFP_ATOMIC);
		अगर (!_req)
			वापस -ENOMEM;

		buf = devm_kzalloc(dev->dev, PAGE_SIZE, GFP_DMA | GFP_ATOMIC);
		अगर (!buf) अणु
			gr_मुक्त_request(&ep->ep, _req);
			वापस -ENOMEM;
		पूर्ण

		req = container_of(_req, काष्ठा gr_request, req);
		req->req.buf = buf;
		req->req.length = MAX_CTRL_PL_SIZE;

		अगर (is_in)
			dev->ep0reqi = req; /* Complete माला_लो set as used */
		अन्यथा
			dev->ep0reqo = req; /* Completion treated separately */

		usb_ep_set_maxpacket_limit(&ep->ep, MAX_CTRL_PL_SIZE);
		ep->bytes_per_buffer = MAX_CTRL_PL_SIZE;

		ep->ep.caps.type_control = true;
	पूर्ण अन्यथा अणु
		usb_ep_set_maxpacket_limit(&ep->ep, (u16)maxplimit);
		list_add_tail(&ep->ep.ep_list, &dev->gadget.ep_list);

		ep->ep.caps.type_iso = true;
		ep->ep.caps.type_bulk = true;
		ep->ep.caps.type_पूर्णांक = true;
	पूर्ण
	list_add_tail(&ep->ep_list, &dev->ep_list);

	अगर (is_in)
		ep->ep.caps.dir_in = true;
	अन्यथा
		ep->ep.caps.dir_out = true;

	ep->tailbuf = dma_alloc_coherent(dev->dev, ep->ep.maxpacket_limit,
					 &ep->tailbuf_paddr, GFP_ATOMIC);
	अगर (!ep->tailbuf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Must be called with dev->lock held */
अटल पूर्णांक gr_udc_init(काष्ठा gr_udc *dev)
अणु
	काष्ठा device_node *np = dev->dev->of_node;
	u32 epctrl_val;
	u32 dmactrl_val;
	पूर्णांक i;
	पूर्णांक ret = 0;
	u32 bufsize;

	gr_set_address(dev, 0);

	INIT_LIST_HEAD(&dev->gadget.ep_list);
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->gadget.ep0 = &dev->epi[0].ep;

	INIT_LIST_HEAD(&dev->ep_list);
	gr_set_ep0state(dev, GR_EP0_DISCONNECT);

	क्रम (i = 0; i < dev->nepo; i++) अणु
		अगर (of_property_पढ़ो_u32_index(np, "epobufsizes", i, &bufsize))
			bufsize = 1024;
		ret = gr_ep_init(dev, i, 0, bufsize);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < dev->nepi; i++) अणु
		अगर (of_property_पढ़ो_u32_index(np, "epibufsizes", i, &bufsize))
			bufsize = 1024;
		ret = gr_ep_init(dev, i, 1, bufsize);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Must be disabled by शेष */
	dev->remote_wakeup = 0;

	/* Enable ep0out and ep0in */
	epctrl_val = (MAX_CTRL_PL_SIZE << GR_EPCTRL_MAXPL_POS) | GR_EPCTRL_EV;
	dmactrl_val = GR_DMACTRL_IE | GR_DMACTRL_AI;
	gr_ग_लिखो32(&dev->epo[0].regs->epctrl, epctrl_val);
	gr_ग_लिखो32(&dev->epi[0].regs->epctrl, epctrl_val | GR_EPCTRL_PI);
	gr_ग_लिखो32(&dev->epo[0].regs->dmactrl, dmactrl_val);
	gr_ग_लिखो32(&dev->epi[0].regs->dmactrl, dmactrl_val);

	वापस 0;
पूर्ण

अटल व्योम gr_ep_हटाओ(काष्ठा gr_udc *dev, पूर्णांक num, पूर्णांक is_in)
अणु
	काष्ठा gr_ep *ep;

	अगर (is_in)
		ep = &dev->epi[num];
	अन्यथा
		ep = &dev->epo[num];

	अगर (ep->tailbuf)
		dma_मुक्त_coherent(dev->dev, ep->ep.maxpacket_limit,
				  ep->tailbuf, ep->tailbuf_paddr);
पूर्ण

अटल पूर्णांक gr_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gr_udc *dev = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	अगर (dev->added)
		usb_del_gadget_udc(&dev->gadget); /* Shuts everything करोwn */
	अगर (dev->driver)
		वापस -EBUSY;

	gr_dfs_delete(dev);
	dma_pool_destroy(dev->desc_pool);
	platक्रमm_set_drvdata(pdev, शून्य);

	gr_मुक्त_request(&dev->epi[0].ep, &dev->ep0reqi->req);
	gr_मुक्त_request(&dev->epo[0].ep, &dev->ep0reqo->req);

	क्रम (i = 0; i < dev->nepo; i++)
		gr_ep_हटाओ(dev, i, 0);
	क्रम (i = 0; i < dev->nepi; i++)
		gr_ep_हटाओ(dev, i, 1);

	वापस 0;
पूर्ण
अटल पूर्णांक gr_request_irq(काष्ठा gr_udc *dev, पूर्णांक irq)
अणु
	वापस devm_request_thपढ़ोed_irq(dev->dev, irq, gr_irq, gr_irq_handler,
					 IRQF_SHARED, driver_name, dev);
पूर्ण

अटल पूर्णांक gr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gr_udc *dev;
	काष्ठा gr_regs __iomem *regs;
	पूर्णांक retval;
	u32 status;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->dev = &pdev->dev;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dev->irq <= 0)
		वापस -ENODEV;

	/* Some core configurations has separate irqs क्रम IN and OUT events */
	dev->irqi = platक्रमm_get_irq(pdev, 1);
	अगर (dev->irqi > 0) अणु
		dev->irqo = platक्रमm_get_irq(pdev, 2);
		अगर (dev->irqo <= 0)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		dev->irqi = 0;
	पूर्ण

	dev->gadget.name = driver_name;
	dev->gadget.max_speed = USB_SPEED_HIGH;
	dev->gadget.ops = &gr_ops;

	spin_lock_init(&dev->lock);
	dev->regs = regs;

	platक्रमm_set_drvdata(pdev, dev);

	/* Determine number of endpoपूर्णांकs and data पूर्णांकerface mode */
	status = gr_पढ़ो32(&dev->regs->status);
	dev->nepi = ((status & GR_STATUS_NEPI_MASK) >> GR_STATUS_NEPI_POS) + 1;
	dev->nepo = ((status & GR_STATUS_NEPO_MASK) >> GR_STATUS_NEPO_POS) + 1;

	अगर (!(status & GR_STATUS_DM)) अणु
		dev_err(dev->dev, "Slave mode cores are not supported\n");
		वापस -ENODEV;
	पूर्ण

	/* --- Effects of the following calls might need explicit cleanup --- */

	/* Create DMA pool क्रम descriptors */
	dev->desc_pool = dma_pool_create("desc_pool", dev->dev,
					 माप(काष्ठा gr_dma_desc), 4, 0);
	अगर (!dev->desc_pool) अणु
		dev_err(dev->dev, "Could not allocate DMA pool");
		वापस -ENOMEM;
	पूर्ण

	/* Inside lock so that no gadget can use this udc until probe is करोne */
	retval = usb_add_gadget_udc(dev->dev, &dev->gadget);
	अगर (retval) अणु
		dev_err(dev->dev, "Could not add gadget udc");
		जाओ out;
	पूर्ण
	dev->added = 1;

	spin_lock(&dev->lock);

	retval = gr_udc_init(dev);
	अगर (retval) अणु
		spin_unlock(&dev->lock);
		जाओ out;
	पूर्ण

	/* Clear all पूर्णांकerrupt enables that might be left on since last boot */
	gr_disable_पूर्णांकerrupts_and_pullup(dev);

	spin_unlock(&dev->lock);

	gr_dfs_create(dev);

	retval = gr_request_irq(dev, dev->irq);
	अगर (retval) अणु
		dev_err(dev->dev, "Failed to request irq %d\n", dev->irq);
		जाओ out;
	पूर्ण

	अगर (dev->irqi) अणु
		retval = gr_request_irq(dev, dev->irqi);
		अगर (retval) अणु
			dev_err(dev->dev, "Failed to request irqi %d\n",
				dev->irqi);
			जाओ out;
		पूर्ण
		retval = gr_request_irq(dev, dev->irqo);
		अगर (retval) अणु
			dev_err(dev->dev, "Failed to request irqo %d\n",
				dev->irqo);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (dev->irqi)
		dev_info(dev->dev, "regs: %p, irqs %d, %d, %d\n", dev->regs,
			 dev->irq, dev->irqi, dev->irqo);
	अन्यथा
		dev_info(dev->dev, "regs: %p, irq %d\n", dev->regs, dev->irq);

out:
	अगर (retval)
		gr_हटाओ(pdev);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा of_device_id gr_match[] = अणु
	अणु.name = "GAISLER_USBDC"पूर्ण,
	अणु.name = "01_021"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gr_match);

अटल काष्ठा platक्रमm_driver gr_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = gr_match,
	पूर्ण,
	.probe = gr_probe,
	.हटाओ = gr_हटाओ,
पूर्ण;
module_platक्रमm_driver(gr_driver);

MODULE_AUTHOR("Aeroflex Gaisler AB.");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
