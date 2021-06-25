<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This असलtraction carries sctp events to the ULP (sockets).
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/busy_poll.h>
#समावेश <net/sctp/काष्ठाs.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

/* Forward declarations क्रम पूर्णांकernal helpers.  */
अटल काष्ठा sctp_ulpevent *sctp_ulpq_reयंत्र(काष्ठा sctp_ulpq *ulpq,
					      काष्ठा sctp_ulpevent *);
अटल काष्ठा sctp_ulpevent *sctp_ulpq_order(काष्ठा sctp_ulpq *,
					      काष्ठा sctp_ulpevent *);
अटल व्योम sctp_ulpq_reयंत्र_drain(काष्ठा sctp_ulpq *ulpq);

/* 1st Level Abstractions */

/* Initialize a ULP queue from a block of memory.  */
काष्ठा sctp_ulpq *sctp_ulpq_init(काष्ठा sctp_ulpq *ulpq,
				 काष्ठा sctp_association *asoc)
अणु
	स_रखो(ulpq, 0, माप(काष्ठा sctp_ulpq));

	ulpq->asoc = asoc;
	skb_queue_head_init(&ulpq->reयंत्र);
	skb_queue_head_init(&ulpq->reयंत्र_uo);
	skb_queue_head_init(&ulpq->lobby);
	ulpq->pd_mode  = 0;

	वापस ulpq;
पूर्ण


/* Flush the reassembly and ordering queues.  */
व्योम sctp_ulpq_flush(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sctp_ulpevent *event;

	जबतक ((skb = __skb_dequeue(&ulpq->lobby)) != शून्य) अणु
		event = sctp_skb2event(skb);
		sctp_ulpevent_मुक्त(event);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&ulpq->reयंत्र)) != शून्य) अणु
		event = sctp_skb2event(skb);
		sctp_ulpevent_मुक्त(event);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&ulpq->reयंत्र_uo)) != शून्य) अणु
		event = sctp_skb2event(skb);
		sctp_ulpevent_मुक्त(event);
	पूर्ण
पूर्ण

/* Dispose of a ulpqueue.  */
व्योम sctp_ulpq_मुक्त(काष्ठा sctp_ulpq *ulpq)
अणु
	sctp_ulpq_flush(ulpq);
पूर्ण

/* Process an incoming DATA chunk.  */
पूर्णांक sctp_ulpq_tail_data(काष्ठा sctp_ulpq *ulpq, काष्ठा sctp_chunk *chunk,
			gfp_t gfp)
अणु
	काष्ठा sk_buff_head temp;
	काष्ठा sctp_ulpevent *event;
	पूर्णांक event_eor = 0;

	/* Create an event from the incoming chunk. */
	event = sctp_ulpevent_make_rcvmsg(chunk->asoc, chunk, gfp);
	अगर (!event)
		वापस -ENOMEM;

	event->ssn = ntohs(chunk->subh.data_hdr->ssn);
	event->ppid = chunk->subh.data_hdr->ppid;

	/* Do reassembly अगर needed.  */
	event = sctp_ulpq_reयंत्र(ulpq, event);

	/* Do ordering अगर needed.  */
	अगर (event) अणु
		/* Create a temporary list to collect chunks on.  */
		skb_queue_head_init(&temp);
		__skb_queue_tail(&temp, sctp_event2skb(event));

		अगर (event->msg_flags & MSG_EOR)
			event = sctp_ulpq_order(ulpq, event);
	पूर्ण

	/* Send event to the ULP.  'event' is the sctp_ulpevent क्रम
	 * very first SKB on the 'temp' list.
	 */
	अगर (event) अणु
		event_eor = (event->msg_flags & MSG_EOR) ? 1 : 0;
		sctp_ulpq_tail_event(ulpq, &temp);
	पूर्ण

	वापस event_eor;
पूर्ण

/* Add a new event क्रम propagation to the ULP.  */
/* Clear the partial delivery mode क्रम this socket.   Note: This
 * assumes that no association is currently in partial delivery mode.
 */
पूर्णांक sctp_clear_pd(काष्ठा sock *sk, काष्ठा sctp_association *asoc)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(sk);

	अगर (atomic_dec_and_test(&sp->pd_mode)) अणु
		/* This means there are no other associations in PD, so
		 * we can go ahead and clear out the lobby in one shot
		 */
		अगर (!skb_queue_empty(&sp->pd_lobby)) अणु
			skb_queue_splice_tail_init(&sp->pd_lobby,
						   &sk->sk_receive_queue);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* There are other associations in PD, so we only need to
		 * pull stuff out of the lobby that beदीर्घs to the
		 * associations that is निकासing PD (all of its notअगरications
		 * are posted here).
		 */
		अगर (!skb_queue_empty(&sp->pd_lobby) && asoc) अणु
			काष्ठा sk_buff *skb, *पंचांगp;
			काष्ठा sctp_ulpevent *event;

			sctp_skb_क्रम_each(skb, &sp->pd_lobby, पंचांगp) अणु
				event = sctp_skb2event(skb);
				अगर (event->asoc == asoc) अणु
					__skb_unlink(skb, &sp->pd_lobby);
					__skb_queue_tail(&sk->sk_receive_queue,
							 skb);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Set the pd_mode on the socket and ulpq */
अटल व्योम sctp_ulpq_set_pd(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sctp_sock *sp = sctp_sk(ulpq->asoc->base.sk);

	atomic_inc(&sp->pd_mode);
	ulpq->pd_mode = 1;
पूर्ण

/* Clear the pd_mode and restart any pending messages रुकोing क्रम delivery. */
अटल पूर्णांक sctp_ulpq_clear_pd(काष्ठा sctp_ulpq *ulpq)
अणु
	ulpq->pd_mode = 0;
	sctp_ulpq_reयंत्र_drain(ulpq);
	वापस sctp_clear_pd(ulpq->asoc->base.sk, ulpq->asoc);
पूर्ण

पूर्णांक sctp_ulpq_tail_event(काष्ठा sctp_ulpq *ulpq, काष्ठा sk_buff_head *skb_list)
अणु
	काष्ठा sock *sk = ulpq->asoc->base.sk;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff_head *queue;
	काष्ठा sk_buff *skb;
	पूर्णांक clear_pd = 0;

	skb = __skb_peek(skb_list);
	event = sctp_skb2event(skb);

	/* If the socket is just going to throw this away, करो not
	 * even try to deliver it.
	 */
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN &&
	    (sk->sk_shutकरोwn & SEND_SHUTDOWN ||
	     !sctp_ulpevent_is_notअगरication(event)))
		जाओ out_मुक्त;

	अगर (!sctp_ulpevent_is_notअगरication(event)) अणु
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	पूर्ण
	/* Check अगर the user wishes to receive this event.  */
	अगर (!sctp_ulpevent_is_enabled(event, ulpq->asoc->subscribe))
		जाओ out_मुक्त;

	/* If we are in partial delivery mode, post to the lobby until
	 * partial delivery is cleared, unless, of course _this_ is
	 * the association the cause of the partial delivery.
	 */

	अगर (atomic_पढ़ो(&sp->pd_mode) == 0) अणु
		queue = &sk->sk_receive_queue;
	पूर्ण अन्यथा अणु
		अगर (ulpq->pd_mode) अणु
			/* If the association is in partial delivery, we
			 * need to finish delivering the partially processed
			 * packet beक्रमe passing any other data.  This is
			 * because we करोn't truly support stream पूर्णांकerleaving.
			 */
			अगर ((event->msg_flags & MSG_NOTIFICATION) ||
			    (SCTP_DATA_NOT_FRAG ==
				    (event->msg_flags & SCTP_DATA_FRAG_MASK)))
				queue = &sp->pd_lobby;
			अन्यथा अणु
				clear_pd = event->msg_flags & MSG_EOR;
				queue = &sk->sk_receive_queue;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * If fragment पूर्णांकerleave is enabled, we
			 * can queue this to the receive queue instead
			 * of the lobby.
			 */
			अगर (sp->frag_पूर्णांकerleave)
				queue = &sk->sk_receive_queue;
			अन्यथा
				queue = &sp->pd_lobby;
		पूर्ण
	पूर्ण

	skb_queue_splice_tail_init(skb_list, queue);

	/* Did we just complete partial delivery and need to get
	 * rolling again?  Move pending data to the receive
	 * queue.
	 */
	अगर (clear_pd)
		sctp_ulpq_clear_pd(ulpq);

	अगर (queue == &sk->sk_receive_queue && !sp->data_पढ़ोy_संकेतled) अणु
		अगर (!sock_owned_by_user(sk))
			sp->data_पढ़ोy_संकेतled = 1;
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
	वापस 1;

out_मुक्त:
	अगर (skb_list)
		sctp_queue_purge_ulpevents(skb_list);
	अन्यथा
		sctp_ulpevent_मुक्त(event);

	वापस 0;
पूर्ण

/* 2nd Level Abstractions */

/* Helper function to store chunks that need to be reassembled.  */
अटल व्योम sctp_ulpq_store_reयंत्र(काष्ठा sctp_ulpq *ulpq,
					 काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff *pos;
	काष्ठा sctp_ulpevent *cevent;
	__u32 tsn, ctsn;

	tsn = event->tsn;

	/* See अगर it beदीर्घs at the end. */
	pos = skb_peek_tail(&ulpq->reयंत्र);
	अगर (!pos) अणु
		__skb_queue_tail(&ulpq->reयंत्र, sctp_event2skb(event));
		वापस;
	पूर्ण

	/* Short circuit just dropping it at the end. */
	cevent = sctp_skb2event(pos);
	ctsn = cevent->tsn;
	अगर (TSN_lt(ctsn, tsn)) अणु
		__skb_queue_tail(&ulpq->reयंत्र, sctp_event2skb(event));
		वापस;
	पूर्ण

	/* Find the right place in this list. We store them by TSN.  */
	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		अगर (TSN_lt(tsn, ctsn))
			अवरोध;
	पूर्ण

	/* Insert beक्रमe pos. */
	__skb_queue_beक्रमe(&ulpq->reयंत्र, pos, sctp_event2skb(event));

पूर्ण

/* Helper function to वापस an event corresponding to the reassembled
 * datagram.
 * This routine creates a re-assembled skb given the first and last skb's
 * as stored in the reassembly queue. The skb's may be non-linear अगर the sctp
 * payload was fragmented on the way and ip had to reassemble them.
 * We add the rest of skb's to the first skb's fraglist.
 */
काष्ठा sctp_ulpevent *sctp_make_reassembled_event(काष्ठा net *net,
						  काष्ठा sk_buff_head *queue,
						  काष्ठा sk_buff *f_frag,
						  काष्ठा sk_buff *l_frag)
अणु
	काष्ठा sk_buff *pos;
	काष्ठा sk_buff *new = शून्य;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *pnext, *last;
	काष्ठा sk_buff *list = skb_shinfo(f_frag)->frag_list;

	/* Store the poपूर्णांकer to the 2nd skb */
	अगर (f_frag == l_frag)
		pos = शून्य;
	अन्यथा
		pos = f_frag->next;

	/* Get the last skb in the f_frag's frag_list अगर present. */
	क्रम (last = list; list; last = list, list = list->next)
		;

	/* Add the list of reमुख्यing fragments to the first fragments
	 * frag_list.
	 */
	अगर (last)
		last->next = pos;
	अन्यथा अणु
		अगर (skb_cloned(f_frag)) अणु
			/* This is a cloned skb, we can't just modअगरy
			 * the frag_list.  We need a new skb to करो that.
			 * Instead of calling skb_unshare(), we'll करो it
			 * ourselves since we need to delay the मुक्त.
			 */
			new = skb_copy(f_frag, GFP_ATOMIC);
			अगर (!new)
				वापस शून्य;	/* try again later */

			sctp_skb_set_owner_r(new, f_frag->sk);

			skb_shinfo(new)->frag_list = pos;
		पूर्ण अन्यथा
			skb_shinfo(f_frag)->frag_list = pos;
	पूर्ण

	/* Remove the first fragment from the reassembly queue.  */
	__skb_unlink(f_frag, queue);

	/* अगर we did unshare, then मुक्त the old skb and re-assign */
	अगर (new) अणु
		kमुक्त_skb(f_frag);
		f_frag = new;
	पूर्ण

	जबतक (pos) अणु

		pnext = pos->next;

		/* Update the len and data_len fields of the first fragment. */
		f_frag->len += pos->len;
		f_frag->data_len += pos->len;

		/* Remove the fragment from the reassembly queue.  */
		__skb_unlink(pos, queue);

		/* Break अगर we have reached the last fragment.  */
		अगर (pos == l_frag)
			अवरोध;
		pos->next = pnext;
		pos = pnext;
	पूर्ण

	event = sctp_skb2event(f_frag);
	SCTP_INC_STATS(net, SCTP_MIB_REASMUSRMSGS);

	वापस event;
पूर्ण


/* Helper function to check अगर an incoming chunk has filled up the last
 * missing fragment in a SCTP datagram and वापस the corresponding event.
 */
अटल काष्ठा sctp_ulpevent *sctp_ulpq_retrieve_reassembled(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sk_buff *pos;
	काष्ठा sctp_ulpevent *cevent;
	काष्ठा sk_buff *first_frag = शून्य;
	__u32 ctsn, next_tsn;
	काष्ठा sctp_ulpevent *retval = शून्य;
	काष्ठा sk_buff *pd_first = शून्य;
	काष्ठा sk_buff *pd_last = शून्य;
	माप_प्रकार pd_len = 0;
	काष्ठा sctp_association *asoc;
	u32 pd_poपूर्णांक;

	/* Initialized to 0 just to aव्योम compiler warning message.  Will
	 * never be used with this value. It is referenced only after it
	 * is set when we find the first fragment of a message.
	 */
	next_tsn = 0;

	/* The chunks are held in the reयंत्र queue sorted by TSN.
	 * Walk through the queue sequentially and look क्रम a sequence of
	 * fragmented chunks that complete a datagram.
	 * 'first_frag' and next_tsn are reset when we find a chunk which
	 * is the first fragment of a datagram. Once these 2 fields are set
	 * we expect to find the reमुख्यing middle fragments and the last
	 * fragment in order. If not, first_frag is reset to शून्य and we
	 * start the next pass when we find another first fragment.
	 *
	 * There is a potential to करो partial delivery अगर user sets
	 * SCTP_PARTIAL_DELIVERY_POINT option. Lets count some things here
	 * to see अगर can करो PD.
	 */
	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			/* If this "FIRST_FRAG" is the first
			 * element in the queue, then count it towards
			 * possible PD.
			 */
			अगर (skb_queue_is_first(&ulpq->reयंत्र, pos)) अणु
			    pd_first = pos;
			    pd_last = pos;
			    pd_len = pos->len;
			पूर्ण अन्यथा अणु
			    pd_first = शून्य;
			    pd_last = शून्य;
			    pd_len = 0;
			पूर्ण

			first_frag = pos;
			next_tsn = ctsn + 1;
			अवरोध;

		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर ((first_frag) && (ctsn == next_tsn)) अणु
				next_tsn++;
				अगर (pd_first) अणु
				    pd_last = pos;
				    pd_len += pos->len;
				पूर्ण
			पूर्ण अन्यथा
				first_frag = शून्य;
			अवरोध;

		हाल SCTP_DATA_LAST_FRAG:
			अगर (first_frag && (ctsn == next_tsn))
				जाओ found;
			अन्यथा
				first_frag = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	asoc = ulpq->asoc;
	अगर (pd_first) अणु
		/* Make sure we can enter partial deliver.
		 * We can trigger partial delivery only अगर framgent
		 * पूर्णांकerleave is set, or the socket is not alपढ़ोy
		 * in  partial delivery.
		 */
		अगर (!sctp_sk(asoc->base.sk)->frag_पूर्णांकerleave &&
		    atomic_पढ़ो(&sctp_sk(asoc->base.sk)->pd_mode))
			जाओ करोne;

		cevent = sctp_skb2event(pd_first);
		pd_poपूर्णांक = sctp_sk(asoc->base.sk)->pd_poपूर्णांक;
		अगर (pd_poपूर्णांक && pd_poपूर्णांक <= pd_len) अणु
			retval = sctp_make_reassembled_event(asoc->base.net,
							     &ulpq->reयंत्र,
							     pd_first, pd_last);
			अगर (retval)
				sctp_ulpq_set_pd(ulpq);
		पूर्ण
	पूर्ण
करोne:
	वापस retval;
found:
	retval = sctp_make_reassembled_event(ulpq->asoc->base.net,
					     &ulpq->reयंत्र, first_frag, pos);
	अगर (retval)
		retval->msg_flags |= MSG_EOR;
	जाओ करोne;
पूर्ण

/* Retrieve the next set of fragments of a partial message. */
अटल काष्ठा sctp_ulpevent *sctp_ulpq_retrieve_partial(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sk_buff *pos, *last_frag, *first_frag;
	काष्ठा sctp_ulpevent *cevent;
	__u32 ctsn, next_tsn;
	पूर्णांक is_last;
	काष्ठा sctp_ulpevent *retval;

	/* The chunks are held in the reयंत्र queue sorted by TSN.
	 * Walk through the queue sequentially and look क्रम the first
	 * sequence of fragmented chunks.
	 */

	अगर (skb_queue_empty(&ulpq->reयंत्र))
		वापस शून्य;

	last_frag = first_frag = शून्य;
	retval = शून्य;
	next_tsn = 0;
	is_last = 0;

	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			अगर (!first_frag)
				वापस शून्य;
			जाओ करोne;
		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (!first_frag) अणु
				first_frag = pos;
				next_tsn = ctsn + 1;
				last_frag = pos;
			पूर्ण अन्यथा अगर (next_tsn == ctsn) अणु
				next_tsn++;
				last_frag = pos;
			पूर्ण अन्यथा
				जाओ करोne;
			अवरोध;
		हाल SCTP_DATA_LAST_FRAG:
			अगर (!first_frag)
				first_frag = pos;
			अन्यथा अगर (ctsn != next_tsn)
				जाओ करोne;
			last_frag = pos;
			is_last = 1;
			जाओ करोne;
		शेष:
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* We have the reassembled event. There is no need to look
	 * further.
	 */
करोne:
	retval = sctp_make_reassembled_event(ulpq->asoc->base.net, &ulpq->reयंत्र,
					     first_frag, last_frag);
	अगर (retval && is_last)
		retval->msg_flags |= MSG_EOR;

	वापस retval;
पूर्ण


/* Helper function to reassemble chunks.  Hold chunks on the reयंत्र queue that
 * need reassembling.
 */
अटल काष्ठा sctp_ulpevent *sctp_ulpq_reयंत्र(काष्ठा sctp_ulpq *ulpq,
						काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_ulpevent *retval = शून्य;

	/* Check अगर this is part of a fragmented message.  */
	अगर (SCTP_DATA_NOT_FRAG == (event->msg_flags & SCTP_DATA_FRAG_MASK)) अणु
		event->msg_flags |= MSG_EOR;
		वापस event;
	पूर्ण

	sctp_ulpq_store_reयंत्र(ulpq, event);
	अगर (!ulpq->pd_mode)
		retval = sctp_ulpq_retrieve_reassembled(ulpq);
	अन्यथा अणु
		__u32 ctsn, ctsnap;

		/* Do not even bother unless this is the next tsn to
		 * be delivered.
		 */
		ctsn = event->tsn;
		ctsnap = sctp_tsnmap_get_ctsn(&ulpq->asoc->peer.tsn_map);
		अगर (TSN_lte(ctsn, ctsnap))
			retval = sctp_ulpq_retrieve_partial(ulpq);
	पूर्ण

	वापस retval;
पूर्ण

/* Retrieve the first part (sequential fragments) क्रम partial delivery.  */
अटल काष्ठा sctp_ulpevent *sctp_ulpq_retrieve_first(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sk_buff *pos, *last_frag, *first_frag;
	काष्ठा sctp_ulpevent *cevent;
	__u32 ctsn, next_tsn;
	काष्ठा sctp_ulpevent *retval;

	/* The chunks are held in the reयंत्र queue sorted by TSN.
	 * Walk through the queue sequentially and look क्रम a sequence of
	 * fragmented chunks that start a datagram.
	 */

	अगर (skb_queue_empty(&ulpq->reयंत्र))
		वापस शून्य;

	last_frag = first_frag = शून्य;
	retval = शून्य;
	next_tsn = 0;

	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		cevent = sctp_skb2event(pos);
		ctsn = cevent->tsn;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			अगर (!first_frag) अणु
				first_frag = pos;
				next_tsn = ctsn + 1;
				last_frag = pos;
			पूर्ण अन्यथा
				जाओ करोne;
			अवरोध;

		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (!first_frag)
				वापस शून्य;
			अगर (ctsn == next_tsn) अणु
				next_tsn++;
				last_frag = pos;
			पूर्ण अन्यथा
				जाओ करोne;
			अवरोध;

		हाल SCTP_DATA_LAST_FRAG:
			अगर (!first_frag)
				वापस शून्य;
			अन्यथा
				जाओ करोne;
			अवरोध;

		शेष:
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* We have the reassembled event. There is no need to look
	 * further.
	 */
करोne:
	retval = sctp_make_reassembled_event(ulpq->asoc->base.net, &ulpq->reयंत्र,
					     first_frag, last_frag);
	वापस retval;
पूर्ण

/*
 * Flush out stale fragments from the reassembly queue when processing
 * a Forward TSN.
 *
 * RFC 3758, Section 3.6
 *
 * After receiving and processing a FORWARD TSN, the data receiver MUST
 * take cautions in updating its re-assembly queue.  The receiver MUST
 * हटाओ any partially reassembled message, which is still missing one
 * or more TSNs earlier than or equal to the new cumulative TSN poपूर्णांक.
 * In the event that the receiver has invoked the partial delivery API,
 * a notअगरication SHOULD also be generated to inक्रमm the upper layer API
 * that the message being partially delivered will NOT be completed.
 */
व्योम sctp_ulpq_reयंत्र_flushtsn(काष्ठा sctp_ulpq *ulpq, __u32 fwd_tsn)
अणु
	काष्ठा sk_buff *pos, *पंचांगp;
	काष्ठा sctp_ulpevent *event;
	__u32 tsn;

	अगर (skb_queue_empty(&ulpq->reयंत्र))
		वापस;

	skb_queue_walk_safe(&ulpq->reयंत्र, pos, पंचांगp) अणु
		event = sctp_skb2event(pos);
		tsn = event->tsn;

		/* Since the entire message must be abanकरोned by the
		 * sender (item A3 in Section 3.5, RFC 3758), we can
		 * मुक्त all fragments on the list that are less then
		 * or equal to ctsn_poपूर्णांक
		 */
		अगर (TSN_lte(tsn, fwd_tsn)) अणु
			__skb_unlink(pos, &ulpq->reयंत्र);
			sctp_ulpevent_मुक्त(event);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Drain the reassembly queue.  If we just cleared parted delivery, it
 * is possible that the reassembly queue will contain alपढ़ोy reassembled
 * messages.  Retrieve any such messages and give them to the user.
 */
अटल व्योम sctp_ulpq_reयंत्र_drain(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sctp_ulpevent *event = शून्य;

	अगर (skb_queue_empty(&ulpq->reयंत्र))
		वापस;

	जबतक ((event = sctp_ulpq_retrieve_reassembled(ulpq)) != शून्य) अणु
		काष्ठा sk_buff_head temp;

		skb_queue_head_init(&temp);
		__skb_queue_tail(&temp, sctp_event2skb(event));

		/* Do ordering अगर needed.  */
		अगर (event->msg_flags & MSG_EOR)
			event = sctp_ulpq_order(ulpq, event);

		/* Send event to the ULP.  'event' is the
		 * sctp_ulpevent क्रम  very first SKB on the  temp' list.
		 */
		अगर (event)
			sctp_ulpq_tail_event(ulpq, &temp);
	पूर्ण
पूर्ण


/* Helper function to gather skbs that have possibly become
 * ordered by an incoming chunk.
 */
अटल व्योम sctp_ulpq_retrieve_ordered(काष्ठा sctp_ulpq *ulpq,
					      काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff_head *event_list;
	काष्ठा sk_buff *pos, *पंचांगp;
	काष्ठा sctp_ulpevent *cevent;
	काष्ठा sctp_stream *stream;
	__u16 sid, csid, cssn;

	sid = event->stream;
	stream  = &ulpq->asoc->stream;

	event_list = (काष्ठा sk_buff_head *) sctp_event2skb(event)->prev;

	/* We are holding the chunks by stream, by SSN.  */
	sctp_skb_क्रम_each(pos, &ulpq->lobby, पंचांगp) अणु
		cevent = (काष्ठा sctp_ulpevent *) pos->cb;
		csid = cevent->stream;
		cssn = cevent->ssn;

		/* Have we gone too far?  */
		अगर (csid > sid)
			अवरोध;

		/* Have we not gone far enough?  */
		अगर (csid < sid)
			जारी;

		अगर (cssn != sctp_ssn_peek(stream, in, sid))
			अवरोध;

		/* Found it, so mark in the stream. */
		sctp_ssn_next(stream, in, sid);

		__skb_unlink(pos, &ulpq->lobby);

		/* Attach all gathered skbs to the event.  */
		__skb_queue_tail(event_list, pos);
	पूर्ण
पूर्ण

/* Helper function to store chunks needing ordering.  */
अटल व्योम sctp_ulpq_store_ordered(काष्ठा sctp_ulpq *ulpq,
					   काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff *pos;
	काष्ठा sctp_ulpevent *cevent;
	__u16 sid, csid;
	__u16 ssn, cssn;

	pos = skb_peek_tail(&ulpq->lobby);
	अगर (!pos) अणु
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
		वापस;
	पूर्ण

	sid = event->stream;
	ssn = event->ssn;

	cevent = (काष्ठा sctp_ulpevent *) pos->cb;
	csid = cevent->stream;
	cssn = cevent->ssn;
	अगर (sid > csid) अणु
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
		वापस;
	पूर्ण

	अगर ((sid == csid) && SSN_lt(cssn, ssn)) अणु
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
		वापस;
	पूर्ण

	/* Find the right place in this list.  We store them by
	 * stream ID and then by SSN.
	 */
	skb_queue_walk(&ulpq->lobby, pos) अणु
		cevent = (काष्ठा sctp_ulpevent *) pos->cb;
		csid = cevent->stream;
		cssn = cevent->ssn;

		अगर (csid > sid)
			अवरोध;
		अगर (csid == sid && SSN_lt(ssn, cssn))
			अवरोध;
	पूर्ण


	/* Insert beक्रमe pos. */
	__skb_queue_beक्रमe(&ulpq->lobby, pos, sctp_event2skb(event));
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_ulpq_order(काष्ठा sctp_ulpq *ulpq,
					     काष्ठा sctp_ulpevent *event)
अणु
	__u16 sid, ssn;
	काष्ठा sctp_stream *stream;

	/* Check अगर this message needs ordering.  */
	अगर (event->msg_flags & SCTP_DATA_UNORDERED)
		वापस event;

	/* Note: The stream ID must be verअगरied beक्रमe this routine.  */
	sid = event->stream;
	ssn = event->ssn;
	stream  = &ulpq->asoc->stream;

	/* Is this the expected SSN क्रम this stream ID?  */
	अगर (ssn != sctp_ssn_peek(stream, in, sid)) अणु
		/* We've received something out of order, so find where it
		 * needs to be placed.  We order by stream and then by SSN.
		 */
		sctp_ulpq_store_ordered(ulpq, event);
		वापस शून्य;
	पूर्ण

	/* Mark that the next chunk has been found.  */
	sctp_ssn_next(stream, in, sid);

	/* Go find any other chunks that were रुकोing क्रम
	 * ordering.
	 */
	sctp_ulpq_retrieve_ordered(ulpq, event);

	वापस event;
पूर्ण

/* Helper function to gather skbs that have possibly become
 * ordered by क्रमward tsn skipping their dependencies.
 */
अटल व्योम sctp_ulpq_reap_ordered(काष्ठा sctp_ulpq *ulpq, __u16 sid)
अणु
	काष्ठा sk_buff *pos, *पंचांगp;
	काष्ठा sctp_ulpevent *cevent;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_stream *stream;
	काष्ठा sk_buff_head temp;
	काष्ठा sk_buff_head *lobby = &ulpq->lobby;
	__u16 csid, cssn;

	stream = &ulpq->asoc->stream;

	/* We are holding the chunks by stream, by SSN.  */
	skb_queue_head_init(&temp);
	event = शून्य;
	sctp_skb_क्रम_each(pos, lobby, पंचांगp) अणु
		cevent = (काष्ठा sctp_ulpevent *) pos->cb;
		csid = cevent->stream;
		cssn = cevent->ssn;

		/* Have we gone too far?  */
		अगर (csid > sid)
			अवरोध;

		/* Have we not gone far enough?  */
		अगर (csid < sid)
			जारी;

		/* see अगर this ssn has been marked by skipping */
		अगर (!SSN_lt(cssn, sctp_ssn_peek(stream, in, csid)))
			अवरोध;

		__skb_unlink(pos, lobby);
		अगर (!event)
			/* Create a temporary list to collect chunks on.  */
			event = sctp_skb2event(pos);

		/* Attach all gathered skbs to the event.  */
		__skb_queue_tail(&temp, pos);
	पूर्ण

	/* If we didn't reap any data, see अगर the next expected SSN
	 * is next on the queue and अगर so, use that.
	 */
	अगर (event == शून्य && pos != (काष्ठा sk_buff *)lobby) अणु
		cevent = (काष्ठा sctp_ulpevent *) pos->cb;
		csid = cevent->stream;
		cssn = cevent->ssn;

		अगर (csid == sid && cssn == sctp_ssn_peek(stream, in, csid)) अणु
			sctp_ssn_next(stream, in, csid);
			__skb_unlink(pos, lobby);
			__skb_queue_tail(&temp, pos);
			event = sctp_skb2event(pos);
		पूर्ण
	पूर्ण

	/* Send event to the ULP.  'event' is the sctp_ulpevent क्रम
	 * very first SKB on the 'temp' list.
	 */
	अगर (event) अणु
		/* see अगर we have more ordered that we can deliver */
		sctp_ulpq_retrieve_ordered(ulpq, event);
		sctp_ulpq_tail_event(ulpq, &temp);
	पूर्ण
पूर्ण

/* Skip over an SSN. This is used during the processing of
 * Forwared TSN chunk to skip over the abanकरोned ordered data
 */
व्योम sctp_ulpq_skip(काष्ठा sctp_ulpq *ulpq, __u16 sid, __u16 ssn)
अणु
	काष्ठा sctp_stream *stream;

	/* Note: The stream ID must be verअगरied beक्रमe this routine.  */
	stream  = &ulpq->asoc->stream;

	/* Is this an old SSN?  If so ignore. */
	अगर (SSN_lt(ssn, sctp_ssn_peek(stream, in, sid)))
		वापस;

	/* Mark that we are no दीर्घer expecting this SSN or lower. */
	sctp_ssn_skip(stream, in, sid, ssn);

	/* Go find any other chunks that were रुकोing क्रम
	 * ordering and deliver them अगर needed.
	 */
	sctp_ulpq_reap_ordered(ulpq, sid);
पूर्ण

__u16 sctp_ulpq_renege_list(काष्ठा sctp_ulpq *ulpq, काष्ठा sk_buff_head *list,
			    __u16 needed)
अणु
	__u16 मुक्तd = 0;
	__u32 tsn, last_tsn;
	काष्ठा sk_buff *skb, *flist, *last;
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_tsnmap *tsnmap;

	tsnmap = &ulpq->asoc->peer.tsn_map;

	जबतक ((skb = skb_peek_tail(list)) != शून्य) अणु
		event = sctp_skb2event(skb);
		tsn = event->tsn;

		/* Don't renege below the Cumulative TSN ACK Poपूर्णांक. */
		अगर (TSN_lte(tsn, sctp_tsnmap_get_ctsn(tsnmap)))
			अवरोध;

		/* Events in ordering queue may have multiple fragments
		 * corresponding to additional TSNs.  Sum the total
		 * मुक्तd space; find the last TSN.
		 */
		मुक्तd += skb_headlen(skb);
		flist = skb_shinfo(skb)->frag_list;
		क्रम (last = flist; flist; flist = flist->next) अणु
			last = flist;
			मुक्तd += skb_headlen(last);
		पूर्ण
		अगर (last)
			last_tsn = sctp_skb2event(last)->tsn;
		अन्यथा
			last_tsn = tsn;

		/* Unlink the event, then renege all applicable TSNs. */
		__skb_unlink(skb, list);
		sctp_ulpevent_मुक्त(event);
		जबतक (TSN_lte(tsn, last_tsn)) अणु
			sctp_tsnmap_renege(tsnmap, tsn);
			tsn++;
		पूर्ण
		अगर (मुक्तd >= needed)
			वापस मुक्तd;
	पूर्ण

	वापस मुक्तd;
पूर्ण

/* Renege 'needed' bytes from the ordering queue. */
अटल __u16 sctp_ulpq_renege_order(काष्ठा sctp_ulpq *ulpq, __u16 needed)
अणु
	वापस sctp_ulpq_renege_list(ulpq, &ulpq->lobby, needed);
पूर्ण

/* Renege 'needed' bytes from the reassembly queue. */
अटल __u16 sctp_ulpq_renege_frags(काष्ठा sctp_ulpq *ulpq, __u16 needed)
अणु
	वापस sctp_ulpq_renege_list(ulpq, &ulpq->reयंत्र, needed);
पूर्ण

/* Partial deliver the first message as there is pressure on rwnd. */
व्योम sctp_ulpq_partial_delivery(काष्ठा sctp_ulpq *ulpq,
				gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_sock *sp;
	__u32 ctsn;
	काष्ठा sk_buff *skb;

	asoc = ulpq->asoc;
	sp = sctp_sk(asoc->base.sk);

	/* If the association is alपढ़ोy in Partial Delivery mode
	 * we have nothing to करो.
	 */
	अगर (ulpq->pd_mode)
		वापस;

	/* Data must be at or below the Cumulative TSN ACK Poपूर्णांक to
	 * start partial delivery.
	 */
	skb = skb_peek(&asoc->ulpq.reयंत्र);
	अगर (skb != शून्य) अणु
		ctsn = sctp_skb2event(skb)->tsn;
		अगर (!TSN_lte(ctsn, sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map)))
			वापस;
	पूर्ण

	/* If the user enabled fragment पूर्णांकerleave socket option,
	 * multiple associations can enter partial delivery.
	 * Otherwise, we can only enter partial delivery अगर the
	 * socket is not in partial deliver mode.
	 */
	अगर (sp->frag_पूर्णांकerleave || atomic_पढ़ो(&sp->pd_mode) == 0) अणु
		/* Is partial delivery possible?  */
		event = sctp_ulpq_retrieve_first(ulpq);
		/* Send event to the ULP.   */
		अगर (event) अणु
			काष्ठा sk_buff_head temp;

			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));
			sctp_ulpq_tail_event(ulpq, &temp);
			sctp_ulpq_set_pd(ulpq);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* Renege some packets to make room क्रम an incoming chunk.  */
व्योम sctp_ulpq_renege(काष्ठा sctp_ulpq *ulpq, काष्ठा sctp_chunk *chunk,
		      gfp_t gfp)
अणु
	काष्ठा sctp_association *asoc = ulpq->asoc;
	__u32 मुक्तd = 0;
	__u16 needed;

	needed = ntohs(chunk->chunk_hdr->length) -
		 माप(काष्ठा sctp_data_chunk);

	अगर (skb_queue_empty(&asoc->base.sk->sk_receive_queue)) अणु
		मुक्तd = sctp_ulpq_renege_order(ulpq, needed);
		अगर (मुक्तd < needed)
			मुक्तd += sctp_ulpq_renege_frags(ulpq, needed - मुक्तd);
	पूर्ण
	/* If able to मुक्त enough room, accept this chunk. */
	अगर (sk_rmem_schedule(asoc->base.sk, chunk->skb, needed) &&
	    मुक्तd >= needed) अणु
		पूर्णांक retval = sctp_ulpq_tail_data(ulpq, chunk, gfp);
		/*
		 * Enter partial delivery अगर chunk has not been
		 * delivered; otherwise, drain the reassembly queue.
		 */
		अगर (retval <= 0)
			sctp_ulpq_partial_delivery(ulpq, gfp);
		अन्यथा अगर (retval == 1)
			sctp_ulpq_reयंत्र_drain(ulpq);
	पूर्ण

	sk_mem_reclaim(asoc->base.sk);
पूर्ण



/* Notअगरy the application अगर an association is पातed and in
 * partial delivery mode.  Send up any pending received messages.
 */
व्योम sctp_ulpq_पात_pd(काष्ठा sctp_ulpq *ulpq, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *ev = शून्य;
	काष्ठा sctp_sock *sp;
	काष्ठा sock *sk;

	अगर (!ulpq->pd_mode)
		वापस;

	sk = ulpq->asoc->base.sk;
	sp = sctp_sk(sk);
	अगर (sctp_ulpevent_type_enabled(ulpq->asoc->subscribe,
				       SCTP_PARTIAL_DELIVERY_EVENT))
		ev = sctp_ulpevent_make_pdapi(ulpq->asoc,
					      SCTP_PARTIAL_DELIVERY_ABORTED,
					      0, 0, 0, gfp);
	अगर (ev)
		__skb_queue_tail(&sk->sk_receive_queue, sctp_event2skb(ev));

	/* If there is data रुकोing, send it up the socket now. */
	अगर ((sctp_ulpq_clear_pd(ulpq) || ev) && !sp->data_पढ़ोy_संकेतled) अणु
		sp->data_पढ़ोy_संकेतled = 1;
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
पूर्ण
