<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _DCCP_H
#घोषणा _DCCP_H
/*
 *  net/dccp/dccp.h
 *
 *  An implementation of the DCCP protocol
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *  Copyright (c) 2005-6 Ian McDonald <ian.mcकरोnald@jandi.co.nz>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/kसमय.स>
#समावेश <net/snmp.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश "ackvec.h"

/*
 * 	DCCP - specअगरic warning and debugging macros.
 */
#घोषणा DCCP_WARN(fmt, ...)						\
	net_warn_ratelimited("%s: " fmt, __func__, ##__VA_ARGS__)
#घोषणा DCCP_CRIT(fmt, a...) prपूर्णांकk(KERN_CRIT fmt " at %s:%d/%s()\n", ##a, \
					 __खाता__, __LINE__, __func__)
#घोषणा DCCP_BUG(a...)       करो अणु DCCP_CRIT("BUG: " a); dump_stack(); पूर्ण जबतक(0)
#घोषणा DCCP_BUG_ON(cond)    करो अणु अगर (unlikely((cond) != 0))		   \
				     DCCP_BUG("\"%s\" holds (exception!)", \
					      __stringअगरy(cond));          \
			     पूर्ण जबतक (0)

#घोषणा DCCP_PRINTK(enable, fmt, args...)	करो अणु अगर (enable)	     \
							prपूर्णांकk(fmt, ##args); \
						पूर्ण जबतक(0)
#घोषणा DCCP_PR_DEBUG(enable, fmt, a...)	DCCP_PRINTK(enable, KERN_DEBUG \
						  "%s: " fmt, __func__, ##a)

#अगर_घोषित CONFIG_IP_DCCP_DEBUG
बाह्य bool dccp_debug;
#घोषणा dccp_pr_debug(क्रमmat, a...)	  DCCP_PR_DEBUG(dccp_debug, क्रमmat, ##a)
#घोषणा dccp_pr_debug_cat(क्रमmat, a...)   DCCP_PRINTK(dccp_debug, क्रमmat, ##a)
#घोषणा dccp_debug(fmt, a...)		  dccp_pr_debug_cat(KERN_DEBUG fmt, ##a)
#अन्यथा
#घोषणा dccp_pr_debug(क्रमmat, a...)
#घोषणा dccp_pr_debug_cat(क्रमmat, a...)
#घोषणा dccp_debug(क्रमmat, a...)
#पूर्ण_अगर

बाह्य काष्ठा inet_hashinfo dccp_hashinfo;

बाह्य काष्ठा percpu_counter dccp_orphan_count;

व्योम dccp_समय_रुको(काष्ठा sock *sk, पूर्णांक state, पूर्णांक समयo);

/*
 *  Set safe upper bounds क्रम header and option length. Since Data Offset is 8
 *  bits (RFC 4340, sec. 5.1), the total header length can never be more than
 *  4 * 255 = 1020 bytes. The largest possible header length is 28 bytes (X=1):
 *    - DCCP-Response with ACK Subheader and 4 bytes of Service code      OR
 *    - DCCP-Reset    with ACK Subheader and 4 bytes of Reset Code fields
 *  Hence a safe upper bound क्रम the maximum option length is 1020-28 = 992
 */
#घोषणा MAX_DCCP_SPECIFIC_HEADER (255 * माप(uपूर्णांक32_t))
#घोषणा DCCP_MAX_PACKET_HDR 28
#घोषणा DCCP_MAX_OPT_LEN (MAX_DCCP_SPECIFIC_HEADER - DCCP_MAX_PACKET_HDR)
#घोषणा MAX_DCCP_HEADER (MAX_DCCP_SPECIFIC_HEADER + MAX_HEADER)

/* Upper bound क्रम initial feature-negotiation overhead (padded to 32 bits) */
#घोषणा DCCP_FEATNEG_OVERHEAD	 (32 * माप(uपूर्णांक32_t))

#घोषणा DCCP_TIMEWAIT_LEN (60 * HZ) /* how दीर्घ to रुको to destroy TIME-WAIT
				     * state, about 60 seconds */

/* RFC 1122, 4.2.3.1 initial RTO value */
#घोषणा DCCP_TIMEOUT_INIT ((अचिन्हित पूर्णांक)(3 * HZ))

/*
 * The maximum back-off value क्रम retransmissions. This is needed क्रम
 *  - retransmitting client-Requests (sec. 8.1.1),
 *  - retransmitting Close/CloseReq when closing (sec. 8.3),
 *  - feature-negotiation retransmission (sec. 6.6.3),
 *  - Acks in client-PARTOPEN state (sec. 8.1.5).
 */
#घोषणा DCCP_RTO_MAX ((अचिन्हित पूर्णांक)(64 * HZ))

/*
 * RTT sampling: sanity bounds and fallback RTT value from RFC 4340, section 3.4
 */
#घोषणा DCCP_SANE_RTT_MIN	100
#घोषणा DCCP_FALLBACK_RTT	(USEC_PER_SEC / 5)
#घोषणा DCCP_SANE_RTT_MAX	(3 * USEC_PER_SEC)

/* sysctl variables क्रम DCCP */
बाह्य पूर्णांक  sysctl_dccp_request_retries;
बाह्य पूर्णांक  sysctl_dccp_retries1;
बाह्य पूर्णांक  sysctl_dccp_retries2;
बाह्य पूर्णांक  sysctl_dccp_tx_qlen;
बाह्य पूर्णांक  sysctl_dccp_sync_ratelimit;

/*
 *	48-bit sequence number arithmetic (चिन्हित and अचिन्हित)
 */
#घोषणा INT48_MIN	  0x800000000000LL		/* 2^47	    */
#घोषणा UINT48_MAX	  0xFFFFFFFFFFFFLL		/* 2^48 - 1 */
#घोषणा COMPLEMENT48(x)	 (0x1000000000000LL - (x))	/* 2^48 - x */
#घोषणा TO_SIGNED48(x)	 (((x) < INT48_MIN)? (x) : -COMPLEMENT48( (x)))
#घोषणा TO_UNSIGNED48(x) (((x) >= 0)?	     (x) :  COMPLEMENT48(-(x)))
#घोषणा ADD48(a, b)	 (((a) + (b)) & UINT48_MAX)
#घोषणा SUB48(a, b)	 ADD48((a), COMPLEMENT48(b))

अटल अंतरभूत व्योम dccp_inc_seqno(u64 *seqno)
अणु
	*seqno = ADD48(*seqno, 1);
पूर्ण

/* चिन्हित mod-2^48 distance: pos. अगर seqno1 < seqno2, neg. अगर seqno1 > seqno2 */
अटल अंतरभूत s64 dccp_delta_seqno(स्थिर u64 seqno1, स्थिर u64 seqno2)
अणु
	u64 delta = SUB48(seqno2, seqno1);

	वापस TO_SIGNED48(delta);
पूर्ण

/* is seq1 < seq2 ? */
अटल अंतरभूत पूर्णांक beक्रमe48(स्थिर u64 seq1, स्थिर u64 seq2)
अणु
	वापस (s64)((seq2 << 16) - (seq1 << 16)) > 0;
पूर्ण

/* is seq1 > seq2 ? */
#घोषणा after48(seq1, seq2)	beक्रमe48(seq2, seq1)

/* is seq2 <= seq1 <= seq3 ? */
अटल अंतरभूत पूर्णांक between48(स्थिर u64 seq1, स्थिर u64 seq2, स्थिर u64 seq3)
अणु
	वापस (seq3 << 16) - (seq2 << 16) >= (seq1 << 16) - (seq2 << 16);
पूर्ण

अटल अंतरभूत u64 max48(स्थिर u64 seq1, स्थिर u64 seq2)
अणु
	वापस after48(seq1, seq2) ? seq1 : seq2;
पूर्ण

/**
 * dccp_loss_count - Approximate the number of lost data packets in a burst loss
 * @s1:  last known sequence number beक्रमe the loss ('hole')
 * @s2:  first sequence number seen after the 'hole'
 * @ndp: NDP count on packet with sequence number @s2
 */
अटल अंतरभूत u64 dccp_loss_count(स्थिर u64 s1, स्थिर u64 s2, स्थिर u64 ndp)
अणु
	s64 delta = dccp_delta_seqno(s1, s2);

	WARN_ON(delta < 0);
	delta -= ndp + 1;

	वापस delta > 0 ? delta : 0;
पूर्ण

/**
 * dccp_loss_मुक्त - Evaluate condition क्रम data loss from RFC 4340, 7.7.1
 */
अटल अंतरभूत bool dccp_loss_मुक्त(स्थिर u64 s1, स्थिर u64 s2, स्थिर u64 ndp)
अणु
	वापस dccp_loss_count(s1, s2, ndp) == 0;
पूर्ण

क्रमागत अणु
	DCCP_MIB_NUM = 0,
	DCCP_MIB_ACTIVEOPENS,			/* ActiveOpens */
	DCCP_MIB_ESTABRESETS,			/* EstabResets */
	DCCP_MIB_CURRESTAB,			/* CurrEstab */
	DCCP_MIB_OUTSEGS,			/* OutSegs */
	DCCP_MIB_OUTRSTS,
	DCCP_MIB_ABORTONTIMEOUT,
	DCCP_MIB_TIMEOUTS,
	DCCP_MIB_ABORTFAILED,
	DCCP_MIB_PASSIVEOPENS,
	DCCP_MIB_ATTEMPTFAILS,
	DCCP_MIB_OUTDATAGRAMS,
	DCCP_MIB_INERRS,
	DCCP_MIB_OPTMANDATORYERROR,
	DCCP_MIB_INVALIDOPT,
	__DCCP_MIB_MAX
पूर्ण;

#घोषणा DCCP_MIB_MAX	__DCCP_MIB_MAX
काष्ठा dccp_mib अणु
	अचिन्हित दीर्घ	mibs[DCCP_MIB_MAX];
पूर्ण;

DECLARE_SNMP_STAT(काष्ठा dccp_mib, dccp_statistics);
#घोषणा DCCP_INC_STATS(field)	SNMP_INC_STATS(dccp_statistics, field)
#घोषणा __DCCP_INC_STATS(field)	__SNMP_INC_STATS(dccp_statistics, field)
#घोषणा DCCP_DEC_STATS(field)	SNMP_DEC_STATS(dccp_statistics, field)

/*
 * 	Checksumming routines
 */
अटल अंतरभूत अचिन्हित पूर्णांक dccp_csum_coverage(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dccp_hdr* dh = dccp_hdr(skb);

	अगर (dh->dccph_cscov == 0)
		वापस skb->len;
	वापस (dh->dccph_करोff + dh->dccph_cscov - 1) * माप(u32);
पूर्ण

अटल अंतरभूत व्योम dccp_csum_outgoing(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक cov = dccp_csum_coverage(skb);

	अगर (cov >= skb->len)
		dccp_hdr(skb)->dccph_cscov = 0;

	skb->csum = skb_checksum(skb, 0, (cov > skb->len)? skb->len : cov, 0);
पूर्ण

व्योम dccp_v4_send_check(काष्ठा sock *sk, काष्ठा sk_buff *skb);

पूर्णांक dccp_retransmit_skb(काष्ठा sock *sk);

व्योम dccp_send_ack(काष्ठा sock *sk);
व्योम dccp_reqsk_send_ack(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 काष्ठा request_sock *rsk);

व्योम dccp_send_sync(काष्ठा sock *sk, स्थिर u64 seq,
		    स्थिर क्रमागत dccp_pkt_type pkt_type);

/*
 * TX Packet Dequeueing Interface
 */
व्योम dccp_qpolicy_push(काष्ठा sock *sk, काष्ठा sk_buff *skb);
bool dccp_qpolicy_full(काष्ठा sock *sk);
व्योम dccp_qpolicy_drop(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा sk_buff *dccp_qpolicy_top(काष्ठा sock *sk);
काष्ठा sk_buff *dccp_qpolicy_pop(काष्ठा sock *sk);
bool dccp_qpolicy_param_ok(काष्ठा sock *sk, __be32 param);

/*
 * TX Packet Output and TX Timers
 */
व्योम dccp_ग_लिखो_xmit(काष्ठा sock *sk);
व्योम dccp_ग_लिखो_space(काष्ठा sock *sk);
व्योम dccp_flush_ग_लिखो_queue(काष्ठा sock *sk, दीर्घ *समय_budget);

व्योम dccp_init_xmit_समयrs(काष्ठा sock *sk);
अटल अंतरभूत व्योम dccp_clear_xmit_समयrs(काष्ठा sock *sk)
अणु
	inet_csk_clear_xmit_समयrs(sk);
पूर्ण

अचिन्हित पूर्णांक dccp_sync_mss(काष्ठा sock *sk, u32 pmtu);

स्थिर अक्षर *dccp_packet_name(स्थिर पूर्णांक type);

व्योम dccp_set_state(काष्ठा sock *sk, स्थिर पूर्णांक state);
व्योम dccp_करोne(काष्ठा sock *sk);

पूर्णांक dccp_reqsk_init(काष्ठा request_sock *rq, काष्ठा dccp_sock स्थिर *dp,
		    काष्ठा sk_buff स्थिर *skb);

पूर्णांक dccp_v4_conn_request(काष्ठा sock *sk, काष्ठा sk_buff *skb);

काष्ठा sock *dccp_create_खोलोreq_child(स्थिर काष्ठा sock *sk,
				       स्थिर काष्ठा request_sock *req,
				       स्थिर काष्ठा sk_buff *skb);

पूर्णांक dccp_v4_करो_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

काष्ठा sock *dccp_v4_request_recv_sock(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				       काष्ठा request_sock *req,
				       काष्ठा dst_entry *dst,
				       काष्ठा request_sock *req_unhash,
				       bool *own_req);
काष्ठा sock *dccp_check_req(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा request_sock *req);

पूर्णांक dccp_child_process(काष्ठा sock *parent, काष्ठा sock *child,
		       काष्ठा sk_buff *skb);
पूर्णांक dccp_rcv_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			   काष्ठा dccp_hdr *dh, अचिन्हित पूर्णांक len);
पूर्णांक dccp_rcv_established(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			 स्थिर काष्ठा dccp_hdr *dh, स्थिर अचिन्हित पूर्णांक len);

पूर्णांक dccp_init_sock(काष्ठा sock *sk, स्थिर __u8 ctl_sock_initialized);
व्योम dccp_destroy_sock(काष्ठा sock *sk);

व्योम dccp_बंद(काष्ठा sock *sk, दीर्घ समयout);
काष्ठा sk_buff *dccp_make_response(स्थिर काष्ठा sock *sk, काष्ठा dst_entry *dst,
				   काष्ठा request_sock *req);

पूर्णांक dccp_connect(काष्ठा sock *sk);
पूर्णांक dccp_disconnect(काष्ठा sock *sk, पूर्णांक flags);
पूर्णांक dccp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen);
पूर्णांक dccp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    sockptr_t optval, अचिन्हित पूर्णांक optlen);
पूर्णांक dccp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक dccp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक dccp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक nonblock,
		 पूर्णांक flags, पूर्णांक *addr_len);
व्योम dccp_shutकरोwn(काष्ठा sock *sk, पूर्णांक how);
पूर्णांक inet_dccp_listen(काष्ठा socket *sock, पूर्णांक backlog);
__poll_t dccp_poll(काष्ठा file *file, काष्ठा socket *sock,
		       poll_table *रुको);
पूर्णांक dccp_v4_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
व्योम dccp_req_err(काष्ठा sock *sk, u64 seq);

काष्ठा sk_buff *dccp_ctl_make_reset(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक dccp_send_reset(काष्ठा sock *sk, क्रमागत dccp_reset_codes code);
व्योम dccp_send_बंद(काष्ठा sock *sk, स्थिर पूर्णांक active);
पूर्णांक dccp_invalid_packet(काष्ठा sk_buff *skb);
u32 dccp_sample_rtt(काष्ठा sock *sk, दीर्घ delta);

अटल अंतरभूत bool dccp_bad_service_code(स्थिर काष्ठा sock *sk,
					स्थिर __be32 service)
अणु
	स्थिर काष्ठा dccp_sock *dp = dccp_sk(sk);

	अगर (dp->dccps_service == service)
		वापस false;
	वापस !dccp_list_has_service(dp->dccps_service_list, service);
पूर्ण

/**
 * dccp_skb_cb  -  DCCP per-packet control inक्रमmation
 * @dccpd_type: one of %dccp_pkt_type (or unknown)
 * @dccpd_ccval: CCVal field (5.1), see e.g. RFC 4342, 8.1
 * @dccpd_reset_code: one of %dccp_reset_codes
 * @dccpd_reset_data: Data1..3 fields (depend on @dccpd_reset_code)
 * @dccpd_opt_len: total length of all options (5.8) in the packet
 * @dccpd_seq: sequence number
 * @dccpd_ack_seq: acknowledgment number subheader field value
 *
 * This is used क्रम transmission as well as क्रम reception.
 */
काष्ठा dccp_skb_cb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm	h4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा inet6_skb_parm	h6;
#पूर्ण_अगर
	पूर्ण header;
	__u8  dccpd_type:4;
	__u8  dccpd_ccval:4;
	__u8  dccpd_reset_code,
	      dccpd_reset_data[3];
	__u16 dccpd_opt_len;
	__u64 dccpd_seq;
	__u64 dccpd_ack_seq;
पूर्ण;

#घोषणा DCCP_SKB_CB(__skb) ((काष्ठा dccp_skb_cb *)&((__skb)->cb[0]))

/* RFC 4340, sec. 7.7 */
अटल अंतरभूत पूर्णांक dccp_non_data_packet(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर __u8 type = DCCP_SKB_CB(skb)->dccpd_type;

	वापस type == DCCP_PKT_ACK	 ||
	       type == DCCP_PKT_CLOSE	 ||
	       type == DCCP_PKT_CLOSEREQ ||
	       type == DCCP_PKT_RESET	 ||
	       type == DCCP_PKT_SYNC	 ||
	       type == DCCP_PKT_SYNCACK;
पूर्ण

/* RFC 4340, sec. 7.7 */
अटल अंतरभूत पूर्णांक dccp_data_packet(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर __u8 type = DCCP_SKB_CB(skb)->dccpd_type;

	वापस type == DCCP_PKT_DATA	 ||
	       type == DCCP_PKT_DATAACK  ||
	       type == DCCP_PKT_REQUEST  ||
	       type == DCCP_PKT_RESPONSE;
पूर्ण

अटल अंतरभूत पूर्णांक dccp_packet_without_ack(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर __u8 type = DCCP_SKB_CB(skb)->dccpd_type;

	वापस type == DCCP_PKT_DATA || type == DCCP_PKT_REQUEST;
पूर्ण

#घोषणा DCCP_PKT_WITHOUT_ACK_SEQ (UINT48_MAX << 2)

अटल अंतरभूत व्योम dccp_hdr_set_seq(काष्ठा dccp_hdr *dh, स्थिर u64 gss)
अणु
	काष्ठा dccp_hdr_ext *dhx = (काष्ठा dccp_hdr_ext *)((व्योम *)dh +
							   माप(*dh));
	dh->dccph_seq2 = 0;
	dh->dccph_seq = htons((gss >> 32) & 0xfffff);
	dhx->dccph_seq_low = htonl(gss & 0xffffffff);
पूर्ण

अटल अंतरभूत व्योम dccp_hdr_set_ack(काष्ठा dccp_hdr_ack_bits *dhack,
				    स्थिर u64 gsr)
अणु
	dhack->dccph_reserved1 = 0;
	dhack->dccph_ack_nr_high = htons(gsr >> 32);
	dhack->dccph_ack_nr_low  = htonl(gsr & 0xffffffff);
पूर्ण

अटल अंतरभूत व्योम dccp_update_gsr(काष्ठा sock *sk, u64 seq)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	अगर (after48(seq, dp->dccps_gsr))
		dp->dccps_gsr = seq;
	/* Sequence validity winकरोw depends on remote Sequence Winकरोw (7.5.1) */
	dp->dccps_swl = SUB48(ADD48(dp->dccps_gsr, 1), dp->dccps_r_seq_win / 4);
	/*
	 * Adjust SWL so that it is not below ISR. In contrast to RFC 4340,
	 * 7.5.1 we perक्रमm this check beyond the initial handshake: W/W' are
	 * always > 32, so क्रम the first W/W' packets in the lअगरeसमय of a
	 * connection we always have to adjust SWL.
	 * A second reason why we are करोing this is that the winकरोw depends on
	 * the feature-remote value of Sequence Winकरोw: nothing stops the peer
	 * from updating this value जबतक we are busy adjusting SWL क्रम the
	 * first W packets (we would have to count from scratch again then).
	 * Thereक्रमe it is safer to always make sure that the Sequence Winकरोw
	 * is not artअगरicially extended by a peer who grows SWL करोwnwards by
	 * continually updating the feature-remote Sequence-Winकरोw.
	 * If sequence numbers wrap it is bad luck. But that will take a जबतक
	 * (48 bit), and this measure prevents Sequence-number attacks.
	 */
	अगर (beक्रमe48(dp->dccps_swl, dp->dccps_isr))
		dp->dccps_swl = dp->dccps_isr;
	dp->dccps_swh = ADD48(dp->dccps_gsr, (3 * dp->dccps_r_seq_win) / 4);
पूर्ण

अटल अंतरभूत व्योम dccp_update_gss(काष्ठा sock *sk, u64 seq)
अणु
	काष्ठा dccp_sock *dp = dccp_sk(sk);

	dp->dccps_gss = seq;
	/* Ack validity winकरोw depends on local Sequence Winकरोw value (7.5.1) */
	dp->dccps_awl = SUB48(ADD48(dp->dccps_gss, 1), dp->dccps_l_seq_win);
	/* Adjust AWL so that it is not below ISS - see comment above क्रम SWL */
	अगर (beक्रमe48(dp->dccps_awl, dp->dccps_iss))
		dp->dccps_awl = dp->dccps_iss;
	dp->dccps_awh = dp->dccps_gss;
पूर्ण

अटल अंतरभूत पूर्णांक dccp_ackvec_pending(स्थिर काष्ठा sock *sk)
अणु
	वापस dccp_sk(sk)->dccps_hc_rx_ackvec != शून्य &&
	       !dccp_ackvec_is_empty(dccp_sk(sk)->dccps_hc_rx_ackvec);
पूर्ण

अटल अंतरभूत पूर्णांक dccp_ack_pending(स्थिर काष्ठा sock *sk)
अणु
	वापस dccp_ackvec_pending(sk) || inet_csk_ack_scheduled(sk);
पूर्ण

पूर्णांक dccp_feat_संकेत_nn_change(काष्ठा sock *sk, u8 feat, u64 nn_val);
पूर्णांक dccp_feat_finalise_settings(काष्ठा dccp_sock *dp);
पूर्णांक dccp_feat_server_ccid_dependencies(काष्ठा dccp_request_sock *dreq);
पूर्णांक dccp_feat_insert_opts(काष्ठा dccp_sock*, काष्ठा dccp_request_sock*,
			  काष्ठा sk_buff *skb);
पूर्णांक dccp_feat_activate_values(काष्ठा sock *sk, काष्ठा list_head *fn);
व्योम dccp_feat_list_purge(काष्ठा list_head *fn_list);

पूर्णांक dccp_insert_options(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक dccp_insert_options_rsk(काष्ठा dccp_request_sock *, काष्ठा sk_buff *);
u32 dccp_बारtamp(व्योम);
व्योम dccp_बारtamping_init(व्योम);
पूर्णांक dccp_insert_option(काष्ठा sk_buff *skb, अचिन्हित अक्षर option,
		       स्थिर व्योम *value, अचिन्हित अक्षर len);

#अगर_घोषित CONFIG_SYSCTL
पूर्णांक dccp_sysctl_init(व्योम);
व्योम dccp_sysctl_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक dccp_sysctl_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dccp_sysctl_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _DCCP_H */
