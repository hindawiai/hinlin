<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * aspeed-vhub -- Driver क्रम Aspeed SoC "vHub" USB gadget
 *
 * epn.c - Generic endpoपूर्णांकs management
 *
 * Copyright 2017 IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

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
#समावेश <linux/usb/gadget.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/dma-mapping.h>

#समावेश "vhub.h"

#घोषणा EXTRA_CHECKS

#अगर_घोषित EXTRA_CHECKS
#घोषणा CHECK(ep, expr, fmt...)					\
	करो अणु							\
		अगर (!(expr)) EPDBG(ep, "CHECK:" fmt);		\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा CHECK(ep, expr, fmt...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल व्योम ast_vhub_epn_kick(काष्ठा ast_vhub_ep *ep, काष्ठा ast_vhub_req *req)
अणु
	अचिन्हित पूर्णांक act = req->req.actual;
	अचिन्हित पूर्णांक len = req->req.length;
	अचिन्हित पूर्णांक chunk;

	/* There should be no DMA ongoing */
	WARN_ON(req->active);

	/* Calculate next chunk size */
	chunk = len - act;
	अगर (chunk > ep->ep.maxpacket)
		chunk = ep->ep.maxpacket;
	अन्यथा अगर ((chunk < ep->ep.maxpacket) || !req->req.zero)
		req->last_desc = 1;

	EPVDBG(ep, "kick req %p act=%d/%d chunk=%d last=%d\n",
	       req, act, len, chunk, req->last_desc);

	/* If DMA unavailable, using staging EP buffer */
	अगर (!req->req.dma) अणु

		/* For IN transfers, copy data over first */
		अगर (ep->epn.is_in) अणु
			स_नकल(ep->buf, req->req.buf + act, chunk);
			vhub_dma_workaround(ep->buf);
		पूर्ण
		ग_लिखोl(ep->buf_dma, ep->epn.regs + AST_VHUB_EP_DESC_BASE);
	पूर्ण अन्यथा अणु
		अगर (ep->epn.is_in)
			vhub_dma_workaround(req->req.buf);
		ग_लिखोl(req->req.dma + act, ep->epn.regs + AST_VHUB_EP_DESC_BASE);
	पूर्ण

	/* Start DMA */
	req->active = true;
	ग_लिखोl(VHUB_EP_DMA_SET_TX_SIZE(chunk),
	       ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
	ग_लिखोl(VHUB_EP_DMA_SET_TX_SIZE(chunk) | VHUB_EP_DMA_SINGLE_KICK,
	       ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
पूर्ण

अटल व्योम ast_vhub_epn_handle_ack(काष्ठा ast_vhub_ep *ep)
अणु
	काष्ठा ast_vhub_req *req;
	अचिन्हित पूर्णांक len;
	u32 stat;

	/* Read EP status */
	stat = पढ़ोl(ep->epn.regs + AST_VHUB_EP_DESC_STATUS);

	/* Grab current request अगर any */
	req = list_first_entry_or_null(&ep->queue, काष्ठा ast_vhub_req, queue);

	EPVDBG(ep, "ACK status=%08x is_in=%d, req=%p (active=%d)\n",
	       stat, ep->epn.is_in, req, req ? req->active : 0);

	/* In असलence of a request, bail out, must have been dequeued */
	अगर (!req)
		वापस;

	/*
	 * Request not active, move on to processing queue, active request
	 * was probably dequeued
	 */
	अगर (!req->active)
		जाओ next_chunk;

	/* Check अगर HW has moved on */
	अगर (VHUB_EP_DMA_RPTR(stat) != 0) अणु
		EPDBG(ep, "DMA read pointer not 0 !\n");
		वापस;
	पूर्ण

	/* No current DMA ongoing */
	req->active = false;

	/* Grab length out of HW */
	len = VHUB_EP_DMA_TX_SIZE(stat);

	/* If not using DMA, copy data out अगर needed */
	अगर (!req->req.dma && !ep->epn.is_in && len)
		स_नकल(req->req.buf + req->req.actual, ep->buf, len);

	/* Adjust size */
	req->req.actual += len;

	/* Check क्रम लघु packet */
	अगर (len < ep->ep.maxpacket)
		req->last_desc = 1;

	/* That's it ? complete the request and pick a new one */
	अगर (req->last_desc >= 0) अणु
		ast_vhub_करोne(ep, req, 0);
		req = list_first_entry_or_null(&ep->queue, काष्ठा ast_vhub_req,
					       queue);

		/*
		 * Due to lock dropping inside "done" the next request could
		 * alपढ़ोy be active, so check क्रम that and bail अगर needed.
		 */
		अगर (!req || req->active)
			वापस;
	पूर्ण

 next_chunk:
	ast_vhub_epn_kick(ep, req);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ast_vhub_count_मुक्त_descs(काष्ठा ast_vhub_ep *ep)
अणु
	/*
	 * d_next == d_last means descriptor list empty to HW,
	 * thus we can only have AST_VHUB_DESCS_COUNT-1 descriptors
	 * in the list
	 */
	वापस (ep->epn.d_last + AST_VHUB_DESCS_COUNT - ep->epn.d_next - 1) &
		(AST_VHUB_DESCS_COUNT - 1);
पूर्ण

अटल व्योम ast_vhub_epn_kick_desc(काष्ठा ast_vhub_ep *ep,
				   काष्ठा ast_vhub_req *req)
अणु
	काष्ठा ast_vhub_desc *desc = शून्य;
	अचिन्हित पूर्णांक act = req->act_count;
	अचिन्हित पूर्णांक len = req->req.length;
	अचिन्हित पूर्णांक chunk;

	/* Mark request active अगर not alपढ़ोy */
	req->active = true;

	/* If the request was alपढ़ोy completely written, करो nothing */
	अगर (req->last_desc >= 0)
		वापस;

	EPVDBG(ep, "kick act=%d/%d chunk_max=%d free_descs=%d\n",
	       act, len, ep->epn.chunk_max, ast_vhub_count_मुक्त_descs(ep));

	/* While we can create descriptors */
	जबतक (ast_vhub_count_मुक्त_descs(ep) && req->last_desc < 0) अणु
		अचिन्हित पूर्णांक d_num;

		/* Grab next मुक्त descriptor */
		d_num = ep->epn.d_next;
		desc = &ep->epn.descs[d_num];
		ep->epn.d_next = (d_num + 1) & (AST_VHUB_DESCS_COUNT - 1);

		/* Calculate next chunk size */
		chunk = len - act;
		अगर (chunk <= ep->epn.chunk_max) अणु
			/*
			 * Is this the last packet ? Because of having up to 8
			 * packets in a descriptor we can't just compare "chunk"
			 * with ep.maxpacket. We have to see अगर it's a multiple
			 * of it to know अगर we have to send a zero packet.
			 * Sadly that involves a modulo which is a bit expensive
			 * but probably still better than not करोing it.
			 */
			अगर (!chunk || !req->req.zero || (chunk % ep->ep.maxpacket) != 0)
				req->last_desc = d_num;
		पूर्ण अन्यथा अणु
			chunk = ep->epn.chunk_max;
		पूर्ण

		EPVDBG(ep, " chunk: act=%d/%d chunk=%d last=%d desc=%d free=%d\n",
		       act, len, chunk, req->last_desc, d_num,
		       ast_vhub_count_मुक्त_descs(ep));

		/* Populate descriptor */
		desc->w0 = cpu_to_le32(req->req.dma + act);

		/* Interrupt अगर end of request or no more descriptors */

		/*
		 * TODO: Be smarter about it, अगर we करोn't have enough
		 * descriptors request an पूर्णांकerrupt beक्रमe queue empty
		 * or so in order to be able to populate more beक्रमe
		 * the HW runs out. This isn't a problem at the moment
		 * as we use 256 descriptors and only put at most one
		 * request in the ring.
		 */
		desc->w1 = cpu_to_le32(VHUB_DSC1_IN_SET_LEN(chunk));
		अगर (req->last_desc >= 0 || !ast_vhub_count_मुक्त_descs(ep))
			desc->w1 |= cpu_to_le32(VHUB_DSC1_IN_INTERRUPT);

		/* Account packet */
		req->act_count = act = act + chunk;
	पूर्ण

	अगर (likely(desc))
		vhub_dma_workaround(desc);

	/* Tell HW about new descriptors */
	ग_लिखोl(VHUB_EP_DMA_SET_CPU_WPTR(ep->epn.d_next),
	       ep->epn.regs + AST_VHUB_EP_DESC_STATUS);

	EPVDBG(ep, "HW kicked, d_next=%d dstat=%08x\n",
	       ep->epn.d_next, पढ़ोl(ep->epn.regs + AST_VHUB_EP_DESC_STATUS));
पूर्ण

अटल व्योम ast_vhub_epn_handle_ack_desc(काष्ठा ast_vhub_ep *ep)
अणु
	काष्ठा ast_vhub_req *req;
	अचिन्हित पूर्णांक len, d_last;
	u32 stat, stat1;

	/* Read EP status, workaround HW race */
	करो अणु
		stat = पढ़ोl(ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
		stat1 = पढ़ोl(ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
	पूर्ण जबतक(stat != stat1);

	/* Extract RPTR */
	d_last = VHUB_EP_DMA_RPTR(stat);

	/* Grab current request अगर any */
	req = list_first_entry_or_null(&ep->queue, काष्ठा ast_vhub_req, queue);

	EPVDBG(ep, "ACK status=%08x is_in=%d ep->d_last=%d..%d\n",
	       stat, ep->epn.is_in, ep->epn.d_last, d_last);

	/* Check all completed descriptors */
	जबतक (ep->epn.d_last != d_last) अणु
		काष्ठा ast_vhub_desc *desc;
		अचिन्हित पूर्णांक d_num;
		bool is_last_desc;

		/* Grab next completed descriptor */
		d_num = ep->epn.d_last;
		desc = &ep->epn.descs[d_num];
		ep->epn.d_last = (d_num + 1) & (AST_VHUB_DESCS_COUNT - 1);

		/* Grab len out of descriptor */
		len = VHUB_DSC1_IN_LEN(le32_to_cpu(desc->w1));

		EPVDBG(ep, " desc %d len=%d req=%p (act=%d)\n",
		       d_num, len, req, req ? req->active : 0);

		/* If no active request pending, move on */
		अगर (!req || !req->active)
			जारी;

		/* Adjust size */
		req->req.actual += len;

		/* Is that the last chunk ? */
		is_last_desc = req->last_desc == d_num;
		CHECK(ep, is_last_desc == (len < ep->ep.maxpacket ||
					   (req->req.actual >= req->req.length &&
					    !req->req.zero)),
		      "Last packet discrepancy: last_desc=%d len=%d r.act=%d "
		      "r.len=%d r.zero=%d mp=%d\n",
		      is_last_desc, len, req->req.actual, req->req.length,
		      req->req.zero, ep->ep.maxpacket);

		अगर (is_last_desc) अणु
			/*
			 * Because we can only have one request at a समय
			 * in our descriptor list in this implementation,
			 * d_last and ep->d_last should now be equal
			 */
			CHECK(ep, d_last == ep->epn.d_last,
			      "DMA read ptr mismatch %d vs %d\n",
			      d_last, ep->epn.d_last);

			/* Note: करोne will drop and re-acquire the lock */
			ast_vhub_करोne(ep, req, 0);
			req = list_first_entry_or_null(&ep->queue,
						       काष्ठा ast_vhub_req,
						       queue);
			अवरोध;
		पूर्ण
	पूर्ण

	/* More work ? */
	अगर (req)
		ast_vhub_epn_kick_desc(ep, req);
पूर्ण

व्योम ast_vhub_epn_ack_irq(काष्ठा ast_vhub_ep *ep)
अणु
	अगर (ep->epn.desc_mode)
		ast_vhub_epn_handle_ack_desc(ep);
	अन्यथा
		ast_vhub_epn_handle_ack(ep);
पूर्ण

अटल पूर्णांक ast_vhub_epn_queue(काष्ठा usb_ep* u_ep, काष्ठा usb_request *u_req,
			      gfp_t gfp_flags)
अणु
	काष्ठा ast_vhub_req *req = to_ast_req(u_req);
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub *vhub = ep->vhub;
	अचिन्हित दीर्घ flags;
	bool empty;
	पूर्णांक rc;

	/* Paranoid checks */
	अगर (!u_req || !u_req->complete || !u_req->buf) अणु
		dev_warn(&vhub->pdev->dev, "Bogus EPn request ! u_req=%p\n", u_req);
		अगर (u_req) अणु
			dev_warn(&vhub->pdev->dev, "complete=%p internal=%d\n",
				 u_req->complete, req->पूर्णांकernal);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/* Endpoपूर्णांक enabled ? */
	अगर (!ep->epn.enabled || !u_ep->desc || !ep->dev || !ep->d_idx ||
	    !ep->dev->enabled) अणु
		EPDBG(ep, "Enqueuing request on wrong or disabled EP\n");
		वापस -ESHUTDOWN;
	पूर्ण

	/* Map request क्रम DMA अगर possible. For now, the rule क्रम DMA is
	 * that:
	 *
	 *  * For single stage mode (no descriptors):
	 *
	 *   - The buffer is aligned to a 8 bytes boundary (HW requirement)
	 *   - For a OUT endpoपूर्णांक, the request size is a multiple of the EP
	 *     packet size (otherwise the controller will DMA past the end
	 *     of the buffer अगर the host is sending a too दीर्घ packet).
	 *
	 *  * For descriptor mode (tx only क्रम now), always.
	 *
	 * We could relax the latter by making the decision to use the bounce
	 * buffer based on the size of a given *segment* of the request rather
	 * than the whole request.
	 */
	अगर (ep->epn.desc_mode ||
	    ((((अचिन्हित दीर्घ)u_req->buf & 7) == 0) &&
	     (ep->epn.is_in || !(u_req->length & (u_ep->maxpacket - 1))))) अणु
		rc = usb_gadget_map_request_by_dev(&vhub->pdev->dev, u_req,
					    ep->epn.is_in);
		अगर (rc) अणु
			dev_warn(&vhub->pdev->dev,
				 "Request mapping failure %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा
		u_req->dma = 0;

	EPVDBG(ep, "enqueue req @%p\n", req);
	EPVDBG(ep, " l=%d dma=0x%x zero=%d noshort=%d noirq=%d is_in=%d\n",
	       u_req->length, (u32)u_req->dma, u_req->zero,
	       u_req->लघु_not_ok, u_req->no_पूर्णांकerrupt,
	       ep->epn.is_in);

	/* Initialize request progress fields */
	u_req->status = -EINPROGRESS;
	u_req->actual = 0;
	req->act_count = 0;
	req->active = false;
	req->last_desc = -1;
	spin_lock_irqsave(&vhub->lock, flags);
	empty = list_empty(&ep->queue);

	/* Add request to list and kick processing अगर empty */
	list_add_tail(&req->queue, &ep->queue);
	अगर (empty) अणु
		अगर (ep->epn.desc_mode)
			ast_vhub_epn_kick_desc(ep, req);
		अन्यथा
			ast_vhub_epn_kick(ep, req);
	पूर्ण
	spin_unlock_irqrestore(&vhub->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ast_vhub_stop_active_req(काष्ठा ast_vhub_ep *ep,
				     bool restart_ep)
अणु
	u32 state, reg, loops;

	/* Stop DMA activity */
	अगर (ep->epn.desc_mode)
		ग_लिखोl(VHUB_EP_DMA_CTRL_RESET, ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	अन्यथा
		ग_लिखोl(0, ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);

	/* Wait क्रम it to complete */
	क्रम (loops = 0; loops < 1000; loops++) अणु
		state = पढ़ोl(ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
		state = VHUB_EP_DMA_PROC_STATUS(state);
		अगर (state == EP_DMA_PROC_RX_IDLE ||
		    state == EP_DMA_PROC_TX_IDLE)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (loops >= 1000)
		dev_warn(&ep->vhub->pdev->dev, "Timeout waiting for DMA\n");

	/* If we करोn't have to restart the endpoint, that's it */
	अगर (!restart_ep)
		वापस;

	/* Restart the endpoपूर्णांक */
	अगर (ep->epn.desc_mode) अणु
		/*
		 * Take out descriptors by resetting the DMA पढ़ो
		 * poपूर्णांकer to be equal to the CPU ग_लिखो poपूर्णांकer.
		 *
		 * Note: If we ever support creating descriptors क्रम
		 * requests that aren't the head of the queue, we
		 * may have to करो something more complex here,
		 * especially अगर the request being taken out is
		 * not the current head descriptors.
		 */
		reg = VHUB_EP_DMA_SET_RPTR(ep->epn.d_next) |
			VHUB_EP_DMA_SET_CPU_WPTR(ep->epn.d_next);
		ग_लिखोl(reg, ep->epn.regs + AST_VHUB_EP_DESC_STATUS);

		/* Then turn it back on */
		ग_लिखोl(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	पूर्ण अन्यथा अणु
		/* Single mode: just turn it back on */
		ग_लिखोl(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	पूर्ण
पूर्ण

अटल पूर्णांक ast_vhub_epn_dequeue(काष्ठा usb_ep* u_ep, काष्ठा usb_request *u_req)
अणु
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub *vhub = ep->vhub;
	काष्ठा ast_vhub_req *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -EINVAL;

	spin_lock_irqsave(&vhub->lock, flags);

	/* Make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry (req, &ep->queue, queue) अणु
		अगर (&req->req == u_req)
			अवरोध;
	पूर्ण

	अगर (&req->req == u_req) अणु
		EPVDBG(ep, "dequeue req @%p active=%d\n",
		       req, req->active);
		अगर (req->active)
			ast_vhub_stop_active_req(ep, true);
		ast_vhub_करोne(ep, req, -ECONNRESET);
		rc = 0;
	पूर्ण

	spin_unlock_irqrestore(&vhub->lock, flags);
	वापस rc;
पूर्ण

व्योम ast_vhub_update_epn_stall(काष्ठा ast_vhub_ep *ep)
अणु
	u32 reg;

	अगर (WARN_ON(ep->d_idx == 0))
		वापस;
	reg = पढ़ोl(ep->epn.regs + AST_VHUB_EP_CONFIG);
	अगर (ep->epn.stalled || ep->epn.wedged)
		reg |= VHUB_EP_CFG_STALL_CTRL;
	अन्यथा
		reg &= ~VHUB_EP_CFG_STALL_CTRL;
	ग_लिखोl(reg, ep->epn.regs + AST_VHUB_EP_CONFIG);

	अगर (!ep->epn.stalled && !ep->epn.wedged)
		ग_लिखोl(VHUB_EP_TOGGLE_SET_EPNUM(ep->epn.g_idx),
		       ep->vhub->regs + AST_VHUB_EP_TOGGLE);
पूर्ण

अटल पूर्णांक ast_vhub_set_halt_and_wedge(काष्ठा usb_ep* u_ep, bool halt,
				      bool wedge)
अणु
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub *vhub = ep->vhub;
	अचिन्हित दीर्घ flags;

	EPDBG(ep, "Set halt (%d) & wedge (%d)\n", halt, wedge);

	अगर (!u_ep || !u_ep->desc)
		वापस -EINVAL;
	अगर (ep->d_idx == 0)
		वापस 0;
	अगर (ep->epn.is_iso)
		वापस -EOPNOTSUPP;

	spin_lock_irqsave(&vhub->lock, flags);

	/* Fail with still-busy IN endpoपूर्णांकs */
	अगर (halt && ep->epn.is_in && !list_empty(&ep->queue)) अणु
		spin_unlock_irqrestore(&vhub->lock, flags);
		वापस -EAGAIN;
	पूर्ण
	ep->epn.stalled = halt;
	ep->epn.wedged = wedge;
	ast_vhub_update_epn_stall(ep);

	spin_unlock_irqrestore(&vhub->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ast_vhub_epn_set_halt(काष्ठा usb_ep *u_ep, पूर्णांक value)
अणु
	वापस ast_vhub_set_halt_and_wedge(u_ep, value != 0, false);
पूर्ण

अटल पूर्णांक ast_vhub_epn_set_wedge(काष्ठा usb_ep *u_ep)
अणु
	वापस ast_vhub_set_halt_and_wedge(u_ep, true, true);
पूर्ण

अटल पूर्णांक ast_vhub_epn_disable(काष्ठा usb_ep* u_ep)
अणु
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub *vhub = ep->vhub;
	अचिन्हित दीर्घ flags;
	u32 imask, ep_ier;

	EPDBG(ep, "Disabling !\n");

	spin_lock_irqsave(&vhub->lock, flags);

	ep->epn.enabled = false;

	/* Stop active DMA अगर any */
	ast_vhub_stop_active_req(ep, false);

	/* Disable endpoपूर्णांक */
	ग_लिखोl(0, ep->epn.regs + AST_VHUB_EP_CONFIG);

	/* Disable ACK पूर्णांकerrupt */
	imask = VHUB_EP_IRQ(ep->epn.g_idx);
	ep_ier = पढ़ोl(vhub->regs + AST_VHUB_EP_ACK_IER);
	ep_ier &= ~imask;
	ग_लिखोl(ep_ier, vhub->regs + AST_VHUB_EP_ACK_IER);
	ग_लिखोl(imask, vhub->regs + AST_VHUB_EP_ACK_ISR);

	/* Nuke all pending requests */
	ast_vhub_nuke(ep, -ESHUTDOWN);

	/* No more descriptor associated with request */
	ep->ep.desc = शून्य;

	spin_unlock_irqrestore(&vhub->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ast_vhub_epn_enable(काष्ठा usb_ep* u_ep,
			       स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);
	काष्ठा ast_vhub_dev *dev;
	काष्ठा ast_vhub *vhub;
	u16 maxpacket, type;
	अचिन्हित दीर्घ flags;
	u32 ep_conf, ep_ier, imask;

	/* Check arguments */
	अगर (!u_ep || !desc)
		वापस -EINVAL;

	maxpacket = usb_endpoपूर्णांक_maxp(desc);
	अगर (!ep->d_idx || !ep->dev ||
	    desc->bDescriptorType != USB_DT_ENDPOINT ||
	    maxpacket == 0 || maxpacket > ep->ep.maxpacket) अणु
		EPDBG(ep, "Invalid EP enable,d_idx=%d,dev=%p,type=%d,mp=%d/%d\n",
		      ep->d_idx, ep->dev, desc->bDescriptorType,
		      maxpacket, ep->ep.maxpacket);
		वापस -EINVAL;
	पूर्ण
	अगर (ep->d_idx != usb_endpoपूर्णांक_num(desc)) अणु
		EPDBG(ep, "EP number mismatch !\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ep->epn.enabled) अणु
		EPDBG(ep, "Already enabled\n");
		वापस -EBUSY;
	पूर्ण
	dev = ep->dev;
	vhub = ep->vhub;

	/* Check device state */
	अगर (!dev->driver) अणु
		EPDBG(ep, "Bogus device state: driver=%p speed=%d\n",
		       dev->driver, dev->gadget.speed);
		वापस -ESHUTDOWN;
	पूर्ण

	/* Grab some info from the descriptor */
	ep->epn.is_in = usb_endpoपूर्णांक_dir_in(desc);
	ep->ep.maxpacket = maxpacket;
	type = usb_endpoपूर्णांक_type(desc);
	ep->epn.d_next = ep->epn.d_last = 0;
	ep->epn.is_iso = false;
	ep->epn.stalled = false;
	ep->epn.wedged = false;

	EPDBG(ep, "Enabling [%s] %s num %d maxpacket=%d\n",
	      ep->epn.is_in ? "in" : "out", usb_ep_type_string(type),
	      usb_endpoपूर्णांक_num(desc), maxpacket);

	/* Can we use DMA descriptor mode ? */
	ep->epn.desc_mode = ep->epn.descs && ep->epn.is_in;
	अगर (ep->epn.desc_mode)
		स_रखो(ep->epn.descs, 0, 8 * AST_VHUB_DESCS_COUNT);

	/*
	 * Large send function can send up to 8 packets from
	 * one descriptor with a limit of 4095 bytes.
	 */
	ep->epn.chunk_max = ep->ep.maxpacket;
	अगर (ep->epn.is_in) अणु
		ep->epn.chunk_max <<= 3;
		जबतक (ep->epn.chunk_max > 4095)
			ep->epn.chunk_max -= ep->ep.maxpacket;
	पूर्ण

	चयन(type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		EPDBG(ep, "Only one control endpoint\n");
		वापस -EINVAL;
	हाल USB_ENDPOINT_XFER_INT:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_INT);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_BULK);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_ISO);
		ep->epn.is_iso = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Encode the rest of the EP config रेजिस्टर */
	अगर (maxpacket < 1024)
		ep_conf |= VHUB_EP_CFG_SET_MAX_PKT(maxpacket);
	अगर (!ep->epn.is_in)
		ep_conf |= VHUB_EP_CFG_सूची_OUT;
	ep_conf |= VHUB_EP_CFG_SET_EP_NUM(usb_endpoपूर्णांक_num(desc));
	ep_conf |= VHUB_EP_CFG_ENABLE;
	ep_conf |= VHUB_EP_CFG_SET_DEV(dev->index + 1);
	EPVDBG(ep, "config=%08x\n", ep_conf);

	spin_lock_irqsave(&vhub->lock, flags);

	/* Disable HW and reset DMA */
	ग_लिखोl(0, ep->epn.regs + AST_VHUB_EP_CONFIG);
	ग_लिखोl(VHUB_EP_DMA_CTRL_RESET,
	       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);

	/* Configure and enable */
	ग_लिखोl(ep_conf, ep->epn.regs + AST_VHUB_EP_CONFIG);

	अगर (ep->epn.desc_mode) अणु
		/* Clear DMA status, including the DMA पढ़ो ptr */
		ग_लिखोl(0, ep->epn.regs + AST_VHUB_EP_DESC_STATUS);

		/* Set descriptor base */
		ग_लिखोl(ep->epn.descs_dma,
		       ep->epn.regs + AST_VHUB_EP_DESC_BASE);

		/* Set base DMA config value */
		ep->epn.dma_conf = VHUB_EP_DMA_DESC_MODE;
		अगर (ep->epn.is_in)
			ep->epn.dma_conf |= VHUB_EP_DMA_IN_LONG_MODE;

		/* First reset and disable all operations */
		ग_लिखोl(ep->epn.dma_conf | VHUB_EP_DMA_CTRL_RESET,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);

		/* Enable descriptor mode */
		ग_लिखोl(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	पूर्ण अन्यथा अणु
		/* Set base DMA config value */
		ep->epn.dma_conf = VHUB_EP_DMA_SINGLE_STAGE;

		/* Reset and चयन to single stage mode */
		ग_लिखोl(ep->epn.dma_conf | VHUB_EP_DMA_CTRL_RESET,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
		ग_लिखोl(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
		ग_लिखोl(0, ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
	पूर्ण

	/* Cleanup data toggle just in हाल */
	ग_लिखोl(VHUB_EP_TOGGLE_SET_EPNUM(ep->epn.g_idx),
	       vhub->regs + AST_VHUB_EP_TOGGLE);

	/* Cleanup and enable ACK पूर्णांकerrupt */
	imask = VHUB_EP_IRQ(ep->epn.g_idx);
	ग_लिखोl(imask, vhub->regs + AST_VHUB_EP_ACK_ISR);
	ep_ier = पढ़ोl(vhub->regs + AST_VHUB_EP_ACK_IER);
	ep_ier |= imask;
	ग_लिखोl(ep_ier, vhub->regs + AST_VHUB_EP_ACK_IER);

	/* Woot, we are online ! */
	ep->epn.enabled = true;

	spin_unlock_irqrestore(&vhub->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ast_vhub_epn_dispose(काष्ठा usb_ep *u_ep)
अणु
	काष्ठा ast_vhub_ep *ep = to_ast_ep(u_ep);

	अगर (WARN_ON(!ep->dev || !ep->d_idx))
		वापस;

	EPDBG(ep, "Releasing endpoint\n");

	/* Take it out of the EP list */
	list_del_init(&ep->ep.ep_list);

	/* Mark the address मुक्त in the device */
	ep->dev->epns[ep->d_idx - 1] = शून्य;

	/* Free name & DMA buffers */
	kमुक्त(ep->ep.name);
	ep->ep.name = शून्य;
	dma_मुक्त_coherent(&ep->vhub->pdev->dev,
			  AST_VHUB_EPn_MAX_PACKET +
			  8 * AST_VHUB_DESCS_COUNT,
			  ep->buf, ep->buf_dma);
	ep->buf = शून्य;
	ep->epn.descs = शून्य;

	/* Mark मुक्त */
	ep->dev = शून्य;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops ast_vhub_epn_ops = अणु
	.enable		= ast_vhub_epn_enable,
	.disable	= ast_vhub_epn_disable,
	.dispose	= ast_vhub_epn_dispose,
	.queue		= ast_vhub_epn_queue,
	.dequeue	= ast_vhub_epn_dequeue,
	.set_halt	= ast_vhub_epn_set_halt,
	.set_wedge	= ast_vhub_epn_set_wedge,
	.alloc_request	= ast_vhub_alloc_request,
	.मुक्त_request	= ast_vhub_मुक्त_request,
पूर्ण;

काष्ठा ast_vhub_ep *ast_vhub_alloc_epn(काष्ठा ast_vhub_dev *d, u8 addr)
अणु
	काष्ठा ast_vhub *vhub = d->vhub;
	काष्ठा ast_vhub_ep *ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* Find a मुक्त one (no device) */
	spin_lock_irqsave(&vhub->lock, flags);
	क्रम (i = 0; i < vhub->max_epns; i++)
		अगर (vhub->epns[i].dev == शून्य)
			अवरोध;
	अगर (i >= vhub->max_epns) अणु
		spin_unlock_irqrestore(&vhub->lock, flags);
		वापस शून्य;
	पूर्ण

	/* Set it up */
	ep = &vhub->epns[i];
	ep->dev = d;
	spin_unlock_irqrestore(&vhub->lock, flags);

	DDBG(d, "Allocating gen EP %d for addr %d\n", i, addr);
	INIT_LIST_HEAD(&ep->queue);
	ep->d_idx = addr;
	ep->vhub = vhub;
	ep->ep.ops = &ast_vhub_epn_ops;
	ep->ep.name = kaप्र_लिखो(GFP_KERNEL, "ep%d", addr);
	d->epns[addr-1] = ep;
	ep->epn.g_idx = i;
	ep->epn.regs = vhub->regs + 0x200 + (i * 0x10);

	ep->buf = dma_alloc_coherent(&vhub->pdev->dev,
				     AST_VHUB_EPn_MAX_PACKET +
				     8 * AST_VHUB_DESCS_COUNT,
				     &ep->buf_dma, GFP_KERNEL);
	अगर (!ep->buf) अणु
		kमुक्त(ep->ep.name);
		ep->ep.name = शून्य;
		वापस शून्य;
	पूर्ण
	ep->epn.descs = ep->buf + AST_VHUB_EPn_MAX_PACKET;
	ep->epn.descs_dma = ep->buf_dma + AST_VHUB_EPn_MAX_PACKET;

	usb_ep_set_maxpacket_limit(&ep->ep, AST_VHUB_EPn_MAX_PACKET);
	list_add_tail(&ep->ep.ep_list, &d->gadget.ep_list);
	ep->ep.caps.type_iso = true;
	ep->ep.caps.type_bulk = true;
	ep->ep.caps.type_पूर्णांक = true;
	ep->ep.caps.dir_in = true;
	ep->ep.caps.dir_out = true;

	वापस ep;
पूर्ण
