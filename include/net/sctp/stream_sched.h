<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright Red Hat Inc. 2017
 *
 * These are definitions used by the stream schedulers, defined in RFC
 * draft ndata (https://tools.ietf.org/hपंचांगl/draft-ietf-tsvwg-sctp-ndata-11)
 *
 * Please send any bug reports or fixes you make to the
 * email addresses:
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   Marcelo Ricarकरो Leitner <marcelo.leitner@gmail.com>
 */

#अगर_अघोषित __sctp_stream_sched_h__
#घोषणा __sctp_stream_sched_h__

काष्ठा sctp_sched_ops अणु
	/* Property handling क्रम a given stream */
	पूर्णांक (*set)(काष्ठा sctp_stream *stream, __u16 sid, __u16 value,
		   gfp_t gfp);
	पूर्णांक (*get)(काष्ठा sctp_stream *stream, __u16 sid, __u16 *value);

	/* Init the specअगरic scheduler */
	पूर्णांक (*init)(काष्ठा sctp_stream *stream);
	/* Init a stream */
	पूर्णांक (*init_sid)(काष्ठा sctp_stream *stream, __u16 sid, gfp_t gfp);
	/* Frees the entire thing */
	व्योम (*मुक्त)(काष्ठा sctp_stream *stream);

	/* Enqueue a chunk */
	व्योम (*enqueue)(काष्ठा sctp_outq *q, काष्ठा sctp_datamsg *msg);
	/* Dequeue a chunk */
	काष्ठा sctp_chunk *(*dequeue)(काष्ठा sctp_outq *q);
	/* Called only अगर the chunk fit the packet */
	व्योम (*dequeue_करोne)(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *chunk);
	/* Sched all chunks alपढ़ोy enqueued */
	व्योम (*sched_all)(काष्ठा sctp_stream *steam);
	/* Unched all chunks alपढ़ोy enqueued */
	व्योम (*unsched_all)(काष्ठा sctp_stream *steam);
पूर्ण;

पूर्णांक sctp_sched_set_sched(काष्ठा sctp_association *asoc,
			 क्रमागत sctp_sched_type sched);
पूर्णांक sctp_sched_get_sched(काष्ठा sctp_association *asoc);
पूर्णांक sctp_sched_set_value(काष्ठा sctp_association *asoc, __u16 sid,
			 __u16 value, gfp_t gfp);
पूर्णांक sctp_sched_get_value(काष्ठा sctp_association *asoc, __u16 sid,
			 __u16 *value);
व्योम sctp_sched_dequeue_करोne(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *ch);

व्योम sctp_sched_dequeue_common(काष्ठा sctp_outq *q, काष्ठा sctp_chunk *ch);
पूर्णांक sctp_sched_init_sid(काष्ठा sctp_stream *stream, __u16 sid, gfp_t gfp);
काष्ठा sctp_sched_ops *sctp_sched_ops_from_stream(काष्ठा sctp_stream *stream);

व्योम sctp_sched_ops_रेजिस्टर(क्रमागत sctp_sched_type sched,
			     काष्ठा sctp_sched_ops *sched_ops);
व्योम sctp_sched_ops_prio_init(व्योम);
व्योम sctp_sched_ops_rr_init(व्योम);

#पूर्ण_अगर /* __sctp_stream_sched_h__ */
