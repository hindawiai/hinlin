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

/* First Come First Serve (a.k.a. FIFO)
 * RFC DRAFT ndata Section 3.1
 */
अटल पूर्णांक sctp_sched_fcfs_set(काष्ठा sctp_stream *stream, __u16 sid,
			       __u16 value, gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_fcfs_get(काष्ठा sctp_stream *stream, __u16 sid,
			       __u16 *value)
अणु
	*value = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_fcfs_init(काष्ठा sctp_stream *stream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_fcfs_init_sid(काष्ठा sctp_stream *stream, __u16 sid,
				    gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल व्योम sctp_sched_fcfs_मुक्त(काष्ठा sctp_stream *stream)
अणु
पूर्ण

अटल व्योम sctp_sched_fcfs_enqueue(काष्ठा sctp_outq *q,
				    काष्ठा sctp_datamsg *msg)
अणु
पूर्ण

अटल काष्ठा sctp_chunk *sctp_sched_fcfs_dequeue(काष्ठा sctp_outq *q)
अणु
	काष्ठा sctp_stream *stream = &q->asoc->stream;
	काष्ठा sctp_chunk *ch = शून्य;
	काष्ठा list_head *entry;

	अगर (list_empty(&q->out_chunk_list))
		जाओ out;

	अगर (stream->out_curr) अणु
		ch = list_entry(stream->out_curr->ext->outq.next,
				काष्ठा sctp_chunk, stream_list);
	पूर्ण अन्यथा अणु
		entry = q->out_chunk_list.next;
		ch = list_entry(entry, काष्ठा sctp_chunk, list);
	पूर्ण

	sctp_sched_dequeue_common(q, ch);

out:
	वापस ch;
पूर्ण

अटल व्योम sctp_sched_fcfs_dequeue_करोne(काष्ठा sctp_outq *q,
					 काष्ठा sctp_chunk *chunk)
अणु
पूर्ण

अटल व्योम sctp_sched_fcfs_sched_all(काष्ठा sctp_stream *stream)
अणु
पूर्ण

अटल व्योम sctp_sched_fcfs_unsched_all(काष्ठा sctp_stream *stream)
अणु
पूर्ण

अटल काष्ठा sctp_sched_ops sctp_sched_fcfs = अणु
	.set = sctp_sched_fcfs_set,
	.get = sctp_sched_fcfs_get,
	.init = sctp_sched_fcfs_init,
	.init_sid = sctp_sched_fcfs_init_sid,
	.मुक्त = sctp_sched_fcfs_मुक्त,
	.enqueue = sctp_sched_fcfs_enqueue,
	.dequeue = sctp_sched_fcfs_dequeue,
	.dequeue_करोne = sctp_sched_fcfs_dequeue_करोne,
	.sched_all = sctp_sched_fcfs_sched_all,
	.unsched_all = sctp_sched_fcfs_unsched_all,
पूर्ण;

अटल व्योम sctp_sched_ops_fcfs_init(व्योम)
अणु
	sctp_sched_ops_रेजिस्टर(SCTP_SS_FCFS, &sctp_sched_fcfs);
पूर्ण

/* API to other parts of the stack */

अटल काष्ठा sctp_sched_ops *sctp_sched_ops[SCTP_SS_MAX + 1];

व्योम sctp_sched_ops_रेजिस्टर(क्रमागत sctp_sched_type sched,
			     काष्ठा sctp_sched_ops *sched_ops)
अणु
	sctp_sched_ops[sched] = sched_ops;
पूर्ण

व्योम sctp_sched_ops_init(व्योम)
अणु
	sctp_sched_ops_fcfs_init();
	sctp_sched_ops_prio_init();
	sctp_sched_ops_rr_init();
पूर्ण

पूर्णांक sctp_sched_set_sched(काष्ठा sctp_association *asoc,
			 क्रमागत sctp_sched_type sched)
अणु
	काष्ठा sctp_sched_ops *n = sctp_sched_ops[sched];
	काष्ठा sctp_sched_ops *old = asoc->outqueue.sched;
	काष्ठा sctp_datamsg *msg = शून्य;
	काष्ठा sctp_chunk *ch;
	पूर्णांक i, ret = 0;

	अगर (old == n)
		वापस ret;

	अगर (sched > SCTP_SS_MAX)
		वापस -EINVAL;

	अगर (old) अणु
		old->मुक्त(&asoc->stream);

		/* Give the next scheduler a clean slate. */
		क्रम (i = 0; i < asoc->stream.outcnt; i++) अणु
			व्योम *p = SCTP_SO(&asoc->stream, i)->ext;

			अगर (!p)
				जारी;

			p += दुरत्वend(काष्ठा sctp_stream_out_ext, outq);
			स_रखो(p, 0, माप(काष्ठा sctp_stream_out_ext) -
				     दुरत्वend(काष्ठा sctp_stream_out_ext, outq));
		पूर्ण
	पूर्ण

	asoc->outqueue.sched = n;
	n->init(&asoc->stream);
	क्रम (i = 0; i < asoc->stream.outcnt; i++) अणु
		अगर (!SCTP_SO(&asoc->stream, i)->ext)
			जारी;

		ret = n->init_sid(&asoc->stream, i, GFP_KERNEL);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* We have to requeue all chunks alपढ़ोy queued. */
	list_क्रम_each_entry(ch, &asoc->outqueue.out_chunk_list, list) अणु
		अगर (ch->msg == msg)
			जारी;
		msg = ch->msg;
		n->enqueue(&asoc->outqueue, msg);
	पूर्ण

	वापस ret;

err:
	n->मुक्त(&asoc->stream);
	asoc->outqueue.sched = &sctp_sched_fcfs; /* Always safe */

	वापस ret;
पूर्ण

पूर्णांक sctp_sched_get_sched(काष्ठा sctp_association *asoc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= SCTP_SS_MAX; i++)
		अगर (asoc->outqueue.sched == sctp_sched_ops[i])
			वापस i;

	वापस 0;
पूर्ण

पूर्णांक sctp_sched_set_value(काष्ठा sctp_association *asoc, __u16 sid,
			 __u16 value, gfp_t gfp)
अणु
	अगर (sid >= asoc->stream.outcnt)
		वापस -EINVAL;

	अगर (!SCTP_SO(&asoc->stream, sid)->ext) अणु
		पूर्णांक ret;

		ret = sctp_stream_init_ext(&asoc->stream, sid);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस asoc->outqueue.sched->set(&asoc->stream, sid, value, gfp);
पूर्ण

पूर्णांक sctp_sched_get_value(काष्ठा sctp_association *asoc, __u16 sid,
			 __u16 *value)
अणु
	अगर (sid >= asoc->stream.outcnt)
		वापस -EINVAL;

	अगर (!SCTP_SO(&asoc->stream, sid)->ext)
		वापस 0;

	वापस asoc->outqueue.sched->get(&asoc->stream, sid, value);
पूर्ण

व्योम sctp_sched_dequeue_करोne(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *ch)
अणु
	अगर (!list_is_last(&ch->frag_list, &ch->msg->chunks) &&
	    !q->asoc->peer.पूर्णांकl_capable) अणु
		काष्ठा sctp_stream_out *sout;
		__u16 sid;

		/* datamsg is not finish, so save it as current one,
		 * in हाल application चयन scheduler or a higher
		 * priority stream comes in.
		 */
		sid = sctp_chunk_stream_no(ch);
		sout = SCTP_SO(&q->asoc->stream, sid);
		q->asoc->stream.out_curr = sout;
		वापस;
	पूर्ण

	q->asoc->stream.out_curr = शून्य;
	q->sched->dequeue_करोne(q, ch);
पूर्ण

/* Auxiliary functions क्रम the schedulers */
व्योम sctp_sched_dequeue_common(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *ch)
अणु
	list_del_init(&ch->list);
	list_del_init(&ch->stream_list);
	q->out_qlen -= ch->skb->len;
पूर्ण

पूर्णांक sctp_sched_init_sid(काष्ठा sctp_stream *stream, __u16 sid, gfp_t gfp)
अणु
	काष्ठा sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);
	काष्ठा sctp_stream_out_ext *ext = SCTP_SO(stream, sid)->ext;

	INIT_LIST_HEAD(&ext->outq);
	वापस sched->init_sid(stream, sid, gfp);
पूर्ण

काष्ठा sctp_sched_ops *sctp_sched_ops_from_stream(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_association *asoc;

	asoc = container_of(stream, काष्ठा sctp_association, stream);

	वापस asoc->outqueue.sched;
पूर्ण
