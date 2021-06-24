<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __T4_MSG_H
#घोषणा __T4_MSG_H

#समावेश <linux/types.h>

क्रमागत अणु
	CPL_PASS_OPEN_REQ     = 0x1,
	CPL_PASS_ACCEPT_RPL   = 0x2,
	CPL_ACT_OPEN_REQ      = 0x3,
	CPL_SET_TCB_FIELD     = 0x5,
	CPL_GET_TCB           = 0x6,
	CPL_CLOSE_CON_REQ     = 0x8,
	CPL_CLOSE_LISTSRV_REQ = 0x9,
	CPL_ABORT_REQ         = 0xA,
	CPL_ABORT_RPL         = 0xB,
	CPL_TX_DATA           = 0xC,
	CPL_RX_DATA_ACK       = 0xD,
	CPL_TX_PKT            = 0xE,
	CPL_L2T_WRITE_REQ     = 0x12,
	CPL_SMT_WRITE_REQ     = 0x14,
	CPL_TID_RELEASE       = 0x1A,
	CPL_SRQ_TABLE_REQ     = 0x1C,
	CPL_TX_DATA_ISO	      = 0x1F,

	CPL_CLOSE_LISTSRV_RPL = 0x20,
	CPL_GET_TCB_RPL       = 0x22,
	CPL_L2T_WRITE_RPL     = 0x23,
	CPL_PASS_OPEN_RPL     = 0x24,
	CPL_ACT_OPEN_RPL      = 0x25,
	CPL_PEER_CLOSE        = 0x26,
	CPL_ABORT_REQ_RSS     = 0x2B,
	CPL_ABORT_RPL_RSS     = 0x2D,
	CPL_SMT_WRITE_RPL     = 0x2E,

	CPL_RX_PHYS_ADDR      = 0x30,
	CPL_CLOSE_CON_RPL     = 0x32,
	CPL_ISCSI_HDR         = 0x33,
	CPL_RDMA_CQE          = 0x35,
	CPL_RDMA_CQE_READ_RSP = 0x36,
	CPL_RDMA_CQE_ERR      = 0x37,
	CPL_RX_DATA           = 0x39,
	CPL_SET_TCB_RPL       = 0x3A,
	CPL_RX_PKT            = 0x3B,
	CPL_RX_DDP_COMPLETE   = 0x3F,

	CPL_ACT_ESTABLISH     = 0x40,
	CPL_PASS_ESTABLISH    = 0x41,
	CPL_RX_DATA_DDP       = 0x42,
	CPL_PASS_ACCEPT_REQ   = 0x44,
	CPL_RX_ISCSI_CMP      = 0x45,
	CPL_TRACE_PKT_T5      = 0x48,
	CPL_RX_ISCSI_DDP      = 0x49,
	CPL_RX_TLS_CMP        = 0x4E,

	CPL_RDMA_READ_REQ     = 0x60,

	CPL_PASS_OPEN_REQ6    = 0x81,
	CPL_ACT_OPEN_REQ6     = 0x83,

	CPL_TX_TLS_PDU        = 0x88,
	CPL_TX_TLS_SFO        = 0x89,
	CPL_TX_SEC_PDU        = 0x8A,
	CPL_TX_TLS_ACK        = 0x8B,

	CPL_RDMA_TERMINATE    = 0xA2,
	CPL_RDMA_WRITE        = 0xA4,
	CPL_SGE_EGR_UPDATE    = 0xA5,
	CPL_RX_MPS_PKT        = 0xAF,

	CPL_TRACE_PKT         = 0xB0,
	CPL_TLS_DATA          = 0xB1,
	CPL_ISCSI_DATA	      = 0xB2,

	CPL_FW4_MSG           = 0xC0,
	CPL_FW4_PLD           = 0xC1,
	CPL_FW4_ACK           = 0xC3,
	CPL_SRQ_TABLE_RPL     = 0xCC,

	CPL_RX_PHYS_DSGL      = 0xD0,

	CPL_FW6_MSG           = 0xE0,
	CPL_FW6_PLD           = 0xE1,
	CPL_TX_TNL_LSO        = 0xEC,
	CPL_TX_PKT_LSO        = 0xED,
	CPL_TX_PKT_XT         = 0xEE,

	NUM_CPL_CMDS
पूर्ण;

क्रमागत CPL_error अणु
	CPL_ERR_NONE               = 0,
	CPL_ERR_TCAM_PARITY        = 1,
	CPL_ERR_TCAM_MISS          = 2,
	CPL_ERR_TCAM_FULL          = 3,
	CPL_ERR_BAD_LENGTH         = 15,
	CPL_ERR_BAD_ROUTE          = 18,
	CPL_ERR_CONN_RESET         = 20,
	CPL_ERR_CONN_EXIST_SYNRECV = 21,
	CPL_ERR_CONN_EXIST         = 22,
	CPL_ERR_ARP_MISS           = 23,
	CPL_ERR_BAD_SYN            = 24,
	CPL_ERR_CONN_TIMEDOUT      = 30,
	CPL_ERR_XMIT_TIMEDOUT      = 31,
	CPL_ERR_PERSIST_TIMEDOUT   = 32,
	CPL_ERR_FINWAIT2_TIMEDOUT  = 33,
	CPL_ERR_KEEPALIVE_TIMEDOUT = 34,
	CPL_ERR_RTX_NEG_ADVICE     = 35,
	CPL_ERR_PERSIST_NEG_ADVICE = 36,
	CPL_ERR_KEEPALV_NEG_ADVICE = 37,
	CPL_ERR_ABORT_FAILED       = 42,
	CPL_ERR_IWARP_FLM          = 50,
	CPL_CONTAINS_READ_RPL      = 60,
	CPL_CONTAINS_WRITE_RPL     = 61,
पूर्ण;

क्रमागत अणु
	CPL_CONN_POLICY_AUTO = 0,
	CPL_CONN_POLICY_ASK  = 1,
	CPL_CONN_POLICY_FILTER = 2,
	CPL_CONN_POLICY_DENY = 3
पूर्ण;

क्रमागत अणु
	ULP_MODE_NONE          = 0,
	ULP_MODE_ISCSI         = 2,
	ULP_MODE_RDMA          = 4,
	ULP_MODE_TCPDDP	       = 5,
	ULP_MODE_FCOE          = 6,
	ULP_MODE_TLS           = 8,
पूर्ण;

क्रमागत अणु
	ULP_CRC_HEADER = 1 << 0,
	ULP_CRC_DATA   = 1 << 1
पूर्ण;

क्रमागत अणु
	CPL_ABORT_SEND_RST = 0,
	CPL_ABORT_NO_RST,
पूर्ण;

क्रमागत अणु                     /* TX_PKT_XT checksum types */
	TX_CSUM_TCP    = 0,
	TX_CSUM_UDP    = 1,
	TX_CSUM_CRC16  = 4,
	TX_CSUM_CRC32  = 5,
	TX_CSUM_CRC32C = 6,
	TX_CSUM_FCOE   = 7,
	TX_CSUM_TCPIP  = 8,
	TX_CSUM_UDPIP  = 9,
	TX_CSUM_TCPIP6 = 10,
	TX_CSUM_UDPIP6 = 11,
	TX_CSUM_IP     = 12,
पूर्ण;

जोड़ opcode_tid अणु
	__be32 opcode_tid;
	u8 opcode;
पूर्ण;

#घोषणा CPL_OPCODE_S    24
#घोषणा CPL_OPCODE_V(x) ((x) << CPL_OPCODE_S)
#घोषणा CPL_OPCODE_G(x) (((x) >> CPL_OPCODE_S) & 0xFF)
#घोषणा TID_G(x)    ((x) & 0xFFFFFF)

/* tid is assumed to be 24-bits */
#घोषणा MK_OPCODE_TID(opcode, tid) (CPL_OPCODE_V(opcode) | (tid))

#घोषणा OPCODE_TID(cmd) ((cmd)->ot.opcode_tid)

/* extract the TID from a CPL command */
#घोषणा GET_TID(cmd) (TID_G(be32_to_cpu(OPCODE_TID(cmd))))

/* partitioning of TID fields that also carry a queue id */
#घोषणा TID_TID_S    0
#घोषणा TID_TID_M    0x3fff
#घोषणा TID_TID_V(x) ((x) << TID_TID_S)
#घोषणा TID_TID_G(x) (((x) >> TID_TID_S) & TID_TID_M)

#घोषणा TID_QID_S    14
#घोषणा TID_QID_M    0x3ff
#घोषणा TID_QID_V(x) ((x) << TID_QID_S)
#घोषणा TID_QID_G(x) (((x) >> TID_QID_S) & TID_QID_M)

काष्ठा rss_header अणु
	u8 opcode;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 channel:2;
	u8 filter_hit:1;
	u8 filter_tid:1;
	u8 hash_type:2;
	u8 ipv6:1;
	u8 send2fw:1;
#अन्यथा
	u8 send2fw:1;
	u8 ipv6:1;
	u8 hash_type:2;
	u8 filter_tid:1;
	u8 filter_hit:1;
	u8 channel:2;
#पूर्ण_अगर
	__be16 qid;
	__be32 hash_val;
पूर्ण;

काष्ठा work_request_hdr अणु
	__be32 wr_hi;
	__be32 wr_mid;
	__be64 wr_lo;
पूर्ण;

/* wr_hi fields */
#घोषणा WR_OP_S    24
#घोषणा WR_OP_V(x) ((__u64)(x) << WR_OP_S)

#घोषणा WR_HDR काष्ठा work_request_hdr wr

/* option 0 fields */
#घोषणा TX_CHAN_S    2
#घोषणा TX_CHAN_V(x) ((x) << TX_CHAN_S)

#घोषणा ULP_MODE_S    8
#घोषणा ULP_MODE_V(x) ((x) << ULP_MODE_S)

#घोषणा RCV_बफ_मान_S    12
#घोषणा RCV_बफ_मान_M    0x3FFU
#घोषणा RCV_बफ_मान_V(x) ((x) << RCV_बफ_मान_S)

#घोषणा SMAC_SEL_S    28
#घोषणा SMAC_SEL_V(x) ((__u64)(x) << SMAC_SEL_S)

#घोषणा L2T_IDX_S    36
#घोषणा L2T_IDX_V(x) ((__u64)(x) << L2T_IDX_S)

#घोषणा WND_SCALE_S    50
#घोषणा WND_SCALE_V(x) ((__u64)(x) << WND_SCALE_S)

#घोषणा KEEP_ALIVE_S    54
#घोषणा KEEP_ALIVE_V(x) ((__u64)(x) << KEEP_ALIVE_S)
#घोषणा KEEP_ALIVE_F    KEEP_ALIVE_V(1ULL)

#घोषणा MSS_IDX_S    60
#घोषणा MSS_IDX_M    0xF
#घोषणा MSS_IDX_V(x) ((__u64)(x) << MSS_IDX_S)
#घोषणा MSS_IDX_G(x) (((x) >> MSS_IDX_S) & MSS_IDX_M)

/* option 2 fields */
#घोषणा RSS_QUEUE_S    0
#घोषणा RSS_QUEUE_M    0x3FF
#घोषणा RSS_QUEUE_V(x) ((x) << RSS_QUEUE_S)
#घोषणा RSS_QUEUE_G(x) (((x) >> RSS_QUEUE_S) & RSS_QUEUE_M)

#घोषणा RSS_QUEUE_VALID_S    10
#घोषणा RSS_QUEUE_VALID_V(x) ((x) << RSS_QUEUE_VALID_S)
#घोषणा RSS_QUEUE_VALID_F    RSS_QUEUE_VALID_V(1U)

#घोषणा RX_FC_DISABLE_S    20
#घोषणा RX_FC_DISABLE_V(x) ((x) << RX_FC_DISABLE_S)
#घोषणा RX_FC_DISABLE_F    RX_FC_DISABLE_V(1U)

#घोषणा RX_FC_VALID_S    22
#घोषणा RX_FC_VALID_V(x) ((x) << RX_FC_VALID_S)
#घोषणा RX_FC_VALID_F    RX_FC_VALID_V(1U)

#घोषणा RX_CHANNEL_S    26
#घोषणा RX_CHANNEL_V(x) ((x) << RX_CHANNEL_S)
#घोषणा RX_CHANNEL_F	RX_CHANNEL_V(1U)

#घोषणा WND_SCALE_EN_S    28
#घोषणा WND_SCALE_EN_V(x) ((x) << WND_SCALE_EN_S)
#घोषणा WND_SCALE_EN_F    WND_SCALE_EN_V(1U)

#घोषणा T5_OPT_2_VALID_S    31
#घोषणा T5_OPT_2_VALID_V(x) ((x) << T5_OPT_2_VALID_S)
#घोषणा T5_OPT_2_VALID_F    T5_OPT_2_VALID_V(1U)

काष्ठा cpl_pass_खोलो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be64 opt0;
	__be64 opt1;
पूर्ण;

/* option 0 fields */
#घोषणा NO_CONG_S    4
#घोषणा NO_CONG_V(x) ((x) << NO_CONG_S)
#घोषणा NO_CONG_F    NO_CONG_V(1U)

#घोषणा DELACK_S    5
#घोषणा DELACK_V(x) ((x) << DELACK_S)
#घोषणा DELACK_F    DELACK_V(1U)

#घोषणा NON_OFFLOAD_S		7
#घोषणा NON_OFFLOAD_V(x)	((x) << NON_OFFLOAD_S)
#घोषणा NON_OFFLOAD_F		NON_OFFLOAD_V(1U)

#घोषणा DSCP_S    22
#घोषणा DSCP_M    0x3F
#घोषणा DSCP_V(x) ((x) << DSCP_S)
#घोषणा DSCP_G(x) (((x) >> DSCP_S) & DSCP_M)

#घोषणा TCAM_BYPASS_S    48
#घोषणा TCAM_BYPASS_V(x) ((__u64)(x) << TCAM_BYPASS_S)
#घोषणा TCAM_BYPASS_F    TCAM_BYPASS_V(1ULL)

#घोषणा NAGLE_S    49
#घोषणा NAGLE_V(x) ((__u64)(x) << NAGLE_S)
#घोषणा NAGLE_F    NAGLE_V(1ULL)

/* option 1 fields */
#घोषणा SYN_RSS_ENABLE_S    0
#घोषणा SYN_RSS_ENABLE_V(x) ((x) << SYN_RSS_ENABLE_S)
#घोषणा SYN_RSS_ENABLE_F    SYN_RSS_ENABLE_V(1U)

#घोषणा SYN_RSS_QUEUE_S    2
#घोषणा SYN_RSS_QUEUE_V(x) ((x) << SYN_RSS_QUEUE_S)

#घोषणा CONN_POLICY_S    22
#घोषणा CONN_POLICY_V(x) ((x) << CONN_POLICY_S)

काष्ठा cpl_pass_खोलो_req6 अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be64 local_ip_hi;
	__be64 local_ip_lo;
	__be64 peer_ip_hi;
	__be64 peer_ip_lo;
	__be64 opt0;
	__be64 opt1;
पूर्ण;

काष्ठा cpl_pass_खोलो_rpl अणु
	जोड़ opcode_tid ot;
	u8 rsvd[3];
	u8 status;
पूर्ण;

काष्ठा tcp_options अणु
	__be16 mss;
	__u8 wsf;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8:4;
	__u8 unknown:1;
	__u8:1;
	__u8 sack:1;
	__u8 tstamp:1;
#अन्यथा
	__u8 tstamp:1;
	__u8 sack:1;
	__u8:1;
	__u8 unknown:1;
	__u8:4;
#पूर्ण_अगर
पूर्ण;

काष्ठा cpl_pass_accept_req अणु
	जोड़ opcode_tid ot;
	__be16 rsvd;
	__be16 len;
	__be32 hdr_len;
	__be16 vlan;
	__be16 l2info;
	__be32 tos_stid;
	काष्ठा tcp_options tcpopt;
पूर्ण;

/* cpl_pass_accept_req.hdr_len fields */
#घोषणा SYN_RX_CHAN_S    0
#घोषणा SYN_RX_CHAN_M    0xF
#घोषणा SYN_RX_CHAN_V(x) ((x) << SYN_RX_CHAN_S)
#घोषणा SYN_RX_CHAN_G(x) (((x) >> SYN_RX_CHAN_S) & SYN_RX_CHAN_M)

#घोषणा TCP_HDR_LEN_S    10
#घोषणा TCP_HDR_LEN_M    0x3F
#घोषणा TCP_HDR_LEN_V(x) ((x) << TCP_HDR_LEN_S)
#घोषणा TCP_HDR_LEN_G(x) (((x) >> TCP_HDR_LEN_S) & TCP_HDR_LEN_M)

#घोषणा IP_HDR_LEN_S    16
#घोषणा IP_HDR_LEN_M    0x3FF
#घोषणा IP_HDR_LEN_V(x) ((x) << IP_HDR_LEN_S)
#घोषणा IP_HDR_LEN_G(x) (((x) >> IP_HDR_LEN_S) & IP_HDR_LEN_M)

#घोषणा ETH_HDR_LEN_S    26
#घोषणा ETH_HDR_LEN_M    0x1F
#घोषणा ETH_HDR_LEN_V(x) ((x) << ETH_HDR_LEN_S)
#घोषणा ETH_HDR_LEN_G(x) (((x) >> ETH_HDR_LEN_S) & ETH_HDR_LEN_M)

/* cpl_pass_accept_req.l2info fields */
#घोषणा SYN_MAC_IDX_S    0
#घोषणा SYN_MAC_IDX_M    0x1FF
#घोषणा SYN_MAC_IDX_V(x) ((x) << SYN_MAC_IDX_S)
#घोषणा SYN_MAC_IDX_G(x) (((x) >> SYN_MAC_IDX_S) & SYN_MAC_IDX_M)

#घोषणा SYN_XACT_MATCH_S    9
#घोषणा SYN_XACT_MATCH_V(x) ((x) << SYN_XACT_MATCH_S)
#घोषणा SYN_XACT_MATCH_F    SYN_XACT_MATCH_V(1U)

#घोषणा SYN_INTF_S    12
#घोषणा SYN_INTF_M    0xF
#घोषणा SYN_INTF_V(x) ((x) << SYN_INTF_S)
#घोषणा SYN_INTF_G(x) (((x) >> SYN_INTF_S) & SYN_INTF_M)

क्रमागत अणु                     /* TCP congestion control algorithms */
	CONG_ALG_RENO,
	CONG_ALG_TAHOE,
	CONG_ALG_NEWRENO,
	CONG_ALG_HIGHSPEED
पूर्ण;

#घोषणा CONG_CNTRL_S    14
#घोषणा CONG_CNTRL_M    0x3
#घोषणा CONG_CNTRL_V(x) ((x) << CONG_CNTRL_S)
#घोषणा CONG_CNTRL_G(x) (((x) >> CONG_CNTRL_S) & CONG_CNTRL_M)

#घोषणा T5_ISS_S    18
#घोषणा T5_ISS_V(x) ((x) << T5_ISS_S)
#घोषणा T5_ISS_F    T5_ISS_V(1U)

काष्ठा cpl_pass_accept_rpl अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 opt2;
	__be64 opt0;
पूर्ण;

/* option 2 fields */
#घोषणा RX_COALESCE_VALID_S    11
#घोषणा RX_COALESCE_VALID_V(x) ((x) << RX_COALESCE_VALID_S)
#घोषणा RX_COALESCE_VALID_F    RX_COALESCE_VALID_V(1U)

#घोषणा RX_COALESCE_S    12
#घोषणा RX_COALESCE_V(x) ((x) << RX_COALESCE_S)

#घोषणा PACE_S    16
#घोषणा PACE_V(x) ((x) << PACE_S)

#घोषणा TX_QUEUE_S    23
#घोषणा TX_QUEUE_M    0x7
#घोषणा TX_QUEUE_V(x) ((x) << TX_QUEUE_S)
#घोषणा TX_QUEUE_G(x) (((x) >> TX_QUEUE_S) & TX_QUEUE_M)

#घोषणा CCTRL_ECN_S    27
#घोषणा CCTRL_ECN_V(x) ((x) << CCTRL_ECN_S)
#घोषणा CCTRL_ECN_F    CCTRL_ECN_V(1U)

#घोषणा TSTAMPS_EN_S    29
#घोषणा TSTAMPS_EN_V(x) ((x) << TSTAMPS_EN_S)
#घोषणा TSTAMPS_EN_F    TSTAMPS_EN_V(1U)

#घोषणा SACK_EN_S    30
#घोषणा SACK_EN_V(x) ((x) << SACK_EN_S)
#घोषणा SACK_EN_F    SACK_EN_V(1U)

काष्ठा cpl_t5_pass_accept_rpl अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 opt2;
	__be64 opt0;
	__be32 iss;
	__be32 rsvd;
पूर्ण;

काष्ठा cpl_act_खोलो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be64 opt0;
	__be32 params;
	__be32 opt2;
पूर्ण;

#घोषणा FILTER_TUPLE_S  24
#घोषणा FILTER_TUPLE_M  0xFFFFFFFFFF
#घोषणा FILTER_TUPLE_V(x) ((x) << FILTER_TUPLE_S)
#घोषणा FILTER_TUPLE_G(x) (((x) >> FILTER_TUPLE_S) & FILTER_TUPLE_M)
काष्ठा cpl_t5_act_खोलो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be64 opt0;
	__be32 rsvd;
	__be32 opt2;
	__be64 params;
पूर्ण;

काष्ठा cpl_t6_act_खोलो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be32 local_ip;
	__be32 peer_ip;
	__be64 opt0;
	__be32 rsvd;
	__be32 opt2;
	__be64 params;
	__be32 rsvd2;
	__be32 opt3;
पूर्ण;

काष्ठा cpl_act_खोलो_req6 अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be64 local_ip_hi;
	__be64 local_ip_lo;
	__be64 peer_ip_hi;
	__be64 peer_ip_lo;
	__be64 opt0;
	__be32 params;
	__be32 opt2;
पूर्ण;

काष्ठा cpl_t5_act_खोलो_req6 अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be64 local_ip_hi;
	__be64 local_ip_lo;
	__be64 peer_ip_hi;
	__be64 peer_ip_lo;
	__be64 opt0;
	__be32 rsvd;
	__be32 opt2;
	__be64 params;
पूर्ण;

काष्ठा cpl_t6_act_खोलो_req6 अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 local_port;
	__be16 peer_port;
	__be64 local_ip_hi;
	__be64 local_ip_lo;
	__be64 peer_ip_hi;
	__be64 peer_ip_lo;
	__be64 opt0;
	__be32 rsvd;
	__be32 opt2;
	__be64 params;
	__be32 rsvd2;
	__be32 opt3;
पूर्ण;

काष्ठा cpl_act_खोलो_rpl अणु
	जोड़ opcode_tid ot;
	__be32 atid_status;
पूर्ण;

/* cpl_act_खोलो_rpl.atid_status fields */
#घोषणा AOPEN_STATUS_S    0
#घोषणा AOPEN_STATUS_M    0xFF
#घोषणा AOPEN_STATUS_G(x) (((x) >> AOPEN_STATUS_S) & AOPEN_STATUS_M)

#घोषणा AOPEN_ATID_S    8
#घोषणा AOPEN_ATID_M    0xFFFFFF
#घोषणा AOPEN_ATID_G(x) (((x) >> AOPEN_ATID_S) & AOPEN_ATID_M)

काष्ठा cpl_pass_establish अणु
	जोड़ opcode_tid ot;
	__be32 rsvd;
	__be32 tos_stid;
	__be16 mac_idx;
	__be16 tcp_opt;
	__be32 snd_isn;
	__be32 rcv_isn;
पूर्ण;

/* cpl_pass_establish.tos_stid fields */
#घोषणा PASS_OPEN_TID_S    0
#घोषणा PASS_OPEN_TID_M    0xFFFFFF
#घोषणा PASS_OPEN_TID_V(x) ((x) << PASS_OPEN_TID_S)
#घोषणा PASS_OPEN_TID_G(x) (((x) >> PASS_OPEN_TID_S) & PASS_OPEN_TID_M)

#घोषणा PASS_OPEN_TOS_S    24
#घोषणा PASS_OPEN_TOS_M    0xFF
#घोषणा PASS_OPEN_TOS_V(x) ((x) << PASS_OPEN_TOS_S)
#घोषणा PASS_OPEN_TOS_G(x) (((x) >> PASS_OPEN_TOS_S) & PASS_OPEN_TOS_M)

/* cpl_pass_establish.tcp_opt fields (also applies to act_खोलो_establish) */
#घोषणा TCPOPT_WSCALE_OK_S	5
#घोषणा TCPOPT_WSCALE_OK_M	0x1
#घोषणा TCPOPT_WSCALE_OK_G(x)	\
	(((x) >> TCPOPT_WSCALE_OK_S) & TCPOPT_WSCALE_OK_M)

#घोषणा TCPOPT_SACK_S		6
#घोषणा TCPOPT_SACK_M		0x1
#घोषणा TCPOPT_SACK_G(x)	(((x) >> TCPOPT_SACK_S) & TCPOPT_SACK_M)

#घोषणा TCPOPT_TSTAMP_S		7
#घोषणा TCPOPT_TSTAMP_M		0x1
#घोषणा TCPOPT_TSTAMP_G(x)	(((x) >> TCPOPT_TSTAMP_S) & TCPOPT_TSTAMP_M)

#घोषणा TCPOPT_SND_WSCALE_S	8
#घोषणा TCPOPT_SND_WSCALE_M	0xF
#घोषणा TCPOPT_SND_WSCALE_G(x)	\
	(((x) >> TCPOPT_SND_WSCALE_S) & TCPOPT_SND_WSCALE_M)

#घोषणा TCPOPT_MSS_S	12
#घोषणा TCPOPT_MSS_M	0xF
#घोषणा TCPOPT_MSS_G(x)	(((x) >> TCPOPT_MSS_S) & TCPOPT_MSS_M)

#घोषणा T6_TCP_HDR_LEN_S   8
#घोषणा T6_TCP_HDR_LEN_V(x) ((x) << T6_TCP_HDR_LEN_S)
#घोषणा T6_TCP_HDR_LEN_G(x) (((x) >> T6_TCP_HDR_LEN_S) & TCP_HDR_LEN_M)

#घोषणा T6_IP_HDR_LEN_S    14
#घोषणा T6_IP_HDR_LEN_V(x) ((x) << T6_IP_HDR_LEN_S)
#घोषणा T6_IP_HDR_LEN_G(x) (((x) >> T6_IP_HDR_LEN_S) & IP_HDR_LEN_M)

#घोषणा T6_ETH_HDR_LEN_S    24
#घोषणा T6_ETH_HDR_LEN_M    0xFF
#घोषणा T6_ETH_HDR_LEN_V(x) ((x) << T6_ETH_HDR_LEN_S)
#घोषणा T6_ETH_HDR_LEN_G(x) (((x) >> T6_ETH_HDR_LEN_S) & T6_ETH_HDR_LEN_M)

काष्ठा cpl_act_establish अणु
	जोड़ opcode_tid ot;
	__be32 rsvd;
	__be32 tos_atid;
	__be16 mac_idx;
	__be16 tcp_opt;
	__be32 snd_isn;
	__be32 rcv_isn;
पूर्ण;

काष्ठा cpl_get_tcb अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 reply_ctrl;
	__be16 cookie;
पूर्ण;

/* cpl_get_tcb.reply_ctrl fields */
#घोषणा QUEUENO_S    0
#घोषणा QUEUENO_V(x) ((x) << QUEUENO_S)

#घोषणा REPLY_CHAN_S    14
#घोषणा REPLY_CHAN_V(x) ((x) << REPLY_CHAN_S)
#घोषणा REPLY_CHAN_F    REPLY_CHAN_V(1U)

#घोषणा NO_REPLY_S    15
#घोषणा NO_REPLY_V(x) ((x) << NO_REPLY_S)
#घोषणा NO_REPLY_F    NO_REPLY_V(1U)

काष्ठा cpl_get_tcb_rpl अणु
	जोड़ opcode_tid ot;
	__u8 cookie;
	__u8 status;
	__be16 len;
पूर्ण;

काष्ठा cpl_set_tcb_field अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 reply_ctrl;
	__be16 word_cookie;
	__be64 mask;
	__be64 val;
पूर्ण;

काष्ठा cpl_set_tcb_field_core अणु
	जोड़ opcode_tid ot;
	__be16 reply_ctrl;
	__be16 word_cookie;
	__be64 mask;
	__be64 val;
पूर्ण;

/* cpl_set_tcb_field.word_cookie fields */
#घोषणा TCB_WORD_S	0
#घोषणा TCB_WORD_V(x)	((x) << TCB_WORD_S)

#घोषणा TCB_COOKIE_S    5
#घोषणा TCB_COOKIE_M    0x7
#घोषणा TCB_COOKIE_V(x) ((x) << TCB_COOKIE_S)
#घोषणा TCB_COOKIE_G(x) (((x) >> TCB_COOKIE_S) & TCB_COOKIE_M)

काष्ठा cpl_set_tcb_rpl अणु
	जोड़ opcode_tid ot;
	__be16 rsvd;
	u8 cookie;
	u8 status;
	__be64 oldval;
पूर्ण;

काष्ठा cpl_बंद_con_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd;
पूर्ण;

काष्ठा cpl_बंद_con_rpl अणु
	जोड़ opcode_tid ot;
	u8 rsvd[3];
	u8 status;
	__be32 snd_nxt;
	__be32 rcv_nxt;
पूर्ण;

काष्ठा cpl_बंद_listsvr_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 reply_ctrl;
	__be16 rsvd;
पूर्ण;

/* additional cpl_बंद_listsvr_req.reply_ctrl field */
#घोषणा LISTSVR_IPV6_S    14
#घोषणा LISTSVR_IPV6_V(x) ((x) << LISTSVR_IPV6_S)
#घोषणा LISTSVR_IPV6_F    LISTSVR_IPV6_V(1U)

काष्ठा cpl_बंद_listsvr_rpl अणु
	जोड़ opcode_tid ot;
	u8 rsvd[3];
	u8 status;
पूर्ण;

काष्ठा cpl_पात_req_rss अणु
	जोड़ opcode_tid ot;
	u8 rsvd[3];
	u8 status;
पूर्ण;

काष्ठा cpl_पात_req_rss6 अणु
	जोड़ opcode_tid ot;
	__be32 srqidx_status;
पूर्ण;

#घोषणा ABORT_RSS_STATUS_S    0
#घोषणा ABORT_RSS_STATUS_M    0xff
#घोषणा ABORT_RSS_STATUS_V(x) ((x) << ABORT_RSS_STATUS_S)
#घोषणा ABORT_RSS_STATUS_G(x) (((x) >> ABORT_RSS_STATUS_S) & ABORT_RSS_STATUS_M)

#घोषणा ABORT_RSS_SRQIDX_S    8
#घोषणा ABORT_RSS_SRQIDX_M    0xffffff
#घोषणा ABORT_RSS_SRQIDX_V(x) ((x) << ABORT_RSS_SRQIDX_S)
#घोषणा ABORT_RSS_SRQIDX_G(x) (((x) >> ABORT_RSS_SRQIDX_S) & ABORT_RSS_SRQIDX_M)

काष्ठा cpl_पात_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd0;
	u8 rsvd1;
	u8 cmd;
	u8 rsvd2[6];
पूर्ण;

काष्ठा cpl_पात_rpl_rss अणु
	जोड़ opcode_tid ot;
	u8 rsvd[3];
	u8 status;
पूर्ण;

काष्ठा cpl_पात_rpl_rss6 अणु
	जोड़ opcode_tid ot;
	__be32 srqidx_status;
पूर्ण;

काष्ठा cpl_पात_rpl अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd0;
	u8 rsvd1;
	u8 cmd;
	u8 rsvd2[6];
पूर्ण;

काष्ठा cpl_peer_बंद अणु
	जोड़ opcode_tid ot;
	__be32 rcv_nxt;
पूर्ण;

काष्ठा cpl_tid_release अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 rsvd;
पूर्ण;

काष्ठा cpl_tx_pkt_core अणु
	__be32 ctrl0;
	__be16 pack;
	__be16 len;
	__be64 ctrl1;
पूर्ण;

काष्ठा cpl_tx_pkt अणु
	WR_HDR;
	काष्ठा cpl_tx_pkt_core c;
पूर्ण;

#घोषणा cpl_tx_pkt_xt cpl_tx_pkt

/* cpl_tx_pkt_core.ctrl0 fields */
#घोषणा TXPKT_VF_S    0
#घोषणा TXPKT_VF_V(x) ((x) << TXPKT_VF_S)

#घोषणा TXPKT_PF_S    8
#घोषणा TXPKT_PF_V(x) ((x) << TXPKT_PF_S)

#घोषणा TXPKT_VF_VLD_S    11
#घोषणा TXPKT_VF_VLD_V(x) ((x) << TXPKT_VF_VLD_S)
#घोषणा TXPKT_VF_VLD_F    TXPKT_VF_VLD_V(1U)

#घोषणा TXPKT_OVLAN_IDX_S    12
#घोषणा TXPKT_OVLAN_IDX_V(x) ((x) << TXPKT_OVLAN_IDX_S)

#घोषणा TXPKT_T5_OVLAN_IDX_S	12
#घोषणा TXPKT_T5_OVLAN_IDX_V(x)	((x) << TXPKT_T5_OVLAN_IDX_S)

#घोषणा TXPKT_INTF_S    16
#घोषणा TXPKT_INTF_V(x) ((x) << TXPKT_INTF_S)

#घोषणा TXPKT_INS_OVLAN_S    21
#घोषणा TXPKT_INS_OVLAN_V(x) ((x) << TXPKT_INS_OVLAN_S)
#घोषणा TXPKT_INS_OVLAN_F    TXPKT_INS_OVLAN_V(1U)

#घोषणा TXPKT_TSTAMP_S    23
#घोषणा TXPKT_TSTAMP_V(x) ((x) << TXPKT_TSTAMP_S)
#घोषणा TXPKT_TSTAMP_F    TXPKT_TSTAMP_V(1ULL)

#घोषणा TXPKT_OPCODE_S    24
#घोषणा TXPKT_OPCODE_V(x) ((x) << TXPKT_OPCODE_S)

/* cpl_tx_pkt_core.ctrl1 fields */
#घोषणा TXPKT_CSUM_END_S    12
#घोषणा TXPKT_CSUM_END_V(x) ((x) << TXPKT_CSUM_END_S)

#घोषणा TXPKT_CSUM_START_S    20
#घोषणा TXPKT_CSUM_START_V(x) ((x) << TXPKT_CSUM_START_S)

#घोषणा TXPKT_IPHDR_LEN_S    20
#घोषणा TXPKT_IPHDR_LEN_V(x) ((__u64)(x) << TXPKT_IPHDR_LEN_S)

#घोषणा TXPKT_CSUM_LOC_S    30
#घोषणा TXPKT_CSUM_LOC_V(x) ((__u64)(x) << TXPKT_CSUM_LOC_S)

#घोषणा TXPKT_ETHHDR_LEN_S    34
#घोषणा TXPKT_ETHHDR_LEN_V(x) ((__u64)(x) << TXPKT_ETHHDR_LEN_S)

#घोषणा T6_TXPKT_ETHHDR_LEN_S    32
#घोषणा T6_TXPKT_ETHHDR_LEN_V(x) ((__u64)(x) << T6_TXPKT_ETHHDR_LEN_S)

#घोषणा TXPKT_CSUM_TYPE_S    40
#घोषणा TXPKT_CSUM_TYPE_V(x) ((__u64)(x) << TXPKT_CSUM_TYPE_S)

#घोषणा TXPKT_VLAN_S    44
#घोषणा TXPKT_VLAN_V(x) ((__u64)(x) << TXPKT_VLAN_S)

#घोषणा TXPKT_VLAN_VLD_S    60
#घोषणा TXPKT_VLAN_VLD_V(x) ((__u64)(x) << TXPKT_VLAN_VLD_S)
#घोषणा TXPKT_VLAN_VLD_F    TXPKT_VLAN_VLD_V(1ULL)

#घोषणा TXPKT_IPCSUM_DIS_S    62
#घोषणा TXPKT_IPCSUM_DIS_V(x) ((__u64)(x) << TXPKT_IPCSUM_DIS_S)
#घोषणा TXPKT_IPCSUM_DIS_F    TXPKT_IPCSUM_DIS_V(1ULL)

#घोषणा TXPKT_L4CSUM_DIS_S    63
#घोषणा TXPKT_L4CSUM_DIS_V(x) ((__u64)(x) << TXPKT_L4CSUM_DIS_S)
#घोषणा TXPKT_L4CSUM_DIS_F    TXPKT_L4CSUM_DIS_V(1ULL)

काष्ठा cpl_tx_pkt_lso_core अणु
	__be32 lso_ctrl;
	__be16 ipid_ofst;
	__be16 mss;
	__be32 seqno_offset;
	__be32 len;
	/* encapsulated CPL (TX_PKT, TX_PKT_XT or TX_DATA) follows here */
पूर्ण;

/* cpl_tx_pkt_lso_core.lso_ctrl fields */
#घोषणा LSO_TCPHDR_LEN_S    0
#घोषणा LSO_TCPHDR_LEN_V(x) ((x) << LSO_TCPHDR_LEN_S)

#घोषणा LSO_IPHDR_LEN_S    4
#घोषणा LSO_IPHDR_LEN_V(x) ((x) << LSO_IPHDR_LEN_S)

#घोषणा LSO_ETHHDR_LEN_S    16
#घोषणा LSO_ETHHDR_LEN_V(x) ((x) << LSO_ETHHDR_LEN_S)

#घोषणा LSO_IPV6_S    20
#घोषणा LSO_IPV6_V(x) ((x) << LSO_IPV6_S)
#घोषणा LSO_IPV6_F    LSO_IPV6_V(1U)

#घोषणा LSO_LAST_SLICE_S    22
#घोषणा LSO_LAST_SLICE_V(x) ((x) << LSO_LAST_SLICE_S)
#घोषणा LSO_LAST_SLICE_F    LSO_LAST_SLICE_V(1U)

#घोषणा LSO_FIRST_SLICE_S    23
#घोषणा LSO_FIRST_SLICE_V(x) ((x) << LSO_FIRST_SLICE_S)
#घोषणा LSO_FIRST_SLICE_F    LSO_FIRST_SLICE_V(1U)

#घोषणा LSO_OPCODE_S    24
#घोषणा LSO_OPCODE_V(x) ((x) << LSO_OPCODE_S)

#घोषणा LSO_T5_XFER_SIZE_S	   0
#घोषणा LSO_T5_XFER_SIZE_V(x) ((x) << LSO_T5_XFER_SIZE_S)

काष्ठा cpl_tx_pkt_lso अणु
	WR_HDR;
	काष्ठा cpl_tx_pkt_lso_core c;
	/* encapsulated CPL (TX_PKT, TX_PKT_XT or TX_DATA) follows here */
पूर्ण;

काष्ठा cpl_iscsi_hdr अणु
	जोड़ opcode_tid ot;
	__be16 pdu_len_ddp;
	__be16 len;
	__be32 seq;
	__be16 urg;
	u8 rsvd;
	u8 status;
पूर्ण;

/* cpl_iscsi_hdr.pdu_len_ddp fields */
#घोषणा ISCSI_PDU_LEN_S    0
#घोषणा ISCSI_PDU_LEN_M    0x7FFF
#घोषणा ISCSI_PDU_LEN_V(x) ((x) << ISCSI_PDU_LEN_S)
#घोषणा ISCSI_PDU_LEN_G(x) (((x) >> ISCSI_PDU_LEN_S) & ISCSI_PDU_LEN_M)

#घोषणा ISCSI_DDP_S    15
#घोषणा ISCSI_DDP_V(x) ((x) << ISCSI_DDP_S)
#घोषणा ISCSI_DDP_F    ISCSI_DDP_V(1U)

काष्ठा cpl_rx_data_ddp अणु
	जोड़ opcode_tid ot;
	__be16 urg;
	__be16 len;
	__be32 seq;
	जोड़ अणु
		__be32 nxt_seq;
		__be32 ddp_report;
	पूर्ण;
	__be32 ulp_crc;
	__be32 ddpvld;
पूर्ण;

#घोषणा cpl_rx_iscsi_ddp cpl_rx_data_ddp

काष्ठा cpl_iscsi_data अणु
	जोड़ opcode_tid ot;
	__u8 rsvd0[2];
	__be16 len;
	__be32 seq;
	__be16 urg;
	__u8 rsvd1;
	__u8 status;
पूर्ण;

काष्ठा cpl_rx_iscsi_cmp अणु
	जोड़ opcode_tid ot;
	__be16 pdu_len_ddp;
	__be16 len;
	__be32 seq;
	__be16 urg;
	__u8 rsvd;
	__u8 status;
	__be32 ulp_crc;
	__be32 ddpvld;
पूर्ण;

काष्ठा cpl_tx_data_iso अणु
	__be32 op_to_scsi;
	__u8   reserved1;
	__u8   ahs_len;
	__be16 mpdu;
	__be32 burst_size;
	__be32 len;
	__be32 reserved2_seglen_offset;
	__be32 datasn_offset;
	__be32 buffer_offset;
	__be32 reserved3;

	/* encapsulated CPL_TX_DATA follows here */
पूर्ण;

/* cpl_tx_data_iso.op_to_scsi fields */
#घोषणा CPL_TX_DATA_ISO_OP_S	24
#घोषणा CPL_TX_DATA_ISO_OP_M	0xff
#घोषणा CPL_TX_DATA_ISO_OP_V(x)	((x) << CPL_TX_DATA_ISO_OP_S)
#घोषणा CPL_TX_DATA_ISO_OP_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_OP_S) & CPL_TX_DATA_ISO_OP_M)

#घोषणा CPL_TX_DATA_ISO_FIRST_S		23
#घोषणा CPL_TX_DATA_ISO_FIRST_M		0x1
#घोषणा CPL_TX_DATA_ISO_FIRST_V(x)	((x) << CPL_TX_DATA_ISO_FIRST_S)
#घोषणा CPL_TX_DATA_ISO_FIRST_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_FIRST_S) & CPL_TX_DATA_ISO_FIRST_M)
#घोषणा CPL_TX_DATA_ISO_FIRST_F	CPL_TX_DATA_ISO_FIRST_V(1U)

#घोषणा CPL_TX_DATA_ISO_LAST_S		22
#घोषणा CPL_TX_DATA_ISO_LAST_M		0x1
#घोषणा CPL_TX_DATA_ISO_LAST_V(x)	((x) << CPL_TX_DATA_ISO_LAST_S)
#घोषणा CPL_TX_DATA_ISO_LAST_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_LAST_S) & CPL_TX_DATA_ISO_LAST_M)
#घोषणा CPL_TX_DATA_ISO_LAST_F	CPL_TX_DATA_ISO_LAST_V(1U)

#घोषणा CPL_TX_DATA_ISO_CPLHDRLEN_S	21
#घोषणा CPL_TX_DATA_ISO_CPLHDRLEN_M	0x1
#घोषणा CPL_TX_DATA_ISO_CPLHDRLEN_V(x)	((x) << CPL_TX_DATA_ISO_CPLHDRLEN_S)
#घोषणा CPL_TX_DATA_ISO_CPLHDRLEN_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_CPLHDRLEN_S) & CPL_TX_DATA_ISO_CPLHDRLEN_M)
#घोषणा CPL_TX_DATA_ISO_CPLHDRLEN_F	CPL_TX_DATA_ISO_CPLHDRLEN_V(1U)

#घोषणा CPL_TX_DATA_ISO_HDRCRC_S	20
#घोषणा CPL_TX_DATA_ISO_HDRCRC_M	0x1
#घोषणा CPL_TX_DATA_ISO_HDRCRC_V(x)	((x) << CPL_TX_DATA_ISO_HDRCRC_S)
#घोषणा CPL_TX_DATA_ISO_HDRCRC_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_HDRCRC_S) & CPL_TX_DATA_ISO_HDRCRC_M)
#घोषणा CPL_TX_DATA_ISO_HDRCRC_F	CPL_TX_DATA_ISO_HDRCRC_V(1U)

#घोषणा CPL_TX_DATA_ISO_PLDCRC_S	19
#घोषणा CPL_TX_DATA_ISO_PLDCRC_M	0x1
#घोषणा CPL_TX_DATA_ISO_PLDCRC_V(x)	((x) << CPL_TX_DATA_ISO_PLDCRC_S)
#घोषणा CPL_TX_DATA_ISO_PLDCRC_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_PLDCRC_S) & CPL_TX_DATA_ISO_PLDCRC_M)
#घोषणा CPL_TX_DATA_ISO_PLDCRC_F	CPL_TX_DATA_ISO_PLDCRC_V(1U)

#घोषणा CPL_TX_DATA_ISO_IMMEDIATE_S	18
#घोषणा CPL_TX_DATA_ISO_IMMEDIATE_M	0x1
#घोषणा CPL_TX_DATA_ISO_IMMEDIATE_V(x)	((x) << CPL_TX_DATA_ISO_IMMEDIATE_S)
#घोषणा CPL_TX_DATA_ISO_IMMEDIATE_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_IMMEDIATE_S) & CPL_TX_DATA_ISO_IMMEDIATE_M)
#घोषणा CPL_TX_DATA_ISO_IMMEDIATE_F	CPL_TX_DATA_ISO_IMMEDIATE_V(1U)

#घोषणा CPL_TX_DATA_ISO_SCSI_S		16
#घोषणा CPL_TX_DATA_ISO_SCSI_M		0x3
#घोषणा CPL_TX_DATA_ISO_SCSI_V(x)	((x) << CPL_TX_DATA_ISO_SCSI_S)
#घोषणा CPL_TX_DATA_ISO_SCSI_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_SCSI_S) & CPL_TX_DATA_ISO_SCSI_M)

/* cpl_tx_data_iso.reserved2_seglen_offset fields */
#घोषणा CPL_TX_DATA_ISO_SEGLEN_OFFSET_S		0
#घोषणा CPL_TX_DATA_ISO_SEGLEN_OFFSET_M		0xffffff
#घोषणा CPL_TX_DATA_ISO_SEGLEN_OFFSET_V(x)	\
	((x) << CPL_TX_DATA_ISO_SEGLEN_OFFSET_S)
#घोषणा CPL_TX_DATA_ISO_SEGLEN_OFFSET_G(x)	\
	(((x) >> CPL_TX_DATA_ISO_SEGLEN_OFFSET_S) & \
	 CPL_TX_DATA_ISO_SEGLEN_OFFSET_M)

काष्ठा cpl_rx_data अणु
	जोड़ opcode_tid ot;
	__be16 rsvd;
	__be16 len;
	__be32 seq;
	__be16 urg;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 dack_mode:2;
	u8 psh:1;
	u8 heartbeat:1;
	u8 ddp_off:1;
	u8 :3;
#अन्यथा
	u8 :3;
	u8 ddp_off:1;
	u8 heartbeat:1;
	u8 psh:1;
	u8 dack_mode:2;
#पूर्ण_अगर
	u8 status;
पूर्ण;

काष्ठा cpl_rx_data_ack अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 credit_dack;
पूर्ण;

/* cpl_rx_data_ack.ack_seq fields */
#घोषणा RX_CREDITS_S    0
#घोषणा RX_CREDITS_V(x) ((x) << RX_CREDITS_S)

#घोषणा RX_FORCE_ACK_S    28
#घोषणा RX_FORCE_ACK_V(x) ((x) << RX_FORCE_ACK_S)
#घोषणा RX_FORCE_ACK_F    RX_FORCE_ACK_V(1U)

#घोषणा RX_DACK_MODE_S    29
#घोषणा RX_DACK_MODE_M    0x3
#घोषणा RX_DACK_MODE_V(x) ((x) << RX_DACK_MODE_S)
#घोषणा RX_DACK_MODE_G(x) (((x) >> RX_DACK_MODE_S) & RX_DACK_MODE_M)

#घोषणा RX_DACK_CHANGE_S    31
#घोषणा RX_DACK_CHANGE_V(x) ((x) << RX_DACK_CHANGE_S)
#घोषणा RX_DACK_CHANGE_F    RX_DACK_CHANGE_V(1U)

काष्ठा cpl_rx_pkt अणु
	काष्ठा rss_header rsshdr;
	u8 opcode;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 अगरf:4;
	u8 csum_calc:1;
	u8 ipmi_pkt:1;
	u8 vlan_ex:1;
	u8 ip_frag:1;
#अन्यथा
	u8 ip_frag:1;
	u8 vlan_ex:1;
	u8 ipmi_pkt:1;
	u8 csum_calc:1;
	u8 अगरf:4;
#पूर्ण_अगर
	__be16 csum;
	__be16 vlan;
	__be16 len;
	__be32 l2info;
	__be16 hdr_len;
	__be16 err_vec;
पूर्ण;

#घोषणा RX_T6_ETHHDR_LEN_M    0xFF
#घोषणा RX_T6_ETHHDR_LEN_G(x) (((x) >> RX_ETHHDR_LEN_S) & RX_T6_ETHHDR_LEN_M)

#घोषणा RXF_PSH_S    20
#घोषणा RXF_PSH_V(x) ((x) << RXF_PSH_S)
#घोषणा RXF_PSH_F    RXF_PSH_V(1U)

#घोषणा RXF_SYN_S    21
#घोषणा RXF_SYN_V(x) ((x) << RXF_SYN_S)
#घोषणा RXF_SYN_F    RXF_SYN_V(1U)

#घोषणा RXF_UDP_S    22
#घोषणा RXF_UDP_V(x) ((x) << RXF_UDP_S)
#घोषणा RXF_UDP_F    RXF_UDP_V(1U)

#घोषणा RXF_TCP_S    23
#घोषणा RXF_TCP_V(x) ((x) << RXF_TCP_S)
#घोषणा RXF_TCP_F    RXF_TCP_V(1U)

#घोषणा RXF_IP_S    24
#घोषणा RXF_IP_V(x) ((x) << RXF_IP_S)
#घोषणा RXF_IP_F    RXF_IP_V(1U)

#घोषणा RXF_IP6_S    25
#घोषणा RXF_IP6_V(x) ((x) << RXF_IP6_S)
#घोषणा RXF_IP6_F    RXF_IP6_V(1U)

#घोषणा RXF_SYN_COOKIE_S    26
#घोषणा RXF_SYN_COOKIE_V(x) ((x) << RXF_SYN_COOKIE_S)
#घोषणा RXF_SYN_COOKIE_F    RXF_SYN_COOKIE_V(1U)

#घोषणा RXF_FCOE_S    26
#घोषणा RXF_FCOE_V(x) ((x) << RXF_FCOE_S)
#घोषणा RXF_FCOE_F    RXF_FCOE_V(1U)

#घोषणा RXF_LRO_S    27
#घोषणा RXF_LRO_V(x) ((x) << RXF_LRO_S)
#घोषणा RXF_LRO_F    RXF_LRO_V(1U)

/* rx_pkt.l2info fields */
#घोषणा RX_ETHHDR_LEN_S    0
#घोषणा RX_ETHHDR_LEN_M    0x1F
#घोषणा RX_ETHHDR_LEN_V(x) ((x) << RX_ETHHDR_LEN_S)
#घोषणा RX_ETHHDR_LEN_G(x) (((x) >> RX_ETHHDR_LEN_S) & RX_ETHHDR_LEN_M)

#घोषणा RX_T5_ETHHDR_LEN_S    0
#घोषणा RX_T5_ETHHDR_LEN_M    0x3F
#घोषणा RX_T5_ETHHDR_LEN_V(x) ((x) << RX_T5_ETHHDR_LEN_S)
#घोषणा RX_T5_ETHHDR_LEN_G(x) (((x) >> RX_T5_ETHHDR_LEN_S) & RX_T5_ETHHDR_LEN_M)

#घोषणा RX_MACIDX_S    8
#घोषणा RX_MACIDX_M    0x1FF
#घोषणा RX_MACIDX_V(x) ((x) << RX_MACIDX_S)
#घोषणा RX_MACIDX_G(x) (((x) >> RX_MACIDX_S) & RX_MACIDX_M)

#घोषणा RXF_SYN_S    21
#घोषणा RXF_SYN_V(x) ((x) << RXF_SYN_S)
#घोषणा RXF_SYN_F    RXF_SYN_V(1U)

#घोषणा RX_CHAN_S    28
#घोषणा RX_CHAN_M    0xF
#घोषणा RX_CHAN_V(x) ((x) << RX_CHAN_S)
#घोषणा RX_CHAN_G(x) (((x) >> RX_CHAN_S) & RX_CHAN_M)

/* rx_pkt.hdr_len fields */
#घोषणा RX_TCPHDR_LEN_S    0
#घोषणा RX_TCPHDR_LEN_M    0x3F
#घोषणा RX_TCPHDR_LEN_V(x) ((x) << RX_TCPHDR_LEN_S)
#घोषणा RX_TCPHDR_LEN_G(x) (((x) >> RX_TCPHDR_LEN_S) & RX_TCPHDR_LEN_M)

#घोषणा RX_IPHDR_LEN_S    6
#घोषणा RX_IPHDR_LEN_M    0x3FF
#घोषणा RX_IPHDR_LEN_V(x) ((x) << RX_IPHDR_LEN_S)
#घोषणा RX_IPHDR_LEN_G(x) (((x) >> RX_IPHDR_LEN_S) & RX_IPHDR_LEN_M)

/* rx_pkt.err_vec fields */
#घोषणा RXERR_CSUM_S    13
#घोषणा RXERR_CSUM_V(x) ((x) << RXERR_CSUM_S)
#घोषणा RXERR_CSUM_F    RXERR_CSUM_V(1U)

#घोषणा T6_COMPR_RXERR_LEN_S    1
#घोषणा T6_COMPR_RXERR_LEN_V(x) ((x) << T6_COMPR_RXERR_LEN_S)
#घोषणा T6_COMPR_RXERR_LEN_F    T6_COMPR_RXERR_LEN_V(1U)

#घोषणा T6_COMPR_RXERR_VEC_S    0
#घोषणा T6_COMPR_RXERR_VEC_M    0x3F
#घोषणा T6_COMPR_RXERR_VEC_V(x) ((x) << T6_COMPR_RXERR_LEN_S)
#घोषणा T6_COMPR_RXERR_VEC_G(x) \
		(((x) >> T6_COMPR_RXERR_VEC_S) & T6_COMPR_RXERR_VEC_M)

/* Logical OR of RX_ERROR_CSUM, RX_ERROR_CSIP */
#घोषणा T6_COMPR_RXERR_SUM_S    4
#घोषणा T6_COMPR_RXERR_SUM_V(x) ((x) << T6_COMPR_RXERR_SUM_S)
#घोषणा T6_COMPR_RXERR_SUM_F    T6_COMPR_RXERR_SUM_V(1U)

#घोषणा T6_RX_TNLHDR_LEN_S    8
#घोषणा T6_RX_TNLHDR_LEN_M    0xFF
#घोषणा T6_RX_TNLHDR_LEN_V(x) ((x) << T6_RX_TNLHDR_LEN_S)
#घोषणा T6_RX_TNLHDR_LEN_G(x) (((x) >> T6_RX_TNLHDR_LEN_S) & T6_RX_TNLHDR_LEN_M)

काष्ठा cpl_trace_pkt अणु
	u8 opcode;
	u8 पूर्णांकf;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8 runt:4;
	u8 filter_hit:4;
	u8 :6;
	u8 err:1;
	u8 trunc:1;
#अन्यथा
	u8 filter_hit:4;
	u8 runt:4;
	u8 trunc:1;
	u8 err:1;
	u8 :6;
#पूर्ण_अगर
	__be16 rsvd;
	__be16 len;
	__be64 tstamp;
पूर्ण;

काष्ठा cpl_t5_trace_pkt अणु
	__u8 opcode;
	__u8 पूर्णांकf;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 runt:4;
	__u8 filter_hit:4;
	__u8:6;
	__u8 err:1;
	__u8 trunc:1;
#अन्यथा
	__u8 filter_hit:4;
	__u8 runt:4;
	__u8 trunc:1;
	__u8 err:1;
	__u8:6;
#पूर्ण_अगर
	__be16 rsvd;
	__be16 len;
	__be64 tstamp;
	__be64 rsvd1;
पूर्ण;

काष्ठा cpl_l2t_ग_लिखो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be16 params;
	__be16 l2t_idx;
	__be16 vlan;
	u8 dst_mac[6];
पूर्ण;

/* cpl_l2t_ग_लिखो_req.params fields */
#घोषणा L2T_W_INFO_S    2
#घोषणा L2T_W_INFO_V(x) ((x) << L2T_W_INFO_S)

#घोषणा L2T_W_PORT_S    8
#घोषणा L2T_W_PORT_V(x) ((x) << L2T_W_PORT_S)

#घोषणा L2T_W_NOREPLY_S    15
#घोषणा L2T_W_NOREPLY_V(x) ((x) << L2T_W_NOREPLY_S)
#घोषणा L2T_W_NOREPLY_F    L2T_W_NOREPLY_V(1U)

#घोषणा CPL_L2T_VLAN_NONE 0xfff

काष्ठा cpl_l2t_ग_लिखो_rpl अणु
	जोड़ opcode_tid ot;
	u8 status;
	u8 rsvd[3];
पूर्ण;

काष्ठा cpl_smt_ग_लिखो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 params;
	__be16 pfvf1;
	u8 src_mac1[6];
	__be16 pfvf0;
	u8 src_mac0[6];
पूर्ण;

काष्ठा cpl_t6_smt_ग_लिखो_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__be32 params;
	__be64 tag;
	__be16 pfvf0;
	u8 src_mac0[6];
	__be32 local_ip;
	__be32 rsvd;
पूर्ण;

काष्ठा cpl_smt_ग_लिखो_rpl अणु
	जोड़ opcode_tid ot;
	u8 status;
	u8 rsvd[3];
पूर्ण;

/* cpl_smt_अणुपढ़ो,ग_लिखोपूर्ण_req.params fields */
#घोषणा SMTW_OVLAN_IDX_S	16
#घोषणा SMTW_OVLAN_IDX_V(x)	((x) << SMTW_OVLAN_IDX_S)

#घोषणा SMTW_IDX_S	20
#घोषणा SMTW_IDX_V(x)	((x) << SMTW_IDX_S)

#घोषणा SMTW_NORPL_S	31
#घोषणा SMTW_NORPL_V(x)	((x) << SMTW_NORPL_S)
#घोषणा SMTW_NORPL_F	SMTW_NORPL_V(1U)

काष्ठा cpl_rdma_terminate अणु
	जोड़ opcode_tid ot;
	__be16 rsvd;
	__be16 len;
पूर्ण;

काष्ठा cpl_sge_egr_update अणु
	__be32 opcode_qid;
	__be16 cidx;
	__be16 pidx;
पूर्ण;

/* cpl_sge_egr_update.ot fields */
#घोषणा EGR_QID_S    0
#घोषणा EGR_QID_M    0x1FFFF
#घोषणा EGR_QID_G(x) (((x) >> EGR_QID_S) & EGR_QID_M)

/* cpl_fw*.type values */
क्रमागत अणु
	FW_TYPE_CMD_RPL = 0,
	FW_TYPE_WR_RPL = 1,
	FW_TYPE_CQE = 2,
	FW_TYPE_OFLD_CONNECTION_WR_RPL = 3,
	FW_TYPE_RSSCPL = 4,
पूर्ण;

काष्ठा cpl_fw4_pld अणु
	u8 opcode;
	u8 rsvd0[3];
	u8 type;
	u8 rsvd1;
	__be16 len;
	__be64 data;
	__be64 rsvd2;
पूर्ण;

काष्ठा cpl_fw6_pld अणु
	u8 opcode;
	u8 rsvd[5];
	__be16 len;
	__be64 data[4];
पूर्ण;

काष्ठा cpl_fw4_msg अणु
	u8 opcode;
	u8 type;
	__be16 rsvd0;
	__be32 rsvd1;
	__be64 data[2];
पूर्ण;

काष्ठा cpl_fw4_ack अणु
	जोड़ opcode_tid ot;
	u8 credits;
	u8 rsvd0[2];
	u8 seq_vld;
	__be32 snd_nxt;
	__be32 snd_una;
	__be64 rsvd1;
पूर्ण;

क्रमागत अणु
	CPL_FW4_ACK_FLAGS_SEQVAL	= 0x1,	/* seqn valid */
	CPL_FW4_ACK_FLAGS_CH		= 0x2,	/* channel change complete */
	CPL_FW4_ACK_FLAGS_FLOWC		= 0x4,	/* fw_flowc_wr complete */
पूर्ण;

#घोषणा CPL_FW4_ACK_FLOWID_S    0
#घोषणा CPL_FW4_ACK_FLOWID_M    0xffffff
#घोषणा CPL_FW4_ACK_FLOWID_G(x) \
	(((x) >> CPL_FW4_ACK_FLOWID_S) & CPL_FW4_ACK_FLOWID_M)

काष्ठा cpl_fw6_msg अणु
	u8 opcode;
	u8 type;
	__be16 rsvd0;
	__be32 rsvd1;
	__be64 data[4];
पूर्ण;

/* cpl_fw6_msg.type values */
क्रमागत अणु
	FW6_TYPE_CMD_RPL = 0,
	FW6_TYPE_WR_RPL = 1,
	FW6_TYPE_CQE = 2,
	FW6_TYPE_OFLD_CONNECTION_WR_RPL = 3,
	FW6_TYPE_RSSCPL = FW_TYPE_RSSCPL,
पूर्ण;

काष्ठा cpl_fw6_msg_ofld_connection_wr_rpl अणु
	__u64   cookie;
	__be32  tid;    /* or atid in हाल of active failure */
	__u8    t_state;
	__u8    retval;
	__u8    rsvd[2];
पूर्ण;

काष्ठा cpl_tx_data अणु
	जोड़ opcode_tid ot;
	__be32 len;
	__be32 rsvd;
	__be32 flags;
पूर्ण;

/* cpl_tx_data.flags field */
#घोषणा TX_FORCE_S	13
#घोषणा TX_FORCE_V(x)	((x) << TX_FORCE_S)

#घोषणा TX_DATA_MSS_S    16
#घोषणा TX_DATA_MSS_M    0xFFFF
#घोषणा TX_DATA_MSS_V(x) ((x) << TX_DATA_MSS_S)
#घोषणा TX_DATA_MSS_G(x) (((x) >> TX_DATA_MSS_S) & TX_DATA_MSS_M)

#घोषणा TX_LENGTH_S    0
#घोषणा TX_LENGTH_M    0xFFFF
#घोषणा TX_LENGTH_V(x) ((x) << TX_LENGTH_S)
#घोषणा TX_LENGTH_G(x) (((x) >> TX_LENGTH_S) & TX_LENGTH_M)

#घोषणा T6_TX_FORCE_S		20
#घोषणा T6_TX_FORCE_V(x)	((x) << T6_TX_FORCE_S)
#घोषणा T6_TX_FORCE_F		T6_TX_FORCE_V(1U)

#घोषणा TX_URG_S    16
#घोषणा TX_URG_V(x) ((x) << TX_URG_S)

#घोषणा TX_SHOVE_S    14
#घोषणा TX_SHOVE_V(x) ((x) << TX_SHOVE_S)
#घोषणा TX_SHOVE_F    TX_SHOVE_V(1U)

#घोषणा TX_BYPASS_S    21
#घोषणा TX_BYPASS_V(x) ((x) << TX_BYPASS_S)
#घोषणा TX_BYPASS_F    TX_BYPASS_V(1U)

#घोषणा TX_PUSH_S    22
#घोषणा TX_PUSH_V(x) ((x) << TX_PUSH_S)
#घोषणा TX_PUSH_F    TX_PUSH_V(1U)

#घोषणा TX_ULP_MODE_S    10
#घोषणा TX_ULP_MODE_M    0x7
#घोषणा TX_ULP_MODE_V(x) ((x) << TX_ULP_MODE_S)
#घोषणा TX_ULP_MODE_G(x) (((x) >> TX_ULP_MODE_S) & TX_ULP_MODE_M)

क्रमागत अणु
	ULP_TX_MEM_READ = 2,
	ULP_TX_MEM_WRITE = 3,
	ULP_TX_PKT = 4
पूर्ण;

क्रमागत अणु
	ULP_TX_SC_NOOP = 0x80,
	ULP_TX_SC_IMM  = 0x81,
	ULP_TX_SC_DSGL = 0x82,
	ULP_TX_SC_ISGL = 0x83,
	ULP_TX_SC_MEMRD = 0x86
पूर्ण;

#घोषणा ULPTX_CMD_S    24
#घोषणा ULPTX_CMD_V(x) ((x) << ULPTX_CMD_S)

#घोषणा ULPTX_LEN16_S    0
#घोषणा ULPTX_LEN16_M    0xFF
#घोषणा ULPTX_LEN16_V(x) ((x) << ULPTX_LEN16_S)

#घोषणा ULP_TX_SC_MORE_S 23
#घोषणा ULP_TX_SC_MORE_V(x) ((x) << ULP_TX_SC_MORE_S)
#घोषणा ULP_TX_SC_MORE_F  ULP_TX_SC_MORE_V(1U)

काष्ठा ulptx_sge_pair अणु
	__be32 len[2];
	__be64 addr[2];
पूर्ण;

काष्ठा ulptx_sgl अणु
	__be32 cmd_nsge;
	__be32 len0;
	__be64 addr0;
	काष्ठा ulptx_sge_pair sge[];
पूर्ण;

काष्ठा ulptx_idata अणु
	__be32 cmd_more;
	__be32 len;
पूर्ण;

काष्ठा ulp_txpkt अणु
	__be32 cmd_dest;
	__be32 len;
पूर्ण;

#घोषणा ULPTX_CMD_S    24
#घोषणा ULPTX_CMD_M    0xFF
#घोषणा ULPTX_CMD_V(x) ((x) << ULPTX_CMD_S)

#घोषणा ULPTX_NSGE_S    0
#घोषणा ULPTX_NSGE_V(x) ((x) << ULPTX_NSGE_S)

#घोषणा ULPTX_MORE_S	23
#घोषणा ULPTX_MORE_V(x)	((x) << ULPTX_MORE_S)
#घोषणा ULPTX_MORE_F	ULPTX_MORE_V(1U)

#घोषणा ULP_TXPKT_DEST_S    16
#घोषणा ULP_TXPKT_DEST_M    0x3
#घोषणा ULP_TXPKT_DEST_V(x) ((x) << ULP_TXPKT_DEST_S)

#घोषणा ULP_TXPKT_FID_S     4
#घोषणा ULP_TXPKT_FID_M     0x7ff
#घोषणा ULP_TXPKT_FID_V(x)  ((x) << ULP_TXPKT_FID_S)

#घोषणा ULP_TXPKT_RO_S      3
#घोषणा ULP_TXPKT_RO_V(x) ((x) << ULP_TXPKT_RO_S)
#घोषणा ULP_TXPKT_RO_F ULP_TXPKT_RO_V(1U)

क्रमागत cpl_tx_tnl_lso_type अणु
	TX_TNL_TYPE_OPAQUE,
	TX_TNL_TYPE_NVGRE,
	TX_TNL_TYPE_VXLAN,
	TX_TNL_TYPE_GENEVE,
पूर्ण;

काष्ठा cpl_tx_tnl_lso अणु
	__be32 op_to_IpIdSplitOut;
	__be16 IpIdOffsetOut;
	__be16 UdpLenSetOut_to_TnlHdrLen;
	__be64 r1;
	__be32 Flow_to_TcpHdrLen;
	__be16 IpIdOffset;
	__be16 IpIdSplit_to_Mss;
	__be32 TCPSeqOffset;
	__be32 EthLenOffset_Size;
	/* encapsulated CPL (TX_PKT_XT) follows here */
पूर्ण;

#घोषणा CPL_TX_TNL_LSO_OPCODE_S		24
#घोषणा CPL_TX_TNL_LSO_OPCODE_M		0xff
#घोषणा CPL_TX_TNL_LSO_OPCODE_V(x)      ((x) << CPL_TX_TNL_LSO_OPCODE_S)
#घोषणा CPL_TX_TNL_LSO_OPCODE_G(x)      \
	(((x) >> CPL_TX_TNL_LSO_OPCODE_S) & CPL_TX_TNL_LSO_OPCODE_M)

#घोषणा CPL_TX_TNL_LSO_FIRST_S		23
#घोषणा CPL_TX_TNL_LSO_FIRST_M		0x1
#घोषणा CPL_TX_TNL_LSO_FIRST_V(x)	((x) << CPL_TX_TNL_LSO_FIRST_S)
#घोषणा CPL_TX_TNL_LSO_FIRST_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_FIRST_S) & CPL_TX_TNL_LSO_FIRST_M)
#घोषणा CPL_TX_TNL_LSO_FIRST_F		CPL_TX_TNL_LSO_FIRST_V(1U)

#घोषणा CPL_TX_TNL_LSO_LAST_S		22
#घोषणा CPL_TX_TNL_LSO_LAST_M		0x1
#घोषणा CPL_TX_TNL_LSO_LAST_V(x)	((x) << CPL_TX_TNL_LSO_LAST_S)
#घोषणा CPL_TX_TNL_LSO_LAST_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_LAST_S) & CPL_TX_TNL_LSO_LAST_M)
#घोषणा CPL_TX_TNL_LSO_LAST_F		CPL_TX_TNL_LSO_LAST_V(1U)

#घोषणा CPL_TX_TNL_LSO_ETHHDRLENXOUT_S	21
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENXOUT_M	0x1
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENXOUT_V(x) \
	((x) << CPL_TX_TNL_LSO_ETHHDRLENXOUT_S)
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENXOUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_ETHHDRLENXOUT_S) & \
	 CPL_TX_TNL_LSO_ETHHDRLENXOUT_M)
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENXOUT_F CPL_TX_TNL_LSO_ETHHDRLENXOUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_IPV6OUT_S	20
#घोषणा CPL_TX_TNL_LSO_IPV6OUT_M	0x1
#घोषणा CPL_TX_TNL_LSO_IPV6OUT_V(x)	((x) << CPL_TX_TNL_LSO_IPV6OUT_S)
#घोषणा CPL_TX_TNL_LSO_IPV6OUT_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_IPV6OUT_S) & CPL_TX_TNL_LSO_IPV6OUT_M)
#घोषणा CPL_TX_TNL_LSO_IPV6OUT_F        CPL_TX_TNL_LSO_IPV6OUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_ETHHDRLEN_S	16
#घोषणा CPL_TX_TNL_LSO_ETHHDRLEN_M	0xf
#घोषणा CPL_TX_TNL_LSO_ETHHDRLEN_V(x)	((x) << CPL_TX_TNL_LSO_ETHHDRLEN_S)
#घोषणा CPL_TX_TNL_LSO_ETHHDRLEN_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_ETHHDRLEN_S) & CPL_TX_TNL_LSO_ETHHDRLEN_M)

#घोषणा CPL_TX_TNL_LSO_IPHDRLEN_S	4
#घोषणा CPL_TX_TNL_LSO_IPHDRLEN_M	0xfff
#घोषणा CPL_TX_TNL_LSO_IPHDRLEN_V(x)	((x) << CPL_TX_TNL_LSO_IPHDRLEN_S)
#घोषणा CPL_TX_TNL_LSO_IPHDRLEN_G(x)    \
	(((x) >> CPL_TX_TNL_LSO_IPHDRLEN_S) & CPL_TX_TNL_LSO_IPHDRLEN_M)

#घोषणा CPL_TX_TNL_LSO_TCPHDRLEN_S	0
#घोषणा CPL_TX_TNL_LSO_TCPHDRLEN_M	0xf
#घोषणा CPL_TX_TNL_LSO_TCPHDRLEN_V(x)	((x) << CPL_TX_TNL_LSO_TCPHDRLEN_S)
#घोषणा CPL_TX_TNL_LSO_TCPHDRLEN_G(x)   \
	(((x) >> CPL_TX_TNL_LSO_TCPHDRLEN_S) & CPL_TX_TNL_LSO_TCPHDRLEN_M)

#घोषणा CPL_TX_TNL_LSO_MSS_S            0
#घोषणा CPL_TX_TNL_LSO_MSS_M            0x3fff
#घोषणा CPL_TX_TNL_LSO_MSS_V(x)         ((x) << CPL_TX_TNL_LSO_MSS_S)
#घोषणा CPL_TX_TNL_LSO_MSS_G(x)         \
	(((x) >> CPL_TX_TNL_LSO_MSS_S) & CPL_TX_TNL_LSO_MSS_M)

#घोषणा CPL_TX_TNL_LSO_SIZE_S		0
#घोषणा CPL_TX_TNL_LSO_SIZE_M		0xfffffff
#घोषणा CPL_TX_TNL_LSO_SIZE_V(x)	((x) << CPL_TX_TNL_LSO_SIZE_S)
#घोषणा CPL_TX_TNL_LSO_SIZE_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_SIZE_S) & CPL_TX_TNL_LSO_SIZE_M)

#घोषणा CPL_TX_TNL_LSO_ETHHDRLENOUT_S   16
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENOUT_M   0xf
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENOUT_V(x) \
	((x) << CPL_TX_TNL_LSO_ETHHDRLENOUT_S)
#घोषणा CPL_TX_TNL_LSO_ETHHDRLENOUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_ETHHDRLENOUT_S) & CPL_TX_TNL_LSO_ETHHDRLENOUT_M)

#घोषणा CPL_TX_TNL_LSO_IPHDRLENOUT_S    4
#घोषणा CPL_TX_TNL_LSO_IPHDRLENOUT_M    0xfff
#घोषणा CPL_TX_TNL_LSO_IPHDRLENOUT_V(x) ((x) << CPL_TX_TNL_LSO_IPHDRLENOUT_S)
#घोषणा CPL_TX_TNL_LSO_IPHDRLENOUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_IPHDRLENOUT_S) & CPL_TX_TNL_LSO_IPHDRLENOUT_M)

#घोषणा CPL_TX_TNL_LSO_IPHDRCHKOUT_S    3
#घोषणा CPL_TX_TNL_LSO_IPHDRCHKOUT_M    0x1
#घोषणा CPL_TX_TNL_LSO_IPHDRCHKOUT_V(x) ((x) << CPL_TX_TNL_LSO_IPHDRCHKOUT_S)
#घोषणा CPL_TX_TNL_LSO_IPHDRCHKOUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_IPHDRCHKOUT_S) & CPL_TX_TNL_LSO_IPHDRCHKOUT_M)
#घोषणा CPL_TX_TNL_LSO_IPHDRCHKOUT_F    CPL_TX_TNL_LSO_IPHDRCHKOUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_IPLENSETOUT_S	2
#घोषणा CPL_TX_TNL_LSO_IPLENSETOUT_M	0x1
#घोषणा CPL_TX_TNL_LSO_IPLENSETOUT_V(x) ((x) << CPL_TX_TNL_LSO_IPLENSETOUT_S)
#घोषणा CPL_TX_TNL_LSO_IPLENSETOUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_IPLENSETOUT_S) & CPL_TX_TNL_LSO_IPLENSETOUT_M)
#घोषणा CPL_TX_TNL_LSO_IPLENSETOUT_F	CPL_TX_TNL_LSO_IPLENSETOUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_IPIDINCOUT_S	1
#घोषणा CPL_TX_TNL_LSO_IPIDINCOUT_M	0x1
#घोषणा CPL_TX_TNL_LSO_IPIDINCOUT_V(x)  ((x) << CPL_TX_TNL_LSO_IPIDINCOUT_S)
#घोषणा CPL_TX_TNL_LSO_IPIDINCOUT_G(x)  \
	(((x) >> CPL_TX_TNL_LSO_IPIDINCOUT_S) & CPL_TX_TNL_LSO_IPIDINCOUT_M)
#घोषणा CPL_TX_TNL_LSO_IPIDINCOUT_F     CPL_TX_TNL_LSO_IPIDINCOUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_UDPCHKCLROUT_S   14
#घोषणा CPL_TX_TNL_LSO_UDPCHKCLROUT_M   0x1
#घोषणा CPL_TX_TNL_LSO_UDPCHKCLROUT_V(x) \
	((x) << CPL_TX_TNL_LSO_UDPCHKCLROUT_S)
#घोषणा CPL_TX_TNL_LSO_UDPCHKCLROUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_UDPCHKCLROUT_S) & \
	 CPL_TX_TNL_LSO_UDPCHKCLROUT_M)
#घोषणा CPL_TX_TNL_LSO_UDPCHKCLROUT_F   CPL_TX_TNL_LSO_UDPCHKCLROUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_UDPLENSETOUT_S   15
#घोषणा CPL_TX_TNL_LSO_UDPLENSETOUT_M   0x1
#घोषणा CPL_TX_TNL_LSO_UDPLENSETOUT_V(x) \
	((x) << CPL_TX_TNL_LSO_UDPLENSETOUT_S)
#घोषणा CPL_TX_TNL_LSO_UDPLENSETOUT_G(x) \
	(((x) >> CPL_TX_TNL_LSO_UDPLENSETOUT_S) & \
	 CPL_TX_TNL_LSO_UDPLENSETOUT_M)
#घोषणा CPL_TX_TNL_LSO_UDPLENSETOUT_F   CPL_TX_TNL_LSO_UDPLENSETOUT_V(1U)

#घोषणा CPL_TX_TNL_LSO_TNLTYPE_S	12
#घोषणा CPL_TX_TNL_LSO_TNLTYPE_M	0x3
#घोषणा CPL_TX_TNL_LSO_TNLTYPE_V(x)	((x) << CPL_TX_TNL_LSO_TNLTYPE_S)
#घोषणा CPL_TX_TNL_LSO_TNLTYPE_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_TNLTYPE_S) & CPL_TX_TNL_LSO_TNLTYPE_M)

#घोषणा S_CPL_TX_TNL_LSO_ETHHDRLEN	16
#घोषणा M_CPL_TX_TNL_LSO_ETHHDRLEN	0xf
#घोषणा V_CPL_TX_TNL_LSO_ETHHDRLEN(x)	((x) << S_CPL_TX_TNL_LSO_ETHHDRLEN)
#घोषणा G_CPL_TX_TNL_LSO_ETHHDRLEN(x)	\
	(((x) >> S_CPL_TX_TNL_LSO_ETHHDRLEN) & M_CPL_TX_TNL_LSO_ETHHDRLEN)

#घोषणा CPL_TX_TNL_LSO_TNLHDRLEN_S      0
#घोषणा CPL_TX_TNL_LSO_TNLHDRLEN_M      0xfff
#घोषणा CPL_TX_TNL_LSO_TNLHDRLEN_V(x)	((x) << CPL_TX_TNL_LSO_TNLHDRLEN_S)
#घोषणा CPL_TX_TNL_LSO_TNLHDRLEN_G(x)   \
	(((x) >> CPL_TX_TNL_LSO_TNLHDRLEN_S) & CPL_TX_TNL_LSO_TNLHDRLEN_M)

#घोषणा CPL_TX_TNL_LSO_IPV6_S		20
#घोषणा CPL_TX_TNL_LSO_IPV6_M		0x1
#घोषणा CPL_TX_TNL_LSO_IPV6_V(x)	((x) << CPL_TX_TNL_LSO_IPV6_S)
#घोषणा CPL_TX_TNL_LSO_IPV6_G(x)	\
	(((x) >> CPL_TX_TNL_LSO_IPV6_S) & CPL_TX_TNL_LSO_IPV6_M)
#घोषणा CPL_TX_TNL_LSO_IPV6_F		CPL_TX_TNL_LSO_IPV6_V(1U)

#घोषणा ULP_TX_SC_MORE_S 23
#घोषणा ULP_TX_SC_MORE_V(x) ((x) << ULP_TX_SC_MORE_S)
#घोषणा ULP_TX_SC_MORE_F  ULP_TX_SC_MORE_V(1U)

काष्ठा ulp_mem_io अणु
	WR_HDR;
	__be32 cmd;
	__be32 len16;             /* command length */
	__be32 dlen;              /* data length in 32-byte units */
	__be32 lock_addr;
पूर्ण;

#घोषणा ULP_MEMIO_LOCK_S    31
#घोषणा ULP_MEMIO_LOCK_V(x) ((x) << ULP_MEMIO_LOCK_S)
#घोषणा ULP_MEMIO_LOCK_F    ULP_MEMIO_LOCK_V(1U)

/* additional ulp_mem_io.cmd fields */
#घोषणा ULP_MEMIO_ORDER_S    23
#घोषणा ULP_MEMIO_ORDER_V(x) ((x) << ULP_MEMIO_ORDER_S)
#घोषणा ULP_MEMIO_ORDER_F    ULP_MEMIO_ORDER_V(1U)

#घोषणा T5_ULP_MEMIO_IMM_S    23
#घोषणा T5_ULP_MEMIO_IMM_V(x) ((x) << T5_ULP_MEMIO_IMM_S)
#घोषणा T5_ULP_MEMIO_IMM_F    T5_ULP_MEMIO_IMM_V(1U)

#घोषणा T5_ULP_MEMIO_ORDER_S    22
#घोषणा T5_ULP_MEMIO_ORDER_V(x) ((x) << T5_ULP_MEMIO_ORDER_S)
#घोषणा T5_ULP_MEMIO_ORDER_F    T5_ULP_MEMIO_ORDER_V(1U)

#घोषणा T5_ULP_MEMIO_FID_S	4
#घोषणा T5_ULP_MEMIO_FID_M	0x7ff
#घोषणा T5_ULP_MEMIO_FID_V(x)	((x) << T5_ULP_MEMIO_FID_S)

/* ulp_mem_io.lock_addr fields */
#घोषणा ULP_MEMIO_ADDR_S    0
#घोषणा ULP_MEMIO_ADDR_V(x) ((x) << ULP_MEMIO_ADDR_S)

/* ulp_mem_io.dlen fields */
#घोषणा ULP_MEMIO_DATA_LEN_S    0
#घोषणा ULP_MEMIO_DATA_LEN_V(x) ((x) << ULP_MEMIO_DATA_LEN_S)

#घोषणा ULPTX_NSGE_S    0
#घोषणा ULPTX_NSGE_M    0xFFFF
#घोषणा ULPTX_NSGE_V(x) ((x) << ULPTX_NSGE_S)
#घोषणा ULPTX_NSGE_G(x) (((x) >> ULPTX_NSGE_S) & ULPTX_NSGE_M)

काष्ठा ulptx_sc_memrd अणु
	__be32 cmd_to_len;
	__be32 addr;
पूर्ण;

#घोषणा ULP_TXPKT_DATAMODIFY_S       23
#घोषणा ULP_TXPKT_DATAMODIFY_M       0x1
#घोषणा ULP_TXPKT_DATAMODIFY_V(x)    ((x) << ULP_TXPKT_DATAMODIFY_S)
#घोषणा ULP_TXPKT_DATAMODIFY_G(x)    \
	(((x) >> ULP_TXPKT_DATAMODIFY_S) & ULP_TXPKT_DATAMODIFY__M)
#घोषणा ULP_TXPKT_DATAMODIFY_F       ULP_TXPKT_DATAMODIFY_V(1U)

#घोषणा ULP_TXPKT_CHANNELID_S        22
#घोषणा ULP_TXPKT_CHANNELID_M        0x1
#घोषणा ULP_TXPKT_CHANNELID_V(x)     ((x) << ULP_TXPKT_CHANNELID_S)
#घोषणा ULP_TXPKT_CHANNELID_G(x)     \
	(((x) >> ULP_TXPKT_CHANNELID_S) & ULP_TXPKT_CHANNELID_M)
#घोषणा ULP_TXPKT_CHANNELID_F        ULP_TXPKT_CHANNELID_V(1U)

#घोषणा SCMD_SEQ_NO_CTRL_S      29
#घोषणा SCMD_SEQ_NO_CTRL_M      0x3
#घोषणा SCMD_SEQ_NO_CTRL_V(x)   ((x) << SCMD_SEQ_NO_CTRL_S)
#घोषणा SCMD_SEQ_NO_CTRL_G(x)   \
	(((x) >> SCMD_SEQ_NO_CTRL_S) & SCMD_SEQ_NO_CTRL_M)

/* StsFieldPrsnt- Status field at the end of the TLS PDU */
#घोषणा SCMD_STATUS_PRESENT_S   28
#घोषणा SCMD_STATUS_PRESENT_M   0x1
#घोषणा SCMD_STATUS_PRESENT_V(x)    ((x) << SCMD_STATUS_PRESENT_S)
#घोषणा SCMD_STATUS_PRESENT_G(x)    \
	(((x) >> SCMD_STATUS_PRESENT_S) & SCMD_STATUS_PRESENT_M)
#घोषणा SCMD_STATUS_PRESENT_F   SCMD_STATUS_PRESENT_V(1U)

/* ProtoVersion - Protocol Version 0: 1.2, 1:1.1, 2:DTLS, 3:Generic,
 * 3-15: Reserved.
 */
#घोषणा SCMD_PROTO_VERSION_S    24
#घोषणा SCMD_PROTO_VERSION_M    0xf
#घोषणा SCMD_PROTO_VERSION_V(x) ((x) << SCMD_PROTO_VERSION_S)
#घोषणा SCMD_PROTO_VERSION_G(x) \
	(((x) >> SCMD_PROTO_VERSION_S) & SCMD_PROTO_VERSION_M)

/* EncDecCtrl - Encryption/Decryption Control. 0: Encrypt, 1: Decrypt */
#घोषणा SCMD_ENC_DEC_CTRL_S     23
#घोषणा SCMD_ENC_DEC_CTRL_M     0x1
#घोषणा SCMD_ENC_DEC_CTRL_V(x)  ((x) << SCMD_ENC_DEC_CTRL_S)
#घोषणा SCMD_ENC_DEC_CTRL_G(x)  \
	(((x) >> SCMD_ENC_DEC_CTRL_S) & SCMD_ENC_DEC_CTRL_M)
#घोषणा SCMD_ENC_DEC_CTRL_F SCMD_ENC_DEC_CTRL_V(1U)

/* CipherAuthSeqCtrl - Cipher Authentication Sequence Control. */
#घोषणा SCMD_CIPH_AUTH_SEQ_CTRL_S       22
#घोषणा SCMD_CIPH_AUTH_SEQ_CTRL_M       0x1
#घोषणा SCMD_CIPH_AUTH_SEQ_CTRL_V(x)    \
	((x) << SCMD_CIPH_AUTH_SEQ_CTRL_S)
#घोषणा SCMD_CIPH_AUTH_SEQ_CTRL_G(x)    \
	(((x) >> SCMD_CIPH_AUTH_SEQ_CTRL_S) & SCMD_CIPH_AUTH_SEQ_CTRL_M)
#घोषणा SCMD_CIPH_AUTH_SEQ_CTRL_F   SCMD_CIPH_AUTH_SEQ_CTRL_V(1U)

/* CiphMode -  Cipher Mode. 0: NOP, 1:AES-CBC, 2:AES-GCM, 3:AES-CTR,
 * 4:Generic-AES, 5-15: Reserved.
 */
#घोषणा SCMD_CIPH_MODE_S    18
#घोषणा SCMD_CIPH_MODE_M    0xf
#घोषणा SCMD_CIPH_MODE_V(x) ((x) << SCMD_CIPH_MODE_S)
#घोषणा SCMD_CIPH_MODE_G(x) \
	(((x) >> SCMD_CIPH_MODE_S) & SCMD_CIPH_MODE_M)

/* AuthMode - Auth Mode. 0: NOP, 1:SHA1, 2:SHA2-224, 3:SHA2-256
 * 4-15: Reserved
 */
#घोषणा SCMD_AUTH_MODE_S    14
#घोषणा SCMD_AUTH_MODE_M    0xf
#घोषणा SCMD_AUTH_MODE_V(x) ((x) << SCMD_AUTH_MODE_S)
#घोषणा SCMD_AUTH_MODE_G(x) \
	(((x) >> SCMD_AUTH_MODE_S) & SCMD_AUTH_MODE_M)

/* HmacCtrl - HMAC Control. 0:NOP, 1:No truncation, 2:Support HMAC Truncation
 * per RFC 4366, 3:IPSec 96 bits, 4-7:Reserved
 */
#घोषणा SCMD_HMAC_CTRL_S    11
#घोषणा SCMD_HMAC_CTRL_M    0x7
#घोषणा SCMD_HMAC_CTRL_V(x) ((x) << SCMD_HMAC_CTRL_S)
#घोषणा SCMD_HMAC_CTRL_G(x) \
	(((x) >> SCMD_HMAC_CTRL_S) & SCMD_HMAC_CTRL_M)

/* IvSize - IV size in units of 2 bytes */
#घोषणा SCMD_IV_SIZE_S  7
#घोषणा SCMD_IV_SIZE_M  0xf
#घोषणा SCMD_IV_SIZE_V(x)   ((x) << SCMD_IV_SIZE_S)
#घोषणा SCMD_IV_SIZE_G(x)   \
	(((x) >> SCMD_IV_SIZE_S) & SCMD_IV_SIZE_M)

/* NumIVs - Number of IVs */
#घोषणा SCMD_NUM_IVS_S  0
#घोषणा SCMD_NUM_IVS_M  0x7f
#घोषणा SCMD_NUM_IVS_V(x)   ((x) << SCMD_NUM_IVS_S)
#घोषणा SCMD_NUM_IVS_G(x)   \
	(((x) >> SCMD_NUM_IVS_S) & SCMD_NUM_IVS_M)

/* EnbDbgId - If this is enabled upper 20 (63:44) bits अगर SeqNumber
 * (below) are used as Cid (connection id क्रम debug status), these
 * bits are padded to zero क्रम क्रमming the 64 bit
 * sequence number क्रम TLS
 */
#घोषणा SCMD_ENB_DBGID_S  31
#घोषणा SCMD_ENB_DBGID_M  0x1
#घोषणा SCMD_ENB_DBGID_V(x)   ((x) << SCMD_ENB_DBGID_S)
#घोषणा SCMD_ENB_DBGID_G(x)   \
	(((x) >> SCMD_ENB_DBGID_S) & SCMD_ENB_DBGID_M)

/* IV generation in SW. */
#घोषणा SCMD_IV_GEN_CTRL_S      30
#घोषणा SCMD_IV_GEN_CTRL_M      0x1
#घोषणा SCMD_IV_GEN_CTRL_V(x)   ((x) << SCMD_IV_GEN_CTRL_S)
#घोषणा SCMD_IV_GEN_CTRL_G(x)   \
	(((x) >> SCMD_IV_GEN_CTRL_S) & SCMD_IV_GEN_CTRL_M)
#घोषणा SCMD_IV_GEN_CTRL_F  SCMD_IV_GEN_CTRL_V(1U)

/* More frags */
#घोषणा SCMD_MORE_FRAGS_S   20
#घोषणा SCMD_MORE_FRAGS_M   0x1
#घोषणा SCMD_MORE_FRAGS_V(x)    ((x) << SCMD_MORE_FRAGS_S)
#घोषणा SCMD_MORE_FRAGS_G(x)    (((x) >> SCMD_MORE_FRAGS_S) & SCMD_MORE_FRAGS_M)

/*last frag */
#घोषणा SCMD_LAST_FRAG_S    19
#घोषणा SCMD_LAST_FRAG_M    0x1
#घोषणा SCMD_LAST_FRAG_V(x) ((x) << SCMD_LAST_FRAG_S)
#घोषणा SCMD_LAST_FRAG_G(x) (((x) >> SCMD_LAST_FRAG_S) & SCMD_LAST_FRAG_M)

/* TlsCompPdu */
#घोषणा SCMD_TLS_COMPPDU_S    18
#घोषणा SCMD_TLS_COMPPDU_M    0x1
#घोषणा SCMD_TLS_COMPPDU_V(x) ((x) << SCMD_TLS_COMPPDU_S)
#घोषणा SCMD_TLS_COMPPDU_G(x) (((x) >> SCMD_TLS_COMPPDU_S) & SCMD_TLS_COMPPDU_M)

/* KeyCntxtInline - Key context अंतरभूत after the scmd  OR PayloadOnly*/
#घोषणा SCMD_KEY_CTX_INLINE_S   17
#घोषणा SCMD_KEY_CTX_INLINE_M   0x1
#घोषणा SCMD_KEY_CTX_INLINE_V(x)    ((x) << SCMD_KEY_CTX_INLINE_S)
#घोषणा SCMD_KEY_CTX_INLINE_G(x)    \
	(((x) >> SCMD_KEY_CTX_INLINE_S) & SCMD_KEY_CTX_INLINE_M)
#घोषणा SCMD_KEY_CTX_INLINE_F   SCMD_KEY_CTX_INLINE_V(1U)

/* TLSFragEnable - 0: Host created TLS PDUs, 1: TLS Framgmentation in ASIC */
#घोषणा SCMD_TLS_FRAG_ENABLE_S  16
#घोषणा SCMD_TLS_FRAG_ENABLE_M  0x1
#घोषणा SCMD_TLS_FRAG_ENABLE_V(x)   ((x) << SCMD_TLS_FRAG_ENABLE_S)
#घोषणा SCMD_TLS_FRAG_ENABLE_G(x)   \
	(((x) >> SCMD_TLS_FRAG_ENABLE_S) & SCMD_TLS_FRAG_ENABLE_M)
#घोषणा SCMD_TLS_FRAG_ENABLE_F  SCMD_TLS_FRAG_ENABLE_V(1U)

/* MacOnly - Only send the MAC and discard PDU. This is valid क्रम hash only
 * modes, in this हाल TLS_TX  will drop the PDU and only
 * send back the MAC bytes.
 */
#घोषणा SCMD_MAC_ONLY_S 15
#घोषणा SCMD_MAC_ONLY_M 0x1
#घोषणा SCMD_MAC_ONLY_V(x)  ((x) << SCMD_MAC_ONLY_S)
#घोषणा SCMD_MAC_ONLY_G(x)  \
	(((x) >> SCMD_MAC_ONLY_S) & SCMD_MAC_ONLY_M)
#घोषणा SCMD_MAC_ONLY_F SCMD_MAC_ONLY_V(1U)

/* AadIVDrop - Drop the AAD and IV fields. Useful in protocols
 * which have complex AAD and IV क्रमmations Eg:AES-CCM
 */
#घोषणा SCMD_AADIVDROP_S 14
#घोषणा SCMD_AADIVDROP_M 0x1
#घोषणा SCMD_AADIVDROP_V(x)  ((x) << SCMD_AADIVDROP_S)
#घोषणा SCMD_AADIVDROP_G(x)  \
	(((x) >> SCMD_AADIVDROP_S) & SCMD_AADIVDROP_M)
#घोषणा SCMD_AADIVDROP_F SCMD_AADIVDROP_V(1U)

/* HdrLength - Length of all headers excluding TLS header
 * present beक्रमe start of crypto PDU/payload.
 */
#घोषणा SCMD_HDR_LEN_S  0
#घोषणा SCMD_HDR_LEN_M  0x3fff
#घोषणा SCMD_HDR_LEN_V(x)   ((x) << SCMD_HDR_LEN_S)
#घोषणा SCMD_HDR_LEN_G(x)   \
	(((x) >> SCMD_HDR_LEN_S) & SCMD_HDR_LEN_M)

काष्ठा cpl_tx_sec_pdu अणु
	__be32 op_ivinsrtofst;
	__be32 pldlen;
	__be32 aadstart_cipherstop_hi;
	__be32 cipherstop_lo_authinsert;
	__be32 seqno_numivs;
	__be32 ivgen_hdrlen;
	__be64 scmd1;
पूर्ण;

#घोषणा CPL_TX_SEC_PDU_OPCODE_S     24
#घोषणा CPL_TX_SEC_PDU_OPCODE_M     0xff
#घोषणा CPL_TX_SEC_PDU_OPCODE_V(x)  ((x) << CPL_TX_SEC_PDU_OPCODE_S)
#घोषणा CPL_TX_SEC_PDU_OPCODE_G(x)  \
	(((x) >> CPL_TX_SEC_PDU_OPCODE_S) & CPL_TX_SEC_PDU_OPCODE_M)

/* RX Channel Id */
#घोषणा CPL_TX_SEC_PDU_RXCHID_S  22
#घोषणा CPL_TX_SEC_PDU_RXCHID_M  0x1
#घोषणा CPL_TX_SEC_PDU_RXCHID_V(x)   ((x) << CPL_TX_SEC_PDU_RXCHID_S)
#घोषणा CPL_TX_SEC_PDU_RXCHID_G(x)   \
	(((x) >> CPL_TX_SEC_PDU_RXCHID_S) & CPL_TX_SEC_PDU_RXCHID_M)
#घोषणा CPL_TX_SEC_PDU_RXCHID_F  CPL_TX_SEC_PDU_RXCHID_V(1U)

/* Ack Follows */
#घोषणा CPL_TX_SEC_PDU_ACKFOLLOWS_S  21
#घोषणा CPL_TX_SEC_PDU_ACKFOLLOWS_M  0x1
#घोषणा CPL_TX_SEC_PDU_ACKFOLLOWS_V(x)   ((x) << CPL_TX_SEC_PDU_ACKFOLLOWS_S)
#घोषणा CPL_TX_SEC_PDU_ACKFOLLOWS_G(x)   \
	(((x) >> CPL_TX_SEC_PDU_ACKFOLLOWS_S) & CPL_TX_SEC_PDU_ACKFOLLOWS_M)
#घोषणा CPL_TX_SEC_PDU_ACKFOLLOWS_F  CPL_TX_SEC_PDU_ACKFOLLOWS_V(1U)

/* Loopback bit in cpl_tx_sec_pdu */
#घोषणा CPL_TX_SEC_PDU_ULPTXLPBK_S  20
#घोषणा CPL_TX_SEC_PDU_ULPTXLPBK_M  0x1
#घोषणा CPL_TX_SEC_PDU_ULPTXLPBK_V(x)   ((x) << CPL_TX_SEC_PDU_ULPTXLPBK_S)
#घोषणा CPL_TX_SEC_PDU_ULPTXLPBK_G(x)   \
	(((x) >> CPL_TX_SEC_PDU_ULPTXLPBK_S) & CPL_TX_SEC_PDU_ULPTXLPBK_M)
#घोषणा CPL_TX_SEC_PDU_ULPTXLPBK_F  CPL_TX_SEC_PDU_ULPTXLPBK_V(1U)

/* Length of cpl header encapsulated */
#घोषणा CPL_TX_SEC_PDU_CPLLEN_S     16
#घोषणा CPL_TX_SEC_PDU_CPLLEN_M     0xf
#घोषणा CPL_TX_SEC_PDU_CPLLEN_V(x)  ((x) << CPL_TX_SEC_PDU_CPLLEN_S)
#घोषणा CPL_TX_SEC_PDU_CPLLEN_G(x)  \
	(((x) >> CPL_TX_SEC_PDU_CPLLEN_S) & CPL_TX_SEC_PDU_CPLLEN_M)

/* PlaceHolder */
#घोषणा CPL_TX_SEC_PDU_PLACEHOLDER_S    10
#घोषणा CPL_TX_SEC_PDU_PLACEHOLDER_M    0x1
#घोषणा CPL_TX_SEC_PDU_PLACEHOLDER_V(x) ((x) << CPL_TX_SEC_PDU_PLACEHOLDER_S)
#घोषणा CPL_TX_SEC_PDU_PLACEHOLDER_G(x) \
	(((x) >> CPL_TX_SEC_PDU_PLACEHOLDER_S) & \
	 CPL_TX_SEC_PDU_PLACEHOLDER_M)

/* IvInsrtOffset: Insertion location क्रम IV */
#घोषणा CPL_TX_SEC_PDU_IVINSRTOFST_S    0
#घोषणा CPL_TX_SEC_PDU_IVINSRTOFST_M    0x3ff
#घोषणा CPL_TX_SEC_PDU_IVINSRTOFST_V(x) ((x) << CPL_TX_SEC_PDU_IVINSRTOFST_S)
#घोषणा CPL_TX_SEC_PDU_IVINSRTOFST_G(x) \
	(((x) >> CPL_TX_SEC_PDU_IVINSRTOFST_S) & \
	 CPL_TX_SEC_PDU_IVINSRTOFST_M)

/* AadStartOffset: Offset in bytes क्रम AAD start from
 * the first byte following the pkt headers (0-255 bytes)
 */
#घोषणा CPL_TX_SEC_PDU_AADSTART_S   24
#घोषणा CPL_TX_SEC_PDU_AADSTART_M   0xff
#घोषणा CPL_TX_SEC_PDU_AADSTART_V(x)    ((x) << CPL_TX_SEC_PDU_AADSTART_S)
#घोषणा CPL_TX_SEC_PDU_AADSTART_G(x)    \
	(((x) >> CPL_TX_SEC_PDU_AADSTART_S) & \
	 CPL_TX_SEC_PDU_AADSTART_M)

/* AadStopOffset: offset in bytes क्रम AAD stop/end from the first byte following
 * the pkt headers (0-511 bytes)
 */
#घोषणा CPL_TX_SEC_PDU_AADSTOP_S    15
#घोषणा CPL_TX_SEC_PDU_AADSTOP_M    0x1ff
#घोषणा CPL_TX_SEC_PDU_AADSTOP_V(x) ((x) << CPL_TX_SEC_PDU_AADSTOP_S)
#घोषणा CPL_TX_SEC_PDU_AADSTOP_G(x) \
	(((x) >> CPL_TX_SEC_PDU_AADSTOP_S) & CPL_TX_SEC_PDU_AADSTOP_M)

/* CipherStartOffset: offset in bytes क्रम encryption/decryption start from the
 * first byte following the pkt headers (0-1023 bytes)
 */
#घोषणा CPL_TX_SEC_PDU_CIPHERSTART_S    5
#घोषणा CPL_TX_SEC_PDU_CIPHERSTART_M    0x3ff
#घोषणा CPL_TX_SEC_PDU_CIPHERSTART_V(x) ((x) << CPL_TX_SEC_PDU_CIPHERSTART_S)
#घोषणा CPL_TX_SEC_PDU_CIPHERSTART_G(x) \
	(((x) >> CPL_TX_SEC_PDU_CIPHERSTART_S) & \
	 CPL_TX_SEC_PDU_CIPHERSTART_M)

/* CipherStopOffset: offset in bytes क्रम encryption/decryption end
 * from end of the payload of this command (0-511 bytes)
 */
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_HI_S      0
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_HI_M      0x1f
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_HI_V(x)   \
	((x) << CPL_TX_SEC_PDU_CIPHERSTOP_HI_S)
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_HI_G(x)   \
	(((x) >> CPL_TX_SEC_PDU_CIPHERSTOP_HI_S) & \
	 CPL_TX_SEC_PDU_CIPHERSTOP_HI_M)

#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_LO_S      28
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_LO_M      0xf
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_LO_V(x)   \
	((x) << CPL_TX_SEC_PDU_CIPHERSTOP_LO_S)
#घोषणा CPL_TX_SEC_PDU_CIPHERSTOP_LO_G(x)   \
	(((x) >> CPL_TX_SEC_PDU_CIPHERSTOP_LO_S) & \
	 CPL_TX_SEC_PDU_CIPHERSTOP_LO_M)

/* AuthStartOffset: offset in bytes क्रम authentication start from
 * the first byte following the pkt headers (0-1023)
 */
#घोषणा CPL_TX_SEC_PDU_AUTHSTART_S  18
#घोषणा CPL_TX_SEC_PDU_AUTHSTART_M  0x3ff
#घोषणा CPL_TX_SEC_PDU_AUTHSTART_V(x)   ((x) << CPL_TX_SEC_PDU_AUTHSTART_S)
#घोषणा CPL_TX_SEC_PDU_AUTHSTART_G(x)   \
	(((x) >> CPL_TX_SEC_PDU_AUTHSTART_S) & \
	 CPL_TX_SEC_PDU_AUTHSTART_M)

/* AuthStopOffset: offset in bytes क्रम authentication
 * end from end of the payload of this command (0-511 Bytes)
 */
#घोषणा CPL_TX_SEC_PDU_AUTHSTOP_S   9
#घोषणा CPL_TX_SEC_PDU_AUTHSTOP_M   0x1ff
#घोषणा CPL_TX_SEC_PDU_AUTHSTOP_V(x)    ((x) << CPL_TX_SEC_PDU_AUTHSTOP_S)
#घोषणा CPL_TX_SEC_PDU_AUTHSTOP_G(x)    \
	(((x) >> CPL_TX_SEC_PDU_AUTHSTOP_S) & \
	 CPL_TX_SEC_PDU_AUTHSTOP_M)

/* AuthInsrtOffset: offset in bytes क्रम authentication insertion
 * from end of the payload of this command (0-511 bytes)
 */
#घोषणा CPL_TX_SEC_PDU_AUTHINSERT_S 0
#घोषणा CPL_TX_SEC_PDU_AUTHINSERT_M 0x1ff
#घोषणा CPL_TX_SEC_PDU_AUTHINSERT_V(x)  ((x) << CPL_TX_SEC_PDU_AUTHINSERT_S)
#घोषणा CPL_TX_SEC_PDU_AUTHINSERT_G(x)  \
	(((x) >> CPL_TX_SEC_PDU_AUTHINSERT_S) & \
	 CPL_TX_SEC_PDU_AUTHINSERT_M)

काष्ठा cpl_rx_phys_dsgl अणु
	__be32 op_to_tid;
	__be32 pcirlxorder_to_noofsgentr;
	काष्ठा rss_header rss_hdr_पूर्णांक;
पूर्ण;

#घोषणा CPL_RX_PHYS_DSGL_OPCODE_S       24
#घोषणा CPL_RX_PHYS_DSGL_OPCODE_M       0xff
#घोषणा CPL_RX_PHYS_DSGL_OPCODE_V(x)    ((x) << CPL_RX_PHYS_DSGL_OPCODE_S)
#घोषणा CPL_RX_PHYS_DSGL_OPCODE_G(x)    \
	(((x) >> CPL_RX_PHYS_DSGL_OPCODE_S) & CPL_RX_PHYS_DSGL_OPCODE_M)

#घोषणा CPL_RX_PHYS_DSGL_ISRDMA_S       23
#घोषणा CPL_RX_PHYS_DSGL_ISRDMA_M       0x1
#घोषणा CPL_RX_PHYS_DSGL_ISRDMA_V(x)    ((x) << CPL_RX_PHYS_DSGL_ISRDMA_S)
#घोषणा CPL_RX_PHYS_DSGL_ISRDMA_G(x)    \
	(((x) >> CPL_RX_PHYS_DSGL_ISRDMA_S) & CPL_RX_PHYS_DSGL_ISRDMA_M)
#घोषणा CPL_RX_PHYS_DSGL_ISRDMA_F       CPL_RX_PHYS_DSGL_ISRDMA_V(1U)

#घोषणा CPL_RX_PHYS_DSGL_RSVD1_S        20
#घोषणा CPL_RX_PHYS_DSGL_RSVD1_M        0x7
#घोषणा CPL_RX_PHYS_DSGL_RSVD1_V(x)     ((x) << CPL_RX_PHYS_DSGL_RSVD1_S)
#घोषणा CPL_RX_PHYS_DSGL_RSVD1_G(x)     \
	(((x) >> CPL_RX_PHYS_DSGL_RSVD1_S) & \
	 CPL_RX_PHYS_DSGL_RSVD1_M)

#घोषणा CPL_RX_PHYS_DSGL_PCIRLXORDER_S          31
#घोषणा CPL_RX_PHYS_DSGL_PCIRLXORDER_M          0x1
#घोषणा CPL_RX_PHYS_DSGL_PCIRLXORDER_V(x)       \
	((x) << CPL_RX_PHYS_DSGL_PCIRLXORDER_S)
#घोषणा CPL_RX_PHYS_DSGL_PCIRLXORDER_G(x)       \
	(((x) >> CPL_RX_PHYS_DSGL_PCIRLXORDER_S) & \
	 CPL_RX_PHYS_DSGL_PCIRLXORDER_M)
#घोषणा CPL_RX_PHYS_DSGL_PCIRLXORDER_F  CPL_RX_PHYS_DSGL_PCIRLXORDER_V(1U)

#घोषणा CPL_RX_PHYS_DSGL_PCINOSNOOP_S           30
#घोषणा CPL_RX_PHYS_DSGL_PCINOSNOOP_M           0x1
#घोषणा CPL_RX_PHYS_DSGL_PCINOSNOOP_V(x)        \
	((x) << CPL_RX_PHYS_DSGL_PCINOSNOOP_S)
#घोषणा CPL_RX_PHYS_DSGL_PCINOSNOOP_G(x)        \
	(((x) >> CPL_RX_PHYS_DSGL_PCINOSNOOP_S) & \
	 CPL_RX_PHYS_DSGL_PCINOSNOOP_M)

#घोषणा CPL_RX_PHYS_DSGL_PCINOSNOOP_F   CPL_RX_PHYS_DSGL_PCINOSNOOP_V(1U)

#घोषणा CPL_RX_PHYS_DSGL_PCITPHNTENB_S          29
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNTENB_M          0x1
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNTENB_V(x)       \
	((x) << CPL_RX_PHYS_DSGL_PCITPHNTENB_S)
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNTENB_G(x)       \
	(((x) >> CPL_RX_PHYS_DSGL_PCITPHNTENB_S) & \
	 CPL_RX_PHYS_DSGL_PCITPHNTENB_M)
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNTENB_F  CPL_RX_PHYS_DSGL_PCITPHNTENB_V(1U)

#घोषणा CPL_RX_PHYS_DSGL_PCITPHNT_S     27
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNT_M     0x3
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNT_V(x)  ((x) << CPL_RX_PHYS_DSGL_PCITPHNT_S)
#घोषणा CPL_RX_PHYS_DSGL_PCITPHNT_G(x)  \
	(((x) >> CPL_RX_PHYS_DSGL_PCITPHNT_S) & \
	 CPL_RX_PHYS_DSGL_PCITPHNT_M)

#घोषणा CPL_RX_PHYS_DSGL_DCAID_S        16
#घोषणा CPL_RX_PHYS_DSGL_DCAID_M        0x7ff
#घोषणा CPL_RX_PHYS_DSGL_DCAID_V(x)     ((x) << CPL_RX_PHYS_DSGL_DCAID_S)
#घोषणा CPL_RX_PHYS_DSGL_DCAID_G(x)     \
	(((x) >> CPL_RX_PHYS_DSGL_DCAID_S) & \
	 CPL_RX_PHYS_DSGL_DCAID_M)

#घोषणा CPL_RX_PHYS_DSGL_NOOFSGENTR_S           0
#घोषणा CPL_RX_PHYS_DSGL_NOOFSGENTR_M           0xffff
#घोषणा CPL_RX_PHYS_DSGL_NOOFSGENTR_V(x)        \
	((x) << CPL_RX_PHYS_DSGL_NOOFSGENTR_S)
#घोषणा CPL_RX_PHYS_DSGL_NOOFSGENTR_G(x)        \
	(((x) >> CPL_RX_PHYS_DSGL_NOOFSGENTR_S) & \
	 CPL_RX_PHYS_DSGL_NOOFSGENTR_M)

काष्ठा cpl_rx_mps_pkt अणु
	__be32 op_to_r1_hi;
	__be32 r1_lo_length;
पूर्ण;

#घोषणा CPL_RX_MPS_PKT_OP_S     24
#घोषणा CPL_RX_MPS_PKT_OP_M     0xff
#घोषणा CPL_RX_MPS_PKT_OP_V(x)  ((x) << CPL_RX_MPS_PKT_OP_S)
#घोषणा CPL_RX_MPS_PKT_OP_G(x)  \
	(((x) >> CPL_RX_MPS_PKT_OP_S) & CPL_RX_MPS_PKT_OP_M)

#घोषणा CPL_RX_MPS_PKT_TYPE_S           20
#घोषणा CPL_RX_MPS_PKT_TYPE_M           0xf
#घोषणा CPL_RX_MPS_PKT_TYPE_V(x)        ((x) << CPL_RX_MPS_PKT_TYPE_S)
#घोषणा CPL_RX_MPS_PKT_TYPE_G(x)        \
	(((x) >> CPL_RX_MPS_PKT_TYPE_S) & CPL_RX_MPS_PKT_TYPE_M)

क्रमागत अणु
	X_CPL_RX_MPS_PKT_TYPE_PAUSE = 1 << 0,
	X_CPL_RX_MPS_PKT_TYPE_PPP   = 1 << 1,
	X_CPL_RX_MPS_PKT_TYPE_QFC   = 1 << 2,
	X_CPL_RX_MPS_PKT_TYPE_PTP   = 1 << 3
पूर्ण;

काष्ठा cpl_srq_table_req अणु
	WR_HDR;
	जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd[2];
	__u8 idx;
	__be64 rsvd_pdid;
	__be32 qlen_qbase;
	__be16 cur_msn;
	__be16 max_msn;
पूर्ण;

काष्ठा cpl_srq_table_rpl अणु
	जोड़ opcode_tid ot;
	__u8 status;
	__u8 rsvd[2];
	__u8 idx;
	__be64 rsvd_pdid;
	__be32 qlen_qbase;
	__be16 cur_msn;
	__be16 max_msn;
पूर्ण;

/* cpl_srq_table_अणुreq,rplपूर्ण.params fields */
#घोषणा SRQT_QLEN_S   28
#घोषणा SRQT_QLEN_M   0xF
#घोषणा SRQT_QLEN_V(x) ((x) << SRQT_QLEN_S)
#घोषणा SRQT_QLEN_G(x) (((x) >> SRQT_QLEN_S) & SRQT_QLEN_M)

#घोषणा SRQT_QBASE_S    0
#घोषणा SRQT_QBASE_M   0x3FFFFFF
#घोषणा SRQT_QBASE_V(x) ((x) << SRQT_QBASE_S)
#घोषणा SRQT_QBASE_G(x) (((x) >> SRQT_QBASE_S) & SRQT_QBASE_M)

#घोषणा SRQT_PDID_S    0
#घोषणा SRQT_PDID_M   0xFF
#घोषणा SRQT_PDID_V(x) ((x) << SRQT_PDID_S)
#घोषणा SRQT_PDID_G(x) (((x) >> SRQT_PDID_S) & SRQT_PDID_M)

#घोषणा SRQT_IDX_S    0
#घोषणा SRQT_IDX_M    0xF
#घोषणा SRQT_IDX_V(x) ((x) << SRQT_IDX_S)
#घोषणा SRQT_IDX_G(x) (((x) >> SRQT_IDX_S) & SRQT_IDX_M)

काष्ठा cpl_tx_tls_sfo अणु
	__be32 op_to_seg_len;
	__be32 pld_len;
	__be32 type_protover;
	__be32 r1_lo;
	__be32 seqno_numivs;
	__be32 ivgen_hdrlen;
	__be64 scmd1;
पूर्ण;

/* cpl_tx_tls_sfo macros */
#घोषणा CPL_TX_TLS_SFO_OPCODE_S         24
#घोषणा CPL_TX_TLS_SFO_OPCODE_V(x)      ((x) << CPL_TX_TLS_SFO_OPCODE_S)

#घोषणा CPL_TX_TLS_SFO_DATA_TYPE_S      20
#घोषणा CPL_TX_TLS_SFO_DATA_TYPE_V(x)   ((x) << CPL_TX_TLS_SFO_DATA_TYPE_S)

#घोषणा CPL_TX_TLS_SFO_CPL_LEN_S        16
#घोषणा CPL_TX_TLS_SFO_CPL_LEN_V(x)     ((x) << CPL_TX_TLS_SFO_CPL_LEN_S)

#घोषणा CPL_TX_TLS_SFO_SEG_LEN_S        0
#घोषणा CPL_TX_TLS_SFO_SEG_LEN_M        0xffff
#घोषणा CPL_TX_TLS_SFO_SEG_LEN_V(x)     ((x) << CPL_TX_TLS_SFO_SEG_LEN_S)
#घोषणा CPL_TX_TLS_SFO_SEG_LEN_G(x)     \
	(((x) >> CPL_TX_TLS_SFO_SEG_LEN_S) & CPL_TX_TLS_SFO_SEG_LEN_M)

#घोषणा CPL_TX_TLS_SFO_TYPE_S           24
#घोषणा CPL_TX_TLS_SFO_TYPE_M           0xff
#घोषणा CPL_TX_TLS_SFO_TYPE_V(x)        ((x) << CPL_TX_TLS_SFO_TYPE_S)
#घोषणा CPL_TX_TLS_SFO_TYPE_G(x)        \
	(((x) >> CPL_TX_TLS_SFO_TYPE_S) & CPL_TX_TLS_SFO_TYPE_M)

#घोषणा CPL_TX_TLS_SFO_PROTOVER_S       8
#घोषणा CPL_TX_TLS_SFO_PROTOVER_M       0xffff
#घोषणा CPL_TX_TLS_SFO_PROTOVER_V(x)    ((x) << CPL_TX_TLS_SFO_PROTOVER_S)
#घोषणा CPL_TX_TLS_SFO_PROTOVER_G(x)    \
	(((x) >> CPL_TX_TLS_SFO_PROTOVER_S) & CPL_TX_TLS_SFO_PROTOVER_M)

काष्ठा cpl_tls_data अणु
	काष्ठा rss_header rsshdr;
	जोड़ opcode_tid ot;
	__be32 length_pkd;
	__be32 seq;
	__be32 r1;
पूर्ण;

#घोषणा CPL_TLS_DATA_OPCODE_S           24
#घोषणा CPL_TLS_DATA_OPCODE_M           0xff
#घोषणा CPL_TLS_DATA_OPCODE_V(x)        ((x) << CPL_TLS_DATA_OPCODE_S)
#घोषणा CPL_TLS_DATA_OPCODE_G(x)        \
	(((x) >> CPL_TLS_DATA_OPCODE_S) & CPL_TLS_DATA_OPCODE_M)

#घोषणा CPL_TLS_DATA_TID_S              0
#घोषणा CPL_TLS_DATA_TID_M              0xffffff
#घोषणा CPL_TLS_DATA_TID_V(x)           ((x) << CPL_TLS_DATA_TID_S)
#घोषणा CPL_TLS_DATA_TID_G(x)           \
	(((x) >> CPL_TLS_DATA_TID_S) & CPL_TLS_DATA_TID_M)

#घोषणा CPL_TLS_DATA_LENGTH_S           0
#घोषणा CPL_TLS_DATA_LENGTH_M           0xffff
#घोषणा CPL_TLS_DATA_LENGTH_V(x)        ((x) << CPL_TLS_DATA_LENGTH_S)
#घोषणा CPL_TLS_DATA_LENGTH_G(x)        \
	(((x) >> CPL_TLS_DATA_LENGTH_S) & CPL_TLS_DATA_LENGTH_M)

काष्ठा cpl_rx_tls_cmp अणु
	काष्ठा rss_header rsshdr;
	जोड़ opcode_tid ot;
	__be32 pdulength_length;
	__be32 seq;
	__be32 ddp_report;
	__be32 r;
	__be32 ddp_valid;
पूर्ण;

#घोषणा CPL_RX_TLS_CMP_OPCODE_S         24
#घोषणा CPL_RX_TLS_CMP_OPCODE_M         0xff
#घोषणा CPL_RX_TLS_CMP_OPCODE_V(x)      ((x) << CPL_RX_TLS_CMP_OPCODE_S)
#घोषणा CPL_RX_TLS_CMP_OPCODE_G(x)      \
	(((x) >> CPL_RX_TLS_CMP_OPCODE_S) & CPL_RX_TLS_CMP_OPCODE_M)

#घोषणा CPL_RX_TLS_CMP_TID_S            0
#घोषणा CPL_RX_TLS_CMP_TID_M            0xffffff
#घोषणा CPL_RX_TLS_CMP_TID_V(x)         ((x) << CPL_RX_TLS_CMP_TID_S)
#घोषणा CPL_RX_TLS_CMP_TID_G(x)         \
	(((x) >> CPL_RX_TLS_CMP_TID_S) & CPL_RX_TLS_CMP_TID_M)

#घोषणा CPL_RX_TLS_CMP_PDULENGTH_S      16
#घोषणा CPL_RX_TLS_CMP_PDULENGTH_M      0xffff
#घोषणा CPL_RX_TLS_CMP_PDULENGTH_V(x)   ((x) << CPL_RX_TLS_CMP_PDULENGTH_S)
#घोषणा CPL_RX_TLS_CMP_PDULENGTH_G(x)   \
	(((x) >> CPL_RX_TLS_CMP_PDULENGTH_S) & CPL_RX_TLS_CMP_PDULENGTH_M)

#घोषणा CPL_RX_TLS_CMP_LENGTH_S         0
#घोषणा CPL_RX_TLS_CMP_LENGTH_M         0xffff
#घोषणा CPL_RX_TLS_CMP_LENGTH_V(x)      ((x) << CPL_RX_TLS_CMP_LENGTH_S)
#घोषणा CPL_RX_TLS_CMP_LENGTH_G(x)      \
	(((x) >> CPL_RX_TLS_CMP_LENGTH_S) & CPL_RX_TLS_CMP_LENGTH_M)
#पूर्ण_अगर  /* __T4_MSG_H */
