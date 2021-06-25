<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel reference Implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel reference Implementation
 *
 * Various protocol defined काष्ठाures.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Or submit a bug report through the following website:
 *    http://www.sf.net/projects/lksctp
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson <karl@athena.chicago.il.us>
 *    Jon Grimm <jgrimm@us.ibm.com>
 *    Xingang Guo <xingang.guo@पूर्णांकel.com>
 *    अक्रमall@sctp.chicago.il.us
 *    kmorneau@cisco.com
 *    qxie1@email.mot.com
 *    Sridhar Samudrala <sri@us.ibm.com>
 *    Kevin Gao <kevin.gao@पूर्णांकel.com>
 *
 * Any bugs reported given to us we will try to fix... any fixes shared will
 * be incorporated पूर्णांकo the next SCTP release.
 */
#अगर_अघोषित __LINUX_SCTP_H__
#घोषणा __LINUX_SCTP_H__

#समावेश <linux/in.h>		/* We need in_addr.  */
#समावेश <linux/in6.h>		/* We need in6_addr.  */
#समावेश <linux/skbuff.h>

#समावेश <uapi/linux/sctp.h>

/* Section 3.1.  SCTP Common Header Format */
काष्ठा sctphdr अणु
	__be16 source;
	__be16 dest;
	__be32 vtag;
	__le32 checksum;
पूर्ण;

अटल अंतरभूत काष्ठा sctphdr *sctp_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा sctphdr *)skb_transport_header(skb);
पूर्ण

/* Section 3.2.  Chunk Field Descriptions. */
काष्ठा sctp_chunkhdr अणु
	__u8 type;
	__u8 flags;
	__be16 length;
पूर्ण;


/* Section 3.2.  Chunk Type Values.
 * [Chunk Type] identअगरies the type of inक्रमmation contained in the Chunk
 * Value field. It takes a value from 0 to 254. The value of 255 is
 * reserved क्रम future use as an extension field.
 */
क्रमागत sctp_cid अणु
	SCTP_CID_DATA			= 0,
        SCTP_CID_INIT			= 1,
        SCTP_CID_INIT_ACK		= 2,
        SCTP_CID_SACK			= 3,
        SCTP_CID_HEARTBEAT		= 4,
        SCTP_CID_HEARTBEAT_ACK		= 5,
        SCTP_CID_ABORT			= 6,
        SCTP_CID_SHUTDOWN		= 7,
        SCTP_CID_SHUTDOWN_ACK		= 8,
        SCTP_CID_ERROR			= 9,
        SCTP_CID_COOKIE_ECHO		= 10,
        SCTP_CID_COOKIE_ACK	        = 11,
        SCTP_CID_ECN_ECNE		= 12,
        SCTP_CID_ECN_CWR		= 13,
        SCTP_CID_SHUTDOWN_COMPLETE	= 14,

	/* AUTH Extension Section 4.1 */
	SCTP_CID_AUTH			= 0x0F,

	/* sctp ndata 5.1. I-DATA */
	SCTP_CID_I_DATA			= 0x40,

	/* PR-SCTP Sec 3.2 */
	SCTP_CID_FWD_TSN		= 0xC0,

	/* Use hex, as defined in ADDIP sec. 3.1 */
	SCTP_CID_ASCONF			= 0xC1,
	SCTP_CID_I_FWD_TSN		= 0xC2,
	SCTP_CID_ASCONF_ACK		= 0x80,
	SCTP_CID_RECONF			= 0x82,
पूर्ण; /* क्रमागत */


/* Section 3.2
 *  Chunk Types are encoded such that the highest-order two bits specअगरy
 *  the action that must be taken अगर the processing endpoपूर्णांक करोes not
 *  recognize the Chunk Type.
 */
क्रमागत अणु
	SCTP_CID_ACTION_DISCARD     = 0x00,
	SCTP_CID_ACTION_DISCARD_ERR = 0x40,
	SCTP_CID_ACTION_SKIP        = 0x80,
	SCTP_CID_ACTION_SKIP_ERR    = 0xc0,
पूर्ण;

क्रमागत अणु SCTP_CID_ACTION_MASK = 0xc0, पूर्ण;

/* This flag is used in Chunk Flags क्रम ABORT and SHUTDOWN COMPLETE.
 *
 * 3.3.7 Abort Association (ABORT) (6):
 *    The T bit is set to 0 अगर the sender had a TCB that it destroyed.
 *    If the sender did not have a TCB it should set this bit to 1.
 */
क्रमागत अणु SCTP_CHUNK_FLAG_T = 0x01 पूर्ण;

/*
 *  Set the T bit
 *
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |   Type = 14   |Reserved     |T|      Length = 4               |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Chunk Flags: 8 bits
 *
 *   Reserved:  7 bits
 *     Set to 0 on transmit and ignored on receipt.
 *
 *   T bit:  1 bit
 *     The T bit is set to 0 अगर the sender had a TCB that it destroyed. If
 *     the sender did NOT have a TCB it should set this bit to 1.
 *
 * Note: Special rules apply to this chunk क्रम verअगरication, please
 * see Section 8.5.1 क्रम details.
 */

#घोषणा sctp_test_T_bit(c)    ((c)->chunk_hdr->flags & SCTP_CHUNK_FLAG_T)

/* RFC 2960
 * Section 3.2.1 Optional/Variable-length Parmaeter Format.
 */

काष्ठा sctp_paramhdr अणु
	__be16 type;
	__be16 length;
पूर्ण;

क्रमागत sctp_param अणु

	/* RFC 2960 Section 3.3.5 */
	SCTP_PARAM_HEARTBEAT_INFO		= cpu_to_be16(1),
	/* RFC 2960 Section 3.3.2.1 */
	SCTP_PARAM_IPV4_ADDRESS			= cpu_to_be16(5),
	SCTP_PARAM_IPV6_ADDRESS			= cpu_to_be16(6),
	SCTP_PARAM_STATE_COOKIE			= cpu_to_be16(7),
	SCTP_PARAM_UNRECOGNIZED_PARAMETERS	= cpu_to_be16(8),
	SCTP_PARAM_COOKIE_PRESERVATIVE		= cpu_to_be16(9),
	SCTP_PARAM_HOST_NAME_ADDRESS		= cpu_to_be16(11),
	SCTP_PARAM_SUPPORTED_ADDRESS_TYPES	= cpu_to_be16(12),
	SCTP_PARAM_ECN_CAPABLE			= cpu_to_be16(0x8000),

	/* AUTH Extension Section 3 */
	SCTP_PARAM_RANDOM			= cpu_to_be16(0x8002),
	SCTP_PARAM_CHUNKS			= cpu_to_be16(0x8003),
	SCTP_PARAM_HMAC_ALGO			= cpu_to_be16(0x8004),

	/* Add-IP: Supported Extensions, Section 4.2 */
	SCTP_PARAM_SUPPORTED_EXT	= cpu_to_be16(0x8008),

	/* PR-SCTP Sec 3.1 */
	SCTP_PARAM_FWD_TSN_SUPPORT	= cpu_to_be16(0xc000),

	/* Add-IP Extension. Section 3.2 */
	SCTP_PARAM_ADD_IP		= cpu_to_be16(0xc001),
	SCTP_PARAM_DEL_IP		= cpu_to_be16(0xc002),
	SCTP_PARAM_ERR_CAUSE		= cpu_to_be16(0xc003),
	SCTP_PARAM_SET_PRIMARY		= cpu_to_be16(0xc004),
	SCTP_PARAM_SUCCESS_REPORT	= cpu_to_be16(0xc005),
	SCTP_PARAM_ADAPTATION_LAYER_IND = cpu_to_be16(0xc006),

	/* RE-CONFIG. Section 4 */
	SCTP_PARAM_RESET_OUT_REQUEST		= cpu_to_be16(0x000d),
	SCTP_PARAM_RESET_IN_REQUEST		= cpu_to_be16(0x000e),
	SCTP_PARAM_RESET_TSN_REQUEST		= cpu_to_be16(0x000f),
	SCTP_PARAM_RESET_RESPONSE		= cpu_to_be16(0x0010),
	SCTP_PARAM_RESET_ADD_OUT_STREAMS	= cpu_to_be16(0x0011),
	SCTP_PARAM_RESET_ADD_IN_STREAMS		= cpu_to_be16(0x0012),
पूर्ण; /* क्रमागत */


/* RFC 2960 Section 3.2.1
 *  The Parameter Types are encoded such that the highest-order two bits
 *  specअगरy the action that must be taken अगर the processing endpoपूर्णांक करोes
 *  not recognize the Parameter Type.
 *
 */
क्रमागत अणु
	SCTP_PARAM_ACTION_DISCARD     = cpu_to_be16(0x0000),
	SCTP_PARAM_ACTION_DISCARD_ERR = cpu_to_be16(0x4000),
	SCTP_PARAM_ACTION_SKIP        = cpu_to_be16(0x8000),
	SCTP_PARAM_ACTION_SKIP_ERR    = cpu_to_be16(0xc000),
पूर्ण;

क्रमागत अणु SCTP_PARAM_ACTION_MASK = cpu_to_be16(0xc000), पूर्ण;

/* RFC 2960 Section 3.3.1 Payload Data (DATA) (0) */

काष्ठा sctp_datahdr अणु
	__be32 tsn;
	__be16 stream;
	__be16 ssn;
	__u32 ppid;
	__u8  payload[];
पूर्ण;

काष्ठा sctp_data_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_datahdr data_hdr;
पूर्ण;

काष्ठा sctp_idatahdr अणु
	__be32 tsn;
	__be16 stream;
	__be16 reserved;
	__be32 mid;
	जोड़ अणु
		__u32 ppid;
		__be32 fsn;
	पूर्ण;
	__u8 payload[0];
पूर्ण;

काष्ठा sctp_idata_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_idatahdr data_hdr;
पूर्ण;

/* DATA Chuck Specअगरic Flags */
क्रमागत अणु
	SCTP_DATA_MIDDLE_FRAG	= 0x00,
	SCTP_DATA_LAST_FRAG	= 0x01,
	SCTP_DATA_FIRST_FRAG	= 0x02,
	SCTP_DATA_NOT_FRAG	= 0x03,
	SCTP_DATA_UNORDERED	= 0x04,
	SCTP_DATA_SACK_IMM	= 0x08,
पूर्ण;
क्रमागत अणु SCTP_DATA_FRAG_MASK = 0x03, पूर्ण;


/* RFC 2960 Section 3.3.2 Initiation (INIT) (1)
 *
 *  This chunk is used to initiate a SCTP association between two
 *  endpoपूर्णांकs.
 */
काष्ठा sctp_inithdr अणु
	__be32 init_tag;
	__be32 a_rwnd;
	__be16 num_outbound_streams;
	__be16 num_inbound_streams;
	__be32 initial_tsn;
	__u8  params[];
पूर्ण;

काष्ठा sctp_init_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_inithdr init_hdr;
पूर्ण;


/* Section 3.3.2.1. IPv4 Address Parameter (5) */
काष्ठा sctp_ipv4addr_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	काष्ठा in_addr addr;
पूर्ण;

/* Section 3.3.2.1. IPv6 Address Parameter (6) */
काष्ठा sctp_ipv6addr_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	काष्ठा in6_addr addr;
पूर्ण;

/* Section 3.3.2.1 Cookie Preservative (9) */
काष्ठा sctp_cookie_preserve_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 lअगरespan_increment;
पूर्ण;

/* Section 3.3.2.1 Host Name Address (11) */
काष्ठा sctp_hostname_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	uपूर्णांक8_t hostname[];
पूर्ण;

/* Section 3.3.2.1 Supported Address Types (12) */
काष्ठा sctp_supported_addrs_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be16 types[];
पूर्ण;

/* ADDIP Section 3.2.6 Adaptation Layer Indication */
काष्ठा sctp_adaptation_ind_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 adaptation_ind;
पूर्ण;

/* ADDIP Section 4.2.7 Supported Extensions Parameter */
काष्ठा sctp_supported_ext_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__u8 chunks[];
पूर्ण;

/* AUTH Section 3.1 Ranकरोm */
काष्ठा sctp_अक्रमom_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__u8 अक्रमom_val[];
पूर्ण;

/* AUTH Section 3.2 Chunk List */
काष्ठा sctp_chunks_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__u8 chunks[];
पूर्ण;

/* AUTH Section 3.3 HMAC Algorithm */
काष्ठा sctp_hmac_algo_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be16 hmac_ids[];
पूर्ण;

/* RFC 2960.  Section 3.3.3 Initiation Acknowledgement (INIT ACK) (2):
 *   The INIT ACK chunk is used to acknowledge the initiation of an SCTP
 *   association.
 */
काष्ठा sctp_initack_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_inithdr init_hdr;
पूर्ण;

/* Section 3.3.3.1 State Cookie (7) */
काष्ठा sctp_cookie_param अणु
	काष्ठा sctp_paramhdr p;
	__u8 body[];
पूर्ण;

/* Section 3.3.3.1 Unrecognized Parameters (8) */
काष्ठा sctp_unrecognized_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	काष्ठा sctp_paramhdr unrecognized;
पूर्ण;



/*
 * 3.3.4 Selective Acknowledgement (SACK) (3):
 *
 *  This chunk is sent to the peer endpoपूर्णांक to acknowledge received DATA
 *  chunks and to inक्रमm the peer endpoपूर्णांक of gaps in the received
 *  subsequences of DATA chunks as represented by their TSNs.
 */

काष्ठा sctp_gap_ack_block अणु
	__be16 start;
	__be16 end;
पूर्ण;

जोड़ sctp_sack_variable अणु
	काष्ठा sctp_gap_ack_block gab;
	__be32 dup;
पूर्ण;

काष्ठा sctp_sackhdr अणु
	__be32 cum_tsn_ack;
	__be32 a_rwnd;
	__be16 num_gap_ack_blocks;
	__be16 num_dup_tsns;
	जोड़ sctp_sack_variable variable[];
पूर्ण;

काष्ठा sctp_sack_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_sackhdr sack_hdr;
पूर्ण;


/* RFC 2960.  Section 3.3.5 Heartbeat Request (HEARTBEAT) (4):
 *
 *  An endpoपूर्णांक should send this chunk to its peer endpoपूर्णांक to probe the
 *  reachability of a particular destination transport address defined in
 *  the present association.
 */

काष्ठा sctp_heartbeathdr अणु
	काष्ठा sctp_paramhdr info;
पूर्ण;

काष्ठा sctp_heartbeat_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_heartbeathdr hb_hdr;
पूर्ण;


/* For the पात and shutकरोwn ACK we must carry the init tag in the
 * common header. Just the common header is all that is needed with a
 * chunk descriptor.
 */
काष्ठा sctp_पात_chunk अणु
	काष्ठा sctp_chunkhdr uh;
पूर्ण;


/* For the graceful shutकरोwn we must carry the tag (in common header)
 * and the highest consecutive acking value.
 */
काष्ठा sctp_shutकरोwnhdr अणु
	__be32 cum_tsn_ack;
पूर्ण;

काष्ठा sctp_shutकरोwn_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_shutकरोwnhdr shutकरोwn_hdr;
पूर्ण;

/* RFC 2960.  Section 3.3.10 Operation Error (ERROR) (9) */

काष्ठा sctp_errhdr अणु
	__be16 cause;
	__be16 length;
	__u8  variable[];
पूर्ण;

काष्ठा sctp_operr_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_errhdr err_hdr;
पूर्ण;

/* RFC 2960 3.3.10 - Operation Error
 *
 * Cause Code: 16 bits (अचिन्हित पूर्णांकeger)
 *
 *     Defines the type of error conditions being reported.
 *    Cause Code
 *     Value           Cause Code
 *     ---------      ----------------
 *      1              Invalid Stream Identअगरier
 *      2              Missing Mandatory Parameter
 *      3              Stale Cookie Error
 *      4              Out of Resource
 *      5              Unresolvable Address
 *      6              Unrecognized Chunk Type
 *      7              Invalid Mandatory Parameter
 *      8              Unrecognized Parameters
 *      9              No User Data
 *     10              Cookie Received While Shutting Down
 */
क्रमागत sctp_error अणु

	SCTP_ERROR_NO_ERROR	   = cpu_to_be16(0x00),
	SCTP_ERROR_INV_STRM	   = cpu_to_be16(0x01),
	SCTP_ERROR_MISS_PARAM 	   = cpu_to_be16(0x02),
	SCTP_ERROR_STALE_COOKIE	   = cpu_to_be16(0x03),
	SCTP_ERROR_NO_RESOURCE 	   = cpu_to_be16(0x04),
	SCTP_ERROR_DNS_FAILED      = cpu_to_be16(0x05),
	SCTP_ERROR_UNKNOWN_CHUNK   = cpu_to_be16(0x06),
	SCTP_ERROR_INV_PARAM       = cpu_to_be16(0x07),
	SCTP_ERROR_UNKNOWN_PARAM   = cpu_to_be16(0x08),
	SCTP_ERROR_NO_DATA         = cpu_to_be16(0x09),
	SCTP_ERROR_COOKIE_IN_SHUTDOWN = cpu_to_be16(0x0a),


	/* SCTP Implementation Guide:
	 *  11  Restart of an association with new addresses
	 *  12  User Initiated Abort
	 *  13  Protocol Violation
	 *  14  Restart of an Association with New Encapsulation Port
	 */

	SCTP_ERROR_RESTART         = cpu_to_be16(0x0b),
	SCTP_ERROR_USER_ABORT      = cpu_to_be16(0x0c),
	SCTP_ERROR_PROTO_VIOLATION = cpu_to_be16(0x0d),
	SCTP_ERROR_NEW_ENCAP_PORT  = cpu_to_be16(0x0e),

	/* ADDIP Section 3.3  New Error Causes
	 *
	 * Four new Error Causes are added to the SCTP Operational Errors,
	 * primarily क्रम use in the ASCONF-ACK chunk.
	 *
	 * Value          Cause Code
	 * ---------      ----------------
	 * 0x00A0          Request to Delete Last Reमुख्यing IP Address.
	 * 0x00A1          Operation Refused Due to Resource Shortage.
	 * 0x00A2          Request to Delete Source IP Address.
	 * 0x00A3          Association Aborted due to illegal ASCONF-ACK
	 * 0x00A4          Request refused - no authorization.
	 */
	SCTP_ERROR_DEL_LAST_IP	= cpu_to_be16(0x00A0),
	SCTP_ERROR_RSRC_LOW	= cpu_to_be16(0x00A1),
	SCTP_ERROR_DEL_SRC_IP	= cpu_to_be16(0x00A2),
	SCTP_ERROR_ASCONF_ACK   = cpu_to_be16(0x00A3),
	SCTP_ERROR_REQ_REFUSED	= cpu_to_be16(0x00A4),

	/* AUTH Section 4.  New Error Cause
	 *
	 * This section defines a new error cause that will be sent अगर an AUTH
	 * chunk is received with an unsupported HMAC identअगरier.
	 * illustrates the new error cause.
	 *
	 * Cause Code      Error Cause Name
	 * --------------------------------------------------------------
	 * 0x0105          Unsupported HMAC Identअगरier
	 */
	 SCTP_ERROR_UNSUP_HMAC	= cpu_to_be16(0x0105)
पूर्ण;



/* RFC 2960.  Appendix A.  Explicit Congestion Notअगरication.
 *   Explicit Congestion Notअगरication Echo (ECNE) (12)
 */
काष्ठा sctp_ecnehdr अणु
	__be32 lowest_tsn;
पूर्ण;

काष्ठा sctp_ecne_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_ecnehdr ence_hdr;
पूर्ण;

/* RFC 2960.  Appendix A.  Explicit Congestion Notअगरication.
 *   Congestion Winकरोw Reduced (CWR) (13)
 */
काष्ठा sctp_cwrhdr अणु
	__be32 lowest_tsn;
पूर्ण;

/* PR-SCTP
 * 3.2 Forward Cumulative TSN Chunk Definition (FORWARD TSN)
 *
 * Forward Cumulative TSN chunk has the following क्रमmat:
 *
 *        0                   1                   2                   3
 *        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |   Type = 192  |  Flags = 0x00 |        Length = Variable      |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |                      New Cumulative TSN                       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |         Stream-1              |       Stream Sequence-1       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      \                                                               /
 *      /                                                               \
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *      |         Stream-N              |       Stream Sequence-N       |
 *      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *      Chunk Flags:
 *
 *        Set to all zeros on transmit and ignored on receipt.
 *
 *      New Cumulative TSN: 32 bit u_पूर्णांक
 *
 *       This indicates the new cumulative TSN to the data receiver. Upon
 *       the reception of this value, the data receiver MUST consider
 *       any missing TSNs earlier than or equal to this value as received
 *       and stop reporting them as gaps in any subsequent SACKs.
 *
 *      Stream-N: 16 bit u_पूर्णांक
 *
 *       This field holds a stream number that was skipped by this
 *       FWD-TSN.
 *
 *      Stream Sequence-N: 16 bit u_पूर्णांक
 *       This field holds the sequence number associated with the stream
 *       that was skipped. The stream sequence field holds the largest stream
 *       sequence number in this stream being skipped.  The receiver of
 *       the FWD-TSN's can use the Stream-N and Stream Sequence-N fields
 *       to enable delivery of any stअक्रमed TSN's that reमुख्य on the stream
 *       re-ordering queues. This field MUST NOT report TSN's corresponding
 *       to DATA chunk that are marked as unordered. For ordered DATA
 *       chunks this field MUST be filled in.
 */
काष्ठा sctp_fwdtsn_skip अणु
	__be16 stream;
	__be16 ssn;
पूर्ण;

काष्ठा sctp_fwdtsn_hdr अणु
	__be32 new_cum_tsn;
	काष्ठा sctp_fwdtsn_skip skip[];
पूर्ण;

काष्ठा sctp_fwdtsn_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_fwdtsn_hdr fwdtsn_hdr;
पूर्ण;

काष्ठा sctp_अगरwdtsn_skip अणु
	__be16 stream;
	__u8 reserved;
	__u8 flags;
	__be32 mid;
पूर्ण;

काष्ठा sctp_अगरwdtsn_hdr अणु
	__be32 new_cum_tsn;
	काष्ठा sctp_अगरwdtsn_skip skip[];
पूर्ण;

काष्ठा sctp_अगरwdtsn_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_अगरwdtsn_hdr fwdtsn_hdr;
पूर्ण;

/* ADDIP
 * Section 3.1.1 Address Configuration Change Chunk (ASCONF)
 *
 * 	Serial Number: 32 bits (अचिन्हित पूर्णांकeger)
 *	This value represents a Serial Number क्रम the ASCONF Chunk. The
 *	valid range of Serial Number is from 0 to 2^32-1.
 *	Serial Numbers wrap back to 0 after reaching 2^32 -1.
 *
 *	Address Parameter: 8 or 20 bytes (depending on type)
 *	The address is an address of the sender of the ASCONF chunk,
 *	the address MUST be considered part of the association by the
 *	peer endpoपूर्णांक. This field may be used by the receiver of the 
 *	ASCONF to help in finding the association. This parameter MUST
 *	be present in every ASCONF message i.e. it is a mandatory TLV
 *	parameter.
 *
 *	ASCONF Parameter: TLV क्रमmat
 *	Each Address configuration change is represented by a TLV
 *	parameter as defined in Section 3.2. One or more requests may
 *	be present in an ASCONF Chunk.
 *
 * Section 3.1.2 Address Configuration Acknowledgement Chunk (ASCONF-ACK)
 * 
 *	Serial Number: 32 bits (अचिन्हित पूर्णांकeger)
 *	This value represents the Serial Number क्रम the received ASCONF
 *	Chunk that is acknowledged by this chunk. This value is copied
 *	from the received ASCONF Chunk. 
 *
 *	ASCONF Parameter Response: TLV क्रमmat
 *	The ASCONF Parameter Response is used in the ASCONF-ACK to
 *	report status of ASCONF processing.
 */
काष्ठा sctp_addip_param अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 crr_id;
पूर्ण;

काष्ठा sctp_addiphdr अणु
	__be32	serial;
	__u8	params[];
पूर्ण;

काष्ठा sctp_addip_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_addiphdr addip_hdr;
पूर्ण;

/* AUTH
 * Section 4.1  Authentication Chunk (AUTH)
 *
 *   This chunk is used to hold the result of the HMAC calculation.
 *
 *    0                   1                   2                   3
 *    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   | Type = 0x0F   |   Flags=0     |             Length            |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |     Shared Key Identअगरier     |   HMAC Identअगरier             |
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *   |                                                               |
 *   \                             HMAC                              /
 *   /                                                               \
 *   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *   Type: 1 byte (अचिन्हित पूर्णांकeger)
 *   	This value MUST be set to 0x0F क्रम  all AUTH-chunks.
 *
 *   Flags: 1 byte (अचिन्हित पूर्णांकeger)
 *	Set to zero on transmit and ignored on receipt.
 *
 *   Length: 2 bytes (अचिन्हित पूर्णांकeger)
 *   	This value holds the length of the HMAC in bytes plus 8.
 *
 *  Shared Key Identअगरier: 2 bytes (अचिन्हित पूर्णांकeger)
 *	This value describes which endpoपूर्णांक pair shared key is used.
 *
 *   HMAC Identअगरier: 2 bytes (अचिन्हित पूर्णांकeger)
 *   	This value describes which message digest is being used.  Table 2
 *	shows the currently defined values.
 *
 *    The following Table 2 shows the currently defined values क्रम HMAC
 *       identअगरiers.
 *
 *	 +-----------------+--------------------------+
 *	 | HMAC Identअगरier | Message Digest Algorithm |
 *	 +-----------------+--------------------------+
 *	 | 0               | Reserved                 |
 *	 | 1               | SHA-1 defined in [8]     |
 *	 | 2               | Reserved                 |
 *	 | 3               | SHA-256 defined in [8]   |
 *	 +-----------------+--------------------------+
 *
 *
 *   HMAC: n bytes (अचिन्हित पूर्णांकeger) This hold the result of the HMAC
 *      calculation.
 */
काष्ठा sctp_authhdr अणु
	__be16 shkey_id;
	__be16 hmac_id;
	__u8   hmac[];
पूर्ण;

काष्ठा sctp_auth_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	काष्ठा sctp_authhdr auth_hdr;
पूर्ण;

काष्ठा sctp_infox अणु
	काष्ठा sctp_info *sctpinfo;
	काष्ठा sctp_association *asoc;
पूर्ण;

काष्ठा sctp_reconf_chunk अणु
	काष्ठा sctp_chunkhdr chunk_hdr;
	__u8 params[];
पूर्ण;

काष्ठा sctp_strreset_outreq अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 request_seq;
	__be32 response_seq;
	__be32 send_reset_at_tsn;
	__be16 list_of_streams[];
पूर्ण;

काष्ठा sctp_strreset_inreq अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 request_seq;
	__be16 list_of_streams[];
पूर्ण;

काष्ठा sctp_strreset_tsnreq अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 request_seq;
पूर्ण;

काष्ठा sctp_strreset_addstrm अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 request_seq;
	__be16 number_of_streams;
	__be16 reserved;
पूर्ण;

क्रमागत अणु
	SCTP_STRRESET_NOTHING_TO_DO	= 0x00,
	SCTP_STRRESET_PERFORMED		= 0x01,
	SCTP_STRRESET_DENIED		= 0x02,
	SCTP_STRRESET_ERR_WRONG_SSN	= 0x03,
	SCTP_STRRESET_ERR_IN_PROGRESS	= 0x04,
	SCTP_STRRESET_ERR_BAD_SEQNO	= 0x05,
	SCTP_STRRESET_IN_PROGRESS	= 0x06,
पूर्ण;

काष्ठा sctp_strreset_resp अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 response_seq;
	__be32 result;
पूर्ण;

काष्ठा sctp_strreset_resptsn अणु
	काष्ठा sctp_paramhdr param_hdr;
	__be32 response_seq;
	__be32 result;
	__be32 senders_next_tsn;
	__be32 receivers_next_tsn;
पूर्ण;

क्रमागत अणु
	SCTP_DSCP_SET_MASK = 0x1,
	SCTP_DSCP_VAL_MASK = 0xfc,
	SCTP_FLOWLABEL_SET_MASK = 0x100000,
	SCTP_FLOWLABEL_VAL_MASK = 0xfffff
पूर्ण;

/* UDP Encapsulation
 * draft-tuexen-tsvwg-sctp-udp-encaps-cons-03.hपंचांगl#section-4-4
 *
 *   The error cause indicating an "Restart of an Association with
 *   New Encapsulation Port"
 *
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |        Cause Code = 14        |       Cause Length = 8        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   Current Encapsulation Port  |     New Encapsulation Port    |
 * +-------------------------------+-------------------------------+
 */
काष्ठा sctp_new_encap_port_hdr अणु
	__be16 cur_port;
	__be16 new_port;
पूर्ण;

#पूर्ण_अगर /* __LINUX_SCTP_H__ */
