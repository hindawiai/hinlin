<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG peripheral driver ep0 handling
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 * Copyright (C) 2008-2009 MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "musb_core.h"

/* ep0 is always musb->endpoपूर्णांकs[0].ep_in */
#घोषणा	next_ep0_request(musb)	next_in_request(&(musb)->endpoपूर्णांकs[0])

/*
 * locking note:  we use only the controller lock, क्रम simpler correctness.
 * It's always held with IRQs blocked.
 *
 * It protects the ep0 request queue as well as ep0_state, not just the
 * controller and indexed रेजिस्टरs.  And that lock stays held unless it
 * needs to be dropped to allow reentering this driver ... like upcalls to
 * the gadget driver, or adjusting endpoपूर्णांक halt status.
 */

अटल अक्षर *decode_ep0stage(u8 stage)
अणु
	चयन (stage) अणु
	हाल MUSB_EP0_STAGE_IDLE:	वापस "idle";
	हाल MUSB_EP0_STAGE_SETUP:	वापस "setup";
	हाल MUSB_EP0_STAGE_TX:		वापस "in";
	हाल MUSB_EP0_STAGE_RX:		वापस "out";
	हाल MUSB_EP0_STAGE_ACKWAIT:	वापस "wait";
	हाल MUSB_EP0_STAGE_STATUSIN:	वापस "in/status";
	हाल MUSB_EP0_STAGE_STATUSOUT:	वापस "out/status";
	शेष:			वापस "?";
	पूर्ण
पूर्ण

/* handle a standard GET_STATUS request
 * Context:  caller holds controller lock
 */
अटल पूर्णांक service_tx_status_request(
	काष्ठा musb *musb,
	स्थिर काष्ठा usb_ctrlrequest *ctrlrequest)
अणु
	व्योम __iomem	*mbase = musb->mregs;
	पूर्णांक handled = 1;
	u8 result[2], epnum = 0;
	स्थिर u8 recip = ctrlrequest->bRequestType & USB_RECIP_MASK;

	result[1] = 0;

	चयन (recip) अणु
	हाल USB_RECIP_DEVICE:
		result[0] = musb->g.is_selfघातered << USB_DEVICE_SELF_POWERED;
		result[0] |= musb->may_wakeup << USB_DEVICE_REMOTE_WAKEUP;
		अगर (musb->g.is_otg) अणु
			result[0] |= musb->g.b_hnp_enable
				<< USB_DEVICE_B_HNP_ENABLE;
			result[0] |= musb->g.a_alt_hnp_support
				<< USB_DEVICE_A_ALT_HNP_SUPPORT;
			result[0] |= musb->g.a_hnp_support
				<< USB_DEVICE_A_HNP_SUPPORT;
		पूर्ण
		अवरोध;

	हाल USB_RECIP_INTERFACE:
		result[0] = 0;
		अवरोध;

	हाल USB_RECIP_ENDPOINT: अणु
		पूर्णांक		is_in;
		काष्ठा musb_ep	*ep;
		u16		पंचांगp;
		व्योम __iomem	*regs;

		epnum = (u8) ctrlrequest->wIndex;
		अगर (!epnum) अणु
			result[0] = 0;
			अवरोध;
		पूर्ण

		is_in = epnum & USB_सूची_IN;
		epnum &= 0x0f;
		अगर (epnum >= MUSB_C_NUM_EPS) अणु
			handled = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (is_in)
			ep = &musb->endpoपूर्णांकs[epnum].ep_in;
		अन्यथा
			ep = &musb->endpoपूर्णांकs[epnum].ep_out;
		regs = musb->endpoपूर्णांकs[epnum].regs;

		अगर (!ep->desc) अणु
			handled = -EINVAL;
			अवरोध;
		पूर्ण

		musb_ep_select(mbase, epnum);
		अगर (is_in)
			पंचांगp = musb_पढ़ोw(regs, MUSB_TXCSR)
						& MUSB_TXCSR_P_SENDSTALL;
		अन्यथा
			पंचांगp = musb_पढ़ोw(regs, MUSB_RXCSR)
						& MUSB_RXCSR_P_SENDSTALL;
		musb_ep_select(mbase, 0);

		result[0] = पंचांगp ? 1 : 0;
		पूर्ण अवरोध;

	शेष:
		/* class, venकरोr, etc ... delegate */
		handled = 0;
		अवरोध;
	पूर्ण

	/* fill up the fअगरo; caller updates csr0 */
	अगर (handled > 0) अणु
		u16	len = le16_to_cpu(ctrlrequest->wLength);

		अगर (len > 2)
			len = 2;
		musb_ग_लिखो_fअगरo(&musb->endpoपूर्णांकs[0], len, result);
	पूर्ण

	वापस handled;
पूर्ण

/*
 * handle a control-IN request, the end0 buffer contains the current request
 * that is supposed to be a standard control request. Assumes the fअगरo to
 * be at least 2 bytes दीर्घ.
 *
 * @वापस 0 अगर the request was NOT HANDLED,
 * < 0 when error
 * > 0 when the request is processed
 *
 * Context:  caller holds controller lock
 */
अटल पूर्णांक
service_in_request(काष्ठा musb *musb, स्थिर काष्ठा usb_ctrlrequest *ctrlrequest)
अणु
	पूर्णांक handled = 0;	/* not handled */

	अगर ((ctrlrequest->bRequestType & USB_TYPE_MASK)
			== USB_TYPE_STANDARD) अणु
		चयन (ctrlrequest->bRequest) अणु
		हाल USB_REQ_GET_STATUS:
			handled = service_tx_status_request(musb,
					ctrlrequest);
			अवरोध;

		/* हाल USB_REQ_SYNC_FRAME: */

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस handled;
पूर्ण

/*
 * Context:  caller holds controller lock
 */
अटल व्योम musb_g_ep0_giveback(काष्ठा musb *musb, काष्ठा usb_request *req)
अणु
	musb_g_giveback(&musb->endpoपूर्णांकs[0].ep_in, req, 0);
पूर्ण

/*
 * Tries to start B-device HNP negotiation अगर enabled via sysfs
 */
अटल अंतरभूत व्योम musb_try_b_hnp_enable(काष्ठा musb *musb)
अणु
	व्योम __iomem	*mbase = musb->mregs;
	u8		devctl;

	musb_dbg(musb, "HNP: Setting HR");
	devctl = musb_पढ़ोb(mbase, MUSB_DEVCTL);
	musb_ग_लिखोb(mbase, MUSB_DEVCTL, devctl | MUSB_DEVCTL_HR);
पूर्ण

/*
 * Handle all control requests with no DATA stage, including standard
 * requests such as:
 * USB_REQ_SET_CONFIGURATION, USB_REQ_SET_INTERFACE, unrecognized
 *	always delegated to the gadget driver
 * USB_REQ_SET_ADDRESS, USB_REQ_CLEAR_FEATURE, USB_REQ_SET_FEATURE
 *	always handled here, except क्रम class/venकरोr/... features
 *
 * Context:  caller holds controller lock
 */
अटल पूर्णांक
service_zero_data_request(काष्ठा musb *musb,
		काष्ठा usb_ctrlrequest *ctrlrequest)
__releases(musb->lock)
__acquires(musb->lock)
अणु
	पूर्णांक handled = -EINVAL;
	व्योम __iomem *mbase = musb->mregs;
	स्थिर u8 recip = ctrlrequest->bRequestType & USB_RECIP_MASK;

	/* the gadget driver handles everything except what we MUST handle */
	अगर ((ctrlrequest->bRequestType & USB_TYPE_MASK)
			== USB_TYPE_STANDARD) अणु
		चयन (ctrlrequest->bRequest) अणु
		हाल USB_REQ_SET_ADDRESS:
			/* change it after the status stage */
			musb->set_address = true;
			musb->address = (u8) (ctrlrequest->wValue & 0x7f);
			handled = 1;
			अवरोध;

		हाल USB_REQ_CLEAR_FEATURE:
			चयन (recip) अणु
			हाल USB_RECIP_DEVICE:
				अगर (ctrlrequest->wValue
						!= USB_DEVICE_REMOTE_WAKEUP)
					अवरोध;
				musb->may_wakeup = 0;
				handled = 1;
				अवरोध;
			हाल USB_RECIP_INTERFACE:
				अवरोध;
			हाल USB_RECIP_ENDPOINT:अणु
				स्थिर u8		epnum =
					ctrlrequest->wIndex & 0x0f;
				काष्ठा musb_ep		*musb_ep;
				काष्ठा musb_hw_ep	*ep;
				काष्ठा musb_request	*request;
				व्योम __iomem		*regs;
				पूर्णांक			is_in;
				u16			csr;

				अगर (epnum == 0 || epnum >= MUSB_C_NUM_EPS ||
				    ctrlrequest->wValue != USB_ENDPOINT_HALT)
					अवरोध;

				ep = musb->endpoपूर्णांकs + epnum;
				regs = ep->regs;
				is_in = ctrlrequest->wIndex & USB_सूची_IN;
				अगर (is_in)
					musb_ep = &ep->ep_in;
				अन्यथा
					musb_ep = &ep->ep_out;
				अगर (!musb_ep->desc)
					अवरोध;

				handled = 1;
				/* Ignore request अगर endpoपूर्णांक is wedged */
				अगर (musb_ep->wedged)
					अवरोध;

				musb_ep_select(mbase, epnum);
				अगर (is_in) अणु
					csr  = musb_पढ़ोw(regs, MUSB_TXCSR);
					csr |= MUSB_TXCSR_CLRDATATOG |
					       MUSB_TXCSR_P_WZC_BITS;
					csr &= ~(MUSB_TXCSR_P_SENDSTALL |
						 MUSB_TXCSR_P_SENTSTALL |
						 MUSB_TXCSR_TXPKTRDY);
					musb_ग_लिखोw(regs, MUSB_TXCSR, csr);
				पूर्ण अन्यथा अणु
					csr  = musb_पढ़ोw(regs, MUSB_RXCSR);
					csr |= MUSB_RXCSR_CLRDATATOG |
					       MUSB_RXCSR_P_WZC_BITS;
					csr &= ~(MUSB_RXCSR_P_SENDSTALL |
						 MUSB_RXCSR_P_SENTSTALL);
					musb_ग_लिखोw(regs, MUSB_RXCSR, csr);
				पूर्ण

				/* Maybe start the first request in the queue */
				request = next_request(musb_ep);
				अगर (!musb_ep->busy && request) अणु
					musb_dbg(musb, "restarting the request");
					musb_ep_restart(musb, request);
				पूर्ण

				/* select ep0 again */
				musb_ep_select(mbase, 0);
				पूर्ण अवरोध;
			शेष:
				/* class, venकरोr, etc ... delegate */
				handled = 0;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल USB_REQ_SET_FEATURE:
			चयन (recip) अणु
			हाल USB_RECIP_DEVICE:
				handled = 1;
				चयन (ctrlrequest->wValue) अणु
				हाल USB_DEVICE_REMOTE_WAKEUP:
					musb->may_wakeup = 1;
					अवरोध;
				हाल USB_DEVICE_TEST_MODE:
					अगर (musb->g.speed != USB_SPEED_HIGH)
						जाओ stall;
					अगर (ctrlrequest->wIndex & 0xff)
						जाओ stall;

					चयन (ctrlrequest->wIndex >> 8) अणु
					हाल USB_TEST_J:
						pr_debug("USB_TEST_J\n");
						musb->test_mode_nr =
							MUSB_TEST_J;
						अवरोध;
					हाल USB_TEST_K:
						pr_debug("USB_TEST_K\n");
						musb->test_mode_nr =
							MUSB_TEST_K;
						अवरोध;
					हाल USB_TEST_SE0_NAK:
						pr_debug("USB_TEST_SE0_NAK\n");
						musb->test_mode_nr =
							MUSB_TEST_SE0_NAK;
						अवरोध;
					हाल USB_TEST_PACKET:
						pr_debug("USB_TEST_PACKET\n");
						musb->test_mode_nr =
							MUSB_TEST_PACKET;
						अवरोध;

					हाल 0xc0:
						/* TEST_FORCE_HS */
						pr_debug("TEST_FORCE_HS\n");
						musb->test_mode_nr =
							MUSB_TEST_FORCE_HS;
						अवरोध;
					हाल 0xc1:
						/* TEST_FORCE_FS */
						pr_debug("TEST_FORCE_FS\n");
						musb->test_mode_nr =
							MUSB_TEST_FORCE_FS;
						अवरोध;
					हाल 0xc2:
						/* TEST_FIFO_ACCESS */
						pr_debug("TEST_FIFO_ACCESS\n");
						musb->test_mode_nr =
							MUSB_TEST_FIFO_ACCESS;
						अवरोध;
					हाल 0xc3:
						/* TEST_FORCE_HOST */
						pr_debug("TEST_FORCE_HOST\n");
						musb->test_mode_nr =
							MUSB_TEST_FORCE_HOST;
						अवरोध;
					शेष:
						जाओ stall;
					पूर्ण

					/* enter test mode after irq */
					अगर (handled > 0)
						musb->test_mode = true;
					अवरोध;
				हाल USB_DEVICE_B_HNP_ENABLE:
					अगर (!musb->g.is_otg)
						जाओ stall;
					musb->g.b_hnp_enable = 1;
					musb_try_b_hnp_enable(musb);
					अवरोध;
				हाल USB_DEVICE_A_HNP_SUPPORT:
					अगर (!musb->g.is_otg)
						जाओ stall;
					musb->g.a_hnp_support = 1;
					अवरोध;
				हाल USB_DEVICE_A_ALT_HNP_SUPPORT:
					अगर (!musb->g.is_otg)
						जाओ stall;
					musb->g.a_alt_hnp_support = 1;
					अवरोध;
				हाल USB_DEVICE_DEBUG_MODE:
					handled = 0;
					अवरोध;
stall:
				शेष:
					handled = -EINVAL;
					अवरोध;
				पूर्ण
				अवरोध;

			हाल USB_RECIP_INTERFACE:
				अवरोध;

			हाल USB_RECIP_ENDPOINT:अणु
				स्थिर u8		epnum =
					ctrlrequest->wIndex & 0x0f;
				काष्ठा musb_ep		*musb_ep;
				काष्ठा musb_hw_ep	*ep;
				व्योम __iomem		*regs;
				पूर्णांक			is_in;
				u16			csr;

				अगर (epnum == 0 || epnum >= MUSB_C_NUM_EPS ||
				    ctrlrequest->wValue	!= USB_ENDPOINT_HALT)
					अवरोध;

				ep = musb->endpoपूर्णांकs + epnum;
				regs = ep->regs;
				is_in = ctrlrequest->wIndex & USB_सूची_IN;
				अगर (is_in)
					musb_ep = &ep->ep_in;
				अन्यथा
					musb_ep = &ep->ep_out;
				अगर (!musb_ep->desc)
					अवरोध;

				musb_ep_select(mbase, epnum);
				अगर (is_in) अणु
					csr = musb_पढ़ोw(regs, MUSB_TXCSR);
					अगर (csr & MUSB_TXCSR_FIFONOTEMPTY)
						csr |= MUSB_TXCSR_FLUSHFIFO;
					csr |= MUSB_TXCSR_P_SENDSTALL
						| MUSB_TXCSR_CLRDATATOG
						| MUSB_TXCSR_P_WZC_BITS;
					musb_ग_लिखोw(regs, MUSB_TXCSR, csr);
				पूर्ण अन्यथा अणु
					csr = musb_पढ़ोw(regs, MUSB_RXCSR);
					csr |= MUSB_RXCSR_P_SENDSTALL
						| MUSB_RXCSR_FLUSHFIFO
						| MUSB_RXCSR_CLRDATATOG
						| MUSB_RXCSR_P_WZC_BITS;
					musb_ग_लिखोw(regs, MUSB_RXCSR, csr);
				पूर्ण

				/* select ep0 again */
				musb_ep_select(mbase, 0);
				handled = 1;
				पूर्ण अवरोध;

			शेष:
				/* class, venकरोr, etc ... delegate */
				handled = 0;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			/* delegate SET_CONFIGURATION, etc */
			handled = 0;
		पूर्ण
	पूर्ण अन्यथा
		handled = 0;
	वापस handled;
पूर्ण

/* we have an ep0out data packet
 * Context:  caller holds controller lock
 */
अटल व्योम ep0_rxstate(काष्ठा musb *musb)
अणु
	व्योम __iomem		*regs = musb->control_ep->regs;
	काष्ठा musb_request	*request;
	काष्ठा usb_request	*req;
	u16			count, csr;

	request = next_ep0_request(musb);
	req = &request->request;

	/* पढ़ो packet and ack; or stall because of gadget driver bug:
	 * should have provided the rx buffer beक्रमe setup() वापसed.
	 */
	अगर (req) अणु
		व्योम		*buf = req->buf + req->actual;
		अचिन्हित	len = req->length - req->actual;

		/* पढ़ो the buffer */
		count = musb_पढ़ोb(regs, MUSB_COUNT0);
		अगर (count > len) अणु
			req->status = -EOVERFLOW;
			count = len;
		पूर्ण
		अगर (count > 0) अणु
			musb_पढ़ो_fअगरo(&musb->endpoपूर्णांकs[0], count, buf);
			req->actual += count;
		पूर्ण
		csr = MUSB_CSR0_P_SVDRXPKTRDY;
		अगर (count < 64 || req->actual == req->length) अणु
			musb->ep0_state = MUSB_EP0_STAGE_STATUSIN;
			csr |= MUSB_CSR0_P_DATAEND;
		पूर्ण अन्यथा
			req = शून्य;
	पूर्ण अन्यथा
		csr = MUSB_CSR0_P_SVDRXPKTRDY | MUSB_CSR0_P_SENDSTALL;


	/* Completion handler may choose to stall, e.g. because the
	 * message just received holds invalid data.
	 */
	अगर (req) अणु
		musb->ackpend = csr;
		musb_g_ep0_giveback(musb, req);
		अगर (!musb->ackpend)
			वापस;
		musb->ackpend = 0;
	पूर्ण
	musb_ep_select(musb->mregs, 0);
	musb_ग_लिखोw(regs, MUSB_CSR0, csr);
पूर्ण

/*
 * transmitting to the host (IN), this code might be called from IRQ
 * and from kernel thपढ़ो.
 *
 * Context:  caller holds controller lock
 */
अटल व्योम ep0_txstate(काष्ठा musb *musb)
अणु
	व्योम __iomem		*regs = musb->control_ep->regs;
	काष्ठा musb_request	*req = next_ep0_request(musb);
	काष्ठा usb_request	*request;
	u16			csr = MUSB_CSR0_TXPKTRDY;
	u8			*fअगरo_src;
	u8			fअगरo_count;

	अगर (!req) अणु
		/* WARN_ON(1); */
		musb_dbg(musb, "odd; csr0 %04x", musb_पढ़ोw(regs, MUSB_CSR0));
		वापस;
	पूर्ण

	request = &req->request;

	/* load the data */
	fअगरo_src = (u8 *) request->buf + request->actual;
	fअगरo_count = min((अचिन्हित) MUSB_EP0_FIFOSIZE,
		request->length - request->actual);
	musb_ग_लिखो_fअगरo(&musb->endpoपूर्णांकs[0], fअगरo_count, fअगरo_src);
	request->actual += fअगरo_count;

	/* update the flags */
	अगर (fअगरo_count < MUSB_MAX_END0_PACKET
			|| (request->actual == request->length
				&& !request->zero)) अणु
		musb->ep0_state = MUSB_EP0_STAGE_STATUSOUT;
		csr |= MUSB_CSR0_P_DATAEND;
	पूर्ण अन्यथा
		request = शून्य;

	/* report completions as soon as the fअगरo's loaded; there's no
	 * win in रुकोing till this last packet माला_लो acked.  (other than
	 * very precise fault reporting, needed by USB TMC; possible with
	 * this hardware, but not usable from portable gadget drivers.)
	 */
	अगर (request) अणु
		musb->ackpend = csr;
		musb_g_ep0_giveback(musb, request);
		अगर (!musb->ackpend)
			वापस;
		musb->ackpend = 0;
	पूर्ण

	/* send it out, triggering a "txpktrdy cleared" irq */
	musb_ep_select(musb->mregs, 0);
	musb_ग_लिखोw(regs, MUSB_CSR0, csr);
पूर्ण

/*
 * Read a SETUP packet (काष्ठा usb_ctrlrequest) from the hardware.
 * Fields are left in USB byte-order.
 *
 * Context:  caller holds controller lock.
 */
अटल व्योम
musb_पढ़ो_setup(काष्ठा musb *musb, काष्ठा usb_ctrlrequest *req)
अणु
	काष्ठा musb_request	*r;
	व्योम __iomem		*regs = musb->control_ep->regs;

	musb_पढ़ो_fअगरo(&musb->endpoपूर्णांकs[0], माप *req, (u8 *)req);

	/* NOTE:  earlier 2.6 versions changed setup packets to host
	 * order, but now USB packets always stay in USB byte order.
	 */
	musb_dbg(musb, "SETUP req%02x.%02x v%04x i%04x l%d",
		req->bRequestType,
		req->bRequest,
		le16_to_cpu(req->wValue),
		le16_to_cpu(req->wIndex),
		le16_to_cpu(req->wLength));

	/* clean up any leftover transfers */
	r = next_ep0_request(musb);
	अगर (r)
		musb_g_ep0_giveback(musb, &r->request);

	/* For zero-data requests we want to delay the STATUS stage to
	 * aव्योम SETUPEND errors.  If we पढ़ो data (OUT), delay accepting
	 * packets until there's a buffer to store them in.
	 *
	 * If we ग_लिखो data, the controller acts happier अगर we enable
	 * the TX FIFO right away, and give the controller a moment
	 * to चयन modes...
	 */
	musb->set_address = false;
	musb->ackpend = MUSB_CSR0_P_SVDRXPKTRDY;
	अगर (req->wLength == 0) अणु
		अगर (req->bRequestType & USB_सूची_IN)
			musb->ackpend |= MUSB_CSR0_TXPKTRDY;
		musb->ep0_state = MUSB_EP0_STAGE_ACKWAIT;
	पूर्ण अन्यथा अगर (req->bRequestType & USB_सूची_IN) अणु
		musb->ep0_state = MUSB_EP0_STAGE_TX;
		musb_ग_लिखोw(regs, MUSB_CSR0, MUSB_CSR0_P_SVDRXPKTRDY);
		जबतक ((musb_पढ़ोw(regs, MUSB_CSR0)
				& MUSB_CSR0_RXPKTRDY) != 0)
			cpu_relax();
		musb->ackpend = 0;
	पूर्ण अन्यथा
		musb->ep0_state = MUSB_EP0_STAGE_RX;
पूर्ण

अटल पूर्णांक
क्रमward_to_driver(काष्ठा musb *musb, स्थिर काष्ठा usb_ctrlrequest *ctrlrequest)
__releases(musb->lock)
__acquires(musb->lock)
अणु
	पूर्णांक retval;
	अगर (!musb->gadget_driver)
		वापस -EOPNOTSUPP;
	spin_unlock(&musb->lock);
	retval = musb->gadget_driver->setup(&musb->g, ctrlrequest);
	spin_lock(&musb->lock);
	वापस retval;
पूर्ण

/*
 * Handle peripheral ep0 पूर्णांकerrupt
 *
 * Context: irq handler; we won't re-enter the driver that way.
 */
irqवापस_t musb_g_ep0_irq(काष्ठा musb *musb)
अणु
	u16		csr;
	u16		len;
	व्योम __iomem	*mbase = musb->mregs;
	व्योम __iomem	*regs = musb->endpoपूर्णांकs[0].regs;
	irqवापस_t	retval = IRQ_NONE;

	musb_ep_select(mbase, 0);	/* select ep0 */
	csr = musb_पढ़ोw(regs, MUSB_CSR0);
	len = musb_पढ़ोb(regs, MUSB_COUNT0);

	musb_dbg(musb, "csr %04x, count %d, ep0stage %s",
			csr, len, decode_ep0stage(musb->ep0_state));

	अगर (csr & MUSB_CSR0_P_DATAEND) अणु
		/*
		 * If DATAEND is set we should not call the callback,
		 * hence the status stage is not complete.
		 */
		वापस IRQ_HANDLED;
	पूर्ण

	/* I sent a stall.. need to acknowledge it now.. */
	अगर (csr & MUSB_CSR0_P_SENTSTALL) अणु
		musb_ग_लिखोw(regs, MUSB_CSR0,
				csr & ~MUSB_CSR0_P_SENTSTALL);
		retval = IRQ_HANDLED;
		musb->ep0_state = MUSB_EP0_STAGE_IDLE;
		csr = musb_पढ़ोw(regs, MUSB_CSR0);
	पूर्ण

	/* request ended "early" */
	अगर (csr & MUSB_CSR0_P_SETUPEND) अणु
		musb_ग_लिखोw(regs, MUSB_CSR0, MUSB_CSR0_P_SVDSETUPEND);
		retval = IRQ_HANDLED;
		/* Transition पूर्णांकo the early status phase */
		चयन (musb->ep0_state) अणु
		हाल MUSB_EP0_STAGE_TX:
			musb->ep0_state = MUSB_EP0_STAGE_STATUSOUT;
			अवरोध;
		हाल MUSB_EP0_STAGE_RX:
			musb->ep0_state = MUSB_EP0_STAGE_STATUSIN;
			अवरोध;
		शेष:
			ERR("SetupEnd came in a wrong ep0stage %s\n",
			    decode_ep0stage(musb->ep0_state));
		पूर्ण
		csr = musb_पढ़ोw(regs, MUSB_CSR0);
		/* NOTE:  request may need completion */
	पूर्ण

	/* करोcs from Mentor only describe tx, rx, and idle/setup states.
	 * we need to handle nuances around status stages, and also the
	 * हाल where status and setup stages come back-to-back ...
	 */
	चयन (musb->ep0_state) अणु

	हाल MUSB_EP0_STAGE_TX:
		/* irq on clearing txpktrdy */
		अगर ((csr & MUSB_CSR0_TXPKTRDY) == 0) अणु
			ep0_txstate(musb);
			retval = IRQ_HANDLED;
		पूर्ण
		अवरोध;

	हाल MUSB_EP0_STAGE_RX:
		/* irq on set rxpktrdy */
		अगर (csr & MUSB_CSR0_RXPKTRDY) अणु
			ep0_rxstate(musb);
			retval = IRQ_HANDLED;
		पूर्ण
		अवरोध;

	हाल MUSB_EP0_STAGE_STATUSIN:
		/* end of sequence #2 (OUT/RX state) or #3 (no data) */

		/* update address (अगर needed) only @ the end of the
		 * status phase per usb spec, which also guarantees
		 * we get 10 msec to receive this irq... until this
		 * is करोne we won't see the next packet.
		 */
		अगर (musb->set_address) अणु
			musb->set_address = false;
			musb_ग_लिखोb(mbase, MUSB_FADDR, musb->address);
		पूर्ण

		/* enter test mode अगर needed (निकास by reset) */
		अन्यथा अगर (musb->test_mode) अणु
			musb_dbg(musb, "entering TESTMODE");

			अगर (MUSB_TEST_PACKET == musb->test_mode_nr)
				musb_load_testpacket(musb);

			musb_ग_लिखोb(mbase, MUSB_TESTMODE,
					musb->test_mode_nr);
		पूर्ण
		fallthrough;

	हाल MUSB_EP0_STAGE_STATUSOUT:
		/* end of sequence #1: ग_लिखो to host (TX state) */
		अणु
			काष्ठा musb_request	*req;

			req = next_ep0_request(musb);
			अगर (req)
				musb_g_ep0_giveback(musb, &req->request);
		पूर्ण

		/*
		 * In हाल when several पूर्णांकerrupts can get coalesced,
		 * check to see अगर we've alपढ़ोy received a SETUP packet...
		 */
		अगर (csr & MUSB_CSR0_RXPKTRDY)
			जाओ setup;

		retval = IRQ_HANDLED;
		musb->ep0_state = MUSB_EP0_STAGE_IDLE;
		अवरोध;

	हाल MUSB_EP0_STAGE_IDLE:
		/*
		 * This state is typically (but not always) indiscernible
		 * from the status states since the corresponding पूर्णांकerrupts
		 * tend to happen within too little period of समय (with only
		 * a zero-length packet in between) and so get coalesced...
		 */
		retval = IRQ_HANDLED;
		musb->ep0_state = MUSB_EP0_STAGE_SETUP;
		fallthrough;

	हाल MUSB_EP0_STAGE_SETUP:
setup:
		अगर (csr & MUSB_CSR0_RXPKTRDY) अणु
			काष्ठा usb_ctrlrequest	setup;
			पूर्णांक			handled = 0;

			अगर (len != 8) अणु
				ERR("SETUP packet len %d != 8 ?\n", len);
				अवरोध;
			पूर्ण
			musb_पढ़ो_setup(musb, &setup);
			retval = IRQ_HANDLED;

			/* someबार the RESET won't be reported */
			अगर (unlikely(musb->g.speed == USB_SPEED_UNKNOWN)) अणु
				u8	घातer;

				prपूर्णांकk(KERN_NOTICE "%s: peripheral reset "
						"irq lost!\n",
						musb_driver_name);
				घातer = musb_पढ़ोb(mbase, MUSB_POWER);
				musb->g.speed = (घातer & MUSB_POWER_HSMODE)
					? USB_SPEED_HIGH : USB_SPEED_FULL;

			पूर्ण

			चयन (musb->ep0_state) अणु

			/* sequence #3 (no data stage), includes requests
			 * we can't क्रमward (notably SET_ADDRESS and the
			 * device/endpoपूर्णांक feature set/clear operations)
			 * plus SET_CONFIGURATION and others we must
			 */
			हाल MUSB_EP0_STAGE_ACKWAIT:
				handled = service_zero_data_request(
						musb, &setup);

				/*
				 * We're expecting no data in any हाल, so
				 * always set the DATAEND bit -- करोing this
				 * here helps aव्योम SetupEnd पूर्णांकerrupt coming
				 * in the idle stage when we're stalling...
				 */
				musb->ackpend |= MUSB_CSR0_P_DATAEND;

				/* status stage might be immediate */
				अगर (handled > 0)
					musb->ep0_state =
						MUSB_EP0_STAGE_STATUSIN;
				अवरोध;

			/* sequence #1 (IN to host), includes GET_STATUS
			 * requests that we can't क्रमward, GET_DESCRIPTOR
			 * and others that we must
			 */
			हाल MUSB_EP0_STAGE_TX:
				handled = service_in_request(musb, &setup);
				अगर (handled > 0) अणु
					musb->ackpend = MUSB_CSR0_TXPKTRDY
						| MUSB_CSR0_P_DATAEND;
					musb->ep0_state =
						MUSB_EP0_STAGE_STATUSOUT;
				पूर्ण
				अवरोध;

			/* sequence #2 (OUT from host), always क्रमward */
			शेष:		/* MUSB_EP0_STAGE_RX */
				अवरोध;
			पूर्ण

			musb_dbg(musb, "handled %d, csr %04x, ep0stage %s",
				handled, csr,
				decode_ep0stage(musb->ep0_state));

			/* unless we need to delegate this to the gadget
			 * driver, we know how to wrap this up:  csr0 has
			 * not yet been written.
			 */
			अगर (handled < 0)
				जाओ stall;
			अन्यथा अगर (handled > 0)
				जाओ finish;

			handled = क्रमward_to_driver(musb, &setup);
			अगर (handled < 0) अणु
				musb_ep_select(mbase, 0);
stall:
				musb_dbg(musb, "stall (%d)", handled);
				musb->ackpend |= MUSB_CSR0_P_SENDSTALL;
				musb->ep0_state = MUSB_EP0_STAGE_IDLE;
finish:
				musb_ग_लिखोw(regs, MUSB_CSR0,
						musb->ackpend);
				musb->ackpend = 0;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल MUSB_EP0_STAGE_ACKWAIT:
		/* This should not happen. But happens with tusb6010 with
		 * g_file_storage and high speed. Do nothing.
		 */
		retval = IRQ_HANDLED;
		अवरोध;

	शेष:
		/* "can't happen" */
		WARN_ON(1);
		musb_ग_लिखोw(regs, MUSB_CSR0, MUSB_CSR0_P_SENDSTALL);
		musb->ep0_state = MUSB_EP0_STAGE_IDLE;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण


अटल पूर्णांक
musb_g_ep0_enable(काष्ठा usb_ep *ep, स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	/* always enabled */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक musb_g_ep0_disable(काष्ठा usb_ep *e)
अणु
	/* always enabled */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
musb_g_ep0_queue(काष्ठा usb_ep *e, काष्ठा usb_request *r, gfp_t gfp_flags)
अणु
	काष्ठा musb_ep		*ep;
	काष्ठा musb_request	*req;
	काष्ठा musb		*musb;
	पूर्णांक			status;
	अचिन्हित दीर्घ		lockflags;
	व्योम __iomem		*regs;

	अगर (!e || !r)
		वापस -EINVAL;

	ep = to_musb_ep(e);
	musb = ep->musb;
	regs = musb->control_ep->regs;

	req = to_musb_request(r);
	req->musb = musb;
	req->request.actual = 0;
	req->request.status = -EINPROGRESS;
	req->tx = ep->is_in;

	spin_lock_irqsave(&musb->lock, lockflags);

	अगर (!list_empty(&ep->req_list)) अणु
		status = -EBUSY;
		जाओ cleanup;
	पूर्ण

	चयन (musb->ep0_state) अणु
	हाल MUSB_EP0_STAGE_RX:		/* control-OUT data */
	हाल MUSB_EP0_STAGE_TX:		/* control-IN data */
	हाल MUSB_EP0_STAGE_ACKWAIT:	/* zero-length data */
		status = 0;
		अवरोध;
	शेष:
		musb_dbg(musb, "ep0 request queued in state %d",
				musb->ep0_state);
		status = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* add request to the list */
	list_add_tail(&req->list, &ep->req_list);

	musb_dbg(musb, "queue to %s (%s), length=%d",
			ep->name, ep->is_in ? "IN/TX" : "OUT/RX",
			req->request.length);

	musb_ep_select(musb->mregs, 0);

	/* sequence #1, IN ... start writing the data */
	अगर (musb->ep0_state == MUSB_EP0_STAGE_TX)
		ep0_txstate(musb);

	/* sequence #3, no-data ... issue IN status */
	अन्यथा अगर (musb->ep0_state == MUSB_EP0_STAGE_ACKWAIT) अणु
		अगर (req->request.length)
			status = -EINVAL;
		अन्यथा अणु
			musb->ep0_state = MUSB_EP0_STAGE_STATUSIN;
			musb_ग_लिखोw(regs, MUSB_CSR0,
					musb->ackpend | MUSB_CSR0_P_DATAEND);
			musb->ackpend = 0;
			musb_g_ep0_giveback(ep->musb, r);
		पूर्ण

	/* अन्यथा क्रम sequence #2 (OUT), caller provides a buffer
	 * beक्रमe the next packet arrives.  deferred responses
	 * (after SETUP is acked) are racey.
	 */
	पूर्ण अन्यथा अगर (musb->ackpend) अणु
		musb_ग_लिखोw(regs, MUSB_CSR0, musb->ackpend);
		musb->ackpend = 0;
	पूर्ण

cleanup:
	spin_unlock_irqrestore(&musb->lock, lockflags);
	वापस status;
पूर्ण

अटल पूर्णांक musb_g_ep0_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	/* we just won't support this */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक musb_g_ep0_halt(काष्ठा usb_ep *e, पूर्णांक value)
अणु
	काष्ठा musb_ep		*ep;
	काष्ठा musb		*musb;
	व्योम __iomem		*base, *regs;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			status;
	u16			csr;

	अगर (!e || !value)
		वापस -EINVAL;

	ep = to_musb_ep(e);
	musb = ep->musb;
	base = musb->mregs;
	regs = musb->control_ep->regs;
	status = 0;

	spin_lock_irqsave(&musb->lock, flags);

	अगर (!list_empty(&ep->req_list)) अणु
		status = -EBUSY;
		जाओ cleanup;
	पूर्ण

	musb_ep_select(base, 0);
	csr = musb->ackpend;

	चयन (musb->ep0_state) अणु

	/* Stalls are usually issued after parsing SETUP packet, either
	 * directly in irq context from setup() or अन्यथा later.
	 */
	हाल MUSB_EP0_STAGE_TX:		/* control-IN data */
	हाल MUSB_EP0_STAGE_ACKWAIT:	/* STALL क्रम zero-length data */
	हाल MUSB_EP0_STAGE_RX:		/* control-OUT data */
		csr = musb_पढ़ोw(regs, MUSB_CSR0);
		fallthrough;

	/* It's also OK to issue stalls during callbacks when a non-empty
	 * DATA stage buffer has been पढ़ो (or even written).
	 */
	हाल MUSB_EP0_STAGE_STATUSIN:	/* control-OUT status */
	हाल MUSB_EP0_STAGE_STATUSOUT:	/* control-IN status */

		csr |= MUSB_CSR0_P_SENDSTALL;
		musb_ग_लिखोw(regs, MUSB_CSR0, csr);
		musb->ep0_state = MUSB_EP0_STAGE_IDLE;
		musb->ackpend = 0;
		अवरोध;
	शेष:
		musb_dbg(musb, "ep0 can't halt in state %d", musb->ep0_state);
		status = -EINVAL;
	पूर्ण

cleanup:
	spin_unlock_irqrestore(&musb->lock, flags);
	वापस status;
पूर्ण

स्थिर काष्ठा usb_ep_ops musb_g_ep0_ops = अणु
	.enable		= musb_g_ep0_enable,
	.disable	= musb_g_ep0_disable,
	.alloc_request	= musb_alloc_request,
	.मुक्त_request	= musb_मुक्त_request,
	.queue		= musb_g_ep0_queue,
	.dequeue	= musb_g_ep0_dequeue,
	.set_halt	= musb_g_ep0_halt,
पूर्ण;
