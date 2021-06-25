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
 * RFC DRAFT ndata section 3.4
 */

अटल व्योम sctp_sched_prio_unsched_all(काष्ठा sctp_stream *stream);

अटल काष्ठा sctp_stream_priorities *sctp_sched_prio_new_head(
			काष्ठा sctp_stream *stream, पूर्णांक prio, gfp_t gfp)
अणु
	काष्ठा sctp_stream_priorities *p;

	p = kदो_स्मृति(माप(*p), gfp);
	अगर (!p)
		वापस शून्य;

	INIT_LIST_HEAD(&p->prio_sched);
	INIT_LIST_HEAD(&p->active);
	p->next = शून्य;
	p->prio = prio;

	वापस p;
पूर्ण

अटल काष्ठा sctp_stream_priorities *sctp_sched_prio_get_head(
			काष्ठा sctp_stream *stream, पूर्णांक prio, gfp_t gfp)
अणु
	काष्ठा sctp_stream_priorities *p;
	पूर्णांक i;

	/* Look पूर्णांकo scheduled priorities first, as they are sorted and
	 * we can find it fast IF it's scheduled.
	 */
	list_क्रम_each_entry(p, &stream->prio_list, prio_sched) अणु
		अगर (p->prio == prio)
			वापस p;
		अगर (p->prio > prio)
			अवरोध;
	पूर्ण

	/* No luck. So we search on all streams now. */
	क्रम (i = 0; i < stream->outcnt; i++) अणु
		अगर (!SCTP_SO(stream, i)->ext)
			जारी;

		p = SCTP_SO(stream, i)->ext->prio_head;
		अगर (!p)
			/* Means all other streams won't be initialized
			 * as well.
			 */
			अवरोध;
		अगर (p->prio == prio)
			वापस p;
	पूर्ण

	/* If not even there, allocate a new one. */
	वापस sctp_sched_prio_new_head(stream, prio, gfp);
पूर्ण

अटल व्योम sctp_sched_prio_next_stream(काष्ठा sctp_stream_priorities *p)
अणु
	काष्ठा list_head *pos;

	pos = p->next->prio_list.next;
	अगर (pos == &p->active)
		pos = pos->next;
	p->next = list_entry(pos, काष्ठा sctp_stream_out_ext, prio_list);
पूर्ण

अटल bool sctp_sched_prio_unsched(काष्ठा sctp_stream_out_ext *soute)
अणु
	bool scheduled = false;

	अगर (!list_empty(&soute->prio_list)) अणु
		काष्ठा sctp_stream_priorities *prio_head = soute->prio_head;

		/* Scheduled */
		scheduled = true;

		अगर (prio_head->next == soute)
			/* Try to move to the next stream */
			sctp_sched_prio_next_stream(prio_head);

		list_del_init(&soute->prio_list);

		/* Also unsched the priority अगर this was the last stream */
		अगर (list_empty(&prio_head->active)) अणु
			list_del_init(&prio_head->prio_sched);
			/* If there is no stream left, clear next */
			prio_head->next = शून्य;
		पूर्ण
	पूर्ण

	वापस scheduled;
पूर्ण

अटल व्योम sctp_sched_prio_sched(काष्ठा sctp_stream *stream,
				  काष्ठा sctp_stream_out_ext *soute)
अणु
	काष्ठा sctp_stream_priorities *prio, *prio_head;

	prio_head = soute->prio_head;

	/* Nothing to करो अगर alपढ़ोy scheduled */
	अगर (!list_empty(&soute->prio_list))
		वापस;

	/* Schedule the stream. If there is a next, we schedule the new
	 * one beक्रमe it, so it's the last in round robin order.
	 * If there isn't, we also have to schedule the priority.
	 */
	अगर (prio_head->next) अणु
		list_add(&soute->prio_list, prio_head->next->prio_list.prev);
		वापस;
	पूर्ण

	list_add(&soute->prio_list, &prio_head->active);
	prio_head->next = soute;

	list_क्रम_each_entry(prio, &stream->prio_list, prio_sched) अणु
		अगर (prio->prio > prio_head->prio) अणु
			list_add(&prio_head->prio_sched, prio->prio_sched.prev);
			वापस;
		पूर्ण
	पूर्ण

	list_add_tail(&prio_head->prio_sched, &stream->prio_list);
पूर्ण

अटल पूर्णांक sctp_sched_prio_set(काष्ठा sctp_stream *stream, __u16 sid,
			       __u16 prio, gfp_t gfp)
अणु
	काष्ठा sctp_stream_out *sout = SCTP_SO(stream, sid);
	काष्ठा sctp_stream_out_ext *soute = sout->ext;
	काष्ठा sctp_stream_priorities *prio_head, *old;
	bool reschedule = false;
	पूर्णांक i;

	prio_head = sctp_sched_prio_get_head(stream, prio, gfp);
	अगर (!prio_head)
		वापस -ENOMEM;

	reschedule = sctp_sched_prio_unsched(soute);
	old = soute->prio_head;
	soute->prio_head = prio_head;
	अगर (reschedule)
		sctp_sched_prio_sched(stream, soute);

	अगर (!old)
		/* Happens when we set the priority क्रम the first समय */
		वापस 0;

	क्रम (i = 0; i < stream->outcnt; i++) अणु
		soute = SCTP_SO(stream, i)->ext;
		अगर (soute && soute->prio_head == old)
			/* It's still in use, nothing अन्यथा to करो here. */
			वापस 0;
	पूर्ण

	/* No hits, we are good to मुक्त it. */
	kमुक्त(old);

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_prio_get(काष्ठा sctp_stream *stream, __u16 sid,
			       __u16 *value)
अणु
	*value = SCTP_SO(stream, sid)->ext->prio_head->prio;
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_prio_init(काष्ठा sctp_stream *stream)
अणु
	INIT_LIST_HEAD(&stream->prio_list);

	वापस 0;
पूर्ण

अटल पूर्णांक sctp_sched_prio_init_sid(काष्ठा sctp_stream *stream, __u16 sid,
				    gfp_t gfp)
अणु
	INIT_LIST_HEAD(&SCTP_SO(stream, sid)->ext->prio_list);
	वापस sctp_sched_prio_set(stream, sid, 0, gfp);
पूर्ण

अटल व्योम sctp_sched_prio_मुक्त(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_stream_priorities *prio, *n;
	LIST_HEAD(list);
	पूर्णांक i;

	/* As we करोn't keep a list of priorities, to aव्योम multiple
	 * मुक्तs we have to करो it in 3 steps:
	 *   1. unsched everyone, so the lists are मुक्त to use in 2.
	 *   2. build the list of the priorities
	 *   3. मुक्त the list
	 */
	sctp_sched_prio_unsched_all(stream);
	क्रम (i = 0; i < stream->outcnt; i++) अणु
		अगर (!SCTP_SO(stream, i)->ext)
			जारी;
		prio = SCTP_SO(stream, i)->ext->prio_head;
		अगर (prio && list_empty(&prio->prio_sched))
			list_add(&prio->prio_sched, &list);
	पूर्ण
	list_क्रम_each_entry_safe(prio, n, &list, prio_sched) अणु
		list_del_init(&prio->prio_sched);
		kमुक्त(prio);
	पूर्ण
पूर्ण

अटल व्योम sctp_sched_prio_enqueue(काष्ठा sctp_outq *q,
				    काष्ठा sctp_datamsg *msg)
अणु
	काष्ठा sctp_stream *stream;
	काष्ठा sctp_chunk *ch;
	__u16 sid;

	ch = list_first_entry(&msg->chunks, काष्ठा sctp_chunk, frag_list);
	sid = sctp_chunk_stream_no(ch);
	stream = &q->asoc->stream;
	sctp_sched_prio_sched(stream, SCTP_SO(stream, sid)->ext);
पूर्ण

अटल काष्ठा sctp_chunk *sctp_sched_prio_dequeue(काष्ठा sctp_outq *q)
अणु
	काष्ठा sctp_stream *stream = &q->asoc->stream;
	काष्ठा sctp_stream_priorities *prio;
	काष्ठा sctp_stream_out_ext *soute;
	काष्ठा sctp_chunk *ch = शून्य;

	/* Bail out quickly अगर queue is empty */
	अगर (list_empty(&q->out_chunk_list))
		जाओ out;

	/* Find which chunk is next. It's easy, it's either the current
	 * one or the first chunk on the next active stream.
	 */
	अगर (stream->out_curr) अणु
		soute = stream->out_curr->ext;
	पूर्ण अन्यथा अणु
		prio = list_entry(stream->prio_list.next,
				  काष्ठा sctp_stream_priorities, prio_sched);
		soute = prio->next;
	पूर्ण
	ch = list_entry(soute->outq.next, काष्ठा sctp_chunk, stream_list);
	sctp_sched_dequeue_common(q, ch);

out:
	वापस ch;
पूर्ण

अटल व्योम sctp_sched_prio_dequeue_करोne(काष्ठा sctp_outq *q,
					 काष्ठा sctp_chunk *ch)
अणु
	काष्ठा sctp_stream_priorities *prio;
	काष्ठा sctp_stream_out_ext *soute;
	__u16 sid;

	/* Last chunk on that msg, move to the next stream on
	 * this priority.
	 */
	sid = sctp_chunk_stream_no(ch);
	soute = SCTP_SO(&q->asoc->stream, sid)->ext;
	prio = soute->prio_head;

	sctp_sched_prio_next_stream(prio);

	अगर (list_empty(&soute->outq))
		sctp_sched_prio_unsched(soute);
पूर्ण

अटल व्योम sctp_sched_prio_sched_all(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_stream_out *sout;
	काष्ठा sctp_chunk *ch;

	asoc = container_of(stream, काष्ठा sctp_association, stream);
	list_क्रम_each_entry(ch, &asoc->outqueue.out_chunk_list, list) अणु
		__u16 sid;

		sid = sctp_chunk_stream_no(ch);
		sout = SCTP_SO(stream, sid);
		अगर (sout->ext)
			sctp_sched_prio_sched(stream, sout->ext);
	पूर्ण
पूर्ण

अटल व्योम sctp_sched_prio_unsched_all(काष्ठा sctp_stream *stream)
अणु
	काष्ठा sctp_stream_priorities *p, *पंचांगp;
	काष्ठा sctp_stream_out_ext *soute, *soutपंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, &stream->prio_list, prio_sched)
		list_क्रम_each_entry_safe(soute, soutपंचांगp, &p->active, prio_list)
			sctp_sched_prio_unsched(soute);
पूर्ण

अटल काष्ठा sctp_sched_ops sctp_sched_prio = अणु
	.set = sctp_sched_prio_set,
	.get = sctp_sched_prio_get,
	.init = sctp_sched_prio_init,
	.init_sid = sctp_sched_prio_init_sid,
	.मुक्त = sctp_sched_prio_मुक्त,
	.enqueue = sctp_sched_prio_enqueue,
	.dequeue = sctp_sched_prio_dequeue,
	.dequeue_करोne = sctp_sched_prio_dequeue_करोne,
	.sched_all = sctp_sched_prio_sched_all,
	.unsched_all = sctp_sched_prio_unsched_all,
पूर्ण;

व्योम sctp_sched_ops_prio_init(व्योम)
अणु
	sctp_sched_ops_रेजिस्टर(SCTP_SS_PRIO, &sctp_sched_prio);
पूर्ण
