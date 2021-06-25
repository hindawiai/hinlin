<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright Red Hat Inc. 2017
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions manipulate sctp stream queue/scheduling.
 *
 * Please send any bug reports or fixes you make to the
 * email addresched(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    Marcelo Ricarकरो Leitner <marcelo.leitner@gmail.com>
 */

#समावेश <linux/list.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>
#समावेश <net/sctp/stream_sched.h>

/* Priority handling
 * RFC DRAFT ndata section 3.2
 */
अटल व्योम sctp_sched_rr_unsched_all(काष्ठा sctp_stream *stream);

अटल व्योम sctp_sched_rr_next_stream(काष्ठा sctp_stream *stream)
अणु
	काष्ठा list_head *pos;

	pos = stream->rr_next->rr_list.next;
	अगर (pos == &stream->rr_list)
		pos = pos->next;
	stream->rr_next = list_entry(pos, काष्ठा sctp_stream_out_ext, rr_list);
पूर्ण

अटल व्योम sctp_sched_rr_unsched(काष्ठा sctp_stream *stream,
				  काष्ठा sctp_stream_out_ext *soute)
अणु
	अगर (stream->rr_next == soute)
		/* Try to move to the next stream */
		sctp_sched_rr_next_stream(stream);

	list_del_init(&soute->rr_list);

	/* If we have no other stream queued, clear next */
	अगर (list_empty(&stream->rr_list))
		stream->rr_next = शून्य;
पूर्ण

अटल व्योम sctp_sched_rr_sched(काष्ठा sctp_stream *stream,
				काष्ठा sctp_stream_out_ext *soute)
अणु
	अगर (!list_empty(&soute->rr_list))
		/* Alपढ़ोy scheduled. */
		वापस;

	/* Schedule the stream */
	list_add_tail(&soute->rr_list, &stream->rr_list);

	अगर (!stream->rr_next)
		stream->rr_next = soute;
पूर्ण

अटल पूर्णांक sctp_sched_rr_set(काष्ठा sctp_stream *stream, __u16 sid,
			     __u16 prio, gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_rr_get(काष्ठा sctp_stream *stream, __u16 sid,
			     __u16 *value)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_rr_init(काष्ठा sctp_stream *stream)
अणु
	INIT_LIST_HEAD(&stream->rr_list);
	stream->rr_next = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_rr_init_sid(काष्ठा sctp_stream *stream, __u16 sid,
				  gfp_t gfp)
अणु
	INIT_LIST_HEAD(&SCTP_SO(stream, sid)->ext->rr_list);

	वापस 0;
पूर्ण

अटल व्योम sctp_sched_rr_मुक्त(काष्ठा sctp_stream *stream)
अणु
	sctp_sched_rr_unsched_all(stream);
पूर्ण

अटल व्योम sctp_sched_rr_enqueue(काष्ठा sctp_outq *q,
				  काष्ठा sctp_datamsg *msg)
अणु
	काष्ठा sctp_stream *stream;
	काष्ठा sctp_chunk *ch;
	__u16 sid;

	ch = list_first_entry(&msg->chunks, काष्ठा sctp_chunk, frag_list);
	sid = sctp_chunk_stream_no(ch);
	stream = &q->asoc->stream;
	sctp_sched_rr_sched(stream, SCTP_SO(stream, sid)->ext);
पूर्ण

अटल काष्ठा sctp_chunk *sctp_sched_rr_dequeue(काष्ठा sctp_outq *q)
अणु
	काष्ठा sctp_stream *stream = &q->asoc->stream;
	काष्ठा sctp_stream_out_ext *soute;
	काष्ठा sctp_chunk *ch = शून्य;

	/* Bail out quickly अगर queue is empty */
	अगर (list_empty(&q->out_chunk_list))
		जाओ out;

	/* Find which chunk is next */
	अगर (stream->out_curr)
		soute = stream->out_curr->ext;
	अन्यथा
		soute = stream->rr_next;
	ch = list_entry(soute->outq.next, काष्ठा sctp_chunk, stream_list);

	sctp_sched_dequeue_common(q, ch);

out:
	वापस ch;
पूर्ण

अटल व्योम sctp_sched_rr_dequeue_करोne(काष्ठा sctp_outq *q,
				       काष्ठा sctp_chunk *ch)
अणु
	काष्ठा sctp_stream_out_ext *soute;
	__u16 sid;

	/* Last chunk on that msg, move to the next stream */
	sid = sctp_chunk_stream_no(ch);
	soute = SCTP_SO(&q->asoc->stream, sid)->ext;

	sctp_sched_rr_next_stream(&q->asoc->stream);

	अगर (list_empty(&soute->outq))
		sctp_sched_rr_unsched(&q->asoc->stream, soute);
पूर्ण

अटल व्योम sctp_sched_rr_sched_all(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_stream_out_ext *soute;
	काष्ठा sctp_chunk *ch;

	asoc = container_of(stream, काष्ठा sctp_association, stream);
	list_क्रम_each_entry(ch, &asoc->outqueue.out_chunk_list, list) अणु
		__u16 sid;

		sid = sctp_chunk_stream_no(ch);
		soute = SCTP_SO(stream, sid)->ext;
		अगर (soute)
			sctp_sched_rr_sched(stream, soute);
	पूर्ण
पूर्ण

अटल व्योम sctp_sched_rr_unsched_all(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_stream_out_ext *soute, *पंचांगp;

	list_क्रम_each_entry_safe(soute, पंचांगp, &stream->rr_list, rr_list)
		sctp_sched_rr_unsched(stream, soute);
पूर्ण

अटल काष्ठा sctp_sched_ops sctp_sched_rr = अणु
	.set = sctp_sched_rr_set,
	.get = sctp_sched_rr_get,
	.init = sctp_sched_rr_init,
	.init_sid = sctp_sched_rr_init_sid,
	.मुक्त = sctp_sched_rr_मुक्त,
	.enqueue = sctp_sched_rr_enqueue,
	.dequeue = sctp_sched_rr_dequeue,
	.dequeue_करोne = sctp_sched_rr_dequeue_करोne,
	.sched_all = sctp_sched_rr_sched_all,
	.unsched_all = sctp_sched_rr_unsched_all,
पूर्ण;

व्योम sctp_sched_ops_rr_init(व्योम)
अणु
	sctp_sched_ops_रेजिस्टर(SCTP_SS_RR, &sctp_sched_rr);
पूर्ण
