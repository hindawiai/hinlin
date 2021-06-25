<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG driver peripheral support
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 * Copyright (C) 2009 MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश "musb_core.h"
#समावेश "musb_trace.h"


/* ----------------------------------------------------------------------- */

#घोषणा is_buffer_mapped(req) (is_dma_capable() && \
					(req->map_state != UN_MAPPED))

/* Maps the buffer to dma  */

अटल अंतरभूत व्योम map_dma_buffer(काष्ठा musb_request *request,
			काष्ठा musb *musb, काष्ठा musb_ep *musb_ep)
अणु
	पूर्णांक compatible = true;
	काष्ठा dma_controller *dma = musb->dma_controller;

	request->map_state = UN_MAPPED;

	अगर (!is_dma_capable() || !musb_ep->dma)
		वापस;

	/* Check अगर DMA engine can handle this request.
	 * DMA code must reject the USB request explicitly.
	 * Default behaviour is to map the request.
	 */
	अगर (dma->is_compatible)
		compatible = dma->is_compatible(musb_ep->dma,
				musb_ep->packet_sz, request->request.buf,
				request->request.length);
	अगर (!compatible)
		वापस;

	अगर (request->request.dma == DMA_ADDR_INVALID) अणु
		dma_addr_t dma_addr;
		पूर्णांक ret;

		dma_addr = dma_map_single(
				musb->controller,
				request->request.buf,
				request->request.length,
				request->tx
					? DMA_TO_DEVICE
					: DMA_FROM_DEVICE);
		ret = dma_mapping_error(musb->controller, dma_addr);
		अगर (ret)
			वापस;

		request->request.dma = dma_addr;
		request->map_state = MUSB_MAPPED;
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_device(musb->controller,
			request->request.dma,
			request->request.length,
			request->tx
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		request->map_state = PRE_MAPPED;
	पूर्ण
पूर्ण

/* Unmap the buffer from dma and maps it back to cpu */
अटल अंतरभूत व्योम unmap_dma_buffer(काष्ठा musb_request *request,
				काष्ठा musb *musb)
अणु
	काष्ठा musb_ep *musb_ep = request->ep;

	अगर (!is_buffer_mapped(request) || !musb_ep->dma)
		वापस;

	अगर (request->request.dma == DMA_ADDR_INVALID) अणु
		dev_vdbg(musb->controller,
				"not unmapping a never mapped buffer\n");
		वापस;
	पूर्ण
	अगर (request->map_state == MUSB_MAPPED) अणु
		dma_unmap_single(musb->controller,
			request->request.dma,
			request->request.length,
			request->tx
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		request->request.dma = DMA_ADDR_INVALID;
	पूर्ण अन्यथा अणु /* PRE_MAPPED */
		dma_sync_single_क्रम_cpu(musb->controller,
			request->request.dma,
			request->request.length,
			request->tx
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
	पूर्ण
	request->map_state = UN_MAPPED;
पूर्ण

/*
 * Immediately complete a request.
 *
 * @param request the request to complete
 * @param status the status to complete the request with
 * Context: controller locked, IRQs blocked.
 */
व्योम musb_g_giveback(
	काष्ठा musb_ep		*ep,
	काष्ठा usb_request	*request,
	पूर्णांक			status)
__releases(ep->musb->lock)
__acquires(ep->musb->lock)
अणु
	काष्ठा musb_request	*req;
	काष्ठा musb		*musb;
	पूर्णांक			busy = ep->busy;

	req = to_musb_request(request);

	list_del(&req->list);
	अगर (req->request.status == -EINPROGRESS)
		req->request.status = status;
	musb = req->musb;

	ep->busy = 1;
	spin_unlock(&musb->lock);

	अगर (!dma_mapping_error(&musb->g.dev, request->dma))
		unmap_dma_buffer(req, musb);

	trace_musb_req_gb(req);
	usb_gadget_giveback_request(&req->ep->end_poपूर्णांक, &req->request);
	spin_lock(&musb->lock);
	ep->busy = busy;
पूर्ण

/* ----------------------------------------------------------------------- */

/*
 * Abort requests queued to an endpoपूर्णांक using the status. Synchronous.
 * caller locked controller and blocked irqs, and selected this ep.
 */
अटल व्योम nuke(काष्ठा musb_ep *ep, स्थिर पूर्णांक status)
अणु
	काष्ठा musb		*musb = ep->musb;
	काष्ठा musb_request	*req = शून्य;
	व्योम __iomem *epio = ep->musb->endpoपूर्णांकs[ep->current_epnum].regs;

	ep->busy = 1;

	अगर (is_dma_capable() && ep->dma) अणु
		काष्ठा dma_controller	*c = ep->musb->dma_controller;
		पूर्णांक value;

		अगर (ep->is_in) अणु
			/*
			 * The programming guide says that we must not clear
			 * the DMAMODE bit beक्रमe DMAENAB, so we only
			 * clear it in the second ग_लिखो...
			 */
			musb_ग_लिखोw(epio, MUSB_TXCSR,
				    MUSB_TXCSR_DMAMODE | MUSB_TXCSR_FLUSHFIFO);
			musb_ग_लिखोw(epio, MUSB_TXCSR,
					0 | MUSB_TXCSR_FLUSHFIFO);
		पूर्ण अन्यथा अणु
			musb_ग_लिखोw(epio, MUSB_RXCSR,
					0 | MUSB_RXCSR_FLUSHFIFO);
			musb_ग_लिखोw(epio, MUSB_RXCSR,
					0 | MUSB_RXCSR_FLUSHFIFO);
		पूर्ण

		value = c->channel_पात(ep->dma);
		musb_dbg(musb, "%s: abort DMA --> %d", ep->name, value);
		c->channel_release(ep->dma);
		ep->dma = शून्य;
	पूर्ण

	जबतक (!list_empty(&ep->req_list)) अणु
		req = list_first_entry(&ep->req_list, काष्ठा musb_request, list);
		musb_g_giveback(ep, &req->request, status);
	पूर्ण
पूर्ण

/* ----------------------------------------------------------------------- */

/* Data transfers - pure PIO, pure DMA, or mixed mode */

/*
 * This assumes the separate CPPI engine is responding to DMA requests
 * from the usb core ... sequenced a bit dअगरferently from mentor dma.
 */

अटल अंतरभूत पूर्णांक max_ep_ग_लिखोsize(काष्ठा musb *musb, काष्ठा musb_ep *ep)
अणु
	अगर (can_bulk_split(musb, ep->type))
		वापस ep->hw_ep->max_packet_sz_tx;
	अन्यथा
		वापस ep->packet_sz;
पूर्ण

/*
 * An endpoपूर्णांक is transmitting data. This can be called either from
 * the IRQ routine or from ep.queue() to kickstart a request on an
 * endpoपूर्णांक.
 *
 * Context: controller locked, IRQs blocked, endpoपूर्णांक selected
 */
अटल व्योम txstate(काष्ठा musb *musb, काष्ठा musb_request *req)
अणु
	u8			epnum = req->epnum;
	काष्ठा musb_ep		*musb_ep;
	व्योम __iomem		*epio = musb->endpoपूर्णांकs[epnum].regs;
	काष्ठा usb_request	*request;
	u16			fअगरo_count = 0, csr;
	पूर्णांक			use_dma = 0;

	musb_ep = req->ep;

	/* Check अगर EP is disabled */
	अगर (!musb_ep->desc) अणु
		musb_dbg(musb, "ep:%s disabled - ignore request",
						musb_ep->end_poपूर्णांक.name);
		वापस;
	पूर्ण

	/* we shouldn't get here जबतक DMA is active ... but we करो ... */
	अगर (dma_channel_status(musb_ep->dma) == MUSB_DMA_STATUS_BUSY) अणु
		musb_dbg(musb, "dma pending...");
		वापस;
	पूर्ण

	/* पढ़ो TXCSR beक्रमe */
	csr = musb_पढ़ोw(epio, MUSB_TXCSR);

	request = &req->request;
	fअगरo_count = min(max_ep_ग_लिखोsize(musb, musb_ep),
			(पूर्णांक)(request->length - request->actual));

	अगर (csr & MUSB_TXCSR_TXPKTRDY) अणु
		musb_dbg(musb, "%s old packet still ready , txcsr %03x",
				musb_ep->end_poपूर्णांक.name, csr);
		वापस;
	पूर्ण

	अगर (csr & MUSB_TXCSR_P_SENDSTALL) अणु
		musb_dbg(musb, "%s stalling, txcsr %03x",
				musb_ep->end_poपूर्णांक.name, csr);
		वापस;
	पूर्ण

	musb_dbg(musb, "hw_ep%d, maxpacket %d, fifo count %d, txcsr %03x",
			epnum, musb_ep->packet_sz, fअगरo_count,
			csr);

#अगर_अघोषित	CONFIG_MUSB_PIO_ONLY
	अगर (is_buffer_mapped(req)) अणु
		काष्ठा dma_controller	*c = musb->dma_controller;
		माप_प्रकार request_size;

		/* setup DMA, then program endpoपूर्णांक CSR */
		request_size = min_t(माप_प्रकार, request->length - request->actual,
					musb_ep->dma->max_len);

		use_dma = (request->dma != DMA_ADDR_INVALID && request_size);

		/* MUSB_TXCSR_P_ISO is still set correctly */

		अगर (musb_dma_inventra(musb) || musb_dma_ux500(musb)) अणु
			अगर (request_size < musb_ep->packet_sz)
				musb_ep->dma->desired_mode = 0;
			अन्यथा
				musb_ep->dma->desired_mode = 1;

			use_dma = use_dma && c->channel_program(
					musb_ep->dma, musb_ep->packet_sz,
					musb_ep->dma->desired_mode,
					request->dma + request->actual, request_size);
			अगर (use_dma) अणु
				अगर (musb_ep->dma->desired_mode == 0) अणु
					/*
					 * We must not clear the DMAMODE bit
					 * beक्रमe the DMAENAB bit -- and the
					 * latter करोesn't always get cleared
					 * beक्रमe we get here...
					 */
					csr &= ~(MUSB_TXCSR_AUTOSET
						| MUSB_TXCSR_DMAENAB);
					musb_ग_लिखोw(epio, MUSB_TXCSR, csr
						| MUSB_TXCSR_P_WZC_BITS);
					csr &= ~MUSB_TXCSR_DMAMODE;
					csr |= (MUSB_TXCSR_DMAENAB |
							MUSB_TXCSR_MODE);
					/* against programming guide */
				पूर्ण अन्यथा अणु
					csr |= (MUSB_TXCSR_DMAENAB
							| MUSB_TXCSR_DMAMODE
							| MUSB_TXCSR_MODE);
					/*
					 * Enable Autoset according to table
					 * below
					 * bulk_split hb_mult	Autoset_Enable
					 *	0	0	Yes(Normal)
					 *	0	>0	No(High BW ISO)
					 *	1	0	Yes(HS bulk)
					 *	1	>0	Yes(FS bulk)
					 */
					अगर (!musb_ep->hb_mult ||
					    can_bulk_split(musb,
							   musb_ep->type))
						csr |= MUSB_TXCSR_AUTOSET;
				पूर्ण
				csr &= ~MUSB_TXCSR_P_UNDERRUN;

				musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
			पूर्ण
		पूर्ण

		अगर (is_cppi_enabled(musb)) अणु
			/* program endpoपूर्णांक CSR first, then setup DMA */
			csr &= ~(MUSB_TXCSR_P_UNDERRUN | MUSB_TXCSR_TXPKTRDY);
			csr |= MUSB_TXCSR_DMAENAB | MUSB_TXCSR_DMAMODE |
				MUSB_TXCSR_MODE;
			musb_ग_लिखोw(epio, MUSB_TXCSR, (MUSB_TXCSR_P_WZC_BITS &
						~MUSB_TXCSR_P_UNDERRUN) | csr);

			/* ensure ग_लिखोbuffer is empty */
			csr = musb_पढ़ोw(epio, MUSB_TXCSR);

			/*
			 * NOTE host side sets DMAENAB later than this; both are
			 * OK since the transfer dma glue (between CPPI and
			 * Mentor fअगरos) just tells CPPI it could start. Data
			 * only moves to the USB TX fअगरo when both fअगरos are
			 * पढ़ोy.
			 */
			/*
			 * "mode" is irrelevant here; handle terminating ZLPs
			 * like PIO करोes, since the hardware RNDIS mode seems
			 * unreliable except क्रम the
			 * last-packet-is-alपढ़ोy-लघु हाल.
			 */
			use_dma = use_dma && c->channel_program(
					musb_ep->dma, musb_ep->packet_sz,
					0,
					request->dma + request->actual,
					request_size);
			अगर (!use_dma) अणु
				c->channel_release(musb_ep->dma);
				musb_ep->dma = शून्य;
				csr &= ~MUSB_TXCSR_DMAENAB;
				musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
				/* invariant: prequest->buf is non-null */
			पूर्ण
		पूर्ण अन्यथा अगर (tusb_dma_omap(musb))
			use_dma = use_dma && c->channel_program(
					musb_ep->dma, musb_ep->packet_sz,
					request->zero,
					request->dma + request->actual,
					request_size);
	पूर्ण
#पूर्ण_अगर

	अगर (!use_dma) अणु
		/*
		 * Unmap the dma buffer back to cpu अगर dma channel
		 * programming fails
		 */
		unmap_dma_buffer(req, musb);

		musb_ग_लिखो_fअगरo(musb_ep->hw_ep, fअगरo_count,
				(u8 *) (request->buf + request->actual));
		request->actual += fअगरo_count;
		csr |= MUSB_TXCSR_TXPKTRDY;
		csr &= ~MUSB_TXCSR_P_UNDERRUN;
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
	पूर्ण

	/* host may alपढ़ोy have the data when this message shows... */
	musb_dbg(musb, "%s TX/IN %s len %d/%d, txcsr %04x, fifo %d/%d",
			musb_ep->end_poपूर्णांक.name, use_dma ? "dma" : "pio",
			request->actual, request->length,
			musb_पढ़ोw(epio, MUSB_TXCSR),
			fअगरo_count,
			musb_पढ़ोw(epio, MUSB_TXMAXP));
पूर्ण

/*
 * FIFO state update (e.g. data पढ़ोy).
 * Called from IRQ,  with controller locked.
 */
व्योम musb_g_tx(काष्ठा musb *musb, u8 epnum)
अणु
	u16			csr;
	काष्ठा musb_request	*req;
	काष्ठा usb_request	*request;
	u8 __iomem		*mbase = musb->mregs;
	काष्ठा musb_ep		*musb_ep = &musb->endpoपूर्णांकs[epnum].ep_in;
	व्योम __iomem		*epio = musb->endpoपूर्णांकs[epnum].regs;
	काष्ठा dma_channel	*dma;

	musb_ep_select(mbase, epnum);
	req = next_request(musb_ep);
	request = &req->request;

	csr = musb_पढ़ोw(epio, MUSB_TXCSR);
	musb_dbg(musb, "<== %s, txcsr %04x", musb_ep->end_poपूर्णांक.name, csr);

	dma = is_dma_capable() ? musb_ep->dma : शून्य;

	/*
	 * REVISIT: क्रम high bandwidth, MUSB_TXCSR_P_INCOMPTX
	 * probably rates reporting as a host error.
	 */
	अगर (csr & MUSB_TXCSR_P_SENTSTALL) अणु
		csr |=	MUSB_TXCSR_P_WZC_BITS;
		csr &= ~MUSB_TXCSR_P_SENTSTALL;
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		वापस;
	पूर्ण

	अगर (csr & MUSB_TXCSR_P_UNDERRUN) अणु
		/* We NAKed, no big deal... little reason to care. */
		csr |=	 MUSB_TXCSR_P_WZC_BITS;
		csr &= ~(MUSB_TXCSR_P_UNDERRUN | MUSB_TXCSR_TXPKTRDY);
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		dev_vdbg(musb->controller, "underrun on ep%d, req %p\n",
				epnum, request);
	पूर्ण

	अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
		/*
		 * SHOULD NOT HAPPEN... has with CPPI though, after
		 * changing SENDSTALL (and other हालs); harmless?
		 */
		musb_dbg(musb, "%s dma still busy?", musb_ep->end_poपूर्णांक.name);
		वापस;
	पूर्ण

	अगर (req) अणु

		trace_musb_req_tx(req);

		अगर (dma && (csr & MUSB_TXCSR_DMAENAB)) अणु
			csr |= MUSB_TXCSR_P_WZC_BITS;
			csr &= ~(MUSB_TXCSR_DMAENAB | MUSB_TXCSR_P_UNDERRUN |
				 MUSB_TXCSR_TXPKTRDY | MUSB_TXCSR_AUTOSET);
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
			/* Ensure ग_लिखोbuffer is empty. */
			csr = musb_पढ़ोw(epio, MUSB_TXCSR);
			request->actual += musb_ep->dma->actual_len;
			musb_dbg(musb, "TXCSR%d %04x, DMA off, len %zu, req %p",
				epnum, csr, musb_ep->dma->actual_len, request);
		पूर्ण

		/*
		 * First, maybe a terminating लघु packet. Some DMA
		 * engines might handle this by themselves.
		 */
		अगर ((request->zero && request->length)
			&& (request->length % musb_ep->packet_sz == 0)
			&& (request->actual == request->length)) अणु

			/*
			 * On DMA completion, FIFO may not be
			 * available yet...
			 */
			अगर (csr & MUSB_TXCSR_TXPKTRDY)
				वापस;

			musb_ग_लिखोw(epio, MUSB_TXCSR, MUSB_TXCSR_MODE
					| MUSB_TXCSR_TXPKTRDY);
			request->zero = 0;
		पूर्ण

		अगर (request->actual == request->length) अणु
			musb_g_giveback(musb_ep, request, 0);
			/*
			 * In the giveback function the MUSB lock is
			 * released and acquired after someसमय. During
			 * this समय period the INDEX रेजिस्टर could get
			 * changed by the gadget_queue function especially
			 * on SMP प्रणालीs. Reselect the INDEX to be sure
			 * we are पढ़ोing/modअगरying the right रेजिस्टरs
			 */
			musb_ep_select(mbase, epnum);
			req = musb_ep->desc ? next_request(musb_ep) : शून्य;
			अगर (!req) अणु
				musb_dbg(musb, "%s idle now",
					musb_ep->end_poपूर्णांक.name);
				वापस;
			पूर्ण
		पूर्ण

		txstate(musb, req);
	पूर्ण
पूर्ण

/* ------------------------------------------------------------ */

/*
 * Context: controller locked, IRQs blocked, endpoपूर्णांक selected
 */
अटल व्योम rxstate(काष्ठा musb *musb, काष्ठा musb_request *req)
अणु
	स्थिर u8		epnum = req->epnum;
	काष्ठा usb_request	*request = &req->request;
	काष्ठा musb_ep		*musb_ep;
	व्योम __iomem		*epio = musb->endpoपूर्णांकs[epnum].regs;
	अचिन्हित		len = 0;
	u16			fअगरo_count;
	u16			csr = musb_पढ़ोw(epio, MUSB_RXCSR);
	काष्ठा musb_hw_ep	*hw_ep = &musb->endpoपूर्णांकs[epnum];
	u8			use_mode_1;

	अगर (hw_ep->is_shared_fअगरo)
		musb_ep = &hw_ep->ep_in;
	अन्यथा
		musb_ep = &hw_ep->ep_out;

	fअगरo_count = musb_ep->packet_sz;

	/* Check अगर EP is disabled */
	अगर (!musb_ep->desc) अणु
		musb_dbg(musb, "ep:%s disabled - ignore request",
						musb_ep->end_poपूर्णांक.name);
		वापस;
	पूर्ण

	/* We shouldn't get here जबतक DMA is active, but we करो... */
	अगर (dma_channel_status(musb_ep->dma) == MUSB_DMA_STATUS_BUSY) अणु
		musb_dbg(musb, "DMA pending...");
		वापस;
	पूर्ण

	अगर (csr & MUSB_RXCSR_P_SENDSTALL) अणु
		musb_dbg(musb, "%s stalling, RXCSR %04x",
		    musb_ep->end_poपूर्णांक.name, csr);
		वापस;
	पूर्ण

	अगर (is_cppi_enabled(musb) && is_buffer_mapped(req)) अणु
		काष्ठा dma_controller	*c = musb->dma_controller;
		काष्ठा dma_channel	*channel = musb_ep->dma;

		/* NOTE:  CPPI won't actually stop advancing the DMA
		 * queue after लघु packet transfers, so this is almost
		 * always going to run as IRQ-per-packet DMA so that
		 * faults will be handled correctly.
		 */
		अगर (c->channel_program(channel,
				musb_ep->packet_sz,
				!request->लघु_not_ok,
				request->dma + request->actual,
				request->length - request->actual)) अणु

			/* make sure that अगर an rxpkt arrived after the irq,
			 * the cppi engine will be पढ़ोy to take it as soon
			 * as DMA is enabled
			 */
			csr &= ~(MUSB_RXCSR_AUTOCLEAR
					| MUSB_RXCSR_DMAMODE);
			csr |= MUSB_RXCSR_DMAENAB | MUSB_RXCSR_P_WZC_BITS;
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
			वापस;
		पूर्ण
	पूर्ण

	अगर (csr & MUSB_RXCSR_RXPKTRDY) अणु
		fअगरo_count = musb_पढ़ोw(epio, MUSB_RXCOUNT);

		/*
		 * Enable Mode 1 on RX transfers only when लघु_not_ok flag
		 * is set. Currently लघु_not_ok flag is set only from
		 * file_storage and f_mass_storage drivers
		 */

		अगर (request->लघु_not_ok && fअगरo_count == musb_ep->packet_sz)
			use_mode_1 = 1;
		अन्यथा
			use_mode_1 = 0;

		अगर (request->actual < request->length) अणु
			अगर (!is_buffer_mapped(req))
				जाओ buffer_aपूर्णांक_mapped;

			अगर (musb_dma_inventra(musb)) अणु
				काष्ठा dma_controller	*c;
				काष्ठा dma_channel	*channel;
				पूर्णांक			use_dma = 0;
				अचिन्हित पूर्णांक transfer_size;

				c = musb->dma_controller;
				channel = musb_ep->dma;

	/* We use DMA Req mode 0 in rx_csr, and DMA controller operates in
	 * mode 0 only. So we करो not get endpoपूर्णांक पूर्णांकerrupts due to DMA
	 * completion. We only get पूर्णांकerrupts from DMA controller.
	 *
	 * We could operate in DMA mode 1 अगर we knew the size of the tranfer
	 * in advance. For mass storage class, request->length = what the host
	 * sends, so that'd work.  But क्रम pretty much everything अन्यथा,
	 * request->length is routinely more than what the host sends. For
	 * most these gadमाला_लो, end of is signअगरied either by a लघु packet,
	 * or filling the last byte of the buffer.  (Sending extra data in
	 * that last pckate should trigger an overflow fault.)  But in mode 1,
	 * we करोn't get DMA completion पूर्णांकerrupt क्रम लघु packets.
	 *
	 * Theoretically, we could enable DMAReq irq (MUSB_RXCSR_DMAMODE = 1),
	 * to get endpoपूर्णांक पूर्णांकerrupt on every DMA req, but that didn't seem
	 * to work reliably.
	 *
	 * REVISIT an updated g_file_storage can set req->लघु_not_ok, which
	 * then becomes usable as a runसमय "use mode 1" hपूर्णांक...
	 */

				/* Experimental: Mode1 works with mass storage use हालs */
				अगर (use_mode_1) अणु
					csr |= MUSB_RXCSR_AUTOCLEAR;
					musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
					csr |= MUSB_RXCSR_DMAENAB;
					musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

					/*
					 * this special sequence (enabling and then
					 * disabling MUSB_RXCSR_DMAMODE) is required
					 * to get DMAReq to activate
					 */
					musb_ग_लिखोw(epio, MUSB_RXCSR,
						csr | MUSB_RXCSR_DMAMODE);
					musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

					transfer_size = min_t(अचिन्हित पूर्णांक,
							request->length -
							request->actual,
							channel->max_len);
					musb_ep->dma->desired_mode = 1;
				पूर्ण अन्यथा अणु
					अगर (!musb_ep->hb_mult &&
						musb_ep->hw_ep->rx_द्विगुन_buffered)
						csr |= MUSB_RXCSR_AUTOCLEAR;
					csr |= MUSB_RXCSR_DMAENAB;
					musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

					transfer_size = min(request->length - request->actual,
							(अचिन्हित)fअगरo_count);
					musb_ep->dma->desired_mode = 0;
				पूर्ण

				use_dma = c->channel_program(
						channel,
						musb_ep->packet_sz,
						channel->desired_mode,
						request->dma
						+ request->actual,
						transfer_size);

				अगर (use_dma)
					वापस;
			पूर्ण

			अगर ((musb_dma_ux500(musb)) &&
				(request->actual < request->length)) अणु

				काष्ठा dma_controller *c;
				काष्ठा dma_channel *channel;
				अचिन्हित पूर्णांक transfer_size = 0;

				c = musb->dma_controller;
				channel = musb_ep->dma;

				/* In हाल first packet is लघु */
				अगर (fअगरo_count < musb_ep->packet_sz)
					transfer_size = fअगरo_count;
				अन्यथा अगर (request->लघु_not_ok)
					transfer_size =	min_t(अचिन्हित पूर्णांक,
							request->length -
							request->actual,
							channel->max_len);
				अन्यथा
					transfer_size = min_t(अचिन्हित पूर्णांक,
							request->length -
							request->actual,
							(अचिन्हित)fअगरo_count);

				csr &= ~MUSB_RXCSR_DMAMODE;
				csr |= (MUSB_RXCSR_DMAENAB |
					MUSB_RXCSR_AUTOCLEAR);

				musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

				अगर (transfer_size <= musb_ep->packet_sz) अणु
					musb_ep->dma->desired_mode = 0;
				पूर्ण अन्यथा अणु
					musb_ep->dma->desired_mode = 1;
					/* Mode must be set after DMAENAB */
					csr |= MUSB_RXCSR_DMAMODE;
					musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
				पूर्ण

				अगर (c->channel_program(channel,
							musb_ep->packet_sz,
							channel->desired_mode,
							request->dma
							+ request->actual,
							transfer_size))

					वापस;
			पूर्ण

			len = request->length - request->actual;
			musb_dbg(musb, "%s OUT/RX pio fifo %d/%d, maxpacket %d",
					musb_ep->end_poपूर्णांक.name,
					fअगरo_count, len,
					musb_ep->packet_sz);

			fअगरo_count = min_t(अचिन्हित, len, fअगरo_count);

			अगर (tusb_dma_omap(musb)) अणु
				काष्ठा dma_controller *c = musb->dma_controller;
				काष्ठा dma_channel *channel = musb_ep->dma;
				u32 dma_addr = request->dma + request->actual;
				पूर्णांक ret;

				ret = c->channel_program(channel,
						musb_ep->packet_sz,
						channel->desired_mode,
						dma_addr,
						fअगरo_count);
				अगर (ret)
					वापस;
			पूर्ण

			/*
			 * Unmap the dma buffer back to cpu अगर dma channel
			 * programming fails. This buffer is mapped अगर the
			 * channel allocation is successful
			 */
			unmap_dma_buffer(req, musb);

			/*
			 * Clear DMAENAB and AUTOCLEAR क्रम the
			 * PIO mode transfer
			 */
			csr &= ~(MUSB_RXCSR_DMAENAB | MUSB_RXCSR_AUTOCLEAR);
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

buffer_aपूर्णांक_mapped:
			musb_पढ़ो_fअगरo(musb_ep->hw_ep, fअगरo_count, (u8 *)
					(request->buf + request->actual));
			request->actual += fअगरo_count;

			/* REVISIT अगर we left anything in the fअगरo, flush
			 * it and report -EOVERFLOW
			 */

			/* ack the पढ़ो! */
			csr |= MUSB_RXCSR_P_WZC_BITS;
			csr &= ~MUSB_RXCSR_RXPKTRDY;
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		पूर्ण
	पूर्ण

	/* reach the end or लघु packet detected */
	अगर (request->actual == request->length ||
	    fअगरo_count < musb_ep->packet_sz)
		musb_g_giveback(musb_ep, request, 0);
पूर्ण

/*
 * Data पढ़ोy क्रम a request; called from IRQ
 */
व्योम musb_g_rx(काष्ठा musb *musb, u8 epnum)
अणु
	u16			csr;
	काष्ठा musb_request	*req;
	काष्ठा usb_request	*request;
	व्योम __iomem		*mbase = musb->mregs;
	काष्ठा musb_ep		*musb_ep;
	व्योम __iomem		*epio = musb->endpoपूर्णांकs[epnum].regs;
	काष्ठा dma_channel	*dma;
	काष्ठा musb_hw_ep	*hw_ep = &musb->endpoपूर्णांकs[epnum];

	अगर (hw_ep->is_shared_fअगरo)
		musb_ep = &hw_ep->ep_in;
	अन्यथा
		musb_ep = &hw_ep->ep_out;

	musb_ep_select(mbase, epnum);

	req = next_request(musb_ep);
	अगर (!req)
		वापस;

	trace_musb_req_rx(req);
	request = &req->request;

	csr = musb_पढ़ोw(epio, MUSB_RXCSR);
	dma = is_dma_capable() ? musb_ep->dma : शून्य;

	musb_dbg(musb, "<== %s, rxcsr %04x%s %p", musb_ep->end_poपूर्णांक.name,
			csr, dma ? " (dma)" : "", request);

	अगर (csr & MUSB_RXCSR_P_SENTSTALL) अणु
		csr |= MUSB_RXCSR_P_WZC_BITS;
		csr &= ~MUSB_RXCSR_P_SENTSTALL;
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		वापस;
	पूर्ण

	अगर (csr & MUSB_RXCSR_P_OVERRUN) अणु
		/* csr |= MUSB_RXCSR_P_WZC_BITS; */
		csr &= ~MUSB_RXCSR_P_OVERRUN;
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);

		musb_dbg(musb, "%s iso overrun on %p", musb_ep->name, request);
		अगर (request->status == -EINPROGRESS)
			request->status = -EOVERFLOW;
	पूर्ण
	अगर (csr & MUSB_RXCSR_INCOMPRX) अणु
		/* REVISIT not necessarily an error */
		musb_dbg(musb, "%s, incomprx", musb_ep->end_poपूर्णांक.name);
	पूर्ण

	अगर (dma_channel_status(dma) == MUSB_DMA_STATUS_BUSY) अणु
		/* "should not happen"; likely RXPKTRDY pending क्रम DMA */
		musb_dbg(musb, "%s busy, csr %04x",
			musb_ep->end_poपूर्णांक.name, csr);
		वापस;
	पूर्ण

	अगर (dma && (csr & MUSB_RXCSR_DMAENAB)) अणु
		csr &= ~(MUSB_RXCSR_AUTOCLEAR
				| MUSB_RXCSR_DMAENAB
				| MUSB_RXCSR_DMAMODE);
		musb_ग_लिखोw(epio, MUSB_RXCSR,
			MUSB_RXCSR_P_WZC_BITS | csr);

		request->actual += musb_ep->dma->actual_len;

#अगर defined(CONFIG_USB_INVENTRA_DMA) || defined(CONFIG_USB_TUSB_OMAP_DMA) || \
	defined(CONFIG_USB_UX500_DMA)
		/* Autoclear करोesn't clear RxPktRdy क्रम लघु packets */
		अगर ((dma->desired_mode == 0 && !hw_ep->rx_द्विगुन_buffered)
				|| (dma->actual_len
					& (musb_ep->packet_sz - 1))) अणु
			/* ack the पढ़ो! */
			csr &= ~MUSB_RXCSR_RXPKTRDY;
			musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		पूर्ण

		/* incomplete, and not लघु? रुको क्रम next IN packet */
		अगर ((request->actual < request->length)
				&& (musb_ep->dma->actual_len
					== musb_ep->packet_sz)) अणु
			/* In द्विगुन buffer हाल, जारी to unload fअगरo अगर
 			 * there is Rx packet in FIFO.
 			 **/
			csr = musb_पढ़ोw(epio, MUSB_RXCSR);
			अगर ((csr & MUSB_RXCSR_RXPKTRDY) &&
				hw_ep->rx_द्विगुन_buffered)
				जाओ निकास;
			वापस;
		पूर्ण
#पूर्ण_अगर
		musb_g_giveback(musb_ep, request, 0);
		/*
		 * In the giveback function the MUSB lock is
		 * released and acquired after someसमय. During
		 * this समय period the INDEX रेजिस्टर could get
		 * changed by the gadget_queue function especially
		 * on SMP प्रणालीs. Reselect the INDEX to be sure
		 * we are पढ़ोing/modअगरying the right रेजिस्टरs
		 */
		musb_ep_select(mbase, epnum);

		req = next_request(musb_ep);
		अगर (!req)
			वापस;
	पूर्ण
#अगर defined(CONFIG_USB_INVENTRA_DMA) || defined(CONFIG_USB_TUSB_OMAP_DMA) || \
	defined(CONFIG_USB_UX500_DMA)
निकास:
#पूर्ण_अगर
	/* Analyze request */
	rxstate(musb, req);
पूर्ण

/* ------------------------------------------------------------ */

अटल पूर्णांक musb_gadget_enable(काष्ठा usb_ep *ep,
			स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा musb_ep		*musb_ep;
	काष्ठा musb_hw_ep	*hw_ep;
	व्योम __iomem		*regs;
	काष्ठा musb		*musb;
	व्योम __iomem	*mbase;
	u8		epnum;
	u16		csr;
	अचिन्हित	पंचांगp;
	पूर्णांक		status = -EINVAL;

	अगर (!ep || !desc)
		वापस -EINVAL;

	musb_ep = to_musb_ep(ep);
	hw_ep = musb_ep->hw_ep;
	regs = hw_ep->regs;
	musb = musb_ep->musb;
	mbase = musb->mregs;
	epnum = musb_ep->current_epnum;

	spin_lock_irqsave(&musb->lock, flags);

	अगर (musb_ep->desc) अणु
		status = -EBUSY;
		जाओ fail;
	पूर्ण
	musb_ep->type = usb_endpoपूर्णांक_type(desc);

	/* check direction and (later) maxpacket size against endpoपूर्णांक */
	अगर (usb_endpoपूर्णांक_num(desc) != epnum)
		जाओ fail;

	/* REVISIT this rules out high bandwidth periodic transfers */
	पंचांगp = usb_endpoपूर्णांक_maxp_mult(desc) - 1;
	अगर (पंचांगp) अणु
		पूर्णांक ok;

		अगर (usb_endpoपूर्णांक_dir_in(desc))
			ok = musb->hb_iso_tx;
		अन्यथा
			ok = musb->hb_iso_rx;

		अगर (!ok) अणु
			musb_dbg(musb, "no support for high bandwidth ISO");
			जाओ fail;
		पूर्ण
		musb_ep->hb_mult = पंचांगp;
	पूर्ण अन्यथा अणु
		musb_ep->hb_mult = 0;
	पूर्ण

	musb_ep->packet_sz = usb_endpoपूर्णांक_maxp(desc);
	पंचांगp = musb_ep->packet_sz * (musb_ep->hb_mult + 1);

	/* enable the पूर्णांकerrupts क्रम the endpoपूर्णांक, set the endpoपूर्णांक
	 * packet size (or fail), set the mode, clear the fअगरo
	 */
	musb_ep_select(mbase, epnum);
	अगर (usb_endpoपूर्णांक_dir_in(desc)) अणु

		अगर (hw_ep->is_shared_fअगरo)
			musb_ep->is_in = 1;
		अगर (!musb_ep->is_in)
			जाओ fail;

		अगर (पंचांगp > hw_ep->max_packet_sz_tx) अणु
			musb_dbg(musb, "packet size beyond hardware FIFO size");
			जाओ fail;
		पूर्ण

		musb->पूर्णांकrtxe |= (1 << epnum);
		musb_ग_लिखोw(mbase, MUSB_INTRTXE, musb->पूर्णांकrtxe);

		/* REVISIT अगर can_bulk_split(), use by updating "tmp";
		 * likewise high bandwidth periodic tx
		 */
		/* Set TXMAXP with the FIFO size of the endpoपूर्णांक
		 * to disable द्विगुन buffering mode.
		 */
		अगर (can_bulk_split(musb, musb_ep->type))
			musb_ep->hb_mult = (hw_ep->max_packet_sz_tx /
						musb_ep->packet_sz) - 1;
		musb_ग_लिखोw(regs, MUSB_TXMAXP, musb_ep->packet_sz
				| (musb_ep->hb_mult << 11));

		csr = MUSB_TXCSR_MODE | MUSB_TXCSR_CLRDATATOG;
		अगर (musb_पढ़ोw(regs, MUSB_TXCSR)
				& MUSB_TXCSR_FIFONOTEMPTY)
			csr |= MUSB_TXCSR_FLUSHFIFO;
		अगर (musb_ep->type == USB_ENDPOINT_XFER_ISOC)
			csr |= MUSB_TXCSR_P_ISO;

		/* set twice in हाल of द्विगुन buffering */
		musb_ग_लिखोw(regs, MUSB_TXCSR, csr);
		/* REVISIT may be inappropriate w/o FIFONOTEMPTY ... */
		musb_ग_लिखोw(regs, MUSB_TXCSR, csr);

	पूर्ण अन्यथा अणु

		अगर (hw_ep->is_shared_fअगरo)
			musb_ep->is_in = 0;
		अगर (musb_ep->is_in)
			जाओ fail;

		अगर (पंचांगp > hw_ep->max_packet_sz_rx) अणु
			musb_dbg(musb, "packet size beyond hardware FIFO size");
			जाओ fail;
		पूर्ण

		musb->पूर्णांकrrxe |= (1 << epnum);
		musb_ग_लिखोw(mbase, MUSB_INTRRXE, musb->पूर्णांकrrxe);

		/* REVISIT अगर can_bulk_combine() use by updating "tmp"
		 * likewise high bandwidth periodic rx
		 */
		/* Set RXMAXP with the FIFO size of the endpoपूर्णांक
		 * to disable द्विगुन buffering mode.
		 */
		musb_ग_लिखोw(regs, MUSB_RXMAXP, musb_ep->packet_sz
				| (musb_ep->hb_mult << 11));

		/* क्रमce shared fअगरo to OUT-only mode */
		अगर (hw_ep->is_shared_fअगरo) अणु
			csr = musb_पढ़ोw(regs, MUSB_TXCSR);
			csr &= ~(MUSB_TXCSR_MODE | MUSB_TXCSR_TXPKTRDY);
			musb_ग_लिखोw(regs, MUSB_TXCSR, csr);
		पूर्ण

		csr = MUSB_RXCSR_FLUSHFIFO | MUSB_RXCSR_CLRDATATOG;
		अगर (musb_ep->type == USB_ENDPOINT_XFER_ISOC)
			csr |= MUSB_RXCSR_P_ISO;
		अन्यथा अगर (musb_ep->type == USB_ENDPOINT_XFER_INT)
			csr |= MUSB_RXCSR_DISNYET;

		/* set twice in हाल of द्विगुन buffering */
		musb_ग_लिखोw(regs, MUSB_RXCSR, csr);
		musb_ग_लिखोw(regs, MUSB_RXCSR, csr);
	पूर्ण

	/* NOTE:  all the I/O code _should_ work fine without DMA, in हाल
	 * क्रम some reason you run out of channels here.
	 */
	अगर (is_dma_capable() && musb->dma_controller) अणु
		काष्ठा dma_controller	*c = musb->dma_controller;

		musb_ep->dma = c->channel_alloc(c, hw_ep,
				(desc->bEndpoपूर्णांकAddress & USB_सूची_IN));
	पूर्ण अन्यथा
		musb_ep->dma = शून्य;

	musb_ep->desc = desc;
	musb_ep->busy = 0;
	musb_ep->wedged = 0;
	status = 0;

	pr_debug("%s periph: enabled %s for %s %s, %smaxpacket %d\n",
			musb_driver_name, musb_ep->end_poपूर्णांक.name,
			musb_ep_xfertype_string(musb_ep->type),
			musb_ep->is_in ? "IN" : "OUT",
			musb_ep->dma ? "dma, " : "",
			musb_ep->packet_sz);

	schedule_delayed_work(&musb->irq_work, 0);

fail:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस status;
पूर्ण

/*
 * Disable an endpoपूर्णांक flushing all requests queued.
 */
अटल पूर्णांक musb_gadget_disable(काष्ठा usb_ep *ep)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा musb	*musb;
	u8		epnum;
	काष्ठा musb_ep	*musb_ep;
	व्योम __iomem	*epio;

	musb_ep = to_musb_ep(ep);
	musb = musb_ep->musb;
	epnum = musb_ep->current_epnum;
	epio = musb->endpoपूर्णांकs[epnum].regs;

	spin_lock_irqsave(&musb->lock, flags);
	musb_ep_select(musb->mregs, epnum);

	/* zero the endpoपूर्णांक sizes */
	अगर (musb_ep->is_in) अणु
		musb->पूर्णांकrtxe &= ~(1 << epnum);
		musb_ग_लिखोw(musb->mregs, MUSB_INTRTXE, musb->पूर्णांकrtxe);
		musb_ग_लिखोw(epio, MUSB_TXMAXP, 0);
	पूर्ण अन्यथा अणु
		musb->पूर्णांकrrxe &= ~(1 << epnum);
		musb_ग_लिखोw(musb->mregs, MUSB_INTRRXE, musb->पूर्णांकrrxe);
		musb_ग_लिखोw(epio, MUSB_RXMAXP, 0);
	पूर्ण

	/* पात all pending DMA and requests */
	nuke(musb_ep, -ESHUTDOWN);

	musb_ep->desc = शून्य;
	musb_ep->end_poपूर्णांक.desc = शून्य;

	schedule_delayed_work(&musb->irq_work, 0);

	spin_unlock_irqrestore(&(musb->lock), flags);

	musb_dbg(musb, "%s", musb_ep->end_poपूर्णांक.name);

	वापस 0;
पूर्ण

/*
 * Allocate a request क्रम an endpoपूर्णांक.
 * Reused by ep0 code.
 */
काष्ठा usb_request *musb_alloc_request(काष्ठा usb_ep *ep, gfp_t gfp_flags)
अणु
	काष्ठा musb_ep		*musb_ep = to_musb_ep(ep);
	काष्ठा musb_request	*request = शून्य;

	request = kzalloc(माप *request, gfp_flags);
	अगर (!request)
		वापस शून्य;

	request->request.dma = DMA_ADDR_INVALID;
	request->epnum = musb_ep->current_epnum;
	request->ep = musb_ep;

	trace_musb_req_alloc(request);
	वापस &request->request;
पूर्ण

/*
 * Free a request
 * Reused by ep0 code.
 */
व्योम musb_मुक्त_request(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा musb_request *request = to_musb_request(req);

	trace_musb_req_मुक्त(request);
	kमुक्त(request);
पूर्ण

अटल LIST_HEAD(buffers);

काष्ठा मुक्त_record अणु
	काष्ठा list_head	list;
	काष्ठा device		*dev;
	अचिन्हित		bytes;
	dma_addr_t		dma;
पूर्ण;

/*
 * Context: controller locked, IRQs blocked.
 */
व्योम musb_ep_restart(काष्ठा musb *musb, काष्ठा musb_request *req)
अणु
	trace_musb_req_start(req);
	musb_ep_select(musb->mregs, req->epnum);
	अगर (req->tx)
		txstate(musb, req);
	अन्यथा
		rxstate(musb, req);
पूर्ण

अटल पूर्णांक musb_ep_restart_resume_work(काष्ठा musb *musb, व्योम *data)
अणु
	काष्ठा musb_request *req = data;

	musb_ep_restart(musb, req);

	वापस 0;
पूर्ण

अटल पूर्णांक musb_gadget_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *req,
			gfp_t gfp_flags)
अणु
	काष्ठा musb_ep		*musb_ep;
	काष्ठा musb_request	*request;
	काष्ठा musb		*musb;
	पूर्णांक			status;
	अचिन्हित दीर्घ		lockflags;

	अगर (!ep || !req)
		वापस -EINVAL;
	अगर (!req->buf)
		वापस -ENODATA;

	musb_ep = to_musb_ep(ep);
	musb = musb_ep->musb;

	request = to_musb_request(req);
	request->musb = musb;

	अगर (request->ep != musb_ep)
		वापस -EINVAL;

	status = pm_runसमय_get(musb->controller);
	अगर ((status != -EINPROGRESS) && status < 0) अणु
		dev_err(musb->controller,
			"pm runtime get failed in %s\n",
			__func__);
		pm_runसमय_put_noidle(musb->controller);

		वापस status;
	पूर्ण
	status = 0;

	trace_musb_req_enq(request);

	/* request is mine now... */
	request->request.actual = 0;
	request->request.status = -EINPROGRESS;
	request->epnum = musb_ep->current_epnum;
	request->tx = musb_ep->is_in;

	map_dma_buffer(request, musb, musb_ep);

	spin_lock_irqsave(&musb->lock, lockflags);

	/* करोn't queue अगर the ep is करोwn */
	अगर (!musb_ep->desc) अणु
		musb_dbg(musb, "req %p queued to %s while ep %s",
				req, ep->name, "disabled");
		status = -ESHUTDOWN;
		unmap_dma_buffer(request, musb);
		जाओ unlock;
	पूर्ण

	/* add request to the list */
	list_add_tail(&request->list, &musb_ep->req_list);

	/* it this is the head of the queue, start i/o ... */
	अगर (!musb_ep->busy && &request->list == musb_ep->req_list.next) अणु
		status = musb_queue_resume_work(musb,
						musb_ep_restart_resume_work,
						request);
		अगर (status < 0)
			dev_err(musb->controller, "%s resume work: %i\n",
				__func__, status);
	पूर्ण

unlock:
	spin_unlock_irqrestore(&musb->lock, lockflags);
	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);

	वापस status;
पूर्ण

अटल पूर्णांक musb_gadget_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *request)
अणु
	काष्ठा musb_ep		*musb_ep = to_musb_ep(ep);
	काष्ठा musb_request	*req = to_musb_request(request);
	काष्ठा musb_request	*r;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			status = 0;
	काष्ठा musb		*musb = musb_ep->musb;

	अगर (!ep || !request || req->ep != musb_ep)
		वापस -EINVAL;

	trace_musb_req_deq(req);

	spin_lock_irqsave(&musb->lock, flags);

	list_क्रम_each_entry(r, &musb_ep->req_list, list) अणु
		अगर (r == req)
			अवरोध;
	पूर्ण
	अगर (r != req) अणु
		dev_err(musb->controller, "request %p not queued to %s\n",
				request, ep->name);
		status = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* अगर the hardware करोesn't have the request, easy ... */
	अगर (musb_ep->req_list.next != &req->list || musb_ep->busy)
		musb_g_giveback(musb_ep, request, -ECONNRESET);

	/* ... अन्यथा पात the dma transfer ... */
	अन्यथा अगर (is_dma_capable() && musb_ep->dma) अणु
		काष्ठा dma_controller	*c = musb->dma_controller;

		musb_ep_select(musb->mregs, musb_ep->current_epnum);
		अगर (c->channel_पात)
			status = c->channel_पात(musb_ep->dma);
		अन्यथा
			status = -EBUSY;
		अगर (status == 0)
			musb_g_giveback(musb_ep, request, -ECONNRESET);
	पूर्ण अन्यथा अणु
		/* NOTE: by sticking to easily tested hardware/driver states,
		 * we leave counting of in-flight packets imprecise.
		 */
		musb_g_giveback(musb_ep, request, -ECONNRESET);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस status;
पूर्ण

/*
 * Set or clear the halt bit of an endpoपूर्णांक. A halted endpoपूर्णांक won't tx/rx any
 * data but will queue requests.
 *
 * exported to ep0 code
 */
अटल पूर्णांक musb_gadget_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा musb_ep		*musb_ep = to_musb_ep(ep);
	u8			epnum = musb_ep->current_epnum;
	काष्ठा musb		*musb = musb_ep->musb;
	व्योम __iomem		*epio = musb->endpoपूर्णांकs[epnum].regs;
	व्योम __iomem		*mbase;
	अचिन्हित दीर्घ		flags;
	u16			csr;
	काष्ठा musb_request	*request;
	पूर्णांक			status = 0;

	अगर (!ep)
		वापस -EINVAL;
	mbase = musb->mregs;

	spin_lock_irqsave(&musb->lock, flags);

	अगर ((USB_ENDPOINT_XFER_ISOC == musb_ep->type)) अणु
		status = -EINVAL;
		जाओ करोne;
	पूर्ण

	musb_ep_select(mbase, epnum);

	request = next_request(musb_ep);
	अगर (value) अणु
		अगर (request) अणु
			musb_dbg(musb, "request in progress, cannot halt %s",
			    ep->name);
			status = -EAGAIN;
			जाओ करोne;
		पूर्ण
		/* Cannot portably stall with non-empty FIFO */
		अगर (musb_ep->is_in) अणु
			csr = musb_पढ़ोw(epio, MUSB_TXCSR);
			अगर (csr & MUSB_TXCSR_FIFONOTEMPTY) अणु
				musb_dbg(musb, "FIFO busy, cannot halt %s",
						ep->name);
				status = -EAGAIN;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		musb_ep->wedged = 0;

	/* set/clear the stall and toggle bits */
	musb_dbg(musb, "%s: %s stall", ep->name, value ? "set" : "clear");
	अगर (musb_ep->is_in) अणु
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		csr |= MUSB_TXCSR_P_WZC_BITS
			| MUSB_TXCSR_CLRDATATOG;
		अगर (value)
			csr |= MUSB_TXCSR_P_SENDSTALL;
		अन्यथा
			csr &= ~(MUSB_TXCSR_P_SENDSTALL
				| MUSB_TXCSR_P_SENTSTALL);
		csr &= ~MUSB_TXCSR_TXPKTRDY;
		musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
	पूर्ण अन्यथा अणु
		csr = musb_पढ़ोw(epio, MUSB_RXCSR);
		csr |= MUSB_RXCSR_P_WZC_BITS
			| MUSB_RXCSR_FLUSHFIFO
			| MUSB_RXCSR_CLRDATATOG;
		अगर (value)
			csr |= MUSB_RXCSR_P_SENDSTALL;
		अन्यथा
			csr &= ~(MUSB_RXCSR_P_SENDSTALL
				| MUSB_RXCSR_P_SENTSTALL);
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
	पूर्ण

	/* maybe start the first request in the queue */
	अगर (!musb_ep->busy && !value && request) अणु
		musb_dbg(musb, "restarting the request");
		musb_ep_restart(musb, request);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस status;
पूर्ण

/*
 * Sets the halt feature with the clear requests ignored
 */
अटल पूर्णांक musb_gadget_set_wedge(काष्ठा usb_ep *ep)
अणु
	काष्ठा musb_ep		*musb_ep = to_musb_ep(ep);

	अगर (!ep)
		वापस -EINVAL;

	musb_ep->wedged = 1;

	वापस usb_ep_set_halt(ep);
पूर्ण

अटल पूर्णांक musb_gadget_fअगरo_status(काष्ठा usb_ep *ep)
अणु
	काष्ठा musb_ep		*musb_ep = to_musb_ep(ep);
	व्योम __iomem		*epio = musb_ep->hw_ep->regs;
	पूर्णांक			retval = -EINVAL;

	अगर (musb_ep->desc && !musb_ep->is_in) अणु
		काष्ठा musb		*musb = musb_ep->musb;
		पूर्णांक			epnum = musb_ep->current_epnum;
		व्योम __iomem		*mbase = musb->mregs;
		अचिन्हित दीर्घ		flags;

		spin_lock_irqsave(&musb->lock, flags);

		musb_ep_select(mbase, epnum);
		/* FIXME वापस zero unless RXPKTRDY is set */
		retval = musb_पढ़ोw(epio, MUSB_RXCOUNT);

		spin_unlock_irqrestore(&musb->lock, flags);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम musb_gadget_fअगरo_flush(काष्ठा usb_ep *ep)
अणु
	काष्ठा musb_ep	*musb_ep = to_musb_ep(ep);
	काष्ठा musb	*musb = musb_ep->musb;
	u8		epnum = musb_ep->current_epnum;
	व्योम __iomem	*epio = musb->endpoपूर्णांकs[epnum].regs;
	व्योम __iomem	*mbase;
	अचिन्हित दीर्घ	flags;
	u16		csr;

	mbase = musb->mregs;

	spin_lock_irqsave(&musb->lock, flags);
	musb_ep_select(mbase, (u8) epnum);

	/* disable पूर्णांकerrupts */
	musb_ग_लिखोw(mbase, MUSB_INTRTXE, musb->पूर्णांकrtxe & ~(1 << epnum));

	अगर (musb_ep->is_in) अणु
		csr = musb_पढ़ोw(epio, MUSB_TXCSR);
		अगर (csr & MUSB_TXCSR_FIFONOTEMPTY) अणु
			csr |= MUSB_TXCSR_FLUSHFIFO | MUSB_TXCSR_P_WZC_BITS;
			/*
			 * Setting both TXPKTRDY and FLUSHFIFO makes controller
			 * to पूर्णांकerrupt current FIFO loading, but not flushing
			 * the alपढ़ोy loaded ones.
			 */
			csr &= ~MUSB_TXCSR_TXPKTRDY;
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
			/* REVISIT may be inappropriate w/o FIFONOTEMPTY ... */
			musb_ग_लिखोw(epio, MUSB_TXCSR, csr);
		पूर्ण
	पूर्ण अन्यथा अणु
		csr = musb_पढ़ोw(epio, MUSB_RXCSR);
		csr |= MUSB_RXCSR_FLUSHFIFO | MUSB_RXCSR_P_WZC_BITS;
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
		musb_ग_लिखोw(epio, MUSB_RXCSR, csr);
	पूर्ण

	/* re-enable पूर्णांकerrupt */
	musb_ग_लिखोw(mbase, MUSB_INTRTXE, musb->पूर्णांकrtxe);
	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops musb_ep_ops = अणु
	.enable		= musb_gadget_enable,
	.disable	= musb_gadget_disable,
	.alloc_request	= musb_alloc_request,
	.मुक्त_request	= musb_मुक्त_request,
	.queue		= musb_gadget_queue,
	.dequeue	= musb_gadget_dequeue,
	.set_halt	= musb_gadget_set_halt,
	.set_wedge	= musb_gadget_set_wedge,
	.fअगरo_status	= musb_gadget_fअगरo_status,
	.fअगरo_flush	= musb_gadget_fअगरo_flush
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक musb_gadget_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा musb	*musb = gadget_to_musb(gadget);

	वापस (पूर्णांक)musb_पढ़ोw(musb->mregs, MUSB_FRAME);
पूर्ण

अटल पूर्णांक musb_gadget_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा musb	*musb = gadget_to_musb(gadget);
	व्योम __iomem	*mregs = musb->mregs;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		status = -EINVAL;
	u8		घातer, devctl;
	पूर्णांक		retries;

	spin_lock_irqsave(&musb->lock, flags);

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_B_PERIPHERAL:
		/* NOTE:  OTG state machine करोesn't include B_SUSPENDED;
		 * that's part of the standard usb 1.1 state machine, and
		 * करोesn't affect OTG transitions.
		 */
		अगर (musb->may_wakeup && musb->is_suspended)
			अवरोध;
		जाओ करोne;
	हाल OTG_STATE_B_IDLE:
		/* Start SRP ... OTG not required. */
		devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
		musb_dbg(musb, "Sending SRP: devctl: %02x", devctl);
		devctl |= MUSB_DEVCTL_SESSION;
		musb_ग_लिखोb(mregs, MUSB_DEVCTL, devctl);
		devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
		retries = 100;
		जबतक (!(devctl & MUSB_DEVCTL_SESSION)) अणु
			devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
			अगर (retries-- < 1)
				अवरोध;
		पूर्ण
		retries = 10000;
		जबतक (devctl & MUSB_DEVCTL_SESSION) अणु
			devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
			अगर (retries-- < 1)
				अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&musb->lock, flags);
		otg_start_srp(musb->xceiv->otg);
		spin_lock_irqsave(&musb->lock, flags);

		/* Block idling क्रम at least 1s */
		musb_platक्रमm_try_idle(musb,
			jअगरfies + msecs_to_jअगरfies(1 * HZ));

		status = 0;
		जाओ करोne;
	शेष:
		musb_dbg(musb, "Unhandled wake: %s",
			usb_otg_state_string(musb->xceiv->otg->state));
		जाओ करोne;
	पूर्ण

	status = 0;

	घातer = musb_पढ़ोb(mregs, MUSB_POWER);
	घातer |= MUSB_POWER_RESUME;
	musb_ग_लिखोb(mregs, MUSB_POWER, घातer);
	musb_dbg(musb, "issue wakeup");

	/* FIXME करो this next chunk in a समयr callback, no udelay */
	mdelay(2);

	घातer = musb_पढ़ोb(mregs, MUSB_POWER);
	घातer &= ~MUSB_POWER_RESUME;
	musb_ग_लिखोb(mregs, MUSB_POWER, घातer);
करोne:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस status;
पूर्ण

अटल पूर्णांक
musb_gadget_set_self_घातered(काष्ठा usb_gadget *gadget, पूर्णांक is_selfघातered)
अणु
	gadget->is_selfघातered = !!is_selfघातered;
	वापस 0;
पूर्ण

अटल व्योम musb_pullup(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	u8 घातer;

	घातer = musb_पढ़ोb(musb->mregs, MUSB_POWER);
	अगर (is_on)
		घातer |= MUSB_POWER_SOFTCONN;
	अन्यथा
		घातer &= ~MUSB_POWER_SOFTCONN;

	/* FIXME अगर on, HdrcStart; अगर off, HdrcStop */

	musb_dbg(musb, "gadget D+ pullup %s",
		is_on ? "on" : "off");
	musb_ग_लिखोb(musb->mregs, MUSB_POWER, घातer);
पूर्ण

#अगर 0
अटल पूर्णांक musb_gadget_vbus_session(काष्ठा usb_gadget *gadget, पूर्णांक is_active)
अणु
	musb_dbg(musb, "<= %s =>\n", __func__);

	/*
	 * FIXME अगरf driver's softconnect flag is set (as it is during probe,
	 * though that can clear it), just musb_pullup().
	 */

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक musb_gadget_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु
	काष्ठा musb	*musb = gadget_to_musb(gadget);

	अगर (!musb->xceiv->set_घातer)
		वापस -EOPNOTSUPP;
	वापस usb_phy_set_घातer(musb->xceiv, mA);
पूर्ण

अटल व्योम musb_gadget_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा musb *musb;
	अचिन्हित दीर्घ flags;

	musb = container_of(work, काष्ठा musb, gadget_work.work);
	pm_runसमय_get_sync(musb->controller);
	spin_lock_irqsave(&musb->lock, flags);
	musb_pullup(musb, musb->softconnect);
	spin_unlock_irqrestore(&musb->lock, flags);
	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);
पूर्ण

अटल पूर्णांक musb_gadget_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा musb	*musb = gadget_to_musb(gadget);
	अचिन्हित दीर्घ	flags;

	is_on = !!is_on;

	/* NOTE: this assumes we are sensing vbus; we'd rather
	 * not pullup unless the B-session is active.
	 */
	spin_lock_irqsave(&musb->lock, flags);
	अगर (is_on != musb->softconnect) अणु
		musb->softconnect = is_on;
		schedule_delayed_work(&musb->gadget_work, 0);
	पूर्ण
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक musb_gadget_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक musb_gadget_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops musb_gadget_operations = अणु
	.get_frame		= musb_gadget_get_frame,
	.wakeup			= musb_gadget_wakeup,
	.set_selfघातered	= musb_gadget_set_self_घातered,
	/* .vbus_session		= musb_gadget_vbus_session, */
	.vbus_draw		= musb_gadget_vbus_draw,
	.pullup			= musb_gadget_pullup,
	.udc_start		= musb_gadget_start,
	.udc_stop		= musb_gadget_stop,
पूर्ण;

/* ----------------------------------------------------------------------- */

/* Registration */

/* Only this registration code "knows" the rule (from USB standards)
 * about there being only one बाह्यal upstream port.  It assumes
 * all peripheral ports are बाह्यal...
 */

अटल व्योम
init_peripheral_ep(काष्ठा musb *musb, काष्ठा musb_ep *ep, u8 epnum, पूर्णांक is_in)
अणु
	काष्ठा musb_hw_ep	*hw_ep = musb->endpoपूर्णांकs + epnum;

	स_रखो(ep, 0, माप *ep);

	ep->current_epnum = epnum;
	ep->musb = musb;
	ep->hw_ep = hw_ep;
	ep->is_in = is_in;

	INIT_LIST_HEAD(&ep->req_list);

	प्र_लिखो(ep->name, "ep%d%s", epnum,
			(!epnum || hw_ep->is_shared_fअगरo) ? "" : (
				is_in ? "in" : "out"));
	ep->end_poपूर्णांक.name = ep->name;
	INIT_LIST_HEAD(&ep->end_poपूर्णांक.ep_list);
	अगर (!epnum) अणु
		usb_ep_set_maxpacket_limit(&ep->end_poपूर्णांक, 64);
		ep->end_poपूर्णांक.caps.type_control = true;
		ep->end_poपूर्णांक.ops = &musb_g_ep0_ops;
		musb->g.ep0 = &ep->end_poपूर्णांक;
	पूर्ण अन्यथा अणु
		अगर (is_in)
			usb_ep_set_maxpacket_limit(&ep->end_poपूर्णांक, hw_ep->max_packet_sz_tx);
		अन्यथा
			usb_ep_set_maxpacket_limit(&ep->end_poपूर्णांक, hw_ep->max_packet_sz_rx);
		ep->end_poपूर्णांक.caps.type_iso = true;
		ep->end_poपूर्णांक.caps.type_bulk = true;
		ep->end_poपूर्णांक.caps.type_पूर्णांक = true;
		ep->end_poपूर्णांक.ops = &musb_ep_ops;
		list_add_tail(&ep->end_poपूर्णांक.ep_list, &musb->g.ep_list);
	पूर्ण

	अगर (!epnum || hw_ep->is_shared_fअगरo) अणु
		ep->end_poपूर्णांक.caps.dir_in = true;
		ep->end_poपूर्णांक.caps.dir_out = true;
	पूर्ण अन्यथा अगर (is_in)
		ep->end_poपूर्णांक.caps.dir_in = true;
	अन्यथा
		ep->end_poपूर्णांक.caps.dir_out = true;
पूर्ण

/*
 * Initialize the endpoपूर्णांकs exposed to peripheral drivers, with backlinks
 * to the rest of the driver state.
 */
अटल अंतरभूत व्योम musb_g_init_endpoपूर्णांकs(काष्ठा musb *musb)
अणु
	u8			epnum;
	काष्ठा musb_hw_ep	*hw_ep;
	अचिन्हित		count = 0;

	/* initialize endpoपूर्णांक list just once */
	INIT_LIST_HEAD(&(musb->g.ep_list));

	क्रम (epnum = 0, hw_ep = musb->endpoपूर्णांकs;
			epnum < musb->nr_endpoपूर्णांकs;
			epnum++, hw_ep++) अणु
		अगर (hw_ep->is_shared_fअगरo /* || !epnum */) अणु
			init_peripheral_ep(musb, &hw_ep->ep_in, epnum, 0);
			count++;
		पूर्ण अन्यथा अणु
			अगर (hw_ep->max_packet_sz_tx) अणु
				init_peripheral_ep(musb, &hw_ep->ep_in,
							epnum, 1);
				count++;
			पूर्ण
			अगर (hw_ep->max_packet_sz_rx) अणु
				init_peripheral_ep(musb, &hw_ep->ep_out,
							epnum, 0);
				count++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* called once during driver setup to initialize and link पूर्णांकo
 * the driver model; memory is zeroed.
 */
पूर्णांक musb_gadget_setup(काष्ठा musb *musb)
अणु
	पूर्णांक status;

	/* REVISIT minor race:  अगर (erroneously) setting up two
	 * musb peripherals at the same समय, only the bus lock
	 * is probably held.
	 */

	musb->g.ops = &musb_gadget_operations;
	musb->g.max_speed = USB_SPEED_HIGH;
	musb->g.speed = USB_SPEED_UNKNOWN;

	MUSB_DEV_MODE(musb);
	musb->xceiv->otg->state = OTG_STATE_B_IDLE;

	/* this "gadget" असलtracts/भवizes the controller */
	musb->g.name = musb_driver_name;
	/* करोn't support otg protocols */
	musb->g.is_otg = 0;
	INIT_DELAYED_WORK(&musb->gadget_work, musb_gadget_work);
	musb_g_init_endpoपूर्णांकs(musb);

	musb->is_active = 0;
	musb_platक्रमm_try_idle(musb, 0);

	status = usb_add_gadget_udc(musb->controller, &musb->g);
	अगर (status)
		जाओ err;

	वापस 0;
err:
	musb->g.dev.parent = शून्य;
	device_unरेजिस्टर(&musb->g.dev);
	वापस status;
पूर्ण

व्योम musb_gadget_cleanup(काष्ठा musb *musb)
अणु
	अगर (musb->port_mode == MUSB_HOST)
		वापस;

	cancel_delayed_work_sync(&musb->gadget_work);
	usb_del_gadget_udc(&musb->g);
पूर्ण

/*
 * Register the gadget driver. Used by gadget drivers when
 * रेजिस्टरing themselves with the controller.
 *
 * -EINVAL something went wrong (not driver)
 * -EBUSY another gadget is alपढ़ोy using the controller
 * -ENOMEM no memory to perक्रमm the operation
 *
 * @param driver the gadget driver
 * @वापस <0 अगर error, 0 अगर everything is fine
 */
अटल पूर्णांक musb_gadget_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा musb		*musb = gadget_to_musb(g);
	काष्ठा usb_otg		*otg = musb->xceiv->otg;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			retval = 0;

	अगर (driver->max_speed < USB_SPEED_HIGH) अणु
		retval = -EINVAL;
		जाओ err;
	पूर्ण

	pm_runसमय_get_sync(musb->controller);

	musb->softconnect = 0;
	musb->gadget_driver = driver;

	spin_lock_irqsave(&musb->lock, flags);
	musb->is_active = 1;

	otg_set_peripheral(otg, &musb->g);
	musb->xceiv->otg->state = OTG_STATE_B_IDLE;
	spin_unlock_irqrestore(&musb->lock, flags);

	musb_start(musb);

	/* REVISIT:  funcall to other code, which also
	 * handles घातer budgeting ... this way also
	 * ensures HdrcStart is indirectly called.
	 */
	अगर (musb->xceiv->last_event == USB_EVENT_ID)
		musb_platक्रमm_set_vbus(musb, 1);

	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);

	वापस 0;

err:
	वापस retval;
पूर्ण

/*
 * Unरेजिस्टर the gadget driver. Used by gadget drivers when
 * unरेजिस्टरing themselves from the controller.
 *
 * @param driver the gadget driver to unरेजिस्टर
 */
अटल पूर्णांक musb_gadget_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा musb	*musb = gadget_to_musb(g);
	अचिन्हित दीर्घ	flags;

	pm_runसमय_get_sync(musb->controller);

	/*
	 * REVISIT always use otg_set_peripheral() here too;
	 * this needs to shut करोwn the OTG engine.
	 */

	spin_lock_irqsave(&musb->lock, flags);

	musb_hnp_stop(musb);

	(व्योम) musb_gadget_vbus_draw(&musb->g, 0);

	musb->xceiv->otg->state = OTG_STATE_UNDEFINED;
	musb_stop(musb);
	otg_set_peripheral(musb->xceiv->otg, शून्य);

	musb->is_active = 0;
	musb->gadget_driver = शून्य;
	musb_platक्रमm_try_idle(musb, 0);
	spin_unlock_irqrestore(&musb->lock, flags);

	/*
	 * FIXME we need to be able to रेजिस्टर another
	 * gadget driver here and have everything work;
	 * that currently misbehaves.
	 */

	/* Force check of devctl रेजिस्टर क्रम PM runसमय */
	schedule_delayed_work(&musb->irq_work, 0);

	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

/* lअगरecycle operations called through plat_uds.c */

व्योम musb_g_resume(काष्ठा musb *musb)
अणु
	musb->is_suspended = 0;
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_B_IDLE:
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
	हाल OTG_STATE_B_PERIPHERAL:
		musb->is_active = 1;
		अगर (musb->gadget_driver && musb->gadget_driver->resume) अणु
			spin_unlock(&musb->lock);
			musb->gadget_driver->resume(&musb->g);
			spin_lock(&musb->lock);
		पूर्ण
		अवरोध;
	शेष:
		WARNING("unhandled RESUME transition (%s)\n",
				usb_otg_state_string(musb->xceiv->otg->state));
	पूर्ण
पूर्ण

/* called when SOF packets stop क्रम 3+ msec */
व्योम musb_g_suspend(काष्ठा musb *musb)
अणु
	u8	devctl;

	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
	musb_dbg(musb, "musb_g_suspend: devctl %02x", devctl);

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_B_IDLE:
		अगर ((devctl & MUSB_DEVCTL_VBUS) == MUSB_DEVCTL_VBUS)
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		musb->is_suspended = 1;
		अगर (musb->gadget_driver && musb->gadget_driver->suspend) अणु
			spin_unlock(&musb->lock);
			musb->gadget_driver->suspend(&musb->g);
			spin_lock(&musb->lock);
		पूर्ण
		अवरोध;
	शेष:
		/* REVISIT अगर B_HOST, clear DEVCTL.HOSTREQ;
		 * A_PERIPHERAL may need care too
		 */
		WARNING("unhandled SUSPEND transition (%s)",
				usb_otg_state_string(musb->xceiv->otg->state));
	पूर्ण
पूर्ण

/* Called during SRP */
व्योम musb_g_wakeup(काष्ठा musb *musb)
अणु
	musb_gadget_wakeup(&musb->g);
पूर्ण

/* called when VBUS drops below session threshold, and in other हालs */
व्योम musb_g_disconnect(काष्ठा musb *musb)
अणु
	व्योम __iomem	*mregs = musb->mregs;
	u8	devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);

	musb_dbg(musb, "musb_g_disconnect: devctl %02x", devctl);

	/* clear HR */
	musb_ग_लिखोb(mregs, MUSB_DEVCTL, devctl & MUSB_DEVCTL_SESSION);

	/* करोn't draw vbus until new b-शेष session */
	(व्योम) musb_gadget_vbus_draw(&musb->g, 0);

	musb->g.speed = USB_SPEED_UNKNOWN;
	अगर (musb->gadget_driver && musb->gadget_driver->disconnect) अणु
		spin_unlock(&musb->lock);
		musb->gadget_driver->disconnect(&musb->g);
		spin_lock(&musb->lock);
	पूर्ण

	चयन (musb->xceiv->otg->state) अणु
	शेष:
		musb_dbg(musb, "Unhandled disconnect %s, setting a_idle",
			usb_otg_state_string(musb->xceiv->otg->state));
		musb->xceiv->otg->state = OTG_STATE_A_IDLE;
		MUSB_HST_MODE(musb);
		अवरोध;
	हाल OTG_STATE_A_PERIPHERAL:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
		MUSB_HST_MODE(musb);
		अवरोध;
	हाल OTG_STATE_B_WAIT_ACON:
	हाल OTG_STATE_B_HOST:
	हाल OTG_STATE_B_PERIPHERAL:
	हाल OTG_STATE_B_IDLE:
		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		अवरोध;
	हाल OTG_STATE_B_SRP_INIT:
		अवरोध;
	पूर्ण

	musb->is_active = 0;
पूर्ण

व्योम musb_g_reset(काष्ठा musb *musb)
__releases(musb->lock)
__acquires(musb->lock)
अणु
	व्योम __iomem	*mbase = musb->mregs;
	u8		devctl = musb_पढ़ोb(mbase, MUSB_DEVCTL);
	u8		घातer;

	musb_dbg(musb, "<== %s driver '%s'",
			(devctl & MUSB_DEVCTL_BDEVICE)
				? "B-Device" : "A-Device",
			musb->gadget_driver
				? musb->gadget_driver->driver.name
				: शून्य
			);

	/* report reset, अगर we didn't alपढ़ोy (flushing EP state) */
	अगर (musb->gadget_driver && musb->g.speed != USB_SPEED_UNKNOWN) अणु
		spin_unlock(&musb->lock);
		usb_gadget_udc_reset(&musb->g, musb->gadget_driver);
		spin_lock(&musb->lock);
	पूर्ण

	/* clear HR */
	अन्यथा अगर (devctl & MUSB_DEVCTL_HR)
		musb_ग_लिखोb(mbase, MUSB_DEVCTL, MUSB_DEVCTL_SESSION);


	/* what speed did we negotiate? */
	घातer = musb_पढ़ोb(mbase, MUSB_POWER);
	musb->g.speed = (घातer & MUSB_POWER_HSMODE)
			? USB_SPEED_HIGH : USB_SPEED_FULL;

	/* start in USB_STATE_DEFAULT */
	musb->is_active = 1;
	musb->is_suspended = 0;
	MUSB_DEV_MODE(musb);
	musb->address = 0;
	musb->ep0_state = MUSB_EP0_STAGE_SETUP;

	musb->may_wakeup = 0;
	musb->g.b_hnp_enable = 0;
	musb->g.a_alt_hnp_support = 0;
	musb->g.a_hnp_support = 0;
	musb->g.quirk_zlp_not_supp = 1;

	/* Normal reset, as B-Device;
	 * or अन्यथा after HNP, as A-Device
	 */
	अगर (!musb->g.is_otg) अणु
		/* USB device controllers that are not OTG compatible
		 * may not have DEVCTL रेजिस्टर in silicon.
		 * In that हाल, करो not rely on devctl क्रम setting
		 * peripheral mode.
		 */
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		musb->g.is_a_peripheral = 0;
	पूर्ण अन्यथा अगर (devctl & MUSB_DEVCTL_BDEVICE) अणु
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		musb->g.is_a_peripheral = 0;
	पूर्ण अन्यथा अणु
		musb->xceiv->otg->state = OTG_STATE_A_PERIPHERAL;
		musb->g.is_a_peripheral = 1;
	पूर्ण

	/* start with शेष limits on VBUS घातer draw */
	(व्योम) musb_gadget_vbus_draw(&musb->g, 8);
पूर्ण
