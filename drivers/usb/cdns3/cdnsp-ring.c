<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence CDNSP DRD Driver.
 *
 * Copyright (C) 2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 * Code based on Linux XHCI driver.
 * Origin: Copyright (C) 2008 Intel Corp
 */

/*
 * Ring initialization rules:
 * 1. Each segment is initialized to zero, except क्रम link TRBs.
 * 2. Ring cycle state = 0. This represents Producer Cycle State (PCS) or
 *    Consumer Cycle State (CCS), depending on ring function.
 * 3. Enqueue poपूर्णांकer = dequeue poपूर्णांकer = address of first TRB in the segment.
 *
 * Ring behavior rules:
 * 1. A ring is empty अगर enqueue == dequeue. This means there will always be at
 *    least one मुक्त TRB in the ring. This is useful अगर you want to turn that
 *    पूर्णांकo a link TRB and expand the ring.
 * 2. When incrementing an enqueue or dequeue poपूर्णांकer, अगर the next TRB is a
 *    link TRB, then load the poपूर्णांकer with the address in the link TRB. If the
 *    link TRB had its toggle bit set, you may need to update the ring cycle
 *    state (see cycle bit rules). You may have to करो this multiple बार
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
 * 3. Notअगरy consumer. If SW is producer, it rings the करोorbell क्रम command
 *    and endpoपूर्णांक rings. If controller is the producer क्रम the event ring,
 *    and it generates an पूर्णांकerrupt according to पूर्णांकerrupt modulation rules.
 *
 * Consumer rules:
 * 1. Check अगर TRB beदीर्घs to you. If the cycle bit == your ring cycle state,
 *    the TRB is owned by the consumer.
 * 2. Update dequeue poपूर्णांकer (which may update the ring cycle state) and
 *    जारी processing TRBs until you reach a TRB which is not owned by you.
 * 3. Notअगरy the producer. SW is the consumer क्रम the event ring, and it
 *    updates event ring dequeue poपूर्णांकer. Controller is the consumer क्रम the
 *    command and endpoपूर्णांक rings; it generates events on the event ring
 *    क्रम these.
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश "cdnsp-trace.h"
#समावेश "cdnsp-gadget.h"

/*
 * Returns zero अगर the TRB isn't in this segment, otherwise it वापसs the DMA
 * address of the TRB.
 */
dma_addr_t cdnsp_trb_virt_to_dma(काष्ठा cdnsp_segment *seg,
				 जोड़ cdnsp_trb *trb)
अणु
	अचिन्हित दीर्घ segment_offset = trb - seg->trbs;

	अगर (trb < seg->trbs || segment_offset >= TRBS_PER_SEGMENT)
		वापस 0;

	वापस seg->dma + (segment_offset * माप(*trb));
पूर्ण

अटल bool cdnsp_trb_is_noop(जोड़ cdnsp_trb *trb)
अणु
	वापस TRB_TYPE_NOOP_LE32(trb->generic.field[3]);
पूर्ण

अटल bool cdnsp_trb_is_link(जोड़ cdnsp_trb *trb)
अणु
	वापस TRB_TYPE_LINK_LE32(trb->link.control);
पूर्ण

bool cdnsp_last_trb_on_seg(काष्ठा cdnsp_segment *seg, जोड़ cdnsp_trb *trb)
अणु
	वापस trb == &seg->trbs[TRBS_PER_SEGMENT - 1];
पूर्ण

bool cdnsp_last_trb_on_ring(काष्ठा cdnsp_ring *ring,
			    काष्ठा cdnsp_segment *seg,
			    जोड़ cdnsp_trb *trb)
अणु
	वापस cdnsp_last_trb_on_seg(seg, trb) && (seg->next == ring->first_seg);
पूर्ण

अटल bool cdnsp_link_trb_toggles_cycle(जोड़ cdnsp_trb *trb)
अणु
	वापस le32_to_cpu(trb->link.control) & LINK_TOGGLE;
पूर्ण

अटल व्योम cdnsp_trb_to_noop(जोड़ cdnsp_trb *trb, u32 noop_type)
अणु
	अगर (cdnsp_trb_is_link(trb)) अणु
		/* Unchain chained link TRBs. */
		trb->link.control &= cpu_to_le32(~TRB_CHAIN);
	पूर्ण अन्यथा अणु
		trb->generic.field[0] = 0;
		trb->generic.field[1] = 0;
		trb->generic.field[2] = 0;
		/* Preserve only the cycle bit of this TRB. */
		trb->generic.field[3] &= cpu_to_le32(TRB_CYCLE);
		trb->generic.field[3] |= cpu_to_le32(TRB_TYPE(noop_type));
	पूर्ण
पूर्ण

/*
 * Updates trb to poपूर्णांक to the next TRB in the ring, and updates seg अगर the next
 * TRB is in a new segment. This करोes not skip over link TRBs, and it करोes not
 * effect the ring dequeue or enqueue poपूर्णांकers.
 */
अटल व्योम cdnsp_next_trb(काष्ठा cdnsp_device *pdev,
			   काष्ठा cdnsp_ring *ring,
			   काष्ठा cdnsp_segment **seg,
			   जोड़ cdnsp_trb **trb)
अणु
	अगर (cdnsp_trb_is_link(*trb)) अणु
		*seg = (*seg)->next;
		*trb = ((*seg)->trbs);
	पूर्ण अन्यथा अणु
		(*trb)++;
	पूर्ण
पूर्ण

/*
 * See Cycle bit rules. SW is the consumer क्रम the event ring only.
 * Don't make a ring full of link TRBs. That would be dumb and this would loop.
 */
व्योम cdnsp_inc_deq(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ring *ring)
अणु
	/* event ring करोesn't have link trbs, check क्रम last trb. */
	अगर (ring->type == TYPE_EVENT) अणु
		अगर (!cdnsp_last_trb_on_seg(ring->deq_seg, ring->dequeue)) अणु
			ring->dequeue++;
			जाओ out;
		पूर्ण

		अगर (cdnsp_last_trb_on_ring(ring, ring->deq_seg, ring->dequeue))
			ring->cycle_state ^= 1;

		ring->deq_seg = ring->deq_seg->next;
		ring->dequeue = ring->deq_seg->trbs;
		जाओ out;
	पूर्ण

	/* All other rings have link trbs. */
	अगर (!cdnsp_trb_is_link(ring->dequeue)) अणु
		ring->dequeue++;
		ring->num_trbs_मुक्त++;
	पूर्ण
	जबतक (cdnsp_trb_is_link(ring->dequeue)) अणु
		ring->deq_seg = ring->deq_seg->next;
		ring->dequeue = ring->deq_seg->trbs;
	पूर्ण
out:
	trace_cdnsp_inc_deq(ring);
पूर्ण

/*
 * See Cycle bit rules. SW is the consumer क्रम the event ring only.
 * Don't make a ring full of link TRBs. That would be dumb and this would loop.
 *
 * If we've just enqueued a TRB that is in the middle of a TD (meaning the
 * chain bit is set), then set the chain bit in all the following link TRBs.
 * If we've enqueued the last TRB in a TD, make sure the following link TRBs
 * have their chain bit cleared (so that each Link TRB is a separate TD).
 *
 * @more_trbs_coming:	Will you enqueue more TRBs beक्रमe ringing the करोorbell.
 */
अटल व्योम cdnsp_inc_enq(काष्ठा cdnsp_device *pdev,
			  काष्ठा cdnsp_ring *ring,
			  bool more_trbs_coming)
अणु
	जोड़ cdnsp_trb *next;
	u32 chain;

	chain = le32_to_cpu(ring->enqueue->generic.field[3]) & TRB_CHAIN;

	/* If this is not event ring, there is one less usable TRB. */
	अगर (!cdnsp_trb_is_link(ring->enqueue))
		ring->num_trbs_मुक्त--;
	next = ++(ring->enqueue);

	/* Update the dequeue poपूर्णांकer further अगर that was a link TRB */
	जबतक (cdnsp_trb_is_link(next)) अणु
		/*
		 * If the caller करोesn't plan on enqueuing more TDs beक्रमe
		 * ringing the करोorbell, then we करोn't want to give the link TRB
		 * to the hardware just yet. We'll give the link TRB back in
		 * cdnsp_prepare_ring() just beक्रमe we enqueue the TD at the
		 * top of the ring.
		 */
		अगर (!chain && !more_trbs_coming)
			अवरोध;

		next->link.control &= cpu_to_le32(~TRB_CHAIN);
		next->link.control |= cpu_to_le32(chain);

		/* Give this link TRB to the hardware */
		wmb();
		next->link.control ^= cpu_to_le32(TRB_CYCLE);

		/* Toggle the cycle bit after the last ring segment. */
		अगर (cdnsp_link_trb_toggles_cycle(next))
			ring->cycle_state ^= 1;

		ring->enq_seg = ring->enq_seg->next;
		ring->enqueue = ring->enq_seg->trbs;
		next = ring->enqueue;
	पूर्ण

	trace_cdnsp_inc_enq(ring);
पूर्ण

/*
 * Check to see अगर there's room to enqueue num_trbs on the ring and make sure
 * enqueue poपूर्णांकer will not advance पूर्णांकo dequeue segment.
 */
अटल bool cdnsp_room_on_ring(काष्ठा cdnsp_device *pdev,
			       काष्ठा cdnsp_ring *ring,
			       अचिन्हित पूर्णांक num_trbs)
अणु
	पूर्णांक num_trbs_in_deq_seg;

	अगर (ring->num_trbs_मुक्त < num_trbs)
		वापस false;

	अगर (ring->type != TYPE_COMMAND && ring->type != TYPE_EVENT) अणु
		num_trbs_in_deq_seg = ring->dequeue - ring->deq_seg->trbs;

		अगर (ring->num_trbs_मुक्त < num_trbs + num_trbs_in_deq_seg)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Workaround क्रम L1: controller has issue with resuming from L1 after
 * setting करोorbell क्रम endpoपूर्णांक during L1 state. This function क्रमces
 * resume संकेत in such हाल.
 */
अटल व्योम cdnsp_क्रमce_l0_go(काष्ठा cdnsp_device *pdev)
अणु
	अगर (pdev->active_port == &pdev->usb2_port && pdev->gadget.lpm_capable)
		cdnsp_set_link_state(pdev, &pdev->active_port->regs->portsc, XDEV_U0);
पूर्ण

/* Ring the करोorbell after placing a command on the ring. */
व्योम cdnsp_ring_cmd_db(काष्ठा cdnsp_device *pdev)
अणु
	ग_लिखोl(DB_VALUE_CMD, &pdev->dba->cmd_db);
पूर्ण

/*
 * Ring the करोorbell after placing a transfer on the ring.
 * Returns true अगर करोorbell was set, otherwise false.
 */
अटल bool cdnsp_ring_ep_करोorbell(काष्ठा cdnsp_device *pdev,
				   काष्ठा cdnsp_ep *pep,
				   अचिन्हित पूर्णांक stream_id)
अणु
	__le32 __iomem *reg_addr = &pdev->dba->ep_db;
	अचिन्हित पूर्णांक ep_state = pep->ep_state;
	अचिन्हित पूर्णांक db_value;

	/*
	 * Don't ring the करोorbell क्रम this endpoपूर्णांक अगर endpoपूर्णांक is halted or
	 * disabled.
	 */
	अगर (ep_state & EP_HALTED || !(ep_state & EP_ENABLED))
		वापस false;

	/* For stream capable endpoपूर्णांकs driver can ring करोorbell only twice. */
	अगर (pep->ep_state & EP_HAS_STREAMS) अणु
		अगर (pep->stream_info.drbls_count >= 2)
			वापस false;

		pep->stream_info.drbls_count++;
	पूर्ण

	pep->ep_state &= ~EP_STOPPED;

	अगर (pep->idx == 0 && pdev->ep0_stage == CDNSP_DATA_STAGE &&
	    !pdev->ep0_expect_in)
		db_value = DB_VALUE_EP0_OUT(pep->idx, stream_id);
	अन्यथा
		db_value = DB_VALUE(pep->idx, stream_id);

	trace_cdnsp_tr_drbl(pep, stream_id);

	ग_लिखोl(db_value, reg_addr);

	cdnsp_क्रमce_l0_go(pdev);

	/* Doorbell was set. */
	वापस true;
पूर्ण

/*
 * Get the right ring क्रम the given pep and stream_id.
 * If the endpoपूर्णांक supports streams, boundary check the USB request's stream ID.
 * If the endpoपूर्णांक करोesn't support streams, वापस the singular endpoपूर्णांक ring.
 */
अटल काष्ठा cdnsp_ring *cdnsp_get_transfer_ring(काष्ठा cdnsp_device *pdev,
						  काष्ठा cdnsp_ep *pep,
						  अचिन्हित पूर्णांक stream_id)
अणु
	अगर (!(pep->ep_state & EP_HAS_STREAMS))
		वापस pep->ring;

	अगर (stream_id == 0 || stream_id >= pep->stream_info.num_streams) अणु
		dev_err(pdev->dev, "ERR: %s ring doesn't exist for SID: %d.\n",
			pep->name, stream_id);
		वापस शून्य;
	पूर्ण

	वापस pep->stream_info.stream_rings[stream_id];
पूर्ण

अटल काष्ठा cdnsp_ring *
	cdnsp_request_to_transfer_ring(काष्ठा cdnsp_device *pdev,
				       काष्ठा cdnsp_request *preq)
अणु
	वापस cdnsp_get_transfer_ring(pdev, preq->pep,
				       preq->request.stream_id);
पूर्ण

/* Ring the करोorbell क्रम any rings with pending requests. */
व्योम cdnsp_ring_करोorbell_क्रम_active_rings(काष्ठा cdnsp_device *pdev,
					  काष्ठा cdnsp_ep *pep)
अणु
	काष्ठा cdnsp_stream_info *stream_info;
	अचिन्हित पूर्णांक stream_id;
	पूर्णांक ret;

	अगर (pep->ep_state & EP_DIS_IN_RROGRESS)
		वापस;

	/* A ring has pending Request अगर its TD list is not empty. */
	अगर (!(pep->ep_state & EP_HAS_STREAMS) && pep->number) अणु
		अगर (pep->ring && !list_empty(&pep->ring->td_list))
			cdnsp_ring_ep_करोorbell(pdev, pep, 0);
		वापस;
	पूर्ण

	stream_info = &pep->stream_info;

	क्रम (stream_id = 1; stream_id < stream_info->num_streams; stream_id++) अणु
		काष्ठा cdnsp_td *td, *td_temp;
		काष्ठा cdnsp_ring *ep_ring;

		अगर (stream_info->drbls_count >= 2)
			वापस;

		ep_ring = cdnsp_get_transfer_ring(pdev, pep, stream_id);
		अगर (!ep_ring)
			जारी;

		अगर (!ep_ring->stream_active || ep_ring->stream_rejected)
			जारी;

		list_क्रम_each_entry_safe(td, td_temp, &ep_ring->td_list,
					 td_list) अणु
			अगर (td->drbl)
				जारी;

			ret = cdnsp_ring_ep_करोorbell(pdev, pep, stream_id);
			अगर (ret)
				td->drbl = 1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Get the hw dequeue poपूर्णांकer controller stopped on, either directly from the
 * endpoपूर्णांक context, or अगर streams are in use from the stream context.
 * The वापसed hw_dequeue contains the lowest four bits with cycle state
 * and possible stream context type.
 */
अटल u64 cdnsp_get_hw_deq(काष्ठा cdnsp_device *pdev,
			    अचिन्हित पूर्णांक ep_index,
			    अचिन्हित पूर्णांक stream_id)
अणु
	काष्ठा cdnsp_stream_ctx *st_ctx;
	काष्ठा cdnsp_ep *pep;

	pep = &pdev->eps[stream_id];

	अगर (pep->ep_state & EP_HAS_STREAMS) अणु
		st_ctx = &pep->stream_info.stream_ctx_array[stream_id];
		वापस le64_to_cpu(st_ctx->stream_ring);
	पूर्ण

	वापस le64_to_cpu(pep->out_ctx->deq);
पूर्ण

/*
 * Move the controller endpoपूर्णांक ring dequeue poपूर्णांकer past cur_td.
 * Record the new state of the controller endpoपूर्णांक ring dequeue segment,
 * dequeue poपूर्णांकer, and new consumer cycle state in state.
 * Update पूर्णांकernal representation of the ring's dequeue poपूर्णांकer.
 *
 * We करो this in three jumps:
 *  - First we update our new ring state to be the same as when the
 *    controller stopped.
 *  - Then we traverse the ring to find the segment that contains
 *    the last TRB in the TD. We toggle the controller new cycle state
 *    when we pass any link TRBs with the toggle cycle bit set.
 *  - Finally we move the dequeue state one TRB further, toggling the cycle bit
 *    अगर we've moved it past a link TRB with the toggle cycle bit set.
 */
अटल व्योम cdnsp_find_new_dequeue_state(काष्ठा cdnsp_device *pdev,
					 काष्ठा cdnsp_ep *pep,
					 अचिन्हित पूर्णांक stream_id,
					 काष्ठा cdnsp_td *cur_td,
					 काष्ठा cdnsp_dequeue_state *state)
अणु
	bool td_last_trb_found = false;
	काष्ठा cdnsp_segment *new_seg;
	काष्ठा cdnsp_ring *ep_ring;
	जोड़ cdnsp_trb *new_deq;
	bool cycle_found = false;
	u64 hw_dequeue;

	ep_ring = cdnsp_get_transfer_ring(pdev, pep, stream_id);
	अगर (!ep_ring)
		वापस;

	/*
	 * Dig out the cycle state saved by the controller during the
	 * stop endpoपूर्णांक command.
	 */
	hw_dequeue = cdnsp_get_hw_deq(pdev, pep->idx, stream_id);
	new_seg = ep_ring->deq_seg;
	new_deq = ep_ring->dequeue;
	state->new_cycle_state = hw_dequeue & 0x1;
	state->stream_id = stream_id;

	/*
	 * We want to find the poपूर्णांकer, segment and cycle state of the new trb
	 * (the one after current TD's last_trb). We know the cycle state at
	 * hw_dequeue, so walk the ring until both hw_dequeue and last_trb are
	 * found.
	 */
	करो अणु
		अगर (!cycle_found && cdnsp_trb_virt_to_dma(new_seg, new_deq)
		    == (dma_addr_t)(hw_dequeue & ~0xf)) अणु
			cycle_found = true;

			अगर (td_last_trb_found)
				अवरोध;
		पूर्ण

		अगर (new_deq == cur_td->last_trb)
			td_last_trb_found = true;

		अगर (cycle_found && cdnsp_trb_is_link(new_deq) &&
		    cdnsp_link_trb_toggles_cycle(new_deq))
			state->new_cycle_state ^= 0x1;

		cdnsp_next_trb(pdev, ep_ring, &new_seg, &new_deq);

		/* Search wrapped around, bail out. */
		अगर (new_deq == pep->ring->dequeue) अणु
			dev_err(pdev->dev,
				"Error: Failed finding new dequeue state\n");
			state->new_deq_seg = शून्य;
			state->new_deq_ptr = शून्य;
			वापस;
		पूर्ण

	पूर्ण जबतक (!cycle_found || !td_last_trb_found);

	state->new_deq_seg = new_seg;
	state->new_deq_ptr = new_deq;

	trace_cdnsp_new_deq_state(state);
पूर्ण

/*
 * flip_cycle means flip the cycle bit of all but the first and last TRB.
 * (The last TRB actually poपूर्णांकs to the ring enqueue poपूर्णांकer, which is not part
 * of this TD.) This is used to हटाओ partially enqueued isoc TDs from a ring.
 */
अटल व्योम cdnsp_td_to_noop(काष्ठा cdnsp_device *pdev,
			     काष्ठा cdnsp_ring *ep_ring,
			     काष्ठा cdnsp_td *td,
			     bool flip_cycle)
अणु
	काष्ठा cdnsp_segment *seg = td->start_seg;
	जोड़ cdnsp_trb *trb = td->first_trb;

	जबतक (1) अणु
		cdnsp_trb_to_noop(trb, TRB_TR_NOOP);

		/* flip cycle अगर asked to */
		अगर (flip_cycle && trb != td->first_trb && trb != td->last_trb)
			trb->generic.field[3] ^= cpu_to_le32(TRB_CYCLE);

		अगर (trb == td->last_trb)
			अवरोध;

		cdnsp_next_trb(pdev, ep_ring, &seg, &trb);
	पूर्ण
पूर्ण

/*
 * This TD is defined by the TRBs starting at start_trb in start_seg and ending
 * at end_trb, which may be in another segment. If the suspect DMA address is a
 * TRB in this TD, this function वापसs that TRB's segment. Otherwise it
 * वापसs 0.
 */
अटल काष्ठा cdnsp_segment *cdnsp_trb_in_td(काष्ठा cdnsp_device *pdev,
					     काष्ठा cdnsp_segment *start_seg,
					     जोड़ cdnsp_trb *start_trb,
					     जोड़ cdnsp_trb *end_trb,
					     dma_addr_t suspect_dma)
अणु
	काष्ठा cdnsp_segment *cur_seg;
	जोड़ cdnsp_trb *temp_trb;
	dma_addr_t end_seg_dma;
	dma_addr_t end_trb_dma;
	dma_addr_t start_dma;

	start_dma = cdnsp_trb_virt_to_dma(start_seg, start_trb);
	cur_seg = start_seg;

	करो अणु
		अगर (start_dma == 0)
			वापस शून्य;

		temp_trb = &cur_seg->trbs[TRBS_PER_SEGMENT - 1];
		/* We may get an event क्रम a Link TRB in the middle of a TD */
		end_seg_dma = cdnsp_trb_virt_to_dma(cur_seg, temp_trb);
		/* If the end TRB isn't in this segment, this is set to 0 */
		end_trb_dma = cdnsp_trb_virt_to_dma(cur_seg, end_trb);

		trace_cdnsp_looking_trb_in_td(suspect_dma, start_dma,
					      end_trb_dma, cur_seg->dma,
					      end_seg_dma);

		अगर (end_trb_dma > 0) अणु
			/*
			 * The end TRB is in this segment, so suspect should
			 * be here
			 */
			अगर (start_dma <= end_trb_dma) अणु
				अगर (suspect_dma >= start_dma &&
				    suspect_dma <= end_trb_dma) अणु
					वापस cur_seg;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * Case क्रम one segment with a
				 * TD wrapped around to the top
				 */
				अगर ((suspect_dma >= start_dma &&
				     suspect_dma <= end_seg_dma) ||
				    (suspect_dma >= cur_seg->dma &&
				     suspect_dma <= end_trb_dma)) अणु
					वापस cur_seg;
				पूर्ण
			पूर्ण

			वापस शून्य;
		पूर्ण

		/* Might still be somewhere in this segment */
		अगर (suspect_dma >= start_dma && suspect_dma <= end_seg_dma)
			वापस cur_seg;

		cur_seg = cur_seg->next;
		start_dma = cdnsp_trb_virt_to_dma(cur_seg, &cur_seg->trbs[0]);
	पूर्ण जबतक (cur_seg != start_seg);

	वापस शून्य;
पूर्ण

अटल व्योम cdnsp_unmap_td_bounce_buffer(काष्ठा cdnsp_device *pdev,
					 काष्ठा cdnsp_ring *ring,
					 काष्ठा cdnsp_td *td)
अणु
	काष्ठा cdnsp_segment *seg = td->bounce_seg;
	काष्ठा cdnsp_request *preq;
	माप_प्रकार len;

	अगर (!seg)
		वापस;

	preq = td->preq;

	trace_cdnsp_bounce_unmap(td->preq, seg->bounce_len, seg->bounce_offs,
				 seg->bounce_dma, 0);

	अगर (!preq->direction) अणु
		dma_unmap_single(pdev->dev, seg->bounce_dma,
				 ring->bounce_buf_len,  DMA_TO_DEVICE);
		वापस;
	पूर्ण

	dma_unmap_single(pdev->dev, seg->bounce_dma, ring->bounce_buf_len,
			 DMA_FROM_DEVICE);

	/* For in transfers we need to copy the data from bounce to sg */
	len = sg_pcopy_from_buffer(preq->request.sg, preq->request.num_sgs,
				   seg->bounce_buf, seg->bounce_len,
				   seg->bounce_offs);
	अगर (len != seg->bounce_len)
		dev_warn(pdev->dev, "WARN Wrong bounce buffer read length: %zu != %d\n",
			 len, seg->bounce_len);

	seg->bounce_len = 0;
	seg->bounce_offs = 0;
पूर्ण

अटल पूर्णांक cdnsp_cmd_set_deq(काष्ठा cdnsp_device *pdev,
			     काष्ठा cdnsp_ep *pep,
			     काष्ठा cdnsp_dequeue_state *deq_state)
अणु
	काष्ठा cdnsp_ring *ep_ring;
	पूर्णांक ret;

	अगर (!deq_state->new_deq_ptr || !deq_state->new_deq_seg) अणु
		cdnsp_ring_करोorbell_क्रम_active_rings(pdev, pep);
		वापस 0;
	पूर्ण

	cdnsp_queue_new_dequeue_state(pdev, pep, deq_state);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);

	trace_cdnsp_handle_cmd_set_deq(cdnsp_get_slot_ctx(&pdev->out_ctx));
	trace_cdnsp_handle_cmd_set_deq_ep(pep->out_ctx);

	/*
	 * Update the ring's dequeue segment and dequeue poपूर्णांकer
	 * to reflect the new position.
	 */
	ep_ring = cdnsp_get_transfer_ring(pdev, pep, deq_state->stream_id);

	अगर (cdnsp_trb_is_link(ep_ring->dequeue)) अणु
		ep_ring->deq_seg = ep_ring->deq_seg->next;
		ep_ring->dequeue = ep_ring->deq_seg->trbs;
	पूर्ण

	जबतक (ep_ring->dequeue != deq_state->new_deq_ptr) अणु
		ep_ring->num_trbs_मुक्त++;
		ep_ring->dequeue++;

		अगर (cdnsp_trb_is_link(ep_ring->dequeue)) अणु
			अगर (ep_ring->dequeue == deq_state->new_deq_ptr)
				अवरोध;

			ep_ring->deq_seg = ep_ring->deq_seg->next;
			ep_ring->dequeue = ep_ring->deq_seg->trbs;
		पूर्ण
	पूर्ण

	/*
	 * Probably there was TIMEOUT during handling Set Dequeue Poपूर्णांकer
	 * command. It's critical error and controller will be stopped.
	 */
	अगर (ret)
		वापस -ESHUTDOWN;

	/* Restart any rings with pending requests */
	cdnsp_ring_करोorbell_क्रम_active_rings(pdev, pep);

	वापस 0;
पूर्ण

पूर्णांक cdnsp_हटाओ_request(काष्ठा cdnsp_device *pdev,
			 काष्ठा cdnsp_request *preq,
			 काष्ठा cdnsp_ep *pep)
अणु
	काष्ठा cdnsp_dequeue_state deq_state;
	काष्ठा cdnsp_td *cur_td = शून्य;
	काष्ठा cdnsp_ring *ep_ring;
	काष्ठा cdnsp_segment *seg;
	पूर्णांक status = -ECONNRESET;
	पूर्णांक ret = 0;
	u64 hw_deq;

	स_रखो(&deq_state, 0, माप(deq_state));

	trace_cdnsp_हटाओ_request(pep->out_ctx);
	trace_cdnsp_हटाओ_request_td(preq);

	cur_td = &preq->td;
	ep_ring = cdnsp_request_to_transfer_ring(pdev, preq);

	/*
	 * If we stopped on the TD we need to cancel, then we have to
	 * move the controller endpoपूर्णांक ring dequeue poपूर्णांकer past
	 * this TD.
	 */
	hw_deq = cdnsp_get_hw_deq(pdev, pep->idx, preq->request.stream_id);
	hw_deq &= ~0xf;

	seg = cdnsp_trb_in_td(pdev, cur_td->start_seg, cur_td->first_trb,
			      cur_td->last_trb, hw_deq);

	अगर (seg && (pep->ep_state & EP_ENABLED))
		cdnsp_find_new_dequeue_state(pdev, pep, preq->request.stream_id,
					     cur_td, &deq_state);
	अन्यथा
		cdnsp_td_to_noop(pdev, ep_ring, cur_td, false);

	/*
	 * The event handler won't see a completion क्रम this TD anymore,
	 * so हटाओ it from the endpoपूर्णांक ring's TD list.
	 */
	list_del_init(&cur_td->td_list);
	ep_ring->num_tds--;
	pep->stream_info.td_count--;

	/*
	 * During disconnecting all endpoपूर्णांक will be disabled so we करोn't
	 * have to worry about updating dequeue poपूर्णांकer.
	 */
	अगर (pdev->cdnsp_state & CDNSP_STATE_DISCONNECT_PENDING) अणु
		status = -ESHUTDOWN;
		ret = cdnsp_cmd_set_deq(pdev, pep, &deq_state);
	पूर्ण

	cdnsp_unmap_td_bounce_buffer(pdev, ep_ring, cur_td);
	cdnsp_gadget_giveback(pep, cur_td->preq, status);

	वापस ret;
पूर्ण

अटल पूर्णांक cdnsp_update_port_id(काष्ठा cdnsp_device *pdev, u32 port_id)
अणु
	काष्ठा cdnsp_port *port = pdev->active_port;
	u8 old_port = 0;

	अगर (port && port->port_num == port_id)
		वापस 0;

	अगर (port)
		old_port = port->port_num;

	अगर (port_id == pdev->usb2_port.port_num) अणु
		port = &pdev->usb2_port;
	पूर्ण अन्यथा अगर (port_id == pdev->usb3_port.port_num) अणु
		port  = &pdev->usb3_port;
	पूर्ण अन्यथा अणु
		dev_err(pdev->dev, "Port event with invalid port ID %d\n",
			port_id);
		वापस -EINVAL;
	पूर्ण

	अगर (port_id != old_port) अणु
		cdnsp_disable_slot(pdev);
		pdev->active_port = port;
		cdnsp_enable_slot(pdev);
	पूर्ण

	अगर (port_id == pdev->usb2_port.port_num)
		cdnsp_set_usb2_hardware_lpm(pdev, शून्य, 1);
	अन्यथा
		ग_लिखोl(PORT_U1_TIMEOUT(1) | PORT_U2_TIMEOUT(1),
		       &pdev->usb3_port.regs->portpmsc);

	वापस 0;
पूर्ण

अटल व्योम cdnsp_handle_port_status(काष्ठा cdnsp_device *pdev,
				     जोड़ cdnsp_trb *event)
अणु
	काष्ठा cdnsp_port_regs __iomem *port_regs;
	u32 portsc, cmd_regs;
	bool port2 = false;
	u32 link_state;
	u32 port_id;

	/* Port status change events always have a successful completion code */
	अगर (GET_COMP_CODE(le32_to_cpu(event->generic.field[2])) != COMP_SUCCESS)
		dev_err(pdev->dev, "ERR: incorrect PSC event\n");

	port_id = GET_PORT_ID(le32_to_cpu(event->generic.field[0]));

	अगर (cdnsp_update_port_id(pdev, port_id))
		जाओ cleanup;

	port_regs = pdev->active_port->regs;

	अगर (port_id == pdev->usb2_port.port_num)
		port2 = true;

new_event:
	portsc = पढ़ोl(&port_regs->portsc);
	ग_लिखोl(cdnsp_port_state_to_neutral(portsc) |
	       (portsc & PORT_CHANGE_BITS), &port_regs->portsc);

	trace_cdnsp_handle_port_status(pdev->active_port->port_num, portsc);

	pdev->gadget.speed = cdnsp_port_speed(portsc);
	link_state = portsc & PORT_PLS_MASK;

	/* Port Link State change detected. */
	अगर ((portsc & PORT_PLC)) अणु
		अगर (!(pdev->cdnsp_state & CDNSP_WAKEUP_PENDING)  &&
		    link_state == XDEV_RESUME) अणु
			cmd_regs = पढ़ोl(&pdev->op_regs->command);
			अगर (!(cmd_regs & CMD_R_S))
				जाओ cleanup;

			अगर (DEV_SUPERSPEED_ANY(portsc)) अणु
				cdnsp_set_link_state(pdev, &port_regs->portsc,
						     XDEV_U0);

				cdnsp_resume_gadget(pdev);
			पूर्ण
		पूर्ण

		अगर ((pdev->cdnsp_state & CDNSP_WAKEUP_PENDING) &&
		    link_state == XDEV_U0) अणु
			pdev->cdnsp_state &= ~CDNSP_WAKEUP_PENDING;

			cdnsp_क्रमce_header_wakeup(pdev, 1);
			cdnsp_ring_cmd_db(pdev);
			cdnsp_रुको_क्रम_cmd_compl(pdev);
		पूर्ण

		अगर (link_state == XDEV_U0 && pdev->link_state == XDEV_U3 &&
		    !DEV_SUPERSPEED_ANY(portsc))
			cdnsp_resume_gadget(pdev);

		अगर (link_state == XDEV_U3 &&  pdev->link_state != XDEV_U3)
			cdnsp_suspend_gadget(pdev);

		pdev->link_state = link_state;
	पूर्ण

	अगर (portsc & PORT_CSC) अणु
		/* Detach device. */
		अगर (pdev->gadget.connected && !(portsc & PORT_CONNECT))
			cdnsp_disconnect_gadget(pdev);

		/* Attach device. */
		अगर (portsc & PORT_CONNECT) अणु
			अगर (!port2)
				cdnsp_irq_reset(pdev);

			usb_gadget_set_state(&pdev->gadget, USB_STATE_ATTACHED);
		पूर्ण
	पूर्ण

	/* Port reset. */
	अगर ((portsc & (PORT_RC | PORT_WRC)) && (portsc & PORT_CONNECT)) अणु
		cdnsp_irq_reset(pdev);
		pdev->u1_allowed = 0;
		pdev->u2_allowed = 0;
		pdev->may_wakeup = 0;
	पूर्ण

	अगर (portsc & PORT_CEC)
		dev_err(pdev->dev, "Port Over Current detected\n");

	अगर (portsc & PORT_CEC)
		dev_err(pdev->dev, "Port Configure Error detected\n");

	अगर (पढ़ोl(&port_regs->portsc) & PORT_CHANGE_BITS)
		जाओ new_event;

cleanup:
	cdnsp_inc_deq(pdev, pdev->event_ring);
पूर्ण

अटल व्योम cdnsp_td_cleanup(काष्ठा cdnsp_device *pdev,
			     काष्ठा cdnsp_td *td,
			     काष्ठा cdnsp_ring *ep_ring,
			     पूर्णांक *status)
अणु
	काष्ठा cdnsp_request *preq = td->preq;

	/* अगर a bounce buffer was used to align this td then unmap it */
	cdnsp_unmap_td_bounce_buffer(pdev, ep_ring, td);

	/*
	 * If the controller said we transferred more data than the buffer
	 * length, Play it safe and say we didn't transfer anything.
	 */
	अगर (preq->request.actual > preq->request.length) अणु
		preq->request.actual = 0;
		*status = 0;
	पूर्ण

	list_del_init(&td->td_list);
	ep_ring->num_tds--;
	preq->pep->stream_info.td_count--;

	cdnsp_gadget_giveback(preq->pep, preq, *status);
पूर्ण

अटल व्योम cdnsp_finish_td(काष्ठा cdnsp_device *pdev,
			    काष्ठा cdnsp_td *td,
			    काष्ठा cdnsp_transfer_event *event,
			    काष्ठा cdnsp_ep *ep,
			    पूर्णांक *status)
अणु
	काष्ठा cdnsp_ring *ep_ring;
	u32 trb_comp_code;

	ep_ring = cdnsp_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));

	अगर (trb_comp_code == COMP_STOPPED_LENGTH_INVALID ||
	    trb_comp_code == COMP_STOPPED ||
	    trb_comp_code == COMP_STOPPED_SHORT_PACKET) अणु
		/*
		 * The Endpoपूर्णांक Stop Command completion will take care of any
		 * stopped TDs. A stopped TD may be restarted, so करोn't update
		 * the ring dequeue poपूर्णांकer or take this TD off any lists yet.
		 */
		वापस;
	पूर्ण

	/* Update ring dequeue poपूर्णांकer */
	जबतक (ep_ring->dequeue != td->last_trb)
		cdnsp_inc_deq(pdev, ep_ring);

	cdnsp_inc_deq(pdev, ep_ring);

	cdnsp_td_cleanup(pdev, td, ep_ring, status);
पूर्ण

/* sum trb lengths from ring dequeue up to stop_trb, _excluding_ stop_trb */
अटल पूर्णांक cdnsp_sum_trb_lengths(काष्ठा cdnsp_device *pdev,
				 काष्ठा cdnsp_ring *ring,
				 जोड़ cdnsp_trb *stop_trb)
अणु
	काष्ठा cdnsp_segment *seg = ring->deq_seg;
	जोड़ cdnsp_trb *trb = ring->dequeue;
	u32 sum;

	क्रम (sum = 0; trb != stop_trb; cdnsp_next_trb(pdev, ring, &seg, &trb)) अणु
		अगर (!cdnsp_trb_is_noop(trb) && !cdnsp_trb_is_link(trb))
			sum += TRB_LEN(le32_to_cpu(trb->generic.field[2]));
	पूर्ण
	वापस sum;
पूर्ण

अटल पूर्णांक cdnsp_giveback_first_trb(काष्ठा cdnsp_device *pdev,
				    काष्ठा cdnsp_ep *pep,
				    अचिन्हित पूर्णांक stream_id,
				    पूर्णांक start_cycle,
				    काष्ठा cdnsp_generic_trb *start_trb)
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

	अगर ((pep->ep_state & EP_HAS_STREAMS) &&
	    !pep->stream_info.first_prime_det) अणु
		trace_cdnsp_रुको_क्रम_prime(pep, stream_id);
		वापस 0;
	पूर्ण

	वापस cdnsp_ring_ep_करोorbell(pdev, pep, stream_id);
पूर्ण

/*
 * Process control tds, update USB request status and actual_length.
 */
अटल व्योम cdnsp_process_ctrl_td(काष्ठा cdnsp_device *pdev,
				  काष्ठा cdnsp_td *td,
				  जोड़ cdnsp_trb *event_trb,
				  काष्ठा cdnsp_transfer_event *event,
				  काष्ठा cdnsp_ep *pep,
				  पूर्णांक *status)
अणु
	काष्ठा cdnsp_ring *ep_ring;
	u32 reमुख्यing;
	u32 trb_type;

	trb_type = TRB_FIELD_TO_TYPE(le32_to_cpu(event_trb->generic.field[3]));
	ep_ring = cdnsp_dma_to_transfer_ring(pep, le64_to_cpu(event->buffer));
	reमुख्यing = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));

	/*
	 * अगर on data stage then update the actual_length of the USB
	 * request and flag it as set, so it won't be overwritten in the event
	 * क्रम the last TRB.
	 */
	अगर (trb_type == TRB_DATA) अणु
		td->request_length_set = true;
		td->preq->request.actual = td->preq->request.length - reमुख्यing;
	पूर्ण

	/* at status stage */
	अगर (!td->request_length_set)
		td->preq->request.actual = td->preq->request.length;

	अगर (pdev->ep0_stage == CDNSP_DATA_STAGE && pep->number == 0 &&
	    pdev->three_stage_setup) अणु
		td = list_entry(ep_ring->td_list.next, काष्ठा cdnsp_td,
				td_list);
		pdev->ep0_stage = CDNSP_STATUS_STAGE;

		cdnsp_giveback_first_trb(pdev, pep, 0, ep_ring->cycle_state,
					 &td->last_trb->generic);
		वापस;
	पूर्ण

	cdnsp_finish_td(pdev, td, event, pep, status);
पूर्ण

/*
 * Process isochronous tds, update usb request status and actual_length.
 */
अटल व्योम cdnsp_process_isoc_td(काष्ठा cdnsp_device *pdev,
				  काष्ठा cdnsp_td *td,
				  जोड़ cdnsp_trb *ep_trb,
				  काष्ठा cdnsp_transfer_event *event,
				  काष्ठा cdnsp_ep *pep,
				  पूर्णांक status)
अणु
	काष्ठा cdnsp_request *preq = td->preq;
	u32 reमुख्यing, requested, ep_trb_len;
	bool sum_trbs_क्रम_length = false;
	काष्ठा cdnsp_ring *ep_ring;
	u32 trb_comp_code;
	u32 td_length;

	ep_ring = cdnsp_dma_to_transfer_ring(pep, le64_to_cpu(event->buffer));
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	reमुख्यing = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
	ep_trb_len = TRB_LEN(le32_to_cpu(ep_trb->generic.field[2]));

	requested = preq->request.length;

	/* handle completion code */
	चयन (trb_comp_code) अणु
	हाल COMP_SUCCESS:
		preq->request.status = 0;
		अवरोध;
	हाल COMP_SHORT_PACKET:
		preq->request.status = 0;
		sum_trbs_क्रम_length = true;
		अवरोध;
	हाल COMP_ISOCH_BUFFER_OVERRUN:
	हाल COMP_BABBLE_DETECTED_ERROR:
		preq->request.status = -EOVERFLOW;
		अवरोध;
	हाल COMP_STOPPED:
		sum_trbs_क्रम_length = true;
		अवरोध;
	हाल COMP_STOPPED_SHORT_PACKET:
		/* field normally containing residue now contains transferred */
		preq->request.status  = 0;
		requested = reमुख्यing;
		अवरोध;
	हाल COMP_STOPPED_LENGTH_INVALID:
		requested = 0;
		reमुख्यing = 0;
		अवरोध;
	शेष:
		sum_trbs_क्रम_length = true;
		preq->request.status = -1;
		अवरोध;
	पूर्ण

	अगर (sum_trbs_क्रम_length) अणु
		td_length = cdnsp_sum_trb_lengths(pdev, ep_ring, ep_trb);
		td_length += ep_trb_len - reमुख्यing;
	पूर्ण अन्यथा अणु
		td_length = requested;
	पूर्ण

	td->preq->request.actual += td_length;

	cdnsp_finish_td(pdev, td, event, pep, &status);
पूर्ण

अटल व्योम cdnsp_skip_isoc_td(काष्ठा cdnsp_device *pdev,
			       काष्ठा cdnsp_td *td,
			       काष्ठा cdnsp_transfer_event *event,
			       काष्ठा cdnsp_ep *pep,
			       पूर्णांक status)
अणु
	काष्ठा cdnsp_ring *ep_ring;

	ep_ring = cdnsp_dma_to_transfer_ring(pep, le64_to_cpu(event->buffer));
	td->preq->request.status = -EXDEV;
	td->preq->request.actual = 0;

	/* Update ring dequeue poपूर्णांकer */
	जबतक (ep_ring->dequeue != td->last_trb)
		cdnsp_inc_deq(pdev, ep_ring);

	cdnsp_inc_deq(pdev, ep_ring);

	cdnsp_td_cleanup(pdev, td, ep_ring, &status);
पूर्ण

/*
 * Process bulk and पूर्णांकerrupt tds, update usb request status and actual_length.
 */
अटल व्योम cdnsp_process_bulk_पूर्णांकr_td(काष्ठा cdnsp_device *pdev,
				       काष्ठा cdnsp_td *td,
				       जोड़ cdnsp_trb *ep_trb,
				       काष्ठा cdnsp_transfer_event *event,
				       काष्ठा cdnsp_ep *ep,
				       पूर्णांक *status)
अणु
	u32 reमुख्यing, requested, ep_trb_len;
	काष्ठा cdnsp_ring *ep_ring;
	u32 trb_comp_code;

	ep_ring = cdnsp_dma_to_transfer_ring(ep, le64_to_cpu(event->buffer));
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	reमुख्यing = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));
	ep_trb_len = TRB_LEN(le32_to_cpu(ep_trb->generic.field[2]));
	requested = td->preq->request.length;

	चयन (trb_comp_code) अणु
	हाल COMP_SUCCESS:
	हाल COMP_SHORT_PACKET:
		*status = 0;
		अवरोध;
	हाल COMP_STOPPED_SHORT_PACKET:
		td->preq->request.actual = reमुख्यing;
		जाओ finish_td;
	हाल COMP_STOPPED_LENGTH_INVALID:
		/* Stopped on ep trb with invalid length, exclude it. */
		ep_trb_len = 0;
		reमुख्यing = 0;
		अवरोध;
	पूर्ण

	अगर (ep_trb == td->last_trb)
		ep_trb_len = requested - reमुख्यing;
	अन्यथा
		ep_trb_len = cdnsp_sum_trb_lengths(pdev, ep_ring, ep_trb) +
						   ep_trb_len - reमुख्यing;
	td->preq->request.actual = ep_trb_len;

finish_td:
	ep->stream_info.drbls_count--;

	cdnsp_finish_td(pdev, td, event, ep, status);
पूर्ण

अटल व्योम cdnsp_handle_tx_nrdy(काष्ठा cdnsp_device *pdev,
				 काष्ठा cdnsp_transfer_event *event)
अणु
	काष्ठा cdnsp_generic_trb *generic;
	काष्ठा cdnsp_ring *ep_ring;
	काष्ठा cdnsp_ep *pep;
	पूर्णांक cur_stream;
	पूर्णांक ep_index;
	पूर्णांक host_sid;
	पूर्णांक dev_sid;

	generic = (काष्ठा cdnsp_generic_trb *)event;
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	dev_sid = TRB_TO_DEV_STREAM(le32_to_cpu(generic->field[0]));
	host_sid = TRB_TO_HOST_STREAM(le32_to_cpu(generic->field[2]));

	pep = &pdev->eps[ep_index];

	अगर (!(pep->ep_state & EP_HAS_STREAMS))
		वापस;

	अगर (host_sid == STREAM_PRIME_ACK) अणु
		pep->stream_info.first_prime_det = 1;
		क्रम (cur_stream = 1; cur_stream < pep->stream_info.num_streams;
		    cur_stream++) अणु
			ep_ring = pep->stream_info.stream_rings[cur_stream];
			ep_ring->stream_active = 1;
			ep_ring->stream_rejected = 0;
		पूर्ण
	पूर्ण

	अगर (host_sid == STREAM_REJECTED) अणु
		काष्ठा cdnsp_td *td, *td_temp;

		pep->stream_info.drbls_count--;
		ep_ring = pep->stream_info.stream_rings[dev_sid];
		ep_ring->stream_active = 0;
		ep_ring->stream_rejected = 1;

		list_क्रम_each_entry_safe(td, td_temp, &ep_ring->td_list,
					 td_list) अणु
			td->drbl = 0;
		पूर्ण
	पूर्ण

	cdnsp_ring_करोorbell_क्रम_active_rings(pdev, pep);
पूर्ण

/*
 * If this function वापसs an error condition, it means it got a Transfer
 * event with a corrupted TRB DMA address or endpoपूर्णांक is disabled.
 */
अटल पूर्णांक cdnsp_handle_tx_event(काष्ठा cdnsp_device *pdev,
				 काष्ठा cdnsp_transfer_event *event)
अणु
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	bool handling_skipped_tds = false;
	काष्ठा cdnsp_segment *ep_seg;
	काष्ठा cdnsp_ring *ep_ring;
	पूर्णांक status = -EINPROGRESS;
	जोड़ cdnsp_trb *ep_trb;
	dma_addr_t ep_trb_dma;
	काष्ठा cdnsp_ep *pep;
	काष्ठा cdnsp_td *td;
	u32 trb_comp_code;
	पूर्णांक invalidate;
	पूर्णांक ep_index;

	invalidate = le32_to_cpu(event->flags) & TRB_EVENT_INVALIDATE;
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	ep_trb_dma = le64_to_cpu(event->buffer);

	pep = &pdev->eps[ep_index];
	ep_ring = cdnsp_dma_to_transfer_ring(pep, le64_to_cpu(event->buffer));

	/*
	 * If device is disconnect then all requests will be dequeued
	 * by upper layers as part of disconnect sequence.
	 * We करोn't want handle such event to aव्योम racing.
	 */
	अगर (invalidate || !pdev->gadget.connected)
		जाओ cleanup;

	अगर (GET_EP_CTX_STATE(pep->out_ctx) == EP_STATE_DISABLED) अणु
		trace_cdnsp_ep_disabled(pep->out_ctx);
		जाओ err_out;
	पूर्ण

	/* Some transfer events करोn't always poपूर्णांक to a trb*/
	अगर (!ep_ring) अणु
		चयन (trb_comp_code) अणु
		हाल COMP_INVALID_STREAM_TYPE_ERROR:
		हाल COMP_INVALID_STREAM_ID_ERROR:
		हाल COMP_RING_UNDERRUN:
		हाल COMP_RING_OVERRUN:
			जाओ cleanup;
		शेष:
			dev_err(pdev->dev, "ERROR: %s event for unknown ring\n",
				pep->name);
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Look क्रम some error हालs that need special treaपंचांगent. */
	चयन (trb_comp_code) अणु
	हाल COMP_BABBLE_DETECTED_ERROR:
		status = -EOVERFLOW;
		अवरोध;
	हाल COMP_RING_UNDERRUN:
	हाल COMP_RING_OVERRUN:
		/*
		 * When the Isoch ring is empty, the controller will generate
		 * a Ring Overrun Event क्रम IN Isoch endpoपूर्णांक or Ring
		 * Underrun Event क्रम OUT Isoch endpoपूर्णांक.
		 */
		जाओ cleanup;
	हाल COMP_MISSED_SERVICE_ERROR:
		/*
		 * When encounter missed service error, one or more isoc tds
		 * may be missed by controller.
		 * Set skip flag of the ep_ring; Complete the missed tds as
		 * लघु transfer when process the ep_ring next समय.
		 */
		pep->skip = true;
		अवरोध;
	पूर्ण

	करो अणु
		/*
		 * This TRB should be in the TD at the head of this ring's TD
		 * list.
		 */
		अगर (list_empty(&ep_ring->td_list)) अणु
			/*
			 * Don't print warnings if it's due to a stopped
			 * endpoपूर्णांक generating an extra completion event, or
			 * a event क्रम the last TRB of a लघु TD we alपढ़ोy
			 * got a लघु event क्रम.
			 * The लघु TD is alपढ़ोy हटाओd from the TD list.
			 */
			अगर (!(trb_comp_code == COMP_STOPPED ||
			      trb_comp_code == COMP_STOPPED_LENGTH_INVALID ||
			      ep_ring->last_td_was_लघु))
				trace_cdnsp_trb_without_td(ep_ring,
					(काष्ठा cdnsp_generic_trb *)event);

			अगर (pep->skip) अणु
				pep->skip = false;
				trace_cdnsp_ep_list_empty_with_skip(pep, 0);
			पूर्ण

			जाओ cleanup;
		पूर्ण

		td = list_entry(ep_ring->td_list.next, काष्ठा cdnsp_td,
				td_list);

		/* Is this a TRB in the currently executing TD? */
		ep_seg = cdnsp_trb_in_td(pdev, ep_ring->deq_seg,
					 ep_ring->dequeue, td->last_trb,
					 ep_trb_dma);

		/*
		 * Skip the Force Stopped Event. The event_trb(ep_trb_dma)
		 * of FSE is not in the current TD poपूर्णांकed by ep_ring->dequeue
		 * because that the hardware dequeue poपूर्णांकer still at the
		 * previous TRB of the current TD. The previous TRB maybe a
		 * Link TD or the last TRB of the previous TD. The command
		 * completion handle will take care the rest.
		 */
		अगर (!ep_seg && (trb_comp_code == COMP_STOPPED ||
				trb_comp_code == COMP_STOPPED_LENGTH_INVALID)) अणु
			pep->skip = false;
			जाओ cleanup;
		पूर्ण

		desc = td->preq->pep->endpoपूर्णांक.desc;
		अगर (!ep_seg) अणु
			अगर (!pep->skip || !usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
				/* Something is busted, give up! */
				dev_err(pdev->dev,
					"ERROR Transfer event TRB DMA ptr not "
					"part of current TD ep_index %d "
					"comp_code %u\n", ep_index,
					trb_comp_code);
				वापस -EINVAL;
			पूर्ण

			cdnsp_skip_isoc_td(pdev, td, event, pep, status);
			जाओ cleanup;
		पूर्ण

		अगर (trb_comp_code == COMP_SHORT_PACKET)
			ep_ring->last_td_was_लघु = true;
		अन्यथा
			ep_ring->last_td_was_लघु = false;

		अगर (pep->skip) अणु
			pep->skip = false;
			cdnsp_skip_isoc_td(pdev, td, event, pep, status);
			जाओ cleanup;
		पूर्ण

		ep_trb = &ep_seg->trbs[(ep_trb_dma - ep_seg->dma)
				       / माप(*ep_trb)];

		trace_cdnsp_handle_transfer(ep_ring,
					    (काष्ठा cdnsp_generic_trb *)ep_trb);

		अगर (cdnsp_trb_is_noop(ep_trb))
			जाओ cleanup;

		अगर (usb_endpoपूर्णांक_xfer_control(desc))
			cdnsp_process_ctrl_td(pdev, td, ep_trb, event, pep,
					      &status);
		अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(desc))
			cdnsp_process_isoc_td(pdev, td, ep_trb, event, pep,
					      status);
		अन्यथा
			cdnsp_process_bulk_पूर्णांकr_td(pdev, td, ep_trb, event, pep,
						   &status);
cleanup:
		handling_skipped_tds = pep->skip;

		/*
		 * Do not update event ring dequeue poपूर्णांकer अगर we're in a loop
		 * processing missed tds.
		 */
		अगर (!handling_skipped_tds)
			cdnsp_inc_deq(pdev, pdev->event_ring);

	/*
	 * If ep->skip is set, it means there are missed tds on the
	 * endpoपूर्णांक ring need to take care of.
	 * Process them as लघु transfer until reach the td poपूर्णांकed by
	 * the event.
	 */
	पूर्ण जबतक (handling_skipped_tds);
	वापस 0;

err_out:
	dev_err(pdev->dev, "@%016llx %08x %08x %08x %08x\n",
		(अचिन्हित दीर्घ दीर्घ)
		cdnsp_trb_virt_to_dma(pdev->event_ring->deq_seg,
				      pdev->event_ring->dequeue),
		 lower_32_bits(le64_to_cpu(event->buffer)),
		 upper_32_bits(le64_to_cpu(event->buffer)),
		 le32_to_cpu(event->transfer_len),
		 le32_to_cpu(event->flags));
	वापस -EINVAL;
पूर्ण

/*
 * This function handles all events on the event ring.
 * Returns true क्रम "possibly more events to process" (caller should call
 * again), otherwise false अगर करोne.
 */
अटल bool cdnsp_handle_event(काष्ठा cdnsp_device *pdev)
अणु
	अचिन्हित पूर्णांक comp_code;
	जोड़ cdnsp_trb *event;
	bool update_ptrs = true;
	u32 cycle_bit;
	पूर्णांक ret = 0;
	u32 flags;

	event = pdev->event_ring->dequeue;
	flags = le32_to_cpu(event->event_cmd.flags);
	cycle_bit = (flags & TRB_CYCLE);

	/* Does the controller or driver own the TRB? */
	अगर (cycle_bit != pdev->event_ring->cycle_state)
		वापस false;

	trace_cdnsp_handle_event(pdev->event_ring, &event->generic);

	/*
	 * Barrier between पढ़ोing the TRB_CYCLE (valid) flag above and any
	 * पढ़ोs of the event's flags/data below.
	 */
	rmb();

	चयन (flags & TRB_TYPE_BITMASK) अणु
	हाल TRB_TYPE(TRB_COMPLETION):
		/*
		 * Command can't be handled in पूर्णांकerrupt context so just
		 * increment command ring dequeue poपूर्णांकer.
		 */
		cdnsp_inc_deq(pdev, pdev->cmd_ring);
		अवरोध;
	हाल TRB_TYPE(TRB_PORT_STATUS):
		cdnsp_handle_port_status(pdev, event);
		update_ptrs = false;
		अवरोध;
	हाल TRB_TYPE(TRB_TRANSFER):
		ret = cdnsp_handle_tx_event(pdev, &event->trans_event);
		अगर (ret >= 0)
			update_ptrs = false;
		अवरोध;
	हाल TRB_TYPE(TRB_SETUP):
		pdev->ep0_stage = CDNSP_SETUP_STAGE;
		pdev->setup_id = TRB_SETUPID_TO_TYPE(flags);
		pdev->setup_speed = TRB_SETUP_SPEEDID(flags);
		pdev->setup = *((काष्ठा usb_ctrlrequest *)
				&event->trans_event.buffer);

		cdnsp_setup_analyze(pdev);
		अवरोध;
	हाल TRB_TYPE(TRB_ENDPOINT_NRDY):
		cdnsp_handle_tx_nrdy(pdev, &event->trans_event);
		अवरोध;
	हाल TRB_TYPE(TRB_HC_EVENT): अणु
		comp_code = GET_COMP_CODE(le32_to_cpu(event->generic.field[2]));

		चयन (comp_code) अणु
		हाल COMP_EVENT_RING_FULL_ERROR:
			dev_err(pdev->dev, "Event Ring Full\n");
			अवरोध;
		शेष:
			dev_err(pdev->dev, "Controller error code 0x%02x\n",
				comp_code);
		पूर्ण

		अवरोध;
	पूर्ण
	हाल TRB_TYPE(TRB_MFINDEX_WRAP):
	हाल TRB_TYPE(TRB_DRB_OVERFLOW):
		अवरोध;
	शेष:
		dev_warn(pdev->dev, "ERROR unknown event type %ld\n",
			 TRB_FIELD_TO_TYPE(flags));
	पूर्ण

	अगर (update_ptrs)
		/* Update SW event ring dequeue poपूर्णांकer. */
		cdnsp_inc_deq(pdev, pdev->event_ring);

	/*
	 * Caller will call us again to check अगर there are more items
	 * on the event ring.
	 */
	वापस true;
पूर्ण

irqवापस_t cdnsp_thपढ़ो_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdnsp_device *pdev = (काष्ठा cdnsp_device *)data;
	जोड़ cdnsp_trb *event_ring_deq;
	अचिन्हित दीर्घ flags;
	पूर्णांक counter = 0;

	spin_lock_irqsave(&pdev->lock, flags);

	अगर (pdev->cdnsp_state & (CDNSP_STATE_HALTED | CDNSP_STATE_DYING)) अणु
		cdnsp_died(pdev);
		spin_unlock_irqrestore(&pdev->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	event_ring_deq = pdev->event_ring->dequeue;

	जबतक (cdnsp_handle_event(pdev)) अणु
		अगर (++counter >= TRBS_PER_EV_DEQ_UPDATE) अणु
			cdnsp_update_erst_dequeue(pdev, event_ring_deq, 0);
			event_ring_deq = pdev->event_ring->dequeue;
			counter = 0;
		पूर्ण
	पूर्ण

	cdnsp_update_erst_dequeue(pdev, event_ring_deq, 1);

	spin_unlock_irqrestore(&pdev->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t cdnsp_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा cdnsp_device *pdev = (काष्ठा cdnsp_device *)priv;
	u32 irq_pending;
	u32 status;

	status = पढ़ोl(&pdev->op_regs->status);

	अगर (status == ~(u32)0) अणु
		cdnsp_died(pdev);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!(status & STS_EINT))
		वापस IRQ_NONE;

	ग_लिखोl(status | STS_EINT, &pdev->op_regs->status);
	irq_pending = पढ़ोl(&pdev->ir_set->irq_pending);
	irq_pending |= IMAN_IP;
	ग_लिखोl(irq_pending, &pdev->ir_set->irq_pending);

	अगर (status & STS_FATAL) अणु
		cdnsp_died(pdev);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

/*
 * Generic function क्रम queuing a TRB on a ring.
 * The caller must have checked to make sure there's room on the ring.
 *
 * @more_trbs_coming:	Will you enqueue more TRBs beक्रमe setting करोorbell?
 */
अटल व्योम cdnsp_queue_trb(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ring *ring,
			    bool more_trbs_coming, u32 field1, u32 field2,
			    u32 field3, u32 field4)
अणु
	काष्ठा cdnsp_generic_trb *trb;

	trb = &ring->enqueue->generic;

	trb->field[0] = cpu_to_le32(field1);
	trb->field[1] = cpu_to_le32(field2);
	trb->field[2] = cpu_to_le32(field3);
	trb->field[3] = cpu_to_le32(field4);

	trace_cdnsp_queue_trb(ring, trb);
	cdnsp_inc_enq(pdev, ring, more_trbs_coming);
पूर्ण

/*
 * Does various checks on the endpoपूर्णांक ring, and makes it पढ़ोy to
 * queue num_trbs.
 */
अटल पूर्णांक cdnsp_prepare_ring(काष्ठा cdnsp_device *pdev,
			      काष्ठा cdnsp_ring *ep_ring,
			      u32 ep_state, अचिन्हित
			      पूर्णांक num_trbs,
			      gfp_t mem_flags)
अणु
	अचिन्हित पूर्णांक num_trbs_needed;

	/* Make sure the endpoपूर्णांक has been added to controller schedule. */
	चयन (ep_state) अणु
	हाल EP_STATE_STOPPED:
	हाल EP_STATE_RUNNING:
	हाल EP_STATE_HALTED:
		अवरोध;
	शेष:
		dev_err(pdev->dev, "ERROR: incorrect endpoint state\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (1) अणु
		अगर (cdnsp_room_on_ring(pdev, ep_ring, num_trbs))
			अवरोध;

		trace_cdnsp_no_room_on_ring("try ring expansion");

		num_trbs_needed = num_trbs - ep_ring->num_trbs_मुक्त;
		अगर (cdnsp_ring_expansion(pdev, ep_ring, num_trbs_needed,
					 mem_flags)) अणु
			dev_err(pdev->dev, "Ring expansion failed\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	जबतक (cdnsp_trb_is_link(ep_ring->enqueue)) अणु
		ep_ring->enqueue->link.control |= cpu_to_le32(TRB_CHAIN);
		/* The cycle bit must be set as the last operation. */
		wmb();
		ep_ring->enqueue->link.control ^= cpu_to_le32(TRB_CYCLE);

		/* Toggle the cycle bit after the last ring segment. */
		अगर (cdnsp_link_trb_toggles_cycle(ep_ring->enqueue))
			ep_ring->cycle_state ^= 1;
		ep_ring->enq_seg = ep_ring->enq_seg->next;
		ep_ring->enqueue = ep_ring->enq_seg->trbs;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_prepare_transfer(काष्ठा cdnsp_device *pdev,
				  काष्ठा cdnsp_request *preq,
				  अचिन्हित पूर्णांक num_trbs)
अणु
	काष्ठा cdnsp_ring *ep_ring;
	पूर्णांक ret;

	ep_ring = cdnsp_get_transfer_ring(pdev, preq->pep,
					  preq->request.stream_id);
	अगर (!ep_ring)
		वापस -EINVAL;

	ret = cdnsp_prepare_ring(pdev, ep_ring,
				 GET_EP_CTX_STATE(preq->pep->out_ctx),
				 num_trbs, GFP_ATOMIC);
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&preq->td.td_list);
	preq->td.preq = preq;

	/* Add this TD to the tail of the endpoपूर्णांक ring's TD list. */
	list_add_tail(&preq->td.td_list, &ep_ring->td_list);
	ep_ring->num_tds++;
	preq->pep->stream_info.td_count++;

	preq->td.start_seg = ep_ring->enq_seg;
	preq->td.first_trb = ep_ring->enqueue;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक cdnsp_count_trbs(u64 addr, u64 len)
अणु
	अचिन्हित पूर्णांक num_trbs;

	num_trbs = DIV_ROUND_UP(len + (addr & (TRB_MAX_BUFF_SIZE - 1)),
				TRB_MAX_BUFF_SIZE);
	अगर (num_trbs == 0)
		num_trbs++;

	वापस num_trbs;
पूर्ण

अटल अचिन्हित पूर्णांक count_trbs_needed(काष्ठा cdnsp_request *preq)
अणु
	वापस cdnsp_count_trbs(preq->request.dma, preq->request.length);
पूर्ण

अटल अचिन्हित पूर्णांक count_sg_trbs_needed(काष्ठा cdnsp_request *preq)
अणु
	अचिन्हित पूर्णांक i, len, full_len, num_trbs = 0;
	काष्ठा scatterlist *sg;

	full_len = preq->request.length;

	क्रम_each_sg(preq->request.sg, sg, preq->request.num_sgs, i) अणु
		len = sg_dma_len(sg);
		num_trbs += cdnsp_count_trbs(sg_dma_address(sg), len);
		len = min(len, full_len);
		full_len -= len;
		अगर (full_len == 0)
			अवरोध;
	पूर्ण

	वापस num_trbs;
पूर्ण

अटल अचिन्हित पूर्णांक count_isoc_trbs_needed(काष्ठा cdnsp_request *preq)
अणु
	वापस cdnsp_count_trbs(preq->request.dma, preq->request.length);
पूर्ण

अटल व्योम cdnsp_check_trb_math(काष्ठा cdnsp_request *preq, पूर्णांक running_total)
अणु
	अगर (running_total != preq->request.length)
		dev_err(preq->pep->pdev->dev,
			"%s - Miscalculated tx length, "
			"queued %#x, asked for %#x (%d)\n",
			preq->pep->name, running_total,
			preq->request.length, preq->request.actual);
पूर्ण

/*
 * TD size is the number of max packet sized packets reमुख्यing in the TD
 * (*not* including this TRB).
 *
 * Total TD packet count = total_packet_count =
 *     DIV_ROUND_UP(TD size in bytes / wMaxPacketSize)
 *
 * Packets transferred up to and including this TRB = packets_transferred =
 *     roundकरोwn(total bytes transferred including this TRB / wMaxPacketSize)
 *
 * TD size = total_packet_count - packets_transferred
 *
 * It must fit in bits 21:17, so it can't be bigger than 31.
 * This is taken care of in the TRB_TD_SIZE() macro
 *
 * The last TRB in a TD must have the TD size set to zero.
 */
अटल u32 cdnsp_td_reमुख्यder(काष्ठा cdnsp_device *pdev,
			      पूर्णांक transferred,
			      पूर्णांक trb_buff_len,
			      अचिन्हित पूर्णांक td_total_len,
			      काष्ठा cdnsp_request *preq,
			      bool more_trbs_coming)
अणु
	u32 maxp, total_packet_count;

	/* One TRB with a zero-length data packet. */
	अगर (!more_trbs_coming || (transferred == 0 && trb_buff_len == 0) ||
	    trb_buff_len == td_total_len)
		वापस 0;

	maxp = usb_endpoपूर्णांक_maxp(preq->pep->endpoपूर्णांक.desc);
	total_packet_count = DIV_ROUND_UP(td_total_len, maxp);

	/* Queuing functions करोn't count the current TRB पूर्णांकo transferred. */
	वापस (total_packet_count - ((transferred + trb_buff_len) / maxp));
पूर्ण

अटल पूर्णांक cdnsp_align_td(काष्ठा cdnsp_device *pdev,
			  काष्ठा cdnsp_request *preq, u32 enqd_len,
			  u32 *trb_buff_len, काष्ठा cdnsp_segment *seg)
अणु
	काष्ठा device *dev = pdev->dev;
	अचिन्हित पूर्णांक unalign;
	अचिन्हित पूर्णांक max_pkt;
	u32 new_buff_len;

	max_pkt = usb_endpoपूर्णांक_maxp(preq->pep->endpoपूर्णांक.desc);
	unalign = (enqd_len + *trb_buff_len) % max_pkt;

	/* We got lucky, last normal TRB data on segment is packet aligned. */
	अगर (unalign == 0)
		वापस 0;

	/* Is the last nornal TRB alignable by splitting it. */
	अगर (*trb_buff_len > unalign) अणु
		*trb_buff_len -= unalign;
		trace_cdnsp_bounce_align_td_split(preq, *trb_buff_len,
						  enqd_len, 0, unalign);
		वापस 0;
	पूर्ण

	/*
	 * We want enqd_len + trb_buff_len to sum up to a number aligned to
	 * number which is भागisible by the endpoपूर्णांक's wMaxPacketSize. IOW:
	 * (size of currently enqueued TRBs + reमुख्यder) % wMaxPacketSize == 0.
	 */
	new_buff_len = max_pkt - (enqd_len % max_pkt);

	अगर (new_buff_len > (preq->request.length - enqd_len))
		new_buff_len = (preq->request.length - enqd_len);

	/* Create a max max_pkt sized bounce buffer poपूर्णांकed to by last trb. */
	अगर (preq->direction) अणु
		sg_pcopy_to_buffer(preq->request.sg,
				   preq->request.num_mapped_sgs,
				   seg->bounce_buf, new_buff_len, enqd_len);
		seg->bounce_dma = dma_map_single(dev, seg->bounce_buf,
						 max_pkt, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		seg->bounce_dma = dma_map_single(dev, seg->bounce_buf,
						 max_pkt, DMA_FROM_DEVICE);
	पूर्ण

	अगर (dma_mapping_error(dev, seg->bounce_dma)) अणु
		/* Try without aligning.*/
		dev_warn(pdev->dev,
			 "Failed mapping bounce buffer, not aligning\n");
		वापस 0;
	पूर्ण

	*trb_buff_len = new_buff_len;
	seg->bounce_len = new_buff_len;
	seg->bounce_offs = enqd_len;

	trace_cdnsp_bounce_map(preq, new_buff_len, enqd_len, seg->bounce_dma,
			       unalign);

	/*
	 * Bounce buffer successful aligned and seg->bounce_dma will be used
	 * in transfer TRB as new transfer buffer address.
	 */
	वापस 1;
पूर्ण

पूर्णांक cdnsp_queue_bulk_tx(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_request *preq)
अणु
	अचिन्हित पूर्णांक enqd_len, block_len, trb_buff_len, full_len;
	अचिन्हित पूर्णांक start_cycle, num_sgs = 0;
	काष्ठा cdnsp_generic_trb *start_trb;
	u32 field, length_field, reमुख्यder;
	काष्ठा scatterlist *sg = शून्य;
	bool more_trbs_coming = true;
	bool need_zero_pkt = false;
	bool zero_len_trb = false;
	काष्ठा cdnsp_ring *ring;
	bool first_trb = true;
	अचिन्हित पूर्णांक num_trbs;
	काष्ठा cdnsp_ep *pep;
	u64 addr, send_addr;
	पूर्णांक sent_len, ret;

	ring = cdnsp_request_to_transfer_ring(pdev, preq);
	अगर (!ring)
		वापस -EINVAL;

	full_len = preq->request.length;

	अगर (preq->request.num_sgs) अणु
		num_sgs = preq->request.num_sgs;
		sg = preq->request.sg;
		addr = (u64)sg_dma_address(sg);
		block_len = sg_dma_len(sg);
		num_trbs = count_sg_trbs_needed(preq);
	पूर्ण अन्यथा अणु
		num_trbs = count_trbs_needed(preq);
		addr = (u64)preq->request.dma;
		block_len = full_len;
	पूर्ण

	pep = preq->pep;

	/* Deal with request.zero - need one more td/trb. */
	अगर (preq->request.zero && preq->request.length &&
	    IS_ALIGNED(full_len, usb_endpoपूर्णांक_maxp(pep->endpoपूर्णांक.desc))) अणु
		need_zero_pkt = true;
		num_trbs++;
	पूर्ण

	ret = cdnsp_prepare_transfer(pdev, preq, num_trbs);
	अगर (ret)
		वापस ret;

	/*
	 * Don't give the first TRB to the hardware (by toggling the cycle bit)
	 * until we've finished creating all the other TRBs. The ring's cycle
	 * state may change as we enqueue the other TRBs, so save it too.
	 */
	start_trb = &ring->enqueue->generic;
	start_cycle = ring->cycle_state;
	send_addr = addr;

	/* Queue the TRBs, even अगर they are zero-length */
	क्रम (enqd_len = 0; zero_len_trb || first_trb || enqd_len < full_len;
	     enqd_len += trb_buff_len) अणु
		field = TRB_TYPE(TRB_NORMAL);

		/* TRB buffer should not cross 64KB boundaries */
		trb_buff_len = TRB_BUFF_LEN_UP_TO_BOUNDARY(addr);
		trb_buff_len = min(trb_buff_len, block_len);
		अगर (enqd_len + trb_buff_len > full_len)
			trb_buff_len = full_len - enqd_len;

		/* Don't change the cycle bit of the first TRB until later */
		अगर (first_trb) अणु
			first_trb = false;
			अगर (start_cycle == 0)
				field |= TRB_CYCLE;
		पूर्ण अन्यथा अणु
			field |= ring->cycle_state;
		पूर्ण

		/*
		 * Chain all the TRBs together; clear the chain bit in the last
		 * TRB to indicate it's the last TRB in the chain.
		 */
		अगर (enqd_len + trb_buff_len < full_len || need_zero_pkt) अणु
			field |= TRB_CHAIN;
			अगर (cdnsp_trb_is_link(ring->enqueue + 1)) अणु
				अगर (cdnsp_align_td(pdev, preq, enqd_len,
						   &trb_buff_len,
						   ring->enq_seg)) अणु
					send_addr = ring->enq_seg->bounce_dma;
					/* Assuming TD won't span 2 segs */
					preq->td.bounce_seg = ring->enq_seg;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (enqd_len + trb_buff_len >= full_len) अणु
			अगर (need_zero_pkt && zero_len_trb) अणु
				zero_len_trb = true;
			पूर्ण अन्यथा अणु
				field &= ~TRB_CHAIN;
				field |= TRB_IOC;
				more_trbs_coming = false;
				need_zero_pkt = false;
				preq->td.last_trb = ring->enqueue;
			पूर्ण
		पूर्ण

		/* Only set पूर्णांकerrupt on लघु packet क्रम OUT endpoपूर्णांकs. */
		अगर (!preq->direction)
			field |= TRB_ISP;

		/* Set the TRB length, TD size, and पूर्णांकerrupter fields. */
		reमुख्यder = cdnsp_td_reमुख्यder(pdev, enqd_len, trb_buff_len,
					       full_len, preq,
					       more_trbs_coming);

		length_field = TRB_LEN(trb_buff_len) | TRB_TD_SIZE(reमुख्यder) |
			TRB_INTR_TARGET(0);

		cdnsp_queue_trb(pdev, ring, more_trbs_coming | need_zero_pkt,
				lower_32_bits(send_addr),
				upper_32_bits(send_addr),
				length_field,
				field);

		addr += trb_buff_len;
		sent_len = trb_buff_len;
		जबतक (sg && sent_len >= block_len) अणु
			/* New sg entry */
			--num_sgs;
			sent_len -= block_len;
			अगर (num_sgs != 0) अणु
				sg = sg_next(sg);
				block_len = sg_dma_len(sg);
				addr = (u64)sg_dma_address(sg);
				addr += sent_len;
			पूर्ण
		पूर्ण
		block_len -= sent_len;
		send_addr = addr;
	पूर्ण

	cdnsp_check_trb_math(preq, enqd_len);
	ret = cdnsp_giveback_first_trb(pdev, pep, preq->request.stream_id,
				       start_cycle, start_trb);

	अगर (ret)
		preq->td.drbl = 1;

	वापस 0;
पूर्ण

पूर्णांक cdnsp_queue_ctrl_tx(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_request *preq)
अणु
	u32 field, length_field, reमुख्यder;
	काष्ठा cdnsp_ep *pep = preq->pep;
	काष्ठा cdnsp_ring *ep_ring;
	पूर्णांक num_trbs;
	पूर्णांक ret;

	ep_ring = cdnsp_request_to_transfer_ring(pdev, preq);
	अगर (!ep_ring)
		वापस -EINVAL;

	/* 1 TRB क्रम data, 1 क्रम status */
	num_trbs = (pdev->three_stage_setup) ? 2 : 1;

	ret = cdnsp_prepare_transfer(pdev, preq, num_trbs);
	अगर (ret)
		वापस ret;

	/* If there's data, queue data TRBs */
	अगर (pdev->ep0_expect_in)
		field = TRB_TYPE(TRB_DATA) | TRB_IOC;
	अन्यथा
		field = TRB_ISP | TRB_TYPE(TRB_DATA) | TRB_IOC;

	अगर (preq->request.length > 0) अणु
		reमुख्यder = cdnsp_td_reमुख्यder(pdev, 0, preq->request.length,
					       preq->request.length, preq, 1);

		length_field = TRB_LEN(preq->request.length) |
				TRB_TD_SIZE(reमुख्यder) | TRB_INTR_TARGET(0);

		अगर (pdev->ep0_expect_in)
			field |= TRB_सूची_IN;

		cdnsp_queue_trb(pdev, ep_ring, true,
				lower_32_bits(preq->request.dma),
				upper_32_bits(preq->request.dma), length_field,
				field | ep_ring->cycle_state |
				TRB_SETUPID(pdev->setup_id) |
				pdev->setup_speed);

		pdev->ep0_stage = CDNSP_DATA_STAGE;
	पूर्ण

	/* Save the DMA address of the last TRB in the TD. */
	preq->td.last_trb = ep_ring->enqueue;

	/* Queue status TRB. */
	अगर (preq->request.length == 0)
		field = ep_ring->cycle_state;
	अन्यथा
		field = (ep_ring->cycle_state ^ 1);

	अगर (preq->request.length > 0 && pdev->ep0_expect_in)
		field |= TRB_सूची_IN;

	अगर (pep->ep_state & EP0_HALTED_STATUS) अणु
		pep->ep_state &= ~EP0_HALTED_STATUS;
		field |= TRB_SETUPSTAT(TRB_SETUPSTAT_STALL);
	पूर्ण अन्यथा अणु
		field |= TRB_SETUPSTAT(TRB_SETUPSTAT_ACK);
	पूर्ण

	cdnsp_queue_trb(pdev, ep_ring, false, 0, 0, TRB_INTR_TARGET(0),
			field | TRB_IOC | TRB_SETUPID(pdev->setup_id) |
			TRB_TYPE(TRB_STATUS) | pdev->setup_speed);

	cdnsp_ring_ep_करोorbell(pdev, pep, preq->request.stream_id);

	वापस 0;
पूर्ण

पूर्णांक cdnsp_cmd_stop_ep(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep)
अणु
	u32 ep_state = GET_EP_CTX_STATE(pep->out_ctx);
	पूर्णांक ret = 0;

	अगर (ep_state == EP_STATE_STOPPED || ep_state == EP_STATE_DISABLED) अणु
		trace_cdnsp_ep_stopped_or_disabled(pep->out_ctx);
		जाओ ep_stopped;
	पूर्ण

	cdnsp_queue_stop_endpoपूर्णांक(pdev, pep->idx);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);

	trace_cdnsp_handle_cmd_stop_ep(pep->out_ctx);

ep_stopped:
	pep->ep_state |= EP_STOPPED;
	वापस ret;
पूर्ण

पूर्णांक cdnsp_cmd_flush_ep(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep)
अणु
	पूर्णांक ret;

	cdnsp_queue_flush_endpoपूर्णांक(pdev, pep->idx);
	cdnsp_ring_cmd_db(pdev);
	ret = cdnsp_रुको_क्रम_cmd_compl(pdev);

	trace_cdnsp_handle_cmd_flush_ep(pep->out_ctx);

	वापस ret;
पूर्ण

/*
 * The transfer burst count field of the isochronous TRB defines the number of
 * bursts that are required to move all packets in this TD. Only SuperSpeed
 * devices can burst up to bMaxBurst number of packets per service पूर्णांकerval.
 * This field is zero based, meaning a value of zero in the field means one
 * burst. Basically, क्रम everything but SuperSpeed devices, this field will be
 * zero.
 */
अटल अचिन्हित पूर्णांक cdnsp_get_burst_count(काष्ठा cdnsp_device *pdev,
					  काष्ठा cdnsp_request *preq,
					  अचिन्हित पूर्णांक total_packet_count)
अणु
	अचिन्हित पूर्णांक max_burst;

	अगर (pdev->gadget.speed < USB_SPEED_SUPER)
		वापस 0;

	max_burst = preq->pep->endpoपूर्णांक.comp_desc->bMaxBurst;
	वापस DIV_ROUND_UP(total_packet_count, max_burst + 1) - 1;
पूर्ण

/*
 * Returns the number of packets in the last "burst" of packets. This field is
 * valid क्रम all speeds of devices. USB 2.0 devices can only करो one "burst", so
 * the last burst packet count is equal to the total number of packets in the
 * TD. SuperSpeed endpoपूर्णांकs can have up to 3 bursts. All but the last burst
 * must contain (bMaxBurst + 1) number of packets, but the last burst can
 * contain 1 to (bMaxBurst + 1) packets.
 */
अटल अचिन्हित पूर्णांक
	cdnsp_get_last_burst_packet_count(काष्ठा cdnsp_device *pdev,
					  काष्ठा cdnsp_request *preq,
					  अचिन्हित पूर्णांक total_packet_count)
अणु
	अचिन्हित पूर्णांक max_burst;
	अचिन्हित पूर्णांक residue;

	अगर (pdev->gadget.speed >= USB_SPEED_SUPER) अणु
		/* bMaxBurst is zero based: 0 means 1 packet per burst. */
		max_burst = preq->pep->endpoपूर्णांक.comp_desc->bMaxBurst;
		residue = total_packet_count % (max_burst + 1);

		/*
		 * If residue is zero, the last burst contains (max_burst + 1)
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

/* Queue function isoc transfer */
अटल पूर्णांक cdnsp_queue_isoc_tx(काष्ठा cdnsp_device *pdev,
			       काष्ठा cdnsp_request *preq)
अणु
	पूर्णांक trb_buff_len, td_len, td_reमुख्य_len, ret;
	अचिन्हित पूर्णांक burst_count, last_burst_pkt;
	अचिन्हित पूर्णांक total_pkt_count, max_pkt;
	काष्ठा cdnsp_generic_trb *start_trb;
	bool more_trbs_coming = true;
	काष्ठा cdnsp_ring *ep_ring;
	पूर्णांक running_total = 0;
	u32 field, length_field;
	पूर्णांक start_cycle;
	पूर्णांक trbs_per_td;
	u64 addr;
	पूर्णांक i;

	ep_ring = preq->pep->ring;
	start_trb = &ep_ring->enqueue->generic;
	start_cycle = ep_ring->cycle_state;
	td_len = preq->request.length;
	addr = (u64)preq->request.dma;
	td_reमुख्य_len = td_len;

	max_pkt = usb_endpoपूर्णांक_maxp(preq->pep->endpoपूर्णांक.desc);
	total_pkt_count = DIV_ROUND_UP(td_len, max_pkt);

	/* A zero-length transfer still involves at least one packet. */
	अगर (total_pkt_count == 0)
		total_pkt_count++;

	burst_count = cdnsp_get_burst_count(pdev, preq, total_pkt_count);
	last_burst_pkt = cdnsp_get_last_burst_packet_count(pdev, preq,
							   total_pkt_count);
	trbs_per_td = count_isoc_trbs_needed(preq);

	ret = cdnsp_prepare_transfer(pdev, preq, trbs_per_td);
	अगर (ret)
		जाओ cleanup;

	/*
	 * Set isoc specअगरic data क्रम the first TRB in a TD.
	 * Prevent HW from getting the TRBs by keeping the cycle state
	 * inverted in the first TDs isoc TRB.
	 */
	field = TRB_TYPE(TRB_ISOC) | TRB_TLBPC(last_burst_pkt) |
		TRB_SIA | TRB_TBC(burst_count);

	अगर (!start_cycle)
		field |= TRB_CYCLE;

	/* Fill the rest of the TRB fields, and reमुख्यing normal TRBs. */
	क्रम (i = 0; i < trbs_per_td; i++) अणु
		u32 reमुख्यder;

		/* Calculate TRB length. */
		trb_buff_len = TRB_BUFF_LEN_UP_TO_BOUNDARY(addr);
		अगर (trb_buff_len > td_reमुख्य_len)
			trb_buff_len = td_reमुख्य_len;

		/* Set the TRB length, TD size, & पूर्णांकerrupter fields. */
		reमुख्यder = cdnsp_td_reमुख्यder(pdev, running_total,
					       trb_buff_len, td_len, preq,
					       more_trbs_coming);

		length_field = TRB_LEN(trb_buff_len) | TRB_INTR_TARGET(0);

		/* Only first TRB is isoc, overग_लिखो otherwise. */
		अगर (i) अणु
			field = TRB_TYPE(TRB_NORMAL) | ep_ring->cycle_state;
			length_field |= TRB_TD_SIZE(reमुख्यder);
		पूर्ण अन्यथा अणु
			length_field |= TRB_TD_SIZE_TBC(burst_count);
		पूर्ण

		/* Only set पूर्णांकerrupt on लघु packet क्रम OUT EPs. */
		अगर (usb_endpoपूर्णांक_dir_out(preq->pep->endpoपूर्णांक.desc))
			field |= TRB_ISP;

		/* Set the chain bit क्रम all except the last TRB. */
		अगर (i < trbs_per_td - 1) अणु
			more_trbs_coming = true;
			field |= TRB_CHAIN;
		पूर्ण अन्यथा अणु
			more_trbs_coming = false;
			preq->td.last_trb = ep_ring->enqueue;
			field |= TRB_IOC;
		पूर्ण

		cdnsp_queue_trb(pdev, ep_ring, more_trbs_coming,
				lower_32_bits(addr), upper_32_bits(addr),
				length_field, field);

		running_total += trb_buff_len;
		addr += trb_buff_len;
		td_reमुख्य_len -= trb_buff_len;
	पूर्ण

	/* Check TD length */
	अगर (running_total != td_len) अणु
		dev_err(pdev->dev, "ISOC TD length unmatch\n");
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	cdnsp_giveback_first_trb(pdev, preq->pep, preq->request.stream_id,
				 start_cycle, start_trb);

	वापस 0;

cleanup:
	/* Clean up a partially enqueued isoc transfer. */
	list_del_init(&preq->td.td_list);
	ep_ring->num_tds--;

	/*
	 * Use the first TD as a temporary variable to turn the TDs we've
	 * queued पूर्णांकo No-ops with a software-owned cycle bit.
	 * That way the hardware won't accidentally start executing bogus TDs
	 * when we partially overग_लिखो them.
	 * td->first_trb and td->start_seg are alपढ़ोy set.
	 */
	preq->td.last_trb = ep_ring->enqueue;
	/* Every TRB except the first & last will have its cycle bit flipped. */
	cdnsp_td_to_noop(pdev, ep_ring, &preq->td, true);

	/* Reset the ring enqueue back to the first TRB and its cycle bit. */
	ep_ring->enqueue = preq->td.first_trb;
	ep_ring->enq_seg = preq->td.start_seg;
	ep_ring->cycle_state = start_cycle;
	वापस ret;
पूर्ण

पूर्णांक cdnsp_queue_isoc_tx_prepare(काष्ठा cdnsp_device *pdev,
				काष्ठा cdnsp_request *preq)
अणु
	काष्ठा cdnsp_ring *ep_ring;
	u32 ep_state;
	पूर्णांक num_trbs;
	पूर्णांक ret;

	ep_ring = preq->pep->ring;
	ep_state = GET_EP_CTX_STATE(preq->pep->out_ctx);
	num_trbs = count_isoc_trbs_needed(preq);

	/*
	 * Check the ring to guarantee there is enough room क्रम the whole
	 * request. Do not insert any td of the USB Request to the ring अगर the
	 * check failed.
	 */
	ret = cdnsp_prepare_ring(pdev, ep_ring, ep_state, num_trbs, GFP_ATOMIC);
	अगर (ret)
		वापस ret;

	वापस cdnsp_queue_isoc_tx(pdev, preq);
पूर्ण

/****		Command Ring Operations		****/
/*
 * Generic function क्रम queuing a command TRB on the command ring.
 * Driver queue only one command to ring in the moment.
 */
अटल व्योम cdnsp_queue_command(काष्ठा cdnsp_device *pdev,
				u32 field1,
				u32 field2,
				u32 field3,
				u32 field4)
अणु
	cdnsp_prepare_ring(pdev, pdev->cmd_ring, EP_STATE_RUNNING, 1,
			   GFP_ATOMIC);

	pdev->cmd.command_trb = pdev->cmd_ring->enqueue;

	cdnsp_queue_trb(pdev, pdev->cmd_ring, false, field1, field2,
			field3, field4 | pdev->cmd_ring->cycle_state);
पूर्ण

/* Queue a slot enable or disable request on the command ring */
व्योम cdnsp_queue_slot_control(काष्ठा cdnsp_device *pdev, u32 trb_type)
अणु
	cdnsp_queue_command(pdev, 0, 0, 0, TRB_TYPE(trb_type) |
			    SLOT_ID_FOR_TRB(pdev->slot_id));
पूर्ण

/* Queue an address device command TRB */
व्योम cdnsp_queue_address_device(काष्ठा cdnsp_device *pdev,
				dma_addr_t in_ctx_ptr,
				क्रमागत cdnsp_setup_dev setup)
अणु
	cdnsp_queue_command(pdev, lower_32_bits(in_ctx_ptr),
			    upper_32_bits(in_ctx_ptr), 0,
			    TRB_TYPE(TRB_ADDR_DEV) |
			    SLOT_ID_FOR_TRB(pdev->slot_id) |
			    (setup == SETUP_CONTEXT_ONLY ? TRB_BSR : 0));
पूर्ण

/* Queue a reset device command TRB */
व्योम cdnsp_queue_reset_device(काष्ठा cdnsp_device *pdev)
अणु
	cdnsp_queue_command(pdev, 0, 0, 0, TRB_TYPE(TRB_RESET_DEV) |
			    SLOT_ID_FOR_TRB(pdev->slot_id));
पूर्ण

/* Queue a configure endpoपूर्णांक command TRB */
व्योम cdnsp_queue_configure_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
				    dma_addr_t in_ctx_ptr)
अणु
	cdnsp_queue_command(pdev, lower_32_bits(in_ctx_ptr),
			    upper_32_bits(in_ctx_ptr), 0,
			    TRB_TYPE(TRB_CONFIG_EP) |
			    SLOT_ID_FOR_TRB(pdev->slot_id));
पूर्ण

/*
 * Suspend is set to indicate "Stop Endpoint Command" is being issued to stop
 * activity on an endpoपूर्णांक that is about to be suspended.
 */
व्योम cdnsp_queue_stop_endpoपूर्णांक(काष्ठा cdnsp_device *pdev, अचिन्हित पूर्णांक ep_index)
अणु
	cdnsp_queue_command(pdev, 0, 0, 0, SLOT_ID_FOR_TRB(pdev->slot_id) |
			    EP_ID_FOR_TRB(ep_index) | TRB_TYPE(TRB_STOP_RING));
पूर्ण

/* Set Transfer Ring Dequeue Poपूर्णांकer command. */
व्योम cdnsp_queue_new_dequeue_state(काष्ठा cdnsp_device *pdev,
				   काष्ठा cdnsp_ep *pep,
				   काष्ठा cdnsp_dequeue_state *deq_state)
अणु
	u32 trb_stream_id = STREAM_ID_FOR_TRB(deq_state->stream_id);
	u32 trb_slot_id = SLOT_ID_FOR_TRB(pdev->slot_id);
	u32 type = TRB_TYPE(TRB_SET_DEQ);
	u32 trb_sct = 0;
	dma_addr_t addr;

	addr = cdnsp_trb_virt_to_dma(deq_state->new_deq_seg,
				     deq_state->new_deq_ptr);

	अगर (deq_state->stream_id)
		trb_sct = SCT_FOR_TRB(SCT_PRI_TR);

	cdnsp_queue_command(pdev, lower_32_bits(addr) | trb_sct |
			    deq_state->new_cycle_state, upper_32_bits(addr),
			    trb_stream_id, trb_slot_id |
			    EP_ID_FOR_TRB(pep->idx) | type);
पूर्ण

व्योम cdnsp_queue_reset_ep(काष्ठा cdnsp_device *pdev, अचिन्हित पूर्णांक ep_index)
अणु
	वापस cdnsp_queue_command(pdev, 0, 0, 0,
				   SLOT_ID_FOR_TRB(pdev->slot_id) |
				   EP_ID_FOR_TRB(ep_index) |
				   TRB_TYPE(TRB_RESET_EP));
पूर्ण

/*
 * Queue a halt endpoपूर्णांक request on the command ring.
 */
व्योम cdnsp_queue_halt_endpoपूर्णांक(काष्ठा cdnsp_device *pdev, अचिन्हित पूर्णांक ep_index)
अणु
	cdnsp_queue_command(pdev, 0, 0, 0, TRB_TYPE(TRB_HALT_ENDPOINT) |
			    SLOT_ID_FOR_TRB(pdev->slot_id) |
			    EP_ID_FOR_TRB(ep_index));
पूर्ण

/*
 * Queue a flush endpoपूर्णांक request on the command ring.
 */
व्योम  cdnsp_queue_flush_endpoपूर्णांक(काष्ठा cdnsp_device *pdev,
				 अचिन्हित पूर्णांक ep_index)
अणु
	cdnsp_queue_command(pdev, 0, 0, 0, TRB_TYPE(TRB_FLUSH_ENDPOINT) |
			    SLOT_ID_FOR_TRB(pdev->slot_id) |
			    EP_ID_FOR_TRB(ep_index));
पूर्ण

व्योम cdnsp_क्रमce_header_wakeup(काष्ठा cdnsp_device *pdev, पूर्णांक पूर्णांकf_num)
अणु
	u32 lo, mid;

	lo = TRB_FH_TO_PACKET_TYPE(TRB_FH_TR_PACKET) |
	     TRB_FH_TO_DEVICE_ADDRESS(pdev->device_address);
	mid = TRB_FH_TR_PACKET_DEV_NOT |
	      TRB_FH_TO_NOT_TYPE(TRB_FH_TR_PACKET_FUNCTION_WAKE) |
	      TRB_FH_TO_INTERFACE(पूर्णांकf_num);

	cdnsp_queue_command(pdev, lo, mid, 0,
			    TRB_TYPE(TRB_FORCE_HEADER) | SET_PORT_ID(2));
पूर्ण
