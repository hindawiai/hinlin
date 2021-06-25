<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * at91_udc -- driver क्रम at91-series USB peripheral controller
 *
 * Copyright (C) 2004 by Thomas Rathbone
 * Copyright (C) 2005 by HP Lअसल
 * Copyright (C) 2005 by David Brownell
 */

#अघोषित	VERBOSE_DEBUG
#अघोषित	PACKET_TRACE

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/clk.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_data/aपंचांगel.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/aपंचांगel-matrix.h>

#समावेश "at91_udc.h"


/*
 * This controller is simple and PIO-only.  It's used in many AT91-series
 * full speed USB controllers, including the at91rm9200 (arm920T, with MMU),
 * at91sam926x (arm926ejs, with MMU), and several no-mmu versions.
 *
 * This driver expects the board has been wired with two GPIOs supporting
 * a VBUS sensing IRQ, and a D+ pullup.  (They may be omitted, but the
 * testing hasn't covered such हालs.)
 *
 * The pullup is most important (so it's पूर्णांकegrated on sam926x parts).  It
 * provides software control over whether the host क्रमागतerates the device.
 *
 * The VBUS sensing helps during क्रमागतeration, and allows both USB घड़ीs
 * (and the transceiver) to stay gated off until they're necessary, saving
 * घातer.  During USB suspend, the 48 MHz घड़ी is gated off in hardware;
 * it may also be gated off by software during some Linux sleep states.
 */

#घोषणा	DRIVER_VERSION	"3 May 2006"

अटल स्थिर अक्षर driver_name [] = "at91_udc";

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा usb_ep_caps caps;
पूर्ण ep_info[] = अणु
#घोषणा EP_INFO(_name, _caps) \
	अणु \
		.name = _name, \
		.caps = _caps, \
	पूर्ण

	EP_INFO("ep0",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTROL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep1",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep2",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep3-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep4",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),
	EP_INFO("ep5",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_ALL, USB_EP_CAPS_सूची_ALL)),

#अघोषित EP_INFO
पूर्ण;

#घोषणा ep0name		ep_info[0].name

#घोषणा VBUS_POLL_TIMEOUT	msecs_to_jअगरfies(1000)

#घोषणा at91_udp_पढ़ो(udc, reg) \
	__raw_पढ़ोl((udc)->udp_baseaddr + (reg))
#घोषणा at91_udp_ग_लिखो(udc, reg, val) \
	__raw_ग_लिखोl((val), (udc)->udp_baseaddr + (reg))

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS

#समावेश <linux/seq_file.h>

अटल स्थिर अक्षर debug_filename[] = "driver/udc";

#घोषणा FOURBITS "%s%s%s%s"
#घोषणा EIGHTBITS FOURBITS FOURBITS

अटल व्योम proc_ep_show(काष्ठा seq_file *s, काष्ठा at91_ep *ep)
अणु
	अटल अक्षर		*types[] = अणु
		"control", "out-iso", "out-bulk", "out-int",
		"BOGUS",   "in-iso",  "in-bulk",  "in-int"पूर्ण;

	u32			csr;
	काष्ठा at91_request	*req;
	अचिन्हित दीर्घ	flags;
	काष्ठा at91_udc	*udc = ep->udc;

	spin_lock_irqsave(&udc->lock, flags);

	csr = __raw_पढ़ोl(ep->creg);

	/* NOTE:  not collecting per-endpoपूर्णांक irq statistics... */

	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "%s, maxpacket %d %s%s %s%s\n",
			ep->ep.name, ep->ep.maxpacket,
			ep->is_in ? "in" : "out",
			ep->is_iso ? " iso" : "",
			ep->is_pingpong
				? (ep->fअगरo_bank ? "pong" : "ping")
				: "",
			ep->stopped ? " stopped" : "");
	seq_म_लिखो(s, "csr %08x rxbytes=%d %s %s %s" EIGHTBITS "\n",
		csr,
		(csr & 0x07ff0000) >> 16,
		(csr & (1 << 15)) ? "enabled" : "disabled",
		(csr & (1 << 11)) ? "DATA1" : "DATA0",
		types[(csr & 0x700) >> 8],

		/* अगरf type is control then prपूर्णांक current direction */
		(!(csr & 0x700))
			? ((csr & (1 << 7)) ? " IN" : " OUT")
			: "",
		(csr & (1 << 6)) ? " rxdatabk1" : "",
		(csr & (1 << 5)) ? " forcestall" : "",
		(csr & (1 << 4)) ? " txpktrdy" : "",

		(csr & (1 << 3)) ? " stallsent" : "",
		(csr & (1 << 2)) ? " rxsetup" : "",
		(csr & (1 << 1)) ? " rxdatabk0" : "",
		(csr & (1 << 0)) ? " txcomp" : "");
	अगर (list_empty (&ep->queue))
		seq_म_लिखो(s, "\t(queue empty)\n");

	अन्यथा list_क्रम_each_entry (req, &ep->queue, queue) अणु
		अचिन्हित	length = req->req.actual;

		seq_म_लिखो(s, "\treq %p len %d/%d buf %p\n",
				&req->req, length,
				req->req.length, req->req.buf);
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल व्योम proc_irq_show(काष्ठा seq_file *s, स्थिर अक्षर *label, u32 mask)
अणु
	पूर्णांक i;

	seq_म_लिखो(s, "%s %04x:%s%s" FOURBITS, label, mask,
		(mask & (1 << 13)) ? " wakeup" : "",
		(mask & (1 << 12)) ? " endbusres" : "",

		(mask & (1 << 11)) ? " sofint" : "",
		(mask & (1 << 10)) ? " extrsm" : "",
		(mask & (1 << 9)) ? " rxrsm" : "",
		(mask & (1 << 8)) ? " rxsusp" : "");
	क्रम (i = 0; i < 8; i++) अणु
		अगर (mask & (1 << i))
			seq_म_लिखो(s, " ep%d", i);
	पूर्ण
	seq_म_लिखो(s, "\n");
पूर्ण

अटल पूर्णांक proc_udc_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा at91_udc	*udc = s->निजी;
	काष्ठा at91_ep	*ep;
	u32		पंचांगp;

	seq_म_लिखो(s, "%s: version %s\n", driver_name, DRIVER_VERSION);

	seq_म_लिखो(s, "vbus %s, pullup %s, %s powered%s, gadget %s\n\n",
		udc->vbus ? "present" : "off",
		udc->enabled
			? (udc->vbus ? "active" : "enabled")
			: "disabled",
		udc->gadget.is_selfघातered ? "self" : "VBUS",
		udc->suspended ? ", suspended" : "",
		udc->driver ? udc->driver->driver.name : "(none)");

	/* करोn't access registers when interface isn't घड़ीed */
	अगर (!udc->घड़ीed) अणु
		seq_म_लिखो(s, "(not clocked)\n");
		वापस 0;
	पूर्ण

	पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_FRM_NUM);
	seq_म_लिखो(s, "frame %05x:%s%s frame=%d\n", पंचांगp,
		(पंचांगp & AT91_UDP_FRM_OK) ? " ok" : "",
		(पंचांगp & AT91_UDP_FRM_ERR) ? " err" : "",
		(पंचांगp & AT91_UDP_NUM));

	पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT);
	seq_म_लिखो(s, "glbstate %02x:%s" FOURBITS "\n", पंचांगp,
		(पंचांगp & AT91_UDP_RMWUPE) ? " rmwupe" : "",
		(पंचांगp & AT91_UDP_RSMINPR) ? " rsminpr" : "",
		(पंचांगp & AT91_UDP_ESR) ? " esr" : "",
		(पंचांगp & AT91_UDP_CONFG) ? " confg" : "",
		(पंचांगp & AT91_UDP_FADDEN) ? " fadden" : "");

	पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_FADDR);
	seq_म_लिखो(s, "faddr   %03x:%s fadd=%d\n", पंचांगp,
		(पंचांगp & AT91_UDP_FEN) ? " fen" : "",
		(पंचांगp & AT91_UDP_FADD));

	proc_irq_show(s, "imr   ", at91_udp_पढ़ो(udc, AT91_UDP_IMR));
	proc_irq_show(s, "isr   ", at91_udp_पढ़ो(udc, AT91_UDP_ISR));

	अगर (udc->enabled && udc->vbus) अणु
		proc_ep_show(s, &udc->ep[0]);
		list_क्रम_each_entry (ep, &udc->gadget.ep_list, ep.ep_list) अणु
			अगर (ep->ep.desc)
				proc_ep_show(s, ep);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम create_debug_file(काष्ठा at91_udc *udc)
अणु
	udc->pde = proc_create_single_data(debug_filename, 0, शून्य,
			proc_udc_show, udc);
पूर्ण

अटल व्योम हटाओ_debug_file(काष्ठा at91_udc *udc)
अणु
	अगर (udc->pde)
		हटाओ_proc_entry(debug_filename, शून्य);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम create_debug_file(काष्ठा at91_udc *udc) अणुपूर्ण
अटल अंतरभूत व्योम हटाओ_debug_file(काष्ठा at91_udc *udc) अणुपूर्ण

#पूर्ण_अगर


/*-------------------------------------------------------------------------*/

अटल व्योम करोne(काष्ठा at91_ep *ep, काष्ठा at91_request *req, पूर्णांक status)
अणु
	अचिन्हित	stopped = ep->stopped;
	काष्ठा at91_udc	*udc = ep->udc;

	list_del_init(&req->queue);
	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;
	अन्यथा
		status = req->req.status;
	अगर (status && status != -ESHUTDOWN)
		VDBG("%s done %p, status %d\n", ep->ep.name, req, status);

	ep->stopped = 1;
	spin_unlock(&udc->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&udc->lock);
	ep->stopped = stopped;

	/* ep0 is always पढ़ोy; other endpoपूर्णांकs need a non-empty queue */
	अगर (list_empty(&ep->queue) && ep->पूर्णांक_mask != (1 << 0))
		at91_udp_ग_लिखो(udc, AT91_UDP_IDR, ep->पूर्णांक_mask);
पूर्ण

/*-------------------------------------------------------------------------*/

/* bits indicating OUT fअगरo has data पढ़ोy */
#घोषणा	RX_DATA_READY	(AT91_UDP_RX_DATA_BK0 | AT91_UDP_RX_DATA_BK1)

/*
 * Endpoपूर्णांक FIFO CSR bits have a mix of bits, making it unsafe to just ग_लिखो
 * back most of the value you just पढ़ो (because of side effects, including
 * bits that may change after पढ़ोing and beक्रमe writing).
 *
 * Except when changing a specअगरic bit, always ग_लिखो values which:
 *  - clear SET_FX bits (setting them could change something)
 *  - set CLR_FX bits (clearing them could change something)
 *
 * There are also state bits like FORCESTALL, EPEDS, सूची, and EPTYPE
 * that shouldn't normally be changed.
 *
 * NOTE at91sam9260 करोcs mention synch between UDPCK and MCK घड़ी करोमुख्यs,
 * implying a need to रुको क्रम one ग_लिखो to complete (test relevant bits)
 * beक्रमe starting the next ग_लिखो.  This shouldn't be an issue given how
 * infrequently we ग_लिखो, except maybe क्रम ग_लिखो-then-पढ़ो idioms.
 */
#घोषणा	SET_FX	(AT91_UDP_TXPKTRDY)
#घोषणा	CLR_FX	(RX_DATA_READY | AT91_UDP_RXSETUP \
		| AT91_UDP_STALLSENT | AT91_UDP_TXCOMP)

/* pull OUT packet data from the endpoपूर्णांक's fअगरo */
अटल पूर्णांक पढ़ो_fअगरo (काष्ठा at91_ep *ep, काष्ठा at91_request *req)
अणु
	u32 __iomem	*creg = ep->creg;
	u8 __iomem	*dreg = ep->creg + (AT91_UDP_FDR(0) - AT91_UDP_CSR(0));
	u32		csr;
	u8		*buf;
	अचिन्हित पूर्णांक	count, bufferspace, is_करोne;

	buf = req->req.buf + req->req.actual;
	bufferspace = req->req.length - req->req.actual;

	/*
	 * there might be nothing to पढ़ो अगर ep_queue() calls us,
	 * or अगर we alपढ़ोy emptied both pingpong buffers
	 */
rescan:
	csr = __raw_पढ़ोl(creg);
	अगर ((csr & RX_DATA_READY) == 0)
		वापस 0;

	count = (csr & AT91_UDP_RXBYTECNT) >> 16;
	अगर (count > ep->ep.maxpacket)
		count = ep->ep.maxpacket;
	अगर (count > bufferspace) अणु
		DBG("%s buffer overflow\n", ep->ep.name);
		req->req.status = -EOVERFLOW;
		count = bufferspace;
	पूर्ण
	__raw_पढ़ोsb(dreg, buf, count);

	/* release and swap pingpong mem bank */
	csr |= CLR_FX;
	अगर (ep->is_pingpong) अणु
		अगर (ep->fअगरo_bank == 0) अणु
			csr &= ~(SET_FX | AT91_UDP_RX_DATA_BK0);
			ep->fअगरo_bank = 1;
		पूर्ण अन्यथा अणु
			csr &= ~(SET_FX | AT91_UDP_RX_DATA_BK1);
			ep->fअगरo_bank = 0;
		पूर्ण
	पूर्ण अन्यथा
		csr &= ~(SET_FX | AT91_UDP_RX_DATA_BK0);
	__raw_ग_लिखोl(csr, creg);

	req->req.actual += count;
	is_करोne = (count < ep->ep.maxpacket);
	अगर (count == bufferspace)
		is_करोne = 1;

	PACKET("%s %p out/%d%s\n", ep->ep.name, &req->req, count,
			is_करोne ? " (done)" : "");

	/*
	 * aव्योम extra trips through IRQ logic क्रम packets alपढ़ोy in
	 * the fअगरo ... maybe preventing an extra (expensive) OUT-NAK
	 */
	अगर (is_करोne)
		करोne(ep, req, 0);
	अन्यथा अगर (ep->is_pingpong) अणु
		/*
		 * One dummy पढ़ो to delay the code because of a HW glitch:
		 * CSR वापसs bad RXCOUNT when पढ़ो too soon after updating
		 * RX_DATA_BK flags.
		 */
		csr = __raw_पढ़ोl(creg);

		bufferspace -= count;
		buf += count;
		जाओ rescan;
	पूर्ण

	वापस is_करोne;
पूर्ण

/* load fअगरo क्रम an IN packet */
अटल पूर्णांक ग_लिखो_fअगरo(काष्ठा at91_ep *ep, काष्ठा at91_request *req)
अणु
	u32 __iomem	*creg = ep->creg;
	u32		csr = __raw_पढ़ोl(creg);
	u8 __iomem	*dreg = ep->creg + (AT91_UDP_FDR(0) - AT91_UDP_CSR(0));
	अचिन्हित	total, count, is_last;
	u8		*buf;

	/*
	 * TODO: allow क्रम writing two packets to the fअगरo ... that'll
	 * reduce the amount of IN-NAKing, but probably won't affect
	 * throughput much.  (Unlike preventing OUT-NAKing!)
	 */

	/*
	 * If ep_queue() calls us, the queue is empty and possibly in
	 * odd states like TXCOMP not yet cleared (we करो it, saving at
	 * least one IRQ) or the fअगरo not yet being मुक्त.  Those aren't
	 * issues normally (IRQ handler fast path).
	 */
	अगर (unlikely(csr & (AT91_UDP_TXCOMP | AT91_UDP_TXPKTRDY))) अणु
		अगर (csr & AT91_UDP_TXCOMP) अणु
			csr |= CLR_FX;
			csr &= ~(SET_FX | AT91_UDP_TXCOMP);
			__raw_ग_लिखोl(csr, creg);
			csr = __raw_पढ़ोl(creg);
		पूर्ण
		अगर (csr & AT91_UDP_TXPKTRDY)
			वापस 0;
	पूर्ण

	buf = req->req.buf + req->req.actual;
	prefetch(buf);
	total = req->req.length - req->req.actual;
	अगर (ep->ep.maxpacket < total) अणु
		count = ep->ep.maxpacket;
		is_last = 0;
	पूर्ण अन्यथा अणु
		count = total;
		is_last = (count < ep->ep.maxpacket) || !req->req.zero;
	पूर्ण

	/*
	 * Write the packet, maybe it's a ZLP.
	 *
	 * NOTE:  incrementing req->actual beक्रमe we receive the ACK means
	 * gadget driver IN bytecounts can be wrong in fault हालs.  That's
	 * fixable with PIO drivers like this one (save "count" here, and
	 * करो the increment later on TX irq), but not क्रम most DMA hardware.
	 *
	 * So all gadget drivers must accept that potential error.  Some
	 * hardware supports precise fअगरo status reporting, letting them
	 * recover when the actual bytecount matters (e.g. क्रम USB Test
	 * and Measurement Class devices).
	 */
	__raw_ग_लिखोsb(dreg, buf, count);
	csr &= ~SET_FX;
	csr |= CLR_FX | AT91_UDP_TXPKTRDY;
	__raw_ग_लिखोl(csr, creg);
	req->req.actual += count;

	PACKET("%s %p in/%d%s\n", ep->ep.name, &req->req, count,
			is_last ? " (done)" : "");
	अगर (is_last)
		करोne(ep, req, 0);
	वापस is_last;
पूर्ण

अटल व्योम nuke(काष्ठा at91_ep *ep, पूर्णांक status)
अणु
	काष्ठा at91_request *req;

	/* terminate any request in the queue */
	ep->stopped = 1;
	अगर (list_empty(&ep->queue))
		वापस;

	VDBG("%s %s\n", __func__, ep->ep.name);
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा at91_request, queue);
		करोne(ep, req, status);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक at91_ep_enable(काष्ठा usb_ep *_ep,
				स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा at91_ep	*ep = container_of(_ep, काष्ठा at91_ep, ep);
	काष्ठा at91_udc *udc;
	u16		maxpacket;
	u32		पंचांगp;
	अचिन्हित दीर्घ	flags;

	अगर (!_ep || !ep
			|| !desc || _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT
			|| (maxpacket = usb_endpoपूर्णांक_maxp(desc)) == 0
			|| maxpacket > ep->maxpacket) अणु
		DBG("bad ep or descriptor\n");
		वापस -EINVAL;
	पूर्ण

	udc = ep->udc;
	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		DBG("bogus device state\n");
		वापस -ESHUTDOWN;
	पूर्ण

	पंचांगp = usb_endpoपूर्णांक_type(desc);
	चयन (पंचांगp) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		DBG("only one control endpoint\n");
		वापस -EINVAL;
	हाल USB_ENDPOINT_XFER_INT:
		अगर (maxpacket > 64)
			जाओ bogus_max;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		चयन (maxpacket) अणु
		हाल 8:
		हाल 16:
		हाल 32:
		हाल 64:
			जाओ ok;
		पूर्ण
bogus_max:
		DBG("bogus maxpacket %d\n", maxpacket);
		वापस -EINVAL;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (!ep->is_pingpong) अणु
			DBG("iso requires double buffering\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

ok:
	spin_lock_irqsave(&udc->lock, flags);

	/* initialize endpoपूर्णांक to match this descriptor */
	ep->is_in = usb_endpoपूर्णांक_dir_in(desc);
	ep->is_iso = (पंचांगp == USB_ENDPOINT_XFER_ISOC);
	ep->stopped = 0;
	अगर (ep->is_in)
		पंचांगp |= 0x04;
	पंचांगp <<= 8;
	पंचांगp |= AT91_UDP_EPEDS;
	__raw_ग_लिखोl(पंचांगp, ep->creg);

	ep->ep.maxpacket = maxpacket;

	/*
	 * reset/init endpoपूर्णांक fअगरo.  NOTE:  leaves fअगरo_bank alone,
	 * since endpoपूर्णांक resets करोn't reset hw pingpong state.
	 */
	at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, ep->पूर्णांक_mask);
	at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, 0);

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक at91_ep_disable (काष्ठा usb_ep * _ep)
अणु
	काष्ठा at91_ep	*ep = container_of(_ep, काष्ठा at91_ep, ep);
	काष्ठा at91_udc	*udc = ep->udc;
	अचिन्हित दीर्घ	flags;

	अगर (ep == &ep->udc->ep[0])
		वापस -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);

	nuke(ep, -ESHUTDOWN);

	/* restore the endpoपूर्णांक's pristine config */
	ep->ep.desc = शून्य;
	ep->ep.maxpacket = ep->maxpacket;

	/* reset fअगरos and endpoपूर्णांक */
	अगर (ep->udc->घड़ीed) अणु
		at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, ep->पूर्णांक_mask);
		at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, 0);
		__raw_ग_लिखोl(0, ep->creg);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/*
 * this is a PIO-only driver, so there's nothing
 * पूर्णांकeresting क्रम request or buffer allocation.
 */

अटल काष्ठा usb_request *
at91_ep_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा at91_request *req;

	req = kzalloc(माप (काष्ठा at91_request), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);
	वापस &req->req;
पूर्ण

अटल व्योम at91_ep_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा at91_request *req;

	req = container_of(_req, काष्ठा at91_request, req);
	BUG_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

अटल पूर्णांक at91_ep_queue(काष्ठा usb_ep *_ep,
			काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा at91_request	*req;
	काष्ठा at91_ep		*ep;
	काष्ठा at91_udc		*udc;
	पूर्णांक			status;
	अचिन्हित दीर्घ		flags;

	req = container_of(_req, काष्ठा at91_request, req);
	ep = container_of(_ep, काष्ठा at91_ep, ep);

	अगर (!_req || !_req->complete
			|| !_req->buf || !list_empty(&req->queue)) अणु
		DBG("invalid request\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!_ep || (!ep->ep.desc && ep->ep.name != ep0name)) अणु
		DBG("invalid ep\n");
		वापस -EINVAL;
	पूर्ण

	udc = ep->udc;

	अगर (!udc || !udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		DBG("invalid device\n");
		वापस -EINVAL;
	पूर्ण

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	spin_lock_irqsave(&udc->lock, flags);

	/* try to kickstart any empty and idle queue */
	अगर (list_empty(&ep->queue) && !ep->stopped) अणु
		पूर्णांक	is_ep0;

		/*
		 * If this control request has a non-empty DATA stage, this
		 * will start that stage.  It works just like a non-control
		 * request (until the status stage starts, maybe early).
		 *
		 * If the data stage is empty, then this starts a successful
		 * IN/STATUS stage.  (Unsuccessful ones use set_halt.)
		 */
		is_ep0 = (ep->ep.name == ep0name);
		अगर (is_ep0) अणु
			u32	पंचांगp;

			अगर (!udc->req_pending) अणु
				status = -EINVAL;
				जाओ करोne;
			पूर्ण

			/*
			 * defer changing CONFG until after the gadget driver
			 * reconfigures the endpoपूर्णांकs.
			 */
			अगर (udc->रुको_क्रम_config_ack) अणु
				पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT);
				पंचांगp ^= AT91_UDP_CONFG;
				VDBG("toggle config\n");
				at91_udp_ग_लिखो(udc, AT91_UDP_GLB_STAT, पंचांगp);
			पूर्ण
			अगर (req->req.length == 0) अणु
ep0_in_status:
				PACKET("ep0 in/status\n");
				status = 0;
				पंचांगp = __raw_पढ़ोl(ep->creg);
				पंचांगp &= ~SET_FX;
				पंचांगp |= CLR_FX | AT91_UDP_TXPKTRDY;
				__raw_ग_लिखोl(पंचांगp, ep->creg);
				udc->req_pending = 0;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (ep->is_in)
			status = ग_लिखो_fअगरo(ep, req);
		अन्यथा अणु
			status = पढ़ो_fअगरo(ep, req);

			/* IN/STATUS stage is otherwise triggered by irq */
			अगर (status && is_ep0)
				जाओ ep0_in_status;
		पूर्ण
	पूर्ण अन्यथा
		status = 0;

	अगर (req && !status) अणु
		list_add_tail (&req->queue, &ep->queue);
		at91_udp_ग_लिखो(udc, AT91_UDP_IER, ep->पूर्णांक_mask);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस (status < 0) ? status : 0;
पूर्ण

अटल पूर्णांक at91_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा at91_ep		*ep;
	काष्ठा at91_request	*req;
	अचिन्हित दीर्घ		flags;
	काष्ठा at91_udc		*udc;

	ep = container_of(_ep, काष्ठा at91_ep, ep);
	अगर (!_ep || ep->ep.name == ep0name)
		वापस -EINVAL;

	udc = ep->udc;

	spin_lock_irqsave(&udc->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry (req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण
	अगर (&req->req != _req) अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	करोne(ep, req, -ECONNRESET);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक at91_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा at91_ep	*ep = container_of(_ep, काष्ठा at91_ep, ep);
	काष्ठा at91_udc	*udc = ep->udc;
	u32 __iomem	*creg;
	u32		csr;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		status = 0;

	अगर (!_ep || ep->is_iso || !ep->udc->घड़ीed)
		वापस -EINVAL;

	creg = ep->creg;
	spin_lock_irqsave(&udc->lock, flags);

	csr = __raw_पढ़ोl(creg);

	/*
	 * fail with still-busy IN endpoपूर्णांकs, ensuring correct sequencing
	 * of data tx then stall.  note that the fअगरo rx bytecount isn't
	 * completely accurate as a tx bytecount.
	 */
	अगर (ep->is_in && (!list_empty(&ep->queue) || (csr >> 16) != 0))
		status = -EAGAIN;
	अन्यथा अणु
		csr |= CLR_FX;
		csr &= ~SET_FX;
		अगर (value) अणु
			csr |= AT91_UDP_FORCESTALL;
			VDBG("halt %s\n", ep->ep.name);
		पूर्ण अन्यथा अणु
			at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, ep->पूर्णांक_mask);
			at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, 0);
			csr &= ~AT91_UDP_FORCESTALL;
		पूर्ण
		__raw_ग_लिखोl(csr, creg);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops at91_ep_ops = अणु
	.enable		= at91_ep_enable,
	.disable	= at91_ep_disable,
	.alloc_request	= at91_ep_alloc_request,
	.मुक्त_request	= at91_ep_मुक्त_request,
	.queue		= at91_ep_queue,
	.dequeue	= at91_ep_dequeue,
	.set_halt	= at91_ep_set_halt,
	/* there's only imprecise fअगरo status reporting */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक at91_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा at91_udc *udc = to_udc(gadget);

	अगर (!to_udc(gadget)->घड़ीed)
		वापस -EINVAL;
	वापस at91_udp_पढ़ो(udc, AT91_UDP_FRM_NUM) & AT91_UDP_NUM;
पूर्ण

अटल पूर्णांक at91_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा at91_udc	*udc = to_udc(gadget);
	u32		glbstate;
	अचिन्हित दीर्घ	flags;

	DBG("%s\n", __func__ );
	spin_lock_irqsave(&udc->lock, flags);

	अगर (!udc->घड़ीed || !udc->suspended)
		जाओ करोne;

	/* NOTE:  some "early versions" handle ESR dअगरferently ... */

	glbstate = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT);
	अगर (!(glbstate & AT91_UDP_ESR))
		जाओ करोne;
	glbstate |= AT91_UDP_ESR;
	at91_udp_ग_लिखो(udc, AT91_UDP_GLB_STAT, glbstate);

करोne:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

/* reinit == restore initial software state */
अटल व्योम udc_reinit(काष्ठा at91_udc *udc)
अणु
	u32 i;

	INIT_LIST_HEAD(&udc->gadget.ep_list);
	INIT_LIST_HEAD(&udc->gadget.ep0->ep_list);
	udc->gadget.quirk_stall_not_supp = 1;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा at91_ep *ep = &udc->ep[i];

		अगर (i != 0)
			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		ep->ep.desc = शून्य;
		ep->stopped = 0;
		ep->fअगरo_bank = 0;
		usb_ep_set_maxpacket_limit(&ep->ep, ep->maxpacket);
		ep->creg = (व्योम __iomem *) udc->udp_baseaddr + AT91_UDP_CSR(i);
		/* initialize one queue per endpoपूर्णांक */
		INIT_LIST_HEAD(&ep->queue);
	पूर्ण
पूर्ण

अटल व्योम reset_gadget(काष्ठा at91_udc *udc)
अणु
	काष्ठा usb_gadget_driver *driver = udc->driver;
	पूर्णांक i;

	अगर (udc->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा at91_ep *ep = &udc->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	पूर्ण
	अगर (driver) अणु
		spin_unlock(&udc->lock);
		usb_gadget_udc_reset(&udc->gadget, driver);
		spin_lock(&udc->lock);
	पूर्ण

	udc_reinit(udc);
पूर्ण

अटल व्योम stop_activity(काष्ठा at91_udc *udc)
अणु
	काष्ठा usb_gadget_driver *driver = udc->driver;
	पूर्णांक i;

	अगर (udc->gadget.speed == USB_SPEED_UNKNOWN)
		driver = शून्य;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		काष्ठा at91_ep *ep = &udc->ep[i];
		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	पूर्ण
	अगर (driver) अणु
		spin_unlock(&udc->lock);
		driver->disconnect(&udc->gadget);
		spin_lock(&udc->lock);
	पूर्ण

	udc_reinit(udc);
पूर्ण

अटल व्योम clk_on(काष्ठा at91_udc *udc)
अणु
	अगर (udc->घड़ीed)
		वापस;
	udc->घड़ीed = 1;

	clk_enable(udc->iclk);
	clk_enable(udc->fclk);
पूर्ण

अटल व्योम clk_off(काष्ठा at91_udc *udc)
अणु
	अगर (!udc->घड़ीed)
		वापस;
	udc->घड़ीed = 0;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	clk_disable(udc->fclk);
	clk_disable(udc->iclk);
पूर्ण

/*
 * activate/deactivate link with host; minimize घातer usage क्रम
 * inactive links by cutting घड़ीs and transceiver घातer.
 */
अटल व्योम pullup(काष्ठा at91_udc *udc, पूर्णांक is_on)
अणु
	अगर (!udc->enabled || !udc->vbus)
		is_on = 0;
	DBG("%sactive\n", is_on ? "" : "in");

	अगर (is_on) अणु
		clk_on(udc);
		at91_udp_ग_लिखो(udc, AT91_UDP_ICR, AT91_UDP_RXRSM);
		at91_udp_ग_लिखो(udc, AT91_UDP_TXVC, 0);
	पूर्ण अन्यथा अणु
		stop_activity(udc);
		at91_udp_ग_लिखो(udc, AT91_UDP_IDR, AT91_UDP_RXRSM);
		at91_udp_ग_लिखो(udc, AT91_UDP_TXVC, AT91_UDP_TXVC_TXVDIS);
		clk_off(udc);
	पूर्ण

	अगर (udc->caps && udc->caps->pullup)
		udc->caps->pullup(udc, is_on);
पूर्ण

/* vbus is here!  turn everything on that's पढ़ोy */
अटल पूर्णांक at91_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	काष्ठा at91_udc	*udc = to_udc(gadget);
	अचिन्हित दीर्घ	flags;

	/* VDBG("vbus %s\n", is_active ? "on" : "off"); */
	spin_lock_irqsave(&udc->lock, flags);
	udc->vbus = (is_active != 0);
	अगर (udc->driver)
		pullup(udc, is_active);
	अन्यथा
		pullup(udc, 0);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक at91_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा at91_udc	*udc = to_udc(gadget);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->enabled = is_on = !!is_on;
	pullup(udc, is_on);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक at91_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा at91_udc	*udc = to_udc(gadget);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&udc->lock, flags);
	gadget->is_selfघातered = (is_on != 0);
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक at91_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक at91_stop(काष्ठा usb_gadget *gadget);

अटल स्थिर काष्ठा usb_gadget_ops at91_udc_ops = अणु
	.get_frame		= at91_get_frame,
	.wakeup			= at91_wakeup,
	.set_selfघातered	= at91_set_selfघातered,
	.vbus_session		= at91_vbus_session,
	.pullup			= at91_pullup,
	.udc_start		= at91_start,
	.udc_stop		= at91_stop,

	/*
	 * VBUS-घातered devices may also also want to support bigger
	 * घातer budमाला_लो after an appropriate SET_CONFIGURATION.
	 */
	/* .vbus_घातer		= at91_vbus_घातer, */
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक handle_ep(काष्ठा at91_ep *ep)
अणु
	काष्ठा at91_request	*req;
	u32 __iomem		*creg = ep->creg;
	u32			csr = __raw_पढ़ोl(creg);

	अगर (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next,
			काष्ठा at91_request, queue);
	अन्यथा
		req = शून्य;

	अगर (ep->is_in) अणु
		अगर (csr & (AT91_UDP_STALLSENT | AT91_UDP_TXCOMP)) अणु
			csr |= CLR_FX;
			csr &= ~(SET_FX | AT91_UDP_STALLSENT | AT91_UDP_TXCOMP);
			__raw_ग_लिखोl(csr, creg);
		पूर्ण
		अगर (req)
			वापस ग_लिखो_fअगरo(ep, req);

	पूर्ण अन्यथा अणु
		अगर (csr & AT91_UDP_STALLSENT) अणु
			/* STALLSENT bit == ISOERR */
			अगर (ep->is_iso && req)
				req->req.status = -EILSEQ;
			csr |= CLR_FX;
			csr &= ~(SET_FX | AT91_UDP_STALLSENT);
			__raw_ग_लिखोl(csr, creg);
			csr = __raw_पढ़ोl(creg);
		पूर्ण
		अगर (req && (csr & RX_DATA_READY))
			वापस पढ़ो_fअगरo(ep, req);
	पूर्ण
	वापस 0;
पूर्ण

जोड़ setup अणु
	u8			raw[8];
	काष्ठा usb_ctrlrequest	r;
पूर्ण;

अटल व्योम handle_setup(काष्ठा at91_udc *udc, काष्ठा at91_ep *ep, u32 csr)
अणु
	u32 __iomem	*creg = ep->creg;
	u8 __iomem	*dreg = ep->creg + (AT91_UDP_FDR(0) - AT91_UDP_CSR(0));
	अचिन्हित	rxcount, i = 0;
	u32		पंचांगp;
	जोड़ setup	pkt;
	पूर्णांक		status = 0;

	/* पढ़ो and ack SETUP; hard-fail क्रम bogus packets */
	rxcount = (csr & AT91_UDP_RXBYTECNT) >> 16;
	अगर (likely(rxcount == 8)) अणु
		जबतक (rxcount--)
			pkt.raw[i++] = __raw_पढ़ोb(dreg);
		अगर (pkt.r.bRequestType & USB_सूची_IN) अणु
			csr |= AT91_UDP_सूची;
			ep->is_in = 1;
		पूर्ण अन्यथा अणु
			csr &= ~AT91_UDP_सूची;
			ep->is_in = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* REVISIT this happens someबार under load; why?? */
		ERR("SETUP len %d, csr %08x\n", rxcount, csr);
		status = -EINVAL;
	पूर्ण
	csr |= CLR_FX;
	csr &= ~(SET_FX | AT91_UDP_RXSETUP);
	__raw_ग_लिखोl(csr, creg);
	udc->रुको_क्रम_addr_ack = 0;
	udc->रुको_क्रम_config_ack = 0;
	ep->stopped = 0;
	अगर (unlikely(status != 0))
		जाओ stall;

#घोषणा w_index		le16_to_cpu(pkt.r.wIndex)
#घोषणा w_value		le16_to_cpu(pkt.r.wValue)
#घोषणा w_length	le16_to_cpu(pkt.r.wLength)

	VDBG("SETUP %02x.%02x v%04x i%04x l%04x\n",
			pkt.r.bRequestType, pkt.r.bRequest,
			w_value, w_index, w_length);

	/*
	 * A few standard requests get handled here, ones that touch
	 * hardware ... notably क्रम device and endpoपूर्णांक features.
	 */
	udc->req_pending = 1;
	csr = __raw_पढ़ोl(creg);
	csr |= CLR_FX;
	csr &= ~SET_FX;
	चयन ((pkt.r.bRequestType << 8) | pkt.r.bRequest) अणु

	हाल ((USB_TYPE_STANDARD|USB_RECIP_DEVICE) << 8)
			| USB_REQ_SET_ADDRESS:
		__raw_ग_लिखोl(csr | AT91_UDP_TXPKTRDY, creg);
		udc->addr = w_value;
		udc->रुको_क्रम_addr_ack = 1;
		udc->req_pending = 0;
		/* FADDR is set later, when we ack host STATUS */
		वापस;

	हाल ((USB_TYPE_STANDARD|USB_RECIP_DEVICE) << 8)
			| USB_REQ_SET_CONFIGURATION:
		पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT) & AT91_UDP_CONFG;
		अगर (pkt.r.wValue)
			udc->रुको_क्रम_config_ack = (पंचांगp == 0);
		अन्यथा
			udc->रुको_क्रम_config_ack = (पंचांगp != 0);
		अगर (udc->रुको_क्रम_config_ack)
			VDBG("wait for config\n");
		/* CONFG is toggled later, अगर gadget driver succeeds */
		अवरोध;

	/*
	 * Hosts may set or clear remote wakeup status, and
	 * devices may report they're VBUS घातered.
	 */
	हाल ((USB_सूची_IN|USB_TYPE_STANDARD|USB_RECIP_DEVICE) << 8)
			| USB_REQ_GET_STATUS:
		पंचांगp = (udc->gadget.is_selfघातered << USB_DEVICE_SELF_POWERED);
		अगर (at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT) & AT91_UDP_ESR)
			पंचांगp |= (1 << USB_DEVICE_REMOTE_WAKEUP);
		PACKET("get device status\n");
		__raw_ग_लिखोb(पंचांगp, dreg);
		__raw_ग_लिखोb(0, dreg);
		जाओ ग_लिखो_in;
		/* then STATUS starts later, स्वतःmatically */
	हाल ((USB_TYPE_STANDARD|USB_RECIP_DEVICE) << 8)
			| USB_REQ_SET_FEATURE:
		अगर (w_value != USB_DEVICE_REMOTE_WAKEUP)
			जाओ stall;
		पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT);
		पंचांगp |= AT91_UDP_ESR;
		at91_udp_ग_लिखो(udc, AT91_UDP_GLB_STAT, पंचांगp);
		जाओ succeed;
	हाल ((USB_TYPE_STANDARD|USB_RECIP_DEVICE) << 8)
			| USB_REQ_CLEAR_FEATURE:
		अगर (w_value != USB_DEVICE_REMOTE_WAKEUP)
			जाओ stall;
		पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT);
		पंचांगp &= ~AT91_UDP_ESR;
		at91_udp_ग_लिखो(udc, AT91_UDP_GLB_STAT, पंचांगp);
		जाओ succeed;

	/*
	 * Interfaces have no feature settings; this is pretty useless.
	 * we won't even insist the पूर्णांकerface exists...
	 */
	हाल ((USB_सूची_IN|USB_TYPE_STANDARD|USB_RECIP_INTERFACE) << 8)
			| USB_REQ_GET_STATUS:
		PACKET("get interface status\n");
		__raw_ग_लिखोb(0, dreg);
		__raw_ग_लिखोb(0, dreg);
		जाओ ग_लिखो_in;
		/* then STATUS starts later, स्वतःmatically */
	हाल ((USB_TYPE_STANDARD|USB_RECIP_INTERFACE) << 8)
			| USB_REQ_SET_FEATURE:
	हाल ((USB_TYPE_STANDARD|USB_RECIP_INTERFACE) << 8)
			| USB_REQ_CLEAR_FEATURE:
		जाओ stall;

	/*
	 * Hosts may clear bulk/पूर्णांकr endpoपूर्णांक halt after the gadget
	 * driver sets it (not widely used); or set it (क्रम testing)
	 */
	हाल ((USB_सूची_IN|USB_TYPE_STANDARD|USB_RECIP_ENDPOINT) << 8)
			| USB_REQ_GET_STATUS:
		पंचांगp = w_index & USB_ENDPOINT_NUMBER_MASK;
		ep = &udc->ep[पंचांगp];
		अगर (पंचांगp >= NUM_ENDPOINTS || (पंचांगp && !ep->ep.desc))
			जाओ stall;

		अगर (पंचांगp) अणु
			अगर ((w_index & USB_सूची_IN)) अणु
				अगर (!ep->is_in)
					जाओ stall;
			पूर्ण अन्यथा अगर (ep->is_in)
				जाओ stall;
		पूर्ण
		PACKET("get %s status\n", ep->ep.name);
		अगर (__raw_पढ़ोl(ep->creg) & AT91_UDP_FORCESTALL)
			पंचांगp = (1 << USB_ENDPOINT_HALT);
		अन्यथा
			पंचांगp = 0;
		__raw_ग_लिखोb(पंचांगp, dreg);
		__raw_ग_लिखोb(0, dreg);
		जाओ ग_लिखो_in;
		/* then STATUS starts later, स्वतःmatically */
	हाल ((USB_TYPE_STANDARD|USB_RECIP_ENDPOINT) << 8)
			| USB_REQ_SET_FEATURE:
		पंचांगp = w_index & USB_ENDPOINT_NUMBER_MASK;
		ep = &udc->ep[पंचांगp];
		अगर (w_value != USB_ENDPOINT_HALT || पंचांगp >= NUM_ENDPOINTS)
			जाओ stall;
		अगर (!ep->ep.desc || ep->is_iso)
			जाओ stall;
		अगर ((w_index & USB_सूची_IN)) अणु
			अगर (!ep->is_in)
				जाओ stall;
		पूर्ण अन्यथा अगर (ep->is_in)
			जाओ stall;

		पंचांगp = __raw_पढ़ोl(ep->creg);
		पंचांगp &= ~SET_FX;
		पंचांगp |= CLR_FX | AT91_UDP_FORCESTALL;
		__raw_ग_लिखोl(पंचांगp, ep->creg);
		जाओ succeed;
	हाल ((USB_TYPE_STANDARD|USB_RECIP_ENDPOINT) << 8)
			| USB_REQ_CLEAR_FEATURE:
		पंचांगp = w_index & USB_ENDPOINT_NUMBER_MASK;
		ep = &udc->ep[पंचांगp];
		अगर (w_value != USB_ENDPOINT_HALT || पंचांगp >= NUM_ENDPOINTS)
			जाओ stall;
		अगर (पंचांगp == 0)
			जाओ succeed;
		अगर (!ep->ep.desc || ep->is_iso)
			जाओ stall;
		अगर ((w_index & USB_सूची_IN)) अणु
			अगर (!ep->is_in)
				जाओ stall;
		पूर्ण अन्यथा अगर (ep->is_in)
			जाओ stall;

		at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, ep->पूर्णांक_mask);
		at91_udp_ग_लिखो(udc, AT91_UDP_RST_EP, 0);
		पंचांगp = __raw_पढ़ोl(ep->creg);
		पंचांगp |= CLR_FX;
		पंचांगp &= ~(SET_FX | AT91_UDP_FORCESTALL);
		__raw_ग_लिखोl(पंचांगp, ep->creg);
		अगर (!list_empty(&ep->queue))
			handle_ep(ep);
		जाओ succeed;
	पूर्ण

#अघोषित w_value
#अघोषित w_index
#अघोषित w_length

	/* pass request up to the gadget driver */
	अगर (udc->driver) अणु
		spin_unlock(&udc->lock);
		status = udc->driver->setup(&udc->gadget, &pkt.r);
		spin_lock(&udc->lock);
	पूर्ण
	अन्यथा
		status = -ENODEV;
	अगर (status < 0) अणु
stall:
		VDBG("req %02x.%02x protocol STALL; stat %d\n",
				pkt.r.bRequestType, pkt.r.bRequest, status);
		csr |= AT91_UDP_FORCESTALL;
		__raw_ग_लिखोl(csr, creg);
		udc->req_pending = 0;
	पूर्ण
	वापस;

succeed:
	/* immediate successful (IN) STATUS after zero length DATA */
	PACKET("ep0 in/status\n");
ग_लिखो_in:
	csr |= AT91_UDP_TXPKTRDY;
	__raw_ग_लिखोl(csr, creg);
	udc->req_pending = 0;
पूर्ण

अटल व्योम handle_ep0(काष्ठा at91_udc *udc)
अणु
	काष्ठा at91_ep		*ep0 = &udc->ep[0];
	u32 __iomem		*creg = ep0->creg;
	u32			csr = __raw_पढ़ोl(creg);
	काष्ठा at91_request	*req;

	अगर (unlikely(csr & AT91_UDP_STALLSENT)) अणु
		nuke(ep0, -EPROTO);
		udc->req_pending = 0;
		csr |= CLR_FX;
		csr &= ~(SET_FX | AT91_UDP_STALLSENT | AT91_UDP_FORCESTALL);
		__raw_ग_लिखोl(csr, creg);
		VDBG("ep0 stalled\n");
		csr = __raw_पढ़ोl(creg);
	पूर्ण
	अगर (csr & AT91_UDP_RXSETUP) अणु
		nuke(ep0, 0);
		udc->req_pending = 0;
		handle_setup(udc, ep0, csr);
		वापस;
	पूर्ण

	अगर (list_empty(&ep0->queue))
		req = शून्य;
	अन्यथा
		req = list_entry(ep0->queue.next, काष्ठा at91_request, queue);

	/* host ACKed an IN packet that we sent */
	अगर (csr & AT91_UDP_TXCOMP) अणु
		csr |= CLR_FX;
		csr &= ~(SET_FX | AT91_UDP_TXCOMP);

		/* ग_लिखो more IN DATA? */
		अगर (req && ep0->is_in) अणु
			अगर (handle_ep(ep0))
				udc->req_pending = 0;

		/*
		 * Ack after:
		 *  - last IN DATA packet (including GET_STATUS)
		 *  - IN/STATUS क्रम OUT DATA
		 *  - IN/STATUS क्रम any zero-length DATA stage
		 * except क्रम the IN DATA हाल, the host should send
		 * an OUT status later, which we'll ack.
		 */
		पूर्ण अन्यथा अणु
			udc->req_pending = 0;
			__raw_ग_लिखोl(csr, creg);

			/*
			 * SET_ADDRESS takes effect only after the STATUS
			 * (to the original address) माला_लो acked.
			 */
			अगर (udc->रुको_क्रम_addr_ack) अणु
				u32	पंचांगp;

				at91_udp_ग_लिखो(udc, AT91_UDP_FADDR,
						AT91_UDP_FEN | udc->addr);
				पंचांगp = at91_udp_पढ़ो(udc, AT91_UDP_GLB_STAT);
				पंचांगp &= ~AT91_UDP_FADDEN;
				अगर (udc->addr)
					पंचांगp |= AT91_UDP_FADDEN;
				at91_udp_ग_लिखो(udc, AT91_UDP_GLB_STAT, पंचांगp);

				udc->रुको_क्रम_addr_ack = 0;
				VDBG("address %d\n", udc->addr);
			पूर्ण
		पूर्ण
	पूर्ण

	/* OUT packet arrived ... */
	अन्यथा अगर (csr & AT91_UDP_RX_DATA_BK0) अणु
		csr |= CLR_FX;
		csr &= ~(SET_FX | AT91_UDP_RX_DATA_BK0);

		/* OUT DATA stage */
		अगर (!ep0->is_in) अणु
			अगर (req) अणु
				अगर (handle_ep(ep0)) अणु
					/* send IN/STATUS */
					PACKET("ep0 in/status\n");
					csr = __raw_पढ़ोl(creg);
					csr &= ~SET_FX;
					csr |= CLR_FX | AT91_UDP_TXPKTRDY;
					__raw_ग_लिखोl(csr, creg);
					udc->req_pending = 0;
				पूर्ण
			पूर्ण अन्यथा अगर (udc->req_pending) अणु
				/*
				 * AT91 hardware has a hard समय with this
				 * "deferred response" mode क्रम control-OUT
				 * transfers.  (For control-IN it's fine.)
				 *
				 * The normal solution leaves OUT data in the
				 * fअगरo until the gadget driver is पढ़ोy.
				 * We couldn't करो that here without disabling
				 * the IRQ that tells about SETUP packets,
				 * e.g. when the host माला_लो impatient...
				 *
				 * Working around it by copying पूर्णांकo a buffer
				 * would almost be a non-deferred response,
				 * except that it wouldn't permit reliable
				 * stalling of the request.  Instead, demand
				 * that gadget drivers not use this mode.
				 */
				DBG("no control-OUT deferred responses!\n");
				__raw_ग_लिखोl(csr | AT91_UDP_FORCESTALL, creg);
				udc->req_pending = 0;
			पूर्ण

		/* STATUS stage क्रम control-IN; ack.  */
		पूर्ण अन्यथा अणु
			PACKET("ep0 out/status ACK\n");
			__raw_ग_लिखोl(csr, creg);

			/* "early" status stage */
			अगर (req)
				करोne(ep0, req, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t at91_udc_irq (पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा at91_udc		*udc = _udc;
	u32			rescans = 5;
	पूर्णांक			disable_घड़ी = 0;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&udc->lock, flags);

	अगर (!udc->घड़ीed) अणु
		clk_on(udc);
		disable_घड़ी = 1;
	पूर्ण

	जबतक (rescans--) अणु
		u32 status;

		status = at91_udp_पढ़ो(udc, AT91_UDP_ISR)
			& at91_udp_पढ़ो(udc, AT91_UDP_IMR);
		अगर (!status)
			अवरोध;

		/* USB reset irq:  not maskable */
		अगर (status & AT91_UDP_ENDBUSRES) अणु
			at91_udp_ग_लिखो(udc, AT91_UDP_IDR, ~MINIMUS_INTERRUPTUS);
			at91_udp_ग_लिखो(udc, AT91_UDP_IER, MINIMUS_INTERRUPTUS);
			/* Aपंचांगel code clears this irq twice */
			at91_udp_ग_लिखो(udc, AT91_UDP_ICR, AT91_UDP_ENDBUSRES);
			at91_udp_ग_लिखो(udc, AT91_UDP_ICR, AT91_UDP_ENDBUSRES);
			VDBG("end bus reset\n");
			udc->addr = 0;
			reset_gadget(udc);

			/* enable ep0 */
			at91_udp_ग_लिखो(udc, AT91_UDP_CSR(0),
					AT91_UDP_EPEDS | AT91_UDP_EPTYPE_CTRL);
			udc->gadget.speed = USB_SPEED_FULL;
			udc->suspended = 0;
			at91_udp_ग_लिखो(udc, AT91_UDP_IER, AT91_UDP_EP(0));

			/*
			 * NOTE:  this driver keeps घड़ीs off unless the
			 * USB host is present.  That saves घातer, but क्रम
			 * boards that करोn't support VBUS detection, both
			 * घड़ीs need to be active most of the समय.
			 */

		/* host initiated suspend (3+ms bus idle) */
		पूर्ण अन्यथा अगर (status & AT91_UDP_RXSUSP) अणु
			at91_udp_ग_लिखो(udc, AT91_UDP_IDR, AT91_UDP_RXSUSP);
			at91_udp_ग_लिखो(udc, AT91_UDP_IER, AT91_UDP_RXRSM);
			at91_udp_ग_लिखो(udc, AT91_UDP_ICR, AT91_UDP_RXSUSP);
			/* VDBG("bus suspend\n"); */
			अगर (udc->suspended)
				जारी;
			udc->suspended = 1;

			/*
			 * NOTE:  when suspending a VBUS-घातered device, the
			 * gadget driver should चयन पूर्णांकo slow घड़ी mode
			 * and then पूर्णांकo standby to aव्योम drawing more than
			 * 500uA घातer (2500uA क्रम some high-घातer configs).
			 */
			अगर (udc->driver && udc->driver->suspend) अणु
				spin_unlock(&udc->lock);
				udc->driver->suspend(&udc->gadget);
				spin_lock(&udc->lock);
			पूर्ण

		/* host initiated resume */
		पूर्ण अन्यथा अगर (status & AT91_UDP_RXRSM) अणु
			at91_udp_ग_लिखो(udc, AT91_UDP_IDR, AT91_UDP_RXRSM);
			at91_udp_ग_लिखो(udc, AT91_UDP_IER, AT91_UDP_RXSUSP);
			at91_udp_ग_लिखो(udc, AT91_UDP_ICR, AT91_UDP_RXRSM);
			/* VDBG("bus resume\n"); */
			अगर (!udc->suspended)
				जारी;
			udc->suspended = 0;

			/*
			 * NOTE:  क्रम a VBUS-घातered device, the gadget driver
			 * would normally want to चयन out of slow घड़ी
			 * mode पूर्णांकo normal mode.
			 */
			अगर (udc->driver && udc->driver->resume) अणु
				spin_unlock(&udc->lock);
				udc->driver->resume(&udc->gadget);
				spin_lock(&udc->lock);
			पूर्ण

		/* endpoपूर्णांक IRQs are cleared by handling them */
		पूर्ण अन्यथा अणु
			पूर्णांक		i;
			अचिन्हित	mask = 1;
			काष्ठा at91_ep	*ep = &udc->ep[1];

			अगर (status & mask)
				handle_ep0(udc);
			क्रम (i = 1; i < NUM_ENDPOINTS; i++) अणु
				mask <<= 1;
				अगर (status & mask)
					handle_ep(ep);
				ep++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (disable_घड़ी)
		clk_off(udc);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम at91_vbus_update(काष्ठा at91_udc *udc, अचिन्हित value)
अणु
	value ^= udc->board.vbus_active_low;
	अगर (value != udc->vbus)
		at91_vbus_session(&udc->gadget, value);
पूर्ण

अटल irqवापस_t at91_vbus_irq(पूर्णांक irq, व्योम *_udc)
अणु
	काष्ठा at91_udc	*udc = _udc;

	/* vbus needs at least brief debouncing */
	udelay(10);
	at91_vbus_update(udc, gpio_get_value(udc->board.vbus_pin));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम at91_vbus_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा at91_udc *udc = container_of(work, काष्ठा at91_udc,
					    vbus_समयr_work);

	at91_vbus_update(udc, gpio_get_value_cansleep(udc->board.vbus_pin));

	अगर (!समयr_pending(&udc->vbus_समयr))
		mod_समयr(&udc->vbus_समयr, jअगरfies + VBUS_POLL_TIMEOUT);
पूर्ण

अटल व्योम at91_vbus_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा at91_udc *udc = from_समयr(udc, t, vbus_समयr);

	/*
	 * If we are polling vbus it is likely that the gpio is on an
	 * bus such as i2c or spi which may sleep, so schedule some work
	 * to पढ़ो the vbus gpio
	 */
	schedule_work(&udc->vbus_समयr_work);
पूर्ण

अटल पूर्णांक at91_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा at91_udc	*udc;

	udc = container_of(gadget, काष्ठा at91_udc, gadget);
	udc->driver = driver;
	udc->gadget.dev.of_node = udc->pdev->dev.of_node;
	udc->enabled = 1;
	udc->gadget.is_selfघातered = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक at91_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा at91_udc *udc;
	अचिन्हित दीर्घ	flags;

	udc = container_of(gadget, काष्ठा at91_udc, gadget);
	spin_lock_irqsave(&udc->lock, flags);
	udc->enabled = 0;
	at91_udp_ग_लिखो(udc, AT91_UDP_IDR, ~0);
	spin_unlock_irqrestore(&udc->lock, flags);

	udc->driver = शून्य;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम at91udc_shutकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा at91_udc *udc = platक्रमm_get_drvdata(dev);
	अचिन्हित दीर्घ	flags;

	/* क्रमce disconnect on reboot */
	spin_lock_irqsave(&udc->lock, flags);
	pullup(platक्रमm_get_drvdata(dev), 0);
	spin_unlock_irqrestore(&udc->lock, flags);
पूर्ण

अटल पूर्णांक at91rm9200_udc_init(काष्ठा at91_udc *udc)
अणु
	काष्ठा at91_ep *ep;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];

		चयन (i) अणु
		हाल 0:
		हाल 3:
			ep->maxpacket = 8;
			अवरोध;
		हाल 1 ... 2:
			ep->maxpacket = 64;
			अवरोध;
		हाल 4 ... 5:
			ep->maxpacket = 256;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!gpio_is_valid(udc->board.pullup_pin)) अणु
		DBG("no D+ pullup?\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_gpio_request(&udc->pdev->dev, udc->board.pullup_pin,
				"udc_pullup");
	अगर (ret) अणु
		DBG("D+ pullup is busy\n");
		वापस ret;
	पूर्ण

	gpio_direction_output(udc->board.pullup_pin,
			      udc->board.pullup_active_low);

	वापस 0;
पूर्ण

अटल व्योम at91rm9200_udc_pullup(काष्ठा at91_udc *udc, पूर्णांक is_on)
अणु
	पूर्णांक active = !udc->board.pullup_active_low;

	अगर (is_on)
		gpio_set_value(udc->board.pullup_pin, active);
	अन्यथा
		gpio_set_value(udc->board.pullup_pin, !active);
पूर्ण

अटल स्थिर काष्ठा at91_udc_caps at91rm9200_udc_caps = अणु
	.init = at91rm9200_udc_init,
	.pullup = at91rm9200_udc_pullup,
पूर्ण;

अटल पूर्णांक at91sam9260_udc_init(काष्ठा at91_udc *udc)
अणु
	काष्ठा at91_ep *ep;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];

		चयन (i) अणु
		हाल 0 ... 3:
			ep->maxpacket = 64;
			अवरोध;
		हाल 4 ... 5:
			ep->maxpacket = 512;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम at91sam9260_udc_pullup(काष्ठा at91_udc *udc, पूर्णांक is_on)
अणु
	u32 txvc = at91_udp_पढ़ो(udc, AT91_UDP_TXVC);

	अगर (is_on)
		txvc |= AT91_UDP_TXVC_PUON;
	अन्यथा
		txvc &= ~AT91_UDP_TXVC_PUON;

	at91_udp_ग_लिखो(udc, AT91_UDP_TXVC, txvc);
पूर्ण

अटल स्थिर काष्ठा at91_udc_caps at91sam9260_udc_caps = अणु
	.init = at91sam9260_udc_init,
	.pullup = at91sam9260_udc_pullup,
पूर्ण;

अटल पूर्णांक at91sam9261_udc_init(काष्ठा at91_udc *udc)
अणु
	काष्ठा at91_ep *ep;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];

		चयन (i) अणु
		हाल 0:
			ep->maxpacket = 8;
			अवरोध;
		हाल 1 ... 3:
			ep->maxpacket = 64;
			अवरोध;
		हाल 4 ... 5:
			ep->maxpacket = 256;
			अवरोध;
		पूर्ण
	पूर्ण

	udc->matrix = syscon_regmap_lookup_by_phandle(udc->pdev->dev.of_node,
						      "atmel,matrix");
	वापस PTR_ERR_OR_ZERO(udc->matrix);
पूर्ण

अटल व्योम at91sam9261_udc_pullup(काष्ठा at91_udc *udc, पूर्णांक is_on)
अणु
	u32 usbpucr = 0;

	अगर (is_on)
		usbpucr = AT91_MATRIX_USBPUCR_PUON;

	regmap_update_bits(udc->matrix, AT91SAM9261_MATRIX_USBPUCR,
			   AT91_MATRIX_USBPUCR_PUON, usbpucr);
पूर्ण

अटल स्थिर काष्ठा at91_udc_caps at91sam9261_udc_caps = अणु
	.init = at91sam9261_udc_init,
	.pullup = at91sam9261_udc_pullup,
पूर्ण;

अटल पूर्णांक at91sam9263_udc_init(काष्ठा at91_udc *udc)
अणु
	काष्ठा at91_ep *ep;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];

		चयन (i) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 3:
			ep->maxpacket = 64;
			अवरोध;
		हाल 4:
		हाल 5:
			ep->maxpacket = 256;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा at91_udc_caps at91sam9263_udc_caps = अणु
	.init = at91sam9263_udc_init,
	.pullup = at91sam9260_udc_pullup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id at91_udc_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91rm9200-udc",
		.data = &at91rm9200_udc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9260-udc",
		.data = &at91sam9260_udc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9261-udc",
		.data = &at91sam9261_udc_caps,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9263-udc",
		.data = &at91sam9263_udc_caps,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_udc_dt_ids);

अटल व्योम at91udc_of_init(काष्ठा at91_udc *udc, काष्ठा device_node *np)
अणु
	काष्ठा at91_udc_data *board = &udc->board;
	स्थिर काष्ठा of_device_id *match;
	क्रमागत of_gpio_flags flags;
	u32 val;

	अगर (of_property_पढ़ो_u32(np, "atmel,vbus-polled", &val) == 0)
		board->vbus_polled = 1;

	board->vbus_pin = of_get_named_gpio_flags(np, "atmel,vbus-gpio", 0,
						  &flags);
	board->vbus_active_low = (flags & OF_GPIO_ACTIVE_LOW) ? 1 : 0;

	board->pullup_pin = of_get_named_gpio_flags(np, "atmel,pullup-gpio", 0,
						  &flags);

	board->pullup_active_low = (flags & OF_GPIO_ACTIVE_LOW) ? 1 : 0;

	match = of_match_node(at91_udc_dt_ids, np);
	अगर (match)
		udc->caps = match->data;
पूर्ण

अटल पूर्णांक at91udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device	*dev = &pdev->dev;
	काष्ठा at91_udc	*udc;
	पूर्णांक		retval;
	काष्ठा at91_ep	*ep;
	पूर्णांक		i;

	udc = devm_kzalloc(dev, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	/* init software state */
	udc->gadget.dev.parent = dev;
	at91udc_of_init(udc, pdev->dev.of_node);
	udc->pdev = pdev;
	udc->enabled = 0;
	spin_lock_init(&udc->lock);

	udc->gadget.ops = &at91_udc_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	udc->gadget.name = driver_name;
	udc->gadget.dev.init_name = "gadget";

	क्रम (i = 0; i < NUM_ENDPOINTS; i++) अणु
		ep = &udc->ep[i];
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &at91_ep_ops;
		ep->udc = udc;
		ep->पूर्णांक_mask = BIT(i);
		अगर (i != 0 && i != 3)
			ep->is_pingpong = 1;
	पूर्ण

	udc->udp_baseaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(udc->udp_baseaddr))
		वापस PTR_ERR(udc->udp_baseaddr);

	अगर (udc->caps && udc->caps->init) अणु
		retval = udc->caps->init(udc);
		अगर (retval)
			वापस retval;
	पूर्ण

	udc_reinit(udc);

	/* get पूर्णांकerface and function घड़ीs */
	udc->iclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(udc->iclk))
		वापस PTR_ERR(udc->iclk);

	udc->fclk = devm_clk_get(dev, "hclk");
	अगर (IS_ERR(udc->fclk))
		वापस PTR_ERR(udc->fclk);

	/* करोn't करो anything until we have both gadget driver and VBUS */
	clk_set_rate(udc->fclk, 48000000);
	retval = clk_prepare(udc->fclk);
	अगर (retval)
		वापस retval;

	retval = clk_prepare_enable(udc->iclk);
	अगर (retval)
		जाओ err_unprepare_fclk;

	at91_udp_ग_लिखो(udc, AT91_UDP_TXVC, AT91_UDP_TXVC_TXVDIS);
	at91_udp_ग_लिखो(udc, AT91_UDP_IDR, 0xffffffff);
	/* Clear all pending पूर्णांकerrupts - UDP may be used by bootloader. */
	at91_udp_ग_लिखो(udc, AT91_UDP_ICR, 0xffffffff);
	clk_disable(udc->iclk);

	/* request UDC and maybe VBUS irqs */
	udc->udp_irq = platक्रमm_get_irq(pdev, 0);
	retval = devm_request_irq(dev, udc->udp_irq, at91_udc_irq, 0,
				  driver_name, udc);
	अगर (retval) अणु
		DBG("request irq %d failed\n", udc->udp_irq);
		जाओ err_unprepare_iclk;
	पूर्ण

	अगर (gpio_is_valid(udc->board.vbus_pin)) अणु
		retval = devm_gpio_request(dev, udc->board.vbus_pin,
					   "udc_vbus");
		अगर (retval) अणु
			DBG("request vbus pin failed\n");
			जाओ err_unprepare_iclk;
		पूर्ण

		gpio_direction_input(udc->board.vbus_pin);

		/*
		 * Get the initial state of VBUS - we cannot expect
		 * a pending पूर्णांकerrupt.
		 */
		udc->vbus = gpio_get_value_cansleep(udc->board.vbus_pin) ^
			udc->board.vbus_active_low;

		अगर (udc->board.vbus_polled) अणु
			INIT_WORK(&udc->vbus_समयr_work, at91_vbus_समयr_work);
			समयr_setup(&udc->vbus_समयr, at91_vbus_समयr, 0);
			mod_समयr(&udc->vbus_समयr,
				  jअगरfies + VBUS_POLL_TIMEOUT);
		पूर्ण अन्यथा अणु
			retval = devm_request_irq(dev,
					gpio_to_irq(udc->board.vbus_pin),
					at91_vbus_irq, 0, driver_name, udc);
			अगर (retval) अणु
				DBG("request vbus irq %d failed\n",
				    udc->board.vbus_pin);
				जाओ err_unprepare_iclk;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		DBG("no VBUS detection, assuming always-on\n");
		udc->vbus = 1;
	पूर्ण
	retval = usb_add_gadget_udc(dev, &udc->gadget);
	अगर (retval)
		जाओ err_unprepare_iclk;
	dev_set_drvdata(dev, udc);
	device_init_wakeup(dev, 1);
	create_debug_file(udc);

	INFO("%s version %s\n", driver_name, DRIVER_VERSION);
	वापस 0;

err_unprepare_iclk:
	clk_unprepare(udc->iclk);
err_unprepare_fclk:
	clk_unprepare(udc->fclk);

	DBG("%s probe failed, %d\n", driver_name, retval);

	वापस retval;
पूर्ण

अटल पूर्णांक at91udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_udc *udc = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ	flags;

	DBG("remove\n");

	usb_del_gadget_udc(&udc->gadget);
	अगर (udc->driver)
		वापस -EBUSY;

	spin_lock_irqsave(&udc->lock, flags);
	pullup(udc, 0);
	spin_unlock_irqrestore(&udc->lock, flags);

	device_init_wakeup(&pdev->dev, 0);
	हटाओ_debug_file(udc);
	clk_unprepare(udc->fclk);
	clk_unprepare(udc->iclk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक at91udc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t mesg)
अणु
	काष्ठा at91_udc *udc = platक्रमm_get_drvdata(pdev);
	पूर्णांक		wake = udc->driver && device_may_wakeup(&pdev->dev);
	अचिन्हित दीर्घ	flags;

	/* Unless we can act normally to the host (letting it wake us up
	 * whenever it has work क्रम us) क्रमce disconnect.  Wakeup requires
	 * PLLB क्रम USB events (संकेतing क्रम reset, wakeup, or incoming
	 * tokens) and VBUS irqs (on प्रणालीs which support them).
	 */
	अगर ((!udc->suspended && udc->addr)
			|| !wake
			|| at91_suspend_entering_slow_घड़ी()) अणु
		spin_lock_irqsave(&udc->lock, flags);
		pullup(udc, 0);
		wake = 0;
		spin_unlock_irqrestore(&udc->lock, flags);
	पूर्ण अन्यथा
		enable_irq_wake(udc->udp_irq);

	udc->active_suspend = wake;
	अगर (gpio_is_valid(udc->board.vbus_pin) && !udc->board.vbus_polled && wake)
		enable_irq_wake(udc->board.vbus_pin);
	वापस 0;
पूर्ण

अटल पूर्णांक at91udc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at91_udc *udc = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ	flags;

	अगर (gpio_is_valid(udc->board.vbus_pin) && !udc->board.vbus_polled &&
	    udc->active_suspend)
		disable_irq_wake(udc->board.vbus_pin);

	/* maybe reconnect to host; अगर so, घड़ीs on */
	अगर (udc->active_suspend)
		disable_irq_wake(udc->udp_irq);
	अन्यथा अणु
		spin_lock_irqsave(&udc->lock, flags);
		pullup(udc, 1);
		spin_unlock_irqrestore(&udc->lock, flags);
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा	at91udc_suspend	शून्य
#घोषणा	at91udc_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver at91_udc_driver = अणु
	.हटाओ		= at91udc_हटाओ,
	.shutकरोwn	= at91udc_shutकरोwn,
	.suspend	= at91udc_suspend,
	.resume		= at91udc_resume,
	.driver		= अणु
		.name	= driver_name,
		.of_match_table	= at91_udc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(at91_udc_driver, at91udc_probe);

MODULE_DESCRIPTION("AT91 udc driver");
MODULE_AUTHOR("Thomas Rathbone, David Brownell");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:at91_udc");
