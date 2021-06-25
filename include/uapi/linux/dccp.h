<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_DCCP_H
#घोषणा _UAPI_LINUX_DCCP_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/**
 * काष्ठा dccp_hdr - generic part of DCCP packet header
 *
 * @dccph_sport - Relevant port on the endpoपूर्णांक that sent this packet
 * @dccph_dport - Relevant port on the other endpoपूर्णांक
 * @dccph_करोff - Data Offset from the start of the DCCP header, in 32-bit words
 * @dccph_ccval - Used by the HC-Sender CCID
 * @dccph_cscov - Parts of the packet that are covered by the Checksum field
 * @dccph_checksum - Internet checksum, depends on dccph_cscov
 * @dccph_x - 0 = 24 bit sequence number, 1 = 48
 * @dccph_type - packet type, see DCCP_PKT_ prefixed macros
 * @dccph_seq - sequence number high or low order 24 bits, depends on dccph_x
 */
काष्ठा dccp_hdr अणु
	__be16	dccph_sport,
		dccph_dport;
	__u8	dccph_करोff;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	dccph_cscov:4,
		dccph_ccval:4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8	dccph_ccval:4,
		dccph_cscov:4;
#अन्यथा
#त्रुटि  "Adjust your <asm/byteorder.h> defines"
#पूर्ण_अगर
	__sum16	dccph_checksum;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	dccph_x:1,
		dccph_type:4,
		dccph_reserved:3;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8	dccph_reserved:3,
		dccph_type:4,
		dccph_x:1;
#अन्यथा
#त्रुटि  "Adjust your <asm/byteorder.h> defines"
#पूर्ण_अगर
	__u8	dccph_seq2;
	__be16	dccph_seq;
पूर्ण;

/**
 * काष्ठा dccp_hdr_ext - the low bits of a 48 bit seq packet
 *
 * @dccph_seq_low - low 24 bits of a 48 bit seq packet
 */
काष्ठा dccp_hdr_ext अणु
	__be32	dccph_seq_low;
पूर्ण;

/**
 * काष्ठा dccp_hdr_request - Connection initiation request header
 *
 * @dccph_req_service - Service to which the client app wants to connect
 */
काष्ठा dccp_hdr_request अणु
	__be32	dccph_req_service;
पूर्ण;
/**
 * काष्ठा dccp_hdr_ack_bits - acknowledgment bits common to most packets
 *
 * @dccph_resp_ack_nr_high - 48 bit ack number high order bits, contains GSR
 * @dccph_resp_ack_nr_low - 48 bit ack number low order bits, contains GSR
 */
काष्ठा dccp_hdr_ack_bits अणु
	__be16	dccph_reserved1;
	__be16	dccph_ack_nr_high;
	__be32	dccph_ack_nr_low;
पूर्ण;
/**
 * काष्ठा dccp_hdr_response - Connection initiation response header
 *
 * @dccph_resp_ack - 48 bit Acknowledgment Number Subheader (5.3)
 * @dccph_resp_service - Echoes the Service Code on a received DCCP-Request
 */
काष्ठा dccp_hdr_response अणु
	काष्ठा dccp_hdr_ack_bits	dccph_resp_ack;
	__be32				dccph_resp_service;
पूर्ण;

/**
 * काष्ठा dccp_hdr_reset - Unconditionally shut करोwn a connection
 *
 * @dccph_reset_ack - 48 bit Acknowledgment Number Subheader (5.6)
 * @dccph_reset_code - one of %dccp_reset_codes
 * @dccph_reset_data - the Data 1 ... Data 3 fields from 5.6
 */
काष्ठा dccp_hdr_reset अणु
	काष्ठा dccp_hdr_ack_bits	dccph_reset_ack;
	__u8				dccph_reset_code,
					dccph_reset_data[3];
पूर्ण;

क्रमागत dccp_pkt_type अणु
	DCCP_PKT_REQUEST = 0,
	DCCP_PKT_RESPONSE,
	DCCP_PKT_DATA,
	DCCP_PKT_ACK,
	DCCP_PKT_DATAACK,
	DCCP_PKT_CLOSEREQ,
	DCCP_PKT_CLOSE,
	DCCP_PKT_RESET,
	DCCP_PKT_SYNC,
	DCCP_PKT_SYNCACK,
	DCCP_PKT_INVALID,
पूर्ण;

#घोषणा DCCP_NR_PKT_TYPES DCCP_PKT_INVALID

अटल अंतरभूत अचिन्हित पूर्णांक dccp_packet_hdr_len(स्थिर __u8 type)
अणु
	अगर (type == DCCP_PKT_DATA)
		वापस 0;
	अगर (type == DCCP_PKT_DATAACK	||
	    type == DCCP_PKT_ACK	||
	    type == DCCP_PKT_SYNC	||
	    type == DCCP_PKT_SYNCACK	||
	    type == DCCP_PKT_CLOSE	||
	    type == DCCP_PKT_CLOSEREQ)
		वापस माप(काष्ठा dccp_hdr_ack_bits);
	अगर (type == DCCP_PKT_REQUEST)
		वापस माप(काष्ठा dccp_hdr_request);
	अगर (type == DCCP_PKT_RESPONSE)
		वापस माप(काष्ठा dccp_hdr_response);
	वापस माप(काष्ठा dccp_hdr_reset);
पूर्ण
क्रमागत dccp_reset_codes अणु
	DCCP_RESET_CODE_UNSPECIFIED = 0,
	DCCP_RESET_CODE_CLOSED,
	DCCP_RESET_CODE_ABORTED,
	DCCP_RESET_CODE_NO_CONNECTION,
	DCCP_RESET_CODE_PACKET_ERROR,
	DCCP_RESET_CODE_OPTION_ERROR,
	DCCP_RESET_CODE_MANDATORY_ERROR,
	DCCP_RESET_CODE_CONNECTION_REFUSED,
	DCCP_RESET_CODE_BAD_SERVICE_CODE,
	DCCP_RESET_CODE_TOO_BUSY,
	DCCP_RESET_CODE_BAD_INIT_COOKIE,
	DCCP_RESET_CODE_AGGRESSION_PENALTY,

	DCCP_MAX_RESET_CODES		/* Leave at the end!  */
पूर्ण;

/* DCCP options */
क्रमागत अणु
	DCCPO_PADDING = 0,
	DCCPO_MANDATORY = 1,
	DCCPO_MIN_RESERVED = 3,
	DCCPO_MAX_RESERVED = 31,
	DCCPO_CHANGE_L = 32,
	DCCPO_CONFIRM_L = 33,
	DCCPO_CHANGE_R = 34,
	DCCPO_CONFIRM_R = 35,
	DCCPO_NDP_COUNT = 37,
	DCCPO_ACK_VECTOR_0 = 38,
	DCCPO_ACK_VECTOR_1 = 39,
	DCCPO_TIMESTAMP = 41,
	DCCPO_TIMESTAMP_ECHO = 42,
	DCCPO_ELAPSED_TIME = 43,
	DCCPO_MAX = 45,
	DCCPO_MIN_RX_CCID_SPECIFIC = 128,	/* from sender to receiver */
	DCCPO_MAX_RX_CCID_SPECIFIC = 191,
	DCCPO_MIN_TX_CCID_SPECIFIC = 192,	/* from receiver to sender */
	DCCPO_MAX_TX_CCID_SPECIFIC = 255,
पूर्ण;
/* maximum size of a single TLV-encoded DCCP option (sans type/len bytes) */
#घोषणा DCCP_SINGLE_OPT_MAXLEN	253

/* DCCP CCIDS */
क्रमागत अणु
	DCCPC_CCID2 = 2,
	DCCPC_CCID3 = 3,
पूर्ण;

/* DCCP features (RFC 4340 section 6.4) */
क्रमागत dccp_feature_numbers अणु
	DCCPF_RESERVED = 0,
	DCCPF_CCID = 1,
	DCCPF_SHORT_SEQNOS = 2,
	DCCPF_SEQUENCE_WINDOW = 3,
	DCCPF_ECN_INCAPABLE = 4,
	DCCPF_ACK_RATIO = 5,
	DCCPF_SEND_ACK_VECTOR = 6,
	DCCPF_SEND_NDP_COUNT = 7,
	DCCPF_MIN_CSUM_COVER = 8,
	DCCPF_DATA_CHECKSUM = 9,
	/* 10-127 reserved */
	DCCPF_MIN_CCID_SPECIFIC = 128,
	DCCPF_SEND_LEV_RATE = 192,	/* RFC 4342, sec. 8.4 */
	DCCPF_MAX_CCID_SPECIFIC = 255,
पूर्ण;

/* DCCP socket control message types क्रम cmsg */
क्रमागत dccp_cmsg_type अणु
	DCCP_SCM_PRIORITY = 1,
	DCCP_SCM_QPOLICY_MAX = 0xFFFF,
	/* ^-- Up to here reserved exclusively क्रम qpolicy parameters */
	DCCP_SCM_MAX
पूर्ण;

/* DCCP priorities क्रम outgoing/queued packets */
क्रमागत dccp_packet_dequeueing_policy अणु
	DCCPQ_POLICY_SIMPLE,
	DCCPQ_POLICY_PRIO,
	DCCPQ_POLICY_MAX
पूर्ण;

/* DCCP socket options */
#घोषणा DCCP_SOCKOPT_PACKET_SIZE	1 /* XXX deprecated, without effect */
#घोषणा DCCP_SOCKOPT_SERVICE		2
#घोषणा DCCP_SOCKOPT_CHANGE_L		3
#घोषणा DCCP_SOCKOPT_CHANGE_R		4
#घोषणा DCCP_SOCKOPT_GET_CUR_MPS	5
#घोषणा DCCP_SOCKOPT_SERVER_TIMEWAIT	6
#घोषणा DCCP_SOCKOPT_SEND_CSCOV		10
#घोषणा DCCP_SOCKOPT_RECV_CSCOV		11
#घोषणा DCCP_SOCKOPT_AVAILABLE_CCIDS	12
#घोषणा DCCP_SOCKOPT_CCID		13
#घोषणा DCCP_SOCKOPT_TX_CCID		14
#घोषणा DCCP_SOCKOPT_RX_CCID		15
#घोषणा DCCP_SOCKOPT_QPOLICY_ID		16
#घोषणा DCCP_SOCKOPT_QPOLICY_TXQLEN	17
#घोषणा DCCP_SOCKOPT_CCID_RX_INFO	128
#घोषणा DCCP_SOCKOPT_CCID_TX_INFO	192

/* maximum number of services provided on the same listening port */
#घोषणा DCCP_SERVICE_LIST_MAX_LEN      32


#पूर्ण_अगर /* _UAPI_LINUX_DCCP_H */
