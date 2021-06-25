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
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   La Monte H.P. Yarroll <piggy@acm.org>
 *   Karl Knutson          <karl@athena.chicago.il.us>
 *   Randall Stewart       <अक्रमall@stewart.chicago.il.us>
 *   Ken Morneau           <kmorneau@cisco.com>
 *   Qiaobing Xie          <qxie1@motorola.com>
 *   Xingang Guo           <xingang.guo@पूर्णांकel.com>
 *   Sridhar Samudrala     <samudrala@us.ibm.com>
 *   Daisy Chang           <daisyc@us.ibm.com>
 */

#अगर_अघोषित __sctp_स्थिरants_h__
#घोषणा __sctp_स्थिरants_h__

#समावेश <linux/sctp.h>
#समावेश <linux/ipv6.h> /* For ipv6hdr. */
#समावेश <net/tcp_states.h>  /* For TCP states used in क्रमागत sctp_sock_state */

/* Value used क्रम stream negotiation. */
क्रमागत अणु SCTP_MAX_STREAM = 0xffff पूर्ण;
क्रमागत अणु SCTP_DEFAULT_OUTSTREAMS = 10 पूर्ण;
क्रमागत अणु SCTP_DEFAULT_INSTREAMS = SCTP_MAX_STREAM पूर्ण;

/* Since CIDs are sparse, we need all four of the following
 * symbols.  CIDs are dense through SCTP_CID_BASE_MAX.
 */
#घोषणा SCTP_CID_BASE_MAX		SCTP_CID_SHUTDOWN_COMPLETE

#घोषणा SCTP_NUM_BASE_CHUNK_TYPES	(SCTP_CID_BASE_MAX + 1)

#घोषणा SCTP_NUM_ADDIP_CHUNK_TYPES	2

#घोषणा SCTP_NUM_PRSCTP_CHUNK_TYPES	1

#घोषणा SCTP_NUM_RECONF_CHUNK_TYPES	1

#घोषणा SCTP_NUM_AUTH_CHUNK_TYPES	1

#घोषणा SCTP_NUM_CHUNK_TYPES		(SCTP_NUM_BASE_CHUNK_TYPES + \
					 SCTP_NUM_ADDIP_CHUNK_TYPES +\
					 SCTP_NUM_PRSCTP_CHUNK_TYPES +\
					 SCTP_NUM_RECONF_CHUNK_TYPES +\
					 SCTP_NUM_AUTH_CHUNK_TYPES)

/* These are the dअगरferent flavours of event.  */
क्रमागत sctp_event_type अणु
	SCTP_EVENT_T_CHUNK = 1,
	SCTP_EVENT_T_TIMEOUT,
	SCTP_EVENT_T_OTHER,
	SCTP_EVENT_T_PRIMITIVE
पूर्ण;

/* As a convenience क्रम the state machine, we append SCTP_EVENT_* and
 * SCTP_ULP_* to the list of possible chunks.
 */

क्रमागत sctp_event_समयout अणु
	SCTP_EVENT_TIMEOUT_NONE = 0,
	SCTP_EVENT_TIMEOUT_T1_COOKIE,
	SCTP_EVENT_TIMEOUT_T1_INIT,
	SCTP_EVENT_TIMEOUT_T2_SHUTDOWN,
	SCTP_EVENT_TIMEOUT_T3_RTX,
	SCTP_EVENT_TIMEOUT_T4_RTO,
	SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD,
	SCTP_EVENT_TIMEOUT_HEARTBEAT,
	SCTP_EVENT_TIMEOUT_RECONF,
	SCTP_EVENT_TIMEOUT_SACK,
	SCTP_EVENT_TIMEOUT_AUTOCLOSE,
पूर्ण;

#घोषणा SCTP_EVENT_TIMEOUT_MAX		SCTP_EVENT_TIMEOUT_AUTOCLOSE
#घोषणा SCTP_NUM_TIMEOUT_TYPES		(SCTP_EVENT_TIMEOUT_MAX + 1)

क्रमागत sctp_event_other अणु
	SCTP_EVENT_NO_PENDING_TSN = 0,
	SCTP_EVENT_ICMP_PROTO_UNREACH,
पूर्ण;

#घोषणा SCTP_EVENT_OTHER_MAX		SCTP_EVENT_ICMP_PROTO_UNREACH
#घोषणा SCTP_NUM_OTHER_TYPES		(SCTP_EVENT_OTHER_MAX + 1)

/* These are primitive requests from the ULP.  */
क्रमागत sctp_event_primitive अणु
	SCTP_PRIMITIVE_ASSOCIATE = 0,
	SCTP_PRIMITIVE_SHUTDOWN,
	SCTP_PRIMITIVE_ABORT,
	SCTP_PRIMITIVE_SEND,
	SCTP_PRIMITIVE_REQUESTHEARTBEAT,
	SCTP_PRIMITIVE_ASCONF,
	SCTP_PRIMITIVE_RECONF,
पूर्ण;

#घोषणा SCTP_EVENT_PRIMITIVE_MAX	SCTP_PRIMITIVE_RECONF
#घोषणा SCTP_NUM_PRIMITIVE_TYPES	(SCTP_EVENT_PRIMITIVE_MAX + 1)

/* We define here a utility type क्रम manipulating subtypes.
 * The subtype स्थिरructors all work like this:
 *
 *   जोड़ sctp_subtype foo = SCTP_ST_CHUNK(SCTP_CID_INIT);
 */

जोड़ sctp_subtype अणु
	क्रमागत sctp_cid chunk;
	क्रमागत sctp_event_समयout समयout;
	क्रमागत sctp_event_other other;
	क्रमागत sctp_event_primitive primitive;
पूर्ण;

#घोषणा SCTP_SUBTYPE_CONSTRUCTOR(_name, _type, _elt) \
अटल अंतरभूत जोड़ sctp_subtype	\
SCTP_ST_## _name (_type _arg)		\
अणु जोड़ sctp_subtype _retval; _retval._elt = _arg; वापस _retval; पूर्ण

SCTP_SUBTYPE_CONSTRUCTOR(CHUNK,		क्रमागत sctp_cid,		chunk)
SCTP_SUBTYPE_CONSTRUCTOR(TIMEOUT,	क्रमागत sctp_event_समयout, समयout)
SCTP_SUBTYPE_CONSTRUCTOR(OTHER,		क्रमागत sctp_event_other,	other)
SCTP_SUBTYPE_CONSTRUCTOR(PRIMITIVE,	क्रमागत sctp_event_primitive, primitive)


#घोषणा sctp_chunk_is_data(a) (a->chunk_hdr->type == SCTP_CID_DATA || \
			       a->chunk_hdr->type == SCTP_CID_I_DATA)

/* Internal error codes */
क्रमागत sctp_ierror अणु
	SCTP_IERROR_NO_ERROR	        = 0,
	SCTP_IERROR_BASE		= 1000,
	SCTP_IERROR_NO_COOKIE,
	SCTP_IERROR_BAD_SIG,
	SCTP_IERROR_STALE_COOKIE,
	SCTP_IERROR_NOMEM,
	SCTP_IERROR_MALFORMED,
	SCTP_IERROR_BAD_TAG,
	SCTP_IERROR_BIG_GAP,
	SCTP_IERROR_DUP_TSN,
	SCTP_IERROR_HIGH_TSN,
	SCTP_IERROR_IGNORE_TSN,
	SCTP_IERROR_NO_DATA,
	SCTP_IERROR_BAD_STREAM,
	SCTP_IERROR_BAD_PORTS,
	SCTP_IERROR_AUTH_BAD_HMAC,
	SCTP_IERROR_AUTH_BAD_KEYID,
	SCTP_IERROR_PROTO_VIOLATION,
	SCTP_IERROR_ERROR,
	SCTP_IERROR_ABORT,
पूर्ण;



/* SCTP state defines क्रम पूर्णांकernal state machine */
क्रमागत sctp_state अणु

	SCTP_STATE_CLOSED		= 0,
	SCTP_STATE_COOKIE_WAIT		= 1,
	SCTP_STATE_COOKIE_ECHOED	= 2,
	SCTP_STATE_ESTABLISHED		= 3,
	SCTP_STATE_SHUTDOWN_PENDING	= 4,
	SCTP_STATE_SHUTDOWN_SENT	= 5,
	SCTP_STATE_SHUTDOWN_RECEIVED	= 6,
	SCTP_STATE_SHUTDOWN_ACK_SENT	= 7,

पूर्ण;

#घोषणा SCTP_STATE_MAX			SCTP_STATE_SHUTDOWN_ACK_SENT
#घोषणा SCTP_STATE_NUM_STATES		(SCTP_STATE_MAX + 1)

/* These are values क्रम sk->state.
 * For a UDP-style SCTP socket, the states are defined as follows
 * - A socket in SCTP_SS_CLOSED state indicates that it is not willing to
 *   accept new associations, but it can initiate the creation of new ones.
 * - A socket in SCTP_SS_LISTENING state indicates that it is willing to
 *   accept new  associations and can initiate the creation of new ones.
 * - A socket in SCTP_SS_ESTABLISHED state indicates that it is a peeled off
 *   socket with one association.
 * For a TCP-style SCTP socket, the states are defined as follows
 * - A socket in SCTP_SS_CLOSED state indicates that it is not willing to
 *   accept new associations, but it can initiate the creation of new ones.
 * - A socket in SCTP_SS_LISTENING state indicates that it is willing to
 *   accept new associations, but cannot initiate the creation of new ones.
 * - A socket in SCTP_SS_ESTABLISHED state indicates that it has a single 
 *   association.
 */
क्रमागत sctp_sock_state अणु
	SCTP_SS_CLOSED         = TCP_CLOSE,
	SCTP_SS_LISTENING      = TCP_LISTEN,
	SCTP_SS_ESTABLISHING   = TCP_SYN_SENT,
	SCTP_SS_ESTABLISHED    = TCP_ESTABLISHED,
	SCTP_SS_CLOSING        = TCP_CLOSE_WAIT,
पूर्ण;

/* These functions map various type to prपूर्णांकable names.  */
स्थिर अक्षर *sctp_cname(स्थिर जोड़ sctp_subtype id);	/* chunk types */
स्थिर अक्षर *sctp_oname(स्थिर जोड़ sctp_subtype id);	/* other events */
स्थिर अक्षर *sctp_tname(स्थिर जोड़ sctp_subtype id);	/* समयouts */
स्थिर अक्षर *sctp_pname(स्थिर जोड़ sctp_subtype id);	/* primitives */

/* This is a table of prपूर्णांकable names of sctp_state_t's.  */
बाह्य स्थिर अक्षर *स्थिर sctp_state_tbl[];
बाह्य स्थिर अक्षर *स्थिर sctp_evttype_tbl[];
बाह्य स्थिर अक्षर *स्थिर sctp_status_tbl[];

/* Maximum chunk length considering padding requirements. */
क्रमागत अणु SCTP_MAX_CHUNK_LEN = ((1<<16) - माप(__u32)) पूर्ण;

/* Encourage Cookie-Echo bundling by pre-fragmenting chunks a little
 * harder (until reaching ESTABLISHED state).
 */
क्रमागत अणु SCTP_ARBITRARY_COOKIE_ECHO_LEN = 200 पूर्ण;

/* Guess at how big to make the TSN mapping array.
 * We guarantee that we can handle at least this big a gap between the
 * cumulative ACK and the highest TSN.  In practice, we can often
 * handle up to twice this value.
 *
 * NEVER make this more than 32767 (2^15-1).  The Gap Ack Blocks in a
 * SACK (see  section 3.3.4) are only 16 bits, so 2*SCTP_TSN_MAP_SIZE
 * must be less than 65535 (2^16 - 1), or we will have overflow
 * problems creating SACK's.
 */
#घोषणा SCTP_TSN_MAP_INITIAL BITS_PER_LONG
#घोषणा SCTP_TSN_MAP_INCREMENT SCTP_TSN_MAP_INITIAL
#घोषणा SCTP_TSN_MAP_SIZE 4096

/* We will not record more than this many duplicate TSNs between two
 * SACKs.  The minimum PMTU is 512.  Remove all the headers and there
 * is enough room क्रम 117 duplicate reports.  Round करोwn to the
 * nearest घातer of 2.
 */
क्रमागत अणु SCTP_MAX_DUP_TSNS = 16 पूर्ण;
क्रमागत अणु SCTP_MAX_GABS = 16 पूर्ण;

/* Heartbeat पूर्णांकerval - 30 secs */
#घोषणा SCTP_DEFAULT_TIMEOUT_HEARTBEAT	(30*1000)

/* Delayed sack समयr - 200ms */
#घोषणा SCTP_DEFAULT_TIMEOUT_SACK	(200)

/* RTO.Initial              - 3  seconds
 * RTO.Min                  - 1  second
 * RTO.Max                  - 60 seconds
 * RTO.Alpha                - 1/8
 * RTO.Beta                 - 1/4
 */
#घोषणा SCTP_RTO_INITIAL	(3 * 1000)
#घोषणा SCTP_RTO_MIN		(1 * 1000)
#घोषणा SCTP_RTO_MAX		(60 * 1000)

#घोषणा SCTP_RTO_ALPHA          3   /* 1/8 when converted to right shअगरts. */
#घोषणा SCTP_RTO_BETA           2   /* 1/4 when converted to right shअगरts. */

/* Maximum number of new data packets that can be sent in a burst.  */
#घोषणा SCTP_DEFAULT_MAX_BURST		4

#घोषणा SCTP_CLOCK_GRANULARITY	1	/* 1 jअगरfy */

#घोषणा SCTP_DEFAULT_COOKIE_LIFE	(60 * 1000) /* 60 seconds */

#घोषणा SCTP_DEFAULT_MINWINDOW	1500	/* शेष minimum rwnd size */
#घोषणा SCTP_DEFAULT_MAXWINDOW	65535	/* शेष rwnd size */
#घोषणा SCTP_DEFAULT_RWND_SHIFT  4	/* by शेष, update on 1/16 of
					 * rcvbuf, which is 1/8 of initial
					 * winकरोw
					 */
#घोषणा SCTP_DEFAULT_MAXSEGMENT 1500	/* MTU size, this is the limit
                                         * to which we will उठाओ the P-MTU.
					 */
#घोषणा SCTP_DEFAULT_MINSEGMENT 512	/* MTU size ... अगर no mtu disc */

#घोषणा SCTP_SECRET_SIZE 32		/* Number of octets in a 256 bits. */

#घोषणा SCTP_SIGNATURE_SIZE 20	        /* size of a SLA-1 signature */

#घोषणा SCTP_COOKIE_MULTIPLE 32 /* Pad out our cookie to make our hash
				 * functions simpler to ग_लिखो.
				 */

#घोषणा SCTP_DEFAULT_UDP_PORT 9899	/* शेष UDP tunneling port */

/* These are the values क्रम pf exposure, UNUSED is to keep compatible with old
 * applications by शेष.
 */
क्रमागत अणु
	SCTP_PF_EXPOSE_UNSET,
	SCTP_PF_EXPOSE_DISABLE,
	SCTP_PF_EXPOSE_ENABLE,
पूर्ण;
#घोषणा SCTP_PF_EXPOSE_MAX	SCTP_PF_EXPOSE_ENABLE

#घोषणा SCTP_PS_RETRANS_MAX	0xffff

/* These वापस values describe the success or failure of a number of
 * routines which क्रमm the lower पूर्णांकerface to SCTP_outqueue.
 */
क्रमागत sctp_xmit अणु
	SCTP_XMIT_OK,
	SCTP_XMIT_PMTU_FULL,
	SCTP_XMIT_RWND_FULL,
	SCTP_XMIT_DELAY,
पूर्ण;

/* These are the commands क्रम manipulating transports.  */
क्रमागत sctp_transport_cmd अणु
	SCTP_TRANSPORT_UP,
	SCTP_TRANSPORT_DOWN,
	SCTP_TRANSPORT_PF,
पूर्ण;

/* These are the address scopes defined मुख्यly क्रम IPv4 addresses
 * based on draft of SCTP IPv4 scoping <draft-stewart-tsvwg-sctp-ipv4-00.txt>.
 * These scopes are hopefully generic enough to be used on scoping both
 * IPv4 and IPv6 addresses in SCTP.
 * At this poपूर्णांक, the IPv6 scopes will be mapped to these पूर्णांकernal scopes
 * as much as possible.
 */
क्रमागत sctp_scope अणु
	SCTP_SCOPE_GLOBAL,		/* IPv4 global addresses */
	SCTP_SCOPE_PRIVATE,		/* IPv4 निजी addresses */
	SCTP_SCOPE_LINK,		/* IPv4 link local address */
	SCTP_SCOPE_LOOPBACK,		/* IPv4 loopback address */
	SCTP_SCOPE_UNUSABLE,		/* IPv4 unusable addresses */
पूर्ण;

क्रमागत अणु
	SCTP_SCOPE_POLICY_DISABLE,	/* Disable IPv4 address scoping */
	SCTP_SCOPE_POLICY_ENABLE,	/* Enable IPv4 address scoping */
	SCTP_SCOPE_POLICY_PRIVATE,	/* Follow draft but allow IPv4 निजी addresses */
	SCTP_SCOPE_POLICY_LINK,		/* Follow draft but allow IPv4 link local addresses */
पूर्ण;

#घोषणा SCTP_SCOPE_POLICY_MAX	SCTP_SCOPE_POLICY_LINK

/* Based on IPv4 scoping <draft-stewart-tsvwg-sctp-ipv4-00.txt>,
 * SCTP IPv4 unusable addresses: 0.0.0.0/8, 224.0.0.0/4, 198.18.0.0/24,
 * 192.88.99.0/24.
 * Also, RFC 8.4, non-unicast addresses are not considered valid SCTP
 * addresses.
 */
#घोषणा IS_IPV4_UNUSABLE_ADDRESS(a)	    \
	((htonl(INADDR_BROADCAST) == a) ||  \
	 ipv4_is_multicast(a) ||	    \
	 ipv4_is_zeronet(a) ||		    \
	 ipv4_is_test_198(a) ||		    \
	 ipv4_is_anycast_6to4(a))

/* Flags used क्रम the bind address copy functions.  */
#घोषणा SCTP_ADDR4_ALLOWED	0x00000001	/* IPv4 address is allowed by
						   local sock family */
#घोषणा SCTP_ADDR6_ALLOWED	0x00000002	/* IPv6 address is allowed by
						   local sock family */
#घोषणा SCTP_ADDR4_PEERSUPP	0x00000004	/* IPv4 address is supported by
						   peer */
#घोषणा SCTP_ADDR6_PEERSUPP	0x00000008	/* IPv6 address is supported by
						   peer */

/* Reasons to retransmit. */
क्रमागत sctp_retransmit_reason अणु
	SCTP_RTXR_T3_RTX,
	SCTP_RTXR_FAST_RTX,
	SCTP_RTXR_PMTUD,
	SCTP_RTXR_T1_RTX,
पूर्ण;

/* Reasons to lower cwnd. */
क्रमागत sctp_lower_cwnd अणु
	SCTP_LOWER_CWND_T3_RTX,
	SCTP_LOWER_CWND_FAST_RTX,
	SCTP_LOWER_CWND_ECNE,
	SCTP_LOWER_CWND_INACTIVE,
पूर्ण;


/* SCTP-AUTH Necessary स्थिरants */

/* SCTP-AUTH, Section 3.3
 *
 *  The following Table 2 shows the currently defined values क्रम HMAC
 *  identअगरiers.
 *
 *  +-----------------+--------------------------+
 *  | HMAC Identअगरier | Message Digest Algorithm |
 *  +-----------------+--------------------------+
 *  | 0               | Reserved                 |
 *  | 1               | SHA-1 defined in [8]     |
 *  | 2               | Reserved                 |
 *  | 3               | SHA-256 defined in [8]   |
 *  +-----------------+--------------------------+
 */
क्रमागत अणु
	SCTP_AUTH_HMAC_ID_RESERVED_0,
	SCTP_AUTH_HMAC_ID_SHA1,
	SCTP_AUTH_HMAC_ID_RESERVED_2,
#अगर defined (CONFIG_CRYPTO_SHA256) || defined (CONFIG_CRYPTO_SHA256_MODULE)
	SCTP_AUTH_HMAC_ID_SHA256,
#पूर्ण_अगर
	__SCTP_AUTH_HMAC_MAX
पूर्ण;

#घोषणा SCTP_AUTH_HMAC_ID_MAX	__SCTP_AUTH_HMAC_MAX - 1
#घोषणा SCTP_AUTH_NUM_HMACS 	__SCTP_AUTH_HMAC_MAX
#घोषणा SCTP_SHA1_SIG_SIZE 20
#घोषणा SCTP_SHA256_SIG_SIZE 32

/*  SCTP-AUTH, Section 3.2
 *     The chunk types क्रम INIT, INIT-ACK, SHUTDOWN-COMPLETE and AUTH chunks
 *     MUST NOT be listed in the CHUNKS parameter
 */
#घोषणा SCTP_NUM_NOAUTH_CHUNKS	4
#घोषणा SCTP_AUTH_MAX_CHUNKS	(SCTP_NUM_CHUNK_TYPES - SCTP_NUM_NOAUTH_CHUNKS)

/* SCTP-AUTH Section 6.1
 * The RANDOM parameter MUST contain a 32 byte अक्रमom number.
 */
#घोषणा SCTP_AUTH_RANDOM_LENGTH 32

#पूर्ण_अगर /* __sctp_स्थिरants_h__ */
