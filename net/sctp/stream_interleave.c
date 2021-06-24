<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright Red Hat Inc. 2017
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions implement sctp stream message पूर्णांकerleaving, mostly
 * including I-DATA and I-FORWARD-TSN chunks process.
 *
 * Please send any bug reports or fixes you make to the
 * email addresched(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Xin Long <lucien.xin@gmail.com>
 */

#समावेश <net/busy_poll.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/ulpevent.h>
#समावेश <linux/sctp.h>

अटल काष्ठा sctp_chunk *sctp_make_idatafrag_empty(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_sndrcvinfo *sinfo,
					पूर्णांक len, __u8 flags, gfp_t gfp)
अणु
	काष्ठा sctp_chunk *retval;
	काष्ठा sctp_idatahdr dp;

	स_रखो(&dp, 0, माप(dp));
	dp.stream = htons(sinfo->sinfo_stream);

	अगर (sinfo->sinfo_flags & SCTP_UNORDERED)
		flags |= SCTP_DATA_UNORDERED;

	retval = sctp_make_idata(asoc, flags, माप(dp) + len, gfp);
	अगर (!retval)
		वापस शून्य;

	retval->subh.idata_hdr = sctp_addto_chunk(retval, माप(dp), &dp);
	स_नकल(&retval->sinfo, sinfo, माप(काष्ठा sctp_sndrcvinfo));

	वापस retval;
पूर्ण

अटल व्योम sctp_chunk_assign_mid(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_stream *stream;
	काष्ठा sctp_chunk *lchunk;
	__u32 cfsn = 0;
	__u16 sid;

	अगर (chunk->has_mid)
		वापस;

	sid = sctp_chunk_stream_no(chunk);
	stream = &chunk->asoc->stream;

	list_क्रम_each_entry(lchunk, &chunk->msg->chunks, frag_list) अणु
		काष्ठा sctp_idatahdr *hdr;
		__u32 mid;

		lchunk->has_mid = 1;

		hdr = lchunk->subh.idata_hdr;

		अगर (lchunk->chunk_hdr->flags & SCTP_DATA_FIRST_FRAG)
			hdr->ppid = lchunk->sinfo.sinfo_ppid;
		अन्यथा
			hdr->fsn = htonl(cfsn++);

		अगर (lchunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) अणु
			mid = lchunk->chunk_hdr->flags & SCTP_DATA_LAST_FRAG ?
				sctp_mid_uo_next(stream, out, sid) :
				sctp_mid_uo_peek(stream, out, sid);
		पूर्ण अन्यथा अणु
			mid = lchunk->chunk_hdr->flags & SCTP_DATA_LAST_FRAG ?
				sctp_mid_next(stream, out, sid) :
				sctp_mid_peek(stream, out, sid);
		पूर्ण
		hdr->mid = htonl(mid);
	पूर्ण
पूर्ण

अटल bool sctp_validate_data(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_stream *stream;
	__u16 sid, ssn;

	अगर (chunk->chunk_hdr->type != SCTP_CID_DATA)
		वापस false;

	अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
		वापस true;

	stream = &chunk->asoc->stream;
	sid = sctp_chunk_stream_no(chunk);
	ssn = ntohs(chunk->subh.data_hdr->ssn);

	वापस !SSN_lt(ssn, sctp_ssn_peek(stream, in, sid));
पूर्ण

अटल bool sctp_validate_idata(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_stream *stream;
	__u32 mid;
	__u16 sid;

	अगर (chunk->chunk_hdr->type != SCTP_CID_I_DATA)
		वापस false;

	अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
		वापस true;

	stream = &chunk->asoc->stream;
	sid = sctp_chunk_stream_no(chunk);
	mid = ntohl(chunk->subh.idata_hdr->mid);

	वापस !MID_lt(mid, sctp_mid_peek(stream, in, sid));
पूर्ण

अटल व्योम sctp_पूर्णांकl_store_reयंत्र(काष्ठा sctp_ulpq *ulpq,
				  काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_ulpevent *cevent;
	काष्ठा sk_buff *pos, *loc;

	pos = skb_peek_tail(&ulpq->reयंत्र);
	अगर (!pos) अणु
		__skb_queue_tail(&ulpq->reयंत्र, sctp_event2skb(event));
		वापस;
	पूर्ण

	cevent = sctp_skb2event(pos);

	अगर (event->stream == cevent->stream &&
	    event->mid == cevent->mid &&
	    (cevent->msg_flags & SCTP_DATA_FIRST_FRAG ||
	     (!(event->msg_flags & SCTP_DATA_FIRST_FRAG) &&
	      event->fsn > cevent->fsn))) अणु
		__skb_queue_tail(&ulpq->reयंत्र, sctp_event2skb(event));
		वापस;
	पूर्ण

	अगर ((event->stream == cevent->stream &&
	     MID_lt(cevent->mid, event->mid)) ||
	    event->stream > cevent->stream) अणु
		__skb_queue_tail(&ulpq->reयंत्र, sctp_event2skb(event));
		वापस;
	पूर्ण

	loc = शून्य;
	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		cevent = sctp_skb2event(pos);

		अगर (event->stream < cevent->stream ||
		    (event->stream == cevent->stream &&
		     MID_lt(event->mid, cevent->mid))) अणु
			loc = pos;
			अवरोध;
		पूर्ण
		अगर (event->stream == cevent->stream &&
		    event->mid == cevent->mid &&
		    !(cevent->msg_flags & SCTP_DATA_FIRST_FRAG) &&
		    (event->msg_flags & SCTP_DATA_FIRST_FRAG ||
		     event->fsn < cevent->fsn)) अणु
			loc = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!loc)
		__skb_queue_tail(&ulpq->reयंत्र, sctp_event2skb(event));
	अन्यथा
		__skb_queue_beक्रमe(&ulpq->reयंत्र, loc, sctp_event2skb(event));
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_retrieve_partial(
						काष्ठा sctp_ulpq *ulpq,
						काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff *first_frag = शून्य;
	काष्ठा sk_buff *last_frag = शून्य;
	काष्ठा sctp_ulpevent *retval;
	काष्ठा sctp_stream_in *sin;
	काष्ठा sk_buff *pos;
	__u32 next_fsn = 0;
	पूर्णांक is_last = 0;

	sin = sctp_stream_in(&ulpq->asoc->stream, event->stream);

	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		काष्ठा sctp_ulpevent *cevent = sctp_skb2event(pos);

		अगर (cevent->stream < event->stream)
			जारी;

		अगर (cevent->stream > event->stream ||
		    cevent->mid != sin->mid)
			अवरोध;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			जाओ out;
		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (!first_frag) अणु
				अगर (cevent->fsn == sin->fsn) अणु
					first_frag = pos;
					last_frag = pos;
					next_fsn = cevent->fsn + 1;
				पूर्ण
			पूर्ण अन्यथा अगर (cevent->fsn == next_fsn) अणु
				last_frag = pos;
				next_fsn++;
			पूर्ण अन्यथा अणु
				जाओ out;
			पूर्ण
			अवरोध;
		हाल SCTP_DATA_LAST_FRAG:
			अगर (!first_frag) अणु
				अगर (cevent->fsn == sin->fsn) अणु
					first_frag = pos;
					last_frag = pos;
					next_fsn = 0;
					is_last = 1;
				पूर्ण
			पूर्ण अन्यथा अगर (cevent->fsn == next_fsn) अणु
				last_frag = pos;
				next_fsn = 0;
				is_last = 1;
			पूर्ण
			जाओ out;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (!first_frag)
		वापस शून्य;

	retval = sctp_make_reassembled_event(ulpq->asoc->base.net, &ulpq->reयंत्र,
					     first_frag, last_frag);
	अगर (retval) अणु
		sin->fsn = next_fsn;
		अगर (is_last) अणु
			retval->msg_flags |= MSG_EOR;
			sin->pd_mode = 0;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_retrieve_reassembled(
						काष्ठा sctp_ulpq *ulpq,
						काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_association *asoc = ulpq->asoc;
	काष्ठा sk_buff *pos, *first_frag = शून्य;
	काष्ठा sctp_ulpevent *retval = शून्य;
	काष्ठा sk_buff *pd_first = शून्य;
	काष्ठा sk_buff *pd_last = शून्य;
	काष्ठा sctp_stream_in *sin;
	__u32 next_fsn = 0;
	__u32 pd_poपूर्णांक = 0;
	__u32 pd_len = 0;
	__u32 mid = 0;

	sin = sctp_stream_in(&ulpq->asoc->stream, event->stream);

	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		काष्ठा sctp_ulpevent *cevent = sctp_skb2event(pos);

		अगर (cevent->stream < event->stream)
			जारी;
		अगर (cevent->stream > event->stream)
			अवरोध;

		अगर (MID_lt(cevent->mid, event->mid))
			जारी;
		अगर (MID_lt(event->mid, cevent->mid))
			अवरोध;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			अगर (cevent->mid == sin->mid) अणु
				pd_first = pos;
				pd_last = pos;
				pd_len = pos->len;
			पूर्ण

			first_frag = pos;
			next_fsn = 0;
			mid = cevent->mid;
			अवरोध;

		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (first_frag && cevent->mid == mid &&
			    cevent->fsn == next_fsn) अणु
				next_fsn++;
				अगर (pd_first) अणु
					pd_last = pos;
					pd_len += pos->len;
				पूर्ण
			पूर्ण अन्यथा अणु
				first_frag = शून्य;
			पूर्ण
			अवरोध;

		हाल SCTP_DATA_LAST_FRAG:
			अगर (first_frag && cevent->mid == mid &&
			    cevent->fsn == next_fsn)
				जाओ found;
			अन्यथा
				first_frag = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pd_first)
		जाओ out;

	pd_poपूर्णांक = sctp_sk(asoc->base.sk)->pd_poपूर्णांक;
	अगर (pd_poपूर्णांक && pd_poपूर्णांक <= pd_len) अणु
		retval = sctp_make_reassembled_event(asoc->base.net,
						     &ulpq->reयंत्र,
						     pd_first, pd_last);
		अगर (retval) अणु
			sin->fsn = next_fsn;
			sin->pd_mode = 1;
		पूर्ण
	पूर्ण
	जाओ out;

found:
	retval = sctp_make_reassembled_event(asoc->base.net, &ulpq->reयंत्र,
					     first_frag, pos);
	अगर (retval)
		retval->msg_flags |= MSG_EOR;

out:
	वापस retval;
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_reयंत्र(काष्ठा sctp_ulpq *ulpq,
					     काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_ulpevent *retval = शून्य;
	काष्ठा sctp_stream_in *sin;

	अगर (SCTP_DATA_NOT_FRAG == (event->msg_flags & SCTP_DATA_FRAG_MASK)) अणु
		event->msg_flags |= MSG_EOR;
		वापस event;
	पूर्ण

	sctp_पूर्णांकl_store_reयंत्र(ulpq, event);

	sin = sctp_stream_in(&ulpq->asoc->stream, event->stream);
	अगर (sin->pd_mode && event->mid == sin->mid &&
	    event->fsn == sin->fsn)
		retval = sctp_पूर्णांकl_retrieve_partial(ulpq, event);

	अगर (!retval)
		retval = sctp_पूर्णांकl_retrieve_reassembled(ulpq, event);

	वापस retval;
पूर्ण

अटल व्योम sctp_पूर्णांकl_store_ordered(काष्ठा sctp_ulpq *ulpq,
				    काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_ulpevent *cevent;
	काष्ठा sk_buff *pos, *loc;

	pos = skb_peek_tail(&ulpq->lobby);
	अगर (!pos) अणु
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
		वापस;
	पूर्ण

	cevent = (काष्ठा sctp_ulpevent *)pos->cb;
	अगर (event->stream == cevent->stream &&
	    MID_lt(cevent->mid, event->mid)) अणु
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
		वापस;
	पूर्ण

	अगर (event->stream > cevent->stream) अणु
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
		वापस;
	पूर्ण

	loc = शून्य;
	skb_queue_walk(&ulpq->lobby, pos) अणु
		cevent = (काष्ठा sctp_ulpevent *)pos->cb;

		अगर (cevent->stream > event->stream) अणु
			loc = pos;
			अवरोध;
		पूर्ण
		अगर (cevent->stream == event->stream &&
		    MID_lt(event->mid, cevent->mid)) अणु
			loc = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!loc)
		__skb_queue_tail(&ulpq->lobby, sctp_event2skb(event));
	अन्यथा
		__skb_queue_beक्रमe(&ulpq->lobby, loc, sctp_event2skb(event));
पूर्ण

अटल व्योम sctp_पूर्णांकl_retrieve_ordered(काष्ठा sctp_ulpq *ulpq,
				       काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff_head *event_list;
	काष्ठा sctp_stream *stream;
	काष्ठा sk_buff *pos, *पंचांगp;
	__u16 sid = event->stream;

	stream  = &ulpq->asoc->stream;
	event_list = (काष्ठा sk_buff_head *)sctp_event2skb(event)->prev;

	sctp_skb_क्रम_each(pos, &ulpq->lobby, पंचांगp) अणु
		काष्ठा sctp_ulpevent *cevent = (काष्ठा sctp_ulpevent *)pos->cb;

		अगर (cevent->stream > sid)
			अवरोध;

		अगर (cevent->stream < sid)
			जारी;

		अगर (cevent->mid != sctp_mid_peek(stream, in, sid))
			अवरोध;

		sctp_mid_next(stream, in, sid);

		__skb_unlink(pos, &ulpq->lobby);

		__skb_queue_tail(event_list, pos);
	पूर्ण
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_order(काष्ठा sctp_ulpq *ulpq,
					     काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_stream *stream;
	__u16 sid;

	stream  = &ulpq->asoc->stream;
	sid = event->stream;

	अगर (event->mid != sctp_mid_peek(stream, in, sid)) अणु
		sctp_पूर्णांकl_store_ordered(ulpq, event);
		वापस शून्य;
	पूर्ण

	sctp_mid_next(stream, in, sid);

	sctp_पूर्णांकl_retrieve_ordered(ulpq, event);

	वापस event;
पूर्ण

अटल पूर्णांक sctp_enqueue_event(काष्ठा sctp_ulpq *ulpq,
			      काष्ठा sk_buff_head *skb_list)
अणु
	काष्ठा sock *sk = ulpq->asoc->base.sk;
	काष्ठा sctp_sock *sp = sctp_sk(sk);
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff *skb;

	skb = __skb_peek(skb_list);
	event = sctp_skb2event(skb);

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN &&
	    (sk->sk_shutकरोwn & SEND_SHUTDOWN ||
	     !sctp_ulpevent_is_notअगरication(event)))
		जाओ out_मुक्त;

	अगर (!sctp_ulpevent_is_notअगरication(event)) अणु
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	पूर्ण

	अगर (!sctp_ulpevent_is_enabled(event, ulpq->asoc->subscribe))
		जाओ out_मुक्त;

	अगर (skb_list)
		skb_queue_splice_tail_init(skb_list,
					   &sk->sk_receive_queue);
	अन्यथा
		__skb_queue_tail(&sk->sk_receive_queue, skb);

	अगर (!sp->data_पढ़ोy_संकेतled) अणु
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

अटल व्योम sctp_पूर्णांकl_store_reयंत्र_uo(काष्ठा sctp_ulpq *ulpq,
				     काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_ulpevent *cevent;
	काष्ठा sk_buff *pos;

	pos = skb_peek_tail(&ulpq->reयंत्र_uo);
	अगर (!pos) अणु
		__skb_queue_tail(&ulpq->reयंत्र_uo, sctp_event2skb(event));
		वापस;
	पूर्ण

	cevent = sctp_skb2event(pos);

	अगर (event->stream == cevent->stream &&
	    event->mid == cevent->mid &&
	    (cevent->msg_flags & SCTP_DATA_FIRST_FRAG ||
	     (!(event->msg_flags & SCTP_DATA_FIRST_FRAG) &&
	      event->fsn > cevent->fsn))) अणु
		__skb_queue_tail(&ulpq->reयंत्र_uo, sctp_event2skb(event));
		वापस;
	पूर्ण

	अगर ((event->stream == cevent->stream &&
	     MID_lt(cevent->mid, event->mid)) ||
	    event->stream > cevent->stream) अणु
		__skb_queue_tail(&ulpq->reयंत्र_uo, sctp_event2skb(event));
		वापस;
	पूर्ण

	skb_queue_walk(&ulpq->reयंत्र_uo, pos) अणु
		cevent = sctp_skb2event(pos);

		अगर (event->stream < cevent->stream ||
		    (event->stream == cevent->stream &&
		     MID_lt(event->mid, cevent->mid)))
			अवरोध;

		अगर (event->stream == cevent->stream &&
		    event->mid == cevent->mid &&
		    !(cevent->msg_flags & SCTP_DATA_FIRST_FRAG) &&
		    (event->msg_flags & SCTP_DATA_FIRST_FRAG ||
		     event->fsn < cevent->fsn))
			अवरोध;
	पूर्ण

	__skb_queue_beक्रमe(&ulpq->reयंत्र_uo, pos, sctp_event2skb(event));
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_retrieve_partial_uo(
						काष्ठा sctp_ulpq *ulpq,
						काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff *first_frag = शून्य;
	काष्ठा sk_buff *last_frag = शून्य;
	काष्ठा sctp_ulpevent *retval;
	काष्ठा sctp_stream_in *sin;
	काष्ठा sk_buff *pos;
	__u32 next_fsn = 0;
	पूर्णांक is_last = 0;

	sin = sctp_stream_in(&ulpq->asoc->stream, event->stream);

	skb_queue_walk(&ulpq->reयंत्र_uo, pos) अणु
		काष्ठा sctp_ulpevent *cevent = sctp_skb2event(pos);

		अगर (cevent->stream < event->stream)
			जारी;
		अगर (cevent->stream > event->stream)
			अवरोध;

		अगर (MID_lt(cevent->mid, sin->mid_uo))
			जारी;
		अगर (MID_lt(sin->mid_uo, cevent->mid))
			अवरोध;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			जाओ out;
		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (!first_frag) अणु
				अगर (cevent->fsn == sin->fsn_uo) अणु
					first_frag = pos;
					last_frag = pos;
					next_fsn = cevent->fsn + 1;
				पूर्ण
			पूर्ण अन्यथा अगर (cevent->fsn == next_fsn) अणु
				last_frag = pos;
				next_fsn++;
			पूर्ण अन्यथा अणु
				जाओ out;
			पूर्ण
			अवरोध;
		हाल SCTP_DATA_LAST_FRAG:
			अगर (!first_frag) अणु
				अगर (cevent->fsn == sin->fsn_uo) अणु
					first_frag = pos;
					last_frag = pos;
					next_fsn = 0;
					is_last = 1;
				पूर्ण
			पूर्ण अन्यथा अगर (cevent->fsn == next_fsn) अणु
				last_frag = pos;
				next_fsn = 0;
				is_last = 1;
			पूर्ण
			जाओ out;
		शेष:
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (!first_frag)
		वापस शून्य;

	retval = sctp_make_reassembled_event(ulpq->asoc->base.net,
					     &ulpq->reयंत्र_uo, first_frag,
					     last_frag);
	अगर (retval) अणु
		sin->fsn_uo = next_fsn;
		अगर (is_last) अणु
			retval->msg_flags |= MSG_EOR;
			sin->pd_mode_uo = 0;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_retrieve_reassembled_uo(
						काष्ठा sctp_ulpq *ulpq,
						काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_association *asoc = ulpq->asoc;
	काष्ठा sk_buff *pos, *first_frag = शून्य;
	काष्ठा sctp_ulpevent *retval = शून्य;
	काष्ठा sk_buff *pd_first = शून्य;
	काष्ठा sk_buff *pd_last = शून्य;
	काष्ठा sctp_stream_in *sin;
	__u32 next_fsn = 0;
	__u32 pd_poपूर्णांक = 0;
	__u32 pd_len = 0;
	__u32 mid = 0;

	sin = sctp_stream_in(&ulpq->asoc->stream, event->stream);

	skb_queue_walk(&ulpq->reयंत्र_uo, pos) अणु
		काष्ठा sctp_ulpevent *cevent = sctp_skb2event(pos);

		अगर (cevent->stream < event->stream)
			जारी;
		अगर (cevent->stream > event->stream)
			अवरोध;

		अगर (MID_lt(cevent->mid, event->mid))
			जारी;
		अगर (MID_lt(event->mid, cevent->mid))
			अवरोध;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			अगर (!sin->pd_mode_uo) अणु
				sin->mid_uo = cevent->mid;
				pd_first = pos;
				pd_last = pos;
				pd_len = pos->len;
			पूर्ण

			first_frag = pos;
			next_fsn = 0;
			mid = cevent->mid;
			अवरोध;

		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (first_frag && cevent->mid == mid &&
			    cevent->fsn == next_fsn) अणु
				next_fsn++;
				अगर (pd_first) अणु
					pd_last = pos;
					pd_len += pos->len;
				पूर्ण
			पूर्ण अन्यथा अणु
				first_frag = शून्य;
			पूर्ण
			अवरोध;

		हाल SCTP_DATA_LAST_FRAG:
			अगर (first_frag && cevent->mid == mid &&
			    cevent->fsn == next_fsn)
				जाओ found;
			अन्यथा
				first_frag = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pd_first)
		जाओ out;

	pd_poपूर्णांक = sctp_sk(asoc->base.sk)->pd_poपूर्णांक;
	अगर (pd_poपूर्णांक && pd_poपूर्णांक <= pd_len) अणु
		retval = sctp_make_reassembled_event(asoc->base.net,
						     &ulpq->reयंत्र_uo,
						     pd_first, pd_last);
		अगर (retval) अणु
			sin->fsn_uo = next_fsn;
			sin->pd_mode_uo = 1;
		पूर्ण
	पूर्ण
	जाओ out;

found:
	retval = sctp_make_reassembled_event(asoc->base.net, &ulpq->reयंत्र_uo,
					     first_frag, pos);
	अगर (retval)
		retval->msg_flags |= MSG_EOR;

out:
	वापस retval;
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_reयंत्र_uo(काष्ठा sctp_ulpq *ulpq,
						काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sctp_ulpevent *retval = शून्य;
	काष्ठा sctp_stream_in *sin;

	अगर (SCTP_DATA_NOT_FRAG == (event->msg_flags & SCTP_DATA_FRAG_MASK)) अणु
		event->msg_flags |= MSG_EOR;
		वापस event;
	पूर्ण

	sctp_पूर्णांकl_store_reयंत्र_uo(ulpq, event);

	sin = sctp_stream_in(&ulpq->asoc->stream, event->stream);
	अगर (sin->pd_mode_uo && event->mid == sin->mid_uo &&
	    event->fsn == sin->fsn_uo)
		retval = sctp_पूर्णांकl_retrieve_partial_uo(ulpq, event);

	अगर (!retval)
		retval = sctp_पूर्णांकl_retrieve_reassembled_uo(ulpq, event);

	वापस retval;
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_retrieve_first_uo(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sctp_stream_in *csin, *sin = शून्य;
	काष्ठा sk_buff *first_frag = शून्य;
	काष्ठा sk_buff *last_frag = शून्य;
	काष्ठा sctp_ulpevent *retval;
	काष्ठा sk_buff *pos;
	__u32 next_fsn = 0;
	__u16 sid = 0;

	skb_queue_walk(&ulpq->reयंत्र_uo, pos) अणु
		काष्ठा sctp_ulpevent *cevent = sctp_skb2event(pos);

		csin = sctp_stream_in(&ulpq->asoc->stream, cevent->stream);
		अगर (csin->pd_mode_uo)
			जारी;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			अगर (first_frag)
				जाओ out;
			first_frag = pos;
			last_frag = pos;
			next_fsn = 0;
			sin = csin;
			sid = cevent->stream;
			sin->mid_uo = cevent->mid;
			अवरोध;
		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (!first_frag)
				अवरोध;
			अगर (cevent->stream == sid &&
			    cevent->mid == sin->mid_uo &&
			    cevent->fsn == next_fsn) अणु
				next_fsn++;
				last_frag = pos;
			पूर्ण अन्यथा अणु
				जाओ out;
			पूर्ण
			अवरोध;
		हाल SCTP_DATA_LAST_FRAG:
			अगर (first_frag)
				जाओ out;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!first_frag)
		वापस शून्य;

out:
	retval = sctp_make_reassembled_event(ulpq->asoc->base.net,
					     &ulpq->reयंत्र_uo, first_frag,
					     last_frag);
	अगर (retval) अणु
		sin->fsn_uo = next_fsn;
		sin->pd_mode_uo = 1;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक sctp_ulpevent_idata(काष्ठा sctp_ulpq *ulpq,
			       काष्ठा sctp_chunk *chunk, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff_head temp;
	पूर्णांक event_eor = 0;

	event = sctp_ulpevent_make_rcvmsg(chunk->asoc, chunk, gfp);
	अगर (!event)
		वापस -ENOMEM;

	event->mid = ntohl(chunk->subh.idata_hdr->mid);
	अगर (event->msg_flags & SCTP_DATA_FIRST_FRAG)
		event->ppid = chunk->subh.idata_hdr->ppid;
	अन्यथा
		event->fsn = ntohl(chunk->subh.idata_hdr->fsn);

	अगर (!(event->msg_flags & SCTP_DATA_UNORDERED)) अणु
		event = sctp_पूर्णांकl_reयंत्र(ulpq, event);
		अगर (event) अणु
			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));

			अगर (event->msg_flags & MSG_EOR)
				event = sctp_पूर्णांकl_order(ulpq, event);
		पूर्ण
	पूर्ण अन्यथा अणु
		event = sctp_पूर्णांकl_reयंत्र_uo(ulpq, event);
		अगर (event) अणु
			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));
		पूर्ण
	पूर्ण

	अगर (event) अणु
		event_eor = (event->msg_flags & MSG_EOR) ? 1 : 0;
		sctp_enqueue_event(ulpq, &temp);
	पूर्ण

	वापस event_eor;
पूर्ण

अटल काष्ठा sctp_ulpevent *sctp_पूर्णांकl_retrieve_first(काष्ठा sctp_ulpq *ulpq)
अणु
	काष्ठा sctp_stream_in *csin, *sin = शून्य;
	काष्ठा sk_buff *first_frag = शून्य;
	काष्ठा sk_buff *last_frag = शून्य;
	काष्ठा sctp_ulpevent *retval;
	काष्ठा sk_buff *pos;
	__u32 next_fsn = 0;
	__u16 sid = 0;

	skb_queue_walk(&ulpq->reयंत्र, pos) अणु
		काष्ठा sctp_ulpevent *cevent = sctp_skb2event(pos);

		csin = sctp_stream_in(&ulpq->asoc->stream, cevent->stream);
		अगर (csin->pd_mode)
			जारी;

		चयन (cevent->msg_flags & SCTP_DATA_FRAG_MASK) अणु
		हाल SCTP_DATA_FIRST_FRAG:
			अगर (first_frag)
				जाओ out;
			अगर (cevent->mid == csin->mid) अणु
				first_frag = pos;
				last_frag = pos;
				next_fsn = 0;
				sin = csin;
				sid = cevent->stream;
			पूर्ण
			अवरोध;
		हाल SCTP_DATA_MIDDLE_FRAG:
			अगर (!first_frag)
				अवरोध;
			अगर (cevent->stream == sid &&
			    cevent->mid == sin->mid &&
			    cevent->fsn == next_fsn) अणु
				next_fsn++;
				last_frag = pos;
			पूर्ण अन्यथा अणु
				जाओ out;
			पूर्ण
			अवरोध;
		हाल SCTP_DATA_LAST_FRAG:
			अगर (first_frag)
				जाओ out;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!first_frag)
		वापस शून्य;

out:
	retval = sctp_make_reassembled_event(ulpq->asoc->base.net,
					     &ulpq->reयंत्र, first_frag,
					     last_frag);
	अगर (retval) अणु
		sin->fsn = next_fsn;
		sin->pd_mode = 1;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम sctp_पूर्णांकl_start_pd(काष्ठा sctp_ulpq *ulpq, gfp_t gfp)
अणु
	काष्ठा sctp_ulpevent *event;
	काष्ठा sk_buff_head temp;

	अगर (!skb_queue_empty(&ulpq->reयंत्र)) अणु
		करो अणु
			event = sctp_पूर्णांकl_retrieve_first(ulpq);
			अगर (event) अणु
				skb_queue_head_init(&temp);
				__skb_queue_tail(&temp, sctp_event2skb(event));
				sctp_enqueue_event(ulpq, &temp);
			पूर्ण
		पूर्ण जबतक (event);
	पूर्ण

	अगर (!skb_queue_empty(&ulpq->reयंत्र_uo)) अणु
		करो अणु
			event = sctp_पूर्णांकl_retrieve_first_uo(ulpq);
			अगर (event) अणु
				skb_queue_head_init(&temp);
				__skb_queue_tail(&temp, sctp_event2skb(event));
				sctp_enqueue_event(ulpq, &temp);
			पूर्ण
		पूर्ण जबतक (event);
	पूर्ण
पूर्ण

अटल व्योम sctp_renege_events(काष्ठा sctp_ulpq *ulpq, काष्ठा sctp_chunk *chunk,
			       gfp_t gfp)
अणु
	काष्ठा sctp_association *asoc = ulpq->asoc;
	__u32 मुक्तd = 0;
	__u16 needed;

	needed = ntohs(chunk->chunk_hdr->length) -
		 माप(काष्ठा sctp_idata_chunk);

	अगर (skb_queue_empty(&asoc->base.sk->sk_receive_queue)) अणु
		मुक्तd = sctp_ulpq_renege_list(ulpq, &ulpq->lobby, needed);
		अगर (मुक्तd < needed)
			मुक्तd += sctp_ulpq_renege_list(ulpq, &ulpq->reयंत्र,
						       needed);
		अगर (मुक्तd < needed)
			मुक्तd += sctp_ulpq_renege_list(ulpq, &ulpq->reयंत्र_uo,
						       needed);
	पूर्ण

	अगर (मुक्तd >= needed && sctp_ulpevent_idata(ulpq, chunk, gfp) <= 0)
		sctp_पूर्णांकl_start_pd(ulpq, gfp);

	sk_mem_reclaim(asoc->base.sk);
पूर्ण

अटल व्योम sctp_पूर्णांकl_stream_पात_pd(काष्ठा sctp_ulpq *ulpq, __u16 sid,
				      __u32 mid, __u16 flags, gfp_t gfp)
अणु
	काष्ठा sock *sk = ulpq->asoc->base.sk;
	काष्ठा sctp_ulpevent *ev = शून्य;

	अगर (!sctp_ulpevent_type_enabled(ulpq->asoc->subscribe,
					SCTP_PARTIAL_DELIVERY_EVENT))
		वापस;

	ev = sctp_ulpevent_make_pdapi(ulpq->asoc, SCTP_PARTIAL_DELIVERY_ABORTED,
				      sid, mid, flags, gfp);
	अगर (ev) अणु
		काष्ठा sctp_sock *sp = sctp_sk(sk);

		__skb_queue_tail(&sk->sk_receive_queue, sctp_event2skb(ev));

		अगर (!sp->data_पढ़ोy_संकेतled) अणु
			sp->data_पढ़ोy_संकेतled = 1;
			sk->sk_data_पढ़ोy(sk);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sctp_पूर्णांकl_reap_ordered(काष्ठा sctp_ulpq *ulpq, __u16 sid)
अणु
	काष्ठा sctp_stream *stream = &ulpq->asoc->stream;
	काष्ठा sctp_ulpevent *cevent, *event = शून्य;
	काष्ठा sk_buff_head *lobby = &ulpq->lobby;
	काष्ठा sk_buff *pos, *पंचांगp;
	काष्ठा sk_buff_head temp;
	__u16 csid;
	__u32 cmid;

	skb_queue_head_init(&temp);
	sctp_skb_क्रम_each(pos, lobby, पंचांगp) अणु
		cevent = (काष्ठा sctp_ulpevent *)pos->cb;
		csid = cevent->stream;
		cmid = cevent->mid;

		अगर (csid > sid)
			अवरोध;

		अगर (csid < sid)
			जारी;

		अगर (!MID_lt(cmid, sctp_mid_peek(stream, in, csid)))
			अवरोध;

		__skb_unlink(pos, lobby);
		अगर (!event)
			event = sctp_skb2event(pos);

		__skb_queue_tail(&temp, pos);
	पूर्ण

	अगर (!event && pos != (काष्ठा sk_buff *)lobby) अणु
		cevent = (काष्ठा sctp_ulpevent *)pos->cb;
		csid = cevent->stream;
		cmid = cevent->mid;

		अगर (csid == sid && cmid == sctp_mid_peek(stream, in, csid)) अणु
			sctp_mid_next(stream, in, csid);
			__skb_unlink(pos, lobby);
			__skb_queue_tail(&temp, pos);
			event = sctp_skb2event(pos);
		पूर्ण
	पूर्ण

	अगर (event) अणु
		sctp_पूर्णांकl_retrieve_ordered(ulpq, event);
		sctp_enqueue_event(ulpq, &temp);
	पूर्ण
पूर्ण

अटल व्योम sctp_पूर्णांकl_पात_pd(काष्ठा sctp_ulpq *ulpq, gfp_t gfp)
अणु
	काष्ठा sctp_stream *stream = &ulpq->asoc->stream;
	__u16 sid;

	क्रम (sid = 0; sid < stream->incnt; sid++) अणु
		काष्ठा sctp_stream_in *sin = SCTP_SI(stream, sid);
		__u32 mid;

		अगर (sin->pd_mode_uo) अणु
			sin->pd_mode_uo = 0;

			mid = sin->mid_uo;
			sctp_पूर्णांकl_stream_पात_pd(ulpq, sid, mid, 0x1, gfp);
		पूर्ण

		अगर (sin->pd_mode) अणु
			sin->pd_mode = 0;

			mid = sin->mid;
			sctp_पूर्णांकl_stream_पात_pd(ulpq, sid, mid, 0, gfp);
			sctp_mid_skip(stream, in, sid, mid);

			sctp_पूर्णांकl_reap_ordered(ulpq, sid);
		पूर्ण
	पूर्ण

	/* पूर्णांकl पात pd happens only when all data needs to be cleaned */
	sctp_ulpq_flush(ulpq);
पूर्ण

अटल अंतरभूत पूर्णांक sctp_get_skip_pos(काष्ठा sctp_अगरwdtsn_skip *skiplist,
				    पूर्णांक nskips, __be16 stream, __u8 flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nskips; i++)
		अगर (skiplist[i].stream == stream &&
		    skiplist[i].flags == flags)
			वापस i;

	वापस i;
पूर्ण

#घोषणा SCTP_FTSN_U_BIT	0x1
अटल व्योम sctp_generate_अगरtsn(काष्ठा sctp_outq *q, __u32 ctsn)
अणु
	काष्ठा sctp_अगरwdtsn_skip ftsn_skip_arr[10];
	काष्ठा sctp_association *asoc = q->asoc;
	काष्ठा sctp_chunk *ftsn_chunk = शून्य;
	काष्ठा list_head *lchunk, *temp;
	पूर्णांक nskips = 0, skip_pos;
	काष्ठा sctp_chunk *chunk;
	__u32 tsn;

	अगर (!asoc->peer.prsctp_capable)
		वापस;

	अगर (TSN_lt(asoc->adv_peer_ack_poपूर्णांक, ctsn))
		asoc->adv_peer_ack_poपूर्णांक = ctsn;

	list_क्रम_each_safe(lchunk, temp, &q->abanकरोned) अणु
		chunk = list_entry(lchunk, काष्ठा sctp_chunk, transmitted_list);
		tsn = ntohl(chunk->subh.data_hdr->tsn);

		अगर (TSN_lte(tsn, ctsn)) अणु
			list_del_init(lchunk);
			sctp_chunk_मुक्त(chunk);
		पूर्ण अन्यथा अगर (TSN_lte(tsn, asoc->adv_peer_ack_poपूर्णांक + 1)) अणु
			__be16 sid = chunk->subh.idata_hdr->stream;
			__be32 mid = chunk->subh.idata_hdr->mid;
			__u8 flags = 0;

			अगर (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
				flags |= SCTP_FTSN_U_BIT;

			asoc->adv_peer_ack_poपूर्णांक = tsn;
			skip_pos = sctp_get_skip_pos(&ftsn_skip_arr[0], nskips,
						     sid, flags);
			ftsn_skip_arr[skip_pos].stream = sid;
			ftsn_skip_arr[skip_pos].reserved = 0;
			ftsn_skip_arr[skip_pos].flags = flags;
			ftsn_skip_arr[skip_pos].mid = mid;
			अगर (skip_pos == nskips)
				nskips++;
			अगर (nskips == 10)
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (asoc->adv_peer_ack_poपूर्णांक > ctsn)
		ftsn_chunk = sctp_make_अगरwdtsn(asoc, asoc->adv_peer_ack_poपूर्णांक,
					       nskips, &ftsn_skip_arr[0]);

	अगर (ftsn_chunk) अणु
		list_add_tail(&ftsn_chunk->list, &q->control_chunk_list);
		SCTP_INC_STATS(asoc->base.net, SCTP_MIB_OUTCTRLCHUNKS);
	पूर्ण
पूर्ण

#घोषणा _sctp_walk_अगरwdtsn(pos, chunk, end) \
	क्रम (pos = chunk->subh.अगरwdtsn_hdr->skip; \
	     (व्योम *)pos < (व्योम *)chunk->subh.अगरwdtsn_hdr->skip + (end); pos++)

#घोषणा sctp_walk_अगरwdtsn(pos, ch) \
	_sctp_walk_अगरwdtsn((pos), (ch), ntohs((ch)->chunk_hdr->length) - \
					माप(काष्ठा sctp_अगरwdtsn_chunk))

अटल bool sctp_validate_fwdtsn(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_fwdtsn_skip *skip;
	__u16 incnt;

	अगर (chunk->chunk_hdr->type != SCTP_CID_FWD_TSN)
		वापस false;

	incnt = chunk->asoc->stream.incnt;
	sctp_walk_fwdtsn(skip, chunk)
		अगर (ntohs(skip->stream) >= incnt)
			वापस false;

	वापस true;
पूर्ण

अटल bool sctp_validate_अगरtsn(काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_अगरwdtsn_skip *skip;
	__u16 incnt;

	अगर (chunk->chunk_hdr->type != SCTP_CID_I_FWD_TSN)
		वापस false;

	incnt = chunk->asoc->stream.incnt;
	sctp_walk_अगरwdtsn(skip, chunk)
		अगर (ntohs(skip->stream) >= incnt)
			वापस false;

	वापस true;
पूर्ण

अटल व्योम sctp_report_fwdtsn(काष्ठा sctp_ulpq *ulpq, __u32 ftsn)
अणु
	/* Move the Cumulattive TSN Ack ahead. */
	sctp_tsnmap_skip(&ulpq->asoc->peer.tsn_map, ftsn);
	/* purge the fragmentation queue */
	sctp_ulpq_reयंत्र_flushtsn(ulpq, ftsn);
	/* Abort any in progress partial delivery. */
	sctp_ulpq_पात_pd(ulpq, GFP_ATOMIC);
पूर्ण

अटल व्योम sctp_पूर्णांकl_reयंत्र_flushtsn(काष्ठा sctp_ulpq *ulpq, __u32 ftsn)
अणु
	काष्ठा sk_buff *pos, *पंचांगp;

	skb_queue_walk_safe(&ulpq->reयंत्र, pos, पंचांगp) अणु
		काष्ठा sctp_ulpevent *event = sctp_skb2event(pos);
		__u32 tsn = event->tsn;

		अगर (TSN_lte(tsn, ftsn)) अणु
			__skb_unlink(pos, &ulpq->reयंत्र);
			sctp_ulpevent_मुक्त(event);
		पूर्ण
	पूर्ण

	skb_queue_walk_safe(&ulpq->reयंत्र_uo, pos, पंचांगp) अणु
		काष्ठा sctp_ulpevent *event = sctp_skb2event(pos);
		__u32 tsn = event->tsn;

		अगर (TSN_lte(tsn, ftsn)) अणु
			__skb_unlink(pos, &ulpq->reयंत्र_uo);
			sctp_ulpevent_मुक्त(event);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sctp_report_अगरtsn(काष्ठा sctp_ulpq *ulpq, __u32 ftsn)
अणु
	/* Move the Cumulattive TSN Ack ahead. */
	sctp_tsnmap_skip(&ulpq->asoc->peer.tsn_map, ftsn);
	/* purge the fragmentation queue */
	sctp_पूर्णांकl_reयंत्र_flushtsn(ulpq, ftsn);
	/* पात only when it's क्रम all data */
	अगर (ftsn == sctp_tsnmap_get_max_tsn_seen(&ulpq->asoc->peer.tsn_map))
		sctp_पूर्णांकl_पात_pd(ulpq, GFP_ATOMIC);
पूर्ण

अटल व्योम sctp_handle_fwdtsn(काष्ठा sctp_ulpq *ulpq, काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_fwdtsn_skip *skip;

	/* Walk through all the skipped SSNs */
	sctp_walk_fwdtsn(skip, chunk)
		sctp_ulpq_skip(ulpq, ntohs(skip->stream), ntohs(skip->ssn));
पूर्ण

अटल व्योम sctp_पूर्णांकl_skip(काष्ठा sctp_ulpq *ulpq, __u16 sid, __u32 mid,
			   __u8 flags)
अणु
	काष्ठा sctp_stream_in *sin = sctp_stream_in(&ulpq->asoc->stream, sid);
	काष्ठा sctp_stream *stream  = &ulpq->asoc->stream;

	अगर (flags & SCTP_FTSN_U_BIT) अणु
		अगर (sin->pd_mode_uo && MID_lt(sin->mid_uo, mid)) अणु
			sin->pd_mode_uo = 0;
			sctp_पूर्णांकl_stream_पात_pd(ulpq, sid, mid, 0x1,
						  GFP_ATOMIC);
		पूर्ण
		वापस;
	पूर्ण

	अगर (MID_lt(mid, sctp_mid_peek(stream, in, sid)))
		वापस;

	अगर (sin->pd_mode) अणु
		sin->pd_mode = 0;
		sctp_पूर्णांकl_stream_पात_pd(ulpq, sid, mid, 0x0, GFP_ATOMIC);
	पूर्ण

	sctp_mid_skip(stream, in, sid, mid);

	sctp_पूर्णांकl_reap_ordered(ulpq, sid);
पूर्ण

अटल व्योम sctp_handle_अगरtsn(काष्ठा sctp_ulpq *ulpq, काष्ठा sctp_chunk *chunk)
अणु
	काष्ठा sctp_अगरwdtsn_skip *skip;

	/* Walk through all the skipped MIDs and पात stream pd अगर possible */
	sctp_walk_अगरwdtsn(skip, chunk)
		sctp_पूर्णांकl_skip(ulpq, ntohs(skip->stream),
			       ntohl(skip->mid), skip->flags);
पूर्ण

अटल पूर्णांक करो_ulpq_tail_event(काष्ठा sctp_ulpq *ulpq, काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff_head temp;

	skb_queue_head_init(&temp);
	__skb_queue_tail(&temp, sctp_event2skb(event));
	वापस sctp_ulpq_tail_event(ulpq, &temp);
पूर्ण

अटल काष्ठा sctp_stream_पूर्णांकerleave sctp_stream_पूर्णांकerleave_0 = अणु
	.data_chunk_len		= माप(काष्ठा sctp_data_chunk),
	.ftsn_chunk_len		= माप(काष्ठा sctp_fwdtsn_chunk),
	/* DATA process functions */
	.make_datafrag		= sctp_make_datafrag_empty,
	.assign_number		= sctp_chunk_assign_ssn,
	.validate_data		= sctp_validate_data,
	.ulpevent_data		= sctp_ulpq_tail_data,
	.enqueue_event		= करो_ulpq_tail_event,
	.renege_events		= sctp_ulpq_renege,
	.start_pd		= sctp_ulpq_partial_delivery,
	.पात_pd		= sctp_ulpq_पात_pd,
	/* FORWARD-TSN process functions */
	.generate_ftsn		= sctp_generate_fwdtsn,
	.validate_ftsn		= sctp_validate_fwdtsn,
	.report_ftsn		= sctp_report_fwdtsn,
	.handle_ftsn		= sctp_handle_fwdtsn,
पूर्ण;

अटल पूर्णांक करो_sctp_enqueue_event(काष्ठा sctp_ulpq *ulpq,
				 काष्ठा sctp_ulpevent *event)
अणु
	काष्ठा sk_buff_head temp;

	skb_queue_head_init(&temp);
	__skb_queue_tail(&temp, sctp_event2skb(event));
	वापस sctp_enqueue_event(ulpq, &temp);
पूर्ण

अटल काष्ठा sctp_stream_पूर्णांकerleave sctp_stream_पूर्णांकerleave_1 = अणु
	.data_chunk_len		= माप(काष्ठा sctp_idata_chunk),
	.ftsn_chunk_len		= माप(काष्ठा sctp_अगरwdtsn_chunk),
	/* I-DATA process functions */
	.make_datafrag		= sctp_make_idatafrag_empty,
	.assign_number		= sctp_chunk_assign_mid,
	.validate_data		= sctp_validate_idata,
	.ulpevent_data		= sctp_ulpevent_idata,
	.enqueue_event		= करो_sctp_enqueue_event,
	.renege_events		= sctp_renege_events,
	.start_pd		= sctp_पूर्णांकl_start_pd,
	.पात_pd		= sctp_पूर्णांकl_पात_pd,
	/* I-FORWARD-TSN process functions */
	.generate_ftsn		= sctp_generate_अगरtsn,
	.validate_ftsn		= sctp_validate_अगरtsn,
	.report_ftsn		= sctp_report_अगरtsn,
	.handle_ftsn		= sctp_handle_अगरtsn,
पूर्ण;

व्योम sctp_stream_पूर्णांकerleave_init(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_association *asoc;

	asoc = container_of(stream, काष्ठा sctp_association, stream);
	stream->si = asoc->peer.पूर्णांकl_capable ? &sctp_stream_पूर्णांकerleave_1
					     : &sctp_stream_पूर्णांकerleave_0;
पूर्ण
