<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These are definitions needed by the state machine.
 *
 * Please send any bug reports or fixes you make to the
 * email addresses:
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson <karl@athena.chicago.il.us>
 *    Xingang Guo <xingang.guo@पूर्णांकel.com>
 *    Jon Grimm <jgrimm@us.ibm.com>
 *    Dajiang Zhang <dajiang.zhang@nokia.com>
 *    Sridhar Samudrala <sri@us.ibm.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Ardelle Fan <ardelle.fan@पूर्णांकel.com>
 *    Kevin Gao <kevin.gao@पूर्णांकel.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <net/sctp/command.h>
#समावेश <net/sctp/sctp.h>

#अगर_अघोषित __sctp_sm_h__
#घोषणा __sctp_sm_h__

/*
 * Possible values क्रम the disposition are:
 */
क्रमागत sctp_disposition अणु
	SCTP_DISPOSITION_DISCARD,	 /* No further processing.  */
	SCTP_DISPOSITION_CONSUME,	 /* Process वापस values normally.  */
	SCTP_DISPOSITION_NOMEM,		 /* We ran out of memory--recover.  */
	SCTP_DISPOSITION_DELETE_TCB,	 /* Close the association.  */
	SCTP_DISPOSITION_ABORT,		 /* Close the association NOW.  */
	SCTP_DISPOSITION_VIOLATION,	 /* The peer is misbehaving.  */
	SCTP_DISPOSITION_NOT_IMPL,	 /* This entry is not implemented.  */
	SCTP_DISPOSITION_ERROR,		 /* This is plain old user error.  */
	SCTP_DISPOSITION_BUG,		 /* This is a bug.  */
पूर्ण;

प्रकार क्रमागत sctp_disposition (sctp_state_fn_t) (
					काष्ठा net *net,
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर जोड़ sctp_subtype type,
					व्योम *arg,
					काष्ठा sctp_cmd_seq *commands);
प्रकार व्योम (sctp_समयr_event_t) (काष्ठा समयr_list *);
काष्ठा sctp_sm_table_entry अणु
	sctp_state_fn_t *fn;
	स्थिर अक्षर *name;
पूर्ण;

/* A naming convention of "sctp_sf_xxx" applies to all the state functions
 * currently in use.
 */

/* Prototypes क्रम generic state functions. */
sctp_state_fn_t sctp_sf_not_impl;
sctp_state_fn_t sctp_sf_bug;

/* Prototypes क्रम gener समयr state functions. */
sctp_state_fn_t sctp_sf_समयr_ignore;

/* Prototypes क्रम chunk state functions. */
sctp_state_fn_t sctp_sf_करो_9_1_पात;
sctp_state_fn_t sctp_sf_cookie_रुको_पात;
sctp_state_fn_t sctp_sf_cookie_echoed_पात;
sctp_state_fn_t sctp_sf_shutकरोwn_pending_पात;
sctp_state_fn_t sctp_sf_shutकरोwn_sent_पात;
sctp_state_fn_t sctp_sf_shutकरोwn_ack_sent_पात;
sctp_state_fn_t sctp_sf_करो_5_1B_init;
sctp_state_fn_t sctp_sf_करो_5_1C_ack;
sctp_state_fn_t sctp_sf_करो_5_1D_ce;
sctp_state_fn_t sctp_sf_करो_5_1E_ca;
sctp_state_fn_t sctp_sf_करो_4_C;
sctp_state_fn_t sctp_sf_eat_data_6_2;
sctp_state_fn_t sctp_sf_eat_data_fast_4_4;
sctp_state_fn_t sctp_sf_eat_sack_6_2;
sctp_state_fn_t sctp_sf_operr_notअगरy;
sctp_state_fn_t sctp_sf_t1_init_समयr_expire;
sctp_state_fn_t sctp_sf_t1_cookie_समयr_expire;
sctp_state_fn_t sctp_sf_t2_समयr_expire;
sctp_state_fn_t sctp_sf_t4_समयr_expire;
sctp_state_fn_t sctp_sf_t5_समयr_expire;
sctp_state_fn_t sctp_sf_sendbeat_8_3;
sctp_state_fn_t sctp_sf_beat_8_3;
sctp_state_fn_t sctp_sf_backbeat_8_3;
sctp_state_fn_t sctp_sf_करो_9_2_final;
sctp_state_fn_t sctp_sf_करो_9_2_shutकरोwn;
sctp_state_fn_t sctp_sf_करो_9_2_shut_ctsn;
sctp_state_fn_t sctp_sf_करो_ecn_cwr;
sctp_state_fn_t sctp_sf_करो_ecne;
sctp_state_fn_t sctp_sf_ootb;
sctp_state_fn_t sctp_sf_pdiscard;
sctp_state_fn_t sctp_sf_violation;
sctp_state_fn_t sctp_sf_discard_chunk;
sctp_state_fn_t sctp_sf_करो_5_2_1_siminit;
sctp_state_fn_t sctp_sf_करो_5_2_2_dupinit;
sctp_state_fn_t sctp_sf_करो_5_2_3_initack;
sctp_state_fn_t sctp_sf_करो_5_2_4_dupcook;
sctp_state_fn_t sctp_sf_unk_chunk;
sctp_state_fn_t sctp_sf_करो_8_5_1_E_sa;
sctp_state_fn_t sctp_sf_cookie_echoed_err;
sctp_state_fn_t sctp_sf_करो_asconf;
sctp_state_fn_t sctp_sf_करो_asconf_ack;
sctp_state_fn_t sctp_sf_करो_reconf;
sctp_state_fn_t sctp_sf_करो_9_2_reshutack;
sctp_state_fn_t sctp_sf_eat_fwd_tsn;
sctp_state_fn_t sctp_sf_eat_fwd_tsn_fast;
sctp_state_fn_t sctp_sf_eat_auth;

/* Prototypes क्रम primitive event state functions.  */
sctp_state_fn_t sctp_sf_करो_prm_asoc;
sctp_state_fn_t sctp_sf_करो_prm_send;
sctp_state_fn_t sctp_sf_करो_9_2_prm_shutकरोwn;
sctp_state_fn_t sctp_sf_cookie_रुको_prm_shutकरोwn;
sctp_state_fn_t sctp_sf_cookie_echoed_prm_shutकरोwn;
sctp_state_fn_t sctp_sf_करो_9_1_prm_पात;
sctp_state_fn_t sctp_sf_cookie_रुको_prm_पात;
sctp_state_fn_t sctp_sf_cookie_echoed_prm_पात;
sctp_state_fn_t sctp_sf_shutकरोwn_pending_prm_पात;
sctp_state_fn_t sctp_sf_shutकरोwn_sent_prm_पात;
sctp_state_fn_t sctp_sf_shutकरोwn_ack_sent_prm_पात;
sctp_state_fn_t sctp_sf_error_बंदd;
sctp_state_fn_t sctp_sf_error_shutकरोwn;
sctp_state_fn_t sctp_sf_ignore_primitive;
sctp_state_fn_t sctp_sf_करो_prm_requestheartbeat;
sctp_state_fn_t sctp_sf_करो_prm_asconf;
sctp_state_fn_t sctp_sf_करो_prm_reconf;

/* Prototypes क्रम other event state functions.  */
sctp_state_fn_t sctp_sf_करो_no_pending_tsn;
sctp_state_fn_t sctp_sf_करो_9_2_start_shutकरोwn;
sctp_state_fn_t sctp_sf_करो_9_2_shutकरोwn_ack;
sctp_state_fn_t sctp_sf_ignore_other;
sctp_state_fn_t sctp_sf_cookie_रुको_icmp_पात;

/* Prototypes क्रम समयout event state functions.  */
sctp_state_fn_t sctp_sf_करो_6_3_3_rtx;
sctp_state_fn_t sctp_sf_send_reconf;
sctp_state_fn_t sctp_sf_करो_6_2_sack;
sctp_state_fn_t sctp_sf_स्वतःबंद_समयr_expire;

/* Prototypes क्रम utility support functions.  */
__u8 sctp_get_chunk_type(काष्ठा sctp_chunk *chunk);
स्थिर काष्ठा sctp_sm_table_entry *sctp_sm_lookup_event(
					काष्ठा net *net,
					क्रमागत sctp_event_type event_type,
					क्रमागत sctp_state state,
					जोड़ sctp_subtype event_subtype);
पूर्णांक sctp_chunk_iअगर(स्थिर काष्ठा sctp_chunk *);
काष्ठा sctp_association *sctp_make_temp_asoc(स्थिर काष्ठा sctp_endpoपूर्णांक *,
					     काष्ठा sctp_chunk *,
					     gfp_t gfp);
__u32 sctp_generate_verअगरication_tag(व्योम);
व्योम sctp_populate_tie_tags(__u8 *cookie, __u32 curTag, __u32 hisTag);

/* Prototypes क्रम chunk-building functions.  */
काष्ठा sctp_chunk *sctp_make_init(स्थिर काष्ठा sctp_association *asoc,
				  स्थिर काष्ठा sctp_bind_addr *bp,
				  gfp_t gfp, पूर्णांक vparam_len);
काष्ठा sctp_chunk *sctp_make_init_ack(स्थिर काष्ठा sctp_association *asoc,
				      स्थिर काष्ठा sctp_chunk *chunk,
				      स्थिर gfp_t gfp, स्थिर पूर्णांक unkparam_len);
काष्ठा sctp_chunk *sctp_make_cookie_echo(स्थिर काष्ठा sctp_association *asoc,
					 स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_cookie_ack(स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_cwr(स्थिर काष्ठा sctp_association *asoc,
				 स्थिर __u32 lowest_tsn,
				 स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_idata(स्थिर काष्ठा sctp_association *asoc,
				   __u8 flags, पूर्णांक paylen, gfp_t gfp);
काष्ठा sctp_chunk *sctp_make_अगरwdtsn(स्थिर काष्ठा sctp_association *asoc,
				     __u32 new_cum_tsn, माप_प्रकार nstreams,
				     काष्ठा sctp_अगरwdtsn_skip *skiplist);
काष्ठा sctp_chunk *sctp_make_datafrag_empty(स्थिर काष्ठा sctp_association *asoc,
					    स्थिर काष्ठा sctp_sndrcvinfo *sinfo,
					    पूर्णांक len, __u8 flags, gfp_t gfp);
काष्ठा sctp_chunk *sctp_make_ecne(स्थिर काष्ठा sctp_association *asoc,
				  स्थिर __u32 lowest_tsn);
काष्ठा sctp_chunk *sctp_make_sack(काष्ठा sctp_association *asoc);
काष्ठा sctp_chunk *sctp_make_shutकरोwn(स्थिर काष्ठा sctp_association *asoc,
				      स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_shutकरोwn_ack(स्थिर काष्ठा sctp_association *asoc,
					  स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_shutकरोwn_complete(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk);
पूर्णांक sctp_init_cause(काष्ठा sctp_chunk *chunk, __be16 cause, माप_प्रकार paylen);
काष्ठा sctp_chunk *sctp_make_पात(स्थिर काष्ठा sctp_association *asoc,
				   स्थिर काष्ठा sctp_chunk *chunk,
				   स्थिर माप_प्रकार hपूर्णांक);
काष्ठा sctp_chunk *sctp_make_पात_no_data(स्थिर काष्ठा sctp_association *asoc,
					   स्थिर काष्ठा sctp_chunk *chunk,
					   __u32 tsn);
काष्ठा sctp_chunk *sctp_make_पात_user(स्थिर काष्ठा sctp_association *asoc,
					काष्ठा msghdr *msg, माप_प्रकार msg_len);
काष्ठा sctp_chunk *sctp_make_पात_violation(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk,
					स्थिर __u8 *payload,
					स्थिर माप_प्रकार paylen);
काष्ठा sctp_chunk *sctp_make_violation_paramlen(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk,
					काष्ठा sctp_paramhdr *param);
काष्ठा sctp_chunk *sctp_make_violation_max_retrans(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_new_encap_port(
					स्थिर काष्ठा sctp_association *asoc,
					स्थिर काष्ठा sctp_chunk *chunk);
काष्ठा sctp_chunk *sctp_make_heartbeat(स्थिर काष्ठा sctp_association *asoc,
				       स्थिर काष्ठा sctp_transport *transport);
काष्ठा sctp_chunk *sctp_make_heartbeat_ack(स्थिर काष्ठा sctp_association *asoc,
					   स्थिर काष्ठा sctp_chunk *chunk,
					   स्थिर व्योम *payload,
					   स्थिर माप_प्रकार paylen);
काष्ठा sctp_chunk *sctp_make_op_error(स्थिर काष्ठा sctp_association *asoc,
				      स्थिर काष्ठा sctp_chunk *chunk,
				      __be16 cause_code, स्थिर व्योम *payload,
				      माप_प्रकार paylen, माप_प्रकार reserve_tail);

काष्ठा sctp_chunk *sctp_make_asconf_update_ip(काष्ठा sctp_association *asoc,
					      जोड़ sctp_addr *laddr,
					      काष्ठा sockaddr *addrs,
					      पूर्णांक addrcnt, __be16 flags);
काष्ठा sctp_chunk *sctp_make_asconf_set_prim(काष्ठा sctp_association *asoc,
					     जोड़ sctp_addr *addr);
bool sctp_verअगरy_asconf(स्थिर काष्ठा sctp_association *asoc,
			काष्ठा sctp_chunk *chunk, bool addr_param_needed,
			काष्ठा sctp_paramhdr **errp);
काष्ठा sctp_chunk *sctp_process_asconf(काष्ठा sctp_association *asoc,
				       काष्ठा sctp_chunk *asconf);
पूर्णांक sctp_process_asconf_ack(काष्ठा sctp_association *asoc,
			    काष्ठा sctp_chunk *asconf_ack);
काष्ठा sctp_chunk *sctp_make_fwdtsn(स्थिर काष्ठा sctp_association *asoc,
				    __u32 new_cum_tsn, माप_प्रकार nstreams,
				    काष्ठा sctp_fwdtsn_skip *skiplist);
काष्ठा sctp_chunk *sctp_make_auth(स्थिर काष्ठा sctp_association *asoc,
				  __u16 key_id);
काष्ठा sctp_chunk *sctp_make_strreset_req(स्थिर काष्ठा sctp_association *asoc,
					  __u16 stream_num, __be16 *stream_list,
					  bool out, bool in);
काष्ठा sctp_chunk *sctp_make_strreset_tsnreq(
					स्थिर काष्ठा sctp_association *asoc);
काष्ठा sctp_chunk *sctp_make_strreset_addstrm(
					स्थिर काष्ठा sctp_association *asoc,
					__u16 out, __u16 in);
काष्ठा sctp_chunk *sctp_make_strreset_resp(स्थिर काष्ठा sctp_association *asoc,
					   __u32 result, __u32 sn);
काष्ठा sctp_chunk *sctp_make_strreset_tsnresp(काष्ठा sctp_association *asoc,
					      __u32 result, __u32 sn,
					      __u32 sender_tsn,
					      __u32 receiver_tsn);
bool sctp_verअगरy_reconf(स्थिर काष्ठा sctp_association *asoc,
			काष्ठा sctp_chunk *chunk,
			काष्ठा sctp_paramhdr **errp);
व्योम sctp_chunk_assign_tsn(काष्ठा sctp_chunk *chunk);
व्योम sctp_chunk_assign_ssn(काष्ठा sctp_chunk *chunk);

/* Prototypes क्रम stream-processing functions.  */
काष्ठा sctp_chunk *sctp_process_strreset_outreq(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp);
काष्ठा sctp_chunk *sctp_process_strreset_inreq(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp);
काष्ठा sctp_chunk *sctp_process_strreset_tsnreq(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp);
काष्ठा sctp_chunk *sctp_process_strreset_addstrm_out(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp);
काष्ठा sctp_chunk *sctp_process_strreset_addstrm_in(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp);
काष्ठा sctp_chunk *sctp_process_strreset_resp(
				काष्ठा sctp_association *asoc,
				जोड़ sctp_params param,
				काष्ठा sctp_ulpevent **evp);

/* Prototypes क्रम statetable processing. */

पूर्णांक sctp_करो_sm(काष्ठा net *net, क्रमागत sctp_event_type event_type,
	       जोड़ sctp_subtype subtype, क्रमागत sctp_state state,
	       काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sctp_association *asoc,
	       व्योम *event_arg, gfp_t gfp);

/* 2nd level prototypes */
व्योम sctp_generate_t3_rtx_event(काष्ठा समयr_list *t);
व्योम sctp_generate_heartbeat_event(काष्ठा समयr_list *t);
व्योम sctp_generate_reconf_event(काष्ठा समयr_list *t);
व्योम sctp_generate_proto_unreach_event(काष्ठा समयr_list *t);

व्योम sctp_ootb_pkt_मुक्त(काष्ठा sctp_packet *packet);

काष्ठा sctp_association *sctp_unpack_cookie(
					स्थिर काष्ठा sctp_endpoपूर्णांक *ep,
					स्थिर काष्ठा sctp_association *asoc,
					काष्ठा sctp_chunk *chunk,
					gfp_t gfp, पूर्णांक *err,
					काष्ठा sctp_chunk **err_chk_p);

/* 3rd level prototypes */
__u32 sctp_generate_tag(स्थिर काष्ठा sctp_endpoपूर्णांक *ep);
__u32 sctp_generate_tsn(स्थिर काष्ठा sctp_endpoपूर्णांक *ep);

/* Extern declarations क्रम major data काष्ठाures.  */
बाह्य sctp_समयr_event_t *sctp_समयr_events[SCTP_NUM_TIMEOUT_TYPES];


/* Get the size of a DATA chunk payload. */
अटल अंतरभूत __u16 sctp_data_size(काष्ठा sctp_chunk *chunk)
अणु
	__u16 size;

	size = ntohs(chunk->chunk_hdr->length);
	size -= sctp_datachk_len(&chunk->asoc->stream);

	वापस size;
पूर्ण

/* Compare two TSNs */
#घोषणा TSN_lt(a,b)	\
	(typecheck(__u32, a) && \
	 typecheck(__u32, b) && \
	 ((__s32)((a) - (b)) < 0))

#घोषणा TSN_lte(a,b)	\
	(typecheck(__u32, a) && \
	 typecheck(__u32, b) && \
	 ((__s32)((a) - (b)) <= 0))

/* Compare two MIDs */
#घोषणा MID_lt(a, b)	\
	(typecheck(__u32, a) && \
	 typecheck(__u32, b) && \
	 ((__s32)((a) - (b)) < 0))

/* Compare two SSNs */
#घोषणा SSN_lt(a,b)		\
	(typecheck(__u16, a) && \
	 typecheck(__u16, b) && \
	 ((__s16)((a) - (b)) < 0))

/* ADDIP 3.1.1 */
#घोषणा ADDIP_SERIAL_gte(a,b)	\
	(typecheck(__u32, a) && \
	 typecheck(__u32, b) && \
	 ((__s32)((b) - (a)) <= 0))

/* Check VTAG of the packet matches the sender's own tag. */
अटल अंतरभूत पूर्णांक
sctp_vtag_verअगरy(स्थिर काष्ठा sctp_chunk *chunk,
		 स्थिर काष्ठा sctp_association *asoc)
अणु
	/* RFC 2960 Sec 8.5 When receiving an SCTP packet, the endpoपूर्णांक
	 * MUST ensure that the value in the Verअगरication Tag field of
	 * the received SCTP packet matches its own Tag. If the received
	 * Verअगरication Tag value करोes not match the receiver's own
	 * tag value, the receiver shall silently discard the packet...
	 */
        अगर (ntohl(chunk->sctp_hdr->vtag) == asoc->c.my_vtag)
                वापस 1;

	chunk->transport->encap_port = SCTP_INPUT_CB(chunk->skb)->encap_port;
	वापस 0;
पूर्ण

/* Check VTAG of the packet matches the sender's own tag and the T bit is
 * not set, OR its peer's tag and the T bit is set in the Chunk Flags.
 */
अटल अंतरभूत पूर्णांक
sctp_vtag_verअगरy_either(स्थिर काष्ठा sctp_chunk *chunk,
			स्थिर काष्ठा sctp_association *asoc)
अणु
        /* RFC 2960 Section 8.5.1, sctpimpguide Section 2.41
	 *
	 * B) The receiver of a ABORT MUST accept the packet
	 *    अगर the Verअगरication Tag field of the packet matches its own tag
	 *    and the T bit is not set
	 *    OR
	 *    it is set to its peer's tag and the T bit is set in the Chunk
	 *    Flags.
	 *    Otherwise, the receiver MUST silently discard the packet
	 *    and take no further action.
	 *
	 * C) The receiver of a SHUTDOWN COMPLETE shall accept the packet
	 *    अगर the Verअगरication Tag field of the packet matches its own tag
	 *    and the T bit is not set
	 *    OR
	 *    it is set to its peer's tag and the T bit is set in the Chunk
	 *    Flags.
	 *    Otherwise, the receiver MUST silently discard the packet
	 *    and take no further action.  An endpoपूर्णांक MUST ignore the
	 *    SHUTDOWN COMPLETE अगर it is not in the SHUTDOWN-ACK-SENT state.
	 */
        अगर ((!sctp_test_T_bit(chunk) &&
             (ntohl(chunk->sctp_hdr->vtag) == asoc->c.my_vtag)) ||
	    (sctp_test_T_bit(chunk) && asoc->c.peer_vtag &&
	     (ntohl(chunk->sctp_hdr->vtag) == asoc->c.peer_vtag))) अणु
                वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __sctp_sm_h__ */
