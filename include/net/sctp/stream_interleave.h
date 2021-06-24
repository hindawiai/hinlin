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
 *   Xin Long <lucien.xin@gmail.com>
 */

#अगर_अघोषित __sctp_stream_पूर्णांकerleave_h__
#घोषणा __sctp_stream_पूर्णांकerleave_h__

काष्ठा sctp_stream_पूर्णांकerleave अणु
	__u16	data_chunk_len;
	__u16	ftsn_chunk_len;
	/* (I-)DATA process */
	काष्ठा sctp_chunk *(*make_datafrag)(स्थिर काष्ठा sctp_association *asoc,
					    स्थिर काष्ठा sctp_sndrcvinfo *sinfo,
					    पूर्णांक len, __u8 flags, gfp_t gfp);
	व्योम	(*assign_number)(काष्ठा sctp_chunk *chunk);
	bool	(*validate_data)(काष्ठा sctp_chunk *chunk);
	पूर्णांक	(*ulpevent_data)(काष्ठा sctp_ulpq *ulpq,
				 काष्ठा sctp_chunk *chunk, gfp_t gfp);
	पूर्णांक	(*enqueue_event)(काष्ठा sctp_ulpq *ulpq,
				 काष्ठा sctp_ulpevent *event);
	व्योम	(*renege_events)(काष्ठा sctp_ulpq *ulpq,
				 काष्ठा sctp_chunk *chunk, gfp_t gfp);
	व्योम	(*start_pd)(काष्ठा sctp_ulpq *ulpq, gfp_t gfp);
	व्योम	(*पात_pd)(काष्ठा sctp_ulpq *ulpq, gfp_t gfp);
	/* (I-)FORWARD-TSN process */
	व्योम	(*generate_ftsn)(काष्ठा sctp_outq *q, __u32 ctsn);
	bool	(*validate_ftsn)(काष्ठा sctp_chunk *chunk);
	व्योम	(*report_ftsn)(काष्ठा sctp_ulpq *ulpq, __u32 ftsn);
	व्योम	(*handle_ftsn)(काष्ठा sctp_ulpq *ulpq,
			       काष्ठा sctp_chunk *chunk);
पूर्ण;

व्योम sctp_stream_पूर्णांकerleave_init(काष्ठा sctp_stream *stream);

#पूर्ण_अगर /* __sctp_stream_पूर्णांकerleave_h__ */
