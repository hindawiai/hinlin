<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2002 International Business Machines, Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions are the methods क्रम accessing the SCTP inqueue.
 *
 * An SCTP inqueue is a queue पूर्णांकo which you push SCTP packets
 * (which might be bundles or fragments of chunks) and out of which you
 * pop SCTP whole chunks.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson <karl@athena.chicago.il.us>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

/* Initialize an SCTP inqueue.  */
व्योम sctp_inq_init(काष्ठा sctp_inq *queue)
अणु
	INIT_LIST_HEAD(&queue->in_chunk_list);
	queue->in_progress = शून्य;

	/* Create a task क्रम delivering data.  */
	INIT_WORK(&queue->immediate, शून्य);
पूर्ण

/* Release the memory associated with an SCTP inqueue.  */
व्योम sctp_inq_मुक्त(काष्ठा sctp_inq *queue)
अणु
	काष्ठा sctp_chunk *chunk, *पंचांगp;

	/* Empty the queue.  */
	list_क्रम_each_entry_safe(chunk, पंचांगp, &queue->in_chunk_list, list) अणु
		list_del_init(&chunk->list);
		sctp_chunk_मुक्त(chunk);
	पूर्ण

	/* If there is a packet which is currently being worked on,
	 * मुक्त it as well.
	 */
	अगर (queue->in_progress) अणु
		sctp_chunk_मुक्त(queue->in_progress);
		queue->in_progress = शून्य;
	पूर्ण
पूर्ण

/* Put a new packet in an SCTP inqueue.
 * We assume that packet->sctp_hdr is set and in host byte order.
 */
व्योम sctp_inq_push(काष्ठा sctp_inq *q, काष्ठा sctp_chunk *chunk)
अणु
	/* Directly call the packet handling routine. */
	अगर (chunk->rcvr->dead) अणु
		sctp_chunk_मुक्त(chunk);
		वापस;
	पूर्ण

	/* We are now calling this either from the soft पूर्णांकerrupt
	 * or from the backlog processing.
	 * Eventually, we should clean up inqueue to not rely
	 * on the BH related data काष्ठाures.
	 */
	list_add_tail(&chunk->list, &q->in_chunk_list);
	अगर (chunk->asoc)
		chunk->asoc->stats.ipackets++;
	q->immediate.func(&q->immediate);
पूर्ण

/* Peek at the next chunk on the inqeue. */
काष्ठा sctp_chunkhdr *sctp_inq_peek(काष्ठा sctp_inq *queue)
अणु
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_chunkhdr *ch = शून्य;

	chunk = queue->in_progress;
	/* If there is no more chunks in this packet, say so */
	अगर (chunk->singleton ||
	    chunk->end_of_packet ||
	    chunk->pdiscard)
		    वापस शून्य;

	ch = (काष्ठा sctp_chunkhdr *)chunk->chunk_end;

	वापस ch;
पूर्ण


/* Extract a chunk from an SCTP inqueue.
 *
 * WARNING:  If you need to put the chunk on another queue, you need to
 * make a shallow copy (clone) of it.
 */
काष्ठा sctp_chunk *sctp_inq_pop(काष्ठा sctp_inq *queue)
अणु
	काष्ठा sctp_chunk *chunk;
	काष्ठा sctp_chunkhdr *ch = शून्य;

	/* The assumption is that we are safe to process the chunks
	 * at this समय.
	 */

	chunk = queue->in_progress;
	अगर (chunk) अणु
		/* There is a packet that we have been working on.
		 * Any post processing work to करो beक्रमe we move on?
		 */
		अगर (chunk->singleton ||
		    chunk->end_of_packet ||
		    chunk->pdiscard) अणु
			अगर (chunk->head_skb == chunk->skb) अणु
				chunk->skb = skb_shinfo(chunk->skb)->frag_list;
				जाओ new_skb;
			पूर्ण
			अगर (chunk->skb->next) अणु
				chunk->skb = chunk->skb->next;
				जाओ new_skb;
			पूर्ण

			अगर (chunk->head_skb)
				chunk->skb = chunk->head_skb;
			sctp_chunk_मुक्त(chunk);
			chunk = queue->in_progress = शून्य;
		पूर्ण अन्यथा अणु
			/* Nothing to करो. Next chunk in the packet, please. */
			ch = (काष्ठा sctp_chunkhdr *)chunk->chunk_end;
			/* Force chunk->skb->data to chunk->chunk_end.  */
			skb_pull(chunk->skb, chunk->chunk_end - chunk->skb->data);
			/* We are guaranteed to pull a SCTP header. */
		पूर्ण
	पूर्ण

	/* Do we need to take the next packet out of the queue to process? */
	अगर (!chunk) अणु
		काष्ठा list_head *entry;

next_chunk:
		/* Is the queue empty?  */
		entry = sctp_list_dequeue(&queue->in_chunk_list);
		अगर (!entry)
			वापस शून्य;

		chunk = list_entry(entry, काष्ठा sctp_chunk, list);

		अगर (skb_is_gso(chunk->skb) && skb_is_gso_sctp(chunk->skb)) अणु
			/* GSO-marked skbs but without frags, handle
			 * them normally
			 */
			अगर (skb_shinfo(chunk->skb)->frag_list)
				chunk->head_skb = chunk->skb;

			/* skbs with "cover letter" */
			अगर (chunk->head_skb && chunk->skb->data_len == chunk->skb->len)
				chunk->skb = skb_shinfo(chunk->skb)->frag_list;

			अगर (WARN_ON(!chunk->skb)) अणु
				__SCTP_INC_STATS(dev_net(chunk->skb->dev), SCTP_MIB_IN_PKT_DISCARDS);
				sctp_chunk_मुक्त(chunk);
				जाओ next_chunk;
			पूर्ण
		पूर्ण

		अगर (chunk->asoc)
			sock_rps_save_rxhash(chunk->asoc->base.sk, chunk->skb);

		queue->in_progress = chunk;

new_skb:
		/* This is the first chunk in the packet.  */
		ch = (काष्ठा sctp_chunkhdr *)chunk->skb->data;
		chunk->singleton = 1;
		chunk->data_accepted = 0;
		chunk->pdiscard = 0;
		chunk->auth = 0;
		chunk->has_asconf = 0;
		chunk->end_of_packet = 0;
		अगर (chunk->head_skb) अणु
			काष्ठा sctp_input_cb
				*cb = SCTP_INPUT_CB(chunk->skb),
				*head_cb = SCTP_INPUT_CB(chunk->head_skb);

			cb->chunk = head_cb->chunk;
			cb->af = head_cb->af;
		पूर्ण
	पूर्ण

	chunk->chunk_hdr = ch;
	chunk->chunk_end = ((__u8 *)ch) + SCTP_PAD4(ntohs(ch->length));
	skb_pull(chunk->skb, माप(*ch));
	chunk->subh.v = शून्य; /* Subheader is no दीर्घer valid.  */

	अगर (chunk->chunk_end + माप(*ch) <= skb_tail_poपूर्णांकer(chunk->skb)) अणु
		/* This is not a singleton */
		chunk->singleton = 0;
	पूर्ण अन्यथा अगर (chunk->chunk_end > skb_tail_poपूर्णांकer(chunk->skb)) अणु
		/* Discard inside state machine. */
		chunk->pdiscard = 1;
		chunk->chunk_end = skb_tail_poपूर्णांकer(chunk->skb);
	पूर्ण अन्यथा अणु
		/* We are at the end of the packet, so mark the chunk
		 * in हाल we need to send a SACK.
		 */
		chunk->end_of_packet = 1;
	पूर्ण

	pr_debug("+++sctp_inq_pop+++ chunk:%p[%s], length:%d, skb->len:%d\n",
		 chunk, sctp_cname(SCTP_ST_CHUNK(chunk->chunk_hdr->type)),
		 ntohs(chunk->chunk_hdr->length), chunk->skb->len);

	वापस chunk;
पूर्ण

/* Set a top-half handler.
 *
 * Originally, we the top-half handler was scheduled as a BH.  We now
 * call the handler directly in sctp_inq_push() at a समय that
 * we know we are lock safe.
 * The पूर्णांकent is that this routine will pull stuff out of the
 * inqueue and process it.
 */
व्योम sctp_inq_set_th_handler(काष्ठा sctp_inq *q, work_func_t callback)
अणु
	INIT_WORK(&q->immediate, callback);
पूर्ण
