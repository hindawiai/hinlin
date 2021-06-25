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
 * These are the definitions needed क्रम the sctp_ulpevent type.  The
 * sctp_ulpevent type is used to carry inक्रमmation from the state machine
 * upwards to the ULP.
 *
 * This file is part of the SCTP kernel implementation
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   Jon Grimm             <jgrimm@us.ibm.com>
 *   La Monte H.P. Yarroll <piggy@acm.org>
 *   Karl Knutson          <karl@athena.chicago.il.us>
 *   Sridhar Samudrala     <sri@us.ibm.com>
 */

#अगर_अघोषित __sctp_ulpevent_h__
#घोषणा __sctp_ulpevent_h__

/* A काष्ठाure to carry inक्रमmation to the ULP (e.g. Sockets API) */
/* Warning: This sits inside an skb.cb[] area.  Be very careful of
 * growing this काष्ठाure as it is at the maximum limit now.
 *
 * sctp_ulpevent is saved in sk->cb(48 bytes), whose last 4 bytes
 * have been taken by sock_skb_cb, So here it has to use 'packed'
 * to make sctp_ulpevent fit पूर्णांकo the rest 44 bytes.
 */
काष्ठा sctp_ulpevent अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_chunk *chunk;
	अचिन्हित पूर्णांक rmem_len;
	जोड़ अणु
		__u32 mid;
		__u16 ssn;
	पूर्ण;
	जोड़ अणु
		__u32 ppid;
		__u32 fsn;
	पूर्ण;
	__u32 tsn;
	__u32 cumtsn;
	__u16 stream;
	__u16 flags;
	__u16 msg_flags;
पूर्ण __packed;

/* Retrieve the skb this event sits inside of. */
अटल अंतरभूत काष्ठा sk_buff *sctp_event2skb(स्थिर काष्ठा sctp_ulpevent *ev)
अणु
	वापस container_of((व्योम *)ev, काष्ठा sk_buff, cb);
पूर्ण

/* Retrieve & cast the event sitting inside the skb. */
अटल अंतरभूत काष्ठा sctp_ulpevent *sctp_skb2event(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा sctp_ulpevent *)skb->cb;
पूर्ण

व्योम sctp_ulpevent_मुक्त(काष्ठा sctp_ulpevent *);
पूर्णांक sctp_ulpevent_is_notअगरication(स्थिर काष्ठा sctp_ulpevent *);
अचिन्हित पूर्णांक sctp_queue_purge_ulpevents(काष्ठा sk_buff_head *list);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_assoc_change(
	स्थिर काष्ठा sctp_association *asoc,
	__u16 flags,
	__u16 state,
	__u16 error,
	__u16 outbound,
	__u16 inbound,
	काष्ठा sctp_chunk *chunk,
	gfp_t gfp);

व्योम sctp_ulpevent_notअगरy_peer_addr_change(काष्ठा sctp_transport *transport,
					   पूर्णांक state, पूर्णांक error);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_remote_error(
	स्थिर काष्ठा sctp_association *asoc,
	काष्ठा sctp_chunk *chunk,
	__u16 flags,
	gfp_t gfp);
काष्ठा sctp_ulpevent *sctp_ulpevent_make_send_failed(
	स्थिर काष्ठा sctp_association *asoc,
	काष्ठा sctp_chunk *chunk,
	__u16 flags,
	__u32 error,
	gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_send_failed_event(
	स्थिर काष्ठा sctp_association *asoc,
	काष्ठा sctp_chunk *chunk,
	__u16 flags,
	__u32 error,
	gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_shutकरोwn_event(
	स्थिर काष्ठा sctp_association *asoc,
	__u16 flags,
	gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_pdapi(
	स्थिर काष्ठा sctp_association *asoc,
	__u32 indication, __u32 sid, __u32 seq,
	__u32 flags, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_adaptation_indication(
	स्थिर काष्ठा sctp_association *asoc, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_rcvmsg(काष्ठा sctp_association *asoc,
	काष्ठा sctp_chunk *chunk,
	gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_authkey(
	स्थिर काष्ठा sctp_association *asoc, __u16 key_id,
	__u32 indication, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_sender_dry_event(
	स्थिर काष्ठा sctp_association *asoc, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_stream_reset_event(
	स्थिर काष्ठा sctp_association *asoc, __u16 flags,
	__u16 stream_num, __be16 *stream_list, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_assoc_reset_event(
	स्थिर काष्ठा sctp_association *asoc, __u16 flags,
	 __u32 local_tsn, __u32 remote_tsn, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_ulpevent_make_stream_change_event(
	स्थिर काष्ठा sctp_association *asoc, __u16 flags,
	__u32 strchange_instrms, __u32 strchange_outstrms, gfp_t gfp);

काष्ठा sctp_ulpevent *sctp_make_reassembled_event(
	काष्ठा net *net, काष्ठा sk_buff_head *queue,
	काष्ठा sk_buff *f_frag, काष्ठा sk_buff *l_frag);

व्योम sctp_ulpevent_पढ़ो_sndrcvinfo(स्थिर काष्ठा sctp_ulpevent *event,
				   काष्ठा msghdr *);
व्योम sctp_ulpevent_पढ़ो_rcvinfo(स्थिर काष्ठा sctp_ulpevent *event,
				काष्ठा msghdr *);
व्योम sctp_ulpevent_पढ़ो_nxtinfo(स्थिर काष्ठा sctp_ulpevent *event,
				काष्ठा msghdr *, काष्ठा sock *sk);

__u16 sctp_ulpevent_get_notअगरication_type(स्थिर काष्ठा sctp_ulpevent *event);

अटल अंतरभूत व्योम sctp_ulpevent_type_set(__u16 *subscribe,
					  __u16 sn_type, __u8 on)
अणु
	अगर (sn_type > SCTP_SN_TYPE_MAX)
		वापस;

	अगर (on)
		*subscribe |=  (1 << (sn_type - SCTP_SN_TYPE_BASE));
	अन्यथा
		*subscribe &= ~(1 << (sn_type - SCTP_SN_TYPE_BASE));
पूर्ण

/* Is this event type enabled? */
अटल अंतरभूत bool sctp_ulpevent_type_enabled(__u16 subscribe, __u16 sn_type)
अणु
	अगर (sn_type > SCTP_SN_TYPE_MAX)
		वापस false;

	वापस subscribe & (1 << (sn_type - SCTP_SN_TYPE_BASE));
पूर्ण

/* Given an event subscription, is this event enabled? */
अटल अंतरभूत bool sctp_ulpevent_is_enabled(स्थिर काष्ठा sctp_ulpevent *event,
					    __u16 subscribe)
अणु
	__u16 sn_type;

	अगर (!sctp_ulpevent_is_notअगरication(event))
		वापस true;

	sn_type = sctp_ulpevent_get_notअगरication_type(event);

	वापस sctp_ulpevent_type_enabled(subscribe, sn_type);
पूर्ण

#पूर्ण_अगर /* __sctp_ulpevent_h__ */
