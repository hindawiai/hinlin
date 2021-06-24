<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG driver host support
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 * Copyright (C) 2008-2009 MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/dma-mapping.h>

#समावेश "musb_core.h"
#समावेश "musb_host.h"
#समावेश "musb_trace.h"

/* MUSB HOST status 22-mar-2006
 *
 * - There's still lots of partial code duplication क्रम fault paths, so
 *   they aren't handled as consistently as they need to be.
 *
 * - PIO mostly behaved when last tested.
 *     + including ep0, with all usbtest हालs 9, 10
 *     + usbtest 14 (ep0out) करोesn't seem to run at all
 *     + द्विगुन buffered OUT/TX endpoपूर्णांकs saw stalls(!) with certain usbtest
 *       configurations, but otherwise द्विगुन buffering passes basic tests.
 *     + क्रम 2.6.N, क्रम N > ~10, needs API changes क्रम hcd framework.
 *
 * - DMA (CPPI) ... partially behaves, not currently recommended
 *     + about 1/15 the speed of typical EHCI implementations (PCI)
 *     + RX, all too often reqpkt seems to misbehave after tx
 *     + TX, no known issues (other than evident silicon issue)
 *
 * - DMA (Mentor/OMAP) ...has at least toggle update problems
 *
 * - [23-feb-2009] minimal traffic scheduling to aव्योम bulk RX packet
 *   starvation ... nothing yet क्रम TX, पूर्णांकerrupt, or bulk.
 *
 * - Not tested with HNP, but some SRP paths seem to behave.
 *
 * NOTE 24-August-2006:
 *
 * - Bulk traffic finally uses both sides of hardware ep1, मुक्तing up an
 *   extra endpoपूर्णांक क्रम periodic use enabling hub + keybd + mouse.  That
 *   mostly works, except that with "usbnet" it's easy to trigger हालs
 *   with "ping" where RX loses.  (a) ping to davinci, even "ping -f",
 *   fine; but (b) ping _from_ davinci, even "ping -c 1", ICMP RX loses
 *   although ARP RX wins.  (That test was करोne with a full speed link.)
 */


/*
 * NOTE on endpoपूर्णांक usage:
 *
 * CONTROL transfers all go through ep0.  BULK ones go through dedicated IN
 * and OUT endpoपूर्णांकs ... hardware is dedicated क्रम those "async" queue(s).
 * (Yes, bulk _could_ use more of the endpoपूर्णांकs than that, and would even
 * benefit from it.)
 *
 * INTERUPPT and ISOCHRONOUS transfers are scheduled to the other endpoपूर्णांकs.
 * So far that scheduling is both dumb and optimistic:  the endpoपूर्णांक will be
 * "claimed" until its software queue is no दीर्घer refilled.  No multiplexing
 * of transfers between endpoपूर्णांकs, or anything clever.
 */

काष्ठा musb *hcd_to_musb(काष्ठा usb_hcd *hcd)
अणु
	वापस *(काष्ठा musb **) hcd->hcd_priv;
पूर्ण


अटल व्योम musb_ep_program(काष्ठा musb *musb, u8 epnum,
			काष्ठा urb *urb, पूर्णांक is_out,
			u8 *buf, u32 offset, u32 len);

/*
 * Clear TX fअगरo. Needed to aव्योम BABBLE errors.
 */
अटल व्योम musb_h_tx_flush_fअगरo(काष्ठा musb_hw_ep *ep)
अणु
	काष्ठा musb	*musb = ep->musb;
	व्योम __iomem	*epio = ep->regs;
	u16		csr;
	पूर्णांक		retries = 1000;

	csr = musb_पढ़ोw(epio, MUSB_TXCSR);
	जबतक (csr & MUSB_TXCSR_FIFONOTEMPTY) अणु
		csr |= MUSB_TXCSR_FLUSHFIFO | MUSB_TXCSR_TXPKTRDY;
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);

		/*
		 * FIXME: someबार the tx fअगरo flush failed, it has been
		 * observed during device disconnect on AM335x.
		 *
		 * To reproduce the issue, ensure tx urb(s) are queued when
		 * unplug the usb device which is connected to AM335x usb
		 * host port.
		 *
		 * I found using a usb-ethernet device and running iperf
		 * (client on AM335x) has very high chance to trigger it.
		 *
		 * Better to turn on musb_dbg() in musb_cleanup_urb() with
		 * CPPI enabled to see the issue when पातing the tx channel.
		 */
		अगर (dev_WARN_ONCE(musb->controller, retries-- < 1,
				"Could not flush host TX%d fifo: csr: %04x\n",
				ep->epnum, csr))
			वापस;
		mdelay(1);
	पूर्ण
पूर्ण

अटल व्योम musb_h_ep0_flush_fअगरo(काष्ठा musb_hw_ep *ep)
अणु
	व्योम __iomem	*epio = ep->regs;
	u16		csr;
	पूर्णांक		retries = 5;

	/* scrub any data left in the fअगरo */
	करो अणु
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		अगर (!(csr & (MUSB_CSR0_TXPKTRDY | MUSB_CSR0_RXPKTRDY)))
			अवरोध;
		musb_ग_लिखोw(epio, MUSB_TXCSR, MUSB_CSR0_FLUSHFIFO);
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		udelay(10);
	पूर्ण जबतक (--retries);

	WARN(!retries, "Could not flush host TX%d fifo: csr: %04x\n",
			ep->epnum, csr);

	/* and reset क्रम the next transfer */
	musb_ग_लिखोw(epio, MUSB_TXCSR, 0);
पूर्ण

/*
 * Start transmit. Caller is responsible क्रम locking shared resources.
 * musb must be locked.
 */
अटल अंतरभूत व्योम musb_h_tx_start(काष्ठा musb_hw_ep *ep)
अणु
	u16	txcsr;

	/* NOTE: no locks here; caller should lock and select EP */
	अगर (ep->epnum) अणु
		txcsr = musb_पढ़ोw(ep->regs, MUSB_TXCSR);
		txcsr |= MUSB_TXCSR_TXPKTRDY | MUSB_TXCSR_H_WZC_BITS;
		musb_ग_लिखोw(ep->regs, MUSB_TXCSR, txcsr);
	पूर्ण अन्यथा अणु
		txcsr = MUSB_CSR0_H_SETUPPKT | MUSB_CSR0_TXPKTRDY;
		musb_ग_लिखोw(ep->regs, MUSB_CSR0, txcsr);
	पूर्ण

पूर्ण

अटल अंतरभूत व्योम musb_h_tx_dma_start(काष्ठा musb_hw_ep *ep)
अणु
	u16	txcsr;

	/* NOTE: no locks here; caller should lock and select EP */
	txcsr = musb_पढ़ोw(ep->regs, MUSB_TXCSR);
	txcsr |= MUSB_TXCSR_DMAENAB | MUSB_TXCSR_H_WZC_BITS;
	अगर (is_cppi_enabled(ep->musb))
		txcsr |= MUSB_TXCSR_DMAMODE;
	musb_ग_लिखोw(ep->regs, MUSB_TXCSR, txcsr);
पूर्ण

अटल व्योम musb_ep_set_qh(काष्ठा musb_hw_ep *ep, पूर्णांक is_in, काष्ठा musb_qh *qh)
अणु
	अगर (is_in != 0 || ep->is_shared_fअगरo)
		ep->in_qh  = qh;
	अगर (is_in == 0 || ep->is_shared_fअगरo)
		ep->out_qh = qh;
पूर्ण

अटल काष्ठा musb_qh *musb_ep_get_qh(काष्ठा musb_hw_ep *ep, पूर्णांक is_in)
अणु
	वापस is_in ? ep->in_qh : ep->out_qh;
पूर्ण

/*
 * Start the URB at the front of an endpoपूर्णांक's queue
 * end must be claimed from the caller.
 *
 * Context: controller locked, irqs blocked
 */
अटल व्योम
musb_start_urb(काष्ठा musb *musb, पूर्णांक is_in, काष्ठा musb_qh *qh)
अणु
	u32			len;
	व्योम __iomem		*mbase =  musb->mregs;
	काष्ठा urb		*urb = next_urb(qh);
	व्योम			*buf = urb->transfer_buffer;
	u32			offset = 0;
	काष्ठा musb_hw_ep	*hw_ep = qh->hw_ep;
	पूर्णांक			epnum = hw_ep->epnum;

	/* initialize software qh state */
	qh->offset = 0;
	qh->segsize = 0;

	/* gather right source of data */
	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		/* control transfers always start with SETUP */
		is_in = 0;
		musb->ep0_stage = MUSB_EP0_START;
		buf = urb->setup_packet;
		len = 8;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		qh->iso_idx = 0;
		qh->frame = 0;
		offset = urb->iso_frame_desc[0].offset;
		len = urb->iso_frame_desc[0].length;
		अवरोध;
	शेष:		/* bulk, पूर्णांकerrupt */
		/* actual_length may be nonzero on retry paths */
		buf = urb->transfer_buffer + urb->actual_length;
		len = urb->transfer_buffer_length - urb->actual_length;
	पूर्ण

	trace_musb_urb_start(musb, urb);

	/* Configure endpoपूर्णांक */
	musb_ep_set_qh(hw_ep, is_in, qh);
	musb_ep_program(musb, epnum, urb, !is_in, buf, offset, len);

	/* transmit may have more work: start it when it is समय */
	अगर (is_in)
		वापस;

	/* determine अगर the समय is right क्रम a periodic transfer */
	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_ISOC:
	हाल USB_ENDPOINT_XFER_INT:
		musb_dbg(musb, "check whether there's still time for periodic Tx");
		/* FIXME this करोesn't implement that scheduling policy ...
		 * or handle framecounter wrapping
		 */
		अगर (1) अणु	/* Always assume URB_ISO_ASAP */
			/* REVISIT the SOF irq handler shouldn't duplicate
			 * this code; and we करोn't init urb->start_frame...
			 */
			qh->frame = 0;
			जाओ start;
		पूर्ण अन्यथा अणु
			qh->frame = urb->start_frame;
			/* enable SOF पूर्णांकerrupt so we can count करोwn */
			musb_dbg(musb, "SOF for %d", epnum);
#अगर 1 /* अगरndef	CONFIG_ARCH_DAVINCI */
			musb_ग_लिखोb(mbase, MUSB_INTRUSBE, 0xff);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	शेष:
start:
		musb_dbg(musb, "Start TX%d %s", epnum,
			hw_ep->tx_channel ? "dma" : "pio");

		अगर (!hw_ep->tx_channel)
			musb_h_tx_start(hw_ep);
		अन्यथा अगर (is_cppi_enabled(musb) || tusb_dma_omap(musb))
			musb_h_tx_dma_start(hw_ep);
	पूर्ण
पूर्ण

/* Context: caller owns controller lock, IRQs are blocked */
अटल व्योम musb_giveback(काष्ठा musb *musb, काष्ठा urb *urb, पूर्णांक status)
__releases(musb->lock)
__acquires(musb->lock)
अणु
	trace_musb_urb_gb(musb, urb);

	usb_hcd_unlink_urb_from_ep(musb->hcd, urb);
	spin_unlock(&musb->lock);
	usb_hcd_giveback_urb(musb->hcd, urb, status);
	spin_lock(&musb->lock);
पूर्ण

/*
 * Advance this hardware endpoपूर्णांक's queue, completing the specअगरied URB and
 * advancing to either the next URB queued to that qh, or अन्यथा invalidating
 * that qh and advancing to the next qh scheduled after the current one.
 *
 * Context: caller owns controller lock, IRQs are blocked
 */
अटल व्योम musb_advance_schedule(काष्ठा musb *musb, काष्ठा urb *urb,
				  काष्ठा musb_hw_ep *hw_ep, पूर्णांक is_in)
अणु
	काष्ठा musb_qh		*qh = musb_ep_get_qh(hw_ep, is_in);
	काष्ठा musb_hw_ep	*ep = qh->hw_ep;
	पूर्णांक			पढ़ोy = qh->is_पढ़ोy;
	पूर्णांक			status;
	u16			toggle;

	status = (urb->status == -EINPROGRESS) ? 0 : urb->status;

	/* save toggle eagerly, क्रम paranoia */
	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		toggle = musb->io.get_toggle(qh, !is_in);
		usb_settoggle(urb->dev, qh->epnum, !is_in, toggle ? 1 : 0);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (status == 0 && urb->error_count)
			status = -EXDEV;
		अवरोध;
	पूर्ण

	qh->is_पढ़ोy = 0;
	musb_giveback(musb, urb, status);
	qh->is_पढ़ोy = पढ़ोy;

	/* reclaim resources (and bandwidth) ASAP; deschedule it, and
	 * invalidate qh as soon as list_empty(&hep->urb_list)
	 */
	अगर (list_empty(&qh->hep->urb_list)) अणु
		काष्ठा list_head	*head;
		काष्ठा dma_controller	*dma = musb->dma_controller;

		अगर (is_in) अणु
			ep->rx_reinit = 1;
			अगर (ep->rx_channel) अणु
				dma->channel_release(ep->rx_channel);
				ep->rx_channel = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			ep->tx_reinit = 1;
			अगर (ep->tx_channel) अणु
				dma->channel_release(ep->tx_channel);
				ep->tx_channel = शून्य;
			पूर्ण
		पूर्ण

		/* Clobber old poपूर्णांकers to this qh */
		musb_ep_set_qh(ep, is_in, शून्य);
		qh->hep->hcpriv = शून्य;

		चयन (qh->type) अणु

		हाल USB_ENDPOINT_XFER_CONTROL:
		हाल USB_ENDPOINT_XFER_BULK:
			/* fअगरo policy क्रम these lists, except that NAKing
			 * should rotate a qh to the end (क्रम fairness).
			 */
			अगर (qh->mux == 1) अणु
				head = qh->ring.prev;
				list_del(&qh->ring);
				kमुक्त(qh);
				qh = first_qh(head);
				अवरोध;
			पूर्ण
			fallthrough;

		हाल USB_ENDPOINT_XFER_ISOC:
		हाल USB_ENDPOINT_XFER_INT:
			/* this is where periodic bandwidth should be
			 * de-allocated अगर it's tracked and allocated;
			 * and where we'd update the schedule tree...
			 */
			kमुक्त(qh);
			qh = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (qh != शून्य && qh->is_पढ़ोy) अणु
		musb_dbg(musb, "... next ep%d %cX urb %p",
		    hw_ep->epnum, is_in ? 'R' : 'T', next_urb(qh));
		musb_start_urb(musb, is_in, qh);
	पूर्ण
पूर्ण

अटल u16 musb_h_flush_rxfअगरo(काष्ठा musb_hw_ep *hw_ep, u16 csr)
अणु
	/* we करोn't want fअगरo to fill itself again;
	 * ignore dma (various models),
	 * leave toggle alone (may not have been saved yet)
	 */
	csr |= MUSB_RXCSR_FLUSHFIFO | MUSB_RXCSR_RXPKTRDY;
	csr &= ~(MUSB_RXCSR_H_REQPKT
		| MUSB_RXCSR_H_AUTOREQ
		| MUSB_RXCSR_AUTOCLEAR);

	/* ग_लिखो 2x to allow द्विगुन buffering */
	musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR, csr);
	musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR, csr);

	/* flush ग_लिखोbuffer */
	वापस musb_पढ़ोw(hw_ep->regs, MUSB_RXCSR);
पूर्ण

/*
 * PIO RX क्रम a packet (or part of it).
 */
अटल bool
musb_host_packet_rx(काष्ठा musb *musb, काष्ठा urb *urb, u8 epnum, u8 iso_err)
अणु
	u16			rx_count;
	u8			*buf;
	u16			csr;
	bool			करोne = false;
	u32			length;
	पूर्णांक			करो_flush = 0;
	काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs + epnum;
	व्योम __iomem		*epio = hw_ep->regs;
	काष्ठा musb_qh		*qh = hw_ep->in_qh;
	पूर्णांक			pipe = urb->pipe;
	व्योम			*buffer = urb->transfer_buffer;

	/* musb_ep_select(mbase, epnum); */
	rx_count = musb_पढ़ोw(epio, MUSB_RXCOUNT);
	musb_dbg(musb, "RX%d count %d, buffer %p len %d/%d", epnum, rx_count,
			urb->transfer_buffer, qh->offset,
			urb->transfer_buffer_length);

	/* unload FIFO */
	अगर (usb_pipeisoc(pipe)) अणु
		पूर्णांक					status = 0;
		काष्ठा usb_iso_packet_descriptor	*d;

		अगर (iso_err) अणु
			status = -EILSEQ;
			urb->error_count++;
		पूर्ण

		d = urb->iso_frame_desc + qh->iso_idx;
		buf = buffer + d->offset;
		length = d->length;
		अगर (rx_count > length) अणु
			अगर (status == 0) अणु
				status = -EOVERFLOW;
				urb->error_count++;
			पूर्ण
			musb_dbg(musb, "OVERFLOW %d into %d", rx_count, length);
			करो_flush = 1;
		पूर्ण अन्यथा
			length = rx_count;
		urb->actual_length += length;
		d->actual_length = length;

		d->status = status;

		/* see अगर we are करोne */
		करोne = (++qh->iso_idx >= urb->number_of_packets);
	पूर्ण अन्यथा अणु
		/* non-isoch */
		buf = buffer + qh->offset;
		length = urb->transfer_buffer_length - qh->offset;
		अगर (rx_count > length) अणु
			अगर (urb->status == -EINPROGRESS)
				urb->status = -EOVERFLOW;
			musb_dbg(musb, "OVERFLOW %d into %d", rx_count, length);
			करो_flush = 1;
		पूर्ण अन्यथा
			length = rx_count;
		urb->actual_length += length;
		qh->offset += length;

		/* see अगर we are करोne */
		करोne = (urb->actual_length == urb->transfer_buffer_length)
			|| (rx_count < qh->maxpacket)
			|| (urb->status != -EINPROGRESS);
		अगर (करोne
				&& (urb->status == -EINPROGRESS)
				&& (urb->transfer_flags & URB_SHORT_NOT_OK)
				&& (urb->actual_length
					< urb->transfer_buffer_length))
			urb->status = -EREMOTEIO;
	पूर्ण

	musb_पढ़ो_fअगरo(hw_ep, length, buf);

	csr = musb_पढ़ोw(epio, MUSB_RXCSR);
	csr |= MUSB_RXCSR_H_WZC_BITS;
	अगर (unlikely(करो_flush))
		musb_h_flush_rxfअगरo(hw_ep, csr);
	अन्यथा अणु
		/* REVISIT this assumes AUTOCLEAR is never set */
		csr &= ~(MUSB_RXCSR_RXPKTRDY | MUSB_RXCSR_H_REQPKT);
		अगर (!करोne)
			csr |= MUSB_RXCSR_H_REQPKT;
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
	पूर्ण

	वापस करोne;
पूर्ण

/* we करोn't always need to reinit a given side of an endpoपूर्णांक...
 * when we करो, use tx/rx reinit routine and then स्थिरruct a new CSR
 * to address data toggle, NYET, and DMA or PIO.
 *
 * it's possible that driver bugs (especially क्रम DMA) or पातing a
 * transfer might have left the endpoपूर्णांक busier than it should be.
 * the busy/not-empty tests are basically paranoia.
 */
अटल व्योम
musb_rx_reinit(काष्ठा musb *musb, काष्ठा musb_qh *qh, u8 epnum)
अणु
	काष्ठा musb_hw_ep *ep = musb->endpoपूर्णांकs + epnum;
	u16	csr;

	/* NOTE:  we know the "rx" fअगरo reinit never triggers क्रम ep0.
	 * That always uses tx_reinit since ep0 repurposes TX रेजिस्टर
	 * offsets; the initial SETUP packet is also a kind of OUT.
	 */

	/* अगर programmed क्रम Tx, put it in RX mode */
	अगर (ep->is_shared_fअगरo) अणु
		csr = musb_पढ़ोw(ep->regs, MUSB_TXCSR);
		अगर (csr & MUSB_TXCSR_MODE) अणु
			musb_h_tx_flush_fअगरo(ep);
			csr = musb_पढ़ोw(ep->regs, MUSB_TXCSR);
			musb_ग_लिखोw(ep->regs, MUSB_TXCSR,
				    csr | MUSB_TXCSR_FRCDATATOG);
		पूर्ण

		/*
		 * Clear the MODE bit (and everything अन्यथा) to enable Rx.
		 * NOTE: we mustn't clear the DMAMODE bit beक्रमe DMAENAB.
		 */
		अगर (csr & MUSB_TXCSR_DMAMODE)
			musb_ग_लिखोw(ep->regs, MUSB_TXCSR, MUSB_TXCSR_DMAMODE);
		musb_ग_लिखोw(ep->regs, MUSB_TXCSR, 0);

	/* scrub all previous state, clearing toggle */
	पूर्ण
	csr = musb_पढ़ोw(ep->regs, MUSB_RXCSR);
	अगर (csr & MUSB_RXCSR_RXPKTRDY)
		WARNING("rx%d, packet/%d ready?\n", ep->epnum,
			musb_पढ़ोw(ep->regs, MUSB_RXCOUNT));

	musb_h_flush_rxfअगरo(ep, MUSB_RXCSR_CLRDATATOG);

	/* target addr and (क्रम multipoपूर्णांक) hub addr/port */
	अगर (musb->is_multipoपूर्णांक) अणु
		musb_ग_लिखो_rxfunaddr(musb, epnum, qh->addr_reg);
		musb_ग_लिखो_rxhubaddr(musb, epnum, qh->h_addr_reg);
		musb_ग_लिखो_rxhubport(musb, epnum, qh->h_port_reg);
	पूर्ण अन्यथा
		musb_ग_लिखोb(musb->mregs, MUSB_FADDR, qh->addr_reg);

	/* protocol/endpoपूर्णांक, पूर्णांकerval/NAKlimit, i/o size */
	musb_ग_लिखोb(ep->regs, MUSB_RXTYPE, qh->type_reg);
	musb_ग_लिखोb(ep->regs, MUSB_RXINTERVAL, qh->पूर्णांकv_reg);
	/* NOTE: bulk combining reग_लिखोs high bits of maxpacket */
	/* Set RXMAXP with the FIFO size of the endpoपूर्णांक
	 * to disable द्विगुन buffer mode.
	 */
	musb_ग_लिखोw(ep->regs, MUSB_RXMAXP,
			qh->maxpacket | ((qh->hb_mult - 1) << 11));

	ep->rx_reinit = 0;
पूर्ण

अटल व्योम musb_tx_dma_set_mode_mentor(काष्ठा dma_controller *dma,
		काष्ठा musb_hw_ep *hw_ep, काष्ठा musb_qh *qh,
		काष्ठा urb *urb, u32 offset,
		u32 *length, u8 *mode)
अणु
	काष्ठा dma_channel	*channel = hw_ep->tx_channel;
	व्योम __iomem		*epio = hw_ep->regs;
	u16			pkt_size = qh->maxpacket;
	u16			csr;

	अगर (*length > channel->max_len)
		*length = channel->max_len;

	csr = musb_पढ़ोw(epio, MUSB_TXCSR);
	अगर (*length > pkt_size) अणु
		*mode = 1;
		csr |= MUSB_TXCSR_DMAMODE | MUSB_TXCSR_DMAENAB;
		/* स्वतःset shouldn't be set in high bandwidth */
		/*
		 * Enable Autoset according to table
		 * below
		 * bulk_split hb_mult	Autoset_Enable
		 *	0	1	Yes(Normal)
		 *	0	>1	No(High BW ISO)
		 *	1	1	Yes(HS bulk)
		 *	1	>1	Yes(FS bulk)
		 */
		अगर (qh->hb_mult == 1 || (qh->hb_mult > 1 &&
					can_bulk_split(hw_ep->musb, qh->type)))
			csr |= MUSB_TXCSR_AUTOSET;
	पूर्ण अन्यथा अणु
		*mode = 0;
		csr &= ~(MUSB_TXCSR_AUTOSET | MUSB_TXCSR_DMAMODE);
		csr |= MUSB_TXCSR_DMAENAB; /* against programmer's guide */
	पूर्ण
	channel->desired_mode = *mode;
	musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
पूर्ण

अटल व्योम musb_tx_dma_set_mode_cppi_tusb(काष्ठा dma_controller *dma,
					   काष्ठा musb_hw_ep *hw_ep,
					   काष्ठा musb_qh *qh,
					   काष्ठा urb *urb,
					   u32 offset,
					   u32 *length,
					   u8 *mode)
अणु
	काष्ठा dma_channel *channel = hw_ep->tx_channel;

	channel->actual_len = 0;

	/*
	 * TX uses "RNDIS" mode स्वतःmatically but needs help
	 * to identअगरy the zero-length-final-packet हाल.
	 */
	*mode = (urb->transfer_flags & URB_ZERO_PACKET) ? 1 : 0;
पूर्ण

अटल bool musb_tx_dma_program(काष्ठा dma_controller *dma,
		काष्ठा musb_hw_ep *hw_ep, काष्ठा musb_qh *qh,
		काष्ठा urb *urb, u32 offset, u32 length)
अणु
	काष्ठा dma_channel	*channel = hw_ep->tx_channel;
	u16			pkt_size = qh->maxpacket;
	u8			mode;

	अगर (musb_dma_inventra(hw_ep->musb) || musb_dma_ux500(hw_ep->musb))
		musb_tx_dma_set_mode_mentor(dma, hw_ep, qh, urb, offset,
					    &length, &mode);
	अन्यथा अगर (is_cppi_enabled(hw_ep->musb) || tusb_dma_omap(hw_ep->musb))
		musb_tx_dma_set_mode_cppi_tusb(dma, hw_ep, qh, urb, offset,
					       &length, &mode);
	अन्यथा
		वापस false;

	qh->segsize = length;

	/*
	 * Ensure the data reaches to मुख्य memory beक्रमe starting
	 * DMA transfer
	 */
	wmb();

	अगर (!dma->channel_program(channel, pkt_size, mode,
			urb->transfer_dma + offset, length)) अणु
		व्योम __iomem *epio = hw_ep->regs;
		u16 csr;

		dma->channel_release(channel);
		hw_ep->tx_channel = शून्य;

		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		csr &= ~(MUSB_TXCSR_AUTOSET | MUSB_TXCSR_DMAENAB);
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr | MUSB_TXCSR_H_WZC_BITS);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Program an HDRC endpoपूर्णांक as per the given URB
 * Context: irqs blocked, controller lock held
 */
अटल व्योम musb_ep_program(काष्ठा musb *musb, u8 epnum,
			काष्ठा urb *urb, पूर्णांक is_out,
			u8 *buf, u32 offset, u32 len)
अणु
	काष्ठा dma_controller	*dma_controller;
	काष्ठा dma_channel	*dma_channel;
	u8			dma_ok;
	व्योम __iomem		*mbase = musb->mregs;
	काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs + epnum;
	व्योम __iomem		*epio = hw_ep->regs;
	काष्ठा musb_qh		*qh = musb_ep_get_qh(hw_ep, !is_out);
	u16			packet_sz = qh->maxpacket;
	u8			use_dma = 1;
	u16			csr;

	musb_dbg(musb, "%s hw%d urb %p spd%d dev%d ep%d%s "
				"h_addr%02x h_port%02x bytes %d",
			is_out ? "-->" : "<--",
			epnum, urb, urb->dev->speed,
			qh->addr_reg, qh->epnum, is_out ? "out" : "in",
			qh->h_addr_reg, qh->h_port_reg,
			len);

	musb_ep_select(mbase, epnum);

	अगर (is_out && !len) अणु
		use_dma = 0;
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		csr &= ~MUSB_TXCSR_DMAENAB;
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		hw_ep->tx_channel = शून्य;
	पूर्ण

	/* candidate क्रम DMA? */
	dma_controller = musb->dma_controller;
	अगर (use_dma && is_dma_capable() && epnum && dma_controller) अणु
		dma_channel = is_out ? hw_ep->tx_channel : hw_ep->rx_channel;
		अगर (!dma_channel) अणु
			dma_channel = dma_controller->channel_alloc(
					dma_controller, hw_ep, is_out);
			अगर (is_out)
				hw_ep->tx_channel = dma_channel;
			अन्यथा
				hw_ep->rx_channel = dma_channel;
		पूर्ण
	पूर्ण अन्यथा
		dma_channel = शून्य;

	/* make sure we clear DMAEnab, स्वतःSet bits from previous run */

	/* OUT/transmit/EP0 or IN/receive? */
	अगर (is_out) अणु
		u16	csr;
		u16	पूर्णांक_txe;
		u16	load_count;

		csr = musb_पढ़ोw(epio, MUSB_TXCSR);

		/* disable पूर्णांकerrupt in हाल we flush */
		पूर्णांक_txe = musb->पूर्णांकrtxe;
		musb_ग_लिखोw(mbase, MUSB_INTRTXE, पूर्णांक_txe & ~(1 << epnum));

		/* general endpoपूर्णांक setup */
		अगर (epnum) अणु
			/* flush all old state, set शेष */
			/*
			 * We could be flushing valid
			 * packets in द्विगुन buffering
			 * हाल
			 */
			अगर (!hw_ep->tx_द्विगुन_buffered)
				musb_h_tx_flush_fअगरo(hw_ep);

			/*
			 * We must not clear the DMAMODE bit beक्रमe or in
			 * the same cycle with the DMAENAB bit, so we clear
			 * the latter first...
			 */
			csr &= ~(MUSB_TXCSR_H_NAKTIMEOUT
					| MUSB_TXCSR_AUTOSET
					| MUSB_TXCSR_DMAENAB
					| MUSB_TXCSR_FRCDATATOG
					| MUSB_TXCSR_H_RXSTALL
					| MUSB_TXCSR_H_ERROR
					| MUSB_TXCSR_TXPKTRDY
					);
			csr |= MUSB_TXCSR_MODE;

			अगर (!hw_ep->tx_द्विगुन_buffered)
				csr |= musb->io.set_toggle(qh, is_out, urb);

			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
			/* REVISIT may need to clear FLUSHFIFO ... */
			csr &= ~MUSB_TXCSR_DMAMODE;
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
			csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		पूर्ण अन्यथा अणु
			/* endpoपूर्णांक 0: just flush */
			musb_h_ep0_flush_fअगरo(hw_ep);
		पूर्ण

		/* target addr and (क्रम multipoपूर्णांक) hub addr/port */
		अगर (musb->is_multipoपूर्णांक) अणु
			musb_ग_लिखो_txfunaddr(musb, epnum, qh->addr_reg);
			musb_ग_लिखो_txhubaddr(musb, epnum, qh->h_addr_reg);
			musb_ग_लिखो_txhubport(musb, epnum, qh->h_port_reg);
/* FIXME अगर !epnum, करो the same क्रम RX ... */
		पूर्ण अन्यथा
			musb_ग_लिखोb(mbase, MUSB_FADDR, qh->addr_reg);

		/* protocol/endpoपूर्णांक/पूर्णांकerval/NAKlimit */
		अगर (epnum) अणु
			musb_ग_लिखोb(epio, MUSB_TXTYPE, qh->type_reg);
			अगर (can_bulk_split(musb, qh->type)) अणु
				qh->hb_mult = hw_ep->max_packet_sz_tx
						/ packet_sz;
				musb_ग_लिखोw(epio, MUSB_TXMAXP, packet_sz
					| ((qh->hb_mult) - 1) << 11);
			पूर्ण अन्यथा अणु
				musb_ग_लिखोw(epio, MUSB_TXMAXP,
						qh->maxpacket |
						((qh->hb_mult - 1) << 11));
			पूर्ण
			musb_ग_लिखोb(epio, MUSB_TXINTERVAL, qh->पूर्णांकv_reg);
		पूर्ण अन्यथा अणु
			musb_ग_लिखोb(epio, MUSB_NAKLIMIT0, qh->पूर्णांकv_reg);
			अगर (musb->is_multipoपूर्णांक)
				musb_ग_लिखोb(epio, MUSB_TYPE0,
						qh->type_reg);
		पूर्ण

		अगर (can_bulk_split(musb, qh->type))
			load_count = min((u32) hw_ep->max_packet_sz_tx,
						len);
		अन्यथा
			load_count = min((u32) packet_sz, len);

		अगर (dma_channel && musb_tx_dma_program(dma_controller,
					hw_ep, qh, urb, offset, len))
			load_count = 0;

		अगर (load_count) अणु
			/* PIO to load FIFO */
			qh->segsize = load_count;
			अगर (!buf) अणु
				sg_miter_start(&qh->sg_miter, urb->sg, 1,
						SG_MITER_ATOMIC
						| SG_MITER_FROM_SG);
				अगर (!sg_miter_next(&qh->sg_miter)) अणु
					dev_err(musb->controller,
							"error: sg"
							"list empty\n");
					sg_miter_stop(&qh->sg_miter);
					जाओ finish;
				पूर्ण
				buf = qh->sg_miter.addr + urb->sg->offset +
					urb->actual_length;
				load_count = min_t(u32, load_count,
						qh->sg_miter.length);
				musb_ग_लिखो_fअगरo(hw_ep, load_count, buf);
				qh->sg_miter.consumed = load_count;
				sg_miter_stop(&qh->sg_miter);
			पूर्ण अन्यथा
				musb_ग_लिखो_fअगरo(hw_ep, load_count, buf);
		पूर्ण
finish:
		/* re-enable पूर्णांकerrupt */
		musb_ग_लिखोw(mbase, MUSB_INTRTXE, पूर्णांक_txe);

	/* IN/receive */
	पूर्ण अन्यथा अणु
		u16 csr = 0;

		अगर (hw_ep->rx_reinit) अणु
			musb_rx_reinit(musb, qh, epnum);
			csr |= musb->io.set_toggle(qh, is_out, urb);

			अगर (qh->type == USB_ENDPOINT_XFER_INT)
				csr |= MUSB_RXCSR_DISNYET;

		पूर्ण अन्यथा अणु
			csr = musb_पढ़ोw(hw_ep->regs, MUSB_RXCSR);

			अगर (csr & (MUSB_RXCSR_RXPKTRDY
					| MUSB_RXCSR_DMAENAB
					| MUSB_RXCSR_H_REQPKT))
				ERR("broken !rx_reinit, ep%d csr %04x\n",
						hw_ep->epnum, csr);

			/* scrub any stale state, leaving toggle alone */
			csr &= MUSB_RXCSR_DISNYET;
		पूर्ण

		/* kick things off */

		अगर ((is_cppi_enabled(musb) || tusb_dma_omap(musb)) && dma_channel) अणु
			/* Candidate क्रम DMA */
			dma_channel->actual_len = 0L;
			qh->segsize = len;

			/* AUTOREQ is in a DMA रेजिस्टर */
			musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR, csr);
			csr = musb_पढ़ोw(hw_ep->regs, MUSB_RXCSR);

			/*
			 * Unless caller treats लघु RX transfers as
			 * errors, we dare not queue multiple transfers.
			 */
			dma_ok = dma_controller->channel_program(dma_channel,
					packet_sz, !(urb->transfer_flags &
						     URB_SHORT_NOT_OK),
					urb->transfer_dma + offset,
					qh->segsize);
			अगर (!dma_ok) अणु
				dma_controller->channel_release(dma_channel);
				hw_ep->rx_channel = dma_channel = शून्य;
			पूर्ण अन्यथा
				csr |= MUSB_RXCSR_DMAENAB;
		पूर्ण

		csr |= MUSB_RXCSR_H_REQPKT;
		musb_dbg(musb, "RXCSR%d := %04x", epnum, csr);
		musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR, csr);
		csr = musb_पढ़ोw(hw_ep->regs, MUSB_RXCSR);
	पूर्ण
पूर्ण

/* Schedule next QH from musb->in_bulk/out_bulk and move the current qh to
 * the end; aव्योमs starvation क्रम other endpoपूर्णांकs.
 */
अटल व्योम musb_bulk_nak_समयout(काष्ठा musb *musb, काष्ठा musb_hw_ep *ep,
	पूर्णांक is_in)
अणु
	काष्ठा dma_channel	*dma;
	काष्ठा urb		*urb;
	व्योम __iomem		*mbase = musb->mregs;
	व्योम __iomem		*epio = ep->regs;
	काष्ठा musb_qh		*cur_qh, *next_qh;
	u16			rx_csr, tx_csr;
	u16			toggle;

	musb_ep_select(mbase, ep->epnum);
	अगर (is_in) अणु
		dma = is_dma_capable() ? ep->rx_channel : शून्य;

		/*
		 * Need to stop the transaction by clearing REQPKT first
		 * then the NAK Timeout bit ref MUSBMHDRC USB 2.0 HIGH-SPEED
		 * DUAL-ROLE CONTROLLER Programmer's Guide, section 9.2.2
		 */
		rx_csr = musb_पढ़ोw(epio, MUSB_RXCSR);
		rx_csr |= MUSB_RXCSR_H_WZC_BITS;
		rx_csr &= ~MUSB_RXCSR_H_REQPKT;
		musb_ग_लिखोw(epio, MUSB_RXCSR, rx_csr);
		rx_csr &= ~MUSB_RXCSR_DATAERROR;
		musb_ग_लिखोw(epio, MUSB_RXCSR, rx_csr);

		cur_qh = first_qh(&musb->in_bulk);
	पूर्ण अन्यथा अणु
		dma = is_dma_capable() ? ep->tx_channel : शून्य;

		/* clear nak समयout bit */
		tx_csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		tx_csr |= MUSB_TXCSR_H_WZC_BITS;
		tx_csr &= ~MUSB_TXCSR_H_NAKTIMEOUT;
		musb_ग_लिखोw(epio, MUSB_TXCSR, tx_csr);

		cur_qh = first_qh(&musb->out_bulk);
	पूर्ण
	अगर (cur_qh) अणु
		urb = next_urb(cur_qh);
		अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
			dma->status = MUSB_DMA_STATUS_CORE_ABORT;
			musb->dma_controller->channel_पात(dma);
			urb->actual_length += dma->actual_len;
			dma->actual_len = 0L;
		पूर्ण
		toggle = musb->io.get_toggle(cur_qh, !is_in);
		usb_settoggle(urb->dev, cur_qh->epnum, !is_in, toggle ? 1 : 0);

		अगर (is_in) अणु
			/* move cur_qh to end of queue */
			list_move_tail(&cur_qh->ring, &musb->in_bulk);

			/* get the next qh from musb->in_bulk */
			next_qh = first_qh(&musb->in_bulk);

			/* set rx_reinit and schedule the next qh */
			ep->rx_reinit = 1;
		पूर्ण अन्यथा अणु
			/* move cur_qh to end of queue */
			list_move_tail(&cur_qh->ring, &musb->out_bulk);

			/* get the next qh from musb->out_bulk */
			next_qh = first_qh(&musb->out_bulk);

			/* set tx_reinit and schedule the next qh */
			ep->tx_reinit = 1;
		पूर्ण

		अगर (next_qh)
			musb_start_urb(musb, is_in, next_qh);
	पूर्ण
पूर्ण

/*
 * Service the शेष endpoपूर्णांक (ep0) as host.
 * Return true until it's समय to start the status stage.
 */
अटल bool musb_h_ep0_जारी(काष्ठा musb *musb, u16 len, काष्ठा urb *urb)
अणु
	bool			 more = false;
	u8			*fअगरo_dest = शून्य;
	u16			fअगरo_count = 0;
	काष्ठा musb_hw_ep	*hw_ep = musb->control_ep;
	काष्ठा musb_qh		*qh = hw_ep->in_qh;
	काष्ठा usb_ctrlrequest	*request;

	चयन (musb->ep0_stage) अणु
	हाल MUSB_EP0_IN:
		fअगरo_dest = urb->transfer_buffer + urb->actual_length;
		fअगरo_count = min_t(माप_प्रकार, len, urb->transfer_buffer_length -
				   urb->actual_length);
		अगर (fअगरo_count < len)
			urb->status = -EOVERFLOW;

		musb_पढ़ो_fअगरo(hw_ep, fअगरo_count, fअगरo_dest);

		urb->actual_length += fअगरo_count;
		अगर (len < qh->maxpacket) अणु
			/* always terminate on लघु पढ़ो; it's
			 * rarely reported as an error.
			 */
		पूर्ण अन्यथा अगर (urb->actual_length <
				urb->transfer_buffer_length)
			more = true;
		अवरोध;
	हाल MUSB_EP0_START:
		request = (काष्ठा usb_ctrlrequest *) urb->setup_packet;

		अगर (!request->wLength) अणु
			musb_dbg(musb, "start no-DATA");
			अवरोध;
		पूर्ण अन्यथा अगर (request->bRequestType & USB_सूची_IN) अणु
			musb_dbg(musb, "start IN-DATA");
			musb->ep0_stage = MUSB_EP0_IN;
			more = true;
			अवरोध;
		पूर्ण अन्यथा अणु
			musb_dbg(musb, "start OUT-DATA");
			musb->ep0_stage = MUSB_EP0_OUT;
			more = true;
		पूर्ण
		fallthrough;
	हाल MUSB_EP0_OUT:
		fअगरo_count = min_t(माप_प्रकार, qh->maxpacket,
				   urb->transfer_buffer_length -
				   urb->actual_length);
		अगर (fअगरo_count) अणु
			fअगरo_dest = (u8 *) (urb->transfer_buffer
					+ urb->actual_length);
			musb_dbg(musb, "Sending %d byte%s to ep0 fifo %p",
					fअगरo_count,
					(fअगरo_count == 1) ? "" : "s",
					fअगरo_dest);
			musb_ग_लिखो_fअगरo(hw_ep, fअगरo_count, fअगरo_dest);

			urb->actual_length += fअगरo_count;
			more = true;
		पूर्ण
		अवरोध;
	शेष:
		ERR("bogus ep0 stage %d\n", musb->ep0_stage);
		अवरोध;
	पूर्ण

	वापस more;
पूर्ण

/*
 * Handle शेष endpoपूर्णांक पूर्णांकerrupt as host. Only called in IRQ समय
 * from musb_पूर्णांकerrupt().
 *
 * called with controller irqlocked
 */
irqवापस_t musb_h_ep0_irq(काष्ठा musb *musb)
अणु
	काष्ठा urb		*urb;
	u16			csr, len;
	पूर्णांक			status = 0;
	व्योम __iomem		*mbase = musb->mregs;
	काष्ठा musb_hw_ep	*hw_ep = musb->control_ep;
	व्योम __iomem		*epio = hw_ep->regs;
	काष्ठा musb_qh		*qh = hw_ep->in_qh;
	bool			complete = false;
	irqवापस_t		retval = IRQ_NONE;

	/* ep0 only has one queue, "in" */
	urb = next_urb(qh);

	musb_ep_select(mbase, 0);
	csr = musb_पढ़ोw(epio, MUSB_CSR0);
	len = (csr & MUSB_CSR0_RXPKTRDY)
			? musb_पढ़ोb(epio, MUSB_COUNT0)
			: 0;

	musb_dbg(musb, "<== csr0 %04x, qh %p, count %d, urb %p, stage %d",
		csr, qh, len, urb, musb->ep0_stage);

	/* अगर we just did status stage, we are करोne */
	अगर (MUSB_EP0_STATUS == musb->ep0_stage) अणु
		retval = IRQ_HANDLED;
		complete = true;
	पूर्ण

	/* prepare status */
	अगर (csr & MUSB_CSR0_H_RXSTALL) अणु
		musb_dbg(musb, "STALLING ENDPOINT");
		status = -EPIPE;

	पूर्ण अन्यथा अगर (csr & MUSB_CSR0_H_ERROR) अणु
		musb_dbg(musb, "no response, csr0 %04x", csr);
		status = -EPROTO;

	पूर्ण अन्यथा अगर (csr & MUSB_CSR0_H_NAKTIMEOUT) अणु
		musb_dbg(musb, "control NAK timeout");

		/* NOTE:  this code path would be a good place to PAUSE a
		 * control transfer, अगर another one is queued, so that
		 * ep0 is more likely to stay busy.  That's alपढ़ोy करोne
		 * क्रम bulk RX transfers.
		 *
		 * अगर (qh->ring.next != &musb->control), then
		 * we have a candidate... NAKing is *NOT* an error
		 */
		musb_ग_लिखोw(epio, MUSB_CSR0, 0);
		retval = IRQ_HANDLED;
	पूर्ण

	अगर (status) अणु
		musb_dbg(musb, "aborting");
		retval = IRQ_HANDLED;
		अगर (urb)
			urb->status = status;
		complete = true;

		/* use the proper sequence to पात the transfer */
		अगर (csr & MUSB_CSR0_H_REQPKT) अणु
			csr &= ~MUSB_CSR0_H_REQPKT;
			musb_ग_लिखोw(epio, MUSB_CSR0, csr);
			csr &= ~MUSB_CSR0_H_NAKTIMEOUT;
			musb_ग_लिखोw(epio, MUSB_CSR0, csr);
		पूर्ण अन्यथा अणु
			musb_h_ep0_flush_fअगरo(hw_ep);
		पूर्ण

		musb_ग_लिखोb(epio, MUSB_NAKLIMIT0, 0);

		/* clear it */
		musb_ग_लिखोw(epio, MUSB_CSR0, 0);
	पूर्ण

	अगर (unlikely(!urb)) अणु
		/* stop endpoपूर्णांक since we have no place क्रम its data, this
		 * SHOULD NEVER HAPPEN! */
		ERR("no URB for end 0\n");

		musb_h_ep0_flush_fअगरo(hw_ep);
		जाओ करोne;
	पूर्ण

	अगर (!complete) अणु
		/* call common logic and prepare response */
		अगर (musb_h_ep0_जारी(musb, len, urb)) अणु
			/* more packets required */
			csr = (MUSB_EP0_IN == musb->ep0_stage)
				?  MUSB_CSR0_H_REQPKT : MUSB_CSR0_TXPKTRDY;
		पूर्ण अन्यथा अणु
			/* data transfer complete; perक्रमm status phase */
			अगर (usb_pipeout(urb->pipe)
					|| !urb->transfer_buffer_length)
				csr = MUSB_CSR0_H_STATUSPKT
					| MUSB_CSR0_H_REQPKT;
			अन्यथा
				csr = MUSB_CSR0_H_STATUSPKT
					| MUSB_CSR0_TXPKTRDY;

			/* disable ping token in status phase */
			csr |= MUSB_CSR0_H_DIS_PING;

			/* flag status stage */
			musb->ep0_stage = MUSB_EP0_STATUS;

			musb_dbg(musb, "ep0 STATUS, csr %04x", csr);

		पूर्ण
		musb_ग_लिखोw(epio, MUSB_CSR0, csr);
		retval = IRQ_HANDLED;
	पूर्ण अन्यथा
		musb->ep0_stage = MUSB_EP0_IDLE;

	/* call completion handler अगर करोne */
	अगर (complete)
		musb_advance_schedule(musb, urb, hw_ep, 1);
करोne:
	वापस retval;
पूर्ण


#अगर_घोषित CONFIG_USB_INVENTRA_DMA

/* Host side TX (OUT) using Mentor DMA works as follows:
	submit_urb ->
		- अगर queue was empty, Program Endpoपूर्णांक
		- ... which starts DMA to fअगरo in mode 1 or 0

	DMA Isr (transfer complete) -> TxAvail()
		- Stop DMA (~DmaEnab)	(<--- Alert ... currently happens
					only in musb_cleanup_urb)
		- TxPktRdy has to be set in mode 0 or क्रम
			लघु packets in mode 1.
*/

#पूर्ण_अगर

/* Service a Tx-Available or dma completion irq क्रम the endpoपूर्णांक */
व्योम musb_host_tx(काष्ठा musb *musb, u8 epnum)
अणु
	पूर्णांक			pipe;
	bool			करोne = false;
	u16			tx_csr;
	माप_प्रकार			length = 0;
	माप_प्रकार			offset = 0;
	काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs + epnum;
	व्योम __iomem		*epio = hw_ep->regs;
	काष्ठा musb_qh		*qh = hw_ep->out_qh;
	काष्ठा urb		*urb = next_urb(qh);
	u32			status = 0;
	व्योम __iomem		*mbase = musb->mregs;
	काष्ठा dma_channel	*dma;
	bool			transfer_pending = false;

	musb_ep_select(mbase, epnum);
	tx_csr = musb_पढ़ोw(epio, MUSB_TXCSR);

	/* with CPPI, DMA someबार triggers "extra" irqs */
	अगर (!urb) अणु
		musb_dbg(musb, "extra TX%d ready, csr %04x", epnum, tx_csr);
		वापस;
	पूर्ण

	pipe = urb->pipe;
	dma = is_dma_capable() ? hw_ep->tx_channel : शून्य;
	trace_musb_urb_tx(musb, urb);
	musb_dbg(musb, "OUT/TX%d end, csr %04x%s", epnum, tx_csr,
			dma ? ", dma" : "");

	/* check क्रम errors */
	अगर (tx_csr & MUSB_TXCSR_H_RXSTALL) अणु
		/* dma was disabled, fअगरo flushed */
		musb_dbg(musb, "TX end %d stall", epnum);

		/* stall; record URB status */
		status = -EPIPE;

	पूर्ण अन्यथा अगर (tx_csr & MUSB_TXCSR_H_ERROR) अणु
		/* (NON-ISO) dma was disabled, fअगरo flushed */
		musb_dbg(musb, "TX 3strikes on ep=%d", epnum);

		status = -ETIMEDOUT;

	पूर्ण अन्यथा अगर (tx_csr & MUSB_TXCSR_H_NAKTIMEOUT) अणु
		अगर (USB_ENDPOINT_XFER_BULK == qh->type && qh->mux == 1
				&& !list_is_singular(&musb->out_bulk)) अणु
			musb_dbg(musb, "NAK timeout on TX%d ep", epnum);
			musb_bulk_nak_समयout(musb, hw_ep, 0);
		पूर्ण अन्यथा अणु
			musb_dbg(musb, "TX ep%d device not responding", epnum);
			/* NOTE:  this code path would be a good place to PAUSE a
			 * transfer, अगर there's some other (nonperiodic) tx urb
			 * that could use this fअगरo.  (dma complicates it...)
			 * That's alपढ़ोy करोne क्रम bulk RX transfers.
			 *
			 * अगर (bulk && qh->ring.next != &musb->out_bulk), then
			 * we have a candidate... NAKing is *NOT* an error
			 */
			musb_ep_select(mbase, epnum);
			musb_ग_लिखोw(epio, MUSB_TXCSR,
					MUSB_TXCSR_H_WZC_BITS
					| MUSB_TXCSR_TXPKTRDY);
		पूर्ण
		वापस;
	पूर्ण

करोne:
	अगर (status) अणु
		अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
			dma->status = MUSB_DMA_STATUS_CORE_ABORT;
			musb->dma_controller->channel_पात(dma);
		पूर्ण

		/* करो the proper sequence to पात the transfer in the
		 * usb core; the dma engine should alपढ़ोy be stopped.
		 */
		musb_h_tx_flush_fअगरo(hw_ep);
		tx_csr &= ~(MUSB_TXCSR_AUTOSET
				| MUSB_TXCSR_DMAENAB
				| MUSB_TXCSR_H_ERROR
				| MUSB_TXCSR_H_RXSTALL
				| MUSB_TXCSR_H_NAKTIMEOUT
				);

		musb_ep_select(mbase, epnum);
		musb_ग_लिखोw(epio, MUSB_TXCSR, tx_csr);
		/* REVISIT may need to clear FLUSHFIFO ... */
		musb_ग_लिखोw(epio, MUSB_TXCSR, tx_csr);
		musb_ग_लिखोb(epio, MUSB_TXINTERVAL, 0);

		करोne = true;
	पूर्ण

	/* second cppi हाल */
	अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
		musb_dbg(musb, "extra TX%d ready, csr %04x", epnum, tx_csr);
		वापस;
	पूर्ण

	अगर (is_dma_capable() && dma && !status) अणु
		/*
		 * DMA has completed.  But अगर we're using DMA mode 1 (multi
		 * packet DMA), we need a terminal TXPKTRDY पूर्णांकerrupt beक्रमe
		 * we can consider this transfer completed, lest we trash
		 * its last packet when writing the next URB's data.  So we
		 * चयन back to mode 0 to get that पूर्णांकerrupt; we'll come
		 * back here once it happens.
		 */
		अगर (tx_csr & MUSB_TXCSR_DMAMODE) अणु
			/*
			 * We shouldn't clear DMAMODE with DMAENAB set; so
			 * clear them in a safe order.  That should be OK
			 * once TXPKTRDY has been set (and I've never seen
			 * it being 0 at this moment -- DMA पूर्णांकerrupt latency
			 * is signअगरicant) but अगर it hasn't been then we have
			 * no choice but to stop being polite and ignore the
			 * programmer's guide... :-)
			 *
			 * Note that we must ग_लिखो TXCSR with TXPKTRDY cleared
			 * in order not to re-trigger the packet send (this bit
			 * can't be cleared by CPU), and there's another caveat:
			 * TXPKTRDY may be set लघुly and then cleared in the
			 * द्विगुन-buffered FIFO mode, so we करो an extra TXCSR
			 * पढ़ो क्रम debouncing...
			 */
			tx_csr &= musb_पढ़ोw(epio, MUSB_TXCSR);
			अगर (tx_csr & MUSB_TXCSR_TXPKTRDY) अणु
				tx_csr &= ~(MUSB_TXCSR_DMAENAB |
					    MUSB_TXCSR_TXPKTRDY);
				musb_ग_लिखोw(epio, MUSB_TXCSR,
					    tx_csr | MUSB_TXCSR_H_WZC_BITS);
			पूर्ण
			tx_csr &= ~(MUSB_TXCSR_DMAMODE |
				    MUSB_TXCSR_TXPKTRDY);
			musb_ग_लिखोw(epio, MUSB_TXCSR,
				    tx_csr | MUSB_TXCSR_H_WZC_BITS);

			/*
			 * There is no guarantee that we'll get an पूर्णांकerrupt
			 * after clearing DMAMODE as we might have करोne this
			 * too late (after TXPKTRDY was cleared by controller).
			 * Re-पढ़ो TXCSR as we have spoiled its previous value.
			 */
			tx_csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		पूर्ण

		/*
		 * We may get here from a DMA completion or TXPKTRDY पूर्णांकerrupt.
		 * In any हाल, we must check the FIFO status here and bail out
		 * only अगर the FIFO still has data -- that should prevent the
		 * "missed" TXPKTRDY पूर्णांकerrupts and deal with द्विगुन-buffered
		 * FIFO mode too...
		 */
		अगर (tx_csr & (MUSB_TXCSR_FIFONOTEMPTY | MUSB_TXCSR_TXPKTRDY)) अणु
			musb_dbg(musb,
				"DMA complete but FIFO not empty, CSR %04x",
				tx_csr);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!status || dma || usb_pipeisoc(pipe)) अणु
		अगर (dma)
			length = dma->actual_len;
		अन्यथा
			length = qh->segsize;
		qh->offset += length;

		अगर (usb_pipeisoc(pipe)) अणु
			काष्ठा usb_iso_packet_descriptor	*d;

			d = urb->iso_frame_desc + qh->iso_idx;
			d->actual_length = length;
			d->status = status;
			अगर (++qh->iso_idx >= urb->number_of_packets) अणु
				करोne = true;
			पूर्ण अन्यथा अणु
				d++;
				offset = d->offset;
				length = d->length;
			पूर्ण
		पूर्ण अन्यथा अगर (dma && urb->transfer_buffer_length == qh->offset) अणु
			करोne = true;
		पूर्ण अन्यथा अणु
			/* see अगर we need to send more data, or ZLP */
			अगर (qh->segsize < qh->maxpacket)
				करोne = true;
			अन्यथा अगर (qh->offset == urb->transfer_buffer_length
					&& !(urb->transfer_flags
						& URB_ZERO_PACKET))
				करोne = true;
			अगर (!करोne) अणु
				offset = qh->offset;
				length = urb->transfer_buffer_length - offset;
				transfer_pending = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* urb->status != -EINPROGRESS means request has been faulted,
	 * so we must पात this transfer after cleanup
	 */
	अगर (urb->status != -EINPROGRESS) अणु
		करोne = true;
		अगर (status == 0)
			status = urb->status;
	पूर्ण

	अगर (करोne) अणु
		/* set status */
		urb->status = status;
		urb->actual_length = qh->offset;
		musb_advance_schedule(musb, urb, hw_ep, USB_सूची_OUT);
		वापस;
	पूर्ण अन्यथा अगर ((usb_pipeisoc(pipe) || transfer_pending) && dma) अणु
		अगर (musb_tx_dma_program(musb->dma_controller, hw_ep, qh, urb,
				offset, length)) अणु
			अगर (is_cppi_enabled(musb) || tusb_dma_omap(musb))
				musb_h_tx_dma_start(hw_ep);
			वापस;
		पूर्ण
	पूर्ण अन्यथा	अगर (tx_csr & MUSB_TXCSR_DMAENAB) अणु
		musb_dbg(musb, "not complete, but DMA enabled?");
		वापस;
	पूर्ण

	/*
	 * PIO: start next packet in this URB.
	 *
	 * REVISIT: some करोcs say that when hw_ep->tx_द्विगुन_buffered,
	 * (and presumably, FIFO is not half-full) we should ग_लिखो *two*
	 * packets beक्रमe updating TXCSR; other करोcs disagree...
	 */
	अगर (length > qh->maxpacket)
		length = qh->maxpacket;
	/* Unmap the buffer so that CPU can use it */
	usb_hcd_unmap_urb_क्रम_dma(musb->hcd, urb);

	/*
	 * We need to map sg अगर the transfer_buffer is
	 * शून्य.
	 */
	अगर (!urb->transfer_buffer) अणु
		/* sg_miter_start is alपढ़ोy करोne in musb_ep_program */
		अगर (!sg_miter_next(&qh->sg_miter)) अणु
			dev_err(musb->controller, "error: sg list empty\n");
			sg_miter_stop(&qh->sg_miter);
			status = -EINVAL;
			जाओ करोne;
		पूर्ण
		length = min_t(u32, length, qh->sg_miter.length);
		musb_ग_लिखो_fअगरo(hw_ep, length, qh->sg_miter.addr);
		qh->sg_miter.consumed = length;
		sg_miter_stop(&qh->sg_miter);
	पूर्ण अन्यथा अणु
		musb_ग_लिखो_fअगरo(hw_ep, length, urb->transfer_buffer + offset);
	पूर्ण

	qh->segsize = length;

	musb_ep_select(mbase, epnum);
	musb_ग_लिखोw(epio, MUSB_TXCSR,
			MUSB_TXCSR_H_WZC_BITS | MUSB_TXCSR_TXPKTRDY);
पूर्ण

#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
/* Seems to set up ISO क्रम cppi41 and not advance len. See commit c57c41d */
अटल पूर्णांक musb_rx_dma_iso_cppi41(काष्ठा dma_controller *dma,
				  काष्ठा musb_hw_ep *hw_ep,
				  काष्ठा musb_qh *qh,
				  काष्ठा urb *urb,
				  माप_प्रकार len)
अणु
	काष्ठा dma_channel *channel = hw_ep->rx_channel;
	व्योम __iomem *epio = hw_ep->regs;
	dma_addr_t *buf;
	u32 length;
	u16 val;

	buf = (व्योम *)urb->iso_frame_desc[qh->iso_idx].offset +
		(u32)urb->transfer_dma;

	length = urb->iso_frame_desc[qh->iso_idx].length;

	val = musb_पढ़ोw(epio, MUSB_RXCSR);
	val |= MUSB_RXCSR_DMAENAB;
	musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR, val);

	वापस dma->channel_program(channel, qh->maxpacket, 0,
				   (u32)buf, length);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक musb_rx_dma_iso_cppi41(काष्ठा dma_controller *dma,
					 काष्ठा musb_hw_ep *hw_ep,
					 काष्ठा musb_qh *qh,
					 काष्ठा urb *urb,
					 माप_प्रकार len)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_USB_INVENTRA_DMA) || defined(CONFIG_USB_UX500_DMA) || \
	defined(CONFIG_USB_TI_CPPI41_DMA)
/* Host side RX (IN) using Mentor DMA works as follows:
	submit_urb ->
		- अगर queue was empty, ProgramEndpoपूर्णांक
		- first IN token is sent out (by setting ReqPkt)
	LinuxIsr -> RxReady()
	/\	=> first packet is received
	|	- Set in mode 0 (DmaEnab, ~ReqPkt)
	|		-> DMA Isr (transfer complete) -> RxReady()
	|		    - Ack receive (~RxPktRdy), turn off DMA (~DmaEnab)
	|		    - अगर urb not complete, send next IN token (ReqPkt)
	|			   |		अन्यथा complete urb.
	|			   |
	---------------------------
 *
 * Nuances of mode 1:
 *	For लघु packets, no ack (+RxPktRdy) is sent स्वतःmatically
 *	(even अगर AutoClear is ON)
 *	For full packets, ack (~RxPktRdy) and next IN token (+ReqPkt) is sent
 *	स्वतःmatically => major problem, as collecting the next packet becomes
 *	dअगरficult. Hence mode 1 is not used.
 *
 * REVISIT
 *	All we care about at this driver level is that
 *       (a) all URBs terminate with REQPKT cleared and fअगरo(s) empty;
 *       (b) termination conditions are: लघु RX, or buffer full;
 *       (c) fault modes include
 *           - अगरf URB_SHORT_NOT_OK, लघु RX status is -EREMOTEIO.
 *             (and that endpoपूर्णांक's dma queue stops immediately)
 *           - overflow (full, PLUS more bytes in the terminal packet)
 *
 *	So क्रम example, usb-storage sets URB_SHORT_NOT_OK, and would
 *	thus be a great candidate क्रम using mode 1 ... क्रम all but the
 *	last packet of one URB's transfer.
 */
अटल पूर्णांक musb_rx_dma_inventra_cppi41(काष्ठा dma_controller *dma,
				       काष्ठा musb_hw_ep *hw_ep,
				       काष्ठा musb_qh *qh,
				       काष्ठा urb *urb,
				       माप_प्रकार len)
अणु
	काष्ठा dma_channel *channel = hw_ep->rx_channel;
	व्योम __iomem *epio = hw_ep->regs;
	u16 val;
	पूर्णांक pipe;
	bool करोne;

	pipe = urb->pipe;

	अगर (usb_pipeisoc(pipe)) अणु
		काष्ठा usb_iso_packet_descriptor *d;

		d = urb->iso_frame_desc + qh->iso_idx;
		d->actual_length = len;

		/* even अगर there was an error, we did the dma
		 * क्रम iso_frame_desc->length
		 */
		अगर (d->status != -EILSEQ && d->status != -EOVERFLOW)
			d->status = 0;

		अगर (++qh->iso_idx >= urb->number_of_packets) अणु
			करोne = true;
		पूर्ण अन्यथा अणु
			/* REVISIT: Why ignore वापस value here? */
			अगर (musb_dma_cppi41(hw_ep->musb))
				करोne = musb_rx_dma_iso_cppi41(dma, hw_ep, qh,
							      urb, len);
			करोne = false;
		पूर्ण

	पूर्ण अन्यथा  अणु
		/* करोne अगर urb buffer is full or लघु packet is recd */
		करोne = (urb->actual_length + len >=
			urb->transfer_buffer_length
			|| channel->actual_len < qh->maxpacket
			|| channel->rx_packet_करोne);
	पूर्ण

	/* send IN token क्रम next packet, without AUTOREQ */
	अगर (!करोne) अणु
		val = musb_पढ़ोw(epio, MUSB_RXCSR);
		val |= MUSB_RXCSR_H_REQPKT;
		musb_ग_लिखोw(epio, MUSB_RXCSR, MUSB_RXCSR_H_WZC_BITS | val);
	पूर्ण

	वापस करोne;
पूर्ण

/* Disadvantage of using mode 1:
 *	It's basically usable only क्रम mass storage class; essentially all
 *	other protocols also terminate transfers on लघु packets.
 *
 * Details:
 *	An extra IN token is sent at the end of the transfer (due to AUTOREQ)
 *	If you try to use mode 1 क्रम (transfer_buffer_length - 512), and try
 *	to use the extra IN token to grab the last packet using mode 0, then
 *	the problem is that you cannot be sure when the device will send the
 *	last packet and RxPktRdy set. Someबार the packet is recd too soon
 *	such that it माला_लो lost when RxCSR is re-set at the end of the mode 1
 *	transfer, जबतक someबार it is recd just a little late so that अगर you
 *	try to configure क्रम mode 0 soon after the mode 1 transfer is
 *	completed, you will find rxcount 0. Okay, so you might think why not
 *	रुको क्रम an पूर्णांकerrupt when the pkt is recd. Well, you won't get any!
 */
अटल पूर्णांक musb_rx_dma_in_inventra_cppi41(काष्ठा dma_controller *dma,
					  काष्ठा musb_hw_ep *hw_ep,
					  काष्ठा musb_qh *qh,
					  काष्ठा urb *urb,
					  माप_प्रकार len,
					  u8 iso_err)
अणु
	काष्ठा musb *musb = hw_ep->musb;
	व्योम __iomem *epio = hw_ep->regs;
	काष्ठा dma_channel *channel = hw_ep->rx_channel;
	u16 rx_count, val;
	पूर्णांक length, pipe, करोne;
	dma_addr_t buf;

	rx_count = musb_पढ़ोw(epio, MUSB_RXCOUNT);
	pipe = urb->pipe;

	अगर (usb_pipeisoc(pipe)) अणु
		पूर्णांक d_status = 0;
		काष्ठा usb_iso_packet_descriptor *d;

		d = urb->iso_frame_desc + qh->iso_idx;

		अगर (iso_err) अणु
			d_status = -EILSEQ;
			urb->error_count++;
		पूर्ण
		अगर (rx_count > d->length) अणु
			अगर (d_status == 0) अणु
				d_status = -EOVERFLOW;
				urb->error_count++;
			पूर्ण
			musb_dbg(musb, "** OVERFLOW %d into %d",
				rx_count, d->length);

			length = d->length;
		पूर्ण अन्यथा
			length = rx_count;
		d->status = d_status;
		buf = urb->transfer_dma + d->offset;
	पूर्ण अन्यथा अणु
		length = rx_count;
		buf = urb->transfer_dma + urb->actual_length;
	पूर्ण

	channel->desired_mode = 0;
#अगर_घोषित USE_MODE1
	/* because of the issue below, mode 1 will
	 * only rarely behave with correct semantics.
	 */
	अगर ((urb->transfer_flags & URB_SHORT_NOT_OK)
	    && (urb->transfer_buffer_length - urb->actual_length)
	    > qh->maxpacket)
		channel->desired_mode = 1;
	अगर (rx_count < hw_ep->max_packet_sz_rx) अणु
		length = rx_count;
		channel->desired_mode = 0;
	पूर्ण अन्यथा अणु
		length = urb->transfer_buffer_length;
	पूर्ण
#पूर्ण_अगर

	/* See comments above on disadvantages of using mode 1 */
	val = musb_पढ़ोw(epio, MUSB_RXCSR);
	val &= ~MUSB_RXCSR_H_REQPKT;

	अगर (channel->desired_mode == 0)
		val &= ~MUSB_RXCSR_H_AUTOREQ;
	अन्यथा
		val |= MUSB_RXCSR_H_AUTOREQ;
	val |= MUSB_RXCSR_DMAENAB;

	/* स्वतःclear shouldn't be set in high bandwidth */
	अगर (qh->hb_mult == 1)
		val |= MUSB_RXCSR_AUTOCLEAR;

	musb_ग_लिखोw(epio, MUSB_RXCSR, MUSB_RXCSR_H_WZC_BITS | val);

	/* REVISIT अगर when actual_length != 0,
	 * transfer_buffer_length needs to be
	 * adjusted first...
	 */
	करोne = dma->channel_program(channel, qh->maxpacket,
				   channel->desired_mode,
				   buf, length);

	अगर (!करोne) अणु
		dma->channel_release(channel);
		hw_ep->rx_channel = शून्य;
		channel = शून्य;
		val = musb_पढ़ोw(epio, MUSB_RXCSR);
		val &= ~(MUSB_RXCSR_DMAENAB
			 | MUSB_RXCSR_H_AUTOREQ
			 | MUSB_RXCSR_AUTOCLEAR);
		musb_ग_लिखोw(epio, MUSB_RXCSR, val);
	पूर्ण

	वापस करोne;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक musb_rx_dma_inventra_cppi41(काष्ठा dma_controller *dma,
					      काष्ठा musb_hw_ep *hw_ep,
					      काष्ठा musb_qh *qh,
					      काष्ठा urb *urb,
					      माप_प्रकार len)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक musb_rx_dma_in_inventra_cppi41(काष्ठा dma_controller *dma,
						 काष्ठा musb_hw_ep *hw_ep,
						 काष्ठा musb_qh *qh,
						 काष्ठा urb *urb,
						 माप_प्रकार len,
						 u8 iso_err)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Service an RX पूर्णांकerrupt क्रम the given IN endpoपूर्णांक; करोcs cover bulk, iso,
 * and high-bandwidth IN transfer हालs.
 */
व्योम musb_host_rx(काष्ठा musb *musb, u8 epnum)
अणु
	काष्ठा urb		*urb;
	काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs + epnum;
	काष्ठा dma_controller	*c = musb->dma_controller;
	व्योम __iomem		*epio = hw_ep->regs;
	काष्ठा musb_qh		*qh = hw_ep->in_qh;
	माप_प्रकार			xfer_len;
	व्योम __iomem		*mbase = musb->mregs;
	u16			rx_csr, val;
	bool			iso_err = false;
	bool			करोne = false;
	u32			status;
	काष्ठा dma_channel	*dma;
	अचिन्हित पूर्णांक sg_flags = SG_MITER_ATOMIC | SG_MITER_TO_SG;

	musb_ep_select(mbase, epnum);

	urb = next_urb(qh);
	dma = is_dma_capable() ? hw_ep->rx_channel : शून्य;
	status = 0;
	xfer_len = 0;

	rx_csr = musb_पढ़ोw(epio, MUSB_RXCSR);
	val = rx_csr;

	अगर (unlikely(!urb)) अणु
		/* REVISIT -- THIS SHOULD NEVER HAPPEN ... but, at least
		 * usbtest #11 (unlinks) triggers it regularly, someबार
		 * with fअगरo full.  (Only with DMA??)
		 */
		musb_dbg(musb, "BOGUS RX%d ready, csr %04x, count %d",
			epnum, val, musb_पढ़ोw(epio, MUSB_RXCOUNT));
		musb_h_flush_rxfअगरo(hw_ep, MUSB_RXCSR_CLRDATATOG);
		वापस;
	पूर्ण

	trace_musb_urb_rx(musb, urb);

	/* check क्रम errors, concurrent stall & unlink is not really
	 * handled yet! */
	अगर (rx_csr & MUSB_RXCSR_H_RXSTALL) अणु
		musb_dbg(musb, "RX end %d STALL", epnum);

		/* stall; record URB status */
		status = -EPIPE;

	पूर्ण अन्यथा अगर (rx_csr & MUSB_RXCSR_H_ERROR) अणु
		dev_err(musb->controller, "ep%d RX three-strikes error", epnum);

		/*
		 * The three-strikes error could only happen when the USB
		 * device is not accessible, क्रम example detached or घातered
		 * off. So वापस the fatal error -ESHUTDOWN so hopefully the
		 * USB device drivers won't immediately resubmit the same URB.
		 */
		status = -ESHUTDOWN;
		musb_ग_लिखोb(epio, MUSB_RXINTERVAL, 0);

		rx_csr &= ~MUSB_RXCSR_H_ERROR;
		musb_ग_लिखोw(epio, MUSB_RXCSR, rx_csr);

	पूर्ण अन्यथा अगर (rx_csr & MUSB_RXCSR_DATAERROR) अणु

		अगर (USB_ENDPOINT_XFER_ISOC != qh->type) अणु
			musb_dbg(musb, "RX end %d NAK timeout", epnum);

			/* NOTE: NAKing is *NOT* an error, so we want to
			 * जारी.  Except ... अगर there's a request क्रम
			 * another QH, use that instead of starving it.
			 *
			 * Devices like Ethernet and serial adapters keep
			 * पढ़ोs posted at all बार, which will starve
			 * other devices without this logic.
			 */
			अगर (usb_pipebulk(urb->pipe)
					&& qh->mux == 1
					&& !list_is_singular(&musb->in_bulk)) अणु
				musb_bulk_nak_समयout(musb, hw_ep, 1);
				वापस;
			पूर्ण
			musb_ep_select(mbase, epnum);
			rx_csr |= MUSB_RXCSR_H_WZC_BITS;
			rx_csr &= ~MUSB_RXCSR_DATAERROR;
			musb_ग_लिखोw(epio, MUSB_RXCSR, rx_csr);

			जाओ finish;
		पूर्ण अन्यथा अणु
			musb_dbg(musb, "RX end %d ISO data error", epnum);
			/* packet error reported later */
			iso_err = true;
		पूर्ण
	पूर्ण अन्यथा अगर (rx_csr & MUSB_RXCSR_INCOMPRX) अणु
		musb_dbg(musb, "end %d high bandwidth incomplete ISO packet RX",
				epnum);
		status = -EPROTO;
	पूर्ण

	/* faults पात the transfer */
	अगर (status) अणु
		/* clean up dma and collect transfer count */
		अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
			dma->status = MUSB_DMA_STATUS_CORE_ABORT;
			musb->dma_controller->channel_पात(dma);
			xfer_len = dma->actual_len;
		पूर्ण
		musb_h_flush_rxfअगरo(hw_ep, MUSB_RXCSR_CLRDATATOG);
		musb_ग_लिखोb(epio, MUSB_RXINTERVAL, 0);
		करोne = true;
		जाओ finish;
	पूर्ण

	अगर (unlikely(dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY)) अणु
		/* SHOULD NEVER HAPPEN ... but at least DaVinci has करोne it */
		ERR("RX%d dma busy, csr %04x\n", epnum, rx_csr);
		जाओ finish;
	पूर्ण

	/* thorough shutकरोwn क्रम now ... given more precise fault handling
	 * and better queueing support, we might keep a DMA pipeline going
	 * जबतक processing this irq क्रम earlier completions.
	 */

	/* FIXME this is _way_ too much in-line logic क्रम Mentor DMA */
	अगर (!musb_dma_inventra(musb) && !musb_dma_ux500(musb) &&
	    (rx_csr & MUSB_RXCSR_H_REQPKT)) अणु
		/* REVISIT this happened क्रम a जबतक on some लघु पढ़ोs...
		 * the cleanup still needs investigation... looks bad...
		 * and also duplicates dma cleanup code above ... plus,
		 * shouldn't this be the "half full" द्विगुन buffer हाल?
		 */
		अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
			dma->status = MUSB_DMA_STATUS_CORE_ABORT;
			musb->dma_controller->channel_पात(dma);
			xfer_len = dma->actual_len;
			करोne = true;
		पूर्ण

		musb_dbg(musb, "RXCSR%d %04x, reqpkt, len %zu%s", epnum, rx_csr,
				xfer_len, dma ? ", dma" : "");
		rx_csr &= ~MUSB_RXCSR_H_REQPKT;

		musb_ep_select(mbase, epnum);
		musb_ग_लिखोw(epio, MUSB_RXCSR,
				MUSB_RXCSR_H_WZC_BITS | rx_csr);
	पूर्ण

	अगर (dma && (rx_csr & MUSB_RXCSR_DMAENAB)) अणु
		xfer_len = dma->actual_len;

		val &= ~(MUSB_RXCSR_DMAENAB
			| MUSB_RXCSR_H_AUTOREQ
			| MUSB_RXCSR_AUTOCLEAR
			| MUSB_RXCSR_RXPKTRDY);
		musb_ग_लिखोw(hw_ep->regs, MUSB_RXCSR, val);

		अगर (musb_dma_inventra(musb) || musb_dma_ux500(musb) ||
		    musb_dma_cppi41(musb)) अणु
			    करोne = musb_rx_dma_inventra_cppi41(c, hw_ep, qh, urb, xfer_len);
			    musb_dbg(hw_ep->musb,
				    "ep %d dma %s, rxcsr %04x, rxcount %d",
				    epnum, करोne ? "off" : "reset",
				    musb_पढ़ोw(epio, MUSB_RXCSR),
				    musb_पढ़ोw(epio, MUSB_RXCOUNT));
		पूर्ण अन्यथा अणु
			करोne = true;
		पूर्ण

	पूर्ण अन्यथा अगर (urb->status == -EINPROGRESS) अणु
		/* अगर no errors, be sure a packet is पढ़ोy क्रम unloading */
		अगर (unlikely(!(rx_csr & MUSB_RXCSR_RXPKTRDY))) अणु
			status = -EPROTO;
			ERR("Rx interrupt with no errors or packet!\n");

			/* FIXME this is another "SHOULD NEVER HAPPEN" */

/* SCRUB (RX) */
			/* करो the proper sequence to पात the transfer */
			musb_ep_select(mbase, epnum);
			val &= ~MUSB_RXCSR_H_REQPKT;
			musb_ग_लिखोw(epio, MUSB_RXCSR, val);
			जाओ finish;
		पूर्ण

		/* we are expecting IN packets */
		अगर ((musb_dma_inventra(musb) || musb_dma_ux500(musb) ||
		    musb_dma_cppi41(musb)) && dma) अणु
			musb_dbg(hw_ep->musb,
				"RX%d count %d, buffer 0x%llx len %d/%d",
				epnum, musb_पढ़ोw(epio, MUSB_RXCOUNT),
				(अचिन्हित दीर्घ दीर्घ) urb->transfer_dma
				+ urb->actual_length,
				qh->offset,
				urb->transfer_buffer_length);

			अगर (musb_rx_dma_in_inventra_cppi41(c, hw_ep, qh, urb,
							   xfer_len, iso_err))
				जाओ finish;
			अन्यथा
				dev_err(musb->controller, "error: rx_dma failed\n");
		पूर्ण

		अगर (!dma) अणु
			अचिन्हित पूर्णांक received_len;

			/* Unmap the buffer so that CPU can use it */
			usb_hcd_unmap_urb_क्रम_dma(musb->hcd, urb);

			/*
			 * We need to map sg अगर the transfer_buffer is
			 * शून्य.
			 */
			अगर (!urb->transfer_buffer) अणु
				qh->use_sg = true;
				sg_miter_start(&qh->sg_miter, urb->sg, 1,
						sg_flags);
			पूर्ण

			अगर (qh->use_sg) अणु
				अगर (!sg_miter_next(&qh->sg_miter)) अणु
					dev_err(musb->controller, "error: sg list empty\n");
					sg_miter_stop(&qh->sg_miter);
					status = -EINVAL;
					करोne = true;
					जाओ finish;
				पूर्ण
				urb->transfer_buffer = qh->sg_miter.addr;
				received_len = urb->actual_length;
				qh->offset = 0x0;
				करोne = musb_host_packet_rx(musb, urb, epnum,
						iso_err);
				/* Calculate the number of bytes received */
				received_len = urb->actual_length -
					received_len;
				qh->sg_miter.consumed = received_len;
				sg_miter_stop(&qh->sg_miter);
			पूर्ण अन्यथा अणु
				करोne = musb_host_packet_rx(musb, urb,
						epnum, iso_err);
			पूर्ण
			musb_dbg(musb, "read %spacket", करोne ? "last " : "");
		पूर्ण
	पूर्ण

finish:
	urb->actual_length += xfer_len;
	qh->offset += xfer_len;
	अगर (करोne) अणु
		अगर (qh->use_sg) अणु
			qh->use_sg = false;
			urb->transfer_buffer = शून्य;
		पूर्ण

		अगर (urb->status == -EINPROGRESS)
			urb->status = status;
		musb_advance_schedule(musb, urb, hw_ep, USB_सूची_IN);
	पूर्ण
पूर्ण

/* schedule nodes correspond to peripheral endpoपूर्णांकs, like an OHCI QH.
 * the software schedule associates multiple such nodes with a given
 * host side hardware endpoपूर्णांक + direction; scheduling may activate
 * that hardware endpoपूर्णांक.
 */
अटल पूर्णांक musb_schedule(
	काष्ठा musb		*musb,
	काष्ठा musb_qh		*qh,
	पूर्णांक			is_in)
अणु
	पूर्णांक			idle = 0;
	पूर्णांक			best_dअगरf;
	पूर्णांक			best_end, epnum;
	काष्ठा musb_hw_ep	*hw_ep = शून्य;
	काष्ठा list_head	*head = शून्य;
	u8			toggle;
	u8			txtype;
	काष्ठा urb		*urb = next_urb(qh);

	/* use fixed hardware क्रम control and bulk */
	अगर (qh->type == USB_ENDPOINT_XFER_CONTROL) अणु
		head = &musb->control;
		hw_ep = musb->control_ep;
		जाओ success;
	पूर्ण

	/* अन्यथा, periodic transfers get muxed to other endpoपूर्णांकs */

	/*
	 * We know this qh hasn't been scheduled, so all we need to करो
	 * is choose which hardware endpoपूर्णांक to put it on ...
	 *
	 * REVISIT what we really want here is a regular schedule tree
	 * like e.g. OHCI uses.
	 */
	best_dअगरf = 4096;
	best_end = -1;

	क्रम (epnum = 1, hw_ep = musb->endpoपूर्णांकs + 1;
			epnum < musb->nr_endpoपूर्णांकs;
			epnum++, hw_ep++) अणु
		पूर्णांक	dअगरf;

		अगर (musb_ep_get_qh(hw_ep, is_in) != शून्य)
			जारी;

		अगर (hw_ep == musb->bulk_ep)
			जारी;

		अगर (is_in)
			dअगरf = hw_ep->max_packet_sz_rx;
		अन्यथा
			dअगरf = hw_ep->max_packet_sz_tx;
		dअगरf -= (qh->maxpacket * qh->hb_mult);

		अगर (dअगरf >= 0 && best_dअगरf > dअगरf) अणु

			/*
			 * Mentor controller has a bug in that अगर we schedule
			 * a BULK Tx transfer on an endpoपूर्णांक that had earlier
			 * handled ISOC then the BULK transfer has to start on
			 * a zero toggle.  If the BULK transfer starts on a 1
			 * toggle then this transfer will fail as the mentor
			 * controller starts the Bulk transfer on a 0 toggle
			 * irrespective of the programming of the toggle bits
			 * in the TXCSR रेजिस्टर.  Check क्रम this condition
			 * जबतक allocating the EP क्रम a Tx Bulk transfer.  If
			 * so skip this EP.
			 */
			hw_ep = musb->endpoपूर्णांकs + epnum;
			toggle = usb_gettoggle(urb->dev, qh->epnum, !is_in);
			txtype = (musb_पढ़ोb(hw_ep->regs, MUSB_TXTYPE)
					>> 4) & 0x3;
			अगर (!is_in && (qh->type == USB_ENDPOINT_XFER_BULK) &&
				toggle && (txtype == USB_ENDPOINT_XFER_ISOC))
				जारी;

			best_dअगरf = dअगरf;
			best_end = epnum;
		पूर्ण
	पूर्ण
	/* use bulk reserved ep1 अगर no other ep is मुक्त */
	अगर (best_end < 0 && qh->type == USB_ENDPOINT_XFER_BULK) अणु
		hw_ep = musb->bulk_ep;
		अगर (is_in)
			head = &musb->in_bulk;
		अन्यथा
			head = &musb->out_bulk;

		/* Enable bulk RX/TX NAK समयout scheme when bulk requests are
		 * multiplexed. This scheme करोes not work in high speed to full
		 * speed scenario as NAK पूर्णांकerrupts are not coming from a
		 * full speed device connected to a high speed device.
		 * NAK समयout पूर्णांकerval is 8 (128 uframe or 16ms) क्रम HS and
		 * 4 (8 frame or 8ms) क्रम FS device.
		 */
		अगर (qh->dev)
			qh->पूर्णांकv_reg =
				(USB_SPEED_HIGH == qh->dev->speed) ? 8 : 4;
		जाओ success;
	पूर्ण अन्यथा अगर (best_end < 0) अणु
		dev_err(musb->controller,
				"%s hwep alloc failed for %dx%d\n",
				musb_ep_xfertype_string(qh->type),
				qh->hb_mult, qh->maxpacket);
		वापस -ENOSPC;
	पूर्ण

	idle = 1;
	qh->mux = 0;
	hw_ep = musb->endpoपूर्णांकs + best_end;
	musb_dbg(musb, "qh %p periodic slot %d", qh, best_end);
success:
	अगर (head) अणु
		idle = list_empty(head);
		list_add_tail(&qh->ring, head);
		qh->mux = 1;
	पूर्ण
	qh->hw_ep = hw_ep;
	qh->hep->hcpriv = qh;
	अगर (idle)
		musb_start_urb(musb, is_in, qh);
	वापस 0;
पूर्ण

अटल पूर्णांक musb_urb_enqueue(
	काष्ठा usb_hcd			*hcd,
	काष्ठा urb			*urb,
	gfp_t				mem_flags)
अणु
	अचिन्हित दीर्घ			flags;
	काष्ठा musb			*musb = hcd_to_musb(hcd);
	काष्ठा usb_host_endpoपूर्णांक	*hep = urb->ep;
	काष्ठा musb_qh			*qh;
	काष्ठा usb_endpoपूर्णांक_descriptor	*epd = &hep->desc;
	पूर्णांक				ret;
	अचिन्हित			type_reg;
	अचिन्हित			पूर्णांकerval;

	/* host role must be active */
	अगर (!is_host_active(musb) || !musb->is_active)
		वापस -ENODEV;

	trace_musb_urb_enq(musb, urb);

	spin_lock_irqsave(&musb->lock, flags);
	ret = usb_hcd_link_urb_to_ep(hcd, urb);
	qh = ret ? शून्य : hep->hcpriv;
	अगर (qh)
		urb->hcpriv = qh;
	spin_unlock_irqrestore(&musb->lock, flags);

	/* DMA mapping was alपढ़ोy करोne, अगर needed, and this urb is on
	 * hep->urb_list now ... so we're done, unless hep wasn't yet
	 * scheduled onto a live qh.
	 *
	 * REVISIT best to keep hep->hcpriv valid until the endpoपूर्णांक माला_लो
	 * disabled, testing क्रम empty qh->ring and aव्योमing qh setup costs
	 * except क्रम the first urb queued after a config change.
	 */
	अगर (qh || ret)
		वापस ret;

	/* Allocate and initialize qh, minimizing the work करोne each समय
	 * hw_ep माला_लो reprogrammed, or with irqs blocked.  Then schedule it.
	 *
	 * REVISIT consider a dedicated qh kmem_cache, so it's harder
	 * क्रम bugs in other kernel code to अवरोध this driver...
	 */
	qh = kzalloc(माप *qh, mem_flags);
	अगर (!qh) अणु
		spin_lock_irqsave(&musb->lock, flags);
		usb_hcd_unlink_urb_from_ep(hcd, urb);
		spin_unlock_irqrestore(&musb->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	qh->hep = hep;
	qh->dev = urb->dev;
	INIT_LIST_HEAD(&qh->ring);
	qh->is_पढ़ोy = 1;

	qh->maxpacket = usb_endpoपूर्णांक_maxp(epd);
	qh->type = usb_endpoपूर्णांक_type(epd);

	/* Bits 11 & 12 of wMaxPacketSize encode high bandwidth multiplier.
	 * Some musb cores करोn't support high bandwidth ISO transfers; and
	 * we करोn't (yet!) support high bandwidth पूर्णांकerrupt transfers.
	 */
	qh->hb_mult = usb_endpoपूर्णांक_maxp_mult(epd);
	अगर (qh->hb_mult > 1) अणु
		पूर्णांक ok = (qh->type == USB_ENDPOINT_XFER_ISOC);

		अगर (ok)
			ok = (usb_pipein(urb->pipe) && musb->hb_iso_rx)
				|| (usb_pipeout(urb->pipe) && musb->hb_iso_tx);
		अगर (!ok) अणु
			dev_err(musb->controller,
				"high bandwidth %s (%dx%d) not supported\n",
				musb_ep_xfertype_string(qh->type),
				qh->hb_mult, qh->maxpacket & 0x7ff);
			ret = -EMSGSIZE;
			जाओ करोne;
		पूर्ण
		qh->maxpacket &= 0x7ff;
	पूर्ण

	qh->epnum = usb_endpoपूर्णांक_num(epd);

	/* NOTE: urb->dev->devnum is wrong during SET_ADDRESS */
	qh->addr_reg = (u8) usb_pipedevice(urb->pipe);

	/* precompute rxtype/txtype/type0 रेजिस्टर */
	type_reg = (qh->type << 4) | qh->epnum;
	चयन (urb->dev->speed) अणु
	हाल USB_SPEED_LOW:
		type_reg |= 0xc0;
		अवरोध;
	हाल USB_SPEED_FULL:
		type_reg |= 0x80;
		अवरोध;
	शेष:
		type_reg |= 0x40;
	पूर्ण
	qh->type_reg = type_reg;

	/* Precompute RXINTERVAL/TXINTERVAL रेजिस्टर */
	चयन (qh->type) अणु
	हाल USB_ENDPOINT_XFER_INT:
		/*
		 * Full/low speeds use the  linear encoding,
		 * high speed uses the logarithmic encoding.
		 */
		अगर (urb->dev->speed <= USB_SPEED_FULL) अणु
			पूर्णांकerval = max_t(u8, epd->bInterval, 1);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल USB_ENDPOINT_XFER_ISOC:
		/* ISO always uses logarithmic encoding */
		पूर्णांकerval = min_t(u8, epd->bInterval, 16);
		अवरोध;
	शेष:
		/* REVISIT we actually want to use NAK limits, hपूर्णांकing to the
		 * transfer scheduling logic to try some other qh, e.g. try
		 * क्रम 2 msec first:
		 *
		 * पूर्णांकerval = (USB_SPEED_HIGH == urb->dev->speed) ? 16 : 2;
		 *
		 * The करोwnside of disabling this is that transfer scheduling
		 * माला_लो VERY unfair क्रम nonperiodic transfers; a misbehaving
		 * peripheral could make that hurt.  That's perfectly normal
		 * क्रम पढ़ोs from network or serial adapters ... so we have
		 * partial NAKlimit support क्रम bulk RX.
		 *
		 * The upside of disabling it is simpler transfer scheduling.
		 */
		पूर्णांकerval = 0;
	पूर्ण
	qh->पूर्णांकv_reg = पूर्णांकerval;

	/* precompute addressing क्रम बाह्यal hub/tt ports */
	अगर (musb->is_multipoपूर्णांक) अणु
		काष्ठा usb_device	*parent = urb->dev->parent;

		अगर (parent != hcd->self.root_hub) अणु
			qh->h_addr_reg = (u8) parent->devnum;

			/* set up tt info अगर needed */
			अगर (urb->dev->tt) अणु
				qh->h_port_reg = (u8) urb->dev->ttport;
				अगर (urb->dev->tt->hub)
					qh->h_addr_reg =
						(u8) urb->dev->tt->hub->devnum;
				अगर (urb->dev->tt->multi)
					qh->h_addr_reg |= 0x80;
			पूर्ण
		पूर्ण
	पूर्ण

	/* invariant: hep->hcpriv is null OR the qh that's alपढ़ोy scheduled.
	 * until we get real dma queues (with an entry क्रम each urb/buffer),
	 * we only have work to करो in the क्रमmer हाल.
	 */
	spin_lock_irqsave(&musb->lock, flags);
	अगर (hep->hcpriv || !next_urb(qh)) अणु
		/* some concurrent activity submitted another urb to hep...
		 * odd, rare, error prone, but legal.
		 */
		kमुक्त(qh);
		qh = शून्य;
		ret = 0;
	पूर्ण अन्यथा
		ret = musb_schedule(musb, qh,
				epd->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK);

	अगर (ret == 0) अणु
		urb->hcpriv = qh;
		/* FIXME set urb->start_frame क्रम iso/पूर्णांकr, it's tested in
		 * musb_start_urb(), but otherwise only konicawc cares ...
		 */
	पूर्ण
	spin_unlock_irqrestore(&musb->lock, flags);

करोne:
	अगर (ret != 0) अणु
		spin_lock_irqsave(&musb->lock, flags);
		usb_hcd_unlink_urb_from_ep(hcd, urb);
		spin_unlock_irqrestore(&musb->lock, flags);
		kमुक्त(qh);
	पूर्ण
	वापस ret;
पूर्ण


/*
 * पात a transfer that's at the head of a hardware queue.
 * called with controller locked, irqs blocked
 * that hardware queue advances to the next transfer, unless prevented
 */
अटल पूर्णांक musb_cleanup_urb(काष्ठा urb *urb, काष्ठा musb_qh *qh)
अणु
	काष्ठा musb_hw_ep	*ep = qh->hw_ep;
	काष्ठा musb		*musb = ep->musb;
	व्योम __iomem		*epio = ep->regs;
	अचिन्हित		hw_end = ep->epnum;
	व्योम __iomem		*regs = ep->musb->mregs;
	पूर्णांक			is_in = usb_pipein(urb->pipe);
	पूर्णांक			status = 0;
	u16			csr;
	काष्ठा dma_channel	*dma = शून्य;

	musb_ep_select(regs, hw_end);

	अगर (is_dma_capable()) अणु
		dma = is_in ? ep->rx_channel : ep->tx_channel;
		अगर (dma) अणु
			status = ep->musb->dma_controller->channel_पात(dma);
			musb_dbg(musb, "abort %cX%d DMA for urb %p --> %d",
				is_in ? 'R' : 'T', ep->epnum,
				urb, status);
			urb->actual_length += dma->actual_len;
		पूर्ण
	पूर्ण

	/* turn off DMA requests, discard state, stop polling ... */
	अगर (ep->epnum && is_in) अणु
		/* giveback saves bulk toggle */
		csr = musb_h_flush_rxfअगरo(ep, 0);

		/* clear the endpoपूर्णांक's irq status here to aव्योम bogus irqs */
		अगर (is_dma_capable() && dma)
			musb_platक्रमm_clear_ep_rxपूर्णांकr(musb, ep->epnum);
	पूर्ण अन्यथा अगर (ep->epnum) अणु
		musb_h_tx_flush_fअगरo(ep);
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		csr &= ~(MUSB_TXCSR_AUTOSET
			| MUSB_TXCSR_DMAENAB
			| MUSB_TXCSR_H_RXSTALL
			| MUSB_TXCSR_H_NAKTIMEOUT
			| MUSB_TXCSR_H_ERROR
			| MUSB_TXCSR_TXPKTRDY);
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		/* REVISIT may need to clear FLUSHFIFO ... */
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		/* flush cpu ग_लिखोbuffer */
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
	पूर्ण अन्यथा  अणु
		musb_h_ep0_flush_fअगरo(ep);
	पूर्ण
	अगर (status == 0)
		musb_advance_schedule(ep->musb, urb, ep, is_in);
	वापस status;
पूर्ण

अटल पूर्णांक musb_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा musb		*musb = hcd_to_musb(hcd);
	काष्ठा musb_qh		*qh;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			is_in  = usb_pipein(urb->pipe);
	पूर्णांक			ret;

	trace_musb_urb_deq(musb, urb);

	spin_lock_irqsave(&musb->lock, flags);
	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (ret)
		जाओ करोne;

	qh = urb->hcpriv;
	अगर (!qh)
		जाओ करोne;

	/*
	 * Any URB not actively programmed पूर्णांकo endpoपूर्णांक hardware can be
	 * immediately given back; that's any URB not at the head of an
	 * endpoपूर्णांक queue, unless someday we get real DMA queues.  And even
	 * अगर it's at the head, it might not be known to the hardware...
	 *
	 * Otherwise पात current transfer, pending DMA, etc.; urb->status
	 * has alपढ़ोy been updated.  This is a synchronous पात; it'd be
	 * OK to hold off until after some IRQ, though.
	 *
	 * NOTE: qh is invalid unless !list_empty(&hep->urb_list)
	 */
	अगर (!qh->is_पढ़ोy
			|| urb->urb_list.prev != &qh->hep->urb_list
			|| musb_ep_get_qh(qh->hw_ep, is_in) != qh) अणु
		पूर्णांक	पढ़ोy = qh->is_पढ़ोy;

		qh->is_पढ़ोy = 0;
		musb_giveback(musb, urb, 0);
		qh->is_पढ़ोy = पढ़ोy;

		/* If nothing अन्यथा (usually musb_giveback) is using it
		 * and its URB list has emptied, recycle this qh.
		 */
		अगर (पढ़ोy && list_empty(&qh->hep->urb_list)) अणु
			qh->hep->hcpriv = शून्य;
			list_del(&qh->ring);
			kमुक्त(qh);
		पूर्ण
	पूर्ण अन्यथा
		ret = musb_cleanup_urb(urb, qh);
करोne:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस ret;
पूर्ण

/* disable an endpoपूर्णांक */
अटल व्योम
musb_h_disable(काष्ठा usb_hcd *hcd, काष्ठा usb_host_endpoपूर्णांक *hep)
अणु
	u8			is_in = hep->desc.bEndpoपूर्णांकAddress & USB_सूची_IN;
	अचिन्हित दीर्घ		flags;
	काष्ठा musb		*musb = hcd_to_musb(hcd);
	काष्ठा musb_qh		*qh;
	काष्ठा urb		*urb;

	spin_lock_irqsave(&musb->lock, flags);

	qh = hep->hcpriv;
	अगर (qh == शून्य)
		जाओ निकास;

	/* NOTE: qh is invalid unless !list_empty(&hep->urb_list) */

	/* Kick the first URB off the hardware, अगर needed */
	qh->is_पढ़ोy = 0;
	अगर (musb_ep_get_qh(qh->hw_ep, is_in) == qh) अणु
		urb = next_urb(qh);

		/* make software (then hardware) stop ASAP */
		अगर (!urb->unlinked)
			urb->status = -ESHUTDOWN;

		/* cleanup */
		musb_cleanup_urb(urb, qh);

		/* Then nuke all the others ... and advance the
		 * queue on hw_ep (e.g. bulk ring) when we're करोne.
		 */
		जबतक (!list_empty(&hep->urb_list)) अणु
			urb = next_urb(qh);
			urb->status = -ESHUTDOWN;
			musb_advance_schedule(musb, urb, qh->hw_ep, is_in);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Just empty the queue; the hardware is busy with
		 * other transfers, and since !qh->is_पढ़ोy nothing
		 * will activate any of these as it advances.
		 */
		जबतक (!list_empty(&hep->urb_list))
			musb_giveback(musb, next_urb(qh), -ESHUTDOWN);

		hep->hcpriv = शून्य;
		list_del(&qh->ring);
		kमुक्त(qh);
	पूर्ण
निकास:
	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

अटल पूर्णांक musb_h_get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);

	वापस musb_पढ़ोw(musb->mregs, MUSB_FRAME);
पूर्ण

अटल पूर्णांक musb_h_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);

	/* NOTE: musb_start() is called when the hub driver turns
	 * on port घातer, or when (OTG) peripheral starts.
	 */
	hcd->state = HC_STATE_RUNNING;
	musb->port1_status = 0;
	वापस 0;
पूर्ण

अटल व्योम musb_h_stop(काष्ठा usb_hcd *hcd)
अणु
	musb_stop(hcd_to_musb(hcd));
	hcd->state = HC_STATE_HALT;
पूर्ण

अटल पूर्णांक musb_bus_suspend(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);
	u8		devctl;
	पूर्णांक		ret;

	ret = musb_port_suspend(musb, true);
	अगर (ret)
		वापस ret;

	अगर (!is_host_active(musb))
		वापस 0;

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_SUSPEND:
		वापस 0;
	हाल OTG_STATE_A_WAIT_VRISE:
		/* ID could be grounded even अगर there's no device
		 * on the other end of the cable.  NOTE that the
		 * A_WAIT_VRISE समयrs are messy with MUSB...
		 */
		devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
		अगर ((devctl & MUSB_DEVCTL_VBUS) == MUSB_DEVCTL_VBUS)
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (musb->is_active) अणु
		WARNING("trying to suspend as %s while active\n",
				usb_otg_state_string(musb->xceiv->otg->state));
		वापस -EBUSY;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक musb_bus_resume(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा musb *musb = hcd_to_musb(hcd);

	अगर (musb->config &&
	    musb->config->host_port_deनिश्चित_reset_at_resume)
		musb_port_reset(musb, false);

	वापस 0;
पूर्ण

#अगर_अघोषित CONFIG_MUSB_PIO_ONLY

#घोषणा MUSB_USB_DMA_ALIGN 4

काष्ठा musb_temp_buffer अणु
	व्योम *kदो_स्मृति_ptr;
	व्योम *old_xfer_buffer;
	u8 data[];
पूर्ण;

अटल व्योम musb_मुक्त_temp_buffer(काष्ठा urb *urb)
अणु
	क्रमागत dma_data_direction dir;
	काष्ठा musb_temp_buffer *temp;
	माप_प्रकार length;

	अगर (!(urb->transfer_flags & URB_ALIGNED_TEMP_BUFFER))
		वापस;

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	temp = container_of(urb->transfer_buffer, काष्ठा musb_temp_buffer,
			    data);

	अगर (dir == DMA_FROM_DEVICE) अणु
		अगर (usb_pipeisoc(urb->pipe))
			length = urb->transfer_buffer_length;
		अन्यथा
			length = urb->actual_length;

		स_नकल(temp->old_xfer_buffer, temp->data, length);
	पूर्ण
	urb->transfer_buffer = temp->old_xfer_buffer;
	kमुक्त(temp->kदो_स्मृति_ptr);

	urb->transfer_flags &= ~URB_ALIGNED_TEMP_BUFFER;
पूर्ण

अटल पूर्णांक musb_alloc_temp_buffer(काष्ठा urb *urb, gfp_t mem_flags)
अणु
	क्रमागत dma_data_direction dir;
	काष्ठा musb_temp_buffer *temp;
	व्योम *kदो_स्मृति_ptr;
	माप_प्रकार kदो_स्मृति_size;

	अगर (urb->num_sgs || urb->sg ||
	    urb->transfer_buffer_length == 0 ||
	    !((uपूर्णांकptr_t)urb->transfer_buffer & (MUSB_USB_DMA_ALIGN - 1)))
		वापस 0;

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	/* Allocate a buffer with enough padding क्रम alignment */
	kदो_स्मृति_size = urb->transfer_buffer_length +
		माप(काष्ठा musb_temp_buffer) + MUSB_USB_DMA_ALIGN - 1;

	kदो_स्मृति_ptr = kदो_स्मृति(kदो_स्मृति_size, mem_flags);
	अगर (!kदो_स्मृति_ptr)
		वापस -ENOMEM;

	/* Position our काष्ठा temp_buffer such that data is aligned */
	temp = PTR_ALIGN(kदो_स्मृति_ptr, MUSB_USB_DMA_ALIGN);


	temp->kदो_स्मृति_ptr = kदो_स्मृति_ptr;
	temp->old_xfer_buffer = urb->transfer_buffer;
	अगर (dir == DMA_TO_DEVICE)
		स_नकल(temp->data, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = temp->data;

	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	वापस 0;
पूर्ण

अटल पूर्णांक musb_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				      gfp_t mem_flags)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);
	पूर्णांक ret;

	/*
	 * The DMA engine in RTL1.8 and above cannot handle
	 * DMA addresses that are not aligned to a 4 byte boundary.
	 * For such engine implemented (un)map_urb_क्रम_dma hooks.
	 * Do not use these hooks क्रम RTL<1.8
	 */
	अगर (musb->hwvers < MUSB_HWVERS_1800)
		वापस usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);

	ret = musb_alloc_temp_buffer(urb, mem_flags);
	अगर (ret)
		वापस ret;

	ret = usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);
	अगर (ret)
		musb_मुक्त_temp_buffer(urb);

	वापस ret;
पूर्ण

अटल व्योम musb_unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	काष्ठा musb	*musb = hcd_to_musb(hcd);

	usb_hcd_unmap_urb_क्रम_dma(hcd, urb);

	/* Do not use this hook क्रम RTL<1.8 (see description above) */
	अगर (musb->hwvers < MUSB_HWVERS_1800)
		वापस;

	musb_मुक्त_temp_buffer(urb);
पूर्ण
#पूर्ण_अगर /* !CONFIG_MUSB_PIO_ONLY */

अटल स्थिर काष्ठा hc_driver musb_hc_driver = अणु
	.description		= "musb-hcd",
	.product_desc		= "MUSB HDRC host driver",
	.hcd_priv_size		= माप(काष्ठा musb *),
	.flags			= HCD_USB2 | HCD_DMA | HCD_MEMORY,

	/* not using irq handler or reset hooks from usbcore, since
	 * those must be shared with peripheral code क्रम OTG configs
	 */

	.start			= musb_h_start,
	.stop			= musb_h_stop,

	.get_frame_number	= musb_h_get_frame_number,

	.urb_enqueue		= musb_urb_enqueue,
	.urb_dequeue		= musb_urb_dequeue,
	.endpoपूर्णांक_disable	= musb_h_disable,

#अगर_अघोषित CONFIG_MUSB_PIO_ONLY
	.map_urb_क्रम_dma	= musb_map_urb_क्रम_dma,
	.unmap_urb_क्रम_dma	= musb_unmap_urb_क्रम_dma,
#पूर्ण_अगर

	.hub_status_data	= musb_hub_status_data,
	.hub_control		= musb_hub_control,
	.bus_suspend		= musb_bus_suspend,
	.bus_resume		= musb_bus_resume,
	/* .start_port_reset	= शून्य, */
	/* .hub_irq_enable	= शून्य, */
पूर्ण;

पूर्णांक musb_host_alloc(काष्ठा musb *musb)
अणु
	काष्ठा device	*dev = musb->controller;

	/* usbcore sets dev->driver_data to hcd, and someबार uses that... */
	musb->hcd = usb_create_hcd(&musb_hc_driver, dev, dev_name(dev));
	अगर (!musb->hcd)
		वापस -EINVAL;

	*musb->hcd->hcd_priv = (अचिन्हित दीर्घ) musb;
	musb->hcd->self.uses_pio_क्रम_control = 1;
	musb->hcd->uses_new_polling = 1;
	musb->hcd->has_tt = 1;

	वापस 0;
पूर्ण

व्योम musb_host_cleanup(काष्ठा musb *musb)
अणु
	अगर (musb->port_mode == MUSB_PERIPHERAL)
		वापस;
	usb_हटाओ_hcd(musb->hcd);
पूर्ण

व्योम musb_host_मुक्त(काष्ठा musb *musb)
अणु
	usb_put_hcd(musb->hcd);
पूर्ण

पूर्णांक musb_host_setup(काष्ठा musb *musb, पूर्णांक घातer_budget)
अणु
	पूर्णांक ret;
	काष्ठा usb_hcd *hcd = musb->hcd;

	अगर (musb->port_mode == MUSB_HOST) अणु
		MUSB_HST_MODE(musb);
		musb->xceiv->otg->state = OTG_STATE_A_IDLE;
	पूर्ण
	otg_set_host(musb->xceiv->otg, &hcd->self);
	/* करोn't support otg protocols */
	hcd->self.otg_port = 0;
	musb->xceiv->otg->host = &hcd->self;
	hcd->घातer_budget = 2 * (घातer_budget ? : 250);
	hcd->skip_phy_initialization = 1;

	ret = usb_add_hcd(hcd, 0, 0);
	अगर (ret < 0)
		वापस ret;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;
पूर्ण

व्योम musb_host_resume_root_hub(काष्ठा musb *musb)
अणु
	usb_hcd_resume_root_hub(musb->hcd);
पूर्ण

व्योम musb_host_poke_root_hub(काष्ठा musb *musb)
अणु
	MUSB_HST_MODE(musb);
	अगर (musb->hcd->status_urb)
		usb_hcd_poll_rh_status(musb->hcd);
	अन्यथा
		usb_hcd_resume_root_hub(musb->hcd);
पूर्ण
