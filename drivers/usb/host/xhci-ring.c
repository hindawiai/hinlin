<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

/*
 * Ring initialization rules:
 * 1. Each segment is initialized to zero, except क्रम link TRBs.
 * 2. Ring cycle state = 0.  This represents Producer Cycle State (PCS) or
 *    Consumer Cycle State (CCS), depending on ring function.
 * 3. Enqueue poपूर्णांकer = dequeue poपूर्णांकer = address of first TRB in the segment.
 *
 * Ring behavior rules:
 * 1. A ring is empty अगर enqueue == dequeue.  This means there will always be at
 *    least one मुक्त TRB in the ring.  This is useful अगर you want to turn that
 *    पूर्णांकo a link TRB and expand the ring.
 * 2. When incrementing an enqueue or dequeue poपूर्णांकer, अगर the next TRB is a
 *    link TRB, then load the poपूर्णांकer with the address in the link TRB.  If the
 *    link TRB had its toggle bit set, you may need to update the ring cycle
 *    state (see cycle bit rules).  You may have to करो this multiple बार
 *    until you reach a non-link TRB.
 * 3. A ring is full अगर enqueue++ (क्रम the definition of increment above)
 *    equals the dequeue poपूर्णांकer.
 *
 * Cycle bit rules:
 * 1. When a consumer increments a dequeue poपूर्णांकer and encounters a toggle bit
 *    in a link TRB, it must toggle the ring cycle state.
 * 2. When a producer increments an enqueue poपूर्णांकer and encounters a toggle bit
 *    in a link TRB, it must toggle the ring cycle state.
 *
 * Producer rules:
 * 1. Check अगर ring is full beक्रमe you enqueue.
 * 2. Write the ring cycle state to the cycle bit in the TRB you're enqueuing.
 *    Update enqueue poपूर्णांकer between each ग_लिखो (which may update the ring
 *    cycle state).
 * 3. Notअगरy consumer.  If SW is producer, it rings the करोorbell क्रम command
 *    and endpoपूर्णांक rings.  If HC is the producer क्रम the event ring,
 *    and it generates an पूर्णांकerrupt according to पूर्णांकerrupt modulation rules.
 *
 * Consumer rules:
 * 1. Check अगर TRB beदीर्घs to you.  If the cycle bit == your ring cycle state,
 *    the TRB is owned by the consumer.
 * 2. Update dequeue poपूर्णांकer (which may update the ring cycle state) and
 *    जारी processing TRBs until you reach a TRB which is not owned by you.
 * 3. Notअगरy the producer.  SW is the consumer क्रम the event ring, and it
 *   updates event ring dequeue poपूर्णांकer.  HC is the consumer क्रम the command and
 *   endpoपूर्णांक rings; it generates events on the event ring क्रम these.
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश "xhci.h"
#समावेश "xhci-trace.h"

अटल पूर्णांक queue_command(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
			 u32 field1, u32 field2,
			 u32 field3, u32 field4, bool command_must_succeed);

/*
 * Returns zero अगर the TRB isn't in this segment, otherwise it वापसs the DMA
 * address of the TRB.
 */
dma_addr_t xhci_trb_virt_to_dma(काष्ठा xhci_segment *seg,
		जोड़ xhci_trb *trb)
अणु
	अचिन्हित दीर्घ segment_offset;

	अगर (!seg || !trb || trb < seg->trbs)
		वापस 0;
	/* offset in TRBs */
	segment_offset = trb - seg->trbs;
	अगर (segment_offset >= TRBS_PER_SEGMENT)
		वापस 0;
	वापस seg->dma + (segment_offset * माप(*trb));
पूर्ण

अटल bool trb_is_noop(जोड़ xhci_trb *trb)
अणु
	वापस TRB_TYPE_NOOP_LE32(trb->generic.field[3]);
पूर्ण

अटल bool trb_is_link(जोड़ xhci_trb *trb)
अणु
	वापस TRB_TYPE_LINK_LE32(trb->link.control);
पूर्ण

अटल bool last_trb_on_seg(काष्ठा xhci_segment *seg, जोड़ xhci_trb *trb)
अणु
	वापस trb == &seg->trbs[TRBS_PER_SEGMENT - 1];
पूर्ण

अटल bool last_trb_on_ring(काष्ठा xhci_ring *ring,
			काष्ठा xhci_segment *seg, जोड़ xhci_trb *trb)
अणु
	वापस last_trb_on_seg(seg, trb) && (seg->next == ring->first_seg);
पूर्ण

अटल bool link_trb_toggles_cycle(जोड़ xhci_trb *trb)
अणु
	वापस le32_to_cpu(trb->link.control) & LINK_TOGGLE;
पूर्ण

अटल bool last_td_in_urb(काष्ठा xhci_td *td)
अणु
	काष्ठा urb_priv *urb_priv = td->urb->hcpriv;

	वापस urb_priv->num_tds_करोne == urb_priv->num_tds;
पूर्ण

अटल व्योम inc_td_cnt(काष्ठा urb *urb)
अणु
	काष्ठा urb_priv *urb_priv = urb->hcpriv;

	urb_priv->num_tds_करोne++;
पूर्ण

अटल व्योम trb_to_noop(जोड़ xhci_trb *trb, u32 noop_type)
अणु
	अगर (trb_is_link(trb)) अणु
		/* unchain chained link TRBs */
		trb->link.control &= cpu_to_le32(~TRB_CHAIN);
	पूर्ण अन्यथा अणु
		trb->generic.field[0] = 0;
		trb->generic.field[1] = 0;
		trb->generic.field[2] = 0;
		/* Preserve only the cycle bit of this TRB */
		trb->generic.field[3] &= cpu_to_le32(TRB_CYCLE);
		trb->generic.field[3] |= cpu_to_le32(TRB_TYPE(noop_type));
	पूर्ण
पूर्ण

/* Updates trb to poपूर्णांक to the next TRB in the ring, and updates seg अगर the next
 * TRB is in a new segment.  This करोes not skip over link TRBs, and it करोes not
 * effect the ring dequeue or enqueue poपूर्णांकers.
 */
अटल व्योम next_trb(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_ring *ring,
		काष्ठा xhci_segment **seg,
		जोड़ xhci_trb **trb)
अणु
	अगर (trb_is_link(*trb)) अणु
		*seg = (*seg)->next;
		*trb = ((*seg)->trbs);
	पूर्ण अन्यथा अणु
		(*trb)++;
	पूर्ण
पूर्ण

/*
 * See Cycle bit rules. SW is the consumer क्रम the event ring only.
 */
व्योम inc_deq(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring)
अणु
	अचिन्हित पूर्णांक link_trb_count = 0;

	/* event ring करोesn't have link trbs, check क्रम last trb */
	अगर (ring->type == TYPE_EVENT) अणु
		अगर (!last_trb_on_seg(ring->deq_seg, ring->dequeue)) अणु
			ring->dequeue++;
			जाओ out;
		पूर्ण
		अगर (last_trb_on_ring(ring, ring->deq_seg, ring->dequeue))
			ring->cycle_state ^= 1;
		ring->deq_seg = ring->deq_seg->next;
		ring->dequeue = ring->deq_seg->trbs;
		जाओ out;
	पूर्ण

	/* All other rings have link trbs */
	अगर (!trb_is_link(ring->dequeue)) अणु
		अगर (last_trb_on_seg(ring->deq_seg, ring->dequeue)) अणु
			xhci_warn(xhci, "Missing link TRB at end of segment\n");
		पूर्ण अन्यथा अणु
			ring->dequeue++;
			ring->num_trbs_मुक्त++;
		पूर्ण
	पूर्ण

	जबतक (trb_is_link(ring->dequeue)) अणु
		ring->deq_seg = ring->deq_seg->next;
		ring->dequeue = ring->deq_seg->trbs;

		अगर (link_trb_count++ > ring->num_segs) अणु
			xhci_warn(xhci, "Ring is an endless link TRB loop\n");
			अवरोध;
		पूर्ण
	पूर्ण
out:
	trace_xhci_inc_deq(ring);

	वापस;
पूर्ण

/*
 * See Cycle bit rules. SW is the consumer क्रम the event ring only.
 *
 * If we've just enqueued a TRB that is in the middle of a TD (meaning the
 * chain bit is set), then set the chain bit in all the following link TRBs.
 * If we've enqueued the last TRB in a TD, make sure the following link TRBs
 * have their chain bit cleared (so that each Link TRB is a separate TD).
 *
 * Section 6.4.4.1 of the 0.95 spec says link TRBs cannot have the chain bit
 * set, but other sections talk about dealing with the chain bit set.  This was
 * fixed in the 0.96 specअगरication errata, but we have to assume that all 0.95
 * xHCI hardware can't handle the chain bit being cleared on a link TRB.
 *
 * @more_trbs_coming:	Will you enqueue more TRBs beक्रमe calling
 *			prepare_transfer()?
 */
अटल व्योम inc_enq(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
			bool more_trbs_coming)
अणु
	u32 chain;
	जोड़ xhci_trb *next;
	अचिन्हित पूर्णांक link_trb_count = 0;

	chain = le32_to_cpu(ring->enqueue->generic.field[3]) & TRB_CHAIN;
	/* If this is not event ring, there is one less usable TRB */
	अगर (!trb_is_link(ring->enqueue))
		ring->num_trbs_मुक्त--;

	अगर (last_trb_on_seg(ring->enq_seg, ring->enqueue)) अणु
		xhci_err(xhci, "Tried to move enqueue past ring segment\n");
		वापस;
	पूर्ण

	next = ++(ring->enqueue);

	/* Update the dequeue poपूर्णांकer further अगर that was a link TRB */
	जबतक (trb_is_link(next)) अणु

		/*
		 * If the caller करोesn't plan on enqueueing more TDs beक्रमe
		 * ringing the करोorbell, then we करोn't want to give the link TRB
		 * to the hardware just yet. We'll give the link TRB back in
		 * prepare_ring() just beक्रमe we enqueue the TD at the top of
		 * the ring.
		 */
		अगर (!chain && !more_trbs_coming)
			अवरोध;

		/* If we're not dealing with 0.95 hardware or isoc rings on
		 * AMD 0.96 host, carry over the chain bit of the previous TRB
		 * (which may mean the chain bit is cleared).
		 */
		अगर (!(ring->type == TYPE_ISOC &&
		      (xhci->quirks & XHCI_AMD_0x96_HOST)) &&
		    !xhci_link_trb_quirk(xhci)) अणु
			next->link.control &= cpu_to_le32(~TRB_CHAIN);
			next->link.control |= cpu_to_le32(chain);
		पूर्ण
		/* Give this link TRB to the hardware */
		wmb();
		next->link.control ^= cpu_to_le32(TRB_CYCLE);

		/* Toggle the cycle bit after the last ring segment. */
		अगर (link_trb_toggles_cycle(next))
			ring->cycle_state ^= 1;

		ring->enq_seg = ring->enq_seg->next;
		ring->enqueue = ring->enq_seg->trbs;
		next = ring->enqueue;

		अगर (link_trb_count++ > ring->num_segs) अणु
			xhci_warn(xhci, "%s: Ring link TRB loop\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	trace_xhci_inc_enq(ring);
पूर्ण

/*
 * Check to see अगर there's room to enqueue num_trbs on the ring and make sure
 * enqueue poपूर्णांकer will not advance पूर्णांकo dequeue segment. See rules above.
 */
अटल अंतरभूत पूर्णांक room_on_ring(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
		अचिन्हित पूर्णांक num_trbs)
अणु
	पूर्णांक num_trbs_in_deq_seg;

	अगर (ring->num_trbs_मुक्त < num_trbs)
		वापस 0;

	अगर (ring->type != TYPE_COMMAND && ring->type != TYPE_EVENT) अणु
		num_trbs_in_deq_seg = ring->dequeue - ring->deq_seg->trbs;
		अगर (ring->num_trbs_मुक्त < num_trbs + num_trbs_in_deq_seg)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* Ring the host controller करोorbell after placing a command on the ring */
व्योम xhci_ring_cmd_db(काष्ठा xhci_hcd *xhci)
अणु
	अगर (!(xhci->cmd_ring_state & CMD_RING_STATE_RUNNING))
		वापस;

	xhci_dbg(xhci, "// Ding dong!\n");

	trace_xhci_ring_host_करोorbell(0, DB_VALUE_HOST);

	ग_लिखोl(DB_VALUE_HOST, &xhci->dba->करोorbell[0]);
	/* Flush PCI posted ग_लिखोs */
	पढ़ोl(&xhci->dba->करोorbell[0]);
पूर्ण

अटल bool xhci_mod_cmd_समयr(काष्ठा xhci_hcd *xhci, अचिन्हित दीर्घ delay)
अणु
	वापस mod_delayed_work(प्रणाली_wq, &xhci->cmd_समयr, delay);
पूर्ण

अटल काष्ठा xhci_command *xhci_next_queued_cmd(काष्ठा xhci_hcd *xhci)
अणु
	वापस list_first_entry_or_null(&xhci->cmd_list, काष्ठा xhci_command,
					cmd_list);
पूर्ण

/*
 * Turn all commands on command ring with status set to "aborted" to no-op trbs.
 * If there are other commands रुकोing then restart the ring and kick the समयr.
 * This must be called with command ring stopped and xhci->lock held.
 */
अटल व्योम xhci_handle_stopped_cmd_ring(काष्ठा xhci_hcd *xhci,
					 काष्ठा xhci_command *cur_cmd)
अणु
	काष्ठा xhci_command *i_cmd;

	/* Turn all पातed commands in list to no-ops, then restart */
	list_क्रम_each_entry(i_cmd, &xhci->cmd_list, cmd_list) अणु

		अगर (i_cmd->status != COMP_COMMAND_ABORTED)
			जारी;

		i_cmd->status = COMP_COMMAND_RING_STOPPED;

		xhci_dbg(xhci, "Turn aborted command %p to no-op\n",
			 i_cmd->command_trb);

		trb_to_noop(i_cmd->command_trb, TRB_CMD_NOOP);

		/*
		 * caller रुकोing क्रम completion is called when command
		 *  completion event is received क्रम these no-op commands
		 */
	पूर्ण

	xhci->cmd_ring_state = CMD_RING_STATE_RUNNING;

	/* ring command ring करोorbell to restart the command ring */
	अगर ((xhci->cmd_ring->dequeue != xhci->cmd_ring->enqueue) &&
	    !(xhci->xhc_state & XHCI_STATE_DYING)) अणु
		xhci->current_cmd = cur_cmd;
		xhci_mod_cmd_समयr(xhci, XHCI_CMD_DEFAULT_TIMEOUT);
		xhci_ring_cmd_db(xhci);
	पूर्ण
पूर्ण

/* Must be called with xhci->lock held, releases and aquires lock back */
अटल पूर्णांक xhci_पात_cmd_ring(काष्ठा xhci_hcd *xhci, अचिन्हित दीर्घ flags)
अणु
	u64 temp_64;
	पूर्णांक ret;

	xhci_dbg(xhci, "Abort command ring\n");

	reinit_completion(&xhci->cmd_ring_stop_completion);

	temp_64 = xhci_पढ़ो_64(xhci, &xhci->op_regs->cmd_ring);
	xhci_ग_लिखो_64(xhci, temp_64 | CMD_RING_ABORT,
			&xhci->op_regs->cmd_ring);

	/* Section 4.6.1.2 of xHCI 1.0 spec says software should also समय the
	 * completion of the Command Abort operation. If CRR is not negated in 5
	 * seconds then driver handles it as अगर host died (-ENODEV).
	 * In the future we should distinguish between -ENODEV and -ETIMEDOUT
	 * and try to recover a -ETIMEDOUT with a host controller reset.
	 */
	ret = xhci_handshake(&xhci->op_regs->cmd_ring,
			CMD_RING_RUNNING, 0, 5 * 1000 * 1000);
	अगर (ret < 0) अणु
		xhci_err(xhci, "Abort failed to stop command ring: %d\n", ret);
		xhci_halt(xhci);
		xhci_hc_died(xhci);
		वापस ret;
	पूर्ण
	/*
	 * Writing the CMD_RING_ABORT bit should cause a cmd completion event,
	 * however on some host hw the CMD_RING_RUNNING bit is correctly cleared
	 * but the completion event in never sent. Wait 2 secs (arbitrary
	 * number) to handle those हालs after negation of CMD_RING_RUNNING.
	 */
	spin_unlock_irqrestore(&xhci->lock, flags);
	ret = रुको_क्रम_completion_समयout(&xhci->cmd_ring_stop_completion,
					  msecs_to_jअगरfies(2000));
	spin_lock_irqsave(&xhci->lock, flags);
	अगर (!ret) अणु
		xhci_dbg(xhci, "No stop event for abort, ring start fail?\n");
		xhci_cleanup_command_queue(xhci);
	पूर्ण अन्यथा अणु
		xhci_handle_stopped_cmd_ring(xhci, xhci_next_queued_cmd(xhci));
	पूर्ण
	वापस 0;
पूर्ण

व्योम xhci_ring_ep_करोorbell(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index,
		अचिन्हित पूर्णांक stream_id)
अणु
	__le32 __iomem *db_addr = &xhci->dba->करोorbell[slot_id];
	काष्ठा xhci_virt_ep *ep = &xhci->devs[slot_id]->eps[ep_index];
	अचिन्हित पूर्णांक ep_state = ep->ep_state;

	/* Don't ring the करोorbell क्रम this endpoपूर्णांक अगर there are pending
	 * cancellations because we करोn't want to पूर्णांकerrupt processing.
	 * We करोn't want to restart any stream rings if there's a set dequeue
	 * poपूर्णांकer command pending because the device can choose to start any
	 * stream once the endpoपूर्णांक is on the HW schedule.
	 */
	अगर ((ep_state & EP_STOP_CMD_PENDING) || (ep_state & SET_DEQ_PENDING) ||
	    (ep_state & EP_HALTED) || (ep_state & EP_CLEARING_TT))
		वापस;

	trace_xhci_ring_ep_करोorbell(slot_id, DB_VALUE(ep_index, stream_id));

	ग_लिखोl(DB_VALUE(ep_index, stream_id), db_addr);
	/* flush the ग_लिखो */
	पढ़ोl(db_addr);
पूर्ण

/* Ring the करोorbell क्रम any rings with pending URBs */
अटल व्योम ring_करोorbell_क्रम_active_rings(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index)
अणु
	अचिन्हित पूर्णांक stream_id;
	काष्ठा xhci_virt_ep *ep;

	ep = &xhci->devs[slot_id]->eps[ep_index];

	/* A ring has pending URBs अगर its TD list is not empty */
	अगर (!(ep->ep_state & EP_HAS_STREAMS)) अणु
		अगर (ep->ring && !(list_empty(&ep->ring->td_list)))
			xhci_ring_ep_करोorbell(xhci, slot_id, ep_index, 0);
		वापस;
	पूर्ण

	क्रम (stream_id = 1; stream_id < ep->stream_info->num_streams;
			stream_id++) अणु
		काष्ठा xhci_stream_info *stream_info = ep->stream_info;
		अगर (!list_empty(&stream_info->stream_rings[stream_id]->td_list))
			xhci_ring_ep_करोorbell(xhci, slot_id, ep_index,
						stream_id);
	पूर्ण
पूर्ण

व्योम xhci_ring_करोorbell_क्रम_active_rings(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index)
अणु
	ring_करोorbell_क्रम_active_rings(xhci, slot_id, ep_index);
पूर्ण

अटल काष्ठा xhci_virt_ep *xhci_get_virt_ep(काष्ठा xhci_hcd *xhci,
					     अचिन्हित पूर्णांक slot_id,
					     अचिन्हित पूर्णांक ep_index)
अणु
	अगर (slot_id == 0 || slot_id >= MAX_HC_SLOTS) अणु
		xhci_warn(xhci, "Invalid slot_id %u\n", slot_id);
		वापस शून्य;
	पूर्ण
	अगर (ep_index >= EP_CTX_PER_DEV) अणु
		xhci_warn(xhci, "Invalid endpoint index %u\n", ep_index);
		वापस शून्य;
	पूर्ण
	अगर (!xhci->devs[slot_id]) अणु
		xhci_warn(xhci, "No xhci virt device for slot_id %u\n", slot_id);
		वापस शून्य;
	पूर्ण

	वापस &xhci->devs[slot_id]->eps[ep_index];
पूर्ण

अटल काष्ठा xhci_ring *xhci_virt_ep_to_ring(काष्ठा xhci_hcd *xhci,
					      काष्ठा xhci_virt_ep *ep,
					      अचिन्हित पूर्णांक stream_id)
अणु
	/* common हाल, no streams */
	अगर (!(ep->ep_state & EP_HAS_STREAMS))
		वापस ep->ring;

	अगर (!ep->stream_info)
		वापस शून्य;

	अगर (stream_id == 0 || stream_id >= ep->stream_info->num_streams) अणु
		xhci_warn(xhci, "Invalid stream_id %u request for slot_id %u ep_index %u\n",
			  stream_id, ep->vdev->slot_id, ep->ep_index);
		वापस शून्य;
	पूर्ण

	वापस ep->stream_info->stream_rings[stream_id];
पूर्ण

/* Get the right ring क्रम the given slot_id, ep_index and stream_id.
 * If the endpoपूर्णांक supports streams, boundary check the URB's stream ID.
 * If the endpoपूर्णांक करोesn't support streams, वापस the singular endpoपूर्णांक ring.
 */
काष्ठा xhci_ring *xhci_triad_to_transfer_ring(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index,
		अचिन्हित पूर्णांक stream_id)
अणु
	काष्ठा xhci_virt_ep *ep;

	ep = xhci_get_virt_ep(xhci, slot_id, ep_index);
	अगर (!ep)
		वापस शून्य;

	वापस xhci_virt_ep_to_ring(xhci, ep, stream_id);
पूर्ण


/*
 * Get the hw dequeue poपूर्णांकer xHC stopped on, either directly from the
 * endpoपूर्णांक context, or अगर streams are in use from the stream context.
 * The वापसed hw_dequeue contains the lowest four bits with cycle state
 * and possbile stream context type.
 */
अटल u64 xhci_get_hw_deq(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_device *vdev,
			   अचिन्हित पूर्णांक ep_index, अचिन्हित पूर्णांक stream_id)
अणु
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_stream_ctx *st_ctx;
	काष्ठा xhci_virt_ep *ep;

	ep = &vdev->eps[ep_index];

	अगर (ep->ep_state & EP_HAS_STREAMS) अणु
		st_ctx = &ep->stream_info->stream_ctx_array[stream_id];
		वापस le64_to_cpu(st_ctx->stream_ring);
	पूर्ण
	ep_ctx = xhci_get_ep_ctx(xhci, vdev->out_ctx, ep_index);
	वापस le64_to_cpu(ep_ctx->deq);
पूर्ण

अटल पूर्णांक xhci_move_dequeue_past_td(काष्ठा xhci_hcd *xhci,
				अचिन्हित पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index,
				अचिन्हित पूर्णांक stream_id, काष्ठा xhci_td *td)
अणु
	काष्ठा xhci_virt_device *dev = xhci->devs[slot_id];
	काष्ठा xhci_virt_ep *ep = &dev->eps[ep_index];
	काष्ठा xhci_ring *ep_ring;
	काष्ठा xhci_command *cmd;
	काष्ठा xhci_segment *new_seg;
	जोड़ xhci_trb *new_deq;
	पूर्णांक new_cycle;
	dma_addr_t addr;
	u64 hw_dequeue;
	bool cycle_found = false;
	bool td_last_trb_found = false;
	u32 trb_sct = 0;
	पूर्णांक ret;

	ep_ring = xhci_triad_to_transfer_ring(xhci, slot_id,
			ep_index, stream_id);
	अगर (!ep_ring) अणु
		xhci_warn(xhci, "WARN can't find new dequeue, invalid stream ID %u\n",
			  stream_id);
		वापस -ENODEV;
	पूर्ण
	/*
	 * A cancelled TD can complete with a stall अगर HW cached the trb.
	 * In this हाल driver can't find td, but अगर the ring is empty we
	 * can move the dequeue poपूर्णांकer to the current enqueue position.
	 * We shouldn't hit this anymore as cached cancelled TRBs are given back
	 * after clearing the cache, but be on the safe side and keep it anyway
	 */
	अगर (!td) अणु
		अगर (list_empty(&ep_ring->td_list)) अणु
			new_seg = ep_ring->enq_seg;
			new_deq = ep_ring->enqueue;
			new_cycle = ep_ring->cycle_state;
			xhci_dbg(xhci, "ep ring empty, Set new dequeue = enqueue");
			जाओ deq_found;
		पूर्ण अन्यथा अणु
			xhci_warn(xhci, "Can't find new dequeue state, missing td\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	hw_dequeue = xhci_get_hw_deq(xhci, dev, ep_index, stream_id);
	new_seg = ep_ring->deq_seg;
	new_deq = ep_ring->dequeue;
	new_cycle = hw_dequeue & 0x1;

	/*
	 * We want to find the poपूर्णांकer, segment and cycle state of the new trb
	 * (the one after current TD's last_trb). We know the cycle state at
	 * hw_dequeue, so walk the ring until both hw_dequeue and last_trb are
	 * found.
	 */
	करो अणु
		अगर (!cycle_found && xhci_trb_virt_to_dma(new_seg, new_deq)
		    == (dma_addr_t)(hw_dequeue & ~0xf)) अणु
			cycle_found = true;
			अगर (td_last_trb_found)
				अवरोध;
		पूर्ण
		अगर (new_deq == td->last_trb)
			td_last_trb_found = true;

		अगर (cycle_found && trb_is_link(new_deq) &&
		    link_trb_toggles_cycle(new_deq))
			new_cycle ^= 0x1;

		next_trb(xhci, ep_ring, &new_seg, &new_deq);

		/* Search wrapped around, bail out */
		अगर (new_deq == ep->ring->dequeue) अणु
			xhci_err(xhci, "Error: Failed finding new dequeue state\n");
			वापस -EINVAL;
		पूर्ण

	पूर्ण जबतक (!cycle_found || !td_last_trb_found);

deq_found:

	/* Don't update the ring cycle state क्रम the producer (us). */
	addr = xhci_trb_virt_to_dma(new_seg, new_deq);
	अगर (addr == 0) अणु
		xhci_warn(xhci, "Can't find dma of new dequeue ptr\n");
		xhci_warn(xhci, "deq seg = %p, deq ptr = %p\n", new_seg, new_deq);
		वापस -EINVAL;
	पूर्ण

	अगर ((ep->ep_state & SET_DEQ_PENDING)) अणु
		xhci_warn(xhci, "Set TR Deq already pending, don't submit for 0x%pad\n",
			  &addr);
		वापस -EBUSY;
	पूर्ण

	/* This function माला_लो called from contexts where it cannot sleep */
	cmd = xhci_alloc_command(xhci, false, GFP_ATOMIC);
	अगर (!cmd) अणु
		xhci_warn(xhci, "Can't alloc Set TR Deq cmd 0x%pad\n", &addr);
		वापस -ENOMEM;
	पूर्ण

	अगर (stream_id)
		trb_sct = SCT_FOR_TRB(SCT_PRI_TR);
	ret = queue_command(xhci, cmd,
		lower_32_bits(addr) | trb_sct | new_cycle,
		upper_32_bits(addr),
		STREAM_ID_FOR_TRB(stream_id), SLOT_ID_FOR_TRB(slot_id) |
		EP_ID_FOR_TRB(ep_index) | TRB_TYPE(TRB_SET_DEQ), false);
	अगर (ret < 0) अणु
		xhci_मुक्त_command(xhci, cmd);
		वापस ret;
	पूर्ण
	ep->queued_deq_seg = new_seg;
	ep->queued_deq_ptr = new_deq;

	xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
		       "Set TR Deq ptr 0x%llx, cycle %u\n", addr, new_cycle);

	/* Stop the TD queueing code from ringing the करोorbell until
	 * this command completes.  The HC won't set the dequeue poपूर्णांकer
	 * अगर the ring is running, and ringing the करोorbell starts the
	 * ring running.
	 */
	ep->ep_state |= SET_DEQ_PENDING;
	xhci_ring_cmd_db(xhci);
	वापस 0;
पूर्ण

/* flip_cycle means flip the cycle bit of all but the first and last TRB.
 * (The last TRB actually poपूर्णांकs to the ring enqueue poपूर्णांकer, which is not part
 * of this TD.)  This is used to हटाओ partially enqueued isoc TDs from a ring.
 */
अटल व्योम td_to_noop(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ep_ring,
		       काष्ठा xhci_td *td, bool flip_cycle)
अणु
	काष्ठा xhci_segment *seg	= td->start_seg;
	जोड़ xhci_trb *trb		= td->first_trb;

	जबतक (1) अणु
		trb_to_noop(trb, TRB_TR_NOOP);

		/* flip cycle अगर asked to */
		अगर (flip_cycle && trb != td->first_trb && trb != td->last_trb)
			trb->generic.field[3] ^= cpu_to_le32(TRB_CYCLE);

		अगर (trb == td->last_trb)
			अवरोध;

		next_trb(xhci, ep_ring, &seg, &trb);
	पूर्ण
पूर्ण

अटल व्योम xhci_stop_watchकरोg_समयr_in_irq(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_ep *ep)
अणु
	ep->ep_state &= ~EP_STOP_CMD_PENDING;
	/* Can't del_समयr_sync in पूर्णांकerrupt */
	del_समयr(&ep->stop_cmd_समयr);
पूर्ण

/*
 * Must be called with xhci->lock held in पूर्णांकerrupt context,
 * releases and re-acquires xhci->lock
 */
अटल व्योम xhci_giveback_urb_in_irq(काष्ठा xhci_hcd *xhci,
				     काष्ठा xhci_td *cur_td, पूर्णांक status)
अणु
	काष्ठा urb	*urb		= cur_td->urb;
	काष्ठा urb_priv	*urb_priv	= urb->hcpriv;
	काष्ठा usb_hcd	*hcd		= bus_to_hcd(urb->dev->bus);

	अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) अणु
		xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs--;
		अगर (xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs	== 0) अणु
			अगर (xhci->quirks & XHCI_AMD_PLL_FIX)
				usb_amd_quirk_pll_enable();
		पूर्ण
	पूर्ण
	xhci_urb_मुक्त_priv(urb_priv);
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	trace_xhci_urb_giveback(urb);
	usb_hcd_giveback_urb(hcd, urb, status);
पूर्ण

अटल व्योम xhci_unmap_td_bounce_buffer(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_ring *ring, काष्ठा xhci_td *td)
अणु
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.controller;
	काष्ठा xhci_segment *seg = td->bounce_seg;
	काष्ठा urb *urb = td->urb;
	माप_प्रकार len;

	अगर (!ring || !seg || !urb)
		वापस;

	अगर (usb_urb_dir_out(urb)) अणु
		dma_unmap_single(dev, seg->bounce_dma, ring->bounce_buf_len,
				 DMA_TO_DEVICE);
		वापस;
	पूर्ण

	dma_unmap_single(dev, seg->bounce_dma, ring->bounce_buf_len,
			 DMA_FROM_DEVICE);
	/* क्रम in tranfers we need to copy the data from bounce to sg */
	अगर (urb->num_sgs) अणु
		len = sg_pcopy_from_buffer(urb->sg, urb->num_sgs, seg->bounce_buf,
					   seg->bounce_len, seg->bounce_offs);
		अगर (len != seg->bounce_len)
			xhci_warn(xhci, "WARN Wrong bounce buffer read length: %zu != %d\n",
				  len, seg->bounce_len);
	पूर्ण अन्यथा अणु
		स_नकल(urb->transfer_buffer + seg->bounce_offs, seg->bounce_buf,
		       seg->bounce_len);
	पूर्ण
	seg->bounce_len = 0;
	seg->bounce_offs = 0;
पूर्ण

अटल पूर्णांक xhci_td_cleanup(काष्ठा xhci_hcd *xhci, काष्ठा xhci_td *td,
			   काष्ठा xhci_ring *ep_ring, पूर्णांक status)
अणु
	काष्ठा urb *urb = शून्य;

	/* Clean up the endpoपूर्णांक's TD list */
	urb = td->urb;

	/* अगर a bounce buffer was used to align this td then unmap it */
	xhci_unmap_td_bounce_buffer(xhci, ep_ring, td);

	/* Do one last check of the actual transfer length.
	 * If the host controller said we transferred more data than the buffer
	 * length, urb->actual_length will be a very big number (since it's
	 * अचिन्हित).  Play it safe and say we didn't transfer anything.
	 */
	अगर (urb->actual_length > urb->transfer_buffer_length) अणु
		xhci_warn(xhci, "URB req %u and actual %u transfer length mismatch\n",
			  urb->transfer_buffer_length, urb->actual_length);
		urb->actual_length = 0;
		status = 0;
	पूर्ण
	/* TD might be हटाओd from td_list अगर we are giving back a cancelled URB */
	अगर (!list_empty(&td->td_list))
		list_del_init(&td->td_list);
	/* Giving back a cancelled URB, or अगर a slated TD completed anyway */
	अगर (!list_empty(&td->cancelled_td_list))
		list_del_init(&td->cancelled_td_list);

	inc_td_cnt(urb);
	/* Giveback the urb when all the tds are completed */
	अगर (last_td_in_urb(td)) अणु
		अगर ((urb->actual_length != urb->transfer_buffer_length &&
		     (urb->transfer_flags & URB_SHORT_NOT_OK)) ||
		    (status != 0 && !usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc)))
			xhci_dbg(xhci, "Giveback URB %p, len = %d, expected = %d, status = %d\n",
				 urb, urb->actual_length,
				 urb->transfer_buffer_length, status);

		/* set isoc urb status to 0 just as EHCI, UHCI, and OHCI */
		अगर (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS)
			status = 0;
		xhci_giveback_urb_in_irq(xhci, td, status);
	पूर्ण

	वापस 0;
पूर्ण


/* Complete the cancelled URBs we unlinked from td_list. */
अटल व्योम xhci_giveback_invalidated_tds(काष्ठा xhci_virt_ep *ep)
अणु
	काष्ठा xhci_ring *ring;
	काष्ठा xhci_td *td, *पंचांगp_td;

	list_क्रम_each_entry_safe(td, पंचांगp_td, &ep->cancelled_td_list,
				 cancelled_td_list) अणु

		ring = xhci_urb_to_transfer_ring(ep->xhci, td->urb);

		अगर (td->cancel_status == TD_CLEARED)
			xhci_td_cleanup(ep->xhci, td, ring, td->status);

		अगर (ep->xhci->xhc_state & XHCI_STATE_DYING)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_reset_halted_ep(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक slot_id,
				अचिन्हित पूर्णांक ep_index, क्रमागत xhci_ep_reset_type reset_type)
अणु
	काष्ठा xhci_command *command;
	पूर्णांक ret = 0;

	command = xhci_alloc_command(xhci, false, GFP_ATOMIC);
	अगर (!command) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ret = xhci_queue_reset_ep(xhci, command, slot_id, ep_index, reset_type);
करोne:
	अगर (ret)
		xhci_err(xhci, "ERROR queuing reset endpoint for slot %d ep_index %d, %d\n",
			 slot_id, ep_index, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक xhci_handle_halted_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
				काष्ठा xhci_virt_ep *ep, अचिन्हित पूर्णांक stream_id,
				काष्ठा xhci_td *td,
				क्रमागत xhci_ep_reset_type reset_type)
अणु
	अचिन्हित पूर्णांक slot_id = ep->vdev->slot_id;
	पूर्णांक err;

	/*
	 * Aव्योम resetting endpoपूर्णांक अगर link is inactive. Can cause host hang.
	 * Device will be reset soon to recover the link so करोn't करो anything
	 */
	अगर (ep->vdev->flags & VDEV_PORT_ERROR)
		वापस -ENODEV;

	/* add td to cancelled list and let reset ep handler take care of it */
	अगर (reset_type == EP_HARD_RESET) अणु
		ep->ep_state |= EP_HARD_CLEAR_TOGGLE;
		अगर (td && list_empty(&td->cancelled_td_list)) अणु
			list_add_tail(&td->cancelled_td_list, &ep->cancelled_td_list);
			td->cancel_status = TD_HALTED;
		पूर्ण
	पूर्ण

	अगर (ep->ep_state & EP_HALTED) अणु
		xhci_dbg(xhci, "Reset ep command already pending\n");
		वापस 0;
	पूर्ण

	err = xhci_reset_halted_ep(xhci, slot_id, ep->ep_index, reset_type);
	अगर (err)
		वापस err;

	ep->ep_state |= EP_HALTED;

	xhci_ring_cmd_db(xhci);

	वापस 0;
पूर्ण

/*
 * Fix up the ep ring first, so HW stops executing cancelled TDs.
 * We have the xHCI lock, so nothing can modअगरy this list until we drop it.
 * We're also in the event handler, so we can't get re-पूर्णांकerrupted अगर another
 * Stop Endpoपूर्णांक command completes.
 *
 * only call this when ring is not in a running state
 */

अटल पूर्णांक xhci_invalidate_cancelled_tds(काष्ठा xhci_virt_ep *ep)
अणु
	काष्ठा xhci_hcd		*xhci;
	काष्ठा xhci_td		*td = शून्य;
	काष्ठा xhci_td		*पंचांगp_td = शून्य;
	काष्ठा xhci_td		*cached_td = शून्य;
	काष्ठा xhci_ring	*ring;
	u64			hw_deq;
	अचिन्हित पूर्णांक		slot_id = ep->vdev->slot_id;
	पूर्णांक			err;

	xhci = ep->xhci;

	list_क्रम_each_entry_safe(td, पंचांगp_td, &ep->cancelled_td_list, cancelled_td_list) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
				"Removing canceled TD starting at 0x%llx (dma).",
				(अचिन्हित दीर्घ दीर्घ)xhci_trb_virt_to_dma(
					td->start_seg, td->first_trb));
		list_del_init(&td->td_list);
		ring = xhci_urb_to_transfer_ring(xhci, td->urb);
		अगर (!ring) अणु
			xhci_warn(xhci, "WARN Cancelled URB %p has invalid stream ID %u.\n",
				  td->urb, td->urb->stream_id);
			जारी;
		पूर्ण
		/*
		 * If a ring stopped on the TD we need to cancel then we have to
		 * move the xHC endpoपूर्णांक ring dequeue poपूर्णांकer past this TD.
		 * Rings halted due to STALL may show hw_deq is past the stalled
		 * TD, but still require a set TR Deq command to flush xHC cache.
		 */
		hw_deq = xhci_get_hw_deq(xhci, ep->vdev, ep->ep_index,
					 td->urb->stream_id);
		hw_deq &= ~0xf;

		अगर (td->cancel_status == TD_HALTED) अणु
			cached_td = td;
		पूर्ण अन्यथा अगर (trb_in_td(xhci, td->start_seg, td->first_trb,
			      td->last_trb, hw_deq, false)) अणु
			चयन (td->cancel_status) अणु
			हाल TD_CLEARED: /* TD is alपढ़ोy no-op */
			हाल TD_CLEARING_CACHE: /* set TR deq command alपढ़ोy queued */
				अवरोध;
			हाल TD_सूचीTY: /* TD is cached, clear it */
			हाल TD_HALTED:
				/* FIXME  stream हाल, several stopped rings */
				cached_td = td;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			td_to_noop(xhci, ring, td, false);
			td->cancel_status = TD_CLEARED;
		पूर्ण
	पूर्ण
	अगर (cached_td) अणु
		cached_td->cancel_status = TD_CLEARING_CACHE;

		err = xhci_move_dequeue_past_td(xhci, slot_id, ep->ep_index,
						cached_td->urb->stream_id,
						cached_td);
		/* Failed to move past cached td, try just setting it noop */
		अगर (err) अणु
			td_to_noop(xhci, ring, cached_td, false);
			cached_td->cancel_status = TD_CLEARED;
		पूर्ण
		cached_td = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Returns the TD the endpoपूर्णांक ring halted on.
 * Only call क्रम non-running rings without streams.
 */
अटल काष्ठा xhci_td *find_halted_td(काष्ठा xhci_virt_ep *ep)
अणु
	काष्ठा xhci_td	*td;
	u64		hw_deq;

	अगर (!list_empty(&ep->ring->td_list)) अणु /* Not streams compatible */
		hw_deq = xhci_get_hw_deq(ep->xhci, ep->vdev, ep->ep_index, 0);
		hw_deq &= ~0xf;
		td = list_first_entry(&ep->ring->td_list, काष्ठा xhci_td, td_list);
		अगर (trb_in_td(ep->xhci, td->start_seg, td->first_trb,
				td->last_trb, hw_deq, false))
			वापस td;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * When we get a command completion क्रम a Stop Endpoपूर्णांक Command, we need to
 * unlink any cancelled TDs from the ring.  There are two ways to करो that:
 *
 *  1. If the HW was in the middle of processing the TD that needs to be
 *     cancelled, then we must move the ring's dequeue poपूर्णांकer past the last TRB
 *     in the TD with a Set Dequeue Poपूर्णांकer Command.
 *  2. Otherwise, we turn all the TRBs in the TD पूर्णांकo No-op TRBs (with the chain
 *     bit cleared) so that the HW will skip over them.
 */
अटल व्योम xhci_handle_cmd_stop_ep(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
				    जोड़ xhci_trb *trb, u32 comp_code)
अणु
	अचिन्हित पूर्णांक ep_index;
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_td *td = शून्य;
	क्रमागत xhci_ep_reset_type reset_type;
	काष्ठा xhci_command *command;
	पूर्णांक err;

	अगर (unlikely(TRB_TO_SUSPEND_PORT(le32_to_cpu(trb->generic.field[3])))) अणु
		अगर (!xhci->devs[slot_id])
			xhci_warn(xhci, "Stop endpoint command completion for disabled slot %u\n",
				  slot_id);
		वापस;
	पूर्ण

	ep_index = TRB_TO_EP_INDEX(le32_to_cpu(trb->generic.field[3]));
	ep = xhci_get_virt_ep(xhci, slot_id, ep_index);
	अगर (!ep)
		वापस;

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);

	trace_xhci_handle_cmd_stop_ep(ep_ctx);

	अगर (comp_code == COMP_CONTEXT_STATE_ERROR) अणु
	/*
	 * If stop endpoपूर्णांक command raced with a halting endpoपूर्णांक we need to
	 * reset the host side endpoपूर्णांक first.
	 * If the TD we halted on isn't cancelled the TD should be given back
	 * with a proper error code, and the ring dequeue moved past the TD.
	 * If streams हाल we can't find hw_deq, or the TD we halted on so करो a
	 * soft reset.
	 *
	 * Proper error code is unknown here, it would be -EPIPE अगर device side
	 * of enadpoit halted (aka STALL), and -EPROTO अगर not (transaction error)
	 * We use -EPROTO, अगर device is stalled it should वापस a stall error on
	 * next transfer, which then will वापस -EPIPE, and device side stall is
	 * noted and cleared by class driver.
	 */
		चयन (GET_EP_CTX_STATE(ep_ctx)) अणु
		हाल EP_STATE_HALTED:
			xhci_dbg(xhci, "Stop ep completion raced with stall, reset ep\n");
			अगर (ep->ep_state & EP_HAS_STREAMS) अणु
				reset_type = EP_SOFT_RESET;
			पूर्ण अन्यथा अणु
				reset_type = EP_HARD_RESET;
				td = find_halted_td(ep);
				अगर (td)
					td->status = -EPROTO;
			पूर्ण
			/* reset ep, reset handler cleans up cancelled tds */
			err = xhci_handle_halted_endpoपूर्णांक(xhci, ep, 0, td,
							  reset_type);
			अगर (err)
				अवरोध;
			xhci_stop_watchकरोg_समयr_in_irq(xhci, ep);
			वापस;
		हाल EP_STATE_RUNNING:
			/* Race, HW handled stop ep cmd beक्रमe ep was running */
			command = xhci_alloc_command(xhci, false, GFP_ATOMIC);
			अगर (!command)
				xhci_stop_watchकरोg_समयr_in_irq(xhci, ep);

			mod_समयr(&ep->stop_cmd_समयr,
				  jअगरfies + XHCI_STOP_EP_CMD_TIMEOUT * HZ);
			xhci_queue_stop_endpoपूर्णांक(xhci, command, slot_id, ep_index, 0);
			xhci_ring_cmd_db(xhci);

			वापस;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	/* will queue a set TR deq अगर stopped on a cancelled, uncleared TD */
	xhci_invalidate_cancelled_tds(ep);
	xhci_stop_watchकरोg_समयr_in_irq(xhci, ep);

	/* Otherwise ring the करोorbell(s) to restart queued transfers */
	xhci_giveback_invalidated_tds(ep);
	ring_करोorbell_क्रम_active_rings(xhci, slot_id, ep_index);
पूर्ण

अटल व्योम xhci_समाप्त_ring_urbs(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring)
अणु
	काष्ठा xhci_td *cur_td;
	काष्ठा xhci_td *पंचांगp;

	list_क्रम_each_entry_safe(cur_td, पंचांगp, &ring->td_list, td_list) अणु
		list_del_init(&cur_td->td_list);

		अगर (!list_empty(&cur_td->cancelled_td_list))
			list_del_init(&cur_td->cancelled_td_list);

		xhci_unmap_td_bounce_buffer(xhci, ring, cur_td);

		inc_td_cnt(cur_td->urb);
		अगर (last_td_in_urb(cur_td))
			xhci_giveback_urb_in_irq(xhci, cur_td, -ESHUTDOWN);
	पूर्ण
पूर्ण

अटल व्योम xhci_समाप्त_endpoपूर्णांक_urbs(काष्ठा xhci_hcd *xhci,
		पूर्णांक slot_id, पूर्णांक ep_index)
अणु
	काष्ठा xhci_td *cur_td;
	काष्ठा xhci_td *पंचांगp;
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_ring *ring;

	ep = &xhci->devs[slot_id]->eps[ep_index];
	अगर ((ep->ep_state & EP_HAS_STREAMS) ||
			(ep->ep_state & EP_GETTING_NO_STREAMS)) अणु
		पूर्णांक stream_id;

		क्रम (stream_id = 1; stream_id < ep->stream_info->num_streams;
				stream_id++) अणु
			ring = ep->stream_info->stream_rings[stream_id];
			अगर (!ring)
				जारी;

			xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
					"Killing URBs for slot ID %u, ep index %u, stream %u",
					slot_id, ep_index, stream_id);
			xhci_समाप्त_ring_urbs(xhci, ring);
		पूर्ण
	पूर्ण अन्यथा अणु
		ring = ep->ring;
		अगर (!ring)
			वापस;
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
				"Killing URBs for slot ID %u, ep index %u",
				slot_id, ep_index);
		xhci_समाप्त_ring_urbs(xhci, ring);
	पूर्ण

	list_क्रम_each_entry_safe(cur_td, पंचांगp, &ep->cancelled_td_list,
			cancelled_td_list) अणु
		list_del_init(&cur_td->cancelled_td_list);
		inc_td_cnt(cur_td->urb);

		अगर (last_td_in_urb(cur_td))
			xhci_giveback_urb_in_irq(xhci, cur_td, -ESHUTDOWN);
	पूर्ण
पूर्ण

/*
 * host controller died, रेजिस्टर पढ़ो वापसs 0xffffffff
 * Complete pending commands, mark them ABORTED.
 * URBs need to be given back as usb core might be रुकोing with device locks
 * held क्रम the URBs to finish during device disconnect, blocking host हटाओ.
 *
 * Call with xhci->lock held.
 * lock is relased and re-acquired जबतक giving back urb.
 */
व्योम xhci_hc_died(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक i, j;

	अगर (xhci->xhc_state & XHCI_STATE_DYING)
		वापस;

	xhci_err(xhci, "xHCI host controller not responding, assume dead\n");
	xhci->xhc_state |= XHCI_STATE_DYING;

	xhci_cleanup_command_queue(xhci);

	/* वापस any pending urbs, हटाओ may be रुकोing क्रम them */
	क्रम (i = 0; i <= HCS_MAX_SLOTS(xhci->hcs_params1); i++) अणु
		अगर (!xhci->devs[i])
			जारी;
		क्रम (j = 0; j < 31; j++)
			xhci_समाप्त_endpoपूर्णांक_urbs(xhci, i, j);
	पूर्ण

	/* inक्रमm usb core hc died अगर PCI हटाओ isn't alपढ़ोy handling it */
	अगर (!(xhci->xhc_state & XHCI_STATE_REMOVING))
		usb_hc_died(xhci_to_hcd(xhci));
पूर्ण

/* Watchकरोg समयr function क्रम when a stop endpoपूर्णांक command fails to complete.
 * In this हाल, we assume the host controller is broken or dying or dead.  The
 * host may still be completing some other events, so we have to be careful to
 * let the event ring handler and the URB dequeueing/enqueueing functions know
 * through xhci->state.
 *
 * The समयr may also fire अगर the host takes a very दीर्घ समय to respond to the
 * command, and the stop endpoपूर्णांक command completion handler cannot delete the
 * समयr beक्रमe the समयr function is called.  Another endpoपूर्णांक cancellation may
 * sneak in beक्रमe the समयr function can grab the lock, and that may queue
 * another stop endpoपूर्णांक command and add the समयr back.  So we cannot use a
 * simple flag to say whether there is a pending stop endpoपूर्णांक command क्रम a
 * particular endpoपूर्णांक.
 *
 * Instead we use a combination of that flag and checking अगर a new समयr is
 * pending.
 */
व्योम xhci_stop_endpoपूर्णांक_command_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा xhci_virt_ep *ep = from_समयr(ep, t, stop_cmd_समयr);
	काष्ठा xhci_hcd *xhci = ep->xhci;
	अचिन्हित दीर्घ flags;
	u32 usbsts;

	spin_lock_irqsave(&xhci->lock, flags);

	/* bail out अगर cmd completed but raced with stop ep watchकरोg समयr.*/
	अगर (!(ep->ep_state & EP_STOP_CMD_PENDING) ||
	    समयr_pending(&ep->stop_cmd_समयr)) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg(xhci, "Stop EP timer raced with cmd completion, exit");
		वापस;
	पूर्ण
	usbsts = पढ़ोl(&xhci->op_regs->status);

	xhci_warn(xhci, "xHCI host not responding to stop endpoint command.\n");
	xhci_warn(xhci, "USBSTS:%s\n", xhci_decode_usbsts(usbsts));

	ep->ep_state &= ~EP_STOP_CMD_PENDING;

	xhci_halt(xhci);

	/*
	 * handle a stop endpoपूर्णांक cmd समयout as अगर host died (-ENODEV).
	 * In the future we could distinguish between -ENODEV and -ETIMEDOUT
	 * and try to recover a -ETIMEDOUT with a host controller reset
	 */
	xhci_hc_died(xhci);

	spin_unlock_irqrestore(&xhci->lock, flags);
	xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
			"xHCI host controller is dead.");
पूर्ण

अटल व्योम update_ring_क्रम_set_deq_completion(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *dev,
		काष्ठा xhci_ring *ep_ring,
		अचिन्हित पूर्णांक ep_index)
अणु
	जोड़ xhci_trb *dequeue_temp;
	पूर्णांक num_trbs_मुक्त_temp;
	bool revert = false;

	num_trbs_मुक्त_temp = ep_ring->num_trbs_मुक्त;
	dequeue_temp = ep_ring->dequeue;

	/* If we get two back-to-back stalls, and the first stalled transfer
	 * ends just beक्रमe a link TRB, the dequeue poपूर्णांकer will be left on
	 * the link TRB by the code in the जबतक loop.  So we have to update
	 * the dequeue poपूर्णांकer one segment further, or we'll jump off
	 * the segment पूर्णांकo la-la-land.
	 */
	अगर (trb_is_link(ep_ring->dequeue)) अणु
		ep_ring->deq_seg = ep_ring->deq_seg->next;
		ep_ring->dequeue = ep_ring->deq_seg->trbs;
	पूर्ण

	जबतक (ep_ring->dequeue != dev->eps[ep_index].queued_deq_ptr) अणु
		/* We have more usable TRBs */
		ep_ring->num_trbs_मुक्त++;
		ep_ring->dequeue++;
		अगर (trb_is_link(ep_ring->dequeue)) अणु
			अगर (ep_ring->dequeue ==
					dev->eps[ep_index].queued_deq_ptr)
				अवरोध;
			ep_ring->deq_seg = ep_ring->deq_seg->next;
			ep_ring->dequeue = ep_ring->deq_seg->trbs;
		पूर्ण
		अगर (ep_ring->dequeue == dequeue_temp) अणु
			revert = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (revert) अणु
		xhci_dbg(xhci, "Unable to find new dequeue pointer\n");
		ep_ring->num_trbs_मुक्त = num_trbs_मुक्त_temp;
	पूर्ण
पूर्ण

/*
 * When we get a completion क्रम a Set Transfer Ring Dequeue Poपूर्णांकer command,
 * we need to clear the set deq pending flag in the endpoपूर्णांक ring state, so that
 * the TD queueing code can ring the करोorbell again.  We also need to ring the
 * endpoपूर्णांक करोorbell to restart the ring, but only अगर there aren't more
 * cancellations pending.
 */
अटल व्योम xhci_handle_cmd_set_deq(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
		जोड़ xhci_trb *trb, u32 cmd_comp_code)
अणु
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित पूर्णांक stream_id;
	काष्ठा xhci_ring *ep_ring;
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_slot_ctx *slot_ctx;
	काष्ठा xhci_td *td, *पंचांगp_td;

	ep_index = TRB_TO_EP_INDEX(le32_to_cpu(trb->generic.field[3]));
	stream_id = TRB_TO_STREAM_ID(le32_to_cpu(trb->generic.field[2]));
	ep = xhci_get_virt_ep(xhci, slot_id, ep_index);
	अगर (!ep)
		वापस;

	ep_ring = xhci_virt_ep_to_ring(xhci, ep, stream_id);
	अगर (!ep_ring) अणु
		xhci_warn(xhci, "WARN Set TR deq ptr command for freed stream ID %u\n",
				stream_id);
		/* XXX: Harmless??? */
		जाओ cleanup;
	पूर्ण

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);
	slot_ctx = xhci_get_slot_ctx(xhci, ep->vdev->out_ctx);
	trace_xhci_handle_cmd_set_deq(slot_ctx);
	trace_xhci_handle_cmd_set_deq_ep(ep_ctx);

	अगर (cmd_comp_code != COMP_SUCCESS) अणु
		अचिन्हित पूर्णांक ep_state;
		अचिन्हित पूर्णांक slot_state;

		चयन (cmd_comp_code) अणु
		हाल COMP_TRB_ERROR:
			xhci_warn(xhci, "WARN Set TR Deq Ptr cmd invalid because of stream ID configuration\n");
			अवरोध;
		हाल COMP_CONTEXT_STATE_ERROR:
			xhci_warn(xhci, "WARN Set TR Deq Ptr cmd failed due to incorrect slot or ep state.\n");
			ep_state = GET_EP_CTX_STATE(ep_ctx);
			slot_state = le32_to_cpu(slot_ctx->dev_state);
			slot_state = GET_SLOT_STATE(slot_state);
			xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
					"Slot state = %u, EP state = %u",
					slot_state, ep_state);
			अवरोध;
		हाल COMP_SLOT_NOT_ENABLED_ERROR:
			xhci_warn(xhci, "WARN Set TR Deq Ptr cmd failed because slot %u was not enabled.\n",
					slot_id);
			अवरोध;
		शेष:
			xhci_warn(xhci, "WARN Set TR Deq Ptr cmd with unknown completion code of %u.\n",
					cmd_comp_code);
			अवरोध;
		पूर्ण
		/* OK what करो we करो now?  The endpoपूर्णांक state is hosed, and we
		 * should never get to this poपूर्णांक अगर the synchronization between
		 * queueing, and endpoपूर्णांक state are correct.  This might happen
		 * अगर the device माला_लो disconnected after we've finished
		 * cancelling URBs, which might not be an error...
		 */
	पूर्ण अन्यथा अणु
		u64 deq;
		/* 4.6.10 deq ptr is written to the stream ctx क्रम streams */
		अगर (ep->ep_state & EP_HAS_STREAMS) अणु
			काष्ठा xhci_stream_ctx *ctx =
				&ep->stream_info->stream_ctx_array[stream_id];
			deq = le64_to_cpu(ctx->stream_ring) & SCTX_DEQ_MASK;
		पूर्ण अन्यथा अणु
			deq = le64_to_cpu(ep_ctx->deq) & ~EP_CTX_CYCLE_MASK;
		पूर्ण
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
			"Successful Set TR Deq Ptr cmd, deq = @%08llx", deq);
		अगर (xhci_trb_virt_to_dma(ep->queued_deq_seg,
					 ep->queued_deq_ptr) == deq) अणु
			/* Update the ring's dequeue segment and dequeue poपूर्णांकer
			 * to reflect the new position.
			 */
			update_ring_क्रम_set_deq_completion(xhci, ep->vdev,
				ep_ring, ep_index);
		पूर्ण अन्यथा अणु
			xhci_warn(xhci, "Mismatch between completed Set TR Deq Ptr command & xHCI internal state.\n");
			xhci_warn(xhci, "ep deq seg = %p, deq ptr = %p\n",
				  ep->queued_deq_seg, ep->queued_deq_ptr);
		पूर्ण
	पूर्ण
	/* HW cached TDs cleared from cache, give them back */
	list_क्रम_each_entry_safe(td, पंचांगp_td, &ep->cancelled_td_list,
				 cancelled_td_list) अणु
		ep_ring = xhci_urb_to_transfer_ring(ep->xhci, td->urb);
		अगर (td->cancel_status == TD_CLEARING_CACHE) अणु
			td->cancel_status = TD_CLEARED;
			xhci_td_cleanup(ep->xhci, td, ep_ring, td->status);
		पूर्ण
	पूर्ण
cleanup:
	ep->ep_state &= ~SET_DEQ_PENDING;
	ep->queued_deq_seg = शून्य;
	ep->queued_deq_ptr = शून्य;
	/* Restart any rings with pending URBs */
	ring_करोorbell_क्रम_active_rings(xhci, slot_id, ep_index);
पूर्ण

अटल व्योम xhci_handle_cmd_reset_ep(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
		जोड़ xhci_trb *trb, u32 cmd_comp_code)
अणु
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_ep_ctx *ep_ctx;
	अचिन्हित पूर्णांक ep_index;

	ep_index = TRB_TO_EP_INDEX(le32_to_cpu(trb->generic.field[3]));
	ep = xhci_get_virt_ep(xhci, slot_id, ep_index);
	अगर (!ep)
		वापस;

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);
	trace_xhci_handle_cmd_reset_ep(ep_ctx);

	/* This command will only fail अगर the endpoपूर्णांक wasn't halted,
	 * but we करोn't care.
	 */
	xhci_dbg_trace(xhci, trace_xhci_dbg_reset_ep,
		"Ignoring reset ep completion code of %u", cmd_comp_code);

	/* Cleanup cancelled TDs as ep is stopped. May queue a Set TR Deq cmd */
	xhci_invalidate_cancelled_tds(ep);

	अगर (xhci->quirks & XHCI_RESET_EP_QUIRK)
		xhci_dbg(xhci, "Note: Removed workaround to queue config ep for this hw");
	/* Clear our पूर्णांकernal halted state */
	ep->ep_state &= ~EP_HALTED;

	xhci_giveback_invalidated_tds(ep);

	/* अगर this was a soft reset, then restart */
	अगर ((le32_to_cpu(trb->generic.field[3])) & TRB_TSP)
		ring_करोorbell_क्रम_active_rings(xhci, slot_id, ep_index);
पूर्ण

अटल व्योम xhci_handle_cmd_enable_slot(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
		काष्ठा xhci_command *command, u32 cmd_comp_code)
अणु
	अगर (cmd_comp_code == COMP_SUCCESS)
		command->slot_id = slot_id;
	अन्यथा
		command->slot_id = 0;
पूर्ण

अटल व्योम xhci_handle_cmd_disable_slot(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_slot_ctx *slot_ctx;

	virt_dev = xhci->devs[slot_id];
	अगर (!virt_dev)
		वापस;

	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->out_ctx);
	trace_xhci_handle_cmd_disable_slot(slot_ctx);

	अगर (xhci->quirks & XHCI_EP_LIMIT_QUIRK)
		/* Delete शेष control endpoपूर्णांक resources */
		xhci_मुक्त_device_endpoपूर्णांक_resources(xhci, virt_dev, true);
	xhci_मुक्त_virt_device(xhci, slot_id);
पूर्ण

अटल व्योम xhci_handle_cmd_config_ep(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
		u32 cmd_comp_code)
अणु
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_ep_ctx *ep_ctx;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित पूर्णांक ep_state;
	u32 add_flags, drop_flags;

	/*
	 * Configure endpoपूर्णांक commands can come from the USB core
	 * configuration or alt setting changes, or because the HW
	 * needed an extra configure endpoपूर्णांक command after a reset
	 * endpoपूर्णांक command or streams were being configured.
	 * If the command was क्रम a halted endpoपूर्णांक, the xHCI driver
	 * is not रुकोing on the configure endpoपूर्णांक command.
	 */
	virt_dev = xhci->devs[slot_id];
	अगर (!virt_dev)
		वापस;
	ctrl_ctx = xhci_get_input_control_ctx(virt_dev->in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "Could not get input context, bad type.\n");
		वापस;
	पूर्ण

	add_flags = le32_to_cpu(ctrl_ctx->add_flags);
	drop_flags = le32_to_cpu(ctrl_ctx->drop_flags);
	/* Input ctx add_flags are the endpoपूर्णांक index plus one */
	ep_index = xhci_last_valid_endpoपूर्णांक(add_flags) - 1;

	ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->out_ctx, ep_index);
	trace_xhci_handle_cmd_config_ep(ep_ctx);

	/* A usb_set_पूर्णांकerface() call directly after clearing a halted
	 * condition may race on this quirky hardware.  Not worth
	 * worrying about, since this is prototype hardware.  Not sure
	 * अगर this will work क्रम streams, but streams support was
	 * untested on this prototype.
	 */
	अगर (xhci->quirks & XHCI_RESET_EP_QUIRK &&
			ep_index != (अचिन्हित पूर्णांक) -1 &&
			add_flags - SLOT_FLAG == drop_flags) अणु
		ep_state = virt_dev->eps[ep_index].ep_state;
		अगर (!(ep_state & EP_HALTED))
			वापस;
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Completed config ep cmd - "
				"last ep index = %d, state = %d",
				ep_index, ep_state);
		/* Clear पूर्णांकernal halted state and restart ring(s) */
		virt_dev->eps[ep_index].ep_state &= ~EP_HALTED;
		ring_करोorbell_क्रम_active_rings(xhci, slot_id, ep_index);
		वापस;
	पूर्ण
	वापस;
पूर्ण

अटल व्योम xhci_handle_cmd_addr_dev(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_slot_ctx *slot_ctx;

	vdev = xhci->devs[slot_id];
	अगर (!vdev)
		वापस;
	slot_ctx = xhci_get_slot_ctx(xhci, vdev->out_ctx);
	trace_xhci_handle_cmd_addr_dev(slot_ctx);
पूर्ण

अटल व्योम xhci_handle_cmd_reset_dev(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_slot_ctx *slot_ctx;

	vdev = xhci->devs[slot_id];
	अगर (!vdev) अणु
		xhci_warn(xhci, "Reset device command completion for disabled slot %u\n",
			  slot_id);
		वापस;
	पूर्ण
	slot_ctx = xhci_get_slot_ctx(xhci, vdev->out_ctx);
	trace_xhci_handle_cmd_reset_dev(slot_ctx);

	xhci_dbg(xhci, "Completed reset device command.\n");
पूर्ण

अटल व्योम xhci_handle_cmd_nec_get_fw(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_event_cmd *event)
अणु
	अगर (!(xhci->quirks & XHCI_NEC_HOST)) अणु
		xhci_warn(xhci, "WARN NEC_GET_FW command on non-NEC host\n");
		वापस;
	पूर्ण
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"NEC firmware version %2x.%02x",
			NEC_FW_MAJOR(le32_to_cpu(event->status)),
			NEC_FW_MINOR(le32_to_cpu(event->status)));
पूर्ण

अटल व्योम xhci_complete_del_and_मुक्त_cmd(काष्ठा xhci_command *cmd, u32 status)
अणु
	list_del(&cmd->cmd_list);

	अगर (cmd->completion) अणु
		cmd->status = status;
		complete(cmd->completion);
	पूर्ण अन्यथा अणु
		kमुक्त(cmd);
	पूर्ण
पूर्ण

व्योम xhci_cleanup_command_queue(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_command *cur_cmd, *पंचांगp_cmd;
	xhci->current_cmd = शून्य;
	list_क्रम_each_entry_safe(cur_cmd, पंचांगp_cmd, &xhci->cmd_list, cmd_list)
		xhci_complete_del_and_मुक्त_cmd(cur_cmd, COMP_COMMAND_ABORTED);
पूर्ण

व्योम xhci_handle_command_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xhci_hcd *xhci;
	अचिन्हित दीर्घ flags;
	u64 hw_ring_state;

	xhci = container_of(to_delayed_work(work), काष्ठा xhci_hcd, cmd_समयr);

	spin_lock_irqsave(&xhci->lock, flags);

	/*
	 * If समयout work is pending, or current_cmd is शून्य, it means we
	 * raced with command completion. Command is handled so just वापस.
	 */
	अगर (!xhci->current_cmd || delayed_work_pending(&xhci->cmd_समयr)) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस;
	पूर्ण
	/* mark this command to be cancelled */
	xhci->current_cmd->status = COMP_COMMAND_ABORTED;

	/* Make sure command ring is running beक्रमe पातing it */
	hw_ring_state = xhci_पढ़ो_64(xhci, &xhci->op_regs->cmd_ring);
	अगर (hw_ring_state == ~(u64)0) अणु
		xhci_hc_died(xhci);
		जाओ समय_out_completed;
	पूर्ण

	अगर ((xhci->cmd_ring_state & CMD_RING_STATE_RUNNING) &&
	    (hw_ring_state & CMD_RING_RUNNING))  अणु
		/* Prevent new करोorbell, and start command पात */
		xhci->cmd_ring_state = CMD_RING_STATE_ABORTED;
		xhci_dbg(xhci, "Command timeout\n");
		xhci_पात_cmd_ring(xhci, flags);
		जाओ समय_out_completed;
	पूर्ण

	/* host हटाओd. Bail out */
	अगर (xhci->xhc_state & XHCI_STATE_REMOVING) अणु
		xhci_dbg(xhci, "host removed, ring start fail?\n");
		xhci_cleanup_command_queue(xhci);

		जाओ समय_out_completed;
	पूर्ण

	/* command समयout on stopped ring, ring can't be पातed */
	xhci_dbg(xhci, "Command timeout on stopped ring\n");
	xhci_handle_stopped_cmd_ring(xhci, xhci->current_cmd);

समय_out_completed:
	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस;
पूर्ण

अटल व्योम handle_cmd_completion(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_event_cmd *event)
अणु
	अचिन्हित पूर्णांक slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->flags));
	u64 cmd_dma;
	dma_addr_t cmd_dequeue_dma;
	u32 cmd_comp_code;
	जोड़ xhci_trb *cmd_trb;
	काष्ठा xhci_command *cmd;
	u32 cmd_type;

	अगर (slot_id >= MAX_HC_SLOTS) अणु
		xhci_warn(xhci, "Invalid slot_id %u\n", slot_id);
		वापस;
	पूर्ण

	cmd_dma = le64_to_cpu(event->cmd_trb);
	cmd_trb = xhci->cmd_ring->dequeue;

	trace_xhci_handle_command(xhci->cmd_ring, &cmd_trb->generic);

	cmd_dequeue_dma = xhci_trb_virt_to_dma(xhci->cmd_ring->deq_seg,
			cmd_trb);
	/*
	 * Check whether the completion event is क्रम our पूर्णांकernal kept
	 * command.
	 */
	अगर (!cmd_dequeue_dma || cmd_dma != (u64)cmd_dequeue_dma) अणु
		xhci_warn(xhci,
			  "ERROR mismatched command completion event\n");
		वापस;
	पूर्ण

	cmd = list_first_entry(&xhci->cmd_list, काष्ठा xhci_command, cmd_list);

	cancel_delayed_work(&xhci->cmd_समयr);

	cmd_comp_code = GET_COMP_CODE(le32_to_cpu(event->status));

	/* If CMD ring stopped we own the trbs between enqueue and dequeue */
	अगर (cmd_comp_code == COMP_COMMAND_RING_STOPPED) अणु
		complete_all(&xhci->cmd_ring_stop_completion);
		वापस;
	पूर्ण

	अगर (cmd->command_trb != xhci->cmd_ring->dequeue) अणु
		xhci_err(xhci,
			 "Command completion event does not match command\n");
		वापस;
	पूर्ण

	/*
	 * Host पातed the command ring, check अगर the current command was
	 * supposed to be पातed, otherwise जारी normally.
	 * The command ring is stopped now, but the xHC will issue a Command
	 * Ring Stopped event which will cause us to restart it.
	 */
	अगर (cmd_comp_code == COMP_COMMAND_ABORTED) अणु
		xhci->cmd_ring_state = CMD_RING_STATE_STOPPED;
		अगर (cmd->status == COMP_COMMAND_ABORTED) अणु
			अगर (xhci->current_cmd == cmd)
				xhci->current_cmd = शून्य;
			जाओ event_handled;
		पूर्ण
	पूर्ण

	cmd_type = TRB_FIELD_TO_TYPE(le32_to_cpu(cmd_trb->generic.field[3]));
	चयन (cmd_type) अणु
	हाल TRB_ENABLE_SLOT:
		xhci_handle_cmd_enable_slot(xhci, slot_id, cmd, cmd_comp_code);
		अवरोध;
	हाल TRB_DISABLE_SLOT:
		xhci_handle_cmd_disable_slot(xhci, slot_id);
		अवरोध;
	हाल TRB_CONFIG_EP:
		अगर (!cmd->completion)
			xhci_handle_cmd_config_ep(xhci, slot_id, cmd_comp_code);
		अवरोध;
	हाल TRB_EVAL_CONTEXT:
		अवरोध;
	हाल TRB_ADDR_DEV:
		xhci_handle_cmd_addr_dev(xhci, slot_id);
		अवरोध;
	हाल TRB_STOP_RING:
		WARN_ON(slot_id != TRB_TO_SLOT_ID(
				le32_to_cpu(cmd_trb->generic.field[3])));
		अगर (!cmd->completion)
			xhci_handle_cmd_stop_ep(xhci, slot_id, cmd_trb,
						cmd_comp_code);
		अवरोध;
	हाल TRB_SET_DEQ:
		WARN_ON(slot_id != TRB_TO_SLOT_ID(
				le32_to_cpu(cmd_trb->generic.field[3])));
		xhci_handle_cmd_set_deq(xhci, slot_id, cmd_trb, cmd_comp_code);
		अवरोध;
	हाल TRB_CMD_NOOP:
		/* Is this an पातed command turned to NO-OP? */
		अगर (cmd->status == COMP_COMMAND_RING_STOPPED)
			cmd_comp_code = COMP_COMMAND_RING_STOPPED;
		अवरोध;
	हाल TRB_RESET_EP:
		WARN_ON(slot_id != TRB_TO_SLOT_ID(
				le32_to_cpu(cmd_trb->generic.field[3])));
		xhci_handle_cmd_reset_ep(xhci, slot_id, cmd_trb, cmd_comp_code);
		अवरोध;
	हाल TRB_RESET_DEV:
		/* SLOT_ID field in reset device cmd completion event TRB is 0.
		 * Use the SLOT_ID from the command TRB instead (xhci 4.6.11)
		 */
		slot_id = TRB_TO_SLOT_ID(
				le32_to_cpu(cmd_trb->generic.field[3]));
		xhci_handle_cmd_reset_dev(xhci, slot_id);
		अवरोध;
	हाल TRB_NEC_GET_FW:
		xhci_handle_cmd_nec_get_fw(xhci, event);
		अवरोध;
	शेष:
		/* Skip over unknown commands on the event ring */
		xhci_info(xhci, "INFO unknown command type %d\n", cmd_type);
		अवरोध;
	पूर्ण

	/* restart समयr अगर this wasn't the last command */
	अगर (!list_is_singular(&xhci->cmd_list)) अणु
		xhci->current_cmd = list_first_entry(&cmd->cmd_list,
						काष्ठा xhci_command, cmd_list);
		xhci_mod_cmd_समयr(xhci, XHCI_CMD_DEFAULT_TIMEOUT);
	पूर्ण अन्यथा अगर (xhci->current_cmd == cmd) अणु
		xhci->current_cmd = शून्य;
	पूर्ण

event_handled:
	xhci_complete_del_and_मुक्त_cmd(cmd, cmd_comp_code);

	inc_deq(xhci, xhci->cmd_ring);
पूर्ण

अटल व्योम handle_venकरोr_event(काष्ठा xhci_hcd *xhci,
				जोड़ xhci_trb *event, u32 trb_type)
अणु
	xhci_dbg(xhci, "Vendor specific event TRB type = %u\n", trb_type);
	अगर (trb_type == TRB_NEC_CMD_COMP && (xhci->quirks & XHCI_NEC_HOST))
		handle_cmd_completion(xhci, &event->event_cmd);
पूर्ण

अटल व्योम handle_device_notअगरication(काष्ठा xhci_hcd *xhci,
		जोड़ xhci_trb *event)
अणु
	u32 slot_id;
	काष्ठा usb_device *udev;

	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->generic.field[3]));
	अगर (!xhci->devs[slot_id]) अणु
		xhci_warn(xhci, "Device Notification event for "
				"unused slot %u\n", slot_id);
		वापस;
	पूर्ण

	xhci_dbg(xhci, "Device Wake Notification event for slot ID %u\n",
			slot_id);
	udev = xhci->devs[slot_id]->udev;
	अगर (udev && udev->parent)
		usb_wakeup_notअगरication(udev->parent, udev->portnum);
पूर्ण

/*
 * Quirk hanlder क्रम errata seen on Cavium ThunderX2 processor XHCI
 * Controller.
 * As per ThunderX2errata-129 USB 2 device may come up as USB 1
 * If a connection to a USB 1 device is followed by another connection
 * to a USB 2 device.
 *
 * Reset the PHY after the USB device is disconnected अगर device speed
 * is less than HCD_USB3.
 * Retry the reset sequence max of 4 बार checking the PLL lock status.
 *
 */
अटल व्योम xhci_cavium_reset_phy_quirk(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा usb_hcd *hcd = xhci_to_hcd(xhci);
	u32 pll_lock_check;
	u32 retry_count = 4;

	करो अणु
		/* Assert PHY reset */
		ग_लिखोl(0x6F, hcd->regs + 0x1048);
		udelay(10);
		/* De-निश्चित the PHY reset */
		ग_लिखोl(0x7F, hcd->regs + 0x1048);
		udelay(200);
		pll_lock_check = पढ़ोl(hcd->regs + 0x1070);
	पूर्ण जबतक (!(pll_lock_check & 0x1) && --retry_count);
पूर्ण

अटल व्योम handle_port_status(काष्ठा xhci_hcd *xhci,
		जोड़ xhci_trb *event)
अणु
	काष्ठा usb_hcd *hcd;
	u32 port_id;
	u32 portsc, cmd_reg;
	पूर्णांक max_ports;
	पूर्णांक slot_id;
	अचिन्हित पूर्णांक hcd_portnum;
	काष्ठा xhci_bus_state *bus_state;
	bool bogus_port_status = false;
	काष्ठा xhci_port *port;

	/* Port status change events always have a successful completion code */
	अगर (GET_COMP_CODE(le32_to_cpu(event->generic.field[2])) != COMP_SUCCESS)
		xhci_warn(xhci,
			  "WARN: xHC returned failed port status event\n");

	port_id = GET_PORT_ID(le32_to_cpu(event->generic.field[0]));
	max_ports = HCS_MAX_PORTS(xhci->hcs_params1);

	अगर ((port_id <= 0) || (port_id > max_ports)) अणु
		xhci_warn(xhci, "Port change event with invalid port ID %d\n",
			  port_id);
		inc_deq(xhci, xhci->event_ring);
		वापस;
	पूर्ण

	port = &xhci->hw_ports[port_id - 1];
	अगर (!port || !port->rhub || port->hcd_portnum == DUPLICATE_ENTRY) अणु
		xhci_warn(xhci, "Port change event, no port for port ID %u\n",
			  port_id);
		bogus_port_status = true;
		जाओ cleanup;
	पूर्ण

	/* We might get पूर्णांकerrupts after shared_hcd is हटाओd */
	अगर (port->rhub == &xhci->usb3_rhub && xhci->shared_hcd == शून्य) अणु
		xhci_dbg(xhci, "ignore port event for removed USB3 hcd\n");
		bogus_port_status = true;
		जाओ cleanup;
	पूर्ण

	hcd = port->rhub->hcd;
	bus_state = &port->rhub->bus_state;
	hcd_portnum = port->hcd_portnum;
	portsc = पढ़ोl(port->addr);

	xhci_dbg(xhci, "Port change event, %d-%d, id %d, portsc: 0x%x\n",
		 hcd->self.busnum, hcd_portnum + 1, port_id, portsc);

	trace_xhci_handle_port_status(hcd_portnum, portsc);

	अगर (hcd->state == HC_STATE_SUSPENDED) अणु
		xhci_dbg(xhci, "resume root hub\n");
		usb_hcd_resume_root_hub(hcd);
	पूर्ण

	अगर (hcd->speed >= HCD_USB3 &&
	    (portsc & PORT_PLS_MASK) == XDEV_INACTIVE) अणु
		slot_id = xhci_find_slot_id_by_port(hcd, xhci, hcd_portnum + 1);
		अगर (slot_id && xhci->devs[slot_id])
			xhci->devs[slot_id]->flags |= VDEV_PORT_ERROR;
	पूर्ण

	अगर ((portsc & PORT_PLC) && (portsc & PORT_PLS_MASK) == XDEV_RESUME) अणु
		xhci_dbg(xhci, "port resume event for port %d\n", port_id);

		cmd_reg = पढ़ोl(&xhci->op_regs->command);
		अगर (!(cmd_reg & CMD_RUN)) अणु
			xhci_warn(xhci, "xHC is not running.\n");
			जाओ cleanup;
		पूर्ण

		अगर (DEV_SUPERSPEED_ANY(portsc)) अणु
			xhci_dbg(xhci, "remote wake SS port %d\n", port_id);
			/* Set a flag to say the port संकेतed remote wakeup,
			 * so we can tell the dअगरference between the end of
			 * device and host initiated resume.
			 */
			bus_state->port_remote_wakeup |= 1 << hcd_portnum;
			xhci_test_and_clear_bit(xhci, port, PORT_PLC);
			usb_hcd_start_port_resume(&hcd->self, hcd_portnum);
			xhci_set_link_state(xhci, port, XDEV_U0);
			/* Need to रुको until the next link state change
			 * indicates the device is actually in U0.
			 */
			bogus_port_status = true;
			जाओ cleanup;
		पूर्ण अन्यथा अगर (!test_bit(hcd_portnum, &bus_state->resuming_ports)) अणु
			xhci_dbg(xhci, "resume HS port %d\n", port_id);
			bus_state->resume_करोne[hcd_portnum] = jअगरfies +
				msecs_to_jअगरfies(USB_RESUME_TIMEOUT);
			set_bit(hcd_portnum, &bus_state->resuming_ports);
			/* Do the rest in GetPortStatus after resume समय delay.
			 * Aव्योम polling roothub status beक्रमe that so that a
			 * usb device स्वतः-resume latency around ~40ms.
			 */
			set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
			mod_समयr(&hcd->rh_समयr,
				  bus_state->resume_करोne[hcd_portnum]);
			usb_hcd_start_port_resume(&hcd->self, hcd_portnum);
			bogus_port_status = true;
		पूर्ण
	पूर्ण

	अगर ((portsc & PORT_PLC) &&
	    DEV_SUPERSPEED_ANY(portsc) &&
	    ((portsc & PORT_PLS_MASK) == XDEV_U0 ||
	     (portsc & PORT_PLS_MASK) == XDEV_U1 ||
	     (portsc & PORT_PLS_MASK) == XDEV_U2)) अणु
		xhci_dbg(xhci, "resume SS port %d finished\n", port_id);
		complete(&bus_state->u3निकास_करोne[hcd_portnum]);
		/* We've just brought the device पूर्णांकo U0/1/2 through either the
		 * Resume state after a device remote wakeup, or through the
		 * U3Exit state after a host-initiated resume.  If it's a device
		 * initiated remote wake, करोn't pass up the link state change,
		 * so the roothub behavior is consistent with बाह्यal
		 * USB 3.0 hub behavior.
		 */
		slot_id = xhci_find_slot_id_by_port(hcd, xhci, hcd_portnum + 1);
		अगर (slot_id && xhci->devs[slot_id])
			xhci_ring_device(xhci, slot_id);
		अगर (bus_state->port_remote_wakeup & (1 << hcd_portnum)) अणु
			xhci_test_and_clear_bit(xhci, port, PORT_PLC);
			usb_wakeup_notअगरication(hcd->self.root_hub,
					hcd_portnum + 1);
			bogus_port_status = true;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Check to see अगर xhci-hub.c is रुकोing on RExit to U0 transition (or
	 * RExit to a disconnect state).  If so, let the the driver know it's
	 * out of the RExit state.
	 */
	अगर (!DEV_SUPERSPEED_ANY(portsc) && hcd->speed < HCD_USB3 &&
			test_and_clear_bit(hcd_portnum,
				&bus_state->rनिकास_ports)) अणु
		complete(&bus_state->rनिकास_करोne[hcd_portnum]);
		bogus_port_status = true;
		जाओ cleanup;
	पूर्ण

	अगर (hcd->speed < HCD_USB3) अणु
		xhci_test_and_clear_bit(xhci, port, PORT_PLC);
		अगर ((xhci->quirks & XHCI_RESET_PLL_ON_DISCONNECT) &&
		    (portsc & PORT_CSC) && !(portsc & PORT_CONNECT))
			xhci_cavium_reset_phy_quirk(xhci);
	पूर्ण

cleanup:
	/* Update event ring dequeue poपूर्णांकer beक्रमe dropping the lock */
	inc_deq(xhci, xhci->event_ring);

	/* Don't make the USB core poll the roothub अगर we got a bad port status
	 * change event.  Besides, at that poपूर्णांक we can't tell which roothub
	 * (USB 2.0 or USB 3.0) to kick.
	 */
	अगर (bogus_port_status)
		वापस;

	/*
	 * xHCI port-status-change events occur when the "or" of all the
	 * status-change bits in the portsc रेजिस्टर changes from 0 to 1.
	 * New status changes won't cause an event अगर any other change
	 * bits are still set.  When an event occurs, चयन over to
	 * polling to aव्योम losing status changes.
	 */
	xhci_dbg(xhci, "%s: starting port polling.\n", __func__);
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	spin_unlock(&xhci->lock);
	/* Pass this up to the core */
	usb_hcd_poll_rh_status(hcd);
	spin_lock(&xhci->lock);
पूर्ण

/*
 * This TD is defined by the TRBs starting at start_trb in start_seg and ending
 * at end_trb, which may be in another segment.  If the suspect DMA address is a
 * TRB in this TD, this function वापसs that TRB's segment.  Otherwise it
 * वापसs 0.
 */
काष्ठा xhci_segment *trb_in_td(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_segment *start_seg,
		जोड़ xhci_trb	*start_trb,
		जोड़ xhci_trb	*end_trb,
		dma_addr_t	suspect_dma,
		bool		debug)
अणु
	dma_addr_t start_dma;
	dma_addr_t end_seg_dma;
	dma_addr_t end_trb_dma;
	काष्ठा xhci_segment *cur_seg;

	start_dma = xhci_trb_virt_to_dma(start_seg, start_trb);
	cur_seg = start_seg;

	करो अणु
		अगर (start_dma == 0)
			वापस शून्य;
		/* We may get an event क्रम a Link TRB in the middle of a TD */
		end_seg_dma = xhci_trb_virt_to_dma(cur_seg,
				&cur_seg->trbs[TRBS_PER_SEGMENT - 1]);
		/* If the end TRB isn't in this segment, this is set to 0 */
		end_trb_dma = xhci_trb_virt_to_dma(cur_seg, end_trb);

		अगर (debug)
			xhci_warn(xhci,
				"Looking for event-dma %016llx trb-start %016llx trb-end %016llx seg-start %016llx seg-end %016llx\n",
				(अचिन्हित दीर्घ दीर्घ)suspect_dma,
				(अचिन्हित दीर्घ दीर्घ)start_dma,
				(अचिन्हित दीर्घ दीर्घ)end_trb_dma,
				(अचिन्हित दीर्घ दीर्घ)cur_seg->dma,
				(अचिन्हित दीर्घ दीर्घ)end_seg_dma);

		अगर (end_trb_dma > 0) अणु
			/* The end TRB is in this segment, so suspect should be here */
			अगर (start_dma <= end_trb_dma) अणु
				अगर (suspect_dma >= start_dma && suspect_dma <= end_trb_dma)
					वापस cur_seg;
			पूर्ण अन्यथा अणु
				/* Case क्रम one segment with
				 * a TD wrapped around to the top
				 */
				अगर ((suspect_dma >= start_dma &&
							suspect_dma <= end_seg_dma) ||
						(suspect_dma >= cur_seg->dma &&
						 suspect_dma <= end_trb_dma))
					वापस cur_seg;
			पूर्ण
			वापस शून्य;
		पूर्ण अन्यथा अणु
			/* Might still be somewhere in this segment */
			अगर (suspect_dma >= start_dma && suspect_dma <= end_seg_dma)
				वापस cur_seg;
		पूर्ण
		cur_seg = cur_seg->next;
		start_dma = xhci_trb_virt_to_dma(cur_seg, &cur_seg->trbs[0]);
	पूर्ण जबतक (cur_seg != start_seg);

	वापस शून्य;
पूर्ण

अटल व्योम xhci_clear_hub_tt_buffer(काष्ठा xhci_hcd *xhci, काष्ठा xhci_td *td,
		काष्ठा xhci_virt_ep *ep)
अणु
	/*
	 * As part of low/full-speed endpoपूर्णांक-halt processing
	 * we must clear the TT buffer (USB 2.0 specअगरication 11.17.5).
	 */
	अगर (td->urb->dev->tt && !usb_pipeपूर्णांक(td->urb->pipe) &&
	    (td->urb->dev->tt->hub != xhci_to_hcd(xhci)->self.root_hub) &&
	    !(ep->ep_state & EP_CLEARING_TT)) अणु
		ep->ep_state |= EP_CLEARING_TT;
		td->urb->ep->hcpriv = td->urb->dev;
		अगर (usb_hub_clear_tt_buffer(td->urb))
			ep->ep_state &= ~EP_CLEARING_TT;
	पूर्ण
पूर्ण

/* Check अगर an error has halted the endpoपूर्णांक ring.  The class driver will
 * cleanup the halt क्रम a non-शेष control endpoपूर्णांक अगर we indicate a stall.
 * However, a babble and other errors also halt the endpoपूर्णांक ring, and the class
 * driver won't clear the halt in that हाल, so we need to issue a Set Transfer
 * Ring Dequeue Poपूर्णांकer command manually.
 */
अटल पूर्णांक xhci_requires_manual_halt_cleanup(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_ep_ctx *ep_ctx,
		अचिन्हित पूर्णांक trb_comp_code)
अणु
	/* TRB completion codes that may require a manual halt cleanup */
	अगर (trb_comp_code == COMP_USB_TRANSACTION_ERROR ||
			trb_comp_code == COMP_BABBLE_DETECTED_ERROR ||
			trb_comp_code == COMP_SPLIT_TRANSACTION_ERROR)
		/* The 0.95 spec says a babbling control endpoपूर्णांक
		 * is not halted. The 0.96 spec says it is.  Some HW
		 * claims to be 0.95 compliant, but it halts the control
		 * endpoपूर्णांक anyway.  Check अगर a babble halted the
		 * endpoपूर्णांक.
		 */
		अगर (GET_EP_CTX_STATE(ep_ctx) == EP_STATE_HALTED)
			वापस 1;

	वापस 0;
पूर्ण

पूर्णांक xhci_is_venकरोr_info_code(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक trb_comp_code)
अणु
	अगर (trb_comp_code >= 224 && trb_comp_code <= 255) अणु
		/* Venकरोr defined "informational" completion code,
		 * treat as not-an-error.
		 */
		xhci_dbg(xhci, "Vendor defined info completion code %u\n",
				trb_comp_code);
		xhci_dbg(xhci, "Treating code as success.\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक finish_td(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_ep *ep,
		     काष्ठा xhci_ring *ep_ring, काष्ठा xhci_td *td,
		     u32 trb_comp_code)
अणु
	काष्ठा xhci_ep_ctx *ep_ctx;

	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep->ep_index);

	चयन (trb_comp_code) अणु
	हाल COMP_STOPPED_LENGTH_INVALID:
	हाल COMP_STOPPED_SHORT_PACKET:
	हाल COMP_STOPPED:
		/*
		 * The "Stop Endpoint" completion will take care of any
		 * stopped TDs. A stopped TD may be restarted, so करोn't update
		 * the ring dequeue poपूर्णांकer or take this TD off any lists yet.
		 */
		वापस 0;
	हाल COMP_USB_TRANSACTION_ERROR:
	हाल COMP_BABBLE_DETECTED_ERROR:
	हाल COMP_SPLIT_TRANSACTION_ERROR:
		/*
		 * If endpoपूर्णांक context state is not halted we might be
		 * racing with a reset endpoपूर्णांक command issued by a unsuccessful
		 * stop endpoपूर्णांक completion (context error). In that हाल the
		 * td should be on the cancelled list, and EP_HALTED flag set.
		 *
		 * Or then it's not halted due to the 0.95 spec stating that a
		 * babbling control endpoपूर्णांक should not halt. The 0.96 spec
		 * again says it should.  Some HW claims to be 0.95 compliant,
		 * but it halts the control endpoपूर्णांक anyway.
		 */
		अगर (GET_EP_CTX_STATE(ep_ctx) != EP_STATE_HALTED) अणु
			/*
			 * If EP_HALTED is set and TD is on the cancelled list
			 * the TD and dequeue poपूर्णांकer will be handled by reset
			 * ep command completion
			 */
			अगर ((ep->ep_state & EP_HALTED) &&
			    !list_empty(&td->cancelled_td_list)) अणु
				xhci_dbg(xhci, "Already resolving halted ep for 0x%llx\n",
					 (अचिन्हित दीर्घ दीर्घ)xhci_trb_virt_to_dma(
						 td->start_seg, td->first_trb));
				वापस 0;
			पूर्ण
			/* endpoपूर्णांक not halted, करोn't reset it */
			अवरोध;
		पूर्ण
		/* Almost same procedure as क्रम STALL_ERROR below */
		xhci_clear_hub_tt_buffer(xhci, td, ep);
		xhci_handle_halted_endpoपूर्णांक(xhci, ep, ep_ring->stream_id, td,
					    EP_HARD_RESET);
		वापस 0;
	हाल COMP_STALL_ERROR:
		/*
		 * xhci पूर्णांकernal endpoपूर्णांक state will go to a "halt" state क्रम
		 * any stall, including शेष control pipe protocol stall.
		 * To clear the host side halt we need to issue a reset endpoपूर्णांक
		 * command, followed by a set dequeue command to move past the
		 * TD.
		 * Class drivers clear the device side halt from a functional
		 * stall later. Hub TT buffer should only be cleared क्रम FS/LS
		 * devices behind HS hubs क्रम functional stalls.
		 */
		अगर (ep->ep_index != 0)
			xhci_clear_hub_tt_buffer(xhci, td, ep);

		xhci_handle_halted_endpoपूर्णांक(xhci, ep, ep_ring->stream_id, td,
					    EP_HARD_RESET);

		वापस 0; /* xhci_handle_halted_endpoपूर्णांक marked td cancelled */
	शेष:
		अवरोध;
	पूर्ण

	/* Update ring dequeue poपूर्णांकer */
	ep_ring->dequeue = td->last_trb;
	ep_ring->deq_seg = td->last_trb_seg;
	ep_ring->num_trbs_मुक्त += td->num_trbs - 1;
	inc_deq(xhci, ep_ring);

	वापस xhci_td_cleanup(xhci, td, ep_ring, td->status);
पूर्ण

/* sum trb lengths from ring dequeue up to stop_trb, _excluding_ stop_trb */
अटल पूर्णांक sum_trb_lengths(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
			   जोड़ xhci_trb *stop_trb)
अणु
	u32 sum;
	जोड़ xhci_trb *trb = ring->dequeue;
	काष्ठा xhci_segment *seg = ring->deq_seg;

	क्रम (sum = 0; trb != stop_trb; next_trb(xhci, ring, &seg, &trb)) अणु
		अगर (!trb_is_noop(trb) && !trb_is_link(trb))
			sum += TRB_LEN(le32_to_cpu(trb->generic.field[2]));
	पूर्ण
	वापस sum;
पूर्ण

/*
 * Process control tds, update urb status and actual_length.
 */
अटल पूर्णांक process_ctrl_td(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_ep *ep,
		काष्ठा xhci_ring *ep_ring,  काष्ठा xhci_td *td,
			   जोड़ xhci_trb *ep_trb, काष्ठा xhci_transfer_event *event)
अणु
	काष्ठा xhci_ep_ctx *ep_ctx;
	u32 trb_comp_code;
	u32 reमुख्यing, requested;
	u32 trb_type;

	trb_type = TRB_FIELD_TO_TYPE(le32_to_cpu(ep_trb->generic.field[3]));
	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep->ep_index);
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	requested = td->urb->transfer_buffer_length;
	reमुख्यing = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));

	चयन (trb_comp_code) अणु
	हाल COMP_SUCCESS:
		अगर (trb_type != TRB_STATUS) अणु
			xhci_warn(xhci, "WARN: Success on ctrl %s TRB without IOC set?\n",
				  (trb_type == TRB_DATA) ? "data" : "setup");
			td->status = -ESHUTDOWN;
			अवरोध;
		पूर्ण
		td->status = 0;
		अवरोध;
	हाल COMP_SHORT_PACKET:
		td->status = 0;
		अवरोध;
	हाल COMP_STOPPED_SHORT_PACKET:
		अगर (trb_type == TRB_DATA || trb_type == TRB_NORMAL)
			td->urb->actual_length = reमुख्यing;
		अन्यथा
			xhci_warn(xhci, "WARN: Stopped Short Packet on ctrl setup or status TRB\n");
		जाओ finish_td;
	हाल COMP_STOPPED:
		चयन (trb_type) अणु
		हाल TRB_SETUP:
			td->urb->actual_length = 0;
			जाओ finish_td;
		हाल TRB_DATA:
		हाल TRB_NORMAL:
			td->urb->actual_length = requested - reमुख्यing;
			जाओ finish_td;
		हाल TRB_STATUS:
			td->urb->actual_length = requested;
			जाओ finish_td;
		शेष:
			xhci_warn(xhci, "WARN: unexpected TRB Type %d\n",
				  trb_type);
			जाओ finish_td;
		पूर्ण
	हाल COMP_STOPPED_LENGTH_INVALID:
		जाओ finish_td;
	शेष:
		अगर (!xhci_requires_manual_halt_cleanup(xhci,
						       ep_ctx, trb_comp_code))
			अवरोध;
		xhci_dbg(xhci, "TRB error %u, halted endpoint index = %u\n",
			 trb_comp_code, ep->ep_index);
		fallthrough;
	हाल COMP_STALL_ERROR:
		/* Did we transfer part of the data (middle) phase? */
		अगर (trb_type == TRB_DATA || trb_type == TRB_NORMAL)
			td->urb->actual_length = requested - reमुख्यing;
		अन्यथा अगर (!td->urb_length_set)
			td->urb->actual_length = 0;
		जाओ finish_td;
	पूर्ण

	/* stopped at setup stage, no data transferred */
	अगर (trb_type == TRB_SETUP)
		जाओ finish_td;

	/*
	 * अगर on data stage then update the actual_length of the URB and flag it
	 * as set, so it won't be overwritten in the event क्रम the last TRB.
	 */
	अगर (trb_type == TRB_DATA ||
		trb_type == TRB_NORMAL) अणु
		td->urb_length_set = true;
		td->urb->actual_length = requested - reमुख्यing;
		xhci_dbg(xhci, "Waiting for status stage event\n");
		वापस 0;
	पूर्ण

	/* at status stage */
	अगर (!td->urb_length_set)
		td->urb->actual_length = requested;

finish_td:
	वापस finish_td(xhci, ep, ep_ring, td, trb_comp_code);
पूर्ण

/*
 * Process isochronous tds, update urb packet status and actual_length.
 */
अटल पूर्णांक process_isoc_td(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_ep *ep,
		काष्ठा xhci_ring *ep_ring, काष्ठा xhci_td *td,
		जोड़ xhci_trb *ep_trb, काष्ठा xhci_transfer_event *event)
अणु
	काष्ठा urb_priv *urb_priv;
	पूर्णांक idx;
	काष्ठा usb_iso_packet_descriptor *frame;
	u32 trb_comp_code;
	bool sum_trbs_क्रम_length = false;
	u32 reमुख्यing, requested, ep_trb_len;
	पूर्णांक लघु_framestatus;

	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	urb_priv = td->urb->hcpriv;
	idx = urb_priv->num_tds_करोne;
	frame = &td->urb->iso_frame_desc[idx];
	requested = frame->length;
	reमुख्यing = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
	ep_trb_len = TRB_LEN(le32_to_cpu(ep_trb->generic.field[2]));
	लघु_framestatus = td->urb->transfer_flags & URB_SHORT_NOT_OK ?
		-EREMOTEIO : 0;

	/* handle completion code */
	चयन (trb_comp_code) अणु
	हाल COMP_SUCCESS:
		अगर (reमुख्यing) अणु
			frame->status = लघु_framestatus;
			अगर (xhci->quirks & XHCI_TRUST_TX_LENGTH)
				sum_trbs_क्रम_length = true;
			अवरोध;
		पूर्ण
		frame->status = 0;
		अवरोध;
	हाल COMP_SHORT_PACKET:
		frame->status = लघु_framestatus;
		sum_trbs_क्रम_length = true;
		अवरोध;
	हाल COMP_BANDWIDTH_OVERRUN_ERROR:
		frame->status = -ECOMM;
		अवरोध;
	हाल COMP_ISOCH_BUFFER_OVERRUN:
	हाल COMP_BABBLE_DETECTED_ERROR:
		frame->status = -EOVERFLOW;
		अवरोध;
	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
	हाल COMP_STALL_ERROR:
		frame->status = -EPROTO;
		अवरोध;
	हाल COMP_USB_TRANSACTION_ERROR:
		frame->status = -EPROTO;
		अगर (ep_trb != td->last_trb)
			वापस 0;
		अवरोध;
	हाल COMP_STOPPED:
		sum_trbs_क्रम_length = true;
		अवरोध;
	हाल COMP_STOPPED_SHORT_PACKET:
		/* field normally containing residue now contains tranferred */
		frame->status = लघु_framestatus;
		requested = reमुख्यing;
		अवरोध;
	हाल COMP_STOPPED_LENGTH_INVALID:
		requested = 0;
		reमुख्यing = 0;
		अवरोध;
	शेष:
		sum_trbs_क्रम_length = true;
		frame->status = -1;
		अवरोध;
	पूर्ण

	अगर (sum_trbs_क्रम_length)
		frame->actual_length = sum_trb_lengths(xhci, ep->ring, ep_trb) +
			ep_trb_len - reमुख्यing;
	अन्यथा
		frame->actual_length = requested;

	td->urb->actual_length += frame->actual_length;

	वापस finish_td(xhci, ep, ep_ring, td, trb_comp_code);
पूर्ण

अटल पूर्णांक skip_isoc_td(काष्ठा xhci_hcd *xhci, काष्ठा xhci_td *td,
			काष्ठा xhci_virt_ep *ep, पूर्णांक status)
अणु
	काष्ठा urb_priv *urb_priv;
	काष्ठा usb_iso_packet_descriptor *frame;
	पूर्णांक idx;

	urb_priv = td->urb->hcpriv;
	idx = urb_priv->num_tds_करोne;
	frame = &td->urb->iso_frame_desc[idx];

	/* The transfer is partly करोne. */
	frame->status = -EXDEV;

	/* calc actual length */
	frame->actual_length = 0;

	/* Update ring dequeue poपूर्णांकer */
	ep->ring->dequeue = td->last_trb;
	ep->ring->deq_seg = td->last_trb_seg;
	ep->ring->num_trbs_मुक्त += td->num_trbs - 1;
	inc_deq(xhci, ep->ring);

	वापस xhci_td_cleanup(xhci, td, ep->ring, status);
पूर्ण

/*
 * Process bulk and पूर्णांकerrupt tds, update urb status and actual_length.
 */
अटल पूर्णांक process_bulk_पूर्णांकr_td(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_ep *ep,
		काष्ठा xhci_ring *ep_ring, काष्ठा xhci_td *td,
		जोड़ xhci_trb *ep_trb, काष्ठा xhci_transfer_event *event)
अणु
	काष्ठा xhci_slot_ctx *slot_ctx;
	u32 trb_comp_code;
	u32 reमुख्यing, requested, ep_trb_len;

	slot_ctx = xhci_get_slot_ctx(xhci, ep->vdev->out_ctx);
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	reमुख्यing = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
	ep_trb_len = TRB_LEN(le32_to_cpu(ep_trb->generic.field[2]));
	requested = td->urb->transfer_buffer_length;

	चयन (trb_comp_code) अणु
	हाल COMP_SUCCESS:
		ep_ring->err_count = 0;
		/* handle success with untransferred data as लघु packet */
		अगर (ep_trb != td->last_trb || reमुख्यing) अणु
			xhci_warn(xhci, "WARN Successful completion on short TX\n");
			xhci_dbg(xhci, "ep %#x - asked for %d bytes, %d bytes untransferred\n",
				 td->urb->ep->desc.bEndpoपूर्णांकAddress,
				 requested, reमुख्यing);
		पूर्ण
		td->status = 0;
		अवरोध;
	हाल COMP_SHORT_PACKET:
		xhci_dbg(xhci, "ep %#x - asked for %d bytes, %d bytes untransferred\n",
			 td->urb->ep->desc.bEndpoपूर्णांकAddress,
			 requested, reमुख्यing);
		td->status = 0;
		अवरोध;
	हाल COMP_STOPPED_SHORT_PACKET:
		td->urb->actual_length = reमुख्यing;
		जाओ finish_td;
	हाल COMP_STOPPED_LENGTH_INVALID:
		/* stopped on ep trb with invalid length, exclude it */
		ep_trb_len	= 0;
		reमुख्यing	= 0;
		अवरोध;
	हाल COMP_USB_TRANSACTION_ERROR:
		अगर (xhci->quirks & XHCI_NO_SOFT_RETRY ||
		    (ep_ring->err_count++ > MAX_SOFT_RETRY) ||
		    le32_to_cpu(slot_ctx->tt_info) & TT_SLOT)
			अवरोध;

		td->status = 0;

		xhci_handle_halted_endpoपूर्णांक(xhci, ep, ep_ring->stream_id, td,
					    EP_SOFT_RESET);
		वापस 0;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	अगर (ep_trb == td->last_trb)
		td->urb->actual_length = requested - reमुख्यing;
	अन्यथा
		td->urb->actual_length =
			sum_trb_lengths(xhci, ep_ring, ep_trb) +
			ep_trb_len - reमुख्यing;
finish_td:
	अगर (reमुख्यing > requested) अणु
		xhci_warn(xhci, "bad transfer trb length %d in event trb\n",
			  reमुख्यing);
		td->urb->actual_length = 0;
	पूर्ण

	वापस finish_td(xhci, ep, ep_ring, td, trb_comp_code);
पूर्ण

/*
 * If this function वापसs an error condition, it means it got a Transfer
 * event with a corrupted Slot ID, Endpoपूर्णांक ID, or TRB DMA address.
 * At this poपूर्णांक, the host controller is probably hosed and should be reset.
 */
अटल पूर्णांक handle_tx_event(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_transfer_event *event)
अणु
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_ring *ep_ring;
	अचिन्हित पूर्णांक slot_id;
	पूर्णांक ep_index;
	काष्ठा xhci_td *td = शून्य;
	dma_addr_t ep_trb_dma;
	काष्ठा xhci_segment *ep_seg;
	जोड़ xhci_trb *ep_trb;
	पूर्णांक status = -EINPROGRESS;
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा list_head *पंचांगp;
	u32 trb_comp_code;
	पूर्णांक td_num = 0;
	bool handling_skipped_tds = false;

	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->flags));
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	ep_trb_dma = le64_to_cpu(event->buffer);

	ep = xhci_get_virt_ep(xhci, slot_id, ep_index);
	अगर (!ep) अणु
		xhci_err(xhci, "ERROR Invalid Transfer event\n");
		जाओ err_out;
	पूर्ण

	ep_ring = xhci_dma_to_transfer_ring(ep, ep_trb_dma);
	ep_ctx = xhci_get_ep_ctx(xhci, ep->vdev->out_ctx, ep_index);

	अगर (GET_EP_CTX_STATE(ep_ctx) == EP_STATE_DISABLED) अणु
		xhci_err(xhci,
			 "ERROR Transfer event for disabled endpoint slot %u ep %u\n",
			  slot_id, ep_index);
		जाओ err_out;
	पूर्ण

	/* Some transfer events करोn't always poपूर्णांक to a trb, see xhci 4.17.4 */
	अगर (!ep_ring) अणु
		चयन (trb_comp_code) अणु
		हाल COMP_STALL_ERROR:
		हाल COMP_USB_TRANSACTION_ERROR:
		हाल COMP_INVALID_STREAM_TYPE_ERROR:
		हाल COMP_INVALID_STREAM_ID_ERROR:
			xhci_handle_halted_endpoपूर्णांक(xhci, ep, 0, शून्य,
						    EP_SOFT_RESET);
			जाओ cleanup;
		हाल COMP_RING_UNDERRUN:
		हाल COMP_RING_OVERRUN:
		हाल COMP_STOPPED_LENGTH_INVALID:
			जाओ cleanup;
		शेष:
			xhci_err(xhci, "ERROR Transfer event for unknown stream ring slot %u ep %u\n",
				 slot_id, ep_index);
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Count current td numbers अगर ep->skip is set */
	अगर (ep->skip) अणु
		list_क्रम_each(पंचांगp, &ep_ring->td_list)
			td_num++;
	पूर्ण

	/* Look क्रम common error हालs */
	चयन (trb_comp_code) अणु
	/* Skip codes that require special handling depending on
	 * transfer type
	 */
	हाल COMP_SUCCESS:
		अगर (EVENT_TRB_LEN(le32_to_cpu(event->transfer_len)) == 0)
			अवरोध;
		अगर (xhci->quirks & XHCI_TRUST_TX_LENGTH ||
		    ep_ring->last_td_was_लघु)
			trb_comp_code = COMP_SHORT_PACKET;
		अन्यथा
			xhci_warn_ratelimited(xhci,
					      "WARN Successful completion on short TX for slot %u ep %u: needs XHCI_TRUST_TX_LENGTH quirk?\n",
					      slot_id, ep_index);
		अवरोध;
	हाल COMP_SHORT_PACKET:
		अवरोध;
	/* Completion codes क्रम endpoपूर्णांक stopped state */
	हाल COMP_STOPPED:
		xhci_dbg(xhci, "Stopped on Transfer TRB for slot %u ep %u\n",
			 slot_id, ep_index);
		अवरोध;
	हाल COMP_STOPPED_LENGTH_INVALID:
		xhci_dbg(xhci,
			 "Stopped on No-op or Link TRB for slot %u ep %u\n",
			 slot_id, ep_index);
		अवरोध;
	हाल COMP_STOPPED_SHORT_PACKET:
		xhci_dbg(xhci,
			 "Stopped with short packet transfer detected for slot %u ep %u\n",
			 slot_id, ep_index);
		अवरोध;
	/* Completion codes क्रम endpoपूर्णांक halted state */
	हाल COMP_STALL_ERROR:
		xhci_dbg(xhci, "Stalled endpoint for slot %u ep %u\n", slot_id,
			 ep_index);
		status = -EPIPE;
		अवरोध;
	हाल COMP_SPLIT_TRANSACTION_ERROR:
		xhci_dbg(xhci, "Split transaction error for slot %u ep %u\n",
			 slot_id, ep_index);
		status = -EPROTO;
		अवरोध;
	हाल COMP_USB_TRANSACTION_ERROR:
		xhci_dbg(xhci, "Transfer error for slot %u ep %u on endpoint\n",
			 slot_id, ep_index);
		status = -EPROTO;
		अवरोध;
	हाल COMP_BABBLE_DETECTED_ERROR:
		xhci_dbg(xhci, "Babble error for slot %u ep %u on endpoint\n",
			 slot_id, ep_index);
		status = -EOVERFLOW;
		अवरोध;
	/* Completion codes क्रम endpoपूर्णांक error state */
	हाल COMP_TRB_ERROR:
		xhci_warn(xhci,
			  "WARN: TRB error for slot %u ep %u on endpoint\n",
			  slot_id, ep_index);
		status = -EILSEQ;
		अवरोध;
	/* completion codes not indicating endpoपूर्णांक state change */
	हाल COMP_DATA_BUFFER_ERROR:
		xhci_warn(xhci,
			  "WARN: HC couldn't access mem fast enough for slot %u ep %u\n",
			  slot_id, ep_index);
		status = -ENOSR;
		अवरोध;
	हाल COMP_BANDWIDTH_OVERRUN_ERROR:
		xhci_warn(xhci,
			  "WARN: bandwidth overrun event for slot %u ep %u on endpoint\n",
			  slot_id, ep_index);
		अवरोध;
	हाल COMP_ISOCH_BUFFER_OVERRUN:
		xhci_warn(xhci,
			  "WARN: buffer overrun event for slot %u ep %u on endpoint",
			  slot_id, ep_index);
		अवरोध;
	हाल COMP_RING_UNDERRUN:
		/*
		 * When the Isoch ring is empty, the xHC will generate
		 * a Ring Overrun Event क्रम IN Isoch endpoपूर्णांक or Ring
		 * Underrun Event क्रम OUT Isoch endpoपूर्णांक.
		 */
		xhci_dbg(xhci, "underrun event on endpoint\n");
		अगर (!list_empty(&ep_ring->td_list))
			xhci_dbg(xhci, "Underrun Event for slot %d ep %d "
					"still with TDs queued?\n",
				 TRB_TO_SLOT_ID(le32_to_cpu(event->flags)),
				 ep_index);
		जाओ cleanup;
	हाल COMP_RING_OVERRUN:
		xhci_dbg(xhci, "overrun event on endpoint\n");
		अगर (!list_empty(&ep_ring->td_list))
			xhci_dbg(xhci, "Overrun Event for slot %d ep %d "
					"still with TDs queued?\n",
				 TRB_TO_SLOT_ID(le32_to_cpu(event->flags)),
				 ep_index);
		जाओ cleanup;
	हाल COMP_MISSED_SERVICE_ERROR:
		/*
		 * When encounter missed service error, one or more isoc tds
		 * may be missed by xHC.
		 * Set skip flag of the ep_ring; Complete the missed tds as
		 * लघु transfer when process the ep_ring next समय.
		 */
		ep->skip = true;
		xhci_dbg(xhci,
			 "Miss service interval error for slot %u ep %u, set skip flag\n",
			 slot_id, ep_index);
		जाओ cleanup;
	हाल COMP_NO_PING_RESPONSE_ERROR:
		ep->skip = true;
		xhci_dbg(xhci,
			 "No Ping response error for slot %u ep %u, Skip one Isoc TD\n",
			 slot_id, ep_index);
		जाओ cleanup;

	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
		/* needs disable slot command to recover */
		xhci_warn(xhci,
			  "WARN: detect an incompatible device for slot %u ep %u",
			  slot_id, ep_index);
		status = -EPROTO;
		अवरोध;
	शेष:
		अगर (xhci_is_venकरोr_info_code(xhci, trb_comp_code)) अणु
			status = 0;
			अवरोध;
		पूर्ण
		xhci_warn(xhci,
			  "ERROR Unknown event condition %u for slot %u ep %u , HC probably busted\n",
			  trb_comp_code, slot_id, ep_index);
		जाओ cleanup;
	पूर्ण

	करो अणु
		/* This TRB should be in the TD at the head of this ring's
		 * TD list.
		 */
		अगर (list_empty(&ep_ring->td_list)) अणु
			/*
			 * Don't print wanings if it's due to a stopped endpoपूर्णांक
			 * generating an extra completion event अगर the device
			 * was suspended. Or, a event क्रम the last TRB of a
			 * लघु TD we alपढ़ोy got a लघु event क्रम.
			 * The लघु TD is alपढ़ोy हटाओd from the TD list.
			 */

			अगर (!(trb_comp_code == COMP_STOPPED ||
			      trb_comp_code == COMP_STOPPED_LENGTH_INVALID ||
			      ep_ring->last_td_was_लघु)) अणु
				xhci_warn(xhci, "WARN Event TRB for slot %d ep %d with no TDs queued?\n",
						TRB_TO_SLOT_ID(le32_to_cpu(event->flags)),
						ep_index);
			पूर्ण
			अगर (ep->skip) अणु
				ep->skip = false;
				xhci_dbg(xhci, "td_list is empty while skip flag set. Clear skip flag for slot %u ep %u.\n",
					 slot_id, ep_index);
			पूर्ण
			अगर (trb_comp_code == COMP_STALL_ERROR ||
			    xhci_requires_manual_halt_cleanup(xhci, ep_ctx,
							      trb_comp_code)) अणु
				xhci_handle_halted_endpoपूर्णांक(xhci, ep,
							    ep_ring->stream_id,
							    शून्य,
							    EP_HARD_RESET);
			पूर्ण
			जाओ cleanup;
		पूर्ण

		/* We've skipped all the TDs on the ep ring when ep->skip set */
		अगर (ep->skip && td_num == 0) अणु
			ep->skip = false;
			xhci_dbg(xhci, "All tds on the ep_ring skipped. Clear skip flag for slot %u ep %u.\n",
				 slot_id, ep_index);
			जाओ cleanup;
		पूर्ण

		td = list_first_entry(&ep_ring->td_list, काष्ठा xhci_td,
				      td_list);
		अगर (ep->skip)
			td_num--;

		/* Is this a TRB in the currently executing TD? */
		ep_seg = trb_in_td(xhci, ep_ring->deq_seg, ep_ring->dequeue,
				td->last_trb, ep_trb_dma, false);

		/*
		 * Skip the Force Stopped Event. The event_trb(event_dma) of FSE
		 * is not in the current TD poपूर्णांकed by ep_ring->dequeue because
		 * that the hardware dequeue poपूर्णांकer still at the previous TRB
		 * of the current TD. The previous TRB maybe a Link TD or the
		 * last TRB of the previous TD. The command completion handle
		 * will take care the rest.
		 */
		अगर (!ep_seg && (trb_comp_code == COMP_STOPPED ||
			   trb_comp_code == COMP_STOPPED_LENGTH_INVALID)) अणु
			जाओ cleanup;
		पूर्ण

		अगर (!ep_seg) अणु
			अगर (!ep->skip ||
			    !usb_endpoपूर्णांक_xfer_isoc(&td->urb->ep->desc)) अणु
				/* Some host controllers give a spurious
				 * successful event after a लघु transfer.
				 * Ignore it.
				 */
				अगर ((xhci->quirks & XHCI_SPURIOUS_SUCCESS) &&
						ep_ring->last_td_was_लघु) अणु
					ep_ring->last_td_was_लघु = false;
					जाओ cleanup;
				पूर्ण
				/* HC is busted, give up! */
				xhci_err(xhci,
					"ERROR Transfer event TRB DMA ptr not "
					"part of current TD ep_index %d "
					"comp_code %u\n", ep_index,
					trb_comp_code);
				trb_in_td(xhci, ep_ring->deq_seg,
					  ep_ring->dequeue, td->last_trb,
					  ep_trb_dma, true);
				वापस -ESHUTDOWN;
			पूर्ण

			skip_isoc_td(xhci, td, ep, status);
			जाओ cleanup;
		पूर्ण
		अगर (trb_comp_code == COMP_SHORT_PACKET)
			ep_ring->last_td_was_लघु = true;
		अन्यथा
			ep_ring->last_td_was_लघु = false;

		अगर (ep->skip) अणु
			xhci_dbg(xhci,
				 "Found td. Clear skip flag for slot %u ep %u.\n",
				 slot_id, ep_index);
			ep->skip = false;
		पूर्ण

		ep_trb = &ep_seg->trbs[(ep_trb_dma - ep_seg->dma) /
						माप(*ep_trb)];

		trace_xhci_handle_transfer(ep_ring,
				(काष्ठा xhci_generic_trb *) ep_trb);

		/*
		 * No-op TRB could trigger पूर्णांकerrupts in a हाल where
		 * a URB was समाप्तed and a STALL_ERROR happens right
		 * after the endpoपूर्णांक ring stopped. Reset the halted
		 * endpoपूर्णांक. Otherwise, the endpoपूर्णांक reमुख्यs stalled
		 * indefinitely.
		 */

		अगर (trb_is_noop(ep_trb)) अणु
			अगर (trb_comp_code == COMP_STALL_ERROR ||
			    xhci_requires_manual_halt_cleanup(xhci, ep_ctx,
							      trb_comp_code))
				xhci_handle_halted_endpoपूर्णांक(xhci, ep,
							    ep_ring->stream_id,
							    td, EP_HARD_RESET);
			जाओ cleanup;
		पूर्ण

		td->status = status;

		/* update the urb's actual_length and give back to the core */
		अगर (usb_endpoपूर्णांक_xfer_control(&td->urb->ep->desc))
			process_ctrl_td(xhci, ep, ep_ring, td, ep_trb, event);
		अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(&td->urb->ep->desc))
			process_isoc_td(xhci, ep, ep_ring, td, ep_trb, event);
		अन्यथा
			process_bulk_पूर्णांकr_td(xhci, ep, ep_ring, td, ep_trb, event);
cleanup:
		handling_skipped_tds = ep->skip &&
			trb_comp_code != COMP_MISSED_SERVICE_ERROR &&
			trb_comp_code != COMP_NO_PING_RESPONSE_ERROR;

		/*
		 * Do not update event ring dequeue poपूर्णांकer अगर we're in a loop
		 * processing missed tds.
		 */
		अगर (!handling_skipped_tds)
			inc_deq(xhci, xhci->event_ring);

	/*
	 * If ep->skip is set, it means there are missed tds on the
	 * endpoपूर्णांक ring need to take care of.
	 * Process them as लघु transfer until reach the td poपूर्णांकed by
	 * the event.
	 */
	पूर्ण जबतक (handling_skipped_tds);

	वापस 0;

err_out:
	xhci_err(xhci, "@%016llx %08x %08x %08x %08x\n",
		 (अचिन्हित दीर्घ दीर्घ) xhci_trb_virt_to_dma(
			 xhci->event_ring->deq_seg,
			 xhci->event_ring->dequeue),
		 lower_32_bits(le64_to_cpu(event->buffer)),
		 upper_32_bits(le64_to_cpu(event->buffer)),
		 le32_to_cpu(event->transfer_len),
		 le32_to_cpu(event->flags));
	वापस -ENODEV;
पूर्ण

/*
 * This function handles all OS-owned events on the event ring.  It may drop
 * xhci->lock between event processing (e.g. to pass up port status changes).
 * Returns >0 क्रम "possibly more events to process" (caller should call again),
 * otherwise 0 अगर करोne.  In future, <0 वापसs should indicate error code.
 */
अटल पूर्णांक xhci_handle_event(काष्ठा xhci_hcd *xhci)
अणु
	जोड़ xhci_trb *event;
	पूर्णांक update_ptrs = 1;
	u32 trb_type;
	पूर्णांक ret;

	/* Event ring hasn't been allocated yet. */
	अगर (!xhci->event_ring || !xhci->event_ring->dequeue) अणु
		xhci_err(xhci, "ERROR event ring not ready\n");
		वापस -ENOMEM;
	पूर्ण

	event = xhci->event_ring->dequeue;
	/* Does the HC or OS own the TRB? */
	अगर ((le32_to_cpu(event->event_cmd.flags) & TRB_CYCLE) !=
	    xhci->event_ring->cycle_state)
		वापस 0;

	trace_xhci_handle_event(xhci->event_ring, &event->generic);

	/*
	 * Barrier between पढ़ोing the TRB_CYCLE (valid) flag above and any
	 * speculative पढ़ोs of the event's flags/data below.
	 */
	rmb();
	trb_type = TRB_FIELD_TO_TYPE(le32_to_cpu(event->event_cmd.flags));
	/* FIXME: Handle more event types. */

	चयन (trb_type) अणु
	हाल TRB_COMPLETION:
		handle_cmd_completion(xhci, &event->event_cmd);
		अवरोध;
	हाल TRB_PORT_STATUS:
		handle_port_status(xhci, event);
		update_ptrs = 0;
		अवरोध;
	हाल TRB_TRANSFER:
		ret = handle_tx_event(xhci, &event->trans_event);
		अगर (ret >= 0)
			update_ptrs = 0;
		अवरोध;
	हाल TRB_DEV_NOTE:
		handle_device_notअगरication(xhci, event);
		अवरोध;
	शेष:
		अगर (trb_type >= TRB_VENDOR_DEFINED_LOW)
			handle_venकरोr_event(xhci, event, trb_type);
		अन्यथा
			xhci_warn(xhci, "ERROR unknown event type %d\n", trb_type);
	पूर्ण
	/* Any of the above functions may drop and re-acquire the lock, so check
	 * to make sure a watchकरोg समयr didn't mark the host as non-responsive.
	 */
	अगर (xhci->xhc_state & XHCI_STATE_DYING) अणु
		xhci_dbg(xhci, "xHCI host dying, returning from "
				"event handler.\n");
		वापस 0;
	पूर्ण

	अगर (update_ptrs)
		/* Update SW event ring dequeue poपूर्णांकer */
		inc_deq(xhci, xhci->event_ring);

	/* Are there more items on the event ring?  Caller will call us again to
	 * check.
	 */
	वापस 1;
पूर्ण

/*
 * Update Event Ring Dequeue Poपूर्णांकer:
 * - When all events have finished
 * - To aव्योम "Event Ring Full Error" condition
 */
अटल व्योम xhci_update_erst_dequeue(काष्ठा xhci_hcd *xhci,
		जोड़ xhci_trb *event_ring_deq)
अणु
	u64 temp_64;
	dma_addr_t deq;

	temp_64 = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_dequeue);
	/* If necessary, update the HW's version of the event ring deq ptr. */
	अगर (event_ring_deq != xhci->event_ring->dequeue) अणु
		deq = xhci_trb_virt_to_dma(xhci->event_ring->deq_seg,
				xhci->event_ring->dequeue);
		अगर (deq == 0)
			xhci_warn(xhci, "WARN something wrong with SW event ring dequeue ptr\n");
		/*
		 * Per 4.9.4, Software ग_लिखोs to the ERDP रेजिस्टर shall
		 * always advance the Event Ring Dequeue Poपूर्णांकer value.
		 */
		अगर ((temp_64 & (u64) ~ERST_PTR_MASK) ==
				((u64) deq & (u64) ~ERST_PTR_MASK))
			वापस;

		/* Update HC event ring dequeue poपूर्णांकer */
		temp_64 &= ERST_PTR_MASK;
		temp_64 |= ((u64) deq & (u64) ~ERST_PTR_MASK);
	पूर्ण

	/* Clear the event handler busy flag (RW1C) */
	temp_64 |= ERST_EHB;
	xhci_ग_लिखो_64(xhci, temp_64, &xhci->ir_set->erst_dequeue);
पूर्ण

/*
 * xHCI spec says we can get an पूर्णांकerrupt, and अगर the HC has an error condition,
 * we might get bad data out of the event ring.  Section 4.10.2.7 has a list of
 * indicators of an event TRB error, but we check the status *first* to be safe.
 */
irqवापस_t xhci_irq(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	जोड़ xhci_trb *event_ring_deq;
	irqवापस_t ret = IRQ_NONE;
	u64 temp_64;
	u32 status;
	पूर्णांक event_loop = 0;

	spin_lock(&xhci->lock);
	/* Check अगर the xHC generated the पूर्णांकerrupt, or the irq is shared */
	status = पढ़ोl(&xhci->op_regs->status);
	अगर (status == ~(u32)0) अणु
		xhci_hc_died(xhci);
		ret = IRQ_HANDLED;
		जाओ out;
	पूर्ण

	अगर (!(status & STS_EINT))
		जाओ out;

	अगर (status & STS_FATAL) अणु
		xhci_warn(xhci, "WARNING: Host System Error\n");
		xhci_halt(xhci);
		ret = IRQ_HANDLED;
		जाओ out;
	पूर्ण

	/*
	 * Clear the op reg पूर्णांकerrupt status first,
	 * so we can receive पूर्णांकerrupts from other MSI-X पूर्णांकerrupters.
	 * Write 1 to clear the पूर्णांकerrupt status.
	 */
	status |= STS_EINT;
	ग_लिखोl(status, &xhci->op_regs->status);

	अगर (!hcd->msi_enabled) अणु
		u32 irq_pending;
		irq_pending = पढ़ोl(&xhci->ir_set->irq_pending);
		irq_pending |= IMAN_IP;
		ग_लिखोl(irq_pending, &xhci->ir_set->irq_pending);
	पूर्ण

	अगर (xhci->xhc_state & XHCI_STATE_DYING ||
	    xhci->xhc_state & XHCI_STATE_HALTED) अणु
		xhci_dbg(xhci, "xHCI dying, ignoring interrupt. "
				"Shouldn't IRQs be disabled?\n");
		/* Clear the event handler busy flag (RW1C);
		 * the event ring should be empty.
		 */
		temp_64 = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_dequeue);
		xhci_ग_लिखो_64(xhci, temp_64 | ERST_EHB,
				&xhci->ir_set->erst_dequeue);
		ret = IRQ_HANDLED;
		जाओ out;
	पूर्ण

	event_ring_deq = xhci->event_ring->dequeue;
	/* FIXME this should be a delayed service routine
	 * that clears the EHB.
	 */
	जबतक (xhci_handle_event(xhci) > 0) अणु
		अगर (event_loop++ < TRBS_PER_SEGMENT / 2)
			जारी;
		xhci_update_erst_dequeue(xhci, event_ring_deq);
		event_loop = 0;
	पूर्ण

	xhci_update_erst_dequeue(xhci, event_ring_deq);
	ret = IRQ_HANDLED;

out:
	spin_unlock(&xhci->lock);

	वापस ret;
पूर्ण

irqवापस_t xhci_msi_irq(पूर्णांक irq, व्योम *hcd)
अणु
	वापस xhci_irq(hcd);
पूर्ण

/****		Endpoपूर्णांक Ring Operations	****/

/*
 * Generic function क्रम queueing a TRB on a ring.
 * The caller must have checked to make sure there's room on the ring.
 *
 * @more_trbs_coming:	Will you enqueue more TRBs beक्रमe calling
 *			prepare_transfer()?
 */
अटल व्योम queue_trb(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
		bool more_trbs_coming,
		u32 field1, u32 field2, u32 field3, u32 field4)
अणु
	काष्ठा xhci_generic_trb *trb;

	trb = &ring->enqueue->generic;
	trb->field[0] = cpu_to_le32(field1);
	trb->field[1] = cpu_to_le32(field2);
	trb->field[2] = cpu_to_le32(field3);
	/* make sure TRB is fully written beक्रमe giving it to the controller */
	wmb();
	trb->field[3] = cpu_to_le32(field4);

	trace_xhci_queue_trb(ring, trb);

	inc_enq(xhci, ring, more_trbs_coming);
पूर्ण

/*
 * Does various checks on the endpoपूर्णांक ring, and makes it पढ़ोy to queue num_trbs.
 * FIXME allocate segments अगर the ring is full.
 */
अटल पूर्णांक prepare_ring(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ep_ring,
		u32 ep_state, अचिन्हित पूर्णांक num_trbs, gfp_t mem_flags)
अणु
	अचिन्हित पूर्णांक num_trbs_needed;
	अचिन्हित पूर्णांक link_trb_count = 0;

	/* Make sure the endpoपूर्णांक has been added to xHC schedule */
	चयन (ep_state) अणु
	हाल EP_STATE_DISABLED:
		/*
		 * USB core changed config/पूर्णांकerfaces without notअगरying us,
		 * or hardware is reporting the wrong state.
		 */
		xhci_warn(xhci, "WARN urb submitted to disabled ep\n");
		वापस -ENOENT;
	हाल EP_STATE_ERROR:
		xhci_warn(xhci, "WARN waiting for error on ep to be cleared\n");
		/* FIXME event handling code क्रम error needs to clear it */
		/* XXX not sure अगर this should be -ENOENT or not */
		वापस -EINVAL;
	हाल EP_STATE_HALTED:
		xhci_dbg(xhci, "WARN halted endpoint, queueing URB anyway.\n");
		अवरोध;
	हाल EP_STATE_STOPPED:
	हाल EP_STATE_RUNNING:
		अवरोध;
	शेष:
		xhci_err(xhci, "ERROR unknown endpoint state for ep\n");
		/*
		 * FIXME issue Configure Endpoपूर्णांक command to try to get the HC
		 * back पूर्णांकo a known state.
		 */
		वापस -EINVAL;
	पूर्ण

	जबतक (1) अणु
		अगर (room_on_ring(xhci, ep_ring, num_trbs))
			अवरोध;

		अगर (ep_ring == xhci->cmd_ring) अणु
			xhci_err(xhci, "Do not support expand command ring\n");
			वापस -ENOMEM;
		पूर्ण

		xhci_dbg_trace(xhci, trace_xhci_dbg_ring_expansion,
				"ERROR no room on ep ring, try ring expansion");
		num_trbs_needed = num_trbs - ep_ring->num_trbs_मुक्त;
		अगर (xhci_ring_expansion(xhci, ep_ring, num_trbs_needed,
					mem_flags)) अणु
			xhci_err(xhci, "Ring expansion failed\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	जबतक (trb_is_link(ep_ring->enqueue)) अणु
		/* If we're not dealing with 0.95 hardware or isoc rings
		 * on AMD 0.96 host, clear the chain bit.
		 */
		अगर (!xhci_link_trb_quirk(xhci) &&
		    !(ep_ring->type == TYPE_ISOC &&
		      (xhci->quirks & XHCI_AMD_0x96_HOST)))
			ep_ring->enqueue->link.control &=
				cpu_to_le32(~TRB_CHAIN);
		अन्यथा
			ep_ring->enqueue->link.control |=
				cpu_to_le32(TRB_CHAIN);

		wmb();
		ep_ring->enqueue->link.control ^= cpu_to_le32(TRB_CYCLE);

		/* Toggle the cycle bit after the last ring segment. */
		अगर (link_trb_toggles_cycle(ep_ring->enqueue))
			ep_ring->cycle_state ^= 1;

		ep_ring->enq_seg = ep_ring->enq_seg->next;
		ep_ring->enqueue = ep_ring->enq_seg->trbs;

		/* prevent infinite loop अगर all first trbs are link trbs */
		अगर (link_trb_count++ > ep_ring->num_segs) अणु
			xhci_warn(xhci, "Ring is an endless link TRB loop\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (last_trb_on_seg(ep_ring->enq_seg, ep_ring->enqueue)) अणु
		xhci_warn(xhci, "Missing link TRB at end of ring segment\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prepare_transfer(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *xdev,
		अचिन्हित पूर्णांक ep_index,
		अचिन्हित पूर्णांक stream_id,
		अचिन्हित पूर्णांक num_trbs,
		काष्ठा urb *urb,
		अचिन्हित पूर्णांक td_index,
		gfp_t mem_flags)
अणु
	पूर्णांक ret;
	काष्ठा urb_priv *urb_priv;
	काष्ठा xhci_td	*td;
	काष्ठा xhci_ring *ep_ring;
	काष्ठा xhci_ep_ctx *ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	ep_ring = xhci_triad_to_transfer_ring(xhci, xdev->slot_id, ep_index,
					      stream_id);
	अगर (!ep_ring) अणु
		xhci_dbg(xhci, "Can't prepare ring for bad stream ID %u\n",
				stream_id);
		वापस -EINVAL;
	पूर्ण

	ret = prepare_ring(xhci, ep_ring, GET_EP_CTX_STATE(ep_ctx),
			   num_trbs, mem_flags);
	अगर (ret)
		वापस ret;

	urb_priv = urb->hcpriv;
	td = &urb_priv->td[td_index];

	INIT_LIST_HEAD(&td->td_list);
	INIT_LIST_HEAD(&td->cancelled_td_list);

	अगर (td_index == 0) अणु
		ret = usb_hcd_link_urb_to_ep(bus_to_hcd(urb->dev->bus), urb);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण

	td->urb = urb;
	/* Add this TD to the tail of the endpoपूर्णांक ring's TD list */
	list_add_tail(&td->td_list, &ep_ring->td_list);
	td->start_seg = ep_ring->enq_seg;
	td->first_trb = ep_ring->enqueue;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक count_trbs(u64 addr, u64 len)
अणु
	अचिन्हित पूर्णांक num_trbs;

	num_trbs = DIV_ROUND_UP(len + (addr & (TRB_MAX_BUFF_SIZE - 1)),
			TRB_MAX_BUFF_SIZE);
	अगर (num_trbs == 0)
		num_trbs++;

	वापस num_trbs;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक count_trbs_needed(काष्ठा urb *urb)
अणु
	वापस count_trbs(urb->transfer_dma, urb->transfer_buffer_length);
पूर्ण

अटल अचिन्हित पूर्णांक count_sg_trbs_needed(काष्ठा urb *urb)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, len, full_len, num_trbs = 0;

	full_len = urb->transfer_buffer_length;

	क्रम_each_sg(urb->sg, sg, urb->num_mapped_sgs, i) अणु
		len = sg_dma_len(sg);
		num_trbs += count_trbs(sg_dma_address(sg), len);
		len = min_t(अचिन्हित पूर्णांक, len, full_len);
		full_len -= len;
		अगर (full_len == 0)
			अवरोध;
	पूर्ण

	वापस num_trbs;
पूर्ण

अटल अचिन्हित पूर्णांक count_isoc_trbs_needed(काष्ठा urb *urb, पूर्णांक i)
अणु
	u64 addr, len;

	addr = (u64) (urb->transfer_dma + urb->iso_frame_desc[i].offset);
	len = urb->iso_frame_desc[i].length;

	वापस count_trbs(addr, len);
पूर्ण

अटल व्योम check_trb_math(काष्ठा urb *urb, पूर्णांक running_total)
अणु
	अगर (unlikely(running_total != urb->transfer_buffer_length))
		dev_err(&urb->dev->dev, "%s - ep %#x - Miscalculated tx length, "
				"queued %#x (%d), asked for %#x (%d)\n",
				__func__,
				urb->ep->desc.bEndpoपूर्णांकAddress,
				running_total, running_total,
				urb->transfer_buffer_length,
				urb->transfer_buffer_length);
पूर्ण

अटल व्योम giveback_first_trb(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index, अचिन्हित पूर्णांक stream_id, पूर्णांक start_cycle,
		काष्ठा xhci_generic_trb *start_trb)
अणु
	/*
	 * Pass all the TRBs to the hardware at once and make sure this ग_लिखो
	 * isn't reordered.
	 */
	wmb();
	अगर (start_cycle)
		start_trb->field[3] |= cpu_to_le32(start_cycle);
	अन्यथा
		start_trb->field[3] &= cpu_to_le32(~TRB_CYCLE);
	xhci_ring_ep_करोorbell(xhci, slot_id, ep_index, stream_id);
पूर्ण

अटल व्योम check_पूर्णांकerval(काष्ठा xhci_hcd *xhci, काष्ठा urb *urb,
						काष्ठा xhci_ep_ctx *ep_ctx)
अणु
	पूर्णांक xhci_पूर्णांकerval;
	पूर्णांक ep_पूर्णांकerval;

	xhci_पूर्णांकerval = EP_INTERVAL_TO_UFRAMES(le32_to_cpu(ep_ctx->ep_info));
	ep_पूर्णांकerval = urb->पूर्णांकerval;

	/* Convert to microframes */
	अगर (urb->dev->speed == USB_SPEED_LOW ||
			urb->dev->speed == USB_SPEED_FULL)
		ep_पूर्णांकerval *= 8;

	/* FIXME change this to a warning and a suggestion to use the new API
	 * to set the polling पूर्णांकerval (once the API is added).
	 */
	अगर (xhci_पूर्णांकerval != ep_पूर्णांकerval) अणु
		dev_dbg_ratelimited(&urb->dev->dev,
				"Driver uses different interval (%d microframe%s) than xHCI (%d microframe%s)\n",
				ep_पूर्णांकerval, ep_पूर्णांकerval == 1 ? "" : "s",
				xhci_पूर्णांकerval, xhci_पूर्णांकerval == 1 ? "" : "s");
		urb->पूर्णांकerval = xhci_पूर्णांकerval;
		/* Convert back to frames क्रम LS/FS devices */
		अगर (urb->dev->speed == USB_SPEED_LOW ||
				urb->dev->speed == USB_SPEED_FULL)
			urb->पूर्णांकerval /= 8;
	पूर्ण
पूर्ण

/*
 * xHCI uses normal TRBs क्रम both bulk and पूर्णांकerrupt.  When the पूर्णांकerrupt
 * endpoपूर्णांक is to be serviced, the xHC will consume (at most) one TD.  A TD
 * (comprised of sg list entries) can take several service पूर्णांकervals to
 * transmit.
 */
पूर्णांक xhci_queue_पूर्णांकr_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags,
		काष्ठा urb *urb, पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index)
अणु
	काष्ठा xhci_ep_ctx *ep_ctx;

	ep_ctx = xhci_get_ep_ctx(xhci, xhci->devs[slot_id]->out_ctx, ep_index);
	check_पूर्णांकerval(xhci, urb, ep_ctx);

	वापस xhci_queue_bulk_tx(xhci, mem_flags, urb, slot_id, ep_index);
पूर्ण

/*
 * For xHCI 1.0 host controllers, TD size is the number of max packet sized
 * packets reमुख्यing in the TD (*not* including this TRB).
 *
 * Total TD packet count = total_packet_count =
 *     DIV_ROUND_UP(TD size in bytes / wMaxPacketSize)
 *
 * Packets transferred up to and including this TRB = packets_transferred =
 *     roundकरोwn(total bytes transferred including this TRB / wMaxPacketSize)
 *
 * TD size = total_packet_count - packets_transferred
 *
 * For xHCI 0.96 and older, TD size field should be the reमुख्यing bytes
 * including this TRB, right shअगरted by 10
 *
 * For all hosts it must fit in bits 21:17, so it can't be bigger than 31.
 * This is taken care of in the TRB_TD_SIZE() macro
 *
 * The last TRB in a TD must have the TD size set to zero.
 */
अटल u32 xhci_td_reमुख्यder(काष्ठा xhci_hcd *xhci, पूर्णांक transferred,
			      पूर्णांक trb_buff_len, अचिन्हित पूर्णांक td_total_len,
			      काष्ठा urb *urb, bool more_trbs_coming)
अणु
	u32 maxp, total_packet_count;

	/* MTK xHCI 0.96 contains some features from 1.0 */
	अगर (xhci->hci_version < 0x100 && !(xhci->quirks & XHCI_MTK_HOST))
		वापस ((td_total_len - transferred) >> 10);

	/* One TRB with a zero-length data packet. */
	अगर (!more_trbs_coming || (transferred == 0 && trb_buff_len == 0) ||
	    trb_buff_len == td_total_len)
		वापस 0;

	/* क्रम MTK xHCI 0.96, TD size include this TRB, but not in 1.x */
	अगर ((xhci->quirks & XHCI_MTK_HOST) && (xhci->hci_version < 0x100))
		trb_buff_len = 0;

	maxp = usb_endpoपूर्णांक_maxp(&urb->ep->desc);
	total_packet_count = DIV_ROUND_UP(td_total_len, maxp);

	/* Queueing functions करोn't count the current TRB पूर्णांकo transferred */
	वापस (total_packet_count - ((transferred + trb_buff_len) / maxp));
पूर्ण


अटल पूर्णांक xhci_align_td(काष्ठा xhci_hcd *xhci, काष्ठा urb *urb, u32 enqd_len,
			 u32 *trb_buff_len, काष्ठा xhci_segment *seg)
अणु
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.controller;
	अचिन्हित पूर्णांक unalign;
	अचिन्हित पूर्णांक max_pkt;
	u32 new_buff_len;
	माप_प्रकार len;

	max_pkt = usb_endpoपूर्णांक_maxp(&urb->ep->desc);
	unalign = (enqd_len + *trb_buff_len) % max_pkt;

	/* we got lucky, last normal TRB data on segment is packet aligned */
	अगर (unalign == 0)
		वापस 0;

	xhci_dbg(xhci, "Unaligned %d bytes, buff len %d\n",
		 unalign, *trb_buff_len);

	/* is the last nornal TRB alignable by splitting it */
	अगर (*trb_buff_len > unalign) अणु
		*trb_buff_len -= unalign;
		xhci_dbg(xhci, "split align, new buff len %d\n", *trb_buff_len);
		वापस 0;
	पूर्ण

	/*
	 * We want enqd_len + trb_buff_len to sum up to a number aligned to
	 * number which is भागisible by the endpoपूर्णांक's wMaxPacketSize. IOW:
	 * (size of currently enqueued TRBs + reमुख्यder) % wMaxPacketSize == 0.
	 */
	new_buff_len = max_pkt - (enqd_len % max_pkt);

	अगर (new_buff_len > (urb->transfer_buffer_length - enqd_len))
		new_buff_len = (urb->transfer_buffer_length - enqd_len);

	/* create a max max_pkt sized bounce buffer poपूर्णांकed to by last trb */
	अगर (usb_urb_dir_out(urb)) अणु
		अगर (urb->num_sgs) अणु
			len = sg_pcopy_to_buffer(urb->sg, urb->num_sgs,
						 seg->bounce_buf, new_buff_len, enqd_len);
			अगर (len != new_buff_len)
				xhci_warn(xhci, "WARN Wrong bounce buffer write length: %zu != %d\n",
					  len, new_buff_len);
		पूर्ण अन्यथा अणु
			स_नकल(seg->bounce_buf, urb->transfer_buffer + enqd_len, new_buff_len);
		पूर्ण

		seg->bounce_dma = dma_map_single(dev, seg->bounce_buf,
						 max_pkt, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		seg->bounce_dma = dma_map_single(dev, seg->bounce_buf,
						 max_pkt, DMA_FROM_DEVICE);
	पूर्ण

	अगर (dma_mapping_error(dev, seg->bounce_dma)) अणु
		/* try without aligning. Some host controllers survive */
		xhci_warn(xhci, "Failed mapping bounce buffer, not aligning\n");
		वापस 0;
	पूर्ण
	*trb_buff_len = new_buff_len;
	seg->bounce_len = new_buff_len;
	seg->bounce_offs = enqd_len;

	xhci_dbg(xhci, "Bounce align, new buff len %d\n", *trb_buff_len);

	वापस 1;
पूर्ण

/* This is very similar to what ehci-q.c qtd_fill() करोes */
पूर्णांक xhci_queue_bulk_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags,
		काष्ठा urb *urb, पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index)
अणु
	काष्ठा xhci_ring *ring;
	काष्ठा urb_priv *urb_priv;
	काष्ठा xhci_td *td;
	काष्ठा xhci_generic_trb *start_trb;
	काष्ठा scatterlist *sg = शून्य;
	bool more_trbs_coming = true;
	bool need_zero_pkt = false;
	bool first_trb = true;
	अचिन्हित पूर्णांक num_trbs;
	अचिन्हित पूर्णांक start_cycle, num_sgs = 0;
	अचिन्हित पूर्णांक enqd_len, block_len, trb_buff_len, full_len;
	पूर्णांक sent_len, ret;
	u32 field, length_field, reमुख्यder;
	u64 addr, send_addr;

	ring = xhci_urb_to_transfer_ring(xhci, urb);
	अगर (!ring)
		वापस -EINVAL;

	full_len = urb->transfer_buffer_length;
	/* If we have scatter/gather list, we use it. */
	अगर (urb->num_sgs && !(urb->transfer_flags & URB_DMA_MAP_SINGLE)) अणु
		num_sgs = urb->num_mapped_sgs;
		sg = urb->sg;
		addr = (u64) sg_dma_address(sg);
		block_len = sg_dma_len(sg);
		num_trbs = count_sg_trbs_needed(urb);
	पूर्ण अन्यथा अणु
		num_trbs = count_trbs_needed(urb);
		addr = (u64) urb->transfer_dma;
		block_len = full_len;
	पूर्ण
	ret = prepare_transfer(xhci, xhci->devs[slot_id],
			ep_index, urb->stream_id,
			num_trbs, urb, 0, mem_flags);
	अगर (unlikely(ret < 0))
		वापस ret;

	urb_priv = urb->hcpriv;

	/* Deal with URB_ZERO_PACKET - need one more td/trb */
	अगर (urb->transfer_flags & URB_ZERO_PACKET && urb_priv->num_tds > 1)
		need_zero_pkt = true;

	td = &urb_priv->td[0];

	/*
	 * Don't give the first TRB to the hardware (by toggling the cycle bit)
	 * until we've finished creating all the other TRBs.  The ring's cycle
	 * state may change as we enqueue the other TRBs, so save it too.
	 */
	start_trb = &ring->enqueue->generic;
	start_cycle = ring->cycle_state;
	send_addr = addr;

	/* Queue the TRBs, even अगर they are zero-length */
	क्रम (enqd_len = 0; first_trb || enqd_len < full_len;
			enqd_len += trb_buff_len) अणु
		field = TRB_TYPE(TRB_NORMAL);

		/* TRB buffer should not cross 64KB boundaries */
		trb_buff_len = TRB_BUFF_LEN_UP_TO_BOUNDARY(addr);
		trb_buff_len = min_t(अचिन्हित पूर्णांक, trb_buff_len, block_len);

		अगर (enqd_len + trb_buff_len > full_len)
			trb_buff_len = full_len - enqd_len;

		/* Don't change the cycle bit of the first TRB until later */
		अगर (first_trb) अणु
			first_trb = false;
			अगर (start_cycle == 0)
				field |= TRB_CYCLE;
		पूर्ण अन्यथा
			field |= ring->cycle_state;

		/* Chain all the TRBs together; clear the chain bit in the last
		 * TRB to indicate it's the last TRB in the chain.
		 */
		अगर (enqd_len + trb_buff_len < full_len) अणु
			field |= TRB_CHAIN;
			अगर (trb_is_link(ring->enqueue + 1)) अणु
				अगर (xhci_align_td(xhci, urb, enqd_len,
						  &trb_buff_len,
						  ring->enq_seg)) अणु
					send_addr = ring->enq_seg->bounce_dma;
					/* assuming TD won't span 2 segs */
					td->bounce_seg = ring->enq_seg;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (enqd_len + trb_buff_len >= full_len) अणु
			field &= ~TRB_CHAIN;
			field |= TRB_IOC;
			more_trbs_coming = false;
			td->last_trb = ring->enqueue;
			td->last_trb_seg = ring->enq_seg;
			अगर (xhci_urb_suitable_क्रम_idt(urb)) अणु
				स_नकल(&send_addr, urb->transfer_buffer,
				       trb_buff_len);
				le64_to_cpus(&send_addr);
				field |= TRB_IDT;
			पूर्ण
		पूर्ण

		/* Only set पूर्णांकerrupt on लघु packet क्रम IN endpoपूर्णांकs */
		अगर (usb_urb_dir_in(urb))
			field |= TRB_ISP;

		/* Set the TRB length, TD size, and पूर्णांकerrupter fields. */
		reमुख्यder = xhci_td_reमुख्यder(xhci, enqd_len, trb_buff_len,
					      full_len, urb, more_trbs_coming);

		length_field = TRB_LEN(trb_buff_len) |
			TRB_TD_SIZE(reमुख्यder) |
			TRB_INTR_TARGET(0);

		queue_trb(xhci, ring, more_trbs_coming | need_zero_pkt,
				lower_32_bits(send_addr),
				upper_32_bits(send_addr),
				length_field,
				field);
		td->num_trbs++;
		addr += trb_buff_len;
		sent_len = trb_buff_len;

		जबतक (sg && sent_len >= block_len) अणु
			/* New sg entry */
			--num_sgs;
			sent_len -= block_len;
			sg = sg_next(sg);
			अगर (num_sgs != 0 && sg) अणु
				block_len = sg_dma_len(sg);
				addr = (u64) sg_dma_address(sg);
				addr += sent_len;
			पूर्ण
		पूर्ण
		block_len -= sent_len;
		send_addr = addr;
	पूर्ण

	अगर (need_zero_pkt) अणु
		ret = prepare_transfer(xhci, xhci->devs[slot_id],
				       ep_index, urb->stream_id,
				       1, urb, 1, mem_flags);
		urb_priv->td[1].last_trb = ring->enqueue;
		urb_priv->td[1].last_trb_seg = ring->enq_seg;
		field = TRB_TYPE(TRB_NORMAL) | ring->cycle_state | TRB_IOC;
		queue_trb(xhci, ring, 0, 0, 0, TRB_INTR_TARGET(0), field);
		urb_priv->td[1].num_trbs++;
	पूर्ण

	check_trb_math(urb, enqd_len);
	giveback_first_trb(xhci, slot_id, ep_index, urb->stream_id,
			start_cycle, start_trb);
	वापस 0;
पूर्ण

/* Caller must have locked xhci->lock */
पूर्णांक xhci_queue_ctrl_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags,
		काष्ठा urb *urb, पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index)
अणु
	काष्ठा xhci_ring *ep_ring;
	पूर्णांक num_trbs;
	पूर्णांक ret;
	काष्ठा usb_ctrlrequest *setup;
	काष्ठा xhci_generic_trb *start_trb;
	पूर्णांक start_cycle;
	u32 field;
	काष्ठा urb_priv *urb_priv;
	काष्ठा xhci_td *td;

	ep_ring = xhci_urb_to_transfer_ring(xhci, urb);
	अगर (!ep_ring)
		वापस -EINVAL;

	/*
	 * Need to copy setup packet पूर्णांकo setup TRB, so we can't use the setup
	 * DMA address.
	 */
	अगर (!urb->setup_packet)
		वापस -EINVAL;

	/* 1 TRB क्रम setup, 1 क्रम status */
	num_trbs = 2;
	/*
	 * Don't need to check अगर we need additional event data and normal TRBs,
	 * since data in control transfers will never get bigger than 16MB
	 * XXX: can we get a buffer that crosses 64KB boundaries?
	 */
	अगर (urb->transfer_buffer_length > 0)
		num_trbs++;
	ret = prepare_transfer(xhci, xhci->devs[slot_id],
			ep_index, urb->stream_id,
			num_trbs, urb, 0, mem_flags);
	अगर (ret < 0)
		वापस ret;

	urb_priv = urb->hcpriv;
	td = &urb_priv->td[0];
	td->num_trbs = num_trbs;

	/*
	 * Don't give the first TRB to the hardware (by toggling the cycle bit)
	 * until we've finished creating all the other TRBs.  The ring's cycle
	 * state may change as we enqueue the other TRBs, so save it too.
	 */
	start_trb = &ep_ring->enqueue->generic;
	start_cycle = ep_ring->cycle_state;

	/* Queue setup TRB - see section 6.4.1.2.1 */
	/* FIXME better way to translate setup_packet पूर्णांकo two u32 fields? */
	setup = (काष्ठा usb_ctrlrequest *) urb->setup_packet;
	field = 0;
	field |= TRB_IDT | TRB_TYPE(TRB_SETUP);
	अगर (start_cycle == 0)
		field |= 0x1;

	/* xHCI 1.0/1.1 6.4.1.2.1: Transfer Type field */
	अगर ((xhci->hci_version >= 0x100) || (xhci->quirks & XHCI_MTK_HOST)) अणु
		अगर (urb->transfer_buffer_length > 0) अणु
			अगर (setup->bRequestType & USB_सूची_IN)
				field |= TRB_TX_TYPE(TRB_DATA_IN);
			अन्यथा
				field |= TRB_TX_TYPE(TRB_DATA_OUT);
		पूर्ण
	पूर्ण

	queue_trb(xhci, ep_ring, true,
		  setup->bRequestType | setup->bRequest << 8 | le16_to_cpu(setup->wValue) << 16,
		  le16_to_cpu(setup->wIndex) | le16_to_cpu(setup->wLength) << 16,
		  TRB_LEN(8) | TRB_INTR_TARGET(0),
		  /* Immediate data in poपूर्णांकer */
		  field);

	/* If there's data, queue data TRBs */
	/* Only set पूर्णांकerrupt on लघु packet क्रम IN endpoपूर्णांकs */
	अगर (usb_urb_dir_in(urb))
		field = TRB_ISP | TRB_TYPE(TRB_DATA);
	अन्यथा
		field = TRB_TYPE(TRB_DATA);

	अगर (urb->transfer_buffer_length > 0) अणु
		u32 length_field, reमुख्यder;
		u64 addr;

		अगर (xhci_urb_suitable_क्रम_idt(urb)) अणु
			स_नकल(&addr, urb->transfer_buffer,
			       urb->transfer_buffer_length);
			le64_to_cpus(&addr);
			field |= TRB_IDT;
		पूर्ण अन्यथा अणु
			addr = (u64) urb->transfer_dma;
		पूर्ण

		reमुख्यder = xhci_td_reमुख्यder(xhci, 0,
				urb->transfer_buffer_length,
				urb->transfer_buffer_length,
				urb, 1);
		length_field = TRB_LEN(urb->transfer_buffer_length) |
				TRB_TD_SIZE(reमुख्यder) |
				TRB_INTR_TARGET(0);
		अगर (setup->bRequestType & USB_सूची_IN)
			field |= TRB_सूची_IN;
		queue_trb(xhci, ep_ring, true,
				lower_32_bits(addr),
				upper_32_bits(addr),
				length_field,
				field | ep_ring->cycle_state);
	पूर्ण

	/* Save the DMA address of the last TRB in the TD */
	td->last_trb = ep_ring->enqueue;
	td->last_trb_seg = ep_ring->enq_seg;

	/* Queue status TRB - see Table 7 and sections 4.11.2.2 and 6.4.1.2.3 */
	/* If the device sent data, the status stage is an OUT transfer */
	अगर (urb->transfer_buffer_length > 0 && setup->bRequestType & USB_सूची_IN)
		field = 0;
	अन्यथा
		field = TRB_सूची_IN;
	queue_trb(xhci, ep_ring, false,
			0,
			0,
			TRB_INTR_TARGET(0),
			/* Event on completion */
			field | TRB_IOC | TRB_TYPE(TRB_STATUS) | ep_ring->cycle_state);

	giveback_first_trb(xhci, slot_id, ep_index, 0,
			start_cycle, start_trb);
	वापस 0;
पूर्ण

/*
 * The transfer burst count field of the isochronous TRB defines the number of
 * bursts that are required to move all packets in this TD.  Only SuperSpeed
 * devices can burst up to bMaxBurst number of packets per service पूर्णांकerval.
 * This field is zero based, meaning a value of zero in the field means one
 * burst.  Basically, क्रम everything but SuperSpeed devices, this field will be
 * zero.  Only xHCI 1.0 host controllers support this field.
 */
अटल अचिन्हित पूर्णांक xhci_get_burst_count(काष्ठा xhci_hcd *xhci,
		काष्ठा urb *urb, अचिन्हित पूर्णांक total_packet_count)
अणु
	अचिन्हित पूर्णांक max_burst;

	अगर (xhci->hci_version < 0x100 || urb->dev->speed < USB_SPEED_SUPER)
		वापस 0;

	max_burst = urb->ep->ss_ep_comp.bMaxBurst;
	वापस DIV_ROUND_UP(total_packet_count, max_burst + 1) - 1;
पूर्ण

/*
 * Returns the number of packets in the last "burst" of packets.  This field is
 * valid क्रम all speeds of devices.  USB 2.0 devices can only करो one "burst", so
 * the last burst packet count is equal to the total number of packets in the
 * TD.  SuperSpeed endpoपूर्णांकs can have up to 3 bursts.  All but the last burst
 * must contain (bMaxBurst + 1) number of packets, but the last burst can
 * contain 1 to (bMaxBurst + 1) packets.
 */
अटल अचिन्हित पूर्णांक xhci_get_last_burst_packet_count(काष्ठा xhci_hcd *xhci,
		काष्ठा urb *urb, अचिन्हित पूर्णांक total_packet_count)
अणु
	अचिन्हित पूर्णांक max_burst;
	अचिन्हित पूर्णांक residue;

	अगर (xhci->hci_version < 0x100)
		वापस 0;

	अगर (urb->dev->speed >= USB_SPEED_SUPER) अणु
		/* bMaxBurst is zero based: 0 means 1 packet per burst */
		max_burst = urb->ep->ss_ep_comp.bMaxBurst;
		residue = total_packet_count % (max_burst + 1);
		/* If residue is zero, the last burst contains (max_burst + 1)
		 * number of packets, but the TLBPC field is zero-based.
		 */
		अगर (residue == 0)
			वापस max_burst;
		वापस residue - 1;
	पूर्ण
	अगर (total_packet_count == 0)
		वापस 0;
	वापस total_packet_count - 1;
पूर्ण

/*
 * Calculates Frame ID field of the isochronous TRB identअगरies the
 * target frame that the Interval associated with this Isochronous
 * Transfer Descriptor will start on. Refer to 4.11.2.5 in 1.1 spec.
 *
 * Returns actual frame id on success, negative value on error.
 */
अटल पूर्णांक xhci_get_isoc_frame_id(काष्ठा xhci_hcd *xhci,
		काष्ठा urb *urb, पूर्णांक index)
अणु
	पूर्णांक start_frame, ist, ret = 0;
	पूर्णांक start_frame_id, end_frame_id, current_frame_id;

	अगर (urb->dev->speed == USB_SPEED_LOW ||
			urb->dev->speed == USB_SPEED_FULL)
		start_frame = urb->start_frame + index * urb->पूर्णांकerval;
	अन्यथा
		start_frame = (urb->start_frame + index * urb->पूर्णांकerval) >> 3;

	/* Isochronous Scheduling Threshold (IST, bits 0~3 in HCSPARAMS2):
	 *
	 * If bit [3] of IST is cleared to '0', software can add a TRB no
	 * later than IST[2:0] Microframes beक्रमe that TRB is scheduled to
	 * be executed.
	 * If bit [3] of IST is set to '1', software can add a TRB no later
	 * than IST[2:0] Frames beक्रमe that TRB is scheduled to be executed.
	 */
	ist = HCS_IST(xhci->hcs_params2) & 0x7;
	अगर (HCS_IST(xhci->hcs_params2) & (1 << 3))
		ist <<= 3;

	/* Software shall not schedule an Isoch TD with a Frame ID value that
	 * is less than the Start Frame ID or greater than the End Frame ID,
	 * where:
	 *
	 * End Frame ID = (Current MFINDEX रेजिस्टर value + 895 ms.) MOD 2048
	 * Start Frame ID = (Current MFINDEX रेजिस्टर value + IST + 1) MOD 2048
	 *
	 * Both the End Frame ID and Start Frame ID values are calculated
	 * in microframes. When software determines the valid Frame ID value;
	 * The End Frame ID value should be rounded करोwn to the nearest Frame
	 * boundary, and the Start Frame ID value should be rounded up to the
	 * nearest Frame boundary.
	 */
	current_frame_id = पढ़ोl(&xhci->run_regs->microframe_index);
	start_frame_id = roundup(current_frame_id + ist + 1, 8);
	end_frame_id = roundकरोwn(current_frame_id + 895 * 8, 8);

	start_frame &= 0x7ff;
	start_frame_id = (start_frame_id >> 3) & 0x7ff;
	end_frame_id = (end_frame_id >> 3) & 0x7ff;

	xhci_dbg(xhci, "%s: index %d, reg 0x%x start_frame_id 0x%x, end_frame_id 0x%x, start_frame 0x%x\n",
		 __func__, index, पढ़ोl(&xhci->run_regs->microframe_index),
		 start_frame_id, end_frame_id, start_frame);

	अगर (start_frame_id < end_frame_id) अणु
		अगर (start_frame > end_frame_id ||
				start_frame < start_frame_id)
			ret = -EINVAL;
	पूर्ण अन्यथा अगर (start_frame_id > end_frame_id) अणु
		अगर ((start_frame > end_frame_id &&
				start_frame < start_frame_id))
			ret = -EINVAL;
	पूर्ण अन्यथा अणु
			ret = -EINVAL;
	पूर्ण

	अगर (index == 0) अणु
		अगर (ret == -EINVAL || start_frame == start_frame_id) अणु
			start_frame = start_frame_id + 1;
			अगर (urb->dev->speed == USB_SPEED_LOW ||
					urb->dev->speed == USB_SPEED_FULL)
				urb->start_frame = start_frame;
			अन्यथा
				urb->start_frame = start_frame << 3;
			ret = 0;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		xhci_warn(xhci, "Frame ID %d (reg %d, index %d) beyond range (%d, %d)\n",
				start_frame, current_frame_id, index,
				start_frame_id, end_frame_id);
		xhci_warn(xhci, "Ignore frame ID field, use SIA bit instead\n");
		वापस ret;
	पूर्ण

	वापस start_frame;
पूर्ण

/* Check अगर we should generate event पूर्णांकerrupt क्रम a TD in an isoc URB */
अटल bool trb_block_event_पूर्णांकr(काष्ठा xhci_hcd *xhci, पूर्णांक num_tds, पूर्णांक i)
अणु
	अगर (xhci->hci_version < 0x100)
		वापस false;
	/* always generate an event पूर्णांकerrupt क्रम the last TD */
	अगर (i == num_tds - 1)
		वापस false;
	/*
	 * If AVOID_BEI is set the host handles full event rings poorly,
	 * generate an event at least every 8th TD to clear the event ring
	 */
	अगर (i && xhci->quirks & XHCI_AVOID_BEI)
		वापस !!(i % 8);

	वापस true;
पूर्ण

/* This is क्रम isoc transfer */
अटल पूर्णांक xhci_queue_isoc_tx(काष्ठा xhci_hcd *xhci, gfp_t mem_flags,
		काष्ठा urb *urb, पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index)
अणु
	काष्ठा xhci_ring *ep_ring;
	काष्ठा urb_priv *urb_priv;
	काष्ठा xhci_td *td;
	पूर्णांक num_tds, trbs_per_td;
	काष्ठा xhci_generic_trb *start_trb;
	bool first_trb;
	पूर्णांक start_cycle;
	u32 field, length_field;
	पूर्णांक running_total, trb_buff_len, td_len, td_reमुख्य_len, ret;
	u64 start_addr, addr;
	पूर्णांक i, j;
	bool more_trbs_coming;
	काष्ठा xhci_virt_ep *xep;
	पूर्णांक frame_id;

	xep = &xhci->devs[slot_id]->eps[ep_index];
	ep_ring = xhci->devs[slot_id]->eps[ep_index].ring;

	num_tds = urb->number_of_packets;
	अगर (num_tds < 1) अणु
		xhci_dbg(xhci, "Isoc URB with zero packets?\n");
		वापस -EINVAL;
	पूर्ण
	start_addr = (u64) urb->transfer_dma;
	start_trb = &ep_ring->enqueue->generic;
	start_cycle = ep_ring->cycle_state;

	urb_priv = urb->hcpriv;
	/* Queue the TRBs क्रम each TD, even अगर they are zero-length */
	क्रम (i = 0; i < num_tds; i++) अणु
		अचिन्हित पूर्णांक total_pkt_count, max_pkt;
		अचिन्हित पूर्णांक burst_count, last_burst_pkt_count;
		u32 sia_frame_id;

		first_trb = true;
		running_total = 0;
		addr = start_addr + urb->iso_frame_desc[i].offset;
		td_len = urb->iso_frame_desc[i].length;
		td_reमुख्य_len = td_len;
		max_pkt = usb_endpoपूर्णांक_maxp(&urb->ep->desc);
		total_pkt_count = DIV_ROUND_UP(td_len, max_pkt);

		/* A zero-length transfer still involves at least one packet. */
		अगर (total_pkt_count == 0)
			total_pkt_count++;
		burst_count = xhci_get_burst_count(xhci, urb, total_pkt_count);
		last_burst_pkt_count = xhci_get_last_burst_packet_count(xhci,
							urb, total_pkt_count);

		trbs_per_td = count_isoc_trbs_needed(urb, i);

		ret = prepare_transfer(xhci, xhci->devs[slot_id], ep_index,
				urb->stream_id, trbs_per_td, urb, i, mem_flags);
		अगर (ret < 0) अणु
			अगर (i == 0)
				वापस ret;
			जाओ cleanup;
		पूर्ण
		td = &urb_priv->td[i];
		td->num_trbs = trbs_per_td;
		/* use SIA as शेष, अगर frame id is used overग_लिखो it */
		sia_frame_id = TRB_SIA;
		अगर (!(urb->transfer_flags & URB_ISO_ASAP) &&
		    HCC_CFC(xhci->hcc_params)) अणु
			frame_id = xhci_get_isoc_frame_id(xhci, urb, i);
			अगर (frame_id >= 0)
				sia_frame_id = TRB_FRAME_ID(frame_id);
		पूर्ण
		/*
		 * Set isoc specअगरic data क्रम the first TRB in a TD.
		 * Prevent HW from getting the TRBs by keeping the cycle state
		 * inverted in the first TDs isoc TRB.
		 */
		field = TRB_TYPE(TRB_ISOC) |
			TRB_TLBPC(last_burst_pkt_count) |
			sia_frame_id |
			(i ? ep_ring->cycle_state : !start_cycle);

		/* xhci 1.1 with ETE uses TD_Size field क्रम TBC, old is Rsvdz */
		अगर (!xep->use_extended_tbc)
			field |= TRB_TBC(burst_count);

		/* fill the rest of the TRB fields, and reमुख्यing normal TRBs */
		क्रम (j = 0; j < trbs_per_td; j++) अणु
			u32 reमुख्यder = 0;

			/* only first TRB is isoc, overग_लिखो otherwise */
			अगर (!first_trb)
				field = TRB_TYPE(TRB_NORMAL) |
					ep_ring->cycle_state;

			/* Only set पूर्णांकerrupt on लघु packet क्रम IN EPs */
			अगर (usb_urb_dir_in(urb))
				field |= TRB_ISP;

			/* Set the chain bit क्रम all except the last TRB  */
			अगर (j < trbs_per_td - 1) अणु
				more_trbs_coming = true;
				field |= TRB_CHAIN;
			पूर्ण अन्यथा अणु
				more_trbs_coming = false;
				td->last_trb = ep_ring->enqueue;
				td->last_trb_seg = ep_ring->enq_seg;
				field |= TRB_IOC;
				अगर (trb_block_event_पूर्णांकr(xhci, num_tds, i))
					field |= TRB_BEI;
			पूर्ण
			/* Calculate TRB length */
			trb_buff_len = TRB_BUFF_LEN_UP_TO_BOUNDARY(addr);
			अगर (trb_buff_len > td_reमुख्य_len)
				trb_buff_len = td_reमुख्य_len;

			/* Set the TRB length, TD size, & पूर्णांकerrupter fields. */
			reमुख्यder = xhci_td_reमुख्यder(xhci, running_total,
						   trb_buff_len, td_len,
						   urb, more_trbs_coming);

			length_field = TRB_LEN(trb_buff_len) |
				TRB_INTR_TARGET(0);

			/* xhci 1.1 with ETE uses TD Size field क्रम TBC */
			अगर (first_trb && xep->use_extended_tbc)
				length_field |= TRB_TD_SIZE_TBC(burst_count);
			अन्यथा
				length_field |= TRB_TD_SIZE(reमुख्यder);
			first_trb = false;

			queue_trb(xhci, ep_ring, more_trbs_coming,
				lower_32_bits(addr),
				upper_32_bits(addr),
				length_field,
				field);
			running_total += trb_buff_len;

			addr += trb_buff_len;
			td_reमुख्य_len -= trb_buff_len;
		पूर्ण

		/* Check TD length */
		अगर (running_total != td_len) अणु
			xhci_err(xhci, "ISOC TD length unmatch\n");
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* store the next frame id */
	अगर (HCC_CFC(xhci->hcc_params))
		xep->next_frame_id = urb->start_frame + num_tds * urb->पूर्णांकerval;

	अगर (xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs == 0) अणु
		अगर (xhci->quirks & XHCI_AMD_PLL_FIX)
			usb_amd_quirk_pll_disable();
	पूर्ण
	xhci_to_hcd(xhci)->self.bandwidth_isoc_reqs++;

	giveback_first_trb(xhci, slot_id, ep_index, urb->stream_id,
			start_cycle, start_trb);
	वापस 0;
cleanup:
	/* Clean up a partially enqueued isoc transfer. */

	क्रम (i--; i >= 0; i--)
		list_del_init(&urb_priv->td[i].td_list);

	/* Use the first TD as a temporary variable to turn the TDs we've queued
	 * पूर्णांकo No-ops with a software-owned cycle bit. That way the hardware
	 * won't accidentally start executing bogus TDs when we partially
	 * overग_लिखो them.  td->first_trb and td->start_seg are alपढ़ोy set.
	 */
	urb_priv->td[0].last_trb = ep_ring->enqueue;
	/* Every TRB except the first & last will have its cycle bit flipped. */
	td_to_noop(xhci, ep_ring, &urb_priv->td[0], true);

	/* Reset the ring enqueue back to the first TRB and its cycle bit. */
	ep_ring->enqueue = urb_priv->td[0].first_trb;
	ep_ring->enq_seg = urb_priv->td[0].start_seg;
	ep_ring->cycle_state = start_cycle;
	ep_ring->num_trbs_मुक्त = ep_ring->num_trbs_मुक्त_temp;
	usb_hcd_unlink_urb_from_ep(bus_to_hcd(urb->dev->bus), urb);
	वापस ret;
पूर्ण

/*
 * Check transfer ring to guarantee there is enough room क्रम the urb.
 * Update ISO URB start_frame and पूर्णांकerval.
 * Update पूर्णांकerval as xhci_queue_पूर्णांकr_tx करोes. Use xhci frame_index to
 * update urb->start_frame अगर URB_ISO_ASAP is set in transfer_flags or
 * Contiguous Frame ID is not supported by HC.
 */
पूर्णांक xhci_queue_isoc_tx_prepare(काष्ठा xhci_hcd *xhci, gfp_t mem_flags,
		काष्ठा urb *urb, पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index)
अणु
	काष्ठा xhci_virt_device *xdev;
	काष्ठा xhci_ring *ep_ring;
	काष्ठा xhci_ep_ctx *ep_ctx;
	पूर्णांक start_frame;
	पूर्णांक num_tds, num_trbs, i;
	पूर्णांक ret;
	काष्ठा xhci_virt_ep *xep;
	पूर्णांक ist;

	xdev = xhci->devs[slot_id];
	xep = &xhci->devs[slot_id]->eps[ep_index];
	ep_ring = xdev->eps[ep_index].ring;
	ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	num_trbs = 0;
	num_tds = urb->number_of_packets;
	क्रम (i = 0; i < num_tds; i++)
		num_trbs += count_isoc_trbs_needed(urb, i);

	/* Check the ring to guarantee there is enough room क्रम the whole urb.
	 * Do not insert any td of the urb to the ring अगर the check failed.
	 */
	ret = prepare_ring(xhci, ep_ring, GET_EP_CTX_STATE(ep_ctx),
			   num_trbs, mem_flags);
	अगर (ret)
		वापस ret;

	/*
	 * Check पूर्णांकerval value. This should be करोne beक्रमe we start to
	 * calculate the start frame value.
	 */
	check_पूर्णांकerval(xhci, urb, ep_ctx);

	/* Calculate the start frame and put it in urb->start_frame. */
	अगर (HCC_CFC(xhci->hcc_params) && !list_empty(&ep_ring->td_list)) अणु
		अगर (GET_EP_CTX_STATE(ep_ctx) ==	EP_STATE_RUNNING) अणु
			urb->start_frame = xep->next_frame_id;
			जाओ skip_start_over;
		पूर्ण
	पूर्ण

	start_frame = पढ़ोl(&xhci->run_regs->microframe_index);
	start_frame &= 0x3fff;
	/*
	 * Round up to the next frame and consider the समय beक्रमe trb really
	 * माला_लो scheduled by hardare.
	 */
	ist = HCS_IST(xhci->hcs_params2) & 0x7;
	अगर (HCS_IST(xhci->hcs_params2) & (1 << 3))
		ist <<= 3;
	start_frame += ist + XHCI_CFC_DELAY;
	start_frame = roundup(start_frame, 8);

	/*
	 * Round up to the next ESIT (Endpoपूर्णांक Service Interval Time) अगर ESIT
	 * is greate than 8 microframes.
	 */
	अगर (urb->dev->speed == USB_SPEED_LOW ||
			urb->dev->speed == USB_SPEED_FULL) अणु
		start_frame = roundup(start_frame, urb->पूर्णांकerval << 3);
		urb->start_frame = start_frame >> 3;
	पूर्ण अन्यथा अणु
		start_frame = roundup(start_frame, urb->पूर्णांकerval);
		urb->start_frame = start_frame;
	पूर्ण

skip_start_over:
	ep_ring->num_trbs_मुक्त_temp = ep_ring->num_trbs_मुक्त;

	वापस xhci_queue_isoc_tx(xhci, mem_flags, urb, slot_id, ep_index);
पूर्ण

/****		Command Ring Operations		****/

/* Generic function क्रम queueing a command TRB on the command ring.
 * Check to make sure there's room on the command ring क्रम one command TRB.
 * Also check that there's room reserved क्रम commands that must not fail.
 * If this is a command that must not fail, meaning command_must_succeed = TRUE,
 * then only check क्रम the number of reserved spots.
 * Don't decrement xhci->cmd_ring_reserved_trbs after we've queued the TRB
 * because the command event handler may want to resubmit a failed command.
 */
अटल पूर्णांक queue_command(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
			 u32 field1, u32 field2,
			 u32 field3, u32 field4, bool command_must_succeed)
अणु
	पूर्णांक reserved_trbs = xhci->cmd_ring_reserved_trbs;
	पूर्णांक ret;

	अगर ((xhci->xhc_state & XHCI_STATE_DYING) ||
		(xhci->xhc_state & XHCI_STATE_HALTED)) अणु
		xhci_dbg(xhci, "xHCI dying or halted, can't queue_command\n");
		वापस -ESHUTDOWN;
	पूर्ण

	अगर (!command_must_succeed)
		reserved_trbs++;

	ret = prepare_ring(xhci, xhci->cmd_ring, EP_STATE_RUNNING,
			reserved_trbs, GFP_ATOMIC);
	अगर (ret < 0) अणु
		xhci_err(xhci, "ERR: No room for command on command ring\n");
		अगर (command_must_succeed)
			xhci_err(xhci, "ERR: Reserved TRB counting for "
					"unfailable commands failed.\n");
		वापस ret;
	पूर्ण

	cmd->command_trb = xhci->cmd_ring->enqueue;

	/* अगर there are no other commands queued we start the समयout समयr */
	अगर (list_empty(&xhci->cmd_list)) अणु
		xhci->current_cmd = cmd;
		xhci_mod_cmd_समयr(xhci, XHCI_CMD_DEFAULT_TIMEOUT);
	पूर्ण

	list_add_tail(&cmd->cmd_list, &xhci->cmd_list);

	queue_trb(xhci, xhci->cmd_ring, false, field1, field2, field3,
			field4 | xhci->cmd_ring->cycle_state);
	वापस 0;
पूर्ण

/* Queue a slot enable or disable request on the command ring */
पूर्णांक xhci_queue_slot_control(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		u32 trb_type, u32 slot_id)
अणु
	वापस queue_command(xhci, cmd, 0, 0, 0,
			TRB_TYPE(trb_type) | SLOT_ID_FOR_TRB(slot_id), false);
पूर्ण

/* Queue an address device command TRB */
पूर्णांक xhci_queue_address_device(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		dma_addr_t in_ctx_ptr, u32 slot_id, क्रमागत xhci_setup_dev setup)
अणु
	वापस queue_command(xhci, cmd, lower_32_bits(in_ctx_ptr),
			upper_32_bits(in_ctx_ptr), 0,
			TRB_TYPE(TRB_ADDR_DEV) | SLOT_ID_FOR_TRB(slot_id)
			| (setup == SETUP_CONTEXT_ONLY ? TRB_BSR : 0), false);
पूर्ण

पूर्णांक xhci_queue_venकरोr_command(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		u32 field1, u32 field2, u32 field3, u32 field4)
अणु
	वापस queue_command(xhci, cmd, field1, field2, field3, field4, false);
पूर्ण

/* Queue a reset device command TRB */
पूर्णांक xhci_queue_reset_device(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		u32 slot_id)
अणु
	वापस queue_command(xhci, cmd, 0, 0, 0,
			TRB_TYPE(TRB_RESET_DEV) | SLOT_ID_FOR_TRB(slot_id),
			false);
पूर्ण

/* Queue a configure endpoपूर्णांक command TRB */
पूर्णांक xhci_queue_configure_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_command *cmd, dma_addr_t in_ctx_ptr,
		u32 slot_id, bool command_must_succeed)
अणु
	वापस queue_command(xhci, cmd, lower_32_bits(in_ctx_ptr),
			upper_32_bits(in_ctx_ptr), 0,
			TRB_TYPE(TRB_CONFIG_EP) | SLOT_ID_FOR_TRB(slot_id),
			command_must_succeed);
पूर्ण

/* Queue an evaluate context command TRB */
पूर्णांक xhci_queue_evaluate_context(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
		dma_addr_t in_ctx_ptr, u32 slot_id, bool command_must_succeed)
अणु
	वापस queue_command(xhci, cmd, lower_32_bits(in_ctx_ptr),
			upper_32_bits(in_ctx_ptr), 0,
			TRB_TYPE(TRB_EVAL_CONTEXT) | SLOT_ID_FOR_TRB(slot_id),
			command_must_succeed);
पूर्ण

/*
 * Suspend is set to indicate "Stop Endpoint Command" is being issued to stop
 * activity on an endpoपूर्णांक that is about to be suspended.
 */
पूर्णांक xhci_queue_stop_endpoपूर्णांक(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
			     पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index, पूर्णांक suspend)
अणु
	u32 trb_slot_id = SLOT_ID_FOR_TRB(slot_id);
	u32 trb_ep_index = EP_ID_FOR_TRB(ep_index);
	u32 type = TRB_TYPE(TRB_STOP_RING);
	u32 trb_suspend = SUSPEND_PORT_FOR_TRB(suspend);

	वापस queue_command(xhci, cmd, 0, 0, 0,
			trb_slot_id | trb_ep_index | type | trb_suspend, false);
पूर्ण

पूर्णांक xhci_queue_reset_ep(काष्ठा xhci_hcd *xhci, काष्ठा xhci_command *cmd,
			पूर्णांक slot_id, अचिन्हित पूर्णांक ep_index,
			क्रमागत xhci_ep_reset_type reset_type)
अणु
	u32 trb_slot_id = SLOT_ID_FOR_TRB(slot_id);
	u32 trb_ep_index = EP_ID_FOR_TRB(ep_index);
	u32 type = TRB_TYPE(TRB_RESET_EP);

	अगर (reset_type == EP_SOFT_RESET)
		type |= TRB_TSP;

	वापस queue_command(xhci, cmd, 0, 0, 0,
			trb_slot_id | trb_ep_index | type, false);
पूर्ण
