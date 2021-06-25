<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * These are the definitions needed क्रम the sctp_ulpq type.  The
 * sctp_ulpq is the पूर्णांकerface between the Upper Layer Protocol, or ULP,
 * and the core SCTP state machine.  This is the component which handles
 * reassembly and ordering.
 *
 * Please send any bug reports or fixes you make to the
 * email addresses:
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   Jon Grimm             <jgrimm@us.ibm.com>
 *   La Monte H.P. Yarroll <piggy@acm.org>
 *   Sridhar Samudrala     <sri@us.ibm.com>
 */

#अगर_अघोषित __sctp_ulpqueue_h__
#घोषणा __sctp_ulpqueue_h__

/* A काष्ठाure to carry inक्रमmation to the ULP (e.g. Sockets API) */
काष्ठा sctp_ulpq अणु
	अक्षर pd_mode;
	काष्ठा sctp_association *asoc;
	काष्ठा sk_buff_head reयंत्र;
	काष्ठा sk_buff_head reयंत्र_uo;
	काष्ठा sk_buff_head lobby;
पूर्ण;

/* Prototypes. */
काष्ठा sctp_ulpq *sctp_ulpq_init(काष्ठा sctp_ulpq *,
				 काष्ठा sctp_association *);
व्योम sctp_ulpq_flush(काष्ठा sctp_ulpq *ulpq);
व्योम sctp_ulpq_मुक्त(काष्ठा sctp_ulpq *);

/* Add a new DATA chunk क्रम processing. */
पूर्णांक sctp_ulpq_tail_data(काष्ठा sctp_ulpq *, काष्ठा sctp_chunk *, gfp_t);

/* Add a new event क्रम propagation to the ULP. */
पूर्णांक sctp_ulpq_tail_event(काष्ठा sctp_ulpq *, काष्ठा sk_buff_head *skb_list);

/* Renege previously received chunks.  */
व्योम sctp_ulpq_renege(काष्ठा sctp_ulpq *, काष्ठा sctp_chunk *, gfp_t);

/* Perक्रमm partial delivery. */
व्योम sctp_ulpq_partial_delivery(काष्ठा sctp_ulpq *, gfp_t);

/* Abort the partial delivery. */
व्योम sctp_ulpq_पात_pd(काष्ठा sctp_ulpq *, gfp_t);

/* Clear the partial data delivery condition on this socket. */
पूर्णांक sctp_clear_pd(काष्ठा sock *sk, काष्ठा sctp_association *asoc);

/* Skip over an SSN. */
व्योम sctp_ulpq_skip(काष्ठा sctp_ulpq *ulpq, __u16 sid, __u16 ssn);

व्योम sctp_ulpq_reयंत्र_flushtsn(काष्ठा sctp_ulpq *, __u32);

__u16 sctp_ulpq_renege_list(काष्ठा sctp_ulpq *ulpq,
			    काष्ठा sk_buff_head *list, __u16 needed);

#पूर्ण_अगर /* __sctp_ulpqueue_h__ */
